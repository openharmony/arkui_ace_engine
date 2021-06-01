/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/components/popup/popup_element.h"

#include "base/utils/string_utils.h"
#include "core/components/box/render_box.h"
#include "core/components/bubble/bubble_component.h"
#include "core/components/stack/stack_element.h"

namespace OHOS::Ace {

void PopupElement::PerformBuild()
{
    RefPtr<PopupComponent> popupComponent = AceType::DynamicCast<PopupComponent>(component_);
    if (!popupComponent) {
        return;
    }
    popup_ = popupComponent;
    const auto& popupController = popupComponent->GetPopupController();
    if (!popupController) {
        return;
    }
    popupController->SetShowPopupImpl([weak = WeakClaim(this)]() {
        auto popupElement = weak.Upgrade();
        if (popupElement) {
            popupElement->ShowPopup();
        }
    });
    popupController->SetCancelPopupImpl([weak = WeakClaim(this)]() {
        auto popupElement = weak.Upgrade();
        if (popupElement) {
            popupElement->CancelPopup();
        }
    });
}

void PopupElement::ShowPopup()
{
    if (!popup_) {
        return;
    }

    const auto context = context_.Upgrade();
    if (!context) {
        return;
    }

    if (popup_->GetPopupParam()->GetTargetId().empty()) {
        return;
    }

    RefPtr<BubbleComponent> bubble = AceType::MakeRefPtr<BubbleComponent>(popup_->GetChild());
    bubble->SetPopupParam(popup_->GetPopupParam());
    bubble->SetId(popup_->GetId());
    bubble->SetDisabledStatus(popup_->IsDisabledStatus());

    auto stackElement = context->GetLastStack();
    if (!stackElement) {
        return;
    }
    weakStack_ = WeakClaim(RawPtr(stackElement));
    bubble->SetWeakStack(weakStack_);
    stackElement->PushComponent(bubble, false, false);
}

void PopupElement::CancelPopup()
{
    auto stackElement = weakStack_.Upgrade();
    if (!stackElement) {
        return;
    }
    stackElement->PopPopup(GetId());

    auto context = context_.Upgrade();
    if (context) {
        const auto& accessibilityManager = context->GetAccessibilityManager();
        if (accessibilityManager) {
            accessibilityManager->RemoveAccessibilityNodeById(StringUtils::StringToInt(popup_->GetId()));
        }
    }
}

} // namespace OHOS::Ace