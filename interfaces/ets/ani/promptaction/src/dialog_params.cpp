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

#include "dialog_params.h"

#include "frameworks/base/error/error_code.h"
#include "frameworks/core/common/ace_engine.h"

namespace OHOS::Ace::NG {
static const std::unordered_map<int32_t, std::string> ERROR_CODE_TO_MSG {
    { ERROR_CODE_PERMISSION_DENIED, "Permission denied. " },
    { ERROR_CODE_PARAM_INVALID, "Parameter error. " },
    { ERROR_CODE_SYSTEMCAP_ERROR, "Capability not supported. " },
    { ERROR_CODE_INTERNAL_ERROR, "Internal error. " },
    { ERROR_CODE_URI_ERROR, "Uri error. " },
    { ERROR_CODE_PAGE_STACK_FULL, "Page stack error. " },
    { ERROR_CODE_URI_ERROR_LITE, "Uri error. " },
    { ERROR_CODE_DIALOG_CONTENT_ERROR, "Dialog content error. " },
    { ERROR_CODE_DIALOG_CONTENT_ALREADY_EXIST, "Dialog content already exist. " },
    { ERROR_CODE_DIALOG_CONTENT_NOT_FOUND, "Dialog content not found. " },
    { ERROR_CODE_TOAST_NOT_FOUND, "Toast not found. " }
};

std::string ErrorToMessage(int32_t code)
{
    auto iter = ERROR_CODE_TO_MSG.find(code);
    return (iter != ERROR_CODE_TO_MSG.end()) ? iter->second : "";
}

std::string GetErrorMsg(int32_t errorCode)
{
    std::string strMsg;
    if (errorCode == ERROR_CODE_DIALOG_CONTENT_ERROR) {
        strMsg = ErrorToMessage(ERROR_CODE_DIALOG_CONTENT_ERROR) + "The ComponentContent is incorrect.";
    } else if (errorCode == ERROR_CODE_DIALOG_CONTENT_ALREADY_EXIST) {
        strMsg = ErrorToMessage(ERROR_CODE_DIALOG_CONTENT_ALREADY_EXIST) +
            "The ComponentContent has already been opened.";
    } else if (errorCode == ERROR_CODE_DIALOG_CONTENT_NOT_FOUND) {
        strMsg = ErrorToMessage(ERROR_CODE_DIALOG_CONTENT_NOT_FOUND) + "The ComponentContent cannot be found.";
    } else {
        strMsg = ErrorToMessage(ERROR_CODE_INTERNAL_ERROR) + "Build custom dialog failed.";
    }
    return strMsg;
}
} // OHOS::Ace::NG

bool GetButtonInfo(ani_env* env, ani_ref resultRef, OHOS::Ace::ButtonInfo& result)
{
    if (IsUndefinedObject(env, resultRef)) {
        return false;
    }
    ani_object object = static_cast<ani_object>(resultRef);
    return GetButtonInfo(env, object, result);
}

bool GetButtonInfo(ani_env* env, ani_object object, OHOS::Ace::ButtonInfo& result)
{
    if (!IsClassObject(env, object, "L@ohos/promptAction/promptAction/Button;")) {
        return false;
    }
    GetResourceStrParam(env, object, "text", result.text);
    GetResourceStrParam(env, object, "color", result.textColor);
    GetBoolParam(env, object, "primary", result.isPrimary);
    return true;
}

bool GetButtonArray(ani_env *env, ani_object object, const char *name, std::vector<OHOS::Ace::ButtonInfo>& result)
{
    ani_ref resultRef;
    ani_status status = env->Object_GetPropertyByName_Ref(object, name, &resultRef);
    if (status != ANI_OK) {
        return false;
    }

    if (IsUndefinedObject(env, resultRef)) {
        return false;
    }

    ani_double length;
    ani_object resultObj = static_cast<ani_object>(resultRef);
    status = env->Object_GetPropertyByName_Double(resultObj, "length", &length);
    if (status != ANI_OK) {
        return false;
    }

    std::vector<OHOS::Ace::ButtonInfo> buttonArray;
    for (int i = 0; i < int(length); i++) {
        ani_ref itemRef;
        status = env->Object_CallMethodByName_Ref(resultObj, "$_get", "I:Lstd/core/Object;", &itemRef, (ani_int)i);
        if (status != ANI_OK) {
            return false;
        }

        OHOS::Ace::ButtonInfo button;
        ani_object itemObj = static_cast<ani_object>(itemRef);
        if (GetButtonInfo(env, itemObj, button)) {
            buttonArray.emplace_back(button);
        }
    }
    result = buttonArray;
    return true;
}

