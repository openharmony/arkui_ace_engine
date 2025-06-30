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

#include "core/components_ng/pattern/toggle/toggle_model_ng.h"

#include "core/common/resource/resource_parse_utils.h"
#include "core/components/toggle/toggle_theme.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/pattern/button/toggle_button_model_ng.h"
#include "core/components_ng/pattern/button/toggle_button_pattern.h"
#include "core/components_ng/pattern/checkbox/checkbox_model_ng.h"
#include "core/components_ng/pattern/checkbox/toggle_checkbox_pattern.h"
#include "core/components_ng/pattern/toggle/switch_pattern.h"

namespace OHOS::Ace::NG {

constexpr uint32_t DEFAULT_COLOR = 0xffffffff;

void ToggleModelNG::Create(NG::ToggleType toggleType, bool isOn)
{
    auto* stack = ViewStackProcessor::GetInstance();
    int nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::TOGGLE_ETS_TAG, nodeId);
    auto childFrameNode = FrameNode::GetFrameNode(V2::TOGGLE_ETS_TAG, nodeId);
    if (!childFrameNode) {
        auto frameNode = CreateFrameNode(nodeId, toggleType, isOn);
        stack->Push(frameNode);
        return;
    }
    auto pattern = childFrameNode->GetPattern();
    if (AceType::InstanceOf<SwitchPattern>(pattern) && toggleType == ToggleType::SWITCH) {
        UpdateSwitchIsOn(childFrameNode, isOn);
        stack->Push(childFrameNode);
    } else if (AceType::InstanceOf<ToggleCheckBoxPattern>(pattern) && toggleType == ToggleType::CHECKBOX) {
        UpdateCheckboxIsOn(childFrameNode, isOn);
        stack->Push(childFrameNode);
    } else if (AceType::InstanceOf<ToggleButtonPattern>(pattern) && toggleType == ToggleType::BUTTON) {
        UpdateToggleButtonIsOn(childFrameNode, isOn);
        stack->Push(childFrameNode);
    } else {
        ReCreateFrameNode(childFrameNode, nodeId, toggleType, isOn);
    }
    auto pros = childFrameNode->GetPaintProperty<SwitchPaintProperty>();
    if (pros) {
        pros->ResetUnselectedColorSetByUser();
        pros->ResetSelectedColorSetByUser();
        pros->ResetSwitchPointColorSetByUser();
    }
}

void ToggleModelNG::ReCreateFrameNode(
    const RefPtr<FrameNode>& childFrameNode, int32_t nodeId, ToggleType toggleType, bool isOn)
{
    auto parentFrame = childFrameNode->GetParent();
    CHECK_NULL_VOID(parentFrame);
    auto index = RemoveNode(childFrameNode, nodeId);
    childFrameNode->SetUndefinedNodeId();
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = CreateFrameNode(nodeId, toggleType, isOn);
    stack->Push(frameNode);
    ReplaceAllChild(childFrameNode);
    AddNewChild(parentFrame, nodeId, index, toggleType);
}

RefPtr<FrameNode> ToggleModelNG::CreateFrameNode(int32_t nodeId, ToggleType toggleType, bool isOn)
{
    switch (toggleType) {
        case ToggleType::CHECKBOX: {
            return CreateCheckboxFrameNode(nodeId, isOn);
        }
        case ToggleType::SWITCH: {
            return CreateSwitchFrameNode(nodeId, isOn);
        }
        case ToggleType::BUTTON: {
            return CreateButtonFrameNode(nodeId, isOn);
        }
        default: {
            return CreateSwitchFrameNode(nodeId, isOn);
        }
    }
}

void ToggleModelNG::SetSelectedColor(const std::optional<Color>& selectedColor)
{
    auto* stack = ViewStackProcessor::GetInstance();
    CHECK_NULL_VOID(stack);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto frameNode = stack->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    Color color;
    if (selectedColor.has_value()) {
        color = selectedColor.value();
    }

    auto checkboxPattern = frameNode->GetPattern<ToggleCheckBoxPattern>();
    if (checkboxPattern) {
        if (!selectedColor.has_value()) {
            CheckBoxModelNG::ResetSelectedColor(frameNode);
        } else {
            CheckBoxModelNG::SetSelectedColor(frameNode, color);
        }
        return;
    }
    auto buttonPattern = frameNode->GetPattern<ToggleButtonPattern>();
    if (buttonPattern) {
        if (!selectedColor.has_value()) {
            ToggleButtonModelNG::ResetSelectedColor();
        } else {
            ToggleButtonModelNG::SetSelectedColor(color);
        }
        return;
    }

    if (!selectedColor.has_value()) {
        ACE_RESET_PAINT_PROPERTY_WITH_FLAG(SwitchPaintProperty, SelectedColor, PROPERTY_UPDATE_RENDER);
        ACE_UPDATE_PAINT_PROPERTY(SwitchPaintProperty, SelectedColorSetByUser, false);
    } else {
        ACE_UPDATE_PAINT_PROPERTY(SwitchPaintProperty, SelectedColor, color);
        ACE_UPDATE_PAINT_PROPERTY(SwitchPaintProperty, SelectedColorSetByUser, true);
    }
}

