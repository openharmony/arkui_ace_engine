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
    AssertionResult VerifyBigItemRect(int32_t index, RectF expectRect);
};

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
        CreateFixedItem(10);
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
    /**
     * @tc.cases: Invalid GapValue
     * @tc.expected: Gap would be null
    */
    Create([](GridModelNG model) {
        model.SetRowsGap(Dimension(-5));
        model.SetColumnsGap(Dimension(-10));
        CreateFixedItem(10);
    });
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
    /**
     * @tc.cases: Only set ColumnsTemplate, set gap
     * @tc.expected: Axis is VERTICAL, has four cols, has gap
     */
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        model.SetColumnsGap(Dimension(COL_GAP));
        model.SetRowsGap(Dimension(ROW_GAP));
        CreateFixedItem(10);
    });
    EXPECT_EQ(pattern_->GetAxis(), Axis::VERTICAL);
    EXPECT_EQ(pattern_->GetCrossCount(), 4);

    EXPECT_LT(GetChildX(frameNode_, 0), GetChildX(frameNode_, 1));
    EXPECT_LT(GetChildX(frameNode_, 1), GetChildX(frameNode_, 2));
    EXPECT_LT(GetChildX(frameNode_, 2), GetChildX(frameNode_, 3));
    EXPECT_EQ(GetChildX(frameNode_, 0), GetChildX(frameNode_, 4));

    EXPECT_EQ(GetChildX(frameNode_, 1), GetChildWidth(frameNode_, 0) + COL_GAP);
    EXPECT_EQ(GetChildY(frameNode_, 4), ITEM_HEIGHT + ROW_GAP);
}

/**
 * @tc.name: ColumnsTemplate002
 * @tc.desc: Test property about columnsTemplate,
 * test condition that template is "1fr 2fr 3fr 1fr"
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, ColumnsTemplate002, TestSize.Level1)
{
    /**
     * @tc.cases: Set ColumnsTemplate "1fr 2fr 3fr 1fr"
     * @tc.expected: Cols has different width
     */
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 2fr 3fr 1fr");
        CreateFixedItem(10);
    });
    float parts = 1 + 2 + 3 + 1; // 7
    float firstItemWidth = GRID_WIDTH / parts;
    EXPECT_EQ(GetChildWidth(frameNode_, 0), firstItemWidth * 1);
    EXPECT_EQ(GetChildWidth(frameNode_, 1), firstItemWidth * 2);
    EXPECT_EQ(GetChildWidth(frameNode_, 2), firstItemWidth * 3);
    EXPECT_EQ(GetChildWidth(frameNode_, 3), firstItemWidth * 1);
}

/**
 * @tc.name: ColumnsTemplate003
 * @tc.desc: Test property about columnsTemplate,
 * test condition that template is "1fr 0fr 0fr 1fr"
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, ColumnsTemplate003, TestSize.Level1)
{
    /**
     * @tc.cases: Set ColumnsTemplate "1fr 0fr 0fr 1fr"
     * @tc.expected: "0fr" col width is zero
     */
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 0fr 0fr 1fr");
        CreateFixedItem(10);
    });
    EXPECT_GT(GetChildWidth(frameNode_, 0), 0.f);
    EXPECT_EQ(GetChildWidth(frameNode_, 1), 0.f);
    EXPECT_EQ(GetChildWidth(frameNode_, 2), 0.f);
    EXPECT_GT(GetChildWidth(frameNode_, 3), 0.f);
}

/**
 * @tc.name: ColumnsTemplate004
 * @tc.desc: Test property about columnsTemplate,
 * test normal condition that template is "repeat(auto-fit, 90px)"
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, ColumnsTemplate004, TestSize.Level1)
{
    /**
     * @tc.cases: Set ColumnsTemplate "repeat(auto-fit, 90px)"
     * @tc.expected: Cols number and gridItem width is self-adaptation
     */
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("repeat(auto-fit, 90px)");
        CreateFixedItem(10);
    });
    float minItemWidth = 90.f;
    int32_t cols = floor(GRID_WIDTH / minItemWidth); // 5
    EXPECT_EQ(pattern_->GetCrossCount(), cols);
    float expectItemWidth = GRID_WIDTH / cols; // 96.f
    EXPECT_EQ(GetChildWidth(frameNode_, 0), expectItemWidth);
}

