/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/web/web_model_ng.h"
#define protected public
#include "core/components_ng/pattern/web/web_pattern.h"
#undef protected
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/manager/drag_drop/drag_drop_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class WebModelTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void WebModelTestNg::SetUpTestCase() {}
void WebModelTestNg::TearDownTestCase() {}
void WebModelTestNg::SetUp() {}
void WebModelTestNg::TearDown() {}

/**
 * @tc.name: WebFrameNodeCreator001
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, WebFrameNodeCreator001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    RefPtr<WebController> controller = AceType::MakeRefPtr<WebController>();
    WebModelNG webModelNG;
    webModelNG.Create("page/index", controller);
    SetWebIdCallback setWebIdCallback = [](int32_t) {};
    SetHapPathCallback setHapPathCallback = [](const std::string&) {};
    webModelNG.Create("page/index", std::move(setWebIdCallback), std::move(setHapPathCallback), -1, true);
    webModelNG.SetCustomScheme("123");
    auto onPageStart = [](const BaseEventInfo* info) {};
    webModelNG.SetOnPageStart(onPageStart);
    auto onPageEnd = [](const BaseEventInfo* info) {};
    webModelNG.SetOnPageFinish(onPageEnd);
    auto onHttpErrorReceive = [](const BaseEventInfo* info) {};
    webModelNG.SetOnHttpErrorReceive(onHttpErrorReceive);
    auto onErrorReceive = [](const BaseEventInfo* info) {};
    webModelNG.SetOnErrorReceive(onErrorReceive);
    auto onConsole = [](const BaseEventInfo* info) -> bool { return true; };
    webModelNG.SetOnConsoleLog(onConsole);
    webModelNG.SetJsEnabled(true);
    auto onProgressChangeImpl = [](const BaseEventInfo* info) {};
    webModelNG.SetOnProgressChange(onProgressChangeImpl);
    auto titleReceiveEventId = [](const BaseEventInfo* info) {};
    webModelNG.SetOnTitleReceive(titleReceiveEventId);
    auto fullScreenExitEventId = [](const BaseEventInfo* info) {};
    webModelNG.SetOnFullScreenExit(fullScreenExitEventId);
    auto geolocationShowEventId = [](const BaseEventInfo* info) {};
    webModelNG.SetOnGeolocationShow(geolocationShowEventId);
    auto requestFocusEventId = [](const BaseEventInfo* info) {};
    webModelNG.SetOnRequestFocus(requestFocusEventId);
#endif
}

/**
 * @tc.name: WebFrameNodeCreator002
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, WebFrameNodeCreator002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto downloadStartEventId = [](const BaseEventInfo* info) {};
    auto downloadRequestEventId = [](const BaseEventInfo* info) -> bool { return true; };
    WebModelNG webModelNG;
    webModelNG.SetOnDownloadStart(downloadStartEventId);
    webModelNG.SetOnHttpAuthRequest(downloadRequestEventId);
    auto onFullScreenEnterImpl = [](const BaseEventInfo* info) {};
    webModelNG.SetOnGeolocationHide(onFullScreenEnterImpl);
    auto onSslErrorRequestImpl = [](const BaseEventInfo* info) -> bool { return true; };
    webModelNG.SetOnSslErrorRequest(onSslErrorRequestImpl);
    auto onSslSelectCertRequestImpl = [](const BaseEventInfo* info) -> bool { return true; };
    webModelNG.SetOnSslSelectCertRequest(onSslSelectCertRequestImpl);
    webModelNG.SetMediaPlayGestureAccess(true);
    auto onKeyEventId = [](KeyEventInfo& keyEventInfo) {};
    webModelNG.SetOnKeyEvent(onKeyEventId);
    auto onInterceptRequestImpl = [](const BaseEventInfo* info) -> RefPtr<WebResponse> {
        return AceType::MakeRefPtr<WebResponse>();
    };
    webModelNG.SetOnInterceptRequest(onInterceptRequestImpl);
    auto onUrlLoadInterceptImpl = [](const BaseEventInfo* info) -> bool { return true; };
    webModelNG.SetOnUrlLoadIntercept(onUrlLoadInterceptImpl);
    webModelNG.SetOnLoadIntercept(onUrlLoadInterceptImpl);
    auto onFileSelectorShowImpl = [](const BaseEventInfo* info) -> bool { return true; };
    webModelNG.SetOnFileSelectorShow(onFileSelectorShowImpl);
    auto onContextMenuImpl = [](const BaseEventInfo* info) -> bool { return true; };
    webModelNG.SetOnContextMenuShow(onContextMenuImpl);
    webModelNG.SetFileAccessEnabled(true);
    webModelNG.SetOnLineImageAccessEnabled(true);
    webModelNG.SetDomStorageAccessEnabled(true);
    webModelNG.SetImageAccessEnabled(true);
    webModelNG.SetMixedMode(MixedModeContent::MIXED_CONTENT_NEVER_ALLOW);
    webModelNG.SetZoomAccessEnabled(true);
    webModelNG.SetGeolocationAccessEnabled(true);
    webModelNG.SetUserAgent("123");
#endif
}

/**
 * @tc.name: WebFrameNodeCreator003
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, WebFrameNodeCreator003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebModelNG webModelNG;
    webModelNG.SetCustomScheme("123");
    auto renderExitedId = [](const BaseEventInfo* info) {};
    webModelNG.SetRenderExitedId(renderExitedId);
    auto refreshAccessedHistoryId = [](const BaseEventInfo* info) {};
    webModelNG.SetRefreshAccessedHistoryId(refreshAccessedHistoryId);
    webModelNG.SetCacheMode(WebCacheMode::DEFAULT);
    webModelNG.SetOverviewModeAccessEnabled(true);
    webModelNG.SetFileFromUrlAccessEnabled(true);
    webModelNG.SetDatabaseAccessEnabled(true);
    webModelNG.SetTextZoomRatio(3);
    webModelNG.SetWebDebuggingAccessEnabled(true);
    auto onMouseId = [](MouseInfo& info) {};
    webModelNG.SetOnMouseEvent(onMouseId);
    auto resourceLoadId = [](const BaseEventInfo* info) -> bool { return true; };
    webModelNG.SetResourceLoadId(resourceLoadId);
    auto scaleChangeId = [](const BaseEventInfo* info) -> bool { return true; };
    webModelNG.SetScaleChangeId(scaleChangeId);
    auto scrollId = [](const BaseEventInfo* info) -> bool { return true; };
    webModelNG.SetScrollId(scrollId);
    webModelNG.SetPermissionRequestEventId(scrollId);
    auto permissionRequestEventId = [](const BaseEventInfo* info) -> bool { return true; };
    webModelNG.SetPermissionRequestEventId(permissionRequestEventId);
    webModelNG.SetBackgroundColor(Color(200));
    webModelNG.InitialScale(1.2f);
    auto searchResultReceiveEventId = [](const BaseEventInfo* info) -> bool { return true; };
    webModelNG.SetSearchResultReceiveEventId(searchResultReceiveEventId);
    webModelNG.SetPinchSmoothModeEnabled(true);
    auto windowNewEventId = [](const std::shared_ptr<BaseEventInfo>& info) {};
    webModelNG.SetWindowNewEvent(windowNewEventId);
    auto windowExitEventId = [](const BaseEventInfo* info) {};
    webModelNG.SetWindowExitEventId(windowExitEventId);
    webModelNG.SetMultiWindowAccessEnabled(true);
    auto jsProxyCallback = []() {};
    webModelNG.SetJsProxyCallback(jsProxyCallback);
#endif
}

/**
 * @tc.name: SetWindowNewEvent004
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetWindowNewEvent004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebModelNG webModelNG;
    auto NewEventId = [](const BaseEventInfo* info) {};
    auto renderExitedId = [](const std::shared_ptr<BaseEventInfo>& info) {};
    webModelNG.SetWindowNewEvent(std::move(renderExitedId));
    webModelNG.SetWindowExitEventId(std::move(NewEventId));
    webModelNG.SetMultiWindowAccessEnabled(true);
    webModelNG.SetWebCursiveFont("test");
    webModelNG.SetWebFantasyFont("test");
    webModelNG.SetWebSansSerifFont("test");
    webModelNG.SetWebSerifFont("test");
    webModelNG.SetWebStandardFont("test");
    webModelNG.SetDefaultFixedFontSize(0);
    webModelNG.SetDefaultFontSize(0);
    webModelNG.SetMinFontSize(0);
    webModelNG.SetMinLogicalFontSize(0);
    webModelNG.SetWebFixedFont("test");
    webModelNG.SetBlockNetwork(true);
    webModelNG.SetPageVisibleId(std::move(renderExitedId));
    std::function<bool(KeyEventInfo & keyEventInfo)> keyEvent = [](KeyEventInfo& keyEventInfo) { return true; };
    webModelNG.SetOnInterceptKeyEventCallback(std::move(keyEvent));
    webModelNG.SetDataResubmittedId(std::move(renderExitedId));
    webModelNG.SetOnDataResubmitted(std::move(renderExitedId));
    webModelNG.SetFaviconReceivedId(std::move(renderExitedId));
    webModelNG.SetTouchIconUrlId(std::move(renderExitedId));
    webModelNG.SetDarkMode(WebDarkMode::On);
    webModelNG.SetForceDarkAccess(true);
    webModelNG.SetAllowWindowOpenMethod(true);
#endif
}

/**
 * @tc.name: SetOnLoadIntercept005
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetOnLoadIntercept005, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebModelNG webModelNG;
    auto onLoadInterceptImpl = [](const BaseEventInfo* info) -> bool { return true; };
    webModelNG.SetOnLoadIntercept(std::move(onLoadInterceptImpl));
    webModelNG.SetHorizontalScrollBarAccessEnabled(true);
    webModelNG.SetVerticalScrollBarAccessEnabled(true);
    auto audioStateChanged = [](const std::shared_ptr<BaseEventInfo>& info) {};
    webModelNG.SetAudioStateChangedId(std::move(audioStateChanged));
    auto firstContentfulPaintId = [](const std::shared_ptr<BaseEventInfo>& info) {};
    webModelNG.SetFirstContentfulPaintId(std::move(firstContentfulPaintId));
    auto safeBrowsingCheckResultId = [](const std::shared_ptr<BaseEventInfo>& info) {};
    webModelNG.SetSafeBrowsingCheckResultId(std::move(safeBrowsingCheckResultId));
    webModelNG.SetNativeVideoPlayerConfig(true, false);
#endif
}

/**
 * @tc.name: SetCustomScheme001
 * @tc.desc: SetCustomScheme
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetCustomScheme001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto webModelNG = std::make_shared<WebModelNG>();
    webModelNG->SetCustomScheme("abc");

    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    EXPECT_EQ(webPattern->customScheme_, "abc");
#endif
}

/**
 * @tc.name: SetOnCommonDialog001
 * @tc.desc: SetOnCommonDialog
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetOnCommonDialog001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    int callCount = 0;
    auto webModelNG = std::make_shared<WebModelNG>();
    auto onCommon = [&callCount](const BaseEventInfo* info) -> bool {
        callCount++;
        return true;
    };
    webModelNG->SetOnCommonDialog(onCommon, 1);
    AceType::DynamicCast<WebEventHub>(ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>())
        ->onBeforeUnloadImpl_(nullptr);
    EXPECT_NE(callCount, 0);
#endif
}

/**
 * @tc.name: SetOnFullScreenEnter001
 * @tc.desc: SetOnFullScreenEnter
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetOnFullScreenEnter001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    int callCount = 0;
    auto webModelNG = std::make_shared<WebModelNG>();
    auto fullScreenEnterEventId = [&callCount](const BaseEventInfo* info) { callCount++; };
    webModelNG->SetOnFullScreenEnter(fullScreenEnterEventId);
    AceType::DynamicCast<WebEventHub>(ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>())
        ->propOnFullScreenEnterEvent_(nullptr);
    EXPECT_NE(callCount, 0);
#endif
}

/**
 * @tc.name: SetOnAllSslErrorRequest001
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetOnAllSslErrorRequest001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    int callCount = 0;
    auto callback = [&callCount](const BaseEventInfo* info) -> bool {
        callCount++;
        return true;
    };
    WebModelNG webModelNG;
    webModelNG.SetOnAllSslErrorRequest(callback);
    AceType::DynamicCast<WebEventHub>(ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>())
        ->propOnAllSslErrorRequestEvent_(nullptr);
    EXPECT_NE(callCount, 0);
#endif
}

/**
 * @tc.name: SetOnAllSslErrorRequest002
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetOnAllSslErrorRequest002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    stack->ClearStack();
    auto callback = [](const BaseEventInfo* info) -> bool { return true; };

    WebModelNG webModelNG;
    webModelNG.SetOnAllSslErrorRequest(callback);
    EXPECT_EQ(ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>(), nullptr);
#endif
}

/**
 * @tc.name: SetOnOverrideUrlLoading001
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetOnOverrideUrlLoading001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    int callCount = 0;
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    auto callback = [&callCount](const BaseEventInfo* info) -> bool {
        callCount++;
        return true;
    };
    WebModelNG webModelNG;
    webModelNG.SetOnOverrideUrlLoading(callback);
    AceType::DynamicCast<WebEventHub>(ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>())
        ->propOnOverrideUrlLoadingEvent_(nullptr);
    EXPECT_NE(callCount, 0);
#endif
}

/**
 * @tc.name: SetOnOverrideUrlLoading002
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetOnOverrideUrlLoading002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    stack->ClearStack();

    auto callback = [](const BaseEventInfo* info) -> bool { return true; };
    WebModelNG webModelNG;
    webModelNG.SetOnOverrideUrlLoading(callback);
    EXPECT_EQ(ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>(), nullptr);
#endif
}

/**
 * @tc.name: SetOnContextMenuHide001
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetOnContextMenuHide001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    int callCount = 0;
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    auto callback = [&callCount](const BaseEventInfo* info) -> bool {
        callCount++;
        return true;
    };
    WebModelNG webModelNG;
    webModelNG.SetOnContextMenuHide(callback);
    AceType::DynamicCast<WebEventHub>(ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>())
        ->propOnContextMenuHideEvent_(nullptr);
    EXPECT_NE(callCount, 0);
#endif
}

/**
 * @tc.name: SetOnContextMenuHide002
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetOnContextMenuHide002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    stack->ClearStack();

    auto callback = [](const BaseEventInfo* info) -> bool { return true; };
    WebModelNG webModelNG;
    webModelNG.SetOnContextMenuHide(callback);
    EXPECT_EQ(ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>(), nullptr);
#endif
}

/**
 * @tc.name: SetOnHttpAuthRequest001
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetOnHttpAuthRequest001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    int callCount = 0;
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    auto callback = [&callCount](const BaseEventInfo* info) -> bool {
        callCount++;
        return true;
    };
    WebModelNG webModelNG;
    webModelNG.SetOnHttpAuthRequest(callback);
    AceType::DynamicCast<WebEventHub>(ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>())
        ->propOnHttpAuthRequestEvent_(nullptr);
    EXPECT_NE(callCount, 0);
#endif
}

/**
 * @tc.name: SetOnSslErrorRequest001
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetOnSslErrorRequest001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    int callCount = 0;
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    auto callback = [&callCount](const BaseEventInfo* info) -> bool {
        callCount++;
        return true;
    };
    WebModelNG webModelNG;
    webModelNG.SetOnSslErrorRequest(callback);
    AceType::DynamicCast<WebEventHub>(ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>())
        ->propOnSslErrorRequestEvent_(nullptr);
    EXPECT_NE(callCount, 0);
#endif
}

/**
 * @tc.name: SetOnSslSelectCertRequest001
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetOnSslSelectCertRequest001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    int callCount = 0;
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    auto callback = [&callCount](const BaseEventInfo* info) -> bool {
        callCount++;
        return true;
    };
    WebModelNG webModelNG;
    webModelNG.SetOnSslSelectCertRequest(callback);
    AceType::DynamicCast<WebEventHub>(ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>())
        ->propOnSslSelectCertRequestEvent_(nullptr);
    EXPECT_NE(callCount, 0);
#endif
}

/**
 * @tc.name: SetMediaPlayGestureAccess001
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetMediaPlayGestureAccess001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();

    WebModelNG webModelNG;
    webModelNG.SetMediaPlayGestureAccess(true);
    EXPECT_EQ(webPattern->GetOrCreateWebProperty()->CheckMediaPlayGestureAccess(true), true);
#endif
}

/**
 * @tc.name: SetOnErrorReceive001
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetOnErrorReceive001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    int callCount = 0;
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    auto callback = [&callCount](const BaseEventInfo* info) -> bool {
        callCount++;
        return true;
    };
    WebModelNG webModelNG;
    webModelNG.SetOnErrorReceive(callback);
    AceType::DynamicCast<WebEventHub>(ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>())
        ->propOnErrorReceiveEvent_(nullptr);
    EXPECT_NE(callCount, 0);
#endif
}

/**
 * @tc.name: SetOnHttpErrorReceive001
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetOnHttpErrorReceive001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    int callCount = 0;
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    auto callback = [&callCount](const BaseEventInfo* info) -> bool {
        callCount++;
        return true;
    };
    WebModelNG webModelNG;
    webModelNG.SetOnHttpErrorReceive(callback);
    AceType::DynamicCast<WebEventHub>(ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>())
        ->propOnHttpErrorReceiveEvent_(nullptr);
    EXPECT_NE(callCount, 0);
#endif
}

/**
 * @tc.name: SetOnUrlLoadIntercept001
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetOnUrlLoadIntercept001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    int callCount = 0;
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    auto callback = [&callCount](const BaseEventInfo* info) -> bool {
        callCount++;
        return true;
    };
    WebModelNG webModelNG;
    webModelNG.SetOnUrlLoadIntercept(callback);
    AceType::DynamicCast<WebEventHub>(ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>())
        ->propOnUrlLoadInterceptEvent_(nullptr);
    EXPECT_NE(callCount, 0);
#endif
}

/**
 * @tc.name: SetOnLoadIntercept001
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetOnLoadIntercept001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    int callCount = 0;
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    auto callback = [&callCount](const BaseEventInfo* info) -> bool {
        callCount++;
        return true;
    };
    WebModelNG webModelNG;
    webModelNG.SetOnLoadIntercept(callback);
    AceType::DynamicCast<WebEventHub>(ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>())
        ->propOnLoadInterceptEvent_(nullptr);
    EXPECT_NE(callCount, 0);
#endif
}

/**
 * @tc.name: SetOnInterceptRequest001
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetOnInterceptRequest001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    int callCount = 0;
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    auto callback = [&callCount](const BaseEventInfo* info) -> RefPtr<WebResponse> {
        callCount++;
        return AceType::MakeRefPtr<WebResponse>();
    };
    WebModelNG webModelNG;
    webModelNG.SetOnInterceptRequest(callback);
    AceType::DynamicCast<WebEventHub>(ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>())
        ->propOnInterceptRequestEvent_(nullptr);
    EXPECT_NE(callCount, 0);
#endif
}

/**
 * @tc.name: SetOnFileSelectorShow001
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetOnFileSelectorShow001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    int callCount = 0;
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    auto callback = [&callCount](const BaseEventInfo* info) -> bool {
        callCount++;
        return true;
    };
    WebModelNG webModelNG;
    webModelNG.SetOnFileSelectorShow(callback);
    AceType::DynamicCast<WebEventHub>(ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>())
        ->propOnFileSelectorShowEvent_(nullptr);
    EXPECT_NE(callCount, 0);
#endif
}

/**
 * @tc.name: SetOnContextMenuShow001
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetOnContextMenuShow001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    int callCount = 0;
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    auto callback = [&callCount](const BaseEventInfo* info) -> bool {
        callCount++;
        return true;
    };
    WebModelNG webModelNG;
    webModelNG.SetOnContextMenuShow(callback);
    AceType::DynamicCast<WebEventHub>(ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>())
        ->propOnContextMenuShowEvent_(nullptr);
    EXPECT_NE(callCount, 0);
#endif
}

/**
 * @tc.name: SetJsEnabled001
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetJsEnabled001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();

    WebModelNG webModelNG;
    webModelNG.SetJsEnabled(true);
    EXPECT_EQ(webPattern->GetOrCreateWebProperty()->CheckJsEnabled(true), true);
#endif
}

/**
 * @tc.name: SetTextZoomRatio001
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetTextZoomRatio001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();

    WebModelNG webModelNG;
    webModelNG.SetTextZoomRatio(1);
    EXPECT_EQ(webPattern->GetOrCreateWebProperty()->CheckTextZoomRatio(1), true);
#endif
}

/**
 * @tc.name: SetFileAccessEnabled001
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetFileAccessEnabled001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();

    WebModelNG webModelNG;
    webModelNG.SetFileAccessEnabled(true);
    EXPECT_EQ(webPattern->GetOrCreateWebProperty()->CheckFileAccessEnabled(true), true);
#endif
}

/**
 * @tc.name: SetOnLineImageAccessEnabled001
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetOnLineImageAccessEnabled001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();

    WebModelNG webModelNG;
    webModelNG.SetOnLineImageAccessEnabled(true);
    EXPECT_EQ(webPattern->GetOrCreateWebProperty()->CheckOnLineImageAccessEnabled(true), true);
#endif
}

/**
 * @tc.name: SetDomStorageAccessEnabled001
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetDomStorageAccessEnabled001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();

    WebModelNG webModelNG;
    webModelNG.SetDomStorageAccessEnabled(true);
    EXPECT_EQ(webPattern->GetOrCreateWebProperty()->CheckDomStorageAccessEnabled(true), true);
#endif
}

/**
 * @tc.name: SetImageAccessEnabled001
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetImageAccessEnabled001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();

    WebModelNG webModelNG;
    webModelNG.SetImageAccessEnabled(true);
    EXPECT_EQ(webPattern->GetOrCreateWebProperty()->CheckImageAccessEnabled(true), true);
#endif
}

/**
 * @tc.name: SetMixedMode001
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetMixedMode001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();

    WebModelNG webModelNG;
    webModelNG.SetMixedMode(MixedModeContent::MIXED_CONTENT_NEVER_ALLOW);
    EXPECT_EQ(webPattern->GetOrCreateWebProperty()->CheckMixedMode(MixedModeContent::MIXED_CONTENT_NEVER_ALLOW),
        MixedModeContent::MIXED_CONTENT_NEVER_ALLOW);
#endif
}

/**
 * @tc.name: SetZoomAccessEnabled001
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetZoomAccessEnabled001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();

    WebModelNG webModelNG;
    webModelNG.SetZoomAccessEnabled(true);
    EXPECT_EQ(webPattern->GetOrCreateWebProperty()->CheckZoomAccessEnabled(true), true);
#endif
}

/**
 * @tc.name: SetGeolocationAccessEnabled001
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetGeolocationAccessEnabled001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();

    WebModelNG webModelNG;
    webModelNG.SetGeolocationAccessEnabled(true);
    EXPECT_EQ(webPattern->GetOrCreateWebProperty()->CheckGeolocationAccessEnabled(true), true);
#endif
}

/**
 * @tc.name: SetDefaultTextEncodingFormat006
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetDefaultTextEncodingFormat006, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();

    WebModelNG webModelNG;
    webModelNG.SetDefaultTextEncodingFormat("test");
    EXPECT_EQ(webPattern->GetOrCreateWebProperty()->CheckDefaultTextEncodingFormat("test"), true);
#endif
}

/**
 * @tc.name: SetNativeEmbedModeEnabled007
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetNativeEmbedModeEnabled007, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();

    WebModelNG webModelNG;
    webModelNG.SetNativeEmbedModeEnabled(true);
    EXPECT_EQ(webPattern->GetOrCreateWebProperty()->CheckNativeEmbedModeEnabled(true), true);
#endif
}

/**
 * @tc.name: RegisterNativeEmbedRule008
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, RegisterNativeEmbedRule008, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();

    WebModelNG webModelNG;
    webModelNG.RegisterNativeEmbedRule("test", "111");
    EXPECT_EQ(webPattern->GetOrCreateWebProperty()->CheckNativeEmbedRuleTag("test"), true);
    EXPECT_EQ(webPattern->GetOrCreateWebProperty()->CheckNativeEmbedRuleType("111"), true);
#endif
}

/**
 * @tc.name: SetOnControllerAttached009
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetOnControllerAttached009, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    int callCount = 0;
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);

    auto callback = [&callCount]() {
        callCount++;
        return;
    };
    WebModelNG webModelNG;
    webModelNG.SetOnControllerAttached(callback);
    AceType::DynamicCast<WebPattern>(ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>())
        ->onControllerAttachedCallback_();
    EXPECT_NE(callCount, 0);
#endif
}

/**
 * @tc.name: NotifyPopupWindowResult010
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, NotifyPopupWindowResult010, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebModelNG webModelNG;
    webModelNG.NotifyPopupWindowResult(0, true);
    auto nweb = OHOS::NWeb::NWebHelper::Instance().GetNWeb(0);
    EXPECT_EQ(nweb, nullptr);
#endif
}

/**
 * @tc.name: NotifyPopupWindowResult011
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, NotifyPopupWindowResult011, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebModelNG webModelNG;
    webModelNG.NotifyPopupWindowResult(-1, true);
    auto nweb = OHOS::NWeb::NWebHelper::Instance().GetNWeb(-1);
    EXPECT_EQ(nweb, nullptr);
#endif
}

/**
 * @tc.name: NotifyPopupWindowResult012
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, NotifyPopupWindowResult012, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebModelNG webModelNG;
    webModelNG.NotifyPopupWindowResult(1, true);
    auto nweb = OHOS::NWeb::NWebHelper::Instance().GetNWeb(1);
    EXPECT_EQ(nweb, nullptr);
#endif
}

/**
 * @tc.name: AddDragFrameNodeToManager013
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, AddDragFrameNodeToManager013, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    MockPipelineContext::SetUp();
    WebModelNG webModelNG;
    webModelNG.AddDragFrameNodeToManager();
    auto ret = PipelineContext::GetCurrentContext()->GetDragDropManager()->dragFrameNodes_.empty();
    EXPECT_EQ(ret, false);
    MockPipelineContext::TearDown();
#endif
}

/**
 * @tc.name: SetAudioResumeInterval014
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetAudioResumeInterval014, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();

    WebModelNG webModelNG;
    webModelNG.SetAudioResumeInterval(0);
    EXPECT_EQ(webPattern->GetOrCreateWebProperty()->CheckAudioResumeInterval(0), true);
#endif
}

/**
 * @tc.name: SetAudioExclusive015
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetAudioExclusive015, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();

    WebModelNG webModelNG;
    webModelNG.SetAudioExclusive(true);
    EXPECT_EQ(webPattern->GetOrCreateWebProperty()->CheckAudioExclusive(true), true);
#endif
}

/**
 * @tc.name: SetOverScrollId016
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetOverScrollId016, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    int callCount = 0;
    WebModelNG webModelNG;
    auto OverScrollId = [&callCount](const BaseEventInfo* info) { callCount++; };
    webModelNG.SetOverScrollId(std::move(OverScrollId));
    AceType::DynamicCast<WebEventHub>(ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>())
        ->propOnOverScrollEvent_(nullptr);
    EXPECT_NE(callCount, 0);
#endif
}

/**
 * @tc.name: SetNativeEmbedLifecycleChangeId017
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetNativeEmbedLifecycleChangeId017, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    int callCount = 0;
    WebModelNG webModelNG;
    auto NativeEmbedLifecycleChangeId = [&callCount](const BaseEventInfo* info) { callCount++; };
    webModelNG.SetNativeEmbedLifecycleChangeId(std::move(NativeEmbedLifecycleChangeId));
    AceType::DynamicCast<WebEventHub>(ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>())
        ->propOnNativeEmbedLifecycleChangeEvent_(nullptr);
    EXPECT_NE(callCount, 0);
#endif
}

/**
 * @tc.name: SetNativeEmbedGestureEventId018
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetNativeEmbedGestureEventId018, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    int callCount = 0;
    WebModelNG webModelNG;
    auto NativeEmbedGestureEventId = [&callCount](const BaseEventInfo* info) { callCount++; };
    webModelNG.SetNativeEmbedGestureEventId(NativeEmbedGestureEventId);
    AceType::DynamicCast<WebEventHub>(ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>())
        ->propOnNativeEmbedGestureEvent_(nullptr);
    EXPECT_NE(callCount, 0);
#endif
}

/**
 * @tc.name: SetLayoutMode019
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetLayoutMode019, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();

    WebModelNG webModelNG;
    webModelNG.SetLayoutMode(WebLayoutMode::FIT_CONTENT);
    EXPECT_EQ(webPattern->layoutMode_, WebLayoutMode::FIT_CONTENT);
#endif
}

/**
 * @tc.name: SetNestedScroll020
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetNestedScroll020, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebModelNG webModelNG;
    NestedScrollOptions NestedScrollOptions = {};
    NestedScrollOptions.forward = NestedScrollMode::SELF_FIRST;
    webModelNG.SetNestedScroll(NestedScrollOptions);

    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    EXPECT_EQ(webPattern->GetNestedScroll().forward, NestedScrollMode::SELF_FIRST);
#endif
}

/**
 * @tc.name: SetNestedScrollExt021
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetNestedScrollExt021, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebModelNG webModelNG;
    NestedScrollOptionsExt NestedScrollOptionsExt = {};
    NestedScrollOptionsExt.scrollUp = NestedScrollMode::SELF_FIRST;
    webModelNG.SetNestedScrollExt(NestedScrollOptionsExt);

    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    EXPECT_EQ(webPattern->nestedScroll_.scrollUp, NestedScrollMode::SELF_FIRST);
#endif
}

/**
 * @tc.name: SetMetaViewport022
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetMetaViewport022, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();

    WebModelNG webModelNG;
    webModelNG.SetMetaViewport(true);
    EXPECT_EQ(webPattern->GetOrCreateWebProperty()->CheckMetaViewport(true), true);
#endif
}

/**
 * @tc.name: JavaScriptOnDocumentStart023
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, JavaScriptOnDocumentStart023, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebModelNG webModelNG;
    ScriptItems scriptItems;
    webModelNG.JavaScriptOnDocumentStart(scriptItems);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    EXPECT_NE(webPattern->onDocumentStartScriptItems_, std::nullopt);
#endif
}

/**
 * @tc.name: JavaScriptOnDocumentEnd024
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, JavaScriptOnDocumentEnd024, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebModelNG webModelNG;
    ScriptItems scriptItemsEnd;
    webModelNG.JavaScriptOnDocumentEnd(scriptItemsEnd);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    EXPECT_NE(webPattern->onDocumentEndScriptItems_, std::nullopt);
#endif
}

/**
 * @tc.name: SetPermissionClipboard025
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetPermissionClipboard025, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    int callCount = 0;
    WebModelNG webModelNG;
    auto SetPermissionClipboard = [&callCount](const std::shared_ptr<BaseEventInfo>& info) { callCount++; };
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();

    webModelNG.SetPermissionClipboard(std::move(SetPermissionClipboard));
    webPattern->permissionClipboardCallback_(nullptr);
    EXPECT_NE(callCount, 0);
#endif
}

/**
 * @tc.name: SetOpenAppLinkFunction026
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetOpenAppLinkFunction026, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    int callCount = 0;
    WebModelNG webModelNG;
    auto SetOpenAppLinkFunction = [&callCount](const std::shared_ptr<BaseEventInfo>& info) { callCount++; };
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();

    webModelNG.SetOpenAppLinkFunction(std::move(SetOpenAppLinkFunction));
    webPattern->onOpenAppLinkCallback_(nullptr);
    EXPECT_NE(callCount, 0);
#endif
}

/**
 * @tc.name: SetPermissionRequestEventId027
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetPermissionRequestEventId027, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    int callCount = 0;
    WebModelNG webModelNG;
    auto SetPermissionRequestEventId = [&callCount](const BaseEventInfo* info) { callCount++; };

    webModelNG.SetPermissionRequestEventId(std::move(SetPermissionRequestEventId));
    AceType::DynamicCast<WebEventHub>(ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>())
        ->propOnPermissionRequestEvent_(nullptr);
    EXPECT_NE(callCount, 0);
#endif
}

/**
 * @tc.name: SetTextAutosizing028
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetTextAutosizing028, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();

    WebModelNG webModelNG;
    webModelNG.SetTextAutosizing(true);
    EXPECT_EQ(webPattern->GetOrCreateWebProperty()->CheckTextAutosizing(true), true);
#endif
}

/**
 * @tc.name: SetNativeVideoPlayerConfig029
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetNativeVideoPlayerConfig029, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();

    WebModelNG webModelNG;
    webModelNG.SetNativeVideoPlayerConfig(true, true);
    EXPECT_EQ(webPattern->GetOrCreateWebProperty()->CheckNativeVideoPlayerConfig(std::make_tuple(true, true)), true);
#endif
}

/**
 * @tc.name: SetFirstMeaningfulPaintId001
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetFirstMeaningfulPaintId001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    int callCount = 0;
    WebModelNG webModelNG;
    auto firstMeaningfulPaintId = [&callCount](const std::shared_ptr<BaseEventInfo>& info) { callCount++; };

    webModelNG.SetFirstMeaningfulPaintId(std::move(firstMeaningfulPaintId));
    AceType::DynamicCast<WebEventHub>(ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>())
        ->propOnFirstMeaningfulPaintEvent_(nullptr);
    EXPECT_NE(callCount, 0);
#endif
}

/**
 * @tc.name: SetLargestContentfulPaintId001
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetLargestContentfulPaintId001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    int callCount = 0;
    WebModelNG webModelNG;
    auto largestContentfulPaintId = [&callCount](const std::shared_ptr<BaseEventInfo>& info) { callCount++; };

    webModelNG.SetLargestContentfulPaintId(std::move(largestContentfulPaintId));
    AceType::DynamicCast<WebEventHub>(ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>())
        ->propOnLargestContentfulPaintEvent_(nullptr);
    EXPECT_NE(callCount, 0);
#endif
}

/**
 * @tc.name: SetNavigationEntryCommittedId001
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetNavigationEntryCommittedId001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    int callCount = 0;
    WebModelNG webModelNG;
    auto navigationEntryCommittedId = [&callCount](const std::shared_ptr<BaseEventInfo>& info) { callCount++; };

    webModelNG.SetNavigationEntryCommittedId(std::move(navigationEntryCommittedId));
    AceType::DynamicCast<WebEventHub>(ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>())
        ->propOnNavigationEntryCommittedEvent_(nullptr);
    EXPECT_NE(callCount, 0);
#endif
}

/**
 * @tc.name: SetIntelligentTrackingPreventionResultId001
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetIntelligentTrackingPreventionResultId001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    int callCount = 0;
    WebModelNG webModelNG;
    auto intelligentTrackingPreventionResultId = [&callCount](
                                                     const std::shared_ptr<BaseEventInfo>& info) { callCount++; };

    webModelNG.SetIntelligentTrackingPreventionResultId(std::move(intelligentTrackingPreventionResultId));
    AceType::DynamicCast<WebEventHub>(ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>())
        ->propOnIntelligentTrackingPreventionResultEvent_(nullptr);
    EXPECT_NE(callCount, 0);
#endif
}

/**
 * @tc.name: SetSmoothDragResizeEnabled001
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetSmoothDragResizeEnabled001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();

    WebModelNG webModelNG;
    webModelNG.SetSmoothDragResizeEnabled(true);
    EXPECT_EQ(webPattern->GetOrCreateWebProperty()->CheckSmoothDragResizeEnabled(true), true);
#endif
}

/**
 * @tc.name: SetRenderProcessNotRespondingId002
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetRenderProcessNotRespondingId002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    int callCount = 0;
    WebModelNG webModelNG;
    auto renderProcessNotRespondingId = [&callCount](const BaseEventInfo* info) { callCount++; };

    webModelNG.SetRenderProcessNotRespondingId(renderProcessNotRespondingId);
    AceType::DynamicCast<WebEventHub>(ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>())
        ->propOnRenderProcessNotRespondingEvent_(nullptr);
    EXPECT_NE(callCount, 0);
#endif
}

/**
 * @tc.name: SetRenderProcessRespondingId003
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetRenderProcessRespondingId003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    int callCount = 0;
    WebModelNG webModelNG;
    auto renderProcessRespondingId = [&callCount](const BaseEventInfo* info) { callCount++; };

    webModelNG.SetRenderProcessRespondingId(renderProcessRespondingId);
    AceType::DynamicCast<WebEventHub>(ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>())
        ->propOnRenderProcessRespondingEvent_(nullptr);
    EXPECT_NE(callCount, 0);
#endif
}

/**
 * @tc.name: SetSelectionMenuOptions004
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetSelectionMenuOptions004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebModelNG webModelNG;
    WebMenuOptionsParam webMenuOption = {};
    MenuOptionsParam menuOptionsParam = {};
    menuOptionsParam.id = "test";
    webMenuOption.menuOption.push_back(menuOptionsParam);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();

    webModelNG.SetSelectionMenuOptions(webMenuOption);
    EXPECT_FALSE(webPattern->menuOptionParam_.empty());
    EXPECT_EQ(webPattern->menuOptionParam_.size(), 1);
    EXPECT_EQ(webPattern->menuOptionParam_[0].id, "test");
#endif
}

/**
 * @tc.name: SetEditMenuOptions005
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetEditMenuOptions005, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    int callCount = 0;
    WebModelNG webModelNG;
    auto onCreateMenuCallback =
        [](const std::vector<OHOS::Ace::NG::MenuItemParam>& /*items*/) -> std::vector<OHOS::Ace::NG::MenuOptionsParam> {
        return {};
    };
    auto onMenuItemClick = [&callCount](const OHOS::Ace::NG::MenuItemParam& /*item*/) -> bool {
        callCount++;
        return false;
    };
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();

    webModelNG.SetEditMenuOptions(onCreateMenuCallback, onMenuItemClick);
    webPattern->onMenuItemClick_({});
    EXPECT_NE(callCount, 0);
