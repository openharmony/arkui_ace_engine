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
static constexpr float CHECK_BOX_GROUP_MARK_SIZE_INVALID_VALUE = -1.0f;
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
    CHECK_NULL_VOID(eventHub);
    if (groupName.has_value()) {
        eventHub->SetGroupName(groupName.value());
    }
}

std::string CheckBoxGroupModelNG::GetCheckboxGroupName(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, "");
    auto eventHub = frameNode->GetEventHub<NG::CheckBoxGroupEventHub>();
    CHECK_NULL_RETURN(eventHub, "");
    return eventHub->GetGroupName();
}

bool CheckBoxGroupModelNG::GetSelect(FrameNode* frameNode)
{
    bool value = false;
    CHECK_NULL_RETURN(frameNode, value);
    ACE_GET_NODE_PAINT_PROPERTY_WITH_DEFAULT_VALUE(
        CheckBoxGroupPaintProperty, CheckBoxGroupSelect, value, frameNode, value);
    return value;
}

Color CheckBoxGroupModelNG::GetSelectedColor(FrameNode* frameNode)
{
    Color value = Color(0xff000000);
    CHECK_NULL_RETURN(frameNode, value);
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_RETURN(pipelineContext, value);
    auto theme = pipelineContext->GetTheme<CheckboxTheme>();
    CHECK_NULL_RETURN(theme, value);
    value = theme->GetActiveColor();
    ACE_GET_NODE_PAINT_PROPERTY_WITH_DEFAULT_VALUE(
        CheckBoxGroupPaintProperty, CheckBoxGroupSelectedColor, value, frameNode, value);
    return value;
}

Color CheckBoxGroupModelNG::GetUnSelectedColor(FrameNode* frameNode)
{
    Color value = Color(0xff000000);
    CHECK_NULL_RETURN(frameNode, value);
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_RETURN(pipelineContext, value);
    auto theme = pipelineContext->GetTheme<CheckboxTheme>();
    CHECK_NULL_RETURN(theme, value);
    value = theme->GetInactiveColor();
    ACE_GET_NODE_PAINT_PROPERTY_WITH_DEFAULT_VALUE(
        CheckBoxGroupPaintProperty, CheckBoxGroupUnSelectedColor, value, frameNode, value);
    return value;
}

Color CheckBoxGroupModelNG::GetCheckMarkColor(FrameNode* frameNode)
{
    Color value = Color(0xff000000);
    CHECK_NULL_RETURN(frameNode, value);
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_RETURN(pipelineContext, value);
    auto theme = pipelineContext->GetTheme<CheckboxTheme>();
    CHECK_NULL_RETURN(theme, value);
    value = theme->GetPointColor();
    ACE_GET_NODE_PAINT_PROPERTY_WITH_DEFAULT_VALUE(
        CheckBoxGroupPaintProperty, CheckBoxGroupCheckMarkColor, value, frameNode, value);
    return value;
}

Dimension CheckBoxGroupModelNG::GetCheckMarkSize(FrameNode* frameNode)
{
    Dimension value = Dimension(CHECK_BOX_GROUP_MARK_SIZE_INVALID_VALUE);
    ACE_GET_NODE_PAINT_PROPERTY_WITH_DEFAULT_VALUE(
        CheckBoxGroupPaintProperty, CheckBoxGroupCheckMarkSize, value, frameNode, value);
    return value;
}

Dimension CheckBoxGroupModelNG::GetCheckMarkWidth(FrameNode* frameNode)
{
    Dimension value = Dimension(0.0);
    CHECK_NULL_RETURN(frameNode, value);
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_RETURN(pipelineContext, value);
    auto theme = pipelineContext->GetTheme<CheckboxTheme>();
    CHECK_NULL_RETURN(theme, value);
    value = theme->GetCheckStroke();
    ACE_GET_NODE_PAINT_PROPERTY_WITH_DEFAULT_VALUE(
        CheckBoxGroupPaintProperty, CheckBoxGroupCheckMarkWidth, value, frameNode, value);
    return value;
}

CheckBoxStyle CheckBoxGroupModelNG::GetCheckboxGroupStyle(FrameNode* frameNode)
{
    CheckBoxStyle value = CheckBoxStyle::CIRCULAR_STYLE;
    ACE_GET_NODE_PAINT_PROPERTY_WITH_DEFAULT_VALUE(
        CheckBoxGroupPaintProperty, CheckBoxGroupSelectedStyle, value, frameNode, value);
    return value;
}

void CheckBoxGroupModelNG::SetOnChange(FrameNode* frameNode, GroupChangeEvent&& onChange)
{
    auto eventHub = frameNode->GetEventHub<CheckBoxGroupEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChange(std::move(onChange));
}
} // namespace OHOS::Ace::NG
