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
#include "core/components_ng/pattern/web/web_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

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
    webModelNG->SetCustomScheme("");
    EXPECT_NE(webModelNG, nullptr);
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
    auto webModelNG = std::make_shared<WebModelNG>();
    auto onCommon = [](const BaseEventInfo* info) -> bool { return true; };
    webModelNG->SetOnCommonDialog(onCommon, 1);
    EXPECT_NE(webModelNG, nullptr);
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
    auto webModelNG = std::make_shared<WebModelNG>();
    auto fullScreenEnterEventId = [](const BaseEventInfo* info) {};
    webModelNG->SetOnFullScreenEnter(fullScreenEnterEventId);
    EXPECT_NE(webModelNG, nullptr);
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
    auto callback = [](const BaseEventInfo* info) -> bool { return true; };
    WebModelNG webModelNG;
    webModelNG.SetOnAllSslErrorRequest(callback);
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
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);

    auto callback = [](const BaseEventInfo* info) -> bool { return true; };
    WebModelNG webModelNG;
    webModelNG.SetOnAllSslErrorRequest(callback);
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
    auto callback = [](const BaseEventInfo* info) -> bool { return true; };
    WebModelNG webModelNG;
    webModelNG.SetOnOverrideUrlLoading(callback);
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
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);

    auto callback = [](const BaseEventInfo* info) -> bool { return true; };
    WebModelNG webModelNG;
    webModelNG.SetOnOverrideUrlLoading(callback);
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
    auto callback = [](const BaseEventInfo* info) -> bool { return true; };
    WebModelNG webModelNG;
    webModelNG.SetOnContextMenuHide(callback);
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
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);

    auto callback = [](const BaseEventInfo* info) -> bool { return true; };
    WebModelNG webModelNG;
    webModelNG.SetOnContextMenuHide(callback);
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
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);

    auto callback = [](const BaseEventInfo* info) -> bool { return true; };
    WebModelNG webModelNG;
    webModelNG.SetOnHttpAuthRequest(callback);
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
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);

    auto callback = [](const BaseEventInfo* info) -> bool { return true; };
    WebModelNG webModelNG;
    webModelNG.SetOnSslErrorRequest(callback);
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
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);

    auto callback = [](const BaseEventInfo* info) -> bool { return true; };
    WebModelNG webModelNG;
    webModelNG.SetOnSslSelectCertRequest(callback);
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
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<StagePattern>(); });
    stack->Push(frameNode);

    WebModelNG webModelNG;
    webModelNG.SetMediaPlayGestureAccess(true);
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
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);

    auto callback = [](const BaseEventInfo* info) -> bool { return true; };
    WebModelNG webModelNG;
    webModelNG.SetOnErrorReceive(callback);
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
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);

    auto callback = [](const BaseEventInfo* info) -> bool { return true; };
    WebModelNG webModelNG;
    webModelNG.SetOnHttpErrorReceive(callback);
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
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);

    auto callback = [](const BaseEventInfo* info) -> bool { return true; };
    WebModelNG webModelNG;
    webModelNG.SetOnUrlLoadIntercept(callback);
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
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);

    auto callback = [](const BaseEventInfo* info) -> bool { return true; };
    WebModelNG webModelNG;
    webModelNG.SetOnLoadIntercept(callback);
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
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);

    auto callback = [](const BaseEventInfo* info) -> RefPtr<WebResponse> { return AceType::MakeRefPtr<WebResponse>(); };
    WebModelNG webModelNG;
    webModelNG.SetOnInterceptRequest(callback);
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
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);

    auto callback = [](const BaseEventInfo* info) -> bool { return true; };
    WebModelNG webModelNG;
    webModelNG.SetOnFileSelectorShow(callback);
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
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);

    auto callback = [](const BaseEventInfo* info) -> bool { return true; };
    WebModelNG webModelNG;
    webModelNG.SetOnContextMenuShow(callback);
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
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<StagePattern>(); });
    stack->Push(frameNode);

    WebModelNG webModelNG;
    webModelNG.SetJsEnabled(true);
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
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<StagePattern>(); });
    stack->Push(frameNode);

    WebModelNG webModelNG;
    webModelNG.SetTextZoomRatio(1);
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
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<StagePattern>(); });
    stack->Push(frameNode);

    WebModelNG webModelNG;
    webModelNG.SetFileAccessEnabled(true);
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
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<StagePattern>(); });
    stack->Push(frameNode);

    WebModelNG webModelNG;
    webModelNG.SetOnLineImageAccessEnabled(true);
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
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<StagePattern>(); });
    stack->Push(frameNode);

    WebModelNG webModelNG;
    webModelNG.SetDomStorageAccessEnabled(true);
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
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<StagePattern>(); });
    stack->Push(frameNode);

    WebModelNG webModelNG;
    webModelNG.SetImageAccessEnabled(true);
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
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<StagePattern>(); });
    stack->Push(frameNode);

    WebModelNG webModelNG;
    webModelNG.SetMixedMode(MixedModeContent::MIXED_CONTENT_NEVER_ALLOW);
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
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<StagePattern>(); });
    stack->Push(frameNode);

    WebModelNG webModelNG;
    webModelNG.SetZoomAccessEnabled(true);
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
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<StagePattern>(); });
    stack->Push(frameNode);

    WebModelNG webModelNG;
    webModelNG.SetGeolocationAccessEnabled(true);
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
    WebModelNG webModelNG;
    webModelNG.SetDefaultTextEncodingFormat("test");
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
    WebModelNG webModelNG;
    webModelNG.SetNativeEmbedModeEnabled(true);
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
    WebModelNG webModelNG;
    webModelNG.RegisterNativeEmbedRule("test", "111");
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
    WebModelNG webModelNG;
    auto Callback = []() {};
    webModelNG.SetOnControllerAttached(Callback);
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
    WebModelNG webModelNG;
    webModelNG.AddDragFrameNodeToManager();
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
    WebModelNG webModelNG;
    webModelNG.SetAudioResumeInterval(0);
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
    WebModelNG webModelNG;
    webModelNG.SetAudioExclusive(true);
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
    WebModelNG webModelNG;
    auto OverScrollId = [](const BaseEventInfo* info) {};
    webModelNG.SetOverScrollId(std::move(OverScrollId));
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
    WebModelNG webModelNG;
    auto NativeEmbedLifecycleChangeId = [](const BaseEventInfo* info) {};
    webModelNG.SetNativeEmbedLifecycleChangeId(std::move(NativeEmbedLifecycleChangeId));
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
    WebModelNG webModelNG;
    auto NativeEmbedGestureEventId = [](const BaseEventInfo* info) {};
    webModelNG.SetNativeEmbedGestureEventId(NativeEmbedGestureEventId);
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
    WebModelNG webModelNG;
    webModelNG.SetLayoutMode(WebLayoutMode::NONE);
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
    NestedScrollOptions NestedScrollOptions;
    webModelNG.SetNestedScroll(NestedScrollOptions);
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
    NestedScrollOptionsExt NestedScrollOptionsExt;
    webModelNG.SetNestedScrollExt(NestedScrollOptionsExt);
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
    WebModelNG webModelNG;
    webModelNG.SetMetaViewport(true);
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
    WebModelNG webModelNG;
    auto SetPermissionClipboard = [](const std::shared_ptr<BaseEventInfo>& info) {};
    webModelNG.SetPermissionClipboard(std::move(SetPermissionClipboard));
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
    WebModelNG webModelNG;
    auto SetOpenAppLinkFunction = [](const std::shared_ptr<BaseEventInfo>& info) {};
    webModelNG.SetOpenAppLinkFunction(std::move(SetOpenAppLinkFunction));
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
    WebModelNG webModelNG;
    auto SetPermissionRequestEventId = [](const BaseEventInfo* info) {};
    webModelNG.SetPermissionRequestEventId(std::move(SetPermissionRequestEventId));
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
    WebModelNG webModelNG;
    webModelNG.SetTextAutosizing(true);
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
    WebModelNG webModelNG;
    webModelNG.SetNativeVideoPlayerConfig(true, true);
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
    WebModelNG webModelNG;
    auto firstMeaningfulPaintId = [](const std::shared_ptr<BaseEventInfo>& info) {};
    webModelNG.SetFirstMeaningfulPaintId(std::move(firstMeaningfulPaintId));
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
    WebModelNG webModelNG;
    auto largestContentfulPaintId = [](const std::shared_ptr<BaseEventInfo>& info) {};
    webModelNG.SetLargestContentfulPaintId(std::move(largestContentfulPaintId));
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
    WebModelNG webModelNG;
    auto navigationEntryCommittedId = [](const std::shared_ptr<BaseEventInfo>& info) {};
    webModelNG.SetNavigationEntryCommittedId(std::move(navigationEntryCommittedId));
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
    WebModelNG webModelNG;
    auto intelligentTrackingPreventionResultId = [](const std::shared_ptr<BaseEventInfo>& info) {};
    webModelNG.SetIntelligentTrackingPreventionResultId(std::move(intelligentTrackingPreventionResultId));
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
    WebModelNG webModelNG;
    webModelNG.SetSmoothDragResizeEnabled(true);
    webModelNG.SetSmoothDragResizeEnabled(false);
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
    WebModelNG webModelNG;
    auto renderProcessNotRespondingId = [](const BaseEventInfo* info) {};
    webModelNG.SetRenderProcessNotRespondingId(renderProcessNotRespondingId);
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
    WebModelNG webModelNG;
    auto renderProcessRespondingId = [](const BaseEventInfo* info) {};
    webModelNG.SetRenderProcessRespondingId(renderProcessRespondingId);
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
    WebMenuOptionsParam webMenuOption;
    webModelNG.SetSelectionMenuOptions(webMenuOption);
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
    WebModelNG webModelNG;
    auto onCreateMenuCallback =
        [](const std::vector<OHOS::Ace::NG::MenuItemParam>& /*items*/) -> std::vector<OHOS::Ace::NG::MenuOptionsParam> {
        return {};
    };
    auto onMenuItemClick = [](const OHOS::Ace::NG::MenuItemParam& /*item*/) -> bool { return false; };
    webModelNG.SetEditMenuOptions(onCreateMenuCallback, onMenuItemClick);
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
    WebModelNG webModelNG;
    auto viewportFitChangedId = [](const BaseEventInfo* info) {};
    webModelNG.SetViewportFitChangedId(viewportFitChangedId);
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
    WebModelNG webModelNG;
    auto onInterceptKeyboardAttach = [](const BaseEventInfo* info) -> WebKeyboardOption { return {}; };
    webModelNG.SetOnInterceptKeyboardAttach(onInterceptKeyboardAttach);
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
    WebModelNG webModelNG;
    auto adsBlockedEventId = [](const BaseEventInfo* info) {};
    webModelNG.SetAdsBlockedEventId(adsBlockedEventId);
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
    WebModelNG webModelNG;
    auto updateInstanceIdCallback = [](int32_t) -> void {};
    webModelNG.SetUpdateInstanceIdCallback(updateInstanceIdCallback);
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
    WebModelNG webModelNG;
    webModelNG.SetOverlayScrollbarEnabled(true);
    webModelNG.SetOverlayScrollbarEnabled(false);
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
    WebModelNG webModelNG;
    webModelNG.SetKeyboardAvoidMode(WebKeyboardAvoidMode::RESIZE_VISUAL);
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
    WebModelNG webModelNG;
    webModelNG.SetOverScrollMode(OverScrollMode::NEVER);
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
    WebModelNG webModelNG;
    webModelNG.SetCopyOptionMode(CopyOptions::None);
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
    WebModelNG webModelNG;
    auto screenCaptureRequestEventId = [](const BaseEventInfo* info) {};
    webModelNG.SetScreenCaptureRequestEventId(screenCaptureRequestEventId);
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
                           const std::string& extraParams) -> DragDropBaseInfo { return {}; };
    webModelNG.SetOnDragStart(onDragStart);
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
} // namespace OHOS::Ace::NG