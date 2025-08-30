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
#include "frameworks/core/pipeline/pipeline_base.h"
#include "core/components/web/web_property.h"
#include "core/components_ng/pattern/web/web_pattern.h"
#include "core/components/web/resource/web_delegate.h"
#include "test/mock/core/common/mock_container.h"
#include "test/unittest/core/pattern/web/mock_web_delegate.h"

#include "adapter/ohos/entrance/ace_container.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#undef protected
#undef private

#include "core/components_ng/base/view_stack_processor.h"
#include "interfaces/inner_api/ui_session/ui_session_manager.h"

using namespace testing;
using namespace testing::ext;

namespace {
class MockNWebAccessibilityNodeInfo : public OHOS::NWeb::NWebAccessibilityNodeInfo {
public:
    MOCK_METHOD(std::string, GetHint, (), (override));
    MOCK_METHOD(std::string, GetError, (), (override));
    MOCK_METHOD(int32_t, GetRectX, (), (override));
    MOCK_METHOD(int32_t, GetRectY, (), (override));
    MOCK_METHOD(void, SetPageId, (int32_t pageId), (override));
    MOCK_METHOD(int32_t, GetPageId, (), (override));
    MOCK_METHOD(std::vector<uint32_t>, GetActions, (), (override));
    MOCK_METHOD(std::string, GetContent, (), (override));
    MOCK_METHOD(std::vector<int64_t>, GetChildIds, (), (override));
    MOCK_METHOD(void, SetParentId, (int64_t parentId), (override));
    MOCK_METHOD(int64_t, GetParentId, (), (override));
    MOCK_METHOD(bool, GetIsHeading, (), (override));
    MOCK_METHOD(bool, GetIsChecked, (), (override));
    MOCK_METHOD(bool, GetIsEnabled, (), (override));
    MOCK_METHOD(bool, GetIsFocused, (), (override));
    MOCK_METHOD(int32_t, GetRectWidth, (), (override));
    MOCK_METHOD(int32_t, GetRectHeight, (), (override));
    MOCK_METHOD(bool, GetIsVisible, (), (override));
    MOCK_METHOD(bool, GetIsHinting, (), (override));
    MOCK_METHOD(bool, GetIsEditable, (), (override));
    MOCK_METHOD(bool, GetIsSelected, (), (override));
    MOCK_METHOD(size_t, GetItemCounts, (), (override));
    MOCK_METHOD(int32_t, GetLiveRegion, (), (override));
    MOCK_METHOD(bool, GetIsPassword, (), (override));
    MOCK_METHOD(bool, GetIsCheckable, (), (override));
    MOCK_METHOD(bool, GetIsClickable, (), (override));
    MOCK_METHOD(bool, GetIsFocusable, (), (override));
    MOCK_METHOD(bool, GetIsScrollable, (), (override));
    MOCK_METHOD(bool, GetIsDeletable, (), (override));
    MOCK_METHOD(int64_t, GetAccessibilityId, (), (override));
    MOCK_METHOD(bool, GetIsPopupSupported, (), (override));
    MOCK_METHOD(bool, GetIsContentInvalid, (), (override));
    MOCK_METHOD(int32_t, GetSelectionEnd, (), (override));
    MOCK_METHOD(int32_t, GetSelectionStart, (), (override));
    MOCK_METHOD(float, GetRangeInfoMin, (), (override));
    MOCK_METHOD(float, GetRangeInfoMax, (), (override));
    MOCK_METHOD(float, GetRangeInfoCurrent, (), (override));
    MOCK_METHOD(int32_t, GetInputType, (), (override));
    MOCK_METHOD(std::string, GetComponentType, (), (override));
    MOCK_METHOD(std::string, GetDescriptionInfo, (), (override));
    MOCK_METHOD(int32_t, GetGridRows, (), (override));
    MOCK_METHOD(int32_t, GetGridItemRow, (), (override));
    MOCK_METHOD(int32_t, GetGridColumns, (), (override));
    MOCK_METHOD(int32_t, GetGridItemColumn, (), (override));
    MOCK_METHOD(int32_t, GetGridItemRowSpan, (), (override));
    MOCK_METHOD(int32_t, GetGridSelectedMode, (), (override));
    MOCK_METHOD(int32_t, GetGridItemColumnSpan, (), (override));
    MOCK_METHOD(bool, GetIsAccessibilityFocus, (), (override));
    MOCK_METHOD(bool, GetIsPluralLineSupported, (), (override));

