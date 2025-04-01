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
#include "grid_row_base_test_ng.h"

namespace OHOS::Ace::NG {
namespace {
    constexpr double DEFAULT_WIDTH = 240.0f;
    constexpr int32_t DEFAULT_COLUMNS = 12;
    constexpr double DEFAULT_SPAN_WIDTH = 20.0f;
    constexpr int32_t FOUR_COLUMNS_LEFT = 4;
    constexpr int32_t TEN_COLUMNS_LEFT = 10;
    constexpr double DEFAULT_CHILD_HEIGHT = 30.0f;
} // namespace
class GridRowMeasureTestNG : public GridRowBaseTestNG {
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

    void CreateMeasureLayoutTask(RefPtr<FrameNode> &gridRow)
    {
        LayoutConstraintF constraint;
        auto layoutProperty = gridRow->GetLayoutProperty();
        layoutProperty->UpdateLayoutConstraint(constraint);
        layoutProperty->UpdateContentConstraint();
        GridRowLayoutAlgorithm algorithm;
        algorithm.Measure(Referenced::RawPtr(gridRow));
        algorithm.Layout(Referenced::RawPtr(gridRow));
    }

    RefPtr<FrameNode> CreateGridColWithProperty(int32_t spanVal, int32_t offsetVal, float height = 0.0f)
    {
        return CreateGridCol([this, spanVal, offsetVal, height](GridColModelNG model) {
            V2::GridContainerSize span(spanVal);
            V2::GridContainerSize offset(offsetVal);
            model.SetSpan(span);
            model.SetOffset(offset);
            ViewAbstract::SetHeight(CalcLength(height));
        });
    }
};

/**
 * @tc.name: ParseNewLineForLargeOffsetTest01
 * @tc.desc: restColumns = 4, gridCol.offset = 26, gridCol.span = 6
 * @tc.type: FUNC
 */
HWTEST_F(GridRowMeasureTestNG, ParseNewLineForLargeOffsetTest01, TestSize.Level1)
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
HWTEST_F(GridRowMeasureTestNG, ParseNewLineForLargeOffsetTest02, TestSize.Level1)
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
HWTEST_F(GridRowMeasureTestNG, ParseNewLineForLargeOffsetTest03, TestSize.Level1)
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

/**
 * @tc.name: CalculateOffsetOfNewlineTest01
 * @tc.desc: case01. restColumns = offset + currentChildSpan
 * @tc.type: FUNC
 */
HWTEST_F(GridRowMeasureTestNG, CalculateOffsetOfNewlineTest01, TestSize.Level1)
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
HWTEST_F(GridRowMeasureTestNG, CalculateOffsetOfNewlineTest02, TestSize.Level1)
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
HWTEST_F(GridRowMeasureTestNG, CalculateOffsetOfNewlineTest03, TestSize.Level1)
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
HWTEST_F(GridRowMeasureTestNG, CalculateOffsetOfNewlineTest04, TestSize.Level1)
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
 * @tc.name: CalcCrossAxisAlignmentTest01
 * @tc.desc: GridRow alignItems is FlexAlign::STRETCH
 * @tc.type: FUNC
 */
HWTEST_F(GridRowMeasureTestNG, CalcCrossAxisAlignmentTest01, TestSize.Level1)
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
HWTEST_F(GridRowMeasureTestNG, CalcCrossAxisAlignmentTest02, TestSize.Level1)
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
HWTEST_F(GridRowMeasureTestNG, CalcCrossAxisAlignmentTest03, TestSize.Level1)
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
HWTEST_F(GridRowMeasureTestNG, CalcCrossAxisAlignmentTest04, TestSize.Level1)
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
HWTEST_F(GridRowMeasureTestNG, CalcCrossAxisAlignmentTest05, TestSize.Level1)
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
HWTEST_F(GridRowMeasureTestNG, CalcCrossAxisAlignmentTest06, TestSize.Level1)
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
 * @tc.name: OnBreakpointChangeTest01
 * @tc.desc: Test OnBreakpointChange
 * @tc.type: FUNC
 */
HWTEST_F(GridRowMeasureTestNG, OnBreakpointChangeTest01, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GridRow
     */
    auto gridRow = CreateGridRow([this](GridRowModelNG model) {
        V2::BreakPoints breakpoints;
        breakpoints.reference = V2::BreakPointsReference::ComponentSize;
        breakpoints.breakpoints.assign({ "100px", "200px", "300px", "400px", "500px" });
        ViewAbstract::SetWidth(CalcLength(10));
        ACE_UPDATE_LAYOUT_PROPERTY(GridRowLayoutProperty, BreakPoints, breakpoints);
    });
    auto eventHub = gridRow->GetEventHub<GridRowEventHub>();
    bool eventTriggerFlag = false;
    auto layoutProperty = gridRow->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    /**
     * @tc.steps: step2. Set OnBreakpointChange callback
     * @tc.expected: breakpoint is changed to xs
     */
    eventHub->SetOnBreakpointChange([&eventTriggerFlag, expectSize = std::string("xs")](const std::string& size) {
        eventTriggerFlag = true;
        EXPECT_EQ(size, expectSize);
    });
    CreateMeasureLayoutTask(gridRow);
    EXPECT_TRUE(eventTriggerFlag);
    eventTriggerFlag = false;
    /**
     * @tc.expected: breakpoint is changed to sm
     */
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(100), CalcLength(DEFAULT_CHILD_HEIGHT)));
    eventHub->SetOnBreakpointChange([&eventTriggerFlag, expectSize = std::string("sm")](const std::string& size) {
        eventTriggerFlag = true;
        EXPECT_EQ(size, expectSize);
    });
    CreateMeasureLayoutTask(gridRow);
    EXPECT_TRUE(eventTriggerFlag);
    eventTriggerFlag = false;
    /**
     * @tc.expected: breakpoint is changed to md
     */
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(200), CalcLength(DEFAULT_CHILD_HEIGHT)));
    eventHub->SetOnBreakpointChange([&eventTriggerFlag, expectSize = std::string("md")](const std::string& size) {
        eventTriggerFlag = true;
        EXPECT_EQ(size, expectSize);
    });
    CreateMeasureLayoutTask(gridRow);
    EXPECT_TRUE(eventTriggerFlag);
}

