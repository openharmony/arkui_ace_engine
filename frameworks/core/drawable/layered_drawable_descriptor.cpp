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

#include "core/drawable/layered_drawable_descriptor.h"

#include <algorithm>
#include <memory>
#include <vector>
#include "securec.h"

#include "base/image/image_source.h"
#include "base/image/pixel_map.h"
#include "core/components_ng/render/drawing.h"

namespace OHOS::Ace {

extern "C" ACE_FORCE_EXPORT int32_t OH_ACE_LayeredDrawableDescriptor_SetForegroundData(
    void* object, uint8_t* data, size_t len)
{
    auto* drawable = reinterpret_cast<LayeredDrawableDescriptor*>(object);
    if (drawable) {
        std::vector<uint8_t> result(data, data + len);
        drawable->SetForegroundData(result);
        return 1;
    }
    return 0;
}

extern "C" ACE_FORCE_EXPORT int32_t OH_ACE_LayeredDrawableDescriptor_SetBackgroundData(
    void* object, uint8_t* data, size_t len)
{
    auto* drawable = reinterpret_cast<LayeredDrawableDescriptor*>(object);
    if (drawable) {
        std::vector<uint8_t> result(data, data + len);
        drawable->SetBackgroundData(result);
        return 1;
    }
    return 0;
}

extern "C" ACE_FORCE_EXPORT int32_t OH_ACE_LayeredDrawableDescriptor_SetMaskData(
    void* object, uint8_t* data, size_t len)
{
    auto* drawable = reinterpret_cast<LayeredDrawableDescriptor*>(object);
    if (drawable) {
        std::vector<uint8_t> result(data, data + len);
        drawable->SetMaskData(result);
        return 1;
    }
    return 0;
}

extern "C" ACE_FORCE_EXPORT int32_t OH_ACE_LayeredDrawableDescriptor_SetMaskPath(void* object, const char* path)
{
    auto* drawable = reinterpret_cast<LayeredDrawableDescriptor*>(object);
    if (drawable) {
        drawable->SetMaskPath(std::string(path));
        return 1;
    }
    return 0;
}

namespace {
constexpr float HALF = 0.5;
constexpr float SIDE = 192.0f;
constexpr int32_t NOT_ADAPTIVE_SIZE = 288;
constexpr float THRESHOLD = 0.001;

RSColorType PixelFormatToColorType(PixelFormat format)
{
    switch (format) {
        case PixelFormat::BGRA_8888:
            return RSColorType::COLORTYPE_BGRA_8888;
        case PixelFormat::ARGB_8888:
        case PixelFormat::ALPHA_8:
        case PixelFormat::RGBA_8888:
        case PixelFormat::RGB_565:
        case PixelFormat::RGB_888:
        case PixelFormat::RGBA_F16:
        case PixelFormat::NV21:
        case PixelFormat::NV12:
        case PixelFormat::CMYK:
        case PixelFormat::UNKNOWN:
        default:
            return RSColorType::COLORTYPE_UNKNOWN;
    }
}

RSAlphaType ConvertAlphaType(AlphaType type)
{
    switch (type) {
        case AlphaType::IMAGE_ALPHA_TYPE_OPAQUE:
            return RSAlphaType::ALPHATYPE_OPAQUE;
        case AlphaType::IMAGE_ALPHA_TYPE_PREMUL:
            return RSAlphaType::ALPHATYPE_PREMUL;
        case AlphaType::IMAGE_ALPHA_TYPE_UNPREMUL:
            return RSAlphaType::ALPHATYPE_UNPREMUL;
        case AlphaType::IMAGE_ALPHA_TYPE_UNKNOWN:
        default:
            return RSAlphaType::ALPHATYPE_UNKNOWN;
    }
}

RSImageInfo CreateRSImageInfo(const RefPtr<PixelMap>& pixelmap, int32_t width, int32_t height)
{
    RSColorType colorType;
    RSAlphaType alphaType;
    if (pixelmap) {
        colorType = PixelFormatToColorType(pixelmap->GetPixelFormat());
        alphaType = ConvertAlphaType(pixelmap->GetAlphaType());
    } else {
        colorType = PixelFormatToColorType(PixelFormat::RGBA_8888);
        alphaType = ConvertAlphaType(AlphaType::IMAGE_ALPHA_TYPE_PREMUL);
    }
    return RSImageInfo(width, height, colorType, alphaType);
}

void DrawOntoCanvas(const std::shared_ptr<RSBitmap>& bitMap, int32_t width, int32_t height, RSCanvas& canvas)
{
    auto x = static_cast<float>((bitMap->GetWidth() - static_cast<float>(width)) / 2);
    auto y = static_cast<float>((bitMap->GetHeight() - static_cast<float>(height)) / 2);
    RSRect srcRect(x, y, static_cast<float>(width) + x, static_cast<float>(width) + y);
    RSRect dstRect(0, 0, static_cast<float>(width), static_cast<float>(width));
    RSImage image;
    image.BuildFromBitmap(*bitMap);
    canvas.DrawImageRect(image, srcRect, dstRect, RSSamplingOptions(), RSSrcRectConstraint::FAST_SRC_RECT_CONSTRAINT);
}

void BlendForeground(RSCanvas& bitmapCanvas, RSBrush& brush, RSImage& image,
    const std::shared_ptr<RSBitmap>& background, const std::shared_ptr<RSBitmap>& foreground)
{
    if (!foreground || !background || foreground->GetWidth() == 0 || foreground->GetHeight() == 0) {
        return;
    }
    auto scale = std::min(background->GetWidth() * 1.0f / foreground->GetWidth(),
        background->GetHeight() * 1.0f / foreground->GetHeight());
    if ((scale - 0.0) > THRESHOLD) {
        return;
    }
    auto destWidth = foreground->GetWidth() * scale;
    auto destHeight = foreground->GetHeight() * scale;
    auto dstOffsetX = static_cast<float>((background->GetWidth() - destWidth) * HALF);
    auto dstOffsetY = static_cast<float>((background->GetHeight() - destHeight) * HALF);
    RSRect rsSrcRect(0.0, 0.0, foreground->GetWidth(), foreground->GetHeight());
    RSRect rsDstRect(dstOffsetX, dstOffsetY, destWidth + dstOffsetX, destHeight + dstOffsetY);
    brush.SetBlendMode(RSBlendMode::SRC_ATOP);
    bitmapCanvas.AttachBrush(brush);
    image.BuildFromBitmap(*foreground);
    bitmapCanvas.DrawImageRect(
        image, rsSrcRect, rsDstRect, RSSamplingOptions(), RSSrcRectConstraint::FAST_SRC_RECT_CONSTRAINT);
    bitmapCanvas.DetachBrush();
}

std::shared_ptr<RSBitmap> PixelMapToBitMap(RefPtr<PixelMap>& pixelmap)
{
    if (!pixelmap) {
        return nullptr;
    }
    RSBitmap bitmap;
    auto data = pixelmap->GetPixels();
    RSColorType colorType = PixelFormatToColorType(pixelmap->GetPixelFormat());
    RSAlphaType alphaType = ConvertAlphaType(pixelmap->GetAlphaType());
    RSImageInfo imageInfo(pixelmap->GetWidth(), pixelmap->GetHeight(), colorType, alphaType);
    bitmap.Build(imageInfo);
    bitmap.SetPixels(const_cast<uint8_t*>(data));
    return std::make_shared<RSBitmap>(bitmap);
}

RefPtr<PixelMap> BitMapToPixelMap(const RSBitmap& bitmap, InitializationOptions& opts)
{
    auto data = bitmap.GetPixels();
    opts.size.SetWidth(static_cast<int32_t>(bitmap.GetWidth()));
    opts.size.SetHeight(static_cast<int32_t>(bitmap.GetHeight()));
    opts.editable = false;
    auto pixelmap = PixelMap::Create(opts);
    if (!pixelmap) {
        return pixelmap;
    }
    auto dstAddr = pixelmap->GetWritablePixels();
    auto byteCount = pixelmap->GetByteCount();
    if (memcpy_s(dstAddr, byteCount, data, byteCount) != 0) {
        return nullptr;
    }
    return pixelmap;
}

RefPtr<PixelMap> CompositeLayerAdaptive(
    RefPtr<PixelMap>& foreground, RefPtr<PixelMap>& background, RefPtr<PixelMap>& mask)
{
    if (!background) {
        return nullptr;
    }
    auto foreBitmap = PixelMapToBitMap(foreground);
    auto backBitmap = PixelMapToBitMap(background);
    auto maskBitmap = PixelMapToBitMap(mask);
    RSBrush brush;
    brush.SetAntiAlias(true);
    RSImageInfo imageInfo = CreateRSImageInfo(background, background->GetWidth(), background->GetHeight());
    RSBitmap tempCache;
    tempCache.Build(imageInfo);
    RSCanvas bitmapCanvas;
    bitmapCanvas.Bind(tempCache);
    brush.SetBlendMode(RSBlendMode::SRC);
    bitmapCanvas.AttachBrush(brush);
    DrawOntoCanvas(backBitmap, background->GetWidth(), background->GetHeight(), bitmapCanvas);
    bitmapCanvas.DetachBrush();
    RSRect dstRect(0.0, 0.0, static_cast<float>(background->GetWidth()), static_cast<float>(background->GetHeight()));
    RSImage image;

    if (maskBitmap) {
        RSRect srcRect(0.0, 0.0, static_cast<float>(mask->GetWidth()), static_cast<float>(mask->GetHeight()));
        image.BuildFromBitmap(*maskBitmap);
        brush.SetBlendMode(RSBlendMode::DST_IN);
        bitmapCanvas.AttachBrush(brush);
        bitmapCanvas.DrawImageRect(
            image, srcRect, dstRect, RSSamplingOptions(), RSSrcRectConstraint::FAST_SRC_RECT_CONSTRAINT);
        bitmapCanvas.DetachBrush();
    }
    if (foreBitmap) {
        BlendForeground(bitmapCanvas, brush, image, backBitmap, foreBitmap);
    }
    bitmapCanvas.ReadPixels(imageInfo, tempCache.GetPixels(), tempCache.GetRowBytes(), 0, 0);
    InitializationOptions opts;
    opts.alphaType = background->GetAlphaType();
    opts.pixelFormat = PixelFormat::BGRA_8888;
    auto pixelmap = BitMapToPixelMap(tempCache, opts);
    return pixelmap;
}

RefPtr<PixelMap> CompositeLayerNotAdaptive(
    RefPtr<PixelMap>& foreground, RefPtr<PixelMap>& background, RefPtr<PixelMap>& mask)
{
    auto foreBitmap = PixelMapToBitMap(foreground);
    auto backBitmap = PixelMapToBitMap(background);
    auto maskBitmap = PixelMapToBitMap(mask);
    RSBrush brush;
    brush.SetAntiAlias(true);
    RSImageInfo imageInfo = CreateRSImageInfo(background, SIDE, SIDE);
    RSBitmap tempCache;
    tempCache.Build(imageInfo);
    RSCanvas bitmapCanvas;
    bitmapCanvas.Bind(tempCache);
    if (background) {
        brush.SetBlendMode(RSBlendMode::SRC);
        bitmapCanvas.AttachBrush(brush);
        DrawOntoCanvas(backBitmap, SIDE, SIDE, bitmapCanvas);
        bitmapCanvas.DetachBrush();
    }
    if (mask) {
        brush.SetBlendMode(RSBlendMode::DST_IN);
        bitmapCanvas.AttachBrush(brush);
        DrawOntoCanvas(maskBitmap, SIDE, SIDE, bitmapCanvas);
        bitmapCanvas.DetachBrush();
    }
    if (foreground) {
        brush.SetBlendMode(RSBlendMode::SRC_ATOP);
        bitmapCanvas.AttachBrush(brush);
        DrawOntoCanvas(foreBitmap, SIDE, SIDE, bitmapCanvas);
        bitmapCanvas.DetachBrush();
    }
    bitmapCanvas.ReadPixels(imageInfo, tempCache.GetPixels(), tempCache.GetRowBytes(), 0, 0);
    InitializationOptions opts;
    if (background) {
        opts.alphaType = background->GetAlphaType();
    } else {
        opts.alphaType = AlphaType::IMAGE_ALPHA_TYPE_PREMUL;
    }
    opts.pixelFormat = PixelFormat::BGRA_8888;
    auto pixelmap = BitMapToPixelMap(tempCache, opts);
    return pixelmap;
}
} // namespace

RefPtr<PixelMap> LayeredDrawableDescriptor::GetPixelMap()
{
    if (composePixelMap_) {
        return composePixelMap_;
    }
    CreatePixelMap();
    return composePixelMap_;
}

void LayeredDrawableDescriptor::CreatePixelMap()
{
    auto foreground = GetForeground();
    auto background = GetBackground();
    auto mask = GetMask();
    if (foreground && foreground->GetWidth() == NOT_ADAPTIVE_SIZE && foreground->GetHeight() == NOT_ADAPTIVE_SIZE) {
        composePixelMap_ = CompositeLayerNotAdaptive(foreground, background, mask);
    } else {
        composePixelMap_ = CompositeLayerAdaptive(foreground, background, mask);
    }
}

RefPtr<PixelMap> LayeredDrawableDescriptor::GetForeground()
{
    if (foreground_) {
        return foreground_;
    }
    CreateForeground();
    return foreground_;
}

RefPtr<PixelMap> LayeredDrawableDescriptor::GetBackground()
{
    if (background_) {
        return background_;
    }
    CreateBackground();
    return background_;
}

RefPtr<PixelMap> LayeredDrawableDescriptor::GetMask()
{
    if (mask_) {
        return mask_;
    }
    CreateMask();
    return mask_;
}

void LayeredDrawableDescriptor::CreateForeground()
{
    if (foregroundData_.empty()) {
        return;
    }
    auto imageSource = ImageSource::Create(foregroundData_.data(), foregroundData_.size());
    if (!imageSource) {
        return;
    }
    DecodeOptions options;
    options.desiredFormat = PixelFormat::BGRA_8888;
    auto pixelmap = imageSource->CreatePixelMap(options);
    foreground_ = pixelmap;
}

void LayeredDrawableDescriptor::CreateBackground()
{
    if (backgroundData_.empty()) {
        return;
    }
    auto imageSource = ImageSource::Create(backgroundData_.data(), backgroundData_.size());
    if (!imageSource) {
        return;
    }
    DecodeOptions options;
    options.desiredFormat = PixelFormat::BGRA_8888;
    auto pixelmap = imageSource->CreatePixelMap(options);
    background_ = pixelmap;
}

void LayeredDrawableDescriptor::CreateMask()
{
    if (CreateMaskByPath()) {
        return;
    }
    CreateMaskByData();
}

bool LayeredDrawableDescriptor::CreateMaskByPath()
{
    if (maskPath_.empty()) {
        return false;
    }
    auto imageSource = ImageSource::Create(maskPath_);
    if (imageSource) {
        return false;
    }
    DecodeOptions options;
    options.desiredFormat = PixelFormat::BGRA_8888;
    auto pixelmap = imageSource->CreatePixelMap(options);
    mask_ = pixelmap;
    return true;
}

bool LayeredDrawableDescriptor::CreateMaskByData()
{
    if (maskData_.empty()) {
        return false;
    }
    auto imageSource = ImageSource::Create(maskData_.data(), maskData_.size());
    if (imageSource) {
        return false;
    }
    DecodeOptions options;
    options.desiredFormat = PixelFormat::BGRA_8888;
    auto pixelmap = imageSource->CreatePixelMap(options);
    mask_ = pixelmap;
    return true;
}

} // namespace OHOS::Ace