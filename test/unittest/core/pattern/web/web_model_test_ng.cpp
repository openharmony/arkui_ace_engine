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
#include "nweb_helper.h"
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
class MockBaseEventInfo : public BaseEventInfo {
public:
    MockBaseEventInfo() : BaseEventInfo("MockEvent") {}
};

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
    bool callbackCalled = false;
    auto mockEventInfo = std::make_shared<MockBaseEventInfo>();
    webModelNG.Create("page/index", controller);
    SetWebIdCallback setWebIdCallback = [](int32_t) {};
    SetHapPathCallback setHapPathCallback = [](const std::string&) {};
    webModelNG.Create("page/index", std::move(setWebIdCallback), std::move(setHapPathCallback), -1, true);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    EXPECT_EQ(webPattern->webSrc_, "page/index");
    webModelNG.SetOnPageStart([&callbackCalled](const BaseEventInfo* info) {
        callbackCalled = true;
    });
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);
    webEventHub->FireOnPageStartedEvent(mockEventInfo);
    EXPECT_TRUE(callbackCalled);

    callbackCalled = false;
    webModelNG.SetOnPageFinish([&callbackCalled](const BaseEventInfo* info) {
        callbackCalled = true;
    });
    webEventHub->FireOnPageFinishedEvent(mockEventInfo);
    EXPECT_TRUE(callbackCalled);
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
    WebModelNG webModelNG;
    bool callbackCalled = false;
    auto mockEventInfo = std::make_shared<MockBaseEventInfo>();
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);
    webModelNG.SetOnDownloadStart([&callbackCalled](const BaseEventInfo* info) {
        callbackCalled = true;
    });
    webEventHub->FireOnDownloadStartEvent(mockEventInfo);
    EXPECT_TRUE(callbackCalled);

    callbackCalled = false;
    webModelNG.SetOnGeolocationHide([&callbackCalled](const BaseEventInfo* info) {
        callbackCalled = true;
    });
    webEventHub->FireOnGeolocationHideEvent(mockEventInfo);
    EXPECT_TRUE(callbackCalled);
    auto onKeyEventId = [](KeyEventInfo& keyEventInfo) {};
    webModelNG.SetOnKeyEvent(onKeyEventId);
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
    webModelNG.SetOptimizeParserBudgetEnabled(true);
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
    bool callbackCalled = false;
    auto mockEventInfo = std::make_shared<MockBaseEventInfo>();
    webModelNG.SetRenderExitedId([&callbackCalled](const BaseEventInfo* info) {
        callbackCalled = true;
    });
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);
    webEventHub->FireOnRenderExitedEvent(mockEventInfo);
    EXPECT_TRUE(callbackCalled);
    callbackCalled = false;
    webModelNG.SetRefreshAccessedHistoryId([&callbackCalled](const BaseEventInfo* info) {
        callbackCalled = true;
    });
    webEventHub->FireOnRefreshAccessedHistoryEvent(mockEventInfo);
    EXPECT_TRUE(callbackCalled);
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
    webModelNG.SetBackgroundColor(Color(200));
    webModelNG.InitialScale(1.2f);
    auto searchResultReceiveEventId = [](const BaseEventInfo* info) -> bool { return true; };
    webModelNG.SetSearchResultReceiveEventId(searchResultReceiveEventId);
    webModelNG.SetPinchSmoothModeEnabled(true);
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
    auto renderExitedId = [](const std::shared_ptr<BaseEventInfo>& info) {};
    bool callbackCalled = false;
    auto mockEventInfo = std::make_shared<MockBaseEventInfo>();
    webModelNG.SetWindowNewEvent([&callbackCalled](const std::shared_ptr<BaseEventInfo> info) {
        callbackCalled = true;
    });
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);
    webEventHub->FireOnWindowNewEvent(mockEventInfo);
    EXPECT_TRUE(callbackCalled);
    callbackCalled = false;
    webModelNG.SetWindowExitEventId([&callbackCalled](const BaseEventInfo* info) {
        callbackCalled = true;
    });
    webEventHub->FireOnWindowExitEvent(mockEventInfo);
    EXPECT_TRUE(callbackCalled);
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
    bool callbackCalled = false;
    auto mockEventInfo = std::make_shared<MockBaseEventInfo>();
    webModelNG.SetAudioStateChangedId([&callbackCalled](const std::shared_ptr<BaseEventInfo> info) {
        callbackCalled = true;
    });
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);
    webEventHub->FireOnAudioStateChangedEvent(mockEventInfo);
    EXPECT_TRUE(callbackCalled);

    callbackCalled = false;
    webModelNG.SetFirstContentfulPaintId([&callbackCalled](const std::shared_ptr<BaseEventInfo> info) {
        callbackCalled = true;
    });
    webEventHub->FireOnFirstContentfulPaintEvent(mockEventInfo);
    EXPECT_TRUE(callbackCalled);

    callbackCalled = false;
    webModelNG.SetSafeBrowsingCheckResultId([&callbackCalled](const std::shared_ptr<BaseEventInfo> info) {
        callbackCalled = true;
    });
    webEventHub->FireOnSafeBrowsingCheckResultEvent(mockEventInfo);
    EXPECT_TRUE(callbackCalled);
    webModelNG.SetHorizontalScrollBarAccessEnabled(true);
    webModelNG.SetVerticalScrollBarAccessEnabled(true);
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
    bool callbackCalled = false;
    WebModelNG webModelNG;
    webModelNG.SetOnCommonDialog(
        [&callbackCalled](const BaseEventInfo* info) -> bool {
            callbackCalled = true;
            return true;
        },
        DialogEventType::DIALOG_EVENT_BEFORE_UNLOAD);

    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);

    callbackCalled = false;
    auto mockEventInfo = std::make_shared<MockBaseEventInfo>();
    auto result = webEventHub->FireOnCommonDialogEvent(mockEventInfo, DialogEventType::DIALOG_EVENT_BEFORE_UNLOAD);
    EXPECT_TRUE(callbackCalled);
    EXPECT_TRUE(result);
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
    bool callbackCalled = false;
    WebModelNG webModelNG;
    webModelNG.SetOnFullScreenEnter([&callbackCalled](const BaseEventInfo* info) {
        callbackCalled = true;
        EXPECT_TRUE(info != nullptr);
    });

    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);

    auto mockEventInfo = std::make_shared<MockBaseEventInfo>();
    webEventHub->FireOnFullScreenEnterEvent(mockEventInfo);
    EXPECT_TRUE(callbackCalled);
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
    bool callbackCalled = false;
    WebModelNG webModelNG;
    webModelNG.SetOnAllSslErrorRequest([&callbackCalled](const BaseEventInfo* info) {
        callbackCalled = true;
        return true;
    });

    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);

    auto mockEventInfo = std::make_shared<MockBaseEventInfo>();
    webEventHub->FireOnAllSslErrorRequestEvent(mockEventInfo);
    EXPECT_TRUE(callbackCalled);
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
    bool callbackCalled = false;
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    WebModelNG webModelNG;
    webModelNG.SetOnOverrideUrlLoading([&callbackCalled](const BaseEventInfo* info) {
        callbackCalled = true;
        return true;
    });

    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);

    auto mockEventInfo = std::make_shared<MockBaseEventInfo>();
    webEventHub->FireOnOverrideUrlLoadingEvent(mockEventInfo);
    EXPECT_TRUE(callbackCalled);
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
    bool callbackCalled = false;
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    WebModelNG webModelNG;
    webModelNG.SetOnContextMenuHide([&callbackCalled](const BaseEventInfo* info) {
        callbackCalled = true;
    });

    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);

    auto mockEventInfo = std::make_shared<MockBaseEventInfo>();
    webEventHub->FireOnContextMenuHideEvent(mockEventInfo);
    EXPECT_TRUE(callbackCalled);
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
    bool callbackCalled = false;
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    WebModelNG webModelNG;
    webModelNG.SetOnHttpAuthRequest([&callbackCalled](const BaseEventInfo* info) {
        callbackCalled = true;
        return true;
    });

    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);

    auto mockEventInfo = std::make_shared<MockBaseEventInfo>();
    webEventHub->FireOnHttpAuthRequestEvent(mockEventInfo);
    EXPECT_TRUE(callbackCalled);
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
    bool callbackCalled = false;
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    WebModelNG webModelNG;
    webModelNG.SetOnSslErrorRequest([&callbackCalled](const BaseEventInfo* info) {
        callbackCalled = true;
        return true;
    });

    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);

    auto mockEventInfo = std::make_shared<MockBaseEventInfo>();
    webEventHub->FireOnSslErrorRequestEvent(mockEventInfo);
    EXPECT_TRUE(callbackCalled);
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
    bool callbackCalled = false;
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    WebModelNG webModelNG;
    webModelNG.SetOnSslSelectCertRequest([&callbackCalled](const BaseEventInfo* info) {
        callbackCalled = true;
        return true;
    });

    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);

    auto mockEventInfo = std::make_shared<MockBaseEventInfo>();
    webEventHub->FireOnSslSelectCertRequestEvent(mockEventInfo);
    EXPECT_TRUE(callbackCalled);
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
    bool callbackCalled = false;
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    WebModelNG webModelNG;
    webModelNG.SetOnErrorReceive([&callbackCalled](const BaseEventInfo* info) {
        callbackCalled = true;
    });

    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);

    auto mockEventInfo = std::make_shared<MockBaseEventInfo>();
    webEventHub->FireOnErrorReceiveEvent(mockEventInfo);
    EXPECT_TRUE(callbackCalled);
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
    bool callbackCalled = false;
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    WebModelNG webModelNG;
    webModelNG.SetOnHttpErrorReceive([&callbackCalled](const BaseEventInfo* info) {
        callbackCalled = true;
    });

    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);

    auto mockEventInfo = std::make_shared<MockBaseEventInfo>();
    webEventHub->FireOnHttpErrorReceiveEvent(mockEventInfo);
    EXPECT_TRUE(callbackCalled);
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
    bool callbackCalled = false;
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    WebModelNG webModelNG;
    webModelNG.SetOnUrlLoadIntercept([&callbackCalled](const BaseEventInfo* info) {
        callbackCalled = true;
        return true;
    });

    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);

    auto mockEventInfo = std::make_shared<MockBaseEventInfo>();
    webEventHub->FireOnUrlLoadInterceptEvent(mockEventInfo);
    EXPECT_TRUE(callbackCalled);
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
    bool callbackCalled = false;
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    WebModelNG webModelNG;
    webModelNG.SetOnLoadIntercept([&callbackCalled](const BaseEventInfo* info) {
        callbackCalled = true;
        return true;
    });

    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);

    auto mockEventInfo = std::make_shared<MockBaseEventInfo>();
    webEventHub->FireOnLoadInterceptEvent(mockEventInfo);
    EXPECT_TRUE(callbackCalled);
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
    bool callbackCalled = false;
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    WebModelNG webModelNG;
    webModelNG.SetOnInterceptRequest([&callbackCalled](const BaseEventInfo* info) {
        callbackCalled = true;
        return nullptr;
    });

    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);

    auto mockEventInfo = std::make_shared<MockBaseEventInfo>();
    webEventHub->FireOnInterceptRequestEvent(mockEventInfo);
    EXPECT_TRUE(callbackCalled);
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
    bool callbackCalled = false;
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    WebModelNG webModelNG;
    webModelNG.SetOnFileSelectorShow([&callbackCalled](const BaseEventInfo* info) {
        callbackCalled = true;
        return true;
    });

    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);

    auto mockEventInfo = std::make_shared<MockBaseEventInfo>();
    webEventHub->FireOnFileSelectorShowEvent(mockEventInfo);
    EXPECT_TRUE(callbackCalled);
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
    bool callbackCalled = false;
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    stack->Push(frameNode);
    WebModelNG webModelNG;
    webModelNG.SetOnContextMenuShow([&callbackCalled](const BaseEventInfo* info) {
        callbackCalled = true;
        return true;
    });

    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);

    auto mockEventInfo = std::make_shared<MockBaseEventInfo>();
    webEventHub->FireOnContextMenuShowEvent(mockEventInfo);
    EXPECT_TRUE(callbackCalled);
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
 * @tc.name: SetJsEnabled002
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetJsEnabled002, TestSize.Level1)
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
    webModelNG.SetJsEnabled(AccessibilityManager::RawPtr(frameNode), true);
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
 * @tc.name: SetFileAccessEnabled002
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetFileAccessEnabled002, TestSize.Level1)
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
    webModelNG.SetFileAccessEnabled(AccessibilityManager::RawPtr(frameNode), true);
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
 * @tc.name: SetDomStorageAccessEnabled002
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetDomStorageAccessEnabled002, TestSize.Level1)
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
    webModelNG.SetDomStorageAccessEnabled(AccessibilityManager::RawPtr(frameNode), true);
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
 * @tc.name: SetMixedMode002
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetMixedMode002, TestSize.Level1)
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
    webModelNG.SetMixedMode(AccessibilityManager::RawPtr(frameNode), MixedModeContent::MIXED_CONTENT_NEVER_ALLOW);
    EXPECT_EQ(webPattern->GetOrCreateWebProperty()->GetMixedMode(), MixedModeContent::MIXED_CONTENT_NEVER_ALLOW);
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
 * @tc.name: SetZoomAccessEnabled002
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetZoomAccessEnabled002, TestSize.Level1)
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
    webModelNG.SetZoomAccessEnabled(AccessibilityManager::RawPtr(frameNode), true);
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
    bool callbackCalled = false;
    WebModelNG webModelNG;
    webModelNG.SetPermissionRequestEventId([&callbackCalled](const BaseEventInfo* info) {
        callbackCalled = true;
    });

    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    ASSERT_NE(webEventHub, nullptr);

    auto mockEventInfo = std::make_shared<MockBaseEventInfo>();
    webEventHub->FireOnPermissionRequestEvent(mockEventInfo);
    EXPECT_TRUE(callbackCalled);
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
 * @tc.name: JavaScriptOnDocumentStart030
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, JavaScriptOnDocumentStart030, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebModelNG webModelNG;
    ScriptItems scriptItems;
    ScriptItemsByOrder scriptItemsByOrder;
    webModelNG.JavaScriptOnDocumentStartByOrder(scriptItems, scriptItemsByOrder);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    EXPECT_NE(webPattern->onDocumentStartScriptItems_, std::nullopt);
