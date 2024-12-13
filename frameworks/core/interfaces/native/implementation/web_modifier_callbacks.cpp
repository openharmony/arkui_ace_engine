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
#ifdef WEB_SUPPORTED

#include "core/interfaces/native/implementation/web_modifier_callbacks.h"

#include "core/interfaces/native/implementation/console_message_peer_impl.h"
#include "core/interfaces/native/implementation/controller_handler_peer_impl.h"
#include "core/interfaces/native/implementation/client_authentication_handler_peer_impl.h"
#include "core/interfaces/native/implementation/data_resubmission_handler_peer_impl.h"
#include "core/interfaces/native/implementation/file_selector_param_peer_impl.h"
#include "core/interfaces/native/implementation/file_selector_result_peer_impl.h"
#include "core/interfaces/native/implementation/full_screen_exit_handler_peer_impl.h"
#include "core/interfaces/native/implementation/js_geolocation_peer_impl.h"
#include "core/interfaces/native/implementation/js_result_peer_impl.h"
#include "core/interfaces/native/implementation/http_auth_handler_peer_impl.h"
#include "core/interfaces/native/implementation/permission_request_peer_impl.h"
#include "core/interfaces/native/implementation/screen_capture_handler_peer_impl.h"
#include "core/interfaces/native/implementation/ssl_error_handler_peer_impl.h"
#include "core/interfaces/native/implementation/web_context_menu_param_peer_impl.h"
#include "core/interfaces/native/implementation/web_context_menu_result_peer_impl.h"
#include "core/interfaces/native/implementation/web_keyboard_controller_peer_impl.h"
#include "core/interfaces/native/implementation/web_resource_error_peer_impl.h"
#include "core/interfaces/native/implementation/web_resource_request_peer_impl.h"
#include "core/interfaces/native/implementation/web_resource_response_peer_impl.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG::GeneratedModifier::WebAttributeModifier {

OnPageEndEvent g_onPageEnd = [](const Callback_OnPageEndEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info) {
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<LoadWebPageFinishEvent>(info);
    Ark_OnPageEndEvent parameter;
    parameter.url = Converter::ArkValue<Ark_String>(eventInfo->GetLoadedUrl());
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(parameter);
};

OnPageBeginEvent g_onPageBegin = [](const Callback_OnPageBeginEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info) {
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<LoadWebPageStartEvent>(info);
    Ark_OnPageBeginEvent parameter;
    parameter.url = Converter::ArkValue<Ark_String>(eventInfo->GetLoadedUrl());
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(parameter);
};

OnProgressChangeEvent g_onProgressChange = [](const Callback_OnProgressChangeEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info) {
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<LoadWebProgressChangeEvent>(info);
    Ark_OnProgressChangeEvent parameter;
    parameter.newProgress = Converter::ArkValue<Ark_Number>(eventInfo->GetNewProgress());
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(parameter);
};

OnTitleReceiveEvent g_onTitleReceive = [](const Callback_OnTitleReceiveEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info) {
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<LoadWebTitleReceiveEvent>(info);
    Ark_OnTitleReceiveEvent parameter;
    parameter.title = Converter::ArkValue<Ark_String>(eventInfo->GetTitle());
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(parameter);
};

OnGeolocationHideEvent g_onGeolocationHide = [](const Callback_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info) {
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke();
};

OnGeolocationShowEvent g_onGeolocationShow = [](const Callback_OnGeolocationShowEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info) {
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<LoadWebGeolocationShowEvent>(info);
    Ark_OnGeolocationShowEvent parameter;
    parameter.origin = Converter::ArkValue<Ark_String>(eventInfo->GetOrigin());
    auto peer = new JsGeolocationPeer();
    peer->webGeolocation = eventInfo->GetWebGeolocation();
    parameter.geolocation.ptr = peer;
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(parameter);
};

OnRequestSelectedEvent g_onRequestSelected = [](const Callback_Void* value,
    WeakPtr<FrameNode> weakNode, const BaseEventInfo* info) {
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke();
};

OnAlertEvent g_onAlert = [](const Callback_OnAlertEvent_Boolean* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId,
    const BaseEventInfo* info) -> bool {
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<WebDialogEvent>(info);
    Ark_OnAlertEvent parameter;
    parameter.message = Converter::ArkValue<Ark_String>(eventInfo->GetMessage());
    parameter.url = Converter::ArkValue<Ark_String>(eventInfo->GetUrl());
    auto peer = new JsResultPeer();
    peer->result = eventInfo->GetResult();
    parameter.result.ptr = peer;
    Callback_Boolean_Void continuation;
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(parameter, continuation);
    LOGE("WebModifier::OnAlertImpl return value can be incorrect");
    return false;
};

