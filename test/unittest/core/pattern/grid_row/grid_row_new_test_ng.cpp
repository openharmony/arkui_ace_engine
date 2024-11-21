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

#include "core/components_ng/pattern//linear_layout/row_model_ng.h"
#include "core/components_v2/grid_layout/grid_container_util_class.h"

namespace OHOS::Ace::NG {
namespace {
const int32_t THIRD_CHILD = 2;
const int32_t EIGHTH_CHILD = 7;
} // namespace
class GridRowNewTestNG : public GridRowBaseTestNG {};

/**
 * @tc.name: Example
 * @tc.desc: Show an example of creating a test case.
 * @tc.type: ETS
 */
HWTEST_F(GridRowNewTestNG, Example, TestSize.Level1)
{
    // If this test is related to api versions, need to SetMinPlatformVersion
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetMinPlatformVersion(12);

    /**
    corresponding ets code:

    @State bgColors: Color[] = [Color.Red, Color.Orange, Color.Yellow, Color.Green, Color.Pink, Color.Grey, Color.Blue,
    Color.Brown]

    GridRow({columns: 5, gutter: { x: '5px', y: '10px' }, direction: GridRowDirection.Row}) {
        ForEach(this.bgColors, (color: Color) => {
          GridCol({ span: { xs: 1, sm: 2, md: 3, lg: 4 }, offset: 0, order: 0 }) {
            Row()
             .width("100%")
             .height("30px")
          }
          .borderColor(color)
          .borderWidth(2)
        })
    }
     .width("300px")
     .height("300px")
    */
    auto frameNode = CreateGridRow([this](GridRowModelNG model) {
        // step: set GridRowOptions
        V2::GridContainerSize col = V2::GridContainerSize(5);
        Dimension xDimension = Dimension(5, DimensionUnit::PX);
        Dimension yDimension = Dimension(10, DimensionUnit::PX);
        V2::Gutter gutter = V2::Gutter(xDimension, yDimension);
        V2::BreakPoints breakpoints;
        // xs: window width <= 1000px, sm: window width > 1000px
        breakpoints.breakpoints = { "1000px" };
        // test case runtime, get window width = 0
        breakpoints.reference = V2::BreakPointsReference::WindowSize;

        ACE_UPDATE_LAYOUT_PROPERTY(GridRowLayoutProperty, Columns, col);
        ACE_UPDATE_LAYOUT_PROPERTY(GridRowLayoutProperty, Gutter, gutter);
        ACE_UPDATE_LAYOUT_PROPERTY(GridRowLayoutProperty, BreakPoints, breakpoints);
        ACE_UPDATE_LAYOUT_PROPERTY(GridRowLayoutProperty, Direction, V2::GridRowDirection::Row);

        // step: Set GridRow attribute
        ViewAbstract::SetWidth(CalcLength(300.0f));
        ViewAbstract::SetHeight(CalcLength(300.0f));

        // step: Create 8 GridCol
        for (int32_t i = 0; i < 8; i++) {
            CreateGridCol([this](GridColModelNG model) {
                V2::GridContainerSize span;
                span.xs = 1;
                span.sm = 2;
                ACE_UPDATE_LAYOUT_PROPERTY(GridColLayoutProperty, Span, span);

                CreateRow([](RowModelNG model) {
                    ViewAbstract::SetWidth(CalcLength(Dimension(100 / 100.0, DimensionUnit::PERCENT)));
                    ViewAbstract::SetHeight(CalcLength(30.0f));
                });
            });
        }
    });
    ASSERT_EQ(frameNode->GetChildren().size(), 8);

    CreateLayoutTask(frameNode);

    // @tc.expected: every grid col width = (300 - 4 * 5px)/5 = 56px
    EXPECT_EQ(frameNode->GetChildByIndex(THIRD_CHILD)->GetGeometryNode()->GetFrameSize().Width(), 56.0f);
    // @tc.expected: 3rd grid col offset x = 2 * 56px + 2 * 5px = 122px
    EXPECT_EQ(frameNode->GetChildByIndex(THIRD_CHILD)->GetGeometryNode()->GetFrameOffset().GetX(), 122.0f);
    // @tc.expected: 8st grid col offset x = 2 * 56px + 2 * 5px = 122px, y = 10px + 30px = 40px
    EXPECT_EQ(frameNode->GetChildByIndex(EIGHTH_CHILD)->GetGeometryNode()->GetFrameOffset().GetX(), 122.0f);
    EXPECT_EQ(frameNode->GetChildByIndex(EIGHTH_CHILD)->GetGeometryNode()->GetFrameOffset().GetY(), 40.0f);
}
} // namespace OHOS::Ace::NG