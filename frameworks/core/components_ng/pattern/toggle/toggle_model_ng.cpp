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
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/toggle_button_model_ng.h"
#include "core/components_ng/pattern/button/toggle_button_pattern.h"
#include "core/components_ng/pattern/checkbox/checkbox_model_ng.h"
#include "core/components_ng/pattern/checkbox/checkbox_pattern.h"
#include "core/components_ng/pattern/toggle/switch_paint_property.h"
#include "core/components_ng/pattern/toggle/switch_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG {

void ToggleModelNG::Create(NG::ToggleType toggleType, bool isOn)
{
    if (previousToggleType_ == ToggleType::NONE) {
        switch (toggleType) {
            case ToggleType::CHECKBOX: {
                CheckBoxModelNG checkBoxModelNG;
                previousNodeId_ = checkBoxModelNG.Create(std::nullopt, std::nullopt, V2::CHECKBOX_ETS_TAG);
                checkBoxModelNG.SetSelect(isOn);
                previousToggleType_ = ToggleType::CHECKBOX;
                break;
            }
            case ToggleType::SWITCH: {
                auto* stack = ViewStackProcessor::GetInstance();
                int32_t nodeId = (stack == nullptr ? 0 : stack->ClaimNodeId());
                auto frameNode = FrameNode::GetOrCreateFrameNode(
                    V2::TOGGLE_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<SwitchPattern>(); });
                stack->Push(frameNode);
                ACE_UPDATE_PAINT_PROPERTY(SwitchPaintProperty, IsOn, isOn);
                previousToggleType_ = ToggleType::SWITCH;
                previousNodeId_ = nodeId;
                break;
            }
            case ToggleType::BUTTON:
                previousNodeId_ = ToggleButtonModelNG::Create(V2::TOGGLE_ETS_TAG);
                ToggleButtonModelNG::SetIsOn(isOn);
                previousToggleType_ = ToggleType::BUTTON;
                break;
            default:
                break;
        }
    } else if (previousToggleType_ != toggleType) {
        auto childFrameNode = FrameNode::GetFrameNode(V2::TOGGLE_ETS_TAG, previousNodeId_);
        CHECK_NULL_VOID(childFrameNode);
        ElementRegister::GetInstance()->RemoveItemSilently(previousNodeId_);
        auto parentFrame = childFrameNode->GetParent();
        childFrameNode->SetRemoveSilently(true);
        CHECK_NULL_VOID(parentFrame);
        auto index = parentFrame->RemoveChildAndReturnIndex(childFrameNode);
        switch (toggleType) {
            case ToggleType::CHECKBOX: {
                CheckBoxModelNG checkBoxModelNG;
                previousNodeId_ = checkBoxModelNG.Create(std::nullopt, std::nullopt, V2::CHECKBOX_ETS_TAG);
                checkBoxModelNG.SetSelect(isOn);
                auto newFrameNode = FrameNode::GetFrameNode(V2::CHECKBOX_ETS_TAG, previousNodeId_);
                parentFrame->AddChild(newFrameNode, index);
                newFrameNode->MarkModifyDone();
                previousToggleType_ = ToggleType::CHECKBOX;
                break;
            }
            case ToggleType::SWITCH: {
                auto* stack = ViewStackProcessor::GetInstance();
                int32_t nodeId = (stack == nullptr ? 0 : stack->ClaimNodeId());
                auto frameNode = FrameNode::GetOrCreateFrameNode(
                    V2::TOGGLE_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<SwitchPattern>(); });
                stack->Push(frameNode);
                ACE_UPDATE_PAINT_PROPERTY(SwitchPaintProperty, IsOn, isOn);
                previousNodeId_ = nodeId;
                parentFrame->AddChild(frameNode, index);
                frameNode->MarkModifyDone();
                previousToggleType_ = ToggleType::SWITCH;
                break;
            }
            case ToggleType::BUTTON: {
                previousNodeId_ = ToggleButtonModelNG::Create(V2::TOGGLE_ETS_TAG);
                ToggleButtonModelNG::SetIsOn(isOn);
                auto newFrameNode = FrameNode::GetFrameNode(V2::CHECKBOX_ETS_TAG, previousNodeId_);
                parentFrame->AddChild(newFrameNode, index);
                newFrameNode->MarkModifyDone();
                previousToggleType_ = ToggleType::BUTTON;
                break;
            }
            default:
                break;
        }
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

} // namespace OHOS::Ace::NG