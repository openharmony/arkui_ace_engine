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
#include "test/unittest/core/gestures/gestures_common_test_ng.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class GestureModelTestNg : public GesturesCommonTestNg {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void GestureModelTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void GestureModelTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: GestureModelTestNg001
 * @tc.desc: test GestureModelNG::Create function
 */
HWTEST_F(GestureModelTestNg, GestureModelTestNg001, TestSize.Level1) {

    GestureModelNG gestureModelNG;
    gestureModelNG.Create(-1, -1);

    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    EXPECT_EQ(gestureProcessor->priority_, GesturePriority::Low);
    EXPECT_EQ(gestureProcessor->gestureMask_, GestureMask::Normal);
}

/**
 * @tc.name: GestureModelTestNg002
 * @tc.desc: test GestureModelNG::Create function
 */
HWTEST_F(GestureModelTestNg, GestureModelTestNg002, TestSize.Level1) {

    GestureModelNG gestureModelNG;
    gestureModelNG.Create(3, 2);

    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    EXPECT_EQ(gestureProcessor->priority_, GesturePriority::Low);
    EXPECT_EQ(gestureProcessor->gestureMask_, GestureMask::Normal);
}

/**
 * @tc.name: GestureModelTestNg003
 * @tc.desc: test SetTag function
 */
HWTEST_F(GestureModelTestNg, GestureModelTestNg003, TestSize.Level1) {

    GestureModelNG gestureModelNG;
    gestureModelNG.Create(3, 2);
    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    gestureModelNG.SetTag("test_tag");
    auto gesture = gestureProcessor->TopGestureNG();
    EXPECT_EQ(gesture->GetTag(), "test_tag");
}

/**
 * @tc.name: GestureModelTestNg004
 * @tc.desc: test SetTag function
 */
HWTEST_F(GestureModelTestNg, GestureModelTestNg004, TestSize.Level1) {

    GestureModelNG gestureModelNG;
    gestureModelNG.Create(3, 2);
    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    std::set<SourceTool> allowType;
    allowType.insert(SourceTool::UNKNOWN);
    gestureModelNG.SetAllowedTypes(allowType);
    auto gesture = gestureProcessor->TopGestureNG();
    EXPECT_EQ(gesture->GetAllowedTypes(), allowType);
}


/**
 * @tc.name: GestureModelTestNg005
 * @tc.desc: test Finish function
 */
HWTEST_F(GestureModelTestNg, GestureModelTestNg005, TestSize.Level1) {
    GestureModelNG gestureModelNG;
    gestureModelNG.Create(3, 2);
    gestureModelNG.Pop();

    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    const int nodeId = 10008;
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::LOCATION_BUTTON_ETS_TAG, nodeId, nullptr);
    NG::ViewStackProcessor::GetInstance()->Push(frameNode);
    RefPtr<GestureEventHub> gestureEventHub;
    gestureEventHub = NG::ViewStackProcessor::GetInstance()->GetMainFrameNodeGestureEventHub();

    gestureModelNG.Finish();
    EXPECT_NE(gestureEventHub, nullptr);
    EXPECT_FALSE(gestureEventHub->IsGestureEmpty());
}

/**
 * @tc.name: GestureModelTestNg006
 * @tc.desc: test Finish function
 */
HWTEST_F(GestureModelTestNg, GestureModelTestNg006, TestSize.Level1) {
    GestureModelNG gestureModelNG;
    gestureModelNG.Create(3, 2);

    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    const int nodeId = 10008;
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::LOCATION_BUTTON_ETS_TAG, nodeId, nullptr);
    NG::ViewStackProcessor::GetInstance()->Push(frameNode);
    RefPtr<GestureEventHub> gestureEventHub;
    gestureEventHub = NG::ViewStackProcessor::GetInstance()->GetMainFrameNodeGestureEventHub();
    
    gestureModelNG.Finish();
    EXPECT_NE(gestureEventHub, nullptr);
    EXPECT_FALSE(gestureEventHub->IsGestureEmpty());
}

