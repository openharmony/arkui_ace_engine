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

#ifndef FOUNDATION_ACE_ACE_ENGINE_ADAPTER_OHOS_CAPABILITY_INTERACTION_COORDINATION_LISTENER_IMPL_H
#define FOUNDATION_ACE_ACE_ENGINE_ADAPTER_OHOS_CAPABILITY_INTERACTION_COORDINATION_LISTENER_IMPL_H

#include <functional>

#include "i_coordination_listener.h"

using DragOutCallback = std::function<void(OHOS::Msdp::CoordinationMessage)>;

namespace OHOS::Ace {
class CoordinationListenerImpl : public OHOS::Msdp::ICoordinationListener {
public:
    CoordinationListenerImpl() = default;
    explicit CoordinationListenerImpl(DragOutCallback callback) : callback_(callback) { }

    void OnCoordinationMessage(const std::string &networkId, Msdp::CoordinationMessage msg) override
    {
        if (callback_) {
            callback_(msg);
        }
    }
private:
    DragOutCallback callback_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_ACE_ENGINE_ADAPTER_OHOS_CAPABILITY_INTERACTION_COORDINATION_LISTENER_IMPL_H

