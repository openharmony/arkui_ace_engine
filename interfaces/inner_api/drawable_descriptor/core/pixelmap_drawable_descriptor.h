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
#ifndef FOUNDATION_ACE_INTERFACE_DRAWABLE_DESCRIPTOR_PIXELMAP_DRAWABLE_DESCRIPTOR_H
#define FOUNDATION_ACE_INTERFACE_DRAWABLE_DESCRIPTOR_PIXELMAP_DRAWABLE_DESCRIPTOR_H

#include <cstdint>
#include <memory>

#include "base/image_data.h"
#include "base/marcos.h"
#include "base/pixel_map.h"
#include "core/drawable_descriptor_base.h"

namespace OHOS {
namespace Ace {
namespace Drawable {
class DRAWABLE_FORCE_EXPORT PixelmapDrawableDescriptor : public DrawableDescriptor {
public:
    PixelmapDrawableDescriptor() = default;

    ~PixelmapDrawableDescriptor() override = default;

    std::shared_ptr<Media::PixelMap> GetPixelMap() override;

    void SetPixelMap(const std::shared_ptr<Media::PixelMap>& pixelMap) override;

    int32_t GetOriginalWidth() const override;

    int32_t GetOriginalHeight() const override;

    DrawableType GetDrawableType() const override;

    DrawableInfo FetchSync() override;

    void Fetch() override;

    void RegisterRedrawCallback(RedrawCallback&& callback) override;

    void Draw(RSCanvas& canvas, PaintConfig config) override;

    void Validate() override;

    void LoadImageData() override;

    void Decode() override;

protected:
    std::shared_ptr<PixelMap> pixelMap_;
};
} // namespace Drawable
} // namespace Ace
} // namespace OHOS

#endif // FOUNDATION_ACE_INTERFACE_DRAWABLE_DESCRIPTOR_PIXELMAP_DRAWABLE_DESCRIPTOR_H
