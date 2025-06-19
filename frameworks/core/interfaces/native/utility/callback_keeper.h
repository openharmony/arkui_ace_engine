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

#include <unordered_map>
#include "base/log/log_wrapper.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"

namespace OHOS::Ace::NG {
template<typename TCallbackType>
class AutoCallbackKeeper {
public:
    AutoCallbackKeeper(std::function<void()>&& handler);
    ~AutoCallbackKeeper();

    TCallbackType ArkValue() const;

private:
    TCallbackType arkCallback_;
};

class CallbackKeeper {
public:
    using ResultHandler = std::function<void(const void *)>;
    using ReverseHandler = std::function<void()>;

    template <typename ArkResultType, typename ContinuationType, typename CallbackHelper, typename... Params>
    static void InvokeWithResultHandler(ResultHandler &&handler, const CallbackHelper &helper, Params&&... args)
    {
        // create continuation
        ContinuationType continuation {
            .resource = GetNextCallbackResource(),
            .call = &ReceiveResult<ArkResultType>,
            .callSync = &ReceiveResultSync<ArkResultType>
        };

        // register handler
        storage_[continuation.resource.resourceId] = { 1, std::move(handler) }; // +1 for automatic Hold

        helper.InvokeSync(std::forward<Params>(args)..., continuation);

        Release(continuation.resource.resourceId);
    }

    template <typename CallbackType>
    static CallbackType DefineReverseCallback(ReverseHandler &&handler)
    {
        // create continuation
        CallbackType callback {
            .resource = GetNextCallbackResource(),
            .call = &InvokeReverseInternal,
            .callSync = &InvokeReverseInternalSync
        };

        auto resultHandler = [handler](const void *) {
            handler();
        };

        // register handler
        storage_[callback.resource.resourceId] = { 1, std::move(resultHandler) }; // +1 for automatic Hold
        return callback;
    }

    template <typename CallbackType>
    static void ReleaseReverseCallback(CallbackType callback)
    {
        Release(callback.resource.resourceId);
    }

    template <typename CallbackType = Callback_Void>
    static AutoCallbackKeeper<CallbackType> Claim(ReverseHandler &&handler)
    {
        return AutoCallbackKeeper<CallbackType>(std::move(handler));
    }

private:
    static void Hold(Ark_Int32 resourceId)
    {
        storage_[resourceId].counter++;
    }

    static void Release(Ark_Int32 resourceId)
    {
        auto it = storage_.find(resourceId);
        if (it == storage_.end()) {
            return;
        }
        (it->second.counter)--;
        if (it->second.counter == 0) {
            storage_.erase(it);
        }
    }

    static Ark_CallbackResource GetNextCallbackResource()
    {
        return {
            .resourceId = ++currentId_,
            .hold = &Hold,
            .release = &Release
        };
    }

    template <typename ArkResultType>
    inline static void ReceiveResult(const Ark_Int32 resourceId, const ArkResultType value)
    {
        ReceiveResultInternal(resourceId, &value);
    }

    template <typename ArkResultType>
    inline static void ReceiveResultSync(Ark_VMContext context, const Ark_Int32 resourceId, const ArkResultType value)
    {
        ReceiveResultInternal(resourceId, &value);
    }

    struct CallbackData {
        int32_t counter = 0;
        ResultHandler handler;
    };

    inline static std::unordered_map<Ark_Int32, CallbackData> storage_;
    inline static Ark_Int32 currentId_ = 0;

    static void ReceiveResultInternal(const Ark_Int32 resourceId, const void* valuePtr)
    {
        if (auto it = storage_.find(resourceId); it != storage_.end()) {
            it->second.handler(valuePtr);
        }
    }

    static void InvokeReverseInternal(const Ark_Int32 resourceId)
    {
        ReceiveResultInternal(resourceId, nullptr);
    }

    static void InvokeReverseInternalSync(Ark_VMContext context, const Ark_Int32 resourceId)
    {
        ReceiveResultInternal(resourceId, nullptr);
    }
};

template<typename TCallbackType>
inline AutoCallbackKeeper<TCallbackType>::AutoCallbackKeeper(std::function<void()>&& handler)
    : arkCallback_(CallbackKeeper::DefineReverseCallback<TCallbackType>(std::move(handler))) {}

template<typename TCallbackType>
inline AutoCallbackKeeper<TCallbackType>::~AutoCallbackKeeper()
{
    CallbackKeeper::ReleaseReverseCallback(arkCallback_);
}

template<typename TCallbackType>
inline TCallbackType AutoCallbackKeeper<TCallbackType>::ArkValue() const
{
    return arkCallback_;
}

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_CALLBACK_KEEPER_H