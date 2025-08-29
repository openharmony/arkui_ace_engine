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
#include "test/unittest/core/gestures/gestures_common_test_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class RecognizerGroupTestNg : public GesturesCommonTestNg {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void RecognizerGroupTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void RecognizerGroupTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: RecognizerGroupTest001
 * @tc.desc: Test PinchRecognizer function: OnAccepted OnRejected
 * @tc.type: FUNC
 */
HWTEST_F(RecognizerGroupTestNg, RecognizerGroupTest001, TestSize.Level1)
{
    std::vector<RefPtr<NGGestureRecognizer>> longPressRecognizers;
    auto longPressRecognizer = AceType::MakeRefPtr<LongPressRecognizer>(false, true);
    longPressRecognizers.push_back(AceType::DynamicCast<NGGestureRecognizer>(longPressRecognizer));
    ExclusiveRecognizer excluRecognizer(longPressRecognizers);
    auto recognizer = excluRecognizer.CreateGestureFromRecognizer();
    EXPECT_NE(recognizer, nullptr);
}

/**
 * @tc.name: RecognizerGroupTest003
 * @tc.desc: Test PinchRecognizer function: OnAccepted OnRejected
 * @tc.type: FUNC
 */
HWTEST_F(RecognizerGroupTestNg, RecognizerGroupTest003, TestSize.Level1)
{
    std::vector<RefPtr<NGGestureRecognizer>> longPressRecognizers;
    auto longPressRecognizer = AceType::MakeRefPtr<LongPressRecognizer>(false, true);
    longPressRecognizers.push_back(AceType::DynamicCast<NGGestureRecognizer>(longPressRecognizer));
    ExclusiveRecognizer excluRecognizer(longPressRecognizers);
    Offset coordinateOffset;
    std::string test = "test";
    int32_t nodeid = 1;
    auto nodePtr = SelectOverlayNode::GetFrameNode(test, nodeid);
    auto component = AceType::MakeRefPtr<TargetComponent>();
    PanDirection panDirection;
    panDirection.type = PanDirection::VERTICAL;
    auto panRecognizer = AceType::MakeRefPtr<PanRecognizer>(1, panDirection, 0);
    std::vector<RefPtr<NGGestureRecognizer>> recognizers { panRecognizer };
    auto testRecognizer = AceType::MakeRefPtr<SequencedRecognizer>(recognizers);
    auto gesture = AceType::MakeRefPtr<NG::GestureReferee>();
    auto Ngg = AceType::DynamicCast<NG::NGGestureRecognizer>(testRecognizer);
    excluRecognizer.recognizers_.push_back(Ngg);
    GetEventTargetImpl getEventTargetImpl = []() -> std::optional<EventTarget> {
        EventTarget target;
        return target;
    };
    excluRecognizer.SetRecognizerInfoRecursively(coordinateOffset, nodePtr, component, getEventTargetImpl);
    EXPECT_EQ(panDirection.type, PanDirection::VERTICAL);
}

/**
 * @tc.name: RecognizerGroupTest004
 * @tc.desc: Test AddHittedRecognizerType
 * @tc.type: FUNC
 */
HWTEST_F(RecognizerGroupTestNg, RecognizerGroupTest004, TestSize.Level1)
{
    std::vector<RefPtr<NGGestureRecognizer>> longPressRecognizers;
    auto longPressRecognizer = AceType::MakeRefPtr<LongPressRecognizer>(false, true);
    longPressRecognizers.push_back(AceType::DynamicCast<NGGestureRecognizer>(longPressRecognizer));
    ExclusiveRecognizer excluRecognizer(longPressRecognizers);
    TouchTestResultInfo tesultInfo;
    tesultInfo.depth = 1;
    std::list<TouchTestResultInfo> testList;
    testList.push_back(tesultInfo);
    std::map<std::string, std::list<TouchTestResultInfo>> tetMap;
    tetMap["test"] = testList;
    excluRecognizer.AddHittedRecognizerType(tetMap);
    EXPECT_EQ(tesultInfo.depth, 1);
}

