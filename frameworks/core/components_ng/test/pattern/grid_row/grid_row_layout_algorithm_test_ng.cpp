/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include <optional>
#include <string>
#include <vector>

#include "gtest/gtest.h"

#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/grid_col/grid_col_layout_pattern.h"
#include "core/components_ng/pattern/grid_col/grid_col_model_ng.h"
#include "core/components_ng/pattern/grid_row/grid_row_layout_pattern.h"
#include "core/components_ng/pattern/grid_row/grid_row_model_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

namespace {
constexpr float DEFAULT_SPAN_WIDTH = 100.0f;
constexpr uint8_t DEFAULT_COLUMNS = 8;
constexpr float DEFAULT_GRID_ROW_WIDTH = (DEFAULT_SPAN_WIDTH * DEFAULT_COLUMNS);
constexpr uint8_t DEFAULT_OFFSET = 7;
constexpr uint8_t DEFAULT_HEIGHT = 10;
} // namespace

class GridRowColPatternTestNg : public testing::Test {
public:
    void SetUp() override;
    void TearDown() override;
    static void SetUpTestSuite();
    static void TearDownTestSuite();

    static RefPtr<LayoutWrapper> CreateLayoutWrapperAndLayout(bool needLayout);
    static void TestGridColWidth(uint8_t span, uint8_t expectWidth);
    static void TestGridColGeometry(uint8_t span, uint8_t offset, uint8_t expectLines, uint8_t expectOffset);

    static RefPtr<FrameNode> rowNode_;
    static std::vector<RefPtr<FrameNode>> colNodes_;
    static const int32_t colNum_ = 2;
};

void GridRowColPatternTestNg::SetUpTestSuite()
{
    /* Create framenode */
    GridRowModelNG gridRowModelNG;
    gridRowModelNG.Create();
    GridColModelNG gridColModelNG;
    for (int32_t i = 0; i < colNum_; i++) {
        gridColModelNG.Create();
        auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
        ViewStackProcessor::GetInstance()->Pop();
        colNodes_.emplace_back(frameNode);
    }
    rowNode_ = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ViewStackProcessor::GetInstance()->PopContainer();
}

void GridRowColPatternTestNg::TearDownTestSuite()
{
    rowNode_->Clean();
    colNodes_.clear();
}

void GridRowColPatternTestNg::SetUp()
{
    /* Set default grid-row properties */
    auto rowLayout = rowNode_->GetLayoutProperty<GridRowLayoutProperty>();
    rowLayout->UpdateColumns(V2::GridContainerSize(DEFAULT_COLUMNS));
    rowLayout->UpdateGutter(V2::Gutter());
    rowLayout->UpdateDirection(V2::GridRowDirection::Row);
    rowLayout->UpdateSizeType(V2::GridSizeType::UNDEFINED);
    rowLayout->UpdateBreakPoints(V2::BreakPoints());

    /* Set default grid-col properties */
    auto colLayoutFront = colNodes_.front()->GetLayoutProperty<GridColLayoutProperty>();
    colLayoutFront->UpdateSpan(V2::GridContainerSize(1));
    colLayoutFront->UpdateOffset(V2::GridContainerSize(DEFAULT_OFFSET));
    colLayoutFront->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(DEFAULT_HEIGHT)));

    auto colLayoutBack = colNodes_.back()->GetLayoutProperty<GridColLayoutProperty>();
    colLayoutBack->UpdateSpan(V2::GridContainerSize(1));
    colLayoutBack->UpdateOffset(V2::GridContainerSize(0));
    colLayoutBack->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(DEFAULT_HEIGHT)));
}

void GridRowColPatternTestNg::TearDown() {}

RefPtr<FrameNode> GridRowColPatternTestNg::rowNode_;
std::vector<RefPtr<FrameNode>> GridRowColPatternTestNg::colNodes_;
const int32_t GridRowColPatternTestNg::colNum_;

RefPtr<LayoutWrapper> GridRowColPatternTestNg::CreateLayoutWrapperAndLayout(bool needLayout = false)
{
    auto layoutWrapper = rowNode_->CreateLayoutWrapper();
    LayoutConstraintF constraint;
    OptionalSizeF size;
    size.SetWidth(DEFAULT_GRID_ROW_WIDTH);
    constraint.UpdateIllegalSelfIdealSizeWithCheck(size);
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    layoutProperty->BuildGridProperty(rowNode_);
    layoutProperty->UpdateLayoutConstraint(constraint);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    geometryNode->SetParentLayoutConstraint(constraint);
    layoutProperty->UpdateContentConstraint();
    auto algorithm = layoutWrapper->GetLayoutAlgorithm();
    algorithm->Measure(AceType::RawPtr(layoutWrapper));
    if (needLayout) {
        algorithm->Layout(AceType::RawPtr(layoutWrapper));
    }
    return layoutWrapper;
}

