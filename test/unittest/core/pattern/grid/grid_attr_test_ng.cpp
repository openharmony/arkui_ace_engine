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

#include "grid_test_ng.h"

namespace OHOS::Ace::NG {

namespace {} // namespace

class GridAttrTestNg : public GridTestNg {
public:
    int32_t CalculateGridColumnsOrRows(float contentWidth, float gridWidth, float gutter = 0.0f, float margin = 0.0f);
    AssertionResult VerifyItemRect(
        int32_t viewItemNumber, int32_t lanes, float width, float height, int32_t startIndex, FlexDirection direction);
    AssertionResult VerifyBigItemRect(int32_t index, RectF expectRect);
};

int32_t GridAttrTestNg::CalculateGridColumnsOrRows(float contentWidth, float gridWidth, float gutter, float margin)
{
    int32_t count = static_cast<int32_t>(floor((contentWidth - 2 * margin + gutter) / (gridWidth + gutter)));
    return count < 1 ? 1 : count;
}

AssertionResult GridAttrTestNg::VerifyItemRect(
    int32_t viewItemNumber, int32_t lanes, float width, float height, int32_t startIndex, FlexDirection direction)
{
    if (lanes < 1) {
        return AssertionFailure() << "lanes < 1";
    }
    float unitX = width + COL_GAP;
    float unitY = height + ROW_GAP;
    float itemWidthTotal = lanes * unitX - COL_GAP;
    float itemHeightTotal = lanes * unitY - ROW_GAP;
    for (int32_t index = 0; index < viewItemNumber; index++) {
        float offsetX;
        float offsetY;
        switch (direction) {
            case FlexDirection::ROW:
                offsetX = index % lanes * unitX;
                offsetY = floor(index / lanes) * unitY;
                break;
            case FlexDirection::ROW_REVERSE:
                offsetX = itemWidthTotal - (index % lanes + 1) * unitX + COL_GAP;
                offsetY = floor(index / lanes) * unitY;
                break;
            case FlexDirection::COLUMN:
                offsetX = floor(index / lanes) * unitX;
                offsetY = index % lanes * unitY;
                break;
            case FlexDirection::COLUMN_REVERSE:
                offsetX = floor(index / lanes) * unitX;
                offsetY = itemHeightTotal - (index % lanes + 1) * unitY + ROW_GAP;
                break;
            default:
                break;
        }
        int32_t itemIndex = index + startIndex;
        RectF rect = GetChildRect(frameNode_, itemIndex);
        RectF expectRect = RectF(offsetX, offsetY, width, height);
        if (rect != expectRect) {
            return AssertionFailure() << "At Item Index: " << itemIndex << " rect: " << rect.ToString() <<
                " != " << "expectRect: " << expectRect.ToString();
        }
        if (!GetChildFrameNode(frameNode_, itemIndex)->IsActive()) {
            return AssertionFailure() << "At Item Index: " << itemIndex << " IsActive() is false";
        }
    }
    return AssertionSuccess();
}

AssertionResult GridAttrTestNg::VerifyBigItemRect(int32_t index, RectF expectRect)
{
    return IsEqual(GetChildRect(frameNode_, index), expectRect);
}

/**
 * @tc.name: Property001
 * @tc.desc: Test Grid properties
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, Property001, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr");
        model.SetRowsTemplate("1fr 1fr 1fr");
        model.SetColumnsGap(Dimension(COL_GAP));
        model.SetRowsGap(Dimension(ROW_GAP));
        model.SetCachedCount(2);
        model.SetEditable(true);
        model.SetLayoutDirection(FlexDirection::ROW);
        model.SetMaxCount(5);
        model.SetMinCount(2);
        model.SetCellLength(100);
        model.SetEdgeEffect(EdgeEffect::SPRING, false);
        model.SetScrollEnabled(false);
        CreateColItem(10);
    });

    /**
     * @tc.steps: step1. Test ToJsonValue
     */
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json);
    EXPECT_EQ(json->GetString("columnsTemplate"), "1fr 1fr");
    EXPECT_EQ(json->GetString("rowsTemplate"), "1fr 1fr 1fr");
    EXPECT_EQ(Dimension::FromString(json->GetString("columnsGap")), Dimension(COL_GAP));
    EXPECT_EQ(Dimension::FromString(json->GetString("rowsGap")), Dimension(ROW_GAP));
    EXPECT_EQ(json->GetInt("cachedCount"), 2);
    EXPECT_EQ(json->GetString("editMode"), "true");
    EXPECT_EQ(json->GetString("layoutDirection"), "GridDirection.Row");
    EXPECT_EQ(json->GetInt("maxCount"), 5);
    EXPECT_EQ(json->GetInt("minCount"), 2);
    EXPECT_EQ(json->GetInt("cellLength"), 100);
    EXPECT_FALSE(json->GetBool("enableScrollInteraction"));

    /**
     * @tc.steps: step2. Test ToJsonValue, change some property
     */
    layoutProperty_->UpdateGridDirection(FlexDirection::ROW_REVERSE);
    json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json);
    EXPECT_EQ(json->GetString("layoutDirection"), "GridDirection.RowReverse");

    /**
     * @tc.steps: step3. Test ToJsonValue, change some property
     */
    layoutProperty_->UpdateGridDirection(FlexDirection::COLUMN);
    json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json);
    EXPECT_EQ(json->GetString("layoutDirection"), "GridDirection.Column");

    /**
     * @tc.steps: step4. Test ToJsonValue, change some property
     */
    layoutProperty_->UpdateGridDirection(FlexDirection::COLUMN_REVERSE);
    json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json);
    EXPECT_EQ(json->GetString("layoutDirection"), "GridDirection.ColumnReverse");
}