bool GetMaskRect(ani_env *env, ani_object object, std::optional<OHOS::Ace::DimensionRect>& result)
{
    ani_ref resultRef;
    ani_status status = env->Object_GetPropertyByName_Ref(object, "maskRect", &resultRef);
    if (status != ANI_OK) {
        return false;
    }

    if (IsUndefinedObject(env, resultRef)) {
        return false;
    }

    ani_object resultObj = static_cast<ani_object>(resultRef);
    ani_ref dxRef;
    status = env->Object_GetPropertyByName_Ref(resultObj, "x", &dxRef);
    if (status != ANI_OK) {
        return false;
    }
    OHOS::Ace::CalcDimension dx;
    if (!GetLengthParam(env, dxRef, dx)) {
        return false;
    }

    ani_ref dyRef;
    status = env->Object_GetPropertyByName_Ref(resultObj, "y", &dyRef);
    if (status != ANI_OK) {
        return false;
    }
    OHOS::Ace::CalcDimension dy;
    if (!GetLengthParam(env, dyRef, dy)) {
        return false;
    }

    ani_ref widthRef;
    status = env->Object_GetPropertyByName_Ref(resultObj, "width", &widthRef);
    if (status != ANI_OK) {
        return false;
    }
    OHOS::Ace::CalcDimension width;
    if (!GetLengthParam(env, widthRef, width)) {
        return false;
    }

    ani_ref heightRef;
    status = env->Object_GetPropertyByName_Ref(resultObj, "height", &heightRef);
    if (status != ANI_OK) {
        return false;
    }
    OHOS::Ace::CalcDimension height;
    if (!GetLengthParam(env, heightRef, height)) {
        return false;
    }
    result->SetOffset(OHOS::Ace::DimensionOffset(dx, dy));
    result->SetSize(OHOS::Ace::DimensionSize(width, height));
    return true;
}

bool GetDialogAlignment(ani_env* env, ani_object object, OHOS::Ace::DialogAlignment& result)
{
    int32_t resultInt;
    if (!GetEnumInt(env, object, "alignment", "Larkui/component/alertDialog/DialogAlignment;", resultInt)) {
        return false;
    }
    result = static_cast<OHOS::Ace::DialogAlignment>(resultInt);
    return true;
}

bool GetThemeColorMode(ani_env* env, ani_object object, OHOS::Ace::ThemeColorMode& result)
{
    int32_t resultInt;
    if (!GetEnumInt(env, object, "colorMode", "Larkui/component/common/ThemeColorMode;", resultInt)) {
        return false;
    }
    result = static_cast<OHOS::Ace::ThemeColorMode>(resultInt);
    return true;
}

bool GetAdaptiveColor(ani_env* env, ani_object object, OHOS::Ace::AdaptiveColor& result)
{
    int32_t resultInt;
    if (!GetEnumInt(env, object, "adaptiveColor", "Larkui/component/common/AdaptiveColor;", resultInt)) {
        return false;
    }
    result = static_cast<OHOS::Ace::AdaptiveColor>(resultInt);
    return true;
}

bool GetBlurOptions(ani_env* env, ani_object object, OHOS::Ace::BlurOption& result)
{
    ani_ref resultRef;
    ani_status status = env->Object_GetPropertyByName_Ref(object, "blurOptions", &resultRef);
    if (status != ANI_OK) {
        return false;
    }

    if (IsUndefinedObject(env, resultRef)) {
        return false;
    }

    ani_object resultObj = static_cast<ani_object>(resultRef);
    if (!IsClassObject(env, resultObj, "Larkui/component/common/BlurOptions;")) {
        return false;
    }
    return GetFloatArrayParam(env, resultObj, "grayscale", result.grayscale);
}

bool GetBlurStyleActivePolicy(ani_env* env, ani_object object, OHOS::Ace::BlurStyleActivePolicy& result)
{
    ani_int resultInt;
    if (!GetEnumInt(env, object, "policy", "Larkui/component/common/BlurStyleActivePolicy;", resultInt)) {
        return false;
    }
    result = static_cast<OHOS::Ace::BlurStyleActivePolicy>(resultInt);
    return true;
}

bool GetBackgroundBlurStyleOptions(ani_env* env, ani_object object, std::optional<OHOS::Ace::BlurStyleOption>& result)
{
    ani_ref resultRef;
    ani_status status = env->Object_GetPropertyByName_Ref(object, "backgroundBlurStyleOptions", &resultRef);
    if (status != ANI_OK) {
        return false;
    }

    if (IsUndefinedObject(env, resultRef)) {
        return false;
    }

    ani_object resultObj = static_cast<ani_object>(resultRef);
    if (!IsClassObject(env, resultObj, "Larkui/component/common/BackgroundBlurStyleOptions;")) {
        return false;
    }

    GetThemeColorMode(env, object, result->colorMode);
    GetAdaptiveColor(env, object, result->adaptiveColor);
    GetDoubleParam(env, object, "scale", result->scale);
    GetBlurOptions(env, object, result->blurOption);
    GetBlurStyleActivePolicy(env, object, result->policy);
    GetResourceColorParam(env, object, "inactiveColor", result->inactiveColor);
    return true;
}

