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
#include "core/interfaces/native/implementation/event_result_peer_impl.h"
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

void OnPageEnd(const Callback_OnPageEndEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<LoadWebPageFinishEvent>(info);
    CHECK_NULL_VOID(eventInfo);
    Ark_OnPageEndEvent parameter;
    parameter.url = Converter::ArkValue<Ark_String>(eventInfo->GetLoadedUrl());
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(parameter);
}

void OnPageBegin(const Callback_OnPageBeginEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<LoadWebPageStartEvent>(info);
    CHECK_NULL_VOID(eventInfo);
    Ark_OnPageBeginEvent parameter;
    parameter.url = Converter::ArkValue<Ark_String>(eventInfo->GetLoadedUrl());
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(parameter);
}

void OnProgressChange(const Callback_OnProgressChangeEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<LoadWebProgressChangeEvent>(info);
    CHECK_NULL_VOID(eventInfo);
    Ark_OnProgressChangeEvent parameter;
    parameter.newProgress = Converter::ArkValue<Ark_Number>(eventInfo->GetNewProgress());
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(parameter);
}

void OnTitleReceive(const Callback_OnTitleReceiveEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<LoadWebTitleReceiveEvent>(info);
    CHECK_NULL_VOID(eventInfo);
    Ark_OnTitleReceiveEvent parameter;
    parameter.title = Converter::ArkValue<Ark_String>(eventInfo->GetTitle());
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(parameter);
}

void OnGeolocationHide(const Callback_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke();
}

void OnGeolocationShow(const Callback_OnGeolocationShowEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<LoadWebGeolocationShowEvent>(info);
    CHECK_NULL_VOID(eventInfo);
    Ark_OnGeolocationShowEvent parameter;
    parameter.origin = Converter::ArkValue<Ark_String>(eventInfo->GetOrigin());
    auto peer = new JsGeolocationPeer();
    peer->webGeolocation = eventInfo->GetWebGeolocation();
    parameter.geolocation.ptr = peer;
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(parameter);
}

void OnRequestSelected(const Callback_Void* value,
    WeakPtr<FrameNode> weakNode, const BaseEventInfo* info)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke();
}

bool OnAlert(const Callback_OnAlertEvent_Boolean* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<WebDialogEvent>(info);
    CHECK_NULL_RETURN(eventInfo, false);
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
}

bool OnBeforeUnload(const Callback_OnBeforeUnloadEvent_Boolean* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<WebDialogEvent>(info);
    CHECK_NULL_RETURN(eventInfo, false);
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
}

bool OnConfirm(const Callback_OnConfirmEvent_Boolean* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<WebDialogEvent>(info);
    CHECK_NULL_RETURN(eventInfo, false);
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
}

bool OnPrompt(const Callback_OnPromptEvent_Boolean* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<WebDialogEvent>(info);
    CHECK_NULL_RETURN(eventInfo, false);
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
}

bool OnConsole(const Callback_OnConsoleEvent_Boolean* value,
    WeakPtr<FrameNode> weakNode, const BaseEventInfo* info)
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<LoadWebConsoleLogEvent>(info);
    CHECK_NULL_RETURN(eventInfo, false);
    Ark_OnConsoleEvent parameter;
    auto peer = new ConsoleMessagePeer();
    peer->webConsoleLog = eventInfo->GetMessage();
    parameter.message.ptr = peer;
    Callback_Boolean_Void continuation;
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(parameter, continuation);
    LOGE("WebAttributeModifier::OnConsoleImpl return value can be incorrect");
    return false;
}

void OnErrorReceive(const Callback_OnErrorReceiveEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<ReceivedErrorEvent>(info);
    CHECK_NULL_VOID(eventInfo);
    Ark_OnErrorReceiveEvent parameter;
    auto errorPeer = new WebResourceErrorPeer();
    errorPeer->handler = eventInfo->GetError();
    parameter.error.ptr = errorPeer;
    auto requestPeer = new WebResourceRequestPeer();
    requestPeer->webRequest = eventInfo->GetRequest();
    parameter.request.ptr = requestPeer;
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(parameter);
}

