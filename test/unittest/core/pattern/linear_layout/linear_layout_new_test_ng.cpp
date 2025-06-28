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
#include "test/mock/core/common/mock_container.h"

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

/**
 * @tc.name: LayoutPolicyTest003
 * @tc.desc: test the measure result when setting matchParent.
 * @tc.type: FUNC
 */
HWTEST_F(LinearLayoutNewTestNG, LayoutPolicyTest003, TestSize.Level1)
{
    RefPtr<FrameNode> columnInner;
    auto column = CreateColumn([this, &columnInner](ColumnModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500));
        ViewAbstract::SetHeight(CalcLength(300));
        columnInner = CreateColumn([this](ColumnModelNG model) {
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
            .width(LayoutPolicy.matchParent)
            .height(LayoutPolicy.matchParent)
        }
        .width("500px")
        .height("300px")
    */

    // Expect column's width is 500, height is 300 and offset is [0.0, 0.0].
    auto geometryNode = column->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(500.0f, 300.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    // Expect columnInner's width is 500, height is 300 and offset is [0.0, 0.0].
    auto geometryNode1 = columnInner->GetGeometryNode();
    ASSERT_NE(geometryNode1, nullptr);
    auto size1 = geometryNode1->GetFrameSize();
    auto offset1 = geometryNode1->GetFrameOffset();
    EXPECT_EQ(size1, SizeF(500.0f, 300.0f));
    EXPECT_EQ(offset1, OffsetF(0.0f, 0.0f));
}

/**
 * @tc.name: LayoutPolicyTest004
 * @tc.desc: test the measure result when setting wrapContent.
 * @tc.type: FUNC
 */
HWTEST_F(LinearLayoutNewTestNG, LayoutPolicyTest004, TestSize.Level1)
{
    RefPtr<FrameNode> columnInner;
    auto column = CreateColumn([this, &columnInner](ColumnModelNG model) {
        ViewAbstractModelNG model1;
        model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, true);
        model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, false);
        columnInner = CreateColumn([this](ColumnModelNG model) {
            ViewAbstract::SetWidth(CalcLength(500));
            ViewAbstract::SetHeight(CalcLength(300));
        });
    });
    ASSERT_NE(column, nullptr);
    ASSERT_EQ(column->GetChildren().size(), 1);
    CreateLayoutTask(column);

    /* corresponding ets code:
        Column() {
          Column()
            .width("500px")
            .height("300px")
        }
        .width(LayoutPolicy.wrapContent)
        .height(LayoutPolicy.wrapContent)
    */

    // Expect column's width is 500, height is 300 and offset is [0.0, 0.0].
    auto geometryNode = column->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(500.0f, 300.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    // Expect columnInner's width is 500, height is 300 and offset is [0.0, 0.0].
    auto geometryNode1 = columnInner->GetGeometryNode();
    ASSERT_NE(geometryNode1, nullptr);
    auto size1 = geometryNode1->GetFrameSize();
    auto offset1 = geometryNode1->GetFrameOffset();
    EXPECT_EQ(size1, SizeF(500.0f, 300.0f));
    EXPECT_EQ(offset1, OffsetF(0.0f, 0.0f));
}

/**
 * @tc.name: LayoutPolicyTest005
 * @tc.desc: test the measure result when setting wrapContent and parent has constraint.
 * @tc.type: FUNC
 */
HWTEST_F(LinearLayoutNewTestNG, LayoutPolicyTest005, TestSize.Level1)
{
    RefPtr<FrameNode> columnInner;
    RefPtr<FrameNode> columnOutter;
    RefPtr<FrameNode> column;
    columnOutter = CreateColumn([this, &column, &columnInner](ColumnModelNG model) {
        ViewAbstract::SetWidth(CalcLength(200.0f));
        ViewAbstract::SetHeight(CalcLength(200.0f));
        column = CreateColumn([this, &columnInner](ColumnModelNG model) {
            ViewAbstractModelNG model1;
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, true);
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, false);
            ViewAbstract::SetMaxWidth(CalcLength(150.0f));
            ViewAbstract::SetMaxHeight(CalcLength(300.0f));
            columnInner = CreateColumn([this](ColumnModelNG model) {
                ViewAbstract::SetWidth(CalcLength(300.0f));
                ViewAbstract::SetHeight(CalcLength(400.0f));
            });
        });
    });
    ASSERT_NE(columnOutter, nullptr);
    ASSERT_EQ(columnOutter->GetChildren().size(), 1);
    CreateLayoutTask(columnOutter);

    /* corresponding ets code:
        Column() {
            Column() {
                Column().width("300px").height("400px")
            }
            .width(LayoutPolicy.wrapContent)
            .height(LayoutPolicy.wrapContent)
            .constraintSize({ maxWidth: "150px", maxHeight: "300px" })
        }.width("200px").height("200px")
    */

    // Expect columnOutter's width is 200, height is 200 and offset is [0.0, 0.0].
    auto geometryNodeOutter = columnOutter->GetGeometryNode();
    ASSERT_NE(geometryNodeOutter, nullptr);
    auto sizeOutter = geometryNodeOutter->GetFrameSize();
    auto offsetOutter = geometryNodeOutter->GetFrameOffset();
    EXPECT_EQ(sizeOutter, SizeF(200.0f, 200.0f));
    EXPECT_EQ(offsetOutter, OffsetF(0.0f, 0.0f));

    // Expect column's width is 150, height is 200 and offset is [25.0, 0.0].
    auto geometryNode = column->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(150.0f, 200.0f));
    EXPECT_EQ(offset, OffsetF(25.0f, 0.0f));

    // Expect columnInner's width is 300, height is 400 and offset is [-75.0, -100.0].
    auto geometryNodeInner = columnInner->GetGeometryNode();
    ASSERT_NE(geometryNodeInner, nullptr);
    auto sizeInner = geometryNodeInner->GetFrameSize();
    auto offsetInner = geometryNodeInner->GetFrameOffset();
    EXPECT_EQ(sizeInner, SizeF(300.0f, 400.0f));
    EXPECT_EQ(offsetInner, OffsetF(-75.0f, 0.0f));
}