/**
 * @tc.name: ColumnsTemplate005
 * @tc.desc: Test property about columnsTemplate
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, ColumnsTemplate005, TestSize.Level1)
{
    /**
     * @tc.cases: Set ColumnsTemplate "repeat(auto-fill, 90px)"
     * @tc.expected: GridItem width is fixed
     */
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("repeat(auto-fill, 90px)");
        CreateFixedItem(10);
    });
    float itemWidth = 90.f;
    int32_t cols = floor(GRID_WIDTH / itemWidth); // 5
    EXPECT_EQ(pattern_->GetCrossCount(), cols);
    EXPECT_EQ(GetChildWidth(frameNode_, 0), itemWidth);
}

/**
 * @tc.name: ColumnsTemplate006
 * @tc.desc: Test property about columnsTemplate
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, ColumnsTemplate006, TestSize.Level1)
{
    /**
     * @tc.cases: Set Invalid ColumnsTemplate ""
     * @tc.expected: Only has one col
     */
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("");
        CreateFixedItem(10);
    });
    EXPECT_EQ(pattern_->GetCrossCount(), 1);
}

/**
 * @tc.name: RowsTemplate001
 * @tc.desc: Test property about rowsTemplate and Gap,
 * test normal condition that template is "1fr 1fr 1fr 1fr"
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, RowsTemplate001, TestSize.Level1)
{
    /**
     * @tc.cases: Only set RowsTemplate, set gap
     * @tc.expected: Axis is HORIZONTAL, has four rows, has gap
     */
    Create([](GridModelNG model) {
        model.SetRowsTemplate("1fr 1fr 1fr 1fr");
        model.SetColumnsGap(Dimension(COL_GAP));
        model.SetRowsGap(Dimension(ROW_GAP));
        CreateFixedItem(10);
    });
    EXPECT_EQ(pattern_->GetAxis(), Axis::HORIZONTAL);
    EXPECT_EQ(pattern_->GetCrossCount(), 4);

    EXPECT_LT(GetChildY(frameNode_, 0), GetChildY(frameNode_, 1));
    EXPECT_LT(GetChildY(frameNode_, 1), GetChildY(frameNode_, 2));
    EXPECT_LT(GetChildY(frameNode_, 2), GetChildY(frameNode_, 3));
    EXPECT_EQ(GetChildY(frameNode_, 0), GetChildY(frameNode_, 4));

    EXPECT_EQ(GetChildY(frameNode_, 1), GetChildHeight(frameNode_, 0) + ROW_GAP);
    EXPECT_EQ(GetChildX(frameNode_, 4), ITEM_WIDTH + COL_GAP);
}

/**
 * @tc.name: RowsTemplate002
 * @tc.desc: Test property about rowsTemplate,
 * test condition that template is "1fr 2fr 3fr 1fr"
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, RowsTemplate002, TestSize.Level1)
{
    /**
     * @tc.cases: Set RowsTemplate "1fr 2fr 3fr 1fr"
     * @tc.expected: Rows has different width
     */
    Create([](GridModelNG model) {
        model.SetRowsTemplate("1fr 2fr 3fr 1fr");
        CreateFixedItem(10);
    });
    float parts = 1 + 2 + 3 + 1; // 7
    float firstItemHeight = GRID_HEIGHT / parts;
    EXPECT_EQ(GetChildHeight(frameNode_, 0), firstItemHeight * 1);
    EXPECT_EQ(GetChildHeight(frameNode_, 1), firstItemHeight * 2);
    EXPECT_EQ(GetChildHeight(frameNode_, 2), firstItemHeight * 3);
    EXPECT_EQ(GetChildHeight(frameNode_, 3), firstItemHeight * 1);
}

/**
 * @tc.name: RowsTemplate003
 * @tc.desc: Test property about rowsTemplate,
 * test condition that template is "1fr 0fr 0fr 1fr"
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, RowsTemplate003, TestSize.Level1)
{
    /**
     * @tc.cases: Set RowsTemplate "1fr 0fr 0fr 1fr"
     * @tc.expected: "0fr" row width is zero
     */
    Create([](GridModelNG model) {
        model.SetRowsTemplate("1fr 0fr 0fr 1fr");
        CreateFixedItem(10);
    });
    EXPECT_GT(GetChildHeight(frameNode_, 0), 0.f);
    EXPECT_EQ(GetChildHeight(frameNode_, 1), 0.f);
    EXPECT_EQ(GetChildHeight(frameNode_, 2), 0.f);
    EXPECT_GT(GetChildHeight(frameNode_, 3), 0.f);
}

