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

#include "test/unittest/core/base/view_abstract_test_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
/**
 * @tc.name: ViewAbstractTest031
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */

/**
 * @tc.name: SetPixelRoundTest
 * @tc.desc: Test the operation of SetPixelRound.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, SetPixelRoundTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a FrameNode object.
     * @tc.steps: step2. Call SetPixelRound with value 2.
     * @tc.expected: The PixelRound property of the FrameNode is set to 0.
     */
    ViewStackProcessor viewStackProcessor;
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    uint8_t value = 2;
    ViewAbstract::SetPixelRound(AceType::RawPtr(frameNode), value);
    ASSERT_EQ(frameNode->GetLayoutProperty()->GetPixelRound(), value);
}

/**
 * @tc.name: SetDashGapTest
 * @tc.desc: Test the operation of SetDashGap method.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, SetDashGapTest, TestSize.Level1)
{
    /**
     * @tc.steps: Build a object viewAbstract and set visual state.
     */
    ViewStackProcessor viewStackProcessor;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: Build a object viewAbstract and set visual state.
     * @tc.expected: The value is not changed.
     */
    ViewAbstract::SetDashGap(Dimension(3));
    ASSERT_NE(frameNode->GetRenderContext()->GetDashGap()->rightDimen, Dimension(3));

    /**
     * @tc.steps: Set visual state to null and SetDashGap
     * @tc.expected: The value is changed as expected.
     */
    ViewStackProcessor::GetInstance()->visualState_ = std::nullopt;
    ViewAbstract::SetDashGap(Dimension(4));
    ASSERT_EQ(frameNode->GetRenderContext()->GetDashGap()->rightDimen, Dimension(4));
}

/**
 * @tc.name: SetDashGapWithFrameNodeTest
 * @tc.desc: Test the operation of SetDashGap method with FrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, SetDashGapWithFrameNodeTest, TestSize.Level1)
{
    /**
     * @tc.steps: Build a object viewAbstract and set visual state.
     */
    ViewStackProcessor viewStackProcessor;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: Set visual state to null and SetDashGap
     * @tc.expected: The value is changed as expected.
     */
    ViewAbstract::SetDashGap(AceType::RawPtr(frameNode), Dimension(2));
    auto dashGapOpt = frameNode->GetRenderContext()->GetDashGap();
    ASSERT_EQ(dashGapOpt->rightDimen, Dimension(2));
}

/**
 * @tc.name: SetDashGapWithBorderWidthPropertyTest
 * @tc.desc: Test the operation of SetDashGap method with BorderWidthProperty.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, SetDashGapWithBorderWidthPropertyTest, TestSize.Level1)
{
    /**
     * @tc.steps: Build a object viewAbstract and set visual state.
     */
    ViewStackProcessor viewStackProcessor;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: Build a object dashGap .
     */
    BorderWidthProperty dashGap1;
    dashGap1.SetBorderWidth(Dimension(3));

    /**
     * @tc.steps: SetDashGap.
     * @tc.expected: The value is not changed.
     */
    ViewAbstract::SetDashGap(dashGap1);
    ASSERT_NE(frameNode->GetRenderContext()->GetDashGap()->rightDimen, Dimension(3));

    /**
     * @tc.steps: Set visual state to null and SetDashGap
     * @tc.expected: The value is changed as expected.
     */
    BorderWidthProperty dashGap2;
    dashGap2.SetBorderWidth(Dimension(2));
    ViewStackProcessor::GetInstance()->visualState_ = std::nullopt;
    ViewAbstract::SetDashGap(dashGap2);
    ASSERT_EQ(frameNode->GetRenderContext()->GetDashGap()->rightDimen, Dimension(2));
}

/**
 * @tc.name: SetDashGapWithFrameNodePropertyTest
 * @tc.desc: Test the operation of SetDashGap method with FrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, SetDashGapWithFrameNodePropertyTest, TestSize.Level1)
{
    /**
     * @tc.steps: Build a object viewAbstract and set visual state.
     */
    ViewStackProcessor viewStackProcessor;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: Set visual state to null and SetDashGap
     * @tc.expected: The value is changed as expected.
     */
    BorderWidthProperty dashGap;
    dashGap.SetBorderWidth(Dimension(2));
    ViewAbstract::SetDashGap(AceType::RawPtr(frameNode), dashGap);
    auto dashGapOpt = frameNode->GetRenderContext()->GetDashGap();
    ASSERT_EQ(dashGapOpt->rightDimen, Dimension(2));
}

