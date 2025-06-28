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

#include "core/components_ng/pattern/checkbox/checkbox_model_ng.h"

#include "core/common/resource/resource_parse_utils.h"
#include "core/components/checkable/checkable_theme.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/checkbox/checkbox_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
constexpr float CHECK_BOX_MARK_SIZE_INVALID_VALUE = -1.0f;

void CheckBoxModelNG::Create(
    const std::optional<std::string>& name, const std::optional<std::string>& groupName, const std::string& tagName)
{
    auto* stack = ViewStackProcessor::GetInstance();
    CHECK_NULL_VOID(stack);
    int32_t nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", tagName.c_str(), nodeId);
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(tagName, nodeId, []() { return AceType::MakeRefPtr<CheckBoxPattern>(); });
    ViewStackProcessor::GetInstance()->Push(frameNode);
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<NG::CheckBoxEventHub>();
    CHECK_NULL_VOID(eventHub);
    if (name.has_value()) {
        eventHub->SetName(name.value());
    }
    if (groupName.has_value()) {
        eventHub->SetGroupName(groupName.value());
    }
}

RefPtr<FrameNode> CheckBoxModelNG::CreateFrameNode(int32_t nodeId)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::CHECK_BOX_ETS_TAG, nodeId, AceType::MakeRefPtr<CheckBoxPattern>());
    CHECK_NULL_RETURN(frameNode, nullptr);
    return frameNode;
}

void CheckBoxModelNG::SetSelect(bool isSelected)
{
    auto* stack = ViewStackProcessor::GetInstance();
    CHECK_NULL_VOID(stack);
    const auto& frameNode = stack->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<CheckBoxEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetCurrentUIState(UI_STATE_SELECTED, isSelected);

    ACE_UPDATE_NODE_PAINT_PROPERTY(CheckBoxPaintProperty, CheckBoxSelect, isSelected, frameNode);
}

void CheckBoxModelNG::SetSelectedColor(const Color& color)
{
    ACE_UPDATE_PAINT_PROPERTY(CheckBoxPaintProperty, CheckBoxSelectedColor, color);
    ACE_UPDATE_PAINT_PROPERTY(CheckBoxPaintProperty, CheckBoxSelectedColorFlagByUser, true);
}

void CheckBoxModelNG::SetUnSelectedColor(const Color& color)
{
    ACE_UPDATE_PAINT_PROPERTY(CheckBoxPaintProperty, CheckBoxUnSelectedColor, color);
    ACE_UPDATE_PAINT_PROPERTY(CheckBoxPaintProperty, CheckBoxUnSelectedColorFlagByUser, true);
}

void CheckBoxModelNG::SetBuilder(std::optional<std::function<void(void)>>& buildFunc)
{
    auto* stack = ViewStackProcessor::GetInstance();
    CHECK_NULL_VOID(stack);
    const auto& frameNode = stack->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto checkBoxPattern = frameNode->GetPattern<CheckBoxPattern>();
    CHECK_NULL_VOID(checkBoxPattern);
    checkBoxPattern->SetIndicatorBuilder(buildFunc);
}

void CheckBoxModelNG::SetCheckboxStyle(CheckBoxStyle checkboxStyle)
{
    ACE_UPDATE_PAINT_PROPERTY(CheckBoxPaintProperty, CheckBoxSelectedStyle, checkboxStyle);
}

void CheckBoxModelNG::SetCheckMarkColor(const Color& color)
{
    ACE_UPDATE_PAINT_PROPERTY(CheckBoxPaintProperty, CheckBoxCheckMarkColor, color);
    ACE_UPDATE_PAINT_PROPERTY(CheckBoxPaintProperty, CheckBoxCheckMarkColorFlagByUser, true);
}

void CheckBoxModelNG::SetCheckMarkSize(const Dimension& size)
{
    ACE_UPDATE_PAINT_PROPERTY(CheckBoxPaintProperty, CheckBoxCheckMarkSize, size);
}

void CheckBoxModelNG::SetCheckMarkWidth(const Dimension& width)
{
    ACE_UPDATE_PAINT_PROPERTY(CheckBoxPaintProperty, CheckBoxCheckMarkWidth, width);
}

void CheckBoxModelNG::SetOnChange(ChangeEvent&& onChange)
{
    auto* stack = ViewStackProcessor::GetInstance();
    CHECK_NULL_VOID(stack);
    auto frameNode = stack->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<CheckBoxEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChange(std::move(onChange));
}

void CheckBoxModelNG::SetWidth(const Dimension& width)
{
    NG::ViewAbstract::SetWidth(NG::CalcLength(width));
}

void CheckBoxModelNG::SetHeight(const Dimension& height)
{
    NG::ViewAbstract::SetHeight(NG::CalcLength(height));
}

