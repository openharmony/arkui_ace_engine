/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#if defined(ANDROID_PLATFORM) || defined(IOS_PLATFORM)
#include "application_context.h"
#endif
#include <cstdlib>
#include <cerrno>
#include <limits>

#include "drawable_descriptor.h"
#include "cJSON.h"
#ifndef PREVIEW
#include "image_source.h"
#endif
#include "include/core/SkImage.h"
#include "include/core/SkRect.h"
#ifdef PREVIEW
#ifdef WINDOWS_PLATFORM
#include <direct.h>
#include <windows.h>
#elif defined(MAC_PLATFORM)
#include <mach-o/dyld.h>
#else
#include <unistd.h>
#endif
#endif

namespace OHOS::Ace::Napi {
namespace {
#ifndef PREVIEW
const char DRAWABLEDESCRIPTOR_JSON_KEY_BACKGROUND[] = "background";
const char DRAWABLEDESCRIPTOR_JSON_KEY_FOREGROUND[] = "foreground";
#endif
#ifdef USE_ROSEN_DRAWING
constexpr float BADGED_SIDE_X = 21.0f;
constexpr float BADGED_SIDE_Y = 7.0f;
constexpr float SIDE = 192.0f;
constexpr float NOT_ADAPTIVE_SIZE = 288.0f;
constexpr float HALF = 0.5f;

inline bool NearEqual(const double left, const double right, const double epsilon)
{
    return (std::abs(left - right) <= epsilon);
}

inline bool NearEqual(const double left, const double right)
{
    constexpr double epsilon = 0.001f;
    return NearEqual(left, right, epsilon);
}

#endif
const int DEFAULT_DURATION = 1000;
const std::string DEFAULT_MASK = "ohos_icon_mask";
constexpr int DECIMAL_BASE = 10;

// define for get resource path in preview scenes
const static char PREVIEW_LOAD_RESOURCE_ID[] = "ohos_drawable_descriptor_path";
#ifdef PREVIEW
#ifdef WINDOWS_PLATFORM
constexpr static char PREVIEW_LOAD_RESOURCE_PATH[] = "\\resources\\resources.index";
#else
constexpr static char PREVIEW_LOAD_RESOURCE_PATH[] = "/resources/resources.index";
#endif

#ifdef LINUX_PLATFORM
const static size_t MAX_PATH_LEN = 255;
#endif
#endif
inline bool IsNumber(const std::string& value)
{
    if (value.empty()) {
        return false;
    }
    return std::all_of(value.begin(), value.end(), [](char i) { return isdigit(i); });
}

bool ConvertStringToUInt32(const std::string& idStr, uint32_t& result)
{
    char* endPtr = nullptr;
    errno = 0;
    result = std::strtoul(idStr.c_str(), &endPtr, DECIMAL_BASE);
    if (errno == ERANGE || result > std::numeric_limits<uint32_t>::max()) {
        HILOGE("Out of range: string value is too large for uint32_t");
        return false;
    }
    if (endPtr == idStr.c_str() || *endPtr != '\0') {
        HILOGE("Invalid argument: unable to convert string to uint32_t");
        return false;
    }

    return true;
}
} // namespace

DrawableItem LayeredDrawableDescriptor::PreGetDrawableItem(
    const std::shared_ptr<Global::Resource::ResourceManager>& resourceMgr, const char* item)
{
    DrawableItem resItem;
    std::string itemStr = item;
    std::string idStr;

    size_t pos = itemStr.find(':');
    if (pos != std::string::npos) {
        idStr = itemStr.substr(pos + 1);
    } else {
        return resItem;
    }
    if (!IsNumber(idStr)) {
        return resItem;
    }

    std::tuple<std::string, size_t, std::string> info;
    uint32_t resourceId = 0;
    if (ConvertStringToUInt32(idStr, resourceId)) {
        resItem.state_ = resourceMgr->GetDrawableInfoById(resourceId, info, resItem.data_, iconType_, density_);
    }
    resItem.len_ = std::get<1>(info);
    return resItem;
}

bool LayeredDrawableDescriptor::PreGetPixelMapFromJsonBuf(
    const std::shared_ptr<Global::Resource::ResourceManager>& resourceMgr, bool isBackground)
{
#ifndef PREVIEW
    cJSON* roots = cJSON_ParseWithLength(reinterpret_cast<const char*>(jsonBuf_.get()), len_);

    if (roots == nullptr) {
        return false;
    }

    cJSON* item = nullptr;
    if (isBackground) {
        item = cJSON_GetObjectItem(roots->child, DRAWABLEDESCRIPTOR_JSON_KEY_BACKGROUND);
    } else {
        item = cJSON_GetObjectItem(roots->child, DRAWABLEDESCRIPTOR_JSON_KEY_FOREGROUND);
    }
    if (item == nullptr) {
        cJSON_Delete(roots);
        HILOGE("GetObjectItem from json buffer failed");
        return false;
    }
    if (cJSON_IsString(item)) {
        DrawableItem& drawableiItem = isBackground ? backgroundItem_ : foregroundItem_;
        drawableiItem = PreGetDrawableItem(resourceMgr, item->valuestring);
    } else {
        cJSON_Delete(roots);
        return false;
    }
    cJSON_Delete(roots);
    return true;
#else
    return false;
#endif
}

void LayeredDrawableDescriptor::InitialResource(const std::shared_ptr<Global::Resource::ResourceManager>& resourceMgr)
{
    if (!resourceMgr) {
        HILOGE("Global resource manager is null!");
        return;
    }
    InitialMask(resourceMgr);
    // preprocess get background and foreground
    if (!PreGetPixelMapFromJsonBuf(resourceMgr, true)) {
        HILOGD("Create background Item imageSource from json buffer failed");
    }
    if (!PreGetPixelMapFromJsonBuf(resourceMgr, false)) {
        HILOGD("Create foreground Item imageSource from json buffer failed");
    }
}

void LayeredDrawableDescriptor::InitialMask(const std::shared_ptr<Global::Resource::ResourceManager>& resourceMgr)
{
    resourceMgr->GetMediaDataByName(DEFAULT_MASK.c_str(), defaultMaskDataLength_, defaultMaskData_);
}

bool DrawableDescriptor::GetPixelMapFromBuffer()
{
    Media::SourceOptions opts;
    uint32_t errorCode = 0;
    std::unique_ptr<Media::ImageSource> imageSource =
        Media::ImageSource::CreateImageSource(mediaData_.get(), len_, opts, errorCode);
    if (errorCode != 0) {
        HILOGE("CreateImageSource from buffer failed");
        return false;
    }
    mediaData_.reset();
    Media::DecodeOptions decodeOpts;
    decodeOpts.desiredPixelFormat = Media::PixelFormat::BGRA_8888;
    if (imageSource) {
        auto pixelMapPtr = imageSource->CreatePixelMap(decodeOpts, errorCode);
        pixelMap_ = std::shared_ptr<Media::PixelMap>(pixelMapPtr.release());
    }
    if (errorCode != 0 || !pixelMap_) {
        HILOGE("Get PixelMap from buffer failed");
        return false;
    }
    return true;
}

std::shared_ptr<Media::PixelMap> DrawableDescriptor::GetPixelMap()
{
    if (pixelMap_.value_or(nullptr)) {
        return pixelMap_.value();
    }
    if (GetPixelMapFromBuffer()) {
        return pixelMap_.value();
    }
    HILOGE("Failed to GetPixelMap!");
    return nullptr;
}

DrawableDescriptor::DrawableType DrawableDescriptor::GetDrawableType()
{
    return DrawableType::BASE;
}

std::unique_ptr<Media::ImageSource> LayeredDrawableDescriptor::CreateImageSource(
    DrawableItem& drawableItem, uint32_t& errorCode)
{
    if (drawableItem.state_ != Global::Resource::SUCCESS) {
        HILOGE("GetDrawableInfoById failed");
        return nullptr;
    }

    Media::SourceOptions opts;
    return Media::ImageSource::CreateImageSource(drawableItem.data_.get(), drawableItem.len_, opts, errorCode);
}

bool LayeredDrawableDescriptor::GetPixelMapFromJsonBuf(bool isBackground)
{
#ifndef PREVIEW
    if ((isBackground && background_.value_or(nullptr)) || (!isBackground && foreground_.value_or(nullptr))) {
        return true;
    }
    if ((isBackground && backgroundItem_.state_ == Global::Resource::SUCCESS) ||
        (!isBackground && foregroundItem_.state_ == Global::Resource::SUCCESS)) {
        uint32_t errorCode = 0;
        std::unique_ptr<Media::ImageSource> imageSource =
            LayeredDrawableDescriptor::CreateImageSource(isBackground ? backgroundItem_ : foregroundItem_, errorCode);
        if (errorCode != 0) {
            HILOGE("CreateImageSource from json buffer failed");
            return false;
        }
        Media::DecodeOptions decodeOpts;
        decodeOpts.desiredPixelFormat = Media::PixelFormat::BGRA_8888;
        if (imageSource) {
            auto pixelMapPtr = imageSource->CreatePixelMap(decodeOpts, errorCode);
            if (errorCode != 0) {
                HILOGE("Get PixelMap from json buffer failed");
                return false;
            }

            if (isBackground) {
                background_ = std::shared_ptr<Media::PixelMap>(pixelMapPtr.release());
            } else {
                foreground_ = std::shared_ptr<Media::PixelMap>(pixelMapPtr.release());
            }
        }
    } else {
        HILOGE("Get background from json buffer failed");
        return false;
    }
    if (isBackground) {
        backgroundItem_.data_.reset();
    } else {
        foregroundItem_.data_.reset();
    }
    return true;
#else
    return false;
#endif
}

bool LayeredDrawableDescriptor::GetDefaultMask()
{
    Media::SourceOptions opts;
    uint32_t errorCode = 0;
    std::unique_ptr<Media::ImageSource> imageSource =
        Media::ImageSource::CreateImageSource(
            defaultMaskData_.get(), defaultMaskDataLength_, opts, errorCode);
    Media::DecodeOptions decodeOpts;
    decodeOpts.desiredPixelFormat = Media::PixelFormat::BGRA_8888;
    if (imageSource) {
        auto pixelMapPtr = imageSource->CreatePixelMap(decodeOpts, errorCode);
        mask_ = std::shared_ptr<Media::PixelMap>(pixelMapPtr.release());
    }
    if (errorCode != 0 || !mask_) {
        HILOGE("Get mask failed");
        return false;
    }
    return true;
}

void LayeredDrawableDescriptor::InitLayeredParam(std::pair<std::unique_ptr<uint8_t[]>, size_t> &foregroundInfo,
    std::pair<std::unique_ptr<uint8_t[]>, size_t> &backgroundInfo)
{
    Media::SourceOptions opts;
    uint32_t errorCode = 0;
    auto foreground = Media::ImageSource::CreateImageSource(foregroundInfo.first.get(), foregroundInfo.second, opts,
        errorCode);
    if (errorCode == 0 && foreground) {
        Media::DecodeOptions decodeOpts;
        decodeOpts.desiredPixelFormat = Media::PixelFormat::BGRA_8888;
        auto pixelMapPtr = foreground->CreatePixelMap(decodeOpts, errorCode);
        foreground_ = std::shared_ptr<Media::PixelMap>(pixelMapPtr.release());
    }
    auto background = Media::ImageSource::CreateImageSource(backgroundInfo.first.get(), backgroundInfo.second, opts,
        errorCode);
    if (errorCode == 0 && background) {
        Media::DecodeOptions decodeOpts;
        decodeOpts.desiredPixelFormat = Media::PixelFormat::BGRA_8888;
        auto pixelMapPtr = background->CreatePixelMap(decodeOpts, errorCode);
        background_ = std::shared_ptr<Media::PixelMap>(pixelMapPtr.release());
    }
}

bool LayeredDrawableDescriptor::GetMaskByPath()
{
    if (maskPath_.empty()) {
        HILOGD("maskPath is null");
        return false;
    }
    Media::SourceOptions opts;
    uint32_t errorCode = 0;
    std::unique_ptr<Media::ImageSource> imageSource =
        Media::ImageSource::CreateImageSource(maskPath_, opts, errorCode);
    Media::DecodeOptions decodeOpts;
    decodeOpts.desiredPixelFormat = Media::PixelFormat::BGRA_8888;
    if (imageSource) {
        auto pixelMapPtr = imageSource->CreatePixelMap(decodeOpts, errorCode);
        mask_ = std::shared_ptr<Media::PixelMap>(pixelMapPtr.release());
    }
    if (errorCode != 0 || !mask_) {
        HILOGE("Get mask failed");
        return false;
    }
    return true;
}

bool LayeredDrawableDescriptor::GetMaskByName(
    std::shared_ptr<Global::Resource::ResourceManager>& resourceMgr, const std::string& name)
{
    size_t len = 0;
    std::unique_ptr<uint8_t[]> data;
    resourceMgr->GetMediaDataByName(name.c_str(), len, data);
    Media::SourceOptions opts;
    uint32_t errorCode = 0;
    std::unique_ptr<Media::ImageSource> imageSource =
        Media::ImageSource::CreateImageSource(data.get(), len, opts, errorCode);
    Media::DecodeOptions decodeOpts;
    decodeOpts.desiredPixelFormat = Media::PixelFormat::BGRA_8888;
    if (imageSource) {
        auto pixelMapPtr = imageSource->CreatePixelMap(decodeOpts, errorCode);
        mask_ = std::shared_ptr<Media::PixelMap>(pixelMapPtr.release());
    }
    if (errorCode != 0 || !mask_) {
        HILOGE("Get mask failed");
        return false;
    }
    return true;
}

std::unique_ptr<DrawableDescriptor> LayeredDrawableDescriptor::GetForeground()
{
    if (foreground_.value_or(nullptr)) {
        return std::make_unique<DrawableDescriptor>(foreground_.value());
    }

    if (GetPixelMapFromJsonBuf(false)) {
        return std::make_unique<DrawableDescriptor>(foreground_.value());
    }

    HILOGE("GetForeground failed");
    return nullptr;
}

std::unique_ptr<DrawableDescriptor> LayeredDrawableDescriptor::GetBackground()
{
    if (background_.value_or(nullptr)) {
        return std::make_unique<DrawableDescriptor>(background_.value());
    }

    if (GetPixelMapFromJsonBuf(true)) {
        return std::make_unique<DrawableDescriptor>(background_.value());
    }
    HILOGE("GetBackground failed");
    return nullptr;
}

std::unique_ptr<DrawableDescriptor> LayeredDrawableDescriptor::GetMask()
{
    if (mask_.value_or(nullptr)) {
        return std::make_unique<DrawableDescriptor>(mask_.value());
    }

    if (GetMaskByPath()) {
        return std::make_unique<DrawableDescriptor>(mask_.value());
    }

    if (GetDefaultMask()) {
        return std::make_unique<DrawableDescriptor>(mask_.value());
    }

    HILOGE("GetMask failed");
    return nullptr;
}

#ifndef USE_ROSEN_DRAWING
void LayeredDrawableDescriptor::DrawOntoCanvas(
    const std::shared_ptr<SkBitmap>& bitMap, float width, float height, SkCanvas& canvas, const SkPaint& paint)
{
    auto x = static_cast<float>((bitMap->width() - static_cast<float>(width)) / 2);
    auto y = static_cast<float>((bitMap->height() - static_cast<float>(height)) / 2);
    auto rect1 = SkRect::MakeXYWH(x, y, static_cast<float>(width), static_cast<float>(width));
    auto rect2 = SkRect::MakeWH(static_cast<float>(width), static_cast<float>(width));

    canvas.drawImageRect(
        SkImage::MakeFromBitmap(*bitMap), rect1, rect2, SkSamplingOptions(), &paint, SkCanvas::kFast_SrcRectConstraint);
}
#else
void LayeredDrawableDescriptor::DrawOntoCanvas(
    const std::shared_ptr<Rosen::Drawing::Bitmap>& bitMap, float width, float height, Rosen::Drawing::Canvas& canvas)
{
    auto x = static_cast<float>((bitMap->GetWidth() - static_cast<float>(width)) / 2);
    auto y = static_cast<float>((bitMap->GetHeight() - static_cast<float>(height)) / 2);
    Rosen::Drawing::Rect srcRect(x, y, static_cast<float>(width) + x, static_cast<float>(width) + y);
    Rosen::Drawing::Rect dstRect(0, 0, static_cast<float>(width), static_cast<float>(width));
    Rosen::Drawing::Image image;
    image.BuildFromBitmap(*bitMap);
    canvas.DrawImageRect(image, srcRect, dstRect, Rosen::Drawing::SamplingOptions(),
        Rosen::Drawing::SrcRectConstraint::FAST_SRC_RECT_CONSTRAINT);
}
bool LayeredDrawableDescriptor::GetLayeredIconParm(std::shared_ptr<Rosen::Drawing::Bitmap>& foreground,
    std::shared_ptr<Rosen::Drawing::Bitmap>& background, std::shared_ptr<Rosen::Drawing::Bitmap>& mask)
{
    if (foreground_.value_or(nullptr) || GetPixelMapFromJsonBuf(false)) {
        foreground = ImageConverter::PixelMapToBitmap(foreground_.value());
    } else if (!customized_) {
        HILOGI("Get pixelMap of foreground failed.");
        return false;
    }
    if (background_.value_or(nullptr) || GetPixelMapFromJsonBuf(true)) {
        background = ImageConverter::PixelMapToBitmap(background_.value());
    } else if (!customized_) {
        HILOGE("Get pixelMap of background failed.");
        return false;
    }
    if (mask_.value_or(nullptr) || GetMaskByPath() || GetDefaultMask()) {
        mask = ImageConverter::PixelMapToBitmap(mask_.value());
    } else if (!customized_) {
        HILOGE("Get pixelMap of mask failed.");
        return false;
    }
    return true;
}

void LayeredDrawableDescriptor::TransformToPixelMap(
    const Rosen::Drawing::Bitmap& bitmap, const Rosen::Drawing::ImageInfo& imageInfo)
{
    Media::InitializationOptions opts;
    if (background_.value_or(nullptr)) {
        opts.alphaType = background_.value()->GetAlphaType();
    } else {
        opts.alphaType = Media::AlphaType::IMAGE_ALPHA_TYPE_PREMUL;
    }
    opts.pixelFormat = Media::PixelFormat::BGRA_8888;
    layeredPixelMap_ = ImageConverter::BitmapToPixelMap(std::make_shared<Rosen::Drawing::Bitmap>(bitmap), opts);
}

Rosen::Drawing::ImageInfo LayeredDrawableDescriptor::CreateRSImageInfo(
    OptionalPixelMap pixelmap, int32_t width, int32_t height)
{
    Rosen::Drawing::ColorType colorType =
        pixelmap.value_or(nullptr)
            ? colorType = ImageConverter::PixelFormatToColorType(pixelmap.value()->GetPixelFormat())
            : colorType = ImageConverter::PixelFormatToColorType(Media::PixelFormat::RGBA_8888);
    Rosen::Drawing::AlphaType alphaType =
        pixelmap.value_or(nullptr)
            ? alphaType = ImageConverter::AlphaTypeToAlphaType(pixelmap.value()->GetAlphaType())
            : alphaType = ImageConverter::AlphaTypeToAlphaType(Media::AlphaType::IMAGE_ALPHA_TYPE_PREMUL);
    return Rosen::Drawing::ImageInfo(width, height, colorType, alphaType);
}

bool LayeredDrawableDescriptor::CompositeIconAdaptive(std::shared_ptr<Rosen::Drawing::Bitmap>& foreground,
    std::shared_ptr<Rosen::Drawing::Bitmap>& background, std::shared_ptr<Rosen::Drawing::Bitmap>& mask)
{
    if (!background) {
        HILOGW("The background is null when adaptive composite icons are used.");
        return false;
    }
    Rosen::Drawing::Brush brush;
    brush.SetAntiAlias(true);
    Rosen::Drawing::ImageInfo imageInfo =
        CreateRSImageInfo(background_, background->GetWidth(), background->GetHeight());
    Rosen::Drawing::Bitmap tempCache;
    tempCache.Build(imageInfo);
    Rosen::Drawing::Canvas bitmapCanvas;
    bitmapCanvas.Bind(tempCache);

    if (background) {
        brush.SetBlendMode(Rosen::Drawing::BlendMode::SRC);
        bitmapCanvas.AttachBrush(brush);
        DrawOntoCanvas(background, background->GetWidth(), background->GetHeight(), bitmapCanvas);
        bitmapCanvas.DetachBrush();
    }

    Rosen::Drawing::Rect dstRect(
        0.0, 0.0, static_cast<float>(background->GetWidth()), static_cast<float>(background->GetHeight()));
    Rosen::Drawing::Image image;
    if (mask) {
        Rosen::Drawing::Rect srcRect(
            0.0, 0.0, static_cast<float>(mask->GetWidth()), static_cast<float>(mask->GetHeight()));
        image.BuildFromBitmap(*mask);
        brush.SetBlendMode(Rosen::Drawing::BlendMode::DST_IN);
        bitmapCanvas.AttachBrush(brush);
        bitmapCanvas.DrawImageRect(image, srcRect, dstRect, Rosen::Drawing::SamplingOptions(),
            Rosen::Drawing::SrcRectConstraint::FAST_SRC_RECT_CONSTRAINT);
        bitmapCanvas.DetachBrush();
    }
    if (foreground) {
        BlendForeground(bitmapCanvas, brush, image, background, foreground);
    }
    // convert bitmap back to pixelMap
    bitmapCanvas.ReadPixels(imageInfo, tempCache.GetPixels(), tempCache.GetRowBytes(), 0, 0);
    TransformToPixelMap(tempCache, imageInfo);

    return true;
}

void LayeredDrawableDescriptor::BlendForeground(Rosen::Drawing::Canvas& bitmapCanvas, Rosen::Drawing::Brush& brush,
    Rosen::Drawing::Image& image, const std::shared_ptr<Rosen::Drawing::Bitmap>& background,
    const std::shared_ptr<Rosen::Drawing::Bitmap>& foreground)
{
    if (!foreground || !background || NearEqual(foreground->GetWidth(), 0.0) ||
        NearEqual(foreground->GetHeight(), 0.0)) {
        return;
    }
    auto scale = std::min(background->GetWidth() * 1.0f / foreground->GetWidth(),
        background->GetHeight() * 1.0f / foreground->GetHeight());
    if (NearEqual(scale, 0.0)) {
        return;
    }
    auto destWidth = foreground->GetWidth() * scale;
    auto destHeight = foreground->GetHeight() * scale;
    auto dstOffsetX = static_cast<float>((background->GetWidth() - destWidth) * HALF);
    auto dstOffsetY = static_cast<float>((background->GetHeight() - destHeight) * HALF);
    Rosen::Drawing::Rect rsSrcRect(0.0, 0.0, foreground->GetWidth(), foreground->GetHeight());
    Rosen::Drawing::Rect rsDstRect(dstOffsetX, dstOffsetY,
        destWidth + dstOffsetX, destHeight + dstOffsetY);
    brush.SetBlendMode(Rosen::Drawing::BlendMode::SRC_ATOP);
    bitmapCanvas.AttachBrush(brush);
    image.BuildFromBitmap(*foreground);
    bitmapCanvas.DrawImageRect(image, rsSrcRect, rsDstRect, Rosen::Drawing::SamplingOptions(),
        Rosen::Drawing::SrcRectConstraint::FAST_SRC_RECT_CONSTRAINT);
    bitmapCanvas.DetachBrush();
}

void LayeredDrawableDescriptor::CompositeIconNotAdaptive(std::shared_ptr<Rosen::Drawing::Bitmap>& foreground,
    std::shared_ptr<Rosen::Drawing::Bitmap>& background, std::shared_ptr<Rosen::Drawing::Bitmap>& mask)
{
    Rosen::Drawing::Brush brush;
    brush.SetAntiAlias(true);
    Rosen::Drawing::ImageInfo imageInfo = CreateRSImageInfo(background_, SIDE, SIDE);
    Rosen::Drawing::Bitmap tempCache;
    tempCache.Build(imageInfo);
    Rosen::Drawing::Canvas bitmapCanvas;
    bitmapCanvas.Bind(tempCache);

    // if developer uses customized param, foreground, background, mask might be null
    if (background) {
        brush.SetBlendMode(Rosen::Drawing::BlendMode::SRC);
        bitmapCanvas.AttachBrush(brush);
        DrawOntoCanvas(background, SIDE, SIDE, bitmapCanvas);
        bitmapCanvas.DetachBrush();
    }
    if (mask) {
        brush.SetBlendMode(Rosen::Drawing::BlendMode::DST_IN);
        bitmapCanvas.AttachBrush(brush);
        DrawOntoCanvas(mask, SIDE, SIDE, bitmapCanvas);
        bitmapCanvas.DetachBrush();
    }
    if (foreground) {
        brush.SetBlendMode(Rosen::Drawing::BlendMode::SRC_ATOP);
        bitmapCanvas.AttachBrush(brush);
        DrawOntoCanvas(foreground, SIDE, SIDE, bitmapCanvas);
        bitmapCanvas.DetachBrush();
    }
    bitmapCanvas.ReadPixels(imageInfo, tempCache.GetPixels(), tempCache.GetRowBytes(), 0, 0);
    // convert bitmap back to pixelMap
    Media::InitializationOptions opts;
    if (background_.value_or(nullptr)) {
        opts.alphaType = background_.value()->GetAlphaType();
    } else {
        opts.alphaType = Media::AlphaType::IMAGE_ALPHA_TYPE_PREMUL;
    }
    opts.pixelFormat = Media::PixelFormat::BGRA_8888;
    TransformToPixelMap(tempCache, imageInfo);
}
#endif

#ifndef USE_ROSEN_DRAWING
bool LayeredDrawableDescriptor::CreatePixelMap()
{
    HILOGE("not support");
    return false;
}

bool LayeredDrawableDescriptor::GetCompositePixelMapWithBadge(
    const std::shared_ptr<Media::PixelMap> layeredPixelMap,
    const std::shared_ptr<Media::PixelMap> badgedPixelMap,
    std::shared_ptr<Media::PixelMap> &compositePixelMap)
{
    HILOGE("not support");
    return false;
}
#else
bool LayeredDrawableDescriptor::CreatePixelMap()
{
    // if customizedParam_.HasParamCustomized() true,
    // meaning this descriptor is not created by resource manager,
    // therefore some params might not be valid.
    // Otherwise if HasParamCustomized() false,
    // meaning this descriptor is created by resource manager or 
    // napi directly but has no param passed in, then we should return if any param is missing
    std::shared_ptr<Rosen::Drawing::Bitmap> foreground;
    std::shared_ptr<Rosen::Drawing::Bitmap> background;
    std::shared_ptr<Rosen::Drawing::Bitmap> mask;
    if (!GetLayeredIconParm(foreground, background, mask)) {
        return false;
    }
    // when the foreground'size is 288 x 288, we don't scale.
    if (foreground && NearEqual(NOT_ADAPTIVE_SIZE, foreground->GetWidth()) &&
        NearEqual(NOT_ADAPTIVE_SIZE, foreground->GetHeight())) {
        HILOGD("foreground size is 288 x 288, we don't scale the foreground.");
        CompositeIconNotAdaptive(foreground, background, mask);
        return true;
    } else if (CompositeIconAdaptive(foreground, background, mask)) {
        HILOGD("foreground size is not 288 x 288, we'll scale the foreground.");
        return true;
    }
    return false;
}

bool LayeredDrawableDescriptor::GetCompositePixelMapWithBadge(
    const std::shared_ptr<Media::PixelMap> layeredPixelMap,
    const std::shared_ptr<Media::PixelMap> badgedPixelMap,
    std::shared_ptr<Media::PixelMap> &compositePixelMap)
{
    if ((layeredPixelMap == nullptr) || (badgedPixelMap == nullptr)) {
        HILOGE("failed due to nullptr");
        return false;
    }
    Rosen::Drawing::Brush brush;
    brush.SetAntiAlias(true);
    Rosen::Drawing::ColorType colorType = ImageConverter::PixelFormatToColorType(layeredPixelMap->GetPixelFormat());
    Rosen::Drawing::AlphaType alphaType = ImageConverter::AlphaTypeToAlphaType(layeredPixelMap->GetAlphaType());
    Rosen::Drawing::ImageInfo imageInfo(SIDE + BADGED_SIDE_X, SIDE + BADGED_SIDE_Y, colorType, alphaType);
    Rosen::Drawing::Bitmap tempCache;
    tempCache.Build(imageInfo);
    Rosen::Drawing::Canvas bitmapCanvas;
    bitmapCanvas.Bind(tempCache);
    std::shared_ptr<Rosen::Drawing::Bitmap> layeredBitmap = ImageConverter::PixelMapToBitmap(layeredPixelMap);
    if (layeredBitmap) {
        brush.SetBlendMode(Rosen::Drawing::BlendMode::SRC);
        bitmapCanvas.AttachBrush(brush);
        Rosen::Drawing::Rect srcRect(0, 0, layeredBitmap->GetWidth(), layeredBitmap->GetHeight());
        Rosen::Drawing::Rect dstRect(0, 0, SIDE, SIDE);
        Rosen::Drawing::Image image;
        image.BuildFromBitmap(*layeredBitmap);
        bitmapCanvas.DrawImageRect(image, srcRect, dstRect,
            Rosen::Drawing::SamplingOptions(), Rosen::Drawing::SrcRectConstraint::FAST_SRC_RECT_CONSTRAINT);
        bitmapCanvas.DetachBrush();
    }
    std::shared_ptr<Rosen::Drawing::Bitmap> badgedBitmap = ImageConverter::PixelMapToBitmap(badgedPixelMap);
    if (badgedBitmap) {
        brush.SetBlendMode(Rosen::Drawing::BlendMode::SRC_OVER);
        bitmapCanvas.AttachBrush(brush);
        Rosen::Drawing::Rect srcRect(0, 0, badgedBitmap->GetWidth(), badgedBitmap->GetHeight());
        Rosen::Drawing::Rect dstRect(SIDE + BADGED_SIDE_X - badgedBitmap->GetWidth(),
            SIDE + BADGED_SIDE_Y - badgedBitmap->GetHeight(), SIDE + BADGED_SIDE_X, SIDE + BADGED_SIDE_Y);
        Rosen::Drawing::Image image;
        image.BuildFromBitmap(*badgedBitmap);
        bitmapCanvas.DrawImageRect(image, srcRect, dstRect,
            Rosen::Drawing::SamplingOptions(), Rosen::Drawing::SrcRectConstraint::FAST_SRC_RECT_CONSTRAINT);
        bitmapCanvas.DetachBrush();
    }
    bitmapCanvas.ReadPixels(imageInfo, tempCache.GetPixels(), tempCache.GetRowBytes(), 0, 0);
    Media::InitializationOptions initializationOptions;
    initializationOptions.alphaType = layeredPixelMap->GetAlphaType();
    initializationOptions.pixelFormat = Media::PixelFormat::BGRA_8888;
    compositePixelMap = ImageConverter::BitmapToPixelMap(std::make_shared<Rosen::Drawing::Bitmap>(tempCache),
        initializationOptions);
    return true;
}
#endif

std::shared_ptr<Media::PixelMap> LayeredDrawableDescriptor::GetPixelMap()
{
    if (layeredPixelMap_.value_or(nullptr)) {
        return layeredPixelMap_.value();
    }

    if (CreatePixelMap()) {
        return layeredPixelMap_.value();
    }

    HILOGE("Failed to GetPixelMap!");
    return nullptr;
}

DrawableDescriptor::DrawableType LayeredDrawableDescriptor::GetDrawableType()
{
    return DrawableType::LAYERED;
}

std::string LayeredDrawableDescriptor::GetStaticMaskClipPath()
{
    std::string data;
#if defined(ANDROID_PLATFORM) || defined(IOS_PLATFORM)
    std::shared_ptr<AbilityRuntime::Platform::ApplicationContext> applicationContext =
        AbilityRuntime::Platform::ApplicationContext::GetInstance();
    if (!applicationContext) {
        HILOGE("Failed to get applicationContext!");
        data = "";
        return data;
    }
    auto resMgr = applicationContext->GetResourceManager();
    if (!resMgr) {
        HILOGE("Failed to get resource manager!");
        data = "";
        return data;
    }
#else
    std::shared_ptr<Global::Resource::ResourceManager> resMgr(Global::Resource::CreateResourceManager());
#endif
#ifdef PREVIEW
    std::string pathTmp = "";
#ifdef WINDOWS_PLATFORM
    char pathBuf[MAX_PATH];
    _getcwd(pathBuf, MAX_PATH);
    pathTmp = pathBuf;
#elif defined(MAC_PLATFORM)
    uint32_t size = 0;
    _NSGetExecutablePath(nullptr, &size);

    char pathBuf[size + 1];
    if (_NSGetExecutablePath(pathBuf, &size) != 0) {
        pathBuf[0] = '\0';
        HILOGE("Failed, buffer too small!");
    }
    pathBuf[size] = '\0';

    std::string previewFullPath = pathBuf;
    size_t lastPathIdx = previewFullPath.find_last_of("\\/");
    pathTmp = (lastPathIdx != std::string::npos) ? previewFullPath.substr(0, lastPathIdx) : "";
#else
    char pathBuf[MAX_PATH_LEN];
    readlink("/proc/self/exe", pathBuf, MAX_PATH_LEN);
    pathTmp = pathBuf;
#endif
    size_t lastPathSepLoc = pathTmp.find_last_of("\\/");
    std::string path = (lastPathSepLoc != std::string::npos) ? pathTmp.substr(0, lastPathSepLoc) : "";
    path += PREVIEW_LOAD_RESOURCE_PATH;
    resMgr->AddResource(path.c_str());
#endif
    resMgr->GetStringByName(PREVIEW_LOAD_RESOURCE_ID, data);
    return data;
}

std::shared_ptr<Media::PixelMap> AnimatedDrawableDescriptor::GetPixelMap()
{
    if (pixelMapList_.empty()) {
        return nullptr;
    }
    return pixelMapList_[0];
}

DrawableDescriptor::DrawableType AnimatedDrawableDescriptor::GetDrawableType()
{
    return DrawableType::ANIMATED;
}

std::vector<std::shared_ptr<Media::PixelMap>> AnimatedDrawableDescriptor::GetPixelMapList()
{
    return pixelMapList_;
}

int32_t AnimatedDrawableDescriptor::GetDuration()
{
    if (duration_ <= 0) {
        duration_ = DEFAULT_DURATION * static_cast<int32_t>(pixelMapList_.size());
    }
    return duration_;
}

int32_t AnimatedDrawableDescriptor::GetIterations()
{
    if (iterations_ < -1) {
        iterations_ = 1;
    }
    return iterations_;
}

void AnimatedDrawableDescriptor::SetDuration(int32_t duration)
{
    if (duration <= 0) {
        duration_ = DEFAULT_DURATION * static_cast<int32_t>(pixelMapList_.size());
    } else {
        duration_ = duration;
    }
}

void AnimatedDrawableDescriptor::SetIterations(int32_t iterations)
{
    if (iterations < -1) {
        iterations_ = 1;
    } else {
        iterations_ = iterations;
    }
}
} // namespace OHOS::Ace::Napi
