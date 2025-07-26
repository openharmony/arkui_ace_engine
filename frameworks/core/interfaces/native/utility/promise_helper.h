/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#pragma once

#include "core/interfaces/native/utility/async_work_helper.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG {
/**
 * This class helps to create and manage asynchronous promise.
 * 1 - create PromiseHelper with promise callback.
 * `auto promise = PromiseHelper(outputArgumentForReturningPromise);`
 * 2 (optional) - create the request for an async work with the context and worker.
 * `promise.StartAsync(vmContext, *asyncWorker, std::move(execFunc));`
 * 3 - Finish work. Use Resolve or Reject with results for CallbackHelper<PromiseCallback>::InvokeSync.
 * `promise.Resolve();`
 */
template<typename PromiseCallback>
class PromiseHelper final {
public:
    // Create without the request for an async work.
    explicit PromiseHelper(const PromiseCallback* callback)
        : callback_(callback ? CallbackHelper(*callback) : CallbackHelper<PromiseCallback>()) {}

    // Create with the request for an async work.
    PromiseHelper(const PromiseCallback* callback, Ark_VMContext vmContext, const Ark_AsyncWorker& asyncWorker,
            AsyncWorkHelper::AsyncExecFunc&& execFunc)
        : work_(AsyncWorkHelper::CreateWork(vmContext, asyncWorker, std::move(execFunc))),
        callback_(callback ? CallbackHelper(*callback) : CallbackHelper<PromiseCallback>()) {}

    void StartAsync(Ark_VMContext vmContext, const Ark_AsyncWorker& asyncWorker,
        AsyncWorkHelper::AsyncExecFunc&& execFunc)
    {
        work_ = AsyncWorkHelper::CreateWork(vmContext, asyncWorker, std::move(execFunc));
        AsyncWorkHelper::QueueWork(work_);
    }

    // Resolve the promise.
    template<typename... ArkResult>
    void Resolve(ArkResult&&... result) const
    {
        callback_.InvokeSync(std::forward<ArkResult>(result)..., Converter::ArkValue<Opt_Array_String>(Ark_Empty()));
    }

    // Reject the promise.
    template<typename ArkResult = void>
    void Reject(const StringArray& errors) const
    {
        Converter::ConvContext ctx;
        auto arkErrors = Converter::ArkValue<Opt_Array_String>(errors, &ctx);
        if constexpr (std::is_same_v<ArkResult, void>) {
            callback_.InvokeSync(arkErrors);
        } else {
            callback_.InvokeSync(Converter::ArkValue<ArkResult>(Ark_Empty()), arkErrors);
        }
    }

private:
    Ark_AsyncWork work_ {};
    CallbackHelper<PromiseCallback> callback_ {};
};
} // namespace OHOS::Ace::NG