void CheckBoxModelNG::SetPadding(const NG::PaddingPropertyF& args, const NG::PaddingProperty& newArgs, bool flag)
{
    NG::ViewAbstract::SetPadding(newArgs);
}

void CheckBoxModelNG::SetChangeEvent(ChangeEvent&& changeEvent)
{
    auto* stack = ViewStackProcessor::GetInstance();
    CHECK_NULL_VOID(stack);
    auto frameNode = stack->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<CheckBoxEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetChangeEvent(std::move(changeEvent));
}

void CheckBoxModelNG::SetResponseRegion(const std::vector<DimensionRect>& responseRegion)
{
    NG::ViewAbstract::SetResponseRegion(responseRegion);
    auto* stack = ViewStackProcessor::GetInstance();
    CHECK_NULL_VOID(stack);
    auto frameNode = stack->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetIsUserSetResponseRegion(true);
}

void CheckBoxModelNG::SetSelect(FrameNode* frameNode, bool isSelected)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<CheckBoxEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetCurrentUIState(UI_STATE_SELECTED, isSelected);
    ACE_UPDATE_NODE_PAINT_PROPERTY(CheckBoxPaintProperty, CheckBoxSelect, isSelected, frameNode);
}

void CheckBoxModelNG::SetSelectedColor(FrameNode* frameNode, const Color& color)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(CheckBoxPaintProperty, CheckBoxSelectedColor, color, frameNode);
    ACE_UPDATE_NODE_PAINT_PROPERTY(CheckBoxPaintProperty, CheckBoxSelectedColorFlagByUser, true, frameNode);
}

void CheckBoxModelNG::SetUnSelectedColor(FrameNode* frameNode, const Color& color)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(CheckBoxPaintProperty, CheckBoxUnSelectedColor, color, frameNode);
    ACE_UPDATE_NODE_PAINT_PROPERTY(CheckBoxPaintProperty, CheckBoxUnSelectedColorFlagByUser, true, frameNode);
}

void CheckBoxModelNG::SetCheckMarkColor(FrameNode* frameNode, const Color& color)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(CheckBoxPaintProperty, CheckBoxCheckMarkColor, color, frameNode);
    ACE_UPDATE_NODE_PAINT_PROPERTY(CheckBoxPaintProperty, CheckBoxCheckMarkColorFlagByUser, true, frameNode);
}

void CheckBoxModelNG::SetCheckMarkSize(FrameNode* frameNode, const Dimension& size)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(CheckBoxPaintProperty, CheckBoxCheckMarkSize, size, frameNode);
}

void CheckBoxModelNG::SetCheckMarkWidth(FrameNode* frameNode, const Dimension& width)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(CheckBoxPaintProperty, CheckBoxCheckMarkWidth, width, frameNode);
}

void CheckBoxModelNG::SetHeight(FrameNode* frameNode, const Dimension& height)
{
    NG::ViewAbstract::SetHeight(frameNode, NG::CalcLength(height));
}

void CheckBoxModelNG::SetWidth(FrameNode* frameNode, const Dimension& width)
{
    NG::ViewAbstract::SetWidth(frameNode, NG::CalcLength(width));
}

void CheckBoxModelNG::SetPadding(FrameNode* frameNode, const NG::PaddingProperty& padding)
{
    NG::ViewAbstract::SetPadding(frameNode, padding);
}

void CheckBoxModelNG::SetResponseRegion(FrameNode* frameNode, const std::vector<DimensionRect>& responseRegion)
{
    NG::ViewAbstract::SetResponseRegion(responseRegion);
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetIsUserSetResponseRegion(true);
}

void CheckBoxModelNG::SetCheckboxStyle(FrameNode* frameNode, CheckBoxStyle checkboxStyle)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(CheckBoxPaintProperty, CheckBoxSelectedStyle, checkboxStyle, frameNode);
}

void CheckBoxModelNG::SetCheckboxName(FrameNode* frameNode, const std::optional<std::string>& name)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<NG::CheckBoxEventHub>();
    CHECK_NULL_VOID(eventHub);
    if (name.has_value()) {
        eventHub->SetName(name.value());
    }
}

void CheckBoxModelNG::SetCheckboxGroup(FrameNode* frameNode, const std::optional<std::string>& groupName)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<NG::CheckBoxEventHub>();
    CHECK_NULL_VOID(eventHub);
    if (groupName.has_value()) {
        eventHub->SetGroupName(groupName.value());
    }
}

bool CheckBoxModelNG::GetSelect(FrameNode* frameNode)
{
    bool value = false;
    CHECK_NULL_RETURN(frameNode, value);
    ACE_GET_NODE_PAINT_PROPERTY_WITH_DEFAULT_VALUE(CheckBoxPaintProperty, CheckBoxSelect, value, frameNode, value);
    return value;
}

