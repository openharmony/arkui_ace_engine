/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "core/components_ng/base/frame_node.h"
#include "frameworks/core/common/event_manager.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const std::string CTRL = "Ctrl";
const std::string SHIFT = "shift";
const std::string ALT = "alt";
const std::string CTRLSHIFT = "Ctrl + shift";

const std::string CHARACTER_C = "C";
const std::string CHARACTER_A = "A";
const std::string CHARACTER_V = "V";
const std::string CHARACTER_Z = "Z";
const std::string CHARACTER_EIGHT = "8";
const std::string CHARACTER_X = "X";

constexpr int32_t NUM_CTRL_VALUE = 1;
constexpr int32_t NUM_SHIFT_VALUE = 2;
constexpr int32_t NUM_ALT_VALUE = 4;

constexpr int32_t NODEID = 1;
} // namespace

class EventManagerTestNg : public testing::Test {
public:
    static void SetUpTestSuite() {};
    static void TearDownTestSuite() {};

protected:
};

/**
 * @tc.name: EventManagerTest001
 * @tc.desc: Test OnDragStart
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest001, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();

    bool isCtrlC = eventManager->IsSystemKeyboardShortcut(CHARACTER_C, NUM_CTRL_VALUE);
    bool isCtrlA = eventManager->IsSystemKeyboardShortcut(CHARACTER_A, NUM_CTRL_VALUE);
    bool isCtrlV = eventManager->IsSystemKeyboardShortcut(CHARACTER_V, NUM_CTRL_VALUE);
    bool isCtrl8 = eventManager->IsSystemKeyboardShortcut(CHARACTER_EIGHT, NUM_CTRL_VALUE);
    bool isCtrlX = eventManager->IsSystemKeyboardShortcut(CHARACTER_X, NUM_CTRL_VALUE);
    bool isShiftC = eventManager->IsSystemKeyboardShortcut(CHARACTER_C, NUM_SHIFT_VALUE);
    bool isShiftA = eventManager->IsSystemKeyboardShortcut(CHARACTER_A, NUM_SHIFT_VALUE);
    bool isShiftV = eventManager->IsSystemKeyboardShortcut(CHARACTER_V, NUM_SHIFT_VALUE);
    bool isShift8 = eventManager->IsSystemKeyboardShortcut(CHARACTER_EIGHT, NUM_SHIFT_VALUE);
    bool isShiftX = eventManager->IsSystemKeyboardShortcut(CHARACTER_X, NUM_SHIFT_VALUE);
    bool isAltC = eventManager->IsSystemKeyboardShortcut(CHARACTER_C, NUM_ALT_VALUE);
    bool isAltA = eventManager->IsSystemKeyboardShortcut(CHARACTER_A, NUM_ALT_VALUE);
    bool isAltV = eventManager->IsSystemKeyboardShortcut(CHARACTER_V, NUM_ALT_VALUE);
    bool isAlt8 = eventManager->IsSystemKeyboardShortcut(CHARACTER_EIGHT, NUM_ALT_VALUE);
    bool isAltX = eventManager->IsSystemKeyboardShortcut(CHARACTER_X, NUM_ALT_VALUE);
    bool isCtrlShiftC = eventManager->IsSystemKeyboardShortcut(CHARACTER_C, (NUM_CTRL_VALUE + NUM_SHIFT_VALUE));
    bool isCtrlShiftA = eventManager->IsSystemKeyboardShortcut(CHARACTER_A, (NUM_CTRL_VALUE + NUM_SHIFT_VALUE));
    bool isCtrlShiftV = eventManager->IsSystemKeyboardShortcut(CHARACTER_V, (NUM_CTRL_VALUE + NUM_SHIFT_VALUE));
    bool isCtrlShift8 = eventManager->IsSystemKeyboardShortcut(CHARACTER_EIGHT, (NUM_CTRL_VALUE + NUM_SHIFT_VALUE));
    bool isCtrlShiftX = eventManager->IsSystemKeyboardShortcut(CHARACTER_X, (NUM_CTRL_VALUE + NUM_SHIFT_VALUE));

    EXPECT_TRUE(isCtrlC);
    EXPECT_TRUE(isCtrlA);
    EXPECT_TRUE(isCtrlV);
    EXPECT_FALSE(isCtrl8);
    EXPECT_TRUE(isCtrlX);
    EXPECT_FALSE(isShiftC);
    EXPECT_FALSE(isShiftA);
    EXPECT_FALSE(isShiftV);
    EXPECT_FALSE(isShift8);
    EXPECT_FALSE(isShiftX);
    EXPECT_FALSE(isAltC);
    EXPECT_FALSE(isAltA);
    EXPECT_FALSE(isAltV);
    EXPECT_FALSE(isAlt8);
    EXPECT_FALSE(isAltX);
    EXPECT_FALSE(isCtrlShiftC);
    EXPECT_FALSE(isCtrlShiftA);
    EXPECT_FALSE(isCtrlShiftV);
    EXPECT_FALSE(isCtrlShift8);
    EXPECT_FALSE(isCtrlShiftX);
}

/**
 * @tc.name: EventManagerTest002
 * @tc.desc: Test OnDragStart
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest002, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    KeyEvent event;
    auto frameNodeCtrl = FrameNode::GetOrCreateFrameNode(CTRL, NODEID, nullptr);
    auto frameNodeShift = FrameNode::GetOrCreateFrameNode(SHIFT, NODEID, nullptr);
    auto frameNodeAlt = FrameNode::GetOrCreateFrameNode(ALT, NODEID, nullptr);
    auto frameNodeCtrlShift = FrameNode::GetOrCreateFrameNode(CTRLSHIFT, NODEID, nullptr);
    frameNodeCtrl->SetActive(true);
    frameNodeShift->SetActive(true);
    frameNodeAlt->SetActive(true);
    frameNodeCtrlShift->SetActive(true);

    auto eventHubCtrl = frameNodeCtrl->GetEventHub<NG::EventHub>();
    auto eventHubShift = frameNodeShift->GetEventHub<NG::EventHub>();
    auto eventHubAlt = frameNodeAlt->GetEventHub<NG::EventHub>();
    auto eventHubCtrlShift = frameNodeCtrlShift->GetEventHub<NG::EventHub>();

    eventManager->AddKeyboardShortcutNode(WeakPtr<NG::FrameNode>(frameNodeCtrl));
    eventManager->AddKeyboardShortcutNode(WeakPtr<NG::FrameNode>(frameNodeShift));
    eventManager->AddKeyboardShortcutNode(WeakPtr<NG::FrameNode>(frameNodeAlt));
    eventManager->AddKeyboardShortcutNode(WeakPtr<NG::FrameNode>(frameNodeCtrlShift));
    eventHubCtrl->SetKeyboardShortcut(CHARACTER_C, (NUM_CTRL_VALUE + NUM_SHIFT_VALUE + NUM_ALT_VALUE), []() {});
    event.code = KeyCode::KEY_C;
    event.action = KeyAction::DOWN;
    event.pressedCodes.emplace_back(KeyCode::KEY_CTRL_LEFT);
    event.pressedCodes.emplace_back(KeyCode::KEY_SHIFT_LEFT);
    event.pressedCodes.emplace_back(KeyCode::KEY_ALT_LEFT);
    event.pressedCodes.emplace_back(KeyCode::KEY_C);
    eventManager->DispatchKeyboardShortcut(event);
    EXPECT_EQ(event.action, KeyAction::DOWN);
    eventHubShift->SetKeyboardShortcut(CHARACTER_A, (NUM_CTRL_VALUE + NUM_SHIFT_VALUE), []() {});
    event.code = KeyCode::KEY_A;
    event.action = KeyAction::DOWN;
    event.pressedCodes.emplace_back(KeyCode::KEY_CTRL_LEFT);
    event.pressedCodes.emplace_back(KeyCode::KEY_SHIFT_LEFT);
    event.pressedCodes.emplace_back(KeyCode::KEY_A);
    eventManager->DispatchKeyboardShortcut(event);
    EXPECT_EQ(event.action, KeyAction::DOWN);
    eventHubAlt->SetKeyboardShortcut(CHARACTER_A, (NUM_CTRL_VALUE + NUM_ALT_VALUE), []() {});
    event.code = KeyCode::KEY_V;
    event.action = KeyAction::DOWN;
    event.pressedCodes.emplace_back(KeyCode::KEY_CTRL_LEFT);
    event.pressedCodes.emplace_back(KeyCode::KEY_V);
    eventManager->DispatchKeyboardShortcut(event);
    EXPECT_EQ(event.action, KeyAction::DOWN);
}

/**
 * @tc.name: EventManagerTest003
 * @tc.desc: Test OnDragStart
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest003, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();

    auto frameNodeCtrl = FrameNode::GetOrCreateFrameNode(CTRL, NUM_CTRL_VALUE, nullptr);
    eventManager->AddKeyboardShortcutNode(WeakPtr<NG::FrameNode>(frameNodeCtrl));
    eventManager->AddKeyboardShortcutNode(WeakPtr<NG::FrameNode>(frameNodeCtrl));
    eventManager->AddKeyboardShortcutNode(WeakPtr<NG::FrameNode>(frameNodeCtrl));
    auto frameNodeShift = FrameNode::GetOrCreateFrameNode(SHIFT, NUM_SHIFT_VALUE, nullptr);
    eventManager->AddKeyboardShortcutNode(WeakPtr<NG::FrameNode>(frameNodeShift));
    auto frameNodeAlt = FrameNode::GetOrCreateFrameNode(ALT, NUM_ALT_VALUE, nullptr);
    eventManager->AddKeyboardShortcutNode(WeakPtr<NG::FrameNode>(frameNodeAlt));
    auto frameNodeCtrlShift = FrameNode::GetOrCreateFrameNode(CTRLSHIFT, (NUM_CTRL_VALUE + NUM_SHIFT_VALUE), nullptr);
    eventManager->AddKeyboardShortcutNode(WeakPtr<NG::FrameNode>(frameNodeCtrlShift));

    auto eventHubCtrl = frameNodeCtrl->GetEventHub<NG::EventHub>();
    auto eventHubShift = frameNodeShift->GetEventHub<NG::EventHub>();
    auto eventHubAlt = frameNodeAlt->GetEventHub<NG::EventHub>();
    auto eventHubCtrlShift = frameNodeCtrlShift->GetEventHub<NG::EventHub>();

    eventHubCtrl->SetKeyboardShortcut(CHARACTER_C, NUM_CTRL_VALUE, []() {});
    eventHubShift->SetKeyboardShortcut(CHARACTER_A, NUM_SHIFT_VALUE, []() {});
    eventHubAlt->SetKeyboardShortcut(CHARACTER_V, NUM_ALT_VALUE, []() {});
    eventHubCtrlShift->SetKeyboardShortcut(CHARACTER_Z, (NUM_CTRL_VALUE + NUM_SHIFT_VALUE), []() {});

    bool isShortcutNodeCtrlC = eventManager->IsSameKeyboardShortcutNode(CHARACTER_C, NUM_CTRL_VALUE);
    EXPECT_TRUE(isShortcutNodeCtrlC);
    bool isShortcutNodeCtrlEIGHT = eventManager->IsSameKeyboardShortcutNode(CHARACTER_EIGHT, NUM_CTRL_VALUE);
    EXPECT_FALSE(isShortcutNodeCtrlEIGHT);
    bool isShortcutNodeShiftC = eventManager->IsSameKeyboardShortcutNode(CHARACTER_C, NUM_SHIFT_VALUE);
    EXPECT_FALSE(isShortcutNodeShiftC);
    bool isShortcutNodeShiftEight = eventManager->IsSameKeyboardShortcutNode(CHARACTER_EIGHT, NUM_SHIFT_VALUE);
    EXPECT_FALSE(isShortcutNodeShiftEight);
    bool isShortcutNodeAltC = eventManager->IsSameKeyboardShortcutNode(CHARACTER_C, NUM_ALT_VALUE);
    EXPECT_FALSE(isShortcutNodeAltC);
    bool isShortcutNodeAltEight = eventManager->IsSameKeyboardShortcutNode(CHARACTER_EIGHT, NUM_ALT_VALUE);
    EXPECT_FALSE(isShortcutNodeAltEight);
    bool isShortcutComposeC = eventManager->IsSameKeyboardShortcutNode(CHARACTER_C, (NUM_CTRL_VALUE + NUM_SHIFT_VALUE));
    EXPECT_FALSE(isShortcutComposeC);
    bool isShortcutComposeEight =
        eventManager->IsSameKeyboardShortcutNode(CHARACTER_EIGHT, (NUM_CTRL_VALUE + NUM_SHIFT_VALUE));
    EXPECT_FALSE(isShortcutComposeEight);
}

/**
 * @tc.name: EventManagerTest004
 * @tc.desc: Test OnDragStart
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest004, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    auto frameNodeone = FrameNode::GetOrCreateFrameNode(CTRL, NODEID, nullptr);

    eventManager->AddKeyboardShortcutNode(WeakPtr<NG::FrameNode>(frameNodeone));
    eventManager->AddKeyboardShortcutNode(WeakPtr<NG::FrameNode>(frameNodeone));
    ASSERT_NE(frameNodeone, nullptr);

    auto frameNodetwo = FrameNode::GetOrCreateFrameNode(SHIFT, NODEID, nullptr);
    eventManager->AddKeyboardShortcutNode(WeakPtr<NG::FrameNode>(frameNodetwo));
    ASSERT_NE(frameNodetwo, nullptr);
}

/**
 * @tc.name: EventManagerTest005
 * @tc.desc: Test OnDragStart
 * @tc.type: FUNC
 */
HWTEST_F(EventManagerTestNg, EventManagerTest005, TestSize.Level1)
{
    auto eventManager = AceType::MakeRefPtr<EventManager>();
    ASSERT_NE(eventManager, nullptr);

    auto frameNodeone = FrameNode::GetOrCreateFrameNode(CTRL, NODEID, nullptr);
    eventManager->AddKeyboardShortcutNode(WeakPtr<NG::FrameNode>(frameNodeone));

    eventManager->DelKeyboardShortcutNode(frameNodeone->GetId());
    ASSERT_NE(frameNodeone, nullptr);

    auto frameNodetwo = FrameNode::GetOrCreateFrameNode(SHIFT, NODEID, nullptr);
    eventManager->DelKeyboardShortcutNode(frameNodetwo->GetId());
    ASSERT_NE(frameNodetwo, nullptr);
}
} // namespace OHOS::Ace::NG
