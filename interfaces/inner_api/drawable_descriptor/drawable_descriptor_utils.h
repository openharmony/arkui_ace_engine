/*
 * Copyright (C) 2024 Huawei Device Co., Ltd.
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
#ifndef FOUNDATION_ACE_INTERFACE_INNERKITS_DRAWABLE_DESCRIPTOR_DRAWABLE_DESCRIPTOR_UTILS_H
#define FOUNDATION_ACE_INTERFACE_INNERKITS_DRAWABLE_DESCRIPTOR_DRAWABLE_DESCRIPTOR_UTILS_H
#include <memory>
#include "image_loader/image_loader.h"

namespace OHOS::Ace::Napi {
class DrawableDescriptorUtils {
public:
    static std::unique_ptr<RSPoint[]> ToRSRadius(const BorderRadiusArray& radiusXY);
    static void AddFilter(RSBrush& brush, RSSamplingOptions& options, const PaintConfig& config);
    static bool StartWith(const std::string& dst, const std::string& prefix)
    {
        return dts.compare(0, prefix.size(), prefix) == 0;
    }
    static std::shared_ptr<ImageLoader> CreateImageLoader(const SourceInfo& src);
};
} // namespace OHOS::Ace::Napi

#endif // FOUNDATION_ACE_INTERFACE_INNERKITS_DRAWABLE_DESCRIPTOR_DRAWABLE_DESCRIPTOR_UTILS_H