/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include <cstdint>
#include <unistd.h>

#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/event/state_style_manager.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/event/ace_events.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class StateStyleManagerTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
};

void StateStyleManagerTestNg::SetUpTestSuite()
{
    GTEST_LOG_(INFO) << "StateStyleManagerTestNg SetUpTestCase";
}

void StateStyleManagerTestNg::TearDownTestSuite()
{
    GTEST_LOG_(INFO) << "StateStyleManagerTestNg TearDownTestCase";
}

void StateStyleManagerTestNg::SetUp()
{
    MockPipelineContext::SetUp();
}

void StateStyleManagerTestNg::TearDown()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: StateStyleTest001
 * @tc.desc: Create StateStyleManager and execute pressed listener.
 * @tc.type: FUNC
 */
HWTEST_F(StateStyleManagerTestNg, StateStyleTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create state style manger.
     * @tc.expected: State style pressed listener is valid.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(frameNode, nullptr);
    auto stateStyleMgr = AceType::MakeRefPtr<StateStyleManager>(frameNode);
    EXPECT_NE(stateStyleMgr, nullptr);
    stateStyleMgr->SetSupportedStates(UI_STATE_PRESSED);
    auto callback = stateStyleMgr->GetPressedListener();
    EXPECT_NE(callback, nullptr);

    /**
     * @tc.steps: step2. Create touch down event and execute it.
     * @tc.expected: Should change to pressed state.
     */

    TouchEventInfo touchEventInfo = TouchEventInfo("touch");
    TouchLocationInfo touchLocationInfo = TouchLocationInfo(1);
    touchLocationInfo.SetLocalLocation(Offset(100.0, 100.0));
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    touchEventInfo.AddTouchLocationInfo(std::move(touchLocationInfo));
    touchEventInfo.AddChangedTouchLocationInfo(std::move(touchLocationInfo));

    (*callback)(touchEventInfo);
    EXPECT_EQ(true, stateStyleMgr->IsCurrentStateOn(UI_STATE_PRESSED));

    /**
     * @tc.steps: step3. Create touch up event and execute it.
     * @tc.expected: Should cancel pressed state.
     */

    touchLocationInfo.SetTouchType(TouchType::UP);
    touchEventInfo.AddTouchLocationInfo(std::move(touchLocationInfo));
    touchEventInfo.AddChangedTouchLocationInfo(std::move(touchLocationInfo));

    (*callback)(touchEventInfo);
    EXPECT_EQ(false, stateStyleMgr->IsCurrentStateOn(UI_STATE_PRESSED));
}

/**
 * @tc.name: StateStyleTest002
 * @tc.desc: Create StateStyleManager and execute pressed listener when multi fingers.
 * @tc.type: FUNC
 */
