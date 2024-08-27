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
#include "test/mock/core/pipeline/mock_pipeline_context.h"

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
 * @tc.name: OnAttachContext_000
 * @tc.desc: OnAttachContext.
 * @tc.type: FUNC
 */
HWTEST_F(WebPatternTestNg, OnAttachContext_000, TestSize.Level1)
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
    auto params = std::make_shared<NWebQuickMenuParamsMock>();
    auto startHandle = std::make_shared<NWebTouchHandleStateMock>();
    auto endHandle = std::make_shared<NWebTouchHandleStateMock>();
    EXPECT_CALL(*startHandle, GetEdgeHeight()).WillOnce(testing::Return(0));
    EXPECT_CALL(*startHandle, GetTouchHandleId()).WillOnce(testing::Return(-1));
    EXPECT_CALL(*endHandle, GetEdgeHeight()).WillOnce(testing::Return(0));
    EXPECT_CALL(*endHandle, GetTouchHandleId()).WillOnce(testing::Return(-1));
    EXPECT_CALL(*params, GetSelectX()).WillOnce(testing::Return(100));
    EXPECT_CALL(*params, GetSelectY()).WillOnce(testing::Return(200));
    EXPECT_CALL(*params, GetSelectWidth()).WillOnce(testing::Return(150));
    EXPECT_CALL(*params, GetSelectXHeight()).WillOnce(testing::Return(50));
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
    auto startHandle = std::make_shared<NWebTouchHandleStateMock>();
    auto endHandle = std::make_shared<NWebTouchHandleStateMock>();
    EXPECT_CALL(*startHandle, GetEdgeHeight()).WillOnce(testing::Return(10));
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
    auto viewDataWrap = AceType::MakeRefPtr<ViewDataWrapMock>(); // 使用 Mock 类初始化
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
    EXPECT_CALL(*viewDataWrap, GetPageNodeInfoWraps()).WillOnce(ReturnRef(nodeInfoWraps));
    EXPECT_CALL(*nodeWrap, GetAutoFillType())
        .WillOnce(Return(AceAutoFillType::ACE_DETAIL_INFO_WITHOUT_STREET));
    EXPECT_CALL(*nodeWrap, GetIsFocus()).WillOnce(Return(true));
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
    auto startSelectionHandle = std::make_shared<NWebTouchHandleStateMock>();
    auto endSelectionHandle = std::make_shared<NWebTouchHandleStateMock>();
    EXPECT_CALL(*startSelectionHandle, GetTouchHandleType())
        .WillRepeatedly(Return(OHOS::NWeb::NWebTouchHandleState::SELECTION_BEGIN_HANDLE));
    EXPECT_CALL(*endSelectionHandle, GetTouchHandleType())
        .WillRepeatedly(Return(OHOS::NWeb::NWebTouchHandleState::SELECTION_BEGIN_HANDLE));
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
    auto startSelectionHandle = std::make_shared<NWebTouchHandleStateMock>();
    auto endSelectionHandle = std::make_shared<NWebTouchHandleStateMock>();
    EXPECT_CALL(*startSelectionHandle, GetTouchHandleType())
        .WillRepeatedly(Return(OHOS::NWeb::NWebTouchHandleState::SELECTION_END_HANDLE));
    EXPECT_CALL(*endSelectionHandle, GetTouchHandleType())
        .WillRepeatedly(Return(OHOS::NWeb::NWebTouchHandleState::SELECTION_END_HANDLE));
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
    auto startSelectionHandle = std::make_shared<NWebTouchHandleStateMock>();
    auto endSelectionHandle = std::make_shared<NWebTouchHandleStateMock>();
    EXPECT_CALL(*startSelectionHandle, GetTouchHandleType())
        .WillRepeatedly(Return(OHOS::NWeb::NWebTouchHandleState::SELECTION_BEGIN_HANDLE));
    EXPECT_CALL(*endSelectionHandle, GetTouchHandleType())
        .WillRepeatedly(Return(OHOS::NWeb::NWebTouchHandleState::SELECTION_END_HANDLE));
    webPattern->startSelectionHandle_ = startSelectionHandle;
    webPattern->endSelectionHandle_ = endSelectionHandle;
    webPattern->IsSelectHandleReverse();
    EXPECT_EQ(webPattern->IsSelectHandleReverse(), false);
#endif
}
} // namespace OHOS::Ace::NG