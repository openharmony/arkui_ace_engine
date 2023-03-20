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

#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/stepper/stepper_node.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"

namespace OHOS::Ace::NG {
int32_t StepperAccessibilityProperty::GetCurrentIndex() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, -1);
    auto stepperPattern = frameNode->GetPattern<StepperPattern>();
    CHECK_NULL_RETURN(stepperPattern, -1);
    return stepperPattern->GetCurrentIndex();
}

int32_t StepperAccessibilityProperty::GetBeginIndex() const
{
    auto frameNode = DynamicCast<StepperNode>(host_.Upgrade());
    CHECK_NULL_RETURN(frameNode, -1);
    auto swiperNode =
        DynamicCast<FrameNode>(frameNode->GetChildAtIndex(frameNode->GetChildIndexById(frameNode->GetSwiperId())));
    CHECK_NULL_RETURN(swiperNode, -1);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_RETURN(swiperPattern, -1);
    int32_t totalCount = swiperPattern->TotalCount();
    if (totalCount > 0) {
        return 0;
    }
    return -1;
}

int32_t StepperAccessibilityProperty::GetEndIndex() const
{
    auto frameNode = DynamicCast<StepperNode>(host_.Upgrade());
    CHECK_NULL_RETURN(frameNode, -1);
    auto swiperNode =
        DynamicCast<FrameNode>(frameNode->GetChildAtIndex(frameNode->GetChildIndexById(frameNode->GetSwiperId())));
    CHECK_NULL_RETURN(swiperNode, -1);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_RETURN(swiperPattern, -1);
    return swiperPattern->TotalCount() - 1;
}

bool StepperAccessibilityProperty::IsScrollable() const
{
    auto frameNode = DynamicCast<StepperNode>(host_.Upgrade());
    CHECK_NULL_RETURN(frameNode, false);
    auto swiperNode =
        DynamicCast<FrameNode>(frameNode->GetChildAtIndex(frameNode->GetChildIndexById(frameNode->GetSwiperId())));
    CHECK_NULL_RETURN(swiperNode, false);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_RETURN(swiperPattern, false);
    return swiperPattern->TotalCount() > 1;
}

int32_t StepperAccessibilityProperty::GetCollectionItemCounts() const
{
    auto frameNode = DynamicCast<StepperNode>(host_.Upgrade());
    CHECK_NULL_RETURN(frameNode, -1);
    auto swiperNode =
        DynamicCast<FrameNode>(frameNode->GetChildAtIndex(frameNode->GetChildIndexById(frameNode->GetSwiperId())));
    CHECK_NULL_RETURN(swiperNode, -1);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_RETURN(swiperPattern, -1);
    return swiperPattern->TotalCount();
}
} // namespace OHOS::Ace::NG