/**
 * @tc.name: SetDashWidthFrameNodePropertyTest
 * @tc.desc: Test the operation of SetDashGap method with FrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, SetDashWidthFrameNodePropertyTest, TestSize.Level1)
{
    /**
     * @tc.steps: Build a object viewAbstract and set visual state.
     */
    ViewStackProcessor viewStackProcessor;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: Set visual state to null and SetDashGap
     * @tc.expected: The value is changed as expected.
     */
    BorderWidthProperty dashGap;
    dashGap.SetBorderWidth(Dimension(2));
    ViewAbstract::SetDashWidth(AceType::RawPtr(frameNode), dashGap);
    auto dashGapOpt = frameNode->GetRenderContext()->GetDashWidth();
    ASSERT_EQ(dashGapOpt->rightDimen, Dimension(2));
}

/**
 * @tc.name: SetDashWidthWithDimensionTest
 * @tc.desc: Test the operation of SetDashWidth method with Dimension.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, SetDashWidthWithDimensionTest, TestSize.Level1)
{
    /**
     * @tc.steps: Build a object viewAbstract and set visual state.
     */
    ViewStackProcessor viewStackProcessor;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: Build a object viewAbstract and set visual state.
     * @tc.expected: The value is not changed.
     */
    ViewAbstract::SetDashWidth(Dimension(3));
    ASSERT_NE(frameNode->GetRenderContext()->GetDashWidth()->rightDimen, Dimension(3));

    /**
     * @tc.steps: Set visual state to null and SetDashGap
     * @tc.expected: The value is changed as expected.
     */
    ViewStackProcessor::GetInstance()->visualState_ = std::nullopt;
    ViewAbstract::SetDashWidth(Dimension(4));
    ASSERT_EQ(frameNode->GetRenderContext()->GetDashWidth()->rightDimen, Dimension(4));
}

/**
 * @tc.name: SetDashWidthWithFrameNodeAndDimensionTest
 * @tc.desc: Test the operation of SetDashWidth method with FrameNode and Dimension.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, SetDashWidthWithFrameNodeAndDimensionTest, TestSize.Level1)
{
    /**
     * @tc.steps: Build a object viewAbstract and set visual state.
     */
    ViewStackProcessor viewStackProcessor;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: Set visual state to null and SetDashGap
     * @tc.expected: The value is changed as expected.
     */
    ViewStackProcessor::GetInstance()->visualState_ = std::nullopt;
    ViewAbstract::SetDashWidth(AceType::RawPtr(frameNode), Dimension(2));
    ASSERT_EQ(frameNode->GetRenderContext()->GetDashWidth()->rightDimen, Dimension(2));
}

/**
 * @tc.name: SetDashWidthWithBorderWidthPropertyTest
 * @tc.desc: Test the operation of SetDashWidth method with BorderWidthProperty.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, SetDashWidthWithBorderWidthPropertyTest, TestSize.Level1)
{
    /**
     * @tc.steps: Build a object viewAbstract and set visual state.
     */
    ViewStackProcessor viewStackProcessor;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);

    BorderWidthProperty dashGap1;
    dashGap1.SetBorderWidth(Dimension(2));

    /**
     * @tc.steps: Build a object viewAbstract and set visual state.
     * @tc.expected: The value is not changed.
     */
    ViewAbstract::SetDashWidth(dashGap1);
    ASSERT_NE(frameNode->GetRenderContext()->GetDashWidth()->rightDimen, Dimension(2));

    /**
     * @tc.steps: Set visual state to null and check the current visual state process
     * @tc.expected: The value is changed as expected.
     */
    BorderWidthProperty dashGap2;
    dashGap2.SetBorderWidth(Dimension(3));
    ViewStackProcessor::GetInstance()->visualState_ = std::nullopt;
    ViewAbstract::SetDashWidth(dashGap2);
    ASSERT_EQ(frameNode->GetRenderContext()->GetDashWidth()->rightDimen, Dimension(3));
}

