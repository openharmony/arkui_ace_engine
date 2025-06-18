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
#include <cstddef>

#include "stack_base_test_ng.h"

#include "base/memory/ace_type.h"
#include "core/components_ng/animation/geometry_transition.h"
#include "core/components_ng/pattern/text/text_model_ng.h"

namespace OHOS::Ace::NG {
namespace {
const int32_t FIRST_CHILD = 0;
const int32_t SECOND_CHILD = 1;
} // namespace
class StackNewTestNG : public StackBaseTestNG {};

/**
 * @tc.name: Example
 * @tc.desc: Show an example of creating a test case.
 * @tc.type: ETS
 */
HWTEST_F(StackNewTestNG, Example, TestSize.Level1)
{
    // If this test is related to api versions, need to SetMinPlatformVersion
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetMinPlatformVersion(12);
    /**
    corresponding ets code:

    Stack({ alignContent: Alignment.Bottom }) {
      Text('First child, show in bottom')
       .width('90%')
       .height('100%')
       .backgroundColor(0xd2cab3)
       .align(Alignment.Top)
      Text('Second child, show in top')
       .width('70%')
       .height('60%')
       .backgroundColor(0xc1cbac)
       .align(Alignment.Top)
    }
     .width('300px')
     .height('300px')
    */
    auto frameNode = CreateStack([this](StackModelNG model) {
        // step: set alignContent: Alignment.Bottom
        ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, Alignment, Alignment::BOTTOM_CENTER);

        // step: set stack common attribute
        ViewAbstract::SetWidth(CalcLength(300.0f));
        ViewAbstract::SetHeight(CalcLength(300.0f));

        // step: create child nodes
        auto textBottom = CreateText(u"First child, show in bottom", [this](TextModelNG model) {
            ViewAbstract::SetWidth(CalcLength(Dimension(90 / 100.0, DimensionUnit::PERCENT)));
            ViewAbstract::SetHeight(CalcLength(Dimension(100 / 100.0, DimensionUnit::PERCENT)));
            ViewAbstract::SetInspectorId("bottom");
        });
        auto textTop = CreateText(u"Second child, show in top", [this](TextModelNG model) {
            ViewAbstract::SetWidth(CalcLength(Dimension(70 / 100.0, DimensionUnit::PERCENT)));
            ViewAbstract::SetHeight(CalcLength(Dimension(60 / 100.0, DimensionUnit::PERCENT)));
            ViewAbstract::SetInspectorId("top");
        });
    });
    ASSERT_EQ(frameNode->GetChildren().size(), 2);
    CreateLayoutTask(frameNode);

    // expect: the second created node is the second child node
    auto second = OHOS::Ace::AceType::DynamicCast<OHOS::Ace::NG::FrameNode>(frameNode->GetChildByIndex(SECOND_CHILD));
    ASSERT_NE(second, nullptr);
    EXPECT_EQ(second->GetInspectorId(), "top");
    // expect: textBottom offset = (x, y) = (300px*(1-0.9)/2, 0) = (15px, 0)
    EXPECT_EQ(frameNode->GetChildByIndex(FIRST_CHILD)->GetGeometryNode()->GetFrameOffset().GetX(), 15.0f);
    EXPECT_EQ(frameNode->GetChildByIndex(FIRST_CHILD)->GetGeometryNode()->GetFrameOffset().GetY(), 0.0f);
    // expect: textTop offset = (x, y) = (300px*0.3/2, 300px*(1-0.6)) = (45px, 120px)
    EXPECT_EQ(frameNode->GetChildByIndex(SECOND_CHILD)->GetGeometryNode()->GetFrameOffset().GetX(), 45.0f);
    EXPECT_EQ(frameNode->GetChildByIndex(SECOND_CHILD)->GetGeometryNode()->GetFrameOffset().GetY(), 120.0f);
}
/**
 * @tc.name: StackIgnoreLayoutSafeArea001
 * @tc.desc: test stack ignoreLayoutSafeArea
 * @tc.type: FUNC
 */
