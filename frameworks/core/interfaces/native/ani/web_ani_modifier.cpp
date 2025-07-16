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
#include "core/interfaces/native/implementation/js_result_peer_impl.h"
#include "core/interfaces/native/implementation/web_context_menu_param_peer_impl.h"
#include "core/interfaces/native/implementation/web_context_menu_result_peer_impl.h"

#include "core/components/web/web_transfer_api.h"
#endif

namespace OHOS::Ace::NG {

void SetWebOptions(ArkUINodeHandle node, const WebviewControllerInfo& controllerInfo)
{
#ifdef WEB_SUPPORTED
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    if (!frameNode) {
        if (controllerInfo.releaseRefFunc) {
            controllerInfo.releaseRefFunc();
        }
        return;
    }
    if (controllerInfo.getNativePtrFunc) {
        int32_t parentNWebId = -1;
        bool isPopup = ControllerHandlerPeer::ExistController(controllerInfo.getNativePtrFunc(), parentNWebId);
        WebModelStatic::SetPopup(frameNode, isPopup, parentNWebId);
    }
    auto setWebIdFunc = std::move(controllerInfo.setWebIdFunc);
    auto setHapPathFunc = std::move(controllerInfo.setHapPathFunc);
    WebModelStatic::SetWebIdCallback(frameNode, std::move(setWebIdFunc));
    WebModelStatic::SetHapPathCallback(frameNode, std::move(setHapPathFunc));
#endif // WEB_SUPPORTED
}

void SetWebControllerControllerHandler(void* controllerHandler, const WebviewControllerInfo& controllerInfo)
{
#ifdef WEB_SUPPORTED
    ControllerHandlerPeer* peer = reinterpret_cast<ControllerHandlerPeer *>(controllerHandler);
    if (!peer) {
        if (controllerInfo.releaseRefFunc) {
            controllerInfo.releaseRefFunc();
        }
        return;
    }
    peer->SetWebController(controllerInfo);
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

const ArkUIAniWebModifier* GetWebAniModifier()
{
    static const ArkUIAniWebModifier impl = {
        .setWebOptions = OHOS::Ace::NG::SetWebOptions,
        .setWebControllerControllerHandler = OHOS::Ace::NG::SetWebControllerControllerHandler,
        .transferJsResultToStatic = OHOS::Ace::NG::TransferJsResultToStatic,
        .transferFileSelectorResultToStatic = OHOS::Ace::NG::TransferFileSelectorResultToStatic,
        .transferFileSelectorParamToStatic = OHOS::Ace::NG::TransferFileSelectorParamToStatic,
        .transferWebContextMenuResultToStatic = OHOS::Ace::NG::TransferWebContextMenuResultToStatic,
        .transferWebContextMenuParamToStatic = OHOS::Ace::NG::TransferWebContextMenuParamToStatic,
        .transferJsResultToDynamic = OHOS::Ace::NG::TransferJsResultToDynamic,
        .transferFileSelectorResultToDynamic = OHOS::Ace::NG::TransferFileSelectorResultToDynamic,
        .transferFileSelectorParamToDynamic = OHOS::Ace::NG::TransferFileSelectorParamToDynamic,
        .transferWebContextMenuResultToDynamic = OHOS::Ace::NG::TransferWebContextMenuResultToDynamic,
        .transferWebContextMenuParamToDynamic = OHOS::Ace::NG::TransferWebContextMenuParamToDynamic,
    };
    return &impl;
}

} // namespace OHOS::Ace::NG
