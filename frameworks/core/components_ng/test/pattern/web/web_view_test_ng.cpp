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
#include "core/components_ng/pattern/web/web_pattern.h"
#include "core/components_ng/pattern/web/web_view.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/web/web_event_hub.h"
#include "core/components_v2/inspector/inspector_constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class WebViewTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void WebViewTestNg::SetUpTestCase() {}
void WebViewTestNg::TearDownTestCase() {}
void WebViewTestNg::SetUp() {}
void WebViewTestNg::TearDown() {}

/**
 * @tc.name: WebFrameNodeCreator001
 * @tc.desc: Test web_view.cpp.
 * @tc.type: FUNC
 */
HWTEST_F(WebViewTestNg, WebFrameNodeCreator001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebView::Create("123");
    RefPtr<WebController> controller = AceType::MakeRefPtr<WebController>();
    WebView::Create("page/index", controller);
    SetWebIdCallback setWebIdCallback = [](int32_t) {};
    WebView::Create("page/index", std::move(setWebIdCallback));
    OnWebSyncFunc onCommonDialogImpl = [](const std::shared_ptr<BaseEventInfo>& info) ->bool {return true;};
    DialogEventType dialogEventType = DialogEventType::DIALOG_EVENT_ALERT;
    WebView::SetOnCommonDialogImpl(std::move(onCommonDialogImpl), dialogEventType);
    OnWebAsyncFunc onPageStart = [](const std::shared_ptr<BaseEventInfo>& info) {};
    WebView::SetOnPageStart(std::move(onPageStart));
    OnWebAsyncFunc onPageEnd = [](const std::shared_ptr<BaseEventInfo>& info) {};
    WebView::SetOnPageFinish(std::move(onPageEnd));
    OnWebAsyncFunc onHttpErrorReceive = [](const std::shared_ptr<BaseEventInfo>& info) {};
    WebView::SetOnHttpErrorReceive(std::move(onHttpErrorReceive));
    OnWebAsyncFunc onErrorReceive = [](const std::shared_ptr<BaseEventInfo>& info) {};
    WebView::SetOnErrorReceive(std::move(onErrorReceive));
    OnWebSyncFunc onConsole = [](const std::shared_ptr<BaseEventInfo>& info) ->bool {return true;};
    WebView::SetOnConsole(std::move(onConsole));
    WebView::SetJsEnabled(true);
    OnWebAsyncFunc onProgressChangeImpl = [](const std::shared_ptr<BaseEventInfo>& info) {};
    WebView::SetProgressChangeImpl(std::move(onProgressChangeImpl));
    OnWebAsyncFunc titleReceiveEventId = [](const std::shared_ptr<BaseEventInfo>& info) {};
    WebView::SetTitleReceiveEventId(std::move(titleReceiveEventId));
    OnWebAsyncFunc fullScreenExitEventId = [](const std::shared_ptr<BaseEventInfo>& info) {};
    WebView::SetFullScreenExitEventId(std::move(fullScreenExitEventId));
    OnWebAsyncFunc geolocationHideEventId = [](const std::shared_ptr<BaseEventInfo>& info) {};
    WebView::SetGeolocationHideEventId(std::move(geolocationHideEventId));
    OnWebAsyncFunc geolocationShowEventId = [](const std::shared_ptr<BaseEventInfo>& info) {};
    WebView::SetGeolocationShowEventId(std::move(geolocationShowEventId));
    OnWebAsyncFunc requestFocusEventId = [](const std::shared_ptr<BaseEventInfo>& info) {};
    WebView::SetRequestFocusEventId(std::move(requestFocusEventId));
#endif
}

/**
 * @tc.name: WebFrameNodeCreator002
 * @tc.desc: Test web_view.cpp.
 * @tc.type: FUNC
 */
