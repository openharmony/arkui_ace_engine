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

#include "core/components_ng/pattern/web/web_view.h"

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/web/web_event_hub.h"
#include "core/components_ng/pattern/web/web_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "nweb_helper.h"

namespace OHOS::Ace::NG {
void WebView::Create(const std::string& webData)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<WebPattern>(); });
    stack->Push(frameNode);

    auto webPattern = frameNode->GetPattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->SetWebData(webData);
    RegisterPipelineCallback(nodeId);
}

void WebView::Create(const std::string& src, const RefPtr<WebController>& webController)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId,
        [src, webController]() { return AceType::MakeRefPtr<WebPattern>(src, webController); });
    stack->Push(frameNode);

    auto webPattern = frameNode->GetPattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->SetWebSrc(src);
    webPattern->SetWebController(webController);
    RegisterPipelineCallback(nodeId);
}

void WebView::Create(const std::string& src, SetWebIdCallback&& setWebIdCallback,
    int32_t parentWebId, bool popup)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId,
        [src, setWebIdCallback]() { return AceType::MakeRefPtr<WebPattern>(src, std::move(setWebIdCallback)); });
    stack->Push(frameNode);
    auto webPattern = frameNode->GetPattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->SetWebSrc(src);
    webPattern->SetPopup(popup);
    webPattern->SetSetWebIdCallback(std::move(setWebIdCallback));
    webPattern->SetParentNWebId(parentWebId);
    RegisterPipelineCallback(nodeId);
}

void WebView::RegisterPipelineCallback(int32_t nodeId)
{
    auto pipeline = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->AddWindowStateChangedCallback(nodeId);
}

void WebView::SetOnCommonDialogImpl(OnWebSyncFunc&& onCommonDialogImpl, DialogEventType dialogEventType)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnCommonDialogEvent(std::move(onCommonDialogImpl), dialogEventType);
}

void WebView::SetOnPageStart(OnWebAsyncFunc&& OnPageStart)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnPageStartedEvent(std::move(OnPageStart));
}

void WebView::SetOnPageFinish(OnWebAsyncFunc&& onPageEnd)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnPageFinishedEvent(std::move(onPageEnd));
}

void WebView::SetOnHttpErrorReceive(OnWebAsyncFunc&& onHttpErrorReceive)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnHttpErrorReceiveEvent(std::move(onHttpErrorReceive));
}

void WebView::SetOnErrorReceive(OnWebAsyncFunc&& onErrorReceive)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnErrorReceiveEvent(std::move(onErrorReceive));
}

void WebView::SetOnConsole(OnWebSyncFunc&& onConsole)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnConsoleEvent(std::move(onConsole));
}

void WebView::SetJsEnabled(bool isJsEnabled)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateJsEnabled(isJsEnabled);
}

void WebView::SetProgressChangeImpl(OnWebAsyncFunc&& onProgressChangeImpl)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnProgressChangeEvent(std::move(onProgressChangeImpl));
}

void WebView::SetTitleReceiveEventId(OnWebAsyncFunc&& titleReceiveEventId)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnTitleReceiveEvent(std::move(titleReceiveEventId));
}

void WebView::SetFullScreenExitEventId(OnWebAsyncFunc&& fullScreenExitEventId)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnFullScreenExitEvent(std::move(fullScreenExitEventId));
}

void WebView::SetGeolocationHideEventId(OnWebAsyncFunc&& geolocationHideEventId)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnGeolocationHideEvent(std::move(geolocationHideEventId));
}

void WebView::SetGeolocationShowEventId(OnWebAsyncFunc&& geolocationShowEventId)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnGeolocationShowEvent(std::move(geolocationShowEventId));
}

void WebView::SetRequestFocusEventId(OnWebAsyncFunc&& requestFocusEventId)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnRequestFocusEvent(std::move(requestFocusEventId));
}

void WebView::SetDownloadStartEventId(OnWebAsyncFunc&& downloadStartEventId)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnDownloadStartEvent(std::move(downloadStartEventId));
}

void WebView::SetOnFullScreenEnterImpl(OnWebAsyncFunc&& onFullScreenEnterImpl)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnFullScreenEnterEvent(std::move(onFullScreenEnterImpl));
}

void WebView::SetOnHttpAuthRequestImpl(OnWebSyncFunc&& onHttpAuthRequestImpl)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnHttpAuthRequestEvent(std::move(onHttpAuthRequestImpl));
}

void WebView::SetOnSslErrorRequestImpl(OnWebSyncFunc&& onSslErrorRequestImpl)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnSslErrorRequestEvent(std::move(onSslErrorRequestImpl));
}

void WebView::SetOnSslSelectCertRequestImpl(OnWebSyncFunc&& onSslSelectCertRequestImpl)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnSslSelectCertRequestEvent(std::move(onSslSelectCertRequestImpl));
}

