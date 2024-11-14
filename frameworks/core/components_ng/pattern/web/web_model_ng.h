/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WEB_WEB_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WEB_WEB_MODEL_NG_H

#if !defined(IOS_PLATFORM) && !defined(ANDROID_PLATFORM)
#include "base/web/webview/ohos_nweb/include/nweb_helper.h"
#endif
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/web/web_model.h"

namespace OHOS::Ace::NG {
using OnWebSyncFunc = std::function<bool(const std::shared_ptr<BaseEventInfo>& info)>;
using OnWebAsyncFunc = std::function<void(const std::shared_ptr<BaseEventInfo>& info)>;
using SetWebIdCallback = std::function<void(int32_t)>;
using SetHapPathCallback = std::function<void(const std::string&)>;
using JsProxyCallback = std::function<void()>;
using setPermissionClipboardCallback = std::function<void(const std::shared_ptr<BaseEventInfo>&)>;

class ACE_EXPORT WebModelNG : public OHOS::Ace::WebModel {
public:
    void Create(const std::string& src, const RefPtr<WebController>& webController,
        RenderMode renderMode = RenderMode::ASYNC_RENDER, bool incognitoMode = false,
        const std::string& sharedRenderProcessToken = "") override;
    void Create(const std::string& src, std::function<void(int32_t)>&& setWebIdCallback,
        std::function<void(const std::string&)>&& setHapPathCallback, int32_t parentWebId, bool popup,
        RenderMode renderMode = RenderMode::ASYNC_RENDER, bool incognitoMode = false,
        const std::string& sharedRenderProcessToken = "") override;
    Color GetDefaultBackgroundColor() override;
    void SetCustomScheme(const std::string& cmdLine) override;
    void SetOnCommonDialog(std::function<bool(const BaseEventInfo* info)>&& jsCallback, int dialogEventType) override;
    void SetOnConsoleLog(std::function<bool(const BaseEventInfo* info)>&& jsCallback) override;
    void SetOnPageStart(std::function<void(const BaseEventInfo* info)>&& jsCallback) override;
    void SetOnPageFinish(std::function<void(const BaseEventInfo* info)>&& jsCallback) override;
    void SetOnProgressChange(std::function<void(const BaseEventInfo* info)>&& jsCallback) override;
    void SetOnTitleReceive(std::function<void(const BaseEventInfo* info)>&& jsCallback) override;
    void SetOnFullScreenExit(std::function<void(const BaseEventInfo* info)>&& jsCallback) override;
    void SetOnFullScreenEnter(std::function<void(const BaseEventInfo* info)>&& jsCallback) override;
    void SetOnGeolocationHide(std::function<void(const BaseEventInfo* info)>&& jsCallback) override;
    void SetOnGeolocationShow(std::function<void(const BaseEventInfo* info)>&& jsCallback) override;
    void SetOnRequestFocus(std::function<void(const BaseEventInfo* info)>&& jsCallback) override;
    void SetOnDownloadStart(std::function<void(const BaseEventInfo* info)>&& jsCallback) override;
    void SetOnHttpAuthRequest(std::function<bool(const BaseEventInfo* info)>&& jsCallback) override;
    void SetOnSslErrorRequest(std::function<bool(const BaseEventInfo* info)>&& jsCallback) override;
    void SetOnAllSslErrorRequest(std::function<bool(const BaseEventInfo* info)>&& jsCallback) override;
    void SetOnSslSelectCertRequest(std::function<bool(const BaseEventInfo* info)>&& jsCallback) override;
    void SetMediaPlayGestureAccess(bool isNeedGestureAccess) override;
    void SetOnKeyEvent(std::function<void(KeyEventInfo& keyEventInfo)>&& jsCallback) override;
    void SetOnErrorReceive(std::function<void(const BaseEventInfo* info)>&& jsCallback) override;
    void SetOnHttpErrorReceive(std::function<void(const BaseEventInfo* info)>&& jsCallback) override;
    void SetOnInterceptRequest(std::function<RefPtr<WebResponse>(const BaseEventInfo* info)>&& jsCallback) override;
    void SetOnUrlLoadIntercept(std::function<bool(const BaseEventInfo* info)>&& jsCallback) override;
    void SetOnLoadIntercept(std::function<bool(const BaseEventInfo* info)>&& jsCallback) override;
    void SetOnOverrideUrlLoading(std::function<bool(const BaseEventInfo* info)>&& jsCallback) override;
    void SetOnFileSelectorShow(std::function<bool(const BaseEventInfo* info)>&& jsCallback) override;
    void SetOnContextMenuShow(std::function<bool(const BaseEventInfo* info)>&& jsCallback) override;
    void SetOnContextMenuHide(std::function<void(const BaseEventInfo* info)>&& jsCallback) override;
    void SetNewDragStyle(bool isNewDragStyle) override;
    void SetPreviewSelectionMenu(const std::shared_ptr<WebPreviewSelectionMenuParam>& param) override;
    void SetJsEnabled(bool isJsEnabled) override;
    void SetFileAccessEnabled(bool isFileAccessEnabled) override;
    void SetOnLineImageAccessEnabled(bool isOnLineImageAccessEnabled) override;
    void SetDomStorageAccessEnabled(bool isDomStorageAccessEnabled) override;
    void SetImageAccessEnabled(bool isImageAccessEnabled) override;
    void SetMixedMode(MixedModeContent mixedMode) override;
    void SetZoomAccessEnabled(bool isZoomAccessEnabled) override;
    void SetGeolocationAccessEnabled(bool isGeolocationAccessEnabled) override;
    void SetJsProxyCallback(std::function<void()>&& jsProxyCallback) override;
    void SetUserAgent(const std::string& userAgent) override;
    void SetRenderExitedId(std::function<void(const BaseEventInfo* info)>&& jsCallback) override;
    void SetRefreshAccessedHistoryId(std::function<void(const BaseEventInfo* info)>&& jsCallback) override;
    void SetCacheMode(WebCacheMode cacheMode) override;
    void SetOverScrollMode(OverScrollMode mode) override;
    void SetBlurOnKeyboardHideMode(BlurOnKeyboardHideMode mode) override;
    void SetCopyOptionMode(CopyOptions mode) override;
    void SetOverviewModeAccessEnabled(bool isOverviewModeAccessEnabled) override;
    void SetFileFromUrlAccessEnabled(bool isFileFromUrlAccessEnabled) override;
    void SetDatabaseAccessEnabled(bool isDatabaseAccessEnabled) override;
    void SetTextZoomRatio(int32_t textZoomRatioNum) override;
    void SetOnMouseEvent(std::function<void(MouseInfo& info)>&& jsCallback) override;
    void SetResourceLoadId(std::function<void(const BaseEventInfo* info)>&& jsCallback) override;
    void SetScaleChangeId(std::function<void(const BaseEventInfo* info)>&& jsCallback) override;
    void SetScrollId(std::function<void(const BaseEventInfo* info)>&& jsCallback) override;
    void SetPermissionRequestEventId(std::function<void(const BaseEventInfo* info)>&& jsCallback) override;
    void SetScreenCaptureRequestEventId(std::function<void(const BaseEventInfo* info)>&& jsCallback) override;
    void SetBackgroundColor(Color backgroundColor) override;
    void InitialScale(float scale) override;
    void SetSearchResultReceiveEventId(std::function<void(const BaseEventInfo* info)>&& jsCallback) override;
    void SetWebDebuggingAccessEnabled(bool isWebDebuggingAccessEnabled) override;