OnBeforeUnloadEvent g_onBeforeUnload = [](const Callback_OnBeforeUnloadEvent_Boolean* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info) -> bool {
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<WebDialogEvent>(info);
    Ark_OnBeforeUnloadEvent parameter;
    parameter.message = Converter::ArkValue<Ark_String>(eventInfo->GetMessage());
    parameter.url = Converter::ArkValue<Ark_String>(eventInfo->GetUrl());
    auto peer = new JsResultPeer();
    peer->result = eventInfo->GetResult();
    parameter.result.ptr = peer;
    Callback_Boolean_Void continuation;
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(parameter, continuation);
    LOGE("WebAttributeModifier::OnBeforeUnloadImpl return value can be incorrect");
    return false;
};

OnConfirmEvent g_onConfirm = [](const Callback_OnConfirmEvent_Boolean* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info) -> bool {
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<WebDialogEvent>(info);
    Ark_OnConfirmEvent parameter;
    parameter.message = Converter::ArkValue<Ark_String>(eventInfo->GetMessage());
    parameter.url = Converter::ArkValue<Ark_String>(eventInfo->GetUrl());
    auto peer = new JsResultPeer();
    peer->result = eventInfo->GetResult();
    parameter.result.ptr = peer;
    Callback_Boolean_Void continuation;
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(parameter, continuation);
    LOGE("WebAttributeModifier::OnConfirmImpl return value can be incorrect");
    return false;
};

OnPromptEvent g_onPrompt = [](const Callback_OnPromptEvent_Boolean* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info) -> bool {
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<WebDialogEvent>(info);
    Ark_OnPromptEvent parameter;
    parameter.message = Converter::ArkValue<Ark_String>(eventInfo->GetMessage());
    parameter.url = Converter::ArkValue<Ark_String>(eventInfo->GetUrl());
    auto peer = new JsResultPeer();
    peer->result = eventInfo->GetResult();
    parameter.result.ptr = peer;
    Callback_Boolean_Void continuation;
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(parameter, continuation);
    LOGE("WebAttributeModifier::OnPromptImpl return value can be incorrect");
    return false;
};

OnConsoleEvent g_onConsole = [](const Callback_OnConsoleEvent_Boolean* value,
    WeakPtr<FrameNode> weakNode, const BaseEventInfo* info) -> bool {
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<LoadWebConsoleLogEvent>(info);
    Ark_OnConsoleEvent parameter;
    auto peer = new ConsoleMessagePeer();
    peer->webConsoleLog = eventInfo->GetMessage();
    parameter.message.ptr = peer;
    Callback_Boolean_Void continuation;
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(parameter, continuation);
    LOGE("WebAttributeModifier::OnConsoleImpl return value can be incorrect");
    return false;
};

OnErrorReceiveEvent g_onErrorReceive = [](const Callback_OnErrorReceiveEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info) {
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<ReceivedErrorEvent>(info);
    Ark_OnErrorReceiveEvent parameter;
    auto errorPeer = new WebResourceErrorPeer();
    errorPeer->handler = eventInfo->GetError();
    parameter.error.ptr = errorPeer;
    auto requestPeer = new WebResourceRequestPeer();
    requestPeer->webRequest = eventInfo->GetRequest();
    parameter.request.ptr = requestPeer;
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(parameter);
};

OnHttpErrorReceiveEvent g_onHttpErrorReceive = [](const Callback_OnHttpErrorReceiveEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info) {
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<ReceivedHttpErrorEvent>(info);
    Ark_OnHttpErrorReceiveEvent parameter;
    auto requestPeer = new WebResourceRequestPeer();
    requestPeer->webRequest = eventInfo->GetRequest();
    parameter.request.ptr = requestPeer;
    auto responsePeer = new WebResourceResponsePeer();
    responsePeer->handler = eventInfo->GetResponse();
    parameter.response.ptr = responsePeer;
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(parameter);
};

