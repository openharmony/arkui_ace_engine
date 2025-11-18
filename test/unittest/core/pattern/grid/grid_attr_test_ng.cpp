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
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/render/mock_render_context.h"

#include "core/components_ng/pattern/grid/grid_item_pattern.h"
namespace OHOS::Ace::NG {

namespace {
const InspectorFilter filter;
} // namespace
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
    GridModelNG model = CreateGrid();
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
    CreateFixedItems(10);
    CreateDone();

    /**
     * @tc.steps: step1. Test ToJsonValue
     */
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
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
    layoutProperty_->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("layoutDirection"), "GridDirection.RowReverse");

    /**
     * @tc.steps: step3. Test ToJsonValue, change some property
     */
    layoutProperty_->UpdateGridDirection(FlexDirection::COLUMN);
    json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("layoutDirection"), "GridDirection.Column");

    /**
     * @tc.steps: step4. Test ToJsonValue, change some property
     */
    layoutProperty_->UpdateGridDirection(FlexDirection::COLUMN_REVERSE);
    json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
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
    GridModelNG model = CreateGrid();
    model.SetRowsGap(Dimension(-5));
    model.SetColumnsGap(Dimension(-10));
    CreateFixedItems(10);
    CreateDone();
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
    layoutProperty->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("rowStart"), "1");
    EXPECT_EQ(json->GetString("rowEnd"), "2");
    EXPECT_EQ(json->GetString("columnStart"), "1");
    EXPECT_EQ(json->GetString("columnEnd"), "2");
}

