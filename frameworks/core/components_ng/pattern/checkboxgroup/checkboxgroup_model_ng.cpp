/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_pattern.h"

namespace OHOS::Ace::NG {
void CheckBoxGroupModelNG::Create(const std::optional<std::string>& groupName)
{
    auto* stack = ViewStackProcessor::GetInstance();
    CHECK_NULL_VOID(stack);
    int32_t nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::CHECKBOXGROUP_ETS_TAG, nodeId);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CHECKBOXGROUP_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<CheckBoxGroupPattern>(); });
    CHECK_NULL_VOID(frameNode);
    stack->Push(frameNode);
    auto eventHub = frameNode->GetEventHub<NG::CheckBoxGroupEventHub>();
    if (groupName.has_value()) {
        eventHub->SetGroupName(groupName.value());
    }
}

void CheckBoxGroupModelNG::SetSelectAll(bool isSelected)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<CheckBoxGroupPattern>();
    pattern->SetUpdateFlag(true);
    auto eventHub = frameNode->GetEventHub<CheckBoxGroupEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetCurrentUIState(UI_STATE_SELECTED, isSelected);

    ACE_UPDATE_PAINT_PROPERTY(CheckBoxGroupPaintProperty, CheckBoxGroupSelect, isSelected);
}

void CheckBoxGroupModelNG::SetSelectedColor(const Color& color)
{
    ACE_UPDATE_PAINT_PROPERTY(CheckBoxGroupPaintProperty, CheckBoxGroupSelectedColor, color);
}

void CheckBoxGroupModelNG::SetUnSelectedColor(const Color& color)
{
    ACE_UPDATE_PAINT_PROPERTY(CheckBoxGroupPaintProperty, CheckBoxGroupUnSelectedColor, color);
}

void CheckBoxGroupModelNG::SetCheckMarkColor(const Color& color)
{
    ACE_UPDATE_PAINT_PROPERTY(CheckBoxGroupPaintProperty, CheckBoxGroupCheckMarkColor, color);
}

void CheckBoxGroupModelNG::SetCheckMarkSize(const Dimension& size)
{
    ACE_UPDATE_PAINT_PROPERTY(CheckBoxGroupPaintProperty, CheckBoxGroupCheckMarkSize, size);
}

void CheckBoxGroupModelNG::SetCheckMarkWidth(const Dimension& width)
{
    ACE_UPDATE_PAINT_PROPERTY(CheckBoxGroupPaintProperty, CheckBoxGroupCheckMarkWidth, width);
}

void CheckBoxGroupModelNG::SetOnChange(GroupChangeEvent&& onChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<CheckBoxGroupEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChange(std::move(onChange));
}

void CheckBoxGroupModelNG::SetWidth(const Dimension& width)
{
    NG::ViewAbstract::SetWidth(NG::CalcLength(width));
}

void CheckBoxGroupModelNG::SetHeight(const Dimension& height)
{
    NG::ViewAbstract::SetHeight(NG::CalcLength(height));
}

void CheckBoxGroupModelNG::SetPadding(const NG::PaddingPropertyF& args, const NG::PaddingProperty& newArgs, bool flag)
{
    NG::ViewAbstract::SetPadding(newArgs);
}

void CheckBoxGroupModelNG::SetChangeEvent(GroupChangeEvent&& changeEvent)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<CheckBoxGroupEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetChangeEvent(std::move(changeEvent));
}

void CheckBoxGroupModelNG::SetResponseRegion(const std::vector<DimensionRect>& responseRegion)
{
    NG::ViewAbstract::SetResponseRegion(responseRegion);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<CheckBoxGroupPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetIsUserSetResponseRegion(true);
}

RefPtr<FrameNode> CheckBoxGroupModelNG::CreateFrameNode(int32_t nodeId)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::CHECKBOXGROUP_ETS_TAG, nodeId,
        AceType::MakeRefPtr<CheckBoxGroupPattern>());
    CHECK_NULL_RETURN(frameNode, nullptr);
    return frameNode;
}

void CheckBoxGroupModelNG::SetSelectAll(FrameNode* frameNode, bool isSelected)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<CheckBoxGroupPattern>();
    pattern->SetUpdateFlag(true);
    ACE_UPDATE_NODE_PAINT_PROPERTY(CheckBoxGroupPaintProperty, CheckBoxGroupSelect, isSelected, frameNode);
}

void CheckBoxGroupModelNG::SetSelectedColor(FrameNode* frameNode, const Color& color)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(CheckBoxGroupPaintProperty, CheckBoxGroupSelectedColor, color, frameNode);
}

void CheckBoxGroupModelNG::SetUnSelectedColor(FrameNode* frameNode, const Color& color)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(CheckBoxGroupPaintProperty, CheckBoxGroupUnSelectedColor, color, frameNode);
}

void CheckBoxGroupModelNG::SetCheckMarkColor(FrameNode* frameNode, const Color& color)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(CheckBoxGroupPaintProperty, CheckBoxGroupCheckMarkColor, color, frameNode);
}

void CheckBoxGroupModelNG::SetCheckMarkSize(FrameNode* frameNode, const Dimension& size)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(CheckBoxGroupPaintProperty, CheckBoxGroupCheckMarkSize, size, frameNode);
}

void CheckBoxGroupModelNG::SetCheckMarkWidth(FrameNode* frameNode, const Dimension& width)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(CheckBoxGroupPaintProperty, CheckBoxGroupCheckMarkWidth, width, frameNode);
}

void CheckBoxGroupModelNG::SetHeight(FrameNode* frameNode, const Dimension& height)
{
    NG::ViewAbstract::SetHeight(frameNode, NG::CalcLength(height));
}

void CheckBoxGroupModelNG::SetWidth(FrameNode* frameNode, const Dimension& width)
{
    NG::ViewAbstract::SetWidth(frameNode, NG::CalcLength(width));
}

void CheckBoxGroupModelNG::SetCheckboxGroupStyle(CheckBoxStyle checkboxGroupStyle)
{
    ACE_UPDATE_PAINT_PROPERTY(CheckBoxGroupPaintProperty, CheckBoxGroupSelectedStyle, checkboxGroupStyle);
}

void CheckBoxGroupModelNG::SetCheckboxGroupStyle(FrameNode* frameNode, CheckBoxStyle checkboxGroupStyle)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(
        CheckBoxGroupPaintProperty, CheckBoxGroupSelectedStyle, checkboxGroupStyle, frameNode);
}

void CheckBoxGroupModelNG::SetCheckboxGroupName(FrameNode* frameNode, const std::optional<std::string>& groupName)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<NG::CheckBoxGroupEventHub>();
    if (groupName.has_value()) {
        eventHub->SetGroupName(groupName.value());
    }
}

} // namespace OHOS::Ace::NG
