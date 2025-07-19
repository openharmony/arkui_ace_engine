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

#include <vector>

#include "base/image/image_source.h"
#include "base/image/pixel_map.h"

namespace OHOS::Ace {

extern "C" ACE_FORCE_EXPORT int32_t OH_ACE_PixelMapDrawableDescriptor_SetRawData(
    void* object, uint8_t* data, size_t len)
{
    auto* drawable = reinterpret_cast<PixelMapDrawableDescriptor*>(object);
    if (drawable) {
        std::vector<uint8_t> result(data, data + len);
        drawable->SetRawData(result);
        return 1;
    }
    return 0;
}

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
    if (rawData_.empty()) {
        return;
    }
    auto imageSource = ImageSource::Create(rawData_.data(), rawData_.size());
    if (!imageSource) {
        return;
    }
    DecodeOptions options;
    options.desiredFormat = PixelFormat::BGRA_8888;
    auto pixelmap = imageSource->CreatePixelMap(options);
    pixelmap_ = pixelmap;
}

} // namespace OHOS::Ace
