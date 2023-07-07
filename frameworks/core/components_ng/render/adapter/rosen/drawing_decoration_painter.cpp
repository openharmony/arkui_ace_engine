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
        RSColorQuad color { RSColor::COLOR_TRANSPARENT };
        float offset { 0.0f };
        bool hasValue { false };
        bool isLength { false };
    };

    explicit GradientShader(const NG::Gradient& gradient)
    {
        for (auto& stop : gradient.GetColors()) {
            ColorStop colorStop;
            colorStop.color = stop.GetColor().GetValue();
            colorStop.hasValue = stop.GetHasValue();
            if (colorStop.hasValue) {
                colorStop.isLength = stop.GetDimension().Unit() != DimensionUnit::PERCENT;
                if (colorStop.isLength) {
                    colorStop.offset = static_cast<float>(stop.GetDimension().Value());
                } else {
                    colorStop.offset = static_cast<float>(stop.GetDimension().Value() / 100.0);
                }
            }
            colorStops_.emplace_back(colorStop);
        }
        isRepeat_ = gradient.GetRepeat();
    }
    virtual ~GradientShader() = default;
    virtual std::shared_ptr<RSShaderEffect> CreateGradientShader()
    {
        return nullptr;
    }

protected:
    void AddColorStops(float gradientLength)
    {
        uint32_t colorSize = colorStops_.size();
        for (uint32_t i = 0; i < colorSize; i++) {
            auto& colorStop = colorStops_[i];
            if (colorStop.hasValue) {
                if (colorStop.isLength) {
                    // only support px and percent
                    colorStop.offset = GreatNotEqual(gradientLength, 0.0) ? colorStop.offset / gradientLength : 0.0f;
                    colorStop.hasValue = true;
                }
            } else if (i == 0) {
                // default: start with 0.0%
                colorStop.offset = 0.0f;
                colorStop.hasValue = true;
            } else if (colorSize > 1 && i == colorSize - 1) {
                // default: end with 100.0%
                colorStop.offset = 1.0f;
                colorStop.hasValue = true;
            }
            // make sure colors in increasing order
            if (colorStop.hasValue && i > 0) {
                auto prev = static_cast<int32_t>(i - 1);
                while (prev >= 0 && !colorStops_[prev].hasValue) {
                    prev--;
                }
                if (prev >= 0 && colorStop.offset < colorStops_[prev].offset) {
                    colorStop.offset = colorStops_[prev].offset;
                }
            }
        }
        AdjustNoValueColorStop();
    }

    void AdjustNoValueColorStop()
    {
        // deal with not specified color stop
        uint32_t colorSize = colorStops_.size();
        if (colorSize <= 2) {
            return;
        }
        int32_t noValueStartIndex = 0;
        bool inUnspecifiedRun = false;
        for (uint32_t i = 0; i < colorSize; ++i) {
            if (!colorStops_[i].hasValue && !inUnspecifiedRun) {
                noValueStartIndex = static_cast<int32_t>(i);
                inUnspecifiedRun = true;
            } else if (colorStops_[i].hasValue && inUnspecifiedRun) {
                auto noValueEndIndex = static_cast<int32_t>(i);
                if (noValueStartIndex < noValueEndIndex) {
                    auto beginValue = colorStops_[noValueStartIndex - 1].offset;
                    auto endValue = colorStops_[noValueEndIndex].offset;
                    auto delta = (endValue - beginValue) / static_cast<float>(noValueEndIndex - noValueStartIndex + 1);

                    for (int32_t j = noValueStartIndex; j < noValueEndIndex; ++j) {
                        colorStops_[j].offset = (beginValue + static_cast<float>(j - noValueStartIndex + 1) * delta);
                        colorStops_[j].hasValue = true;
                    }
                }
                inUnspecifiedRun = false;
            }
        }
    }

    bool NeedAdjustColorStops() const
    {
        if (colorStops_.size() < 2) {
            return false;
        }

        if (isRepeat_) {
            return true;
        }
        // not in the range of [0, 1]
        if (colorStops_.front().offset < 0.0f || colorStops_.back().offset > 1.0f) {
            return true;
        }
        return false;
    }

    void AdjustColorStops()
    {
        const auto firstOffset = colorStops_.front().offset;
        const auto lastOffset = colorStops_.back().offset;
        const float span = std::min(std::max(lastOffset - firstOffset, 0.0f), std::numeric_limits<float>::max());
        if (NearZero(span)) {
            return;
        }
        for (auto& stop : colorStops_) {
            const auto relativeOffset = std::min(stop.offset - firstOffset, std::numeric_limits<float>::max());
            const auto adjustOffset = relativeOffset / span;
            stop.offset = adjustOffset;
        }
    }

    void ToRSColors(std::vector<RSScalar>& pos, std::vector<RSColorQuad>& colors) const
    {
        if (colorStops_.empty()) {
            pos.push_back(0.0f);
            colors.push_back(RSColor::COLOR_TRANSPARENT);
        } else if (colorStops_.front().offset > 0.0f) {
            pos.push_back(0.0f);
            colors.push_back(colorStops_.front().color);
        }

        for (const auto& stop : colorStops_) {
            pos.push_back(stop.offset);
            colors.push_back(stop.color);
        }

        if (pos.back() < 1.0f) {
            pos.push_back(1.0f);
            colors.push_back(colors.back());
        }
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
        auto point = secondPoint_ - firstPoint_;
        AddColorStops(std::sqrt(std::pow(point.GetX(), 2) + std::pow(point.GetY(), 2)));
        if (NeedAdjustColorStops()) {
            auto startOffset = colorStops_.front().offset;
            auto endOffset = colorStops_.back().offset;
            AdjustColorStops();
            AdjustPoint(startOffset, endOffset);
        }

        std::vector<RSScalar> pos;
        std::vector<RSColorQuad> colors;
        ToRSColors(pos, colors);
        RSPoint pts[2] = { firstPoint_, secondPoint_ };
        RSTileMode tileMode = RSTileMode::CLAMP;
        if (isRepeat_) {
            tileMode = RSTileMode::REPEAT;
        }
        return RSShaderEffect::CreateLinearGradient(pts[0], pts[1], colors, pos, tileMode);
    }

    static std::unique_ptr<GradientShader> CreateLinearGradient(const NG::Gradient& gradient, const RSSize& size)
    {
        auto linearGradient = gradient.GetLinearGradient();
        CHECK_NULL_RETURN_NOLOG(linearGradient, nullptr);
        RSPoint firstPoint { 0.0f, 0.0f };
        RSPoint secondPoint { 0.0f, 0.0f };
        if (linearGradient->angle) {
            EndPointsFromAngle(linearGradient->angle.value().Value(), size, firstPoint, secondPoint);
        } else {
            if (linearGradient->linearX && linearGradient->linearY) {
                float width = size.Width();
                float height = size.Height();
                if (linearGradient->linearX == NG::GradientDirection::LEFT) {
                    height *= -1;
                }
                if (linearGradient->linearY == NG::GradientDirection::BOTTOM) {
                    width *= -1;
                }
                float angle = 90.0f - Rad2deg(atan2(width, height));
                EndPointsFromAngle(angle, size, firstPoint, secondPoint);
            } else if (linearGradient->linearX || linearGradient->linearY) {
                secondPoint = DirectionToPoint(linearGradient->linearX, linearGradient->linearY, size);
                if (linearGradient->linearX) {
                    firstPoint.SetX(size.Width() - secondPoint.GetX());
                }
                if (linearGradient->linearY) {
                    firstPoint.SetY(size.Height() - secondPoint.GetY());
                }
            } else {
                secondPoint = RSPoint(0.0f, size.Height());
            }
        }
        return std::make_unique<LinearGradientShader>(gradient, firstPoint, secondPoint);
    }

