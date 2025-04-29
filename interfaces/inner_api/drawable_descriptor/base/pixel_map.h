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

#ifndef FOUNDATION_ACE_INTERFACE_INNERAPI_BASE_PIXEL_MAP_H
#define FOUNDATION_ACE_INTERFACE_INNERAPI_BASE_PIXEL_MAP_H

#include <cstdint>
#include <memory>

#include "marcos.h"

namespace OHOS {
namespace Ace {
class Rect;
}
namespace Media {
class PixelMap;
}

namespace Ace {
namespace Drawable {

enum class PixelFormat : int32_t {
    UNKNOWN = 0,
    ARGB_8888 = 1, // Each pixel is stored on 4 bytes.
    RGB_565 = 2,   // Each pixel is stored on 2 bytes
    RGBA_8888 = 3,
    BGRA_8888 = 4,
    RGB_888 = 5,
    ALPHA_8 = 6,
    RGBA_F16 = 7,
    NV21 = 8, // Each pixel is stored on 3/2 bytes.
    NV12 = 9,
    CMYK = 10,
    YCBCR_P010 = 11,
    YCRCB_P010 = 12,
    RGBA_1010102 = 14,
};

enum class AlphaType : int32_t {
    IMAGE_ALPHA_TYPE_UNKNOWN = 0,
    IMAGE_ALPHA_TYPE_OPAQUE = 1,   // image pixels are stored as opaque.
    IMAGE_ALPHA_TYPE_PREMUL = 2,   // image have alpha component, and all pixels have premultiplied by alpha value.
    IMAGE_ALPHA_TYPE_UNPREMUL = 3, // image have alpha component, and all pixels stored without premultiply alpha value.
};

enum class AllocatorType : int32_t {
    // keep same with java AllocatorType
    DEFAULT = 0,
    HEAP_ALLOC = 1,
    SHARE_MEM_ALLOC = 2,
    CUSTOM_ALLOC = 3, // external
    DMA_ALLOC = 4,    // SurfaceBuffer
};

enum class ResizableOption {
    LEFT,
    RIGHT,
    TOP,
    BOTTOM,
};

enum class AceAntiAliasingOption : int32_t {
    NONE = 0,
    LOW = 1,
    MEDIUM = 2,
    HIGH = 3,
};

class PixelMap {
public:
    static std::shared_ptr<PixelMap> Create(std::unique_ptr<Media::PixelMap>&& pixmap);
    static std::shared_ptr<PixelMap> Create(const std::shared_ptr<Media::PixelMap>& pixmap);

    virtual int32_t GetWidth() const;
    virtual int32_t GetHeight() const;
    virtual const uint8_t* GetPixels() const;
    virtual int32_t GetRowStride() const;
    virtual int32_t GetRowBytes() const;
    virtual int32_t GetByteCount() const;
    virtual bool IsHdr() const;
    virtual void* GetRawPixelMapPtr() const;
    virtual std::shared_ptr<Media::PixelMap> GetPixelMapSharedPtr();
};
} // namespace Drawable
} // namespace Ace
} // namespace OHOS
#endif // FOUNDATION_ACE_INTERFACE_INNERAPI_BASE_PIXEL_MAP_H