/* Examine grid-col width */
void GridRowColPatternTestNg::TestGridColWidth(uint8_t span, uint8_t expectWidth)
{
    // first grid-col occupies the first line to constrain the line-height of that line
    auto colNode = colNodes_.front();
    auto layoutProperty = colNode->GetLayoutProperty<GridColLayoutProperty>();
    layoutProperty->UpdateSpan(V2::GridContainerSize(span));
    layoutProperty->UpdateOffset(V2::GridContainerSize(0));

    // Check geometry Size
    auto layoutWrapper = CreateLayoutWrapperAndLayout();
    auto spanWidth = layoutWrapper->GetOrCreateChildByIndex(0)->GetGeometryNode()->GetFrameSize().Width();
    EXPECT_EQ(spanWidth, expectWidth * DEFAULT_SPAN_WIDTH);
}

/* Examine the last grid-col position according to span/offset */
void GridRowColPatternTestNg::TestGridColGeometry(
    uint8_t span, uint8_t offset, uint8_t expectLines, uint8_t expectOffset)
{
    // first grid-col occupies the first line to constrain the line-height of that line
    auto colNode = colNodes_.back();
    auto layoutProperty = colNode->GetLayoutProperty<GridColLayoutProperty>();
    layoutProperty->UpdateSpan(V2::GridContainerSize(span));
    layoutProperty->UpdateOffset(V2::GridContainerSize(offset));

    auto layoutWrapper = CreateLayoutWrapperAndLayout(true);

    // Check geometry Size
    auto firstGridColFrameRect = layoutWrapper->GetOrCreateChildByIndex(0)->GetGeometryNode()->GetFrameRect();
    auto frameRect = layoutWrapper->GetOrCreateChildByIndex(1)->GetGeometryNode()->GetFrameRect();
    float columnWidth = firstGridColFrameRect.Width();
    float lineHeight = firstGridColFrameRect.Height();

    EXPECT_EQ(columnWidth, DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(frameRect.GetX(),
        firstGridColFrameRect.GetX() + columnWidth * (expectOffset - DEFAULT_OFFSET)); // examine offset
    EXPECT_EQ(frameRect.GetY() - firstGridColFrameRect.GetY(),
        lineHeight * expectLines); // examine lines
}

/**
 * @tc.name: Algorithm001
 * @tc.desc: Test GridRow Measure().
 * @tc.type: FUNC
 */
HWTEST_F(GridRowColPatternTestNg, Algorithm001, TestSize.Level1)
{
    TestGridColWidth(0, 0);
    TestGridColWidth(1, 1);
    TestGridColWidth(DEFAULT_COLUMNS + 1, DEFAULT_COLUMNS); // span > columns
}

/**
 * @tc.name: Algorithm002
 * @tc.desc: Test GridRow layout algorithm with different span/offset.
 * @tc.type: FUNC
 */
HWTEST_F(GridRowColPatternTestNg, Algorithm002, TestSize.Level1)
{
    // span + offset <= columns
    constexpr uint8_t span = 6;
    TestGridColGeometry(span, DEFAULT_COLUMNS - span, 1, DEFAULT_COLUMNS - span);

    // offset <= columns, span + offset > columns
    TestGridColGeometry(DEFAULT_COLUMNS - 1, 2, 2, 0);

    // offset > columns, span <= columns
    TestGridColGeometry(2, DEFAULT_COLUMNS + 1, 2, 1);

    // span > columns
    TestGridColGeometry(DEFAULT_COLUMNS + 1, 1, 2, 0);
}

/**
 * @tc.name: Algorithm003
 * @tc.desc: Test GridRow layout algorithm with different sizetype.
 * @tc.type: FUNC
 */
HWTEST_F(GridRowColPatternTestNg, Algorithm003, TestSize.Level1)
{
    /* update grid-row columns of LG size */
    auto layoutProperty = rowNode_->GetLayoutProperty<GridRowLayoutProperty>();
    constexpr int32_t testColumns = 7;
    V2::GridContainerSize columns(DEFAULT_COLUMNS);
    columns.lg = testColumns;
    layoutProperty->UpdateColumns(columns);
    layoutProperty->UpdateSizeType(V2::GridSizeType::LG);
    auto layoutWrapper = CreateLayoutWrapperAndLayout(true);
    auto frameRect = layoutWrapper->GetOrCreateChildByIndex(0)->GetGeometryNode()->GetFrameRect();
    float columnWidth = frameRect.Width();

    // the first grid-col's offset occupies a whole line
    EXPECT_EQ(columnWidth, DEFAULT_GRID_ROW_WIDTH / testColumns);
    EXPECT_EQ(frameRect.GetX(), 0);
}

/**
 * @tc.name: Algorithm004
 * @tc.desc: Test GridRow layout algorithm with different gutter.
 * @tc.type: FUNC
 */
HWTEST_F(GridRowColPatternTestNg, Algorithm004, TestSize.Level1)
{
    auto layoutProperty = rowNode_->GetLayoutProperty<GridRowLayoutProperty>();
    constexpr float gutterVal = 20.0f;
    layoutProperty->UpdateGutter(V2::Gutter(Dimension(gutterVal)));
    auto layoutWrapper = CreateLayoutWrapperAndLayout(true);
    auto frameRect = layoutWrapper->GetOrCreateChildByIndex(0)->GetGeometryNode()->GetFrameRect();
    float columnWidth = frameRect.Width();

    // the first grid-col's offset occupies a whole line
    float expectcolumnWidth = (DEFAULT_GRID_ROW_WIDTH + gutterVal) / DEFAULT_COLUMNS - gutterVal;
    EXPECT_EQ(columnWidth, expectcolumnWidth);
    EXPECT_EQ(frameRect.GetX(), DEFAULT_GRID_ROW_WIDTH - expectcolumnWidth);
}

/**
 * @tc.name: Algorithm005
 * @tc.desc: Test GridRow layout algorithm with different direction.
 * @tc.type: FUNC
 */
HWTEST_F(GridRowColPatternTestNg, Algorithm005, TestSize.Level1)
{
    auto layoutProperty = rowNode_->GetLayoutProperty<GridRowLayoutProperty>();
    layoutProperty->UpdateDirection(V2::GridRowDirection::RowReverse);
    auto layoutWrapper = CreateLayoutWrapperAndLayout(true);
    auto frameRect = layoutWrapper->GetOrCreateChildByIndex(0)->GetGeometryNode()->GetFrameRect();
    float columnWidth = frameRect.Width();

    EXPECT_EQ(columnWidth, DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(frameRect.GetX(), 0);
}

/**
 * @tc.name: Algorithm006
 * @tc.desc: Test GridCol layout order.
 * @tc.type: FUNC
 */
HWTEST_F(GridRowColPatternTestNg, Algorithm006, TestSize.Level1)
{
    auto colLayoutFront = colNodes_.front()->GetLayoutProperty<GridColLayoutProperty>();
    colLayoutFront->UpdateOrder(V2::GridContainerSize(6));
    auto colLayoutBack = colNodes_.back()->GetLayoutProperty<GridColLayoutProperty>();
    colLayoutBack->UpdateOrder(V2::GridContainerSize(-1));
    auto layoutWrapper = CreateLayoutWrapperAndLayout(true);
    auto frameRect = layoutWrapper->GetOrCreateChildByIndex(0)->GetGeometryNode()->GetFrameRect();

    EXPECT_EQ(frameRect.GetX(), 0);
    EXPECT_EQ(frameRect.GetY(), DEFAULT_HEIGHT);
}

/**
 * @tc.name: Breakpoint
 * @tc.desc: Test GridRow layout algorithm with different breakpoint and
 *           trigerring event when breakpoint changes.
 * @tc.type: FUNC
 */
HWTEST_F(GridRowColPatternTestNg, Breakpoint, TestSize.Level1)
{
    auto layoutProperty = rowNode_->GetLayoutProperty<GridRowLayoutProperty>();
    constexpr int32_t mdCols = 6;
    constexpr int32_t lgCols = 4;
    V2::GridContainerSize columns(DEFAULT_COLUMNS);
    columns.md = mdCols;
    columns.lg = lgCols;
    layoutProperty->UpdateColumns(columns);

    V2::BreakPoints breakpoints;
    breakpoints.reference = V2::BreakPointsReference::ComponentSize;
    breakpoints.breakpoints.assign({ "400px", "700px", "1000px" }); // xs sm md lg
    layoutProperty->UpdateBreakPoints(breakpoints);

    auto layoutWrapper = CreateLayoutWrapperAndLayout(true);
    auto frameRect = layoutWrapper->GetOrCreateChildByIndex(0)->GetGeometryNode()->GetFrameRect();
    float columnWidth = frameRect.Width();
    EXPECT_EQ(columnWidth, DEFAULT_GRID_ROW_WIDTH / mdCols); // expect md

    auto eventHub = rowNode_->GetEventHub<GridRowEventHub>();
    bool eventTriggerFlag = false;
    eventHub->SetOnBreakpointChange([&eventTriggerFlag, expectSize = std::string("lg")](const std::string& size) {
        eventTriggerFlag = true;
        EXPECT_EQ(size, expectSize);
    });

    breakpoints.breakpoints.assign({ "100px", "400px", "700px" }); // xs sm md lg
    layoutProperty->UpdateBreakPoints(breakpoints);

    layoutWrapper = CreateLayoutWrapperAndLayout(true);
    frameRect = layoutWrapper->GetOrCreateChildByIndex(0)->GetGeometryNode()->GetFrameRect();
    columnWidth = frameRect.Width();
    EXPECT_EQ(columnWidth, DEFAULT_GRID_ROW_WIDTH / lgCols); // expect lg
    EXPECT_TRUE(eventTriggerFlag);
}
} // namespace OHOS::Ace::NG
