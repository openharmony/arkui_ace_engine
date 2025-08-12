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
#ifndef PREVIEW
#ifdef ARKUI_CAPI_UNITTEST
#include "base/image/pixel_map.h"
#include "test/unittest/capi/stubs/mock_image_source.h"
#else
#include "pixel_map.h"
#include "image_source.h"
#endif // ARKUI_CAPI_UNITTEST
#else
#include "image_source_preview.h"
#endif // PREVIEW

#include "core/components_ng/pattern/web/web_model_ng.h"
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
#include "core/interfaces/native/implementation/pixel_map_peer.h"
#include "core/interfaces/native/implementation/screen_capture_handler_peer_impl.h"
#include "core/interfaces/native/implementation/ssl_error_handler_peer_impl.h"
#include "core/interfaces/native/implementation/web_context_menu_param_peer_impl.h"
#include "core/interfaces/native/implementation/web_context_menu_result_peer_impl.h"
#include "core/interfaces/native/implementation/web_keyboard_controller_peer_impl.h"
#include "core/interfaces/native/implementation/web_resource_error_peer_impl.h"
#include "core/interfaces/native/implementation/web_resource_request_peer_impl.h"
#include "core/interfaces/native/implementation/web_resource_response_peer_impl.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG::GeneratedModifier::WebAttributeModifier {

void OnPageEnd(const CallbackHelper<Callback_OnPageEndEvent_Void>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<LoadWebPageFinishEvent>(info);
    CHECK_NULL_VOID(eventInfo);
    Ark_OnPageEndEvent parameter;
    parameter.url = Converter::ArkValue<Ark_String>(eventInfo->GetLoadedUrl());
    arkCallback.InvokeSync(parameter);
}

void OnPageBegin(const CallbackHelper<Callback_OnPageBeginEvent_Void>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<LoadWebPageStartEvent>(info);
    CHECK_NULL_VOID(eventInfo);
    Ark_OnPageBeginEvent parameter;
    parameter.url = Converter::ArkValue<Ark_String>(eventInfo->GetLoadedUrl());
    arkCallback.InvokeSync(parameter);
}

void OnProgressChange(const CallbackHelper<Callback_OnProgressChangeEvent_Void>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<LoadWebProgressChangeEvent>(info);
    CHECK_NULL_VOID(eventInfo);
    Ark_OnProgressChangeEvent parameter;
    parameter.newProgress = Converter::ArkValue<Ark_Number>(eventInfo->GetNewProgress());
    arkCallback.InvokeSync(parameter);
}

void OnTitleReceive(const CallbackHelper<Callback_OnTitleReceiveEvent_Void>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<LoadWebTitleReceiveEvent>(info);
    CHECK_NULL_VOID(eventInfo);
    Ark_OnTitleReceiveEvent parameter;
    parameter.title = Converter::ArkValue<Ark_String>(eventInfo->GetTitle());
    arkCallback.Invoke(parameter);
}

void OnGeolocationHide(const CallbackHelper<Callback_Void>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    arkCallback.Invoke();
}

void OnGeolocationShow(const CallbackHelper<Callback_OnGeolocationShowEvent_Void>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<LoadWebGeolocationShowEvent>(info);
    CHECK_NULL_VOID(eventInfo);
    Ark_OnGeolocationShowEvent parameter;
    parameter.origin = Converter::ArkValue<Ark_String>(eventInfo->GetOrigin());
    auto peer = new JsGeolocationPeer();
    peer->webGeolocation = eventInfo->GetWebGeolocation();
    parameter.geolocation = peer;
    arkCallback.Invoke(parameter);
}

void OnRequestSelected(const CallbackHelper<Callback_Void>& arkCallback,
    WeakPtr<FrameNode> weakNode, const BaseEventInfo* info)
{
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    arkCallback.Invoke();
}

bool OnAlert(const CallbackHelper<Callback_OnAlertEvent_Boolean>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    const auto refNode = weakNode.Upgrade();
    CHECK_NULL_RETURN(refNode, false);
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipelineContext, false);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<WebDialogEvent>(info);
    CHECK_NULL_RETURN(eventInfo, false);
    Ark_OnAlertEvent parameter;
    parameter.message = Converter::ArkValue<Ark_String>(eventInfo->GetMessage());
    parameter.url = Converter::ArkValue<Ark_String>(eventInfo->GetUrl());
    auto peer = new JsResultPeer();
    peer->result = eventInfo->GetResult();
    parameter.result = peer;
    const auto result = arkCallback.InvokeWithOptConvertResult<bool, Ark_Boolean, Callback_Boolean_Void>(parameter);
    return result.value_or(false);
}

