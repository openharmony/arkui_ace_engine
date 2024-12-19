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

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

#include "frameworks/core/interfaces/native/implementation/ui_extension_proxy_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
const GENERATED_ArkUIUIExtensionProxyAccessor* GetUIExtensionProxyAccessor();
namespace UIExtensionProxyAccessor {
void DestroyPeerImpl(UIExtensionProxyPeer* peer)
{
    if (peer) {
        delete peer;
    }
}
Ark_NativePointer CtorImpl()
{
    return new UIExtensionProxyPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void SendImpl(UIExtensionProxyPeer* peer,
              const Map_String_CustomObject* data)
{
    LOGE("UIExtensionProxyAccessor::SendImpl - is not supported");
}
Ark_NativePointer SendSyncImpl(UIExtensionProxyPeer* peer,
                               const Map_String_CustomObject* data)
{
    LOGE("UIExtensionProxyAccessor::SendSyncImpl - is not supported");
    return nullptr;
}
void OnAsyncReceiverRegisterImpl(UIExtensionProxyPeer* peer,
                                 const Callback_UIExtensionProxy_Void* callback)
{
#ifdef WINDOW_SCENE_SUPPORTED
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(callback);
    auto func = [arkCallback = CallbackHelper(*callback)](const RefPtr<UIExtensionProxy>& proxy) {
        auto accessor = GetUIExtensionProxyAccessor();
        CHECK_NULL_VOID(accessor);
        auto peer = accessor->ctor();
        CHECK_NULL_VOID(peer);
        auto uiExtensionProxyPeerPtr = reinterpret_cast<UIExtensionProxyPeer*>(peer);
        uiExtensionProxyPeerPtr->SetProxy(proxy);
        arkCallback.Invoke(Ark_Materialized{ .ptr = peer });
    };

    std::lock_guard<std::mutex> lock(peer->callbackListLock_);
    peer->AddAsyncCallbackToList(callback->resource.resourceId, std::move(func));
    auto pattern = peer->GetPattern();
    CHECK_NULL_VOID(pattern);
    auto funcList = peer->GetOnAsyncCallbackList();
    pattern->SetAsyncCallbacks(std::move(funcList));
#endif //WINDOW_SCENE_SUPPORTED
}
void OnSyncReceiverRegisterImpl(UIExtensionProxyPeer* peer,
                                const Callback_UIExtensionProxy_Void* callback)
{
#ifdef WINDOW_SCENE_SUPPORTED
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(callback);
    auto func = [arkCallback = CallbackHelper(*callback)](const RefPtr<UIExtensionProxy>& proxy) {
        auto accessor = GetUIExtensionProxyAccessor();
        CHECK_NULL_VOID(accessor);
        auto peer = accessor->ctor();
        CHECK_NULL_VOID(peer);
        auto uiExtensionProxyPeerPtr = reinterpret_cast<UIExtensionProxyPeer*>(peer);
        uiExtensionProxyPeerPtr->SetProxy(proxy);
        arkCallback.Invoke(Ark_Materialized{ .ptr = peer });
    };

    std::lock_guard<std::mutex> lock(peer->callbackListLock_);
    peer->AddSyncCallbackToList(callback->resource.resourceId, std::move(func));
    auto pattern = peer->GetPattern();
    CHECK_NULL_VOID(pattern);
    auto funcList = peer->GetOnSyncCallbackList();
    pattern->SetSyncCallbacks(std::move(funcList));
#endif //WINDOW_SCENE_SUPPORTED
}
void OffAsyncReceiverRegisterImpl(UIExtensionProxyPeer* peer,
                                  const Opt_Callback_UIExtensionProxy_Void* callback)
{
#ifdef WINDOW_SCENE_SUPPORTED
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(callback);
    auto cb = Converter::OptConvert<Callback_UIExtensionProxy_Void>(*callback);
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
void OffSyncReceiverRegisterImpl(UIExtensionProxyPeer* peer,
                                 const Opt_Callback_UIExtensionProxy_Void* callback)
{
#ifdef WINDOW_SCENE_SUPPORTED
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(callback);
    auto cb = Converter::OptConvert<Callback_UIExtensionProxy_Void>(*callback);
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
} // UIExtensionProxyAccessor
const GENERATED_ArkUIUIExtensionProxyAccessor* GetUIExtensionProxyAccessor()
{
    static const GENERATED_ArkUIUIExtensionProxyAccessor UIExtensionProxyAccessorImpl {
        UIExtensionProxyAccessor::DestroyPeerImpl,
        UIExtensionProxyAccessor::CtorImpl,
        UIExtensionProxyAccessor::GetFinalizerImpl,
        UIExtensionProxyAccessor::SendImpl,
        UIExtensionProxyAccessor::SendSyncImpl,
        UIExtensionProxyAccessor::OnAsyncReceiverRegisterImpl,
        UIExtensionProxyAccessor::OnSyncReceiverRegisterImpl,
        UIExtensionProxyAccessor::OffAsyncReceiverRegisterImpl,
        UIExtensionProxyAccessor::OffSyncReceiverRegisterImpl,
    };
    return &UIExtensionProxyAccessorImpl;
}

}