void OnHttpErrorReceive(const Callback_OnHttpErrorReceiveEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<ReceivedHttpErrorEvent>(info);
    CHECK_NULL_VOID(eventInfo);
    Ark_OnHttpErrorReceiveEvent parameter;
    auto requestPeer = new WebResourceRequestPeer();
    requestPeer->webRequest = eventInfo->GetRequest();
    parameter.request.ptr = requestPeer;
    auto responsePeer = new WebResourceResponsePeer();
    responsePeer->handler = eventInfo->GetResponse();
    parameter.response.ptr = responsePeer;
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(parameter);
}

void OnDownloadStart(const Callback_OnDownloadStartEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<DownloadStartEvent>(info);
    CHECK_NULL_VOID(eventInfo);
    Ark_OnDownloadStartEvent parameter;
    parameter.url = Converter::ArkValue<Ark_String>(eventInfo->GetUrl());
    parameter.mimetype = Converter::ArkValue<Ark_String>(eventInfo->GetMimetype());
    parameter.contentDisposition = Converter::ArkValue<Ark_String>(eventInfo->GetContentDisposition());
    parameter.userAgent = Converter::ArkValue<Ark_String>(eventInfo->GetUserAgent());
    parameter.contentLength = Converter::ArkValue<Ark_Number>(eventInfo->GetContentLength());
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(parameter);
}

void OnRefreshAccessedHistory(const Callback_OnRefreshAccessedHistoryEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<RefreshAccessedHistoryEvent>(info);
    CHECK_NULL_VOID(eventInfo);
    Ark_OnRefreshAccessedHistoryEvent parameter;
    parameter.url = Converter::ArkValue<Ark_String>(eventInfo->GetVisitedUrl());
    parameter.isRefreshed = Converter::ArkValue<Ark_Boolean>(eventInfo->IsRefreshed());
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(parameter);
}

bool OnUrlLoadIntercept(const Type_WebAttribute_onUrlLoadIntercept_callback* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<UrlLoadInterceptEvent>(info);
    CHECK_NULL_RETURN(eventInfo, false);
    Ark_Literal_Union_String_WebResourceRequest_data parameter;
    parameter.data = Converter::ArkUnion<Ark_Union_String_WebResourceRequest, Ark_String>(
        Converter::ArkValue<Ark_String>(eventInfo->GetData()));
    auto optParam = Converter::ArkValue<Opt_Literal_Union_String_WebResourceRequest_data>(parameter);
    Callback_Boolean_Void continuation;
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(optParam, continuation);
    LOGE("WebAttributeModifier::OnUrlLoadInterceptImpl return value can be incorrect");
    return false;
}

void OnRenderExited(const Callback_OnRenderExitedEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<RenderExitedEvent>(info);
    CHECK_NULL_VOID(eventInfo);
    Ark_OnRenderExitedEvent parameter;
    parameter.renderExitReason = Converter::ArkValue<Ark_RenderExitReason>(
        static_cast<Converter::RenderExitReason>(eventInfo->GetExitedReason()));
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(parameter);
}

bool OnShowFileSelector(const Callback_OnShowFileSelectorEvent_Boolean* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<FileSelectorEvent>(info);
    CHECK_NULL_RETURN(eventInfo, false);
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
}

void OnResourceLoad(const Callback_OnResourceLoadEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<ResourceLoadEvent>(info);
    CHECK_NULL_VOID(eventInfo);
    Ark_OnResourceLoadEvent parameter;
    parameter.url = Converter::ArkValue<Ark_String>(eventInfo->GetOnResourceLoadUrl());
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(parameter);
}

void OnFullScreenExit(const Callback_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke();
}

void OnFullScreenEnter(const OnFullScreenEnterCallback* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<FullScreenEnterEvent>(info);
    CHECK_NULL_VOID(eventInfo);
    Ark_FullScreenEnterEvent parameter;
    parameter.videoWidth = Converter::ArkValue<Opt_Number>(eventInfo->GetVideoNaturalWidth());
    parameter.videoHeight = Converter::ArkValue<Opt_Number>(eventInfo->GetVideoNaturalHeight());
    auto peer = new FullScreenExitHandlerPeer();
    peer->handler = eventInfo->GetHandler();
    parameter.handler.ptr = peer;
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(parameter);
}