/**
 * @tc.name: GestureModelTestNg007
 * @tc.desc: test Finish function
 */
HWTEST_F(GestureModelTestNg, GestureModelTestNg007, TestSize.Level1) {
    GestureModelNG gestureModelNG;
    gestureModelNG.Create(3, 2);

    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto tapGesture = AceType::MakeRefPtr<NG::TapGesture>(1, 1);
    auto onActionStart = [](GestureEvent& info) { return true; };
    tapGesture->SetOnActionId(onActionStart);
    gestureProcessor->PushGestureNG(tapGesture);

    const int nodeId = 10008;
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::LOCATION_BUTTON_ETS_TAG, nodeId, nullptr);
    NG::ViewStackProcessor::GetInstance()->Push(frameNode);
    RefPtr<GestureEventHub> gestureEventHub;
    gestureEventHub = NG::ViewStackProcessor::GetInstance()->GetMainFrameNodeGestureEventHub();
    auto focusHub = NG::ViewStackProcessor::GetInstance()->GetOrCreateMainFrameNodeFocusHub();

    gestureModelNG.Finish();
    EXPECT_NE(gestureEventHub, nullptr);
    EXPECT_NE(focusHub, nullptr);
    EXPECT_FALSE(gestureEventHub->IsGestureEmpty());
    EXPECT_NE(focusHub->GetOnClickCallback(), nullptr);
}


/**
 * @tc.name: GestureModelTestNg008
 * @tc.desc: test Finish function
 */
HWTEST_F(GestureModelTestNg, GestureModelTestNg008, TestSize.Level1) {
    GestureModelNG gestureModelNG;
    gestureModelNG.Create(3, 2);

    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto tapGesture = AceType::MakeRefPtr<NG::TapGesture>(1, 1);
    auto onActionStart = [](GestureEvent& info) { return true; };
    tapGesture->SetOnActionId(onActionStart);

    auto gestureGroupNG = AceType::DynamicCast<NG::GestureGroup>(gestureProcessor->TopGestureNG());
    std::vector<RefPtr<Gesture>> gestures;
    gestures.push_back(tapGesture);
    GestureGroup gestureGroup = GestureGroup(GestureMode::Sequence);
    gestureGroup.gestures_ = gestures;
    gestureProcessor->PushGestureNG(tapGesture);

    const int nodeId = 10008;
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::LOCATION_BUTTON_ETS_TAG, nodeId, nullptr);
    NG::ViewStackProcessor::GetInstance()->Push(frameNode);
    RefPtr<GestureEventHub> gestureEventHub;
    gestureEventHub = NG::ViewStackProcessor::GetInstance()->GetMainFrameNodeGestureEventHub();
    auto focusHub = NG::ViewStackProcessor::GetInstance()->GetOrCreateMainFrameNodeFocusHub();

    gestureModelNG.Finish();
    EXPECT_NE(gestureEventHub, nullptr);
    EXPECT_NE(focusHub, nullptr);
    EXPECT_FALSE(gestureEventHub->IsGestureEmpty());
    EXPECT_NE(focusHub->GetOnClickCallback(), nullptr);
}

/**
 * @tc.name: GestureModelTestNg009
 * @tc.desc: test Finish function
 */
HWTEST_F(GestureModelTestNg, GestureModelTestNg009, TestSize.Level1) {
    GestureModelNG gestureModelNG;
    gestureModelNG.Create(3, 2);

    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto tapGesture = AceType::MakeRefPtr<NG::TapGesture>(1, 1);
    tapGesture->SetOnActionId(nullptr);
    gestureProcessor->PushGestureNG(tapGesture);

    const int nodeId = 10008;
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::LOCATION_BUTTON_ETS_TAG, nodeId, nullptr);
    NG::ViewStackProcessor::GetInstance()->Push(frameNode);
    RefPtr<GestureEventHub> gestureEventHub;
    gestureEventHub = NG::ViewStackProcessor::GetInstance()->GetMainFrameNodeGestureEventHub();
    auto focusHub = NG::ViewStackProcessor::GetInstance()->GetOrCreateMainFrameNodeFocusHub();

    gestureModelNG.Finish();
    EXPECT_NE(gestureEventHub, nullptr);
    EXPECT_NE(focusHub, nullptr);
    EXPECT_FALSE(gestureEventHub->IsGestureEmpty());
    EXPECT_NE(focusHub->GetOnClickCallback(), nullptr);
}

