/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/stepper/stepper_item_model_static.h"

#include "core/components_ng/pattern/stepper/stepper_item_pattern.h"

namespace OHOS::Ace::NG {

RefPtr<FrameNode> StepperItemModelStatic::CreateFrameNode(int32_t nodeId)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::STEPPER_ITEM_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<StepperItemPattern>(); });
    return frameNode;
}

void StepperItemModelStatic::SetNextLabel(FrameNode* frameNode, const std::string& rightLabel)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(StepperItemLayoutProperty, RightLabel, rightLabel, frameNode);
}

void StepperItemModelStatic::ResetNextLabel(FrameNode* frameNode)
{
    ACE_RESET_NODE_LAYOUT_PROPERTY(StepperItemLayoutProperty, RightLabel, frameNode);
}

void StepperItemModelStatic::SetPrevLabel(FrameNode* frameNode, const std::string& leftLabel)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(StepperItemLayoutProperty, LeftLabel, leftLabel, frameNode);
}

void StepperItemModelStatic::ResetPrevLabel(FrameNode* frameNode)
{
    ACE_RESET_NODE_LAYOUT_PROPERTY(StepperItemLayoutProperty, LeftLabel, frameNode);
}

void StepperItemModelStatic::SetStatus(FrameNode* frameNode, const std::optional<std::string>& labelStatus)
{
    CHECK_NULL_VOID(frameNode);
    if (labelStatus.has_value()) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(StepperItemLayoutProperty, LabelStatus, labelStatus.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(StepperItemLayoutProperty, LabelStatus, frameNode);
    }
}

void StepperItemModelStatic::ResetStatus(FrameNode* frameNode)
{
    ACE_RESET_NODE_LAYOUT_PROPERTY(StepperItemLayoutProperty, LabelStatus, frameNode);
}

const std::map<StepperItemModelStatic::ItemState, std::string> StepperItemModelStatic::ITEM_STATE = {
    {StepperItemModelStatic::ItemState::NORMAL, "normal"},
    {StepperItemModelStatic::ItemState::DISABLED, "disabled"},
    {StepperItemModelStatic::ItemState::WAITING, "waiting"},
    {StepperItemModelStatic::ItemState::SKIP, "skip"}
};
} // namespace OHOS::Ace::NG