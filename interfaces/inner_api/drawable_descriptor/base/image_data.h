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
#ifndef FOUNDATION_ACE_INTERFACE_DRAWABLE_IMAGE_DATA_H
#define FOUNDATION_ACE_INTERFACE_DRAWABLE_IMAGE_DATA_H

#include <memory>
#include <cstdint>

#include "base/pixel_map.h"

namespace OHOS {
namespace Ace {
namespace Drawable {

struct DecodeParmas {
    int32_t width;
    int32_t height;
};

class ImageData {
public:
    ImageData() = default;
    virtual ~ImageData() = default;

    static std::shared_ptr<ImageData> Create(const uint8_t* data, uint32_t size);

    virtual std::shared_ptr<PixelMap> CreatePixelMap(const DecodeParmas& params) = 0;
};
} // namespace Drawable
} // namespace Ace
} // namespace OHOS

#endif // FOUNDATION_ACE_INTERFACE_DRAWABLE_IMAGE_DATA_H