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
} // namespace OHOS::Ace::NG
