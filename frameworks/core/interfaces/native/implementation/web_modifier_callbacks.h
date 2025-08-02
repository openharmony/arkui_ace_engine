/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_WEB_MODIFIER_CALLBACKS_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_WEB_MODIFIER_CALLBACKS_H

#ifdef WEB_SUPPORTED
#include "core/components_ng/base/frame_node.h"
#include "core/components/web/web_event.h"
#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"
#include "core/interfaces/native/utility/callback_helper.h"

namespace OHOS::Ace::NG::GeneratedModifier::WebAttributeModifier {

void OnPageEnd(const CallbackHelper<Callback_OnPageEndEvent_Void>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
void OnPageBegin(const CallbackHelper<Callback_OnPageBeginEvent_Void>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
void OnProgressChange(const CallbackHelper<Callback_OnProgressChangeEvent_Void>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
void OnTitleReceive(const CallbackHelper<Callback_OnTitleReceiveEvent_Void>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
void OnGeolocationHide(const CallbackHelper<Callback_Void>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
void OnGeolocationShow(const CallbackHelper<Callback_OnGeolocationShowEvent_Void>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
void OnRequestSelected(const CallbackHelper<Callback_Void>& arkCallback,
    WeakPtr<FrameNode> weakNode, const BaseEventInfo* info);
bool OnAlert(const CallbackHelper<Callback_OnAlertEvent_Boolean>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
bool OnBeforeUnload(const CallbackHelper<Callback_OnBeforeUnloadEvent_Boolean>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
bool OnConfirm(const CallbackHelper<Callback_OnConfirmEvent_Boolean>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
bool OnPrompt(const CallbackHelper<Callback_OnPromptEvent_Boolean>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
bool OnConsole(const CallbackHelper<Callback_OnConsoleEvent_Boolean>& arkCallback,
    WeakPtr<FrameNode> weakNode, const BaseEventInfo* info);
void OnErrorReceive(const CallbackHelper<Callback_OnErrorReceiveEvent_Void>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
void OnHttpErrorReceive(const CallbackHelper<Callback_OnHttpErrorReceiveEvent_Void>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
void OnDownloadStart(const CallbackHelper<Callback_OnDownloadStartEvent_Void>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
void OnRefreshAccessedHistory(const CallbackHelper<Callback_OnRefreshAccessedHistoryEvent_Void>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
bool OnUrlLoadIntercept(const CallbackHelper<Type_WebAttribute_onUrlLoadIntercept_callback>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
void OnRenderExited(const CallbackHelper<Callback_OnRenderExitedEvent_Void>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
bool OnShowFileSelector(const CallbackHelper<Callback_OnShowFileSelectorEvent_Boolean>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
void OnResourceLoad(const CallbackHelper<Callback_OnResourceLoadEvent_Void>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
void OnFullScreenExit(const CallbackHelper<Callback_Void>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
void OnFullScreenEnter(const CallbackHelper<OnFullScreenEnterCallback>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
void OnScaleChange(const CallbackHelper<Callback_OnScaleChangeEvent_Void>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
bool OnHttpAuthRequest(const CallbackHelper<Callback_OnHttpAuthRequestEvent_Boolean>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
RefPtr<WebResponse> OnInterceptRequest(
    const CallbackHelper<Callback_OnInterceptRequestEvent_WebResourceResponse>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
void OnPermissionRequest(const CallbackHelper<Callback_OnPermissionRequestEvent_Void>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
void OnScreenCaptureRequest(const CallbackHelper<Callback_OnScreenCaptureRequestEvent_Void>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
bool OnContextMenuShow(const CallbackHelper<Callback_OnContextMenuShowEvent_Boolean>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
void OnContextMenuHide(const CallbackHelper<OnContextMenuHideCallback>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
void OnSearchResultReceive(const CallbackHelper<Callback_OnSearchResultReceiveEvent_Void>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
void OnScroll(const CallbackHelper<Callback_OnScrollEvent_Void>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
bool OnSslErrorEventReceive(const CallbackHelper<Callback_OnSslErrorEventReceiveEvent_Void>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
bool OnSslError(const CallbackHelper<OnSslErrorEventCallback>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
bool OnClientAuthentication(const CallbackHelper<Callback_OnClientAuthenticationEvent_Void>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
void OnWindowNew(const CallbackHelper<Callback_OnWindowNewEvent_Void>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const std::shared_ptr<BaseEventInfo>& info);
void OnWindowExit(const CallbackHelper<Callback_Void>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
bool OnInterceptKey(const CallbackHelper<Callback_KeyEvent_Boolean>& arkCallback,
    WeakPtr<FrameNode> weakNode, KeyEventInfo& keyEventInfo);
void OnTouchIconUrlReceived(const CallbackHelper<Callback_OnTouchIconUrlReceivedEvent_Void>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const std::shared_ptr<BaseEventInfo>& info);
void OnFaviconReceived(const CallbackHelper<Callback_OnFaviconReceivedEvent_Void>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const std::shared_ptr<BaseEventInfo>& info);
void OnPageVisible(const CallbackHelper<Callback_OnPageVisibleEvent_Void>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const std::shared_ptr<BaseEventInfo>& info);
void OnDataResubmitted(const CallbackHelper<Callback_OnDataResubmittedEvent_Void>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const std::shared_ptr<BaseEventInfo>& info);
void OnAudioStateChanged(const CallbackHelper<Callback_OnAudioStateChangedEvent_Void>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const std::shared_ptr<BaseEventInfo>& info);
void OnFirstContentfulPaint(const CallbackHelper<Callback_OnFirstContentfulPaintEvent_Void>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const std::shared_ptr<BaseEventInfo>& info);
void OnFirstMeaningfulPaint(const CallbackHelper<OnFirstMeaningfulPaintCallback>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const std::shared_ptr<BaseEventInfo>& info);
void OnLargestContentfulPaint(const CallbackHelper<OnLargestContentfulPaintCallback>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const std::shared_ptr<BaseEventInfo>& info);
bool OnLoadIntercept(const CallbackHelper<Callback_OnLoadInterceptEvent_Boolean>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
void OnControllerAttached(const CallbackHelper<Callback_Void>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId);
void OnOverScroll(const CallbackHelper<Callback_OnOverScrollEvent_Void>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
void OnSafeBrowsingCheckResult(const CallbackHelper<OnSafeBrowsingCheckResultCallback>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const std::shared_ptr<BaseEventInfo>& info);
void OnNavigationEntryCommitted(const CallbackHelper<OnNavigationEntryCommittedCallback>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const std::shared_ptr<BaseEventInfo>& info);
void OnIntelligentTrackingPrevention(const CallbackHelper<OnIntelligentTrackingPreventionCallback>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const std::shared_ptr<BaseEventInfo>& info);
void OnNativeEmbedDataInfo(const CallbackHelper<Callback_NativeEmbedDataInfo_Void>& arkCallback,
    int32_t instanceId, const BaseEventInfo* info);
void OnNativeEmbedVisibilityChange(const CallbackHelper<OnNativeEmbedVisibilityChangeCallback>& arkCallback,
    int32_t instanceId, const BaseEventInfo* info);
void OnNativeEmbedTouchInfo(const CallbackHelper<Callback_NativeEmbedTouchInfo_Void>& arkCallback,
    int32_t instanceId, const BaseEventInfo* info);
bool OnOverrideUrlLoading(const CallbackHelper<OnOverrideUrlLoadingCallback>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
void OnRenderProcessNotResponding(const CallbackHelper<OnRenderProcessNotRespondingCallback>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
void OnRenderProcessResponding(const CallbackHelper<OnRenderProcessRespondingCallback>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
void OnViewportFitChanged(const CallbackHelper<OnViewportFitChangedCallback>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
WebKeyboardOption OnWebKeyboard(const CallbackHelper<WebKeyboardCallback>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
void OnAdsBlocked(const CallbackHelper<OnAdsBlockedCallback>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);

} // namespace OHOS::Ace::NG::GeneratedModifier::WebAttributeModifier
#endif // WEB_SUPPORTED

#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_WEB_MODIFIER_CALLBACKS_H

