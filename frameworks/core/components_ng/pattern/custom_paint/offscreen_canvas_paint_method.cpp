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

#include "core/components_ng/pattern/custom_paint/offscreen_canvas_paint_method.h"

#ifndef USE_GRAPHIC_TEXT_GINE
#include "txt/paragraph_builder.h"
#include "txt/paragraph_style.h"
#else
#include "rosen_text/typography_create.h"
#include "rosen_text/typography_style.h"
#endif
#include "include/core/SkMaskFilter.h"
#include "core/components/common/properties/paint_state.h"
#ifndef NEW_SKIA
#include "include/effects/SkBlurImageFilter.h"
#else
#include "include/core/SkColorFilter.h"
#include "include/effects/SkImageFilters.h"
#endif
#include "include/encode/SkJpegEncoder.h"
#include "include/encode/SkPngEncoder.h"
#include "include/encode/SkWebpEncoder.h"
#include "include/utils/SkBase64.h"

#include "base/geometry/ng/offset_t.h"
#include "base/i18n/localization.h"
#include "base/image/pixel_map.h"
#include "base/utils/utils.h"
#ifndef NEW_SKIA
#include "core/components/common/painter/flutter_decoration_painter.h"
#endif
#include "core/components/common/painter/rosen_decoration_painter.h"
#include "core/components/font/constants_converter.h"
#ifndef NEW_SKIA
#include "core/components/font/flutter_font_collection.h"
#endif
#include "core/components/font/rosen_font_collection.h"