void ToggleModelNG::SetSwitchPointColor(const std::optional<Color>& switchPointColor)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto paintProperty = frameNode->GetPaintProperty<SwitchPaintProperty>();
    if (paintProperty) {
        if (switchPointColor.has_value()) {
            paintProperty->UpdateSwitchPointColor(switchPointColor.value());
        } else {
            paintProperty->ResetSwitchPointColor();
        }
    }
}

void ToggleModelNG::SetSwitchPointColorSetByUser(const bool flag)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto paintProperty = frameNode->GetPaintProperty<SwitchPaintProperty>();
    if (paintProperty) {
        paintProperty->UpdateSwitchPointColorSetByUser(flag);
    }
}

void ToggleModelNG::OnChange(ChangeEvent&& onChange)
{
    auto* stack = ViewStackProcessor::GetInstance();
    CHECK_NULL_VOID(stack);
    auto frameNode = stack->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto checkboxPattern = frameNode->GetPattern<ToggleCheckBoxPattern>();
    if (checkboxPattern) {
        auto eventHub = frameNode->GetOrCreateEventHub<CheckBoxEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->SetOnChange(std::move(onChange));
        return;
    }
    auto buttonPattern = frameNode->GetPattern<ToggleButtonPattern>();
    if (buttonPattern) {
        auto eventHub = frameNode->GetOrCreateEventHub<ToggleButtonEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->SetOnChange(std::move(onChange));
        return;
    }
    auto eventHub = frameNode->GetOrCreateEventHub<SwitchEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChange(std::move(onChange));
}

void ToggleModelNG::OnChange(FrameNode* frameNode, ChangeEvent&& onChange)
{
    CHECK_NULL_VOID(frameNode);
    auto checkboxPattern = AceType::DynamicCast<ToggleCheckBoxPattern>(frameNode->GetPattern());
    if (checkboxPattern) {
        auto eventHub = frameNode->GetOrCreateEventHub<CheckBoxEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->SetOnChange(std::move(onChange));
        return;
    }
    auto buttonPattern = AceType::DynamicCast<ToggleButtonPattern>(frameNode->GetPattern());
    if (buttonPattern) {
        auto eventHub = frameNode->GetOrCreateEventHub<ToggleButtonEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->SetOnChange(std::move(onChange));
        return;
    }
    auto eventHub = frameNode->GetOrCreateEventHub<SwitchEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChange(std::move(onChange));
}

void ToggleModelNG::SetBuilderFunc(FrameNode* frameNode, NG::SwitchMakeCallback&& makeFunc)
{
    CHECK_NULL_VOID(frameNode);
    auto checkboxPattern = AceType::DynamicCast<ToggleCheckBoxPattern>(frameNode->GetPattern());
    if (checkboxPattern) {
        checkboxPattern->SetToggleBuilderFunc(std::move(makeFunc));
        return;
    }
    auto buttonPattern = AceType::DynamicCast<ToggleButtonPattern>(frameNode->GetPattern());
    if (buttonPattern) {
        buttonPattern->SetToggleBuilderFunc(std::move(makeFunc));
        return;
    }
    auto pattern = frameNode->GetPattern<SwitchPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetBuilderFunc(std::move(makeFunc));
}

void ToggleModelNG::SetChangeValue(FrameNode* frameNode, bool value)
{
    CHECK_NULL_VOID(frameNode);
    auto checkboxPattern = AceType::DynamicCast<ToggleCheckBoxPattern>(frameNode->GetPattern());
    if (checkboxPattern) {
        checkboxPattern->SetCheckBoxSelect(std::move(value));
        return;
    }
    auto buttonPattern = AceType::DynamicCast<ToggleButtonPattern>(frameNode->GetPattern());
    if (buttonPattern) {
        buttonPattern->SetButtonPress(std::move(value));
        return;
    }
    auto pattern = frameNode->GetPattern<SwitchPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSwitchIsOn(value);
}

void ToggleModelNG::SetWidth(const Dimension& width)
{
    NG::ViewAbstract::SetWidth(NG::CalcLength(width));
}

