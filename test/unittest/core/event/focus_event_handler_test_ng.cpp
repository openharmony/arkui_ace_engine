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
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/memory/referenced.h"
#include "core/components/common/properties/color.h"
#include "core/components/theme/app_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/focus_event_handler.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
namespace OHOS::Ace::NG {
namespace {
const int32_t VERSION_TWELVE = 12;
const int32_t VERSION_EIGHTEEN = 18;
} // namespace

class FocusEventHandlerTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
};
} // namespace OHOS::Ace::NG

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
void FocusEventHandlerTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp(MockPipelineContext::GetCurrent());
}

void FocusEventHandlerTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void FocusEventHandlerTestNg::SetUp() {}

void FocusEventHandlerTestNg::TearDown()
{
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    ASSERT_NE(context->rootNode_, nullptr);
    context->rootNode_->children_.clear();
}

struct KeyEventClickTestCase {
    bool focusActive;
    bool needFocusHandleClick;
    FocusIntension intension;
    bool isTabStop;
    bool expect;
};

const vector<KeyEventClickTestCase> HandleKeyEventClickOnVersion12TestCase {
    { false, false, FocusIntension::SELECT, false, false },
    { true, false, FocusIntension::SELECT, false, false },
    { false, true, FocusIntension::SELECT, false, true },
    { true, true, FocusIntension::SELECT, false, true },
    { false, false, FocusIntension::SPACE, false, false },
    { true, false, FocusIntension::SPACE, false, false },
    { false, true, FocusIntension::SPACE, false, true },
    { true, true, FocusIntension::SPACE, false, true },
    { false, false, FocusIntension::SELECT, true, false },
    { true, false, FocusIntension::SELECT, true, false },
    { false, true, FocusIntension::SELECT, true, false },
    { true, true, FocusIntension::SELECT, true, false },
    { false, false, FocusIntension::SPACE, true, false },
    { true, false, FocusIntension::SPACE, true, false },
    { false, true, FocusIntension::SPACE, true, true },
    { true, true, FocusIntension::SPACE, true, true },
};

const vector<KeyEventClickTestCase> HandleKeyEventClickOnVersion18TestCase {
    { false, false, FocusIntension::SELECT, false, false },
    { true, false, FocusIntension::SELECT, false, false },
    { false, true, FocusIntension::SELECT, false, false },
    { true, true, FocusIntension::SELECT, false, true },
    { false, false, FocusIntension::SPACE, false, false },
    { true, false, FocusIntension::SPACE, false, false },
    { false, true, FocusIntension::SPACE, false, false },
    { true, true, FocusIntension::SPACE, false, true },
    { false, false, FocusIntension::SELECT, true, false },
    { true, false, FocusIntension::SELECT, true, false },
    { false, true, FocusIntension::SELECT, true, false },
    { true, true, FocusIntension::SELECT, true, false },
    { false, false, FocusIntension::SPACE, true, false },
    { true, false, FocusIntension::SPACE, true, false },
    { false, true, FocusIntension::SPACE, true, false },
    { true, true, FocusIntension::SPACE, true, true },
};

RefPtr<FrameNode> CreateTestTreeWithDefaultFocus()
{
    auto context = MockPipelineContext::GetCurrent();
    auto focusManager = context->GetOrCreateFocusManager();
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, 1, pagePattern);
    pageNode->onMainTree_ = true;
    auto pageFocusHub = pageNode->GetOrCreateFocusHub();
    context->rootNode_->AddChild(pageNode);
    auto columnPattern = AceType::MakeRefPtr<LinearLayoutPattern>(true);
    auto columnNode = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG, 2, columnPattern);
    columnNode->onMainTree_ = true;
    auto columnFocusHub = columnNode->GetOrCreateFocusHub();
    auto buttonPattern = AceType::MakeRefPtr<ButtonPattern>();
    auto buttonNode = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, 3, buttonPattern);
    buttonNode->onMainTree_ = true;
    auto buttonFocusHub = buttonNode->GetOrCreateFocusHub();
    pageNode->AddChild(columnNode);
    columnNode->AddChild(buttonNode);
    pagePattern->FocusViewShow();
    context->FlushFocusView();
    pagePattern->TriggerFocusMove();
    EXPECT_EQ(buttonFocusHub->IsCurrentFocus(), true);
    return buttonNode;
}

void ClearRootChild()
{
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    ASSERT_NE(context->rootNode_, nullptr);
    context->rootNode_->children_.clear();
}

/**
 * @tc.name: GetFocusIntension001
 * @tc.desc: Create SetStyle.
 * @tc.type: FUNC
 */
HWTEST_F(FocusEventHandlerTestNg, GetFocusIntensionTest001, TestSize.Level1)
{
    KeyEvent event;
    event.action = KeyAction::DOWN;
    event.isPreIme = false;
    event.code = KeyCode::KEY_NUMPAD_ENTER;
    event.pressedCodes = { KeyCode::KEY_NUMPAD_ENTER };
    auto expectIntension = FocusEvent::GetFocusIntension(event);
    EXPECT_EQ(expectIntension, FocusIntension::SELECT);
    event.code = KeyCode::KEY_SPACE;
    event.pressedCodes = { KeyCode::KEY_SPACE };
    expectIntension = FocusEvent::GetFocusIntension(event);
    EXPECT_EQ(expectIntension, FocusIntension::SPACE);
}

