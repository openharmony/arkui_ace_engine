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

#include <chrono>
#include <fstream>
#include <string>
#include <vector>
#include <memory>

#include "base/geometry/dimension.h"
#include "base/geometry/rect.h"
#include "base/geometry/ng/size_t.h"
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
    CUSTOM_ALLOC = 3,  // external
    DMA_ALLOC = 4, // SurfaceBuffer
};

enum class ResizableOption {
    LEFT,
    RIGHT,
    TOP,
    BOTTOM,
};

struct ImageResizableSlice {
    Dimension left;
    Dimension right;
    Dimension top;
    Dimension bottom;
    std::string ToString() const
    {
        std::string result;
        result.append("ImageResizableSlice: {");
        result.append("left: ");
        result.append(left.ToString());
        result.append(", right: ");
        result.append(right.ToString());
        result.append(", top: ");
        result.append(top.ToString());
        result.append(", bottom: ");
        result.append(bottom.ToString());
        result.append("}");
        return result;
    }
    bool operator==(const ImageResizableSlice& slice) const
    {
        return left == slice.left && right == slice.right && top == slice.top && bottom == slice.bottom;
    }
    bool Valid() const
    {
        return left.IsValid() || right.IsValid() || top.IsValid() || bottom.IsValid();
    }
    void SetResizableLeft(const Dimension& sliceDimension)
    {
        left = sliceDimension;
    }
    void SetResizableRight(const Dimension& sliceDimension)
    {
        right = sliceDimension;
    }
    void SetResizableBottom(const Dimension& sliceDimension)
    {
        bottom = sliceDimension;
    }
    void SetResizableTop(const Dimension& sliceDimension)
    {
        top = sliceDimension;
    }
    void SetEdgeSlice(ResizableOption direction, const Dimension& sliceDimension)
    {
        switch (direction) {
            case ResizableOption::TOP:
                SetResizableTop(sliceDimension);
                break;
            case ResizableOption::BOTTOM:
                SetResizableBottom(sliceDimension);
                break;
            case ResizableOption::LEFT:
                SetResizableLeft(sliceDimension);
                break;
            case ResizableOption::RIGHT:
                SetResizableRight(sliceDimension);
                break;
            default:
                break;
        }
    }
};

enum class AceAntiAliasingOption : int32_t {
    NONE = 0,
    LOW = 1,
    MEDIUM = 2,
    HIGH = 3,
};

enum class ScaleMode : int32_t {
    FIT_TARGET_SIZE = 0,
    CENTER_CROP = 1,
};

struct InitializationOptions {
    NG::SizeT<int32_t> size;
    PixelFormat srcPixelFormat = PixelFormat::BGRA_8888;
    PixelFormat pixelFormat = PixelFormat::UNKNOWN;
    AlphaType alphaType = AlphaType::IMAGE_ALPHA_TYPE_UNKNOWN;
    ScaleMode scaleMode = ScaleMode::FIT_TARGET_SIZE;
    int32_t srcRowStride = 0;
    bool editable = false;
    bool useSourceIfMatch = false;
    bool useDMA = false;
};

struct WritePixelsOptions {
    const uint8_t* source = nullptr;
    uint64_t bufferSize = 0;
    uint32_t offset = 0;
    uint32_t stride = 0;
    Rect region;
    PixelFormat srcPixelFormat = PixelFormat::BGRA_8888;
};

class ACE_FORCE_EXPORT PixelMap : public AceType {
    DECLARE_ACE_TYPE(PixelMap, AceType)

public:
    static RefPtr<PixelMap> Create(std::unique_ptr<Media::PixelMap>&& pixmap);
    static RefPtr<PixelMap> Create(const InitializationOptions& opts);
    static RefPtr<PixelMap> CreatePixelMap(void* sptrAddr);
    static RefPtr<PixelMap> CopyPixelMap(const RefPtr<PixelMap>& pixelMap);
    static RefPtr<PixelMap> DecodeTlv(std::vector<uint8_t>& buff);
    
    /**
     * @param ptr: drawable pointer of type Napi::DrawableDescriptor&
     */
    static RefPtr<PixelMap> GetFromDrawable(void* ptr);
    static bool GetPxielMapListFromAnimatedDrawable(void* ptr, std::vector<RefPtr<PixelMap>>& pixelMaps,
        int32_t& duration, int32_t& iterations);
    static RefPtr<PixelMap> CreatePixelMapFromDataAbility(void* uniquePtr);
    static RefPtr<PixelMap> ConvertSkImageToPixmap(
        const uint32_t* colors, uint32_t colorLength, int32_t width, int32_t height);
    virtual int32_t GetWidth() const = 0;
    virtual int32_t GetHeight() const = 0;
    virtual bool GetPixelsVec(std::vector<uint8_t>& data) const = 0;
    virtual const uint8_t* GetPixels() const = 0;
    virtual PixelFormat GetPixelFormat() const = 0;
    virtual AlphaType GetAlphaType() const = 0;
    virtual int32_t GetRowStride() const = 0;
    virtual int32_t GetRowBytes() const = 0;
    virtual int32_t GetByteCount() const = 0;
    virtual AllocatorType GetAllocatorType() const = 0;
    virtual bool IsHdr() const = 0;
    virtual void* GetPixelManager() const = 0;
    virtual void* GetRawPixelMapPtr() const = 0;
    virtual std::string GetId() = 0;
    virtual std::string GetModifyId() = 0;
    virtual std::shared_ptr<Media::PixelMap> GetPixelMapSharedPtr() = 0;
    virtual void* GetWritablePixels() const = 0;
    virtual void Scale(float xAxis, float yAxis) = 0;
    virtual void Scale(float xAxis, float yAxis, const AceAntiAliasingOption &option) = 0;

    static void* GetReleaseContext(const RefPtr<PixelMap>& pixelMap);
    // passed to SkImage to release PixelMap shared_ptr
    static void ReleaseProc(const void* /* pixels */, void* context);
    virtual void SavePixelMapToFile(const std::string& dst) const = 0;
    virtual RefPtr<PixelMap> GetCropPixelMap(const Rect& srcRect) = 0;
    virtual bool EncodeTlv(std::vector<uint8_t>& buff) = 0;
    virtual uint32_t WritePixels(const WritePixelsOptions& opts) = 0;
};

} // namespace Ace
} // namespace OHOS

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_IMAGE_ACE_PIXEL_MAP_H
