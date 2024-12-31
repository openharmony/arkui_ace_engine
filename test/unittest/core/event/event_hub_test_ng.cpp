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
#define protected public
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/geometry/ng/offset_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr bool EVENT_HUB_ENABLE = false;
const std::string DRAG_STARR_EVENT_TYPE = "drag start";
const std::string DRAG_ENTER_EVENT_TYPE = "drag enter";
const std::string DRAG_LEAVE_EVENT_TYPE = "drag leave";
const std::string DRAG_MOVE_EVENT_TYPE = "drag move";
const std::string DRAG_DROP_EVENT_TYPE = "drag drop";
const std::string DRAG_END_EVENT_TYPE = "drag end";

const float OLD_X_VALUE = 10.9f;
const float OLD_Y_VALUE = 11.0f;
const float OLD_WIDTH = 400.0f;
const float OLD_HEIGHT = 400.0f;
const RectF OLD_RECT = RectF(OLD_X_VALUE, OLD_Y_VALUE, OLD_WIDTH, OLD_HEIGHT);
const OffsetF OLD_ORIGIN = OffsetF(OLD_WIDTH, OLD_HEIGHT);

const float NEW_X_VALUE = 15.9f;
const float NEW_Y_VALUE = 15.0f;
const float NEW_WIDTH = 500.0f;
const float NEW_HEIGHT = 500.0f;
const RectF NEW_RECT = RectF(NEW_X_VALUE, NEW_Y_VALUE, NEW_WIDTH, NEW_HEIGHT);
const OffsetF NEW_ORIGIN = OffsetF(NEW_WIDTH, NEW_HEIGHT);

const RectF RECT_DELTA = RectF(1.0f, 1.0f, 1.0f, 1.0f);
const OffsetF OFFSET_DELTA = OffsetF(1.0f, 1.0f);
const OffsetF ORIGIN_DELTA = OffsetF(1.0f, 1.0f);

const std::string STRINGCTER_A = "A";
const std::string STRINGCTER_Q = "Q";
const std::string STRINGCTER_E = "E";
constexpr int32_t NUM_CTRL_VALUE = 1;
constexpr int32_t NUM_SHIFT_VALUE = 2;
constexpr int32_t NUM_ALT_VALUE = 4;
constexpr uint32_t MIN_INTERVAL = 100; // 100ms

const std::string RESULT_SUCCESS_ONE = "sucess1";
const std::string RESULT_SUCCESS_TWO = "sucess2";

int32_t flag = 0;
} // namespace

class EventHubTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
};

void EventHubTestNg::SetUpTestSuite()
{
    GTEST_LOG_(INFO) << "EventHubTestNg SetUpTestCase";
}

void EventHubTestNg::TearDownTestSuite()
{
    GTEST_LOG_(INFO) << "EventHubTestNg TearDownTestCase";
}

void EventHubTestNg::SetUp()
{
    MockPipelineContext::SetUp();
}

void EventHubTestNg::TearDown()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: EventHubCreateTest001
 * @tc.desc: Create EventHub.
 * @tc.type: FUNC
 */
HWTEST_F(EventHubTestNg, EventHubCreateTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventHub.
     * @tc.expected: eventHub is not null.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->MarkModifyDone();
    EXPECT_NE(eventHub, nullptr);

    /**
     * @tc.steps: step2. Get EventHub's properties.
     * @tc.expected: These properties are null when GetOrCreateEventHub functions have not been invoked.
     */
    EXPECT_EQ(eventHub->GetGestureEventHub(), nullptr);
    EXPECT_EQ(eventHub->GetInputEventHub(), nullptr);
    EXPECT_EQ(eventHub->GetFocusHub(), nullptr);
    EXPECT_EQ(eventHub->GetFrameNode(), nullptr);
    EXPECT_EQ(eventHub->GetOnDragStart(), nullptr);

    /**
     * @tc.steps: step3. Test EventHub's default properties.
     */
    EXPECT_TRUE(!eventHub->HasOnAreaChanged());
    EXPECT_TRUE(!eventHub->HasOnDragStart());
    EXPECT_TRUE(!eventHub->HasOnDrop());
    EXPECT_TRUE(eventHub->IsEnabled());
}

/**
 * @tc.name: EventHubPropertyTest002
 * @tc.desc: Create EventHub and invoke GetOrCreateEventHub functions.
 * @tc.type: FUNC
 */
HWTEST_F(EventHubTestNg, EventHubPropertyTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventHub.
     * @tc.expected: eventHub is not null.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_NE(eventHub, nullptr);

    /**
     * @tc.steps: step2. Invoke GetOrCreateEventHub functions.
     * @tc.expected: These eventHub properties are not null.
     */
    eventHub->GetOrCreateGestureEventHub();
    eventHub->GetOrCreateInputEventHub();
    eventHub->GetOrCreateFocusHub();
    EXPECT_NE(eventHub->GetGestureEventHub(), nullptr);
    EXPECT_NE(eventHub->GetInputEventHub(), nullptr);
    EXPECT_NE(eventHub->GetFocusHub(), nullptr);

    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    EXPECT_TRUE(eventHub->GetFrameNode() != nullptr && eventHub->GetFrameNode()->GetTag() == V2::TEXT_ETS_TAG);
    eventHub->OnContextAttached();
    eventHub->SetEnabled(EVENT_HUB_ENABLE);
    EXPECT_TRUE(!eventHub->IsEnabled());
}

/**
 * @tc.name: EventHubPropertyTest003
 * @tc.desc: Create EventHub and set/fire onAreaChanged, onAppear and onDisappear function.
 * @tc.type: FUNC
 */
HWTEST_F(EventHubTestNg, EventHubPropertyTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventHub.
     * @tc.expected: eventHub is not null.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_NE(eventHub, nullptr);

    /**
     * @tc.steps: step2. Set EventHub OnAreaChanged function and fire it.
     * @tc.expected: onAreaChanged is invoked and the temp values are assigned with correct values.
     */
    RectF tempOldRect;
    OffsetF tempOldOrigin;
    RectF tempNewRect;
    OffsetF tempNewOrigin;
    auto onAreaChanged = [&tempOldRect, &tempOldOrigin, &tempNewRect, &tempNewOrigin](
                             const RectF& oldRect, const OffsetF& oldOrigin, const RectF& rect, const OffsetF& origin) {
        tempOldRect = oldRect;
        tempOldOrigin = oldOrigin;
        tempNewRect = rect;
        tempNewOrigin = origin;
    };

    eventHub->SetOnAreaChanged(onAreaChanged);
    eventHub->FireOnAreaChanged(OLD_RECT, OLD_ORIGIN, NEW_RECT, NEW_ORIGIN);
    EXPECT_TRUE(eventHub->HasOnAreaChanged());
    EXPECT_EQ(tempOldRect, OLD_RECT);
    EXPECT_EQ(tempOldOrigin, OLD_ORIGIN);
    EXPECT_EQ(tempNewRect, NEW_RECT);
    EXPECT_EQ(tempNewOrigin, NEW_ORIGIN);

    /**
     * @tc.steps: step3. Set/fire EventHub onAppear and onDisappear function.
     * @tc.expected: isAppear is assigned with correct value.
     */
    eventHub->SetOnAppear([]() {});
    eventHub->FireOnAppear();

    eventHub->SetOnDisappear([]() {});
    eventHub->FireOnDisappear();
}

