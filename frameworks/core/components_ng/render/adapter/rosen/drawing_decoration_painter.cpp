/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/render/adapter/rosen/drawing_decoration_painter.h"

#include <cmath>
#include <functional>
#include <memory>

#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/utils/utils.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_ng/render/drawing_prop_convertor.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t CORNER_NUMS = 4;
constexpr uint32_t COLOR_MASK = 0xff000000;

template<typename T>
class Evaluator : public AceType {
public:
    virtual T Evaluate(const T& begin, const T& end, float fraction) = 0;
};

template<typename T>
class LinearEvaluator : public Evaluator<T> {
public:
    LinearEvaluator() = default;

    ~LinearEvaluator() override = default;

    T Evaluate(const T& begin, const T& end, float fraction) override
    {
        return begin + (end - begin) * fraction;
    }
};

class GradientShader {
public:
    struct ColorStop {
    };

    explicit GradientShader(const NG::Gradient& gradient)
    {
    }
    virtual ~GradientShader() = default;
    virtual std::shared_ptr<RSShaderEffect> CreateGradientShader()
    {
        return nullptr;
    }

protected:
    void AddColorStops(float gradientLength)
    {
    }

    void AdjustNoValueColorStop()
    {
    }

    bool NeedAdjustColorStops() const
    {
    }

    void AdjustColorStops()
    {
    }

    void ToRSColors(std::vector<RSScalar>& pos, std::vector<RSColorQuad>& colors) const
    {
    }

protected:
    std::vector<ColorStop> colorStops_;
    bool isRepeat_ { false };
};

class LinearGradientShader final : public GradientShader {
public:
    LinearGradientShader(const NG::Gradient& gradient, const RSPoint& firstPoint, const RSPoint& secondPoint)
        : GradientShader(gradient), firstPoint_(firstPoint), secondPoint_(secondPoint)
    {}
    ~LinearGradientShader() override = default;

    std::shared_ptr<RSShaderEffect> CreateGradientShader() override
    {
    }

    static std::unique_ptr<GradientShader> CreateLinearGradient(const NG::Gradient& gradient, const RSSize& size)
    {
    }

private:
    void AdjustPoint(float firstOffset, float lastOffset)
    {
    }

    static float Deg2rad(float deg)
    {
        return static_cast<float>(deg * M_PI / 180.0);
    }

    static float Rad2deg(float rad)
    {
        return static_cast<float>(rad * 180.0 / M_PI);
    }

    static void EndPointsFromAngle(float angle, const RSSize& size, RSPoint& firstPoint, RSPoint& secondPoint)
    {
    }

    static RSPoint DirectionToPoint(
        const std::optional<GradientDirection>& x, const std::optional<GradientDirection>& y, const RSSize& size)
    {
    }

private:
    RSPoint firstPoint_ { 0.0f, 0.0f };
    RSPoint secondPoint_ { 0.0f, 0.0f };
};

class RadialGradientShader final : public GradientShader {
public:
    RadialGradientShader(const NG::Gradient& gradient, const RSPoint& center, float radius0, float radius1, float ratio)
        : GradientShader(gradient), center_(center), radius0_(radius0), radius1_(radius1), ratio_(ratio)
    {}

    ~RadialGradientShader() override = default;

    std::shared_ptr<RSShaderEffect> CreateGradientShader() override
    {
    }

    static std::unique_ptr<GradientShader> CreateRadialGradient(const NG::Gradient& gradient, const RSSize& size)
    {
    }

private:
    void AdjustRadius(float firstOffset, float lastOffset)
    {
    }

    void ClampNegativeOffsets()
    {
    }

    static RSPoint GetCenter(const std::shared_ptr<NG::RadialGradient>& radialGradient, const RSSize& size)
    {
    }

    static RSSize GetCircleSize(
        const std::shared_ptr<NG::RadialGradient>& radialGradient, const RSSize& size, const RSPoint& center)
    {
    }

    using CompareType = std::function<bool(float, float)>;

    static RSSize RadiusToSide(
        const RSPoint& center, const RSSize& size, NG::RadialShapeType type, const CompareType& compare)
    {
    }

    static inline RSSize EllipseRadius(const RSPoint& p, float ratio)
    {
    }

    static RSSize RadiusToCorner(
        const RSPoint& center, const RSSize& size, NG::RadialShapeType type, const CompareType& compare)
    {
    }

private:
    RSPoint center_ { 0.0f, 0.0f };
    float radius0_ { 0.0f };
    float radius1_ { 0.0f };
    float ratio_ { 1.0f };
};

