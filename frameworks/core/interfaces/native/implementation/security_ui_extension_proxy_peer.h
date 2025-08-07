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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_SECURITY_UI_EXTENSION_PROXY_PEER_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_SECURITY_UI_EXTENSION_PROXY_PEER_H

#include "base/memory/ace_type.h"
#ifdef WINDOW_SCENE_SUPPORTED
#include <mutex>
#include "core/components_ng/pattern/ui_extension/security_ui_extension_component/security_ui_extension_proxy.h"
#include "frameworks/core/interfaces/native/implementation/ui_extension_proxy_peer_base.h"
#endif //WINDOW_SCENE_SUPPORTED
namespace OHOS::Ace::NG::GeneratedModifier {
#ifdef WINDOW_SCENE_SUPPORTED
struct SecurityUIExtensionProxyPeerImpl : public UIExtensionProxyPeerBase {
#else
struct SecurityUIExtensionProxyPeerImpl : public AceType {
#endif
#ifdef WINDOW_SCENE_SUPPORTED
    using ProxyRefPtr = OHOS::Ace::RefPtr<OHOS::Ace::NG::SecurityUIExtensionProxy>;
    using CallbackFunc = std::function<void(const ProxyRefPtr&)>;
    using CallbackFuncPairList = std::list<std::pair<int32_t, CallbackFunc>>;
    using PatternRefPtr = OHOS::Ace::RefPtr<OHOS::Ace::NG::SecurityUIExtensionPattern>;
#endif //WINDOW_SCENE_SUPPORTED
    SecurityUIExtensionProxyPeerImpl() = default;
    ~SecurityUIExtensionProxyPeerImpl() = default;
#ifdef WINDOW_SCENE_SUPPORTED
    inline void SetProxy(const ProxyRefPtr& proxy)
    {
        proxy_ = proxy;
    }

    void SendData(const AAFwk::WantParams& wantParams) override;

    int32_t SendDataSync(
        const AAFwk::WantParams& wantParams, AAFwk::WantParams& reWantParams) override;
    
    inline PatternRefPtr GetPattern()
    {
        CHECK_NULL_RETURN(proxy_, nullptr);
        return proxy_->GetPattern();
    }

    inline std::list<CallbackFunc> GetOnSyncCallbackList()
    {
        std::list<CallbackFunc> reList;
        for (const auto& item : onSyncCallbackList_) {
            reList.emplace_back(item.second);
        }
        return reList;
    }

    inline std::list<CallbackFunc> GetOnAsyncCallbackList()
    {
        std::list<CallbackFunc> reList;
        for (const auto& item : onAsyncCallbackList_) {
            reList.emplace_back(item.second);
        }
        return reList;
    }

    inline void AddAsyncCallbackToList(int32_t id, const CallbackFunc& onFunc)
    {
        auto iter = FindCallback(id, onAsyncCallbackList_);
        if (iter == onAsyncCallbackList_.end()) {
            onAsyncCallbackList_.emplace_back(std::make_pair(id, onFunc));
        }
    }

    inline void AddSyncCallbackToList(int32_t id, const CallbackFunc& onFunc)
    {
        auto iter = FindCallback(id, onSyncCallbackList_);
        if (iter == onSyncCallbackList_.end()) {
            onSyncCallbackList_.emplace_back(std::make_pair(id, onFunc));
        }
    }

    inline void DeleteSyncCallbackFromList(int32_t id)
    {
        auto iter = FindCallback(id, onSyncCallbackList_);
        if (iter != onSyncCallbackList_.end()) {
            onSyncCallbackList_.erase(iter);
        }
    }

    inline void ClearSyncCallbackList()
    {
        onSyncCallbackList_.clear();
    }

    inline void DeleteAsyncCallbackFromList(int32_t id)
    {
        auto iter = FindCallback(id, onAsyncCallbackList_);
        if (iter != onAsyncCallbackList_.end()) {
            onAsyncCallbackList_.erase(iter);
        }
    }

    inline void ClearAsyncCallbackList()
    {
        onAsyncCallbackList_.clear();
    }

    std::mutex callbackListLock_;
private:
    inline CallbackFuncPairList::const_iterator FindCallback(int32_t id, CallbackFuncPairList& callbackList)
    {
        return std::find_if(callbackList.begin(), callbackList.end(), [id](const auto& item) -> bool {
            return (item.first == id);
        });
    }
    ProxyRefPtr proxy_;
    CallbackFuncPairList onSyncCallbackList_;
    CallbackFuncPairList onAsyncCallbackList_;
#endif //WINDOW_SCENE_SUPPORTED
};
} // namespace OHOS::Ace::NG::GeneratedModifier

struct SecurityUIExtensionProxyPeer : public OHOS::Ace::NG::GeneratedModifier::SecurityUIExtensionProxyPeerImpl {};
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_SECURITY_UI_EXTENSION_PROXY_PEER_H
