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
    constexpr double DEFAULT_WIDTH = 230.0f;
    constexpr int32_t DEFAULT_COLUMNS = 12;
    constexpr int32_t REST_COLUMNS_FOUR = 4;
    constexpr double DEFAULT_CHILD_HEIGHT = 30.0f;
} // namespace
class GridRowLayoutTestNG : public GridRowBaseTestNG {
};

/**
 * @tc.name: LayoutTest01
 * @tc.desc: restColumns = 4, gridCol.offset = 26, gridCol.span = 6
 *           gutter.x = 10, gutter.y = 10
 * @tc.type: FUNC
 */
HWTEST_F(GridRowLayoutTestNG, LayoutTest01, TestSize.Level1)
{
    RefPtr<FrameNode> gridCol1, gridCol2;
    auto gridRow = CreateGridRow([this, &gridCol1, &gridCol2](GridRowModelNG model) {
        ViewAbstract::SetWidth(CalcLength(DEFAULT_WIDTH));
        Dimension xDimension = Dimension(10, DimensionUnit::PX);
        Dimension yDimension = Dimension(10, DimensionUnit::PX);
        V2::Gutter gutter = V2::Gutter(xDimension, yDimension);
        ACE_UPDATE_LAYOUT_PROPERTY(GridRowLayoutProperty, Gutter, gutter);
        gridCol1 = CreateGridCol([this](GridColModelNG model) {
            V2::GridContainerSize span(DEFAULT_COLUMNS - REST_COLUMNS_FOUR);
            ACE_UPDATE_LAYOUT_PROPERTY(GridColLayoutProperty, Span, span);
            ViewAbstract::SetHeight(CalcLength(DEFAULT_CHILD_HEIGHT));
        });
        gridCol2 = CreateGridCol([this](GridColModelNG model) {
            V2::GridContainerSize span(6);
            V2::GridContainerSize offset(26);
            ACE_UPDATE_LAYOUT_PROPERTY(GridColLayoutProperty, Span, span);
            ACE_UPDATE_LAYOUT_PROPERTY(GridColLayoutProperty, Offset, offset);
            ViewAbstract::SetHeight(CalcLength(DEFAULT_CHILD_HEIGHT));
        });
    });
    ASSERT_NE(gridRow, nullptr);
    /**
     * @tc.steps: Call CreateLayoutTask
     * @tc.expected: gridCol1.FrameRect = (0, 0, 150, DEFAULT_CHILD_HEIGHT)
     *               gridCol2.FrameRect = (0, 3 * DEFAULT_CHILD_HEIGHT + gutter.Y, 110, DEFAULT_CHILD_HEIGHT)
     */
    LayoutConstraintF constraint;
    OptionalSizeF size;
    size.SetWidth(DEFAULT_WIDTH);
    constraint.UpdateIllegalSelfIdealSizeWithCheck(size);
    auto layoutProperty = gridRow->GetLayoutProperty();
    layoutProperty->UpdateLayoutConstraint(constraint);
    layoutProperty->UpdateContentConstraint();
    GridRowLayoutAlgorithm algorithm;
    algorithm.Measure(Referenced::RawPtr(gridRow));
    algorithm.Layout(Referenced::RawPtr(gridRow));
    EXPECT_EQ(gridCol1->GetGeometryNode()->GetMarginFrameRect(), RectF(0, 0, 150, DEFAULT_CHILD_HEIGHT))
        << gridCol1->GetGeometryNode()->GetMarginFrameRect().ToString();
    EXPECT_EQ(gridCol2->GetGeometryNode()->GetMarginFrameRect(), RectF(0, 100, 110, DEFAULT_CHILD_HEIGHT))
        << gridCol2->GetGeometryNode()->GetMarginFrameRect().ToString();
    /**
     * @tc.step: change the text direction to RTL
     */
    layoutProperty->UpdateLayoutDirection(TextDirection::RTL);
    algorithm.Measure(Referenced::RawPtr(gridRow));
    algorithm.Layout(Referenced::RawPtr(gridRow));
    EXPECT_EQ(gridCol1->GetGeometryNode()->GetMarginFrameRect(), RectF(80, 0, 150, DEFAULT_CHILD_HEIGHT))
        << gridCol1->GetGeometryNode()->GetMarginFrameRect().ToString();
    EXPECT_EQ(gridCol2->GetGeometryNode()->GetMarginFrameRect(), RectF(120, 100, 110, DEFAULT_CHILD_HEIGHT))
        << gridCol2->GetGeometryNode()->GetMarginFrameRect().ToString();
}

/**
 * @tc.name: LayoutTest02
 * @tc.desc: restColumns = 4, gridCol.offset = 26, gridCol.span = 6
 *           gutter.x = 10, gutter.y = 10, direction = RowReverse
 * @tc.type: FUNC
 */
