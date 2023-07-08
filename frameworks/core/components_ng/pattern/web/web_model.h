/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WEB_WEB_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WEB_WEB_MODEL_H

#include <mutex>

#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components/web/web_property.h"

namespace OHOS::Ace {
class WebModel {
public:
    static WebModel* GetInstance();
    virtual ~WebModel() = default;

    virtual void Create(const std::string& src, const RefPtr<WebController>& webController) = 0;
    virtual void Create(const std::string& src, std::function<void(int32_t)>&& setWebIdCallback,
        std::function<void(const std::string&)>&& setHapPathCallback, int32_t parentWebId, bool popup) = 0;
    virtual void SetCustomScheme(const std::string& cmdLine) = 0;
    virtual void SetFocusable(bool focusable) {};
    virtual void SetFocusNode(bool isFocusNode) {};
    virtual void SetOnCommonDialog(
        std::function<bool(const BaseEventInfo* info)>&& jsCallback, int dialogEventType) = 0;
    virtual void SetOnConsoleLog(std::function<bool(const BaseEventInfo* info)>&& jsCallback) = 0;
    virtual void SetOnPageStart(std::function<void(const BaseEventInfo* info)>&& jsCallback) = 0;
    virtual void SetOnPageFinish(std::function<void(const BaseEventInfo* info)>&& jsCallback) = 0;
    virtual void SetOnProgressChange(std::function<void(const BaseEventInfo* info)>&& jsCallback) = 0;
    virtual void SetOnTitleReceive(std::function<void(const BaseEventInfo* info)>&& jsCallback) = 0;
    virtual void SetOnFullScreenExit(std::function<void(const BaseEventInfo* info)>&& jsCallback) = 0;
    virtual void SetOnFullScreenEnter(std::function<void(const BaseEventInfo* info)>&& jsCallback) = 0;
    virtual void SetOnGeolocationHide(std::function<void(const BaseEventInfo* info)>&& jsCallback) = 0;
    virtual void SetOnGeolocationShow(std::function<void(const BaseEventInfo* info)>&& jsCallback) = 0;
    virtual void SetOnRequestFocus(std::function<void(const BaseEventInfo* info)>&& jsCallback) = 0;
    virtual void SetOnDownloadStart(std::function<void(const BaseEventInfo* info)>&& jsCallback) = 0;
    virtual void SetOnHttpAuthRequest(std::function<bool(const BaseEventInfo* info)>&& jsCallback) = 0;
    virtual void SetOnSslErrorRequest(std::function<bool(const BaseEventInfo* info)>&& jsCallback) = 0;
    virtual void SetOnSslSelectCertRequest(std::function<bool(const BaseEventInfo* info)>&& jsCallback) = 0;
    virtual void SetMediaPlayGestureAccess(bool isNeedGestureAccess) = 0;
    virtual void SetOnKeyEvent(std::function<void(KeyEventInfo& keyEventInfo)>&& jsCallback) = 0;
    virtual void SetOnErrorReceive(std::function<void(const BaseEventInfo* info)>&& jsCallback) = 0;
    virtual void SetOnHttpErrorReceive(std::function<void(const BaseEventInfo* info)>&& jsCallback) = 0;
    virtual void SetOnInterceptRequest(std::function<RefPtr<WebResponse>(const BaseEventInfo* info)>&& jsCallback) = 0;
    virtual void SetOnUrlLoadIntercept(std::function<bool(const BaseEventInfo* info)>&& jsCallback) = 0;
    virtual void SetOnLoadIntercept(std::function<bool(const BaseEventInfo* info)>&& jsCallback) = 0;
    virtual void SetOnFileSelectorShow(std::function<bool(const BaseEventInfo* info)>&& jsCallback) = 0;
    virtual void SetOnContextMenuShow(std::function<bool(const BaseEventInfo* info)>&& jsCallback) = 0;
    virtual void SetJsEnabled(bool isJsEnabled) = 0;
    virtual void SetFileAccessEnabled(bool isFileAccessEnabled) = 0;
    virtual void SetOnLineImageAccessEnabled(bool isOnLineImageAccessEnabled) = 0;
    virtual void SetDomStorageAccessEnabled(bool isDomStorageAccessEnabled) = 0;
    virtual void SetImageAccessEnabled(bool isImageAccessEnabled) = 0;
    virtual void SetMixedMode(MixedModeContent mixedMode) = 0;
    virtual void SetZoomAccessEnabled(bool isZoomAccessEnabled) = 0;
    virtual void SetGeolocationAccessEnabled(bool isGeolocationAccessEnabled) = 0;
    virtual void SetJsProxyCallback(std::function<void()>&& jsProxyCallback) = 0;
    virtual void SetUserAgent(const std::string& userAgent) = 0;
    virtual void SetRenderExitedId(std::function<void(const BaseEventInfo* info)>&& jsCallback) = 0;
    virtual void SetRefreshAccessedHistoryId(std::function<void(const BaseEventInfo* info)>&& jsCallback) = 0;
    virtual void SetCacheMode(WebCacheMode cacheMode) = 0;
    virtual void SetOverviewModeAccessEnabled(bool isOverviewModeAccessEnabled) = 0;
    virtual void SetFileFromUrlAccessEnabled(bool isFileFromUrlAccessEnabled) = 0;
    virtual void SetDatabaseAccessEnabled(bool isDatabaseAccessEnabled) = 0;
    virtual void SetTextZoomRatio(int32_t textZoomRatioNum) = 0;
    virtual void SetWebDebuggingAccessEnabled(bool isWebDebuggingAccessEnabled) = 0;
    virtual void SetOnMouseEvent(std::function<void(MouseInfo& info)>&& jsCallback) = 0;
    virtual void SetResourceLoadId(std::function<void(const BaseEventInfo* info)>&& jsCallback) = 0;
    virtual void SetScaleChangeId(std::function<void(const BaseEventInfo* info)>&& jsCallback) = 0;
    virtual void SetScrollId(std::function<void(const BaseEventInfo* info)>&& jsCallback) = 0;
    virtual void SetPermissionRequestEventId(std::function<void(const BaseEventInfo* info)>&& jsCallback) = 0;
    virtual void SetBackgroundColor(Color backgroundColor) = 0;
    virtual void InitialScale(float scale) = 0;
    virtual void SetSearchResultReceiveEventId(std::function<void(const BaseEventInfo* info)>&& jsCallback) = 0;