/**
 * @tc.name: LayoutPolicyTest006
 * @tc.desc: test the measure result when setting fixAtIdealSize.
 * @tc.type: FUNC
 */
HWTEST_F(LinearLayoutNewTestNG, LayoutPolicyTest006, TestSize.Level1)
{
    RefPtr<FrameNode> columnInner;
    auto column = CreateColumn([this, &columnInner](ColumnModelNG model) {
        ViewAbstractModelNG model1;
        model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, true);
        model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, false);
        columnInner = CreateColumn([this](ColumnModelNG model) {
            ViewAbstract::SetWidth(CalcLength(500.0f));
            ViewAbstract::SetHeight(CalcLength(300.0f));
        });
    });
    ASSERT_NE(column, nullptr);
    ASSERT_EQ(column->GetChildren().size(), 1);
    CreateLayoutTask(column);

    /* corresponding ets code:
        Column() {
          Column()
            .width("500px")
            .height("300px")
        }
        .width(LayoutPolicy.fixAtIdealSize)
        .height(LayoutPolicy.fixAtIdealSize)
    */

    // Expect column's width is 500, height is 300 and offset is [0.0, 0.0].
    auto geometryNode = column->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(500.0f, 300.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    // Expect columnInner's width is 500, height is 300 and offset is [0.0, 0.0].
    auto geometryNode1 = columnInner->GetGeometryNode();
    ASSERT_NE(geometryNode1, nullptr);
    auto size1 = geometryNode1->GetFrameSize();
    auto offset1 = geometryNode1->GetFrameOffset();
    EXPECT_EQ(size1, SizeF(500.0f, 300.0f));
    EXPECT_EQ(offset1, OffsetF(0.0f, 0.0f));
}

/**
 * @tc.name: LayoutPolicyTest007
 * @tc.desc: test the measure result when setting fixAtIdealSize and parent has constraint.
 * @tc.type: FUNC
 */
