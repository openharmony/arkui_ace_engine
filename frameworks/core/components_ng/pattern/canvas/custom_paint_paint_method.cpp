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

#include "core/components_ng/pattern/canvas/custom_paint_paint_method.h"

#include <cmath>
#include <unistd.h>

#include "base/geometry/ng/offset_t.h"
#include "base/i18n/localization.h"
#include "base/json/json_util.h"
#include "base/log/ace_trace.h"
#include "base/utils/linear_map.h"
#include "base/utils/string_utils.h"
#include "base/utils/utils.h"
#include "bridge/common/utils/utils.h"
#include "core/components_ng/render/drawing.h"
#ifndef ACE_UNITTEST
#include "core/components/common/painter/rosen_decoration_painter.h"
#include "core/components/font/constants_converter.h"
#include "core/components/font/rosen_font_collection.h"
#include "core/image/image_provider.h"
#include "core/image/sk_image_cache.h"
#endif

namespace OHOS::Ace::NG {
namespace {
// BT.709
constexpr float LUMR = 0.2126f;
constexpr float LUMG = 0.7152f;
constexpr float LUMB = 0.0722f;
constexpr double HALF = 0.5;
constexpr double HALF_CIRCLE_ANGLE = 180.0;
constexpr double FULL_CIRCLE_ANGLE = 360.0;
constexpr double CONIC_START_ANGLE = 0.0;
constexpr double CONIC_END_ANGLE = 359.9;
constexpr double MAX_GRAYSCALE = 255.0;
constexpr double HANGING_PERCENT = 0.8;
constexpr Dimension DEFAULT_FONT_SIZE = 14.0_px;
const int32_t PX2REM_NUM = 15;

#ifndef ACE_UNITTEST
constexpr int32_t IMAGE_CACHE_COUNT = 50;
#endif

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
            std::regex contrastRegexExpression(R"((-?0)|(\d+(\.\d+)?%?)|(^$))");
            return std::regex_match(filterParam, contrastRegexExpression);
        }
        case FilterType::BLUR: {
            std::regex blurRegexExpression(R"((-?0)|(\d+(\.\d+)?(px|vp|rem))|(^$))");
            return std::regex_match(filterParam, blurRegexExpression);
        }
        case FilterType::HUE_ROTATE: {
            std::regex hueRotateRegexExpression(R"((-?0)|(-?\d+(\.\d+)?(deg|grad|rad|turn))|(^$))");
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
    if (filterType == FilterType::NONE) {
        return false;
    }
    std::string filterParam = filter.substr(index + 1);
    filterParam.erase(0, filterParam.find_first_not_of(' '));
    filterParam.erase(filterParam.find_last_not_of(' ') + 1);
    if (!CheckFilterProperty(filterType, filterParam)) {
        return false;
    }
    filters.emplace_back(FilterProperty{filterType, filterParam});
    return true;
}

bool CustomPaintPaintMethod::HasShadow() const
{
    return !(NearZero(state_.shadow.GetOffset().GetX()) && NearZero(state_.shadow.GetOffset().GetY()) &&
             NearZero(state_.shadow.GetBlurRadius()));
}

void CustomPaintPaintMethod::UpdateLineDash(RSPen& pen)
{
    if (!state_.strokeState.GetLineDash().lineDash.empty()) {
        auto lineDashState = state_.strokeState.GetLineDash().lineDash;
        RSScalar intervals[lineDashState.size()];
        for (size_t i = 0; i < lineDashState.size(); ++i) {
            intervals[i] = static_cast<RSScalar>(lineDashState[i]);
        }
        RSScalar phase = static_cast<RSScalar>(state_.strokeState.GetLineDash().dashOffset);
        pen.SetPathEffect(RSPathEffect::CreateDashPathEffect(intervals, lineDashState.size(), phase));
    }
}

void CustomPaintPaintMethod::UpdateFontFamilies()
{
    auto context = context_.Upgrade();
    if (!context) {
        context = PipelineBase::GetCurrentContextSafely();
    }
    CHECK_NULL_VOID(context);
    auto fontManager = context->GetFontManager();
    CHECK_NULL_VOID(fontManager);
    if (!fontManager->IsUseAppCustomFont()) {
        return;
    }
    auto fontFamilies = Framework::ConvertStrToFontFamilies(fontManager->GetAppCustomFont());
    if (state_.fillState.GetTextStyle().GetFontFamilies().empty()) {
        state_.fillState.SetFontFamilies(fontFamilies);
    }
    if (state_.strokeState.GetTextStyle().GetFontFamilies().empty()) {
        state_.strokeState.SetFontFamilies(fontFamilies);
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

void CustomPaintPaintMethod::UpdatePaintShader(RSPen* pen, RSBrush* brush, const Ace::Gradient& gradient)
{
    RSPoint beginPoint = RSPoint(static_cast<RSScalar>(gradient.GetBeginOffset().GetX()),
        static_cast<RSScalar>(gradient.GetBeginOffset().GetY()));
    RSPoint endPoint = RSPoint(static_cast<RSScalar>(gradient.GetEndOffset().GetX()),
        static_cast<RSScalar>(gradient.GetEndOffset().GetY()));
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
    matrix.SetMatrix(pattern.GetScaleX(), pattern.GetSkewX(), pattern.GetTranslateX(), pattern.GetSkewY(),
        pattern.GetScaleY(), pattern.GetTranslateY(), 0.0f, 0.0f, 1.0f);
    return matrix;
}

std::shared_ptr<RSImage> CustomPaintPaintMethod::GetImage(const std::string& src)
{
#ifndef ACE_UNITTEST
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
#else
    return nullptr;
#endif
}

void CustomPaintPaintMethod::UpdatePaintShader(const Ace::Pattern& pattern, RSPen* pen, RSBrush* brush)
{
#ifndef ACE_UNITTEST
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
#endif
}

void CustomPaintPaintMethod::InitPaintBlend(RSBrush& brush)
{
    brush.SetBlendMode(ConvertEnumToDrawingEnum(
        state_.globalState.GetType(), DRAWING_BLEND_MODE_TABLE, BLEND_MODE_SIZE, RSBlendMode::SRC_OVER));
}

void CustomPaintPaintMethod::InitPaintBlend(RSPen& pen)
{
    pen.SetBlendMode(ConvertEnumToDrawingEnum(
        state_.globalState.GetType(), DRAWING_BLEND_MODE_TABLE, BLEND_MODE_SIZE, RSBlendMode::SRC_OVER));
}

void CustomPaintPaintMethod::GetFillPaint(RSBrush& brush, RSSamplingOptions& options)
{
    InitImagePaint(nullptr, &brush, options);
    brush.SetAntiAlias(antiAlias_);
    if (state_.fillState.GetPaintStyle() == OHOS::Ace::PaintStyle::Color) {
        brush.SetColor(state_.fillState.GetColor().GetValue());
    }
    if (state_.fillState.GetGradient().IsValid() && state_.fillState.GetPaintStyle() == PaintStyle::Gradient) {
        UpdatePaintShader(nullptr, &brush, state_.fillState.GetGradient());
    }
    if (state_.fillState.GetPatternValue().IsValid() && state_.fillState.GetPaintStyle() == PaintStyle::ImagePattern) {
        UpdatePaintShader(state_.fillState.GetPatternValue(), nullptr, &brush);
    }
    if (state_.globalState.HasGlobalAlpha()) {
        if (state_.fillState.GetPaintStyle() == OHOS::Ace::PaintStyle::Color) {
            brush.SetAlphaF(state_.globalState.GetAlpha() *
                            static_cast<double>(state_.fillState.GetColor().GetAlpha()) / MAX_GRAYSCALE);
        } else {
            brush.SetAlphaF(state_.globalState.GetAlpha());
        }
    }
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
    if (state_.strokeState.GetPaintStyle() == PaintStyle::Color) {
        pen.SetColor(state_.strokeState.GetColor().GetValue());
    }
    if (state_.strokeState.GetGradient().IsValid() && state_.strokeState.GetPaintStyle() == PaintStyle::Gradient) {
        UpdatePaintShader(&pen, nullptr, state_.strokeState.GetGradient());
    }
    if (state_.strokeState.GetPatternValue().IsValid() &&
        state_.strokeState.GetPaintStyle() == PaintStyle::ImagePattern) {
        UpdatePaintShader(state_.strokeState.GetPatternValue(), &pen, nullptr);
    }
    pen.SetAntiAlias(antiAlias_);
    pen.SetJoinStyle(ConvertEnumToDrawingEnum(
        state_.strokeState.GetLineJoin(), skLineJoinTable, ArraySize(skLineJoinTable), RSPen::JoinStyle::MITER_JOIN));
    pen.SetCapStyle(ConvertEnumToDrawingEnum(
        state_.strokeState.GetLineCap(), skLineCapTable, ArraySize(skLineCapTable), RSPen::CapStyle::FLAT_CAP));
    pen.SetWidth(static_cast<RSScalar>(state_.strokeState.GetLineWidth()));
    pen.SetMiterLimit(static_cast<RSScalar>(state_.strokeState.GetMiterLimit()));

    // set line Dash
    UpdateLineDash(pen);

    // set global alpha
    if (state_.globalState.HasGlobalAlpha()) {
        if (state_.strokeState.GetPaintStyle() == PaintStyle::Color) {
            pen.SetAlphaF(state_.globalState.GetAlpha() *
                          static_cast<double>(state_.strokeState.GetColor().GetAlpha()) / MAX_GRAYSCALE);
        } else {
            pen.SetAlphaF(state_.globalState.GetAlpha());
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

void CustomPaintPaintMethod::DrawSvgImage(
    RefPtr<SvgDomBase> svgDom, const Ace::CanvasImage& canvasImage, const ImageFit& imageFit)
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
    OffsetF startPoint =
        OffsetF(dstRect.GetLeft(), dstRect.GetTop()) - OffsetF(srcRect.GetLeft() * scaleX, srcRect.GetTop() * scaleY);

    CHECK_NULL_VOID(rsCanvas_);
    rsCanvas_->Save();
    rsCanvas_->ClipRect(dstRect, RSClipOp::INTERSECT);
    rsCanvas_->Translate(startPoint.GetX(), startPoint.GetY());
    rsCanvas_->Scale(scaleX, scaleY);
    svgDom->DrawImage(*rsCanvas_, imageFit, Size(srcRect.GetWidth(), srcRect.GetHeight()));
    rsCanvas_->Restore();
}

void CustomPaintPaintMethod::DrawImageInternal(
    const Ace::CanvasImage& canvasImage, const std::shared_ptr<RSImage>& image)
{
    RSBrush compositeOperationpBrush;
    InitPaintBlend(compositeOperationpBrush);
    RSSaveLayerOps slo(nullptr, &compositeOperationpBrush);
    if (state_.globalState.GetType() != CompositeOperation::SOURCE_OVER) {
        rsCanvas_->SaveLayer(slo);
    }
    imageBrush_.SetAntiAlias(antiAlias_);
    InitImagePaint(nullptr, &imageBrush_, sampleOptions_);
    if (state_.globalState.HasGlobalAlpha()) {
        imageBrush_.SetAlphaF(state_.globalState.GetAlpha());
    }
    if (HasShadow()) {
        RSRect rsRect = RSRect(
            canvasImage.dx, canvasImage.dy, canvasImage.dWidth + canvasImage.dx, canvasImage.dHeight + canvasImage.dy);
        RSPath path;
        path.AddRect(rsRect);
        PaintImageShadow(path, state_.shadow, &imageBrush_, nullptr,
            (state_.globalState.GetType() != CompositeOperation::SOURCE_OVER) ? &slo : nullptr);
    }
    rsCanvas_->AttachBrush(imageBrush_);
    switch (canvasImage.flag) {
        case DrawImageType::THREE_PARAMS:
            rsCanvas_->DrawImage(*image, canvasImage.dx, canvasImage.dy, sampleOptions_);
            break;
        case DrawImageType::FIVE_PARAMS: {
            RSRect rect = RSRect(canvasImage.dx, canvasImage.dy, canvasImage.dWidth + canvasImage.dx,
                canvasImage.dHeight + canvasImage.dy);
            rsCanvas_->DrawImageRect(*image, rect, sampleOptions_);
            break;
        }
        case DrawImageType::NINE_PARAMS: {
            RSRect dstRect = RSRect(canvasImage.dx, canvasImage.dy, canvasImage.dWidth + canvasImage.dx,
                canvasImage.dHeight + canvasImage.dy);
            RSRect srcRect = RSRect(canvasImage.sx, canvasImage.sy, canvasImage.sWidth + canvasImage.sx,
                canvasImage.sHeight + canvasImage.sy);
            rsCanvas_->DrawImageRect(*image, srcRect, dstRect, sampleOptions_,
                RSSrcRectConstraint::FAST_SRC_RECT_CONSTRAINT);
            break;
        }
        default:
            break;
    }
    rsCanvas_->DetachBrush();
    if (state_.globalState.GetType() != CompositeOperation::SOURCE_OVER) {
        rsCanvas_->Restore();
    }
}

void CustomPaintPaintMethod::DrawImage(const Ace::CanvasImage& canvasImage, double width, double height)
{
#ifndef ACE_UNITTEST
    ContainerScope scope(canvasImage.instanceId);
    auto context = PipelineBase::GetCurrentContext();
    auto image = std::make_shared<RSImage>();
    if (canvasImage.imageData != nullptr) {
        auto imageData = *(canvasImage.imageData);
        if (imageData.data.empty()) {
            return;
        }
        RSBitmap bitmap;
        RSBitmapFormat format { RSColorType::COLORTYPE_BGRA_8888, RSAlphaType::ALPHATYPE_OPAQUE };
        bitmap.Build(imageData.dirtyWidth, imageData.dirtyHeight, format);
        bitmap.SetPixels(const_cast<void*>(reinterpret_cast<const void*>(imageData.data.data())));
        image->BuildFromBitmap(bitmap);
    } else {
        image = Ace::ImageProvider::GetDrawingImage(
            canvasImage.src, context, Size(std::max(width, 0.0), std::max(height, 0.0)));
    }
    CHECK_NULL_VOID(image);
    DrawImageInternal(canvasImage, image);
#endif
}

void CustomPaintPaintMethod::PutImageData(const Ace::ImageData& imageData)
{
    if (imageData.data.empty()) {
        return;
    }
    RSBitmap bitmap;
    RSBitmapFormat format { RSColorType::COLORTYPE_BGRA_8888, RSAlphaType::ALPHATYPE_OPAQUE };
    bitmap.Build(imageData.dirtyWidth, imageData.dirtyHeight, format);
    bitmap.SetPixels(const_cast<void*>(reinterpret_cast<const void*>(imageData.data.data())));
    RSBrush brush;
    brush.SetBlendMode(RSBlendMode::SRC);
    rsCanvas_->AttachBrush(brush);
    rsCanvas_->DrawBitmap(bitmap, imageData.x, imageData.y);
    rsCanvas_->DetachBrush();
}

void CustomPaintPaintMethod::FillRect(const Rect& rect)
{
    RSBrush brush;
    RSSamplingOptions options;
    GetFillPaint(brush, options);
    RSRect rsRect(rect.Left(), rect.Top(), rect.Right(), +rect.Bottom());
    if (state_.globalState.GetType() == CompositeOperation::SOURCE_OVER) {
        if (HasShadow()) {
            RSRecordingPath path;
            path.AddRect(rsRect);
            PaintShadow(path, state_.shadow, &brush, nullptr);
        }
        rsCanvas_->AttachBrush(brush);
        rsCanvas_->DrawRect(rsRect);
        rsCanvas_->DetachBrush();
    } else {
        RSBrush compositeOperationpBrush;
        InitPaintBlend(compositeOperationpBrush);
        RSSaveLayerOps slo(nullptr, &compositeOperationpBrush);
        if (HasShadow()) {
            RSRecordingPath path;
            path.AddRect(rsRect);
            PaintShadow(path, state_.shadow, &brush, nullptr, &slo);
        }
        rsCanvas_->SaveLayer(slo);
        rsCanvas_->AttachBrush(brush);
        rsCanvas_->DrawRect(rsRect);
        rsCanvas_->DetachBrush();
        rsCanvas_->Restore();
    }
}

void CustomPaintPaintMethod::StrokeRect(const Rect& rect)
{
    RSPen pen;
    RSSamplingOptions options;
    GetStrokePaint(pen, options);
    RSRect rsRect(rect.Left(), rect.Top(), rect.Right(), +rect.Bottom());
    if (state_.globalState.GetType() == CompositeOperation::SOURCE_OVER) {
        if (HasShadow()) {
            RSRecordingPath path;
            path.AddRect(rsRect);
            PaintShadow(path, state_.shadow, nullptr, &pen);
        }
        rsCanvas_->AttachPen(pen);
        rsCanvas_->DrawRect(rsRect);
        rsCanvas_->DetachPen();
    } else {
        RSBrush compositeOperationpBrush;
        InitPaintBlend(compositeOperationpBrush);
        RSSaveLayerOps slo(nullptr, &compositeOperationpBrush);
        if (HasShadow()) {
            RSRecordingPath path;
            path.AddRect(rsRect);
            PaintShadow(path, state_.shadow, nullptr, &pen, &slo);
        }
        rsCanvas_->SaveLayer(slo);
        rsCanvas_->AttachPen(pen);
        rsCanvas_->DrawRect(rsRect);
        rsCanvas_->DetachPen();
        rsCanvas_->Restore();
    }
}

void CustomPaintPaintMethod::ClearRect(const Rect& rect)
{
    RSBrush brush;
    RSSamplingOptions options;
    InitImagePaint(nullptr, &brush, options);
    brush.SetAntiAlias(antiAlias_);
    brush.SetBlendMode(RSBlendMode::CLEAR);
    RSRect rsRect(rect.Left(), rect.Top(), rect.Right(), rect.Bottom());
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

void CustomPaintPaintMethod::Fill()
{
    RSBrush brush;
    RSSamplingOptions options;
    GetFillPaint(brush, options);
    if (state_.globalState.GetType() == CompositeOperation::SOURCE_OVER) {
        if (HasShadow()) {
            PaintShadow(rsPath_, state_.shadow, &brush, nullptr);
        }
        rsCanvas_->AttachBrush(brush);
        rsCanvas_->DrawPath(rsPath_);
        rsCanvas_->DetachBrush();
    } else {
        RSBrush compositeOperationpBrush;
        InitPaintBlend(compositeOperationpBrush);
        RSSaveLayerOps slo(nullptr, &compositeOperationpBrush);
        if (HasShadow()) {
            PaintShadow(rsPath_, state_.shadow, &brush, nullptr, &slo);
        }
        rsCanvas_->SaveLayer(slo);
        rsCanvas_->AttachBrush(brush);
        rsCanvas_->DrawPath(rsPath_);
        rsCanvas_->DetachBrush();
        rsCanvas_->Restore();
    }
}

void CustomPaintPaintMethod::Fill(const RefPtr<CanvasPath2D>& path)
{
    CHECK_NULL_VOID(path);
    ParsePath2D(path);
    Path2DFill();
    rsPath2d_.Reset();
}

void CustomPaintPaintMethod::Path2DFill()
{
    RSBrush brush;
    RSSamplingOptions options;
    GetFillPaint(brush, options);
    if (state_.globalState.GetType() == CompositeOperation::SOURCE_OVER) {
        if (HasShadow()) {
            PaintShadow(rsPath2d_, state_.shadow, &brush, nullptr);
        }
        rsCanvas_->AttachBrush(brush);
        rsCanvas_->DrawPath(rsPath2d_);
        rsCanvas_->DetachBrush();
    } else {
        RSBrush compositeOperationpBrush;
        InitPaintBlend(compositeOperationpBrush);
        RSSaveLayerOps slo(nullptr, &compositeOperationpBrush);
        if (HasShadow()) {
            PaintShadow(rsPath2d_, state_.shadow, &brush, nullptr, &slo);
        }
        rsCanvas_->SaveLayer(slo);
        rsCanvas_->AttachBrush(brush);
        rsCanvas_->DrawPath(rsPath2d_);
        rsCanvas_->DetachBrush();
        rsCanvas_->Restore();
    }
}

void CustomPaintPaintMethod::Stroke()
{
    RSPen pen;
    RSSamplingOptions options;
    GetStrokePaint(pen, options);
    if (state_.globalState.GetType() == CompositeOperation::SOURCE_OVER) {
        if (HasShadow()) {
            PaintShadow(rsPath_, state_.shadow, nullptr, &pen);
        }
        rsCanvas_->AttachPen(pen);
        rsCanvas_->DrawPath(rsPath_);
        rsCanvas_->DetachPen();
    } else {
        RSBrush compositeOperationpBrush;
        InitPaintBlend(compositeOperationpBrush);
        RSSaveLayerOps slo(nullptr, &compositeOperationpBrush);
        if (HasShadow()) {
            PaintShadow(rsPath_, state_.shadow, nullptr, &pen, &slo);
        }
        rsCanvas_->SaveLayer(slo);
        rsCanvas_->AttachPen(pen);
        rsCanvas_->DrawPath(rsPath_);
        rsCanvas_->DetachPen();
        rsCanvas_->Restore();
    }
}

void CustomPaintPaintMethod::Stroke(const RefPtr<CanvasPath2D>& path)
{
    CHECK_NULL_VOID(path);
    ParsePath2D(path);
    Path2DStroke();
    rsPath2d_.Reset();
}

void CustomPaintPaintMethod::Path2DStroke()
{
    RSPen pen;
    RSSamplingOptions options;
    GetStrokePaint(pen, options);
    if (state_.globalState.GetType() == CompositeOperation::SOURCE_OVER) {
        if (HasShadow()) {
            PaintShadow(rsPath2d_, state_.shadow, nullptr, &pen);
        }
        rsCanvas_->AttachPen(pen);
        rsCanvas_->DrawPath(rsPath2d_);
        rsCanvas_->DetachPen();
    } else {
        RSBrush compositeOperationpBrush;
        InitPaintBlend(compositeOperationpBrush);
        RSSaveLayerOps slo(nullptr, &compositeOperationpBrush);
        if (HasShadow()) {
            PaintShadow(rsPath2d_, state_.shadow, nullptr, &pen, &slo);
        }
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
    ParsePath2D(path);
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

void CustomPaintPaintMethod::MoveTo(double x, double y)
{
    rsPath_.MoveTo(static_cast<RSScalar>(x), static_cast<RSScalar>(y));
}

void CustomPaintPaintMethod::LineTo(double x, double y)
{
    rsPath_.LineTo(static_cast<RSScalar>(x), static_cast<RSScalar>(y));
}

void CustomPaintPaintMethod::Arc(const ArcParam& param)
{
    double left = param.x - param.radius;
    double top = param.y - param.radius;
    double right = param.x + param.radius;
    double bottom = param.y + param.radius;
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
    } else if (!NearEqual(std::fmod(sweepAngle, FULL_CIRCLE_ANGLE), 0.0) && std::abs(sweepAngle) > FULL_CIRCLE_ANGLE) {
        double half = GreatNotEqual(sweepAngle, 0.0) ? HALF_CIRCLE_ANGLE : -HALF_CIRCLE_ANGLE;
        rsPath_.ArcTo(point1, point2, static_cast<RSScalar>(startAngle), static_cast<RSScalar>(half));
        rsPath_.ArcTo(point1, point2, static_cast<RSScalar>(half + startAngle), static_cast<RSScalar>(half));
        rsPath_.ArcTo(
            point1, point2, static_cast<RSScalar>(half + half + startAngle), static_cast<RSScalar>(sweepAngle));
    } else {
        rsPath_.ArcTo(point1, point2, static_cast<RSScalar>(startAngle), static_cast<RSScalar>(sweepAngle));
    }
}

void CustomPaintPaintMethod::ArcTo(const ArcToParam& param)
{
    rsPath_.ArcTo(static_cast<RSScalar>(param.x1), static_cast<RSScalar>(param.y1), static_cast<RSScalar>(param.x2),
        static_cast<RSScalar>(param.y2), static_cast<RSScalar>(param.radius));
}

void CustomPaintPaintMethod::AddRect(const Rect& rect)
{
    RSRect rsRect(rect.Left(), rect.Top(), rect.Right(), rect.Bottom());
    rsPath_.AddRect(rsRect);
}

void CustomPaintPaintMethod::Ellipse(const EllipseParam& param)
{
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
    double left = param.x - param.radiusX;
    double top = param.y - param.radiusY;
    double right = param.x + param.radiusX;
    double bottom = param.y + param.radiusY;
    RSPoint point1(left, top);
    RSPoint point2(right, bottom);
    if (!NearZero(rotation)) {
        RSMatrix matrix;
        matrix.Rotate(-rotation, param.x, param.y);
        rsPath_.Transform(matrix);
    }
    if (NearEqual(std::abs(std::fmod(sweepAngle, FULL_CIRCLE_ANGLE)), 0.0) ||
        NearEqual(std::abs(std::fmod(sweepAngle, FULL_CIRCLE_ANGLE)), FULL_CIRCLE_ANGLE)) {
        double half = GreatNotEqual(sweepAngle, 0.0) ? HALF_CIRCLE_ANGLE : -HALF_CIRCLE_ANGLE;
        rsPath_.ArcTo(point1, point2, static_cast<RSScalar>(startAngle), static_cast<RSScalar>(half));
        rsPath_.ArcTo(point1, point2, static_cast<RSScalar>(half + startAngle), static_cast<RSScalar>(half));
    } else if (!NearEqual(std::fmod(sweepAngle, FULL_CIRCLE_ANGLE), 0.0) && std::abs(sweepAngle) > FULL_CIRCLE_ANGLE) {
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
        matrix.Rotate(rotation, param.x, param.y);
        rsPath_.Transform(matrix);
    }
}

void CustomPaintPaintMethod::BezierCurveTo(const BezierCurveParam& param)
{
    rsPath_.CubicTo(static_cast<RSScalar>(param.cp1x),
        static_cast<RSScalar>(param.cp1y), static_cast<RSScalar>(param.cp2x),
        static_cast<RSScalar>(param.cp2y), static_cast<RSScalar>(param.x),
        static_cast<RSScalar>(param.y));
}

void CustomPaintPaintMethod::QuadraticCurveTo(const QuadraticCurveParam& param)
{
    rsPath_.QuadTo(static_cast<RSScalar>(param.cpx), static_cast<RSScalar>(param.cpy),
        static_cast<RSScalar>(param.x), static_cast<RSScalar>(param.y));
}

void CustomPaintPaintMethod::ParsePath2D(const RefPtr<CanvasPath2D>& path)
{
    for (const auto& [cmd, args] : path->GetCaches()) {
        switch (cmd) {
            case PathCmd::CMDS:
                Path2DAddPath(args);
                break;
            case PathCmd::TRANSFORM:
                Path2DSetTransform(args);
                break;
            case PathCmd::MOVE_TO:
                Path2DMoveTo(args);
                break;
            case PathCmd::LINE_TO:
                Path2DLineTo(args);
                break;
            case PathCmd::ARC:
                Path2DArc(args);
                break;
            case PathCmd::ARC_TO:
                Path2DArcTo(args);
                break;
            case PathCmd::QUADRATIC_CURVE_TO:
                Path2DQuadraticCurveTo(args);
                break;
            case PathCmd::BEZIER_CURVE_TO:
                Path2DBezierCurveTo(args);
                break;
            case PathCmd::ELLIPSE:
                Path2DEllipse(args);
                break;
            case PathCmd::RECT:
                Path2DRect(args);
                break;
            case PathCmd::CLOSE_PATH:
                Path2DClosePath();
                break;
            default:
                break;
        }
    }
}

void CustomPaintPaintMethod::Path2DAddPath(const PathArgs& args)
{
    RSRecordingPath out;
    out.BuildFromSVGString(args.cmds);
    rsPath2d_.AddPath(out);
}

void CustomPaintPaintMethod::Path2DClosePath()
{
    rsPath2d_.Close();
}

void CustomPaintPaintMethod::Path2DMoveTo(const PathArgs& args)
{
    rsPath2d_.MoveTo(args.para1, args.para2);
}

void CustomPaintPaintMethod::Path2DLineTo(const PathArgs& args)
{
    rsPath2d_.LineTo(args.para1, args.para2);
}

void CustomPaintPaintMethod::Path2DArc(const PathArgs& args)
{
    RSPoint point1(args.para1 - args.para3, args.para2 - args.para3);
    RSPoint point2(args.para1 + args.para3, args.para2 + args.para3);
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
    } else if (!NearEqual(std::fmod(sweepAngle, FULL_CIRCLE_ANGLE), 0.0) && std::abs(sweepAngle) > FULL_CIRCLE_ANGLE) {
        double half = GreatNotEqual(sweepAngle, 0.0) ? HALF_CIRCLE_ANGLE : -HALF_CIRCLE_ANGLE;
        rsPath2d_.ArcTo(point1, point2, static_cast<RSScalar>(startAngle), static_cast<RSScalar>(half));
        rsPath2d_.ArcTo(point1, point2, static_cast<RSScalar>(half + startAngle), static_cast<RSScalar>(half));
        rsPath2d_.ArcTo(
            point1, point2, static_cast<RSScalar>(half + half + startAngle), static_cast<RSScalar>(sweepAngle));
    } else {
        rsPath2d_.ArcTo(point1, point2, startAngle, sweepAngle);
    }
}

void CustomPaintPaintMethod::Path2DArcTo(const PathArgs& args)
{
    rsPath2d_.ArcTo(static_cast<RSScalar>(args.para1), static_cast<RSScalar>(args.para2),
        static_cast<RSScalar>(args.para3), static_cast<RSScalar>(args.para4), static_cast<RSScalar>(args.para5));
}

void CustomPaintPaintMethod::Path2DEllipse(const PathArgs& args)
{
    if (NearEqual(args.para6, args.para7)) {
        return; // Just return when startAngle is same as endAngle.
    }

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
    RSPoint point1(args.para1 - args.para3, args.para2 - args.para4);
    RSPoint point2(args.para1 + args.para3, args.para2 + args.para4);

    if (!NearZero(rotation)) {
        RSMatrix matrix;
        matrix.Rotate(-rotation, args.para1, args.para2);
        rsPath2d_.Transform(matrix);
    }
    if (NearEqual(std::abs(std::fmod(sweepAngle, FULL_CIRCLE_ANGLE)), 0.0) ||
        NearEqual(std::abs(std::fmod(sweepAngle, FULL_CIRCLE_ANGLE)), FULL_CIRCLE_ANGLE)) {
        double half = GreatNotEqual(sweepAngle, 0.0) ? HALF_CIRCLE_ANGLE : -HALF_CIRCLE_ANGLE;
        rsPath2d_.ArcTo(point1, point2, static_cast<RSScalar>(startAngle), static_cast<RSScalar>(half));
        rsPath2d_.ArcTo(point1, point2, static_cast<RSScalar>(half + startAngle), static_cast<RSScalar>(half));
    } else if (!NearEqual(std::fmod(sweepAngle, FULL_CIRCLE_ANGLE), 0.0) && std::abs(sweepAngle) > FULL_CIRCLE_ANGLE) {
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
        matrix.Rotate(rotation, args.para1, args.para2);
        rsPath2d_.Transform(matrix);
    }
}

void CustomPaintPaintMethod::Path2DBezierCurveTo(const PathArgs& args)
{
    rsPath2d_.CubicTo(args.para1, args.para2, args.para3, args.para4, args.para5, args.para6);
}

void CustomPaintPaintMethod::Path2DQuadraticCurveTo(const PathArgs& args)
{
    rsPath2d_.QuadTo(args.para1, args.para2, args.para3, args.para4);
}

void CustomPaintPaintMethod::Path2DSetTransform(const PathArgs& args)
{
    RSMatrix matrix;
    matrix.SetMatrix(args.para1, args.para3, args.para5, args.para2, args.para4, args.para6, 0, 0, 1);
    rsPath2d_.Transform(matrix);
}

void CustomPaintPaintMethod::Save()
{
    saveStates_.push_back(state_);
    saveColorFilter_.push_back(colorFilter_);
    saveBlurFilter_.push_back(blurFilter_);
    rsCanvas_->Save();
}

void CustomPaintPaintMethod::Restore()
{
    if ((rsCanvas_->GetSaveCount() > DEFAULT_SAVE_COUNT) && (!saveStates_.empty()) && (!saveColorFilter_.empty()) &&
        (!saveBlurFilter_.empty())) {
        state_ = saveStates_.back();
        saveStates_.pop_back();
        colorFilter_ = saveColorFilter_.back();
        saveColorFilter_.pop_back();
        blurFilter_ = saveBlurFilter_.back();
        saveBlurFilter_.pop_back();
        rsCanvas_->Restore();
    }
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

void CustomPaintPaintMethod::FillText(const std::string& text, double x, double y, std::optional<double> maxWidth)
{
    auto success = UpdateFillParagraph(text);
    CHECK_NULL_VOID(success);
    PaintText(lastLayoutSize_.Width(), x, y, maxWidth, false);
}

void CustomPaintPaintMethod::StrokeText(const std::string& text, double x, double y, std::optional<double> maxWidth)
{
    auto success = UpdateStrokeParagraph(text);
    CHECK_NULL_VOID(success);
    PaintText(lastLayoutSize_.Width(), x, y, maxWidth, true);
}

void CustomPaintPaintMethod::PaintText(
    const float width, double x, double y, std::optional<double> maxWidth, bool isStroke)
{
    CHECK_NULL_VOID(paragraph_);
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TEN)) {
        paragraph_->Layout(FLT_MAX);
    } else {
        paragraph_->Layout(width);
    }
    if (width > paragraph_->GetMaxIntrinsicWidth()) {
        paragraph_->Layout(std::ceil(paragraph_->GetMaxIntrinsicWidth()));
    }
    auto align = isStroke ? state_.strokeState.GetTextAlign() : state_.fillState.GetTextAlign();
    double dx = 0.0;
    if (maxWidth.has_value() && (maxWidth.value() < paragraph_->GetMaxIntrinsicWidth())) {
        dx = x + GetAlignOffset(align, maxWidth.value());
    } else {
        dx = x + GetAlignOffset(align, paragraph_->GetMaxIntrinsicWidth());
    }
    auto baseline = isStroke ? state_.strokeState.GetTextStyle().GetTextBaseline()
                             : state_.fillState.GetTextStyle().GetTextBaseline();
    double dy = y + GetBaselineOffset(baseline, paragraph_);

    std::optional<double> scale = CalcTextScale(paragraph_->GetMaxIntrinsicWidth(), maxWidth);
    RSBrush compositeOperationpBrush;
    InitPaintBlend(compositeOperationpBrush);
    RSSaveLayerOps slo(nullptr, &compositeOperationpBrush);
    if (state_.globalState.GetType() != CompositeOperation::SOURCE_OVER) {
        rsCanvas_->SaveLayer(slo);
    }
    if (isStroke && shadowParagraph_ != nullptr && HasShadow()) {
        PaintStrokeTextShadow(width, dx, dy, scale, &slo);
    }
    if (scale.has_value()) {
        if (!NearZero(scale.value())) {
            dx /= scale.value();
        }
        rsCanvas_->Save();
        rsCanvas_->Scale(scale.value(), 1.0);
        paragraph_->Paint(rsCanvas_.get(), dx, dy);
        rsCanvas_->Restore();
    } else {
        paragraph_->Paint(rsCanvas_.get(), dx, dy);
    }
    if (state_.globalState.GetType() != CompositeOperation::SOURCE_OVER) {
        rsCanvas_->Restore();
    }
}

void CustomPaintPaintMethod::PaintStrokeTextShadow(
    const float width, const double dx, const double dy, const std::optional<double> scale, RSSaveLayerOps* slo)
{
    CHECK_NULL_VOID(shadowParagraph_);
    if (state_.globalState.GetType() != CompositeOperation::SOURCE_OVER) {
        rsCanvas_->SaveLayer(*slo);
    }
    double finalDx = dx;
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TEN)) {
        shadowParagraph_->Layout(FLT_MAX);
    } else {
        shadowParagraph_->Layout(width);
    }
    if (width > shadowParagraph_->GetMaxIntrinsicWidth()) {
        shadowParagraph_->Layout(std::ceil(shadowParagraph_->GetMaxIntrinsicWidth()));
    }
    rsCanvas_->Save();
    auto shadowOffsetX = state_.shadow.GetOffset().GetX();
    auto shadowOffsetY = state_.shadow.GetOffset().GetY();
    if (scale.has_value()) {
        if (!NearZero(scale.value())) {
            finalDx /= scale.value();
            shadowOffsetX /= scale.value();
        }
        rsCanvas_->Scale(scale.value(), 1.0);
    }
    shadowParagraph_->Paint(rsCanvas_.get(), finalDx + shadowOffsetX, dy + shadowOffsetY);
    rsCanvas_->Restore();
    if (state_.globalState.GetType() != CompositeOperation::SOURCE_OVER) {
        rsCanvas_->Restore();
    }
}

double CustomPaintPaintMethod::GetAlignOffset(TextAlign align, double width)
{
    double x = 0.0;
    TextDirection textDirection = state_.fillState.GetOffTextDirection();
    switch (align) {
        case TextAlign::LEFT:
            x = 0.0;
            break;
        case TextAlign::START:
            x = (textDirection == TextDirection::LTR) ? 0.0 : -width;
            break;
        case TextAlign::RIGHT:
            x = -width;
            break;
        case TextAlign::END:
            x = (textDirection == TextDirection::LTR) ? -width : 0.0;
            break;
        case TextAlign::CENTER:
            x = -width * HALF;
            break;
        default:
            x = 0.0;
            break;
    }
    return x;
}

double CustomPaintPaintMethod::GetBaselineOffset(TextBaseline baseline, std::unique_ptr<RSParagraph>& paragraph)
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
            y = -paragraph->GetHeight() * HALF;
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

#ifndef ACE_UNITTEST
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

double CustomPaintPaintMethod::GetFontAlign(TextAlign align, std::unique_ptr<RSParagraph>& paragraph) const
{
    TextDirection textDirection = state_.fillState.GetOffTextDirection();
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
#endif

RSTextAlign CustomPaintPaintMethod::GetEffectiveAlign(RSTextAlign align, RSTextDirection direction) const
{
    if (align == RSTextAlign::START) {
        return (direction == RSTextDirection::LTR) ? RSTextAlign::LEFT : RSTextAlign::RIGHT;
    } else if (align == RSTextAlign::END) {
        return (direction == RSTextDirection::LTR) ? RSTextAlign::RIGHT : RSTextAlign::LEFT;
    } else {
        return align;
    }
}

void CustomPaintPaintMethod::ClearPaintImage(RSPen* pen, RSBrush* brush)
{
    RSFilter filter;
    RSColorMatrix colorMatrix;
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
    if (pen) {
        auto filter = pen->GetFilter();
        filter.SetColorFilter(colorFilter_);
        filter.SetImageFilter(blurFilter_);
        pen->SetFilter(filter);
    }
    if (brush) {
        auto filter = brush->GetFilter();
        filter.SetColorFilter(colorFilter_);
        filter.SetImageFilter(blurFilter_);
        brush->SetFilter(filter);
    }
}

void CustomPaintPaintMethod::SetFilterParam(const std::string& filterStr)
{
    std::vector<FilterProperty> filters;
    if (!GetFilterType(filterStr, filters)) {
        return;
    }
    colorMatrix_ = RSColorMatrix();
    colorFilter_ = RSColorFilter::CreateMatrixColorFilter(colorMatrix_);
    blurFilter_ = RSImageFilter::CreateBlurImageFilter(0, 0, RSTileMode::DECAL, nullptr);
    for (FilterProperty filter : filters) {
        switch (filter.filterType_) {
            case FilterType::NONE:
                break;
            case FilterType::GRAYSCALE:
                SetGrayFilter(filter.filterParam_);
                break;
            case FilterType::SEPIA:
                SetSepiaFilter(filter.filterParam_);
                break;
            case FilterType::SATURATE:
                SetSaturateFilter(filter.filterParam_);
                break;
            case FilterType::HUE_ROTATE:
                SetHueRotateFilter(filter.filterParam_);
                break;
            case FilterType::INVERT:
                SetInvertFilter(filter.filterParam_);
                break;
            case FilterType::OPACITY:
                SetOpacityFilter(filter.filterParam_);
                break;
            case FilterType::BRIGHTNESS:
                SetBrightnessFilter(filter.filterParam_);
                break;
            case FilterType::CONTRAST:
                SetContrastFilter(filter.filterParam_);
                break;
            case FilterType::BLUR:
                SetBlurFilter(filter.filterParam_);
                break;
            case FilterType::DROP_SHADOW:
                break;
            default:
                break;
        }
    }
    colorFilter_ = RSColorFilter::CreateMatrixColorFilter(colorMatrix_);
}

// https://drafts.fxtf.org/filter-effects/#grayscaleEquivalent
void CustomPaintPaintMethod::SetGrayFilter(const std::string& percent)
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
    RSColorMatrix colorMatrix;
    colorMatrix.SetArray(matrix);
    colorMatrix_.PreConcat(colorMatrix);
}

// https://drafts.fxtf.org/filter-effects/#sepiaEquivalent
void CustomPaintPaintMethod::SetSepiaFilter(const std::string& percent)
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
    RSColorMatrix colorMatrix;
    colorMatrix.SetArray(matrix);
    colorMatrix_.PreConcat(colorMatrix);
}

// https://drafts.fxtf.org/filter-effects/#saturateEquivalent
void CustomPaintPaintMethod::SetSaturateFilter(const std::string& percent)
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
    RSColorMatrix colorMatrix;
    colorMatrix.SetArray(matrix);
    colorMatrix_.PreConcat(colorMatrix);
}

// https://drafts.fxtf.org/filter-effects/#huerotateEquivalent
void CustomPaintPaintMethod::SetHueRotateFilter(const std::string& filterParam)
{
    std::string percent = filterParam;
    float rad = 0.0f;
    size_t index = percent.find("deg");
    if (index != std::string::npos) {
        percent.resize(index);
        rad = StringUtils::StringToFloat(percent);
        rad = rad / HALF_CIRCLE_ANGLE * M_PI;
    } else if ((index = percent.find("turn")) != std::string::npos) {
        percent.resize(index);
        rad = StringUtils::StringToFloat(percent);
        rad = rad * 2 * M_PI;
    } else if ((index = percent.find("rad")) != std::string::npos) {
        percent.resize(index);
        rad = StringUtils::StringToFloat(percent);
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
    RSColorMatrix colorMatrix;
    colorMatrix.SetArray(matrix);
    colorMatrix_.PreConcat(colorMatrix);
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
void CustomPaintPaintMethod::SetInvertFilter(const std::string& percent)
{
    float percentNum = 1.0f;
    if (!CheckNumberAndPercentage(percent, true, percentNum)) {
        return;
    }
    float matrix[20] = { 0.0f };
    matrix[0] = matrix[6] = matrix[12] = 1.0 - 2.0 * percentNum;
    matrix[4] = matrix[9] = matrix[14] = percentNum;
    matrix[18] = 1.0f;
    RSColorMatrix colorMatrix;
    colorMatrix.SetArray(matrix);
    colorMatrix_.PreConcat(colorMatrix);
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
void CustomPaintPaintMethod::SetOpacityFilter(const std::string& percent)
{
    float percentNum = 1.0f;
    if (!CheckNumberAndPercentage(percent, true, percentNum)) {
        return;
    }
    float matrix[20] = { 0.0f };
    matrix[0] = matrix[6] = matrix[12] = 1.0f;
    matrix[18] = percentNum;
    RSColorMatrix colorMatrix;
    colorMatrix.SetArray(matrix);
    colorMatrix_.PreConcat(colorMatrix);
}

/*
 * https://drafts.fxtf.org/filter-effects/#brightnessEquivalent
 * Example for R in RGB:
 * R' = funcR(R) = slope * R + intercept
 * where: slope = percentNum, intercept = 0
 */
void CustomPaintPaintMethod::SetBrightnessFilter(const std::string& percent)
{
    float percentNum = 1.0f;
    if (!CheckNumberAndPercentage(percent, false, percentNum)) {
        return;
    }
    float matrix[20] = { 0.0f };
    matrix[0] = matrix[6] = matrix[12] = percentNum;
    matrix[18] = 1.0f;
    RSColorMatrix colorMatrix;
    colorMatrix.SetArray(matrix);
    colorMatrix_.PreConcat(colorMatrix);
}

/*
 * https://drafts.fxtf.org/filter-effects/#contrastEquivalent
 * Example for R in RGB:
 * R' = funcR(R) = slope * R + intercept
 * where: slope = percentNum, intercept = 0.5 * (1 - percentNum)
 */
void CustomPaintPaintMethod::SetContrastFilter(const std::string& percent)
{
    float percentNum = 1.0f;
    if (!CheckNumberAndPercentage(percent, false, percentNum)) {
        return;
    }
    float matrix[20] = { 0.0f };
    matrix[0] = matrix[6] = matrix[12] = percentNum;
    matrix[4] = matrix[9] = matrix[14] = 0.5f * (1 - percentNum);
    matrix[18] = 1;
    RSColorMatrix colorMatrix;
    colorMatrix.SetArray(matrix);
    colorMatrix_.PreConcat(colorMatrix);
}

// https://drafts.fxtf.org/filter-effects/#blurEquivalent
void CustomPaintPaintMethod::SetBlurFilter(const std::string& percent)
{
    float blurNum = 0.0f;
    blurNum = BlurStrToDouble(percent);
    if (Negative(blurNum)) {
        return;
    }
    blurFilter_ =
        RSImageFilter::CreateBlurImageFilter(blurNum, blurNum, RSTileMode::DECAL, nullptr);
}

bool CustomPaintPaintMethod::GetFilterType(const std::string& filterStr, std::vector<FilterProperty>& filters)
{
    std::string paramData = filterStr;
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
    size_t index = percent.find("%");
    if (index != std::string::npos) {
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
        ret = StringUtils::StringToDouble(result);
    }
    return ret;
}

double CustomPaintPaintMethod::BlurStrToDouble(const std::string& str)
{
    double ret = 0;
    
    // check px case
    size_t index = str.find("px");
    if (index != std::string::npos) {
        std::string result = str.substr(0, index);
        ret = StringUtils::StringToDouble(result);
        return ret;
    }

    // check vp case
    index = str.find("vp");
    if (index != std::string::npos) {
        std::string result = str.substr(0, index);
        ret = StringUtils::StringToDouble(result);
        ret = ret * density_;
        return ret;
    }
    
    // check rem case
    index = str.find("rem");
    if (index != std::string::npos) {
        std::string result = str.substr(0, index);
        ret = StringUtils::StringToDouble(result);
        ret = ret * PX2REM_NUM;
        return ret;
    }

    ret = StringUtils::StringToDouble(str);
    return ret * density_;
}

float CustomPaintPaintMethod::PercentStrToFloat(const std::string& percentStr)
{
    std::string percentage = percentStr;
    bool hasPercent = IsPercentStr(percentage);
    float percentNum = 0.0f;
    percentNum = StringUtils::StringToFloat(percentage);
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
    CHECK_EQUAL_RETURN(param.size(), 0, false);
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
    param.scaleX = matrix_.Get(static_cast<int>(RSMatrix::Index::SCALE_X));
    param.scaleY = matrix_.Get(static_cast<int>(RSMatrix::Index::SCALE_Y));
    param.skewX = matrix_.Get(static_cast<int>(RSMatrix::Index::SKEW_X));
    param.skewY = matrix_.Get(static_cast<int>(RSMatrix::Index::SKEW_Y));
    param.translateX = matrix_.Get(static_cast<int>(RSMatrix::Index::TRANS_X));
    param.translateY = matrix_.Get(static_cast<int>(RSMatrix::Index::TRANS_Y));
    return param;
}

void CustomPaintPaintMethod::SaveProperties()
{
    matrixStates_.push_back(matrix_);
    lineDashStates_.push_back(lineDash_);
}

void CustomPaintPaintMethod::RestoreProperties()
{
    if (!matrixStates_.empty()) {
        matrix_ = matrixStates_.back();
        matrixStates_.pop_back();
    }
    if (!lineDashStates_.empty()) {
        lineDash_ = lineDashStates_.back();
        lineDashStates_.pop_back();
    }
}

void CustomPaintPaintMethod::ResetTransformMatrix()
{
    matrix_.Reset();
}

void CustomPaintPaintMethod::ResetLineDash()
{
    std::vector<double>().swap(lineDash_.lineDash);
    lineDash_.dashOffset = 0.0;
}

void CustomPaintPaintMethod::RotateMatrix(double angle)
{
    RSMatrix matrix;
    matrix.Rotate(angle * HALF_CIRCLE_ANGLE / M_PI, 0, 0);
    matrix_.PreConcat(matrix);
}

void CustomPaintPaintMethod::ScaleMatrix(double sx, double sy)
{
    RSMatrix matrix;
    matrix.SetScale(sx, sy);
    matrix_.PreConcat(matrix);
}

void CustomPaintPaintMethod::SetTransformMatrix(const TransformParam& param)
{
    matrix_.SetMatrix(
        param.scaleX, param.skewX, param.translateX, param.skewY, param.scaleY, param.translateY, 0, 0, 1);
}

void CustomPaintPaintMethod::TransformMatrix(const TransformParam& param)
{
    RSMatrix matrix;
    matrix.SetMatrix(param.scaleX, param.skewY, param.translateX, param.skewX, param.scaleY, param.translateY, 0, 0, 1);
    matrix_.PreConcat(matrix);
}

void CustomPaintPaintMethod::TranslateMatrix(double tx, double ty)
{
    if (tx || ty) {
        matrix_.PreTranslate(tx, ty);
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
    smoothingEnabled_ = true;
    smoothingQuality_ = "low";
    state_.fillState = PaintState();
    state_.strokeState = StrokePaintState();
    state_.globalState = GlobalPaintState();
    // The default value of the font size in canvas is 14px.
    SetFontSize(DEFAULT_FONT_SIZE);
    // The default value of TextAlign is TextAlign::START.
    SetDefaultTextAlign();
    state_.shadow = Shadow();
    imageBrush_ = RSBrush();
    rsPath_.Reset();
    rsPath2d_.Reset();
    std::vector<PaintHolder>().swap(saveStates_);
    std::vector<RSMatrix>().swap(matrixStates_);
    std::vector<LineDashParam>().swap(lineDashStates_);
    std::vector<std::shared_ptr<RSColorFilter>>().swap(saveColorFilter_);
    std::vector<std::shared_ptr<RSImageFilter>>().swap(saveBlurFilter_);
    colorMatrix_ = RSColorMatrix();
    colorFilter_ = RSColorFilter::CreateMatrixColorFilter(colorMatrix_);
    blurFilter_ = RSImageFilter::CreateBlurImageFilter(0, 0, RSTileMode::DECAL, nullptr);
}

void CustomPaintPaintMethod::PaintShadow(
    const RSPath& path, const Shadow& shadow, const RSBrush* brush, const RSPen* pen, RSSaveLayerOps* slo)
{
#ifndef ACE_UNITTEST
    CHECK_NULL_VOID(rsCanvas_);
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE) && slo != nullptr) {
        rsCanvas_->SaveLayer(*slo);
        RosenDecorationPainter::PaintShadow(path, shadow, rsCanvas_.get(), brush, pen);
        rsCanvas_->Restore();
    } else {
        RosenDecorationPainter::PaintShadow(path, shadow, rsCanvas_.get(), brush, pen);
    }
#endif
}

void CustomPaintPaintMethod::PaintImageShadow(
    const RSPath& path, const Shadow& shadow, const RSBrush* brush, const RSPen* pen, RSSaveLayerOps* slo)
{
#ifndef ACE_UNITTEST
    CHECK_NULL_VOID(rsCanvas_);
    RosenDecorationPainter::PaintShadow(path, shadow, rsCanvas_.get(), brush, pen);
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE) && slo != nullptr) {
        rsCanvas_->Restore();
        rsCanvas_->SaveLayer(*slo);
    }
#endif
}

void CustomPaintPaintMethod::Path2DRect(const PathArgs& args)
{
    rsPath2d_.AddRect(RSRect(args.para1, args.para2, args.para3 + args.para1, args.para4 + args.para2));
}

void CustomPaintPaintMethod::SetTransform(const TransformParam& param)
{
    RSMatrix rsMatrix;
    rsMatrix.SetMatrix(
        param.scaleX, param.skewX, param.translateX, param.skewY, param.scaleY, param.translateY, 0, 0, 1);
    rsCanvas_->SetMatrix(rsMatrix);
}

TextMetrics CustomPaintPaintMethod::MeasureTextMetrics(const std::string& text, const PaintState& state)
{
#ifndef ACE_UNITTEST
    TextMetrics textMetrics;
    RSParagraphStyle style;
    style.textAlign = Constants::ConvertTxtTextAlign(state.GetTextAlign());
    auto fontCollection = RosenFontCollection::GetInstance().GetFontCollection();
    CHECK_NULL_RETURN(fontCollection, textMetrics);
    std::unique_ptr<RSParagraphBuilder> builder = RSParagraphBuilder::Create(style, fontCollection);
    RSTextStyle txtStyle;
    ConvertTxtStyle(state.GetTextStyle(), txtStyle);
    txtStyle.fontSize = state.GetTextStyle().GetFontSize().Value();
    builder->PushStyle(txtStyle);
    builder->AppendText(StringUtils::Str8ToStr16(text));

    auto paragraph = builder->CreateTypography();
    paragraph->Layout(Size::INFINITE_SIZE);
    /**
     * @brief reference: https://html.spec.whatwg.org/multipage/canvas.html#dom-textmetrics-alphabeticbaseline
     *
     */
    auto fontMetrics = paragraph->MeasureText();
    auto glyphsBoundsTop = paragraph->GetGlyphsBoundsTop();
    auto glyphsBoundsBottom = paragraph->GetGlyphsBoundsBottom();
    auto glyphsBoundsLeft = paragraph->GetGlyphsBoundsLeft();
    auto glyphsBoundsRight = paragraph->GetGlyphsBoundsRight();
    auto textAlign = state.GetTextAlign();
    auto textBaseLine = state.GetTextStyle().GetTextBaseline();
    const double baseLineY = GetFontBaseline(fontMetrics, textBaseLine);
    const double baseLineX = GetFontAlign(textAlign, paragraph);

    textMetrics.width = paragraph->GetMaxIntrinsicWidth();
    textMetrics.height = paragraph->GetHeight();
    textMetrics.actualBoundingBoxAscent = baseLineY - glyphsBoundsTop;
    textMetrics.actualBoundingBoxDescent = glyphsBoundsBottom - baseLineY;
    textMetrics.actualBoundingBoxLeft = baseLineX - glyphsBoundsLeft;
    textMetrics.actualBoundingBoxRight = glyphsBoundsRight - baseLineX;
    textMetrics.alphabeticBaseline = baseLineY;
    textMetrics.ideographicBaseline = baseLineY - fontMetrics.fDescent;
    textMetrics.fontBoundingBoxAscent = baseLineY - fontMetrics.fTop;
    textMetrics.fontBoundingBoxDescent = fontMetrics.fBottom - baseLineY;
    textMetrics.hangingBaseline = baseLineY - (HANGING_PERCENT * fontMetrics.fAscent);
    textMetrics.emHeightAscent = baseLineY - fontMetrics.fAscent;
    textMetrics.emHeightDescent = fontMetrics.fDescent - baseLineY;
    return textMetrics;
#else
    return TextMetrics {};
#endif
}

bool CustomPaintPaintMethod::UpdateFillParagraph(const std::string& text)
{
#ifndef ACE_UNITTEST
    RSParagraphStyle style;
    TextAlign textAlign = state_.fillState.GetTextAlign();
    style.textAlign = Constants::ConvertTxtTextAlign(textAlign);
    style.textDirection = Constants::ConvertTxtTextDirection(state_.fillState.GetOffTextDirection());
    style.textAlign = GetEffectiveAlign(style.textAlign, style.textDirection);
    auto fontCollection = RosenFontCollection::GetInstance().GetFontCollection();
    CHECK_NULL_RETURN(fontCollection, false);
    std::unique_ptr<RSParagraphBuilder> builder = RSParagraphBuilder::Create(style, fontCollection);
    CHECK_NULL_RETURN(builder, false);
    RSTextStyle txtStyle;
    if (HasShadow()) {
        Rosen::TextShadow txtShadow;
        txtShadow.color = state_.shadow.GetColor().GetValue();
        txtShadow.offset.SetX(state_.shadow.GetOffset().GetX());
        txtShadow.offset.SetY(state_.shadow.GetOffset().GetY());
        txtShadow.blurRadius = state_.shadow.GetBlurRadius();
        txtStyle.shadows.emplace_back(txtShadow);
    }
    txtStyle.locale = Localization::GetInstance()->GetFontLocale();
    UpdateFontFamilies();
    txtStyle.color = Constants::ConvertSkColor(state_.fillState.GetColor());
    txtStyle.fontSize = state_.fillState.GetTextStyle().GetFontSize().Value();
    ConvertTxtStyle(state_.fillState.GetTextStyle(), txtStyle);
    RSBrush brush;
    RSSamplingOptions options;
    GetFillPaint(brush, options);
    InitPaintBlend(brush);
    txtStyle.foregroundBrush = brush;
    builder->PushStyle(txtStyle);
    builder->AppendText(StringUtils::Str8ToStr16(text));
    paragraph_ = builder->CreateTypography();
    return true;
#else
    return false;
#endif
}

bool CustomPaintPaintMethod::UpdateStrokeParagraph(const std::string& text)
{
#ifndef ACE_UNITTEST
    RSParagraphStyle style;
    TextAlign textAlign = state_.strokeState.GetTextAlign();
    style.textAlign = Constants::ConvertTxtTextAlign(textAlign);
    style.textDirection = Constants::ConvertTxtTextDirection(state_.fillState.GetOffTextDirection());
    style.textAlign = GetEffectiveAlign(style.textAlign, style.textDirection);
    auto fontCollection = RosenFontCollection::GetInstance().GetFontCollection();
    CHECK_NULL_RETURN(fontCollection, false);
    std::unique_ptr<RSParagraphBuilder> builder = RSParagraphBuilder::Create(style, fontCollection);
    CHECK_NULL_RETURN(builder, false);
    RSTextStyle txtStyle;
    txtStyle.locale = Localization::GetInstance()->GetFontLocale();
    UpdateFontFamilies();
    RSPen pen;
    RSSamplingOptions options;
    GetStrokePaint(pen, options);
    InitPaintBlend(pen);
    ConvertTxtStyle(state_.strokeState.GetTextStyle(), txtStyle);
    txtStyle.fontSize = state_.strokeState.GetTextStyle().GetFontSize().Value();
    txtStyle.foregroundPen = pen;
    builder->PushStyle(txtStyle);
    builder->AppendText(StringUtils::Str8ToStr16(text));
    paragraph_ = builder->CreateTypography();
    if (HasShadow()) {
        UpdateStrokeShadowParagraph(text, &pen, style);
    }
    return true;
#else
    return false;
#endif
}

void CustomPaintPaintMethod::UpdateStrokeShadowParagraph(
    const std::string& text, const RSPen* pen, const RSParagraphStyle& style)
{
#ifndef ACE_UNITTEST
    auto fontCollection = RosenFontCollection::GetInstance().GetFontCollection();
    CHECK_NULL_VOID(fontCollection);
    RSTextStyle shadowStyle;
    shadowStyle.locale = Localization::GetInstance()->GetFontLocale();
    UpdateFontFamilies();
    ConvertTxtStyle(state_.strokeState.GetTextStyle(), shadowStyle);
    shadowStyle.fontSize = state_.strokeState.GetTextStyle().GetFontSize().Value();
    RSPen shadowPen;
    shadowPen.SetColor(state_.shadow.GetColor().GetValue());
    shadowPen.SetAntiAlias(true);
    shadowPen.SetWidth(pen->GetWidth());
    shadowPen.SetMiterLimit(pen->GetMiterLimit());
    shadowPen.SetCapStyle(pen->GetCapStyle());
    shadowPen.SetJoinStyle(pen->GetJoinStyle());
    if (state_.globalState.HasGlobalAlpha()) {
        shadowPen.SetAlphaF(
            state_.globalState.GetAlpha() * static_cast<double>(state_.shadow.GetColor().GetValue()) / MAX_GRAYSCALE);
    }
    RSFilter filter;
    filter.SetMaskFilter(RSMaskFilter::CreateBlurMaskFilter(
        RSBlurType::NORMAL, RosenDecorationPainter::ConvertRadiusToSigma(state_.shadow.GetBlurRadius())));
    shadowPen.SetFilter(filter);
    InitPaintBlend(shadowPen);
    shadowStyle.foregroundPen = shadowPen;
    std::unique_ptr<RSParagraphBuilder> shadowBuilder = RSParagraphBuilder::Create(style, fontCollection);
    CHECK_NULL_VOID(shadowBuilder);
    shadowBuilder->PushStyle(shadowStyle);
    shadowBuilder->AppendText(StringUtils::Str8ToStr16(text));
    shadowParagraph_ = shadowBuilder->CreateTypography();
#endif
}

void CustomPaintPaintMethod::SetTransform(std::shared_ptr<Ace::Pattern> pattern, const TransformParam& transform)
{
    pattern->SetScaleX(transform.scaleX);
    pattern->SetScaleY(transform.scaleY);
    pattern->SetSkewX(transform.skewX);
    pattern->SetSkewY(transform.skewY);
    pattern->SetTranslateX(transform.translateX);
    pattern->SetTranslateY(transform.translateY);
}
} // namespace OHOS::Ace::NG