    MOCK_METHOD(bool, GetIsAccessibilityGroup, (), (override));
    MOCK_METHOD(std::string, GetAccessibilityLevel, (), (override));
    MOCK_METHOD(std::string, GetAccessibilityDescription, (), (override));
    MOCK_METHOD(std::string, GetAccessibilityText, (), (override));
    MOCK_METHOD(std::string, GetComponentTypeDescription, (), (override));
    MOCK_METHOD(int32_t, GetCheckboxGroupSelectedStatus, (), (override));
    MOCK_METHOD(std::string, GetExpandedState, (), (override));
    MOCK_METHOD(std::string, GetHtmlElementId, (), (override));
};
} // namespace

namespace OHOS::Ace::NG {
namespace {
RefPtr<WebPattern> g_webPattern = nullptr;
}

class WebAccessibilityEventReportTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void WebAccessibilityEventReportTest::SetUpTestCase()
{
#ifdef OHOS_STANDARD_SYSTEM
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockContainer::Current()->pipelineContext_ = MockPipelineContext::GetCurrentContext();
    MockContainer::Current()->pipelineContext_->taskExecutor_ = MockContainer::Current()->taskExecutor_;

    std::string src = "web_test";
    RefPtr<WebController> controller = AceType::MakeRefPtr<WebController>();
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::WEB_ETS_TAG, nodeId, [src, controller]() { return AceType::MakeRefPtr<WebPattern>(src, controller); });
    stack->Push(frameNode);

    g_webPattern = frameNode->GetPattern<WebPattern>();
    CHECK_NULL_VOID(g_webPattern);
    g_webPattern->OnModifyDone();
#endif
}

void WebAccessibilityEventReportTest::TearDownTestCase()
{
#ifdef OHOS_STANDARD_SYSTEM
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
    g_webPattern = nullptr;
#endif
}

void WebAccessibilityEventReportTest::SetUp()
{
#ifdef OHOS_STANDARD_SYSTEM
    if (g_webPattern) {
        g_webPattern->accessibilityState_ = false;
        g_webPattern->textBlurAccessibilityEnable_ = false;
        g_webPattern->inspectorAccessibilityEnable_ = false;
        g_webPattern->webAccessibilityEventReport_ = nullptr;
    }
    OHOS::Ace::SetReturnStatus("");
    OHOS::Ace::SetReturnNode(nullptr);
#endif
}

void WebAccessibilityEventReportTest::TearDown()
{
#ifdef OHOS_STANDARD_SYSTEM
    OHOS::Ace::SetReturnStatus("");
    OHOS::Ace::SetReturnNode(nullptr);
#endif
}

/**
 * @tc.name: GetAccessibilityEventReport
 * @tc.desc: Test GetAccessibilityEventReport.
 * @tc.type: FUNC
 */
HWTEST_F(WebAccessibilityEventReportTest, GetAccessibilityEventReport, TestSize.Level0)
{
#ifdef OHOS_STANDARD_SYSTEM
    EXPECT_NE(g_webPattern->GetAccessibilityEventReport(), nullptr);
    EXPECT_NE(g_webPattern->GetAccessibilityEventReport(), nullptr);
#endif
}

/**
 * @tc.name: InitInputEventReportCallback
 * @tc.desc: Test InitInputEventReportCallback.
 * @tc.type: FUNC
 */
