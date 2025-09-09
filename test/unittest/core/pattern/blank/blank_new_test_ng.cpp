/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "blank_new_test_ng.h"

#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/base/view_abstract_model_ng.h"
#include "core/components_ng/base/view_stack_processor.h"

namespace OHOS::Ace::NG {

void BlankNewTestNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    MockPipelineContext::GetCurrent()->SetUseFlushUITasks(true);
}

void BlankNewTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void BlankNewTestNg::SetUp()
{
    ViewStackProcessor::GetInstance()->ClearStack();
}

void BlankNewTestNg::TearDown() {}

RefPtr<FrameNode> BlankNewTestNg::CreateBlank(const std::function<void(BlankModelNG)>& callback)
{
    BlankModelNG model;
    model.Create();
    if (callback) {
        callback(model);
    }
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    ViewStackProcessor::GetInstance()->Pop();
    return AceType::DynamicCast<FrameNode>(element);
}

RefPtr<FrameNode> BlankNewTestNg::CreateFlexRow(const std::function<void(FlexModelNG)>& callback)
{
    FlexModelNG model;
    model.CreateFlexRow();
    if (callback) {
        callback(model);
    }
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    ViewStackProcessor::GetInstance()->Pop();
    return AceType::DynamicCast<FrameNode>(element);
}

/**
 * @tc.name: LayoutPolicyTest001
 * @tc.desc: test the measure result when setting matchParent.
 * @tc.type: FUNC
 */
HWTEST_F(BlankNewTestNg, LayoutPolicyTest001, TestSize.Level0)
{
    RefPtr<FrameNode> blank;
    auto flex = CreateFlexRow([this, &blank](FlexModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500));
        ViewAbstract::SetHeight(CalcLength(300));
        blank = CreateBlank([this](BlankModelNG model) {
            ViewAbstractModelNG model1;
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, true);
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, false);
        });
    });
    ASSERT_NE(flex, nullptr);
    ASSERT_EQ(flex->GetChildren().size(), 1);
    CreateLayoutTask(flex);

    /* corresponding ets code:
        Flex() {
          Blank()
            .width(LayoutPolicy.matchParent)
            .height(LayoutPolicy.matchParent)
        }
        .width("500px")
        .height("300px")
    */

    // Expect flex's width is 500, height is 300 and offset is [0.0, 0.0].
    auto geometryNode = flex->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(500.0f, 300.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    // Expect blank's width is 500, height is 300 and offset is [0.0, 0.0].
    auto geometryNode1 = blank->GetGeometryNode();
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
HWTEST_F(BlankNewTestNg, LayoutPolicyTest002, TestSize.Level0)
{
    RefPtr<FrameNode> blank;
    auto flex = CreateFlexRow([this, &blank](FlexModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500));
        ViewAbstract::SetHeight(CalcLength(300));
        ViewAbstract::SetPadding(CalcLength(20));
        blank = CreateBlank([this](BlankModelNG model) {
            ViewAbstractModelNG model1;
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, true);
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, false);
        });
    });
    ASSERT_NE(flex, nullptr);
    ASSERT_EQ(flex->GetChildren().size(), 1);
    CreateLayoutTask(flex);

    /* corresponding ets code:
        Flex() {
          Blank()
            .width(LayoutPolicy.matchParent)
            .height(LayoutPolicy.matchParent)
        }
        .width("500px")
        .height("300px")
        .padding("20px")
    */

    // Expect flex's width is 500, height is 300 and offset is [0.0, 0.0].
    auto geometryNode = flex->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(500.0f, 300.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    // Expect blank's width is 460, height is 260 and offset is [20.0, 20.0].
    auto geometryNode1 = blank->GetGeometryNode();
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
HWTEST_F(BlankNewTestNg, LayoutPolicyTest003, TestSize.Level0)
{
    RefPtr<FrameNode> blank;
    auto flex = CreateFlexRow([this, &blank](FlexModelNG model) {
        ViewAbstract::SetWidth(CalcLength(200));
        ViewAbstract::SetHeight(CalcLength(200));
        blank = CreateBlank([this](BlankModelNG model) {
            ViewAbstractModelNG model1;
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, true);
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, false);
        });
    });
    ASSERT_NE(flex, nullptr);
    ASSERT_EQ(flex->GetChildren().size(), 1);
    CreateLayoutTask(flex);

    /* corresponding ets code:
        Flex() {
          Blank()
            .width(LayoutPolicy.wrapContent)
            .height(LayoutPolicy.wrapContent)
        }
        .width("200px")
        .height("200px")
    */

    // Expect flex's width is 200, height is 200 and offset is [0.0, 0.0].
    auto geometryNode = flex->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(200.0f, 200.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    // Expect blank's width is 0, height is 0 and offset is [0.0, 0.0].
    auto geometryNode1 = blank->GetGeometryNode();
    ASSERT_NE(geometryNode1, nullptr);
    auto size1 = geometryNode1->GetFrameSize();
    auto offset1 = geometryNode1->GetFrameOffset();
    EXPECT_EQ(size1, SizeF(0.0f, 0.0f));
    EXPECT_EQ(offset1, OffsetF(0.0f, 0.0f));
}

/**
 * @tc.name: LayoutPolicyTest004
 * @tc.desc: test the measure result when setting fixAtIdealSize.
 * @tc.type: FUNC
 */
