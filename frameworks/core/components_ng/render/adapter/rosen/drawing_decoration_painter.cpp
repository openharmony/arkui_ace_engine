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
        RSSize circleSize { 0.0f, 0.0f };
        if (radialGradient->radialHorizontalSize) {
            const auto& hValue = radialGradient->radialHorizontalSize.value();
            circleSize.SetWidth(static_cast<float>(
                hValue.Unit() == DimensionUnit::PERCENT ? hValue.Value() * size.Width() : hValue.ConvertToPx()));
            circleSize.SetHeight(circleSize.Width());
            if (radialGradient->radialVerticalSize) {
                const auto& wValue = radialGradient->radialVerticalSize.value();
                circleSize.SetHeight(static_cast<float>(
                    wValue.Unit() == DimensionUnit::PERCENT ? wValue.Value() * size.Height() : wValue.ConvertToPx()));
            }
        } else {
            RadialShapeType shape = NG::RadialShapeType::ELLIPSE;
            if ((radialGradient->radialShape && radialGradient->radialShape.value() == NG::RadialShapeType::CIRCLE) ||
                (!radialGradient->radialShape && !radialGradient->radialSizeType &&
                    radialGradient->radialHorizontalSize && !radialGradient->radialVerticalSize)) {
                shape = NG::RadialShapeType::CIRCLE;
            }
            auto sizeType =
                radialGradient->radialSizeType ? radialGradient->radialSizeType.value() : NG::RadialSizeType::NONE;
            switch (sizeType) {
                case NG::RadialSizeType::CLOSEST_SIDE:
                    circleSize = RadiusToSide(center, size, shape, std::less<>());
                    break;
                case NG::RadialSizeType::FARTHEST_SIDE:
                    circleSize = RadiusToSide(center, size, shape, std::greater<>());
                    break;
                case NG::RadialSizeType::CLOSEST_CORNER:
                    circleSize = RadiusToCorner(center, size, shape, std::less<>());
                    break;
                case NG::RadialSizeType::FARTHEST_CORNER:
                case NG::RadialSizeType::NONE:
                default:
                    circleSize = RadiusToCorner(center, size, shape, std::greater<>());
                    break;
            }
        }
        return circleSize;
    }

    using CompareType = std::function<bool(float, float)>;

    static RSSize RadiusToSide(
        const RSPoint& center, const RSSize& size, NG::RadialShapeType type, const CompareType& compare)
    {
        auto dx1 = static_cast<float>(std::fabs(center.GetX()));
        auto dy1 = static_cast<float>(std::fabs(center.GetY()));
        auto dx2 = static_cast<float>(std::fabs(center.GetX() - size.Width()));
        auto dy2 = static_cast<float>(std::fabs(center.GetY() - size.Height()));

        auto dx = compare(dx1, dx2) ? dx1 : dx2;
        auto dy = compare(dy1, dy2) ? dy1 : dy2;

        if (type == NG::RadialShapeType::CIRCLE) {
            return compare(dx, dy) ? RSSize(dx, dx) : RSSize(dy, dy);
        }
        return RSSize(dx, dy);
    }

    static inline RSSize EllipseRadius(const RSPoint& p, float ratio)
    {
        if (NearZero(ratio) || std::isinf(ratio)) {
            return RSSize { 0.0f, 0.0f };
        }
        // x^2/a^2 + y^2/b^2 = 1
        // a/b = ratio, b = a/ratio
        // a = sqrt(x^2 + y^2/(1/r^2))
        float a = sqrtf(p.GetX() * p.GetX() + p.GetY() * p.GetY() * ratio * ratio);
        return RSSize(a, a / ratio);
    }

    static RSSize RadiusToCorner(
        const RSPoint& center, const RSSize& size, NG::RadialShapeType type, const CompareType& compare)
    {
        const RSPoint corners[4] = {
            RSPoint(0.0f, 0.0f),
            RSPoint(size.Width(), 0.0f),
            RSPoint(size.Width(), size.Height()),
            RSPoint(0.0f, size.Height()),
        };

        int32_t cornerIndex = 0;
        auto point = center - corners[cornerIndex];
        float distance = std::sqrt(std::pow(point.GetX(), 2) + std::pow(point.GetY(), 2));
        for (int32_t i = 1; i < CORNER_NUMS; i++) {
            point = center - corners[i];
            float newDistance = std::sqrt(std::pow(point.GetX(), 2) + std::pow(point.GetY(), 2));
            if (compare(newDistance, distance)) {
                cornerIndex = i;
                distance = newDistance;
            }
        }

        if (type == NG::RadialShapeType::CIRCLE) {
            return RSSize(distance, distance);
        }

        RSSize sideRadius = RadiusToSide(center, size, NG::RadialShapeType::ELLIPSE, compare);
        return EllipseRadius(corners[cornerIndex] - center,
            NearZero(sideRadius.Height()) ? 1.0f : sideRadius.Width() / sideRadius.Height());
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
        AddColorStops(1.0f);
        if (NeedAdjustColorStops()) {
            auto startOffset = colorStops_.front().offset;
            auto endOffset = colorStops_.back().offset;
            AdjustColorStops();
            AdjustAngle(startOffset, endOffset);
        }

        RSMatrix matrix;
        if (!NearZero(rotation_)) {
            matrix.Rotate(rotation_, center_.GetX(), center_.GetY());
        }

        std::vector<RSScalar> pos;
        std::vector<RSColorQuad> colors;
        ToRSColors(pos, colors);
        RSTileMode tileMode = RSTileMode::CLAMP;
        if (isRepeat_) {
            tileMode = RSTileMode::REPEAT;
        }
        return RSShaderEffect::CreateSweepGradient(center_, colors, pos, tileMode, startAngle_, endAngle_);
    }

    static std::unique_ptr<GradientShader> CreateSweepGradient(const NG::Gradient& gradient, const RSSize& size)
    {
        auto sweepGradient = gradient.GetSweepGradient();
        CHECK_NULL_RETURN_NOLOG(sweepGradient, nullptr);
        RSPoint center = GetCenter(sweepGradient, size);
        float rotationAngle = 0.0f;
        if (sweepGradient->rotation) {
            rotationAngle = fmod(sweepGradient->rotation.value().Value(), 360.0f);
            if (LessNotEqual(rotationAngle, 0.0f)) {
                rotationAngle += 360.0f;
            }
        }
        float startAngle = 0.0f;
        float endAngle = 0.0f;
        if (sweepGradient->startAngle.has_value()) {
            startAngle = sweepGradient->startAngle.value().Value();
        }
        if (sweepGradient->endAngle.has_value()) {
            endAngle = sweepGradient->endAngle.value().Value();
        }
        return std::make_unique<NG::SweepGradientShader>(gradient, center, startAngle, endAngle, rotationAngle);
    }