HWTEST_F(StateStyleManagerTestNg, StateStyleTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create state style manger.
     * @tc.expected: State style pressed listener is valid.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(frameNode, nullptr);
    auto stateStyleMgr = AceType::MakeRefPtr<StateStyleManager>(frameNode);
    EXPECT_NE(stateStyleMgr, nullptr);
    stateStyleMgr->SetSupportedStates(UI_STATE_PRESSED);
    auto callback = stateStyleMgr->GetPressedListener();
    EXPECT_NE(callback, nullptr);

    /**
     * @tc.steps: step2. One finger touch down.
     * @tc.expected: Should change to pressed state.
     */

    TouchEventInfo touchEventInfo = TouchEventInfo("touch");
    TouchLocationInfo touchLocationInfo1 = TouchLocationInfo(1);
    touchLocationInfo1.SetLocalLocation(Offset(100.0, 100.0));
    touchLocationInfo1.SetTouchType(TouchType::DOWN);
    touchEventInfo.AddTouchLocationInfo(std::move(touchLocationInfo1));
    touchEventInfo.AddChangedTouchLocationInfo(std::move(touchLocationInfo1));

    (*callback)(touchEventInfo);
    EXPECT_EQ(true, stateStyleMgr->IsCurrentStateOn(UI_STATE_PRESSED));

    /**
     * @tc.steps: step3. One more finger touch down.
     * @tc.expected: Should hold on pressed state.
     */

    TouchLocationInfo touchLocationInfo2 = TouchLocationInfo(2);
    touchLocationInfo2.SetLocalLocation(Offset(100.0, 100.0));
    touchLocationInfo2.SetTouchType(TouchType::DOWN);
    touchEventInfo.AddTouchLocationInfo(std::move(touchLocationInfo2));
    touchEventInfo.AddChangedTouchLocationInfo(std::move(touchLocationInfo2));

    (*callback)(touchEventInfo);
    EXPECT_EQ(true, stateStyleMgr->IsCurrentStateOn(UI_STATE_PRESSED));

    /**
     * @tc.steps: step4. One finger touch up.
     * @tc.expected: Should hold on pressed state.
     */

    touchLocationInfo1.SetTouchType(TouchType::UP);
    touchEventInfo.AddTouchLocationInfo(std::move(touchLocationInfo1));
    touchEventInfo.AddChangedTouchLocationInfo(std::move(touchLocationInfo1));

    (*callback)(touchEventInfo);
    EXPECT_EQ(true, stateStyleMgr->IsCurrentStateOn(UI_STATE_PRESSED));

    /**
     * @tc.steps: step5. One more finger touch up.
     * @tc.expected: Should cancel pressed state.
     */

    touchLocationInfo2.SetTouchType(TouchType::UP);
    touchEventInfo.AddTouchLocationInfo(std::move(touchLocationInfo2));
    touchEventInfo.AddChangedTouchLocationInfo(std::move(touchLocationInfo2));

    (*callback)(touchEventInfo);
    EXPECT_EQ(false, stateStyleMgr->IsCurrentStateOn(UI_STATE_PRESSED));
}

/**
 * @tc.name: StateStyleTest003
 * @tc.desc: Create StateStyleManager and execute its functions.
 * @tc.type: FUNC
 */
HWTEST_F(StateStyleManagerTestNg, StateStyleTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create state style manger.
     * @tc.expected: Should have no scrolling parent.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    EXPECT_NE(frameNode, nullptr);
    auto stateStyleMgr = AceType::MakeRefPtr<StateStyleManager>(frameNode);
    EXPECT_NE(stateStyleMgr, nullptr);
    stateStyleMgr->HandleScrollingParent();
    bool hasScrollingParent = stateStyleMgr->GetHasScrollingParent();
    EXPECT_EQ(false, hasScrollingParent);

    /**
     * @tc.steps: step2. Set parent to current frame node.
     * @tc.expected:  Should have scrolling parent.
     */

    auto parent = AceType::MakeRefPtr<FrameNode>(V2::LIST_ETS_TAG, -1, AceType::MakeRefPtr<ListPattern>());
    EXPECT_NE(parent, nullptr);
    frameNode->SetParent(parent);
    stateStyleMgr->HandleScrollingParent();
    hasScrollingParent = stateStyleMgr->GetHasScrollingParent();
    EXPECT_EQ(true, hasScrollingParent);
}

/**
 * @tc.name: StateStyleTest004
 * @tc.desc: Create StateStyleManager and execute its functions.
 * @tc.type: FUNC
 */
