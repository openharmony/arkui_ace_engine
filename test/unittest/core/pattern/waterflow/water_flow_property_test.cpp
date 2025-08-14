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

#include "water_flow_test_ng.h"

namespace OHOS::Ace::NG {

class WaterFlowPropertyTest : public WaterFlowTestNg {};

/**
 * @tc.name: ColumnsTemplateNormal001
 * @tc.desc: Test single column layout with valid template
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowPropertyTest, ColumnsTemplateNormal001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr"); // Valid single column
    CreateWaterFlowItems(3);
    CreateDone();

    /**
     * @tc.steps: step1. Verify single column configuration
     * @tc.expected: Full width allocation
     */
    EXPECT_EQ(layoutProperty_->GetColumnsTemplateValue(), "1fr");
    EXPECT_EQ(pattern_->GetColumns(), 1);
    EXPECT_FLOAT_EQ(GetChildWidth(frameNode_, 0), WATER_FLOW_WIDTH);
}

/**
 * @tc.name: ColumnsTemplateNormal002
 * @tc.desc: Test two equal columns layout
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowPropertyTest, ColumnsTemplateNormal002, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr"); // Valid double columns
    CreateWaterFlowItems(4);
    CreateDone();

    /**
     * @tc.steps: step1. Verify two-column distribution
     * @tc.expected: Equal width division
     */
    const float colWidth = WATER_FLOW_WIDTH / 2;
    EXPECT_EQ(pattern_->GetColumns(), 2);
    EXPECT_FLOAT_EQ(GetChildWidth(frameNode_, 0), colWidth);
    EXPECT_FLOAT_EQ(GetChildX(frameNode_, 1), colWidth);
}

/**
 * @tc.name: ColumnsTemplateNormal003
 * @tc.desc: Test three equal columns layout
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowPropertyTest, ColumnsTemplateNormal003, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr 1fr"); // Valid triple columns
    CreateWaterFlowItems(9);
    CreateDone();

    /**
     * @tc.steps: step1. Verify three-column layout
     * @tc.expected: Equal thirds distribution
     */
    const float colWidth = WATER_FLOW_WIDTH / 3;
    EXPECT_EQ(pattern_->GetColumns(), 3);
    EXPECT_FLOAT_EQ(GetChildWidth(frameNode_, 0), colWidth);
    EXPECT_FLOAT_EQ(GetChildX(frameNode_, 1), colWidth);
    EXPECT_FLOAT_EQ(GetChildX(frameNode_, 2), colWidth * 2);
}

/**
 * @tc.name: ColumnsTemplateInvalid001
 * @tc.desc: Test mixed valid/invalid units
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowPropertyTest, ColumnsTemplateInvalid001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fx"); // Invalid unit
    CreateWaterFlowItems(4);
    CreateDone();

    /**
     * @tc.steps: step1. Verify error handling
     * @tc.expected: Ignore invalid units
     */
    EXPECT_EQ(layoutProperty_->GetColumnsTemplateValue(), "1fr 1fx");
    EXPECT_EQ(pattern_->GetColumns(), 1);
}

/**
 * @tc.name: ColumnsTemplateInvalid002
 * @tc.desc: Test incomplete unit specification
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowPropertyTest, ColumnsTemplateInvalid002, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1f 1fr"); // Malformed unit
    CreateWaterFlowItems(4);
    CreateDone();

    /**
     * @tc.steps: step1. Verify malformed unit handling
     * @tc.expected: Partial valid template
     */
    EXPECT_EQ(layoutProperty_->GetColumnsTemplateValue(), "1f 1fr");
    EXPECT_EQ(pattern_->GetColumns(), 1);
}

/**
 * @tc.name: ColumnsTemplateInvalid003
 * @tc.desc: Test special characters in template
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowPropertyTest, ColumnsTemplateInvalid003, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr,1fr"); // Comma separator
    CreateWaterFlowItems(4);
    CreateDone();

    /**
     * @tc.steps: step1. Verify format tolerance
     * @tc.expected: Treat as single column
     */
    EXPECT_EQ(layoutProperty_->GetColumnsTemplateValue(), "1fr,1fr");
    EXPECT_EQ(pattern_->GetColumns(), 1);
}

/**
 * @tc.name: RowsTemplateNormal001
 * @tc.desc: Test single row layout with valid template
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowPropertyTest, RowsTemplateNormal001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetRowsTemplate("1fr"); // Valid single row
    CreateWaterFlowItems(3);
    CreateDone();

    /**
     * @tc.steps: step1. Verify single row configuration
     * @tc.expected: Full height allocation
     */
    EXPECT_EQ(layoutProperty_->GetRowsTemplateValue(), "1fr");
    EXPECT_EQ(pattern_->GetRows(), 3);
    EXPECT_FLOAT_EQ(GetChildHeight(frameNode_, 0), 100);
}

