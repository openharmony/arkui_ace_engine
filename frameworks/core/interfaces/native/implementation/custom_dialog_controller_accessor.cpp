/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/implementation/custom_dialog_controller_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace CustomDialogControllerAccessor {
void DestroyPeerImpl(Ark_CustomDialogController peer)
{
    CHECK_NULL_VOID(peer);
    peer->DecRefCount();
}
Ark_CustomDialogController ConstructImpl(const Ark_CustomDialogControllerOptions* value)
{
    auto peer = AceType::MakeRefPtr<CustomDialogControllerPeer>();
    peer->IncRefCount();
    CHECK_NULL_RETURN(value, AceType::RawPtr(peer));

#ifdef WRONG_GEN
    peer->SetBuilder(value->builder, peer);
#endif
    peer->SetOnCancel(value->cancel, peer);
    peer->SetAutoCancel(value->autoCancel);
    peer->SetDialogAlignment(value->alignment);
    peer->SetOffset(value->offset);
    peer->SetCustomStyle(value->customStyle);
    peer->SetGridCount(value->gridCount);
    peer->SetMaskColor(value->maskColor);
    peer->SetMaskRect(value->maskRect);
    peer->SetOpenAnimation(value->openAnimation);
    peer->SetCloseAnimation(value->closeAnimation);
    peer->SetShowInSubWindow(value->showInSubWindow);
    peer->SetBackgroundColor(value->backgroundColor);
    peer->SetCornerRadius(value->cornerRadius);
    peer->SetIsModal(value->isModal);
    peer->SetDismiss(value->onWillDismiss);
    peer->SetWidth(value->width);
    peer->SetHeight(value->height);
    peer->SetBorderWidth(value->borderWidth);
    peer->SetBorderColor(value->borderColor);
    peer->SetBorderStyle(value->borderStyle);
    peer->SetShadow(value->shadow);
    peer->SetBlurStyle(value->backgroundBlurStyle);
    peer->SetKeyboardAvoidMode(value->keyboardAvoidMode);
    peer->SetEnableHoverMode(value->enableHoverMode);
    peer->SetHoverModeArea(value->hoverModeArea);
    peer->SetBackgroundBlurStyleOptions(value->backgroundBlurStyleOptions);
    peer->SetBackgroundEffect(value->backgroundEffect);
    peer->SetOnDidAppear(value->onDidAppear, peer);
    peer->SetOnDidDisappear(value->onDidDisappear, peer);
    peer->SetOnWillAppear(value->onWillAppear, peer);
    peer->SetOnWillDisappear(value->onWillDisappear, peer);
    peer->SetKeyboardAvoidDistance(value->keyboardAvoidDistance);
    peer->SetLevelMode(value->showInSubWindow, value->levelMode);
    peer->SetLevelUniqueId(value->levelUniqueId);
    peer->SetImersiveMode(value->immersiveMode);
    peer->SetLevelOrder(value->levelOrder);
    peer->SetFocusable(value->focusable);

    return AceType::RawPtr(peer);
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void OpenImpl(Ark_CustomDialogController peer)
{
    CHECK_NULL_VOID(peer);
    peer->OpenDialog();
}
void CloseImpl(Ark_CustomDialogController peer)
{
    CHECK_NULL_VOID(peer);
    peer->CloseDialog();
}
Ark_CustomDialogControllerExternalOptions GetExternalOptionsImpl(Ark_CustomDialogController peer)
{
    Ark_CustomDialogControllerExternalOptions result = {
        .customStyle = Converter::ArkValue<Opt_Boolean>(false),
    };
    CHECK_NULL_RETURN(peer, result);
    result.customStyle = peer->GetCustomStyle();
    return result;
}
Ark_promptAction_CommonState GetStateImpl(Ark_CustomDialogController peer)
{
    CHECK_NULL_RETURN(peer, {});
    auto state = peer->GetState();
    return Converter::ArkValue<Ark_promptAction_CommonState>(state);
}
void SetOwnerViewImpl(Ark_CustomDialogController peer, Ark_NodeHandle node)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(node);
    peer->SetOwnerView(node);
}
} // CustomDialogControllerAccessor
const GENERATED_ArkUICustomDialogControllerAccessor* GetCustomDialogControllerAccessor()
{
    static const GENERATED_ArkUICustomDialogControllerAccessor CustomDialogControllerAccessorImpl {
        CustomDialogControllerAccessor::DestroyPeerImpl,
        CustomDialogControllerAccessor::ConstructImpl,
        CustomDialogControllerAccessor::GetFinalizerImpl,
        CustomDialogControllerAccessor::OpenImpl,
        CustomDialogControllerAccessor::CloseImpl,
        CustomDialogControllerAccessor::GetExternalOptionsImpl,
        CustomDialogControllerAccessor::GetStateImpl,
    };
    return &CustomDialogControllerAccessorImpl;
}
}