/**
 * @tc.name: GestureModelTestNg010
 * @tc.desc: test Finish function
 */
HWTEST_F(GestureModelTestNg, GestureModelTestNg010, TestSize.Level1) {
    GestureModelNG gestureModelNG;
    gestureModelNG.Create(3, 2);

    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto tapGesture = AceType::MakeRefPtr<NG::TapGesture>(1, 1);
    tapGesture->SetOnActionId(nullptr);

    auto gestureGroupNG = AceType::DynamicCast<NG::GestureGroup>(gestureProcessor->TopGestureNG());
    std::vector<RefPtr<Gesture>> gestures;
    gestures.push_back(tapGesture);
    GestureGroup gestureGroup = GestureGroup(GestureMode::Sequence);
    gestureGroup.gestures_ = gestures;
    gestureProcessor->PushGestureNG(tapGesture);

    const int nodeId = 10008;
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::LOCATION_BUTTON_ETS_TAG, nodeId, nullptr);
    NG::ViewStackProcessor::GetInstance()->Push(frameNode);
    RefPtr<GestureEventHub> gestureEventHub;
    gestureEventHub = NG::ViewStackProcessor::GetInstance()->GetMainFrameNodeGestureEventHub();
    auto focusHub = NG::ViewStackProcessor::GetInstance()->GetOrCreateMainFrameNodeFocusHub();

    gestureModelNG.Finish();
    EXPECT_NE(gestureEventHub, nullptr);
    EXPECT_NE(focusHub, nullptr);
    EXPECT_FALSE(gestureEventHub->IsGestureEmpty());
    EXPECT_NE(focusHub->GetOnClickCallback(), nullptr);
}


/**
 * @tc.name: GestureModelTestNg011
 * @tc.desc: test Finish function
 */
HWTEST_F(GestureModelTestNg, GestureModelTestNg011, TestSize.Level1) {
    GestureModelNG gestureModelNG;
    gestureModelNG.Create(3, 2);

    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto tapGesture = AceType::MakeRefPtr<NG::TapGesture>(COUNT, FINGER_NUMBER);
    auto onActionStart = [](GestureEvent& info) { return true; };
    tapGesture->SetOnActionId(onActionStart);
    gestureProcessor->PushGestureNG(tapGesture);

    const int nodeId = 10008;
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::LOCATION_BUTTON_ETS_TAG, nodeId, nullptr);
    NG::ViewStackProcessor::GetInstance()->Push(frameNode);
    RefPtr<GestureEventHub> gestureEventHub;
    gestureEventHub = NG::ViewStackProcessor::GetInstance()->GetMainFrameNodeGestureEventHub();
    auto focusHub = NG::ViewStackProcessor::GetInstance()->GetOrCreateMainFrameNodeFocusHub();

    gestureModelNG.Finish();
    EXPECT_NE(gestureEventHub, nullptr);
    EXPECT_NE(focusHub, nullptr);
    EXPECT_FALSE(gestureEventHub->IsGestureEmpty());
    EXPECT_NE(focusHub->GetOnClickCallback(), nullptr);
}


/**
 * @tc.name: GestureModelTestNg012
 * @tc.desc: test Finish function
 */
