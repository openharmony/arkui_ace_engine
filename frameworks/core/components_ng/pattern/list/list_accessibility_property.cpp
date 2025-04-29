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

#include "core/components_ng/pattern/list/list_accessibility_property.h"

#include "core/components_ng/pattern/list/list_pattern.h"

namespace OHOS::Ace::NG {
bool ListAccessibilityProperty::IsScrollable() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, false);
    auto listPattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_RETURN(listPattern, false);
    return listPattern->IsScrollable();
}

int32_t ListAccessibilityProperty::GetBeginIndex() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, -1);
    auto listPattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_RETURN(listPattern, -1);
    return listPattern->GetStartIndex();
}

int32_t ListAccessibilityProperty::GetEndIndex() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, -1);
    auto listPattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_RETURN(listPattern, -1);
    return listPattern->GetEndIndex();
}

int32_t ListAccessibilityProperty::GetCollectionItemCounts() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, -1);
    auto listPattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_RETURN(listPattern, -1);
    return listPattern->GetMaxListItemIndex() + 1;
}

void ListAccessibilityProperty::SetSpecificSupportAction()
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_VOID(frameNode);
    auto listPattern = frameNode->GetPattern<ListPattern>();
    CHECK_NULL_VOID(listPattern);
    if (IsScrollable()) {
        if (!(listPattern->IsAtTop())) {
            AddSupportAction(AceAction::ACTION_SCROLL_BACKWARD);
        }
        if (!(listPattern->IsAtBottom())) {
            AddSupportAction(AceAction::ACTION_SCROLL_FORWARD);
        }
    }
}
} // namespace OHOS::Ace::NG
