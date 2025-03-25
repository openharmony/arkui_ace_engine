/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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

#if defined(ANDROID_PLATFORM) || defined(IOS_PLATFORM)
#include "application_context.h"
#endif
#include <cerrno>
#include <cstdlib>
#include <limits>

#include "draw/canvas.h"
#include "image/bitmap.h"
#include "image/image_info.h"
#include "resource_manager.h"
#include "securec.h"

#ifdef PREVIEW
#ifdef WINDOWS_PLATFORM
#include <direct.h>
#include <windows.h>
#ifdef ERROR
#undef ERROR
#endif
#elif defined(MAC_PLATFORM)
#include <mach-o/dyld.h>
#else
#include <unistd.h>
#endif
#endif

#include "cJSON.h"
#ifndef PREVIEW
#include "image_source.h"
#include "pixel_map.h"
#else
#include "image_source_preview.h"
#endif
#include "base/log.h"

namespace OHOS {
namespace Ace {
namespace Napi {
namespace {
const char DRAWABLEDESCRIPTOR_JSON_KEY_BACKGROUND[] = "background";
const char DRAWABLEDESCRIPTOR_JSON_KEY_FOREGROUND[] = "foreground";
constexpr float BADGED_SIDE_X = 21.0f;
constexpr float BADGED_SIDE_Y = 7.0f;
constexpr float SIDE = 192.0f;
constexpr float NOT_ADAPTIVE_SIZE = 288.0f;
constexpr float HALF = 0.5f;
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

inline bool NearEqual(const double left, const double right, const double epsilon)
{
    return (std::abs(left - right) <= epsilon);
}

inline bool NearEqual(const double left, const double right)
{
    constexpr double epsilon = 0.001f;
    return NearEqual(left, right, epsilon);
}

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

Rosen::Drawing::ColorType PixelFormatToColorType(Media::PixelFormat pixelFormat)
{
    switch (pixelFormat) {
        case Media::PixelFormat::BGRA_8888:
            return Rosen::Drawing::ColorType::COLORTYPE_BGRA_8888;
        case Media::PixelFormat::ARGB_8888:
        case Media::PixelFormat::ALPHA_8:
        case Media::PixelFormat::RGBA_8888:
        case Media::PixelFormat::RGB_565:
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

Rosen::Drawing::AlphaType AlphaTypeToAlphaType(Media::AlphaType alphaType)
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

SharedBitMap PixelMapToBitmap(const SharedPixelMap& pixelMap)
{
    if (!pixelMap) {
        return nullptr;
    }
    auto data = pixelMap->GetPixels();
    RSBitmap bitmap;
    Rosen::Drawing::ColorType colorType = PixelFormatToColorType(pixelMap->GetPixelFormat());
    Rosen::Drawing::AlphaType alphaType = AlphaTypeToAlphaType(pixelMap->GetAlphaType());
    RSImageInfo imageInfo(pixelMap->GetWidth(), pixelMap->GetHeight(), colorType, alphaType);
    bitmap.Build(imageInfo);
    bitmap.SetPixels(const_cast<uint8_t*>(data));
    return std::make_shared<RSBitmap>(bitmap);
}

SharedPixelMap BitmapToPixelMap(const SharedBitMap& bitMap, Media::InitializationOptions& opts)
{
    auto data = bitMap->GetPixels();
    opts.size.width = static_cast<int32_t>(bitMap->GetWidth());
    opts.size.height = static_cast<int32_t>(bitMap->GetHeight());
    opts.editable = false;
    auto pixelMap = Media::PixelMap::Create(opts);
    if (!pixelMap) {
        HILOGE("PixelMap is null, bitMap's Size = (%{public}d, %{public}d)", bitMap->GetWidth(), bitMap->GetHeight());
        return pixelMap;
    }
    auto dstAddr = pixelMap->GetWritablePixels();
    if (memcpy_s(dstAddr, pixelMap->GetByteCount(), data, pixelMap->GetByteCount()) != 0) {
        HILOGE("PixelMap write fail");
        return nullptr;
    }
    return pixelMap;
}

void DrawOntoCanvas(const SharedBitMap& bitMap, float width, float height, RSCanvas& canvas)
{
    auto x = static_cast<float>((bitMap->GetWidth() - static_cast<float>(width)) / 2);
    auto y = static_cast<float>((bitMap->GetHeight() - static_cast<float>(height)) / 2);
    Rosen::Drawing::Rect srcRect(x, y, static_cast<float>(width) + x, static_cast<float>(width) + y);
    Rosen::Drawing::Rect dstRect(0, 0, static_cast<float>(width), static_cast<float>(width));
    RSImage image;
    image.BuildFromBitmap(*bitMap);
    canvas.DrawImageRect(image, srcRect, dstRect, Rosen::Drawing::SamplingOptions(),
        Rosen::Drawing::SrcRectConstraint::FAST_SRC_RECT_CONSTRAINT);
}

RSImageInfo CreateRSImageInfo(OptionalPixelMap pixelmap, int32_t width, int32_t height)
{
    Rosen::Drawing::ColorType colorType = pixelmap.value_or(nullptr)
                                              ? colorType = PixelFormatToColorType(pixelmap.value()->GetPixelFormat())
                                              : colorType = PixelFormatToColorType(Media::PixelFormat::RGBA_8888);
    Rosen::Drawing::AlphaType alphaType =
        pixelmap.value_or(nullptr) ? alphaType = AlphaTypeToAlphaType(pixelmap.value()->GetAlphaType())
                                   : alphaType = AlphaTypeToAlphaType(Media::AlphaType::IMAGE_ALPHA_TYPE_PREMUL);
    return RSImageInfo(width, height, colorType, alphaType);
}

void BlendForeground(RSCanvas& bitmapCanvas, RSBrush& brush, RSImage& image, const SharedBitMap& background,
    const SharedBitMap& foreground)
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
    Rosen::Drawing::Rect rsDstRect(dstOffsetX, dstOffsetY, destWidth + dstOffsetX, destHeight + dstOffsetY);
    brush.SetBlendMode(Rosen::Drawing::BlendMode::SRC_ATOP);
    bitmapCanvas.AttachBrush(brush);
    image.BuildFromBitmap(*foreground);
    bitmapCanvas.DrawImageRect(image, rsSrcRect, rsDstRect, Rosen::Drawing::SamplingOptions(),
        Rosen::Drawing::SrcRectConstraint::FAST_SRC_RECT_CONSTRAINT);
    bitmapCanvas.DetachBrush();
}

#ifndef PREVIEW
UniqueImageSource CreateImageSource(DrawableItem& drawableItem, uint32_t& errorCode)
{
    if (drawableItem.state_ != Global::Resource::SUCCESS) {
        HILOGE("GetDrawableInfoById failed");
        return nullptr;
    }

    Media::SourceOptions opts;
    return Media::ImageSource::CreateImageSource(drawableItem.data_.get(), drawableItem.len_, opts, errorCode);
}
#endif
} // namespace

bool DrawableDescriptor::GetPixelMapFromBuffer()
{
    Media::SourceOptions opts;
    uint32_t errorCode = 0;
    UniqueImageSource imageSource = Media::ImageSource::CreateImageSource(mediaData_.get(), len_, opts, errorCode);
    if (errorCode != 0) {
        HILOGE("CreateImageSource from buffer failed");
        return false;
    }
    mediaData_.reset();
    Media::DecodeOptions decodeOpts;
    auto decoderSize = GetDecodeSize();
    if (decoderSize.has_value()) {
        decodeOpts.desiredSize = { std::max(0, decoderSize->first), std::max(0, decoderSize->second) };
    }
    decodeOpts.desiredPixelFormat = Media::PixelFormat::BGRA_8888;
    if (imageSource) {
        auto pixelMapPtr = imageSource->CreatePixelMap(decodeOpts, errorCode);
        pixelMap_ = SharedPixelMap(pixelMapPtr.release());
    }
    if (errorCode != 0 || !pixelMap_) {
        HILOGE("Get PixelMap from buffer failed");
        return false;
    }
    return true;
}

SharedPixelMap DrawableDescriptor::GetPixelMap()
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

DrawableItem LayeredDrawableDescriptor::PreGetDrawableItem(const SharedResourceManager& resourceMgr, const char* item)
{
    DrawableItem resItem;
    std::string itemStr = item;
    std::string idStr;
    resItem.state_ = Global::Resource::ERROR;

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

bool LayeredDrawableDescriptor::PreGetPixelMapFromJsonBuf(const SharedResourceManager& resourceMgr, bool isBackground)
{
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
}

void LayeredDrawableDescriptor::InitialResource(const SharedResourceManager& resourceMgr)
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

void LayeredDrawableDescriptor::InitialMask(const SharedResourceManager& resourceMgr)
{
    resourceMgr->GetMediaDataByName(DEFAULT_MASK.c_str(), defaultMaskDataLength_, defaultMaskData_);
}

void DrawableDescriptor::SetDecodeSize(int32_t width, int32_t height)
{
    decodeSize_ = { width, height };
}

OptionalDecodeSize DrawableDescriptor::GetDecodeSize()
{
    return decodeSize_;
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
        UniqueImageSource imageSource = CreateImageSource(isBackground ? backgroundItem_ : foregroundItem_, errorCode);
        if (errorCode != 0) {
            HILOGE("CreateImageSource from json buffer failed");
            return false;
        }
        Media::DecodeOptions decodeOpts;
        decodeOpts.desiredPixelFormat = Media::PixelFormat::BGRA_8888;
        auto decoderSize = GetDecodeSize();
        auto decoderWidth = decoderSize.has_value() ? decoderSize->first : 0;
        auto decoderHeight = decoderSize.has_value() ? decoderSize->second : 0;
        decodeOpts.desiredSize = { std::max(0, decoderWidth), std::max(0, decoderHeight) };
        if (imageSource) {
            auto pixelMapPtr = imageSource->CreatePixelMap(decodeOpts, errorCode);
            if (errorCode != 0) {
                HILOGE("Get PixelMap from json buffer failed");
                return false;
            }

            if (isBackground) {
                background_ = SharedPixelMap(pixelMapPtr.release());
            } else {
                foreground_ = SharedPixelMap(pixelMapPtr.release());
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
    UniqueImageSource imageSource =
        Media::ImageSource::CreateImageSource(defaultMaskData_.get(), defaultMaskDataLength_, opts, errorCode);
    Media::DecodeOptions decodeOpts;
    decodeOpts.desiredPixelFormat = Media::PixelFormat::BGRA_8888;
    if (imageSource) {
        auto pixelMapPtr = imageSource->CreatePixelMap(decodeOpts, errorCode);
        mask_ = SharedPixelMap(pixelMapPtr.release());
    }
    if (errorCode != 0 || !mask_) {
        HILOGE("Get mask failed");
        return false;
    }
    return true;
}

void LayeredDrawableDescriptor::InitLayeredParam(
    std::pair<UINT8, size_t>& foregroundInfo, std::pair<UINT8, size_t>& backgroundInfo)
{
    Media::SourceOptions opts;
    uint32_t errorCode = 0;
    auto foreground =
        Media::ImageSource::CreateImageSource(foregroundInfo.first.get(), foregroundInfo.second, opts, errorCode);
    auto decoderSize = GetDecodeSize();
    if (errorCode == 0 && foreground) {
        Media::DecodeOptions decodeOpts;
        decodeOpts.desiredPixelFormat = Media::PixelFormat::BGRA_8888;
        if (decoderSize.has_value()) {
            decodeOpts.desiredSize = { std::max(0, decoderSize->first), std::max(0, decoderSize->second) };
        }
        auto pixelMapPtr = foreground->CreatePixelMap(decodeOpts, errorCode);
        foreground_ = SharedPixelMap(pixelMapPtr.release());
    }
    auto background =
        Media::ImageSource::CreateImageSource(backgroundInfo.first.get(), backgroundInfo.second, opts, errorCode);
    if (errorCode == 0 && background) {
        Media::DecodeOptions decodeOpts;
        decodeOpts.desiredPixelFormat = Media::PixelFormat::BGRA_8888;
        if (decoderSize.has_value()) {
            decodeOpts.desiredSize = { std::max(0, decoderSize->first), std::max(0, decoderSize->second) };
        }
        auto pixelMapPtr = background->CreatePixelMap(decodeOpts, errorCode);
        background_ = SharedPixelMap(pixelMapPtr.release());
    }
}

void LayeredDrawableDescriptor::SetForeground(SharedPixelMap foreground)
{
    foreground_ = foreground;
    customized_ = true;
}

void LayeredDrawableDescriptor::SetBackground(SharedPixelMap background)
{
    background_ = background;
    customized_ = true;
}

void LayeredDrawableDescriptor::SetMask(SharedPixelMap mask)
{
    mask_ = mask;
    customized_ = true;
}

bool LayeredDrawableDescriptor::Customized()
{
    return customized_;
}

bool LayeredDrawableDescriptor::GetMaskByPath()
{
    if (maskPath_.empty()) {
        HILOGD("maskPath is null");
        return false;
    }
    Media::SourceOptions opts;
    uint32_t errorCode = 0;
    UniqueImageSource imageSource = Media::ImageSource::CreateImageSource(maskPath_, opts, errorCode);
    Media::DecodeOptions decodeOpts;
    decodeOpts.desiredPixelFormat = Media::PixelFormat::BGRA_8888;
    if (imageSource) {
        auto pixelMapPtr = imageSource->CreatePixelMap(decodeOpts, errorCode);
        mask_ = SharedPixelMap(pixelMapPtr.release());
    }
    if (errorCode != 0 || !mask_) {
        HILOGE("Get mask failed");
        return false;
    }
    return true;
}

bool LayeredDrawableDescriptor::GetMaskByName(SharedResourceManager& resourceMgr, const std::string& name)
{
    size_t len = 0;
    UINT8 data;
    resourceMgr->GetMediaDataByName(name.c_str(), len, data);
    Media::SourceOptions opts;
    uint32_t errorCode = 0;
    UniqueImageSource imageSource = Media::ImageSource::CreateImageSource(data.get(), len, opts, errorCode);
    Media::DecodeOptions decodeOpts;
    decodeOpts.desiredPixelFormat = Media::PixelFormat::BGRA_8888;
    if (imageSource) {
        auto pixelMapPtr = imageSource->CreatePixelMap(decodeOpts, errorCode);
        mask_ = SharedPixelMap(pixelMapPtr.release());
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

bool LayeredDrawableDescriptor::GetLayeredIconParm(
    SharedBitMap& foreground, SharedBitMap& background, SharedBitMap& mask)
{
    if (foreground_.value_or(nullptr) || GetPixelMapFromJsonBuf(false)) {
        foreground = PixelMapToBitmap(foreground_.value());
    } else if (!customized_) {
        HILOGI("Get pixelMap of foreground failed.");
        return false;
    }
    if (background_.value_or(nullptr) || GetPixelMapFromJsonBuf(true)) {
        background = PixelMapToBitmap(background_.value());
    } else if (!customized_) {
        HILOGE("Get pixelMap of background failed.");
        return false;
    }
    if (mask_.value_or(nullptr) || GetMaskByPath() || GetDefaultMask()) {
        mask = PixelMapToBitmap(mask_.value());
    } else if (!customized_) {
        HILOGE("Get pixelMap of mask failed.");
        return false;
    }
    return true;
}

void LayeredDrawableDescriptor::TransformToPixelMap(const RSBitmap& bitmap, const RSImageInfo& imageInfo)
{
    Media::InitializationOptions opts;
    if (background_.value_or(nullptr)) {
        opts.alphaType = background_.value()->GetAlphaType();
    } else {
        opts.alphaType = Media::AlphaType::IMAGE_ALPHA_TYPE_PREMUL;
    }
    opts.pixelFormat = Media::PixelFormat::BGRA_8888;
    layeredPixelMap_ = BitmapToPixelMap(std::make_shared<RSBitmap>(bitmap), opts);
}

bool LayeredDrawableDescriptor::CompositeIconAdaptive(
    SharedBitMap& foreground, SharedBitMap& background, SharedBitMap& mask)
{
    if (!background) {
        HILOGW("The background is null when adaptive composite icons are used.");
        return false;
    }
    RSBrush brush;
    brush.SetAntiAlias(true);
    RSImageInfo imageInfo = CreateRSImageInfo(background_, background->GetWidth(), background->GetHeight());
    RSBitmap tempCache;
    tempCache.Build(imageInfo);
    RSCanvas bitmapCanvas;
    bitmapCanvas.Bind(tempCache);

    if (background) {
        brush.SetBlendMode(Rosen::Drawing::BlendMode::SRC);
        bitmapCanvas.AttachBrush(brush);
        DrawOntoCanvas(background, background->GetWidth(), background->GetHeight(), bitmapCanvas);
        bitmapCanvas.DetachBrush();
    }

    Rosen::Drawing::Rect dstRect(
        0.0, 0.0, static_cast<float>(background->GetWidth()), static_cast<float>(background->GetHeight()));
    RSImage image;
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

void LayeredDrawableDescriptor::CompositeIconNotAdaptive(
    SharedBitMap& foreground, SharedBitMap& background, SharedBitMap& mask)
{
    RSBrush brush;
    brush.SetAntiAlias(true);
    RSImageInfo imageInfo = CreateRSImageInfo(background_, SIDE, SIDE);
    RSBitmap tempCache;
    tempCache.Build(imageInfo);
    RSCanvas bitmapCanvas;
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

bool LayeredDrawableDescriptor::GetCompositePixelMapWithBadge(
    const SharedPixelMap layeredPixelMap, const SharedPixelMap badgedPixelMap, SharedPixelMap& compositePixelMap)
{
    if ((layeredPixelMap == nullptr) || (badgedPixelMap == nullptr)) {
        HILOGE("failed due to nullptr");
        return false;
    }
    RSBrush brush;
    brush.SetAntiAlias(true);
    Rosen::Drawing::ColorType colorType = PixelFormatToColorType(layeredPixelMap->GetPixelFormat());
    Rosen::Drawing::AlphaType alphaType = AlphaTypeToAlphaType(layeredPixelMap->GetAlphaType());
    RSImageInfo imageInfo(SIDE + BADGED_SIDE_X, SIDE + BADGED_SIDE_Y, colorType, alphaType);
    RSBitmap tempCache;
    tempCache.Build(imageInfo);
    RSCanvas bitmapCanvas;
    bitmapCanvas.Bind(tempCache);
    SharedBitMap layeredBitmap = PixelMapToBitmap(layeredPixelMap);
    if (layeredBitmap) {
        brush.SetBlendMode(Rosen::Drawing::BlendMode::SRC);
        bitmapCanvas.AttachBrush(brush);
        Rosen::Drawing::Rect srcRect(0, 0, layeredBitmap->GetWidth(), layeredBitmap->GetHeight());
        Rosen::Drawing::Rect dstRect(0, 0, SIDE, SIDE);
        RSImage image;
        image.BuildFromBitmap(*layeredBitmap);
        bitmapCanvas.DrawImageRect(image, srcRect, dstRect, Rosen::Drawing::SamplingOptions(),
            Rosen::Drawing::SrcRectConstraint::FAST_SRC_RECT_CONSTRAINT);
        bitmapCanvas.DetachBrush();
    }
    SharedBitMap badgedBitmap = PixelMapToBitmap(badgedPixelMap);
    if (badgedBitmap) {
        brush.SetBlendMode(Rosen::Drawing::BlendMode::SRC_OVER);
        bitmapCanvas.AttachBrush(brush);
        Rosen::Drawing::Rect srcRect(0, 0, badgedBitmap->GetWidth(), badgedBitmap->GetHeight());
        Rosen::Drawing::Rect dstRect(SIDE + BADGED_SIDE_X - badgedBitmap->GetWidth(),
            SIDE + BADGED_SIDE_Y - badgedBitmap->GetHeight(), SIDE + BADGED_SIDE_X, SIDE + BADGED_SIDE_Y);
        RSImage image;
        image.BuildFromBitmap(*badgedBitmap);
        bitmapCanvas.DrawImageRect(image, srcRect, dstRect, Rosen::Drawing::SamplingOptions(),
            Rosen::Drawing::SrcRectConstraint::FAST_SRC_RECT_CONSTRAINT);
        bitmapCanvas.DetachBrush();
    }
    bitmapCanvas.ReadPixels(imageInfo, tempCache.GetPixels(), tempCache.GetRowBytes(), 0, 0);
    Media::InitializationOptions initializationOptions;
    initializationOptions.alphaType = layeredPixelMap->GetAlphaType();
    initializationOptions.pixelFormat = Media::PixelFormat::BGRA_8888;
    compositePixelMap = BitmapToPixelMap(std::make_shared<RSBitmap>(tempCache), initializationOptions);
    return true;
}

bool LayeredDrawableDescriptor::CreatePixelMap()
{
    // if customizedParam_.HasParamCustomized() true,
    // meaning this descriptor is not created by resource manager,
    // therefore some params might not be valid.
    // Otherwise if HasParamCustomized() false,
    // meaning this descriptor is created by resource manager or
    // napi directly but has no param passed in, then we should return if any param is missing
    SharedBitMap foreground;
    SharedBitMap background;
    SharedBitMap mask;
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

SharedPixelMap LayeredDrawableDescriptor::GetPixelMap()
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
    SharedResourceManager resMgr(Global::Resource::CreateResourceManager());
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

SharedPixelMap AnimatedDrawableDescriptor::GetPixelMap()
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

std::vector<SharedPixelMap> AnimatedDrawableDescriptor::GetPixelMapList()
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

// drawable factory implement
std::unique_ptr<DrawableDescriptor> DrawableDescriptorFactory::Create(
    int32_t id, const SharedResourceManager& resourceMgr, RState& state, DrawableType& drawableType, uint32_t density)
{
    std::string type;
    size_t len;
    UINT8 jsonBuf;
    state = resourceMgr->GetDrawableInfoById(id, type, len, jsonBuf, density);
    if (state != Global::Resource::SUCCESS) {
        HILOGE("Failed to get drawable info from resmgr");
        return nullptr;
    }
    transform(type.begin(), type.end(), type.begin(), ::tolower);
    if (type == "json") {
        HILOGD("Create LayeredDrawableDescriptor object");
        drawableType = DrawableDescriptor::DrawableType::LAYERED;
        state = Global::Resource::SUCCESS;
        return std::make_unique<LayeredDrawableDescriptor>(std::move(jsonBuf), len, resourceMgr);
    }
    if (type == "png" || type == "jpg" || type == "bmp" || type == "svg" || type == "gif" || type == "webp" ||
        type == "astc" || type == "sut") {
        HILOGD("Create DrawableDescriptor object");
        drawableType = DrawableDescriptor::DrawableType::BASE;
        state = Global::Resource::SUCCESS;
        return std::make_unique<DrawableDescriptor>(std::move(jsonBuf), len);
    }
    HILOGE("unknow resource type: %{public}s", type.c_str());
    state = Global::Resource::INVALID_FORMAT;
    return nullptr;
}

std::unique_ptr<DrawableDescriptor> DrawableDescriptorFactory::Create(const char* name,
    const SharedResourceManager& resourceMgr, RState& state, DrawableType& drawableType, uint32_t density)
{
    std::string type;
    size_t len;
    UINT8 jsonBuf;
    state = resourceMgr->GetDrawableInfoByName(name, type, len, jsonBuf, density);
    if (state != Global::Resource::SUCCESS) {
        HILOGE("Failed to get drawable info from resmgr");
        return nullptr;
    }
    transform(type.begin(), type.end(), type.begin(), ::tolower);
    if (type == "json") {
        HILOGD("Create LayeredDrawableDescriptor object");
        drawableType = DrawableDescriptor::DrawableType::LAYERED;
        state = Global::Resource::SUCCESS;
        return std::make_unique<LayeredDrawableDescriptor>(std::move(jsonBuf), len, resourceMgr);
    }
    if (type == "png" || type == "jpg" || type == "bmp" || type == "svg" || type == "gif" || type == "webp" ||
        type == "astc" || type == "sut") {
        HILOGD("Create DrawableDescriptor object");
        drawableType = DrawableDescriptor::DrawableType::BASE;
        state = Global::Resource::SUCCESS;
        return std::make_unique<DrawableDescriptor>(std::move(jsonBuf), len);
    }
    HILOGE("unknow resource type: %{public}s", type.c_str());
    state = Global::Resource::INVALID_FORMAT;
    return nullptr;
}

std::unique_ptr<DrawableDescriptor> DrawableDescriptorFactory::Create(
    std::tuple<int32_t, uint32_t, uint32_t>& drawableInfo, const SharedResourceManager& resourceMgr, RState& state,
    DrawableType& drawableType)
{
    int32_t resId = std::get<0>(drawableInfo);
    uint32_t iconType = std::get<1>(drawableInfo);
    uint32_t density = std::get<2>(drawableInfo);
    UINT8 jsonBuf;
    std::tuple<std::string, size_t, std::string> info;
    state = resourceMgr->GetDrawableInfoById(resId, info, jsonBuf, iconType, density);
    if (state != Global::Resource::SUCCESS) {
        HILOGW("Failed to get drawable info from resmgr");
        return nullptr;
    }
    std::string type = std::get<0>(info);
    size_t len = std::get<1>(info);
    std::string path = std::get<2>(info);
    transform(type.begin(), type.end(), type.begin(), ::tolower);
    if (type == "json") {
        HILOGD("Create LayeredDrawableDescriptor object");
        drawableType = DrawableDescriptor::DrawableType::LAYERED;
        auto layeredDrawableDescriptor =
            std::make_unique<LayeredDrawableDescriptor>(std::move(jsonBuf), len, resourceMgr, path, iconType, density);
        return layeredDrawableDescriptor;
    }
    if (type == "png" || type == "jpg" || type == "bmp" || type == "svg" || type == "gif" || type == "webp" ||
        type == "astc" || type == "sut") {
        HILOGD("Create DrawableDescriptor object");
        drawableType = DrawableDescriptor::DrawableType::BASE;
        return std::make_unique<DrawableDescriptor>(std::move(jsonBuf), len);
    }
    HILOGE("unknow resource type: %{public}s", type.c_str());
    state = Global::Resource::INVALID_FORMAT;
    return nullptr;
}

std::unique_ptr<DrawableDescriptor> DrawableDescriptorFactory::Create(
    std::tuple<const char*, uint32_t, uint32_t>& drawableInfo, const SharedResourceManager& resourceMgr, RState& state,
    DrawableType& drawableType)
{
    const char* name = std::get<0>(drawableInfo);
    uint32_t iconType = std::get<1>(drawableInfo);
    uint32_t density = std::get<2>(drawableInfo);
    UINT8 jsonBuf;
    std::tuple<std::string, size_t, std::string> info;
    state = resourceMgr->GetDrawableInfoByName(name, info, jsonBuf, iconType, density);
    if (state != Global::Resource::SUCCESS) {
        HILOGW("Failed to get drawable info from resmgr");
        return nullptr;
    }
    std::string type = std::get<0>(info);
    size_t len = std::get<1>(info);
    std::string path = std::get<2>(info);
    transform(type.begin(), type.end(), type.begin(), ::tolower);
    if (type == "json") {
        HILOGD("Create LayeredDrawableDescriptor object");
        drawableType = DrawableDescriptor::DrawableType::LAYERED;
        auto layeredDrawableDescriptor =
            std::make_unique<LayeredDrawableDescriptor>(std::move(jsonBuf), len, resourceMgr, path, iconType, density);
        return layeredDrawableDescriptor;
    }
    if (type == "png" || type == "jpg" || type == "bmp" || type == "svg" || type == "gif" || type == "webp" ||
        type == "astc" || type == "sut") {
        HILOGD("Create DrawableDescriptor object");
        drawableType = DrawableDescriptor::DrawableType::BASE;
        return std::make_unique<DrawableDescriptor>(std::move(jsonBuf), len);
    }
    HILOGE("unknow resource type: %{public}s", type.c_str());
    state = Global::Resource::INVALID_FORMAT;
    return nullptr;
}

std::unique_ptr<DrawableDescriptor> DrawableDescriptorFactory::Create(DataInfo& foregroundInfo,
    DataInfo& backgroundInfo, std::string& path, DrawableType& drawableType, const SharedResourceManager& resourceMgr)
{
    UINT8 jsonBuf;
    drawableType = DrawableDescriptor::DrawableType::LAYERED;
    auto layeredDrawableDescriptor = std::make_unique<LayeredDrawableDescriptor>(
        std::move(jsonBuf), 0, resourceMgr, path, 1, foregroundInfo, backgroundInfo);
    return layeredDrawableDescriptor;
}
} // namespace Napi
} // namespace Ace
} // namespace OHOS