HWTEST_F(WebAccessibilityEventReportTest, InitInputEventReportCallback, TestSize.Level0)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webCallback = [](bool isRegister) {};
    UiSessionManager::GetInstance()->SaveRegisterForWebFunction(webCallback);
    UiSessionManager::GetInstance()->NotifyAllWebPattern(true);

    g_webPattern->InitInputEventReportCallback();
    // no check because of the wrong mock ui_session_manger, use register all callback instead

    auto report = g_webPattern->GetAccessibilityEventReport();
    ASSERT_NE(report, nullptr);
    report->SetIsFirstRegister(true);
    report->RegisterAllReportEventCallback();
    EXPECT_FALSE(report->isFirstRegister_);
    EXPECT_TRUE(report->eventReportEnable_);

    UiSessionManager::GetInstance()->NotifyAllWebPattern(false);
    g_webPattern->InitInputEventReportCallback();
    EXPECT_FALSE(report->eventReportEnable_);
#endif
}

/**
 * @tc.name: SetEventReportEnable
 * @tc.desc: Test SetEventReportEnable.
 * @tc.type: FUNC
 */
HWTEST_F(WebAccessibilityEventReportTest, SetEventReportEnable, TestSize.Level0)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto report = g_webPattern->GetAccessibilityEventReport();
    report->SetEventReportEnable(false);
    report->SetEventReportEnable(true);
    EXPECT_TRUE(report->eventReportEnable_);

    report->SetEventReportEnable(false);
    EXPECT_FALSE(report->eventReportEnable_);

    g_webPattern->textBlurAccessibilityEnable_ = true;
    report->SetEventReportEnable(true);
    report->SetEventReportEnable(false);
    EXPECT_FALSE(report->eventReportEnable_);

    g_webPattern->inspectorAccessibilityEnable_ = true;
    report->SetEventReportEnable(true);
    report->SetEventReportEnable(false);
    EXPECT_FALSE(report->eventReportEnable_);

    g_webPattern->accessibilityState_ = true;
    report->SetEventReportEnable(true);
    report->SetEventReportEnable(false);
    EXPECT_FALSE(report->eventReportEnable_);
#endif
}

/**
 * @tc.name: SetAccessibilityState
 * @tc.desc: Test SetAccessibilityState.
 * @tc.type: FUNC
 */
HWTEST_F(WebAccessibilityEventReportTest, SetAccessibilityState, TestSize.Level0)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto report = g_webPattern->GetAccessibilityEventReport();
    g_webPattern->accessibilityState_ = true;
    report->eventReportEnable_ = true;
    g_webPattern->SetAccessibilityState(false);
    EXPECT_FALSE(g_webPattern->accessibilityState_);
#endif
}

/**
 * @tc.name: GetAccessibilityNodeById
 * @tc.desc: Test GetAccessibilityNodeById.
 * @tc.type: FUNC
 */
HWTEST_F(WebAccessibilityEventReportTest, GetAccessibilityNodeById, TestSize.Level0)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto report = AceType::MakeRefPtr<WebAccessibilityEventReport>(AceType::WeakClaim(AceType::RawPtr(g_webPattern)));
    OHOS::Ace::SetReturnStatus("true");
    EXPECT_EQ(report->GetAccessibilityNodeById(1), nullptr);
    report->eventReportEnable_ = true;
    EXPECT_NE(report->GetAccessibilityNodeById(1), nullptr);
#endif
}

/**
 * @tc.name: RegisterAllReportEventCallback
 * @tc.desc: Test RegisterAllReportEventCallback.
 * @tc.type: FUNC
 */
HWTEST_F(WebAccessibilityEventReportTest, RegisterAllReportEventCallback, TestSize.Level0)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto report = AceType::MakeRefPtr<WebAccessibilityEventReport>(AceType::WeakClaim(AceType::RawPtr(g_webPattern)));
    report->RegisterAllReportEventCallback();

    EXPECT_TRUE(report->eventReportEnable_);

    EXPECT_NE(report->textFocusCallback_, nullptr);
    EXPECT_NE(report->textBlurCallback_, nullptr);
    EXPECT_NE(report->textChangeCallback_, nullptr);
