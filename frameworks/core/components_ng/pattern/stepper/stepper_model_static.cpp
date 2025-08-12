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

#include "core/components_ng/pattern/stepper/stepper_model_static.h"

#include "core/components_ng/pattern/stepper/stepper_node.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"

namespace OHOS::Ace::NG {

RefPtr<FrameNode> StepperModelStatic::CreateFrameNode(int32_t nodeId)
{
    auto stepperNode = StepperNode::GetOrCreateStepperNode(
        V2::STEPPER_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<StepperPattern>(); });
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
    uint32_t value = static_cast<uint32_t>(index.value_or(0));
    if (!hasSwiperNode) {
        swiperNode = CreateSwiperChild(swiperId, value);
        swiperNode->MountToParent(Referenced::Claim(stepperNode));
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(StepperLayoutProperty, Index, value, frameNode);
    } else {
        swiperNode = AceType::DynamicCast<FrameNode>(
            stepperNode->GetChildAtIndex(stepperNode->GetChildIndexById(stepperNode->GetSwiperId())));
        CHECK_NULL_VOID(swiperNode);
        auto swiperController = swiperNode->GetPattern<SwiperPattern>()->GetSwiperController();
        swiperController->SwipeTo(value);
    }
    auto swiperPaintProperty = swiperNode->GetPaintProperty<SwiperPaintProperty>();
    if (swiperPaintProperty) {
        swiperPaintProperty->UpdateCurve(Curves::LINEAR);
    }
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
    auto swiperNode =
        FrameNode::GetOrCreateFrameNode(V2::SWIPER_ETS_TAG, id, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    auto swiperPaintProperty = swiperNode->GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_RETURN(swiperPaintProperty, nullptr);
    swiperPaintProperty->UpdateEdgeEffect(EdgeEffect::NONE);
    auto swiperLayoutProperty = swiperNode->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(swiperLayoutProperty, nullptr);
    swiperLayoutProperty->UpdateDisableSwipe(true);
    swiperLayoutProperty->UpdateLoop(false);
    swiperLayoutProperty->UpdateCachedCount(0);
    swiperLayoutProperty->UpdateIndex(static_cast<int32_t>(index));
    swiperLayoutProperty->UpdateShowIndicator(false);
    swiperNode->MarkModifyDone();
    return swiperNode;
}

void StepperModelStatic::SetOnChangeEvent(FrameNode* frameNode, IndexChangeEvent&& onChangeEvent)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<StepperEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChangeEvent(std::move(onChangeEvent));
}
} // namespace OHOS::Ace::NG