private:
    static RSPoint GetCenter(const std::shared_ptr<NG::SweepGradient>& sweepGradient, const RSSize& size)
    {
        RSPoint center = RSPoint(size.Width() / 2.0f, size.Height() / 2.0f);

        if (sweepGradient->centerX) {
            const auto& value = sweepGradient->centerX.value();
            center.SetX(static_cast<float>(
                value.Unit() == DimensionUnit::PERCENT ? value.Value() / 100.0f * size.Width() : value.ConvertToPx()));
        }
        if (sweepGradient->centerY) {
            const auto& value = sweepGradient->centerY.value();
            center.SetY(static_cast<float>(
                value.Unit() == DimensionUnit::PERCENT ? value.Value() / 100.0f * size.Height() : value.ConvertToPx()));
        }
        return center;
    }

    void AdjustAngle(float firstOffset, float lastOffset)
    {
        const auto delta = endAngle_ - startAngle_;
        endAngle_ = startAngle_ + delta * lastOffset;
        startAngle_ = startAngle_ + delta * firstOffset;
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
    auto ptr = std::make_unique<GradientShader>(gradient);
    auto size = RSSize(frameSize.Width(), frameSize.Height());
    switch (gradient.GetType()) {
        case NG::GradientType::LINEAR:
            ptr = LinearGradientShader::CreateLinearGradient(gradient, size);
            break;
        case NG::GradientType::RADIAL:
            ptr = RadialGradientShader::CreateRadialGradient(gradient, size);
            break;
        case NG::GradientType::SWEEP:
            ptr = SweepGradientShader::CreateSweepGradient(gradient, size);
            break;
        default:
            LOGE("unsupported gradient type.");
            break;
    }
    return ptr->CreateGradientShader();
}

float DrawingDecorationPainter::DrawingDimensionToPx(const Dimension& value, const SizeF& size, LengthMode type)
{
    if (value.Unit() == DimensionUnit::PERCENT) {
        switch (type) {
            case LengthMode::HORIZONTAL:
                return ConvertToPx(value, ScaleProperty::CreateScaleProperty(), size.Width()).value();
            case LengthMode::VERTICAL:
                return ConvertToPx(value, ScaleProperty::CreateScaleProperty(), size.Height()).value();
            case LengthMode::OTHER:
                return ConvertToPx(value, ScaleProperty::CreateScaleProperty(), sqrt(size.Width() * size.Height()))
                    .value();
            default:
                return 0.0f;
        }
    } else {
        return static_cast<float>(value.ConvertToPx());
    }
}