/**
 * @tc.name: EventHubDragEventsTest004
 * @tc.desc: Create EventHub and set/fire drag related functions.
 * @tc.type: FUNC
 */
HWTEST_F(EventHubTestNg, EventHubDragEventsTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventHub.
     * @tc.expected: eventHub is not null.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_NE(eventHub, nullptr);

    /**
     * @tc.steps: step2. Set EventHub OnDragStart event and fire it.
     * @tc.expected: OnDragStart is invoked and the temp values are assigned with correct values.
     */
    auto dragEvent = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    std::string dragEventType;
    auto OnDragStartFunc = [&dragEventType](const RefPtr<OHOS::Ace::DragEvent>& /* dragEvent */,
                               const std::string& eventType) -> DragDropInfo {
        dragEventType = eventType;
        return {};
    };
    eventHub->SetOnDragStart(OnDragStartFunc);
    EXPECT_TRUE(eventHub->HasOnDragStart());
    EXPECT_NE(eventHub->GetOnDragStart(), nullptr);
    eventHub->GetOnDragStart()(dragEvent, DRAG_STARR_EVENT_TYPE);
    EXPECT_EQ(dragEventType, DRAG_STARR_EVENT_TYPE);

    /**
     * @tc.steps: step3. Set EventHub OnDragEnter event and fire it.
     * @tc.expected: OnDragEnter is invoked and the temp values are assigned with correct values.
     */
    auto OnDragFunc = [&dragEventType](const RefPtr<OHOS::Ace::DragEvent>& /* dragEvent */,
                          const std::string& eventType) { dragEventType = eventType; };
    auto onDragEnter = OnDragFunc;
    eventHub->SetOnDragEnter(onDragEnter);
    eventHub->FireOnDragEnter(dragEvent, DRAG_ENTER_EVENT_TYPE);
    EXPECT_EQ(dragEventType, DRAG_ENTER_EVENT_TYPE);

    /**
     * @tc.steps: step4. Set EventHub OnDragLeave event and fire it.
     * @tc.expected: OnDragLeave is invoked and the temp values are assigned with correct values.
     */
    auto onDragLeave = OnDragFunc;
    eventHub->SetOnDragLeave(onDragLeave);
    eventHub->FireOnDragLeave(dragEvent, DRAG_LEAVE_EVENT_TYPE);
    EXPECT_EQ(dragEventType, DRAG_LEAVE_EVENT_TYPE);

    /**
     * @tc.steps: step5. Set EventHub OnDragMove event and fire it.
     * @tc.expected: OnDragMove is invoked and the temp values are assigned with correct values.
     */
    auto onDragMove = OnDragFunc;
    eventHub->SetOnDragMove(onDragMove);
    eventHub->FireOnDragMove(dragEvent, DRAG_MOVE_EVENT_TYPE);
    EXPECT_EQ(dragEventType, DRAG_MOVE_EVENT_TYPE);

    /**
     * @tc.steps: step6. Set EventHub OnDrop event and fire it.
     * @tc.expected: OnDrop is invoked and the temp values are assigned with correct values.
     */
    auto onDragDrop = OnDragFunc;
    eventHub->SetOnDrop(onDragDrop);
    eventHub->FireOnDragMove(dragEvent, DRAG_DROP_EVENT_TYPE);
    EXPECT_TRUE(eventHub->HasOnDrop());
    EXPECT_EQ(dragEventType, DRAG_DROP_EVENT_TYPE);
}

/**
 * @tc.name: EventHubCreateTest005
 * @tc.desc: Create EventHub.
 * @tc.type: FUNC
 */
HWTEST_F(EventHubTestNg, EventHubDragEventsTest005, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    std::vector<KeyboardShortcut> keyboardShortcut;
    eventHub->SetKeyboardShortcut(STRINGCTER_A, NUM_CTRL_VALUE, []() {});
    keyboardShortcut = eventHub->GetKeyboardShortcut();
    for (auto iter = keyboardShortcut.begin(); iter != keyboardShortcut.end(); iter++) {
        EXPECT_EQ(STRINGCTER_A, (*iter).value);
        EXPECT_EQ(NUM_CTRL_VALUE, (*iter).keys);
    }
    keyboardShortcut.clear();

    eventHub->SetKeyboardShortcut(STRINGCTER_Q, NUM_SHIFT_VALUE, []() {});
    eventHub->GetKeyboardShortcut();
    for (auto iter = keyboardShortcut.begin(); iter != keyboardShortcut.end(); iter++) {
        EXPECT_EQ(STRINGCTER_Q, (*iter).value);
        EXPECT_EQ(NUM_SHIFT_VALUE, (*iter).keys);
    }
    keyboardShortcut.clear();

    eventHub->SetKeyboardShortcut(STRINGCTER_E, NUM_ALT_VALUE, []() {});
    eventHub->GetKeyboardShortcut();
    for (auto iter = keyboardShortcut.begin(); iter != keyboardShortcut.end(); iter++) {
        EXPECT_EQ(STRINGCTER_E, (*iter).value);
        EXPECT_EQ(NUM_CTRL_VALUE, (*iter).keys);
    }
    keyboardShortcut.clear();
}

/**
 * @tc.name: EventHubDragEventsTest006
 * @tc.desc: Create EventHub and set/fire drag related customer functions.
 * @tc.type: FUNC
 */
