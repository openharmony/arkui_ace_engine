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

#include "core/components/container_modal/container_modal_element.h"

#include "core/components/box/box_element.h"
#include "core/components/flex/flex_element.h"
#include "core/components/flex/flex_item_element.h"
#include "core/components/container_modal/render_container_modal.h"

namespace OHOS::Ace {
namespace {

constexpr uint32_t COLUMN_CHILD_MIN = 2;

} // namespace

RefPtr<StackElement> ContainerModalElement::GetStackElement() const
{
    auto containerbox = AceType::DynamicCast<BoxElement>(GetFirstChild());
    if (!containerbox) {
        LOGE("Get stack element failed. Container box element is null!");
        return RefPtr<StackElement>();
    }

    auto column = AceType::DynamicCast<ColumnElement>(containerbox->GetFirstChild());
    if (!column || column->GetChildren().size() < COLUMN_CHILD_MIN) {
        // column should has more than 2 child
        LOGE("Get stack element failed. Column is null or child size error!");
        return RefPtr<StackElement>();
    }

    // Get second child
    auto secondItr = std::next(column->GetChildren().begin());
    auto contentFlexItem = AceType::DynamicCast<FlexItemElement>(*secondItr);
    if (!contentFlexItem) {
        LOGE("Get stack element failed. content flex item element is null!");
        return RefPtr<StackElement>();
    }

    auto contentBox = AceType::DynamicCast<BoxElement>(contentFlexItem->GetFirstChild());
    if (!contentBox) {
        LOGE("Get stack element failed. content box element is null!");
        return RefPtr<StackElement>();
    }

    auto clip = contentBox->GetFirstChild();
    if (!clip) {
        LOGE("Get stack element failed. clip is null!");
        return RefPtr<StackElement>();
    }

    auto stack = clip->GetFirstChild();
    if (!stack || !AceType::InstanceOf<StackElement>(stack)) {
        LOGE("Get stack element failed. stack is null or type error!");
        return RefPtr<StackElement>();
    }

    return AceType::DynamicCast<StackElement>(stack);
}

RefPtr<OverlayElement> ContainerModalElement::GetOverlayElement() const
{
    auto stack = GetStackElement();
    if (!stack) {
        LOGE("Get overlay element failed, stack element is null");
        return RefPtr<OverlayElement>();
    }

    for (auto child : stack->GetChildren()) {
        if (child && AceType::InstanceOf<OverlayElement>(child)) {
            return AceType::DynamicCast<OverlayElement>(child);
        }
    }
    LOGE("Get overlay element failed, all children of stack element do not meet the requirements");
    return RefPtr<OverlayElement>();
}

RefPtr<StageElement> ContainerModalElement::GetStageElement() const
{
    auto stack = GetStackElement();
    if (!stack) {
        LOGE("Get stage element failed, stack element is null");
        return RefPtr<StageElement>();
    }
    for (auto child : stack->GetChildren()) {
        if (child && AceType::InstanceOf<StageElement>(child)) {
            return AceType::DynamicCast<StageElement>(child);
        }
    }
    LOGE("Get stage element failed, all children of stack element do not meet the requirements");
    return RefPtr<StageElement>();
}

} // namespace OHOS::Ace