/**
 * @tc.name: RowsTemplate004
 * @tc.desc: Test property about rowsTemplate and Gap,
 * test normal condition that template is "repeat(auto-fit, 90px)"
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, RowsTemplate004, TestSize.Level1)
{
    /**
     * @tc.cases: Set RowsTemplate "repeat(auto-fit, 90px)"
     * @tc.expected: Rows number and gridItem height is self-adaptation
     */
    Create([](GridModelNG model) {
        model.SetRowsTemplate("repeat(auto-fit, 90px)");
        CreateFixedItem(10);
    });
    float minItemHeight = 90.f;
    int32_t rows = floor(GRID_HEIGHT / minItemHeight); // 8
    EXPECT_EQ(pattern_->GetCrossCount(), rows);
    float expectItemHeight = GRID_HEIGHT / rows; // 100.f
    EXPECT_EQ(GetChildHeight(frameNode_, 0), expectItemHeight);
}

/**
 * @tc.name: RowsTemplate005
 * @tc.desc: Test property about rowsTemplate
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, RowsTemplate005, TestSize.Level1)
{
    /**
     * @tc.cases: Set RowsTemplate "repeat(auto-fill, 90px)"
     * @tc.expected: GridItem width is fixed
     */
    Create([](GridModelNG model) {
        model.SetRowsTemplate("repeat(auto-fill, 90px)");
        CreateFixedItem(10);
    });
    float itemHeight = 90.f;
    int32_t rows = floor(GRID_HEIGHT / itemHeight); // 5
    EXPECT_EQ(pattern_->GetCrossCount(), rows);
    EXPECT_EQ(GetChildHeight(frameNode_, 0), itemHeight);
}

/**
 * @tc.name: RowsTemplate006
 * @tc.desc: Test property about rowsTemplate
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, RowsTemplate006, TestSize.Level1)
{
    /**
     * @tc.cases: Set Invalid RowsTemplate ""
     * @tc.expected: Only has one row
     */
    Create([](GridModelNG model) {
        model.SetRowsTemplate("");
        CreateFixedItem(10);
    });
    EXPECT_EQ(pattern_->GetCrossCount(), 1);
}

/**
 * @tc.name: ColumnsRows001
 * @tc.desc: Test property about columns/rows Template,
 * set both columns/rows Template with "1fr 1fr 1fr 1fr"
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, ColumnsRows001, TestSize.Level1)
{
    /**
     * @tc.cases: Both set ColumnsTemplate and RowsTemplate
     * @tc.expected: GridItem will fill the mesh size by default
     */
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        model.SetRowsTemplate("1fr 1fr 1fr 1fr");
        CreateItem(20);
    });
    EXPECT_EQ(pattern_->GetCrossCount(), 4);
    EXPECT_TRUE(IsEqual(GetChildSize(frameNode_, 0), SizeF(ITEM_WIDTH, ITEM_HEIGHT)));
}

/**
 * @tc.name: LayoutDirection001
 * @tc.desc: Test property layoutDirection,
 * not set columns/rows Template. FlexDirection::ROW
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, LayoutDirection001, TestSize.Level1)
{
    /**
     * @tc.cases: Set LayoutDirection ROW, set minCount maxCount, setgap
     * @tc.expected: Axis is VERTICAL, has three cols, has gap
     */
    Create([](GridModelNG model) {
        model.SetLayoutDirection(FlexDirection::ROW);
        model.SetCellLength(ITEM_HEIGHT);
        model.SetMinCount(2);
        model.SetMaxCount(4);
        model.SetColumnsGap(Dimension(COL_GAP));
        model.SetRowsGap(Dimension(ROW_GAP));
        CreateFixedItem(10);
    });
    EXPECT_EQ(pattern_->GetAxis(), Axis::VERTICAL);
    EXPECT_EQ(pattern_->GetCrossCount(), 3);

    EXPECT_EQ(GetChildX(frameNode_, 1), ITEM_WIDTH + COL_GAP);
    EXPECT_EQ(GetChildY(frameNode_, 4), ITEM_HEIGHT + ROW_GAP);
}

/**
 * @tc.name: LayoutDirection002
 * @tc.desc: Test property layoutDirection,
 * not set columns/rows Template. FlexDirection::ROW_REVERSE
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, LayoutDirection002, TestSize.Level1)
{
    /**
     * @tc.cases: Set LayoutDirection ROW_REVERSE, set minCount maxCount, set bigger itemWidth
     * @tc.expected: Has minCount cols, gridItem from right to left
     */
    float minCount = 2;
    float itemWidth = GRID_WIDTH / minCount + 100.f; // greater than half of GRID_WIDTH
    Create([=](GridModelNG model) {
        model.SetLayoutDirection(FlexDirection::ROW_REVERSE);
        model.SetCellLength(ITEM_HEIGHT);
        model.SetMinCount(minCount);
        model.SetMaxCount(4);
        CreateItem(10, itemWidth, ITEM_HEIGHT);
    });
    EXPECT_EQ(pattern_->GetCrossCount(), minCount);
    EXPECT_GT(GetChildX(frameNode_, 0), GetChildX(frameNode_, 1));
}

