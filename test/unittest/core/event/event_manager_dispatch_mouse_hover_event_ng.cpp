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
#include "gtest/gtest.h"
#include "test/unittest/core/event/event_manager_test_ng.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {

class HoverEventTargetTest : public HoverEventTarget {
    DECLARE_ACE_TYPE(HoverEventTargetTest, HoverEventTarget);

public:
    HoverEventTargetTest(const std::string& nodeName, int32_t nodeId, bool setStopPropagation = false,
        int32_t expectedResult = 0, bool expectedHoverIn = true)
        : HoverEventTarget(nodeName, nodeId), setStopPropagation_(setStopPropagation), expectedResult_(expectedResult),
          expectedHoveIn_(expectedHoverIn)
    {
        SetCallback([this](bool isHoverIn, HoverInfo& info) {
            // set stop propagation
            info.SetStopPropagation(setStopPropagation_);
            isHoverIn_ = isHoverIn;
            callbackInvokeCount_++;
        });
    }

    int32_t GetCallbackInvokeCount() const
    {
        return callbackInvokeCount_;
    }

    void ResetCallbackInvokeCount()
    {
        callbackInvokeCount_ = 0;
    }

    int32_t GetExpectedResult() const
    {
        return expectedResult_;
    }

    bool GetIsHoveIn() const
    {
        return isHoverIn_;
    }

    void ResetIsHoveIn()
    {
        isHoverIn_ = false;
    }

    bool CheckExpectResult() const
    {
        return callbackInvokeCount_ == expectedResult_ && isHoverIn_ == expectedHoveIn_;
    }

    void SetStopPropagation(bool flag)
    {
        setStopPropagation_ = flag;
    }

private:
    bool setStopPropagation_ = false;
    int32_t callbackInvokeCount_ = 0;
    bool isHoverIn_ = false;
    int32_t expectedResult_ = 0;
    bool expectedHoveIn_ = false;
};

class EventManagerDispatchMouseHoverEventNG : public EventManagerTestNg {
public:
    static void SetUpTestSuite()
    {
        EventManagerTestNg::SetUpTestSuite();
    }
    static void TearDownTestSuite()
    {
        EventManagerTestNg::TearDownTestSuite();
    }
};

/**
 * @tc.name: EventManagerDispatchMouseHoverEventNG001
 * @tc.desc: hove in event only will be invoked once.
 * @tc.type: FUNC
 */

HWTEST_F(EventManagerDispatchMouseHoverEventNG, EventManagerDispatchMouseHoverEventNG001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    TouchTestResult testCases = {
        AceType::MakeRefPtr<HoverEventTargetTest>("0", 0, false, 1, true),
        AceType::MakeRefPtr<HoverEventTargetTest>("1", 1, false, 1, true),
        AceType::MakeRefPtr<HoverEventTargetTest>("2", 2, false, 1, true),
        AceType::MakeRefPtr<HoverEventTargetTest>("3", 3, false, 1, true),
    };

    /**
     * @tc.steps: step2. Inject mock mouseEvent, mock mouse event not leave current node
     * @tc.expected: hove in event only be invoked once
     */

    for (auto i = 0; i < 10; i++) {
        MouseEvent event;
        event.action = MouseAction::MOVE;
        // mock mouse test result
        eventManager->UpdateHoverNode(event, testCases);
        auto result = eventManager->DispatchMouseHoverEventNG(event);
        // result of DispatchMouseHoverEventNG always be true
        ASSERT_TRUE(result);

        for (auto iter = testCases.begin(); iter != testCases.end(); iter++) {
            auto hoverEventTargetTest = AceType::DynamicCast<HoverEventTargetTest>(*iter);
            ASSERT_NE(hoverEventTargetTest, nullptr);

            EXPECT_TRUE(hoverEventTargetTest->CheckExpectResult());
        }
    }
}

/**
 * @tc.name: EventManagerDispatchMouseHoverEventNG002
 * @tc.desc: test stop progration can stop hove in event dispatch.
 * @tc.type: FUNC
 */

