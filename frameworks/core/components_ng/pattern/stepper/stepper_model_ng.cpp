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

#include "core/components_ng/pattern/stepper/stepper_model_ng.h"

#include "core/components_ng/pattern/stepper/stepper_node.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"

namespace OHOS::Ace::NG {

void StepperModelNG::Create(uint32_t index)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::STEPPER_ETS_TAG, nodeId);
    auto stepperNode = StepperNode::GetOrCreateStepperNode(
        V2::STEPPER_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<StepperPattern>(); });
    stack->Push(stepperNode);
    bool hasSwiperNode = stepperNode->HasSwiperNode();
    auto swiperId = stepperNode->GetSwiperId();
    RefPtr<FrameNode> swiperNode;
    if (!hasSwiperNode) {
        swiperNode = CreateSwiperChild(swiperId, index);
        swiperNode->MountToParent(stepperNode);
        ACE_UPDATE_LAYOUT_PROPERTY(StepperLayoutProperty, Index, index);
    } else {
        swiperNode = AceType::DynamicCast<FrameNode>(
            stepperNode->GetChildAtIndex(stepperNode->GetChildIndexById(stepperNode->GetSwiperId())));
        CHECK_NULL_VOID(swiperNode);
        auto swiperController = swiperNode->GetPattern<SwiperPattern>()->GetSwiperController();
        swiperController->SwipeTo(index);
    }
    auto swiperPaintProperty = swiperNode->GetPaintProperty<SwiperPaintProperty>();
    if (swiperPaintProperty) {
        swiperPaintProperty->UpdateCurve(Curves::LINEAR);
    }
}

void StepperModelNG::SetOnFinish(RoutineCallbackEvent&& eventOnFinish)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<StepperEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetFinishEvent(std::move(eventOnFinish));
}

void StepperModelNG::SetOnSkip(RoutineCallbackEvent&& eventOnSkip)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<StepperEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetSkipEvent(std::move(eventOnSkip));
}

void StepperModelNG::SetOnChange(IndexCallbackEvent&& eventOnChange)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<StepperEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetChangeEvent(std::move(eventOnChange));
}

void StepperModelNG::SetOnNext(IndexCallbackEvent&& eventOnNext)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<StepperEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetNextEvent(std::move(eventOnNext));
}

void StepperModelNG::SetOnPrevious(IndexCallbackEvent&& eventOnPrevious)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<StepperEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetPreviousEvent(std::move(eventOnPrevious));
}

RefPtr<FrameNode> StepperModelNG::CreateSwiperChild(int32_t id, uint32_t index)
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

void StepperModelNG::SetOnChangeEvent(IndexChangeEvent&& onChangeEvent)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetOrCreateEventHub<StepperEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChangeEvent(std::move(onChangeEvent));
}
} // namespace OHOS::Ace::NG
