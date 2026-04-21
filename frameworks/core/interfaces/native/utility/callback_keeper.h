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

#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_CALLBACK_KEEPER_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_CALLBACK_KEEPER_H

#pragma once

#include <any>

#include "base/log/log_wrapper.h"
#include "core/interfaces/native/utility/base_keeper.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"

#include "patch.h"

namespace OHOS::Ace::NG {
template<typename TCallbackType>
class AutoCallbackHolder {
public:
    AutoCallbackHolder(const AutoCallbackHolder& other) : arkCallback_(other.arkCallback_)
    {
        if (arkCallback_.resource.hold) {
            arkCallback_.resource.hold(arkCallback_.resource.resourceId);
        }
    }

    AutoCallbackHolder(AutoCallbackHolder&& other) : arkCallback_(other.arkCallback_)
    {
        other.arkCallback_ = {};
    }

    ~AutoCallbackHolder()
    {
        if (arkCallback_.resource.release) {
            arkCallback_.resource.release(arkCallback_.resource.resourceId);
        }
    }

    TCallbackType ArkValue() const&
    {
        return arkCallback_;
    }

private:
    friend class CallbackKeeper;
    explicit AutoCallbackHolder(TCallbackType callback) : arkCallback_(callback) {}

    TCallbackType arkCallback_;
};

namespace {
using ReverseResultHandler = std::any;
}

class CallbackKeeper : public BaseKeeper<ReverseResultHandler> {
public:
    // This defines the reverse callback for the specific handler type.
    template <typename CallbackType, typename FinalHandlerType>
    static CallbackType ReturnReverseCallback(FinalHandlerType handler, bool autoHold = false)
    {
        // create callback resource
        CallbackType callback {
            .resource = GetNextResource(),
            .call = &ReceiveResult<FinalHandlerType>,
            .callSync = &ReceiveResultSync<FinalHandlerType>
        };

        // register handler
        storage_[callback.resource.resourceId] = { autoHold ? 1 : 0, std::move(ReverseResultHandler(handler)) };
        return callback;
    }

    template<typename CallbackType, typename HandlerType>
    static AutoCallbackHolder<CallbackType> Claim(HandlerType&& handler)
    {
        return AutoCallbackHolder(ReturnReverseCallback<CallbackType>(std::move(handler), true));
    }
private:
    template <typename FinalHandlerType, typename... Params>
    static void ReceiveResult(const Ark_Int32 resourceId, Params... args)
    {
        auto it = storage_.find(resourceId);
        if (it == storage_.end()) {
            return;
        }
        Hold(it);
        auto reverseResultHandler = it->second.data;
        if (auto handlerPtr = std::any_cast<FinalHandlerType>(&reverseResultHandler); handlerPtr) {
            (*handlerPtr)(std::forward<Params>(args)...);
        }
        Release(it);
    }

    template<typename FinalHandlerType, typename... Params>
    static void ReceiveResultSync(Ark_VMContext context, const Ark_Int32 resourceId, Params... args)
    {
        ReceiveResult<FinalHandlerType>(resourceId, std::forward<Params>(args)...);
    }
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_CALLBACK_KEEPER_H