/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WEB_ANI_WEB_MODEL_STATIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WEB_ANI_WEB_MODEL_STATIC_H

#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/web/web_model.h"
#include "core/components_ng/pattern/web/web_model_ng.h"
#include "core/components/web/web_property.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT WebModelStatic : public OHOS::Ace::WebModel {
public:
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static void SetPopup(FrameNode* frameNode, bool isPopup, int32_t parentWebId);
    static void SetWebIdCallback(FrameNode* frameNode, std::function<void(int32_t)>&& webIdCallback);
    static void SetHapPathCallback(FrameNode* frameNode, std::function<void(const std::string&)>&& hapPathCallback);
    static void SetWebSrc(FrameNode* frameNode, const std::optional<std::string>& webSrc);
    static void SetRenderMode(FrameNode* frameNode, const std::optional<RenderMode>& renderMode);
    static void SetIncognitoMode(FrameNode* frameNode, const std::optional<bool>& incognitoMode);
    static void SetSharedRenderProcessToken(FrameNode* frameNode,
        const std::optional<std::string>& sharedRenderProcessToken);
    static void SetWebController(FrameNode* frameNode, const RefPtr<WebController>& webController);
    static void SetOnLineImageAccessEnabled(FrameNode* frameNode, bool isOnLineImageAccessEnabled);
    static void SetImageAccessEnabled(FrameNode* frameNode, bool isImageAccessEnabled);
    static void SetGeolocationAccessEnabled(FrameNode* frameNode, bool isGeolocationAccessEnabled);
    static void SetForceDarkAccess(FrameNode* frameNode, bool access);
    static void SetOverviewModeAccessEnabled(FrameNode* frameNode, bool isOverviewModeAccessEnabled);
    static void SetDatabaseAccessEnabled(FrameNode* frameNode, bool isDatabaseAccessEnabled);
    static void SetMetaViewport(FrameNode* frameNode, bool enabled);
    static void SetMediaPlayGestureAccess(FrameNode* frameNode, bool isNeedGestureAccess);
    static void SetOverlayScrollbarEnabled(FrameNode* frameNode, bool isEnabled);
    static void SetBlockNetwork(FrameNode* frameNode, bool isNetworkBlocked);
    static void SetHorizontalScrollBarAccessEnabled(FrameNode* frameNode, bool isHorizontalScrollBarAccessEnabled);
    static void SetVerticalScrollBarAccessEnabled(FrameNode* frameNode, bool isVerticalScrollBarAccessEnabled);
    static void SetPinchSmoothModeEnabled(FrameNode* frameNode, bool isPinchSmoothModeEnabled);
    static void SetNativeEmbedModeEnabled(FrameNode* frameNode, bool isEmbedModeEnabled);
    static void SetTextAutosizing(FrameNode* frameNode, bool isTextAutosizing);
    static void SetEnabledHapticFeedback(FrameNode* frameNode, bool isEnabled);
    static void SetOptimizeParserBudgetEnabled(FrameNode *frameNode, const std::optional<bool>& enable);
    static void SetEnableFollowSystemFontWeight(FrameNode *frameNode,
        const std::optional<bool>& enableFollowSystemFontWeight);
    static void SetWebMediaAVSessionEnabled(FrameNode *frameNode, const std::optional<bool>& enable);
    static void JavaScriptOnDocumentStart(FrameNode* frameNode, const ScriptItems& scriptItems);
    static void JavaScriptOnDocumentEnd(FrameNode* frameNode, const ScriptItems& scriptItems);
    static void JavaScriptOnHeadEnd(FrameNode *frameNode, const ScriptItems& scriptItems);
    static void SetNativeEmbedOptions(FrameNode *frameNode, bool supportDefaultIntrinsicSize);
    static void SetMixedMode(FrameNode* frameNode, const std::optional<MixedModeContent>& mixedMode);
    static void SetCacheMode(FrameNode* frameNode, const std::optional<WebCacheMode>& cacheMode);
    static void SetDarkMode(FrameNode* frameNode, const std::optional<WebDarkMode>& mode);
    static void SetOverScrollMode(FrameNode* frameNode, const std::optional<OverScrollMode>& mode);
    static void SetLayoutMode(FrameNode* frameNode, const std::optional<WebLayoutMode>& mode);
    static void SetCopyOptionMode(FrameNode* frameNode, const std::optional<CopyOptions>& mode);
    static void SetKeyboardAvoidMode(FrameNode* frameNode, const std::optional<WebKeyboardAvoidMode>& mode);
    static void SetAudioResumeInterval(FrameNode* frameNode, const std::optional<int32_t>& resumeInterval);
    static void SetAudioExclusive(FrameNode* frameNode, const std::optional<bool>& audioExclusive);
    static void SetBlurOnKeyboardHideMode(FrameNode* frameNode, const std::optional<BlurOnKeyboardHideMode>& mode);
    static void SetTextZoomRatio(FrameNode* frameNode, int32_t textZoomRatioNum);
    static void InitialScale(FrameNode* frameNode, float scale);
    static void SetUserAgent(FrameNode* frameNode, const std::string& userAgent);
    static void SetWebStandardFont(FrameNode* frameNode, const std::string& standardFontFamily);
    static void SetWebSerifFont(FrameNode* frameNode, const std::string& serifFontFamily);
    static void SetWebSansSerifFont(FrameNode* frameNode, const std::string& sansSerifFontFamily);
    static void SetWebFixedFont(FrameNode* frameNode, const std::string& fixedFontFamily);
    static void SetWebFantasyFont(FrameNode* frameNode, const std::string& fixedFontFamily);
    static void SetWebCursiveFont(FrameNode* frameNode, const std::string& cursiveFontFamily);
    static void SetDefaultFixedFontSize(FrameNode* frameNode, int32_t defaultFixedFontSize);
    static void SetDefaultFontSize(FrameNode* frameNode, int32_t defaultFontSize);
    static void SetMinFontSize(FrameNode* frameNode, int32_t minFontSize);
    static void SetMinLogicalFontSize(FrameNode* frameNode, int32_t minLogicalFontSize);
    static void SetDefaultTextEncodingFormat(FrameNode* frameNode, const std::string& textEncodingFormat);
    static void RegisterNativeEmbedRule(FrameNode* frameNode, const std::string& tag, const std::string& type);
    static void SetNativeVideoPlayerConfig(FrameNode* frameNode, bool enable, bool shouldOverlay);
    static void SetNestedScrollExt(FrameNode* frameNode, const std::optional<NestedScrollOptionsExt>& nestedOpt);
    static void SetSelectionMenuOptions(FrameNode* frameNode, const WebMenuOptionsParam& webMenuOption);
    static void SetEditMenuOptions(FrameNode* frameNode, const NG::OnCreateMenuCallback&& onCreateMenuCallback,
        const NG::OnMenuItemClickCallback&& onMenuItemClick);
    static void SetNewDragStyle(FrameNode* frameNode, bool isNewDragStyle);
    static void SetPreviewSelectionMenu(
        FrameNode* frameNode, const std::shared_ptr<WebPreviewSelectionMenuParam>& param);
    static void SetOnPageFinish(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback);
    static void SetOnPageStart(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback);
    static void SetOnProgressChange(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback);
    static void SetOnTitleReceive(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback);
    static void SetOnGeolocationHide(
        FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback);
    static void SetOnGeolocationShow(
        FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback);
    static void SetOnRequestFocus(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback);
    static void SetOnCommonDialog(
        FrameNode* frameNode, std::function<bool(const BaseEventInfo* info)>&& callback, int dialogEventType);
    static void SetOnConsoleLog(FrameNode* frameNode, std::function<bool(const BaseEventInfo* info)>&& callback);
    static void SetOnErrorReceive(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback);
    static void SetOnHttpErrorReceive(
        FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback);
    static void SetOnDownloadStart(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback);
    static void SetRefreshAccessedHistoryId(
        FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback);
    static void SetOnUrlLoadIntercept(
        FrameNode* frameNode, std::function<bool(const BaseEventInfo* info)>&& callback);
    static void SetRenderExitedId(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback);
    static void SetOnFileSelectorShow(
        FrameNode* frameNode, std::function<bool(const BaseEventInfo* info)>&& callback);
    static void SetResourceLoadId(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback);
    static void SetOnFullScreenExit(
        FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback);
    static void SetOnFullScreenEnter(
        FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback);
    static void SetScaleChangeId(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback);
    static void SetOnHttpAuthRequest(
        FrameNode* frameNode, std::function<bool(const BaseEventInfo* info)>&& callback);
    static void SetOnInterceptRequest(
        FrameNode* frameNode, std::function<RefPtr<WebResponse>(const BaseEventInfo* info)>&& callback);
    static void SetPermissionRequestEventId(
        FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback);
    static void SetScreenCaptureRequestEventId(
        FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback);
    static void SetOnContextMenuShow(
        FrameNode* frameNode, std::function<bool(const BaseEventInfo* info)>&& callback);
    static void SetOnContextMenuHide(
        FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback);
    static void SetSearchResultReceiveEventId(
        FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback);
    static void SetScrollId(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback);
    static void SetOnSslErrorRequest(
        FrameNode* frameNode, std::function<bool(const BaseEventInfo* info)>&& callback);
    static void SetOnAllSslErrorRequest(
        FrameNode* frameNode, std::function<bool(const BaseEventInfo* info)>&& callback);
    static void SetOnSslSelectCertRequest(
        FrameNode* frameNode, std::function<bool(const BaseEventInfo* info)>&& callback);
    static void SetWindowNewEvent(
        FrameNode* frameNode, std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& callback);
    static void SetWindowExitEventId(
        FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback);
    static void SetOnInterceptKeyEventCallback(
        FrameNode* frameNode, std::function<bool(KeyEventInfo& keyEventInfo)>&& keyEventInfo);
    static void SetTouchIconUrlId(
        FrameNode* frameNode, std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& touchIconUrlId);
    static void SetFaviconReceivedId(
        FrameNode* frameNode, std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& faviconReceivedId);
    static void SetPageVisibleId(
        FrameNode* frameNode, std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& pageVisibleId);
    static void SetOnDataResubmitted(
        FrameNode* frameNode, std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& dataResubmittedId);
    static void SetAudioStateChangedId(
        FrameNode* frameNode, std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& audioStateChanged);
    static void SetFirstContentfulPaintId(FrameNode* frameNode,
        std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& firstContentfulPaintId);
    static void SetFirstMeaningfulPaintId(FrameNode* frameNode,
        std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& firstMeaningfulPaintId);
    static void SetLargestContentfulPaintId(FrameNode* frameNode,
        std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& largestContentfulPaintId);
    static void SetOnLoadIntercept(FrameNode* frameNode, std::function<bool(const BaseEventInfo* info)>&& callback);
    static void SetOnControllerAttached(FrameNode* frameNode, std::function<void()>&& callback);
    static void SetOverScrollId(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback);
    static void SetSafeBrowsingCheckResultId(FrameNode* frameNode,
        std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& safeBrowsingCheckResultId);
    static void SetNavigationEntryCommittedId(FrameNode* frameNode,
        std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& navigationEntryCommittedId);
    static void SetIntelligentTrackingPreventionResultId(FrameNode* frameNode,
        std::function<void(const std::shared_ptr<BaseEventInfo>& info)>&& intelligentTrackingPreventionResultId);
    static void SetNativeEmbedLifecycleChangeId(
        FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback);
    static void SetNativeEmbedVisibilityChangeId(
        FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback);
    static void SetNativeEmbedGestureEventId(
        FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback);
    static void SetOnOverrideUrlLoading(
        FrameNode* frameNode, std::function<bool(const BaseEventInfo* info)>&& callback);
    static void SetRenderProcessNotRespondingId(
        FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback);
    static void SetRenderProcessRespondingId(
        FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback);
    static void SetViewportFitChangedId(
        FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback);
    static void SetOnInterceptKeyboardAttach(
        FrameNode* frameNode, std::function<WebKeyboardOption(const BaseEventInfo* info)>&& callback);
    static void SetAdsBlockedEventId(
        FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& callback);
    static void NotifyPopupWindowResultStatic(int32_t webId, bool result);
    static void SetJsEnabled(FrameNode* frameNode, bool isJsEnabled);
    static void SetFileAccessEnabled(FrameNode* frameNode, bool isFileAccessEnabled);
    static void SetDomStorageAccessEnabled(FrameNode* frameNode, bool isDomStorageAccessEnabled);
    static void SetZoomAccessEnabled(FrameNode* frameNode, bool isZoomAccessEnabled);
    static void SetMultiWindowAccessEnabled(FrameNode* frameNode, bool isMultiWindowAccessEnable);
    static void SetAllowWindowOpenMethod(FrameNode* frameNode, bool isAllowWindowOpenMethod);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WEB_ANI_WEB_MODEL_STATIC_H