#endif
}

/**
 * @tc.name: RegisterReportBlurEventCallback
 * @tc.desc: Test RegisterReportBlurEventCallback.
 * @tc.type: FUNC
 */
HWTEST_F(WebAccessibilityEventReportTest, RegisterReportBlurEventCallback, TestSize.Level0)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto report = AceType::MakeRefPtr<WebAccessibilityEventReport>(AceType::WeakClaim(AceType::RawPtr(g_webPattern)));
    auto blurCallback = [](int64_t accessibilityId, const std::string data) {};
    report->RegisterCallback(std::move(blurCallback), AccessibilityEventType::BLUR);
    EXPECT_TRUE(report->eventReportEnable_);
#endif
}

/**
 * @tc.name: RegisterReportFocusEventCallback
 * @tc.desc: Test RegisterReportFocusEventCallback.
 * @tc.type: FUNC
 */
HWTEST_F(WebAccessibilityEventReportTest, RegisterReportFocusEventCallback, TestSize.Level0)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto report = AceType::MakeRefPtr<WebAccessibilityEventReport>(AceType::WeakClaim(AceType::RawPtr(g_webPattern)));
    auto focusCallback = [](int64_t accessibilityId, const std::string data) {};
    report->RegisterCallback(std::move(focusCallback), AccessibilityEventType::FOCUS);
    EXPECT_TRUE(report->eventReportEnable_);
#endif
}

/**
 * @tc.name: RegisterReportTextChangeEventCallback
 * @tc.desc: Test RegisterReportTextChangeEventCallback.
 * @tc.type: FUNC
 */
HWTEST_F(WebAccessibilityEventReportTest, RegisterReportTextChangeEventCallback, TestSize.Level0)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto report = AceType::MakeRefPtr<WebAccessibilityEventReport>(AceType::WeakClaim(AceType::RawPtr(g_webPattern)));

    auto textChangeCallback = [](int64_t accessibilityId, const std::string data) {};
    report->RegisterCallback(std::move(textChangeCallback), AccessibilityEventType::TEXT_CHANGE);

    EXPECT_TRUE(report->eventReportEnable_);
#endif
}

/**
 * @tc.name: RegisterUndefinedReportEventCallback_001
 * @tc.desc: Test RegisterUndefinedReportEventCallback_001.
 * @tc.type: FUNC
 */