/**
 * @tc.name: Property002
 * @tc.desc: Test Negative Gap
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, Property002, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetRowsGap(Dimension(-5));
        model.SetColumnsGap(Dimension(-10));
        CreateColItem(10);
    });

    /**
     * @tc.steps: step1. Verify GapValue
     * @tc.expected: Gap not be set
     */
    EXPECT_EQ(layoutProperty_->GetRowsGap(), std::nullopt);
    EXPECT_EQ(layoutProperty_->GetColumnsGap(), std::nullopt);
}

/**
 * @tc.name: Property003
 * @tc.desc: Test all the properties of GridItem.
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, Property003, TestSize.Level1)
{
    GridItemModelNG itemModel;
    itemModel.Create(GridItemStyle::NONE);
    itemModel.SetRowStart(1);
    itemModel.SetRowEnd(2);
    itemModel.SetColumnStart(1);
    itemModel.SetColumnEnd(2);
    itemModel.SetForceRebuild(true);
    itemModel.SetSelectable(false);
    itemModel.SetOnSelect([](bool) {});

    /**
     * @tc.steps: step1. Get frameNode and properties.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    auto layoutProperty = frameNode->GetLayoutProperty<GridItemLayoutProperty>();
    EXPECT_EQ(layoutProperty->GetRowStart(), 1);
    EXPECT_EQ(layoutProperty->GetRowEnd(), 2);
    EXPECT_EQ(layoutProperty->GetColumnStart(), 1);
    EXPECT_EQ(layoutProperty->GetColumnEnd(), 2);
    EXPECT_EQ(layoutProperty->GetCustomCrossIndex(Axis::VERTICAL), 1);
    EXPECT_EQ(layoutProperty->GetMainSpan(Axis::VERTICAL), 2);
    EXPECT_EQ(layoutProperty->GetCrossSpan(Axis::VERTICAL), 2);
    EXPECT_EQ(layoutProperty->GetMainStart(Axis::VERTICAL), 1);
    EXPECT_EQ(layoutProperty->GetCrossStart(Axis::VERTICAL), 1);
    EXPECT_EQ(layoutProperty->GetCustomCrossIndex(Axis::HORIZONTAL), 1);
    EXPECT_EQ(layoutProperty->GetMainSpan(Axis::HORIZONTAL), 2);
    EXPECT_EQ(layoutProperty->GetCrossSpan(Axis::HORIZONTAL), 2);
    EXPECT_EQ(layoutProperty->GetMainStart(Axis::HORIZONTAL), 1);
    EXPECT_EQ(layoutProperty->GetCrossStart(Axis::HORIZONTAL), 1);
    EXPECT_EQ(layoutProperty->GetMainEnd(Axis::VERTICAL), 2);
    EXPECT_EQ(layoutProperty->GetMainEnd(Axis::HORIZONTAL), 2);
    EXPECT_EQ(layoutProperty->GetCrossEnd(Axis::VERTICAL), 2);
    EXPECT_EQ(layoutProperty->GetCrossEnd(Axis::HORIZONTAL), 2);
    auto pattern = frameNode->GetPattern<GridItemPattern>();
    EXPECT_TRUE(pattern->forceRebuild_);
    auto eventHub = frameNode->GetEventHub<GridItemEventHub>();
    ASSERT_NE(eventHub->onSelect_, nullptr);

    /**
     * @tc.steps: step2. Test ToJsonValue
     */
    auto json = JsonUtil::Create(true);
    layoutProperty->ToJsonValue(json);
    EXPECT_EQ(json->GetString("rowStart"), "1");
    EXPECT_EQ(json->GetString("rowEnd"), "2");
    EXPECT_EQ(json->GetString("columnStart"), "1");
    EXPECT_EQ(json->GetString("columnEnd"), "2");
}

/**
 * @tc.name: ColumnsTemplate001
 * @tc.desc: Test property about columnsTemplate and Gap,
 * test normal condition that template is "1fr 1fr 1fr 1fr"
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, ColumnsTemplate001, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        model.SetColumnsGap(Dimension(COL_GAP));
        model.SetRowsGap(Dimension(ROW_GAP));
        CreateColItem(20);
    });

    /**
     * @tc.steps: step1. While only set ColumnsTemplate
     * @tc.expected: The axis is VERTICAL
     */
    EXPECT_EQ(pattern_->GetAxis(), Axis::VERTICAL);

    /**
     * @tc.steps: step2. Verify all of gridItems rect
     */
    float averageWidth = (GRID_WIDTH + COL_GAP) / 4 - COL_GAP;
    EXPECT_TRUE(VerifyItemRect(12, 4, averageWidth, ITEM_HEIGHT, 0, FlexDirection::ROW));

    /**
     * @tc.steps: step3. Scroll and Verify
     */
    UpdateCurrentOffset(-(ITEM_HEIGHT + ROW_GAP));
    EXPECT_TRUE(VerifyItemRect(12, 4, averageWidth, ITEM_HEIGHT, 4, FlexDirection::ROW));
}

