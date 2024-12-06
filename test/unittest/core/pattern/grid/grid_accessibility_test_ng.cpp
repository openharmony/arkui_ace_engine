/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "grid_test_ng.h"

#include "core/components_ng/pattern/grid/grid_item_pattern.h"

namespace OHOS::Ace::NG {
class GridAccessibilityTestNg : public GridTestNg {};

/**
 * @tc.name: AccessibilityProperty001
 * @tc.desc: Test AccessibilityFunc
 * @tc.type: FUNC
 */
HWTEST_F(GridAccessibilityTestNg, AccessibilityProperty001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    model.SetMultiSelectable(true);
    model.SetEditable(true);
    CreateFixedItems(14);
    CreateDone();

    EXPECT_TRUE(accessibilityProperty_->IsScrollable());
    EXPECT_TRUE(accessibilityProperty_->IsEditable());
    EXPECT_EQ(accessibilityProperty_->GetBeginIndex(), 0);
    EXPECT_EQ(accessibilityProperty_->GetEndIndex(), 13);
    EXPECT_EQ(accessibilityProperty_->GetCollectionItemCounts(), 14);
    AceCollectionInfo info = accessibilityProperty_->GetCollectionInfo();
    EXPECT_EQ(info.rows, 4);
    EXPECT_EQ(info.columns, 4);
    EXPECT_EQ(info.selectMode, 1);
}

/**
 * @tc.name: SetSpecificSupportAction001
 * @tc.desc: Test SetSpecificSupportAction
 * @tc.type: FUNC
 */
HWTEST_F(GridAccessibilityTestNg, SetSpecificSupportAction001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr");
    CreateFixedItems(10);
    CreateDone();

    /**
     * @tc.steps: step1. Grid is at top.
     * @tc.expected: Check actions value
     */
    EXPECT_TRUE(pattern_->IsAtTop());
    EXPECT_FALSE(pattern_->IsAtBottom());
    accessibilityProperty_->ResetSupportAction();
    uint64_t expectActions = 0;
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    EXPECT_EQ(GetActions(accessibilityProperty_), expectActions);

    /**
     * @tc.steps: step2. Grid is at middle.
     * @tc.expected: Check actions value
     */
    ScrollTo(ITEM_MAIN_SIZE);
    EXPECT_FALSE(pattern_->IsAtTop());
    EXPECT_FALSE(pattern_->IsAtBottom());
    accessibilityProperty_->ResetSupportAction();
    expectActions = 0;
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    EXPECT_EQ(GetActions(accessibilityProperty_), expectActions);

    /**
     * @tc.steps: step3. Grid is at bottom.
     * @tc.expected: Check actions value
     */
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM);
    EXPECT_FALSE(pattern_->IsAtTop());
    EXPECT_TRUE(pattern_->IsAtBottom());
    accessibilityProperty_->ResetSupportAction();
    expectActions = 0;
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    EXPECT_EQ(GetActions(accessibilityProperty_), expectActions);
}

/**
 * @tc.name: GridItemAccessibilityTest001
 * @tc.desc: Test GridItem AccessibilityProperty Func
 * @tc.type: FUNC
 */
HWTEST_F(GridAccessibilityTestNg, GridItemAccessibilityTest001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateFixedItems(20);
    CreateDone();

    auto itemAccessibility = GetChildAccessibilityProperty<GridItemAccessibilityProperty>(frameNode_, 1);
    EXPECT_FALSE(itemAccessibility->IsSelected());
    AceCollectionItemInfo info = itemAccessibility->GetCollectionItemInfo();
    EXPECT_EQ(info.row, 0);
    EXPECT_EQ(info.column, 1);
    EXPECT_EQ(info.rowSpan, 1);
    EXPECT_EQ(info.columnSpan, 1);
    EXPECT_FALSE(info.heading);

    itemAccessibility->ResetSupportAction();
    uint64_t expectActions = 0;
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SELECT);
    expectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_CLEAR_SELECTION);
    EXPECT_EQ(GetActions(itemAccessibility), expectActions);
}

/**
 * @tc.name: GridItemAccessibilityTest002
 * @tc.desc: Test GridItem AccessibilityProperty GetCollectionItemInfo func with has heading GridItem
 * @tc.type: FUNC
 */
HWTEST_F(GridAccessibilityTestNg, GridItemAccessibilityTest002, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    // Create big item
    CreateBigColItem(0, 3);
    CreateFixedItems(10);
    CreateDone();

    auto itemAccessibility = GetChildAccessibilityProperty<GridItemAccessibilityProperty>(frameNode_, 0);
    AceCollectionItemInfo info = itemAccessibility->GetCollectionItemInfo();
    EXPECT_EQ(info.row, 0);
    EXPECT_EQ(info.column, 0);
    EXPECT_EQ(info.rowSpan, 1);
    EXPECT_EQ(info.columnSpan, 4);
    EXPECT_TRUE(info.heading);
}

