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

#include "core/components_ng/pattern/custom_paint/custom_paint_paint_method.h"

#include <cmath>
#include <unistd.h>

#include "drawing/engine_adapter/skia_adapter/skia_canvas.h"
#include "include/core/SkBlendMode.h"
#include "include/core/SkCanvas.h"
#include "include/core/SkColor.h"
#include "include/core/SkColorFilter.h"
#include "include/core/SkImage.h"
#include "include/core/SkPoint.h"
#include "include/core/SkShader.h"
#include "include/core/SkSurface.h"
#include "include/effects/SkDashPathEffect.h"
#include "include/effects/SkGradientShader.h"
#include "include/effects/SkImageFilters.h"
#include "include/utils/SkParsePath.h"
#include "securec.h"

#include "base/geometry/ng/offset_t.h"
#include "base/json/json_util.h"
#include "base/log/ace_trace.h"
#include "base/utils/linear_map.h"
#include "base/utils/string_utils.h"
#include "base/utils/utils.h"
#include "core/components/calendar/rosen_render_calendar.h"
#include "core/components/common/painter/rosen_decoration_painter.h"
#include "core/components/common/properties/decoration.h"
#include "core/components_ng/render/drawing.h"
#include "core/image/image_cache.h"
#include "core/image/image_provider.h"
#include "core/image/sk_image_cache.h"
#include "core/pipeline/base/rosen_render_context.h"

#ifdef ENABLE_ROSEN_BACKEND
#include "pipeline/rs_recording_canvas.h"
#endif

