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

#ifndef IMAGE_INFO_H
#define IMAGE_INFO_H
#include "draw/color.h"
#include "utils/rect.h"
namespace OHOS {
namespace Rosen {
namespace Drawing {

enum class EncodedImageFormat {
    JPEG,
    PNG,
    WEBP,
    UNKNOWN,
};

class ImageInfo {
public:
    ImageInfo() = default;
    ~ImageInfo() = default;

    static ImageInfo MakeN32Premul(int32_t width, int32_t height)
    {
        return ImageInfo();
    }
    /**
     * @brief Gets the width value of ImageInfo.
     */
    int GetWidth() const
    {
        return width_;
    }

    /**
     * @brief Gets the height value of ImageInfo.
     */
    int GetHeight() const
    {
        return height_;
    }

    /**
     * @brief Gets the color type value of ImageInfo.
     */
    ColorType GetColorType() const
    {
        return colorType_;
    }

    /**
     * @brief Gets the alpha type value of ImageInfo.
     */
    AlphaType GetAlphaType() const
    {
        return alphaType_;
    }
    /**
     * @brief Returns number of bytes per pixel.
     */
    int32_t GetBytesPerPixel() const
    {
        // returns the number of bytes per pixel: 1byte, 2bytes, 4bytes
        switch (colorType_) {
            case COLORTYPE_ALPHA_8:
                return 1;  // 1 byte
            case COLORTYPE_RGB_565:
            case COLORTYPE_ARGB_4444:
                return 2;  // 2 bytes
            case COLORTYPE_RGBA_8888:
            case COLORTYPE_BGRA_8888:
            case COLORTYPE_RGB_888X:
            case COLORTYPE_N32:
                return 4;  // 4 bytes
            default:
                return 0;
        }
    }

    /**
     * @brief Sets the width value of ImageInfo.
     */
    void SetWidth(int width)
    {
        width_ = width;
    }

    /**
     * @brief Sets the height value of ImageInfo.
     */
    void SetHeight(int height)
    {
        height_ = height;
    }

    /**
     * @brief Sets the color type value of ImageInfo.
     */
    void SetColorType(ColorType colorType)
    {
        colorType_ = colorType;
    }

    /**
     * @brief Sets the alpha type value of ImageInfo.
     */
    void SetAlphaType(AlphaType alphaType)
    {
        alphaType_ = alphaType;
    }

    /**
     * @brief Gets the bounds of ImageInfo.
     */
    RectI GetBound() const
    {
        return RectI(0, 0, width_, height_);
    }

private:
    int width_ = 0;
    int height_ = 0;
    ColorType colorType_ = COLORTYPE_UNKNOWN;
    AlphaType alphaType_ = ALPHATYPE_UNKNOWN;
};
} // namespace Drawing
} // namespace Rosen
} // namespace OHOS
#endif // IMAGE_INFO_H