/**
 * @tc.name: ColumnsTemplate002
 * @tc.desc: Test property about columnsTemplate,
 * test condition that template is "1fr 2fr 3fr 1fr"
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, ColumnsTemplate002, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 2fr 3fr 1fr");
        CreateColItem(10);
    });

    /**
     * @tc.steps: step1. Verify index 1 gridItem rect
     */
    float averageWidth = GRID_WIDTH / 7;
    EXPECT_TRUE(IsEqual(GetChildRect(frameNode_, 1),
        RectF(averageWidth, 0.f, averageWidth * 2, ITEM_HEIGHT)));

    /**
     * @tc.steps: step2. Verify index 6 gridItem rect
     */
    EXPECT_TRUE(IsEqual(GetChildRect(frameNode_, 6),
        RectF(averageWidth * 3, ITEM_HEIGHT, averageWidth * 3, ITEM_HEIGHT)));
}

/**
 * @tc.name: ColumnsTemplate003
 * @tc.desc: Test property about columnsTemplate,
 * test condition that template is "1fr 0fr 0fr 1fr"
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, ColumnsTemplate003, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 0fr 0fr 1fr");
        CreateColItem(10);
    });

    /**
     * @tc.steps: step1. Verify index 1 gridItem rect
     * @tc.expected: The item width is zero
     */
    float averageWidth = GRID_WIDTH / 2;
    EXPECT_TRUE(IsEqual(GetChildRect(frameNode_, 1),
        RectF(averageWidth, 0.f, 0.f, ITEM_HEIGHT)));
}

/**
 * @tc.name: ColumnsTemplate004
 * @tc.desc: Test property about columnsTemplate and Gap,
 * test normal condition that template is "repeat(auto-fit, 90px)"
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, ColumnsTemplate004, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("repeat(auto-fit, 90px)");
        model.SetColumnsGap(Dimension(COL_GAP));
        model.SetRowsGap(Dimension(ROW_GAP));
        CreateColItem(20);
    });

    /**
     * @tc.steps: step1. While only set ColumnsTemplate
     * @tc.expected: The axis is VERTICAL
     */
    EXPECT_EQ(pattern_->GetAxis(), Axis::VERTICAL);

    /**
     * @tc.steps: step2. Verify all of gridItems rect
     */
    float gridWidth = 90.0f;
    int32_t lanes = CalculateGridColumnsOrRows(GRID_WIDTH, gridWidth, COL_GAP);
    float averageWidth = (GRID_WIDTH + COL_GAP) / 4 - COL_GAP;
    EXPECT_TRUE(VerifyItemRect(12, lanes, averageWidth, ITEM_HEIGHT, 0, FlexDirection::ROW));

    /**
     * @tc.steps: step3. Scroll and Verify
     */
    UpdateCurrentOffset(-(ITEM_HEIGHT + ROW_GAP));
    EXPECT_TRUE(VerifyItemRect(12, lanes, averageWidth, ITEM_HEIGHT, 4, FlexDirection::ROW));
}

/**
 * @tc.name: RowsTemplate001
 * @tc.desc: Test property about rowsTemplate and Gap,
 * test normal condition that template is "1fr 1fr 1fr 1fr"
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, RowsTemplate001, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetRowsTemplate("1fr 1fr 1fr 1fr");
        model.SetColumnsGap(Dimension(COL_GAP));
        model.SetRowsGap(Dimension(ROW_GAP));
        CreateRowItem(20);
    });

    /**
     * @tc.steps: step1. While only set rowsTemplate
     * @tc.expected: The axis is HORIZONTAL
     */
    EXPECT_EQ(pattern_->GetAxis(), Axis::HORIZONTAL);

    /**
     * @tc.steps: step2. Verify all of gridItems rect
     */
    float averageHeight = (GRID_HEIGHT + ROW_GAP) / 4 - ROW_GAP;
    EXPECT_TRUE(VerifyItemRect(12, 4, ITEM_WIDTH, averageHeight, 0, FlexDirection::COLUMN));

    /**
     * @tc.steps: step3. Scroll and Verify
     */
    UpdateCurrentOffset(-(ITEM_WIDTH + COL_GAP));
    EXPECT_TRUE(VerifyItemRect(12, 4, ITEM_WIDTH, averageHeight, 4, FlexDirection::COLUMN));
}

/**
 * @tc.name: RowsTemplate002
 * @tc.desc: Test property about rowsTemplate,
 * test condition that template is "1fr 2fr 3fr 1fr"
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, RowsTemplate002, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetRowsTemplate("1fr 2fr 3fr 1fr");
        CreateRowItem(10);
    });

    /**
     * @tc.steps: step1. Verify index 1 gridItem rect
     */
    float averageHeight = GRID_HEIGHT / 7;
    EXPECT_TRUE(IsEqual(GetChildRect(frameNode_, 1),
        RectF(0.f, averageHeight, ITEM_WIDTH, averageHeight * 2)));

    /**
     * @tc.steps: step2. Verify index 6 gridItem rect
     */
    EXPECT_TRUE(IsEqual(GetChildRect(frameNode_, 6),
        RectF(ITEM_WIDTH, averageHeight * 3, ITEM_WIDTH, averageHeight * 3)));
}

