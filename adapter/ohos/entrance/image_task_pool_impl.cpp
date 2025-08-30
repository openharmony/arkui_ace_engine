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

#include "adapter/ohos/entrance/image_task_pool_impl.h"
#include "base/log/log_wrapper.h"

namespace OHOS::Ace {
ImageTaskPool* ImageTaskPool::GetInstance()
{
    static ImageTaskPoolImpl instance;
    return &instance;
}

ImageTaskPoolImpl::ImageTaskPoolImpl()
{
    queue_ = std::make_unique<ffrt::queue>(ffrt::queue_concurrent, "ImageTaskPool",
        ffrt::queue_attr().qos(ffrt_qos_user_interactive).max_concurrency(defaultMaxConcurrency_));
}

void ImageTaskPoolImpl::PostTask(Task&& task, const std::string& name)
{
    if (queue_ == nullptr) {
        LOGE("AceImage ImageTaskPool Queue is null, cannot post task.");
        return;
    }
    queue_->submit_h(std::move(task));
}
} // namespace OHOS::Ace