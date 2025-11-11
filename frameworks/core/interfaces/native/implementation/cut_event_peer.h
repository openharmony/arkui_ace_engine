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

#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPLEMENTATION_CUT_EVENT_PEER_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPLEMENTATION_CUT_EVENT_PEER_H

#include "base/utils/utils.h"
#include "core/interfaces/native/utility/peer_utils.h"

struct CutEventPeer {
    static CutEventPeer* Create()
    {
        return OHOS::Ace::NG::PeerUtils::CreatePeer<CutEventPeer>();
    }

    void SetPreventDefault(std::function<void()>&& preventDefault)
    {
        preventDefault_ = std::move(preventDefault);
    }

    void HandlePreventDefault()
    {
        CHECK_NULL_VOID(preventDefault_);
        preventDefault_();
    }

private:
    CutEventPeer() = default;
    ~CutEventPeer() = default;
    std::function<void()> preventDefault_;
    friend OHOS::Ace::NG::PeerUtils;
};
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPLEMENTATION_CUT_EVENT_PEER_H