HWTEST_F(WebViewTestNg, WebFrameNodeCreator002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    OnWebAsyncFunc downloadStartEventId = [](const std::shared_ptr<BaseEventInfo>& info) {};
    WebView::SetDownloadStartEventId(std::move(downloadStartEventId));
    OnWebAsyncFunc onFullScreenEnterImpl = [](const std::shared_ptr<BaseEventInfo>& info) {};
    WebView::SetOnFullScreenEnterImpl(std::move(onFullScreenEnterImpl));
    OnWebSyncFunc onHttpAuthRequestImpl = [](const std::shared_ptr<BaseEventInfo>& info) ->bool {return true;};
    WebView::SetOnHttpAuthRequestImpl(std::move(onHttpAuthRequestImpl));
    OnWebSyncFunc onSslErrorRequestImpl = [](const std::shared_ptr<BaseEventInfo>& info) ->bool {return true;};
    WebView::SetOnSslErrorRequestImpl(std::move(onSslErrorRequestImpl));
    OnWebSyncFunc onSslSelectCertRequestImpl = [](const std::shared_ptr<BaseEventInfo>& info) ->bool {return true;};
    WebView::SetOnSslSelectCertRequestImpl(std::move(onSslSelectCertRequestImpl));
    WebView::SetMediaPlayGestureAccess(true);
    std::function<void(KeyEventInfo& keyEventInfo)> onKeyEventId = [](KeyEventInfo& keyEventInfo) {};
    WebView::SetOnKeyEventCallback(std::move(onKeyEventId));
    std::function<RefPtr<WebResponse>(const std::shared_ptr<BaseEventInfo>& info)> onInterceptRequestImpl =
        [](const std::shared_ptr<BaseEventInfo>& info) ->
        RefPtr<WebResponse> {return AceType::MakeRefPtr<WebResponse>();};
    WebView::SetOnInterceptRequest(std::move(onInterceptRequestImpl));
    OnWebSyncFunc onUrlLoadInterceptImpl = [](const std::shared_ptr<BaseEventInfo>& info) ->bool {return true;};
    WebView::SetOnUrlLoadIntercept(std::move(onUrlLoadInterceptImpl));
    OnWebSyncFunc onFileSelectorShowImpl = [](const std::shared_ptr<BaseEventInfo>& info) ->bool {return true;};
    WebView::SetOnFileSelectorShow(std::move(onFileSelectorShowImpl));
    OnWebSyncFunc onContextMenuImpl = [](const std::shared_ptr<BaseEventInfo>& info) ->bool {return true;};
    WebView::SetOnContextMenuShow(std::move(onContextMenuImpl));
    WebView::SetFileAccessEnabled(true);
    WebView::SetOnLineImageAccessEnabled(true);
    WebView::SetDomStorageAccessEnabled(true);
    WebView::SetImageAccessEnabled(true);
    WebView::SetMixedMode(MixedModeContent::MIXED_CONTENT_NEVER_ALLOW);
    WebView::SetZoomAccessEnabled(true);
    WebView::SetGeolocationAccessEnabled(true);
    WebView::SetUserAgent("123");
#endif
}

/**
 * @tc.name: WebFrameNodeCreator003
 * @tc.desc: Test web_view.cpp.
 * @tc.type: FUNC
 */
HWTEST_F(WebViewTestNg, WebFrameNodeCreator003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    WebView::SetCustomScheme("123");
    OnWebAsyncFunc renderExitedId = [](const std::shared_ptr<BaseEventInfo>& info) {};
    WebView::SetRenderExitedId(std::move(renderExitedId));
    OnWebAsyncFunc refreshAccessedHistoryId = [](const std::shared_ptr<BaseEventInfo>& info) {};
    WebView::SetRefreshAccessedHistoryId(std::move(refreshAccessedHistoryId));
    WebView::SetCacheMode(WebCacheMode::DEFAULT);
    WebView::SetOverviewModeAccessEnabled(true);
    WebView::SetFileFromUrlAccessEnabled(true);
    WebView::SetDatabaseAccessEnabled(true);
    WebView::SetTextZoomRatio(3);
    WebView::SetWebDebuggingAccessEnabled(true);
    std::function<void(MouseInfo& info)> onMouseId = [](MouseInfo& info) {};
    WebView::SetOnMouseEventCallback(std::move(onMouseId));
    OnWebSyncFunc resourceLoadId =
        [](const std::shared_ptr<BaseEventInfo>& info) ->bool {return true;};
    WebView::SetResourceLoadId(std::move(resourceLoadId));
    OnWebSyncFunc scaleChangeId =
        [](const std::shared_ptr<BaseEventInfo>& info) ->bool {return true;};
    WebView::SetScaleChangeId(std::move(scaleChangeId));
    OnWebSyncFunc scrollId =
        [](const std::shared_ptr<BaseEventInfo>& info) ->bool {return true;};
    WebView::SetScrollId(std::move(scrollId));
    OnWebSyncFunc permissionRequestEventId =
        [](const std::shared_ptr<BaseEventInfo>& info) ->bool {return true;};
    WebView::SetPermissionRequestEventId(std::move(permissionRequestEventId));
    WebView::SetBackgroundColor(200);
    WebView::SetInitialScale(1.2f);
    OnWebSyncFunc searchResultReceiveEventId =
        [](const std::shared_ptr<BaseEventInfo>& info) ->bool {return true;};
    WebView::SetSearchResultReceiveEventId(std::move(searchResultReceiveEventId));
    WebView::SetPinchSmoothModeEnabled(true);
    OnWebAsyncFunc windowNewEventId = [](const std::shared_ptr<BaseEventInfo>& info) {};
    WebView::SetWindowNewEvent(std::move(windowNewEventId));
    OnWebAsyncFunc windowExitEventId = [](const std::shared_ptr<BaseEventInfo>& info) {};
    WebView::SetWindowExitEventId(std::move(windowExitEventId));
    WebView::SetMultiWindowAccessEnabled(true);
    JsProxyCallback jsProxyCallback = []() {};
    WebView::SetJsProxyCallback(std::move(jsProxyCallback));
#endif
}
} // namespace OHOS::Ace::NG