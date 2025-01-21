/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/swiper_indicator/indicator_common/indicator_accessibility.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/indicator_pattern.h"

namespace OHOS::Ace::NG {
int32_t IndicatorAccessibilityProperty::GetCurrentIndex() const
{
    CHECK_NULL_RETURN(!GetSwiperNode(), SwiperIndicatorAccessibilityProperty::GetCurrentIndex());

    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, -1);
    auto indicatorPattern = frameNode->GetPattern<IndicatorPattern>();
    CHECK_NULL_RETURN(indicatorPattern, -1);
    return indicatorPattern->GetCurrentIndex();
}

int32_t IndicatorAccessibilityProperty::GetBeginIndex() const
{
    CHECK_NULL_RETURN(!GetSwiperNode(), SwiperIndicatorAccessibilityProperty::GetBeginIndex());
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, -1);
    auto indicatorPattern = frameNode->GetPattern<IndicatorPattern>();
    CHECK_NULL_RETURN(indicatorPattern, -1);
    return 0;
}

int32_t IndicatorAccessibilityProperty::GetEndIndex() const
{
    CHECK_NULL_RETURN(!GetSwiperNode(), SwiperIndicatorAccessibilityProperty::GetEndIndex());
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, -1);
    auto indicatorPattern = frameNode->GetPattern<IndicatorPattern>();
    CHECK_NULL_RETURN(indicatorPattern, -1);
    return indicatorPattern->RealTotalCount() - 1;
}

int32_t IndicatorAccessibilityProperty::GetCollectionItemCounts() const
{
    CHECK_NULL_RETURN(!GetSwiperNode(), SwiperIndicatorAccessibilityProperty::GetCollectionItemCounts());
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, -1);
    auto indicatorPattern = frameNode->GetPattern<IndicatorPattern>();
    CHECK_NULL_RETURN(indicatorPattern, -1);
    return indicatorPattern->RealTotalCount();
}

AccessibilityValue IndicatorAccessibilityProperty::GetAccessibilityValue() const
{
    CHECK_NULL_RETURN(!GetSwiperNode(), SwiperIndicatorAccessibilityProperty::GetAccessibilityValue());
    AccessibilityValue result;
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, result);
    auto indicatorPattern = frameNode->GetPattern<IndicatorPattern>();
    CHECK_NULL_RETURN(indicatorPattern, result);
    result.min = 0;
    result.max = indicatorPattern->RealTotalCount() < 1 ? 0 : indicatorPattern->RealTotalCount() - 1;
    result.current = indicatorPattern->GetCurrentIndex();
    return result;
}

RefPtr<FrameNode> IndicatorAccessibilityProperty::GetSwiperNode() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto indicatorPattern = frameNode->GetPattern<IndicatorPattern>();
    CHECK_NULL_RETURN(indicatorPattern, nullptr);
    return indicatorPattern->GetSwiperNode();
}

} // namespace OHOS::Ace::NG
