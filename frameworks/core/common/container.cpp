/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/common/container.h"

#include "core/common/ace_engine.h"

namespace OHOS::Ace {

thread_local int32_t Container::currentId_ = INSTANCE_ID_UNDEFINED;

int32_t Container::CurrentId()
{
    return currentId_;
}

RefPtr<Container> Container::Current()
{
    return AceEngine::Get().GetContainer(currentId_);
}

RefPtr<TaskExecutor> Container::CurrentTaskExecutor()
{
    auto curContainer = Current();
    if (curContainer) {
        return curContainer->GetTaskExecutor();
    }
    return nullptr;
}

void Container::InitForThread(int32_t id)
{
    LOGI("InitForThread id:%{public}d", id);
    currentId_ = id;
}

} // namespace OHOS::Ace