HWTEST_F(StateStyleManagerTestNg, StateStyleTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create state style manger.
     * @tc.expected: State style pressed listener is valid.
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto stateStyleMgr = AceType::MakeRefPtr<StateStyleManager>(frameNode);
    stateStyleMgr->SetSupportedStates(UI_STATE_PRESSED);
    auto callback = stateStyleMgr->GetPressedListener();
    EXPECT_NE(callback, nullptr);
    auto callback2 = stateStyleMgr->GetPressedListener();
    EXPECT_EQ(callback, callback2);

    /**
     * @tc.steps: step2. Create condition that touches.empty()  changeTouches.empty()
     * @tc.expected: State style pressed listener is valid.
     */
    EXPECT_EQ(false, stateStyleMgr->IsCurrentStateOn(UI_STATE_PRESSED));
    TouchEventInfo touchEventInfo = TouchEventInfo("touch");
    (*callback)(touchEventInfo);
    EXPECT_EQ(false, stateStyleMgr->IsCurrentStateOn(UI_STATE_PRESSED));

    /**
     * @tc.steps: step3. Create condition that touches.empty()=false  changeTouches.empty true
     * @tc.expected: State style pressed listener is valid.
     */
    TouchLocationInfo touchLocationInfo = TouchLocationInfo(1);
    touchLocationInfo.SetLocalLocation(Offset(100.0, 100.0));
    touchLocationInfo.SetTouchType(TouchType::CANCEL);
    touchEventInfo.AddTouchLocationInfo(std::move(touchLocationInfo));
    stateStyleMgr->SetSupportedStates(UI_STATE_PRESSED);
    stateStyleMgr->SetCurrentUIState(UI_STATE_PRESSED, true);
    EXPECT_EQ(true, stateStyleMgr->IsCurrentStateOn(UI_STATE_PRESSED));
    (*callback)(touchEventInfo);
    EXPECT_EQ(true, stateStyleMgr->IsCurrentStateOn(UI_STATE_PRESSED));

    /**
     * @tc.steps: step3. Create condition that touches.empty false  changeTouches.empty false
     * @tc.expected: State style pressed listener is valid.
     */
    touchEventInfo.AddChangedTouchLocationInfo(std::move(touchLocationInfo));
    EXPECT_EQ(true, stateStyleMgr->IsCurrentStateOn(UI_STATE_PRESSED));
    (*callback)(touchEventInfo);
    EXPECT_EQ(false, stateStyleMgr->IsCurrentStateOn(UI_STATE_PRESSED));
}

/**
 * @tc.name: StateStyleTest005
 * @tc.desc: Create StateStyleManager and execute its functions.
 * @tc.type: FUNC
 */
HWTEST_F(StateStyleManagerTestNg, StateStyleTest005, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto stateStyleMgr = AceType::MakeRefPtr<StateStyleManager>(frameNode);
    auto callback = stateStyleMgr->GetPressedListener();
    EXPECT_NE(callback, nullptr);
    auto callback2 = stateStyleMgr->GetPressedListener();
    EXPECT_EQ(callback, callback2);

    TouchEventInfo touchEventInfo = TouchEventInfo("touch");
    TouchLocationInfo touchLocationInfo = TouchLocationInfo(1);
    touchLocationInfo.SetLocalLocation(Offset(-100.0, -100.0));
    touchLocationInfo.SetTouchType(TouchType::MOVE);
    touchEventInfo.AddTouchLocationInfo(std::move(touchLocationInfo));
    touchEventInfo.AddChangedTouchLocationInfo(std::move(touchLocationInfo));
    stateStyleMgr->SetCurrentUIState(UI_STATE_PRESSED, true);
    stateStyleMgr->ResetPressedPendingState();
    EXPECT_EQ(true, stateStyleMgr->IsCurrentStateOn(UI_STATE_PRESSED));
    (*callback)(touchEventInfo);
    EXPECT_EQ(true, stateStyleMgr->IsCurrentStateOn(UI_STATE_PRESSED));

    stateStyleMgr->SetCurrentUIState(UI_STATE_PRESSED, false);
    stateStyleMgr->ResetPressedPendingState();
    (*callback)(touchEventInfo);
    EXPECT_EQ(false, stateStyleMgr->IsCurrentStateOn(UI_STATE_PRESSED));
}

/**
 * @tc.name: StateStyleTest006
 * @tc.desc: Test HandleTouchDown function.
 * @tc.type: FUNC
 */
