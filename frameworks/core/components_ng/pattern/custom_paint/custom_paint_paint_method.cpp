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

#include "securec.h"

#include "drawing/engine_adapter/skia_adapter/skia_canvas.h"
#include "include/core/SkCanvas.h"
#include "include/core/SkColor.h"
#include "include/core/SkShader.h"
#include "include/core/SkBlendMode.h"
#include "include/core/SkCanvas.h"
#include "include/core/SkColor.h"
#include "include/core/SkImage.h"
#include "include/core/SkPoint.h"
#include "include/core/SkSurface.h"
#ifdef NEW_SKIA
#include "include/core/SkColorFilter.h"
#include "include/effects/SkImageFilters.h"
#else
#include "include/effects/SkBlurImageFilter.h"
#endif
#include "include/effects/SkDashPathEffect.h"
#include "include/effects/SkGradientShader.h"
#include "include/utils/SkParsePath.h"

#include "base/geometry/ng/offset_t.h"
#include "base/json/json_util.h"
#include "base/log/ace_trace.h"
#include "base/utils/linear_map.h"
#include "base/utils/string_utils.h"
#include "base/utils/utils.h"
#include "core/components/calendar/rosen_render_calendar.h"
#ifndef NEW_SKIA
#include "core/components/common/painter/flutter_decoration_painter.h"
#endif
#include "core/components/common/painter/rosen_decoration_painter.h"
#include "core/components/common/properties/decoration.h"
#include "core/components_ng/render/drawing.h"
#include "core/image/flutter_image_cache.h"
#include "core/image/image_cache.h"
#include "core/image/image_provider.h"
#include "core/pipeline/base/rosen_render_context.h"

#ifdef ENABLE_ROSEN_BACKEND
#include "pipeline/rs_recording_canvas.h"
#endif

namespace OHOS::Ace::NG {
namespace {
constexpr double HALF_CIRCLE_ANGLE = 180.0;
constexpr double FULL_CIRCLE_ANGLE = 360.0;
constexpr double CONIC_START_ANGLE = 0.0;
constexpr double CONIC_END_ANGLE = 359.9;
constexpr double MAX_GRAYSCALE = 255.0;
constexpr int32_t IMAGE_CACHE_COUNT = 50;

#ifndef USE_ROSEN_DRAWING
const LinearEnumMapNode<CompositeOperation, SkBlendMode> SK_BLEND_MODE_TABLE[] = {
    { CompositeOperation::SOURCE_OVER, SkBlendMode::kSrcOver },
    { CompositeOperation::SOURCE_ATOP, SkBlendMode::kSrcATop },
    { CompositeOperation::SOURCE_IN, SkBlendMode::kSrcIn },
    { CompositeOperation::SOURCE_OUT, SkBlendMode::kSrcOut },
    { CompositeOperation::DESTINATION_OVER, SkBlendMode::kDstOver },
    { CompositeOperation::DESTINATION_ATOP, SkBlendMode::kDstATop },
    { CompositeOperation::DESTINATION_IN, SkBlendMode::kDstIn },
    { CompositeOperation::DESTINATION_OUT, SkBlendMode::kDstOut },
    { CompositeOperation::LIGHTER, SkBlendMode::kLighten },
    { CompositeOperation::COPY, SkBlendMode::kSrc },
    { CompositeOperation::XOR, SkBlendMode::kXor },
};
constexpr size_t BLEND_MODE_SIZE = ArraySize(SK_BLEND_MODE_TABLE);
#else
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
#endif

#ifndef USE_ROSEN_DRAWING
template<typename T, typename N>
N ConvertEnumToSkEnum(T key, const LinearEnumMapNode<T, N>* map, size_t length, N defaultValue)
#else
template<typename T, typename N>
N ConvertEnumToDrawingEnum(T key, const LinearEnumMapNode<T, N>* map, size_t length, N defaultValue)
#endif
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

void CustomPaintPaintMethod::UpdateRecordingCanvas(float width, float height)
{
#ifndef USE_ROSEN_DRAWING
    rsRecordingCanvas_ = std::make_shared<OHOS::Rosen::RSRecordingCanvas>(width, height);
    skCanvas_ = std::static_pointer_cast<SkCanvas>(rsRecordingCanvas_);
    contentModifier_->UpdateCanvas(rsRecordingCanvas_);
#else
    rsRecordingCanvas_ = std::make_shared<RSRecordingCanvas>(width, height);
    rsCanvas_ = std::static_pointer_cast<RSCanvas>(rsRecordingCanvas_);
    contentModifier_->UpdateCanvas(rsRecordingCanvas_);
#endif
}

bool CustomPaintPaintMethod::HasShadow() const
{
    return !(NearZero(shadow_.GetOffset().GetX()) && NearZero(shadow_.GetOffset().GetY()) &&
             NearZero(shadow_.GetBlurRadius()));
}

#ifndef USE_ROSEN_DRAWING
void CustomPaintPaintMethod::UpdateLineDash(SkPaint& paint)
{
    if (!strokeState_.GetLineDash().lineDash.empty()) {
        auto lineDashState = strokeState_.GetLineDash().lineDash;
        SkScalar intervals[lineDashState.size()];
        for (size_t i = 0; i < lineDashState.size(); ++i) {
            intervals[i] = SkDoubleToScalar(lineDashState[i]);
        }
        SkScalar phase = SkDoubleToScalar(strokeState_.GetLineDash().dashOffset);
        paint.setPathEffect(SkDashPathEffect::Make(intervals, lineDashState.size(), phase));
    }
}
#else
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
#endif

#ifndef USE_ROSEN_DRAWING
sk_sp<SkShader> CustomPaintPaintMethod::MakeConicGradient(SkPaint& paint, const Ace::Gradient& gradient)
{
    sk_sp<SkShader> skShader = nullptr;
    if (gradient.GetType() == Ace::GradientType::CONIC) {
        if (!gradient.GetConicGradient().centerX.has_value() ||
            !gradient.GetConicGradient().centerY.has_value() ||
            !gradient.GetConicGradient().startAngle.has_value()) {
            return skShader;
        }
        SkMatrix matrix = SkMatrix::I();
        SkScalar centerX = SkDoubleToScalar(gradient.GetConicGradient().centerX->Value());
        SkScalar centerY = SkDoubleToScalar(gradient.GetConicGradient().centerY->Value());
        auto gradientColors = gradient.GetColors();
        std::stable_sort(gradientColors.begin(), gradientColors.end(),
            [](auto& colorA, auto& colorB) { return colorA.GetDimension() < colorB.GetDimension(); });
        uint32_t colorsSize = gradientColors.size();
        SkColor colors[gradientColors.size()];
        float pos[gradientColors.size()];
        double angle = gradient.GetConicGradient().startAngle->Value() / M_PI * 180.0;
        SkScalar startAngle = SkDoubleToScalar(angle);
        matrix.preRotate(startAngle, centerX, centerY);
        for (uint32_t i = 0; i < colorsSize; ++i) {
            const auto& gradientColor = gradientColors[i];
            colors[i] = gradientColor.GetColor().GetValue();
            pos[i] = gradientColor.GetDimension().Value();
        }
#ifdef USE_SYSTEM_SKIA
    auto mode = SkShader::kClamp_TileMode;
#else
    auto mode = SkTileMode::kClamp;
#endif
        skShader = SkGradientShader::MakeSweep(centerX, centerY,
                                               colors, pos, colorsSize, mode,
                                               SkDoubleToScalar(CONIC_START_ANGLE),
                                               SkDoubleToScalar(CONIC_END_ANGLE),
                                               0, &matrix);
    }
    return skShader;
}
#else
std::shared_ptr<RSShaderEffect> CustomPaintPaintMethod::MakeConicGradient(
    RSBrush* brush, const Ace::Gradient& gradient)
{
    std::shared_ptr<RSShaderEffect> shaderEffect = nullptr;
    if (gradient.GetType() == Ace::GradientType::CONIC) {
        if (!gradient.GetConicGradient().centerX.has_value() ||
            !gradient.GetConicGradient().centerY.has_value() ||
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
        matrix.Rotate(startAngle, centerX, centerY);
        for (uint32_t i = 0; i < colorsSize; ++i) {
            const auto& gradientColor = gradientColors[i];
            colors.at(i) = gradientColor.GetColor().GetValue();
            pos.at(i) = gradientColor.GetDimension().Value();
        }
        auto mode = RSTileMode::CLAMP;
        shaderEffect = RSShaderEffect::CreateSweepGradient(RSPoint(centerX, centerY),
            colors, pos, mode, static_cast<RSScalar>(CONIC_START_ANGLE), static_cast<RSScalar>(CONIC_END_ANGLE));
    }
    return shaderEffect;
}
#endif

#ifndef USE_ROSEN_DRAWING
void CustomPaintPaintMethod::UpdatePaintShader(const OffsetF& offset, SkPaint& paint, const Ace::Gradient& gradient)
{
    SkPoint beginPoint = SkPoint::Make(SkDoubleToScalar(gradient.GetBeginOffset().GetX() + offset.GetX()),
        SkDoubleToScalar(gradient.GetBeginOffset().GetY() + offset.GetY()));
    SkPoint endPoint = SkPoint::Make(SkDoubleToScalar(gradient.GetEndOffset().GetX() + offset.GetX()),
        SkDoubleToScalar(gradient.GetEndOffset().GetY() + offset.GetY()));
    SkPoint pts[2] = { beginPoint, endPoint };
    auto gradientColors = gradient.GetColors();
    std::stable_sort(gradientColors.begin(), gradientColors.end(),
        [](auto& colorA, auto& colorB) { return colorA.GetDimension() < colorB.GetDimension(); });
    uint32_t colorsSize = gradientColors.size();
    SkColor colors[gradientColors.size()];
    float pos[gradientColors.size()];
    for (uint32_t i = 0; i < colorsSize; ++i) {
        const auto& gradientColor = gradientColors[i];
        colors[i] = gradientColor.GetColor().GetValue();
        pos[i] = gradientColor.GetDimension().Value();
    }
#ifdef USE_SYSTEM_SKIA
    auto mode = SkShader::kClamp_TileMode;
#else
    auto mode = SkTileMode::kClamp;
#endif
    sk_sp<SkShader> skShader = nullptr;
    if (gradient.GetType() == Ace::GradientType::LINEAR) {
        skShader = SkGradientShader::MakeLinear(pts, colors, pos, gradientColors.size(), mode);
    } else if (gradient.GetType() == Ace::GradientType::CONIC) {
        skShader = MakeConicGradient(paint, gradient);
    } else {
        if (gradient.GetInnerRadius() <= 0.0 && beginPoint == endPoint) {
            skShader = SkGradientShader::MakeRadial(
                endPoint, gradient.GetOuterRadius(), colors, pos, gradientColors.size(), mode);
        } else {
            skShader = SkGradientShader::MakeTwoPointConical(beginPoint, gradient.GetInnerRadius(), endPoint,
                gradient.GetOuterRadius(), colors, pos, gradientColors.size(), mode);
        }
    }
    paint.setShader(skShader);
}
#else
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
            shaderEffect = RSShaderEffect::CreateRadialGradient(
                endPoint, gradient.GetOuterRadius(), colors, pos, mode);
        } else {
            shaderEffect = RSShaderEffect::CreateTwoPointConical(
                beginPoint, gradient.GetInnerRadius(), endPoint, gradient.GetOuterRadius(), colors, pos, mode);
        }
    }
    if (pen != nullptr) {
        pen->SetShaderEffect(shaderEffect);
    }
    if (brush != nullptr) {
        brush->SetShaderEffect(shaderEffect);
    }
}
#endif

