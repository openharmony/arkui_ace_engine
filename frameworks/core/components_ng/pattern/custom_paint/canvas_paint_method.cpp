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

#include "core/components_ng/pattern/custom_paint/canvas_paint_method.h"

#include "drawing/engine_adapter/skia_adapter/skia_canvas.h"
#include "txt/paragraph_builder.h"
#include "txt/paragraph_style.h"
#include "include/core/SkImage.h"
#include "include/core/SkMaskFilter.h"
#include "include/encode/SkJpegEncoder.h"
#include "include/encode/SkPngEncoder.h"
#include "include/encode/SkWebpEncoder.h"
#include "include/utils/SkBase64.h"

#include "base/i18n/localization.h"
#include "base/image/pixel_map.h"
#include "base/utils/utils.h"
#include "core/components/common/painter/rosen_decoration_painter.h"
#include "core/components/font/constants_converter.h"
#ifndef NEW_SKIA
#include "core/components/font/flutter_font_collection.h"
#endif
#include "core/components/font/rosen_font_collection.h"
#include "core/components_ng/image_provider/image_object.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"
#include "core/components_ng/render/drawing.h"
#include "core/image/flutter_image_cache.h"

namespace OHOS::Ace::NG {
namespace {
constexpr double HANGING_PERCENT = 0.8;
constexpr int32_t IMAGE_CACHE_COUNT = 50;
constexpr double DEFAULT_QUALITY = 0.92;
constexpr int32_t MAX_LENGTH = 2048 * 2048;
constexpr int32_t PLATFORM_VERSION_TEN = 10;
const std::string UNSUPPORTED = "data:image/png";
const std::string URL_PREFIX = "data:";
const std::string URL_SYMBOL = ";base64,";
const std::string IMAGE_PNG = "image/png";
const std::string IMAGE_JPEG = "image/jpeg";
const std::string IMAGE_WEBP = "image/webp";

std::string GetMimeType(const std::string& args)
{
    // Args example: ["image/png"]
    std::vector<std::string> values;
    StringUtils::StringSplitter(args, '"', values);
    if (values.size() < 3) {
        return IMAGE_PNG;
    }
    // Convert to lowercase string.
    for (size_t i = 0; i < values[1].size(); ++i) {
        values[1][i] = static_cast<uint8_t>(tolower(values[1][i]));
    }
    return values[1];
}

// Quality need between 0.0 and 1.0 for MimeType jpeg and webp
double GetQuality(const std::string& args)
{
    // Args example: ["image/jpeg", 0.8]
    std::vector<std::string> values;
    StringUtils::StringSplitter(args, ',', values);
    if (values.size() < 2) {
        return DEFAULT_QUALITY;
    }
    auto mimeType = GetMimeType(args);
    if (mimeType != IMAGE_JPEG && mimeType != IMAGE_WEBP) {
        return DEFAULT_QUALITY;
    }
    double quality = StringUtils::StringToDouble(values[1]);
    if (quality < 0.0 || quality > 1.0) {
        return DEFAULT_QUALITY;
    }
    return quality;
}
} // namespace

void CanvasPaintMethod::UpdateContentModifier(PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(paintWrapper);
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    auto viewScale = context->GetViewScale();
    auto frameSize = paintWrapper->GetGeometryNode()->GetFrameSize();
    if (lastLayoutSize_ != frameSize) {
        UpdateRecordingCanvas(frameSize.Width() * viewScale, frameSize.Height() * viewScale);
        lastLayoutSize_.SetSizeT(frameSize);
    }
#ifndef USE_ROSEN_DRAWING
    if (!skCanvas_) {
        LOGW("skCanvas_ is null");
        return;
    }
#else
    if (!rsCanvas_) {
        LOGW("rsCanvas_ is null");
        return;
    }
#endif

    if (tasks_.empty()) {
        return;
    }

#ifndef USE_ROSEN_DRAWING
    skCanvas_->scale(viewScale, viewScale);
#else
    rsCanvas_->Scale(viewScale, viewScale);
#endif
    for (const auto& task : tasks_) {
        task(*this, paintWrapper);
    }
    tasks_.clear();
    CHECK_NULL_VOID(contentModifier_);
    contentModifier_->MarkModifierDirty();
}

void CanvasPaintMethod::ImageObjReady(const RefPtr<Ace::ImageObject>& imageObj)
{
    imageObj_ = imageObj;
    if (!imageObj_->IsSvg()) {
        LOGE("image is not svg");
        return;
    }
    skiaDom_ = AceType::DynamicCast<SvgSkiaImageObject>(imageObj_)->GetSkiaDom();
    currentSource_ = loadingSource_;
    Ace::CanvasImage canvasImage = canvasImage_;
    TaskFunc func = [canvasImage](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
        paintMethod.DrawImage(paintWrapper, canvasImage, 0, 0);
    };
    tasks_.emplace_back(func);
}

void CanvasPaintMethod::ImageObjFailed()
{
    imageObj_ = nullptr;
    skiaDom_ = nullptr;
}

void CanvasPaintMethod::DrawImage(
    PaintWrapper* paintWrapper, const Ace::CanvasImage& canvasImage, double width, double height)
{
    std::string::size_type tmp = canvasImage.src.find(".svg");
    if (tmp != std::string::npos) {
        DrawSvgImage(paintWrapper, canvasImage);
        return;
    }

    auto image = GetImage(canvasImage.src);
    CHECK_NULL_VOID(image);
#ifndef USE_ROSEN_DRAWING
#ifndef NEW_SKIA
    InitImagePaint(imagePaint_);
#else
    InitImagePaint(imagePaint_, sampleOptions_);
#endif
    InitPaintBlend(imagePaint_);

    const auto skCanvas = skCanvas_.get();
    if (HasImageShadow()) {
        SkRect skRect = SkRect::MakeXYWH(canvasImage.dx, canvasImage.dy, canvasImage.dWidth, canvasImage.dHeight);
        SkPath path;
        path.addRect(skRect);
        PaintShadow(path, *imageShadow_, skCanvas);
    }

    if (globalState_.HasGlobalAlpha()) {
        imagePaint_.setAlphaf(globalState_.GetAlpha());
    }

    switch (canvasImage.flag) {
        case 0: {
#ifndef NEW_SKIA
            skCanvas_->drawImage(image, canvasImage.dx, canvasImage.dy);
#else
            skCanvas_->drawImage(image, canvasImage.dx, canvasImage.dy, sampleOptions_, &imagePaint_);
#endif
            break;
        }
        case 1: {
            SkRect rect = SkRect::MakeXYWH(canvasImage.dx, canvasImage.dy, canvasImage.dWidth, canvasImage.dHeight);
#ifndef NEW_SKIA
            skCanvas_->drawImageRect(image, rect, &imagePaint_);
#else
            skCanvas_->drawImageRect(image, rect, sampleOptions_, &imagePaint_);
#endif
            break;
        }
        case 2: {
            SkRect dstRect = SkRect::MakeXYWH(canvasImage.dx, canvasImage.dy, canvasImage.dWidth, canvasImage.dHeight);
            SkRect srcRect = SkRect::MakeXYWH(canvasImage.sx, canvasImage.sy, canvasImage.sWidth, canvasImage.sHeight);
#ifndef NEW_SKIA
            skCanvas_->drawImageRect(image, srcRect, dstRect, &imagePaint_);
#else
            skCanvas_->drawImageRect(
                image, srcRect, dstRect, sampleOptions_, &imagePaint_, SkCanvas::kStrict_SrcRectConstraint);
#endif
            break;
        }
        default:
            break;
    }
#else
    InitImagePaint(nullptr, &imageBrush_, sampleOptions_);
    InitPaintBlend(imageBrush_);

    const auto rsCanvas = rsCanvas_.get();
    if (HasImageShadow()) {
        RSRect rsRect = RSRect(canvasImage.dx, canvasImage.dy,
            canvasImage.dWidth + canvasImage.dx, canvasImage.dHeight + canvasImage.dy);
        RSPath path;
        path.AddRect(rsRect);
        PaintShadow(path, *imageShadow_, rsCanvas);
    }

    if (globalState_.HasGlobalAlpha()) {
        imageBrush_.SetAlphaF(globalState_.GetAlpha());
    }

    switch (canvasImage.flag) {
        case 0:
            rsCanvas_->DrawImage(*image, canvasImage.dx, canvasImage.dy, RSSamplingOptions());
            break;
        case 1: {
            RSRect rect = RSRect(canvasImage.dx, canvasImage.dy,
                canvasImage.dWidth + canvasImage.dx, canvasImage.dHeight + canvasImage.dy);
            rsCanvas_->AttachBrush(imageBrush_);
            rsCanvas_->DrawImageRect(*image, rect, sampleOptions_);
            rsCanvas_->DetachBrush();
            break;
        }
        case 2: {
            RSRect dstRect = RSRect(canvasImage.dx, canvasImage.dy,
                canvasImage.dWidth + canvasImage.dx, canvasImage.dHeight + canvasImage.dy);
            RSRect srcRect = RSRect(canvasImage.sx, canvasImage.sy,
                canvasImage.sWidth + canvasImage.sx, canvasImage.sHeight + canvasImage.sy);
            rsCanvas_->AttachBrush(imageBrush_);
            rsCanvas_->DrawImageRect(*image, srcRect, dstRect, sampleOptions_);
            rsCanvas_->DetachBrush();
            break;
        }
        default:
            break;
    }
#endif
}

void CanvasPaintMethod::DrawPixelMap(RefPtr<PixelMap> pixelMap, const Ace::CanvasImage& canvasImage)
{
#ifndef USE_ROSEN_DRAWING
    // get skImage form pixelMap
    auto imageInfo = Ace::ImageProvider::MakeSkImageInfoFromPixelMap(pixelMap);
    SkPixmap imagePixmap(imageInfo, reinterpret_cast<const void*>(pixelMap->GetPixels()), pixelMap->GetRowBytes());

    // Step2: Create SkImage and draw it, using gpu or cpu
    sk_sp<SkImage> image =
        SkImage::MakeFromRaster(imagePixmap, &PixelMap::ReleaseProc, PixelMap::GetReleaseContext(pixelMap));
    CHECK_NULL_VOID(image);
#ifndef NEW_SKIA
    InitImagePaint(imagePaint_);
#else
    InitImagePaint(imagePaint_, sampleOptions_);
#endif
    InitPaintBlend(imagePaint_);
    switch (canvasImage.flag) {
        case 0:
            skCanvas_->drawImage(image, canvasImage.dx, canvasImage.dy);
            break;
        case 1: {
            SkRect rect = SkRect::MakeXYWH(canvasImage.dx, canvasImage.dy, canvasImage.dWidth, canvasImage.dHeight);
#ifndef NEW_SKIA
            skCanvas_->drawImageRect(image, rect, &imagePaint_);
#else
            skCanvas_->drawImageRect(image, rect, sampleOptions_, &imagePaint_);
#endif
            break;
        }
        case 2: {
            SkRect dstRect = SkRect::MakeXYWH(canvasImage.dx, canvasImage.dy, canvasImage.dWidth, canvasImage.dHeight);
            SkRect srcRect = SkRect::MakeXYWH(canvasImage.sx, canvasImage.sy, canvasImage.sWidth, canvasImage.sHeight);
#ifndef NEW_SKIA
            skCanvas_->drawImageRect(image, srcRect, dstRect, &imagePaint_);
#else
            skCanvas_->drawImageRect(
                image, srcRect, dstRect, sampleOptions_, &imagePaint_, SkCanvas::kStrict_SrcRectConstraint);
#endif
            break;
        }
        default:
            break;
    }
#else
    LOGE("Drawing is not supported");
#endif
}

#ifndef USE_ROSEN_DRAWING
sk_sp<SkImage> CanvasPaintMethod::GetImage(const std::string& src)
{
    if (!imageCache_) {
        imageCache_ = ImageCache::Create();
        imageCache_->SetCapacity(IMAGE_CACHE_COUNT);
    }
    auto cacheImage = imageCache_->GetCacheImage(src);
    if (cacheImage && cacheImage->imagePtr) {
        return cacheImage->imagePtr;
    }

    auto context = context_.Upgrade();
    CHECK_NULL_RETURN(context, nullptr);
    auto image = Ace::ImageProvider::GetSkImage(src, context);
    CHECK_NULL_RETURN(image, nullptr);
    auto rasterizedImage = image->makeRasterImage();
    imageCache_->CacheImage(src, std::make_shared<Ace::CachedImage>(rasterizedImage));
    return rasterizedImage;
}
#else
std::shared_ptr<RSImage> CanvasPaintMethod::GetImage(const std::string& src)
{
    if (!imageCache_) {
        imageCache_ = ImageCache::Create();
        imageCache_->SetCapacity(IMAGE_CACHE_COUNT);
    }
    auto cacheImage = imageCache_->GetCacheImage(src);
    if (cacheImage && cacheImage->imagePtr) {
        return cacheImage->imagePtr;
    }

    auto context = context_.Upgrade();
    CHECK_NULL_RETURN(context, nullptr);
    auto image = Ace::ImageProvider::GetDrawingImage(src, context);
    CHECK_NULL_RETURN(image, nullptr);
    RSBitmapFormat rsBitmapFormat { image->GetColorType(), image->GetAlphaType() };
    RSBitmap rsBitmap;
    rsBitmap.Build(image->GetWidth(), image->GetHeight(), rsBitmapFormat);
    CHECK_NULL_RETURN(image->ReadPixels(rsBitmap, 0, 0), nullptr);
    auto rasterizedImage = std::make_shared<RSImage>();
    rasterizedImage->BuildFromBitmap(rsBitmap);
    imageCache_->CacheImage(src, std::make_shared<Ace::CachedImage>(rasterizedImage));
    return rasterizedImage;
}
#endif


void CanvasPaintMethod::CloseImageBitmap(const std::string& src)
{
    CHECK_NULL_VOID(imageCache_);
    auto cacheImage = imageCache_->GetCacheImage(src);
    if (cacheImage && cacheImage->imagePtr) {
        imageCache_->ClearCacheImage(src);
    }
}

std::unique_ptr<Ace::ImageData> CanvasPaintMethod::GetImageData(RefPtr<RosenRenderContext> renderContext,
    double left, double top, double width, double height)
{
    CHECK_NULL_RETURN(renderContext, nullptr);
    double viewScale = 1.0;
    auto context = context_.Upgrade();
    CHECK_NULL_RETURN(context, nullptr);
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
    SkBitmap tempCache;
    tempCache.allocPixels(imageInfo);

    SkBitmap currentBitmap;
    CHECK_NULL_RETURN(rsRecordingCanvas_, nullptr);
    auto drawCmdList = rsRecordingCanvas_->GetDrawCmdList();
    bool res = renderContext->GetBitmap(currentBitmap, rsRecordingCanvas_->GetDrawCmdList());
    if (!res || currentBitmap.empty()) {
        LOGE("Bitmap is empty");
        return nullptr;
    }
    rsRecordingCanvas_->Clear();

    int32_t size = dirtyWidth * dirtyHeight;
    const uint8_t* pixels = nullptr;
    SkCanvas tempCanvas(tempCache);
    auto srcRect = SkRect::MakeXYWH(scaledLeft, scaledTop, dirtyWidth * viewScale, dirtyHeight * viewScale);
    auto dstRect = SkRect::MakeXYWH(0.0, 0.0, dirtyWidth, dirtyHeight);
#ifndef NEW_SKIA
    tempCanvas.drawBitmapRect(currentBitmap, srcRect, dstRect, nullptr);
#else
    tempCanvas.drawImageRect(
        currentBitmap.asImage(), srcRect, dstRect, SkSamplingOptions(), nullptr, SkCanvas::kStrict_SrcRectConstraint);
#endif
    pixels = tempCache.pixmap().addr8();
#else
    RSBitmapFormat format { RSColorType::COLORTYPE_BGRA_8888, RSAlphaType::ALPHATYPE_OPAQUE };
    RSBitmap tempCache;
    tempCache.Build(width, height, format);

    RSBitmap currentBitmap;
    CHECK_NULL_RETURN(rsRecordingCanvas_, nullptr);
    auto drawCmdList = rsRecordingCanvas_->GetDrawCmdList();
    bool res = renderContext->GetBitmap(currentBitmap, rsRecordingCanvas_->GetDrawCmdList());
    if (!res || !currentBitmap.IsValid()) {
        LOGE("Bitmap is empty");
        return nullptr;
    }
    LOGE("Drawing is not supported");

    int32_t size = dirtyWidth * dirtyHeight;
    RSCanvas tempCanvas;
    tempCanvas.Bind(tempCache);
    auto srcRect = RSRect(scaledLeft, scaledTop,
        dirtyWidth * viewScale + scaledLeft, dirtyHeight * viewScale + scaledTop);
    auto dstRect = RSRect(0.0, 0.0, dirtyWidth, dirtyHeight);
    RSImage rsImage;
    rsImage.BuildFromBitmap(currentBitmap);
    tempCanvas.DrawImageRect(rsImage, srcRect, dstRect, RSSamplingOptions());
    const uint8_t* pixels = static_cast<const uint8_t*>(tempCache.GetPixels());
#endif
    CHECK_NULL_RETURN(pixels, nullptr);
    std::unique_ptr<Ace::ImageData> imageData = std::make_unique<Ace::ImageData>();
    imageData->dirtyWidth = dirtyWidth;
    imageData->dirtyHeight = dirtyHeight;
    // a pixel include 4 data(blue, green, red, alpha)
    for (int i = 0; i < size * 4; i += 4) {
        auto blue = pixels[i];
        auto green = pixels[i + 1];
        auto red = pixels[i + 2];
        auto alpha = pixels[i + 3];
        imageData->data.emplace_back(Color::FromARGB(alpha, red, green, blue));
    }
    return imageData;
}

void CanvasPaintMethod::TransferFromImageBitmap(PaintWrapper* paintWrapper,
    const RefPtr<OffscreenCanvasPattern>& offscreenCanvas)
{
    std::unique_ptr<Ace::ImageData> imageData =
        offscreenCanvas->GetImageData(0, 0, offscreenCanvas->GetWidth(), offscreenCanvas->GetHeight());
    CHECK_NULL_VOID(imageData);
    PutImageData(paintWrapper, *imageData);
}

void CanvasPaintMethod::FillText(
    PaintWrapper* paintWrapper, const std::string& text, double x, double y, std::optional<double> maxWidth)
{
    CHECK_NULL_VOID(paintWrapper);
    OffsetF offset = GetContentOffset(paintWrapper);
    auto frameSize = paintWrapper->GetGeometryNode()->GetFrameSize();

    auto success = UpdateParagraph(offset, text, false, HasShadow());
    CHECK_NULL_VOID(success);
    PaintText(offset, frameSize, x, y, maxWidth, false, HasShadow());
}

void CanvasPaintMethod::StrokeText(
    PaintWrapper* paintWrapper, const std::string& text, double x, double y, std::optional<double> maxWidth)
{
    CHECK_NULL_VOID(paintWrapper);
    OffsetF offset = GetContentOffset(paintWrapper);
    auto frameSize = paintWrapper->GetGeometryNode()->GetFrameSize();

    if (HasShadow()) {
        auto success = UpdateParagraph(offset, text, true, true);
        CHECK_NULL_VOID(success);
        PaintText(offset, frameSize, x, y, maxWidth, true, true);
    }

    auto success = UpdateParagraph(offset, text, true);
    CHECK_NULL_VOID(success);
    PaintText(offset, frameSize, x, y, maxWidth, true);
}

double CanvasPaintMethod::MeasureText(const std::string& text, const PaintState& state)
{
    using namespace Constants;
    txt::ParagraphStyle style;
    style.text_align = ConvertTxtTextAlign(state.GetTextAlign());
#ifndef NEW_SKIA
    auto fontCollection = FlutterFontCollection::GetInstance().GetFontCollection();
#else
    auto fontCollection = RosenFontCollection::GetInstance().GetFontCollection();
#endif
    CHECK_NULL_RETURN(fontCollection, 0.0);
    std::unique_ptr<txt::ParagraphBuilder> builder = txt::ParagraphBuilder::CreateTxtBuilder(style, fontCollection);
    txt::TextStyle txtStyle;
    ConvertTxtStyle(state.GetTextStyle(), context_, txtStyle);
    txtStyle.font_size = state.GetTextStyle().GetFontSize().Value();
    builder->PushStyle(txtStyle);
    builder->AddText(StringUtils::Str8ToStr16(text));
    auto paragraph = builder->Build();
    paragraph->Layout(Size::INFINITE_SIZE);
    return paragraph->GetMaxIntrinsicWidth();
}

double CanvasPaintMethod::MeasureTextHeight(const std::string& text, const PaintState& state)
{
    using namespace Constants;
    txt::ParagraphStyle style;
    style.text_align = ConvertTxtTextAlign(state.GetTextAlign());
#ifndef NEW_SKIA
    auto fontCollection = FlutterFontCollection::GetInstance().GetFontCollection();
#else
    auto fontCollection = RosenFontCollection::GetInstance().GetFontCollection();
#endif
    CHECK_NULL_RETURN(fontCollection, 0.0);
    std::unique_ptr<txt::ParagraphBuilder> builder = txt::ParagraphBuilder::CreateTxtBuilder(style, fontCollection);
    txt::TextStyle txtStyle;
    ConvertTxtStyle(state.GetTextStyle(), context_, txtStyle);
    txtStyle.font_size = state.GetTextStyle().GetFontSize().Value();
    builder->PushStyle(txtStyle);
    builder->AddText(StringUtils::Str8ToStr16(text));
    auto paragraph = builder->Build();
    paragraph->Layout(Size::INFINITE_SIZE);
    return paragraph->GetHeight();
}

TextMetrics CanvasPaintMethod::MeasureTextMetrics(const std::string& text, const PaintState& state)
{
    using namespace Constants;
    TextMetrics textMetrics = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
    txt::ParagraphStyle style;
    style.text_align = ConvertTxtTextAlign(state.GetTextAlign());
#ifndef NEW_SKIA
    auto fontCollection = FlutterFontCollection::GetInstance().GetFontCollection();
#else
    auto fontCollection = RosenFontCollection::GetInstance().GetFontCollection();
#endif
    CHECK_NULL_RETURN(fontCollection, textMetrics);
    std::unique_ptr<txt::ParagraphBuilder> builder = txt::ParagraphBuilder::CreateTxtBuilder(style, fontCollection);
    txt::TextStyle txtStyle;
    ConvertTxtStyle(state.GetTextStyle(), context_, txtStyle);
    txtStyle.font_size = state.GetTextStyle().GetFontSize().Value();
    builder->PushStyle(txtStyle);
    builder->AddText(StringUtils::Str8ToStr16(text));
    auto paragraph = builder->Build();
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

void CanvasPaintMethod::PaintText(const OffsetF& offset, const SizeF& frameSize, double x, double y,
    std::optional<double> maxWidth, bool isStroke, bool hasShadow)
{
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    if (pipelineContext->GetMinPlatformVersion() >= PLATFORM_VERSION_TEN) {
        paragraph_->Layout(FLT_MAX);
    } else {
        paragraph_->Layout(frameSize.Width());
    }
    auto width = paragraph_->GetMaxIntrinsicWidth();
    if (frameSize.Width() > width) {
        paragraph_->Layout(std::ceil(width));
    }
    auto align = isStroke ? strokeState_.GetTextAlign() : fillState_.GetTextAlign();
#ifndef USE_ROSEN_DRAWING
    double dx = offset.GetX() + x + GetAlignOffset(align, paragraph_);
    auto baseline =
        isStroke ? strokeState_.GetTextStyle().GetTextBaseline() : fillState_.GetTextStyle().GetTextBaseline();
    double dy = offset.GetY() + y + GetBaselineOffset(baseline, paragraph_);

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
    double dx = offset.GetX() + x + GetAlignOffset(align, paragraph_);

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

double CanvasPaintMethod::GetBaselineOffset(TextBaseline baseline, std::unique_ptr<txt::Paragraph>& paragraph)
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

bool CanvasPaintMethod::UpdateParagraph(const OffsetF& offset, const std::string& text, bool isStroke, bool hasShadow)
{
    using namespace Constants;
    txt::ParagraphStyle style;
    if (isStroke) {
        style.text_align = ConvertTxtTextAlign(strokeState_.GetTextAlign());
    } else {
        style.text_align = ConvertTxtTextAlign(fillState_.GetTextAlign());
    }
    style.text_direction = ConvertTxtTextDirection(fillState_.GetOffTextDirection());
    style.text_align = GetEffectiveAlign(style.text_align, style.text_direction);
#ifndef NEW_SKIA
    auto fontCollection = FlutterFontCollection::GetInstance().GetFontCollection();
#else
    auto fontCollection = RosenFontCollection::GetInstance().GetFontCollection();
#endif
    CHECK_NULL_RETURN(fontCollection, false);
    std::unique_ptr<txt::ParagraphBuilder> builder = txt::ParagraphBuilder::CreateTxtBuilder(style, fontCollection);
    txt::TextStyle txtStyle;
    if (!isStroke && hasShadow) {
        txt::TextShadow txtShadow;
        txtShadow.color = shadow_.GetColor().GetValue();
        txtShadow.offset.fX = shadow_.GetOffset().GetX();
        txtShadow.offset.fY = shadow_.GetOffset().GetY();
#ifndef NEW_SKIA
        txtShadow.blur_radius = shadow_.GetBlurRadius();
#else
        txtShadow.blur_sigma = shadow_.GetBlurRadius();
#endif
        txtStyle.text_shadows.emplace_back(txtShadow);
    }
    txtStyle.locale = Localization::GetInstance()->GetFontLocale();
    UpdateTextStyleForeground(offset, isStroke, txtStyle, hasShadow);
    builder->PushStyle(txtStyle);
    builder->AddText(StringUtils::Str8ToStr16(text));
    paragraph_ = builder->Build();
    return true;
}

void CanvasPaintMethod::UpdateTextStyleForeground(
    const OffsetF& offset, bool isStroke, txt::TextStyle& txtStyle, bool hasShadow)
{
#ifndef USE_ROSEN_DRAWING
    using namespace Constants;
    if (!isStroke) {
        txtStyle.color = ConvertSkColor(fillState_.GetColor());
        txtStyle.font_size = fillState_.GetTextStyle().GetFontSize().Value();
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
            UpdatePaintShader(offset, paint, fillState_.GetGradient());
            txtStyle.foreground = paint;
            txtStyle.has_foreground = true;
        }
        if (globalState_.HasGlobalAlpha()) {
            if (txtStyle.has_foreground) {
                txtStyle.foreground.setColor(fillState_.GetColor().GetValue());
                txtStyle.foreground.setAlphaf(globalState_.GetAlpha()); // set alpha after color
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
                InitPaintBlend(paint);
                txtStyle.foreground = paint;
                txtStyle.has_foreground = true;
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
        InitPaintBlend(paint);
        ConvertTxtStyle(strokeState_.GetTextStyle(), context_, txtStyle);
        txtStyle.font_size = strokeState_.GetTextStyle().GetFontSize().Value();
        if (strokeState_.GetGradient().IsValid() && strokeState_.GetPaintStyle() == PaintStyle::Gradient) {
            UpdatePaintShader(offset, paint, strokeState_.GetGradient());
        }
        if (hasShadow) {
            paint.setColor(shadow_.GetColor().GetValue());
            paint.setMaskFilter(SkMaskFilter::MakeBlur(SkBlurStyle::kNormal_SkBlurStyle,
                RosenDecorationPainter::ConvertRadiusToSigma(shadow_.GetBlurRadius())));
        }
        txtStyle.foreground = paint;
        txtStyle.has_foreground = true;
    }
#else
    LOGE("Drawing is not supported");
#endif
}

#ifndef USE_ROSEN_DRAWING
void CanvasPaintMethod::PaintShadow(const SkPath& path, const Shadow& shadow, SkCanvas* canvas)
#else
void CanvasPaintMethod::PaintShadow(const RSPath& path, const Shadow& shadow, RSCanvas* canvas)
#endif
{
#ifdef ENABLE_ROSEN_BACKEND
    RosenDecorationPainter::PaintShadow(path, shadow, canvas);
#endif
}

void CanvasPaintMethod::Path2DRect(const OffsetF& offset, const PathArgs& args)
{
    double left = args.para1 + offset.GetX();
    double top = args.para2 + offset.GetY();
    double right = args.para3 + args.para1 + offset.GetX();
    double bottom = args.para4 + args.para2 + offset.GetY();
#ifndef USE_ROSEN_DRAWING
    skPath2d_.addRect(SkRect::MakeLTRB(left, top, right, bottom));
#else
    rsPath2d_.AddRect(RSRect(left, top, right, bottom));
#endif
}

void CanvasPaintMethod::SetTransform(const TransformParam& param)
{
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    double viewScale = context->GetViewScale();
#ifndef USE_ROSEN_DRAWING
    SkMatrix skMatrix;
    skMatrix.setAll(param.scaleX * viewScale, param.skewX * viewScale, param.translateX * viewScale,
        param.skewY * viewScale, param.scaleY * viewScale, param.translateY * viewScale, 0, 0, 1);
    skCanvas_->setMatrix(skMatrix);
#else
    RSMatrix rsMatrix;
    rsMatrix.SetMatrix(param.scaleX * viewScale, param.skewX * viewScale, param.translateX * viewScale,
        param.skewY * viewScale, param.scaleY * viewScale, param.translateY * viewScale, 0, 0, 1);
    rsCanvas_->SetMatrix(rsMatrix);
#endif
}

std::string CanvasPaintMethod::ToDataURL(RefPtr<RosenRenderContext> renderContext, const std::string& args)
{
    CHECK_NULL_RETURN(renderContext, UNSUPPORTED);
    std::string mimeType = GetMimeType(args);
    double quality = GetQuality(args);
    double width = lastLayoutSize_.Width();
    double height = lastLayoutSize_.Height();
    SkBitmap tempCache;
    tempCache.allocPixels(SkImageInfo::Make(width, height, SkColorType::kBGRA_8888_SkColorType,
        (mimeType == IMAGE_JPEG) ? SkAlphaType::kOpaque_SkAlphaType : SkAlphaType::kUnpremul_SkAlphaType));

#ifndef USE_ROSEN_DRAWING
    SkBitmap currentBitmap;
#else
    RSBitmap currentBitmap;
#endif
    CHECK_NULL_RETURN(rsRecordingCanvas_, UNSUPPORTED);
    auto drawCmdList = rsRecordingCanvas_->GetDrawCmdList();
    bool res = renderContext->GetBitmap(currentBitmap, rsRecordingCanvas_->GetDrawCmdList());
#ifndef USE_ROSEN_DRAWING
    if (!res || currentBitmap.empty()) {
#else
    if (!res || !currentBitmap.IsValid()) {
#endif
        LOGE("Bitmap is empty");
        return UNSUPPORTED;
    }
#ifndef USE_ROSEN_DRAWING
    rsRecordingCanvas_->Clear();
    bool success = false;
#ifndef NEW_SKIA
    success = currentBitmap.pixmap().scalePixels(tempCache.pixmap(), SkFilterQuality::kHigh_SkFilterQuality);
#else
    success = currentBitmap.pixmap().scalePixels(
        tempCache.pixmap(), SkSamplingOptions(SkCubicResampler { 1 / 3.0f, 1 / 3.0f }));
#endif
#else
    LOGE("Drawing is not supported");
    bool success = false;
    auto& skBitmap = currentBitmap.GetImpl<Rosen::Drawing::SkiaBitmap>()->ExportSkiaBitmap();
    success = skBitmap.pixmap().scalePixels(
        tempCache.pixmap(), SkSamplingOptions(SkCubicResampler { 1 / 3.0f, 1 / 3.0f }));
#endif

    CHECK_NULL_RETURN(success, UNSUPPORTED);
    SkPixmap src = tempCache.pixmap();
    SkDynamicMemoryWStream dst;
    if (mimeType == IMAGE_JPEG) {
        SkJpegEncoder::Options options;
        options.fQuality = quality * 100;
        success = SkJpegEncoder::Encode(&dst, src, options);
    } else if (mimeType == IMAGE_WEBP) {
        SkWebpEncoder::Options options;
        options.fQuality = quality * 100.0;
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
        LOGE("ToDataURL failed, image too large.");
        return UNSUPPORTED;
    }
    SkString info(len);
    SkBase64::Encode(result->data(), result->size(), info.writable_str());

    return std::string(URL_PREFIX).append(mimeType).append(URL_SYMBOL).append(info.c_str());
}

std::string CanvasPaintMethod::GetJsonData(const std::string& path)
{
    AssetImageLoader imageLoader;
    return imageLoader.LoadJsonData(path, context_);
}
} // namespace OHOS::Ace::NG

