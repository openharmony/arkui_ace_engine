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

#include "gtest/gtest.h"

#include "base/geometry/axis.h"
#include "base/geometry/ng/offset_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/event/pan_event.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/gestures/gesture_info.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
bool OHOS::Ace::SystemProperties::GetDebugEnabled()
{
    return false;
}
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
namespace {
const std::string NODE_TAG("node");
const OffsetF COORDINATE_OFFSET(20.0f, 20.0f);
constexpr int32_t TOUCH_ID = 0;
const Axis AXIS_VERTICAL = Axis::VERTICAL;
const PanDirection PAN_DIRECTION_ALL;
constexpr int32_t FINGERS = 1;
constexpr float DISTANCE = 10.0;
} // namespace

class GestureEventHubTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
};

void GestureEventHubTestNg::SetUpTestSuite()
{
    GTEST_LOG_(INFO) << "GestureEventHubTestNg SetUpTestCase";
}

void GestureEventHubTestNg::TearDownTestSuite()
{
    GTEST_LOG_(INFO) << "GestureEventHubTestNg TearDownTestCase";
}

void GestureEventHubTestNg::SetUp()
{
    GTEST_LOG_(INFO) << "GestureEventHubTestNg SetUp";
}

void GestureEventHubTestNg::TearDown()
{
    GTEST_LOG_(INFO) << "GestureEventHubTestNg TearDown";
}

/**
 * @tc.name: GestureEventHubTest001
 * @tc.desc: Create GestureEventHub and call GetFrameNode
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, GestureEventHubTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: eventHub is not null.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_TRUE(eventHub);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    EXPECT_TRUE(gestureEventHub);

    /**
     * @tc.steps: step2. Test GetFrameNode
     *            case: eventHub is valid
     * @tc.expected: frameNodeOfEvent is not null.
     */
    auto frameNodeOfEvent = gestureEventHub->GetFrameNode();
    EXPECT_TRUE(frameNodeOfEvent);

    /**
     * @tc.steps: step2. Test GetFrameNode
     *            case: eventHub is invalid
     * @tc.expected: frameNodeOfEvent is null.
     */
    eventHub = nullptr;
    frameNode = nullptr;
    frameNodeOfEvent = gestureEventHub->GetFrameNode();
    EXPECT_FALSE(frameNodeOfEvent);
}

/**
 * @tc.name: GestureEventHubTest002
 * @tc.desc: Create GestureEventHub.
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, GestureEventHubTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_TRUE(eventHub);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    EXPECT_TRUE(gestureEventHub);

    /**
     * @tc.steps: step2. Test ProcessTouchTestHit
     *            case: eventHub is null && actuators such as scrollableActuator_ & touchEventActuator_ are all null
     * @tc.expected: ProcessTouchTestHit return false,  innerTargets & finalResult is empty
     */
    TouchRestrict touchRestrict;
    TouchTestResult innerTargets;
    TouchTestResult finalResult;
    auto flag =
        gestureEventHub->ProcessTouchTestHit(COORDINATE_OFFSET, touchRestrict, innerTargets, finalResult, TOUCH_ID);
    EXPECT_FALSE(flag);
    auto sizeOfInnerTargets = static_cast<int32_t>(innerTargets.size());
    auto sizeOfFinalResult = static_cast<int32_t>(finalResult.size());
    EXPECT_EQ(sizeOfInnerTargets, 0);
    EXPECT_EQ(sizeOfFinalResult, 0);

    /**
     * @tc.steps: step3. construct actuators such as scrollableActuator_ & touchEventActuator_
     *                   then set them to gestureEventHub
     */

    // set scrollableActuator_
    auto scrollableEvent = AceType::MakeRefPtr<ScrollableEvent>(AXIS_VERTICAL);
    gestureEventHub->AddScrollableEvent(scrollableEvent);

    // set touchEventActuator_
    auto touchCallback = [](TouchEventInfo& info) {};
    auto touchEvent = AceType::MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    gestureEventHub->AddTouchEvent(touchEvent);

    // set clickEventActuator_
    auto clickCallback = [](GestureEvent& info) {};
    auto clickEvent = AceType::MakeRefPtr<ClickEvent>(std::move(clickCallback));
    gestureEventHub->AddClickEvent(clickEvent);

    // set panEventActuator_
    auto panActionStart = [](GestureEvent& info) {};
    auto panActionUpdate = [](GestureEvent& info) {};
    auto panActionEnd = [](GestureEvent& info) {};
    auto panActionCancel = []() {};
    auto panEvent = AceType::MakeRefPtr<PanEvent>(
        std::move(panActionStart), std::move(panActionUpdate), std::move(panActionEnd), std::move(panActionCancel));
    gestureEventHub->AddPanEvent(panEvent, PAN_DIRECTION_ALL, FINGERS, DISTANCE);

    // set longPressEventActuator_
    auto longPressCallback = [](GestureEvent& info) {};
    auto longPressEvent = AceType::MakeRefPtr<LongPressEvent>(longPressCallback);
    gestureEventHub->SetLongPressEvent(longPressEvent);

    // set dragEventActuator_
    auto dragActionStart = [](GestureEvent& info) {};
    auto dragActionUpdate = [](GestureEvent& info) {};
    auto dragActionEnd = [](GestureEvent& info) {};
    auto dragActionCancel = []() {};
    auto dragEvent = AceType::MakeRefPtr<DragEvent>(
        std::move(dragActionStart), std::move(dragActionUpdate), std::move(dragActionEnd), std::move(dragActionCancel));
    // const RefPtr<DragEvent>& dragEvent, PanDirection direction, int32_t fingers, float distance
    gestureEventHub->SetCustomDragEvent(dragEvent, PAN_DIRECTION_ALL, FINGERS, DISTANCE);

    /**
     * @tc.steps: step4. Test ProcessTouchTestHit
     *            case: eventHub is not null && actuators such as scrollableActuator_ & touchEventActuator_ are all not
     * null
     * @tc.expected: ProcessTouchTestHit return false,  innerTargets & finalResult is not empty
     */
    flag = gestureEventHub->ProcessTouchTestHit(COORDINATE_OFFSET, touchRestrict, innerTargets, finalResult, TOUCH_ID);
    EXPECT_FALSE(flag);
    sizeOfInnerTargets = static_cast<int32_t>(innerTargets.size());
    sizeOfFinalResult = static_cast<int32_t>(finalResult.size());
    EXPECT_GT(sizeOfInnerTargets, 0);
    EXPECT_GT(sizeOfFinalResult, 0);
}
} // namespace OHOS::Ace::NG
