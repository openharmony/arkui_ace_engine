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

#include "core/components_ng/pattern/checkbox/checkbox_view.h"

#include <string>

#include "core/components/common/properties/color.h"
#include "core/components/picker/picker_value_element.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/checkbox/checkbox_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

void CheckBoxView::Create(
    const std::optional<std::string>& name, const std::optional<std::string>& groupName, const std::string& tagName)
{
    auto* stack = ViewStackProcessor::GetInstance();
    int32_t nodeId = (stack == nullptr ? 0 : stack->ClaimNodeId());
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(tagName, nodeId, []() { return AceType::MakeRefPtr<CheckBoxPattern>(); });
    ViewStackProcessor::GetInstance()->Push(frameNode);

    auto eventHub = frameNode->GetEventHub<NG::CheckBoxEventHub>();
    if (name.has_value()) {
        eventHub->SetName(name.value());
    }
    if (groupName.has_value()) {
        eventHub->SetGroupName(groupName.value());
    }
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void CheckBoxView::SetSelect(bool isSelected)
{
    ACE_UPDATE_PAINT_PROPERTY(CheckBoxPaintProperty, CheckBoxSelect, isSelected);
}

void CheckBoxView::SetSelectedColor(Color color)
{
    ACE_UPDATE_PAINT_PROPERTY(CheckBoxPaintProperty, CheckBoxSelectedColor, color);
}

void CheckBoxView::SetOnChange(ChangeEvent&& onChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<CheckBoxEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChange(std::move(onChange));
}

} // namespace OHOS::Ace::NG