OnDownloadStartEvent g_onDownloadStart = [](const Callback_OnDownloadStartEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info) {
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<DownloadStartEvent>(info);
    Ark_OnDownloadStartEvent parameter;
    parameter.url = Converter::ArkValue<Ark_String>(eventInfo->GetUrl());
    parameter.mimetype = Converter::ArkValue<Ark_String>(eventInfo->GetMimetype());
    parameter.contentDisposition = Converter::ArkValue<Ark_String>(eventInfo->GetContentDisposition());
    parameter.userAgent = Converter::ArkValue<Ark_String>(eventInfo->GetUserAgent());
    parameter.contentLength = Converter::ArkValue<Ark_Number>(eventInfo->GetContentLength());
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(parameter);
};

OnRefreshAccessedHistoryEvent g_onRefreshAccessedHistory = [](
    const Callback_OnRefreshAccessedHistoryEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info) {
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<RefreshAccessedHistoryEvent>(info);
    Ark_OnRefreshAccessedHistoryEvent parameter;
    parameter.url = Converter::ArkValue<Ark_String>(eventInfo->GetVisitedUrl());
    parameter.isRefreshed = Converter::ArkValue<Ark_Boolean>(eventInfo->IsRefreshed());
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(parameter);
};

OnUrlLoadInterceptEvent g_onUrlLoadIntercept = [](const Type_WebAttribute_onUrlLoadIntercept_callback* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info) -> bool {
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<UrlLoadInterceptEvent>(info);
    Ark_Literal_Union_String_WebResourceRequest_data parameter;
    parameter.data = Converter::ArkUnion<Ark_Union_String_WebResourceRequest, Ark_String>(
        Converter::ArkValue<Ark_String>(eventInfo->GetData()));
    auto optParam = Converter::ArkValue<Opt_Literal_Union_String_WebResourceRequest_data>(parameter);
    Callback_Boolean_Void continuation;
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(optParam, continuation);
    LOGE("WebAttributeModifier::OnUrlLoadInterceptImpl return value can be incorrect");
    return false;
};

OnRenderExitedEvent g_onRenderExited = [](const Callback_OnRenderExitedEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info) {
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<RenderExitedEvent>(info);
    Ark_OnRenderExitedEvent parameter;
    parameter.renderExitReason = Converter::ArkValue<Ark_RenderExitReason>(
        static_cast<Converter::RenderExitReason>(eventInfo->GetExitedReason()));
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(parameter);
};

OnShowFileSelectorEvent g_onShowFileSelector = [](const Callback_OnShowFileSelectorEvent_Boolean* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info) -> bool {
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<FileSelectorEvent>(info);
    Ark_OnShowFileSelectorEvent parameter;
    auto paramPeer = new FileSelectorParamPeer();
    paramPeer->handler = eventInfo->GetParam();
    parameter.fileSelector.ptr = paramPeer;
    auto resultPeer = new FileSelectorResultPeer();
    resultPeer->handler = eventInfo->GetFileSelectorResult();
    parameter.result.ptr = resultPeer;
    Callback_Boolean_Void continuation;
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(parameter, continuation);
    LOGE("WebAttributeModifier::OnShowFileSelectorImpl return value can be incorrect");
    return false;
};

OnResourceLoadEvent g_onResourceLoad = [](const Callback_OnResourceLoadEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info) {
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<ResourceLoadEvent>(info);
    Ark_OnResourceLoadEvent parameter;
    parameter.url = Converter::ArkValue<Ark_String>(eventInfo->GetOnResourceLoadUrl());
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(parameter);
};

OnFullScreenExitEvent g_onFullScreenExit = [](const Callback_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info) {
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke();
};

OnFullScreenEnterEvent g_onFullScreenEnter = [](const OnFullScreenEnterCallback* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info) {
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<FullScreenEnterEvent>(info);
    Ark_FullScreenEnterEvent parameter;
    parameter.videoWidth = Converter::ArkValue<Opt_Number>(eventInfo->GetVideoNaturalWidth());
    parameter.videoHeight = Converter::ArkValue<Opt_Number>(eventInfo->GetVideoNaturalHeight());
    parameter.handler.ptr = Referenced::RawPtr(eventInfo->GetHandler());
    auto peer = new FullScreenExitHandlerPeer();
    peer->handler = eventInfo->GetHandler();
    parameter.handler.ptr = peer;
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(parameter);
};

