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

#include "core/drawable/animated_drawable_descriptor.h"

namespace OHOS::Ace {
namespace {
constexpr int32_t DEFAULT_DURATION = 100;
} // namespace

RefPtr<PixelMap> AnimatedDrawableDescriptor::GetPixelMap()
{
    if (pixelMapList_.empty()) {
        return nullptr;
    }
    return pixelMapList_.front();
}

int32_t AnimatedDrawableDescriptor::GetTotalDuration()
{
    auto size = pixelMapList_.size();
    if (totalDuration_ < 0) {
        totalDuration_ = static_cast<int32_t>(size);
    }
    return totalDuration_;
}

std::vector<int32_t> AnimatedDrawableDescriptor::GetDurations()
{
    auto size = pixelMapList_.size();
    if (durations_.empty()) {
        durations_.resize(size, DEFAULT_DURATION);
    }
    return durations_;
}
} // namespace OHOS::Ace
