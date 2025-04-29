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

#include "core/components_ng/pattern/grid/grid_item_accessibility_property.h"

#include "core/components_ng/pattern/grid/grid_item_pattern.h"

namespace OHOS::Ace::NG {
bool GridItemAccessibilityProperty::IsSelected() const
{
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, false);
    auto gridItemPattern = frameNode->GetPattern<GridItemPattern>();
    CHECK_NULL_RETURN(gridItemPattern, false);
    return gridItemPattern->IsSelected();
}

AceCollectionItemInfo GridItemAccessibilityProperty::GetCollectionItemInfo() const
{
    AceCollectionItemInfo aceCollectionItemInfo;
    auto frameNode = host_.Upgrade();
    CHECK_NULL_RETURN(frameNode, aceCollectionItemInfo);
    auto gridItemPattern = frameNode->GetPattern<GridItemPattern>();
    CHECK_NULL_RETURN(gridItemPattern, aceCollectionItemInfo);
    auto gridItemLayoutProperty = frameNode->GetLayoutProperty<GridItemLayoutProperty>();
    CHECK_NULL_RETURN(gridItemLayoutProperty, aceCollectionItemInfo);
    auto uiNode = DynamicCast<UINode>(frameNode);
    CHECK_NULL_RETURN(uiNode, aceCollectionItemInfo);
    while (uiNode->GetTag() != V2::GRID_ETS_TAG) {
        uiNode = uiNode->GetParent();
        CHECK_NULL_RETURN(uiNode, aceCollectionItemInfo);
    }
    auto gridNode = DynamicCast<FrameNode>(uiNode);
    CHECK_NULL_RETURN(gridNode, aceCollectionItemInfo);
    auto gridPattern = gridNode->GetPattern<GridPattern>();
    CHECK_NULL_RETURN(gridPattern, aceCollectionItemInfo);
    auto gridAxis = gridPattern->GetAxis();
    aceCollectionItemInfo.row = gridItemLayoutProperty->GetMainIndex().value_or(-1);
    aceCollectionItemInfo.column = gridItemLayoutProperty->GetCrossIndex().value_or(-1);
    aceCollectionItemInfo.rowSpan = gridItemLayoutProperty->GetMainSpan(gridAxis);
    aceCollectionItemInfo.columnSpan = gridItemLayoutProperty->GetCrossSpan(gridAxis);

    auto gridAccessibilityProperty = gridNode->GetAccessibilityProperty<GridAccessibilityProperty>();
    if (aceCollectionItemInfo.columnSpan == gridAccessibilityProperty->GetCollectionInfo().columns) {
        aceCollectionItemInfo.heading = true;
    }
    return aceCollectionItemInfo;
}

void GridItemAccessibilityProperty::SetSpecificSupportAction()
{
    AddSupportAction(AceAction::ACTION_SELECT);
    AddSupportAction(AceAction::ACTION_CLEAR_SELECTION);
}
} // namespace OHOS::Ace::NG