    void SetOnDragStart(
        std::function<NG::DragDropBaseInfo(const RefPtr<OHOS::Ace::DragEvent>& info, const std::string& extraParams)>&&
            onDragStart) override;
    void SetOnDragEnter(
        std::function<void(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)>&& onDragEnter) override;
    void SetOnDragMove(
        std::function<void(const RefPtr<OHOS::Ace::DragEvent>& info, const std::string& extraParams)>&& onDragMoveId)
        override;
    void SetOnDragLeave(
        std::function<void(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)>&& onDragLeave) override;
    void SetOnDrop(std::function<void(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)>&& onDropId) override;
    void AddDragFrameNodeToManager();
    void SetPinchSmoothModeEnabled(bool isPinchSmoothModeEnabled) override;
    void SetWindowNewEvent(std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& jsCallback) override;
    void SetWindowExitEventId(std::function<void(const BaseEventInfo* info)>&& jsCallback) override;

    void SetMultiWindowAccessEnabled(bool isMultiWindowAccessEnable) override;
    void SetAllowWindowOpenMethod(bool isAllowWindowOpenMethod) override;
    void SetWebCursiveFont(const std::string& cursiveFontFamily) override;
    void SetWebFantasyFont(const std::string& fixedFontFamily) override;
    void SetWebFixedFont(const std::string& fixedFontFamily) override;
    void SetWebSansSerifFont(const std::string& sansSerifFontFamily) override;
    void SetWebSerifFont(const std::string& serifFontFamily) override;
    void SetWebStandardFont(const std::string& standardFontFamily) override;
    void SetDefaultFixedFontSize(int32_t defaultFixedFontSize) override;
    void SetDefaultFontSize(int32_t defaultFontSize) override;
    void SetDefaultTextEncodingFormat(const std::string& textEncodingFormat) override;
    void SetMinFontSize(int32_t minFontSize) override;
    void SetMinLogicalFontSize(int32_t minLogicalFontSize) override;
    void SetBlockNetwork(bool isNetworkBlocked) override;

