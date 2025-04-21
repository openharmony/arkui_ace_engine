/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#include "native_interface.h"
#include "node/animate_impl.h"
#include "node/dialog_model.h"
#include "node/gesture_impl.h"
#include "node/node_model.h"
#include "node_extened.h"

#include "base/log/log_wrapper.h"

namespace {

constexpr int32_t CURRENT_NATIVE_NODE_API_VERSION = 1;
constexpr int32_t NATIVE_DIALOG_VERSION_0 = 0;
constexpr int32_t NATIVE_DIALOG_VERSION_1 = 1;
constexpr int32_t NATIVE_DIALOG_VERSION_2 = 2;
constexpr int32_t NATIVE_DIALOG_VERSION_3 = 3;

ArkUI_NativeNodeAPI_Compatible nodeImpl_compatible = {
    CURRENT_NATIVE_NODE_API_VERSION,
    OHOS::Ace::NodeModel::CreateNode,
    OHOS::Ace::NodeModel::DisposeNode,
    OHOS::Ace::NodeModel::AddChild,
    OHOS::Ace::NodeModel::RemoveChild,
    OHOS::Ace::NodeModel::InsertChildAfter,
    OHOS::Ace::NodeModel::InsertChildBefore,
    OHOS::Ace::NodeModel::InsertChildAt,
    OHOS::Ace::NodeModel::SetAttribute,
    OHOS::Ace::NodeModel::GetAttribute,
    OHOS::Ace::NodeModel::ResetAttribute,
    OHOS::Ace::NodeModel::RegisterNodeEvent,
    OHOS::Ace::NodeModel::UnregisterNodeEvent,
    OHOS::Ace::NodeModel::RegisterOnEvent,
    OHOS::Ace::NodeModel::UnregisterOnEvent,
    OHOS::Ace::NodeModel::MarkDirty,
};

ArkUI_NativeNodeAPI_1 nodeImpl_1 = {
    CURRENT_NATIVE_NODE_API_VERSION,
    OHOS::Ace::NodeModel::CreateNode,
    OHOS::Ace::NodeModel::DisposeNode,
    OHOS::Ace::NodeModel::AddChild,
    OHOS::Ace::NodeModel::RemoveChild,
    OHOS::Ace::NodeModel::InsertChildAfter,
    OHOS::Ace::NodeModel::InsertChildBefore,
    OHOS::Ace::NodeModel::InsertChildAt,
    OHOS::Ace::NodeModel::SetAttribute,
    OHOS::Ace::NodeModel::GetAttribute,
    OHOS::Ace::NodeModel::ResetAttribute,
    OHOS::Ace::NodeModel::RegisterNodeEvent,
    OHOS::Ace::NodeModel::UnregisterNodeEvent,
    OHOS::Ace::NodeModel::RegisterOnEvent,
    OHOS::Ace::NodeModel::UnregisterOnEvent,
    OHOS::Ace::NodeModel::MarkDirty,
    OHOS::Ace::NodeModel::GetTotalChildCount,
    OHOS::Ace::NodeModel::GetChildAt,
    OHOS::Ace::NodeModel::GetFirstChild,
    OHOS::Ace::NodeModel::GetLastChild,
    OHOS::Ace::NodeModel::GetPreviousSibling,
    OHOS::Ace::NodeModel::GetNextSibling,
    OHOS::Ace::NodeModel::RegisterNodeCustomEvent,
    OHOS::Ace::NodeModel::UnregisterNodeCustomEvent,
    OHOS::Ace::NodeModel::RegisterNodeCustomReceiver,
    OHOS::Ace::NodeModel::UnregisterNodeCustomEventReceiver,
    OHOS::Ace::NodeModel::SetMeasuredSize,
    OHOS::Ace::NodeModel::SetLayoutPosition,
    OHOS::Ace::NodeModel::GetMeasuredSize,
    OHOS::Ace::NodeModel::GetLayoutPosition,
    OHOS::Ace::NodeModel::MeasureNode,
    OHOS::Ace::NodeModel::LayoutNode,
    OHOS::Ace::NodeModel::AddNodeEventReceiver,
    OHOS::Ace::NodeModel::RemoveNodeEventReceiver,
    OHOS::Ace::NodeModel::AddNodeCustomEventReceiver,
    OHOS::Ace::NodeModel::RemoveNodeCustomEventReceiver,
    OHOS::Ace::NodeModel::SetUserData,
    OHOS::Ace::NodeModel::GetUserData,
    OHOS::Ace::NodeModel::SetLengthMetricUnit,
    OHOS::Ace::NodeModel::GetParent,
    OHOS::Ace::NodeModel::RemoveAllChildren,
};

ArkUI_NativeDialogAPI_1 dialogImpl_1 = {
    OHOS::Ace::DialogModel::Create,
    OHOS::Ace::DialogModel::Dispose,
    OHOS::Ace::DialogModel::SetContent,
    OHOS::Ace::DialogModel::RemoveContent,
    OHOS::Ace::DialogModel::SetContentAlignment,
    OHOS::Ace::DialogModel::ResetContentAlignment,
    OHOS::Ace::DialogModel::SetModalMode,
    OHOS::Ace::DialogModel::SetAutoCancel,
    OHOS::Ace::DialogModel::SetMask,
    OHOS::Ace::DialogModel::SetBackgroundColor,
    OHOS::Ace::DialogModel::SetCornerRadius,
    OHOS::Ace::DialogModel::SetGridColumnCount,
    OHOS::Ace::DialogModel::EnableCustomStyle,
    OHOS::Ace::DialogModel::EnableCustomAnimation,
    OHOS::Ace::DialogModel::RegisterOnWillDismiss,
    OHOS::Ace::DialogModel::Show,
    OHOS::Ace::DialogModel::Close,
    OHOS::Ace::DialogModel::RegisterOnWillDismissWithUserData,
};

ArkUI_NativeDialogAPI_2 dialogImpl_2 = {
    dialogImpl_1,
    OHOS::Ace::DialogModel::SetKeyboardAvoidDistance,
    OHOS::Ace::DialogModel::SetLevelMode,
    OHOS::Ace::DialogModel::SetLevelUniqueId,
    OHOS::Ace::DialogModel::SetImmersiveMode,
};

ArkUI_NativeDialogAPI_3 dialogImpl_3 = {
    dialogImpl_1,
    dialogImpl_2,
    OHOS::Ace::DialogModel::SetLevelOrder,
    OHOS::Ace::DialogModel::RegisterOnWillAppear,
    OHOS::Ace::DialogModel::RegisterOnDidAppear,
    OHOS::Ace::DialogModel::RegisterOnWillDisappear,
    OHOS::Ace::DialogModel::RegisterOnDidDisappear,
    OHOS::Ace::DialogModel::SetBorderWidth,
    OHOS::Ace::DialogModel::SetBorderColor,
    OHOS::Ace::DialogModel::SetBorderStyle,
    OHOS::Ace::DialogModel::SetWidth,
    OHOS::Ace::DialogModel::SetHeight,
    OHOS::Ace::DialogModel::SetShadow,
    OHOS::Ace::DialogModel::SetCustomShadow,
    OHOS::Ace::DialogModel::SetBackgroundBlurStyle,
    OHOS::Ace::DialogModel::SetKeyboardAvoidMode,
    OHOS::Ace::DialogModel::EnableHoverMode,
    OHOS::Ace::DialogModel::SetHoverModeArea,
    OHOS::Ace::DialogModel::SetFocusable,
    OHOS::Ace::DialogModel::SetBackgroundBlurStyleOptions,
    OHOS::Ace::DialogModel::SetBackgroundEffect,
};

constexpr int32_t CURRENT_NATIVE_GESTURE_API_VERSION = 1;
ArkUI_NativeGestureAPI_1 gestureImpl_1 = {
    CURRENT_NATIVE_GESTURE_API_VERSION,
    OHOS::Ace::GestureModel::CreateTapGesture,
    OHOS::Ace::GestureModel::CreateLongPressGesture,
    OHOS::Ace::GestureModel::CreatePanGesture,
    OHOS::Ace::GestureModel::CreatePinchGesture,
    OHOS::Ace::GestureModel::CreateRotationGesture,
    OHOS::Ace::GestureModel::CreateSwipeGesture,
    OHOS::Ace::GestureModel::CreateGroupGesture,
    OHOS::Ace::GestureModel::DisposeGesture,
    OHOS::Ace::GestureModel::AddChildGesture,
    OHOS::Ace::GestureModel::RemoveChildGesture,
    OHOS::Ace::GestureModel::SetGestureEventTarget,
    OHOS::Ace::GestureModel::AddGestureToNode,
    OHOS::Ace::GestureModel::RemoveGestureFromNode,
    OHOS::Ace::GestureModel::SetGestureInterrupterToNode,
    OHOS::Ace::GestureModel::GetGestureType,
    OHOS::Ace::GestureModel::SetInnerGestureParallelTo,
    OHOS::Ace::GestureModel::CreateTapGestureWithDistanceThreshold,
};

ArkUI_NativeGestureAPI_2 gestureImpl_2 = {
    &gestureImpl_1,
    OHOS::Ace::GestureModel::SetGestureInterrupterToNodeWithUserData,  
};

ArkUI_NativeAnimateAPI_1 animateImpl_1 = {
    OHOS::Ace::AnimateModel::AnimateTo,
    OHOS::Ace::AnimateModel::KeyframeAnimateTo,
    OHOS::Ace::AnimateModel::CreateAnimator,
    OHOS::Ace::AnimateModel::DisposeAnimator,
};

} // namespace

