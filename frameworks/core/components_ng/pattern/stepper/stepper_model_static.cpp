/*
 * Copyright (c) 2025-2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/stepper/stepper_model_static.h"

#include "core/interfaces/native/node/node_swiper_custom_modifier.h"
#include "core/components_ng/pattern/stepper/stepper_constants.h"
#include "core/components_ng/pattern/stepper/stepper_node.h"

namespace OHOS::Ace::NG {
namespace {
void SwipeToSwiperNode(const RefPtr<FrameNode>& swiperNode, int32_t index)
{
    CHECK_NULL_VOID(swiperNode);
    auto modifier = GetSwiperCustomModifier();
    CHECK_NULL_VOID(modifier);
    modifier->swipeTo(reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(swiperNode)), index);
}

void SetSwiperCurveLinear(const RefPtr<FrameNode>& swiperNode)
{
    CHECK_NULL_VOID(swiperNode);
    auto modifier = GetSwiperCustomModifier();
    CHECK_NULL_VOID(modifier);
    modifier->setCurveLinear(reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(swiperNode)));
}
} // namespace

RefPtr<FrameNode> StepperModelStatic::CreateFrameNode(int32_t nodeId)
{
    auto stepperNode = StepperNode::GetOrCreateStepperNode(
        STEPPER_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<StepperPattern>(); });
    return stepperNode;
}

void StepperModelStatic::SetIndex(FrameNode* frameNode, const std::optional<int32_t>& index)
{
    CHECK_NULL_VOID(frameNode);
    auto stepperNode = AceType::DynamicCast<StepperNode>(frameNode);
    CHECK_NULL_VOID(stepperNode);
    bool hasSwiperNode = stepperNode->HasSwiperNode();
    auto swiperId = stepperNode->GetSwiperId();
    RefPtr<FrameNode> swiperNode;
    uint32_t value = index.value_or(0);
    if (!hasSwiperNode) {
        swiperNode = CreateSwiperChild(swiperId, value);
        swiperNode->MountToParent(Referenced::Claim(stepperNode));
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(StepperLayoutProperty, Index, value, frameNode);
    } else {
        swiperNode = AceType::DynamicCast<FrameNode>(
            stepperNode->GetChildAtIndex(stepperNode->GetChildIndexById(stepperNode->GetSwiperId())));
        CHECK_NULL_VOID(swiperNode);
        SwipeToSwiperNode(swiperNode, value);
    }
    SetSwiperCurveLinear(swiperNode);
}

void StepperModelStatic::SetOnFinish(FrameNode* frameNode, RoutineCallbackEvent&& eventOnFinish)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<StepperEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetFinishEvent(std::move(eventOnFinish));
}

void StepperModelStatic::SetOnSkip(FrameNode* frameNode, RoutineCallbackEvent&& eventOnSkip)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<StepperEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetSkipEvent(std::move(eventOnSkip));
}

void StepperModelStatic::SetOnChange(FrameNode* frameNode, IndexCallbackEvent&& eventOnChange)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<StepperEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetChangeEvent(std::move(eventOnChange));
}

void StepperModelStatic::SetOnNext(FrameNode* frameNode, IndexCallbackEvent&& eventOnNext)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<StepperEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetNextEvent(std::move(eventOnNext));
}

void StepperModelStatic::SetOnPrevious(FrameNode* frameNode, IndexCallbackEvent&& eventOnPrevious)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<StepperEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetPreviousEvent(std::move(eventOnPrevious));
}

RefPtr<FrameNode> StepperModelStatic::CreateSwiperChild(int32_t id, uint32_t index)
{
    auto modifier = GetSwiperCustomModifier();
    CHECK_NULL_RETURN(modifier, nullptr);
    return AceType::Claim(reinterpret_cast<FrameNode*>(modifier->createStepperSwiperNode(id, index)));
}

void StepperModelStatic::SetOnChangeEvent(FrameNode* frameNode, IndexChangeEvent&& onChangeEvent)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<StepperEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChangeEvent(std::move(onChangeEvent));
}
} // namespace OHOS::Ace::NG
