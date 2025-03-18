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

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class GestureGroupTestNg : public GesturesCommonTestNg {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void GestureGroupTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void GestureGroupTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: RecognizerGroupTest001
 * @tc.desc: Test RecognizerGroup function: OnBeginGestureReferee
 * @tc.type: FUNC
 */
HWTEST_F(GestureGroupTestNg, RecognizerGroupTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create RecognizerGroup
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<ExclusiveRecognizer> exclusiveRecognizer = AceType::MakeRefPtr<ExclusiveRecognizer>(recognizers);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call OnBeginGestureReferee function and compare result.
     * @tc.steps: case1: needUpdateChild is false
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer->recognizers_.clear();
    exclusiveRecognizer->OnBeginGestureReferee(0, false);
    EXPECT_EQ(exclusiveRecognizer->recognizers_.size(), 0);

    /**
     * @tc.steps: step2. call OnBeginGestureReferee function and compare result.
     * @tc.steps: case2: needUpdateChild is true, recognizers is empty
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer->recognizers_.clear();
    exclusiveRecognizer->OnBeginGestureReferee(0, true);
    EXPECT_EQ(exclusiveRecognizer->recognizers_.size(), 0);

    /**
     * @tc.steps: step2. call OnBeginGestureReferee function and compare result.
     * @tc.steps: case3: needUpdateChild is true, recognizers has nullptr
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer->recognizers_.clear();
    exclusiveRecognizer->recognizers_.push_back(nullptr);
    exclusiveRecognizer->OnBeginGestureReferee(0, true);
    EXPECT_EQ(exclusiveRecognizer->recognizers_.size(), 1);

    /**
     * @tc.steps: step2. call OnBeginGestureReferee function and compare result.
     * @tc.steps: case4: needUpdateChild is true, recognizers has ptr
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer->recognizers_.clear();
    exclusiveRecognizer->recognizers_.push_back(clickRecognizerPtr);
    exclusiveRecognizer->OnBeginGestureReferee(0, true);
    EXPECT_EQ(exclusiveRecognizer->recognizers_.size(), 1);
}

/**
 * @tc.name: RecognizerGroupCheckStatesTest001
 * @tc.desc: Test RecognizerGroup function: CheckStates
 * @tc.type: FUNC
 */
HWTEST_F(GestureGroupTestNg, RecognizerGroupCheckStatesTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create RecognizerGroup
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<ExclusiveRecognizer> exclusiveRecognizer = AceType::MakeRefPtr<ExclusiveRecognizer>(recognizers);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call CheckStates function and compare result.
     * @tc.steps: case1: recognizers_ is empty
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer->recognizers_.clear();
    exclusiveRecognizer->CheckStates(0);
    EXPECT_EQ(exclusiveRecognizer->recognizers_.size(), 0);

    /**
     * @tc.steps: step2. call CheckStates function and compare result.
     * @tc.steps: case2: recognizers has nullptr
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer->recognizers_.clear();
    exclusiveRecognizer->CheckStates(0);
    EXPECT_EQ(exclusiveRecognizer->recognizers_.size(), 0);

    /**
     * @tc.steps: step2. call CheckStates function and compare result.
     * @tc.steps: case3: recognizers has ptr
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer->recognizers_.clear();
    exclusiveRecognizer->recognizers_.push_back(clickRecognizerPtr);
    exclusiveRecognizer->CheckStates(0);
    EXPECT_EQ(exclusiveRecognizer->recognizers_.size(), 1);
}

/**
 * @tc.name: RecognizerGroupCheckStatesTest002
 * @tc.desc: Test RecognizerGroup function: CheckStates
 * @tc.type: FUNC
 */
HWTEST_F(GestureGroupTestNg, RecognizerGroupCheckStatesTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create RecognizerGroup
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<ExclusiveRecognizer> exclusiveRecognizer = AceType::MakeRefPtr<ExclusiveRecognizer>(recognizers);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    TouchEvent touchEventStart;
    touchEventStart.id = 0;
    clickRecognizerPtr->touchPoints_[0] = touchEventStart;
    TouchEvent touchEventEnd;
    touchEventEnd.id = 1;
    clickRecognizerPtr->touchPoints_[1] = touchEventEnd;

    std::vector<RefPtr<NGGestureRecognizer>> recognizers2 = {};
    RefPtr<ExclusiveRecognizer> exclusiveRecognizerPtr = AceType::MakeRefPtr<ExclusiveRecognizer>(recognizers2);
    exclusiveRecognizerPtr->touchPoints_[0] = touchEventStart;
    exclusiveRecognizerPtr->touchPoints_[1] = touchEventEnd;

    /**
     * @tc.steps: step2. call CheckStates function and compare result.
     * @tc.steps: case1: recognizers_ is empty
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer->recognizers_.clear();
    exclusiveRecognizer->CheckStates(0);
    EXPECT_EQ(exclusiveRecognizer->recognizers_.size(), 0);

    /**
     * @tc.steps: step2. call CheckStates function and compare result.
     * @tc.steps: case2: recognizers has nullptr
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer->recognizers_.clear();
    exclusiveRecognizer->CheckStates(0);
    EXPECT_EQ(exclusiveRecognizer->recognizers_.size(), 0);

    /**
     * @tc.steps: step2. call CheckStates function and compare result.
     * @tc.steps: case3: recognizers has ptr
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer->recognizers_.clear();
    exclusiveRecognizer->recognizers_.push_back(clickRecognizerPtr);
    exclusiveRecognizer->CheckStates(0);
    EXPECT_EQ(exclusiveRecognizer->recognizers_.size(), 1);

    /**
     * @tc.steps: step2. call CheckStates function and compare result.
     * @tc.steps: case3: recognizers has ptr
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer->recognizers_.clear();
    exclusiveRecognizer->recognizers_.push_back(exclusiveRecognizerPtr);
    exclusiveRecognizer->CheckStates(0);
    EXPECT_EQ(exclusiveRecognizer->recognizers_.size(), 1);
}

/**
 * @tc.name: RecognizerGroupCheckStatesTest003
 * @tc.desc: Test RecognizerGroup function: CheckStates
 * @tc.type: FUNC
 */
HWTEST_F(GestureGroupTestNg, RecognizerGroupCheckStatesTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create RecognizerGroup
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<ExclusiveRecognizer> exclusiveRecognizer = AceType::MakeRefPtr<ExclusiveRecognizer>(recognizers);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    TouchEvent touchEventStart;
    touchEventStart.id = 0;
    clickRecognizerPtr->touchPoints_[0] = touchEventStart;
    TouchEvent touchEventEnd;
    touchEventEnd.id = 1;
    clickRecognizerPtr->touchPoints_[1] = touchEventEnd;

    /**
     * @tc.steps: step2. call CheckStates function and compare result.
     * @tc.steps: case1: recognizers_ is empty
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer->recognizers_.clear();
    exclusiveRecognizer->CheckStates(0);
    EXPECT_EQ(exclusiveRecognizer->recognizers_.size(), 0);

    /**
     * @tc.steps: step2. call CheckStates function and compare result.
     * @tc.steps: case2: recognizers has nullptr
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer->recognizers_.clear();
    exclusiveRecognizer->CheckStates(0);
    EXPECT_EQ(exclusiveRecognizer->recognizers_.size(), 0);

    /**
     * @tc.steps: step2. call CheckStates function and compare result.
     * @tc.steps: case3: recognizers has ptr
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer->recognizers_.clear();
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED_BLOCKED;
    exclusiveRecognizer->recognizers_.push_back(clickRecognizerPtr);
    exclusiveRecognizer->CheckStates(0);
    EXPECT_EQ(exclusiveRecognizer->recognizers_.size(), 1);

    /**
     * @tc.steps: step2. call CheckStates function and compare result.
     * @tc.steps: case3: recognizers has ptr
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer->recognizers_.clear();
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    exclusiveRecognizer->recognizers_.push_back(clickRecognizerPtr);
    exclusiveRecognizer->CheckStates(0);
    EXPECT_EQ(exclusiveRecognizer->recognizers_.size(), 1);

    /**
     * @tc.steps: step2. call CheckStates function and compare result.
     * @tc.steps: case3: recognizers has ptr
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer->recognizers_.clear();
    clickRecognizerPtr->refereeState_ = RefereeState::FAIL;
    exclusiveRecognizer->recognizers_.push_back(clickRecognizerPtr);
    exclusiveRecognizer->CheckStates(0);
    EXPECT_EQ(exclusiveRecognizer->recognizers_.size(), 1);

    /**
     * @tc.steps: step2. call CheckStates function and compare result.
     * @tc.steps: case3: recognizers has ptr
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer->recognizers_.clear();
    clickRecognizerPtr->refereeState_ = RefereeState::READY;
    exclusiveRecognizer->recognizers_.push_back(clickRecognizerPtr);
    exclusiveRecognizer->CheckStates(0);
    EXPECT_EQ(exclusiveRecognizer->recognizers_.size(), 1);

    /**
     * @tc.steps: step2. call CheckStates function and compare result.
     * @tc.steps: case3: recognizers has ptr
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer->recognizers_.clear();
    clickRecognizerPtr->refereeState_ = RefereeState::DETECTING;
    exclusiveRecognizer->recognizers_.push_back(clickRecognizerPtr);
    exclusiveRecognizer->CheckStates(0);
    EXPECT_EQ(exclusiveRecognizer->recognizers_.size(), 1);
}

/**
 * @tc.name: RecognizerGroupCheckStatesTest005
 * @tc.desc: Test RecognizerGroup function: CheckStates
 * @tc.type: FUNC
 */
HWTEST_F(GestureGroupTestNg, RecognizerGroupCheckStatesTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create RecognizerGroup
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<ExclusiveRecognizer> exclusiveRecognizer = AceType::MakeRefPtr<ExclusiveRecognizer>(recognizers);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    TouchEvent touchEventStart;
    touchEventStart.id = 0;
    clickRecognizerPtr->touchPoints_[0] = touchEventStart;
    TouchEvent touchEventEnd;
    touchEventEnd.id = 1;
    clickRecognizerPtr->touchPoints_[1] = touchEventEnd;

    std::vector<RefPtr<NGGestureRecognizer>> recognizers2 = {};
    RefPtr<ExclusiveRecognizer> exclusiveRecognizerPtr = AceType::MakeRefPtr<ExclusiveRecognizer>(recognizers2);
    exclusiveRecognizerPtr->touchPoints_[0] = touchEventStart;
    exclusiveRecognizerPtr->touchPoints_[1] = touchEventEnd;

    RefPtr<ClickRecognizer> clickRecognizerPtr2 = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    touchEventStart.id = 0;
    clickRecognizerPtr2->touchPoints_[0] = touchEventStart;
    touchEventEnd.id = 1;
    clickRecognizerPtr2->touchPoints_[1] = touchEventEnd;
    clickRecognizerPtr2->refereeState_ = RefereeState::DETECTING;
    exclusiveRecognizerPtr->recognizers_.push_back(clickRecognizerPtr2);

    /**
     * @tc.steps: step2. call CheckStates function and compare result.
     * @tc.steps: case1: recognizers_ is empty
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer->recognizers_.clear();
    exclusiveRecognizer->CheckStates(0);
    EXPECT_EQ(exclusiveRecognizer->recognizers_.size(), 0);

    /**
     * @tc.steps: step2. call CheckStates function and compare result.
     * @tc.steps: case2: recognizers has nullptr
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer->recognizers_.clear();
    exclusiveRecognizer->CheckStates(0);
    EXPECT_EQ(exclusiveRecognizer->recognizers_.size(), 0);

    /**
     * @tc.steps: step2. call CheckStates function and compare result.
     * @tc.steps: case3: recognizers has ptr
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer->recognizers_.clear();
    exclusiveRecognizer->recognizers_.push_back(clickRecognizerPtr);
    exclusiveRecognizer->CheckStates(0);
    EXPECT_EQ(exclusiveRecognizer->recognizers_.size(), 1);

    /**
     * @tc.steps: step2. call CheckStates function and compare result.
     * @tc.steps: case3: recognizers has ptr
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer->recognizers_.clear();
    exclusiveRecognizer->recognizers_.push_back(exclusiveRecognizerPtr);
    exclusiveRecognizer->CheckStates(0);
    EXPECT_EQ(exclusiveRecognizer->recognizers_.size(), 1);
}

/**
 * @tc.name: RecognizerGroupOnResetStatusTest001
 * @tc.desc: Test RecognizerGroup function: OnResetStatus
 * @tc.type: FUNC
 */
HWTEST_F(GestureGroupTestNg, RecognizerGroupOnResetStatusTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create RecognizerGroup
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<ExclusiveRecognizer> exclusiveRecognizer = AceType::MakeRefPtr<ExclusiveRecognizer>(recognizers);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call OnResetStatus function and compare result.
     * @tc.steps: case1: recognizers_ is empty
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer->recognizers_.clear();
    exclusiveRecognizer->remainChildOnResetStatus_ = true;
    exclusiveRecognizer->OnResetStatus();
    EXPECT_EQ(exclusiveRecognizer->recognizers_.size(), 0);

    /**
     * @tc.steps: step2. call OnResetStatus function and compare result.
     * @tc.steps: case2: recognizers has nullptr
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer->recognizers_.clear();
    exclusiveRecognizer->recognizers_.push_back(nullptr);
    exclusiveRecognizer->remainChildOnResetStatus_ = false;
    exclusiveRecognizer->OnResetStatus();
    EXPECT_EQ(exclusiveRecognizer->recognizers_.size(), 0);

    /**
     * @tc.steps: step2. call OnResetStatus function and compare result.
     * @tc.steps: case3: recognizers has ptr
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer->recognizers_.clear();
    exclusiveRecognizer->recognizers_.push_back(clickRecognizerPtr);
    exclusiveRecognizer->remainChildOnResetStatus_ = false;
    exclusiveRecognizer->OnResetStatus();
    EXPECT_EQ(exclusiveRecognizer->recognizers_.size(), 0);
}

/**
 * @tc.name: RecognizerGroupTest003
 * @tc.desc: Test RecognizerGroup function: AddChildren
 * @tc.type: FUNC
 */
HWTEST_F(GestureGroupTestNg, RecognizerGroupTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create RecognizerGroup
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<ExclusiveRecognizer> exclusiveRecognizer = AceType::MakeRefPtr<ExclusiveRecognizer>(recognizers);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    std::list<RefPtr<NGGestureRecognizer>> recognizersInput = {};

    /**
     * @tc.steps: step2. call OnFinishGestureReferee function and compare result.
     * @tc.steps: case1: recognizers is empty
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer->AddChildren(recognizersInput);
    EXPECT_EQ(exclusiveRecognizer->recognizers_.size(), 0);

    /**
     * @tc.steps: step2. call OnFinishGestureReferee function and compare result.
     * @tc.steps: case2: recognizers is not empty
     * @tc.expected: step2. result equals.
     */
    recognizersInput = { nullptr, clickRecognizerPtr, clickRecognizerPtr };
    exclusiveRecognizer->AddChildren(recognizersInput);
    EXPECT_EQ(exclusiveRecognizer->recognizers_.size(), 1);
}

/**
 * @tc.name: RecognizerGroupTest004
 * @tc.desc: Test RecognizerGroup function: Existed
 * @tc.type: FUNC
 */
HWTEST_F(GestureGroupTestNg, RecognizerGroupTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create RecognizerGroup
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<ExclusiveRecognizer> exclusiveRecognizer = AceType::MakeRefPtr<ExclusiveRecognizer>(recognizers);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call Existed function and compare result.
     * @tc.steps: case1: recognizers is empty
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer->Existed(clickRecognizerPtr);
    EXPECT_EQ(exclusiveRecognizer->recognizers_.size(), 0);

    /**
     * @tc.steps: step2. call Existed function and compare result.
     * @tc.steps: case2: recognizers is empty
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer->recognizers_.push_back(clickRecognizerPtr);
    exclusiveRecognizer->Existed(clickRecognizerPtr);
    EXPECT_EQ(exclusiveRecognizer->recognizers_.size(), 1);
}

/**
 * @tc.name: RecognizerGroupTest005
 * @tc.desc: Test RecognizerGroup function: OnFlushTouchEventsBegin End Reset
 * @tc.type: FUNC
 */
HWTEST_F(GestureGroupTestNg, RecognizerGroupTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create RecognizerGroup
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<ExclusiveRecognizer> exclusiveRecognizer = AceType::MakeRefPtr<ExclusiveRecognizer>(recognizers);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call function and compare result.
     * @tc.steps: case1: recognizers is empty
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer->OnFlushTouchEventsBegin();
    exclusiveRecognizer->OnFlushTouchEventsEnd();
    EXPECT_EQ(exclusiveRecognizer->recognizers_.size(), 0);

    /**
     * @tc.steps: step2. call function and compare result.
     * @tc.steps: case2: recognizers has nullptr
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer->recognizers_.push_back(nullptr);
    exclusiveRecognizer->OnFlushTouchEventsBegin();
    exclusiveRecognizer->OnFlushTouchEventsEnd();
    EXPECT_EQ(exclusiveRecognizer->recognizers_.size(), 1);

    /**
     * @tc.steps: step2. call function and compare result.
     * @tc.steps: case3: recognizers has ptr
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer->recognizers_.clear();
    exclusiveRecognizer->recognizers_.push_back(clickRecognizerPtr);
    exclusiveRecognizer->OnFlushTouchEventsBegin();
    exclusiveRecognizer->OnFlushTouchEventsEnd();
    EXPECT_EQ(exclusiveRecognizer->recognizers_.size(), 1);

    /**
     * @tc.steps: step2. call function and compare result.
     * @tc.steps: case4: recognizers has ptr
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer->remainChildOnResetStatus_ = true;
    EXPECT_EQ(exclusiveRecognizer->recognizers_.size(), 1);
}

/**
 * @tc.name: RecognizerGroupTest006
 * @tc.desc: Test RecognizerGroup function: GetGroupRecognizer
 * @tc.type: FUNC
 */
HWTEST_F(GestureGroupTestNg, RecognizerGroupTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create RecognizerGroup
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<ExclusiveRecognizer> exclusiveRecognizer = AceType::MakeRefPtr<ExclusiveRecognizer>(recognizers);

    /**
     * @tc.steps: step2. call function and compare result.
     * @tc.steps: case1: recognizers is empty
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer->OnFlushTouchEventsBegin();
    exclusiveRecognizer->OnFlushTouchEventsEnd();
    exclusiveRecognizer->GetGroupRecognizer();
    EXPECT_EQ(exclusiveRecognizer->recognizers_.size(), 0);
}

/**
 * @tc.name: RecognizerGroupTest007
 * @tc.desc: Test RecognizerGroup function: ForceReject
 * @tc.type: FUNC
 */
HWTEST_F(GestureGroupTestNg, RecognizerGroupTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create RecognizerGroup
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<ExclusiveRecognizer> exclusiveRecognizer = AceType::MakeRefPtr<ExclusiveRecognizer>(recognizers);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    /**
     * @tc.steps: step2. call function and compare result.
     * @tc.steps: case1: recognizers is empty
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer->recognizers_.clear();
    exclusiveRecognizer->OnFlushTouchEventsBegin();
    exclusiveRecognizer->OnFlushTouchEventsEnd();
    exclusiveRecognizer->ForceReject();
    EXPECT_EQ(exclusiveRecognizer->recognizers_.size(), 0);

    /**
     * @tc.steps: step2. call function and compare result.
     * @tc.steps: case1: recognizers is empty
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer->recognizers_.clear();
    exclusiveRecognizer->recognizers_.push_back(clickRecognizerPtr);
    exclusiveRecognizer->OnFlushTouchEventsBegin();
    exclusiveRecognizer->OnFlushTouchEventsEnd();
    exclusiveRecognizer->ForceReject();
    EXPECT_EQ(exclusiveRecognizer->recognizers_.size(), 1);
}

/**
 * @tc.name: RecognizerGroupForceRejectTest001
 * @tc.desc: Test RecognizerGroup function: ForceReject
 * @tc.type: FUNC
 */
HWTEST_F(GestureGroupTestNg, RecognizerGroupForceRejectTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create RecognizerGroup
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<ExclusiveRecognizer> exclusiveRecognizer = AceType::MakeRefPtr<ExclusiveRecognizer>(recognizers);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    std::vector<RefPtr<NGGestureRecognizer>> recognizers2 = {};
    RefPtr<ExclusiveRecognizer> exclusiveRecognizerPtr = AceType::MakeRefPtr<ExclusiveRecognizer>(recognizers2);

    /**
     * @tc.steps: step2. call function and compare result.
     * @tc.steps: case1: recognizers is empty
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer->recognizers_.clear();
    exclusiveRecognizer->recognizers_.push_back(exclusiveRecognizerPtr);
    exclusiveRecognizer->OnFlushTouchEventsBegin();
    exclusiveRecognizer->OnFlushTouchEventsEnd();
    exclusiveRecognizer->ForceReject();
    EXPECT_EQ(exclusiveRecognizer->recognizers_.size(), 1);

    /**
     * @tc.steps: step2. call function and compare result.
     * @tc.steps: case1: recognizers is empty
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer->recognizers_.clear();
    clickRecognizerPtr->refereeState_ = RefereeState::DETECTING;
    exclusiveRecognizer->recognizers_.push_back(clickRecognizerPtr);
    exclusiveRecognizer->OnFlushTouchEventsBegin();
    exclusiveRecognizer->OnFlushTouchEventsEnd();
    exclusiveRecognizer->ForceReject();
    EXPECT_EQ(exclusiveRecognizer->recognizers_.size(), 1);

    /**
     * @tc.steps: step2. call function and compare result.
     * @tc.steps: case1: recognizers is empty
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer->recognizers_.clear();
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED_BLOCKED;
    exclusiveRecognizer->recognizers_.push_back(clickRecognizerPtr);
    exclusiveRecognizer->OnFlushTouchEventsBegin();
    exclusiveRecognizer->OnFlushTouchEventsEnd();
    exclusiveRecognizer->ForceReject();
    EXPECT_EQ(exclusiveRecognizer->recognizers_.size(), 1);

    /**
     * @tc.steps: step2. call function and compare result.
     * @tc.steps: case1: recognizers is empty
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer->recognizers_.clear();
    clickRecognizerPtr->refereeState_ = RefereeState::SUCCEED;
    exclusiveRecognizer->recognizers_.push_back(clickRecognizerPtr);
    exclusiveRecognizer->OnFlushTouchEventsBegin();
    exclusiveRecognizer->OnFlushTouchEventsEnd();
    exclusiveRecognizer->ForceReject();
    EXPECT_EQ(exclusiveRecognizer->recognizers_.size(), 1);

    /**
     * @tc.steps: step2. call function and compare result.
     * @tc.steps: case1: recognizers is empty
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer->recognizers_.clear();
    clickRecognizerPtr->refereeState_ = RefereeState::FAIL;
    exclusiveRecognizer->recognizers_.push_back(clickRecognizerPtr);
    exclusiveRecognizer->OnFlushTouchEventsBegin();
    exclusiveRecognizer->OnFlushTouchEventsEnd();
    exclusiveRecognizer->ForceReject();
    EXPECT_EQ(exclusiveRecognizer->recognizers_.size(), 1);
}

/**
 * @tc.name: RecognizerGroupTest008
 * @tc.desc: Test RecognizerGroup function: CheckAllFailed
 * @tc.type: FUNC
 */
HWTEST_F(GestureGroupTestNg, RecognizerGroupTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create RecognizerGroup
     */
    std::vector<RefPtr<NGGestureRecognizer>> recognizers = {};
    RefPtr<ExclusiveRecognizer> exclusiveRecognizer = AceType::MakeRefPtr<ExclusiveRecognizer>(recognizers);

    /**
     * @tc.steps: step2. call function and compare result.
     * @tc.steps: case1: recognizers is empty
     * @tc.expected: step2. result equals.
     */
    exclusiveRecognizer->OnFlushTouchEventsBegin();
    exclusiveRecognizer->OnFlushTouchEventsEnd();
    bool result = exclusiveRecognizer->CheckAllFailed();
    EXPECT_EQ(exclusiveRecognizer->recognizers_.size(), 0);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: GestureGroupTest001
 * @tc.desc: Test GestureGroup CreateRecognizer function
 */
HWTEST_F(GestureGroupTestNg, GestureGroupTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureGroup.
     */
    GestureGroupModelNG gestureGroupModelNG;
    gestureGroupModelNG.Create(0);

    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto gestureGroupNG = AceType::DynamicCast<NG::GestureGroup>(gestureProcessor->TopGestureNG());
    EXPECT_EQ(gestureGroupNG->mode_, GestureMode::Sequence);

    GestureGroup gestureGroup = GestureGroup(GestureMode::Sequence);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case1: GestureMode::Begin
     */
    gestureGroup.priority_ = GesturePriority::Low;
    gestureGroup.gestureMask_ = GestureMask::Normal;
    gestureGroup.mode_ = GestureMode::Begin;
    auto groupRecognizer = gestureGroup.CreateRecognizer();
    EXPECT_EQ(groupRecognizer, nullptr);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case2: GestureMode::Sequence
     */
    gestureGroup.priority_ = GesturePriority::Low;
    gestureGroup.gestureMask_ = GestureMask::Normal;
    gestureGroup.mode_ = GestureMode::Sequence;
    groupRecognizer = gestureGroup.CreateRecognizer();
    EXPECT_NE(groupRecognizer, nullptr);
    EXPECT_EQ(groupRecognizer->GetPriority(), GesturePriority::Low);
    EXPECT_EQ(groupRecognizer->GetPriorityMask(), GestureMask::Normal);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case3: GestureMode::Parallel
     */
    gestureGroup.priority_ = GesturePriority::Low;
    gestureGroup.gestureMask_ = GestureMask::Normal;
    gestureGroup.mode_ = GestureMode::Parallel;
    groupRecognizer = gestureGroup.CreateRecognizer();
    EXPECT_NE(groupRecognizer, nullptr);
    EXPECT_EQ(groupRecognizer->GetPriority(), GesturePriority::Low);
    EXPECT_EQ(groupRecognizer->GetPriorityMask(), GestureMask::Normal);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case4: GestureMode::Exclusive
     */
    gestureGroup.priority_ = GesturePriority::Low;
    gestureGroup.gestureMask_ = GestureMask::Normal;
    gestureGroup.mode_ = GestureMode::Exclusive;
    groupRecognizer = gestureGroup.CreateRecognizer();
    EXPECT_NE(groupRecognizer, nullptr);
    EXPECT_EQ(groupRecognizer->GetPriority(), GesturePriority::Low);
    EXPECT_EQ(groupRecognizer->GetPriorityMask(), GestureMask::Normal);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case5: GestureMode::End
     */
    gestureGroup.priority_ = GesturePriority::Low;
    gestureGroup.gestureMask_ = GestureMask::Normal;
    gestureGroup.mode_ = GestureMode::End;
    groupRecognizer = gestureGroup.CreateRecognizer();
    EXPECT_EQ(groupRecognizer, nullptr);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case6: GestureMode::Sequence, have onActionCancelId_
     */
    gestureGroup.priority_ = GesturePriority::Low;
    gestureGroup.gestureMask_ = GestureMask::Normal;
    gestureGroup.mode_ = GestureMode::Sequence;
    std::unique_ptr<GestureEventFunc> onActionCancelId;
    gestureGroup.onActionCancelId_ = std::move(onActionCancelId);
    groupRecognizer = gestureGroup.CreateRecognizer();
    EXPECT_NE(groupRecognizer, nullptr);
}

/**
 * @tc.name: GestureGroupGestureGroupTest003
 * @tc.desc: Test GestureGroup GestureGroup
 */
HWTEST_F(GestureGroupTestNg, GestureGroupGestureGroupTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureGroup.
     */
    GestureGroupModelNG gestureGroupModelNG;
    gestureGroupModelNG.Create(0);

    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto gestureGroupNG = AceType::DynamicCast<NG::GestureGroup>(gestureProcessor->TopGestureNG());
    std::vector<RefPtr<Gesture>> gestures;
    RefPtr<LongPressGesture> LongPressGesturePtr = AceType::MakeRefPtr<LongPressGesture>(FINGER_NUMBER,
        false, LONG_PRESS_DURATION, false, false);
    gestures.push_back(LongPressGesturePtr);

    GestureGroup gestureGroup = GestureGroup(GestureMode::Sequence);
    gestureGroup.gestures_ = gestures;

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case1: GestureMode::Begin
     */
    gestureGroup.priority_ = GesturePriority::Low;
    gestureGroup.gestureMask_ = GestureMask::Normal;
    gestureGroup.mode_ = GestureMode::Begin;
    auto groupRecognizer = gestureGroup.CreateRecognizer();
    EXPECT_EQ(groupRecognizer, nullptr);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case2: GestureMode::Sequence
     */
    gestureGroup.priority_ = GesturePriority::Low;
    gestureGroup.gestureMask_ = GestureMask::Normal;
    gestureGroup.mode_ = GestureMode::Sequence;
    groupRecognizer = gestureGroup.CreateRecognizer();
    EXPECT_EQ(groupRecognizer->GetPriorityMask(), GestureMask::Normal);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case3: GestureMode::Parallel
     */
    gestureGroup.priority_ = GesturePriority::Low;
    gestureGroup.gestureMask_ = GestureMask::Normal;
    gestureGroup.mode_ = GestureMode::Parallel;
    groupRecognizer = gestureGroup.CreateRecognizer();
    EXPECT_EQ(groupRecognizer->GetPriorityMask(), GestureMask::Normal);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case4: GestureMode::Exclusive
     */
    gestureGroup.priority_ = GesturePriority::Low;
    gestureGroup.gestureMask_ = GestureMask::Normal;
    gestureGroup.mode_ = GestureMode::Exclusive;
    groupRecognizer = gestureGroup.CreateRecognizer();
    EXPECT_EQ(groupRecognizer->GetPriorityMask(), GestureMask::Normal);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case5: GestureMode::End
     */
    gestureGroup.priority_ = GesturePriority::Low;
    gestureGroup.gestureMask_ = GestureMask::Normal;
    gestureGroup.mode_ = GestureMode::End;
    groupRecognizer = gestureGroup.CreateRecognizer();
    EXPECT_EQ(groupRecognizer, nullptr);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case6: GestureMode::Sequence, have onActionCancelId_
     */
    gestureGroup.priority_ = GesturePriority::Low;
    gestureGroup.gestureMask_ = GestureMask::Normal;
    gestureGroup.mode_ = GestureMode::Sequence;
    std::unique_ptr<GestureEventFunc> onActionCancelId;
    gestureGroup.onActionCancelId_ = std::move(onActionCancelId);
    groupRecognizer = gestureGroup.CreateRecognizer();
    EXPECT_NE(groupRecognizer, nullptr);
}

/**
 * @tc.name: GestureGroupCreateRecognizerTest001
 * @tc.desc: Test GestureGroup CreateRecognizer function
 */
HWTEST_F(GestureGroupTestNg, GestureGroupCreateRecognizerTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create GestureGroup.
     */
    GestureGroupModelNG gestureGroupModelNG;
    gestureGroupModelNG.Create(0);

    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto gestureGroupNG = AceType::DynamicCast<NG::GestureGroup>(gestureProcessor->TopGestureNG());
    EXPECT_EQ(gestureGroupNG->mode_, GestureMode::Sequence);

    GestureGroup gestureGroup = GestureGroup(GestureMode::Sequence);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case1: GestureMode::Begin
     */
    gestureGroup.priority_ = GesturePriority::Low;
    gestureGroup.gestureMask_ = GestureMask::Normal;
    gestureGroup.mode_ = GestureMode::Begin;
    auto groupRecognizer = gestureGroup.CreateRecognizer();
    EXPECT_EQ(groupRecognizer, nullptr);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case2: GestureMode::Sequence
     */
    gestureGroup.priority_ = GesturePriority::Low;
    gestureGroup.gestureMask_ = GestureMask::Normal;
    gestureGroup.mode_ = GestureMode::Sequence;
    auto onActionCancel = [](const GestureEvent& info) { return true; };
    gestureGroup.SetOnActionCancelId(onActionCancel);
    groupRecognizer = gestureGroup.CreateRecognizer();
    EXPECT_NE(groupRecognizer, nullptr);
    EXPECT_EQ(groupRecognizer->GetPriority(), GesturePriority::Low);
    EXPECT_EQ(groupRecognizer->GetPriorityMask(), GestureMask::Normal);
}

/**
 * @tc.name: GestureGroupTestNg001
 * @tc.desc: Test GestureGroup Deserialize function
 */
HWTEST_F(GestureGroupTestNg, GestureGroupTestNg001, TestSize.Level1)
{
    GestureGroupModelNG gestureGroupModelNG;
    gestureGroupModelNG.Create(0);
    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto gestureGroupNG = AceType::DynamicCast<NG::GestureGroup>(gestureProcessor->TopGestureNG());
    GestureGroup gestureGroup = GestureGroup(GestureMode::Sequence);
    const char* buff = "-123bytes";
    gestureGroup.Deserialize(buff);
    const char* buff2 = nullptr;
    auto result = gestureGroup.Deserialize(buff2);
    char buff3[8] = { 0, 0, 0, 0, 3 & 0xFF, 0, 0, 0 };
    gestureGroup.Deserialize(buff3);
    char buff4[8] = { 0, 0, 0, 0, 7 & 0xFF, 0, 0, 0 };
    gestureGroup.Deserialize(buff4);
    char buff5[8] = { 0, 0, 0, 0, 11 & 0xFF, 0, 0, 0 };
    gestureGroup.Deserialize(buff5);
    char buff6[8] = { 0, 0, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF };
    gestureGroup.Deserialize(buff6);
    char buff7[20] = { 0, 0, 0, 0, 13 & 0xFF, 0, 0, 0, 8 & 0xFF, 0, 0, 0, 8 & 0xFF, 0, 0, 0, 8 & 0xFF, 0, 0, 0 };
    gestureGroup.Deserialize(buff7);
    char buff8[8] = { 0, 0, 0, 0, 12 & 0xFF, 0, 0, 0 };
    gestureGroup.Deserialize(buff8);
    char buff9[16] = { 0, 0, 0, 0, 172 & 0xFF, 0, 0, 0, 8 & 0xFF, 0, 0, 0, 8 & 0xFF, 0, 0, 0 };
    gestureGroup.Deserialize(buff9);
    EXPECT_EQ(result, -1);
}

/**
 * @tc.name: GestureGroupTestNg002
 * @tc.desc: Test GestureGroup SizeofMe function
 */
HWTEST_F(GestureGroupTestNg, GestureGroupTestNg002, TestSize.Level1)
{
    GestureGroupModelNG gestureGroupModelNG;
    gestureGroupModelNG.Create(0);
    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto gestureGroupNG = AceType::DynamicCast<NG::GestureGroup>(gestureProcessor->TopGestureNG());
    GestureGroup gestureGroup = GestureGroup(GestureMode::Sequence);
    gestureGroup.MakeGesture(GestureType::GROUP);
    auto result = gestureGroup.MakeGesture(GestureType::LONG_PRESS);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: GestureGroupTestNg003
 * @tc.desc: Test GestureGroup Serialize function
 */
HWTEST_F(GestureGroupTestNg, GestureGroupTestNg003, TestSize.Level1)
{
    GestureGroupModelNG gestureGroupModelNG;
    gestureGroupModelNG.Create(0);
    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto gestureGroupNG = AceType::DynamicCast<NG::GestureGroup>(gestureProcessor->TopGestureNG());
    GestureGroup gestureGroup = GestureGroup(GestureMode::Sequence);
    char* buff = nullptr;
    auto result = gestureGroup.Serialize(buff);
    char buff2[16] = { 0, 0, 0, 0, 172 & 0xFF, 0, 0, 0, 8 & 0xFF, 0, 0, 0, 8 & 0xFF, 0, 0, 0 };
    gestureGroup.Serialize(buff2);
    EXPECT_EQ(result, -1);
}

/**
 * @tc.name: GestureGroupTestNg004
 * @tc.desc: Test GestureGroup RemoveGesture function
 */
HWTEST_F(GestureGroupTestNg, GestureGroupTestNg004, TestSize.Level1)
{
    bool result = true;
    GestureGroupModelNG gestureGroupModelNG;
    gestureGroupModelNG.Create(0);
    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto gestureGroupNG = AceType::DynamicCast<NG::GestureGroup>(gestureProcessor->TopGestureNG());
    GestureGroup gestureGroup = GestureGroup(GestureMode::Sequence);
    auto gesture = AceType::MakeRefPtr<TapGesture>();
    auto gesture2 = AceType::MakeRefPtr<TapGesture>();
    auto gesture3 = AceType::MakeRefPtr<TapGesture>();
    gestureGroup.AddGesture(gesture);
    gestureGroup.AddGesture(gesture2);
    gestureGroup.AddGesture(gesture3);

    std::vector<RefPtr<Gesture>> gestures;
    auto longPressGestureOne = AceType::MakeRefPtr<LongPressGesture>(5, false, 1);
    longPressGestureOne->SetTag("HELLO");
    gestures.emplace_back(longPressGestureOne);
    auto longPressGestureTwo = AceType::MakeRefPtr<LongPressGesture>(5, false, 1);
    gestures.emplace_back(longPressGestureTwo);
    auto group = AceType::MakeRefPtr<GestureGroup>(GestureMode::Exclusive, gestures);
    gestureGroup.AddGesture(group);

    gestureGroup.RemoveGesture(gesture2);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: GestureGroupTestNg005
 * @tc.desc: Test GestureGroup RemoveChildrenByTag function
 */
HWTEST_F(GestureGroupTestNg, GestureGroupTestNg005, TestSize.Level1)
{
    bool result = true;
    GestureGroupModelNG gestureGroupModelNG;
    gestureGroupModelNG.Create(0);
    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto gestureGroupNG = AceType::DynamicCast<NG::GestureGroup>(gestureProcessor->TopGestureNG());
    GestureGroup gestureGroup = GestureGroup(GestureMode::Sequence);

    std::vector<RefPtr<Gesture>> gestures;
    auto longPressGestureOne = AceType::MakeRefPtr<LongPressGesture>(5, false, 1);
    longPressGestureOne->SetTag("HELLO");
    gestures.emplace_back(longPressGestureOne);
    auto longPressGestureTwo = AceType::MakeRefPtr<LongPressGesture>(5, false, 1);
    gestures.emplace_back(longPressGestureTwo);
    auto group = AceType::MakeRefPtr<GestureGroup>(GestureMode::Exclusive, gestures);
    gestureGroup.AddGesture(group);

    gestureGroup.RemoveChildrenByTag("HELLO", result);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: GestureGroupTestNg006
 * @tc.desc: Test Pan_Gesture Deserialize function
 */
HWTEST_F(GestureGroupTestNg, GestureGroupTestNg006, TestSize.Level1)
{
    PanDirection panDirection;
    panDirection.type = PanDirection::RIGHT;
    auto panGesture = AceType::MakeRefPtr<PanGesture>(SINGLE_FINGER_NUMBER, panDirection, PAN_DISTANCE);
    const char* buff = nullptr;
    auto result = panGesture->Deserialize(buff);
    char buff2[320] = { 0, 0, 0, 0, 13 & 0xFF, 0, 0, 0, 8 & 0xFF, 0, 0, 0, 8 & 0xFF, 0, 0, 0, 8 & 0xFF, 0, 0, 0 };
    panGesture->Deserialize(buff2);
    EXPECT_EQ(result, -1);
}

/**
 * @tc.name: GestureGroupTestNg007
 * @tc.desc: Test Pan_Gesture Serialize function
 */
HWTEST_F(GestureGroupTestNg, GestureGroupTestNg007, TestSize.Level1)
{
    PanDirection panDirection;
    panDirection.type = PanDirection::RIGHT;
    auto panGesture = AceType::MakeRefPtr<PanGesture>(SINGLE_FINGER_NUMBER, panDirection, PAN_DISTANCE);
    char* buff = nullptr;
    auto result = panGesture->Serialize(buff);
    char buff2[320] = { 0, 0, 0, 0, 172 & 0xFF, 0, 0, 0, 8 & 0xFF, 0, 0, 0, 8 & 0xFF, 0, 0, 0 };
    panGesture->Serialize(buff2);
    EXPECT_EQ(result, -1);
}
} // namespace OHOS::Ace::NG