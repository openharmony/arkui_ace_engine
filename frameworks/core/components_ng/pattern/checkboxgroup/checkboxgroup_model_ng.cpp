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

#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_model_ng.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

void CheckBoxGroupModelNG::Create(const std::optional<std::string>& groupName)
{
    auto* stack = ViewStackProcessor::GetInstance();
    int32_t nodeId = (stack == nullptr ? 0 : stack->ClaimNodeId());
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::CHECKBOXGROUP_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<CheckBoxGroupPattern>(); });
    ViewStackProcessor::GetInstance()->Push(frameNode);

    auto eventHub = frameNode->GetEventHub<NG::CheckBoxGroupEventHub>();
    if (groupName.has_value()) {
        eventHub->SetGroupName(groupName.value());
    }
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    
    ACE_UPDATE_PAINT_PROPERTY(CheckBoxGroupPaintProperty, CheckBoxGroupSelect, false);
}

void CheckBoxGroupModelNG::SetSelectAll(bool isSelected)
{
    ACE_UPDATE_PAINT_PROPERTY(CheckBoxGroupPaintProperty, CheckBoxGroupSelect, isSelected);
}

void CheckBoxGroupModelNG::SetSelectedColor(const Color& color)
{
    ACE_UPDATE_PAINT_PROPERTY(CheckBoxGroupPaintProperty, CheckBoxGroupSelectedColor, color);
}

void CheckBoxGroupModelNG::SetOnChange(GroupChangeEvent&& onChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<CheckBoxGroupEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChange(std::move(onChange));
}

void CheckBoxGroupModelNG::SetWidth(const Dimension& width) {}

void CheckBoxGroupModelNG::SetHeight(const Dimension& height) {}

void CheckBoxGroupModelNG::SetPadding(const NG::PaddingPropertyF& args) {}

} // namespace OHOS::Ace::NG