private:
    void AdjustPoint(float firstOffset, float lastOffset)
    {
        const auto delta = secondPoint_ - firstPoint_;
        secondPoint_ = firstPoint_ + delta * lastOffset;
        firstPoint_ = firstPoint_ + delta * firstOffset;
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
        angle = fmod(angle, 360.0f);
        if (LessNotEqual(angle, 0.0)) {
            angle += 360.0f;
        }

        if (NearEqual(angle, 0.0)) {
            firstPoint = RSPoint(0.0f, size.Height());
            secondPoint = RSPoint(0.0f, 0.0f);
            return;
        } else if (NearEqual(angle, 90.0)) {
            firstPoint = RSPoint(0.0f, 0.0f);
            secondPoint = RSPoint(size.Width(), 0.0f);
            return;
        } else if (NearEqual(angle, 180.0)) {
            firstPoint = RSPoint(0.0f, 0.0f);
            secondPoint = RSPoint(0, size.Height());
            return;
        } else if (NearEqual(angle, 270.0)) {
            firstPoint = RSPoint(size.Width(), 0.0f);
            secondPoint = RSPoint(0.0f, 0.0f);
            return;
        }
        float slope = tan(Deg2rad(90.0f - angle));
        float perpendicularSlope = -1 / slope;

        float halfHeight = size.Height() / 2;
        float halfWidth = size.Width() / 2;
        RSPoint cornerPoint { 0.0f, 0.0f };
        if (angle < 90.0) {
            cornerPoint = RSPoint(halfWidth, halfHeight);
        } else if (angle < 180) {
            cornerPoint = RSPoint(halfWidth, -halfHeight);
        } else if (angle < 270) {
            cornerPoint = RSPoint(-halfWidth, -halfHeight);
        } else {
            cornerPoint = RSPoint(-halfWidth, halfHeight);
        }

        // Compute b (of y = kx + b) using the corner point.
        float b = cornerPoint.GetY() - perpendicularSlope * cornerPoint.GetX();
        float endX = b / (slope - perpendicularSlope);
        float endY = perpendicularSlope * endX + b;

        secondPoint = RSPoint(halfWidth + endX, halfHeight - endY);
        firstPoint = RSPoint(halfWidth - endX, halfHeight + endY);
    }

    static RSPoint DirectionToPoint(
        const std::optional<GradientDirection>& x, const std::optional<GradientDirection>& y, const RSSize& size)
    {
        RSPoint point { 0.0f, 0.0f };
        if (x) {
            if (x == GradientDirection::LEFT) {
                point.SetX(0.0f);
            } else {
                point.SetX(size.Width());
            }
        }

        if (y) {
            if (y == GradientDirection::TOP) {
                point.SetY(0.0f);
            } else {
                point.SetY(size.Height());
            }
        }

        return point;
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
        RSMatrix matrix;
        ratio_ = NearZero(ratio_) ? 1.0f : ratio_;
        if (ratio_ != 1.0f) {
            matrix.Scale(1.0f, 1 / ratio_, center_.GetX(), center_.GetY());
        }
        AddColorStops(radius1_);
        if (NeedAdjustColorStops()) {
            auto startOffset = colorStops_.front().offset;
            auto endOffset = colorStops_.back().offset;
            AdjustColorStops();
            AdjustRadius(startOffset, endOffset);
        }

        RSTileMode tileMode = RSTileMode::CLAMP;
        if (isRepeat_) {
            ClampNegativeOffsets();
            tileMode = RSTileMode::REPEAT;
        }
        std::vector<RSScalar> pos;
        std::vector<RSColorQuad> colors;
        ToRSColors(pos, colors);
        radius0_ = std::max(radius0_, 0.0f);
        radius1_ = std::max(radius1_, 0.0f);
        return RSShaderEffect::CreateTwoPointConical(
            center_, radius0_, center_, radius1_, colors, pos, tileMode);
    }

    static std::unique_ptr<GradientShader> CreateRadialGradient(const NG::Gradient& gradient, const RSSize& size)
    {
        auto radialGradient = gradient.GetRadialGradient();
        if (!radialGradient) {
            return nullptr;
        }
        RSPoint center = GetCenter(radialGradient, size);
        RSSize circleSize = GetCircleSize(radialGradient, size, center);
        bool isDegenerate = NearZero(circleSize.Width()) || NearZero(circleSize.Height());
        float ratio = NearZero(circleSize.Height()) ? 1.0f : circleSize.Width() / circleSize.Height();
        float radius0 = 0.0f;
        float radius1 = circleSize.Width();
        if (isDegenerate) {
            ratio = 1.0f;
            radius1 = 0.0f;
        }
        return std::make_unique<RadialGradientShader>(gradient, center, radius0, radius1, ratio);
    }

