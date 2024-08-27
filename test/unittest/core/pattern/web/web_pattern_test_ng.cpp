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

#include <gmock/gmock.h>

#include "gtest/gtest.h"
#define private public
#include "base/web/webview/ohos_nweb/include/nweb_handler.h"
#include "core/components/web/resource/web_delegate.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/web/web_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/base/utils/system_properties.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
    void DialogTheme::Builder::ParseNewPattern(const RefPtr<ThemeConstants>& themeConstants,
        const RefPtr<DialogTheme>& theme) const{};
    void DialogTheme::Builder::ParsePattern(const RefPtr<ThemeConstants>& themeConstants,
        const RefPtr<DialogTheme>& theme) const{};
}

namespace OHOS::NWeb {
class NWebDateTimeChooserCallbackMock : public NWebDateTimeChooserCallback {
public:

    void Continue(bool success, const DateTime& value) override
    {}
};

class NWebSelectPopupMenuCallbackMock : public NWebSelectPopupMenuCallback {
public:

    void Continue(const std::vector<int32_t>& indices) override
    {}

    void Cancel() override
    {}
};

class NWebCursorInfoMock : public NWebCursorInfo {
public:
    int32_t GetX() override
    {
        return 0;
    }

    int32_t GetY() override
    {
        return 0;
    }

    uint8_t* GetBuff() override
    {
        return nullptr;
    }

    float GetScale() override
    {
        return 0;
    }

    int32_t GetWidth() override
    {
        return 0;
    }

    int32_t GetHeight() override
    {
        return 0;
    }
};

class NWebSelectPopupMenuParamMock : public NWebSelectPopupMenuParam {
public:

    std::vector<std::shared_ptr<NWebSelectPopupMenuItem>> GetMenuItems() override
    {
        std::vector<std::shared_ptr<NWebSelectPopupMenuItem>> value;
        return value;
    }

    int GetItemHeight() override
    {
        return 0;
    }

    int GetSelectedItem() override
    {
        return 0;
    }

    double GetItemFontSize() override
    {
        return 0;
    }

    bool GetIsRightAligned() override
    {
        return true;
    }

    std::shared_ptr<NWebSelectMenuBound> GetSelectMenuBound() override
    {
        return 0;
    }

    bool GetIsAllowMultipleSelection() override
    {
        return true;
    }
};

}