/**
 * @tc.name: RowsTemplate003
 * @tc.desc: Test property about rowsTemplate,
 * test condition that template is "1fr 0fr 0fr 1fr"
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, RowsTemplate003, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetRowsTemplate("1fr 0fr 0fr 1fr");
        CreateRowItem(10);
    });

    /**
     * @tc.steps: step1. Verify index 1 gridItem rect
     * @tc.expected: The item height is zero
     */
    float averageHeight = GRID_HEIGHT / 2;
    EXPECT_TRUE(IsEqual(GetChildRect(frameNode_, 1),
        RectF(0.f, averageHeight, ITEM_WIDTH, 0.f)));
}

/**
 * @tc.name: RowsTemplate004
 * @tc.desc: Test property about rowsTemplate and Gap,
 * test normal condition that template is "repeat(auto-fit, 90px)"
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, RowsTemplate004, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetRowsTemplate("repeat(auto-fit, 90px)");
        model.SetColumnsGap(Dimension(COL_GAP));
        model.SetRowsGap(Dimension(ROW_GAP));
        CreateRowItem(24);
    });

    /**
     * @tc.steps: step1. While only set rowsTemplate
     * @tc.expected: The axis is HORIZONTAL
     */
    EXPECT_EQ(pattern_->GetAxis(), Axis::HORIZONTAL);

    /**
     * @tc.steps: step2. Verify all of gridItems rect
     * @tc.expected: The rect is equal to expectRect
     */
    float gridHeight = 90.0f;
    int32_t lanes = CalculateGridColumnsOrRows(GRID_HEIGHT, gridHeight, ROW_GAP);
    float averageHeight = (GRID_HEIGHT + ROW_GAP) / lanes - ROW_GAP;
    EXPECT_TRUE(VerifyItemRect(15, lanes, ITEM_WIDTH, averageHeight, 0, FlexDirection::COLUMN));
}

/**
 * @tc.name: ColumnsRows001
 * @tc.desc: Test property about columns/rows Template,
 * test condition that template is empty: ""
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, ColumnsRows001, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetRowsTemplate("");
        model.SetColumnsTemplate("");
        CreateColItem(10);
    });

    /**
     * @tc.steps: step1. compare grid properties and expected value after change.
     * @tc.expected: grid properties equals expected value after change.
     */
    EXPECT_EQ(layoutProperty_->GetRowsTemplateValue(), "1fr");
    EXPECT_EQ(layoutProperty_->GetColumnsTemplateValue(), "1fr");
}

/**
 * @tc.name: ColumnsRows002
 * @tc.desc: Test property about columns/rows Template,
 * set both columns/rows Template with "1fr 1fr 1fr 1fr"
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, ColumnsRows002, TestSize.Level1)
{
    // not set gridItem width/height, gridItem will fill the mesh size by default
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        model.SetRowsTemplate("1fr 1fr 1fr 1fr");
        model.SetColumnsGap(Dimension(COL_GAP));
        model.SetRowsGap(Dimension(ROW_GAP));
        CreateItem(20);
    });

    /**
     * @tc.steps: step1. Set both columns/rows Template
     * @tc.expected: The gridItem width/height will slef-adaption
     */
    int32_t lanes = 4;
    float averageWidth = (GRID_WIDTH + COL_GAP) / lanes - COL_GAP;
    float averageHeight = (GRID_HEIGHT + ROW_GAP) / lanes - ROW_GAP;
    EXPECT_TRUE(VerifyItemRect(12, lanes, averageWidth, averageHeight, 0, FlexDirection::ROW));

    /**
     * @tc.steps: step2. Scroll and Verify
     * @tc.expected: Can not scroll
     */
    UpdateCurrentOffset(-(ITEM_HEIGHT + ROW_GAP));
    EXPECT_TRUE(VerifyItemRect(12, lanes, averageWidth, averageHeight, 0, FlexDirection::ROW));
}

/**
 * @tc.name: LayoutDirection001
 * @tc.desc: Test property layoutDirection,
 * not set columns/rows Template. FlexDirection::ROW
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, LayoutDirection001, TestSize.Level1)
{
    float itemWidth = 100.f;
    Create([itemWidth](GridModelNG model) {
        model.SetLayoutDirection(FlexDirection::ROW);
        model.SetCellLength(ITEM_HEIGHT);
        model.SetMinCount(2);
        model.SetMaxCount(4);
        model.SetColumnsGap(Dimension(COL_GAP));
        model.SetRowsGap(Dimension(ROW_GAP));
        CreateItem(20, itemWidth, ITEM_HEIGHT);
    });

    /**
     * @tc.steps: step1. Not set columns/rows Template
     * @tc.expected: The gridItem rect would effect by minCount, maxCount, gap ...
     */
    EXPECT_TRUE(VerifyItemRect(8, 4, itemWidth, ITEM_HEIGHT, 0, FlexDirection::ROW));

    /**
     * @tc.steps: step2. Scroll and Verify
     * @tc.expected: Can not scroll
     */
    UpdateCurrentOffset(-(ITEM_HEIGHT + ROW_GAP));
    EXPECT_TRUE(VerifyItemRect(8, 4, itemWidth, ITEM_HEIGHT, 0, FlexDirection::ROW));
}