HWTEST_F(StackNewTestNG, StackIgnoreLayoutSafeArea001, TestSize.Level1)
{
    RefPtr<FrameNode> text;

    auto frameNode = CreateStack([this, &text](StackModelNG model) {
        ViewAbstract::SetWidth(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetSafeAreaPadding(CalcLength(10.0f, DimensionUnit::PX));

        text = CreateText(u"Text", [this](TextModelNG model) {
            ViewAbstract::SetWidth(CalcLength(100.0f, DimensionUnit::PX));
            ViewAbstract::SetHeight(CalcLength(50.0f, DimensionUnit::PX));
        });
    });
    IgnoreLayoutSafeAreaOpts opts = { .type = NG::LAYOUT_SAFE_AREA_TYPE_SYSTEM,
        .edges = NG::LAYOUT_SAFE_AREA_EDGE_ALL };
    text->GetLayoutProperty()->UpdateIgnoreLayoutSafeAreaOpts(opts);
    auto layoutWrapper = AceType::DynamicCast<LayoutWrapper>(frameNode);
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateAlignment(Alignment::TOP_LEFT);
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks(frameNode);
    EXPECT_EQ(text->GetGeometryNode()->GetFrameSize(), SizeF(100.0f, 50.0F));
    EXPECT_EQ(text->GetGeometryNode()->GetFrameOffset(), OffsetF(0.0f, 0.0F));
}

/**
 * @tc.name: StackIgnoreLayoutSafeArea002
 * @tc.desc: test stack ignoreLayoutSafeArea
 * @tc.type: FUNC
 */
HWTEST_F(StackNewTestNG, StackIgnoreLayoutSafeArea002, TestSize.Level1)
{
    RefPtr<FrameNode> stack1;
    RefPtr<FrameNode> stack2;

    auto frameNode = CreateStack([this, &stack1, &stack2](StackModelNG model) {
        ViewAbstract::SetWidth(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetHeight(CalcLength(300.0f, DimensionUnit::PX));
        ViewAbstract::SetSafeAreaPadding(CalcLength(10.0f, DimensionUnit::PX));
        stack1 = CreateStack([this, &stack2](StackModelNG model) {
            ViewAbstract::SetWidth(CalcLength(1.0f, DimensionUnit::PERCENT));
            ViewAbstract::SetHeight(CalcLength(1.0f, DimensionUnit::PERCENT));
            ViewAbstract::SetSafeAreaPadding(CalcLength(10.0f, DimensionUnit::PX));
            stack2 = CreateStack( [this](StackModelNG model) {});
        });
    });
    auto childLayoutProperty = stack2->GetLayoutProperty();
    ASSERT_NE(childLayoutProperty, nullptr);
    childLayoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, false);
    childLayoutProperty->UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, true);
    IgnoreLayoutSafeAreaOpts opts = { .type = NG::LAYOUT_SAFE_AREA_TYPE_SYSTEM,
        .edges = NG::LAYOUT_SAFE_AREA_EDGE_ALL };
    childLayoutProperty->UpdateIgnoreLayoutSafeAreaOpts(opts);
    auto layoutWrapper = AceType::DynamicCast<LayoutWrapper>(frameNode);
    ASSERT_NE(layoutWrapper, nullptr);
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateAlignment(Alignment::BOTTOM_RIGHT);
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks(frameNode);
    EXPECT_EQ(stack2->GetGeometryNode()->GetFrameSize(), SizeF(300.0f, 300.0f));
    EXPECT_EQ(stack2->GetGeometryNode()->GetFrameOffset(), OffsetF(-10.0f, -10.0f));
    EXPECT_EQ(stack1->GetGeometryNode()->GetFrameSize(), SizeF(280.0f, 280.0f));
    EXPECT_EQ(stack1->GetGeometryNode()->GetFrameOffset(), OffsetF(10.0f, 10.0f));
}

/**
 * @tc.name: LayoutPolicyTest001
 * @tc.desc: test the measure result when setting matchParent.
 * @tc.type: FUNC
 */
