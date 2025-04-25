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

#include "gtest/gtest.h"

#define private public
#define protected public

#include "test/mock/core/pipeline/mock_pipeline_context.h"

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
const InspectorFilter filter;
constexpr float DEFAULT_SPAN_WIDTH = 100.0f;
constexpr uint8_t DEFAULT_COLUMNS = 8;
constexpr float DEFAULT_GRID_ROW_WIDTH = (DEFAULT_SPAN_WIDTH * DEFAULT_COLUMNS);
constexpr uint8_t DEFAULT_OFFSET = 7;
constexpr uint8_t DEFAULT_HEIGHT = 10;
constexpr uint8_t TEST_ALIGN_HEIGHT = 30;
} // namespace

class GridRowTestNg : public testing::Test {
public:
    void SetUp() override;
    void TearDown() override;
    static void SetUpTestSuite();
    static void TearDownTestSuite();

    static RefPtr<LayoutWrapperNode> CreateLayoutWrapperAndLayout(bool needLayout);
    static void TestGridColWidth(uint8_t span, uint8_t expectWidth);
    static testing::AssertionResult TestGridColGeometry(
        uint8_t offset, uint8_t span, uint8_t expectOffsetX, uint8_t expectLines);
    static OffsetF GetColOffset(RefPtr<LayoutWrapperNode>& layoutWrapper, int32_t index);

    static RefPtr<FrameNode> rowNode_;
    static std::vector<RefPtr<FrameNode>> colNodes_;
    static const int32_t colNum_ = 2;
};

void GridRowTestNg::SetUpTestSuite()
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
    MockPipelineContext::SetUp();
}

void GridRowTestNg::TearDownTestSuite()
{
    rowNode_->Clean();
    colNodes_.clear();
    MockPipelineContext::TearDown();
}

void GridRowTestNg::SetUp()
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

    MockPipelineContext::GetCurrent()->SetWindowModal(WindowModal::CONTAINER_MODAL);
    MockPipelineContext::GetCurrent()->windowManager_ = AceType::MakeRefPtr<WindowManager>();
    MockPipelineContext::GetCurrent()->windowManager_->SetWindowGetModeCallBack(
        []() -> WindowMode { return WindowMode::WINDOW_MODE_FLOATING; });
}

void GridRowTestNg::TearDown() {}

RefPtr<FrameNode> GridRowTestNg::rowNode_;
std::vector<RefPtr<FrameNode>> GridRowTestNg::colNodes_;
const int32_t GridRowTestNg::colNum_;

RefPtr<LayoutWrapperNode> GridRowTestNg::CreateLayoutWrapperAndLayout(bool needLayout = false)
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
void GridRowTestNg::TestGridColWidth(uint8_t span, uint8_t expectWidth)
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
testing::AssertionResult GridRowTestNg::TestGridColGeometry(
    uint8_t offset, uint8_t span, uint8_t expectOffsetX, uint8_t expectLines)
{
    auto firstColNode = colNodes_.front();
    auto firstColLayoutProperty = firstColNode->GetLayoutProperty<GridColLayoutProperty>();
    firstColLayoutProperty->UpdateSpan(V2::GridContainerSize(span));
    firstColLayoutProperty->UpdateOffset(V2::GridContainerSize(offset));

    auto layoutWrapper = CreateLayoutWrapperAndLayout(true);
    auto secondColOffset = GetColOffset(layoutWrapper, 1);
    const OffsetF expectOffset = OffsetF(DEFAULT_SPAN_WIDTH * expectOffsetX, DEFAULT_HEIGHT * expectLines);
    if (secondColOffset == expectOffset) {
        return testing::AssertionSuccess();
    }
    return testing::AssertionFailure() << "secondColOffset: " << secondColOffset.ToString()
                                       << " But expect offset: " << expectOffset.ToString();
}

OffsetF GridRowTestNg::GetColOffset(RefPtr<LayoutWrapperNode>& layoutWrapper, int32_t index)
{
    return layoutWrapper->GetOrCreateChildByIndex(index)->GetGeometryNode()->GetFrameOffset();
}

/**
 * @tc.name: Algorithm001
 * @tc.desc: Test GridRow Measure().
 * @tc.type: FUNC
 */
HWTEST_F(GridRowTestNg, Algorithm001, TestSize.Level1)
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
HWTEST_F(GridRowTestNg, Algorithm002, TestSize.Level1)
{
    // Set the first col: span + offset == columns
    // Test second col position
    EXPECT_TRUE(TestGridColGeometry(2, 6, 0, 1));

    // span + offset > columns, offset <= columns
    EXPECT_TRUE(TestGridColGeometry(2, 7, 7, 0));

    // span < columns, offset > columns
    EXPECT_TRUE(TestGridColGeometry(9, 2, 3, 0));

    // span > columns
    EXPECT_TRUE(TestGridColGeometry(1, 9, 0, 1));
}

/**
 * @tc.name: Algorithm003
 * @tc.desc: Test GridRow layout algorithm with different sizetype.
 * @tc.type: FUNC
 */
HWTEST_F(GridRowTestNg, Algorithm003, TestSize.Level1)
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
    EXPECT_EQ(columnWidth, DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(frameRect.GetX(), testColumns * DEFAULT_SPAN_WIDTH);
}

/**
 * @tc.name: Algorithm004
 * @tc.desc: Test GridRow layout algorithm with different gutter.
 * @tc.type: FUNC
 */
HWTEST_F(GridRowTestNg, Algorithm004, TestSize.Level1)
{
    auto layoutProperty = rowNode_->GetLayoutProperty<GridRowLayoutProperty>();
    constexpr float gutterVal = 20.0f;
    layoutProperty->UpdateGutter(V2::Gutter(Dimension(gutterVal)));
    auto layoutWrapper = CreateLayoutWrapperAndLayout(true);
    auto frameRect = layoutWrapper->GetOrCreateChildByIndex(0)->GetGeometryNode()->GetFrameRect();
    float columnWidth = frameRect.Width();

    // the first grid-col's offset occupies a whole line
    const float expectColWidth = (DEFAULT_GRID_ROW_WIDTH - (DEFAULT_COLUMNS - 1) * gutterVal) / DEFAULT_COLUMNS;
    EXPECT_EQ(columnWidth, expectColWidth);
    EXPECT_EQ(frameRect.GetX(), DEFAULT_GRID_ROW_WIDTH - expectColWidth);
}

/**
 * @tc.name: Algorithm005
 * @tc.desc: Test GridRow layout algorithm with different direction.
 * @tc.type: FUNC
 */
