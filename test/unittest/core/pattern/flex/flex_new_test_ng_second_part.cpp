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
#include "flex_new_test_common.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;

/**
 * @tc.name: LayoutPolicyTest002
 * @tc.desc: test the measure result when setting matchParent and parent has padding.
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, LayoutPolicyTest002, TestSize.Level0)
{
    RefPtr<FrameNode> flexInner;
    auto flex = CreateFlexRow([this, &flexInner](FlexModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500));
        ViewAbstract::SetHeight(CalcLength(300));
        ViewAbstract::SetPadding(CalcLength(20));
        flexInner = CreateFlexRow([this](FlexModelNG model) {
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
          Flex()
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

    // Expect flexInner's width is 460, height is 260 and offset is [20.0, 20.0].
    auto geometryNode1 = flexInner->GetGeometryNode();
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
HWTEST_F(FlexNewTestNG, LayoutPolicyTest003, TestSize.Level0)
{
    RefPtr<FrameNode> flexInner;
    auto flex = CreateFlexRow([this, &flexInner](FlexModelNG model) {
        ViewAbstractModelNG model1;
        model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, true);
        model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, false);
        flexInner = CreateFlexRow([this](FlexModelNG model) {
            ViewAbstract::SetWidth(CalcLength(500));
            ViewAbstract::SetHeight(CalcLength(300));
        });
    });
    ASSERT_NE(flex, nullptr);
    ASSERT_EQ(flex->GetChildren().size(), 1);
    CreateLayoutTask(flex);

    /* corresponding ets code:
        Flex() {
          Flex()
            .width("500px")
            .height("300px")
        }
        .width(LayoutPolicy.wrapContent)
        .height(LayoutPolicy.wrapContent)
    */

    // Expect flex's width is 500, height is 300 and offset is [0.0, 0.0].
    auto geometryNode = flex->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(500.0f, 300.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    // Expect flexInner's width is 500, height is 300 and offset is [0.0, 0.0].
    auto geometryNode1 = flexInner->GetGeometryNode();
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
HWTEST_F(FlexNewTestNG, LayoutPolicyTest004, TestSize.Level0)
{
    RefPtr<FrameNode> flexInner;
    RefPtr<FrameNode> flexOutter;
    RefPtr<FrameNode> flex;
    flexOutter = CreateFlexRow([this, &flex, &flexInner](FlexModelNG model) {
        ViewAbstract::SetWidth(CalcLength(200.0f));
        ViewAbstract::SetHeight(CalcLength(200.0f));
        flex = CreateFlexRow([this, &flexInner](FlexModelNG model) {
            ViewAbstractModelNG model1;
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, true);
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, false);
            ViewAbstract::SetMaxWidth(CalcLength(150.0f));
            ViewAbstract::SetMaxHeight(CalcLength(300.0f));
            flexInner = CreateFlexRow([this](FlexModelNG model) {
                ViewAbstract::SetWidth(CalcLength(300.0f));
                ViewAbstract::SetHeight(CalcLength(400.0f));
                ViewAbstract::SetFlexShrink(0.0f);
            });
        });
    });
    ASSERT_NE(flexOutter, nullptr);
    ASSERT_EQ(flexOutter->GetChildren().size(), 1);
    CreateLayoutTask(flexOutter);

    /* corresponding ets code:
        Flex() {
            Flex() {
                Flex().width("300px").height("400px").flexShrink(0)
            }
            .width(LayoutPolicy.wrapContent)
            .height(LayoutPolicy.wrapContent)
            .constraintSize({ maxWidth: "150px", maxHeight: "300px" })
        }.width("200px").height("200px")
    */

    // Expect flexOutter's width is 200, height is 200 and offset is [0.0, 0.0].
    auto geometryNodeOutter = flexOutter->GetGeometryNode();
    ASSERT_NE(geometryNodeOutter, nullptr);
    auto sizeOutter = geometryNodeOutter->GetFrameSize();
    auto offsetOutter = geometryNodeOutter->GetFrameOffset();
    EXPECT_EQ(sizeOutter, SizeF(200.0f, 200.0f));
    EXPECT_EQ(offsetOutter, OffsetF(0.0f, 0.0f));

    // Expect flex's width is 150, height is 200 and offset is [25.0, 0.0].
    auto geometryNode = flex->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(150.0f, 200.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    // Expect flexInner's width is 300, height is 400 and offset is [-75.0, -100.0].
    auto geometryNodeInner = flexInner->GetGeometryNode();
    ASSERT_NE(geometryNodeInner, nullptr);
    auto sizeInner = geometryNodeInner->GetFrameSize();
    auto offsetInner = geometryNodeInner->GetFrameOffset();
    EXPECT_EQ(sizeInner, SizeF(300.0f, 400.0f));
    EXPECT_EQ(offsetInner, OffsetF(0.0f, 0.0f));
}