class SweepGradientShader final : public GradientShader {
public:
    SweepGradientShader(
        const NG::Gradient& gradient, const RSPoint& center, float startAngle, float endAngle, float rotation)
        : GradientShader(gradient), center_(center), startAngle_(startAngle), endAngle_(endAngle), rotation_(rotation)
    {}
    ~SweepGradientShader() override = default;

    std::shared_ptr<RSShaderEffect> CreateGradientShader() override
    {
    }

    static std::unique_ptr<GradientShader> CreateSweepGradient(const NG::Gradient& gradient, const RSSize& size)
    {
    }

private:
    static RSPoint GetCenter(const std::shared_ptr<NG::SweepGradient>& sweepGradient, const RSSize& size)
    {
    }

    void AdjustAngle(float firstOffset, float lastOffset)
    {
    }

private:
    RSPoint center_ { 0.0f, 0.0f };
    float startAngle_ { 0.0f };
    float endAngle_ { 0.0f };
    float rotation_ { 0.0f };
};
} // namespace

std::shared_ptr<RSShaderEffect> DrawingDecorationPainter::CreateGradientShader(
    const NG::Gradient& gradient, const SizeF& frameSize)
{
}

float DrawingDecorationPainter::DrawingDimensionToPx(const Dimension& value, const SizeF& size, LengthMode type)
{
}

float DrawingDecorationPainter::DrawingGetFloatRadiusValue(
    const Dimension& src, const Dimension& dest, const SizeF& size, LengthMode type)
{
}

RSPath DrawingDecorationPainter::DrawingCreatePath(const RefPtr<BasicShape>& basicShape, const SizeF& size)
{
}

void DrawingDecorationPainter::DrawingCreateInset(
    const RefPtr<BasicShape>& basicShape, const SizeF& size, const OffsetF& position, RSPath& rsPath)
{
}

void DrawingDecorationPainter::DrawingCreateCircle(
    const RefPtr<BasicShape>& basicShape, const SizeF& size, const OffsetF& position, RSPath& rsPath)
{
}

void DrawingDecorationPainter::DrawingCreateEllipse(
    const RefPtr<BasicShape>& basicShape, const SizeF& size, const OffsetF& position, RSPath& rsPath)
{
}

void DrawingDecorationPainter::DrawingCreatePolygon(
    const RefPtr<BasicShape>& basicShape, const SizeF& size, const OffsetF& position, RSPath& rsPath)
{
}

void DrawingDecorationPainter::DrawingCreatePath(
    const RefPtr<BasicShape>& basicShape, const SizeF& size, const OffsetF& position, RSPath& rsPath)
{
}

void DrawingDecorationPainter::DrawingCreateRect(
    const RefPtr<BasicShape>& basicShape, const SizeF& size, const OffsetF& position, RSPath& rsPath)
{
    const auto& rect = AceType::DynamicCast<ShapeRect>(basicShape);
    CHECK_NULL_VOID(rect);
    double left = DrawingDimensionToPx(rect->GetOffset().GetX(), size, LengthMode::HORIZONTAL) + position.GetX();
    double top = DrawingDimensionToPx(rect->GetOffset().GetY(), size, LengthMode::VERTICAL) + position.GetY();
    double width = DrawingDimensionToPx(rect->GetWidth(), size, LengthMode::HORIZONTAL);
    double height = DrawingDimensionToPx(rect->GetHeight(), size, LengthMode::VERTICAL);
    RSRect rsRect = RSRect(left, top, left + width, top + height);
    auto radiusSize = SizeF(width, height);
    float topLeftRadiusX = DrawingGetFloatRadiusValue(
        rect->GetTopLeftRadius().GetX(), rect->GetTopLeftRadius().GetY(), radiusSize, LengthMode::HORIZONTAL);
    float topLeftRadiusY = DrawingGetFloatRadiusValue(
        rect->GetTopLeftRadius().GetY(), rect->GetTopLeftRadius().GetX(), radiusSize, LengthMode::VERTICAL);
    float topRightRadiusX = DrawingGetFloatRadiusValue(
        rect->GetTopRightRadius().GetX(), rect->GetTopRightRadius().GetY(), radiusSize, LengthMode::HORIZONTAL);
    float topRightRadiusY = DrawingGetFloatRadiusValue(
        rect->GetTopRightRadius().GetY(), rect->GetTopRightRadius().GetX(), radiusSize, LengthMode::VERTICAL);
    float bottomRightRadiusX = DrawingGetFloatRadiusValue(
        rect->GetBottomRightRadius().GetX(), rect->GetBottomRightRadius().GetY(), radiusSize, LengthMode::HORIZONTAL);
    float bottomRightRadiusY = DrawingGetFloatRadiusValue(
        rect->GetBottomRightRadius().GetY(), rect->GetBottomRightRadius().GetX(), radiusSize, LengthMode::VERTICAL);
    float bottomLeftRadiusX = DrawingGetFloatRadiusValue(
        rect->GetBottomLeftRadius().GetX(), rect->GetBottomLeftRadius().GetY(), radiusSize, LengthMode::HORIZONTAL);
    float bottomLeftRadiusY = DrawingGetFloatRadiusValue(
        rect->GetBottomLeftRadius().GetY(), rect->GetBottomLeftRadius().GetX(), radiusSize, LengthMode::VERTICAL);
    std::vector<RSPoint> fRadii = { { topLeftRadiusX, topLeftRadiusY }, { topRightRadiusX, topRightRadiusY },
        { bottomRightRadiusX, bottomRightRadiusY }, { bottomLeftRadiusX, bottomLeftRadiusY } };
    RSRoundRect roundRect(rsRect, fRadii);
    rsPath.AddRoundRect(roundRect);
}