HWTEST_F(EventHubTestNg, EventHubDragEventsTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventHub.
     * @tc.expected: eventHub is not null.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_NE(eventHub, nullptr);

    /**
     * @tc.steps: step2. Set EventHub Customer OnDragEnter event and fire it.
     * @tc.expected: OnDragEnter is invoked and the temp values are assigned with correct values.
     */
    auto dragEvent = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    std::string dragEventType;
    auto OnDragFunc = [&dragEventType](const RefPtr<OHOS::Ace::DragEvent>& /* dragEvent */,
                          const std::string& eventType) { dragEventType = eventType; };
    auto onDragEnter = OnDragFunc;
    eventHub->SetCustomerOnDragFunc(DragFuncType::DRAG_ENTER, onDragEnter);
    eventHub->FireCustomerOnDragFunc(DragFuncType::DRAG_ENTER, dragEvent, DRAG_ENTER_EVENT_TYPE);
    EXPECT_EQ(dragEventType, DRAG_ENTER_EVENT_TYPE);

    /**
     * @tc.steps: step3. Set EventHub Customer OnDragLeave event and fire it.
     * @tc.expected: OnDragLeave is invoked and the temp values are assigned with correct values.
     */
    auto onDragLeave = OnDragFunc;
    eventHub->SetCustomerOnDragFunc(DragFuncType::DRAG_LEAVE, onDragLeave);
    eventHub->FireCustomerOnDragFunc(DragFuncType::DRAG_LEAVE, dragEvent, DRAG_LEAVE_EVENT_TYPE);
    EXPECT_EQ(dragEventType, DRAG_LEAVE_EVENT_TYPE);

    /**
     * @tc.steps: step4. Set EventHub Customer OnDragMove event and fire it.
     * @tc.expected: OnDragMove is invoked and the temp values are assigned with correct values.
     */
    auto onDragMove = OnDragFunc;
    eventHub->SetCustomerOnDragFunc(DragFuncType::DRAG_MOVE, onDragMove);
    eventHub->FireCustomerOnDragFunc(DragFuncType::DRAG_MOVE, dragEvent, DRAG_MOVE_EVENT_TYPE);
    EXPECT_EQ(dragEventType, DRAG_MOVE_EVENT_TYPE);

    /**
     * @tc.steps: step6. Set EventHub Customer OnDrop event and fire it.
     * @tc.expected: OnDrop is invoked and the temp values are assigned with correct values.
     */
    auto onDragDrop = OnDragFunc;
    eventHub->SetCustomerOnDragFunc(DragFuncType::DRAG_DROP, onDragDrop);
    eventHub->FireCustomerOnDragFunc(DragFuncType::DRAG_DROP, dragEvent, DRAG_DROP_EVENT_TYPE);
    EXPECT_TRUE(eventHub->HasCustomerOnDrop());
    EXPECT_EQ(dragEventType, DRAG_DROP_EVENT_TYPE);

    /**
     * @tc.steps: step7. Set EventHub Customer OnDragEnd event and fire it.
     * @tc.expected: OnDragEnd is invoked and the temp values are assigned with correct values.
     */
    auto OnDragEnd = [&dragEventType](const RefPtr<OHOS::Ace::DragEvent>& /* dragEvent */) {
        dragEventType = DRAG_END_EVENT_TYPE;
    };
    eventHub->SetCustomerOnDragFunc(DragFuncType::DRAG_END, OnDragEnd);
    eventHub->FireCustomerOnDragFunc(DragFuncType::DRAG_END, dragEvent);
    EXPECT_EQ(dragEventType, DRAG_END_EVENT_TYPE);
}

/**
 * @tc.name: EventHubDisableAreaChange001
 * @tc.desc: Create EventHub and test disable areaChange function.
 * @tc.type: FUNC
 */
HWTEST_F(EventHubTestNg, EventHubDisableAreaChange001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventHub.
     * @tc.expected: eventHub is not null.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_NE(eventHub, nullptr);

    /**
     * @tc.steps: step2. Set EventHub OnAreaChanged function and fire it.
     * @tc.expected: onAreaChanged is invoked and the temp values are assigned with correct values.
     */
    RectF tempOldRect;
    OffsetF tempOldOrigin;
    RectF tempNewRect;
    OffsetF tempNewOrigin;
    auto onAreaChanged = [&tempOldRect, &tempOldOrigin, &tempNewRect, &tempNewOrigin](
                             const RectF& oldRect, const OffsetF& oldOrigin, const RectF& rect, const OffsetF& origin) {
        tempOldRect = oldRect;
        tempOldOrigin = oldOrigin;
        tempNewRect = rect;
        tempNewOrigin = origin;
    };

    eventHub->SetOnAreaChanged(onAreaChanged);
    eventHub->FireOnAreaChanged(OLD_RECT, OLD_ORIGIN, NEW_RECT, NEW_ORIGIN);
    EXPECT_TRUE(eventHub->HasOnAreaChanged());
    EXPECT_EQ(tempOldRect, OLD_RECT);
    EXPECT_EQ(tempOldOrigin, OLD_ORIGIN);
    EXPECT_EQ(tempNewRect, NEW_RECT);
    EXPECT_EQ(tempNewOrigin, NEW_ORIGIN);

    /**
     * @tc.steps: step3. Clear the callback.
     * @tc.expected: onAreaChanged is empty.
     */
    eventHub->ClearUserOnAreaChanged();
    eventHub->FireOnAreaChanged(
        OLD_RECT + OFFSET_DELTA, OLD_ORIGIN + ORIGIN_DELTA, NEW_RECT + OFFSET_DELTA, NEW_ORIGIN + ORIGIN_DELTA);
    EXPECT_FALSE(eventHub->HasOnAreaChanged());
    EXPECT_EQ(tempOldRect, OLD_RECT);
    EXPECT_EQ(tempOldOrigin, OLD_ORIGIN);
    EXPECT_EQ(tempNewRect, NEW_RECT);
    EXPECT_EQ(tempNewOrigin, NEW_ORIGIN);

    /**
     * @tc.steps: step3. Set/fire areaChange function.
     * @tc.expected: areaChange is assigned with correct value.
     */
    eventHub->SetOnAreaChanged(onAreaChanged);
    eventHub->FireOnAreaChanged(
        OLD_RECT + OFFSET_DELTA, OLD_ORIGIN + ORIGIN_DELTA, NEW_RECT + OFFSET_DELTA, NEW_ORIGIN + ORIGIN_DELTA);
    EXPECT_TRUE(eventHub->HasOnAreaChanged());
    EXPECT_EQ(tempOldRect, OLD_RECT + OFFSET_DELTA);
    EXPECT_EQ(tempOldOrigin, OLD_ORIGIN + ORIGIN_DELTA);
    EXPECT_EQ(tempNewRect, NEW_RECT + OFFSET_DELTA);
    EXPECT_EQ(tempNewOrigin, NEW_ORIGIN + ORIGIN_DELTA);
}

/**
 * @tc.name: EventHubDisableAppear001
 * @tc.desc: Create EventHub and test disable onAppear function.
 * @tc.type: FUNC
 */