HWTEST_F(GridRowTestNg, Algorithm005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. V2::GridRowDirection::Row
     * @tc.expected: GridCol is sorted from left to right
     */
    auto layoutProperty = rowNode_->GetLayoutProperty<GridRowLayoutProperty>();
    auto direction = layoutProperty->GetDirection();
    EXPECT_EQ(direction, V2::GridRowDirection::Row);
    auto layoutWrapper = CreateLayoutWrapperAndLayout(true);
    auto frameRect = layoutWrapper->GetOrCreateChildByIndex(0)->GetGeometryNode()->GetFrameRect();
    auto columnWidth = frameRect.Width();

    EXPECT_EQ(columnWidth, DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(frameRect.GetX(), DEFAULT_GRID_ROW_WIDTH - DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(frameRect.GetY(), 0);
    frameRect = layoutWrapper->GetOrCreateChildByIndex(1)->GetGeometryNode()->GetFrameRect();
    EXPECT_EQ(frameRect.GetX(), 0);
    EXPECT_EQ(frameRect.GetY(), DEFAULT_HEIGHT);

    /**
     * @tc.steps: step2. V2::GridRowDirection::RowReverse
     * @tc.expected: GridCol is sorted from right to left
     */
    layoutProperty->UpdateDirection(V2::GridRowDirection::RowReverse);
    layoutWrapper = CreateLayoutWrapperAndLayout(true);
    frameRect = layoutWrapper->GetOrCreateChildByIndex(0)->GetGeometryNode()->GetFrameRect();
    columnWidth = frameRect.Width();
    EXPECT_EQ(columnWidth, DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(frameRect.GetX(), DEFAULT_GRID_ROW_WIDTH - (DEFAULT_OFFSET + 1) * DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(frameRect.GetY(), 0);
    frameRect = layoutWrapper->GetOrCreateChildByIndex(1)->GetGeometryNode()->GetFrameRect();
    EXPECT_EQ(frameRect.GetX(), (DEFAULT_COLUMNS - 1) * DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(frameRect.GetY(), DEFAULT_HEIGHT);
}

/**
 * @tc.name: Algorithm006
 * @tc.desc: Test GridCol layout order.
 * @tc.type: FUNC
 */
HWTEST_F(GridRowTestNg, Algorithm006, TestSize.Level1)
{
    auto colLayoutFront = colNodes_.front()->GetLayoutProperty<GridColLayoutProperty>();
    colLayoutFront->UpdateOrder(V2::GridContainerSize(6));
    auto colLayoutBack = colNodes_.back()->GetLayoutProperty<GridColLayoutProperty>();
    colLayoutBack->UpdateOrder(V2::GridContainerSize(-1));
    auto layoutWrapper = CreateLayoutWrapperAndLayout(true);
    auto frameRect = layoutWrapper->GetOrCreateChildByIndex(0)->GetGeometryNode()->GetFrameRect();

    EXPECT_EQ(frameRect.GetX(), 0);
    EXPECT_EQ(frameRect.GetY(), DEFAULT_HEIGHT); // because of DEFAULT_OFFSET, the col is at second row
}

/**
 * @tc.name: Algorithm007
 * @tc.desc: Test GridRow layout algorithm with text direction = Reverse,
 *           System parameter is left to right.
 * @tc.type: FUNC
 */
HWTEST_F(GridRowTestNg, Algorithm007, TestSize.Level1)
{
    auto pipeLine = PipelineBase::GetCurrentContext();
    auto layoutProperty = rowNode_->GetLayoutProperty<GridRowLayoutProperty>();
    // Set RowReverse
    layoutProperty->UpdateDirection(V2::GridRowDirection::RowReverse);
    // Set LTR
    pipeLine->SetIsRightToLeft(false);

    // get row direction
    auto direction = layoutProperty->GetDirection();
    EXPECT_EQ(direction, V2::GridRowDirection::RowReverse);
    auto isRTL = pipeLine->IsRightToLeft();
    EXPECT_EQ(isRTL, false);

    auto layoutWrapper = CreateLayoutWrapperAndLayout(true);
    auto frameRect = layoutWrapper->GetOrCreateChildByIndex(0)->GetGeometryNode()->GetFrameRect();
    auto columnWidth = frameRect.Width();
    EXPECT_EQ(columnWidth, DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(frameRect.GetX(), DEFAULT_GRID_ROW_WIDTH - DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(frameRect.GetY(), DEFAULT_HEIGHT);
    frameRect = layoutWrapper->GetOrCreateChildByIndex(1)->GetGeometryNode()->GetFrameRect();
    EXPECT_EQ(frameRect.GetX(), (DEFAULT_COLUMNS - 1) * DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(frameRect.GetY(), 0);
}

/**
 * @tc.name: Algorithm008
 * @tc.desc: Test GridRow layout algorithm with text direction = Row,
 *           System parameter is right to left.
 * @tc.type: FUNC
 */
HWTEST_F(GridRowTestNg, Algorithm008, TestSize.Level1)
{
    auto pipeLine = PipelineBase::GetCurrentContext();
    auto layoutProperty = rowNode_->GetLayoutProperty<GridRowLayoutProperty>();

    // Set Row
    layoutProperty->UpdateDirection(V2::GridRowDirection::Row);
    // Set RTL
    pipeLine->SetIsRightToLeft(true);

    // get row direction
    auto direction = layoutProperty->GetDirection();
    EXPECT_EQ(direction, V2::GridRowDirection::Row);
    auto isRTL = pipeLine->IsRightToLeft();
    EXPECT_EQ(isRTL, true);

    auto layoutWrapper = CreateLayoutWrapperAndLayout(true);
    auto frameRect = layoutWrapper->GetOrCreateChildByIndex(0)->GetGeometryNode()->GetFrameRect();
    auto columnWidth = frameRect.Width();
    EXPECT_EQ(columnWidth, DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(frameRect.GetX(), DEFAULT_GRID_ROW_WIDTH - (DEFAULT_OFFSET + 1) * DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(frameRect.GetY(), DEFAULT_HEIGHT);
    frameRect = layoutWrapper->GetOrCreateChildByIndex(1)->GetGeometryNode()->GetFrameRect();
    EXPECT_EQ(frameRect.GetX(), 0);
    EXPECT_EQ(frameRect.GetY(), 0);
}

/**
 * @tc.name: Algorithm009
 * @tc.desc: Test GridRow layout algorithm with text direction = Reverse,
 *           Layout direction is auto, System parameter is left to right.
 * @tc.type: FUNC
 */
HWTEST_F(GridRowTestNg, Algorithm009, TestSize.Level1)
{
    auto pipeLine = PipelineBase::GetCurrentContext();
    auto layoutProperty = rowNode_->GetLayoutProperty<GridRowLayoutProperty>();
    // Set RowReverse
    layoutProperty->UpdateDirection(V2::GridRowDirection::RowReverse);
    // Set LTR
    pipeLine->SetIsRightToLeft(false);
    // Set Layout direction
    layoutProperty->UpdateLayoutDirection(TextDirection::AUTO);

    // get row direction
    auto direction = layoutProperty->GetDirection();
    EXPECT_EQ(direction, V2::GridRowDirection::RowReverse);
    auto textDirection = layoutProperty->GetLayoutDirection();
    EXPECT_EQ(textDirection, TextDirection::AUTO);
    auto isRTL = pipeLine->IsRightToLeft();
    EXPECT_EQ(isRTL, false);

    auto layoutWrapper = CreateLayoutWrapperAndLayout(true);
    auto frameRect = layoutWrapper->GetOrCreateChildByIndex(0)->GetGeometryNode()->GetFrameRect();
    auto columnWidth = frameRect.Width();
    EXPECT_EQ(columnWidth, DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(frameRect.GetX(), (DEFAULT_COLUMNS - 1) * DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(frameRect.GetY(), DEFAULT_HEIGHT);
    frameRect = layoutWrapper->GetOrCreateChildByIndex(1)->GetGeometryNode()->GetFrameRect();
    EXPECT_EQ(frameRect.GetX(), (DEFAULT_COLUMNS - 1) * DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(frameRect.GetY(), 0);
}

/**
 * @tc.name: Algorithm010
 * @tc.desc: Test GridRow layout algorithm with text direction = Row,
 *           Layout direction is auto, System parameter is right to left.
 * @tc.type: FUNC
 */
HWTEST_F(GridRowTestNg, Algorithm010, TestSize.Level1)
{
    auto pipeLine = PipelineBase::GetCurrentContext();
    auto layoutProperty = rowNode_->GetLayoutProperty<GridRowLayoutProperty>();
    // Set Row
    layoutProperty->UpdateDirection(V2::GridRowDirection::Row);
    // Set RTL
    pipeLine->SetIsRightToLeft(true);
    // Set Layout direction
    layoutProperty->UpdateLayoutDirection(TextDirection::AUTO);

    // get row direction
    auto direction = layoutProperty->GetDirection();
    EXPECT_EQ(direction, V2::GridRowDirection::Row);
    auto textDirection = layoutProperty->GetLayoutDirection();
    EXPECT_EQ(textDirection, TextDirection::AUTO);
    auto isRTL = pipeLine->IsRightToLeft();
    EXPECT_EQ(isRTL, true);

    auto layoutWrapper = CreateLayoutWrapperAndLayout(true);
    auto frameRect = layoutWrapper->GetOrCreateChildByIndex(0)->GetGeometryNode()->GetFrameRect();
    auto columnWidth = frameRect.Width();
    EXPECT_EQ(columnWidth, DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(frameRect.GetX(), DEFAULT_GRID_ROW_WIDTH - (DEFAULT_OFFSET + 1) * DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(frameRect.GetY(), DEFAULT_HEIGHT);
    frameRect = layoutWrapper->GetOrCreateChildByIndex(1)->GetGeometryNode()->GetFrameRect();
    EXPECT_EQ(frameRect.GetX(), 0);
    EXPECT_EQ(frameRect.GetY(), 0);
}

/**
 * @tc.name: Algorithm011
 * @tc.desc: Test GridRow layout algorithm with text direction = Row,
 *           Layout direction is auto, System parameter is left to right.
 * @tc.type: FUNC
 */
HWTEST_F(GridRowTestNg, Algorithm011, TestSize.Level1)
{
    auto pipeLine = PipelineBase::GetCurrentContext();
    auto layoutProperty = rowNode_->GetLayoutProperty<GridRowLayoutProperty>();
    // Set Row
    layoutProperty->UpdateDirection(V2::GridRowDirection::Row);
    // Set LTR
    pipeLine->SetIsRightToLeft(false);
    // Set Layout direction
    layoutProperty->UpdateLayoutDirection(TextDirection::AUTO);

    // get row direction
    auto direction = layoutProperty->GetDirection();
    EXPECT_EQ(direction, V2::GridRowDirection::Row);
    auto textDirection = layoutProperty->GetLayoutDirection();
    EXPECT_EQ(textDirection, TextDirection::AUTO);
    auto isRTL = pipeLine->IsRightToLeft();
    EXPECT_EQ(isRTL, false);

    auto layoutWrapper = CreateLayoutWrapperAndLayout(true);
    auto frameRect = layoutWrapper->GetOrCreateChildByIndex(0)->GetGeometryNode()->GetFrameRect();
    auto columnWidth = frameRect.Width();
    EXPECT_EQ(columnWidth, DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(frameRect.GetX(), 0);
    EXPECT_EQ(frameRect.GetY(), DEFAULT_HEIGHT);
    frameRect = layoutWrapper->GetOrCreateChildByIndex(1)->GetGeometryNode()->GetFrameRect();
    EXPECT_EQ(frameRect.GetX(), 0);
    EXPECT_EQ(frameRect.GetY(), 0);
}

/**
 * @tc.name: Algorithm012
 * @tc.desc: Test GridRow layout algorithm with text direction = RowReverse,
 *           Layout direction is auto, System parameter is right to left.
 * @tc.type: FUNC
 */
HWTEST_F(GridRowTestNg, Algorithm012, TestSize.Level1)
{
    auto pipeLine = PipelineBase::GetCurrentContext();
    auto layoutProperty = rowNode_->GetLayoutProperty<GridRowLayoutProperty>();
    // Set RowReverse
    layoutProperty->UpdateDirection(V2::GridRowDirection::RowReverse);
    // Set RTL
    pipeLine->SetIsRightToLeft(true);
    // Set Layout direction
    layoutProperty->UpdateLayoutDirection(TextDirection::AUTO);

    // get row direction
    auto direction = layoutProperty->GetDirection();
    EXPECT_EQ(direction, V2::GridRowDirection::RowReverse);
    auto textDirection = layoutProperty->GetLayoutDirection();
    EXPECT_EQ(textDirection, TextDirection::AUTO);
    auto isRTL = pipeLine->IsRightToLeft();
    EXPECT_EQ(isRTL, true);

    auto layoutWrapper = CreateLayoutWrapperAndLayout(true);
    auto frameRect = layoutWrapper->GetOrCreateChildByIndex(0)->GetGeometryNode()->GetFrameRect();
    auto columnWidth = frameRect.Width();
    EXPECT_EQ(columnWidth, DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(frameRect.GetX(), DEFAULT_GRID_ROW_WIDTH - DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(frameRect.GetY(), DEFAULT_HEIGHT);
    frameRect = layoutWrapper->GetOrCreateChildByIndex(1)->GetGeometryNode()->GetFrameRect();
    EXPECT_EQ(frameRect.GetX(), DEFAULT_GRID_ROW_WIDTH - DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(frameRect.GetY(), 0);
}

/**
 * @tc.name: ItemAlign001
 * @tc.desc: Test GridRow layout algorithm with default ItemAlign.
 * @tc.type: FUNC
 */
HWTEST_F(GridRowTestNg, ItemAlign001, TestSize.Level1)
{
    auto layoutProperty = rowNode_->GetLayoutProperty<GridRowLayoutProperty>();
    auto direction = layoutProperty->GetDirection();
    EXPECT_EQ(direction, V2::GridRowDirection::Row);
    auto itemAlign = layoutProperty->GetAlignItems();
    EXPECT_FALSE(itemAlign.has_value());

    /**
     * @tc.steps: step1. create environment for running process.
     */
    auto firstColNode = colNodes_.front();
    auto firstColLayoutProperty = firstColNode->GetLayoutProperty<GridColLayoutProperty>();
    firstColLayoutProperty->UpdateSpan(V2::GridContainerSize(1));
    firstColLayoutProperty->UpdateOffset(V2::GridContainerSize(0));
    firstColLayoutProperty->UpdateOrder(V2::GridContainerSize());
    firstColLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(TEST_ALIGN_HEIGHT)));

    auto secondColNode = colNodes_.back();
    auto secondColLayoutProperty = secondColNode->GetLayoutProperty<GridColLayoutProperty>();
    secondColLayoutProperty->UpdateSpan(V2::GridContainerSize(1));
    secondColLayoutProperty->UpdateOffset(V2::GridContainerSize(0));
    secondColLayoutProperty->UpdateOrder(V2::GridContainerSize());
    secondColLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(DEFAULT_HEIGHT)));

    /**
     * @tc.steps: step2. Running layout function and check the result with expected results.
     */
    auto layoutWrapper = CreateLayoutWrapperAndLayout(true);
    auto frameRect = layoutWrapper->GetOrCreateChildByIndex(0)->GetGeometryNode()->GetFrameRect();
    auto columnWidth = frameRect.Width();
    auto columnHeight = frameRect.Height();
    EXPECT_EQ(frameRect.GetX(), 0);
    EXPECT_EQ(frameRect.GetY(), 0);
    EXPECT_EQ(columnWidth, DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(columnHeight, TEST_ALIGN_HEIGHT);

    frameRect = layoutWrapper->GetOrCreateChildByIndex(1)->GetGeometryNode()->GetFrameRect();
    columnWidth = frameRect.Width();
    columnHeight = frameRect.Height();
    EXPECT_EQ(frameRect.GetX(), DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(frameRect.GetY(), 0);
    EXPECT_EQ(columnWidth, DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(columnHeight, DEFAULT_HEIGHT);
}

/**
 * @tc.name: ItemAlign002
 * @tc.desc: Test GridRow layout algorithm with ItemAlign.Start.
 * @tc.type: FUNC
 */
HWTEST_F(GridRowTestNg, ItemAlign002, TestSize.Level1)
{
    auto layoutProperty = rowNode_->GetLayoutProperty<GridRowLayoutProperty>();
    layoutProperty->UpdateAlignItems(FlexAlign::FLEX_START);

    /**
     * @tc.steps: step1. create environment for running process.
     */
    auto firstColNode = colNodes_.front();
    auto firstColLayoutProperty = firstColNode->GetLayoutProperty<GridColLayoutProperty>();
    firstColLayoutProperty->UpdateSpan(V2::GridContainerSize(1));
    firstColLayoutProperty->UpdateOffset(V2::GridContainerSize(0));
    firstColLayoutProperty->UpdateOrder(V2::GridContainerSize());
    firstColLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(TEST_ALIGN_HEIGHT)));

    auto secondColNode = colNodes_.back();
    auto secondColLayoutProperty = secondColNode->GetLayoutProperty<GridColLayoutProperty>();
    secondColLayoutProperty->UpdateSpan(V2::GridContainerSize(1));
    secondColLayoutProperty->UpdateOffset(V2::GridContainerSize(0));
    secondColLayoutProperty->UpdateOrder(V2::GridContainerSize());
    secondColLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(DEFAULT_HEIGHT)));

    /**
     * @tc.steps: step2. Running layout function and check the result with expected results.
     */
    auto layoutWrapper = CreateLayoutWrapperAndLayout(true);
    auto frameRect = layoutWrapper->GetOrCreateChildByIndex(0)->GetGeometryNode()->GetFrameRect();
    auto columnWidth = frameRect.Width();
    auto columnHeight = frameRect.Height();
    EXPECT_EQ(frameRect.GetX(), 0);
    EXPECT_EQ(frameRect.GetY(), 0);
    EXPECT_EQ(columnWidth, DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(columnHeight, TEST_ALIGN_HEIGHT);

    frameRect = layoutWrapper->GetOrCreateChildByIndex(1)->GetGeometryNode()->GetFrameRect();
    columnWidth = frameRect.Width();
    columnHeight = frameRect.Height();
    EXPECT_EQ(frameRect.GetX(), DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(frameRect.GetY(), 0);
    EXPECT_EQ(columnWidth, DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(columnHeight, DEFAULT_HEIGHT);
}

/**
 * @tc.name: ItemAlign003
 * @tc.desc: Test GridRow layout algorithm with ItemAlign.Center.
 * @tc.type: FUNC
 */
HWTEST_F(GridRowTestNg, ItemAlign003, TestSize.Level1)
{
    auto layoutProperty = rowNode_->GetLayoutProperty<GridRowLayoutProperty>();
    layoutProperty->UpdateAlignItems(FlexAlign::CENTER);

    /**
     * @tc.steps: step1. create environment for running process.
     */
    auto firstColNode = colNodes_.front();
    auto firstColLayoutProperty = firstColNode->GetLayoutProperty<GridColLayoutProperty>();
    firstColLayoutProperty->UpdateSpan(V2::GridContainerSize(1));
    firstColLayoutProperty->UpdateOffset(V2::GridContainerSize(0));
    firstColLayoutProperty->UpdateOrder(V2::GridContainerSize());
    firstColLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(TEST_ALIGN_HEIGHT)));

    auto secondColNode = colNodes_.back();
    auto secondColLayoutProperty = secondColNode->GetLayoutProperty<GridColLayoutProperty>();
    secondColLayoutProperty->UpdateSpan(V2::GridContainerSize(1));
    secondColLayoutProperty->UpdateOffset(V2::GridContainerSize(0));
    secondColLayoutProperty->UpdateOrder(V2::GridContainerSize());
    secondColLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(DEFAULT_HEIGHT)));

    /**
     * @tc.steps: step2. Running layout function and check the result with expected results.
     */
    auto layoutWrapper = CreateLayoutWrapperAndLayout(true);
    auto frameRect = layoutWrapper->GetOrCreateChildByIndex(0)->GetGeometryNode()->GetFrameRect();
    auto columnWidth = frameRect.Width();
    auto columnHeight = frameRect.Height();
    EXPECT_EQ(frameRect.GetX(), 0);
    EXPECT_EQ(frameRect.GetY(), 0);
    EXPECT_EQ(columnWidth, DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(columnHeight, TEST_ALIGN_HEIGHT);

    frameRect = layoutWrapper->GetOrCreateChildByIndex(1)->GetGeometryNode()->GetFrameRect();
    columnWidth = frameRect.Width();
    columnHeight = frameRect.Height();
    EXPECT_EQ(frameRect.GetX(), DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(frameRect.GetY(), TEST_ALIGN_HEIGHT * 0.5 - DEFAULT_HEIGHT * 0.5);
    EXPECT_EQ(columnWidth, DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(columnHeight, DEFAULT_HEIGHT);
}

/**
 * @tc.name: ItemAlign004
 * @tc.desc: Test GridRow layout algorithm with ItemAlign.End.
 * @tc.type: FUNC
 */
HWTEST_F(GridRowTestNg, ItemAlign004, TestSize.Level1)
{
    auto layoutProperty = rowNode_->GetLayoutProperty<GridRowLayoutProperty>();
    layoutProperty->UpdateAlignItems(FlexAlign::FLEX_END);

    /**
     * @tc.steps: step1. create environment for running process.
     */
    auto firstColNode = colNodes_.front();
    auto firstColLayoutProperty = firstColNode->GetLayoutProperty<GridColLayoutProperty>();
    firstColLayoutProperty->UpdateSpan(V2::GridContainerSize(1));
    firstColLayoutProperty->UpdateOffset(V2::GridContainerSize(0));
    firstColLayoutProperty->UpdateOrder(V2::GridContainerSize());
    firstColLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(TEST_ALIGN_HEIGHT)));

    auto secondColNode = colNodes_.back();
    auto secondColLayoutProperty = secondColNode->GetLayoutProperty<GridColLayoutProperty>();
    secondColLayoutProperty->UpdateSpan(V2::GridContainerSize(1));
    secondColLayoutProperty->UpdateOffset(V2::GridContainerSize(0));
    secondColLayoutProperty->UpdateOrder(V2::GridContainerSize());
    secondColLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(DEFAULT_HEIGHT)));

    /**
     * @tc.steps: step2. Running layout function and check the result with expected results.
     */
    auto layoutWrapper = CreateLayoutWrapperAndLayout(true);
    auto frameRect = layoutWrapper->GetOrCreateChildByIndex(0)->GetGeometryNode()->GetFrameRect();
    auto columnWidth = frameRect.Width();
    auto columnHeight = frameRect.Height();
    EXPECT_EQ(frameRect.GetX(), 0);
    EXPECT_EQ(frameRect.GetY(), 0);
    EXPECT_EQ(columnWidth, DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(columnHeight, TEST_ALIGN_HEIGHT);

    frameRect = layoutWrapper->GetOrCreateChildByIndex(1)->GetGeometryNode()->GetFrameRect();
    columnWidth = frameRect.Width();
    columnHeight = frameRect.Height();
    EXPECT_EQ(frameRect.GetX(), DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(frameRect.GetY(), TEST_ALIGN_HEIGHT - DEFAULT_HEIGHT);
    EXPECT_EQ(columnWidth, DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(columnHeight, DEFAULT_HEIGHT);
}

/**
 * @tc.name: ItemAlign005
 * @tc.desc: Test GridRow layout algorithm with ItemAlign.STRETCH.
 * @tc.type: FUNC
 */
HWTEST_F(GridRowTestNg, ItemAlign005, TestSize.Level1)
{
    auto layoutProperty = rowNode_->GetLayoutProperty<GridRowLayoutProperty>();
    layoutProperty->UpdateAlignItems(FlexAlign::STRETCH);

    /**
     * @tc.steps: step1. create environment for running process.
     */
    auto firstColNode = colNodes_.front();
    auto firstColLayoutProperty = firstColNode->GetLayoutProperty<GridColLayoutProperty>();
    firstColLayoutProperty->UpdateSpan(V2::GridContainerSize(1));
    firstColLayoutProperty->UpdateOffset(V2::GridContainerSize(0));
    firstColLayoutProperty->UpdateOrder(V2::GridContainerSize());
    firstColLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(TEST_ALIGN_HEIGHT)));

    auto secondColNode = colNodes_.back();
    auto secondColLayoutProperty = secondColNode->GetLayoutProperty<GridColLayoutProperty>();
    secondColLayoutProperty->UpdateSpan(V2::GridContainerSize(1));
    secondColLayoutProperty->UpdateOffset(V2::GridContainerSize(0));
    secondColLayoutProperty->UpdateOrder(V2::GridContainerSize());
    secondColLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(DEFAULT_HEIGHT)));

    /**
     * @tc.steps: step2. Running layout function and check the result with expected results.
     */
    auto layoutWrapper = CreateLayoutWrapperAndLayout(true);
    auto frameRect = layoutWrapper->GetOrCreateChildByIndex(0)->GetGeometryNode()->GetFrameRect();
    auto columnWidth = frameRect.Width();
    auto columnHeight = frameRect.Height();
    EXPECT_EQ(frameRect.GetX(), 0);
    EXPECT_EQ(frameRect.GetY(), 0);
    EXPECT_EQ(columnWidth, DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(columnHeight, TEST_ALIGN_HEIGHT);

    frameRect = layoutWrapper->GetOrCreateChildByIndex(1)->GetGeometryNode()->GetFrameRect();
    columnWidth = frameRect.Width();
    columnHeight = frameRect.Height();
    EXPECT_EQ(frameRect.GetX(), DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(frameRect.GetY(), 0);
    EXPECT_EQ(columnWidth, DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(columnHeight, TEST_ALIGN_HEIGHT);
}

/**
 * @tc.name: ItemAlign006
 * @tc.desc: Test GridRow layout algorithm with diferent direction and default ItemAlign
 * @tc.type: FUNC
 */
HWTEST_F(GridRowTestNg, ItemAlign006, TestSize.Level1)
{
    auto layoutProperty = rowNode_->GetLayoutProperty<GridRowLayoutProperty>();
    layoutProperty->ResetAlignItems();
    auto itemAlign = layoutProperty->GetAlignItems();
    layoutProperty->UpdateDirection(V2::GridRowDirection::RowReverse);
    EXPECT_FALSE(itemAlign.has_value());

    /**
     * @tc.steps: step1. create environment for running process.
     */
    auto firstColNode = colNodes_.front();
    auto firstColLayoutProperty = firstColNode->GetLayoutProperty<GridColLayoutProperty>();
    firstColLayoutProperty->UpdateSpan(V2::GridContainerSize(1));
    firstColLayoutProperty->UpdateOffset(V2::GridContainerSize(0));
    firstColLayoutProperty->UpdateOrder(V2::GridContainerSize());
    firstColLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(TEST_ALIGN_HEIGHT)));

    auto secondColNode = colNodes_.back();
    auto secondColLayoutProperty = secondColNode->GetLayoutProperty<GridColLayoutProperty>();
    secondColLayoutProperty->UpdateSpan(V2::GridContainerSize(1));
    secondColLayoutProperty->UpdateOffset(V2::GridContainerSize(0));
    secondColLayoutProperty->UpdateOrder(V2::GridContainerSize());
    secondColLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(DEFAULT_HEIGHT)));

    /**
     * @tc.steps: step2. Running layout function and check the result with expected results.
     */
    auto layoutWrapper = CreateLayoutWrapperAndLayout(true);
    auto frameRect = layoutWrapper->GetOrCreateChildByIndex(0)->GetGeometryNode()->GetFrameRect();
    auto columnWidth = frameRect.Width();
    auto columnHeight = frameRect.Height();
    EXPECT_EQ(frameRect.GetX(), DEFAULT_GRID_ROW_WIDTH - DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(frameRect.GetY(), 0);
    EXPECT_EQ(columnWidth, DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(columnHeight, TEST_ALIGN_HEIGHT);

    frameRect = layoutWrapper->GetOrCreateChildByIndex(1)->GetGeometryNode()->GetFrameRect();
    columnWidth = frameRect.Width();
    columnHeight = frameRect.Height();
    EXPECT_EQ(frameRect.GetX(), DEFAULT_GRID_ROW_WIDTH - DEFAULT_SPAN_WIDTH * 2);
    EXPECT_EQ(frameRect.GetY(), 0);
    EXPECT_EQ(columnWidth, DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(columnHeight, DEFAULT_HEIGHT);
}

/**
 * @tc.name: ItemAlign007
 * @tc.desc: Test GridRow layout algorithm with diferent direction and ItemAlign.Start.
 * @tc.type: FUNC
 */
HWTEST_F(GridRowTestNg, ItemAlign007, TestSize.Level1)
{
    auto layoutProperty = rowNode_->GetLayoutProperty<GridRowLayoutProperty>();
    layoutProperty->UpdateDirection(V2::GridRowDirection::RowReverse);
    layoutProperty->UpdateAlignItems(FlexAlign::FLEX_START);

    /**
     * @tc.steps: step1. create environment for running process.
     */
    auto firstColNode = colNodes_.front();
    auto firstColLayoutProperty = firstColNode->GetLayoutProperty<GridColLayoutProperty>();
    firstColLayoutProperty->UpdateSpan(V2::GridContainerSize(1));
    firstColLayoutProperty->UpdateOffset(V2::GridContainerSize(0));
    firstColLayoutProperty->UpdateOrder(V2::GridContainerSize());
    firstColLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(TEST_ALIGN_HEIGHT)));

    auto secondColNode = colNodes_.back();
    auto secondColLayoutProperty = secondColNode->GetLayoutProperty<GridColLayoutProperty>();
    secondColLayoutProperty->UpdateSpan(V2::GridContainerSize(1));
    secondColLayoutProperty->UpdateOffset(V2::GridContainerSize(0));
    secondColLayoutProperty->UpdateOrder(V2::GridContainerSize());
    secondColLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(DEFAULT_HEIGHT)));

    /**
     * @tc.steps: step2. Running layout function and check the result with expected results.
     */
    auto layoutWrapper = CreateLayoutWrapperAndLayout(true);
    auto frameRect = layoutWrapper->GetOrCreateChildByIndex(0)->GetGeometryNode()->GetFrameRect();
    auto columnWidth = frameRect.Width();
    auto columnHeight = frameRect.Height();
    EXPECT_EQ(frameRect.GetX(), DEFAULT_GRID_ROW_WIDTH - DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(frameRect.GetY(), 0);
    EXPECT_EQ(columnWidth, DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(columnHeight, TEST_ALIGN_HEIGHT);

    frameRect = layoutWrapper->GetOrCreateChildByIndex(1)->GetGeometryNode()->GetFrameRect();
    columnWidth = frameRect.Width();
    columnHeight = frameRect.Height();
    EXPECT_EQ(frameRect.GetX(), DEFAULT_GRID_ROW_WIDTH - DEFAULT_SPAN_WIDTH * 2);
    EXPECT_EQ(frameRect.GetY(), 0);
    EXPECT_EQ(columnWidth, DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(columnHeight, DEFAULT_HEIGHT);
}

/**
 * @tc.name: ItemAlign008
 * @tc.desc: Test GridRow layout algorithm with diferent direction and ItemAlign.Center.
 * @tc.type: FUNC
 */
HWTEST_F(GridRowTestNg, ItemAlign008, TestSize.Level1)
{
    auto layoutProperty = rowNode_->GetLayoutProperty<GridRowLayoutProperty>();
    layoutProperty->UpdateDirection(V2::GridRowDirection::RowReverse);
    layoutProperty->UpdateAlignItems(FlexAlign::CENTER);

    /**
     * @tc.steps: step1. create environment for running process.
     */
    auto firstColNode = colNodes_.front();
    auto firstColLayoutProperty = firstColNode->GetLayoutProperty<GridColLayoutProperty>();
    firstColLayoutProperty->UpdateSpan(V2::GridContainerSize(1));
    firstColLayoutProperty->UpdateOffset(V2::GridContainerSize(0));
    firstColLayoutProperty->UpdateOrder(V2::GridContainerSize());
    firstColLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(TEST_ALIGN_HEIGHT)));

    auto secondColNode = colNodes_.back();
    auto secondColLayoutProperty = secondColNode->GetLayoutProperty<GridColLayoutProperty>();
    secondColLayoutProperty->UpdateSpan(V2::GridContainerSize(1));
    secondColLayoutProperty->UpdateOffset(V2::GridContainerSize(0));
    secondColLayoutProperty->UpdateOrder(V2::GridContainerSize());
    secondColLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(DEFAULT_HEIGHT)));

    /**
     * @tc.steps: step2. Running layout function and check the result with expected results.
     */
    auto layoutWrapper = CreateLayoutWrapperAndLayout(true);
    auto frameRect = layoutWrapper->GetOrCreateChildByIndex(0)->GetGeometryNode()->GetFrameRect();
    auto columnWidth = frameRect.Width();
    auto columnHeight = frameRect.Height();
    EXPECT_EQ(frameRect.GetX(), DEFAULT_GRID_ROW_WIDTH - DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(frameRect.GetY(), 0);
    EXPECT_EQ(columnWidth, DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(columnHeight, TEST_ALIGN_HEIGHT);

    frameRect = layoutWrapper->GetOrCreateChildByIndex(1)->GetGeometryNode()->GetFrameRect();
    columnWidth = frameRect.Width();
    columnHeight = frameRect.Height();
    EXPECT_EQ(frameRect.GetX(), DEFAULT_GRID_ROW_WIDTH - DEFAULT_SPAN_WIDTH * 2);
    EXPECT_EQ(frameRect.GetY(), TEST_ALIGN_HEIGHT * 0.5 - DEFAULT_HEIGHT * 0.5);
    EXPECT_EQ(columnWidth, DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(columnHeight, DEFAULT_HEIGHT);
}
/**
 * @tc.name: ItemAlign009
 * @tc.desc: Test GridRow layout algorithm with ItemAlign.End.
 * @tc.type: FUNC
 */
HWTEST_F(GridRowTestNg, ItemAlign009, TestSize.Level1)
{
    auto layoutProperty = rowNode_->GetLayoutProperty<GridRowLayoutProperty>();
    layoutProperty->UpdateDirection(V2::GridRowDirection::RowReverse);
    layoutProperty->UpdateAlignItems(FlexAlign::FLEX_END);

    /**
     * @tc.steps: step1. create environment for running process.
     */
    auto firstColNode = colNodes_.front();
    auto firstColLayoutProperty = firstColNode->GetLayoutProperty<GridColLayoutProperty>();
    firstColLayoutProperty->UpdateSpan(V2::GridContainerSize(1));
    firstColLayoutProperty->UpdateOffset(V2::GridContainerSize(0));
    firstColLayoutProperty->UpdateOrder(V2::GridContainerSize());
    firstColLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(TEST_ALIGN_HEIGHT)));

    auto secondColNode = colNodes_.back();
    auto secondColLayoutProperty = secondColNode->GetLayoutProperty<GridColLayoutProperty>();
    secondColLayoutProperty->UpdateSpan(V2::GridContainerSize(1));
    secondColLayoutProperty->UpdateOffset(V2::GridContainerSize(0));
    secondColLayoutProperty->UpdateOrder(V2::GridContainerSize());
    secondColLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(DEFAULT_HEIGHT)));

    /**
     * @tc.steps: step2. Running layout function and check the result with expected results.
     */
    auto layoutWrapper = CreateLayoutWrapperAndLayout(true);
    auto frameRect = layoutWrapper->GetOrCreateChildByIndex(0)->GetGeometryNode()->GetFrameRect();
    auto columnWidth = frameRect.Width();
    auto columnHeight = frameRect.Height();
    EXPECT_EQ(frameRect.GetX(), DEFAULT_GRID_ROW_WIDTH-DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(frameRect.GetY(), 0);
    EXPECT_EQ(columnWidth, DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(columnHeight, TEST_ALIGN_HEIGHT);

    frameRect = layoutWrapper->GetOrCreateChildByIndex(1)->GetGeometryNode()->GetFrameRect();
    columnWidth = frameRect.Width();
    columnHeight = frameRect.Height();
    EXPECT_EQ(frameRect.GetX(), DEFAULT_GRID_ROW_WIDTH - DEFAULT_SPAN_WIDTH * 2);
    EXPECT_EQ(frameRect.GetY(), TEST_ALIGN_HEIGHT - DEFAULT_HEIGHT);
    EXPECT_EQ(columnWidth, DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(columnHeight, DEFAULT_HEIGHT);
}

/**
 * @tc.name: ItemAlign010
 * @tc.desc: Test GridRow layout algorithm with ItemAlign.STRETCH.
 * @tc.type: FUNC
 */
HWTEST_F(GridRowTestNg, ItemAlign010, TestSize.Level1)
{
    auto layoutProperty = rowNode_->GetLayoutProperty<GridRowLayoutProperty>();
    layoutProperty->UpdateDirection(V2::GridRowDirection::RowReverse);
    layoutProperty->UpdateAlignItems(FlexAlign::STRETCH);

    /**
     * @tc.steps: step1. create environment for running process.
     */
    auto firstColNode = colNodes_.front();
    auto firstColLayoutProperty = firstColNode->GetLayoutProperty<GridColLayoutProperty>();
    firstColLayoutProperty->UpdateSpan(V2::GridContainerSize(1));
    firstColLayoutProperty->UpdateOffset(V2::GridContainerSize(0));
    firstColLayoutProperty->UpdateOrder(V2::GridContainerSize());
    firstColLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(TEST_ALIGN_HEIGHT)));

    auto secondColNode = colNodes_.back();
    auto secondColLayoutProperty = secondColNode->GetLayoutProperty<GridColLayoutProperty>();
    secondColLayoutProperty->UpdateSpan(V2::GridContainerSize(1));
    secondColLayoutProperty->UpdateOffset(V2::GridContainerSize(0));
    secondColLayoutProperty->UpdateOrder(V2::GridContainerSize());
    secondColLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(DEFAULT_HEIGHT)));

    /**
     * @tc.steps: step2. Running layout function and check the result with expected results.
     */
    auto layoutWrapper = CreateLayoutWrapperAndLayout(true);
    auto frameRect = layoutWrapper->GetOrCreateChildByIndex(0)->GetGeometryNode()->GetFrameRect();
    auto columnWidth = frameRect.Width();
    auto columnHeight = frameRect.Height();
    EXPECT_EQ(frameRect.GetX(), DEFAULT_GRID_ROW_WIDTH - DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(frameRect.GetY(), 0);
    EXPECT_EQ(columnWidth, DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(columnHeight, TEST_ALIGN_HEIGHT);

    frameRect = layoutWrapper->GetOrCreateChildByIndex(1)->GetGeometryNode()->GetFrameRect();
    columnWidth = frameRect.Width();
    columnHeight = frameRect.Height();
    EXPECT_EQ(frameRect.GetX(), DEFAULT_GRID_ROW_WIDTH - DEFAULT_SPAN_WIDTH  * 2);
    EXPECT_EQ(frameRect.GetY(), 0);
    EXPECT_EQ(columnWidth, DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(columnHeight, TEST_ALIGN_HEIGHT);
}

/**
 * @tc.name: ItemAlign011
 * @tc.desc: Test GridRow layout algorithm with diferent offset and default ItemAlign
 * @tc.type: FUNC
 */
HWTEST_F(GridRowTestNg, ItemAlign011, TestSize.Level1)
{
    auto layoutProperty = rowNode_->GetLayoutProperty<GridRowLayoutProperty>();
    layoutProperty->ResetAlignItems();
    auto itemAlign = layoutProperty->GetAlignItems();
    layoutProperty->UpdateDirection(V2::GridRowDirection::Row);
    EXPECT_FALSE(itemAlign.has_value());

    /**
     * @tc.steps: step1. create environment for running process.
     */
    auto firstColNode = colNodes_.front();
    auto firstColLayoutProperty = firstColNode->GetLayoutProperty<GridColLayoutProperty>();
    firstColLayoutProperty->UpdateSpan(V2::GridContainerSize(1));
    firstColLayoutProperty->UpdateOffset(V2::GridContainerSize(7));
    firstColLayoutProperty->UpdateOrder(V2::GridContainerSize());
    firstColLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(TEST_ALIGN_HEIGHT)));

    auto secondColNode = colNodes_.back();
    auto secondColLayoutProperty = secondColNode->GetLayoutProperty<GridColLayoutProperty>();
    secondColLayoutProperty->UpdateSpan(V2::GridContainerSize(1));
    secondColLayoutProperty->UpdateOffset(V2::GridContainerSize(0));
    secondColLayoutProperty->UpdateOrder(V2::GridContainerSize());
    secondColLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(DEFAULT_HEIGHT)));

    /**
     * @tc.steps: step2. Running layout function and check the result with expected results.
     */
    auto layoutWrapper = CreateLayoutWrapperAndLayout(true);
    auto frameRect = layoutWrapper->GetOrCreateChildByIndex(0)->GetGeometryNode()->GetFrameRect();
    auto columnWidth = frameRect.Width();
    auto columnHeight = frameRect.Height();
    EXPECT_EQ(frameRect.GetX(), DEFAULT_GRID_ROW_WIDTH - DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(frameRect.GetY(), 0);
    EXPECT_EQ(columnWidth, DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(columnHeight, TEST_ALIGN_HEIGHT);

    frameRect = layoutWrapper->GetOrCreateChildByIndex(1)->GetGeometryNode()->GetFrameRect();
    columnWidth = frameRect.Width();
    columnHeight = frameRect.Height();
    EXPECT_EQ(frameRect.GetX(), 0);
    EXPECT_EQ(frameRect.GetY(), TEST_ALIGN_HEIGHT);
    EXPECT_EQ(columnWidth, DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(columnHeight, DEFAULT_HEIGHT);
}

/**
 * @tc.name: ItemAlign012
 * @tc.desc: Test GridRow layout algorithm with different offset and ItemAlign.Start.
 * @tc.type: FUNC
 */
HWTEST_F(GridRowTestNg, ItemAlign012, TestSize.Level1)
{
    auto layoutProperty = rowNode_->GetLayoutProperty<GridRowLayoutProperty>();
    layoutProperty->UpdateAlignItems(FlexAlign::FLEX_START);

    /**
     * @tc.steps: step1. create environment for running process.
     */
    auto firstColNode = colNodes_.front();
    auto firstColLayoutProperty = firstColNode->GetLayoutProperty<GridColLayoutProperty>();
    firstColLayoutProperty->UpdateSpan(V2::GridContainerSize(1));
    firstColLayoutProperty->UpdateOffset(V2::GridContainerSize(7));
    firstColLayoutProperty->UpdateOrder(V2::GridContainerSize());
    firstColLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(TEST_ALIGN_HEIGHT)));

    auto secondColNode = colNodes_.back();
    auto secondColLayoutProperty = secondColNode->GetLayoutProperty<GridColLayoutProperty>();
    secondColLayoutProperty->UpdateSpan(V2::GridContainerSize(1));
    secondColLayoutProperty->UpdateOffset(V2::GridContainerSize(0));
    secondColLayoutProperty->UpdateOrder(V2::GridContainerSize());
    secondColLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(DEFAULT_HEIGHT)));

    /**
     * @tc.steps: step2. Running layout function and check the result with expected results.
     */
    auto layoutWrapper = CreateLayoutWrapperAndLayout(true);
    auto frameRect = layoutWrapper->GetOrCreateChildByIndex(0)->GetGeometryNode()->GetFrameRect();
    auto columnWidth = frameRect.Width();
    auto columnHeight = frameRect.Height();
    EXPECT_EQ(frameRect.GetX(), DEFAULT_GRID_ROW_WIDTH - DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(frameRect.GetY(), 0);
    EXPECT_EQ(columnWidth, DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(columnHeight, TEST_ALIGN_HEIGHT);

    frameRect = layoutWrapper->GetOrCreateChildByIndex(1)->GetGeometryNode()->GetFrameRect();
    columnWidth = frameRect.Width();
    columnHeight = frameRect.Height();
    EXPECT_EQ(frameRect.GetX(), 0);
    EXPECT_EQ(frameRect.GetY(), TEST_ALIGN_HEIGHT);
    EXPECT_EQ(columnWidth, DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(columnHeight, DEFAULT_HEIGHT);
}

/**
 * @tc.name: ItemAlign013
 * @tc.desc: Test GridRow layout algorithm with different offset and ItemAlign.Center.
 * @tc.type: FUNC
 */
HWTEST_F(GridRowTestNg, ItemAlign013, TestSize.Level1)
{
    auto layoutProperty = rowNode_->GetLayoutProperty<GridRowLayoutProperty>();
    layoutProperty->UpdateAlignItems(FlexAlign::CENTER);

    /**
     * @tc.steps: step1. create environment for running process.
     */
    auto firstColNode = colNodes_.front();
    auto firstColLayoutProperty = firstColNode->GetLayoutProperty<GridColLayoutProperty>();
    firstColLayoutProperty->UpdateSpan(V2::GridContainerSize(1));
    firstColLayoutProperty->UpdateOffset(V2::GridContainerSize(7));
    firstColLayoutProperty->UpdateOrder(V2::GridContainerSize());
    firstColLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(TEST_ALIGN_HEIGHT)));

    auto secondColNode = colNodes_.back();
    auto secondColLayoutProperty = secondColNode->GetLayoutProperty<GridColLayoutProperty>();
    secondColLayoutProperty->UpdateSpan(V2::GridContainerSize(1));
    secondColLayoutProperty->UpdateOffset(V2::GridContainerSize(0));
    secondColLayoutProperty->UpdateOrder(V2::GridContainerSize());
    secondColLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(DEFAULT_HEIGHT)));

    /**
     * @tc.steps: step2. Running layout function and check the result with expected results.
     */
    auto layoutWrapper = CreateLayoutWrapperAndLayout(true);
    auto frameRect = layoutWrapper->GetOrCreateChildByIndex(0)->GetGeometryNode()->GetFrameRect();
    auto columnWidth = frameRect.Width();
    auto columnHeight = frameRect.Height();
    EXPECT_EQ(frameRect.GetX(), DEFAULT_GRID_ROW_WIDTH - DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(frameRect.GetY(), 0);
    EXPECT_EQ(columnWidth, DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(columnHeight, TEST_ALIGN_HEIGHT);

    frameRect = layoutWrapper->GetOrCreateChildByIndex(1)->GetGeometryNode()->GetFrameRect();
    columnWidth = frameRect.Width();
    columnHeight = frameRect.Height();
    EXPECT_EQ(frameRect.GetX(), 0);
    EXPECT_EQ(frameRect.GetY(), TEST_ALIGN_HEIGHT);
    EXPECT_EQ(columnWidth, DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(columnHeight, DEFAULT_HEIGHT);
}

/**
 * @tc.name: ItemAlign014
 * @tc.desc: Test GridRow layout algorithm with different offset and ItemAlign.End.
 * @tc.type: FUNC
 */
HWTEST_F(GridRowTestNg, ItemAlign014, TestSize.Level1)
{
    auto layoutProperty = rowNode_->GetLayoutProperty<GridRowLayoutProperty>();
    layoutProperty->UpdateAlignItems(FlexAlign::FLEX_END);

    /**
     * @tc.steps: step1. create environment for running process.
     */
    auto firstColNode = colNodes_.front();
    auto firstColLayoutProperty = firstColNode->GetLayoutProperty<GridColLayoutProperty>();
    firstColLayoutProperty->UpdateSpan(V2::GridContainerSize(1));
    firstColLayoutProperty->UpdateOffset(V2::GridContainerSize(7));
    firstColLayoutProperty->UpdateOrder(V2::GridContainerSize());
    firstColLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(TEST_ALIGN_HEIGHT)));

    auto secondColNode = colNodes_.back();
    auto secondColLayoutProperty = secondColNode->GetLayoutProperty<GridColLayoutProperty>();
    secondColLayoutProperty->UpdateSpan(V2::GridContainerSize(1));
    secondColLayoutProperty->UpdateOffset(V2::GridContainerSize(0));
    secondColLayoutProperty->UpdateOrder(V2::GridContainerSize());
    secondColLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(DEFAULT_HEIGHT)));

    /**
     * @tc.steps: step2. Running layout function and check the result with expected results.
     */
    auto layoutWrapper = CreateLayoutWrapperAndLayout(true);
    auto frameRect = layoutWrapper->GetOrCreateChildByIndex(0)->GetGeometryNode()->GetFrameRect();
    auto columnWidth = frameRect.Width();
    auto columnHeight = frameRect.Height();
    EXPECT_EQ(frameRect.GetX(), DEFAULT_GRID_ROW_WIDTH - DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(frameRect.GetY(), 0);
    EXPECT_EQ(columnWidth, DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(columnHeight, TEST_ALIGN_HEIGHT);

    frameRect = layoutWrapper->GetOrCreateChildByIndex(1)->GetGeometryNode()->GetFrameRect();
    columnWidth = frameRect.Width();
    columnHeight = frameRect.Height();
    EXPECT_EQ(frameRect.GetX(), 0);
    EXPECT_EQ(frameRect.GetY(), TEST_ALIGN_HEIGHT);
    EXPECT_EQ(columnWidth, DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(columnHeight, DEFAULT_HEIGHT);
}

/**
 * @tc.name: ItemAlign015
 * @tc.desc: Test GridRow layout algorithm with different offset and ItemAlign.STRETCH.
 * @tc.type: FUNC
 */
HWTEST_F(GridRowTestNg, ItemAlign015, TestSize.Level1)
{
    auto layoutProperty = rowNode_->GetLayoutProperty<GridRowLayoutProperty>();
    layoutProperty->UpdateAlignItems(FlexAlign::STRETCH);

    /**
     * @tc.steps: step1. create environment for running process.
     */
    auto firstColNode = colNodes_.front();
    auto firstColLayoutProperty = firstColNode->GetLayoutProperty<GridColLayoutProperty>();
    firstColLayoutProperty->UpdateSpan(V2::GridContainerSize(1));
    firstColLayoutProperty->UpdateOffset(V2::GridContainerSize(7));
    firstColLayoutProperty->UpdateOrder(V2::GridContainerSize());
    firstColLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(TEST_ALIGN_HEIGHT)));

    auto secondColNode = colNodes_.back();
    auto secondColLayoutProperty = secondColNode->GetLayoutProperty<GridColLayoutProperty>();
    secondColLayoutProperty->UpdateSpan(V2::GridContainerSize(1));
    secondColLayoutProperty->UpdateOffset(V2::GridContainerSize(0));
    secondColLayoutProperty->UpdateOrder(V2::GridContainerSize());
    secondColLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(DEFAULT_HEIGHT)));

    /**
     * @tc.steps: step2. Running layout function and check the result with expected results.
     */
    auto layoutWrapper = CreateLayoutWrapperAndLayout(true);
    auto frameRect = layoutWrapper->GetOrCreateChildByIndex(0)->GetGeometryNode()->GetFrameRect();
    auto columnWidth = frameRect.Width();
    auto columnHeight = frameRect.Height();
    EXPECT_EQ(frameRect.GetX(), DEFAULT_GRID_ROW_WIDTH - DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(frameRect.GetY(), 0);
    EXPECT_EQ(columnWidth, DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(columnHeight, TEST_ALIGN_HEIGHT);

    frameRect = layoutWrapper->GetOrCreateChildByIndex(1)->GetGeometryNode()->GetFrameRect();
    columnWidth = frameRect.Width();
    columnHeight = frameRect.Height();
    EXPECT_EQ(frameRect.GetX(), 0);
    EXPECT_EQ(frameRect.GetY(), TEST_ALIGN_HEIGHT);
    EXPECT_EQ(columnWidth, DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(columnHeight, DEFAULT_HEIGHT);
}
/**
 * @tc.name: ItemAlign016
 * @tc.desc: Test GridRow layout algorithm with diferent offset, direction and default ItemAlign
 * @tc.type: FUNC
 */
HWTEST_F(GridRowTestNg, ItemAlign016, TestSize.Level1)
{
    auto layoutProperty = rowNode_->GetLayoutProperty<GridRowLayoutProperty>();
    layoutProperty->ResetAlignItems();
    auto itemAlign = layoutProperty->GetAlignItems();
    layoutProperty->UpdateDirection(V2::GridRowDirection::RowReverse);
    EXPECT_FALSE(itemAlign.has_value());

    /**
     * @tc.steps: step1. create environment for running process.
     */
    auto firstColNode = colNodes_.front();
    auto firstColLayoutProperty = firstColNode->GetLayoutProperty<GridColLayoutProperty>();
    firstColLayoutProperty->UpdateSpan(V2::GridContainerSize(1));
    firstColLayoutProperty->UpdateOffset(V2::GridContainerSize(7));
    firstColLayoutProperty->UpdateOrder(V2::GridContainerSize());
    firstColLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(TEST_ALIGN_HEIGHT)));

    auto secondColNode = colNodes_.back();
    auto secondColLayoutProperty = secondColNode->GetLayoutProperty<GridColLayoutProperty>();
    secondColLayoutProperty->UpdateSpan(V2::GridContainerSize(1));
    secondColLayoutProperty->UpdateOffset(V2::GridContainerSize(0));
    secondColLayoutProperty->UpdateOrder(V2::GridContainerSize());
    secondColLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(DEFAULT_HEIGHT)));

    /**
     * @tc.steps: step2. Running layout function and check the result with expected results.
     */
    auto layoutWrapper = CreateLayoutWrapperAndLayout(true);
    auto frameRect = layoutWrapper->GetOrCreateChildByIndex(0)->GetGeometryNode()->GetFrameRect();
    auto columnWidth = frameRect.Width();
    auto columnHeight = frameRect.Height();
    EXPECT_EQ(frameRect.GetX(), 0);
    EXPECT_EQ(frameRect.GetY(), 0);
    EXPECT_EQ(columnWidth, DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(columnHeight, TEST_ALIGN_HEIGHT);

    frameRect = layoutWrapper->GetOrCreateChildByIndex(1)->GetGeometryNode()->GetFrameRect();
    columnWidth = frameRect.Width();
    columnHeight = frameRect.Height();
    EXPECT_EQ(frameRect.GetX(), DEFAULT_GRID_ROW_WIDTH - DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(frameRect.GetY(), TEST_ALIGN_HEIGHT);
    EXPECT_EQ(columnWidth, DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(columnHeight, DEFAULT_HEIGHT);
}

/**
 * @tc.name: ItemAlign017
 * @tc.desc: Test GridRow layout algorithm with different offset, direction and ItemAlign.Start.
 * @tc.type: FUNC
 */
HWTEST_F(GridRowTestNg, ItemAlign017, TestSize.Level1)
{
    auto layoutProperty = rowNode_->GetLayoutProperty<GridRowLayoutProperty>();
    layoutProperty->UpdateDirection(V2::GridRowDirection::RowReverse);
    layoutProperty->UpdateAlignItems(FlexAlign::FLEX_START);

    /**
     * @tc.steps: step1. create environment for running process.
     */
    auto firstColNode = colNodes_.front();
    auto firstColLayoutProperty = firstColNode->GetLayoutProperty<GridColLayoutProperty>();
    firstColLayoutProperty->UpdateSpan(V2::GridContainerSize(1));
    firstColLayoutProperty->UpdateOffset(V2::GridContainerSize(7));
    firstColLayoutProperty->UpdateOrder(V2::GridContainerSize());
    firstColLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(TEST_ALIGN_HEIGHT)));

    auto secondColNode = colNodes_.back();
    auto secondColLayoutProperty = secondColNode->GetLayoutProperty<GridColLayoutProperty>();
    secondColLayoutProperty->UpdateSpan(V2::GridContainerSize(1));
    secondColLayoutProperty->UpdateOffset(V2::GridContainerSize(0));
    secondColLayoutProperty->UpdateOrder(V2::GridContainerSize());
    secondColLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(DEFAULT_HEIGHT)));

    /**
     * @tc.steps: step2. Running layout function and check the result with expected results.
     */
    auto layoutWrapper = CreateLayoutWrapperAndLayout(true);
    auto frameRect = layoutWrapper->GetOrCreateChildByIndex(0)->GetGeometryNode()->GetFrameRect();
    auto columnWidth = frameRect.Width();
    auto columnHeight = frameRect.Height();
    EXPECT_EQ(frameRect.GetX(), 0);
    EXPECT_EQ(frameRect.GetY(), 0);
    EXPECT_EQ(columnWidth, DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(columnHeight, TEST_ALIGN_HEIGHT);

    frameRect = layoutWrapper->GetOrCreateChildByIndex(1)->GetGeometryNode()->GetFrameRect();
    columnWidth = frameRect.Width();
    columnHeight = frameRect.Height();
    EXPECT_EQ(frameRect.GetX(), DEFAULT_GRID_ROW_WIDTH - DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(frameRect.GetY(), TEST_ALIGN_HEIGHT);
    EXPECT_EQ(columnWidth, DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(columnHeight, DEFAULT_HEIGHT);
}

/**
 * @tc.name: ItemAlign018
 * @tc.desc: Test GridRow layout algorithm with different offset, direction and ItemAlign.Center.
 * @tc.type: FUNC
 */
HWTEST_F(GridRowTestNg, ItemAlign018, TestSize.Level1)
{
    auto layoutProperty = rowNode_->GetLayoutProperty<GridRowLayoutProperty>();
    layoutProperty->UpdateDirection(V2::GridRowDirection::RowReverse);
    layoutProperty->UpdateAlignItems(FlexAlign::CENTER);

    /**
     * @tc.steps: step1. create environment for running process.
     */
    auto firstColNode = colNodes_.front();
    auto firstColLayoutProperty = firstColNode->GetLayoutProperty<GridColLayoutProperty>();
    firstColLayoutProperty->UpdateSpan(V2::GridContainerSize(1));
    firstColLayoutProperty->UpdateOffset(V2::GridContainerSize(7));
    firstColLayoutProperty->UpdateOrder(V2::GridContainerSize());
    firstColLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(TEST_ALIGN_HEIGHT)));

    auto secondColNode = colNodes_.back();
    auto secondColLayoutProperty = secondColNode->GetLayoutProperty<GridColLayoutProperty>();
    secondColLayoutProperty->UpdateSpan(V2::GridContainerSize(1));
    secondColLayoutProperty->UpdateOffset(V2::GridContainerSize(0));
    secondColLayoutProperty->UpdateOrder(V2::GridContainerSize());
    secondColLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(DEFAULT_HEIGHT)));

    /**
     * @tc.steps: step2. Running layout function and check the result with expected results.
     */
    auto layoutWrapper = CreateLayoutWrapperAndLayout(true);
    auto frameRect = layoutWrapper->GetOrCreateChildByIndex(0)->GetGeometryNode()->GetFrameRect();
    auto columnWidth = frameRect.Width();
    auto columnHeight = frameRect.Height();
    EXPECT_EQ(frameRect.GetX(), 0);
    EXPECT_EQ(frameRect.GetY(), 0);
    EXPECT_EQ(columnWidth, DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(columnHeight, TEST_ALIGN_HEIGHT);

    frameRect = layoutWrapper->GetOrCreateChildByIndex(1)->GetGeometryNode()->GetFrameRect();
    columnWidth = frameRect.Width();
    columnHeight = frameRect.Height();
    EXPECT_EQ(frameRect.GetX(), DEFAULT_GRID_ROW_WIDTH - DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(frameRect.GetY(), TEST_ALIGN_HEIGHT);
    EXPECT_EQ(columnWidth, DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(columnHeight, DEFAULT_HEIGHT);
}

/**
 * @tc.name: ItemAlign019
 * @tc.desc: Test GridRow layout algorithm with different offset, direction and ItemAlign.End.
 * @tc.type: FUNC
 */
HWTEST_F(GridRowTestNg, ItemAlign019, TestSize.Level1)
{
    auto layoutProperty = rowNode_->GetLayoutProperty<GridRowLayoutProperty>();
    layoutProperty->UpdateDirection(V2::GridRowDirection::RowReverse);
    layoutProperty->UpdateAlignItems(FlexAlign::FLEX_END);

    /**
     * @tc.steps: step1. create environment for running process.
     */
    auto firstColNode = colNodes_.front();
    auto firstColLayoutProperty = firstColNode->GetLayoutProperty<GridColLayoutProperty>();
    firstColLayoutProperty->UpdateSpan(V2::GridContainerSize(1));
    firstColLayoutProperty->UpdateOffset(V2::GridContainerSize(7));
    firstColLayoutProperty->UpdateOrder(V2::GridContainerSize());
    firstColLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(TEST_ALIGN_HEIGHT)));

    auto secondColNode = colNodes_.back();
    auto secondColLayoutProperty = secondColNode->GetLayoutProperty<GridColLayoutProperty>();
    secondColLayoutProperty->UpdateSpan(V2::GridContainerSize(1));
    secondColLayoutProperty->UpdateOffset(V2::GridContainerSize(0));
    secondColLayoutProperty->UpdateOrder(V2::GridContainerSize());
    secondColLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(DEFAULT_HEIGHT)));

    /**
     * @tc.steps: step2. Running layout function and check the result with expected results.
     */
    auto layoutWrapper = CreateLayoutWrapperAndLayout(true);
    auto frameRect = layoutWrapper->GetOrCreateChildByIndex(0)->GetGeometryNode()->GetFrameRect();
    auto columnWidth = frameRect.Width();
    auto columnHeight = frameRect.Height();
    EXPECT_EQ(frameRect.GetX(), 0);
    EXPECT_EQ(frameRect.GetY(), 0);
    EXPECT_EQ(columnWidth, DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(columnHeight, TEST_ALIGN_HEIGHT);

    frameRect = layoutWrapper->GetOrCreateChildByIndex(1)->GetGeometryNode()->GetFrameRect();
    columnWidth = frameRect.Width();
    columnHeight = frameRect.Height();
    EXPECT_EQ(frameRect.GetX(), DEFAULT_GRID_ROW_WIDTH - DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(frameRect.GetY(), TEST_ALIGN_HEIGHT);
    EXPECT_EQ(columnWidth, DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(columnHeight, DEFAULT_HEIGHT);
}

/**
 * @tc.name: ItemAlign020
 * @tc.desc: Test GridRow layout algorithm with different offset, direction and ItemAlign.STRETCH.
 * @tc.type: FUNC
 */
HWTEST_F(GridRowTestNg, ItemAlign020, TestSize.Level1)
{
    auto layoutProperty = rowNode_->GetLayoutProperty<GridRowLayoutProperty>();
    layoutProperty->UpdateDirection(V2::GridRowDirection::RowReverse);
    layoutProperty->UpdateAlignItems(FlexAlign::STRETCH);

    /**
     * @tc.steps: step1. create environment for running process.
     */
    auto firstColNode = colNodes_.front();
    auto firstColLayoutProperty = firstColNode->GetLayoutProperty<GridColLayoutProperty>();
    firstColLayoutProperty->UpdateSpan(V2::GridContainerSize(1));
    firstColLayoutProperty->UpdateOffset(V2::GridContainerSize(7));
    firstColLayoutProperty->UpdateOrder(V2::GridContainerSize());
    firstColLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(TEST_ALIGN_HEIGHT)));

    auto secondColNode = colNodes_.back();
    auto secondColLayoutProperty = secondColNode->GetLayoutProperty<GridColLayoutProperty>();
    secondColLayoutProperty->UpdateSpan(V2::GridContainerSize(1));
    secondColLayoutProperty->UpdateOffset(V2::GridContainerSize(0));
    secondColLayoutProperty->UpdateOrder(V2::GridContainerSize());
    secondColLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(DEFAULT_HEIGHT)));

    /**
     * @tc.steps: step2. Running layout function and check the result with expected results.
     */
    auto layoutWrapper = CreateLayoutWrapperAndLayout(true);
    auto frameRect = layoutWrapper->GetOrCreateChildByIndex(0)->GetGeometryNode()->GetFrameRect();
    auto columnWidth = frameRect.Width();
    auto columnHeight = frameRect.Height();
    EXPECT_EQ(frameRect.GetX(), 0);
    EXPECT_EQ(frameRect.GetY(), 0);
    EXPECT_EQ(columnWidth, DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(columnHeight, TEST_ALIGN_HEIGHT);

    frameRect = layoutWrapper->GetOrCreateChildByIndex(1)->GetGeometryNode()->GetFrameRect();
    columnWidth = frameRect.Width();
    columnHeight = frameRect.Height();
    EXPECT_EQ(frameRect.GetX(), DEFAULT_GRID_ROW_WIDTH - DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(frameRect.GetY(), TEST_ALIGN_HEIGHT);
    EXPECT_EQ(columnWidth, DEFAULT_SPAN_WIDTH);
    EXPECT_EQ(columnHeight, DEFAULT_HEIGHT);
}

/**
 * @tc.name: Breakpoint
 * @tc.desc: Test GridRow layout algorithm with different breakpoint and
 *           trigerring event when breakpoint changes.
 * @tc.type: FUNC
 */
HWTEST_F(GridRowTestNg, Breakpoint, TestSize.Level1)
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

    auto eventHub = rowNode_->GetOrCreateEventHub<GridRowEventHub>();
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

/**
 * @tc.name: GridRowDefault001
 * @tc.desc: Test the default values of GridRow's properties.
 * @tc.type: FUNC
 */
HWTEST_F(GridRowTestNg, GridRowDefault001, TestSize.Level1)
{
    GridRowModelNG gridRowModelNG;
    gridRowModelNG.Create();
    gridRowModelNG.SetOnBreakPointChange([](const std::string& size) {});
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<GridRowLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    auto columns = layoutProperty->GetColumns();
    EXPECT_TRUE(columns.has_value());
    auto gutter = layoutProperty->GetGutter();
    EXPECT_TRUE(gutter.has_value());
    auto breakpoints = layoutProperty->GetBreakPoints();
    EXPECT_TRUE(breakpoints.has_value());
    auto direction = layoutProperty->GetDirection();
    EXPECT_TRUE(direction.has_value());

    constexpr int32_t testVal = 7;
    layoutProperty->UpdateColumns(V2::GridContainerSize(testVal));
    EXPECT_EQ(layoutProperty->GetColumnsValue().xs, testVal);
    layoutProperty->UpdateGutter(V2::Gutter(Dimension(testVal)));
    EXPECT_EQ(layoutProperty->GetGutterValue().yMd, Dimension(testVal));
    V2::BreakPoints breakpointsVal;
    breakpointsVal.breakpoints.assign({ "123vp" });
    layoutProperty->UpdateBreakPoints(breakpointsVal);
    EXPECT_EQ(layoutProperty->GetBreakPointsValue().breakpoints.front(), "123vp");
    layoutProperty->UpdateDirection(V2::GridRowDirection::RowReverse);
    EXPECT_EQ(layoutProperty->GetDirectionValue(), V2::GridRowDirection::RowReverse);

    // rubbish code for coverity
    auto clone = layoutProperty->Clone();
    clone.Reset();
    auto json = JsonUtil::Create(true);
    layoutProperty->ToJsonValue(json, filter);
}

/**
 * @tc.name: GridRowDefault002
 * @tc.desc: Test GridRow's properties.
 * @tc.type: FUNC
 */
HWTEST_F(GridRowTestNg, GridRowDefault002, TestSize.Level1)
{
    GridRowModelNG gridRowModelNG;

    auto colVal = Referenced::MakeRefPtr<V2::GridContainerSize>();
    auto gutterVal = Referenced::MakeRefPtr<V2::Gutter>();
    auto breakpointsVal = Referenced::MakeRefPtr<V2::BreakPoints>();
    auto directionVal = V2::GridRowDirection::Row;

    gridRowModelNG.Create(colVal, gutterVal, breakpointsVal, directionVal);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<GridRowLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    auto columns = layoutProperty->GetColumns();
    EXPECT_TRUE(columns.has_value());
    auto gutter = layoutProperty->GetGutter();
    EXPECT_TRUE(gutter.has_value());
    auto breakpoints = layoutProperty->GetBreakPoints();
    EXPECT_TRUE(breakpoints.has_value());
    auto direction = layoutProperty->GetDirection();
    EXPECT_TRUE(direction.has_value());
}

/**
 * @tc.name: GridColDefault001
 * @tc.desc: Test the default values of GridCol's properties.
 * @tc.type: FUNC
 */
HWTEST_F(GridRowTestNg, GridColDefault001, TestSize.Level1)
{
    GridColModelNG gridColModelNG;
    gridColModelNG.Create();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<GridColLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    auto span = layoutProperty->GetSpan();
    EXPECT_TRUE(span.has_value());
    auto offset = layoutProperty->GetOffset();
    EXPECT_TRUE(offset.has_value());
    auto order = layoutProperty->GetOrder();
    EXPECT_TRUE(order.has_value());

    constexpr int32_t testVal = 7;
    layoutProperty->UpdateSpan(V2::GridContainerSize(testVal));
    EXPECT_EQ(layoutProperty->GetSpanValue().xs, testVal);
    layoutProperty->UpdateOffset(V2::GridContainerSize(testVal));
    EXPECT_EQ(layoutProperty->GetOffsetValue().md, testVal);
    layoutProperty->UpdateOrder(V2::GridContainerSize(testVal));
    EXPECT_EQ(layoutProperty->GetOrderValue().lg, testVal);

    // rubbish code for coverity
    auto clone = layoutProperty->Clone();
    clone.Reset();
    auto json = JsonUtil::Create(true);
    layoutProperty->ToJsonValue(json, filter);
}

/**
 * @tc.name: GridColDefault002
 * @tc.desc: Test GridCol's properties.
 * @tc.type: FUNC
 */
HWTEST_F(GridRowTestNg, GridColDefault002, TestSize.Level1)
{
    GridColModelNG gridColModelNG;
    V2::GridContainerSize spanVal = V2::GridContainerSize(1);
    V2::GridContainerSize offsetVal = V2::GridContainerSize(0);
    V2::GridContainerSize orderVal = V2::GridContainerSize(0);
    gridColModelNG.Create(spanVal, offsetVal, orderVal);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    EXPECT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<GridColLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);

    auto span = layoutProperty->GetSpan();
    EXPECT_TRUE(span.has_value());
    auto offset = layoutProperty->GetOffset();
    EXPECT_TRUE(offset.has_value());
    auto order = layoutProperty->GetOrder();
    EXPECT_TRUE(order.has_value());
}
} // namespace OHOS::Ace::NG