void DrawingDecorationPainter::PaintGrayScale(const RSRoundRect& rRect, RSCanvas* canvas, float scale)
{
    if (GreatNotEqual(scale, 0.0)) {
        if (canvas) {
            RSAutoCanvasRestore acr(*canvas, true);
            canvas->ClipRoundRect(rRect, RSClipOp::INTERSECT, true);
            RSBrush brush;
            brush.SetAntiAlias(true);
            float matrix[20] = { 0.0f };
            matrix[0] = matrix[5] = matrix[10] = 0.2126f * scale;
            matrix[1] = matrix[6] = matrix[11] = 0.7152f * scale;
            matrix[2] = matrix[7] = matrix[12] = 0.0722f * scale;
            matrix[18] = 1.0f * scale;
            RSColorMatrix colorMatrix;
            colorMatrix.SetArray(matrix);
            RSFilter filter;
            filter.SetColorFilter(RSColorFilter::CreateMatrixColorFilter(colorMatrix));
            brush.SetFilter(filter);
            RSSaveLayerOps slr(nullptr, &brush, RSSaveLayerOps::Flags::INIT_WITH_PREVIOUS);
            canvas->SaveLayer(slr);
        }
    }
}

void DrawingDecorationPainter::PaintBrightness(const RSRoundRect& rRect, RSCanvas* canvas, float bright)
{
    // brightness range = (0, 2)
    // skip painting when brightness is normal
    CHECK_NULL_VOID_NOLOG(!NearEqual(bright, 1.0));
    if (canvas) {
        RSAutoCanvasRestore acr(*canvas, true);
        canvas->ClipRoundRect(rRect, RSClipOp::INTERSECT, true);
        RSBrush brush;
        brush.SetAntiAlias(true);
        float matrix[20] = { 0.0f };
        // shift brightness to (-1, 1)
        bright = bright - 1;
        matrix[0] = matrix[6] = matrix[12] = matrix[18] = 1.0f;
        matrix[4] = matrix[9] = matrix[14] = bright;
        RSColorMatrix colorMatrix;
        colorMatrix.SetArray(matrix);
        RSFilter filter;
        filter.SetColorFilter(RSColorFilter::CreateMatrixColorFilter(colorMatrix));
        brush.SetFilter(filter);
        RSSaveLayerOps slr(nullptr, &brush, RSSaveLayerOps::Flags::INIT_WITH_PREVIOUS);
        canvas->SaveLayer(slr);
    }
}

void DrawingDecorationPainter::PaintContrast(const RSRoundRect& rRect, RSCanvas* canvas, float contrasts)
{
    // skip painting if contrast is normal
    CHECK_NULL_VOID_NOLOG(!NearEqual(contrasts, 1.0));
    if (canvas) {
        RSAutoCanvasRestore acr(*canvas, true);
        canvas->ClipRoundRect(rRect, RSClipOp::INTERSECT, true);
        RSBrush brush;
        brush.SetAntiAlias(true);
        float matrix[20] = { 0.0f };
        matrix[0] = matrix[6] = matrix[12] = contrasts;
        matrix[4] = matrix[9] = matrix[14] = 128 * (1 - contrasts) / 255;
        matrix[18] = 1.0f;
        RSColorMatrix colorMatrix;
        colorMatrix.SetArray(matrix);
        RSFilter filter;
        filter.SetColorFilter(RSColorFilter::CreateMatrixColorFilter(colorMatrix));
        brush.SetFilter(filter);
        RSSaveLayerOps slr(nullptr, &brush, RSSaveLayerOps::Flags::INIT_WITH_PREVIOUS);
        canvas->SaveLayer(slr);
    }
}