/**
 * @tc.name: RecognizerGroupTest005
 * @tc.desc: Test CleanRecognizerState
 * @tc.type: FUNC
 */
HWTEST_F(RecognizerGroupTestNg, RecognizerGroupTest005, TestSize.Level1)
{
    std::vector<RefPtr<NGGestureRecognizer>> longPressRecognizers;
    auto longPressRecognizer = AceType::MakeRefPtr<LongPressRecognizer>(false, true);
    longPressRecognizers.push_back(AceType::DynamicCast<NGGestureRecognizer>(longPressRecognizer));
    ExclusiveRecognizer excluRecognizer(longPressRecognizers);
    excluRecognizer.refereeState_ = RefereeState::SUCCEED;
    excluRecognizer.currentFingers_ = 0;
    excluRecognizer.RecognizerGroup::CleanRecognizerState();
    std::vector<RefPtr<NGGestureRecognizer>> longPressRecognizers1;
    auto longPressRecognizer1 = AceType::MakeRefPtr<LongPressRecognizer>(false, true);
    longPressRecognizers1.push_back(AceType::DynamicCast<NGGestureRecognizer>(longPressRecognizer1));
    ExclusiveRecognizer excluRecognizer1(longPressRecognizers1);
    excluRecognizer1.refereeState_ = RefereeState::FAIL;
    excluRecognizer1.currentFingers_ = 0;
    excluRecognizer1.RecognizerGroup::CleanRecognizerState();
    std::vector<RefPtr<NGGestureRecognizer>> longPressRecognizers2;
    auto longPressRecognizer2 = AceType::MakeRefPtr<LongPressRecognizer>(false, true);
    longPressRecognizers2.push_back(AceType::DynamicCast<NGGestureRecognizer>(longPressRecognizer2));
    ExclusiveRecognizer excluRecognizer2(longPressRecognizers2);
    excluRecognizer2.refereeState_ = RefereeState::DETECTING;
    excluRecognizer2.currentFingers_ = 0;
    excluRecognizer2.RecognizerGroup::CleanRecognizerState();
    EXPECT_EQ(excluRecognizer2.currentFingers_, 0);
}

/**
 * @tc.name: RecognizerGroupTest0052
 * @tc.desc: Test CleanRecognizerState
 * @tc.type: FUNC
 */
HWTEST_F(RecognizerGroupTestNg, RecognizerGroupTest0052, TestSize.Level1)
{
    std::vector<RefPtr<NGGestureRecognizer>> longPressRecognizers3;
    auto longPressRecognizer3 = AceType::MakeRefPtr<LongPressRecognizer>(false, true);
    longPressRecognizers3.push_back(AceType::DynamicCast<NGGestureRecognizer>(longPressRecognizer3));
    ExclusiveRecognizer excluRecognizer3(longPressRecognizers3);
    excluRecognizer3.refereeState_ = RefereeState::DETECTING;
    excluRecognizer3.currentFingers_ = 0;
    excluRecognizer3.RecognizerGroup::CleanRecognizerState();
    std::vector<RefPtr<NGGestureRecognizer>> longPressRecognizers4;
    auto longPressRecognizer4 = AceType::MakeRefPtr<LongPressRecognizer>(false, true);
    longPressRecognizers4.push_back(AceType::DynamicCast<NGGestureRecognizer>(longPressRecognizer4));
    ExclusiveRecognizer excluRecognizer4(longPressRecognizers4);
    excluRecognizer4.refereeState_ = RefereeState::DETECTING;
    excluRecognizer4.currentFingers_ = 1;
    excluRecognizer4.RecognizerGroup::CleanRecognizerState();
    std::vector<RefPtr<NGGestureRecognizer>> longPressRecognizers5;
    auto longPressRecognizer5 = AceType::MakeRefPtr<LongPressRecognizer>(false, true);
    longPressRecognizers5.push_back(AceType::DynamicCast<NGGestureRecognizer>(longPressRecognizer5));
    ExclusiveRecognizer excluRecognizer5(longPressRecognizers5);
    excluRecognizer5.refereeState_ = RefereeState::DETECTING;
    excluRecognizer5.currentFingers_ = 1;
    excluRecognizer5.recognizers_.clear();
    excluRecognizer5.RecognizerGroup::CleanRecognizerState();
    EXPECT_EQ(excluRecognizer5.currentFingers_, 1);
}