/**
 * @tc.name: GetFocusIntensionFromKey001
 * @tc.desc: Create SetStyle.
 * @tc.type: FUNC
 */
HWTEST_F(FocusEventHandlerTestNg, GetFocusIntensionFromKeyTest001, TestSize.Level1)
{
    KeyIntention keyIntention;
    keyIntention = KeyIntention::INTENTION_SELECT;
    auto expectIntension = FocusEvent::GetFocusIntensionFromKey(keyIntention);
    EXPECT_EQ(expectIntension, FocusIntension::SELECT);
    keyIntention = KeyIntention::INTENTION_ESCAPE;
    expectIntension = FocusEvent::GetFocusIntensionFromKey(keyIntention);
    EXPECT_EQ(expectIntension, FocusIntension::ESC);
    keyIntention = KeyIntention::INTENTION_HOME;
    expectIntension = FocusEvent::GetFocusIntensionFromKey(keyIntention);
    EXPECT_EQ(expectIntension, FocusIntension::HOME);
    keyIntention = KeyIntention::INTENTION_UNKNOWN;
    expectIntension = FocusEvent::GetFocusIntensionFromKey(keyIntention);
    EXPECT_EQ(expectIntension, FocusIntension::NONE);
}

/**
 * @tc.name: HandleKeyEventRedispatchTest001
 * @tc.desc: Create SetStyle.
 * @tc.type: FUNC
 */
HWTEST_F(FocusEventHandlerTestNg, HandleKeyEventRedispatchTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test HandleKeyEvent Redispatch false
     * expected: return false
     */
    auto context = MockPipelineContext::GetCurrent();
    ASSERT_NE(context, nullptr);
    auto buttonNode = CreateTestTreeWithDefaultFocus();
    EXPECT_NE(buttonNode, nullptr);
    auto buttonFocusHub = buttonNode->GetOrCreateFocusHub();
    EXPECT_NE(buttonFocusHub, nullptr);
    KeyEvent event;
    event.isRedispatch = true;
    FocusIntension intension = FocusIntension::NONE;
    auto result = buttonFocusHub->HandleKeyEvent(event, intension);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: HandleKeyEventMetaKeyTest001
 * @tc.desc: Create SetStyle.
 * @tc.type: FUNC
 */
HWTEST_F(FocusEventHandlerTestNg, HandleKeyEventMetaKeyTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Test HandleKeyEventMetaKey with KeyCode::KEY_0
     * expected: PreIme consume and metaKey is 0;
     */
    auto context = MockPipelineContext::GetCurrent();
    auto focusManager = context->GetOrCreateFocusManager();
    ASSERT_NE(context, nullptr);
    KeyEvent event;
    event.isRedispatch = false;
    event.isPreIme = true;
    event.code = KeyCode::KEY_0;
    event.pressedCodes = { KeyCode::KEY_0 };
    FocusIntension intension = FocusIntension::NONE;
    auto metaKey = 0;
    auto onKeyEventCallback = [&metaKey](KeyEventInfo& event) {
        if (event.GetMetaKey() == 1) {
            metaKey = 1;
        }
        event.SetStopPropagation(true);
        return true;
    };
    auto buttonNode = CreateTestTreeWithDefaultFocus();
    EXPECT_NE(buttonNode, nullptr);
    auto buttonFocusHub = buttonNode->GetOrCreateFocusHub();
    EXPECT_NE(buttonFocusHub, nullptr);
    buttonFocusHub->SetOnKeyPreIme(std::move(onKeyEventCallback));
    auto result = buttonFocusHub->HandleKeyEvent(event, intension);
    EXPECT_EQ(result, true);
    EXPECT_EQ(metaKey, 0);

    /**
     * @tc.steps: step2. Test HandleKeyEventMetaKey with KeyCode::KEY_META_LEFT
     * expected: PreIme consume and metaKey is 1;
     */
    event.code = KeyCode::KEY_META_LEFT;
    event.pressedCodes = { KeyCode::KEY_META_LEFT };
    auto result2 = buttonFocusHub->HandleKeyEvent(event, intension);
    EXPECT_EQ(result2, true);
    EXPECT_EQ(metaKey, 1);

    /**
     * @tc.steps: step3. Test HandleKeyEventMetaKey with KeyCode::KEY_META_RIGHT
     * expected: PreIme consume and metaKey is 1;
     */
    metaKey = 0;
    event.code = KeyCode::KEY_META_RIGHT;
    event.pressedCodes = { KeyCode::KEY_META_RIGHT };
    auto result3 = buttonFocusHub->HandleKeyEvent(event, intension);
    EXPECT_EQ(result3, true);
    EXPECT_EQ(metaKey, 1);
}

/**
 * @tc.name: HandleKeyEventOnClickTest001
 * @tc.desc: Create SetStyle.
 * @tc.type: FUNC
 */
HWTEST_F(FocusEventHandlerTestNg, HandleKeyEventOnClickTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set APITargetVersion 12
     * expected: ret is equal to expect;
     */
    KeyEvent event;
    event.isRedispatch = false;
    event.isPreIme = false;
    for (auto& testcase : HandleKeyEventClickOnVersion12TestCase) {
        auto context = MockPipelineContext::GetCurrent();
        ASSERT_NE(context, nullptr);
        auto buttonNode = CreateTestTreeWithDefaultFocus();
        EXPECT_NE(buttonNode, nullptr);
        auto buttonFocusHub = buttonNode->GetOrCreateFocusHub();
        EXPECT_NE(buttonFocusHub, nullptr);
        MockContainer::Current()->SetApiTargetVersion(VERSION_TWELVE);
        FocusIntension intension = testcase.intension;
        buttonFocusHub->ClearOnClickCallback();
        if (testcase.needFocusHandleClick) {
            auto onClickEventCallback = [](GestureEvent& info) { return true; };
            buttonFocusHub->SetOnClickCallback(std::move(onClickEventCallback));
        }
        auto focusManager = context->GetOrCreateFocusManager();
        focusManager->isFocusActive_ = testcase.focusActive;
        auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
        context->SetThemeManager(themeManager);
        EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<AppTheme>()));
        auto appTheme = context->GetTheme<AppTheme>();
        appTheme->focusActiveByTab_ = testcase.needFocusHandleClick;
        buttonFocusHub->tabStop_ = testcase.isTabStop;
        auto result = buttonFocusHub->HandleKeyEvent(event, intension);
        EXPECT_EQ(result, testcase.expect);
    }
}