/**
 * @tc.name: ViewAbstractDisableOnAttachTest
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractDisableOnAttachTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create framenode and check callback;
     * @tc.expected: callback is not null.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);

    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(node, nullptr);
    std::function<void()> onAttachCallback = []() {};
    ViewAbstract::SetOnAttach(AceType::RawPtr(node), std::move(onAttachCallback));
    auto eventHub = node->GetEventHub<EventHub>();
    auto& callback = eventHub->onAttach_;
    EXPECT_NE(callback, nullptr);

    /**
     * @tc.steps: step2. Disable callback.
     * @tc.expected: callback is null.
     */
    ViewAbstract::DisableOnAttach();
    EXPECT_EQ(callback, nullptr);
}

/**
 * @tc.name: ViewAbstractDisableOnDetachTest
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractDisableOnDetachTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create framenode and check callback;
     * @tc.expected: callback is not null.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);

    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(node, nullptr);
    std::function<void()> onDetachCallback = []() {};
    ViewAbstract::SetOnDetach(AceType::RawPtr(node), std::move(onDetachCallback));
    auto eventHub = node->GetEventHub<EventHub>();
    auto& callback = eventHub->onDetach_;
    EXPECT_NE(callback, nullptr);

    /**
     * @tc.steps: step2. Disable callback.
     * @tc.expected: callback is null.
     */
    ViewAbstract::DisableOnDetach();
    EXPECT_EQ(callback, nullptr);
}

/**
 * @tc.name: ViewAbstractDisableOnAttachByFrameNodeTest
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractDisableOnAttachByFrameNodeTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create framenode and check callback;
     * @tc.expected: callback is not null.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);

    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(node, nullptr);
    std::function<void()> onAttachCallback = []() {};
    ViewAbstract::SetOnAttach(AceType::RawPtr(node), std::move(onAttachCallback));
    auto eventHub = node->GetEventHub<EventHub>();
    auto& callback = eventHub->onAttach_;
    EXPECT_NE(callback, nullptr);

    /**
     * @tc.steps: step2. Disable callback.
     * @tc.expected: callback is null.
     */
    ViewAbstract::DisableOnAttach(AceType::RawPtr(node));
    EXPECT_EQ(callback, nullptr);
}

/**
 * @tc.name: ViewAbstractDisableOnDetachByFrameNodeTest
 * @tc.desc: Test the operation of View_Abstract.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractDisableOnDetachByFrameNodeTest, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create framenode and check callback;
     * @tc.expected: callback is not null.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);

    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(node, nullptr);
    std::function<void()> onDetachCallback = []() {};
    ViewAbstract::SetOnDetach(AceType::RawPtr(node), std::move(onDetachCallback));
    auto eventHub = node->GetEventHub<EventHub>();
    auto& callback = eventHub->onDetach_;
    EXPECT_NE(callback, nullptr);

    /**
     * @tc.steps: step2. Disable callback.
     * @tc.expected: callback is null.
     */
    ViewAbstract::DisableOnDetach(AceType::RawPtr(node));
    EXPECT_EQ(callback, nullptr);
}

/**
 * @tc.name: ViewAbstractTouchIntercept001
 * @tc.desc: Test setting touch intercept function on a specific frame node
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTouchIntercept001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a new frame node and set the touch intercept function.
     */
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);
    TouchInterceptFunc touchInterceptFunc;
    ViewAbstract::SetOnTouchIntercept(std::move(touchInterceptFunc));

    /**
     * @tc.steps: step2. Verify that the touch intercept function has been set.
     * @tc.expected: The touch intercept function should be set correctly.
     */
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    EXPECT_NE(ViewStackProcessor::GetInstance()->GetMainElementNode(), nullptr);
}

/**
 * @tc.name: ViewAbstractTouchIntercept002
 * @tc.desc: Test setting touch intercept function on the main frame node
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTouchIntercept002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a new frame node and set the touch intercept function.
     */
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(node, nullptr);
    TouchInterceptFunc touchInterceptFunc;
    ViewAbstract::SetOnTouchIntercept(AceType::RawPtr(node), std::move(touchInterceptFunc));

    /**
     * @tc.steps: step2. Verify that the touch intercept function has been set.
     * @tc.expected: The touch intercept function should be set correctly.
     */
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    EXPECT_NE(ViewStackProcessor::GetInstance()->GetMainElementNode(), nullptr);
}