HWTEST_F(EventHubTestNg, EventHubDisableAppear001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventHub.
     * @tc.expected: eventHub is not null.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_NE(eventHub, nullptr);

    /**
     * @tc.steps: step2. Set EventHub onAppear function and fire it.
     * @tc.expected: onAppear is invoked and the temp values are assigned with correct values.
     */
    std::string result;
    auto onAppear = [&result]() { result = RESULT_SUCCESS_ONE; };

    eventHub->SetOnAppear(onAppear);
    EXPECT_NE(eventHub->onAppear_, nullptr);
    eventHub->onAppear_();
    EXPECT_EQ(result, RESULT_SUCCESS_ONE);
    /**
     * @tc.steps: step3. Clear the callback.
     * @tc.expected: onAppear is empty.
     */
    eventHub->ClearUserOnAppear();
    EXPECT_EQ(eventHub->onAppear_, nullptr);

    /**
     * @tc.steps: step3. Set/fire EventHub onAppear function.
     * @tc.expected: onAppear is assigned with correct value.
     */
    auto onAppear2 = [&result]() { result = RESULT_SUCCESS_TWO; };

    eventHub->SetOnAppear(onAppear2);
    EXPECT_NE(eventHub->onAppear_, nullptr);
    eventHub->onAppear_();
    EXPECT_EQ(result, RESULT_SUCCESS_TWO);
}

/**
 * @tc.name: EventHubDisableDisAppear001
 * @tc.desc: Create EventHub and test disable onDisAppear function.
 * @tc.type: FUNC
 */
HWTEST_F(EventHubTestNg, EventHubDisableDisAppear001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventHub.
     * @tc.expected: eventHub is not null.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_NE(eventHub, nullptr);

    /**
     * @tc.steps: step2. Set EventHub onDisAppear function and fire it.
     * @tc.expected: onDisAppear is invoked and the temp values are assigned with correct values.
     */
    std::string result;
    auto onDisAppear = [&result]() { result = RESULT_SUCCESS_ONE; };

    eventHub->SetOnDisappear(onDisAppear);
    EXPECT_NE(eventHub->onDisappear_, nullptr);
    eventHub->onDisappear_();
    EXPECT_EQ(result, RESULT_SUCCESS_ONE);
    /**
     * @tc.steps: step3. Clear the callback.
     * @tc.expected: onDisAppear is empty.
     */
    eventHub->ClearUserOnDisAppear();
    EXPECT_EQ(eventHub->onDisappear_, nullptr);

    /**
     * @tc.steps: step3. Set/fire EventHub onDisappear function.
     * @tc.expected: disAppear is assigned with correct value.
     */
    auto onDisAppear2 = [&result]() { result = RESULT_SUCCESS_TWO; };

    eventHub->SetOnDisappear(onDisAppear2);
    EXPECT_NE(eventHub->onDisappear_, nullptr);
    eventHub->onDisappear_();
    EXPECT_EQ(result, RESULT_SUCCESS_TWO);
}

/**
 * @tc.name: SetCurrentUIState001
 * @tc.desc: Create EventHub and test disable onDisAppear function.
 * @tc.type: FUNC
 */
HWTEST_F(EventHubTestNg, SetCurrentUIState002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventHub.
     * @tc.expected: eventHub is not null.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_NE(eventHub, nullptr);
    bool temp = true;

    /**
     * @tc.steps: Use SetCurrentUIState to set the UIState state
     * @tc.expected: Use 'GetCurrentUIState' to obtain the already set UIState
     */
    eventHub->AddSupportedState(UI_STATE_NORMAL);
    eventHub->SetSupportedStates(UI_STATE_NORMAL);
    eventHub->MarkModifyDone();

    eventHub->SetCurrentUIState(UI_STATE_NORMAL, temp);
    EXPECT_EQ(eventHub->GetCurrentUIState(), UI_STATE_NORMAL);

    eventHub->IsCurrentStateOn(UI_STATE_NORMAL);
    eventHub->CreateGetEventTargetImpl();

    eventHub->SetCurrentUIState(UI_STATE_PRESSED, temp);
    EXPECT_EQ(eventHub->GetCurrentUIState(), UI_STATE_PRESSED);

    eventHub->SetCurrentUIState(UI_STATE_FOCUSED, temp);
    EXPECT_EQ(eventHub->GetCurrentUIState(), UI_STATE_NORMAL | UI_STATE_PRESSED | UI_STATE_FOCUSED);
    eventHub->MarkModifyDone();

    eventHub->SetCurrentUIState(UI_STATE_DISABLED, temp);
    EXPECT_EQ(eventHub->GetCurrentUIState(), UI_STATE_NORMAL | UI_STATE_PRESSED | UI_STATE_FOCUSED | UI_STATE_DISABLED);

    eventHub->SetCurrentUIState(UI_STATE_SELECTED, temp);
    EXPECT_EQ(eventHub->GetCurrentUIState(),
        UI_STATE_SELECTED | UI_STATE_NORMAL | UI_STATE_PRESSED | UI_STATE_FOCUSED | UI_STATE_DISABLED);
}

/**
 * @tc.name: EventHubTest001
 * @tc.desc: Default branch in test FireCustomerOnDragFunc
 * @tc.type: FUNC
 */
HWTEST_F(EventHubTestNg, EventHubTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventHub.
     * @tc.expected: eventHub is not null.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_NE(eventHub, nullptr);

    /**
     * @tc.steps: step2. Create DragEvent.
     * @tc.expected: DragEvent is not null.
     */
    auto dragEvent = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    EXPECT_NE(dragEvent, nullptr);

    /**
     * @tc.steps: step3. Calling DRAG in FirecustomerOnDragFunc_ CustomerOnDragEnd in END_ Empty branch.
     * @tc.expected: retFlag is false.
     */
    eventHub->FireCustomerOnDragFunc(DragFuncType::DRAG_END, dragEvent, DRAG_DROP_EVENT_TYPE);
    auto retFlag = eventHub->HasCustomerOnDrop();
    EXPECT_FALSE(retFlag);

    /**
     * @tc.steps: step4. Calling the default branch in FirecustomerOnDragFunc.
     * @tc.expected: retFlag is false.
     */
    eventHub->FireCustomerOnDragFunc(DragFuncType(10), dragEvent, DRAG_DROP_EVENT_TYPE);
    retFlag = eventHub->HasCustomerOnDrop();
    EXPECT_FALSE(retFlag);
}

/**
 * @tc.name: EventHubTest002
 * @tc.desc: Default Branch in Test SetCustomerOnDragFunc(OnDragFunc)
 * @tc.type: FUNC
 */
