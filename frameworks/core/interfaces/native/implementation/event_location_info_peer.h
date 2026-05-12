/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/gestures/gesture_info.h"
#include "core/interfaces/native/implementation/base_event_peer.h"

struct EventLocationInfoPeer : public OHOS::Ace::Referenced {
    OHOS::Ace::FingerInfo handler;
    void SetHandler(const OHOS::Ace::FingerInfo& handlerIn)
    {
        handler = handlerIn;
        if (!handler.currentLocalLocation_) {
            handler.currentLocalLocation_ = [this]() {
                return handler.localLocation_;
            };
        }
    }
    void SetHandler(const OHOS::Ace::EventLocationInfo& handlerIn)
    {
        OHOS::Ace::FingerInfo info;
        info.localLocation_ = handlerIn.localLocation_;
        info.globalLocation_ = handlerIn.windowLocation_;
        info.screenLocation_ = handlerIn.displayLocation_;
        info.globalDisplayLocation_ = handlerIn.globalDisplayLocation_;
        SetHandler(info);
    }
    OHOS::Ace::FingerInfo* GetEventInfo()
    {
        return &handler;
    }
protected:
    EventLocationInfoPeer() = default;
    ~EventLocationInfoPeer() override = default;
    friend OHOS::Ace::NG::PeerUtils;
};