HWTEST_F(GestureModelTestNg, GestureModelTestNg012, TestSize.Level1) {
    GestureModelNG gestureModelNG;
    gestureModelNG.Create(3, 2);

    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto tapGesture = AceType::MakeRefPtr<NG::TapGesture>(COUNT, FINGER_NUMBER);
    auto onActionStart = [](GestureEvent& info) { return true; };
    tapGesture->SetOnActionId(onActionStart);

    auto gestureGroupNG = AceType::DynamicCast<NG::GestureGroup>(gestureProcessor->TopGestureNG());
    std::vector<RefPtr<Gesture>> gestures;
    gestures.push_back(tapGesture);
    GestureGroup gestureGroup = GestureGroup(GestureMode::Sequence);
    gestureGroup.gestures_ = gestures;
    gestureProcessor->PushGestureNG(tapGesture);

    const int nodeId = 10008;
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::LOCATION_BUTTON_ETS_TAG, nodeId, nullptr);
    NG::ViewStackProcessor::GetInstance()->Push(frameNode);
    RefPtr<GestureEventHub> gestureEventHub;
    gestureEventHub = NG::ViewStackProcessor::GetInstance()->GetMainFrameNodeGestureEventHub();
    auto focusHub = NG::ViewStackProcessor::GetInstance()->GetOrCreateMainFrameNodeFocusHub();

    gestureModelNG.Finish();
    EXPECT_NE(gestureEventHub, nullptr);
    EXPECT_NE(focusHub, nullptr);
    EXPECT_FALSE(gestureEventHub->IsGestureEmpty());
    EXPECT_NE(focusHub->GetOnClickCallback(), nullptr);
}

/**
 * @tc.name: GestureModelTestNg013
 * @tc.desc: test Finish function
 */
HWTEST_F(GestureModelTestNg, GestureModelTestNg013, TestSize.Level1) {
    GestureModelNG gestureModelNG;
    gestureModelNG.Create(3, 2);

    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto tapGesture = AceType::MakeRefPtr<NG::TapGesture>(COUNT, FINGER_NUMBER);
    tapGesture->SetOnActionId(nullptr);
    gestureProcessor->PushGestureNG(tapGesture);

    const int nodeId = 10008;
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::LOCATION_BUTTON_ETS_TAG, nodeId, nullptr);
    NG::ViewStackProcessor::GetInstance()->Push(frameNode);
    RefPtr<GestureEventHub> gestureEventHub;
    gestureEventHub = NG::ViewStackProcessor::GetInstance()->GetMainFrameNodeGestureEventHub();
    auto focusHub = NG::ViewStackProcessor::GetInstance()->GetOrCreateMainFrameNodeFocusHub();

    gestureModelNG.Finish();
    EXPECT_NE(gestureEventHub, nullptr);
    EXPECT_NE(focusHub, nullptr);
    EXPECT_FALSE(gestureEventHub->IsGestureEmpty());
    EXPECT_NE(focusHub->GetOnClickCallback(), nullptr);
}

/**
 * @tc.name: GestureModelTestNg014
 * @tc.desc: test Finish function
 */
HWTEST_F(GestureModelTestNg, GestureModelTestNg014, TestSize.Level1) {
    GestureModelNG gestureModelNG;
    gestureModelNG.Create(3, 2);

    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto tapGesture = AceType::MakeRefPtr<NG::TapGesture>(COUNT, FINGER_NUMBER);
    tapGesture->SetOnActionId(nullptr);

    auto gestureGroupNG = AceType::DynamicCast<NG::GestureGroup>(gestureProcessor->TopGestureNG());
    std::vector<RefPtr<Gesture>> gestures;
    gestures.push_back(tapGesture);
    GestureGroup gestureGroup = GestureGroup(GestureMode::Sequence);
    gestureGroup.gestures_ = gestures;
    gestureProcessor->PushGestureNG(tapGesture);

    const int nodeId = 10008;
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::LOCATION_BUTTON_ETS_TAG, nodeId, nullptr);
    NG::ViewStackProcessor::GetInstance()->Push(frameNode);
    RefPtr<GestureEventHub> gestureEventHub;
    gestureEventHub = NG::ViewStackProcessor::GetInstance()->GetMainFrameNodeGestureEventHub();
    auto focusHub = NG::ViewStackProcessor::GetInstance()->GetOrCreateMainFrameNodeFocusHub();

    gestureModelNG.Finish();
    EXPECT_NE(gestureEventHub, nullptr);
    EXPECT_NE(focusHub, nullptr);
    EXPECT_FALSE(gestureEventHub->IsGestureEmpty());
    EXPECT_NE(focusHub->GetOnClickCallback(), nullptr);
}


