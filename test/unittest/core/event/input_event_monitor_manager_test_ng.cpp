/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/common/mock_container.h"

#include "base/memory/ace_type.h"
#include "core/components_ng/base/frame_node.h"
#include "frameworks/core/common/event_manager.h"
#include "frameworks/core/common/input_event_monitor_manager.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr uint32_t INVALID_MASK = 1u << 20;
RefPtr<MockTaskExecutor> g_mockTaskExecutor;

InputEventListenerCallback g_continueHandler =
    [](const RawInputEventWrapper&) { return InputEventInterceptAction::CONTINUE; };
InputEventListenerCallback g_blockHandler =
    [](const RawInputEventWrapper&) { return InputEventInterceptAction::BLOCK; };
} // namespace

class InputEventMonitorManagerTestNg : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockContainer::SetUp();
        MockContainer::Current()->pipelineContext_ = nullptr;
        g_mockTaskExecutor = AceType::MakeRefPtr<MockTaskExecutor>();
    }

    static void TearDownTestSuite()
    {
        MockContainer::TearDown();
    }
};

/**
 * @tc.name: RawInputEventWrapperTest001
 * @tc.desc: Verify wrapper type and getter methods.
 * @tc.type: FUNC
 */
HWTEST_F(InputEventMonitorManagerTestNg, RawInputEventWrapperTest001, TestSize.Level1)
{
    MouseEvent mouseEvent;
    RawInputEventWrapper mouseWrapper(mouseEvent);
    EXPECT_TRUE(mouseWrapper.IsMouseEvent());
    EXPECT_FALSE(mouseWrapper.IsTouchEvent());
    EXPECT_FALSE(mouseWrapper.IsKeyEvent());
    EXPECT_NE(mouseWrapper.GetMouseEvent(), nullptr);
    EXPECT_EQ(mouseWrapper.GetTouchEvent(), nullptr);
    EXPECT_EQ(mouseWrapper.GetKeyEvent(), nullptr);

    TouchEvent touchEvent;
    RawInputEventWrapper touchWrapper(touchEvent);
    EXPECT_TRUE(touchWrapper.IsTouchEvent());
    EXPECT_NE(touchWrapper.GetTouchEvent(), nullptr);
    EXPECT_EQ(touchWrapper.GetMouseEvent(), nullptr);
    EXPECT_EQ(touchWrapper.GetKeyEvent(), nullptr);

    KeyEvent keyEvent;
    RawInputEventWrapper keyWrapper(keyEvent);
    EXPECT_TRUE(keyWrapper.IsKeyEvent());
    EXPECT_NE(keyWrapper.GetKeyEvent(), nullptr);
    EXPECT_EQ(keyWrapper.GetMouseEvent(), nullptr);
    EXPECT_EQ(keyWrapper.GetTouchEvent(), nullptr);
}

/**
 * @tc.name: InputEventMonitorManagerTest001
 * @tc.desc: Verify add/remove monitor with valid and invalid parameters.
 * @tc.type: FUNC
 */
HWTEST_F(InputEventMonitorManagerTestNg, InputEventMonitorManagerTest001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<InputEventMonitorManager>();
    ASSERT_NE(manager, nullptr);

    EXPECT_EQ(manager->AddLocalInputMonitor(
        static_cast<uint32_t>(InputEventSubTypeMask::NONE), g_continueHandler), nullptr);
    EXPECT_EQ(manager->AddLocalInputMonitor(INVALID_MASK, g_continueHandler), nullptr);

    InputEventListenerCallback nullHandler;
    EXPECT_EQ(manager->AddLocalInputMonitor(
        static_cast<uint32_t>(InputEventSubTypeMask::KEY_DOWN), nullHandler), nullptr);

    auto identity = manager->AddLocalInputMonitor(
        static_cast<uint32_t>(InputEventSubTypeMask::KEY_DOWN), g_continueHandler);
    ASSERT_NE(identity, nullptr);
    EXPECT_EQ(manager->monitors_.size(), 1);

    manager->RemoveLocalInputMonitor(nullptr);
    EXPECT_EQ(manager->monitors_.size(), 1);

    manager->RemoveLocalInputMonitor(identity);
    EXPECT_TRUE(manager->monitors_.empty());
}

/**
 * @tc.name: InputEventMonitorManagerTest002
 * @tc.desc: Cover mouse monitor processing branches.
 * @tc.type: FUNC
 */
