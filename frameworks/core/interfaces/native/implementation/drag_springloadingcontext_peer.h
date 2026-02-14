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

#include "core/gestures/drag_event.h"
#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"

struct dragController_SpringLoadingContextPeer {
    virtual ~dragController_SpringLoadingContextPeer() = default;

    OHOS::Ace::RefPtr<OHOS::Ace::DragSpringLoadingContext> context;

    static dragController_SpringLoadingContextPeer* Create(
        const OHOS::Ace::RefPtr<OHOS::Ace::DragSpringLoadingContext>& src)
    {
        auto peer = new dragController_SpringLoadingContextPeer;
        CHECK_NULL_RETURN(peer, nullptr);
        peer->context = src;
        return peer;
    }
};
