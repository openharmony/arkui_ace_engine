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

#include "toast_params.h"

#include "prompt_action_utils.h"

std::unordered_map<std::string, int> alignmentMap = {
    {"TopStart", 0},
    {"Top", 1},
    {"TopEnd", 2},
    {"Start", 3},
    {"Center", 4},
    {"End", 5},
    {"BottomStart", 6},
    {"Bottom", 7},
    {"BottomEnd", 8}
};

bool GetToastBottom(ani_env* env, ani_object object, std::string& result)
{
    ani_ref resultRef;
    ani_status status = env->Object_GetPropertyByName_Ref(object, "bottom", &resultRef);
    if (status != ANI_OK) {
        return false;
    }

    if (IsUndefinedObject(env, resultRef)) {
        return false;
    }

    if (GetStringParam(env, resultRef, result)) {
        return true;
    }

    double resultDouble;
    if (GetDoubleParam(env, resultRef, resultDouble)) {
        result = std::to_string(resultDouble);
        return true;
    }
    return false;
}

bool GetToastShowMode(ani_env* env, ani_object object, OHOS::Ace::NG::ToastShowMode& result)
{
    int32_t resultInt;
    if (!GetEnumInt(env, object, "showMode", "@ohos.promptAction.promptAction.ToastShowMode", resultInt)) {
        return false;
    }
    result = static_cast<OHOS::Ace::NG::ToastShowMode>(resultInt);
    return true;
}

bool GetToastAlignment(ani_env* env, ani_object object, int32_t& result)
{
    result = -1;
    if (!GetEnumInt(env, object, "alignment", "arkui.component.enums.Alignment", result)) {
        return false;
    }
    return true;
}

bool GetToastShadow(ani_env* env, ani_object object, std::optional<OHOS::Ace::Shadow>& result, bool& isTypeStyleShadow)
{
    ani_ref resultRef;
    ani_status status = env->Object_GetPropertyByName_Ref(object, "shadow", &resultRef);
    if (status != ANI_OK) {
        return false;
    }

    if (IsUndefinedObject(env, resultRef)) {
        return false;
    }

    ani_object resultObj = static_cast<ani_object>(resultRef);
    OHOS::Ace::Shadow shadow;
    if (GetShadowStyleParam(env, resultObj, shadow)) {
        result = std::make_optional<OHOS::Ace::Shadow>(shadow);
        isTypeStyleShadow = true;
        return true;
    }

    if (GetShadowOptionsParam(env, resultObj, shadow)) {
        result = std::make_optional<OHOS::Ace::Shadow>(shadow);
        isTypeStyleShadow = false;
        return true;
    }
    return false;
}

bool GetShowToastOptions(ani_env* env, ani_object object, OHOS::Ace::NG::ToastInfo& result)
{
    if (IsUndefinedObject(env, object)) {
        return false;
    }

    if (!IsClassObject(env, object, "@ohos.promptAction.promptAction.ShowToastOptions")) {
        return false;
    }

    GetResourceStrParam(env, object, "message", result.message);
    double duration = -1.0f;
    GetDoubleParam(env, object, "duration", duration);
    result.duration = static_cast<int32_t>(duration);
    GetToastBottom(env, object, result.bottom);
    GetToastShowMode(env, object, result.showMode);
    GetToastAlignment(env, object, result.alignment);
    GetOffsetParamOpt(env, object, result.offset);
    GetResourceColorParamOpt(env, object, "backgroundColor", result.backgroundColor);
    GetResourceColorParamOpt(env, object, "textColor", result.textColor);
    GetBackgroundBlurStyleParamOpt(env, object, result.backgroundBlurStyle);
    GetToastShadow(env, object, result.shadow, result.isTypeStyleShadow);
    GetBoolParam(env, object, "enableHoverMode", result.enableHoverMode);
    GetHoverModeAreaParam(env, object, result.hoverModeArea);
    return true;
}

std::function<void(int32_t)> GetToastPromise(std::shared_ptr<PromptActionAsyncContext>& asyncContext)
{
    auto callback = [asyncContext](int32_t toastId) mutable {
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

        auto task = [asyncContext, toastId]() {
            if (asyncContext == nullptr || !asyncContext->deferred) {
                return;
            }

            ani_env* env = nullptr;
            ani_status status = asyncContext->vm->GetEnv(ANI_VERSION_1, &env);
            if (status != ANI_OK || env == nullptr) {
                TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DIALOG, "[ANI] GetEnv fail. status: %{public}d", status);
                return;
            }

            ani_size nrRefs = 16;
            status = env->CreateLocalScope(nrRefs);
            if (status != ANI_OK || !nrRefs) {
                TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DIALOG, "[ANI] CreateLocalScope fail. status: %{public}d", status);
                return;
            }

            if (toastId > 0) {
                double returnToastId = static_cast<double>(toastId);
                ani_object toastIdObj = CreateANIDoubleObject(env, returnToastId);
                ani_ref toastRef = static_cast<ani_ref>(toastIdObj);
                status = env->PromiseResolver_Resolve(asyncContext->deferred, toastRef);
                if (status != ANI_OK) {
                    TAG_LOGW(OHOS::Ace::AceLogTag::ACE_DIALOG,
                        "[ANI] PromiseResolver_Resolve fail. status: %{public}d", status);
                }
            } else {
                int32_t errorCode = OHOS::Ace::ERROR_CODE_INTERNAL_ERROR;
                std::string errorMsg = OHOS::Ace::Ani::GetErrorMsg(errorCode);
                ani_error error = OHOS::Ace::Ani::GetErrorObject(env, errorMsg, errorCode);
                status = env->PromiseResolver_Reject(asyncContext->deferred, error);
                if (status != ANI_OK) {
                    TAG_LOGW(OHOS::Ace::AceLogTag::ACE_DIALOG,
                        "[ANI] PromiseResolver_Reject fail. status: %{public}d", status);
                }
            }

            status = env->DestroyLocalScope();
            if (status != ANI_OK) {
                TAG_LOGW(OHOS::Ace::AceLogTag::ACE_DIALOG, "[ANI] DestroyLocalScope fail. status: %{public}d", status);
            }
        };
        taskExecutor->PostTask(
            std::move(task), OHOS::Ace::TaskExecutor::TaskType::JS, "ArkUIDialogParseCustomToastIdCallback");
        asyncContext = nullptr;
    };
    return callback;
}