bool OnBeforeUnload(const CallbackHelper<Callback_OnBeforeUnloadEvent_Boolean>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    const auto refNode = weakNode.Upgrade();
    CHECK_NULL_RETURN(refNode, false);
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipelineContext, false);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<WebDialogEvent>(info);
    CHECK_NULL_RETURN(eventInfo, false);
    Ark_OnBeforeUnloadEvent parameter;
    parameter.message = Converter::ArkValue<Ark_String>(eventInfo->GetMessage());
    parameter.url = Converter::ArkValue<Ark_String>(eventInfo->GetUrl());
    auto peer = new JsResultPeer();
    peer->result = eventInfo->GetResult();
    parameter.result = peer;
    const auto result = arkCallback.InvokeWithOptConvertResult<bool, Ark_Boolean, Callback_Boolean_Void>(parameter);
    return result.value_or(false);
}

bool OnConfirm(const CallbackHelper<Callback_OnConfirmEvent_Boolean>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    const auto refNode = weakNode.Upgrade();
    CHECK_NULL_RETURN(refNode, false);
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipelineContext, false);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<WebDialogEvent>(info);
    CHECK_NULL_RETURN(eventInfo, false);
    Ark_OnConfirmEvent parameter;
    parameter.message = Converter::ArkValue<Ark_String>(eventInfo->GetMessage());
    parameter.url = Converter::ArkValue<Ark_String>(eventInfo->GetUrl());
    auto peer = new JsResultPeer();
    peer->result = eventInfo->GetResult();
    parameter.result = peer;
    const auto result = arkCallback.InvokeWithOptConvertResult<bool, Ark_Boolean, Callback_Boolean_Void>(parameter);
    return result.value_or(false);
}

bool OnPrompt(const CallbackHelper<Callback_OnPromptEvent_Boolean>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    const auto refNode = weakNode.Upgrade();
    CHECK_NULL_RETURN(refNode, false);
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipelineContext, false);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<WebDialogEvent>(info);
    CHECK_NULL_RETURN(eventInfo, false);
    Ark_OnPromptEvent parameter;
    parameter.message = Converter::ArkValue<Ark_String>(eventInfo->GetMessage());
    parameter.url = Converter::ArkValue<Ark_String>(eventInfo->GetUrl());
    parameter.value = Converter::ArkValue<Ark_String>(eventInfo->GetValue());
    auto peer = new JsResultPeer();
    peer->result = eventInfo->GetResult();
    parameter.result = peer;
    const auto result = arkCallback.InvokeWithOptConvertResult<bool, Ark_Boolean, Callback_Boolean_Void>(parameter);
    return result.value_or(false);
}

bool OnConsole(const CallbackHelper<Callback_OnConsoleEvent_Boolean>& arkCallback,
    WeakPtr<FrameNode> weakNode, const BaseEventInfo* info)
{
    const auto refNode = weakNode.Upgrade();
    CHECK_NULL_RETURN(refNode, false);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipelineContext, false);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<LoadWebConsoleLogEvent>(info);
    CHECK_NULL_RETURN(eventInfo, false);
    Ark_OnConsoleEvent parameter;
    auto peer = new ConsoleMessagePeer();
    peer->webConsoleLog = eventInfo->GetMessage();
    parameter.message = peer;
    const auto result = arkCallback.InvokeWithOptConvertResult<bool, Ark_Boolean, Callback_Boolean_Void>(parameter);
    return result.value_or(false);
}

void OnErrorReceive(const CallbackHelper<Callback_OnErrorReceiveEvent_Void>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<ReceivedErrorEvent>(info);
    CHECK_NULL_VOID(eventInfo);
    Ark_OnErrorReceiveEvent parameter;
    auto errorPeer = new WebResourceErrorPeer();
    errorPeer->handler = eventInfo->GetError();
    parameter.error = errorPeer;
    auto requestPeer = new WebResourceRequestPeer();
    requestPeer->webRequest = eventInfo->GetRequest();
    parameter.request = requestPeer;
    arkCallback.InvokeSync(parameter);
}

void OnHttpErrorReceive(const CallbackHelper<Callback_OnHttpErrorReceiveEvent_Void>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<ReceivedHttpErrorEvent>(info);
    CHECK_NULL_VOID(eventInfo);
    Ark_OnHttpErrorReceiveEvent parameter;
    auto requestPeer = new WebResourceRequestPeer();
    requestPeer->webRequest = eventInfo->GetRequest();
    parameter.request = requestPeer;
    auto responsePeer = new WebResourceResponsePeer();
    responsePeer->handler = eventInfo->GetResponse();
    parameter.response = responsePeer;
    arkCallback.Invoke(parameter);
}

void OnDownloadStart(const CallbackHelper<Callback_OnDownloadStartEvent_Void>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
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
    arkCallback.Invoke(parameter);
}

void OnRefreshAccessedHistory(const CallbackHelper<Callback_OnRefreshAccessedHistoryEvent_Void>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<RefreshAccessedHistoryEvent>(info);
    CHECK_NULL_VOID(eventInfo);
    Ark_OnRefreshAccessedHistoryEvent parameter;
    parameter.url = Converter::ArkValue<Ark_String>(eventInfo->GetVisitedUrl());
    parameter.isRefreshed = Converter::ArkValue<Ark_Boolean>(eventInfo->IsRefreshed());
    arkCallback.Invoke(parameter);
}

