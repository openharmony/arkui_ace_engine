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

typedef std::function<void(
    const Callback_OnPageEndEvent_Void*,
    WeakPtr<FrameNode>, int32_t, const BaseEventInfo*)> OnPageEndEvent;

typedef std::function<void(
    const Callback_OnPageBeginEvent_Void*,
    WeakPtr<FrameNode>, int32_t, const BaseEventInfo*)> OnPageBeginEvent;

typedef std::function<void(
    const Callback_OnProgressChangeEvent_Void*,
    WeakPtr<FrameNode>, int32_t, const BaseEventInfo*)> OnProgressChangeEvent;

typedef std::function<void(
    const Callback_OnTitleReceiveEvent_Void*,
    WeakPtr<FrameNode>, int32_t, const BaseEventInfo*)> OnTitleReceiveEvent;

typedef std::function<void(
    const Callback_Void*,
    WeakPtr<FrameNode>, int32_t, const BaseEventInfo*)> OnGeolocationHideEvent;

typedef std::function<void(
    const Callback_OnGeolocationShowEvent_Void*,
    WeakPtr<FrameNode>, int32_t, const BaseEventInfo*)> OnGeolocationShowEvent;

typedef std::function<void(
    const Callback_Void*,
    WeakPtr<FrameNode>, const BaseEventInfo*)> OnRequestSelectedEvent;

typedef std::function<bool(
    const Callback_OnAlertEvent_Boolean*,
    WeakPtr<FrameNode>, int32_t, const BaseEventInfo*)> OnAlertEvent;

typedef std::function<bool(
    const Callback_OnBeforeUnloadEvent_Boolean*,
    WeakPtr<FrameNode>, int32_t, const BaseEventInfo*)> OnBeforeUnloadEvent;

typedef std::function<bool(
    const Callback_OnConfirmEvent_Boolean*,
    WeakPtr<FrameNode>, int32_t, const BaseEventInfo*)> OnConfirmEvent;

typedef std::function<bool(
    const Callback_OnPromptEvent_Boolean*,
    WeakPtr<FrameNode>, int32_t, const BaseEventInfo*)> OnPromptEvent;

typedef std::function<bool(
    const Callback_OnConsoleEvent_Boolean*,
    WeakPtr<FrameNode>, const BaseEventInfo*)> OnConsoleEvent;

typedef std::function<void(
    const Callback_OnErrorReceiveEvent_Void*,
    WeakPtr<FrameNode>, int32_t, const BaseEventInfo*)> OnErrorReceiveEvent;

typedef std::function<void(
    const Callback_OnHttpErrorReceiveEvent_Void*,
    WeakPtr<FrameNode>, int32_t, const BaseEventInfo*)> OnHttpErrorReceiveEvent;

typedef std::function<void(
    const Callback_OnDownloadStartEvent_Void*,
    WeakPtr<FrameNode>, int32_t, const BaseEventInfo*)> OnDownloadStartEvent;

typedef std::function<void(
    const Callback_OnRefreshAccessedHistoryEvent_Void*,
    WeakPtr<FrameNode>, int32_t, const BaseEventInfo*)> OnRefreshAccessedHistoryEvent;

typedef std::function<bool(
    const Type_WebAttribute_onUrlLoadIntercept_callback*,
    WeakPtr<FrameNode>, int32_t, const BaseEventInfo*)> OnUrlLoadInterceptEvent;

typedef std::function<void(
    const Callback_OnRenderExitedEvent_Void*,
    WeakPtr<FrameNode>, int32_t, const BaseEventInfo*)> OnRenderExitedEvent;

typedef std::function<bool(
    const Callback_OnShowFileSelectorEvent_Boolean*,
    WeakPtr<FrameNode>, int32_t, const BaseEventInfo*)> OnShowFileSelectorEvent;

typedef std::function<void(
    const Callback_OnResourceLoadEvent_Void*,
    WeakPtr<FrameNode>, int32_t, const BaseEventInfo*)> OnResourceLoadEvent;

typedef std::function<void(
    const Callback_Void*,
    WeakPtr<FrameNode>, int32_t, const BaseEventInfo*)> OnFullScreenExitEvent;

typedef std::function<void(
    const OnFullScreenEnterCallback*,
    WeakPtr<FrameNode>, int32_t, const BaseEventInfo*)> OnFullScreenEnterEvent;

typedef std::function<void(
    const Callback_OnScaleChangeEvent_Void*,
    WeakPtr<FrameNode>, int32_t, const BaseEventInfo*)> OnScaleChangeEvent;

typedef std::function<bool(
    const Callback_OnHttpAuthRequestEvent_Boolean*,
    WeakPtr<FrameNode>, int32_t, const BaseEventInfo*)> OnHttpAuthRequestEvent;

typedef std::function<RefPtr<WebResponse>(
    const Callback_OnInterceptRequestEvent_WebResourceResponse*,
    WeakPtr<FrameNode>, int32_t, const BaseEventInfo*)> OnInterceptRequest;

typedef std::function<void(
    const Callback_OnPermissionRequestEvent_Void*,
    WeakPtr<FrameNode>, int32_t, const BaseEventInfo*)> OnPermissionRequestEvent;

typedef std::function<void(
    const Callback_OnScreenCaptureRequestEvent_Void*,
    WeakPtr<FrameNode>, int32_t, const BaseEventInfo*)> OnScreenCaptureRequestEvent;

typedef std::function<bool(
    const Callback_OnContextMenuShowEvent_Boolean*,
    WeakPtr<FrameNode>, int32_t, const BaseEventInfo*)> OnContextMenuShowEvent;

