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
#include "test/unittest/core/pattern/grid_row/grid_row_base_test_ng.h"
#include "core/components_v2/grid_layout/grid_container_utils.h"

namespace OHOS::Ace::NG {
namespace {
    constexpr double DEFAULT_WIDTH = 240.0f;
    constexpr int32_t DEFAULT_COLUMNS = 12;
    constexpr double DEFAULT_SPAN_WIDTH = 20.0f;
    constexpr int32_t FOUR_COLUMNS_LEFT = 4;
    constexpr int32_t TEN_COLUMNS_LEFT = 10;
    constexpr double DEFAULT_CHILD_HEIGHT = 30.0f;
} // namespace
class GridrowCalcGridcolPosTestNg : public GridRowBaseTestNG {
public:
    string DumpChildrenInfo(std::list<ChildrenRow>& listOfChildren)
    {
        string result;
        for (auto &row : listOfChildren) {
            for (auto &child : row) {
                result += child.second.ToString();
            }
        }
        return result;
    }

    void CreateNewLineOffset(int32_t newLineCount, int32_t offset, int32_t span, float offsetY, NewLineOffset &result)
    {
        result.newLineCount = newLineCount;
        result.offset = offset;
        result.span = span;
        result.offsetY = offsetY;
    }
};

/**
 * @tc.name: CalculateOffsetOfNewlineTest01
 * @tc.desc: case01. restColumns = offset + currentChildSpan
 * @tc.type: FUNC
 */
HWTEST_F(GridrowCalcGridcolPosTestNg, CalculateOffsetOfNewlineTest01, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create GridRow and GridCol, the first line has ten columns left
     */
    auto gridRow = CreateGridRow([this](GridRowModelNG model) {
        ViewAbstract::SetWidth(CalcLength(DEFAULT_WIDTH));
        CreateGridCol([this](GridColModelNG model) {
            V2::GridContainerSize span(DEFAULT_COLUMNS - TEN_COLUMNS_LEFT);
            model.SetSpan(span);
            ViewAbstract::SetHeight(CalcLength(DEFAULT_CHILD_HEIGHT));
        });
        CreateGridCol([this](GridColModelNG model) {
            V2::GridContainerSize span(4);
            V2::GridContainerSize offset(6);
            model.SetSpan(span);
            model.SetOffset(offset);
            ViewAbstract::SetHeight(CalcLength(DEFAULT_CHILD_HEIGHT));
        });
    });
    ASSERT_NE(gridRow, nullptr);
    /**
     * @tc.steps: step2. Call GridRowLayoutAlgorithm.MeasureChildren
     */
    GridRowLayoutAlgorithm algorithm;
    auto gutter = std::make_pair<double, double>(0, 0);
    auto resultHeight = algorithm.MeasureChildren(Referenced::RawPtr(gridRow), 20.0f, 0, gutter,
        V2::GridSizeType::XS, 12);
    EXPECT_EQ(algorithm.gridColChildrenRows_.size(), 1) << algorithm.gridColChildrenRows_.size();
    EXPECT_EQ(resultHeight, DEFAULT_CHILD_HEIGHT) << resultHeight;
    /**
     * @tc.steps: step3. Check the NewlineOffset
     * @tc.expected: newlineCount = 0, offset = 2 + 6, childSpan = 4
     */
    NewLineOffset expectResult;
    CreateNewLineOffset(0, 0, 2, 0.0f, expectResult);
    auto expected = expectResult.ToString();
    CreateNewLineOffset(0, 8, 4, 0.0f, expectResult);
    expected += expectResult.ToString();
    auto result = DumpChildrenInfo(algorithm.gridColChildrenRows_);
    EXPECT_EQ(result, expected) << result;
}

/**
 * @tc.name: CalculateOffsetOfNewlineTest02
 * @tc.desc: case02. restColumns > offset + currentChildSpan
 * @tc.type: FUNC
 */
HWTEST_F(GridrowCalcGridcolPosTestNg, CalculateOffsetOfNewlineTest02, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create GridRow and GridCol, the first line has ten columns left
     */
    auto gridRow = CreateGridRow([this](GridRowModelNG model) {
        ViewAbstract::SetWidth(CalcLength(DEFAULT_WIDTH));
        CreateGridCol([this](GridColModelNG model) {
            V2::GridContainerSize span(DEFAULT_COLUMNS - TEN_COLUMNS_LEFT);
            model.SetSpan(span);
            ViewAbstract::SetHeight(CalcLength(DEFAULT_CHILD_HEIGHT));
        });
        CreateGridCol([this](GridColModelNG model) {
            V2::GridContainerSize span(1);
            V2::GridContainerSize offset(6);
            model.SetSpan(span);
            model.SetOffset(offset);
            ViewAbstract::SetHeight(CalcLength(DEFAULT_CHILD_HEIGHT));
        });
    });
    ASSERT_NE(gridRow, nullptr);
    /**
     * @tc.steps: step2. Call GridRowLayoutAlgorithm.MeasureChildren
     */
    GridRowLayoutAlgorithm algorithm;
    auto gutter = std::make_pair<double, double>(0, 0);
    auto resultHeight = algorithm.MeasureChildren(Referenced::RawPtr(gridRow), 20.0f, 0, gutter,
        V2::GridSizeType::XS, 12);
    EXPECT_EQ(algorithm.gridColChildrenRows_.size(), 1) << algorithm.gridColChildrenRows_.size();
    EXPECT_EQ(resultHeight, DEFAULT_CHILD_HEIGHT) << resultHeight;
    /**
     * @tc.steps: step3. Check the NewlineOffset
     * @tc.expected: newlineCount = 0, offset = 2 + 6, childSpan = 1
     */
    NewLineOffset expectResult;
    CreateNewLineOffset(0, 0, 2, 0.0f, expectResult);
    auto expected = expectResult.ToString();
    CreateNewLineOffset(0, 8, 1, 0.0f, expectResult);
    expected += expectResult.ToString();
    auto result = DumpChildrenInfo(algorithm.gridColChildrenRows_);
    EXPECT_EQ(result, expected) << result;
}

/**
 * @tc.name: CalculateOffsetOfNewlineTest03
 * @tc.desc: case03. restColumns < offset + currentChildSpan, restColumns == offset
 * @tc.type: FUNC
 */
HWTEST_F(GridrowCalcGridcolPosTestNg, CalculateOffsetOfNewlineTest03, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create GridRow and GridCol, the first line has ten columns left
     */
    auto gridRow = CreateGridRow([this](GridRowModelNG model) {
        ViewAbstract::SetWidth(CalcLength(DEFAULT_WIDTH));
        CreateGridCol([this](GridColModelNG model) {
            V2::GridContainerSize span(DEFAULT_COLUMNS - TEN_COLUMNS_LEFT);
            model.SetSpan(span);
            ViewAbstract::SetHeight(CalcLength(DEFAULT_CHILD_HEIGHT));
        });
        CreateGridCol([this](GridColModelNG model) {
            V2::GridContainerSize span(10);
            V2::GridContainerSize offset(10);
            model.SetSpan(span);
            model.SetOffset(offset);
            ViewAbstract::SetHeight(CalcLength(DEFAULT_CHILD_HEIGHT));
        });
    });
    ASSERT_NE(gridRow, nullptr);
    /**
     * @tc.steps: step2. Call GridRowLayoutAlgorithm.MeasureChildren
     */
    GridRowLayoutAlgorithm algorithm;
    auto gutter = std::make_pair<double, double>(0, 0);
    auto resultHeight = algorithm.MeasureChildren(Referenced::RawPtr(gridRow), 20.0f, 0, gutter,
        V2::GridSizeType::XS, 12);
    EXPECT_EQ(algorithm.gridColChildrenRows_.size(), 2) << algorithm.gridColChildrenRows_.size();
    EXPECT_EQ(resultHeight, DEFAULT_CHILD_HEIGHT * 2) << resultHeight;
    /**
     * @tc.steps: step3. Check the NewlineOffset
     * @tc.expected: newlineCount = 1, offset = 0, childSpan = 10
     */
    NewLineOffset expectResult;
    CreateNewLineOffset(0, 0, 2, 0.0f, expectResult);
    auto expected = expectResult.ToString();
    // The GridCol is placed at the second line
    CreateNewLineOffset(1, 0, 10, DEFAULT_CHILD_HEIGHT, expectResult);
    expected += expectResult.ToString();
    auto result = DumpChildrenInfo(algorithm.gridColChildrenRows_);
    EXPECT_EQ(result, expected) << result;
}

/**
 * @tc.name: CalculateOffsetOfNewlineTest04
 * @tc.desc: case04. restColumns < offset + currentChildSpan, restColumns > offset
 * @tc.type: FUNC
 */
HWTEST_F(GridrowCalcGridcolPosTestNg, CalculateOffsetOfNewlineTest04, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create GridRow and GridCol, the first line has ten columns left
     */
    auto gridRow = CreateGridRow([this](GridRowModelNG model) {
        ViewAbstract::SetWidth(CalcLength(DEFAULT_WIDTH));
        CreateGridCol([this](GridColModelNG model) {
            V2::GridContainerSize span(DEFAULT_COLUMNS - TEN_COLUMNS_LEFT);
            model.SetSpan(span);
            ViewAbstract::SetHeight(CalcLength(DEFAULT_CHILD_HEIGHT));
        });
        CreateGridCol([this](GridColModelNG model) {
            V2::GridContainerSize span(10);
            V2::GridContainerSize offset(5);
            model.SetSpan(span);
            model.SetOffset(offset);
            ViewAbstract::SetHeight(CalcLength(DEFAULT_CHILD_HEIGHT));
        });
    });
    ASSERT_NE(gridRow, nullptr);
    /**
     * @tc.steps: step2. Call GridRowLayoutAlgorithm.MeasureChildren
     */
    GridRowLayoutAlgorithm algorithm;
    auto gutter = std::make_pair<double, double>(0, 0);
    auto resultHeight = algorithm.MeasureChildren(Referenced::RawPtr(gridRow), 20.0f, 0, gutter,
        V2::GridSizeType::XS, 12);
    EXPECT_EQ(algorithm.gridColChildrenRows_.size(), 2) << algorithm.gridColChildrenRows_.size();
    EXPECT_EQ(resultHeight, DEFAULT_CHILD_HEIGHT * 2) << resultHeight;
    /**
     * @tc.steps: step3. Check the NewlineOffset
     * @tc.expected: newlineCount = 1, offset = 0, childSpan = 10
     */
    NewLineOffset expectResult;
    CreateNewLineOffset(0, 0, 2, 0.0f, expectResult);
    auto expected = expectResult.ToString();
    CreateNewLineOffset(1, 0, 10, DEFAULT_CHILD_HEIGHT, expectResult);
    expected += expectResult.ToString();
    auto result = DumpChildrenInfo(algorithm.gridColChildrenRows_);
    EXPECT_EQ(result, expected) << result;
}

/**
 * @tc.name: GetChildAlignmentTest01
 * @tc.desc: GridRow alignItems is FlexAlign::FLEX_START
 * @tc.type: FUNC
 */
HWTEST_F(GridrowCalcGridcolPosTestNg, GetChildAlignmentTest01, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create GridRow and GridCol
     */
    RefPtr<FrameNode> gridCol1, gridCol2, gridCol3, gridCol4, gridCol5, gridCol6;
    auto gridRow = CreateGridRow([this, &gridCol1, &gridCol2, &gridCol3, &gridCol4, &gridCol5, &gridCol6]
        (GridRowModelNG model) {
        model.SetAlignItems(FlexAlign::FLEX_START);
        gridCol1 = CreateGridCol([this](GridColModelNG model) {
            ViewAbstract::SetAlignSelf(FlexAlign::AUTO);
        });
        gridCol2 = CreateGridCol([this](GridColModelNG model) {
            ViewAbstract::SetAlignSelf(FlexAlign::FLEX_START);
        });
        gridCol3 = CreateGridCol([this](GridColModelNG model) {
            ViewAbstract::SetAlignSelf(FlexAlign::CENTER);
        });
        gridCol4 = CreateGridCol([this](GridColModelNG model) {
            ViewAbstract::SetAlignSelf(FlexAlign::FLEX_END);
        });
        gridCol5 = CreateGridCol([this](GridColModelNG model) {
            ViewAbstract::SetAlignSelf(FlexAlign::STRETCH);
        });
        gridCol6 = CreateGridCol([this](GridColModelNG model) {
        });
    });
    FlexAlign childAlign;
    GridRowLayoutAlgorithm algorithm;
    childAlign = algorithm.GetChildAlignment(Referenced::RawPtr(gridRow), gridCol1->GetLayoutProperty());
    EXPECT_EQ(childAlign, FlexAlign::FLEX_START);
    childAlign = algorithm.GetChildAlignment(Referenced::RawPtr(gridRow), gridCol2->GetLayoutProperty());
    EXPECT_EQ(childAlign, FlexAlign::FLEX_START);
    childAlign = algorithm.GetChildAlignment(Referenced::RawPtr(gridRow), gridCol3->GetLayoutProperty());
    EXPECT_EQ(childAlign, FlexAlign::CENTER);
    childAlign = algorithm.GetChildAlignment(Referenced::RawPtr(gridRow), gridCol4->GetLayoutProperty());
    EXPECT_EQ(childAlign, FlexAlign::FLEX_END);
    childAlign = algorithm.GetChildAlignment(Referenced::RawPtr(gridRow), gridCol5->GetLayoutProperty());
    EXPECT_EQ(childAlign, FlexAlign::STRETCH);
    childAlign = algorithm.GetChildAlignment(Referenced::RawPtr(gridRow), gridCol6->GetLayoutProperty());
    EXPECT_EQ(childAlign, FlexAlign::FLEX_START);
}

/**
 * @tc.name: GetChildAlignmentTest02
 * @tc.desc: GridRow alignItems is FlexAlign::CENTER
 * @tc.type: FUNC
 */
HWTEST_F(GridrowCalcGridcolPosTestNg, GetChildAlignmentTest02, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create GridRow and GridCol
     */
    RefPtr<FrameNode> gridCol1, gridCol2, gridCol3, gridCol4, gridCol5, gridCol6;
    auto gridRow = CreateGridRow([this, &gridCol1, &gridCol2, &gridCol3, &gridCol4, &gridCol5, &gridCol6]
        (GridRowModelNG model) {
        model.SetAlignItems(FlexAlign::CENTER);
        gridCol1 = CreateGridCol([this](GridColModelNG model) {
            ViewAbstract::SetAlignSelf(FlexAlign::AUTO);
        });
        gridCol2 = CreateGridCol([this](GridColModelNG model) {
            ViewAbstract::SetAlignSelf(FlexAlign::FLEX_START);
        });
        gridCol3 = CreateGridCol([this](GridColModelNG model) {
            ViewAbstract::SetAlignSelf(FlexAlign::CENTER);
        });
        gridCol4 = CreateGridCol([this](GridColModelNG model) {
            ViewAbstract::SetAlignSelf(FlexAlign::FLEX_END);
        });
        gridCol5 = CreateGridCol([this](GridColModelNG model) {
            ViewAbstract::SetAlignSelf(FlexAlign::STRETCH);
        });
        gridCol6 = CreateGridCol([this](GridColModelNG model) {
        });
    });
    FlexAlign childAlign;
    GridRowLayoutAlgorithm algorithm;
    childAlign = algorithm.GetChildAlignment(Referenced::RawPtr(gridRow), gridCol1->GetLayoutProperty());
    EXPECT_EQ(childAlign, FlexAlign::CENTER);
    childAlign = algorithm.GetChildAlignment(Referenced::RawPtr(gridRow), gridCol2->GetLayoutProperty());
    EXPECT_EQ(childAlign, FlexAlign::FLEX_START);
    childAlign = algorithm.GetChildAlignment(Referenced::RawPtr(gridRow), gridCol3->GetLayoutProperty());
    EXPECT_EQ(childAlign, FlexAlign::CENTER);
    childAlign = algorithm.GetChildAlignment(Referenced::RawPtr(gridRow), gridCol4->GetLayoutProperty());
    EXPECT_EQ(childAlign, FlexAlign::FLEX_END);
    childAlign = algorithm.GetChildAlignment(Referenced::RawPtr(gridRow), gridCol5->GetLayoutProperty());
    EXPECT_EQ(childAlign, FlexAlign::STRETCH);
    childAlign = algorithm.GetChildAlignment(Referenced::RawPtr(gridRow), gridCol6->GetLayoutProperty());
    EXPECT_EQ(childAlign, FlexAlign::CENTER);
}

/**
 * @tc.name: GetChildAlignmentTest03
 * @tc.desc: GridRow alignItems is FlexAlign::FLEX_END
 * @tc.type: FUNC
 */
HWTEST_F(GridrowCalcGridcolPosTestNg, GetChildAlignmentTest03, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create GridRow and GridCol
     */
    RefPtr<FrameNode> gridCol1, gridCol2, gridCol3, gridCol4, gridCol5, gridCol6;
    auto gridRow = CreateGridRow([this, &gridCol1, &gridCol2, &gridCol3, &gridCol4, &gridCol5, &gridCol6]
        (GridRowModelNG model) {
        model.SetAlignItems(FlexAlign::FLEX_END);
        gridCol1 = CreateGridCol([this](GridColModelNG model) {
            ViewAbstract::SetAlignSelf(FlexAlign::AUTO);
        });
        gridCol2 = CreateGridCol([this](GridColModelNG model) {
            ViewAbstract::SetAlignSelf(FlexAlign::FLEX_START);
        });
        gridCol3 = CreateGridCol([this](GridColModelNG model) {
            ViewAbstract::SetAlignSelf(FlexAlign::CENTER);
        });
        gridCol4 = CreateGridCol([this](GridColModelNG model) {
            ViewAbstract::SetAlignSelf(FlexAlign::FLEX_END);
        });
        gridCol5 = CreateGridCol([this](GridColModelNG model) {
            ViewAbstract::SetAlignSelf(FlexAlign::STRETCH);
        });
        gridCol6 = CreateGridCol([this](GridColModelNG model) {
        });
    });
    FlexAlign childAlign;
    GridRowLayoutAlgorithm algorithm;
    childAlign = algorithm.GetChildAlignment(Referenced::RawPtr(gridRow), gridCol1->GetLayoutProperty());
    EXPECT_EQ(childAlign, FlexAlign::FLEX_END);
    childAlign = algorithm.GetChildAlignment(Referenced::RawPtr(gridRow), gridCol2->GetLayoutProperty());
    EXPECT_EQ(childAlign, FlexAlign::FLEX_START);
    childAlign = algorithm.GetChildAlignment(Referenced::RawPtr(gridRow), gridCol3->GetLayoutProperty());
    EXPECT_EQ(childAlign, FlexAlign::CENTER);
    childAlign = algorithm.GetChildAlignment(Referenced::RawPtr(gridRow), gridCol4->GetLayoutProperty());
    EXPECT_EQ(childAlign, FlexAlign::FLEX_END);
    childAlign = algorithm.GetChildAlignment(Referenced::RawPtr(gridRow), gridCol5->GetLayoutProperty());
    EXPECT_EQ(childAlign, FlexAlign::STRETCH);
    childAlign = algorithm.GetChildAlignment(Referenced::RawPtr(gridRow), gridCol6->GetLayoutProperty());
    EXPECT_EQ(childAlign, FlexAlign::FLEX_END);
}

/**
 * @tc.name: GetChildAlignmentTest04
 * @tc.desc: GridRow alignItems is FlexAlign::STRETCH
 * @tc.type: FUNC
 */
HWTEST_F(GridrowCalcGridcolPosTestNg, GetChildAlignmentTest04, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create GridRow and GridCol
     */
    RefPtr<FrameNode> gridCol1, gridCol2, gridCol3, gridCol4, gridCol5, gridCol6;
    auto gridRow = CreateGridRow([this, &gridCol1, &gridCol2, &gridCol3, &gridCol4, &gridCol5, &gridCol6]
        (GridRowModelNG model) {
        model.SetAlignItems(FlexAlign::STRETCH);
        gridCol1 = CreateGridCol([this](GridColModelNG model) {
            ViewAbstract::SetAlignSelf(FlexAlign::AUTO);
        });
        gridCol2 = CreateGridCol([this](GridColModelNG model) {
            ViewAbstract::SetAlignSelf(FlexAlign::FLEX_START);
        });
        gridCol3 = CreateGridCol([this](GridColModelNG model) {
            ViewAbstract::SetAlignSelf(FlexAlign::CENTER);
        });
        gridCol4 = CreateGridCol([this](GridColModelNG model) {
            ViewAbstract::SetAlignSelf(FlexAlign::FLEX_END);
        });
        gridCol5 = CreateGridCol([this](GridColModelNG model) {
            ViewAbstract::SetAlignSelf(FlexAlign::STRETCH);
        });
        gridCol6 = CreateGridCol([this](GridColModelNG model) {
        });
    });
    FlexAlign childAlign;
    GridRowLayoutAlgorithm algorithm;
    childAlign = algorithm.GetChildAlignment(Referenced::RawPtr(gridRow), gridCol1->GetLayoutProperty());
    EXPECT_EQ(childAlign, FlexAlign::STRETCH);
    childAlign = algorithm.GetChildAlignment(Referenced::RawPtr(gridRow), gridCol2->GetLayoutProperty());
    EXPECT_EQ(childAlign, FlexAlign::FLEX_START);
    childAlign = algorithm.GetChildAlignment(Referenced::RawPtr(gridRow), gridCol3->GetLayoutProperty());
    EXPECT_EQ(childAlign, FlexAlign::CENTER);
    childAlign = algorithm.GetChildAlignment(Referenced::RawPtr(gridRow), gridCol4->GetLayoutProperty());
    EXPECT_EQ(childAlign, FlexAlign::FLEX_END);
    childAlign = algorithm.GetChildAlignment(Referenced::RawPtr(gridRow), gridCol5->GetLayoutProperty());
    EXPECT_EQ(childAlign, FlexAlign::STRETCH);
    childAlign = algorithm.GetChildAlignment(Referenced::RawPtr(gridRow), gridCol6->GetLayoutProperty());
    EXPECT_EQ(childAlign, FlexAlign::STRETCH);
}

/**
 * @tc.name: CalcCrossAxisAlignmentTest01
 * @tc.desc: GridRow alignItems is FlexAlign::STRETCH
 * @tc.type: FUNC
 */
HWTEST_F(GridrowCalcGridcolPosTestNg, CalcCrossAxisAlignmentTest01, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create GridRow and GridCol
     */
    RefPtr<FrameNode> gridCol1, gridCol2, gridCol3, gridCol4;
    auto gridRow = CreateGridRow([this, &gridCol1, &gridCol2, &gridCol3, &gridCol4](GridRowModelNG model) {
        ViewAbstract::SetWidth(CalcLength(DEFAULT_WIDTH));
        model.SetAlignItems(FlexAlign::STRETCH);
        gridCol1 = CreateGridCol([this](GridColModelNG model) {
            ViewAbstract::SetHeight(CalcLength(DEFAULT_CHILD_HEIGHT));
            ViewAbstract::SetAlignSelf(FlexAlign::AUTO);
        });
        gridCol2 = CreateGridCol([this](GridColModelNG model) {
            ViewAbstract::SetHeight(CalcLength(DEFAULT_CHILD_HEIGHT));
            ViewAbstract::SetAlignSelf(FlexAlign::STRETCH);
        });
        gridCol3 = CreateGridCol([this](GridColModelNG model) {
            ViewAbstract::SetHeight(CalcLength(DEFAULT_CHILD_HEIGHT));
            ViewAbstract::SetAlignSelf(FlexAlign::CENTER);
        });
        gridCol4 = CreateGridCol([this](GridColModelNG model) {
            ViewAbstract::SetHeight(CalcLength(DEFAULT_CHILD_HEIGHT * 3));
        });
    });
    /**
     * @tc.steps: step2. Call GridRowLayoutAlgorithm.MeasureChildren
     * @tc.expected: GridRow height is DEFAULT_CHILD_HEIGHT * 3
     */
    GridRowLayoutAlgorithm algorithm;
    algorithm.columnNum_ = DEFAULT_COLUMNS;
    algorithm.columnUnitWidth_ = DEFAULT_SPAN_WIDTH;
    auto gutter = std::make_pair<double, double>(0, 0);
    auto resultHeight = algorithm.MeasureChildren(Referenced::RawPtr(gridRow), 20.0f, 0, gutter,
        V2::GridSizeType::XS, 12);
    EXPECT_EQ(resultHeight, DEFAULT_CHILD_HEIGHT * 3) << resultHeight;
    auto result = DumpChildrenInfo(algorithm.gridColChildrenRows_);
    /**
     * @tc.steps: step3. Check the NewlineOffset
     * @tc.expected: GridCols have correct NewlineOffset.offsetY and measured size.
     */
    std::string expected;
    NewLineOffset expectResult;
    CreateNewLineOffset(0, 0, 1, 0, expectResult);
    expected += expectResult.ToString();
    CreateNewLineOffset(0, 1, 1, 0, expectResult);
    expected += expectResult.ToString();
    // offsetY = 0.5 * (3 - 1) * DEFAULT_CHILD_HEIGHT
    CreateNewLineOffset(0, 2, 1, DEFAULT_CHILD_HEIGHT, expectResult);
    expected += expectResult.ToString();
    CreateNewLineOffset(0, 3, 1, 0, expectResult);
    expected += expectResult.ToString();
    EXPECT_EQ(result, expected) << result;
    EXPECT_EQ(gridCol1->GetGeometryNode()->GetFrameSize(), SizeF(DEFAULT_SPAN_WIDTH, DEFAULT_CHILD_HEIGHT * 3))
        << gridCol1->GetGeometryNode()->GetFrameSize().ToString();
    EXPECT_EQ(gridCol2->GetGeometryNode()->GetFrameSize(), SizeF(DEFAULT_SPAN_WIDTH, DEFAULT_CHILD_HEIGHT * 3))
        << gridCol2->GetGeometryNode()->GetFrameSize().ToString();
    EXPECT_EQ(gridCol3->GetGeometryNode()->GetFrameSize(), SizeF(DEFAULT_SPAN_WIDTH, DEFAULT_CHILD_HEIGHT))
        << gridCol3->GetGeometryNode()->GetFrameSize().ToString();
    EXPECT_EQ(gridCol4->GetGeometryNode()->GetFrameSize(), SizeF(DEFAULT_SPAN_WIDTH, DEFAULT_CHILD_HEIGHT * 3))
        << gridCol4->GetGeometryNode()->GetFrameSize().ToString();
}

/**
 * @tc.name: CalcCrossAxisAlignmentTest02
 * @tc.desc: GridRow alignItems is FlexAlign::STRETCH
 * @tc.type: FUNC
 */
HWTEST_F(GridrowCalcGridcolPosTestNg, CalcCrossAxisAlignmentTest02, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create GridRow and GridCol
     */
    RefPtr<FrameNode> gridCol1, gridCol2, gridCol3;
    auto gridRow = CreateGridRow([this, &gridCol1, &gridCol2, &gridCol3](GridRowModelNG model) {
        ViewAbstract::SetWidth(CalcLength(DEFAULT_WIDTH));
        model.SetAlignItems(FlexAlign::STRETCH);
        gridCol1 = CreateGridCol([this](GridColModelNG model) {
            ViewAbstract::SetHeight(CalcLength(DEFAULT_CHILD_HEIGHT));
            ViewAbstract::SetAlignSelf(FlexAlign::AUTO);
        });
        gridCol2 = CreateGridCol([this](GridColModelNG model) {
            ViewAbstract::SetHeight(CalcLength(DEFAULT_CHILD_HEIGHT));
            ViewAbstract::SetAlignSelf(FlexAlign::FLEX_END);
        });
        gridCol3 = CreateGridCol([this](GridColModelNG model) {
            ViewAbstract::SetHeight(CalcLength(DEFAULT_CHILD_HEIGHT * 3));
        });
    });
    /**
     * @tc.steps: step2. Call GridRowLayoutAlgorithm.MeasureChildren
     * @tc.expected: GridRow height is DEFAULT_CHILD_HEIGHT * 3
     */
    GridRowLayoutAlgorithm algorithm;
    algorithm.columnNum_ = DEFAULT_COLUMNS;
    algorithm.columnUnitWidth_ = DEFAULT_SPAN_WIDTH;
    auto gutter = std::make_pair<double, double>(0, 0);
    auto resultHeight = algorithm.MeasureChildren(Referenced::RawPtr(gridRow), 20.0f, 0, gutter,
        V2::GridSizeType::XS, 12);
    EXPECT_EQ(resultHeight, DEFAULT_CHILD_HEIGHT * 3) << resultHeight;
    auto result = DumpChildrenInfo(algorithm.gridColChildrenRows_);
    /**
     * @tc.steps: step3. Check the NewlineOffset
     * @tc.expected: GridCols have correct NewlineOffset.offsetY and measured size.
     */
    std::string expected;
    NewLineOffset expectResult;
    CreateNewLineOffset(0, 0, 1, 0, expectResult);
    expected += expectResult.ToString();
    // offsetY = (3 - 1) * DEFAULT_CHILD_HEIGHT
    CreateNewLineOffset(0, 1, 1, DEFAULT_CHILD_HEIGHT * 2, expectResult);
    expected += expectResult.ToString();
    CreateNewLineOffset(0, 2, 1, 0, expectResult);
    expected += expectResult.ToString();
    EXPECT_EQ(result, expected) << result;
    EXPECT_EQ(gridCol1->GetGeometryNode()->GetFrameSize(), SizeF(DEFAULT_SPAN_WIDTH, DEFAULT_CHILD_HEIGHT * 3))
        << gridCol1->GetGeometryNode()->GetFrameSize().ToString();
    EXPECT_EQ(gridCol2->GetGeometryNode()->GetFrameSize(), SizeF(DEFAULT_SPAN_WIDTH, DEFAULT_CHILD_HEIGHT))
        << gridCol2->GetGeometryNode()->GetFrameSize().ToString();
    EXPECT_EQ(gridCol3->GetGeometryNode()->GetFrameSize(), SizeF(DEFAULT_SPAN_WIDTH, DEFAULT_CHILD_HEIGHT * 3))
        << gridCol3->GetGeometryNode()->GetFrameSize().ToString();
}

/**
 * @tc.name: CalcCrossAxisAlignmentTest03
 * @tc.desc: GridRow alignItems is FlexAlign::CENTER
 * @tc.type: FUNC
 */
HWTEST_F(GridrowCalcGridcolPosTestNg, CalcCrossAxisAlignmentTest03, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create GridRow and GridCol
     */
    RefPtr<FrameNode> gridCol1, gridCol2, gridCol3, gridCol4;
    auto gridRow = CreateGridRow([this, &gridCol1, &gridCol2, &gridCol3, &gridCol4](GridRowModelNG model) {
        ViewAbstract::SetWidth(CalcLength(DEFAULT_WIDTH));
        model.SetAlignItems(FlexAlign::CENTER);
        gridCol1 = CreateGridCol([this](GridColModelNG model) {
            ViewAbstract::SetHeight(CalcLength(DEFAULT_CHILD_HEIGHT));
            ViewAbstract::SetAlignSelf(FlexAlign::AUTO);
        });
        gridCol2 = CreateGridCol([this](GridColModelNG model) {
            ViewAbstract::SetHeight(CalcLength(DEFAULT_CHILD_HEIGHT));
            ViewAbstract::SetAlignSelf(FlexAlign::STRETCH);
        });
        gridCol3 = CreateGridCol([this](GridColModelNG model) {
            ViewAbstract::SetHeight(CalcLength(DEFAULT_CHILD_HEIGHT));
            ViewAbstract::SetAlignSelf(FlexAlign::CENTER);
        });
        gridCol4 = CreateGridCol([this](GridColModelNG model) {
            ViewAbstract::SetHeight(CalcLength(DEFAULT_CHILD_HEIGHT * 3));
        });
    });
    /**
     * @tc.steps: step2. Call GridRowLayoutAlgorithm.MeasureChildren
     * @tc.expected: GridRow height is DEFAULT_CHILD_HEIGHT * 3
     */
    GridRowLayoutAlgorithm algorithm;
    algorithm.columnNum_ = DEFAULT_COLUMNS;
    algorithm.columnUnitWidth_ = DEFAULT_SPAN_WIDTH;
    auto gutter = std::make_pair<double, double>(0, 0);
    auto resultHeight = algorithm.MeasureChildren(Referenced::RawPtr(gridRow), 20.0f, 0, gutter,
        V2::GridSizeType::XS, 12);
    EXPECT_EQ(resultHeight, DEFAULT_CHILD_HEIGHT * 3) << resultHeight;
    /**
     * @tc.steps: step3. Check the NewlineOffset
     * @tc.expected: GridCols have correct NewlineOffset.offsetY and measured size.
     */
    auto result = DumpChildrenInfo(algorithm.gridColChildrenRows_);
    std::string expected;
    NewLineOffset expectResult;
    CreateNewLineOffset(0, 0, 1, DEFAULT_CHILD_HEIGHT, expectResult);
    expected += expectResult.ToString();
    CreateNewLineOffset(0, 1, 1, 0, expectResult);
    expected += expectResult.ToString();
    CreateNewLineOffset(0, 2, 1, DEFAULT_CHILD_HEIGHT, expectResult);
    expected += expectResult.ToString();
    CreateNewLineOffset(0, 3, 1, 0, expectResult);
    expected += expectResult.ToString();
    EXPECT_EQ(result, expected) << result;
    EXPECT_EQ(gridCol1->GetGeometryNode()->GetFrameSize(), SizeF(DEFAULT_SPAN_WIDTH, DEFAULT_CHILD_HEIGHT))
        << gridCol1->GetGeometryNode()->GetFrameSize().ToString();
    EXPECT_EQ(gridCol2->GetGeometryNode()->GetFrameSize(), SizeF(DEFAULT_SPAN_WIDTH, DEFAULT_CHILD_HEIGHT * 3))
        << gridCol2->GetGeometryNode()->GetFrameSize().ToString();
    EXPECT_EQ(gridCol3->GetGeometryNode()->GetFrameSize(), SizeF(DEFAULT_SPAN_WIDTH, DEFAULT_CHILD_HEIGHT))
        << gridCol3->GetGeometryNode()->GetFrameSize().ToString();
    EXPECT_EQ(gridCol4->GetGeometryNode()->GetFrameSize(), SizeF(DEFAULT_SPAN_WIDTH, DEFAULT_CHILD_HEIGHT * 3))
        << gridCol4->GetGeometryNode()->GetFrameSize().ToString();
}

/**
 * @tc.name: CalcCrossAxisAlignmentTest04
 * @tc.desc: GridRow alignItems is FlexAlign::CENTER
 * @tc.type: FUNC
 */
HWTEST_F(GridrowCalcGridcolPosTestNg, CalcCrossAxisAlignmentTest04, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create GridRow and GridCol
     */
    RefPtr<FrameNode> gridCol1, gridCol2, gridCol3;
    auto gridRow = CreateGridRow([this, &gridCol1, &gridCol2, &gridCol3](GridRowModelNG model) {
        ViewAbstract::SetWidth(CalcLength(DEFAULT_WIDTH));
        model.SetAlignItems(FlexAlign::CENTER);
        gridCol1 = CreateGridCol([this](GridColModelNG model) {
            ViewAbstract::SetHeight(CalcLength(DEFAULT_CHILD_HEIGHT));
            ViewAbstract::SetAlignSelf(FlexAlign::AUTO);
        });
        gridCol2 = CreateGridCol([this](GridColModelNG model) {
            ViewAbstract::SetHeight(CalcLength(DEFAULT_CHILD_HEIGHT));
            ViewAbstract::SetAlignSelf(FlexAlign::FLEX_END);
        });
        gridCol3 = CreateGridCol([this](GridColModelNG model) {
            ViewAbstract::SetHeight(CalcLength(DEFAULT_CHILD_HEIGHT * 3));
        });
    });
    /**
     * @tc.steps: step2. Call GridRowLayoutAlgorithm.MeasureChildren
     * @tc.expected: GridRow height is DEFAULT_CHILD_HEIGHT * 3
     */
    GridRowLayoutAlgorithm algorithm;
    algorithm.columnNum_ = DEFAULT_COLUMNS;
    algorithm.columnUnitWidth_ = DEFAULT_SPAN_WIDTH;
    auto gutter = std::make_pair<double, double>(0, 0);
    auto resultHeight = algorithm.MeasureChildren(Referenced::RawPtr(gridRow), 20.0f, 0, gutter,
        V2::GridSizeType::XS, 12);
    EXPECT_EQ(resultHeight, DEFAULT_CHILD_HEIGHT * 3) << resultHeight;
    /**
     * @tc.steps: step3. Check the NewlineOffset
     * @tc.expected: GridCols have correct NewlineOffset.offsetY and measured size.
     */
    auto result = DumpChildrenInfo(algorithm.gridColChildrenRows_);
    std::string expected;
    NewLineOffset expectResult;
    CreateNewLineOffset(0, 0, 1, DEFAULT_CHILD_HEIGHT, expectResult);
    expected += expectResult.ToString();
    CreateNewLineOffset(0, 1, 1, DEFAULT_CHILD_HEIGHT * 2, expectResult);
    expected += expectResult.ToString();
    CreateNewLineOffset(0, 2, 1, 0, expectResult);
    expected += expectResult.ToString();
    EXPECT_EQ(result, expected) << result;
    EXPECT_EQ(gridCol1->GetGeometryNode()->GetFrameSize(), SizeF(DEFAULT_SPAN_WIDTH, DEFAULT_CHILD_HEIGHT))
        << gridCol1->GetGeometryNode()->GetFrameSize().ToString();
    EXPECT_EQ(gridCol2->GetGeometryNode()->GetFrameSize(), SizeF(DEFAULT_SPAN_WIDTH, DEFAULT_CHILD_HEIGHT))
        << gridCol2->GetGeometryNode()->GetFrameSize().ToString();
    EXPECT_EQ(gridCol3->GetGeometryNode()->GetFrameSize(), SizeF(DEFAULT_SPAN_WIDTH, DEFAULT_CHILD_HEIGHT * 3))
        << gridCol3->GetGeometryNode()->GetFrameSize().ToString();
}

/**
 * @tc.name: CalcCrossAxisAlignmentTest05
 * @tc.desc: GridRow alignItems is FlexAlign::FLEX_END
 * @tc.type: FUNC
 */
HWTEST_F(GridrowCalcGridcolPosTestNg, CalcCrossAxisAlignmentTest05, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create GridRow and GridCol
     */
    RefPtr<FrameNode> gridCol1, gridCol2, gridCol3, gridCol4;
    auto gridRow = CreateGridRow([this, &gridCol1, &gridCol2, &gridCol3, &gridCol4](GridRowModelNG model) {
        // step: Set GridRow attribute
        ViewAbstract::SetWidth(CalcLength(DEFAULT_WIDTH));
        model.SetAlignItems(FlexAlign::FLEX_END);
        gridCol1 = CreateGridCol([this](GridColModelNG model) {
            ViewAbstract::SetHeight(CalcLength(DEFAULT_CHILD_HEIGHT));
            ViewAbstract::SetAlignSelf(FlexAlign::AUTO);
        });
        gridCol2 = CreateGridCol([this](GridColModelNG model) {
            ViewAbstract::SetHeight(CalcLength(DEFAULT_CHILD_HEIGHT));
            ViewAbstract::SetAlignSelf(FlexAlign::STRETCH);
        });
        gridCol3 = CreateGridCol([this](GridColModelNG model) {
            ViewAbstract::SetHeight(CalcLength(DEFAULT_CHILD_HEIGHT));
            ViewAbstract::SetAlignSelf(FlexAlign::CENTER);
        });
        gridCol4 = CreateGridCol([this](GridColModelNG model) {
            ViewAbstract::SetHeight(CalcLength(DEFAULT_CHILD_HEIGHT * 3));
        });
    });
    /**
     * @tc.steps: step2. Call GridRowLayoutAlgorithm.MeasureChildren
     * @tc.expected: GridRow height is DEFAULT_CHILD_HEIGHT * 3
     */
    GridRowLayoutAlgorithm algorithm;
    algorithm.columnNum_ = DEFAULT_COLUMNS;
    algorithm.columnUnitWidth_ = DEFAULT_SPAN_WIDTH;
    auto gutter = std::make_pair<double, double>(0, 0);
    auto resultHeight = algorithm.MeasureChildren(Referenced::RawPtr(gridRow), 20.0f, 0, gutter,
        V2::GridSizeType::XS, 12);
    EXPECT_EQ(resultHeight, DEFAULT_CHILD_HEIGHT * 3) << resultHeight;
    /**
     * @tc.steps: step3. Check the NewlineOffset
     * @tc.expected: GridCols have correct NewlineOffset.offsetY and measured size.
     */
    auto result = DumpChildrenInfo(algorithm.gridColChildrenRows_);
    std::string expected;
    NewLineOffset expectResult;
    CreateNewLineOffset(0, 0, 1, DEFAULT_CHILD_HEIGHT * 2, expectResult);
    expected += expectResult.ToString();
    CreateNewLineOffset(0, 1, 1, 0, expectResult);
    expected += expectResult.ToString();
    CreateNewLineOffset(0, 2, 1, DEFAULT_CHILD_HEIGHT, expectResult);
    expected += expectResult.ToString();
    CreateNewLineOffset(0, 3, 1, 0, expectResult);
    expected += expectResult.ToString();
    EXPECT_EQ(result, expected) << result;
    EXPECT_EQ(gridCol1->GetGeometryNode()->GetFrameSize(), SizeF(DEFAULT_SPAN_WIDTH, DEFAULT_CHILD_HEIGHT))
        << gridCol1->GetGeometryNode()->GetFrameSize().ToString();
    EXPECT_EQ(gridCol2->GetGeometryNode()->GetFrameSize(), SizeF(DEFAULT_SPAN_WIDTH, DEFAULT_CHILD_HEIGHT * 3))
        << gridCol2->GetGeometryNode()->GetFrameSize().ToString();
    EXPECT_EQ(gridCol3->GetGeometryNode()->GetFrameSize(), SizeF(DEFAULT_SPAN_WIDTH, DEFAULT_CHILD_HEIGHT))
        << gridCol3->GetGeometryNode()->GetFrameSize().ToString();
    EXPECT_EQ(gridCol4->GetGeometryNode()->GetFrameSize(), SizeF(DEFAULT_SPAN_WIDTH, DEFAULT_CHILD_HEIGHT * 3))
        << gridCol4->GetGeometryNode()->GetFrameSize().ToString();
}

/**
 * @tc.name: CalcCrossAxisAlignmentTest06
 * @tc.desc: GridRow alignItems is FlexAlign::FLEX_END
 * @tc.type: FUNC
 */
HWTEST_F(GridrowCalcGridcolPosTestNg, CalcCrossAxisAlignmentTest06, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create GridRow and GridCol
     */
    RefPtr<FrameNode> gridCol1, gridCol2, gridCol3;
    auto gridRow = CreateGridRow([this, &gridCol1, &gridCol2, &gridCol3](GridRowModelNG model) {
        // step: Set GridRow attribute
        ViewAbstract::SetWidth(CalcLength(DEFAULT_WIDTH));
        model.SetAlignItems(FlexAlign::FLEX_END);
        gridCol1 = CreateGridCol([this](GridColModelNG model) {
            ViewAbstract::SetHeight(CalcLength(DEFAULT_CHILD_HEIGHT));
            ViewAbstract::SetAlignSelf(FlexAlign::AUTO);
        });
        gridCol2 = CreateGridCol([this](GridColModelNG model) {
            ViewAbstract::SetHeight(CalcLength(DEFAULT_CHILD_HEIGHT));
            ViewAbstract::SetAlignSelf(FlexAlign::FLEX_END);
        });
        gridCol3 = CreateGridCol([this](GridColModelNG model) {
            ViewAbstract::SetHeight(CalcLength(DEFAULT_CHILD_HEIGHT * 3));
        });
    });
    /**
     * @tc.steps: step2. Call GridRowLayoutAlgorithm.MeasureChildren
     * @tc.expected: GridRow height is DEFAULT_CHILD_HEIGHT * 3
     */
    GridRowLayoutAlgorithm algorithm;
    algorithm.columnNum_ = DEFAULT_COLUMNS;
    algorithm.columnUnitWidth_ = DEFAULT_SPAN_WIDTH;
    auto gutter = std::make_pair<double, double>(0, 0);
    auto resultHeight = algorithm.MeasureChildren(Referenced::RawPtr(gridRow), 20.0f, 0, gutter,
        V2::GridSizeType::XS, 12);
    EXPECT_EQ(resultHeight, DEFAULT_CHILD_HEIGHT * 3) << resultHeight;
    /**
     * @tc.steps: step3. Check the NewlineOffset
     * @tc.expected: GridCols have correct NewlineOffset.offsetY and measured size.
     */
    auto result = DumpChildrenInfo(algorithm.gridColChildrenRows_);
    std::string expected;
    NewLineOffset expectResult;
    CreateNewLineOffset(0, 0, 1, DEFAULT_CHILD_HEIGHT * 2, expectResult);
    expected += expectResult.ToString();
    CreateNewLineOffset(0, 1, 1, DEFAULT_CHILD_HEIGHT * 2, expectResult);
    expected += expectResult.ToString();
    CreateNewLineOffset(0, 2, 1, 0, expectResult);
    expected += expectResult.ToString();
    EXPECT_EQ(result, expected) << result;
    EXPECT_EQ(gridCol1->GetGeometryNode()->GetFrameSize(), SizeF(DEFAULT_SPAN_WIDTH, DEFAULT_CHILD_HEIGHT))
        << gridCol1->GetGeometryNode()->GetFrameSize().ToString();
    EXPECT_EQ(gridCol2->GetGeometryNode()->GetFrameSize(), SizeF(DEFAULT_SPAN_WIDTH, DEFAULT_CHILD_HEIGHT))
        << gridCol2->GetGeometryNode()->GetFrameSize().ToString();
    EXPECT_EQ(gridCol3->GetGeometryNode()->GetFrameSize(), SizeF(DEFAULT_SPAN_WIDTH, DEFAULT_CHILD_HEIGHT * 3))
        << gridCol3->GetGeometryNode()->GetFrameSize().ToString();
}

/**
 * @tc.name: CalcCrossAxisOffsetTest
 * @tc.desc: Test CalcCrossAxisOffset()
 * @tc.type: FUNC
 */
HWTEST_F(GridrowCalcGridcolPosTestNg, CalcCrossAxisOffsetTest, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create GridRow and GridCol
     */
    auto gridRow = CreateGridRow([this] (GridRowModelNG model) {
        model.SetAlignItems(FlexAlign::STRETCH);
        CreateGridCol([this](GridColModelNG model) {
            ViewAbstract::SetAlignSelf(FlexAlign::AUTO);
            ViewAbstract::SetMargin(CalcLength(10));
        });
    });
    GridRowLayoutAlgorithm algorithm;
    auto gridCol1 = *(gridRow->GetAllChildrenWithBuild().begin());
    gridCol1->GetGeometryNode()->SetFrameSize(SizeF(30.0f, 30.0f));
    gridCol1->GetGeometryNode()->UpdateMargin(gridCol1->GetLayoutProperty()->CreateMargin());
    ASSERT_NE(gridCol1, nullptr);
    float extraOffset = 0.0f;
    /**
     * @tc.expected: extraOffset = (90 - 10 * 2 - 30) / 2 = 20
     */
    extraOffset = algorithm.CalcCrossAxisOffset(Referenced::RawPtr(gridRow), gridCol1, FlexAlign::CENTER, 90.0f);
    EXPECT_EQ(extraOffset, 20.0f) << extraOffset;
    /**
     * @tc.expected: extraOffset = 0
     */
    extraOffset = algorithm.CalcCrossAxisOffset(Referenced::RawPtr(gridRow), gridCol1, FlexAlign::FLEX_START, 90.0f);
    EXPECT_EQ(extraOffset, 0.0f) << extraOffset;
    /**
     * @tc.expected: extraOffset = 90 - 10 * 2 - 30 = 40
     */
    extraOffset = algorithm.CalcCrossAxisOffset(Referenced::RawPtr(gridRow), gridCol1, FlexAlign::FLEX_END, 90.0f);
    EXPECT_EQ(extraOffset, 40.0f) << extraOffset;
    /**
     * @tc.expected: extraOffset = 0
     */
    extraOffset = algorithm.CalcCrossAxisOffset(Referenced::RawPtr(gridRow), gridCol1, FlexAlign::STRETCH, 90.0f);
    EXPECT_EQ(extraOffset, 0.0f) << extraOffset;
    EXPECT_EQ(gridCol1->GetGeometryNode()->GetMarginFrameSize(), SizeF(30.0f, 90.0f))
        << gridCol1->GetGeometryNode()->GetMarginFrameSize().ToString();
}

/**
 * @tc.name: InsertIntoGridRowTableTest
 * @tc.desc: Test InsertIntoGridRowTable function
 * @tc.type: FUNC
 */
HWTEST_F(GridrowCalcGridcolPosTestNg, InsertIntoGridRowTableTest, TestSize.Level0)
{
    int32_t currentPosition = 0;
    GridRowLayoutAlgorithm algorithm;
    NewLineOffset newLineOffset;
    algorithm.columnNum_ = 12;
    algorithm.InsertIntoGridRowTable(CreateGridColWithProperty(2, 0),
        V2::GridSizeType::XS, currentPosition, newLineOffset);
    EXPECT_EQ(currentPosition, 2);
    algorithm.InsertIntoGridRowTable(CreateGridColWithProperty(4, 2),
        V2::GridSizeType::XS, currentPosition, newLineOffset);
    EXPECT_EQ(currentPosition, 8);
    algorithm.InsertIntoGridRowTable(CreateGridColWithProperty(6, 26),
        V2::GridSizeType::XS, currentPosition, newLineOffset);
    /**
     * @tc.expected: newLineOffset.newLineCount = (26 - 4) / 12 + 1 = 2, offset =  (26 - 4) % 12 = 10, childSpan = 6
            but offset + childSpan > 12, so newLineCount = 3
            currentPosition = 6
     */
    EXPECT_EQ(currentPosition, 6);
    EXPECT_EQ(newLineOffset.newLineCount, 3);
    EXPECT_EQ(algorithm.gridColChildrenRows_.size(), 1);
    /**
     * @tc.expected: prevLineCount = 0, the child number of last line is 2
     */
    EXPECT_EQ(algorithm.gridColChildrenRows_.back().size(), 2);
    EXPECT_EQ(algorithm.gridColChildrenOfOneRow_.size(), 1);
    algorithm.InsertIntoGridRowTable(CreateGridColWithProperty(6, 20),
        V2::GridSizeType::XS, currentPosition, newLineOffset);
    EXPECT_EQ(currentPosition, 8);
    EXPECT_EQ(newLineOffset.newLineCount, 2);
    EXPECT_EQ(algorithm.gridColChildrenRows_.size(), 2);
    EXPECT_EQ(algorithm.gridColChildrenRows_.back().size(), 1);
    EXPECT_EQ(algorithm.gridColChildrenOfOneRow_.size(), 1);
}

/**
 * @tc.name: ParseNewLineForLargeOffsetTest01
 * @tc.desc: restColumns = 4, gridCol.offset = 26, gridCol.span = 6
 * @tc.type: FUNC
 */
HWTEST_F(GridrowCalcGridcolPosTestNg, ParseNewLineForLargeOffsetTest01, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create GridRow and GridCol, the first line has four columns left
     */
    auto gridRow = CreateGridRow([this](GridRowModelNG model) {
        ViewAbstract::SetWidth(CalcLength(DEFAULT_WIDTH));
        CreateGridCol([this](GridColModelNG model) {
            V2::GridContainerSize span(DEFAULT_COLUMNS - FOUR_COLUMNS_LEFT);
            model.SetSpan(span);
            ViewAbstract::SetHeight(CalcLength(DEFAULT_CHILD_HEIGHT * 2));
        });
        CreateGridCol([this](GridColModelNG model) {
            V2::GridContainerSize span(6);
            V2::GridContainerSize offset(26);
            model.SetSpan(span);
            model.SetOffset(offset);
            ViewAbstract::SetHeight(CalcLength(DEFAULT_CHILD_HEIGHT));
        });
    });
    ASSERT_NE(gridRow, nullptr);
    /**
     * @tc.steps: step2. Call GridRowLayoutAlgorithm.MeasureChildren
     * @tc.expected: GridRow height = DEFAULT_CHILD_HEIGHT * 2 + (DEFAULT_CHILD_HEIGHT * 2) * 2 + DEFAULT_CHILD_HEIGHT
     */
    GridRowLayoutAlgorithm algorithm;
    auto gutter = std::make_pair<double, double>(0, 0);
    auto resultHeight = algorithm.MeasureChildren(Referenced::RawPtr(gridRow), 20.0f, 0, gutter,
        V2::GridSizeType::XS, 12);
    EXPECT_EQ(algorithm.gridColChildrenRows_.size(), 2) << algorithm.gridColChildrenRows_.size();
    EXPECT_EQ(resultHeight, DEFAULT_CHILD_HEIGHT * 7) << resultHeight;
    /**
     * @tc.steps: step3. Check the NewlineOffset
     * @tc.expected: newlineCount = (26 - 4) / 12 + 1 = 2, offset =  (26 - 4) % 12 = 10, childSpan = 6
            but offset + childSpan > 12, so newlineCount = 3, offset = 0
     */
    NewLineOffset expectResult;
    CreateNewLineOffset(0, 0, 8, 0.0f, expectResult);
    auto expected = expectResult.ToString();
    CreateNewLineOffset(3, 0, 6, DEFAULT_CHILD_HEIGHT * 6, expectResult);
    expected += expectResult.ToString();
    auto result = DumpChildrenInfo(algorithm.gridColChildrenRows_);
    EXPECT_EQ(result, expected) << result;
}

/**
 * @tc.name: ParseNewLineForLargeOffsetTest02
 * @tc.desc: restColumns = 4, gridCol.offset = 20, gridCol.span = 6
 * @tc.type: FUNC
 */
HWTEST_F(GridrowCalcGridcolPosTestNg, ParseNewLineForLargeOffsetTest02, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create GridRow and GridCol, the first line has four columns left
     */
    auto gridRow = CreateGridRow([this](GridRowModelNG model) {
        ViewAbstract::SetWidth(CalcLength(DEFAULT_WIDTH));
        CreateGridCol([this](GridColModelNG model) {
            V2::GridContainerSize span(DEFAULT_COLUMNS - FOUR_COLUMNS_LEFT);
            model.SetSpan(span);
            ViewAbstract::SetHeight(CalcLength(DEFAULT_CHILD_HEIGHT));
        });
        CreateGridCol([this](GridColModelNG model) {
            V2::GridContainerSize span(6);
            V2::GridContainerSize offset(20);
            model.SetSpan(span);
            model.SetOffset(offset);
            ViewAbstract::SetHeight(CalcLength(DEFAULT_CHILD_HEIGHT * 2));
        });
    });
    ASSERT_NE(gridRow, nullptr);
    /**
     * @tc.steps: step2. Call GridRowLayoutAlgorithm.MeasureChildren
     * @tc.expected: GridRow height = DEFAULT_CHILD_HEIGHT + 2 * (DEFAULT_CHILD_HEIGHT * 2)
     */
    GridRowLayoutAlgorithm algorithm;
    auto gutter = std::make_pair<double, double>(0, 0);
    auto resultHeight = algorithm.MeasureChildren(Referenced::RawPtr(gridRow), 20.0f, 0, gutter,
        V2::GridSizeType::XS, 12);
    EXPECT_EQ(algorithm.gridColChildrenRows_.size(), 2) << algorithm.gridColChildrenRows_.size();
    EXPECT_EQ(resultHeight, DEFAULT_CHILD_HEIGHT * 4) << resultHeight;
    /**
     * @tc.steps: step3. Check the NewlineOffset
     * @tc.expected: newlineCount = (20 - 4) / 12 + 1 = 2, offset =  (20 - 4) % 12 = 4, childSpan = 6
     */
    NewLineOffset expectResult;
    CreateNewLineOffset(0, 0, 8, 0.0f, expectResult);
    auto expected = expectResult.ToString();
    CreateNewLineOffset(2, 4, 6, DEFAULT_CHILD_HEIGHT * 2, expectResult);
    expected += expectResult.ToString();
    auto result = DumpChildrenInfo(algorithm.gridColChildrenRows_);
    EXPECT_EQ(result, expected) << result;
}

/**
 * @tc.name: ParseNewLineForLargeOffsetTest03
 * @tc.desc: restColumns = 4, gridCol.offset = 20, gridCol.span = 8
 * @tc.type: FUNC
 */
HWTEST_F(GridrowCalcGridcolPosTestNg, ParseNewLineForLargeOffsetTest03, TestSize.Level0)
{
    /**
     * @tc.steps: step1. Create GridRow and GridCol, the first line has four columns left
     */
    auto gridRow = CreateGridRow([this](GridRowModelNG model) {
        ViewAbstract::SetWidth(CalcLength(DEFAULT_WIDTH));
        CreateGridCol([this](GridColModelNG model) {
            V2::GridContainerSize span(DEFAULT_COLUMNS - FOUR_COLUMNS_LEFT);
            model.SetSpan(span);
            ViewAbstract::SetHeight(CalcLength(DEFAULT_CHILD_HEIGHT));
        });
        CreateGridCol([this](GridColModelNG model) {
            V2::GridContainerSize span(8);
            V2::GridContainerSize offset(20);
            model.SetSpan(span);
            model.SetOffset(offset);
            ViewAbstract::SetHeight(CalcLength(DEFAULT_CHILD_HEIGHT));
        });
    });
    ASSERT_NE(gridRow, nullptr);
    /**
     * @tc.steps: step2. Call GridRowLayoutAlgorithm.MeasureChildren
     * @tc.expected: GridRow height = DEFAULT_CHILD_HEIGHT + DEFAULT_CHILD_HEIGHT * 2
     */
    GridRowLayoutAlgorithm algorithm;
    auto gutter = std::make_pair<double, double>(0, 0);
    auto resultHeight = algorithm.MeasureChildren(Referenced::RawPtr(gridRow), 20.0f, 0, gutter,
        V2::GridSizeType::XS, 12);
    EXPECT_EQ(algorithm.gridColChildrenRows_.size(), 2) << algorithm.gridColChildrenRows_.size();
    EXPECT_EQ(resultHeight, DEFAULT_CHILD_HEIGHT * 3) << resultHeight;
    /**
     * @tc.steps: step3. Check the NewlineOffset
     * @tc.expected: newlineCount = (20 - 4) / 12 + 1 = 2, offset =  (26 - 4) % 12 = 4, childSpan = 8
     */
    NewLineOffset expectResult;
    CreateNewLineOffset(0, 0, 8, 0.0f, expectResult);
    auto expected = expectResult.ToString();
    CreateNewLineOffset(2, 4, 8, DEFAULT_CHILD_HEIGHT * 2, expectResult);
    expected += expectResult.ToString();
    auto result = DumpChildrenInfo(algorithm.gridColChildrenRows_);
    EXPECT_EQ(result, expected) << result;
}
} // namespace OHOS::Ace::NG
