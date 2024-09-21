/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <algorithm>
#include <map>
#include <mutex>
#include <set>
#include <vector>

#include "napi/native_api.h"
#include "napi/native_common.h"
#include "napi/native_node_api.h"

#include "base/utils/utils.h"
#include "bridge/common/media_query/media_queryer.h"
#include "bridge/common/utils/engine_helper.h"
#include "bridge/js_frontend/engine/common/js_engine.h"
#include "core/common/container.h"

namespace OHOS::Ace::Napi {
namespace {
constexpr size_t STR_BUFFER_SIZE = 1024;
constexpr int32_t TWO_ARGS = 2;
}

using namespace OHOS::Ace::Framework;
struct MediaQueryResult {
    bool matches_ = false;
    std::string media_;

    MediaQueryResult(bool match, const std::string& media) : matches_(match), media_(media) {}
    virtual ~MediaQueryResult() = default;
    virtual void NapiSerializer(napi_env& env, napi_value& result)
    {
        /* construct a MediaQueryListener object */
        napi_create_object(env, &result);
        napi_handle_scope scope = nullptr;
        napi_open_handle_scope(env, &scope);
        if (scope == nullptr) {
            return;
        }

        napi_value matchesVal = nullptr;
        napi_get_boolean(env, matches_, &matchesVal);
        napi_set_named_property(env, result, "matches", matchesVal);

        napi_value mediaVal = nullptr;
        napi_create_string_utf8(env, media_.c_str(), media_.size(), &mediaVal);
        napi_set_named_property(env, result, "media", mediaVal);
        napi_close_handle_scope(env, scope);
    }
};

class MediaQueryListener : public MediaQueryResult {
public:
    MediaQueryListener(bool match, const std::string& media) : MediaQueryResult(match, media) {}
    ~MediaQueryListener() override
    {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            TAG_LOGI(AceLogTag::ACE_MEDIA_QUERY, "clean:%{public}s", media_.c_str());
            CleanListenerSet();
        }

        if (env_ == nullptr) {
            return;
        }
        for (auto& item : cbList_) {
            napi_delete_reference(env_, item);
        }
    }

    static void NapiCallback(JsEngine* jsEngine)
    {
        OnNapiCallback(jsEngine);
    }

    static void OnNapiCallback(JsEngine* jsEngine)
    {
        std::set<std::unique_ptr<MediaQueryListener>> delayDeleteListenerSets;
        std::set<napi_ref> delayDeleteCallbacks;
        std::vector<MediaQueryListener*> copyListeners;
        {
            std::lock_guard<std::mutex> lock(mutex_);
            auto& currentListeners = listenerSets_[AceType::WeakClaim(jsEngine)];
            copyListeners.insert(copyListeners.end(), currentListeners.begin(), currentListeners.end());
        }
        struct Leave {
            ~Leave()
            {
                if (delayDeleteEnv_) {
                    for (auto& cbRef : *delayDeleteCallbacks_) {
                        napi_delete_reference(delayDeleteEnv_, cbRef);
                    }
                }
                delayDeleteEnv_ = nullptr;
                delayDeleteCallbacks_ = nullptr;
                delayDeleteListenerSets_ = nullptr;
            }
        } leave;

        delayDeleteCallbacks_ = &delayDeleteCallbacks;
        delayDeleteListenerSets_ = &delayDeleteListenerSets;

        TriggerAllCallbacks(copyListeners);
    }

    static void TriggerAllCallbacks(std::vector<MediaQueryListener*>& copyListeners)
    {
        MediaQueryer queryer;
        for (auto& listener : copyListeners) {
            auto json = MediaQueryInfo::GetMediaQueryJsonInfo();
            listener->matches_ = queryer.MatchCondition(listener->media_, json);
            std::set<napi_ref> delayDeleteCallbacks;
            std::vector<napi_ref> copyCallbacks;
            {
                std::lock_guard<std::mutex> lock(mutex_);
                auto& currentCallbacks = listener->cbList_;
                copyCallbacks.insert(copyCallbacks.end(), currentCallbacks.begin(), currentCallbacks.end());
            }

            for (const auto& cbRef : copyCallbacks) {
                if (delayDeleteCallbacks_->find(cbRef) != delayDeleteCallbacks_->end()) {
                    continue;
                }
                TAG_LOGI(AceLogTag::ACE_MEDIA_QUERY, "trigger:%{public}s matches:%{public}d",
                    listener->media_.c_str(), listener->matches_);
                napi_handle_scope scope = nullptr;
                napi_open_handle_scope(listener->env_, &scope);
                if (scope == nullptr) {
                    return;
                }

                napi_value cb = nullptr;
                napi_get_reference_value(listener->env_, cbRef, &cb);

                napi_value resultArg = nullptr;
                listener->MediaQueryResult::NapiSerializer(listener->env_, resultArg);

                napi_value result = nullptr;
                napi_call_function(listener->env_, nullptr, cb, 1, &resultArg, &result);
                napi_close_handle_scope(listener->env_, scope);
            }
        }
    }

