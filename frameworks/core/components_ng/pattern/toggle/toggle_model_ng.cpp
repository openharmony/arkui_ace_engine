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

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components/toggle/toggle_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/toggle_button_model_ng.h"
#include "core/components_ng/pattern/button/toggle_button_pattern.h"
#include "core/components_ng/pattern/checkbox/checkbox_model_ng.h"
#include "core/components_ng/pattern/checkbox/checkbox_pattern.h"
#include "core/components_ng/pattern/toggle/switch_paint_property.h"
#include "core/components_ng/pattern/toggle/switch_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {

void ToggleModelNG::Create(NG::ToggleType toggleType, bool isOn)
{
    auto* stack = ViewStackProcessor::GetInstance();
    int nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::TOGGLE_ETS_TAG, nodeId);
    auto childFrameNode = FrameNode::GetFrameNode(V2::TOGGLE_ETS_TAG, nodeId);
    if (!childFrameNode) {
        switch (toggleType) {
            case ToggleType::CHECKBOX: {
                CheckBoxModelNG checkBoxModelNG;
                CreateCheckbox(nodeId);
                checkBoxModelNG.SetSelect(isOn);
                break;
            }
            case ToggleType::SWITCH: {
                CreateSwitch(nodeId);
                SetSwitchSelected(childFrameNode, isOn);
                ACE_UPDATE_PAINT_PROPERTY(SwitchPaintProperty, IsOn, isOn);
                break;
            }
            case ToggleType::BUTTON: {
                CreateButton(nodeId);
                ToggleButtonModelNG::SetIsOn(isOn);
                break;
            }
            default:
                break;
        }
        return;
    }
    auto pattern = childFrameNode->GetPattern();
    if (AceType::InstanceOf<CheckBoxPattern>(pattern)) {
        if (toggleType == ToggleType::CHECKBOX) {
            stack->Push(childFrameNode);
            CheckBoxModelNG checkBoxModelNG;
            checkBoxModelNG.SetSelect(isOn);
            return;
        }
        if (toggleType == ToggleType::SWITCH) {
            auto parentFrame = childFrameNode->GetParent();
            CHECK_NULL_VOID(parentFrame);
            auto index = RemoveNode(childFrameNode, nodeId);
            childFrameNode->SetUndefinedNodeId();
            CreateSwitch(nodeId);
            SetSwitchSelected(childFrameNode, isOn);
            ACE_UPDATE_PAINT_PROPERTY(SwitchPaintProperty, IsOn, isOn);
            AddNewChild(parentFrame, nodeId, index);
            return;
        }
        auto parentFrame = childFrameNode->GetParent();
        CHECK_NULL_VOID(parentFrame);
        auto index = RemoveNode(childFrameNode, nodeId);
        childFrameNode->SetUndefinedNodeId();
        CreateButton(nodeId);
        ToggleButtonModelNG::SetIsOn(isOn);
        AddNewChild(parentFrame, nodeId, index);
        return;
    }
    if (AceType::InstanceOf<SwitchPattern>(pattern)) {
        if (toggleType == ToggleType::SWITCH) {
            SetSwitchSelected(childFrameNode, isOn);
            stack->Push(childFrameNode);
            ACE_UPDATE_PAINT_PROPERTY(SwitchPaintProperty, IsOn, isOn);
            return;
        }
        if (toggleType == ToggleType::CHECKBOX) {
            auto parentFrame = childFrameNode->GetParent();
            CHECK_NULL_VOID(parentFrame);
            auto index = RemoveNode(childFrameNode, nodeId);
            childFrameNode->SetUndefinedNodeId();
            CheckBoxModelNG checkBoxModelNG;
            CreateCheckbox(nodeId);
            checkBoxModelNG.SetSelect(isOn);
            AddNewChild(parentFrame, nodeId, index);
            return;
        }
        auto parentFrame = childFrameNode->GetParent();
        CHECK_NULL_VOID(parentFrame);
        auto index = RemoveNode(childFrameNode, nodeId);
        childFrameNode->SetUndefinedNodeId();
        CreateButton(nodeId);
        ToggleButtonModelNG::SetIsOn(isOn);
        AddNewChild(parentFrame, nodeId, index);
        return;
    }
    if (AceType::InstanceOf<ToggleButtonPattern>(pattern)) {
        if (toggleType == ToggleType::BUTTON) {
            stack->Push(childFrameNode);
            ToggleButtonModelNG::SetIsOn(isOn);
            return;
        }
        if (toggleType == ToggleType::CHECKBOX) {
            auto parentFrame = childFrameNode->GetParent();
            CHECK_NULL_VOID(parentFrame);
            auto index = RemoveNode(childFrameNode, nodeId);
            childFrameNode->SetUndefinedNodeId();
            CheckBoxModelNG checkBoxModelNG;
            CreateCheckbox(nodeId);
            checkBoxModelNG.SetSelect(isOn);
            AddNewChild(parentFrame, nodeId, index);
            return;
        }
        auto parentFrame = childFrameNode->GetParent();
        CHECK_NULL_VOID(parentFrame);
        auto index = RemoveNode(childFrameNode, nodeId);
        childFrameNode->SetUndefinedNodeId();
        CreateSwitch(nodeId);
        SetSwitchSelected(childFrameNode, isOn);
        ACE_UPDATE_PAINT_PROPERTY(SwitchPaintProperty, IsOn, isOn);
        AddNewChild(parentFrame, nodeId, index);
    }
}
RefPtr<FrameNode> ToggleModelNG::CreateFrameNode(int32_t nodeId, ToggleType toggleType, bool isOn)
{
    RefPtr<FrameNode> frameNode = nullptr;
    switch (toggleType) {
        case ToggleType::CHECKBOX: {
            frameNode = CreateCheckboxFrameNode(nodeId, isOn);
            break;
        }
        case ToggleType::SWITCH: {
            frameNode = CreateSwitchFrameNode(nodeId, isOn);
            break;
        }
        case ToggleType::BUTTON: {
            frameNode = CreateButtonFrameNode(nodeId, isOn);
            break;
        }
        default:
            break;
    }
    return frameNode;
}
void ToggleModelNG::SetSwitchSelected(RefPtr<FrameNode>& childFrameNode, bool isOn)
{
    if (!childFrameNode) {
        auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        CHECK_NULL_VOID(frameNode);
        childFrameNode = frameNode;
    }
    auto eventHub = childFrameNode->GetEventHub<SwitchEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetCurrentUIState(UI_STATE_SELECTED, isOn);
}

