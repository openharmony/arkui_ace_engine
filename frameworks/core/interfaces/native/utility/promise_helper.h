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

namespace OHOS::Ace::NG {
/**
 * This class helps to create and manage asynchronous promise.
 * 1 - create PromiseHelper with promise callback.
 * `auto promise = PromiseHelper(outputArgumentForReturningPromise);`
 * 2 (optional) - create the request for an async work with the context and worker.
 * `promise.StartAsync(vmContext, *asyncWorker, std::move(execFunc));`
 * 3 - Finish work. Use Resolve or Reject with results for CallbackHelper<PromiseCallback>::InvokeSync.
 * For Resolve the error needs to be Converter::ArkValue<Ark_Xxx>(Ark_Empty).
 * `promise.Resolve(Converter::ArkValue<Ark_Xxx>(Ark_Empty));`
 */
template<typename PromiseCallback>
class PromiseHelper final {
public:
    explicit PromiseHelper(const PromiseCallback* callback)
        : callback_(callback ? CallbackHelper(*callback) : CallbackHelper<PromiseCallback>()) {}

    void StartAsync(Ark_VMContext vmContext, const Ark_AsyncWorkerPtr asyncWorker,
        AsyncWorkHelper::AsyncExecFunc&& execFunc)
    {
        CHECK_NULL_VOID(asyncWorker);
        work_ = AsyncWorkHelper::CreateWork(vmContext, *asyncWorker, std::move(execFunc));
    }

    // Resolve the promise. The error needs to be Converter::ArkValue<Ark_Xxx>(Ark_Empty).
    // It is mandatory to pass an empty error, but this requirement may be waived in the future.
    template<typename... Results>
    void Resolve(Results&&... results) const
    {
        callback_.InvokeSync(std::forward<Results>(results)...);
        AsyncWorkHelper::ResolveWork(work_);
    }

    // Reject the promise.
    template<typename... Results>
    void Reject(Results&&... results) const
    {
        callback_.InvokeSync(std::forward<Results>(results)...);
        AsyncWorkHelper::RejectWork(work_);
    }

private:
    Ark_AsyncWork work_ {};
    CallbackHelper<PromiseCallback> callback_;
};
} // namespace OHOS::Ace::NG