bool OnUrlLoadIntercept(const CallbackHelper<Type_WebAttribute_onUrlLoadIntercept_callback>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    const auto refNode = weakNode.Upgrade();
    CHECK_NULL_RETURN(refNode, false);
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipelineContext, false);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<UrlLoadInterceptEvent>(info);
    CHECK_NULL_RETURN(eventInfo, false);
    Ark_Literal_Union_String_WebResourceRequest_data parameter;
    parameter.data = Converter::ArkUnion<Ark_Union_String_WebResourceRequest, Ark_String>(
        Converter::ArkValue<Ark_String>(eventInfo->GetData()));
    auto optParam = Converter::ArkValue<Opt_Literal_Union_String_WebResourceRequest_data>(parameter);
    const auto result = arkCallback.InvokeWithOptConvertResult<bool, Ark_Boolean, Callback_Boolean_Void>(optParam);
    return result.value_or(false);
}

void OnRenderExited(const CallbackHelper<Callback_OnRenderExitedEvent_Void>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<RenderExitedEvent>(info);
    CHECK_NULL_VOID(eventInfo);
    Ark_OnRenderExitedEvent parameter;
    parameter.renderExitReason = Converter::ArkValue<Ark_RenderExitReason>(
        static_cast<Converter::RenderExitReason>(eventInfo->GetExitedReason()));
    arkCallback.InvokeSync(parameter);
}

bool OnShowFileSelector(const CallbackHelper<Callback_OnShowFileSelectorEvent_Boolean>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    const auto refNode = weakNode.Upgrade();
    CHECK_NULL_RETURN(refNode, false);
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipelineContext, false);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<FileSelectorEvent>(info);
    CHECK_NULL_RETURN(eventInfo, false);
    Ark_OnShowFileSelectorEvent parameter;
    auto paramPeer = new FileSelectorParamPeer();
    paramPeer->handler = eventInfo->GetParam();
    parameter.fileSelector = paramPeer;
    auto resultPeer = new FileSelectorResultPeer();
    resultPeer->handler = eventInfo->GetFileSelectorResult();
    parameter.result = resultPeer;
    const auto result = arkCallback.InvokeWithOptConvertResult<bool, Ark_Boolean, Callback_Boolean_Void>(parameter);
    return result.value_or(false);
}

void OnResourceLoad(const CallbackHelper<Callback_OnResourceLoadEvent_Void>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<ResourceLoadEvent>(info);
    CHECK_NULL_VOID(eventInfo);
    Ark_OnResourceLoadEvent parameter;
    parameter.url = Converter::ArkValue<Ark_String>(eventInfo->GetOnResourceLoadUrl());
    arkCallback.Invoke(parameter);
}

void OnFullScreenExit(const CallbackHelper<Callback_Void>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    arkCallback.Invoke();
}

void OnFullScreenEnter(const CallbackHelper<OnFullScreenEnterCallback>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<FullScreenEnterEvent>(info);
    CHECK_NULL_VOID(eventInfo);
    Ark_FullScreenEnterEvent parameter;
    parameter.videoWidth = Converter::ArkValue<Opt_Number>(eventInfo->GetVideoNaturalWidth());
    parameter.videoHeight = Converter::ArkValue<Opt_Number>(eventInfo->GetVideoNaturalHeight());
    auto peer = new FullScreenExitHandlerPeer();
    peer->handler = eventInfo->GetHandler();
    parameter.handler = peer;
    arkCallback.Invoke(parameter);
}

void OnScaleChange(const CallbackHelper<Callback_OnScaleChangeEvent_Void>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<ScaleChangeEvent>(info);
    CHECK_NULL_VOID(eventInfo);
    Ark_OnScaleChangeEvent parameter;
    parameter.newScale = Converter::ArkValue<Ark_Number>(eventInfo->GetOnScaleChangeNewScale());
    parameter.oldScale = Converter::ArkValue<Ark_Number>(eventInfo->GetOnScaleChangeOldScale());
    arkCallback.Invoke(parameter);
}

bool OnHttpAuthRequest(const CallbackHelper<Callback_OnHttpAuthRequestEvent_Boolean>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    const auto refNode = weakNode.Upgrade();
    CHECK_NULL_RETURN(refNode, false);
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipelineContext, false);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<WebHttpAuthEvent>(info);
    CHECK_NULL_RETURN(eventInfo, false);
    Ark_OnHttpAuthRequestEvent parameter;
    parameter.host = Converter::ArkValue<Ark_String>(eventInfo->GetHost());
    parameter.realm = Converter::ArkValue<Ark_String>(eventInfo->GetRealm());
    auto peer = new HttpAuthHandlerPeer();
    peer->handler = eventInfo->GetResult();
    parameter.handler = peer;
    const auto result = arkCallback.InvokeWithOptConvertResult<bool, Ark_Boolean, Callback_Boolean_Void>(parameter);
    return result.value_or(false);
}

