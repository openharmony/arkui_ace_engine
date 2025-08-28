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

#include <numeric>

namespace OHOS::Ace {
namespace {
constexpr int32_t DEFAULT_DURATION = 1000;
} // namespace

RefPtr<PixelMap> AnimatedDrawableDescriptor::GetPixelMap()
{
    if (pixelMapList_.empty()) {
        return nullptr;
    }
    return pixelMapList_.front();
}

void AnimatedDrawableDescriptor::SetTotalDuration(const int32_t totalDuration)
{
    if (totalDuration <= 0) {
        totalDuration_ = DEFAULT_DURATION * static_cast<int32_t>(pixelMapList_.size());
    } else {
        totalDuration_ = totalDuration;
    }
}

int32_t AnimatedDrawableDescriptor::GetTotalDuration()
{
    if (totalDuration_ <= 0) {
        totalDuration_ = DEFAULT_DURATION * static_cast<int32_t>(pixelMapList_.size());
    }
    return totalDuration_;
}

void AnimatedDrawableDescriptor::SetDurations(const std::vector<int32_t>& durations)
{
    durations_ = durations;
    totalDuration_ = std::accumulate(durations_.begin(), durations_.end(), 0);
}

std::vector<int32_t> AnimatedDrawableDescriptor::GetDurations()
{
    auto size = pixelMapList_.size();
    if (durations_.empty() && size > 0) {
        durations_.resize(size, GetTotalDuration() / size);
    }
    return durations_;
}
} // namespace OHOS::Ace