HWTEST_F(StackNewTestNG, LayoutPolicyTest001, TestSize.Level1)
{
    RefPtr<FrameNode> stackInner;
    auto stack = CreateStack([this, &stackInner](StackModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500));
        ViewAbstract::SetHeight(CalcLength(300));
        stackInner = CreateStack([this](StackModelNG model) {
            ViewAbstractModelNG model1;
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, true);
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, false);
        });
    });
    ASSERT_NE(stack, nullptr);
    ASSERT_EQ(stack->GetChildren().size(), 1);
    CreateLayoutTask(stack);

    /* corresponding ets code:
        Stack() {
          Stack()
            .width(LayoutPolicy.MATCH_PARENT)
            .height(LayoutPolicy.MATCH_PARENT)
        }
        .width("500px")
        .height("300px")
    */

    // Expect stack's width is 500, height is 300 and offset is [0.0, 0.0].
    auto geometryNode = stack->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(500.0f, 300.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    // Expect stackInner's width is 500, height is 300 and offset is [0.0, 0.0].
    auto geometryNode1 = stackInner->GetGeometryNode();
    ASSERT_NE(geometryNode1, nullptr);
    auto size1 = geometryNode1->GetFrameSize();
    auto offset1 = geometryNode1->GetFrameOffset();
    EXPECT_EQ(size1, SizeF(500.0f, 300.0f));
    EXPECT_EQ(offset1, OffsetF(0.0f, 0.0f));
}

/**
 * @tc.name: LayoutPolicyTest002
 * @tc.desc: test the measure result when setting matchParent and parent has padding.
 * @tc.type: FUNC
 */
HWTEST_F(StackNewTestNG, LayoutPolicyTest002, TestSize.Level1)
{
    RefPtr<FrameNode> stackInner;
    auto stack = CreateStack([this, &stackInner](StackModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500));
        ViewAbstract::SetHeight(CalcLength(300));
        ViewAbstract::SetPadding(CalcLength(20));
        stackInner = CreateStack([this](StackModelNG model) {
            ViewAbstractModelNG model1;
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, true);
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, false);
        });
    });
    ASSERT_NE(stack, nullptr);
    ASSERT_EQ(stack->GetChildren().size(), 1);
    CreateLayoutTask(stack);

    /* corresponding ets code:
        Stack() {
          Stack()
            .width(LayoutPolicy.MATCH_PARENT)
            .height(LayoutPolicy.MATCH_PARENT)
        }
        .width("500px")
        .height("300px")
        .padding("20px")
    */

    // Expect stack's width is 500, height is 300 and offset is [0.0, 0.0].
    auto geometryNode = stack->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(500.0f, 300.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    // Expect stackInner's width is 460, height is 260 and offset is [20.0, 20.0].
    auto geometryNode1 = stackInner->GetGeometryNode();
    ASSERT_NE(geometryNode1, nullptr);
    auto size1 = geometryNode1->GetFrameSize();
    auto offset1 = geometryNode1->GetFrameOffset();
    EXPECT_EQ(size1, SizeF(460.0f, 260.0f));
    EXPECT_EQ(offset1, OffsetF(20.0f, 20.0f));
}

/**
 * @tc.name: LayoutPolicyTest003
 * @tc.desc: test the measure result when setting wrapContent.
 * @tc.type: FUNC
 */
HWTEST_F(StackNewTestNG, LayoutPolicyTest003, TestSize.Level1)
{
    RefPtr<FrameNode> stackInner;
    auto stack = CreateStack([this, &stackInner](StackModelNG model) {
        ViewAbstractModelNG model1;
        model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, true);
        model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, false);
        stackInner = CreateStack([this](StackModelNG model) {
            ViewAbstract::SetWidth(CalcLength(500));
            ViewAbstract::SetHeight(CalcLength(300));
        });
    });
    ASSERT_NE(stack, nullptr);
    ASSERT_EQ(stack->GetChildren().size(), 1);
    CreateLayoutTask(stack);

    /* corresponding ets code:
        Stack() {
          Stack()
            .width("500px")
            .height("300px")
        }
        .width(LayoutPolicy.WRAP_CONTENT)
        .height(LayoutPolicy.WRAP_CONTENT)
    */

    // Expect stack's width is 500, height is 300 and offset is [0.0, 0.0].
    auto geometryNode = stack->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(500.0f, 300.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    // Expect stackInner's width is 500, height is 300 and offset is [0.0, 0.0].
    auto geometryNode1 = stackInner->GetGeometryNode();
    ASSERT_NE(geometryNode1, nullptr);
    auto size1 = geometryNode1->GetFrameSize();
    auto offset1 = geometryNode1->GetFrameOffset();
    EXPECT_EQ(size1, SizeF(500.0f, 300.0f));
    EXPECT_EQ(offset1, OffsetF(0.0f, 0.0f));
}

/**
 * @tc.name: LayoutPolicyTest004
 * @tc.desc: test the measure result when setting wrapContent and parent has constraint.
 * @tc.type: FUNC
 */