bool GetBackgroundEffectOptions(ani_env* env, ani_object object, std::optional<OHOS::Ace::EffectOption>& result)
{
    ani_ref resultRef;
    ani_status status = env->Object_GetPropertyByName_Ref(object, "backgroundEffect", &resultRef);
    if (status != ANI_OK) {
        return false;
    }

    if (IsUndefinedObject(env, resultRef)) {
        return false;
    }

    ani_object resultObj = static_cast<ani_object>(resultRef);
    if (!IsClassObject(env, resultObj, "Larkui/component/common/BackgroundEffectOptions;")) {
        return false;
    }

    ani_ref radiusRef;
    status = env->Object_GetPropertyByName_Ref(object, "backgroundEffect", &radiusRef);
    if (status == ANI_OK) {
        OHOS::Ace::CalcDimension dimension;
        if (GetLengthParam(env, radiusRef, dimension)) {
            result->radius = dimension;
        }
    }

    GetDoubleParam(env, resultObj, "saturation", result->saturation);
    result->saturation = (result->saturation > 0.0f || OHOS::Ace::NearZero(result->saturation)) ?
        result->saturation : 1.0f;
    GetDoubleParam(env, resultObj, "brightness", result->brightness);
    result->brightness = (result->brightness > 0.0f || OHOS::Ace::NearZero(result->brightness)) ?
        result->brightness : 1.0f;
    GetResourceColorParam(env, resultObj, "color", result->color);
    GetAdaptiveColor(env, resultObj, result->adaptiveColor);
    GetBlurOptions(env, resultObj, result->blurOption);
    GetBlurStyleActivePolicy(env, resultObj, result->policy);
    GetResourceColorParam(env, resultObj, "inactiveColor", result->inactiveColor);
    return true;
}

bool GetLevelMode(ani_env* env, ani_object object, OHOS::Ace::LevelMode& result)
{
    ani_int resultInt;
    if (!GetEnumInt(env, object, "levelMode", "L@ohos/promptAction/LevelMode;", resultInt)) {
        return false;
    }
    result = static_cast<OHOS::Ace::LevelMode>(resultInt);
    return true;
}

bool GetImmersiveMode(ani_env* env, ani_object object, OHOS::Ace::ImmersiveMode& result)
{
    ani_int resultInt;
    if (!GetEnumInt(env, object, "immersiveMode", "L@ohos/promptAction/ImmersiveMode;", resultInt)) {
        return false;
    }
    result = static_cast<OHOS::Ace::ImmersiveMode>(resultInt);
    return true;
}

bool GetShowDialogOptions(ani_env* env, ani_object object, OHOS::Ace::DialogProperties& dialogProps)
{
    if (IsUndefinedObject(env, object)) {
        return false;
    }

    if (!IsClassObject(env, object, "L@ohos/promptAction/promptAction/ShowDialogOptions;")) {
        return false;
    }

    GetResourceStrParam(env, object, "title", dialogProps.title);
    GetResourceStrParam(env, object, "message", dialogProps.content);
    GetButtonArray(env, object, "buttons", dialogProps.buttons);
    GetMaskRect(env, object, dialogProps.maskRect);
    GetDialogAlignment(env, object, dialogProps.alignment);
    GetOffsetParam(env, object, dialogProps.offset);
    GetBoolParam(env, object, "showInSubWindow", dialogProps.isShowInSubWindow);
    GetBoolParam(env, object, "isModal", dialogProps.isModal);
    GetResourceColorParamOpt(env, object, "backgroundColor", dialogProps.backgroundColor);
    GetBackgroundBlurStyleParamOpt(env, object, dialogProps.backgroundBlurStyle);
    GetBackgroundBlurStyleOptions(env, object, dialogProps.blurStyleOption);
    GetShadowParamOpt(env, object, dialogProps.shadow);
    GetBoolParam(env, object, "enableHoverMode", dialogProps.enableHoverMode);
    GetHoverModeAreaParamOpt(env, object, dialogProps.hoverModeArea);
    GetFunctionParam(env, object, "onDidAppear", dialogProps.onDidAppear);
    GetFunctionParam(env, object, "onDidDisappear", dialogProps.onDidDisappear);
    GetFunctionParam(env, object, "onWillAppear", dialogProps.onWillAppear);
    GetFunctionParam(env, object, "onWillDisappear", dialogProps.onWillDisappear);
    GetLevelMode(env, object, dialogProps.dialogLevelMode);
    GetInt32Param(env, object, "levelUniqueId", dialogProps.dialogLevelUniqueId);
    GetImmersiveMode(env, object, dialogProps.dialogImmersiveMode);
    return true;
}

