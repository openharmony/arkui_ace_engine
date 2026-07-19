/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/stepper/stepper_accessibility_property.h"

#include "core/interfaces/native/node/node_swiper_custom_modifier.h"
#include "core/components_ng/pattern/stepper/stepper_node.h"
#include "core/components_ng/pattern/swiper/swiper_layout_property.h"

namespace OHOS::Ace::NG {
namespace {
RefPtr<FrameNode> GetSwiperNode(const RefPtr<StepperNode>& frameNode)
{
    CHECK_NULL_RETURN(frameNode, nullptr);
    return AceType::DynamicCast<FrameNode>(
        frameNode->GetChildAtIndex(frameNode->GetChildIndexById(frameNode->GetSwiperId())));
}

int32_t GetSwiperTotalCount(const RefPtr<FrameNode>& swiperNode)
{
    CHECK_NULL_RETURN(swiperNode, -1);
    auto swiperModifier = GetSwiperCustomModifier();
    CHECK_NULL_RETURN(swiperModifier, -1);
    return swiperModifier->getTotalCount(reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(swiperNode)));
}
} // namespace

int32_t StepperAccessibilityProperty::GetCurrentIndex() const
{
    auto frameNode = AceType::DynamicCast<StepperNode>(host_.Upgrade());
    CHECK_NULL_RETURN(frameNode, -1);
    auto stepperPattern = frameNode->GetPattern<StepperPattern>();
    CHECK_NULL_RETURN(stepperPattern, -1);
    auto swiperNode = GetSwiperNode(frameNode);
    CHECK_NULL_RETURN(swiperNode, -1);
    return GetSwiperTotalCount(swiperNode) < 1 ? -1 : stepperPattern->GetCurrentIndex();
}

int32_t StepperAccessibilityProperty::GetBeginIndex() const
{
    auto frameNode = AceType::DynamicCast<StepperNode>(host_.Upgrade());
    CHECK_NULL_RETURN(frameNode, -1);
    auto swiperNode = GetSwiperNode(frameNode);
    CHECK_NULL_RETURN(swiperNode, -1);
    return GetSwiperTotalCount(swiperNode) < 1 ? -1 : 0;
}

int32_t StepperAccessibilityProperty::GetEndIndex() const
{
    auto frameNode = AceType::DynamicCast<StepperNode>(host_.Upgrade());
    CHECK_NULL_RETURN(frameNode, -1);
    auto swiperNode = GetSwiperNode(frameNode);
    CHECK_NULL_RETURN(swiperNode, -1);
    auto totalCount = GetSwiperTotalCount(swiperNode);
    return totalCount < 1 ? -1 : totalCount - 1;
}

bool StepperAccessibilityProperty::IsScrollable() const
{
    auto frameNode = AceType::DynamicCast<StepperNode>(host_.Upgrade());
    CHECK_NULL_RETURN(frameNode, false);
    auto swiperNode = GetSwiperNode(frameNode);
    CHECK_NULL_RETURN(swiperNode, false);
    auto swiperLayoutProperty = swiperNode->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(swiperLayoutProperty, false);
    bool isLoop = swiperLayoutProperty->GetLoop().value_or(true);
    return (!isLoop && GetSwiperTotalCount(swiperNode) <= 1) ? false : true;
}

int32_t StepperAccessibilityProperty::GetCollectionItemCounts() const
{
    auto frameNode = AceType::DynamicCast<StepperNode>(host_.Upgrade());
    CHECK_NULL_RETURN(frameNode, -1);
    auto swiperNode = GetSwiperNode(frameNode);
    CHECK_NULL_RETURN(swiperNode, -1);
    return GetSwiperTotalCount(swiperNode);
}

void StepperAccessibilityProperty::SetSpecificSupportAction()
{
    auto frameNode = AceType::DynamicCast<StepperNode>(host_.Upgrade());
    CHECK_NULL_VOID(frameNode);
    auto swiperNode = GetSwiperNode(frameNode);
    CHECK_NULL_VOID(swiperNode);
    auto swiperLayoutProperty = swiperNode->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(swiperLayoutProperty);
    bool isLoop = swiperLayoutProperty->GetLoop().value_or(true);
    if (IsScrollable()) {
        if (!isLoop) {
            if (GetCurrentIndex() > GetBeginIndex()) {
                AddSupportAction(AceAction::ACTION_SCROLL_BACKWARD);
            }
            if (GetCurrentIndex() < GetEndIndex()) {
                AddSupportAction(AceAction::ACTION_SCROLL_FORWARD);
            }
        } else {
            AddSupportAction(AceAction::ACTION_SCROLL_FORWARD);
            AddSupportAction(AceAction::ACTION_SCROLL_BACKWARD);
        }
    }
}
} // namespace OHOS::Ace::NG
