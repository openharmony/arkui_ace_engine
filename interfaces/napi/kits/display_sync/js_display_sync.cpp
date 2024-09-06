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

#include "interfaces/napi/kits/utils/napi_utils.h"
#include "interfaces/napi/kits/display_sync/js_display_sync.h"


namespace OHOS::Ace::Napi {
constexpr size_t STR_MAX_BUFFER_SIZE = 1024;
constexpr size_t CALLBACK_OJECT_NUM = 1;
constexpr size_t ARGC_NUM_SIZE = 2;

napi_value NapiGetUndefined(napi_env env)
{
    napi_value result = nullptr;
    napi_get_undefined(env, &result);
    return result;
}

void NapiPrintErrorInfo(napi_env env)
{
    const napi_extended_error_info *error_info;
    napi_get_last_error_info(env, &error_info);
    LOGE("JsDisplaySync ErrorInfo: %{public}s", error_info->error_message);
    return;
}

bool ParseJsValue(napi_env env, napi_value jsObject, const std::string& name, int32_t& data)
{
    napi_value value = nullptr;
    napi_get_named_property(env, jsObject, name.c_str(), &value);
    napi_valuetype type = napi_undefined;
    napi_typeof(env, value, &type);
    if (type == napi_number) {
        napi_get_value_int32(env, value, &data);
        return true;
    } else {
        return false;
    }
    return true;
}

static size_t ParseArgs(
    napi_env& env, napi_callback_info& info, napi_value& thisVar, napi_value& cb, CallbackType& callbackType)
{
    size_t argc = ARGC_NUM_SIZE;
    napi_value argv[ARGC_NUM_SIZE] = { 0 };
    napi_get_cb_info(env, info, &argc, argv, &thisVar, nullptr);
    NAPI_ASSERT_BASE(env, argc > 0, "too few parameter", 0);

    napi_valuetype napiType;
    NAPI_CALL_BASE(env, napi_typeof(env, argv[0], &napiType), 0);
    NAPI_ASSERT_BASE(env, napiType == napi_string, "parameter 1 should be string", 0);
    char type[STR_MAX_BUFFER_SIZE] = { 0 };
    size_t len = 0;
    napi_get_value_string_utf8(env, argv[0], type, STR_MAX_BUFFER_SIZE, &len);
    NAPI_ASSERT_BASE(env, len < STR_MAX_BUFFER_SIZE, "condition string too long", 0);
    NAPI_ASSERT_BASE(
        env, (strcmp("frame", type) == 0), "type mismatch('frame')", 0);
    if (strcmp("frame", type) == 0) {
        callbackType = CallbackType::ONFRAME;
    } else {
        callbackType = CallbackType::UNKNOW;
    }

    if (argc <= 1) {
        return argc;
    }

    NAPI_CALL_BASE(env, napi_typeof(env, argv[1], &napiType), 0);
    NAPI_ASSERT_BASE(env, napiType == napi_function, "type mismatch for parameter 2", 0);
    cb = argv[1];
    return argc;
}

DisplaySync* GetDisplaySync(napi_env env, napi_callback_info info)
{
    DisplaySync* displaySync = nullptr;
    napi_value thisVar = nullptr;
    napi_get_cb_info(env, info, nullptr, nullptr, &thisVar, nullptr);
    napi_unwrap(env, thisVar, reinterpret_cast<void**>(&displaySync));
    return displaySync;
}

void CreateTimeInfoJsObject(const napi_env env, RefPtr<DisplaySyncData> displaySyncData,
                            napi_value& intervalInfo)
{
    napi_status status = napi_create_object(env, &intervalInfo);
    if (status != napi_ok) {
        NapiPrintErrorInfo(env);
        return;
    }

    napi_value timestamp;
    napi_value targetTimestamp;
    napi_create_int64(env, displaySyncData->timestamp_, &timestamp);
    napi_create_int64(env, displaySyncData->targetTimestamp_, &targetTimestamp);
    auto resultTimestamp = napi_set_named_property(env, intervalInfo, "timestamp", timestamp);
    auto resultTargetTimestamp = napi_set_named_property(env, intervalInfo, "targetTimestamp", targetTimestamp);
    if (resultTimestamp != napi_ok || resultTargetTimestamp != napi_ok) {
        NapiPrintErrorInfo(env);
        return;
    }
}

napi_value ParseExpectedFrameRateRange(napi_env env, napi_callback_info info, FrameRateRange& frameRateRange)
{
    size_t argc = 1;
    napi_value argv[1];
    napi_value thisVar = nullptr;
    napi_get_cb_info(env, info, &argc, argv, &thisVar, nullptr);
    if (argc != 1) {
        NapiThrow(env, "The number of parameters is incorrect.", ERROR_CODE_PARAM_INVALID);
        return NapiGetUndefined(env);
    }

    napi_value nativeObj = argv[0];
    if (nativeObj == nullptr) {
        NapiThrow(env, "The nativeObj is nullptr.", ERROR_CODE_PARAM_INVALID);
        return NapiGetUndefined(env);
    }

    int32_t minFPS = 0;
    int32_t maxFPS = 0;
    int32_t expectedFPS = 0;
    ParseJsValue(env, nativeObj, "min", minFPS);
    ParseJsValue(env, nativeObj, "max", maxFPS);
    ParseJsValue(env, nativeObj, "expected", expectedFPS);

    frameRateRange.Set(minFPS, maxFPS, expectedFPS);
    if (!frameRateRange.IsValid()) {
        NapiThrow(env, "ExpectedFrameRateRange Error", ERROR_CODE_PARAM_INVALID);
        return NapiGetUndefined(env);
    }
    return NapiGetUndefined(env);
}

napi_value JSSetExpectedFrameRateRange(napi_env env, napi_callback_info info)
{
    FrameRateRange frameRateRange;
    ParseExpectedFrameRateRange(env, info, frameRateRange);

    auto displaySync = GetDisplaySync(env, info);
    if (!displaySync) {
        TAG_LOGW(AceLogTag::ACE_DISPLAY_SYNC, "JSSetExpectedFrameRateRange: cannot find displaySync.");
        return NapiGetUndefined(env);
    }
    RefPtr<UIDisplaySync> uiDisplaySync = displaySync->GetUIDisplaySync();
    if (!uiDisplaySync) {
        TAG_LOGW(AceLogTag::ACE_DISPLAY_SYNC, "JSSetExpectedFrameRateRange: cannot get uiDisplaySync.");
        return NapiGetUndefined(env);
    }

    uiDisplaySync->SetExpectedFrameRateRange(frameRateRange);
    TAG_LOGD(AceLogTag::ACE_DISPLAY_SYNC, "Id: %{public}" PRIu64 " SetExpectedFrameRateRange"
        "{%{public}d, %{public}d, %{public}d}", uiDisplaySync->GetId(), frameRateRange.min_, frameRateRange.max_,
        frameRateRange.preferred_);
    return NapiGetUndefined(env);
}

napi_value JSStart(napi_env env, napi_callback_info info)
{
    auto displaySync = GetDisplaySync(env, info);
    if (!displaySync) {
        TAG_LOGW(AceLogTag::ACE_DISPLAY_SYNC, "JSStart: cannot find displaySync.");
        return NapiGetUndefined(env);
    }
    RefPtr<UIDisplaySync> uiDisplaySync = displaySync->GetUIDisplaySync();
    if (!uiDisplaySync) {
        TAG_LOGW(AceLogTag::ACE_DISPLAY_SYNC, "JSStart: cannot get uiDisplaySync when starting.");
        return NapiGetUndefined(env);
    }

    uiDisplaySync->AddToPipelineOnContainer();
    TAG_LOGD(AceLogTag::ACE_DISPLAY_SYNC, "Id: %{public}" PRIu64 " Start", uiDisplaySync->GetId());
    return NapiGetUndefined(env);
}

napi_value JSStop(napi_env env, napi_callback_info info)
{
    auto displaySync = GetDisplaySync(env, info);
    if (!displaySync) {
        TAG_LOGW(AceLogTag::ACE_DISPLAY_SYNC, "JSStop: cannot find displaySync.");
        return NapiGetUndefined(env);
    }
    RefPtr<UIDisplaySync> uiDisplaySync = displaySync->GetUIDisplaySync();
    if (!uiDisplaySync) {
        TAG_LOGW(AceLogTag::ACE_DISPLAY_SYNC, "JSStop: cannot get uiDisplaySync when stopping.");
        return NapiGetUndefined(env);
    }

    uiDisplaySync->DelFromPipelineOnContainer();
    TAG_LOGD(AceLogTag::ACE_DISPLAY_SYNC, "Id: %{public}" PRIu64 " Stop", uiDisplaySync->GetId());
    return NapiGetUndefined(env);
}

void DisplaySync::Initialize(napi_env env, napi_value thisVar)
{
    napi_handle_scope scope = nullptr;
    napi_open_handle_scope(env, &scope);
    if (!scope) {
        return;
    }
    napi_create_reference(env, thisVar, 1, &thisVarRef_);
    napi_close_handle_scope(env, scope);
}

void DisplaySync::NapiSerializer(napi_env& env, napi_value& jsDisplaySync)
{
    napi_status status = napi_create_object(env, &jsDisplaySync);
    if (status != napi_ok) {
        NapiPrintErrorInfo(env);
        return;
    }

    napi_wrap(
        env, jsDisplaySync, this,
        [](napi_env env, void* data, void* hint) {
            DisplaySync* displaySync = static_cast<DisplaySync*>(data);
            if (displaySync) {
                displaySync->Destroy(env);
                delete displaySync;
            }
        },
        nullptr, nullptr);
}

void DisplaySync::RegisterOnFrameCallback(napi_value cb, napi_ref& onFrameRef,
    CallbackType callbackType, napi_env env)
{
    if (onFrameRef) {
        return;
    }
    napi_create_reference(env, cb, 1, &onFrameRef);

    GetUIDisplaySync()->RegisterOnFrameWithData([env, onFrameRef] (RefPtr<DisplaySyncData> displaySyncData) {
        napi_handle_scope innerScope = nullptr;
        napi_status status = napi_open_handle_scope(env, &innerScope);
        if (status != napi_ok) {
            NapiPrintErrorInfo(env);
            return;
        }

        napi_value ret = nullptr;
        napi_value onframe = nullptr;
        auto result = napi_get_reference_value(env, onFrameRef, &onframe);
        if (result != napi_ok || onframe == nullptr) {
            NapiPrintErrorInfo(env);
            napi_close_handle_scope(env, innerScope);
            return;
        }

        napi_value intervalInfo = nullptr;
        CreateTimeInfoJsObject(env, displaySyncData, intervalInfo);
        napi_value args[CALLBACK_OJECT_NUM] = { intervalInfo };
        napi_call_function(env, nullptr, onframe, CALLBACK_OJECT_NUM, args, &ret);
        napi_close_handle_scope(env, innerScope);
    });
}

void DisplaySync::UnregisterOnFrameCallback(napi_env env, size_t argc, napi_ref& onFrameRef)
{
    if (argc >= 1) {
        napi_delete_reference(env, onFrameRef);
        onFrameRef = nullptr;
        GetUIDisplaySync()->UnregisterOnFrame();
    }
    return;
}

void DisplaySync::Destroy(napi_env env)
{
    if (onFrameRef_ != nullptr) {
        napi_delete_reference(env, onFrameRef_);
    }

    if (thisVarRef_ != nullptr) {
        napi_delete_reference(env, thisVarRef_);
    }
}

napi_value JSOnFrame_On(napi_env env, napi_callback_info info)
{
    napi_value thisVar = nullptr;
    napi_value cb = nullptr;
    CallbackType callbackType = CallbackType::UNKNOW;
    size_t argc = ParseArgs(env, info, thisVar, cb, callbackType);
    NAPI_ASSERT(env, (argc == ARGC_NUM_SIZE && thisVar != nullptr && cb != nullptr), "Invalid arguments");

    DisplaySync* displaySync = GetDisplaySync(env, info);
    if (!displaySync) {
        return NapiGetUndefined(env);
    }

    if (callbackType == CallbackType::ONFRAME) {
        displaySync->RegisterOnFrameCallback(cb, displaySync->onFrameRef_, callbackType, env);
    }
    return NapiGetUndefined(env);
}

napi_value JSOnFrame_Off(napi_env env, napi_callback_info info)
{
    napi_value thisVar = nullptr;
    napi_value cb = nullptr;
    CallbackType callbackType = CallbackType::UNKNOW;
    size_t argc = ParseArgs(env, info, thisVar, cb, callbackType);
    DisplaySync* displaySync = GetDisplaySync(env, info);
    if (!displaySync) {
        return NapiGetUndefined(env);
    }
    if (callbackType == CallbackType::ONFRAME) {
        displaySync->UnregisterOnFrameCallback(env, argc, displaySync->onFrameRef_);
    }
    return NapiGetUndefined(env);
}

static napi_value JSCreate(napi_env env, napi_callback_info info)
{
    auto uiDisplaySync = AceType::MakeRefPtr<UIDisplaySync>();
    DisplaySync* displaySync = new DisplaySync(uiDisplaySync);

    napi_value jsDisplaySync = nullptr;
    displaySync->NapiSerializer(env, jsDisplaySync);
    if (!jsDisplaySync) {
        delete displaySync;
        return nullptr;
    }

    napi_property_descriptor resultFuncs[] = {
        DECLARE_NAPI_FUNCTION("setExpectedFrameRateRange", JSSetExpectedFrameRateRange),
        DECLARE_NAPI_FUNCTION("on", JSOnFrame_On),
        DECLARE_NAPI_FUNCTION("off", JSOnFrame_Off),
        DECLARE_NAPI_FUNCTION("start", JSStart),
        DECLARE_NAPI_FUNCTION("stop", JSStop),
    };

    TAG_LOGD(AceLogTag::ACE_DISPLAY_SYNC, "Create UIDisplaySync Id: %{public}" PRIu64 "",
        uiDisplaySync->GetId());
    NAPI_CALL(env, napi_define_properties(
        env, jsDisplaySync, sizeof(resultFuncs) / sizeof(resultFuncs[0]), resultFuncs));
    return jsDisplaySync;
}

static napi_value DisplaySyncExport(napi_env env, napi_value exports)
{
    napi_property_descriptor displaySyncDesc[] = {
        DECLARE_NAPI_FUNCTION("create", JSCreate),
    };
    NAPI_CALL(env, napi_define_properties(
        env, exports, sizeof(displaySyncDesc) / sizeof(displaySyncDesc[0]), displaySyncDesc));
    return exports;
}

static napi_module displaySyncModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = DisplaySyncExport,
    .nm_modname = "graphics.displaySync",
    .nm_priv = ((void*)0),
    .reserved = { 0 },
};

extern "C" __attribute__((constructor)) void DisplaySyncRegister()
{
    napi_module_register(&displaySyncModule);
}
} // namespace OHOS::Ace::Napi