/**
 * @tc.name: LayoutDirection002
 * @tc.desc: Test property layoutDirection,
 * not set columns/rows Template. FlexDirection::ROW_REVERSE
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, LayoutDirection002, TestSize.Level1)
{
    float itemWidth = 100.f;
    Create([itemWidth](GridModelNG model) {
        model.SetLayoutDirection(FlexDirection::ROW_REVERSE);
        model.SetCellLength(ITEM_HEIGHT);
        model.SetMinCount(2);
        model.SetMaxCount(4);
        model.SetColumnsGap(Dimension(COL_GAP));
        model.SetRowsGap(Dimension(ROW_GAP));
        CreateItem(20, itemWidth, ITEM_HEIGHT);
    });

    /**
     * @tc.steps: step1. Not set columns/rows Template
     * @tc.expected: The gridItem rect would effect by minCount, maxCount, gap ...
     */
    EXPECT_TRUE(VerifyItemRect(8, 4, itemWidth, ITEM_HEIGHT, 0, FlexDirection::ROW_REVERSE));

    /**
     * @tc.steps: step3. Scroll and Verify
     * @tc.expected: Can not scroll
     */
    UpdateCurrentOffset(-(ITEM_HEIGHT + ROW_GAP));
    EXPECT_TRUE(VerifyItemRect(8, 4, itemWidth, ITEM_HEIGHT, 0, FlexDirection::ROW_REVERSE));
}

/**
 * @tc.name: LayoutDirection003
 * @tc.desc: Test property layoutDirection,
 * not set columns/rows Template. FlexDirection::COLUMN
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, LayoutDirection003, TestSize.Level1)
{
    float itemHeight = 100.f;
    Create([itemHeight](GridModelNG model) {
        model.SetLayoutDirection(FlexDirection::COLUMN);
        model.SetCellLength(ITEM_WIDTH);
        model.SetMinCount(2);
        model.SetMaxCount(4);
        model.SetColumnsGap(Dimension(COL_GAP));
        model.SetRowsGap(Dimension(ROW_GAP));
        CreateItem(20, ITEM_WIDTH, itemHeight);
    });

    /**
     * @tc.steps: step1. Not set columns/rows Template
     * @tc.expected: The gridItem rect would effect by minCount, maxCount, gap ...
     */
    EXPECT_TRUE(VerifyItemRect(8, 4, ITEM_WIDTH, itemHeight, 0, FlexDirection::COLUMN));

    /**
     * @tc.steps: step3. Scroll and Verify
     * @tc.expected: Can not scroll
     */
    UpdateCurrentOffset(-(ITEM_WIDTH + COL_GAP));
    EXPECT_TRUE(VerifyItemRect(8, 4, ITEM_WIDTH, itemHeight, 0, FlexDirection::COLUMN));
}

/**
 * @tc.name: LayoutDirection004
 * @tc.desc: Test property layoutDirection,
 * not set columns/rows Template. FlexDirection::COLUMN_REVERSE
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, LayoutDirection004, TestSize.Level1)
{
    float itemHeight = 100.f;
    Create([itemHeight](GridModelNG model) {
        model.SetLayoutDirection(FlexDirection::COLUMN_REVERSE);
        model.SetCellLength(ITEM_WIDTH);
        model.SetMinCount(2);
        model.SetMaxCount(4);
        model.SetColumnsGap(Dimension(COL_GAP));
        model.SetRowsGap(Dimension(ROW_GAP));
        CreateItem(20, ITEM_WIDTH, itemHeight);
    });

    /**
     * @tc.steps: step1. Not set columns/rows Template
     * @tc.expected: The gridItem rect would effect by minCount, maxCount, gap ...
     */
    EXPECT_TRUE(VerifyItemRect(8, 4, ITEM_WIDTH, itemHeight, 0, FlexDirection::COLUMN_REVERSE));

    /**
     * @tc.steps: step3. Scroll and Verify
     * @tc.expected: Can not scroll
     */
    UpdateCurrentOffset(-(ITEM_WIDTH + COL_GAP));
    EXPECT_TRUE(VerifyItemRect(8, 4, ITEM_WIDTH, itemHeight, 0, FlexDirection::COLUMN_REVERSE));
}