/**
 * @tc.name: OnBreakpointChangeTest02
 * @tc.desc: Test OnBreakpointChange
 * @tc.type: FUNC
 */
HWTEST_F(GridRowMeasureTestNG, OnBreakpointChangeTest02, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GridRow
     */
    auto gridRow = CreateGridRow([this](GridRowModelNG model) {
        V2::BreakPoints breakpoints;
        breakpoints.reference = V2::BreakPointsReference::ComponentSize;
        breakpoints.breakpoints.assign({ "100px", "200px", "300px", "400px", "500px" });
        ViewAbstract::SetWidth(CalcLength(300));
        ACE_UPDATE_LAYOUT_PROPERTY(GridRowLayoutProperty, BreakPoints, breakpoints);
    });
    auto eventHub = gridRow->GetEventHub<GridRowEventHub>();
    bool eventTriggerFlag = false;
    auto layoutProperty = gridRow->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    /**
     * @tc.steps: step2. Set OnBreakpointChange callback
     * @tc.expected: breakpoint is changed to lg
     */
    eventHub->SetOnBreakpointChange([&eventTriggerFlag, expectSize = std::string("lg")](const std::string& size) {
        eventTriggerFlag = true;
        EXPECT_EQ(size, expectSize);
    });
    CreateMeasureLayoutTask(gridRow);
    EXPECT_TRUE(eventTriggerFlag);
    eventTriggerFlag = false;
    /**
     * @tc.expected: breakpoint is changed to xl
     */
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(400), CalcLength(DEFAULT_CHILD_HEIGHT)));
    eventHub->SetOnBreakpointChange([&eventTriggerFlag, expectSize = std::string("xl")](const std::string& size) {
        eventTriggerFlag = true;
        EXPECT_EQ(size, expectSize);
    });
    CreateMeasureLayoutTask(gridRow);
    EXPECT_TRUE(eventTriggerFlag);
    eventTriggerFlag = false;
    /**
     * @tc.expected: breakpoint is changed to xxl
     */
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(500), CalcLength(DEFAULT_CHILD_HEIGHT)));
    eventHub->SetOnBreakpointChange([&eventTriggerFlag, expectSize = std::string("xxl")](const std::string& size) {
        eventTriggerFlag = true;
        EXPECT_EQ(size, expectSize);
    });
    CreateMeasureLayoutTask(gridRow);
    EXPECT_TRUE(eventTriggerFlag);
}