/**
 * @tc.name: LayoutDirection003
 * @tc.desc: Test property layoutDirection,
 * not set columns/rows Template. FlexDirection::COLUMN
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, LayoutDirection003, TestSize.Level1)
{
    /**
     * @tc.cases: Set LayoutDirection COLUMN, set minCount maxCount, set smaller itemHeight
     * @tc.expected: Has maxCount rows, gridItem from top to bottom
     */
    float maxCount = 4;
    float itemHeight = GRID_HEIGHT / maxCount - 100.f; // less than quarter of GRID_HEIGHT
    Create([=](GridModelNG model) {
        model.SetLayoutDirection(FlexDirection::COLUMN);
        model.SetCellLength(ITEM_WIDTH);
        model.SetMinCount(2);
        model.SetMaxCount(maxCount);
        CreateItem(10, ITEM_WIDTH, itemHeight);
    });
    EXPECT_LT(GetChildY(frameNode_, 0), GetChildY(frameNode_, 1));
    EXPECT_LT(GetChildY(frameNode_, 1), GetChildY(frameNode_, 2));
    EXPECT_LT(GetChildY(frameNode_, 2), GetChildY(frameNode_, 3));
    EXPECT_EQ(GetChildY(frameNode_, 0), GetChildY(frameNode_, 4));
}

/**
 * @tc.name: LayoutDirection004
 * @tc.desc: Test property layoutDirection,
 * not set columns/rows Template. FlexDirection::COLUMN_REVERSE
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, LayoutDirection004, TestSize.Level1)
{
    /**
     * @tc.cases: Set LayoutDirection COLUMN_REVERSE
     * @tc.expected: GridItem from bottom to top
     */
    Create([](GridModelNG model) {
        model.SetLayoutDirection(FlexDirection::COLUMN_REVERSE);
        model.SetCellLength(ITEM_WIDTH);
        model.SetMinCount(2);
        model.SetMaxCount(4);
        CreateFixedItem(10);
    });
    EXPECT_GT(GetChildY(frameNode_, 0), GetChildY(frameNode_, 1));
    EXPECT_GT(GetChildY(frameNode_, 1), GetChildY(frameNode_, 2));
    EXPECT_GT(GetChildY(frameNode_, 2), GetChildY(frameNode_, 3));
    EXPECT_EQ(GetChildY(frameNode_, 0), GetChildY(frameNode_, 4));
}

/**
 * @tc.name: BigItem001
 * @tc.desc: Test property rowStart/rowEnd/colStart/colEnd with colTemplate/rowTemplate
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, BigItem001, TestSize.Level1)
{
    /**
     * @tc.cases: Set RowsTemplate and ColumnsTemplate, create big items
     * @tc.expected: Big items have bigger size
     */
    Create([](GridModelNG model) {
        model.SetRowsTemplate("1fr 1fr 1fr 1fr");
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateBigItem(1, 2, 1, 2);
        CreateBigItem(NULL_VALUE, NULL_VALUE, 1, 3);
        CreateBigItem(1, 3, NULL_VALUE, NULL_VALUE);
        CreateItem(7);
    });
    EXPECT_TRUE(VerifyBigItemRect(0, RectF(ITEM_WIDTH, ITEM_HEIGHT, ITEM_WIDTH * 2, ITEM_HEIGHT * 2)));
    EXPECT_TRUE(VerifyBigItemRect(1, RectF(0.f, 0.f, ITEM_WIDTH * 3, ITEM_HEIGHT)));
    EXPECT_TRUE(VerifyBigItemRect(2, RectF(ITEM_WIDTH * 3, 0.f, ITEM_WIDTH, ITEM_HEIGHT * 3)));

    EXPECT_TRUE(VerifyBigItemRect(3, RectF(0, ITEM_HEIGHT, ITEM_WIDTH, ITEM_HEIGHT)));
    EXPECT_TRUE(VerifyBigItemRect(4, RectF(0, ITEM_HEIGHT * 2, ITEM_WIDTH, ITEM_HEIGHT)));
    EXPECT_TRUE(VerifyBigItemRect(5, RectF(0, ITEM_HEIGHT * 3, ITEM_WIDTH, ITEM_HEIGHT)));
    EXPECT_TRUE(VerifyBigItemRect(6, RectF(ITEM_WIDTH, ITEM_HEIGHT * 3, ITEM_WIDTH, ITEM_HEIGHT)));
    EXPECT_TRUE(VerifyBigItemRect(7, RectF(ITEM_WIDTH * 2, ITEM_HEIGHT * 3, ITEM_WIDTH, ITEM_HEIGHT)));
    EXPECT_TRUE(VerifyBigItemRect(8, RectF(ITEM_WIDTH * 3, ITEM_HEIGHT * 3, ITEM_WIDTH, ITEM_HEIGHT)));
    EXPECT_TRUE(VerifyBigItemRect(9, RectF()));
}