void WebView::SetMediaPlayGestureAccess(bool isNeedGestureAccess)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateMediaPlayGestureAccess(isNeedGestureAccess);
}

void WebView::SetOnKeyEventCallback(std::function<void(KeyEventInfo& keyEventInfo)>&& onKeyEventId)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnKeyEvent(std::move(onKeyEventId));
}

void WebView::SetOnInterceptRequest(
    std::function<RefPtr<WebResponse>(const std::shared_ptr<BaseEventInfo>& info)>&& onInterceptRequestImpl)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnInterceptRequestEvent(std::move(onInterceptRequestImpl));
}

void WebView::SetOnUrlLoadIntercept(OnWebSyncFunc&& onUrlLoadInterceptImpl)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnUrlLoadInterceptEvent(std::move(onUrlLoadInterceptImpl));
}

void WebView::SetOnFileSelectorShow(OnWebSyncFunc&& onFileSelectorShowImpl)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnFileSelectorShowEvent(std::move(onFileSelectorShowImpl));
}

void WebView::SetOnContextMenuShow(OnWebSyncFunc&& onContextMenuImpl)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnContextMenuShowEvent(std::move(onContextMenuImpl));
}

void WebView::SetFileAccessEnabled(bool isFileAccessEnabled)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateFileAccessEnabled(isFileAccessEnabled);
}

void WebView::SetOnLineImageAccessEnabled(bool isOnLineImageAccessEnabled)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateOnLineImageAccessEnabled(isOnLineImageAccessEnabled);
}

void WebView::SetDomStorageAccessEnabled(bool isDomStorageAccessEnabled)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateDomStorageAccessEnabled(isDomStorageAccessEnabled);
}

void WebView::SetImageAccessEnabled(bool isImageAccessEnabled)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateImageAccessEnabled(isImageAccessEnabled);
}

void WebView::SetMixedMode(MixedModeContent mixedContentMode)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateMixedMode(mixedContentMode);
}

void WebView::SetZoomAccessEnabled(bool isZoomAccessEnabled)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateZoomAccessEnabled(isZoomAccessEnabled);
}

void WebView::SetGeolocationAccessEnabled(bool isGeolocationAccessEnabled)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateGeolocationAccessEnabled(isGeolocationAccessEnabled);
}

void WebView::SetUserAgent(const std::string& userAgent)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateUserAgent(userAgent);
}

void WebView::SetCustomScheme(const std::string& customScheme)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->SetCustomScheme(customScheme);
}

void WebView::SetRenderExitedId(OnWebAsyncFunc&& renderExitedId)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnRenderExitedEvent(std::move(renderExitedId));
}

void WebView::SetRefreshAccessedHistoryId(OnWebAsyncFunc&& refreshAccessedHistoryId)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnRefreshAccessedHistoryEvent(std::move(refreshAccessedHistoryId));
}

void WebView::SetCacheMode(WebCacheMode mode)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateCacheMode(mode);
}

void WebView::SetOverviewModeAccessEnabled(bool isOverviewModeAccessEnabled)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateOverviewModeAccessEnabled(isOverviewModeAccessEnabled);
}

void WebView::SetFileFromUrlAccessEnabled(bool isFileFromUrlAccessEnabled)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateFileFromUrlAccessEnabled(isFileFromUrlAccessEnabled);
}

void WebView::SetDatabaseAccessEnabled(bool isDatabaseAccessEnabled)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateDatabaseAccessEnabled(isDatabaseAccessEnabled);
}

void WebView::SetTextZoomRatio(int32_t textZoomRatioNum)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateTextZoomRatio(textZoomRatioNum);
}

void WebView::SetWebDebuggingAccessEnabled(bool isWebDebuggingAccessEnabled)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateWebDebuggingAccessEnabled(isWebDebuggingAccessEnabled);
}

void WebView::SetOnMouseEventCallback(std::function<void(MouseInfo& info)>&& onMouseId)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnMouseEvent(std::move(onMouseId));
}

void WebView::SetResourceLoadId(OnWebAsyncFunc&& resourceLoadId)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnResourceLoadEvent(std::move(resourceLoadId));
}

void WebView::SetScaleChangeId(OnWebAsyncFunc&& scaleChangeId)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnScaleChangeEvent(std::move(scaleChangeId));
}

void WebView::SetScrollId(OnWebAsyncFunc&& scrollId)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnScrollEvent(std::move(scrollId));
}

void WebView::SetPermissionRequestEventId(OnWebAsyncFunc&& permissionRequestEventId)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnPermissionRequestEvent(std::move(permissionRequestEventId));
}

