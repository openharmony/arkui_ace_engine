/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "adapter/ohos/osal/image_packer_ohos.h"

#include "base/image/pixel_map.h"

namespace OHOS::Ace {
RefPtr<ImagePacker> ImagePacker::Create()
{
    return MakeRefPtr<ImagePackerOhos>();
}

ImagePackerOhos::ImagePackerOhos()
{
    imagePacker_ = std::make_unique<Media::ImagePacker>();
}

uint32_t ImagePackerOhos::AddImage(PixelMap& pixelMap)
{
    return imagePacker_->AddImage(*(pixelMap.GetPixelMapSharedPtr()));
}

uint32_t ImagePackerOhos::StartPacking(uint8_t* data, uint32_t maxSize, const PackOption& option)
{
    Media::PackOption packOption {option.format, option.quality, option.numberHint};
    return imagePacker_->StartPacking(data, maxSize, packOption);
}

uint32_t ImagePackerOhos::StartPacking(const std::string& filePath, const PackOption& option)
{
    Media::PackOption packOption {option.format, option.quality, option.numberHint};
    return imagePacker_->StartPacking(filePath, packOption);
}

uint32_t ImagePackerOhos::FinalizePacking(int64_t& packedSize)
{
    return imagePacker_->FinalizePacking(packedSize);
}
} // namespace OHOS::Ace