HWTEST_F(WebAccessibilityEventReportTest, RegisterUndefinedReportEventCallback_001, TestSize.Level0)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto report = AceType::MakeRefPtr<WebAccessibilityEventReport>(AceType::WeakClaim(AceType::RawPtr(g_webPattern)));

    auto clickCallback = [](int64_t accessibilityId, const std::string data) {};
    report->RegisterCallback(std::move(clickCallback), AccessibilityEventType::CLICK);

    auto longPressCallback = [](int64_t accessibilityId, const std::string data) {};
    report->RegisterCallback(std::move(longPressCallback), AccessibilityEventType::LONG_PRESS);

    auto selectedCallback = [](int64_t accessibilityId, const std::string data) {};
    report->RegisterCallback(std::move(selectedCallback), AccessibilityEventType::SELECTED);

    auto ejectDismissCallback = [](int64_t accessibilityId, const std::string data) {};
    report->RegisterCallback(std::move(ejectDismissCallback), AccessibilityEventType::EJECT_DISMISS);

    auto mouseCallback = [](int64_t accessibilityId, const std::string data) {};
    report->RegisterCallback(std::move(mouseCallback), AccessibilityEventType::MOUSE);

    auto keyboardBackCallback = [](int64_t accessibilityId, const std::string data) {};
    report->RegisterCallback(std::move(keyboardBackCallback), AccessibilityEventType::KEYBOARD_BACK);

    auto keyboardUpCallback = [](int64_t accessibilityId, const std::string data) {};
    report->RegisterCallback(std::move(keyboardUpCallback), AccessibilityEventType::KEYBOARD_UP);

    auto keyboardDownCallback = [](int64_t accessibilityId, const std::string data) {};
    report->RegisterCallback(std::move(keyboardDownCallback), AccessibilityEventType::KEYBOARD_DOWN);

    auto keyboardLeftCallback = [](int64_t accessibilityId, const std::string data) {};
    report->RegisterCallback(std::move(keyboardLeftCallback), AccessibilityEventType::KEYBOARD_LEFT);

    auto keyboardRightCallback = [](int64_t accessibilityId, const std::string data) {};
    report->RegisterCallback(std::move(keyboardRightCallback), AccessibilityEventType::KEYBOARD_RIGHT);

    auto keyboardCenterCallback = [](int64_t accessibilityId, const std::string data) {};
    report->RegisterCallback(std::move(keyboardCenterCallback), AccessibilityEventType::KEYBOARD_CENTER);

    auto handleACallback = [](int64_t accessibilityId, const std::string data) {};
    report->RegisterCallback(std::move(handleACallback), AccessibilityEventType::HANDLE_A);

    auto handleSelectCallback = [](int64_t accessibilityId, const std::string data) {};
    report->RegisterCallback(std::move(handleSelectCallback), AccessibilityEventType::HANDLE_SELECT);

    auto keyboardTabCallback = [](int64_t accessibilityId, const std::string data) {};
    report->RegisterCallback(std::move(keyboardTabCallback), AccessibilityEventType::KEYBOARD_TAB);

    EXPECT_FALSE(report->eventReportEnable_);
#endif
}

/**
 * @tc.name: RegisterUndefinedReportEventCallback_002
 * @tc.desc: Test RegisterUndefinedReportEventCallback_002.
 * @tc.type: FUNC
 */
HWTEST_F(WebAccessibilityEventReportTest, RegisterUndefinedReportEventCallback_002, TestSize.Level0)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto report = AceType::MakeRefPtr<WebAccessibilityEventReport>(AceType::WeakClaim(AceType::RawPtr(g_webPattern)));

    auto keyboardSpaceCallback = [](int64_t accessibilityId, const std::string data) {};
    report->RegisterCallback(std::move(keyboardSpaceCallback), AccessibilityEventType::KEYBOARD_SPACE);

    auto keyboardEnterCallback = [](int64_t accessibilityId, const std::string data) {};
    report->RegisterCallback(std::move(keyboardEnterCallback), AccessibilityEventType::KEYBOARD_ENTER);

    auto keyboardEscapeCallback = [](int64_t accessibilityId, const std::string data) {};
    report->RegisterCallback(std::move(keyboardEscapeCallback), AccessibilityEventType::KEYBOARD_ESCAPE);

    auto keyboardNumberEnterCallback = [](int64_t accessibilityId, const std::string data) {};
    report->RegisterCallback(std::move(keyboardNumberEnterCallback), AccessibilityEventType::KEYBOARD_NUMBER_ENTER);

    auto tvControlMediaPlayCallback = [](int64_t accessibilityId, const std::string data) {};
    report->RegisterCallback(std::move(tvControlMediaPlayCallback), AccessibilityEventType::TV_CONTROL_MEDIA_PLAY);

    auto pageChangeCallback = [](int64_t accessibilityId, const std::string data) {};
    report->RegisterCallback(std::move(pageChangeCallback), AccessibilityEventType::PAGE_CHANGE);

    auto hoverEnterEventCallback = [](int64_t accessibilityId, const std::string data) {};
    report->RegisterCallback(std::move(hoverEnterEventCallback), AccessibilityEventType::HOVER_ENTER_EVENT);

    auto hoverExitEventCallback = [](int64_t accessibilityId, const std::string data) {};
    report->RegisterCallback(std::move(hoverExitEventCallback), AccessibilityEventType::HOVER_EXIT_EVENT);

    auto touchStartCallback = [](int64_t accessibilityId, const std::string data) {};
    report->RegisterCallback(std::move(touchStartCallback), AccessibilityEventType::TOUCH_START);

    auto touchMoveCallback = [](int64_t accessibilityId, const std::string data) {};
    report->RegisterCallback(std::move(touchMoveCallback), AccessibilityEventType::TOUCH_MOVE);

    auto touchCancelCallback = [](int64_t accessibilityId, const std::string data) {};
    report->RegisterCallback(std::move(touchCancelCallback), AccessibilityEventType::TOUCH_CANCEL);

    auto touchEndCallback = [](int64_t accessibilityId, const std::string data) {};
    report->RegisterCallback(std::move(touchEndCallback), AccessibilityEventType::TOUCH_END);

    auto changeCallback = [](int64_t accessibilityId, const std::string data) {};
    report->RegisterCallback(std::move(changeCallback), AccessibilityEventType::CHANGE);

    auto componentChangeCallback = [](int64_t accessibilityId, const std::string data) {};
    report->RegisterCallback(std::move(componentChangeCallback), AccessibilityEventType::COMPONENT_CHANGE);

    EXPECT_FALSE(report->eventReportEnable_);
