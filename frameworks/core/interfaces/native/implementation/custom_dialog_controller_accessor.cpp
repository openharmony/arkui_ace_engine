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
Ark_CustomDialogController CtorImpl(const Ark_CustomDialogControllerOptions* value)
{
    auto peer = AceType::MakeRefPtr<CustomDialogControllerPeer>();
    peer->IncRefCount();
    CHECK_NULL_RETURN(value, AceType::RawPtr(peer));

    LOGE("CustomDialogControllerAccessor::CtorImpl. There is no a frame node for SetOwnerView.");
    peer->SetOwnerView(nullptr);
    LOGE("CustomDialogControllerAccessor::CtorImpl. There is no a frame node for SetBuilder.");
    // Call peer->SetBuilder with value->builder and frameNode if it possible.
    LOGE("CustomDialogControllerAccessor::CtorImpl. There is no a frame node for SetOnCancel.");
    peer->SetOnCancel(value->cancel, nullptr);
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
} // CustomDialogControllerAccessor
const GENERATED_ArkUICustomDialogControllerAccessor* GetCustomDialogControllerAccessor()
{
    static const GENERATED_ArkUICustomDialogControllerAccessor CustomDialogControllerAccessorImpl {
        CustomDialogControllerAccessor::DestroyPeerImpl,
        CustomDialogControllerAccessor::CtorImpl,
        CustomDialogControllerAccessor::GetFinalizerImpl,
        CustomDialogControllerAccessor::OpenImpl,
        CustomDialogControllerAccessor::CloseImpl,
    };
    return &CustomDialogControllerAccessorImpl;
}
}
