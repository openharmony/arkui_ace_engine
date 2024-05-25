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
class TapGestureTestNg : public GesturesCommonTestNg {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void TapGestureTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void TapGestureTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: TapGestureTest001
 * @tc.desc: Test TapGesture CreateRecognizer function
 */
HWTEST_F(TapGestureTestNg, TapGestureTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create TapGestureGesture.
     */
    TapGestureModelNG tapGestureModelNG;
    tapGestureModelNG.Create(COUNT, FINGER_NUMBER);

    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto tapGestureNG = AceType::DynamicCast<NG::TapGesture>(gestureProcessor->TopGestureNG());
    EXPECT_EQ(tapGestureNG->count_, COUNT);

    TapGesture tapGesture = TapGesture(COUNT, FINGER_NUMBER);
    EXPECT_EQ(tapGesture.count_, COUNT);
    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case1: not have onActionId
     */
    tapGesture.priority_ = GesturePriority::Low;
    tapGesture.gestureMask_ = GestureMask::Normal;
    auto tapRecognizer = AceType::DynamicCast<ClickRecognizer>(tapGesture.CreateRecognizer());
    EXPECT_NE(tapRecognizer, nullptr);
    EXPECT_EQ(tapRecognizer->GetPriority(), GesturePriority::Low);
    EXPECT_EQ(tapRecognizer->GetPriorityMask(), GestureMask::Normal);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case2: have onActionId
     */
    std::unique_ptr<GestureEventFunc> onActionId;
    tapGesture.onActionId_ = std::move(onActionId);
    tapRecognizer = AceType::DynamicCast<ClickRecognizer>(tapGesture.CreateRecognizer());
    EXPECT_EQ(tapRecognizer->GetPriority(), GesturePriority::Low);
    EXPECT_EQ(tapRecognizer->GetPriorityMask(), GestureMask::Normal);
}

/**
 * @tc.name: TapGestureTest002
 * @tc.desc: Test TapGesture CreateRecognizer function
 */
HWTEST_F(TapGestureTestNg, TapGestureTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create TapGestureGesture.
     */
    TapGestureModelNG tapGestureModelNG;
    tapGestureModelNG.Create(COUNT, FINGER_NUMBER);

    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    auto tapGestureNG = AceType::DynamicCast<NG::TapGesture>(gestureProcessor->TopGestureNG());
    EXPECT_EQ(tapGestureNG->count_, COUNT);

    TapGesture tapGesture = TapGesture(COUNT, FINGER_NUMBER);
    EXPECT_EQ(tapGesture.count_, COUNT);
    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case1: not have onActionId
     */
    tapGesture.priority_ = GesturePriority::Low;
    tapGesture.gestureMask_ = GestureMask::Normal;
    auto onActionStart = [](GestureEvent& info) { return true; };
    tapGesture.SetOnActionId(onActionStart);
    auto tapRecognizer = AceType::DynamicCast<ClickRecognizer>(tapGesture.CreateRecognizer());
    EXPECT_NE(tapRecognizer, nullptr);
    EXPECT_EQ(tapRecognizer->GetPriority(), GesturePriority::Low);
    EXPECT_EQ(tapRecognizer->GetPriorityMask(), GestureMask::Normal);

    /**
     * @tc.steps: step2. call CreateRecognizer function and compare result
     * @tc.steps: case2: have onActionId
     */
    std::unique_ptr<GestureEventFunc> onActionId;
    tapGesture.onActionId_ = std::move(onActionId);
    tapRecognizer = AceType::DynamicCast<ClickRecognizer>(tapGesture.CreateRecognizer());
    EXPECT_EQ(tapRecognizer->GetPriority(), GesturePriority::Low);
    EXPECT_EQ(tapRecognizer->GetPriorityMask(), GestureMask::Normal);
}

/**
 * @tc.name: GestureTest001
 * @tc.desc: Test TapGesture CreateRecognizer function
 */
HWTEST_F(TapGestureTestNg, GestureTest001, TestSize.Level1)
{
    GestureModelNG gestureModelNG;
    gestureModelNG.Create(0, 0);
    gestureModelNG.Finish();
    gestureModelNG.Pop();

    RefPtr<GestureProcessor> gestureProcessor;
    gestureProcessor = NG::ViewStackProcessor::GetInstance()->GetOrCreateGestureProcessor();
    EXPECT_EQ(gestureProcessor->priority_, GesturePriority::Low);
    EXPECT_EQ(gestureProcessor->gestureMask_, GestureMask::Normal);

    PanGestureModelNG panGestureModelNG;
    int32_t fingersNum = DEFAULT_PAN_FINGER;
    double distanceNum = DEFAULT_PAN_DISTANCE.ConvertToPx();
    PanDirection panDirection;
    panGestureModelNG.Create(fingersNum, panDirection, distanceNum);
    auto panGestureNG = AceType::DynamicCast<NG::PanGesture>(gestureProcessor->TopGestureNG());
    EXPECT_EQ(panGestureNG->distance_, distanceNum);

    RefPtr<PanGestureOption> refPanGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    panGestureModelNG.SetPanGestureOption(refPanGestureOption);

    TimeoutGestureModelNG timeoutGestureModelNG;
    timeoutGestureModelNG.GetGestureProcessor();

    SwipeGestureModelNG swipeGestureModelNG;
    fingersNum = DEFAULT_SLIDE_FINGER;
    double speedNum = DEFAULT_SLIDE_SPEED;
    SwipeDirection slideDirection;
    swipeGestureModelNG.Create(fingersNum, slideDirection, speedNum);
    auto swipeGestureNG = AceType::DynamicCast<NG::SwipeGesture>(gestureProcessor->TopGestureNG());
    EXPECT_EQ(swipeGestureNG->speed_, speedNum);
}
} // namespace OHOS::Ace::NG