ani_ref CreateShowDialogSuccessResponse(ani_env* env, int32_t index)
{
    ani_class responseCls;
    ani_status status = env->FindClass(
        "L@ohos/promptAction/promptAction/ShowDialogSuccessResponseInner;", &responseCls);
    if (status != ANI_OK) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_OVERLAY, "FindClass failed %{public}d", status);
        return nullptr;
    }

    ani_method ctorMethod;
    status = env->Class_FindMethod(responseCls, "<ctor>", nullptr, &ctorMethod);
    if (status != ANI_OK) {
        return nullptr;
    }

    ani_object responseObj;
    status = env->Object_New(responseCls, ctorMethod, &responseObj);
    if (status != ANI_OK) {
        return nullptr;
    }

    ani_int indexInt = static_cast<ani_int>(index);
    status = env->Object_SetPropertyByName_Int(responseObj, "index", indexInt);
    if (status != ANI_OK) {
        return nullptr;
    }
    return reinterpret_cast<ani_ref>(responseObj);
}

std::function<void(int32_t, int32_t)> GetShowDialogCallback(std::shared_ptr<PromptActionAsyncContext>& asyncContext)
{
    auto callback = [asyncContext](int32_t callbackType, int32_t successIndex) mutable {
        if (!asyncContext) {
            return;
        }

        auto container = OHOS::Ace::AceEngine::Get().GetContainer(asyncContext->instanceId);
        if (!container) {
            return;
        }

        auto taskExecutor = container->GetTaskExecutor();
        if (!taskExecutor) {
            return;
        }

        auto task = [asyncContext, successIndex]() {
            if (asyncContext == nullptr) {
                return;
            }

            ani_size nrRefs = 16;
            ani_status status = asyncContext->env->CreateLocalScope(nrRefs);
            if (status != ANI_OK && !nrRefs) {
                return;
            }

            ani_ref reponseRef = CreateShowDialogSuccessResponse(asyncContext->env, successIndex);
            if (reponseRef) {
                status = asyncContext->env->FunctionalObject_Call(asyncContext->callback, 1, &reponseRef, nullptr);
            }
            status = asyncContext->env->DestroyLocalScope();
        };
        taskExecutor->PostTask(
            std::move(task), OHOS::Ace::TaskExecutor::TaskType::JS, "ArkUIDialogParseDialogCallback");
        asyncContext = nullptr;
    };
    return callback;
}

std::function<void(int32_t, int32_t)> GetShowDialogPromise(std::shared_ptr<PromptActionAsyncContext>& asyncContext)
{
    auto callback = [asyncContext](int32_t callbackType, int32_t successIndex) mutable {
        if (!asyncContext) {
            return;
        }

        auto container = OHOS::Ace::AceEngine::Get().GetContainer(asyncContext->instanceId);
        if (!container) {
            return;
        }

        auto taskExecutor = container->GetTaskExecutor();
        if (!taskExecutor) {
            return;
        }

        auto task = [asyncContext, callbackType, successIndex]() {
            if (asyncContext == nullptr) {
                return;
            }

            if (!asyncContext->deferred) {
                return;
            }

            ani_size nrRefs = 16;
            ani_status status = asyncContext->env->CreateLocalScope(nrRefs);
            if (status != ANI_OK && !nrRefs) {
                return;
            }

            if (callbackType == 0) {
                ani_ref responseRef = CreateShowDialogSuccessResponse(asyncContext->env, successIndex);
                status = asyncContext->env->PromiseResolver_Resolve(asyncContext->deferred, responseRef);
                if (status != ANI_OK) {
                    TAG_LOGW(OHOS::Ace::AceLogTag::ACE_DIALOG,
                        "[ANI] PromiseResolver_Resolve fail. status: %{public}d", status);
                }
            } else {
                ani_ref errorRef = CreateBusinessError(asyncContext->env, 0, "cancel");
                ani_error error = static_cast<ani_error>(errorRef);
                status = asyncContext->env->PromiseResolver_Reject(asyncContext->deferred, error);
                if (status != ANI_OK) {
                    TAG_LOGW(OHOS::Ace::AceLogTag::ACE_OVERLAY,
                        "[ANI] PromiseResolver_Reject fail. status: %{public}d", status);
                }
            }
            status = asyncContext->env->DestroyLocalScope();
        };
        taskExecutor->PostTask(
            std::move(task), OHOS::Ace::TaskExecutor::TaskType::JS, "ArkUIDialogParseCustomDialogIdCallback");
        asyncContext = nullptr;
    };
    return callback;
}

bool GetActionMenuOptions(ani_env* env, ani_object object, OHOS::Ace::DialogProperties& dialogProps)
{
    if (IsUndefinedObject(env, object)) {
        return false;
    }

    if (!IsClassObject(env, object, "L@ohos/promptAction/promptAction/ActionMenuOptions;")) {
        return false;
    }

    GetResourceStrParam(env, object, "title", dialogProps.title);
    GetButtonArray(env, object, "buttons", dialogProps.buttons);
    GetBoolParam(env, object, "showInSubWindow", dialogProps.isShowInSubWindow);
    GetBoolParam(env, object, "isModal", dialogProps.isModal);
    GetLevelMode(env, object, dialogProps.dialogLevelMode);
    GetInt32Param(env, object, "levelUniqueId", dialogProps.dialogLevelUniqueId);
    GetImmersiveMode(env, object, dialogProps.dialogImmersiveMode);
    return true;
}