namespace OHOS::Ace::NG {
namespace {
constexpr double HANGING_PERCENT = 0.8;
constexpr double DEFAULT_QUALITY = 0.92;
constexpr int32_t MAX_LENGTH = 2048 * 2048;
constexpr int32_t PLATFORM_VERSION_TEN = 10;
const std::string UNSUPPORTED = "data:image/png";
const std::string URL_PREFIX = "data:";
const std::string URL_SYMBOL = ";base64,";
const std::string IMAGE_PNG = "image/png";
const std::string IMAGE_JPEG = "image/jpeg";
const std::string IMAGE_WEBP = "image/webp";
// If args is empty or invalid format, use default: image/png
std::string GetMimeType(const std::string& args)
{
    std::string type = args;
    for (size_t i = 0; i < type.size(); ++i) {
        type[i] = static_cast<uint8_t>(tolower(type[i]));
    }
    return type;
}

// Quality need between 0.0 and 1.0 for MimeType jpeg and webp
double GetQuality(const std::string& args, const double quality)
{
    std::string type = args;
    auto mimeType = GetMimeType(type);
    if (mimeType != IMAGE_JPEG && mimeType != IMAGE_WEBP) {
        return DEFAULT_QUALITY;
    }
    if (quality < 0.0 || quality > 1.0) {
        return DEFAULT_QUALITY;
    }
    return quality;
}
} // namespace

OffscreenCanvasPaintMethod::OffscreenCanvasPaintMethod(
    const WeakPtr<PipelineBase> context, int32_t width, int32_t height)
{
    antiAlias_ = true;
    context_ = context;
    width_ = width;
    height_ = height;
    lastLayoutSize_.SetWidth(static_cast<float>(width));
    lastLayoutSize_.SetHeight(static_cast<float>(height));
    matrix_.reset();

#ifndef USE_ROSEN_DRAWING
    auto imageInfo =
        SkImageInfo::Make(width, height, SkColorType::kRGBA_8888_SkColorType, SkAlphaType::kUnpremul_SkAlphaType);
    if (!canvasCache_.tryAllocPixels(imageInfo)) {
        LOGE("The OffScreenCanvas fail to constructor due to the width and height being too large");
        isSucceed_ = false;
        return;
    }
    canvasCache_.eraseColor(SK_ColorTRANSPARENT);
    skCanvas_ = std::make_unique<SkCanvas>(canvasCache_);
#else
    RSBitmapFormat bitmapFormat = { RSColorType::COLORTYPE_RGBA_8888, RSAlphaType::ALPHATYPE_UNPREMUL };
    canvasCache_.Build(width, height, bitmapFormat);
    canvasCache_.ClearWithColor(RSColor::COLOR_TRANSPARENT);
    rsCanvas_ = std::make_unique<RSCanvas>();
    rsCanvas_->Bind(canvasCache_);
#endif

    imageShadow_ = std::make_unique<Shadow>();
    InitImageCallbacks();
}

void OffscreenCanvasPaintMethod::ImageObjReady(const RefPtr<Ace::ImageObject>& imageObj)
{
    if (imageObj->IsSvg()) {
        skiaDom_ = AceType::DynamicCast<SvgSkiaImageObject>(imageObj)->GetSkiaDom();
        currentSource_ = loadingSource_;
    } else {
        LOGE("image is not svg");
    }
}

void OffscreenCanvasPaintMethod::ImageObjFailed()
{
    loadingSource_.SetSrc("");
    currentSource_.SetSrc("");
    skiaDom_ = nullptr;
}

void OffscreenCanvasPaintMethod::DrawImage(
    PaintWrapper* paintWrapper, const Ace::CanvasImage& canvasImage, double width, double height)
{
    std::string::size_type tmp = canvasImage.src.find(".svg");
    if (tmp != std::string::npos) {
        DrawSvgImage(paintWrapper, canvasImage);
        return;
    }

#ifndef USE_ROSEN_DRAWING
    auto image = GreatOrEqual(width, 0) && GreatOrEqual(height, 0)
                     ? Ace::ImageProvider::GetSkImage(canvasImage.src, context_, Size(width, height))
                     : Ace::ImageProvider::GetSkImage(canvasImage.src, context_);
    CHECK_NULL_VOID(image);

    const auto skCanvas = skCanvas_.get();
    SkPaint compositeOperationpPaint;
    InitPaintBlend(compositeOperationpPaint);
    if (globalState_.GetType() != CompositeOperation::SOURCE_OVER) {
        skCanvas_->saveLayer(
            SkRect::MakeXYWH(0, 0, lastLayoutSize_.Width(), lastLayoutSize_.Height()), &compositeOperationpPaint);
    }

#ifndef NEW_SKIA
    InitImagePaint(imagePaint_);
#else
    InitImagePaint(imagePaint_, sampleOptions_);
#endif

    if (globalState_.HasGlobalAlpha()) {
        imagePaint_.setAlphaf(globalState_.GetAlpha());
    }

    if (HasShadow()) {
        SkRect skRect = SkRect::MakeXYWH(canvasImage.dx, canvasImage.dy, canvasImage.dWidth, canvasImage.dHeight);
        SkPath path;
        path.addRect(skRect);
        RosenDecorationPainter::PaintShadow(path, shadow_, skCanvas, &imagePaint_);
    }

    switch (canvasImage.flag) {
        case 0:
            skCanvas->drawImage(image, canvasImage.dx, canvasImage.dy);
            break;
        case 1: {
            SkRect rect = SkRect::MakeXYWH(canvasImage.dx, canvasImage.dy, canvasImage.dWidth, canvasImage.dHeight);
#ifndef NEW_SKIA
            skCanvas->drawImageRect(image, rect, &imagePaint_);
#else
            skCanvas->drawImageRect(image, rect, sampleOptions_, &imagePaint_);
#endif
            break;
        }
        case 2: {
            SkRect dstRect =
                SkRect::MakeXYWH(canvasImage.dx, canvasImage.dy, canvasImage.dWidth, canvasImage.dHeight);
            SkRect srcRect =
                SkRect::MakeXYWH(canvasImage.sx, canvasImage.sy, canvasImage.sWidth, canvasImage.sHeight);
#ifndef NEW_SKIA
            skCanvas->drawImageRect(image, srcRect, dstRect, &imagePaint_);
#else
            skCanvas->drawImageRect(
                image, srcRect, dstRect, sampleOptions_, &imagePaint_, SkCanvas::kFast_SrcRectConstraint);
#endif
            break;
        }
        default:
            break;
    }

    if (globalState_.GetType() != CompositeOperation::SOURCE_OVER) {
        skCanvas_->restore();
    }
#else
    auto image = GreatOrEqual(width, 0) && GreatOrEqual(height, 0)
                        ? Ace::ImageProvider::GetDrawingImage(canvasImage.src, context_, Size(width, height))
                        : Ace::ImageProvider::GetDrawingImage(canvasImage.src, context_);
    CHECK_NULL_VOID(image);

    const auto rsCanvas = rsCanvas_.get();
    RSBrush compositeOperationpBrush;
    InitPaintBlend(compositeOperationpBrush);
    if (globalState_.GetType() != CompositeOperation::SOURCE_OVER) {
        auto rect = RSRect(0, 0, lastLayoutSize_.Width(), lastLayoutSize_.Height());
        RSSaveLayerOps slo(&rect, &compositeOperationpBrush);
        rsCanvas_->SaveLayer(slo);
    }

    InitImagePaint(nullptr, &imageBrush_, sampleOptions_);
    if (HasImageShadow()) {
        RSRect rsRect = RSRect(canvasImage.dx, canvasImage.dy,
            canvasImage.dWidth + canvasImage.dx, canvasImage.dHeight + canvasImage.dy);
        RSPath path;
        path.AddRect(rsRect);
        RosenDecorationPainter::PaintShadow(path, *imageShadow_, rsCanvas);
    }

    if (globalState_.HasGlobalAlpha()) {
        imageBrush_.SetAlphaF(globalState_.GetAlpha());
    }
    switch (canvasImage.flag) {
        case 0:
            rsCanvas->DrawImage(*image, canvasImage.dx, canvasImage.dy, RSSamplingOptions());
            break;
        case 1: {
            RSRect rect = RSRect(canvasImage.dx, canvasImage.dy,
                canvasImage.dWidth + canvasImage.dx, canvasImage.dHeight + canvasImage.dy);
            rsCanvas->AttachBrush(imageBrush_);
            rsCanvas->DrawImageRect(*image, rect, sampleOptions_);
            rsCanvas->DetachBrush();
            break;
        }
        case 2: {
            RSRect dstRect = RSRect(canvasImage.dx, canvasImage.dy,
                canvasImage.dWidth + canvasImage.dx, canvasImage.dHeight + canvasImage.dy);
            RSRect srcRect = RSRect(canvasImage.sx, canvasImage.sy,
                canvasImage.sWidth + canvasImage.sx, canvasImage.sHeight + canvasImage.sy);
            rsCanvas->AttachBrush(imageBrush_);
            rsCanvas->DrawImageRect(*image, srcRect, dstRect, sampleOptions_);
            rsCanvas->DetachBrush();
            break;
        }
        default:
            break;
    }
    if (globalState_.GetType() != CompositeOperation::SOURCE_OVER) {
        rsCanvas_->Restore();
    }
#endif
}

void OffscreenCanvasPaintMethod::DrawPixelMap(RefPtr<PixelMap> pixelMap, const Ace::CanvasImage& canvasImage)
{
#ifndef USE_ROSEN_DRAWING
    // get skImage form pixelMap
    auto imageInfo = Ace::ImageProvider::MakeSkImageInfoFromPixelMap(pixelMap);
    SkPixmap imagePixmap(imageInfo, reinterpret_cast<const void*>(pixelMap->GetPixels()), pixelMap->GetRowBytes());

    // Step2: Create SkImage and draw it, using gpu or cpu
    sk_sp<SkImage> image;

    image = SkImage::MakeFromRaster(imagePixmap, &PixelMap::ReleaseProc, PixelMap::GetReleaseContext(pixelMap));
    CHECK_NULL_VOID(image);

    const auto skCanvas = skCanvas_.get();
    SkPaint compositeOperationpPaint;
    InitPaintBlend(compositeOperationpPaint);
    if (globalState_.GetType() != CompositeOperation::SOURCE_OVER) {
        skCanvas_->saveLayer(
            SkRect::MakeXYWH(0, 0, lastLayoutSize_.Width(), lastLayoutSize_.Height()), &compositeOperationpPaint);
    }

#ifndef NEW_SKIA
    InitImagePaint(imagePaint_);
#else
    InitImagePaint(imagePaint_, sampleOptions_);

    if (globalState_.HasGlobalAlpha()) {
        imagePaint_.setAlphaf(globalState_.GetAlpha());
    }

    if (HasShadow()) {
        SkRect skRect = SkRect::MakeXYWH(canvasImage.dx, canvasImage.dy, canvasImage.dWidth, canvasImage.dHeight);
        SkPath path;
        path.addRect(skRect);
        RosenDecorationPainter::PaintShadow(path, shadow_, skCanvas, &imagePaint_);
    }
#endif
    switch (canvasImage.flag) {
        case 0:
            skCanvas->drawImage(image, canvasImage.dx, canvasImage.dy);
            break;
        case 1: {
            SkRect rect = SkRect::MakeXYWH(canvasImage.dx, canvasImage.dy, canvasImage.dWidth, canvasImage.dHeight);
#ifndef NEW_SKIA
            skCanvas->drawImageRect(image, rect, &imagePaint_);
#else
            skCanvas->drawImageRect(image, rect, sampleOptions_, &imagePaint_);
#endif
            break;
        }
        case 2: {
            SkRect dstRect =
                SkRect::MakeXYWH(canvasImage.dx, canvasImage.dy, canvasImage.dWidth, canvasImage.dHeight);
            SkRect srcRect =
                SkRect::MakeXYWH(canvasImage.sx, canvasImage.sy, canvasImage.sWidth, canvasImage.sHeight);
#ifndef NEW_SKIA
            skCanvas->drawImageRect(image, srcRect, dstRect, &imagePaint_);
#else
            skCanvas->drawImageRect(
                image, srcRect, dstRect, sampleOptions_, &imagePaint_, SkCanvas::kFast_SrcRectConstraint);
#endif
            break;
        }
        default:
            break;
    }

    if (globalState_.GetType() != CompositeOperation::SOURCE_OVER) {
        skCanvas_->restore();
    }
#else
    // get Image form pixelMap
    auto rsBitmapFormat = Ace::ImageProvider::MakeRSBitmapFormatFromPixelMap(pixelMap);
    auto rsBitmap = std::make_shared<RSBitmap>();
    rsBitmap->Build(pixelMap->GetWidth(), pixelMap->GetHeight(), rsBitmapFormat);
    rsBitmap->SetPixels(const_cast<void*>(reinterpret_cast<const void*>(pixelMap->GetPixels())));

    // Step2: Create Image and draw it, using gpu or cpu
    auto image = std::make_shared<RSImage>();
    CHECK_NULL_VOID(image->BuildFromBitmap(*rsBitmap));

    const auto rsCanvas = rsCanvas_.get();
    RSBrush compositeOperationpBrush;
    InitPaintBlend(compositeOperationpBrush);
    if (globalState_.GetType() != CompositeOperation::SOURCE_OVER) {
        auto rect = RSRect(0, 0, lastLayoutSize_.Width(), lastLayoutSize_.Height());
        RSSaveLayerOps slo(&rect, &compositeOperationpBrush);
        rsCanvas_->SaveLayer(slo);
    }

    InitImagePaint(nullptr, &imageBrush_, sampleOptions_);
    switch (canvasImage.flag) {
        case 0:
            rsCanvas->DrawImage(*image, canvasImage.dx, canvasImage.dy, RSSamplingOptions());
            break;
        case 1: {
            RSRect rect = RSRect(canvasImage.dx, canvasImage.dy,
                canvasImage.dWidth + canvasImage.dx, canvasImage.dHeight + canvasImage.dy);
            rsCanvas->AttachBrush(imageBrush_);
            rsCanvas->DrawImageRect(*image, rect, sampleOptions_);
            rsCanvas->DetachBrush();
            break;
        }
        case 2: {
            RSRect dstRect = RSRect(canvasImage.dx, canvasImage.dy,
                canvasImage.dWidth + canvasImage.dx, canvasImage.dHeight + canvasImage.dy);
            RSRect srcRect = RSRect(canvasImage.sx, canvasImage.sy,
                canvasImage.sWidth + canvasImage.sx, canvasImage.sHeight + canvasImage.sy);
            rsCanvas->AttachBrush(imageBrush_);
            rsCanvas->DrawImageRect(
                *image, srcRect, dstRect, sampleOptions_, RSSrcRectConstraint::FAST_SRC_RECT_CONSTRAINT);
            rsCanvas->DetachBrush();
            break;
        }
        default:
            break;
    }
    if (globalState_.GetType() != CompositeOperation::SOURCE_OVER) {
        rsCanvas_->Restore();
    }
#endif
}

std::unique_ptr<Ace::ImageData> OffscreenCanvasPaintMethod::GetImageData(
    double left, double top, double width, double height)
{
    double viewScale = 1.0;
    auto context = context_.Upgrade();
    CHECK_NULL_RETURN(context, std::unique_ptr<Ace::ImageData>());
    viewScale = context->GetViewScale();
    double dirtyWidth = std::abs(width);
    double dirtyHeight = std::abs(height);
    double scaledLeft = left * viewScale;
    double scaledTop = top * viewScale;
    if (Negative(width)) {
        scaledLeft += width * viewScale;
    }
    if (Negative(height)) {
        scaledTop += height * viewScale;
    }
    // copy the bitmap to tempCanvas
#ifndef USE_ROSEN_DRAWING
    auto imageInfo =
        SkImageInfo::Make(dirtyWidth, dirtyHeight,
        SkColorType::kBGRA_8888_SkColorType, SkAlphaType::kOpaque_SkAlphaType);

    int32_t size = dirtyWidth * dirtyHeight;
    auto srcRect = SkRect::MakeXYWH(scaledLeft, scaledTop, dirtyWidth * viewScale, dirtyHeight * viewScale);
    auto dstRect = SkRect::MakeXYWH(0.0, 0.0, dirtyWidth, dirtyHeight);
    SkBitmap tempCache;
    tempCache.allocPixels(imageInfo);
    SkCanvas tempCanvas(tempCache);
#if defined(USE_SYSTEM_SKIA_S) || defined (NEW_SKIA)
    tempCanvas.drawImageRect(
        canvasCache_.asImage(), srcRect, dstRect, SkSamplingOptions(), nullptr, SkCanvas::kFast_SrcRectConstraint);
#else
    tempCanvas.drawBitmapRect(canvasCache_, srcRect, dstRect, nullptr);
#endif
    // write color
    std::unique_ptr<uint8_t[]> pixels = std::make_unique<uint8_t[]>(size * 4);
    tempCanvas.readPixels(imageInfo, pixels.get(), dirtyWidth * imageInfo.bytesPerPixel(), 0, 0);
#else
    RSBitmapFormat format { RSColorType::COLORTYPE_BGRA_8888, RSAlphaType::ALPHATYPE_OPAQUE };
    int32_t size = dirtyWidth * dirtyHeight;
    auto srcRect = RSRect(scaledLeft, scaledTop,
        dirtyWidth * viewScale + scaledLeft, dirtyHeight * viewScale + scaledTop);
    auto dstRect = RSRect(0.0, 0.0, dirtyWidth, dirtyHeight);
    RSBitmap tempCache;
    tempCache.Build(width, height, format);
    RSCanvas tempCanvas;
    tempCanvas.Bind(tempCache);
    RSImage rsImage;
    rsImage.BuildFromBitmap(canvasCache_);
    tempCanvas.DrawImageRect(
        rsImage, srcRect, dstRect, RSSamplingOptions(), RSSrcRectConstraint::FAST_SRC_RECT_CONSTRAINT);
    // write color
    uint8_t* pixels = static_cast<uint8_t*>(tempCache.GetPixels());
#endif
    std::unique_ptr<Ace::ImageData> imageData = std::make_unique<Ace::ImageData>();
    imageData->dirtyWidth = dirtyWidth;
    imageData->dirtyHeight = dirtyHeight;
    // a pixel include 4 data blue, green, red, alpha
    for (int i = 0; i < size * 4; i += 4) {
        auto blue = pixels[i];
        auto green = pixels[i + 1];
        auto red = pixels[i + 2];
        auto alpha = pixels[i + 3];
        imageData->data.emplace_back(Color::FromARGB(alpha, red, green, blue));
    }
    return imageData;
}

void OffscreenCanvasPaintMethod::FillText(
    const std::string& text, double x, double y, std::optional<double> maxWidth, const PaintState& state)
{
    if (!UpdateOffParagraph(text, false, state, HasShadow())) {
        return;
    }
    PaintText(text, x, y, maxWidth, false, HasShadow());
}

void OffscreenCanvasPaintMethod::StrokeText(
    const std::string& text, double x, double y, std::optional<double> maxWidth, const PaintState& state)
{
    if (HasShadow()) {
        if (!UpdateOffParagraph(text, true, state, true)) {
            return;
        }
        PaintText(text, x, y, maxWidth, true, true);
    }

    if (!UpdateOffParagraph(text, true, state)) {
        return;
    }
    PaintText(text, x, y, maxWidth, true);
}

double OffscreenCanvasPaintMethod::MeasureText(const std::string& text, const PaintState& state)
{
    using namespace Constants;
#ifndef USE_GRAPHIC_TEXT_GINE
    txt::ParagraphStyle style;
    style.text_align = ConvertTxtTextAlign(state.GetTextAlign());
    style.text_direction = ConvertTxtTextDirection(state.GetOffTextDirection());
#else
    Rosen::TypographyStyle style;
    style.textAlign = ConvertTxtTextAlign(state.GetTextAlign());
    style.textDirection = ConvertTxtTextDirection(state.GetOffTextDirection());
#endif
    auto fontCollection = RosenFontCollection::GetInstance().GetFontCollection();
    CHECK_NULL_RETURN(fontCollection, 0.0);
#ifndef USE_GRAPHIC_TEXT_GINE
    std::unique_ptr<txt::ParagraphBuilder> builder = txt::ParagraphBuilder::CreateTxtBuilder(style, fontCollection);
    txt::TextStyle txtStyle;
#else
    std::unique_ptr<Rosen::TypographyCreate> builder = Rosen::TypographyCreate::Create(style, fontCollection);
    Rosen::TextStyle txtStyle;
#endif
    ConvertTxtStyle(state.GetTextStyle(), context_, txtStyle);
#ifndef USE_GRAPHIC_TEXT_GINE
    txtStyle.font_size = state.GetTextStyle().GetFontSize().Value();
#else
    txtStyle.fontSize = state.GetTextStyle().GetFontSize().Value();
#endif
    builder->PushStyle(txtStyle);
#ifndef USE_GRAPHIC_TEXT_GINE
    builder->AddText(StringUtils::Str8ToStr16(text));
    auto paragraph = builder->Build();
#else
    builder->AppendText(StringUtils::Str8ToStr16(text));
    auto paragraph = builder->CreateTypography();
#endif
    paragraph->Layout(Size::INFINITE_SIZE);
    return paragraph->GetMaxIntrinsicWidth();
}

double OffscreenCanvasPaintMethod::MeasureTextHeight(const std::string& text, const PaintState& state)
{
    using namespace Constants;
#ifndef USE_GRAPHIC_TEXT_GINE
    txt::ParagraphStyle style;
    style.text_align = ConvertTxtTextAlign(state.GetTextAlign());
    style.text_direction = ConvertTxtTextDirection(state.GetOffTextDirection());
#else
    Rosen::TypographyStyle style;
    style.textAlign = ConvertTxtTextAlign(state.GetTextAlign());
    style.textDirection = ConvertTxtTextDirection(state.GetOffTextDirection());
#endif
    auto fontCollection = RosenFontCollection::GetInstance().GetFontCollection();
    CHECK_NULL_RETURN(fontCollection, 0.0);
#ifndef USE_GRAPHIC_TEXT_GINE
    std::unique_ptr<txt::ParagraphBuilder> builder = txt::ParagraphBuilder::CreateTxtBuilder(style, fontCollection);
    txt::TextStyle txtStyle;
#else
    std::unique_ptr<Rosen::TypographyCreate> builder = Rosen::TypographyCreate::Create(style, fontCollection);
    Rosen::TextStyle txtStyle;
#endif
    ConvertTxtStyle(state.GetTextStyle(), context_, txtStyle);
#ifndef USE_GRAPHIC_TEXT_GINE
    txtStyle.font_size = state.GetTextStyle().GetFontSize().Value();
#else
    txtStyle.fontSize = state.GetTextStyle().GetFontSize().Value();
#endif
    builder->PushStyle(txtStyle);
#ifndef USE_GRAPHIC_TEXT_GINE
    builder->AddText(StringUtils::Str8ToStr16(text));
    auto paragraph = builder->Build();
#else
    builder->AppendText(StringUtils::Str8ToStr16(text));
    auto paragraph = builder->CreateTypography();
#endif
    paragraph->Layout(Size::INFINITE_SIZE);
    return paragraph->GetHeight();
}

TextMetrics OffscreenCanvasPaintMethod::MeasureTextMetrics(const std::string& text, const PaintState& state)
{
    using namespace Constants;
    TextMetrics textMetrics = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
#ifndef USE_GRAPHIC_TEXT_GINE
    txt::ParagraphStyle style;
    style.text_align = ConvertTxtTextAlign(state.GetTextAlign());
    style.text_direction = ConvertTxtTextDirection(state.GetOffTextDirection());
#else
    Rosen::TypographyStyle style;
    style.textAlign = ConvertTxtTextAlign(state.GetTextAlign());
    style.textDirection = ConvertTxtTextDirection(state.GetOffTextDirection());
#endif
    auto fontCollection = RosenFontCollection::GetInstance().GetFontCollection();
    CHECK_NULL_RETURN(fontCollection, textMetrics);
#ifndef USE_GRAPHIC_TEXT_GINE
    std::unique_ptr<txt::ParagraphBuilder> builder = txt::ParagraphBuilder::CreateTxtBuilder(style, fontCollection);
    txt::TextStyle txtStyle;
#else
    std::unique_ptr<Rosen::TypographyCreate> builder = Rosen::TypographyCreate::Create(style, fontCollection);
    Rosen::TextStyle txtStyle;
#endif
    ConvertTxtStyle(state.GetTextStyle(), context_, txtStyle);
#ifndef USE_GRAPHIC_TEXT_GINE
    txtStyle.font_size = state.GetTextStyle().GetFontSize().Value();
#else
    txtStyle.fontSize = state.GetTextStyle().GetFontSize().Value();
#endif
    builder->PushStyle(txtStyle);
#ifndef USE_GRAPHIC_TEXT_GINE
    builder->AddText(StringUtils::Str8ToStr16(text));
    auto paragraph = builder->Build();
#else
    builder->AppendText(StringUtils::Str8ToStr16(text));
    auto paragraph = builder->CreateTypography();
#endif
    paragraph->Layout(Size::INFINITE_SIZE);

    auto textAlign = state.GetTextAlign();
    auto textBaseLine = state.GetTextStyle().GetTextBaseline();
    textMetrics.width = paragraph->GetMaxIntrinsicWidth();
    textMetrics.height = paragraph->GetHeight();
    textMetrics.actualBoundingBoxLeft = -GetAlignOffset(textAlign, paragraph);
    textMetrics.actualBoundingBoxRight = textMetrics.width - textMetrics.actualBoundingBoxLeft;
    textMetrics.actualBoundingBoxAscent = -GetBaselineOffset(textBaseLine, paragraph);
    textMetrics.actualBoundingBoxDescent = textMetrics.height - textMetrics.actualBoundingBoxAscent;
    return textMetrics;
}

void OffscreenCanvasPaintMethod::PaintText(
    const std::string& text, double x, double y, std::optional<double> maxWidth, bool isStroke, bool hasShadow)
{
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    if (pipelineContext->GetMinPlatformVersion() >= PLATFORM_VERSION_TEN) {
        paragraph_->Layout(FLT_MAX);
    } else {
        paragraph_->Layout(width_);
    }
    if (width_ > paragraph_->GetMaxIntrinsicWidth()) {
        paragraph_->Layout(std::ceil(paragraph_->GetMaxIntrinsicWidth()));
    }
    auto align = isStroke ? strokeState_.GetTextAlign() : fillState_.GetTextAlign();
#ifndef USE_ROSEN_DRAWING
    double dx = x + GetAlignOffset(align, paragraph_);
    auto baseline =
        isStroke ? strokeState_.GetTextStyle().GetTextBaseline() : fillState_.GetTextStyle().GetTextBaseline();
    double dy = y + GetBaselineOffset(baseline, paragraph_);

    std::optional<double> scale = CalcTextScale(paragraph_->GetMaxIntrinsicWidth(), maxWidth);
    if (hasShadow) {
        skCanvas_->save();
        auto shadowOffsetX = shadow_.GetOffset().GetX();
        auto shadowOffsetY = shadow_.GetOffset().GetY();
        if (scale.has_value()) {
            if (!NearZero(scale.value())) {
                dx /= scale.value();
                shadowOffsetX /= scale.value();
            }
            skCanvas_->scale(scale.value(), 1.0);
        }
        paragraph_->Paint(skCanvas_.get(), dx + shadowOffsetX, dy + shadowOffsetY);
        skCanvas_->restore();
        return;
    }
#else
    double dx = x + GetAlignOffset(align, paragraph_);

    std::optional<double> scale = CalcTextScale(paragraph_->GetMaxIntrinsicWidth(), maxWidth);
    if (hasShadow) {
        rsCanvas_->Save();
        auto shadowOffsetX = shadow_.GetOffset().GetX();
        if (scale.has_value()) {
            if (!NearZero(scale.value())) {
                dx /= scale.value();
                shadowOffsetX /= scale.value();
            }
            rsCanvas_->Scale(scale.value(), 1.0);
        }
        LOGE("Drawing is not supported");
        rsCanvas_->Restore();
        return;
    }
#endif
    if (scale.has_value()) {
        if (!NearZero(scale.value())) {
            dx /= scale.value();
        }
#ifndef USE_ROSEN_DRAWING
        skCanvas_->save();
        skCanvas_->scale(scale.value(), 1.0);
        paragraph_->Paint(skCanvas_.get(), dx, dy);
        skCanvas_->restore();
    } else {
        paragraph_->Paint(skCanvas_.get(), dx, dy);
    }
#else
        rsCanvas_->Save();
        rsCanvas_->Scale(scale.value(), 1.0);
        LOGE("Drawing is not supported");
        rsCanvas_->Restore();
    } else {
        LOGE("Drawing is not supported");
    }
#endif
}

