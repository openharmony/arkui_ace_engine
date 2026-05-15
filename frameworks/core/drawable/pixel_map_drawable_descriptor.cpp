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
#include "base/error/error_code.h"
#include "core/components_ng/image_provider/image_utils.h"
#include "core/drawable/drawable_descriptor_loader.h"

namespace OHOS::Ace {
RefPtr<PixelMap> PixelMapDrawableDescriptor::GetPixelMap()
{
    std::scoped_lock<std::mutex> lock(loadMutx_);
    if (pixelmap_) {
        return pixelmap_;
    }
    CreatePixelMap();
    return pixelmap_;
}

DrawableDescriptorLoadResult PixelMapDrawableDescriptor::LoadSync()
{
    std::scoped_lock<std::mutex> lock(loadMutx_);
    if (pixelmap_) {
        return { pixelmap_->GetWidth(), pixelmap_->GetHeight(), 0 };
    }
    if (!info_ && !rawData_.data) {
        LOGW("Must to set resource/base64/file info.");
        return { 0, 0, ERROR_CODE_DRAWABLE_LOADER_ERROR };
    }
    CreatePixelMap();
    if (pixelmap_) {
        return { pixelmap_->GetWidth(), pixelmap_->GetHeight(), 0 };
    }
    return { 0, 0, ERROR_CODE_DRAWABLE_LOADER_ERROR };
}

void PixelMapDrawableDescriptor::LoadAsync(const LoadCallback&& callback)
{
    NG::ImageUtils::PostToBg(
        [weak = WeakClaim(this), callback = std::move(callback)]() {
            auto self = weak.Upgrade();
            CHECK_NULL_VOID(self);
            auto result = self->LoadSync();
            callback(result);
        },
        "PixelMapDrawableDescriptorLoadAsync");
}

void PixelMapDrawableDescriptor::CreatePixelMap()
{
    if (!rawData_.data && info_) {
        auto mediaData = DrawableDescriptorLoader::GetInstance()->LoadData(info_);
        rawData_.len = mediaData.len;
        rawData_.data.reset(mediaData.data.release());
    }
    if (rawData_.len == 0 || rawData_.data == nullptr) {
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