HWTEST_F(InputEventMonitorManagerTestNg, InputEventMonitorManagerTest002, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<InputEventMonitorManager>();
    ASSERT_NE(manager, nullptr);

    MouseEvent emptyMouse;
    emptyMouse.action = MouseAction::PRESS;
    emptyMouse.button = MouseButton::LEFT_BUTTON;
    EXPECT_FALSE(manager->ProcessMouseEvent(emptyMouse));

    ASSERT_NE(manager->AddLocalInputMonitor(
        static_cast<uint32_t>(InputEventSubTypeMask::TOUCH_DOWN), g_continueHandler), nullptr);

    MouseEvent moveNone;
    moveNone.action = MouseAction::MOVE;
    moveNone.button = MouseButton::NONE_BUTTON;
    moveNone.deviceId = 11;
    EXPECT_FALSE(manager->ProcessMouseEvent(moveNone));

    MouseEvent pressContinue;
    pressContinue.action = MouseAction::PRESS;
    pressContinue.button = MouseButton::LEFT_BUTTON;
    pressContinue.deviceId = 11;
    EXPECT_FALSE(manager->ProcessMouseEvent(pressContinue));
    auto mouseKey = manager->GetMouseInteractionId(pressContinue);
    EXPECT_TRUE(manager->mouseTracker_.IsDownEventDelivered(mouseKey));

    MouseEvent leave = pressContinue;
    leave.action = MouseAction::WINDOW_LEAVE;
    EXPECT_FALSE(manager->ProcessMouseEvent(leave));
    EXPECT_FALSE(manager->mouseTracker_.IsDownEventDelivered(mouseKey));

    auto managerBlockPress = AceType::MakeRefPtr<InputEventMonitorManager>();
    ASSERT_NE(managerBlockPress, nullptr);
    ASSERT_NE(managerBlockPress->AddLocalInputMonitor(
        static_cast<uint32_t>(InputEventSubTypeMask::LEFT_MOUSE_DOWN), g_blockHandler), nullptr);

    MouseEvent pressBlocked;
    pressBlocked.action = MouseAction::PRESS;
    pressBlocked.button = MouseButton::LEFT_BUTTON;
    pressBlocked.deviceId = 12;
    EXPECT_TRUE(managerBlockPress->ProcessMouseEvent(pressBlocked));

    MouseEvent moveBlocked = pressBlocked;
    moveBlocked.action = MouseAction::MOVE;
    EXPECT_TRUE(managerBlockPress->ProcessMouseEvent(moveBlocked));

    MouseEvent releaseBlocked = pressBlocked;
    releaseBlocked.action = MouseAction::RELEASE;
    EXPECT_TRUE(managerBlockPress->ProcessMouseEvent(releaseBlocked));
    EXPECT_FALSE(releaseBlocked.isFalsifyCancel);

    auto managerBlockRelease = AceType::MakeRefPtr<InputEventMonitorManager>();
    ASSERT_NE(managerBlockRelease, nullptr);
    ASSERT_NE(managerBlockRelease->AddLocalInputMonitor(
        static_cast<uint32_t>(InputEventSubTypeMask::LEFT_MOUSE_UP), g_blockHandler), nullptr);

    MouseEvent press;
    press.action = MouseAction::PRESS;
    press.button = MouseButton::LEFT_BUTTON;
    press.deviceId = 13;
    EXPECT_FALSE(managerBlockRelease->ProcessMouseEvent(press));

    MouseEvent release = press;
    release.action = MouseAction::RELEASE;
    EXPECT_TRUE(managerBlockRelease->ProcessMouseEvent(release));
    EXPECT_EQ(release.action, MouseAction::CANCEL);
    EXPECT_TRUE(release.isFalsifyCancel);

    MouseEvent cancelEvent = press;
    cancelEvent.action = MouseAction::CANCEL;
    EXPECT_FALSE(managerBlockRelease->ProcessMouseEvent(cancelEvent));
}

/**
 * @tc.name: InputEventMonitorManagerTest003
 * @tc.desc: Cover touch monitor processing branches.
 * @tc.type: FUNC
 */
HWTEST_F(InputEventMonitorManagerTestNg, InputEventMonitorManagerTest003, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<InputEventMonitorManager>();
    ASSERT_NE(manager, nullptr);

    ASSERT_NE(manager->AddLocalInputMonitor(
        static_cast<uint32_t>(InputEventSubTypeMask::KEY_DOWN), g_continueHandler), nullptr);

    TouchEvent moveEvent;
    moveEvent.type = TouchType::MOVE;
    moveEvent.deviceId = 21;
    moveEvent.id = 1;
    EXPECT_FALSE(manager->ProcessTouchEvent(moveEvent));

    TouchEvent downEvent;
    downEvent.type = TouchType::DOWN;
    downEvent.deviceId = 21;
    downEvent.id = 1;
    EXPECT_FALSE(manager->ProcessTouchEvent(downEvent));

    TouchEvent cancelEvent = downEvent;
    cancelEvent.type = TouchType::CANCEL;
    EXPECT_FALSE(manager->ProcessTouchEvent(cancelEvent));

    auto managerBlockDown = AceType::MakeRefPtr<InputEventMonitorManager>();
    ASSERT_NE(managerBlockDown, nullptr);
    ASSERT_NE(managerBlockDown->AddLocalInputMonitor(
        static_cast<uint32_t>(InputEventSubTypeMask::TOUCH_DOWN), g_blockHandler), nullptr);

    TouchEvent downBlocked;
    downBlocked.type = TouchType::DOWN;
    downBlocked.deviceId = 22;
    downBlocked.id = 2;
    EXPECT_TRUE(managerBlockDown->ProcessTouchEvent(downBlocked));

    TouchEvent moveBlocked = downBlocked;
    moveBlocked.type = TouchType::MOVE;
    EXPECT_TRUE(managerBlockDown->ProcessTouchEvent(moveBlocked));

    TouchEvent upBlocked = downBlocked;
    upBlocked.type = TouchType::UP;
    EXPECT_TRUE(managerBlockDown->ProcessTouchEvent(upBlocked));
    EXPECT_FALSE(upBlocked.isFalsified);

    auto managerBlockUp = AceType::MakeRefPtr<InputEventMonitorManager>();
    ASSERT_NE(managerBlockUp, nullptr);
    ASSERT_NE(managerBlockUp->AddLocalInputMonitor(
        static_cast<uint32_t>(InputEventSubTypeMask::TOUCH_UP), g_blockHandler), nullptr);

    TouchEvent down;
    down.type = TouchType::DOWN;
    down.deviceId = 23;
    down.id = 3;
    EXPECT_FALSE(managerBlockUp->ProcessTouchEvent(down));

    TouchEvent up = down;
    up.type = TouchType::UP;
    EXPECT_TRUE(managerBlockUp->ProcessTouchEvent(up));
    EXPECT_EQ(up.type, TouchType::CANCEL);
    EXPECT_TRUE(up.isFalsified);
}

/**
 * @tc.name: InputEventMonitorManagerTest004
 * @tc.desc: Cover key monitor processing branches.
 * @tc.type: FUNC
 */