/**
 * @tc.name: ViewAbstractRecognizerParallel001
 * @tc.desc: Test setting ShouldBuiltInRecognizerParallelWith function
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractRecognizerParallel001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a new frame node and set the touch intercept function.
     */
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);
    
    NG::ShouldBuiltInRecognizerParallelWithFunc shouldBuiltInRecognizerParallelWithFunc;
    ViewAbstract::SetShouldBuiltInRecognizerParallelWith(std::move(shouldBuiltInRecognizerParallelWithFunc));

    /**
     * @tc.steps: step2. Verify that the touch intercept function has been set.
     * @tc.expected: The touch intercept function should be set correctly.
     */
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    EXPECT_NE(ViewStackProcessor::GetInstance()->GetMainElementNode(), nullptr);
}

/**
 * @tc.name: ViewAbstractGestureRecognizerJudge001
 * @tc.desc: Test setting OnGestureRecognizerJudgeBegin function
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractGestureRecognizerJudge001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a new frame node and set the touch intercept function.
     */
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);
    
    GestureRecognizerJudgeFunc gestureRecognizerJudgeFunc;
    ViewAbstract::SetOnGestureRecognizerJudgeBegin(std::move(gestureRecognizerJudgeFunc), false);

    /**
     * @tc.steps: step2. Verify that the touch intercept function has been set.
     * @tc.expected: The touch intercept function should be set correctly.
     */
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    EXPECT_NE(ViewStackProcessor::GetInstance()->GetMainElementNode(), nullptr);
}

/**
 * @tc.name: ViewAbstractOnTouchTest001
 * @tc.desc: Test setting OnTouchTest function
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractOnTouchTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a new frame node and set the touch intercept function.
     */
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);
    
    NG::OnChildTouchTestFunc onChildTouchTest;
    ViewAbstract::SetOnTouchTestFunc(std::move(onChildTouchTest));

    /**
     * @tc.steps: step2. Verify that the touch intercept function has been set.
     * @tc.expected: The touch intercept function should be set correctly.
     */
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    EXPECT_NE(ViewStackProcessor::GetInstance()->GetMainElementNode(), nullptr);
}

/**
 * @tc.name: ViewAbstractFocusBoxStyle001
 * @tc.desc: Test setting focus box style
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractFocusBoxStyle001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a new frame node and set the touch intercept function.
     */
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(node, nullptr);
    
    NG::FocusBoxStyle style;
    ViewAbstract::SetFocusBoxStyle(std::move(style));

    /**
     * @tc.steps: step2. Verify that the touch intercept function has been set.
     * @tc.expected: The touch intercept function should be set correctly.
     */
    auto focusHub = ViewStackProcessor::GetInstance()->GetOrCreateMainFrameNodeFocusHub();
    ASSERT_NE(focusHub, nullptr);
    EXPECT_NE(ViewStackProcessor::GetInstance()->GetMainElementNode(), nullptr);
}

/**
 * @tc.name: ViewAbstractFocusScopeId001
 * @tc.desc: Test setting focus scope ID
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractFocusScopeId001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Push main frame node and set the focus scope ID.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    std::string focusScopeId = "focusScope1";
    bool isGroup = true;
    ViewStackProcessor::GetInstance()->GetOrCreateMainFrameNodeFocusHub()->focusType_ = FocusType::SCOPE;
    ViewAbstract::SetFocusScopeId(focusScopeId, isGroup, true);

    /**
     * @tc.steps: step2. Verify that the focus scope ID has been set.
     * @tc.expected: The focus scope ID should be set correctly.
     */
    auto focusHub = ViewStackProcessor::GetInstance()->GetOrCreateMainFrameNodeFocusHub();
    ASSERT_NE(focusHub, nullptr);
    EXPECT_EQ(focusHub->focusScopeId_, focusScopeId);

    /**
     * @tc.steps: step3. Finish view stack.
     */
    ViewStackProcessor::GetInstance()->Finish();
}

/**
 * @tc.name: ViewAbstractFocusScopePriority001
 * @tc.desc: Test setting focus scope priority
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractFocusScopePriority001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Push main frame node and set the focus scope priority.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    std::string focusScopeId = "focusScope1";
    uint32_t focusPriority = 1;
    ViewStackProcessor::GetInstance()->GetOrCreateMainFrameNodeFocusHub()->isFocusScope_ = true;
    ViewAbstract::SetFocusScopePriority(focusScopeId, focusPriority);

    /**
     * @tc.steps: step2. Verify that the focus scope priority has been set.
     * @tc.expected: The focus scope priority should be set correctly.
     */
    auto focusHub = ViewStackProcessor::GetInstance()->GetOrCreateMainFrameNodeFocusHub();
    ASSERT_NE(focusHub, nullptr);
    EXPECT_EQ(focusHub->focusScopeId_, focusScopeId);

    /**
     * @tc.steps: step3. Finish view stack.
     */
    ViewStackProcessor::GetInstance()->Finish();
}

