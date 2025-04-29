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

#include "core/components_ng/pattern/menu/menu_accessibility_property.h"
#if defined(OHOS_STANDARD_SYSTEM) and !defined(ACE_UNITTEST)
#include "accessibility_element_info.h"
#endif
#include "core/components_ng/pattern/scroll/scroll_pattern.h"

namespace OHOS::Ace::NG {
bool MenuAccessibilityProperty::IsScrollable() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, false);
    auto firstChild = DynamicCast<FrameNode>(frameNode->GetChildAtIndex(0));
    if (firstChild && firstChild->GetTag() == V2::SCROLL_ETS_TAG) {
        auto scrollPattern = firstChild->GetPattern<ScrollPattern>();
        CHECK_NULL_RETURN(scrollPattern, false);
        if (scrollPattern->IsScrollable() && !NearZero(scrollPattern->GetScrollableDistance())) {
            return true;
        }
    }
    return false;
}

void MenuAccessibilityProperty::SetSpecificSupportAction()
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_VOID(frameNode);
    auto firstChild = DynamicCast<FrameNode>(frameNode->GetChildAtIndex(0));
    if (firstChild && firstChild->GetTag() == V2::SCROLL_ETS_TAG) {
        auto scrollPattern = firstChild->GetPattern<ScrollPattern>();
        CHECK_NULL_VOID(scrollPattern);
        if (scrollPattern->IsScrollable() && !NearZero(scrollPattern->GetScrollableDistance())) {
            if (!scrollPattern->IsAtTop()) {
                AddSupportAction(AceAction::ACTION_SCROLL_BACKWARD);
            }
            if (!scrollPattern->IsAtBottom()) {
                AddSupportAction(AceAction::ACTION_SCROLL_FORWARD);
            }
        }
    }
}

void MenuAccessibilityProperty::GetExtraElementInfo(Accessibility::ExtraElementInfo& extraElementInfo)
{
#if defined(OHOS_STANDARD_SYSTEM) and !defined(ACE_UNITTEST)
    extraElementInfo.SetExtraElementInfo("SideBarContainerStates", static_cast<int32_t>(isShow_));
#endif
}
} // namespace OHOS::Ace::NG