    static napi_value On(napi_env env, napi_callback_info info)
    {
        auto jsEngine = EngineHelper::GetCurrentEngineSafely();
        if (!jsEngine) {
            return nullptr;
        }
        jsEngine->RegisterMediaUpdateCallback(NapiCallback);

        napi_handle_scope scope = nullptr;
        napi_open_handle_scope(env, &scope);
        if (scope == nullptr) {
            return nullptr;
        }
        napi_value thisVar = nullptr;
        napi_value cb = nullptr;
        size_t argc = ParseArgs(env, info, thisVar, cb);
        if (!(argc == TWO_ARGS && thisVar != nullptr && cb != nullptr)) {
            napi_close_handle_scope(env, scope);
            return nullptr;
        }
        MediaQueryListener* listener = GetListener(env, thisVar);
        if (!listener) {
            napi_close_handle_scope(env, scope);
            return nullptr;
        }
        auto iter = listener->FindCbList(cb);
        if (iter != listener->cbList_.end()) {
            napi_close_handle_scope(env, scope);
            return nullptr;
        }
        napi_ref ref = nullptr;
        napi_create_reference(env, cb, 1, &ref);
        listener->cbList_.emplace_back(ref);
        TAG_LOGI(AceLogTag::ACE_MEDIA_QUERY, "on:%{public}s num=%{public}d", listener->media_.c_str(),
            static_cast<int>(listener->cbList_.size()));
        napi_close_handle_scope(env, scope);

#if defined(PREVIEW)
        NapiCallback(AceType::RawPtr(jsEngine));
#endif

        return nullptr;
    }

    static napi_value Off(napi_env env, napi_callback_info info)
    {
        napi_value thisVar = nullptr;
        napi_value cb = nullptr;
        size_t argc = ParseArgs(env, info, thisVar, cb);
        MediaQueryListener* listener = GetListener(env, thisVar);
        if (!listener) {
            return nullptr;
        }
        if (argc == 1) {
            if (delayDeleteCallbacks_) {
                delayDeleteEnv_ = env;
                for (auto& item : listener->cbList_) {
                    (*delayDeleteCallbacks_).emplace(item);
                }
            } else {
                for (auto& item : listener->cbList_) {
                    napi_delete_reference(listener->env_, item);
                }
            }
            listener->cbList_.clear();
        } else {
            NAPI_ASSERT(env, (argc == 2 && listener != nullptr && cb != nullptr), "Invalid arguments");
            auto iter = listener->FindCbList(cb);
            if (iter != listener->cbList_.end()) {
                if (delayDeleteCallbacks_) {
                    delayDeleteEnv_ = env;
                    (*delayDeleteCallbacks_).emplace(*iter);
                } else {
                    napi_delete_reference(listener->env_, *iter);
                }
                listener->cbList_.erase(iter);
            }
        }
        TAG_LOGI(AceLogTag::ACE_MEDIA_QUERY, "off:%{public}s num=%{public}d", listener->media_.c_str(),
            static_cast<int>(listener->cbList_.size()));
        return nullptr;
    }

    std::list<napi_ref>::iterator FindCbList(napi_value cb)
    {
        return std::find_if(cbList_.begin(), cbList_.end(), [env = env_, cb](const napi_ref& item) -> bool {
            bool result = false;
            napi_value refItem;
            napi_get_reference_value(env, item, &refItem);
            napi_strict_equals(env, refItem, cb, &result);
            return result;
        });
    }

    void NapiSerializer(napi_env& env, napi_value& result) override
    {
        MediaQueryResult::NapiSerializer(env, result);

        napi_wrap(
            env, result, this,
            [](napi_env env, void* data, void* hint) {
                MediaQueryListener* listener = static_cast<MediaQueryListener*>(data);
                if (delayDeleteListenerSets_) {
                    delayDeleteListenerSets_->emplace(listener);
                } else {
                    delete listener;
                }
            },
            nullptr, nullptr);

        /* insert callback functions */
        const char* funName = "on";
        napi_value funcValue = nullptr;
        napi_create_function(env, funName, NAPI_AUTO_LENGTH, On, nullptr, &funcValue);
        napi_set_named_property(env, result, funName, funcValue);

        funName = "off";
        napi_create_function(env, funName, NAPI_AUTO_LENGTH, Off, nullptr, &funcValue);
        napi_set_named_property(env, result, funName, funcValue);
    }

private:
    void CleanListenerSet()
    {
        auto iter = listenerSets_.begin();
        while (iter != listenerSets_.end()) {
            iter->second.erase(this);
            if (iter->second.empty()) {
                auto jsEngineWeak = iter->first.Upgrade();
                if (jsEngineWeak) {
                    jsEngineWeak->UnregisterMediaUpdateCallback();
                }
                iter = listenerSets_.erase(iter);
            } else {
                iter++;
            }
        }
    }