void OnScaleChange(const Callback_OnScaleChangeEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<ScaleChangeEvent>(info);
    CHECK_NULL_VOID(eventInfo);
    Ark_OnScaleChangeEvent parameter;
    parameter.newScale = Converter::ArkValue<Ark_Number>(eventInfo->GetOnScaleChangeNewScale());
    parameter.oldScale = Converter::ArkValue<Ark_Number>(eventInfo->GetOnScaleChangeOldScale());
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(parameter);
}

bool OnHttpAuthRequest(const Callback_OnHttpAuthRequestEvent_Boolean* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<WebHttpAuthEvent>(info);
    CHECK_NULL_RETURN(eventInfo, false);
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
}

RefPtr<WebResponse> OnInterceptRequest(const Callback_OnInterceptRequestEvent_WebResourceResponse* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, nullptr);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<OnInterceptRequestEvent>(info);
    CHECK_NULL_RETURN(eventInfo, nullptr);
    Ark_OnInterceptRequestEvent parameter;
    auto peer = new WebResourceRequestPeer();
    peer->webRequest = eventInfo->GetRequest();
    parameter.request.ptr = peer;
    Callback_WebResourceResponse_Void continuation;
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(parameter, continuation);
    LOGE("WebAttributeModifier::OnInterceptRequestImpl return value can be incorrect");
    return nullptr;
}

void OnPermissionRequest(const Callback_OnPermissionRequestEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<WebPermissionRequestEvent>(info);
    CHECK_NULL_VOID(eventInfo);
    Ark_OnPermissionRequestEvent parameter;
    auto peer = new PermissionRequestPeer();
    peer->handler = eventInfo->GetWebPermissionRequest();
    parameter.request.ptr = peer;
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(parameter);
}

void OnScreenCaptureRequest(const Callback_OnScreenCaptureRequestEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<WebScreenCaptureRequestEvent>(info);
    CHECK_NULL_VOID(eventInfo);
    Ark_OnScreenCaptureRequestEvent parameter;
    auto peer = new ScreenCaptureHandlerPeer();
    peer->handler = eventInfo->GetWebScreenCaptureRequest();
    parameter.handler.ptr = peer;
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(parameter);
}

bool OnContextMenuShow(const Callback_OnContextMenuShowEvent_Boolean* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<ContextMenuEvent>(info);
    CHECK_NULL_RETURN(eventInfo, false);
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
}

void OnContextMenuHide(const OnContextMenuHideCallback* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke();
}

void OnSearchResultReceive(const Callback_OnSearchResultReceiveEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<SearchResultReceiveEvent>(info);
    CHECK_NULL_VOID(eventInfo);
    Ark_OnSearchResultReceiveEvent parameter;
    parameter.activeMatchOrdinal = Converter::ArkValue<Ark_Number>(eventInfo->GetActiveMatchOrdinal());
    parameter.numberOfMatches = Converter::ArkValue<Ark_Number>(eventInfo->GetNumberOfMatches());
    parameter.isDoneCounting = Converter::ArkValue<Ark_Boolean>(eventInfo->GetIsDoneCounting());
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(parameter);
}

void OnScroll(const Callback_OnScrollEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<WebOnScrollEvent>(info);
    CHECK_NULL_VOID(eventInfo);
    Ark_OnScrollEvent parameter;
    parameter.xOffset = Converter::ArkValue<Ark_Number>(eventInfo->GetX());
    parameter.yOffset = Converter::ArkValue<Ark_Number>(eventInfo->GetY());
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(parameter);
}

bool OnSslErrorEventReceive(const Callback_OnSslErrorEventReceiveEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<WebSslErrorEvent>(info);
    CHECK_NULL_RETURN(eventInfo, false);
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
}

bool OnSslError(const OnSslErrorEventCallback* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<WebAllSslErrorEvent>(info);
    CHECK_NULL_RETURN(eventInfo, false);
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
}

