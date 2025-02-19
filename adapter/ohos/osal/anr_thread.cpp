/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "base/utils/utils.h"
#include "core/common/anr_thread.h"

#include "xcollie/watchdog.h"

namespace OHOS::Ace {
namespace  {
constexpr uint64_t SECOND_TO_MILLISECOND = 1000;
} // namespace

void AnrThread::Start() {}

void AnrThread::Stop() {}

bool AnrThread::PostTaskToTaskRunner(Task&& task, uint32_t delayTime, const std::string& name)
{
    CHECK_NULL_RETURN(task, false);
    if (delayTime > 0) {
        OHOS::HiviewDFX::Watchdog::GetInstance().RunOneShotTask(
            name, std::move(task), delayTime * SECOND_TO_MILLISECOND);
    } else {
        OHOS::HiviewDFX::Watchdog::GetInstance().RunOneShotTask(name, std::move(task));
    }
    return true;
}
} // namespace OHOS::Ace