/**
 * @tc.name: MeasureSelfTest
 * @tc.desc: Test MeasureSelf
 * @tc.type: FUNC
 */
HWTEST_F(GridRowMeasureTestNG, MeasureSelfTest, TestSize.Level1)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto gridRow = CreateGridRow([this](GridRowModelNG model) {
    });
    LayoutConstraintF constraint;
    constraint.UpdateIllegalSelfIdealSizeWithCheck({std::nullopt, 60.f});
    auto layoutProperty = gridRow->GetLayoutProperty();
    layoutProperty->UpdateLayoutConstraint(constraint);
    pipeline->SetMinPlatformVersion(9);
    GridRowLayoutAlgorithm algorithm;
    algorithm.MeasureSelf(Referenced::RawPtr(gridRow), 30.f, 60.f);
    auto gridRowHeight = gridRow->GetGeometryNode()->GetFrameSize().Height();
    /**
     * @tc.expected: gridRowHeight equal to childHeight 30.0f when API < 10
     */
    EXPECT_EQ(gridRowHeight, 30.0f) << gridRowHeight;
    pipeline->SetMinPlatformVersion(12);
    algorithm.MeasureSelf(Referenced::RawPtr(gridRow), 30.f, 60.f);
    gridRowHeight = gridRow->GetGeometryNode()->GetFrameSize().Height();
    /**
     * @tc.expected: gridRowHeight equal to selfHeight 60.0f when API >= 11
     */
    EXPECT_EQ(gridRowHeight, 60.f) << gridRowHeight;
}

/**
 * @tc.name: GetSizeTypeAndMaxSizeTest01
 * @tc.desc: Test GetSizeTypeAndMaxSizeTest()
 * @tc.type: FUNC
 */