#endif
}

/**
 * @tc.name: RegisterUndefinedReportEventCallback_003
 * @tc.desc: Test RegisterUndefinedReportEventCallback_003.
 * @tc.type: FUNC
 */
HWTEST_F(WebAccessibilityEventReportTest, RegisterUndefinedReportEventCallback_003, TestSize.Level0)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto report = AceType::MakeRefPtr<WebAccessibilityEventReport>(AceType::WeakClaim(AceType::RawPtr(g_webPattern)));

    auto scrollEndCallback = [](int64_t accessibilityId, const std::string data) {};
    report->RegisterCallback(std::move(scrollEndCallback), AccessibilityEventType::SCROLL_END);

    auto textSelectionUpdateCallback = [](int64_t accessibilityId, const std::string data) {};
    report->RegisterCallback(std::move(textSelectionUpdateCallback), AccessibilityEventType::TEXT_SELECTION_UPDATE);

    auto accessibilityFocusedCallback = [](int64_t accessibilityId, const std::string data) {};
    report->RegisterCallback(std::move(accessibilityFocusedCallback), AccessibilityEventType::ACCESSIBILITY_FOCUSED);

    auto accessibilityFocusClearedCallback = [](int64_t accessibilityId, const std::string data) {};
    report->RegisterCallback(
        std::move(accessibilityFocusClearedCallback), AccessibilityEventType::ACCESSIBILITY_FOCUS_CLEARED);

    auto textMoveUnitCallback = [](int64_t accessibilityId, const std::string data) {};
    report->RegisterCallback(std::move(textMoveUnitCallback), AccessibilityEventType::TEXT_MOVE_UNIT);

    auto requestFocusCallback = [](int64_t accessibilityId, const std::string data) {};
    report->RegisterCallback(std::move(requestFocusCallback), AccessibilityEventType::REQUEST_FOCUS);

    auto scrollStartCallback = [](int64_t accessibilityId, const std::string data) {};
    report->RegisterCallback(std::move(scrollStartCallback), AccessibilityEventType::SCROLL_START);

    auto pageCloseCallback = [](int64_t accessibilityId, const std::string data) {};
    report->RegisterCallback(std::move(pageCloseCallback), AccessibilityEventType::PAGE_CLOSE);

    auto announceForAccessibilityCallback = [](int64_t accessibilityId, const std::string data) {};
    report->RegisterCallback(
        std::move(announceForAccessibilityCallback), AccessibilityEventType::ANNOUNCE_FOR_ACCESSIBILITY);

    auto pageOpenCallback = [](int64_t accessibilityId, const std::string data) {};
    report->RegisterCallback(std::move(pageOpenCallback), AccessibilityEventType::PAGE_OPEN);

    auto elementInfoChangeCallback = [](int64_t accessibilityId, const std::string data) {};
    report->RegisterCallback(std::move(elementInfoChangeCallback), AccessibilityEventType::ELEMENT_INFO_CHANGE);

    auto announceForAccessibilityNotInterruptCallback = [](int64_t accessibilityId, const std::string data) {};
    report->RegisterCallback(std::move(announceForAccessibilityNotInterruptCallback),
        AccessibilityEventType::ANNOUNCE_FOR_ACCESSIBILITY_NOT_INTERRUPT);

    auto scrollingEventCallback = [](int64_t accessibilityId, const std::string data) {};
    report->RegisterCallback(std::move(scrollingEventCallback), AccessibilityEventType::SCROLLING_EVENT);

    auto unknownCallback = [](int64_t accessibilityId, const std::string data) {};
    report->RegisterCallback(std::move(unknownCallback), AccessibilityEventType::UNKNOWN);

    EXPECT_FALSE(report->eventReportEnable_);
