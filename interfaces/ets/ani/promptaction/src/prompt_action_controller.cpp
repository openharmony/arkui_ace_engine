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
#include <cstddef>
#include <string>

#include "prompt_action_controller.h"
#include "prompt_action_params.h"

#include "frameworks/core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::Ani {

void PromptActionDialogController::Close()
{
    if (node_.Invalid()) {
        return;
    }
    auto dialogNode = node_.Upgrade();
    CHECK_NULL_VOID(dialogNode);
    auto pipeline = dialogNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto overlayManager = pipeline->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    overlayManager->CloseDialog(dialogNode);
}

ani_long ANICreateDialogController(ani_env* env, ani_object object)
{
    static const char *className = "L@ohos/promptAction/promptAction/DialogController;";
    ani_class cls;
    ani_status status = env->FindClass(className, &cls);
    if (status != ANI_OK) {
        return (ani_long)0;
    }

    PromptActionDialogController* dialogController = new PromptActionDialogController();
    return reinterpret_cast<ani_long>(dialogController);
}

void ANICloseDialog(ani_env* env, ani_object object)
{
    ani_long nativePtr;
    ani_status status = env->Object_GetFieldByName_Long(object, "nativePtr", &nativePtr);
    if (status != ANI_OK) {
        return;
    }

    auto dialogController = reinterpret_cast<PromptActionDialogController *>(nativePtr);
    CHECK_NULL_VOID(dialogController);
    dialogController->Close();
}

void ANICleanDialogController(ani_env* env, ani_object object)
{
    ani_long ptr;
    ani_status status = env->Object_GetFieldByName_Long(object, "ptr", &ptr);
    if (status != ANI_OK) {
        return;
    }
    delete reinterpret_cast<PromptActionDialogController *>(ptr);
}

ani_status BindDialogController(ani_env* env)
{
    static const char *className = "L@ohos/promptAction/promptAction/DialogController;";
    ani_class cls;
    ani_status status = env->FindClass(className, &cls);
    if (status != ANI_OK) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DIALOG, "DialogController FindClass fail. status: %{public}d", status);
        return ANI_ERROR;
    }

    std::array methods = {
        ani_native_function {"createPtr", nullptr, reinterpret_cast<void *>(ANICreateDialogController)},
        ani_native_function {"close", nullptr, reinterpret_cast<void *>(ANICloseDialog)},
    };
    status = env->Class_BindNativeMethods(cls, methods.data(), methods.size());
    if (status != ANI_OK) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DIALOG, "DialogController BindMethods fail. status: %{public}d", status);
        return ANI_ERROR;
    }

    static const char *cleanerName = "L@ohos/promptAction/promptAction/Cleaner;";
    ani_class cleanerCls;
    status = env->FindClass(cleanerName, &cleanerCls);
    if (status != ANI_OK) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DIALOG, "Cleaner FindClass fail. status: %{public}d", status);
        return ANI_ERROR;
    }

    std::array cleanerMethods = {
        ani_native_function {"clean", nullptr, reinterpret_cast<void *>(ANICleanDialogController)},
    };
    status = env->Class_BindNativeMethods(cleanerCls, cleanerMethods.data(), cleanerMethods.size());
    if (status != ANI_OK) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DIALOG, "Cleaner BindMethods fail. status: %{public}d", status);
        return ANI_ERROR;
    }
    return ANI_OK;
}

bool GetDialogController(ani_env* env, ani_object object,
    std::function<void(RefPtr<NG::FrameNode> dialogNode)>& result)
{
    if (IsUndefinedObject(env, object)) {
        return false;
    }

    ani_long nativePtr;
    ani_status status = env->Object_GetFieldByName_Long(object, "nativePtr", &nativePtr);
    if (status != ANI_OK) {
        return false;
    }

    auto dialogController = reinterpret_cast<PromptActionDialogController *>(nativePtr);
    CHECK_NULL_RETURN(dialogController, false);
    result = [dialogController](RefPtr<NG::FrameNode> dialogNode) {
        if (dialogController) {
            dialogController->SetNode(dialogNode);
        }
    };
    return true;
}

} // OHOS::Ace::Ani