    void Initialize(napi_env env, napi_value thisVar)
    {
        napi_handle_scope scope = nullptr;
        napi_open_handle_scope(env, &scope);
        if (scope == nullptr) {
            return;
        }
        if (env_ == nullptr) {
            env_ = env;
        }
        napi_close_handle_scope(env, scope);
        auto jsEngine = EngineHelper::GetCurrentEngineSafely();
        if (!jsEngine) {
            return;
        }
        {
            std::lock_guard<std::mutex> lock(mutex_);
            listenerSets_[jsEngine].emplace(this);
        }
    }

    static MediaQueryListener* GetListener(napi_env env, napi_value thisVar)
    {
        MediaQueryListener* listener = nullptr;
        napi_unwrap(env, thisVar, (void**)&listener);
        CHECK_NULL_RETURN(listener, nullptr);
        listener->Initialize(env, thisVar);
        return listener;
    }

    static size_t ParseArgs(napi_env& env, napi_callback_info& info, napi_value& thisVar, napi_value& cb)
    {
        const size_t argNum = 2;
        size_t argc = argNum;
        napi_value argv[argNum] = { 0 };
        void* data = nullptr;
        napi_get_cb_info(env, info, &argc, argv, &thisVar, &data);
        NAPI_ASSERT_BASE(env, argc > 0, "too few parameter", 0);

        napi_valuetype napiType;
        NAPI_CALL_BASE(env, napi_typeof(env, argv[0], &napiType), 0);
        NAPI_ASSERT_BASE(env, napiType == napi_string, "parameter 1 should be string", 0);
        char type[STR_BUFFER_SIZE] = { 0 };
        size_t len = 0;
        napi_get_value_string_utf8(env, argv[0], type, STR_BUFFER_SIZE, &len);
        NAPI_ASSERT_BASE(env, len < STR_BUFFER_SIZE, "condition string too long", 0);
        NAPI_ASSERT_BASE(env, strcmp("change", type) == 0, "type mismatch('change')", 0);

        if (argc <= 1) {
            return argc;
        }

        NAPI_CALL_BASE(env, napi_typeof(env, argv[1], &napiType), 0);
        NAPI_ASSERT_BASE(env, napiType == napi_function, "type mismatch for parameter 2", 0);
        cb = argv[1];
        return argc;
    }

    napi_env env_ = nullptr;
    std::list<napi_ref> cbList_;
    static std::set<std::unique_ptr<MediaQueryListener>>* delayDeleteListenerSets_;
    static napi_env delayDeleteEnv_;
    static std::set<napi_ref>* delayDeleteCallbacks_;
    static std::map<WeakPtr<JsEngine>, std::set<MediaQueryListener*>> listenerSets_;
    static std::mutex mutex_;
};
std::set<std::unique_ptr<MediaQueryListener>>* MediaQueryListener::delayDeleteListenerSets_;
napi_env MediaQueryListener::delayDeleteEnv_ = nullptr;
std::set<napi_ref>* MediaQueryListener::delayDeleteCallbacks_;
std::map<WeakPtr<JsEngine>, std::set<MediaQueryListener*>> MediaQueryListener::listenerSets_;
std::mutex MediaQueryListener::mutex_;

static napi_value JSMatchMediaSync(napi_env env, napi_callback_info info)
{
    /* Get arguments */
    size_t argc = 1;
    napi_value argv = nullptr;
    napi_value thisVar = nullptr;
    void* data = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, &argv, &thisVar, &data));
    NAPI_ASSERT(env, argc == 1, "requires 1 parameter");

    /* Checkout arguments */
    napi_valuetype type;
    NAPI_CALL(env, napi_typeof(env, argv, &type));
    NAPI_ASSERT(env, type == napi_string, "type mismatch");
    char condition[STR_BUFFER_SIZE] = { 0 };
    size_t len = 0;
    napi_get_value_string_utf8(env, argv, condition, STR_BUFFER_SIZE, &len);
    NAPI_ASSERT(env, len < STR_BUFFER_SIZE, "condition string too long");

    /* construct object for query */
    std::string conditionStr(condition, len);
    auto mediaFeature = MediaQueryInfo::GetMediaQueryJsonInfo();
    MediaQueryer queryer;
    bool matchResult = queryer.MatchCondition(conditionStr, mediaFeature);
    MediaQueryListener* listener = new MediaQueryListener(matchResult, conditionStr);
    napi_value result = nullptr;
    listener->NapiSerializer(env, result);
    return result;
}

static napi_value Export(napi_env env, napi_value exports)
{
    napi_property_descriptor properties[] = { DECLARE_NAPI_FUNCTION("matchMediaSync", JSMatchMediaSync) };

    NAPI_CALL(env, napi_define_properties(env, exports, sizeof(properties) / sizeof(properties[0]), properties));
    return exports;
}

static napi_module media_query_module = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = Export,
    .nm_modname = "mediaquery", // relative to the dynamic library's name
    .nm_priv = ((void*)0),
    .reserved = { 0 },
};

extern "C" __attribute__((constructor)) void RegisterMediaQuery()
{
    napi_module_register(&media_query_module);
}

} // namespace OHOS::Ace::Napi