/**
 * @tc.name: LayoutPolicyTest005
 * @tc.desc: test the measure result when setting fixAtIdealSize.
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, LayoutPolicyTest005, TestSize.Level0)
{
    RefPtr<FrameNode> flexInner;
    auto flex = CreateFlexRow([this, &flexInner](FlexModelNG model) {
        ViewAbstractModelNG model1;
        model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, true);
        model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, false);
        flexInner = CreateFlexRow([this](FlexModelNG model) {
            ViewAbstract::SetWidth(CalcLength(500.0f));
            ViewAbstract::SetHeight(CalcLength(300.0f));
        });
    });
    ASSERT_NE(flex, nullptr);
    ASSERT_EQ(flex->GetChildren().size(), 1);
    CreateLayoutTask(flex);

    /* corresponding ets code:
        Flex() {
          Flex()
            .width("500px")
            .height("300px")
        }
        .width(LayoutPolicy.fixAtIdealSize)
        .height(LayoutPolicy.fixAtIdealSize)
    */

    // Expect flex's width is 500, height is 300 and offset is [0.0, 0.0].
    auto geometryNode = flex->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(500.0f, 300.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    // Expect flexInner's width is 500, height is 300 and offset is [0.0, 0.0].
    auto geometryNode1 = flexInner->GetGeometryNode();
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
HWTEST_F(FlexNewTestNG, LayoutPolicyTest006, TestSize.Level0)
{
    RefPtr<FrameNode> flexInner;
    RefPtr<FrameNode> flexOutter;
    RefPtr<FrameNode> flex;
    flexOutter = CreateFlexRow([this, &flex, &flexInner](FlexModelNG model) {
        ViewAbstract::SetWidth(CalcLength(200.0f));
        ViewAbstract::SetHeight(CalcLength(200.0f));
        flex = CreateFlexRow([this, &flexInner](FlexModelNG model) {
            ViewAbstractModelNG model1;
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, true);
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, false);
            ViewAbstract::SetMaxWidth(CalcLength(150.0f));
            ViewAbstract::SetMaxHeight(CalcLength(300.0f));
            flexInner = CreateFlexRow([this](FlexModelNG model) {
                ViewAbstract::SetWidth(CalcLength(300.0f));
                ViewAbstract::SetHeight(CalcLength(400.0f));
                ViewAbstract::SetFlexShrink(0.0f);
            });
        });
    });
    ASSERT_NE(flexOutter, nullptr);
    ASSERT_EQ(flexOutter->GetChildren().size(), 1);
    CreateLayoutTask(flexOutter);

    /* corresponding ets code:
        Flex() {
            Flex() {
                Flex().width("300px").height("400px").flexShrink(0)
            }
            .width(LayoutPolicy.fixAtIdealSize)
            .height(LayoutPolicy.fixAtIdealSize)
            .constraintSize({ maxWidth: "150px", maxHeight: "300px" })
        }.width("200px").height("200px")
    */

    // Expect flexOutter's width is 200, height is 200 and offset is [0.0, 0.0].
    auto geometryNodeOutter = flexOutter->GetGeometryNode();
    ASSERT_NE(geometryNodeOutter, nullptr);
    auto sizeOutter = geometryNodeOutter->GetFrameSize();
    auto offsetOutter = geometryNodeOutter->GetFrameOffset();
    EXPECT_EQ(sizeOutter, SizeF(200.0f, 200.0f));
    EXPECT_EQ(offsetOutter, OffsetF(0.0f, 0.0f));

    // Expect flex's width is 150, height is 300 and offset is [25.0, -50.0].
    auto geometryNode = flex->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(150.0f, 300.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    // Expect flexInner's width is 300, height is 400 and offset is [-75.0, -50.0].
    auto geometryNodeInner = flexInner->GetGeometryNode();
    ASSERT_NE(geometryNodeInner, nullptr);
    auto sizeInner = geometryNodeInner->GetFrameSize();
    auto offsetInner = geometryNodeInner->GetFrameOffset();
    EXPECT_EQ(sizeInner, SizeF(300.0f, 400.0f));
    EXPECT_EQ(offsetInner, OffsetF(0.0f, 0.0f));
}