void ToggleModelNG::SetHeight(const Dimension& height)
{
    NG::ViewAbstract::SetHeight(NG::CalcLength(height));
}

void ToggleModelNG::SetBackgroundColor(const Color& color, bool flag)
{
    ToggleButtonModelNG::SetBackgroundColor(color, flag);
}

bool ToggleModelNG::IsToggle()
{
    return false;
}

void ToggleModelNG::SetPadding(const NG::PaddingPropertyF& /*args*/, const NG::PaddingProperty& newArgs)
{
    NG::ViewAbstract::SetPadding(newArgs);
}
RefPtr<FrameNode> ToggleModelNG::CreateCheckboxFrameNode(int32_t nodeId, bool isOn)
{
    auto frameNode =
        FrameNode::CreateFrameNode(V2::CHECKBOX_ETS_TAG, nodeId, AceType::MakeRefPtr<ToggleCheckBoxPattern>());
    UpdateCheckboxIsOn(frameNode, isOn);
    return frameNode;
}

RefPtr<FrameNode> ToggleModelNG::CreateSwitchFrameNode(int32_t nodeId, bool isOn)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TOGGLE_ETS_TAG, nodeId, AceType::MakeRefPtr<SwitchPattern>());
    UpdateSwitchIsOn(frameNode, isOn);
    return frameNode;
}

RefPtr<FrameNode> ToggleModelNG::CreateButtonFrameNode(int32_t nodeId, bool isOn)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TOGGLE_ETS_TAG, nodeId, AceType::MakeRefPtr<ToggleButtonPattern>());
    UpdateToggleButtonIsOn(frameNode, isOn);
    return frameNode;
}

void ToggleModelNG::ReplaceAllChild(const RefPtr<FrameNode>& oldFrameNode)
{
    auto currentNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    CHECK_NULL_VOID(currentNode);
    const auto& children = oldFrameNode->GetChildren();
    auto switchPattern = oldFrameNode->GetPattern<SwitchPattern>();
    auto checkboxPattern = oldFrameNode->GetPattern<CheckBoxPattern>();
    auto toggleButtonPattern = oldFrameNode->GetPattern<ToggleButtonPattern>();
    for (const auto& child : children) {
        if (!child) {
            continue;
        }
        if (switchPattern && switchPattern->UseContentModifier() && switchPattern->GetBuilderId() == child->GetId()) {
            continue;
        }
        if (checkboxPattern && checkboxPattern->UseContentModifier()) {
            auto modifierNode = checkboxPattern->GetContentModifierNode();
            if (modifierNode && modifierNode->GetId() == child->GetId()) {
                continue;
            }
        }
        if (toggleButtonPattern && toggleButtonPattern->UseContentModifier() &&
            toggleButtonPattern->GetBuilderId() == child->GetId()) {
            continue;
        }
        child->MountToParent(currentNode);
    }
    oldFrameNode->RemoveAllChildInRenderTree();
}

void ToggleModelNG::AddNewChild(const RefPtr<UINode>& parentFrame, int32_t nodeId, int32_t index, ToggleType toggleType)
{
    auto newFrameNode = FrameNode::GetFrameNode(V2::TOGGLE_ETS_TAG, nodeId);
    parentFrame->AddChild(newFrameNode, index);
    CHECK_NULL_VOID(newFrameNode);
    const auto& children = newFrameNode->GetChildren();
    for (const auto& child : children) {
        if (!child) {
            continue;
        }
        auto childNode = AceType::DynamicCast<FrameNode>(child);
        CHECK_NULL_VOID(childNode);
        auto accessibilityProperty = childNode->GetAccessibilityProperty<AccessibilityProperty>();
        CHECK_NULL_VOID(accessibilityProperty);
        if (toggleType == ToggleType::CHECKBOX || toggleType == ToggleType::SWITCH) {
            accessibilityProperty->SetAccessibilityLevel(AccessibilityProperty::Level::NO_STR);
        } else {
            accessibilityProperty->SetAccessibilityLevel(AccessibilityProperty::Level::YES_STR);
        }
    }
    newFrameNode->MarkModifyDone();
}

int32_t ToggleModelNG::RemoveNode(const RefPtr<FrameNode>& childFrameNode, int32_t nodeId)
{
    ElementRegister::GetInstance()->RemoveItemSilently(nodeId);
    auto parentFrame = childFrameNode->GetParent();
    CHECK_NULL_RETURN(parentFrame, 0);
    return parentFrame->RemoveChildAndReturnIndex(childFrameNode);
}