HWTEST_F(GridRowMeasureTestNG, GetSizeTypeAndMaxSizeTest01, TestSize.Level1)
{
    auto gridRow = CreateGridRow([this](GridRowModelNG model) {
        V2::BreakPoints breakpoints;
        breakpoints.reference = V2::BreakPointsReference::ComponentSize;
        breakpoints.breakpoints.assign({ "100px", "200px", "300px", "400px", "500px" });
        ACE_UPDATE_LAYOUT_PROPERTY(GridRowLayoutProperty, BreakPoints, breakpoints);
        ViewAbstract::SetBorderWidth(Dimension(5));
        ViewAbstract::SetPadding(CalcLength(5));
    });
    GridRowLayoutAlgorithm algorithm;
    LayoutConstraintF parentConstraint;
    SizeF maxSize;
    V2::GridSizeType sizeType;
    auto layoutProperty = gridRow->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    /**
     * @tc.expected: maxSize.Width = 100 - border - padding = 90
     *               sizeType = xs
     */
    parentConstraint.selfIdealSize = OptionalSizeF(100, DEFAULT_CHILD_HEIGHT);
    layoutProperty->UpdateLayoutConstraint(parentConstraint);
    algorithm.GetSizeTypeAndMaxSize(Referenced::RawPtr(gridRow), maxSize, sizeType);
    EXPECT_EQ(maxSize, SizeF(80, DEFAULT_CHILD_HEIGHT - 20)) << maxSize.ToString();
    EXPECT_EQ(sizeType, V2::GridSizeType::XS);
    /**
     * @tc.expected: maxSize.Width = 200 - border - padding = 190
     *               sizeType = sm
     */
    parentConstraint.selfIdealSize = OptionalSizeF(200, DEFAULT_CHILD_HEIGHT);
    layoutProperty->UpdateLayoutConstraint(parentConstraint);
    algorithm.GetSizeTypeAndMaxSize(Referenced::RawPtr(gridRow), maxSize, sizeType);
    EXPECT_EQ(maxSize, SizeF(180, DEFAULT_CHILD_HEIGHT - 20)) << maxSize.ToString();
    EXPECT_EQ(sizeType, V2::GridSizeType::SM);
    /**
     * @tc.expected: maxSize.Width = 300 - border - padding = 290
     *               sizeType = md
     */
    parentConstraint.selfIdealSize = OptionalSizeF(300, DEFAULT_CHILD_HEIGHT);
    layoutProperty->UpdateLayoutConstraint(parentConstraint);
    algorithm.GetSizeTypeAndMaxSize(Referenced::RawPtr(gridRow), maxSize, sizeType);
    EXPECT_EQ(maxSize, SizeF(280, DEFAULT_CHILD_HEIGHT - 20)) << maxSize.ToString();
    EXPECT_EQ(sizeType, V2::GridSizeType::MD);
    /**
     * @tc.expected: maxSize.Width = 400 - border - padding = 390
     *               sizeType = lg
     */
    parentConstraint.selfIdealSize = OptionalSizeF(400, DEFAULT_CHILD_HEIGHT);
    layoutProperty->UpdateLayoutConstraint(parentConstraint);
    algorithm.GetSizeTypeAndMaxSize(Referenced::RawPtr(gridRow), maxSize, sizeType);
    EXPECT_EQ(maxSize, SizeF(380, DEFAULT_CHILD_HEIGHT - 20)) << maxSize.ToString();
    EXPECT_EQ(sizeType, V2::GridSizeType::LG);
    /**
     * @tc.expected: maxSize.Width = 500 - border - padding = 490
     *               sizeType = xl
     */
    parentConstraint.selfIdealSize = OptionalSizeF(500, DEFAULT_CHILD_HEIGHT);
    layoutProperty->UpdateLayoutConstraint(parentConstraint);
    algorithm.GetSizeTypeAndMaxSize(Referenced::RawPtr(gridRow), maxSize, sizeType);
    EXPECT_EQ(maxSize, SizeF(480, DEFAULT_CHILD_HEIGHT - 20)) << maxSize.ToString();
    EXPECT_EQ(sizeType, V2::GridSizeType::XL);
    /**
     * @tc.expected: maxSize.Width = 600 - border - padding = 590
     *               sizeType = xxl
     */
    parentConstraint.selfIdealSize = OptionalSizeF(600, DEFAULT_CHILD_HEIGHT);
    layoutProperty->UpdateLayoutConstraint(parentConstraint);
    algorithm.GetSizeTypeAndMaxSize(Referenced::RawPtr(gridRow), maxSize, sizeType);
    EXPECT_EQ(maxSize, SizeF(580, DEFAULT_CHILD_HEIGHT - 20)) << maxSize.ToString();
    EXPECT_EQ(sizeType, V2::GridSizeType::XXL);
}

/**
 * @tc.name: GetSizeTypeAndMaxSizeTest02
 * @tc.desc: Test GetSizeTypeAndMaxSizeTest()
 * @tc.type: FUNC
 */