HWTEST_F(StackNewTestNG, LayoutPolicyTest004, TestSize.Level1)
{
    RefPtr<FrameNode> stackInner;
    RefPtr<FrameNode> stackOutter;
    RefPtr<FrameNode> stack;
    stackOutter = CreateStack([this, &stack, &stackInner](StackModelNG model) {
        ViewAbstract::SetWidth(CalcLength(200.0f));
        ViewAbstract::SetHeight(CalcLength(200.0f));
        stack = CreateStack([this, &stackInner](StackModelNG model) {
            ViewAbstractModelNG model1;
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, true);
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, false);
            ViewAbstract::SetMaxWidth(CalcLength(150.0f));
            ViewAbstract::SetMaxHeight(CalcLength(300.0f));
            stackInner = CreateStack([this](StackModelNG model) {
                ViewAbstract::SetWidth(CalcLength(300.0f));
                ViewAbstract::SetHeight(CalcLength(400.0f));
            });
        });
    });
    ASSERT_NE(stackOutter, nullptr);
    ASSERT_EQ(stackOutter->GetChildren().size(), 1);
    CreateLayoutTask(stackOutter);

    /* corresponding ets code:
        Stack() {
            Stack() {
                Stack().width("300px").height("400px")
            }
            .width(LayoutPolicy.wrapContent)
            .height(LayoutPolicy.wrapContent)
            .constraintSize({ maxWidth: "150px", maxHeight: "300px" })
        }.width("200px").height("200px")
    */

    // Expect stackOutter's width is 200, height is 200 and offset is [0.0, 0.0].
    auto geometryNodeOutter = stackOutter->GetGeometryNode();
    ASSERT_NE(geometryNodeOutter, nullptr);
    auto sizeOutter = geometryNodeOutter->GetFrameSize();
    auto offsetOutter = geometryNodeOutter->GetFrameOffset();
    EXPECT_EQ(sizeOutter, SizeF(200.0f, 200.0f));
    EXPECT_EQ(offsetOutter, OffsetF(0.0f, 0.0f));

    // Expect stack's width is 150, height is 200 and offset is [25.0, 0.0].
    auto geometryNode = stack->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(150.0f, 200.0f));
    EXPECT_EQ(offset, OffsetF(25.0f, 0.0f));

    // Expect stackInner's width is 300, height is 400 and offset is [-75.0, -100.0].
    auto geometryNodeInner = stackInner->GetGeometryNode();
    ASSERT_NE(geometryNodeInner, nullptr);
    auto sizeInner = geometryNodeInner->GetFrameSize();
    auto offsetInner = geometryNodeInner->GetFrameOffset();
    EXPECT_EQ(sizeInner, SizeF(300.0f, 400.0f));
    EXPECT_EQ(offsetInner, OffsetF(-75.0f, -100.0f));
}

/**
 * @tc.name: LayoutPolicyTest005
 * @tc.desc: test the measure result when setting fixAtIdealSize.
 * @tc.type: FUNC
 */
HWTEST_F(StackNewTestNG, LayoutPolicyTest005, TestSize.Level1)
{
    RefPtr<FrameNode> stackInner;
    auto stack = CreateStack([this, &stackInner](StackModelNG model) {
        ViewAbstractModelNG model1;
        model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, true);
        model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, false);
        stackInner = CreateStack([this](StackModelNG model) {
            ViewAbstract::SetWidth(CalcLength(500.0f));
            ViewAbstract::SetHeight(CalcLength(300.0f));
        });
    });
    ASSERT_NE(stack, nullptr);
    ASSERT_EQ(stack->GetChildren().size(), 1);
    CreateLayoutTask(stack);

    /* corresponding ets code:
        Stack() {
          Stack()
            .width("500px")
            .height("300px")
        }
        .width(LayoutPolicy.fixAtIdealSize)
        .height(LayoutPolicy.fixAtIdealSize)
    */

    // Expect stack's width is 500, height is 300 and offset is [0.0, 0.0].
    auto geometryNode = stack->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(500.0f, 300.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    // Expect stackInner's width is 500, height is 300 and offset is [0.0, 0.0].
    auto geometryNode1 = stackInner->GetGeometryNode();
    ASSERT_NE(geometryNode1, nullptr);
    auto size1 = geometryNode1->GetFrameSize();
    auto offset1 = geometryNode1->GetFrameOffset();
    EXPECT_EQ(size1, SizeF(500.0f, 300.0f));
    EXPECT_EQ(offset1, OffsetF(0.0f, 0.0f));
}

