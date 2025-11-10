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

#include "web_ani_modifier.h"

#include "base/log/log.h"
#include "core/components_ng/base/frame_node.h"
#ifdef WEB_SUPPORTED
#include "core/components_ng/pattern/web/ani/web_model_static.h"
#include "core/interfaces/native/implementation/controller_handler_peer_impl.h"
#include "core/interfaces/native/implementation/file_selector_param_peer_impl.h"
#include "core/interfaces/native/implementation/file_selector_result_peer_impl.h"
#include "core/interfaces/native/implementation/js_geolocation_peer_impl.h"
#include "core/interfaces/native/implementation/js_result_peer_impl.h"
#include "core/interfaces/native/implementation/screen_capture_handler_peer_impl.h"
#include "core/interfaces/native/implementation/event_result_peer_impl.h"
#include "core/interfaces/native/implementation/web_context_menu_param_peer_impl.h"
#include "core/interfaces/native/implementation/web_context_menu_result_peer_impl.h"
#include "core/interfaces/native/implementation/http_auth_handler_peer_impl.h"
#include "core/interfaces/native/implementation/web_resource_response_peer_impl.h"
#include "core/interfaces/native/implementation/web_resource_request_peer_impl.h"
#include "core/interfaces/native/implementation/console_message_peer_impl.h"
#include "core/interfaces/native/implementation/data_resubmission_handler_peer_impl.h"
#include "core/interfaces/native/implementation/client_authentication_handler_peer_impl.h"
#include "core/interfaces/native/implementation/ssl_error_handler_peer_impl.h"
#include "core/interfaces/native/implementation/permission_request_peer_impl.h"
#include "core/interfaces/native/implementation/controller_handler_peer_impl.h"
#include "core/interfaces/native/implementation/web_keyboard_controller_peer_impl.h"
#include "core/components/web/web_transfer_api.h"
#endif