HWTEST_F(GridRowMeasureTestNG, GetSizeTypeAndMaxSizeTest02, TestSize.Level1)
{
    auto gridRow = CreateGridRow([this](GridRowModelNG model) {
        V2::BreakPoints breakpoints;
        breakpoints.reference = V2::BreakPointsReference::ComponentSize;
        breakpoints.breakpoints.assign({ "100px", "200px", "300px", "400px", "500px" });
        ACE_UPDATE_LAYOUT_PROPERTY(GridRowLayoutProperty, BreakPoints, breakpoints);
        ViewAbstract::SetBorderWidth(Dimension(5));
        ViewAbstract::SetPadding(CalcLength(5));
    });
    GridRowLayoutAlgorithm algorithm;
    SizeF maxSize;
    V2::GridSizeType sizeType;
    auto layoutProperty = gridRow->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    LayoutConstraintF parentConstraint;
    /**
     * @tc.expected: maxSize.Width = 100 - border - padding = 90
     *               sizeType = xs
     */
    parentConstraint.parentIdealSize = OptionalSizeF(100, DEFAULT_CHILD_HEIGHT);
    layoutProperty->UpdateLayoutConstraint(parentConstraint);
    algorithm.GetSizeTypeAndMaxSize(Referenced::RawPtr(gridRow), maxSize, sizeType);
    EXPECT_EQ(maxSize, SizeF(80, DEFAULT_CHILD_HEIGHT - 20)) << maxSize.ToString();
    EXPECT_EQ(sizeType, V2::GridSizeType::XS);
    /**
     * @tc.expected: maxSize.Width = 200 - border - padding = 190
     *               sizeType = sm
     */
    parentConstraint.parentIdealSize = OptionalSizeF(200, DEFAULT_CHILD_HEIGHT);
    layoutProperty->UpdateLayoutConstraint(parentConstraint);
    algorithm.GetSizeTypeAndMaxSize(Referenced::RawPtr(gridRow), maxSize, sizeType);
    EXPECT_EQ(maxSize, SizeF(180, DEFAULT_CHILD_HEIGHT - 20)) << maxSize.ToString();
    EXPECT_EQ(sizeType, V2::GridSizeType::SM);
    /**
     * @tc.expected: maxSize.Width = 300 - border - padding = 290
     *               sizeType = md
     */
    parentConstraint.parentIdealSize = OptionalSizeF(300, DEFAULT_CHILD_HEIGHT);
    layoutProperty->UpdateLayoutConstraint(parentConstraint);
    algorithm.GetSizeTypeAndMaxSize(Referenced::RawPtr(gridRow), maxSize, sizeType);
    EXPECT_EQ(maxSize, SizeF(280, DEFAULT_CHILD_HEIGHT - 20)) << maxSize.ToString();
    EXPECT_EQ(sizeType, V2::GridSizeType::MD);
    /**
     * @tc.expected: maxSize.Width = 400 - border - padding = 390
     *               sizeType = lg
     */
    parentConstraint.parentIdealSize = OptionalSizeF(400, DEFAULT_CHILD_HEIGHT);
    layoutProperty->UpdateLayoutConstraint(parentConstraint);
    algorithm.GetSizeTypeAndMaxSize(Referenced::RawPtr(gridRow), maxSize, sizeType);
    EXPECT_EQ(maxSize, SizeF(380, DEFAULT_CHILD_HEIGHT - 20)) << maxSize.ToString();
    EXPECT_EQ(sizeType, V2::GridSizeType::LG);
    /**
     * @tc.expected: maxSize.Width = 500 - border - padding = 490
     *               sizeType = xl
     */
    parentConstraint.parentIdealSize = OptionalSizeF(500, DEFAULT_CHILD_HEIGHT);
    layoutProperty->UpdateLayoutConstraint(parentConstraint);
    algorithm.GetSizeTypeAndMaxSize(Referenced::RawPtr(gridRow), maxSize, sizeType);
    EXPECT_EQ(maxSize, SizeF(480, DEFAULT_CHILD_HEIGHT - 20)) << maxSize.ToString();
    EXPECT_EQ(sizeType, V2::GridSizeType::XL);
    /**
     * @tc.expected: maxSize.Width = 600 - border - padding = 590
     *               sizeType = xxl
     */
    parentConstraint.parentIdealSize = OptionalSizeF(600, DEFAULT_CHILD_HEIGHT);
    layoutProperty->UpdateLayoutConstraint(parentConstraint);
    algorithm.GetSizeTypeAndMaxSize(Referenced::RawPtr(gridRow), maxSize, sizeType);
    EXPECT_EQ(maxSize, SizeF(580, DEFAULT_CHILD_HEIGHT - 20)) << maxSize.ToString();
    EXPECT_EQ(sizeType, V2::GridSizeType::XXL);
}