#ifndef USE_GRAPHIC_TEXT_GINE
double OffscreenCanvasPaintMethod::GetBaselineOffset(TextBaseline baseline, std::unique_ptr<txt::Paragraph>& paragraph)
#else
double OffscreenCanvasPaintMethod::GetBaselineOffset(TextBaseline baseline, std::unique_ptr<OHOS::Rosen::Typography>& paragraph)
#endif
{
    double y = 0.0;
    switch (baseline) {
        case TextBaseline::ALPHABETIC:
            y = -paragraph->GetAlphabeticBaseline();
            break;
        case TextBaseline::IDEOGRAPHIC:
            y = -paragraph->GetIdeographicBaseline();
            break;
        case TextBaseline::BOTTOM:
            y = -paragraph->GetHeight();
            break;
        case TextBaseline::TOP:
            y = 0.0;
            break;
        case TextBaseline::MIDDLE:
            y = -paragraph->GetHeight() / 2;
            break;
        case TextBaseline::HANGING:
            y = -HANGING_PERCENT * (paragraph->GetHeight() - paragraph->GetAlphabeticBaseline());
            break;
        default:
            y = -paragraph->GetAlphabeticBaseline();
            break;
    }
    return y;
}

#ifndef USE_GRAPHIC_TEXT_GINE
bool OffscreenCanvasPaintMethod::UpdateOffParagraph(const std::string& text, bool isStroke, const PaintState& state, bool hasShadow)
#else
bool OffscreenCanvasPaintMethod::UpdateOffParagraph(const std::string& text, bool isStroke,
    const PaintState& state, bool hasShadow)
