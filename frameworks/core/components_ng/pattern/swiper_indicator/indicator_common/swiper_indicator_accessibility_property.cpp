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

#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_indicator_accessibility_property.h"

#include "core/components_ng/pattern/swiper/swiper_pattern.h"

namespace OHOS::Ace::NG {
int32_t SwiperIndicatorAccessibilityProperty::GetCurrentIndex() const
{
    auto swiper = GetSwiperNode();
    CHECK_NULL_RETURN(swiper, -1);
    auto swiperAccessibilityProperty = swiper->GetAccessibilityProperty<SwiperAccessibilityProperty>();
    CHECK_NULL_RETURN(swiperAccessibilityProperty, -1);
    return swiperAccessibilityProperty->GetCurrentIndex();
}

int32_t SwiperIndicatorAccessibilityProperty::GetBeginIndex() const
{
    auto swiper = GetSwiperNode();
    CHECK_NULL_RETURN(swiper, -1);
    auto swiperAccessibilityProperty = swiper->GetAccessibilityProperty<SwiperAccessibilityProperty>();
    CHECK_NULL_RETURN(swiperAccessibilityProperty, -1);
    return swiperAccessibilityProperty->GetBeginIndex();
}

int32_t SwiperIndicatorAccessibilityProperty::GetEndIndex() const
{
    auto swiper = GetSwiperNode();
    CHECK_NULL_RETURN(swiper, -1);
    auto swiperAccessibilityProperty = swiper->GetAccessibilityProperty<SwiperAccessibilityProperty>();
    CHECK_NULL_RETURN(swiperAccessibilityProperty, -1);
    return swiperAccessibilityProperty->GetEndIndex();
}

int32_t SwiperIndicatorAccessibilityProperty::GetCollectionItemCounts() const
{
    auto swiper = GetSwiperNode();
    CHECK_NULL_RETURN(swiper, -1);
    auto swiperPattern = swiper->GetPattern<SwiperPattern>();
    CHECK_NULL_RETURN(swiperPattern, -1);
    return swiperPattern->RealTotalCount();
}

std::string SwiperIndicatorAccessibilityProperty::GetAccessibilityText() const
{
    auto swiper = GetSwiperNode();
    CHECK_NULL_RETURN(swiper, "");
    auto swiperAccessibilityProperty = swiper->GetAccessibilityProperty<SwiperAccessibilityProperty>();
    CHECK_NULL_RETURN(swiperAccessibilityProperty, "");
    return swiperAccessibilityProperty->GetAccessibilityText();
}

AccessibilityValue SwiperIndicatorAccessibilityProperty::GetAccessibilityValue() const
{
    AccessibilityValue result;
    auto swiper = GetSwiperNode();
    CHECK_NULL_RETURN(swiper, result);
    auto swiperAccessibilityProperty = swiper->GetAccessibilityProperty<SwiperAccessibilityProperty>();
    CHECK_NULL_RETURN(swiperAccessibilityProperty, result);
    return swiperAccessibilityProperty->GetAccessibilityValue();
}

RefPtr<FrameNode> SwiperIndicatorAccessibilityProperty::GetSwiperNode() const
{
    auto host = host_.Upgrade();
    CHECK_NULL_RETURN(host, nullptr);
    auto swiperNode = host->GetParent();
    CHECK_NULL_RETURN(swiperNode, nullptr);
    return DynamicCast<FrameNode>(swiperNode);
}
} // namespace OHOS::Ace::NG