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
#include "test/unittest/core/gestures/gestures_common_test_ng.h"
#include "core/common/event_manager.h"

#include "core/components_ng/gestures/recognizers/click_recognizer.h"
#include "core/components_ng/gestures/recognizers/multi_fingers_recognizer.h"
#include "core/event/ace_events.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
class MultiFingersRecognizerTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void MultiFingersRecognizerTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void MultiFingersRecognizerTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

struct CheckDownFingersTestCase {
    InputEventType inputEventType_ = InputEventType::AXIS;
    RefereeState lastRefereeState_ = RefereeState::READY;
    RefereeState refereeState_ = RefereeState::READY;
    bool isPostEventResult_ = false;
    std::vector<int32_t> downFingerIds;
    std::vector<int32_t> touchPointIds;
    size_t expectFingerListSize_;

    CheckDownFingersTestCase(InputEventType inputEventType, RefereeState lastRefereeState, RefereeState refereeState,
        bool isPostEventResult, std::vector<int32_t> downFingerIds, std::vector<int32_t> touchPointIds,
        size_t expectFingerListSize) : inputEventType_(inputEventType), lastRefereeState_(lastRefereeState),
        refereeState_(refereeState), isPostEventResult_(isPostEventResult), downFingerIds(std::move(downFingerIds)),
        touchPointIds(std::move(touchPointIds)), expectFingerListSize_(expectFingerListSize) {}
};

const std::vector<CheckDownFingersTestCase> CHECK_DOWN_FINGERS_TEST_CASES = {
    CheckDownFingersTestCase(InputEventType::AXIS, RefereeState::READY,
        RefereeState::READY, false, { 1 }, { 0 }, 1),
    CheckDownFingersTestCase(InputEventType::TOUCH_SCREEN, RefereeState::PENDING,
        RefereeState::PENDING, false, { 1 }, { 0 }, 1),
    CheckDownFingersTestCase(InputEventType::TOUCH_SCREEN, RefereeState::PENDING,
        RefereeState::PENDING_BLOCKED, false, { 1 }, { 0 }, 1),
    CheckDownFingersTestCase(InputEventType::TOUCH_SCREEN, RefereeState::PENDING,
        RefereeState::SUCCEED_BLOCKED, false, { 1 }, { 0 }, 1),
    CheckDownFingersTestCase(InputEventType::TOUCH_SCREEN, RefereeState::PENDING,
        RefereeState::READY, false, { 1 }, { 0 }, 1),
    CheckDownFingersTestCase(InputEventType::TOUCH_SCREEN, RefereeState::PENDING_BLOCKED,
        RefereeState::PENDING, false, { 1 }, { 0 }, 1),
    CheckDownFingersTestCase(InputEventType::TOUCH_SCREEN, RefereeState::PENDING_BLOCKED,
        RefereeState::PENDING_BLOCKED, false, { 1 }, { 0 }, 1),
    CheckDownFingersTestCase(InputEventType::TOUCH_SCREEN, RefereeState::PENDING_BLOCKED,
        RefereeState::SUCCEED_BLOCKED, false, { 1 }, { 0 }, 1),
    CheckDownFingersTestCase(InputEventType::TOUCH_SCREEN, RefereeState::PENDING_BLOCKED,
        RefereeState::READY, false, { 1 }, { 0 }, 1),
    CheckDownFingersTestCase(InputEventType::TOUCH_SCREEN, RefereeState::SUCCEED_BLOCKED,
        RefereeState::PENDING, false, { 1 }, { 0 }, 1),
    CheckDownFingersTestCase(InputEventType::TOUCH_SCREEN, RefereeState::SUCCEED_BLOCKED,
        RefereeState::PENDING_BLOCKED, false, { 1 }, { 0 }, 1),
    CheckDownFingersTestCase(InputEventType::TOUCH_SCREEN, RefereeState::SUCCEED_BLOCKED,
        RefereeState::SUCCEED_BLOCKED, false, { 1 }, { 0 }, 1),
    CheckDownFingersTestCase(InputEventType::TOUCH_SCREEN, RefereeState::SUCCEED_BLOCKED,
        RefereeState::READY, false, { 1 }, { 0 }, 1),
    CheckDownFingersTestCase(InputEventType::TOUCH_SCREEN, RefereeState::READY,
        RefereeState::PENDING, false, { 1 }, { 0 }, 1),
    CheckDownFingersTestCase(InputEventType::TOUCH_SCREEN, RefereeState::READY,
        RefereeState::PENDING_BLOCKED, false, { 1 }, { 0 }, 1),
    CheckDownFingersTestCase(InputEventType::TOUCH_SCREEN, RefereeState::READY,
        RefereeState::SUCCEED_BLOCKED, false, { 1 }, { 0 }, 1),
    CheckDownFingersTestCase(InputEventType::TOUCH_SCREEN, RefereeState::READY,
        RefereeState::READY, false, { 1 }, { 0 }, 0),
    CheckDownFingersTestCase(InputEventType::TOUCH_SCREEN, RefereeState::READY,
        RefereeState::READY, true, { 1 }, { 0 }, 1),
    CheckDownFingersTestCase(InputEventType::TOUCH_SCREEN, RefereeState::READY,
        RefereeState::READY, false, { 1, 2, 3 }, { 1, 2 }, 2),
};

