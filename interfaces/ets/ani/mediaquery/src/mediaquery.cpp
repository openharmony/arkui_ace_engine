/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include <ani.h>
#include <array>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <future>
#include <thread>
#include <map>
#include <string>

#include "frameworks/bridge/declarative_frontend/engine/jsi/jsi_declarative_engine.h"
#include "frameworks/base/utils/utils.h"
#include "frameworks/bridge/common/utils/engine_helper.h"
#include "frameworks/bridge/common/media_query/media_queryer.h"
#include "frameworks/core/common/container.h"
#include "frameworks/core/common/container_scope.cpp"
#include "frameworks/core/common/container_scope.h"
#include "frameworks/core/animation/cubic_curve.h"
#include "frameworks/core/animation/curve.h"

namespace {
constexpr int32_t TWO_ARGS = 2;
}

struct MediaQueryResult {
    bool matches_ = false;
    std::string media_;

    MediaQueryResult(bool match, const std::string& media) : matches_(match), media_(media) {}
    virtual ~MediaQueryResult() = default;
    virtual void AniSerializer([[maybe_unused]] ani_env *env, ani_object& result)
    {
        ani_boolean match = false;
        ani_string media = nullptr;
        static const char *className = "L@ohos/mediaquery/mediaquery/Mediaquery;";
        ani_class cls;
        if (ANI_OK != env->FindClass(className, &cls)) {
            return;
        }
        ani_method method;
        if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", nullptr, &method)) {
            return;
        }
        env->Object_New(cls, method, &result, match, media);
        ani_size nr_refs = 16;
        if (ANI_OK != env->CreateLocalScope(nr_refs)) {
            return;
        }
        const char* mediac = media_.c_str();
        env->String_NewUTF8(mediac, strlen(mediac), &media);
        match = static_cast<ani_boolean>(matches_);
        env->Object_SetFieldByName_Boolean(result, "matches", match);
        env->Object_SetFieldByName_Ref(result, "matches", static_cast<ani_ref>(media));
        env->DestroyLocalScope();
    }
};

