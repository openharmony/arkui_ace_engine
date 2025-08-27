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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_PEER_UTILS_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_PEER_UTILS_H

#include <type_traits>
#include <unordered_map>

#ifdef ARKUI_CAPI_UNITTEST
#include <gtest/gtest.h>
#endif

#include "base/memory/referenced.h"
#include "interfaces/inner_api/ace/ai/image_analyzer.h"

namespace OHOS::Ace::NG {
class PeerUtils {
public:
    template<typename T, typename... U>
    static T *CreatePeer(U&&... u)
    {
        auto peer = new T(std::forward<U>(u)...);
#ifdef ARKUI_CAPI_UNITTEST
        peerMap_.insert_or_assign(peer, [peer]() {DestroyPeer(peer);});
#endif
        if constexpr (std::is_base_of_v<Referenced, T>) {
            peer->IncRefCount();
        }
        return peer;
    }

    template<typename T>
    static void DestroyPeer(T *peer)
    {
        CHECK_NULL_VOID(peer);
#ifdef ARKUI_CAPI_UNITTEST
        auto pos = peerMap_.find(peer);
        if (pos == peerMap_.end()) {
            FAIL() << "Deleting peer with DestroyPeer() which was not created by CreatePeer()!";
            return;
        }
        peerMap_.erase(pos);
#endif
        if constexpr (std::is_base_of_v<Referenced, T>) {
            peer->DecRefCount();
        } else {
            delete peer;
        }
    }

#ifdef ARKUI_CAPI_UNITTEST
    inline static void ClearAllPeers()
    {
        std::vector<void *> keys;
        // Copy keys, since map will be changed during destroy process
        std::transform(peerMap_.begin(), peerMap_.end(), std::back_inserter(keys),
            [](const auto& val) {return val.first;});
        for (auto key : keys) {
            peerMap_.at(key)();
        }
    }

private:
    inline static std::unordered_map<void *, std::function<void()>> peerMap_;
#endif

public:
    static std::vector<std::string> CreateAIError(OHOS::Ace::ImageAnalyzerState state);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_X_COMPONENT_CONTROLLER_PEER_IMPL_H