/**
 * @tc.name: HandleKeyEventOnClickTest002
 * @tc.desc: Create SetStyle.
 * @tc.type: FUNC
 */
HWTEST_F(FocusEventHandlerTestNg, HandleKeyEventOnClickTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set APITargetVersion 18
     * expected: ret is equal to expect;
     */
    KeyEvent event;
    event.isRedispatch = false;
    event.isPreIme = false;
    for (auto& testcase : HandleKeyEventClickOnVersion18TestCase) {
        auto context = MockPipelineContext::GetCurrent();
        ASSERT_NE(context, nullptr);
        auto buttonNode = CreateTestTreeWithDefaultFocus();
        EXPECT_NE(buttonNode, nullptr);
        auto buttonFocusHub = buttonNode->GetOrCreateFocusHub();
        EXPECT_NE(buttonFocusHub, nullptr);
        MockContainer::Current()->SetApiTargetVersion(VERSION_EIGHTEEN);
        FocusIntension intension = testcase.intension;
        buttonFocusHub->ClearOnClickCallback();
        if (testcase.needFocusHandleClick) {
            auto onClickEventCallback = [](GestureEvent& info) { return true; };
            buttonFocusHub->SetOnClickCallback(std::move(onClickEventCallback));
        }
        auto focusManager = context->GetOrCreateFocusManager();
        focusManager->isFocusActive_ = testcase.focusActive;
        auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
        context->SetThemeManager(themeManager);
        EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<AppTheme>()));
        auto appTheme = context->GetTheme<AppTheme>();
        appTheme->focusActiveByTab_ = testcase.needFocusHandleClick;
        buttonFocusHub->tabStop_ = testcase.isTabStop;
        auto result = buttonFocusHub->HandleKeyEvent(event, intension);
        EXPECT_EQ(result, testcase.expect);
    }
}

/**
 * @tc.name: HandleCrownEventTest001
 * @tc.desc: Create SetStyle.
 * @tc.type: FUNC
 */
HWTEST_F(FocusEventHandlerTestNg, HandleCrownEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set CrownEventInternal
     * expected: ret is equal to expect;
     */
    CrownEvent event;
    FocusEvent focusEvent(static_cast<const NonPointerEvent&>(event));
    auto consume = false;
    auto onCrownEventCallbackInternal = [&consume](const CrownEvent&) {
        consume = true;
        return true;
    };
    auto buttonNode = CreateTestTreeWithDefaultFocus();
    EXPECT_NE(buttonNode, nullptr);
    auto buttonFocusHub = buttonNode->GetOrCreateFocusHub();
    EXPECT_NE(buttonFocusHub, nullptr);
    buttonFocusHub->SetOnCrownEventInternal(std::move(onCrownEventCallbackInternal));
    auto result = buttonFocusHub->OnFocusEventNode(focusEvent);
    EXPECT_EQ(consume, result);

    /**
     * @tc.steps: step2. Set CrownEventUser
     * expected: ret is equal to expect;
     */
    consume = false;
    auto consume2 = false;
    auto onCrownEventCallbackUser = [&consume2](CrownEventInfo& crownInfo) {
        crownInfo.SetStopPropagation(true);
        consume2 = true;
        return true;
    };
    buttonFocusHub->SetOnCrownCallback(std::move(onCrownEventCallbackUser));
    result = buttonFocusHub->OnFocusEventNode(focusEvent);
    EXPECT_EQ(consume, false);
    EXPECT_EQ(consume2, result);
}
} // namespace OHOS::Ace::NG
