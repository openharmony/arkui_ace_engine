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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_BAR_ITEM_ACCESSIBILITY_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_BAR_ITEM_ACCESSIBILITY_PROPERTY_H

#include <string>

#include "base/utils/utils.h"
#include "core/components_ng/pattern/navigation/bar_item_node.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/property/accessibility_property.h"

namespace OHOS::Ace::NG {
class BarItemAccessibilityProperty : public AccessibilityProperty {
    DECLARE_ACE_TYPE(BarItemAccessibilityProperty, AccessibilityProperty);

public:
    BarItemAccessibilityProperty() = default;

    ~BarItemAccessibilityProperty() override = default;

    std::string GetText() const override
    {
        auto frameNode = AceType::DynamicCast<BarItemNode>(host_.Upgrade());
        CHECK_NULL_RETURN(frameNode, "");
        auto textNode = DynamicCast<FrameNode>(frameNode->GetTextNode());
        CHECK_NULL_RETURN(textNode, "");
        auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_RETURN(textLayoutProperty, "");
        return textLayoutProperty->GetContentValue("");
    }

private:
    ACE_DISALLOW_COPY_AND_MOVE(BarItemAccessibilityProperty);
};
} // namespace OHOS::Ace::NG

#endif