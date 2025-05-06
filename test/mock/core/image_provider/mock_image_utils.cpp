/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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
#include <thread>

#include "mock_image_loader.h"

#include "core/components_ng/image_provider/image_utils.h"

namespace {
constexpr unsigned int MAX_THREADS = 2;
} // namespace

namespace OHOS::Ace {
std::vector<std::thread> g_threads;

namespace NG {
void ImageUtils::PostToUI(
    std::function<void()>&& task, const std::string& name, const int32_t containerId, PriorityType priorityType)
{
    if (task) {
        task();
    }
}

void ImageUtils::PostToBg(
    std::function<void()>&& task, const std::string& name, const int32_t containerId, PriorityType priorityType)
{
    // mock bg thread pool
    if (g_threads.size() > MAX_THREADS) {
        return;
    }
    g_threads.emplace_back(std::thread(task));
}

void ImageUtils::PostDelayedTaskToUI(std::function<void()>&& task, uint32_t delayTime, const std::string& name,
    const int32_t containerId, PriorityType priorityType)
{}
} // namespace NG
} // namespace OHOS::Ace