/**
 * @tc.name: Property004
 * @tc.desc: Test all the properties of GridItem.
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, Property004, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    CreateFixedItems(4);
    CreateDone();

    /**
     * @tc.steps: step1. set invalid values.
     * @tc.expected: default value
     */
    model.SetColumnsTemplate(AceType::RawPtr(frameNode_), "");
    model.SetRowsTemplate(AceType::RawPtr(frameNode_), "");
    model.SetColumnsGap(AceType::RawPtr(frameNode_), Dimension(-5));
    model.SetRowsGap(AceType::RawPtr(frameNode_), Dimension(-5));
    model.SetFriction(AceType::RawPtr(frameNode_), -1.0);
    EXPECT_EQ(pattern_->GetFriction(), FRICTION);
    EXPECT_EQ(layoutProperty_->GetColumnsTemplateValue(""), "1fr");
    EXPECT_EQ(layoutProperty_->GetRowsTemplateValue(""), "1fr");
    EXPECT_FALSE(layoutProperty_->HasColumnsGap());
    EXPECT_FALSE(layoutProperty_->HasRowsGap());

    /**
     * @tc.steps: step2. set invalid values.
     * @tc.expected: the set value
     */
    model.SetColumnsTemplate(AceType::RawPtr(frameNode_), "1fr 1fr");
    model.SetRowsTemplate(AceType::RawPtr(frameNode_), "1fr 1fr");
    model.SetColumnsGap(AceType::RawPtr(frameNode_), Dimension(10));
    model.SetRowsGap(AceType::RawPtr(frameNode_), Dimension(10));
    model.SetFriction(AceType::RawPtr(frameNode_), 0.1);
    EXPECT_EQ(pattern_->GetFriction(), 0.1);
    EXPECT_EQ(layoutProperty_->GetColumnsTemplateValue(""), "1fr 1fr");
    EXPECT_EQ(layoutProperty_->GetRowsTemplateValue(""), "1fr 1fr");
    EXPECT_EQ(layoutProperty_->GetColumnsGapValue(Dimension(0)), Dimension(10));
    EXPECT_EQ(layoutProperty_->GetColumnsGapValue(Dimension(0)), Dimension(10));
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
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    model.SetColumnsGap(Dimension(COL_GAP));
    model.SetRowsGap(Dimension(ROW_GAP));
    CreateFixedItems(10);
    CreateDone();
    EXPECT_EQ(pattern_->GetAxis(), Axis::VERTICAL);
    EXPECT_EQ(pattern_->GetCrossCount(), 4);

    EXPECT_LT(GetChildX(frameNode_, 0), GetChildX(frameNode_, 1));
    EXPECT_LT(GetChildX(frameNode_, 1), GetChildX(frameNode_, 2));
    EXPECT_LT(GetChildX(frameNode_, 2), GetChildX(frameNode_, 3));
    EXPECT_EQ(GetChildX(frameNode_, 0), GetChildX(frameNode_, 4));

    EXPECT_EQ(GetChildX(frameNode_, 1), GetChildWidth(frameNode_, 0) + COL_GAP);
    EXPECT_EQ(GetChildY(frameNode_, 4), ITEM_MAIN_SIZE + ROW_GAP);
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
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 2fr 3fr 1fr");
    CreateFixedItems(10);
    CreateDone();
    float parts = 1 + 2 + 3 + 1; // 7
    float firstItemWidth = WIDTH / parts;
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
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 0fr 0fr 1fr");
    CreateFixedItems(10);
    CreateDone();
    EXPECT_GT(GetChildWidth(frameNode_, 0), 0);
    EXPECT_EQ(GetChildWidth(frameNode_, 1), 0);
    EXPECT_EQ(GetChildWidth(frameNode_, 2), 0);
    EXPECT_GT(GetChildWidth(frameNode_, 3), 0);
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
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("repeat(auto-fit, 90px)");
    CreateFixedItems(10);
    CreateDone();
    float minItemWidth = 90.f;
    int32_t cols = floor(WIDTH / minItemWidth); // 5
    EXPECT_EQ(pattern_->GetCrossCount(), cols);
    float expectItemWidth = WIDTH / cols; // 96.f
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
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("repeat(auto-fill, 90px)");
    CreateFixedItems(10);
    CreateDone();
    float itemWidth = 90.f;
    int32_t cols = floor(WIDTH / itemWidth); // 5
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
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("");
    CreateFixedItems(10);
    CreateDone();
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
    GridModelNG model = CreateGrid();
    model.SetRowsTemplate("1fr 1fr 1fr 1fr");
    model.SetColumnsGap(Dimension(COL_GAP));
    model.SetRowsGap(Dimension(ROW_GAP));
    CreateFixedItems(10);
    CreateDone();
    EXPECT_EQ(pattern_->GetAxis(), Axis::HORIZONTAL);
    EXPECT_EQ(pattern_->GetCrossCount(), 4);

    EXPECT_LT(GetChildY(frameNode_, 0), GetChildY(frameNode_, 1));
    EXPECT_LT(GetChildY(frameNode_, 1), GetChildY(frameNode_, 2));
    EXPECT_LT(GetChildY(frameNode_, 2), GetChildY(frameNode_, 3));
    EXPECT_EQ(GetChildY(frameNode_, 0), GetChildY(frameNode_, 4));

    EXPECT_EQ(GetChildY(frameNode_, 1), GetChildHeight(frameNode_, 0) + ROW_GAP);
    EXPECT_EQ(GetChildX(frameNode_, 4), ITEM_MAIN_SIZE + COL_GAP);
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
    GridModelNG model = CreateGrid();
    model.SetRowsTemplate("1fr 2fr 3fr 1fr");
    CreateFixedItems(10);
    CreateDone();
    float parts = 1 + 2 + 3 + 1; // 7
    float firstItemHeight = HEIGHT / parts;
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
    GridModelNG model = CreateGrid();
    model.SetRowsTemplate("1fr 0fr 0fr 1fr");
    CreateFixedItems(10);
    CreateDone();
    EXPECT_GT(GetChildHeight(frameNode_, 0), 0);
    EXPECT_EQ(GetChildHeight(frameNode_, 1), 0);
    EXPECT_EQ(GetChildHeight(frameNode_, 2), 0);
    EXPECT_GT(GetChildHeight(frameNode_, 3), 0);
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
    GridModelNG model = CreateGrid();
    model.SetRowsTemplate("repeat(auto-fit, 90px)");
    CreateFixedItems(10);
    CreateDone();
    float minItemHeight = 90.f;
    int32_t rows = floor(HEIGHT / minItemHeight); // 8
    EXPECT_EQ(pattern_->GetCrossCount(), rows);
    float expectItemHeight = HEIGHT / rows; // 100.f
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
    GridModelNG model = CreateGrid();
    model.SetRowsTemplate("repeat(auto-fill, 90px)");
    CreateFixedItems(10);
    CreateDone();
    float itemHeight = 90.f;
    int32_t rows = floor(HEIGHT / itemHeight); // 5
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
    GridModelNG model = CreateGrid();
    model.SetRowsTemplate("");
    CreateFixedItems(10);
    CreateDone();
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
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    model.SetRowsTemplate("1fr 1fr 1fr 1fr");
    CreateGridItems(20);
    CreateDone();
    EXPECT_EQ(pattern_->GetCrossCount(), 4);
    EXPECT_TRUE(IsEqual(GetChildSize(frameNode_, 0), SizeF(60.0f, ITEM_MAIN_SIZE)));
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
     * @tc.cases: Set LayoutDirection ROW, set minCount maxCount, set Gap
     * @tc.expected: Axis is VERTICAL, has three cols, has gap
     */
    GridModelNG model = CreateGrid();
    model.SetLayoutDirection(FlexDirection::ROW);
    model.SetCellLength(ITEM_MAIN_SIZE);
    model.SetMinCount(2);
    model.SetMaxCount(4);
    model.SetColumnsGap(Dimension(COL_GAP));
    model.SetRowsGap(Dimension(ROW_GAP));
    CreateFixedItems(10);
    CreateDone();
    EXPECT_EQ(pattern_->GetAxis(), Axis::VERTICAL);
    EXPECT_EQ(pattern_->GetCrossCount(), 2);

    EXPECT_EQ(GetChildX(frameNode_, 1), ITEM_MAIN_SIZE + COL_GAP);
    EXPECT_EQ(GetChildY(frameNode_, 3), ITEM_MAIN_SIZE + ROW_GAP);
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
    float itemWidth = WIDTH / minCount + 100.f; // greater than half of WIDTH
    GridModelNG model = CreateGrid();
    model.SetLayoutDirection(FlexDirection::ROW_REVERSE);
    model.SetCellLength(ITEM_MAIN_SIZE);
    model.SetMinCount(minCount);
    model.SetMaxCount(4);
    CreateGridItems(10, itemWidth, ITEM_MAIN_SIZE);
    CreateDone();
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
    float itemHeight = HEIGHT / maxCount - 50.0f; // less than quarter of HEIGHT
    GridModelNG model = CreateGrid();
    model.SetLayoutDirection(FlexDirection::COLUMN);
    model.SetCellLength(ITEM_MAIN_SIZE);
    model.SetMinCount(2);
    model.SetMaxCount(maxCount);
    CreateGridItems(10, ITEM_MAIN_SIZE, itemHeight);
    CreateDone();
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
    GridModelNG model = CreateGrid();
    model.SetLayoutDirection(FlexDirection::COLUMN_REVERSE);
    model.SetCellLength(ITEM_MAIN_SIZE);
    model.SetMinCount(2);
    model.SetMaxCount(4);
    CreateFixedItems(10);
    CreateDone();
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
    GridModelNG model = CreateGrid();
    model.SetRowsTemplate("1fr 1fr 1fr 1fr");
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateBigItem(1, 2, 1, 2);
    CreateBigItem(NULL_VALUE, NULL_VALUE, 1, 3);
    CreateBigItem(1, 3, NULL_VALUE, NULL_VALUE);
    CreateGridItems(7);
    CreateDone();
    float itemWidth = 60.0f;
    EXPECT_TRUE(VerifyBigItemRect(0, RectF(itemWidth, ITEM_MAIN_SIZE, itemWidth * 2, ITEM_MAIN_SIZE * 2)));
    EXPECT_TRUE(VerifyBigItemRect(1, RectF(0, 0, itemWidth * 3, ITEM_MAIN_SIZE)));
    EXPECT_TRUE(VerifyBigItemRect(2, RectF(itemWidth * 3, 0, itemWidth, ITEM_MAIN_SIZE * 3)));

    EXPECT_TRUE(VerifyBigItemRect(3, RectF(0, ITEM_MAIN_SIZE, itemWidth, ITEM_MAIN_SIZE)));
    EXPECT_TRUE(VerifyBigItemRect(4, RectF(0, ITEM_MAIN_SIZE * 2, itemWidth, ITEM_MAIN_SIZE)));
    EXPECT_TRUE(VerifyBigItemRect(5, RectF(0, ITEM_MAIN_SIZE * 3, itemWidth, ITEM_MAIN_SIZE)));
    EXPECT_TRUE(VerifyBigItemRect(6, RectF(itemWidth, ITEM_MAIN_SIZE * 3, itemWidth, ITEM_MAIN_SIZE)));
    EXPECT_TRUE(VerifyBigItemRect(7, RectF(itemWidth * 2, ITEM_MAIN_SIZE * 3, itemWidth, ITEM_MAIN_SIZE)));
    EXPECT_TRUE(VerifyBigItemRect(8, RectF(itemWidth * 3, ITEM_MAIN_SIZE * 3, itemWidth, ITEM_MAIN_SIZE)));
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
    float itemWidth = 60.0f;
    GridModelNG model = CreateGrid();
    model.SetRowsTemplate("1fr 1fr 1fr 1fr");
    CreateBigRowItem(1, 2);
    CreateBigRowItem(0, 2);
    CreateBigRowItem(2, 3);
    CreateFixedWidthItems(7, itemWidth);
    CreateDone();
    EXPECT_TRUE(VerifyBigItemRect(0, RectF(0, ITEM_MAIN_SIZE, itemWidth, ITEM_MAIN_SIZE * 2)));
    EXPECT_TRUE(VerifyBigItemRect(1, RectF(itemWidth, 0, itemWidth, ITEM_MAIN_SIZE * 3)));
    EXPECT_TRUE(VerifyBigItemRect(2, RectF(itemWidth * 2, ITEM_MAIN_SIZE * 2, itemWidth, ITEM_MAIN_SIZE * 2)));

    EXPECT_TRUE(VerifyBigItemRect(3, RectF(itemWidth * 3, 0, itemWidth, ITEM_MAIN_SIZE)));
    EXPECT_TRUE(VerifyBigItemRect(4, RectF(itemWidth * 3, ITEM_MAIN_SIZE, itemWidth, ITEM_MAIN_SIZE)));
    EXPECT_TRUE(VerifyBigItemRect(5, RectF(itemWidth * 3, ITEM_MAIN_SIZE * 2, itemWidth, ITEM_MAIN_SIZE)));
    EXPECT_TRUE(VerifyBigItemRect(6, RectF(itemWidth * 3, ITEM_MAIN_SIZE * 3, itemWidth, ITEM_MAIN_SIZE)));
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
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateBigColItem(2, 3);
    CreateBigColItem(0, 2);
    CreateBigColItem(2, 1);
    CreateFixedItems(7);
    CreateDone();
    float itemWidth = 60.0f;
    EXPECT_TRUE(VerifyBigItemRect(0, RectF(itemWidth * 2, 0, itemWidth * 2, ITEM_MAIN_SIZE)));
    EXPECT_TRUE(VerifyBigItemRect(1, RectF(0, ITEM_MAIN_SIZE, itemWidth * 3, ITEM_MAIN_SIZE)));
    EXPECT_TRUE(VerifyBigItemRect(2, RectF(itemWidth * 2, ITEM_MAIN_SIZE * 2, itemWidth, ITEM_MAIN_SIZE)));

    EXPECT_TRUE(VerifyBigItemRect(3, RectF(itemWidth * 3, ITEM_MAIN_SIZE * 2, itemWidth, ITEM_MAIN_SIZE)));
    EXPECT_TRUE(VerifyBigItemRect(4, RectF(0, ITEM_MAIN_SIZE * 3, itemWidth, ITEM_MAIN_SIZE)));
    EXPECT_TRUE(VerifyBigItemRect(5, RectF(itemWidth, ITEM_MAIN_SIZE * 3, itemWidth, ITEM_MAIN_SIZE)));
    EXPECT_TRUE(VerifyBigItemRect(6, RectF(itemWidth * 2, ITEM_MAIN_SIZE * 3, itemWidth, ITEM_MAIN_SIZE)));
    EXPECT_TRUE(VerifyBigItemRect(7, RectF(itemWidth * 3, ITEM_MAIN_SIZE * 3, itemWidth, ITEM_MAIN_SIZE)));
    EXPECT_TRUE(VerifyBigItemRect(8, RectF()));
    EXPECT_TRUE(VerifyBigItemRect(9, RectF()));
}