/**
 * @tc.name: RecognizerGroupTest006
 * @tc.desc: Test CleanRecognizerState
 * @tc.type: FUNC
 */
HWTEST_F(RecognizerGroupTestNg, RecognizerGroupTest006, TestSize.Level1)
{
    std::vector<RefPtr<NGGestureRecognizer>> longPressRecognizers;
    auto longPressRecognizer = AceType::MakeRefPtr<LongPressRecognizer>(false, true);
    longPressRecognizers.push_back(AceType::DynamicCast<NGGestureRecognizer>(longPressRecognizer));
    ExclusiveRecognizer excluRecognizer(longPressRecognizers);
    auto recognizerTest = AceType::DynamicCast<RecognizerGroup>(&excluRecognizer);
    recognizerTest->refereeState_ = RefereeState::READY;
    auto result = recognizerTest->IsReady();
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: RecognizerGroupTest007
 * @tc.desc: Test CleanRecognizerState
 * @tc.type: FUNC
 */
HWTEST_F(RecognizerGroupTestNg, RecognizerGroupTest007, TestSize.Level1)
{
    std::vector<RefPtr<NGGestureRecognizer>> longPressRecognizers;
    auto longPressRecognizer = AceType::MakeRefPtr<LongPressRecognizer>(false, true);
    longPressRecognizers.push_back(AceType::DynamicCast<NGGestureRecognizer>(longPressRecognizer));
    ExclusiveRecognizer excluRecognizer(longPressRecognizers);
    auto recognizerTest = AceType::DynamicCast<RecognizerGroup>(&excluRecognizer);
    recognizerTest->refereeState_ = RefereeState::DETECTING;
    auto result = recognizerTest->IsReady();
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: RecognizerGroupTest008
 * @tc.desc: Test PinchRecognizer function: OnAccepted OnRejected
 * @tc.type: FUNC
 */
HWTEST_F(RecognizerGroupTestNg, RecognizerGroupTest008, TestSize.Level1)
{
    std::vector<RefPtr<NGGestureRecognizer>> longPressRecognizers;
    auto longPressRecognizer = AceType::MakeRefPtr<LongPressRecognizer>(false, true);
    longPressRecognizers.push_back(AceType::DynamicCast<NGGestureRecognizer>(longPressRecognizer));
    ExclusiveRecognizer excluRecognizer(longPressRecognizers);
    Offset coordinateOffset;
    std::string test = "test";
    int32_t nodeid = 1;
    auto nodePtr = SelectOverlayNode::GetFrameNode(test, nodeid);
    auto component = AceType::MakeRefPtr<TargetComponent>();
    GetEventTargetImpl getEventTargetImpl = []() -> std::optional<EventTarget> {
        EventTarget target;
        return target;
    };
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    excluRecognizer.recognizers_.clear();
    excluRecognizer.recognizers_.push_back(clickRecognizerPtr);
    excluRecognizer.SetRecognizerInfoRecursively(coordinateOffset, nodePtr, component, getEventTargetImpl);
    EXPECT_EQ(nodeid, 1);
}

/**
 * @tc.name: RecognizerGroupTest009
 * @tc.desc: Test PinchRecognizer function: OnAccepted OnRejected
 * @tc.type: FUNC
 */
HWTEST_F(RecognizerGroupTestNg, RecognizerGroupTest009, TestSize.Level1)
{
    std::vector<RefPtr<NGGestureRecognizer>> longPressRecognizers;
    auto longPressRecognizer = AceType::MakeRefPtr<LongPressRecognizer>(false, true);
    longPressRecognizers.push_back(AceType::DynamicCast<NGGestureRecognizer>(longPressRecognizer));
    ExclusiveRecognizer excluRecognizer(longPressRecognizers);
    RefPtr<ClickRecognizer> clickRecognizerPtrNotSame = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    excluRecognizer.recognizers_.push_back(clickRecognizerPtrNotSame);
    excluRecognizer.recognizers_.push_back(nullptr);
    auto recognizer = excluRecognizer.CreateGestureFromRecognizer();
    EXPECT_NE(recognizer, nullptr);
}

/**
 * @tc.name: RecognizerGroupTest010
 * @tc.desc: Test AddHittedRecognizerType
 * @tc.type: FUNC
 */
HWTEST_F(RecognizerGroupTestNg, RecognizerGroupTest010, TestSize.Level1)
{
    std::vector<RefPtr<NGGestureRecognizer>> longPressRecognizers;
    auto longPressRecognizer = AceType::MakeRefPtr<LongPressRecognizer>(false, true);
    longPressRecognizers.push_back(AceType::DynamicCast<NGGestureRecognizer>(longPressRecognizer));
    ExclusiveRecognizer excluRecognizer(longPressRecognizers);
    TouchTestResultInfo tesultInfo;
    tesultInfo.depth = 1;
    std::list<TouchTestResultInfo> testList;
    testList.push_back(tesultInfo);
    std::map<std::string, std::list<TouchTestResultInfo>> tetMap;
    tetMap["test"] = testList;
    PanDirection panDirection;
    panDirection.type = PanDirection::VERTICAL;
    auto panRecognizer = AceType::MakeRefPtr<PanRecognizer>(1, panDirection, 0);
    std::vector<RefPtr<NGGestureRecognizer>> recognizers { panRecognizer };
    auto testRecognizer = AceType::MakeRefPtr<SequencedRecognizer>(recognizers);
    auto gesture = AceType::MakeRefPtr<NG::GestureReferee>();
    auto Ngg = AceType::DynamicCast<NG::NGGestureRecognizer>(testRecognizer);
    RefPtr<FrameNode> FRAME_NODE_0 = FrameNode::CreateFrameNode("0", 0, AceType::MakeRefPtr<Pattern>());
    Ngg->AttachFrameNode(FRAME_NODE_0);
    excluRecognizer.recognizers_.push_back(Ngg);
    excluRecognizer.AddHittedRecognizerType(tetMap);
    EXPECT_EQ(panDirection.type, PanDirection::VERTICAL);
}

/**
 * @tc.name: RecognizerGroupTest011
 * @tc.desc: Test CleanRecognizerState
 * @tc.type: FUNC
 */
HWTEST_F(RecognizerGroupTestNg, RecognizerGroupTest011, TestSize.Level1)
{
    std::vector<RefPtr<NGGestureRecognizer>> longPressRecognizers;
    auto longPressRecognizer = AceType::MakeRefPtr<LongPressRecognizer>(false, true);
    longPressRecognizers.push_back(AceType::DynamicCast<NGGestureRecognizer>(longPressRecognizer));
    ExclusiveRecognizer excluRecognizer(longPressRecognizers);
    auto recognizerTest = AceType::DynamicCast<RecognizerGroup>(&excluRecognizer);
    recognizerTest->refereeState_ = RefereeState::READY;
    PanDirection panDirection;
    panDirection.type = PanDirection::VERTICAL;
    auto panRecognizer = AceType::MakeRefPtr<PanRecognizer>(1, panDirection, 0);
    std::vector<RefPtr<NGGestureRecognizer>> recognizers { panRecognizer };
    auto testRecognizer = AceType::MakeRefPtr<SequencedRecognizer>(recognizers);
    auto gesture = AceType::MakeRefPtr<NG::GestureReferee>();
    auto Ngg = AceType::DynamicCast<NG::NGGestureRecognizer>(testRecognizer);
    recognizerTest->recognizers_.push_back(Ngg);
    auto result = recognizerTest->IsReady();
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: RecognizerGroupTest012
 * @tc.desc: Test CleanRecognizerState
 * @tc.type: FUNC
 */
HWTEST_F(RecognizerGroupTestNg, RecognizerGroupTest012, TestSize.Level1)
{
    std::vector<RefPtr<NGGestureRecognizer>> longPressRecognizers;
    auto longPressRecognizer = AceType::MakeRefPtr<LongPressRecognizer>(false, true);
    longPressRecognizers.push_back(AceType::DynamicCast<NGGestureRecognizer>(longPressRecognizer));
    ExclusiveRecognizer excluRecognizer(longPressRecognizers);
    auto recognizerTest = AceType::DynamicCast<RecognizerGroup>(&excluRecognizer);
    recognizerTest->refereeState_ = RefereeState::DETECTING;
    PanDirection panDirection;
    panDirection.type = PanDirection::VERTICAL;
    auto panRecognizer = AceType::MakeRefPtr<PanRecognizer>(1, panDirection, 0);
    std::vector<RefPtr<NGGestureRecognizer>> recognizers { panRecognizer };
    auto testRecognizer = AceType::MakeRefPtr<SequencedRecognizer>(recognizers);
    auto gesture = AceType::MakeRefPtr<NG::GestureReferee>();
    auto Ngg = AceType::DynamicCast<NG::NGGestureRecognizer>(testRecognizer);
    recognizerTest->recognizers_.push_back(Ngg);
    auto result = recognizerTest->IsReady();
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: RecognizerGroupTest013
 * @tc.desc: Test ForceCleanRecognizerWithGroup
 * @tc.type: FUNC
 */
HWTEST_F(RecognizerGroupTestNg, RecognizerGroupTest013, TestSize.Level1)
{
    /**
     * @tc.step1: Create gestureGroup.
     * @tc.expected: GestureGroup is not nullptr.
     */
    std::vector<RefPtr<NGGestureRecognizer>> longPressRecognizers;
    auto longPressRecognizer = AceType::MakeRefPtr<LongPressRecognizer>(false, true);
    longPressRecognizers.push_back(AceType::DynamicCast<NGGestureRecognizer>(longPressRecognizer));
    ExclusiveRecognizer excluRecognizer(longPressRecognizers);
    auto recognizerTest = AceType::DynamicCast<RecognizerGroup>(&excluRecognizer);
    recognizerTest->refereeState_ = RefereeState::DETECTING;
    PanDirection panDirection;
    panDirection.type = PanDirection::VERTICAL;
    auto panRecognizer = AceType::MakeRefPtr<PanRecognizer>(1, panDirection, 0);
    std::vector<RefPtr<NGGestureRecognizer>> recognizers { panRecognizer };
    auto testRecognizer = AceType::MakeRefPtr<SequencedRecognizer>(recognizers);
    auto gestureRecognizer = AceType::DynamicCast<NG::NGGestureRecognizer>(testRecognizer);
    recognizerTest->recognizers_.push_back(gestureRecognizer);
    recognizerTest->recognizers_.push_back(nullptr);
    recognizerTest->RemainChildOnResetStatus();
    /**
     * @tc.step2: Call ForceCleanRecognizerWithGroup.
     * @tc.expected: RecognizerTest->recognizers_.empty() is false.
     */
    recognizerTest->ForceCleanRecognizerWithGroup();
    EXPECT_EQ(recognizerTest->recognizers_.empty(), false);

    /**
     * @tc.step3: Call ForceCleanRecognizerWithGroup.
     * @tc.expected: RecognizerTest->recognizers_.empty() is true.
     */
    recognizerTest->remainChildOnResetStatus_ = false;
    recognizerTest->ForceCleanRecognizerWithGroup();
    EXPECT_EQ(recognizerTest->recognizers_.empty(), true);
}
}; // namespace OHOS::Ace::NG