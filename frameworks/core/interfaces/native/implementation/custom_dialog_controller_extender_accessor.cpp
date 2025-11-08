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
namespace CustomDialogControllerExtenderAccessor {
void DestroyPeerImpl(Ark_CustomDialogControllerExtender peer)
{
    CHECK_NULL_VOID(peer);
    peer->DecRefCount();
}
Ark_CustomDialogControllerExtender ConstructImpl(const Ark_CustomDialogControllerOptionsExtender* value)
{
    auto peer = AceType::MakeRefPtr<CustomDialogControllerExtenderPeer>();
    peer->IncRefCount();
    CHECK_NULL_RETURN(value, AceType::RawPtr(peer));
    peer->SetBuilderExtender(value->builder, peer);
    peer->SetOnCancelExtender(value->cancel, peer);
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
    peer->SetOnDidAppearExtender(value->onDidAppear, peer);
    peer->SetOnDidDisappearExtender(value->onDidDisappear, peer);
    peer->SetOnWillAppearExtender(value->onWillAppear, peer);
    peer->SetOnWillDisappearExtender(value->onWillDisappear, peer);
    peer->SetKeyboardAvoidDistance(value->keyboardAvoidDistance);
    peer->SetLevelMode(value->showInSubWindow, value->levelMode);
    peer->SetLevelUniqueId(value->levelUniqueId);
    peer->SetImersiveMode(value->immersiveMode);
    peer->SetLevelOrderExtender(value->levelOrderExtender);
    peer->SetFocusable(value->focusable);

    return AceType::RawPtr(peer);
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void OpenImpl(Ark_CustomDialogControllerExtender peer)
{
    CHECK_NULL_VOID(peer);
    peer->OpenDialog();
}
void CloseImpl(Ark_CustomDialogControllerExtender peer)
{
    CHECK_NULL_VOID(peer);
    peer->CloseDialog();
}
void SetOwnerViewImpl(Ark_CustomDialogControllerExtender peer,
                      Ark_NativePointer content)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(content);
    peer->SetOwnerView(content);
}
Ark_CustomDialogControllerExternalOptionsExtender GetExternalOptionsImpl(Ark_CustomDialogControllerExtender peer)
{
    Ark_CustomDialogControllerExternalOptionsExtender result = {
        .customStyle = Converter::ArkValue<Opt_Boolean>(false),
    };
    CHECK_NULL_RETURN(peer, result);
    result.customStyle = peer->GetCustomStyle();
    return result;
}
} // CustomDialogControllerExtenderAccessor
const GENERATED_ArkUICustomDialogControllerExtenderAccessor* GetCustomDialogControllerExtenderAccessor()
{
    static const GENERATED_ArkUICustomDialogControllerExtenderAccessor CustomDialogControllerExtenderAccessorImpl {
        CustomDialogControllerExtenderAccessor::DestroyPeerImpl,
        CustomDialogControllerExtenderAccessor::ConstructImpl,
        CustomDialogControllerExtenderAccessor::GetFinalizerImpl,
        CustomDialogControllerExtenderAccessor::OpenImpl,
        CustomDialogControllerExtenderAccessor::CloseImpl,
        CustomDialogControllerExtenderAccessor::SetOwnerViewImpl,
        CustomDialogControllerExtenderAccessor::GetExternalOptionsImpl,
    };
    return &CustomDialogControllerExtenderAccessorImpl;
}
}
