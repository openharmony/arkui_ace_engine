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

#include "core/components/custom_dialog/custom_dialog_element.h"

#include "base/utils/string_utils.h"
#include "core/components/dialog/dialog_component.h"
#include "core/components/stack/stack_element.h"

namespace OHOS::Ace {

void CustomDialogElement::PerformBuild()
{
    RefPtr<CustomDialogComponent> customComponent = AceType::DynamicCast<CustomDialogComponent>(component_);
    if (!customComponent) {
        return;
    }
    dialog_ = customComponent;
    const auto& controller = customComponent->GetDialogController();
    if (!controller) {
        return;
    }
    controller->SetShowDialogImpl([weak = AceType::WeakClaim(this)]() {
        auto dialog = weak.Upgrade();
        if (dialog) {
            dialog->ShowDialog();
        }
    });
    controller->SetCloseDialogImpl([weak = AceType::WeakClaim(this)]() {
        auto dialog = weak.Upgrade();
        if (dialog) {
            dialog->CloseDialog();
        }
    });
}

void CustomDialogElement::ShowDialog()
{
    if (!dialog_) {
        return;
    }
    const auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    auto stackElement = context->GetLastStack();
    if (!stackElement) {
        return;
    }
    DialogProperties dialogProperties;
    const auto& baseDialog = DialogBuilder::Build(dialogProperties, context_);
    baseDialog->SetTextDirection(dialog_->GetTextDirection());
    baseDialog->SetCustomChild(dialog_->GetChild());
    baseDialog->SetOnCancelId(dialog_->GetOnCancel());
    baseDialog->SetHeight(dialog_->GetHeight());
    baseDialog->SetWidth(dialog_->GetWidth());
    if (dialog_->IsSetMargin()) {
        baseDialog->SetMargin(dialog_->GetMargin());
    }
    animator_ = baseDialog->GetAnimator();
    stackElement->PushDialog(baseDialog);
    isPopDialog_ = false;
#if defined(WINDOWS_PLATFORM) || defined(MAC_PLATFORM)
    baseDialog->SetCustomDialogId(StringUtils::StringToInt(GetId()));
    auto mananger = context->GetAccessibilityManager();
    if (mananger) {
        auto node = mananger->GetAccessibilityNodeById(StringUtils::StringToInt(GetId()));
        mananger->ClearNodeRectInfo(node, isPopDialog_);
    }
#endif
}

void CustomDialogElement::CloseDialog()
{
    const auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    const auto& lastStack = context->GetLastStack();
    if (!lastStack) {
        return;
    }
    auto animator = animator_.Upgrade();
    if (animator) {
        animator->AddStopListener([weakStack = AceType::WeakClaim(AceType::RawPtr(lastStack))] {
            auto lastStack = weakStack.Upgrade();
            if (lastStack) {
                lastStack->PopDialog(true);
            }
        });
        animator->Play();
    } else {
        lastStack->PopDialog(true);
    }
    isPopDialog_ = true;
#if defined(WINDOWS_PLATFORM) || defined(MAC_PLATFORM)
    auto manager = context->GetAccessibilityManager();
    if (manager) {
        auto node = manager->GetAccessibilityNodeById(StringUtils::StringToInt(GetId()));
        manager->ClearNodeRectInfo(node, isPopDialog_);
    }
#endif
}

} // namespace OHOS::Ace