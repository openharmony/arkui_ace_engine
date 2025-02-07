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
#ifndef FOUNDATION_ACE_INTERFACE_INNERKITS_DRAWABLE_DESCRIPTOR_PIXELMAP_DRAWABLE_DESCRIPTOR_H
#define FOUNDATION_ACE_INTERFACE_INNERKITS_DRAWABLE_DESCRIPTOR_PIXELMAP_DRAWABLE_DESCRIPTOR_H

#include "drawable_descriptor_base.h"

#include "base/marcos.h"

namespace OHOS {
namespace Ace {
namespace Napi {

class DRAWABLE_FORCE_EXPORT PixelmapDrawableDescriptor : public DrawableDescriptor {
public:
    PixelmapDrawableDescriptor() = default;
    explicit PixelmapDrawableDescriptor(std::shared_ptr<Media::PixelMap> pixelMap) : DrawableDescriptor(pixelMap) {}
    PixelmapDrawableDescriptor(std::unique_ptr<uint8_t[]> mediaData, size_t len)
        : DrawableDescriptor(std::move(mediaData), len)
    {}
    ~PixelmapDrawableDescriptor() override = default;
    DrawableType GetDrawableType() override;
};
} // namespace Napi
} // namespace Ace
} // namespace OHOS

#endif // FOUNDATION_ACE_INTERFACE_INNERKITS_DRAWABLE_DESCRIPTOR_PIXELMAP_DRAWABLE_DESCRIPTOR_H