ani_ref CreateActionMenuSuccessResponse(ani_env* env, int32_t index)
{
    ani_class responseCls;
    ani_status status = env->FindClass(
        "L@ohos/promptAction/promptAction/ActionMenuSuccessResponseInner;", &responseCls);
    if (status != ANI_OK) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_OVERLAY, "FindClass failed %{public}d", status);
        return nullptr;
    }

    ani_method ctorMethod;
    status = env->Class_FindMethod(responseCls, "<ctor>", nullptr, &ctorMethod);
    if (status != ANI_OK) {
        return nullptr;
    }

    ani_object responseObj;
    status = env->Object_New(responseCls, ctorMethod, &responseObj);
    if (status != ANI_OK) {
        return nullptr;
    }

    ani_int indexInt = static_cast<ani_int>(index);
    status = env->Object_SetPropertyByName_Int(responseObj, "index", indexInt);
    if (status != ANI_OK) {
        return nullptr;
    }
    return reinterpret_cast<ani_ref>(responseObj);
}

std::function<void(int32_t, int32_t)> GetShowActionMenuCallback(
    std::shared_ptr<PromptActionAsyncContext>& asyncContext)
{
    auto callback = [asyncContext](int32_t callbackType, int32_t successIndex) mutable {
        if (!asyncContext) {
            return;
        }

        auto container = OHOS::Ace::AceEngine::Get().GetContainer(asyncContext->instanceId);
        if (!container) {
            return;
        }

        auto taskExecutor = container->GetTaskExecutor();
        if (!taskExecutor) {
            return;
        }

        auto task = [asyncContext, successIndex]() {
            if (asyncContext == nullptr) {
                return;
            }

            ani_size nrRefs = 16;
            ani_status status = asyncContext->env->CreateLocalScope(nrRefs);
            if (status != ANI_OK && !nrRefs) {
                return;
            }

            ani_ref reponseRef = CreateActionMenuSuccessResponse(asyncContext->env, successIndex);
            if (reponseRef) {
                status = asyncContext->env->FunctionalObject_Call(asyncContext->callback, 1, &reponseRef, nullptr);
            }
            status = asyncContext->env->DestroyLocalScope();
        };
        taskExecutor->PostTask(
            std::move(task), OHOS::Ace::TaskExecutor::TaskType::JS, "ArkUIDialogParseActionMenuCallback");
        asyncContext = nullptr;
    };
    return callback;
}

std::function<void(int32_t, int32_t)> GetShowActionMenuPromise(std::shared_ptr<PromptActionAsyncContext>& asyncContext)
{
    auto callback = [asyncContext](int32_t callbackType, int32_t successIndex) mutable {
        if (!asyncContext) {
            return;
        }

        auto container = OHOS::Ace::AceEngine::Get().GetContainer(asyncContext->instanceId);
        if (!container) {
            return;
        }

        auto taskExecutor = container->GetTaskExecutor();
        if (!taskExecutor) {
            return;
        }

        auto task = [asyncContext, callbackType, successIndex]() {
            if (asyncContext == nullptr) {
                return;
            }

            if (!asyncContext->deferred) {
                return;
            }

            ani_size nrRefs = 16;
            ani_status status = asyncContext->env->CreateLocalScope(nrRefs);
            if (status != ANI_OK && !nrRefs) {
                return;
            }

            if (callbackType == 0) {
                ani_ref responseRef = CreateActionMenuSuccessResponse(asyncContext->env, successIndex);
                status = asyncContext->env->PromiseResolver_Resolve(asyncContext->deferred, responseRef);
                if (status != ANI_OK) {
                    TAG_LOGW(OHOS::Ace::AceLogTag::ACE_DIALOG,
                        "[ANI] PromiseResolver_Resolve fail. status: %{public}d", status);
                }
            } else {
                ani_ref errorRef = CreateBusinessError(asyncContext->env, 0, "cancel");
                ani_error error = static_cast<ani_error>(errorRef);
                status = asyncContext->env->PromiseResolver_Reject(asyncContext->deferred, error);
                if (status != ANI_OK) {
                    TAG_LOGE(OHOS::Ace::AceLogTag::ACE_OVERLAY,
                        "[ANI] PromiseResolver_Reject fail. status: %{public}d", status);
                }
            }
            status = asyncContext->env->DestroyLocalScope();
        };
        taskExecutor->PostTask(
            std::move(task), OHOS::Ace::TaskExecutor::TaskType::JS, "ArkUIDialogParseActionMenuCallback");
        asyncContext = nullptr;
    };
    return callback;
}

