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

#include "image_source_ohos.h"

namespace OHOS::Ace::Napi {
std::shared_ptr<ImageSource> ImageSource::Create(const uint8_t* data, uint32_t size)
{
    uint32_t errorCode;
    Media::SourceOptions options;
    auto src = Media::ImageSource::CreateImageSource(data, size, options, errorCode);
    if (Media::SUCCESS != errorCode) {
        HILOGW("create image source failed.(%{public}u)", errorCode);
        return nullptr;
    }
    return std::make_shared<ImageSourceOhos>(std::move(src));
}

std::shared_ptr<Media::PixelMap> ImageSourceOhos::CreatePixelMap(
    uint32_t index, const Size& size, AIImageQuality imageQuality, bool isHdrDecodeerNeed)
{
    Media::DecodeOptions options;
    options.preferDma = true;
    // only hdr image need to decoder in hdr mode
    if (isHdrDecodeerNeed) {
        options.desiredDynamicRange = Media::DecodeDynamicRange::AUTO;
    }
    options.resolutionQuality = static_cast<Media::ResolutionQuality>(imageQuality);
    // pass imageQuality to image framework
    if (size.first > 0 && size.second > 0) {
        options.desiredSize = { size.first, size.second };
    }
    uint32_t errorCode;
    auto pixmap = imageSource_->CreatePixelMapEx(index, options, errorCode);
    if (Media::SUCCESS != errorCode) {
        HILOGW("create PixelMap failed, index = %{public}u, err = %{public}u", index, errorCode);
        return nullptr;
    }
    return std::move(pixmap);
}

Size ImageSourceOhos::GetImageSize()
{
    Media::ImageInfo info;
    auto errorCode = imageSource->GetImageInfo(info);
    if (Media::SUCCESS != errorCode) {
        HILOGW("get imageinfo failed.(%{public}u)", errorCode);
        return { 0, 0 };
    }
    return { info.size.width, info.size.height };
}

} // namespace OHOS::Ace::Napi