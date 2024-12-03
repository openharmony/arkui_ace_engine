/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include <clocale>
#include <cmath>
#include <cstdint>
#include <unistd.h>

#include "gtest/gtest.h"

#include "base/geometry/ng/offset_t.h"
#include "base/memory/ace_type.h"
#define private public
#define protected public
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/scrollable_event.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr double GESTURE_EVENT_PROPERTY_DEFAULT_VALUE = 0.0;
constexpr double GESTURE_EVENT_PROPERTY_VALUE = 10.0;
constexpr uint32_t PAN_EVENT_TEST_RESULT_SIZE_1 = 2;
constexpr uint32_t PAN_EVENT_TEST_RESULT_SIZE = 0;
const TouchRestrict PAN_EVENT_RESTRICT = { TouchRestrict::LONG_PRESS };
constexpr float WIDTH = 400.0f;
constexpr float HEIGHT = 400.0f;
const OffsetF COORDINATE_OFFSET(WIDTH, HEIGHT);
const PanDirection PAN_EVENT_DIRECTION = { PanDirection::LEFT };
constexpr int32_t FINGERS_NUMBER = 0;
constexpr int32_t FINGERS_NUMBER_GREATER_THAN_DEFAULT = 2;
constexpr float DISTANCE = 3.0f;
constexpr float DISTANCE_GREATER_THAN_DEFAULT = 6.0f;
constexpr int32_t DEFAULT_PAN_FINGER = 1;
} // namespace

class PanEventTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
};

void PanEventTestNg::SetUpTestSuite()
{
    GTEST_LOG_(INFO) << "PanEventTestNg SetUpTestCase";
}

void PanEventTestNg::TearDownTestSuite()
{
    GTEST_LOG_(INFO) << "PanEventTestNg TearDownTestCase";
}

void PanEventTestNg::SetUp()
{
    MockPipelineContext::SetUp();
}

void PanEventTestNg::TearDown()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: PanEventOnCollectTouchTargetTest001
 * @tc.desc: Create PanEvent.
 * @tc.type: FUNC
 */
HWTEST_F(PanEventTestNg, PanEventOnCollectTouchTargetTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DragEventActuator when fingers number and distance are both less than the default.
     * @tc.expected: panEventActuator is initialized with the fingers_ and distance_ has been assigned with the default
     * value.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto panEventActuator = AceType::MakeRefPtr<PanEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), PAN_EVENT_DIRECTION, FINGERS_NUMBER, DISTANCE);
    EXPECT_NE(panEventActuator, nullptr);
    EXPECT_EQ(panEventActuator->fingers_, DEFAULT_PAN_FINGER);
    EXPECT_EQ(panEventActuator->distance_, DISTANCE);

    /**
     * @tc.steps: step2. Create DragEventActuator when fingers number and distance are both greater than the default.
     * @tc.expected: panEventActuator is initialized with the fingers_ and distance_ defined before.
     */
    auto panEventActuator2 = AceType::MakeRefPtr<PanEventActuator>(AceType::WeakClaim(AceType::RawPtr(gestureEventHub)),
        PAN_EVENT_DIRECTION, FINGERS_NUMBER_GREATER_THAN_DEFAULT, DISTANCE_GREATER_THAN_DEFAULT);
    EXPECT_NE(panEventActuator2, nullptr);
    EXPECT_EQ(panEventActuator2->fingers_, FINGERS_NUMBER_GREATER_THAN_DEFAULT);
    EXPECT_EQ(panEventActuator2->distance_, DISTANCE_GREATER_THAN_DEFAULT);
}

/**
 * @tc.name: PanEventOnCollectTouchTargetTest002
 * @tc.desc: Create PanEvent and invoke OnCollectTouchTarget.
 * @tc.type: FUNC
 */