/**
 * @tc.name: GridItem001
 * @tc.desc: Test property rowStart/rowEnd/colStart/colEnd with colTemplate/rowTemplate
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, GridItem001, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetRowsTemplate("1fr 1fr 1fr 1fr");
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateBigItem(1, 2, 1, 2);
        CreateBigItem(NULL_VALUE, NULL_VALUE, 1, 3);
        CreateBigItem(1, 3, NULL_VALUE, NULL_VALUE);
        CreateItem(7);
    });

    float averageWidth = GRID_WIDTH / 4;
    float averageHeight = GRID_HEIGHT / 4;
    EXPECT_TRUE(VerifyBigItemRect(0, RectF(averageWidth, averageHeight, averageWidth * 2, averageHeight * 2)));
    EXPECT_TRUE(VerifyBigItemRect(1, RectF(0.f, 0.f, averageWidth * 3, averageHeight)));
    EXPECT_TRUE(VerifyBigItemRect(2, RectF(averageWidth * 3, 0.f, averageWidth, averageHeight * 3)));
    EXPECT_TRUE(VerifyBigItemRect(3, RectF(0, averageHeight, averageWidth, averageHeight)));
    EXPECT_TRUE(VerifyBigItemRect(4, RectF(0, averageHeight * 2, averageWidth, averageHeight)));
    EXPECT_TRUE(VerifyBigItemRect(5, RectF(0, averageHeight * 3, averageWidth, averageHeight)));
    EXPECT_TRUE(VerifyBigItemRect(6, RectF(averageWidth, averageHeight * 3, averageWidth, averageHeight)));
    EXPECT_TRUE(VerifyBigItemRect(7, RectF(averageWidth * 2, averageHeight * 3, averageWidth, averageHeight)));
    EXPECT_TRUE(VerifyBigItemRect(8, RectF(averageWidth * 3, averageHeight * 3, averageWidth, averageHeight)));
    EXPECT_TRUE(VerifyBigItemRect(9, RectF()));
}

/**
 * @tc.name: GridItem002
 * @tc.desc: Test property rowStart/rowEnd with rowTemplate
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, GridItem002, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetRowsTemplate("1fr 1fr 1fr 1fr");
        CreateBigRowItem(1, 2);
        CreateBigRowItem(0, 2);
        CreateBigRowItem(2, 3);
        CreateRowItem(7);
    });

    float averageHeight = GRID_HEIGHT / 4;
    EXPECT_TRUE(VerifyBigItemRect(0, RectF(0.f, averageHeight, ITEM_WIDTH, averageHeight * 2)));
    EXPECT_TRUE(VerifyBigItemRect(1, RectF(ITEM_WIDTH, 0.f, ITEM_WIDTH, averageHeight * 3)));
    EXPECT_TRUE(VerifyBigItemRect(2, RectF(ITEM_WIDTH * 2, averageHeight * 2, ITEM_WIDTH, averageHeight * 2)));
    EXPECT_TRUE(VerifyBigItemRect(3, RectF(ITEM_WIDTH * 3, 0, ITEM_WIDTH, averageHeight)));
    EXPECT_TRUE(VerifyBigItemRect(4, RectF(ITEM_WIDTH * 3, averageHeight, ITEM_WIDTH, averageHeight)));
    EXPECT_TRUE(VerifyBigItemRect(5, RectF(ITEM_WIDTH * 3, averageHeight * 2, ITEM_WIDTH, averageHeight)));
    EXPECT_TRUE(VerifyBigItemRect(6, RectF(ITEM_WIDTH * 3, averageHeight * 3, ITEM_WIDTH, averageHeight)));
    EXPECT_TRUE(VerifyBigItemRect(7, RectF()));
    EXPECT_TRUE(VerifyBigItemRect(8, RectF()));
    EXPECT_TRUE(VerifyBigItemRect(9, RectF()));

    UpdateCurrentOffset(-ITEM_WIDTH);
    EXPECT_TRUE(VerifyBigItemRect(0, RectF(-ITEM_WIDTH, averageHeight, ITEM_WIDTH, averageHeight * 2)));
    EXPECT_TRUE(VerifyBigItemRect(1, RectF(0.f, 0.f, ITEM_WIDTH, averageHeight * 3)));
    EXPECT_TRUE(VerifyBigItemRect(2, RectF(ITEM_WIDTH, averageHeight * 2, ITEM_WIDTH, averageHeight * 2)));
}

/**
 * @tc.name: GridItem003
 * @tc.desc: Test property colStart/colEnd with colTemplate
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, GridItem003, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateBigColItem(2, 3);
        CreateBigColItem(0, 2);
        CreateBigColItem(2, 1);
        CreateColItem(7);
    });

    float averageWidth = GRID_WIDTH / 4;
    EXPECT_TRUE(VerifyBigItemRect(0, RectF(averageWidth * 2, 0.f, averageWidth * 2, ITEM_HEIGHT)));
    EXPECT_TRUE(VerifyBigItemRect(1, RectF(0.f, ITEM_HEIGHT, averageWidth * 3, ITEM_HEIGHT)));
    EXPECT_TRUE(VerifyBigItemRect(2, RectF(averageWidth * 2, ITEM_HEIGHT * 2, averageWidth, ITEM_HEIGHT)));
    EXPECT_TRUE(VerifyBigItemRect(3, RectF(averageWidth * 3, ITEM_HEIGHT * 2, averageWidth, ITEM_HEIGHT)));
    EXPECT_TRUE(VerifyBigItemRect(4, RectF(0, ITEM_HEIGHT * 3, averageWidth, ITEM_HEIGHT)));
    EXPECT_TRUE(VerifyBigItemRect(5, RectF(averageWidth, ITEM_HEIGHT * 3, averageWidth, ITEM_HEIGHT)));
    EXPECT_TRUE(VerifyBigItemRect(6, RectF(averageWidth * 2, ITEM_HEIGHT * 3, averageWidth, ITEM_HEIGHT)));
    EXPECT_TRUE(VerifyBigItemRect(7, RectF(averageWidth * 3, ITEM_HEIGHT * 3, averageWidth, ITEM_HEIGHT)));
    EXPECT_TRUE(VerifyBigItemRect(8, RectF()));
    EXPECT_TRUE(VerifyBigItemRect(9, RectF()));

    UpdateCurrentOffset(-ITEM_HEIGHT);
    EXPECT_TRUE(VerifyBigItemRect(0, RectF(averageWidth * 2, -ITEM_HEIGHT, averageWidth * 2, ITEM_HEIGHT)));
    EXPECT_TRUE(VerifyBigItemRect(1, RectF(0.f, 0.f, averageWidth * 3, ITEM_HEIGHT)));
    EXPECT_TRUE(VerifyBigItemRect(2, RectF(averageWidth * 2, ITEM_HEIGHT, averageWidth, ITEM_HEIGHT)));
}

/**
 * @tc.name: EnableScrollInteraction001
 * @tc.desc: Test property about enableScrollInteraction.
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, EnableScrollInteraction001, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetScrollEnabled(true);
        CreateColItem(10);
    });
    EXPECT_EQ(layoutProperty_->GetScrollEnabled(), true);

    Create([](GridModelNG model) {
        model.SetScrollEnabled(false);
        CreateColItem(10);
    });
    EXPECT_EQ(layoutProperty_->GetScrollEnabled(), false);
}

/**
 * @tc.name: Gap001
 * @tc.desc: Test gap
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, Gap001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default
     */
    Create([](GridModelNG model) {
        model.SetRowsTemplate("1fr 1fr 1fr 1fr");
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateItem(16, NULL_VALUE, NULL_VALUE);
    });
    EXPECT_EQ(GetChildRect(frameNode_, 1).GetX(), ITEM_WIDTH);
    EXPECT_EQ(GetChildRect(frameNode_, 4).GetY(), ITEM_HEIGHT);

    /**
     * @tc.steps: step2. Set normal value
     * @tc.expected: valid
     */
    Create([](GridModelNG model) {
        model.SetRowsTemplate("1fr 1fr 1fr 1fr");
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateItem(16, NULL_VALUE, NULL_VALUE);
        model.SetColumnsGap(Dimension(COL_GAP));
        model.SetRowsGap(Dimension(ROW_GAP));
    });
    EXPECT_EQ(GetChildRect(frameNode_, 1).GetX(), (GRID_WIDTH + COL_GAP) / 4);
    EXPECT_EQ(GetChildRect(frameNode_, 4).GetY(), (GRID_HEIGHT + ROW_GAP) / 4);

    /**
     * @tc.steps: step3. Set out of range value
     * @tc.expected: Invalid
     */
    Create([](GridModelNG model) {
        model.SetRowsTemplate("1fr 1fr 1fr 1fr");
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateItem(16, NULL_VALUE, NULL_VALUE);
        model.SetColumnsGap(Dimension(-1));
        model.SetRowsGap(Dimension(-1));
    });
    EXPECT_EQ(GetChildRect(frameNode_, 1).GetX(), ITEM_WIDTH);
    EXPECT_EQ(GetChildRect(frameNode_, 4).GetY(), ITEM_HEIGHT);

    Create([](GridModelNG model) {
        model.SetRowsTemplate("1fr 1fr 1fr 1fr");
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateItem(16, NULL_VALUE, NULL_VALUE);
        model.SetColumnsGap(Dimension(GRID_WIDTH / 3));
        model.SetRowsGap(Dimension(GRID_HEIGHT / 3 + 1));
    });
    EXPECT_EQ(GetChildRect(frameNode_, 1).GetX(), ITEM_WIDTH);
    EXPECT_EQ(GetChildRect(frameNode_, 4).GetY(), ITEM_HEIGHT);

    /**
     * @tc.steps: step4. Set grid scrollable
     * @tc.expected: the scrollable direction gap valid, the another one invalid
     */
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateColItem(16);
        model.SetColumnsGap(Dimension(GRID_WIDTH / 3));
        model.SetRowsGap(Dimension(GRID_HEIGHT / 3));
    });
    EXPECT_EQ(GetChildRect(frameNode_, 1).GetX(), ITEM_WIDTH);
    EXPECT_EQ(GetChildRect(frameNode_, 4).GetY(), ITEM_HEIGHT + GRID_HEIGHT / 3);
}