/**
 * @tc.name: GestureModelTestNg015
 * @tc.desc: test SetOnGestureEvent function
 */
HWTEST_F(GestureModelTestNg, GestureModelTestNg015, TestSize.Level1) {
    GestureModelNG gestureModelNG;
    gestureModelNG.Create(3, 2);
    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto tapGesture = AceType::MakeRefPtr<NG::TapGesture>(COUNT, FINGER_NUMBER);
    gestureProcessor->PushGestureNG(tapGesture);

    int32_t doneId = 0;
    auto testFunc = [&doneId](GestureEvent& info) { ++doneId; };
    gestureModelNG.SetOnGestureEvent(testFunc);

    GestureEvent info;
    auto gesture = gestureProcessor->TopGestureNG();
    EXPECT_NE(gesture, nullptr);
    EXPECT_NE((gesture->onActionCancelId_), nullptr);
    (*(gesture->onActionCancelId_))(info);
    EXPECT_EQ(doneId, 1);
}

/**
 * @tc.name: GestureModelTestNg016
 * @tc.desc: test SetOnActionFunc function
 */
HWTEST_F(GestureModelTestNg, GestureModelTestNg016, TestSize.Level1) {
    GestureModelNG gestureModelNG;
    gestureModelNG.Create(3, 2);
    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto tapGesture = AceType::MakeRefPtr<NG::TapGesture>(COUNT, FINGER_NUMBER);
    gestureProcessor->PushGestureNG(tapGesture);

    int32_t doneId = 0;
    auto testFunc = [&doneId](GestureEvent& info) { ++doneId; };

    GestureEvent info;
    auto gesture = gestureProcessor->TopGestureNG();

    gestureModelNG.SetOnActionFunc(testFunc, Ace::GestureEventAction::ACTION);
    (*(gesture->onActionId_))(info);
    EXPECT_EQ(doneId, 1);

    gestureModelNG.SetOnActionFunc(testFunc, Ace::GestureEventAction::START);
    (*(gesture->onActionStartId_))(info);
    EXPECT_EQ(doneId, 2);

    gestureModelNG.SetOnActionFunc(testFunc, Ace::GestureEventAction::UPDATE);
    (*(gesture->onActionUpdateId_))(info);
    EXPECT_EQ(doneId, 3);

    gestureModelNG.SetOnActionFunc(testFunc, Ace::GestureEventAction::END);
    (*(gesture->onActionEndId_))(info);
    EXPECT_EQ(doneId, 4);

    gestureModelNG.SetOnActionFunc(testFunc, Ace::GestureEventAction::CANCEL);
    EXPECT_EQ(doneId, 4);
}

/**
 * @tc.name: GestureModelTestNg017
 * @tc.desc: test panGestureModelNG.Create function
 */
HWTEST_F(GestureModelTestNg, GestureModelTestNg017, TestSize.Level1) {
    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();

    PanGestureModelNG panGestureModelNG;
    int32_t fingersNum = DEFAULT_PAN_FINGER;
    PanDistanceMapDimension distanceMap = { { SourceTool::UNKNOWN, DEFAULT_PAN_DISTANCE } };
    PanDirection panDirection;
    panDirection.type = PanDirection::VERTICAL;
    panGestureModelNG.Create(fingersNum, panDirection, distanceMap, false);
    auto panGestureNG = AceType::DynamicCast<NG::PanGesture>(gestureProcessor->TopGestureNG());
    EXPECT_EQ(panGestureNG->distanceMap_, distanceMap);
}

/**
 * @tc.name: GestureModelTestNg018
 * @tc.desc: test Finish function
 */
