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

#include "core/components_ng/pattern/stepper/stepper_pattern.h"

#include <algorithm>

#include "base/i18n/localization.h"
#include "core/components_ng/pattern/stepper/stepper_item_layout_property.h"
#include "core/components_ng/pattern/stepper/stepper_node.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"

namespace OHOS::Ace::NG {

void StepperPattern::OnModifyDone()
{
    auto hostNode = DynamicCast<StepperNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto stepperHub = hostNode->GetEventHub<StepperEventHub>();
    CHECK_NULL_VOID(stepperHub);
    auto leftButtonNode =
        DynamicCast<FrameNode>(hostNode->GetChildAtIndex(hostNode->GetChildIndexById(hostNode->GetLeftButtonId())));
    CHECK_NULL_VOID(leftButtonNode);
    auto leftGestureHub = leftButtonNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(leftGestureHub);
    auto rightButtonNode =
        DynamicCast<FrameNode>(hostNode->GetChildAtIndex(hostNode->GetChildIndexById(hostNode->GetRightButtonId())));
    CHECK_NULL_VOID(rightButtonNode);
    auto rightGestureHub = rightButtonNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(rightGestureHub);
    auto swiperNode =
        DynamicCast<FrameNode>(hostNode->GetChildAtIndex(hostNode->GetChildIndexById(hostNode->GetSwiperId())));
    CHECK_NULL_VOID(swiperNode);
    auto stepperLayoutProperty = hostNode->GetLayoutProperty<StepperLayoutProperty>();
    index_ = static_cast<int32_t>(stepperLayoutProperty->GetIndex().value_or(0));
    maxIndex_ = TotalCount();
    InitButtonClickEvent(leftGestureHub, rightGestureHub, swiperNode);
    UpdateButtonText();
}

void StepperPattern::InitButtonClickEvent(const RefPtr<GestureEventHub>& leftGestureHub,
    const RefPtr<GestureEventHub>& rightGestureHub, const RefPtr<FrameNode>& swiperNode)
{
    if (!leftClickEvent_) {
        auto clickEvent = [swiperNode, weak = WeakClaim(this)](const GestureEvent& info) {
            auto stepperPattern = weak.Upgrade();
            if (stepperPattern) {
                stepperPattern->HandlingButtonClickEvent(true, swiperNode);
            }
            auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
            if (swiperPattern) {
                auto swiperController = swiperPattern->GetSwiperController();
                swiperController->ShowPrevious();
                stepperPattern->UpdateButtonText();
            }
        };
        leftGestureHub->RemoveClickEvent(leftClickEvent_);
        leftClickEvent_ = MakeRefPtr<ClickEvent>(std::move(clickEvent));
        leftGestureHub->AddClickEvent(leftClickEvent_);
    }

    if (!rightClickEvent_) {
        auto clickEvent = [swiperNode, weak = WeakClaim(this)](const GestureEvent& info) {
            auto stepperPattern = weak.Upgrade();
            if (stepperPattern) {
                stepperPattern->HandlingButtonClickEvent(false, swiperNode);
            }
            auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
            if (swiperPattern) {
                auto swiperController = swiperPattern->GetSwiperController();
                swiperController->ShowNext();
                stepperPattern->UpdateButtonText();
            }
        };
        rightGestureHub->RemoveClickEvent(rightClickEvent_);
        rightClickEvent_ = MakeRefPtr<ClickEvent>(std::move(clickEvent));
        rightGestureHub->AddClickEvent(rightClickEvent_);
    }
}

int32_t StepperPattern::TotalCount() const
{
    auto hostNode = DynamicCast<StepperNode>(GetHost());
    CHECK_NULL_RETURN(hostNode, 0);
    auto swiperNode =
        DynamicCast<FrameNode>(hostNode->GetChildAtIndex(hostNode->GetChildIndexById(hostNode->GetSwiperId())));
    CHECK_NULL_RETURN(swiperNode, 0);
    return swiperNode->TotalChildCount();
}

void StepperPattern::HandlingButtonClickEvent(bool isLeft, const RefPtr<FrameNode>& swiperNode)
{
    CHECK_NULL_VOID(swiperNode);
    index_ = swiperNode->GetPattern<SwiperPattern>()->GetCurrentIndex();
    auto StepperItemNode = DynamicCast<FrameNode>(swiperNode->GetChildAtIndex(static_cast<int32_t>(index_)));
    CHECK_NULL_VOID(StepperItemNode);

    auto stepperHub = GetEventHub<StepperEventHub>();
    CHECK_NULL_VOID(stepperHub);
    if (!isLeft && index_ == maxIndex_) {
        stepperHub->FireFinishEvent();
    }
    auto labelStatus =
        StepperItemNode->GetLayoutProperty<StepperItemLayoutProperty>()->GetLabelStatus().value_or("normal");
    if (!isLeft && labelStatus == "skip") {
        stepperHub->FireSkipEvent();
    }
    if (!isLeft && index_ < maxIndex_) {
        stepperHub->FireChangeEvent(index_, std::clamp<int32_t>(index_ + 1, 0, maxIndex_));
        stepperHub->FireNextEvent(index_, std::clamp<int32_t>(index_ + 1, 0, maxIndex_));
    }
    if (isLeft && index_ > 0) {
        stepperHub->FireChangeEvent(index_, std::clamp<int32_t>(index_ - 1, 0, maxIndex_));
        stepperHub->FirePreviousEvent(index_, std::clamp<int32_t>(index_ - 1, 0, maxIndex_));
    }
}

void StepperPattern::UpdateButtonText()
{
    auto hostNode = DynamicCast<StepperNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto leftButtonNode =
        DynamicCast<FrameNode>(hostNode->GetChildAtIndex(hostNode->GetChildIndexById(hostNode->GetLeftButtonId())));
    CHECK_NULL_VOID(leftButtonNode);
    auto rightButtonNode =
        DynamicCast<FrameNode>(hostNode->GetChildAtIndex(hostNode->GetChildIndexById(hostNode->GetRightButtonId())));
    CHECK_NULL_VOID(rightButtonNode);
    auto leftTextNode = DynamicCast<FrameNode>(leftButtonNode->GetChildAtIndex(0));
    CHECK_NULL_VOID(leftTextNode);
    auto rightTextNode = DynamicCast<FrameNode>(rightButtonNode->GetChildAtIndex(0));
    CHECK_NULL_VOID(rightTextNode);
    auto swiperNode =
        DynamicCast<FrameNode>(hostNode->GetChildAtIndex(hostNode->GetChildIndexById(hostNode->GetSwiperId())));
    CHECK_NULL_VOID(swiperNode);
    // Get the LayoutProperty of the current StepperItemNode
    index_ = swiperNode->GetPattern<SwiperPattern>()->GetCurrentIndex();
    auto StepperItemNode = DynamicCast<FrameNode>(swiperNode->GetChildAtIndex(static_cast<int32_t>(index_)));
    CHECK_NULL_VOID(StepperItemNode);
    auto stepperItemLayoutProperty = StepperItemNode->GetLayoutProperty<StepperItemLayoutProperty>();
    // Set the text of the leftButton
    std::string buttonBackText = "< " + Localization::GetInstance()->GetEntryLetters("stepper.back");
    auto leftLabel = stepperItemLayoutProperty->GetLeftLabel().value_or(index_ == 0 ? "" : buttonBackText);
    leftTextNode->GetLayoutProperty<TextLayoutProperty>()->UpdateContent(leftLabel);
    leftTextNode->MarkModifyDone();
    // Set the text of the rightButton
    std::string buttonStartText = Localization::GetInstance()->GetEntryLetters("stepper.start");
    std::string buttonNextText = Localization::GetInstance()->GetEntryLetters("stepper.next") + " >";
    auto rightLabel =
        stepperItemLayoutProperty->GetRightLabel().value_or(index_ == maxIndex_ ? buttonStartText : buttonNextText);
    rightTextNode->GetLayoutProperty<TextLayoutProperty>()->UpdateContent(rightLabel);
    rightTextNode->MarkModifyDone();

    hostNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

} // namespace OHOS::Ace::NG