Color CheckBoxModelNG::GetSelectedColor(FrameNode* frameNode)
{
    Color value;
    CHECK_NULL_RETURN(frameNode, value);
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_RETURN(pipelineContext, value);
    auto theme = pipelineContext->GetTheme<CheckboxTheme>(frameNode->GetThemeScopeId());
    CHECK_NULL_RETURN(theme, value);
    value = theme->GetActiveColor();
    ACE_GET_NODE_PAINT_PROPERTY_WITH_DEFAULT_VALUE(
        CheckBoxPaintProperty, CheckBoxSelectedColor, value, frameNode, value);
    return value;
}

Color CheckBoxModelNG::GetUnSelectedColor(FrameNode* frameNode)
{
    Color value;
    CHECK_NULL_RETURN(frameNode, value);
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_RETURN(pipelineContext, value);
    auto theme = pipelineContext->GetTheme<CheckboxTheme>(frameNode->GetThemeScopeId());
    CHECK_NULL_RETURN(theme, value);
    value = theme->GetInactiveColor();
    ACE_GET_NODE_PAINT_PROPERTY_WITH_DEFAULT_VALUE(
        CheckBoxPaintProperty, CheckBoxUnSelectedColor, value, frameNode, value);
    return value;
}

Color CheckBoxModelNG::GetCheckMarkColor(FrameNode* frameNode)
{
    Color value;
    CHECK_NULL_RETURN(frameNode, value);
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_RETURN(pipelineContext, value);
    auto theme = pipelineContext->GetTheme<CheckboxTheme>(frameNode->GetThemeScopeId());
    CHECK_NULL_RETURN(theme, value);
    value = theme->GetPointColor();
    ACE_GET_NODE_PAINT_PROPERTY_WITH_DEFAULT_VALUE(
        CheckBoxPaintProperty, CheckBoxCheckMarkColor, value, frameNode, value);
    return value;
}

Dimension CheckBoxModelNG::GetCheckMarkSize(FrameNode* frameNode)
{
    Dimension value = Dimension(CHECK_BOX_MARK_SIZE_INVALID_VALUE);
    CHECK_NULL_RETURN(frameNode, value);
    ACE_GET_NODE_PAINT_PROPERTY_WITH_DEFAULT_VALUE(
        CheckBoxPaintProperty, CheckBoxCheckMarkSize, value, frameNode, value);
    return value;
}

Dimension CheckBoxModelNG::GetCheckMarkWidth(FrameNode* frameNode)
{
    Dimension value;
    CHECK_NULL_RETURN(frameNode, value);
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_RETURN(pipelineContext, value);
    auto theme = pipelineContext->GetTheme<CheckboxTheme>();
    CHECK_NULL_RETURN(theme, value);
    value = theme->GetCheckStroke();
    ACE_GET_NODE_PAINT_PROPERTY_WITH_DEFAULT_VALUE(
        CheckBoxPaintProperty, CheckBoxCheckMarkWidth, value, frameNode, value);
    return value;
}

CheckBoxStyle CheckBoxModelNG::GetCheckboxStyle(FrameNode* frameNode)
{
    CheckBoxStyle value = CheckBoxStyle::CIRCULAR_STYLE;
    CHECK_NULL_RETURN(frameNode, value);
    ACE_GET_NODE_PAINT_PROPERTY_WITH_DEFAULT_VALUE(
        CheckBoxPaintProperty, CheckBoxSelectedStyle, value, frameNode, value);
    return value;
}

void CheckBoxModelNG::SetBuilderFunc(FrameNode* frameNode, NG::CheckBoxMakeCallback&& makeFunc)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetBuilderFunc(std::move(makeFunc));
}

void CheckBoxModelNG::SetChangeValue(FrameNode* frameNode, bool value)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetCheckBoxSelect(value);
}

void CheckBoxModelNG::SetOnChange(FrameNode* frameNode, ChangeEvent&& onChange)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<CheckBoxEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChange(std::move(onChange));
}

std::string CheckBoxModelNG::GetCheckboxName(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, "");
    auto eventHub = frameNode->GetOrCreateEventHub<NG::CheckBoxEventHub>();
    CHECK_NULL_RETURN(eventHub, "");
    return eventHub->GetName();
}

std::string CheckBoxModelNG::GetCheckboxGroup(FrameNode* frameNode)
{
    CHECK_NULL_RETURN(frameNode, "");
    auto eventHub = frameNode->GetOrCreateEventHub<NG::CheckBoxEventHub>();
    CHECK_NULL_RETURN(eventHub, "");
    return eventHub->GetGroupName();
}

void CheckBoxModelNG::CreateWithColorResourceObj(
    const RefPtr<ResourceObject>& resObj, const CheckBoxColorType checkBoxColorType)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    CreateWithResourceObj(frameNode, checkBoxColorType, resObj);
}