bool GetKeyboardAvoidMode(ani_env* env, ani_object object, OHOS::Ace::KeyboardAvoidMode& result)
{
    ani_int resultInt;
    if (!GetEnumInt(env, object, "keyboardAvoidMode", "Larkui/component/common/KeyboardAvoidMode;", resultInt)) {
        return false;
    }
    result = static_cast<OHOS::Ace::KeyboardAvoidMode>(resultInt);
    return true;
}

bool GetKeyboardAvoidDistance(ani_env *env, ani_object object, std::optional<OHOS::Ace::Dimension>& result)
{
    ani_ref resultRef;
    ani_status status = env->Object_GetPropertyByName_Ref(object, "keyboardAvoidDistance", &resultRef);
    if (status != ANI_OK) {
        return false;
    }

    if (IsUndefinedObject(env, resultRef)) {
        return false;
    }

    ani_double value;
    ani_object resultObj = static_cast<ani_object>(resultRef);
    status = env->Object_GetPropertyByName_Double(resultObj, "value", &value);
    if (status != ANI_OK) {
        return false;
    }

    ani_int unit;
    status = env->Object_GetPropertyByName_Int(resultObj, "unit", &unit);
    if (status != ANI_OK) {
        return false;
    }

    auto dimensionUnit = static_cast<OHOS::Ace::DimensionUnit>(unit);
    if (value >= 0.0 && dimensionUnit >= OHOS::Ace::DimensionUnit::PX
        && dimensionUnit <= OHOS::Ace::DimensionUnit::CALC && dimensionUnit != OHOS::Ace::DimensionUnit::PERCENT) {
        OHOS::Ace::Dimension dimension(value, dimensionUnit);
        result = dimension;
    } else {
        OHOS::Ace::Dimension dimension(DEFAULT_AVOID_DISTANCE, OHOS::Ace::DimensionUnit::VP);
        result = dimension;
    }
    return true;
}

bool GetBaseDialogOptions(ani_env* env, ani_object object, OHOS::Ace::DialogProperties& dialogProps)
{
    if (IsUndefinedObject(env, object)) {
        return false;
    }

    if (!IsClassObject(env, object, "L@ohos/promptAction/promptAction/BaseDialogOptions;")) {
        return false;
    }

    GetMaskRect(env, object, dialogProps.maskRect);
    GetDialogAlignment(env, object, dialogProps.alignment);
    GetOffsetParam(env, object, dialogProps.offset);
    GetBoolParam(env, object, "showInSubWindow", dialogProps.isShowInSubWindow);
    GetBoolParam(env, object, "isModal", dialogProps.isModal);
    GetBoolParam(env, object, "autoCancel", dialogProps.autoCancel);
    GetResourceColorParamOpt(env, object, "maskColor", dialogProps.maskColor);
    GetFunctionParam(env, object, "onDidAppear", dialogProps.onDidAppear);
    GetFunctionParam(env, object, "onDidDisappear", dialogProps.onDidDisappear);
    GetFunctionParam(env, object, "onWillAppear", dialogProps.onWillAppear);
    GetFunctionParam(env, object, "onWillDisappear", dialogProps.onWillDisappear);
    GetKeyboardAvoidMode(env, object, dialogProps.keyboardAvoidMode);
    GetBoolParam(env, object, "enableHoverMode", dialogProps.enableHoverMode);
    GetHoverModeAreaParamOpt(env, object, dialogProps.hoverModeArea);
    GetBackgroundBlurStyleOptions(env, object, dialogProps.blurStyleOption);
    GetBackgroundEffectOptions(env, object, dialogProps.effectOption);
    GetKeyboardAvoidDistance(env, object, dialogProps.keyboardAvoidDistance);
    GetLevelMode(env, object, dialogProps.dialogLevelMode);
    GetInt32Param(env, object, "levelUniqueId", dialogProps.dialogLevelUniqueId);
    GetImmersiveMode(env, object, dialogProps.dialogImmersiveMode);
    GetBoolParam(env, object, "focusable", dialogProps.focusable);
    return true;
}

bool GetCustomBuilder(ani_env *env, ani_object object, std::function<void()>& result)
{
    ani_ref resultRef;
    ani_status status = env->Object_GetPropertyByName_Ref(object, "builder", &resultRef);
    if (status != ANI_OK) {
        return false;
    }

    if (IsUndefinedObject(env, resultRef)) {
        return false;
    }

    result = [env, resultRef]() {
        if (resultRef) {
            ani_fn_object resultFunc = static_cast<ani_fn_object>(resultRef);
            env->FunctionalObject_Call(resultFunc, 0, nullptr, nullptr);
        }
    };
    return true;
}

