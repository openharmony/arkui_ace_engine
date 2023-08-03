/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#define private public

#include "base/geometry/axis.h"
#include "base/geometry/ng/offset_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/test/mock/mock_drag_window.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/event/pan_event.h"
#include "core/components_ng/event/touch_event.h"
#include "core/components_ng/gestures/long_press_gesture.h"
#include "core/components_ng/gestures/pan_gesture.h"
#include "core/components_ng/gestures/recognizers/click_recognizer.h"
#include "core/components_ng/gestures/tap_gesture.h"
#include "core/components_ng/manager/drag_drop/drag_drop_proxy.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/gestures/gesture_info.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

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
constexpr int32_t DOUBLE_FINGERS = 2;
constexpr int32_t CLICK_COUNTS = 2;
constexpr Dimension DISTANCE = 10.0_vp;
const std::string CHECK_TAG_1("HELLO");
const std::string CHECK_TAG_2("WORLD");
const PointF GLOBAL_POINT { 20.0f, 20.0f };
const PointF LOCAL_POINT { 15.0f, 15.0f };
RefPtr<DragWindow> MOCK_DRAG_WINDOW;
constexpr int32_t GESTURES_COUNTS = 2;
} // namespace

class GestureEventHubTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void GestureEventHubTestNg::SetUpTestSuite()
{
    MockPipelineBase::SetUp();
    MOCK_DRAG_WINDOW = DragWindow::CreateDragWindow("", 0, 0, 0, 0);
    GTEST_LOG_(INFO) << "GestureEventHubTestNg SetUpTestCase";
}

void GestureEventHubTestNg::TearDownTestSuite()
{
    MockPipelineBase::TearDown();
    MOCK_DRAG_WINDOW = nullptr;
    GTEST_LOG_(INFO) << "GestureEventHubTestNg TearDownTestCase";
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
 * @tc.desc: Test ProcessTouchTestHit part1
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
    eventHub = nullptr;
    TouchRestrict touchRestrict;
    TouchTestResult innerTargets;
    TouchTestResult finalResult;
    auto flag = gestureEventHub->ProcessTouchTestHit(
        COORDINATE_OFFSET, touchRestrict, innerTargets, finalResult, TOUCH_ID, PointF());
    EXPECT_FALSE(flag);
    auto sizeOfInnerTargets = static_cast<int32_t>(innerTargets.size());
    auto sizeOfFinalResult = static_cast<int32_t>(finalResult.size());
    EXPECT_EQ(sizeOfInnerTargets, 0);
    EXPECT_EQ(sizeOfFinalResult, 0);

    /**
     * @tc.steps: step3. construct touchEventActuator_
     *                   then set it to gestureEventHub
     */
    // reconstruct a gestureEventHub
    eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_TRUE(eventHub);
    gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    EXPECT_TRUE(gestureEventHub);
    // set touchEventActuator_
    auto touchCallback = [](TouchEventInfo& info) {};
    auto touchEvent = AceType::MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    gestureEventHub->AddTouchEvent(touchEvent);

    /**
     * @tc.steps: step4. Test ProcessTouchTestHit
     *            case: eventHub is not null && touchEventActuator_ is not null
     * @tc.expected: ProcessTouchTestHit return false,  innerTargets & finalResult have one element
     */
    flag = gestureEventHub->ProcessTouchTestHit(
        COORDINATE_OFFSET, touchRestrict, innerTargets, finalResult, TOUCH_ID, PointF());
    EXPECT_FALSE(flag);
    sizeOfInnerTargets = static_cast<int32_t>(innerTargets.size());
    sizeOfFinalResult = static_cast<int32_t>(finalResult.size());
    EXPECT_EQ(sizeOfInnerTargets, 1);
    EXPECT_EQ(sizeOfFinalResult, 1);
}

