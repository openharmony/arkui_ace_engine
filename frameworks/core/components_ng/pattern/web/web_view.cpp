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

#include "base/utils/utils.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/web/web_event_hub.h"
#include "core/components_ng/pattern/web/web_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
void WebView::Create(const std::string& src, const RefPtr<WebController>& webController)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::WEB_ETS_TAG, nodeId,
        [src, webController]() { return AceType::MakeRefPtr<WebPattern>(src, webController); });
    stack->Push(frameNode);
    NG::ViewAbstract::SetFocusType(NG::FocusType::NODE);
    NG::ViewAbstract::SetFocusable(true);

    auto webPattern = frameNode->GetPattern<WebPattern>();
    CHECK_NULL_VOID(webPattern);
    webPattern->SetWebSrc(src);
    webPattern->SetWebController(webController);
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

void WebView::SetOnDragStartId(const OnDragFunc& onDragStartId)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnDragStartEvent(std::move(onDragStartId));
}

void WebView::SetOnDragEnterId(const OnDropFunc& onDragEnterId)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnDragEnterEvent(std::move(onDragEnterId));
}

void WebView::SetOnDragMoveId(const OnDropFunc& onDragMoveId)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnDragMoveEvent(std::move(onDragMoveId));
}

void WebView::SetOnDragLeaveId(const OnDropFunc& onDragLeaveId)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnDragLeaveEvent(std::move(onDragLeaveId));
}

void WebView::SetOnDropId(const OnDropFunc& onDropId)
{
    auto webEventHub = ViewStackProcessor::GetInstance()->GetMainFrameNodeEventHub<WebEventHub>();
    CHECK_NULL_VOID(webEventHub);
    webEventHub->SetOnDropEvent(std::move(onDropId));
}

} // namespace OHOS::Ace::NG