#endif
{
    using namespace Constants;
#ifndef USE_GRAPHIC_TEXT_GINE
    txt::ParagraphStyle style;
#else
    Rosen::TypographyStyle style;
#endif
    if (isStroke) {
#ifndef USE_GRAPHIC_TEXT_GINE
        style.text_align = ConvertTxtTextAlign(strokeState_.GetTextAlign());
#else
        style.textAlign = ConvertTxtTextAlign(strokeState_.GetTextAlign());
#endif
    } else {
#ifndef USE_GRAPHIC_TEXT_GINE
        style.text_align = ConvertTxtTextAlign(fillState_.GetTextAlign());
#else
        style.textAlign = ConvertTxtTextAlign(fillState_.GetTextAlign());
#endif
    }
#ifndef USE_GRAPHIC_TEXT_GINE
    style.text_direction = ConvertTxtTextDirection(fillState_.GetOffTextDirection());
    style.text_align = GetEffectiveAlign(style.text_align, style.text_direction);
#else
    style.textDirection = ConvertTxtTextDirection(fillState_.GetOffTextDirection());
    style.textAlign = GetEffectiveAlign(style.textAlign, style.textDirection);
#endif
    auto fontCollection = RosenFontCollection::GetInstance().GetFontCollection();
    CHECK_NULL_RETURN(fontCollection, false);
#ifndef USE_GRAPHIC_TEXT_GINE
    std::unique_ptr<txt::ParagraphBuilder> builder = txt::ParagraphBuilder::CreateTxtBuilder(style, fontCollection);
    txt::TextStyle txtStyle;
#else
    std::unique_ptr<Rosen::TypographyCreate> builder = Rosen::TypographyCreate::Create(style, fontCollection);
    Rosen::TextStyle txtStyle;
#endif
    if (!isStroke && hasShadow) {
#ifndef USE_GRAPHIC_TEXT_GINE
        txt::TextShadow txtShadow;
        txtShadow.color = shadow_.GetColor().GetValue();
        txtShadow.offset.fX = shadow_.GetOffset().GetX();
        txtShadow.offset.fY = shadow_.GetOffset().GetY();
#else
        Rosen::TextShadow txtShadow;
        txtShadow.color = shadow_.GetColor().GetValue();
        txtShadow.offset.SetX(shadow_.GetOffset().GetX());
        txtShadow.offset.SetY(shadow_.GetOffset().GetY());
#endif
#ifndef NEW_SKIA
#ifndef USE_GRAPHIC_TEXT_GINE
        txtShadow.blur_radius = shadow_.GetBlurRadius();
#else
        txtShadow.blurRadius = shadow_.GetBlurRadius();
#endif
#else
#ifndef USE_GRAPHIC_TEXT_GINE
        txtShadow.blur_sigma = shadow_.GetBlurRadius();
#endif
#endif
#ifndef USE_GRAPHIC_TEXT_GINE
        txtStyle.text_shadows.emplace_back(txtShadow);
#else
        txtStyle.shadows.emplace_back(txtShadow);
#endif
    }
    txtStyle.locale = Localization::GetInstance()->GetFontLocale();
    UpdateTextStyleForeground(isStroke, txtStyle, hasShadow);
    builder->PushStyle(txtStyle);
#ifndef USE_GRAPHIC_TEXT_GINE
    builder->AddText(StringUtils::Str8ToStr16(text));
    paragraph_ = builder->Build();
#else
    builder->AppendText(StringUtils::Str8ToStr16(text));
    paragraph_ = builder->CreateTypography();
#endif
    return true;
}