bool OnClientAuthentication(const Callback_OnClientAuthenticationEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<WebSslSelectCertEvent>(info);
    CHECK_NULL_RETURN(eventInfo, false);
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
}

void OnWindowNew(const Callback_OnWindowNewEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const std::shared_ptr<BaseEventInfo>& info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<WebWindowNewEvent>(info.get());
    CHECK_NULL_VOID(eventInfo);
    Ark_OnWindowNewEvent parameter;
    parameter.isAlert = Converter::ArkValue<Ark_Boolean>(eventInfo->IsAlert());
    parameter.isUserTrigger = Converter::ArkValue<Ark_Boolean>(eventInfo->IsUserTrigger());
    parameter.targetUrl = Converter::ArkValue<Ark_String>(eventInfo->GetTargetUrl());
    auto peer = new ControllerHandlerPeer();
    peer->handler = eventInfo->GetWebWindowNewHandler();
    parameter.handler.ptr = peer;
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(parameter);
}

void OnWindowExit(const Callback_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke();
}

bool OnInterceptKey(const Callback_KeyEvent_Boolean* value,
    WeakPtr<FrameNode> weakNode, KeyEventInfo& keyEventInfo)
{
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
}

void OnTouchIconUrlReceived(const Callback_OnTouchIconUrlReceivedEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const std::shared_ptr<BaseEventInfo>& info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto arkCallback = CallbackHelper(*value);
    auto func = [arkCallback, info]() {
        auto* eventInfo = TypeInfoHelper::DynamicCast<TouchIconUrlEvent>(info.get());
        CHECK_NULL_VOID(eventInfo);
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
}

void OnFaviconReceived(const Callback_OnFaviconReceivedEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const std::shared_ptr<BaseEventInfo>& info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto arkCallback = CallbackHelper(*value);
    pipelineContext->PostAsyncEvent([arkCallback]() {
        Ark_OnFaviconReceivedEvent parameter;
        LOGE("WebAttributeModifier::OnFaviconReceivedImpl PixelMap supporting is not implemented yet");
        arkCallback.Invoke(parameter);
        }, "ArkUIWebFaviconReceived");
}

void OnPageVisible(const Callback_OnPageVisibleEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const std::shared_ptr<BaseEventInfo>& info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto arkCallback = CallbackHelper(*value);
    auto func = [arkCallback, info]() {
        auto* eventInfo = TypeInfoHelper::DynamicCast<PageVisibleEvent>(info.get());
        CHECK_NULL_VOID(eventInfo);
        Ark_OnPageVisibleEvent parameter;
        parameter.url = Converter::ArkValue<Ark_String>(eventInfo->GetUrl());
        arkCallback.Invoke(parameter);
    };
#ifdef ARKUI_CAPI_UNITTEST
    func();
#else
    pipelineContext->PostAsyncEvent([func]() { func(); }, "ArkUIWebPageVisible");
#endif // ARKUI_CAPI_UNITTEST
}

void OnDataResubmitted(const Callback_OnDataResubmittedEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const std::shared_ptr<BaseEventInfo>& info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto arkCallback = CallbackHelper(*value);
    auto func = [arkCallback, info]() {
        auto* eventInfo = TypeInfoHelper::DynamicCast<DataResubmittedEvent>(info.get());
        CHECK_NULL_VOID(eventInfo);
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
}

void OnAudioStateChanged(const Callback_OnAudioStateChangedEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const std::shared_ptr<BaseEventInfo>& info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<AudioStateChangedEvent>(info.get());
    CHECK_NULL_VOID(eventInfo);
    Ark_OnAudioStateChangedEvent parameter;
    parameter.playing = Converter::ArkValue<Ark_Boolean>(eventInfo->IsPlaying());
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(parameter);
}

void OnFirstContentfulPaint(const Callback_OnFirstContentfulPaintEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const std::shared_ptr<BaseEventInfo>& info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto arkCallback = CallbackHelper(*value);
    auto func = [arkCallback, info]() {
        auto* eventInfo = TypeInfoHelper::DynamicCast<FirstContentfulPaintEvent>(info.get());
        CHECK_NULL_VOID(eventInfo);
        Ark_OnFirstContentfulPaintEvent parameter;
        parameter.firstContentfulPaintMs = Converter::ArkValue<Ark_Number>(
            eventInfo->GetFirstContentfulPaintMs());
        parameter.navigationStartTick = Converter::ArkValue<Ark_Number>(eventInfo->GetNavigationStartTick());
        arkCallback.Invoke(parameter);
    };
#ifdef ARKUI_CAPI_UNITTEST
    func();
#else
    pipelineContext->PostAsyncEvent([func]() { func(); }, "ArkUIWebFirstContentfulPaint");
#endif // ARKUI_CAPI_UNITTEST
}

void OnFirstMeaningfulPaint(const OnFirstMeaningfulPaintCallback* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const std::shared_ptr<BaseEventInfo>& info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto arkCallback = CallbackHelper(*value);
    auto func = [arkCallback, info]() {
        auto* eventInfo = TypeInfoHelper::DynamicCast<FirstMeaningfulPaintEvent>(info.get());
        CHECK_NULL_VOID(eventInfo);
        Ark_FirstMeaningfulPaint parameter;
        parameter.firstMeaningfulPaintTime = Converter::ArkValue<Opt_Number>(eventInfo->GetFirstMeaningfulPaintTime());
        parameter.navigationStartTime = Converter::ArkValue<Opt_Number>(eventInfo->GetNavigationStartTime());
        arkCallback.Invoke(parameter);
    };
#ifdef ARKUI_CAPI_UNITTEST
    func();
#else
    pipelineContext->PostAsyncEvent([func]() { func(); }, "ArkUIWebFirstMeaningfulPaint");
#endif // ARKUI_CAPI_UNITTEST
}

void OnLargestContentfulPaint(const OnLargestContentfulPaintCallback* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const std::shared_ptr<BaseEventInfo>& info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto arkCallback = CallbackHelper(*value);
    auto func = [arkCallback, info]() {
        auto* eventInfo = TypeInfoHelper::DynamicCast<LargestContentfulPaintEvent>(info.get());
        CHECK_NULL_VOID(eventInfo);
        Ark_LargestContentfulPaint parameter;
        parameter.imageBPP = Converter::ArkValue<Opt_Number>(eventInfo->GetImageBPP());
        parameter.largestImageLoadEndTime = Converter::ArkValue<Opt_Number>(eventInfo->GetLargestImageLoadEndTime());
        parameter.largestImageLoadStartTime = Converter::ArkValue<Opt_Number>(
            eventInfo->GetLargestImageLoadStartTime());
        parameter.largestImagePaintTime = Converter::ArkValue<Opt_Number>(eventInfo->GetLargestImagePaintTime());
        parameter.largestTextPaintTime = Converter::ArkValue<Opt_Number>(eventInfo->GetLargestTextPaintTime());
        parameter.navigationStartTime = Converter::ArkValue<Opt_Number>(eventInfo->GetNavigationStartTime());
        arkCallback.Invoke(parameter);
    };
#ifdef ARKUI_CAPI_UNITTEST
    func();
#else
    pipelineContext->PostAsyncEvent([func]() { func(); }, "ArkUIWebLargestContentfulPaint");
#endif // ARKUI_CAPI_UNITTEST
}

bool OnLoadIntercept(const Callback_OnLoadInterceptEvent_Boolean* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<LoadInterceptEvent>(info);
    CHECK_NULL_RETURN(eventInfo, false);
    Ark_OnLoadInterceptEvent parameter;
    auto peer = new WebResourceRequestPeer();
    peer->webRequest = eventInfo->GetRequest();
    parameter.data.ptr = peer;
    Callback_Boolean_Void continuation;
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(parameter, continuation);
    LOGE("WebAttributeModifier::OnLoadInterceptImpl return value can be incorrect");
    return false;
}

void OnControllerAttached(const Callback_Void* value, WeakPtr<FrameNode> weakNode, int32_t instanceId)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto arkCallback = CallbackHelper(*value);
    auto func = [arkCallback]() {
        arkCallback.Invoke();
    };
#ifdef ARKUI_CAPI_UNITTEST
    func();
#else
    pipelineContext->PostAsyncEvent([func]() { func(); }, "ArkUIWebControllerAttached");
#endif // ARKUI_CAPI_UNITTEST
}

void OnOverScroll(const Callback_OnOverScrollEvent_Void* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<WebOnOverScrollEvent>(info);
    CHECK_NULL_VOID(eventInfo);
    Ark_OnOverScrollEvent parameter;
    parameter.xOffset = Converter::ArkValue<Ark_Number>(eventInfo->GetX());
    parameter.yOffset = Converter::ArkValue<Ark_Number>(eventInfo->GetY());
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(parameter);
}

void OnSafeBrowsingCheckResult(const OnSafeBrowsingCheckResultCallback* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const std::shared_ptr<BaseEventInfo>& info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto arkCallback = CallbackHelper(*value);
    auto func = [arkCallback, info]() {
        auto* eventInfo = TypeInfoHelper::DynamicCast<SafeBrowsingCheckResultEvent>(info.get());
        CHECK_NULL_VOID(eventInfo);
        Ark_ThreatType parameter = Converter::ArkValue<Ark_ThreatType>(
            static_cast<Converter::ThreatType>(eventInfo->GetThreatType()));
        arkCallback.Invoke(parameter);
    };
#ifdef ARKUI_CAPI_UNITTEST
    func();
#else
    pipelineContext->PostAsyncEvent([func]() { func(); }, "ArkUIWebSafeBrowsingCheckResult");
#endif // ARKUI_CAPI_UNITTEST
}

void OnNavigationEntryCommitted(const OnNavigationEntryCommittedCallback* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const std::shared_ptr<BaseEventInfo>& info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto arkCallback = CallbackHelper(*value);
    auto func = [arkCallback, info]() {
        auto* eventInfo = TypeInfoHelper::DynamicCast<NavigationEntryCommittedEvent>(info.get());
        CHECK_NULL_VOID(eventInfo);
        Ark_LoadCommittedDetails parameter;
        parameter.didReplaceEntry = Converter::ArkValue<Ark_Boolean>(eventInfo->DidReplaceEntry());
        parameter.isMainFrame = Converter::ArkValue<Ark_Boolean>(eventInfo->IsMainFrame());
        parameter.isSameDocument = Converter::ArkValue<Ark_Boolean>(eventInfo->IsSameDocument());
        parameter.navigationType = Converter::ArkValue<Ark_WebNavigationType>(eventInfo->GetNavigationType());
        parameter.url = Converter::ArkValue<Ark_String>(eventInfo->GetUrl());
        arkCallback.Invoke(parameter);
    };
#ifdef ARKUI_CAPI_UNITTEST
    func();
#else
    pipelineContext->PostAsyncEvent([func]() { func(); }, "ArkUIWebNavigationEntryCommitted");
#endif // ARKUI_CAPI_UNITTEST
}

void OnIntelligentTrackingPrevention(const OnIntelligentTrackingPreventionCallback* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const std::shared_ptr<BaseEventInfo>& info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto arkCallback = CallbackHelper(*value);
    auto func = [arkCallback, info]() {
        auto* eventInfo = TypeInfoHelper::DynamicCast<IntelligentTrackingPreventionResultEvent>(info.get());
        CHECK_NULL_VOID(eventInfo);
        Ark_IntelligentTrackingPreventionDetails parameter;
        parameter.host = Converter::ArkValue<Ark_String>(eventInfo->GetHost());
        parameter.trackerHost = Converter::ArkValue<Ark_String>(eventInfo->GetTrackerHost());
        arkCallback.Invoke(parameter);
    };
#ifdef ARKUI_CAPI_UNITTEST
    func();
#else
    pipelineContext->PostAsyncEvent([func]() { func(); }, "ArkUIWebIntelligentTrackingPreventionResult");
#endif // ARKUI_CAPI_UNITTEST
}

void OnNativeEmbedDataInfo(const Callback_NativeEmbedDataInfo_Void* valueInfo,
    int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto* eventInfo = TypeInfoHelper::DynamicCast<NativeEmbedDataInfo>(info);
    CHECK_NULL_VOID(eventInfo);
    Ark_NativeEmbedDataInfo parameter;
    parameter.embedId = Converter::ArkValue<Opt_String>(eventInfo->GetEmbedId());
    auto emebdInfo = eventInfo->GetEmebdInfo();
    Map_String_String map;
    map.size = static_cast<Ark_Int32>(emebdInfo.params.size());
    std::vector<std::string> key;
    std::vector<std::string> value;
    for (std::map<std::string, std::string>::iterator it = emebdInfo.params.begin();
        it != emebdInfo.params.end(); ++it) {
        key.push_back(it->first);
        value.push_back(it->second);
    }
    Converter::ArkArrayHolder<Array_String> vecKeyHolder(key);
    auto arkKeys = vecKeyHolder.ArkValue();
    map.keys = arkKeys.array;
    Converter::ArkArrayHolder<Array_String> vecValueHolder(value);
    auto arkValues = vecValueHolder.ArkValue();
    map.values = arkValues.array;
    Ark_NativeEmbedInfo arkInfo = Converter::ArkValue<Ark_NativeEmbedInfo>(emebdInfo);
    arkInfo.params = Converter::ArkValue<Opt_Map_String_String>(map);
    parameter.info = Converter::ArkValue<Opt_NativeEmbedInfo>(arkInfo);
    parameter.status = Converter::ArkValue<Opt_NativeEmbedStatus>(eventInfo->GetStatus());
    parameter.surfaceId = Converter::ArkValue<Opt_String>(eventInfo->GetSurfaceId());
    auto arkCallback = CallbackHelper(*valueInfo);
    arkCallback.Invoke(parameter);
}

void OnNativeEmbedVisibilityChange(const OnNativeEmbedVisibilityChangeCallback* value,
    int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto* eventInfo = TypeInfoHelper::DynamicCast<NativeEmbedVisibilityInfo>(info);
    CHECK_NULL_VOID(eventInfo);
    Ark_NativeEmbedVisibilityInfo parameter;
    parameter.embedId = Converter::ArkValue<Ark_String>(eventInfo->GetEmbedId());
    parameter.visibility = Converter::ArkValue<Ark_Boolean>(eventInfo->GetVisibility());
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(parameter);
}

void OnNativeEmbedTouchInfo(const Callback_NativeEmbedTouchInfo_Void* value,
    int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto* eventInfo = TypeInfoHelper::DynamicCast<NativeEmbeadTouchInfo>(info);
    CHECK_NULL_VOID(eventInfo);
    Ark_NativeEmbedTouchInfo parameter;
    parameter.embedId = Converter::ArkValue<Opt_String>(eventInfo->GetEmbedId());
    auto touchEventInfo = eventInfo->GetTouchEventInfo();
    Ark_TouchEvent touchEvent = Converter::ArkValue<Ark_TouchEvent>(touchEventInfo);
    std::list<TouchLocationInfo> touches = touchEventInfo.GetTouches();
    std::vector<TouchLocationInfo> vTouches { std::begin(touches), std::end(touches) };
    Converter::ArkArrayHolder<Array_TouchObject> touchesHolder(vTouches);
    touchEvent.touches = touchesHolder.ArkValue();
    std::list<TouchLocationInfo> changedTouches = touchEventInfo.GetChangedTouches();
    std::vector<TouchLocationInfo> vChangedTouches { std::begin(changedTouches), std::end(changedTouches) };
    Converter::ArkArrayHolder<Array_TouchObject> changedTouchesHolder(vChangedTouches);
    touchEvent.changedTouches = changedTouchesHolder.ArkValue();
    parameter.touchEvent = Converter::ArkValue<Opt_TouchEvent>(touchEvent);
    Ark_EventResult arkEventResult;
    auto peer = new EventResultPeer();
    peer->handler = eventInfo->GetResult();
    arkEventResult.ptr = peer;
    parameter.result = Converter::ArkValue<Opt_EventResult>(arkEventResult);
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(parameter);
}

bool OnOverrideUrlLoading(const OnOverrideUrlLoadingCallback* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<LoadOverrideEvent>(info);
    CHECK_NULL_RETURN(eventInfo, false);
    Ark_WebResourceRequest parameter;
    auto peer = new WebResourceRequestPeer();
    peer->webRequest = eventInfo->GetRequest();
    parameter.ptr = peer;
    Callback_Boolean_Void continuation;
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(parameter, continuation);
    LOGE("WebAttributeModifier::OnOverrideUrlLoadingImpl return value can be incorrect");
    return false;
}

void OnRenderProcessNotResponding(const OnRenderProcessNotRespondingCallback* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<RenderProcessNotRespondingEvent>(info);
    CHECK_NULL_VOID(eventInfo);
    Ark_RenderProcessNotRespondingData parameter;
    parameter.jsStack = Converter::ArkValue<Ark_String>(eventInfo->GetJsStack());
    parameter.pid = Converter::ArkValue<Ark_Number>(eventInfo->GetPid());
    parameter.reason = Converter::ArkValue<Ark_RenderProcessNotRespondingReason>(
        static_cast<RenderProcessNotRespondingReason>(eventInfo->GetReason()));
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(parameter);
}

void OnRenderProcessResponding(const OnRenderProcessRespondingCallback* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke();
}

void OnViewportFitChanged(const OnViewportFitChangedCallback* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<ViewportFitChangedEvent>(info);
    CHECK_NULL_VOID(eventInfo);
    Ark_ViewportFit parameter = Converter::ArkValue<Ark_ViewportFit>(
        static_cast<ViewportFit>(eventInfo->GetViewportFit()));
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(parameter);
}

WebKeyboardOption OnWebKeyboard(const WebKeyboardCallback* valueCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    WebKeyboardOption opt;
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, opt);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<InterceptKeyboardEvent>(info);
    CHECK_NULL_RETURN(eventInfo, opt);
    Ark_WebKeyboardCallbackInfo parameter;
    auto peer = new WebKeyboardControllerPeer();
    peer->handler = eventInfo->GetCustomKeyboardHandler();
    parameter.controller.ptr = peer;

    Map_String_String attributes;
    auto attributesMap = eventInfo->GetAttributesMap();
    attributes.size = static_cast<Ark_Int32>(attributesMap.size());
    std::vector<std::string> key;
    std::vector<std::string> value;
    for (std::map<std::string, std::string>::iterator it = attributesMap.begin(); it != attributesMap.end(); ++it) {
        key.push_back(it->first);
        value.push_back(it->second);
    }
    Converter::ArkArrayHolder<Array_String> vecKeyHolder(key);
    auto arkKeys = vecKeyHolder.ArkValue();
    attributes.keys = arkKeys.array;
    Converter::ArkArrayHolder<Array_String> vecValueHolder(value);
    auto arkValues = vecValueHolder.ArkValue();
    attributes.values = arkValues.array;
    parameter.attributes = attributes;

    Callback_WebKeyboardOptions_Void continuation;
    auto arkCallback = CallbackHelper(*valueCallback);
    arkCallback.Invoke(parameter, continuation);
    LOGE("WebAttributeModifier::OnInterceptKeyboardAttachImpl return value can be incorrect");
    return opt;
}

void OnAdsBlocked(const OnAdsBlockedCallback* value,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<AdsBlockedEvent>(info);
    CHECK_NULL_VOID(eventInfo);
    Ark_AdsBlockedDetails parameter;
    parameter.url = Converter::ArkValue<Ark_String>(eventInfo->GetUrl());
    std::vector<std::string> adsBlocked = eventInfo->GetAdsBlocked();
    Converter::ArkArrayHolder<Array_String> adsBlockedHolder(adsBlocked);
    parameter.adsBlocked = adsBlockedHolder.ArkValue();
    auto arkCallback = CallbackHelper(*value);
    arkCallback.Invoke(parameter);
}

} // namespace OHOS::Ace::NG::GeneratedModifier::WebAttributeModifier
#endif // WEB_SUPPORTED