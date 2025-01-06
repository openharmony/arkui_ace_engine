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

#include "core/components_ng/pattern/scroll_bar/scroll_bar_accessibility_property.h"

#include "core/components_ng/pattern/scroll_bar/scroll_bar_pattern.h"

namespace OHOS::Ace::NG {
bool ScrollBarAccessibilityProperty::IsScrollable() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, false);
    auto scrollBarPattern = frameNode->GetPattern<ScrollBarPattern>();
    CHECK_NULL_RETURN(scrollBarPattern, false);
    if (scrollBarPattern->GetAxis() != Axis::NONE && Positive(scrollBarPattern->GetControlDistance())
        && (scrollBarPattern->UseInnerScrollBar() || Positive(scrollBarPattern->GetScrollableDistance()))) {
        return true;
    }
    return false;
}

AccessibilityValue ScrollBarAccessibilityProperty::GetAccessibilityValue() const
{
    AccessibilityValue result;
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, result);
    auto scrollBarPattern = frameNode->GetPattern<ScrollBarPattern>();
    CHECK_NULL_RETURN(scrollBarPattern, result);
    result.current = scrollBarPattern->GetCurrentPosition();
    result.min = 0.0;
    result.max = scrollBarPattern->GetScrollableDistance();
    return result;
}

void ScrollBarAccessibilityProperty::SetSpecificSupportAction()
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_VOID(frameNode);
    auto scrollBarPattern = frameNode->GetPattern<ScrollBarPattern>();
    CHECK_NULL_VOID(scrollBarPattern);
    if (IsScrollable()) {
        if (!scrollBarPattern->IsAtTop()) {
            AddSupportAction(AceAction::ACTION_SCROLL_BACKWARD);
        }
        if (!scrollBarPattern->IsAtBottom()) {
            AddSupportAction(AceAction::ACTION_SCROLL_FORWARD);
        }
    }
}
} // namespace OHOS::Ace::NG
