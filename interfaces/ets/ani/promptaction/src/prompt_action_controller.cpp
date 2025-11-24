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

#include "frameworks/core/components_ng/pattern/overlay/dialog_manager_static.h"
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

PromptActionCommonState PromptActionDialogController::GetState()
{
    PromptActionCommonState state = PromptActionCommonState::UNINITIALIZED;
    if (node_.Invalid()) {
        if (hasBind_) {
            return PromptActionCommonState::DISAPPEARED;
        }
        return state;
    }
    auto dialogNode = node_.Upgrade();
    CHECK_NULL_RETURN(dialogNode, state);
    auto pattern = dialogNode->GetPattern<NG::DialogPattern>();
    CHECK_NULL_RETURN(pattern, state);
    state = pattern->GetState();
    return state;
}

ani_long ANICreateDialogController(ani_env* env, ani_object object)
{
    static const char *className = "@ohos.promptAction.promptAction.DialogController";
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

ani_enum_item ANIDialogControllerGetState(ani_env* env, ani_object object)
{
    ani_enum_item enumItem = nullptr;
    ani_enum enumType;
    ani_status status = env->FindEnum("@ohos.promptAction.promptAction.CommonState", &enumType);
    if (status != ANI_OK) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_OVERLAY, "CommonState FindEnum fail. status: %{public}d", status);
        return enumItem;
    }
    ani_long nativePtr;
    status = env->Object_GetFieldByName_Long(object, "nativePtr", &nativePtr);
    if (status != ANI_OK) {
        return enumItem;
    }
    auto dialogController = reinterpret_cast<PromptActionDialogController*>(nativePtr);
    CHECK_NULL_RETURN(dialogController, enumItem);
    auto state = dialogController->GetState();
    status = env->Enum_GetEnumItemByIndex(enumType, static_cast<ani_size>(state), &enumItem);
    if (status != ANI_OK) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_OVERLAY, "Get EnumItem fail. status: %{public}d", status);
        return enumItem;
    }
    return enumItem;
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
    static const char *className = "@ohos.promptAction.promptAction.DialogController";
    ani_class cls;
    ani_status status = env->FindClass(className, &cls);
    if (status != ANI_OK) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DIALOG, "DialogController FindClass fail. status: %{public}d", status);
        return ANI_ERROR;
    }

    std::array methods = {
        ani_native_function {"createPtr", nullptr, reinterpret_cast<void *>(ANICreateDialogController)},
        ani_native_function {"close", nullptr, reinterpret_cast<void *>(ANICloseDialog)},
        ani_native_function {"getState", nullptr, reinterpret_cast<void *>(ANIDialogControllerGetState)},
    };
    status = env->Class_BindNativeMethods(cls, methods.data(), methods.size());
    if (status != ANI_OK) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DIALOG, "DialogController BindMethods fail. status: %{public}d", status);
        return ANI_ERROR;
    }

    static const char *cleanerName = "@ohos.promptAction.promptAction.Cleaner";
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

static void CreateCommonController(ani_env* env, ani_object object)
{
    TAG_LOGD(OHOS::Ace::AceLogTag::ACE_OVERLAY, "[ANI] CreateCommonController.");
}

static void CommonControllerClose(ani_env* env, ani_object object)
{
    TAG_LOGD(OHOS::Ace::AceLogTag::ACE_OVERLAY, "[ANI] CommonControllerClose.");
}

static ani_enum_item CommonControllerGetState(ani_env* env, ani_object object)
{
    ani_enum_item enumItem = nullptr;
    ani_enum enumType;
    ani_status status = env->FindEnum("@ohos.promptAction.promptAction.CommonState", &enumType);
    if (status != ANI_OK) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_OVERLAY, "CommonState FindEnum fail. status: %{public}d", status);
        return enumItem;
    }

    status = env->Enum_GetEnumItemByName(enumType, "UNINITIALIZED", &enumItem);
    if (status != ANI_OK) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_OVERLAY, "Get UNINITIALIZED fail. status: %{public}d", status);
        return enumItem;
    }
    return enumItem;
}

