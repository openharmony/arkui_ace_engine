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

#include <variant>
#include "base/log/log_wrapper.h"
#include "core/interfaces/native/utility/base_keeper.h"
#include "core/interfaces/native/utility/callback_helper.h"

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

namespace {
using ReverseResultHandler = std::variant<std::function<void()>, std::function<void(const void*)>,
    std::function<void(Ark_Boolean)>, std::function<void(Ark_Number)>, std::function<void(Ark_Number, Ark_Number)>>;
}

class CallbackKeeper : public BaseKeeper<ReverseResultHandler> {
public:
    using AnyResultHandlerType = std::function<void(const void*)>;
    using ReverseHandler = std::function<void()>;

    template<typename ArkResultType, typename ContinuationType, typename CallbackHelper, typename... Params>
    static void InvokeWithResultHandler(
        std::function<void(const void*)>&& handler, const CallbackHelper& helper, Params&&... args)
    {
        // create continuation
        // register handler
        auto continuation = RegisterReverseCallback<ContinuationType, AnyResultHandlerType>(handler);
        helper.InvokeSync(std::forward<Params>(args)..., continuation);
        Release(continuation.resource.resourceId);
    }

    template<typename ArkResultType, typename ContinuationType, typename CallbackHelper, typename... Params>
    static void InvokeWithResultHandlerAsync(
        std::function<void(const void*)>&& handler, const CallbackHelper& helper, Params&&... args)
    {
        // create continuation
        // register handler
        auto continuation = RegisterReverseCallback<ContinuationType, AnyResultHandlerType>(handler);
        helper.Invoke(std::forward<Params>(args)..., continuation);
        Release(continuation.resource.resourceId);
    }

    // This defines the reverse callback for the specific handler type.
    // Possible the handler types are listed in ReverseResultHandler type
    template<typename CallbackType, typename FinalHandlerType>
    static CallbackType RegisterReverseCallback(FinalHandlerType handler, bool autoHold = true)
    {
        // create callback resource
        CallbackType callback { .resource = GetNextResource(),
            .call = &ReceiveResult<FinalHandlerType>,
            .callSync = &ReceiveResultSync<FinalHandlerType> };

        // register handler
        storage_[callback.resource.resourceId] = { autoHold ? 1 : 0, std::move(ReverseResultHandler(handler)) };
        return callback;
    }

    // This defines the reverse callback without parameters.
    template<typename CallbackType>
    static CallbackType DefineReverseCallback(ReverseHandler handler, bool autoHold = true)
    {
        return RegisterReverseCallback<CallbackType, ReverseHandler>(handler, autoHold);
    }

    template<typename CallbackType>
    static void ReleaseReverseCallback(CallbackType callback)
    {
        Release(callback.resource.resourceId);
    }

    template<typename CallbackType = Callback_Void>
    static AutoCallbackKeeper<CallbackType> Claim(ReverseHandler&& handler)
    {
        return AutoCallbackKeeper<CallbackType>(std::move(handler));
    }

private:
    template<typename FinalHandlerType, typename... Params>
    static void ReceiveResult(const Ark_Int32 resourceId, Params... args)
    {
        auto it = storage_.find(resourceId);
        if (it == storage_.end()) {
            return;
        }
        Hold(it);
        auto reverseResultHandler = it->second.data;
        if (auto handlerPtr = std::get_if<FinalHandlerType>(&reverseResultHandler); handlerPtr) {
            if constexpr (std::is_same_v<FinalHandlerType, AnyResultHandlerType>) {
                auto arg0 = std::get<0>(std::tuple<Params...> { args... });
                (*handlerPtr)(reinterpret_cast<const void*>(&arg0));
            } else {
                (*handlerPtr)(std::forward<Params>(args)...);
            }
        }
        Release(it);
    }

    template<typename FinalHandlerType, typename... Params>
    static void ReceiveResultSync(Ark_VMContext context, const Ark_Int32 resourceId, Params... args)
    {
        ReceiveResult<FinalHandlerType>(resourceId, std::forward<Params>(args)...);
    }
};

template<typename TCallbackType>
inline AutoCallbackKeeper<TCallbackType>::AutoCallbackKeeper(std::function<void()>&& handler)
    : arkCallback_(CallbackKeeper::DefineReverseCallback<TCallbackType>(std::move(handler)))
{}

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