/**
 * @tc.name: Test001
 * @tc.desc: Test InitGlobalValue
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, Test001, TestSize.Level1)
{
    RefPtr<ClickRecognizer> clicRecognizerFirst = AceType::MakeRefPtr<ClickRecognizer>(5, 5);
    RefPtr<ClickRecognizer> clicRecognizerSecond = AceType::MakeRefPtr<ClickRecognizer>(10, 5);
    RefPtr<ClickRecognizer> clicRecognizerThird = AceType::MakeRefPtr<ClickRecognizer>(-1, 5);
    clicRecognizerFirst->InitGlobalValue(SourceType::MOUSE);
    clicRecognizerSecond->InitGlobalValue(SourceType::MOUSE);
    clicRecognizerThird->InitGlobalValue(SourceType::MOUSE);
    EXPECT_NE(clicRecognizerFirst, clicRecognizerSecond);
}

/**
 * @tc.name: Test002
 * @tc.desc: Test IsNeedResetStatus
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, Test002, TestSize.Level1)
{
    RefPtr<ClickRecognizer> clicRecognizerFirst = AceType::MakeRefPtr<ClickRecognizer>(5, 5);
    RefPtr<MultiFingersRecognizer> fingersRecognizer = clicRecognizerFirst;
    auto status = fingersRecognizer->IsNeedResetStatus();
    EXPECT_EQ(status, true);
}

/**
 * @tc.name: Test003
 * @tc.desc: Test IsNeedResetStatus
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, Test003, TestSize.Level1)
{
    RefPtr<ClickRecognizer> clicRecognizerFirst = AceType::MakeRefPtr<ClickRecognizer>(5, 5);
    RefPtr<MultiFingersRecognizer> fingersRecognizer = clicRecognizerFirst;
    AxisEvent event;
    event.id = 1;
    event.x = 10.1;
    event.y = 10.1;
    event.screenX = 10.1;
    event.screenY = 10.1;
    event.globalDisplayX = 10.1;
    event.globalDisplayY = 10.1;
    event.sourceType = SourceType::MOUSE;
    event.sourceTool = SourceTool::PEN;
    event.originalId = 1;
    fingersRecognizer->UpdateTouchPointWithAxisEvent(event);
    auto status = fingersRecognizer->IsNeedResetStatus();
    EXPECT_EQ(status, true);
}

template<class T>
class MockReferenced : public Referenced {
public:
    MOCK_METHOD(RefPtr<T>, Claim, (T * rawPtr), ());
};

/**
 * @tc.name: Test004
 * @tc.desc: Test IsNeedResetStatus
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, Test004, TestSize.Level1)
{
    MockReferenced<MultiFingersRecognizer> test;
    EXPECT_CALL(test, Claim(_)).WillRepeatedly(Return(nullptr));
    RefPtr<ClickRecognizer> clicRecognizerFirst = AceType::MakeRefPtr<ClickRecognizer>(5, 5);
    RefPtr<MultiFingersRecognizer> fingersRecognizer = clicRecognizerFirst;
    AxisEvent event;
    event.id = 1;
    event.x = 10.1;
    event.y = 10.1;
    event.screenX = 10.1;
    event.screenY = 10.1;
    event.sourceType = SourceType::MOUSE;
    event.sourceTool = SourceTool::PEN;
    event.originalId = 1;
    fingersRecognizer->UpdateTouchPointWithAxisEvent(event);
    auto status = fingersRecognizer->IsNeedResetStatus();
    EXPECT_EQ(status, true);
}

class MockRecognizerGroup : public ClickRecognizer {
public:
    MOCK_CONST_METHOD0(GetGroupRecognizer, const std::list<RefPtr<NGGestureRecognizer>>&());
};

/**
 * @tc.name: Test005
 * @tc.desc: Test IsNeedResetStatus
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, Test005, TestSize.Level1)
{
    std::list<RefPtr<NGGestureRecognizer>> listTest;
    listTest.resize(10, nullptr);
    MockRecognizerGroup groupTest;
    EXPECT_CALL(groupTest, GetGroupRecognizer()).WillRepeatedly(ReturnRef(listTest));
    RefPtr<ClickRecognizer> clicRecognizerFirst = AceType::MakeRefPtr<ClickRecognizer>(5, 5);
    RefPtr<MultiFingersRecognizer> fingersRecognizer = clicRecognizerFirst;
    AxisEvent event;
    event.id = 1;
    event.x = 10.1;
    event.y = 10.1;
    event.screenX = 10.1;
    event.screenY = 10.1;
    event.sourceType = SourceType::MOUSE;
    event.sourceTool = SourceTool::PEN;
    event.originalId = 1;
    fingersRecognizer->UpdateTouchPointWithAxisEvent(event);
    auto status = fingersRecognizer->IsNeedResetStatus();
    EXPECT_EQ(status, true);
}

class MockMultiFingersRecognizer : public MultiFingersRecognizer {
public:
    MockMultiFingersRecognizer() : MultiFingersRecognizer() {}
    explicit MockMultiFingersRecognizer(int32_t fingers) : MultiFingersRecognizer(fingers) {}
    MockMultiFingersRecognizer(int32_t fingers, bool isLimitFingerCount)
        : MultiFingersRecognizer(fingers, isLimitFingerCount) {}

    MOCK_METHOD(void, OnFinishGestureReferee, (int32_t, bool), ());
    MOCK_METHOD(bool, IsNeedResetStatus, (), ());
    MOCK_METHOD(void, ResetStatusOnFinish, (bool isBlocked), ());
    void BatchAdjudicate(const RefPtr<NGGestureRecognizer>& recognizer, GestureDisposal disposal) {}
    void OnBeginGestureReferee(int32_t touchId, int32_t originalId, bool needUpdateChild = false) {}
    void HandleTouchDownEvent(const TouchEvent& event) {}
    void HandleTouchUpEvent(const TouchEvent& event) {}
    void HandleTouchMoveEvent(const TouchEvent& event) {}
    void HandleTouchCancelEvent(const TouchEvent& event) {}
    void HandleTouchDownEvent(const AxisEvent& event) {}
    void HandleTouchUpEvent(const AxisEvent& event) {}
    void HandleTouchMoveEvent(const AxisEvent& event) {}
    void HandleTouchCancelEvent(const AxisEvent& event) {}
    void OnResetStatus() {}
    void OnSucceedCancel() {}
    void OnAccepted() {}
    void OnRejected() {}
};

class MockNGGestureRecognizer : public NGGestureRecognizer {
public:
    MOCK_METHOD(void, ResetStatusOnFinish, (bool isBlocked), ());
    void BatchAdjudicate(const RefPtr<NGGestureRecognizer>& recognizer, GestureDisposal disposal) {}
    void OnBeginGestureReferee(int32_t touchId, int32_t originalId, bool needUpdateChild = false) {}
    void HandleTouchDownEvent(const TouchEvent& event) {}
    void HandleTouchUpEvent(const TouchEvent& event) {}
    void HandleTouchMoveEvent(const TouchEvent& event) {}
    void HandleTouchCancelEvent(const TouchEvent& event) {}
    void HandleTouchDownEvent(const AxisEvent& event) {}
    void HandleTouchUpEvent(const AxisEvent& event) {}
    void HandleTouchMoveEvent(const AxisEvent& event) {}
    void HandleTouchCancelEvent(const AxisEvent& event) {}
    void OnResetStatus() {}
    void OnSucceedCancel() {}
    void OnAccepted() {}
    void OnRejected() {}
    bool CheckTouchId(int32_t touchId)
    {
        return false;
    }
    std::map<int32_t, TouchEvent> GetTouchPoints()
    {
        std::map<int32_t, TouchEvent> emptyTouchPoints;
        return emptyTouchPoints;
    }
    void CheckCurrentFingers() const {};
};

/**
 * @tc.name: Test006
 * @tc.desc: Test UpdateTouchPointWithAxisEvent
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, Test006, TestSize.Level1)
{
    std::list<RefPtr<NGGestureRecognizer>> listTest;
    listTest.resize(10, nullptr);
    RefPtr<ClickRecognizer> clicRecognizerFirst = AceType::MakeRefPtr<ClickRecognizer>(5, 5);
    RefPtr<MultiFingersRecognizer> fingersRecognizer = clicRecognizerFirst;
    AxisEvent event;
    event.id = 1;
    event.x = 10.1;
    event.y = 10.1;
    event.screenX = 10.1;
    event.screenY = 10.1;
    event.sourceType = SourceType::MOUSE;
    event.sourceTool = SourceTool::PEN;
    event.originalId = 1;
    fingersRecognizer->UpdateTouchPointWithAxisEvent(event);
    EXPECT_EQ(event.originalId, 1);
}

/**
 * @tc.name: Test007
 * @tc.desc: Test CleanRecognizerState
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, Test007, TestSize.Level1)
{
    RefPtr<ClickRecognizer> clicRecognizerFirst = AceType::MakeRefPtr<ClickRecognizer>(5, 5);
    RefPtr<MultiFingersRecognizer> fingersRecognizer = clicRecognizerFirst;
    fingersRecognizer->refereeState_ = RefereeState::SUCCEED;
    fingersRecognizer->currentFingers_ = 0;
    fingersRecognizer->MultiFingersRecognizer::CleanRecognizerState();
    fingersRecognizer->refereeState_ = RefereeState::FAIL;
    fingersRecognizer->currentFingers_ = 0;
    fingersRecognizer->MultiFingersRecognizer::CleanRecognizerState();
    fingersRecognizer->refereeState_ = RefereeState::DETECTING;
    fingersRecognizer->currentFingers_ = 0;
    fingersRecognizer->MultiFingersRecognizer::CleanRecognizerState();
    fingersRecognizer->refereeState_ = RefereeState::SUCCEED;
    fingersRecognizer->currentFingers_ = 1;
    fingersRecognizer->MultiFingersRecognizer::CleanRecognizerState();
    EXPECT_EQ(fingersRecognizer->currentFingers_, 1);
}

/**
 * @tc.name: Test008
 * @tc.desc: Test CheckFingerListInDownFingers
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, Test008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create pipelineContext and eventManager.
     */
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    context->eventManager_ = eventManager;
    int32_t caseNum = 0;
    for (const auto& testCase : CHECK_DOWN_FINGERS_TEST_CASES) {
        /**
         * @tc.steps: step2. create clickRecognizer.
         */
        RefPtr<ClickRecognizer> clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(5, 5);
        clickRecognizer->inputEventType_ = testCase.inputEventType_;
        clickRecognizer->lastRefereeState_ = testCase.lastRefereeState_;
        clickRecognizer->refereeState_ = testCase.refereeState_;
        clickRecognizer->isPostEventResult_ = testCase.isPostEventResult_;
        eventManager->downFingerIds_.clear();
        for (auto id : testCase.downFingerIds) {
            eventManager->downFingerIds_[id] = id;
        }
        for (auto id : testCase.touchPointIds) {
            TouchEvent event;
            event.id = id;
            event.originalId = id;
            clickRecognizer->touchPoints_[id] = event;
        }
        clickRecognizer->UpdateFingerListInfo();
        EXPECT_EQ(clickRecognizer->fingerList_.size(), testCase.expectFingerListSize_);
        caseNum++;
    }
}

/**
 * @tc.name: Test009
 * @tc.desc: Test UpdateFingerListInfo
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, Test009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create pipelineContext and eventManager.
     */
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    context->eventManager_ = eventManager;

    /**
     * @tc.steps: step2. create clickRecognizer.
     */
    RefPtr<ClickRecognizer> clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(5, 5);
    clickRecognizer->inputEventType_ = InputEventType::TOUCH_SCREEN;
    clickRecognizer->lastRefereeState_ = RefereeState::SUCCEED;
    clickRecognizer->refereeState_ = RefereeState::SUCCEED;
    clickRecognizer->isPostEventResult_ = false;
    eventManager->downFingerIds_.clear();
    for (int32_t id = 0; id < 2; id++) {
        eventManager->downFingerIds_[id] = id;
    }
    for (int32_t id = 0; id < 2; id++) {
        TouchEvent event;
        event.id = id;
        event.pointers.clear();
        clickRecognizer->touchPoints_[id] = event;
    }
    clickRecognizer->UpdateFingerListInfo();
    EXPECT_EQ(clickRecognizer->lastPointEvent_, nullptr);
}

/**
 * @tc.name: GetGestureInfoString001
 * @tc.desc: Test MultiFingersRecognizerTestNg function: GetGestureInfoString with touchPoints_
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, GetGestureInfoString001, TestSize.Level1)
{
    RefPtr<ClickRecognizer> clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(1, 1);

    /**
     * @tc.steps: call clickRecognizer with empty touchPoints_;
     * @tc.expected: result equal.
     */
    std::string result = clickRecognizer->GetGestureInfoString();
    EXPECT_THAT(result, HasSubstr("TP:[]"));

    /**
     * @tc.steps: call clickRecognizer with not empty touchPoints_;
     * @tc.expected: result equal.
     */
    TouchEvent event;
    event.id = 1;
    event.originalId = 2;
    clickRecognizer->touchPoints_[0] = event;
    result = clickRecognizer->GetGestureInfoString();
    EXPECT_THAT(result, HasSubstr("TP:[,0->(1,2)]"));
}

