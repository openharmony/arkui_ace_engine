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

// enum type used for decoupe NWeb dependency, same as NWeb::ImageColorType
enum class TransImageColorType {
    // Unknown color type
    COLOR_TYPE_UNKNOWN = -1,

    // RGBA with 8 bits per pixel (32 bits total).
    COLOR_TYPE_RGBA_8888 = 0,

    // RGRA with 8 bits per pixel (32 bits total).
    COLOR_TYPE_BGRA_8888 = 1,
};

// enum type used for decoupe NWeb dependency, same as NWeb::ImageAlphaType
enum class TransImageAlphaType {
    // Unknown alpha type
    ALPHA_TYPE_UNKNOWN = -1,

    // No transparency. The alpha component is ignored.
    ALPHA_TYPE_OPAQUE = 0,

    // Transparency with pre-multiplied alpha component.
    ALPHA_TYPE_PREMULTIPLIED = 1,

    // Transparency with post-multiplied alpha component.
    ALPHA_TYPE_POSTMULTIPLIED = 2,
};

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
    void SetWebDebuggingAccessEnabledAndPort(
        bool isWebDebuggingAccessEnabled, int32_t webDebuggingPort) override;

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
    void SetActivateContentEventId(std::function<void(const BaseEventInfo* info)>&& jsCallback) override;
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
    void SetAudioSessionType(WebAudioSessionType audioSessionType) override;
    void SetOverScrollId(std::function<void(const BaseEventInfo* info)>&& jsCallback) override;
    void SetNativeEmbedModeEnabled(bool isEmbedModeEnabled) override;
    void SetIntrinsicSizeEnabled(bool isIntrinsicSizeEnabled) override;
    void RegisterNativeEmbedRule(const std::string& tag, const std::string& type) override;
    void SetNativeEmbedLifecycleChangeId(std::function<void(const BaseEventInfo* info)>&& jsCallback) override;
    void SetNativeEmbedVisibilityChangeId(std::function<void(const BaseEventInfo* info)>&& jsCallback) override;
    void SetNativeEmbedGestureEventId(std::function<void(const BaseEventInfo* info)>&& jsCallback) override;
    void SetLayoutMode(WebLayoutMode mode) override;
    void SetNestedScroll(const NestedScrollOptions& nestedOpt) override;
    void SetNestedScrollExt(const NestedScrollOptionsExt& nestedOpt) override;
    void SetMetaViewport(bool enabled) override;
    void JavaScriptOnDocumentStart(const ScriptItems& scriptItems) override;
    void JavaScriptOnDocumentStartByOrder(const ScriptItems& scriptItems,
        const ScriptItemsByOrder& scriptItemsByOrder) override;
    void JavaScriptOnDocumentEndByOrder(const ScriptItems& scriptItems,
        const ScriptItemsByOrder& scriptItemsByOrder) override;
    void JavaScriptOnHeadReadyByOrder(const ScriptItems& scriptItems,
        const ScriptItemsByOrder& scriptItemsByOrder) override;
    void JavaScriptOnDocumentEnd(const ScriptItems& scriptItems) override;

    void SetPermissionClipboard(std::function<void(const std::shared_ptr<BaseEventInfo>&)>&& jsCallback) override;
    void SetOpenAppLinkFunction(std::function<void(const std::shared_ptr<BaseEventInfo>&)>&& jsCallback) override;
    void SetDefaultFileSelectorShow(std::function<void(const std::shared_ptr<BaseEventInfo>&)>&& jsCallback) override;
    void SetIntelligentTrackingPreventionResultId(
        std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&&
            intelligentTrackingPreventionResultId) override;
    void SetTextAutosizing(bool isTextAutosizing) override;
    void SetNativeVideoPlayerConfig(bool enable, bool shouldOverlay) override;
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
    void SetOptimizeParserBudgetEnabled(bool enable) override;
    void SetWebMediaAVSessionEnabled(bool isEnabled) override;
    void SetEnableDataDetector(bool isEnabled) override;
    void SetDataDetectorConfig(const TextDetectConfig& config) override;
    void SetEnableFollowSystemFontWeight(bool enableFollowSystemFontWeight) override;
    void SetBypassVsyncCondition(WebBypassVsyncCondition condition) override;

    // static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    // static void SetWebIdCallback(FrameNode* frameNode, std::function<void(int32_t)>&& webIdCallback);
    // static void SetHapPathCallback(FrameNode* frameNode, std::function<void(const std::string&)>&& hapPathCallback);
    // static void SetWebSrc(FrameNode* frameNode, const std::optional<std::string>& webSrc);
    // static void SetRenderMode(FrameNode* frameNode, const std::optional<RenderMode>& renderMode);
    // static void SetIncognitoMode(FrameNode* frameNode, const std::optional<bool>& incognitoMode);
    // static void SetSharedRenderProcessToken(FrameNode* frameNode,
    //     const std::optional<std::string>& sharedRenderProcessToken);
    // static void SetWebController(FrameNode* frameNode, const RefPtr<WebController>& webController);
    static void SetJsEnabled(FrameNode* frameNode, bool isJsEnabled);
    static void SetFileAccessEnabled(FrameNode* frameNode, bool isFileAccessEnabled);
    // static void SetOnLineImageAccessEnabled(FrameNode* frameNode, bool isOnLineImageAccessEnabled);
    static void SetDomStorageAccessEnabled(FrameNode* frameNode, bool isDomStorageAccessEnabled);
    // static void SetImageAccessEnabled(FrameNode* frameNode, bool isImageAccessEnabled);
    static void SetMixedMode(FrameNode* frameNode, MixedModeContent mixedMode);
    static void SetZoomAccessEnabled(FrameNode* frameNode, bool isZoomAccessEnabled);
    // static void SetGeolocationAccessEnabled(FrameNode* frameNode, bool isGeolocationAccessEnabled);
    // static void SetForceDarkAccess(FrameNode* frameNode, bool access);
    // static void SetOverviewModeAccessEnabled(FrameNode* frameNode, bool isOverviewModeAccessEnabled);
    // static void SetDatabaseAccessEnabled(FrameNode* frameNode, bool isDatabaseAccessEnabled);
    // static void SetMetaViewport(FrameNode* frameNode, bool enabled);
    // static void SetMediaPlayGestureAccess(FrameNode* frameNode, bool isNeedGestureAccess);
    static void SetCacheMode(FrameNode* frameNode, WebCacheMode cacheMode);
    static void SetDarkMode(FrameNode* frameNode, WebDarkMode mode);
    static void SetMultiWindowAccessEnabled(FrameNode* frameNode, bool isMultiWindowAccessEnable);
    // static void SetOverlayScrollbarEnabled(FrameNode* frameNode, bool isEnabled);
    // static void SetBlockNetwork(FrameNode* frameNode, bool isNetworkBlocked);
    // static void SetHorizontalScrollBarAccessEnabled(FrameNode* frameNode, bool isHorizontalScrollBarAccessEnabled);
    // static void SetVerticalScrollBarAccessEnabled(FrameNode* frameNode, bool isVerticalScrollBarAccessEnabled);
    // static void SetPinchSmoothModeEnabled(FrameNode* frameNode, bool isPinchSmoothModeEnabled);
    static void SetAllowWindowOpenMethod(FrameNode* frameNode, bool isAllowWindowOpenMethod);
    static void SetKeyboardAvoidMode(FrameNode* frameNode, const WebKeyboardAvoidMode& mode);
    static void SetOnControllerAttached(FrameNode* frameNode, std::function<void()>&& callback);
    static void SetVerticalScrollBarAccessEnabled(FrameNode* frameNode, bool isVerticalScrollBarAccessEnabled);
    static void SetHorizontalScrollBarAccessEnabled(FrameNode* frameNode, bool isHorizontalScrollBarAccessEnabled);
    static void SetTextZoomRatio(FrameNode* frameNode, int32_t textZoomRatioNum);
    static void InitialScale(FrameNode* frameNode, float scale);
    static void SetOnScroll(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& jsCallback);
    static void SetOnOverScroll(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& jsCallback);
    static void SetOnScaleChange(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& jsCallback);
    static void SetOnRequestFocus(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& jsCallback);
    static void SetOnContextMenuHide(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& jsCallback);
    static void SetGeolocationAccessEnabled(FrameNode* frameNode, bool isGeolocationAccessEnabled);
    static void SetDatabaseAccessEnabled(FrameNode* frameNode, bool isDatabaseAccessEnabled);
    static void SetOnGeolocationShow(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& jsCallback);
    static void SetOverviewModeAccessEnabled(FrameNode* frameNode, bool isOverviewModeAccessEnabled);
    static void SetForceDarkAccess(FrameNode* frameNode, bool isForceDarkAccess);
    static void SetPinchSmoothModeEnabled(FrameNode* frameNode, bool isPinchSmoothModeEnabled);
    static void SetMetaViewport(FrameNode* frameNode, bool isMetaViewport);
    static void SetEnableFollowSystemFontWeight(FrameNode* frameNode, bool isEnableFollowSystemFontWeight);
    static void SetNativeEmbedModeEnabled(FrameNode* frameNode, bool isNativeEmbedModeEnabled);
    static void SetMinFontSize(FrameNode* frameNode, int32_t minFontSize);
    static void SetDefaultFontSize(FrameNode* frameNode, int32_t defaultFontSize);
    static void SetDefaultFixedFontSize(FrameNode* frameNode, int32_t defaultFixedFontSize);
    static void SetMinLogicalFontSize(FrameNode* frameNode, int32_t minLogicalFontSize);
    static void SetWebStandardFont(FrameNode* frameNode, const std::string& standardFontFamily);
    static void SetWebSerifFont(FrameNode* frameNode, const std::string& serifFontFamily);
    static void SetWebSansSerifFont(FrameNode* frameNode, const std::string& sansSerifFontFamily);
    
    static void SetWebFixedFont(FrameNode* frameNode, const std::string& fixedFontFamily);
    static void SetWebFantasyFont(FrameNode* frameNode, const std::string& fixedFontFamily);
    static void SetWebCursiveFont(FrameNode* frameNode, const std::string& cursiveFontFamily);
    static void SetLayoutMode(FrameNode* frameNode, WebLayoutMode mode);
    static void SetNativeEmbedLifecycleChangeId(
        FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& jsCallback);
    static void SetNativeEmbedGestureEventId(
        FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& jsCallback);
    static void RegisterNativeEmbedRule(FrameNode* frameNode, const std::string& tag, const std::string& type);
    static void SetIntrinsicSizeEnabled(FrameNode* frameNode, bool isIntrinsicSizeEnabled);
    static void SetFirstContentfulPaintId(
        FrameNode* frameNode, std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& firstContentfulPaintId);
    static void SetAudioStateChangedId(
        FrameNode* frameNode, std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& audioStateChanged);
    static void SetOnFullScreenExit(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& jsCallback);
    static void SetImageAccessEnabled(FrameNode* frameNode, bool isImageAccessEnabled);
    static void SetOnLineImageAccessEnabled(FrameNode* frameNode, bool isOnLineImageAccessEnabled);
    static void SetMediaPlayGestureAccess(FrameNode* frameNode, bool isNeedGestureAccess);
    static void SetAudioResumeInterval(FrameNode* frameNode, int32_t resumeInterval);
    static void SetAudioExclusive(FrameNode* frameNode, bool audioExclusive);
    static void SetOnPageFinish(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& jsCallback);
    static void SetOnPageStart(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& jsCallback);
    static void SetOnProgressChange(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& jsCallback);
    static void SetOnTitleReceive(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& jsCallback);
    static void SetOnDownloadStart(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& jsCallback);
    static void JavaScriptOnDocumentStart(FrameNode* frameNode, const ScriptItems& scriptItems);
    static void JavaScriptOnDocumentEnd(FrameNode* frameNode, const ScriptItems& scriptItems);
    static void SetCopyOptionMode(FrameNode* frameNode, CopyOptions mode);
    static void SetRenderProcessNotRespondingId(
        FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& jsCallback);
    static void SetOnPageVisible(
        FrameNode* frameNode, std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& pageVisible);
    static void SetOnRenderExited(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& jsCallback);
    static void SetBlockNetwork(FrameNode* frameNode, bool isNetworkBlocked);
    static void SetOnResourceLoad(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& jsCallback);
    static void SetOnRefreshAccessedHistory(
        FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& jsCallback);
    static void SetOnNavigationEntryCommitted(FrameNode* frameNode,
        std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& navigationEntryCommitted);
    static void SetOnSearchResultReceive(
        FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& jsCallback);
    static void SetOverScrollMode(FrameNode* frameNode, OverScrollMode mode);
    static void SetOnTouchIconUrlReceived(
        FrameNode* frameNode, std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& touchIconUrlId);
    static void SetOnRenderProcessResponding(
        FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& jsCallback);
	static void SetPermissionRequestEventId(
        FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& jsCallback);
    static void SetScreenCaptureRequestEventId(
        FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& jsCallback);
    static void SetWindowNewEvent(
        FrameNode* frameNode, std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& jsCallback);
    static void SetOnFullScreenEnter(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& jsCallback);
    static void SetWindowExitEventId(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& jsCallback);
    static void SetOnAlert(
        FrameNode* frameNode, std::function<bool(const BaseEventInfo* info)>&& jsCallback, int dialogEventType);
    static void SetOnConfirm(
        FrameNode* frameNode, std::function<bool(const BaseEventInfo* info)>&& jsCallback, int dialogEventType);
    static void SetOnPrompt(
        FrameNode* frameNode, std::function<bool(const BaseEventInfo* info)>&& jsCallback, int dialogEventType);
    static void SetOnShowFileSelector(
        FrameNode* frameNode, std::function<bool(const BaseEventInfo* info)>&& jsCallback);
    static void SetOnContextMenuShow(FrameNode* frameNode, std::function<bool(const BaseEventInfo* info)>&& jsCallback);
    static void SetOnSafeBrowsingCheckResult(FrameNode* frameNode,
        std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& safeBrowsingCheckResult);
    static void SetNestedScrollExt(FrameNode* frameNode, const NestedScrollOptionsExt& nestedOpt);
    static void SetOnInterceptKeyEvent(
        FrameNode* frameNode, std::function<bool(KeyEventInfo& keyEventInfo)>&& keyEventInfo);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WEB_WEB_MODEL_NG_H