typedef std::function<void(
    const OnContextMenuHideCallback*,
    WeakPtr<FrameNode>, int32_t, const BaseEventInfo*)> OnContextMenuHideEvent;

typedef std::function<void(
    const Callback_OnSearchResultReceiveEvent_Void*,
    WeakPtr<FrameNode>, int32_t, const BaseEventInfo*)> OnSearchResultReceiveEvent;

typedef std::function<void(
    const Callback_OnScrollEvent_Void*,
    WeakPtr<FrameNode>, int32_t, const BaseEventInfo*)> OnScrollEvent;

typedef std::function<bool(
    const Callback_OnSslErrorEventReceiveEvent_Void*,
    WeakPtr<FrameNode>, int32_t, const BaseEventInfo*)> OnSslErrorEventReceiveEvent;

typedef std::function<bool(
    const OnSslErrorEventCallback*,
    WeakPtr<FrameNode>, int32_t, const BaseEventInfo*)> OnSslErrorEvent;

typedef std::function<bool(
    const Callback_OnClientAuthenticationEvent_Void*,
    WeakPtr<FrameNode>, int32_t, const BaseEventInfo*)> OnClientAuthenticationEvent;

typedef std::function<void(
    const Callback_OnWindowNewEvent_Void*,
    WeakPtr<FrameNode>, int32_t, const std::shared_ptr<BaseEventInfo>&)> OnWindowNewEvent;

typedef std::function<void(
    const Callback_Void*,
    WeakPtr<FrameNode>, int32_t, const BaseEventInfo*)> OnWindowExitEvent;

typedef std::function<bool(
    const Callback_KeyEvent_Boolean*,
    WeakPtr<FrameNode>, KeyEventInfo&)> OnKeyEvent;

typedef std::function<void(
    const Callback_OnTouchIconUrlReceivedEvent_Void*,
    WeakPtr<FrameNode>, int32_t, const std::shared_ptr<BaseEventInfo>&)> OnTouchIconUrlReceivedEvent;

typedef std::function<void(
    const Callback_OnFaviconReceivedEvent_Void*,
    WeakPtr<FrameNode>, int32_t, const std::shared_ptr<BaseEventInfo>&)> OnFaviconReceivedEvent;

typedef std::function<void(
    const Callback_OnPageVisibleEvent_Void*,
    WeakPtr<FrameNode>, int32_t, const std::shared_ptr<BaseEventInfo>&)> OnPageVisibleEvent;

typedef std::function<void(
    const Callback_OnDataResubmittedEvent_Void*,
    WeakPtr<FrameNode>, int32_t, const std::shared_ptr<BaseEventInfo>&)> OnDataResubmittedEvent;

extern OnPageEndEvent g_onPageEnd;
extern OnPageBeginEvent g_onPageBegin;
extern OnProgressChangeEvent g_onProgressChange;
extern OnTitleReceiveEvent g_onTitleReceive;
extern OnGeolocationHideEvent g_onGeolocationHide;
extern OnGeolocationShowEvent g_onGeolocationShow;
extern OnRequestSelectedEvent g_onRequestSelected;
extern OnAlertEvent g_onAlert;
extern OnBeforeUnloadEvent g_onBeforeUnload;
extern OnConfirmEvent g_onConfirm;
extern OnPromptEvent g_onPrompt;
extern OnConsoleEvent g_onConsole;
extern OnErrorReceiveEvent g_onErrorReceive;
extern OnHttpErrorReceiveEvent g_onHttpErrorReceive;
extern OnDownloadStartEvent g_onDownloadStart;
extern OnRefreshAccessedHistoryEvent g_onRefreshAccessedHistory;
extern OnUrlLoadInterceptEvent g_onUrlLoadIntercept;
extern OnRenderExitedEvent g_onRenderExited;
extern OnShowFileSelectorEvent g_onShowFileSelector;
extern OnResourceLoadEvent g_onResourceLoad;
extern OnFullScreenExitEvent g_onFullScreenExit;
extern OnFullScreenEnterEvent g_onFullScreenEnter;
extern OnScaleChangeEvent g_onScaleChange;
extern OnHttpAuthRequestEvent g_onHttpAuthRequest;
extern OnInterceptRequest g_onInterceptRequest;
extern OnPermissionRequestEvent g_onPermissionRequest;
extern OnScreenCaptureRequestEvent g_onScreenCaptureRequest;
extern OnContextMenuShowEvent g_onContextMenuShow;
extern OnContextMenuHideEvent g_onContextMenuHide;
extern OnSearchResultReceiveEvent g_onSearchResultReceive;
extern OnScrollEvent g_onScroll;
extern OnSslErrorEventReceiveEvent g_onSslErrorEventReceive;
extern OnSslErrorEvent g_onSslErrorEvent;
extern OnClientAuthenticationEvent g_onClientAuthenticationRequest;
extern OnWindowNewEvent g_onWindowNew;
extern OnWindowExitEvent g_onWindowExit;
extern OnKeyEvent g_onInterceptKeyEvent;
extern OnTouchIconUrlReceivedEvent g_onTouchIconUrlReceived;
extern OnFaviconReceivedEvent g_onFaviconReceived;
extern OnPageVisibleEvent g_onPageVisible;
extern OnDataResubmittedEvent g_onDataResubmitted;

} // namespace OHOS::Ace::NG::GeneratedModifier::WebAttributeModifier
#endif // WEB_SUPPORTED

#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_WEB_MODIFIER_CALLBACKS_H