HWTEST_F(InputEventMonitorManagerTestNg, InputEventMonitorManagerTest004, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<InputEventMonitorManager>();
    ASSERT_NE(manager, nullptr);

    ASSERT_NE(manager->AddLocalInputMonitor(
        static_cast<uint32_t>(InputEventSubTypeMask::TOUCH_DOWN), g_continueHandler), nullptr);

    KeyEvent longPressEvent;
    longPressEvent.code = KeyCode::KEY_A;
    longPressEvent.action = KeyAction::LONG_PRESS;
    longPressEvent.deviceId = 31;
    EXPECT_FALSE(manager->ProcessKeyEvent(longPressEvent));

    KeyEvent downEvent;
    downEvent.code = KeyCode::KEY_A;
    downEvent.action = KeyAction::DOWN;
    downEvent.deviceId = 31;
    EXPECT_FALSE(manager->ProcessKeyEvent(downEvent));

    KeyEvent cancelEvent = downEvent;
    cancelEvent.action = KeyAction::CANCEL;
    EXPECT_FALSE(manager->ProcessKeyEvent(cancelEvent));

    auto managerBlockDown = AceType::MakeRefPtr<InputEventMonitorManager>();
    ASSERT_NE(managerBlockDown, nullptr);
    ASSERT_NE(managerBlockDown->AddLocalInputMonitor(
        static_cast<uint32_t>(InputEventSubTypeMask::KEY_DOWN), g_blockHandler), nullptr);

    KeyEvent downBlocked;
    downBlocked.code = KeyCode::KEY_B;
    downBlocked.action = KeyAction::DOWN;
    downBlocked.deviceId = 32;
    EXPECT_TRUE(managerBlockDown->ProcessKeyEvent(downBlocked));

    KeyEvent upBlocked = downBlocked;
    upBlocked.action = KeyAction::UP;
    EXPECT_TRUE(managerBlockDown->ProcessKeyEvent(upBlocked));
    EXPECT_FALSE(upBlocked.isFalsifyCancel);

    auto managerBlockUp = AceType::MakeRefPtr<InputEventMonitorManager>();
    ASSERT_NE(managerBlockUp, nullptr);
    ASSERT_NE(managerBlockUp->AddLocalInputMonitor(
        static_cast<uint32_t>(InputEventSubTypeMask::KEY_UP), g_blockHandler), nullptr);

    KeyEvent down;
    down.code = KeyCode::KEY_C;
    down.action = KeyAction::DOWN;
    down.deviceId = 33;
    EXPECT_FALSE(managerBlockUp->ProcessKeyEvent(down));

    KeyEvent up = down;
    up.action = KeyAction::UP;
    up.isPreIme = true;
    EXPECT_TRUE(managerBlockUp->ProcessKeyEvent(up));
    EXPECT_EQ(up.action, KeyAction::CANCEL);
    EXPECT_TRUE(up.isFalsifyCancel);
    EXPECT_FALSE(up.isPreIme);
}

/**
 * @tc.name: InputEventMonitorManagerTest005
 * @tc.desc: Cover remaining mouse branches: valid MOVE continue/block and RELEASE continue/block(no down).
 * @tc.type: FUNC
 */
HWTEST_F(InputEventMonitorManagerTestNg, InputEventMonitorManagerTest005, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<InputEventMonitorManager>();
    ASSERT_NE(manager, nullptr);

    ASSERT_NE(manager->AddLocalInputMonitor(static_cast<uint32_t>(InputEventSubTypeMask::LEFT_MOUSE_DRAGGING),
        g_continueHandler), nullptr);
    ASSERT_NE(manager->AddLocalInputMonitor(static_cast<uint32_t>(InputEventSubTypeMask::RIGHT_MOUSE_DRAGGING),
        g_blockHandler), nullptr);
    ASSERT_NE(manager->AddLocalInputMonitor(static_cast<uint32_t>(InputEventSubTypeMask::MIDDLE_MOUSE_UP),
        g_continueHandler), nullptr);

    MouseEvent pressNone;
    pressNone.action = MouseAction::PRESS;
    pressNone.button = MouseButton::NONE_BUTTON;
    pressNone.deviceId = 51;
    EXPECT_FALSE(manager->ProcessMouseEvent(pressNone));

    MouseEvent moveLeft;
    moveLeft.action = MouseAction::MOVE;
    moveLeft.button = MouseButton::LEFT_BUTTON;
    moveLeft.deviceId = 52;
    EXPECT_FALSE(manager->ProcessMouseEvent(moveLeft));

    MouseEvent moveRight = moveLeft;
    moveRight.button = MouseButton::RIGHT_BUTTON;
    EXPECT_TRUE(manager->ProcessMouseEvent(moveRight));

    MouseEvent pressMiddle;
    pressMiddle.action = MouseAction::PRESS;
    pressMiddle.button = MouseButton::MIDDLE_BUTTON;
    pressMiddle.deviceId = 53;
    EXPECT_FALSE(manager->ProcessMouseEvent(pressMiddle));

    MouseEvent releaseMiddle = pressMiddle;
    releaseMiddle.action = MouseAction::RELEASE;
    EXPECT_FALSE(manager->ProcessMouseEvent(releaseMiddle));

    auto managerBlockUpOnly = AceType::MakeRefPtr<InputEventMonitorManager>();
    ASSERT_NE(managerBlockUpOnly, nullptr);
    ASSERT_NE(managerBlockUpOnly->AddLocalInputMonitor(
        static_cast<uint32_t>(InputEventSubTypeMask::RIGHT_MOUSE_UP), g_blockHandler), nullptr);

    MouseEvent releaseOnly;
    releaseOnly.action = MouseAction::RELEASE;
    releaseOnly.button = MouseButton::RIGHT_BUTTON;
    releaseOnly.deviceId = 54;
    EXPECT_TRUE(managerBlockUpOnly->ProcessMouseEvent(releaseOnly));
    EXPECT_FALSE(releaseOnly.isFalsifyCancel);
}

/**
 * @tc.name: InputEventMonitorManagerTest006
 * @tc.desc: Cover remaining touch branches: UP continue and UP block without DOWN delivered.
 * @tc.type: FUNC
 */
