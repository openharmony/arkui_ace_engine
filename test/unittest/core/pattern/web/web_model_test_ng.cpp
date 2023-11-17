/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
#endif
}
} // namespace OHOS::Ace::NG