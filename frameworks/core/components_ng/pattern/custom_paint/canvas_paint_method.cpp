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
#include "flutter/third_party/txt/src/txt/paragraph_builder.h"
#include "flutter/third_party/txt/src/txt/paragraph_style.h"
#include "third_party/skia/include/core/SkMaskFilter.h"
#include "third_party/skia/include/encode/SkJpegEncoder.h"
#include "third_party/skia/include/encode/SkPngEncoder.h"
#include "third_party/skia/include/encode/SkWebpEncoder.h"
#include "third_party/skia/include/utils/SkBase64.h"

#include "base/i18n/localization.h"
#include "core/components/common/painter/rosen_decoration_painter.h"
#include "core/components/font/constants_converter.h"
#include "core/components/font/flutter_font_collection.h"
#include "core/components/font/rosen_font_collection.h"
#include "core/components_ng/render/drawing.h"
#include "core/image/flutter_image_cache.h"

namespace OHOS::Ace::NG {
namespace {
constexpr double HANGING_PERCENT = 0.8;
constexpr int32_t IMAGE_CACHE_COUNT = 50;
constexpr double DEFAULT_QUALITY = 0.92;
constexpr int32_t MAX_LENGTH = 2048 * 2048;
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
    } else {
        // Convert to lowercase string.
        for (size_t i = 0; i < values[1].size(); ++i) {
            values[1][i] = static_cast<uint8_t>(tolower(values[1][i]));
        }
        return values[1];
    }
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

CanvasDrawFunction CanvasPaintMethod::GetForegroundDrawFunction(PaintWrapper* paintWrapper)
{
    auto paintFunc = [weak = WeakClaim(this), paintWrapper](RSCanvas& canvas) {
        auto customPaint = weak.Upgrade();
        if (customPaint) {
            customPaint->PaintCustomPaint(canvas, paintWrapper);
        }
    };

    return paintFunc;
}

void CanvasPaintMethod::PaintCustomPaint(RSCanvas& canvas, PaintWrapper* paintWrapper)
{
    SkCanvas* skCanvas = canvas.GetImpl<Rosen::Drawing::SkiaCanvas>()->ExportSkCanvas();
    auto frameSize = paintWrapper->GetGeometryNode()->GetFrameSize();
    if (lastLayoutSize_ != frameSize) {
        CreateBitmap(frameSize);
        lastLayoutSize_.SetSizeT(frameSize);
    }
    auto viewScale = context_->GetViewScale();
    skCanvas_->scale(viewScale, viewScale);

    for (const auto& task : tasks_) {
        task(*this, paintWrapper);
    }
    skCanvas_->scale(1.0 / viewScale, 1.0 / viewScale);
    tasks_.clear();

    skCanvas->save();
    skCanvas->scale(1.0 / viewScale, 1.0 / viewScale);
    skCanvas->drawBitmap(canvasCache_, 0.0f, 0.0f);

    skCanvas->restore();
}

void CanvasPaintMethod::CreateBitmap(SizeF frameSize)
{
    auto viewScale = context_->GetViewScale();
    auto imageInfo = SkImageInfo::Make(frameSize.Width() * viewScale, frameSize.Height() * viewScale,
        SkColorType::kRGBA_8888_SkColorType, SkAlphaType::kUnpremul_SkAlphaType);
    canvasCache_.reset();
    cacheBitmap_.reset();
    canvasCache_.allocPixels(imageInfo);
    cacheBitmap_.allocPixels(imageInfo);
    canvasCache_.eraseColor(SK_ColorTRANSPARENT);
    cacheBitmap_.eraseColor(SK_ColorTRANSPARENT);
    skCanvas_ = std::make_unique<SkCanvas>(canvasCache_);
    cacheCanvas_ = std::make_unique<SkCanvas>(cacheBitmap_);
}

void CanvasPaintMethod::ImageObjReady(const RefPtr<ImageObject>& imageObj)
{
    imageObj_ = imageObj;
    if (imageObj_->IsSvg()) {
        skiaDom_ = AceType::DynamicCast<SvgSkiaImageObject>(imageObj_)->GetSkiaDom();
        currentSource_ = loadingSource_;
        Ace::CanvasImage canvasImage = canvasImage_;
        TaskFunc func = [canvasImage](CanvasPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
            paintMethod.DrawImage(paintWrapper, canvasImage, 0, 0);
        };
        tasks_.emplace_back(func);
        return;
    }
    LOGE("image is not svg");
}

void CanvasPaintMethod::ImageObjFailed()
{
    imageObj_ = nullptr;
    skiaDom_ = nullptr;
}

void CanvasPaintMethod::DrawImage(
    PaintWrapper* paintWrapper, const Ace::CanvasImage& canvasImage, double width, double height)
{
    if (!flutter::UIDartState::Current()) {
        return;
    }

    std::string::size_type tmp = canvasImage.src.find(".svg");
    if (tmp != std::string::npos) {
        DrawSvgImage(paintWrapper, canvasImage);
        return;
    }

    auto image = GetImage(canvasImage.src);
    if (!image) {
        LOGE("image is null");
        return;
    }
    InitImagePaint();
    InitPaintBlend(imagePaint_);

    switch (canvasImage.flag) {
        case 0:
            skCanvas_->drawImage(image, canvasImage.dx, canvasImage.dy);
            break;
        case 1: {
            SkRect rect = SkRect::MakeXYWH(canvasImage.dx, canvasImage.dy, canvasImage.dWidth, canvasImage.dHeight);
            skCanvas_->drawImageRect(image, rect, &imagePaint_);
            break;
        }
        case 2: {
            SkRect dstRect = SkRect::MakeXYWH(canvasImage.dx, canvasImage.dy, canvasImage.dWidth, canvasImage.dHeight);
            SkRect srcRect = SkRect::MakeXYWH(canvasImage.sx, canvasImage.sy, canvasImage.sWidth, canvasImage.sHeight);
            skCanvas_->drawImageRect(image, srcRect, dstRect, &imagePaint_);
            break;
        }
        default:
            break;
    }
}

void CanvasPaintMethod::DrawPixelMap(RefPtr<PixelMap> pixelMap, const Ace::CanvasImage& canvasImage)
{
    if (!flutter::UIDartState::Current()) {
        return;
    }

    // get skImage form pixelMap
    auto imageInfo = ImageProvider::MakeSkImageInfoFromPixelMap(pixelMap);
    SkPixmap imagePixmap(imageInfo, reinterpret_cast<const void*>(pixelMap->GetPixels()), pixelMap->GetRowBytes());

    // Step2: Create SkImage and draw it, using gpu or cpu
    sk_sp<SkImage> image;
    if (!renderTaskHolder_->ioManager) {
        image = SkImage::MakeFromRaster(imagePixmap, nullptr, nullptr);
    } else {
#ifndef GPU_DISABLED
        image = SkImage::MakeCrossContextFromPixmap(renderTaskHolder_->ioManager->GetResourceContext().get(),
            imagePixmap, true, imagePixmap.colorSpace(), true);
#else
        image = SkImage::MakeFromRaster(imagePixmap, nullptr, nullptr);
#endif
    }
    if (!image) {
        LOGE("image is null");
        return;
    }
    InitImagePaint();
    InitPaintBlend(imagePaint_);
    switch (canvasImage.flag) {
        case 0:
            skCanvas_->drawImage(image, canvasImage.dx, canvasImage.dy);
            break;
        case 1: {
            SkRect rect = SkRect::MakeXYWH(canvasImage.dx, canvasImage.dy, canvasImage.dWidth, canvasImage.dHeight);
            skCanvas_->drawImageRect(image, rect, &imagePaint_);
            break;
        }
        case 2: {
            SkRect dstRect = SkRect::MakeXYWH(canvasImage.dx, canvasImage.dy, canvasImage.dWidth, canvasImage.dHeight);
            SkRect srcRect = SkRect::MakeXYWH(canvasImage.sx, canvasImage.sy, canvasImage.sWidth, canvasImage.sHeight);
            skCanvas_->drawImageRect(image, srcRect, dstRect, &imagePaint_);
            break;
        }
        default:
            break;
    }
}

sk_sp<SkImage> CanvasPaintMethod::GetImage(const std::string& src)
{
    if (!imageCache_) {
        imageCache_ = ImageCache::Create();
        imageCache_->SetCapacity(IMAGE_CACHE_COUNT);
    }
    auto cacheImage = imageCache_->GetCacheImage(src);
    if (cacheImage && cacheImage->imagePtr) {
        return cacheImage->imagePtr->image();
    }

    CHECK_NULL_RETURN(context_, nullptr);

    auto image = ImageProvider::GetSkImage(src, context_);
    if (image) {
        auto rasterizedImage = image->makeRasterImage();
        auto canvasImage = flutter::CanvasImage::Create();
        canvasImage->set_image({ rasterizedImage, renderTaskHolder_->unrefQueue });
        imageCache_->CacheImage(src, std::make_shared<CachedImage>(canvasImage));
        return rasterizedImage;
    }

    return image;
}

std::unique_ptr<Ace::ImageData> CanvasPaintMethod::GetImageData(
    double left, double top, double width, double height)
{
    double viewScale = 1.0;
    CHECK_NULL_RETURN(context_, nullptr);
    viewScale = context_->GetViewScale();
    // copy the bitmap to tempCanvas
    auto imageInfo =
        SkImageInfo::Make(width, height, SkColorType::kBGRA_8888_SkColorType, SkAlphaType::kOpaque_SkAlphaType);
    SkBitmap tempCache;
    double scaledLeft = left * viewScale;
    double scaledTop = top * viewScale;
    double dirtyWidth = width >= 0 ? width : 0;
    double dirtyHeight = height >= 0 ? height : 0;
    tempCache.allocPixels(imageInfo);
    int32_t size = dirtyWidth * dirtyHeight;
    bool isGpuEnable = false;
    const uint8_t* pixels = nullptr;
    SkCanvas tempCanvas(tempCache);
    auto srcRect = SkRect::MakeXYWH(scaledLeft, scaledTop, width * viewScale, height * viewScale);
    auto dstRect = SkRect::MakeXYWH(0.0, 0.0, dirtyWidth, dirtyHeight);

    if (!isGpuEnable) {
        tempCanvas.drawBitmapRect(canvasCache_, srcRect, dstRect, nullptr);
    }
    pixels = tempCache.pixmap().addr8();
    if (pixels == nullptr) {
        return nullptr;
    }
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
    Ace::ImageData* imageDataPtr = imageData.get();
    if (imageData != nullptr) {
        PutImageData(paintWrapper, *imageDataPtr);
    }
}

void CanvasPaintMethod::FillText(PaintWrapper* paintWrapper, const std::string& text, double x, double y)
{
    CHECK_NULL_VOID(paintWrapper);
    auto offset = paintWrapper->GetContentOffset();
    auto frameSize = paintWrapper->GetGeometryNode()->GetFrameSize();

    if (!UpdateParagraph(offset, text, false)) {
        return;
    }
    PaintText(offset, frameSize, x, y, false);
}

void CanvasPaintMethod::StrokeText(PaintWrapper* paintWrapper, const std::string& text, double x, double y)
{
    CHECK_NULL_VOID(paintWrapper);
    auto offset = paintWrapper->GetContentOffset();
    auto frameSize = paintWrapper->GetGeometryNode()->GetFrameSize();

    if (HasShadow()) {
        if (!UpdateParagraph(offset, text, true, true)) {
            return;
        }
        PaintText(offset, frameSize, x, y, true);
    }

    if (!UpdateParagraph(offset, text, true)) {
        return;
    }
    PaintText(offset, frameSize, x, y, true);
}

double CanvasPaintMethod::MeasureText(const std::string& text, const PaintState& state)
{
    using namespace Constants;
    txt::ParagraphStyle style;
    style.text_align = ConvertTxtTextAlign(state.GetTextAlign());
    auto fontCollection = FlutterFontCollection::GetInstance().GetFontCollection();
    if (!fontCollection) {
        LOGW("MeasureText: fontCollection is null");
        return 0.0;
    }
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
    auto fontCollection = FlutterFontCollection::GetInstance().GetFontCollection();
    if (!fontCollection) {
        LOGW("MeasureText: fontCollection is null");
        return 0.0;
    }
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
    txt::ParagraphStyle style;
    style.text_align = ConvertTxtTextAlign(state.GetTextAlign());
    auto fontCollection = FlutterFontCollection::GetInstance().GetFontCollection();
    if (!fontCollection) {
        LOGW("MeasureText: fontCollection is null");
        return { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
    }
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

    auto width = paragraph->GetMaxIntrinsicWidth();
    auto height = paragraph->GetHeight();

    auto actualBoundingBoxLeft = -GetAlignOffset(textAlign, paragraph);
    auto actualBoundingBoxRight = width - actualBoundingBoxLeft;
    auto actualBoundingBoxAscent = -GetBaselineOffset(textBaseLine, paragraph);
    auto actualBoundingBoxDescent = height - actualBoundingBoxAscent;

    return { width, height, actualBoundingBoxLeft, actualBoundingBoxRight, actualBoundingBoxAscent,
        actualBoundingBoxDescent };
}

void CanvasPaintMethod::PaintText(
    const OffsetF& offset, const SizeF& frameSize, double x, double y, bool isStroke, bool hasShadow)
{
    paragraph_->Layout(frameSize.Width());
    if (frameSize.Width() > paragraph_->GetMaxIntrinsicWidth()) {
        paragraph_->Layout(std::ceil(paragraph_->GetMaxIntrinsicWidth()));
    }
    auto align = isStroke ? strokeState_.GetTextAlign() : fillState_.GetTextAlign();
    double dx = offset.GetX() + x + GetAlignOffset(align, paragraph_);
    auto baseline =
        isStroke ? strokeState_.GetTextStyle().GetTextBaseline() : fillState_.GetTextStyle().GetTextBaseline();
    double dy = offset.GetY() + y + GetBaselineOffset(baseline, paragraph_);

    if (hasShadow) {
        skCanvas_->save();
        auto shadowOffsetX = shadow_.GetOffset().GetX();
        auto shadowOffsetY = shadow_.GetOffset().GetY();
        paragraph_->Paint(skCanvas_.get(), dx + shadowOffsetX, dy + shadowOffsetY);
        skCanvas_->restore();
        return;
    }

    paragraph_->Paint(skCanvas_.get(), dx, dy);
}

double CanvasPaintMethod::GetAlignOffset(TextAlign align, std::unique_ptr<txt::Paragraph>& paragraph)
{
    double x = 0.0;
    TextDirection textDirection = TextDirection::LTR;
    switch (align) {
        case TextAlign::LEFT:
            x = 0.0;
            break;
        case TextAlign::START:
            x = (textDirection == TextDirection::LTR) ? 0.0 : -paragraph->GetMaxIntrinsicWidth();
            break;
        case TextAlign::RIGHT:
            x = -paragraph->GetMaxIntrinsicWidth();
            break;
        case TextAlign::END:
            x = (textDirection == TextDirection::LTR) ? -paragraph->GetMaxIntrinsicWidth() : 0.0;
            break;
        case TextAlign::CENTER:
            x = -paragraph->GetMaxIntrinsicWidth() / 2;
            break;
        default:
            x = 0.0;
            break;
    }
    return x;
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
    auto fontCollection = FlutterFontCollection::GetInstance().GetFontCollection();
    if (!fontCollection) {
        LOGW("UpdateParagraph: fontCollection is null");
        return false;
    }
    std::unique_ptr<txt::ParagraphBuilder> builder = txt::ParagraphBuilder::CreateTxtBuilder(style, fontCollection);
    txt::TextStyle txtStyle;
    if (!isStroke && hasShadow) {
        txt::TextShadow txtShadow;
        txtShadow.color = shadow_.GetColor().GetValue();
        txtShadow.offset.fX = shadow_.GetOffset().GetX();
        txtShadow.offset.fY = shadow_.GetOffset().GetY();
        txtShadow.blur_radius = shadow_.GetBlurRadius();
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
    using namespace Constants;
    if (!isStroke) {
        txtStyle.color = ConvertSkColor(fillState_.GetColor());
        txtStyle.font_size = fillState_.GetTextStyle().GetFontSize().Value();
        ConvertTxtStyle(fillState_.GetTextStyle(), context_, txtStyle);
        if (fillState_.GetGradient().IsValid()) {
            SkPaint paint;
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
                paint.setColor(fillState_.GetColor().GetValue());
                paint.setAlphaf(globalState_.GetAlpha()); // set alpha after color
                InitPaintBlend(paint);
                txtStyle.foreground = paint;
                txtStyle.has_foreground = true;
            }
        }
    } else {
        // use foreground to draw stroke
        SkPaint paint = GetStrokePaint();
        InitPaintBlend(paint);
        ConvertTxtStyle(strokeState_.GetTextStyle(), context_, txtStyle);
        txtStyle.font_size = strokeState_.GetTextStyle().GetFontSize().Value();
        if (strokeState_.GetGradient().IsValid()) {
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
}

std::string CanvasPaintMethod::ToDataURL(const std::string& args)
{
    std::string mimeType = GetMimeType(args);
    double quality = GetQuality(args);
    double width = lastLayoutSize_.Width();
    double height = lastLayoutSize_.Height();
    SkBitmap tempCache;
    tempCache.allocPixels(SkImageInfo::Make(width, height, SkColorType::kBGRA_8888_SkColorType,
        (mimeType == IMAGE_JPEG) ? SkAlphaType::kOpaque_SkAlphaType : SkAlphaType::kUnpremul_SkAlphaType));
    bool isGpuEnable = false;
    bool success = false;

    if (!isGpuEnable) {
        if (canvasCache_.empty()) {
            LOGE("Bitmap is empty");
            return UNSUPPORTED;
        }

        success = canvasCache_.pixmap().scalePixels(tempCache.pixmap(), SkFilterQuality::kHigh_SkFilterQuality);
        if (!success) {
            LOGE("scalePixels failed when ToDataURL.");
            return UNSUPPORTED;
        }
    }
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
    if (!success) {
        LOGE("Encode failed when ToDataURL.");
        return UNSUPPORTED;
    }
    auto result = dst.detachAsData();
    if (result == nullptr) {
        LOGE("DetachAsData failed when ToDataURL.");
        return UNSUPPORTED;
    }
    size_t len = SkBase64::Encode(result->data(), result->size(), nullptr);
    if (len > MAX_LENGTH) {
        LOGE("ToDataURL failed, image too large.");
        return UNSUPPORTED;
    }
    SkString info(len);
    SkBase64::Encode(result->data(), result->size(), info.writable_str());
    return std::string(URL_PREFIX).append(mimeType).append(URL_SYMBOL).append(info.c_str());
}
} // namespace OHOS::Ace::NG