/**
 * @tc.name: GetGestureInfoString002
 * @tc.desc: Test MultiFingersRecognizerTestNg function: GetGestureInfoString with activeFingers_
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, GetGestureInfoString002, TestSize.Level1)
{
    RefPtr<ClickRecognizer> clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(1, 1);

    /**
     * @tc.steps: call clickRecognizer with empty activeFingers_;
     * @tc.expected: result equal.
     */
    std::string result = clickRecognizer->GetGestureInfoString();
    EXPECT_THAT(result, HasSubstr("TP:[]"));

    /**
     * @tc.steps: call clickRecognizer with not empty activeFingers_;
     * @tc.expected: result equal.
     */
    clickRecognizer->activeFingers_.emplace_back(1);
    result = clickRecognizer->GetGestureInfoString();
    EXPECT_THAT(result, HasSubstr("AF:[,1]"));
}

/**
 * @tc.name: GetGestureInfoString003
 * @tc.desc: Test MultiFingersRecognizerTestNg function: GetGestureInfoString with backupTouchPointsForSucceedBlock_
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, GetGestureInfoString003, TestSize.Level1)
{
    RefPtr<ClickRecognizer> clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(1, 1);

    /**
     * @tc.steps: call clickRecognizer with empty backupTouchPointsForSucceedBlock_;
     * @tc.expected: result equal.
     */
    std::string result = clickRecognizer->GetGestureInfoString();
    EXPECT_THAT(result, HasSubstr("TP:[]"));

    /**
     * @tc.steps: call clickRecognizer with not empty backupTouchPointsForSucceedBlock_;
     * @tc.expected: result equal.
     */
    TouchEvent event;
    event.id = 1;
    event.originalId = 2;
    clickRecognizer->touchPoints_[0] = event;
    clickRecognizer->SetTouchPointsForSucceedBlock();
    result = clickRecognizer->GetGestureInfoString();
    EXPECT_THAT(result, HasSubstr("BTP:[,0->(1,2)]"));
}

/**
 * @tc.name: IsNeedResetStatusTest001
 * @tc.desc: Test IsNeedResetStatus with non-zero valid fingers count
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, IsNeedResetStatusTest001, TestSize.Level1)
{
    RefPtr<ClickRecognizer> clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(5, 5);
    RefPtr<MultiFingersRecognizer> fingersRecognizer = clickRecognizer;
    fingersRecognizer->currentFingers_ = 1;
    TouchEvent event;
    event.type = TouchType::DOWN;
    fingersRecognizer->touchPoints_[0] = event;

    bool result = fingersRecognizer->IsNeedResetStatus();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: IsNeedResetStatusTest002
 * @tc.desc: Test IsNeedResetStatus with zero valid fingers and null group
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, IsNeedResetStatusTest002, TestSize.Level1)
{
    RefPtr<ClickRecognizer> clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(5, 5);
    RefPtr<MultiFingersRecognizer> fingersRecognizer = clickRecognizer;
    fingersRecognizer->currentFingers_ = 0;

    bool result = fingersRecognizer->IsNeedResetStatus();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: IsNeedResetStatusTest003
 * @tc.desc: Test IsNeedResetStatus with zero valid fingers and non-null group
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, IsNeedResetStatusTest003, TestSize.Level1)
{
    std::vector<RefPtr<NGGestureRecognizer>> emptyRecognizers;
    auto recognizerGroup = AceType::MakeRefPtr<ExclusiveRecognizer>(emptyRecognizers);
    RefPtr<ClickRecognizer> clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(5, 5);
    clickRecognizer->gestureGroup_ = recognizerGroup;
    RefPtr<MultiFingersRecognizer> fingersRecognizer = clickRecognizer;
    fingersRecognizer->currentFingers_ = 0;

    bool result = fingersRecognizer->IsNeedResetStatus();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: IsNeedResetStatusTest004
 * @tc.desc: Test IsNeedResetStatus with multi-fingers group needing reset
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, IsNeedResetStatusTest004, TestSize.Level1)
{
    auto clickRecognizer1 = AceType::MakeRefPtr<ClickRecognizer>(5, 5);
    auto clickRecognizer2 = AceType::MakeRefPtr<ClickRecognizer>(5, 5);
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = { clickRecognizer1, clickRecognizer2 };
    auto recognizerGroup = AceType::MakeRefPtr<ExclusiveRecognizer>(recognizers);
    
    RefPtr<MultiFingersRecognizer> fingersRecognizer1 = clickRecognizer1;
    RefPtr<MultiFingersRecognizer> fingersRecognizer2 = clickRecognizer2;
    fingersRecognizer1->currentFingers_ = 0;
    fingersRecognizer2->currentFingers_ = 0;

    bool result = fingersRecognizer1->IsNeedResetStatus();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: IsNeedResetStatusTest005
 * @tc.desc: Test IsNeedResetStatus with multi-fingers group not needing reset
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, IsNeedResetStatusTest005, TestSize.Level1)
{
    auto clickRecognizer1 = AceType::MakeRefPtr<ClickRecognizer>(5, 5);
    auto clickRecognizer2 = AceType::MakeRefPtr<ClickRecognizer>(5, 5);
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = { clickRecognizer1, clickRecognizer2 };
    auto recognizerGroup = AceType::MakeRefPtr<ExclusiveRecognizer>(recognizers);
    
    RefPtr<MultiFingersRecognizer> fingersRecognizer1 = clickRecognizer1;
    RefPtr<MultiFingersRecognizer> fingersRecognizer2 = clickRecognizer2;
    fingersRecognizer1->currentFingers_ = 0;
    fingersRecognizer2->currentFingers_ = 1;
    TouchEvent event;
    event.type = TouchType::DOWN;
    fingersRecognizer2->touchPoints_[0] = event;

    bool result = recognizerGroup->IsNeedResetStatus();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: DumpGestureInfoTest001
 * @tc.desc: Test DumpGestureInfo with null gestureInfo_
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, DumpGestureInfoTest001, TestSize.Level1)
{
    RefPtr<ClickRecognizer> clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(5, 5);
    RefPtr<MultiFingersRecognizer> fingersRecognizer = clickRecognizer;
    fingersRecognizer->gestureInfo_ = nullptr;

    std::string result = fingersRecognizer->DumpGestureInfo();
    EXPECT_EQ(result, "allowedTypes: [all]");
}

/**
 * @tc.name: DumpGestureInfoTest002
 * @tc.desc: Test DumpGestureInfo with empty allowedTypes
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, DumpGestureInfoTest002, TestSize.Level1)
{
    RefPtr<ClickRecognizer> clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(5, 5);
    RefPtr<MultiFingersRecognizer> fingersRecognizer = clickRecognizer;
    fingersRecognizer->gestureInfo_ = AceType::MakeRefPtr<GestureInfo>();

    std::string result = fingersRecognizer->DumpGestureInfo();
    EXPECT_EQ(result, "allowedTypes: [all]");
}

/**
 * @tc.name: DumpGestureInfoTest003
 * @tc.desc: Test DumpGestureInfo with single allowedType
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, DumpGestureInfoTest003, TestSize.Level1)
{
    RefPtr<ClickRecognizer> clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(5, 5);
    RefPtr<MultiFingersRecognizer> fingersRecognizer = clickRecognizer;
    fingersRecognizer->gestureInfo_ = AceType::MakeRefPtr<GestureInfo>();
    std::set<SourceTool> allowedTypes = { SourceTool::FINGER };
    fingersRecognizer->gestureInfo_->SetAllowedTypes(allowedTypes);

    std::string result = fingersRecognizer->DumpGestureInfo();
    EXPECT_EQ(result, "allowedTypes: [1]");
}

/**
 * @tc.name: DumpGestureInfoTest004
 * @tc.desc: Test DumpGestureInfo with multiple allowedTypes
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, DumpGestureInfoTest004, TestSize.Level1)
{
    RefPtr<ClickRecognizer> clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(5, 5);
    RefPtr<MultiFingersRecognizer> fingersRecognizer = clickRecognizer;
    fingersRecognizer->gestureInfo_ = AceType::MakeRefPtr<GestureInfo>();
    std::set<SourceTool> allowedTypes = { SourceTool::FINGER, SourceTool::PEN, SourceTool::MOUSE };
    fingersRecognizer->gestureInfo_->SetAllowedTypes(allowedTypes);

    std::string result = fingersRecognizer->DumpGestureInfo();
    EXPECT_EQ(result, "allowedTypes: [1, 2, 7]");
}

/**
 * @tc.name: CheckCurrentFingersTest001
 * @tc.desc: Test CheckCurrentFingers with negative currentFingers_
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, CheckCurrentFingersTest001, TestSize.Level1)
{
    RefPtr<ClickRecognizer> clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(5, 5);
    RefPtr<MultiFingersRecognizer> fingersRecognizer = clickRecognizer;
    fingersRecognizer->currentFingers_ = -1;
    fingersRecognizer->touchPoints_.clear();

    fingersRecognizer->CheckCurrentFingers();
    EXPECT_NE(fingersRecognizer, nullptr);
}

/**
 * @tc.name: CheckCurrentFingersTest002
 * @tc.desc: Test CheckCurrentFingers with zero currentFingers_
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, CheckCurrentFingersTest002, TestSize.Level1)
{
    RefPtr<ClickRecognizer> clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(5, 5);
    RefPtr<MultiFingersRecognizer> fingersRecognizer = clickRecognizer;
    fingersRecognizer->currentFingers_ = 0;
    fingersRecognizer->touchPoints_.clear();

    fingersRecognizer->CheckCurrentFingers();
    EXPECT_NE(fingersRecognizer, nullptr);
}

/**
 * @tc.name: CheckCurrentFingersTest003
 * @tc.desc: Test CheckCurrentFingers with positive currentFingers_ equal to touchPoints size
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, CheckCurrentFingersTest003, TestSize.Level1)
{
    RefPtr<ClickRecognizer> clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(5, 5);
    RefPtr<MultiFingersRecognizer> fingersRecognizer = clickRecognizer;
    fingersRecognizer->currentFingers_ = 2;
    
    TouchEvent event1;
    event1.id = 1;
    TouchEvent event2;
    event2.id = 2;
    fingersRecognizer->touchPoints_[1] = event1;
    fingersRecognizer->touchPoints_[2] = event2;

    fingersRecognizer->CheckCurrentFingers();
    EXPECT_NE(fingersRecognizer, nullptr);
}

/**
 * @tc.name: CheckCurrentFingersTest004
 * @tc.desc: Test CheckCurrentFingers with positive currentFingers_ greater than touchPoints size
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, CheckCurrentFingersTest004, TestSize.Level1)
{
    RefPtr<ClickRecognizer> clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(5, 5);
    RefPtr<MultiFingersRecognizer> fingersRecognizer = clickRecognizer;
    fingersRecognizer->currentFingers_ = 3;
    
    TouchEvent event1;
    event1.id = 1;
    TouchEvent event2;
    event2.id = 2;
    fingersRecognizer->touchPoints_[1] = event1;
    fingersRecognizer->touchPoints_[2] = event2;

    fingersRecognizer->CheckCurrentFingers();
    EXPECT_NE(fingersRecognizer, nullptr);
}

/**
 * @tc.name: CheckCurrentFingersTest005
 * @tc.desc: Test CheckCurrentFingers with positive currentFingers_ less than touchPoints size
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, CheckCurrentFingersTest005, TestSize.Level1)
{
    RefPtr<ClickRecognizer> clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(5, 5);
    RefPtr<MultiFingersRecognizer> fingersRecognizer = clickRecognizer;
    fingersRecognizer->currentFingers_ = 1;
    
    TouchEvent event1;
    event1.id = 1;
    TouchEvent event2;
    event2.id = 2;
    fingersRecognizer->touchPoints_[1] = event1;
    fingersRecognizer->touchPoints_[2] = event2;

    fingersRecognizer->CheckCurrentFingers();
    EXPECT_NE(fingersRecognizer, nullptr);
}

/**
 * @tc.name: UpdateTouchPointWithAxisEventTest002
 * @tc.desc: Test UpdateTouchPointWithAxisEvent with eventHandleId <= 0
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, UpdateTouchPointWithAxisEventTest002, TestSize.Level1)
{
    RefPtr<ClickRecognizer> clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(5, 5);
    RefPtr<MultiFingersRecognizer> fingersRecognizer = clickRecognizer;

    AxisEvent event;
    event.id = 1;
    event.x = 10.0;
    event.y = 10.0;
    event.screenX = 10.0;
    event.screenY = 10.0;
    event.globalDisplayX = 10.0;
    event.globalDisplayY = 10.0;
    event.sourceType = SourceType::MOUSE;
    event.sourceTool = SourceTool::PEN;
    event.originalId = 1;
    event.eventHandleId = 0;
    event.passThrough = true;
    event.postEventNodeId = 123;

    fingersRecognizer->UpdateTouchPointWithAxisEvent(event);
    EXPECT_EQ(fingersRecognizer->touchPoints_[1].id, 1);
    EXPECT_EQ(fingersRecognizer->touchPoints_[1].x, 10.0);
    EXPECT_EQ(fingersRecognizer->touchPoints_[1].y, 10.0);
    EXPECT_EQ(fingersRecognizer->touchPoints_[1].screenX, 10.0);
    EXPECT_EQ(fingersRecognizer->touchPoints_[1].screenY, 10.0);
    EXPECT_EQ(fingersRecognizer->touchPoints_[1].globalDisplayX, 10.0);
    EXPECT_EQ(fingersRecognizer->touchPoints_[1].globalDisplayY, 10.0);
    EXPECT_EQ(fingersRecognizer->touchPoints_[1].sourceType, SourceType::MOUSE);
    EXPECT_EQ(fingersRecognizer->touchPoints_[1].sourceTool, SourceTool::PEN);
    EXPECT_EQ(fingersRecognizer->touchPoints_[1].originalId, 1);
    EXPECT_FALSE(fingersRecognizer->touchPoints_[1].passThrough);
    EXPECT_EQ(fingersRecognizer->touchPoints_[1].postEventNodeId, 0);

    event.eventHandleId = 1;
    fingersRecognizer->UpdateTouchPointWithAxisEvent(event);
    EXPECT_TRUE(fingersRecognizer->touchPoints_[1].passThrough);
    EXPECT_EQ(fingersRecognizer->touchPoints_[1].postEventNodeId, 123);
}

/**
 * @tc.name: MultiFingersRecognizerConstructorTest001
 * @tc.desc: Test MultiFingersRecognizer default constructor
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, MultiFingersRecognizerConstructorTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create MultiFingersRecognizer with default constructor
     * @tc.expected: recognizer is not null and fingers_ is default value
     */
    RefPtr<MultiFingersRecognizer> recognizer = AceType::MakeRefPtr<MockMultiFingersRecognizer>();
    EXPECT_NE(recognizer, nullptr);
    EXPECT_EQ(recognizer->GetFingers(), 1);
    EXPECT_FALSE(recognizer->GetLimitFingerCount());
}

