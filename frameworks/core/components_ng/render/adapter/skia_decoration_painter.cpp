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

#include "core/components_ng/render/adapter/skia_decoration_painter.h"

#include <cmath>
#include <functional>
#include <memory>

#include "include/core/SkColor.h"
#include "include/effects/SkGradientShader.h"

#include "base/geometry/dimension.h"

namespace OHOS::Ace::NG {

namespace {
constexpr int CORNER_NUMS = 4;

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
        SkColor color { SK_ColorTRANSPARENT };
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
    virtual sk_sp<SkShader> CreateGradientShader()
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

    void ToSkColors(std::vector<SkScalar>& pos, std::vector<SkColor>& colors) const
    {
        if (colorStops_.empty()) {
            pos.push_back(0.0f);
            colors.push_back(SK_ColorTRANSPARENT);
        } else if (colorStops_.front().offset > 0.0f) {
            pos.push_back(0.0f);
            colors.push_back(SkColor(colorStops_.front().color));
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
    LinearGradientShader(const NG::Gradient& gradient, const SkPoint& firstPoint, const SkPoint& secondPoint)
        : GradientShader(gradient), firstPoint_(firstPoint), secondPoint_(secondPoint)
    {}
    ~LinearGradientShader() override = default;

    sk_sp<SkShader> CreateGradientShader() override
    {
        AddColorStops((secondPoint_ - firstPoint_).length());
        if (NeedAdjustColorStops()) {
            auto startOffset = colorStops_.front().offset;
            auto endOffset = colorStops_.back().offset;
            AdjustColorStops();
            AdjustPoint(startOffset, endOffset);
        }

        std::vector<SkScalar> pos;
        std::vector<SkColor> colors;
        ToSkColors(pos, colors);
        SkPoint pts[2] = { firstPoint_, secondPoint_ };
        SkTileMode tileMode = SkTileMode::kClamp;
        if (isRepeat_) {
            tileMode = SkTileMode::kRepeat;
        }
        return SkGradientShader::MakeLinear(pts, &colors[0], &pos[0], colors.size(), tileMode);
    }

    static std::unique_ptr<GradientShader> CreateLinearGradient(const NG::Gradient& gradient, const SkSize& size)
    {
        auto linearGradient = gradient.GetLinearGradient();
        if (!linearGradient) {
            return nullptr;
        }
        SkPoint firstPoint { 0.0f, 0.0f };
        SkPoint secondPoint { 0.0f, 0.0f };
        if (linearGradient->angle) {
            EndPointsFromAngle(linearGradient->angle.value().Value(), size, firstPoint, secondPoint);
        } else {
            if (linearGradient->linearX && linearGradient->linearY) {
                float width = size.width();
                float height = size.height();
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
                    firstPoint.fX = size.width() - secondPoint.x();
                }
                if (linearGradient->linearY) {
                    firstPoint.fY = size.height() - secondPoint.y();
                }
            } else {
                secondPoint.set(0.0f, size.height());
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

    static void EndPointsFromAngle(float angle, const SkSize& size, SkPoint& firstPoint, SkPoint& secondPoint)
    {
        angle = fmod(angle, 360.0f);
        if (LessNotEqual(angle, 0.0)) {
            angle += 360.0f;
        }

        if (NearEqual(angle, 0.0)) {
            firstPoint.set(0.0f, size.height());
            secondPoint.set(0.0f, 0.0f);
            return;
        } else if (NearEqual(angle, 90.0)) {
            firstPoint.set(0.0f, 0.0f);
            secondPoint.set(size.width(), 0.0f);
            return;
        } else if (NearEqual(angle, 180.0)) {
            firstPoint.set(0.0f, 0.0f);
            secondPoint.set(0, size.height());
            return;
        } else if (NearEqual(angle, 270.0)) {
            firstPoint.set(size.width(), 0.0f);
            secondPoint.set(0.0f, 0.0f);
            return;
        }
        float slope = tan(Deg2rad(90.0f - angle));
        float perpendicularSlope = -1 / slope;

        float halfHeight = size.height() / 2;
        float halfWidth = size.width() / 2;
        SkPoint cornerPoint { 0.0f, 0.0f };
        if (angle < 90.0) {
            cornerPoint.set(halfWidth, halfHeight);
        } else if (angle < 180) {
            cornerPoint.set(halfWidth, -halfHeight);
        } else if (angle < 270) {
            cornerPoint.set(-halfWidth, -halfHeight);
        } else {
            cornerPoint.set(-halfWidth, halfHeight);
        }

        // Compute b (of y = kx + b) using the corner point.
        float b = cornerPoint.y() - perpendicularSlope * cornerPoint.x();
        float endX = b / (slope - perpendicularSlope);
        float endY = perpendicularSlope * endX + b;

        secondPoint.set(halfWidth + endX, halfHeight - endY);
        firstPoint.set(halfWidth - endX, halfHeight + endY);
    }

    static SkPoint DirectionToPoint(
        const std::optional<GradientDirection>& x, const std::optional<GradientDirection>& y, const SkSize& size)
    {
        SkPoint point { 0.0f, 0.0f };
        if (x) {
            if (x == GradientDirection::LEFT) {
                point.fX = 0.0f;
            } else {
                point.fX = size.width();
            }
        }

        if (y) {
            if (y == GradientDirection::TOP) {
                point.fY = 0.0f;
            } else {
                point.fY = size.height();
            }
        }

        return point;
    }

private:
    SkPoint firstPoint_ { 0.0f, 0.0f };
    SkPoint secondPoint_ { 0.0f, 0.0f };
};

class RadialGradientShader final : public GradientShader {
public:
    RadialGradientShader(const NG::Gradient& gradient, const SkPoint& center, float radius0, float radius1, float ratio)
        : GradientShader(gradient), center_(center), radius0_(radius0), radius1_(radius1), ratio_(ratio)
    {}

    ~RadialGradientShader() override = default;

    sk_sp<SkShader> CreateGradientShader() override
    {
        SkMatrix matrix = SkMatrix::I();
        ratio_ = NearZero(ratio_) ? 1.0f : ratio_;
        if (ratio_ != 1.0f) {
            matrix.preScale(1.0f, 1 / ratio_, center_.x(), center_.y());
        }
        AddColorStops(radius1_);
        if (NeedAdjustColorStops()) {
            auto startOffset = colorStops_.front().offset;
            auto endOffset = colorStops_.back().offset;
            AdjustColorStops();
            AdjustRadius(startOffset, endOffset);
        }

        SkTileMode tileMode = SkTileMode::kClamp;
        if (isRepeat_) {
            ClampNegativeOffsets();
            tileMode = SkTileMode::kRepeat;
        }
        std::vector<SkScalar> pos;
        std::vector<SkColor> colors;
        ToSkColors(pos, colors);
        radius0_ = std::max(radius0_, 0.0f);
        radius1_ = std::max(radius1_, 0.0f);
        return SkGradientShader::MakeTwoPointConical(
            center_, radius0_, center_, radius1_, &colors[0], &pos[0], colors.size(), tileMode, 0, &matrix);
    }

    static std::unique_ptr<GradientShader> CreateRadialGradient(const NG::Gradient& gradient, const SkSize& size)
    {
        auto radialGradient = gradient.GetRadialGradient();
        if (!radialGradient) {
            return nullptr;
        }
        SkPoint center = GetCenter(radialGradient, size);
        SkSize circleSize = GetCircleSize(radialGradient, size, center);
        bool isDegenerate = NearZero(circleSize.width()) || NearZero(circleSize.height());
        float ratio = NearZero(circleSize.height()) ? 1.0f : circleSize.width() / circleSize.height();
        float radius0 = 0.0f;
        float radius1 = circleSize.width();
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

    static SkPoint GetCenter(const std::shared_ptr<NG::RadialGradient>& radialGradient, const SkSize& size)
    {
        SkPoint center = SkPoint::Make(size.width() / 2.0f, size.height() / 2.0f);
        if (radialGradient->radialCenterX) {
            const auto& value = radialGradient->radialCenterX.value();
            center.fX = static_cast<float>(value.Unit() == DimensionUnit::PERCENT ? value.Value() / 100.0 * size.width()
                                                                                  : value.ConvertToPx());
        }
        if (radialGradient->radialCenterY) {
            const auto& value = radialGradient->radialCenterY.value();
            center.fY =
                static_cast<float>(value.Unit() == DimensionUnit::PERCENT ? value.Value() / 100.0 * size.height()
                                                                          : value.ConvertToPx());
        }
        return center;
    }

    static SkSize GetCircleSize(
        const std::shared_ptr<NG::RadialGradient>& radialGradient, const SkSize& size, const SkPoint& center)
    {
        SkSize circleSize { 0.0f, 0.0f };
        if (radialGradient->radialHorizontalSize) {
            const auto& hValue = radialGradient->radialHorizontalSize.value();
            circleSize.fWidth = static_cast<float>(
                hValue.Unit() == DimensionUnit::PERCENT ? hValue.Value() * size.width() : hValue.ConvertToPx());
            circleSize.fHeight = circleSize.fWidth;
            if (radialGradient->radialVerticalSize) {
                const auto& wValue = radialGradient->radialVerticalSize.value();
                circleSize.fHeight =
                    static_cast<float>(wValue.Unit() == DimensionUnit::PERCENT ? wValue.Value() * size.height()
                                                                               : wValue.ConvertToPx());
            }
        } else {
            RadialShapeType shape = NG::RadialShapeType::ELLIPSE;
            if ((radialGradient->radialShape && radialGradient->radialShape.value() == NG::RadialShapeType::CIRCLE) ||
                (!radialGradient->radialShape && !radialGradient->radialSizeType
                 && radialGradient->radialHorizontalSize &&!radialGradient->radialVerticalSize)) {
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

    static SkSize RadiusToSide(
        const SkPoint& center, const SkSize& size, NG::RadialShapeType type, const CompareType& compare)
    {
        auto dx1 = static_cast<float>(std::fabs(center.fX));
        auto dy1 = static_cast<float>(std::fabs(center.fY));
        auto dx2 = static_cast<float>(std::fabs(center.fX - size.width()));
        auto dy2 = static_cast<float>(std::fabs(center.fY - size.height()));

        auto dx = compare(dx1, dx2) ? dx1 : dx2;
        auto dy = compare(dy1, dy2) ? dy1 : dy2;

        if (type == NG::RadialShapeType::CIRCLE) {
            return compare(dx, dy) ? SkSize::Make(dx, dx) : SkSize::Make(dy, dy);
        }
        return SkSize::Make(dx, dy);
    }

    static inline SkSize EllipseRadius(const SkPoint& p, float ratio)
    {
        if (NearZero(ratio) || std::isinf(ratio)) {
            return SkSize { 0.0f, 0.0f };
        }
        // x^2/a^2 + y^2/b^2 = 1
        // a/b = ratio, b = a/ratio
        // a = sqrt(x^2 + y^2/(1/r^2))
        float a = sqrtf(p.fX * p.fX + p.fY * p.fY * ratio * ratio);
        return SkSize::Make(a, a / ratio);
    }

    static SkSize RadiusToCorner(
        const SkPoint& center, const SkSize& size, NG::RadialShapeType type, const CompareType& compare)
    {
        const SkPoint corners[4] = {
            SkPoint::Make(0.0f, 0.0f),
            SkPoint::Make(size.width(), 0.0f),
            SkPoint::Make(size.width(), size.height()),
            SkPoint::Make(0.0f, size.height()),
        };

        int32_t cornerIndex = 0;
        float distance = (center - corners[cornerIndex]).length();
        for (int32_t i = 1; i < CORNER_NUMS; i++) {
            float newDistance = (center - corners[i]).length();
            if (compare(newDistance, distance)) {
                cornerIndex = i;
                distance = newDistance;
            }
        }

        if (type == NG::RadialShapeType::CIRCLE) {
            return SkSize::Make(distance, distance);
        }

        SkSize sideRadius = RadiusToSide(center, size, NG::RadialShapeType::ELLIPSE, compare);
        return EllipseRadius(corners[cornerIndex] - center,
            NearZero(sideRadius.height()) ? 1.0f : sideRadius.width() / sideRadius.height());
    }

private:
    SkPoint center_ { 0.0f, 0.0f };
    float radius0_ { 0.0f };
    float radius1_ { 0.0f };
    float ratio_ { 1.0f };
};

class SweepGradientShader final : public GradientShader {
public:
    SweepGradientShader(
        const NG::Gradient& gradient, const SkPoint& center, float startAngle, float endAngle, float rotation)
        : GradientShader(gradient), center_(center), startAngle_(startAngle), endAngle_(endAngle), rotation_(rotation)
    {}
    ~SweepGradientShader() override = default;

    sk_sp<SkShader> CreateGradientShader() override
    {
        AddColorStops(1.0f);
        if (NeedAdjustColorStops()) {
            auto startOffset = colorStops_.front().offset;
            auto endOffset = colorStops_.back().offset;
            AdjustColorStops();
            AdjustAngle(startOffset, endOffset);
        }

        SkMatrix matrix = SkMatrix::I();
        if (!NearZero(rotation_)) {
            matrix.preRotate(rotation_, center_.fX, center_.fY);
        }

        std::vector<SkScalar> pos;
        std::vector<SkColor> colors;
        ToSkColors(pos, colors);
        SkTileMode tileMode = SkTileMode::kClamp;
        if (isRepeat_) {
            tileMode = SkTileMode::kRepeat;
        }
        return SkGradientShader::MakeSweep(
            center_.fX, center_.fY, &colors[0], &pos[0], colors.size(), tileMode, startAngle_, endAngle_, 0, &matrix);
    }

    static std::unique_ptr<GradientShader> CreateSweepGradient(
        const NG::Gradient& gradient, const SkSize& size)
    {
        auto sweepGradient = gradient.GetSweepGradient();
        if (!sweepGradient) {
            return nullptr;
        }
        SkPoint center = GetCenter(sweepGradient, size);
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
    static SkPoint GetCenter(const std::shared_ptr<NG::SweepGradient>& sweepGradient, const SkSize& size)
    {
        SkPoint center = SkPoint::Make(size.width() / 2.0f, size.height() / 2.0f);

        if (sweepGradient->centerX) {
            const auto& value = sweepGradient->centerX.value();
            center.fX =
                static_cast<float>(value.Unit() == DimensionUnit::PERCENT ? value.Value() / 100.0f * size.width()
                                                                          : value.ConvertToPx());
        }
        if (sweepGradient->centerY) {
            const auto& value = sweepGradient->centerY.value();
            center.fY =
                static_cast<float>(value.Unit() == DimensionUnit::PERCENT ? value.Value() / 100.0f * size.height()
                                                                          : value.ConvertToPx());
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
    SkPoint center_ { 0.0f, 0.0f };
    float startAngle_ { 0.0f };
    float endAngle_ { 0.0f };
    float rotation_ { 0.0f };
};

} // namespace

sk_sp<SkShader> SkiaDecorationPainter::CreateGradientShader(
    const NG::Gradient& gradient, const SizeF& frameSize)
{
    auto ptr = std::make_unique<GradientShader>(gradient);
    auto size = SkSize::Make(frameSize.Width(), frameSize.Height());
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

} // namespace OHOS::Ace::NG