/**
 * @tc.name: BigItem004
 * @tc.desc: Test property colStart/colEnd with colTemplate
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, BigItem004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Only set ColumnsTemplate, create big items
     * @tc.expected: Big item have bigger size
     */
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateBigColItem(2, 3);
    CreateFixedItems(7);
    CreateDone();
    float itemWidth = 60.0f;
    EXPECT_TRUE(VerifyBigItemRect(0, RectF(itemWidth * 2, 0, itemWidth * 2, ITEM_MAIN_SIZE))); // big item
    EXPECT_TRUE(VerifyBigItemRect(1, RectF(0, ITEM_MAIN_SIZE, itemWidth, ITEM_MAIN_SIZE)));    // normal item

    /**
     * @tc.steps: step2. Change colStart and colEnd
     * @tc.expected: Big item size is changed
     */
    auto itemLayoutProperty = GetChildLayoutProperty<GridItemLayoutProperty>(frameNode_, 0);
    itemLayoutProperty->UpdateColumnStart(0);
    itemLayoutProperty->UpdateColumnEnd(1);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE); // update items
    FlushUITasks();
    EXPECT_TRUE(VerifyBigItemRect(0, RectF(0, 0, itemWidth * 2, ITEM_MAIN_SIZE)));         // big item
    EXPECT_TRUE(VerifyBigItemRect(1, RectF(itemWidth * 2, 0, itemWidth, ITEM_MAIN_SIZE))); // normal item
}