#ifdef __cplusplus
extern "C" {
#endif

void* OH_ArkUI_QueryModuleInterface(ArkUI_NativeAPIVariantKind type, int32_t version)
{
    if (!OHOS::Ace::NodeModel::InitialFullImpl()) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_NATIVE_NODE,
            "fail to get %{public}d node api family of %{public}d version, impl library is not found", type, version);
        return nullptr;
    }
    switch (type) {
        case ARKUI_NATIVE_NODE: {
            switch (version) {
                case 0:
                case 1:
                    return &nodeImpl_compatible;
                default: {
                    TAG_LOGE(OHOS::Ace::AceLogTag::ACE_NATIVE_NODE,
                        "fail to get basic node api family, version is incorrect: %{public}d", version);
                    return nullptr;
                }
            }
            break;
        }
        case ARKUI_NATIVE_DIALOG: {
            switch (version) {
                case NATIVE_DIALOG_VERSION_0:
                case NATIVE_DIALOG_VERSION_1:
                    return &dialogImpl_1;
                case NATIVE_DIALOG_VERSION_2:
                    return &dialogImpl_2;
                case NATIVE_DIALOG_VERSION_3:
                    return &dialogImpl_3;
                default: {
                    TAG_LOGE(OHOS::Ace::AceLogTag::ACE_NATIVE_NODE,
                        "fail to get dialog api family, version is incorrect: %{public}d", version);
                    return nullptr;
                }
            }
        }
        case ARKUI_NATIVE_GESTURE: {
            switch (version) {
                case 0:
                case 1:
                    return &gestureImpl_1;
                case 2:
                    return &gestureImpl_2;
                default: {
                    TAG_LOGE(OHOS::Ace::AceLogTag::ACE_NATIVE_NODE,
                        "fail to get gesture api family, version is incorrect: %{public}d", version);
                    return nullptr;
                }
            }
            break;
        }
        default: {
            TAG_LOGE(OHOS::Ace::AceLogTag::ACE_NATIVE_NODE,
                "fail to get %{public}d node api family, version is incorrect: %{public}d", type, version);
            return nullptr;
        }
    }
}