#endif
}

/**
 * @tc.name: UnregisterCallback
 * @tc.desc: Test UnregisterCallback.
 * @tc.type: FUNC
 */
HWTEST_F(WebAccessibilityEventReportTest, UnregisterCallback, TestSize.Level0)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto report = AceType::MakeRefPtr<WebAccessibilityEventReport>(AceType::WeakClaim(AceType::RawPtr(g_webPattern)));
    report->RegisterAllReportEventCallback();
    EXPECT_TRUE(report->eventReportEnable_);

    report->UnregisterCallback();
    EXPECT_FALSE(report->eventReportEnable_);

    EXPECT_EQ(report->textFocusCallback_, nullptr);
    EXPECT_EQ(report->textBlurCallback_, nullptr);
    EXPECT_EQ(report->textChangeCallback_, nullptr);
#endif
}

/**
 * @tc.name: ReportEvent
 * @tc.desc: Test ReportEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebAccessibilityEventReportTest, ReportEvent, TestSize.Level0)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto report = AceType::MakeRefPtr<WebAccessibilityEventReport>(AceType::WeakClaim(AceType::RawPtr(g_webPattern)));

    report->ReportEvent(AccessibilityEventType::FOCUS, 1);
    report->eventReportEnable_ = true;

    report->lastFocusInputId_ = 2;
    report->ReportEvent(AccessibilityEventType::FOCUS, 1);
    EXPECT_EQ(report->lastFocusReportId_, 2);

    report->ReportEvent(AccessibilityEventType::BLUR, 2);
    report->ReportEvent(AccessibilityEventType::BLUR, 3);

    report->ReportEvent(AccessibilityEventType::TEXT_CHANGE, 4);
#endif
}

/**
 * @tc.name: ReportTextBlurEventByFocus
 * @tc.desc: Test ReportTextBlurEventByFocus.
 * @tc.type: FUNC
 */
HWTEST_F(WebAccessibilityEventReportTest, ReportTextBlurEventByFocus, TestSize.Level0)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto report = AceType::MakeRefPtr<WebAccessibilityEventReport>(AceType::WeakClaim(AceType::RawPtr(g_webPattern)));
    report->lastFocusInputId_ = 0;
    report->ReportTextBlurEventByFocus(1);
    EXPECT_EQ(report->lastFocusInputId_, 0);
    EXPECT_EQ(report->lastFocusReportId_, 0);

    OHOS::Ace::SetReturnStatus("true");
    report->RegisterAllReportEventCallback();

    report->lastFocusInputId_ = 0;
    report->ReportTextBlurEventByFocus(1);
    EXPECT_EQ(report->lastFocusInputId_, 1);
    EXPECT_EQ(report->lastFocusReportId_, 0);

    report->ReportTextBlurEventByFocus(1);
    EXPECT_EQ(report->lastFocusInputId_, 1);
    EXPECT_EQ(report->lastFocusReportId_, 0);

    report->ReportTextBlurEventByFocus(2);
    EXPECT_EQ(report->lastFocusInputId_, 2);
    EXPECT_EQ(report->lastFocusReportId_, 1);