HWTEST_F(StateStyleManagerTestNg, StateStyleTest006, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto stateStyleMgr = AceType::MakeRefPtr<StateStyleManager>(frameNode);
    stateStyleMgr->SetSupportedStates(UI_STATE_NORMAL);
    stateStyleMgr->HandleTouchDown();
    EXPECT_EQ(false, stateStyleMgr->IsCurrentStateOn(UI_STATE_PRESSED));

    stateStyleMgr->SetSupportedStates(UI_STATE_PRESSED);
    stateStyleMgr->HandleTouchDown();
    EXPECT_EQ(true, stateStyleMgr->IsCurrentStateOn(UI_STATE_PRESSED));

    auto parent = AceType::MakeRefPtr<FrameNode>(V2::LIST_ETS_TAG, -1, AceType::MakeRefPtr<ListPattern>());
    EXPECT_NE(parent, nullptr);
    frameNode->SetParent(parent);
    stateStyleMgr->PendingCancelPressedState();
    EXPECT_EQ(true, stateStyleMgr->IsPressedCancelStatePending());
    stateStyleMgr->HandleTouchDown();
    EXPECT_EQ(false, stateStyleMgr->IsPressedCancelStatePending());
    EXPECT_EQ(true, stateStyleMgr->IsPressedStatePending());

    stateStyleMgr->ResetPressedCancelPendingState();
    stateStyleMgr->HandleTouchDown();
    EXPECT_EQ(false, stateStyleMgr->IsPressedCancelStatePending());
    EXPECT_EQ(true, stateStyleMgr->IsPressedStatePending());
}

/**
 * @tc.name: StateStyleTest007
 * @tc.desc: Test HandleTouchUp function.
 * @tc.type: FUNC
 */
HWTEST_F(StateStyleManagerTestNg, StateStyleTest007, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto stateStyleMgr = AceType::MakeRefPtr<StateStyleManager>(frameNode);
    auto parent = AceType::MakeRefPtr<FrameNode>(V2::LIST_ETS_TAG, -1, AceType::MakeRefPtr<ListPattern>());
    EXPECT_NE(parent, nullptr);
    frameNode->SetParent(parent);

    stateStyleMgr->PendingPressedState();
    stateStyleMgr->SetSupportedStates(UI_STATE_PRESSED);
    stateStyleMgr->SetCurrentUIState(UI_STATE_PRESSED, true);
    stateStyleMgr->HandleTouchUp();
    EXPECT_EQ(false, stateStyleMgr->IsPressedStatePending());
    EXPECT_EQ(true, stateStyleMgr->IsPressedCancelStatePending());
    EXPECT_EQ(true, stateStyleMgr->IsCurrentStateOn(UI_STATE_PRESSED));

    stateStyleMgr->ResetPressedPendingState();
    stateStyleMgr->ResetPressedCancelPendingState();
    stateStyleMgr->SetCurrentUIState(UI_STATE_PRESSED, true);
    stateStyleMgr->HandleTouchUp();
    EXPECT_EQ(false, stateStyleMgr->IsPressedStatePending());
    EXPECT_EQ(false, stateStyleMgr->IsCurrentStateOn(UI_STATE_PRESSED));

    stateStyleMgr->SetCurrentUIState(UI_STATE_PRESSED, true);
    stateStyleMgr->PendingCancelPressedState();
    stateStyleMgr->HandleTouchUp();
    EXPECT_EQ(true, stateStyleMgr->IsCurrentStateOn(UI_STATE_PRESSED));
}

/**
 * @tc.name: StateStyleTest008
 * @tc.desc: Test PostPressStyleTask function.
 * @tc.type: FUNC
 */
HWTEST_F(StateStyleManagerTestNg, StateStyleTest008, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto stateStyleMgr = AceType::MakeRefPtr<StateStyleManager>(frameNode);
    stateStyleMgr->PendingPressedState();
    EXPECT_EQ(true, stateStyleMgr->IsPressedStatePending());
    stateStyleMgr->SetSupportedStates(UI_STATE_PRESSED);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto taskExecutor = context->GetTaskExecutor();
    ASSERT_NE(taskExecutor, nullptr);
    stateStyleMgr->PostPressStyleTask(1);
    EXPECT_EQ(false, stateStyleMgr->IsCurrentStateOn(UI_STATE_PRESSED));

    stateStyleMgr->ResetPressedPendingState();
    stateStyleMgr->ResetPressedCancelPendingState();
    EXPECT_EQ(false, stateStyleMgr->IsPressedStatePending());
    stateStyleMgr->PostPressStyleTask(1);
    EXPECT_EQ(true, stateStyleMgr->IsCurrentStateOn(UI_STATE_PRESSED));
}