HWTEST_F(EventHubTestNg, EventHubTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventHub.
     * @tc.expected: eventHub is not null.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_NE(eventHub, nullptr);

    /**
     * @tc.steps: step2. Create DragEvent.
     * @tc.expected: DragEvent is not null.
     */
    auto dragEvent = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    EXPECT_NE(dragEvent, nullptr);

    /**
     * @tc.steps: step3. construct OnDragFunc.
     */
    std::string dragEventType;
    auto onDragFunc = [&dragEventType](const RefPtr<OHOS::Ace::DragEvent>& /* dragEvent */,
                          const std::string& eventType) { dragEventType = eventType; };

    /**
     * @tc.steps: step4. Calling the default branch in SetCustomerOnDragFunc.
     * @tc.expected: eventHub->customerOnDragEnd_ is false.
     */
    eventHub->SetCustomerOnDragFunc(DragFuncType(10), onDragFunc);
    EXPECT_FALSE(eventHub->customerOnDragEnd_);
}

/**
 * @tc.name: EventHubTest003
 * @tc.desc: Default Branch in Test SetCustomerOnDragFunc(OnNewDragFunc)
 * @tc.type: FUNC
 */
HWTEST_F(EventHubTestNg, EventHubTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventHub.
     * @tc.expected: eventHub is not null.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_NE(eventHub, nullptr);

    /**
     * @tc.steps: step2. Create DragEvent.
     * @tc.expected: DragEvent is not null.
     */
    auto dragEvent = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    EXPECT_NE(dragEvent, nullptr);

    /**
     * @tc.steps: step3. construct OnDragFunc.
     */
    std::string dragEventType;
    auto onDragFunc = [&dragEventType](
                          const RefPtr<OHOS::Ace::DragEvent>& /* dragEvent */) { dragEventType = DRAG_END_EVENT_TYPE; };

    /**
     * @tc.steps: step4. Call SetCustomerOnDragFunc with OnDragFunc.
     * @tc.expected: eventHub->customerOnDragEnter_ is false.
     */
    eventHub->SetCustomerOnDragFunc(DragFuncType(10), onDragFunc);
    EXPECT_FALSE(eventHub->customerOnDragEnter_);
}

/**
 * @tc.name: EventHubTest004
 * @tc.desc: Test MarkModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(EventHubTestNg, EventHubTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventHub.
     * @tc.expected: eventHub is not null.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_NE(eventHub, nullptr);

    /**
     * @tc.steps: step2. Update SupportedState in eventHub using UI_STATE_PRESSED.
     */
    eventHub->AddSupportedState(UI_STATE_PRESSED);
    eventHub->SetSupportedStates(UI_STATE_PRESSED);

    /**
     * @tc.steps: step3. Call MarkModifyDone, stateStyleMgr_->HasStateStyle(UI_STATE_PRESSED) is a true branch.
     * @tc.expected: retFlag is true.
     */
    eventHub->MarkModifyDone();
    bool retFlag = eventHub->stateStyleMgr_->HasStateStyle(UI_STATE_PRESSED);
    EXPECT_TRUE(retFlag);

    /**
     * @tc.steps: step4. Update SupportedState in eventHub using UI_STATE_DISABLED.
     */
    eventHub->AddSupportedState(UI_STATE_DISABLED);
    eventHub->SetSupportedStates(UI_STATE_DISABLED);

    /**
     * @tc.steps: step5. Call MarkModifyDone, stateStyleMgr_->HasStateStyle(UI_STATE_DISABLED) is a true branch.
     * @tc.expected: retFlag is true.
     */
    eventHub->MarkModifyDone();
    retFlag = eventHub->stateStyleMgr_->HasStateStyle(UI_STATE_DISABLED);
    EXPECT_TRUE(retFlag);

    /**
     * @tc.steps: step6. Update SupportedState in eventHub using UI_STATE_DISABLED.
     */
    eventHub->AddSupportedState(UI_STATE_DISABLED);
    eventHub->SetSupportedStates(UI_STATE_DISABLED);
    eventHub->SetEnabled(false);

    /**
     * @tc.steps: step7. Call MarkModifyDone, enabled_ is a false branch.
     * @tc.expected: eventHub->IsEnabled() return value is false.
     */
    eventHub->MarkModifyDone();
    EXPECT_FALSE(eventHub->IsEnabled());
}

/**
 * @tc.name: EventHubTest005
 * @tc.desc: stateStyleMgr_ in Test SetSupportedStates is a fake branch
 * @tc.type: FUNC
 */
HWTEST_F(EventHubTestNg, EventHubTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventHub.
     * @tc.expected: eventHub is not null.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_NE(eventHub, nullptr);

    /**
     * @tc.steps: step2. Call SetSupportedStates with UI_STATE_PRESSED.
     * @tc.expected: eventHub->stateStyleMgr_ is true.
     */
    eventHub->stateStyleMgr_ = nullptr;
    eventHub->SetSupportedStates(UI_STATE_PRESSED);
    EXPECT_TRUE(eventHub->stateStyleMgr_);
}

/**
 * @tc.name: EventHubFrameNodeTest001
 * @tc.desc: test ClearJSFrameNodeOnDisappear
 * @tc.type: FUNC
 */
HWTEST_F(EventHubTestNg, EventHubFrameNodeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventHub.
     * @tc.expected: eventHub is not null.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_NE(eventHub, nullptr);

    /**
     * @tc.steps: step2. Call ClearJSFrameNodeOnDisappear with onJSFrameNodeDisappear_ is nullptr.
     * @tc.expected: eventHub->onJSFrameNodeDisappear_ is nullptr.
     */
    eventHub->onJSFrameNodeDisappear_ = nullptr;
    eventHub->ClearJSFrameNodeOnDisappear();
    EXPECT_EQ(eventHub->onJSFrameNodeDisappear_, nullptr);

    /**
     * @tc.steps: step3. Call ClearJSFrameNodeOnDisappear with onJSFrameNodeDisappear_ is not nullptr.
     * @tc.expected: flag is equal 1.
     */
    std::function<void()> flagFunc = []() { ++flag; };
    eventHub->SetJSFrameNodeOnDisappear(std::move(flagFunc));
    EXPECT_NE(eventHub->onJSFrameNodeDisappear_, nullptr);
    eventHub->ClearJSFrameNodeOnDisappear();
    EXPECT_EQ(eventHub->onJSFrameNodeDisappear_, nullptr);
}

/**
 * @tc.name: EventHubFrameNodeTest002
 * @tc.desc: test ClearJSFrameNodeOnAppear
 * @tc.type: FUNC
 */