/**
 * @tc.name: ParseGridRowParamsTest01
 * @tc.desc: Test ParseGridRowParams()
 * @tc.type: FUNC
 */
HWTEST_F(GridRowMeasureTestNG, ParseGridRowParamsTest01, TestSize.Level1)
{
    auto gridRow = CreateGridRow([this](GridRowModelNG model) {
        V2::GridContainerSize columns;
        columns.xs = 2;
        columns.sm = 4;
        columns.md = 6;
        columns.lg = 8;
        columns.xl = 10;
        columns.xxl = 12;
        V2::Gutter gutter;
        gutter.xXs = gutter.yXs = Dimension(10);
        gutter.xSm = gutter.ySm = Dimension(20);
        gutter.xMd = gutter.yMd = Dimension(30);
        gutter.xLg = gutter.yLg = Dimension(40);
        gutter.xXl = gutter.yXl = Dimension(50);
        gutter.xXXl = gutter.yXXl = Dimension(60);
        ACE_UPDATE_LAYOUT_PROPERTY(GridRowLayoutProperty, Columns, columns);
        ACE_UPDATE_LAYOUT_PROPERTY(GridRowLayoutProperty, Gutter, gutter);
    });
    GridRowLayoutAlgorithm algorithm;
    /**
     * @tc.expected: columnUnitWidth_ = (100 - (2 - 1) * 10) / 2 = 45.f
     */
    algorithm.ParseGridRowParams(Referenced::RawPtr(gridRow), V2::GridSizeType::XS, SizeF(100, 30));
    EXPECT_EQ(algorithm.gutterInDouble_.first, 10);
    EXPECT_EQ(algorithm.gutterInDouble_.second, 10);
    EXPECT_EQ(algorithm.columnNum_, 2);
    EXPECT_EQ(algorithm.columnUnitWidth_, 45.0f);
    /**
     * @tc.expected: columnUnitWidth_ = (220 - (4 - 1) * 20) / 4 = 40.f
     */
    algorithm.ParseGridRowParams(Referenced::RawPtr(gridRow), V2::GridSizeType::SM, SizeF(220, 30));
    EXPECT_EQ(algorithm.gutterInDouble_.first, 20);
    EXPECT_EQ(algorithm.gutterInDouble_.second, 20);
    EXPECT_EQ(algorithm.columnNum_, 4);
    EXPECT_EQ(algorithm.columnUnitWidth_, 40.0f);
    /**
     * @tc.expected: columnUnitWidth_ = (300 - (6 - 1) * 30) / 6 = 25.0f
     */
    algorithm.ParseGridRowParams(Referenced::RawPtr(gridRow), V2::GridSizeType::MD, SizeF(300, 30));
    EXPECT_EQ(algorithm.gutterInDouble_.first, 30);
    EXPECT_EQ(algorithm.gutterInDouble_.second, 30);
    EXPECT_EQ(algorithm.columnNum_, 6);
    EXPECT_EQ(algorithm.columnUnitWidth_, 25.0f);
}