OnScaleChangeEvent g_onScaleChange = [](const Callback_OnScaleChangeEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info) {
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<ScaleChangeEvent>(info);
    Ark_OnScaleChangeEvent parameter;
    parameter.newScale = Converter::ArkValue<Ark_Number>(eventInfo->GetOnScaleChangeNewScale());
    parameter.oldScale = Converter::ArkValue<Ark_Number>(eventInfo->GetOnScaleChangeOldScale());
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(parameter);
};

OnHttpAuthRequestEvent g_onHttpAuthRequest = [](const Callback_OnHttpAuthRequestEvent_Boolean* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info) -> bool {
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<WebHttpAuthEvent>(info);
    Ark_OnHttpAuthRequestEvent parameter;
    parameter.host = Converter::ArkValue<Ark_String>(eventInfo->GetHost());
    parameter.realm = Converter::ArkValue<Ark_String>(eventInfo->GetRealm());
    auto peer = new HttpAuthHandlerPeer();
    peer->handler = eventInfo->GetResult();
    parameter.handler.ptr = peer;
    Callback_Boolean_Void continuation;
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(parameter, continuation);
    LOGE("WebAttributeModifier::OnHttpAuthRequestImpl return value can be incorrect");
    return false;
};

OnInterceptRequest g_onInterceptRequest = [](const Callback_OnInterceptRequestEvent_WebResourceResponse* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info) -> RefPtr<WebResponse> {
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, nullptr);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<OnInterceptRequestEvent>(info);
    Ark_OnInterceptRequestEvent parameter;
    auto peer = new WebResourceRequestPeer();
    peer->webRequest = eventInfo->GetRequest();
    parameter.request.ptr = peer;
    Callback_WebResourceResponse_Void continuation;
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(parameter, continuation);
    LOGE("WebAttributeModifier::OnInterceptRequestImpl return value can be incorrect");
    return nullptr;
};

OnPermissionRequestEvent g_onPermissionRequest = [](const Callback_OnPermissionRequestEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info) {
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<WebPermissionRequestEvent>(info);
    Ark_OnPermissionRequestEvent parameter;
    auto peer = new PermissionRequestPeer();
    peer->handler = eventInfo->GetWebPermissionRequest();
    parameter.request.ptr = peer;
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(parameter);
};

OnScreenCaptureRequestEvent g_onScreenCaptureRequest = [](const Callback_OnScreenCaptureRequestEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info) {
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<WebScreenCaptureRequestEvent>(info);
    Ark_OnScreenCaptureRequestEvent parameter;
    auto peer = new ScreenCaptureHandlerPeer();
    peer->handler = eventInfo->GetWebScreenCaptureRequest();
    parameter.handler.ptr = peer;
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(parameter);
};

OnContextMenuShowEvent g_onContextMenuShow = [](const Callback_OnContextMenuShowEvent_Boolean* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info) -> bool {
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<ContextMenuEvent>(info);
    Ark_OnContextMenuShowEvent parameter;
    auto paramPeer = new WebContextMenuParamPeer();
    paramPeer->handler = eventInfo->GetParam();
    parameter.param.ptr = paramPeer;
    auto resultPeer = new WebContextMenuResultPeer();
    resultPeer->handler = eventInfo->GetContextMenuResult();
    parameter.result.ptr = resultPeer;
    Callback_Boolean_Void continuation;
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(parameter, continuation);
    LOGE("WebAttributeModifier::OnContextMenuShowImpl return value can be incorrect");
    return false;
};

OnContextMenuHideEvent g_onContextMenuHide = [](const OnContextMenuHideCallback* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info) {
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke();
};

OnSearchResultReceiveEvent g_onSearchResultReceive = [](const Callback_OnSearchResultReceiveEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info) {
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<SearchResultReceiveEvent>(info);
    Ark_OnSearchResultReceiveEvent parameter;
    parameter.activeMatchOrdinal = Converter::ArkValue<Ark_Number>(eventInfo->GetActiveMatchOrdinal());
    parameter.numberOfMatches = Converter::ArkValue<Ark_Number>(eventInfo->GetNumberOfMatches());
    parameter.isDoneCounting = Converter::ArkValue<Ark_Boolean>(eventInfo->GetIsDoneCounting());
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(parameter);
};

OnScrollEvent g_onScroll = [](const Callback_OnScrollEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info) {
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<WebOnScrollEvent>(info);
    Ark_OnScrollEvent parameter;
    parameter.xOffset = Converter::ArkValue<Ark_Number>(eventInfo->GetX());
    parameter.yOffset = Converter::ArkValue<Ark_Number>(eventInfo->GetY());
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(parameter);
};

