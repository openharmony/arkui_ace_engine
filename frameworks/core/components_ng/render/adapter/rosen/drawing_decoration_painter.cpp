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
}

void DrawingDecorationPainter::PaintGrayScale(const RSRoundRect& rRect, RSCanvas* canvas, float scale)
{
}

void DrawingDecorationPainter::PaintBrightness(const RSRoundRect& rRect, RSCanvas* canvas, float bright)
{
}

void DrawingDecorationPainter::PaintContrast(const RSRoundRect& rRect, RSCanvas* canvas, float contrasts)
{
}

void DrawingDecorationPainter::PaintColorBlend(const RSRoundRect& rRect, RSCanvas* canvas, const Color& colorBlend)
{
}

void DrawingDecorationPainter::PaintSaturate(const RSRoundRect& rRect, RSCanvas* canvas, float saturates)
{
}

void DrawingDecorationPainter::PaintSepia(const RSRoundRect& rRect, RSCanvas* canvas, float sepias)
{
}

void DrawingDecorationPainter::PaintInvert(const RSRoundRect& rRect, RSCanvas* canvas, float inverts)
{
}

void DrawingDecorationPainter::PaintHueRotate(const RSRoundRect& rRect, RSCanvas* canvas, float hueRotate)
{
}

RSBrush DrawingDecorationPainter::CreateMaskDrawingBrush(const RefPtr<BasicShape>& basicShape)
{
}

RSImage DrawingDecorationPainter::CreateBorderImageGradient(const NG::Gradient& gradient, const SizeF& paintSize)
{
}
} // namespace OHOS::Ace::NG