#endif
}

/**
 * @tc.name: SetViewportFitChangedId006
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetViewportFitChangedId006, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    int callCount = 0;
    WebModelNG webModelNG;
    auto viewportFitChangedId = [&callCount](const BaseEventInfo* info) { callCount++; };

    webModelNG.SetViewportFitChangedId(viewportFitChangedId);
    AceType::DynamicCast<WebEventHub>(ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>())
        ->propOnViewportFitChangedEvent_(nullptr);
    EXPECT_NE(callCount, 0);
#endif
}

/**
 * @tc.name: SetOnInterceptKeyboardAttach007
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetOnInterceptKeyboardAttach007, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    int callCount = 0;
    WebModelNG webModelNG;
    auto onInterceptKeyboardAttach = [&callCount](const BaseEventInfo* info) -> WebKeyboardOption {
        callCount++;
        return {};
    };
    webModelNG.SetOnInterceptKeyboardAttach(onInterceptKeyboardAttach);
    AceType::DynamicCast<WebEventHub>(ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>())
        ->propOnInterceptKeyboardAttachEvent_(nullptr);
    EXPECT_NE(callCount, 0);
#endif
}

/**
 * @tc.name: SetAdsBlockedEventId008
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetAdsBlockedEventId008, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    int callCount = 0;
    WebModelNG webModelNG;
    auto adsBlockedEventId = [&callCount](const BaseEventInfo* info) { callCount++; };
    webModelNG.SetAdsBlockedEventId(adsBlockedEventId);
    AceType::DynamicCast<WebEventHub>(ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>())
        ->propOnAdsBlockedEvent_(nullptr);
    EXPECT_NE(callCount, 0);
#endif
}

/**
 * @tc.name: SetUpdateInstanceIdCallback009
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetUpdateInstanceIdCallback009, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    int callCount = 0;
    WebModelNG webModelNG;
    auto updateInstanceIdCallback = [&callCount](int32_t) -> void { callCount++; };
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();

    webModelNG.SetUpdateInstanceIdCallback(updateInstanceIdCallback);
    webPattern->updateInstanceIdCallback_(0);
    EXPECT_NE(callCount, 0);
#endif
}

/**
 * @tc.name: SetOverlayScrollbarEnabled010
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetOverlayScrollbarEnabled010, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();

    WebModelNG webModelNG;
    webModelNG.SetOverlayScrollbarEnabled(true);
    EXPECT_EQ(webPattern->GetOrCreateWebProperty()->CheckOverlayScrollbarEnabled(true), true);
#endif
}

/**
 * @tc.name: SetKeyboardAvoidMode011
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetKeyboardAvoidMode011, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();

    WebModelNG webModelNG;
    webModelNG.SetKeyboardAvoidMode(WebKeyboardAvoidMode::RESIZE_VISUAL);
    EXPECT_EQ(webPattern->GetOrCreateWebProperty()->CheckKeyboardAvoidMode(WebKeyboardAvoidMode::RESIZE_VISUAL), true);
#endif
}

/**
 * @tc.name: SetOverScrollMode006
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetOverScrollMode006, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();

    WebModelNG webModelNG;
    webModelNG.SetOverScrollMode(OverScrollMode::ALWAYS);
    EXPECT_EQ(webPattern->GetOrCreateWebProperty()->CheckOverScrollMode(OverScrollMode::ALWAYS), true);
#endif
}

/**
 * @tc.name: SetCopyOptionMode007
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetCopyOptionMode007, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();

    WebModelNG webModelNG;
    webModelNG.SetCopyOptionMode(CopyOptions::InApp);
    EXPECT_EQ(webPattern->GetOrCreateWebProperty()->CheckCopyOptionMode(1), true);
#endif
}

/**
 * @tc.name: SetScreenCaptureRequestEventId008
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetScreenCaptureRequestEventId008, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    int callCount = 0;
    WebModelNG webModelNG;
    auto screenCaptureRequestEventId = [&callCount](const BaseEventInfo* info) { callCount++; };
    webModelNG.SetScreenCaptureRequestEventId(screenCaptureRequestEventId);
    AceType::DynamicCast<WebEventHub>(ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>())
        ->propOnScreenCaptureRequestEvent_(nullptr);
    EXPECT_NE(callCount, 0);
#endif
}

/**
 * @tc.name: SetOnDragStart009
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetOnDragStart009, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebModelNG webModelNG;
    auto onDragStart = [](const RefPtr<OHOS::Ace::DragEvent>& event,
                           const std::string& extraParams) -> DragDropBaseInfo {
        return DragDropBaseInfo { nullptr, nullptr, "" };
    };
    webModelNG.SetOnDragStart(onDragStart);
    auto dragEvent = RefPtr<OHOS::Ace::DragEvent>();
    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<EventHub>();
    auto info = eventHub->onDragStart_(dragEvent, "");
    EXPECT_EQ(info.pixelMap, nullptr);
#endif
}

/**
 * @tc.name: SetOnDragEnter010
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetOnDragEnter010, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebModelNG webModelNG;
    auto onDragEnter = [](const RefPtr<OHOS::Ace::DragEvent>&, const std::string&) {};
    webModelNG.SetOnDragEnter(onDragEnter);
#endif
}

/**
 * @tc.name: SetOnDragMove011
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetOnDragMove011, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebModelNG webModelNG;
    auto onDragMove = [](const RefPtr<OHOS::Ace::DragEvent>&, const std::string&) {};
    webModelNG.SetOnDragMove(onDragMove);
#endif
}

/**
 * @tc.name: SetOnDragLeave012
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetOnDragLeave012, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebModelNG webModelNG;
    auto onDragLeave = [](const RefPtr<OHOS::Ace::DragEvent>&, const std::string&) {};
    webModelNG.SetOnDragLeave(onDragLeave);
#endif
}

/**
 * @tc.name: SetOnDragLeave013
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetOnDragLeave013, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebModelNG webModelNG;
    auto onDragLeave = [](const RefPtr<OHOS::Ace::DragEvent>&, const std::string&) {};
    webModelNG.SetOnDragLeave(onDragLeave);
#endif
}

/**
 * @tc.name: SetOnDrop014
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetOnDrop014, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebModelNG webModelNG;
    auto onDrop = [](const RefPtr<OHOS::Ace::DragEvent>&, const std::string&) {};
    webModelNG.SetOnDrop(onDrop);
#endif
}

/**
 * @tc.name: SetOnRequestFocus001
 * @tc.desc: Test OnRequestFoscus with frameNode
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetOnRequestFocus001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    MockPipelineContext::SetUp();
    RefPtr<WebController> controller = AceType::MakeRefPtr<WebController>();
    WebModelNG webModelNG;
    webModelNG.Create("page/index", controller);
    NG::FrameNode* frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto onRequestFocus = [](const BaseEventInfo *) {};
    webModelNG.SetOnRequestFocus(std::move(onRequestFocus));
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);
    auto focusEvent = std::make_shared<LoadWebRequestFocusEvent>("");
    ASSERT_NE(focusEvent, nullptr);
    webEventHub->FireOnRequestFocusEvent(focusEvent);
    // Clear the FrameNode in ViewStackProcessor.
    NG::ViewStackProcessor::GetInstance()->elementsStack_.pop();
    MockPipelineContext::TearDown();
#endif
}

/**
 * @tc.name: SetOnRequestFocus002
 * @tc.desc: Test OnRequestFoscus without frameNode
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetOnRequestFocus002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    MockPipelineContext::SetUp();
    RefPtr<WebController> controller = AceType::MakeRefPtr<WebController>();
    WebModelNG webModelNG;
    webModelNG.Create("page/index", controller);
    NG::FrameNode* frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto onRequestFocus = [](const BaseEventInfo *) {};
    webModelNG.SetOnRequestFocus(std::move(onRequestFocus));
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);
    // Pop the webNode to let it destruct.
    NG::ViewStackProcessor::GetInstance()->elementsStack_.pop();
    auto focusEvent = std::make_shared<LoadWebRequestFocusEvent>("");
    ASSERT_NE(focusEvent, nullptr);
    webEventHub->FireOnRequestFocusEvent(focusEvent);
    MockPipelineContext::TearDown();
#endif
}

/**
 * @tc.name: SetOnKeyEvent001
 * @tc.desc: Test OnKeyEvent with frameNode
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetOnKeyEvent001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    MockPipelineContext::SetUp();
    RefPtr<WebController> controller = AceType::MakeRefPtr<WebController>();
    WebModelNG webModelNG;
    webModelNG.Create("page/index", controller);
    NG::FrameNode* frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto onKeyEvent = [](KeyEventInfo& keyEventInfo) {};
    webModelNG.SetOnKeyEvent(std::move(onKeyEvent));

    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);
    auto keyEventCallback = webEventHub->GetOnKeyEvent();
    ASSERT_NE(keyEventCallback, nullptr);
    KeyEvent keyEvent;
    KeyEventInfo keyEventInfo(keyEvent);
    keyEventCallback(keyEventInfo);
    // Clear the FrameNode in ViewStackProcessor.
    NG::ViewStackProcessor::GetInstance()->elementsStack_.pop();
    MockPipelineContext::TearDown();
#endif
}

/**
 * @tc.name: SetOnKeyEvent002
 * @tc.desc: Test OnKeyEvent without frameNode
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetOnKeyEvent002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    MockPipelineContext::SetUp();
    RefPtr<WebController> controller = AceType::MakeRefPtr<WebController>();
    WebModelNG webModelNG;
    webModelNG.Create("page/index", controller);
    NG::FrameNode* frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto onKeyEvent = [](KeyEventInfo& keyEventInfo) {};
    webModelNG.SetOnKeyEvent(std::move(onKeyEvent));
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);
    // Pop the webNode to let it destruct.
    NG::ViewStackProcessor::GetInstance()->elementsStack_.pop();
    auto keyEventCallback = webEventHub->GetOnKeyEvent();
    ASSERT_NE(keyEventCallback, nullptr);
    KeyEvent keyEvent;
    KeyEventInfo keyEventInfo(keyEvent);
    keyEventCallback(keyEventInfo);
    MockPipelineContext::TearDown();
#endif
}

/**
 * @tc.name: SetOnMouseEvent001
 * @tc.desc: Test OnMouseEvent with frameNode
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetOnMouseEvent001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    MockPipelineContext::SetUp();
    RefPtr<WebController> controller = AceType::MakeRefPtr<WebController>();
    WebModelNG webModelNG;
    webModelNG.Create("page/index", controller);
    NG::FrameNode* frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto onMouseEvent = [](MouseInfo &info) {};
    webModelNG.SetOnMouseEvent(std::move(onMouseEvent));

    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);
    auto mouseEventCallback = webEventHub->GetOnMouseEvent();
    ASSERT_NE(mouseEventCallback, nullptr);
    MouseInfo mouseInfo;
    mouseEventCallback(mouseInfo);
    // Clear the FrameNode in ViewStackProcessor.
    NG::ViewStackProcessor::GetInstance()->elementsStack_.pop();
    MockPipelineContext::TearDown();
#endif
}

/**
 * @tc.name: SetOnMouseEvent002
 * @tc.desc: Test OnMouseEvent without frameNode
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetOnMouseEvent002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    MockPipelineContext::SetUp();
    RefPtr<WebController> controller = AceType::MakeRefPtr<WebController>();
    WebModelNG webModelNG;
    webModelNG.Create("page/index", controller);
    NG::FrameNode* frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto onMouseEvent = [](MouseInfo& info) {};
    webModelNG.SetOnMouseEvent(std::move(onMouseEvent));
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);
    // Pop the webNode to let it destruct.
    NG::ViewStackProcessor::GetInstance()->elementsStack_.pop();
    auto mouseEventCallback = webEventHub->GetOnMouseEvent();
    ASSERT_NE(mouseEventCallback, nullptr);
    MouseInfo mouseInfo;
    mouseEventCallback(mouseInfo);
    MockPipelineContext::TearDown();
#endif
}

/**
 * @tc.name: SetOnInterceptKeyEvent001
 * @tc.desc: Test OnInterceptKeyEvent with frameNode
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetOnInterceptKeyEvent001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    MockPipelineContext::SetUp();
    RefPtr<WebController> controller = AceType::MakeRefPtr<WebController>();
    WebModelNG webModelNG;
    webModelNG.Create("page/index", controller);
    NG::FrameNode* frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto onInterceptKeyEvent = [](KeyEventInfo& keyEventInfo) -> bool {
        return true;
    };
    webModelNG.SetOnInterceptKeyEventCallback(std::move(onInterceptKeyEvent));

    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);
    auto interceptKeyEventCallback = webEventHub->GetOnPreKeyEvent();
    ASSERT_NE(interceptKeyEventCallback, nullptr);
    KeyEvent keyEvent;
    KeyEventInfo keyEventInfo(keyEvent);
    interceptKeyEventCallback(keyEventInfo);
    // Clear the FrameNode in ViewStackProcessor.
    NG::ViewStackProcessor::GetInstance()->elementsStack_.pop();
    MockPipelineContext::TearDown();
#endif
}

/**
 * @tc.name: SetOnInterceptKeyEvent002
 * @tc.desc: Test OnInterceptKeyEvent without frameNode
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetOnInterceptKeyEvent002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    MockPipelineContext::SetUp();
    RefPtr<WebController> controller = AceType::MakeRefPtr<WebController>();
    WebModelNG webModelNG;
    webModelNG.Create("page/index", controller);
    NG::FrameNode* frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto onInterceptKeyEvent = [](KeyEventInfo& keyEventInfo) -> bool {
        return true;
    };
    webModelNG.SetOnInterceptKeyEventCallback(std::move(onInterceptKeyEvent));

    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);
    // Pop the webNode to let it destruct.
    NG::ViewStackProcessor::GetInstance()->elementsStack_.pop();
    auto interceptKeyEventCallback = webEventHub->GetOnPreKeyEvent();
    ASSERT_NE(interceptKeyEventCallback, nullptr);
    KeyEvent keyEvent;
    KeyEventInfo keyEventInfo(keyEvent);
    interceptKeyEventCallback(keyEventInfo);
    MockPipelineContext::TearDown();
#endif
}
} // namespace OHOS::Ace::NG
