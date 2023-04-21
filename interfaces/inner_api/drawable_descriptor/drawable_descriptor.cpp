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

#include "SkBlendMode.h"
#include "SkCanvas.h"
#include "SkImage.h"
#include "SkPaint.h"
#include "SkRect.h"
#include "cJSON.h"
#include "image_source.h"

namespace OHOS::Ace::Napi {
namespace {
const char DRAWABLEDESCRIPTOR_JSON_KEY_BACKGROUND[] = "background";
const char DRAWABLEDESCRIPTOR_JSON_KEY_FOREGROUND[] = "foreground";
} // namespace

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
    SkCanvas bitmapCanvas(*background);
    auto rect1 = SkRect::MakeWH(static_cast<float>(mask->width()), static_cast<float>(mask->height()));
    auto rect2 = SkRect::MakeXYWH(0, 0, static_cast<float>(background->width()),
        static_cast<float>(background->height()));
    paint.setBlendMode(SkBlendMode::kDstATop);
    bitmapCanvas.drawImageRect(SkImage::MakeFromBitmap(*mask), rect1, rect2, &paint);

    rect1 = SkRect::MakeWH(static_cast<float>(foreground->width()), static_cast<float>(foreground->height()));
    auto x = static_cast<float>((background->width() - foreground->width()) / 2);
    auto y = static_cast<float>((background->height() - foreground->height()) / 2);
    rect2 = SkRect::MakeXYWH(x, y, static_cast<float>(foreground->width()), static_cast<float>(foreground->height()));
    paint.setBlendMode(SkBlendMode::kSrcATop);
    bitmapCanvas.drawImageRect(SkImage::MakeFromBitmap(*foreground), rect1, rect2, &paint);
    SkBitmap result;
    result.allocPixels(background->info());
    bitmapCanvas.readPixels(result, 0, 0);

    // convert bitmap back to pixelMap
    Media::InitializationOptions opts;
    opts.alphaType = background_.value()->GetAlphaType();
    opts.pixelFormat = Media::PixelFormat::BGRA_8888;
    pixelMap_ = ImageConverter::BitmapToPixelMap(std::make_shared<SkBitmap>(result), opts);
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