HWTEST_F(LinearLayoutNewTestNG, LayoutPolicyTest007, TestSize.Level1)
{
    RefPtr<FrameNode> columnInner;
    RefPtr<FrameNode> columnOutter;
    RefPtr<FrameNode> column;
    columnOutter = CreateColumn([this, &column, &columnInner](ColumnModelNG model) {
        ViewAbstract::SetWidth(CalcLength(200.0f));
        ViewAbstract::SetHeight(CalcLength(200.0f));
        column = CreateColumn([this, &columnInner](ColumnModelNG model) {
            ViewAbstractModelNG model1;
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, true);
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, false);
            ViewAbstract::SetMaxWidth(CalcLength(150.0f));
            ViewAbstract::SetMaxHeight(CalcLength(300.0f));
            columnInner = CreateColumn([this](ColumnModelNG model) {
                ViewAbstract::SetWidth(CalcLength(300.0f));
                ViewAbstract::SetHeight(CalcLength(400.0f));
            });
        });
    });
    ASSERT_NE(columnOutter, nullptr);
    ASSERT_EQ(columnOutter->GetChildren().size(), 1);
    CreateLayoutTask(columnOutter);

    /* corresponding ets code:
        Column() {
            Column() {
                Column().width("300px").height("400px")
            }
            .width(LayoutPolicy.fixAtIdealSize)
            .height(LayoutPolicy.fixAtIdealSize)
            .constraintSize({ maxWidth: "150px", maxHeight: "300px" })
        }.width("200px").height("200px")
    */

    // Expect columnOutter's width is 200, height is 200 and offset is [0.0, 0.0].
    auto geometryNodeOutter = columnOutter->GetGeometryNode();
    ASSERT_NE(geometryNodeOutter, nullptr);
    auto sizeOutter = geometryNodeOutter->GetFrameSize();
    auto offsetOutter = geometryNodeOutter->GetFrameOffset();
    EXPECT_EQ(sizeOutter, SizeF(200.0f, 200.0f));
    EXPECT_EQ(offsetOutter, OffsetF(0.0f, 0.0f));

    // Expect column's width is 150, height is 300 and offset is [25.0, -50.0].
    auto geometryNode = column->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(150.0f, 300.0f));
    EXPECT_EQ(offset, OffsetF(25.0f, 0.0f));

    // Expect columnInner's width is 300, height is 400 and offset is [-75.0, -50.0].
    auto geometryNodeInner = columnInner->GetGeometryNode();
    ASSERT_NE(geometryNodeInner, nullptr);
    auto sizeInner = geometryNodeInner->GetFrameSize();
    auto offsetInner = geometryNodeInner->GetFrameOffset();
    EXPECT_EQ(sizeInner, SizeF(300.0f, 400.0f));
    EXPECT_EQ(offsetInner, OffsetF(-75.0f, 0.0f));
}

/**
 * @tc.name: LinearIgnoreLayoutSafeArea001
 * @tc.desc: test linear ignoreLayoutSafeArea
 * @tc.type: FUNC
 */
HWTEST_F(LinearLayoutNewTestNG, LinearIgnoreLayoutSafeArea001, TestSize.Level1)
{
    RefPtr<FrameNode> row1;
    RefPtr<FrameNode> row2;

    auto frameNode = CreateRow([this, &row1, &row2](RowModelNG model) {
        ViewAbstract::SetWidth(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetSafeAreaPadding(CalcLength(10.0f, DimensionUnit::PX));

        row1 = CreateRow([this](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(50.0f, DimensionUnit::PX));
        });
        row2 = CreateRow([this](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(50.0f, DimensionUnit::PX));
        });
    });
    IgnoreLayoutSafeAreaOpts opts = {.type = NG::LAYOUT_SAFE_AREA_TYPE_SYSTEM, .edges = NG::LAYOUT_SAFE_AREA_EDGE_ALL};
    row1->GetLayoutProperty()->UpdateIgnoreLayoutSafeAreaOpts(opts);
    auto layoutWrapper = AceType::DynamicCast<LayoutWrapper>(frameNode);
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutProperty = AceType::DynamicCast<FlexLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateCrossAxisAlign(FlexAlign::FLEX_START);
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks(frameNode);
    EXPECT_EQ(row1->GetGeometryNode()->GetFrameSize(), SizeF(100.0f, 50.0f));
    EXPECT_EQ(row1->GetGeometryNode()->GetFrameOffset(), OffsetF(0.0f, 0.0f));
    EXPECT_EQ(row2->GetGeometryNode()->GetFrameSize(), SizeF(100.0f, 50.0f));
    EXPECT_EQ(row2->GetGeometryNode()->GetFrameOffset(), OffsetF(110.0f, 10.0f));
}


/**
 * @tc.name: LinearIgnoreLayoutSafeArea002
 * @tc.desc: test linear ignoreLayoutSafeArea
 * @tc.type: FUNC
 */
HWTEST_F(LinearLayoutNewTestNG, LinearIgnoreLayoutSafeArea002, TestSize.Level1)
{
    RefPtr<FrameNode> row1;
    RefPtr<FrameNode> row2;

    auto frameNode = CreateRow([this, &row1, &row2](RowModelNG model) {
        ViewAbstract::SetWidth(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetSafeAreaPadding(CalcLength(10.0f, DimensionUnit::PX));

        row1 = CreateRow([this](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(50.0f, DimensionUnit::PX));
        });
        row2 = CreateRow([this](RowModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(50.0f, DimensionUnit::PX));
        });
    });
    IgnoreLayoutSafeAreaOpts opts = {.type = NG::LAYOUT_SAFE_AREA_TYPE_SYSTEM, .edges = NG::LAYOUT_SAFE_AREA_EDGE_ALL};
    row1->GetLayoutProperty()->UpdateIgnoreLayoutSafeAreaOpts(opts);
    auto layoutWrapper = AceType::DynamicCast<LayoutWrapper>(frameNode);
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutProperty = AceType::DynamicCast<FlexLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateIsReverse(true);
    layoutProperty->UpdateCrossAxisAlign(FlexAlign::FLEX_START);
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks(frameNode);
    EXPECT_EQ(row1->GetGeometryNode()->GetFrameSize(), SizeF(100.0f, 50.0f));
    EXPECT_EQ(row1->GetGeometryNode()->GetFrameOffset(), OffsetF(200.0f, 0.0f));
    EXPECT_EQ(row2->GetGeometryNode()->GetFrameSize(), SizeF(100.0f, 50.0f));
    EXPECT_EQ(row2->GetGeometryNode()->GetFrameOffset(), OffsetF(90.0f, 10.0f));
}