HWTEST_F(PanEventTestNg, PanEventOnCollectTouchTargetTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create DragEventActuator.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    auto panEventActuator = AceType::MakeRefPtr<PanEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(gestureEventHub)), PAN_EVENT_DIRECTION, FINGERS_NUMBER, DISTANCE);
    EXPECT_NE(panEventActuator, nullptr);

    /**
     * @tc.steps: step2. Invoke OnCollectTouchTarget when panEvents_ and userCallback_ are both empty.
     * @tc.expected: OnCollectTouchTarget function will return directly and result size is 0.
     */
    TouchTestResult result;
    ResponseLinkResult responseLinkResult;
    panEventActuator->OnCollectTouchTarget(
        COORDINATE_OFFSET, PAN_EVENT_RESTRICT, eventHub->CreateGetEventTargetImpl(), result, responseLinkResult);
    EXPECT_EQ(result.size(), PAN_EVENT_TEST_RESULT_SIZE);

    /**
     * @tc.steps: step3. ReplacePanEvent to initialize userCallback_ and AddPanEvent to add panEvent into panEvents_.
     * @tc.expected: userCallback_ is not nullptr and panEvents_ is not empty.
     */
    double unknownPropertyValue = GESTURE_EVENT_PROPERTY_DEFAULT_VALUE;
    GestureEventFunc actionStart = [&unknownPropertyValue](
                                       GestureEvent& info) { unknownPropertyValue = info.GetScale(); };
    GestureEventFunc actionUpdate = [&unknownPropertyValue](
                                        GestureEvent& info) { unknownPropertyValue = info.GetScale(); };
    GestureEventFunc actionEnd = [&unknownPropertyValue](
                                     GestureEvent& info) { unknownPropertyValue = info.GetScale(); };
    GestureEventNoParameter actionCancel = [&unknownPropertyValue]() {
        unknownPropertyValue = GESTURE_EVENT_PROPERTY_VALUE;
    };

    auto panEvent = AceType::MakeRefPtr<PanEvent>(
        std::move(actionStart), std::move(actionUpdate), std::move(actionEnd), std::move(actionCancel));
    EXPECT_NE(panEvent, nullptr);
    panEventActuator->AddPanEvent(panEvent);
    auto panEventNullptr = AceType::MakeRefPtr<PanEvent>(nullptr, nullptr, nullptr, nullptr);
    panEventActuator->AddPanEvent(panEventNullptr);
    EXPECT_FALSE(panEventActuator->panEvents_.empty());
    panEventActuator->OnCollectTouchTarget(
        COORDINATE_OFFSET, PAN_EVENT_RESTRICT, eventHub->CreateGetEventTargetImpl(), result, responseLinkResult);
    panEventActuator->ReplacePanEvent(panEvent);
    EXPECT_NE(panEventActuator->userCallback_, nullptr);

    /**
     * @tc.steps: step4. Invoke OnCollectTouchTarget when panEvents_ and userCallback_ are not empty
     * @tc.expected: result size was increased by one.
     */
    panEventActuator->OnCollectTouchTarget(
        COORDINATE_OFFSET, PAN_EVENT_RESTRICT, eventHub->CreateGetEventTargetImpl(), result, responseLinkResult);

    EXPECT_NE(panEventActuator->panRecognizer_->onActionStart_, nullptr);
    EXPECT_NE(panEventActuator->panRecognizer_->onActionUpdate_, nullptr);
    EXPECT_NE(panEventActuator->panRecognizer_->onActionEnd_, nullptr);
    EXPECT_NE(panEventActuator->panRecognizer_->getEventTargetImpl_, nullptr);
    EXPECT_EQ(panEventActuator->panRecognizer_->GetCoordinateOffset(), Offset(WIDTH, HEIGHT));
    EXPECT_EQ(result.size(), PAN_EVENT_TEST_RESULT_SIZE_1);

    /**
     * @tc.steps: step5. Invoke onActionStart, onActionUpdate, onActionEnd, onActionCancel when the onActionStart
     * function exists.
     * @tc.expected: The functions have been executed and the unknownPropertyValue has been assigned the correct
     * value.
     */
    GestureEvent info = GestureEvent();
    info.SetScale(GESTURE_EVENT_PROPERTY_VALUE);
    (*(panEventActuator->panRecognizer_->onActionStart_))(info);
    EXPECT_EQ(unknownPropertyValue, GESTURE_EVENT_PROPERTY_VALUE);
    (*(panEventActuator->panRecognizer_->onActionUpdate_))(info);
    EXPECT_EQ(unknownPropertyValue, GESTURE_EVENT_PROPERTY_VALUE);
    (*(panEventActuator->panRecognizer_->onActionEnd_))(info);
    EXPECT_EQ(unknownPropertyValue, GESTURE_EVENT_PROPERTY_VALUE);
    (*(panEventActuator->panRecognizer_->onActionCancel_))();
    EXPECT_EQ(unknownPropertyValue, GESTURE_EVENT_PROPERTY_VALUE);

    /**
     * @tc.steps: step6. Invoke onActionStart, onActionUpdate, onActionEnd, onActionCancel when the onActionStart
     * function not exist.
     * @tc.expected: The functions have not been executed.
     */
    panEventActuator->ReplacePanEvent(panEventNullptr);
    panEventActuator->RemovePanEvent(panEvent);
    unknownPropertyValue = 0.0;
    (*(panEventActuator->panRecognizer_->onActionStart_))(info);
    (*(panEventActuator->panRecognizer_->onActionUpdate_))(info);
    (*(panEventActuator->panRecognizer_->onActionEnd_))(info);
    (*(panEventActuator->panRecognizer_->onActionCancel_))();
    EXPECT_EQ(unknownPropertyValue, GESTURE_EVENT_PROPERTY_DEFAULT_VALUE);
}
} // namespace OHOS::Ace::NG