/**
 * @tc.name: EnableScrollInteraction001
 * @tc.desc: Test property about enableScrollInteraction.
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, EnableScrollInteraction001, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetScrollEnabled(true);
    CreateFixedItems(10);
    CreateDone();
    EXPECT_TRUE(layoutProperty_->GetScrollEnabledValue());
}

/**
 * @tc.name: EnableScrollInteraction002
 * @tc.desc: Test property about enableScrollInteraction.
 * @tc.type: FUNC
 */
HWTEST_F(GridAttrTestNg, EnableScrollInteraction002, TestSize.Level1)
{
    GridModelNG model = CreateGrid();
    model.SetScrollEnabled(false);
    CreateFixedItems(10);
    CreateDone();
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
    GridModelNG model = CreateGrid();
    model.SetRowsTemplate("1fr 1fr 1fr 1fr");
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateGridItems(16, NULL_VALUE, NULL_VALUE);
    CreateDone();
    EXPECT_EQ(GetChildX(frameNode_, 1) - GetChildWidth(frameNode_, 1), 0);
    EXPECT_EQ(GetChildY(frameNode_, 4) - GetChildHeight(frameNode_, 1), 0);
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
    GridModelNG model = CreateGrid();
    model.SetRowsTemplate("1fr 1fr 1fr 1fr");
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    model.SetColumnsGap(Dimension(COL_GAP));
    model.SetRowsGap(Dimension(ROW_GAP));
    CreateGridItems(16, NULL_VALUE, NULL_VALUE);
    CreateDone();
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
    GridModelNG model = CreateGrid();
    model.SetRowsTemplate("1fr 1fr 1fr 1fr");
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    model.SetColumnsGap(Dimension(-1));
    model.SetRowsGap(Dimension(-1));
    CreateGridItems(16, NULL_VALUE, NULL_VALUE);
    CreateDone();
    EXPECT_EQ(GetChildX(frameNode_, 1) - GetChildWidth(frameNode_, 1), 0);
    EXPECT_EQ(GetChildY(frameNode_, 4) - GetChildHeight(frameNode_, 1), 0);
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
    GridModelNG model = CreateGrid();
    model.SetRowsTemplate("1fr 1fr 1fr 1fr");
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    model.SetColumnsGap(Dimension(WIDTH / 3));
    model.SetRowsGap(Dimension(HEIGHT / 3 + 1));
    CreateGridItems(16, NULL_VALUE, NULL_VALUE);
    CreateDone();
    EXPECT_EQ(GetChildX(frameNode_, 1) - GetChildWidth(frameNode_, 1), 0);
    EXPECT_EQ(GetChildY(frameNode_, 4) - GetChildHeight(frameNode_, 1), 0);
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
    GridModelNG model = CreateGrid();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    model.SetColumnsGap(Dimension(WIDTH / 3));
    model.SetRowsGap(Dimension(HEIGHT / 3));
    CreateFixedItems(16);
    CreateDone();
    EXPECT_TRUE(layoutProperty_->IsConfiguredScrollable());
    EXPECT_EQ(GetChildX(frameNode_, 1) - GetChildWidth(frameNode_, 1), 0);
    EXPECT_EQ(GetChildY(frameNode_, 4) - GetChildHeight(frameNode_, 1), HEIGHT / 3);
}
} // namespace OHOS::Ace::NG
