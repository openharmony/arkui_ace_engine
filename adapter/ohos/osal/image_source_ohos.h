/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_OSAL_IMAGE_SOURCE_OHOS_H
#define FOUNDATION_ACE_ADAPTER_OHOS_OSAL_IMAGE_SOURCE_OHOS_H

#include <memory>

#include "image_source.h"

#include "base/image/image_source.h"
#include "base/image/pixel_map.h"

namespace OHOS::Ace {
class ImageSourceOhos : public ImageSource {
    DECLARE_ACE_TYPE(ImageSourceOhos, ImageSource)
public:
    explicit ImageSourceOhos(std::unique_ptr<Media::ImageSource>&& source) : imageSource_(std::move(source)) {}

    std::string GetProperty(const std::string& key) override;
    RefPtr<PixelMap> CreatePixelMap(
        const Size& size, uint32_t& errorCode, const PixelMapConfig& pixelMapConfig = {}) override;
    RefPtr<PixelMap> CreatePixelMap(
        uint32_t index, const Size& size, uint32_t& errorCode, const PixelMapConfig& pixelMapConfig = {}) override;
    RefPtr<PixelMap> CreatePixelMap() override;
#if defined(ACE_STATIC)
    /**
     * Only for ArkTS 1.2
     *
     * @param options: DecodeOptions media decode options
     **/
    RefPtr<PixelMap> CreatePixelMap(const DecodeOptions& options) override;
#endif
    Size GetImageSize() override;
    uint32_t GetFrameCount() override;
    std::string GetEncodedFormat() override;

private:
    std::unique_ptr<Media::ImageSource> imageSource_;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_ADAPTER_OHOS_OSAL_IMAGE_SOURCE_OHOS_H