RefPtr<WebResponse> OnInterceptRequest(
    const CallbackHelper<Callback_OnInterceptRequestEvent_WebResourceResponse>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    const auto refNode = weakNode.Upgrade();
    CHECK_NULL_RETURN(refNode, nullptr);
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipelineContext, nullptr);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<OnInterceptRequestEvent>(info);
    CHECK_NULL_RETURN(eventInfo, nullptr);
    Ark_OnInterceptRequestEvent parameter;
    auto peer = new WebResourceRequestPeer();
    peer->webRequest = eventInfo->GetRequest();
    parameter.request = peer;
    const auto arkResult = arkCallback.InvokeWithObtainResult<Ark_WebResourceResponse,
        Callback_WebResourceResponse_Void>(parameter);
    CHECK_NULL_RETURN(arkResult, nullptr);
    return arkResult->handler;
}

void OnPermissionRequest(const CallbackHelper<Callback_OnPermissionRequestEvent_Void>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<WebPermissionRequestEvent>(info);
    CHECK_NULL_VOID(eventInfo);
    Ark_OnPermissionRequestEvent parameter;
    auto peer = new PermissionRequestPeer();
    peer->handler = eventInfo->GetWebPermissionRequest();
    parameter.request = peer;
    arkCallback.Invoke(parameter);
}

void OnScreenCaptureRequest(const CallbackHelper<Callback_OnScreenCaptureRequestEvent_Void>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<WebScreenCaptureRequestEvent>(info);
    CHECK_NULL_VOID(eventInfo);
    Ark_OnScreenCaptureRequestEvent parameter;
    auto peer = new ScreenCaptureHandlerPeer();
    peer->handler = eventInfo->GetWebScreenCaptureRequest();
    parameter.handler = peer;
    arkCallback.Invoke(parameter);
}

bool OnContextMenuShow(const CallbackHelper<Callback_OnContextMenuShowEvent_Boolean>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    const auto refNode = weakNode.Upgrade();
    CHECK_NULL_RETURN(refNode, false);
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipelineContext, false);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<ContextMenuEvent>(info);
    CHECK_NULL_RETURN(eventInfo, false);
    Ark_OnContextMenuShowEvent parameter;
    auto paramPeer = new WebContextMenuParamPeer();
    paramPeer->handler = eventInfo->GetParam();
    parameter.param = paramPeer;
    auto resultPeer = new WebContextMenuResultPeer();
    resultPeer->handler = eventInfo->GetContextMenuResult();
    parameter.result = resultPeer;
    const auto result = arkCallback.InvokeWithOptConvertResult<bool, Ark_Boolean, Callback_Boolean_Void>(parameter);
    return result.value_or(false);
}

void OnContextMenuHide(const CallbackHelper<OnContextMenuHideCallback>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    arkCallback.Invoke();
}

void OnSearchResultReceive(const CallbackHelper<Callback_OnSearchResultReceiveEvent_Void>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<SearchResultReceiveEvent>(info);
    CHECK_NULL_VOID(eventInfo);
    Ark_OnSearchResultReceiveEvent parameter;
    parameter.activeMatchOrdinal = Converter::ArkValue<Ark_Number>(eventInfo->GetActiveMatchOrdinal());
    parameter.numberOfMatches = Converter::ArkValue<Ark_Number>(eventInfo->GetNumberOfMatches());
    parameter.isDoneCounting = Converter::ArkValue<Ark_Boolean>(eventInfo->GetIsDoneCounting());
    arkCallback.Invoke(parameter);
}

void OnScroll(const CallbackHelper<Callback_OnScrollEvent_Void>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<WebOnScrollEvent>(info);
    CHECK_NULL_VOID(eventInfo);
    Ark_OnScrollEvent parameter;
    parameter.xOffset = Converter::ArkValue<Ark_Number>(eventInfo->GetX());
    parameter.yOffset = Converter::ArkValue<Ark_Number>(eventInfo->GetY());
    arkCallback.Invoke(parameter);
}

bool OnSslErrorEventReceive(const CallbackHelper<Callback_OnSslErrorEventReceiveEvent_Void>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipelineContext, false);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<WebSslErrorEvent>(info);
    CHECK_NULL_RETURN(eventInfo, false);
    Ark_OnSslErrorEventReceiveEvent parameter;
    parameter.error = Converter::ArkValue<Ark_SslError>(static_cast<Converter::SslError>(eventInfo->GetError()));
    Converter::ArkArrayHolder<Array_Buffer> vecHolder(eventInfo->GetCertChainData());
    auto tempValue = vecHolder.ArkValue();
    parameter.certChainData = Converter::ArkValue<Opt_Array_Buffer>(tempValue);
    auto peer = new SslErrorHandlerPeer();
    peer->handler = eventInfo->GetResult();
    parameter.handler = peer;
    arkCallback.Invoke(parameter);
    return true;
}