/**
 * @tc.name: ParseGridRowParamsTest02
 * @tc.desc: Test ParseGridRowParams()
 * @tc.type: FUNC
 */
HWTEST_F(GridRowMeasureTestNG, ParseGridRowParamsTest02, TestSize.Level1)
{
    auto gridRow = CreateGridRow([this](GridRowModelNG model) {
        V2::GridContainerSize columns;
        columns.xs = 2;
        columns.sm = 4;
        columns.md = 6;
        columns.lg = 8;
        columns.xl = 10;
        columns.xxl = 12;
        V2::Gutter gutter;
        gutter.xXs = gutter.yXs = Dimension(10);
        gutter.xSm = gutter.ySm = Dimension(20);
        gutter.xMd = gutter.yMd = Dimension(30);
        gutter.xLg = gutter.yLg = Dimension(40);
        gutter.xXl = gutter.yXl = Dimension(50);
        gutter.xXXl = gutter.yXXl = Dimension(60);
        ACE_UPDATE_LAYOUT_PROPERTY(GridRowLayoutProperty, Columns, columns);
        ACE_UPDATE_LAYOUT_PROPERTY(GridRowLayoutProperty, Gutter, gutter);
    });
    GridRowLayoutAlgorithm algorithm;
    /**
     * @tc.expected: columnUnitWidth_ = (400 - (8 - 1) * 40) / 8 = 15.f
     */
    algorithm.ParseGridRowParams(Referenced::RawPtr(gridRow), V2::GridSizeType::LG, SizeF(400, 30));
    EXPECT_EQ(algorithm.gutterInDouble_.first, 40);
    EXPECT_EQ(algorithm.gutterInDouble_.second, 40);
    EXPECT_EQ(algorithm.columnNum_, 8);
    EXPECT_EQ(algorithm.columnUnitWidth_, 15.0f);
    /**
     * @tc.expected: columnUnitWidth_ = (500 - (10 - 1) * 50) / 10 = 5.f
     */
    algorithm.ParseGridRowParams(Referenced::RawPtr(gridRow), V2::GridSizeType::XL, SizeF(500, 30));
    EXPECT_EQ(algorithm.gutterInDouble_.first, 50);
    EXPECT_EQ(algorithm.gutterInDouble_.second, 50);
    EXPECT_EQ(algorithm.columnNum_, 10);
    EXPECT_EQ(algorithm.columnUnitWidth_, 5.0f);
    /**
     * @tc.expected: columnUnitWidth_ = (1260 - (12 - 1) * 60) / 12 = 50.f
     */
    algorithm.ParseGridRowParams(Referenced::RawPtr(gridRow), V2::GridSizeType::XXL, SizeF(1260, 30));
    EXPECT_EQ(algorithm.gutterInDouble_.first, 60);
    EXPECT_EQ(algorithm.gutterInDouble_.second, 60);
    EXPECT_EQ(algorithm.columnNum_, 12);
    EXPECT_EQ(algorithm.columnUnitWidth_, 50.0f);
}

/**
 * @tc.name: GetChildAlignmentTest01
 * @tc.desc: GridRow alignItems is FlexAlign::FLEX_START
 * @tc.type: FUNC
 */
HWTEST_F(GridRowMeasureTestNG, GetChildAlignmentTest01, TestSize.Level1)
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
HWTEST_F(GridRowMeasureTestNG, GetChildAlignmentTest02, TestSize.Level1)
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
HWTEST_F(GridRowMeasureTestNG, GetChildAlignmentTest03, TestSize.Level1)
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
HWTEST_F(GridRowMeasureTestNG, GetChildAlignmentTest04, TestSize.Level1)
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
 * @tc.name: CalcCrossAxisOffsetTest
 * @tc.desc: Test CalcCrossAxisOffset()
 * @tc.type: FUNC
 */
HWTEST_F(GridRowMeasureTestNG, CalcCrossAxisOffsetTest, TestSize.Level1)
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
 * @tc.name: MeasureChildrenTest
 * @tc.desc: Test MeasureChildren function
 * @tc.type: FUNC
 */