/**
 * @tc.name: GestureEventHubTest003
 * @tc.desc: Test ProcessTouchTestHit part2
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, GestureEventHubTest003, TestSize.Level1)
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
     * @tc.steps: step2. construct scrollableActuator_ and other actuators
     *                   then set them to gestureEventHub
     */

    // set touchEventActuator_
    auto touchCallback = [](TouchEventInfo& info) {};
    auto touchEvent = AceType::MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    gestureEventHub->AddTouchEvent(touchEvent);

    // set scrollableActuator_
    auto scrollableEvent = AceType::MakeRefPtr<ScrollableEvent>(AXIS_VERTICAL);
    gestureEventHub->AddScrollableEvent(scrollableEvent);

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
    gestureEventHub->SetCustomDragEvent(dragEvent, PAN_DIRECTION_ALL, FINGERS, DISTANCE);

    /**
     * @tc.steps: step3. Test ProcessTouchTestHit
     *            case: eventHub is not null && all Actuator_ is not null
     * @tc.expected: ProcessTouchTestHit return false,  innerTargets & finalResult have 2 elements
     *               there are 3 TouchEventTarget has created by touchEventActuator_, longPressEventActuator_ &
     *               dragEventActuator_
     *               innerTargets contains a touchEventActuator & a parallelRecognizer
     *               finalResult containers a longPressRecognizer & a currentRecognizer(in ProcessTouchTestHierarchy)
     */
    TouchRestrict touchRestrict;
    TouchTestResult innerTargets;
    TouchTestResult finalResult;
    auto flag = gestureEventHub->ProcessTouchTestHit(
        COORDINATE_OFFSET, touchRestrict, innerTargets, finalResult, TOUCH_ID, PointF());
    EXPECT_FALSE(flag);
    auto sizeOfInnerTargets = static_cast<int32_t>(innerTargets.size());
    auto sizeOfFinalResult = static_cast<int32_t>(finalResult.size());
    EXPECT_EQ(sizeOfInnerTargets, 2);
    EXPECT_EQ(sizeOfFinalResult, 2);

    /**
     * @tc.steps: step4. call ProcessTouchTestHit again
     *            case: nodeParallelRecognizer_  & externalParallelRecognizer_ is existed
     * @tc.expected: ProcessTouchTestHit return false,  innerTargets 4 elements & finalResult have 5 elements
     */
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    flag = gestureEventHub->ProcessTouchTestHit(
        COORDINATE_OFFSET, touchRestrict, innerTargets, finalResult, TOUCH_ID, PointF());
    EXPECT_FALSE(flag);
    sizeOfInnerTargets = static_cast<int32_t>(innerTargets.size());
    sizeOfFinalResult = static_cast<int32_t>(finalResult.size());
    EXPECT_EQ(sizeOfInnerTargets, 4);
    EXPECT_EQ(sizeOfFinalResult, 5);
}