bool GetCornerRadius(ani_env *env, ani_object object, std::optional<OHOS::Ace::NG::BorderRadiusProperty>& result)
{
    ani_ref resultRef;
    ani_status status = env->Object_GetPropertyByName_Ref(object, "cornerRadius", &resultRef);
    if (status != ANI_OK) {
        return false;
    }

    if (IsUndefinedObject(env, resultRef)) {
        return false;
    }

    OHOS::Ace::CalcDimension dimension;
    if (GetDimesionParam(env, resultRef, dimension)) {
        CheckDimension(dimension);
        result = OHOS::Ace::NG::BorderRadiusProperty(dimension);
        return true;
    }

    ani_object resultObj = static_cast<ani_object>(resultRef);
    OHOS::Ace::CalcDimension topLeft;
    if (GetDimesionParam(env, resultObj, "topLeft", topLeft)) {
        CheckDimension(topLeft);
        result->radiusTopLeft = topLeft;
    }

    OHOS::Ace::CalcDimension topRight;
    if (GetDimesionParam(env, resultObj, "topRight", topRight)) {
        CheckDimension(topRight);
        result->radiusTopRight = topRight;
    }

    OHOS::Ace::CalcDimension bottomLeft;
    if (GetDimesionParam(env, resultObj, "bottomLeft", bottomLeft)) {
        CheckDimension(bottomLeft);
        result->radiusBottomLeft = bottomLeft;
    }

    OHOS::Ace::CalcDimension bottomRight;
    if (GetDimesionParam(env, resultObj, "bottomRight", bottomRight)) {
        CheckDimension(bottomRight);
        result->radiusBottomRight = bottomRight;
    }
    result->multiValued = true;
    return true;
}

bool GetBorderWidth(ani_env *env, ani_object object, std::optional<OHOS::Ace::NG::BorderWidthProperty>& result)
{
    ani_ref resultRef;
    ani_status status = env->Object_GetPropertyByName_Ref(object, "borderWidth", &resultRef);
    if (status != ANI_OK) {
        return false;
    }

    if (IsUndefinedObject(env, resultRef)) {
        return false;
    }

    OHOS::Ace::CalcDimension dimension;
    if (GetDimesionParam(env, resultRef, dimension)) {
        CheckDimension(dimension);
        result = OHOS::Ace::NG::BorderWidthProperty({ dimension, dimension, dimension, dimension });
        return true;
    }

    ani_object resultObj = static_cast<ani_object>(resultRef);
    OHOS::Ace::CalcDimension left;
    if (GetDimesionParam(env, resultObj, "left", left)) {
        CheckDimension(left);
        result->leftDimen = left;
    }

    OHOS::Ace::CalcDimension right;
    if (GetDimesionParam(env, resultObj, "right", right)) {
        CheckDimension(left);
        result->rightDimen = right;
    }

    OHOS::Ace::CalcDimension top;
    if (GetDimesionParam(env, resultObj, "top", top)) {
        CheckDimension(top);
        result->topDimen = top;
    }

    OHOS::Ace::CalcDimension bottom;
    if (GetDimesionParam(env, resultObj, "bottom", bottom)) {
        CheckDimension(bottom);
        result->bottomDimen = bottom;
    }
    result->multiValued = true;
    return true;
}

bool GetBorderColor(ani_env *env, ani_object object, std::optional<OHOS::Ace::NG::BorderColorProperty>& result)
{
    ani_ref resultRef;
    ani_status status = env->Object_GetPropertyByName_Ref(object, "borderColor", &resultRef);
    if (status != ANI_OK) {
        return false;
    }

    if (IsUndefinedObject(env, resultRef)) {
        return false;
    }

    ani_object resultObj = static_cast<ani_object>(resultRef);
    OHOS::Ace::Color color;
    if (GetResourceColorParam(env, resultObj, color)) {
        result->SetColor(color);
        return true;
    }

    OHOS::Ace::Color left;
    if (GetResourceColorParam(env, resultObj, "left", left)) {
        result->leftColor = left;
    }

    OHOS::Ace::Color right;
    if (GetResourceColorParam(env, resultObj, "right", right)) {
        result->rightColor = right;
    }

    OHOS::Ace::Color top;
    if (GetResourceColorParam(env, resultObj, "top", top)) {
        result->topColor = top;
    }

    OHOS::Ace::Color bottom;
    if (GetResourceColorParam(env, resultObj, "bottom", bottom)) {
        result->bottomColor = bottom;
    }
    result->multiValued = true;
    return true;
}

bool GetBorderStyle(ani_env* env, ani_object object, OHOS::Ace::BorderStyle& result)
{
    ani_int resultInt;
    if (!GetEnumInt(env, object, "Larkui/component/enums/BorderStyle;", resultInt)) {
        return false;
    }
    result = static_cast<OHOS::Ace::BorderStyle>(resultInt);
    return true;
}

