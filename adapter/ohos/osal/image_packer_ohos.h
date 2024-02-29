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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_OSAL_IMAGE_PACKER_OHOS_H
#define FOUNDATION_ACE_ADAPTER_OHOS_OSAL_IMAGE_PACKER_OHOS_H

#include "image_packer.h"

#include "base/image/image_packer.h"

namespace OHOS::Ace {
class ImagePackerOhos : public ImagePacker {
    DECLARE_ACE_TYPE(ImagePackerOhos, ImagePacker)
public:
    ImagePackerOhos();

    uint32_t StartPacking(uint8_t* data, uint32_t maxSize, const PackOption& option) override;
    uint32_t StartPacking(const std::string& filePath, const PackOption& option) override;
    uint32_t AddImage(PixelMap& pixelMap) override;
    uint32_t FinalizePacking(int64_t& packedSize) override;

private:
    std::unique_ptr<Media::ImagePacker> imagePacker_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_ADAPTER_OHOS_OSAL_IMAGE_PACKER_OHOS_H