/**
 * @tc.name: GestureEventHubTest004
 * @tc.desc: Test AddClickEvent, SetUserOnClick, ActClick & SetFocusClickEvent
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, GestureEventHubTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_TRUE(eventHub);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    EXPECT_TRUE(gestureEventHub);

    /**
     * @tc.steps: step2. call ActClick
     *            case: clickEventActuator_ is null
     * @tc.expected: flag is false
     */
    auto flag = gestureEventHub->ActClick();
    EXPECT_FALSE(flag);

    /**
     * @tc.steps: step3. call ActClick
     *            case: clickEventActuator_ is null, clickRecognizer fingers is 2, count is 1
     * @tc.expected: flag is false
     */
    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(DOUBLE_FINGERS, 1);
    gestureEventHub->gestureHierarchy_.emplace_back(clickRecognizer);
    EXPECT_FALSE(gestureEventHub->ActClick());
    gestureEventHub->gestureHierarchy_.clear();

    /**
     * @tc.steps: step4. call ActClick
     *            case: clickEventActuator_ is null, clickRecognizer fingers is 1, count is 1
     * @tc.expected: flag is true
     */
    clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(1, 1);
    clickRecognizer->SetOnAction([](GestureEvent& info) {});
    gestureEventHub->gestureHierarchy_.emplace_back(clickRecognizer);
    EXPECT_TRUE(gestureEventHub->ActClick());
    gestureEventHub->gestureHierarchy_.clear();

    /**
     * @tc.steps: step5. construct two clickCallback
     *            one is for SetUserOnClick, the other is for AddClickEvent
     */
    std::string msg1;
    auto clickCallback = [&msg1](GestureEvent& /* info */) { msg1 = CHECK_TAG_1; };
    gestureEventHub->SetUserOnClick(clickCallback);
    std::string msg2;
    auto clickCallback2 = [&msg2](GestureEvent& /* info */) { msg2 = CHECK_TAG_2; };
    auto clickEvent = AceType::MakeRefPtr<ClickEvent>(std::move(clickCallback2));
    gestureEventHub->AddClickEvent(clickEvent);

    /**
     * @tc.steps: step6. call ActClick
     *                   case: clickEventActuator_ is not null
     * @tc.expected: flag is true & clickCallback & clickCallback2 has be called
     */
    flag = gestureEventHub->ActClick();
    EXPECT_TRUE(flag);
    EXPECT_EQ(msg1, CHECK_TAG_1);
    EXPECT_EQ(msg2, CHECK_TAG_2);

    /**
     * @tc.steps: step7. call eventHub's GetOrCreateFocusHub
     * @tc.expected: return is not null
     */
    auto focusHub = eventHub->GetOrCreateFocusHub();
    EXPECT_TRUE(focusHub);

    /**
     * @tc.steps: step8. call SetFocusClickEvent
     * @tc.expected: no fatal error occur
     */
    msg1 = "";
    auto clickCallback3 = [&msg1](GestureEvent& /* info */) { msg1 = CHECK_TAG_1; };
    gestureEventHub->SetFocusClickEvent(clickCallback3);
}

/**
 * @tc.name: GestureEventHubTest005
 * @tc.desc: Test ActLongClick
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, GestureEventHubTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_TRUE(eventHub);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    EXPECT_TRUE(gestureEventHub);

    /**
     * @tc.steps: step2. call ActLongClick
     *            case: longPressEventActuator_ is null
     * @tc.expected: flag is false
     */
    auto flag = gestureEventHub->ActLongClick();
    EXPECT_FALSE(flag);

    /**
     * @tc.steps: step3. call ActLongClick
     *            case: longPressEventActuator_ is null, longPressRecognizer fingers is 2
     * @tc.expected: flag is false
     */
    auto longPressRecognizer = AceType::MakeRefPtr<LongPressRecognizer>(1, DOUBLE_FINGERS, false);
    gestureEventHub->gestureHierarchy_.emplace_back(longPressRecognizer);
    EXPECT_FALSE(gestureEventHub->ActLongClick());
    gestureEventHub->gestureHierarchy_.clear();

    /**
     * @tc.steps: step4. call ActLongClick
     *            case: longPressEventActuator_ is null, longPressRecognizer fingers is 1
     * @tc.expected: flag is true
     */
    longPressRecognizer = AceType::MakeRefPtr<LongPressRecognizer>(1, 1, false);
    longPressRecognizer->SetOnAction([](GestureEvent& info) {});
    gestureEventHub->gestureHierarchy_.emplace_back(longPressRecognizer);
    EXPECT_TRUE(gestureEventHub->ActLongClick());
    gestureEventHub->gestureHierarchy_.clear();

    /**
     * @tc.steps: step5. construct a longPressCallback
     */
    std::string msg1;
    auto longPressCallback = [&msg1](GestureEvent& /* info */) { msg1 = CHECK_TAG_1; };
    auto longPressEvent = AceType::MakeRefPtr<LongPressEvent>(longPressCallback);
    gestureEventHub->SetLongPressEvent(longPressEvent);

    /**
     * @tc.steps: step6. call ActLongClick
     *                   case: longPressEventActuator_ is not null
     * @tc.expected: flag is true & longPressCallback will be called
     */
    flag = gestureEventHub->ActLongClick();
    EXPECT_TRUE(flag);
    EXPECT_EQ(msg1, CHECK_TAG_1);

    /**
     * @tc.steps: step7. call eventHub's GetOrCreateFocusHub
     * @tc.expected: return is not null
     */
    auto focusHub = eventHub->GetOrCreateFocusHub();
    EXPECT_TRUE(focusHub);

    /**
     * @tc.steps: step8. call SetFocusClickEvent
     * @tc.expected: no fatal error occur
     */
    msg1 = "";
    auto clickCallback3 = [&msg1](GestureEvent& /* info */) { msg1 = CHECK_TAG_1; };
    gestureEventHub->SetFocusClickEvent(clickCallback3);
}

