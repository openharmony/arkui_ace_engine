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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_IMAGE_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_IMAGE_UTILS_H

#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
class ImageUtils {
public:
    static void PostToUI(std::function<void()>&& task);
    static void PostToBg(std::function<void()>&& task);

    inline static std::string GenerateImageKey(const ImageSourceInfo& src, const NG::SizeF& targetSize)
    {
        return src.GetKey() + "&size=" + targetSize.ToString();
    }

private:
    // helper function to post task to [TaskType] thread
    static void PostTask(std::function<void()>&& task, TaskExecutor::TaskType taskType, const char* taskTypeName);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_IMAGE_UTILS_H