OnSslErrorEventReceiveEvent g_onSslErrorEventReceive = [](const Callback_OnSslErrorEventReceiveEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info) -> bool {
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<WebSslErrorEvent>(info);
    Ark_OnSslErrorEventReceiveEvent parameter;
    parameter.error = Converter::ArkValue<Ark_SslError>(static_cast<Converter::SslError>(eventInfo->GetError()));
    Converter::ArkArrayHolder<Array_Buffer> vecHolder(eventInfo->GetCertChainData());
    parameter.certChainData = Converter::ArkValue<Opt_Array_Buffer>(vecHolder.ArkValue());
    auto peer = new SslErrorHandlerPeer();
    peer->handler = eventInfo->GetResult();
    parameter.handler.ptr = peer;
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(parameter);
    return true;
};

OnSslErrorEvent g_onSslErrorEvent = [](const OnSslErrorEventCallback* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info) -> bool {
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<WebAllSslErrorEvent>(info);
    Ark_SslErrorEvent parameter;
    parameter.error = Converter::ArkValue<Ark_SslError>(static_cast<Converter::SslError>(eventInfo->GetError()));
    parameter.isFatalError = Converter::ArkValue<Ark_Boolean>(eventInfo->GetIsFatalError());
    parameter.isMainFrame = Converter::ArkValue<Ark_Boolean>(eventInfo->GetIsMainFrame());
    auto original = eventInfo->GetOriginalUrl();
    parameter.originalUrl = Converter::ArkValue<Ark_String>(original);
    auto referrer = eventInfo->GetReferrer();
    parameter.referrer = Converter::ArkValue<Ark_String>(referrer);
    auto url = eventInfo->GetUrl();
    parameter.url = Converter::ArkValue<Ark_String>(url);
    auto peer = new SslErrorHandlerPeer();
    peer->handler = eventInfo->GetResult();
    parameter.handler.ptr = peer;
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(parameter);
    return true;
};

OnClientAuthenticationEvent g_onClientAuthenticationRequest = [](
    const Callback_OnClientAuthenticationEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info) -> bool {
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<WebSslSelectCertEvent>(info);
    Ark_OnClientAuthenticationEvent parameter;
    parameter.host = Converter::ArkValue<Ark_String>(eventInfo->GetHost());
    parameter.port = Converter::ArkValue<Ark_Number>(eventInfo->GetPort());
    std::vector<std::string> keyTypes = eventInfo->GetKeyTypes();
    Converter::ArkArrayHolder<Array_String> vecKeyTypes(keyTypes);
    parameter.keyTypes = vecKeyTypes.ArkValue();
    std::vector<std::string> issuers = eventInfo->GetIssuers_();
    Converter::ArkArrayHolder<Array_String> vecIssuers(issuers);
    parameter.issuers = vecIssuers.ArkValue();
        auto peer = new ClientAuthenticationHandlerPeer();
    peer->handler = eventInfo->GetResult();
    parameter.handler.ptr = peer;
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(parameter);
    return false;
};

OnWindowNewEvent g_onWindowNew = [](const Callback_OnWindowNewEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const std::shared_ptr<BaseEventInfo>& info) {
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<WebWindowNewEvent>(info.get());
    Ark_OnWindowNewEvent parameter;
    parameter.isAlert = Converter::ArkValue<Ark_Boolean>(eventInfo->IsAlert());
    parameter.isUserTrigger = Converter::ArkValue<Ark_Boolean>(eventInfo->IsUserTrigger());
    parameter.targetUrl = Converter::ArkValue<Ark_String>(eventInfo->GetTargetUrl());
    auto peer = new ControllerHandlerPeer();
    peer->handler = eventInfo->GetWebWindowNewHandler();
    parameter.handler.ptr = peer;
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(parameter);
};

OnWindowExitEvent g_onWindowExit = [](const Callback_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info) {
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke();
};

