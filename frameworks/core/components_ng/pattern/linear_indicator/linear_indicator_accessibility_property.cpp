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

#include "core/components_ng/pattern/linear_indicator/linear_indicator_accessibility_property.h"

#include "core/components_ng/pattern/linear_indicator/linear_indicator_pattern.h"

namespace OHOS::Ace::NG {
int32_t LinearIndicatorAccessibilityProperty::GetCurrentIndex() const
{
    auto pattern = GetLinearIndicatorPattern();
    CHECK_NULL_RETURN(pattern, 0);
    auto controller = pattern->GetController();
    CHECK_NULL_RETURN(controller, 0);
    return controller->Index();
}

int32_t LinearIndicatorAccessibilityProperty::GetBeginIndex() const
{
    return 0;
}

int32_t LinearIndicatorAccessibilityProperty::GetEndIndex() const
{
    int32_t count = GetCollectionItemCounts();
    if (count > 0) {
        return count - 1;
    } else {
        return 0;
    }
}

int32_t LinearIndicatorAccessibilityProperty::GetCollectionItemCounts() const
{
    auto pattern = GetLinearIndicatorPattern();
    CHECK_NULL_RETURN(pattern, 0);
    auto layoutProperty = pattern->GetLayoutProperty<LinearIndicatorLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, 0);
    return layoutProperty->GetProgressCount().value_or(0);
}

AccessibilityValue LinearIndicatorAccessibilityProperty::GetAccessibilityValue() const
{
    AccessibilityValue result;
    result.min = GetBeginIndex();
    result.max = GetEndIndex();
    result.current = GetCurrentIndex();
    return result;
}

RefPtr<LinearIndicatorPattern> LinearIndicatorAccessibilityProperty::GetLinearIndicatorPattern() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, nullptr);
    return frameNode->GetPattern<LinearIndicatorPattern>();
}

} // namespace OHOS::Ace::NG