#ifndef USE_GRAPHIC_TEXT_GINE
void OffscreenCanvasPaintMethod::UpdateTextStyleForeground(bool isStroke, txt::TextStyle& txtStyle, bool hasShadow)
#else
void OffscreenCanvasPaintMethod::UpdateTextStyleForeground(bool isStroke, Rosen::TextStyle& txtStyle, bool hasShadow)
#endif
{
#ifndef USE_ROSEN_DRAWING
    using namespace Constants;
    if (!isStroke) {
        txtStyle.color = ConvertSkColor(fillState_.GetColor());
#ifndef USE_GRAPHIC_TEXT_GINE
        txtStyle.font_size = fillState_.GetTextStyle().GetFontSize().Value();
#else
        txtStyle.fontSize = fillState_.GetTextStyle().GetFontSize().Value();
#endif
        ConvertTxtStyle(fillState_.GetTextStyle(), context_, txtStyle);
        if (fillState_.GetGradient().IsValid() && fillState_.GetPaintStyle() == PaintStyle::Gradient) {
            SkPaint paint;
#ifndef NEW_SKIA
            InitImagePaint(paint);
#else
            SkSamplingOptions options;
            InitImagePaint(paint, options);
#endif
            paint.setStyle(SkPaint::Style::kFill_Style);
            UpdatePaintShader(OffsetF(0, 0), paint, fillState_.GetGradient());
            txtStyle.foreground = paint;
#ifndef USE_GRAPHIC_TEXT_GINE
            txtStyle.has_foreground = true;
#endif
        }
        if (globalState_.HasGlobalAlpha()) {
#ifndef USE_GRAPHIC_TEXT_GINE
            if (txtStyle.has_foreground) {
                txtStyle.foreground.setColor(fillState_.GetColor().GetValue());
                txtStyle.foreground.setAlphaf(globalState_.GetAlpha()); // set alpha after color
#else
            if (txtStyle.foreground.has_value()) {
                txtStyle.foreground->setColor(fillState_.GetColor().GetValue());
                txtStyle.foreground->setAlphaf(globalState_.GetAlpha()); // set alpha after color
#endif
            } else {
                SkPaint paint;
#ifndef NEW_SKIA
                InitImagePaint(paint);
#else
                SkSamplingOptions options;
                InitImagePaint(paint, options);
#endif
                paint.setColor(fillState_.GetColor().GetValue());
                paint.setAlphaf(globalState_.GetAlpha()); // set alpha after color
                txtStyle.foreground = paint;
#ifndef USE_GRAPHIC_TEXT_GINE
                txtStyle.has_foreground = true;
#endif
            }
        }
    } else {
        // use foreground to draw stroke
        SkPaint paint;
#ifndef NEW_SKIA
        GetStrokePaint(paint);
#else
        SkSamplingOptions options;
        GetStrokePaint(paint, options);
#endif
        ConvertTxtStyle(strokeState_.GetTextStyle(), context_, txtStyle);
#ifndef USE_GRAPHIC_TEXT_GINE
        txtStyle.font_size = strokeState_.GetTextStyle().GetFontSize().Value();
        if (strokeState_.GetGradient().IsValid() && strokeState_.GetPaintStyle() == PaintStyle::Gradient) {
#else
        txtStyle.fontSize = strokeState_.GetTextStyle().GetFontSize().Value();
        if (strokeState_.GetGradient().IsValid()) {
#endif
            UpdatePaintShader(OffsetF(0, 0), paint, strokeState_.GetGradient());
        }
        if (hasShadow) {
            paint.setColor(shadow_.GetColor().GetValue());
            paint.setMaskFilter(SkMaskFilter::MakeBlur(SkBlurStyle::kNormal_SkBlurStyle,
                NG::SkiaDecorationPainter::ConvertRadiusToSigma(shadow_.GetBlurRadius())));
        }
        txtStyle.foreground = paint;
#ifndef USE_GRAPHIC_TEXT_GINE
        txtStyle.has_foreground = true;
#endif
    }
#else
    LOGE("Drawing is not supported");
#endif
}

#ifndef USE_ROSEN_DRAWING
void OffscreenCanvasPaintMethod::PaintShadow(const SkPath& path, const Shadow& shadow, SkCanvas* canvas, const SkPaint* paint)
{
    RosenDecorationPainter::PaintShadow(path, shadow, canvas, paint);
}
#else
void OffscreenCanvasPaintMethod::PaintShadow(const RSPath& path, const Shadow& shadow, RSCanvas* canvas)
{
    RosenDecorationPainter::PaintShadow(path, shadow, canvas);
}
#endif

void OffscreenCanvasPaintMethod::Path2DRect(const OffsetF& offset, const PathArgs& args)
{
    double left = args.para1 + offset.GetX();
    double top = args.para2 + offset.GetY();
    double right = args.para3 + args.para1;
    double bottom = args.para4 + args.para2;
#ifndef USE_ROSEN_DRAWING
    skPath2d_.addRect(SkRect::MakeLTRB(left, top, right, bottom));
#else
    rsPath2d_.AddRect(RSRect(left, top, right, bottom));
#endif
}

void OffscreenCanvasPaintMethod::SetTransform(const TransformParam& param)
{
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    double viewScale = context->GetViewScale();
#ifndef USE_ROSEN_DRAWING
    SkMatrix skMatrix;
    skMatrix.setAll(param.scaleX * viewScale, param.skewX * viewScale, param.translateX, param.skewY * viewScale,
        param.scaleY * viewScale, param.translateY, 0, 0, 1);
    skCanvas_->setMatrix(skMatrix);
#else
    RSMatrix rsMatrix;
    rsMatrix.SetMatrix(param.scaleX * viewScale, param.skewX * viewScale, param.translateX, param.skewY * viewScale,
        param.scaleY * viewScale, param.translateY, 0, 0, 1);
    rsCanvas_->SetMatrix(rsMatrix);
#endif
}

std::string OffscreenCanvasPaintMethod::ToDataURL(const std::string& type, const double quality)
{
    auto context = context_.Upgrade();
    CHECK_NULL_RETURN(context, UNSUPPORTED);
    std::string mimeType = GetMimeType(type);
    double qua = GetQuality(type, quality);
#ifndef USE_ROSEN_DRAWING
    SkBitmap tempCache;
    tempCache.allocPixels(SkImageInfo::Make(width_, height_, SkColorType::kBGRA_8888_SkColorType,
        (mimeType == IMAGE_JPEG) ? SkAlphaType::kOpaque_SkAlphaType : SkAlphaType::kUnpremul_SkAlphaType));
    SkCanvas tempCanvas(tempCache);
    double viewScale = context->GetViewScale();
    tempCanvas.clear(SK_ColorTRANSPARENT);
    tempCanvas.scale(1.0 / viewScale, 1.0 / viewScale);
#if defined(USE_SYSTEM_SKIA_S) || defined (NEW_SKIA)
    //The return value of the dual framework interface has no alpha
    tempCanvas.drawImage(canvasCache_.asImage(), 0.0f, 0.0f);
#else
    tempCanvas.drawBitmap(canvasCache_, 0.0f, 0.0f);
#endif
    SkPixmap src;
    bool success = tempCache.peekPixels(&src);
#else
    RSBitmap tempCache;
    tempCache.Build(width_, height_, { RSColorType::COLORTYPE_BGRA_8888,
        (mimeType == IMAGE_JPEG) ? RSAlphaType::ALPHATYPE_OPAQUE : RSAlphaType::ALPHATYPE_UNPREMUL });
    RSCanvas tempCanvas;
    tempCanvas.Bind(tempCache);
    double viewScale = context->GetViewScale();
    tempCanvas.Clear(RSColor::COLOR_TRANSPARENT);
    tempCanvas.Scale(1.0 / viewScale, 1.0 / viewScale);
    tempCanvas.DrawBitmap(canvasCache_, 0.0f, 0.0f);

    auto& skBitmap = tempCache.GetImpl<Rosen::Drawing::SkiaBitmap>()->ExportSkiaBitmap();
    SkPixmap src;
    bool success = skBitmap.peekPixels(&src);
#endif
    CHECK_NULL_RETURN(success, UNSUPPORTED);
    SkDynamicMemoryWStream dst;
    if (mimeType == IMAGE_JPEG) {
        SkJpegEncoder::Options options;
        options.fQuality = qua;
        success = SkJpegEncoder::Encode(&dst, src, options);
    } else if (mimeType == IMAGE_WEBP) {
        SkWebpEncoder::Options options;
        options.fQuality = qua * 100.0;
        success = SkWebpEncoder::Encode(&dst, src, options);
    } else {
        mimeType = IMAGE_PNG;
        SkPngEncoder::Options options;
        success = SkPngEncoder::Encode(&dst, src, options);
    }
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
}

TransformParam OffscreenCanvasPaintMethod::GetTransform() const
{
    TransformParam param;
#ifndef USE_ROSEN_DRAWING
    if (skCanvas_ != nullptr) {
        SkMatrix matrix = skCanvas_->getTotalMatrix();
        param.scaleX = matrix.getScaleX();
        param.scaleY = matrix.getScaleY();
        param.skewX = matrix.getSkewX();
        param.skewY = matrix.getSkewY();
        param.translateX = matrix.getTranslateX();
        param.translateY = matrix.getTranslateY();
    }
#else
    if (rsCanvas_ != nullptr) {
        RSMatrix matrix = rsCanvas_->GetTotalMatrix();
        param.scaleX = matrix.Get(RSMatrix::SCALE_X);
        param.scaleY = matrix.Get(RSMatrix::SCALE_Y);
        param.skewX = matrix.Get(RSMatrix::SKEW_X);
        param.skewY = matrix.Get(RSMatrix::SKEW_Y);
        param.translateX = matrix.Get(RSMatrix::TRANS_X);
        param.translateY = matrix.Get(RSMatrix::TRANS_Y);
    }
#endif
    return param;
}
} // namespace OHOS::Ace::NG
