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

#include <cstdint>
#include <functional>
#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"

namespace OHOS::Ace::NG {
class AsyncWorkTestHelper {
public:
    inline static void Reset()
    {
        queueWorkId_ = nullptr;
        cancelWorkId_ = nullptr;
    }

    inline static InteropAsyncWorker* GetWorkerPtr()
    {
        return &interopAsyncWorker_;
    }
    inline static bool HasWorkCreated()
    {
        return handle_ && execute_ && complete_;
    }

    inline static void DoExeceute()
    {
        execute_ ? execute_(handle_) : (void)0;
    }
    inline static void DoComplete()
    {
        complete_ ? complete_(handle_) : (void)0;
        Reset();
        handle_ = nullptr;
        execute_ = nullptr;
        complete_ = nullptr;
    }
    inline static bool HasResolved()
    {
        return handle_ && (queueWorkId_ == handle_) && !cancelWorkId_;
    }
    inline static bool HasRejected()
    {
        return handle_ && !queueWorkId_ && (cancelWorkId_ == handle_);
    }
protected:
    inline static InteropNativePointer handle_ = nullptr;
    inline static void (*execute_)(InteropNativePointer handle) = nullptr;
    inline static void (*complete_)(InteropNativePointer handle) = nullptr;
    inline static InteropNativePointer queueWorkId_ = nullptr;
    inline static InteropNativePointer cancelWorkId_ = nullptr;

    inline static InteropAsyncWork CreateWork(InteropVMContext context,
        InteropNativePointer handle,
        void (*execute)(InteropNativePointer handle),
        void (*complete)(InteropNativePointer handle))
    {
        handle_ = handle;
        execute_ = execute;
        complete_ = complete;
        return InteropAsyncWork {
            .workId = handle,
            .queue = &AsyncWorkTestHelper::Queue,
            .cancel = &AsyncWorkTestHelper::Cancel,
        };
    };
    inline static void Queue(InteropNativePointer workId)
    {
        queueWorkId_ = workId;
    }
    inline static void Cancel(InteropNativePointer workId)
    {
        cancelWorkId_ = workId;
    }
    inline static InteropAsyncWorker interopAsyncWorker_ = {
        .createWork = &AsyncWorkTestHelper::CreateWork
    };
};
} // namespace OHOS::Ace::NG