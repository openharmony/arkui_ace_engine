/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

#include "frameworks/core/interfaces/native/implementation/security_ui_extension_proxy_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
const GENERATED_ArkUISecurityUIExtensionProxyAccessor* GetSecurityUIExtensionProxyAccessor();
namespace SecurityUIExtensionProxyAccessor {
void DestroyPeerImpl(Ark_SecurityUIExtensionProxy peer)
{
    if (peer) {
        delete peer;
    }
}
Ark_SecurityUIExtensionProxy CtorImpl()
{
    return new SecurityUIExtensionProxyPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void SendImpl(Ark_SecurityUIExtensionProxy peer, const Map_String_Object* data)
{
    LOGE("SecurityUIExtensionProxyAccessor::SendImpl - implement by ANI");
}
Map_String_Object SendSyncImpl(Ark_VMContext vmContext,
    Ark_SecurityUIExtensionProxy peer, const Map_String_Object* data)
{
    LOGE("SecurityUIExtensionProxyAccessor::SendSyncImpl - implement by ANI");
    return {};
}
void OnAsyncReceiverRegisterImpl(Ark_SecurityUIExtensionProxy peer,
    const Callback_SecurityUIExtensionProxy_Void* callback_)
{
#ifdef WINDOW_SCENE_SUPPORTED
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(callback_);
    auto func = [arkCallback = CallbackHelper(*callback_)](const RefPtr<SecurityUIExtensionProxy>& proxy) {
        auto accessor = GetSecurityUIExtensionProxyAccessor();
        CHECK_NULL_VOID(accessor);
        auto peer = accessor->ctor();
        CHECK_NULL_VOID(peer);
        auto uiExtensionProxyPeerPtr = reinterpret_cast<SecurityUIExtensionProxyPeer*>(peer);
        uiExtensionProxyPeerPtr->SetProxy(proxy);
        arkCallback.Invoke(peer);
    };

    std::lock_guard<std::mutex> lock(peer->callbackListLock_);
    peer->AddAsyncCallbackToList(callback_->resource.resourceId, std::move(func));
    auto pattern = peer->GetPattern();
    CHECK_NULL_VOID(pattern);
    auto funcList = peer->GetOnAsyncCallbackList();
    pattern->SetAsyncCallbacks(std::move(funcList));
#endif //WINDOW_SCENE_SUPPORTED
}
void OnSyncReceiverRegisterImpl(Ark_SecurityUIExtensionProxy peer,
    const Callback_SecurityUIExtensionProxy_Void* callback_)
{
#ifdef WINDOW_SCENE_SUPPORTED
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(callback_);
    auto func = [arkCallback = CallbackHelper(*callback_)](const RefPtr<SecurityUIExtensionProxy>& proxy) {
        auto accessor = GetSecurityUIExtensionProxyAccessor();
        CHECK_NULL_VOID(accessor);
        auto peer = accessor->ctor();
        CHECK_NULL_VOID(peer);
        auto uiExtensionProxyPeerPtr = reinterpret_cast<SecurityUIExtensionProxyPeer*>(peer);
        uiExtensionProxyPeerPtr->SetProxy(proxy);
        arkCallback.Invoke(peer);
    };

    std::lock_guard<std::mutex> lock(peer->callbackListLock_);
    peer->AddSyncCallbackToList(callback_->resource.resourceId, std::move(func));
    auto pattern = peer->GetPattern();
    CHECK_NULL_VOID(pattern);
    auto funcList = peer->GetOnSyncCallbackList();
    pattern->SetSyncCallbacks(std::move(funcList));
#endif //WINDOW_SCENE_SUPPORTED
}
void OffAsyncReceiverRegisterImpl(Ark_SecurityUIExtensionProxy peer,
    const Opt_Callback_SecurityUIExtensionProxy_Void* callback_)
{
#ifdef WINDOW_SCENE_SUPPORTED
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(callback_);
    auto cb = Converter::OptConvert<Callback_SecurityUIExtensionProxy_Void>(*callback_);
    std::lock_guard<std::mutex> lock(peer->callbackListLock_);
    if (cb) {
        peer->DeleteAsyncCallbackFromList(cb.value().resource.resourceId);
    } else {
        peer->ClearAsyncCallbackList();
    }
    auto pattern = peer->GetPattern();
    CHECK_NULL_VOID(pattern);
    auto funcList = peer->GetOnAsyncCallbackList();
    pattern->SetAsyncCallbacks(std::move(funcList));
#endif //WINDOW_SCENE_SUPPORTED
}
void OffSyncReceiverRegisterImpl(Ark_SecurityUIExtensionProxy peer,
    const Opt_Callback_SecurityUIExtensionProxy_Void* callback_)
{
#ifdef WINDOW_SCENE_SUPPORTED
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(callback_);
    auto cb = Converter::OptConvert<Callback_SecurityUIExtensionProxy_Void>(*callback_);
    std::lock_guard<std::mutex> lock(peer->callbackListLock_);
    if (cb) {
        peer->DeleteSyncCallbackFromList(cb.value().resource.resourceId);
    } else {
        peer->ClearSyncCallbackList();
    }
    auto pattern = peer->GetPattern();
    CHECK_NULL_VOID(pattern);
    auto funcList = peer->GetOnSyncCallbackList();
    pattern->SetSyncCallbacks(std::move(funcList));
#endif //WINDOW_SCENE_SUPPORTED
}
} // SecurityUIExtensionProxyAccessor
const GENERATED_ArkUISecurityUIExtensionProxyAccessor* GetSecurityUIExtensionProxyAccessor()
{
    static const GENERATED_ArkUISecurityUIExtensionProxyAccessor SecurityUIExtensionProxyAccessorImpl {
        SecurityUIExtensionProxyAccessor::DestroyPeerImpl,
        SecurityUIExtensionProxyAccessor::CtorImpl,
        SecurityUIExtensionProxyAccessor::GetFinalizerImpl,
        SecurityUIExtensionProxyAccessor::SendImpl,
        SecurityUIExtensionProxyAccessor::SendSyncImpl,
        SecurityUIExtensionProxyAccessor::OnAsyncReceiverRegisterImpl,
        SecurityUIExtensionProxyAccessor::OnSyncReceiverRegisterImpl,
        SecurityUIExtensionProxyAccessor::OffAsyncReceiverRegisterImpl,
        SecurityUIExtensionProxyAccessor::OffSyncReceiverRegisterImpl,
    };
    return &SecurityUIExtensionProxyAccessorImpl;
}

}