/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "js_inspector.h"

namespace OHOS::Ace::Napi {
namespace {
constexpr size_t STR_BUFFER_SIZE = 1024;
constexpr uint8_t PARA_COUNT = 2;
} // namespace

static ComponentObserver* GetObserver(napi_env env, napi_value thisVar)
{
    ComponentObserver* observer = nullptr;
    napi_unwrap(env, thisVar, (void**)&observer);
    if (!observer) {
        return nullptr;
    }
    observer->Initialize(env, thisVar);

    return observer;
}

static size_t ParseArgs(
    napi_env& env, napi_callback_info& info, napi_value& thisVar, napi_value& cb, CalloutType& calloutType)
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
    NAPI_ASSERT_BASE(
        env, (strcmp("layout", type) == 0 || strcmp("draw", type) == 0 || strcmp("drawChildren", type) == 0),
        "type mismatch('layout' or 'draw')", 0);
    if (strcmp("layout", type) == 0) {
        calloutType = CalloutType::LAYOUTCALLOUT;
    } else if (strcmp("draw", type) == 0) {
        calloutType = CalloutType::DRAWCALLOUT;
    } else if (strcmp("drawChildren", type) == 0) {
        calloutType = CalloutType::DRAWCHILDRENCALLOUT;
    } else {
        calloutType = CalloutType::UNKNOW;
    }

    if (argc <= 1) {
        return argc;
    }

    NAPI_CALL_BASE(env, napi_typeof(env, argv[1], &napiType), 0);
    NAPI_ASSERT_BASE(env, napiType == napi_function, "type mismatch for parameter 2", 0);
    cb = argv[1];
    return argc;
}

void ComponentObserver::callUserFunction(napi_env env, std::list<napi_ref>& cbList)
{
    napi_handle_scope scope = nullptr;
    napi_open_handle_scope(env, &scope);
    if (scope == nullptr) {
        return;
    }

    std::list<napi_value> cbs;
    for (auto& cbRef : cbList) {
        napi_value cb = nullptr;
        napi_get_reference_value(env, cbRef, &cb);
        cbs.emplace_back(cb);
    }
    for (auto& cb : cbs) {
        napi_value resultArg = nullptr;
        napi_value result = nullptr;
        napi_call_function(env, nullptr, cb, 1, &resultArg, &result);
    }
    napi_close_handle_scope(env, scope);
}

std::list<napi_ref>::iterator ComponentObserver::FindCbList(napi_env env, napi_value cb, CalloutType calloutType)
{
    if (calloutType == CalloutType::LAYOUTCALLOUT) {
        return std::find_if(cbLayoutList_.begin(), cbLayoutList_.end(), [env, cb](const napi_ref& item) -> bool {
            bool result = false;
            napi_value refItem;
            napi_get_reference_value(env, item, &refItem);
            napi_strict_equals(env, refItem, cb, &result);
            return result;
        });
    } else if (calloutType == CalloutType::DRAWCALLOUT) {
        return std::find_if(cbDrawList_.begin(), cbDrawList_.end(), [env, cb](const napi_ref& item) -> bool {
            bool result = false;
            napi_value refItem;
            napi_get_reference_value(env, item, &refItem);
            napi_strict_equals(env, refItem, cb, &result);
            return result;
        });
    } else {
        return std::find_if(cbDrawChildrenList_.begin(),
            cbDrawChildrenList_.end(), [env, cb](const napi_ref& item) -> bool {
            bool result = false;
            napi_value refItem;
            napi_get_reference_value(env, item, &refItem);
            napi_strict_equals(env, refItem, cb, &result);
            return result;
        });
    }
}

void ComponentObserver::AddCallbackToList(
    napi_value cb, std::list<napi_ref>& cbList, CalloutType calloutType, napi_env env, napi_handle_scope scope)
{
    auto iter = FindCbList(env, cb, calloutType);
    if (iter != cbList.end()) {
        napi_close_handle_scope(env, scope);
        return;
    }
    napi_ref ref = nullptr;
    napi_create_reference(env, cb, 1, &ref);
    cbList.emplace_back(ref);
    napi_close_handle_scope(env, scope);
}

