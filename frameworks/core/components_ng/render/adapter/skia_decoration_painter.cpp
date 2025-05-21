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
#include "include/core/SkColorFilter.h"
#include "include/core/SkImage.h"
#include "include/core/SkRRect.h"
#include "include/core/SkScalar.h"
#include "include/effects/SkGradientShader.h"
#include "include/utils/SkParsePath.h"

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
constexpr double RIGHT_ANGLE_D = 90.0;
constexpr float RIGHT_ANGLE_F = 90.0f;
constexpr int32_t STRAIGHT_ANGLE = 180;
constexpr double STRAIGHT_ANGLE_D = 180.0;
constexpr int32_t REFLEX_ANGLE = 270;
constexpr double REFLEX_ANGLE_D = 270.0;
constexpr int32_t FULL_ROTATION_F = 360;
constexpr double FULL_ROTATION_F = 360.0f;
constexpr int32_t MIN_COLOR_STOPS = 2;
constexpr int32_t MIN_COLOR_SIZE = 2;
constexpr uint32_t COLOR_MASK_ALPHA = 0xFF000000;
constexpr uint32_t COLOR_MASK_RED = 0x00FF0000;
constexpr uint32_t COLOR_MASK_GREEN = 0x0000FF00;
constexpr uint32_t COLOR_MASK_BLUE = 0x000000FF;
constexpr float COLOR_DIVISOR = 255.0f;
constexpr uint32_t ALPHA_SHIFT = 24;
constexpr uint32_t RED_SHIFT = 16;
constexpr uint32_t GREEN_SHIFT = 8;

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
        if (colorSize <= MIN_COLOR_SIZE) {
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
        if (colorStops_.size() < MIN_COLOR_STOPS) {
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

    static SKColor4f SkColorToSKColor4f(SkColor color)
    {
        uint32_t alpha = (color & COLOR_MASK_ALPHA) >> ALPHA_SHIFT;
        uint32_t red = (color & COLOR_MASK_RED) >> RED_SHIFT;
        uint32_t green = (color & COLOR_MASK_GREEN) >> GREEN_SHIFT;
        uint32_t blue = color & COLOR_MASK_BLUE;
        RSColor4f color4f;
        color4f.alphaF_ = alpha / COLOR_DIVISOR;
        color4f.redF_ = red / COLOR_DIVISOR;
        color4f.greenF_ = green / COLOR_DIVISOR;
        color4f.blueF_ = blue / COLOR_DIVISOR;
        return color4f;
    }

    void ToSKColor4fVector(std::vector<SkScalar>& pos, std::vector<SKColor4f>& color4fs) const
    {
        if (colorStops_.empty()) {
            pos.push_back(0.0f);
            color4fs.push_back(SkColorToSKColor4f(SK_Color::TRANSPARENT));
        } else if (colorStops_.front().offset > 0.0f) {
            pos.push_back(0.0f);
            color4fs.push_back(SkColorToSKColor4f(SkColor(colorStops_.front().color)));
        }

        for (const auto& stop : colorStops_) {
            pos.push_back(stop.offset);
            color4fs.push_back(SkColorToSKColor4f(stop.color));
        }

        if (pos.back() < 1.0f) {
            pos.push_back(1.0f);
            color4fs.push_back(color4fs.back());
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
        CHECK_NULL_RETURN(linearGradient, nullptr);
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
                float angle = RIGHT_ANGLE_F - Rad2deg(atan2(width, height));
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
        return static_cast<float>(deg * M_PI / STRAIGHT_ANGLE_D);
    }

    static float Rad2deg(float rad)
    {
        return static_cast<float>(rad * STRAIGHT_ANGLE_D / M_PI);
    }

    static void EndPointsFromAngle(float angle, const SkSize& size, SkPoint& firstPoint, SkPoint& secondPoint)
    {
        angle = fmod(angle, FULL_ROTATION_F);
        if (LessNotEqual(angle, 0.0)) {
            angle += FULL_ROTATION_F;
        }

        if (NearEqual(angle, 0.0)) {
            firstPoint.set(0.0f, size.height());
            secondPoint.set(0.0f, 0.0f);
            return;
        } else if (NearEqual(angle, RIGHT_ANGLE_D)) {
            firstPoint.set(0.0f, 0.0f);
            secondPoint.set(size.width(), 0.0f);
            return;
        } else if (NearEqual(angle, STRAIGHT_ANGLE_D)) {
            firstPoint.set(0.0f, 0.0f);
            secondPoint.set(0, size.height());
            return;
        } else if (NearEqual(angle, REFLEX_ANGLE_D)) {
            firstPoint.set(size.width(), 0.0f);
            secondPoint.set(0.0f, 0.0f);
            return;
        }
        float slope = tan(Deg2rad(RIGHT_ANGLE_F - angle));
        float perpendicularSlope = -1 / slope;

        float halfHeight = size.height() / 2;
        float halfWidth = size.width() / 2;
        SkPoint cornerPoint { 0.0f, 0.0f };
        if (angle < RIGHT_ANGLE_D) {
            cornerPoint.set(halfWidth, halfHeight);
        } else if (angle < STRAIGHT_ANGLE) {
            cornerPoint.set(halfWidth, -halfHeight);
        } else if (angle < REFLEX_ANGLE) {
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
            center.fX = static_cast<float>(
                value.Unit() == DimensionUnit::PERCENT ? value.Value() / 100.0 * size.width() : value.ConvertToPx());
        }
        if (radialGradient->radialCenterY) {
            const auto& value = radialGradient->radialCenterY.value();
            center.fY = static_cast<float>(
                value.Unit() == DimensionUnit::PERCENT ? value.Value() / 100.0 * size.height() : value.ConvertToPx());
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
                circleSize.fHeight = static_cast<float>(
                    wValue.Unit() == DimensionUnit::PERCENT ? wValue.Value() * size.height() : wValue.ConvertToPx());
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
        std::vector<SKColor4f> color4fs;
        sk_sp<SkColorSpace> colorSpace = SkColorSpace::MakeSRGB();
        if (!colorStops_.empty()) {
            if (ColorSpace::DISPLAY_P3 == colorStops_.front().colorSpace) {
                colorSpace = SkColorSpace::MakeRGB(
                    Rosen::Drawing::CMSTransferFuncType::SRGB, Rosen::Drawing::CMSMatrixType::DCIP3);
            } else {
                colorSpace = SkColorSpace::MakeRGB(
                    Rosen::Drawing::CMSTransferFuncType::SRGB, Rosen::Drawing::CMSMatrixType::SRGB);
            }
        }
        ToSKColor4fVector(pos, color4fs);
        SkTileMode tileMode = SkTileMode::kClamp;
        if (isRepeat_) {
            tileMode = SkTileMode::kRepeat;
        }
        return SkGradientShader::MakeSweep(center_.fX, center_.fY, &color4fs[0], colorSpace,
            &pos[0], color4fs.size(), tileMode, startAngle_, endAngle_, 0, &matrix);
    }

    static std::unique_ptr<GradientShader> CreateSweepGradient(const NG::Gradient& gradient, const SkSize& size)
    {
        auto sweepGradient = gradient.GetSweepGradient();
        CHECK_NULL_RETURN(sweepGradient, nullptr);
        SkPoint center = GetCenter(sweepGradient, size);
        float rotationAngle = 0.0f;
        if (sweepGradient->rotation) {
            rotationAngle = fmod(sweepGradient->rotation.value().Value(), FULL_ROTATION_F);
            if (LessNotEqual(rotationAngle, 0.0f)) {
                rotationAngle += FULL_ROTATION_F;
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
        if (startAngle > endAngle) {
            return nullptr;
        }
        return std::make_unique<NG::SweepGradientShader>(gradient, center, startAngle, endAngle, rotationAngle);
    }

private:
    static SkPoint GetCenter(const std::shared_ptr<NG::SweepGradient>& sweepGradient, const SkSize& size)
    {
        SkPoint center = SkPoint::Make(size.width() / 2.0f, size.height() / 2.0f);

        if (sweepGradient->centerX) {
            const auto& value = sweepGradient->centerX.value();
            center.fX = static_cast<float>(
                value.Unit() == DimensionUnit::PERCENT ? value.Value() / 100.0f * size.width() : value.ConvertToPx());
        }
        if (sweepGradient->centerY) {
            const auto& value = sweepGradient->centerY.value();
            center.fY = static_cast<float>(
                value.Unit() == DimensionUnit::PERCENT ? value.Value() / 100.0f * size.height() : value.ConvertToPx());
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

sk_sp<SkShader> SkiaDecorationPainter::CreateGradientShader(const NG::Gradient& gradient, const SizeF& frameSize)
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
    if (!ptr) {
        return nullptr;
    }
    return ptr->CreateGradientShader();
}

float SkiaDecorationPainter::SkiaDimensionToPx(const Dimension& value, const SizeF& size, LengthMode type)
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

float SkiaDecorationPainter::SkiaGetFloatRadiusValue(
    const Dimension& src, const Dimension& dest, const SizeF& size, LengthMode type)
{
    if (src.Value() < 0.0 && dest.Value() > 0.0) {
        return SkiaDimensionToPx(dest, size, type);
    }
    return SkiaDimensionToPx(src, size, type);
}

SkPath SkiaDecorationPainter::SkiaCreateSkPath(const RefPtr<BasicShape>& basicShape, const SizeF& size)
{
    OffsetF position;
    SkPath skPath;
    if (basicShape == nullptr || basicShape->GetBasicShapeType() == BasicShapeType::NONE) {
        skPath.addRect(SkRect::MakeXYWH(0.0, 0.0, size.Width(), size.Height()));
        return skPath;
    }
    float offsetX = SkiaDimensionToPx(basicShape->GetPosition().GetX(), size, LengthMode::HORIZONTAL);
    float offsetY = SkiaDimensionToPx(basicShape->GetPosition().GetY(), size, LengthMode::VERTICAL);
    position += OffsetF(offsetX, offsetY);
    switch (basicShape->GetBasicShapeType()) {
        case BasicShapeType::INSET: {
            SkiaCreateInset(basicShape, size, position, skPath);
            break;
        }
        case BasicShapeType::CIRCLE: {
            SkiaCreateCircle(basicShape, size, position, skPath);
            break;
        }
        case BasicShapeType::ELLIPSE: {
            SkiaCreateEllipse(basicShape, size, position, skPath);
            break;
        }
        case BasicShapeType::POLYGON: {
            SkiaCreatePolygon(basicShape, size, position, skPath);
            break;
        }
        case BasicShapeType::PATH: {
            SkiaCreatePath(basicShape, size, position, skPath);
            break;
        }
        case BasicShapeType::RECT: {
            SkiaCreateRect(basicShape, size, position, skPath);
            break;
        }
        default: {
            LOGE("invalid BasicShapeType");
            break;
        }
    }
    return skPath;
}

void SkiaDecorationPainter::SkiaCreateInset(
    const RefPtr<BasicShape>& basicShape, const SizeF& size, const OffsetF& position, SkPath& skPath)
{
    const auto& inset = AceType::DynamicCast<Inset>(basicShape);
    CHECK_NULL_VOID(inset);
    double left = SkiaDimensionToPx(inset->GetLeft(), size, LengthMode::HORIZONTAL) + position.GetX();
    double top = SkiaDimensionToPx(inset->GetTop(), size, LengthMode::VERTICAL) + position.GetY();
    double right = size.Width() - SkiaDimensionToPx(inset->GetRight(), size, LengthMode::HORIZONTAL) + position.GetX();
    double bottom = size.Height() - SkiaDimensionToPx(inset->GetBottom(), size, LengthMode::VERTICAL) + position.GetY();
    SkRect rect = SkRect::MakeLTRB(left, top, right, bottom);
    auto radiusSize = SizeF(std::abs(rect.width()), std::abs(rect.height()));
    float topLeftRadiusX = SkiaDimensionToPx(inset->GetTopLeftRadius().GetX(), radiusSize, LengthMode::HORIZONTAL);
    float topLeftRadiusY = SkiaDimensionToPx(inset->GetTopLeftRadius().GetY(), radiusSize, LengthMode::VERTICAL);
    float topRightRadiusX = SkiaDimensionToPx(inset->GetTopRightRadius().GetX(), radiusSize, LengthMode::HORIZONTAL);
    float topRightRadiusY = SkiaDimensionToPx(inset->GetTopRightRadius().GetY(), radiusSize, LengthMode::VERTICAL);
    float bottomRightRadiusX =
        SkiaDimensionToPx(inset->GetBottomRightRadius().GetX(), radiusSize, LengthMode::HORIZONTAL);
    float bottomRightRadiusY =
        SkiaDimensionToPx(inset->GetBottomRightRadius().GetY(), radiusSize, LengthMode::VERTICAL);
    float bottomLeftRadiusX =
        SkiaDimensionToPx(inset->GetBottomLeftRadius().GetX(), radiusSize, LengthMode::HORIZONTAL);
    float bottomLeftRadiusY = SkiaDimensionToPx(inset->GetBottomLeftRadius().GetY(), radiusSize, LengthMode::VERTICAL);
    const SkVector fRadii[4] = { { topLeftRadiusX, topLeftRadiusY }, { topRightRadiusX, topRightRadiusY },
        { bottomRightRadiusX, bottomRightRadiusY }, { bottomLeftRadiusX, bottomLeftRadiusY } };
    SkRRect roundRect;
    roundRect.setRectRadii(rect, fRadii);
    skPath.addRRect(roundRect);
}

void SkiaDecorationPainter::SkiaCreateCircle(
    const RefPtr<BasicShape>& basicShape, const SizeF& size, const OffsetF& position, SkPath& skPath)
{
    const auto& circle = AceType::DynamicCast<Circle>(basicShape);
    CHECK_NULL_VOID(circle);
    if (circle->GetRadius().IsValid()) {
        skPath.addCircle(SkiaDimensionToPx(circle->GetAxisX(), size, LengthMode::HORIZONTAL) + position.GetX(),
            SkiaDimensionToPx(circle->GetAxisY(), size, LengthMode::VERTICAL) + position.GetY(),
            SkiaDimensionToPx(circle->GetRadius(), size, LengthMode::OTHER));
    } else {
        float width = SkiaDimensionToPx(circle->GetWidth(), size, LengthMode::HORIZONTAL);
        float height = SkiaDimensionToPx(circle->GetHeight(), size, LengthMode::VERTICAL);
        float offsetX = SkiaDimensionToPx(circle->GetOffset().GetX(), size, LengthMode::HORIZONTAL) + position.GetX();
        float offsetY = SkiaDimensionToPx(circle->GetOffset().GetY(), size, LengthMode::VERTICAL) + position.GetY();
        skPath.addCircle(width * 0.5 + offsetX, height * 0.5 + offsetY, std::min(width, height) * 0.5);
    }
}

void SkiaDecorationPainter::SkiaCreateEllipse(
    const RefPtr<BasicShape>& basicShape, const SizeF& size, const OffsetF& position, SkPath& skPath)
{
    const auto& ellipse = AceType::DynamicCast<Ellipse>(basicShape);
    CHECK_NULL_VOID(ellipse);
    if (ellipse->GetRadiusX().IsValid()) {
        float rx = SkiaDimensionToPx(ellipse->GetRadiusX(), size, LengthMode::HORIZONTAL);
        float ry = SkiaDimensionToPx(ellipse->GetRadiusY(), size, LengthMode::VERTICAL);
        double x = SkiaDimensionToPx(ellipse->GetAxisX(), size, LengthMode::HORIZONTAL) + position.GetX() - rx;
        double y = SkiaDimensionToPx(ellipse->GetAxisY(), size, LengthMode::VERTICAL) + position.GetY() - ry;
        SkRect rect = SkRect::MakeXYWH(x, y, rx + rx, ry + ry);
        skPath.addOval(rect);
    } else {
        auto width = SkiaDimensionToPx(ellipse->GetWidth(), size, LengthMode::HORIZONTAL);
        auto height = SkiaDimensionToPx(ellipse->GetHeight(), size, LengthMode::VERTICAL);
        float x = SkiaDimensionToPx(ellipse->GetOffset().GetX(), size, LengthMode::HORIZONTAL) + position.GetX();
        float y = SkiaDimensionToPx(ellipse->GetOffset().GetY(), size, LengthMode::VERTICAL) + position.GetY();
        SkRect rect = SkRect::MakeXYWH(x, y, width, height);
        skPath.addOval(rect);
    }
}

void SkiaDecorationPainter::SkiaCreatePolygon(
    const RefPtr<BasicShape>& basicShape, const SizeF& size, const OffsetF& position, SkPath& skPath)
{
    const auto& polygon = AceType::DynamicCast<Polygon>(basicShape);
    CHECK_NULL_VOID(polygon);
    std::vector<SkPoint> skPoints;
    for (auto [x, y] : polygon->GetPoints()) {
        skPoints.emplace_back(SkPoint::Make(SkiaDimensionToPx(x, size, LengthMode::HORIZONTAL) + position.GetX(),
            SkiaDimensionToPx(y, size, LengthMode::VERTICAL) + position.GetX()));
    }
    if (skPoints.empty()) {
        LOGW("points is null");
        return;
    }
    skPath.addPoly(&skPoints[0], skPoints.size(), true);
}

void SkiaDecorationPainter::SkiaCreatePath(
    const RefPtr<BasicShape>& basicShape, const SizeF& size, const OffsetF& position, SkPath& skPath)
{
    const auto& path = AceType::DynamicCast<Path>(basicShape);
    CHECK_NULL_VOID(path);
    if (path->GetValue().empty()) {
        LOGW("path value is null");
        return;
    }
    SkPath tmpPath;
    bool ret = SkParsePath::FromSVGString(path->GetValue().c_str(), &tmpPath);
    if (!ret) {
        LOGW("path value is invalid");
        return;
    }
    float offsetX = SkiaDimensionToPx(path->GetOffset().GetX(), size, LengthMode::HORIZONTAL) + position.GetX();
    float offsetY = SkiaDimensionToPx(path->GetOffset().GetY(), size, LengthMode::VERTICAL) + position.GetY();
    skPath.addPath(tmpPath, offsetX, offsetY);
}

void SkiaDecorationPainter::SkiaCreateRect(
    const RefPtr<BasicShape>& basicShape, const SizeF& size, const OffsetF& position, SkPath& skPath)
{
    const auto& rect = AceType::DynamicCast<ShapeRect>(basicShape);
    CHECK_NULL_VOID(rect);
    double left = SkiaDimensionToPx(rect->GetOffset().GetX(), size, LengthMode::HORIZONTAL) + position.GetX();
    double top = SkiaDimensionToPx(rect->GetOffset().GetY(), size, LengthMode::VERTICAL) + position.GetY();
    double width = SkiaDimensionToPx(rect->GetWidth(), size, LengthMode::HORIZONTAL);
    double height = SkiaDimensionToPx(rect->GetHeight(), size, LengthMode::VERTICAL);
    SkRect skRect = SkRect::MakeXYWH(left, top, width, height);
    auto radiusSize = SizeF(width, height);
    float topLeftRadiusX = SkiaGetFloatRadiusValue(
        rect->GetTopLeftRadius().GetX(), rect->GetTopLeftRadius().GetY(), radiusSize, LengthMode::HORIZONTAL);
    float topLeftRadiusY = SkiaGetFloatRadiusValue(
        rect->GetTopLeftRadius().GetY(), rect->GetTopLeftRadius().GetX(), radiusSize, LengthMode::VERTICAL);
    float topRightRadiusX = SkiaGetFloatRadiusValue(
        rect->GetTopRightRadius().GetX(), rect->GetTopRightRadius().GetY(), radiusSize, LengthMode::HORIZONTAL);
    float topRightRadiusY = SkiaGetFloatRadiusValue(
        rect->GetTopRightRadius().GetY(), rect->GetTopRightRadius().GetX(), radiusSize, LengthMode::VERTICAL);
    float bottomRightRadiusX = SkiaGetFloatRadiusValue(
        rect->GetBottomRightRadius().GetX(), rect->GetBottomRightRadius().GetY(), radiusSize, LengthMode::HORIZONTAL);
    float bottomRightRadiusY = SkiaGetFloatRadiusValue(
        rect->GetBottomRightRadius().GetY(), rect->GetBottomRightRadius().GetX(), radiusSize, LengthMode::VERTICAL);
    float bottomLeftRadiusX = SkiaGetFloatRadiusValue(
        rect->GetBottomLeftRadius().GetX(), rect->GetBottomLeftRadius().GetY(), radiusSize, LengthMode::HORIZONTAL);
    float bottomLeftRadiusY = SkiaGetFloatRadiusValue(
        rect->GetBottomLeftRadius().GetY(), rect->GetBottomLeftRadius().GetX(), radiusSize, LengthMode::VERTICAL);
    const SkVector fRadii[4] = { { topLeftRadiusX, topLeftRadiusY }, { topRightRadiusX, topRightRadiusY },
        { bottomRightRadiusX, bottomRightRadiusY }, { bottomLeftRadiusX, bottomLeftRadiusY } };
    SkRRect roundRect;
    roundRect.setRectRadii(skRect, fRadii);
    skPath.addRRect(roundRect);
}

void SkiaDecorationPainter::PaintGrayScale(const SkRRect& rRect, SkCanvas* canvas, float scale)
{
    if (GreatNotEqual(scale, 0.0)) {
        if (canvas) {
            SkAutoCanvasRestore acr(canvas, true);
            canvas->clipRRect(rRect, true);
            SkPaint paint;
            paint.setAntiAlias(true);
            float matrix[20] = { 0.0f };
            matrix[0] = matrix[5] = matrix[10] = 0.2126f * scale;
            matrix[1] = matrix[6] = matrix[11] = 0.7152f * scale;
            matrix[2] = matrix[7] = matrix[12] = 0.0722f * scale;
            matrix[18] = 1.0f * scale;
            paint.setColorFilter(SkColorFilters::Matrix(matrix));
            SkCanvas::SaveLayerRec slr(nullptr, &paint, SkCanvas::kInitWithPrevious_SaveLayerFlag);
            canvas->saveLayer(slr);
        }
    }
}

void SkiaDecorationPainter::PaintBrightness(const SkRRect& rRect, SkCanvas* canvas, float bright)
{
    // brightness range = (0, 2)
    // skip painting when brightness is normal
    CHECK_NULL_VOID(!NearEqual(bright, 1.0));
    if (canvas) {
        SkAutoCanvasRestore acr(canvas, true);
        canvas->clipRRect(rRect, true);
        SkPaint paint;
        paint.setAntiAlias(true);
        float matrix[20] = { 0.0f };
        // shift brightness to (-1, 1)
        bright = bright - 1;
        matrix[0] = matrix[6] = matrix[12] = matrix[18] = 1.0f;
        matrix[4] = matrix[9] = matrix[14] = bright;
        paint.setColorFilter(SkColorFilters::Matrix(matrix));
        SkCanvas::SaveLayerRec slr(nullptr, &paint, SkCanvas::kInitWithPrevious_SaveLayerFlag);
        canvas->saveLayer(slr);
    }
}

void SkiaDecorationPainter::PaintContrast(const SkRRect& rRect, SkCanvas* canvas, float contrasts)
{
    // skip painting if contrast is normal
    CHECK_NULL_VOID(!NearEqual(contrasts, 1.0));
    if (canvas) {
        SkAutoCanvasRestore acr(canvas, true);
        canvas->clipRRect(rRect, true);
        SkPaint paint;
        paint.setAntiAlias(true);
        float matrix[20] = { 0.0f };
        matrix[0] = matrix[6] = matrix[12] = contrasts;
        matrix[4] = matrix[9] = matrix[14] = 128 * (1 - contrasts) / 255;
        matrix[18] = 1.0f;
        paint.setColorFilter(SkColorFilters::Matrix(matrix));
        SkCanvas::SaveLayerRec slr(nullptr, &paint, SkCanvas::kInitWithPrevious_SaveLayerFlag);
        canvas->saveLayer(slr);
    }
}

void SkiaDecorationPainter::PaintColorBlend(const SkRRect& rRect, SkCanvas* canvas, const Color& colorBlend)
{
    if (colorBlend.GetValue() != COLOR_MASK) {
        if (canvas) {
            SkAutoCanvasRestore acr(canvas, true);
            canvas->clipRRect(rRect, true);
            SkPaint paint;
            paint.setAntiAlias(true);
            paint.setColorFilter(SkColorFilters::Blend(
                SkColorSetARGB(colorBlend.GetAlpha(), colorBlend.GetRed(), colorBlend.GetGreen(), colorBlend.GetBlue()),
                SkBlendMode::kPlus));
            SkCanvas::SaveLayerRec slr(nullptr, &paint, SkCanvas::kInitWithPrevious_SaveLayerFlag);
            canvas->saveLayer(slr);
        }
    }
}

void SkiaDecorationPainter::PaintSaturate(const SkRRect& rRect, SkCanvas* canvas, float saturates)
{
    if (!NearEqual(saturates, 1.0) && GreatOrEqual(saturates, 0.0)) {
        if (canvas) {
            SkAutoCanvasRestore acr(canvas, true);
            canvas->clipRRect(rRect, true);
            SkPaint paint;
            paint.setAntiAlias(true);
            float matrix[20] = { 0.0f };
            matrix[0] = 0.3086f * (1 - saturates) + saturates;
            matrix[1] = matrix[11] = 0.6094f * (1 - saturates);
            matrix[2] = matrix[7] = 0.0820f * (1 - saturates);
            matrix[5] = matrix[10] = 0.3086f * (1 - saturates);
            matrix[6] = 0.6094f * (1 - saturates) + saturates;
            matrix[12] = 0.0820f * (1 - saturates) + saturates;
            matrix[18] = 1.0f;
            paint.setColorFilter(SkColorFilters::Matrix(matrix));
            SkCanvas::SaveLayerRec slr(nullptr, &paint, SkCanvas::kInitWithPrevious_SaveLayerFlag);
            canvas->saveLayer(slr);
        }
    }
}

void SkiaDecorationPainter::PaintSepia(const SkRRect& rRect, SkCanvas* canvas, float sepias)
{
    if (sepias > 1.0) {
        sepias = 1.0;
    }
    if (GreatNotEqual(sepias, 0.0)) {
        if (canvas) {
            SkAutoCanvasRestore acr(canvas, true);
            canvas->clipRRect(rRect, true);
            SkPaint paint;
            paint.setAntiAlias(true);
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
            paint.setColorFilter(SkColorFilters::Matrix(matrix));
            SkCanvas::SaveLayerRec slr(nullptr, &paint, SkCanvas::kInitWithPrevious_SaveLayerFlag);
            canvas->saveLayer(slr);
        }
    }
}

void SkiaDecorationPainter::PaintInvert(const SkRRect& rRect, SkCanvas* canvas, float inverts)
{
    if (GreatNotEqual(inverts, 0.0)) {
        if (canvas) {
            SkAutoCanvasRestore acr(canvas, true);
            canvas->clipRRect(rRect, true);
            SkPaint paint;
            paint.setAntiAlias(true);
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
            paint.setColorFilter(SkColorFilters::Matrix(matrix));
            SkCanvas::SaveLayerRec slr(nullptr, &paint, SkCanvas::kInitWithPrevious_SaveLayerFlag);
            canvas->saveLayer(slr);
        }
    }
}

void SkiaDecorationPainter::PaintHueRotate(const SkRRect& rRect, SkCanvas* canvas, float hueRotate)
{
    if (GreatNotEqual(hueRotate, 0.0)) {
        if (canvas) {
            SkAutoCanvasRestore acr(canvas, true);
            canvas->clipRRect(rRect, true);
            SkPaint paint;
            paint.setAntiAlias(true);
            while (GreatOrEqual(hueRotate, FULL_ROTATION)) {
                hueRotate -= FULL_ROTATION;
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
            paint.setColorFilter(SkColorFilters::Matrix(matrix));
            SkCanvas::SaveLayerRec slr(nullptr, &paint, SkCanvas::kInitWithPrevious_SaveLayerFlag);
            canvas->saveLayer(slr);
        }
    }
}

SkPaint SkiaDecorationPainter::CreateMaskSkPaint(const RefPtr<BasicShape>& basicShape)
{
    SkPaint paint;
    paint.setAntiAlias(true);
    paint.setStyle(SkPaint::Style::kFill_Style);
    paint.setColor(basicShape->GetColor().GetValue());
    return paint;
}

RSImage SkiaDecorationPainter::CreateBorderImageGradient(const NG::Gradient& gradient, const SizeF& paintSize)
{
    auto shader = SkiaDecorationPainter::CreateGradientShader(gradient, paintSize);
    SkPaint paint;
    paint.setAntiAlias(true);
    paint.setShader(std::move(shader));

    auto imageInfo = SkImageInfo::Make(paintSize.Width(), paintSize.Height(),
        SkColorType::kRGBA_8888_SkColorType, SkAlphaType::kOpaque_SkAlphaType);
    SkBitmap skBitmap;
    skBitmap.allocPixels(imageInfo);

    std::unique_ptr<SkCanvas> skCanvas = std::make_unique<SkCanvas>(skBitmap);
    skCanvas->drawPaint(paint);
    auto skImage = SkImage::MakeFromBitmap(skBitmap);
    return RSImage(&skImage);
}

} // namespace OHOS::Ace::NG