namespace OHOS::Ace::NG {
namespace {
constexpr double HANGING_PERCENT = 0.8;
constexpr double HALF_CIRCLE_ANGLE = 180.0;
constexpr double FULL_CIRCLE_ANGLE = 360.0;
constexpr double CONIC_START_ANGLE = 0.0;
constexpr double CONIC_END_ANGLE = 359.9;
constexpr double MAX_GRAYSCALE = 255.0;
constexpr int32_t IMAGE_CACHE_COUNT = 50;
constexpr int32_t DEFAULT_SAVE_COUNT = 1;

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

template<typename T, typename N>
N ConvertEnumToDrawingEnum(T key, const LinearEnumMapNode<T, N>* map, size_t length, N defaultValue)
{
    int64_t index = BinarySearchFindIndex(map, length, key);
    return index != -1 ? map[index].value : defaultValue;
}

template<typename T>
inline T ConvertStrToEnum(const char* key, const LinearMapNode<T>* map, size_t length, T defaultValue)
{
    int64_t index = BinarySearchFindIndex(map, length, key);
    return index != -1 ? map[index].value : defaultValue;
}
} // namespace

const LinearMapNode<void (*)(std::shared_ptr<RSImage>&, std::shared_ptr<RSShaderEffect>&, RSMatrix&)>
    CustomPaintPaintMethod::staticPattern[] = {
        { "clamp",
            [](std::shared_ptr<RSImage>& image, std::shared_ptr<RSShaderEffect>& shaderEffect, RSMatrix& matrix) {
                shaderEffect = RSShaderEffect::CreateImageShader(
                    *image, RSTileMode::CLAMP, RSTileMode::CLAMP, RSSamplingOptions(), matrix);
            } },
        { "mirror",
            [](std::shared_ptr<RSImage>& image, std::shared_ptr<RSShaderEffect>& shaderEffect, RSMatrix& matrix) {
                shaderEffect = RSShaderEffect::CreateImageShader(
                    *image, RSTileMode::MIRROR, RSTileMode::MIRROR, RSSamplingOptions(), matrix);
            } },
        { "no-repeat",
            [](std::shared_ptr<RSImage>& image, std::shared_ptr<RSShaderEffect>& shaderEffect, RSMatrix& matrix) {
                shaderEffect = RSShaderEffect::CreateImageShader(
                    *image, RSTileMode::DECAL, RSTileMode::DECAL, RSSamplingOptions(), matrix);
            } },
        { "repeat",
            [](std::shared_ptr<RSImage>& image, std::shared_ptr<RSShaderEffect>& shaderEffect, RSMatrix& matrix) {
                shaderEffect = RSShaderEffect::CreateImageShader(
                    *image, RSTileMode::REPEAT, RSTileMode::REPEAT, RSSamplingOptions(), matrix);
            } },
        { "repeat-x",
            [](std::shared_ptr<RSImage>& image, std::shared_ptr<RSShaderEffect>& shaderEffect, RSMatrix& matrix) {
                shaderEffect = RSShaderEffect::CreateImageShader(
                    *image, RSTileMode::REPEAT, RSTileMode::DECAL, RSSamplingOptions(), matrix);
            } },
        { "repeat-y",
            [](std::shared_ptr<RSImage>& image, std::shared_ptr<RSShaderEffect>& shaderEffect, RSMatrix& matrix) {
                shaderEffect = RSShaderEffect::CreateImageShader(
                    *image, RSTileMode::DECAL, RSTileMode::REPEAT, RSSamplingOptions(), matrix);
            } },
    };

bool CustomPaintPaintMethod::CheckFilterProperty(FilterType filterType, const std::string& filterParam)
{
    switch (filterType) {
        case FilterType::GRAYSCALE:
        case FilterType::SEPIA:
        case FilterType::SATURATE:
        case FilterType::INVERT:
        case FilterType::OPACITY:
        case FilterType::BRIGHTNESS:
        case FilterType::CONTRAST: {
            std::regex contrastRegexExpression(R"((\d+(\.\d+)?%?)|(^$))");
            return std::regex_match(filterParam, contrastRegexExpression);
        }
        case FilterType::BLUR: {
            std::regex blurRegexExpression(R"((\d+(\.\d+)?(px|rem))|(^$))");
            return std::regex_match(filterParam, blurRegexExpression);
        }
        case FilterType::HUE_ROTATE: {
            std::regex hueRotateRegexExpression(R"((\d+(\.\d+)?(deg|grad|rad|turn))|(^$))");
            return std::regex_match(filterParam, hueRotateRegexExpression);
        }
        default:
            return false;
    }
}

bool CustomPaintPaintMethod::ParseFilter(std::string& filter, std::vector<FilterProperty>& filters)
{
    filter.erase(0, filter.find_first_not_of(' '));
    size_t index = filter.find_first_of('(');
    if (index == std::string::npos) {
        return false;
    }
    FilterType filterType = FilterStrToFilterType(filter.substr(0, index));
    std::string filterParam = filter.substr(index + 1);
    filterParam.erase(0, filterParam.find_first_not_of(' '));
    filterParam.erase(filterParam.find_last_not_of(' ') + 1);
    if (!CheckFilterProperty(filterType, filterParam)) {
        return false;
    }
    filters.emplace_back(FilterProperty{filterType, filterParam});
    return true;
}

void CustomPaintPaintMethod::UpdateRecordingCanvas(float width, float height)
{
    rsRecordingCanvas_ = std::make_shared<RSRecordingCanvas>(width, height);
    rsCanvas_ = std::static_pointer_cast<RSCanvas>(rsRecordingCanvas_);
    contentModifier_->UpdateCanvas(rsRecordingCanvas_);
    RSCanvas* rsCanvas = GetRawPtrOfRSCanvas();
    CHECK_NULL_VOID(rsCanvas);
    rsCanvas->Save();
    if (canvasCallback_) {
        canvasCallback_(rsCanvas_.get(), width, height);
    }
}

void CustomPaintPaintMethod::SetRSCanvasCallback(std::function<void(RSCanvas*, double, double)>& callback)
{
    canvasCallback_ = callback;
}

bool CustomPaintPaintMethod::HasShadow() const
{
    return !(NearZero(shadow_.GetOffset().GetX()) && NearZero(shadow_.GetOffset().GetY()) &&
             NearZero(shadow_.GetBlurRadius()));
}

void CustomPaintPaintMethod::UpdateLineDash(RSPen& pen)
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

std::shared_ptr<RSShaderEffect> CustomPaintPaintMethod::MakeConicGradient(RSBrush* brush, const Ace::Gradient& gradient)
{
    std::shared_ptr<RSShaderEffect> shaderEffect = nullptr;
    if (gradient.GetType() == Ace::GradientType::CONIC) {
        if (!gradient.GetConicGradient().centerX.has_value() || !gradient.GetConicGradient().centerY.has_value() ||
            !gradient.GetConicGradient().startAngle.has_value()) {
            return nullptr;
        }
        RSMatrix matrix;
        RSScalar centerX = static_cast<RSScalar>(gradient.GetConicGradient().centerX->Value());
        RSScalar centerY = static_cast<RSScalar>(gradient.GetConicGradient().centerY->Value());
        auto gradientColors = gradient.GetColors();
        std::stable_sort(gradientColors.begin(), gradientColors.end(),
            [](auto& colorA, auto& colorB) { return colorA.GetDimension() < colorB.GetDimension(); });
        uint32_t colorsSize = gradientColors.size();
        std::vector<RSColorQuad> colors(gradientColors.size(), 0);
        std::vector<RSScalar> pos(gradientColors.size(), 0);
        double angle = gradient.GetConicGradient().startAngle->Value() / M_PI * 180.0;
        RSScalar startAngle = static_cast<RSScalar>(angle);
        matrix.PreRotate(startAngle, centerX, centerY);
        for (uint32_t i = 0; i < colorsSize; ++i) {
            const auto& gradientColor = gradientColors[i];
            colors.at(i) = gradientColor.GetColor().GetValue();
            pos.at(i) = gradientColor.GetDimension().Value();
        }
        auto mode = RSTileMode::CLAMP;
        shaderEffect = RSShaderEffect::CreateSweepGradient(RSPoint(centerX, centerY), colors, pos, mode,
            static_cast<RSScalar>(CONIC_START_ANGLE), static_cast<RSScalar>(CONIC_END_ANGLE), &matrix);
    }
    return shaderEffect;
}

void CustomPaintPaintMethod::UpdatePaintShader(
    const OffsetF& offset, RSPen* pen, RSBrush* brush, const Ace::Gradient& gradient)
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
    if (gradient.GetType() == Ace::GradientType::LINEAR) {
        shaderEffect = RSShaderEffect::CreateLinearGradient(pts.at(0), pts.at(1), colors, pos, mode);
    } else if (gradient.GetType() == Ace::GradientType::CONIC) {
        shaderEffect = MakeConicGradient(nullptr, gradient);
    } else {
        if (gradient.GetInnerRadius() <= 0.0 && beginPoint == endPoint) {
            shaderEffect = RSShaderEffect::CreateRadialGradient(endPoint, gradient.GetOuterRadius(), colors, pos, mode);
        } else {
            RSMatrix matrix;
            shaderEffect = RSShaderEffect::CreateTwoPointConical(beginPoint, gradient.GetInnerRadius(), endPoint,
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

RSMatrix CustomPaintPaintMethod::GetMatrixFromPattern(const Ace::Pattern& pattern)
{
    RSMatrix matrix;
    double viewScale = 1.0;
    matrix.SetMatrix(pattern.GetScaleX() * viewScale, pattern.GetSkewX() * viewScale,
        pattern.GetTranslateX() * viewScale, pattern.GetSkewY() * viewScale, pattern.GetScaleY() * viewScale,
        pattern.GetTranslateY() * viewScale, 0.0f, 0.0f, 1.0f);
    return matrix;
}

std::shared_ptr<RSImage> CustomPaintPaintMethod::GetImage(const std::string& src)
{
    if (!imageCache_) {
        imageCache_ = ImageCache::Create();
        imageCache_->SetCapacity(IMAGE_CACHE_COUNT);
    }
    auto cacheImage = imageCache_->GetCacheImage(src);
    if (cacheImage && cacheImage->imagePtr) {
        return cacheImage->imagePtr;
    }

    auto context = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(context, nullptr);
    auto image = Ace::ImageProvider::GetDrawingImage(src, context);
    CHECK_NULL_RETURN(image, nullptr);
    imageCache_->CacheImage(src, std::make_shared<Ace::CachedImage>(image));
    return image;
}

void CustomPaintPaintMethod::UpdatePaintShader(const Ace::Pattern& pattern, RSPen* pen, RSBrush* brush)
{
#if !defined(PREVIEW)
    auto pixelMap = pattern.GetPixelMap();
    CHECK_NULL_VOID(pixelMap);
    auto rsBitmapFormat = Ace::ImageProvider::MakeRSBitmapFormatFromPixelMap(pixelMap);
    auto rsBitmap = std::make_shared<RSBitmap>();
    rsBitmap->Build(pixelMap->GetWidth(), pixelMap->GetHeight(), rsBitmapFormat, pixelMap->GetRowStride());
    rsBitmap->SetPixels(const_cast<void*>(reinterpret_cast<const void*>(pixelMap->GetPixels())));
    auto image = std::make_shared<RSImage>();
    CHECK_NULL_VOID(image->BuildFromBitmap(*rsBitmap));
#else
    auto image = GetImage(pattern.GetImgSrc());
    CHECK_NULL_VOID(image);
#endif
    RSMatrix matrix;
    if (pattern.IsTransformable()) {
        matrix = GetMatrixFromPattern(pattern);
    }
    auto operatorIter = BinarySearchFindIndex(staticPattern, ArraySize(staticPattern), pattern.GetRepetition().c_str());
    if (operatorIter != -1) {
        std::shared_ptr<RSShaderEffect> shaderEffect = nullptr;
        staticPattern[operatorIter].value(image, shaderEffect, matrix);
        if (pen) {
            pen->SetShaderEffect(shaderEffect);
        }
        if (brush) {
            brush->SetShaderEffect(shaderEffect);
        }
    }
}

void CustomPaintPaintMethod::InitPaintBlend(RSBrush& brush)
{
    brush.SetBlendMode(ConvertEnumToDrawingEnum(
        globalState_.GetType(), DRAWING_BLEND_MODE_TABLE, BLEND_MODE_SIZE, RSBlendMode::SRC_OVER));
}

void CustomPaintPaintMethod::InitPaintBlend(RSPen& pen)
{
    pen.SetBlendMode(ConvertEnumToDrawingEnum(
        globalState_.GetType(), DRAWING_BLEND_MODE_TABLE, BLEND_MODE_SIZE, RSBlendMode::SRC_OVER));
}

void CustomPaintPaintMethod::GetStrokePaint(RSPen& pen, RSSamplingOptions& options)
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
    InitImagePaint(&pen, nullptr, options);
    if (strokeState_.GetPaintStyle() == PaintStyle::Color) {
        pen.SetColor(strokeState_.GetColor().GetValue());
    }
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
        if (strokeState_.GetPaintStyle() == PaintStyle::Color) {
            pen.SetAlphaF(
                globalState_.GetAlpha() * static_cast<double>(strokeState_.GetColor().GetAlpha()) / MAX_GRAYSCALE);
        } else {
            pen.SetAlphaF(globalState_.GetAlpha());
        }
    }
}

void CustomPaintPaintMethod::InitImagePaint(RSPen* pen, RSBrush* brush, RSSamplingOptions& options)
{
    RSFilter filter;
    if (smoothingEnabled_) {
        if (smoothingQuality_ == "low") {
            options = RSSamplingOptions(RSFilterMode::LINEAR, RSMipmapMode::NONE);
            filter.SetFilterQuality(RSFilter::FilterQuality::LOW);
        } else if (smoothingQuality_ == "medium") {
            options = RSSamplingOptions(RSFilterMode::LINEAR, RSMipmapMode::LINEAR);
            filter.SetFilterQuality(RSFilter::FilterQuality::MEDIUM);
        } else if (smoothingQuality_ == "high") {
            options = RSSamplingOptions(RSCubicResampler::Mitchell());
            filter.SetFilterQuality(RSFilter::FilterQuality::HIGH);
        }
    } else {
        options = RSSamplingOptions(RSFilterMode::NEAREST, RSMipmapMode::NONE);
        filter.SetFilterQuality(RSFilter::FilterQuality::NONE);
    }
    if (pen) {
        pen->SetFilter(filter);
    }
    if (brush) {
        brush->SetFilter(filter);
    }
    ClearPaintImage(pen, brush);
    SetPaintImage(pen, brush);
}

void CustomPaintPaintMethod::InitImageCallbacks()
{
    imageObjSuccessCallback_ = [weak = AceType::WeakClaim(this)](
                                   ImageSourceInfo info, const RefPtr<Ace::ImageObject>& imageObj) {
        auto paintMethod = weak.Upgrade();
        if (paintMethod->loadingSource_ == info) {
            paintMethod->ImageObjReady(imageObj);
            return;
        }
    };

    failedCallback_ = [weak = AceType::WeakClaim(this)](ImageSourceInfo info, const std::string& errorMsg = "") {
        auto paintMethod = weak.Upgrade();
        paintMethod->ImageObjFailed();
    };

    uploadSuccessCallback_ = [weak = AceType::WeakClaim(this)](
                                 ImageSourceInfo sourceInfo, const RefPtr<NG::CanvasImage>& image) {};

    onPostBackgroundTask_ = [weak = AceType::WeakClaim(this)](CancelableTask task) {};
}

void CustomPaintPaintMethod::GetSvgRect(
    const sk_sp<SkSVGDOM>& skiaDom, const Ace::CanvasImage& canvasImage, RSRect* srcRect, RSRect* dstRect)
{
    switch (canvasImage.flag) {
        case DrawImageType::THREE_PARAMS:
            *srcRect = RSRect(0, 0, skiaDom->containerSize().width(), skiaDom->containerSize().height());
            *dstRect = RSRect(canvasImage.dx, canvasImage.dy, skiaDom->containerSize().width() + canvasImage.dx,
                skiaDom->containerSize().height() + canvasImage.dy);
            break;
        case DrawImageType::FIVE_PARAMS: {
            *srcRect = RSRect(0, 0, skiaDom->containerSize().width(), skiaDom->containerSize().height());
            *dstRect = RSRect(canvasImage.dx, canvasImage.dy, canvasImage.dWidth + canvasImage.dx,
                canvasImage.dHeight + canvasImage.dy);
            break;
        }
        case DrawImageType::NINE_PARAMS: {
            *srcRect = RSRect(canvasImage.sx, canvasImage.sy, canvasImage.sWidth + canvasImage.sx,
                canvasImage.sHeight + canvasImage.sy);
            *dstRect = RSRect(canvasImage.dx, canvasImage.dy, canvasImage.dWidth + canvasImage.dx,
                canvasImage.dHeight + canvasImage.dy);
            break;
        }
        default:
            break;
    }
}

void CustomPaintPaintMethod::DrawSvgImage(PaintWrapper* paintWrapper, const Ace::CanvasImage& canvasImage)
{
    // Make the ImageSourceInfo
    canvasImage_ = canvasImage;
    loadingSource_ = ImageSourceInfo(canvasImage.src);
    // get the ImageObject
    auto context = PipelineBase::GetCurrentContext();
    if (currentSource_ != loadingSource_) {
        ImageProvider::FetchImageObject(loadingSource_, imageObjSuccessCallback_, uploadSuccessCallback_,
            failedCallback_, context, true, true, true, onPostBackgroundTask_);
    }

    CHECK_NULL_VOID(skiaDom_);
    // draw the svg
    RSRect srcRect;
    RSRect dstRect;
    GetSvgRect(skiaDom_, canvasImage, &srcRect, &dstRect);
    float scaleX = dstRect.GetWidth() / srcRect.GetWidth();
    float scaleY = dstRect.GetHeight() / srcRect.GetHeight();
    OffsetF offset = GetContentOffset(paintWrapper);
    OffsetF startPoint = offset + OffsetF(dstRect.GetLeft(), dstRect.GetTop()) -
                         OffsetF(srcRect.GetLeft() * scaleX, srcRect.GetTop() * scaleY);

    RSCanvas* rsCanvas = GetRawPtrOfRSCanvas();
    rsCanvas->Save();
    if (rsCanvas->GetDrawingType() == Rosen::Drawing::DrawingType::RECORDING) {
        RSBitmap bitmap;
        RSBrush brush;
        RSBitmapFormat bitmapFormat = { RSColorType::COLORTYPE_RGBA_8888, RSAlphaType::ALPHATYPE_UNPREMUL };
        bitmap.Build(rsCanvas->GetWidth(), rsCanvas->GetHeight(), bitmapFormat);
        bitmap.ClearWithColor(RSColor::COLOR_TRANSPARENT);
        auto rs_OffscreenCanvas = std::make_unique<RSCanvas>();
        rs_OffscreenCanvas->Bind(bitmap);
        rs_OffscreenCanvas->ClipRect(dstRect, RSClipOp::INTERSECT);
        rs_OffscreenCanvas->Translate(startPoint.GetX(), startPoint.GetY());
        rs_OffscreenCanvas->Scale(scaleX, scaleY);
        rs_OffscreenCanvas->DrawSVGDOM(skiaDom_);
        rsCanvas->AttachBrush(brush);
        rsCanvas->DrawBitmap(bitmap, 0, 0);
        rsCanvas->DetachBrush();
    } else {
        rsCanvas->ClipRect(dstRect, RSClipOp::INTERSECT);
        rsCanvas->Translate(startPoint.GetX(), startPoint.GetY());
        rsCanvas->Scale(scaleX, scaleY);
        rsCanvas->DrawSVGDOM(skiaDom_);
    }
    rsCanvas->Restore();
}

void CustomPaintPaintMethod::DrawSvgImage(PaintWrapper* paintWrapper, RefPtr<SvgDomBase> svgDom,
    const Ace::CanvasImage& canvasImage, const ImageFit& imageFit)
{
    CHECK_NULL_VOID(svgDom);
    RSRect srcRect;
    RSRect dstRect;
    switch (canvasImage.flag) {
        case 0:
            srcRect = RSRect(0, 0, svgDom->GetContainerSize().Width(), svgDom->GetContainerSize().Height());
            dstRect = RSRect(canvasImage.dx, canvasImage.dy, svgDom->GetContainerSize().Width() + canvasImage.dx,
                svgDom->GetContainerSize().Height() + canvasImage.dy);
            break;
        case 1: {
            srcRect = RSRect(0, 0, svgDom->GetContainerSize().Width(), svgDom->GetContainerSize().Height());
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
    float scaleX = dstRect.GetWidth() / srcRect.GetWidth();
    float scaleY = dstRect.GetHeight() / srcRect.GetHeight();
    OffsetF offset = GetContentOffset(paintWrapper);
    OffsetF startPoint = offset + OffsetF(dstRect.GetLeft(), dstRect.GetTop()) -
                         OffsetF(srcRect.GetLeft() * scaleX, srcRect.GetTop() * scaleY);

    RSCanvas* rsCanvas = GetRawPtrOfRSCanvas();
    CHECK_NULL_VOID(rsCanvas);
    rsCanvas->Save();
    rsCanvas->ClipRect(dstRect, RSClipOp::INTERSECT);
    rsCanvas->Translate(startPoint.GetX(), startPoint.GetY());
    rsCanvas->Scale(scaleX, scaleY);
    svgDom->DrawImage(*rsCanvas, imageFit, Size(srcRect.GetWidth(), srcRect.GetHeight()));
    rsCanvas->Restore();
}

void CustomPaintPaintMethod::PutImageData(PaintWrapper* paintWrapper, const Ace::ImageData& imageData)
{
    if (imageData.data.empty()) {
        return;
    }
    uint32_t* data = new (std::nothrow) uint32_t[imageData.data.size()];
    CHECK_NULL_VOID(data);

    for (uint32_t i = 0; i < imageData.data.size(); ++i) {
        data[i] = imageData.data[i].GetValue();
    }
    RSBitmap bitmap;
    RSBitmapFormat format { RSColorType::COLORTYPE_BGRA_8888, RSAlphaType::ALPHATYPE_OPAQUE };
    bitmap.Build(imageData.dirtyWidth, imageData.dirtyHeight, format);
    bitmap.SetPixels(data);
    auto contentOffset = GetContentOffset(paintWrapper);
    RSBrush brush;
    brush.SetBlendMode(RSBlendMode::SRC);
    rsCanvas_->AttachBrush(brush);
    rsCanvas_->DrawBitmap(bitmap, imageData.x + contentOffset.GetX(), imageData.y + contentOffset.GetY());
    rsCanvas_->DetachBrush();
    delete[] data;
}

void CustomPaintPaintMethod::FillRect(PaintWrapper* paintWrapper, const Rect& rect)
{
    OffsetF offset = GetContentOffset(paintWrapper);
    RSBrush brush;
    RSSamplingOptions options;
    InitImagePaint(nullptr, &brush, options);
    brush.SetAntiAlias(antiAlias_);
    if (fillState_.GetPaintStyle() == OHOS::Ace::PaintStyle::Color) {
        brush.SetColor(fillState_.GetColor().GetValue());
    }
    RSRect rsRect(rect.Left() + offset.GetX(), rect.Top() + offset.GetY(), rect.Right() + offset.GetX(),
        offset.GetY() + rect.Bottom());
    if (fillState_.GetGradient().IsValid() && fillState_.GetPaintStyle() == PaintStyle::Gradient) {
        UpdatePaintShader(offset, nullptr, &brush, fillState_.GetGradient());
    }
    if (fillState_.GetPatternValue().IsValid() && fillState_.GetPaintStyle() == PaintStyle::ImagePattern) {
        UpdatePaintShader(fillState_.GetPatternValue(), nullptr, &brush);
    }
    if (globalState_.HasGlobalAlpha()) {
        if (fillState_.GetPaintStyle() == OHOS::Ace::PaintStyle::Color) {
            brush.SetAlphaF(
                globalState_.GetAlpha() * static_cast<double>(fillState_.GetColor().GetAlpha()) / MAX_GRAYSCALE);
        } else {
            brush.SetAlphaF(globalState_.GetAlpha()); // update the global alpha after setting the color
        }
    }
    if (HasShadow()) {
        RSRecordingPath path;
        path.AddRect(rsRect);
        PaintShadow(path, shadow_, rsCanvas_.get(), &brush, nullptr);
    }
    if (globalState_.GetType() == CompositeOperation::SOURCE_OVER) {
        rsCanvas_->AttachBrush(brush);
        rsCanvas_->DrawRect(rsRect);
        rsCanvas_->DetachBrush();
    } else {
        RSBrush compositeOperationpBrush;
        InitPaintBlend(compositeOperationpBrush);
        auto rect = RSRect(0, 0, lastLayoutSize_.Width(), lastLayoutSize_.Height());
        RSSaveLayerOps slo(&rect, &compositeOperationpBrush);
        rsCanvas_->SaveLayer(slo);
        rsCanvas_->AttachBrush(brush);
        rsCanvas_->DrawRect(rsRect);
        rsCanvas_->DetachBrush();
        rsCanvas_->Restore();
    }
}

void CustomPaintPaintMethod::StrokeRect(PaintWrapper* paintWrapper, const Rect& rect)
{
    OffsetF offset = GetContentOffset(paintWrapper);
    RSPen pen;
    RSSamplingOptions options;
    GetStrokePaint(pen, options);
    pen.SetAntiAlias(antiAlias_);
    RSRect rsRect(rect.Left() + offset.GetX(), rect.Top() + offset.GetY(), rect.Right() + offset.GetX(),
        offset.GetY() + rect.Bottom());
    if (HasShadow()) {
        RSRecordingPath path;
        path.AddRect(rsRect);
        PaintShadow(path, shadow_, rsCanvas_.get(), nullptr, &pen);
    }
    if (strokeState_.GetGradient().IsValid() && strokeState_.GetPaintStyle() == PaintStyle::Gradient) {
        UpdatePaintShader(offset, &pen, nullptr, strokeState_.GetGradient());
    }
    if (strokeState_.GetPatternValue().IsValid() && strokeState_.GetPaintStyle() == PaintStyle::ImagePattern) {
        UpdatePaintShader(strokeState_.GetPatternValue(), &pen, nullptr);
    }
    if (globalState_.GetType() == CompositeOperation::SOURCE_OVER) {
        rsCanvas_->AttachPen(pen);
        rsCanvas_->DrawRect(rsRect);
        rsCanvas_->DetachPen();
    } else {
        RSBrush compositeOperationpBrush;
        InitPaintBlend(compositeOperationpBrush);
        auto rect = RSRect(0, 0, lastLayoutSize_.Width(), lastLayoutSize_.Height());
        RSSaveLayerOps slo(&rect, &compositeOperationpBrush);
        rsCanvas_->SaveLayer(slo);
        rsCanvas_->AttachPen(pen);
        rsCanvas_->DrawRect(rsRect);
        rsCanvas_->DetachPen();
        rsCanvas_->Restore();
    }
}

void CustomPaintPaintMethod::ClearRect(PaintWrapper* paintWrapper, const Rect& rect)
{
    OffsetF offset = GetContentOffset(paintWrapper);
    RSBrush brush;
    RSSamplingOptions options;
    InitImagePaint(nullptr, &brush, options);
    brush.SetAntiAlias(antiAlias_);
    brush.SetBlendMode(RSBlendMode::CLEAR);
    RSRect rsRect(rect.Left() + offset.GetX(), rect.Top() + offset.GetY(), rect.Right() + offset.GetX(),
        rect.Bottom() + offset.GetY());
    rsCanvas_->AttachBrush(brush);
    rsCanvas_->DrawRect(rsRect);
    rsCanvas_->DetachBrush();
}

void CustomPaintPaintMethod::SetFillRuleForPath(const CanvasFillRule& rule)
{
    if (rule == CanvasFillRule::NONZERO) {
        rsPath_.SetFillStyle(RSPathFillType::WINDING);
    } else if (rule == CanvasFillRule::EVENODD) {
        rsPath_.SetFillStyle(RSPathFillType::EVENTODD);
    }
}

void CustomPaintPaintMethod::SetFillRuleForPath2D(const CanvasFillRule& rule)
{
    if (rule == CanvasFillRule::NONZERO) {
        rsPath2d_.SetFillStyle(RSPathFillType::WINDING);
    } else if (rule == CanvasFillRule::EVENODD) {
        rsPath2d_.SetFillStyle(RSPathFillType::EVENTODD);
    }
}

void CustomPaintPaintMethod::Fill(PaintWrapper* paintWrapper)
{
    OffsetF offset = GetContentOffset(paintWrapper);
    RSBrush brush;
    RSSamplingOptions options;
    InitImagePaint(nullptr, &brush, options);
    brush.SetAntiAlias(antiAlias_);
    if (fillState_.GetPaintStyle() == OHOS::Ace::PaintStyle::Color) {
        brush.SetColor(fillState_.GetColor().GetValue());
    }
    if (fillState_.GetGradient().IsValid() && fillState_.GetPaintStyle() == PaintStyle::Gradient) {
        UpdatePaintShader(offset, nullptr, &brush, fillState_.GetGradient());
    }
    if (fillState_.GetPatternValue().IsValid() && fillState_.GetPaintStyle() == PaintStyle::ImagePattern) {
        UpdatePaintShader(fillState_.GetPatternValue(), nullptr, &brush);
    }
    if (globalState_.HasGlobalAlpha()) {
        if (fillState_.GetPaintStyle() == OHOS::Ace::PaintStyle::Color) {
            brush.SetAlphaF(
                globalState_.GetAlpha() * static_cast<double>(fillState_.GetColor().GetAlpha()) / MAX_GRAYSCALE);
        } else {
            brush.SetAlphaF(globalState_.GetAlpha());
        }
    }
    if (HasShadow()) {
        PaintShadow(rsPath_, shadow_, rsCanvas_.get(), &brush, nullptr);
    }
    if (globalState_.GetType() == CompositeOperation::SOURCE_OVER) {
        rsCanvas_->AttachBrush(brush);
        rsCanvas_->DrawPath(rsPath_);
        rsCanvas_->DetachBrush();
    } else {
        RSBrush compositeOperationpBrush;
        InitPaintBlend(compositeOperationpBrush);
        auto rect = RSRect(0, 0, lastLayoutSize_.Width(), lastLayoutSize_.Height());
        RSSaveLayerOps slo(&rect, &compositeOperationpBrush);
        rsCanvas_->SaveLayer(slo);
        rsCanvas_->AttachBrush(brush);
        rsCanvas_->DrawPath(rsPath_);
        rsCanvas_->DetachBrush();
        rsCanvas_->Restore();
    }
}

void CustomPaintPaintMethod::Fill(PaintWrapper* paintWrapper, const RefPtr<CanvasPath2D>& path)
{
    CHECK_NULL_VOID(path);
    OffsetF offset = GetContentOffset(paintWrapper);
    ParsePath2D(offset, path);
    Path2DFill(offset);
    rsPath2d_.Reset();
}

void CustomPaintPaintMethod::Path2DFill(const OffsetF& offset)
{
    RSBrush brush;
    RSSamplingOptions options;
    InitImagePaint(nullptr, &brush, options);
    brush.SetAntiAlias(antiAlias_);
    if (fillState_.GetPaintStyle() == OHOS::Ace::PaintStyle::Color) {
        brush.SetColor(fillState_.GetColor().GetValue());
    }
    if (fillState_.GetGradient().IsValid() && fillState_.GetPaintStyle() == PaintStyle::Gradient) {
        UpdatePaintShader(offset, nullptr, &brush, fillState_.GetGradient());
    }
    if (fillState_.GetPatternValue().IsValid() && fillState_.GetPaintStyle() == PaintStyle::ImagePattern) {
        UpdatePaintShader(fillState_.GetPattern(), nullptr, &brush);
    }
    if (globalState_.HasGlobalAlpha()) {
        if (fillState_.GetPaintStyle() == OHOS::Ace::PaintStyle::Color) {
            brush.SetAlphaF(
                globalState_.GetAlpha() * static_cast<double>(fillState_.GetColor().GetAlpha()) / MAX_GRAYSCALE);
        } else {
            brush.SetAlphaF(globalState_.GetAlpha());
        }
    }
    if (HasShadow()) {
        PaintShadow(rsPath2d_, shadow_, rsCanvas_.get(), &brush, nullptr);
    }
    if (globalState_.GetType() == CompositeOperation::SOURCE_OVER) {
        rsCanvas_->AttachBrush(brush);
        rsCanvas_->DrawPath(rsPath2d_);
        rsCanvas_->DetachBrush();
    } else {
        RSBrush compositeOperationpBrush;
        InitPaintBlend(compositeOperationpBrush);
        auto rect = RSRect(0, 0, lastLayoutSize_.Width(), lastLayoutSize_.Height());
        RSSaveLayerOps slo(&rect, &compositeOperationpBrush);
        rsCanvas_->SaveLayer(slo);
        rsCanvas_->AttachBrush(brush);
        rsCanvas_->DrawPath(rsPath2d_);
        rsCanvas_->DetachBrush();
        rsCanvas_->Restore();
    }
}

void CustomPaintPaintMethod::Stroke(PaintWrapper* paintWrapper)
{
    OffsetF offset = GetContentOffset(paintWrapper);
    RSPen pen;
    RSSamplingOptions options;
    GetStrokePaint(pen, options);
    pen.SetAntiAlias(antiAlias_);
    if (strokeState_.GetGradient().IsValid() && strokeState_.GetPaintStyle() == PaintStyle::Gradient) {
        UpdatePaintShader(offset, &pen, nullptr, strokeState_.GetGradient());
    }
    if (strokeState_.GetPatternValue().IsValid() && strokeState_.GetPaintStyle() == PaintStyle::ImagePattern) {
        UpdatePaintShader(strokeState_.GetPatternValue(), &pen, nullptr);
    }
    if (HasShadow()) {
        PaintShadow(rsPath_, shadow_, rsCanvas_.get(), nullptr, &pen);
    }
    if (globalState_.GetType() == CompositeOperation::SOURCE_OVER) {
        rsCanvas_->AttachPen(pen);
        rsCanvas_->DrawPath(rsPath_);
        rsCanvas_->DetachPen();
    } else {
        RSBrush compositeOperationpBrush;
        InitPaintBlend(compositeOperationpBrush);
        auto rect = RSRect(0, 0, lastLayoutSize_.Width(), lastLayoutSize_.Height());
        RSSaveLayerOps slo(&rect, &compositeOperationpBrush);
        rsCanvas_->SaveLayer(slo);
        rsCanvas_->AttachPen(pen);
        rsCanvas_->DrawPath(rsPath_);
        rsCanvas_->DetachPen();
        rsCanvas_->Restore();
    }
}

void CustomPaintPaintMethod::Stroke(PaintWrapper* paintWrapper, const RefPtr<CanvasPath2D>& path)
{
    CHECK_NULL_VOID(path);
    OffsetF offset = GetContentOffset(paintWrapper);
    ParsePath2D(offset, path);
    Path2DStroke(offset);
    rsPath2d_.Reset();
}

void CustomPaintPaintMethod::Path2DStroke(const OffsetF& offset)
{
    RSPen pen;
    RSSamplingOptions options;
    GetStrokePaint(pen, options);
    pen.SetAntiAlias(antiAlias_);
    if (strokeState_.GetGradient().IsValid() && strokeState_.GetPaintStyle() == PaintStyle::Gradient) {
        UpdatePaintShader(offset, &pen, nullptr, strokeState_.GetGradient());
    }
    if (strokeState_.GetPatternValue().IsValid() && strokeState_.GetPaintStyle() == PaintStyle::ImagePattern) {
        UpdatePaintShader(strokeState_.GetPatternValue(), &pen, nullptr);
    }
    if (HasShadow()) {
        PaintShadow(rsPath2d_, shadow_, rsCanvas_.get(), nullptr, &pen);
    }
    if (globalState_.GetType() == CompositeOperation::SOURCE_OVER) {
        rsCanvas_->AttachPen(pen);
        rsCanvas_->DrawPath(rsPath2d_);
        rsCanvas_->DetachPen();
    } else {
        RSBrush compositeOperationpBrush;
        InitPaintBlend(compositeOperationpBrush);
        auto rect = RSRect(0, 0, lastLayoutSize_.Width(), lastLayoutSize_.Height());
        RSSaveLayerOps slo(&rect, &compositeOperationpBrush);
        rsCanvas_->SaveLayer(slo);
        rsCanvas_->AttachPen(pen);
        rsCanvas_->DrawPath(rsPath2d_);
        rsCanvas_->DetachPen();
        rsCanvas_->Restore();
    }
}

void CustomPaintPaintMethod::Clip()
{
    rsCanvas_->ClipPath(rsPath_, RSClipOp::INTERSECT);
}

void CustomPaintPaintMethod::Clip(const RefPtr<CanvasPath2D>& path)
{
    CHECK_NULL_VOID(path);
    auto offset = OffsetF(0, 0);
    ParsePath2D(offset, path);
    Path2DClip();
    rsPath2d_.Reset();
}

void CustomPaintPaintMethod::Path2DClip()
{
    rsCanvas_->ClipPath(rsPath2d_, RSClipOp::INTERSECT);
}

void CustomPaintPaintMethod::BeginPath()
{
    rsPath_.Reset();
}

void CustomPaintPaintMethod::ClosePath()
{
    rsPath_.Close();
}

void CustomPaintPaintMethod::MoveTo(PaintWrapper* paintWrapper, double x, double y)
{
    OffsetF offset = GetContentOffset(paintWrapper);
    rsPath_.MoveTo(static_cast<RSScalar>(x + offset.GetX()), static_cast<RSScalar>(y + offset.GetY()));
}

void CustomPaintPaintMethod::LineTo(PaintWrapper* paintWrapper, double x, double y)
{
    OffsetF offset = GetContentOffset(paintWrapper);
    rsPath_.LineTo(static_cast<RSScalar>(x + offset.GetX()), static_cast<RSScalar>(y + offset.GetY()));
}

void CustomPaintPaintMethod::Arc(PaintWrapper* paintWrapper, const ArcParam& param)
{
    OffsetF offset = GetContentOffset(paintWrapper);
    double left = param.x - param.radius + offset.GetX();
    double top = param.y - param.radius + offset.GetY();
    double right = param.x + param.radius + offset.GetX();
    double bottom = param.y + param.radius + offset.GetY();
    double startAngle = param.startAngle * HALF_CIRCLE_ANGLE / M_PI;
    double endAngle = param.endAngle * HALF_CIRCLE_ANGLE / M_PI;
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
    if (!NearEqual(startAngle, endAngle) &&
        (NearEqual(std::abs(std::fmod(sweepAngle, FULL_CIRCLE_ANGLE)), 0.0) ||
            NearEqual(std::abs(std::fmod(sweepAngle, FULL_CIRCLE_ANGLE)), FULL_CIRCLE_ANGLE))) {
        // draw circle
        double half = GreatNotEqual(sweepAngle, 0.0) ? HALF_CIRCLE_ANGLE : -HALF_CIRCLE_ANGLE;
        rsPath_.ArcTo(point1, point2, static_cast<RSScalar>(startAngle), static_cast<RSScalar>(half));
        rsPath_.ArcTo(point1, point2, static_cast<RSScalar>(half + startAngle), static_cast<RSScalar>(half));
    } else if (!NearEqual(std::fmod(sweepAngle, FULL_CIRCLE_ANGLE), 0.0) && abs(sweepAngle) > FULL_CIRCLE_ANGLE) {
        double half = GreatNotEqual(sweepAngle, 0.0) ? HALF_CIRCLE_ANGLE : -HALF_CIRCLE_ANGLE;
        rsPath_.ArcTo(point1, point2, static_cast<RSScalar>(startAngle), static_cast<RSScalar>(half));
        rsPath_.ArcTo(point1, point2, static_cast<RSScalar>(half + startAngle), static_cast<RSScalar>(half));
        rsPath_.ArcTo(
            point1, point2, static_cast<RSScalar>(half + half + startAngle), static_cast<RSScalar>(sweepAngle));
    } else {
        rsPath_.ArcTo(point1, point2, static_cast<RSScalar>(startAngle), static_cast<RSScalar>(sweepAngle));
    }
}

void CustomPaintPaintMethod::ArcTo(PaintWrapper* paintWrapper, const ArcToParam& param)
{
    OffsetF offset = GetContentOffset(paintWrapper);
    double x1 = param.x1 + offset.GetX();
    double y1 = param.y1 + offset.GetY();
    double x2 = param.x2 + offset.GetX();
    double y2 = param.y2 + offset.GetY();
    double radius = param.radius;
    rsPath_.ArcTo(static_cast<RSScalar>(x1), static_cast<RSScalar>(y1), static_cast<RSScalar>(x2),
        static_cast<RSScalar>(y2), static_cast<RSScalar>(radius));
}

void CustomPaintPaintMethod::AddRect(PaintWrapper* paintWrapper, const Rect& rect)
{
    OffsetF offset = GetContentOffset(paintWrapper);
    RSRect rsRect(rect.Left() + offset.GetX(), rect.Top() + offset.GetY(), rect.Right() + offset.GetX(),
        offset.GetY() + rect.Bottom());
    rsPath_.AddRect(rsRect);
}

void CustomPaintPaintMethod::Ellipse(PaintWrapper* paintWrapper, const EllipseParam& param)
{
    OffsetF offset = GetContentOffset(paintWrapper);
    // Init the start and end angle, then calculated the sweepAngle.
    double startAngle = param.startAngle * HALF_CIRCLE_ANGLE / M_PI;
    double endAngle = param.endAngle * HALF_CIRCLE_ANGLE / M_PI;
    if (NearEqual(param.startAngle, param.endAngle)) {
        return; // Just return when startAngle is same as endAngle.
    }
    double rotation = param.rotation * HALF_CIRCLE_ANGLE / M_PI;
    double sweepAngle = endAngle - startAngle;
    if (param.anticlockwise) {
        sweepAngle =
            endAngle > startAngle ? (std::fmod(sweepAngle, FULL_CIRCLE_ANGLE) - FULL_CIRCLE_ANGLE) : sweepAngle;
    } else {
        sweepAngle =
            endAngle > startAngle ? sweepAngle : (std::fmod(sweepAngle, FULL_CIRCLE_ANGLE) + FULL_CIRCLE_ANGLE);
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
        rsPath_.Transform(matrix);
    }
    if (NearEqual(std::abs(std::fmod(sweepAngle, FULL_CIRCLE_ANGLE)), 0.0) ||
        NearEqual(std::abs(std::fmod(sweepAngle, FULL_CIRCLE_ANGLE)), FULL_CIRCLE_ANGLE)) {
        double half = GreatNotEqual(sweepAngle, 0.0) ? HALF_CIRCLE_ANGLE : -HALF_CIRCLE_ANGLE;
        rsPath_.ArcTo(point1, point2, static_cast<RSScalar>(startAngle), static_cast<RSScalar>(half));
        rsPath_.ArcTo(point1, point2, static_cast<RSScalar>(half + startAngle), static_cast<RSScalar>(half));
    } else if (!NearEqual(std::fmod(sweepAngle, FULL_CIRCLE_ANGLE), 0.0) && abs(sweepAngle) > FULL_CIRCLE_ANGLE) {
        double half = GreatNotEqual(sweepAngle, 0.0) ? HALF_CIRCLE_ANGLE : -HALF_CIRCLE_ANGLE;
        rsPath_.ArcTo(point1, point2, static_cast<RSScalar>(startAngle), static_cast<RSScalar>(half));
        rsPath_.ArcTo(point1, point2, static_cast<RSScalar>(half + startAngle), static_cast<RSScalar>(half));
        rsPath_.ArcTo(
            point1, point2, static_cast<RSScalar>(half + half + startAngle), static_cast<RSScalar>(sweepAngle));
    } else {
        rsPath_.ArcTo(point1, point2, static_cast<RSScalar>(startAngle), static_cast<RSScalar>(sweepAngle));
    }
    if (!NearZero(rotation)) {
        RSMatrix matrix;
        matrix.Rotate(rotation, param.x + offset.GetX(), param.y + offset.GetY());
        rsPath_.Transform(matrix);
    }
}

void CustomPaintPaintMethod::BezierCurveTo(PaintWrapper* paintWrapper, const BezierCurveParam& param)
{
    OffsetF offset = GetContentOffset(paintWrapper);
    rsPath_.CubicTo(static_cast<RSScalar>(param.cp1x + offset.GetX()),
        static_cast<RSScalar>(param.cp1y + offset.GetY()), static_cast<RSScalar>(param.cp2x + offset.GetX()),
        static_cast<RSScalar>(param.cp2y + offset.GetY()), static_cast<RSScalar>(param.x + offset.GetX()),
        static_cast<RSScalar>(param.y + offset.GetY()));
}

void CustomPaintPaintMethod::QuadraticCurveTo(PaintWrapper* paintWrapper, const QuadraticCurveParam& param)
{
    OffsetF offset = GetContentOffset(paintWrapper);
    rsPath_.QuadTo(static_cast<RSScalar>(param.cpx + offset.GetX()), static_cast<RSScalar>(param.cpy + offset.GetY()),
        static_cast<RSScalar>(param.x + offset.GetX()), static_cast<RSScalar>(param.y + offset.GetY()));
}

void CustomPaintPaintMethod::ParsePath2D(const OffsetF& offset, const RefPtr<CanvasPath2D>& path)
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

void CustomPaintPaintMethod::Path2DAddPath(const OffsetF& offset, const PathArgs& args)
{
    RSRecordingPath out;
    out.BuildFromSVGString(args.cmds);
    rsPath2d_.AddPath(out);
}

void CustomPaintPaintMethod::Path2DClosePath(const OffsetF& offset, const PathArgs& args)
{
    rsPath2d_.Close();
}

void CustomPaintPaintMethod::Path2DMoveTo(const OffsetF& offset, const PathArgs& args)
{
    double x = args.para1 + offset.GetX();
    double y = args.para2 + offset.GetY();
    rsPath2d_.MoveTo(x, y);
}

void CustomPaintPaintMethod::Path2DLineTo(const OffsetF& offset, const PathArgs& args)
{
    double x = args.para1 + offset.GetX();
    double y = args.para2 + offset.GetY();
    rsPath2d_.LineTo(x, y);
}

void CustomPaintPaintMethod::Path2DArc(const OffsetF& offset, const PathArgs& args)
{
    double x = args.para1;
    double y = args.para2;
    double r = args.para3;
    RSPoint point1(x - r + offset.GetX(), y - r + offset.GetY());
    RSPoint point2(x + r + offset.GetX(), y + r + offset.GetY());
    double startAngle = args.para4 * HALF_CIRCLE_ANGLE / M_PI;
    double endAngle = args.para5 * HALF_CIRCLE_ANGLE / M_PI;
    double sweepAngle = endAngle - startAngle;
    if (!NearZero(args.para6)) {
        sweepAngle =
            endAngle > startAngle ? (std::fmod(sweepAngle, FULL_CIRCLE_ANGLE) - FULL_CIRCLE_ANGLE) : sweepAngle;
    } else {
        sweepAngle =
            endAngle > startAngle ? sweepAngle : (std::fmod(sweepAngle, FULL_CIRCLE_ANGLE) + FULL_CIRCLE_ANGLE);
    }
    if (!NearEqual(startAngle, endAngle) &&
        (NearEqual(std::abs(std::fmod(sweepAngle, FULL_CIRCLE_ANGLE)), 0.0) ||
         NearEqual(std::abs(std::fmod(sweepAngle, FULL_CIRCLE_ANGLE)), FULL_CIRCLE_ANGLE))) {
        double half = GreatNotEqual(sweepAngle, 0.0) ? HALF_CIRCLE_ANGLE : -HALF_CIRCLE_ANGLE;
        rsPath2d_.ArcTo(point1, point2, static_cast<RSScalar>(startAngle), static_cast<RSScalar>(half));
        rsPath2d_.ArcTo(point1, point2, static_cast<RSScalar>(half + startAngle), static_cast<RSScalar>(half));
    } else if (!NearEqual(std::fmod(sweepAngle, FULL_CIRCLE_ANGLE), 0.0) && abs(sweepAngle) > FULL_CIRCLE_ANGLE) {
        double half = GreatNotEqual(sweepAngle, 0.0) ? HALF_CIRCLE_ANGLE : -HALF_CIRCLE_ANGLE;
        rsPath2d_.ArcTo(point1, point2, static_cast<RSScalar>(startAngle), static_cast<RSScalar>(half));
        rsPath2d_.ArcTo(point1, point2, static_cast<RSScalar>(half + startAngle), static_cast<RSScalar>(half));
        rsPath2d_.ArcTo(
            point1, point2, static_cast<RSScalar>(half + half + startAngle), static_cast<RSScalar>(sweepAngle));
    } else {
        rsPath2d_.ArcTo(point1, point2, startAngle, sweepAngle);
    }
}

void CustomPaintPaintMethod::Path2DArcTo(const OffsetF& offset, const PathArgs& args)
{
    double x1 = args.para1 + offset.GetX();
    double y1 = args.para2 + offset.GetY();
    double x2 = args.para3 + offset.GetX();
    double y2 = args.para4 + offset.GetY();
    double r = args.para5;
    rsPath2d_.ArcTo(static_cast<RSScalar>(x1), static_cast<RSScalar>(y1), static_cast<RSScalar>(x2),
        static_cast<RSScalar>(y2), static_cast<RSScalar>(r));
}

void CustomPaintPaintMethod::Path2DEllipse(const OffsetF& offset, const PathArgs& args)
{
    if (NearEqual(args.para6, args.para7)) {
        return; // Just return when startAngle is same as endAngle.
    }

    double x = args.para1;
    double y = args.para2;
    double rx = args.para3;
    double ry = args.para4;
    double rotation = args.para5 * HALF_CIRCLE_ANGLE / M_PI;
    double startAngle = args.para6 * HALF_CIRCLE_ANGLE / M_PI;
    double endAngle = args.para7 * HALF_CIRCLE_ANGLE / M_PI;
    bool anticlockwise = NearZero(args.para8) ? false : true;
    double sweepAngle = endAngle - startAngle;
    if (anticlockwise) {
        sweepAngle =
            endAngle > startAngle ? (std::fmod(sweepAngle, FULL_CIRCLE_ANGLE) - FULL_CIRCLE_ANGLE) : sweepAngle;
    } else {
        sweepAngle =
            endAngle > startAngle ? sweepAngle : (std::fmod(sweepAngle, FULL_CIRCLE_ANGLE) + FULL_CIRCLE_ANGLE);
    }
    RSPoint point1(x - rx + offset.GetX(), y - ry + offset.GetY());
    RSPoint point2(x + rx + offset.GetX(), y + ry + offset.GetY());

    if (!NearZero(rotation)) {
        RSMatrix matrix;
        matrix.Rotate(-rotation, x + offset.GetX(), y + offset.GetY());
        rsPath2d_.Transform(matrix);
    }
    if (NearEqual(std::abs(std::fmod(sweepAngle, FULL_CIRCLE_ANGLE)), 0.0) ||
        NearEqual(std::abs(std::fmod(sweepAngle, FULL_CIRCLE_ANGLE)), FULL_CIRCLE_ANGLE)) {
        double half = GreatNotEqual(sweepAngle, 0.0) ? HALF_CIRCLE_ANGLE : -HALF_CIRCLE_ANGLE;
        rsPath2d_.ArcTo(point1, point2, static_cast<RSScalar>(startAngle), static_cast<RSScalar>(half));
        rsPath2d_.ArcTo(point1, point2, static_cast<RSScalar>(half + startAngle), static_cast<RSScalar>(half));
    } else if (!NearEqual(std::fmod(sweepAngle, FULL_CIRCLE_ANGLE), 0.0) && abs(sweepAngle) > FULL_CIRCLE_ANGLE) {
        double half = GreatNotEqual(sweepAngle, 0.0) ? HALF_CIRCLE_ANGLE : -HALF_CIRCLE_ANGLE;
        rsPath2d_.ArcTo(point1, point2, static_cast<RSScalar>(startAngle), static_cast<RSScalar>(half));
        rsPath2d_.ArcTo(point1, point2, static_cast<RSScalar>(half + startAngle), static_cast<RSScalar>(half));
        rsPath2d_.ArcTo(
            point1, point2, static_cast<RSScalar>(half + half + startAngle), static_cast<RSScalar>(sweepAngle));
    } else {
        rsPath2d_.ArcTo(point1, point2, startAngle, sweepAngle);
    }
    if (!NearZero(rotation)) {
        RSMatrix matrix;
        matrix.Rotate(rotation, x + offset.GetX(), y + offset.GetY());
        rsPath2d_.Transform(matrix);
    }
}

void CustomPaintPaintMethod::Path2DBezierCurveTo(const OffsetF& offset, const PathArgs& args)
{
    double cp1x = args.para1 + offset.GetX();
    double cp1y = args.para2 + offset.GetY();
    double cp2x = args.para3 + offset.GetX();
    double cp2y = args.para4 + offset.GetY();
    double x = args.para5 + offset.GetX();
    double y = args.para6 + offset.GetY();
    rsPath2d_.CubicTo(cp1x, cp1y, cp2x, cp2y, x, y);
}

void CustomPaintPaintMethod::Path2DQuadraticCurveTo(const OffsetF& offset, const PathArgs& args)
{
    double cpx = args.para1 + offset.GetX();
    double cpy = args.para2 + offset.GetY();
    double x = args.para3 + offset.GetX();
    double y = args.para4 + offset.GetY();
    rsPath2d_.QuadTo(cpx, cpy, x, y);
}

void CustomPaintPaintMethod::Path2DSetTransform(const OffsetF& offset, const PathArgs& args)
{
    RSMatrix matrix;
    double scaleX = args.para1;
    double skewX = args.para2;
    double skewY = args.para3;
    double scaleY = args.para4;
    double translateX = args.para5;
    double translateY = args.para6;
    matrix.SetMatrix(scaleX, skewY, translateX, skewX, scaleY, translateY, 0, 0, 1);
    rsPath2d_.Transform(matrix);
}

void CustomPaintPaintMethod::Save()
{
    SaveStates();
    rsCanvas_->Save();
}

void CustomPaintPaintMethod::Restore()
{
    if (rsCanvas_->GetSaveCount() <= DEFAULT_SAVE_COUNT) {
        return;
    }
    RestoreStates();
    rsCanvas_->Restore();
}

void CustomPaintPaintMethod::Scale(double x, double y)
{
    rsCanvas_->Scale(x, y);
}

void CustomPaintPaintMethod::Rotate(double angle)
{
    rsCanvas_->Rotate(angle * 180 / M_PI);
}

void CustomPaintPaintMethod::ResetTransform()
{
    rsCanvas_->ResetMatrix();
}

void CustomPaintPaintMethod::Transform(const TransformParam& param)
{
    RSMatrix matrix;
    matrix.SetMatrix(param.scaleX, param.skewY, param.translateX, param.skewX, param.scaleY, param.translateY, 0, 0, 1);
    rsCanvas_->ConcatMatrix(matrix);
}

void CustomPaintPaintMethod::Translate(double x, double y)
{
    rsCanvas_->Translate(x, y);
}

double CustomPaintPaintMethod::GetAlignOffset(TextAlign align, std::unique_ptr<OHOS::Rosen::Typography>& paragraph)
{
    double x = 0.0;
    TextDirection textDirection = fillState_.GetOffTextDirection();
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
            x = -paragraph->GetMaxIntrinsicWidth() / 2.0;
            break;
        default:
            x = 0.0;
            break;
    }
    return x;
}

double CustomPaintPaintMethod::GetFontBaseline(
    const Rosen::Drawing::FontMetrics& fontMetrics, TextBaseline baseline) const
{
    switch (baseline) {
        case TextBaseline::TOP:
            return fontMetrics.fAscent;
        case TextBaseline::HANGING:
            return fontMetrics.fAscent * HANGING_PERCENT;
        case TextBaseline::MIDDLE:
            return fontMetrics.fAscent + fontMetrics.fDescent;
        case TextBaseline::BOTTOM:
        case TextBaseline::IDEOGRAPHIC:
            return fontMetrics.fDescent;
        case TextBaseline::ALPHABETIC:
            return 0;
        default:
            break;
    }
    return 0;
}

double CustomPaintPaintMethod::GetFontAlign(
    TextAlign align, std::unique_ptr<OHOS::Rosen::Typography>& paragraph) const
{
    TextDirection textDirection = fillState_.GetOffTextDirection();
    switch (align) {
        case TextAlign::LEFT:
            return 0;
        case TextAlign::START:
            return (textDirection == TextDirection::LTR) ? 0.0 : paragraph->GetMaxIntrinsicWidth();
        case TextAlign::RIGHT:
            return paragraph->GetMaxIntrinsicWidth();
        case TextAlign::END:
            return (textDirection == TextDirection::LTR) ? paragraph->GetMaxIntrinsicWidth() : 0.0;
        case TextAlign::CENTER:
            return paragraph->GetMaxIntrinsicWidth() / 2.0;
        default:
            break;
    }
    return 0;
}

OHOS::Rosen::TextAlign CustomPaintPaintMethod::GetEffectiveAlign(
    OHOS::Rosen::TextAlign align, OHOS::Rosen::TextDirection direction) const
{
    if (align == OHOS::Rosen::TextAlign::START) {
        return (direction == OHOS::Rosen::TextDirection::LTR) ? OHOS::Rosen::TextAlign::LEFT
                                                              : OHOS::Rosen::TextAlign::RIGHT;
    } else if (align == OHOS::Rosen::TextAlign::END) {
        return (direction == OHOS::Rosen::TextDirection::LTR) ? OHOS::Rosen::TextAlign::RIGHT
                                                              : OHOS::Rosen::TextAlign::LEFT;
    } else {
        return align;
    }
}

void CustomPaintPaintMethod::ClearPaintImage(RSPen* pen, RSBrush* brush)
{
    float matrix[20] = { 0.0f };
    matrix[0] = matrix[6] = matrix[12] = matrix[18] = 1.0f;
    RSFilter filter;
    RSColorMatrix colorMatrix;
    colorMatrix.SetArray(matrix);
    filter.SetColorFilter(RSColorFilter::CreateMatrixColorFilter(colorMatrix));
    filter.SetMaskFilter(RSMaskFilter::CreateBlurMaskFilter(RSBlurType::NORMAL, 0));
    filter.SetImageFilter(RSImageFilter::CreateBlurImageFilter(0, 0, RSTileMode::DECAL, nullptr));
    if (pen) {
        pen->SetFilter(filter);
    }
    if (brush) {
        brush->SetFilter(filter);
    }
}

void CustomPaintPaintMethod::SetPaintImage(RSPen* pen, RSBrush* brush)
{
    std::vector<FilterProperty> filters;
    if (GetFilterType(filters)) {
        lastFilters_ = filters;
    } else {
        filters = lastFilters_;
    }
    for (FilterProperty filter : filters) {
        switch (filter.filterType_) {
            case FilterType::NONE:
                break;
            case FilterType::GRAYSCALE:
                SetGrayFilter(filter.filterParam_, pen, brush);
                break;
            case FilterType::SEPIA:
                SetSepiaFilter(filter.filterParam_, pen, brush);
                break;
            case FilterType::SATURATE:
                SetSaturateFilter(filter.filterParam_, pen, brush);
                break;
            case FilterType::HUE_ROTATE:
                SetHueRotateFilter(filter.filterParam_, pen, brush);
                break;
            case FilterType::INVERT:
                SetInvertFilter(filter.filterParam_, pen, brush);
                break;
            case FilterType::OPACITY:
                SetOpacityFilter(filter.filterParam_, pen, brush);
                break;
            case FilterType::BRIGHTNESS:
                SetBrightnessFilter(filter.filterParam_, pen, brush);
                break;
            case FilterType::CONTRAST:
                SetContrastFilter(filter.filterParam_, pen, brush);
                break;
            case FilterType::BLUR:
                SetBlurFilter(filter.filterParam_, pen, brush);
                break;
            case FilterType::DROP_SHADOW:
                break;
            default:
                break;
        }
    }
}

// https://drafts.fxtf.org/filter-effects/#grayscaleEquivalent
void CustomPaintPaintMethod::SetGrayFilter(const std::string& percent, RSPen* pen, RSBrush* brush)
{
    float percentNum = 1.0f;
    if (!CheckNumberAndPercentage(percent, true, percentNum)) {
        return;
    }

    float matrix[20] = { 0.0f };
    float value = 1 - percentNum;

    matrix[0] = LUMR + (1 - LUMR) * value;
    matrix[5] = LUMR - LUMR * value;
    matrix[10] = LUMR - LUMR * value;

    matrix[1] = LUMG - LUMG * value;
    matrix[6] = LUMG + (1 - LUMG) * value;
    matrix[11] = LUMG - LUMG * value;

    matrix[2] = LUMB - LUMB * value;
    matrix[7] = LUMB - LUMB * value;
    matrix[12] = LUMB + (1 - LUMB) * value;

    matrix[18] = 1.0f;
    SetColorFilter(matrix, pen, brush);
}

// https://drafts.fxtf.org/filter-effects/#sepiaEquivalent
void CustomPaintPaintMethod::SetSepiaFilter(const std::string& percent, RSPen* pen, RSBrush* brush)
{
    float percentNum = 1.0f;
    if (!CheckNumberAndPercentage(percent, true, percentNum)) {
        return;
    }
    float matrix[20] = { 0.0f };
    matrix[0] = 1.0f - percentNum * 0.607f;
    matrix[1] = percentNum * 0.769f;
    matrix[2] = percentNum * 0.189f;

    matrix[5] = percentNum * 0.349f;
    matrix[6] = 1.0f - percentNum * 0.314f;
    matrix[7] = percentNum * 0.168f;

    matrix[10] = percentNum * 0.272f;
    matrix[11] = percentNum * 0.534f;
    matrix[12] = 1.0f - percentNum * 0.869f;

    matrix[18] = 1.0f;
    SetColorFilter(matrix, pen, brush);
}

// https://drafts.fxtf.org/filter-effects/#saturateEquivalent
void CustomPaintPaintMethod::SetSaturateFilter(const std::string& percent, RSPen* pen, RSBrush* brush)
{
    float percentNum = 1.0f;
    if (!CheckNumberAndPercentage(percent, false, percentNum)) {
        return;
    }
    float matrix[20] = { 0.0f };

    matrix[0] = LUMR + (1 - LUMR) * percentNum;
    matrix[5] = LUMR - LUMR * percentNum;
    matrix[10] = LUMR - LUMR * percentNum;

    matrix[1] = LUMG - LUMG * percentNum;
    matrix[6] = LUMG + (1 - LUMG) * percentNum;
    matrix[11] = LUMG - LUMG * percentNum;

    matrix[2] = LUMB - LUMB * percentNum;
    matrix[7] = LUMB - LUMB * percentNum;
    matrix[12] = LUMB + (1 - LUMB) * percentNum;

    matrix[18] = 1.0f;
    SetColorFilter(matrix, pen, brush);
}

// https://drafts.fxtf.org/filter-effects/#huerotateEquivalent
void CustomPaintPaintMethod::SetHueRotateFilter(const std::string& filterParam, RSPen* pen, RSBrush* brush)
{
    std::string percent = filterParam;
    float rad = 0.0f;
    if (percent.find("deg") != std::string::npos) {
        size_t index = percent.find("deg");
        percent.resize(index);
        std::istringstream iss(percent);
        iss >> rad;
        rad = rad / HALF_CIRCLE_ANGLE * M_PI;
    }
    if (percent.find("turn") != std::string::npos) {
        size_t index = percent.find("turn");
        percent.resize(index);
        std::istringstream iss(percent);
        iss >> rad;
        rad = rad * 2 * M_PI;
    }
    if (percent.find("rad") != std::string::npos) {
        size_t index = percent.find("rad");
        percent.resize(index);
        std::istringstream iss(percent);
        iss >> rad;
    }

    float cosValue = std::cos(rad);
    float sinValue = std::sin(rad);
    float matrix[20] = { 0.0f };

    matrix[0] = LUMR + cosValue * (1 - LUMR) + sinValue * (-LUMR);
    matrix[5] = LUMR + cosValue * (-LUMR) + sinValue * 0.143f;
    matrix[10] = LUMR + cosValue * (-LUMR) + sinValue * (LUMR - 1);

    matrix[1] = LUMG + cosValue * (-LUMG) + sinValue * (-LUMG);
    matrix[6] = LUMG + cosValue * (1 - LUMG) + sinValue * 0.140f;
    matrix[11] = LUMG + cosValue * (-LUMG) + sinValue * LUMG;

    matrix[2] = LUMB + cosValue * (-LUMB) + sinValue * (1 - LUMB);
    matrix[7] = LUMB + cosValue * (-LUMB) + sinValue * (-0.283f);
    matrix[12] = LUMB + cosValue * (1 - LUMB) + sinValue * LUMB;

    matrix[18] = 1.0f;
    SetColorFilter(matrix, pen, brush);
}

/*
 * https://drafts.fxtf.org/filter-effects/#invertEquivalent
 * Example for R in RGB:
 * v0 = percentNum, v1 = 1 - percentNum, n = 1
 * If 0 <= R < 1,
 * k / n <= R < (k + 1) / n => R * n - 1 < k <= R * n => k = 0
 * R' = funcR(R) = v0 + (R - k / n) * n * (v1 - v0) = percentNum + (1 - 2 * percentNum) * R
 * If R==1, R' = v1 = 1 - percentNum = percentNum + (1 - 2 * percentNum) * R
 * so R' = funcR(R) = percentNum + (1 - 2 * percentNum) * R, where 0 <= R <= 1.
 */
void CustomPaintPaintMethod::SetInvertFilter(const std::string& percent, RSPen* pen, RSBrush* brush)
{
    float percentNum = 1.0f;
    if (!CheckNumberAndPercentage(percent, true, percentNum)) {
        return;
    }
    float matrix[20] = { 0.0f };
    matrix[0] = matrix[6] = matrix[12] = 1.0 - 2.0 * percentNum;
    matrix[4] = matrix[9] = matrix[14] = percentNum;
    matrix[18] = 1.0f;
    SetColorFilter(matrix, pen, brush);
}

/*
 * https://drafts.fxtf.org/filter-effects/#opacityEquivalent
 * A is short for Alpha:
 * v0 = 0, v1 = percentNum, n = 1
 * If 0 <= A < 1, k = 0. reference：SetInvertFilter.
 * A' = funcR(A) = v0 + (A - k / n) * n * (v1 - v0) = percentNum * A
 * If A==1, A' = v1 = percentNum = percentNum * A
 * so A' = funcR(A) = percentNum * A, where 0 <= A <= 1.
 */
void CustomPaintPaintMethod::SetOpacityFilter(const std::string& percent, RSPen* pen, RSBrush* brush)
{
    float percentNum = 1.0f;
    if (!CheckNumberAndPercentage(percent, true, percentNum)) {
        return;
    }
    float matrix[20] = { 0.0f };
    matrix[0] = matrix[6] = matrix[12] = 1.0f;
    matrix[18] = percentNum;
    SetColorFilter(matrix, pen, brush);
}

/*
 * https://drafts.fxtf.org/filter-effects/#brightnessEquivalent
 * Example for R in RGB:
 * R' = funcR(R) = slope * R + intercept
 * where: slope = percentNum, intercept = 0
 */
void CustomPaintPaintMethod::SetBrightnessFilter(const std::string& percent, RSPen* pen, RSBrush* brush)
{
    float percentNum = 1.0f;
    if (!CheckNumberAndPercentage(percent, false, percentNum)) {
        return;
    }
    float matrix[20] = { 0.0f };
    matrix[0] = matrix[6] = matrix[12] = percentNum;
    matrix[18] = 1.0f;
    SetColorFilter(matrix, pen, brush);
}

/*
 * https://drafts.fxtf.org/filter-effects/#contrastEquivalent
 * Example for R in RGB:
 * R' = funcR(R) = slope * R + intercept
 * where: slope = percentNum, intercept = 0.5 * (1 - percentNum)
 */
void CustomPaintPaintMethod::SetContrastFilter(const std::string& percent, RSPen* pen, RSBrush* brush)
{
    float percentNum = 1.0f;
    if (!CheckNumberAndPercentage(percent, false, percentNum)) {
        return;
    }
    float matrix[20] = { 0.0f };
    matrix[0] = matrix[6] = matrix[12] = percentNum;
    matrix[4] = matrix[9] = matrix[14] = 0.5f * (1 - percentNum);
    matrix[18] = 1;
    SetColorFilter(matrix, pen, brush);
}

// https://drafts.fxtf.org/filter-effects/#blurEquivalent
void CustomPaintPaintMethod::SetBlurFilter(const std::string& percent, RSPen* pen, RSBrush* brush)
{
    float blurNum = 0.0f;
    blurNum = BlurStrToDouble(percent);
    if (Negative(blurNum)) {
        return;
    }
    auto imageFilter = RSImageFilter::CreateBlurImageFilter(blurNum, blurNum, RSTileMode::DECAL, nullptr);
    if (pen) {
        auto filter = pen->GetFilter();
        filter.SetImageFilter(imageFilter);
        pen->SetFilter(filter);
    }
    if (brush) {
        auto filter = brush->GetFilter();
        filter.SetImageFilter(imageFilter);
        brush->SetFilter(filter);
    }
}

void CustomPaintPaintMethod::SetColorFilter(float matrix[20], RSPen* pen, RSBrush* brush)
{
    RSColorMatrix colorMatrix;
    colorMatrix.SetArray(matrix);
    auto colorFilter = RSColorFilter::CreateMatrixColorFilter(colorMatrix);
    if (pen) {
        auto filter = pen->GetFilter();
        filter.SetColorFilter(colorFilter);
        pen->SetFilter(filter);
    }
    if (brush) {
        auto filter = brush->GetFilter();
        filter.SetColorFilter(colorFilter);
        brush->SetFilter(filter);
    }
}

bool CustomPaintPaintMethod::GetFilterType(std::vector<FilterProperty>& filters)
{
    std::string paramData = filterParam_;
    std::transform(paramData.begin(), paramData.end(), paramData.begin(), ::tolower);
    paramData.erase(paramData.find_last_not_of(' ') + 1);
    paramData.erase(0, paramData.find_first_not_of(' '));
    if (paramData == "none") {
        filters.emplace_back(FilterProperty{FilterType::NONE, ""});
        return true;
    }

    std::string filter;
    for (auto ch : paramData) {
        if (ch == ')') {
            if (!ParseFilter(filter, filters)) {
                return false;
            }
            filter.clear();
        } else {
            filter.push_back(ch);
        }
    }
    if (!filter.empty()) {
        if (!ParseFilter(filter, filters)) {
            return false;
        }
    }
    return (filters.size() > 0);
}

bool CustomPaintPaintMethod::IsPercentStr(std::string& percent)
{
    if (percent.find("%") != std::string::npos) {
        size_t index = percent.find("%");
        percent = percent.substr(0, index);
        return true;
    }
    return false;
}

double CustomPaintPaintMethod::PxStrToDouble(const std::string& str)
{
    double ret = 0;
    size_t index = str.find("px");
    if (index != std::string::npos) {
        std::string result = str.substr(0, index);
        std::istringstream iss(result);
        iss >> ret;
    }
    return ret;
}

double CustomPaintPaintMethod::BlurStrToDouble(const std::string& str)
{
    double ret = 0;
    size_t index = str.find("px");
    size_t index1 = str.find("rem");
    size_t demIndex = std::string::npos;
    if (index != std::string::npos) {
        demIndex = index;
    }
    if (index1 != std::string::npos) {
        demIndex = index1;
    }
    if (demIndex != std::string::npos) {
        std::string result = str.substr(0, demIndex);
        std::istringstream iss(result);
        iss >> ret;
    }
    if (str.find("rem") != std::string::npos) {
        return ret * 15;
    }
    return ret;
}

float CustomPaintPaintMethod::PercentStrToFloat(const std::string& percentStr)
{
    std::string percentage = percentStr;
    bool hasPercent = IsPercentStr(percentage);
    float percentNum = 0.0f;
    std::istringstream iss(percentage);
    iss >> percentNum;
    if (hasPercent) {
        percentNum = percentNum / 100;
    }
    return percentNum;
}

bool CustomPaintPaintMethod::CheckNumberAndPercentage(const std::string& param, bool isClamped, float& result)
{
    // param.size() == 1, param[0] != 0 ~ 9, return false
    if (param.size() == 1 && (param[0] < '0' || param[0] > '9')) {
        return false;
    }
    // param.size() > 1, param[i] != (. || 0 ~ 9), return false (except for the last one)
    for (auto i = 0U; i < param.size() - 1; i++) {
        if (param[i] < '.' || param[i] == '/' || param[i] > '9') {
            return false;
        }
    }
    result = PercentStrToFloat(param);
    if (Negative(result)) {
        return false;
    }
    if (isClamped && GreatNotEqual(result, 1.0f)) {
        result = 1.0f;
    }
    return true;
}

FilterType CustomPaintPaintMethod::FilterStrToFilterType(const std::string& filterStr)
{
    const LinearMapNode<FilterType> filterTypeTable[] = {
        { "blur", FilterType::BLUR },
        { "brightness", FilterType::BRIGHTNESS },
        { "contrast", FilterType::CONTRAST },
        { "drop-shadow", FilterType::DROP_SHADOW },
        { "grayscale", FilterType::GRAYSCALE },
        { "hue-rotate", FilterType::HUE_ROTATE },
        { "invert", FilterType::INVERT },
        { "none", FilterType::NONE },
        { "opacity", FilterType::OPACITY },
        { "saturate", FilterType::SATURATE },
        { "sepia", FilterType::SEPIA },
    };
    return ConvertStrToEnum(filterStr.c_str(), filterTypeTable, ArraySize(filterTypeTable), FilterType::NONE);
}

bool CustomPaintPaintMethod::HasImageShadow() const
{
    return !(NearZero(imageShadow_->GetOffset().GetX()) && NearZero(imageShadow_->GetOffset().GetY()) &&
             NearZero(imageShadow_->GetBlurRadius()));
}

std::optional<double> CustomPaintPaintMethod::CalcTextScale(double maxIntrinsicWidth, std::optional<double> maxWidth)
{
    std::optional<double> scale;
    if (NearZero(maxIntrinsicWidth) || !maxWidth.has_value()) {
        return scale;
    }
    if (Negative(maxWidth.value())) {
        maxWidth = 0.0f;
    }
    double maxWidthValue = maxWidth.value();
    if (GreatNotEqual(maxIntrinsicWidth, maxWidthValue)) {
        scale = maxWidthValue / maxIntrinsicWidth;
    }
    return scale;
}

TransformParam CustomPaintPaintMethod::GetTransform() const
{
    TransformParam param;
    param.scaleX = matrix_.getScaleX();
    param.scaleY = matrix_.getScaleY();
    param.skewX = matrix_.getSkewX();
    param.skewY = matrix_.getSkewY();
    param.translateX = matrix_.getTranslateX();
    param.translateY = matrix_.getTranslateY();
    return param;
}

void CustomPaintPaintMethod::SaveMatrix()
{
    matrixStates_.push(matrix_);
}

void CustomPaintPaintMethod::RestoreMatrix()
{
    if (matrixStates_.empty()) {
        return;
    }
    matrix_ = matrixStates_.top();
    matrixStates_.pop();
}

void CustomPaintPaintMethod::ResetTransformMatrix()
{
    matrix_.reset();
}

void CustomPaintPaintMethod::RotateMatrix(double angle)
{
    SkMatrix matrix;
    matrix.setRotate(angle * HALF_CIRCLE_ANGLE / M_PI);
    matrix_.preConcat(matrix);
}

void CustomPaintPaintMethod::ScaleMatrix(double sx, double sy)
{
    SkMatrix matrix;
    matrix.setScale(sx, sy);
    matrix_.preConcat(matrix);
}

void CustomPaintPaintMethod::SetTransformMatrix(const TransformParam& param)
{
    double viewScale = 1.0;
    matrix_.setAll(param.scaleX * viewScale, param.skewX * viewScale, param.translateX * viewScale,
        param.skewY * viewScale, param.scaleY * viewScale, param.translateY * viewScale, 0, 0, 1);
}

void CustomPaintPaintMethod::TransformMatrix(const TransformParam& param)
{
    SkMatrix matrix;
    matrix.setAll(param.scaleX, param.skewY, param.translateX, param.skewX, param.scaleY, param.translateY, 0, 0, 1);
    matrix_.preConcat(matrix);
}

void CustomPaintPaintMethod::TranslateMatrix(double tx, double ty)
{
    if (tx || ty) {
        matrix_.preTranslate(tx, ty);
    }
}

void CustomPaintPaintMethod::SaveLayer()
{
    RSBrush compositeOperationpBrush;
    InitPaintBlend(compositeOperationpBrush);
    RSSaveLayerOps slo(nullptr, &compositeOperationpBrush);
    rsCanvas_->SaveLayer(slo);
}

void CustomPaintPaintMethod::RestoreLayer()
{
    rsCanvas_->Restore();
}

void CustomPaintPaintMethod::ResetStates()
{
    antiAlias_ = false;
    smoothingEnabled_ = true;
    smoothingQuality_ = "low";
    filterParam_ = "";
    matrix_.reset();
    fillState_ = PaintState();
    strokeState_ = StrokePaintState();
    globalState_ = GlobalPaintState();
    shadow_ = Shadow();
    imageBrush_ = RSBrush();
    lastFilters_.clear();
    rsPath_.Reset();
    rsPath2d_.Reset();
    while (!saveStates_.empty()) {
        saveStates_.pop();
    }
    while (!matrixStates_.empty()) {
        matrixStates_.pop();
    }
}
} // namespace OHOS::Ace::NG
