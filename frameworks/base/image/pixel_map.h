/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_IMAGE_ACE_PIXEL_MAP_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_IMAGE_ACE_PIXEL_MAP_H

#include "base/memory/ace_type.h"

namespace OHOS {

namespace Media {
class PixelMap;
}

namespace Ace {

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
};

enum class AlphaType : int32_t {
    IMAGE_ALPHA_TYPE_UNKNOWN = 0,
    IMAGE_ALPHA_TYPE_OPAQUE = 1,   // image pixels are stored as opaque.
    IMAGE_ALPHA_TYPE_PREMUL = 2,   // image have alpha component, and all pixels have premultiplied by alpha value.
    IMAGE_ALPHA_TYPE_UNPREMUL = 3, // image have alpha component, and all pixels stored without premultiply alpha value.
};

class ACE_EXPORT PixelMap : public AceType {
    DECLARE_ACE_TYPE(PixelMap, AceType)

public:
    static RefPtr<PixelMap> Create(std::unique_ptr<Media::PixelMap>&& pixmap);
    static RefPtr<PixelMap> CreatePixelMap(void* sptrAddr);
    /**
     * @param ptr: drawable pointer of type Napi::DrawableDescriptor&
     */
    static RefPtr<PixelMap> GetFromDrawable(void* ptr);
    static RefPtr<PixelMap> CreatePixelMapFromDataAbility(void* uniquePtr);
    static RefPtr<PixelMap> ConvertSkImageToPixmap(
        const uint32_t* colors, uint32_t colorLength, int32_t width, int32_t height);
    virtual int32_t GetWidth() const = 0;
    virtual int32_t GetHeight() const = 0;
    virtual const uint8_t* GetPixels() const = 0;
    virtual PixelFormat GetPixelFormat() const = 0;
    virtual AlphaType GetAlphaType() const = 0;
    virtual int32_t GetRowBytes() const = 0;
    virtual int32_t GetByteCount() const = 0;
    virtual void* GetPixelManager() const = 0;
    virtual void* GetRawPixelMapPtr() const = 0;
    virtual std::string GetId() = 0;
    virtual std::string GetModifyId() = 0;
    virtual std::shared_ptr<Media::PixelMap> GetPixelMapSharedPtr() = 0;
    virtual void* GetWritablePixels() const = 0;

    static void* GetReleaseContext(const RefPtr<PixelMap>& pixelMap);
    // passed to SkImage to release PixelMap shared_ptr
    static void ReleaseProc(const void* /* pixels */, void* context);
};

} // namespace Ace
} // namespace OHOS

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_IMAGE_ACE_PIXEL_MAP_H
