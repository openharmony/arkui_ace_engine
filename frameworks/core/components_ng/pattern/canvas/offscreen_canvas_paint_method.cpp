/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/canvas/offscreen_canvas_paint_method.h"

#ifndef ACE_UNITTEST
#include "include/utils/SkBase64.h"
#include "core/components/common/painter/rosen_decoration_painter.h"
#include "core/components/font/constants_converter.h"
#include "core/components/font/rosen_font_collection.h"
#endif

#include "base/i18n/localization.h"
#include "core/common/container.h"
#include "core/components_ng/pattern/canvas/custom_paint_util.h"

namespace OHOS::Ace::NG {
constexpr Dimension DEFAULT_FONT_SIZE = 14.0_px;
OffscreenCanvasPaintMethod::OffscreenCanvasPaintMethod(int32_t width, int32_t height)
{
    antiAlias_ = false;
    matrix_.Reset();
    width_ = width;
    height_ = height;
    lastLayoutSize_.SetWidth(static_cast<float>(width));
    lastLayoutSize_.SetHeight(static_cast<float>(height));
    InitBitmap();
    // The default value of the font size in canvas is 14px.
    SetFontSize(DEFAULT_FONT_SIZE);
    if (apiVersion_ >= static_cast<int32_t>(PlatformVersion::VERSION_EIGHTEEN)) {
        isPathChanged_ = false;
        isPath2dChanged_ = false;
    }
}

void OffscreenCanvasPaintMethod::InitBitmap()
{
    RSBitmapFormat bitmapFormat = { RSColorType::COLORTYPE_RGBA_8888, RSAlphaType::ALPHATYPE_UNPREMUL };
    bool ret = bitmap_.Build(width_, height_, bitmapFormat);
    if (!ret) {
        TAG_LOGE(AceLogTag::ACE_CANVAS, "The width and height exceed the limit size.");
        return;
    }
    bitmap_.ClearWithColor(RSColor::COLOR_TRANSPARENT);
    bitmapSize_ = bitmap_.ComputeByteSize();
    rsCanvas_ = std::make_unique<RSCanvas>();
    rsCanvas_->Bind(bitmap_);
}

RefPtr<PixelMap> OffscreenCanvasPaintMethod::TransferToImageBitmap()
{
#ifdef PIXEL_MAP_SUPPORTED
    OHOS::Media::InitializationOptions options;
    options.alphaType = OHOS::Media::AlphaType::IMAGE_ALPHA_TYPE_PREMUL;
    options.pixelFormat = OHOS::Media::PixelFormat::RGBA_8888;
    options.scaleMode = OHOS::Media::ScaleMode::CENTER_CROP;
    options.size.width = width_;
    options.size.height = height_;
    options.editable = true;
    auto pixelMap = Ace::PixelMap::Create(OHOS::Media::PixelMap::Create(options));
    CHECK_NULL_RETURN(pixelMap, nullptr);
    std::shared_ptr<Ace::ImageData> imageData = std::make_shared<Ace::ImageData>();
    imageData->pixelMap = pixelMap;
    imageData->dirtyX = 0.0f;
    imageData->dirtyY = 0.0f;
    imageData->dirtyWidth = width_;
    imageData->dirtyHeight = height_;
    GetImageData(imageData);
    return pixelMap;
#else
    return nullptr;
#endif
}

void OffscreenCanvasPaintMethod::Reset()
{
    matrix_.Reset();
    ResetStates();
    InitBitmap();
}

TextDirection OffscreenCanvasPaintMethod::GetSystemDirection()
{
    return AceApplicationInfo::GetInstance().IsRightToLeft() ? TextDirection::RTL : TextDirection::LTR;
}

void OffscreenCanvasPaintMethod::UpdateSize(int32_t width, int32_t height)
{
    width_ = width;
    height_ = height;
    lastLayoutSize_.SetWidth(static_cast<float>(width));
    lastLayoutSize_.SetHeight(static_cast<float>(height));
    Reset();
}

void OffscreenCanvasPaintMethod::DrawPixelMap(RefPtr<PixelMap> pixelMap, const Ace::CanvasImage& canvasImage)
{
#ifndef ACE_UNITTEST
    // get Image form pixelMap
    CHECK_NULL_VOID(pixelMap);
    auto rsBitmapFormat = Ace::ImageProvider::MakeRSBitmapFormatFromPixelMap(pixelMap);
    auto rsBitmap = std::make_shared<RSBitmap>();
    bool ret = rsBitmap->Build(pixelMap->GetWidth(), pixelMap->GetHeight(), rsBitmapFormat, pixelMap->GetRowStride());
    if (!ret) {
        TAG_LOGE(AceLogTag::ACE_CANVAS, "The width and height exceed the limit size.");
        return;
    }
    rsBitmap->SetPixels(const_cast<void*>(reinterpret_cast<const void*>(pixelMap->GetPixels())));

    // Step2: Create Image and draw it, using gpu or cpu
    auto image = std::make_shared<RSImage>();
    CHECK_NULL_VOID(image->BuildFromBitmap(*rsBitmap));
    DrawImageInternal(canvasImage, image);
#endif
}

std::unique_ptr<Ace::ImageData> OffscreenCanvasPaintMethod::GetImageData(
    double left, double top, double width, double height)
{
    double dirtyWidth = std::abs(width);
    double dirtyHeight = std::abs(height);
    double scaledLeft = left + std::min(width, 0.0);
    double scaledTop = top + std::min(height, 0.0);
    // copy the bitmap to tempCanvas
    RSBitmapFormat format = GetBitmapFormat();
    int32_t size = dirtyWidth * dirtyHeight;
    auto srcRect =
        RSRect(scaledLeft, scaledTop, dirtyWidth + scaledLeft, dirtyHeight + scaledTop);
    auto dstRect = RSRect(0.0, 0.0, dirtyWidth, dirtyHeight);
    RSBitmap tempCache;
    tempCache.Build(dirtyWidth, dirtyHeight, format);
    RSCanvas tempCanvas;
    tempCanvas.Bind(tempCache);
    RSImage rsImage;
    rsImage.BuildFromBitmap(bitmap_);
    tempCanvas.DrawImageRect(
        rsImage, srcRect, dstRect, RSSamplingOptions(), RSSrcRectConstraint::FAST_SRC_RECT_CONSTRAINT);
    // write color
    uint8_t* pixels = static_cast<uint8_t*>(tempCache.GetPixels());
    std::unique_ptr<Ace::ImageData> imageData = std::make_unique<Ace::ImageData>();
    imageData->dirtyWidth = dirtyWidth;
    imageData->dirtyHeight = dirtyHeight;
    // a pixel include 4 data blue, green, red, alpha
    for (int i = 0; i < size * 4; i += 4) {
        auto blue = pixels[i];
        auto green = pixels[i + 1];
        auto red = pixels[i + 2];
        auto alpha = pixels[i + 3];
        imageData->data.emplace_back(Color::FromARGB(alpha, red, green, blue).GetValue());
    }
    return imageData;
}

void OffscreenCanvasPaintMethod::GetImageData(const std::shared_ptr<Ace::ImageData>& imageData)
{
    int32_t dirtyWidth = std::abs(imageData->dirtyWidth);
    int32_t dirtyHeight = std::abs(imageData->dirtyHeight);
    double scaledLeft = imageData->dirtyX + std::min(imageData->dirtyWidth, 0);
    double scaledTop = imageData->dirtyY + std::min(imageData->dirtyHeight, 0);
    double dx = std::min(scaledLeft, 0.0);
    double dy = std::min(scaledTop, 0.0);
    // copy the bitmap to tempCanvas
    RSBitmap subBitmap;
    auto rect = RSRect(scaledLeft, scaledTop, dirtyWidth + scaledLeft, dirtyHeight + scaledTop);
    bool ret = bitmap_.ExtractSubset(subBitmap, rect);
    if (!ret) {
        return;
    }
    auto pixelMap = imageData->pixelMap;
    CHECK_NULL_VOID(pixelMap);
    auto* rawData = pixelMap->GetWritablePixels();
    CHECK_NULL_VOID(rawData);
    RSImageInfo imageInfo =
        RSImageInfo(dirtyWidth, dirtyHeight, RSColorType::COLORTYPE_RGBA_8888, RSAlphaType::ALPHATYPE_PREMUL);
    subBitmap.ReadPixels(imageInfo, rawData, dirtyWidth * imageInfo.GetBytesPerPixel(), dx, dy);
}

std::string OffscreenCanvasPaintMethod::ToDataURL(const std::string& type, const double quality)
{
#ifndef ACE_UNITTEST
    std::string mimeType = GetMimeType(type);
    // Quality needs to be between 0.0 and 1.0 for MimeType jpeg and webp
    double qua = GetQuality(mimeType, quality);
    auto imageInfo = SkImageInfo::Make(width_, height_, SkColorType::kBGRA_8888_SkColorType,
        (mimeType == IMAGE_JPEG) ? SkAlphaType::kOpaque_SkAlphaType : SkAlphaType::kUnpremul_SkAlphaType);
    RSBitmap tempCache;
    tempCache.Build(width_, height_,
        { RSColorType::COLORTYPE_BGRA_8888,
            (mimeType == IMAGE_JPEG) ? RSAlphaType::ALPHATYPE_OPAQUE : RSAlphaType::ALPHATYPE_UNPREMUL });
    RSCanvas tempCanvas;
    tempCanvas.Bind(tempCache);
    tempCanvas.Clear(RSColor::COLOR_TRANSPARENT);
    tempCanvas.Scale(1.0, 1.0);
    tempCanvas.DrawBitmap(bitmap_, 0.0f, 0.0f);
    RSPixmap rsSrc;
    bool success = tempCache.PeekPixels(rsSrc);
    CHECK_NULL_RETURN(success, UNSUPPORTED);
    SkPixmap src { imageInfo, rsSrc.GetAddr(), rsSrc.GetRowBytes() };
    SkDynamicMemoryWStream dst;
    success = EncodeImage(mimeType, qua, src, dst);
    CHECK_NULL_RETURN(success, UNSUPPORTED);
    auto result = dst.detachAsData();
    CHECK_NULL_RETURN(result, UNSUPPORTED);
    size_t len = SkBase64::Encode(result->data(), result->size(), nullptr);
    if (len > MAX_LENGTH) {
        return UNSUPPORTED;
    }
    SkString info(len);
    SkBase64::Encode(result->data(), result->size(), info.writable_str());
    return std::string(URL_PREFIX).append(mimeType).append(URL_SYMBOL).append(info.c_str());
#else
    return UNSUPPORTED;
#endif
}

TransformParam OffscreenCanvasPaintMethod::GetTransform() const
{
    TransformParam param;
    CHECK_NULL_RETURN(rsCanvas_, param);
    RSMatrix matrix = rsCanvas_->GetTotalMatrix();
    param.scaleX = matrix.Get(RSMatrix::SCALE_X);
    param.scaleY = matrix.Get(RSMatrix::SCALE_Y);
    param.skewX = matrix.Get(RSMatrix::SKEW_X);
    param.skewY = matrix.Get(RSMatrix::SKEW_Y);
    param.translateX = matrix.Get(RSMatrix::TRANS_X);
    param.translateY = matrix.Get(RSMatrix::TRANS_Y);
    return param;
}

LineDashParam OffscreenCanvasPaintMethod::GetLineDash() const
{
    return state_.strokeState.GetLineDash();
}

#ifndef ACE_UNITTEST
void OffscreenCanvasPaintMethod::ConvertTxtStyle(const TextStyle& textStyle, Rosen::TextStyle& txtStyle)
{
    Constants::ConvertTxtStyle(textStyle, txtStyle);
}
#endif
} // namespace OHOS::Ace::NG