HWTEST_F(BlankNewTestNg, LayoutPolicyTest004, TestSize.Level0)
{
    RefPtr<FrameNode> blank;
    auto flex = CreateFlexRow([this, &blank](FlexModelNG model) {
        ViewAbstract::SetWidth(CalcLength(200));
        ViewAbstract::SetHeight(CalcLength(200));
        blank = CreateBlank([this](BlankModelNG model) {
            ViewAbstractModelNG model1;
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, true);
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, false);
        });
    });
    ASSERT_NE(flex, nullptr);
    ASSERT_EQ(flex->GetChildren().size(), 1);
    CreateLayoutTask(flex);

    /* corresponding ets code:
        Flex() {
          Blank()
            .width(LayoutPolicy.fixAtIdealSize)
            .height(LayoutPolicy.fixAtIdealSize)
        }
        .width("200px")
        .height("200px")
    */

    // Expect flex's width is 200, height is 200 and offset is [0.0, 0.0].
    auto geometryNode = flex->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(200.0f, 200.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    // Expect blank's width is 0, height is 0 and offset is [0.0, 0.0].
    auto geometryNode1 = blank->GetGeometryNode();
    ASSERT_NE(geometryNode1, nullptr);
    auto size1 = geometryNode1->GetFrameSize();
    auto offset1 = geometryNode1->GetFrameOffset();
    EXPECT_EQ(size1, SizeF(0.0f, 0.0f));
    EXPECT_EQ(offset1, OffsetF(0.0f, 0.0f));
}

/**
 * @tc.name: LayoutPolicyTest005
 * @tc.desc: test the measure result when setting matchParent and constraintSize.
 * @tc.type: FUNC
 */
HWTEST_F(BlankNewTestNg, LayoutPolicyTest005, TestSize.Level0)
{
    RefPtr<FrameNode> blank;
    auto flex = CreateFlexRow([this, &blank](FlexModelNG model) {
        ViewAbstract::SetWidth(CalcLength(100.0f));
        ViewAbstract::SetHeight(CalcLength(100.0f));
        blank = CreateBlank([this](BlankModelNG model) {
            ViewAbstractModelNG model1;
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, true);
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, false);
            ViewAbstract::SetMinWidth(CalcLength(200.0f));
            ViewAbstract::SetMinHeight(CalcLength(200.0f));
            ViewAbstract::SetFlexShrink(0.0f);
        });
    });
    ASSERT_NE(flex, nullptr);
    ASSERT_EQ(flex->GetChildren().size(), 1);
    CreateLayoutTask(flex);

    /* corresponding ets code:
        Flex() {
          Blank()
            .width(LayoutPolicy.matchParent)
            .height(LayoutPolicy.matchParent)
            .constraintSize({ minWidth: "200px", minHeight: "200px" })
            .flexShrink(0)
        }
        .width("100px")
        .height("100px")
    */

    // Expect flex's width is 100, height is 100 and offset is [0.0, 0.0].
    auto geometryNode = flex->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(100.0f, 100.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    // Expect blank's width is 200, height is 200 and offset is [0.0, 0.0].
    auto geometryNode1 = blank->GetGeometryNode();
    ASSERT_NE(geometryNode1, nullptr);
    auto size1 = geometryNode1->GetFrameSize();
    auto offset1 = geometryNode1->GetFrameOffset();
    EXPECT_EQ(size1, SizeF(200.0f, 200.0f));
    EXPECT_EQ(offset1, OffsetF(0.0f, 0.0f));
}

/**
 * @tc.name: LayoutPolicyTest006
 * @tc.desc: test the measure result when setting matchParent and constraintSize.
 * @tc.type: FUNC
 */
HWTEST_F(BlankNewTestNg, LayoutPolicyTest006, TestSize.Level0)
{
    RefPtr<FrameNode> blank;
    auto flex = CreateFlexRow([this, &blank](FlexModelNG model) {
        ViewAbstract::SetWidth(CalcLength(300.0f));
        ViewAbstract::SetHeight(CalcLength(300.0f));
        blank = CreateBlank([this](BlankModelNG model) {
            ViewAbstractModelNG model1;
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, true);
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, false);
            ViewAbstract::SetMaxWidth(CalcLength(200.0f));
            ViewAbstract::SetMaxHeight(CalcLength(200.0f));
            ViewAbstract::SetFlexShrink(0.0f);
        });
    });
    ASSERT_NE(flex, nullptr);
    ASSERT_EQ(flex->GetChildren().size(), 1);
    CreateLayoutTask(flex);

    /* corresponding ets code:
        Flex() {
          Blank()
            .width(LayoutPolicy.matchParent)
            .height(LayoutPolicy.matchParent)
            .constraintSize({ minWidth: "200px", minHeight: "200px" })
            .flexShrink(0)
        }
        .width("300px")
        .height("300px")
    */

    // Expect flex's width is 300, height is 300 and offset is [0.0, 0.0].
    auto geometryNode = flex->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(300.0f, 300.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    // Expect blank's width is 200, height is 200 and offset is [0.0, 0.0].
    auto geometryNode1 = blank->GetGeometryNode();
    ASSERT_NE(geometryNode1, nullptr);
    auto size1 = geometryNode1->GetFrameSize();
    auto offset1 = geometryNode1->GetFrameOffset();
    EXPECT_EQ(size1, SizeF(200.0f, 200.0f));
    EXPECT_EQ(offset1, OffsetF(0.0f, 0.0f));
}
} // namespace OHOS::Ace::NG