/**
 * @tc.name: GestureEventHubTest006
 * @tc.desc: Test CombineIntoExclusiveRecognizer
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, GestureEventHubTest006, TestSize.Level1)
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
     * @tc.steps: step2. call CombineIntoExclusiveRecognizer
     *            case: result is empty
     * @tc.expected: result is empty
     */
    TouchTestResult result;
    gestureEventHub->CombineIntoExclusiveRecognizer(GLOBAL_POINT, LOCAL_POINT, result, TOUCH_ID);
    auto size = static_cast<int32_t>(result.size());
    EXPECT_EQ(size, 0);

    /**
     * @tc.steps: step3. insert element to result
     * @tc.expected: result'size is 3
     */

    // new TouchEventActuator
    auto touchEventActuator = AceType::MakeRefPtr<TouchEventActuator>();

    // new LongPressRecognizer (extends NGGestureRecognizer)
    auto longPressRecognizer = AceType::MakeRefPtr<LongPressRecognizer>(false, false);

    // new ClickRecognizer (extends NGGestureRecognizer)
    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>();

    result.emplace_back(touchEventActuator);
    result.emplace_back(longPressRecognizer);
    result.emplace_back(clickRecognizer);
    size = static_cast<int32_t>(result.size());
    EXPECT_EQ(size, 3);

    /**
     * @tc.steps: step4. call CombineIntoExclusiveRecognizer
     *            case: recognizers'size > 1
     * @tc.expected: result'size is 2. One is touchEventActuator, the other is a exclusiveRecognizer created by
     *               longPressRecognizer and clickRecognizer
     */
    gestureEventHub->CombineIntoExclusiveRecognizer(GLOBAL_POINT, LOCAL_POINT, result, TOUCH_ID);
    size = static_cast<int32_t>(result.size());
    EXPECT_EQ(size, 2);

    /**
     * @tc.steps: step5. call CombineIntoExclusiveRecognizer
     *            case: recognizers'size = 1
     * @tc.expected: result2'size is 2. One is touchEventActuator, the other is longPressRecognizer
     */
    TouchTestResult result2;
    result2.emplace_back(touchEventActuator);
    result2.emplace_back(longPressRecognizer);
    gestureEventHub->CombineIntoExclusiveRecognizer(GLOBAL_POINT, LOCAL_POINT, result2, TOUCH_ID);
    size = static_cast<int32_t>(result2.size());
    EXPECT_EQ(size, 2);
}

/**
 * @tc.name: GestureEventHubTest007
 * @tc.desc: Test InitDragDropEvent
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, GestureEventHubTest007, TestSize.Level1)
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
     * @tc.steps: step2. Call InitDragDropEvent.
     * @tc.expected: dragEventActuator_ is not null.
     */
    gestureEventHub->InitDragDropEvent();
    EXPECT_TRUE(gestureEventHub->dragEventActuator_);
}

