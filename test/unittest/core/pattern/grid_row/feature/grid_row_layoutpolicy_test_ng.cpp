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
class GridRowLayoutPolicyTestNG : public GridRowBaseTestNG {
};

/**
 * @tc.name: MeasureSelfByLayoutPolicyTest01
 * @tc.desc: Test whether MeasureSelfByLayoutPolicy can return correct policySize
 * @tc.type: FUNC
 */
HWTEST_F(GridRowLayoutPolicyTestNG, MeasureSelfByLayoutPolicyTest01, TestSize.Level0)
{
    auto frameNode = CreateGridRow([this](GridRowModelNG model) {});
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    GridRowLayoutAlgorithm algorithm;
    
    LayoutConstraintF layoutConstraint = {.parentIdealSize = {300, 350}};
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    auto selfSize = algorithm.MeasureSelfByLayoutPolicy(Referenced::RawPtr(frameNode), 90,
        LayoutCalPolicy::MATCH_PARENT, LayoutCalPolicy::MATCH_PARENT);
    EXPECT_EQ(selfSize, OptionalSizeF(300, 350)) << selfSize.ToString();

    selfSize = algorithm.MeasureSelfByLayoutPolicy(Referenced::RawPtr(frameNode), 90,
        LayoutCalPolicy::NO_MATCH, LayoutCalPolicy::NO_MATCH);
    EXPECT_EQ(selfSize, OptionalSizeF(std::nullopt, std::nullopt));

    selfSize = algorithm.MeasureSelfByLayoutPolicy(Referenced::RawPtr(frameNode), 90,
        LayoutCalPolicy::WRAP_CONTENT, LayoutCalPolicy::WRAP_CONTENT);
    EXPECT_EQ(selfSize, OptionalSizeF(std::nullopt, std::nullopt));
    
    selfSize = algorithm.MeasureSelfByLayoutPolicy(Referenced::RawPtr(frameNode), 90,
        LayoutCalPolicy::FIX_AT_IDEAL_SIZE, LayoutCalPolicy::FIX_AT_IDEAL_SIZE);
    EXPECT_EQ(selfSize, OptionalSizeF(std::nullopt, 90));

    layoutProperty->UpdateCalcMaxSize(CalcSize(CalcLength(50), CalcLength(50)));
    selfSize = algorithm.MeasureSelfByLayoutPolicy(Referenced::RawPtr(frameNode), 90,
        LayoutCalPolicy::FIX_AT_IDEAL_SIZE, LayoutCalPolicy::FIX_AT_IDEAL_SIZE);
    EXPECT_EQ(selfSize, OptionalSizeF(std::nullopt, 50));
}

/**
 * @tc.name: LayoutWithMatchParentInfoTest01
 * @tc.desc: Test LayoutWithMatchParentInfo func
 * @tc.type: FUNC
 */
HWTEST_F(GridRowLayoutPolicyTestNG, LayoutWithMatchParentInfoTest01, TestSize.Level0) {
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

HWTEST_F(GridRowLayoutPolicyTestNG, LayoutWithMatchParentInfoTest02, TestSize.Level0) {
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
HWTEST_F(GridRowLayoutPolicyTestNG, LayoutWithMatchParentInfoTest03, TestSize.Level0) {
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
} // namespace OHOS::Ace::NG