HWTEST_F(EventManagerDispatchMouseHoverEventNG, EventManagerDispatchMouseHoverEventNG002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    TouchTestResult testCases = {
        AceType::MakeRefPtr<HoverEventTargetTest>("0", 0, false, 1, true),
        AceType::MakeRefPtr<HoverEventTargetTest>("1", 1, true, 1, true), // this target stop progration the hove event
        AceType::MakeRefPtr<HoverEventTargetTest>("2", 2, false, 0, false),
        AceType::MakeRefPtr<HoverEventTargetTest>("3", 3, false, 0, false),
    };

    /**
     * @tc.steps: step2. Inject mock mouseEvent, suppose mock mouse event not leave current node
     * @tc.expected: when some one stop progration ohter targets can not be invoked.
     */

    for (auto i = 0; i < 10; i++) {
        MouseEvent event;
        event.action = MouseAction::MOVE;
        // mock mouse test result
        eventManager->UpdateHoverNode(event, testCases);
        auto result = eventManager->DispatchMouseHoverEventNG(event);
        // result of DispatchMouseHoverEventNG always be true
        ASSERT_TRUE(result);

        for (auto iter = testCases.begin(); iter != testCases.end(); iter++) {
            auto hoverEventTargetTest = AceType::DynamicCast<HoverEventTargetTest>(*iter);
            ASSERT_NE(hoverEventTargetTest, nullptr);

            EXPECT_TRUE(hoverEventTargetTest->CheckExpectResult());
        }
    }
}

/**
 * @tc.name: EventManagerDispatchMouseHoverEventNG003
 * @tc.desc: test hove out event dispatch and stop progration no work for hove out event dispatch
 * @tc.type: FUNC
 */

HWTEST_F(EventManagerDispatchMouseHoverEventNG, EventManagerDispatchMouseHoverEventNG003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventManager.
     * @tc.expected: eventManager is not null.
     */
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    std::vector<RefPtr<HoverEventTargetTest>> testCases = {
        AceType::MakeRefPtr<HoverEventTargetTest>("0", 0, false, 1, true),
        AceType::MakeRefPtr<HoverEventTargetTest>("1", 1, false, 1, true),
        AceType::MakeRefPtr<HoverEventTargetTest>("2", 2, false, 1, true),
        AceType::MakeRefPtr<HoverEventTargetTest>("3", 3, false, 1, true),
    };

    /**
     * @tc.steps: step2. Create a scene of hove in.
     * @tc.expected: All hove target will be invoked once hove in.
     */

    TouchTestResult mouseTouchTestResult1(testCases.begin(), testCases.end());
    MouseEvent event;
    event.action = MouseAction::MOVE;
    eventManager->UpdateHoverNode(event, mouseTouchTestResult1);
    eventManager->DispatchMouseHoverEventNG(event);
    for (auto iter = mouseTouchTestResult1.begin(); iter != mouseTouchTestResult1.end(); iter++) {
        auto hoverEventTargetTest = AceType::DynamicCast<HoverEventTargetTest>(*iter);
        ASSERT_NE(hoverEventTargetTest, nullptr);

        EXPECT_TRUE(hoverEventTargetTest->CheckExpectResult());
    }

    /**
     * @tc.steps: step3. Cerate as scene of hove out, suppose item 0 and item 3 can not be touch test.
     */
    TouchTestResult mouseTouchTestResult2;
    testCases[0]->ResetCallbackInvokeCount();
    testCases[0]->SetStopPropagation(false); // item 0 set stop progration
    mouseTouchTestResult2.emplace_back(testCases[1]);
    mouseTouchTestResult2.emplace_back(testCases[2]);
    testCases[3]->ResetCallbackInvokeCount();

    /**
     * @tc.steps: step4. Inject mock mouseEvent 10 times, suppose mock mouse event leave item 0 and item 3
     * @tc.expected: item 0 and item 3 can be invoke once hove out, other targets have no change.
     */
    for (auto i = 0; i < 10; i++) {
        MouseEvent event;
        event.action = MouseAction::MOVE;
        eventManager->UpdateHoverNode(event, mouseTouchTestResult2);
        auto result = eventManager->DispatchMouseHoverEventNG(event);
        // result of DispatchMouseHoverEventNG always be true
        ASSERT_TRUE(result);
    }

    EXPECT_EQ(testCases[0]->GetCallbackInvokeCount(), 1);
    EXPECT_FALSE(testCases[0]->GetIsHoveIn());
    EXPECT_EQ(testCases[3]->GetCallbackInvokeCount(), 1);
    EXPECT_FALSE(testCases[3]->GetIsHoveIn());

    for (auto iter = mouseTouchTestResult2.begin(); iter != mouseTouchTestResult2.end(); iter++) {
        auto hoverEventTargetTest = AceType::DynamicCast<HoverEventTargetTest>(*iter);
        ASSERT_NE(hoverEventTargetTest, nullptr);

        EXPECT_EQ(hoverEventTargetTest->GetCallbackInvokeCount(), 1);
        EXPECT_TRUE(hoverEventTargetTest->GetIsHoveIn());
    }
}
} // namespace OHOS::Ace::NG