namespace OHOS::Ace::NG {

bool TransferScreenCaptureHandlerToStatic(void* peer, void* nativePtr)
{
#ifdef WEB_SUPPORTED
    auto* objectPeer = reinterpret_cast<ScreenCaptureHandlerPeer *>(peer);
    CHECK_NULL_RETURN(objectPeer, false);
    auto* transfer = reinterpret_cast<WebTransferBase<RefPtr<WebScreenCaptureRequest>>*>(nativePtr);
    CHECK_NULL_RETURN(transfer, false);
    objectPeer->handler = transfer->get<0>();
    return true;
#else
    return false;
#endif // WEB_SUPPORTED
}
 
napi_value  TransferScreenCaptureHandlerToDynamic(napi_env env, void* peer)
{
#ifdef WEB_SUPPORTED
    auto* objectPeer = reinterpret_cast<ScreenCaptureHandlerPeer *>(peer);
    CHECK_NULL_RETURN(objectPeer, nullptr);
    return OHOS::Ace::Framework::CreateJSScreenCaptureRequestObject(env, objectPeer->handler);
#else
    return nullptr;
#endif // WEB_SUPPORTED
}

bool TransferJsResultToStatic(void* peer, void* nativePtr)
{
#ifdef WEB_SUPPORTED
    auto* objectPeer = reinterpret_cast<JsResultPeer *>(peer);
    CHECK_NULL_RETURN(objectPeer, false);
    auto* transfer = reinterpret_cast<WebTransferBase<RefPtr<Result>>*>(nativePtr);
    CHECK_NULL_RETURN(transfer, false);
    objectPeer->result = transfer->get<0>();
    return true;
#else
    return false;
#endif // WEB_SUPPORTED
}

bool TransferJsGeolocationToStatic(void* peer, void* nativePtr)
{
#ifdef WEB_SUPPORTED
    auto* objectPeer = reinterpret_cast<JsGeolocationPeer *>(peer);
    CHECK_NULL_RETURN(objectPeer, false);
    auto* transfer = reinterpret_cast<WebTransferBase<RefPtr<WebGeolocation>>*>(nativePtr);
    CHECK_NULL_RETURN(transfer, false);
    objectPeer->webGeolocation = transfer->get<0>();
    return true;
#else
    return false;
#endif // WEB_SUPPORTED
}

napi_value TransferJsGeolocationToDynamic(napi_env env, void* peer)
{
#ifdef WEB_SUPPORTED
    auto* objectPeer = reinterpret_cast<JsGeolocationPeer *>(peer);
    CHECK_NULL_RETURN(objectPeer, nullptr);
    return OHOS::Ace::Framework::CreateJSWebGeolocationObject(env, objectPeer->webGeolocation);
#else
    return nullptr;
#endif // WEB_SUPPORTED
}

napi_value TransferJsResultToDynamic(napi_env env, void* peer)
{
#ifdef WEB_SUPPORTED
    auto* objectPeer = reinterpret_cast<JsResultPeer *>(peer);
    CHECK_NULL_RETURN(objectPeer, nullptr);
    return OHOS::Ace::Framework::CreateJSWebDialogObject(env, objectPeer->result);
#else
    return nullptr;
#endif // WEB_SUPPORTED
}

bool TransferEventResultToStatic(void* peer, void* nativePtr)
{
#ifdef WEB_SUPPORTED
    auto* objectPeer = reinterpret_cast<EventResultPeer *>(peer);
    CHECK_NULL_RETURN(objectPeer, false);
    auto* transfer = reinterpret_cast<WebTransferBase<RefPtr<GestureEventResult>>*>(nativePtr);
    CHECK_NULL_RETURN(transfer, false);
    objectPeer->handler = transfer->get<0>();
    return true;
#else
    return false;
#endif // WEB_SUPPORTED
}

napi_value TransferEventResultToDynamic(napi_env env, void* peer)
{
#ifdef WEB_SUPPORTED
    auto* objectPeer = reinterpret_cast<EventResultPeer *>(peer);
    CHECK_NULL_RETURN(objectPeer, nullptr);
    if (objectPeer->handler.has_value()) {
        auto& variant = objectPeer->handler.value();
        if (auto gestureResult = std::get_if<RefPtr<GestureEventResult>>(&variant)) {
            if (*gestureResult) {
                return OHOS::Ace::Framework::CreateJSNativeEmbedGestureRequestObject(env, *gestureResult);
            }
        }
    }
    return nullptr;
#else
    return nullptr;
#endif // WEB_SUPPORTED
}

bool TransferFileSelectorResultToStatic(void* peer, void* nativePtr)
{
#ifdef WEB_SUPPORTED
    auto* objectPeer = reinterpret_cast<FileSelectorResultPeer *>(peer);
    CHECK_NULL_RETURN(objectPeer, false);
    auto* transfer = reinterpret_cast<WebTransferBase<RefPtr<FileSelectorResult>>*>(nativePtr);
    CHECK_NULL_RETURN(transfer, false);
    objectPeer->handler = transfer->get<0>();
    return true;
#else
    return false;
#endif // WEB_SUPPORTED
}

napi_value TransferFileSelectorResultToDynamic(napi_env env, void* peer)
{
#ifdef WEB_SUPPORTED
    auto* objectPeer = reinterpret_cast<FileSelectorResultPeer *>(peer);
    CHECK_NULL_RETURN(objectPeer, nullptr);
    return OHOS::Ace::Framework::CreateJSFileSelectorResultObject(env, objectPeer->handler);
#else
    return nullptr;
#endif // WEB_SUPPORTED
}

bool TransferFileSelectorParamToStatic(void* peer, void* nativePtr)
{
#ifdef WEB_SUPPORTED
    auto* objectPeer = reinterpret_cast<FileSelectorParamPeer *>(peer);
    CHECK_NULL_RETURN(objectPeer, false);
    auto* transfer = reinterpret_cast<WebTransferBase<RefPtr<WebFileSelectorParam>>*>(nativePtr);
    CHECK_NULL_RETURN(transfer, false);
    objectPeer->handler = transfer->get<0>();
    return true;
#else
    return false;
#endif // WEB_SUPPORTED
}

napi_value TransferFileSelectorParamToDynamic(napi_env env, void* peer)
{
#ifdef WEB_SUPPORTED
    auto* objectPeer = reinterpret_cast<FileSelectorParamPeer *>(peer);
    CHECK_NULL_RETURN(objectPeer, nullptr);
    return OHOS::Ace::Framework::CreateJSFileSelectorParamObject(env, objectPeer->handler);
#else
    return nullptr;
#endif // WEB_SUPPORTED
}

bool TransferWebContextMenuResultToStatic(void* peer, void* nativePtr)
{
#ifdef WEB_SUPPORTED
    auto* objectPeer = reinterpret_cast<WebContextMenuResultPeer *>(peer);
    CHECK_NULL_RETURN(objectPeer, false);
    auto* transfer = reinterpret_cast<WebTransferBase<RefPtr<ContextMenuResult>>*>(nativePtr);
    CHECK_NULL_RETURN(transfer, false);
    objectPeer->handler = transfer->get<0>();
    return true;
#else
    return false;
#endif // WEB_SUPPORTED
}

napi_value TransferWebContextMenuResultToDynamic(napi_env env, void* peer)
{
#ifdef WEB_SUPPORTED
    auto* objectPeer = reinterpret_cast<WebContextMenuResultPeer *>(peer);
    CHECK_NULL_RETURN(objectPeer, nullptr);
    return OHOS::Ace::Framework::CreateJSContextMenuResultObject(env, objectPeer->handler);
#else
    return nullptr;
#endif // WEB_SUPPORTED
}

bool TransferWebContextMenuParamToStatic(void* peer, void* nativePtr)
{
#ifdef WEB_SUPPORTED
    auto* objectPeer = reinterpret_cast<WebContextMenuParamPeer *>(peer);
    CHECK_NULL_RETURN(objectPeer, false);
    auto* transfer = reinterpret_cast<WebTransferBase<RefPtr<WebContextMenuParam>>*>(nativePtr);
    CHECK_NULL_RETURN(transfer, false);
    objectPeer->handler = transfer->get<0>();
    return true;
#else
    return false;
#endif // WEB_SUPPORTED
}

napi_value TransferWebContextMenuParamToDynamic(napi_env env, void* peer)
{
#ifdef WEB_SUPPORTED
    auto* objectPeer = reinterpret_cast<WebContextMenuParamPeer *>(peer);
    CHECK_NULL_RETURN(objectPeer, nullptr);
    return OHOS::Ace::Framework::CreateJSContextMenuParamObject(env, objectPeer->handler);
#else
    return nullptr;
#endif // WEB_SUPPORTED
}

bool TransferHttpAuthHandlerToStatic(void* peer, void* nativePtr)
{
#ifdef WEB_SUPPORTED
    auto* objectPeer = reinterpret_cast<HttpAuthHandlerPeer *>(peer);
    CHECK_NULL_RETURN(objectPeer, false);
    auto* transfer = reinterpret_cast<WebTransferBase<RefPtr<AuthResult>>*>(nativePtr);
    CHECK_NULL_RETURN(transfer, false);
    objectPeer->handler = transfer->get<0>();
    return true;
#else
    return false;
#endif // WEB_SUPPORTED
}

napi_value TransferHttpAuthHandlerToDynamic(napi_env env, void* peer)
{
#ifdef WEB_SUPPORTED
    auto* objectPeer = reinterpret_cast<HttpAuthHandlerPeer *>(peer);
    CHECK_NULL_RETURN(objectPeer, nullptr);
    return OHOS::Ace::Framework::CreateJSWebHttpAuthObject(env, objectPeer->handler);
#else
    return nullptr;
#endif // WEB_SUPPORTED
}

bool TransferWebResourceReponseToStatic(void* peer, void* nativePtr)
{
#ifdef WEB_SUPPORTED
    auto* objectPeer = reinterpret_cast<WebResourceResponsePeer *>(peer);
    CHECK_NULL_RETURN(objectPeer, false);
    auto* transfer = reinterpret_cast<WebTransferBase<RefPtr<WebResponse>>*>(nativePtr);
    CHECK_NULL_RETURN(transfer, false);
    objectPeer->handler = transfer->get<0>();
    return true;
#else
    return false;
#endif // WEB_SUPPORTED
}

napi_value TransferWebResourceReponseToDynamic(napi_env env, void* peer)
{
#ifdef WEB_SUPPORTED
    auto* objectPeer = reinterpret_cast<WebResourceResponsePeer *>(peer);
    CHECK_NULL_RETURN(objectPeer, nullptr);
    return OHOS::Ace::Framework::CreateJSWebResourceResponseObject(env, objectPeer->handler);
#else
    return nullptr;
#endif // WEB_SUPPORTED
}

bool TransferWebResourceRequestToStatic(void* peer, void* nativePtr)
{
#ifdef WEB_SUPPORTED
    auto* objectPeer = reinterpret_cast<WebResourceRequestPeer *>(peer);
    CHECK_NULL_RETURN(objectPeer, false);
    auto* transfer = reinterpret_cast<WebTransferBase<RefPtr<WebRequest>>*>(nativePtr);
    CHECK_NULL_RETURN(transfer, false);
    objectPeer->webRequest = transfer->get<0>();
    return true;
#else
    return false;
#endif // WEB_SUPPORTED
}

napi_value TransferWebResourceRequestToDynamic(napi_env env, void* peer)
{
#ifdef WEB_SUPPORTED
    auto* objectPeer = reinterpret_cast<WebResourceRequestPeer *>(peer);
    CHECK_NULL_RETURN(objectPeer, nullptr);
    return OHOS::Ace::Framework::CreateJSWebResourceRequestObject(env, objectPeer->webRequest);
#else
    return nullptr;
#endif // WEB_SUPPORTED
}

bool TransferConsoleMessageToStatic(void* peer, void* nativePtr)
{
#ifdef WEB_SUPPORTED
    auto* objectPeer = reinterpret_cast<ConsoleMessagePeer *>(peer);
    CHECK_NULL_RETURN(objectPeer, false);
    auto* transfer = reinterpret_cast<WebTransferBase<RefPtr<WebConsoleLog>>*>(nativePtr);
    CHECK_NULL_RETURN(transfer, false);
    objectPeer->webConsoleLog = transfer->get<0>();
    return true;
#else
    return false;
#endif // WEB_SUPPORTED
}

napi_value TransferConsoleMessageToDynamic(napi_env env, void* peer)
{
#ifdef WEB_SUPPORTED
    auto* objectPeer = reinterpret_cast<ConsoleMessagePeer *>(peer);
    CHECK_NULL_RETURN(objectPeer, nullptr);
    return OHOS::Ace::Framework::CreateJSWebConsoleLogObject(env, objectPeer->webConsoleLog);
#else
    return nullptr;
#endif // WEB_SUPPORTED
}

bool TransferDataResubmissionHandlerToStatic(void* peer, void* nativePtr)
{
#ifdef WEB_SUPPORTED
    auto* objectPeer = reinterpret_cast<DataResubmissionHandlerPeer *>(peer);
    CHECK_NULL_RETURN(objectPeer, false);
    auto* transfer = reinterpret_cast<WebTransferBase<RefPtr<DataResubmitted>>*>(nativePtr);
    CHECK_NULL_RETURN(transfer, false);
    objectPeer->handler = transfer->get<0>();
    return true;
#else
    return false;
#endif // WEB_SUPPORTED
}

napi_value TransferDataResubmissionHandlerToDynamic(napi_env env, void* peer)
{
#ifdef WEB_SUPPORTED
    auto* objectPeer = reinterpret_cast<DataResubmissionHandlerPeer *>(peer);
    CHECK_NULL_RETURN(objectPeer, nullptr);
    return OHOS::Ace::Framework::CreateJSDataResubmittedObject(env, objectPeer->handler);
#else
    return nullptr;
#endif // WEB_SUPPORTED
}

bool TransferClientAuthenticationHandlerToStatic(void* peer, void* nativePtr)
{
#ifdef WEB_SUPPORTED
    auto* objectPeer = reinterpret_cast<ClientAuthenticationHandlerPeer *>(peer);
    CHECK_NULL_RETURN(objectPeer, false);
    auto* transfer = reinterpret_cast<WebTransferBase<RefPtr<SslSelectCertResult>>*>(nativePtr);
    CHECK_NULL_RETURN(transfer, false);
    objectPeer->handler = transfer->get<0>();
    return true;
#else
    return false;
#endif // WEB_SUPPORTED
}

napi_value TransferClientAuthenticationHandlerToDynamic(napi_env env, void* peer)
{
#ifdef WEB_SUPPORTED
    auto* objectPeer = reinterpret_cast<ClientAuthenticationHandlerPeer *>(peer);
    CHECK_NULL_RETURN(objectPeer, nullptr);
    return OHOS::Ace::Framework::CreateJSWebSslSelectCertObject(env, objectPeer->handler);
#else
    return nullptr;
#endif // WEB_SUPPORTED
}

bool TransferSslErrorHandlerToStatic(void* peer, void* nativePtr)
{
#ifdef WEB_SUPPORTED
    auto* objectPeer = reinterpret_cast<SslErrorHandlerPeer *>(peer);
    CHECK_NULL_RETURN(objectPeer, false);
    auto* transfer = reinterpret_cast<WebTransferBase<RefPtr<SslErrorResult>>*>(nativePtr);
    CHECK_NULL_RETURN(transfer, false);
    objectPeer->sslErrorHandler = transfer->get<0>();
    return true;
#else
    return false;
#endif // WEB_SUPPORTED
}

napi_value TransferSslErrorHandlerToDynamic(napi_env env, void* peer)
{
#ifdef WEB_SUPPORTED
    auto* objectPeer = reinterpret_cast<SslErrorHandlerPeer *>(peer);
    CHECK_NULL_RETURN(objectPeer, nullptr);
    return OHOS::Ace::Framework::CreateJSWebSslErrorObject(env, objectPeer->sslErrorHandler);
#else
    return nullptr;
#endif // WEB_SUPPORTED
}

bool TransferPermissionRequestToStatic(void* peer, void* nativePtr)
{
#ifdef WEB_SUPPORTED
    auto* objectPeer = reinterpret_cast<PermissionRequestPeer *>(peer);
    CHECK_NULL_RETURN(objectPeer, false);
    auto* transfer = reinterpret_cast<WebTransferBase<RefPtr<WebPermissionRequest>>*>(nativePtr);
    CHECK_NULL_RETURN(transfer, false);
    objectPeer->handler = transfer->get<0>();
    return true;
#else
    return false;
#endif // WEB_SUPPORTED
}

napi_value TransferPermissionRequestToDynamic(napi_env env, void* peer)
{
#ifdef WEB_SUPPORTED
    auto* objectPeer = reinterpret_cast<PermissionRequestPeer *>(peer);
    CHECK_NULL_RETURN(objectPeer, nullptr);
    return OHOS::Ace::Framework::CreateJSWebPermissionRequestObject(env, objectPeer->handler);
#else
    return nullptr;
#endif // WEB_SUPPORTED
}

bool TransferControllerHandlerToStatic(void* peer, void* nativePtr)
{
#ifdef WEB_SUPPORTED
    auto* objectPeer = reinterpret_cast<ControllerHandlerPeer *>(peer);
    CHECK_NULL_RETURN(objectPeer, false);
    auto* transfer = reinterpret_cast<WebTransferBase<RefPtr<WebWindowNewHandler>>*>(nativePtr);
    CHECK_NULL_RETURN(transfer, false);
    objectPeer->handler = transfer->get<0>();
    return true;
#else
    return false;
#endif // WEB_SUPPORTED
}

napi_value TransferControllerHandlerToDynamic(napi_env env, void* peer)
{
#ifdef WEB_SUPPORTED
    auto* objectPeer = reinterpret_cast<ControllerHandlerPeer *>(peer);
    CHECK_NULL_RETURN(objectPeer, nullptr);
    return OHOS::Ace::Framework::CreateJSWebWindowNewHandlerObject(env, objectPeer->handler);
#else
    return nullptr;
#endif // WEB_SUPPORTED
}

bool TransferWebKeyboardControllerToStatic(void* peer, void* nativePtr)
{
#ifdef WEB_SUPPORTED
    auto* objectPeer = reinterpret_cast<WebKeyboardControllerPeer *>(peer);
    CHECK_NULL_RETURN(objectPeer, false);
    auto* transfer = reinterpret_cast<WebTransferBase<RefPtr<WebCustomKeyboardHandler>>*>(nativePtr);
    CHECK_NULL_RETURN(transfer, false);
    objectPeer->handler = transfer->get<0>();
    return true;
#else
    return false;
#endif // WEB_SUPPORTED
}

napi_value TransferWebKeyboardControllerToDynamic(napi_env env, void* peer)
{
#ifdef WEB_SUPPORTED
    auto* objectPeer = reinterpret_cast<WebKeyboardControllerPeer *>(peer);
    CHECK_NULL_RETURN(objectPeer, nullptr);
    return OHOS::Ace::Framework::CreateJSWebKeyboardControllerObject(env, objectPeer->handler);
#else
    return nullptr;
#endif // WEB_SUPPORTED
}

void SetJavaScriptProxyController(void* node, std::function<void()>&& callback)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (!frameNode) {
        return;
    }
    WebModelStatic::SetJavaScriptProxy(frameNode, std::move(callback));
#endif // WEB_SUPPORTED
}