HWTEST_F(EventHubTestNg, EventHubFrameNodeTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventHub.
     * @tc.expected: eventHub is not null.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_NE(eventHub, nullptr);

    /**
     * @tc.steps: step2. Call ClearJSFrameNodeOnAppear with onJSFrameNodeAppear_ is nullptr.
     * @tc.expected: eventHub->onJSFrameNodeAppear_ is nullptr.
     */
    eventHub->onJSFrameNodeAppear_ = nullptr;
    eventHub->ClearJSFrameNodeOnAppear();
    EXPECT_EQ(eventHub->onJSFrameNodeAppear_, nullptr);

    /**
     * @tc.steps: step3. Call ClearJSFrameNodeOnAppear with onJSFrameNodeDisappear_ is not nullptr.
     * @tc.expected:onJSFrameNodeAppear_ is nullptr.
     */
    std::function<void()> flagFunc = []() { ++flag; };
    eventHub->SetJSFrameNodeOnAppear(std::move(flagFunc));
    EXPECT_NE(eventHub->onJSFrameNodeAppear_, nullptr);
    eventHub->ClearJSFrameNodeOnAppear();
    EXPECT_EQ(eventHub->onJSFrameNodeAppear_, nullptr);
}

/**
 * @tc.name: EventHubFrameNodeTest003
 * @tc.desc: test FireOnAppear
 * @tc.type: FUNC
 */
HWTEST_F(EventHubTestNg, EventHubFrameNodeTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventHub.
     * @tc.expected: eventHub is not null.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_NE(eventHub, nullptr);

    /**
     * @tc.steps: step2. Call FireOnAppear with onAppear_ and onJSFrameNodeAppear_ are both nullptr.
     * @tc.expected: flag is equal 0.
     */
    eventHub->onAppear_ = nullptr;
    eventHub->onJSFrameNodeAppear_ = nullptr;
    eventHub->FireOnAppear();
    EXPECT_EQ(flag, 0);

    /**
     * @tc.steps: step3. Call FireOnAppear with onAppear_  is nullptr and onJSFrameNodeAppear_ are is not nullptr.
     * @tc.expected: onJSFrameNodeAppear_ is not nullptr.
     */
    std::function<void()> flagFunc = []() { ++flag; };
    eventHub->SetJSFrameNodeOnAppear(std::move(flagFunc));
    eventHub->FireOnAppear();
    EXPECT_NE(eventHub->onJSFrameNodeAppear_, nullptr);
}

/**
 * @tc.name: EventHubFrameNodeTest004
 * @tc.desc: test FireOnDisappear
 * @tc.type: FUNC
 */
HWTEST_F(EventHubTestNg, EventHubFrameNodeTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventHub.
     * @tc.expected: eventHub is not null.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_NE(eventHub, nullptr);

    /**
     * @tc.steps: step2. Call FireOnDisappear with onAppear_ and onJSFrameNodeAppear_ are both nullptr.
     * @tc.expected: flag is equal 0.
     */
    eventHub->onDisappear_ = nullptr;
    eventHub->onJSFrameNodeDisappear_ = nullptr;
    eventHub->FireOnDisappear();
    EXPECT_EQ(flag, 0);

    /**
     * @tc.steps: step3. Call FireOnDisappear with onAppear_  is and onJSFrameNodeAppear_ are both not nullptr.
     * @tc.expected: flag is equal 2.
     */
    std::function<void()> flagFunc = []() { flag++; };
    eventHub->onDisappear_ = flagFunc;
    eventHub->onJSFrameNodeDisappear_ = flagFunc;
    eventHub->FireOnDisappear();
    EXPECT_EQ(flag, 2);
}

/**
 * @tc.name: EventHubFrameNodeTest005
 * @tc.desc: test set event about visibleAreaChange
 * @tc.type: FUNC
 */
HWTEST_F(EventHubTestNg, EventHubFrameNodeTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create EventHub.
     * @tc.expected: eventHub is not null.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    EXPECT_NE(eventHub, nullptr);

    /**
     * @tc.steps: step2. set throttledVisibleAreaRatios_, throttledVisibleAreaCallback_.
     * @tc.expected: HasImmediatelyVisibleCallback is equal to false.
     */
    VisibleCallbackInfo callbackInfo;
    const std::function<void(bool, double)>&& jsCallback = [](bool isVisible, double radio) { flag++; };
    callbackInfo.callback = jsCallback;
    callbackInfo.period = MIN_INTERVAL;
    std::vector<double> ratios = { 0, 1.0 };
    flag = 0;
    eventHub->SetVisibleAreaRatiosAndCallback(callbackInfo, ratios, true);
    EXPECT_EQ(flag, 0);
    EXPECT_NE(eventHub->HasImmediatelyVisibleCallback(), true);
    EXPECT_EQ(eventHub->GetThrottledVisibleAreaRatios(), ratios);
    EXPECT_NE(eventHub->GetThrottledVisibleAreaCallback().callback, nullptr);

    /**
     * @tc.steps: step3. clear throttledVisibleAreaRatios_, throttledVisibleAreaCallback_.
     * @tc.expected:throttledVisibleAreaRatios_ is empty, callback in throttledVisibleAreaCallback_ is nullptr.
     */
    eventHub->CleanVisibleAreaCallback(true, true);
    EXPECT_EQ(eventHub->GetThrottledVisibleAreaRatios().empty(), true);
    EXPECT_EQ(eventHub->GetThrottledVisibleAreaCallback().callback, nullptr);

    /**
     * @tc.steps: step4. set visibleAreaUserCallback_.
     * @tc.expected: HasImmediatelyVisibleCallback is equal to true.
     */
    callbackInfo.period = 0;
    eventHub->SetVisibleAreaRatiosAndCallback(callbackInfo, ratios, true);
    EXPECT_EQ(flag, 0);
    EXPECT_EQ(eventHub->HasImmediatelyVisibleCallback(), true);
}

/**
 * @tc.name: EventHubTest006
 * @tc.desc: OnAttachContext
 * @tc.type: FUNC
 */
HWTEST_F(EventHubTestNg, EventHubTest006, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto dragEvent = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    RectF tempOldRect;
    OffsetF tempOldOrigin;
    RectF tempNewRect;
    OffsetF tempNewOrigin;
    auto onAreaChanged = [&tempOldRect, &tempOldOrigin, &tempNewRect, &tempNewOrigin](
                             const RectF& oldRect, const OffsetF& oldOrigin, const RectF& rect, const OffsetF& origin) {
        tempOldRect = oldRect;
        tempOldOrigin = oldOrigin;
        tempNewRect = rect;
        tempNewOrigin = origin;
    };

    eventHub->SetOnAreaChanged(onAreaChanged);
    eventHub->GetOrCreateGestureEventHub();
    eventHub->GetOrCreateInputEventHub();
    eventHub->GetOrCreateFocusHub();

    VisibleCallbackInfo callbackInfo;
    const std::function<void(bool, double)>&& jsCallback = [](bool isVisible, double radio) { flag++; };
    callbackInfo.callback = jsCallback;
    callbackInfo.period = MIN_INTERVAL;
    callbackInfo.period = 0;
    std::vector<double> ratios = { 0, 1.0 };
    eventHub->SetVisibleAreaRatiosAndCallback(callbackInfo, ratios, true);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);

    auto context = MockPipelineContext::GetCurrent();
    eventHub->OnAttachContext(AceType::RawPtr(context));
    EXPECT_NE(eventHub->GetOrCreateGestureEventHub(), nullptr);
}