float DrawingDecorationPainter::DrawingGetFloatRadiusValue(
    const Dimension& src, const Dimension& dest, const SizeF& size, LengthMode type)
{
    if (src.Value() < 0.0 && dest.Value() > 0.0) {
        return DrawingDimensionToPx(dest, size, type);
    }
    return DrawingDimensionToPx(src, size, type);
}

RSPath DrawingDecorationPainter::DrawingCreatePath(const RefPtr<BasicShape>& basicShape, const SizeF& size)
{
    OffsetF position;
    RSPath rsPath;
    if (basicShape == nullptr) {
        rsPath.AddRect(RSRect(0.0, 0.0, size.Width(), size.Height()));
        return rsPath;
    }
    float offsetX = DrawingDimensionToPx(basicShape->GetPosition().GetX(), size, LengthMode::HORIZONTAL);
    float offsetY = DrawingDimensionToPx(basicShape->GetPosition().GetY(), size, LengthMode::VERTICAL);
    position += OffsetF(offsetX, offsetY);
    switch (basicShape->GetBasicShapeType()) {
        case BasicShapeType::INSET: {
            DrawingCreateInset(basicShape, size, position, rsPath);
            break;
        }
        case BasicShapeType::CIRCLE: {
            DrawingCreateCircle(basicShape, size, position, rsPath);
            break;
        }
        case BasicShapeType::ELLIPSE: {
            DrawingCreateEllipse(basicShape, size, position, rsPath);
            break;
        }
        case BasicShapeType::POLYGON: {
            DrawingCreatePolygon(basicShape, size, position, rsPath);
            break;
        }
        case BasicShapeType::PATH: {
            DrawingCreatePath(basicShape, size, position, rsPath);
            break;
        }
        case BasicShapeType::RECT: {
            DrawingCreateRect(basicShape, size, position, rsPath);
            break;
        }
        default: {
            LOGE("invalid BasicShapeType");
            break;
        }
    }
    return rsPath;
}

void DrawingDecorationPainter::DrawingCreateInset(
    const RefPtr<BasicShape>& basicShape, const SizeF& size, const OffsetF& position, RSPath& rsPath)
{
    const auto& inset = AceType::DynamicCast<Inset>(basicShape);
    CHECK_NULL_VOID(inset);
    double left = DrawingDimensionToPx(inset->GetLeft(), size, LengthMode::HORIZONTAL) + position.GetX();
    double top = DrawingDimensionToPx(inset->GetTop(), size, LengthMode::VERTICAL) + position.GetY();
    double right = size.Width() - DrawingDimensionToPx(inset->GetRight(), size, LengthMode::HORIZONTAL) + position.GetX();
    double bottom =
        size.Height() - DrawingDimensionToPx(inset->GetBottom(), size, LengthMode::VERTICAL) + position.GetY();
    RSRect rect(left, top, right, bottom);
    auto radiusSize = SizeF(std::abs(rect.GetWidth()), std::abs(rect.GetHeight()));
    float topLeftRadiusX = DrawingDimensionToPx(inset->GetTopLeftRadius().GetX(), radiusSize, LengthMode::HORIZONTAL);
    float topLeftRadiusY = DrawingDimensionToPx(inset->GetTopLeftRadius().GetY(), radiusSize, LengthMode::VERTICAL);
    float topRightRadiusX = DrawingDimensionToPx(inset->GetTopRightRadius().GetX(), radiusSize, LengthMode::HORIZONTAL);
    float topRightRadiusY = DrawingDimensionToPx(inset->GetTopRightRadius().GetY(), radiusSize, LengthMode::VERTICAL);
    float bottomRightRadiusX =
        DrawingDimensionToPx(inset->GetBottomRightRadius().GetX(), radiusSize, LengthMode::HORIZONTAL);
    float bottomRightRadiusY =
        DrawingDimensionToPx(inset->GetBottomRightRadius().GetY(), radiusSize, LengthMode::VERTICAL);
    float bottomLeftRadiusX =
        DrawingDimensionToPx(inset->GetBottomLeftRadius().GetX(), radiusSize, LengthMode::HORIZONTAL);
    float bottomLeftRadiusY = DrawingDimensionToPx(inset->GetBottomLeftRadius().GetY(), radiusSize, LengthMode::VERTICAL);
    std::vector<RSPoint> fRadii = { { topLeftRadiusX, topLeftRadiusY }, { topRightRadiusX, topRightRadiusY },
        { bottomRightRadiusX, bottomRightRadiusY }, { bottomLeftRadiusX, bottomLeftRadiusY } };
    RSRoundRect roundRect(rect, fRadii);
    rsPath.AddRoundRect(roundRect);
}

