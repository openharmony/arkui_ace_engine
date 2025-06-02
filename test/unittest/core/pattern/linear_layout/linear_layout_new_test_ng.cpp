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
#include "linear_layout_base_test_ng.h"

#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/pattern/text/text_model_ng.h"

namespace OHOS::Ace::NG {
namespace {
const int32_t FIRST_CHILD = 0;
const int32_t SECOND_CHILD = 1;
} // namespace
class LinearLayoutNewTestNG : public LinearLayoutBaseTestNG {};

/**
 * @tc.name: Example
 * @tc.desc: Show an example of creating a test case.
 * @tc.type: ETS
 */
HWTEST_F(LinearLayoutNewTestNG, Example, TestSize.Level1)
{
    // If this test is related to api versions, need to SetMinPlatformVersion
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetMinPlatformVersion(12);
    /**
    corresponding ets code:

    Column() {
        Column()
         .width('50%')
         .height(30)
         .backgroundColor(0xAFEEEE)
        Column()
        .width('50%')
        .height(30)
        .backgroundColor(0x00FFFF)
      }
       .alignItems(HorizontalAlign.Start)
       .width('300px')
       .height('300px')
    */
    auto frameNode = CreateColumn([this](ColumnModelNG model) {
        // step: set alignItems: HorizontalAlign.Start
        model.SetAlignItems(FlexAlign::FLEX_START);

        // step: set stack common attribute
        ViewAbstract::SetWidth(CalcLength(300.0f));
        ViewAbstract::SetHeight(CalcLength(300.0f));

        // step: create child nodes
        for (int32_t i = 0; i < 2; i++) {
            CreateColumn([this](ColumnModelNG model) {
                ViewAbstract::SetWidth(CalcLength(Dimension(50 / 100.0, DimensionUnit::PERCENT)));
                ViewAbstract::SetHeight(CalcLength(30.0f));
            });
        }
    });
    ASSERT_EQ(frameNode->GetChildren().size(), 2);
    CreateLayoutTask(frameNode);

    // expect: first column offset (x, y) = (0, 0)
    EXPECT_EQ(frameNode->GetChildByIndex(FIRST_CHILD)->GetGeometryNode()->GetFrameOffset().GetX(), 0.0f);
    EXPECT_EQ(frameNode->GetChildByIndex(FIRST_CHILD)->GetGeometryNode()->GetFrameOffset().GetY(), 0.0f);
    // expect: second column offset (x, y) = (0, 30)
    EXPECT_EQ(frameNode->GetChildByIndex(SECOND_CHILD)->GetGeometryNode()->GetFrameOffset().GetX(), 0.0f);
    EXPECT_EQ(frameNode->GetChildByIndex(SECOND_CHILD)->GetGeometryNode()->GetFrameOffset().GetY(), 30.0f);
}

/**
 * @tc.name: LayoutPolicyTest001
 * @tc.desc: test the measure result when setting layoutPolicy.
 * @tc.type: FUNC
 */
HWTEST_F(LinearLayoutNewTestNG, LayoutPolicyTest001, TestSize.Level1)
{
    RefPtr<FrameNode> column1;
    auto column = CreateColumn([this, &column1](ColumnModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500));
        ViewAbstract::SetHeight(CalcLength(300));
        column1 = CreateColumn([](ColumnModelNG model) {
            ViewAbstractModelNG model1;
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, true);
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, false);
        });
    });
    ASSERT_NE(column, nullptr);
    ASSERT_EQ(column->GetChildren().size(), 1);
    CreateLayoutTask(column);

    /* corresponding ets code:
        Column() {
          Column()
            .width(LayoutPolicy.MATCH_PARENT)
            .height(LayoutPolicy.MATCH_PARENT)
        }
        .width(500)
        .height(300)
    */

    // Expect column's width is 500, height is 300 and offset is [0.0, 0.0].
    auto geometryNode = column->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(500.0f, 300.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    // Expect column1's width is 500, height is 300 and offset is [0.0, 0.0].
    auto geometryNode1 = column1->GetGeometryNode();
    ASSERT_NE(geometryNode1, nullptr);
    auto size1 = geometryNode1->GetFrameSize();
    auto offset1 = geometryNode1->GetFrameOffset();
    EXPECT_EQ(size1, SizeF(500.0f, 300.0f));
    EXPECT_EQ(offset1, OffsetF(0.0f, 0.0f));
}