/**
 * @tc.name: GestureEventHubTest008
 * @tc.desc: Test Functions related with drag
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, GestureEventHubTest008, TestSize.Level1)
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
     * @tc.steps: step2. call HandleOnDragStart
     *            case: eventHub->HasOnDragStart() is null
     * @tc.expected: dragDropProxy_ is null.
     */
    GestureEvent info;
    gestureEventHub->HandleOnDragStart(info);
    EXPECT_FALSE(gestureEventHub->dragDropProxy_);

    /**
     * @tc.steps: step3. set OnDragStart for eventHub
     *            after that eventHub->HasOnDragStart() is not null
     *            case: dragDropInfo.customNode is not null
     */
    RefPtr<UINode> customNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto onDragStart = [&customNode](
                           const RefPtr<OHOS::Ace::DragEvent>& /* dragEvent */, const std::string& /* param */) {
        DragDropInfo dragDropInfo;
        dragDropInfo.customNode = customNode;
        return dragDropInfo;
    };
    eventHub->SetOnDragStart(std::move(onDragStart));

    /**
     * @tc.steps: step4. call HandleOnDragStart
     *            case: dragDropInfo.customNode is not null
     * @tc.expected: dragDropProxy_ is not null.
     */
    gestureEventHub->HandleOnDragStart(info);
    EXPECT_FALSE(gestureEventHub->dragDropProxy_);

    /**
     * @tc.steps: step5. set OnDragStart for eventHub2
     *            after that eventHub->HasOnDragStart() is not null
     *            case: dragDropInfo.pixelMap is not null
     */
    void* voidPtr = static_cast<void*>(new char[0]);
    RefPtr<PixelMap> pixelMap = PixelMap::CreatePixelMap(voidPtr);
    auto onDragStart2 = [&pixelMap](
                            const RefPtr<OHOS::Ace::DragEvent>& /* dragEvent */, const std::string& /* param */) {
        DragDropInfo dragDropInfo;
        dragDropInfo.pixelMap = pixelMap;
        return dragDropInfo;
    };
    auto eventHub2 = AceType::MakeRefPtr<EventHub>();
    EXPECT_TRUE(eventHub2);
    eventHub2->SetOnDragStart(std::move(onDragStart2));
    auto gestureEventHub2 = AceType::MakeRefPtr<GestureEventHub>(eventHub2);
    EXPECT_TRUE(gestureEventHub2);

    /**
     * @tc.steps: step6. call HandleOnDragStart
     *            case: dragDropInfo.pixelMap is not null
     * @tc.expected: dragDropProxy_ is not null.
     */
    gestureEventHub2->HandleOnDragStart(info);
    EXPECT_FALSE(gestureEventHub2->dragDropProxy_);

    /**
     * @tc.steps: step7. call HandleOnDragStart again
     *            case: dragDropProxy_ need to reset
     * @tc.expected: dragDropProxy_ is not null.
     */
    gestureEventHub2->HandleOnDragStart(info);
    EXPECT_FALSE(gestureEventHub2->dragDropProxy_);

    /**
     * @tc.steps: step8. call HandleOnDragUpdate
     * @tc.expected: dragDropProxy_ is not null.
     */
    gestureEventHub2->HandleOnDragUpdate(info);
    EXPECT_FALSE(gestureEventHub2->dragDropProxy_);

    /**
     * @tc.steps: step9. call HandleOnDragCancel
     * @tc.expected: dragDropProxy_ is null.
     */
    gestureEventHub2->HandleOnDragCancel();
    EXPECT_FALSE(gestureEventHub2->dragDropProxy_);

    /**
     * @tc.steps: step10. call HandleOnDragEnd
     *            case: eventHub->HasOnDrop() is false
     * @tc.expected: dragDropProxy_ is null.
     */
    gestureEventHub->HandleOnDragEnd(info);
    EXPECT_FALSE(gestureEventHub->dragDropProxy_);

    /**
     * @tc.steps: step10. call HandleOnDragEnd
     *            case: eventHub->HasOnDrop() is true
     * @tc.expected: dragDropProxy_ is null
     *               onDrop has been called, msg1 = CHECK_TAG_1
     */
    std::string msg1;
    auto onDrop = [&msg1](const RefPtr<OHOS::Ace::DragEvent>& /* dragEvent */, const std::string& /* param */) {
        msg1 = CHECK_TAG_1;
    };
    eventHub->SetOnDrop(std::move(onDrop));
    gestureEventHub->HandleOnDragStart(info);
    gestureEventHub->HandleOnDragEnd(info);
    EXPECT_FALSE(gestureEventHub->dragDropProxy_);
    EXPECT_EQ(msg1, CHECK_TAG_1);
}

