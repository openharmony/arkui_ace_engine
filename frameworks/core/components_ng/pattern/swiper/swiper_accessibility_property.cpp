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

#include "core/components_ng/pattern/swiper/swiper_accessibility_property.h"

#include "core/components_ng/pattern/swiper/swiper_pattern.h"

namespace OHOS::Ace::NG {
int32_t SwiperAccessibilityProperty::GetCurrentIndex() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, -1);
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    CHECK_NULL_RETURN(swiperPattern, -1);
    return swiperPattern->TotalCount() < 1 ? -1 : swiperPattern->GetCurrentIndex();
}

int32_t SwiperAccessibilityProperty::GetBeginIndex() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, -1);
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    CHECK_NULL_RETURN(swiperPattern, -1);
    return swiperPattern->TotalCount() < 1 ? -1 : swiperPattern->GetStartIndex();
}

int32_t SwiperAccessibilityProperty::GetEndIndex() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, -1);
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    CHECK_NULL_RETURN(swiperPattern, -1);
    return swiperPattern->TotalCount() < 1 ? -1 : swiperPattern->GetEndIndex();
}

AccessibilityValue SwiperAccessibilityProperty::GetAccessibilityValue() const
{
    AccessibilityValue result;
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, result);
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    CHECK_NULL_RETURN(swiperPattern, result);

    result.min = 0;
    result.max = swiperPattern->TotalCount() < 1 ? 0 : swiperPattern->TotalCount() - 1;
    result.current = swiperPattern->GetCurrentIndex();
    return result;
}

bool SwiperAccessibilityProperty::IsScrollable() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, false);
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    CHECK_NULL_RETURN(swiperPattern, false);
    auto swiperLayoutProperty = frameNode->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_RETURN(swiperLayoutProperty, false);
    if (swiperLayoutProperty->GetDisableSwipeValue(false)) {
        return false;
    }
    bool isLoop = swiperLayoutProperty->GetLoop().value_or(true);
    if (!isLoop && swiperPattern->TotalCount() <= 1) {
        return false;
    }
    return true;
}

int32_t SwiperAccessibilityProperty::GetCollectionItemCounts() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, -1);
    auto swiperPattern = frameNode->GetPattern<SwiperPattern>();
    CHECK_NULL_RETURN(swiperPattern, -1);
    return swiperPattern->TotalCount();
}

void SwiperAccessibilityProperty::SetSpecificSupportAction()
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_VOID(frameNode);
    auto swiperLayoutProperty = frameNode->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(swiperLayoutProperty);
    bool isLoop = swiperLayoutProperty->GetLoop().value_or(true);
    if (IsScrollable()) {
        if (!isLoop) {
            if (GetCurrentIndex() > 0) {
                AddSupportAction(AceAction::ACTION_SCROLL_BACKWARD);
            }

            if (GetCurrentIndex() < GetCollectionItemCounts() - 1) {
                AddSupportAction(AceAction::ACTION_SCROLL_FORWARD);
            }
        } else {
            AddSupportAction(AceAction::ACTION_SCROLL_FORWARD);
            AddSupportAction(AceAction::ACTION_SCROLL_BACKWARD);
        }
    }
}
} // namespace OHOS::Ace::NG
