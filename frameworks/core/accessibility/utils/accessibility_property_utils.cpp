/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#include "frameworks/core/accessibility/utils/accessibility_property_utils.h"
#include "base/log/log_wrapper.h"
#include "frameworks/core/accessibility/accessibility_manager.h"
#include "frameworks/core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

std::string AccessibilityPropertyUtils::GetContent(const RefPtr<AccessibilityProperty>& accessibilityProperty)
{
    CHECK_NULL_RETURN(accessibilityProperty, "");
    if (accessibilityProperty->HasUserTextValue()) {
        return accessibilityProperty->GetUserTextValue();
    }
    return accessibilityProperty->GetGroupText();
}

std::string AccessibilityPropertyUtils::GetAccessibilityText(
    const RefPtr<AccessibilityProperty>& accessibilityProperty)
{
    CHECK_NULL_RETURN(accessibilityProperty, "");
    if (!accessibilityProperty->HasUserTextValue() && accessibilityProperty->GetAccessibilityText().empty() &&
        accessibilityProperty->IsAccessibilityGroup() && accessibilityProperty->IsAccessibilityTextPreferred()) {
        return accessibilityProperty->GetGroupPreferAccessibilityText();
    }
    return accessibilityProperty->GetAccessibilityText();
}

std::string AccessibilityPropertyUtils::GetComponentType(
    const RefPtr<FrameNode>& node, const RefPtr<AccessibilityProperty>& accessibilityProperty)
{
    std::string type;
    CHECK_NULL_RETURN(accessibilityProperty, type);
    CHECK_NULL_RETURN(node, type);
    if (accessibilityProperty->HasAccessibilityRole()) {
        type = accessibilityProperty->GetAccessibilityRole();
    } else {
        type = node->GetTag();
    }
    if (accessibilityProperty->HasAccessibilityCustomRole()) {
        type = accessibilityProperty->GetAccessibilityCustomRole();
    }
    return type;
}
} // namespace OHOS::Ace::NG