/**
 * @tc.name: MultiFingersRecognizerConstructorTest002
 * @tc.desc: Test MultiFingersRecognizer constructor with fingers parameter
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, MultiFingersRecognizerConstructorTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create MultiFingersRecognizer with fingers parameter
     * @tc.expected: recognizer is not null and fingers_ is set correctly
     */
    RefPtr<MultiFingersRecognizer> recognizer = AceType::MakeRefPtr<MockMultiFingersRecognizer>(2);
    EXPECT_NE(recognizer, nullptr);
    EXPECT_EQ(recognizer->GetFingers(), 2);
    EXPECT_FALSE(recognizer->GetLimitFingerCount());
}
	 
/**
 * @tc.name: MultiFingersRecognizerConstructorTest003
 * @tc.desc: Test MultiFingersRecognizer constructor with fingers and isLimitFingerCount parameters
 * @tc.type: FUNC
*/
HWTEST_F(MultiFingersRecognizerTestNg, MultiFingersRecognizerConstructorTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create MultiFingersRecognizer with fingers and isLimitFingerCount parameters
     * @tc.expected: recognizer is not null and both parameters are set correctly
     */
    RefPtr<MultiFingersRecognizer> recognizer = AceType::MakeRefPtr<MockMultiFingersRecognizer>(3, true);
    EXPECT_NE(recognizer, nullptr);
    EXPECT_EQ(recognizer->GetFingers(), 3);
    EXPECT_TRUE(recognizer->GetLimitFingerCount());
}

/**
 * @tc.name: MultiFingersRecognizerConstructorTest004
 * @tc.desc: Test MultiFingersRecognizer constructor with zero fingers
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, MultiFingersRecognizerConstructorTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create MultiFingersRecognizer with zero fingers
     * @tc.expected: recognizer is not null and fingers_ is set to 0
     */
    RefPtr<MultiFingersRecognizer> recognizer = AceType::MakeRefPtr<MockMultiFingersRecognizer>(0, false);
    EXPECT_NE(recognizer, nullptr);
    EXPECT_EQ(recognizer->GetFingers(), 1);
    EXPECT_FALSE(recognizer->GetLimitFingerCount());
}

/**
 * @tc.name: MultiFingersRecognizerConstructorTest005
 * @tc.desc: Test MultiFingersRecognizer constructor with large fingers value
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, MultiFingersRecognizerConstructorTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create MultiFingersRecognizer with large fingers value
     * @tc.expected: recognizer is not null and fingers_ is set correctly
     */
    RefPtr<MultiFingersRecognizer> recognizer = AceType::MakeRefPtr<MockMultiFingersRecognizer>(10, true);
    EXPECT_NE(recognizer, nullptr);
    EXPECT_EQ(recognizer->GetFingers(), 10);
    EXPECT_TRUE(recognizer->GetLimitFingerCount());
}

/**
 * @tc.name: GetFingersTest001
 * @tc.desc: Test GetFingers function with default value
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, GetFingersTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create MultiFingersRecognizer and call GetFingers
     * @tc.expected: GetFingers returns default value 1
     */
    RefPtr<MultiFingersRecognizer> recognizer = AceType::MakeRefPtr<MockMultiFingersRecognizer>();
    EXPECT_NE(recognizer, nullptr);
    int32_t fingers = recognizer->GetFingers();
    EXPECT_EQ(fingers, 1);
}

