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

#pragma once

#include "core/event/mouse_event.h"
#include "core/interfaces/native/implementation/base_event_peer.h"

struct HoverEventPeer
    : public OHOS::Ace::NG::GeneratedModifier::SomeEventPeer<OHOS::Ace::HoverInfo> {
    static HoverEventPeer* Create(void* ptr)
    {
        auto* peer = OHOS::Ace::NG::PeerUtils::CreatePeer<HoverEventPeer>();
        CHECK_NULL_RETURN(peer, nullptr);
        peer->SetEventInfo(reinterpret_cast<OHOS::Ace::HoverInfo*>(ptr));
        return peer;
    }
protected:
    HoverEventPeer() = default;
    ~HoverEventPeer() override = default;
    friend OHOS::Ace::NG::PeerUtils;
};
