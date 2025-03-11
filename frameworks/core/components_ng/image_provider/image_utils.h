/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_IMAGE_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_IMAGE_UTILS_H

#include <cstdint>

#include "core/common/container.h"

namespace OHOS::Ace::NG {
class ImageUtils {
public:
    static void PostToUI(std::function<void()>&& task, const std::string& name,
        const int32_t containerId = Container::CurrentId(), PriorityType priorityType = PriorityType::VIP);

    static void PostDelayedTaskToUI(std::function<void()>&& task, uint32_t delayTime, const std::string& name,
        const int32_t containerId = Container::CurrentId(), PriorityType priorityType = PriorityType::VIP);

    static void PostToBg(std::function<void()>&& task, const std::string& name,
        const int32_t containerId = Container::CurrentId(), PriorityType priorityType = PriorityType::IMMEDIATE);

    inline static std::string GenerateImageKey(const ImageSourceInfo& src, const NG::SizeF& targetSize)
    {
        return src.GetTaskKey() + "&size=" + targetSize.ToString();
    }

private:
    // helper function to post task to [TaskType] thread
    static void PostTask(std::function<void()>&& task, TaskExecutor::TaskType taskType, const char* taskTypeName,
        PriorityType priorityType = PriorityType::LOW);
    static void PostDelayedTask(std::function<void()>&& task, TaskExecutor::TaskType taskType, uint32_t delayTime,
        const char* taskTypeName, PriorityType priorityType = PriorityType::LOW);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_IMAGE_UTILS_H
