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

#include "core/components_ng/pattern/badge/badge_accessibility_property.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/badge/badge_layout_property.h"

namespace OHOS::Ace::NG {
std::string BadgeAccessibilityProperty::GetText() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, "");
    auto badgeLayoutProperty = frameNode->GetLayoutProperty<NG::BadgeLayoutProperty>();
    CHECK_NULL_RETURN(badgeLayoutProperty, "");
    auto badgeCount = badgeLayoutProperty->GetBadgeCount();
    if (badgeCount.has_value()) {
        return std::to_string(badgeCount.value_or(0));
    } else {
        auto badgeValue = badgeLayoutProperty->GetBadgeValue();
        return badgeValue.value_or("");
    }
}
} // namespace OHOS::Ace::NG