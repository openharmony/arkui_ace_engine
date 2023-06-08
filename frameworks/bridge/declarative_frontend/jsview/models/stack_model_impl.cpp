/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/models/stack_model_impl.h"

#include "base/memory/referenced.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {

void StackModelImpl::Create()
{
    Alignment alignment = Alignment::CENTER;
    std::list<RefPtr<Component>> children;
    RefPtr<StackComponent> component =
        AceType::MakeRefPtr<StackComponent>(alignment, StackFit::KEEP, Overflow::OBSERVABLE, children);
    ViewStackProcessor::GetInstance()->ClaimElementId(component);
    ViewStackProcessor::GetInstance()->Push(component);
    JSInteractableView::SetFocusNode(true);
}

void StackModelImpl::Create(Alignment alignment)
{
    std::list<RefPtr<Component>> children;
    RefPtr<StackComponent> component =
        AceType::MakeRefPtr<StackComponent>(alignment, StackFit::KEEP, Overflow::OBSERVABLE, children);
    ViewStackProcessor::GetInstance()->ClaimElementId(component);
    ViewStackProcessor::GetInstance()->Push(component);
    JSInteractableView::SetFocusNode(true);
}

void StackModelImpl::SetStackFit(StackFit fit)
{
    auto stack = AceType::DynamicCast<StackComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (stack) {
        stack->SetStackFit(fit);
    }
}

void StackModelImpl::SetOverflow(Overflow overflow)
{
    auto stack = AceType::DynamicCast<StackComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (stack) {
        stack->SetOverflow(overflow);
    }
}

void StackModelImpl::SetAlignment(Alignment alignment)
{
    auto stack = AceType::DynamicCast<StackComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (stack) {
        stack->SetAlignment(alignment);
    }
}

void StackModelImpl::SetHasWidth()
{
    auto stack = AceType::DynamicCast<StackComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (stack) {
        if (stack->GetMainStackSize() == MainStackSize::MAX || stack->GetMainStackSize() == MainStackSize::MAX_Y) {
            stack->SetMainStackSize(MainStackSize::MAX);
        } else {
            stack->SetMainStackSize(MainStackSize::MAX_X);
        }
    }
}

void StackModelImpl::SetHasHeight()
{
    auto stack = AceType::DynamicCast<StackComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (stack) {
        if (stack->GetMainStackSize() == MainStackSize::MAX || stack->GetMainStackSize() == MainStackSize::MAX_X) {
            stack->SetMainStackSize(MainStackSize::MAX);
        } else {
            stack->SetMainStackSize(MainStackSize::MAX_Y);
        }
    }
}

} // namespace OHOS::Ace::Framework
