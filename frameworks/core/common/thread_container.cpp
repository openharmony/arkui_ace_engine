/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/common/thread_container.h"

#include "core/common/task_runner_adapter_factory.h"

namespace OHOS::Ace {
ThreadContainer::ThreadContainer(std::string namePrefix, uint64_t mask)
{
    if (mask & ThreadType::Platform) {
        platformThread = TaskRunnerAdapterFactory::Create(false, namePrefix + ".platform");
    }

    if (mask & ThreadType::UI) {
        uiThread = TaskRunnerAdapterFactory::Create(false, namePrefix + ".ui");
    }

    if (mask & ThreadType::GPU) {
        gpuThread = TaskRunnerAdapterFactory::Create(false, namePrefix + ".gpu");
    }

    if (mask & ThreadType::IO) {
        ioThread = TaskRunnerAdapterFactory::Create(false, namePrefix + ".io");
    }
}
} // namespace OHOS::Ace