/**
 * @tc.name: LayoutPolicyTest007
 * @tc.desc: test the measure result when setting matchParent and constraintSize.
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, LayoutPolicyTest007, TestSize.Level0)
{
    RefPtr<FrameNode> flexInner;
    auto flex = CreateFlexRow([this, &flexInner](FlexModelNG model) {
        ViewAbstract::SetWidth(CalcLength(500));
        ViewAbstract::SetHeight(CalcLength(300));
        flexInner = CreateFlexRow([this](FlexModelNG model) {
            ViewAbstractModelNG model1;
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, true);
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::MATCH_PARENT, false);
            ViewAbstract::SetMaxWidth(CalcLength(200.0f));
            ViewAbstract::SetMaxHeight(CalcLength(200.0f));
        });
    });
    ASSERT_NE(flex, nullptr);
    ASSERT_EQ(flex->GetChildren().size(), 1);
    CreateLayoutTask(flex);

    /* corresponding ets code:
        Flex() {
          Flex()
            .width(LayoutPolicy.matchParent)
            .height(LayoutPolicy.matchParent)
            .constraintSize({ maxWidth: "200px", maxHeight: "200px" })
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

    // Expect flexInner's width is 200, height is 200 and offset is [0.0, 0.0].
    auto geometryNode1 = flexInner->GetGeometryNode();
    ASSERT_NE(geometryNode1, nullptr);
    auto size1 = geometryNode1->GetFrameSize();
    auto offset1 = geometryNode1->GetFrameOffset();
    EXPECT_EQ(size1, SizeF(200.0f, 200.0f));
    EXPECT_EQ(offset1, OffsetF(0.0f, 0.0f));
}

/**
 * @tc.name: LayoutPolicyTest008
 * @tc.desc: test the measure result when setting matchParent and constraintSize.
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, LayoutPolicyTest008, TestSize.Level0)
{
    RefPtr<FrameNode> flexInner;
    auto flex = CreateFlexRow([this, &flexInner](FlexModelNG model) {
        ViewAbstract::SetWidth(CalcLength(100.0f));
        ViewAbstract::SetHeight(CalcLength(100.0f));
        flexInner = CreateFlexRow([this](FlexModelNG model) {
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
          Flex()
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

    // Expect flexInner's width is 200, height is 200 and offset is [0.0, 0.0].
    auto geometryNode1 = flexInner->GetGeometryNode();
    ASSERT_NE(geometryNode1, nullptr);
    auto size1 = geometryNode1->GetFrameSize();
    auto offset1 = geometryNode1->GetFrameOffset();
    EXPECT_EQ(size1, SizeF(200.0f, 200.0f));
    EXPECT_EQ(offset1, OffsetF(0.0f, 0.0f));
}

/**
 * @tc.name: LayoutPolicyTest009
 * @tc.desc: test the viewabstract UpdateLayoutPolicyProperty.
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, LayoutPolicyTest009, TestSize.Level0)
{
    RefPtr<FrameNode> flexInner;
    auto flex = CreateFlexRow([this, &flexInner](FlexModelNG model) {
        ViewAbstract::SetWidth(CalcLength(100.0f));
        ViewAbstract::SetHeight(CalcLength(100.0f));
        flexInner = CreateFlexRow([this](FlexModelNG model) {});
        ViewAbstract::UpdateLayoutPolicyProperty(flexInner.GetRawPtr(), LayoutCalPolicy::MATCH_PARENT, true);
        ViewAbstract::UpdateLayoutPolicyProperty(flexInner.GetRawPtr(), LayoutCalPolicy::MATCH_PARENT, false);
    });
    ASSERT_NE(flex, nullptr);
    ASSERT_EQ(flex->GetChildren().size(), 1);
    CreateLayoutTask(flex);

    // Expect flex's width is 100, height is 100 and offset is [0.0, 0.0].
    auto geometryNode = flex->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(100.0f, 100.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    // Expect flexInner's width is 100, height is 100 and offset is [0.0, 0.0].
    auto geometryNode1 = flexInner->GetGeometryNode();
    ASSERT_NE(geometryNode1, nullptr);
    auto size1 = geometryNode1->GetFrameSize();
    auto offset1 = geometryNode1->GetFrameOffset();
    EXPECT_EQ(size1, SizeF(100.0f, 100.0f));
    EXPECT_EQ(offset1, OffsetF(0.0f, 0.0f));
}

/**
 * @tc.name: LayoutPolicyTest010
 * @tc.desc: test the viewabstract Get and Reset LayoutPolicyProperty.
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, LayoutPolicyTest010, TestSize.Level0)
{
    RefPtr<FrameNode> flexInner;
    auto flex = CreateFlexRow([this, &flexInner](FlexModelNG model) {
        ViewAbstract::SetWidth(CalcLength(100.0f));
        ViewAbstract::SetHeight(CalcLength(100.0f));
        flexInner = CreateFlexRow([this](FlexModelNG model) {});
        ViewAbstract::UpdateLayoutPolicyProperty(flexInner.GetRawPtr(), LayoutCalPolicy::MATCH_PARENT, true);
        ViewAbstract::UpdateLayoutPolicyProperty(flexInner.GetRawPtr(), LayoutCalPolicy::MATCH_PARENT, false);
    });
    ASSERT_NE(flex, nullptr);
    ASSERT_EQ(flex->GetChildren().size(), 1);

    ViewAbstract::ResetLayoutPolicyProperty(flexInner.GetRawPtr(), true);
    ViewAbstract::ResetLayoutPolicyProperty(flexInner.GetRawPtr(), false);
    CreateLayoutTask(flex);
    LayoutCalPolicy widthPolicy1 = ViewAbstract::GetLayoutPolicy(flexInner.GetRawPtr(), true);
    LayoutCalPolicy heightPolicy1 = ViewAbstract::GetLayoutPolicy(flexInner.GetRawPtr(), false);
    EXPECT_EQ(widthPolicy1, LayoutCalPolicy::NO_MATCH);
    EXPECT_EQ(heightPolicy1, LayoutCalPolicy::NO_MATCH);
    auto geometryNode1 = flexInner->GetGeometryNode();
    ASSERT_NE(geometryNode1, nullptr);
    auto size1 = geometryNode1->GetFrameSize();
    auto offset1 = geometryNode1->GetFrameOffset();
    EXPECT_EQ(size1, SizeF(-1.0f, -1.0f));
    EXPECT_EQ(offset1, OffsetF(0.0f, 0.0f));
}

/**
 * @tc.name: FlexWrapTest001
 * @tc.desc: test the measure result in flex wrap and pixel_round_after_measure mode.
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, FlexWrapTest001, TestSize.Level0)
{
    RefPtr<FrameNode> flexInner1, flexInner2;
    auto flexWrap = CreateFlexWrapRow([this, &flexInner1, &flexInner2](FlexModelNG model) {
        ViewAbstract::SetWidth(CalcLength(325.0f));
        flexInner1 = CreateFlexRow([this](FlexModelNG model) {
            ViewAbstract::SetWidth(CalcLength(162.5f));
            ViewAbstract::SetHeight(CalcLength(100.0f));
        });
        flexInner2 = CreateFlexRow([this](FlexModelNG model) {
            ViewAbstract::SetWidth(CalcLength(162.5f));
            ViewAbstract::SetHeight(CalcLength(100.0f));
        });
    });
    ASSERT_NE(flexWrap, nullptr);
    ASSERT_EQ(flexWrap->GetChildren().size(), 2);
    CreateLayoutTask(flexWrap);

    /* corresponding ets code:
        Flex({wrap : FlexWrap.Wrap}) {
          Flex()
            .width("162.5px")
            .height("100px")
          Flex()
            .width("162.5px")
            .height("100px")
        }
        .width("325px")
    */

    // Expect flexWrap's width is 325, height is 100 and offset is [0.0, 0.0].
    auto geometryNode = flexWrap->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    auto size = geometryNode->GetFrameSize();
    auto offset = geometryNode->GetFrameOffset();
    EXPECT_EQ(size, SizeF(325.0f, 100.0f));
    EXPECT_EQ(offset, OffsetF(0.0f, 0.0f));

    // Expect flexInner1's width is 162.5, height is 100 and offset is [0.0, 0.0].
    auto geometryNode1 = flexInner1->GetGeometryNode();
    ASSERT_NE(geometryNode1, nullptr);
    auto size1 = geometryNode1->GetFrameSize();
    auto offset1 = geometryNode1->GetFrameOffset();
    EXPECT_EQ(size1, SizeF(162.5f, 100.0f));
    EXPECT_EQ(offset1, OffsetF(0.0f, 0.0f));

    // Expect flexInner2's width is 162.5, height is 100 and offset is [0.0, 0.0].
    auto geometryNode2 = flexInner2->GetGeometryNode();
    ASSERT_NE(geometryNode2, nullptr);
    auto size2 = geometryNode2->GetFrameSize();
    auto offset2 = geometryNode2->GetFrameOffset();
    EXPECT_EQ(size2, SizeF(162.5f, 100.0f));
    EXPECT_EQ(offset2, OffsetF(162.5f, 0.0f));
}

