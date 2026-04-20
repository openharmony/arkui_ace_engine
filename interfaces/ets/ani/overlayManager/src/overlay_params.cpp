/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "overlay_params.h"

#include "ani_utils.h"
#include "core/common/ace_engine.h"
#include "frameworks/base/error/error_code.h"

namespace OHOS::Ace {

bool GetLevelMode(ani_env* env, ani_object object, LevelMode& result)
{
    ani_int resultInt;
    if (!AniUtils::GetEnumInt(env, object, "levelMode", "@ohos.promptAction.LevelMode", resultInt)) {
        return false;
    }
    result = static_cast<LevelMode>(resultInt);
    return true;
}

bool GetOrderOverlayOptions(ani_env* env, ani_object object, NG::OrderOverlayOptions& result)
{
    if (AniUtils::IsUndefinedObject(env, object)) {
        return false;
    }

    if (!AniUtils::IsClassObject(env, object, "@ohos.arkui.UIContext.OrderOverlayOptions")) {
        return false;
    }

    GetLevelMode(env, object, result.levelMode);
    result.levelUniqueId = -1;
    AniUtils::GetInt32Param(env, object, "levelUniqueId", result.levelUniqueId);

    return true;
}

bool GetOrderOverlayOptionsInternal(ani_env* env, ani_object object, NG::OrderOverlayOptions& result)
{
    if (AniUtils::IsUndefinedObject(env, object)) {
        return false;
    }

    if (!AniUtils::IsClassObject(env, object, "@ohos.overlayManager.OrderOverlayOptionsInternal")) {
        return false;
    }

    AniUtils::GetDoubleParamOpt(env, object, "levelOrder", result.levelOrder);
    return true;
}

std::function<void(int32_t)> GetOpenOrderOverlayPromise(std::shared_ptr<OverlayAsyncContext>& asyncContext)
{
    auto callback = [asyncContext](int32_t errorCode) mutable {
        if (!asyncContext) {
            return;
        }

        auto container = AceEngine::Get().GetContainer(asyncContext->instanceId);
        if (!container) {
            return;
        }

        auto taskExecutor = container->GetTaskExecutor();
        if (!taskExecutor) {
            return;
        }

        auto task = [asyncContext, errorCode]() {
            if (!asyncContext || !asyncContext->deferred) {
                return;
            }
            ani_env* env = nullptr;
            ani_status status = asyncContext->vm->GetEnv(ANI_VERSION_1, &env);
            if (status != ANI_OK || env == nullptr) {
                TAG_LOGE(AceLogTag::ACE_OVERLAY, "[ANI] GetEnv fail. status: %{public}d", status);
                return;
            }

            ani_size nrRefs = 16;
            status = env->CreateLocalScope(nrRefs);
            if (status != ANI_OK) {
                TAG_LOGE(AceLogTag::ACE_OVERLAY, "[ANI] CreateLocalScope fail. status: %{public}d", status);
                return;
            }

            if (errorCode == ERROR_CODE_NO_ERROR) {
                ani_ref successRef;
                env->GetUndefined(&successRef);
                status = env->PromiseResolver_Resolve(asyncContext->deferred, successRef);
                if (status != ANI_OK) {
                    TAG_LOGW(AceLogTag::ACE_OVERLAY, "[ANI] PromiseResolver_Resolve fail. status: %{public}d", status);
                }
            } else {
                std::string errorMsg = AniUtils::GetErrorMsg(errorCode);
                ani_error error = AniUtils::GetErrorObject(env, errorMsg, errorCode);
                status = env->PromiseResolver_Reject(asyncContext->deferred, error);
                if (status != ANI_OK) {
                    TAG_LOGW(AceLogTag::ACE_OVERLAY, "[ANI] PromiseResolver_Reject fail. status: %{public}d", status);
                }
            }
            env->DestroyLocalScope();
        };
        taskExecutor->PostTask(std::move(task), TaskExecutor::TaskType::JS, "ArkUIOpenOrderOverlayCallback");
        asyncContext = nullptr;
    };
    return callback;
}

} // namespace OHOS::Ace