void ToggleModelNG::SetSelectedColor(const std::optional<Color>& selectedColor)
{
    auto* stack = ViewStackProcessor::GetInstance();
    CHECK_NULL_VOID(stack);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    Color color;
    if (selectedColor.has_value()) {
        color = selectedColor.value();
    }

    auto checkboxPattern = stack->GetMainFrameNodePattern<CheckBoxPattern>();
    if (checkboxPattern) {
        if (!selectedColor.has_value()) {
            auto theme = pipeline->GetTheme<CheckboxTheme>();
            CHECK_NULL_VOID(theme);
            color = theme->GetActiveColor();
        }
        CheckBoxModelNG checkBoxModelNG;
        checkBoxModelNG.SetSelectedColor(color);
        return;
    }
    auto buttonPattern = stack->GetMainFrameNodePattern<ToggleButtonPattern>();
    if (buttonPattern) {
        if (!selectedColor.has_value()) {
            auto theme = pipeline->GetTheme<ToggleTheme>();
            CHECK_NULL_VOID(theme);
            color = theme->GetCheckedColor();
        }
        ToggleButtonModelNG::SetSelectedColor(color);
        return;
    }

    if (!selectedColor.has_value()) {
        auto theme = pipeline->GetTheme<SwitchTheme>();
        CHECK_NULL_VOID(theme);
        color = theme->GetActiveColor();
    }
    ACE_UPDATE_PAINT_PROPERTY(SwitchPaintProperty, SelectedColor, color);
}

void ToggleModelNG::SetSwitchPointColor(const Color& switchPointColor)
{
    ACE_UPDATE_PAINT_PROPERTY(SwitchPaintProperty, SwitchPointColor, switchPointColor);
}
void ToggleModelNG::OnChange(ChangeEvent&& onChange)
{
    auto* stack = ViewStackProcessor::GetInstance();
    CHECK_NULL_VOID(stack);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto checkboxPattern = stack->GetMainFrameNodePattern<CheckBoxPattern>();
    if (checkboxPattern) {
        auto eventHub = frameNode->GetEventHub<CheckBoxEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->SetOnChange(std::move(onChange));
        return;
    }
    auto buttonPattern = stack->GetMainFrameNodePattern<ToggleButtonPattern>();
    if (buttonPattern) {
        auto eventHub = frameNode->GetEventHub<ToggleButtonEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->SetOnChange(std::move(onChange));
        return;
    }
    auto eventHub = frameNode->GetEventHub<SwitchEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChange(std::move(onChange));
}

void ToggleModelNG::SetWidth(const Dimension& width)
{
    NG::ViewAbstract::SetWidth(NG::CalcLength(width));
}

void ToggleModelNG::SetHeight(const Dimension& height)
{
    NG::ViewAbstract::SetHeight(NG::CalcLength(height));
}

void ToggleModelNG::SetBackgroundColor(const Color& color)
{
    ToggleButtonModelNG::SetBackgroundColor(color);
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
    auto frameNode = FrameNode::CreateFrameNode(V2::CHECKBOX_ETS_TAG, nodeId, AceType::MakeRefPtr<CheckBoxPattern>());
    CHECK_NULL_RETURN(frameNode, nullptr);
    CheckBoxModelNG checkBoxModelNG;
    checkBoxModelNG.SetSelect(isOn);
    return frameNode;
}