/**
 * @tc.name: BigItem002
 * @tc.desc: Test property rowStart/rowEnd with rowTemplate
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, BigItem002, TestSize.Level1)
{
    /**
     * @tc.cases: Only set RowsTemplate, create big items
     * @tc.expected: Big items have bigger size
     */
    Create([](GridModelNG model) {
        model.SetRowsTemplate("1fr 1fr 1fr 1fr");
        CreateBigRowItem(1, 2);
        CreateBigRowItem(0, 2);
        CreateBigRowItem(2, 3);
        CreateFixedItem(7);
    });
    EXPECT_TRUE(VerifyBigItemRect(0, RectF(0.f, ITEM_HEIGHT, ITEM_WIDTH, ITEM_HEIGHT * 2)));
    EXPECT_TRUE(VerifyBigItemRect(1, RectF(ITEM_WIDTH, 0.f, ITEM_WIDTH, ITEM_HEIGHT * 3)));
    EXPECT_TRUE(VerifyBigItemRect(2, RectF(ITEM_WIDTH * 2, ITEM_HEIGHT * 2, ITEM_WIDTH, ITEM_HEIGHT * 2)));

    EXPECT_TRUE(VerifyBigItemRect(3, RectF(ITEM_WIDTH * 3, 0, ITEM_WIDTH, ITEM_HEIGHT)));
    EXPECT_TRUE(VerifyBigItemRect(4, RectF(ITEM_WIDTH * 3, ITEM_HEIGHT, ITEM_WIDTH, ITEM_HEIGHT)));
    EXPECT_TRUE(VerifyBigItemRect(5, RectF(ITEM_WIDTH * 3, ITEM_HEIGHT * 2, ITEM_WIDTH, ITEM_HEIGHT)));
    EXPECT_TRUE(VerifyBigItemRect(6, RectF(ITEM_WIDTH * 3, ITEM_HEIGHT * 3, ITEM_WIDTH, ITEM_HEIGHT)));
    EXPECT_TRUE(VerifyBigItemRect(7, RectF()));
    EXPECT_TRUE(VerifyBigItemRect(8, RectF()));
    EXPECT_TRUE(VerifyBigItemRect(9, RectF()));
}

/**
 * @tc.name: BigItem003
 * @tc.desc: Test property colStart/colEnd with colTemplate
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, BigItem003, TestSize.Level1)
{
    /**
     * @tc.cases: Only set ColumnsTemplate, create big items
     * @tc.expected: Big items have bigger size
     */
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateBigColItem(2, 3);
        CreateBigColItem(0, 2);
        CreateBigColItem(2, 1);
        CreateFixedItem(7);
    });
    EXPECT_TRUE(VerifyBigItemRect(0, RectF(ITEM_WIDTH * 2, 0.f, ITEM_WIDTH * 2, ITEM_HEIGHT)));
    EXPECT_TRUE(VerifyBigItemRect(1, RectF(0.f, ITEM_HEIGHT, ITEM_WIDTH * 3, ITEM_HEIGHT)));
    EXPECT_TRUE(VerifyBigItemRect(2, RectF(ITEM_WIDTH * 2, ITEM_HEIGHT * 2, ITEM_WIDTH, ITEM_HEIGHT)));

    EXPECT_TRUE(VerifyBigItemRect(3, RectF(ITEM_WIDTH * 3, ITEM_HEIGHT * 2, ITEM_WIDTH, ITEM_HEIGHT)));
    EXPECT_TRUE(VerifyBigItemRect(4, RectF(0, ITEM_HEIGHT * 3, ITEM_WIDTH, ITEM_HEIGHT)));
    EXPECT_TRUE(VerifyBigItemRect(5, RectF(ITEM_WIDTH, ITEM_HEIGHT * 3, ITEM_WIDTH, ITEM_HEIGHT)));
    EXPECT_TRUE(VerifyBigItemRect(6, RectF(ITEM_WIDTH * 2, ITEM_HEIGHT * 3, ITEM_WIDTH, ITEM_HEIGHT)));
    EXPECT_TRUE(VerifyBigItemRect(7, RectF(ITEM_WIDTH * 3, ITEM_HEIGHT * 3, ITEM_WIDTH, ITEM_HEIGHT)));
    EXPECT_TRUE(VerifyBigItemRect(8, RectF()));
    EXPECT_TRUE(VerifyBigItemRect(9, RectF()));
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
        CreateFixedItem(10);
    });
    EXPECT_TRUE(layoutProperty_->GetScrollEnabledValue());
}
    
