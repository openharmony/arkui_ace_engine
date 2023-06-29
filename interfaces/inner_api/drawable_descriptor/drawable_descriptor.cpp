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
#include <string>

#include "base/utils/string_utils.h"

#ifdef NEW_SKIA
#include "include/core/SkSamplingOptions.h"
#endif
#include "cJSON.h"
#include "image_source.h"
#include "include/core/SkImage.h"
#include "include/core/SkRect.h"

namespace OHOS::Ace::Napi {
namespace {
const char DRAWABLEDESCRIPTOR_JSON_KEY_BACKGROUND[] = "background";
const char DRAWABLEDESCRIPTOR_JSON_KEY_FOREGROUND[] = "foreground";
constexpr float SIDE = 192.0;
} // namespace

bool DrawableDescriptor::GetPixelMapFromBuffer()
{
    Media::SourceOptions opts;
    uint32_t errorCode = 0;
    std::unique_ptr<Media::ImageSource> imageSource =
        Media::ImageSource::CreateImageSource(mediaData_.get(), len_, opts, errorCode);
    if (errorCode != 0) {
        HILOG_ERROR("CreateImageSource from buffer failed");
        return false;
    }
    mediaData_.reset();
    Media::DecodeOptions decodeOpts;
    decodeOpts.desiredPixelFormat = Media::PixelFormat::BGRA_8888;
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
    }
    if (GetPixelMapFromBuffer()) {
        return pixelMap_.value();
    }
    HILOG_ERROR("Failed to GetPixelMap!");
    return nullptr;
}

std::unique_ptr<Media::ImageSource> LayeredDrawableDescriptor::CreateImageSource(const char* item, uint32_t& errorCode)
{
    std::string itemStr = item;
    std::string idStr = itemStr.substr(itemStr.find(':') + 1);
    if (!StringUtils::IsNumber(idStr)) {
        return nullptr;
    }

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
        HILOG_ERROR("Get background from json buffer failed");
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
    decodeOpts.desiredPixelFormat = Media::PixelFormat::BGRA_8888;
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
    decodeOpts.desiredPixelFormat = Media::PixelFormat::BGRA_8888;
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

void LayeredDrawableDescriptor::DrawOntoCanvas(
    const std::shared_ptr<SkBitmap>& bitMap, float width, float height, SkCanvas& canvas, const SkPaint& paint)
{
    auto x = static_cast<float>((bitMap->width() - static_cast<float>(width)) / 2);
    auto y = static_cast<float>((bitMap->height() - static_cast<float>(height)) / 2);
    auto rect1 = SkRect::MakeXYWH(x, y, static_cast<float>(width), static_cast<float>(width));
    auto rect2 = SkRect::MakeWH(static_cast<float>(width), static_cast<float>(width));
#ifndef NEW_SKIA
    canvas.drawImageRect(SkImage::MakeFromBitmap(*bitMap), rect1, rect2, &paint);
#else
    canvas.drawImageRect(
        SkImage::MakeFromBitmap(*bitMap), rect1, rect2, SkSamplingOptions(), &paint, SkCanvas::kFast_SrcRectConstraint);
#endif
}

bool LayeredDrawableDescriptor::CreatePixelMap()
{
    std::shared_ptr<SkBitmap> foreground;
    if (foreground_.has_value()) {
        foreground = ImageConverter::PixelMapToBitmap(foreground_.value());
    } else if (GetPixelMapFromJsonBuf(false)) {
        foreground = ImageConverter::PixelMapToBitmap(foreground_.value());
    } else {
        HILOG_INFO("Get pixelMap of foreground failed.");
        return false;
    }

    std::shared_ptr<SkBitmap> background;
    if (background_.has_value()) {
        background = ImageConverter::PixelMapToBitmap(background_.value());
    } else if (GetPixelMapFromJsonBuf(true)) {
        background = ImageConverter::PixelMapToBitmap(background_.value());
    } else {
        HILOG_ERROR("Get pixelMap of background failed.");
        return false;
    }

    std::shared_ptr<SkBitmap> mask;
    if (mask_.has_value()) {
        mask = ImageConverter::PixelMapToBitmap(mask_.value());
    } else if (GetDefaultMask()) {
        mask = ImageConverter::PixelMapToBitmap(mask_.value());
    } else {
        HILOG_ERROR("Get pixelMap of mask failed.");
        return false;
    }

    SkPaint paint;
    paint.setAntiAlias(true);
    auto colorType = ImageConverter::PixelFormatToSkColorType(background_.value()->GetPixelFormat());
    auto alphaType = ImageConverter::AlphaTypeToSkAlphaType(background_.value()->GetAlphaType());
    auto imageInfo = SkImageInfo::Make(SIDE, SIDE, colorType, alphaType);
    SkBitmap tempCache;
    tempCache.allocPixels(imageInfo);
    SkCanvas bitmapCanvas(tempCache);

    paint.setBlendMode(SkBlendMode::kSrc);
    DrawOntoCanvas(background, SIDE, SIDE, bitmapCanvas, paint);
    paint.setBlendMode(SkBlendMode::kDstATop);
    DrawOntoCanvas(mask, SIDE, SIDE, bitmapCanvas, paint);
    paint.setBlendMode(SkBlendMode::kSrcATop);
    DrawOntoCanvas(foreground, SIDE, SIDE, bitmapCanvas, paint);
    bitmapCanvas.readPixels(tempCache, 0, 0);

    // convert bitmap back to pixelMap
    Media::InitializationOptions opts;
    opts.alphaType = background_.value()->GetAlphaType();
    opts.pixelFormat = Media::PixelFormat::BGRA_8888;
    layeredPixelMap_ = ImageConverter::BitmapToPixelMap(std::make_shared<SkBitmap>(tempCache), opts);
    return true;
}

std::shared_ptr<Media::PixelMap> LayeredDrawableDescriptor::GetPixelMap()
{
    if (layeredPixelMap_.has_value()) {
        return layeredPixelMap_.value();
    }

    if (CreatePixelMap()) {
        return layeredPixelMap_.value();
    }

    HILOG_ERROR("Failed to GetPixelMap!");
    return nullptr;
}

std::string LayeredDrawableDescriptor::GetStaticMaskClipPath()
{
    const std::string name = "ohos_drawable_descriptor_path";
    std::string data;
    std::shared_ptr<Global::Resource::ResourceManager> ResMgr_(Global::Resource::CreateResourceManager());
    ResMgr_->GetStringByName(name.c_str(), data);
    return data;
}
} // namespace OHOS::Ace::Napi