/**
 * @tc.name: ViewAbstractFocusScopeIdWithFrameNode001
 * @tc.desc: Test setting focus scope ID with frame node
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractFocusScopeIdWithFrameNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a new frame node and set the focus scope ID.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    std::string focusScopeId = "focusScope2";
    bool isGroup = true;
    ViewStackProcessor::GetInstance()->GetOrCreateMainFrameNodeFocusHub()->focusType_ = FocusType::SCOPE;
    ViewAbstract::SetFocusScopeId(AceType::RawPtr(frameNode), focusScopeId, isGroup, true);

    /**
     * @tc.steps: step2. Verify that the focus scope ID has been set.
     * @tc.expected: The focus scope ID should be set correctly.
     */
    auto focusHub = frameNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);

    /**
     * @tc.steps: step3. Finish view stack.
     */
    ViewStackProcessor::GetInstance()->Finish();
}

/**
 * @tc.name: ViewAbstractFocusScopePriorityWithFrameNode001
 * @tc.desc: Test setting focus scope priority with frame node
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractFocusScopePriorityWithFrameNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a new frame node and set the focus scope priority.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    std::string focusScopeId = "focusScope2";
    uint32_t focusPriority = 2;
    ViewAbstract::SetFocusScopePriority(AceType::RawPtr(frameNode), focusScopeId, focusPriority);

    /**
     * @tc.steps: step2. Verify that the focus scope priority has been set.
     * @tc.expected: The focus scope priority should be set correctly.
     */
    auto focusHub = frameNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    EXPECT_EQ(focusHub->focusScopeId_, focusScopeId);

    /**
     * @tc.steps: step3. Finish view stack.
     */
    ViewStackProcessor::GetInstance()->Finish();
}

/**
 * @tc.name: ViewAbstractOnAttach001
 * @tc.desc: Test setting onAttach function
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractOnAttach001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create framenode and check callback;
     * @tc.expected: callback is not null.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);

    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(node, nullptr);
    std::function<void()> onAttachCallback = []() {};
    ViewAbstract::SetOnAttach(AceType::RawPtr(node), std::move(onAttachCallback));
    auto eventHub = node->GetEventHub<EventHub>();
    auto& callback = eventHub->onAttach_;
    EXPECT_NE(callback, nullptr);

    /**
     * @tc.steps: step2. Disable callback.
     * @tc.expected: callback is null.
     */
    ViewAbstract::DisableOnAttach(AceType::RawPtr(node));
    EXPECT_EQ(callback, nullptr);
    
    /**
     * @tc.steps: step3. Finish view stack.
     */
    ViewStackProcessor::GetInstance()->Finish();
}

/**
 * @tc.name: ViewAbstractOnDetach001
 * @tc.desc: Test setting onDetach function
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractOnDetach001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create framenode and check callback;
     * @tc.expected: callback is not null.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);

    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(node, nullptr);
    std::function<void()> onDetachCallback = []() {};
    ViewAbstract::SetOnDetach(std::move(onDetachCallback));
    auto eventHub = node->GetEventHub<EventHub>();
    auto& callback = eventHub->onDetach_;
    EXPECT_NE(callback, nullptr);

    /**
     * @tc.steps: step2. Disable callback.
     * @tc.expected: callback is null.
     */
    ViewAbstract::DisableOnDetach(AceType::RawPtr(node));
    EXPECT_EQ(callback, nullptr);

    /**
     * @tc.steps: step3. Finish view stack.
     */
    ViewStackProcessor::GetInstance()->Finish();
}

/**
 * @tc.name: ViewAbstractOnAttach002
 * @tc.desc: Test setting onAttach callback
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractOnAttach002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create framenode and check callback;
     * @tc.expected: callback is not null.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_CHILD);

    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    EXPECT_EQ(strcmp(topFrameNodeOne->GetTag().c_str(), TAG_CHILD), 0);
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);
    auto node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(node, nullptr);
    std::function<void()> onAttachCallback = []() {};
    ViewAbstract::SetOnAttach(std::move(onAttachCallback));
    auto eventHub = node->GetEventHub<EventHub>();
    auto& callback = eventHub->onAttach_;
    EXPECT_NE(callback, nullptr);

    /**
     * @tc.steps: step2. Disable callback.
     * @tc.expected: callback is null.
     */
    ViewAbstract::DisableOnAttach(AceType::RawPtr(node));
    EXPECT_EQ(callback, nullptr);

    /**
     * @tc.steps: step3. Finish view stack.
     */
    ViewStackProcessor::GetInstance()->Finish();
}

