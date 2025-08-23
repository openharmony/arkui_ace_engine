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
public:
    void CreateMeasureLayoutTask(RefPtr<FrameNode> &gridRow, std::optional<float> width = std::nullopt,
        std::optional<float> height = std::nullopt)
    {
        LayoutConstraintF constraint;
        if (width.has_value()) {
            constraint.selfIdealSize.SetWidth(width.value());
        }
        if (height.has_value()) {
            constraint.selfIdealSize.SetHeight(height.value());
        }
        auto layoutProperty = gridRow->GetLayoutProperty();
        layoutProperty->UpdateLayoutConstraint(constraint);
        layoutProperty->UpdateContentConstraint();
        GridRowLayoutAlgorithm algorithm;
        algorithm.Measure(Referenced::RawPtr(gridRow));
        algorithm.Layout(Referenced::RawPtr(gridRow));
    }

    RefPtr<FrameNode> CreateGridColWithProperty(int32_t spanVal, int32_t offsetVal, float height = 0.0f,
        FlexAlign flexAlign = FlexAlign::FLEX_START)
    {
        return CreateGridCol([this, spanVal, offsetVal, height, flexAlign](GridColModelNG model) {
            V2::GridContainerSize span(spanVal);
            V2::GridContainerSize offset(offsetVal);
            model.SetSpan(span);
            model.SetOffset(offset);
            ViewAbstract::SetHeight(CalcLength(height));
            ViewAbstract::SetAlignSelf(flexAlign);
        });
    }
};

/**
 * @tc.name: LayoutTest01
 * @tc.desc: restColumns = 4, gridCol.offset = 26, gridCol.span = 6
 *           gutter.x = 10, gutter.y = 10
 * @tc.type: FUNC
 */
HWTEST_F(GridRowLayoutTestNG, LayoutTest01, TestSize.Level0)
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
HWTEST_F(GridRowLayoutTestNG, LayoutTest02, TestSize.Level0)
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
HWTEST_F(GridRowLayoutTestNG, IsRightToLeftTest, TestSize.Level0)
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

/**
 * @tc.name: LayoutWithMatchParentInfoTest01
 * @tc.desc: Test LayoutWithMatchParentInfo func
 * @tc.type: FUNC
 */
HWTEST_F(GridRowLayoutTestNG, LayoutWithMatchParentInfoTest01, TestSize.Level0) {
    RefPtr<FrameNode> gridCol1, gridCol2, gridCol3, gridCol4, gridCol5;
    auto gridRow = CreateGridRow([this, &gridCol1, &gridCol2, &gridCol3, &gridCol4, &gridCol5](GridRowModelNG model) {
        ViewAbstract::SetWidth(CalcLength(370.0f));
        ViewAbstract::SetHeight(CalcLength(70.0f));
        ViewAbstract::SetPadding(CalcLength(10));
        V2::Gutter gutter(Dimension(10));
        ACE_UPDATE_LAYOUT_PROPERTY(GridRowLayoutProperty, Gutter, gutter);
        gridCol1 = CreateGridColWithProperty(3, 0, 10, FlexAlign::CENTER);
        gridCol2 = CreateGridColWithProperty(3, 0, 20, FlexAlign::FLEX_END);
        gridCol3 = CreateGridColWithProperty(3, 0, 30);
        gridCol4 = CreateGridColWithProperty(3, 0, 40, FlexAlign::STRETCH);
        gridCol5 = CreateGridColWithProperty(3, 12, 30);
    });
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetMinPlatformVersion(12);
    gridCol3->GetLayoutProperty()->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, false);
    gridCol3->GetLayoutProperty()->ClearUserDefinedIdealSize(true, true);
    CreateMeasureLayoutTask(gridRow, std::optional<int>(370), std::optional<int>(70));
    /* @tc.expected: The matchParentHeight of gridCol3 should be 50 = 70(gridrow height) - 20(padding)
     *               The gridCol5 is placed at the third line and
     *               gridCol5.offsetY = 10(padding.top) + 2 * 50(matchParentHeight) + 10(gutter.y)
     *               The first line is aligned with gridCol3.
     *               Each gridCol has correct frameSize.
     */
    EXPECT_EQ(gridCol1->GetGeometryNode()->GetMarginFrameRect(), RectF(10, 30, 80, 10))
        << "gridcol1:" << gridCol1->GetGeometryNode()->GetMarginFrameRect().ToString();
    EXPECT_EQ(gridCol2->GetGeometryNode()->GetMarginFrameRect(), RectF(100, 40, 80, 20))
        << "gridcol2:" << gridCol2->GetGeometryNode()->GetMarginFrameRect().ToString();
    EXPECT_EQ(gridCol3->GetGeometryNode()->GetMarginFrameRect(), RectF(190, 10, 80, 50))
        << "gridcol3:" << gridCol3->GetGeometryNode()->GetMarginFrameRect().ToString();
    EXPECT_EQ(gridCol4->GetGeometryNode()->GetMarginFrameRect(), RectF(280, 10, 80, 50))
        << "gridcol4:" << gridCol4->GetGeometryNode()->GetMarginFrameRect().ToString();
    EXPECT_EQ(gridCol5->GetGeometryNode()->GetMarginFrameRect(), RectF(10, 120, 80, 30))
        << "gridcol5:" << gridCol5->GetGeometryNode()->GetMarginFrameRect().ToString();
}