/**
 * @tc.name: GestureEventHubTest009
 * @tc.desc: Test ModifyDone & UpdateGestureHierarchy
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, GestureEventHubTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_TRUE(eventHub);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    EXPECT_TRUE(gestureEventHub);

    /**
     * @tc.steps: step2. call OnModifyDone
     *            case: recreateGesture_ is true & gestures_.size() == gestureHierarchy_.size() == 0
     * @tc.expected: recreateGesture_ = false
     */
    gestureEventHub->OnModifyDone();
    EXPECT_FALSE(gestureEventHub->recreateGesture_);

    /**
     * @tc.steps: step3. call OnModifyDone
     *            case: recreateGesture_ is false
     * @tc.expected: recreateGesture_ = false
     */
    gestureEventHub->OnModifyDone();
    EXPECT_FALSE(gestureEventHub->recreateGesture_);

    /**
     * @tc.steps: step4. call OnModifyDone
     *            case: recreateGesture_ is true & gestures_.size() != gestureHierarchy_.size()
     * @tc.expected: recreateGesture_ = false
     *               gestures_ has cleared & gestureHierarchy_ has one element
     */
    gestureEventHub->recreateGesture_ = true;
    auto longPressGesture = AceType::MakeRefPtr<LongPressGesture>(FINGERS, false, 1);
    gestureEventHub->gestures_.emplace_back(longPressGesture);
    gestureEventHub->OnModifyDone();
    EXPECT_FALSE(gestureEventHub->recreateGesture_);
    auto sizeGestures = static_cast<int32_t>(gestureEventHub->gestures_.size());
    auto sizeGestureHierarchy = static_cast<int32_t>(gestureEventHub->gestureHierarchy_.size());
    EXPECT_EQ(sizeGestures, 0);
    EXPECT_EQ(sizeGestureHierarchy, 1);
}

