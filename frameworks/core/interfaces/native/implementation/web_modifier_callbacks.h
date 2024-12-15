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

namespace OHOS::Ace::NG::GeneratedModifier::WebAttributeModifier {

void OnPageEnd(const Callback_OnPageEndEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
void OnPageBegin(const Callback_OnPageBeginEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
void OnProgressChange(const Callback_OnProgressChangeEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
void OnTitleReceive(const Callback_OnTitleReceiveEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
void OnGeolocationHide(const Callback_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
void OnGeolocationShow(const Callback_OnGeolocationShowEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
void OnRequestSelected(const Callback_Void* value,
    WeakPtr<FrameNode> weakNode, const BaseEventInfo* info);
bool OnAlert(const Callback_OnAlertEvent_Boolean* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
bool OnBeforeUnload(const Callback_OnBeforeUnloadEvent_Boolean* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
bool OnConfirm(const Callback_OnConfirmEvent_Boolean* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
bool OnPrompt(const Callback_OnPromptEvent_Boolean* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
bool OnConsole(const Callback_OnConsoleEvent_Boolean* value,
    WeakPtr<FrameNode> weakNode, const BaseEventInfo* info);
void OnErrorReceive(const Callback_OnErrorReceiveEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
void OnHttpErrorReceive(const Callback_OnHttpErrorReceiveEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
void OnDownloadStart(const Callback_OnDownloadStartEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
void OnRefreshAccessedHistory(const Callback_OnRefreshAccessedHistoryEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
bool OnUrlLoadIntercept(const Type_WebAttribute_onUrlLoadIntercept_callback* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
void OnRenderExited(const Callback_OnRenderExitedEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
bool OnShowFileSelector(const Callback_OnShowFileSelectorEvent_Boolean* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
void OnResourceLoad(const Callback_OnResourceLoadEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
void OnFullScreenExit(const Callback_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
void OnFullScreenEnter(const OnFullScreenEnterCallback* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
void OnScaleChange(const Callback_OnScaleChangeEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
bool OnHttpAuthRequest(const Callback_OnHttpAuthRequestEvent_Boolean* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
RefPtr<WebResponse> OnInterceptRequest(const Callback_OnInterceptRequestEvent_WebResourceResponse* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
void OnPermissionRequest(const Callback_OnPermissionRequestEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
void OnScreenCaptureRequest(const Callback_OnScreenCaptureRequestEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
bool OnContextMenuShow(const Callback_OnContextMenuShowEvent_Boolean* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
void OnContextMenuHide(const OnContextMenuHideCallback* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
void OnSearchResultReceive(const Callback_OnSearchResultReceiveEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
void OnScroll(const Callback_OnScrollEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
bool OnSslErrorEventReceive(const Callback_OnSslErrorEventReceiveEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
bool OnSslError(const OnSslErrorEventCallback* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
bool OnClientAuthentication(const Callback_OnClientAuthenticationEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
void OnWindowNew(const Callback_OnWindowNewEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const std::shared_ptr<BaseEventInfo>& info);
void OnWindowExit(const Callback_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
bool OnInterceptKey(const Callback_KeyEvent_Boolean* value,
    WeakPtr<FrameNode> weakNode, KeyEventInfo& keyEventInfo);
void OnTouchIconUrlReceived(const Callback_OnTouchIconUrlReceivedEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const std::shared_ptr<BaseEventInfo>& info);
void OnFaviconReceived(const Callback_OnFaviconReceivedEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const std::shared_ptr<BaseEventInfo>& info);
void OnPageVisible(const Callback_OnPageVisibleEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const std::shared_ptr<BaseEventInfo>& info);
void OnDataResubmitted(const Callback_OnDataResubmittedEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const std::shared_ptr<BaseEventInfo>& info);
void OnAudioStateChanged(const Callback_OnAudioStateChangedEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const std::shared_ptr<BaseEventInfo>& info);
void OnFirstContentfulPaint(const Callback_OnFirstContentfulPaintEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const std::shared_ptr<BaseEventInfo>& info);
void OnFirstMeaningfulPaint(const OnFirstMeaningfulPaintCallback* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const std::shared_ptr<BaseEventInfo>& info);
void OnLargestContentfulPaint(const OnLargestContentfulPaintCallback* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const std::shared_ptr<BaseEventInfo>& info);
bool OnLoadIntercept(const Callback_OnLoadInterceptEvent_Boolean* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
void OnControllerAttached(const Callback_Void* value, WeakPtr<FrameNode> weakNode, int32_t instanceId);
void OnOverScroll(const Callback_OnOverScrollEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
void OnSafeBrowsingCheckResult(const OnSafeBrowsingCheckResultCallback* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const std::shared_ptr<BaseEventInfo>& info);
void OnNavigationEntryCommitted(const OnNavigationEntryCommittedCallback* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const std::shared_ptr<BaseEventInfo>& info);
void OnIntelligentTrackingPrevention(const OnIntelligentTrackingPreventionCallback* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const std::shared_ptr<BaseEventInfo>& info);
void OnNativeEmbedDataInfo(const Callback_NativeEmbedDataInfo_Void* valueInfo,
    int32_t instanceId, const BaseEventInfo* info);
void OnNativeEmbedVisibilityChange(const OnNativeEmbedVisibilityChangeCallback* value,
    int32_t instanceId, const BaseEventInfo* info);
void OnNativeEmbedTouchInfo(const Callback_NativeEmbedTouchInfo_Void* value,
    int32_t instanceId, const BaseEventInfo* info);
bool OnOverrideUrlLoading(const OnOverrideUrlLoadingCallback* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
void OnRenderProcessNotResponding(const OnRenderProcessNotRespondingCallback* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
void OnRenderProcessResponding(const OnRenderProcessRespondingCallback* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
void OnViewportFitChanged(const OnViewportFitChangedCallback* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
WebKeyboardOption OnWebKeyboard(const WebKeyboardCallback* valueCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);
void OnAdsBlocked(const OnAdsBlockedCallback* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info);

} // namespace OHOS::Ace::NG::GeneratedModifier::WebAttributeModifier
#endif // WEB_SUPPORTED

#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_WEB_MODIFIER_CALLBACKS_H