HWTEST_F(InputEventMonitorManagerTestNg, InputEventMonitorManagerTest006, TestSize.Level1)
{
    auto managerContinue = AceType::MakeRefPtr<InputEventMonitorManager>();
    ASSERT_NE(managerContinue, nullptr);
    ASSERT_NE(managerContinue->AddLocalInputMonitor(
        static_cast<uint32_t>(InputEventSubTypeMask::TOUCH_UP), g_continueHandler), nullptr);

    TouchEvent down;
    down.type = TouchType::DOWN;
    down.deviceId = 61;
    down.id = 6;
    EXPECT_FALSE(managerContinue->ProcessTouchEvent(down));

    TouchEvent up = down;
    up.type = TouchType::UP;
    EXPECT_FALSE(managerContinue->ProcessTouchEvent(up));

    auto managerBlockUpOnly = AceType::MakeRefPtr<InputEventMonitorManager>();
    ASSERT_NE(managerBlockUpOnly, nullptr);
    ASSERT_NE(managerBlockUpOnly->AddLocalInputMonitor(
        static_cast<uint32_t>(InputEventSubTypeMask::TOUCH_UP), g_blockHandler), nullptr);

    TouchEvent upOnly;
    upOnly.type = TouchType::UP;
    upOnly.deviceId = 62;
    upOnly.id = 7;
    EXPECT_TRUE(managerBlockUpOnly->ProcessTouchEvent(upOnly));
    EXPECT_FALSE(upOnly.isFalsified);
}

/**
 * @tc.name: InputEventMonitorManagerTest007
 * @tc.desc: Cover remaining key branches: UP continue and UP block without DOWN delivered.
 * @tc.type: FUNC
 */
HWTEST_F(InputEventMonitorManagerTestNg, InputEventMonitorManagerTest007, TestSize.Level1)
{
    auto managerContinue = AceType::MakeRefPtr<InputEventMonitorManager>();
    ASSERT_NE(managerContinue, nullptr);
    ASSERT_NE(managerContinue->AddLocalInputMonitor(
        static_cast<uint32_t>(InputEventSubTypeMask::KEY_UP), g_continueHandler), nullptr);

    KeyEvent down;
    down.code = KeyCode::KEY_F;
    down.action = KeyAction::DOWN;
    down.deviceId = 71;
    EXPECT_FALSE(managerContinue->ProcessKeyEvent(down));

    KeyEvent up = down;
    up.action = KeyAction::UP;
    EXPECT_FALSE(managerContinue->ProcessKeyEvent(up));

    auto managerBlockUpOnly = AceType::MakeRefPtr<InputEventMonitorManager>();
    ASSERT_NE(managerBlockUpOnly, nullptr);
    ASSERT_NE(managerBlockUpOnly->AddLocalInputMonitor(
        static_cast<uint32_t>(InputEventSubTypeMask::KEY_UP), g_blockHandler), nullptr);

    KeyEvent upOnly;
    upOnly.code = KeyCode::KEY_G;
    upOnly.action = KeyAction::UP;
    upOnly.deviceId = 72;
    EXPECT_TRUE(managerBlockUpOnly->ProcessKeyEvent(upOnly));
    EXPECT_FALSE(upOnly.isFalsifyCancel);
}

/**
 * @tc.name: EventManagerInputMonitorInterceptTest001
 * @tc.desc: Verify key interception path in EventManager::OnNonPointerEvent.
 * @tc.type: FUNC
 */
HWTEST_F(InputEventMonitorManagerTestNg, EventManagerInputMonitorInterceptTest001, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);
    ASSERT_NE(eventManager->inputMonitorManager_, nullptr);

    auto identity = eventManager->inputMonitorManager_->AddLocalInputMonitor(
        static_cast<uint32_t>(InputEventSubTypeMask::KEY_DOWN), g_blockHandler);
    ASSERT_NE(identity, nullptr);

    KeyEvent down;
    down.code = KeyCode::KEY_D;
    down.action = KeyAction::DOWN;
    down.deviceId = 41;
    EXPECT_TRUE(eventManager->OnNonPointerEvent(down));

    eventManager->inputMonitorManager_->RemoveLocalInputMonitor(identity);
    identity = eventManager->inputMonitorManager_->AddLocalInputMonitor(
        static_cast<uint32_t>(InputEventSubTypeMask::KEY_UP), g_blockHandler);
    ASSERT_NE(identity, nullptr);

    down.code = KeyCode::KEY_E;
    down.action = KeyAction::DOWN;
    down.deviceId = 42;
    EXPECT_FALSE(eventManager->OnNonPointerEvent(down));

    KeyEvent up = down;
    up.action = KeyAction::UP;
    EXPECT_FALSE(eventManager->OnNonPointerEvent(up));
}

/**
 * @tc.name: InteractionTrackerDirectTest001
 * @tc.desc: Direct test of InteractionTracker methods.
 * @tc.type: FUNC
 */
