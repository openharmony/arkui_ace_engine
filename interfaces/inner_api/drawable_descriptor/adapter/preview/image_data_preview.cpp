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

#include "base/image_data.h"
#include "base/pixel_map.h"

namespace OHOS {
namespace Ace {
namespace Drawable {
class ImageDataPreview final : public ImageData {
public:
    ImageDataPreview() = default;
    ~ImageDataPreview() override = default;

    std::shared_ptr<PixelMap> CreatePixelMap(const DecodeParmas& params) override;
};

std::shared_ptr<ImageData> ImageData::Create(const uint8_t* data, uint32_t size)
{
    return nullptr;
}

std::shared_ptr<PixelMap> ImageDataPreview::CreatePixelMap(const DecodeParmas& params)
{
    return nullptr;
}
} // namespace Drawable
} // namespace Ace
} // namespace OHOS