/**
 * @tc.name: PerformActionTest001
 * @tc.desc: Grid AccessibilityPerformAction test ScrollForward and ScrollBackward.
 * @tc.type: FUNC
 */
HWTEST_F(GridAccessibilityTestNg, PerformActionTest001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr");
    CreateFixedItems(10);
    CreateDone();

    /**
     * @tc.steps: step1. Call ActActionScrollForward
     * @tc.expected: Trigger ScrollPage down
     */
    accessibilityProperty_->ActActionScrollForward();
    EXPECT_TRUE(Position(-GRID_HEIGHT));

    /**
     * @tc.steps: step2. Call ActActionScrollForward
     * @tc.expected: Trigger ScrollPage up
     */
    accessibilityProperty_->ActActionScrollBackward();
    EXPECT_TRUE(Position(0));
}

/**
 * @tc.name: PerformActionTest002
 * @tc.desc: GridItem AccessibilityPerformAction test Select and ClearSelection.
 * @tc.type: FUNC
 */
HWTEST_F(GridAccessibilityTestNg, PerformActionTest002, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr");
    CreateFixedItems(1);
    CreateDone();

    /**
     * @tc.steps: step1. When gridItem is unSelectable
     * @tc.expected: can not be selected
     */
    auto gridItemPattern = GetChildPattern<GridItemPattern>(frameNode_, 0);
    auto gridItemAccessibilityProperty = GetChildAccessibilityProperty<GridItemAccessibilityProperty>(frameNode_, 0);
    gridItemPattern->SetSelectable(false);
    gridItemAccessibilityProperty->ActActionSelect();
    EXPECT_FALSE(gridItemPattern->IsSelected());
    gridItemAccessibilityProperty->ActActionClearSelection();
    EXPECT_FALSE(gridItemPattern->IsSelected());

    /**
     * @tc.steps: step2. When gridItem is Selectable
     * @tc.expected: can be selected
     */
    gridItemPattern->SetSelectable(true);
    gridItemAccessibilityProperty->ActActionSelect();
    EXPECT_TRUE(gridItemPattern->IsSelected());
    gridItemAccessibilityProperty->ActActionClearSelection();
    EXPECT_FALSE(gridItemPattern->IsSelected());
}

/**
 * @tc.name: UnScrollableGrid001
 * @tc.desc: Test AccessibilityProperty GetCollectionInfo func with empty GridItem
 * @tc.type: FUNC
 */
HWTEST_F(GridAccessibilityTestNg, UnScrollableGrid001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateDone();

    AceCollectionInfo info = accessibilityProperty_->GetCollectionInfo();
    EXPECT_EQ(info.rows, 0);
    EXPECT_EQ(info.columns, 0);
    EXPECT_EQ(info.selectMode, 0);
}

/**
 * @tc.name: UnScrollableGrid002
 * @tc.desc: Test AccessibilityProperty GetCollectionInfo func in unScrollable Grid
 * @tc.type: FUNC
 */
HWTEST_F(GridAccessibilityTestNg, UnScrollableGrid002, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateGridItems(8);
    CreateDone();

    AceCollectionInfo info = accessibilityProperty_->GetCollectionInfo();
    EXPECT_EQ(info.rows, 2);
    EXPECT_EQ(info.columns, 4);
    EXPECT_EQ(info.selectMode, 0);

    /**
     * @tc.steps: step1. When grid is unScrollable
     * @tc.expected: Can not ScrollPage
     */
    accessibilityProperty_->ActActionScrollForward();
    EXPECT_TRUE(Position(0));

    accessibilityProperty_->ActActionScrollBackward();
    EXPECT_TRUE(Position(0));
}

/**
 * @tc.name: UnScrollableGrid003
 * @tc.desc: Test AccessibilityProperty GetCollectionInfo func in unScrollable Grid
 * @tc.type: FUNC
 */
HWTEST_F(GridAccessibilityTestNg, UnScrollableGrid003, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetRowsTemplate("1fr");
    model.SetColumnsTemplate("1fr");
    CreateDone();
    EXPECT_FALSE(accessibilityProperty_->IsScrollable());

    accessibilityProperty_->ResetSupportAction();
    uint64_t expectActions = 0;
    EXPECT_EQ(GetActions(accessibilityProperty_), expectActions);
}
} // namespace OHOS::Ace::NG