void* OH_ArkUI_GetNativeAPI(ArkUI_NativeAPIVariantKind type, int32_t version)
{
    return OH_ArkUI_QueryModuleInterface(type, version);
}

void* OH_ArkUI_QueryModuleInterfaceByName(ArkUI_NativeAPIVariantKind type, const char* structName)
{
    if (!OHOS::Ace::NodeModel::InitialFullImpl()) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_NATIVE_NODE,
            "fail to get %{public}d node api family, impl library is not found", type);
        return nullptr;
    }
    switch (type) {
        case ARKUI_NATIVE_NODE:
            if (strcmp(structName, "ArkUI_NativeNodeAPI_1") == 0) {
                return &nodeImpl_1;
            }
            break;
        case ARKUI_NATIVE_DIALOG:
            if (strcmp(structName, "ArkUI_NativeDialogAPI_1") == 0) {
                return &dialogImpl_1;
            } else if (strcmp(structName, "ArkUI_NativeDialogAPI_2") == 0) {
                return &dialogImpl_2;
            } else if (strcmp(structName, "ArkUI_NativeDialogAPI_3") == 0) {
                return &dialogImpl_3;
            }
            break;
        case ARKUI_NATIVE_GESTURE:
            if (strcmp(structName, "ArkUI_NativeGestureAPI_1") == 0) {
                return &gestureImpl_1;
            } else if (strcmp(structName, "ArkUI_NativeGestureAPI_2") == 0) {
                return &gestureImpl_2;
            }
            break;
        case ARKUI_NATIVE_ANIMATE:
            if (strcmp(structName, "ArkUI_NativeAnimateAPI_1") == 0) {
                return &animateImpl_1;
            }
            break;
        default:
            break;
    }
    return nullptr;
}

#ifdef __cplusplus
};
#endif