/**
 * @tc.name: MinMaxCount001
 * @tc.desc: Test minCount maxCount
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, MinMaxCount001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default
     */
    Create([](GridModelNG model) {
        model.SetLayoutDirection(FlexDirection::ROW);
        CreateColItem(16);
    });
    EXPECT_EQ(GetChildRect(frameNode_, 15).GetY(), 0);
    EXPECT_EQ(GetChildRect(frameNode_, 15).GetX(), 0);

    /**
     * @tc.steps: step2. Valid
     */
    Create([](GridModelNG model) {
        model.SetLayoutDirection(FlexDirection::ROW);
        CreateColItem(16);
        model.SetMinCount(2);
        model.SetMaxCount(5);
    });
    EXPECT_EQ(GetChildRect(frameNode_, 15).GetY(), ITEM_HEIGHT * 3);
    EXPECT_EQ(GetChildRect(frameNode_, 15).GetX(), 0);

    /**
     * @tc.steps: step3. Invalid
     */
    Create([](GridModelNG model) {
        model.SetLayoutDirection(FlexDirection::ROW);
        CreateColItem(16);
        model.SetMinCount(-1);
        model.SetMaxCount(-1);
    });
    EXPECT_EQ(GetChildRect(frameNode_, 15).GetY(), 0);
    EXPECT_EQ(GetChildRect(frameNode_, 15).GetX(), 0);
}

