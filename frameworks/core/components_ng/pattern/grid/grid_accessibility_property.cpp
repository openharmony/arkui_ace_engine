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

#include "core/components_ng/pattern/grid/grid_accessibility_property.h"

#include "core/components_ng/pattern/grid/grid_pattern.h"

namespace OHOS::Ace::NG {
bool GridAccessibilityProperty::IsScrollable() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, false);
    auto gridPattern = frameNode->GetPattern<GridPattern>();
    CHECK_NULL_RETURN(gridPattern, false);
    return gridPattern->IsScrollable();
}

bool GridAccessibilityProperty::IsEditable() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, false);
    auto gridLayoutProperty = frameNode->GetLayoutProperty<GridLayoutProperty>();
    CHECK_NULL_RETURN(gridLayoutProperty, false);
    return gridLayoutProperty->GetEditable().value_or(false);
}

int32_t GridAccessibilityProperty::GetBeginIndex() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, -1);
    auto gridPattern = frameNode->GetPattern<GridPattern>();
    CHECK_NULL_RETURN(gridPattern, -1);
    auto gridLayoutInfo = gridPattern->GetGridLayoutInfo();
    return gridLayoutInfo.startIndex_;
}

int32_t GridAccessibilityProperty::GetEndIndex() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, -1);
    auto gridPattern = frameNode->GetPattern<GridPattern>();
    CHECK_NULL_RETURN(gridPattern, -1);
    auto gridLayoutInfo = gridPattern->GetGridLayoutInfo();
    return gridLayoutInfo.endIndex_;
}

int32_t GridAccessibilityProperty::GetCollectionItemCounts() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, 0);
    auto gridPattern = frameNode->GetPattern<GridPattern>();
    CHECK_NULL_RETURN(gridPattern, 0);
    return gridPattern->GetChildrenCount();
}

AceCollectionInfo GridAccessibilityProperty::GetCollectionInfo() const
{
    AceCollectionInfo aceCollectionInfo;
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, aceCollectionInfo);
    auto gridPattern = frameNode->GetPattern<GridPattern>();
    CHECK_NULL_RETURN(gridPattern, aceCollectionInfo);
    auto gridLayoutInfo = gridPattern->GetGridLayoutInfo();
    aceCollectionInfo.rows = static_cast<int32_t>(gridLayoutInfo.gridMatrix_.size());
    if (aceCollectionInfo.rows > 0) {
        aceCollectionInfo.columns = static_cast<int32_t>(gridLayoutInfo.gridMatrix_.begin()->second.size());
    } else {
        aceCollectionInfo.columns = 0;
    }
    aceCollectionInfo.selectMode = gridPattern->MultiSelectable();
    return aceCollectionInfo;
}

void GridAccessibilityProperty::SetSpecificSupportAction()
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_VOID(frameNode);
    auto gridPattern = frameNode->GetPattern<GridPattern>();
    CHECK_NULL_VOID(gridPattern);
    if (IsScrollable()) {
        if (!(gridPattern->IsAtTop())) {
            AddSupportAction(AceAction::ACTION_SCROLL_BACKWARD);
        }
        if (!(gridPattern->IsAtBottom())) {
            AddSupportAction(AceAction::ACTION_SCROLL_FORWARD);
        }
    }
}
} // namespace OHOS::Ace::NG