#ifndef USE_ROSEN_DRAWING
SkMatrix CustomPaintPaintMethod::GetMatrixFromPattern(const Ace::Pattern& pattern)
{
    SkMatrix matrix;
    double viewScale = 1.0;
    auto context = context_.Upgrade();
    if (context) {
        viewScale = context->GetViewScale();
    }
    matrix.setAll(pattern.GetScaleX() * viewScale, pattern.GetSkewX() * viewScale, pattern.GetTranslateX() * viewScale,
        pattern.GetSkewY() * viewScale, pattern.GetScaleY() * viewScale, pattern.GetTranslateY() * viewScale, 0.0f,
        0.0f, 1.0f);
    return matrix;
}
#else
RSMatrix CustomPaintPaintMethod::GetMatrixFromPattern(const Ace::Pattern& pattern)
{
    RSMatrix matrix;
    double viewScale = 1.0;
    auto context = context_.Upgrade();
    if (context) {
        viewScale = context->GetViewScale();
    }
    matrix.SetMatrix(
        pattern.GetScaleX() * viewScale, pattern.GetSkewX() * viewScale, pattern.GetTranslateX() * viewScale,
        pattern.GetSkewY() * viewScale, pattern.GetScaleY() * viewScale, pattern.GetTranslateY() * viewScale,
        0.0f, 0.0f, 1.0f);
    return matrix;
}
#endif

#ifndef USE_ROSEN_DRAWING
sk_sp<SkImage> CustomPaintPaintMethod::GetImage(const std::string& src)
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