/**
 * @tc.name: EdgeEffectOption001
 * @tc.desc: Test EdgeEffectOption
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, EdgeEffectOption001, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateColItem(20);
        model.SetEdgeEffect(EdgeEffect::SPRING, false);
    });
    EXPECT_FALSE(pattern_->GetAlwaysEnabled());
    EXPECT_TRUE(pattern_->scrollable_);
}

/**
 * @tc.name: EdgeEffectOption002
 * @tc.desc: Test EdgeEffectOption
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, EdgeEffectOption002, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateColItem(20);
        model.SetEdgeEffect(EdgeEffect::SPRING, true);
    });
    EXPECT_TRUE(pattern_->GetAlwaysEnabled());
    EXPECT_TRUE(pattern_->scrollable_);
}

/**
 * @tc.name: EdgeEffectOption003
 * @tc.desc: Test EdgeEffectOption
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, EdgeEffectOption003, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateColItem(3); // 3 is item count
        model.SetEdgeEffect(EdgeEffect::SPRING, false);
    });
    EXPECT_FALSE(pattern_->GetAlwaysEnabled());
    EXPECT_FALSE(pattern_->scrollable_);
}

/**
 * @tc.name: EdgeEffectOption004
 * @tc.desc: Test EdgeEffectOption
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, EdgeEffectOption004, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateColItem(3); // 3 is item count
        model.SetEdgeEffect(EdgeEffect::SPRING, true);
    });
    EXPECT_TRUE(pattern_->GetAlwaysEnabled());
    EXPECT_TRUE(pattern_->scrollable_);
}

/**
 * @tc.name: GridSetFrictionTest001
 * @tc.desc: Test SetFriction Function.
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, GridSetFriction001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. friction <= 0
     * @tc.expected: friction would be default
     */
    Create([](GridModelNG model) { model.SetFriction(NULL_VALUE); });
    EXPECT_DOUBLE_EQ(pattern_->GetFriction(), DEFAULT_FRICTION);
    Create([](GridModelNG model) { model.SetFriction(0); });
    EXPECT_DOUBLE_EQ(pattern_->GetFriction(), DEFAULT_FRICTION);

    /**
     * @tc.steps: step2. friction > 0
     * @tc.expected: friction would be itself
     */
    Create([](GridModelNG model) { model.SetFriction(1); });
    EXPECT_DOUBLE_EQ(pattern_->GetFriction(), 1);
}

/**
 * @tc.name: GridItemHoverEventTest001
 * @tc.desc: GirdItem hover event test.
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, GridItemHoverEventTest001, TestSize.Level1)
{
    Create([](GridModelNG model) {
        CreateColItem(10, false, GridItemStyle::PLAIN);
    });

    /**
     * @tc.steps: step2. Get girdItem frameNode and pattern, set callback function.
     * @tc.expected: Related function is called.
     */
    auto gridItemPattern = GetChildPattern<GridItemPattern>(frameNode_, 0);
    gridItemPattern->isPressed_ = false;
    gridItemPattern->HandleHoverEvent(true);
    EXPECT_TRUE(gridItemPattern->isHover_);
    gridItemPattern->HandleHoverEvent(false);
    EXPECT_FALSE(gridItemPattern->isHover_);

    /**
     * @tc.steps: step3. Test gridItem hover event when hoverEvent_ has value.
     * @tc.expected: InitHoverEvent func will return.
     */
    gridItemPattern->hoverEvent_ = AceType::MakeRefPtr<InputEvent>([](MouseInfo&) {});
    gridItemPattern->InitHoverEvent();
}

/**
 * @tc.name: GridItemPressEventTest001
 * @tc.desc: GirdItem press event test.
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, GridItemPressEventTest001, TestSize.Level1)
{
    Create([](GridModelNG model) {
        CreateColItem(10, false, GridItemStyle::PLAIN);
    });

    /**
     * @tc.steps: step2. Get girdItem frameNode and pattern, set callback function.
     * @tc.expected: Related function is called.
     */
    auto gridItemPattern = GetChildPattern<GridItemPattern>(frameNode_, 0);
    gridItemPattern->isHover_ = false;
    gridItemPattern->HandlePressEvent(true);
    EXPECT_TRUE(gridItemPattern->isPressed_);
    gridItemPattern->HandlePressEvent(false);
    EXPECT_FALSE(gridItemPattern->isPressed_);

    /**
     * @tc.steps: step3. Test gridItem press event when touchListener_ has value.
     * @tc.expected: InitPressEvent func will return.
     */
    auto touchCallback = [](TouchEventInfo& info) {};
    auto touchEvent = AceType::MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    gridItemPattern->touchListener_ = touchEvent;
    gridItemPattern->InitPressEvent();
}
} // namespace OHOS::Ace::NG