/**
 * @tc.name: ViewAbstractBgDynamicBrightness001
 * @tc.desc: Test setting background dynamic brightness option
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractBgDynamicBrightness001, TestSize.Level1)
{
    /**
     * @tc.steps: Build a object viewAbstract and set visual state.
     */
    ViewStackProcessor viewStackProcessor;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: Build a object viewAbstract and set visual state.
     * @tc.expected: The foreground effect is not changed.
     */
    BrightnessOption brightnessOption;
    ViewAbstract::SetBgDynamicBrightness(brightnessOption);
    ASSERT_FALSE(frameNode->GetRenderContext()->GetBgDynamicBrightnessOption().has_value());

    /**
     * @tc.steps: Set visual state to null and check the current visual state process
     * @tc.expected: The foreground effect is changed as expected.
     */
    ViewStackProcessor::GetInstance()->visualState_ = std::nullopt;
    ViewAbstract::SetBgDynamicBrightness(brightnessOption);
    ASSERT_TRUE(frameNode->GetRenderContext()->GetBgDynamicBrightnessOption().has_value());
}

/**
 * @tc.name: ViewAbstractFgDynamicBrightness001
 * @tc.desc: Test setting foreground dynamic brightness option
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractFgDynamicBrightness001, TestSize.Level1)
{
    /**
     * @tc.steps: Build a object viewAbstract and set visual state.
     */
    ViewStackProcessor viewStackProcessor;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: Build a object viewAbstract and set visual state.
     * @tc.expected: The foreground effect is not changed.
     */
    BrightnessOption brightnessOption;
    ViewAbstract::SetFgDynamicBrightness(brightnessOption);
    ASSERT_FALSE(frameNode->GetRenderContext()->GetFgDynamicBrightnessOption().has_value());

    /**
     * @tc.steps: Set visual state to null and check the current visual state process
     * @tc.expected: The foreground effect is changed as expected.
     */
    ViewStackProcessor::GetInstance()->visualState_ = std::nullopt;
    ViewAbstract::SetFgDynamicBrightness(brightnessOption);
    ASSERT_TRUE(frameNode->GetRenderContext()->GetFgDynamicBrightnessOption().has_value());
}

/**
 * @tc.name: ViewAbstractBgDynamicBrightness002
 * @tc.desc: Test setting background dynamic brightness option
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractBgDynamicBrightness002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a new frame node and set the background dynamic brightness option.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ViewStackProcessor viewStackProcessor;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();

    /**
     * @tc.steps: Build a object viewAbstract and set visual state.
     * @tc.expected: The foreground effect is not changed.
     */
    BrightnessOption brightnessOption;
    auto node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(node, nullptr);
    ViewAbstract::SetBgDynamicBrightness(AceType::RawPtr(node), brightnessOption);

    /**
     * @tc.steps: Set visual state to null and check the current visual state process
     * @tc.expected: The foreground effect is changed as expected.
     */
    ViewStackProcessor::GetInstance()->visualState_ = std::nullopt;
    ViewAbstract::SetBgDynamicBrightness(AceType::RawPtr(node), brightnessOption);
    ASSERT_TRUE(frameNode->GetRenderContext()->GetBgDynamicBrightnessOption().has_value());
}

/**
 * @tc.name: ViewAbstractFgDynamicBrightness002
 * @tc.desc: Test setting foreground dynamic brightness option
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractFgDynamicBrightness002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a new frame node and set the background dynamic brightness option.
     */
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ViewStackProcessor viewStackProcessor;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();

    /**
     * @tc.steps: Build a object viewAbstract and set visual state.
     * @tc.expected: The foreground effect is not changed.
     */
    BrightnessOption brightnessOption;
    auto node = AceType::DynamicCast<NG::FrameNode>(frameNode);
    ASSERT_NE(node, nullptr);
    ViewAbstract::SetFgDynamicBrightness(AceType::RawPtr(node), brightnessOption);

    /**
     * @tc.steps: Set visual state to null and check the current visual state process
     * @tc.expected: The foreground effect is changed as expected.
     */
    ViewStackProcessor::GetInstance()->visualState_ = std::nullopt;
    ViewAbstract::SetFgDynamicBrightness(AceType::RawPtr(node), brightnessOption);
    ASSERT_TRUE(frameNode->GetRenderContext()->GetFgDynamicBrightnessOption().has_value());
}