private:
    void AdjustRadius(float firstOffset, float lastOffset)
    {
        float adjustedR0 = radius1_ * firstOffset;
        float adjustedR1 = radius1_ * lastOffset;
        if (adjustedR0 < 0.0) {
            const float radiusSpan = adjustedR1 - adjustedR0;
            const float shiftToPositive = radiusSpan * ceilf(-adjustedR0 / radiusSpan);
            adjustedR0 += shiftToPositive;
            adjustedR1 += shiftToPositive;
        }
        radius0_ = adjustedR0;
        radius1_ = adjustedR1;
    }

    void ClampNegativeOffsets()
    {
        float lastNegativeOffset = 0.0f;
        for (uint32_t i = 0; i < colorStops_.size(); ++i) {
            auto current = colorStops_[i].offset;
            if (GreatOrEqual(current, 0.0f)) {
                if (i > 0) {
                    float fraction = -lastNegativeOffset / (current - lastNegativeOffset);
                    LinearEvaluator<Color> evaluator;
                    Color adjustColor =
                        evaluator.Evaluate(Color(colorStops_[i - 1].color), Color(colorStops_[i].color), fraction);
                    colorStops_[i - 1].color = adjustColor.GetValue();
                }
                break;
            }
            colorStops_[i].offset = 0.0f;
            lastNegativeOffset = current;
        }
    }

    static RSPoint GetCenter(const std::shared_ptr<NG::RadialGradient>& radialGradient, const RSSize& size)
    {
        RSPoint center = RSPoint(size.Width() / 2.0f, size.Height() / 2.0f);
        if (radialGradient->radialCenterX) {
            const auto& value = radialGradient->radialCenterX.value();
            center.SetX(static_cast<float>(
                value.Unit() == DimensionUnit::PERCENT ? value.Value() / 100.0 * size.Width() : value.ConvertToPx()));
        }
        if (radialGradient->radialCenterY) {
            const auto& value = radialGradient->radialCenterY.value();
            center.SetY(static_cast<float>(
                value.Unit() == DimensionUnit::PERCENT ? value.Value() / 100.0 * size.Height() : value.ConvertToPx()));
        }
        return center;
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