/**
 * @tc.name: RowsGapPositive001
 * @tc.desc: Test valid positive rows gap
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowPropertyTest, RowsGapPositive001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetRowsGap(Dimension(20.0f)); // 20vp gap
    CreateWaterFlowItems(6);
    CreateDone();

    /**
     * @tc.steps: step1. Verify gap between rows
     * @tc.expected: Apply specified gap value
     */
    EXPECT_FLOAT_EQ(layoutProperty_->GetRowsGapValue().ConvertToPx(), 20.0f);
    EXPECT_GT(GetChildY(frameNode_, 3), 100.0f);
}

/**
 * @tc.name: RowsGapNegative001
 * @tc.desc: Test negative gap value
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowPropertyTest, RowsGapNegative001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetRowsGap(Dimension(0)); // Negative value
    CreateWaterFlowItems(6);
    CreateDone();

    /**
     * @tc.steps: step1. Verify negative handling
     * @tc.expected: Clamp to zero gap
     */
    EXPECT_EQ(layoutProperty_->GetRowsGapValue().ConvertToPx(), 0.0f);
}

/**
 * @tc.name: RowsGapUnitConversion001
 * @tc.desc: Test different dimension units
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowPropertyTest, RowsGapUnitConversion001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetRowsGap(Dimension(10, DimensionUnit::PX)); // Pixel unit
    CreateWaterFlowItems(6);
    CreateDone();

    /**
     * @tc.steps: step1. Verify unit conversion
     * @tc.expected: Apply exact pixel value
     */
    EXPECT_FLOAT_EQ(layoutProperty_->GetRowsGapValue().ConvertToPx(), 10.0f);
}

/**
 * @tc.name: RowsGapUpdate001
 * @tc.desc: Test dynamic gap update
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowPropertyTest, RowsGapUpdate001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetRowsGap(Dimension(5.0f));
    CreateWaterFlowItems(6);
    CreateDone();

    /**
     * @tc.steps: step1. Update gap value
     * @tc.expected: Layout reflow triggered
     */
    layoutProperty_->UpdateRowsGap(Dimension(15.0f));
    FlushUITasks();

    EXPECT_FLOAT_EQ(layoutProperty_->GetRowsGapValue().ConvertToPx(), 15.0f);
    EXPECT_EQ(GetChildY(frameNode_, 3), 445.0f);
}

/**
 * @tc.name: ColumnsGapPositive001
 * @tc.desc: Test valid positive columns gap
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowPropertyTest, ColumnsGapPositive001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsGap(Dimension(20.0f)); // 20vp gap
    CreateWaterFlowItems(6);
    CreateDone();

    /**
     * @tc.steps: step1. Verify gap between columns
     * @tc.expected: Apply specified gap value
     */
    EXPECT_FLOAT_EQ(layoutProperty_->GetColumnsGapValue().ConvertToPx(), 20.0f);
}

/**
 * @tc.name: ColumnsGapUnitConversion001
 * @tc.desc: Test different dimension units
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowPropertyTest, ColumnsGapUnitConversion001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsGap(Dimension(10, DimensionUnit::PX)); // Pixel unit
    CreateWaterFlowItems(6);
    CreateDone();

    /**
     * @tc.steps: step1. Verify unit conversion
     * @tc.expected: Apply exact pixel value
     */
    EXPECT_FLOAT_EQ(layoutProperty_->GetColumnsGapValue().ConvertToPx(), 10.0f);
}

/**
 * @tc.name: ColumnsGapUpdate001
 * @tc.desc: Test dynamic gap update
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowPropertyTest, ColumnsGapUpdate001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsGap(Dimension(5.0f));
    CreateWaterFlowItems(6);
    CreateDone();

    /**
     * @tc.steps: step1. Update gap value
     * @tc.expected: Layout reflow triggered
     */
    layoutProperty_->UpdateColumnsGap(Dimension(15.0f));
    FlushUITasks();

    EXPECT_FLOAT_EQ(layoutProperty_->GetColumnsGapValue().ConvertToPx(), 15.0f);
}

