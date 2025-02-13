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
#ifndef FOUNDATION_ACE_DRAWABLE_DESCRIPTOR_DRAWABLE_DESCRIPTOR_BASE_H
#define FOUNDATION_ACE_DRAWABLE_DESCRIPTOR_DRAWABLE_DESCRIPTOR_BASE_H

#include <cstdint>
#include <memory>

#include "base/constants.h"
#include "base/error.h"
#include "base/marcos.h"

namespace OHOS {
namespace Media {
class PixelMap;
}

namespace Ace {
namespace Napi {
class DRAWABLE_FORCE_EXPORT DrawableDescriptor {
public:
    enum class DrawableType : int32_t {
        BASE = 0,
        LAYERED = 1,
        ANIMATED = 2,
        PIXELMAP = 3,
    };
    DrawableDescriptor() = default;

    DrawableDescriptor(std::unique_ptr<uint8_t[]>& mediaData, size_t len)
        : mediaData_(std::move(mediaData)), len_(len) {};

    virtual ~DrawableDescriptor() = default;

    // only for bundle manager
    virtual std::shared_ptr<Media::PixelMap> GetPixelMap() = 0;

    virtual DrawableType GetDrawableType() = 0;

    virtual Drawable::LoadError FetchSync(const Drawable::DrawableInfo& info) = 0;

    virtual void FetchAsync(const Drawable::DrawableInfo& info) = 0;

private:
    std::unique_ptr<uint8_t[]> mediaData_;
    size_t len_ = 0;
};

} // namespace Napi
} // namespace Ace
} // namespace OHOS
#endif // FOUNDATION_ACE_DRAWABLE_DESCRIPTOR_DRAWABLE_DESCRIPTOR_BASE_H