void ToggleModelNG::OnChangeEvent(ChangeEvent&& onChangeEvent)
{
    auto* stack = ViewStackProcessor::GetInstance();
    CHECK_NULL_VOID(stack);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto checkboxPattern = stack->GetMainFrameNodePattern<ToggleCheckBoxPattern>();
    if (checkboxPattern) {
        auto eventHub = frameNode->GetOrCreateEventHub<CheckBoxEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->SetChangeEvent(std::move(onChangeEvent));
        return;
    }
    auto buttonPattern = stack->GetMainFrameNodePattern<ToggleButtonPattern>();
    if (buttonPattern) {
        auto eventHub = frameNode->GetOrCreateEventHub<ToggleButtonEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->SetOnChangeEvent(std::move(onChangeEvent));
        return;
    }
    auto eventHub = frameNode->GetOrCreateEventHub<SwitchEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChangeEvent(std::move(onChangeEvent));
}

void ToggleModelNG::SetResponseRegion(const std::vector<DimensionRect>& responseRegion)
{
    NG::ViewAbstract::SetResponseRegion(responseRegion);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SwitchPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetIsUserSetResponseRegion(true);
}

void ToggleModelNG::SetHoverEffect(HoverEffectType hoverEffect)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SwitchPattern>();
    if (pattern) {
        pattern->SetShowHoverEffect(hoverEffect != HoverEffectType::NONE);
    }
    if (hoverEffect == HoverEffectType::BOARD) {
        return;
    }
    NG::ViewAbstract::SetHoverEffect(hoverEffect);
}

void ToggleModelNG::Pop()
{
    ViewStackProcessor::GetInstance()->PopContainer();
}

void ToggleModelNG::SetPointRadius(const Dimension& switchPointRadius)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto paintProperty = frameNode->GetPaintProperty<SwitchPaintProperty>();
    if (paintProperty) {
        paintProperty->UpdatePointRadius(switchPointRadius);
    }
}

void ToggleModelNG::ResetPointRadius()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto paintProperty = frameNode->GetPaintProperty<SwitchPaintProperty>();
    if (paintProperty) {
        paintProperty->ResetPointRadius();
        paintProperty->UpdatePropertyChangeFlag(PROPERTY_UPDATE_RENDER);
    }
}

void ToggleModelNG::SetPointRadius(FrameNode* frameNode, const Dimension& switchPointRadius)
{
    CHECK_NULL_VOID(frameNode);
    auto paintProperty = frameNode->GetPaintProperty<SwitchPaintProperty>();
    if (paintProperty) {
        paintProperty->UpdatePointRadius(switchPointRadius);
    }
}

void ToggleModelNG::ResetPointRadius(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto paintProperty = frameNode->GetPaintProperty<SwitchPaintProperty>();
    if (paintProperty) {
        paintProperty->ResetPointRadius();
        paintProperty->UpdatePropertyChangeFlag(PROPERTY_UPDATE_RENDER);
    }
}

void ToggleModelNG::SetUnselectedColor(const Color& unselectedColor)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto paintProperty = frameNode->GetPaintProperty<SwitchPaintProperty>();
    if (paintProperty) {
        paintProperty->UpdateUnselectedColor(unselectedColor);
    }
}

void ToggleModelNG::SetUnselectedColorSetByUser(const bool flag)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto paintProperty = frameNode->GetPaintProperty<SwitchPaintProperty>();
    if (paintProperty) {
        paintProperty->UpdateUnselectedColorSetByUser(flag);
    }
}

void ToggleModelNG::SetUnselectedColor(FrameNode* frameNode, const Color& unselectedColor)
{
    CHECK_NULL_VOID(frameNode);
    auto paintProperty = frameNode->GetPaintProperty<SwitchPaintProperty>();
    if (paintProperty) {
        paintProperty->UpdateUnselectedColor(unselectedColor);
    }
}

void ToggleModelNG::SetUnselectedColorSetByUser(FrameNode* frameNode, const bool flag)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(SwitchPaintProperty, UnselectedColorSetByUser, flag, frameNode);
}

void ToggleModelNG::SetTrackBorderRadius(const Dimension& borderRadius)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto paintProperty = frameNode->GetPaintProperty<SwitchPaintProperty>();
    if (paintProperty) {
        paintProperty->UpdateTrackBorderRadius(borderRadius);
    }
}

void ToggleModelNG::ResetTrackBorderRadius()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto paintProperty = frameNode->GetPaintProperty<SwitchPaintProperty>();
    if (paintProperty) {
        paintProperty->ResetTrackBorderRadius();
        paintProperty->UpdatePropertyChangeFlag(PROPERTY_UPDATE_RENDER);
    }
}

