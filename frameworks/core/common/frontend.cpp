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

#include "core/common/frontend.h"

namespace OHOS::Ace {
Frontend::~Frontend()
{
    std::lock_guard lock(destructMutex_);
    LOGI("Frontend destroyed");
}

bool Frontend::MaybeRelease()
{
    CHECK_NULL_RETURN(taskExecutor_, true);
    if (taskExecutor_->WillRunOnCurrentThread(TaskExecutor::TaskType::JS)) {
        LOGI("Destroy Frontend on JS thread.");
        return true;
    } else {
        std::lock_guard lock(destructMutex_);
        LOGI("Post Destroy Frontend Task to JS thread.");
        return !taskExecutor_->PostTask([this] { delete this; }, TaskExecutor::TaskType::JS, "ArkUIFrontendRelease",
            TaskExecutor::GetPriorityTypeWithCheck(PriorityType::VIP));
    }
}

std::string Frontend::stateToString(int state)
{
    static const char* stateMap[7] = {
        "ON_CREATE",
        "ON_DESTROY",
        "ON_SHOW",
        "ON_HIDE",
        "ON_ACTIVE",
        "ON_INACTIVE",
        "UNDEFINE",
    };
    return stateMap[state];
}
} // namespace OHOS::Ace