/**
 * @tc.name: ViewAbstractSystemBarEffect001
 * @tc.desc: Test setting system bar effect
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractSystemBarEffect001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Push main frame node and set the system bar effect.
     */
    ViewStackProcessor viewStackProcessor;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps:  using a unCurrent visual state Process and set value
     * @tc.expected: The valueis not changed.
     */
    ViewAbstract::SetSystemBarEffect(true);
    ASSERT_FALSE(frameNode->GetRenderContext()->GetSystemBarEffect());

    /**
     * @tc.steps: Set visual state to null and check the current visual state process
     * @tc.expected: The value is changed as expected.
     */
    ViewStackProcessor::GetInstance()->visualState_ = std::nullopt;
    ViewAbstract::SetSystemBarEffect(true);
    ASSERT_TRUE(frameNode->GetRenderContext()->GetSystemBarEffect());
}

/**
 * @tc.name: ViewAbstractSystemBarEffect002
 * @tc.desc: Test setting system bar effect
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractSystemBarEffect002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Push main frame node and set the system bar effect.
     */
    ViewStackProcessor viewStackProcessor;
    int32_t index = 1;
    auto state = static_cast<VisualState>(index);
    viewStackProcessor.GetInstance()->SetVisualState(state);
    auto topFrameNodeOne = ViewStackProcessor::GetInstance()->GetMainElementNode();
    auto frameNode = AceType::DynamicCast<FrameNode>(topFrameNodeOne);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: Set visual state to null and check the current visual state process
     * @tc.expected: The value is changed as expected.
     */
    ViewAbstract::SetSystemBarEffect(nullptr, false);
    ASSERT_FALSE(frameNode->GetRenderContext()->GetSystemBarEffect());
}

/**
 * @tc.name: ViewAbstractPositionEdges002
 * @tc.desc: Test setting position edges
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractPositionEdges002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create and put mainNode, then build some necessary params.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);

    /**
     * @tc.steps: step2. get node in ViewStackProcessor.
     * @tc.expected: node is not null.
     */
    auto rootFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(rootFrameNode, nullptr);

    /**
     * @tc.steps: step3. use ViewAbstract::SetPositionEdges.
     * @tc.expected: success set render property PositionEdges value.
     */
    EdgesParam edges;
    CalcDimension bottom(30, DimensionUnit::VP);
    CalcDimension right(20, DimensionUnit::VP);
    edges.SetBottom(bottom);
    edges.SetRight(right);
    ViewAbstract::SetPositionEdges(rootFrameNode, edges);

    EXPECT_NE(FRAME_NODE_ROOT->GetRenderContext(), nullptr);
    EXPECT_EQ(FRAME_NODE_ROOT->GetRenderContext()
                  ->GetPositionEdgesValue(EdgesParam {}).bottom.value_or(Dimension {}).ConvertToVp(), 30.0f);
    EXPECT_EQ(FRAME_NODE_ROOT->GetRenderContext()
                  ->GetPositionEdgesValue(EdgesParam {}).right.value_or(Dimension {}).ConvertToVp(), 20.0f);

    /**
     * @tc.steps: step5. finish view stack.
     */
    ViewStackProcessor::GetInstance()->Finish();
}