void ToggleModelNG::SetTrackBorderRadius(FrameNode* frameNode, const Dimension& borderRadius)
{
    CHECK_NULL_VOID(frameNode);
    auto paintProperty = frameNode->GetPaintProperty<SwitchPaintProperty>();
    if (paintProperty) {
        paintProperty->UpdateTrackBorderRadius(borderRadius);
    }
}

void ToggleModelNG::ResetTrackBorderRadius(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto paintProperty = frameNode->GetPaintProperty<SwitchPaintProperty>();
    if (paintProperty) {
        paintProperty->ResetTrackBorderRadius();
        paintProperty->UpdatePropertyChangeFlag(PROPERTY_UPDATE_RENDER);
    }
}

void ToggleModelNG::SetSelectedColor(FrameNode* frameNode, const std::optional<Color>& selectedColor)
{
    CHECK_NULL_VOID(frameNode);

    auto pipeline = PipelineBase::GetCurrentContextSafely();
    CHECK_NULL_VOID(pipeline);
    Color color;
    if (selectedColor.has_value()) {
        color = selectedColor.value();
    }

    auto checkboxPattern = AceType::DynamicCast<ToggleCheckBoxPattern>(frameNode->GetPattern());
    if (checkboxPattern) {
        if (!selectedColor.has_value()) {
            auto theme = pipeline->GetTheme<CheckboxTheme>(frameNode->GetThemeScopeId());
            CHECK_NULL_VOID(theme);
            color = theme->GetActiveColor();
        }
        CheckBoxModelNG checkBoxModelNG;
        checkBoxModelNG.SetSelectedColor(frameNode, color);
        return;
    }

    auto buttonPattern = AceType::DynamicCast<ToggleButtonPattern>(frameNode->GetPattern());
    if (buttonPattern) {
        if (!selectedColor.has_value()) {
            auto theme = pipeline->GetTheme<ToggleTheme>(frameNode->GetThemeScopeId());
            CHECK_NULL_VOID(theme);
            color = theme->GetCheckedColor();
        }
        ToggleButtonModelNG::SetSelectedColor(frameNode, color);
        return;
    }

    if (!selectedColor.has_value()) {
        auto theme = pipeline->GetTheme<SwitchTheme>(frameNode->GetThemeScopeId());
        CHECK_NULL_VOID(theme);
        color = theme->GetActiveColor();
        ACE_UPDATE_NODE_PAINT_PROPERTY(SwitchPaintProperty, SelectedColorSetByUser, false, frameNode);
    } else {
        ACE_UPDATE_NODE_PAINT_PROPERTY(SwitchPaintProperty, SelectedColorSetByUser, true, frameNode);
    }

    ACE_UPDATE_NODE_PAINT_PROPERTY(SwitchPaintProperty, SelectedColor, color, frameNode);
}

void ToggleModelNG::SetSwitchPointColor(FrameNode* frameNode, const std::optional<Color>& switchPointColor)
{
    CHECK_NULL_VOID(frameNode);
    auto pipeline = PipelineBase::GetCurrentContextSafely();
    CHECK_NULL_VOID(pipeline);
    Color color;
    if (switchPointColor.has_value()) {
        color = switchPointColor.value();
    }

    if (!switchPointColor.has_value()) {
        auto theme = pipeline->GetTheme<SwitchTheme>(frameNode->GetThemeScopeId());
        CHECK_NULL_VOID(theme);
        color = theme->GetPointColor();
    }
    ACE_UPDATE_NODE_PAINT_PROPERTY(SwitchPaintProperty, SwitchPointColor, color, frameNode);
}

void ToggleModelNG::SetSwitchPointColorSetByUser(FrameNode* frameNode, const bool flag)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(SwitchPaintProperty, SwitchPointColorSetByUser, flag, frameNode);
}

void ToggleModelNG::SetBackgroundColor(FrameNode* frameNode, const Color& color)
{
    ToggleButtonModelNG::SetBackgroundColor(frameNode, color);
}

void ToggleModelNG::SetHeight(FrameNode* frameNode, const Dimension& height)
{
    NG::ViewAbstract::SetHeight(frameNode, NG::CalcLength(height));
}

void ToggleModelNG::SetPadding(
    FrameNode* frameNode, const NG::PaddingPropertyF& /*args*/, const NG::PaddingProperty& newArgs)
{
    NG::ViewAbstract::SetPadding(frameNode, newArgs);
}

