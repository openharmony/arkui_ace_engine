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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_IMAGE_IMAGE_TASK_POOL_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_IMAGE_IMAGE_TASK_POOL_H

#include <cstdint>
#include <functional>
#include <string>

namespace OHOS {
namespace Ace {
const int32_t DEFAULT_MAX_CONCURRENCY = 8;
class ImageTaskPool {
public:
    using Task = std::function<void()>;
    ImageTaskPool(const ImageTaskPool&) = delete;
    ImageTaskPool& operator=(const ImageTaskPool&) = delete;
    virtual ~ImageTaskPool() = default;

    static ImageTaskPool* GetInstance();

    virtual void PostTask(Task&& task, const std::string& name) = 0;

protected:
    ImageTaskPool() = default;
    int32_t defaultMaxConcurrency_ = DEFAULT_MAX_CONCURRENCY;
};
} // namespace Ace
} // namespace OHOS

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_IMAGE_IMAGE_TASK_POOL_H
