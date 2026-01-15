/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#include "compatible/components/canvas/rosen_render_custom_paint.h"


#include "rosen_text/typography.h"
#include "rosen_text/typography_create.h"
#include "rosen_text/typography_style.h"

#include "include/core/SkVertices.h"
#include "include/encode/SkJpegEncoder.h"
#include "include/encode/SkPngEncoder.h"
#include "include/encode/SkWebpEncoder.h"
#ifdef USE_NEW_SKIA
#include "src/base/SkBase64.h"
#else
#include "include/utils/SkBase64.h"
#endif
#include "include/utils/SkParsePath.h"

#include "base/geometry/dimension.h"
#include "base/i18n/localization.h"
#include "base/image/pixel_map.h"
#include "base/json/json_util.h"
#include "base/memory/ace_type.h"
#include "base/utils/linear_map.h"
#include "core/components/common/painter/rosen_decoration_painter.h"
#include "core/components/font/constants_converter.h"
#include "core/components/font/rosen_font_collection.h"
#include "core/components/text/text_theme.h"
#include "core/components_ng/render/adapter/drawing_image.h"
#include "core/image/image_cache.h"
#include "core/pipeline/base/rosen_render_context.h"
#include "core/pipeline/base/constants.h"

namespace OHOS::Ace {
namespace {
constexpr double HANGING_PERCENT = 0.8;
constexpr double HALF_CIRCLE_ANGLE = 180.0;
constexpr double FULL_CIRCLE_ANGLE = 360.0;
constexpr int32_t IMAGE_CACHE_COUNT = 50;
constexpr double DEFAULT_QUALITY = 0.92;
constexpr int32_t MAX_LENGTH = 2048 * 2048;
const std::string UNSUPPORTED = "data:image/png";
const std::string URL_PREFIX = "data:";
const std::string URL_SYMBOL = ";base64,";
const std::string IMAGE_PNG = "image/png";
const std::string IMAGE_JPEG = "image/jpeg";
const std::string IMAGE_WEBP = "image/webp";
const std::u16string ELLIPSIS = u"\u2026";
const std::string FONTWEIGHT = "wght";

// If args is empty or invalid format, use default: image/png
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

template<typename T, typename N>
N ConvertEnumToDrawingEnum(T key, const LinearEnumMapNode<T, N>* map, size_t length, N defaultValue)
{
    int64_t index = BinarySearchFindIndex(map, length, key);
    return index != -1 ? map[index].value : defaultValue;
}

const LinearEnumMapNode<CompositeOperation, RSBlendMode> DRAWING_BLEND_MODE_TABLE[] = {
    { CompositeOperation::SOURCE_OVER, RSBlendMode::SRC_OVER },
    { CompositeOperation::SOURCE_ATOP, RSBlendMode::SRC_ATOP },
    { CompositeOperation::SOURCE_IN, RSBlendMode::SRC_IN },
    { CompositeOperation::SOURCE_OUT, RSBlendMode::SRC_OUT },
    { CompositeOperation::DESTINATION_OVER, RSBlendMode::DST_OVER },
    { CompositeOperation::DESTINATION_ATOP, RSBlendMode::DST_ATOP },
    { CompositeOperation::DESTINATION_IN, RSBlendMode::DST_IN },
    { CompositeOperation::DESTINATION_OUT, RSBlendMode::DST_OUT },
    { CompositeOperation::LIGHTER, RSBlendMode::LIGHTEN },
    { CompositeOperation::COPY, RSBlendMode::SRC },
    { CompositeOperation::XOR, RSBlendMode::XOR },
};
constexpr size_t BLEND_MODE_SIZE = ArraySize(DRAWING_BLEND_MODE_TABLE);

} // namespace

RosenRenderCustomPaint::RosenRenderCustomPaint()
{
    InitImageCallbacks();
}

RosenRenderCustomPaint::~RosenRenderCustomPaint() {}

void RosenRenderCustomPaint::CreateBitmap(double viewScale)
{
    RSBitmapFormat format { RSColorType::COLORTYPE_RGBA_8888, RSAlphaType::ALPHATYPE_UNPREMUL };
    canvasCache_.Free();
    cacheBitmap_.Free();
    canvasCache_.Build(GetLayoutSize().Width() * viewScale, GetLayoutSize().Height() * viewScale, format);
    cacheBitmap_.Build(GetLayoutSize().Width() * viewScale, GetLayoutSize().Height() * viewScale, format);
    canvasCache_.ClearWithColor(RSColor::COLOR_TRANSPARENT);
    cacheBitmap_.ClearWithColor(RSColor::COLOR_TRANSPARENT);
    drawingCanvas_ = std::make_unique<RSCanvas>();
    drawingCanvas_->Bind(canvasCache_);
    cacheCanvas_ = std::make_unique<RSCanvas>();
    cacheCanvas_->Bind(cacheBitmap_);
}

void RosenRenderCustomPaint::Paint(RenderContext& context, const Offset& offset)
{
    ACE_SCOPED_TRACE("RosenRenderCustomPaint::Paint");
    auto canvas = static_cast<RosenRenderContext*>(&context)->GetCanvas();
    if (auto rsNode = static_cast<RosenRenderContext*>(&context)->GetRSNode()) {
        rsNode->SetClipToFrame(true);
    }
    if (!canvas) {
        return;
    }
    auto pipeline = context_.Upgrade();
    if (!pipeline) {
        return;
    }
    // use physical pixel to store bitmap
    double viewScale = pipeline->GetViewScale();
    if (lastLayoutSize_ != GetLayoutSize()) {
        if (GetLayoutSize().IsInfinite()) {
            return;
        }
        CreateBitmap(viewScale);
        lastLayoutSize_ = GetLayoutSize();
    }
    if (!drawingCanvas_) {
        LOGE("drawingCanvas_ is null");
        return;
    }
    drawingCanvas_->Scale(viewScale, viewScale);
    TriggerOnReadyEvent();

    for (const auto& task : tasks_) {
        task(*this, offset);
    }
    drawingCanvas_->Scale(1.0 / viewScale, 1.0 / viewScale);
    tasks_.clear();

    canvas->Save();
    canvas->Scale(1.0 / viewScale, 1.0 / viewScale);
    RSBrush brush;
    canvas->AttachBrush(brush);
    canvas->DrawBitmap(canvasCache_, 0.0f, 0.0f);
    canvas->DetachBrush();
    canvas->Restore();
}

RSPen RosenRenderCustomPaint::GetStrokePaint()
{
    static const LinearEnumMapNode<LineJoinStyle, RSPen::JoinStyle> skLineJoinTable[] = {
        { LineJoinStyle::MITER, RSPen::JoinStyle::MITER_JOIN },
        { LineJoinStyle::ROUND, RSPen::JoinStyle::ROUND_JOIN },
        { LineJoinStyle::BEVEL, RSPen::JoinStyle::BEVEL_JOIN },
    };
    static const LinearEnumMapNode<LineCapStyle, RSPen::CapStyle> skLineCapTable[] = {
        { LineCapStyle::BUTT, RSPen::CapStyle::FLAT_CAP },
        { LineCapStyle::ROUND, RSPen::CapStyle::ROUND_CAP },
        { LineCapStyle::SQUARE, RSPen::CapStyle::SQUARE_CAP },
    };
    RSPen pen;
    pen.SetColor(strokeState_.GetColor().GetValue());
    pen.SetJoinStyle(ConvertEnumToDrawingEnum(
        strokeState_.GetLineJoin(), skLineJoinTable, ArraySize(skLineJoinTable), RSPen::JoinStyle::MITER_JOIN));
    pen.SetCapStyle(ConvertEnumToDrawingEnum(
        strokeState_.GetLineCap(), skLineCapTable, ArraySize(skLineCapTable), RSPen::CapStyle::FLAT_CAP));
    pen.SetWidth(static_cast<RSScalar>(strokeState_.GetLineWidth()));
    pen.SetMiterLimit(static_cast<RSScalar>(strokeState_.GetMiterLimit()));

    // set line Dash
    UpdateLineDash(pen);

    // set global alpha
    if (globalState_.HasGlobalAlpha()) {
        pen.SetAlphaF(globalState_.GetAlpha());
    }
    return pen;
}

std::string RosenRenderCustomPaint::ToDataURL(const std::string& args)
{
    std::string mimeType = GetMimeType(args);
    double quality = GetQuality(args);
    double width = GetLayoutSize().Width();
    double height = GetLayoutSize().Height();
    SkBitmap tempCache;
    tempCache.allocPixels(SkImageInfo::Make(width, height, SkColorType::kBGRA_8888_SkColorType,
        (mimeType == IMAGE_JPEG) ? SkAlphaType::kOpaque_SkAlphaType : SkAlphaType::kUnpremul_SkAlphaType));
    bool isGpuEnable = false;
    bool success = false;
    if (!isGpuEnable) {
        if (!canvasCache_.IsValid()) {
            LOGE("Bitmap is invalid");
            return UNSUPPORTED;
        }
        auto skiaBitmap = canvasCache_.GetImpl<Rosen::Drawing::SkiaBitmap>();
        CHECK_NULL_RETURN(skiaBitmap, UNSUPPORTED);
        auto& skBitmap = skiaBitmap->ExportSkiaBitmap();
        success = skBitmap.pixmap().scalePixels(
            tempCache.pixmap(), SkSamplingOptions(SkCubicResampler { 1 / 3.0f, 1 / 3.0f }));
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
#ifdef USE_NEW_SKIA
    SkBase64::Encode(result->data(), result->size(), info.data());
#else
    SkBase64::Encode(result->data(), result->size(), info.writable_str());
#endif
    return std::string(URL_PREFIX).append(mimeType).append(URL_SYMBOL).append(info.c_str());
}

void RosenRenderCustomPaint::SetAntiAlias(bool isEnabled)
{
    antiAlias_ = isEnabled;
}

void RosenRenderCustomPaint::TransferFromImageBitmap(const RefPtr<OffscreenCanvas>& offscreenCanvas)
{
    std::unique_ptr<ImageData> imageData =
        offscreenCanvas->GetImageData(0, 0, offscreenCanvas->GetWidth(), offscreenCanvas->GetHeight());
    ImageData* imageDataPtr = imageData.get();
    if (imageData != nullptr) {
        PutImageData(Offset(0, 0), *imageDataPtr);
    }
}

void RosenRenderCustomPaint::FillRect(const Offset& offset, const Rect& rect)
{
    RSBrush brush;
    brush.SetAntiAlias(antiAlias_);
    brush.SetColor(fillState_.GetColor().GetValue());
    RSRect drawingRect(rect.Left() + offset.GetX(), rect.Top() + offset.GetY(), rect.Right() + offset.GetX(),
        offset.GetY() + rect.Bottom());
    if (HasShadow()) {
        RSRecordingPath path;
        path.AddRect(drawingRect);
        RosenDecorationPainter::PaintShadow(path, shadow_, drawingCanvas_.get());
    }
    if (fillState_.GetGradient().IsValid()) {
        UpdatePaintShader(offset, nullptr, &brush, fillState_.GetGradient());
    }
    if (fillState_.GetPattern().IsValid()) {
        UpdatePaintShader(fillState_.GetPattern(), nullptr, &brush);
    }
    if (globalState_.HasGlobalAlpha()) {
        brush.SetAlphaF(globalState_.GetAlpha()); // update the global alpha after setting the color
    }
    if (globalState_.GetType() == CompositeOperation::SOURCE_OVER) {
        drawingCanvas_->AttachBrush(brush);
        drawingCanvas_->DrawRect(drawingRect);
        drawingCanvas_->DetachBrush();
    } else {
        cacheCanvas_->AttachBrush(brush);
        cacheCanvas_->DrawRect(drawingRect);
        cacheCanvas_->DetachBrush();
        InitPaintBlend(cacheBrush_);
        drawingCanvas_->AttachBrush(cacheBrush_);
        drawingCanvas_->DrawBitmap(cacheBitmap_, 0, 0);
        drawingCanvas_->DetachBrush();
        cacheBitmap_.ClearWithColor(RSColor::COLOR_TRANSPARENT);
    }
}

void RosenRenderCustomPaint::StrokeRect(const Offset& offset, const Rect& rect)
{
    RSPen pen = GetStrokePaint();
    pen.SetAntiAlias(antiAlias_);
    RSRect drawingRect(rect.Left() + offset.GetX(), rect.Top() + offset.GetY(), rect.Right() + offset.GetX(),
        offset.GetY() + rect.Bottom());
    if (HasShadow()) {
        RSRecordingPath path;
        path.AddRect(drawingRect);
        RosenDecorationPainter::PaintShadow(path, shadow_, drawingCanvas_.get());
    }
    if (strokeState_.GetGradient().IsValid()) {
        UpdatePaintShader(offset, &pen, nullptr, strokeState_.GetGradient());
    }
    if (strokeState_.GetPattern().IsValid()) {
        UpdatePaintShader(strokeState_.GetPattern(), &pen, nullptr);
    }
    if (globalState_.GetType() == CompositeOperation::SOURCE_OVER) {
        drawingCanvas_->AttachPen(pen);
        drawingCanvas_->DrawRect(drawingRect);
        drawingCanvas_->DetachPen();
    } else {
        cacheCanvas_->AttachPen(pen);
        cacheCanvas_->DrawRect(drawingRect);
        cacheCanvas_->DetachPen();
        InitPaintBlend(cacheBrush_);
        drawingCanvas_->AttachBrush(cacheBrush_);
        drawingCanvas_->DrawBitmap(cacheBitmap_, 0, 0);
        drawingCanvas_->DetachBrush();
        cacheBitmap_.ClearWithColor(RSColor::COLOR_TRANSPARENT);
    }
}

void RosenRenderCustomPaint::ClearRect(const Offset& offset, const Rect& rect)
{
    RSBrush brush;
    brush.SetAntiAlias(antiAlias_);
    brush.SetBlendMode(RSBlendMode::CLEAR);
    RSRect drawingRect(rect.Left() + offset.GetX(), rect.Top() + offset.GetY(), rect.Right() + offset.GetX(),
        rect.Bottom() + offset.GetY());
    drawingCanvas_->AttachBrush(brush);
    drawingCanvas_->DrawRect(drawingRect);
    drawingCanvas_->DetachBrush();
}

void RosenRenderCustomPaint::FillText(const Offset& offset, const std::string& text, double x, double y)
{
    if (!UpdateParagraph(offset, text, false, HasShadow())) {
        return;
    }
    PaintText(offset, x, y, false, HasShadow());
}

void RosenRenderCustomPaint::StrokeText(const Offset& offset, const std::string& text, double x, double y)
{
    if (HasShadow()) {
        if (!UpdateParagraph(offset, text, true, true)) {
            return;
        }
        PaintText(offset, x, y, true, true);
    }

    if (!UpdateParagraph(offset, text, true)) {
        return;
    }
    PaintText(offset, x, y, true);
}



double RosenRenderCustomPaint::MeasureText(const std::string& text, const PaintState& state)
{
    using namespace Constants;
    Rosen::TypographyStyle style;
    style.textAlign = ConvertTxtTextAlign(state.GetTextAlign());
    auto fontCollection = RosenFontCollection::GetInstance().GetFontCollection();
    if (!fontCollection) {
        LOGW("MeasureText: fontCollection is null");
        return 0.0;
    }
    std::unique_ptr<Rosen::TypographyCreate> builder = Rosen::TypographyCreate::Create(style, fontCollection);
    Rosen::TextStyle txtStyle;
    ConvertTxtStyle(state.GetTextStyle(), context_, txtStyle);
    txtStyle.fontSize = state.GetTextStyle().GetFontSize().Value();
    builder->PushStyle(txtStyle);
    builder->AppendText(StringUtils::Str8ToStr16(text));
    auto paragraph = builder->CreateTypography();
    paragraph->Layout(Size::INFINITE_SIZE);
    return paragraph->GetMaxIntrinsicWidth();
}

double RosenRenderCustomPaint::MeasureTextHeight(const std::string& text, const PaintState& state)
{
    using namespace Constants;
    Rosen::TypographyStyle style;
    style.textAlign = ConvertTxtTextAlign(state.GetTextAlign());
    auto fontCollection = RosenFontCollection::GetInstance().GetFontCollection();
    if (!fontCollection) {
        LOGW("MeasureText: fontCollection is null");
        return 0.0;
    }
    std::unique_ptr<Rosen::TypographyCreate> builder = Rosen::TypographyCreate::Create(style, fontCollection);
    Rosen::TextStyle txtStyle;
    ConvertTxtStyle(state.GetTextStyle(), context_, txtStyle);
    txtStyle.fontSize = state.GetTextStyle().GetFontSize().Value();
    builder->PushStyle(txtStyle);
    builder->AppendText(StringUtils::Str8ToStr16(text));
    auto paragraph = builder->CreateTypography();
    paragraph->Layout(Size::INFINITE_SIZE);
    return paragraph->GetHeight();
}

TextMetrics RosenRenderCustomPaint::MeasureTextMetrics(const std::string& text, const PaintState& state)
{
    using namespace Constants;
    Rosen::TypographyStyle style;
    style.textAlign = ConvertTxtTextAlign(state.GetTextAlign());
    auto fontCollection = RosenFontCollection::GetInstance().GetFontCollection();
    if (!fontCollection) {
        LOGW("MeasureText: fontCollection is null");
        return { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
    }
    std::unique_ptr<Rosen::TypographyCreate> builder = Rosen::TypographyCreate::Create(style, fontCollection);
    Rosen::TextStyle txtStyle;
    ConvertTxtStyle(state.GetTextStyle(), context_, txtStyle);
    txtStyle.fontSize = state.GetTextStyle().GetFontSize().Value();
    builder->PushStyle(txtStyle);
    builder->AppendText(StringUtils::Str8ToStr16(text));
    auto paragraph = builder->CreateTypography();
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

void RosenRenderCustomPaint::PaintText(const Offset& offset, double x, double y, bool isStroke, bool hasShadow)
{
    paragraph_->Layout(GetLayoutSize().Width());
    if (GetLayoutSize().Width() > paragraph_->GetMaxIntrinsicWidth()) {
        paragraph_->Layout(std::ceil(paragraph_->GetMaxIntrinsicWidth()));
    }
    if (hasShadow) {
        drawingCanvas_->Save();
        LOGE("Drawing is not supported");
        drawingCanvas_->Restore();
        return;
    }

    LOGE("Drawing is not supported");
}

double RosenRenderCustomPaint::GetAlignOffset(TextAlign align, std::unique_ptr<Rosen::Typography>& paragraph)
{
    double x = 0.0;
    switch (align) {
        case TextAlign::LEFT:
            x = 0.0;
            break;
        case TextAlign::START:
            x = (GetTextDirection() == TextDirection::LTR) ? 0.0 : -paragraph->GetMaxIntrinsicWidth();
            break;
        case TextAlign::RIGHT:
            x = -paragraph->GetMaxIntrinsicWidth();
            break;
        case TextAlign::END:
            x = (GetTextDirection() == TextDirection::LTR) ? -paragraph->GetMaxIntrinsicWidth() : 0.0;
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

double RosenRenderCustomPaint::GetBaselineOffset(TextBaseline baseline, std::unique_ptr<Rosen::Typography>& paragraph)
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

void RosenRenderCustomPaint::MoveTo(const Offset& offset, double x, double y)
{
    drawingPath_.MoveTo(static_cast<RSScalar>(x + offset.GetX()), static_cast<RSScalar>(y + offset.GetY()));
}

void RosenRenderCustomPaint::LineTo(const Offset& offset, double x, double y)
{
    drawingPath_.LineTo(static_cast<RSScalar>(x + offset.GetX()), static_cast<RSScalar>(y + offset.GetY()));
}

void RosenRenderCustomPaint::BezierCurveTo(const Offset& offset, const BezierCurveParam& param)
{
    drawingPath_.CubicTo(static_cast<RSScalar>(param.cp1x + offset.GetX()),
        static_cast<RSScalar>(param.cp1y + offset.GetY()), static_cast<RSScalar>(param.cp2x + offset.GetX()),
        static_cast<RSScalar>(param.cp2y + offset.GetY()), static_cast<RSScalar>(param.x + offset.GetX()),
        static_cast<RSScalar>(param.y + offset.GetY()));
}

void RosenRenderCustomPaint::QuadraticCurveTo(const Offset& offset, const QuadraticCurveParam& param)
{
    drawingPath_.QuadTo(static_cast<RSScalar>(param.cpx + offset.GetX()),
        static_cast<RSScalar>(param.cpy + offset.GetY()), static_cast<RSScalar>(param.x + offset.GetX()),
        static_cast<RSScalar>(param.y + offset.GetY()));
}

void RosenRenderCustomPaint::Arc(const Offset& offset, const ArcParam& param)
{
    double left = param.x - param.radius + offset.GetX();
    double top = param.y - param.radius + offset.GetY();
    double right = param.x + param.radius + offset.GetX();
    double bottom = param.y + param.radius + offset.GetY();
    double startAngle = param.startAngle * HALF_CIRCLE_ANGLE / ACE_PI;
    double endAngle = param.endAngle * HALF_CIRCLE_ANGLE / ACE_PI;
    double sweepAngle = endAngle - startAngle;
    if (param.anticlockwise) {
        sweepAngle =
            endAngle > startAngle ? (std::fmod(sweepAngle, FULL_CIRCLE_ANGLE) - FULL_CIRCLE_ANGLE) : sweepAngle;
    } else {
        sweepAngle =
            endAngle > startAngle ? sweepAngle : (std::fmod(sweepAngle, FULL_CIRCLE_ANGLE) + FULL_CIRCLE_ANGLE);
    }
    RSPoint point1(left, top);
    RSPoint point2(right, bottom);
    if (NearEqual(std::fmod(sweepAngle, FULL_CIRCLE_ANGLE), 0.0) && !NearEqual(startAngle, endAngle)) {
        // draw circle
        double half = GreatNotEqual(sweepAngle, 0.0) ? HALF_CIRCLE_ANGLE : -HALF_CIRCLE_ANGLE;
        drawingPath_.ArcTo(point1, point2, static_cast<RSScalar>(startAngle), static_cast<RSScalar>(half));
        drawingPath_.ArcTo(point1, point2, static_cast<RSScalar>(half + startAngle), static_cast<RSScalar>(half));
    } else if (!NearEqual(std::fmod(sweepAngle, FULL_CIRCLE_ANGLE), 0.0) && abs(sweepAngle) > FULL_CIRCLE_ANGLE) {
        double half = GreatNotEqual(sweepAngle, 0.0) ? HALF_CIRCLE_ANGLE : -HALF_CIRCLE_ANGLE;
        drawingPath_.ArcTo(point1, point2, static_cast<RSScalar>(startAngle), static_cast<RSScalar>(half));
        drawingPath_.ArcTo(point1, point2, static_cast<RSScalar>(half + startAngle), static_cast<RSScalar>(half));
        drawingPath_.ArcTo(
            point1, point2, static_cast<RSScalar>(half + half + startAngle), static_cast<RSScalar>(sweepAngle));
    } else {
        drawingPath_.ArcTo(point1, point2, static_cast<RSScalar>(startAngle), static_cast<RSScalar>(sweepAngle));
    }
}

void RosenRenderCustomPaint::ArcTo(const Offset& offset, const ArcToParam& param)
{
    LOGE("Drawing is not supported");
}

void RosenRenderCustomPaint::Ellipse(const Offset& offset, const EllipseParam& param)
{
    // Init the start and end angle, then calculated the sweepAngle.
    double startAngle = std::fmod(param.startAngle, ACE_PI * 2.0);
    double endAngle = std::fmod(param.endAngle, ACE_PI * 2.0);
    startAngle = (startAngle < 0.0 ? startAngle + ACE_PI * 2.0 : startAngle) * HALF_CIRCLE_ANGLE / ACE_PI;
    endAngle = (endAngle < 0.0 ? endAngle + ACE_PI * 2.0 : endAngle) * HALF_CIRCLE_ANGLE / ACE_PI;
    if (NearEqual(param.startAngle, param.endAngle)) {
        return; // Just return when startAngle is same as endAngle.
    }
    double rotation = param.rotation * HALF_CIRCLE_ANGLE / ACE_PI;
    double sweepAngle = endAngle - startAngle;
    if (param.anticlockwise) {
        if (sweepAngle > 0.0) { // Make sure the sweepAngle is negative when anticlockwise.
            sweepAngle -= FULL_CIRCLE_ANGLE;
        }
    } else {
        if (sweepAngle < 0.0) { // Make sure the sweepAngle is positive when clockwise.
            sweepAngle += FULL_CIRCLE_ANGLE;
        }
    }

    // Init the oval Rect(left, top, right, bottom).
    double left = param.x - param.radiusX + offset.GetX();
    double top = param.y - param.radiusY + offset.GetY();
    double right = param.x + param.radiusX + offset.GetX();
    double bottom = param.y + param.radiusY + offset.GetY();
    RSPoint point1(left, top);
    RSPoint point2(right, bottom);
    if (!NearZero(rotation)) {
        RSMatrix matrix;
        matrix.Rotate(-rotation, param.x + offset.GetX(), param.y + offset.GetY());
        drawingPath_.Transform(matrix);
    }
    if (NearZero(sweepAngle) && !NearZero(param.endAngle - param.startAngle)) {
        // The entire ellipse needs to be drawn with two arcTo.
        drawingPath_.ArcTo(point1, point2, startAngle, HALF_CIRCLE_ANGLE);
        drawingPath_.ArcTo(point1, point2, startAngle + HALF_CIRCLE_ANGLE, HALF_CIRCLE_ANGLE);
    } else {
        drawingPath_.ArcTo(point1, point2, startAngle, sweepAngle);
    }
    if (!NearZero(rotation)) {
        RSMatrix matrix;
        matrix.Rotate(rotation, param.x + offset.GetX(), param.y + offset.GetY());
        drawingPath_.Transform(matrix);
    }
}

void RosenRenderCustomPaint::AddRect(const Offset& offset, const Rect& rect)
{
    RSRect drawingRect(rect.Left() + offset.GetX(), rect.Top() + offset.GetY(), rect.Right() + offset.GetX(),
        offset.GetY() + rect.Bottom());
    drawingPath_.AddRect(drawingRect);
}

void RosenRenderCustomPaint::SetFillRuleForPath(const CanvasFillRule& rule)
{
    if (rule == CanvasFillRule::NONZERO) {
        drawingPath_.SetFillStyle(RSPathFillType::WINDING);
    } else if (rule == CanvasFillRule::EVENODD) {
        drawingPath_.SetFillStyle(RSPathFillType::EVENTODD);
    }
}

void RosenRenderCustomPaint::SetFillRuleForPath2D(const CanvasFillRule& rule)
{
    if (rule == CanvasFillRule::NONZERO) {
        drawingPath2d_.SetFillStyle(RSPathFillType::WINDING);
    } else if (rule == CanvasFillRule::EVENODD) {
        drawingPath2d_.SetFillStyle(RSPathFillType::EVENTODD);
    }
}

void RosenRenderCustomPaint::ParsePath2D(const Offset& offset, const RefPtr<CanvasPath2D>& path)
{
    for (const auto& [cmd, args] : path->GetCaches()) {
        switch (cmd) {
            case PathCmd::CMDS: {
                Path2DAddPath(offset, args);
                break;
            }
            case PathCmd::TRANSFORM: {
                Path2DSetTransform(offset, args);
                break;
            }
            case PathCmd::MOVE_TO: {
                Path2DMoveTo(offset, args);
                break;
            }
            case PathCmd::LINE_TO: {
                Path2DLineTo(offset, args);
                break;
            }
            case PathCmd::ARC: {
                Path2DArc(offset, args);
                break;
            }
            case PathCmd::ARC_TO: {
                Path2DArcTo(offset, args);
                break;
            }
            case PathCmd::QUADRATIC_CURVE_TO: {
                Path2DQuadraticCurveTo(offset, args);
                break;
            }
            case PathCmd::BEZIER_CURVE_TO: {
                Path2DBezierCurveTo(offset, args);
                break;
            }
            case PathCmd::ELLIPSE: {
                Path2DEllipse(offset, args);
                break;
            }
            case PathCmd::RECT: {
                Path2DRect(offset, args);
                break;
            }
            case PathCmd::CLOSE_PATH: {
                Path2DClosePath(offset, args);
                break;
            }
            default: {
                break;
            }
        }
    }
}

void RosenRenderCustomPaint::Fill(const Offset& offset)
{
    RSBrush brush;
    brush.SetAntiAlias(antiAlias_);
    brush.SetColor(fillState_.GetColor().GetValue());
    if (HasShadow()) {
        RosenDecorationPainter::PaintShadow(drawingPath_, shadow_, drawingCanvas_.get());
    }
    if (fillState_.GetGradient().IsValid()) {
        UpdatePaintShader(offset, nullptr, &brush, fillState_.GetGradient());
    }
    if (fillState_.GetPattern().IsValid()) {
        UpdatePaintShader(fillState_.GetPattern(), nullptr, &brush);
    }
    if (globalState_.HasGlobalAlpha()) {
        brush.SetAlphaF(globalState_.GetAlpha());
    }
    if (globalState_.GetType() == CompositeOperation::SOURCE_OVER) {
        drawingCanvas_->AttachBrush(brush);
        drawingCanvas_->DrawPath(drawingPath_);
        drawingCanvas_->DetachBrush();
    } else {
        cacheCanvas_->AttachBrush(brush);
        cacheCanvas_->DrawPath(drawingPath_);
        cacheCanvas_->DetachBrush();
        InitPaintBlend(cacheBrush_);
        drawingCanvas_->AttachBrush(cacheBrush_);
        drawingCanvas_->DrawBitmap(cacheBitmap_, 0, 0);
        drawingCanvas_->DetachBrush();
        cacheBitmap_.ClearWithColor(RSColor::COLOR_TRANSPARENT);
    }
}

void RosenRenderCustomPaint::Fill(const Offset& offset, const RefPtr<CanvasPath2D>& path)
{
    if (path == nullptr) {
        LOGE("Fill failed, target path is null.");
        return;
    }
    ParsePath2D(offset, path);
    Path2DFill(offset);
    drawingPath2d_.Reset();
}

void RosenRenderCustomPaint::Stroke(const Offset& offset)
{
    RSPen pen = GetStrokePaint();
    pen.SetAntiAlias(antiAlias_);
    if (HasShadow()) {
        RosenDecorationPainter::PaintShadow(drawingPath_, shadow_, drawingCanvas_.get());
    }
    if (strokeState_.GetGradient().IsValid()) {
        UpdatePaintShader(offset, &pen, nullptr, strokeState_.GetGradient());
    }
    if (strokeState_.GetPattern().IsValid()) {
        UpdatePaintShader(strokeState_.GetPattern(), &pen, nullptr);
    }
    if (globalState_.GetType() == CompositeOperation::SOURCE_OVER) {
        drawingCanvas_->AttachPen(pen);
        drawingCanvas_->DrawPath(drawingPath_);
        drawingCanvas_->DetachPen();
    } else {
        cacheCanvas_->AttachPen(pen);
        cacheCanvas_->DrawPath(drawingPath_);
        cacheCanvas_->DetachPen();
        InitPaintBlend(cacheBrush_);
        drawingCanvas_->AttachBrush(cacheBrush_);
        drawingCanvas_->DrawBitmap(cacheBitmap_, 0, 0);
        drawingCanvas_->DetachBrush();
        cacheBitmap_.ClearWithColor(RSColor::COLOR_TRANSPARENT);
    }
}

void RosenRenderCustomPaint::Stroke(const Offset& offset, const RefPtr<CanvasPath2D>& path)
{
    if (path == nullptr) {
        LOGE("Stroke failed, target path is null.");
        return;
    }
    ParsePath2D(offset, path);
    Path2DStroke(offset);
    drawingPath2d_.Reset();
}

void RosenRenderCustomPaint::Path2DAddPath(const Offset& offset, const PathArgs& args)
{
    RSRecordingPath out;
    out.BuildFromSVGString(args.cmds);
    drawingPath2d_.AddPath(out);
}

void RosenRenderCustomPaint::Path2DSetTransform(const Offset& offset, const PathArgs& args)
{
    RSMatrix matrix;
    double scaleX = args.para1;
    double skewX = args.para2;
    double skewY = args.para3;
    double scaleY = args.para4;
    double translateX = args.para5;
    double translateY = args.para6;
    matrix.SetMatrix(scaleX, skewY, translateX, skewX, scaleY, translateY, 0, 0, 1);
    drawingPath2d_.Transform(matrix);
}

void RosenRenderCustomPaint::Path2DMoveTo(const Offset& offset, const PathArgs& args)
{
    double x = args.para1 + offset.GetX();
    double y = args.para2 + offset.GetY();
    drawingPath2d_.MoveTo(x, y);
}

void RosenRenderCustomPaint::Path2DLineTo(const Offset& offset, const PathArgs& args)
{
    double x = args.para1 + offset.GetX();
    double y = args.para2 + offset.GetY();
    drawingPath2d_.LineTo(x, y);
}

void RosenRenderCustomPaint::Path2DArc(const Offset& offset, const PathArgs& args)
{
    double x = args.para1;
    double y = args.para2;
    double r = args.para3;
    RSPoint point1(x - r + offset.GetX(), y - r + offset.GetY());
    RSPoint point2(x + r + offset.GetX(), y + r + offset.GetY());
    double startAngle = args.para4 * HALF_CIRCLE_ANGLE / ACE_PI;
    double endAngle = args.para5 * HALF_CIRCLE_ANGLE / ACE_PI;
    double sweepAngle = endAngle - startAngle;
    if (!NearZero(args.para6)) {
        sweepAngle =
            endAngle > startAngle ? (std::fmod(sweepAngle, FULL_CIRCLE_ANGLE) - FULL_CIRCLE_ANGLE) : sweepAngle;
    } else {
        sweepAngle =
            endAngle > startAngle ? sweepAngle : (std::fmod(sweepAngle, FULL_CIRCLE_ANGLE) + FULL_CIRCLE_ANGLE);
    }

    if (NearEqual(std::fmod(sweepAngle, FULL_CIRCLE_ANGLE), 0.0) && !NearEqual(startAngle, endAngle)) {
        drawingPath2d_.ArcTo(point1, point2, startAngle, HALF_CIRCLE_ANGLE);
        drawingPath2d_.ArcTo(point1, point2, startAngle + HALF_CIRCLE_ANGLE, HALF_CIRCLE_ANGLE);
    } else if (!NearEqual(std::fmod(sweepAngle, FULL_CIRCLE_ANGLE), 0.0) && abs(sweepAngle) > FULL_CIRCLE_ANGLE) {
        drawingPath2d_.ArcTo(point1, point2, startAngle, HALF_CIRCLE_ANGLE);
        drawingPath2d_.ArcTo(point1, point2, startAngle + HALF_CIRCLE_ANGLE, HALF_CIRCLE_ANGLE);
        drawingPath2d_.ArcTo(point1, point2, startAngle + HALF_CIRCLE_ANGLE + HALF_CIRCLE_ANGLE, sweepAngle);
    } else {
        drawingPath2d_.ArcTo(point1, point2, startAngle, sweepAngle);
    }
}

void RosenRenderCustomPaint::Path2DArcTo(const Offset& offset, const PathArgs& args)
{
    LOGE("Drawing is not supported");
}

void RosenRenderCustomPaint::Path2DQuadraticCurveTo(const Offset& offset, const PathArgs& args)
{
    double cpx = args.para1 + offset.GetX();
    double cpy = args.para2 + offset.GetY();
    double x = args.para3 + offset.GetX();
    double y = args.para4 + offset.GetY();
    drawingPath2d_.QuadTo(cpx, cpy, x, y);
}

void RosenRenderCustomPaint::Path2DBezierCurveTo(const Offset& offset, const PathArgs& args)
{
    double cp1x = args.para1 + offset.GetX();
    double cp1y = args.para2 + offset.GetY();
    double cp2x = args.para3 + offset.GetX();
    double cp2y = args.para4 + offset.GetY();
    double x = args.para5 + offset.GetX();
    double y = args.para6 + offset.GetY();
    drawingPath2d_.CubicTo(cp1x, cp1y, cp2x, cp2y, x, y);
}

void RosenRenderCustomPaint::Path2DEllipse(const Offset& offset, const PathArgs& args)
{
    if (NearEqual(args.para6, args.para7)) {
        return; // Just return when startAngle is same as endAngle.
    }

    double x = args.para1;
    double y = args.para2;
    double rx = args.para3;
    double ry = args.para4;
    double rotation = args.para5 * HALF_CIRCLE_ANGLE / ACE_PI;
    double startAngle = std::fmod(args.para6, ACE_PI * 2.0);
    double endAngle = std::fmod(args.para7, ACE_PI * 2.0);
    bool anticlockwise = NearZero(args.para8) ? false : true;
    startAngle = (startAngle < 0.0 ? startAngle + ACE_PI * 2.0 : startAngle) * HALF_CIRCLE_ANGLE / ACE_PI;
    endAngle = (endAngle < 0.0 ? endAngle + ACE_PI * 2.0 : endAngle) * HALF_CIRCLE_ANGLE / ACE_PI;
    double sweepAngle = endAngle - startAngle;
    if (anticlockwise) {
        if (sweepAngle > 0.0) { // Make sure the sweepAngle is negative when anticlockwise.
            sweepAngle -= FULL_CIRCLE_ANGLE;
        }
    } else {
        if (sweepAngle < 0.0) { // Make sure the sweepAngle is positive when clockwise.
            sweepAngle += FULL_CIRCLE_ANGLE;
        }
    }
    RSPoint point1(x - rx + offset.GetX(), y - ry + offset.GetY());
    RSPoint point2(x + rx + offset.GetX(), y + ry + offset.GetY());

    if (!NearZero(rotation)) {
        RSMatrix matrix;
        matrix.Rotate(-rotation, x + offset.GetX(), y + offset.GetY());
        drawingPath2d_.Transform(matrix);
    }
    if (NearZero(sweepAngle) && !NearZero(args.para6 - args.para7)) {
        // The entire ellipse needs to be drawn with two arcTo.
        drawingPath2d_.ArcTo(point1, point2, startAngle, HALF_CIRCLE_ANGLE);
        drawingPath2d_.ArcTo(point1, point2, startAngle + HALF_CIRCLE_ANGLE, HALF_CIRCLE_ANGLE);
    } else {
        drawingPath2d_.ArcTo(point1, point2, startAngle, sweepAngle);
    }
    if (!NearZero(rotation)) {
        RSMatrix matrix;
        matrix.Rotate(rotation, x + offset.GetX(), y + offset.GetY());
        drawingPath2d_.Transform(matrix);
    }
}

void RosenRenderCustomPaint::Path2DRect(const Offset& offset, const PathArgs& args)
{
    double left = args.para1 + offset.GetX();
    double top = args.para2 + offset.GetY();
    double right = args.para3 + args.para1 + offset.GetX();
    double bottom = args.para4 + args.para2 + offset.GetY();
    drawingPath2d_.AddRect(RSRect(left, top, right, bottom));
}

void RosenRenderCustomPaint::Path2DClosePath(const Offset& offset, const PathArgs& args)
{
    drawingPath2d_.Close();
}

void RosenRenderCustomPaint::Path2DStroke(const Offset& offset)
{
    RSPen pen = GetStrokePaint();
    pen.SetAntiAlias(antiAlias_);
    if (HasShadow()) {
        RosenDecorationPainter::PaintShadow(drawingPath2d_, shadow_, drawingCanvas_.get());
    }
    if (strokeState_.GetGradient().IsValid()) {
        UpdatePaintShader(offset, &pen, nullptr, strokeState_.GetGradient());
    }
    if (strokeState_.GetPattern().IsValid()) {
        UpdatePaintShader(strokeState_.GetPattern(), &pen, nullptr);
    }
    if (globalState_.GetType() == CompositeOperation::SOURCE_OVER) {
        drawingCanvas_->AttachPen(pen);
        drawingCanvas_->DrawPath(drawingPath2d_);
        drawingCanvas_->DetachPen();
    } else {
        cacheCanvas_->AttachPen(pen);
        cacheCanvas_->DrawPath(drawingPath2d_);
        cacheCanvas_->DetachPen();
        InitPaintBlend(cacheBrush_);
        drawingCanvas_->AttachBrush(cacheBrush_);
        drawingCanvas_->DrawBitmap(cacheBitmap_, 0, 0);
        drawingCanvas_->DetachBrush();
        cacheBitmap_.ClearWithColor(RSColor::COLOR_TRANSPARENT);
    }
}

void RosenRenderCustomPaint::Path2DFill(const Offset& offset)
{
    RSBrush brush;
    brush.SetAntiAlias(antiAlias_);
    brush.SetColor(fillState_.GetColor().GetValue());
    if (HasShadow()) {
        RosenDecorationPainter::PaintShadow(drawingPath2d_, shadow_, drawingCanvas_.get());
    }
    if (fillState_.GetGradient().IsValid()) {
        UpdatePaintShader(offset, nullptr, &brush, fillState_.GetGradient());
    }
    if (fillState_.GetPattern().IsValid()) {
        UpdatePaintShader(fillState_.GetPattern(), nullptr, &brush);
    }
    if (globalState_.HasGlobalAlpha()) {
        brush.SetAlphaF(globalState_.GetAlpha());
    }
    if (globalState_.GetType() == CompositeOperation::SOURCE_OVER) {
        drawingCanvas_->AttachBrush(brush);
        drawingCanvas_->DrawPath(drawingPath2d_);
        drawingCanvas_->DetachBrush();
    } else {
        cacheCanvas_->AttachBrush(brush);
        cacheCanvas_->DrawPath(drawingPath2d_);
        cacheCanvas_->DetachBrush();
        InitPaintBlend(cacheBrush_);
        drawingCanvas_->AttachBrush(cacheBrush_);
        drawingCanvas_->DrawBitmap(cacheBitmap_, 0, 0);
        drawingCanvas_->DetachBrush();
        cacheBitmap_.ClearWithColor(RSColor::COLOR_TRANSPARENT);
    }
}

void RosenRenderCustomPaint::Path2DClip()
{
    drawingCanvas_->ClipPath(drawingPath2d_, RSClipOp::INTERSECT);
}

void RosenRenderCustomPaint::Clip()
{
    drawingCanvas_->ClipPath(drawingPath_, RSClipOp::INTERSECT);
}

void RosenRenderCustomPaint::Clip(const RefPtr<CanvasPath2D>& path)
{
    if (path == nullptr) {
        LOGE("Fill failed, target path is null.");
        return;
    }
    auto offset = Offset(0, 0);
    ParsePath2D(offset, path);
    Path2DClip();
    drawingPath2d_.Reset();
}

void RosenRenderCustomPaint::BeginPath()
{
    drawingPath_.Reset();
}

void RosenRenderCustomPaint::ResetTransform()
{
    drawingCanvas_->ResetMatrix();
}

void RosenRenderCustomPaint::ClosePath()
{
    drawingPath_.Close();
}

void RosenRenderCustomPaint::Save()
{
    SaveStates();
    drawingCanvas_->Save();
}

void RosenRenderCustomPaint::Restore()
{
    RestoreStates();
    drawingCanvas_->Restore();
}

void RosenRenderCustomPaint::InitImagePaint()
{
    auto filter = imageBrush_.GetFilter();
    if (smoothingEnabled_) {
        if (smoothingQuality_ == "low") {
            options_ = RSSamplingOptions(RSFilterMode::LINEAR, RSMipmapMode::NONE);
            filter.SetFilterQuality(RSFilter::FilterQuality::LOW);
            imageBrush_.SetFilter(filter);
        } else if (smoothingQuality_ == "medium") {
            options_ = RSSamplingOptions(RSFilterMode::LINEAR, RSMipmapMode::LINEAR);
            filter.SetFilterQuality(RSFilter::FilterQuality::MEDIUM);
            imageBrush_.SetFilter(filter);
        } else if (smoothingQuality_ == "high") {
            options_ = RSSamplingOptions(RSCubicResampler::Mitchell());
            filter.SetFilterQuality(RSFilter::FilterQuality::HIGH);
            imageBrush_.SetFilter(filter);
        } else {
            LOGE("Unsupported Quality type:%{public}s", smoothingQuality_.c_str());
        }
    } else {
        options_ = RSSamplingOptions(RSFilterMode::NEAREST, RSMipmapMode::NONE);
        filter.SetFilterQuality(RSFilter::FilterQuality::NONE);
        imageBrush_.SetFilter(filter);
    }
}

void RosenRenderCustomPaint::InitPaintBlend(RSBrush& brush)
{
    brush.SetBlendMode(ConvertEnumToDrawingEnum(
        globalState_.GetType(), DRAWING_BLEND_MODE_TABLE, BLEND_MODE_SIZE, RSBlendMode::SRC_OVER));
}

bool RosenRenderCustomPaint::UpdateParagraph(
    const Offset& offset, const std::string& text, bool isStroke, bool hasShadow)
{
    using namespace Constants;
    Rosen::TypographyStyle style;
    if (isStroke) {
        style.textAlign = ConvertTxtTextAlign(strokeState_.GetTextAlign());
    } else {
        style.textAlign = ConvertTxtTextAlign(fillState_.GetTextAlign());
    }
    auto fontCollection = RosenFontCollection::GetInstance().GetFontCollection();
    if (!fontCollection) {
        LOGW("UpdateParagraph: fontCollection is null");
        return false;
    }
    std::unique_ptr<Rosen::TypographyCreate> builder = Rosen::TypographyCreate::Create(style, fontCollection);
    Rosen::TextStyle txtStyle;
    if (!isStroke && hasShadow) {
        Rosen::TextShadow txtShadow;
        txtShadow.color = shadow_.GetColor().GetValue();
        txtShadow.offset.SetX(shadow_.GetOffset().GetX());
        txtShadow.offset.SetY(shadow_.GetOffset().GetY());
        txtShadow.blurRadius = shadow_.GetBlurRadius();
        txtStyle.shadows.emplace_back(txtShadow);
    }
    txtStyle.locale = Localization::GetInstance()->GetFontLocale();
    UpdateTextStyleForeground(offset, isStroke, txtStyle, hasShadow);
    builder->PushStyle(txtStyle);
    builder->AppendText(StringUtils::Str8ToStr16(text));
    paragraph_ = builder->CreateTypography();
    return true;
}

void RosenRenderCustomPaint::UpdateTextStyleForeground(
    const Offset& offset, bool isStroke, Rosen::TextStyle& txtStyle, bool hasShadow)
{
    using namespace Constants;
    LOGE("Drawing is not supported");
}

bool RosenRenderCustomPaint::HasShadow() const
{
    return !(NearZero(shadow_.GetOffset().GetX()) && NearZero(shadow_.GetOffset().GetY()) &&
             NearZero(shadow_.GetBlurRadius()));
}

void RosenRenderCustomPaint::UpdatePaintShader(
    const Offset& offset, RSPen* pen, RSBrush* brush, const Gradient& gradient)
{
    RSPoint beginPoint = RSPoint(static_cast<RSScalar>(gradient.GetBeginOffset().GetX() + offset.GetX()),
        static_cast<RSScalar>(gradient.GetBeginOffset().GetY() + offset.GetY()));
    RSPoint endPoint = RSPoint(static_cast<RSScalar>(gradient.GetEndOffset().GetX() + offset.GetX()),
        static_cast<RSScalar>(gradient.GetEndOffset().GetY() + offset.GetY()));
    std::vector<RSPoint> pts = { beginPoint, endPoint };
    auto gradientColors = gradient.GetColors();
    std::stable_sort(gradientColors.begin(), gradientColors.end(),
        [](auto& colorA, auto& colorB) { return colorA.GetDimension() < colorB.GetDimension(); });
    uint32_t colorsSize = gradientColors.size();
    std::vector<RSColorQuad> colors(gradientColors.size(), 0);
    std::vector<RSScalar> pos(gradientColors.size(), 0);
    for (uint32_t i = 0; i < colorsSize; ++i) {
        const auto& gradientColor = gradientColors[i];
        colors.at(i) = gradientColor.GetColor().GetValue();
        pos.at(i) = gradientColor.GetDimension().Value();
    }

    auto mode = RSTileMode::CLAMP;

    std::shared_ptr<RSShaderEffect> shaderEffect = nullptr;
    if (gradient.GetType() == GradientType::LINEAR) {
        shaderEffect = RSShaderEffect::CreateLinearGradient(pts.at(0), pts.at(1), colors, pos, mode);
    } else {
        if (gradient.GetInnerRadius() <= 0.0 && beginPoint == endPoint) {
            shaderEffect =
                RSShaderEffect::CreateRadialGradient(pts.at(1), gradient.GetOuterRadius(), colors, pos, mode);
        } else {
            RSMatrix matrix;
            shaderEffect = RSShaderEffect::CreateTwoPointConical(pts.at(0), gradient.GetInnerRadius(), pts.at(1),
                gradient.GetOuterRadius(), colors, pos, mode, &matrix);
        }
    }
    if (pen != nullptr) {
        pen->SetShaderEffect(shaderEffect);
    }
    if (brush != nullptr) {
        brush->SetShaderEffect(shaderEffect);
    }
}

void RosenRenderCustomPaint::Rotate(double angle)
{
    drawingCanvas_->Rotate(angle * 180 / ACE_PI);
}

void RosenRenderCustomPaint::Scale(double x, double y)
{
    drawingCanvas_->Scale(x, y);
}

void RosenRenderCustomPaint::SetTransform(const TransformParam& param)
{
    auto pipeline = context_.Upgrade();
    if (!pipeline) {
        return;
    }
    // use physical pixel to store bitmap
    double viewScale = pipeline->GetViewScale();
    RSMatrix matrix;
    matrix.SetMatrix(param.scaleX * viewScale, param.skewY * viewScale, param.translateX * viewScale,
        param.skewX * viewScale, param.scaleY * viewScale, param.translateY * viewScale, 0, 0, 1);
    drawingCanvas_->SetMatrix(matrix);
}

void RosenRenderCustomPaint::Transform(const TransformParam& param)
{
    RSMatrix matrix;
    matrix.SetMatrix(param.scaleX, param.skewY, param.translateX, param.skewX, param.scaleY, param.translateY, 0, 0, 1);
    drawingCanvas_->ConcatMatrix(matrix);
}

void RosenRenderCustomPaint::Translate(double x, double y)
{
    drawingCanvas_->Translate(x, y);
}

void RosenRenderCustomPaint::UpdateLineDash(RSPen& pen)
{
    if (!strokeState_.GetLineDash().lineDash.empty()) {
        auto lineDashState = strokeState_.GetLineDash().lineDash;
        RSScalar intervals[lineDashState.size()];
        for (size_t i = 0; i < lineDashState.size(); ++i) {
            intervals[i] = static_cast<RSScalar>(lineDashState[i]);
        }
        RSScalar phase = static_cast<RSScalar>(strokeState_.GetLineDash().dashOffset);
        pen.SetPathEffect(RSPathEffect::CreateDashPathEffect(intervals, lineDashState.size(), phase));
    }
}

void RosenRenderCustomPaint::InitImageCallbacks()
{
    imageObjSuccessCallback_ = [weak = AceType::WeakClaim(this)](
                                   ImageSourceInfo info, const RefPtr<ImageObject>& imageObj) {
        auto render = weak.Upgrade();
        if (render->loadingSource_ == info) {
            render->ImageObjReady(imageObj);
            return;
        } else {
            LOGE("image sourceInfo_ check error, : %{public}s vs %{public}s", render->loadingSource_.ToString().c_str(),
                info.ToString().c_str());
        }
    };

    failedCallback_ = [weak = AceType::WeakClaim(this)](ImageSourceInfo info, const std::string& errorMsg = "") {
        auto render = weak.Upgrade();
        LOGE("tkh failedCallback_");
        render->ImageObjFailed();
    };

    uploadSuccessCallback_ = [weak = AceType::WeakClaim(this)](
                                 ImageSourceInfo sourceInfo, const RefPtr<NG::CanvasImage>& image) {};

    onPostBackgroundTask_ = [weak = AceType::WeakClaim(this)](CancelableTask task) {};
}

void RosenRenderCustomPaint::ImageObjReady(const RefPtr<ImageObject>& imageObj)
{
    imageObj_ = imageObj;
    if (imageObj_->IsSvg()) {
        skiaDom_ = AceType::DynamicCast<SvgSkiaImageObject>(imageObj_)->GetSkiaDom();
        currentSource_ = loadingSource_;
        CanvasImage canvasImage = canvasImage_;
        TaskFunc func = [canvasImage](RenderCustomPaint& iface, const Offset& offset) {
            iface.DrawImage(offset, canvasImage, 0, 0);
        };
        tasks_.emplace_back(func);
        MarkNeedRender();
    } else {
        LOGE("image is not svg");
    }
}

void RosenRenderCustomPaint::ImageObjFailed()
{
    imageObj_ = nullptr;
    skiaDom_ = nullptr;
}

void RosenRenderCustomPaint::DrawSvgImage(const Offset& offset, const CanvasImage& canvasImage)
{
    // Make the ImageSourceInfo
    canvasImage_ = canvasImage;
    loadingSource_ = ImageSourceInfo(canvasImage.src);
    // get the ImageObject
    if (currentSource_ != loadingSource_) {
        ImageProvider::FetchImageObject(loadingSource_, imageObjSuccessCallback_, uploadSuccessCallback_,
            failedCallback_, GetContext(), true, true, true, onPostBackgroundTask_);
    }

    // draw the svg
    if (skiaDom_) {
        RSRect srcRect;
        RSRect dstRect;
        Offset startPoint;
        double scaleX = 1.0f;
        double scaleY = 1.0f;
        switch (canvasImage.flag) {
            case 0:
                srcRect = RSRect(0, 0, skiaDom_->containerSize().width(), skiaDom_->containerSize().height());
                dstRect = RSRect(canvasImage.dx, canvasImage.dy, skiaDom_->containerSize().width() + canvasImage.dx,
                    skiaDom_->containerSize().height() + canvasImage.dy);
                break;
            case 1: {
                srcRect = RSRect(0, 0, skiaDom_->containerSize().width(), skiaDom_->containerSize().height());
                dstRect = RSRect(canvasImage.dx, canvasImage.dy, canvasImage.dWidth + canvasImage.dx,
                    canvasImage.dHeight + canvasImage.dy);
                break;
            }
            case 2: {
                srcRect = RSRect(canvasImage.sx, canvasImage.sy, canvasImage.sWidth + canvasImage.sx,
                    canvasImage.sHeight + canvasImage.sy);
                dstRect = RSRect(canvasImage.dx, canvasImage.dy, canvasImage.dWidth + canvasImage.dx,
                    canvasImage.dHeight + canvasImage.dy);
                break;
            }
            default:
                break;
        }
        scaleX = dstRect.GetWidth() / srcRect.GetWidth();
        scaleY = dstRect.GetHeight() / srcRect.GetHeight();
        startPoint = offset + Offset(dstRect.GetLeft(), dstRect.GetTop()) -
                     Offset(srcRect.GetLeft() * scaleX, srcRect.GetTop() * scaleY);

        drawingCanvas_->Save();
        drawingCanvas_->ClipRect(dstRect, RSClipOp::INTERSECT, false);
        drawingCanvas_->Translate(startPoint.GetX(), startPoint.GetY());
        drawingCanvas_->Scale(scaleX, scaleY);
        drawingCanvas_->DrawSVGDOM(skiaDom_);
        drawingCanvas_->Restore();
    }
}

void RosenRenderCustomPaint::DrawImage(
    const Offset& offset, const CanvasImage& canvasImage, double width, double height)
{
    std::string::size_type tmp = canvasImage.src.find(".svg");
    if (tmp != std::string::npos) {
        DrawSvgImage(offset, canvasImage);
        return;
    }

    auto image = GetImage(canvasImage.src);

    if (!image) {
        LOGE("image is null");
        return;
    }
    InitImagePaint();
    InitPaintBlend(imageBrush_);

    switch (canvasImage.flag) {
        case 0:
            drawingCanvas_->DrawImage(*image, canvasImage.dx, canvasImage.dy, RSSamplingOptions());
            break;
        case 1: {
            RSRect rect = RSRect(canvasImage.dx, canvasImage.dy, canvasImage.dWidth + canvasImage.dx,
                canvasImage.dHeight + canvasImage.dy);
            drawingCanvas_->AttachBrush(imageBrush_);
            drawingCanvas_->DrawImageRect(*image, rect, options_);
            drawingCanvas_->DetachBrush();
            break;
        }
        case 2: {
            RSRect dstRect = RSRect(canvasImage.dx, canvasImage.dy, canvasImage.dWidth + canvasImage.dx,
                canvasImage.dHeight + canvasImage.dy);
            RSRect srcRect = RSRect(canvasImage.sx, canvasImage.sy, canvasImage.sWidth + canvasImage.sx,
                canvasImage.sHeight + canvasImage.sy);
            drawingCanvas_->AttachBrush(imageBrush_);
            drawingCanvas_->DrawImageRect(
                *image, srcRect, dstRect, options_, RSSrcRectConstraint::FAST_SRC_RECT_CONSTRAINT);
            drawingCanvas_->DetachBrush();
            break;
        }
        default:
            break;
    }
}

void RosenRenderCustomPaint::DrawPixelMap(RefPtr<PixelMap> pixelMap, const CanvasImage& canvasImage)
{
    auto context = GetContext().Upgrade();
    if (!context) {
        return;
    }
    LOGE("Drawing is not supported");
}

void RosenRenderCustomPaint::UpdatePaintShader(const Pattern& pattern, RSPen* pen, RSBrush* brush)
{
    auto context = GetContext().Upgrade();
    if (!context) {
        return;
    }

    auto width = pattern.GetImageWidth();
    auto height = pattern.GetImageHeight();
    auto image = GreatOrEqual(width, 0) && GreatOrEqual(height, 0)
                     ? ImageProvider::GetDrawingImage(pattern.GetImgSrc(), context, Size(width, height))
                     : ImageProvider::GetDrawingImage(pattern.GetImgSrc(), context);
    if (!image) {
        LOGE("image is null");
        return;
    }
    static const LinearMapNode<void (*)(std::shared_ptr<RSImage>&, std::shared_ptr<RSShaderEffect>&)>
        staticPattern[] = {
            { "no-repeat",
                [](std::shared_ptr<RSImage>& image, std::shared_ptr<RSShaderEffect>& rsShaderEffect) {
                    rsShaderEffect = RSShaderEffect::CreateImageShader(
                        *image, RSTileMode::DECAL, RSTileMode::DECAL, RSSamplingOptions(), RSMatrix());
                } },
            { "repeat",
                [](std::shared_ptr<RSImage>& image, std::shared_ptr<RSShaderEffect>& rsShaderEffect) {
                    rsShaderEffect = RSShaderEffect::CreateImageShader(
                        *image, RSTileMode::REPEAT, RSTileMode::REPEAT, RSSamplingOptions(), RSMatrix());
                } },
            { "repeat-x",
                [](std::shared_ptr<RSImage>& image, std::shared_ptr<RSShaderEffect>& rsShaderEffect) {
                    rsShaderEffect = RSShaderEffect::CreateImageShader(
                        *image, RSTileMode::REPEAT, RSTileMode::DECAL, RSSamplingOptions(), RSMatrix());
                } },
            { "repeat-y",
                [](std::shared_ptr<RSImage>& image, std::shared_ptr<RSShaderEffect>& rsShaderEffect) {
                    rsShaderEffect = RSShaderEffect::CreateImageShader(
                        *image, RSTileMode::DECAL, RSTileMode::REPEAT, RSSamplingOptions(), RSMatrix());
                } },
        };
    auto operatorIter = BinarySearchFindIndex(staticPattern, ArraySize(staticPattern), pattern.GetRepetition().c_str());
    if (operatorIter != -1) {
        std::shared_ptr<RSShaderEffect> shaderEffect = nullptr;
        staticPattern[operatorIter].value(image, shaderEffect);
        if (pen) {
            pen->SetShaderEffect(shaderEffect);
        }
        if (brush) {
            brush->SetShaderEffect(shaderEffect);
        }
    }
}

void RosenRenderCustomPaint::PutImageData(const Offset& offset, const ImageData& imageData)
{
    if (imageData.data.empty()) {
        LOGE("PutImageData failed, image data is empty.");
        return;
    }
    uint32_t* data = new (std::nothrow) uint32_t[imageData.data.size()];
    if (data == nullptr) {
        LOGE("PutImageData failed, new data is null.");
        return;
    }

    for (uint32_t i = 0; i < imageData.data.size(); ++i) {
        data[i] = imageData.data[i];
    }

    RSBitmap bitmap;
    RSBitmapFormat format { RSColorType::COLORTYPE_BGRA_8888, RSAlphaType::ALPHATYPE_OPAQUE };
    bitmap.Build(imageData.dirtyWidth, imageData.dirtyHeight, format);
    bitmap.SetPixels(data);
    RSBrush brush;
    drawingCanvas_->AttachBrush(brush);
    drawingCanvas_->DrawBitmap(bitmap, imageData.x, imageData.y);
    drawingCanvas_->DetachBrush();
    delete[] data;
}

std::unique_ptr<ImageData> RosenRenderCustomPaint::GetImageData(double left, double top, double width, double height)
{
    double viewScale = 1.0;
    auto pipeline = context_.Upgrade();
    if (pipeline) {
        viewScale = pipeline->GetViewScale();
    }
    // copy the bitmap to tempCanvas
    RSBitmapFormat format { RSColorType::COLORTYPE_BGRA_8888, RSAlphaType::ALPHATYPE_OPAQUE };
    RSBitmap tempCache;
    tempCache.Build(width, height, format);
    double scaledLeft = left * viewScale;
    double scaledTop = top * viewScale;
    double dirtyWidth = width >= 0 ? width : 0;
    double dirtyHeight = height >= 0 ? height : 0;
    int32_t size = dirtyWidth * dirtyHeight;
    bool isGpuEnable = false;
    RSCanvas tempCanvas;
    tempCanvas.Bind(tempCache);
    auto srcRect = RSRect(scaledLeft, scaledTop, width * viewScale + scaledLeft, height * viewScale + scaledTop);
    auto dstRect = RSRect(0.0, 0.0, dirtyWidth, dirtyHeight);
    if (!isGpuEnable) {
        RSImage rsImage;
        rsImage.BuildFromBitmap(canvasCache_);
        tempCanvas.DrawImageRect(rsImage, srcRect, dstRect, options_, RSSrcRectConstraint::FAST_SRC_RECT_CONSTRAINT);
    }
    const uint8_t* pixels = static_cast<const uint8_t*>(tempCache.GetPixels());
    if (pixels == nullptr) {
        return nullptr;
    }
    std::unique_ptr<ImageData> imageData = std::make_unique<ImageData>();
    imageData->dirtyWidth = dirtyWidth;
    imageData->dirtyHeight = dirtyHeight;
    // a pixel include 4 data(blue, green, red, alpha)
    for (int i = 0; i < size * 4; i += 4) {
        auto blue = pixels[i];
        auto green = pixels[i + 1];
        auto red = pixels[i + 2];
        auto alpha = pixels[i + 3];
        imageData->data.emplace_back(Color::FromARGB(alpha, red, green, blue).GetValue());
    }
    return imageData;
}

std::string RosenRenderCustomPaint::GetJsonData(const std::string& path)
{
    AssetImageLoader imageLoader;
    return imageLoader.LoadJsonData(path, context_.Upgrade());
}

void RosenRenderCustomPaint::WebGLInit(CanvasRenderContextBase* context)
{
    webGLContext_ = context;
    if (webGLContext_) {
        auto pipeline = context_.Upgrade();
        if (!pipeline) {
            return;
        }
        double viewScale = pipeline->GetViewScale();
        if (!webglBitmap_.GetPixels()) {
            RSBitmapFormat format { RSColorType::COLORTYPE_RGBA_8888, RSAlphaType::ALPHATYPE_OPAQUE };
            webglBitmap_.Build(GetLayoutSize().Width() * viewScale, GetLayoutSize().Height() * viewScale, format);
        }
        webGLContext_->SetBitMapPtr(
            reinterpret_cast<char*>(webglBitmap_.GetPixels()), webglBitmap_.GetWidth(), webglBitmap_.GetHeight());
    }
}

void RosenRenderCustomPaint::WebGLUpdate()
{
    if (drawingCanvas_ && webglBitmap_.GetPixels() != nullptr) {
        drawingCanvas_->Save();
        /* Do mirror flip */
        RSMatrix matrix;
        matrix.Scale(1.0, -1.0, 0.0, 0.0);
        drawingCanvas_->SetMatrix(matrix);
        RSBrush brush;
        drawingCanvas_->AttachBrush(brush);
        drawingCanvas_->DrawBitmap(webglBitmap_, 0, -webglBitmap_.GetHeight());
        drawingCanvas_->DetachBrush();
        drawingCanvas_->Restore();
    }
}

void RosenRenderCustomPaint::DrawBitmapMesh(
    const RefPtr<OffscreenCanvas>& offscreenCanvas, const std::vector<double>& mesh, int32_t column, int32_t row)
{
    std::unique_ptr<ImageData> imageData =
        offscreenCanvas->GetImageData(0, 0, offscreenCanvas->GetWidth(), offscreenCanvas->GetHeight());
    if (imageData != nullptr) {
        if (imageData->data.empty()) {
            LOGE("PutImageData failed, image data is empty.");
            return;
        }
        uint32_t* data = new (std::nothrow) uint32_t[imageData->data.size()];
        if (data == nullptr) {
            LOGE("PutImageData failed, new data is null.");
            return;
        }

        for (uint32_t i = 0; i < imageData->data.size(); ++i) {
            data[i] = imageData->data[i];
        }
        RSBitmap bitmap;
        RSBitmapFormat format { RSColorType::COLORTYPE_BGRA_8888, RSAlphaType::ALPHATYPE_OPAQUE };
        bitmap.Build(imageData->dirtyWidth, imageData->dirtyHeight, format);
        bitmap.SetPixels(data);
        uint32_t size = mesh.size();
        float verts[size];
        for (uint32_t i = 0; i < size; i++) {
            verts[i] = mesh[i];
        }
        Mesh(bitmap, column, row, verts, 0, nullptr);
        delete[] data;
    }
}

void RosenRenderCustomPaint::Mesh(
    RSBitmap& bitmap, int column, int row, const float* vertices, const int* colors, const RSBrush* brush)
{
    const int vertCounts = (column + 1) * (row + 1);
    int32_t size = 6;
    const int indexCount = column * row * size;
    uint32_t flags = SkVertices::kHasTexCoords_BuilderFlag;
    if (colors) {
        flags |= SkVertices::kHasColors_BuilderFlag;
    }
    SkVertices::Builder builder(SkVertices::kTriangles_VertexMode, vertCounts, indexCount, flags);
    if (memcpy_s(builder.positions(), vertCounts * sizeof(SkPoint), vertices, vertCounts * sizeof(SkPoint)) != EOK) {
        return;
    }
    if (colors) {
        if (memcpy_s(builder.colors(), vertCounts * sizeof(SkColor), colors, vertCounts * sizeof(SkColor)) != EOK) {
            return;
        }
    }
    SkPoint* texsPoint = builder.texCoords();
    uint16_t* indices = builder.indices();
    const RSScalar height = static_cast<RSScalar>(bitmap.GetHeight());
    const RSScalar width = static_cast<RSScalar>(bitmap.GetWidth());
    if (row == 0) {
        LOGE("row is zero");
        return;
    }
    if (column == 0) {
        LOGE("column is zero");
        return;
    }
    const SkScalar dy = height / row;
    const SkScalar dx = width / column;

    SkPoint* texsPit = texsPoint;
    SkScalar y = 0;
    for (int i = 0; i <= row; i++) {
        if (i == row) {
            y = height; // to ensure numerically we hit h exactly
        }
        SkScalar x = 0;
        for (int j = 0; j < column; j++) {
            texsPit->set(x, y);
            texsPit += 1;
            x += dx;
        }
        texsPit->set(width, y);
        texsPit += 1;
        y += dy;
    }

    uint16_t* dexs = indices;
    int index = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            *dexs++ = index;
            *dexs++ = index + column + 1;
            *dexs++ = index + column + 2;

            *dexs++ = index;
            *dexs++ = index + column + 2;
            *dexs++ = index + 1;

            index += 1;
        }
        index += 1;
    }

    RSBrush tempBrush;
    if (brush) {
        tempBrush = *brush;
    }
    auto image = std::make_shared<RSImage>();
    image->BuildFromBitmap(bitmap);
    auto shader = RSShaderEffect::CreateImageShader(
        *image, RSTileMode::CLAMP, RSTileMode::CLAMP, RSSamplingOptions(), RSMatrix());
    tempBrush.SetShaderEffect(shader);
    drawingCanvas_->AttachBrush(tempBrush);
    LOGE("Drawing is not supported");
    drawingCanvas_->DetachBrush();
}

std::shared_ptr<RSImage> RosenRenderCustomPaint::GetImage(const std::string& src)
{
    if (!imageCache_) {
        imageCache_ = ImageCache::Create();
        imageCache_->SetCapacity(IMAGE_CACHE_COUNT);
    }
    auto cacheImage = imageCache_->GetCacheImage(src);
    if (cacheImage && cacheImage->imagePtr) {
        return cacheImage->imagePtr;
    }

    auto context = GetContext().Upgrade();
    if (!context) {
        return nullptr;
    }

    auto image = ImageProvider::GetDrawingImage(src, context);
    if (image) {
        RSBitmapFormat rsBitmapFormat { image->GetColorType(), image->GetAlphaType() };
        RSBitmap rsBitmap;
        rsBitmap.Build(image->GetWidth(), image->GetHeight(), rsBitmapFormat);
        if (image->ReadPixels(rsBitmap, 0, 0)) {
            auto rasterizedImage = std::make_shared<RSImage>();
            rasterizedImage->BuildFromBitmap(rsBitmap);
            imageCache_->CacheImage(src, std::make_shared<CachedImage>(rasterizedImage));
            return rasterizedImage;
        }
    }

    return image;
}

} // namespace OHOS::Ace