void ToggleModelNG::SetResponseRegion(FrameNode* frameNode, const std::vector<DimensionRect>& responseRegion)
{
    CHECK_NULL_VOID(frameNode);
    NG::ViewAbstract::SetResponseRegion(frameNode, responseRegion);
    auto pattern = frameNode->GetPattern<SwitchPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetIsUserSetResponseRegion(true);
}

void ToggleModelNG::SetHoverEffect(FrameNode* frameNode, HoverEffectType hoverEffect)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SwitchPattern>();
    if (pattern) {
        pattern->SetShowHoverEffect(hoverEffect != HoverEffectType::NONE);
    }
    if (hoverEffect == HoverEffectType::BOARD) {
        return;
    }
    NG::ViewAbstract::SetHoverEffect(frameNode, hoverEffect);
}

void ToggleModelNG::SetToggleState(FrameNode* frameNode, bool isOn)
{
    CHECK_NULL_VOID(frameNode);
    auto refNode = AceType::Claim(frameNode);
    CHECK_NULL_VOID(refNode);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    if (AceType::InstanceOf<SwitchPattern>(pattern)) {
        UpdateSwitchIsOn(refNode, isOn);
    } else if (AceType::InstanceOf<CheckBoxPattern>(pattern)) {
        UpdateCheckboxIsOn(refNode, isOn);
    } else if (AceType::InstanceOf<ButtonPattern>(pattern)) {
        UpdateToggleButtonIsOn(refNode, isOn);
    }
}

Color ToggleModelNG::GetSelectedColor(FrameNode* frameNode)
{
    Color value;
    ACE_GET_NODE_PAINT_PROPERTY_WITH_DEFAULT_VALUE(
        SwitchPaintProperty, SelectedColor, value, frameNode, Color(DEFAULT_COLOR));
    return value;
}

Color ToggleModelNG::GetSwitchPointColor(FrameNode* frameNode)
{
    Color value;
    ACE_GET_NODE_PAINT_PROPERTY_WITH_DEFAULT_VALUE(
        SwitchPaintProperty, SwitchPointColor, value, frameNode, Color(DEFAULT_COLOR));
    return value;
}

void ToggleModelNG::SetSwitchIsOn(FrameNode* frameNode, bool isOn)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<SwitchEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetCurrentUIState(UI_STATE_SELECTED, isOn);
    ACE_UPDATE_NODE_PAINT_PROPERTY(SwitchPaintProperty, IsOn, isOn, frameNode);
}

void ToggleModelNG::CreateWithColorResourceObj(
    const RefPtr<ResourceObject>& resObj, const ToggleColorType toggleColorType)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    CreateWithResourceObj(frameNode, toggleColorType, resObj);
}

void ToggleModelNG::SetSwitchDefaultColor(FrameNode* frameNode, const ToggleColorType type)
{
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SwitchTheme>();
    CHECK_NULL_VOID(theme);
    Color color;
    switch (type) {
        case ToggleColorType::SELECTED_COLOR:
            color = theme->GetActiveColor();
            ACE_UPDATE_NODE_PAINT_PROPERTY(SwitchPaintProperty, SelectedColor, color, frameNode);
            break;
        case ToggleColorType::SWITCH_POINT_COLOR:
            color = theme->GetPointColor();
            ACE_UPDATE_NODE_PAINT_PROPERTY(SwitchPaintProperty, SwitchPointColor, color, frameNode);
            break;
        case ToggleColorType::UN_SELECTED_COLOR:
            color = theme->GetInactiveColor();
            SetUnselectedColor(frameNode, color);
            break;
        default:
            break;
    }
}