void WebView::SetBackgroundColor(int32_t backgroundColor)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateBackgroundColor(backgroundColor);
}

void WebView::SetInitialScale(float scale)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateInitialScale(scale);
}

void WebView::SetSearchResultReceiveEventId(OnWebAsyncFunc&& searchResultReceiveEventId)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnSearchResultReceiveEvent(std::move(searchResultReceiveEventId));
}

void WebView::SetPinchSmoothModeEnabled(bool isPinchSmoothModeEnabled)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdatePinchSmoothModeEnabled(isPinchSmoothModeEnabled);
}

void WebView::SetWindowNewEvent(OnWebAsyncFunc&& windowNewEventId)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnWindowNewEvent(std::move(windowNewEventId));
}

void WebView::SetWindowExitEventId(OnWebAsyncFunc&& windowExitEventId)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnWindowExitEvent(std::move(windowExitEventId));
}

void WebView::SetMultiWindowAccessEnabled(bool isMultiWindowAccessEnabled)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateMultiWindowAccessEnabled(isMultiWindowAccessEnabled);
}

void WebView::SetJsProxyCallback(JsProxyCallback&& jsProxyCallback)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->SetJsProxyCallback(std::move(jsProxyCallback));
}

void WebView::SetWebCursiveFont(const std::string& cursiveFontFamily)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateWebCursiveFont(cursiveFontFamily);
}

void WebView::SetWebFantasyFont(const std::string& fantasyFontFamily)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateWebFantasyFont(fantasyFontFamily);
}

void WebView::SetWebFixedFont(const std::string& fixedFontFamily)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateWebFixedFont(fixedFontFamily);
}

void WebView::SetWebSansSerifFont(const std::string& sansSerifFontFamily)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateWebSansSerifFont(sansSerifFontFamily);
}

void WebView::SetWebSerifFont(const std::string& serifFontFamily)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateWebSerifFont(serifFontFamily);
}

void WebView::SetWebStandardFont(const std::string& standardFontFamily)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateWebStandardFont(standardFontFamily);
}

void WebView::SetDefaultFixedFontSize(int32_t defaultFixedFontSize)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateDefaultFixedFontSize(defaultFixedFontSize);
}

void WebView::SetDefaultFontSize(int32_t defaultFontSize)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateDefaultFontSize(defaultFontSize);
}

void WebView::SetMinFontSize(int32_t minFontSize)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateMinFontSize(minFontSize);
}

void WebView::SetMinLogicalFontSize(int32_t minLogicalFontSize)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateMinLogicalFontSize(minLogicalFontSize);
}

void WebView::SetBlockNetwork(bool isNetworkBlocked)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateBlockNetwork(isNetworkBlocked);
}

void WebView::SetHorizontalScrollBarAccessEnabled(bool isHorizontalScrollBarAccessEnabled)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateHorizontalScrollBarAccessEnabled(isHorizontalScrollBarAccessEnabled);
}

void WebView::SetVerticalScrollBarAccessEnabled(bool isVerticalScrollBarAccessEnabled)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateVerticalScrollBarAccessEnabled(isVerticalScrollBarAccessEnabled);
}

void WebView::SetPageVisibleId(OnWebAsyncFunc&& pageVisibleId)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnPageVisibleEvent(std::move(pageVisibleId));
}

void WebView::SetOnInterceptKeyEventCallback(std::function<bool(KeyEventInfo& keyEventInfo)>&& onPreKeyEventId)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnPreKeyEvent(std::move(onPreKeyEventId));
}

void WebView::SetDataResubmittedId(OnWebAsyncFunc&& dataResubmittedId)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnDataResubmittedEvent(std::move(dataResubmittedId));
}

void WebView::SetFaviconReceivedId(OnWebAsyncFunc&& faviconReceivedId)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnFaviconReceivedEvent(std::move(faviconReceivedId));
}

void WebView::SetTouchIconUrlId(OnWebAsyncFunc&& touchIconUrlId)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnTouchIconUrlEvent(std::move(touchIconUrlId));
}

void WebView::SetDarkMode(WebDarkMode mode)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateDarkMode(mode);
}

void WebView::SetForceDarkAccess(bool access)
{
    auto webPattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->UpdateForceDarkAccess(access);
}

void WebView::NotifyPopupWindowResult(int32_t webId, bool result)
{
    if (webId != -1) {
        std::weak_ptr<OHOS::NWeb::NWeb> nwebWeak = OHOS::NWeb::NWebHelper::Instance().GetNWeb(webId);
        auto nwebSptr = nwebWeak.lock();
        if (nwebSptr) {
            nwebSptr->NotifyPopupWindowResult(result);
        }
    }
}
} // namespace OHOS::Ace::NG
