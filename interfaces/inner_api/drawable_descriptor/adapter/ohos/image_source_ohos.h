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
#ifndef FOUNDATION_ACE_INTERFACE_INNERKITS_DRAWABLE_DESCRIPTOR_ADAPTER_OHOS_IMAGE_SOURCE_OHOS_H
#define FOUNDATION_ACE_INTERFACE_INNERKITS_DRAWABLE_DESCRIPTOR_ADAPTER_OHOS_IMAGE_SOURCE_OHOS_H
#include <memory>
#include "../../base/image_source.h"
// include multimedia's header files
#include "pixel_map.h"
#include "image_source.h"
#include "media_errors.h"

namespace OHOS::Ace::Napi {
class ImageSourceOhos : public ImageSource {
public:
    ImageSourceOhos() = default;
    ~ImageSourceOhos() override = default;
    explicit ImageSourceOhos(std::unique_ptr<Media::ImageSource>&& source) : imageSource_(std::move(source)) {}
    std::shared_ptr<Media::PixelMap> CreatePixelMap(uint32_t index, const Size& size,
        AIImageQuality imageQuality, bool isHdrDecodeerNeed) override;
    Size GetImageSize() override;

private:
    std::unique_ptr<Media::ImageSource> imageSource_;
};
} // namespace OHOS::Ace::Napi

#endif // FOUNDATION_ACE_INTERFACE_INNERKITS_DRAWABLE_DESCRIPTOR_ADAPTER_OHOS_IMAGE_SOURCE_OHOS_H