void ToggleModelNG::CreateWithSwitchResourceObj(FrameNode* node, const ToggleColorType toggleColorType,
    const RefPtr<ResourceObject>& resObj, const std::string& key)
{
    CHECK_NULL_VOID(node);
    auto pattern = node->GetPattern<SwitchPattern>();
    CHECK_NULL_VOID(pattern);
    if (!resObj) {
        pattern->RemoveResObj(key);
        return;
    }
    auto&& updateFunc = [toggleColorType, weak = AceType::WeakClaim(node)](const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        CHECK_NULL_VOID(resObj);
        Color result;
        if (!ResourceParseUtils::ParseResColor(resObj, result)) {
            SetSwitchDefaultColor(AceType::RawPtr(frameNode), toggleColorType);
            return;
        }
        switch (toggleColorType) {
            case ToggleColorType::SELECTED_COLOR:
                SetSelectedColor(AceType::RawPtr(frameNode), result);
                break;
            case ToggleColorType::SWITCH_POINT_COLOR:
                SetSwitchPointColor(AceType::RawPtr(frameNode), result);
                break;
            case ToggleColorType::UN_SELECTED_COLOR:
                SetUnselectedColor(AceType::RawPtr(frameNode), result);
                break;
            default:
                break;
        }
        frameNode->MarkModifyDone();
        frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

void ToggleModelNG::SetCheckboxDefaultColor(FrameNode* frameNode, const ToggleColorType type)
{
    if (type != ToggleColorType::SELECTED_COLOR) {
        return;
    }
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<CheckboxTheme>();
    CHECK_NULL_VOID(theme);
    auto color = theme->GetActiveColor();
    ACE_UPDATE_NODE_PAINT_PROPERTY(SwitchPaintProperty, SelectedColor, color, frameNode);
}

void ToggleModelNG::CreateWithCheckBoxResourceObj(FrameNode* node, const ToggleColorType toggleColorType,
    const RefPtr<ResourceObject>& resObj, const std::string& key)
{
    CHECK_NULL_VOID(node);
    auto pattern = node->GetPattern<ToggleCheckBoxPattern>();
    CHECK_NULL_VOID(pattern);
    if (!resObj) {
        pattern->RemoveResObj(key);
        return;
    }
    auto&& updateFunc = [toggleColorType, weak = AceType::WeakClaim(node)](const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        CHECK_NULL_VOID(resObj);
        Color result;
        if (!ResourceParseUtils::ParseResColor(resObj, result)) {
            SetCheckboxDefaultColor(AceType::RawPtr(frameNode), toggleColorType);
            return;
        }
        if (toggleColorType == ToggleColorType::SELECTED_COLOR) {
            SetSelectedColor(AceType::RawPtr(frameNode), result);
            frameNode->MarkModifyDone();
            frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        }
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

void ToggleModelNG::SetButtonDefaultColor(FrameNode* frameNode, const ToggleColorType type)
{
    if (type != ToggleColorType::SELECTED_COLOR) {
        return;
    }
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<ToggleTheme>();
    CHECK_NULL_VOID(theme);
    auto color = theme->GetCheckedColor();
    ACE_UPDATE_NODE_PAINT_PROPERTY(SwitchPaintProperty, SelectedColor, color, frameNode);
}

void ToggleModelNG::CreateWithButtonResourceObj(FrameNode* node, const ToggleColorType toggleColorType,
    const RefPtr<ResourceObject>& resObj, const std::string& key)
{
    CHECK_NULL_VOID(node);
    auto pattern = node->GetPattern<ToggleButtonPattern>();
    CHECK_NULL_VOID(pattern);
    if (!resObj) {
        pattern->RemoveResObj(key);
        return;
    }
    auto&& updateFunc = [toggleColorType, weak = AceType::WeakClaim(node)](const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        CHECK_NULL_VOID(resObj);
        Color result;
        if (!ResourceParseUtils::ParseResColor(resObj, result)) {
            SetButtonDefaultColor(AceType::RawPtr(frameNode), toggleColorType);
            return;
        }
        if (toggleColorType == ToggleColorType::SELECTED_COLOR) {
            SetSelectedColor(AceType::RawPtr(frameNode), result);
            frameNode->MarkModifyDone();
            frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
        }
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

void ToggleModelNG::CreateWithResourceObj(
    const FrameNode* node, const ToggleColorType toggleColorType, const RefPtr<ResourceObject>& resObj)
{
    CHECK_NULL_VOID(node);
    std::string key = "toggle" + ColorTypeToString(toggleColorType);
    CreateWithSwitchResourceObj(const_cast<FrameNode*>(node), toggleColorType, resObj, key);
    CreateWithCheckBoxResourceObj(const_cast<FrameNode*>(node), toggleColorType, resObj, key);
    CreateWithButtonResourceObj(const_cast<FrameNode*>(node), toggleColorType, resObj, key);
}

void ToggleModelNG::CreateWithDimensionVpResourceObj(
    const RefPtr<ResourceObject>& resObj, const ToggleDimensionType toggleDimensionType)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    CreateWithResourceObj(frameNode, toggleDimensionType, resObj);
}

void ToggleModelNG::CreateWithResourceObj(
    FrameNode* node, const ToggleDimensionType toggleDimensionType, const RefPtr<ResourceObject>& resObj)
{
    CHECK_NULL_VOID(node);
    auto pattern = node->GetPattern<SwitchPattern>();
    CHECK_NULL_VOID(pattern);
    std::string key = "toggle" + DimensionTypeToString(toggleDimensionType);
    if (!resObj) {
        pattern->RemoveResObj(key);
        return;
    }
    auto&& updateFunc = [toggleDimensionType, weak = AceType::WeakClaim(node)](const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        CHECK_NULL_VOID(resObj);
        CalcDimension result;
        if (!ResourceParseUtils::ParseResDimensionVpNG(resObj, result, false) && !result.IsNegative()) {
            ResetTrackBorderRadius(AceType::RawPtr(frameNode));
            return;
        }
        switch (toggleDimensionType) {
            case ToggleDimensionType::POINT_RADIUS:
                SetPointRadius(AceType::RawPtr(frameNode), result);
                break;
            case ToggleDimensionType::TRACK_BORDER_RADIUS:
                SetTrackBorderRadius(AceType::RawPtr(frameNode), result);
                break;
            default:
                break;
        }
    };
    pattern->AddResObj(key, resObj, std::move(updateFunc));
}

std::string ToggleModelNG::ColorTypeToString(const ToggleColorType toggleColorType)
{
    std::string rst;
    switch (toggleColorType) {
        case ToggleColorType::SELECTED_COLOR:
            rst = "SelectedColor";
            break;
        case ToggleColorType::SWITCH_POINT_COLOR:
            rst = "SwitchPointColor";
            break;
        case ToggleColorType::UN_SELECTED_COLOR:
            rst = "UnselectedColor";
            break;
        default:
            rst = "Unknown";
            break;
    }
    return rst;
}

std::string ToggleModelNG::DimensionTypeToString(const ToggleDimensionType toggleDimensionType)
{
    std::string rst;
    switch (toggleDimensionType) {
        case ToggleDimensionType::POINT_RADIUS:
            rst = "PointRadius";
            break;
        case ToggleDimensionType::TRACK_BORDER_RADIUS:
            rst = "TrackBorderRadius";
            break;
        default:
            rst = "Unknown";
            break;
    }
    return rst;
}

void ToggleModelNG::UpdateSwitchIsOn(const RefPtr<FrameNode>& frameNode, bool isOn)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<SwitchEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetCurrentUIState(UI_STATE_SELECTED, isOn);
    auto paintProperty = frameNode->GetPaintPropertyPtr<SwitchPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    if (paintProperty->HasIsOn() && paintProperty->GetIsOn().value() != isOn) {
        TAG_LOGI(AceLogTag::ACE_SELECT_COMPONENT, "switch update isOn %{public}d", isOn);
    }
    paintProperty->UpdateIsOn(isOn);
}

void ToggleModelNG::UpdateCheckboxIsOn(const RefPtr<FrameNode>& frameNode, bool isOn)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<CheckBoxEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetCurrentUIState(UI_STATE_SELECTED, isOn);
    ACE_UPDATE_NODE_PAINT_PROPERTY(CheckBoxPaintProperty, CheckBoxSelect, isOn, frameNode);
}

void ToggleModelNG::UpdateToggleButtonIsOn(const RefPtr<FrameNode>& frameNode, bool isOn)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<ToggleButtonEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetCurrentUIState(UI_STATE_SELECTED, isOn);
    ACE_UPDATE_NODE_PAINT_PROPERTY(ToggleButtonPaintProperty, IsOn, isOn, frameNode);
}

bool ToggleModelNG::GetSwitchIsOn(FrameNode* frameNode)
{
    bool value = false;
    CHECK_NULL_RETURN(frameNode, value);
    ACE_GET_NODE_PAINT_PROPERTY_WITH_DEFAULT_VALUE(SwitchPaintProperty, IsOn, value, frameNode, value);
    return value;
}

Color ToggleModelNG::GetUnselectedColor(FrameNode* frameNode)
{
    Color value;
    ACE_GET_NODE_PAINT_PROPERTY_WITH_DEFAULT_VALUE(
        SwitchPaintProperty, UnselectedColor, value, frameNode, Color(DEFAULT_COLOR));
    return value;
}

void ToggleModelNG::SetIsUserSetMargin(bool isUserSet)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    SetIsUserSetMargin(frameNode, isUserSet);
}

void ToggleModelNG::SetIsUserSetMargin(FrameNode* frameNode, bool isUserSet)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    if (AceType::InstanceOf<SwitchPattern>(pattern)) {
        auto switchPattern = AceType::DynamicCast<SwitchPattern>(pattern);
        CHECK_NULL_VOID(switchPattern);
        switchPattern->SetIsUserSetMargin(isUserSet);
    } else if (AceType::InstanceOf<CheckBoxPattern>(pattern)) {
        auto checkboxPattern = AceType::DynamicCast<CheckBoxPattern>(pattern);
        CHECK_NULL_VOID(checkboxPattern);
        checkboxPattern->SetIsUserSetMargin(isUserSet);
    }
}
} // namespace OHOS::Ace::NG