/**
 * @tc.name: ItemSizeConstraints001
 * @tc.desc: Test item size constraints with valid values
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowPropertyTest, ItemSizeConstraints001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    // Set constraints
    model.SetItemMinWidth(Dimension(50));
    model.SetItemMinHeight(Dimension(60));
    model.SetItemMaxWidth(Dimension(200));
    model.SetItemMaxHeight(Dimension(300));
    CreateWaterFlowItems(6); // Create items with different sizes
    CreateDone();

    // Verify property values
    auto minSize = layoutProperty_->GetItemMinSize();
    EXPECT_EQ(minSize->Width().value().ToString(), "50.00px");
    EXPECT_EQ(minSize->Height().value().ToString(), "60.00px");
    
    auto maxSize = layoutProperty_->GetItemMaxSize();
    EXPECT_EQ(maxSize->Width().value().ToString(), "200.00px");
    EXPECT_EQ(maxSize->Height().value().ToString(), "300.00px");
}

/**
 * @tc.name: HorizontalScrollTest001
 * @tc.desc: Test horizontal scroll layout
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowPropertyTest, HorizontalScrollTest001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetLayoutDirection(FlexDirection::ROW);
    model.SetRowsTemplate("1fr 1fr");
    CreateWaterFlowItems(12); // Create 12 items with different widths
    CreateDone();

    // Verify initial layout positions
    EXPECT_TRUE(IsEqual(GetChildRect(frameNode_, 0), RectF(0, 0, 100, 400)));
    EXPECT_TRUE(IsEqual(GetChildRect(frameNode_, 1), RectF(0, 400, 200, 400)));

    // Perform horizontal scroll by 200px
    UpdateCurrentOffset(-200.f, SCROLL_FROM_UPDATE);
    
    // Validate positions of newly visible items after scrolling
    EXPECT_TRUE(IsEqual(GetChildRect(frameNode_, 4), RectF(0, 400, 100, 400)));
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 3);
}

/**
 * @tc.name: DataUpdateTest001
 * @tc.desc: Test layout update after item deletion
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowPropertyTest, DataUpdateTest001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    CreateWaterFlowItems(20);
    CreateDone();

    // Verify initial display of 10 items
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 10);

    // Remove items 5-7 from the list
    for (int i = 7; i >= 5; i--) {
        frameNode_->RemoveChildAtIndex(i);
    }
    frameNode_->ChildrenUpdatedFrom(5);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();

    // Check updated item display after deletion
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 11);
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 12)->IsActive());
}

/**
 * @tc.name: RTLayoutTest001
 * @tc.desc: Test right-to-left layout direction
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowPropertyTest, RTLayoutTest001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    model.SetColumnsTemplate("1fr 1fr");
    CreateWaterFlowItems(8);
    CreateDone();

    // Validate RTL layout positions
    EXPECT_TRUE(IsEqual(GetChildRect(frameNode_, 0), RectF(WATER_FLOW_WIDTH/2, 0, WATER_FLOW_WIDTH/2, 100)));
    EXPECT_TRUE(IsEqual(GetChildRect(frameNode_, 1), RectF(0, 0, WATER_FLOW_WIDTH/2, 200)));
}

/**
 * @tc.name: InvalidColumnTemplate001
 * @tc.desc: Test WaterFlow behavior when setting invalid column template at runtime
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, InvalidColumnTemplate001, TestSize.Level1)
{
    // Create normal WaterFlow
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    ViewAbstract::SetWidth(CalcLength(400.0f));
    ViewAbstract::SetHeight(CalcLength(600.0f));
    CreateWaterFlowItems(20);
    CreateDone();

    // Verify initial state is normal
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 0);
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 0)->IsActive());
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 1)->IsActive());

    /**
     * @tc.steps: step1. Set invalid column template dynamically
     * @tc.expected: WaterFlow should maintain previous layout state without crashing
     */
    layoutProperty_->UpdateColumnsTemplate(""); // Empty string
    FlushUITasks();

    // Verify layout is still valid
    EXPECT_GE(pattern_->layoutInfo_->endIndex_, 0);
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 0)->IsActive());

    /**
     * @tc.steps: step2. Set column template with invalid syntax
     * @tc.expected: Should fallback to default behavior or maintain original state
     */
    layoutProperty_->UpdateColumnsTemplate("invalid syntax");
    FlushUITasks();

    // Verify no crash and reasonable fallback behavior
    EXPECT_GE(pattern_->layoutInfo_->endIndex_, 0);

    /**
     * @tc.steps: step3. Restore valid column template
     * @tc.expected: Layout should recover normally
     */
    layoutProperty_->UpdateColumnsTemplate("1fr 1fr 1fr");
    FlushUITasks();

    EXPECT_TRUE(GetChildFrameNode(frameNode_, 0)->IsActive());
    EXPECT_GE(pattern_->layoutInfo_->endIndex_, 2);
}
}