/**
 * @tc.name: ViewAbstractOffsetEdges002
 * @tc.desc: test offset attribute, use Edges type.
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractOffset002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create and put mainNode, then build some necessary params.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);

    /**
     * @tc.steps: step2. get node in ViewStackProcessor.
     * @tc.expected: node is not null.
     */
    auto rootFrameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    EXPECT_NE(rootFrameNode, nullptr);

    /**
     * @tc.steps: step3. use ViewAbstract::SetOffsetEdges.
     * @tc.expected: success set render property offsetEdges value.
     */
    EdgesParam edges;
    CalcDimension top(30, DimensionUnit::VP);
    CalcDimension left(20, DimensionUnit::VP);
    edges.SetTop(top);
    edges.SetLeft(left);
    ViewAbstract::SetOffsetEdges(rootFrameNode, edges);

    EXPECT_NE(FRAME_NODE_ROOT->GetRenderContext(), nullptr);
    EXPECT_EQ(FRAME_NODE_ROOT->GetRenderContext()
                  ->GetOffsetEdgesValue(EdgesParam {}).top.value_or(Dimension {}).ConvertToVp(), 30.0f);
    EXPECT_EQ(FRAME_NODE_ROOT->GetRenderContext()
                  ->GetOffsetEdgesValue(EdgesParam {}).left.value_or(Dimension {}).ConvertToVp(), 20.0f);

    /**
     * @tc.steps: step5. finish view stack.
     */
    ViewStackProcessor::GetInstance()->Finish();
}

/**
 * @tc.name: ViewAbstractTest043
 * @tc.desc: Test the operation of View_Abstract
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractTest043, TestSize.Level1)
{
    /**
     * @tc.steps: step1.ClearStack.
     */
    auto state = static_cast<VisualState>(INDEX);
    ViewStackProcessor::GetInstance()->SetVisualState(state);
    ViewStackProcessor::GetInstance()->ClearStack();

    /**
     * @tc.steps: step2. related function is called.
     */
    CalcDimension dimensionRadius(0.0);
    ViewAbstract::SetLightPosition(dimensionRadius, dimensionRadius, dimensionRadius);
    ViewAbstract::SetLightPosition(nullptr, dimensionRadius, dimensionRadius, dimensionRadius);
    ViewAbstract::SetLightIntensity(RATIO);
    ViewAbstract::SetLightIntensity(nullptr, RATIO);
    ViewAbstract::SetIlluminatedBorderWidth(ZERO);
    ViewAbstract::SetIlluminatedBorderWidth(nullptr, ZERO);
    ViewAbstract::SetDisplayIndex(INDEX);
    ViewAbstract::SetDisplayIndex(nullptr, INDEX);
    ViewAbstract::SetGrayScale(RADIUS);
    ViewAbstract::SetGrayScale(nullptr, RADIUS);
    OHOS::Rosen::VisualEffect* visualEffect;
    ViewAbstract::SetVisualEffect(visualEffect);
    OHOS::Rosen::Filter* backgroundFilter;
    ViewAbstract::SetBackgroundFilter(backgroundFilter);
    OHOS::Rosen::Filter* foregroundFilter;
    ViewAbstract::SetForegroundFilter(foregroundFilter);
    OHOS::Rosen::Filter* compositingFilter;
    ViewAbstract::SetCompositingFilter(compositingFilter);
    ViewAbstract::SetDynamicDim(1.0f);
    ViewAbstract::SetSystemBarEffect(false);
    ViewAbstract::SetSystemBarEffect(nullptr, false);
    ImageResizableSlice slice;
    ViewAbstract::SetBackgroundImageResizableSlice(slice);
    ViewAbstract::SetBackgroundImageResizableSlice(nullptr, slice);
    MotionBlurOption motionBlurOption;
    motionBlurOption.radius = 5;
    motionBlurOption.anchor.x = 0.5;
    motionBlurOption.anchor.y = 0.5;
    ViewAbstract::SetMotionBlur(motionBlurOption);
    ViewAbstract::SetLayoutWeight(AceType::RawPtr(FRAME_NODE_REGISTER), TEN);

    /**
     * @tc.expected: Return expected results.
     */
    bool result = ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ViewAbstractDisallowDropForcedly001
 * @tc.desc: Test setting disallow drop forcedly
 * @tc.type: FUNC
 */
HWTEST_F(ViewAbstractTestNg, ViewAbstractDisallowDropForcedly001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Push main frame node and set the disallow drop forcedly.
     */
    ViewStackProcessor::GetInstance()->Push(FRAME_NODE_ROOT);
    bool isDisallowDropForcedly = true;
    ViewAbstract::SetDisallowDropForcedly(isDisallowDropForcedly);

    /**
     * @tc.steps: step2. Verify that the disallow drop forcedly has been set.
     * @tc.expected: The disallow drop forcedly should be set correctly.
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(frameNode->isDisallowDropForcedly_, isDisallowDropForcedly);

    /**
     * @tc.steps: step3. Finish view stack.
     */
    ViewStackProcessor::GetInstance()->Finish();
}
} // namespace OHOS::Ace::NG