/**
 * @tc.name: StateStyleTest009
 * @tc.desc: Test PostPressCancelStyleTask function.
 * @tc.type: FUNC
 */
HWTEST_F(StateStyleManagerTestNg, StateStyleTest009, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto stateStyleMgr = AceType::MakeRefPtr<StateStyleManager>(frameNode);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto taskExecutor = context->GetTaskExecutor();
    ASSERT_NE(taskExecutor, nullptr);

    stateStyleMgr->SetSupportedStates(UI_STATE_PRESSED);
    stateStyleMgr->SetCurrentUIState(UI_STATE_PRESSED, true);

    stateStyleMgr->PendingPressedState();
    stateStyleMgr->PendingCancelPressedState();
    stateStyleMgr->PostPressCancelStyleTask(1);
    EXPECT_EQ(true, stateStyleMgr->IsCurrentStateOn(UI_STATE_PRESSED));

    stateStyleMgr->SetCurrentUIState(UI_STATE_PRESSED, true);
    stateStyleMgr->ResetPressedPendingState();
    stateStyleMgr->PendingCancelPressedState();
    stateStyleMgr->PostPressCancelStyleTask(1);
    EXPECT_EQ(true, stateStyleMgr->IsCurrentStateOn(UI_STATE_PRESSED));

    stateStyleMgr->SetCurrentUIState(UI_STATE_PRESSED, true);
    stateStyleMgr->PendingPressedState();
    stateStyleMgr->ResetPressedCancelPendingState();
    stateStyleMgr->PostPressCancelStyleTask(1);
    EXPECT_EQ(true, stateStyleMgr->IsCurrentStateOn(UI_STATE_PRESSED));

    stateStyleMgr->SetCurrentUIState(UI_STATE_PRESSED, true);
    stateStyleMgr->ResetPressedPendingState();
    stateStyleMgr->ResetPressedCancelPendingState();
    stateStyleMgr->PostPressCancelStyleTask(1);
    EXPECT_EQ(false, stateStyleMgr->IsCurrentStateOn(UI_STATE_PRESSED));
}

/**
 * @tc.name: StateStyleTest010
 * @tc.desc: Test HandleTouchUp function.
 * @tc.type: FUNC
 */
HWTEST_F(StateStyleManagerTestNg, StateStyleTest010, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto stateStyleMgr = AceType::MakeRefPtr<StateStyleManager>(frameNode);
    auto parent = AceType::MakeRefPtr<FrameNode>(V2::LIST_ETS_TAG, -1, AceType::MakeRefPtr<ListPattern>());
    frameNode->SetParent(parent);

    stateStyleMgr->PendingPressedState();
    stateStyleMgr->SetSupportedStates(UI_STATE_PRESSED);
    stateStyleMgr->SetCurrentUIState(UI_STATE_PRESSED, true);
    stateStyleMgr->hasScrollingParent_ = true;
    stateStyleMgr->HandleTouchUp();
    EXPECT_NE(parent, nullptr);
}

/**
 * @tc.name: StateStyleTest011
 * @tc.desc: Test CleanScrollingParentListener function.
 * @tc.type: FUNC
 */
HWTEST_F(StateStyleManagerTestNg, StateStyleTest011, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto stateStyleMgr = AceType::MakeRefPtr<StateStyleManager>(frameNode);
    auto parent = AceType::MakeRefPtr<FrameNode>(V2::LIST_ETS_TAG, -1, AceType::MakeRefPtr<ListPattern>());
    frameNode->SetParent(parent);

    stateStyleMgr->PendingPressedState();
    stateStyleMgr->SetSupportedStates(UI_STATE_PRESSED);
    stateStyleMgr->SetCurrentUIState(UI_STATE_PRESSED, true);
    stateStyleMgr->CleanScrollingParentListener();
    EXPECT_NE(parent, nullptr);
}