    virtual void SetOnDragStart(
        std::function<NG::DragDropBaseInfo(const RefPtr<OHOS::Ace::DragEvent>& info, const std::string& extraParams)>&&
            onDragStart) = 0;
    virtual void SetOnDragEnter(
        std::function<void(const RefPtr<OHOS::Ace::DragEvent>& info, const std::string& extraParams)>&&
            onDragEnter) = 0;
    virtual void SetOnDragMove(
        std::function<void(const RefPtr<DragEvent>& info, const std::string& extraParams)>&& onDragMoveId) = 0;
    virtual void SetOnDragLeave(std::function<void(const RefPtr<DragEvent>&, const std::string&)>&& onDragLeave) = 0;
    virtual void SetOnDrop(std::function<void(const RefPtr<DragEvent>&, const std::string&)>&& onDropId) = 0;
    virtual void SetPinchSmoothModeEnabled(bool isPinchSmoothModeEnabled) = 0;
    virtual void SetWindowNewEvent(std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& jsCallback) = 0;
    virtual void SetWindowExitEventId(std::function<void(const BaseEventInfo* info)>&& jsCallback) = 0;

    virtual void SetMultiWindowAccessEnabled(bool isMultiWindowAccessEnable) = 0;
    virtual void SetAllowWindowOpenMethod(bool isAllowWindowOpenMethod) = 0;
    virtual void SetWebCursiveFont(const std::string& cursiveFontFamily) {};
    virtual void SetWebFantasyFont(const std::string& fixedFontFamily) {};
    virtual void SetWebFixedFont(const std::string& fixedFontFamily) {};
    virtual void SetWebSansSerifFont(const std::string& sansSerifFontFamily) {};
    virtual void SetWebSerifFont(const std::string& serifFontFamily) {};
    virtual void SetWebStandardFont(const std::string& standardFontFamily) {};
    virtual void SetDefaultFixedFontSize(int32_t defaultFixedFontSize) {};
    virtual void SetDefaultFontSize(int32_t defaultFontSize) {};
    virtual void SetMinFontSize(int32_t minFontSize) {};
    virtual void SetMinLogicalFontSize(int32_t minLogicalFontSize) {};
    virtual void SetBlockNetwork(bool isNetworkBlocked) {};

    virtual void SetPageVisibleId(std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& pageVisibleId) {};
    virtual void SetAudioStateChangedId(
        std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& audioStateChanged) {};
    virtual void SetFirstContentfulPaintId(
        std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& firstContentfulPaintId) {};
    virtual void SetOnInterceptKeyEventCallback(std::function<bool(KeyEventInfo& keyEventInfo)>&& keyEventInfo) = 0;
    virtual void SetOnDataResubmitted(
        std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& dataResubmittedId) {};
    virtual void SetDataResubmittedId(
        std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& dataResubmittedId) {};
    virtual void SetFaviconReceivedId(
        std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& faviconReceivedId) {};
    virtual void SetTouchIconUrlId(std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& touchIconUrlId) {};

    virtual void SetDarkMode(WebDarkMode mode) {};
    virtual void SetForceDarkAccess(bool access) {};
    virtual void SetHorizontalScrollBarAccessEnabled(bool isHorizontalScrollBarAccessEnabled) {};
    virtual void SetVerticalScrollBarAccessEnabled(bool isVerticalScrollBarAccessEnabled) {};

    virtual void SetOnControllerAttached(std::function<void()>&& callback) {};
    virtual void NotifyPopupWindowResult(int32_t webId, bool result) {};
    virtual void SetAudioResumeInterval(int32_t resumeInterval) {};
    virtual void SetAudioExclusive(bool audioExclusive) {};
    virtual void SetOverScrollId(std::function<void(const BaseEventInfo* info)>&& jsCallback) = 0;

    virtual void SetScreenCaptureRequestEventId(std::function<void(const BaseEventInfo* info)>&& jsCallback) {};

private:
    static std::unique_ptr<WebModel> instance_;
    static std::mutex mutex_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WEB_WEB_MODEL_H