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

#include "core/components_ng/pattern/rating/rating_accessibility_property.h"

#include "core/components_ng/pattern/rating/rating_pattern.h"

namespace OHOS::Ace::NG {
AccessibilityValue RatingAccessibilityProperty::GetAccessibilityValue() const
{
    AccessibilityValue accessibilityValue;
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, accessibilityValue);
    auto ratingLayoutProperty = frameNode->GetLayoutProperty<NG::RatingLayoutProperty>();
    CHECK_NULL_RETURN(ratingLayoutProperty, accessibilityValue);
    accessibilityValue.max = ratingLayoutProperty->GetStars().value_or(0);
    auto ratingRenderProperty = frameNode->GetPaintProperty<NG::RatingRenderProperty>();
    CHECK_NULL_RETURN(ratingRenderProperty, accessibilityValue);
    accessibilityValue.current = ratingRenderProperty->GetRatingScore().value_or(0);
    accessibilityValue.min = 0;
    return accessibilityValue;
}

std::string RatingAccessibilityProperty::GetText() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, "");
    auto ratingRenderProperty = frameNode->GetPaintProperty<NG::RatingRenderProperty>();
    CHECK_NULL_RETURN(ratingRenderProperty, "");
    return std::to_string(ratingRenderProperty->GetRatingScore().value_or(0));
}

bool RatingAccessibilityProperty::IsEditable() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, false);
    auto ratingLayoutProperty = frameNode->GetLayoutProperty<NG::RatingLayoutProperty>();
    CHECK_NULL_RETURN(ratingLayoutProperty, false);
    bool indicator = ratingLayoutProperty->GetIndicator().value_or(false);
    return !indicator;
}
} // namespace OHOS::Ace::NG