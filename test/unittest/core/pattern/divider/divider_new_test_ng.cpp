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
#include "divider_base_test_ng.h"

#include "core/components_ng/property/layout_constraint.h"
#include "frameworks/base/memory/ace_type.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;

namespace {} // namespace
class DividerNewTestNG : public DividerBaseTestNG {};

/**
 * @tc.name: DividerLengthTests
 * @tc.desc: percentRef > maxSize, horizontal.
 * @tc.type: FUNC
 */
HWTEST_F(DividerNewTestNG, DividerLengthTest01, TestSize.Level0)
{
    // step: make percentRef > maxSize
    OHOS::Ace::NG::LayoutConstraintF parentConstraint;
    parentConstraint.maxSize = SizeF(200, 200);
    parentConstraint.percentReference = SizeF(300, 300);

    auto frameNode = CreateDivider([this](DividerModelNG model) {});
    frameNode->GetGeometryNode()->SetParentLayoutConstraint(parentConstraint);
    CreateLayoutTask(frameNode);

    auto pattern = OHOS::Ace::AceType::DynamicCast<DividerPattern>(frameNode->GetPattern());

    // expect: divider length = 200
    EXPECT_EQ(pattern->dividerLength_, 200.0f);
}

/**
 * @tc.name: DividerLengthTests
 * @tc.desc: percentRef > maxSize, vertical
 * @tc.type: FUNC
 */
HWTEST_F(DividerNewTestNG, DividerLengthTest02, TestSize.Level0)
{
    // step: make percentRef > maxSize
    OHOS::Ace::NG::LayoutConstraintF parentConstraint;
    parentConstraint.maxSize = SizeF(200, 100);
    parentConstraint.percentReference = SizeF(300, 300);

    auto frameNode = CreateDivider([this](DividerModelNG model) { model.Vertical(true); });
    frameNode->GetGeometryNode()->SetParentLayoutConstraint(parentConstraint);
    CreateLayoutTask(frameNode);

    auto pattern = OHOS::Ace::AceType::DynamicCast<DividerPattern>(frameNode->GetPattern());
    EXPECT_EQ(pattern->dividerLength_, 100.0f);
}

/**
 * @tc.name: LayoutPolicyTest001
 * @tc.desc: test the measure result when setting matchParent.
 * @tc.type: FUNC
 */