HWTEST_F(InputEventMonitorManagerTestNg, InteractionTrackerDirectTest001, TestSize.Level1)
{
    InteractionTracker tracker;
    constexpr uint64_t key1 = 100;
    constexpr uint64_t key2 = 200;

    /**
     * @tc.steps: step1. Initially no interactions.
     * @tc.expected: IsDownEventDelivered and IsDownEventBlocked return false.
     */
    EXPECT_FALSE(tracker.IsDownEventDelivered(key1));
    EXPECT_FALSE(tracker.IsDownEventBlocked(key1));

    /**
     * @tc.steps: step2. OnDownEvent and verify.
     * @tc.expected: IsDownEventDelivered true, IsDownEventBlocked false.
     */
    tracker.OnDownEvent(key1);
    EXPECT_TRUE(tracker.IsDownEventDelivered(key1));
    EXPECT_FALSE(tracker.IsDownEventBlocked(key1));

    /**
     * @tc.steps: step3. OnDownEventBlocked and verify.
     * @tc.expected: IsDownEventBlocked true, IsDownEventDelivered false.
     */
    tracker.OnDownEventBlocked(key2);
    EXPECT_TRUE(tracker.IsDownEventBlocked(key2));
    EXPECT_FALSE(tracker.IsDownEventDelivered(key2));

    /**
     * @tc.steps: step4. EndInteraction and verify cleanup.
     * @tc.expected: Both return false after EndInteraction.
     */
    tracker.EndInteraction(key1);
    EXPECT_FALSE(tracker.IsDownEventDelivered(key1));
    EXPECT_FALSE(tracker.IsDownEventBlocked(key1));

    tracker.EndInteraction(key2);
    EXPECT_FALSE(tracker.IsDownEventDelivered(key2));
    EXPECT_FALSE(tracker.IsDownEventBlocked(key2));

    /**
     * @tc.steps: step5. EndInteraction on non-existent key.
     * @tc.expected: No state change, IsDownEventDelivered and IsDownEventBlocked still return false.
     */
    tracker.EndInteraction(999);
    EXPECT_FALSE(tracker.IsDownEventDelivered(999));
    EXPECT_FALSE(tracker.IsDownEventBlocked(999));
    EXPECT_FALSE(tracker.IsDownEventDelivered(key1));
    EXPECT_FALSE(tracker.IsDownEventBlocked(key1));
}

/**
 * @tc.name: GetSubTypeMaskMouseFullTest001
 * @tc.desc: Cover all MouseEvent GetSubTypeMask branches.
 * @tc.type: FUNC
 */
HWTEST_F(InputEventMonitorManagerTestNg, GetSubTypeMaskMouseFullTest001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<InputEventMonitorManager>();
    ASSERT_NE(manager, nullptr);

    /**
     * @tc.steps: step1. RIGHT_MOUSE_DOWN.
     */
    MouseEvent rightPress;
    rightPress.action = MouseAction::PRESS;
    rightPress.button = MouseButton::RIGHT_BUTTON;
    EXPECT_EQ(manager->GetSubTypeMask(rightPress), InputEventSubTypeMask::RIGHT_MOUSE_DOWN);

    /**
     * @tc.steps: step2. MIDDLE_MOUSE_DOWN.
     */
    MouseEvent middlePress;
    middlePress.action = MouseAction::PRESS;
    middlePress.button = MouseButton::MIDDLE_BUTTON;
    EXPECT_EQ(manager->GetSubTypeMask(middlePress), InputEventSubTypeMask::MIDDLE_MOUSE_DOWN);

    /**
     * @tc.steps: step3. RIGHT_MOUSE_UP.
     */
    MouseEvent rightRelease;
    rightRelease.action = MouseAction::RELEASE;
    rightRelease.button = MouseButton::RIGHT_BUTTON;
    EXPECT_EQ(manager->GetSubTypeMask(rightRelease), InputEventSubTypeMask::RIGHT_MOUSE_UP);

    /**
     * @tc.steps: step4. MIDDLE_MOUSE_UP.
     */
    MouseEvent middleRelease;
    middleRelease.action = MouseAction::RELEASE;
    middleRelease.button = MouseButton::MIDDLE_BUTTON;
    EXPECT_EQ(manager->GetSubTypeMask(middleRelease), InputEventSubTypeMask::MIDDLE_MOUSE_UP);

    /**
     * @tc.steps: step5. LEFT_MOUSE_DRAGGING.
     */
    MouseEvent leftMove;
    leftMove.action = MouseAction::MOVE;
    leftMove.button = MouseButton::LEFT_BUTTON;
    EXPECT_EQ(manager->GetSubTypeMask(leftMove), InputEventSubTypeMask::LEFT_MOUSE_DRAGGING);

    /**
     * @tc.steps: step6. MIDDLE_MOUSE_DRAGGING.
     */
    MouseEvent middleMove;
    middleMove.action = MouseAction::MOVE;
    middleMove.button = MouseButton::MIDDLE_BUTTON;
    EXPECT_EQ(manager->GetSubTypeMask(middleMove), InputEventSubTypeMask::MIDDLE_MOUSE_DRAGGING);

    /**
     * @tc.steps: step7. PRESS with NONE_BUTTON returns NONE.
     */
    MouseEvent nonePress;
    nonePress.action = MouseAction::PRESS;
    nonePress.button = MouseButton::NONE_BUTTON;
    EXPECT_EQ(manager->GetSubTypeMask(nonePress), InputEventSubTypeMask::NONE);

    /**
     * @tc.steps: step8. RELEASE with NONE_BUTTON returns NONE.
     */
    MouseEvent noneRelease;
    noneRelease.action = MouseAction::RELEASE;
    noneRelease.button = MouseButton::NONE_BUTTON;
    EXPECT_EQ(manager->GetSubTypeMask(noneRelease), InputEventSubTypeMask::NONE);

    /**
     * @tc.steps: step9. Unknown action returns NONE.
     */
    MouseEvent unknownAction;
    unknownAction.action = MouseAction::WINDOW_LEAVE;
    unknownAction.button = MouseButton::LEFT_BUTTON;
    EXPECT_EQ(manager->GetSubTypeMask(unknownAction), InputEventSubTypeMask::NONE);
}

/**
 * @tc.name: GetSubTypeMaskTouchKeyDefaultTest001
 * @tc.desc: Cover TouchEvent and KeyEvent GetSubTypeMask default branches.
 * @tc.type: FUNC
 */