/**
 * @tc.name: GestureEventHubTest010
 * @tc.desc: Test ProcessTouchTestHierarchy
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, GestureEventHubTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_TRUE(eventHub);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    EXPECT_TRUE(gestureEventHub);

    /**
     * @tc.steps: step2. call ProcessTouchTestHierarchy
     *            case: innerRecognizers & gestureHierarchy_ is empty, current is null
     * @tc.expected: finalResult is empty
     */
    TouchRestrict touchRestrict;
    std::list<RefPtr<NGGestureRecognizer>> innerTargets;
    TouchTestResult finalResult;

    gestureEventHub->externalExclusiveRecognizer_.push_back(nullptr);
    gestureEventHub->externalParallelRecognizer_.push_back(nullptr);
    EXPECT_EQ(static_cast<int32_t>(gestureEventHub->externalExclusiveRecognizer_.size()), 1);
    EXPECT_EQ(static_cast<int32_t>(gestureEventHub->externalParallelRecognizer_.size()), 1);

    gestureEventHub->ProcessTouchTestHierarchy(COORDINATE_OFFSET, touchRestrict, innerTargets, finalResult, TOUCH_ID);
    EXPECT_TRUE(finalResult.empty());

    /**
     * @tc.steps: step3. call ProcessTouchTestHierarchy several
     *            case: innerRecognizers & gestureHierarchy_ is not all empty
     * @tc.expected: finalResult's size has increased by 1 per call
     */
    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(FINGERS, 1); // priority == GesturePriority::Low
    innerTargets.emplace_back(clickRecognizer);

    gestureEventHub->gestureHierarchy_.emplace_back(nullptr);
    auto clickRecognizer2 = AceType::MakeRefPtr<ClickRecognizer>(FINGERS, 1);
    clickRecognizer2->SetPriorityMask(GestureMask::IgnoreInternal);           // current will assigned to this
    auto clickRecognizer3 = AceType::MakeRefPtr<ClickRecognizer>(FINGERS, 1); // priority == GesturePriority::High
    clickRecognizer3->SetPriority(GesturePriority::High);
    auto clickRecognizer4 = AceType::MakeRefPtr<ClickRecognizer>(FINGERS, 1); // priority == GesturePriority::Parallel
    clickRecognizer4->SetPriority(GesturePriority::Parallel);
    auto clickRecognizer5 = AceType::MakeRefPtr<ClickRecognizer>(FINGERS, 1); // priority == GesturePriority::Parallel
    clickRecognizer5->SetPriority(GesturePriority::Parallel);

    gestureEventHub->gestureHierarchy_.emplace_back(clickRecognizer);
    gestureEventHub->gestureHierarchy_.emplace_back(clickRecognizer4);
    gestureEventHub->gestureHierarchy_.emplace_back(clickRecognizer2);
    gestureEventHub->gestureHierarchy_.emplace_back(clickRecognizer3);
    gestureEventHub->gestureHierarchy_.emplace_back(clickRecognizer5);

    gestureEventHub->ProcessTouchTestHierarchy(COORDINATE_OFFSET, touchRestrict, innerTargets, finalResult, TOUCH_ID);
    auto sizeOfFinalResult = static_cast<int32_t>(finalResult.size());
    EXPECT_EQ(sizeOfFinalResult, 1);

    auto clickRecognizer6 = AceType::MakeRefPtr<ClickRecognizer>(FINGERS, 1); // priority == GesturePriority::Low
    std::list<RefPtr<NGGestureRecognizer>> innerTargets2;
    innerTargets2.emplace_back(clickRecognizer);
    innerTargets2.emplace_back(clickRecognizer6);
    gestureEventHub->ProcessTouchTestHierarchy(COORDINATE_OFFSET, touchRestrict, innerTargets2, finalResult, TOUCH_ID);
    sizeOfFinalResult = static_cast<int32_t>(finalResult.size());
    EXPECT_EQ(sizeOfFinalResult, 2);

    std::list<RefPtr<NGGestureRecognizer>> innerTargets3;
    innerTargets3.emplace_back(clickRecognizer);
    innerTargets3.emplace_back(clickRecognizer6);
    gestureEventHub->ProcessTouchTestHierarchy(COORDINATE_OFFSET, touchRestrict, innerTargets3, finalResult, TOUCH_ID);
    sizeOfFinalResult = static_cast<int32_t>(finalResult.size());
    EXPECT_EQ(sizeOfFinalResult, 3);

    std::list<RefPtr<NGGestureRecognizer>> innerTargets4;
    gestureEventHub->gestureHierarchy_.clear();
    gestureEventHub->gestureHierarchy_.emplace_back(clickRecognizer4);
    gestureEventHub->ProcessTouchTestHierarchy(COORDINATE_OFFSET, touchRestrict, innerTargets4, finalResult, TOUCH_ID);
    sizeOfFinalResult = static_cast<int32_t>(finalResult.size());
    EXPECT_EQ(sizeOfFinalResult, 4);

    std::list<RefPtr<NGGestureRecognizer>> innerTargets5;
    gestureEventHub->gestureHierarchy_.clear();
    gestureEventHub->gestureHierarchy_.emplace_back(clickRecognizer);
    gestureEventHub->ProcessTouchTestHierarchy(COORDINATE_OFFSET, touchRestrict, innerTargets5, finalResult, TOUCH_ID);
    sizeOfFinalResult = static_cast<int32_t>(finalResult.size());
    EXPECT_EQ(sizeOfFinalResult, 5);
}