/**
 * @tc.name: StateStyleTest012
 * @tc.desc: Test CleanScrollingParentListener function.
 * @tc.type: FUNC
 */
HWTEST_F(StateStyleManagerTestNg, StateStyleTest012, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto stateStyleMgr = AceType::MakeRefPtr<StateStyleManager>(frameNode);

    stateStyleMgr->PendingPressedState();
    stateStyleMgr->SetSupportedStates(UI_STATE_PRESSED);
    stateStyleMgr->SetCurrentUIState(UI_STATE_PRESSED, true);
    stateStyleMgr->CleanScrollingParentListener();
    EXPECT_NE(frameNode, nullptr);
}

/**
 * @tc.name: StateStyleTest013
 * @tc.desc: Test CleanScrollingParentListener function.
 * @tc.type: FUNC
 */
HWTEST_F(StateStyleManagerTestNg, StateStyleTest013, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto stateStyleMgr = AceType::MakeRefPtr<StateStyleManager>(frameNode);
    auto pagePattern = AceType::MakeRefPtr<Pattern>();
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern);
    frameNode->SetParent(pageNode);

    stateStyleMgr->PendingPressedState();
    stateStyleMgr->SetSupportedStates(UI_STATE_PRESSED);
    stateStyleMgr->SetCurrentUIState(UI_STATE_PRESSED, true);
    stateStyleMgr->CleanScrollingParentListener();
    EXPECT_NE(pageNode, nullptr);
}

/**
 * @tc.name: StateStyleTest014
 * @tc.desc: Test Transform function.
 * @tc.type: FUNC
 */
HWTEST_F(StateStyleManagerTestNg, StateStyleTest014, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto stateStyleMgr = AceType::MakeRefPtr<StateStyleManager>(frameNode);
    PointF current = { 1.1f, 1.0f };
    RefPtr<FrameNode> node;
    stateStyleMgr->Transform(current, node);
    EXPECT_NE(frameNode, nullptr);
}

/**
 * @tc.name: StateStyleTest016
 * @tc.desc: test FireStateFunc
 * @tc.type: FUNC
 */
HWTEST_F(StateStyleManagerTestNg, StateStyleTest016, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    RefPtr<CustomNode> customNode =
        CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), "test");
    auto stateStyleMgr = AceType::MakeRefPtr<StateStyleManager>(frameNode);
    bool hasScrollingParent = true;
    auto swiperPattern = AceType::MakeRefPtr<SwiperPattern>();
    customNode->AddChild(frameNode);
    stateStyleMgr->FireStateFunc(UI_STATE_PRESSED, stateStyleMgr->currentState_, hasScrollingParent);
    EXPECT_EQ(true, hasScrollingParent);
}

/**
 * @tc.name: StateStyleTest017
 * @tc.desc: test FireStateFunc
 * @tc.type: FUNC
 */
HWTEST_F(StateStyleManagerTestNg, StateStyleTest017, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto contentNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 22, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    RefPtr<CustomNode> customNode =
        CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), "test");
    auto stateStyleMgr = AceType::MakeRefPtr<StateStyleManager>(frameNode);
    bool hasScrollingParent = true;
    auto popupBasePattern = AceType::MakeRefPtr<PopupBasePattern>();
    contentNode->pattern_ = popupBasePattern;
    customNode->SetParent(contentNode);
    frameNode->SetParent(contentNode);
    stateStyleMgr->FireStateFunc(UI_STATE_PRESSED, stateStyleMgr->currentState_, hasScrollingParent);
    EXPECT_EQ(true, hasScrollingParent);
}

/**
 * @tc.name: StateStyleTest018
 * @tc.desc: test AddSupportedUIStateWithCallback
 * @tc.type: FUNC
 */