#ifndef USE_ROSEN_DRAWING
void CustomPaintPaintMethod::UpdatePaintShader(const Ace::Pattern& pattern, SkPaint& paint)
{
    auto image = GetImage(pattern.GetImgSrc());
    CHECK_NULL_VOID(image);
    SkMatrix* matrix = nullptr;
    SkMatrix tempMatrix;
    if (pattern.IsTransformable()) {
        tempMatrix = GetMatrixFromPattern(pattern);
        matrix = &tempMatrix;
    }
    static const LinearMapNode<void (*)(sk_sp<SkImage>, SkPaint&, SkMatrix*)> staticPattern[] = {
        { "clamp",
            [](sk_sp<SkImage> image, SkPaint& paint, SkMatrix* matrix) {
#ifdef USE_SYSTEM_SKIA
                paint.setShader(image->makeShader(SkShader::kClamp_TileMode, SkShader::kClamp_TileMode, matrix));
#else
#ifdef NEW_SKIA
                paint.setShader(
                    image->makeShader(SkTileMode::kClamp, SkTileMode::kClamp, SkSamplingOptions(), matrix));
#else
                paint.setShader(image->makeShader(SkTileMode::kClamp, SkTileMode::kClamp, matrix));
#endif
#endif
            } },
        { "mirror",
            [](sk_sp<SkImage> image, SkPaint& paint, SkMatrix* matrix) {
#ifdef USE_SYSTEM_SKIA
                paint.setShader(image->makeShader(SkShader::kClamp_TileMode, SkShader::kClamp_TileMode, matrix));
#else
#ifdef NEW_SKIA
                paint.setShader(
                    image->makeShader(SkTileMode::kMirror, SkTileMode::kMirror, SkSamplingOptions(), matrix));
#else
                paint.setShader(image->makeShader(SkTileMode::kMirror, SkTileMode::kMirror, matrix));
#endif
#endif
            } },
        { "no-repeat",
            [](sk_sp<SkImage> image, SkPaint& paint, SkMatrix* matrix) {
#ifdef USE_SYSTEM_SKIA
                paint.setShader(image->makeShader(SkShader::kDecal_TileMode, SkShader::kDecal_TileMode, matrix));
#else
#ifdef NEW_SKIA
                paint.setShader(
                    image->makeShader(SkTileMode::kDecal, SkTileMode::kDecal, SkSamplingOptions(), matrix));
#else
                paint.setShader(image->makeShader(SkTileMode::kDecal, SkTileMode::kDecal, matrix));
#endif
#endif
            } },
        { "repeat",
            [](sk_sp<SkImage> image, SkPaint& paint, SkMatrix* matrix) {
#ifdef USE_SYSTEM_SKIA
                paint.setShader(image->makeShader(SkShader::kRepeat_TileMode, SkShader::kRepeat_TileMode, matrix));
#else
#ifdef NEW_SKIA
                paint.setShader(
                    image->makeShader(SkTileMode::kRepeat, SkTileMode::kRepeat, SkSamplingOptions(), matrix));
#else
                paint.setShader(image->makeShader(SkTileMode::kRepeat, SkTileMode::kRepeat, matrix));
#endif
#endif
            } },
        { "repeat-x",
            [](sk_sp<SkImage> image, SkPaint& paint, SkMatrix* matrix) {
#ifdef USE_SYSTEM_SKIA
                paint.setShader(image->makeShader(SkShader::kRepeat_TileMode, SkShader::kDecal_TileMode, matrix));
#else
#ifdef NEW_SKIA
                paint.setShader(
                    image->makeShader(SkTileMode::kRepeat, SkTileMode::kDecal, SkSamplingOptions(), matrix));
#else
                paint.setShader(image->makeShader(SkTileMode::kRepeat, SkTileMode::kDecal, matrix));
#endif
#endif
            } },
        { "repeat-y",
            [](sk_sp<SkImage> image, SkPaint& paint, SkMatrix* matrix) {
#ifdef USE_SYSTEM_SKIA
                paint.setShader(image->makeShader(SkShader::kDecal_TileMode, SkShader::kRepeat_TileMode, matrix));
#else
#ifdef NEW_SKIA
                paint.setShader(
                    image->makeShader(SkTileMode::kDecal, SkTileMode::kRepeat, SkSamplingOptions(), matrix));
#else
                paint.setShader(image->makeShader(SkTileMode::kDecal, SkTileMode::kRepeat, matrix));
#endif
#endif
            } },
    };
    auto operatorIter = BinarySearchFindIndex(staticPattern, ArraySize(staticPattern),
        pattern.GetRepetition().c_str());
    if (operatorIter != -1) {
        staticPattern[operatorIter].value(image, paint, matrix);
    }
}
#else
void CustomPaintPaintMethod::UpdatePaintShader(const Ace::Pattern& pattern, RSPen* pen, RSBrush* brush)
{
    auto image = GetImage(pattern.GetImgSrc());
    CHECK_NULL_VOID(image);
    RSMatrix matrix;
    if (pattern.IsTransformable()) {
        matrix = GetMatrixFromPattern(pattern);
    }
    static const LinearMapNode<void (*)(std::shared_ptr<RSImage>&, std::shared_ptr<RSShaderEffect>&, RSMatrix&)>
        staticPattern[] = {
        { "clamp",
            [](std::shared_ptr<RSImage>& image, std::shared_ptr<RSShaderEffect>& shaderEffect, RSMatrix& matrix) {
                shaderEffect = RSShaderEffect::CreateImageShader(*image,
                    RSTileMode::CLAMP, RSTileMode::CLAMP, RSSamplingOptions(), matrix);
            } },
        { "mirror",
            [](std::shared_ptr<RSImage>& image, std::shared_ptr<RSShaderEffect>& shaderEffect, RSMatrix& matrix) {
                shaderEffect = RSShaderEffect::CreateImageShader(*image,
                    RSTileMode::MIRROR, RSTileMode::MIRROR, RSSamplingOptions(), matrix);
            } },
        { "no-repeat",
            [](std::shared_ptr<RSImage>& image, std::shared_ptr<RSShaderEffect>& shaderEffect, RSMatrix& matrix) {
                    shaderEffect = RSShaderEffect::CreateImageShader(*image,
                        RSTileMode::DECAL, RSTileMode::DECAL, RSSamplingOptions(), matrix);
            } },
        { "repeat",
            [](std::shared_ptr<RSImage>& image, std::shared_ptr<RSShaderEffect>& shaderEffect, RSMatrix& matrix) {
                    shaderEffect = RSShaderEffect::CreateImageShader(*image,
                        RSTileMode::REPEAT, RSTileMode::REPEAT, RSSamplingOptions(), matrix);
            } },
        { "repeat-x",
            [](std::shared_ptr<RSImage>& image, std::shared_ptr<RSShaderEffect>& shaderEffect, RSMatrix& matrix) {
                    shaderEffect = RSShaderEffect::CreateImageShader(*image,
                        RSTileMode::REPEAT, RSTileMode::DECAL, RSSamplingOptions(), matrix);
            } },
        { "repeat-y",
            [](std::shared_ptr<RSImage>& image, std::shared_ptr<RSShaderEffect>& shaderEffect, RSMatrix& matrix) {
                    shaderEffect = RSShaderEffect::CreateImageShader(*image,
                        RSTileMode::DECAL, RSTileMode::REPEAT, RSSamplingOptions(), matrix);
            } },
        };
    auto operatorIter = BinarySearchFindIndex(staticPattern, ArraySize(staticPattern),
        pattern.GetRepetition().c_str());
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
#endif

#ifndef USE_ROSEN_DRAWING
void CustomPaintPaintMethod::InitPaintBlend(SkPaint& paint)
{
    paint.setBlendMode(
        ConvertEnumToSkEnum(globalState_.GetType(), SK_BLEND_MODE_TABLE, BLEND_MODE_SIZE, SkBlendMode::kSrcOver));
}
#else
void CustomPaintPaintMethod::InitPaintBlend(RSBrush& brush)
{
    brush.SetBlendMode(ConvertEnumToDrawingEnum(
        globalState_.GetType(), DRAWING_BLEND_MODE_TABLE, BLEND_MODE_SIZE, RSBlendMode::SRC_OVER));
}
#endif

#ifndef USE_ROSEN_DRAWING
#ifndef NEW_SKIA
void CustomPaintPaintMethod::GetStrokePaint(SkPaint& paint)
{
    static const LinearEnumMapNode<LineJoinStyle, SkPaint::Join> skLineJoinTable[] = {
        { LineJoinStyle::MITER, SkPaint::Join::kMiter_Join },
        { LineJoinStyle::ROUND, SkPaint::Join::kRound_Join },
        { LineJoinStyle::BEVEL, SkPaint::Join::kBevel_Join },
    };
    static const LinearEnumMapNode<LineCapStyle, SkPaint::Cap> skLineCapTable[] = {
        { LineCapStyle::BUTT, SkPaint::Cap::kButt_Cap },
        { LineCapStyle::ROUND, SkPaint::Cap::kRound_Cap },
        { LineCapStyle::SQUARE, SkPaint::Cap::kSquare_Cap },
    };
    InitImagePaint(paint);
    paint.setColor(strokeState_.GetColor().GetValue());
    paint.setStyle(SkPaint::Style::kStroke_Style);
    paint.setStrokeJoin(ConvertEnumToSkEnum(
        strokeState_.GetLineJoin(), skLineJoinTable, ArraySize(skLineJoinTable), SkPaint::Join::kMiter_Join));
    paint.setStrokeCap(ConvertEnumToSkEnum(
        strokeState_.GetLineCap(), skLineCapTable, ArraySize(skLineCapTable), SkPaint::Cap::kButt_Cap));
    paint.setStrokeWidth(static_cast<SkScalar>(strokeState_.GetLineWidth()));
    paint.setStrokeMiter(static_cast<SkScalar>(strokeState_.GetMiterLimit()));

    // set line Dash
    UpdateLineDash(paint);

    // set global alpha
    if (globalState_.HasGlobalAlpha()) {
        paint.setAlphaf(globalState_.GetAlpha() *
                        static_cast<double>(strokeState_.GetColor().GetAlpha()) /
                        MAX_GRAYSCALE);
    }
}

void CustomPaintPaintMethod::InitImagePaint(SkPaint& paint)
{
    if (smoothingEnabled_) {
        if (smoothingQuality_ == "low") {
            paint.setFilterQuality(SkFilterQuality::kLow_SkFilterQuality);
        } else if (smoothingQuality_ == "medium") {
            paint.setFilterQuality(SkFilterQuality::kMedium_SkFilterQuality);
        } else if (smoothingQuality_ == "high") {
            paint.setFilterQuality(SkFilterQuality::kHigh_SkFilterQuality);
        } else {
            LOGE("Unsupported Quality type:%{public}s", smoothingQuality_.c_str());
        }
    } else {
        paint.setFilterQuality(SkFilterQuality::kNone_SkFilterQuality);
    }
    ClearPaintImage(paint);
    SetPaintImage(paint);
}
#else
void CustomPaintPaintMethod::GetStrokePaint(SkPaint& paint, SkSamplingOptions& options)
{
    static const LinearEnumMapNode<LineJoinStyle, SkPaint::Join> skLineJoinTable[] = {
        { LineJoinStyle::MITER, SkPaint::Join::kMiter_Join },
        { LineJoinStyle::ROUND, SkPaint::Join::kRound_Join },
        { LineJoinStyle::BEVEL, SkPaint::Join::kBevel_Join },
    };
    static const LinearEnumMapNode<LineCapStyle, SkPaint::Cap> skLineCapTable[] = {
        { LineCapStyle::BUTT, SkPaint::Cap::kButt_Cap },
        { LineCapStyle::ROUND, SkPaint::Cap::kRound_Cap },
        { LineCapStyle::SQUARE, SkPaint::Cap::kSquare_Cap },
    };
    InitImagePaint(paint, options);
    if (strokeState_.GetPaintStyle() == PaintStyle::Color) {
        paint.setColor(strokeState_.GetColor().GetValue());
    }
    paint.setStyle(SkPaint::Style::kStroke_Style);
    paint.setStrokeJoin(ConvertEnumToSkEnum(
        strokeState_.GetLineJoin(), skLineJoinTable, ArraySize(skLineJoinTable), SkPaint::Join::kMiter_Join));
    paint.setStrokeCap(ConvertEnumToSkEnum(
        strokeState_.GetLineCap(), skLineCapTable, ArraySize(skLineCapTable), SkPaint::Cap::kButt_Cap));
    paint.setStrokeWidth(static_cast<SkScalar>(strokeState_.GetLineWidth()));
    paint.setStrokeMiter(static_cast<SkScalar>(strokeState_.GetMiterLimit()));

    // set line Dash
    UpdateLineDash(paint);

    // set global alpha
    if (globalState_.HasGlobalAlpha()) {
        if (strokeState_.GetPaintStyle() == PaintStyle::Color) {
            paint.setAlphaf(globalState_.GetAlpha() *
                            static_cast<double>(strokeState_.GetColor().GetAlpha()) /
                            MAX_GRAYSCALE);
        } else {
            paint.setAlphaf(globalState_.GetAlpha());
        }
    }
}

void CustomPaintPaintMethod::InitImagePaint(SkPaint& paint, SkSamplingOptions& options)
{
    if (smoothingEnabled_) {
        if (smoothingQuality_ == "low") {
            options = SkSamplingOptions(SkFilterMode::kLinear, SkMipmapMode::kNone);
        } else if (smoothingQuality_ == "medium") {
            options = SkSamplingOptions(SkFilterMode::kLinear, SkMipmapMode::kLinear);
        } else if (smoothingQuality_ == "high") {
            options = SkSamplingOptions(SkCubicResampler::Mitchell());
        } else {
            LOGE("Unsupported Quality type:%{public}s", smoothingQuality_.c_str());
        }
    } else {
        options = SkSamplingOptions(SkFilterMode::kNearest, SkMipmapMode::kNone);
    }
    ClearPaintImage(paint);
    SetPaintImage(paint);
}
#endif
#else
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
            pen.SetAlphaF(globalState_.GetAlpha() *
                            static_cast<double>(strokeState_.GetColor().GetAlpha()) /
                            MAX_GRAYSCALE);
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
        } else {
            LOGE("Unsupported Quality type:%{public}s", smoothingQuality_.c_str());
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
#endif

void CustomPaintPaintMethod::InitImageCallbacks()
{
    imageObjSuccessCallback_ = [weak = AceType::WeakClaim(this)](
                                   ImageSourceInfo info, const RefPtr<Ace::ImageObject>& imageObj) {
        auto paintMethod = weak.Upgrade();
        if (paintMethod->loadingSource_ == info) {
            paintMethod->ImageObjReady(imageObj);
            return;
        } else {
            LOGE("image sourceInfo_ check error, : %{public}s vs %{public}s",
                paintMethod->loadingSource_.ToString().c_str(), info.ToString().c_str());
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

void CustomPaintPaintMethod::DrawSvgImage(PaintWrapper* paintWrapper, const Ace::CanvasImage& canvasImage)
{
    // Make the ImageSourceInfo
    canvasImage_ = canvasImage;
    loadingSource_ = ImageSourceInfo(canvasImage.src);
    // get the ImageObject
    if (currentSource_ != loadingSource_) {
        ImageProvider::FetchImageObject(loadingSource_, imageObjSuccessCallback_, uploadSuccessCallback_,
            failedCallback_, context_, true, true, true, onPostBackgroundTask_);
    }

    CHECK_NULL_VOID(skiaDom_);
    // draw the svg
#ifndef USE_ROSEN_DRAWING
    SkRect srcRect;
    SkRect dstRect;
    switch (canvasImage.flag) {
        case 0:
            srcRect = SkRect::MakeXYWH(0, 0, skiaDom_->containerSize().width(), skiaDom_->containerSize().height());
            dstRect = SkRect::MakeXYWH(canvasImage.dx, canvasImage.dy, skiaDom_->containerSize().width(),
                skiaDom_->containerSize().height());
            break;
        case 1: {
            srcRect = SkRect::MakeXYWH(0, 0, skiaDom_->containerSize().width(), skiaDom_->containerSize().height());
            dstRect = SkRect::MakeXYWH(canvasImage.dx, canvasImage.dy, canvasImage.dWidth, canvasImage.dHeight);
            break;
        }
        case 2: {
            srcRect = SkRect::MakeXYWH(canvasImage.sx, canvasImage.sy, canvasImage.sWidth, canvasImage.sHeight);
            dstRect = SkRect::MakeXYWH(canvasImage.dx, canvasImage.dy, canvasImage.dWidth, canvasImage.dHeight);
            break;
        }
        default:
            break;
    }
    float scaleX = dstRect.width() / srcRect.width();
    float scaleY = dstRect.height() / srcRect.height();
    OffsetF offset = GetContentOffset(paintWrapper);
    OffsetF startPoint = offset + OffsetF(dstRect.left(), dstRect.top()) -
        OffsetF(srcRect.left() * scaleX, srcRect.top() * scaleY);

    SkCanvas* skCanvas = GetRawPtrOfSkCanvas();
    skCanvas->save();
    skCanvas->clipRect(dstRect);
    skCanvas->translate(startPoint.GetX(), startPoint.GetY());
    skCanvas->scale(scaleX, scaleY);
    skiaDom_->render(skCanvas);
    skCanvas->restore();
#else
    RSRect srcRect;
    RSRect dstRect;
    switch (canvasImage.flag) {
        case 0:
            srcRect = RSRect(0, 0, skiaDom_->containerSize().width(), skiaDom_->containerSize().height());
            dstRect = RSRect(canvasImage.dx, canvasImage.dy, skiaDom_->containerSize().width() + canvasImage.dx,
                skiaDom_->containerSize().height() + canvasImage.dy);
            break;
        case 1: {
            srcRect = RSRect(0, 0, skiaDom_->containerSize().width(), skiaDom_->containerSize().height());
            dstRect = RSRect(canvasImage.dx, canvasImage.dy,
                canvasImage.dWidth + canvasImage.dx, canvasImage.dHeight + canvasImage.dy);
            break;
        }
        case 2: {
            srcRect = RSRect(canvasImage.sx, canvasImage.sy,
                canvasImage.sWidth + canvasImage.sx, canvasImage.sHeight + canvasImage.sy);
            dstRect = RSRect(canvasImage.dx, canvasImage.dy,
                canvasImage.dWidth + canvasImage.dx, canvasImage.dHeight + canvasImage.dy);
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
    rsCanvas->Save();
    rsCanvas->ClipRect(dstRect, RSClipOp::INTERSECT);
    rsCanvas->Translate(startPoint.GetX(), startPoint.GetY());
    rsCanvas->Scale(scaleX, scaleY);
    rsCanvas->DrawSVGDOM(skiaDom_);
    rsCanvas->Restore();
#endif
}

void CustomPaintPaintMethod::PutImageData(PaintWrapper* paintWrapper, const Ace::ImageData& imageData)
{
    if (imageData.data.empty()) {
        LOGE("PutImageData failed, image data is empty.");
        return;
    }
    uint32_t* data = new (std::nothrow) uint32_t[imageData.data.size()];
    CHECK_NULL_VOID(data);

    for (uint32_t i = 0; i < imageData.data.size(); ++i) {
        data[i] = imageData.data[i].GetValue();
    }
#ifndef USE_ROSEN_DRAWING
    SkBitmap skBitmap;
    auto imageInfo = SkImageInfo::Make(imageData.dirtyWidth, imageData.dirtyHeight, SkColorType::kBGRA_8888_SkColorType,
        SkAlphaType::kOpaque_SkAlphaType);
    skBitmap.allocPixels(imageInfo);
    skBitmap.setPixels(data);
    auto contentOffset = GetContentOffset(paintWrapper);
#ifndef NEW_SKIA
    skCanvas_->drawBitmap(skBitmap, imageData.x + contentOffset.GetX(), imageData.y + contentOffset.GetY());
#else
    SkPaint paint;
    paint.setBlendMode(SkBlendMode::kSrc);
    skCanvas_->drawImage(skBitmap.asImage(), imageData.x + contentOffset.GetX(), imageData.y + contentOffset.GetY(),
        SkSamplingOptions(), &paint);
#endif
#else
    RSBitmap bitmap;
    RSBitmapFormat format { RSColorType::COLORTYPE_BGRA_8888, RSAlphaType::ALPHATYPE_OPAQUE };
    bitmap.Build(imageData.dirtyWidth, imageData.dirtyHeight, format);
    bitmap.SetPixels(data);
    auto contentOffset = GetContentOffset(paintWrapper);
    rsCanvas_->DrawBitmap(bitmap, imageData.x + contentOffset.GetX(), imageData.y + contentOffset.GetY());
#endif
    delete[] data;
}

void CustomPaintPaintMethod::FillRect(PaintWrapper* paintWrapper, const Rect& rect)
{
    OffsetF offset = GetContentOffset(paintWrapper);
#ifndef USE_ROSEN_DRAWING
    SkPaint paint;
#ifndef NEW_SKIA
    InitImagePaint(paint);
#else
    SkSamplingOptions options;
    InitImagePaint(paint, options);
#endif
    paint.setAntiAlias(antiAlias_);
    if (fillState_.GetPaintStyle() == OHOS::Ace::PaintStyle::Color) {
        paint.setColor(fillState_.GetColor().GetValue());
    }
    paint.setStyle(SkPaint::Style::kFill_Style);
    SkRect skRect = SkRect::MakeLTRB(rect.Left() + offset.GetX(), rect.Top() + offset.GetY(),
        rect.Right() + offset.GetX(), offset.GetY() + rect.Bottom());
    if (fillState_.GetGradient().IsValid() && fillState_.GetPaintStyle() == PaintStyle::Gradient) {
        UpdatePaintShader(offset, paint, fillState_.GetGradient());
    }
    if (fillState_.GetPatternValue().IsValid() && fillState_.GetPaintStyle() == PaintStyle::ImagePattern) {
        UpdatePaintShader(fillState_.GetPatternValue(), paint);
    }
    if (globalState_.HasGlobalAlpha()) {
        if (fillState_.GetPaintStyle() == OHOS::Ace::PaintStyle::Color) {
            paint.setAlphaf(globalState_.GetAlpha() *
                            static_cast<double>(fillState_.GetColor().GetAlpha()) /
                            MAX_GRAYSCALE);
        } else {
            paint.setAlphaf(globalState_.GetAlpha()); // update the global alpha after setting the color
        }
    }
    if (HasShadow()) {
        SkPath path;
        path.addRect(skRect);
        PaintShadow(path, shadow_, skCanvas_.get(), &paint);
    }
    if (globalState_.GetType() == CompositeOperation::SOURCE_OVER) {
        skCanvas_->drawRect(skRect, paint);
    } else {
        SkPaint compositeOperationpPaint;
        InitPaintBlend(compositeOperationpPaint);
        skCanvas_->saveLayer(
            SkRect::MakeXYWH(0, 0, lastLayoutSize_.Width(), lastLayoutSize_.Height()), &compositeOperationpPaint);
        skCanvas_->drawRect(skRect, paint);
        skCanvas_->restore();
    }
#else
    RSBrush brush;
    RSSamplingOptions options;
    InitImagePaint(nullptr, &brush, options);
    brush.SetAntiAlias(antiAlias_);
    if (fillState_.GetPaintStyle() == OHOS::Ace::PaintStyle::Color) {
        brush.SetColor(fillState_.GetColor().GetValue());
    }
    RSRect rsRect(rect.Left() + offset.GetX(), rect.Top() + offset.GetY(),
        rect.Right() + offset.GetX(), offset.GetY() + rect.Bottom());
    if (HasShadow()) {
        RSRecordingPath path;
        path.AddRect(rsRect);
        PaintShadow(path, shadow_, rsCanvas_.get());
    }
    if (fillState_.GetGradient().IsValid() && fillState_.GetPaintStyle() == PaintStyle::Gradient) {
        UpdatePaintShader(offset, nullptr, &brush, fillState_.GetGradient());
    }
    if (fillState_.GetPatternValue().IsValid() && fillState_.GetPaintStyle() == PaintStyle::ImagePattern) {
        UpdatePaintShader(fillState_.GetPatternValue(), nullptr, &brush);
    }
    if (globalState_.HasGlobalAlpha()) {
        if (fillState_.GetPaintStyle() == OHOS::Ace::PaintStyle::Color) {
            brush.SetAlphaF(globalState_.GetAlpha() *
                            static_cast<double>(fillState_.GetColor().GetAlpha()) /
                            MAX_GRAYSCALE);
        } else {
            brush.SetAlphaF(globalState_.GetAlpha()); // update the global alpha after setting the color
        }
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
#endif
}

void CustomPaintPaintMethod::StrokeRect(PaintWrapper* paintWrapper, const Rect& rect)
{
    OffsetF offset = GetContentOffset(paintWrapper);
#ifndef USE_ROSEN_DRAWING
    SkPaint paint;
#ifndef NEW_SKIA
    GetStrokePaint(paint);
#else
    SkSamplingOptions options;
    GetStrokePaint(paint, options);
#endif
    paint.setAntiAlias(antiAlias_);
    SkRect skRect = SkRect::MakeLTRB(rect.Left() + offset.GetX(), rect.Top() + offset.GetY(),
        rect.Right() + offset.GetX(), offset.GetY() + rect.Bottom());
    if (strokeState_.GetGradient().IsValid() && strokeState_.GetPaintStyle() == PaintStyle::Gradient) {
        UpdatePaintShader(offset, paint, strokeState_.GetGradient());
    }
    if (strokeState_.GetPatternValue().IsValid() && strokeState_.GetPaintStyle() == PaintStyle::ImagePattern) {
        UpdatePaintShader(strokeState_.GetPatternValue(), paint);
    }
    if (HasShadow()) {
        SkPath path;
        path.addRect(skRect);
        PaintShadow(path, shadow_, skCanvas_.get(), &paint);
    }
    if (globalState_.GetType() == CompositeOperation::SOURCE_OVER) {
        skCanvas_->drawRect(skRect, paint);
    } else {
        SkPaint compositeOperationpPaint;
        InitPaintBlend(compositeOperationpPaint);
        skCanvas_->saveLayer(
            SkRect::MakeXYWH(0, 0, lastLayoutSize_.Width(), lastLayoutSize_.Height()), &compositeOperationpPaint);
        skCanvas_->drawRect(skRect, paint);
        skCanvas_->restore();
    }
#else
    RSPen pen;
    RSSamplingOptions options;
    GetStrokePaint(pen, options);
    pen.SetAntiAlias(antiAlias_);
    RSRect rsRect(rect.Left() + offset.GetX(), rect.Top() + offset.GetY(),
        rect.Right() + offset.GetX(), offset.GetY() + rect.Bottom());
    if (HasShadow()) {
        RSRecordingPath path;
        path.AddRect(rsRect);
        PaintShadow(path, shadow_, rsCanvas_.get());
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
#endif
}

void CustomPaintPaintMethod::ClearRect(PaintWrapper* paintWrapper, const Rect& rect)
{
    OffsetF offset = GetContentOffset(paintWrapper);
#ifndef USE_ROSEN_DRAWING
    SkPaint paint;
#ifndef NEW_SKIA
    InitImagePaint(paint);
#else
    SkSamplingOptions options;
    InitImagePaint(paint, options);
#endif
    paint.setAntiAlias(antiAlias_);
    paint.setBlendMode(SkBlendMode::kClear);
    auto skRect = SkRect::MakeLTRB(rect.Left() + offset.GetX(), rect.Top() + offset.GetY(),
        rect.Right() + offset.GetX(), rect.Bottom() + offset.GetY());
    skCanvas_->drawRect(skRect, paint);
#else
    RSBrush brush;
    RSSamplingOptions options;
    InitImagePaint(nullptr, &brush, options);
    brush.SetAntiAlias(antiAlias_);
    brush.SetBlendMode(RSBlendMode::CLEAR);
    RSRect rsRect(rect.Left() + offset.GetX(), rect.Top() + offset.GetY(),
        rect.Right() + offset.GetX(), rect.Bottom() + offset.GetY());
    rsCanvas_->AttachBrush(brush);
    rsCanvas_->DrawRect(rsRect);
    rsCanvas_->DetachBrush();
#endif
}

void CustomPaintPaintMethod::SetFillRuleForPath(const CanvasFillRule& rule)
{
#ifndef USE_ROSEN_DRAWING
    if (rule == CanvasFillRule::NONZERO) {
#ifndef NEW_SKIA
        skPath_.setFillType(SkPath::FillType::kWinding_FillType);
#else
        skPath_.setFillType(SkPathFillType::kWinding);
#endif
    } else if (rule == CanvasFillRule::EVENODD) {
#ifndef NEW_SKIA
        skPath_.setFillType(SkPath::FillType::kEvenOdd_FillType);
#else
        skPath_.setFillType(SkPathFillType::kEvenOdd);
#endif
    }
#else
    if (rule == CanvasFillRule::NONZERO) {
        rsPath_.SetFillStyle(RSPathFillType::WINDING);
    } else if (rule == CanvasFillRule::EVENODD) {
        rsPath_.SetFillStyle(RSPathFillType::EVENTODD);
    }
#endif
}

void CustomPaintPaintMethod::SetFillRuleForPath2D(const CanvasFillRule& rule)
{
#ifndef USE_ROSEN_DRAWING
    if (rule == CanvasFillRule::NONZERO) {
#ifndef NEW_SKIA
        skPath2d_.setFillType(SkPath::FillType::kWinding_FillType);
#else
        skPath2d_.setFillType(SkPathFillType::kWinding);
#endif
    } else if (rule == CanvasFillRule::EVENODD) {
#ifndef NEW_SKIA
        skPath2d_.setFillType(SkPath::FillType::kEvenOdd_FillType);
#else
        skPath2d_.setFillType(SkPathFillType::kEvenOdd);
#endif
    }
#else
    if (rule == CanvasFillRule::NONZERO) {
        rsPath2d_.SetFillStyle(RSPathFillType::WINDING);
    } else if (rule == CanvasFillRule::EVENODD) {
        rsPath2d_.SetFillStyle(RSPathFillType::EVENTODD);
    }
#endif
}

void CustomPaintPaintMethod::Fill(PaintWrapper* paintWrapper)
{
    OffsetF offset = GetContentOffset(paintWrapper);
#ifndef USE_ROSEN_DRAWING
    SkPaint paint;
#ifndef NEW_SKIA
    InitImagePaint(paint);
#else
    SkSamplingOptions options;
    InitImagePaint(paint, options);
#endif
    paint.setAntiAlias(antiAlias_);
    if (fillState_.GetPaintStyle() == OHOS::Ace::PaintStyle::Color) {
        paint.setColor(fillState_.GetColor().GetValue());
    }
    paint.setStyle(SkPaint::Style::kFill_Style);
    if (fillState_.GetGradient().IsValid() && fillState_.GetPaintStyle() == PaintStyle::Gradient) {
        UpdatePaintShader(offset, paint, fillState_.GetGradient());
    }
    if (fillState_.GetPatternValue().IsValid() && fillState_.GetPaintStyle() == PaintStyle::ImagePattern) {
        UpdatePaintShader(fillState_.GetPatternValue(), paint);
    }
    if (globalState_.HasGlobalAlpha()) {
        if (fillState_.GetPaintStyle() == OHOS::Ace::PaintStyle::Color) {
            paint.setAlphaf(globalState_.GetAlpha() *
                            static_cast<double>(fillState_.GetColor().GetAlpha()) /
                            MAX_GRAYSCALE);
        } else {
            paint.setAlphaf(globalState_.GetAlpha());
        }
    }
    if (HasShadow()) {
        PaintShadow(skPath_, shadow_, skCanvas_.get(), &paint);
    }
    if (globalState_.GetType() == CompositeOperation::SOURCE_OVER) {
        skCanvas_->drawPath(skPath_, paint);
    } else {
        SkPaint compositeOperationpPaint;
        InitPaintBlend(compositeOperationpPaint);
        skCanvas_->saveLayer(
            SkRect::MakeXYWH(0, 0, lastLayoutSize_.Width(), lastLayoutSize_.Height()), &compositeOperationpPaint);
        skCanvas_->drawPath(skPath_, paint);
        skCanvas_->restore();
    }
#else
    RSBrush brush;
    RSSamplingOptions options;
    InitImagePaint(nullptr, &brush, options);
    brush.SetAntiAlias(antiAlias_);
    if (fillState_.GetPaintStyle() == OHOS::Ace::PaintStyle::Color) {
        brush.SetColor(fillState_.GetColor().GetValue());
    }
    if (HasShadow()) {
        PaintShadow(rsPath_, shadow_, rsCanvas_.get());
    }
    if (fillState_.GetGradient().IsValid() && fillState_.GetPaintStyle() == PaintStyle::Gradient) {
        UpdatePaintShader(offset, nullptr, &brush, fillState_.GetGradient());
    }
    if (fillState_.GetPatternValue().IsValid() && fillState_.GetPaintStyle() == PaintStyle::ImagePattern) {
        UpdatePaintShader(fillState_.GetPatternValue(), nullptr, &brush);
    }
    if (globalState_.HasGlobalAlpha()) {
        if (fillState_.GetPaintStyle() == OHOS::Ace::PaintStyle::Color) {
            brush.SetAlphaF(globalState_.GetAlpha() *
                            static_cast<double>(fillState_.GetColor().GetAlpha()) /
                            MAX_GRAYSCALE);
        } else {
            brush.SetAlphaF(globalState_.GetAlpha());
        }
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
#endif
}

void CustomPaintPaintMethod::Fill(PaintWrapper* paintWrapper, const RefPtr<CanvasPath2D>& path)
{
    CHECK_NULL_VOID(path);
    OffsetF offset = GetContentOffset(paintWrapper);
    ParsePath2D(offset, path);
    Path2DFill(offset);
#ifndef USE_ROSEN_DRAWING
    skPath2d_.reset();
#else
    rsPath2d_.Reset();
#endif
}

void CustomPaintPaintMethod::Path2DFill(const OffsetF& offset)
{
#ifndef USE_ROSEN_DRAWING
    SkPaint paint;
#ifndef NEW_SKIA
    InitImagePaint(paint);
#else
    SkSamplingOptions options;
    InitImagePaint(paint, options);
#endif
    paint.setAntiAlias(antiAlias_);
    if (fillState_.GetPaintStyle() == OHOS::Ace::PaintStyle::Color) {
        paint.setColor(fillState_.GetColor().GetValue());
    }
    paint.setStyle(SkPaint::Style::kFill_Style);
    if (fillState_.GetGradient().IsValid() && fillState_.GetPaintStyle() == PaintStyle::Gradient) {
        UpdatePaintShader(offset, paint, fillState_.GetGradient());
    }
    if (fillState_.GetPatternValue().IsValid() && fillState_.GetPaintStyle() == PaintStyle::ImagePattern) {
        UpdatePaintShader(fillState_.GetPatternValue(), paint);
    }
    if (globalState_.HasGlobalAlpha()) {
        if (fillState_.GetPaintStyle() == OHOS::Ace::PaintStyle::Color) {
            paint.setAlphaf(globalState_.GetAlpha() *
                            static_cast<double>(fillState_.GetColor().GetAlpha()) /
                            MAX_GRAYSCALE);
        } else {
            paint.setAlphaf(globalState_.GetAlpha());
        }
    }
    if (HasShadow()) {
        PaintShadow(skPath2d_, shadow_, skCanvas_.get(), &paint);
    }
    if (globalState_.GetType() == CompositeOperation::SOURCE_OVER) {
        skCanvas_->drawPath(skPath2d_, paint);
    } else {
        SkPaint compositeOperationpPaint;
        InitPaintBlend(compositeOperationpPaint);
        skCanvas_->saveLayer(
            SkRect::MakeXYWH(0, 0, lastLayoutSize_.Width(), lastLayoutSize_.Height()), &compositeOperationpPaint);
        skCanvas_->drawPath(skPath2d_, paint);
        skCanvas_->restore();
    }
#else
    RSBrush brush;
    RSSamplingOptions options;
    InitImagePaint(nullptr, &brush, options);
    brush.SetAntiAlias(antiAlias_);
    if (fillState_.GetPaintStyle() == OHOS::Ace::PaintStyle::Color) {
        brush.SetColor(fillState_.GetColor().GetValue());
    }
    if (HasShadow()) {
        PaintShadow(rsPath2d_, shadow_, rsCanvas_.get());
    }
    if (fillState_.GetGradient().IsValid() && fillState_.GetPaintStyle() == PaintStyle::Gradient) {
        UpdatePaintShader(offset, nullptr, &brush, fillState_.GetGradient());
    }
    if (fillState_.GetPatternValue().IsValid() && fillState_.GetPaintStyle() == PaintStyle::ImagePattern) {
        UpdatePaintShader(fillState_.GetPattern(), nullptr, &brush);
    }
    if (globalState_.HasGlobalAlpha()) {
        if (fillState_.GetPaintStyle() == OHOS::Ace::PaintStyle::Color) {
            brush.SetAlphaF(globalState_.GetAlpha() *
                            static_cast<double>(fillState_.GetColor().GetAlpha()) /
                            MAX_GRAYSCALE);
        } else {
            brush.SetAlphaF(globalState_.GetAlpha());
        }
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
#endif
}

void CustomPaintPaintMethod::Stroke(PaintWrapper* paintWrapper)
{
    OffsetF offset = GetContentOffset(paintWrapper);
#ifndef USE_ROSEN_DRAWING
    SkPaint paint;
#ifndef NEW_SKIA
    GetStrokePaint(paint);
#else
    SkSamplingOptions options;
    GetStrokePaint(paint, options);
#endif
    paint.setAntiAlias(antiAlias_);
    if (strokeState_.GetGradient().IsValid() && strokeState_.GetPaintStyle() == PaintStyle::Gradient) {
        UpdatePaintShader(offset, paint, strokeState_.GetGradient());
    }
    if (strokeState_.GetPatternValue().IsValid() && strokeState_.GetPaintStyle() == PaintStyle::ImagePattern) {
        UpdatePaintShader(strokeState_.GetPatternValue(), paint);
    }
    if (HasShadow()) {
        PaintShadow(skPath_, shadow_, skCanvas_.get(), &paint);
    }
    if (globalState_.GetType() == CompositeOperation::SOURCE_OVER) {
        skCanvas_->drawPath(skPath_, paint);
    } else {
        SkPaint compositeOperationpPaint;
        InitPaintBlend(compositeOperationpPaint);
        skCanvas_->saveLayer(
            SkRect::MakeXYWH(0, 0, lastLayoutSize_.Width(), lastLayoutSize_.Height()), &compositeOperationpPaint);
        skCanvas_->drawPath(skPath_, paint);
        skCanvas_->restore();
    }
#else
    RSPen pen;
    RSSamplingOptions options;
    GetStrokePaint(pen, options);
    pen.SetAntiAlias(antiAlias_);
    if (HasShadow()) {
        PaintShadow(rsPath_, shadow_, rsCanvas_.get());
    }
    if (strokeState_.GetGradient().IsValid() && strokeState_.GetPaintStyle() == PaintStyle::Gradient) {
        UpdatePaintShader(offset, &pen, nullptr, strokeState_.GetGradient());
    }
    if (strokeState_.GetPatternValue().IsValid() && strokeState_.GetPaintStyle() == PaintStyle::ImagePattern) {
        UpdatePaintShader(strokeState_.GetPatternValue(), &pen, nullptr);
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
#endif
}

void CustomPaintPaintMethod::Stroke(PaintWrapper* paintWrapper, const RefPtr<CanvasPath2D>& path)
{
    CHECK_NULL_VOID(path);
    OffsetF offset = GetContentOffset(paintWrapper);
    ParsePath2D(offset, path);
    Path2DStroke(offset);
#ifndef USE_ROSEN_DRAWING
    skPath2d_.reset();
#else
    rsPath2d_.Reset();
#endif
}

void CustomPaintPaintMethod::Path2DStroke(const OffsetF& offset)
{
#ifndef USE_ROSEN_DRAWING
    SkPaint paint;
#ifndef NEW_SKIA
    GetStrokePaint(paint);
#else
    SkSamplingOptions options;
    GetStrokePaint(paint, options);
#endif
    paint.setAntiAlias(antiAlias_);
    if (strokeState_.GetGradient().IsValid() && strokeState_.GetPaintStyle() == PaintStyle::Gradient) {
        UpdatePaintShader(offset, paint, strokeState_.GetGradient());
    }
    if (strokeState_.GetPatternValue().IsValid() && strokeState_.GetPaintStyle() == PaintStyle::ImagePattern) {
        UpdatePaintShader(strokeState_.GetPatternValue(), paint);
    }
    if (HasShadow()) {
        PaintShadow(skPath2d_, shadow_, skCanvas_.get(), &paint);
    }
    if (globalState_.GetType() == CompositeOperation::SOURCE_OVER) {
        skCanvas_->drawPath(skPath2d_, paint);
    } else {
        SkPaint compositeOperationpPaint;
        InitPaintBlend(compositeOperationpPaint);
        skCanvas_->saveLayer(
            SkRect::MakeXYWH(0, 0, lastLayoutSize_.Width(), lastLayoutSize_.Height()), &compositeOperationpPaint);
        skCanvas_->drawPath(skPath2d_, paint);
        skCanvas_->restore();
    }
#else
    RSPen pen;
    RSSamplingOptions options;
    GetStrokePaint(pen, options);
    pen.SetAntiAlias(antiAlias_);
    if (HasShadow()) {
        PaintShadow(rsPath2d_, shadow_, rsCanvas_.get());
    }
    if (strokeState_.GetGradient().IsValid() && strokeState_.GetPaintStyle() == PaintStyle::Gradient) {
        UpdatePaintShader(offset, &pen, nullptr, strokeState_.GetGradient());
    }
    if (strokeState_.GetPatternValue().IsValid() && strokeState_.GetPaintStyle() == PaintStyle::ImagePattern) {
        UpdatePaintShader(strokeState_.GetPatternValue(), &pen, nullptr);
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
#endif
}

void CustomPaintPaintMethod::Clip()
{
#ifndef USE_ROSEN_DRAWING
    skCanvas_->clipPath(skPath_);
#else
    rsCanvas_->ClipPath(rsPath_, RSClipOp::INTERSECT);
#endif
}

void CustomPaintPaintMethod::Clip(const RefPtr<CanvasPath2D>& path)
{
    CHECK_NULL_VOID(path);
    auto offset = OffsetF(0, 0);
    ParsePath2D(offset, path);
    Path2DClip();
#ifndef USE_ROSEN_DRAWING
    skPath2d_.reset();
#else
    rsPath2d_.Reset();
#endif
}

void CustomPaintPaintMethod::Path2DClip()
{
#ifndef USE_ROSEN_DRAWING
    skCanvas_->clipPath(skPath2d_);
#else
    rsCanvas_->ClipPath(rsPath2d_, RSClipOp::INTERSECT);
#endif
}

void CustomPaintPaintMethod::BeginPath()
{
#ifndef USE_ROSEN_DRAWING
    skPath_.reset();
#else
    rsPath_.Reset();
#endif
}

void CustomPaintPaintMethod::ClosePath()
{
#ifndef USE_ROSEN_DRAWING
    skPath_.close();
#else
    rsPath_.Close();
#endif
}

void CustomPaintPaintMethod::MoveTo(PaintWrapper* paintWrapper, double x, double y)
{
    OffsetF offset = GetContentOffset(paintWrapper);
#ifndef USE_ROSEN_DRAWING
    skPath_.moveTo(SkDoubleToScalar(x + offset.GetX()), SkDoubleToScalar(y + offset.GetY()));
#else
    rsPath_.MoveTo(
        static_cast<RSScalar>(x + offset.GetX()), static_cast<RSScalar>(y + offset.GetY()));
#endif
}

void CustomPaintPaintMethod::LineTo(PaintWrapper* paintWrapper, double x, double y)
{
    OffsetF offset = GetContentOffset(paintWrapper);
#ifndef USE_ROSEN_DRAWING
    skPath_.lineTo(SkDoubleToScalar(x + offset.GetX()), SkDoubleToScalar(y + offset.GetY()));
#else
    rsPath_.LineTo(
        static_cast<RSScalar>(x + offset.GetX()), static_cast<RSScalar>(y + offset.GetY()));
#endif
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
#ifndef USE_ROSEN_DRAWING
    auto rect = SkRect::MakeLTRB(left, top, right, bottom);
    if (NearEqual(std::fmod(sweepAngle, FULL_CIRCLE_ANGLE), 0.0) && !NearEqual(startAngle, endAngle)) {
        // draw circle
        double half = GreatNotEqual(sweepAngle, 0.0) ? HALF_CIRCLE_ANGLE : -HALF_CIRCLE_ANGLE;
        skPath_.arcTo(rect, SkDoubleToScalar(startAngle), SkDoubleToScalar(half), false);
        skPath_.arcTo(rect, SkDoubleToScalar(half + startAngle), SkDoubleToScalar(half), false);
    } else if (!NearEqual(std::fmod(sweepAngle, FULL_CIRCLE_ANGLE), 0.0) && abs(sweepAngle) > FULL_CIRCLE_ANGLE) {
        double half = GreatNotEqual(sweepAngle, 0.0) ? HALF_CIRCLE_ANGLE : -HALF_CIRCLE_ANGLE;
        skPath_.arcTo(rect, SkDoubleToScalar(startAngle), SkDoubleToScalar(half), false);
        skPath_.arcTo(rect, SkDoubleToScalar(half + startAngle), SkDoubleToScalar(half), false);
        skPath_.arcTo(rect, SkDoubleToScalar(half + half + startAngle), SkDoubleToScalar(sweepAngle), false);
    } else {
        skPath_.arcTo(rect, SkDoubleToScalar(startAngle), SkDoubleToScalar(sweepAngle), false);
    }
#else
    RSPoint point1(left, top);
    RSPoint point2(right, bottom);
    if (NearEqual(std::fmod(sweepAngle, FULL_CIRCLE_ANGLE), 0.0) && !NearEqual(startAngle, endAngle)) {
        // draw circle
        double half = GreatNotEqual(sweepAngle, 0.0) ? HALF_CIRCLE_ANGLE : -HALF_CIRCLE_ANGLE;
        rsPath_.ArcTo(point1, point2, static_cast<RSScalar>(startAngle), static_cast<RSScalar>(half));
        rsPath_.ArcTo(point1, point2, static_cast<RSScalar>(half + startAngle), static_cast<RSScalar>(half));
    } else if (!NearEqual(std::fmod(sweepAngle, FULL_CIRCLE_ANGLE), 0.0) && abs(sweepAngle) > FULL_CIRCLE_ANGLE) {
        double half = GreatNotEqual(sweepAngle, 0.0) ? HALF_CIRCLE_ANGLE : -HALF_CIRCLE_ANGLE;
        rsPath_.ArcTo(point1, point2, static_cast<RSScalar>(startAngle), static_cast<RSScalar>(half));
        rsPath_.ArcTo(point1, point2, static_cast<RSScalar>(half + startAngle), static_cast<RSScalar>(half));
        rsPath_.ArcTo(point1, point2, static_cast<RSScalar>(half + half + startAngle),
            static_cast<RSScalar>(sweepAngle));
    } else {
        rsPath_.ArcTo(point1, point2, static_cast<RSScalar>(startAngle), static_cast<RSScalar>(sweepAngle));
    }
#endif
}

void CustomPaintPaintMethod::ArcTo(PaintWrapper* paintWrapper, const ArcToParam& param)
{
#ifndef USE_ROSEN_DRAWING
    OffsetF offset = GetContentOffset(paintWrapper);
    double x1 = param.x1 + offset.GetX();
    double y1 = param.y1 + offset.GetY();
    double x2 = param.x2 + offset.GetX();
    double y2 = param.y2 + offset.GetY();
    double radius = param.radius;
    skPath_.arcTo(SkDoubleToScalar(x1), SkDoubleToScalar(y1), SkDoubleToScalar(x2), SkDoubleToScalar(y2),
        SkDoubleToScalar(radius));
#else
    LOGE("Drawing is not supported");
#endif
}

void CustomPaintPaintMethod::AddRect(PaintWrapper* paintWrapper, const Rect& rect)
{
    OffsetF offset = GetContentOffset(paintWrapper);
#ifndef USE_ROSEN_DRAWING
    SkRect skRect = SkRect::MakeLTRB(rect.Left() + offset.GetX(), rect.Top() + offset.GetY(),
        rect.Right() + offset.GetX(), offset.GetY() + rect.Bottom());
    skPath_.addRect(skRect);
#else
    RSRect rsRect(rect.Left() + offset.GetX(), rect.Top() + offset.GetY(),
        rect.Right() + offset.GetX(), offset.GetY() + rect.Bottom());
    rsPath_.AddRect(rsRect);
#endif
}

void CustomPaintPaintMethod::Ellipse(PaintWrapper* paintWrapper, const EllipseParam& param)
{
    OffsetF offset = GetContentOffset(paintWrapper);
    // Init the start and end angle, then calculated the sweepAngle.
    double startAngle = std::fmod(param.startAngle, M_PI * 2.0);
    double endAngle = std::fmod(param.endAngle, M_PI * 2.0);
    startAngle = (startAngle < 0.0 ? startAngle + M_PI * 2.0 : startAngle) * HALF_CIRCLE_ANGLE / M_PI;
    endAngle = (endAngle < 0.0 ? endAngle + M_PI * 2.0 : endAngle) * HALF_CIRCLE_ANGLE / M_PI;
    if (NearEqual(param.startAngle, param.endAngle)) {
        return; // Just return when startAngle is same as endAngle.
    }
    double rotation = param.rotation * HALF_CIRCLE_ANGLE / M_PI;
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
#ifndef USE_ROSEN_DRAWING
    auto rect = SkRect::MakeLTRB(left, top, right, bottom);
    if (!NearZero(rotation)) {
        SkMatrix matrix;
        matrix.setRotate(-rotation, param.x + offset.GetX(), param.y + offset.GetY());
        skPath_.transform(matrix);
    }
    if (NearZero(sweepAngle) && !NearZero(param.endAngle - param.startAngle)) {
        // The entire ellipse needs to be drawn with two arcTo.
        skPath_.arcTo(rect, startAngle, HALF_CIRCLE_ANGLE, false);
        skPath_.arcTo(rect, startAngle + HALF_CIRCLE_ANGLE, HALF_CIRCLE_ANGLE, false);
    } else {
        skPath_.arcTo(rect, startAngle, sweepAngle, false);
    }
    if (!NearZero(rotation)) {
        SkMatrix matrix;
        matrix.setRotate(rotation, param.x + offset.GetX(), param.y + offset.GetY());
        skPath_.transform(matrix);
    }
#else
    RSPoint point1(left, top);
    RSPoint point2(right, bottom);
    if (!NearZero(rotation)) {
        RSMatrix matrix;
        matrix.Rotate(-rotation, param.x + offset.GetX(), param.y + offset.GetY());
        rsPath_.Transform(matrix);
    }
    if (NearZero(sweepAngle) && !NearZero(param.endAngle - param.startAngle)) {
        // The entire ellipse needs to be drawn with two arcTo.
        rsPath_.ArcTo(point1, point2, startAngle, HALF_CIRCLE_ANGLE);
        rsPath_.ArcTo(point1, point2, startAngle + HALF_CIRCLE_ANGLE, HALF_CIRCLE_ANGLE);
    } else {
        rsPath_.ArcTo(point1, point2, startAngle, sweepAngle);
    }
    if (!NearZero(rotation)) {
        RSMatrix matrix;
        matrix.Rotate(rotation, param.x + offset.GetX(), param.y + offset.GetY());
        rsPath_.Transform(matrix);
    }
#endif
}

void CustomPaintPaintMethod::BezierCurveTo(PaintWrapper* paintWrapper, const BezierCurveParam& param)
{
    OffsetF offset = GetContentOffset(paintWrapper);
#ifndef USE_ROSEN_DRAWING
    skPath_.cubicTo(SkDoubleToScalar(param.cp1x + offset.GetX()), SkDoubleToScalar(param.cp1y + offset.GetY()),
        SkDoubleToScalar(param.cp2x + offset.GetX()), SkDoubleToScalar(param.cp2y + offset.GetY()),
        SkDoubleToScalar(param.x + offset.GetX()), SkDoubleToScalar(param.y + offset.GetY()));
#else
    rsPath_.CubicTo(static_cast<RSScalar>(param.cp1x + offset.GetX()),
        static_cast<RSScalar>(param.cp1y + offset.GetY()),
        static_cast<RSScalar>(param.cp2x + offset.GetX()),
        static_cast<RSScalar>(param.cp2y + offset.GetY()),
        static_cast<RSScalar>(param.x + offset.GetX()),
        static_cast<RSScalar>(param.y + offset.GetY()));
#endif
}

void CustomPaintPaintMethod::QuadraticCurveTo(PaintWrapper* paintWrapper, const QuadraticCurveParam& param)
{
    OffsetF offset = GetContentOffset(paintWrapper);
#ifndef USE_ROSEN_DRAWING
    skPath_.quadTo(SkDoubleToScalar(param.cpx + offset.GetX()), SkDoubleToScalar(param.cpy + offset.GetY()),
        SkDoubleToScalar(param.x + offset.GetX()), SkDoubleToScalar(param.y + offset.GetY()));
#else
    rsPath_.QuadTo(static_cast<RSScalar>(param.cpx + offset.GetX()),
        static_cast<RSScalar>(param.cpy + offset.GetY()),
        static_cast<RSScalar>(param.x + offset.GetX()),
        static_cast<RSScalar>(param.y + offset.GetY()));
#endif
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
#ifndef USE_ROSEN_DRAWING
    SkPath out;
    SkParsePath::FromSVGString(args.cmds.c_str(), &out);
    skPath2d_.addPath(out);
#else
    RSRecordingPath out;
    out.BuildFromSVGString(args.cmds);
    rsPath2d_.AddPath(out);
#endif
}

void CustomPaintPaintMethod::Path2DClosePath(const OffsetF& offset, const PathArgs& args)
{
#ifndef USE_ROSEN_DRAWING
    skPath2d_.close();
#else
    rsPath2d_.Close();
#endif
}

void CustomPaintPaintMethod::Path2DMoveTo(const OffsetF& offset, const PathArgs& args)
{
    double x = args.para1 + offset.GetX();
    double y = args.para2 + offset.GetY();
#ifndef USE_ROSEN_DRAWING
    skPath2d_.moveTo(x, y);
#else
    rsPath2d_.MoveTo(x, y);
#endif
}

void CustomPaintPaintMethod::Path2DLineTo(const OffsetF& offset, const PathArgs& args)
{
    double x = args.para1 + offset.GetX();
    double y = args.para2 + offset.GetY();
#ifndef USE_ROSEN_DRAWING
    skPath2d_.lineTo(x, y);
#else
    rsPath2d_.LineTo(x, y);
#endif
}

void CustomPaintPaintMethod::Path2DArc(const OffsetF& offset, const PathArgs& args)
{
    double x = args.para1;
    double y = args.para2;
    double r = args.para3;
#ifndef USE_ROSEN_DRAWING
    auto rect =
        SkRect::MakeLTRB(x - r + offset.GetX(), y - r + offset.GetY(), x + r + offset.GetX(), y + r + offset.GetY());
#else
    RSPoint point1(x - r + offset.GetX(), y - r + offset.GetY());
    RSPoint point2(x + r + offset.GetX(), y + r + offset.GetY());
#endif
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
#ifndef USE_ROSEN_DRAWING
    if (NearEqual(std::fmod(sweepAngle, FULL_CIRCLE_ANGLE), 0.0) && !NearEqual(startAngle, endAngle)) {
        skPath2d_.arcTo(rect, startAngle, HALF_CIRCLE_ANGLE, false);
        skPath2d_.arcTo(rect, startAngle + HALF_CIRCLE_ANGLE, HALF_CIRCLE_ANGLE, false);
    } else if (!NearEqual(std::fmod(sweepAngle, FULL_CIRCLE_ANGLE), 0.0) && abs(sweepAngle) > FULL_CIRCLE_ANGLE) {
        skPath2d_.arcTo(rect, startAngle, HALF_CIRCLE_ANGLE, false);
        skPath2d_.arcTo(rect, startAngle + HALF_CIRCLE_ANGLE, HALF_CIRCLE_ANGLE, false);
        skPath2d_.arcTo(rect, startAngle + HALF_CIRCLE_ANGLE + HALF_CIRCLE_ANGLE, sweepAngle, false);
    } else {
        skPath2d_.arcTo(rect, startAngle, sweepAngle, false);
    }
#else
    if (NearEqual(std::fmod(sweepAngle, FULL_CIRCLE_ANGLE), 0.0) && !NearEqual(startAngle, endAngle)) {
        rsPath2d_.ArcTo(point1, point2, startAngle, HALF_CIRCLE_ANGLE);
        rsPath2d_.ArcTo(point1, point2, startAngle + HALF_CIRCLE_ANGLE, HALF_CIRCLE_ANGLE);
    } else if (!NearEqual(std::fmod(sweepAngle, FULL_CIRCLE_ANGLE), 0.0) && abs(sweepAngle) > FULL_CIRCLE_ANGLE) {
        rsPath2d_.ArcTo(point1, point2, startAngle, HALF_CIRCLE_ANGLE);
        rsPath2d_.ArcTo(point1, point2, startAngle + HALF_CIRCLE_ANGLE, HALF_CIRCLE_ANGLE);
        rsPath2d_.ArcTo(point1, point2, startAngle + HALF_CIRCLE_ANGLE + HALF_CIRCLE_ANGLE, sweepAngle);
    } else {
        rsPath2d_.ArcTo(point1, point2, startAngle, sweepAngle);
    }
#endif
}

void CustomPaintPaintMethod::Path2DArcTo(const OffsetF& offset, const PathArgs& args)
{
#ifndef USE_ROSEN_DRAWING
    double x1 = args.para1 + offset.GetX();
    double y1 = args.para2 + offset.GetY();
    double x2 = args.para3 + offset.GetX();
    double y2 = args.para4 + offset.GetY();
    double r = args.para5;
    skPath2d_.arcTo(x1, y1, x2, y2, r);
#else
    LOGE("Drawing is not supported");
#endif
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
    double startAngle = std::fmod(args.para6, M_PI * 2.0);
    double endAngle = std::fmod(args.para7, M_PI * 2.0);
    bool anticlockwise = NearZero(args.para8) ? false : true;
    startAngle = (startAngle < 0.0 ? startAngle + M_PI * 2.0 : startAngle) * HALF_CIRCLE_ANGLE / M_PI;
    endAngle = (endAngle < 0.0 ? endAngle + M_PI * 2.0 : endAngle) * HALF_CIRCLE_ANGLE / M_PI;
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
#ifndef USE_ROSEN_DRAWING
    auto rect = SkRect::MakeLTRB(
        x - rx + offset.GetX(), y - ry + offset.GetY(), x + rx + offset.GetX(), y + ry + offset.GetY());

    if (!NearZero(rotation)) {
        SkMatrix matrix;
        matrix.setRotate(-rotation, x + offset.GetX(), y + offset.GetY());
        skPath2d_.transform(matrix);
    }
    if (NearZero(sweepAngle) && !NearZero(args.para6 - args.para7)) {
        // The entire ellipse needs to be drawn with two arcTo.
        skPath2d_.arcTo(rect, startAngle, HALF_CIRCLE_ANGLE, false);
        skPath2d_.arcTo(rect, startAngle + HALF_CIRCLE_ANGLE, HALF_CIRCLE_ANGLE, false);
    } else {
        skPath2d_.arcTo(rect, startAngle, sweepAngle, false);
    }
    if (!NearZero(rotation)) {
        SkMatrix matrix;
        matrix.setRotate(rotation, x + offset.GetX(), y + offset.GetY());
        skPath2d_.transform(matrix);
    }
#else
    RSPoint point1(x - rx + offset.GetX(), y - ry + offset.GetY());
    RSPoint point2(x + rx + offset.GetX(), y + ry + offset.GetY());

    if (!NearZero(rotation)) {
        RSMatrix matrix;
        matrix.Rotate(-rotation, x + offset.GetX(), y + offset.GetY());
        rsPath2d_.Transform(matrix);
    }
    if (NearZero(sweepAngle) && !NearZero(args.para6 - args.para7)) {
        // The entire ellipse needs to be drawn with two arcTo.
        rsPath2d_.ArcTo(point1, point2, startAngle, HALF_CIRCLE_ANGLE);
        rsPath2d_.ArcTo(point1, point2, startAngle + HALF_CIRCLE_ANGLE, HALF_CIRCLE_ANGLE);
    } else {
        rsPath2d_.ArcTo(point1, point2, startAngle, sweepAngle);
    }
    if (!NearZero(rotation)) {
        RSMatrix matrix;
        matrix.Rotate(rotation, x + offset.GetX(), y + offset.GetY());
        rsPath2d_.Transform(matrix);
    }
#endif
}

void CustomPaintPaintMethod::Path2DBezierCurveTo(const OffsetF& offset, const PathArgs& args)
{
    double cp1x = args.para1 + offset.GetX();
    double cp1y = args.para2 + offset.GetY();
    double cp2x = args.para3 + offset.GetX();
    double cp2y = args.para4 + offset.GetY();
    double x = args.para5 + offset.GetX();
    double y = args.para6 + offset.GetY();
#ifndef USE_ROSEN_DRAWING
    skPath2d_.cubicTo(cp1x, cp1y, cp2x, cp2y, x, y);
#else
    rsPath2d_.CubicTo(cp1x, cp1y, cp2x, cp2y, x, y);
#endif
}

void CustomPaintPaintMethod::Path2DQuadraticCurveTo(const OffsetF& offset, const PathArgs& args)
{
    double cpx = args.para1 + offset.GetX();
    double cpy = args.para2 + offset.GetY();
    double x = args.para3 + offset.GetX();
    double y = args.para4 + offset.GetY();
#ifndef USE_ROSEN_DRAWING
    skPath2d_.quadTo(cpx, cpy, x, y);
#else
    rsPath2d_.QuadTo(cpx, cpy, x, y);
#endif
}

void CustomPaintPaintMethod::Path2DSetTransform(const OffsetF& offset, const PathArgs& args)
{
#ifndef USE_ROSEN_DRAWING
    SkMatrix skMatrix;
#else
    RSMatrix matrix;
#endif
    double scaleX = args.para1;
    double skewX = args.para2;
    double skewY = args.para3;
    double scaleY = args.para4;
    double translateX = args.para5;
    double translateY = args.para6;
#ifndef USE_ROSEN_DRAWING
    skMatrix.setAll(scaleX, skewY, translateX, skewX, scaleY, translateY, 0.0f, 0.0f, 1.0f);
    skPath2d_.transform(skMatrix);
#else
    matrix.SetMatrix(scaleX, skewY, translateX, skewX, scaleY, translateY, 0, 0, 1);
    rsPath2d_.Transform(matrix);
#endif
}

void CustomPaintPaintMethod::Save()
{
    SaveStates();
#ifndef USE_ROSEN_DRAWING
    skCanvas_->save();
#else
    rsCanvas_->Save();
#endif
}

void CustomPaintPaintMethod::Restore()
{
    RestoreStates();
#ifndef USE_ROSEN_DRAWING
    skCanvas_->restore();
#else
    rsCanvas_->Restore();
#endif
}

void CustomPaintPaintMethod::Scale(double x, double y)
{
#ifndef USE_ROSEN_DRAWING
    skCanvas_->scale(x, y);
#else
    rsCanvas_->Scale(x, y);
#endif
}

void CustomPaintPaintMethod::Rotate(double angle)
{
#ifndef USE_ROSEN_DRAWING
    skCanvas_->rotate(angle * 180 / M_PI);
#else
    rsCanvas_->Rotate(angle * 180 / M_PI);
#endif
}

void CustomPaintPaintMethod::ResetTransform()
{
#ifndef USE_ROSEN_DRAWING
    skCanvas_->resetMatrix();
#else
    rsCanvas_->ResetMatrix();
#endif
}

void CustomPaintPaintMethod::Transform(const TransformParam& param)
{
#ifndef USE_ROSEN_DRAWING
    SkMatrix skMatrix;
    skMatrix.setAll(param.scaleX, param.skewY, param.translateX, param.skewX, param.scaleY, param.translateY, 0, 0, 1);
    skCanvas_->concat(skMatrix);
#else
    RSMatrix matrix;
    matrix.SetMatrix(param.scaleX, param.skewY, param.translateX, param.skewX, param.scaleY, param.translateY, 0, 0, 1);
    rsCanvas_->ConcatMatrix(matrix);
#endif
}

void CustomPaintPaintMethod::Translate(double x, double y)
{
#ifndef USE_ROSEN_DRAWING
    skCanvas_->translate(x, y);
#else
    rsCanvas_->Translate(x, y);
#endif
}

#ifndef USE_GRAPHIC_TEXT_GINE
double CustomPaintPaintMethod::GetAlignOffset(TextAlign align, std::unique_ptr<txt::Paragraph>& paragraph)
#else
double CustomPaintPaintMethod::GetAlignOffset(TextAlign align, std::unique_ptr<OHOS::Rosen::Typography>& paragraph)
#endif
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

#ifndef USE_GRAPHIC_TEXT_GINE
txt::TextAlign CustomPaintPaintMethod::GetEffectiveAlign(txt::TextAlign align, txt::TextDirection direction) const
#else
OHOS::Rosen::TextAlign CustomPaintPaintMethod::GetEffectiveAlign(
    OHOS::Rosen::TextAlign align, OHOS::Rosen::TextDirection direction) const
#endif
{
#ifndef USE_GRAPHIC_TEXT_GINE
    if (align == txt::TextAlign::start) {
        return (direction == txt::TextDirection::ltr) ? txt::TextAlign::left
                                                      : txt::TextAlign::right;
    } else if (align == txt::TextAlign::end) {
        return (direction == txt::TextDirection::ltr) ? txt::TextAlign::right
                                                      : txt::TextAlign::left;
#else
    if (align == OHOS::Rosen::TextAlign::START) {
        return (direction == OHOS::Rosen::TextDirection::LTR) ? OHOS::Rosen::TextAlign::LEFT
                                                      : OHOS::Rosen::TextAlign::RIGHT;
    } else if (align == OHOS::Rosen::TextAlign::END) {
        return (direction == OHOS::Rosen::TextDirection::LTR) ? OHOS::Rosen::TextAlign::RIGHT
                                                      : OHOS::Rosen::TextAlign::LEFT;
#endif
    } else {
        return align;
    }
}

#ifndef USE_ROSEN_DRAWING
void CustomPaintPaintMethod::ClearPaintImage(SkPaint& paint)
{
    float matrix[20] = { 0.0f };
    matrix[0] = matrix[6] = matrix[12] = matrix[18] = 1.0f;
#ifdef USE_SYSTEM_SKIA
    paint.setColorFilter(SkColorFilter::MakeMatrixFilterRowMajor255(matrix));
#else
    paint.setColorFilter(SkColorFilters::Matrix(matrix));
#endif
    paint.setMaskFilter(SkMaskFilter::MakeBlur(SkBlurStyle::kNormal_SkBlurStyle, 0));
#ifdef NEW_SKIA
    paint.setImageFilter(SkImageFilters::Blur(0, 0, nullptr));
#else
    paint.setImageFilter(SkBlurImageFilter::Make(0, 0, nullptr));
#endif
}
#else
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
#endif

#ifndef USE_ROSEN_DRAWING
void CustomPaintPaintMethod::SetPaintImage(SkPaint& paint)
#else
void CustomPaintPaintMethod::SetPaintImage(RSPen* pen, RSBrush* brush)
#endif
{
    FilterType filterType;
    std::string filterParam;
    if (!GetFilterType(filterType, filterParam)) {
        return;
    }
    switch (filterType) {
        case FilterType::NONE:
            break;
        case FilterType::GRAYSCALE:
#ifndef USE_ROSEN_DRAWING
            SetGrayFilter(filterParam, paint);
#else
            SetGrayFilter(filterParam, pen, brush);
#endif
            break;
        case FilterType::SEPIA:
#ifndef USE_ROSEN_DRAWING
            SetSepiaFilter(filterParam, paint);
#else
            SetSepiaFilter(filterParam, pen, brush);
#endif
            break;
        case FilterType::SATURATE:
#ifndef USE_ROSEN_DRAWING
            SetSaturateFilter(filterParam, paint);
#else
            SetSaturateFilter(filterParam, pen, brush);
#endif
            break;
        case FilterType::HUE_ROTATE:
#ifndef USE_ROSEN_DRAWING
            SetHueRotateFilter(filterParam, paint);
#else
            SetHueRotateFilter(filterParam, pen, brush);
#endif
            break;
        case FilterType::INVERT:
#ifndef USE_ROSEN_DRAWING
            SetInvertFilter(filterParam, paint);
#else
            SetInvertFilter(filterParam, pen, brush);
#endif
            break;
        case FilterType::OPACITY:
#ifndef USE_ROSEN_DRAWING
            SetOpacityFilter(filterParam, paint);
#else
            SetOpacityFilter(filterParam, pen, brush);
#endif
            break;
        case FilterType::BRIGHTNESS:
#ifndef USE_ROSEN_DRAWING
            SetBrightnessFilter(filterParam, paint);
#else
            SetBrightnessFilter(filterParam, pen, brush);
#endif
            break;
        case FilterType::CONTRAST:
#ifndef USE_ROSEN_DRAWING
            SetContrastFilter(filterParam, paint);
#else
            SetContrastFilter(filterParam, pen, brush);
#endif
            break;
        case FilterType::BLUR:
#ifndef USE_ROSEN_DRAWING
            SetBlurFilter(filterParam, paint);
#else
            SetBlurFilter(filterParam, pen, brush);
#endif
            break;
        case FilterType::DROP_SHADOW:
            LOGW("Dropshadow is not supported yet.");
            break;
        default:
            LOGE("invalid type of filter");
    }
}

// https://drafts.fxtf.org/filter-effects/#grayscaleEquivalent
#ifndef USE_ROSEN_DRAWING
void CustomPaintPaintMethod::SetGrayFilter(const std::string& percent, SkPaint& paint)
#else
void CustomPaintPaintMethod::SetGrayFilter(const std::string& percent, RSPen* pen, RSBrush* brush)
#endif
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
#ifndef USE_ROSEN_DRAWING
    SetColorFilter(matrix, paint);
#else
    SetColorFilter(matrix, pen, brush);
#endif
}

// https://drafts.fxtf.org/filter-effects/#sepiaEquivalent
#ifndef USE_ROSEN_DRAWING
void CustomPaintPaintMethod::SetSepiaFilter(const std::string& percent, SkPaint& paint)
#else
void CustomPaintPaintMethod::SetSepiaFilter(const std::string& percent, RSPen* pen, RSBrush* brush)
#endif
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
#ifndef USE_ROSEN_DRAWING
    SetColorFilter(matrix, paint);
#else
    SetColorFilter(matrix, pen, brush);
#endif
}

// https://drafts.fxtf.org/filter-effects/#saturateEquivalent
#ifndef USE_ROSEN_DRAWING
void CustomPaintPaintMethod::SetSaturateFilter(const std::string& percent, SkPaint& paint)
#else
void CustomPaintPaintMethod::SetSaturateFilter(const std::string& percent, RSPen* pen, RSBrush* brush)
#endif
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
#ifndef USE_ROSEN_DRAWING
    SetColorFilter(matrix, paint);
#else
    SetColorFilter(matrix, pen, brush);
#endif
}

// https://drafts.fxtf.org/filter-effects/#huerotateEquivalent
#ifndef USE_ROSEN_DRAWING
void CustomPaintPaintMethod::SetHueRotateFilter(const std::string& filterParam, SkPaint& paint)
#else
void CustomPaintPaintMethod::SetHueRotateFilter(const std::string& filterParam, RSPen* pen, RSBrush* brush)
#endif
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
#ifndef USE_ROSEN_DRAWING
    SetColorFilter(matrix, paint);
#else
    SetColorFilter(matrix, pen, brush);
#endif
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
#ifndef USE_ROSEN_DRAWING
void CustomPaintPaintMethod::SetInvertFilter(const std::string& percent, SkPaint& paint)
#else
void CustomPaintPaintMethod::SetInvertFilter(const std::string& percent, RSPen* pen, RSBrush* brush)
#endif
{
    float percentNum = 1.0f;
    if (!CheckNumberAndPercentage(percent, true, percentNum)) {
        return;
    }
    float matrix[20] = { 0.0f };
    matrix[0] = matrix[6] = matrix[12] = 1.0 - 2.0 * percentNum;
    matrix[4] = matrix[9] = matrix[14] = percentNum;
    matrix[18] = 1.0f;
#ifndef USE_ROSEN_DRAWING
    SetColorFilter(matrix, paint);
#else
    SetColorFilter(matrix, pen, brush);
#endif
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
#ifndef USE_ROSEN_DRAWING
void CustomPaintPaintMethod::SetOpacityFilter(const std::string& percent, SkPaint& paint)
#else
void CustomPaintPaintMethod::SetOpacityFilter(const std::string& percent, RSPen* pen, RSBrush* brush)
#endif
{
    float percentNum = 1.0f;
    if (!CheckNumberAndPercentage(percent, true, percentNum)) {
        return;
    }
    float matrix[20] = { 0.0f };
    matrix[0] = matrix[6] = matrix[12] = 1.0f;
    matrix[18] = percentNum;
#ifndef USE_ROSEN_DRAWING
    SetColorFilter(matrix, paint);
#else
    SetColorFilter(matrix, pen, brush);
#endif
}

/*
 * https://drafts.fxtf.org/filter-effects/#brightnessEquivalent
 * Example for R in RGB:
 * R' = funcR(R) = slope * R + intercept
 * where: slope = percentNum, intercept = 0
 */
#ifndef USE_ROSEN_DRAWING
void CustomPaintPaintMethod::SetBrightnessFilter(const std::string& percent, SkPaint& paint)
#else
void CustomPaintPaintMethod::SetBrightnessFilter(const std::string& percent, RSPen* pen, RSBrush* brush)
#endif
{
    float percentNum = 1.0f;
    if (!CheckNumberAndPercentage(percent, false, percentNum)) {
        return;
    }
    float matrix[20] = { 0.0f };
    matrix[0] = matrix[6] = matrix[12] = percentNum;
    matrix[18] = 1.0f;
#ifndef USE_ROSEN_DRAWING
    SetColorFilter(matrix, paint);
#else
    SetColorFilter(matrix, pen, brush);
#endif
}

/*
 * https://drafts.fxtf.org/filter-effects/#contrastEquivalent
 * Example for R in RGB:
 * R' = funcR(R) = slope * R + intercept
 * where: slope = percentNum, intercept = 0.5 * (1 - percentNum)
 */
#ifndef USE_ROSEN_DRAWING
void CustomPaintPaintMethod::SetContrastFilter(const std::string& percent, SkPaint& paint)
#else
void CustomPaintPaintMethod::SetContrastFilter(const std::string& percent, RSPen* pen, RSBrush* brush)
#endif
{
    float percentNum = 1.0f;
    if (!CheckNumberAndPercentage(percent, false, percentNum)) {
        return;
    }
    float matrix[20] = { 0.0f };
    matrix[0] = matrix[6] = matrix[12] = percentNum;
    matrix[4] = matrix[9] = matrix[14] = 0.5f * (1 - percentNum);
    matrix[18] = 1;
#ifndef USE_ROSEN_DRAWING
    SetColorFilter(matrix, paint);
#else
    SetColorFilter(matrix, pen, brush);
#endif
}

// https://drafts.fxtf.org/filter-effects/#blurEquivalent
#ifndef USE_ROSEN_DRAWING
void CustomPaintPaintMethod::SetBlurFilter(const std::string& percent, SkPaint& paint)
{
    float blurNum = 0.0f;
    blurNum = BlurStrToDouble(percent);
    if (Negative(blurNum)) {
        return;
    }
#ifdef NEW_SKIA
    paint.setImageFilter(SkImageFilters::Blur(blurNum, blurNum, nullptr));
#else
    paint.setImageFilter(SkBlurImageFilter::Make(blurNum, blurNum, nullptr));
#endif
}
#else
void CustomPaintPaintMethod::SetBlurFilter(const std::string& percent, RSPen* pen, RSBrush* brush)
{
    auto imageFilter = RSImageFilter::CreateBlurImageFilter(
        BlurStrToDouble(percent), BlurStrToDouble(percent), RSTileMode::DECAL, nullptr);
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
#endif

#ifndef USE_ROSEN_DRAWING
void CustomPaintPaintMethod::SetColorFilter(float matrix[20], SkPaint& paint)
#else
void CustomPaintPaintMethod::SetColorFilter(float matrix[20], RSPen* pen, RSBrush* brush)
#endif
{
#ifndef USE_ROSEN_DRAWING
#ifdef USE_SYSTEM_SKIA
    matrix[4] *= 255;
    matrix[9] *= 255;
    matrix[14] *= 255;
    matrix[19] *= 255;
    paint.setColorFilter(SkColorFilter::MakeMatrixFilterRowMajor255(matrix));
#else
    paint.setColorFilter(SkColorFilters::Matrix(matrix));
#endif
#else
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
#endif
}

bool CustomPaintPaintMethod::GetFilterType(FilterType& filterType, std::string& filterParam)
{
    std::string paramData = filterParam_;
    size_t index = paramData.find("(");
    if (index == std::string::npos) {
        return false;
    }
    filterType = FilterStrToFilterType(paramData.substr(0, index));
    filterParam = paramData.substr(index + 1);
    size_t endIndex = filterParam.find(")");
    if (endIndex  != std::string::npos) {
            filterParam.erase(endIndex, 1);
    }
    return true;
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
    for (auto i  = 0U; i < param.size() - 1; i++) {
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
    auto context = context_.Upgrade();
    CHECK_NULL_VOID(context);
    double viewScale = context->GetViewScale();
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
} // namespace OHOS::Ace::NG