/**
 * @tc.name: GetFingersTest002
 * @tc.desc: Test GetFingers function with custom value
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, GetFingersTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create MultiFingersRecognizer with custom fingers and call GetFingers
     * @tc.expected: GetFingers returns custom value
     */
    RefPtr<MultiFingersRecognizer> recognizer = AceType::MakeRefPtr<MockMultiFingersRecognizer>(5);
    EXPECT_NE(recognizer, nullptr);
    int32_t fingers = recognizer->GetFingers();
    EXPECT_EQ(fingers, 5);
}

/**
 * @tc.name: SetLimitFingerCountTest001
 * @tc.desc: Test SetLimitFingerCount with true value
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, SetLimitFingerCountTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create MultiFingersRecognizer and set isLimitFingerCount to true
     * @tc.expected: GetLimitFingerCount returns true
     */
    RefPtr<MultiFingersRecognizer> recognizer = AceType::MakeRefPtr<MockMultiFingersRecognizer>();
    EXPECT_NE(recognizer, nullptr);
    recognizer->SetLimitFingerCount(true);
    EXPECT_TRUE(recognizer->GetLimitFingerCount());
}

/**
 * @tc.name: SetLimitFingerCountTest002
 * @tc.desc: Test SetLimitFingerCount with false value
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, SetLimitFingerCountTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create MultiFingersRecognizer with isLimitFingerCount true, then set to false
     * @tc.expected: GetLimitFingerCount returns false
     */
    RefPtr<MultiFingersRecognizer> recognizer = AceType::MakeRefPtr<MockMultiFingersRecognizer>(1, true);
    EXPECT_NE(recognizer, nullptr);
    EXPECT_TRUE(recognizer->GetLimitFingerCount());
    recognizer->SetLimitFingerCount(false);
    EXPECT_FALSE(recognizer->GetLimitFingerCount());
}

/**
 * @tc.name: SetLimitFingerCountTest003
 * @tc.desc: Test SetLimitFingerCount toggle behavior
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, SetLimitFingerCountTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create MultiFingersRecognizer and toggle isLimitFingerCount multiple times
     * @tc.expected: GetLimitFingerCount reflects to current state
     */
    RefPtr<MultiFingersRecognizer> recognizer = AceType::MakeRefPtr<MockMultiFingersRecognizer>();
    EXPECT_NE(recognizer, nullptr);
    recognizer->SetLimitFingerCount(true);
    EXPECT_TRUE(recognizer->GetLimitFingerCount());
    recognizer->SetLimitFingerCount(false);
    EXPECT_FALSE(recognizer->GetLimitFingerCount());
    recognizer->SetLimitFingerCount(true);
    EXPECT_TRUE(recognizer->GetLimitFingerCount());
}

/**
 * @tc.name: GetLimitFingerCountTest001
 * @tc.desc: Test GetLimitFingerCount with default value
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, GetLimitFingerCountTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create MultiFingersRecognizer and call GetLimitFingerCount
     * @tc.expected: GetLimitFingerCount returns default false
     */
    RefPtr<MultiFingersRecognizer> recognizer = AceType::MakeRefPtr<MockMultiFingersRecognizer>();
    EXPECT_NE(recognizer, nullptr);
    bool limitFingerCount = recognizer->GetLimitFingerCount();
    EXPECT_FALSE(limitFingerCount);
}

/**
 * @tc.name: GetLimitFingerCountTest002
 * @tc.desc: Test GetLimitFingerCount with true value
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, GetLimitFingerCountTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create MultiFingersRecognizer with isLimitFingerCount true
     * @tc.expected: GetLimitFingerCount returns true
     */
    RefPtr<MultiFingersRecognizer> recognizer = AceType::MakeRefPtr<MockMultiFingersRecognizer>(1, true);
    EXPECT_NE(recognizer, nullptr);
    bool limitFingerCount = recognizer->GetLimitFingerCount();
    EXPECT_TRUE(limitFingerCount);
}

/**
 * @tc.name: CheckLimitFingerTest001
 * @tc.desc: Test CheckLimitFinger when isLimitFingerCount is false
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, CheckLimitFingerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create MultiFingersRecognizer with isLimitFingerCount false
     * @tc.expected: CheckLimitFinger returns false
     */
    RefPtr<MultiFingersRecognizer> recognizer = AceType::MakeRefPtr<MockMultiFingersRecognizer>(2, false);
    EXPECT_NE(recognizer, nullptr);
    bool result = recognizer->CheckLimitFinger();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckLimitFingerTest002
 * @tc.desc: Test CheckLimitFinger when touchPoints size equals fingers
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, CheckLimitFingerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create MultiFingersRecognizer with isLimitFingerCount true and touchPoints size equals fingers
     * @tc.expected: CheckLimitFinger returns false
     */
    RefPtr<MultiFingersRecognizer> recognizer = AceType::MakeRefPtr<MockMultiFingersRecognizer>(2, true);
    EXPECT_NE(recognizer, nullptr);
    TouchEvent event1;
    event1.id = 1;
    TouchEvent event2;
    event2.id = 2;
    recognizer->touchPoints_[1] = event1;
    recognizer->touchPoints_[2] = event2;
    bool result = recognizer->CheckLimitFinger();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckLimitFingerTest003
 * @tc.desc: Test CheckLimitFinger when touchPoints size not equals fingers
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, CheckLimitFingerTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Recognizer with isLimitFingerCount true and touchPoints size not equals fingers
     * @tc.expected: CheckLimitFinger returns true
     */
    RefPtr<MultiFingersRecognizer> recognizer = AceType::MakeRefPtr<MockMultiFingersRecognizer>(3, true);
    EXPECT_NE(recognizer, nullptr);
    TouchEvent event1;
    event1.id = 1;
    TouchEvent event2;
    event2.id = 2;
    recognizer->touchPoints_[1] = event1;
    recognizer->touchPoints_[2] = event2;
    bool result = recognizer->CheckLimitFinger();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CheckLimitFingerTest004
 * @tc.desc: Test CheckLimitFinger with empty touchPoints
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, CheckLimitFingerTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create MultiFingersRecognizer with isLimitFingerCount true and empty touchPoints
     * @tc.expected: CheckLimitFinger returns true
     */
    RefPtr<MultiFingersRecognizer> recognizer = AceType::MakeRefPtr<MockMultiFingersRecognizer>(1, true);
    EXPECT_NE(recognizer, nullptr);
    recognizer->touchPoints_.clear();
    bool result = recognizer->CheckLimitFinger();
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CheckLimitFingerTest005
 * @tc.desc: Test CheckLimitFinger with single finger
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, CheckLimitFingerTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create MultiFingersRecognizer with isLimitFingerCount true and single finger
     * @tc.expected: CheckLimitFinger returns false when touchPoints size equals fingers
     */
    RefPtr<MultiFingersRecognizer> recognizer = AceType::MakeRefPtr<MockMultiFingersRecognizer>(1, true);
    EXPECT_NE(recognizer, nullptr);
    TouchEvent event;
    event.id = 1;
    recognizer->touchPoints_[1] = event;
    bool result = recognizer->CheckLimitFinger();
    EXPECT_FALSE(result);
}

/**
 * @tc.name: ForceCleanRecognizerTest001
 * @tc.desc: Test ForceCleanRecognizer with empty touchPoints
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, ForceCleanRecognizerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create MultiFingersRecognizer and call ForceCleanRecognizer
     * @tc.expected: touchPoints is cleared and state is reset
     */
    RefPtr<MultiFingersRecognizer> recognizer = AceType::MakeRefPtr<MockMultiFingersRecognizer>();
    EXPECT_NE(recognizer, nullptr);
    recognizer->ForceCleanRecognizer();
    EXPECT_TRUE(recognizer->touchPoints_.empty());
    EXPECT_EQ(recognizer->refereeState_, RefereeState::READY);
    EXPECT_EQ(recognizer->lastRefereeState_, RefereeState::READY);
}

/**
 * @tc.name: ForceCleanRecognizerTest002
 * @tc.desc: Test ForceCleanRecognizer with non-empty touchPoints
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, ForceCleanRecognizerTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create MultiFingersRecognizer with touchPoints, then call ForceCleanRecognizer
     * @tc.expected: touchPoints are cleared and state is reset
     */
    RefPtr<MultiFingersRecognizer> recognizer = AceType::MakeRefPtr<MockMultiFingersRecognizer>();
    EXPECT_NE(recognizer, nullptr);
    TouchEvent event1;
    event1.id = 1;
    TouchEvent event2;
    event2.id = 2;
    recognizer->touchPoints_[1] = event1;
    recognizer->touchPoints_[2] = event2;
    recognizer->refereeState_ = RefereeState::SUCCEED;
    recognizer->ForceCleanRecognizer();
    EXPECT_EQ(recognizer->touchPoints_.size(), 2);
    EXPECT_EQ(recognizer->refereeState_, RefereeState::READY);
    EXPECT_EQ(recognizer->lastRefereeState_, RefereeState::READY);
}

