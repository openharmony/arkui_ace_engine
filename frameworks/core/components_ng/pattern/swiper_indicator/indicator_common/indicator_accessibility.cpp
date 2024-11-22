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

namespace OHOS::Ace::NG {
int32_t IndicatorAccessibilityProperty::GetCurrentIndex() const
{
    auto indicatorPattern = GetIndicatorPattern();
    CHECK_NULL_RETURN(indicatorPattern, -1);
    return indicatorPattern->GetCurrentIndex();
}

int32_t IndicatorAccessibilityProperty::GetBeginIndex() const
{
    auto indicatorPattern = GetIndicatorPattern();
    CHECK_NULL_RETURN(indicatorPattern, -1);
    return 0;
}

int32_t IndicatorAccessibilityProperty::GetEndIndex() const
{
    auto indicatorPattern = GetIndicatorPattern();
    CHECK_NULL_RETURN(indicatorPattern, -1);
    return indicatorPattern->RealTotalCount();
}

int32_t IndicatorAccessibilityProperty::GetCollectionItemCounts() const
{
    auto indicatorPattern = GetIndicatorPattern();
    CHECK_NULL_RETURN(indicatorPattern, -1);
    return indicatorPattern->RealTotalCount();
}

std::string IndicatorAccessibilityProperty::GetAccessibilityText() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, "");
    auto indicatorAccessibilityProperty = frameNode->GetAccessibilityProperty<IndicatorAccessibilityProperty>();
    CHECK_NULL_RETURN(indicatorAccessibilityProperty, "");
    return indicatorAccessibilityProperty->GetAccessibilityText();
}

AccessibilityValue IndicatorAccessibilityProperty::GetAccessibilityValue() const
{
    AccessibilityValue result;
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, result);
    auto indicatorAccessibilityProperty = frameNode->GetAccessibilityProperty<IndicatorAccessibilityProperty>();
    CHECK_NULL_RETURN(indicatorAccessibilityProperty, result);
    return indicatorAccessibilityProperty->GetAccessibilityValue();
}

RefPtr<FrameNode> IndicatorAccessibilityProperty::GetSwiperNode() const
{
    auto indicatorPattern = GetIndicatorPattern();
    CHECK_NULL_RETURN(indicatorPattern, nullptr);
    return indicatorPattern->GetSwiperNode();
}

RefPtr<SwiperIndicatorPattern> IndicatorAccessibilityProperty::GetIndicatorPattern() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, nullptr);
    return frameNode->GetPattern<SwiperIndicatorPattern>();
}

} // namespace OHOS::Ace::NG