/**
 * @tc.name: UpdatePercentSensitiveTest
 * @tc.desc: test UpdatePercentSensitive
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, UpdatePercentSensitiveTest, TestSize.Level0)
{
    auto flexNode = CreateFlexRow([this](FlexModelNG model) {});
    FlexLayoutAlgorithm algorithm;
    algorithm.UpdatePercentSensitive(Referenced::RawPtr(flexNode));
    auto layoutAlgorithmWrapper = flexNode->GetLayoutAlgorithm();
    /**
     * @tc.expected: widthPercent_ == false, heightPercent_ == false
     */
    EXPECT_FALSE(layoutAlgorithmWrapper->GetPercentHeight());
    EXPECT_FALSE(layoutAlgorithmWrapper->GetPercentWidth());
    algorithm.isUsingPercentReference_ = true;
    algorithm.UpdatePercentSensitive(Referenced::RawPtr(flexNode));
    /**
     * @tc.expected: isUsingPercentReference_ == true means flexAlgorithm use percentReference
     *               to initialize horizontal mainAxis size so widthPercent_ == true
     */
    EXPECT_FALSE(layoutAlgorithmWrapper->GetPercentHeight());
    EXPECT_TRUE(layoutAlgorithmWrapper->GetPercentWidth());
    algorithm.direction_ = FlexDirection::COLUMN;
    algorithm.UpdatePercentSensitive(Referenced::RawPtr(flexNode));
    /**
     * @tc.expected: isUsingPercentReference_ == true means flexAlgorithm use percentReference
     *               to initialize horizontal mainAxis size so heightPercent_ == true
     */
    EXPECT_TRUE(layoutAlgorithmWrapper->GetPercentHeight());
}