void DrawingDecorationPainter::PaintColorBlend(const RSRoundRect& rRect, RSCanvas* canvas, const Color& colorBlend)
{
    if (colorBlend.GetValue() != COLOR_MASK) {
        if (canvas) {
            RSAutoCanvasRestore acr(*canvas, true);
            canvas->ClipRoundRect(rRect, RSClipOp::INTERSECT, true);
            RSBrush brush;
            brush.SetAntiAlias(true);
            RSFilter filter;
            filter.SetColorFilter(RSColorFilter::CreateBlendModeColorFilter(RSColor::ColorQuadSetARGB(
                colorBlend.GetRed(), colorBlend.GetGreen(), colorBlend.GetBlue(), colorBlend.GetAlpha()),
                RSBlendMode::PLUS));
            brush.SetFilter(filter);
            RSSaveLayerOps slr(nullptr, &brush, RSSaveLayerOps::Flags::INIT_WITH_PREVIOUS);
            canvas->SaveLayer(slr);
        }
    }
}

void DrawingDecorationPainter::PaintSaturate(const RSRoundRect& rRect, RSCanvas* canvas, float saturates)
{
    if (!NearEqual(saturates, 1.0) && GreatOrEqual(saturates, 0.0)) {
        if (canvas) {
            RSAutoCanvasRestore acr(*canvas, true);
            canvas->ClipRoundRect(rRect, RSClipOp::INTERSECT, true);
            RSBrush brush;
            brush.SetAntiAlias(true);
            float matrix[20] = { 0.0f };
            matrix[0] = 0.3086f * (1 - saturates) + saturates;
            matrix[1] = matrix[11] = 0.6094f * (1 - saturates);
            matrix[2] = matrix[7] = 0.0820f * (1 - saturates);
            matrix[5] = matrix[10] = 0.3086f * (1 - saturates);
            matrix[6] = 0.6094f * (1 - saturates) + saturates;
            matrix[12] = 0.0820f * (1 - saturates) + saturates;
            matrix[18] = 1.0f;
            RSColorMatrix colorMatrix;
            colorMatrix.SetArray(matrix);
            RSFilter filter;
            filter.SetColorFilter(RSColorFilter::CreateMatrixColorFilter(colorMatrix));
            brush.SetFilter(filter);
            RSSaveLayerOps slr(nullptr, &brush, RSSaveLayerOps::Flags::INIT_WITH_PREVIOUS);
            canvas->SaveLayer(slr);
        }
    }
}

void DrawingDecorationPainter::PaintSepia(const RSRoundRect& rRect, RSCanvas* canvas, float sepias)
{
    if (sepias > 1.0) {
        sepias = 1.0;
    }
    if (GreatNotEqual(sepias, 0.0)) {
        if (canvas) {
            RSAutoCanvasRestore acr(*canvas, true);
            canvas->ClipRoundRect(rRect, RSClipOp::INTERSECT, true);
            RSBrush brush;
            brush.SetAntiAlias(true);
            float matrix[20] = { 0.0f };
            matrix[0] = 0.393f * sepias;
            matrix[1] = 0.769f * sepias;
            matrix[2] = 0.189f * sepias;

            matrix[5] = 0.349f * sepias;
            matrix[6] = 0.686f * sepias;
            matrix[7] = 0.168f * sepias;

            matrix[10] = 0.272f * sepias;
            matrix[11] = 0.534f * sepias;
            matrix[12] = 0.131f * sepias;
            matrix[18] = 1.0f * sepias;
            RSColorMatrix colorMatrix;
            colorMatrix.SetArray(matrix);
            RSFilter filter;
            filter.SetColorFilter(RSColorFilter::CreateMatrixColorFilter(colorMatrix));
            brush.SetFilter(filter);
            RSSaveLayerOps slr(nullptr, &brush, RSSaveLayerOps::Flags::INIT_WITH_PREVIOUS);
            canvas->SaveLayer(slr);
        }
    }
}