HWTEST_F(GestureModelTestNg, GestureModelTestNg018, TestSize.Level1) {
    GestureModelNG gestureModelNG;
    gestureModelNG.Create(3, 2);

    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto tapGesture1 = AceType::MakeRefPtr<NG::TapGesture>(COUNT, FINGER_NUMBER);
    auto onActionStart1 = [](GestureEvent& info) { return true; };
    tapGesture1->SetOnActionId(onActionStart1);
    auto tapGesture2 = AceType::MakeRefPtr<NG::TapGesture>(1, 1);
    auto onActionStart2 = [](GestureEvent& info) { return true; };
    tapGesture2->SetOnActionId(onActionStart2);

    auto gestureGroupNG = AceType::DynamicCast<NG::GestureGroup>(gestureProcessor->TopGestureNG());
    std::vector<RefPtr<Gesture>> gestures;
    gestures.push_back(tapGesture2);
    gestures.push_back(tapGesture1);
    GestureGroup gestureGroup = GestureGroup(GestureMode::Sequence);
    gestureGroup.gestures_ = gestures;
    gestureProcessor->PushGestureNG(tapGesture1);

    const int nodeId = 10008;
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::LOCATION_BUTTON_ETS_TAG, nodeId, nullptr);
    NG::ViewStackProcessor::GetInstance()->Push(frameNode);
    RefPtr<GestureEventHub> gestureEventHub;
    gestureEventHub = NG::ViewStackProcessor::GetInstance()->GetMainFrameNodeGestureEventHub();
    auto focusHub = NG::ViewStackProcessor::GetInstance()->GetOrCreateMainFrameNodeFocusHub();

    gestureModelNG.Finish();
    EXPECT_NE(gestureEventHub, nullptr);
    EXPECT_NE(focusHub, nullptr);
    EXPECT_FALSE(gestureEventHub->IsGestureEmpty());
    EXPECT_NE(focusHub->GetOnClickCallback(), nullptr);
}

/**
 * @tc.name: GestureModelTestNg019
 * @tc.desc: test Finish function
 */
HWTEST_F(GestureModelTestNg, GestureModelTestNg019, TestSize.Level1) {
    GestureModelNG gestureModelNG;
    gestureModelNG.Create(3, 2);

    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto tapGesture1 = AceType::MakeRefPtr<NG::TapGesture>(COUNT, FINGER_NUMBER);
    auto onActionStart = [](GestureEvent& info) { return true; };
    tapGesture1->SetOnActionId(onActionStart);
    auto tapGesture2 = AceType::MakeRefPtr<NG::TapGesture>(1, 1);
    tapGesture2->SetOnActionId(nullptr);

    auto gestureGroupNG = AceType::DynamicCast<NG::GestureGroup>(gestureProcessor->TopGestureNG());
    std::vector<RefPtr<Gesture>> gestures;
    gestures.push_back(tapGesture2);
    gestures.push_back(tapGesture1);
    GestureGroup gestureGroup = GestureGroup(GestureMode::Sequence);
    gestureGroup.gestures_ = gestures;
    gestureProcessor->PushGestureNG(tapGesture1);

    const int nodeId = 10008;
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::LOCATION_BUTTON_ETS_TAG, nodeId, nullptr);
    NG::ViewStackProcessor::GetInstance()->Push(frameNode);
    RefPtr<GestureEventHub> gestureEventHub;
    gestureEventHub = NG::ViewStackProcessor::GetInstance()->GetMainFrameNodeGestureEventHub();
    auto focusHub = NG::ViewStackProcessor::GetInstance()->GetOrCreateMainFrameNodeFocusHub();

    gestureModelNG.Finish();
    EXPECT_NE(gestureEventHub, nullptr);
    EXPECT_NE(focusHub, nullptr);
    EXPECT_FALSE(gestureEventHub->IsGestureEmpty());
    EXPECT_NE(focusHub->GetOnClickCallback(), nullptr);
}
} // namespace OHOS::Ace::NG