bool GetBorderStyle(ani_env* env, ani_object object, const char *name, OHOS::Ace::BorderStyle& result)
{
    ani_int resultInt;
    if (!GetEnumInt(env, object, name, "Larkui/component/enums/BorderStyle;", resultInt)) {
        return false;
    }
    result = static_cast<OHOS::Ace::BorderStyle>(resultInt);
    return true;
}

bool GetBorderStyle(ani_env *env, ani_object object, std::optional<OHOS::Ace::NG::BorderStyleProperty>& result)
{
    ani_ref resultRef;
    ani_status status = env->Object_GetPropertyByName_Ref(object, "borderStyle", &resultRef);
    if (status != ANI_OK) {
        return false;
    }

    if (IsUndefinedObject(env, resultRef)) {
        return false;
    }

    ani_object resultObj = static_cast<ani_object>(resultRef);
    OHOS::Ace::BorderStyle style;
    if (GetBorderStyle(env, resultObj, style)) {
        result = OHOS::Ace::NG::BorderStyleProperty({ style, style, style, style });
        return true;
    }

    OHOS::Ace::BorderStyle left;
    if (GetBorderStyle(env, resultObj, "left", left)) {
        result->styleLeft = left;
    }

    OHOS::Ace::BorderStyle right;
    if (GetBorderStyle(env, resultObj, "right", right)) {
        result->styleRight = right;
    }

    OHOS::Ace::BorderStyle top;
    if (GetBorderStyle(env, resultObj, "top", top)) {
        result->styleTop = top;
    }

    OHOS::Ace::BorderStyle bottom;
    if (GetBorderStyle(env, resultObj, "bottom", bottom)) {
        result->styleBottom = bottom;
    }
    result->multiValued = true;
    return true;
}

bool GetCustomDialogOptions(ani_env* env, ani_object object, OHOS::Ace::DialogProperties& dialogProps)
{
    if (!GetBaseDialogOptions(env, object, dialogProps)) {
        return false;
    }

    if (!IsClassObject(env, object, "L@ohos/promptAction/promptAction/CustomDialogOptions;")) {
        return false;
    }

    GetCustomBuilder(env, object, dialogProps.customBuilder);
    GetResourceColorParamOpt(env, object, "backgroundColor", dialogProps.backgroundColor);
    GetCornerRadius(env, object, dialogProps.borderRadius);
    GetDimesionParamOpt(env, object, "width", dialogProps.width);
    GetDimesionParamOpt(env, object, "height", dialogProps.height);
    GetBorderWidth(env, object, dialogProps.borderWidth);
    GetBorderColor(env, object, dialogProps.borderColor);
    GetBorderStyle(env, object, dialogProps.borderStyle);
    GetBackgroundBlurStyleParamOpt(env, object, dialogProps.backgroundBlurStyle);
    GetShadowParamOpt(env, object, dialogProps.shadow);
    return true;
}

std::function<void(int32_t)> GetOpenCustomDialogPromise(std::shared_ptr<PromptActionAsyncContext>& asyncContext)
{
    auto callback = [asyncContext](int32_t dialogId) mutable {
        if (!asyncContext) {
            return;
        }

        auto container = OHOS::Ace::AceEngine::Get().GetContainer(asyncContext->instanceId);
        if (!container) {
            return;
        }

        auto taskExecutor = container->GetTaskExecutor();
        if (!taskExecutor) {
            return;
        }

        auto task = [asyncContext, dialogId]() {
            if (asyncContext == nullptr) {
                return;
            }

            if (!asyncContext->deferred) {
                return;
            }

            ani_size nrRefs = 16;
            asyncContext->env->CreateLocalScope(nrRefs);
            if (!nrRefs) {
                return;
            }

            if (dialogId > 0) {
                ani_ref dialogIdRef = reinterpret_cast<ani_ref>(dialogId);
                ani_status status = asyncContext->env->PromiseResolver_Resolve(asyncContext->deferred, dialogIdRef);
                if (status != ANI_OK) {
                    TAG_LOGW(OHOS::Ace::AceLogTag::ACE_DIALOG, "[ANI] PromiseResolver_Resolve fail.");
                }
            } else {
                std::string strMsg = OHOS::Ace::NG::GetErrorMsg(dialogId);
                ani_ref errorRef = CreateBusinessError(asyncContext->env, dialogId, strMsg);
                ani_error error = static_cast<ani_error>(errorRef);
                ani_status status = asyncContext->env->PromiseResolver_Reject(asyncContext->deferred, error);
                if (status != ANI_OK) {
                    TAG_LOGW(OHOS::Ace::AceLogTag::ACE_DIALOG, "[ANI] PromiseResolver_Reject fail.");
                }
            }
            asyncContext->env->DestroyLocalScope();
        };
        taskExecutor->PostTask(
            std::move(task), OHOS::Ace::TaskExecutor::TaskType::JS, "ArkUIDialogParseCustomDialogIdCallback");
        asyncContext = nullptr;
    };
    return callback;
}