void ComponentObserver::DeleteCallbackFromList(
    size_t argc, std::list<napi_ref>& cbList, CalloutType calloutType, napi_value cb, napi_env env)
{
    if (argc == 1) {
        for (auto& item : cbList) {
            napi_delete_reference(env, item);
        }
        cbList.clear();
    } else {
        NAPI_ASSERT_RETURN_VOID(env, (argc == PARA_COUNT && cb != nullptr), "Invalid arguments");
        auto iter = FindCbList(env, cb, calloutType);
        if (iter != cbList.end()) {
            napi_delete_reference(env, *iter);
            cbList.erase(iter);
        }
    }
}

void ComponentObserver::FunctionOn(napi_env& env, napi_value result, const char* funName)
{
    napi_value funcValue = nullptr;
    auto On = [](napi_env env, napi_callback_info info) -> napi_value {
        auto jsEngine = EngineHelper::GetCurrentEngineSafely();
        if (!jsEngine) {
            return nullptr;
        }

        napi_handle_scope scope = nullptr;
        napi_open_handle_scope(env, &scope);
        CHECK_NULL_RETURN(scope, nullptr);
        napi_value thisVar = nullptr;
        napi_value cb = nullptr;
        CalloutType calloutType = CalloutType::UNKNOW;
        size_t argc = ParseArgs(env, info, thisVar, cb, calloutType);
        NAPI_ASSERT(env, (argc == 2 && thisVar != nullptr && cb != nullptr), "Invalid arguments");

        ComponentObserver* observer = GetObserver(env, thisVar);
        if (!observer) {
            napi_close_handle_scope(env, scope);
            return nullptr;
        }

        if (calloutType == CalloutType::LAYOUTCALLOUT) {
            observer->AddCallbackToList(cb, observer->cbLayoutList_, calloutType, env, scope);
        } else if (calloutType == CalloutType::DRAWCALLOUT) {
            observer->AddCallbackToList(cb, observer->cbDrawList_, calloutType, env, scope);
        } else if (calloutType == CalloutType::DRAWCHILDRENCALLOUT) {
            observer->AddCallbackToList(cb, observer->cbDrawChildrenList_, calloutType, env, scope);
        }
        return nullptr;
    };
    napi_create_function(env, funName, NAPI_AUTO_LENGTH, On, nullptr, &funcValue);
    napi_set_named_property(env, result, funName, funcValue);
}

void ComponentObserver::FunctionOff(napi_env& env, napi_value result, const char* funName)
{
    napi_value funcValue = nullptr;
    auto Off = [](napi_env env, napi_callback_info info) -> napi_value {
        napi_value thisVar = nullptr;
        napi_value cb = nullptr;
        CalloutType calloutType = CalloutType::UNKNOW;
        napi_handle_scope scope = nullptr;
        napi_open_handle_scope(env, &scope);
        CHECK_NULL_RETURN(scope, nullptr);
        size_t argc = ParseArgs(env, info, thisVar, cb, calloutType);
        ComponentObserver* observer = GetObserver(env, thisVar);
        if (!observer) {
            napi_close_handle_scope(env, scope);
            return nullptr;
        }
        if (calloutType == CalloutType::LAYOUTCALLOUT) {
            observer->DeleteCallbackFromList(argc, observer->cbLayoutList_, calloutType, cb, env);
        } else if (calloutType == CalloutType::DRAWCALLOUT) {
            observer->DeleteCallbackFromList(argc, observer->cbDrawList_, calloutType, cb, env);
        } else if (calloutType == CalloutType::DRAWCHILDRENCALLOUT) {
            observer->DeleteCallbackFromList(argc, observer->cbDrawChildrenList_, calloutType, cb, env);
        }
        napi_close_handle_scope(env, scope);
        return nullptr;
    };

    napi_create_function(env, funName, NAPI_AUTO_LENGTH, Off, nullptr, &funcValue);
    napi_set_named_property(env, result, funName, funcValue);
}

void ComponentObserver::NapiSerializer(napi_env& env, napi_value& result)
{
    napi_create_object(env, &result);
    napi_handle_scope scope = nullptr;
    napi_open_handle_scope(env, &scope);
    if (scope == nullptr) {
        return;
    }

    napi_value componentIdVal = nullptr;
    napi_create_string_utf8(env, componentId_.c_str(), componentId_.size(), &componentIdVal);
    napi_set_named_property(env, result, "componentId", componentIdVal);

    napi_wrap(
        env, result, this,
        [](napi_env env, void* data, void* hint) {
            ComponentObserver* observer = static_cast<ComponentObserver*>(data);
            observer->Destroy(env);
            if (observer != nullptr) {
                delete observer;
            }
        },
        nullptr, nullptr);

    FunctionOn(env, result, "on");
    FunctionOff(env, result, "off");
    napi_close_handle_scope(env, scope);
}

