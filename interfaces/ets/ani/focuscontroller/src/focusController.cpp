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
#include <optional>

#include "base/log/log_wrapper.h"
#include "base/memory/referenced.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/bridge/common/utils/engine_helper.h"
#include "frameworks/core/common/container.h"
#include "frameworks/base/error/error_code.h"

namespace {
static void AniThrow(ani_env* env, const std::string& errMsg, int32_t errorCode)
{
    CHECK_NULL_VOID(env);
    ani_class errCls;
    if (ANI_OK != env->FindClass("L@ohos/base/BusinessError", &errCls)) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_FOCUS, "FindClass BusinessError failed.");
        return;
    }
    ani_method errCtor {};
    if (ANI_OK != env->Class_FindMethod(errCls, "<ctor>", "C{std.core.String}C{escompat.ErrorOptions}:", &errCtor)) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_FOCUS, "FindMethod escompat.Error failed.");
        return;
    }
    ani_string resultString {};
    if (ANI_OK != env->String_NewUTF8(errMsg.c_str(), errMsg.size(), &resultString)) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_FOCUS, "Convert string to ani string failed.");
        return;
    }
    ani_ref undefinedRef {};
    if (ANI_OK != env->GetUndefined(&undefinedRef)) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_FOCUS, "Get undefined failed.");
        return;
    }
    ani_object errObj {};
    if (ANI_OK != env->Object_New(errCls, errCtor, &errObj, resultString, undefinedRef)) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_FOCUS, "Create ani error object failed.");
        return;
    }
    if (ANI_OK != env->Object_SetFieldByName_Int(errObj, "code", static_cast<ani_int>(errorCode))) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_FOCUS, "Set error code failed.");
        return;
    }
    if (ANI_OK != env->Object_SetFieldByName_Ref(errObj, "message", resultString)) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_FOCUS, "Set error message failed.");
        return;
    }
    if (ANI_OK != env->ThrowError(static_cast<ani_error>(errObj))) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_FOCUS, "Throw ani error object failed.");
        return;
    }
}
std::string ANIUtils_ANIStringToStdString(ani_env* env, ani_string ani_str)
{
    ani_size strSize;
    env->String_GetUTF8Size(ani_str, &strSize);

    std::vector<char> buffer(strSize + 1); // +1 for null terminator
    char* utf8Buffer = buffer.data();

    ani_size bytes_written = 0;
    env->String_GetUTF8(ani_str, utf8Buffer, strSize + 1, &bytes_written);

    utf8Buffer[bytes_written] = '\0';
    std::string content = std::string(utf8Buffer);
    return content;
}
} // namespace

static bool GetBooleanValue(ani_env* env, ani_object object, bool& value)
{
    ani_boolean isUndefined;
    env->Reference_IsUndefined(object, &isUndefined);
    if (isUndefined) {
        return false;
    }
    ani_boolean aniValue;
    if (ANI_OK != env->Object_CallMethodByName_Boolean(object, "toBoolean", ":z", &aniValue)) {
        return false;
    }
    value = static_cast<bool>(aniValue);
    return true;
}

static void clearFocus(ani_env* env, [[maybe_unused]] ani_object object)
{
    OHOS::Ace::NG::FocusHub::LostFocusToViewRoot();
}