bool OnSslError(const CallbackHelper<OnSslErrorEventCallback>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    // ContainerScope scope(instanceId);
    // auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    // CHECK_NULL_RETURN(pipelineContext, false);
    // pipelineContext->UpdateCurrentActiveNode(weakNode);
    // auto* eventInfo = TypeInfoHelper::DynamicCast<WebAllSslErrorEvent>(info);
    // CHECK_NULL_RETURN(eventInfo, false);
    // Ark_SslErrorEvent parameter;
    // parameter.error = Converter::ArkValue<Ark_SslError>(static_cast<Converter::SslError>(eventInfo->GetError()));
    // parameter.isFatalError = Converter::ArkValue<Ark_Boolean>(eventInfo->GetIsFatalError());
    // parameter.isMainFrame = Converter::ArkValue<Ark_Boolean>(eventInfo->GetIsMainFrame());
    // auto original = eventInfo->GetOriginalUrl();
    // parameter.originalUrl = Converter::ArkValue<Ark_String>(original);
    // auto referrer = eventInfo->GetReferrer();
    // parameter.referrer = Converter::ArkValue<Ark_String>(referrer);
    // auto url = eventInfo->GetUrl();
    // parameter.url = Converter::ArkValue<Ark_String>(url);
    // auto peer = new SslErrorHandlerPeer();
    // // need check
    // peer->handler = eventInfo->GetResult();
    // parameter.handler = peer;
    // arkCallback.Invoke(parameter);
    return true;
}

bool OnClientAuthentication(const CallbackHelper<Callback_OnClientAuthenticationEvent_Void>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
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
    parameter.handler = peer;
    arkCallback.Invoke(parameter);
    return false;
}

static bool HandleWindowNewEvent(const WebWindowNewEvent* eventInfo)
{
    auto handler = eventInfo->GetWebWindowNewHandler();
    if ((handler) && (!handler->IsFrist())) {
        int32_t parentId = -1;
        auto controllerInfo = ControllerHandlerPeer::PopController(handler->GetId(), &parentId);
        if (controllerInfo.getWebIdFunc) {
            handler->SetWebController(controllerInfo.getWebIdFunc());
        }
        if (controllerInfo.completeWindowNewFunc) {
            controllerInfo.completeWindowNewFunc(parentId);
        }
        if (controllerInfo.releaseRefFunc) {
            controllerInfo.releaseRefFunc();
        }
        return false;
    }
    return true;
}

void OnWindowNew(const CallbackHelper<Callback_OnWindowNewEvent_Void>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const std::shared_ptr<BaseEventInfo>& info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<WebWindowNewEvent>(info.get());
    CHECK_NULL_VOID(eventInfo);
    if (!HandleWindowNewEvent(eventInfo)) {
        return;
    }
    Ark_OnWindowNewEvent parameter;
    parameter.isAlert = Converter::ArkValue<Ark_Boolean>(eventInfo->IsAlert());
    parameter.isUserTrigger = Converter::ArkValue<Ark_Boolean>(eventInfo->IsUserTrigger());
    parameter.targetUrl = Converter::ArkValue<Ark_String>(eventInfo->GetTargetUrl());
    auto peer = new ControllerHandlerPeer();
    peer->handler = eventInfo->GetWebWindowNewHandler();
    parameter.handler = peer;
    arkCallback.InvokeSync(parameter);
}

void OnWindowExit(const CallbackHelper<Callback_Void>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    arkCallback.InvokeSync();
}

bool OnInterceptKey(const CallbackHelper<Callback_KeyEvent_Boolean>& arkCallback,
    WeakPtr<FrameNode> weakNode, KeyEventInfo& keyEventInfo)
{
    const auto refNode = weakNode.Upgrade();
    CHECK_NULL_RETURN(refNode, false);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipelineContext, false);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    const auto event = Converter::ArkKeyEventSync(keyEventInfo);
    const auto result = arkCallback.InvokeWithOptConvertResult<bool, Ark_Boolean, Callback_Boolean_Void>(
        event.ArkValue());
    return result.value_or(false);
}