void DrawingDecorationPainter::DrawingCreateCircle(
    const RefPtr<BasicShape>& basicShape, const SizeF& size, const OffsetF& position, RSPath& rsPath)
{
    const auto& circle = AceType::DynamicCast<Circle>(basicShape);
    CHECK_NULL_VOID(circle);
    if (circle->GetRadius().IsValid()) {
        rsPath.AddCircle(DrawingDimensionToPx(circle->GetAxisX(), size, LengthMode::HORIZONTAL) + position.GetX(),
            DrawingDimensionToPx(circle->GetAxisY(), size, LengthMode::VERTICAL) + position.GetY(),
            DrawingDimensionToPx(circle->GetRadius(), size, LengthMode::OTHER));
    } else {
        float width = DrawingDimensionToPx(circle->GetWidth(), size, LengthMode::HORIZONTAL);
        float height = DrawingDimensionToPx(circle->GetHeight(), size, LengthMode::VERTICAL);
        float offsetX = DrawingDimensionToPx(circle->GetOffset().GetX(), size, LengthMode::HORIZONTAL) + position.GetX();
        float offsetY = DrawingDimensionToPx(circle->GetOffset().GetY(), size, LengthMode::VERTICAL) + position.GetY();
        rsPath.AddCircle(width * 0.5 + offsetX, height * 0.5 + offsetY, std::min(width, height) * 0.5);
    }
}

void DrawingDecorationPainter::DrawingCreateEllipse(
    const RefPtr<BasicShape>& basicShape, const SizeF& size, const OffsetF& position, RSPath& rsPath)
{
    const auto& ellipse = AceType::DynamicCast<Ellipse>(basicShape);
    CHECK_NULL_VOID(ellipse);
    if (ellipse->GetRadiusX().IsValid()) {
        float rx = DrawingDimensionToPx(ellipse->GetRadiusX(), size, LengthMode::HORIZONTAL);
        float ry = DrawingDimensionToPx(ellipse->GetRadiusY(), size, LengthMode::VERTICAL);
        double x = DrawingDimensionToPx(ellipse->GetAxisX(), size, LengthMode::HORIZONTAL) + position.GetX() - rx;
        double y = DrawingDimensionToPx(ellipse->GetAxisY(), size, LengthMode::VERTICAL) + position.GetY() - ry;
        RSRect rect = RSRect(x, y, x + rx + rx, y + ry + ry);
        rsPath.AddOval(rect);
    } else {
        auto width = DrawingDimensionToPx(ellipse->GetWidth(), size, LengthMode::HORIZONTAL);
        auto height = DrawingDimensionToPx(ellipse->GetHeight(), size, LengthMode::VERTICAL);
        float x = DrawingDimensionToPx(ellipse->GetOffset().GetX(), size, LengthMode::HORIZONTAL) + position.GetX();
        float y = DrawingDimensionToPx(ellipse->GetOffset().GetY(), size, LengthMode::VERTICAL) + position.GetY();
        RSRect rect = RSRect(x, y, x + width, y + height);
        rsPath.AddOval(rect);
    }
}

void DrawingDecorationPainter::DrawingCreatePolygon(
    const RefPtr<BasicShape>& basicShape, const SizeF& size, const OffsetF& position, RSPath& rsPath)
{
    const auto& polygon = AceType::DynamicCast<Polygon>(basicShape);
    CHECK_NULL_VOID(polygon);
    std::vector<RSPoint> rsPoints;
    for (auto [x, y] : polygon->GetPoints()) {
        rsPoints.emplace_back(RSPoint(DrawingDimensionToPx(x, size, LengthMode::HORIZONTAL) + position.GetX(),
            DrawingDimensionToPx(y, size, LengthMode::VERTICAL) + position.GetX()));
    }
    if (rsPoints.empty()) {
        LOGW("points is null");
        return;
    }
    rsPath.AddPoly(rsPoints, rsPoints.size(), true);
}

void DrawingDecorationPainter::DrawingCreatePath(
    const RefPtr<BasicShape>& basicShape, const SizeF& size, const OffsetF& position, RSPath& rsPath)
{
    const auto& path = AceType::DynamicCast<Path>(basicShape);
    CHECK_NULL_VOID(path);
    if (path->GetValue().empty()) {
        LOGW("path value is null");
        return;
    }
    RSPath tmpPath;
    if (!tmpPath.BuildFromSVGString(path->GetValue().c_str())) {
        LOGW("path value is invalid");
        return;
    }
    float offsetX = DrawingDimensionToPx(path->GetOffset().GetX(), size, LengthMode::HORIZONTAL) + position.GetX();
    float offsetY = DrawingDimensionToPx(path->GetOffset().GetY(), size, LengthMode::VERTICAL) + position.GetY();
    rsPath.AddPath(tmpPath, offsetX, offsetY);
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