HWTEST_F(InputEventMonitorManagerTestNg, GetSubTypeMaskTouchKeyDefaultTest001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<InputEventMonitorManager>();
    ASSERT_NE(manager, nullptr);

    /**
     * @tc.steps: step1. TouchEvent MOVE returns NONE.
     */
    TouchEvent moveEvent;
    moveEvent.type = TouchType::MOVE;
    EXPECT_EQ(manager->GetSubTypeMask(moveEvent), InputEventSubTypeMask::NONE);

    /**
     * @tc.steps: step2. TouchEvent CANCEL returns NONE.
     */
    TouchEvent cancelTouch;
    cancelTouch.type = TouchType::CANCEL;
    EXPECT_EQ(manager->GetSubTypeMask(cancelTouch), InputEventSubTypeMask::NONE);

    /**
     * @tc.steps: step3. KeyEvent LONG_PRESS returns NONE.
     */
    KeyEvent longPress;
    longPress.action = KeyAction::LONG_PRESS;
    EXPECT_EQ(manager->GetSubTypeMask(longPress), InputEventSubTypeMask::NONE);

    /**
     * @tc.steps: step4. KeyEvent CANCEL returns NONE.
     */
    KeyEvent cancelKey;
    cancelKey.action = KeyAction::CANCEL;
    EXPECT_EQ(manager->GetSubTypeMask(cancelKey), InputEventSubTypeMask::NONE);
}

/**
 * @tc.name: InteractionIdTest001
 * @tc.desc: Test GetMouseInteractionId, GetTouchInteractionId, GetKeyInteractionId.
 * @tc.type: FUNC
 */
HWTEST_F(InputEventMonitorManagerTestNg, InteractionIdTest001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<InputEventMonitorManager>();
    ASSERT_NE(manager, nullptr);

    /**
     * @tc.steps: step1. GetMouseInteractionId with same deviceId/button gives same id.
     */
    MouseEvent mouse1;
    mouse1.deviceId = 42;
    mouse1.button = MouseButton::LEFT_BUTTON;
    auto id1 = manager->GetMouseInteractionId(mouse1);

    MouseEvent mouse2;
    mouse2.deviceId = 42;
    mouse2.button = MouseButton::LEFT_BUTTON;
    auto id2 = manager->GetMouseInteractionId(mouse2);
    EXPECT_EQ(id1, id2);

    /**
     * @tc.steps: step2. Different button gives different id.
     */
    mouse2.button = MouseButton::RIGHT_BUTTON;
    auto id3 = manager->GetMouseInteractionId(mouse2);
    EXPECT_NE(id1, id3);

    /**
     * @tc.steps: step3. GetTouchInteractionId with same deviceId/id gives same id.
     */
    TouchEvent touch1;
    touch1.deviceId = 10;
    touch1.id = 5;
    auto touchId1 = manager->GetTouchInteractionId(touch1);

    TouchEvent touch2;
    touch2.deviceId = 10;
    touch2.id = 5;
    auto touchId2 = manager->GetTouchInteractionId(touch2);
    EXPECT_EQ(touchId1, touchId2);

    /**
     * @tc.steps: step4. GetKeyInteractionId with same deviceId/code gives same id.
     */
    KeyEvent key1;
    key1.deviceId = 7;
    key1.code = KeyCode::KEY_A;
    auto keyId1 = manager->GetKeyInteractionId(key1);

    KeyEvent key2;
    key2.deviceId = 7;
    key2.code = KeyCode::KEY_A;
    auto keyId2 = manager->GetKeyInteractionId(key2);
    EXPECT_EQ(keyId1, keyId2);
}

/**
 * @tc.name: IsValidEventMaskTest001
 * @tc.desc: Test IsValidEventMask with various inputs.
 * @tc.type: FUNC
 */
HWTEST_F(InputEventMonitorManagerTestNg, IsValidEventMaskTest001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<InputEventMonitorManager>();
    ASSERT_NE(manager, nullptr);

    /**
     * @tc.steps: step1. NONE mask is invalid.
     */
    EXPECT_FALSE(manager->IsValidEventMask(static_cast<uint32_t>(InputEventSubTypeMask::NONE)));

    /**
     * @tc.steps: step2. Valid single mask.
     */
    EXPECT_TRUE(manager->IsValidEventMask(
        static_cast<uint32_t>(InputEventSubTypeMask::LEFT_MOUSE_DOWN)));

    /**
     * @tc.steps: step3. Valid combined mask.
     */
    EXPECT_TRUE(manager->IsValidEventMask(
        static_cast<uint32_t>(InputEventSubTypeMask::KEY_DOWN) |
        static_cast<uint32_t>(InputEventSubTypeMask::KEY_UP)));

    /**
     * @tc.steps: step4. Mask with bits outside valid set is invalid.
     */
    EXPECT_FALSE(manager->IsValidEventMask(INVALID_MASK));
}

/**
 * @tc.name: RunMonitorChainTest001
 * @tc.desc: Test RunMonitorChain directly.
 * @tc.type: FUNC
 */
HWTEST_F(InputEventMonitorManagerTestNg, RunMonitorChainTest001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<InputEventMonitorManager>();
    ASSERT_NE(manager, nullptr);

    /**
     * @tc.steps: step1. RunMonitorChain with NONE sub-type.
     * @tc.expected: Returns CONTINUE (invalid mask).
     */
    MouseEvent mouseEvent;
    mouseEvent.action = MouseAction::PRESS;
    mouseEvent.button = MouseButton::LEFT_BUTTON;
    RawInputEventWrapper wrapper(mouseEvent);
    EXPECT_EQ(manager->RunMonitorChain(InputEventSubTypeMask::NONE, wrapper),
        InputEventInterceptAction::CONTINUE);

    /**
     * @tc.steps: step2. Add a CONTINUE monitor, verify chain returns CONTINUE.
     */
    ASSERT_NE(manager->AddLocalInputMonitor(
        static_cast<uint32_t>(InputEventSubTypeMask::LEFT_MOUSE_DOWN), g_continueHandler), nullptr);
    EXPECT_EQ(manager->RunMonitorChain(InputEventSubTypeMask::LEFT_MOUSE_DOWN, wrapper),
        InputEventInterceptAction::CONTINUE);

    /**
     * @tc.steps: step3. Add a BLOCK monitor for the same mask.
     * @tc.expected: Chain returns BLOCK (BLOCK takes priority).
     */
    ASSERT_NE(manager->AddLocalInputMonitor(
        static_cast<uint32_t>(InputEventSubTypeMask::LEFT_MOUSE_DOWN), g_blockHandler), nullptr);
    EXPECT_EQ(manager->RunMonitorChain(InputEventSubTypeMask::LEFT_MOUSE_DOWN, wrapper),
        InputEventInterceptAction::BLOCK);
}