/**
 * @tc.name: ForceCleanRecognizerTest003
 * @tc.desc: Test ForceCleanRecognizer with activeFingers
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, ForceCleanRecognizerTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create MultiFingersRecognizer with activeFingers, then call ForceCleanRecognizer
     * @tc.expected: activeFingers is cleared and currentFingers is reset
     */
    RefPtr<MultiFingersRecognizer> recognizer = AceType::MakeRefPtr<MockMultiFingersRecognizer>();
    EXPECT_NE(recognizer, nullptr);
    recognizer->activeFingers_.push_back(1);
    recognizer->activeFingers_.push_back(2);
    recognizer->currentFingers_ = 2;
    recognizer->ForceCleanRecognizer();
    EXPECT_TRUE(recognizer->activeFingers_.empty());
    EXPECT_EQ(recognizer->currentFingers_, 0);
}

/**
 * @tc.name: ForceCleanRecognizerTest004
 * @tc.desc: Test ForceCleanRecognizer with fingersId
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, ForceCleanRecognizerTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create MultiFingersRecognizer with fingersId, then call ForceCleanRecognizer
     * @tc.expected: fingersId is cleared
     */
    RefPtr<MultiFingersRecognizer> recognizer = AceType::MakeRefPtr<MockMultiFingersRecognizer>();
    EXPECT_NE(recognizer, nullptr);
    recognizer->fingersId_.insert(1);
    recognizer->fingersId_.insert(2);
    recognizer->ForceCleanRecognizer();
    EXPECT_TRUE(recognizer->fingersId_.empty());
}

/**
 * @tc.name: ForceCleanRecognizerTest005
 * @tc.desc: Test ForceCleanRecognizer with fingerList
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, ForceCleanRecognizerTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create MultiFingersRecognizer with fingerList, then call ForceCleanRecognizer
     * @tc.expected: fingerList is cleared
     */
    RefPtr<MultiFingersRecognizer> recognizer = AceType::MakeRefPtr<MockMultiFingersRecognizer>();
    EXPECT_NE(recognizer, nullptr);
    FingerInfo fingerInfo1;
    fingerInfo1.fingerId_ = 1;
    FingerInfo fingerInfo2;
    fingerInfo2.fingerId_ = 2;
    recognizer->fingerList_.push_back(fingerInfo1);
    recognizer->fingerList_.push_back(fingerInfo2);
    recognizer->ForceCleanRecognizer();
    EXPECT_TRUE(recognizer->fingerList_.empty());
}

/**
 * @tc.name: ForceCleanRecognizerTest006
 * @tc.desc: Test ForceCleanRecognizer with backupTouchPointsForSucceedBlock
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, ForceCleanRecognizerTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Recognizer with backupTouchPointsForSucceedBlock, then call ForceCleanRecognizer
     * @tc.expected: backupTouchPointsForSucceedBlock is reset
     */
    RefPtr<MultiFingersRecognizer> recognizer = AceType::MakeRefPtr<MockMultiFingersRecognizer>();
    EXPECT_NE(recognizer, nullptr);
    TouchEvent event;
    event.id = 1;
    recognizer->touchPoints_[1] = event;
    recognizer->SetTouchPointsForSucceedBlock();
    EXPECT_TRUE(recognizer->backupTouchPointsForSucceedBlock_.has_value());
    recognizer->ForceCleanRecognizer();
    EXPECT_FALSE(recognizer->backupTouchPointsForSucceedBlock_.has_value());
}

/**
 * @tc.name: ForceCleanRecognizerTest007
 * @tc.desc: Test ForceCleanRecognizer with preventBegin
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, ForceCleanRecognizerTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create MultiFingersRecognizer with preventBegin true, then call ForceCleanRecognizer
     * @tc.expected: preventBegin is reset to false
     */
    RefPtr<MultiFingersRecognizer> recognizer = AceType::MakeRefPtr<MockMultiFingersRecognizer>();
    EXPECT_NE(recognizer, nullptr);
    recognizer->preventBegin_ = true;
    recognizer->ForceCleanRecognizer();
    EXPECT_FALSE(recognizer->preventBegin_);
}

/**
 * @tc.name: ForceCleanRecognizerTest008
 * @tc.desc: Test ForceCleanRecognizer with disposal
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, ForceCleanRecognizerTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create MultiFingersRecognizer with disposal, then call ForceCleanRecognizer
     * @tc.expected: disposal is reset to NONE
     */
    RefPtr<MultiFingersRecognizer> recognizer = AceType::MakeRefPtr<MockMultiFingersRecognizer>();
    EXPECT_NE(recognizer, nullptr);
    recognizer->disposal_ = GestureDisposal::ACCEPT;
    recognizer->ForceCleanRecognizer();
    EXPECT_EQ(recognizer->disposal_, GestureDisposal::NONE);
}

/**
 * @tc.name: GetValidFingersCountTest001
 * @tc.desc: Test GetValidFingersCount with empty touchPoints
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, GetValidFingersCountTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create MultiFingersRecognizer with empty touchPoints
     * @tc.expected: GetValidFingersCount returns 0
     */
    RefPtr<MultiFingersRecognizer> recognizer = AceType::MakeRefPtr<MockMultiFingersRecognizer>();
    EXPECT_NE(recognizer, nullptr);
    recognizer->touchPoints_.clear();
    int32_t count = recognizer->GetValidFingersCount();
    EXPECT_EQ(count, 0);
}

/**
 * @tc.name: GetValidFingersCountTest002
 * @tc.desc: Test GetValidFingersCount with valid touchPoints
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, GetValidFingersCountTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create MultiFingersRecognizer with valid touchPoints
     * @tc.expected: GetValidFingersCount returns count of valid touchPoints
     */
    RefPtr<MultiFingersRecognizer> recognizer = AceType::MakeRefPtr<MockMultiFingersRecognizer>();
    EXPECT_NE(recognizer, nullptr);
    TouchEvent event1;
    event1.id = 1;
    event1.type = TouchType::DOWN;
    TouchEvent event2;
    event2.id = 2;
    event2.type = TouchType::DOWN;
    recognizer->touchPoints_[1] = event1;
    recognizer->touchPoints_[2] = event2;
    int32_t count = recognizer->GetValidFingersCount();
    EXPECT_EQ(count, 2);
}

/**
 * @tc.name: GetValidFingersCountTest003
 * @tc.desc: Test GetValidFingersCount with mixed valid and invalid touchPoints
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, GetValidFingersCountTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create MultiFingersRecognizer with mixed valid and invalid touchPoints
     * @tc.expected: GetValidFingersCount returns only to count of valid touchPoints
     */
    RefPtr<MultiFingersRecognizer> recognizer = AceType::MakeRefPtr<MockMultiFingersRecognizer>();
    EXPECT_NE(recognizer, nullptr);
    TouchEvent event1;
    event1.id = 1;
    event1.type = TouchType::DOWN;
    TouchEvent event2;
    event2.id = 2;
    event2.type = TouchType::UNKNOWN;
    TouchEvent event3;
    event3.id = 3;
    event3.type = TouchType::DOWN;
    recognizer->touchPoints_[1] = event1;
    recognizer->touchPoints_[2] = event2;
    recognizer->touchPoints_[3] = event3;
    int32_t count = recognizer->GetValidFingersCount();
    EXPECT_EQ(count, 2);
}

/**
 * @tc.name: GetValidFingersCountTest004
 * @tc.desc: Test GetValidFingersCount with all invalid touchPoints
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, GetValidFingersCountTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create MultiFingersRecognizer with all invalid touchPoints
     * @tc.expected: GetValidFingersCount returns 0
     */
    RefPtr<MultiFingersRecognizer> recognizer = AceType::MakeRefPtr<MockMultiFingersRecognizer>();
    EXPECT_NE(recognizer, nullptr);
    TouchEvent event1;
    event1.id = 1;
    event1.type = TouchType::UNKNOWN;
    TouchEvent event2;
    event2.id = 2;
    event2.type = TouchType::UNKNOWN;
    recognizer->touchPoints_[1] = event1;
    recognizer->touchPoints_[2] = event2;
    int32_t count = recognizer->GetValidFingersCount();
    EXPECT_EQ(count, 0);
}

/**
 * @tc.name: GetTouchPointsSizeTest001
 * @tc.desc: Test GetTouchPointsSize with empty touchPoints
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, GetTouchPointsSizeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create MultiFingersRecognizer with empty touchPoints
     * @tc.expected: GetTouchPointsSize returns 0
     */
    RefPtr<MultiFingersRecognizer> recognizer = AceType::MakeRefPtr<MockMultiFingersRecognizer>();
    EXPECT_NE(recognizer, nullptr);
    recognizer->touchPoints_.clear();
    int32_t size = recognizer->GetTouchPointsSize();
    EXPECT_EQ(size, 0);
}