/**
 * @tc.name: GestureEventHubTest011
 * @tc.desc: Test IsAccessibilityClickable and IsAccessibiityLongClickable
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, GestureEventHubTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    eventHub->AttachHost(frameNode);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    ASSERT_NE(gestureEventHub, nullptr);

    /**
     * @tc.steps: step2. gestureHierarchy_ has ClickRecognizer, the number of fingers is two or click count is two
     * @tc.expected: IsAccessibilityClickable is false
     */
    EXPECT_FALSE(gestureEventHub->IsAccessibilityClickable());

    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(DOUBLE_FINGERS, 1);
    gestureEventHub->gestureHierarchy_.emplace_back(clickRecognizer);
    EXPECT_FALSE(gestureEventHub->IsAccessibilityClickable());
    gestureEventHub->gestureHierarchy_.clear();
    clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(1, CLICK_COUNTS);
    gestureEventHub->gestureHierarchy_.emplace_back(clickRecognizer);
    EXPECT_FALSE(gestureEventHub->IsAccessibilityClickable());
    gestureEventHub->gestureHierarchy_.clear();

    /**
     * @tc.steps: step3. gestureHierarchy_ has ClickRecognizer, the number of fingers is one
     * @tc.expected: IsAccessibilityClickable is true
     */
    clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>(FINGERS, 1);
    gestureEventHub->gestureHierarchy_.emplace_back(clickRecognizer);
    EXPECT_TRUE(gestureEventHub->IsAccessibilityClickable());
    gestureEventHub->gestureHierarchy_.clear();

    /**
     * @tc.steps: step4. call AddClickEvent
     * @tc.expected: IsAccessibilityClickable is true
     */
    auto clickCallback = [](GestureEvent& info) {};
    auto clickEvent = AceType::MakeRefPtr<ClickEvent>(std::move(clickCallback));
    gestureEventHub->AddClickEvent(clickEvent);
    EXPECT_TRUE(gestureEventHub->IsAccessibilityClickable());

    /**
     * @tc.steps: step5. gestureHierarchy_ has LongPressRecognizer, the number of fingers is two
     * @tc.expected: IsAccessibilityLongClickable is false
     */
    EXPECT_FALSE(gestureEventHub->IsAccessibilityLongClickable());

    auto longPressRecognizer = AceType::MakeRefPtr<LongPressRecognizer>(1, DOUBLE_FINGERS, false);
    gestureEventHub->gestureHierarchy_.emplace_back(longPressRecognizer);
    EXPECT_FALSE(gestureEventHub->IsAccessibilityLongClickable());
    gestureEventHub->gestureHierarchy_.clear();

    /**
     * @tc.steps: step6. gestureHierarchy_ has LongPressRecognizer, the number of fingers is one
     * @tc.expected: IsAccessibilityLongClickable is false
     */
    longPressRecognizer = AceType::MakeRefPtr<LongPressRecognizer>(1, 1, false);
    gestureEventHub->gestureHierarchy_.emplace_back(longPressRecognizer);
    EXPECT_TRUE(gestureEventHub->IsAccessibilityLongClickable());
    gestureEventHub->gestureHierarchy_.clear();

    /**
     * @tc.steps: step7. call SetLongPressEvent
     * @tc.expected: IsAccessibilityLongClickable is true
     */
    auto longPressCallback = [](GestureEvent& info) {};
    auto longPressEvent = AceType::MakeRefPtr<LongPressEvent>(longPressCallback);
    gestureEventHub->SetLongPressEvent(longPressEvent);
    EXPECT_TRUE(gestureEventHub->IsAccessibilityLongClickable());
}

/**
 * @tc.name: GestureEventHubTest012
 * @tc.desc: Test UpdateGestureHierarchy
 * @tc.type: FUNC
 */
HWTEST_F(GestureEventHubTestNg, GestureEventHubTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create GestureEventHub.
     * @tc.expected: gestureEventHub is not null.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(NODE_TAG, -1, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    eventHub->AttachHost(frameNode);
    auto gestureEventHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    ASSERT_NE(gestureEventHub, nullptr);

    /**
     * @tc.steps: step2. call OnModifyDone
     * @tc.expected: gestureHierarchy_ has two elements
     */
    gestureEventHub->recreateGesture_ = true;
    auto tapGesture = AceType::MakeRefPtr<TapGesture>(FINGERS, 1);
    gestureEventHub->gestures_.emplace_back(tapGesture);
    auto longPressGesture = AceType::MakeRefPtr<LongPressGesture>(FINGERS, false, 1);
    gestureEventHub->gestures_.emplace_back(longPressGesture);
    auto onAccessibilityEvent = gestureEventHub->GetOnAccessibilityEventFunc();
    ASSERT_NE(onAccessibilityEvent, nullptr);
    onAccessibilityEvent(AccessibilityEventType::CLICK);
    gestureEventHub->OnModifyDone();

    auto sizeGestureHierarchy = static_cast<int32_t>(gestureEventHub->gestureHierarchy_.size());
    EXPECT_EQ(sizeGestureHierarchy, GESTURES_COUNTS);
}
} // namespace OHOS::Ace::NG