/**
 * @tc.name: EnableScrollInteraction002
 * @tc.desc: Test property about enableScrollInteraction.
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, EnableScrollInteraction002, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetScrollEnabled(false);
        CreateFixedItem(10);
    });
    EXPECT_FALSE(layoutProperty_->GetScrollEnabledValue());
}

/**
 * @tc.name: Gap001
 * @tc.desc: Test gap
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, Gap001, TestSize.Level1)
{
    /**
     * @tc.cases: Do not set gap
     * @tc.expected: Has no gap
     */
    Create([](GridModelNG model) {
        model.SetRowsTemplate("1fr 1fr 1fr 1fr");
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateItem(16, NULL_VALUE, NULL_VALUE);
    });
    EXPECT_EQ(GetChildX(frameNode_, 1) - GetChildWidth(frameNode_, 1), 0.f);
    EXPECT_EQ(GetChildY(frameNode_, 4) - GetChildHeight(frameNode_, 1), 0.f);
}

/**
 * @tc.name: Gap002
 * @tc.desc: Test gap
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, Gap002, TestSize.Level1)
{
    /**
     * @tc.cases: Set normal gap
     * @tc.expected: Has gap
     */
    Create([](GridModelNG model) {
        model.SetRowsTemplate("1fr 1fr 1fr 1fr");
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        model.SetColumnsGap(Dimension(COL_GAP));
        model.SetRowsGap(Dimension(ROW_GAP));
        CreateItem(16, NULL_VALUE, NULL_VALUE);
    });
    EXPECT_EQ(GetChildX(frameNode_, 1) - GetChildWidth(frameNode_, 1), COL_GAP);
    EXPECT_EQ(GetChildY(frameNode_, 4) - GetChildHeight(frameNode_, 1), ROW_GAP);
}

/**
 * @tc.name: Gap003
 * @tc.desc: Test gap
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, Gap003, TestSize.Level1)
{
    /**
     * @tc.cases: Set out of range gap, less than zero
     * @tc.expected: Has no gap
     */
    Create([](GridModelNG model) {
        model.SetRowsTemplate("1fr 1fr 1fr 1fr");
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        model.SetColumnsGap(Dimension(-1));
        model.SetRowsGap(Dimension(-1));
        CreateItem(16, NULL_VALUE, NULL_VALUE);
    });
    EXPECT_EQ(GetChildX(frameNode_, 1) - GetChildWidth(frameNode_, 1), 0.f);
    EXPECT_EQ(GetChildY(frameNode_, 4) - GetChildHeight(frameNode_, 1), 0.f);
}

/**
 * @tc.name: Gap004
 * @tc.desc: Test gap
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, Gap004, TestSize.Level1)
{
    /**
     * @tc.cases: Set out of range gap, total gap greater than grid size
     * @tc.expected: Has no gap
     */
    Create([](GridModelNG model) {
        model.SetRowsTemplate("1fr 1fr 1fr 1fr");
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        model.SetColumnsGap(Dimension(GRID_WIDTH / 3));
        model.SetRowsGap(Dimension(GRID_HEIGHT / 3 + 1));
        CreateItem(16, NULL_VALUE, NULL_VALUE);
    });
    EXPECT_EQ(GetChildX(frameNode_, 1) - GetChildWidth(frameNode_, 1), 0.f);
    EXPECT_EQ(GetChildY(frameNode_, 4) - GetChildHeight(frameNode_, 1), 0.f);
}