void DrawingDecorationPainter::PaintInvert(const RSRoundRect& rRect, RSCanvas* canvas, float inverts)
{
    if (GreatNotEqual(inverts, 0.0)) {
        if (canvas) {
            RSAutoCanvasRestore acr(*canvas, true);
            canvas->ClipRoundRect(rRect, RSClipOp::INTERSECT, true);
            RSBrush brush;
            brush.SetAntiAlias(true);
            float matrix[20] = { 0.0f };
            if (inverts > 1.0) {
                inverts = 1.0;
            }
            // complete color invert when dstRGB = 1 - srcRGB
            // map (0, 1) to (1, -1)
            matrix[0] = matrix[6] = matrix[12] = 1.0 - 2.0 * inverts;
            matrix[18] = 1.0f;
            // inverts = 0.5 -> RGB = (0.5, 0.5, 0.5) -> image completely gray
            matrix[4] = matrix[9] = matrix[14] = inverts;
            RSColorMatrix colorMatrix;
            colorMatrix.SetArray(matrix);
            RSFilter filter;
            filter.SetColorFilter(RSColorFilter::CreateMatrixColorFilter(colorMatrix));
            brush.SetFilter(filter);
            RSSaveLayerOps slr(nullptr, &brush, RSSaveLayerOps::Flags::INIT_WITH_PREVIOUS);
            canvas->SaveLayer(slr);
        }
    }
}

void DrawingDecorationPainter::PaintHueRotate(const RSRoundRect& rRect, RSCanvas* canvas, float hueRotate)
{
    if (GreatNotEqual(hueRotate, 0.0)) {
        if (canvas) {
            RSAutoCanvasRestore acr(*canvas, true);
            canvas->ClipRoundRect(rRect, RSClipOp::INTERSECT, true);
            RSBrush brush;
            brush.SetAntiAlias(true);
            while (GreatOrEqual(hueRotate, 360)) {
                hueRotate -= 360;
            }
            float matrix[20] = { 0.0f };
            int32_t type = hueRotate / 120;
            float N = (hueRotate - 120 * type) / 120;
            switch (type) {
                case 0:
                    // color change = R->G, G->B, B->R
                    matrix[2] = matrix[5] = matrix[11] = N;
                    matrix[0] = matrix[6] = matrix[12] = 1 - N;
                    matrix[18] = 1.0f;
                    break;
                case 1:
                    // compare to original: R->B, G->R, B->G
                    matrix[1] = matrix[7] = matrix[10] = N;
                    matrix[2] = matrix[5] = matrix[11] = 1 - N;
                    matrix[18] = 1.0f;
                    break;
                case 2:
                    // back to normal color
                    matrix[0] = matrix[6] = matrix[12] = N;
                    matrix[1] = matrix[7] = matrix[10] = 1 - N;
                    matrix[18] = 1.0f;
                    break;
                default:
                    break;
            }
            RSColorMatrix colorMatrix;
            colorMatrix.SetArray(matrix);
            RSFilter filter;
            filter.SetColorFilter(RSColorFilter::CreateMatrixColorFilter(colorMatrix));
            brush.SetFilter(filter);
            RSSaveLayerOps slr(nullptr, &brush, RSSaveLayerOps::Flags::INIT_WITH_PREVIOUS);
            canvas->SaveLayer(slr);
        }
    }
}

RSBrush DrawingDecorationPainter::CreateMaskDrawingBrush(const RefPtr<BasicShape>& basicShape)
{
    RSBrush brush;
    brush.SetAntiAlias(true);
    brush.SetColor(basicShape->GetColor().GetValue());
    return brush;
}

RSImage DrawingDecorationPainter::CreateBorderImageGradient(const NG::Gradient& gradient, const SizeF& paintSize)
{
    auto shader = DrawingDecorationPainter::CreateGradientShader(gradient, paintSize);
    RSBrush brush;
    brush.SetAntiAlias(true);
    brush.SetShaderEffect(std::move(shader));

    RSBitmapFormat format { RSColorType::COLORTYPE_RGBA_8888, RSAlphaType::ALPHATYPE_OPAQUE };
    RSBitmap rsBitmap;
    rsBitmap.Build(paintSize.Width(), paintSize.Height(), format);

    auto canvas = std::make_unique<RSCanvas>();
    canvas->Bind(rsBitmap);
    canvas->DrawBackground(brush);
    RSImage rsImage;
    rsImage.BuildFromBitmap(rsBitmap);
    return rsImage;
}
} // namespace OHOS::Ace::NG