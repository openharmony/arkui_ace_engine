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

#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_CALLBACK_HELPER_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_CALLBACK_HELPER_H

#pragma once

#include <type_traits>
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG {
template<typename CallbackType,
    std::enable_if_t<std::is_same_v<decltype(CallbackType().resource), Ark_CallbackResource>, bool> = true,
    std::enable_if_t<std::is_function_v<std::remove_pointer_t<decltype(CallbackType().call)>>, bool> = true
>
class CallbackHelper {
public:
    CallbackHelper() = default;

    CallbackHelper(const CallbackType &callback): callback_(callback)
    {
        if (callback_.resource.hold) {
            (*callback_.resource.hold)(callback_.resource.resourceId);
        }
    }
    CallbackHelper(const CallbackHelper &other): callback_(other.callback_)
    {
        if (callback_.resource.hold) {
            (*callback_.resource.hold)(callback_.resource.resourceId);
        }
    }
    ~CallbackHelper()
    {
        if (callback_.resource.release) {
            (*callback_.resource.release)(callback_.resource.resourceId);
        }
    }

    template<typename... Params>
    void Invoke(Params&&... args) const
    {
        if (callback_.call) {
            (*callback_.call)(callback_.resource.resourceId, std::forward<Params>(args)...);
        }
    }
protected:
    const CallbackType callback_  = {
        .resource = {.hold = nullptr, .release = nullptr},
        .call = nullptr
    };
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_ARKOALA_IMPL_CALLBACK_HELPER_H
