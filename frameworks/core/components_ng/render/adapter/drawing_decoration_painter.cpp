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

#include "core/components_ng/render/adapter/drawing_decoration_painter.h"

#include "core/components_ng/property/measure_utils.h"
#include "core/pipeline/base/constants.h"

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
        ColorSpace colorSpace { ColorSpace::SRGB };
    };

    explicit GradientShader(const NG::Gradient& gradient)
    {
        for (auto& stop : gradient.GetColors()) {
            ColorStop colorStop;
            colorStop.color = stop.GetColor().GetValue();
            colorStop.colorSpace = stop.GetColor().GetColorSpace();
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
                if (noValueStartIndex < noValueEndIndex && noValueStartIndex > 0) {
                    uint32_t index = static_cast<uint32_t>(noValueStartIndex - 1);
                    auto beginValue = colorStops_[index].offset;
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

    static RSColor4f RSColorQuadToRSColor4f(RSColorQuad colorQuad)
    {
        Rosen::Drawing::Color color { colorQuad };
        return color.GetColor4f();
    }

    void ToRSColor4fVector(std::vector<RSScalar>& pos, std::vector<RSColor4f>& color4fs)
    {
        if (colorStops_.empty()) {
            pos.push_back(0.0f);
            color4fs.push_back(RSColorQuadToRSColor4f(RSColor::COLOR_TRANSPARENT));
        } else if (colorStops_.front().offset > 0.0f) {
            pos.push_back(0.0f);
            color4fs.push_back(RSColorQuadToRSColor4f(colorStops_.front().color));
        }

        for (const auto& stop : colorStops_) {
            pos.push_back(stop.offset);
            color4fs.push_back(RSColorQuadToRSColor4f(stop.color));
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
        return RSRecordingShaderEffect::CreateLinearGradient(pts[0], pts[1], colors, pos, tileMode);
    }

    static std::unique_ptr<GradientShader> CreateLinearGradient(const NG::Gradient& gradient, const RSSize& size)
    {
        auto linearGradient = gradient.GetLinearGradient();
        CHECK_NULL_RETURN(linearGradient, nullptr);
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
        return static_cast<float>(deg * ACE_PI / 180.0);
    }

    static float Rad2deg(float rad)
    {
        return static_cast<float>(rad * 180.0 / ACE_PI);
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
        return RSRecordingShaderEffect::CreateTwoPointConical(
            center_, radius0_, center_, radius1_, colors, pos, tileMode, &matrix);
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
        std::vector<RSColor4f> color4fs;
        std::shared_ptr<RSColorSpace> colorSpace = RSColorSpace::CreateSRGB();
        if (!colorStops_.empty()) {
            if (ColorSpace::DISPLAY_P3 == colorStops_.back().colorSpace) {
                colorSpace = RSColorSpace::CreateRGB(
                    Rosen::Drawing::CMSTransferFuncType::SRGB, Rosen::Drawing::CMSMatrixType::DCIP3);
            }
        }
        ToRSColor4fVector(pos, color4fs);
        RSTileMode tileMode = RSTileMode::CLAMP;
        if (isRepeat_) {
            tileMode = RSTileMode::REPEAT;
        }
        return RSRecordingShaderEffect::CreateSweepGradient(
            center_, color4fs, colorSpace, pos, tileMode, startAngle_, endAngle_, &matrix);
    }

    static std::unique_ptr<GradientShader> CreateSweepGradient(const NG::Gradient& gradient, const RSSize& size)
    {
        auto sweepGradient = gradient.GetSweepGradient();
        CHECK_NULL_RETURN(sweepGradient, nullptr);
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
        if (startAngle > endAngle) {
            return nullptr;
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
    if (!ptr) {
        return nullptr;
    }
    return ptr->CreateGradientShader();
}

float DrawingDecorationPainter::DrawingDimensionToPx(const Dimension& value, const SizeF& size, LengthMode type)
{
    if (value.Unit() == DimensionUnit::PERCENT) {
        switch (type) {
            case LengthMode::HORIZONTAL:
                return ConvertToPx(value, ScaleProperty::CreateScaleProperty(), size.Width()).value_or(0.0f);
            case LengthMode::VERTICAL:
                return ConvertToPx(value, ScaleProperty::CreateScaleProperty(), size.Height()).value_or(0.0f);
            case LengthMode::OTHER:
                return ConvertToPx(value, ScaleProperty::CreateScaleProperty(), sqrt(size.Width() * size.Height()))
                    .value_or(0.0f);
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

RSRecordingPath DrawingDecorationPainter::DrawingCreatePath(const RefPtr<BasicShape>& basicShape, const SizeF& size)
{
    OffsetF position;
    RSRecordingPath rsPath;
    if (basicShape == nullptr || basicShape->GetBasicShapeType() == BasicShapeType::NONE) {
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
    double right =
        size.Width() - DrawingDimensionToPx(inset->GetRight(), size, LengthMode::HORIZONTAL) + position.GetX();
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
    float bottomLeftRadiusY =
        DrawingDimensionToPx(inset->GetBottomLeftRadius().GetY(), radiusSize, LengthMode::VERTICAL);
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
        float offsetX =
            DrawingDimensionToPx(circle->GetOffset().GetX(), size, LengthMode::HORIZONTAL) + position.GetX();
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
    RSRecordingPath tmpPath;
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
            filter.SetColorFilter(RSRecordingColorFilter::CreateMatrixColorFilter(colorMatrix));
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
    CHECK_NULL_VOID(!NearEqual(bright, 1.0));
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
        filter.SetColorFilter(RSRecordingColorFilter::CreateMatrixColorFilter(colorMatrix));
        brush.SetFilter(filter);
        RSSaveLayerOps slr(nullptr, &brush, RSSaveLayerOps::Flags::INIT_WITH_PREVIOUS);
        canvas->SaveLayer(slr);
    }
}

void DrawingDecorationPainter::PaintContrast(const RSRoundRect& rRect, RSCanvas* canvas, float contrasts)
{
    // skip painting if contrast is normal
    CHECK_NULL_VOID(!NearEqual(contrasts, 1.0));
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
        filter.SetColorFilter(RSRecordingColorFilter::CreateMatrixColorFilter(colorMatrix));
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
            filter.SetColorFilter(RSRecordingColorFilter::CreateBlendModeColorFilter(RSColor::ColorQuadSetARGB(
                colorBlend.GetAlpha(), colorBlend.GetRed(), colorBlend.GetGreen(), colorBlend.GetBlue()),
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
            filter.SetColorFilter(RSRecordingColorFilter::CreateMatrixColorFilter(colorMatrix));
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
            filter.SetColorFilter(RSRecordingColorFilter::CreateMatrixColorFilter(colorMatrix));
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
            filter.SetColorFilter(RSRecordingColorFilter::CreateMatrixColorFilter(colorMatrix));
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
            filter.SetColorFilter(RSRecordingColorFilter::CreateMatrixColorFilter(colorMatrix));
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
