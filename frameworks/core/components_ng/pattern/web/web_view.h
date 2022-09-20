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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WEB_WEB_VIEW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WEB_WEB_VIEW_H

#include <functional>
#include <string>

#include "core/components/web/web_property.h"
#include "core/components/box/drag_drop_event.h"

namespace OHOS::Ace::NG {

using OnWebSyncFunc = std::function<bool(const std::shared_ptr<BaseEventInfo>& info)>;
using OnWebAsyncFunc = std::function<void(const std::shared_ptr<BaseEventInfo>& info)>;

class ACE_EXPORT WebView {
public:
    static void Create(const std::string& src, const RefPtr<WebController>& webController);
    static void SetOnCommonDialogImpl(OnWebSyncFunc&& onCommonDialogImpl, DialogEventType dialogEventType);
    static void SetOnPageStart(OnWebAsyncFunc&& onPageStart);
    static void SetOnPageFinish(OnWebAsyncFunc&& onPageEnd);
    static void SetOnHttpErrorReceive(OnWebAsyncFunc&& onHttpErrorReceive);
    static void SetOnErrorReceive(OnWebAsyncFunc&& onErrorReceive);
    static void SetOnConsole(OnWebSyncFunc&& onConsole);
    static void SetJsEnabled(bool isJsEnabled);
    static void SetProgressChangeImpl(OnWebAsyncFunc&& onProgressChangeImpl);
    static void SetTitleReceiveEventId(OnWebAsyncFunc&& titleReceiveEventId);
    static void SetGeolocationHideEventId(OnWebAsyncFunc&& geolocationHideEventId);
    static void SetGeolocationShowEventId(OnWebAsyncFunc&& geolocationShowEventId);
    static void SetRequestFocusEventId(OnWebAsyncFunc&& requestFocusEventId);
    static void SetDownloadStartEventId(OnWebAsyncFunc&& downloadStartEventId);
    static void SetOnHttpAuthRequestImpl(OnWebSyncFunc&& onHttpAuthRequestImpl);
    static void SetOnSslErrorRequestImpl(OnWebSyncFunc&& onSslErrorRequestImpl);
    static void SetOnSslSelectCertRequestImpl(OnWebSyncFunc&& onSslSelectCertRequestImpl);
    static void SetMediaPlayGestureAccess(bool isNeedGestureAccess);
    static void SetOnKeyEventCallback(std::function<void(KeyEventInfo& keyEventInfo)>&& onKeyEventId);
    static void SetOnInterceptRequest(
        std::function<RefPtr<WebResponse>(const std::shared_ptr<BaseEventInfo>& info)>&& onInterceptRequestImpl);
    static void SetOnUrlLoadIntercept(OnWebSyncFunc&& onUrlLoadInterceptImpl);
    static void SetOnFileSelectorShow(OnWebSyncFunc&& onFileSelectorShowImpl);
    static void SetOnContextMenuShow(OnWebSyncFunc&& onContextMenuImpl);
    static void SetFileAccessEnabled(bool isFileAccessEnabled);
    static void SetOnLineImageAccessEnabled(bool isOnLineImageAccessEnabled);
    static void SetDomStorageAccessEnabled(bool isDomStorageAccessEnabled);
    static void SetImageAccessEnabled(bool isImageAccessEnabled);
    static void SetMixedMode(MixedModeContent mixedContentMode);
    static void SetZoomAccessEnabled(bool isZoomAccessEnabled);
    static void SetGeolocationAccessEnabled(bool isGeolocationAccessEnabled);
    static void SetUserAgent(const std::string& userAgent);
    static void SetRenderExitedId(OnWebAsyncFunc&& renderExitedId);
    static void SetRefreshAccessedHistoryId(OnWebAsyncFunc&& refreshAccessedHistoryId);
    static void SetCacheMode(WebCacheMode mode);
    static void SetOverviewModeAccessEnabled(bool isOverviewModeAccessEnabled);
    static void SetFileFromUrlAccessEnabled(bool isFileFromUrlAccessEnabled);
    static void SetDatabaseAccessEnabled(bool isDatabaseAccessEnabled);
    static void SetTextZoomRatio(int32_t textZoomRatioNum);
    static void SetWebDebuggingAccessEnabled(bool isWebDebuggingAccessEnabled);
    static void SetOnMouseEventCallback(std::function<void(MouseInfo& info)>&& onMouseId);
    static void SetResourceLoadId(OnWebAsyncFunc&& resourceLoadId);
    static void SetScaleChangeId(OnWebAsyncFunc&& scaleChangeId);
    static void SetScrollId(OnWebAsyncFunc&& scrollId);
    static void SetPermissionRequestEventId(OnWebAsyncFunc&& permissionRequestEventId);
    static void SetBackgroundColor(int32_t backgroundColor);
    static void SetInitialScale(float scale);
    static void SetSearchResultReceiveEventId(OnWebAsyncFunc&& searchResultReceiveEventId);
    static void SetOnDragStartId(const OnDragFunc& onDragStartId);
    static void SetOnDragEnterId(const OnDropFunc& onDragEnterId);
    static void SetOnDragMoveId(const OnDropFunc& onDragMoveId);
    static void SetOnDragLeaveId(const OnDropFunc& onDragLeaveId);
    static void SetOnDropId(const OnDropFunc& onDropId);
    static void SetPinchSmoothModeEnabled(bool isPinchSmoothModeEnabled);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WEB_WEB_VIEW_H