HWTEST_F(StateStyleManagerTestNg, StateStyleTest018, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto stateStyleMgr = AceType::MakeRefPtr<StateStyleManager>(frameNode);
    std::function<void(UIState)> callback = [](UIState state) {};
    stateStyleMgr->AddSupportedUIStateWithCallback(UI_STATE_NORMAL, callback, true);
    EXPECT_TRUE(stateStyleMgr->HasStateStyle(UI_STATE_NORMAL));
       
    stateStyleMgr->AddSupportedUIStateWithCallback(UI_STATE_NORMAL | UI_STATE_PRESSED, callback, true);
    EXPECT_TRUE(stateStyleMgr->HasStateStyle(UI_STATE_PRESSED));

    stateStyleMgr->AddSupportedUIStateWithCallback(UI_STATE_NORMAL | UI_STATE_PRESSED, callback, false);
    bool flag = (stateStyleMgr->userStateStyleSubscribers_.first & UI_STATE_PRESSED) == UI_STATE_PRESSED;
    EXPECT_TRUE(flag);
}

/**
 * @tc.name: StateStyleTest019
 * @tc.desc: test RemoveSupportedUIState
 * @tc.type: FUNC
 */
HWTEST_F(StateStyleManagerTestNg, StateStyleTest019, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto stateStyleMgr = AceType::MakeRefPtr<StateStyleManager>(frameNode);
    stateStyleMgr->RemoveSupportedUIState(UI_STATE_NORMAL, true);
    EXPECT_TRUE(stateStyleMgr->HasStateStyle(UI_STATE_NORMAL));
    EXPECT_FALSE(stateStyleMgr->HasStateStyle(UI_STATE_PRESSED));

    std::function<void(UIState)> callback = [](UIState state) {};
    stateStyleMgr->AddSupportedUIStateWithCallback(UI_STATE_PRESSED, callback, true);
    stateStyleMgr->AddSupportedUIStateWithCallback(UI_STATE_PRESSED, callback, false);
    EXPECT_TRUE(stateStyleMgr->HasStateStyle(UI_STATE_PRESSED));

    stateStyleMgr->RemoveSupportedUIState(UI_STATE_PRESSED, true);
    EXPECT_TRUE(stateStyleMgr->HasStateStyle(UI_STATE_PRESSED));

    stateStyleMgr->RemoveSupportedUIState(UI_STATE_PRESSED, false);
    EXPECT_FALSE(stateStyleMgr->HasStateStyle(UI_STATE_PRESSED));
}

/**
 * @tc.name: StateStyleTest020
 * @tc.desc: test HandleStateChangeInternal
 * @tc.type: FUNC
 */
HWTEST_F(StateStyleManagerTestNg, StateStyleTest020, TestSize.Level1)
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::BUTTON_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto stateStyleMgr = AceType::MakeRefPtr<StateStyleManager>(frameNode);

    std::function<void(UIState)> callback = [](UIState state) {};
    stateStyleMgr->AddSupportedUIStateWithCallback(UI_STATE_NORMAL | UI_STATE_PRESSED, callback, true);
    EXPECT_TRUE(stateStyleMgr->HasStateStyle(UI_STATE_NORMAL | UI_STATE_PRESSED));
    stateStyleMgr->HandleStateChangeInternal(UI_STATE_PRESSED, stateStyleMgr->currentState_, true);
    EXPECT_TRUE(stateStyleMgr->innerStateStyleSubscribers_.second);

    stateStyleMgr->AddSupportedUIStateWithCallback(UI_STATE_NORMAL | UI_STATE_PRESSED, callback, false);
    EXPECT_TRUE(stateStyleMgr->HasStateStyle(UI_STATE_NORMAL | UI_STATE_PRESSED));
    stateStyleMgr->HandleStateChangeInternal(UI_STATE_PRESSED, stateStyleMgr->currentState_, false);
    EXPECT_TRUE(stateStyleMgr->userStateStyleSubscribers_.second);
}
} // namespace OHOS::Ace::NG