OnKeyEvent g_onInterceptKeyEvent = [](const Callback_KeyEvent_Boolean* value,
    WeakPtr<FrameNode> weakNode, KeyEventInfo& keyEventInfo) -> bool {
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    Ark_KeyEvent parameter;
    parameter.type = Converter::ArkValue<Ark_KeyType>(keyEventInfo.GetKeyType());
    parameter.keyCode = Converter::ArkValue<Ark_Number>(static_cast<int32_t>(keyEventInfo.GetKeyCode()));
    parameter.keyText = Converter::ArkValue<Ark_String>(keyEventInfo.GetKeyText());
    parameter.keySource = Converter::ArkValue<Ark_KeySource>(keyEventInfo.GetKeySource());
    parameter.deviceId = Converter::ArkValue<Ark_Number>(keyEventInfo.GetDeviceId());
    parameter.metaKey = Converter::ArkValue<Ark_Number>(keyEventInfo.GetMetaKey());
    parameter.timestamp = Converter::ArkValue<Ark_Number>(
        std::chrono::duration_cast<std::chrono::milliseconds>(
            keyEventInfo.GetTimeStamp().time_since_epoch()).count());
    LOGE("WebAttributeModifier::OnInterceptKeyEventImpl IntentionCode supporting is not implemented yet");
    parameter.unicode = Converter::ArkValue<Opt_Number>(keyEventInfo.GetUnicode());
    Callback_Boolean_Void continuation;
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(parameter, continuation);
    LOGE("WebAttributeModifier::OnInterceptKeyEventImpl return value can be incorrect");
    return false;
};

OnTouchIconUrlReceivedEvent g_onTouchIconUrlReceived = [](const Callback_OnTouchIconUrlReceivedEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const std::shared_ptr<BaseEventInfo>& info) {
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto arkCallback = CallbackHelper(*value);
    auto func = [arkCallback, info]() {
        auto* eventInfo = TypeInfoHelper::DynamicCast<TouchIconUrlEvent>(info.get());
        Ark_OnTouchIconUrlReceivedEvent parameter;
        parameter.url = Converter::ArkValue<Ark_String>(eventInfo->GetUrl());
        parameter.precomposed = Converter::ArkValue<Ark_Boolean>(eventInfo->GetPreComposed());
        arkCallback.Invoke(parameter);
    };
#ifdef ARKUI_CAPI_UNITTEST
    func();
#else
    pipelineContext->PostAsyncEvent([func]() { func(); }, "ArkUIWebTouchIconUrlReceived");
#endif // ARKUI_CAPI_UNITTEST
};

OnFaviconReceivedEvent g_onFaviconReceived = [](const Callback_OnFaviconReceivedEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const std::shared_ptr<BaseEventInfo>& info) {
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto arkCallback = CallbackHelper(*value);
    pipelineContext->PostAsyncEvent([arkCallback, info]() {
        Ark_OnFaviconReceivedEvent parameter;
        LOGE("WebAttributeModifier::OnFaviconReceivedImpl PixelMap supporting is not implemented yet");
        arkCallback.Invoke(parameter);
        }, "ArkUIWebFaviconReceived");
};

OnPageVisibleEvent g_onPageVisible = [](const Callback_OnPageVisibleEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const std::shared_ptr<BaseEventInfo>& info) {
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto arkCallback = CallbackHelper(*value);
    auto func = [arkCallback, info]() {
        auto* eventInfo = TypeInfoHelper::DynamicCast<PageVisibleEvent>(info.get());
        Ark_OnPageVisibleEvent parameter;
        parameter.url = Converter::ArkValue<Ark_String>(eventInfo->GetUrl());
        arkCallback.Invoke(parameter);
    };
#ifdef ARKUI_CAPI_UNITTEST
    func();
#else
    pipelineContext->PostAsyncEvent([func]() { func(); }, "ArkUIWebPageVisible");
#endif // ARKUI_CAPI_UNITTEST
};

OnDataResubmittedEvent g_onDataResubmitted = [](const Callback_OnDataResubmittedEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const std::shared_ptr<BaseEventInfo>& info) {
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto arkCallback = CallbackHelper(*value);
    auto func = [arkCallback, info]() {
        auto* eventInfo = TypeInfoHelper::DynamicCast<DataResubmittedEvent>(info.get());
        Ark_OnDataResubmittedEvent parameter;
        auto peer = new DataResubmissionHandlerPeer();
        peer->handler = eventInfo->GetHandler();
        parameter.handler.ptr = peer;
        arkCallback.Invoke(parameter);
    };
#ifdef ARKUI_CAPI_UNITTEST
    func();
#else
    pipelineContext->PostAsyncEvent([func]() { func(); }, "ArkUIWebDataResubmitted");
#endif // ARKUI_CAPI_UNITTEST
};

} // namespace OHOS::Ace::NG::GeneratedModifier::WebAttributeModifier
#endif // WEB_SUPPORTED