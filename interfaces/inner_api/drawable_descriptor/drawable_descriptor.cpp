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

#include "drawable_descriptor.h"

#include <cstddef>
#include <memory>

#include "cJSON.h"

#include "foundation/graphic/graphic_2d/rosen/modules/2d_graphics/include/draw/blend_mode.h"
#include "foundation/graphic/graphic_2d/rosen/modules/2d_graphics/include/draw/brush.h"
#include "foundation/graphic/graphic_2d/rosen/modules/2d_graphics/include/draw/canvas.h"
#include "foundation/graphic/graphic_2d/rosen/modules/2d_graphics/include/image/image.h"
#include "foundation/graphic/graphic_2d/rosen/modules/2d_graphics/include/utils/rect.h"
#include "foundation/graphic/graphic_2d/rosen/modules/2d_graphics/include/utils/sampling_options.h"
#include "platform/image_native/image_type.h"
namespace OHOS::Ace::Napi {
namespace {
const char DRAWABLEDESCRIPTOR_JSON_KEY_BACKGROUND[] = "background";
const char DRAWABLEDESCRIPTOR_JSON_KEY_FOREGROUND[] = "foreground";
}

bool DrawableDescriptor::GetPixelMapFromBuffer()
{
    Media::SourceOptions opts;
    uint32_t errorCode = 0;
    std::unique_ptr<Media::ImageSource> imageSource =
        Media::ImageSource::CreateImageSource(jsonBuf_.get(), len_, opts, errorCode);
    if (errorCode != 0) {
        HILOG_ERROR("CreateImageSource from buffer failed");
        return false;
    }
    Media::DecodeOptions decodeOpts;
    auto pixelMapPtr = imageSource->CreatePixelMap(decodeOpts, errorCode);
    pixelMap_ = std::shared_ptr<Media::PixelMap>(pixelMapPtr.release());
    if (errorCode != 0 || !pixelMap_) {
        HILOG_ERROR("Get PixelMap from buffer failed");
        return false;
    }
    return true;
}

std::shared_ptr<Media::PixelMap> DrawableDescriptor::GetPixelMap()
{
    if (pixelMap_.has_value()) {
        return pixelMap_.value();
    } else {
        if (GetPixelMapFromBuffer()) {
            return pixelMap_.value();
        } else {
            HILOG_ERROR("Failed to GetPixelMap");
            return nullptr;
        }
    }
}

std::unique_ptr<Media::ImageSource> LayeredDrawableDescriptor::CreateImageSource(const char* item, uint32_t& errorCode)
{
    std::string itemStr = item;
    std::string idStr = itemStr.substr(itemStr.find(':') + 1);
    size_t len = 0;
    std::unique_ptr<uint8_t[]> data;
    
    auto state = resourceMgr_->GetMediaDataById(static_cast<uint32_t>(std::stoul(idStr)), len, data);
    if (state != Global::Resource::SUCCESS) {
        HILOG_ERROR("GetMediaDataById failed");
        return nullptr;
    }
    
    Media::SourceOptions opts;
    return Media::ImageSource::CreateImageSource(data.get(), len, opts, errorCode);
}

bool LayeredDrawableDescriptor::GetPixelMapFromJsonBuf(bool isBackground)
{
    cJSON* roots = cJSON_ParseWithLength(reinterpret_cast<const char*>(jsonBuf_.get()), len_);

    if (roots == nullptr) {
        return false;
    }

    uint32_t errorCode = 0;
    cJSON* item = nullptr;
    if (isBackground) {
        item = cJSON_GetObjectItem(roots->child, DRAWABLEDESCRIPTOR_JSON_KEY_BACKGROUND);
    } else {
        item = cJSON_GetObjectItem(roots->child, DRAWABLEDESCRIPTOR_JSON_KEY_FOREGROUND);
    }
    if (item == nullptr) {
        HILOG_ERROR("GetObjectItem from json buffer failed");
        return false;
    }

    if (cJSON_IsString(item)) {
        std::unique_ptr<Media::ImageSource> imageSource =
            LayeredDrawableDescriptor::CreateImageSource(item->valuestring, errorCode);
        if (errorCode != 0) {
            HILOG_ERROR("CreateImageSource from json buffer failed");
            return false;
        }
        Media::DecodeOptions decodeOpts;
        decodeOpts.desiredPixelFormat = Media::PixelFormat::BGRA_8888;
        auto pixelMapPtr = imageSource->CreatePixelMap(decodeOpts, errorCode);
        if (errorCode != 0) {
            HILOG_ERROR("Get PixelMap from json buffer failed");
            return false;
        }

        if (isBackground) {
            background_ = std::shared_ptr<Media::PixelMap>(pixelMapPtr.release());
        } else {
            foreground_ = std::shared_ptr<Media::PixelMap>(pixelMapPtr.release());
        }
    } else {
        HILOG_ERROR("GetPixelMapFromJsonBuf from json buffer failed");
        return false;
    }
    return true;
}

bool LayeredDrawableDescriptor::GetDefaultMask()
{
    const std::string name = "ohos_icon_mask";
    size_t len = 0;
    std::unique_ptr<uint8_t[]> data;
    resourceMgr_->GetMediaDataByName(name.c_str(), len, data);
    Media::SourceOptions opts;
    uint32_t errorCode = 0;
    std::unique_ptr<Media::ImageSource> imageSource =
        Media::ImageSource::CreateImageSource(data.get(), len, opts, errorCode);
    Media::DecodeOptions decodeOpts;
    auto pixelMapPtr = imageSource->CreatePixelMap(decodeOpts, errorCode);
    mask_ = std::shared_ptr<Media::PixelMap>(pixelMapPtr.release());
    if (errorCode != 0 || !mask_) {
        HILOG_ERROR("Get mask failed");
        return false;
    }
    return true;
}

bool LayeredDrawableDescriptor::GetMaskByName(const std::string& name)
{
    size_t len = 0;
    std::unique_ptr<uint8_t[]> data;
    resourceMgr_->GetMediaDataByName(name.c_str(), len, data);
    Media::SourceOptions opts;
    uint32_t errorCode = 0;
    std::unique_ptr<Media::ImageSource> imageSource =
        Media::ImageSource::CreateImageSource(data.get(), len, opts, errorCode);
    Media::DecodeOptions decodeOpts;
    auto pixelMapPtr = imageSource->CreatePixelMap(decodeOpts, errorCode);
    mask_ = std::shared_ptr<Media::PixelMap>(pixelMapPtr.release());
    if (errorCode != 0 || !mask_) {
        HILOG_ERROR("Get mask failed");
        return false;
    }
    return true;
}

std::unique_ptr<DrawableDescriptor> LayeredDrawableDescriptor::GetForeground()
{
    if (foreground_.has_value()) {
        return std::make_unique<DrawableDescriptor>(foreground_.value());
    }

    if (GetPixelMapFromJsonBuf(false)) {
        return std::make_unique<DrawableDescriptor>(foreground_.value());
    }

    HILOG_ERROR("GetForeground failed");
    return nullptr;
}

std::unique_ptr<DrawableDescriptor> LayeredDrawableDescriptor::GetBackground()
{
    if (background_.has_value()) {
        return std::make_unique<DrawableDescriptor>(background_.value());
    }

    if (GetPixelMapFromJsonBuf(true)) {
        return std::make_unique<DrawableDescriptor>(background_.value());
    }

    HILOG_ERROR("GetForeground failed");
    return nullptr;
}

std::unique_ptr<DrawableDescriptor> LayeredDrawableDescriptor::GetMask()
{
    if (mask_.has_value()) {
        return std::make_unique<DrawableDescriptor>(mask_.value());
    }

    if (GetDefaultMask()) {
        return std::make_unique<DrawableDescriptor>(mask_.value());
    }

    HILOG_ERROR("GetMask failed");
    return nullptr;
}

Rosen::Drawing::ColorType LayeredDrawableDescriptor::PixelFormatToColorType(Media::PixelFormat pixelFormat)
{
    switch (pixelFormat) {
        case Media::PixelFormat::RGB_565:
            return Rosen::Drawing::ColorType::COLORTYPE_RGB_565;
        case Media::PixelFormat::RGBA_8888:
            return Rosen::Drawing::ColorType::COLORTYPE_RGBA_8888;
        case Media::PixelFormat::BGRA_8888:
            return Rosen::Drawing::ColorType::COLORTYPE_BGRA_8888;
        case Media::PixelFormat::ALPHA_8:
            return Rosen::Drawing::ColorType::COLORTYPE_ALPHA_8;
        case Media::PixelFormat::ARGB_8888:
        case Media::PixelFormat::RGB_888:
        case Media::PixelFormat::RGBA_F16:
        case Media::PixelFormat::NV21:
        case Media::PixelFormat::NV12:
        case Media::PixelFormat::CMYK:
        case Media::PixelFormat::UNKNOWN:
        default:
            return Rosen::Drawing::ColorType::COLORTYPE_UNKNOWN;
    }
}

Rosen::Drawing::AlphaType LayeredDrawableDescriptor::AlphaTypeToRSAlphaType(Media::AlphaType alphaType)
{
    switch (alphaType) {
        case Media::AlphaType::IMAGE_ALPHA_TYPE_OPAQUE:
            return Rosen::Drawing::AlphaType::ALPHATYPE_OPAQUE;
        case Media::AlphaType::IMAGE_ALPHA_TYPE_PREMUL:
            return Rosen::Drawing::AlphaType::ALPHATYPE_PREMUL;
        case Media::AlphaType::IMAGE_ALPHA_TYPE_UNPREMUL:
            return Rosen::Drawing::AlphaType::ALPHATYPE_UNPREMUL;
        case Media::AlphaType::IMAGE_ALPHA_TYPE_UNKNOWN:
        default:
            return Rosen::Drawing::AlphaType::ALPHATYPE_UNKNOWN;
    }
}

std::shared_ptr<Rosen::Drawing::Bitmap> LayeredDrawableDescriptor::PixelMapToBitMap(
    const std::shared_ptr<Media::PixelMap>& pixelMap)
{
    Rosen::Drawing::Bitmap bitmap;
    Rosen::Drawing::ColorType colorType = LayeredDrawableDescriptor::PixelFormatToColorType(pixelMap->GetPixelFormat());
    Rosen::Drawing::AlphaType rAlphaType = LayeredDrawableDescriptor::AlphaTypeToRSAlphaType(pixelMap->GetAlphaType());
    Rosen::Drawing::BitmapFormat format { colorType, rAlphaType };
    auto data = pixelMap->GetPixels();
    bitmap.Build(pixelMap->GetWidth(), pixelMap->GetHeight(), format);
    bitmap.SetPixels(const_cast<uint8_t*>(data));
    return std::make_shared<Rosen::Drawing::Bitmap>(bitmap);
}

std::shared_ptr<Media::PixelMap> LayeredDrawableDescriptor::BitMapToPixelMap(
    const std::shared_ptr<Rosen::Drawing::Bitmap>& bitMap, Media::InitializationOptions& opts)
{
    auto data = bitMap->GetPixels();
    opts.size.width = bitMap->GetWidth();
    opts.size.height = bitMap->GetHeight();
    pixelMap_ = Media::PixelMap::Create(reinterpret_cast<uint32_t*>(data), opts.size.width * opts.size.height, opts);
    return pixelMap_.value();
}

bool LayeredDrawableDescriptor::CreatePixelMap()
{
    // get pixelMap
    std::shared_ptr<Rosen::Drawing::Bitmap> foreground;
    bool isBackground = false;
    if (foreground_.has_value()) {
        foreground = PixelMapToBitMap(foreground_.value());
    } else if (GetPixelMapFromJsonBuf(isBackground)) {
        foreground = PixelMapToBitMap(foreground_.value());
    } else {
        HILOG_ERROR("Get piexelmap of foreground faied.");
        return false;
    }
    
    std::shared_ptr<Rosen::Drawing::Bitmap> background;
    isBackground = true;
    if (background_.has_value()) {
        background = PixelMapToBitMap(background_.value());
    } else if (GetPixelMapFromJsonBuf(isBackground)) {
        background = PixelMapToBitMap(background_.value());
    } else {
        HILOG_ERROR("Get piexelmap of background faied.");
        return false;
    }

    std::shared_ptr<Rosen::Drawing::Bitmap> mask;
    if (mask_.has_value()) {
        mask = PixelMapToBitMap(mask_.value());
    } else if (GetDefaultMask()) {
        mask = PixelMapToBitMap(mask_.value());
    } else {
        HILOG_ERROR("Get piexelmap of mask faied.");
        return false;
    }

    Rosen::Drawing::Canvas canvas;
    canvas.Bind(static_cast<const OHOS::Rosen::Drawing::Bitmap>(*(background.get())));
    Rosen::Drawing::Brush brush;
    brush.SetAntiAlias(true);
    canvas.AttachBrush(brush);
    Rosen::Drawing::Image image;
    image.BuildFromBitmap(static_cast<const OHOS::Rosen::Drawing::Bitmap>(*(foreground.get())));
    Rosen::Drawing::RectF dst = Rosen::Drawing::RectF(
        0.0f, static_cast<float>(foreground->GetWidth()), 0.0f, static_cast<float>(foreground->GetHeight()));
    Rosen::Drawing::SamplingOptions ops;
    canvas.DrawImageRect(image, dst, ops);

    brush.SetBlendMode(Rosen::Drawing::BlendMode::DST_IN);
    canvas.AttachBrush(brush);
    image.BuildFromBitmap(static_cast<const OHOS::Rosen::Drawing::Bitmap>(*(mask.get())));
    canvas.DrawImageRect(image, dst, ops);

    // convert bitMap back to pixelMap
    Media::InitializationOptions opts;
    opts.alphaType = background_.value()->GetAlphaType();
    opts.pixelFormat = background_.value()->GetPixelFormat();
    pixelMap_ = BitMapToPixelMap(background, opts);
    return true;
}

std::shared_ptr<Media::PixelMap> LayeredDrawableDescriptor::GetPixelMap()
{
    if (pixelMap_.has_value()) {
        return pixelMap_.value();
    }

    if (CreatePixelMap()) {
        return pixelMap_.value();
    }

    HILOG_ERROR("Failed to GetPixelMap!");
    return nullptr;
}
} // namespace OHOS::Ace::Napi