ani_status BindCommonController(ani_env* env)
{
    ani_class commonControllerCls;
    ani_status status = env->FindClass("@ohos.promptAction.promptAction.CommonController", &commonControllerCls);
    if (status != ANI_OK) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_OVERLAY, "CommonController FindClass fail. status: %{public}d", status);
        return ANI_ERROR;
    }

    std::array commonControllerMethods = {
        ani_native_function { "<ctor>", ":", reinterpret_cast<void*>(CreateCommonController) },
        ani_native_function { "close", nullptr, reinterpret_cast<void*>(CommonControllerClose) },
        ani_native_function { "getState", nullptr, reinterpret_cast<void*>(CommonControllerGetState) },
    };
    status = env->Class_BindNativeMethods(
        commonControllerCls, commonControllerMethods.data(), commonControllerMethods.size());
    if (status != ANI_OK) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_OVERLAY, "CommonController BindMethods fail. status: %{public}d", status);
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

void DismissDialogAction::Dismiss()
{
    int32_t instanceId = Container::CurrentIdSafely();
    if (instanceId_ != INSTANCE_ID_UNDEFINED) {
        instanceId = instanceId_;
    }
    NG::DialogManagerStatic::RemoveCustomDialog(instanceId_);
}

void ANIDismissDialog(ani_env* env, ani_object object)
{
    ani_long nativePtr;
    ani_status status = env->Object_GetFieldByName_Long(object, "nativePtr", &nativePtr);
    if (status != ANI_OK) {
        return;
    }

    auto dismissDialogAction = reinterpret_cast<DismissDialogAction *>(nativePtr);
    CHECK_NULL_VOID(dismissDialogAction);
    dismissDialogAction->Dismiss();
}

ani_status BindDismissDialogAction(ani_env* env)
{
    static const char *className = "@ohos.promptAction.DismissDialogActionInner";
    ani_class cls;
    ani_status status = env->FindClass(className, &cls);
    if (status != ANI_OK) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DIALOG, "DismissDialogAction FindClass fail. status: %{public}d", status);
        return ANI_ERROR;
    }

    std::array methods = {
        ani_native_function {"dismiss", nullptr, reinterpret_cast<void *>(ANIDismissDialog)},
    };
    status = env->Class_BindNativeMethods(cls, methods.data(), methods.size());
    if (status != ANI_OK) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DIALOG, "DismissDialogAction BindMethods fail. status: %{public}d", status);
        return ANI_ERROR;
    }
    return ANI_OK;
}

ani_object ANICreateDismissDialogAction(ani_env* env, const int32_t reason, const int32_t instanceId)
{
    ani_object result = {};
    static const char *className = "@ohos.promptAction.DismissDialogActionInner";
    ani_class cls;
    ani_status status = env->FindClass(className, &cls);
    if (status != ANI_OK) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DIALOG, "DismissDialogAction FindClass fail. status: %{public}d", status);
        return result;
    }

    ani_method ctor;
    status = env->Class_FindMethod(cls, "<ctor>", nullptr, &ctor);
    if (status != ANI_OK) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DIALOG, "DismissDialogAction FindMethod fail. status: %{public}d", status);
        return result;
    }

    auto dismissDialogAction = new DismissDialogAction();
    dismissDialogAction->SetInstanceId(instanceId);
    ani_long nativePtr = reinterpret_cast<ani_long>(dismissDialogAction);
    status = env->Object_New(cls, ctor, &result, nativePtr);
    if (status != ANI_OK) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DIALOG, "DismissDialogAction NewObject fail. status: %{public}d", status);
        delete dismissDialogAction;
        return result;
    }

    ani_enum enumType;
    status = env->FindEnum("arkui.component.common.DismissReason", &enumType);
    if (status != ANI_OK) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DIALOG, "DismissReason FindEnum fail. status: %{public}d", status);
        return result;
    }

    ani_enum_item enumItem;
    status = env->Enum_GetEnumItemByIndex(enumType, ani_size(reason), &enumItem);
    if (status != ANI_OK) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DIALOG, "DismissReason GetEnumItem fail. status: %{public}d", status);
        return result;
    }

    status = env->Object_SetPropertyByName_Ref(result, "reason", static_cast<ani_ref>(enumItem));
    if (status != ANI_OK) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DIALOG, "DismissDialogAction SetReason fail. status: %{public}d", status);
        return result;
    }
    return result;
}

} // OHOS::Ace::Ani
