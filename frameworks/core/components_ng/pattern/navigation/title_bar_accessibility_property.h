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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_TITLE_BAR_ACCESSIBILITY_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_NAVIGATION_TITLE_BAR_ACCESSIBILITY_PROPERTY_H

#include <string>

#include "base/utils/utf_helper.h"
#include "base/utils/utils.h"
#include "core/components_ng/pattern/navigation/title_bar_node.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/property/accessibility_property.h"

namespace OHOS::Ace::NG {
class TitleBarAccessibilityProperty : public AccessibilityProperty {
    DECLARE_ACE_TYPE(TitleBarAccessibilityProperty, AccessibilityProperty);

public:
    TitleBarAccessibilityProperty() = default;

    ~TitleBarAccessibilityProperty() override = default;

    std::string GetText() const override
    {
        auto frameNode = AceType::DynamicCast<TitleBarNode>(host_.Upgrade());
        CHECK_NULL_RETURN(frameNode, "");
        auto titleNode = frameNode->GetTitle();
        CHECK_NULL_RETURN(titleNode, "");
        auto title = AceType::DynamicCast<FrameNode>(titleNode);
        CHECK_NULL_RETURN(title, "");
        auto textLayoutProperty = title->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_RETURN(textLayoutProperty, "");
        return UtfUtils::Str16ToStr8(textLayoutProperty->GetContentValue(u""));
    }

private:
    ACE_DISALLOW_COPY_AND_MOVE(TitleBarAccessibilityProperty);
};
} // namespace OHOS::Ace::NG

#endif