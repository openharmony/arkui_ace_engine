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

#include "gtest/gtest.h"
#define private public
#define protected public
#include "interfaces/inner_api/ace_kit/include/ui/base/lifecycle_checkable.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/memory/referenced.h"
#include "base/ressched/ressched_report.h"
#include "core/common/container.h"
#include "core/common/key_event_manager.h"
#include "core/components/theme/app_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_manager.h"
#include "core/components_ng/pattern/root/root_pattern.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "frameworks/base/input_manager/input_manager.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class MockKeyEventManager : public KeyEventManager {
public:
    MockKeyEventManager() = default;
    ~MockKeyEventManager() override = default;

protected:
    int32_t GetInstanceId() override
    {
        return 0;
    }
};

class KeyEventManagerTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() {}
    void TearDown() {}
};

void KeyEventManagerTest::SetUpTestCase()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp(MockPipelineContext::GetCurrent());
}

void KeyEventManagerTest::TearDownTestCase()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

struct OnKeyEventPreImeTestCase {
    bool needHanleKeyEvent;
    bool needSkip;
    bool needHanleShortCutKey;
    bool expect;
};

const std::vector<OnKeyEventPreImeTestCase> HandleOnKeyEventPreImeTestCase {
    { true, false, true, true },
    { true, true, true, true },
    { false, true, true, false },
    { false, false, true, true },
    { true, false, false, true },
    { true, true, false, true },
    { false, true, false, false },
    { false, false, false, false },
};

struct ReDispatchTestCase {
    bool needHanleShortCutKey;
    bool needHanleTabKey;
    bool needHanleKeyEvent;
    int32_t expect;
};

const std::vector<ReDispatchTestCase> HandleReDispatchTestCase {
    { true, false, true, 1 },
    { true, true, true, 1 },
    { true, false, false, 1 },
    { true, true, false, 1 },
    { false, true, true, 2 },
    { false, true, false, 2 },
    { false, false, true, 3 },
    { false, false, false, 0 },
};

RefPtr<FrameNode> CreateTestTreeWithDefaultFocus()
{
    auto context = MockPipelineContext::GetCurrent();
    auto focusManager = context->GetOrCreateFocusManager();
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 2, pagePattern);
    pageNode->onMainTree_ = true;
    auto pageFocusHub = pageNode->GetOrCreateFocusHub();
    context->rootNode_->AddChild(pageNode);
    auto columnPattern = AceType::MakeRefPtr<LinearLayoutPattern>(true);
    auto columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 3, columnPattern);
    columnNode->onMainTree_ = true;
    auto columnNodeFocusHub = columnNode->GetOrCreateFocusHub();
    auto buttonPattern = AceType::MakeRefPtr<ButtonPattern>();
    auto buttonNode = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 4, buttonPattern);
    auto buttonFocusHub = buttonNode->GetOrCreateFocusHub();
    pageNode->AddChild(columnNode);
    columnNode->AddChild(buttonNode);
    pagePattern->FocusViewShow();
    context->FlushFocusView();
    pagePattern->TriggerFocusMove();
    EXPECT_EQ(buttonFocusHub->IsCurrentFocus(), true);
    buttonNode->isActive_ = true;
    focusManager->currentFocus_ = AceType::WeakClaim(AceType::RawPtr(buttonFocusHub));
    EXPECT_NE(buttonNode, nullptr);
    return buttonNode;
}

