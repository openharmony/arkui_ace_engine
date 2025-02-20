/*
 * Copyright (C) 2025 Huawei Device Co., Ltd.
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
#ifndef FOUNDATION_ACE_INTERFACE_DRAWABLE_DESCRIPTOR_ANIMATED_DRAWABLE_DESCRIPTOR_H
#define FOUNDATION_ACE_INTERFACE_DRAWABLE_DESCRIPTOR_ANIMATED_DRAWABLE_DESCRIPTOR_H

#include "core/drawable_descriptor_base.h"

namespace OHOS {
namespace Ace {
namespace Drawable {
class DRAWABLE_FORCE_EXPORT AnimatedDrawableDescriptor : public DrawableDescriptor {
public:
    AnimatedDrawableDescriptor(
        std::vector<std::shared_ptr<Media::PixelMap>> pixelMaps, int32_t duration, int32_t iterations)
        : pixelMapList_(std::move(pixelMaps)), duration_(duration), iterations_(iterations) {};
    ~AnimatedDrawableDescriptor() override = default;
    std::shared_ptr<Media::PixelMap> GetPixelMap() override;
    DrawableType GetDrawableType() override;
    std::vector<std::shared_ptr<Media::PixelMap>> GetPixelMapList();
    int32_t GetDuration();
    int32_t GetIterations();
    void SetDuration(int32_t duration);
    void SetIterations(int32_t iterations);

private:
    std::vector<std::shared_ptr<Media::PixelMap>> pixelMapList_;
    int32_t duration_ = -1;
    int32_t iterations_ = 1;
};
} // namespace Drawable
} // namespace Ace
} // namespace OHOS

#endif // FOUNDATION_ACE_INTERFACE_INNERKITS_DRAWABLE_DESCRIPTOR_ANIMATED_DRAWABLE_DESCRIPTOR_H