void CheckBoxModelNG::UpdateComponentColor(FrameNode* frameNode, const CheckBoxColorType checkBoxColorType)
{
    CHECK_NULL_VOID(frameNode);
    switch (checkBoxColorType) {
        case CheckBoxColorType::SELECTED_COLOR:
            ResetSelectedColor(frameNode);
            break;
        case CheckBoxColorType::UN_SELECTED_COLOR:
            ResetUnSelectedColor(frameNode);
            break;
        default:
            break;
    }
}

void CheckBoxModelNG::CreateWithResourceObj(
    FrameNode* frameNode, const CheckBoxColorType jsResourceType, const RefPtr<ResourceObject>& resObj)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    CHECK_NULL_VOID(pattern);

    std::string key = "checkbox" + ColorTypeToString(jsResourceType);
    pattern->RemoveResObj(key);
    CHECK_NULL_VOID(resObj);
    auto&& updateFunc = [jsResourceType, weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto pattern = frameNode->GetPattern<CheckBoxPattern>();
        CHECK_NULL_VOID(pattern);
        Color result;
        if (ResourceParseUtils::ParseResColor(resObj, result)) {
            UpdateComponentColor(AceType::RawPtr(frameNode), jsResourceType);
            return;
        }

        pattern->UpdateCheckboxComponentColor(result, jsResourceType);
    };
    updateFunc(resObj);
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

std::string CheckBoxModelNG::ColorTypeToString(const CheckBoxColorType checkBoxColorType)
{
    std::string rst;
    switch (checkBoxColorType) {
        case CheckBoxColorType::SELECTED_COLOR:
            rst = "SelectedColor";
            break;
        case CheckBoxColorType::UN_SELECTED_COLOR:
            rst = "UnSelectedColor";
            break;
        default:
            rst = "Unknown";
            break;
    }
    return rst;
}

void CheckBoxModelNG::ResetSelectedColor()
{
    ACE_RESET_PAINT_PROPERTY_WITH_FLAG(CheckBoxPaintProperty, CheckBoxSelectedColor, PROPERTY_UPDATE_RENDER);
    ACE_RESET_PAINT_PROPERTY_WITH_FLAG(CheckBoxPaintProperty, CheckBoxSelectedColorFlagByUser, PROPERTY_UPDATE_RENDER);
}

void CheckBoxModelNG::ResetSelectedColor(FrameNode* frameNode)
{
    ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(
        CheckBoxPaintProperty, CheckBoxSelectedColor, PROPERTY_UPDATE_RENDER, frameNode);
    ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(
        CheckBoxPaintProperty, CheckBoxSelectedColorFlagByUser, PROPERTY_UPDATE_RENDER, frameNode);
}

void CheckBoxModelNG::ResetUnSelectedColor()
{
    ACE_RESET_PAINT_PROPERTY_WITH_FLAG(CheckBoxPaintProperty, CheckBoxUnSelectedColor, PROPERTY_UPDATE_RENDER);
    ACE_RESET_PAINT_PROPERTY_WITH_FLAG(
        CheckBoxPaintProperty, CheckBoxUnSelectedColorFlagByUser, PROPERTY_UPDATE_RENDER);
}

void CheckBoxModelNG::ResetUnSelectedColor(FrameNode* frameNode)
{
    ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(
        CheckBoxPaintProperty, CheckBoxUnSelectedColor, PROPERTY_UPDATE_RENDER, frameNode);
    ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(
        CheckBoxPaintProperty, CheckBoxUnSelectedColorFlagByUser, PROPERTY_UPDATE_RENDER, frameNode);
}

void CheckBoxModelNG::ResetCheckMarkColor()
{
    ACE_RESET_PAINT_PROPERTY_WITH_FLAG(CheckBoxPaintProperty, CheckBoxCheckMarkColor, PROPERTY_UPDATE_RENDER);
    ACE_RESET_PAINT_PROPERTY_WITH_FLAG(CheckBoxPaintProperty, CheckBoxCheckMarkColorFlagByUser, PROPERTY_UPDATE_RENDER);
}

void CheckBoxModelNG::ResetCheckMarkColor(FrameNode* frameNode)
{
    ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(
        CheckBoxPaintProperty, CheckBoxCheckMarkColor, PROPERTY_UPDATE_RENDER, frameNode);
    ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(
        CheckBoxPaintProperty, CheckBoxCheckMarkColorFlagByUser, PROPERTY_UPDATE_RENDER, frameNode);
}

void CheckBoxModelNG::SetIsUserSetMargin(bool isUserSet)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    SetIsUserSetMargin(frameNode, isUserSet);
}

void CheckBoxModelNG::SetIsUserSetMargin(FrameNode* frameNode, bool isUserSet)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<CheckBoxPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetIsUserSetMargin(isUserSet);
}
} // namespace OHOS::Ace::NG