RefPtr<FrameNode> ToggleModelNG::CreateSwitchFrameNode(int32_t nodeId, bool isOn)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TOGGLE_ETS_TAG, nodeId, AceType::MakeRefPtr<SwitchPattern>());
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<SwitchEventHub>();
    CHECK_NULL_RETURN(eventHub, nullptr);
    eventHub->SetCurrentUIState(UI_STATE_SELECTED, isOn);
    auto paintProperty = frameNode->GetPaintProperty<SwitchPaintProperty>();
    CHECK_NULL_RETURN(paintProperty, nullptr);
    paintProperty->UpdateIsOn(isOn);
    return frameNode;
}

RefPtr<FrameNode> ToggleModelNG::CreateButtonFrameNode(int32_t nodeId, bool isOn)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TOGGLE_ETS_TAG, nodeId, AceType::MakeRefPtr<ToggleButtonPattern>());
    CHECK_NULL_RETURN(frameNode, nullptr);
    ToggleButtonModelNG::SetIsOn(isOn);
    return frameNode;
}
void ToggleModelNG::CreateCheckbox(int32_t nodeId)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::CHECKBOX_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<CheckBoxPattern>(); });
    stack->Push(frameNode);
}

void ToggleModelNG::CreateSwitch(int32_t nodeId)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::TOGGLE_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<SwitchPattern>(); });
    stack->Push(frameNode);
}

void ToggleModelNG::CreateButton(int32_t nodeId)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::TOGGLE_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<ToggleButtonPattern>(); });
    stack->Push(frameNode);
}

void ToggleModelNG::AddNewChild(const RefPtr<UINode>& parentFrame, int32_t nodeId, int32_t index)
{
    auto newFrameNode = FrameNode::GetFrameNode(V2::TOGGLE_ETS_TAG, nodeId);
    parentFrame->AddChild(newFrameNode, index);
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
    auto checkboxPattern = stack->GetMainFrameNodePattern<CheckBoxPattern>();
    if (checkboxPattern) {
        auto eventHub = frameNode->GetEventHub<CheckBoxEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->SetChangeEvent(std::move(onChangeEvent));
        return;
    }
    auto buttonPattern = stack->GetMainFrameNodePattern<ToggleButtonPattern>();
    if (buttonPattern) {
        auto eventHub = frameNode->GetEventHub<ToggleButtonEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->SetOnChangeEvent(std::move(onChangeEvent));
        return;
    }
    auto eventHub = frameNode->GetEventHub<SwitchEventHub>();
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
    // button is a container but switch or checkbox is not, container should pop container
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto switchPattern = frameNode->GetPattern<SwitchPattern>();
    if (switchPattern) {
        ViewStackProcessor::GetInstance()->Pop();
        return;
    }
    auto checkboxPattern = frameNode->GetPattern<CheckBoxPattern>();
    if (checkboxPattern) {
        ViewStackProcessor::GetInstance()->Pop();
        return;
    }
    ViewStackProcessor::GetInstance()->PopContainer();
}

void ToggleModelNG::SetSelectedColor(FrameNode* frameNode, const std::optional<Color>& selectedColor)
{
    CHECK_NULL_VOID(frameNode);

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    Color color;
    if (selectedColor.has_value()) {
        color = selectedColor.value();
    }

    auto checkboxPattern = AceType::DynamicCast<CheckBoxPattern>(frameNode->GetPattern());
    if (checkboxPattern) {
        if (!selectedColor.has_value()) {
            auto theme = pipeline->GetTheme<CheckboxTheme>();
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
            auto theme = pipeline->GetTheme<ToggleTheme>();
            CHECK_NULL_VOID(theme);
            color = theme->GetCheckedColor();
        }
        ToggleButtonModelNG::SetSelectedColor(frameNode, color);
        return;
    }

    if (!selectedColor.has_value()) {
        auto theme = pipeline->GetTheme<SwitchTheme>();
        CHECK_NULL_VOID(theme);
        color = theme->GetActiveColor();
    }

    ACE_UPDATE_NODE_PAINT_PROPERTY(SwitchPaintProperty, SelectedColor, color, frameNode);
}

void ToggleModelNG::SetSwitchPointColor(FrameNode* frameNode, const Color& switchPointColor)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(SwitchPaintProperty, SwitchPointColor, switchPointColor, frameNode);
}

void ToggleModelNG::SetBackgroundColor(FrameNode* frameNode, const Color& color)
{
    ToggleButtonModelNG::SetBackgroundColor(frameNode, color);
}
} // namespace OHOS::Ace::NG