/**
 * @tc.name: GetTouchPointsSizeTest002
 * @tc.desc: Test GetTouchPointsSize with non-empty touchPoints
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, GetTouchPointsSizeTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create MultiFingersRecognizer with non-empty touchPoints
     * @tc.expected: GetTouchPointsSize returns to correct size
     */
    RefPtr<MultiFingersRecognizer> recognizer = AceType::MakeRefPtr<MockMultiFingersRecognizer>();
    EXPECT_NE(recognizer, nullptr);
    TouchEvent event1;
    event1.id = 1;
    TouchEvent event2;
    event2.id = 2;
    TouchEvent event3;
    event3.id = 3;
    recognizer->touchPoints_[1] = event1;
    recognizer->touchPoints_[2] = event2;
    recognizer->touchPoints_[3] = event3;
    int32_t size = recognizer->GetTouchPointsSize();
    EXPECT_EQ(size, 3);
}

/**
 * @tc.name: GetTouchPointsSizeTest003
 * @tc.desc: Test GetTouchPointsSize with single touchPoint
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, GetTouchPointsSizeTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create MultiFingersRecognizer with single touchPoint
     * @tc.expected: GetTouchPointsSize returns 1
     */
    RefPtr<MultiFingersRecognizer> recognizer = AceType::MakeRefPtr<MockMultiFingersRecognizer>();
    EXPECT_NE(recognizer, nullptr);
    TouchEvent event;
    event.id = 1;
    recognizer->touchPoints_[1] = event;
    int32_t size = recognizer->GetTouchPointsSize();
    EXPECT_EQ(size, 1);
}

/**
 * @tc.name: GetOriginalTouchPointsSizeTest001
 * @tc.desc: Test GetOriginalTouchPointsSize with empty touchPoints
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, GetOriginalTouchPointsSizeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create MultiFingersRecognizer with empty touchPoints
     * @tc.expected: GetOriginalTouchPointsSize returns 0
     */
    RefPtr<MultiFingersRecognizer> recognizer = AceType::MakeRefPtr<MockMultiFingersRecognizer>();
    EXPECT_NE(recognizer, nullptr);
    recognizer->touchPoints_.clear();
    int32_t size = recognizer->GetOriginalTouchPointsSize();
    EXPECT_EQ(size, 0);
}

/**
 * @tc.name: GetOriginalTouchPointsSizeTest002
 * @tc.desc: Test GetOriginalTouchPointsSize with non-empty touchPoints
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, GetOriginalTouchPointsSizeTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create MultiFingersRecognizer with non-empty touchPoints
     * @tc.expected: GetOriginalTouchPointsSize returns to correct size
     */
    RefPtr<MultiFingersRecognizer> recognizer = AceType::MakeRefPtr<MockMultiFingersRecognizer>();
    EXPECT_NE(recognizer, nullptr);
    TouchEvent event1;
    event1.id = 1;
    event1.originalId = 10;
    TouchEvent event2;
    event2.id = 2;
    event2.originalId = 20;
    recognizer->touchPoints_[1] = event1;
    recognizer->touchPoints_[2] = event2;
    int32_t size = recognizer->GetOriginalTouchPointsSize();
    EXPECT_EQ(size, 2);
}

/**
 * @tc.name: GetOriginalTouchPointsSizeTest003
 * @tc.desc: Test GetOriginalTouchPointsSize with duplicate originalId
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, GetOriginalTouchPointsSizeTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create MultiFingersRecognizer with duplicate originalId
     * @tc.expected: GetOriginalTouchPointsSize returns to count of unique originalId
     */
    RefPtr<MultiFingersRecognizer> recognizer = AceType::MakeRefPtr<MockMultiFingersRecognizer>();
    EXPECT_NE(recognizer, nullptr);
    TouchEvent event1;
    event1.id = 1;
    event1.originalId = 10;
    TouchEvent event2;
    event2.id = 2;
    event2.originalId = 10;
    TouchEvent event3;
    event3.id = 3;
    event3.originalId = 20;
    recognizer->touchPoints_[1] = event1;
    recognizer->touchPoints_[2] = event2;
    recognizer->touchPoints_[3] = event3;
    int32_t size = recognizer->GetOriginalTouchPointsSize();
    EXPECT_EQ(size, 2);
}

/**
 * @tc.name: ResetTouchPointsForSucceedBlockTest001
 * @tc.desc: Test ResetTouchPointsForSucceedBlock with no backup
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, ResetTouchPointsForSucceedBlockTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create MultiFingersRecognizer and call ResetTouchPointsForSucceedBlock
     * @tc.expected: backupTouchPointsForSucceedBlock remains empty
     */
    RefPtr<MultiFingersRecognizer> recognizer = AceType::MakeRefPtr<MockMultiFingersRecognizer>();
    EXPECT_NE(recognizer, nullptr);
    EXPECT_FALSE(recognizer->backupTouchPointsForSucceedBlock_.has_value());
    recognizer->ResetTouchPointsForSucceedBlock();
    EXPECT_FALSE(recognizer->backupTouchPointsForSucceedBlock_.has_value());
}

/**
 * @tc.name: ResetTouchPointsForSucceedBlockTest002
 * @tc.desc: Test ResetTouchPointsForSucceedBlock with backup
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, ResetTouchPointsForSucceedBlockTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create MultiFingersRecognizer with backup, then call ResetTouchPointsForSucceedBlock
     * @tc.expected: backupTouchPointsForSucceedBlock is reset
     */
    RefPtr<MultiFingersRecognizer> recognizer = AceType::MakeRefPtr<MockMultiFingersRecognizer>();
    EXPECT_NE(recognizer, nullptr);
    TouchEvent event;
    event.id = 1;
    recognizer->touchPoints_[1] = event;
    recognizer->SetTouchPointsForSucceedBlock();
    EXPECT_TRUE(recognizer->backupTouchPointsForSucceedBlock_.has_value());
    recognizer->ResetTouchPointsForSucceedBlock();
    EXPECT_FALSE(recognizer->backupTouchPointsForSucceedBlock_.has_value());
}

/**
 * @tc.name: ResetTouchPointsForSucceedBlockTest003
 * @tc.desc: Test ResetTouchPointsForSucceedBlock multiple calls
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, ResetTouchPointsForSucceedBlockTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create MultiFingersRecognizer and call ResetTouchPointsForSucceedBlock multiple times
     * @tc.expected: backupTouchPointsForSucceedBlock remains empty
     */
    RefPtr<MultiFingersRecognizer> recognizer = AceType::MakeRefPtr<MockMultiFingersRecognizer>();
    EXPECT_NE(recognizer, nullptr);
    recognizer->ResetTouchPointsForSucceedBlock();
    EXPECT_FALSE(recognizer->backupTouchPointsForSucceedBlock_.has_value());
    recognizer->ResetTouchPointsForSucceedBlock();
    EXPECT_FALSE(recognizer->backupTouchPointsForSucceedBlock_.has_value());
    recognizer->ResetTouchPointsForSucceedBlock();
    EXPECT_FALSE(recognizer->backupTouchPointsForSucceedBlock_.has_value());
}

/**
 * @tc.name: CheckTouchIdTest001
 * @tc.desc: Test CheckTouchId with existing touchId
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, CheckTouchIdTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create MultiFingersRecognizer with touchPoints
     * @tc.expected: CheckTouchId returns true for existing touchId
     */
    RefPtr<MultiFingersRecognizer> recognizer = AceType::MakeRefPtr<MockMultiFingersRecognizer>();
    EXPECT_NE(recognizer, nullptr);
    TouchEvent event;
    event.id = 1;
    recognizer->touchPoints_[1] = event;
    bool result = recognizer->CheckTouchId(1);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CheckTouchIdTest002
 * @tc.desc: Test CheckTouchId with non-existing touchId
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, CheckTouchIdTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create MultiFingersRecognizer with touchPoints
     * @tc.expected: CheckTouchId returns false for non-existing touchId
     */
    RefPtr<MultiFingersRecognizer> recognizer = AceType::MakeRefPtr<MockMultiFingersRecognizer>();
    EXPECT_NE(recognizer, nullptr);
    TouchEvent event;
    event.id = 1;
    recognizer->touchPoints_[1] = event;
    bool result = recognizer->CheckTouchId(2);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckTouchIdTest003
 * @tc.desc: Test CheckTouchId with empty touchPoints
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, CheckTouchIdTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create MultiFingersRecognizer with empty touchPoints
     * @tc.expected: CheckTouchId returns false for any touchId
     */
    RefPtr<MultiFingersRecognizer> recognizer = AceType::MakeRefPtr<MockMultiFingersRecognizer>();
    EXPECT_NE(recognizer, nullptr);
    recognizer->touchPoints_.clear();
    bool result1 = recognizer->CheckTouchId(1);
    bool result2 = recognizer->CheckTouchId(2);
    EXPECT_FALSE(result1);
    EXPECT_FALSE(result2);
}

/**
 * @tc.name: CheckTouchIdTest004
 * @tc.desc: Test CheckTouchId with multiple touchPoints
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, CheckTouchIdTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create MultiFingersRecognizer with multiple touchPoints
     * @tc.expected: CheckTouchId returns correct result for each touchId
     */
    RefPtr<MultiFingersRecognizer> recognizer = AceType::MakeRefPtr<MockMultiFingersRecognizer>();
    EXPECT_NE(recognizer, nullptr);
    TouchEvent event1;
    event1.id = 1;
    TouchEvent event2;
    event2.id = 2;
    TouchEvent event3;
    event3.id = 3;
    recognizer->touchPoints_[1] = event1;
    recognizer->touchPoints_[2] = event2;
    recognizer->touchPoints_[3] = event3;
    bool result1 = recognizer->CheckTouchId(1);
    bool result2 = recognizer->CheckTouchId(2);
    bool result3 = recognizer->CheckTouchId(3);
    bool result4 = recognizer->CheckTouchId(4);
    EXPECT_TRUE(result1);
    EXPECT_TRUE(result2);
    EXPECT_TRUE(result3);
    EXPECT_FALSE(result4);
}

