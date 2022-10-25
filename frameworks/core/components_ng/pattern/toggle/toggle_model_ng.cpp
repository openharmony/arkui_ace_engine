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

#include "core/components_ng/pattern/toggle/toggle_model_ng.h"

#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
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
    int nodeId = (stack == nullptr ? 0 : stack->ClaimNodeId());
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
            return;
        }
        if (toggleType == ToggleType::SWITCH) {
            auto parentFrame = childFrameNode->GetParent();
            CHECK_NULL_VOID(parentFrame);
            auto index = RemoveNode(childFrameNode, nodeId);
            CreateSwitch(nodeId);
            ACE_UPDATE_PAINT_PROPERTY(SwitchPaintProperty, IsOn, isOn);
            AddNewChild(parentFrame, nodeId, index);
            return;
        }
        auto parentFrame = childFrameNode->GetParent();
        CHECK_NULL_VOID(parentFrame);
        auto index = RemoveNode(childFrameNode, nodeId);
        CreateButton(nodeId);
        ToggleButtonModelNG::SetIsOn(isOn);
        AddNewChild(parentFrame, nodeId, index);
        return;
    }
    if (AceType::InstanceOf<SwitchPattern>(pattern)) {
        if (toggleType == ToggleType::SWITCH) {
            stack->Push(childFrameNode);
            return;
        }
        if (toggleType == ToggleType::CHECKBOX) {
            auto parentFrame = childFrameNode->GetParent();
            CHECK_NULL_VOID(parentFrame);
            auto index = RemoveNode(childFrameNode, nodeId);
            CheckBoxModelNG checkBoxModelNG;
            CreateCheckbox(nodeId);
            checkBoxModelNG.SetSelect(isOn);
            AddNewChild(parentFrame, nodeId, index);
            return;
        }
        auto parentFrame = childFrameNode->GetParent();
        CHECK_NULL_VOID(parentFrame);
        auto index = RemoveNode(childFrameNode, nodeId);
        CreateButton(nodeId);
        ToggleButtonModelNG::SetIsOn(isOn);
        AddNewChild(parentFrame, nodeId, index);
        return;
    }
    if (AceType::InstanceOf<ToggleButtonPattern>(pattern)) {
        if (toggleType == ToggleType::BUTTON) {
            stack->Push(childFrameNode);
            return;
        }
        if (toggleType == ToggleType::CHECKBOX) {
            auto parentFrame = childFrameNode->GetParent();
            CHECK_NULL_VOID(parentFrame);
            auto index = RemoveNode(childFrameNode, nodeId);
            CheckBoxModelNG checkBoxModelNG;
            CreateCheckbox(nodeId);
            checkBoxModelNG.SetSelect(isOn);
            AddNewChild(parentFrame, nodeId, index);
            return;
        }
        auto parentFrame = childFrameNode->GetParent();
        CHECK_NULL_VOID(parentFrame);
        auto index = RemoveNode(childFrameNode, nodeId);
        CreateSwitch(nodeId);
        ACE_UPDATE_PAINT_PROPERTY(SwitchPaintProperty, IsOn, isOn);
        AddNewChild(parentFrame, nodeId, index);
    }
}

void ToggleModelNG::SetSelectedColor(const Color& selectedColor)
{
    auto* stack = ViewStackProcessor::GetInstance();
    CHECK_NULL_VOID(stack);
    auto checkboxPattern = stack->GetMainFrameNodePattern<CheckBoxPattern>();
    if (checkboxPattern) {
        CheckBoxModelNG checkBoxModelNG;
        checkBoxModelNG.SetSelectedColor(selectedColor);
        return;
    }
    auto buttonPattern = stack->GetMainFrameNodePattern<ToggleButtonPattern>();
    if (buttonPattern) {
        ToggleButtonModelNG::SetSelectedColor(selectedColor);
        return;
    }

    ACE_UPDATE_PAINT_PROPERTY(SwitchPaintProperty, SelectedColor, selectedColor);
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

void ToggleModelNG::SetWidth(const Dimension& width) {}

void ToggleModelNG::SetHeight(const Dimension& height) {}

void ToggleModelNG::SetBackgroundColor(const Color& color)
{
    ToggleButtonModelNG::SetBackgroundColor(color);
}

bool ToggleModelNG::IsToggle()
{
    return false;
}

void ToggleModelNG::SetPadding(const NG::PaddingPropertyF& args) {}

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
    childFrameNode->SetRemoveSilently(true);
    return parentFrame->RemoveChildAndReturnIndex(childFrameNode);
}

} // namespace OHOS::Ace::NG