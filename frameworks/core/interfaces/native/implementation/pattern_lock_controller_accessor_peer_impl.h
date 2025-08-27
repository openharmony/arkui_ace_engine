/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_PATTERN_LOCK_CTRL_ACCESSOR_PEER_IMPL_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_PATTERN_LOCK_CTRL_ACCESSOR_PEER_IMPL_H

#include "base/memory/referenced.h"
#include "core/components_v2/pattern_lock/pattern_lock_controller.h"

struct PatternLockControllerPeer final {
    OHOS::Ace::RefPtr<OHOS::Ace::V2::PatternLockController> handler;

    void SetHandler(const OHOS::Ace::RefPtr<OHOS::Ace::V2::PatternLockController>& handlerIn)
    {
        handler = handlerIn;
    }
};

namespace OHOS::Ace::NG::GeneratedModifier {
    using PatternLockControllerPeerImpl = ::PatternLockControllerPeer;
} // namespace OHOS::Ace::NG::GeneratedModifier
#endif //FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_PATTERN_LOCK_CTRL_ACCESSOR_PEER_IMPL_H