void ComponentObserver::Destroy(napi_env env)
{
    for (auto& layoutitem : cbLayoutList_) {
        napi_delete_reference(env, layoutitem);
    }
    for (auto& drawitem : cbDrawList_) {
        napi_delete_reference(env, drawitem);
    }
    for (auto& drawChildrenitem : cbDrawChildrenList_) {
        napi_delete_reference(env, drawChildrenitem);
    }
    cbLayoutList_.clear();
    cbDrawList_.clear();
    cbDrawChildrenList_.clear();
    auto jsEngine = weakEngine_.Upgrade();
    if (!jsEngine) {
        return;
    }
    jsEngine->UnregisterLayoutInspectorCallback(layoutEvent_, componentId_);
    jsEngine->UnregisterDrawInspectorCallback(drawEvent_, componentId_);
    jsEngine->UnregisterDrawChildrenInspectorCallback(drawChildrenEvent_, componentId_);
}

void ComponentObserver::Initialize(napi_env env, napi_value thisVar)
{
    napi_handle_scope scope = nullptr;
    napi_open_handle_scope(env, &scope);
    if (scope == nullptr) {
        return;
    }
    napi_close_handle_scope(env, scope);
}

static napi_value JSCreateComponentObserver(napi_env env, napi_callback_info info)
{
    auto jsEngine = EngineHelper::GetCurrentEngineSafely();
    if (!jsEngine) {
        return nullptr;
    }
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
    char componentId[STR_BUFFER_SIZE] = { 0 };
    size_t len = 0;
    napi_get_value_string_utf8(env, argv, componentId, STR_BUFFER_SIZE, &len);
    NAPI_ASSERT(env, len < STR_BUFFER_SIZE, "condition string too long");

    /* construct object for query */
    std::string componentIdStr(componentId, len);
    ComponentObserver* observer = new ComponentObserver(componentIdStr);
    napi_value result = nullptr;
    observer->NapiSerializer(env, result);
    if (!result) {
        delete observer;
        return nullptr;
    }
    auto layoutCallback = [observer, env]() { observer->callUserFunction(env, observer->cbLayoutList_); };
    observer->layoutEvent_ = AceType::MakeRefPtr<InspectorEvent>(std::move(layoutCallback));

    auto drawCallback = [observer, env]() { observer->callUserFunction(env, observer->cbDrawList_); };
    observer->drawEvent_ = AceType::MakeRefPtr<InspectorEvent>(std::move(drawCallback));
    auto drawChildrenCallback = [observer, env]() { observer->callUserFunction(env, observer->cbDrawChildrenList_); };
    observer->drawChildrenEvent_ = AceType::MakeRefPtr<InspectorEvent>(std::move(drawChildrenCallback));
    jsEngine->RegisterLayoutInspectorCallback(observer->layoutEvent_, observer->componentId_);
    jsEngine->RegisterDrawInspectorCallback(observer->drawEvent_, observer->componentId_);
    jsEngine->RegisterDrawChildrenInspectorCallback(observer->drawChildrenEvent_, observer->componentId_);
    observer->SetEngine(jsEngine);
#if defined(PREVIEW)
    layoutCallback();
    drawCallback();
#endif
    return result;
}

static napi_value Export(napi_env env, napi_value exports)
{
    napi_property_descriptor properties[] = { DECLARE_NAPI_FUNCTION(
        "createComponentObserver", JSCreateComponentObserver) };

    NAPI_CALL(env, napi_define_properties(env, exports, sizeof(properties) / sizeof(properties[0]), properties));
    return exports;
}

static napi_module inspector_module = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = Export,
    .nm_modname = "arkui.inspector", // relative to the dynamic library's name
    .nm_priv = ((void*)0),
    .reserved = { 0 },
};

extern "C" __attribute__((constructor)) void RegisterInspector()
{
    napi_module_register(&inspector_module);
}
} // namespace OHOS::Ace::Napi