/**
 * @tc.name: ProcessMouseEventRightMiddleDownBlock001
 * @tc.desc: Test ProcessMouseEvent with RIGHT_MOUSE_DOWN and MIDDLE_MOUSE_DOWN block.
 * @tc.type: FUNC
 */
HWTEST_F(InputEventMonitorManagerTestNg, ProcessMouseEventRightMiddleDownBlock001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set up monitor for RIGHT_MOUSE_DOWN block.
     */
    auto manager = AceType::MakeRefPtr<InputEventMonitorManager>();
    ASSERT_NE(manager, nullptr);
    ASSERT_NE(manager->AddLocalInputMonitor(
        static_cast<uint32_t>(InputEventSubTypeMask::RIGHT_MOUSE_DOWN), g_blockHandler), nullptr);

    /**
     * @tc.steps: step2. RIGHT_MOUSE_DOWN is blocked.
     * @tc.expected: Returns true.
     */
    MouseEvent rightPress;
    rightPress.action = MouseAction::PRESS;
    rightPress.button = MouseButton::RIGHT_BUTTON;
    rightPress.deviceId = 81;
    EXPECT_TRUE(manager->ProcessMouseEvent(rightPress));

    /**
     * @tc.steps: step3. Set up monitor for MIDDLE_MOUSE_DOWN block.
     */
    auto manager2 = AceType::MakeRefPtr<InputEventMonitorManager>();
    ASSERT_NE(manager2, nullptr);
    ASSERT_NE(manager2->AddLocalInputMonitor(
        static_cast<uint32_t>(InputEventSubTypeMask::MIDDLE_MOUSE_DOWN), g_blockHandler), nullptr);

    /**
     * @tc.steps: step4. MIDDLE_MOUSE_DOWN is blocked.
     */
    MouseEvent middlePress;
    middlePress.action = MouseAction::PRESS;
    middlePress.button = MouseButton::MIDDLE_BUTTON;
    middlePress.deviceId = 82;
    EXPECT_TRUE(manager2->ProcessMouseEvent(middlePress));
}

/**
 * @tc.name: ProcessMouseEventRightUpWithDown001
 * @tc.desc: Test RIGHT_MOUSE_UP block when DOWN was delivered (falsify cancel).
 * @tc.type: FUNC
 */
HWTEST_F(InputEventMonitorManagerTestNg, ProcessMouseEventRightUpWithDown001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<InputEventMonitorManager>();
    ASSERT_NE(manager, nullptr);
    ASSERT_NE(manager->AddLocalInputMonitor(
        static_cast<uint32_t>(InputEventSubTypeMask::RIGHT_MOUSE_UP), g_blockHandler), nullptr);

    /**
     * @tc.steps: step1. Deliver RIGHT_MOUSE_DOWN first (no block for DOWN).
     */
    MouseEvent rightPress;
    rightPress.action = MouseAction::PRESS;
    rightPress.button = MouseButton::RIGHT_BUTTON;
    rightPress.deviceId = 91;
    EXPECT_FALSE(manager->ProcessMouseEvent(rightPress));

    /**
     * @tc.steps: step2. RIGHT_MOUSE_UP is blocked, DOWN was delivered.
     * @tc.expected: event.action becomes CANCEL, isFalsifyCancel becomes true.
     */
    MouseEvent rightRelease = rightPress;
    rightRelease.action = MouseAction::RELEASE;
    EXPECT_TRUE(manager->ProcessMouseEvent(rightRelease));
    EXPECT_EQ(rightRelease.action, MouseAction::CANCEL);
    EXPECT_TRUE(rightRelease.isFalsifyCancel);
}

/**
 * @tc.name: ProcessMouseEventCancelTest001
 * @tc.desc: Test ProcessMouseEvent with CANCEL action.
 * @tc.type: FUNC
 */
HWTEST_F(InputEventMonitorManagerTestNg, ProcessMouseEventCancelTest001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<InputEventMonitorManager>();
    ASSERT_NE(manager, nullptr);
    ASSERT_NE(manager->AddLocalInputMonitor(
        static_cast<uint32_t>(InputEventSubTypeMask::LEFT_MOUSE_DOWN), g_continueHandler), nullptr);

    /**
     * @tc.steps: step1. Deliver DOWN first.
     */
    MouseEvent press;
    press.action = MouseAction::PRESS;
    press.button = MouseButton::LEFT_BUTTON;
    press.deviceId = 101;
    EXPECT_FALSE(manager->ProcessMouseEvent(press));
    auto mouseKey = manager->GetMouseInteractionId(press);
    EXPECT_TRUE(manager->mouseTracker_.IsDownEventDelivered(mouseKey));

    /**
     * @tc.steps: step2. Send CANCEL event.
     * @tc.expected: Returns false, interaction ended.
     */
    MouseEvent cancelEvent = press;
    cancelEvent.action = MouseAction::CANCEL;
    EXPECT_FALSE(manager->ProcessMouseEvent(cancelEvent));
    EXPECT_FALSE(manager->mouseTracker_.IsDownEventDelivered(mouseKey));
}

/**
 * @tc.name: ProcessKeyEventLongPressAndCancel001
 * @tc.desc: Test ProcessKeyEvent with LONG_PRESS and CANCEL actions.
 * @tc.type: FUNC
 */