const ArkUIAniWebModifier* GetWebAniModifier()
{
    static const ArkUIAniWebModifier impl = {
        .setJavaScriptProxyController = OHOS::Ace::NG::SetJavaScriptProxyController,
        .transferScreenCaptureHandlerToStatic = OHOS::Ace::NG::TransferScreenCaptureHandlerToStatic,
        .transferJsGeolocationToStatic = OHOS::Ace::NG::TransferJsGeolocationToStatic,
        .transferJsResultToStatic = OHOS::Ace::NG::TransferJsResultToStatic,
        .transferEventResultToStatic = OHOS::Ace::NG::TransferEventResultToStatic,
        .transferFileSelectorResultToStatic = OHOS::Ace::NG::TransferFileSelectorResultToStatic,
        .transferFileSelectorParamToStatic = OHOS::Ace::NG::TransferFileSelectorParamToStatic,
        .transferWebContextMenuResultToStatic = OHOS::Ace::NG::TransferWebContextMenuResultToStatic,
        .transferWebContextMenuParamToStatic = OHOS::Ace::NG::TransferWebContextMenuParamToStatic,
        .transferHttpAuthHandlerToStatic = OHOS::Ace::NG::TransferHttpAuthHandlerToStatic,
        .transferWebResourceReponseToStatic = OHOS::Ace::NG::TransferWebResourceReponseToStatic,
        .transferWebResourceRequestToStatic = OHOS::Ace::NG::TransferWebResourceRequestToStatic,
        .transferConsoleMessageToStatic = OHOS::Ace::NG::TransferConsoleMessageToStatic,
        .transferDataResubmissionHandlerToStatic = OHOS::Ace::NG::TransferDataResubmissionHandlerToStatic,
        .transferClientAuthenticationHandlerToStatic = OHOS::Ace::NG::TransferClientAuthenticationHandlerToStatic,
        .transferSslErrorHandlerToStatic = OHOS::Ace::NG::TransferSslErrorHandlerToStatic,
        .transferPermissionRequestToStatic = OHOS::Ace::NG::TransferPermissionRequestToStatic,
        .transferControllerHandlerToStatic = OHOS::Ace::NG::TransferControllerHandlerToStatic,
        .transferWebKeyboardControllerToStatic = OHOS::Ace::NG::TransferWebKeyboardControllerToStatic,
        .transferScreenCaptureHandlerToDynamic = OHOS::Ace::NG::TransferScreenCaptureHandlerToDynamic,
        .transferJsGeolocationToDynamic = OHOS::Ace::NG::TransferJsGeolocationToDynamic,
        .transferJsResultToDynamic = OHOS::Ace::NG::TransferJsResultToDynamic,
        .transferEventResultToDynamic = OHOS::Ace::NG::TransferEventResultToDynamic,
        .transferFileSelectorResultToDynamic = OHOS::Ace::NG::TransferFileSelectorResultToDynamic,
        .transferFileSelectorParamToDynamic = OHOS::Ace::NG::TransferFileSelectorParamToDynamic,
        .transferWebContextMenuResultToDynamic = OHOS::Ace::NG::TransferWebContextMenuResultToDynamic,
        .transferWebContextMenuParamToDynamic = OHOS::Ace::NG::TransferWebContextMenuParamToDynamic,
        .transferHttpAuthHandlerToDynamic = OHOS::Ace::NG::TransferHttpAuthHandlerToDynamic,
        .transferWebResourceReponseToDynamic = OHOS::Ace::NG::TransferWebResourceReponseToDynamic,
        .transferWebResourceRequestToDynamic = OHOS::Ace::NG::TransferWebResourceRequestToDynamic,
        .transferConsoleMessageToDynamic = OHOS::Ace::NG::TransferConsoleMessageToDynamic,
        .transferDataResubmissionHandlerToDynamic = OHOS::Ace::NG::TransferDataResubmissionHandlerToDynamic,
        .transferClientAuthenticationHandlerToDynamic = OHOS::Ace::NG::TransferClientAuthenticationHandlerToDynamic,
        .transferSslErrorHandlerToDynamic = OHOS::Ace::NG::TransferSslErrorHandlerToDynamic,
        .transferPermissionRequestToDynamic = OHOS::Ace::NG::TransferPermissionRequestToDynamic,
        .transferControllerHandlerToDynamic = OHOS::Ace::NG::TransferControllerHandlerToDynamic,
        .transferWebKeyboardControllerToDynamic = OHOS::Ace::NG::TransferWebKeyboardControllerToDynamic,
    };
    return &impl;
}

} // namespace OHOS::Ace::NG
