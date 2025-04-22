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
#include "base/log/log_wrapper.h"
#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"

namespace OHOS::Ace::NG {
class AsyncWorkHelper final {
public:
    using Handler = Ark_NativePointer;
    using AsyncExecFunc = std::function<void()>;
    static Ark_AsyncWork CreateWork(Ark_VMContext vmContext, const Ark_AsyncWorker& asyncWorker,
                                    AsyncExecFunc&& execFunc)
    {
        CHECK_NULL_RETURN(asyncWorker.createWork, {});
        auto handler = static_cast<Handler>(new AsyncExecFunc(std::move(execFunc)));
        return (*asyncWorker.createWork)(vmContext, handler, &Execute, &Destroy);
    }

    static void FinishWork(const Ark_AsyncWork& work, int32_t errCode)
    {
        if (errCode == ERROR_CODE_NO_ERROR) {
            CHECK_NULL_VOID(work.queue);
            (*work.queue)(work.workId);
        } else {
            CHECK_NULL_VOID(work.cancel);
            (*work.cancel)(work.workId);
        }
    }

private:
    static void Execute(Handler handler)
    {
        if (auto execFunc = static_cast<AsyncExecFunc*>(handler); execFunc) {
            (*execFunc)();
        }
    }
    static void Destroy(Handler handler)
    {
        delete static_cast<AsyncExecFunc*>(handler);
    }
};
} // namespace OHOS::Ace::NG