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
    void OnBeginGestureReferee(int32_t touchId, bool needUpdateChild = false) {}
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
    void OnBeginGestureReferee(int32_t touchId, bool needUpdateChild = false) {}
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
}; // namespace OHOS::Ace::NG