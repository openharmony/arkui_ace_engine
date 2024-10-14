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
#include "core/components/web/resource/web_delegate.h"
#include "core/components_ng/pattern/web/web_pattern.h"
#undef private

#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "base/web/webview/ohos_nweb/include/nweb_handler.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "frameworks/base/utils/system_properties.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
void DialogTheme::Builder::ParseNewPattern(
    const RefPtr<ThemeConstants>& themeConstants, const RefPtr<DialogTheme>& theme) const {};
void DialogTheme::Builder::ParsePattern(
    const RefPtr<ThemeConstants>& themeConstants, const RefPtr<DialogTheme>& theme) const {};
} // namespace OHOS::Ace

namespace OHOS::NWeb {
class NWebDateTimeChooserCallbackMock : public NWebDateTimeChooserCallback {
public:
    void Continue(bool success, const DateTime& value) override {}
};

class NWebSelectPopupMenuCallbackMock : public NWebSelectPopupMenuCallback {
public:
    void Continue(const std::vector<int32_t>& indices) override {}

    void Cancel() override {}
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

} // namespace OHOS::NWeb

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

class MockNWebDragData : public NWeb::NWebDragData {
public:
    MOCK_METHOD(std::string, GetLinkURL, (), (override));
    MOCK_METHOD(std::string, GetFragmentText, (), (override));
    MOCK_METHOD(std::string, GetFragmentHtml, (), (override));
    MOCK_METHOD(bool, GetPixelMapSetting, (const void** data, size_t& len, int& width, int& height), (override));
    MOCK_METHOD(bool, SetFragmentHtml, (const std::string& html), (override));
    MOCK_METHOD(bool, SetPixelMapSetting, (const void* data, size_t len, int width, int height), (override));
    MOCK_METHOD(bool, SetLinkURL, (const std::string& url), (override));
    MOCK_METHOD(bool, SetFragmentText, (const std::string& Text), (override));
    MOCK_METHOD(std::string, GetLinkTitle, (), (override));
    MOCK_METHOD(bool, SetLinkTitle, (const std::string& title), (override));
    void GetDragStartPosition(int& x, int& y)
    {
        x = kDefaultDragStartX;
        y = kDefaultDragStartY;
    }
    MOCK_METHOD(bool, IsSingleImageContent, (), (override));
    MOCK_METHOD(bool, SetFileUri, (const std::string& uri), (override));
    MOCK_METHOD(std::string, GetImageFileName, (), (override));
    MOCK_METHOD(void, ClearImageFileNames, (), (override));
    int kDefaultDragStartX = 10;
    int kDefaultDragStartY = 20;
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
    std::shared_ptr<BaseEventInfo> emptyInfo = nullptr;
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
    EXPECT_NE(ret, false);
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
    webPattern->pinchGesture_ = nullptr;
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

/**
 * @tc.name: OnDetachContext_001
 * @tc.desc: HandleFocusEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnDetachContext_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    MockPipelineContext::SetUp();
    auto pipelineContext = MockPipelineContext::GetCurrent();
    webPattern->OnDetachContext(pipelineContext.GetRawPtr());
    MockPipelineContext::TearDown();
    EXPECT_EQ(webPattern->nodeAttach_, false);
    EXPECT_EQ(webPattern->scrollableParentInfo_.hasParent, true);
#endif
}

/**
 * @tc.name: OnDetachContext_002
 * @tc.desc: OnDetachContext.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnDetachContext_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    webPattern->delegate_ = nullptr;
    MockPipelineContext::SetUp();
    auto pipelineContext = MockPipelineContext::GetCurrent();
    webPattern->OnDetachContext(pipelineContext.GetRawPtr());
    MockPipelineContext::TearDown();
    EXPECT_EQ(webPattern->nodeAttach_, false);
    EXPECT_EQ(webPattern->scrollableParentInfo_.hasParent, true);
#endif
}

/**
 * @tc.name: OnDetachContext_003
 * @tc.desc: OnDetachContext.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnDetachContext_003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    webPattern->delegate_ = nullptr;
    webPattern->observer_ = nullptr;
    MockPipelineContext::SetUp();
    auto pipelineContext = MockPipelineContext::GetCurrent();
    webPattern->OnDetachContext(pipelineContext.GetRawPtr());
    MockPipelineContext::TearDown();
    EXPECT_EQ(webPattern->nodeAttach_, false);
    EXPECT_EQ(webPattern->scrollableParentInfo_.hasParent, true);
#endif
}

/**
 * @tc.name: OnDetachContext_004
 * @tc.desc: OnDetachContext.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnDetachContext_004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    webPattern->delegate_ = nullptr;
    webPattern->observer_ = nullptr;
    webPattern->selectOverlayProxy_ = nullptr;
    MockPipelineContext::SetUp();
    auto pipelineContext = MockPipelineContext::GetCurrent();
    webPattern->OnDetachContext(pipelineContext.GetRawPtr());
    MockPipelineContext::TearDown();
    EXPECT_EQ(webPattern->nodeAttach_, false);
    EXPECT_EQ(webPattern->scrollableParentInfo_.hasParent, true);
#endif
}

/**
 * @tc.name: OnDetachContext_005
 * @tc.desc: OnDetachContext.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnDetachContext_005, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    webPattern->OnModifyDone();
    webPattern->delegate_ = nullptr;
    webPattern->observer_ = nullptr;
    webPattern->selectOverlayProxy_ = nullptr;
    webPattern->tooltipId_ = -1;
    MockPipelineContext::SetUp();
    auto pipelineContext = MockPipelineContext::GetCurrent();
    webPattern->OnDetachContext(pipelineContext.GetRawPtr());
    MockPipelineContext::TearDown();
    EXPECT_EQ(webPattern->nodeAttach_, false);
    EXPECT_EQ(webPattern->scrollableParentInfo_.hasParent, true);
#endif
}

/**
 * @tc.name: SetUpdateInstanceIdCallback_001
 * @tc.desc: Test SetUpdateInstanceIdCallback function.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, SetUpdateInstanceIdCallback_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    ASSERT_NE(webPattern, nullptr);
    MockPipelineContext::SetUp();
    auto pipelineContext = MockPipelineContext::GetCurrent();
    int32_t instanceId = -1;
    auto callback = [&instanceId](int32_t id) { instanceId = id; };
    webPattern->SetUpdateInstanceIdCallback(std::move(callback));
    MockPipelineContext::TearDown();
    ASSERT_NE(webPattern->updateInstanceIdCallback_, nullptr);
    webPattern->updateInstanceIdCallback_(123);
    EXPECT_EQ(instanceId, 123);
#endif
}

/**
 * @tc.name: OnScrollBarColorUpdate_001
 * @tc.desc: Test OnScrollBarColorUpdate function.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnScrollBarColorUpdate_001, TestSize.Level1)
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
    webPattern->needOnFocus_ = true;
    webPattern->OnScrollBarColorUpdate("red");
#endif
}

/**
 * @tc.name: OnScrollBarColorUpdate_002
 * @tc.desc: Test OnScrollBarColorUpdate function.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnScrollBarColorUpdate_002, TestSize.Level1)
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
    webPattern->delegate_ = nullptr;
    ASSERT_EQ(webPattern->delegate_, nullptr);
    webPattern->needOnFocus_ = true;
    webPattern->OnScrollBarColorUpdate("red");
#endif
}

/**
 * @tc.name: OnDefaultTextEncodingFormatUpdate_001
 * @tc.desc: Test OnDefaultTextEncodingFormatUpdate function.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnDefaultTextEncodingFormatUpdate_001, TestSize.Level1)
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
    webPattern->UpdateDefaultTextEncodingFormat("UTF-8");
#endif
}

/**
 * @tc.name: OnNativeVideoPlayerConfigUpdate_001
 * @tc.desc: Test OnNativeVideoPlayerConfigUpdate function.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnNativeVideoPlayerConfigUpdate_001, TestSize.Level1)
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
    // const std::tuple<bool, bool>& config
    std::tuple<bool, bool> config = std::make_tuple(true, false);
    webPattern->OnNativeVideoPlayerConfigUpdate(config);
#endif
}

/**
 * @tc.name: RegistVirtualKeyBoardListener_001
 * @tc.desc: Test RegistVirtualKeyBoardListener function.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, RegistVirtualKeyBoardListener_001, TestSize.Level1)
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
    MockPipelineContext::SetUp();
    auto pipelineContext = MockPipelineContext::GetCurrent();
    webPattern->RegistVirtualKeyBoardListener(pipelineContext);
    MockPipelineContext::TearDown();
    ASSERT_EQ(webPattern->needUpdateWeb_, false);
#endif
}

/**
 * @tc.name: InitEnhanceSurfaceFlag_001
 * @tc.desc: Test InitEnhanceSurfaceFlag function.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, InitEnhanceSurfaceFlag_001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webpattern;
    webpattern.delegate_ = nullptr;
    EXPECT_EQ(webpattern.delegate_, nullptr);
    SystemProperties::SetExtSurfaceEnabled(true);
    webpattern.InitEnhanceSurfaceFlag();
    ASSERT_EQ(webpattern.isEnhanceSurface_, true);
#endif
}

/**
 * @tc.name: InitEnhanceSurfaceFlag_002
 * @tc.desc: Test InitEnhanceSurfaceFlag function.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, InitEnhanceSurfaceFlag_002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebPattern webpattern;
    webpattern.delegate_ = nullptr;
    EXPECT_EQ(webpattern.delegate_, nullptr);
    SystemProperties::SetExtSurfaceEnabled(false);
    webpattern.InitEnhanceSurfaceFlag();
    ASSERT_EQ(webpattern.isEnhanceSurface_, false);
#endif
}

/**
 * @tc.name: OnModifyDone_001
 * @tc.desc: Test OnModifyDone function.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnModifyDone_001, TestSize.Level1)
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
    webPattern->delegate_ = nullptr;
    webPattern->OnModifyDone();
#endif
}

/**
 * @tc.name: OnModifyDone_002
 * @tc.desc: Test OnModifyDone function.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnModifyDone_002, TestSize.Level1)
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
#endif
}

/**
 * @tc.name: InitInOfflineMode_001
 * @tc.desc: Test InitInOfflineMode function.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, InitInOfflineMode_001, TestSize.Level1)
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
    webPattern->InitInOfflineMode();
    ASSERT_EQ(webPattern->offlineWebInited_, true);
#endif
}

/**
 * @tc.name: IsNeedResizeVisibleViewport_001
 * @tc.desc: Test IsNeedResizeVisibleViewport function.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, IsNeedResizeVisibleViewport_001, TestSize.Level1)
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
    webPattern->IsNeedResizeVisibleViewport();
#endif
}

/**
 * @tc.name: IsNeedResizeVisibleViewport_002
 * @tc.desc: Test IsNeedResizeVisibleViewport function.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, IsNeedResizeVisibleViewport_002, TestSize.Level1)
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
    webPattern->visibleViewportSize_.SetHeight(-1.0);
    auto ret = webPattern->IsNeedResizeVisibleViewport();
    ASSERT_EQ(ret, false);
#endif
}

/**
 * @tc.name: IsNeedResizeVisibleViewport_003
 * @tc.desc: Test IsNeedResizeVisibleViewport function.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, IsNeedResizeVisibleViewport_003, TestSize.Level1)
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
    webPattern->visibleViewportSize_.SetWidth(-1.0);
    auto ret = webPattern->IsNeedResizeVisibleViewport();
    ASSERT_EQ(ret, false);
#endif
}

/**
 * @tc.name: IsNeedResizeVisibleViewport_004
 * @tc.desc: Test IsNeedResizeVisibleViewport function.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, IsNeedResizeVisibleViewport_004, TestSize.Level1)
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
    webPattern->isVirtualKeyBoardShow_ = WebPattern::VkState::VK_NONE;
    auto ret = webPattern->IsNeedResizeVisibleViewport();
    ASSERT_EQ(ret, false);
#endif
}

/**
 * @tc.name: IsNeedResizeVisibleViewport_005
 * @tc.desc: Test IsNeedResizeVisibleViewport function.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, IsNeedResizeVisibleViewport_005, TestSize.Level1)
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
    webPattern->isVirtualKeyBoardShow_ = WebPattern::VkState::VK_NONE;
    auto ret = webPattern->IsNeedResizeVisibleViewport();
    ASSERT_EQ(ret, false);
#endif
}

/**
 * @tc.name: ProcessVirtualKeyBoardHide_001
 * @tc.desc: Test ProcessVirtualKeyBoardHide function.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, ProcessVirtualKeyBoardHide_001, TestSize.Level1)
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
    webPattern->ProcessVirtualKeyBoardHide(1000, 2000, true);
#endif
}

/**
 * @tc.name: ProcessVirtualKeyBoardShow_001
 * @tc.desc: Test ProcessVirtualKeyBoardShow function.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, ProcessVirtualKeyBoardShow_001, TestSize.Level1)
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
    webPattern->ProcessVirtualKeyBoardShow(1000, 2000, 500.0, false);
#endif
}

/**
 * @tc.name: ProcessVirtualKeyBoard_001
 * @tc.desc: Test ProcessVirtualKeyBoard function.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, ProcessVirtualKeyBoard_001, TestSize.Level1)
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
    webPattern->ProcessVirtualKeyBoard(1000, 2000, 500.0);
#endif
}

/**
 * @tc.name: UpdateWebLayoutSize_001
 * @tc.desc: Test UpdateWebLayoutSize function.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, UpdateWebLayoutSize_001, TestSize.Level1)
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
    webPattern->UpdateWebLayoutSize(1000, 2000, true, true);
#endif
}

/**
 * @tc.name: RegisterSelectOverLayOnClose001
 * @tc.desc: RegisterSelectOverLayOnClose.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, RegisterSelectOverLayOnClose001, TestSize.Level1)
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
    SelectOverlayInfo selectInfo;
    webPattern->RegisterSelectOverLayOnClose(selectInfo);
#endif
}

class NWebQuickMenuParamsMock : public OHOS::NWeb::NWebQuickMenuParams {
public:
    MOCK_METHOD(int32_t, GetXCoord, (), (override));
    MOCK_METHOD(int32_t, GetYCoord, (), (override));
    MOCK_METHOD(int32_t, GetWidth, (), (override));
    MOCK_METHOD(int32_t, GetHeight, (), (override));
    MOCK_METHOD(int32_t, GetEditStateFlags, (), (override));
    MOCK_METHOD(int32_t, GetSelectX, (), (override));
    MOCK_METHOD(int32_t, GetSelectY, (), (override));
    MOCK_METHOD(int32_t, GetSelectWidth, (), (override));
    MOCK_METHOD(int32_t, GetSelectXHeight, (), (override));
    MOCK_METHOD(std::shared_ptr<OHOS::NWeb::NWebTouchHandleState>, GetTouchHandleState,
        (OHOS::NWeb::NWebTouchHandleState::TouchHandleType type), (override));
    MOCK_METHOD(bool, GetIsLongPressActived, (), (override));
};

class NWebQuickMenuParamsDummy : public OHOS::NWeb::NWebQuickMenuParams {
public:
    int32_t GetXCoord() override
    {
        return 0;
    };
    int32_t GetYCoord() override
    {
        return 0;
    };
    int32_t GetWidth() override
    {
        return 0;
    };
    int32_t GetHeight() override
    {
        return 0;
    };
    int32_t GetEditStateFlags() override
    {
        return 0;
    };
    int32_t GetSelectX() override
    {
        return selectX;
    };
    int32_t GetSelectY() override
    {
        return selectY;
    };
    int32_t GetSelectWidth() override
    {
        return width;
    };
    int32_t GetSelectXHeight() override
    {
        return height;
    };
    std::shared_ptr<OHOS::NWeb::NWebTouchHandleState> GetTouchHandleState(
        OHOS::NWeb::NWebTouchHandleState::TouchHandleType type) override
    {
        return nullptr;
    }
    bool GetIsLongPressActived() override
    {
        return isLongPresseActived;
    }

private:
    int32_t selectX = 100;
    int32_t selectY = 200;
    int32_t width = 150;
    int32_t height = 50;
    bool isLongPresseActived = false;
};

class NWebTouchHandleStateMock : public OHOS::NWeb::NWebTouchHandleState {
public:
    NWebTouchHandleStateMock() = default;
    MOCK_METHOD(int32_t, GetTouchHandleId, (), (override));
    MOCK_METHOD(int32_t, GetX, (), (override));
    MOCK_METHOD(int32_t, GetY, (), (override));
    MOCK_METHOD(int32_t, GetViewPortX, (), (override));
    MOCK_METHOD(int32_t, GetViewPortY, (), (override));
    MOCK_METHOD(TouchHandleType, GetTouchHandleType, (), (override));
    MOCK_METHOD(bool, IsEnable, (), (override));
    MOCK_METHOD(float, GetAlpha, (), (override));
    MOCK_METHOD(float, GetEdgeHeight, (), (override));
};

class NWebTouchHandleStateDummy : public OHOS::NWeb::NWebTouchHandleState {
public:
    NWebTouchHandleStateDummy() = default;
    int32_t GetTouchHandleId() override
    {
        return -1;
    };
    int32_t GetX() override
    {
        return 0;
    };
    int32_t GetY() override
    {
        return 0;
    };
    int32_t GetViewPortX() override
    {
        return 0;
    };
    int32_t GetViewPortY() override
    {
        return 0;
    };
    TouchHandleType GetTouchHandleType() override
    {
        return TouchHandleType::SELECTION_BEGIN_HANDLE;
    };
    bool IsEnable() override
    {
        return false;
    };
    float GetAlpha() override
    {
        return 0.0;
    };
    float GetEdgeHeight() override
    {
        return 0.0;
    };
};

class NWebTouchHandleStateEndDummy : public OHOS::NWeb::NWebTouchHandleState {
public:
    NWebTouchHandleStateEndDummy() = default;
    int32_t GetTouchHandleId() override
    {
        return -1;
    };
    int32_t GetX() override
    {
        return 0;
    };
    int32_t GetY() override
    {
        return 0;
    };
    int32_t GetViewPortX() override
    {
        return 0;
    };
    int32_t GetViewPortY() override
    {
        return 0;
    };
    TouchHandleType GetTouchHandleType() override
    {
        return TouchHandleType::SELECTION_END_HANDLE;
    };
    bool IsEnable() override
    {
        return false;
    };
    float GetAlpha() override
    {
        return 0.0;
    };
    float GetEdgeHeight() override
    {
        return edgeHeight;
    };

private:
    float edgeHeight = 10.0;
};

class NWebTouchHandleStateBeginDummy : public OHOS::NWeb::NWebTouchHandleState {
public:
    NWebTouchHandleStateBeginDummy() = default;
    int32_t GetTouchHandleId() override
    {
        return -1;
    };
    int32_t GetX() override
    {
        return 0;
    };
    int32_t GetY() override
    {
        return 0;
    };
    int32_t GetViewPortX() override
    {
        return 0;
    };
    int32_t GetViewPortY() override
    {
        return 0;
    };
    TouchHandleType GetTouchHandleType() override
    {
        return TouchHandleType::SELECTION_BEGIN_HANDLE;
    };
    bool IsEnable() override
    {
        return false;
    };
    float GetAlpha() override
    {
        return 0.0;
    };
    float GetEdgeHeight() override
    {
        return edgeHeight;
    };

private:
    float edgeHeight = 10.0;
};

/**
 * @tc.name: ComputeClippedSelectionBounds001
 * @tc.desc: ComputeClippedSelectionBounds.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, ComputeClippedSelectionBounds001, TestSize.Level1)
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
    auto params = std::make_shared<NWebQuickMenuParamsMock>();
    auto startHandle = std::make_shared<NWebTouchHandleStateMock>();
    auto endHandle = std::make_shared<NWebTouchHandleStateMock>();
    bool isNewAvoid = true;
    auto ret = webPattern->ComputeClippedSelectionBounds(params, startHandle, endHandle, isNewAvoid);
    EXPECT_TRUE(isNewAvoid);
    EXPECT_EQ(ret, RectF());
#endif
}

/**
 * @tc.name: QuickMenuIsNeedNewAvoid001
 * @tc.desc: QuickMenuIsNeedNewAvoid.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, QuickMenuIsNeedNewAvoid001, TestSize.Level1)
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
    SelectOverlayInfo selectInfo;
    selectInfo.firstHandle.isShow = false;
    selectInfo.secondHandle.isShow = false;
    auto params = std::make_shared<NWebQuickMenuParamsDummy>();
    auto startHandle = std::make_shared<NWebTouchHandleStateDummy>();
    auto endHandle = std::make_shared<NWebTouchHandleStateDummy>();
    webPattern->QuickMenuIsNeedNewAvoid(selectInfo, params, startHandle, endHandle);
    EXPECT_EQ(webPattern->isQuickMenuMouseTrigger_, true);
    EXPECT_TRUE(selectInfo.isNewAvoid);
    EXPECT_TRUE(webPattern->isQuickMenuMouseTrigger_);
    EXPECT_EQ(selectInfo.selectArea, RectF(100, 0, 150, 50));
#endif
}

/**
 * @tc.name: QuickMenuIsNeedNewAvoid002
 * @tc.desc: QuickMenuIsNeedNewAvoid.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, QuickMenuIsNeedNewAvoid002, TestSize.Level1)
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
    SelectOverlayInfo selectInfo;
    selectInfo.firstHandle.isShow = false;
    selectInfo.secondHandle.isShow = false;
    auto params = std::make_shared<NWebQuickMenuParamsMock>();
    auto startHandle = std::make_shared<NWebTouchHandleStateEndDummy>();
    auto endHandle = std::make_shared<NWebTouchHandleStateEndDummy>();
    webPattern->QuickMenuIsNeedNewAvoid(selectInfo, params, startHandle, endHandle);
    EXPECT_EQ(webPattern->isQuickMenuMouseTrigger_, false);
    EXPECT_TRUE(selectInfo.isNewAvoid);
    EXPECT_EQ(selectInfo.selectArea, RectF());
#endif
}

/**
 * @tc.name: OnQuickMenuDismissed001
 * @tc.desc: OnQuickMenuDismissed.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnQuickMenuDismissed001, TestSize.Level1)
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
    webPattern->OnQuickMenuDismissed();
    EXPECT_NE(webPattern, nullptr);
#endif
}

class ViewDataWrapMock : public ViewDataWrap {
public:
    MOCK_METHOD(const std::string&, GetBundleName, (), (const, override));
    MOCK_METHOD(const std::string&, GetModuleName, (), (const, override));
    MOCK_METHOD(const std::string&, GetAbilityName, (), (const, override));
    MOCK_METHOD(const std::string&, GetPageUrl, (), (const, override));
    MOCK_METHOD(const std::vector<RefPtr<PageNodeInfoWrap>>&, GetPageNodeInfoWraps, (), ());
    MOCK_METHOD(const NG::RectF&, GetPageRect, (), (const, override));
    MOCK_METHOD(bool, GetUserSelected, (), (const, override));
    MOCK_METHOD(bool, GetOtherAccount, (), (const, override));
    MOCK_METHOD(void, SetBundleName, (const std::string& bundleName), (override));
    MOCK_METHOD(void, SetModuleName, (const std::string& moduleName), (override));
    MOCK_METHOD(void, SetAbilityName, (const std::string& abilityName), (override));
    MOCK_METHOD(void, SetPageUrl, (const std::string& pageUrl), (override));
    MOCK_METHOD(void, AddPageNodeInfoWrap, (RefPtr<PageNodeInfoWrap> pageNodeInfoWrap), (override));
    MOCK_METHOD(void, SetPageRect, (const NG::RectF& rect), (override));
    MOCK_METHOD(void, SetUserSelected, (bool isUserSelected), (override));
    MOCK_METHOD(void, SetOtherAccount, (bool isOtherAccount), (override));
};

/**
 * @tc.name: DumpViewDataPageNode001
 * @tc.desc: DumpViewDataPageNode.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, DumpViewDataPageNode001, TestSize.Level1)
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
    auto viewDataWrap = RefPtr<ViewDataWrapMock>();
    viewDataWrap = nullptr;
    bool needsRecordData = true;
    webPattern->DumpViewDataPageNode(viewDataWrap, needsRecordData);
    EXPECT_EQ(viewDataWrap, nullptr);
#endif
}

/**
 * @tc.name: DumpViewDataPageNode002
 * @tc.desc: DumpViewDataPageNode.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, DumpViewDataPageNode002, TestSize.Level1)
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
    auto viewDataWrap = RefPtr<ViewDataWrapMock>();
    bool needsRecordData = true;
    webPattern->DumpViewDataPageNode(viewDataWrap, needsRecordData);
    EXPECT_NE(webPattern, nullptr);
#endif
}

class PageNodeInfoWrapMock : public PageNodeInfoWrap {
public:
    MOCK_METHOD(void, SetId, (int32_t id), (override));
    MOCK_METHOD(int32_t, GetId, (), (const, override));
    MOCK_METHOD(void, SetDepth, (int32_t depth), (override));
    MOCK_METHOD(int32_t, GetDepth, (), (const, override));
    MOCK_METHOD(void, SetAutoFillType, (AceAutoFillType autoFillType), (override));
    MOCK_METHOD(AceAutoFillType, GetAutoFillType, (), (const, override));
    MOCK_METHOD(void, SetTag, (const std::string& tag), (override));
    MOCK_METHOD(const std::string&, GetTag, (), (const, override));
    MOCK_METHOD(void, SetValue, (const std::string& value), (override));
    MOCK_METHOD(const std::string&, GetValue, (), (const, override));
    MOCK_METHOD(void, SetPlaceholder, (const std::string& placeholder), (override));
    MOCK_METHOD(const std::string&, GetPlaceholder, (), (const, override));
    MOCK_METHOD(void, SetMetadata, (const std::string& metadata), (override));
    MOCK_METHOD(const std::string&, GetMetadata, (), (const, override));
    MOCK_METHOD(void, SetPasswordRules, (const std::string& passwordRules), (override));
    MOCK_METHOD(const std::string&, GetPasswordRules, (), (const, override));
    MOCK_METHOD(void, SetEnableAutoFill, (bool enableAutoFill), (override));
    MOCK_METHOD(bool, GetEnableAutoFill, (), (const, override));
    MOCK_METHOD(void, SetIsFocus, (bool isFocus), (override));
    MOCK_METHOD(bool, GetIsFocus, (), (const, override));
    MOCK_METHOD(void, SetPageNodeRect, (const NG::RectF& rect), (override));
    MOCK_METHOD(const NG::RectF&, GetPageNodeRect, (), (const, override));
};

/**
 * @tc.name: NotifyFillRequestSuccess001
 * @tc.desc: NotifyFillRequestSuccess.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, NotifyFillRequestSuccess001, TestSize.Level1)
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
    EXPECT_NE(webPattern, nullptr);
    auto viewDataWrap = RefPtr<ViewDataWrapMock>();
    viewDataWrap = nullptr;
    RefPtr<PageNodeInfoWrapMock> nodeWrap = AceType::MakeRefPtr<PageNodeInfoWrapMock>();
    AceAutoFillType autoFillType = AceAutoFillType::ACE_DETAIL_INFO_WITHOUT_STREET;
    webPattern->NotifyFillRequestSuccess(viewDataWrap, nodeWrap, autoFillType);
    EXPECT_EQ(viewDataWrap, nullptr);
#endif
}

/**
 * @tc.name: NotifyFillRequestSuccess002
 * @tc.desc: NotifyFillRequestSuccess.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, NotifyFillRequestSuccess002, TestSize.Level1)
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
    EXPECT_NE(webPattern, nullptr);
    auto viewDataWrap = AceType::MakeRefPtr<ViewDataWrapMock>();
    RefPtr<PageNodeInfoWrapMock> nodeWrap = AceType::MakeRefPtr<PageNodeInfoWrapMock>();
    std::vector<RefPtr<PageNodeInfoWrap>> nodeInfoWraps { nodeWrap };
    std::string pageUrl = "http://example.com";
    EXPECT_CALL(*viewDataWrap, GetPageNodeInfoWraps()).WillOnce(ReturnRef(nodeInfoWraps));
    EXPECT_CALL(*nodeWrap, GetAutoFillType()).WillOnce(Return(AceAutoFillType::ACE_UNSPECIFIED));
    EXPECT_CALL(*nodeWrap, GetIsFocus()).WillOnce(Return(false));
    EXPECT_CALL(*viewDataWrap, GetPageUrl()).WillOnce(ReturnRef(pageUrl));
    EXPECT_CALL(*viewDataWrap, GetOtherAccount()).WillOnce(Return(true));
    AceAutoFillType autoFillType = AceAutoFillType::ACE_DETAIL_INFO_WITHOUT_STREET;
    webPattern->NotifyFillRequestSuccess(viewDataWrap, nodeWrap, autoFillType);
#endif
}

/**
 * @tc.name: NotifyFillRequestSuccess003
 * @tc.desc: NotifyFillRequestSuccess.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, NotifyFillRequestSuccess003, TestSize.Level1)
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
    EXPECT_NE(webPattern, nullptr);
    auto viewDataWrap = AceType::MakeRefPtr<ViewDataWrapMock>();
    auto nodeWrap = AceType::MakeRefPtr<PageNodeInfoWrapMock>();
    std::vector<RefPtr<PageNodeInfoWrap>> nodeInfoWraps { nodeWrap };
    std::string pageUrl = "http://example.com";
    std::string metadata = "metadata";
    std::string value = "value";
    EXPECT_CALL(*viewDataWrap, GetPageNodeInfoWraps()).WillOnce(ReturnRef(nodeInfoWraps));
    EXPECT_CALL(*nodeWrap, GetAutoFillType()).WillOnce(Return(AceAutoFillType::ACE_DETAIL_INFO_WITHOUT_STREET));
    EXPECT_CALL(*nodeWrap, GetIsFocus()).WillOnce(Return(true));
    EXPECT_CALL(*nodeWrap, GetMetadata()).WillOnce(ReturnRef(metadata));
    EXPECT_CALL(*nodeWrap, GetValue()).WillOnce(ReturnRef(value));
    EXPECT_CALL(*viewDataWrap, GetPageUrl()).WillOnce(ReturnRef(pageUrl));
    EXPECT_CALL(*viewDataWrap, GetOtherAccount()).WillOnce(Return(true));
    webPattern->NotifyFillRequestSuccess(viewDataWrap, nodeWrap, AceAutoFillType::ACE_UNSPECIFIED);
#endif
}

/**
 * @tc.name: NotifyFillRequestFailed001
 * @tc.desc: NotifyFillRequestFailed.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, NotifyFillRequestFailed001, TestSize.Level1)
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
    EXPECT_NE(webPattern, nullptr);
    int32_t errCode = 4000;
    const std::string fillContent = "fillContent";
    bool isPopup = false;
    webPattern->isPasswordFill_ = false;
    webPattern->NotifyFillRequestFailed(errCode, fillContent, isPopup);
    EXPECT_EQ(webPattern->isPasswordFill_, false);
#endif
}

/**
 * @tc.name: NotifyFillRequestFailed002
 * @tc.desc: NotifyFillRequestFailed.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, NotifyFillRequestFailed002, TestSize.Level1)
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
    EXPECT_NE(webPattern, nullptr);
    int32_t errCode = 4000;
    const std::string fillContent = "fillContent";
    bool isPopup = false;
    webPattern->isPasswordFill_ = true;
    webPattern->NotifyFillRequestFailed(errCode, fillContent, isPopup);
    EXPECT_EQ(webPattern->isPasswordFill_, true);
#endif
}

/**
 * @tc.name: ParseViewDataNumber001
 * @tc.desc: ParseViewDataNumber.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, ParseViewDataNumber001, TestSize.Level1)
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
    EXPECT_NE(webPattern, nullptr);
    const std::string key = "key";
    int32_t value = 0;
    RefPtr<PageNodeInfoWrapMock> node = AceType::MakeRefPtr<PageNodeInfoWrapMock>();
    RectT<float> rect;
    float viewScale = 0;
    webPattern->ParseViewDataNumber(key, value, node, rect, viewScale);
    EXPECT_EQ(viewScale, 0);
#endif
}

/**
 * @tc.name: ParseViewDataNumber002
 * @tc.desc: ParseViewDataNumber.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, ParseViewDataNumber002, TestSize.Level1)
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
    EXPECT_NE(webPattern, nullptr);
    const std::string key = "key";
    int32_t value = 0;
    RefPtr<PageNodeInfoWrapMock> node = AceType::MakeRefPtr<PageNodeInfoWrapMock>();
    node = nullptr;
    RectT<float> rect;
    float viewScale = 1;
    webPattern->ParseViewDataNumber(key, value, node, rect, viewScale);
    EXPECT_EQ(viewScale, 1);
    EXPECT_EQ(node, nullptr);
#endif
}

/**
 * @tc.name: ParseViewDataNumber003
 * @tc.desc: ParseViewDataNumber.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, ParseViewDataNumber003, TestSize.Level1)
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
    EXPECT_NE(webPattern, nullptr);
    const std::string key = OHOS::NWeb::NWEB_VIEW_DATA_KEY_FOCUS;
    int32_t value = 0;
    RefPtr<NiceMock<PageNodeInfoWrapMock>> node = AceType::MakeRefPtr<NiceMock<PageNodeInfoWrapMock>>();
    RectT<float> rect;
    float viewScale = 1;
    webPattern->ParseViewDataNumber(key, value, node, rect, viewScale);
    EXPECT_EQ(viewScale, 1);
    EXPECT_NE(node, nullptr);
    EXPECT_EQ(key, OHOS::NWeb::NWEB_VIEW_DATA_KEY_FOCUS);
#endif
}

/**
 * @tc.name: ParseViewDataNumber004
 * @tc.desc: ParseViewDataNumber.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, ParseViewDataNumber004, TestSize.Level1)
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
    EXPECT_NE(webPattern, nullptr);
    const std::string key = OHOS::NWeb::NWEB_VIEW_DATA_KEY_RECT_X;
    int32_t value = 0;
    RefPtr<NiceMock<PageNodeInfoWrapMock>> node = AceType::MakeRefPtr<NiceMock<PageNodeInfoWrapMock>>();
    RectT<float> rect;
    float viewScale = 1;
    webPattern->ParseViewDataNumber(key, value, node, rect, viewScale);
    EXPECT_EQ(viewScale, 1);
    EXPECT_NE(node, nullptr);
    EXPECT_EQ(key, OHOS::NWeb::NWEB_VIEW_DATA_KEY_RECT_X);
#endif
}

/**
 * @tc.name: ParseViewDataNumber005
 * @tc.desc: ParseViewDataNumber.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, ParseViewDataNumber005, TestSize.Level1)
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
    EXPECT_NE(webPattern, nullptr);
    const std::string key = OHOS::NWeb::NWEB_VIEW_DATA_KEY_RECT_Y;
    int32_t value = 0;
    RefPtr<PageNodeInfoWrapMock> node = AceType::MakeRefPtr<PageNodeInfoWrapMock>();
    RectT<float> rect;
    float viewScale = 1;
    webPattern->ParseViewDataNumber(key, value, node, rect, viewScale);
    EXPECT_EQ(viewScale, 1);
    EXPECT_NE(node, nullptr);
    EXPECT_EQ(key, OHOS::NWeb::NWEB_VIEW_DATA_KEY_RECT_Y);
#endif
}

/**
 * @tc.name: ParseViewDataNumber006
 * @tc.desc: ParseViewDataNumber.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, ParseViewDataNumber006, TestSize.Level1)
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
    EXPECT_NE(webPattern, nullptr);
    const std::string key = OHOS::NWeb::NWEB_VIEW_DATA_KEY_RECT_W;
    int32_t value = 0;
    RefPtr<PageNodeInfoWrapMock> node = AceType::MakeRefPtr<PageNodeInfoWrapMock>();
    RectT<float> rect;
    float viewScale = 1;
    webPattern->ParseViewDataNumber(key, value, node, rect, viewScale);
    EXPECT_EQ(viewScale, 1);
    EXPECT_NE(node, nullptr);
    EXPECT_EQ(key, OHOS::NWeb::NWEB_VIEW_DATA_KEY_RECT_W);
#endif
}

/**
 * @tc.name: ParseViewDataNumber007
 * @tc.desc: ParseViewDataNumber.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, ParseViewDataNumber007, TestSize.Level1)
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
    EXPECT_NE(webPattern, nullptr);
    const std::string key = OHOS::NWeb::NWEB_VIEW_DATA_KEY_RECT_H;
    int32_t value = 0;
    RefPtr<PageNodeInfoWrapMock> node = AceType::MakeRefPtr<PageNodeInfoWrapMock>();
    RectT<float> rect;
    float viewScale = 1;
    webPattern->ParseViewDataNumber(key, value, node, rect, viewScale);
    EXPECT_EQ(viewScale, 1);
    EXPECT_NE(node, nullptr);
    EXPECT_EQ(key, OHOS::NWeb::NWEB_VIEW_DATA_KEY_RECT_H);
#endif
}

/**
 * @tc.name: ParseNWebViewDataNode001
 * @tc.desc: ParseNWebViewDataNode.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, ParseNWebViewDataNode001, TestSize.Level1)
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
    EXPECT_NE(webPattern, nullptr);
    auto child = std::make_unique<JsonValue>();
    std::vector<RefPtr<PageNodeInfoWrap>> nodeInfos;
    int32_t nId = 1;
    webPattern->ParseNWebViewDataNode(std::move(child), nodeInfos, nId);
#endif
}

/**
 * @tc.name: GetFocusedType001
 * @tc.desc: GetFocusedType.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, GetFocusedType001, TestSize.Level1)
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
    EXPECT_NE(webPattern, nullptr);
    webPattern->pageNodeInfo_.clear();
    webPattern->GetFocusedType();
    EXPECT_EQ(webPattern->GetFocusedType(), AceAutoFillType::ACE_UNSPECIFIED);
#endif
}

/**
 * @tc.name: GetFocusedType002
 * @tc.desc: GetFocusedType.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, GetFocusedType002, TestSize.Level1)
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
    EXPECT_NE(webPattern, nullptr);
    RefPtr<PageNodeInfoWrapMock> pageNodeInfo = AceType::MakeRefPtr<PageNodeInfoWrapMock>();
    webPattern->pageNodeInfo_.push_back(pageNodeInfo);
    EXPECT_CALL(*pageNodeInfo, GetIsFocus()).WillRepeatedly(::testing::Return(false));
    webPattern->GetFocusedType();
    EXPECT_EQ(webPattern->GetFocusedType(), AceAutoFillType::ACE_UNSPECIFIED);
#endif
}

/**
 * @tc.name: GetFocusedType003
 * @tc.desc: GetFocusedType.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, GetFocusedType003, TestSize.Level1)
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
    EXPECT_NE(webPattern, nullptr);
    RefPtr<PageNodeInfoWrapMock> pageNodeInfo = AceType::MakeRefPtr<PageNodeInfoWrapMock>();
    webPattern->pageNodeInfo_.push_back(pageNodeInfo);
    EXPECT_CALL(*pageNodeInfo, GetIsFocus()).WillRepeatedly(::testing::Return(true));
    EXPECT_CALL(*pageNodeInfo, GetAutoFillType()).WillRepeatedly(::testing::Return(AceAutoFillType::ACE_UNSPECIFIED));
    AceAutoFillType result = webPattern->GetFocusedType();
    EXPECT_EQ(result, AceAutoFillType::ACE_UNSPECIFIED);
#endif
}

/**
 * @tc.name: GetFocusedType004
 * @tc.desc: GetFocusedType.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, GetFocusedType004, TestSize.Level1)
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
    EXPECT_NE(webPattern, nullptr);
    RefPtr<PageNodeInfoWrapMock> pageNodeInfo = AceType::MakeRefPtr<PageNodeInfoWrapMock>();
    RefPtr<PageNodeInfoWrapMock> pageNodeInfo_no = AceType::MakeRefPtr<PageNodeInfoWrapMock>();
    webPattern->pageNodeInfo_.push_back(pageNodeInfo);
    webPattern->pageNodeInfo_.push_back(pageNodeInfo_no);
    EXPECT_CALL(*pageNodeInfo, GetIsFocus()).WillRepeatedly(::testing::Return(true));
    EXPECT_CALL(*pageNodeInfo, GetAutoFillType()).WillRepeatedly(::testing::Return(AceAutoFillType::ACE_UNSPECIFIED));
    EXPECT_CALL(*pageNodeInfo_no, GetIsFocus()).WillRepeatedly(::testing::Return(false));
    EXPECT_CALL(*pageNodeInfo, GetIsFocus()).WillRepeatedly(::testing::Return(false));
    AceAutoFillType result = webPattern->GetFocusedType();
    EXPECT_EQ(result, AceAutoFillType::ACE_UNSPECIFIED);
#endif
}

/**
 * @tc.name: RequestAutoFill001
 * @tc.desc: RequestAutoFill.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, RequestAutoFill001, TestSize.Level1)
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
    EXPECT_NE(webPattern, nullptr);
    auto host = webPattern->GetHost();
    EXPECT_NE(host, nullptr);
    auto ret = webPattern->RequestAutoFill(AceAutoFillType::ACE_UNSPECIFIED);
    EXPECT_EQ(ret, false);
#endif
}

/**
 * @tc.name: RequestAutoSave001
 * @tc.desc: RequestAutoSave.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, RequestAutoSave001, TestSize.Level1)
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
    EXPECT_NE(webPattern, nullptr);
    auto host = webPattern->GetHost();
    EXPECT_NE(host, nullptr);
    auto ret = webPattern->RequestAutoSave();
    EXPECT_EQ(ret, false);
#endif
}

/**
 * @tc.name: UpdateAutoFillPopup001
 * @tc.desc: UpdateAutoFillPopup.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, UpdateAutoFillPopup001, TestSize.Level1)
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
    EXPECT_NE(webPattern, nullptr);
    webPattern->isAutoFillClosing_ = true;
    auto ret = webPattern->UpdateAutoFillPopup();
    EXPECT_EQ(ret, false);
#endif
}

/**
 * @tc.name: CloseAutoFillPopup001
 * @tc.desc: CloseAutoFillPopup.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, CloseAutoFillPopup001, TestSize.Level1)
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
    EXPECT_NE(webPattern, nullptr);
    auto ret = webPattern->CloseAutoFillPopup();
    EXPECT_EQ(ret, false);
#endif
}

/**
 * @tc.name: UpdateSelectHandleInfo001
 * @tc.desc: UpdateSelectHandleInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, UpdateSelectHandleInfo001, TestSize.Level1)
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
    EXPECT_NE(webPattern, nullptr);
    auto selectOverlayProxy = AceType::MakeRefPtr<SelectOverlayProxy>(1);
    webPattern->selectOverlayProxy_ = selectOverlayProxy;
    auto startSelectionHandle = std::make_shared<NiceMock<NWebTouchHandleStateMock>>();
    auto endSelectionHandle = std::make_shared<NiceMock<NWebTouchHandleStateMock>>();
    webPattern->startSelectionHandle_ = startSelectionHandle;
    webPattern->endSelectionHandle_ = endSelectionHandle;
    webPattern->UpdateSelectHandleInfo();
#endif
}

/**
 * @tc.name: IsSelectHandleReverse001
 * @tc.desc: IsSelectHandleReverse.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, IsSelectHandleReverse001, TestSize.Level1)
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
    EXPECT_NE(webPattern, nullptr);
    auto startSelectionHandle = std::make_shared<NWebTouchHandleStateDummy>();
    auto endSelectionHandle = std::make_shared<NWebTouchHandleStateDummy>();
    webPattern->startSelectionHandle_ = startSelectionHandle;
    webPattern->endSelectionHandle_ = endSelectionHandle;
    webPattern->IsSelectHandleReverse();
    EXPECT_EQ(webPattern->IsSelectHandleReverse(), true);
#endif
}

/**
 * @tc.name: IsSelectHandleReverse002
 * @tc.desc: IsSelectHandleReverse.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, IsSelectHandleReverse002, TestSize.Level1)
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
    EXPECT_NE(webPattern, nullptr);
    auto startSelectionHandle = std::make_shared<NWebTouchHandleStateEndDummy>();
    auto endSelectionHandle = std::make_shared<NWebTouchHandleStateEndDummy>();
    webPattern->startSelectionHandle_ = startSelectionHandle;
    webPattern->endSelectionHandle_ = endSelectionHandle;
    webPattern->IsSelectHandleReverse();
    EXPECT_EQ(webPattern->IsSelectHandleReverse(), true);
#endif
}

/**
 * @tc.name: IsSelectHandleReverse003
 * @tc.desc: IsSelectHandleReverse.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, IsSelectHandleReverse003, TestSize.Level1)
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
    EXPECT_NE(webPattern, nullptr);
    auto startSelectionHandle = std::make_shared<NWebTouchHandleStateBeginDummy>();
    auto endSelectionHandle = std::make_shared<NWebTouchHandleStateEndDummy>();
    webPattern->startSelectionHandle_ = startSelectionHandle;
    webPattern->endSelectionHandle_ = endSelectionHandle;
    webPattern->IsSelectHandleReverse();
    EXPECT_EQ(webPattern->IsSelectHandleReverse(), false);
#endif
}

/**
 * @tc.name: IsRootNeedExportTexture_001
 * @tc.desc: IsRootNeedExportTexture.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, IsRootNeedExportTexture_001, TestSize.Level1)
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
    auto ret = webPattern->IsRootNeedExportTexture();
    EXPECT_EQ(ret, false);

#endif
}

/**
 * @tc.name: OnOverScrollModeUpdate_001
 * @tc.desc: OnOverScrollModeUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnOverScrollModeUpdate_001, TestSize.Level1)
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
    webPattern->OnOverScrollModeUpdate(0);

#endif
}

/**
 * @tc.name: OnOverScrollModeUpdate_002
 * @tc.desc: OnOverScrollModeUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnOverScrollModeUpdate_002, TestSize.Level1)
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

    webPattern->delegate_ = nullptr;
    webPattern->OnOverScrollModeUpdate(0);

#endif
}

/**
 * @tc.name: OnCopyOptionModeUpdate_001
 * @tc.desc: OnCopyOptionModeUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnCopyOptionModeUpdate_001, TestSize.Level1)
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
    webPattern->OnCopyOptionModeUpdate(0);

#endif
}

/**
 * @tc.name: OnCopyOptionModeUpdate_002
 * @tc.desc: OnCopyOptionModeUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnCopyOptionModeUpdate_002, TestSize.Level1)
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

    webPattern->delegate_ = nullptr;
    webPattern->OnCopyOptionModeUpdate(0);

#endif
}

/**
 * @tc.name: OnMetaViewportUpdate_001
 * @tc.desc: OnMetaViewportUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnMetaViewportUpdate_001, TestSize.Level1)
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
    webPattern->OnMetaViewportUpdate(true);

#endif
}

/**
 * @tc.name: OnMetaViewportUpdate_002
 * @tc.desc: OnMetaViewportUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnMetaViewportUpdate_002, TestSize.Level1)
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

    webPattern->delegate_ = nullptr;
    webPattern->OnMetaViewportUpdate(true);

#endif
}

/**
 * @tc.name: OnOverlayScrollbarEnabledUpdate_001
 * @tc.desc: OnOverlayScrollbarEnabledUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnOverlayScrollbarEnabledUpdate_001, TestSize.Level1)
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
    webPattern->OnOverlayScrollbarEnabledUpdate(true);

#endif
}

/**
 * @tc.name: OnOverlayScrollbarEnabledUpdate_002
 * @tc.desc: OnOverlayScrollbarEnabledUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnOverlayScrollbarEnabledUpdate_002, TestSize.Level1)
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
    webPattern->delegate_ = nullptr;
    webPattern->OnOverlayScrollbarEnabledUpdate(true);

#endif
}

/**
 * @tc.name: OnNativeEmbedModeEnabledUpdate_001
 * @tc.desc: OnNativeEmbedModeEnabledUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnNativeEmbedModeEnabledUpdate_001, TestSize.Level1)
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
    webPattern->OnNativeEmbedModeEnabledUpdate(true);

#endif
}

/**
 * @tc.name: OnNativeEmbedModeEnabledUpdate_002
 * @tc.desc: OnNativeEmbedModeEnabledUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnNativeEmbedModeEnabledUpdate_002, TestSize.Level1)

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
    webPattern->delegate_ = nullptr;
    webPattern->OnNativeEmbedModeEnabledUpdate(true);

#endif
}

/**
 * @tc.name: OnNativeEmbedRuleTagUpdate_001
 * @tc.desc: OnNativeEmbedRuleTagUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnNativeEmbedRuleTagUpdate_001, TestSize.Level1)
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
    webPattern->OnNativeEmbedRuleTagUpdate("test");

#endif
}

/**
 * @tc.name: OnNativeEmbedRuleTagUpdate_002
 * @tc.desc: OnNativeEmbedRuleTagUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnNativeEmbedRuleTagUpdate_002, TestSize.Level1)
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
    webPattern->delegate_ = nullptr;
    webPattern->OnNativeEmbedRuleTagUpdate("test");

#endif
}

/**
 * @tc.name: OnNativeEmbedRuleTypeUpdate_001
 * @tc.desc: OnNativeEmbedRuleTypeUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnNativeEmbedRuleTypeUpdate_001, TestSize.Level1)
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
    webPattern->OnNativeEmbedRuleTypeUpdate("test");

#endif
}

/**
 * @tc.name: OnNativeEmbedRuleTypeUpdate_002
 * @tc.desc: OnNativeEmbedRuleTypeUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnNativeEmbedRuleTypeUpdate_002, TestSize.Level1)
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
    webPattern->delegate_ = nullptr;
    webPattern->OnNativeEmbedRuleTypeUpdate("test");

#endif
}

/**
 * @tc.name: OnTextAutosizingUpdate_001
 * @tc.desc: OnTextAutosizingUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnTextAutosizingUpdate_001, TestSize.Level1)
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
    webPattern->OnTextAutosizingUpdate(true);

#endif
}

/**
 * @tc.name: OnTextAutosizingUpdate_002
 * @tc.desc: OnTextAutosizingUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnTextAutosizingUpdate_002, TestSize.Level1)
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
    webPattern->delegate_ = nullptr;
    webPattern->OnTextAutosizingUpdate(true);

#endif
}

/**
 * @tc.name: OnKeyboardAvoidModeUpdate_001
 * @tc.desc: OnKeyboardAvoidModeUpdate.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnKeyboardAvoidModeUpdate_001, TestSize.Level1)
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
    webPattern->OnKeyboardAvoidModeUpdate(WebKeyboardAvoidMode::RESIZE_CONTENT);
    EXPECT_EQ(webPattern->keyBoardAvoidMode_, WebKeyboardAvoidMode::RESIZE_CONTENT);

#endif
}

/**
 * @tc.name: HandleScroll_001
 * @tc.desc: HandleScroll.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, HandleScroll_001, TestSize.Level1)
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
    webPattern->needOnFocus_ = true;
    ScrollResult result = webPattern->HandleScroll(1.f, SCROLL_FROM_UPDATE, NestedState::CHILD_SCROLL, 1.f);
    EXPECT_EQ(result.remain, 0.f);
    EXPECT_FALSE(result.reachEdge);

#endif
}

/**
 * @tc.name: HandleScroll_002
 * @tc.desc: HandleScroll.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, HandleScroll_002, TestSize.Level1)
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
    ScrollResult result = webPattern->HandleScroll(
        webPattern->GetNestedScrollParent(), 1.f, SCROLL_FROM_UPDATE, NestedState::CHILD_SCROLL);
    EXPECT_EQ(result.remain, 0.f);
    EXPECT_FALSE(result.reachEdge);

#endif
}

/**
 * @tc.name: HandleScrollVelocity_001
 * @tc.desc: HandleScrollVelocity.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, HandleScrollVelocity_001, TestSize.Level1)
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
    auto result = webPattern->HandleScrollVelocity(1.f, webPattern->GetNestedScrollParent());
    EXPECT_FALSE(result);

#endif
}

/**
 * @tc.name: HandleScrollVelocity_002
 * @tc.desc: HandleScrollVelocity.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, HandleScrollVelocity_002, TestSize.Level1)
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
    auto result = webPattern->HandleScrollVelocity(webPattern->GetNestedScrollParent(), 1.f);
    EXPECT_FALSE(result);

#endif
}

/**
 * @tc.name: OnScrollStartRecursive_001
 * @tc.desc: OnScrollStartRecursive.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnScrollStartRecursive_001, TestSize.Level1)
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
    webPattern->OnScrollStartRecursive(1.f, 1.f);
    EXPECT_TRUE(webPattern->isFirstFlingScrollVelocity_);
    EXPECT_TRUE(webPattern->isNeedUpdateScrollAxis_);
    EXPECT_TRUE(webPattern->isScrollStarted_);

#endif
}

/**
 * @tc.name: OnScrollStartRecursive_002
 * @tc.desc: OnScrollStartRecursive.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnScrollStartRecursive_002, TestSize.Level1)
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
    std::vector<float> positions = { 1.f };
    webPattern->OnScrollStartRecursive(positions);
    EXPECT_TRUE(webPattern->isFirstFlingScrollVelocity_);
    EXPECT_TRUE(webPattern->isNeedUpdateScrollAxis_);
    EXPECT_TRUE(webPattern->isScrollStarted_);

#endif
}

/**
 * @tc.name: OnScrollEndRecursive_001
 * @tc.desc: OnScrollEndRecursive.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnScrollEndRecursive_001, TestSize.Level1)
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
    webPattern->isScrollStarted_ = true;
    webPattern->isNestedInterrupt_ = true;
    std::optional<float> velocity = 1.f;
    webPattern->OnScrollEndRecursive(velocity);
    EXPECT_FALSE(webPattern->isScrollStarted_);
    EXPECT_FALSE(webPattern->isNestedInterrupt_);
#endif
}

/**
 * @tc.name: OnScrollEndRecursive_002
 * @tc.desc: OnScrollEndRecursive.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnScrollEndRecursive_002, TestSize.Level1)
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
    webPattern->isScrollStarted_ = false;
    webPattern->isNestedInterrupt_ = true;
    std::optional<float> velocity = 1.f;
    webPattern->OnScrollEndRecursive(velocity);
    EXPECT_FALSE(webPattern->isScrollStarted_);
    EXPECT_TRUE(webPattern->isNestedInterrupt_);

#endif
}

/**
 * @tc.name: SetLayoutMode_001
 * @tc.desc: SetLayoutMode.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, SetLayoutMode_001, TestSize.Level1)
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
    auto mode = static_cast<OHOS::Ace::WebLayoutMode>(WebLayoutMode::FIT_CONTENT);
    webPattern->SetLayoutMode(mode);
    webPattern->SetLayoutMode(mode);
    EXPECT_NE(webPattern->layoutMode_, mode);
#endif
}

/**
 * @tc.name: SetRenderMode_001
 * @tc.desc: SetRenderMode.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, SetRenderMode_001, TestSize.Level1)
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
    auto renderMode = RenderMode::ASYNC_RENDER;
    webPattern->SetRenderMode(renderMode);
    webPattern->SetRenderMode(renderMode);
    EXPECT_EQ(webPattern->renderMode_, renderMode);
#endif
}

/**
 * @tc.name: GetParentAxis_001
 * @tc.desc: GetParentAxis.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, GetParentAxis_001, TestSize.Level1)
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
    webPattern->axis_ = Axis::HORIZONTAL;
    webPattern->GetParentAxis();
    EXPECT_EQ(webPattern->axis_, Axis::HORIZONTAL);

#endif
}

/**
 * @tc.name: OnAttachContext_001
 * @tc.desc: OnAttachContext.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnAttachContext_001, TestSize.Level1)
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
    MockPipelineContext::SetUp();
    auto pipelineContext = MockPipelineContext::GetCurrent();
    webPattern->OnAttachContext(pipelineContext.GetRawPtr());
    MockPipelineContext::TearDown();
    EXPECT_EQ(webPattern->instanceId_, 0);

#endif
}

/**
 * @tc.name: OnAttachContext_002
 * @tc.desc: OnAttachContext.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnAttachContext_002, TestSize.Level1)
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
    webPattern->delegate_ = nullptr;
    webPattern->observer_ = nullptr;
    webPattern->updateInstanceIdCallback_ = nullptr;
    webPattern->renderSurface_ = nullptr;
    MockPipelineContext::SetUp();
    auto pipelineContext = MockPipelineContext::GetCurrent();
    webPattern->OnAttachContext(pipelineContext.GetRawPtr());
    MockPipelineContext::TearDown();
    EXPECT_EQ(webPattern->instanceId_, 0);

#endif
}

/**
 * @tc.name: ZoomOutAndIn_001
 * @tc.desc: ZoomOutAndIn.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, ZoomOutAndIn_001, TestSize.Level1)
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
    webPattern->zoomOutSwitch_ = false;
    webPattern->preScale_ = -1;
    double curScale = -3;
    double scale = 1;

    auto ret = webPattern->ZoomOutAndIn(curScale, scale);
    EXPECT_EQ(webPattern->zoomStatus_, 1);
    EXPECT_EQ(ret, true);
#endif
}

/**
 * @tc.name: ZoomOutAndIn_002
 * @tc.desc: ZoomOutAndIn.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, ZoomOutAndIn_002, TestSize.Level1)
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
    double curScale = 3;
    webPattern->preScale_ = 2;
    webPattern->startPinchScale_ = 2;
    double scale = 1;
    webPattern->zoomOutSwitch_ = false;

    auto ret = webPattern->ZoomOutAndIn(curScale, scale);
    EXPECT_EQ(webPattern->zoomStatus_, 2);
    EXPECT_EQ(ret, true);
#endif
}

/**
 * @tc.name: ZoomOutAndIn_003
 * @tc.desc: ZoomOutAndIn.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, ZoomOutAndIn_003, TestSize.Level1)
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
    double curScale = 3;
    webPattern->preScale_ = 2;
    webPattern->startPinchScale_ = 0;
    double scale = 1;
    webPattern->zoomOutSwitch_ = true;

    auto ret = webPattern->ZoomOutAndIn(curScale, scale);
    EXPECT_EQ(ret, true);
#endif
}

/**
 * @tc.name: ZoomOutAndIn_004
 * @tc.desc: ZoomOutAndIn.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, ZoomOutAndIn_004, TestSize.Level1)
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
    double curScale = 3;
    webPattern->preScale_ = 0;
    webPattern->zoomStatus_ = 1;
    double scale = 1;

    auto ret = webPattern->ZoomOutAndIn(curScale, scale);
    EXPECT_EQ(webPattern->zoomOutSwitch_, true);
    EXPECT_EQ(webPattern->zoomStatus_, 2);
    EXPECT_EQ(ret, true);
#endif
}

/**
 * @tc.name: ZoomOutAndIn_005
 * @tc.desc: ZoomOutAndIn.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, ZoomOutAndIn_005, TestSize.Level1)
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
    double curScale = 3;
    webPattern->preScale_ = 0;
    webPattern->zoomStatus_ = 0;
    double scale = 1;

    auto ret = webPattern->ZoomOutAndIn(curScale, scale);
    EXPECT_EQ(webPattern->zoomStatus_, 2);
    EXPECT_EQ(ret, true);
#endif
}

/**
 * @tc.name: ZoomOutAndIn_006
 * @tc.desc: ZoomOutAndIn.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, ZoomOutAndIn_006, TestSize.Level1)
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
    double curScale = 3;
    webPattern->preScale_ = 4;
    webPattern->zoomOutSwitch_ = true;
    webPattern->zoomStatus_ = 2;
    double scale = 1;

    auto ret = webPattern->ZoomOutAndIn(curScale, scale);
    EXPECT_EQ(webPattern->zoomOutSwitch_, false);
    EXPECT_EQ(ret, true);
#endif
}

/**
 * @tc.name: HandleScaleGestureChange_001
 * @tc.desc: HandleScaleGestureChange.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, HandleScaleGestureChange_001, TestSize.Level1)
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

    webPattern->HandleScaleGestureChange(event);
    EXPECT_NE(webPattern, nullptr);
#endif
}

/**
 * @tc.name: HandleScaleGestureChange_002
 * @tc.desc: HandleScaleGestureChange.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, HandleScaleGestureChange_002, TestSize.Level1)
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
    event.SetScale(0);
    webPattern->preScale_ = 0;

    webPattern->HandleScaleGestureChange(event);
    EXPECT_NE(webPattern, nullptr);
#endif
}

/**
 * @tc.name: HandleScaleGestureChange_003
 * @tc.desc: HandleScaleGestureChange.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, HandleScaleGestureChange_003, TestSize.Level1)
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
    event.SetScale(-2);
    webPattern->preScale_ = 0;
    webPattern->zoomStatus_ = 2;
    webPattern->zoomErrorCount_ = 1;

    webPattern->HandleScaleGestureChange(event);
    EXPECT_EQ(webPattern->zoomErrorCount_, 2);
    EXPECT_NE(webPattern, nullptr);
#endif
}

/**
 * @tc.name: HandleScaleGestureChange_004
 * @tc.desc: HandleScaleGestureChange.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, HandleScaleGestureChange_004, TestSize.Level1)
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
    event.SetScale(-2);
    webPattern->zoomStatus_ = 3;
    webPattern->zoomErrorCount_ = 1;
    webPattern->preScale_ = 4;
    webPattern->zoomOutSwitch_ = true;

    webPattern->HandleScaleGestureChange(event);
    EXPECT_EQ(webPattern->zoomErrorCount_, 0);
    EXPECT_NE(webPattern, nullptr);
#endif
}

/**
 * @tc.name: HandleScaleGestureChange_005
 * @tc.desc: HandleScaleGestureChange.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, HandleScaleGestureChange_005, TestSize.Level1)
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
    event.SetScale(-2);
    webPattern->zoomStatus_ = 3;
    webPattern->zoomErrorCount_ = 1;
    webPattern->preScale_ = 4;
    webPattern->zoomOutSwitch_ = false;

    webPattern->HandleScaleGestureChange(event);
    EXPECT_EQ(webPattern->zoomErrorCount_, 0);
    EXPECT_NE(webPattern, nullptr);
#endif
}

/**
 * @tc.name: GetNewScale_001
 * @tc.desc: GetNewScale.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, GetNewScale_001, TestSize.Level1)
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
    webPattern->pageScale_ = 1;
    double scale = 10;

    auto ret = webPattern->GetNewScale(scale);
    EXPECT_EQ(scale, 5);
    EXPECT_EQ(ret, 1);
#endif
}

/**
 * @tc.name: GetNewScale_002
 * @tc.desc: GetNewScale.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, GetNewScale_002, TestSize.Level1)
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
    webPattern->pageScale_ = 1;
    webPattern->zoomStatus_ = 2;
    double scale = 3;

    auto ret = webPattern->GetNewScale(scale);
    EXPECT_EQ(ret, scale);
#endif
}

/**
 * @tc.name: GetNewScale_003
 * @tc.desc: GetNewScale.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, GetNewScale_003, TestSize.Level1)
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
    webPattern->pageScale_ = 0.1;
    webPattern->zoomStatus_ = 1;
    webPattern->startPageScale_ = 1;
    double scale = 3;

    auto ret = webPattern->GetNewScale(scale);
    EXPECT_EQ(scale, 5);
    EXPECT_EQ(ret, 5);
#endif
}

/**
 * @tc.name: GetNewScale_004
 * @tc.desc: GetNewScale.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, GetNewScale_004, TestSize.Level1)
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
    webPattern->pageScale_ = 0.1;
    webPattern->zoomStatus_ = 1;
    webPattern->startPageScale_ = -1;
    double scale = 3;

    auto ret = webPattern->GetNewScale(scale);
    EXPECT_EQ(scale, 1);
    EXPECT_EQ(ret, 0.1);
#endif
}

/**
 * @tc.name: GetNewScale_005
 * @tc.desc: GetNewScale.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, GetNewScale_005, TestSize.Level1)
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
    webPattern->pageScale_ = 10;
    webPattern->zoomStatus_ = 1;
    double scale = 0.1;
    webPattern->startPageScale_ = (1 - scale) * 10 * 0.4444 + 0.1;

    auto ret = webPattern->GetNewScale(scale);
    EXPECT_EQ(scale, 1);
    EXPECT_EQ(ret, 0.1);
#endif
}

/**
 * @tc.name: GetNewScale_006
 * @tc.desc: GetNewScale.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, GetNewScale_006, TestSize.Level1)
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
    webPattern->pageScale_ = 0.1;
    webPattern->zoomStatus_ = 1;
    double scale = 0.1;
    webPattern->startPageScale_ = (1 - scale) * 10 * 0.4444;

    auto ret = webPattern->GetNewScale(scale);
    EXPECT_EQ(scale, 1);
    EXPECT_EQ(ret, 0.1);
#endif
}
/**
 * @tc.name: InitTouchEvent_001
 * @tc.desc: InitTouchEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, InitTouchEvent_001, TestSize.Level1)
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
    webPattern->touchEvent_ = nullptr;

    webPattern->InitTouchEvent(gestureHub);
    EXPECT_NE(webPattern, nullptr);
#endif
}

/**
 * @tc.name: InitTouchEvent_002
 * @tc.desc: InitTouchEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, InitTouchEvent_002, TestSize.Level1)
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
    TouchEventFunc func = [](TouchEventInfo&) {};
    RefPtr<TouchEventImpl> touchEvent_ = AceType::MakeRefPtr<TouchEventImpl>(std::move(func));
    webPattern->touchEvent_ = touchEvent_;
    EXPECT_NE(webPattern->touchEvent_, nullptr);

    webPattern->InitTouchEvent(gestureHub);
    EXPECT_NE(webPattern, nullptr);
#endif
}

/**
 * @tc.name: InitMouseEvent_001
 * @tc.desc: InitMouseEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, InitMouseEvent_001, TestSize.Level1)
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
    RefPtr<InputEventHub> inputHub = AceType::MakeRefPtr<InputEventHub>(eventHub);
    webPattern->mouseEvent_ = nullptr;
    EXPECT_EQ(webPattern->mouseEvent_, nullptr);

    webPattern->InitMouseEvent(inputHub);
    EXPECT_NE(webPattern, nullptr);
#endif
}

/**
 * @tc.name: InitHoverEvent_001
 * @tc.desc: InitHoverEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, InitHoverEvent_001, TestSize.Level1)
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
    RefPtr<InputEventHub> inputHub = AceType::MakeRefPtr<InputEventHub>(eventHub);
    webPattern->hoverEvent_ = nullptr;
    EXPECT_EQ(webPattern->hoverEvent_, nullptr);

    webPattern->InitHoverEvent(inputHub);
    EXPECT_NE(webPattern, nullptr);
#endif
}

/**
 * @tc.name: HandleMouseEvent_001
 * @tc.desc: HandleMouseEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, HandleMouseEvent_001, TestSize.Level1)
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
    MouseInfo info;

    webPattern->HandleMouseEvent(info);
    EXPECT_NE(webPattern, nullptr);
#endif
}

/**
 * @tc.name: WebOnMouseEvent_001
 * @tc.desc: WebOnMouseEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, WebOnMouseEvent_001, TestSize.Level1)
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
    MouseInfo info;

    webPattern->WebOnMouseEvent(info);
    EXPECT_NE(webPattern, nullptr);
#endif
}

/**
 * @tc.name: WebOnMouseEvent_002
 * @tc.desc: WebOnMouseEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, WebOnMouseEvent_002, TestSize.Level1)
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
    MouseInfo info;
    Offset offset;
    offset.SetX(10);
    offset.SetY(20);
    info.SetLocalLocation(offset);
    webPattern->mouseHoveredX_ = 1;
    webPattern->mouseHoveredY_ = 2;
    info.SetAction(MouseAction::PRESS);
    info.SetButton(MouseButton::LEFT_BUTTON);

    webPattern->WebOnMouseEvent(info);
    EXPECT_EQ(webPattern->mouseHoveredX_, 1);
    EXPECT_EQ(webPattern->mouseHoveredY_, 2);
#endif
}

/**
 * @tc.name: WebOnMouseEvent_003
 * @tc.desc: WebOnMouseEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, WebOnMouseEvent_003, TestSize.Level1)
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
    MouseInfo info;
    Offset offset;
    offset.SetX(10);
    offset.SetY(20);
    info.SetLocalLocation(offset);
    webPattern->mouseHoveredX_ = 1;
    webPattern->mouseHoveredY_ = 2;
    info.SetAction(MouseAction::RELEASE);
    info.SetButton(MouseButton::LEFT_BUTTON);
    webPattern->isReceivedArkDrag_ = true;

    webPattern->WebOnMouseEvent(info);
    EXPECT_EQ(webPattern->mouseHoveredX_, 1);
    EXPECT_EQ(webPattern->mouseHoveredY_, 2);
#endif
}

/**
 * @tc.name: WebOnMouseEvent_004
 * @tc.desc: WebOnMouseEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, WebOnMouseEvent_004, TestSize.Level1)
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
    MouseInfo info;
    Offset offset;
    offset.SetX(10);
    offset.SetY(20);
    info.SetLocalLocation(offset);
    webPattern->mouseHoveredX_ = 1;
    webPattern->mouseHoveredY_ = 2;
    info.SetAction(MouseAction::HOVER_EXIT);
    info.SetButton(MouseButton::LEFT_BUTTON);
    webPattern->isReceivedArkDrag_ = false;

    webPattern->WebOnMouseEvent(info);
    EXPECT_EQ(webPattern->mouseHoveredX_, 1);
    EXPECT_EQ(webPattern->mouseHoveredY_, 2);
#endif
}

/**
 * @tc.name: WebOnMouseEvent_005
 * @tc.desc: WebOnMouseEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, WebOnMouseEvent_005, TestSize.Level1)
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
    MouseInfo info;
    Offset offset;
    offset.SetX(10);
    offset.SetY(20);
    info.SetLocalLocation(offset);
    webPattern->mouseHoveredX_ = 1;
    webPattern->mouseHoveredY_ = 2;
    info.SetAction(MouseAction::MOVE);
    info.SetButton(MouseButton::LEFT_BUTTON);

    webPattern->WebOnMouseEvent(info);
    EXPECT_EQ(webPattern->mouseHoveredX_, 10);
    EXPECT_EQ(webPattern->mouseHoveredY_, 20);
#endif
}

/**
 * @tc.name: ResetDragAction_001
 * @tc.desc: ResetDragAction.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, ResetDragAction_001, TestSize.Level1)
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
    webPattern->isDragging_ = true;

    webPattern->ResetDragAction();
    EXPECT_EQ(webPattern->isDragging_, false);
#endif
}

/**
 * @tc.name: ResetDragAction_002
 * @tc.desc: ResetDragAction.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, ResetDragAction_002, TestSize.Level1)
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
    webPattern->isDragging_ = true;

    webPattern->ResetDragAction();
    EXPECT_EQ(webPattern->isDragging_, false);
#endif
}

/**
 * @tc.name: ResetDragAction_003
 * @tc.desc: ResetDragAction.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, ResetDragAction_003, TestSize.Level1)
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
    webPattern->isDragging_ = false;

    webPattern->ResetDragAction();
    EXPECT_EQ(webPattern->isDragging_, false);
#endif
}

/**
 * @tc.name: GetDragOffset_001
 * @tc.desc: GetDragOffset.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, GetDragOffset_001, TestSize.Level1)
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

    auto ret = webPattern->GetDragOffset();
    EXPECT_EQ(ret.GetX(), 0);
    EXPECT_EQ(ret.GetY(), 0);
#endif
}

/**
 * @tc.name: GetDragOffset_002
 * @tc.desc: GetDragOffset.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, GetDragOffset_002, TestSize.Level1)
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
    webPattern->delegate_->dragData_ = nullptr;

    auto ret = webPattern->GetDragOffset();
    EXPECT_EQ(ret.GetX(), 0);
    EXPECT_EQ(ret.GetY(), 0);
#endif
}

/**
 * @tc.name: GetDragOffset_003
 * @tc.desc: GetDragOffset.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, GetDragOffset_003, TestSize.Level1)
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
    auto dragData_ = std::make_shared<MockNWebDragData>();
    webPattern->delegate_->dragData_ = dragData_;

    auto ret = webPattern->GetDragOffset();
    EXPECT_EQ(ret.GetX(), 10);
    EXPECT_EQ(ret.GetY(), 20);
#endif
}

/**
 * @tc.name: WebRequestFocus_001
 * @tc.desc: WebRequestFocus.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, WebRequestFocus_001, TestSize.Level1)
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
    webPattern->WebRequestFocus();
#endif
}

/**
 * @tc.name: HandleFocusEvent_001
 * @tc.desc: HandleFocusEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, HandleFocusEvent_001, TestSize.Level1)
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
    webPattern->needOnFocus_ = false;
    webPattern->HandleFocusEvent();
    EXPECT_TRUE(webPattern->needOnFocus_);
#endif
}

/**
 * @tc.name: HandleFocusEvent_002
 * @tc.desc: HandleFocusEvent.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, HandleFocusEvent_002, TestSize.Level1)
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
    webPattern->needOnFocus_ = true;
    webPattern->HandleFocusEvent();
    EXPECT_TRUE(webPattern->needOnFocus_);
#endif
}
} // namespace OHOS::Ace::NG