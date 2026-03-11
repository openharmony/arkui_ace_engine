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
}; // namespace OHOS::Ace::NG