/**
 * @tc.name: EventHubTest007
 * @tc.desc: OnAttachContext
 * @tc.type: FUNC
 */
HWTEST_F(EventHubTestNg, EventHubTest007, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();

    eventHub->GetOrCreateGestureEventHub();
    eventHub->GetOrCreateInputEventHub();
    eventHub->GetOrCreateFocusHub();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    bool flags = false;
    OnAreaChangedFunc onAreaChanged = [&flags](const RectF& oldRect, const OffsetF& oldOrigin, const RectF& rect,
                                          const OffsetF& origin) { flags = !flags; };
    eventHub->AddInnerOnAreaChangedCallback(1, std::move(onAreaChanged));
    VisibleCallbackInfo callbackInfo;
    const std::function<void(bool, double)>&& jsCallback = [](bool isVisible, double radio) { flag++; };
    callbackInfo.callback = jsCallback;
    callbackInfo.period = MIN_INTERVAL;
    std::vector<double> ratios = { 0, 1.0 };
    eventHub->SetVisibleAreaRatiosAndCallback(callbackInfo, ratios, false);

    auto context = MockPipelineContext::GetCurrent();
    eventHub->OnAttachContext(AceType::RawPtr(context));
    EXPECT_NE(eventHub->GetOrCreateGestureEventHub(), nullptr);
}

/**
 * @tc.name: EventHubTest008
 * @tc.desc: OnDetachContext
 * @tc.type: FUNC
 */
HWTEST_F(EventHubTestNg, EventHubTest008, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto dragEvent = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    RectF tempOldRect;
    OffsetF tempOldOrigin;
    RectF tempNewRect;
    OffsetF tempNewOrigin;
    auto onAreaChanged = [&tempOldRect, &tempOldOrigin, &tempNewRect, &tempNewOrigin](
                             const RectF& oldRect, const OffsetF& oldOrigin, const RectF& rect, const OffsetF& origin) {
        tempOldRect = oldRect;
        tempOldOrigin = oldOrigin;
        tempNewRect = rect;
        tempNewOrigin = origin;
    };

    eventHub->SetOnAreaChanged(onAreaChanged);
    eventHub->GetOrCreateGestureEventHub();
    eventHub->GetOrCreateInputEventHub();
    eventHub->GetOrCreateFocusHub();

    VisibleCallbackInfo callbackInfo;
    const std::function<void(bool, double)>&& jsCallback = [](bool isVisible, double radio) { flag++; };
    callbackInfo.callback = jsCallback;
    callbackInfo.period = MIN_INTERVAL;
    callbackInfo.period = 0;
    std::vector<double> ratios = { 0, 1.0 };
    eventHub->SetVisibleAreaRatiosAndCallback(callbackInfo, ratios, true);
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);

    auto context = MockPipelineContext::GetCurrent();
    eventHub->OnDetachContext(AceType::RawPtr(context));
    EXPECT_NE(eventHub->GetOrCreateGestureEventHub(), nullptr);
}

/**
 * @tc.name: EventHubTest009
 * @tc.desc: OnDetachContext
 * @tc.type: FUNC
 */
HWTEST_F(EventHubTestNg, EventHubTest009, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->GetOrCreateGestureEventHub();
    eventHub->GetOrCreateInputEventHub();
    eventHub->GetOrCreateFocusHub();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    bool flags = false;
    OnAreaChangedFunc onAreaChanged = [&flags](const RectF& oldRect, const OffsetF& oldOrigin, const RectF& rect,
                                          const OffsetF& origin) { flags = !flags; };
    eventHub->AddInnerOnAreaChangedCallback(1, std::move(onAreaChanged));
    VisibleCallbackInfo callbackInfo;
    const std::function<void(bool, double)>&& jsCallback = [](bool isVisible, double radio) { flag++; };
    callbackInfo.callback = jsCallback;
    callbackInfo.period = MIN_INTERVAL;
    std::vector<double> ratios = { 0, 1.0 };
    eventHub->SetVisibleAreaRatiosAndCallback(callbackInfo, ratios, false);
    auto context = MockPipelineContext::GetCurrent();
    eventHub->OnDetachContext(AceType::RawPtr(context));
    EXPECT_NE(eventHub->GetOrCreateGestureEventHub(), nullptr);
}

/**
 * @tc.name: EventHubTest010
 * @tc.desc: FireOnSizeChanged
 * @tc.type: FUNC
 */
HWTEST_F(EventHubTestNg, EventHubTest010, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    bool flags = false;
    OnSizeChangedFunc onSizeChanged = [&flags](const RectF& oldRect, const RectF& Rect) { flags = !flags; };
    RectF tempOldRect;
    RectF tempNewRect;
    eventHub->SetOnSizeChanged(std::move(onSizeChanged));
    eventHub->FireOnSizeChanged(tempOldRect, tempNewRect);
    EXPECT_NE(eventHub->GetOrCreateGestureEventHub(), nullptr);
}

/**
 * @tc.name: EventHubTest011
 * @tc.desc: FireOnSizeChanged
 * @tc.type: FUNC
 */
HWTEST_F(EventHubTestNg, EventHubTest011, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    RectF tempOldRect;
    RectF tempNewRect;
    eventHub->FireOnSizeChanged(tempOldRect, tempNewRect);
    EXPECT_NE(eventHub->GetOrCreateGestureEventHub(), nullptr);
}

/**
 * @tc.name: EventHubTest012
 * @tc.desc: FireJSFrameNodeOnSizeChanged
 * @tc.type: FUNC
 */
HWTEST_F(EventHubTestNg, EventHubTest012, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    bool flags = false;
    OnSizeChangedFunc onSizeChanged = [&flags](const RectF& oldRect, const RectF& Rect) { flags = !flags; };
    RectF tempOldRect;
    RectF tempNewRect;
    eventHub->SetJSFrameNodeOnSizeChangeCallback(std::move(onSizeChanged));
    eventHub->FireJSFrameNodeOnSizeChanged(tempOldRect, tempNewRect);
    EXPECT_NE(eventHub->GetOrCreateGestureEventHub(), nullptr);
}