class MediaQueryListener : public MediaQueryResult {
public:
    MediaQueryListener(bool match, const std::string& media) : MediaQueryResult(match, media) {}
    ~MediaQueryListener() override
    {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            TAG_LOGI(OHOS::Ace::AceLogTag::ACE_MEDIA_QUERY, "clean:%{public}s", media_.c_str());
            CleanListenerSet();
        }
        if (env_ == nullptr) {
            return;
        }
        for (auto& item : cbList_) {
            env_->GlobalReference_Delete(item);
        }
    }

    static void IdlCallback(OHOS::Ace::Framework::JsEngine* jsEngine)
    {
        OnIdlCallback(jsEngine);
    }

    static void OnIdlCallback(OHOS::Ace::Framework::JsEngine* jsEngine)
    {
        std::set<std::unique_ptr<MediaQueryListener>> delayDeleteListenerSets;
        std::set<ani_ref> delayDeleteCallbacks;
        std::vector<MediaQueryListener*> copyListeners;
        {
            std::lock_guard<std::mutex> lock(mutex_);
            auto& currentListeners = listenerSets_[OHOS::Ace::AceType::WeakClaim(jsEngine)];
            copyListeners.insert(copyListeners.end(), currentListeners.begin(), currentListeners.end());
        }
        struct Leave {
            ~Leave()
            {
                for (auto& cbRef : *delayDeleteCallbacks_) {
                    delayDeleteEnv_->GlobalReference_Delete(cbRef);
                }
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
        OHOS::Ace::Framework::MediaQueryer queryer;
        for (auto& listener : copyListeners) {
            auto json = OHOS::Ace::Framework::MediaQueryInfo::GetMediaQueryJsonInfo();
            listener->matches_ = queryer.MatchCondition(listener->media_, json);
            std::set<ani_ref> delayDeleteCallbacks;
            std::vector<ani_ref> copyCallbacks;
            {
                std::lock_guard<std::mutex> lock(mutex_);
                auto& currentCallbacks = listener->cbList_;
                copyCallbacks.insert(copyCallbacks.end(), currentCallbacks.begin(), currentCallbacks.end());
            }

            for (const auto &cbRef : copyCallbacks) {
                if (delayDeleteCallbacks_->find(cbRef) != delayDeleteCallbacks_->end()) {
                    continue;
                }
                TAG_LOGI(OHOS::Ace::AceLogTag::ACE_MEDIA_QUERY, "trigger:%{public}s matches:%{public}d",
                    listener->media_.c_str(), listener->matches_);
                ani_size nr_refs = 16;
                if (ANI_OK != listener->env_->CreateLocalScope(nr_refs)) {
                    return;
                }
                ani_wref cbWref;
                listener->env_->WeakReference_Create(cbRef, &cbWref);
                ani_ref ref;
                ani_boolean wasReleased;
                listener->env_->WeakReference_GetReference(cbWref, &wasReleased, &ref);
                ani_object result = {};
                listener->MediaQueryResult::AniSerializer(listener->env_, result);
                ani_ref resultRef = static_cast<ani_ref>(result);
                listener->env_->FunctionalObject_Call(static_cast<ani_fn_object>(ref), 1, &resultRef, nullptr);
                listener->env_->DestroyLocalScope();
            }
        }
    }

    std::list<ani_ref>::iterator FindCbList(ani_object cb)
    {
        return std::find_if(cbList_.begin(), cbList_.end(), [env = env_, cb](const ani_ref& item) -> bool {
            ani_boolean result = false;
            ani_wref cbWref;
            env->WeakReference_Create(item, &cbWref);
            ani_ref ref;
            ani_boolean wasReleased;
            env->WeakReference_GetReference(cbWref, &wasReleased, &ref);
            env->Reference_StrictEquals(ref, cb, &result);
            return static_cast<bool>(result);
        });
    }

    static void On([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object,
        ani_string type, ani_object callback)
    {
        auto jsEngine = OHOS::Ace::EngineHelper::GetCurrentEngineSafely();
        if (!jsEngine) {
            return;
        }
        jsEngine->RegisterMediaUpdateCallback(MediaQueryListener::IdlCallback);
        ani_size nr_refs = 16;
        if (ANI_OK != env->CreateLocalScope(nr_refs)) {
            return;
        }
        size_t argc = ParseArgs(env, object, type, callback);
        if (argc == TWO_ARGS) {
            env->DestroyLocalScope();
            return;
        }

        MediaQueryListener* listener = GetListener(env, object);
        if (!listener) {
            env->DestroyLocalScope();
            return;
        }
        auto iter = listener->FindCbList(callback);
        if (iter != listener->cbList_.end()) {
            env->DestroyLocalScope();
            return;
        }
        ani_ref ref;
        env->GlobalReference_Create(static_cast<ani_ref>(callback), &ref);
        listener->cbList_.emplace_back(ref);
        TAG_LOGI(OHOS::Ace::AceLogTag::ACE_MEDIA_QUERY, "on:%{public}s num=%{public}d", listener->media_.c_str(),
            static_cast<int>(listener->cbList_.size()));
        env->DestroyLocalScope();
    }

    static void Off([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object,
        ani_string type, ani_object callback)
    {
        size_t argc = ParseArgs(env, object, type, callback);
        MediaQueryListener* listener = GetListener(env, object);
        if (!listener || argc == 0) {
            return;
        }
        if (argc == 1) {
            if (delayDeleteCallbacks_) {
                delayDeleteEnv_ = env;
                for (auto& item : listener->cbList_) {
                    (*delayDeleteCallbacks_).emplace(item);
                }
            } else {
                for (auto& item : listener->cbList_) {
                    listener->env_->GlobalReference_Delete(item);
                }
            }
            listener->cbList_.clear();
        } else {
            auto iter = listener->FindCbList(callback);
            if (iter != listener->cbList_.end()) {
                if (delayDeleteCallbacks_) {
                    (*delayDeleteCallbacks_).emplace(*iter);
                } else {
                    listener->env_->GlobalReference_Delete(*iter);
                }
                listener->cbList_.erase(iter);
            }
        }
        TAG_LOGI(OHOS::Ace::AceLogTag::ACE_MEDIA_QUERY, "off:%{public}s num=%{public}d", listener->media_.c_str(),
            static_cast<int>(listener->cbList_.size()));
        return;
    }

    void AniSerializer([[maybe_unused]] ani_env *env, ani_object& result) override
    {
        MediaQueryResult::AniSerializer(env, result);
        static const char *mediaquery = "L@ohos/mediaquery/mediaquery/Mediaquery;";
        ani_class cls2;
        if (ANI_OK != env->FindClass(mediaquery, &cls2)) {
            std::cerr << "Not found '" << mediaquery << "'" << std::endl;
            return;
        }
        ani_field serializerField;
        if (ANI_OK != env->Class_FindField(cls2, "nativeSerializerResult", &serializerField)) {
            std::cerr << "animator create Get Field Fail" << "'" << std::endl;
            return;
        }
        env->Object_SetField_Long(result, serializerField, reinterpret_cast<ani_long>(this));
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

    void Initialize([[maybe_unused]] ani_env *env)
    {
        ani_size nr_refs = 16;
        if (ANI_OK != env->CreateLocalScope(nr_refs)) {
            return;
        }
        if (env_ == nullptr) {
            env_ = env;
        }
        env->DestroyLocalScope();
        auto jsEngine = OHOS::Ace::EngineHelper::GetCurrentEngineSafely();
        if (!jsEngine) {
            return;
        }
        {
            std::lock_guard<std::mutex> lock(mutex_);
            listenerSets_[jsEngine].emplace(this);
        }
    }

    static MediaQueryListener* GetListener([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object)
    {
        MediaQueryListener* listener = nullptr;
        ani_long serializer;
        env->Object_GetFieldByName_Long(object, "nativeSerializerResult", &serializer);
        listener = reinterpret_cast<MediaQueryListener*>(serializer);
        CHECK_NULL_RETURN(listener, nullptr);
        listener->Initialize(env);
        return listener;
    }

    static std::string ANIUtils_ANIStringToStdString(ani_env *env, ani_string ani_str)
    {
        ani_size  strSize;
        env->String_GetUTF8Size(ani_str, &strSize);
    
        std::vector<char> buffer(strSize + 1);
        char* utf8Buffer = buffer.data();

        ani_size bytes_written = 0;
        env->String_GetUTF8(ani_str, utf8Buffer, strSize + 1, &bytes_written);
        
        utf8Buffer[bytes_written] = '\0';
        std::string content = std::string(utf8Buffer);
        return content;
    }

    static size_t ParseArgs([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object,
        ani_string type, ani_object callback)
    {
        auto typeStr = ANIUtils_ANIStringToStdString(env, type);
        if (typeStr != "change") {
            return 0;
        }
        ani_boolean isUndefinedResponse;
        env->Reference_IsUndefined(callback, &isUndefinedResponse);
        if (isUndefinedResponse) {
            return 1;
        }
        return TWO_ARGS;
    }

    ani_env *env_ = nullptr;
    std::list<ani_ref> cbList_;
    static std::set<std::unique_ptr<MediaQueryListener>>* delayDeleteListenerSets_;
    static std::set<ani_ref>* delayDeleteCallbacks_;
    static ani_env* delayDeleteEnv_;
    static std::map<OHOS::Ace::WeakPtr<OHOS::Ace::Framework::JsEngine>, std::set<MediaQueryListener*>> listenerSets_;
    static std::mutex mutex_;
};
std::set<std::unique_ptr<MediaQueryListener>>* MediaQueryListener::delayDeleteListenerSets_;
ani_env* MediaQueryListener::delayDeleteEnv_;
std::set<ani_ref>* MediaQueryListener::delayDeleteCallbacks_;
std::map<OHOS::Ace::WeakPtr<OHOS::Ace::Framework::JsEngine>, std::set<MediaQueryListener*>>
    MediaQueryListener::listenerSets_;
std::mutex MediaQueryListener::mutex_;

void On([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_string type, ani_object callback)
{
    MediaQueryListener::On(env, object, type, callback);
#if defined(PREVIEW)
    MediaQueryListener::IdlCallback(AceType::RawPtr(jsEngine));
#endif
}

void Off([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_string type, ani_object callback)
{
    MediaQueryListener::Off(env, object, type, callback);
}

static ani_object JSMatchMediaSync([[maybe_unused]] ani_env *env, ani_string condition)
{
    ani_size strSize = 0U;
    env->String_GetUTF8Size(condition, &strSize);
    std::vector<char> buffer(strSize + 1); // +1 for null terminator
    char* utf8Buffer = buffer.data();
    ani_size bytes_written = 0;
    env->String_GetUTF8(condition, utf8Buffer, strSize + 1, &bytes_written);
    utf8Buffer[bytes_written] = '\0';
    std::string mediaCondition = std::string(utf8Buffer);

    static const char *className = "L@ohos/mediaquery/mediaquery;";
    ani_object mediaquery_obj = {};
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        return mediaquery_obj;
    }

    ani_method ctor;
    if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", nullptr, &ctor)) {
        return mediaquery_obj;
    }

    OHOS::Ace::Framework::MediaQueryer queryer;
    auto mediaFeature = OHOS::Ace::Framework::MediaQueryInfo::GetMediaQueryJsonInfo();
    bool matchResult = queryer.MatchCondition(mediaCondition, mediaFeature);
    MediaQueryListener* listener = new MediaQueryListener(matchResult, mediaCondition);

    listener->AniSerializer(env, mediaquery_obj);
    return mediaquery_obj;
}

ANI_EXPORT ani_status ANI_Constructor(ani_vm *vm, uint32_t *result)
{
    ani_env *env;
    if (ANI_OK != vm->GetEnv(ANI_VERSION_1, &env)) {
        return ANI_ERROR;
    }

    ani_namespace ns;
    if (ANI_OK != env->FindNamespace("L@ohos/mediaquery/mediaquery;", &ns)) {
        return ANI_ERROR;
    }
    std::array methods = {
        ani_native_function {"matchMediaSync", nullptr, reinterpret_cast<void *>(JSMatchMediaSync)},
    };

    if (ANI_OK != env->Namespace_BindNativeFunctions(ns, methods.data(), methods.size())) {
        return ANI_ERROR;
    }

    static const char *className = "L@ohos/mediaquery/mediaquery/Mediaquery;";
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        return ANI_ERROR;
    }

    std::array methodsListener = {
        ani_native_function {"on", nullptr, reinterpret_cast<void *>(On)},
        ani_native_function {"off", nullptr, reinterpret_cast<void *>(Off)},
    };

    if (ANI_OK != env->Class_BindNativeMethods(cls, methodsListener.data(), methodsListener.size())) {
        return ANI_ERROR;
    };
    *result = ANI_VERSION_1;
    return ANI_OK;
}