HWTEST_F(GridRowLayoutTestNG, LayoutWithMatchParentInfoTest02, TestSize.Level0) {
    RefPtr<FrameNode> gridCol1, gridCol2, gridCol3, gridCol4, gridCol5;
    auto gridRow = CreateGridRow([this, &gridCol1, &gridCol2, &gridCol3, &gridCol4, &gridCol5](GridRowModelNG model) {
        ViewAbstract::SetWidth(CalcLength(370.0f));
        ViewAbstract::SetPadding(CalcLength(10));
        V2::Gutter gutter(Dimension(10));
        ACE_UPDATE_LAYOUT_PROPERTY(GridRowLayoutProperty, Gutter, gutter);
        gridCol1 = CreateGridColWithProperty(3, 0, 10, FlexAlign::CENTER);
        gridCol2 = CreateGridColWithProperty(3, 0, 20, FlexAlign::FLEX_END);
        gridCol3 = CreateGridColWithProperty(3, 0, 30);
        gridCol4 = CreateGridColWithProperty(3, 0, 40, FlexAlign::STRETCH);
        gridCol5 = CreateGridColWithProperty(3, 12, 30);
    });
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetMinPlatformVersion(12);
    gridCol3->GetLayoutProperty()->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, false);
    gridCol3->GetLayoutProperty()->ClearUserDefinedIdealSize(true, true);
    CreateMeasureLayoutTask(gridRow, std::optional<int>(370));
    /* @tc.expected: the gridRow height is the total height of non-matchParent gridcols,
     *               which is 40(first row height) + 40(skip row height) + 10(gutter.y) + 30 + 20 = 140
     *               the matchParentHeight of gridCol3 should be 120 = 140(gridrow height) - 20(padding)
     *               Each gridCol has correct frameSize.
     */
    EXPECT_EQ(gridCol1->GetGeometryNode()->GetMarginFrameRect(), RectF(10, 65, 80, 10))
        << "gridcol1:" << gridCol1->GetGeometryNode()->GetMarginFrameRect().ToString();
    EXPECT_EQ(gridCol2->GetGeometryNode()->GetMarginFrameRect(), RectF(100, 110, 80, 20))
        << "gridcol2:" << gridCol2->GetGeometryNode()->GetMarginFrameRect().ToString();
    EXPECT_EQ(gridCol3->GetGeometryNode()->GetMarginFrameRect(), RectF(190, 10, 80, 120))
        << "gridcol3:" << gridCol3->GetGeometryNode()->GetMarginFrameRect().ToString();
    EXPECT_EQ(gridCol4->GetGeometryNode()->GetMarginFrameRect(), RectF(280, 10, 80, 120))
        << "gridcol4:" << gridCol4->GetGeometryNode()->GetMarginFrameRect().ToString();
    EXPECT_EQ(gridCol5->GetGeometryNode()->GetMarginFrameRect(), RectF(10, 260, 80, 30))
        << "gridcol5:" << gridCol5->GetGeometryNode()->GetMarginFrameRect().ToString();
}