/**
 * @tc.name: SetInitMainAxisSizeTest
 * @tc.desc: test SetInitMainAxisSize set isUsingPercentReference_ correctly
 *           test flex layout algorithm update percentSensitive correctly
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, SetInitMainAxisSizeTest, TestSize.Level0)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->SetMinPlatformVersion(12);
    auto flexNode = CreateFlexRow([this](FlexModelNG model) {});
    auto layoutAlgorithmWrapper = flexNode->GetLayoutAlgorithm();
    FlexLayoutAlgorithm algorithm;
    algorithm.direction_ = FlexDirection::COLUMN;
    algorithm.mainAxisSize_ = -1.0f;
    LayoutConstraintF constraint;
    flexNode->GetLayoutProperty()->UpdateLayoutConstraint(constraint);
    /**
     * @tc.expected: use percentReference to initialize mainAxis size, isUsingPercentReference_ == true
     */
    algorithm.SetInitMainAxisSize(Referenced::RawPtr(flexNode));
    algorithm.isLinearLayoutFeature_ = false;
    EXPECT_TRUE(algorithm.isUsingPercentReference_);
    /**
     * @tc.expected: when totalFlexWeight_ > 0, set percentSensitiveHeight to true
     */
    algorithm.totalFlexWeight_ = 10;
    FlexItemProperties flexItemProperty;
    algorithm.MeasureAndCleanMagicNodes(Referenced::RawPtr(flexNode), flexItemProperty);
    EXPECT_TRUE(layoutAlgorithmWrapper->GetPercentHeight());
    /**
     * @tc.expected: when isInfiniteLayout_ is false, percentSensitiveHeight should be false
     */
    algorithm.totalFlexWeight_= 0;
    algorithm.maxDisplayPriority_= 10;
    algorithm.isInfiniteLayout_ = false;
    layoutAlgorithmWrapper->SetPercentHeight(false);
    algorithm.MeasureAndCleanMagicNodes(Referenced::RawPtr(flexNode), flexItemProperty);
    EXPECT_FALSE(layoutAlgorithmWrapper->GetPercentHeight());
}