/**
 * @tc.name: LinearIgnoreLayoutSafeArea003
 * @tc.desc: test linear ignoreLayoutSafeArea
 * @tc.type: FUNC
 */
HWTEST_F(LinearLayoutNewTestNG, LinearIgnoreLayoutSafeArea003, TestSize.Level1)
{
    RefPtr<FrameNode> column1;
    RefPtr<FrameNode> column2;

    auto frameNode = CreateColumn([this, &column1, &column2](ColumnModelNG model) {
        ViewAbstract::SetWidth(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetSafeAreaPadding(CalcLength(10.0f, DimensionUnit::PX));

        column1 = CreateColumn([this](ColumnModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(50.0f, DimensionUnit::PX));
        });
        column2 = CreateColumn([this](ColumnModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(50.0f, DimensionUnit::PX));
        });
    });
    IgnoreLayoutSafeAreaOpts opts = {.type = NG::LAYOUT_SAFE_AREA_TYPE_SYSTEM, .edges = NG::LAYOUT_SAFE_AREA_EDGE_ALL};
    column1->GetLayoutProperty()->UpdateIgnoreLayoutSafeAreaOpts(opts);
    auto layoutWrapper = AceType::DynamicCast<LayoutWrapper>(frameNode);
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutProperty = AceType::DynamicCast<FlexLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateCrossAxisAlign(FlexAlign::FLEX_START);
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks(frameNode);
    EXPECT_EQ(column1->GetGeometryNode()->GetFrameSize(), SizeF(100.0f, 50.0f));
    EXPECT_EQ(column1->GetGeometryNode()->GetFrameOffset(), OffsetF(0.0f, 0.0f));
    EXPECT_EQ(column2->GetGeometryNode()->GetFrameSize(), SizeF(100.0f, 50.0f));
    EXPECT_EQ(column2->GetGeometryNode()->GetFrameOffset(), OffsetF(10.0f, 60.0f));
}

/**
 * @tc.name: LinearIgnoreLayoutSafeArea004
 * @tc.desc: test linear ignoreLayoutSafeArea
 * @tc.type: FUNC
 */
HWTEST_F(LinearLayoutNewTestNG, LinearIgnoreLayoutSafeArea004, TestSize.Level1)
{
    RefPtr<FrameNode> column1;
    RefPtr<FrameNode> column2;

    auto frameNode = CreateColumn([this, &column1, &column2](ColumnModelNG model) {
        ViewAbstract::SetWidth(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetSafeAreaPadding(CalcLength(10.0f, DimensionUnit::PX));

        column1 = CreateColumn([this](ColumnModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(50.0f, DimensionUnit::PX));
        });
        column2 = CreateColumn([this](ColumnModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(50.0f, DimensionUnit::PX));
        });
    });
    IgnoreLayoutSafeAreaOpts opts = {.type = NG::LAYOUT_SAFE_AREA_TYPE_SYSTEM, .edges = NG::LAYOUT_SAFE_AREA_EDGE_ALL};
    column1->GetLayoutProperty()->UpdateIgnoreLayoutSafeAreaOpts(opts);
    auto layoutWrapper = AceType::DynamicCast<LayoutWrapper>(frameNode);
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutProperty = AceType::DynamicCast<FlexLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateCrossAxisAlign(FlexAlign::FLEX_END);
    layoutProperty->UpdateMainAxisAlign(FlexAlign::FLEX_END);
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks(frameNode);
    EXPECT_EQ(column1->GetGeometryNode()->GetFrameSize(), SizeF(100.0f, 50.0f));
    EXPECT_EQ(column1->GetGeometryNode()->GetFrameOffset(), OffsetF(200.0f, 190.0f));
    EXPECT_EQ(column2->GetGeometryNode()->GetFrameSize(), SizeF(100.0f, 50.0f));
    EXPECT_EQ(column2->GetGeometryNode()->GetFrameOffset(), OffsetF(190.0f, 240.0f));
}
} // namespace OHOS::Ace::NG