HWTEST_F(GridRowLayoutTestNG, LayoutTest02, TestSize.Level1)
{
    RefPtr<FrameNode> gridCol1, gridCol2;
    auto gridRow = CreateGridRow([this, &gridCol1, &gridCol2](GridRowModelNG model) {
        ViewAbstract::SetWidth(CalcLength(DEFAULT_WIDTH));
        Dimension xDimension = Dimension(10, DimensionUnit::PX);
        Dimension yDimension = Dimension(10, DimensionUnit::PX);
        V2::Gutter gutter = V2::Gutter(xDimension, yDimension);
        ACE_UPDATE_LAYOUT_PROPERTY(GridRowLayoutProperty, Gutter, gutter);
        ACE_UPDATE_LAYOUT_PROPERTY(GridRowLayoutProperty, Direction, V2::GridRowDirection::RowReverse);
        gridCol1 = CreateGridCol([this](GridColModelNG model) {
            V2::GridContainerSize span(DEFAULT_COLUMNS - REST_COLUMNS_FOUR);
            ACE_UPDATE_LAYOUT_PROPERTY(GridColLayoutProperty, Span, span);
            ViewAbstract::SetHeight(CalcLength(DEFAULT_CHILD_HEIGHT));
        });
        gridCol2 = CreateGridCol([this](GridColModelNG model) {
            V2::GridContainerSize span(6);
            V2::GridContainerSize offset(26);
            ACE_UPDATE_LAYOUT_PROPERTY(GridColLayoutProperty, Span, span);
            ACE_UPDATE_LAYOUT_PROPERTY(GridColLayoutProperty, Offset, offset);
            ViewAbstract::SetHeight(CalcLength(DEFAULT_CHILD_HEIGHT));
        });
    });
    ASSERT_NE(gridRow, nullptr);
    /**
     * @tc.steps: Call CreateLayoutTask
     * @tc.expected: gridCol1.FrameRect = (80, 0, 150, DEFAULT_CHILD_HEIGHT)
     *               gridCol2.FrameRect = (120, 3 * DEFAULT_CHILD_HEIGHT + gutter.Y, 110, DEFAULT_CHILD_HEIGHT)
     */
    LayoutConstraintF constraint;
    OptionalSizeF size;
    size.SetWidth(DEFAULT_WIDTH);
    constraint.UpdateIllegalSelfIdealSizeWithCheck(size);
    auto layoutProperty = gridRow->GetLayoutProperty();
    layoutProperty->UpdateLayoutConstraint(constraint);
    layoutProperty->UpdateContentConstraint();
    GridRowLayoutAlgorithm algorithm;
    algorithm.Measure(Referenced::RawPtr(gridRow));
    algorithm.Layout(Referenced::RawPtr(gridRow));
    EXPECT_EQ(gridCol1->GetGeometryNode()->GetMarginFrameRect(), RectF(80, 0, 150, DEFAULT_CHILD_HEIGHT))
        << gridCol1->GetGeometryNode()->GetMarginFrameRect().ToString();
    EXPECT_EQ(gridCol2->GetGeometryNode()->GetMarginFrameRect(), RectF(120, 100, 110, DEFAULT_CHILD_HEIGHT))
        << gridCol2->GetGeometryNode()->GetMarginFrameRect().ToString();

    /**
     * @tc.step: change the text direction to RTL
     */
    layoutProperty->UpdateLayoutDirection(TextDirection::RTL);
    algorithm.Measure(Referenced::RawPtr(gridRow));
    algorithm.Layout(Referenced::RawPtr(gridRow));
    EXPECT_EQ(gridCol1->GetGeometryNode()->GetMarginFrameRect(), RectF(0, 0, 150, DEFAULT_CHILD_HEIGHT))
        << gridCol1->GetGeometryNode()->GetMarginFrameRect().ToString();
    EXPECT_EQ(gridCol2->GetGeometryNode()->GetMarginFrameRect(), RectF(0, 100, 110, DEFAULT_CHILD_HEIGHT))
        << gridCol2->GetGeometryNode()->GetMarginFrameRect().ToString();
}

/**
 * @tc.name: IsRightToLeftTest
 * @tc.desc: Test the layout direction of gridrow
 * @tc.type: FUNC
 */
HWTEST_F(GridRowLayoutTestNG, IsRightToLeftTest, TestSize.Level1)
{
    auto gridRow1 = CreateGridRow([this](GridRowModelNG model) {});
    GridRowLayoutAlgorithm algorithm;
    EXPECT_EQ(algorithm.IsRightToLeft(Referenced::RawPtr(gridRow1)), false);
    auto layoutProperty = gridRow1->GetLayoutProperty();
    layoutProperty->UpdateLayoutDirection(TextDirection::RTL);
    EXPECT_EQ(algorithm.IsRightToLeft(Referenced::RawPtr(gridRow1)), true);
    auto gridRow2 = CreateGridRow([this](GridRowModelNG model) {
         ACE_UPDATE_LAYOUT_PROPERTY(GridRowLayoutProperty, Direction, V2::GridRowDirection::RowReverse);
    });
    EXPECT_EQ(algorithm.IsRightToLeft(Referenced::RawPtr(gridRow2)), true);
    layoutProperty = gridRow2->GetLayoutProperty();
    layoutProperty->UpdateLayoutDirection(TextDirection::RTL);
    EXPECT_EQ(algorithm.IsRightToLeft(Referenced::RawPtr(gridRow2)), false);
}
} // namespace OHOS::Ace::NG