/**
 * @tc.name: LayoutWithMatchParentInfoTest03
 * @tc.desc: Test LayoutWithMatchParentInfo func
 * @tc.type: FUNC
 */
HWTEST_F(GridRowLayoutTestNG, LayoutWithMatchParentInfoTest03, TestSize.Level0) {
    RefPtr<FrameNode> gridCol1, gridCol2, gridCol3, gridCol4, gridCol5;
    auto gridRow = CreateGridRow([this, &gridCol1, &gridCol2, &gridCol3, &gridCol4, &gridCol5](GridRowModelNG model) {
        ViewAbstract::SetWidth(CalcLength(370.0f));
        ViewAbstract::SetHeight(CalcLength(70.0f));
        ViewAbstract::SetPadding(CalcLength(10));
        V2::Gutter gutter(Dimension(10));
        ACE_UPDATE_LAYOUT_PROPERTY(GridRowLayoutProperty, Gutter, gutter);
        gridCol1 = CreateGridColWithProperty(3, 0, 10, FlexAlign::CENTER);
        gridCol2 = CreateGridColWithProperty(3, 0, 20, FlexAlign::FLEX_END);
        gridCol3 = CreateGridColWithProperty(3, 0, 30, FlexAlign::STRETCH);
        gridCol4 = CreateGridColWithProperty(3, 0, 100);
        gridCol5 = CreateGridColWithProperty(3, 12, 30);
    });
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetMinPlatformVersion(12);
    gridCol3->GetLayoutProperty()->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, false);
    gridCol3->GetLayoutProperty()->ClearUserDefinedIdealSize(true, true);
    CreateMeasureLayoutTask(gridRow, std::optional<int>(370), std::optional<int>(70));
    /* @tc.expected: The matchParentHeight of gridCol3 should be 50 = 70(gridrow height) - 20(padding)
     *               The gridCol5 is placed at the third line and
     *               gridCol5.offsetY = 10(padding.top) + 2 * 100(first line hegiht) + 10(gutter.y)
     *               The first line is aligned with gridCol4.
     *               Each gridCol has correct frameSize.
     */
    EXPECT_EQ(gridCol1->GetGeometryNode()->GetMarginFrameRect(), RectF(10, 55, 80, 10))
        << "gridcol1:" << gridCol1->GetGeometryNode()->GetMarginFrameRect().ToString();
    EXPECT_EQ(gridCol2->GetGeometryNode()->GetMarginFrameRect(), RectF(100, 90, 80, 20))
        << "gridcol2:" << gridCol2->GetGeometryNode()->GetMarginFrameRect().ToString();
    EXPECT_EQ(gridCol3->GetGeometryNode()->GetMarginFrameRect(), RectF(190, 10, 80, 100))
        << "gridcol3:" << gridCol3->GetGeometryNode()->GetMarginFrameRect().ToString();
    EXPECT_EQ(gridCol4->GetGeometryNode()->GetMarginFrameRect(), RectF(280, 10, 80, 100))
        << "gridcol4:" << gridCol4->GetGeometryNode()->GetMarginFrameRect().ToString();
    EXPECT_EQ(gridCol5->GetGeometryNode()->GetMarginFrameRect(), RectF(10, 220, 80, 30))
        << "gridcol5:" << gridCol5->GetGeometryNode()->GetMarginFrameRect().ToString();
}

/**
 * @tc.name: GetPaddingOffsetTest
 * @tc.desc: Test GetPaddingOffset func
 * @tc.type: FUNC
 */
HWTEST_F(GridRowLayoutTestNG, GetPaddingOffsetTest, TestSize.Level0)
{
    auto gridRow = CreateGridRow([this](GridRowModelNG model) {
        PaddingProperty padding = {
            .left = CalcLength(10),
            .right = CalcLength(20),
            .top = CalcLength(30),
        };
        ViewAbstract::SetPadding(padding);
    });
    GridRowLayoutAlgorithm algorithm;
    OffsetF result;
    result = algorithm.GetPaddingOffset(Referenced::RawPtr(gridRow), false);
    EXPECT_EQ(result, OffsetF(10, 30));
    result = algorithm.GetPaddingOffset(Referenced::RawPtr(gridRow), true);
    EXPECT_EQ(result, OffsetF(-20, 30));
}
} // namespace OHOS::Ace::NG