/**
 * @tc.name: LayoutPolicyTest002
 * @tc.desc: test the measure result when setting layoutPolicy and other layoutConstraint.
 * @tc.type: FUNC
 */
HWTEST_F(LinearLayoutNewTestNG, LayoutPolicyTest002, TestSize.Level1)
{
    RefPtr<FrameNode> column1, column2, column3;
    auto column = CreateColumn([this, &column1, &column2, &column3](ColumnModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500));
        ViewAbstract::SetHeight(CalcLength(300));
        column1 = CreateColumn([](ColumnModelNG model) {
            ViewAbstract::SetWidth(CalcLength(500));
            ViewAbstract::SetHeight(CalcLength(300));
            ViewAbstract::SetFlexShrink(1);
        });
        column2 = CreateColumn([](ColumnModelNG model) {
            ViewAbstract::SetWidth(CalcLength(500));
            ViewAbstract::SetHeight(CalcLength(300));
            ViewAbstract::SetFlexShrink(2);
        });
        column3 = CreateColumn([](ColumnModelNG model) {
            ViewAbstractModelNG model1;
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, true);
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, false);
            ViewAbstract::SetFlexShrink(2);
        });
    });
    ASSERT_NE(column, nullptr);
    ASSERT_EQ(column->GetChildren().size(), 3);
    CreateLayoutTask(column);

    /* corresponding ets code:
        Column() {
            Column()
                .width(500)
                .height(300)
                .flexShrink(1)
            Column()
                .width(500)
                .height(300)
                .flexShrink(2)
            Column()
                .width(LayoutPolicy.MATCH_PARENT)
                .height(LayoutPolicy.MATCH_PARENT)
                .flexShrink(2)
        }
        .width(500)
        .height(300)
    */

    // Expect column's width is 500, height is 300 and offset is [0.0, 0.0].
    auto geometryNode = column->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(500.0f, 300.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    // Expect column1's width is 500, height is 200 and offset is [0.0, 0.0].
    auto geometryNode1 = column1->GetGeometryNode();
    ASSERT_NE(geometryNode1, nullptr);
    auto size1 = geometryNode1->GetFrameSize();
    auto offset1 = geometryNode1->GetFrameOffset();
    EXPECT_EQ(size1, SizeF(500.0f, 200.0f));
    EXPECT_EQ(offset1, OffsetF(0.0f, 0.0f));

    // Expect column2's width is 500, height is 100 and offset is [0.0, 100.0].
    auto geometryNode2 = column2->GetGeometryNode();
    ASSERT_NE(geometryNode2, nullptr);
    auto size2 = geometryNode2->GetFrameSize();
    auto offset2 = geometryNode2->GetFrameOffset();
    EXPECT_EQ(size2, SizeF(500.0f, 100.0f));
    EXPECT_EQ(offset2, OffsetF(0.0f, 200.0f));

    // Expect column3's width is 500, height is 300 and offset is [0.0, 300.0].
    auto geometryNode3 = column3->GetGeometryNode();
    ASSERT_NE(geometryNode3, nullptr);
    auto size3 = geometryNode3->GetFrameSize();
    auto offset3 = geometryNode3->GetFrameOffset();
    EXPECT_EQ(size3, SizeF(500.0f, 300.0f));
    EXPECT_EQ(offset3, OffsetF(0.0f, 300.0f));
}
} // namespace OHOS::Ace::NG