/**
 * @tc.name: LayoutPolicyTest006
 * @tc.desc: test the measure result when setting fixAtIdealSize and parent has constraint.
 * @tc.type: FUNC
 */
HWTEST_F(StackNewTestNG, LayoutPolicyTest006, TestSize.Level1)
{
    RefPtr<FrameNode> stackInner;
    RefPtr<FrameNode> stackOutter;
    RefPtr<FrameNode> stack;
    stackOutter = CreateStack([this, &stack, &stackInner](StackModelNG model) {
        ViewAbstract::SetWidth(CalcLength(200.0f));
        ViewAbstract::SetHeight(CalcLength(200.0f));
        stack = CreateStack([this, &stackInner](StackModelNG model) {
            ViewAbstractModelNG model1;
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, true);
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, false);
            ViewAbstract::SetMaxWidth(CalcLength(150.0f));
            ViewAbstract::SetMaxHeight(CalcLength(300.0f));
            stackInner = CreateStack([this](StackModelNG model) {
                ViewAbstract::SetWidth(CalcLength(300.0f));
                ViewAbstract::SetHeight(CalcLength(400.0f));
            });
        });
    });
    ASSERT_NE(stackOutter, nullptr);
    ASSERT_EQ(stackOutter->GetChildren().size(), 1);
    CreateLayoutTask(stackOutter);

    /* corresponding ets code:
        Stack() {
            Stack() {
                Flex().width("300px").height("400px")
            }
            .width(LayoutPolicy.fixAtIdealSize)
            .height(LayoutPolicy.fixAtIdealSize)
            .constraintSize({ maxWidth: "150px", maxHeight: "300px" })
        }.width("200px").height("200px")
    */

    // Expect stackOutter's width is 200, height is 200 and offset is [0.0, 0.0].
    auto geometryNodeOutter = stackOutter->GetGeometryNode();
    ASSERT_NE(geometryNodeOutter, nullptr);
    auto sizeOutter = geometryNodeOutter->GetFrameSize();
    auto offsetOutter = geometryNodeOutter->GetFrameOffset();
    EXPECT_EQ(sizeOutter, SizeF(200.0f, 200.0f));
    EXPECT_EQ(offsetOutter, OffsetF(0.0f, 0.0f));

    // Expect stack's width is 150, height is 300 and offset is [25.0, -50.0].
    auto geometryNode = stack->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(150.0f, 300.0f));
    EXPECT_EQ(offset, OffsetF(25.0f, -50.0f));

    // Expect stackInner's width is 300, height is 400 and offset is [-75.0, -50.0].
    auto geometryNodeInner = stackInner->GetGeometryNode();
    ASSERT_NE(geometryNodeInner, nullptr);
    auto sizeInner = geometryNodeInner->GetFrameSize();
    auto offsetInner = geometryNodeInner->GetFrameOffset();
    EXPECT_EQ(sizeInner, SizeF(300.0f, 400.0f));
    EXPECT_EQ(offsetInner, OffsetF(-75.0f, -50.0f));
}

/**
 * @tc.name: LayoutGravityTest
 * @tc.desc: Test stack Layout with LayoutGravityTest
 * @tc.type: FUNC
 */
HWTEST_F(StackNewTestNG, LayoutGravityTest, TestSize.Level1)
{
    auto frameNode = CreateStack([this](StackModelNG model) {
        ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, Alignment, Alignment::BOTTOM_CENTER);
        auto text = CreateText(
            u"First child", [this](TextModelNG model) { ViewAbstract::SetLayoutGravity(Alignment::CENTER_RIGHT); });
    });
    CreateLayoutTask(frameNode);
    auto textFrameNode = frameNode->GetChildByIndex(FIRST_CHILD);
    ASSERT_NE(textFrameNode, nullptr);
    auto textLayoutProperty = textFrameNode->GetLayoutProperty();
    ASSERT_NE(textLayoutProperty, nullptr);
    ASSERT_NE(textLayoutProperty->GetPositionProperty(), nullptr);
    EXPECT_EQ(textLayoutProperty->GetPositionProperty()->GetLayoutGravity().value(), Alignment::CENTER_RIGHT);
}
} // namespace OHOS::Ace::NG