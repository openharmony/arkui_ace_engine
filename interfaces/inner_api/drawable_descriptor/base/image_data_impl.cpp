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

#include <memory>

#include "image_data.h"
#include "image_source.h"
#include "image_type.h"
#include "media_errors.h"

#include "base/image_data.h"
#include "base/log.h"
#include "base/pixel_map.h"

namespace OHOS {
namespace Ace {
namespace Drawable {
class ImageDataImpl final : public ImageData {
public:
    ImageDataImpl() = default;
    ~ImageDataImpl() override = default;

    explicit ImageDataImpl(std::unique_ptr<Media::ImageSource>&& imageSource) : imageSource_(std::move(imageSource)) {}

    std::shared_ptr<PixelMap> CreatePixelMap(const DecodeParmas& params) override;

private:
    std::unique_ptr<Media::ImageSource> imageSource_;
};

std::shared_ptr<ImageData> ImageData::Create(const uint8_t* data, uint32_t size)
{
    uint32_t errorCode;
    Media::SourceOptions options;
    auto src = Media::ImageSource::CreateImageSource(data, size, options, errorCode);
    if (errorCode != Media::SUCCESS) {
        HILOGE("create image source failed by uint8 data, its size = %{public}d", size);
        return nullptr;
    }
    return std::make_shared<ImageDataImpl>(std::move(src));
}

std::shared_ptr<PixelMap> ImageDataImpl::CreatePixelMap(const DecodeParmas& params)
{
    uint32_t errorCode;
    Media::DecodeOptions decodeOpts;
    auto pixelMap = imageSource_->CreatePixelMap(decodeOpts, errorCode);
    if (errorCode != Media::SUCCESS) {
        HILOGE("create pixel map failed");
        return nullptr;
    }
    return PixelMap::Create(std::move(pixelMap));
}
} // namespace Drawable
} // namespace Ace
} // namespace OHOS
