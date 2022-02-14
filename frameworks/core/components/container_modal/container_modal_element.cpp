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
#include "core/components/container_modal/render_container_modal.h"
#include "core/components/flex/flex_element.h"
#include "core/components/flex/flex_item_element.h"

namespace OHOS::Ace {
namespace {

constexpr uint32_t COLUMN_CHILD_NUM = 2;

} // namespace

RefPtr<StackElement> ContainerModalElement::GetStackElement() const
{
    auto containerBox = AceType::DynamicCast<BoxElement>(GetFirstChild());
    if (!containerBox) {
        LOGE("Get stack element failed. Container box element is null!");
        return {};
    }

    auto column = AceType::DynamicCast<ColumnElement>(containerBox->GetFirstChild());
    if (!column || column->GetChildren().size() != COLUMN_CHILD_NUM) {
        // column should have 2 children, title and content.
        LOGE("Get stack element failed. Column is null or child size error!");
        return {};
    }

    // Get second child
    auto secondItr = std::next(column->GetChildren().begin());
    auto contentBox = AceType::DynamicCast<BoxElement>(*secondItr);

    if (!contentBox) {
        LOGE("Get stack element failed. content box element is null!");
        return {};
    }

    auto stack = contentBox->GetFirstChild();
    if (!stack || !AceType::InstanceOf<StackElement>(stack)) {
        LOGE("Get stack element failed. stack is null or type error!");
        return {};
    }

    return AceType::DynamicCast<StackElement>(stack);
}

RefPtr<OverlayElement> ContainerModalElement::GetOverlayElement() const
{
    auto stack = GetStackElement();
    if (!stack) {
        LOGE("Get overlay element failed, stack element is null");
        return {};
    }

    for (const auto& child : stack->GetChildren()) {
        if (child && AceType::InstanceOf<OverlayElement>(child)) {
            return AceType::DynamicCast<OverlayElement>(child);
        }
    }
    LOGE("Get overlay element failed, all children of stack element do not meet the requirements");
    return {};
}

RefPtr<StageElement> ContainerModalElement::GetStageElement() const
{
    auto stack = GetStackElement();
    if (!stack) {
        LOGE("Get stage element failed, stack element is null");
        return {};
    }
    for (const auto& child : stack->GetChildren()) {
        if (child && AceType::InstanceOf<StageElement>(child)) {
            return AceType::DynamicCast<StageElement>(child);
        }
    }
    LOGE("Get stage element failed, all children of stack element do not meet the requirements");
    return {};
}

} // namespace OHOS::Ace