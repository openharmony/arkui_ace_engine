/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/common/platform_res_register.h"

#include "base/log/log.h"

namespace OHOS::Ace {

void PlatformResRegister::RegisterEvent(const std::string& eventId, const EventCallback&& eventCallback)
{
    eventMap_[eventId] = std::move(eventCallback);
}

void PlatformResRegister::UnregisterEvent(const std::string& eventId)
{
    eventMap_.erase(eventId);
}

void PlatformResRegister::OnEvent(const std::string& eventId, const std::string& param)
{
    auto event = eventMap_.find(eventId);
    if (event != eventMap_.end() && event->second) {
        event->second(param);
    } else {
        LOGW("failed to find eventId = %{public}s", eventId.c_str());
    }
}

} // namespace OHOS::Ace
