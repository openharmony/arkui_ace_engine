/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_CUSTOM_DIALOG_CONTROLLER_PEER_IMPL_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_CUSTOM_DIALOG_CONTROLLER_PEER_IMPL_H

#include "base/memory/ace_type.h"
#include "core/common/container_consts.h"
#include "core/components/dialog/dialog_properties.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG::GeneratedModifier {
class CustomDialogControllerPeerImpl : public virtual AceType {
    DECLARE_ACE_TYPE(CustomDialogControllerPeerImpl, AceType)
public:
    CustomDialogControllerPeerImpl() = default;
    ~CustomDialogControllerPeerImpl() override = default;

    void SetOwnerView(Ark_NativePointer node);
    void SetBuilder(CustomNodeBuilder builder, const RefPtr<CustomDialogControllerPeer>& peer);
    void SetOnCancel(Opt_Callback_Void cancel, const RefPtr<CustomDialogControllerPeer>& peer);
    void SetBuilderExtender(CustomNodeBuilder builder, const RefPtr<CustomDialogControllerExtenderPeer>& peer);
    void SetOnCancelExtender(Opt_Callback_Void cancel, const RefPtr<CustomDialogControllerExtenderPeer>& peer);
    void SetAutoCancel(Opt_Boolean autoCancel);
    void SetDialogAlignment(Opt_DialogAlignment alignment);
    void SetOffset(Opt_Offset offset);
    void SetCustomStyle(Opt_Boolean customStyle);
    Opt_Boolean GetCustomStyle();
    void SetGridCount(Opt_Int32 gridCount);
    void SetMaskColor(Opt_ResourceColor maskColor);
    void SetMaskRect(Opt_Rectangle maskRect);
    void SetOpenAnimation(Opt_AnimateParam openAnimation);
    void SetCloseAnimation(Opt_AnimateParam closeAnimation);
    void SetShowInSubWindow(Opt_Boolean showInSubWindow);
    void SetBackgroundColor(Opt_ResourceColor backgroundColor);
    void SetCornerRadius(Opt_Union_Dimension_BorderRadiuses cornerRadius);
    void SetIsModal(Opt_Boolean isModal);
    void SetDismiss(Opt_Callback_DismissDialogAction_Void onWillDismiss);
    void SetWidth(Opt_Dimension width);
    void SetHeight(Opt_Dimension height);
    void SetBorderWidth(Opt_Union_Dimension_EdgeWidths borderWidth);
    void SetBorderColor(Opt_Union_ResourceColor_EdgeColors borderColor);
    void SetBorderStyle(Opt_Union_BorderStyle_EdgeStyles borderStyle);
    void SetShadow(Opt_Union_ShadowOptions_ShadowStyle shadow);
    void SetBlurStyle(Opt_BlurStyle backgroundBlurStyle);
    void SetKeyboardAvoidMode(Opt_KeyboardAvoidMode keyboardAvoidMode);
    void SetEnableHoverMode(Opt_Boolean enableHoverMode);
    void SetHoverModeArea(Opt_HoverModeAreaType hoverModeArea);
    void SetBackgroundBlurStyleOptions(Opt_BackgroundBlurStyleOptions backgroundBlurStyleOptions);
    void SetBackgroundEffect(Opt_BackgroundEffectOptions backgroundEffect);
    void SetOnDidAppear(Opt_Callback_Void onDidAppear, const RefPtr<CustomDialogControllerPeer>& peer);
    void SetOnDidDisappear(Opt_Callback_Void onDidDisappear, const RefPtr<CustomDialogControllerPeer>& peer);
    void SetOnWillAppear(Opt_Callback_Void onWillAppear, const RefPtr<CustomDialogControllerPeer>& peer);
    void SetOnWillDisappear(Opt_Callback_Void onWillDisappear, const RefPtr<CustomDialogControllerPeer>& peer);
    void SetOnDidAppearExtender(Opt_Callback_Void onDidAppear, const RefPtr<CustomDialogControllerExtenderPeer>& peer);
    void SetOnDidDisappearExtender(Opt_Callback_Void onDidDisappear,
        const RefPtr<CustomDialogControllerExtenderPeer>& peer);
    void SetOnWillAppearExtender(Opt_Callback_Void onWillAppear,
        const RefPtr<CustomDialogControllerExtenderPeer>& peer);
    void SetOnWillDisappearExtender(Opt_Callback_Void onWillDisappear,
        const RefPtr<CustomDialogControllerExtenderPeer>& peer);
    void SetKeyboardAvoidDistance(Opt_LengthMetrics keyboardAvoidDistance);
    void SetLevelMode(Opt_Boolean showInSubWindow, Opt_LevelMode levelMode);
    void SetLevelUniqueId(Opt_Int32 levelUniqueId);
    void SetImersiveMode(Opt_ImmersiveMode immersiveMode);
    void SetLevelOrder(Opt_LevelOrder levelOrder);
    void SetLevelOrderExtender(Opt_LevelOrderExtender levelOrderExtender);
    void SetFocusable(Opt_Boolean focusable);

    DialogProperties GetDialogProperties() const;

    void OpenDialog();
    void CloseDialog();
    PromptActionCommonState GetState();

    void SetInstanceId(int32_t id)
    {
        instanceId_ = id;
    }

    WeakPtr<FrameNode> GetOwnerViewNode()
    {
        return ownerView_;
    }
private:
    RefPtr<UINode> GetWindowScene() const;
    std::function<void()> TransformCallbackToFunctionVoid(
        Opt_Callback_Void callback, const RefPtr<CustomDialogControllerPeer>& peer);
    std::function<void()> TransformCallbackToFunctionVoidExtender(
        Opt_Callback_Void callback, const RefPtr<CustomDialogControllerExtenderPeer>& peer);

    WeakPtr<FrameNode> ownerView_;
    DialogProperties dialogProperties_;
    std::vector<WeakPtr<AceType>> dialogs_;
    std::function<void()> builder_;
    int32_t instanceId_ = INSTANCE_ID_UNDEFINED;
    bool hasBind_ = false;
};
} // namespace OHOS::Ace::NG::GeneratedModifier

struct CustomDialogControllerPeer : public OHOS::Ace::NG::GeneratedModifier::CustomDialogControllerPeerImpl {
    ~CustomDialogControllerPeer() override = default;
};

struct CustomDialogControllerExtenderPeer : public OHOS::Ace::NG::GeneratedModifier::CustomDialogControllerPeerImpl {
    ~CustomDialogControllerExtenderPeer() override = default;
};

#endif //FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_CUSTOM_DIALOG_CONTROLLER_PEER_IMPL_H
