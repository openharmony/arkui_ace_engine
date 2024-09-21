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

#include "core/components_ng/pattern/slider/slider_accessibility_property.h"

#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/slider/slider_paint_property.h"

namespace OHOS::Ace::NG {
std::string SliderAccessibilityProperty::GetText() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, "");
    auto sliderProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_RETURN(sliderProperty, "");
    return std::to_string(sliderProperty->GetValue().value_or(0));
}

AccessibilityValue SliderAccessibilityProperty::GetAccessibilityValue() const
{
    AccessibilityValue result;
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, result);
    auto sliderProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_RETURN(sliderProperty, result);
    result.min = sliderProperty->GetMin().value_or(0);
    result.max = sliderProperty->GetMax().value_or(100.0f);
    result.current = sliderProperty->GetValue().value_or(0);
    return result;
}

void SliderAccessibilityProperty::SetSpecificSupportAction()
{
    auto value = GetAccessibilityValue();
    if (value.current < value.max) {
        AddSupportAction(AceAction::ACTION_SCROLL_FORWARD);
    }
    if (value.min < value.current) {
        AddSupportAction(AceAction::ACTION_SCROLL_BACKWARD);
    }
}
} // namespace OHOS::Ace::NG