#endif
}

/**
 * @tc.name: JavaScriptOnDocumentEnd031
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, JavaScriptOnDocumentEnd031, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebModelNG webModelNG;
    ScriptItems scriptItemsEnd;
    ScriptItemsByOrder scriptItemsByOrder;
    webModelNG.JavaScriptOnDocumentEndByOrder(scriptItemsEnd, scriptItemsByOrder);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    EXPECT_NE(webPattern->onDocumentEndScriptItems_, std::nullopt);
#endif
}

/**
 * @tc.name: JavaScriptOnHeadReady032
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, JavaScriptOnHeadReady032, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebModelNG webModelNG;
    ScriptItems scriptItemsEnd;
    ScriptItemsByOrder scriptItemsByOrder;
    webModelNG.JavaScriptOnHeadReadyByOrder(scriptItemsEnd, scriptItemsByOrder);
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    EXPECT_NE(webPattern->onHeadReadyScriptItems_, std::nullopt);
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
 * @tc.name: SetOptimizeParserBudgetEnabled
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetOptimizeParserBudgetEnabled001, TestSize.Level1)
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
    webModelNG.SetOptimizeParserBudgetEnabled(true);
    EXPECT_EQ(webPattern->GetOrCreateWebProperty()->CheckOptimizeParserBudgetEnabled(true), true);
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
    bool callbackCalled = false;
    auto onDragEnter = [&callbackCalled](const RefPtr<OHOS::Ace::DragEvent>&, const std::string&) {
        callbackCalled = true;
    };
    webModelNG.SetOnDragEnter(std::move(onDragEnter));

    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<EventHub>();
    RefPtr<OHOS::Ace::DragEvent> dragEvent = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    std::string extraParams = "extraParams";
    eventHub->FireCustomerOnDragFunc(DragFuncType::DRAG_ENTER, dragEvent, extraParams);
    EXPECT_TRUE(callbackCalled);
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
    bool callbackCalled = false;
    auto onDragMove = [&callbackCalled](const RefPtr<OHOS::Ace::DragEvent>&, const std::string&) {
        callbackCalled = true;
    };
    webModelNG.SetOnDragMove(std::move(onDragMove));

    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<EventHub>();
    RefPtr<OHOS::Ace::DragEvent> dragEvent = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    std::string extraParams = "extraParams";
    eventHub->FireCustomerOnDragFunc(DragFuncType::DRAG_MOVE, dragEvent, extraParams);
    EXPECT_TRUE(callbackCalled);
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
    bool callbackCalled = false;
    auto onDragLeave = [&callbackCalled](const RefPtr<OHOS::Ace::DragEvent>&, const std::string&) {
        callbackCalled = true;
    };
    webModelNG.SetOnDragLeave(std::move(onDragLeave));

    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<EventHub>();
    RefPtr<OHOS::Ace::DragEvent> dragEvent = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    std::string extraParams = "extraParams";
    eventHub->FireCustomerOnDragFunc(DragFuncType::DRAG_DROP, dragEvent, extraParams);
    EXPECT_TRUE(callbackCalled);
#endif
}

/**
 * @tc.name: SetOnDrop013
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetOnDrop013, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebModelNG webModelNG;
    bool callbackCalled = false;
    auto onDrop = [&callbackCalled](const RefPtr<OHOS::Ace::DragEvent>&, const std::string&) {
        callbackCalled = true;
    };
    webModelNG.SetOnDrop(std::move(onDrop));

    auto eventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<EventHub>();
    RefPtr<OHOS::Ace::DragEvent> dragEvent = AceType::MakeRefPtr<OHOS::Ace::DragEvent>();
    std::string extraParams = "extraParams";
    eventHub->FireCustomerOnDragFunc(DragFuncType::DRAG_DROP, dragEvent, extraParams);
    EXPECT_TRUE(callbackCalled);
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

/**
 * @tc.name: SetEnableFollowSystemFontWeight001
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetEnableFollowSystemFontWeight001, TestSize.Level1)
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
    webModelNG.SetEnableFollowSystemFontWeight(true);
    EXPECT_EQ(webPattern->GetOrCreateWebProperty()->CheckEnableFollowSystemFontWeight(true), true);
#endif
}

/**
 * @tc.name: SetCacheMode001
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetCacheMode001, TestSize.Level1)
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
    webModelNG.SetCacheMode(AccessibilityManager::RawPtr(frameNode), WebCacheMode::DEFAULT);
    EXPECT_EQ(webPattern->GetOrCreateWebProperty()->GetCacheMode(), WebCacheMode::DEFAULT);
#endif
}

/**
 * @tc.name: SetDarkMode001
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetDarkMode001, TestSize.Level1)
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
    webModelNG.SetDarkMode(AccessibilityManager::RawPtr(frameNode), WebDarkMode::Auto);
    EXPECT_EQ(webPattern->GetOrCreateWebProperty()->GetDarkMode(), WebDarkMode::Auto);
#endif
}

/**
 * @tc.name: SetAllowWindowOpenMethod001
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetAllowWindowOpenMethod001, TestSize.Level1)
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
    webModelNG.SetAllowWindowOpenMethod(AccessibilityManager::RawPtr(frameNode), true);
    EXPECT_EQ(webPattern->GetOrCreateWebProperty()->CheckAllowWindowOpenMethod(true), true);
#endif
}

/**
 * @tc.name: SetMultiWindowAccessEnabled001
 * @tc.desc: Test web_model_ng.cpp
 * @tc.type: FUNC
 */
HWTEST_F(WebModelTestNg, SetMultiWindowAccessEnabled001, TestSize.Level1)
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
    webModelNG.SetMultiWindowAccessEnabled(AccessibilityManager::RawPtr(frameNode), true);
    EXPECT_EQ(webPattern->GetOrCreateWebProperty()->CheckMultiWindowAccessEnabled(true), true);
#endif
}

} // namespace OHOS::Ace::NG