/**
 * @tc.name: MeasureAndCleanMagicNodesTest
 * @tc.desc: test flex layout algorithm update percentSensitive correctly
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, MeasureAndCleanMagicNodesTest, TestSize.Level0)
{
    auto flexNode = CreateFlexRow([this](FlexModelNG model) {
        CreateText(u"text1", [this](TextModelNG model) {
        });
    });
    LayoutConstraintF constraint;
    constraint.minSize.SetHeight(100.f);
    auto layoutProperty = flexNode->GetLayoutProperty();
    layoutProperty->UpdateLayoutConstraint(constraint);
    layoutProperty->UpdateContentConstraint();
    FlexLayoutAlgorithm algorithm;
    algorithm.Measure(Referenced::RawPtr(flexNode));
    auto layoutAlgorithmWrapper = flexNode->GetLayoutAlgorithm();
    EXPECT_FALSE(layoutAlgorithmWrapper->GetPercentWidth());
}

/**
 * @tc.name: WrapAndFixTest001
 * @tc.desc: test wrap layout algorithm use wrap and fix correctly
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, WrapAndFixTest001, TestSize.Level0)
{
    RefPtr<FrameNode> flex, text;
    auto flexColumn = CreateFlexRow([this, &flex, &text](FlexModelNG model) {
        model.SetDirection(FlexDirection::COLUMN);
        ViewAbstract::SetWidth(CalcLength(400));
        ViewAbstract::SetHeight(CalcLength(400));
        flex = CreateFlexWrapRow([this, &text, &flex](FlexModelNG model) {
            ViewAbstractModelNG model1;
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, true);
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::WRAP_CONTENT, false);
            ViewAbstract::SetFlexShrink(0.0f);
            text = CreateText(u"text1", [this](TextModelNG model) {
                ViewAbstract::SetFlexShrink(0.0f);
                ViewAbstract::SetWidth(CalcLength(500));
                ViewAbstract::SetHeight(CalcLength(300));
            });
        });
    });

    /* corresponding ets code:
        Flex() {
          Flex() {
            Text("text1")
            .width("500px")
            .height("300px")
        }
        .width(LayoutPolicy.wrapContent)
        .height(LayoutPolicy.wrapContent)
        }
        .width("400px")
        .height("400px")
    */

    ASSERT_NE(flexColumn, nullptr);
    CreateLayoutTask(flexColumn);

    auto flexColumnGeometryNode = flexColumn->GetGeometryNode();
    ASSERT_NE(flexColumnGeometryNode, nullptr);
    auto flexColumnSize = flexColumnGeometryNode->GetFrameSize();
    EXPECT_EQ(flexColumnSize, SizeF(400.0f, 400.0f));
    
    auto flexGeometryNode = flex->GetGeometryNode();
    ASSERT_NE(flexGeometryNode, nullptr);
    auto flexSize = flexGeometryNode->GetFrameSize();
    EXPECT_EQ(flexSize, SizeF(400.0f, 300.0f)) << flexSize.ToString().c_str();

    auto textGeometryNode = text->GetGeometryNode();
    ASSERT_NE(textGeometryNode, nullptr);
    auto textSize = textGeometryNode->GetFrameSize();
    EXPECT_EQ(textSize, SizeF(500.0f, 300.0f));
    auto textOffset = textGeometryNode->GetFrameOffset();
    EXPECT_EQ(textOffset, OffsetF(0.0f, 0.0f));
}