    void SetPageVisibleId(std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& pageVisibleId) override;
    void SetOnInterceptKeyEventCallback(std::function<bool(KeyEventInfo& keyEventInfo)>&& keyEventInfo) override;
    void SetDataResubmittedId(
        std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& dataResubmittedId) override;
    void SetOnDataResubmitted(
        std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& dataResubmittedId) override;
    void SetFaviconReceivedId(
        std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& faviconReceivedId) override;
    void SetAudioStateChangedId(
        std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& audioStateChanged) override;
    void SetFirstContentfulPaintId(
        std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& firstContentfulPaintId) override;
    void SetFirstMeaningfulPaintId(
        std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& firstMeaningfulPaintId) override;
    void SetLargestContentfulPaintId(
        std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& largestContentfulPaintId) override;
    void SetSafeBrowsingCheckResultId(
        std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& safeBrowsingCheckResultId) override;
    void SetNavigationEntryCommittedId(
        std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& navigationEntryCommittedId) override;
    void SetTouchIconUrlId(std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& touchIconUrlId) override;

    void SetDarkMode(WebDarkMode mode) override;
    void SetForceDarkAccess(bool access) override;
    void SetHorizontalScrollBarAccessEnabled(bool isHorizontalScrollBarAccessEnabled) override;
    void SetVerticalScrollBarAccessEnabled(bool isVerticalScrollBarAccessEnabled) override;

    void SetOnControllerAttached(std::function<void()>&& callback) override;
    void NotifyPopupWindowResult(int32_t webId, bool result) override;
    void SetAudioResumeInterval(int32_t resumeInterval) override;
    void SetAudioExclusive(bool audioExclusive) override;
    void SetOverScrollId(std::function<void(const BaseEventInfo* info)>&& jsCallback) override;
    void SetNativeEmbedModeEnabled(bool isEmbedModeEnabled) override;
    void RegisterNativeEmbedRule(const std::string& tag, const std::string& type) override;
    void SetNativeEmbedLifecycleChangeId(std::function<void(const BaseEventInfo* info)>&& jsCallback) override;
    void SetNativeEmbedVisibilityChangeId(std::function<void(const BaseEventInfo* info)>&& jsCallback) override;
    void SetNativeEmbedGestureEventId(std::function<void(const BaseEventInfo* info)>&& jsCallback) override;
    void SetLayoutMode(WebLayoutMode mode) override;
    void SetNestedScroll(const NestedScrollOptions& nestedOpt) override;
    void SetNestedScrollExt(const NestedScrollOptionsExt& nestedOpt) override;
    void SetMetaViewport(bool enabled) override;
    void JavaScriptOnDocumentStart(const ScriptItems& scriptItems) override;
    void JavaScriptOnDocumentEnd(const ScriptItems& scriptItems) override;

    void SetPermissionClipboard(std::function<void(const std::shared_ptr<BaseEventInfo>&)>&& jsCallback) override;
    void SetOpenAppLinkFunction(std::function<void(const std::shared_ptr<BaseEventInfo>&)>&& jsCallback) override;
    void SetDefaultFileSelectorShow(std::function<void(const std::shared_ptr<BaseEventInfo>&)>&& jsCallback) override;
    void SetIntelligentTrackingPreventionResultId(
        std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&&
            intelligentTrackingPreventionResultId) override;
    void SetTextAutosizing(bool isTextAutosizing) override;
    void SetNativeVideoPlayerConfig(bool enable, bool shouldOverlay) override;
    void SetSmoothDragResizeEnabled(bool isSmoothDragResizeEnabled) override;
    void SetRenderProcessNotRespondingId(std::function<void(const BaseEventInfo* info)>&& jsCallback) override;
    void SetRenderProcessRespondingId(std::function<void(const BaseEventInfo* info)>&& jsCallback) override;
    void SetSelectionMenuOptions(const WebMenuOptionsParam& webMenuOption) override;
    void SetViewportFitChangedId(std::function<void(const BaseEventInfo* info)>&& jsCallback) override;
    void SetOnInterceptKeyboardAttach(
        std::function<WebKeyboardOption(const BaseEventInfo* info)>&& jsCallback) override;
    void SetAdsBlockedEventId(std::function<void(const BaseEventInfo* info)>&& jsCallback) override;
    void SetUpdateInstanceIdCallback(std::function<void(int32_t)>&& callback) override;
    void SetOverlayScrollbarEnabled(bool isEnabled) override;
    void SetKeyboardAvoidMode(const WebKeyboardAvoidMode& mode) override;
    void SetEditMenuOptions(const NG::OnCreateMenuCallback&& onCreateMenuCallback,
        const NG::OnMenuItemClickCallback&& onMenuItemClick) override;
    void SetEnabledHapticFeedback(bool isEnabled) override;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WEB_WEB_MODEL_NG_H
