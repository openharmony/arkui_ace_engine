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
#include "animated_drawable_descriptor.h"
#include "include/core/SkImage.h"
#include "include/core/SkRect.h"

namespace OHOS::Ace::Napi {

const int DEFAULT_DURATION = 1000;
std::shared_ptr<Media::PixelMap> AnimatedDrawableDescriptor::GetPixelMap()
{
    if (pixelMapList_.empty()) {
        return nullptr;
    }
    return pixelMapList_[0];
}

DrawableDescriptor::DrawableType AnimatedDrawableDescriptor::GetDrawableType()
{
    return DrawableType::ANIMATED;
}

std::vector<std::shared_ptr<Media::PixelMap>> AnimatedDrawableDescriptor::GetPixelMapList()
{
    return pixelMapList_;
}

int32_t AnimatedDrawableDescriptor::GetDuration()
{
    if (duration_ <= 0) {
        duration_ = DEFAULT_DURATION * static_cast<int32_t>(pixelMapList_.size());
    }
    return duration_;
}

int32_t AnimatedDrawableDescriptor::GetIterations()
{
    if (iterations_ < -1) {
        iterations_ = 1;
    }
    return iterations_;
}

void AnimatedDrawableDescriptor::SetDuration(int32_t duration)
{
    if (duration <= 0) {
        duration_ = DEFAULT_DURATION * static_cast<int32_t>(pixelMapList_.size());
    } else {
        duration_ = duration;
    }
}

void AnimatedDrawableDescriptor::SetIterations(int32_t iterations)
{
    if (iterations < -1) {
        iterations_ = 1;
    } else {
        iterations_ = iterations;
    }
}
} // namespace OHOS::Ace::Napi