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

#include "core/components_ng/pattern/stepper/stepper_item_model_ng.h"

#include "core/components_ng/pattern/stepper/stepper_item_pattern.h"

namespace OHOS::Ace::NG {

void StepperItemModelNG::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::STEPPER_ITEM_ETS_TAG, nodeId);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::STEPPER_ITEM_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<StepperItemPattern>(); });
    stack->Push(frameNode);
}

RefPtr<FrameNode> StepperItemModelNG::CreateFrameNode(int32_t nodeId)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::STEPPER_ITEM_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<StepperItemPattern>(); });
    return frameNode;
}

void StepperItemModelNG::SetPrevLabel(const std::string& leftLabel)
{
    ACE_UPDATE_LAYOUT_PROPERTY(StepperItemLayoutProperty, LeftLabel, leftLabel);
}

void StepperItemModelNG::SetNextLabel(const std::string& rightLabel)
{
    ACE_UPDATE_LAYOUT_PROPERTY(StepperItemLayoutProperty, RightLabel, rightLabel);
}

void StepperItemModelNG::SetStatus(const std::string& labelStatus)
{
    ACE_UPDATE_LAYOUT_PROPERTY(StepperItemLayoutProperty, LabelStatus, labelStatus);
}

void StepperItemModelNG::ResetPrevLabel()
{
    ACE_RESET_LAYOUT_PROPERTY(StepperItemLayoutProperty, LeftLabel);
}

void StepperItemModelNG::ResetNextLabel()
{
    ACE_RESET_LAYOUT_PROPERTY(StepperItemLayoutProperty, RightLabel);
}

void StepperItemModelNG::SetNextLabel(FrameNode* frameNode, const std::string& rightLabel)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(StepperItemLayoutProperty, RightLabel, rightLabel, frameNode);
}

void StepperItemModelNG::ResetNextLabel(FrameNode* frameNode)
{
    ACE_RESET_NODE_LAYOUT_PROPERTY(StepperItemLayoutProperty, RightLabel, frameNode);
}

void StepperItemModelNG::SetPrevLabel(FrameNode* frameNode, const std::string& leftLabel)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(StepperItemLayoutProperty, LeftLabel, leftLabel, frameNode);
}

void StepperItemModelNG::ResetPrevLabel(FrameNode* frameNode)
{
    ACE_RESET_NODE_LAYOUT_PROPERTY(StepperItemLayoutProperty, LeftLabel, frameNode);
}

void StepperItemModelNG::SetStatus(FrameNode* frameNode, const std::optional<std::string>& labelStatus)
{
    CHECK_NULL_VOID(frameNode);
    if (labelStatus.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(StepperItemLayoutProperty, LabelStatus, labelStatus.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(StepperItemLayoutProperty, LabelStatus, frameNode);
    }
}

void StepperItemModelNG::ResetStatus(FrameNode* frameNode)
{
    ACE_RESET_NODE_LAYOUT_PROPERTY(StepperItemLayoutProperty, LabelStatus, frameNode);
}

const std::map<StepperItemModelNG::ItemState, std::string> StepperItemModelNG::ITEM_STATE = {
    {StepperItemModelNG::ItemState::NORMAL, "normal"},
    {StepperItemModelNG::ItemState::DISABLED, "disabled"},
    {StepperItemModelNG::ItemState::WAITING, "waiting"},
    {StepperItemModelNG::ItemState::SKIP, "skip"}
};
} // namespace OHOS::Ace::NG