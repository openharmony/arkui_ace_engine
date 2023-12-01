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
#include "core/components_ng/event/state_style_manager.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/pattern.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

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
    bool hasScrollingParent = stateStyleMgr->HandleScrollingParent();
    EXPECT_EQ(false, hasScrollingParent);

    /**
     * @tc.steps: step2. Set parent to current frame node.
     * @tc.expected:  Should have scrolling parent.
     */

    auto parent = AceType::MakeRefPtr<FrameNode>(V2::LIST_ETS_TAG, -1, AceType::MakeRefPtr<ListPattern>());
    EXPECT_NE(parent, nullptr);
    frameNode->SetParent(parent);
    hasScrollingParent = stateStyleMgr->HandleScrollingParent();
    EXPECT_EQ(true, hasScrollingParent);
}
} // namespace OHOS::Ace::NG