/**
 * @tc.name: EventHubTest013
 * @tc.desc: FireJSFrameNodeOnSizeChanged
 * @tc.type: FUNC
 */
HWTEST_F(EventHubTestNg, EventHubTest013, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    RectF tempOldRect;
    RectF tempNewRect;
    eventHub->FireJSFrameNodeOnSizeChanged(tempOldRect, tempNewRect);
    EXPECT_NE(eventHub->GetOrCreateGestureEventHub(), nullptr);
}

/**
 * @tc.name: EventHubTest014
 * @tc.desc:ClearJSFrameNodeOnSizeChange
 * @tc.type: FUNC
 */
HWTEST_F(EventHubTestNg, EventHubTest014, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->ClearJSFrameNodeOnSizeChange();
    EXPECT_NE(eventHub->GetOrCreateGestureEventHub(), nullptr);
}

/**
 * @tc.name: EventHubTest015
 * @tc.desc: ClearJSFrameNodeOnSizeChange
 * @tc.type: FUNC
 */
HWTEST_F(EventHubTestNg, EventHubTest015, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    bool flags = false;
    OnSizeChangedFunc onSizeChanged = [&flags](const RectF& oldRect, const RectF& Rect) { flags = !flags; };
    eventHub->SetJSFrameNodeOnSizeChangeCallback(std::move(onSizeChanged));
    eventHub->ClearJSFrameNodeOnSizeChange();
    EXPECT_NE(eventHub->GetOrCreateGestureEventHub(), nullptr);
}

/**
 * @tc.name: EventHubTest016
 * @tc.desc: FireInnerOnSizeChanged
 * @tc.type: FUNC
 */
HWTEST_F(EventHubTestNg, EventHubTest016, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    bool flags = false;
    OnSizeChangedFunc onSizeChanged = [&flags](const RectF& oldRect, const RectF& Rect) { flags = !flags; };
    eventHub->AddInnerOnSizeChanged(1, std::move(onSizeChanged));
    eventHub->AddInnerOnSizeChanged(2, std::move(onSizeChanged));
    RectF tempOldRect;
    RectF tempNewRect;
    eventHub->FireInnerOnSizeChanged(tempOldRect, tempNewRect);
    EXPECT_NE(eventHub->GetOrCreateGestureEventHub(), nullptr);
}

/**
 * @tc.name: EventHubTest017
 * @tc.desc: FireInnerOnSizeChanged
 * @tc.type: FUNC
 */
HWTEST_F(EventHubTestNg, EventHubTest017, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    RectF tempOldRect;
    RectF tempNewRect;
    eventHub->FireInnerOnSizeChanged(tempOldRect, tempNewRect);
    EXPECT_NE(eventHub->GetOrCreateGestureEventHub(), nullptr);
}

/**
 * @tc.name: EventHubTest018
 * @tc.desc: FireOnAttach
 * @tc.type: FUNC
 */
HWTEST_F(EventHubTestNg, EventHubTest018, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    std::function<void()> onAttachCallback = []() {};
    eventHub->SetOnAttach(std::move(onAttachCallback));
    eventHub->FireOnAttach();
    EXPECT_NE(eventHub->GetOrCreateGestureEventHub(), nullptr);
}

/**
 * @tc.name: EventHubTest019
 * @tc.desc: FireOnAttach
 * @tc.type: FUNC
 */
HWTEST_F(EventHubTestNg, EventHubTest019, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    std::function<void()> onAttachCallback = []() {};
    eventHub->SetOnDetach(std::move(onAttachCallback));
    eventHub->FireOnDetach();
    EXPECT_NE(eventHub->GetOrCreateGestureEventHub(), nullptr);
}

/**
 * @tc.name: EventHubTest020
 * @tc.desc: debugEnabled_
 * @tc.type: FUNC
 */
HWTEST_F(EventHubTestNg, EventHubTest020, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    SystemProperties::debugEnabled_ = true;
    auto dragEvent = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    eventHub->FireOnDragEnter(dragEvent, DRAG_ENTER_EVENT_TYPE);
    eventHub->FireOnDragLeave(dragEvent, DRAG_ENTER_EVENT_TYPE);
    eventHub->FireOnDragMove(dragEvent, DRAG_ENTER_EVENT_TYPE);
    eventHub->FireOnDrop(dragEvent, DRAG_ENTER_EVENT_TYPE);
    EXPECT_NE(eventHub->GetOrCreateGestureEventHub(), nullptr);
}

/**
 * @tc.name: EventHubTest021
 * @tc.desc: FireOnWillBind
 * @tc.type: FUNC
 */
HWTEST_F(EventHubTestNg, EventHubTest021, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto nodeContainerId = frameNode->GetId();
    std::function<void(int32_t)> onWillBindCallback = [](int32_t) {};
    eventHub->SetOnWillBind(std::move(onWillBindCallback));
    eventHub->FireOnWillBind(nodeContainerId);
    EXPECT_NE(eventHub->GetOrCreateGestureEventHub(), nullptr);
}

/**
 * @tc.name: EventHubTest022
 * @tc.desc: FireOnWillUnbind
 * @tc.type: FUNC
 */
HWTEST_F(EventHubTestNg, EventHubTest022, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto nodeContainerId = frameNode->GetId();
    std::function<void(int32_t)> onWillUnbindCallback = [](int32_t) {};
    eventHub->SetOnWillUnbind(std::move(onWillUnbindCallback));
    eventHub->FireOnWillUnbind(nodeContainerId);
    EXPECT_NE(eventHub->GetOrCreateGestureEventHub(), nullptr);
}

/**
 * @tc.name: EventHubTest023
 * @tc.desc: FireOnBind
 * @tc.type: FUNC
 */
HWTEST_F(EventHubTestNg, EventHubTest023, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto nodeContainerId = frameNode->GetId();
    std::function<void(int32_t)> onBindCallback = [](int32_t) {};
    eventHub->SetOnBind(std::move(onBindCallback));
    eventHub->FireOnBind(nodeContainerId);
    EXPECT_NE(eventHub->GetOrCreateGestureEventHub(), nullptr);
}

/**
 * @tc.name: EventHubTest024
 * @tc.desc: FireOnUnbind
 * @tc.type: FUNC
 */
HWTEST_F(EventHubTestNg, EventHubTest024, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto nodeContainerId = frameNode->GetId();
    std::function<void(int32_t)> onUnbindCallback = [](int32_t) {};
    eventHub->SetOnUnbind(std::move(onUnbindCallback));
    eventHub->FireOnUnbind(nodeContainerId);
    EXPECT_NE(eventHub->GetOrCreateGestureEventHub(), nullptr);
}
} // namespace OHOS::Ace::NG