/**
 * @tc.name: Gap005
 * @tc.desc: Test gap
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, Gap005, TestSize.Level1)
{
    /**
     * @tc.cases: Only set ColumnsTemplate
     * @tc.expected: Grid is scrollable, the scrollable direction gap valid, the another one invalid
     */
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        model.SetColumnsGap(Dimension(GRID_WIDTH / 3));
        model.SetRowsGap(Dimension(GRID_HEIGHT / 3));
        CreateFixedItem(16);
    });
    EXPECT_TRUE(layoutProperty_->IsConfiguredScrollable());
    EXPECT_EQ(GetChildX(frameNode_, 1) - GetChildWidth(frameNode_, 1), 0.f);
    EXPECT_EQ(GetChildY(frameNode_, 4) - GetChildHeight(frameNode_, 1), GRID_HEIGHT / 3);
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
        CreateFixedItem(20);
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
        CreateFixedItem(20);
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
        CreateFixedItem(3); // 3 is item count
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
        CreateFixedItem(3); // 3 is item count
        model.SetEdgeEffect(EdgeEffect::SPRING, true);
    });
    EXPECT_TRUE(pattern_->GetAlwaysEnabled());
    EXPECT_TRUE(pattern_->scrollable_);
}

/**
 * @tc.name: GridSetFriction001
 * @tc.desc: Test SetFriction Function.
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, GridSetFriction001, TestSize.Level1)
{
    /**
     * @tc.cases: Set friction less than zero
     * @tc.expected: friction would be default
     */
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        model.SetFriction(-1.0);
    });
    EXPECT_DOUBLE_EQ(pattern_->GetFriction(), DEFAULT_FRICTION);
}

/**
 * @tc.name: GridSetFriction002
 * @tc.desc: Test SetFriction Function.
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, GridSetFriction002, TestSize.Level1)
{
    /**
     * @tc.cases: Set friction equal to zero
     * @tc.expected: friction would be default
     */
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        model.SetFriction(0.0);
    });
    EXPECT_DOUBLE_EQ(pattern_->GetFriction(), DEFAULT_FRICTION);
}

/**
 * @tc.name: GridSetFriction003
 * @tc.desc: Test SetFriction Function.
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, GridSetFriction003, TestSize.Level1)
{
    /**
     * @tc.cases: Set friction greater than zero
     * @tc.expected: Friction would be itself
     */
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        model.SetFriction(1.0);
    });
    EXPECT_DOUBLE_EQ(pattern_->GetFriction(), 1.0);
}

/**
 * @tc.name: GridItemHoverEventTest001
 * @tc.desc: GirdItem hover event test.
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, GridItemHoverEventTest001, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateFixedItem(10, GridItemStyle::PLAIN);
    });
    auto gridItemPattern = GetChildPattern<GridItemPattern>(frameNode_, 0);

    /**
     * @tc.steps: step1. Hover gridItem
     * @tc.expected: isHover_ is true
     */
    gridItemPattern->HandleHoverEvent(true);
    EXPECT_TRUE(gridItemPattern->isHover_);

    /**
     * @tc.steps: step2. Leave gridItem
     * @tc.expected: isHover_ is false
     */
    gridItemPattern->HandleHoverEvent(false);
    EXPECT_FALSE(gridItemPattern->isHover_);
}

/**
 * @tc.name: GridItemPressEventTest001
 * @tc.desc: GirdItem press event test.
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, GridItemPressEventTest001, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateFixedItem(10, GridItemStyle::PLAIN);
    });
    auto gridItemPattern = GetChildPattern<GridItemPattern>(frameNode_, 0);

    /**
     * @tc.steps: step1. Press gridItem
     * @tc.expected: isPressed_ is true
     */
    gridItemPattern->HandlePressEvent(true);
    EXPECT_TRUE(gridItemPattern->isPressed_);

    /**
     * @tc.steps: step2. Release gridItem
     * @tc.expected: isPressed_ is false
     */
    gridItemPattern->HandlePressEvent(false);
    EXPECT_FALSE(gridItemPattern->isPressed_);
}

/**
 * @tc.name: LayoutOptions001
 * @tc.desc: Test LayoutOptions
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, LayoutOptions001, TestSize.Level1)
{
    /**
     * @tc.cases: Set GridLayoutOptions:irregularIndexes
     * @tc.expected: Each gridItem rect is correct
     */
    GridLayoutOptions option;
    option.irregularIndexes = { 6, 1, 4};
    Create([option](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        model.SetLayoutOptions(option);
        CreateColItem(10);
    });
    EXPECT_TRUE(VerifyBigItemRect(0, RectF(0.f, ITEM_HEIGHT * 0, ITEM_WIDTH, ITEM_HEIGHT)));
    EXPECT_TRUE(VerifyBigItemRect(1, RectF(0.f, ITEM_HEIGHT * 1, GRID_WIDTH, ITEM_HEIGHT)));
    EXPECT_TRUE(VerifyBigItemRect(2, RectF(0.f, ITEM_HEIGHT * 2, ITEM_WIDTH, ITEM_HEIGHT)));
    EXPECT_TRUE(VerifyBigItemRect(3, RectF(ITEM_WIDTH, ITEM_HEIGHT * 2, ITEM_WIDTH, ITEM_HEIGHT)));
    EXPECT_TRUE(VerifyBigItemRect(4, RectF(0.f, ITEM_HEIGHT * 3, GRID_WIDTH, ITEM_HEIGHT)));
    EXPECT_TRUE(VerifyBigItemRect(5, RectF())); // out of view
}