static void requestFocus([[maybe_unused]] ani_env* env, ani_string key)
{
    auto keyStr = ANIUtils_ANIStringToStdString(env, key);
    std::optional<OHOS::Ace::NG::RequestFocusResult> result;
    auto focusCallback = [env, &result](OHOS::Ace::NG::RequestFocusResult requestResult) {
        result = requestResult;
    };
    LOGI("focuscontroller requestFocus key %{public}s", keyStr.c_str());
    auto pipeline = OHOS::Ace::NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto focusManager = pipeline->GetOrCreateFocusManager();
    CHECK_NULL_VOID(focusManager);
    focusManager->SetRequestFocusCallback(focusCallback);
    pipeline->RequestFocus(keyStr, true);
    focusManager->ResetRequestFocusCallback();

    if (result.has_value()) {
        switch (result.value()) {
            case OHOS::Ace::NG::RequestFocusResult::NON_FOCUSABLE:
                AniThrow(env, "This component is not focusable.",
                    OHOS::Ace::ERROR_CODE_NON_FOCUSABLE);
                break;
            case OHOS::Ace::NG::RequestFocusResult::NON_FOCUSABLE_ANCESTOR:
                AniThrow(env, "This component has unfocusable ancestor.",
                    OHOS::Ace::ERROR_CODE_NON_FOCUSABLE_ANCESTOR);
                break;
            case OHOS::Ace::NG::RequestFocusResult::NON_EXIST:
                AniThrow(env, "The component doesn't exist, is currently invisible, or has been disabled.",
                    OHOS::Ace::ERROR_CODE_NON_EXIST);
                break;
            default:
                AniThrow(env, "An internal error occurred.",
                    OHOS::Ace::ERROR_CODE_INTERNAL_ERROR);
                break;
        }
    }
}

static void activate(ani_env* env, ani_boolean isActive, ani_object autoInactive)
{
    bool isActiveValue = static_cast<bool>(isActive);
    bool autoInactiveValue = true;

    GetBooleanValue(env, autoInactive, autoInactiveValue);

    auto pipeline = OHOS::Ace::NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetIsFocusActive(isActiveValue, OHOS::Ace::NG::FocusActiveReason::USE_API, autoInactiveValue);
}

static void setAutoFocusTransfer(ani_env* env, ani_boolean isAutoFocusTransfer)
{
    bool isAutoFocusTransferValue = static_cast<bool>(isAutoFocusTransfer);
    auto pipeline = OHOS::Ace::NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto focusManager = pipeline->GetOrCreateFocusManager();
    CHECK_NULL_VOID(focusManager);
    focusManager->SetIsAutoFocusTransfer(isAutoFocusTransferValue);
}

static void setKeyProcessingMode(ani_env* env, ani_enum_item mode)
{
    ani_int keyProcessingMode;
    if (ANI_OK != env->EnumItem_GetValue_Int(mode, &keyProcessingMode)) {
        LOGE("focuscontroller setKeyProcessingMode get modeType failed");
        return;
    }
    auto pipeline = OHOS::Ace::NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto focusManager = pipeline->GetOrCreateFocusManager();
    CHECK_NULL_VOID(focusManager);
    focusManager->SetKeyProcessingMode(static_cast<OHOS::Ace::NG::KeyProcessingMode>(keyProcessingMode));
}

ANI_EXPORT ani_status ANI_Constructor(ani_vm* vm, uint32_t* result)
{
    if (vm == nullptr) {
        return ANI_ERROR;
    }
    ani_env* env;
    if (ANI_OK != vm->GetEnv(ANI_VERSION_1, &env)) {
        return ANI_ERROR;
    }

    ani_namespace ns;
    if (ANI_OK != env->FindNamespace("@ohos.arkui.focusController.focusController", &ns)) {
        return ANI_ERROR;
    }
    std::array methods = {
        ani_native_function { "clearFocus", nullptr, reinterpret_cast<void*>(clearFocus) },
        ani_native_function { "requestFocus", nullptr, reinterpret_cast<void*>(requestFocus) },
        ani_native_function { "activate", nullptr, reinterpret_cast<void*>(activate) },
        ani_native_function { "setAutoFocusTransfer", nullptr, reinterpret_cast<void*>(setAutoFocusTransfer) },
        ani_native_function { "setKeyProcessingMode", nullptr, reinterpret_cast<void*>(setKeyProcessingMode) },
    };
    if (ANI_OK != env->Namespace_BindNativeFunctions(ns, methods.data(), methods.size())) {
        return ANI_ERROR;
    }

    *result = ANI_VERSION_1;
    return ANI_OK;
}