namespace OHOS::Ace::NG {
class MockWebContextMenuParam : public WebContextMenuParam {
public:
    MOCK_METHOD(int32_t, GetXCoord, (), (const, override));
    MOCK_METHOD(int32_t, GetYCoord, (), (const, override));
    MOCK_METHOD(std::string, GetLinkUrl, (), (const, override));
    MOCK_METHOD(std::string, GetUnfilteredLinkUrl, (), (const, override));
    MOCK_METHOD(std::string, GetSourceUrl, (), (const, override));
    MOCK_METHOD(bool, HasImageContents, (), (const, override));
    MOCK_METHOD(bool, IsEditable, (), (const, override));
    MOCK_METHOD(int, GetEditStateFlags, (), (const, override));
    MOCK_METHOD(int, GetSourceType, (), (const, override));
    MOCK_METHOD(int, GetMediaType, (), (const, override));
    MOCK_METHOD(int, GetInputFieldType, (), (const, override));
    MOCK_METHOD(std::string, GetSelectionText, (), (const, override));
};

class MockContextMenuResult : public ContextMenuResult {
public:
    MOCK_METHOD(void, Cancel, (), (const, override));
    MOCK_METHOD(void, CopyImage, (), (const, override));
    MOCK_METHOD(void, Copy, (), (const, override));
    MOCK_METHOD(void, Paste, (), (const, override));
    MOCK_METHOD(void, Cut, (), (const, override));
    MOCK_METHOD(void, SelectAll, (), (const, override));
};

class MockWebContextSelectOverlay : public WebContextSelectOverlay {
public:
    MockWebContextSelectOverlay(WeakPtr<TextBase> textBase) : WebContextSelectOverlay(textBase) {}
    ~MockWebContextSelectOverlay() override = default;
    bool IsCurrentMenuVisibile()
    {
        return true;
    }
};

class MockWebContextSelectOverlayfalse : public WebContextSelectOverlay {
public:
    MockWebContextSelectOverlayfalse(WeakPtr<TextBase> textBase) : WebContextSelectOverlay(textBase) {}
    ~MockWebContextSelectOverlayfalse() override = default;
    bool IsCurrentMenuVisibile()
    {
        return false;
    }
};

class WebPatternTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void WebPatternTestNg::SetUpTestCase() {}
void WebPatternTestNg::TearDownTestCase() {}
void WebPatternTestNg::SetUp() {}
void WebPatternTestNg::TearDown() {}

/**
 * @tc.name: WebPatternTestNg_001
 * @tc.desc: Test webPattern.cpp.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, WebPatternTestNg_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webpattern;
    webpattern.delegate_ = nullptr;
    EXPECT_EQ(webpattern.delegate_, nullptr);
    webpattern.HandleFocusEvent();
    webpattern.OnWebSrcUpdate();
    webpattern.OnWebDataUpdate();
    webpattern.OnJsEnabledUpdate(true);
    webpattern.OnMediaPlayGestureAccessUpdate(true);
    webpattern.OnFileAccessEnabledUpdate(true);
    webpattern.OnOnLineImageAccessEnabledUpdate(true);
    webpattern.OnDomStorageAccessEnabledUpdate(true);
    webpattern.OnImageAccessEnabledUpdate(true);
    webpattern.OnMixedModeUpdate(MixedModeContent::MIXED_CONTENT_ALWAYS_ALLOW);
    webpattern.OnZoomAccessEnabledUpdate(true);
    webpattern.OnGeolocationAccessEnabledUpdate(true);
    webpattern.OnUserAgentUpdate("chrome");
    webpattern.OnCacheModeUpdate(WebCacheMode::DEFAULT);
    webpattern.OnWebCursiveFontUpdate("test");
    webpattern.OnWebFantasyFontUpdate("test");
    webpattern.OnWebSansSerifFontUpdate("test");
    webpattern.OnWebSerifFontUpdate("test");
    webpattern.OnWebStandardFontUpdate("test");
    webpattern.OnDefaultFixedFontSizeUpdate(0);
    webpattern.OnDefaultFontSizeUpdate(0);
    webpattern.OnMinFontSizeUpdate(0);
    webpattern.OnMinLogicalFontSizeUpdate(0);
    webpattern.OnWebFixedFontUpdate("test");
    webpattern.OnBlockNetworkUpdate(true);
    webpattern.OnDarkModeUpdate(WebDarkMode::On);
    webpattern.OnForceDarkAccessUpdate(true);
    webpattern.OnAllowWindowOpenMethodUpdate(true);
    webpattern.OnHorizontalScrollBarAccessEnabledUpdate(true);
    webpattern.OnVerticalScrollBarAccessEnabledUpdate(true);
    webpattern.OnAudioResumeIntervalUpdate(0);
    webpattern.OnAudioExclusiveUpdate(true);
#endif
}

/**
 * @tc.name: WebPatternTestNg_002
 * @tc.desc: Test webPattern.cpp.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, WebPatternTestNg_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern->delegate_, nullptr);
    webPattern->HandleFocusEvent();
    webPattern->OnWebSrcUpdate();
    webPattern->OnWebDataUpdate();
    webPattern->isUrlLoaded_ = true;
    webPattern->OnWebSrcUpdate();
    webPattern->OnWebDataUpdate();
    webPattern->OnJsEnabledUpdate(true);
    webPattern->OnMediaPlayGestureAccessUpdate(true);
    webPattern->OnFileAccessEnabledUpdate(true);
    webPattern->OnOnLineImageAccessEnabledUpdate(true);
    webPattern->OnDomStorageAccessEnabledUpdate(true);
    webPattern->OnImageAccessEnabledUpdate(true);
    webPattern->OnMixedModeUpdate(MixedModeContent::MIXED_CONTENT_ALWAYS_ALLOW);
    webPattern->OnZoomAccessEnabledUpdate(true);
    webPattern->OnGeolocationAccessEnabledUpdate(true);
    webPattern->OnUserAgentUpdate("chrome");
    webPattern->OnCacheModeUpdate(WebCacheMode::DEFAULT);
    webPattern->OnWebCursiveFontUpdate("test");
    webPattern->OnWebFantasyFontUpdate("test");
    webPattern->OnWebSansSerifFontUpdate("test");
    webPattern->OnWebSerifFontUpdate("test");
    webPattern->OnWebStandardFontUpdate("test");
    webPattern->OnDefaultFixedFontSizeUpdate(0);
    webPattern->OnDefaultFontSizeUpdate(0);
    webPattern->OnMinFontSizeUpdate(0);
    webPattern->OnMinLogicalFontSizeUpdate(0);
    webPattern->OnWebFixedFontUpdate("test");
    webPattern->OnBlockNetworkUpdate(true);
    webPattern->OnAllowWindowOpenMethodUpdate(true);
    webPattern->OnHorizontalScrollBarAccessEnabledUpdate(true);
    webPattern->OnVerticalScrollBarAccessEnabledUpdate(true);
#endif
}

/**
 * @tc.name: WebPatternTestNg_003
 * @tc.desc: Test webPattern.cpp.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, WebPatternTestNg_003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern->delegate_, nullptr);
    GestureEvent event;
    event.SetInputEventType(InputEventType::TOUCH_SCREEN);
    webPattern->HandleDragMove(event);
    event.SetInputEventType(InputEventType::AXIS);
    webPattern->HandleDragMove(event);
    webPattern->OnDarkModeUpdate(WebDarkMode::On);
    webPattern->OnForceDarkAccessUpdate(true);
    webPattern->OnAudioResumeIntervalUpdate(0);
    webPattern->OnAudioExclusiveUpdate(true);
    webPattern->isEnhanceSurface_ = true;
    webPattern->delegate_ = nullptr;
    webPattern->OnModifyDone();
#endif
}

/**
 * @tc.name: OnScrollBarColorUpdate004
 * @tc.desc: OnScrollBarColorUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnScrollBarColorUpdate004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern->delegate_, nullptr);
    webPattern->OnAreaChangedInner();
    webPattern->isInWindowDrag_ = true;
    webPattern->OnAreaChangedInner();
    const std::string value;
    webPattern->OnScrollBarColorUpdate(value);
    SelectOverlayInfo selectInfo;
    webPattern->RegisterSelectOverlayEvent(selectInfo);
    TouchEventInfo event("webtest");
    selectInfo.onTouchMove(event);
    webPattern->OnWindowSizeChanged(0, 0, WindowSizeChangeReason::DRAG_START);
    webPattern->OnWindowSizeChanged(0, 0, WindowSizeChangeReason::DRAG_END);
    webPattern->OnWindowSizeChanged(0, 0, WindowSizeChangeReason::DRAG_END);
    webPattern->OnWindowSizeChanged(0, 0, WindowSizeChangeReason::DRAG);
    webPattern->OnCompleteSwapWithNewSize();
    webPattern->OnResizeNotWork();
    webPattern->isInWindowDrag_ = true;
    webPattern->OnCompleteSwapWithNewSize();
    webPattern->OnResizeNotWork();
    webPattern->OnWindowSizeChanged(0, 0, WindowSizeChangeReason::DRAG);
    webPattern->isWaiting_ = true;
    webPattern->OnWindowSizeChanged(0, 0, WindowSizeChangeReason::DRAG);
    webPattern->OnCompleteSwapWithNewSize();
    webPattern->OnResizeNotWork();
    webPattern->isInWindowDrag_ = false;
    webPattern->OnCompleteSwapWithNewSize();
    webPattern->OnResizeNotWork();
#endif
}

/**
 * @tc.name: OnScrollBarColorUpdate005
 * @tc.desc: OnScrollBarColorUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnScrollBarColorUpdate005, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webpattern;
    webpattern.delegate_ = nullptr;
    EXPECT_EQ(webpattern.delegate_, nullptr);
    const std::string value;
    webpattern.OnScrollBarColorUpdate(value);
    SystemProperties::SetExtSurfaceEnabled(true);
    webpattern.InitEnhanceSurfaceFlag();
    SystemProperties::SetExtSurfaceEnabled(false);
    webpattern.InitEnhanceSurfaceFlag();
#endif
}

/**
 * @tc.name: InitDragEvent006
 * @tc.desc: InitDragEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, InitDragEvent006, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern->delegate_, nullptr);
    WeakPtr<EventHub> eventHub = nullptr;
    RefPtr<GestureEventHub> gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    EXPECT_NE(gestureHub, nullptr);
    bool rerult = webPattern->NotifyStartDragTask();
    EXPECT_TRUE(rerult);
    webPattern->isDisableDrag_ = true;
    rerult = webPattern->NotifyStartDragTask();
    EXPECT_FALSE(rerult);
    webPattern->InitDragEvent(gestureHub);
    webPattern->InitDragEvent(gestureHub);
    EXPECT_NE(webPattern->dragEvent_, nullptr);
    rerult = webPattern->OnCursorChange(OHOS::NWeb::CursorType::CT_CROSS, nullptr);
    EXPECT_FALSE(rerult);
    std::shared_ptr<OHOS::NWeb::NWebSelectPopupMenuParamMock> params =
        std::make_shared<OHOS::NWeb::NWebSelectPopupMenuParamMock>();
    EXPECT_NE(params, nullptr);
    std::shared_ptr<OHOS::NWeb::NWebSelectPopupMenuCallbackMock> callback =
        std::make_shared<OHOS::NWeb::NWebSelectPopupMenuCallbackMock>();
    EXPECT_NE(callback, nullptr);
    webPattern->OnSelectPopupMenu(params, callback);
#endif
}

/**
 * @tc.name: ShowDateTimeDialog007
 * @tc.desc: ShowDateTimeDialog.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, ShowDateTimeDialog007, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);
    DialogTheme::Builder builder;
    RefPtr<DialogTheme> theme = builder.Build(nullptr);
    EXPECT_NE(theme, nullptr);
    // SystemProperties::InitDeviceType(DeviceType::PHONE);
    webPattern->GetDialogProperties(theme);
    // SystemProperties::InitDeviceType(DeviceType::TV);
    webPattern->GetDialogProperties(theme);
#endif
}

/**
 * @tc.name: GetSelectPopupPostion008
 * @tc.desc: GetSelectPopupPostion.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, GetSelectPopupPostion008, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);
    std::shared_ptr<OHOS::NWeb::NWebSelectPopupMenuCallbackMock> callback =
        std::make_shared<OHOS::NWeb::NWebSelectPopupMenuCallbackMock>();
    EXPECT_NE(callback, nullptr);
    std::shared_ptr<OHOS::NWeb::NWebSelectPopupMenuParamMock> params =
        std::make_shared<OHOS::NWeb::NWebSelectPopupMenuParamMock>();
    EXPECT_NE(params, nullptr);
#endif
}

/**
 * @tc.name: WebPatternTestNg_004.
 * @tc.desc: Test WebPattern  OnCursorChange when CursorType = context-menu.
 * @tc.type: FUNC.
 * @tc.require:I5OZZ8
 */
HWTEST_F(WebPatternTestNg, WebPatternTestNg_004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    EXPECT_NE(webPattern, nullptr);
    NWeb::NWebCursorInfoMock info;
    bool rerult = webPattern->OnCursorChange(OHOS::NWeb::CursorType::CT_CONTEXTMENU, nullptr);
    EXPECT_FALSE(rerult);
#endif
}

/**
 * @tc.name: JavaScriptOnDocumentStart009
 * @tc.desc: JavaScriptOnDocumentStart.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, JavaScriptOnDocumentStart009, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern, nullptr);
    std::map<std::string, std::vector<std::string>> scriptItems;
    std::string group = "groupp";
    std::vector<std::string> vec;
    vec.push_back("main");
    scriptItems.insert(std::make_pair(group, vec));
    webPattern->JavaScriptOnDocumentStart(scriptItems);
    EXPECT_NE(webPattern->delegate_, nullptr);
#endif
}

/**
 * @tc.name: UpdateJavaScriptOnDocumentStart010
 * @tc.desc: UpdateJavaScriptOnDocumentStart.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, UpdateJavaScriptOnDocumentStart010, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern, nullptr);
    std::map<std::string, std::vector<std::string>> scriptItems;
    std::string group = "groupp";
    std::vector<std::string> vec;
    vec.push_back("main");
    scriptItems.insert(std::make_pair(group, vec));
    webPattern->JavaScriptOnDocumentStart(scriptItems);
    webPattern->UpdateJavaScriptOnDocumentStart();
    EXPECT_FALSE(webPattern->onDocumentStartScriptItems_);
#endif
}

/**
 * @tc.name: OnModifyDone011
 * @tc.desc: OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnModifyDone011, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    AceApplicationInfo::GetInstance().SetAccessibilityEnabled(true);
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
#endif
}

/**
 * @tc.name: GetFocusedAccessibilityNode012
 * @tc.desc: GetFocusedAccessibilityNode.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, GetFocusedAccessibilityNode012, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    int32_t accessibilityId = 1;
    bool isAccessibilityFocus = true;
    auto ret = webPattern->GetFocusedAccessibilityNode(accessibilityId, isAccessibilityFocus);
    EXPECT_EQ(ret, nullptr);
#endif
}

/**
 * @tc.name: GetAccessibilityNodeById013
 * @tc.desc: GetAccessibilityNodeById.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, GetAccessibilityNodeById013, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    int32_t accessibilityId = 1;
    auto ret = webPattern->GetAccessibilityNodeById(accessibilityId);
    EXPECT_EQ(ret, nullptr);
#endif
}

/**
 * @tc.name: GetAccessibilityNodeByFocusMove014
 * @tc.desc: GetAccessibilityNodeByFocusMove.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, GetAccessibilityNodeByFocusMove014, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    int32_t accessibilityId = 1;
    int32_t direction = 1;
    auto ret = webPattern->GetAccessibilityNodeByFocusMove(accessibilityId, direction);
    EXPECT_EQ(ret, nullptr);
#endif
}

/**
 * @tc.name: ExecuteAction015
 * @tc.desc: ExecuteAction.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, ExecuteAction015, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
#endif
}

/**
 * @tc.name: SetAccessibilityState014
 * @tc.desc: SetAccessibilityState.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, SetAccessibilityState014, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->SetAccessibilityState(true);
#endif
}

/**
 * @tc.name: JavaScriptOnDocumentEnd015
 * @tc.desc: JavaScriptOnDocumentEnd.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, JavaScriptOnDocumentEnd009, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern, nullptr);
    std::map<std::string, std::vector<std::string>> scriptItems;
    std::string group = "group";
    std::vector<std::string> vec;
    vec.push_back("main");
    scriptItems.insert(std::make_pair(group, vec));
    webPattern->JavaScriptOnDocumentEnd(scriptItems);
    EXPECT_NE(webPattern->delegate_, nullptr);
#endif
}

/**
 * @tc.name: UpdateJavaScriptOnDocumentEnd016
 * @tc.desc: UpdateJavaScriptOnDocumentEnd.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, UpdateJavaScriptOnDocumentEnd010, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    webPattern->OnModifyDone();
    EXPECT_NE(webPattern, nullptr);
    std::map<std::string, std::vector<std::string>> scriptItems;
    std::string group = "group";
    std::vector<std::string> vec;
    vec.push_back("main");
    scriptItems.insert(std::make_pair(group, vec));
    webPattern->JavaScriptOnDocumentEnd(scriptItems);
    webPattern->UpdateJavaScriptOnDocumentEnd();
    EXPECT_FALSE(webPattern->onDocumentEndScriptItems_);
#endif
}

/**
 * @tc.name: ShowContextSelectOverlay_001
 * @tc.desc: ShowContextSelectOverlay.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, ShowContextSelectOverlay_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    auto textBase = WeakPtr<TextBase>();
    auto contextSelectOverlay = AceType::MakeRefPtr<WebContextSelectOverlay>(textBase);
    webPattern->contextSelectOverlay_ = contextSelectOverlay;
    auto responseType = TextResponseType::RIGHT_CLICK;

    webPattern->ShowContextSelectOverlay(RectF(), RectF(), responseType, true);
    EXPECT_NE(webPattern->contextSelectOverlay_, nullptr);
#endif
}

/**
 * @tc.name: ShowContextSelectOverlay_002
 * @tc.desc: ShowContextSelectOverlay.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, ShowContextSelectOverlay_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    auto responseType = TextResponseType::RIGHT_CLICK;

    webPattern->ShowContextSelectOverlay(RectF(), RectF(), responseType, true);

    EXPECT_EQ(webPattern->contextSelectOverlay_, nullptr);
#endif
}

/**
 * @tc.name: CloseContextSelectionMenu_001
 * @tc.desc: CloseContextSelectionMenu.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, CloseContextSelectionMenu_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    auto textBase = WeakPtr<TextBase>();
    auto contextSelectOverlay = AceType::MakeRefPtr<MockWebContextSelectOverlay>(textBase);
    webPattern->contextSelectOverlay_ = contextSelectOverlay;

    webPattern->CloseContextSelectionMenu();
    EXPECT_NE(webPattern->contextSelectOverlay_, nullptr);
#endif
}

/**
 * @tc.name: CloseContextSelectionMenu_002
 * @tc.desc: CloseContextSelectionMenu.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, CloseContextSelectionMenu_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    auto textBase = WeakPtr<TextBase>();
    auto contextSelectOverlay = AceType::MakeRefPtr<MockWebContextSelectOverlayfalse>(textBase);
    webPattern->contextSelectOverlay_ = contextSelectOverlay;

    webPattern->CloseContextSelectionMenu();
    EXPECT_NE(webPattern->contextSelectOverlay_, nullptr);
#endif
}

/**
 * @tc.name: CloseContextSelectionMenu_003
 * @tc.desc: CloseContextSelectionMenu.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, CloseContextSelectionMenu_003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->contextSelectOverlay_ = nullptr;

    webPattern->CloseContextSelectionMenu();
    EXPECT_EQ(webPattern->contextSelectOverlay_, nullptr);
#endif
}

/**
 * @tc.name: OnContextMenuShow_001
 * @tc.desc: OnContextMenuShow.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnContextMenuShow_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    std::shared_ptr<BaseEventInfo> emptyInfo =nullptr;
    webPattern->contextSelectOverlay_ = nullptr;

    webPattern->OnContextMenuShow(emptyInfo);
    EXPECT_EQ(webPattern->contextSelectOverlay_, nullptr);
#endif
}

/**
 * @tc.name: OnContextMenuShow_002
 * @tc.desc: OnContextMenuShow.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnContextMenuShow_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    auto textBase = WeakPtr<TextBase>();
    auto contextSelectOverlay = AceType::MakeRefPtr<MockWebContextSelectOverlay>(textBase);
    webPattern->contextSelectOverlay_ = contextSelectOverlay;
    webPattern->contextMenuParam_ = nullptr;
    RefPtr<WebContextMenuParam> param_ = nullptr;
    RefPtr<ContextMenuResult> result_;
    auto emptyInfo = std::make_shared<ContextMenuEvent>(param_, result_);

    webPattern->OnContextMenuShow(emptyInfo);
    EXPECT_NE(webPattern->contextSelectOverlay_, nullptr);
    EXPECT_EQ(webPattern->contextMenuParam_, nullptr);
    EXPECT_EQ(webPattern->contextMenuResult_, nullptr);
#endif
}

/**
 * @tc.name: OnContextMenuShow_003
 * @tc.desc: OnContextMenuShow.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnContextMenuShow_003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    auto textBase = WeakPtr<TextBase>();
    auto contextSelectOverlay = AceType::MakeRefPtr<MockWebContextSelectOverlay>(textBase);
    webPattern->contextSelectOverlay_ = contextSelectOverlay;
    webPattern->contextMenuParam_ = nullptr;
    auto param_ = AceType::MakeRefPtr<MockWebContextMenuParam>();
    RefPtr<ContextMenuResult> result_ = nullptr;
    auto emptyInfo = std::make_shared<ContextMenuEvent>(param_, result_);

    webPattern->OnContextMenuShow(emptyInfo);
    EXPECT_NE(webPattern->contextSelectOverlay_, nullptr);
    EXPECT_NE(webPattern->contextMenuParam_, nullptr);
    EXPECT_EQ(webPattern->contextMenuResult_, nullptr);
#endif
}

/**
 * @tc.name: OnContextMenuShow_004
 * @tc.desc: OnContextMenuShow.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnContextMenuShow_004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    auto textBase = WeakPtr<TextBase>();
    auto contextSelectOverlay = AceType::MakeRefPtr<MockWebContextSelectOverlay>(textBase);
    webPattern->contextSelectOverlay_ = contextSelectOverlay;
    webPattern->contextMenuParam_ = nullptr;
    auto param_ = AceType::MakeRefPtr<MockWebContextMenuParam>();
    auto result_ = AceType::MakeRefPtr<MockContextMenuResult>();
    auto emptyInfo = std::make_shared<ContextMenuEvent>(param_, result_);

    webPattern->OnContextMenuShow(emptyInfo);
    EXPECT_NE(webPattern->contextSelectOverlay_, nullptr);
    EXPECT_NE(webPattern->contextMenuParam_, nullptr);
    EXPECT_NE(webPattern->contextMenuResult_, nullptr);
#endif
}

/**
 * @tc.name: OnContextMenuHide_001
 * @tc.desc: OnContextMenuHide.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnContextMenuHide_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);

    webPattern->OnContextMenuHide();
    EXPECT_NE(webPattern, nullptr);
#endif
}

/**
 * @tc.name: NeedSoftKeyboard_001
 * @tc.desc: NeedSoftKeyboard.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, NeedSoftKeyboard_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);

    auto ret = webPattern->NeedSoftKeyboard();
    EXPECT_EQ(ret, false);
#endif
}

/**
 * @tc.name: NeedSoftKeyboard_002
 * @tc.desc: NeedSoftKeyboard.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, NeedSoftKeyboard_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->delegate_ = nullptr;

    auto ret = webPattern->NeedSoftKeyboard();
    EXPECT_EQ(ret, false);
#endif
}

/**
 * @tc.name: OnAttachToMainTree_001
 * @tc.desc: OnAttachToMainTree.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnAttachToMainTree_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);

    webPattern->OnAttachToMainTree();
    ASSERT_NE(webPattern->delegate_, nullptr);
#endif
}

/**
 * @tc.name: OnDetachFromMainTree_001
 * @tc.desc: OnDetachFromMainTree.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnDetachFromMainTree_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);

    webPattern->OnDetachFromMainTree();
    ASSERT_NE(webPattern->delegate_, nullptr);
#endif
}

/**
 * @tc.name: OnAttachToFrameNode_001
 * @tc.desc: OnAttachToFrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnAttachToFrameNode_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    auto renderContextForSurface_ = RenderContext::Create();
    auto renderContextForPopupSurface_ = RenderContext::Create();
    webPattern->renderContextForSurface_ = renderContextForSurface_;
    webPattern->renderContextForPopupSurface_ = renderContextForPopupSurface_;

    webPattern->OnAttachToFrameNode();
    EXPECT_NE(webPattern->renderContextForSurface_, nullptr);
    EXPECT_NE(webPattern->renderContextForPopupSurface_, nullptr);
#endif
}

/**
 * @tc.name: OnDetachFromFrameNode_001
 * @tc.desc: OnDetachFromFrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnDetachFromFrameNode_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->delegate_ = nullptr;

    auto pattern = AceType::MakeRefPtr<Pattern>();
    FrameNode node("exampleTag", 1, pattern, true, false);
    webPattern->OnDetachFromFrameNode(&node);
    EXPECT_EQ(webPattern->delegate_, nullptr);
#endif
}

/**
 * @tc.name: OnDetachFromFrameNode_002
 * @tc.desc: OnDetachFromFrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnDetachFromFrameNode_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);

    auto pattern = AceType::MakeRefPtr<Pattern>();
    FrameNode node("exampleTag", 1, pattern, true, false);
    webPattern->OnDetachFromFrameNode(&node);
    EXPECT_NE(webPattern->delegate_, nullptr);
#endif
}


/**
 * @tc.name: SetRotation_001
 * @tc.desc: SetRotation.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, SetRotation_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->renderMode_ = RenderMode::SYNC_RENDER;
    uint32_t rotation = 1;
    webPattern->rotation_ = rotation;
    webPattern->SetRotation(rotation);
    EXPECT_NE(webPattern->renderSurface_, nullptr);
#endif
}

/**
 * @tc.name: SetRotation_002
 * @tc.desc: SetRotation.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, SetRotation_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->renderMode_ = RenderMode::SYNC_RENDER;
    uint32_t rotation = 1;
    webPattern->rotation_ = 0;
    webPattern->SetRotation(rotation);
    EXPECT_NE(webPattern->renderSurface_, nullptr);
#endif
}

/**
 * @tc.name: SetRotation_003
 * @tc.desc: SetRotation.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, SetRotation_003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->renderMode_ = RenderMode::ASYNC_RENDER;
    uint32_t rotation = 1;
    webPattern->rotation_ = rotation;
    webPattern->SetRotation(rotation);
    EXPECT_NE(webPattern->renderSurface_, nullptr);
#endif
}

/**
 * @tc.name: SetRotation_004
 * @tc.desc: SetRotation.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, SetRotation_004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->renderMode_ = RenderMode::ASYNC_RENDER;
    uint32_t rotation = 1;
    webPattern->rotation_ = 0;
    webPattern->SetRotation(rotation);
    EXPECT_NE(webPattern->renderSurface_, nullptr);
#endif
}

/**
 * @tc.name: SetRotation_005
 * @tc.desc: SetRotation.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, SetRotation_005, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->renderMode_ = RenderMode::ASYNC_RENDER;
    uint32_t rotation = 1;
    webPattern->rotation_ = 0;
    webPattern->renderSurface_ = nullptr;

    webPattern->SetRotation(rotation);
    EXPECT_EQ(webPattern->renderSurface_, nullptr);
#endif
}

/**
 * @tc.name: InitEvent_001
 * @tc.desc: InitEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, InitEvent_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);

    webPattern->InitEvent();
    EXPECT_NE(webPattern, nullptr);
#endif
}

/**
 * @tc.name: InitFeatureParam_001
 * @tc.desc: InitFeatureParam.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, InitFeatureParam_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);

    webPattern->InitFeatureParam();
    EXPECT_NE(webPattern, nullptr);
#endif
}

/**
 * @tc.name: HandleFlingMove_001
 * @tc.desc: HandleFlingMove.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, HandleFlingMove_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    GestureEvent event;
    event.SetInputEventType(InputEventType::TOUCH_SCREEN);
    event.SetSourceTool(SourceTool::FINGER);

    webPattern->HandleFlingMove(event);
    EXPECT_NE(webPattern, nullptr);
#endif
}

/**
 * @tc.name: HandleFlingMove_002
 * @tc.desc: HandleFlingMove.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, HandleFlingMove_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    GestureEvent event;
    event.SetInputEventType(InputEventType::AXIS);
    event.SetSourceTool(SourceTool::FINGER);

    webPattern->HandleFlingMove(event);
    EXPECT_NE(webPattern, nullptr);
#endif
}

/**
 * @tc.name: HandleFlingMove_003
 * @tc.desc: HandleFlingMove.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, HandleFlingMove_003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    GestureEvent event;
    event.SetInputEventType(InputEventType::TOUCH_SCREEN);
    event.SetSourceTool(SourceTool::TOUCHPAD);

    webPattern->HandleFlingMove(event);
    EXPECT_NE(webPattern, nullptr);
#endif
}

/**
 * @tc.name: HandleFlingMove_004
 * @tc.desc: HandleFlingMove.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, HandleFlingMove_004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->delegate_ = nullptr;
    GestureEvent event;
    event.SetInputEventType(InputEventType::AXIS);
    event.SetSourceTool(SourceTool::TOUCHPAD);

    webPattern->HandleFlingMove(event);
    EXPECT_NE(webPattern, nullptr);
#endif
}

/**
 * @tc.name: HandleFlingMove_005
 * @tc.desc: HandleFlingMove.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, HandleFlingMove_005, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    GestureEvent event;
    event.SetInputEventType(InputEventType::AXIS);
    event.SetSourceTool(SourceTool::TOUCHPAD);
    std::vector<KeyCode> keyCodes;
    keyCodes.push_back(KeyCode::KEY_FN);
    event.SetPressedKeyCodes(keyCodes);

    webPattern->HandleFlingMove(event);
    EXPECT_NE(webPattern, nullptr);
#endif
}

/**
 * @tc.name: InitPinchEvent_001
 * @tc.desc: InitPinchEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, InitPinchEvent_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    WeakPtr<EventHub> eventHub = nullptr;
    RefPtr<GestureEventHub> gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    RefPtr<PinchGesture> pinchGesture_ = AceType::MakeRefPtr<PinchGesture>(1, 1.1);
    webPattern->pinchGesture_ = pinchGesture_;
    EXPECT_NE(webPattern->pinchGesture_, nullptr);

    webPattern->InitPinchEvent(gestureHub);
    EXPECT_NE(webPattern, nullptr);
#endif
}

/**
 * @tc.name: InitPinchEvent_002
 * @tc.desc: InitPinchEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, InitPinchEvent_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    WeakPtr<EventHub> eventHub = nullptr;
    RefPtr<GestureEventHub> gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    webPattern->pinchGesture_ =nullptr;
    EXPECT_EQ(webPattern->pinchGesture_, nullptr);

    webPattern->InitPinchEvent(gestureHub);
    EXPECT_NE(webPattern->pinchGesture_, nullptr);
#endif
}

/**
 * @tc.name: CheckZoomStatus_001
 * @tc.desc: CheckZoomStatus.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, CheckZoomStatus_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->zoomStatus_ = 3;
    double scale = 1.0;

    auto ret = webPattern->CheckZoomStatus(scale);
    EXPECT_EQ(ret, true);
    webPattern->zoomStatus_ = 0;
#endif
}

/**
 * @tc.name: CheckZoomStatus_002
 * @tc.desc: CheckZoomStatus.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, CheckZoomStatus_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->zoomStatus_ = 2;
    double scale = -2.0;
    webPattern->zoomErrorCount_ = 0;

    auto ret = webPattern->CheckZoomStatus(scale);
    EXPECT_EQ(ret, false);
    webPattern->zoomStatus_ = 0;
#endif
}

/**
 * @tc.name: CheckZoomStatus_003
 * @tc.desc: CheckZoomStatus.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, CheckZoomStatus_003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->zoomStatus_ = 1;
    double scale = -2.0;
    webPattern->zoomErrorCount_ = 0;

    auto ret = webPattern->CheckZoomStatus(scale);
    EXPECT_EQ(ret, true);
    webPattern->zoomStatus_ = 0;
#endif
}

/**
 * @tc.name: CheckZoomStatus_004
 * @tc.desc: CheckZoomStatus.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, CheckZoomStatus_004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->zoomStatus_ = 2;
    double scale = 1.0;
    webPattern->zoomErrorCount_ = 0;

    auto ret = webPattern->CheckZoomStatus(scale);
    EXPECT_EQ(ret, true);
    webPattern->zoomStatus_ = 0;
#endif
}

/**
 * @tc.name: CheckZoomStatus_005
 * @tc.desc: CheckZoomStatus.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, CheckZoomStatus_005, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->zoomStatus_ = 1;
    double scale = 1.0;
    webPattern->zoomErrorCount_ = 0;

    auto ret = webPattern->CheckZoomStatus(scale);
    EXPECT_EQ(ret, false);
    webPattern->zoomStatus_ = 0;
#endif
}

/**
 * @tc.name: CheckZoomStatus_006
 * @tc.desc: CheckZoomStatus.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, CheckZoomStatus_006, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->zoomStatus_ = 2;
    double scale = -2.0;
    webPattern->zoomErrorCount_ = 5;

    auto ret = webPattern->CheckZoomStatus(scale);
    EXPECT_EQ(ret, true);
    webPattern->zoomStatus_ = 0;
#endif
}

/**
 * @tc.name: CheckZoomStatus_007
 * @tc.desc: CheckZoomStatus.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, CheckZoomStatus_007, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->zoomStatus_ = 1;
    double scale = -2.0;
    webPattern->zoomErrorCount_ = 5;

    auto ret = webPattern->CheckZoomStatus(scale);
    EXPECT_EQ(ret, true);
    webPattern->zoomStatus_ = 0;
#endif
}

/**
 * @tc.name: CheckZoomStatus_008
 * @tc.desc: CheckZoomStatus.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, CheckZoomStatus_008, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->zoomStatus_ = 2;
    double scale = 1.0;
    webPattern->zoomErrorCount_ = 5;

    auto ret = webPattern->CheckZoomStatus(scale);
    EXPECT_EQ(ret, true);
    webPattern->zoomStatus_ = 0;
#endif
}

/**
 * @tc.name: CheckZoomStatus_009
 * @tc.desc: CheckZoomStatus.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, CheckZoomStatus_009, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    EXPECT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    ASSERT_NE(webPattern->delegate_, nullptr);
    webPattern->zoomStatus_ = 1;
    double scale = 1.0;
    webPattern->zoomErrorCount_ = 5;

    auto ret = webPattern->CheckZoomStatus(scale);
    EXPECT_EQ(ret, true);
    webPattern->zoomStatus_ = 0;
    webPattern->zoomErrorCount_ = 0;
#endif
}
} // namespace OHOS::Ace::NG