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

#include "core/drawable/pixel_map_drawable_descriptor.h"

#include <cstddef>
#include <cstdint>
#include <vector>

#include "base/image/image_source.h"
#include "base/image/pixel_map.h"

namespace OHOS::Ace {

RefPtr<PixelMap> PixelMapDrawableDescriptor::GetPixelMap()
{
    if (pixelmap_) {
        return pixelmap_;
    }
    CreatePixelMap();
    return pixelmap_;
}

void PixelMapDrawableDescriptor::CreatePixelMap()
{
    if (rawData_.len == 0 && rawData_.data == nullptr) {
        return;
    }
    uint32_t errorCode = 0;
    auto imageSource = ImageSource::Create(rawData_.data.get(), rawData_.len, errorCode);
    if (!imageSource) {
        return;
    }
    DecodeOptions options;
    options.desiredFormat = PixelFormat::BGRA_8888;
    auto pixelmap = imageSource->CreatePixelMap(options);
    pixelmap_ = pixelmap;
}

} // namespace OHOS::Ace