/**
 * @tc.name: WrapAndFixTest003
 * @tc.desc: test wrap layout algorithm use wrap and fix correctly
 * @tc.type: FUNC
 */
HWTEST_F(FlexNewTestNG, WrapAndFixTest002, TestSize.Level0)
{
    RefPtr<FrameNode> flex, text;
    auto flexColumn = CreateFlexRow([this, &flex, &text](FlexModelNG model) {
        model.SetDirection(FlexDirection::COLUMN);
        ViewAbstract::SetWidth(CalcLength(400));
        ViewAbstract::SetHeight(CalcLength(400));
        flex = CreateFlexWrapRow([this, &text, &flex](FlexModelNG model) {
            ViewAbstractModelNG model1;
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, true);
            model1.UpdateLayoutPolicyProperty(LayoutCalPolicy::FIX_AT_IDEAL_SIZE, false);
            ViewAbstract::SetFlexShrink(0.0f);
            text = CreateText(u"text1", [this](TextModelNG model) {
                ViewAbstract::SetWidth(CalcLength(500));
                ViewAbstract::SetHeight(CalcLength(300));
            });
        });
    });

    /* corresponding ets code:
        Flex() {
          Flex() {
            Text("text1")
            .width("500px")
            .height("300px")
        }
        .flexShrink(0)
        .width(LayoutPolicy.fixAtIdealSize)
        .height(LayoutPolicy.fixAtIdealSize)
        }
        .width("400px")
        .height("400px")
    */

    ASSERT_NE(flexColumn, nullptr);
    CreateLayoutTask(flexColumn);

    auto flexColumnGeometryNode = flexColumn->GetGeometryNode();
    ASSERT_NE(flexColumnGeometryNode, nullptr);
    auto flexColumnSize = flexColumnGeometryNode->GetFrameSize();
    EXPECT_EQ(flexColumnSize, SizeF(400.0f, 400.0f));
    
    ASSERT_NE(flex, nullptr);
    auto flexGeometryNode = flex->GetGeometryNode();
    ASSERT_NE(flexGeometryNode, nullptr);
    auto flexSize = flexGeometryNode->GetFrameSize();
    EXPECT_EQ(flexSize, SizeF(500.0f, 300.0f)) << flexSize.ToString().c_str();

    ASSERT_NE(text, nullptr);
    auto textGeometryNode = text->GetGeometryNode();
    ASSERT_NE(textGeometryNode, nullptr);
    auto textSize = textGeometryNode->GetFrameSize();
    EXPECT_EQ(textSize, SizeF(500.0f, 300.0f));
    auto textOffset = textGeometryNode->GetFrameOffset();
    EXPECT_EQ(textOffset, OffsetF(0.0f, 0.0f));
}
} // namespace OHOS::Ace::NG