void OnTouchIconUrlReceived(const CallbackHelper<Callback_OnTouchIconUrlReceivedEvent_Void>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const std::shared_ptr<BaseEventInfo>& info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
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

Media::PixelFormat GetPixelFormat(NG::TransImageColorType colorType)
{
    Media::PixelFormat pixelFormat;
    switch (colorType) {
        case NG::TransImageColorType::COLOR_TYPE_UNKNOWN:
            pixelFormat = Media::PixelFormat::UNKNOWN;
            break;
        case NG::TransImageColorType::COLOR_TYPE_RGBA_8888:
            pixelFormat = Media::PixelFormat::RGBA_8888;
            break;
        case NG::TransImageColorType::COLOR_TYPE_BGRA_8888:
            pixelFormat = Media::PixelFormat::BGRA_8888;
            break;
        default:
            pixelFormat = Media::PixelFormat::UNKNOWN;
            break;
    }
    return pixelFormat;
}

Media::AlphaType GetAlphaType(NG::TransImageAlphaType alphaType)
{
    Media::AlphaType imageAlphaType;
    switch (alphaType) {
        case NG::TransImageAlphaType::ALPHA_TYPE_UNKNOWN:
            imageAlphaType = Media::AlphaType::IMAGE_ALPHA_TYPE_UNKNOWN;
            break;
        case NG::TransImageAlphaType::ALPHA_TYPE_OPAQUE:
            imageAlphaType = Media::AlphaType::IMAGE_ALPHA_TYPE_OPAQUE;
            break;
        case NG::TransImageAlphaType::ALPHA_TYPE_PREMULTIPLIED:
            imageAlphaType = Media::AlphaType::IMAGE_ALPHA_TYPE_PREMUL;
            break;
        case NG::TransImageAlphaType::ALPHA_TYPE_POSTMULTIPLIED:
            imageAlphaType = Media::AlphaType::IMAGE_ALPHA_TYPE_UNPREMUL;
            break;
        default:
            imageAlphaType = Media::AlphaType::IMAGE_ALPHA_TYPE_UNKNOWN;
            break;
    }
    return imageAlphaType;
}

void OnFaviconReceived(const CallbackHelper<Callback_OnFaviconReceivedEvent_Void>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const std::shared_ptr<BaseEventInfo>& info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto func = [arkCallback, info]() {
        Ark_OnFaviconReceivedEvent parameter;
        auto* eventInfo = TypeInfoHelper::DynamicCast<FaviconReceivedEvent>(info.get());
        auto data = eventInfo->GetHandler()->GetData();
        size_t width = eventInfo->GetHandler()->GetWidth();
        size_t height = eventInfo->GetHandler()->GetHeight();
        int colorType = eventInfo->GetHandler()->GetColorType();
        int alphaType = eventInfo->GetHandler()->GetAlphaType();

        Media::InitializationOptions opt;
        opt.size.width = static_cast<int32_t>(width);
        opt.size.height = static_cast<int32_t>(height);
        opt.pixelFormat = GetPixelFormat(NG::TransImageColorType(colorType));
        opt.alphaType = GetAlphaType(NG::TransImageAlphaType(alphaType));
        opt.editable = true;
        auto pixelMap = Media::PixelMap::Create(opt);
        CHECK_NULL_VOID(pixelMap);
        uint32_t stride = width << 2;
        uint64_t bufferSize = stride * height;
        pixelMap->WritePixels(static_cast<const uint8_t*>(data), bufferSize);
        parameter.favicon = PeerUtils::CreatePeer<PixelMapPeer>();
        CHECK_NULL_VOID(parameter.favicon);
        parameter.favicon->pixelMap = PixelMap::Create(std::move(pixelMap));
        CHECK_NULL_VOID(parameter.favicon->pixelMap);
        LOGE("WebAttributeModifier::OnFaviconReceivedImpl PixelMap supporting is not implemented yet");
        arkCallback.Invoke(parameter);
    };
#ifdef ARKUI_CAPI_UNITTEST
    func();
#else
    pipelineContext->PostAsyncEvent([func]() { func(); }, "ArkUIWebFaviconReceived");
#endif // ARKUI_CAPI_UNITTEST
}

void OnPageVisible(const CallbackHelper<Callback_OnPageVisibleEvent_Void>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const std::shared_ptr<BaseEventInfo>& info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto func = [arkCallback, info]() {
        auto* eventInfo = TypeInfoHelper::DynamicCast<PageVisibleEvent>(info.get());
        CHECK_NULL_VOID(eventInfo);
        Ark_OnPageVisibleEvent parameter;
        parameter.url = Converter::ArkValue<Ark_String>(eventInfo->GetUrl());
        arkCallback.InvokeSync(parameter);
    };
#ifdef ARKUI_CAPI_UNITTEST
    func();
#else
    pipelineContext->PostAsyncEvent([func]() { func(); }, "ArkUIWebPageVisible");
#endif // ARKUI_CAPI_UNITTEST
}

void OnDataResubmitted(const CallbackHelper<Callback_OnDataResubmittedEvent_Void>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const std::shared_ptr<BaseEventInfo>& info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto func = [arkCallback, info]() {
        auto* eventInfo = TypeInfoHelper::DynamicCast<DataResubmittedEvent>(info.get());
        CHECK_NULL_VOID(eventInfo);
        Ark_OnDataResubmittedEvent parameter;
        auto peer = new DataResubmissionHandlerPeer();
        peer->handler = eventInfo->GetHandler();
        parameter.handler = peer;
        arkCallback.Invoke(parameter);
    };
#ifdef ARKUI_CAPI_UNITTEST
    func();
#else
    pipelineContext->PostAsyncEvent([func]() { func(); }, "ArkUIWebDataResubmitted");
#endif // ARKUI_CAPI_UNITTEST
}

void OnAudioStateChanged(const CallbackHelper<Callback_OnAudioStateChangedEvent_Void>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const std::shared_ptr<BaseEventInfo>& info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<AudioStateChangedEvent>(info.get());
    CHECK_NULL_VOID(eventInfo);
    Ark_OnAudioStateChangedEvent parameter;
    parameter.playing = Converter::ArkValue<Ark_Boolean>(eventInfo->IsPlaying());
    arkCallback.Invoke(parameter);
}

void OnFirstContentfulPaint(const CallbackHelper<Callback_OnFirstContentfulPaintEvent_Void>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const std::shared_ptr<BaseEventInfo>& info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
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

void OnFirstMeaningfulPaint(const CallbackHelper<OnFirstMeaningfulPaintCallback>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const std::shared_ptr<BaseEventInfo>& info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
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

void OnLargestContentfulPaint(const CallbackHelper<OnLargestContentfulPaintCallback>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const std::shared_ptr<BaseEventInfo>& info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
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

bool OnLoadIntercept(const CallbackHelper<Callback_OnLoadInterceptEvent_Boolean>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    const auto refNode = weakNode.Upgrade();
    CHECK_NULL_RETURN(refNode, false);
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipelineContext, false);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<LoadInterceptEvent>(info);
    CHECK_NULL_RETURN(eventInfo, false);
    Ark_OnLoadInterceptEvent parameter;
    auto peer = new WebResourceRequestPeer();
    peer->webRequest = eventInfo->GetRequest();
    parameter.data = peer;
    const auto result = arkCallback.InvokeWithOptConvertResult<bool, Ark_Boolean, Callback_Boolean_Void>(parameter);
    return result.value_or(false);
}

void OnControllerAttached(const CallbackHelper<Callback_Void>& arkCallback,
                          WeakPtr<FrameNode> weakNode, int32_t instanceId)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto func = [arkCallback]() {
        arkCallback.Invoke();
    };
#ifdef ARKUI_CAPI_UNITTEST
    func();
#else
    pipelineContext->PostAsyncEvent([func]() { func(); }, "ArkUIWebControllerAttached");
#endif // ARKUI_CAPI_UNITTEST
}

void OnOverScroll(const CallbackHelper<Callback_OnOverScrollEvent_Void>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<WebOnOverScrollEvent>(info);
    CHECK_NULL_VOID(eventInfo);
    Ark_OnOverScrollEvent parameter;
    parameter.xOffset = Converter::ArkValue<Ark_Number>(eventInfo->GetX());
    parameter.yOffset = Converter::ArkValue<Ark_Number>(eventInfo->GetY());
    arkCallback.Invoke(parameter);
}

void OnSafeBrowsingCheckResult(const CallbackHelper<OnSafeBrowsingCheckResultCallback>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const std::shared_ptr<BaseEventInfo>& info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
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

void OnNavigationEntryCommitted(const CallbackHelper<OnNavigationEntryCommittedCallback>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const std::shared_ptr<BaseEventInfo>& info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
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

void OnIntelligentTrackingPrevention(const CallbackHelper<OnIntelligentTrackingPreventionCallback>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const std::shared_ptr<BaseEventInfo>& info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
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

void OnNativeEmbedDataInfo(const CallbackHelper<Callback_NativeEmbedDataInfo_Void>& arkCallback,
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
    arkCallback.InvokeSync(parameter);
}

void OnNativeEmbedVisibilityChange(const CallbackHelper<OnNativeEmbedVisibilityChangeCallback>& arkCallback,
    int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto* eventInfo = TypeInfoHelper::DynamicCast<NativeEmbedVisibilityInfo>(info);
    CHECK_NULL_VOID(eventInfo);
    Ark_NativeEmbedVisibilityInfo parameter;
    parameter.embedId = Converter::ArkValue<Ark_String>(eventInfo->GetEmbedId());
    parameter.visibility = Converter::ArkValue<Ark_Boolean>(eventInfo->GetVisibility());
    arkCallback.InvokeSync(parameter);
}

void OnNativeEmbedTouchInfo(const CallbackHelper<Callback_NativeEmbedTouchInfo_Void>& arkCallback,
    int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto* eventInfo = TypeInfoHelper::DynamicCast<NativeEmbeadTouchInfo>(info);
    CHECK_NULL_VOID(eventInfo);
    Ark_NativeEmbedTouchInfo parameter;
    parameter.embedId = Converter::ArkValue<Opt_String>(eventInfo->GetEmbedId());
    auto touchEventInfo = eventInfo->GetTouchEventInfo();
    const auto event = Converter::ArkTouchEventSync(touchEventInfo);
    parameter.touchEvent = Converter::ArkValue<Opt_TouchEvent>(event.ArkValue());
    Ark_EventResult arkEventResult;
    auto peer = new EventResultPeer();
    peer->handler = eventInfo->GetResult();
    arkEventResult = peer;
    parameter.result = Converter::ArkValue<Opt_EventResult>(arkEventResult);
    arkCallback.InvokeSync(parameter);
}

bool OnOverrideUrlLoading(const CallbackHelper<OnOverrideUrlLoadingCallback>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    const auto refNode = weakNode.Upgrade();
    CHECK_NULL_RETURN(refNode, false);
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipelineContext, false);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<LoadOverrideEvent>(info);
    CHECK_NULL_RETURN(eventInfo, false);
    Ark_WebResourceRequest parameter;
    auto peer = new WebResourceRequestPeer();
    peer->webRequest = eventInfo->GetRequest();
    parameter = peer;
    const auto result = arkCallback.InvokeWithOptConvertResult<bool, Ark_Boolean, Callback_Boolean_Void>(parameter);
    return result.value_or(false);
}

void OnRenderProcessNotResponding(const CallbackHelper<OnRenderProcessNotRespondingCallback>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<RenderProcessNotRespondingEvent>(info);
    CHECK_NULL_VOID(eventInfo);
    Ark_RenderProcessNotRespondingData parameter;
    parameter.jsStack = Converter::ArkValue<Ark_String>(eventInfo->GetJsStack());
    parameter.pid = Converter::ArkValue<Ark_Number>(eventInfo->GetPid());
    parameter.reason = Converter::ArkValue<Ark_RenderProcessNotRespondingReason>(
        static_cast<RenderProcessNotRespondingReason>(eventInfo->GetReason()));
    arkCallback.InvokeSync(parameter);
}

void OnRenderProcessResponding(const CallbackHelper<OnRenderProcessRespondingCallback>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    arkCallback.InvokeSync();
}

void OnViewportFitChanged(const CallbackHelper<OnViewportFitChangedCallback>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<ViewportFitChangedEvent>(info);
    CHECK_NULL_VOID(eventInfo);
    Ark_ViewportFit parameter = Converter::ArkValue<Ark_ViewportFit>(
        static_cast<ViewportFit>(eventInfo->GetViewportFit()));
    arkCallback.InvokeSync(parameter);
}

WebKeyboardOption OnWebKeyboard(const CallbackHelper<WebKeyboardCallback>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    WebKeyboardOption opt;
    const auto refNode = weakNode.Upgrade();
    CHECK_NULL_RETURN(refNode, opt);
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipelineContext, opt);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<InterceptKeyboardEvent>(info);
    CHECK_NULL_RETURN(eventInfo, opt);
    Ark_WebKeyboardCallbackInfo parameter;
    auto peer = new WebKeyboardControllerPeer();
    peer->handler = eventInfo->GetCustomKeyboardHandler();
    parameter.controller = peer;

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

    auto frameNode = Referenced::RawPtr(refNode);
    const auto arkResult = arkCallback.InvokeWithObtainResult<Ark_WebKeyboardOptions,
        Callback_WebKeyboardOptions_Void>(parameter);
    opt.isSystemKeyboard_ = Converter::Convert<bool>(arkResult.useSystemKeyboard);
    if (auto enterKeyType = Converter::OptConvert<int32_t>(arkResult.enterKeyType); enterKeyType) {
        opt.enterKeyTpye_ = enterKeyType.value();
    }
    if (auto optBuilder = Converter::OptConvert<CustomNodeBuilder>(arkResult.customKeyboard); optBuilder) {
        opt.customKeyboardBuilder_ = [
            callback = CallbackHelper(optBuilder.value()),
            node = reinterpret_cast<Ark_NativePointer>(frameNode)
        ]() {
            auto builderNode = callback.BuildSync(node);
            NG::ViewStackProcessor::GetInstance()->Push(builderNode);
        };
    }
    return opt;
}

void OnAdsBlocked(const CallbackHelper<OnAdsBlockedCallback>& arkCallback,
    WeakPtr<FrameNode> weakNode, int32_t instanceId, const BaseEventInfo* info)
{
    ContainerScope scope(instanceId);
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->UpdateCurrentActiveNode(weakNode);
    auto* eventInfo = TypeInfoHelper::DynamicCast<AdsBlockedEvent>(info);
    CHECK_NULL_VOID(eventInfo);
    Ark_AdsBlockedDetails parameter;
    parameter.url = Converter::ArkValue<Ark_String>(eventInfo->GetUrl());
    std::vector<std::string> adsBlocked = eventInfo->GetAdsBlocked();
    Converter::ArkArrayHolder<Array_String> adsBlockedHolder(adsBlocked);
    parameter.adsBlocked = adsBlockedHolder.ArkValue();
    arkCallback.Invoke(parameter);
}

} // namespace OHOS::Ace::NG::GeneratedModifier::WebAttributeModifier
#endif // WEB_SUPPORTED

