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
    DECLARE_ACE_TYPE(CustomDialogControllerPeerImpl, AceType);
public:
    CustomDialogControllerPeerImpl() = default;
    ~CustomDialogControllerPeerImpl() override = default;

    void SetOwnerView(Ark_NativePointer node);
    void SetBuilder(CustomNodeBuilder builder, Ark_NativePointer node);
    void SetOnCancel(Opt_Callback_Void cancel, Ark_NativePointer node);
    void SetAutoCancel(Opt_Boolean autoCancel);
    void SetDialogAlignment(Opt_DialogAlignment alignment);
    void SetOffset(Opt_Offset offset);
    void SetCustomStyle(Opt_Boolean customStyle);
    void SetGridCount(Opt_Number gridCount);
    void SetMaskColor(Opt_ResourceColor maskColor);
    void SetMaskRect(Opt_Rectangle maskRect);
    void SetOpenAnimation(Opt_AnimateParam openAnimation);
    void SetCloseAnimation(Opt_AnimateParam closeAnimation);
    void SetShowInSubWindow(Opt_Boolean showInSubWindow);
    void SetBackgroundColor(Opt_ResourceColor backgroundColor);
    void SetCornerRadius(Opt_Union_Dimension_BorderRadiuses cornerRadius);
    void SetIsModal(Opt_Boolean isModal);
    void SetDismiss(Opt_Callback_DismissDialogAction_Void onWillDismiss);
    void SetWidth(Opt_Length width);
    void SetHeight(Opt_Length height);
    void SetBorderWidth(Opt_Union_Dimension_EdgeWidths borderWidth);
    void SetBorderColor(Opt_Union_ResourceColor_EdgeColors borderColor);
    void SetBorderStyle(Opt_Union_BorderStyle_EdgeStyles borderStyle);
    void SetShadow(Opt_Union_ShadowOptions_ShadowStyle shadow);
    void SetBlurStyle(Opt_BlurStyle backgroundBlurStyle);
    void SetKeyboardAvoidMode(Opt_KeyboardAvoidMode keyboardAvoidMode);
    void SetEnableHoverMode(Opt_Boolean enableHoverMode);
    void SetHoverModeArea(Opt_HoverModeAreaType hoverModeArea);

    DialogProperties GetDialogProperties() const;

    void OpenDialog();
    void CloseDialog();

    void SetInstanceId(int32_t id)
    {
        instanceId_ = id;
    }

private:
    RefPtr<UINode> GetWindowScene() const;

    WeakPtr<FrameNode> ownerView_;
    DialogProperties dialogProperties_;
    std::vector<WeakPtr<AceType>> dialogs_;
    std::function<RefPtr<UINode>()> builder_;
    int32_t instanceId_ = INSTANCE_ID_UNDEFINED;
};
} // namespace OHOS::Ace::NG::GeneratedModifier

struct CustomDialogControllerPeer : public OHOS::Ace::NG::GeneratedModifier::CustomDialogControllerPeerImpl {
    ~CustomDialogControllerPeer() override = default;
};

#endif //FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_CUSTOM_DIALOG_CONTROLLER_PEER_IMPL_H