HWTEST_F(InputEventMonitorManagerTestNg, ProcessKeyEventLongPressAndCancel001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<InputEventMonitorManager>();
    ASSERT_NE(manager, nullptr);
    ASSERT_NE(manager->AddLocalInputMonitor(
        static_cast<uint32_t>(InputEventSubTypeMask::KEY_DOWN), g_continueHandler), nullptr);

    /**
     * @tc.steps: step1. LONG_PRESS key event is not intercepted.
     * @tc.expected: Returns false.
     */
    KeyEvent longPressEvent;
    longPressEvent.code = KeyCode::KEY_H;
    longPressEvent.action = KeyAction::LONG_PRESS;
    longPressEvent.deviceId = 111;
    EXPECT_FALSE(manager->ProcessKeyEvent(longPressEvent));

    /**
     * @tc.steps: step2. Deliver DOWN then send CANCEL.
     * @tc.expected: Returns false, interaction ended.
     */
    KeyEvent downEvent;
    downEvent.code = KeyCode::KEY_I;
    downEvent.action = KeyAction::DOWN;
    downEvent.deviceId = 112;
    EXPECT_FALSE(manager->ProcessKeyEvent(downEvent));
    auto key = manager->GetKeyInteractionId(downEvent);
    EXPECT_TRUE(manager->keyTracker_.IsDownEventDelivered(key));

    KeyEvent cancelEvent = downEvent;
    cancelEvent.action = KeyAction::CANCEL;
    EXPECT_FALSE(manager->ProcessKeyEvent(cancelEvent));
    EXPECT_FALSE(manager->keyTracker_.IsDownEventDelivered(key));
}

/**
 * @tc.name: ProcessKeyEventUpContinueWithDown001
 * @tc.desc: Test KEY_UP continue when DOWN was delivered.
 * @tc.type: FUNC
 */
HWTEST_F(InputEventMonitorManagerTestNg, ProcessKeyEventUpContinueWithDown001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<InputEventMonitorManager>();
    ASSERT_NE(manager, nullptr);
    ASSERT_NE(manager->AddLocalInputMonitor(
        static_cast<uint32_t>(InputEventSubTypeMask::KEY_UP), g_continueHandler), nullptr);

    /**
     * @tc.steps: step1. Deliver KEY_DOWN first.
     */
    KeyEvent downEvent;
    downEvent.code = KeyCode::KEY_J;
    downEvent.action = KeyAction::DOWN;
    downEvent.deviceId = 121;
    EXPECT_FALSE(manager->ProcessKeyEvent(downEvent));

    /**
     * @tc.steps: step2. KEY_UP continues, DOWN was delivered.
     * @tc.expected: Returns false, interaction ended.
     */
    KeyEvent upEvent = downEvent;
    upEvent.action = KeyAction::UP;
    EXPECT_FALSE(manager->ProcessKeyEvent(upEvent));
    auto key = manager->GetKeyInteractionId(downEvent);
    EXPECT_FALSE(manager->keyTracker_.IsDownEventDelivered(key));
}

/**
 * @tc.name: ProcessKeyEventUpBlockIsPreIme001
 * @tc.desc: Test KEY_UP block resets isPreIme to false.
 * @tc.type: FUNC
 */
HWTEST_F(InputEventMonitorManagerTestNg, ProcessKeyEventUpBlockIsPreIme001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<InputEventMonitorManager>();
    ASSERT_NE(manager, nullptr);
    ASSERT_NE(manager->AddLocalInputMonitor(
        static_cast<uint32_t>(InputEventSubTypeMask::KEY_UP), g_blockHandler), nullptr);

    /**
     * @tc.steps: step1. Deliver KEY_DOWN first, then KEY_UP with isPreIme=true.
     * @tc.expected: After block, isPreIme becomes false.
     */
    KeyEvent downEvent;
    downEvent.code = KeyCode::KEY_K;
    downEvent.action = KeyAction::DOWN;
    downEvent.deviceId = 131;
    EXPECT_FALSE(manager->ProcessKeyEvent(downEvent));

    KeyEvent upEvent = downEvent;
    upEvent.action = KeyAction::UP;
    upEvent.isPreIme = true;
    EXPECT_TRUE(manager->ProcessKeyEvent(upEvent));
    EXPECT_FALSE(upEvent.isPreIme);
    EXPECT_EQ(upEvent.action, KeyAction::CANCEL);
    EXPECT_TRUE(upEvent.isFalsifyCancel);
}

/**
 * @tc.name: ProcessTouchEventCancelEndInteraction001
 * @tc.desc: Test ProcessTouchEvent CANCEL ends interaction.
 * @tc.type: FUNC
 */
HWTEST_F(InputEventMonitorManagerTestNg, ProcessTouchEventCancelEndInteraction001, TestSize.Level1)
{
    auto manager = AceType::MakeRefPtr<InputEventMonitorManager>();
    ASSERT_NE(manager, nullptr);
    ASSERT_NE(manager->AddLocalInputMonitor(
        static_cast<uint32_t>(InputEventSubTypeMask::TOUCH_DOWN), g_continueHandler), nullptr);

    /**
     * @tc.steps: step1. Deliver TOUCH_DOWN.
     */
    TouchEvent downEvent;
    downEvent.type = TouchType::DOWN;
    downEvent.deviceId = 141;
    downEvent.id = 14;
    EXPECT_FALSE(manager->ProcessTouchEvent(downEvent));
    auto touchKey = manager->GetTouchInteractionId(downEvent);
    EXPECT_TRUE(manager->touchTracker_.IsDownEventDelivered(touchKey));

    /**
     * @tc.steps: step2. Send CANCEL.
     * @tc.expected: Returns false, interaction ended.
     */
    TouchEvent cancelEvent = downEvent;
    cancelEvent.type = TouchType::CANCEL;
    EXPECT_FALSE(manager->ProcessTouchEvent(cancelEvent));
    EXPECT_FALSE(manager->touchTracker_.IsDownEventDelivered(touchKey));
}
} // namespace OHOS::Ace::NG