#endif
}

/**
 * @tc.name: ParseNodeContent
 * @tc.desc: Test ParseNodeContent.
 * @tc.type: FUNC
 */
HWTEST_F(WebAccessibilityEventReportTest, ParseNodeContent, TestSize.Level0)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto report = AceType::MakeRefPtr<WebAccessibilityEventReport>(AceType::WeakClaim(AceType::RawPtr(g_webPattern)));
    auto node = std::make_shared<MockNWebAccessibilityNodeInfo>();
    std::string nodeText = "";
    {
        EXPECT_CALL(*node, GetIsPassword()).WillOnce(testing::Return(true));
        report->ParseNodeContent(node, nodeText);
        EXPECT_EQ(nodeText, "*");
    }
    {
        EXPECT_CALL(*node, GetIsPassword()).WillOnce(testing::Return(false));
        EXPECT_CALL(*node, GetInputType())
            .WillOnce(testing::Return(static_cast<int32_t>(AceTextCategory::INPUT_TYPE_NUMBER)));
        nodeText = "123, placeholder";
        report->ParseNodeContent(node, nodeText);
        EXPECT_EQ(nodeText, "123");
    }
    {
        EXPECT_CALL(*node, GetIsPassword()).WillOnce(testing::Return(false));
        EXPECT_CALL(*node, GetInputType()).WillOnce(testing::Return(0));
        nodeText = "text";
        report->ParseNodeContent(node, nodeText);
        EXPECT_EQ(nodeText, "text");
    }
#endif
}

/**
 * @tc.name: CheckAccessibilityNodeAndReport
 * @tc.desc: Test CheckAccessibilityNodeAndReport.
 * @tc.type: FUNC
 */
HWTEST_F(WebAccessibilityEventReportTest, CheckAccessibilityNodeAndReport, TestSize.Level0)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto report = AceType::MakeRefPtr<WebAccessibilityEventReport>(AceType::WeakClaim(AceType::RawPtr(g_webPattern)));
    auto node = std::make_shared<MockNWebAccessibilityNodeInfo>();
    OHOS::Ace::SetReturnStatus("true");
    OHOS::Ace::SetReturnNode(node);

    report->RegisterAllReportEventCallback();
    {
        EXPECT_CALL(*node, GetContent()).WillOnce(testing::Return("text"));
        EXPECT_CALL(*node, GetIsEditable()).WillOnce(testing::Return(false));
        EXPECT_CALL(*node, GetIsPassword()).Times(0);
        report->CheckAccessibilityNodeAndReport(AccessibilityEventType::FOCUS, 1);
    }

    {
        EXPECT_CALL(*node, GetContent()).WillOnce(testing::Return("text"));
        EXPECT_CALL(*node, GetIsEditable()).WillOnce(testing::Return(true));
        EXPECT_CALL(*node, GetIsPassword()).WillOnce(testing::Return(true));
        report->CheckAccessibilityNodeAndReport(AccessibilityEventType::FOCUS, 1);
    }

    {
        EXPECT_CALL(*node, GetContent()).Times(4).WillRepeatedly(testing::Return("text"));
        EXPECT_CALL(*node, GetIsEditable()).Times(4).WillRepeatedly(testing::Return(true));
        EXPECT_CALL(*node, GetIsPassword()).Times(4).WillRepeatedly(testing::Return(false));

        report->CheckAccessibilityNodeAndReport(AccessibilityEventType::FOCUS, 1);
        report->CheckAccessibilityNodeAndReport(AccessibilityEventType::BLUR, 1);
        report->CheckAccessibilityNodeAndReport(AccessibilityEventType::TEXT_CHANGE, 1);
        report->CheckAccessibilityNodeAndReport(AccessibilityEventType::CLICK, 1);
    }
#endif
}

} // namespace OHOS::Ace::NG