HWTEST_F(GridRowMeasureTestNG, MeasureChildrenTest, TestSize.Level1)
{
    RefPtr<FrameNode> gridCol1, gridCol2, gridCol3, gridCol4, gridCol5;
    auto gridRow = CreateGridRow([this, &gridCol1, &gridCol2, &gridCol3, &gridCol4, &gridCol5](GridRowModelNG model) {
        ViewAbstract::SetHeight(CalcLength(180.0f));
        ViewAbstract::SetWidth(CalcLength(350.0f));
        V2::Gutter gutter(Dimension(10));
        ACE_UPDATE_LAYOUT_PROPERTY(GridRowLayoutProperty, Gutter, gutter);
        gridCol1 = CreateGridColWithProperty(2, 0, 10);
        gridCol2 = CreateGridColWithProperty(4, 2, 20);
        gridCol3 = CreateGridColWithProperty(6, 26, 30);
        gridCol4 = CreateGridColWithProperty(6, 20, 40);
        gridCol5 = CreateGridColWithProperty(2, 0, 30);
    });
    GridRowLayoutAlgorithm algorithm;
    algorithm.gutterInDouble_ = std::make_pair(10, 10);
    algorithm.columnUnitWidth_ = 20.0f;
    algorithm.columnNum_ = 12;
    /**
     * @tc.expected: totalHeight = (3 * 20 + 10) + (2 * 30 + 10) + 40
     */
    auto gutter = std::make_pair<double, double>(10, 10);
    auto totalHeight = algorithm.MeasureChildren(Referenced::RawPtr(gridRow), 20.0f, 0, gutter,
        V2::GridSizeType::XS, 12);
    EXPECT_EQ(totalHeight, 180) << totalHeight;
    auto result = DumpChildrenInfo(algorithm.gridColChildrenRows_);
    std::string expected;
    NewLineOffset expectResult;
    CreateNewLineOffset(0, 0, 2, 0, expectResult);
    expected += expectResult.ToString();
    CreateNewLineOffset(0, 4, 4, 0, expectResult);
    expected += expectResult.ToString();
    /**
     * @tc.expected: the offsetY of the second line should be 3 * firstlineHeight + gutter.y
     */
    CreateNewLineOffset(3, 0, 6, 70, expectResult);
    expected += expectResult.ToString();
    /**
     * @tc.expected: the offsetY of the third line should be 2 * secondlineHeight + gutter.y
     */
    CreateNewLineOffset(2, 2, 6, 140, expectResult);
    expected += expectResult.ToString();
    CreateNewLineOffset(0, 8, 2, 140, expectResult);
    expected += expectResult.ToString();
    EXPECT_EQ(result, expected) << result;
    /**
     * @tc.expected: the frameSize of each child is correct
     */
    EXPECT_EQ(gridCol1->GetGeometryNode()->GetFrameSize(), SizeF(50, 10))
        << gridCol1->GetGeometryNode()->GetFrameSize().ToString();
    EXPECT_EQ(gridCol2->GetGeometryNode()->GetFrameSize(), SizeF(110, 20))
        << gridCol2->GetGeometryNode()->GetFrameSize().ToString();
    EXPECT_EQ(gridCol3->GetGeometryNode()->GetFrameSize(), SizeF(170, 30))
        << gridCol3->GetGeometryNode()->GetFrameSize().ToString();
    EXPECT_EQ(gridCol4->GetGeometryNode()->GetFrameSize(), SizeF(170, 40))
        << gridCol4->GetGeometryNode()->GetFrameSize().ToString();
    EXPECT_EQ(gridCol5->GetGeometryNode()->GetFrameSize(), SizeF(50, 30))
        << gridCol5->GetGeometryNode()->GetFrameSize().ToString();
}
} // namespace OHOS::Ace::NG