HWTEST_F(DividerNewTestNG, LayoutPolicyTest001, TestSize.Level0)
{
    RefPtr<FrameNode> divider;
    auto stack = CreateStack([this, &divider](StackModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500));
        ViewAbstract::SetHeight(CalcLength(300));
        divider = CreateDivider([this](DividerModelNG model) {
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
          Divider()
            .width(LayoutPolicy.matchParent)
            .height(LayoutPolicy.matchParent)
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

    // Expect divider's width is 500, height is 300 and offset is [0.0, 0.0].
    auto geometryNode1 = divider->GetGeometryNode();
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
HWTEST_F(DividerNewTestNG, LayoutPolicyTest002, TestSize.Level0)
{
    RefPtr<FrameNode> divider;
    auto stack = CreateStack([this, &divider](StackModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500));
        ViewAbstract::SetHeight(CalcLength(300));
        ViewAbstract::SetPadding(CalcLength(20));
        divider = CreateDivider([this](DividerModelNG model) {
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
          Divider()
            .width(LayoutPolicy.matchParent)
            .height(LayoutPolicy.matchParent)
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

    // Expect divider's width is 460, height is 260 and offset is [20.0, 20.0].
    auto geometryNode1 = divider->GetGeometryNode();
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
HWTEST_F(DividerNewTestNG, LayoutPolicyTest003, TestSize.Level0)
{
    RefPtr<FrameNode> divider;
    auto stack = CreateStack([this, &divider](StackModelNG model) {
        ViewAbstract::SetWidth(CalcLength(200));
        ViewAbstract::SetHeight(CalcLength(200));
        divider = CreateDivider([this](DividerModelNG model) {
            ViewAbstractModelNG model1;
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, true);
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, false);
            model.StrokeWidth(Dimension(20));
        });
    });
    ASSERT_NE(stack, nullptr);
    ASSERT_EQ(stack->GetChildren().size(), 1);
    CreateLayoutTask(stack);

    /* corresponding ets code:
        Stack() {
          Divider()
            .strokeWidth("20px")
            .width(LayoutPolicy.wrapContent)
            .height(LayoutPolicy.wrapContent)
        }
        .width("200px")
        .height("200px")
    */

    // Expect stack's width is 200, height is 200 and offset is [0.0, 0.0].
    auto geometryNode = stack->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(200.0f, 200.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    // Expect divider's width is 0, height is 20 and offset is [100.0, 90.0].
    auto geometryNode1 = divider->GetGeometryNode();
    ASSERT_NE(geometryNode1, nullptr);
    auto size1 = geometryNode1->GetFrameSize();
    auto offset1 = geometryNode1->GetFrameOffset();
    EXPECT_EQ(size1, SizeF(0.0f, 20.0f));
    EXPECT_EQ(offset1, OffsetF(100.0f, 90.0f));
}

/**
 * @tc.name: LayoutPolicyTest004
 * @tc.desc: test the measure result when setting wrapContent.
 * @tc.type: FUNC
 */
HWTEST_F(DividerNewTestNG, LayoutPolicyTest004, TestSize.Level0)
{
    RefPtr<FrameNode> divider;
    auto stack = CreateStack([this, &divider](StackModelNG model) {
        ViewAbstract::SetWidth(CalcLength(200));
        ViewAbstract::SetHeight(CalcLength(200));
        divider = CreateDivider([this](DividerModelNG model) {
            ViewAbstractModelNG model1;
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, true);
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, false);
            model.Vertical(true);
            model.StrokeWidth(Dimension(20));
        });
    });
    ASSERT_NE(stack, nullptr);
    ASSERT_EQ(stack->GetChildren().size(), 1);
    CreateLayoutTask(stack);

    /* corresponding ets code:
        Stack() {
          Divider()
            .strokeWidth("20px")
            .width(LayoutPolicy.wrapContent)
            .height(LayoutPolicy.wrapContent)
            .vertical(true)
        }
        .width("200px")
        .height("200px")
    */

    // Expect stack's width is 200, height is 200 and offset is [0.0, 0.0].
    auto geometryNode = stack->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(200.0f, 200.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    // Expect divider's width is 20, height is 0 and offset is [90.0, 100.0].
    auto geometryNode1 = divider->GetGeometryNode();
    ASSERT_NE(geometryNode1, nullptr);
    auto size1 = geometryNode1->GetFrameSize();
    auto offset1 = geometryNode1->GetFrameOffset();
    EXPECT_EQ(size1, SizeF(20.0f, 0.0f));
    EXPECT_EQ(offset1, OffsetF(90.0f, 100.0f));
}

/**
 * @tc.name: LayoutPolicyTest005
 * @tc.desc: test the measure result when setting fixAtIdealSize.
 * @tc.type: FUNC
 */
HWTEST_F(DividerNewTestNG, LayoutPolicyTest005, TestSize.Level0)
{
    RefPtr<FrameNode> divider;
    auto stack = CreateStack([this, &divider](StackModelNG model) {
        ViewAbstract::SetWidth(CalcLength(200));
        ViewAbstract::SetHeight(CalcLength(200));
        divider = CreateDivider([this](DividerModelNG model) {
            ViewAbstractModelNG model1;
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, true);
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, false);
            model.StrokeWidth(Dimension(20));
        });
    });
    ASSERT_NE(stack, nullptr);
    ASSERT_EQ(stack->GetChildren().size(), 1);
    CreateLayoutTask(stack);

    /* corresponding ets code:
        Stack() {
          Divider()
            .strokeWidth("20px")
            .width(LayoutPolicy.fixAtIdealSize)
            .height(LayoutPolicy.fixAtIdealSize)
        }
        .width("200px")
        .height("200px")
    */

    // Expect stack's width is 200, height is 200 and offset is [0.0, 0.0].
    auto geometryNode = stack->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(200.0f, 200.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    // Expect divider's width is 0, height is 20 and offset is [100.0, 90.0].
    auto geometryNode1 = divider->GetGeometryNode();
    ASSERT_NE(geometryNode1, nullptr);
    auto size1 = geometryNode1->GetFrameSize();
    auto offset1 = geometryNode1->GetFrameOffset();
    EXPECT_EQ(size1, SizeF(0.0f, 20.0f));
    EXPECT_EQ(offset1, OffsetF(100.0f, 90.0f));
}

/**
 * @tc.name: LayoutPolicyTest006
 * @tc.desc: test the measure result when setting fixAtIdealSize.
 * @tc.type: FUNC
 */
HWTEST_F(DividerNewTestNG, LayoutPolicyTest006, TestSize.Level0)
{
    RefPtr<FrameNode> divider;
    auto stack = CreateStack([this, &divider](StackModelNG model) {
        ViewAbstract::SetWidth(CalcLength(200));
        ViewAbstract::SetHeight(CalcLength(200));
        divider = CreateDivider([this](DividerModelNG model) {
            ViewAbstractModelNG model1;
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, true);
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, false);
            model.Vertical(true);
            model.StrokeWidth(Dimension(20));
        });
    });
    ASSERT_NE(stack, nullptr);
    ASSERT_EQ(stack->GetChildren().size(), 1);
    CreateLayoutTask(stack);

    /* corresponding ets code:
        Stack() {
          Divider()
            .strokeWidth("20px")
            .width(LayoutPolicy.fixAtIdealSize)
            .height(LayoutPolicy.fixAtIdealSize)
            .vertical(true)
        }
        .width("200px")
        .height("200px")
    */

    // Expect stack's width is 200, height is 200 and offset is [0.0, 0.0].
    auto geometryNode = stack->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(200.0f, 200.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    // Expect divider's width is 20, height is 0 and offset is [90.0, 100.0].
    auto geometryNode1 = divider->GetGeometryNode();
    ASSERT_NE(geometryNode1, nullptr);
    auto size1 = geometryNode1->GetFrameSize();
    auto offset1 = geometryNode1->GetFrameOffset();
    EXPECT_EQ(size1, SizeF(20.0f, 0.0f));
    EXPECT_EQ(offset1, OffsetF(90.0f, 100.0f));
}
} // namespace OHOS::Ace::NG