/**
 * @tc.name: GetTouchPointsTest001
 * @tc.desc: Test GetTouchPoints with empty touchPoints
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, GetTouchPointsTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create MultiFingersRecognizer with empty touchPoints
     * @tc.expected: GetTouchPoints returns empty map
     */
    RefPtr<MultiFingersRecognizer> recognizer = AceType::MakeRefPtr<MockMultiFingersRecognizer>();
    EXPECT_NE(recognizer, nullptr);
    recognizer->touchPoints_.clear();
    std::map<int32_t, TouchEvent> result = recognizer->GetTouchPoints();
    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: GetTouchPointsTest002
 * @tc.desc: Test GetTouchPoints with non-empty touchPoints
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, GetTouchPointsTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create MultiFingersRecognizer with non-empty touchPoints
     * @tc.expected: GetTouchPoints returns to correct touchPoints
     */
    RefPtr<MultiFingersRecognizer> recognizer = AceType::MakeRefPtr<MockMultiFingersRecognizer>();
    EXPECT_NE(recognizer, nullptr);
    TouchEvent event1;
    event1.id = 1;
    TouchEvent event2;
    event2.id = 2;
    recognizer->touchPoints_[1] = event1;
    recognizer->touchPoints_[2] = event2;
    std::map<int32_t, TouchEvent> result = recognizer->GetTouchPoints();
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result[1].id, 1);
    EXPECT_EQ(result[2].id, 2);
}

/**
 * @tc.name: GetTouchPointsTest003
 * @tc.desc: Test GetTouchPoints returns copy, not reference
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, GetTouchPointsTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create MultiFingersRecognizer and get touchPoints, then modify original
     * @tc.expected: returned copy is not affected by original modification
     */
    RefPtr<MultiFingersRecognizer> recognizer = AceType::MakeRefPtr<MockMultiFingersRecognizer>();
    EXPECT_NE(recognizer, nullptr);
    TouchEvent event;
    event.id = 1;
    recognizer->touchPoints_[1] = event;
    std::map<int32_t, TouchEvent> result = recognizer->GetTouchPoints();
    EXPECT_EQ(result.size(), 1);
    recognizer->touchPoints_[2] = event;
    EXPECT_EQ(result.size(), 1);
}

/**
 * @tc.name: MultiFingersRecognizerComprehensiveTest001
 * @tc.desc: Test comprehensive scenario with multiple operations
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, MultiFingersRecognizerComprehensiveTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create MultiFingersRecognizer and perform multiple operations
     * @tc.expected: all operations work correctly
     */
    RefPtr<MultiFingersRecognizer> recognizer = AceType::MakeRefPtr<MockMultiFingersRecognizer>(2, true);
    EXPECT_NE(recognizer, nullptr);
    EXPECT_EQ(recognizer->GetFingers(), 2);
    EXPECT_TRUE(recognizer->GetLimitFingerCount());
    
    TouchEvent event1;
    event1.id = 1;
    event1.type = TouchType::DOWN;
    TouchEvent event2;
    event2.id = 2;
    event2.type = TouchType::DOWN;
    recognizer->touchPoints_[1] = event1;
    recognizer->touchPoints_[2] = event2;
    
    EXPECT_EQ(recognizer->GetTouchPointsSize(), 2);
    EXPECT_EQ(recognizer->GetValidFingersCount(), 2);
    EXPECT_FALSE(recognizer->CheckLimitFinger());
    
    recognizer->SetTouchPointsForSucceedBlock();
    EXPECT_TRUE(recognizer->backupTouchPointsForSucceedBlock_.has_value());
    
    recognizer->ResetTouchPointsForSucceedBlock();
    EXPECT_FALSE(recognizer->backupTouchPointsForSucceedBlock_.has_value());
}

/**
 * @tc.name: MultiFingersRecognizerComprehensiveTest002
 * @tc.desc: Test comprehensive scenario with state transitions
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, MultiFingersRecognizerComprehensiveTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create MultiFingersRecognizer and test state transitions
     * @tc.expected: state transitions work correctly
     */
    RefPtr<MultiFingersRecognizer> recognizer = AceType::MakeRefPtr<MockMultiFingersRecognizer>(1, false);
    EXPECT_NE(recognizer, nullptr);
    
    recognizer->refereeState_ = RefereeState::PENDING;
    recognizer->currentFingers_ = 1;
    TouchEvent event;
    event.id = 1;
    event.type = TouchType::DOWN;
    recognizer->touchPoints_[1] = event;
    
    EXPECT_EQ(recognizer->GetValidFingersCount(), 1);
    EXPECT_TRUE(recognizer->CheckTouchId(1));
    
    recognizer->ForceCleanRecognizer();
    EXPECT_EQ(recognizer->refereeState_, RefereeState::READY);
    EXPECT_EQ(recognizer->currentFingers_, 0);
    EXPECT_TRUE(recognizer->CheckTouchId(1));
}

/**
 * @tc.name: MultiFingersRecognizerComprehensiveTest003
 * @tc.desc: Test comprehensive scenario with finger limit
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, MultiFingersRecognizerComprehensiveTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create MultiFingersRecognizer with finger limit and test various scenarios
     * @tc.expected: finger limit works correctly
     */
    RefPtr<MultiFingersRecognizer> recognizer = AceType::MakeRefPtr<MockMultiFingersRecognizer>(3, true);
    EXPECT_NE(recognizer, nullptr);
    
    TouchEvent event1;
    event1.id = 1;
    event1.type = TouchType::DOWN;
    TouchEvent event2;
    event2.id = 2;
    event2.type = TouchType::DOWN;
    recognizer->touchPoints_[1] = event1;
    recognizer->touchPoints_[2] = event2;
    
    EXPECT_TRUE(recognizer->CheckLimitFinger());
    
    TouchEvent event3;
    event3.id = 3;
    event3.type = TouchType::DOWN;
    recognizer->touchPoints_[3] = event3;
    
    EXPECT_FALSE(recognizer->CheckLimitFinger());
    EXPECT_EQ(recognizer->GetValidFingersCount(), 3);
    EXPECT_EQ(recognizer->GetTouchPointsSize(), 3);
}

/**
 * @tc.name: MultiFingersRecognizerComprehensiveTest004
 * @tc.desc: Test comprehensive scenario with backup and restore
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, MultiFingersRecognizerComprehensiveTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create MultiFingersRecognizer and test backup/restore operations
     * @tc.expected: backup/restore operations work correctly
     */
    RefPtr<MultiFingersRecognizer> recognizer = AceType::MakeRefPtr<MockMultiFingersRecognizer>();
    EXPECT_NE(recognizer, nullptr);
    
    TouchEvent event1;
    event1.id = 1;
    event1.type = TouchType::DOWN;
    TouchEvent event2;
    event2.id = 2;
    event2.type = TouchType::DOWN;
    recognizer->touchPoints_[1] = event1;
    recognizer->touchPoints_[2] = event2;
    
    EXPECT_EQ(recognizer->GetTouchPointsSize(), 2);
    
    recognizer->SetTouchPointsForSucceedBlock();
    EXPECT_TRUE(recognizer->backupTouchPointsForSucceedBlock_.has_value());
    
    recognizer->touchPoints_.clear();
    EXPECT_EQ(recognizer->GetTouchPointsSize(), 0);
    
    recognizer->ResetTouchPointsForSucceedBlock();
    EXPECT_FALSE(recognizer->backupTouchPointsForSucceedBlock_.has_value());
}

/**
 * @tc.name: MultiFingersRecognizerComprehensiveTest005
 * @tc.desc: Test comprehensive scenario with edge cases
 * @tc.type: FUNC
 */
HWTEST_F(MultiFingersRecognizerTestNg, MultiFingersRecognizerComprehensiveTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create MultiFingersRecognizer and test edge cases
     * @tc.expected: edge cases are handled correctly
     */
    RefPtr<MultiFingersRecognizer> recognizer = AceType::MakeRefPtr<MockMultiFingersRecognizer>(0, false);
    EXPECT_NE(recognizer, nullptr);
    EXPECT_EQ(recognizer->GetFingers(), 1);
    
    EXPECT_EQ(recognizer->GetValidFingersCount(), 0);
    EXPECT_EQ(recognizer->GetTouchPointsSize(), 0);
    EXPECT_EQ(recognizer->GetOriginalTouchPointsSize(), 0);
    
    recognizer->SetLimitFingerCount(true);
    EXPECT_TRUE(recognizer->GetLimitFingerCount());
    EXPECT_TRUE(recognizer->CheckLimitFinger());
    
    recognizer->ForceCleanRecognizer();
    EXPECT_EQ(recognizer->refereeState_, RefereeState::READY);
}
}; // namespace OHOS::Ace::NG