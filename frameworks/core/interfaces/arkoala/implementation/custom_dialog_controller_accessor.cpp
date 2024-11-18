/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "core/interfaces/arkoala/implementation/custom_dialog_controller_peer_impl.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace CustomDialogControllerAccessor {
static void DestroyPeer(CustomDialogControllerPeerImpl *peerImpl)
{
    if (peerImpl) {
        peerImpl->DecRefCount();
    }
}
CustomDialogControllerPeer* CtorImpl(const Ark_CustomDialogControllerOptions* value)
{
    auto peerImpl = AceType::MakeRefPtr<CustomDialogControllerPeerImpl>();
    peerImpl->IncRefCount();
    auto result = reinterpret_cast<CustomDialogControllerPeer*>(AceType::RawPtr(peerImpl));
    CHECK_NULL_RETURN(value, result);

    LOGE("CustomDialogControllerAccessor::CtorImpl unsupported options: builder, cancel, onWillDismiss");
    LOGE("CustomDialogControllerAccessor::CtorImpl partially supported options: openAnimation, closeAnimation");

    peerImpl->SetAutoCancel(value->autoCancel);
    peerImpl->SetDialogAlignment(value->alignment);
    peerImpl->SetOffset(value->offset);
    peerImpl->SetCustomStyle(value->customStyle);
    peerImpl->SetGridCount(value->gridCount);
    peerImpl->SetMaskColor(value->maskColor);
    peerImpl->SetMaskRect(value->maskRect);
    peerImpl->SetOpenAnimation(value->openAnimation);
    peerImpl->SetCloseAnimation(value->closeAnimation);
    peerImpl->SetShowInSubWindow(value->showInSubWindow);
    peerImpl->SetBackgroundColor(value->backgroundColor);
    peerImpl->SetCornerRadius(value->cornerRadius);
    peerImpl->SetIsModal(value->isModal);
    peerImpl->SetWidth(value->width);
    peerImpl->SetHeight(value->height);
    peerImpl->SetBorderWidth(value->borderWidth);
    peerImpl->SetBorderColor(value->borderColor);
    peerImpl->SetBorderStyle(value->borderStyle);
    peerImpl->SetShadow(value->shadow);
    peerImpl->SetBlurStyle(value->backgroundBlurStyle);
    peerImpl->SetKeyboardAvoidMode(value->keyboardAvoidMode);
    peerImpl->SetEnableHoverMode(value->enableHoverMode);
    peerImpl->SetHoverModeArea(value->hoverModeArea);

    return result;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeer);
}
void OpenImpl(CustomDialogControllerPeer* peer)
{
    LOGE("CustomDialogControllerAccessor::OpenImpl method is not implemented");
}
void CloseImpl(CustomDialogControllerPeer* peer)
{
    LOGE("CustomDialogControllerAccessor::CloseImpl method is not implemented");
}
} // CustomDialogControllerAccessor
const GENERATED_ArkUICustomDialogControllerAccessor* GetCustomDialogControllerAccessor()
{
    static const GENERATED_ArkUICustomDialogControllerAccessor CustomDialogControllerAccessorImpl {
        CustomDialogControllerAccessor::CtorImpl,
        CustomDialogControllerAccessor::GetFinalizerImpl,
        CustomDialogControllerAccessor::OpenImpl,
        CustomDialogControllerAccessor::CloseImpl,
    };
    return &CustomDialogControllerAccessorImpl;
}

}