/**
 * @tc.name: LayoutOptions002
 * @tc.desc: Test LayoutOptions
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, LayoutOptions002, TestSize.Level1)
{
    /**
     * @tc.cases: Set GridLayoutOptions:irregularIndexes getSizeByIndex
     * @tc.expected: Each gridItem rect is correct
     */
    GridLayoutOptions option;
    option.irregularIndexes = { 6, 1, 3, 4, 5, 0 };
    GetSizeByIndex onGetIrregularSizeByIndex = [](int32_t index) {
        if (index == 3) {
            return GridItemSize { 1, 2 };
        }
        return GridItemSize { 1, 4 };
    };
    option.getSizeByIndex = std::move(onGetIrregularSizeByIndex);
    Create([option](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        model.SetLayoutOptions(option);
        CreateColItem(10);
    });
    EXPECT_TRUE(VerifyBigItemRect(0, RectF(0.f, ITEM_HEIGHT * 0, GRID_WIDTH, ITEM_HEIGHT)));
    EXPECT_TRUE(VerifyBigItemRect(1, RectF(0.f, ITEM_HEIGHT * 1, GRID_WIDTH, ITEM_HEIGHT)));
    EXPECT_TRUE(VerifyBigItemRect(2, RectF(0.f, ITEM_HEIGHT * 2, ITEM_WIDTH * 1, ITEM_HEIGHT)));
    EXPECT_TRUE(VerifyBigItemRect(3, RectF(ITEM_WIDTH, ITEM_HEIGHT * 2, ITEM_WIDTH * 2, ITEM_HEIGHT)));
    EXPECT_TRUE(VerifyBigItemRect(4, RectF(0.f, ITEM_HEIGHT * 3, GRID_WIDTH, ITEM_HEIGHT)));
    EXPECT_TRUE(VerifyBigItemRect(5, RectF())); // out of view
}

/**
 * @tc.name: GridItemDumpAdvanceInfoTest001
 * @tc.desc: GirdItem dumpadvanceinfo test.
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, GridItemDumpAdvanceInfoTest001, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr");
        model.SetRowsTemplate("1fr 1fr 1fr");
        model.SetColumnsGap(Dimension(COL_GAP));
        model.SetRowsGap(Dimension(ROW_GAP));
        CreateColItem(10);
    });

    /**
     * @tc.steps: step1. Get gridItemPattern and call dumpAdvanceInfo.
     * @tc.expected: Related function is called.
     */
    auto gridItemPattern = GetChildPattern<GridItemPattern>(frameNode_, 0);
    gridItemPattern->DumpAdvanceInfo();
    EXPECT_EQ(gridItemPattern->gridItemStyle_, GridItemStyle::NONE);

    gridItemPattern->gridItemStyle_ = GridItemStyle::PLAIN;
    gridItemPattern->DumpAdvanceInfo();
    EXPECT_EQ(gridItemPattern->gridItemStyle_, GridItemStyle::PLAIN);
}

/**
 * @tc.name: GridItemSetSelectableTest001
 * @tc.desc: GirdItem setselectable test.
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, GridItemSetSelectableTest001, TestSize.Level1)
{
    Create([](GridModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateColItem(20);
    });

    /**
     * @tc.steps: step1. Get gridItemPattern.
     */
    auto gridItemPattern = GetChildPattern<GridItemPattern>(frameNode_, 0);

    /**
     * @tc.steps: step2. When gridItem is unSelectable isSelected_ and selectable_ is true.
     * @tc.expected: gridItemPattern->selectable_ is false.
     */
    gridItemPattern->isSelected_ = true;
    gridItemPattern->selectable_ = true;
    gridItemPattern->SetSelectable(false);
    EXPECT_FALSE(gridItemPattern->selectable_);
}
} // namespace OHOS::Ace::NG
