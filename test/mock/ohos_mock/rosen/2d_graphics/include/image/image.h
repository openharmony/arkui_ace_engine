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

#ifndef IMAGE_H
#define IMAGE_H

#include "utils/data.h"
#include "utils/rect.h"

#include "bitmap.h"
#include "yuv_info.h"

namespace OHOS {
namespace Rosen {
namespace Drawing {
enum class BitDepth {
    KU8,
    KF16,
};

enum class CompressedType {
    NoneType,
    ETC2_RGB8_UNORM, // the same ad ETC1
    BC1_RGB8_UNORM,
    BC1_RGBA8_UNORM,
    ASTC_RGBA8_4x4,
    ASTC_RGBA8_6x6,
    ASTC_RGBA8_8x8,
    ASTC_RGBA10_4x4,
};

enum class TextureOrigin {
    TOP_LEFT,
    BOTTOM_LEFT,
};

enum class ScalingType {
    OPTION_AAE_ARSR = 0,
    OPTION_INVALID,
};

struct ScalingOption {
    RectI srcRect = RectI(0, 0, 0, 0);
    RectI dstRect = RectI(0, 0, 0, 0);
    ScalingType type = ScalingType::OPTION_AAE_ARSR;
};

enum class ScaleImageResult {
    SCALE_RESULT_SUCCESS = 0,
    SCALE_ERROR_INVALID_INPUT = 1,
    SCALE_ERROR_DEVICE_NOT_READY = 2,
    SCALE_ERROR_DEVICE_UNAVAILABLE = 3,
    SCALE_ERROR_DEVICE_FAILED = 4,
    SCALE_ERROR_UNSUPPORTED = 5
};

class Surface;

class TextureInfo {
public:
    /*
     * @brief  Sets the width value of Texture.
     */
    void SetWidth(int width)
    {
        width_ = width;
    }

    /*
     * @brief  Sets the height value of Texture.
     */
    void SetHeight(int height)
    {
        height_ = height;
    }

    /*
     * @brief  Used to say whether a texture has mip levels allocated or not.
     */
    void SetIsMipMapped(bool isMipMapped)
    {
        isMipMapped_ = isMipMapped;
    }

    /*
     * @brief         Sets the target type of texture to render.
     * @param target  The target type of texture.
     */
    void SetTarget(unsigned int target)
    {
        target_ = target;
    }

    /*
     * @brief     Sets the Id of texture to render.
     * @param id  Texture Id value.
     */
    void SetID(unsigned int id)
    {
        id_ = id;
    }

    /*
     * @brief         Set the format of texture.
     * @param format  The format of texture.
     */
    void SetFormat(unsigned int format)
    {
        format_ = format;
    }

    /*
     * @brief  Gets the width of TextureInfo.
     */
    int GetWidth() const
    {
        return width_;
    }

    /*
     * @brief  Gets the height of TextureInfo.
     */
    int GetHeight() const
    {
        return height_;
    }

    /*
     * @brief  Gets whether the texture has mip levels allocated.
     */
    bool GetIsMipMapped() const
    {
        return isMipMapped_;
    }

    /*
     * @brief   Gets the target type of TextureInfo.
     * @return  The target type of TextureInfo.
     */
    unsigned int GetTarget() const
    {
        return target_;
    }

    /*
     * @brief   Gets the Id of TextureInfo.
     * @return  The Id of TextureInfo.
     */
    unsigned int GetID() const
    {
        return id_;
    }

    /*
     * @brief   Gets the format of TextureInfo.
     * @return  The target format of TextureInfo.
     */
    unsigned int GetFormat() const
    {
        return format_;
    }

private:
    int width_ = 0;
    int height_ = 0;
    bool isMipMapped_ = false;
    unsigned int target_ = 0;
    unsigned int id_ = 0;
    unsigned int format_ = 0;
};

class BackendTexture {
public:
    BackendTexture() noexcept;
    BackendTexture(bool isValid) noexcept;
    virtual ~BackendTexture() {};

    bool IsValid() const;
    void SetTextureInfo(const TextureInfo& textureInfo);
    const TextureInfo& GetTextureInfo() const;

private:
    bool isValid_;
    TextureInfo textureInfo_;
};

class Image {
public:
    Image() noexcept = default;
    virtual ~Image() {};
        virtual int GetWidth()
    {
        const int imageWidth = 100;
        return imageWidth;
    }

    virtual int GetHeight()
    {
        const int imageHeight = 100;
        return imageHeight;
    }

    virtual uint32_t GetUniqueID() const
    {
        const uint32_t id = 0;
        return id;
    }

    virtual bool BuildFromBitmap(const Bitmap& bitmap) const
    {
        return true;
    }

    bool MakeFromEncoded(const std::shared_ptr<Data>& data)
    {
        return true;
    }
};
} // namespace Drawing
} // namespace Rosen
} // namespace OHOS
#endif
