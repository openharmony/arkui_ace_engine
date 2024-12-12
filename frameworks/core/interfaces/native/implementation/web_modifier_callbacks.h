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

#include "core/components/web/web_event.h"
#include "core/interfaces/native/implementation/console_message_peer_impl.h"
#include "core/interfaces/native/implementation/file_selector_param_peer_impl.h"
#include "core/interfaces/native/implementation/file_selector_result_peer_impl.h"
#include "core/interfaces/native/implementation/full_screen_exit_handler_peer_impl.h"
#include "core/interfaces/native/implementation/js_geolocation_peer_impl.h"
#include "core/interfaces/native/implementation/js_result_peer_impl.h"
#include "core/interfaces/native/implementation/http_auth_handler_peer_impl.h"
#include "core/interfaces/native/implementation/permission_request_peer_impl.h"
#include "core/interfaces/native/implementation/web_resource_error_peer_impl.h"
#include "core/interfaces/native/implementation/web_resource_request_peer_impl.h"
#include "core/interfaces/native/implementation/web_resource_response_peer_impl.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG::GeneratedModifier::WebAttributeModifier {
auto g_onPageEnd = [](const Callback_OnPageEndEvent_Void* value, WeakPtr<FrameNode> weakNode, int32_t instanceId,
    const BaseEventInfo* info) {
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

auto g_onPageBegin = [](const Callback_OnPageBeginEvent_Void* value, WeakPtr<FrameNode> weakNode,
    int32_t instanceId, const BaseEventInfo* info) {
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

auto g_onProgressChange = [](const Callback_OnProgressChangeEvent_Void* value, WeakPtr<FrameNode> weakNode,
    int32_t instanceId, const BaseEventInfo* info) {
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

auto g_onTitleReceive = [](const Callback_OnTitleReceiveEvent_Void* value, WeakPtr<FrameNode> weakNode,
    int32_t instanceId, const BaseEventInfo* info) {
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

auto g_onGeolocationHide = [](const Callback_Void* value, WeakPtr<FrameNode> weakNode, int32_t instanceId,
    const BaseEventInfo* info) {
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke();
};

auto g_onGeolocationShow = [](const Callback_OnGeolocationShowEvent_Void* value, WeakPtr<FrameNode> weakNode,
    int32_t instanceId, const BaseEventInfo* info) {
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

auto g_onRequestSelected = [](const Callback_Void* value, WeakPtr<FrameNode> weakNode, const BaseEventInfo* info) {
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke();
};

auto g_onAlert = [](const Callback_OnAlertEvent_Boolean* value, WeakPtr<FrameNode> weakNode, int32_t instanceId,
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

auto g_onBeforeUnload = [](const Callback_OnBeforeUnloadEvent_Boolean* value, WeakPtr<FrameNode> weakNode,
    int32_t instanceId, const BaseEventInfo* info) -> bool {
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

auto g_onConfirm = [](const Callback_OnConfirmEvent_Boolean* value, WeakPtr<FrameNode> weakNode,
    int32_t instanceId, const BaseEventInfo* info) -> bool {
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

auto g_onPrompt = [](const Callback_OnPromptEvent_Boolean* value, WeakPtr<FrameNode> weakNode,
    int32_t instanceId, const BaseEventInfo* info) -> bool {
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

auto g_onConsole = [](const Callback_OnConsoleEvent_Boolean* value, WeakPtr<FrameNode> weakNode,
    const BaseEventInfo* info) -> bool {
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

auto g_onErrorReceive = [](const Callback_OnErrorReceiveEvent_Void* value, WeakPtr<FrameNode> weakNode,
    int32_t instanceId, const BaseEventInfo* info) {
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

auto g_onHttpErrorReceive = [](const Callback_OnHttpErrorReceiveEvent_Void* value, WeakPtr<FrameNode> weakNode,
    int32_t instanceId, const BaseEventInfo* info) {
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

auto g_onDownloadStart = [](const Callback_OnDownloadStartEvent_Void* value, WeakPtr<FrameNode> weakNode,
    int32_t instanceId, const BaseEventInfo* info) {
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

auto g_onRefreshAccessedHistory = [](const Callback_OnRefreshAccessedHistoryEvent_Void* value,
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

auto g_onUrlLoadIntercept = [](const Type_WebAttribute_onUrlLoadIntercept_callback* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info) -> bool {
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<UrlLoadInterceptEvent>(info);
    Ark_Literal_Union_String_WebResourceRequest_data parameter;
    parameter.data = Converter::ArkUnion<Ark_Union_String_WebResourceRequest, Ark_String>(
        Converter::ArkValue<Ark_String>(eventInfo->GetData()));
    auto optParam = Converter::ArkValue<Opt_Literal_Union_String_WebResourceRequest_data>(
        std::optional<Ark_Literal_Union_String_WebResourceRequest_data>(parameter));
    Callback_Boolean_Void continuation;
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(optParam, continuation);
    LOGE("WebAttributeModifier::OnUrlLoadInterceptImpl return value can be incorrect");
    return false;
};

auto g_onRenderExited = [](const Callback_OnRenderExitedEvent_Void* value, WeakPtr<FrameNode> weakNode,
    int32_t instanceId, const BaseEventInfo* info) {
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

auto g_onShowFileSelector = [](const Callback_OnShowFileSelectorEvent_Boolean* value, WeakPtr<FrameNode> weakNode,
    int32_t instanceId, const BaseEventInfo* info) -> bool {
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

auto g_onResourceLoad = [](const Callback_OnResourceLoadEvent_Void* value, WeakPtr<FrameNode> weakNode,
    int32_t instanceId, const BaseEventInfo* info) {
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

auto g_onFullScreenExit = [](const Callback_Void* value, WeakPtr<FrameNode> weakNode, int32_t instanceId,
    const BaseEventInfo* info) {
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke();
};

auto g_onFullScreenEnter = [](const OnFullScreenEnterCallback* value, WeakPtr<FrameNode> weakNode,
    int32_t instanceId, const BaseEventInfo* info) {
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<FullScreenEnterEvent>(info);
    Ark_FullScreenEnterEvent parameter;
    parameter.videoWidth = Converter::ArkValue<Opt_Number>(std::optional<Ark_Number>(
        Converter::ArkValue<Ark_Number>(eventInfo->GetVideoNaturalWidth())));
    parameter.videoHeight = Converter::ArkValue<Opt_Number>(std::optional<Ark_Number>(
        Converter::ArkValue<Ark_Number>(eventInfo->GetVideoNaturalHeight())));
    parameter.handler.ptr = Referenced::RawPtr(eventInfo->GetHandler());
    auto peer = new FullScreenExitHandlerPeer();
    peer->handler = eventInfo->GetHandler();
    parameter.handler.ptr = peer;
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(parameter);
};

auto g_onScaleChange = [](const Callback_OnScaleChangeEvent_Void* value, WeakPtr<FrameNode> weakNode,
    int32_t instanceId, const BaseEventInfo* info) {
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

auto g_onHttpAuthRequest = [](const Callback_OnHttpAuthRequestEvent_Boolean* value, WeakPtr<FrameNode> weakNode,
    int32_t instanceId, const BaseEventInfo* info) -> bool {
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

auto g_onInterceptRequest = [](const Callback_OnInterceptRequestEvent_WebResourceResponse* value,
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

auto g_onPermissionRequest = [](const Callback_OnPermissionRequestEvent_Void* value, WeakPtr<FrameNode> weakNode,
    int32_t instanceId, const BaseEventInfo* info) {
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
} // namespace OHOS::Ace::NG::GeneratedModifier::WebAttributeModifier

#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_WEB_MODIFIER_CALLBACKS_H