/**
 * @tc.name: IsSystemKeyboardShortcut001
 * @tc.desc: Verify the AddSubContainer Interface of FormManager work correctly.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventManagerTest, IsSystemKeyboardShortcut001, TestSize.Level1)
{
    KeyEvent event;

    auto keyEventManager = AceType::MakeRefPtr<MockKeyEventManager>();
    std::vector<HotKey> systemHotKeys;

    auto ret = keyEventManager->IsSystemKeyboardShortcut(event);
    EXPECT_FALSE(ret);

    std::set<int32_t> mySet = {static_cast<int32_t>(KeyCode::KEY_1)};
    int32_t myInt = static_cast<int32_t>(KeyCode::KEY_1);
    std::tuple<std::set<int32_t>, int32_t> a(mySet, myInt);
    systemHotKeys.push_back(a);
    event.pressedCodes.push_back(KeyCode::KEY_1);
    event.code = KeyCode::KEY_1;
    ret = keyEventManager->IsSystemKeyboardShortcut(event);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: OnKeyEventPreIme001
 * @tc.desc: Test the OnKeyEvent.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventManagerTest, OnKeyEventPreIme001, TestSize.Level1)
{
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    auto eventManager = context->GetEventManager();
    ASSERT_NE(eventManager, nullptr);
    for (auto& testcase : HandleOnKeyEventPreImeTestCase) {
        auto buttonNode = CreateTestTreeWithDefaultFocus();
        EXPECT_NE(buttonNode, nullptr);
        auto buttonFocusHub = buttonNode->GetOrCreateFocusHub();
        EXPECT_NE(buttonFocusHub, nullptr);
        eventManager->keyboardShortcutNode_.clear();
        if (testcase.needHanleKeyEvent) {
            auto onKeyEventCallback = [](KeyEventInfo& event) {
                event.SetStopPropagation(true);
                return true;
            };
            buttonFocusHub->SetOnKeyPreIme(std::move(onKeyEventCallback));
        }
        if (testcase.needHanleShortCutKey) {
            auto onShortCutKeyEventCallback = []() { return true; };
            std::vector<ModifierKey> keys;
            keys.push_back(ModifierKey::SHIFT);
            ViewStackProcessor::GetInstance()->Push(buttonNode);
            ViewAbstract::SetKeyboardShortcut("A", std::move(keys), onShortCutKeyEventCallback);
        }
        if (testcase.needSkip) {
            buttonNode->tag_ = V2::WEB_ETS_TAG;
        }
        KeyEvent event;
        event.isPreIme = true;
        event.pressedCodes = { KeyCode::KEY_SHIFT_LEFT, KeyCode::KEY_A };
        event.action = KeyAction::DOWN;
        event.code = KeyCode::KEY_A;
        auto result = eventManager->OnKeyEvent(event);
        EXPECT_EQ(result, testcase.expect);
    }
}

/**
 * @tc.name: TriggerKeyEventDispatch001
 * @tc.desc: Test the TriggerKeyEventDispatch.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventManagerTest, TriggerKeyEventDispatch001, TestSize.Level1)
{
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    auto eventManager = context->GetEventManager();
    ASSERT_NE(eventManager, nullptr);
    KeyEvent event;
    event.pressedCodes = { KeyCode::KEY_TAB };
    event.action = KeyAction::DOWN;
    event.code = KeyCode::KEY_TAB;
    auto buttonNode = CreateTestTreeWithDefaultFocus();
    EXPECT_NE(buttonNode, nullptr);
    auto buttonFocusHub = buttonNode->GetOrCreateFocusHub();
    EXPECT_NE(buttonFocusHub, nullptr);
    buttonNode->tag_ = V2::WEB_ETS_TAG;

    event.isPreIme = false;
    auto result = eventManager->TriggerKeyEventDispatch(event);
    EXPECT_EQ(result, false);

    buttonNode->tag_ = V2::WEB_CORE_TAG;
    buttonFocusHub->SetTabIndex(1);
    result = eventManager->TriggerKeyEventDispatch(event);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: ReDispatch001
 * @tc.desc: Test the ReDispatch.
 * @tc.type: FUNC
 */
HWTEST_F(KeyEventManagerTest, ReDispatch001, TestSize.Level1)
{
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    auto eventManager = context->GetEventManager();
    ASSERT_NE(eventManager, nullptr);
    for (auto& testcase : HandleReDispatchTestCase) {
        auto buttonNode = CreateTestTreeWithDefaultFocus();
        EXPECT_NE(buttonNode, nullptr);
        auto buttonParent = buttonNode->GetParent();
        auto buttonNode2 = CreateTestTreeWithDefaultFocus();
        EXPECT_NE(buttonNode2, nullptr);
        auto buttonFocusHub2 = buttonNode2->GetOrCreateFocusHub();
        EXPECT_NE(buttonFocusHub2, nullptr);
        buttonParent->AddChild(buttonNode2);
        eventManager->keyboardShortcutNode_.clear();
        KeyEvent event;
        event.isPreIme = false;
        event.pressedCodes = { KeyCode::KEY_SHIFT_LEFT, KeyCode::KEY_A };
        event.action = KeyAction::DOWN;
        event.code = KeyCode::KEY_A;
        auto flag = false;
        if (testcase.needHanleShortCutKey) {
            auto onShortCutKeyEventCallback = [&flag]() {
                flag = true;
                return true;
            };
            std::vector<ModifierKey> keys;
            keys.push_back(ModifierKey::SHIFT);
            ViewStackProcessor::GetInstance()->Push(buttonNode);
            ViewAbstract::SetKeyboardShortcut("A", std::move(keys), onShortCutKeyEventCallback);
        } else if (testcase.needHanleTabKey) {
            event.pressedCodes = { KeyCode::KEY_TAB };
            event.code = KeyCode::KEY_TAB;
            buttonNode2->tag_ = V2::WEB_CORE_TAG;
            buttonFocusHub2->SetTabIndex(1);
        } else if (testcase.needHanleKeyEvent) {
            auto onKeyEventCallback2 = [&flag](const KeyEventInfo& event) {
                flag = true;
                return true;
            };
            buttonFocusHub2->SetOnKeyEventDispatchCallback(std::move(onKeyEventCallback2));
        }
        eventManager->ReDispatch(event);
        if (testcase.expect == 1 || testcase.expect == 3) {
            EXPECT_NE(flag, false);
        } else if (testcase.expect == 2) {
            EXPECT_EQ(buttonFocusHub2->IsCurrentFocus(), true);
        } else {
            EXPECT_NE(flag, true);
        }
    }
}
} // namespace OHOS::Ace::NG