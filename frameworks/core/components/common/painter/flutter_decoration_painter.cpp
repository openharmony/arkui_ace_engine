/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "core/components/common/painter/flutter_decoration_painter.h"

#include <cmath>
#include <functional>

#include "flutter/common/task_runners.h"
#include "include/core/SkColor.h"
#include "include/core/SkMaskFilter.h"
#include "include/effects/Sk1DPathEffect.h"
#include "include/effects/SkDashPathEffect.h"
#include "include/effects/SkGradientShader.h"
#include "include/effects/SkImageFilters.h"
#include "include/utils/SkShadowUtils.h"

#include "core/components/common/painter/border_image_painter.h"
#include "core/components/common/properties/color.h"
#include "core/pipeline/base/flutter_render_context.h"
#include "core/pipeline/base/render_node.h"
#include "core/pipeline/pipeline_context.h"

namespace OHOS::Ace {
namespace {

constexpr int32_t DOUBLE_WIDTH = 2;
constexpr int32_t DASHED_LINE_LENGTH = 3;
constexpr float TOP_START = 225.0f;
constexpr float TOP_END = 270.0f;
constexpr float RIGHT_START = 315.0f;
constexpr float RIGHT_END = 0.0f;
constexpr float BOTTOM_START = 45.0f;
constexpr float BOTTOM_END = 90.0f;
constexpr float LEFT_START = 135.0f;
constexpr float LEFT_END = 180.0f;
constexpr float SWEEP_ANGLE = 45.0f;
constexpr float EXTEND = 1024.0f;
constexpr uint32_t COLOR_MASK = 0xff000000;

class GradientShader {
public:
    struct ColorStop {
        SkColor color { SK_ColorTRANSPARENT };
        float offset { 0.0f };
        bool hasValue { false };
        bool isLength { false };
    };

    explicit GradientShader(const Gradient& gradient)
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
                if (noValueStartIndex > 0 && noValueStartIndex < noValueEndIndex) {
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
    LinearGradientShader(const Gradient& gradient, const SkPoint& firstPoint, const SkPoint& secondPoint)
        : GradientShader(gradient), firstPoint_(firstPoint), secondPoint_(secondPoint)
    {}
    ~LinearGradientShader() = default;

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

    static std::unique_ptr<GradientShader> CreateLinearGradient(const Gradient& gradient, const SkSize& size)
    {
        auto linearGradient = gradient.GetLinearGradient();
        SkPoint firstPoint { 0.0f, 0.0f };
        SkPoint secondPoint { 0.0f, 0.0f };
        if (linearGradient.angle) {
            EndPointsFromAngle(linearGradient.angle.value().Value(), size, firstPoint, secondPoint);
        } else {
            if (linearGradient.linearX && linearGradient.linearY) {
                float width = size.width();
                float height = size.height();
                if (linearGradient.linearX == GradientDirection::LEFT) {
                    height *= -1;
                }
                if (linearGradient.linearY == GradientDirection::BOTTOM) {
                    width *= -1;
                }
                float angle = 90.0f - Rad2deg(atan2(width, height));
                EndPointsFromAngle(angle, size, firstPoint, secondPoint);
            } else if (linearGradient.linearX || linearGradient.linearY) {
                secondPoint = DirectionToPoint(linearGradient.linearX, linearGradient.linearY, size);
                if (linearGradient.linearX) {
                    firstPoint.fX = size.width() - secondPoint.x();
                }
                if (linearGradient.linearY) {
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
    RadialGradientShader(const Gradient& gradient, const SkPoint& center, float radius0, float radius1, float ratio)
        : GradientShader(gradient), center_(center), radius0_(radius0), radius1_(radius1), ratio_(ratio)
    {}

    ~RadialGradientShader() = default;

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

    static std::unique_ptr<GradientShader> CreateRadialGradient(
        const Gradient& gradient, const SkSize& size, float dipScale)
    {
        auto radialGradient = gradient.GetRadialGradient();
        SkPoint center = GetCenter(radialGradient, size, dipScale);
        SkSize circleSize = GetCircleSize(radialGradient, size, center, dipScale);
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

    static SkPoint GetCenter(const RadialGradient& radialGradient, const SkSize& size, float dipScale)
    {
        SkPoint center = SkPoint::Make(size.width() / 2.0f, size.height() / 2.0f);
        if (radialGradient.radialCenterX) {
            const auto& value = radialGradient.radialCenterX.value();
            center.fX = static_cast<float>(value.Unit() == DimensionUnit::PERCENT ? value.Value() / 100.0 * size.width()
                                                                                  : value.ConvertToPx(dipScale));
        }
        if (radialGradient.radialCenterY) {
            const auto& value = radialGradient.radialCenterY.value();
            center.fY =
                static_cast<float>(value.Unit() == DimensionUnit::PERCENT ? value.Value() / 100.0 * size.height()
                                                                          : value.ConvertToPx(dipScale));
        }
        return center;
    }

    static SkSize GetCircleSize(
        const RadialGradient& radialGradient, const SkSize& size, const SkPoint& center, float dipScale)
    {
        SkSize circleSize { 0.0f, 0.0f };
        if (radialGradient.radialHorizontalSize) {
            const auto& hValue = radialGradient.radialHorizontalSize.value();
            circleSize.fWidth = static_cast<float>(
                hValue.Unit() == DimensionUnit::PERCENT ? hValue.Value() * size.width() : hValue.ConvertToPx(dipScale));
            circleSize.fHeight = circleSize.fWidth;
            if (radialGradient.radialVerticalSize) {
                const auto& wValue = radialGradient.radialVerticalSize.value();
                circleSize.fHeight =
                    static_cast<float>(wValue.Unit() == DimensionUnit::PERCENT ? wValue.Value() * size.height()
                                                                               : wValue.ConvertToPx(dipScale));
            }
        } else {
            RadialShapeType shape = RadialShapeType::ELLIPSE;
            if ((radialGradient.radialShape && radialGradient.radialShape.value() == RadialShapeType::CIRCLE) ||
                (!radialGradient.radialShape && !radialGradient.radialSizeType && radialGradient.radialHorizontalSize &&
                    !radialGradient.radialVerticalSize)) {
                shape = RadialShapeType::CIRCLE;
            }
            auto sizeType =
                radialGradient.radialSizeType ? radialGradient.radialSizeType.value() : RadialSizeType::NONE;
            switch (sizeType) {
                case RadialSizeType::CLOSEST_SIDE:
                    circleSize = RadiusToSide(center, size, shape, std::less<>());
                    break;
                case RadialSizeType::FARTHEST_SIDE:
                    circleSize = RadiusToSide(center, size, shape, std::greater<>());
                    break;
                case RadialSizeType::CLOSEST_CORNER:
                    circleSize = RadiusToCorner(center, size, shape, std::less<>());
                    break;
                case RadialSizeType::FARTHEST_CORNER:
                case RadialSizeType::NONE:
                default:
                    circleSize = RadiusToCorner(center, size, shape, std::greater<>());
                    break;
            }
        }
        return circleSize;
    }

    using CompareType = std::function<bool(float, float)>;

    static SkSize RadiusToSide(
        const SkPoint& center, const SkSize& size, RadialShapeType type, const CompareType& compare)
    {
        auto dx1 = static_cast<float>(std::fabs(center.fX));
        auto dy1 = static_cast<float>(std::fabs(center.fY));
        auto dx2 = static_cast<float>(std::fabs(center.fX - size.width()));
        auto dy2 = static_cast<float>(std::fabs(center.fY - size.height()));

        auto dx = compare(dx1, dx2) ? dx1 : dx2;
        auto dy = compare(dy1, dy2) ? dy1 : dy2;

        if (type == RadialShapeType::CIRCLE) {
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
        const SkPoint& center, const SkSize& size, RadialShapeType type, const CompareType& compare)
    {
        const SkPoint corners[4] = {
            SkPoint::Make(0.0f, 0.0f),
            SkPoint::Make(size.width(), 0.0f),
            SkPoint::Make(size.width(), size.height()),
            SkPoint::Make(0.0f, size.height()),
        };

        int32_t cornerIndex = 0;
        float distance = (center - corners[cornerIndex]).length();
        for (int32_t i = 1; i < 4; i++) {
            float newDistance = (center - corners[i]).length();
            if (compare(newDistance, distance)) {
                cornerIndex = i;
                distance = newDistance;
            }
        }

        if (type == RadialShapeType::CIRCLE) {
            return SkSize::Make(distance, distance);
        }

        SkSize sideRadius = RadiusToSide(center, size, RadialShapeType::ELLIPSE, compare);
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
        const Gradient& gradient, const SkPoint& center, float startAngle, float endAngle, float rotation)
        : GradientShader(gradient), center_(center), startAngle_(startAngle), endAngle_(endAngle), rotation_(rotation)
    {}
    ~SweepGradientShader() = default;

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
        const Gradient& gradient, const SkSize& size, float dipScale)
    {
        auto sweepGradient = gradient.GetSweepGradient();
        SkPoint center = GetCenter(sweepGradient, size, dipScale);
        float rotationAngle = 0.0f;
        if (sweepGradient.rotation) {
            rotationAngle = fmod(sweepGradient.rotation.value().Value(), 360.0f);
            if (LessNotEqual(rotationAngle, 0.0f)) {
                rotationAngle += 360.0f;
            }
        }
        float startAngle = 0.0f;
        float endAngle = 0.0f;
        if (sweepGradient.startAngle.has_value()) {
            startAngle = sweepGradient.startAngle.value().Value();
        }
        if (sweepGradient.endAngle.has_value()) {
            endAngle = sweepGradient.endAngle.value().Value();
        }
        return std::make_unique<SweepGradientShader>(gradient, center, startAngle, endAngle, rotationAngle);
    }

private:
    static SkPoint GetCenter(const SweepGradient& sweepGradient, const SkSize& size, float dipScale)
    {
        SkPoint center = SkPoint::Make(size.width() / 2.0f, size.height() / 2.0f);

        if (sweepGradient.centerX) {
            const auto& value = sweepGradient.centerX.value();
            center.fX =
                static_cast<float>(value.Unit() == DimensionUnit::PERCENT ? value.Value() / 100.0f * size.width()
                                                                          : value.ConvertToPx(dipScale));
        }
        if (sweepGradient.centerY) {
            const auto& value = sweepGradient.centerY.value();
            center.fY =
                static_cast<float>(value.Unit() == DimensionUnit::PERCENT ? value.Value() / 100.0f * size.height()
                                                                          : value.ConvertToPx(dipScale));
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

FlutterDecorationPainter::FlutterDecorationPainter(
    const RefPtr<Decoration>& decoration, const Rect& paintRect, const Size& paintSize, double dipScale)
    : dipScale_(dipScale), paintRect_(paintRect), decoration_(decoration), paintSize_(paintSize)
{}

void FlutterDecorationPainter::PaintDecoration(const Offset& offset, SkCanvas* canvas, RenderContext& context)
{
    if (!canvas) {
        LOGE("PaintDecoration failed, canvas is null.");
        return;
    }
    if (decoration_ && paintSize_.IsValid()) {
        canvas->save();
        SkPaint paint;

        if (opacity_ != UINT8_MAX) {
            paint.setAlpha(opacity_);
        }

        Border border = decoration_->GetBorder();
        flutter::RRect outerRRect = GetOuterRRect(offset + margin_.GetOffsetInPx(scale_), border);
        flutter::RRect innerRRect = GetInnerRRect(offset + margin_.GetOffsetInPx(scale_), border);
        flutter::RRect clipRRect = GetClipRRect(offset + margin_.GetOffsetInPx(scale_), border);
        if (clipLayer_) {
            // If you want to clip the rounded edges, you need to set a Cliplayer first.
            clipLayer_->SetClipRRect(outerRRect);
        }
        PaintBoxShadows(outerRRect.sk_rrect, decoration_->GetShadows(), canvas);
        canvas->clipRRect(CanUseInnerRRect(border) ? innerRRect.sk_rrect : outerRRect.sk_rrect, true);
        PaintColorAndImage(offset, canvas, paint, context);
        canvas->restore();
        if (border.HasValue()) {
            paint.setAntiAlias(true);
            AdjustBorderStyle(border);
            if (CanUseFourLine(border)) {
                PaintBorderWithLine(offset + margin_.GetOffsetInPx(scale_), border, canvas, paint);
            } else if (CanUseFillStyle(border, paint)) {
                canvas->drawDRRect(outerRRect.sk_rrect, innerRRect.sk_rrect, paint);
            } else if (CanUsePathRRect(border, paint)) {
                SkPath borderPath;
                borderPath.addRRect(clipRRect.sk_rrect);
                canvas->drawPath(borderPath, paint);
            } else {
                canvas->save();
                canvas->clipRRect(outerRRect.sk_rrect, SkClipOp::kIntersect, true);
                canvas->clipRRect(innerRRect.sk_rrect, SkClipOp::kDifference, true);
                PaintBorderWithPath(offset + margin_.GetOffsetInPx(scale_), border, canvas, paint);
                canvas->restore();
            }
        }
    }
}

void FlutterDecorationPainter::PaintBorderImage(
    SkPaint& paint, const Offset& offset, SkCanvas* canvas, const sk_sp<SkImage>& image)
{
    paint.setAntiAlias(true);
    if (decoration_->GetHasBorderImageSource()) {
        if (!image) {
            return;
        }
        canvas->save();

        BorderImagePainter borderImagePainter(paintSize_, decoration_, image, dipScale_);
        borderImagePainter.InitPainter();
        borderImagePainter.PaintBorderImage(offset + margin_.GetOffsetInPx(dipScale_), canvas, paint);
        canvas->restore();
    }
    if (decoration_->GetHasBorderImageGradient()) {
        Gradient gradient = decoration_->GetBorderImageGradient();
        if (!gradient.IsValid()) {
            LOGE("Gradient not valid");
            return;
        }
        if (NearZero(paintSize_.Width()) || NearZero(paintSize_.Height())) {
            return;
        }
        canvas->save();

        SkSize skPaintSize = SkSize::Make(paintSize_.Width(), paintSize_.Height());
        auto shader = CreateGradientShader(gradient, skPaintSize);
        paint.setShader(std::move(shader));

        auto imageInfo = SkImageInfo::Make(paintSize_.Width(), paintSize_.Height(), SkColorType::kRGBA_8888_SkColorType,
            SkAlphaType::kOpaque_SkAlphaType);
        SkBitmap skBitmap_;
        skBitmap_.allocPixels(imageInfo);
        std::unique_ptr<SkCanvas> skCanvas_ = std::make_unique<SkCanvas>(skBitmap_);
        skCanvas_->drawPaint(paint);
        sk_sp<SkImage> skImage_ = SkImage::MakeFromBitmap(skBitmap_);
        BorderImagePainter borderImagePainter(paintSize_, decoration_, skImage_, dipScale_);
        borderImagePainter.InitPainter();
        borderImagePainter.PaintBorderImage(offset + margin_.GetOffsetInPx(dipScale_), canvas, paint);
        paint.setShader(nullptr);
        canvas->restore();
    }
}

void FlutterDecorationPainter::PaintDecoration(
    const Offset& offset, SkCanvas* canvas, RenderContext& context, const sk_sp<SkImage>& image, bool paintBorder)
{
    if (!canvas) {
        LOGE("PaintDecoration failed, canvas is null.");
        return;
    }
    if (decoration_) {
        canvas->save();
        SkPaint paint;

        if (opacity_ != UINT8_MAX) {
            paint.setAlpha(opacity_);
        }
        Border border = decoration_->GetBorder();
        flutter::RRect outerRRect = GetOuterRRect(offset + margin_.GetOffsetInPx(scale_), border);
        flutter::RRect innerRRect = GetInnerRRect(offset + margin_.GetOffsetInPx(scale_), border);

        if (clipLayer_) {
            // If you want to clip the rounded edges, you need to set a Cliplayer first.
            clipLayer_->SetClipRRect(outerRRect);
        }
        PaintBoxShadows(outerRRect.sk_rrect, decoration_->GetShadows(), canvas);
        canvas->clipRRect(CanUseInnerRRect(border) ? innerRRect.sk_rrect : outerRRect.sk_rrect, true);
        PaintColorAndImage(offset, canvas, paint, context);
        canvas->restore();
        if (decoration_->GetHasBorderImageSource() || decoration_->GetHasBorderImageGradient()) {
            PaintBorderImage(paint, offset, canvas, image);
            return;
        }
        if (paintBorder) {
            PaintBorder(offset, canvas);
        }
    }
}

void FlutterDecorationPainter::PaintGrayScale(
    const flutter::RRect& outerRRect, SkCanvas* canvas, const Dimension& grayscale, const Color& color)
{
    double scale = grayscale.Value();
    if (GreatNotEqual(scale, 0.0)) {
        if (canvas) {
            SkAutoCanvasRestore acr(canvas, true);
            canvas->clipRRect(outerRRect.sk_rrect, true);
            SkPaint paint;
            paint.setAntiAlias(true);
            float matrix[20] = { 0 };
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

void FlutterDecorationPainter::PaintBrightness(
    const flutter::RRect& outerRRect, SkCanvas* canvas, const Dimension& brightness, const Color& color)
{
    double bright = brightness.Value();
    // brightness range (0, 2), 1 is normal brightness
    // skip painting when brightness is 1
    if (NearEqual(bright, 1.0)) {
        return;
    }
    if (canvas) {
        SkAutoCanvasRestore acr(canvas, true);
        canvas->clipRRect(outerRRect.sk_rrect, true);
        SkPaint paint;
        paint.setAntiAlias(true);
        float matrix[20] = { 0 };
        // brightness range in Skia: (-1, 1), convert from range (0, 2)
        bright--;
        matrix[0] = matrix[6] = matrix[12] = matrix[18] = 1.0f;
        matrix[4] = matrix[9] = matrix[14] = bright;

        paint.setColorFilter(SkColorFilters::Matrix(matrix));

        SkCanvas::SaveLayerRec slr(nullptr, &paint, SkCanvas::kInitWithPrevious_SaveLayerFlag);
        canvas->saveLayer(slr);
    }
}

void FlutterDecorationPainter::PaintContrast(
    const flutter::RRect& outerRRect, SkCanvas* canvas, const Dimension& contrast, const Color& color)
{
    double contrasts = contrast.Value();
    // skip painting if contrast is normal
    if (NearEqual(contrasts, 1.0)) {
        return;
    }
    if (canvas) {
        SkAutoCanvasRestore acr(canvas, true);
        canvas->clipRRect(outerRRect.sk_rrect, true);
        SkPaint paint;
        paint.setAntiAlias(true);
        float matrix[20] = { 0 };
        matrix[0] = matrix[6] = matrix[12] = contrasts;
        matrix[4] = matrix[9] = matrix[14] = 128 * (1 - contrasts) / 255;
        matrix[18] = 1.0f;

        paint.setColorFilter(SkColorFilters::Matrix(matrix));
        SkCanvas::SaveLayerRec slr(nullptr, &paint, SkCanvas::kInitWithPrevious_SaveLayerFlag);
        canvas->saveLayer(slr);
    }
}

void FlutterDecorationPainter::PaintColorBlend(
    const flutter::RRect& outerRRect, SkCanvas* canvas, const Color& colorBlend, const Color& color)
{
    if (colorBlend.GetValue() != COLOR_MASK) {
        if (canvas) {
            SkAutoCanvasRestore acr(canvas, true);
            canvas->clipRRect(outerRRect.sk_rrect, true);
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

void FlutterDecorationPainter::PaintSaturate(
    const flutter::RRect& outerRRect, SkCanvas* canvas, const Dimension& saturate, const Color& color)
{
    double saturates = saturate.Value();
    if (!NearEqual(saturates, 1.0) && GreatOrEqual(saturates, 0.0)) {
        if (canvas) {
            SkAutoCanvasRestore acr(canvas, true);
            canvas->clipRRect(outerRRect.sk_rrect, true);
            SkPaint paint;
            paint.setAntiAlias(true);
            float matrix[20] = { 0 };
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

void FlutterDecorationPainter::PaintSepia(
    const flutter::RRect& outerRRect, SkCanvas* canvas, const Dimension& sepia, const Color& color)
{
    double sepias = sepia.Value();
    if (sepias > 1.0) {
        sepias = 1.0;
    }
    if (GreatNotEqual(sepias, 0.0)) {
        if (canvas) {
            SkAutoCanvasRestore acr(canvas, true);
            canvas->clipRRect(outerRRect.sk_rrect, true);
            SkPaint paint;
            paint.setAntiAlias(true);
            float matrix[20] = { 0 };
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

void FlutterDecorationPainter::PaintInvert(
    const flutter::RRect& outerRRect, SkCanvas* canvas, const Dimension& invert, const Color& color)
{
    double inverts = invert.Value();
    // normal invert = 0, no effect
    if (GreatNotEqual(inverts, 0.0)) {
        if (canvas) {
            SkAutoCanvasRestore acr(canvas, true);
            canvas->clipRRect(outerRRect.sk_rrect, true);
            SkPaint paint;
            paint.setAntiAlias(true);
            float matrix[20] = { 0 };
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

void FlutterDecorationPainter::PaintHueRotate(
    const flutter::RRect& outerRRect, SkCanvas* canvas, const float& hueRotate, const Color& color)
{
    float hueRotates = hueRotate;
    if (GreatNotEqual(hueRotates, 0.0)) {
        if (canvas) {
            SkAutoCanvasRestore acr(canvas, true);
            canvas->clipRRect(outerRRect.sk_rrect, true);
            SkPaint paint;
            paint.setAntiAlias(true);
            while (GreatOrEqual(hueRotates, 360)) {
                hueRotates -= 360;
            }
            float matrix[20] = { 0 };
            int32_t type = hueRotates / 120;
            float N = (hueRotates - 120 * type) / 120;
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

void FlutterDecorationPainter::PaintBlur(
    const flutter::RRect& outerRRect, SkCanvas* canvas, const Dimension& blurRadius, const Color& color)
{
    auto radius = ConvertRadiusToSigma(NormalizeToPx(blurRadius));
    if (GreatNotEqual(radius, 0.0)) {
        if (canvas) {
            SkAutoCanvasRestore acr(canvas, true);
            canvas->clipRRect(outerRRect.sk_rrect, true);
            SkPaint paint;
            paint.setAntiAlias(true);

            paint.setColorFilter(SkColorFilters::Blend(color.GetValue(), SkBlendMode::kDstOver));

            paint.setImageFilter(SkImageFilters::Blur(radius, radius, nullptr));
            SkCanvas::SaveLayerRec slr(nullptr, &paint, SkCanvas::kInitWithPrevious_SaveLayerFlag);
            canvas->saveLayer(slr);
        }
    }
}

flutter::RRect FlutterDecorationPainter::GetBoxOuterRRect(const Offset& offset)
{
    flutter::RRect outerRRect;
    if (decoration_) {
        Border border = decoration_->GetBorder();
        outerRRect = GetBoxRRect(offset + margin_.GetOffsetInPx(scale_), border, 0.0, true);
    }
    outerRRect.is_null = false;
    return outerRRect;
}

void FlutterDecorationPainter::PaintColorAndImage(
    const Offset& offset, SkCanvas* canvas, SkPaint& paint, RenderContext& renderContext)
{
    if (!decoration_) {
        return;
    }

    // paint backColor
    bool paintBgColor = false;
    paint.setStyle(SkPaint::Style::kFill_Style);
    Color backColor = decoration_->GetBackgroundColor();
    Color animationColor = decoration_->GetAnimationColor();
    if (backColor != Color::TRANSPARENT) {
        paint.setColor(backColor.GetValue());
        if (opacity_ != UINT8_MAX) {
            paint.setAlpha(opacity_);
        }
        canvas->drawRect(
            SkRect::MakeXYWH(offset.GetX() + NormalizeToPx(margin_.Left()),
                offset.GetY() + NormalizeToPx(margin_.Top()), GetLayoutSize().Width() - NormalizeToPx(margin_.Right()),
                GetLayoutSize().Height() - NormalizeToPx(margin_.Bottom())),
            paint);
        paintBgColor = true;
    }
    if (animationColor != Color::TRANSPARENT) {
        paint.setColor(animationColor.GetValue());
        if (opacity_ != UINT8_MAX) {
            paint.setAlpha(opacity_);
        }
        canvas->drawRect(
            SkRect::MakeXYWH(offset.GetX() + NormalizeToPx(margin_.Left()),
                offset.GetY() + NormalizeToPx(margin_.Top()), GetLayoutSize().Width() - NormalizeToPx(margin_.Right()),
                GetLayoutSize().Height() - NormalizeToPx(margin_.Bottom())),
            paint);
    }

    // paint background image.
    RefPtr<ArcBackground> arcBG = decoration_->GetArcBackground();
    if (arcBG) {
        Color arcColor = arcBG->GetColor();
        if (arcColor != Color::TRANSPARENT) {
            paint.setColor(arcColor.GetValue());
            canvas->drawCircle(arcBG->GetCenter().GetX(), arcBG->GetCenter().GetY(), arcBG->GetRadius(), paint);
            paintBgColor = true;
        }
    }
    if (paintBgColor) {
        return;
    }
    // paint background image.
    if (decoration_->GetImage()) {
        PaintImage(offset, renderContext);
        return;
    }
    // paint Gradient color.
    if (decoration_->GetGradient().IsValid()) {
        PaintGradient(offset, canvas, paint);
    }
}

flutter::RRect FlutterDecorationPainter::GetOuterRRect(const Offset& offset, const Border& border)
{
    flutter::RRect rrect = flutter::RRect();
    float topLeftRadiusX = NormalizeToPx(border.TopLeftRadius().GetX());
    float topLeftRadiusY = NormalizeToPx(border.TopLeftRadius().GetY());
    float topRightRadiusX = NormalizeToPx(border.TopRightRadius().GetX());
    float topRightRadiusY = NormalizeToPx(border.TopRightRadius().GetY());
    float bottomRightRadiusX = NormalizeToPx(border.BottomRightRadius().GetX());
    float bottomRightRadiusY = NormalizeToPx(border.BottomRightRadius().GetY());
    float bottomLeftRadiusX = NormalizeToPx(border.BottomLeftRadius().GetX());
    float bottomLeftRadiusY = NormalizeToPx(border.BottomLeftRadius().GetY());
    SkRect outerRect = SkRect::MakeXYWH(offset.GetX(), offset.GetY(), paintSize_.Width(), paintSize_.Height());
    const SkVector outerRadii[] = { SkVector::Make(topLeftRadiusX, topLeftRadiusY),
        SkVector::Make(topRightRadiusX, topRightRadiusY), SkVector::Make(bottomRightRadiusX, bottomRightRadiusY),
        SkVector::Make(bottomLeftRadiusX, bottomLeftRadiusY) };
    rrect.sk_rrect.setRectRadii(outerRect, outerRadii);
    return rrect;
}

flutter::RRect FlutterDecorationPainter::GetInnerRRect(const Offset& offset, const Border& border)
{
    flutter::RRect rrect = flutter::RRect();
    float x = offset.GetX();
    float y = offset.GetY();
    float w = paintSize_.Width();
    float h = paintSize_.Height();
    float leftW = NormalizeToPx(border.Left().GetWidth());
    float topW = NormalizeToPx(border.Top().GetWidth());
    float rightW = NormalizeToPx(border.Right().GetWidth());
    float bottomW = NormalizeToPx(border.Bottom().GetWidth());
    float tlX = NormalizeToPx(border.TopLeftRadius().GetX());
    float tlY = NormalizeToPx(border.TopLeftRadius().GetY());
    float trX = NormalizeToPx(border.TopRightRadius().GetX());
    float trY = NormalizeToPx(border.TopRightRadius().GetY());
    float brX = NormalizeToPx(border.BottomRightRadius().GetX());
    float brY = NormalizeToPx(border.BottomRightRadius().GetY());
    float blX = NormalizeToPx(border.BottomLeftRadius().GetX());
    float blY = NormalizeToPx(border.BottomLeftRadius().GetY());
    SkRect innerRect = SkRect::MakeXYWH(x + leftW, y + topW, w - rightW - leftW, h - bottomW - topW);
    const SkVector innerRadii[] = { SkVector::Make(std::max(0.0f, tlX - leftW), std::max(0.0f, tlY - topW)),
        SkVector::Make(std::max(0.0f, trX - rightW), std::max(0.0f, trY - topW)),
        SkVector::Make(std::max(0.0f, brX - rightW), std::max(0.0f, brY - bottomW)),
        SkVector::Make(std::max(0.0f, blX - leftW), std::max(0.0f, blY - bottomW)) };
    rrect.sk_rrect.setRectRadii(innerRect, innerRadii);
    return rrect;
}

flutter::RRect FlutterDecorationPainter::GetClipRRect(const Offset& offset, const Border& border)
{
    flutter::RRect rrect = flutter::RRect();
    float bottomRightRadiusX = NormalizeToPx(border.BottomRightRadius().GetX());
    float bottomRightRadiusY = NormalizeToPx(border.BottomRightRadius().GetY());
    float bottomLeftRadiusX = NormalizeToPx(border.BottomLeftRadius().GetX());
    float bottomLeftRadiusY = NormalizeToPx(border.BottomLeftRadius().GetY());
    float topLeftRadiusX = NormalizeToPx(border.TopLeftRadius().GetX());
    float topLeftRadiusY = NormalizeToPx(border.TopLeftRadius().GetY());
    float topRightRadiusX = NormalizeToPx(border.TopRightRadius().GetX());
    float topRightRadiusY = NormalizeToPx(border.TopRightRadius().GetY());
    const SkVector outerRadii[] = { SkVector::Make(topLeftRadiusX, topLeftRadiusY),
        SkVector::Make(topRightRadiusX, topRightRadiusY), SkVector::Make(bottomRightRadiusX, bottomRightRadiusY),
        SkVector::Make(bottomLeftRadiusX, bottomLeftRadiusY) };
    float leftW = NormalizeToPx(border.Left().GetWidth());
    float topW = NormalizeToPx(border.Top().GetWidth());
    float rightW = NormalizeToPx(border.Right().GetWidth());
    float bottomW = NormalizeToPx(border.Bottom().GetWidth());
    float x = offset.GetX() + leftW / 2.0f;
    float y = offset.GetY() + topW / 2.0f;
    float w = paintSize_.Width() - (leftW + rightW) / 2.0f;
    float h = paintSize_.Height() - (topW + bottomW) / 2.0f;
    rrect.sk_rrect.setRectRadii(SkRect::MakeXYWH(x, y, w, h), outerRadii);
    return rrect;
}

bool FlutterDecorationPainter::CanUseFillStyle(const Border& border, SkPaint& paint)
{
    if (border.Top().GetBorderStyle() != BorderStyle::SOLID || border.Right().GetBorderStyle() != BorderStyle::SOLID ||
        border.Bottom().GetBorderStyle() != BorderStyle::SOLID ||
        border.Left().GetBorderStyle() != BorderStyle::SOLID) {
        return false;
    }
    if (border.Left().GetColor() != border.Top().GetColor() || border.Left().GetColor() != border.Right().GetColor() ||
        border.Left().GetColor() != border.Bottom().GetColor()) {
        return false;
    }
    paint.setStyle(SkPaint::Style::kFill_Style);
    paint.setColor(border.Left().GetColor().GetValue());
    return true;
}

bool FlutterDecorationPainter::CanUsePathRRect(const Border& border, SkPaint& paint)
{
    if (border.Left().GetBorderStyle() != border.Top().GetBorderStyle() ||
        border.Left().GetBorderStyle() != border.Right().GetBorderStyle() ||
        border.Left().GetBorderStyle() != border.Bottom().GetBorderStyle()) {
        return false;
    }
    if (border.Left().GetWidth() != border.Top().GetWidth() || border.Left().GetWidth() != border.Right().GetWidth() ||
        border.Left().GetWidth() != border.Bottom().GetWidth()) {
        return false;
    }
    if (border.Left().GetColor() != border.Top().GetColor() || border.Left().GetColor() != border.Right().GetColor() ||
        border.Left().GetColor() != border.Bottom().GetColor()) {
        return false;
    }
    SetBorderStyle(border.Left(), paint, false);
    return true;
}

bool FlutterDecorationPainter::CanUseFourLine(const Border& border)
{
    if (border.Left().GetBorderStyle() != border.Top().GetBorderStyle() ||
        border.Left().GetBorderStyle() != border.Right().GetBorderStyle() ||
        border.Left().GetBorderStyle() != border.Bottom().GetBorderStyle()) {
        return false;
    }
    if (border.Left().GetColor() != border.Top().GetColor() || border.Left().GetColor() != border.Right().GetColor() ||
        border.Left().GetColor() != border.Bottom().GetColor()) {
        return false;
    }
    if (border.TopLeftRadius().IsValid() || border.TopRightRadius().IsValid() || border.BottomLeftRadius().IsValid() ||
        border.BottomRightRadius().IsValid()) {
        return false;
    }
    return true;
}

bool FlutterDecorationPainter::CanUseInnerRRect(const Border& border)
{
    if (!border.HasValue()) {
        return false;
    }
    if (border.Top().GetBorderStyle() != BorderStyle::SOLID || border.Right().GetBorderStyle() != BorderStyle::SOLID ||
        border.Bottom().GetBorderStyle() != BorderStyle::SOLID ||
        border.Left().GetBorderStyle() != BorderStyle::SOLID) {
        return false;
    }
    return true;
}

flutter::RRect FlutterDecorationPainter::GetBoxRRect(
    const Offset& offset, const Border& border, double shrinkFactor, bool isRound)
{
    flutter::RRect rrect = flutter::RRect();
    SkRect skRect {};
    SkVector fRadii[4] = { { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 } };
    if (CheckBorderEdgeForRRect(border)) {
        BorderEdge borderEdge = border.Left();
        double borderWidth = NormalizeToPx(borderEdge.GetWidth());
        skRect.setXYWH(SkDoubleToScalar(offset.GetX() + shrinkFactor * borderWidth),
            SkDoubleToScalar(offset.GetY() + shrinkFactor * borderWidth),
            SkDoubleToScalar(paintSize_.Width() - shrinkFactor * DOUBLE_WIDTH * borderWidth),
            SkDoubleToScalar(paintSize_.Height() - shrinkFactor * DOUBLE_WIDTH * borderWidth));
        if (isRound) {
            fRadii[SkRRect::kUpperLeft_Corner].set(
                SkDoubleToScalar(
                    std::max(NormalizeToPx(border.TopLeftRadius().GetX()) - shrinkFactor * borderWidth, 0.0)),
                SkDoubleToScalar(
                    std::max(NormalizeToPx(border.TopLeftRadius().GetY()) - shrinkFactor * borderWidth, 0.0)));
            fRadii[SkRRect::kUpperRight_Corner].set(
                SkDoubleToScalar(
                    std::max(NormalizeToPx(border.TopRightRadius().GetX()) - shrinkFactor * borderWidth, 0.0)),
                SkDoubleToScalar(
                    std::max(NormalizeToPx(border.TopRightRadius().GetY()) - shrinkFactor * borderWidth, 0.0)));
            fRadii[SkRRect::kLowerRight_Corner].set(
                SkDoubleToScalar(
                    std::max(NormalizeToPx(border.BottomRightRadius().GetX()) - shrinkFactor * borderWidth, 0.0)),
                SkDoubleToScalar(
                    std::max(NormalizeToPx(border.BottomRightRadius().GetY()) - shrinkFactor * borderWidth, 0.0)));
            fRadii[SkRRect::kLowerLeft_Corner].set(
                SkDoubleToScalar(
                    std::max(NormalizeToPx(border.BottomLeftRadius().GetX()) - shrinkFactor * borderWidth, 0.0)),
                SkDoubleToScalar(
                    std::max(NormalizeToPx(border.BottomLeftRadius().GetY()) - shrinkFactor * borderWidth, 0.0)));
        }
    } else {
        skRect.setXYWH(SkDoubleToScalar(offset.GetX() + shrinkFactor * NormalizeToPx(border.Left().GetWidth())),
            SkDoubleToScalar(offset.GetY() + shrinkFactor * NormalizeToPx(border.Top().GetWidth())),
            SkDoubleToScalar(
                paintSize_.Width() - shrinkFactor * DOUBLE_WIDTH * NormalizeToPx(border.Right().GetWidth())),
            SkDoubleToScalar(paintSize_.Height() - shrinkFactor * (NormalizeToPx(border.Bottom().GetWidth()) +
                                                                      NormalizeToPx(border.Top().GetWidth()))));
    }
    rrect.sk_rrect.setRectRadii(skRect, fRadii);
    return rrect;
}

void FlutterDecorationPainter::SetBorderStyle(
    const BorderEdge& borderEdge, SkPaint& paint, bool useDefaultColor, double spaceBetweenDot, double borderLength)
{
    if (borderEdge.HasValue()) {
        double width = NormalizeToPx(borderEdge.GetWidth());
        uint32_t color = useDefaultColor ? Color::BLACK.GetValue() : borderEdge.GetColor().GetValue();
        paint.setStrokeWidth(width);
        paint.setColor(color);
        paint.setStyle(SkPaint::Style::kStroke_Style);
        if (borderEdge.GetBorderStyle() == BorderStyle::DOTTED) {
            SkPath dotPath;
            if (NearZero(spaceBetweenDot)) {
                spaceBetweenDot = width * 2.0;
            }
            dotPath.addCircle(0.0f, 0.0f, SkDoubleToScalar(width / 2.0));
            paint.setPathEffect(
                SkPath1DPathEffect::Make(dotPath, spaceBetweenDot, 0.0, SkPath1DPathEffect::kRotate_Style));
        } else if (borderEdge.GetBorderStyle() == BorderStyle::DASHED) {
            double addLen = 0.0; // When left < 2 * gap, splits left to gaps.
            double delLen = 0.0; // When left > 2 * gap, add one dash and shortening them.
            if (!NearZero(borderLength)) {
                double count = borderLength / width;
                double leftLen = fmod((count - DASHED_LINE_LENGTH), (DASHED_LINE_LENGTH + 1));
                if (leftLen > DASHED_LINE_LENGTH - 1) {
                    delLen = (DASHED_LINE_LENGTH + 1 - leftLen) * width /
                             (int32_t)((count - DASHED_LINE_LENGTH) / (DASHED_LINE_LENGTH + 1) + 2);
                } else {
                    addLen = leftLen * width / (int32_t)((count - DASHED_LINE_LENGTH) / (DASHED_LINE_LENGTH + 1));
                }
            }
            const float intervals[] = { width * DASHED_LINE_LENGTH - delLen, width + addLen };
            paint.setPathEffect(SkDashPathEffect::Make(intervals, SK_ARRAY_COUNT(intervals), 0.0));
        } else {
            paint.setPathEffect(nullptr);
        }
    }
}

void FlutterDecorationPainter::PaintBorder(const Offset& offset, SkCanvas* canvas)
{
    if (!decoration_) {
        return;
    }

    if (decoration_->GetHasBorderImageSource() || decoration_->GetHasBorderImageGradient()) {
        return;
    }

    Border border = decoration_->GetBorder();
    if (!border.HasValue()) {
        return;
    }

    SkPaint paint;
    if (opacity_ != UINT8_MAX) {
        paint.setAlpha(opacity_);
    }
    paint.setAntiAlias(true);
    paint.setStyle(SkPaint::Style::kFill_Style);
    flutter::RRect outerRRect = GetOuterRRect(offset + margin_.GetOffsetInPx(scale_), border);
    flutter::RRect innerRRect = GetInnerRRect(offset + margin_.GetOffsetInPx(scale_), border);
    flutter::RRect clipRRect = GetClipRRect(offset + margin_.GetOffsetInPx(scale_), border);

    AdjustBorderStyle(border);
    if (CanUseFourLine(border)) {
        PaintBorderWithLine(offset + margin_.GetOffsetInPx(scale_), border, canvas, paint);
    } else if (CanUseFillStyle(border, paint)) {
        canvas->drawDRRect(outerRRect.sk_rrect, innerRRect.sk_rrect, paint);
    } else if (CanUsePathRRect(border, paint)) {
        SkPath borderPath;
        borderPath.addRRect(clipRRect.sk_rrect);
        canvas->drawPath(borderPath, paint);
    } else {
        canvas->save();
        canvas->clipRRect(outerRRect.sk_rrect, SkClipOp::kIntersect, true);
        canvas->clipRRect(innerRRect.sk_rrect, SkClipOp::kDifference, true);
        PaintBorderWithPath(offset + margin_.GetOffsetInPx(scale_), border, canvas, paint);
        canvas->restore();
    }
}

void FlutterDecorationPainter::PaintBorderWithPath(
    const Offset& offset, const Border& border, SkCanvas* canvas, SkPaint& paint)
{
    float offsetX = offset.GetX();
    float offsetY = offset.GetY();
    float width = paintSize_.Width();
    float height = paintSize_.Height();
    float leftW = NormalizeToPx(border.Left().GetWidth());
    float topW = NormalizeToPx(border.Top().GetWidth());
    float rightW = NormalizeToPx(border.Right().GetWidth());
    float bottomW = NormalizeToPx(border.Bottom().GetWidth());
    float maxW = std::max(std::max(leftW, topW), std::max(rightW, bottomW));
    float x = offset.GetX() + leftW / 2.0f;
    float y = offset.GetY() + topW / 2.0f;
    float w = std::max(0.0, paintSize_.Width() - (leftW + rightW) / 2.0f);
    float h = std::max(0.0, paintSize_.Height() - (topW + bottomW) / 2.0f);
    float tlX = std::max(0.0, NormalizeToPx(border.TopLeftRadius().GetX()) - (topW + leftW) / 4.0f);
    float tlY = std::max(0.0, NormalizeToPx(border.TopLeftRadius().GetY()) - (topW + leftW) / 4.0f);
    float trX = std::max(0.0, NormalizeToPx(border.TopRightRadius().GetX()) - (topW + rightW) / 4.0f);
    float trY = std::max(0.0, NormalizeToPx(border.TopRightRadius().GetY()) - (topW + rightW) / 4.0f);
    float brX = std::max(0.0, NormalizeToPx(border.BottomRightRadius().GetX()) - (bottomW + rightW) / 4.0f);
    float brY = std::max(0.0, NormalizeToPx(border.BottomRightRadius().GetY()) - (bottomW + rightW) / 4.0f);
    float blX = std::max(0.0, NormalizeToPx(border.BottomLeftRadius().GetX()) - (bottomW + leftW) / 4.0f);
    float blY = std::max(0.0, NormalizeToPx(border.BottomLeftRadius().GetY()) - (bottomW + leftW) / 4.0f);
    if (border.Top().HasValue() && !NearZero(topW)) {
        // Draw Top Border
        SetBorderStyle(border.Top(), paint, false);
        auto rectStart = SkRect::MakeXYWH(x, y, tlX * 2.0f, tlY * 2.0f);
        auto rectEnd = SkRect::MakeXYWH(x + w - trX * 2.0f, y, trX * 2.0f, trY * 2.0f);
        SkPath topBorder;
        paint.setStrokeWidth(maxW);
        if (border.Top().GetBorderStyle() != BorderStyle::DOTTED) {
            paint.setStrokeWidth(maxW);
        }
        if (NearZero(tlX) || NearZero(tlY) || NearZero(trX) || NearZero(trY)) {
            canvas->save();
        }
        if (NearZero(tlX) && !NearZero(leftW)) {
            topBorder.moveTo(offsetX, y);
            topBorder.lineTo(x, y);
            SkPath topClipPath;
            topClipPath.moveTo(offsetX - leftW, offsetY - topW);
            topClipPath.lineTo(offsetX + leftW * EXTEND, offsetY + topW * EXTEND);
            topClipPath.lineTo(offsetX, offsetY + topW * EXTEND);
            topClipPath.close();
            canvas->clipPath(topClipPath, SkClipOp::kDifference, true);
        }
        topBorder.arcTo(rectStart, TOP_START, SWEEP_ANGLE, false);
        topBorder.arcTo(rectEnd, TOP_END, SWEEP_ANGLE + 0.5f, false);
        if (NearZero(trX) && !NearZero(rightW)) {
            topBorder.lineTo(offsetX + width, y);
            SkPath topClipPath;
            topClipPath.moveTo(offsetX + width + rightW, offsetY - topW);
            topClipPath.lineTo(offsetX + width - rightW * EXTEND, offsetY + topW * EXTEND);
            topClipPath.lineTo(offsetX + width, offsetY + topW * EXTEND);
            topClipPath.close();
            canvas->clipPath(topClipPath, SkClipOp::kDifference, true);
        }
        canvas->drawPath(topBorder, paint);
        if (NearZero(tlX) || NearZero(tlY) || NearZero(trX) || NearZero(trY)) {
            canvas->restore();
        }
    }
    if (border.Right().HasValue() && !NearZero(rightW)) {
        // Draw Right Border
        SetBorderStyle(border.Right(), paint, false);
        auto rectStart = SkRect::MakeXYWH(x + w - trX * 2.0f, y, trX * 2.0f, trY * 2.0f);
        auto rectEnd = SkRect::MakeXYWH(x + w - brX * 2.0f, y + h - brY * 2.0f, brX * 2.0f, brY * 2.0f);
        SkPath rightBorder;
        paint.setStrokeWidth(maxW);
        if (border.Right().GetBorderStyle() != BorderStyle::DOTTED) {
            paint.setStrokeWidth(maxW);
        }
        if (NearZero(trX) || NearZero(trY) || NearZero(brX) || NearZero(brY)) {
            canvas->save();
        }
        if (NearZero(trX) && !NearZero(topW)) {
            rightBorder.moveTo(offsetX + width - rightW / 2.0f, offsetY);
            rightBorder.lineTo(x + w - trX * 2.0f, y);
            SkPath rightClipPath;
            rightClipPath.moveTo(offsetX + width + rightW, offsetY - topW);
            rightClipPath.lineTo(offsetX + width - rightW * EXTEND, offsetY + topW * EXTEND);
            rightClipPath.lineTo(offsetX + width - rightW * EXTEND, offsetY);
            rightClipPath.close();
            canvas->clipPath(rightClipPath, SkClipOp::kDifference, true);
        }
        rightBorder.arcTo(rectStart, RIGHT_START, SWEEP_ANGLE, false);
        rightBorder.arcTo(rectEnd, RIGHT_END, SWEEP_ANGLE + 0.5f, false);
        if (NearZero(brX) && !NearZero(bottomW)) {
            rightBorder.lineTo(offsetX + width - rightW / 2.0f, offsetY + height);
            SkPath rightClipPath;
            rightClipPath.moveTo(offsetX + width + rightW, offsetY + height + bottomW);
            rightClipPath.lineTo(offsetX + width - rightW * EXTEND, offsetY + height - bottomW * EXTEND);
            rightClipPath.lineTo(offsetX + width - rightW * EXTEND, offsetY + height);
            rightClipPath.close();
            canvas->clipPath(rightClipPath, SkClipOp::kDifference, true);
        }
        canvas->drawPath(rightBorder, paint);
        if (NearZero(trX) || NearZero(trY) || NearZero(brX) || NearZero(brY)) {
            canvas->restore();
        }
    }
    if (border.Bottom().HasValue() && !NearZero(bottomW)) {
        // Draw Bottom Border
        SetBorderStyle(border.Bottom(), paint, false);
        auto rectStart = SkRect::MakeXYWH(x + w - brX * 2.0f, y + h - brY * 2.0f, brX * 2.0f, brY * 2.0f);
        auto rectEnd = SkRect::MakeXYWH(x, y + h - blY * 2.0f, blX * 2.0f, blY * 2.0f);
        SkPath bottomBorder;
        if (border.Bottom().GetBorderStyle() != BorderStyle::DOTTED) {
            paint.setStrokeWidth(maxW);
        }
        if (NearZero(brX) || NearZero(brY) || NearZero(blX) || NearZero(blY)) {
            canvas->save();
        }
        if (NearZero(brX) && !NearZero(rightW)) {
            bottomBorder.moveTo(offsetX + width, offsetY + height - bottomW / 2.0f);
            bottomBorder.lineTo(x + w - brX * 2.0f, y + h - brY * 2.0f);
            SkPath bottomClipPath;
            bottomClipPath.moveTo(offsetX + width + rightW, offsetY + height + bottomW);
            bottomClipPath.lineTo(offsetX + width - rightW * EXTEND, offsetY + height - bottomW * EXTEND);
            bottomClipPath.lineTo(offsetX + width, offsetY + height - bottomW * EXTEND);
            bottomClipPath.close();
            canvas->clipPath(bottomClipPath, SkClipOp::kDifference, true);
        }
        bottomBorder.arcTo(rectStart, BOTTOM_START, SWEEP_ANGLE, false);
        bottomBorder.arcTo(rectEnd, BOTTOM_END, SWEEP_ANGLE + 0.5f, false);
        if (NearZero(blX) && !NearZero(leftW)) {
            bottomBorder.lineTo(offsetX, offsetY + height - bottomW / 2.0f);
            SkPath bottomClipPath;
            bottomClipPath.moveTo(offsetX - leftW, offsetY + height + bottomW);
            bottomClipPath.lineTo(offsetX + leftW * EXTEND, offsetY + height - bottomW * EXTEND);
            bottomClipPath.lineTo(offsetX, offsetY + height - bottomW * EXTEND);
            bottomClipPath.close();
            canvas->clipPath(bottomClipPath, SkClipOp::kDifference, true);
        }
        canvas->drawPath(bottomBorder, paint);
        if (NearZero(brX) || NearZero(brY) || NearZero(blX) || NearZero(blY)) {
            canvas->restore();
        }
    }
    if (border.Left().HasValue() && !NearZero(leftW)) {
        // Draw Left Border
        SetBorderStyle(border.Left(), paint, false);
        auto rectStart = SkRect::MakeXYWH(x, y + h - blY * 2.0f, blX * 2.0f, blY * 2.0f);
        auto rectEnd = SkRect::MakeXYWH(x, y, tlX * 2.0f, tlY * 2.0f);
        SkPath leftBorder;
        if (border.Left().GetBorderStyle() != BorderStyle::DOTTED) {
            paint.setStrokeWidth(maxW);
        }
        if (NearZero(blX) || NearZero(blY) || NearZero(tlX) || NearZero(tlY)) {
            canvas->save();
        }
        if (NearZero(blX) && !NearZero(bottomW)) {
            leftBorder.moveTo(offsetX + leftW / 2.0f, offsetY + height);
            leftBorder.lineTo(x, y + h - blY * 2.0f);
            SkPath leftClipPath;
            leftClipPath.moveTo(offsetX - leftW, offsetY + height + bottomW);
            leftClipPath.lineTo(offsetX + leftW * EXTEND, offsetY + height - bottomW * EXTEND);
            leftClipPath.lineTo(offsetX + leftW * EXTEND, offsetY + height);
            leftClipPath.close();
            canvas->clipPath(leftClipPath, SkClipOp::kDifference, true);
        }
        leftBorder.arcTo(rectStart, LEFT_START, SWEEP_ANGLE, false);
        leftBorder.arcTo(rectEnd, LEFT_END, SWEEP_ANGLE + 0.5f, false);
        if (NearZero(tlX) && !NearZero(topW)) {
            leftBorder.lineTo(offsetX + leftW / 2.0f, offsetY);
            SkPath topClipPath;
            topClipPath.moveTo(offsetX - leftW, offsetY - topW);
            topClipPath.lineTo(offsetX + leftW * EXTEND, offsetY + topW * EXTEND);
            topClipPath.lineTo(offsetX + leftW * EXTEND, offsetY);
            topClipPath.close();
            canvas->clipPath(topClipPath, SkClipOp::kDifference, true);
        }
        canvas->drawPath(leftBorder, paint);
        if (NearZero(blX) || NearZero(blY) || NearZero(tlX) || NearZero(tlY)) {
            canvas->restore();
        }
    }
}

void FlutterDecorationPainter::PaintBorderWithLine(
    const Offset& offset, const Border& border, SkCanvas* canvas, SkPaint& paint)
{
    double addLen = 0.5;
    if (border.Left().GetBorderStyle() != BorderStyle::DOTTED) {
        addLen = 0.0;
    }
    // paint left border edge.
    BorderEdge left = border.Left();
    if (left.HasValue()) {
        if (NearZero(NormalizeToPx(left.GetWidth()))) {
            LOGI("left border width is zero");
            return;
        }
        auto borderLength = paintSize_.Height() - NormalizeToPx(left.GetWidth()) * addLen * 2.0;
        int32_t rawNumber = borderLength / (2 * NormalizeToPx(left.GetWidth()));
        if (NearZero(rawNumber)) {
            LOGI("number of dot is zero");
            return;
        }
        SetBorderStyle(left, paint, false, borderLength / rawNumber, borderLength);
        canvas->drawLine(offset.GetX() + SK_ScalarHalf * NormalizeToPx(left.GetWidth()),
            offset.GetY() + addLen * NormalizeToPx(left.GetWidth()),
            offset.GetX() + SK_ScalarHalf * NormalizeToPx(left.GetWidth()), offset.GetY() + paintSize_.Height(), paint);
    }

    // paint bottom border edge.
    BorderEdge bottom = border.Bottom();
    if (bottom.HasValue()) {
        if (NearZero(NormalizeToPx(bottom.GetWidth()))) {
            LOGI("bottom border width is zero");
            return;
        }
        auto borderLength = paintSize_.Width() - NormalizeToPx(bottom.GetWidth()) * addLen * 2.0;
        int32_t rawNumber = borderLength / (2 * NormalizeToPx(bottom.GetWidth()));
        if (NearZero(rawNumber)) {
            LOGI("number of dot is zero");
            return;
        }
        SetBorderStyle(bottom, paint, false, borderLength / rawNumber, borderLength);
        canvas->drawLine(offset.GetX() + addLen * NormalizeToPx(bottom.GetWidth()),
            offset.GetY() + paintSize_.Height() - SK_ScalarHalf * NormalizeToPx(bottom.GetWidth()),
            offset.GetX() + paintSize_.Width(),
            offset.GetY() + paintSize_.Height() - SK_ScalarHalf * NormalizeToPx(bottom.GetWidth()), paint);
    }
    // paint right border edge.
    BorderEdge right = border.Right();
    if (right.HasValue()) {
        if (NearZero(NormalizeToPx(right.GetWidth()))) {
            LOGI("right border width is zero");
            return;
        }
        auto borderLength = paintSize_.Height() - NormalizeToPx(right.GetWidth()) * addLen * 2.0;
        int32_t rawNumber = borderLength / (2 * NormalizeToPx(right.GetWidth()));
        if (NearZero(rawNumber)) {
            LOGI("number of dot is zero");
            return;
        }
        SetBorderStyle(right, paint, false, borderLength / rawNumber, borderLength);
        canvas->drawLine(offset.GetX() + paintSize_.Width() - SK_ScalarHalf * NormalizeToPx(right.GetWidth()),
            offset.GetY() + paintSize_.Height() - addLen * NormalizeToPx(right.GetWidth()),
            offset.GetX() + paintSize_.Width() - SK_ScalarHalf * NormalizeToPx(right.GetWidth()), offset.GetY(), paint);
    }
    // paint top border edge.
    BorderEdge top = border.Top();
    if (top.HasValue()) {
        if (NearZero(NormalizeToPx(top.GetWidth()))) {
            LOGI("top border width is zero");
            return;
        }
        auto borderLength = paintSize_.Width() - NormalizeToPx(top.GetWidth()) * addLen * 2.0;
        int32_t rawNumber = borderLength / (2 * NormalizeToPx(top.GetWidth()));
        if (NearZero(rawNumber)) {
            LOGI("number of dot is zero");
            return;
        }
        SetBorderStyle(top, paint, false, borderLength / rawNumber, borderLength);
        canvas->drawLine(offset.GetX() + addLen * NormalizeToPx(top.GetWidth()),
            offset.GetY() + SK_ScalarHalf * NormalizeToPx(top.GetWidth()), offset.GetX() + paintSize_.Width(),
            offset.GetY() + SK_ScalarHalf * NormalizeToPx(top.GetWidth()), paint);
    }
}

// Add for box-shadow, otherwise using PaintShadow().
void FlutterDecorationPainter::PaintBoxShadows(
    const SkRRect& rrect, const std::vector<Shadow>& shadows, SkCanvas* canvas)
{
    if (!canvas) {
        LOGE("PaintBoxShadows failed, canvas is null.");
        return;
    }
    canvas->save();
    // The location of the component itself does not draw a shadow
    canvas->clipRRect(rrect, SkClipOp::kDifference, true);

    if (!shadows.empty()) {
        for (const auto& shadow : shadows) {
            if (!shadow.IsValid()) {
                LOGW("The current shadow is not drawn if the shadow is invalid.");
                continue;
            }
            if (shadow.GetHardwareAcceleration()) {
                // Do not support blurRadius and spreadRadius to paint shadow, use elevation.
                PaintShadow(SkPath().addRRect(rrect), shadow, canvas);
            } else {
                SkRRect shadowRRect = rrect;
                // Keep the original rounded corners.
                SkVector fRadii[4] = { rrect.radii(SkRRect::kUpperLeft_Corner),
                    rrect.radii(SkRRect::kUpperRight_Corner), rrect.radii(SkRRect::kLowerRight_Corner),
                    rrect.radii(SkRRect::kLowerLeft_Corner) };

                SkScalar left = rrect.rect().left();
                SkScalar top = rrect.rect().top();
                auto width = rrect.width() + DOUBLE_WIDTH * shadow.GetSpreadRadius();
                auto height = rrect.height() + DOUBLE_WIDTH * shadow.GetSpreadRadius();
                SkRect skRect {};
                skRect.setXYWH(left + SkDoubleToScalar(shadow.GetOffset().GetX() - shadow.GetSpreadRadius()),
                    top + SkDoubleToScalar(shadow.GetOffset().GetY() - shadow.GetSpreadRadius()),
                    SkDoubleToScalar(width > 0.0 ? width : 0.0), SkDoubleToScalar(height > 0.0 ? height : 0.0));
                shadowRRect.setRectRadii(skRect, fRadii);
                SkPaint paint;
                paint.setColor(shadow.GetColor().GetValue());
                paint.setAntiAlias(true);
                paint.setMaskFilter(SkMaskFilter::MakeBlur(
                    SkBlurStyle::kNormal_SkBlurStyle, ConvertRadiusToSigma(shadow.GetBlurRadius())));
                canvas->drawRRect(shadowRRect, paint);
            }
        }
    }
    canvas->restore();
}

void FlutterDecorationPainter::PaintShadow(const SkPath& path, const Shadow& shadow, SkCanvas* canvas)
{
    if (!canvas) {
        LOGE("PaintShadow failed, canvas is null.");
        return;
    }
    if (!shadow.IsValid()) {
        LOGW("The current shadow is not drawn if the shadow is invalid.");
        return;
    }

    canvas->save();
    SkPath skPath = path;
    skPath.offset(shadow.GetOffset().GetX(), shadow.GetOffset().GetY());
    SkColor spotColor = shadow.GetColor().GetValue();
    if (shadow.GetHardwareAcceleration()) {
        // PlaneParams represents the coordinates of the component, and here we only need to focus on the elevation
        // of the component.
        SkPoint3 planeParams = { 0.0f, 0.0f, shadow.GetElevation() };

        // LightPos is the location of a spot light source, which is by default located directly above the center
        // of the component.
        SkPoint3 lightPos = { skPath.getBounds().centerX(), skPath.getBounds().centerY(), shadow.GetLightHeight() };

        // Current ambient color is not available.
        SkColor ambientColor = SkColorSetARGB(0, 0, 0, 0);
        SkShadowUtils::DrawShadow(canvas, skPath, planeParams, lightPos, shadow.GetLightRadius(), ambientColor,
            spotColor, SkShadowFlags::kTransparentOccluder_ShadowFlag);
    } else {
        SkPaint paint;
        paint.setColor(spotColor);
        paint.setAntiAlias(true);
        paint.setMaskFilter(SkMaskFilter::MakeBlur(kNormal_SkBlurStyle, ConvertRadiusToSigma(shadow.GetBlurRadius())));
        canvas->drawPath(skPath, paint);
    }
    canvas->restore();
}

void FlutterDecorationPainter::PaintImage(const Offset& offset, RenderContext& context)
{
    if (decoration_) {
        RefPtr<BackgroundImage> backgroundImage = decoration_->GetImage();
        if (backgroundImage && renderImage_) {
            renderImage_->RenderWithContext(context, offset);
        }
    }
}

bool FlutterDecorationPainter::GetGradientPaint(SkPaint& paint)
{
    Gradient gradient = decoration_->GetGradient();
    if (NearZero(paintSize_.Width()) || NearZero(paintSize_.Height()) || !gradient.IsValid()) {
        return false;
    }

    SkSize skPaintSize = SkSize::Make(paintSize_.Width(), paintSize_.Height());
    auto shader = CreateGradientShader(gradient, skPaintSize);
    paint.setShader(std::move(shader));
    return true;
}

void FlutterDecorationPainter::PaintGradient(const Offset& offset, SkCanvas* canvas, SkPaint& paint)
{
    Gradient gradient = decoration_->GetGradient();
    if (NearZero(paintSize_.Width()) || NearZero(paintSize_.Height())) {
        return;
    }
    if (!gradient.IsValid()) {
        return;
    }

    SkSize skPaintSize = SkSize::Make(paintSize_.Width(), paintSize_.Height());
    SkAutoCanvasRestore restore(canvas, true);
    auto shader = CreateGradientShader(gradient, skPaintSize);
    paint.setShader(std::move(shader));

    canvas->translate(offset.GetX() + NormalizeToPx(margin_.Left()), offset.GetY() + NormalizeToPx(margin_.Top()));
    canvas->drawRect(SkRect::MakeXYWH(0.0f, 0.0f, paintSize_.Width(), paintSize_.Height()), paint);
    // reset shader;
    paint.setShader(nullptr);
}

sk_sp<SkShader> FlutterDecorationPainter::CreateGradientShader(const Gradient& gradient, const SkSize& size)
{
    auto ptr = std::make_unique<GradientShader>(gradient);
    switch (gradient.GetType()) {
        case GradientType::LINEAR:
            ptr = LinearGradientShader::CreateLinearGradient(gradient, size);
            break;
        case GradientType::RADIAL:
            ptr = RadialGradientShader::CreateRadialGradient(gradient, size, dipScale_);
            break;
        case GradientType::SWEEP:
            ptr = SweepGradientShader::CreateSweepGradient(gradient, size, dipScale_);
            break;
        default:
            LOGE("unsupported gradient type.");
            break;
    }
    return ptr->CreateGradientShader();
}

bool FlutterDecorationPainter::CheckBorderEdgeForRRect(const Border& border)
{
    double leftWidth = NormalizeToPx(border.Left().GetWidth());
    if (NearEqual(leftWidth, NormalizeToPx(border.Top().GetWidth())) &&
        NearEqual(leftWidth, NormalizeToPx(border.Right().GetWidth())) &&
        NearEqual(leftWidth, NormalizeToPx(border.Bottom().GetWidth()))) {
        BorderStyle leftStyle = border.Left().GetBorderStyle();
        return leftStyle == border.Top().GetBorderStyle() && leftStyle == border.Right().GetBorderStyle() &&
               leftStyle == border.Bottom().GetBorderStyle();
    }
    return false;
}

void FlutterDecorationPainter::AdjustBorderStyle(Border& border)
{
    // if not set border style use default border style solid
    if (border.Left().IsValid() && border.Left().GetBorderStyle() == BorderStyle::NONE) {
        border.SetLeftStyle(BorderStyle::SOLID);
    }

    if (border.Top().IsValid() && border.Top().GetBorderStyle() == BorderStyle::NONE) {
        border.SetTopStyle(BorderStyle::SOLID);
    }

    if (border.Right().IsValid() && border.Right().GetBorderStyle() == BorderStyle::NONE) {
        border.SetRightStyle(BorderStyle::SOLID);
    }

    if (border.Bottom().IsValid() && border.Bottom().GetBorderStyle() == BorderStyle::NONE) {
        border.SetBottomStyle(BorderStyle::SOLID);
    }
}

double FlutterDecorationPainter::NormalizeToPx(const Dimension& dimension) const
{
    if ((dimension.Unit() == DimensionUnit::VP) || (dimension.Unit() == DimensionUnit::FP)) {
        return (dimension.Value() * dipScale_);
    }
    return dimension.Value();
}

double FlutterDecorationPainter::SliceNormalizePercentToPx(const Dimension& dimension, bool isVertical) const
{
    if (dimension.Unit() != DimensionUnit::PERCENT) {
        return NormalizeToPx(dimension);
    }
    auto limit = isVertical ? image_->width() : image_->height();
    return limit * dimension.Value();
}

double FlutterDecorationPainter::WidthNormalizePercentToPx(const Dimension& dimension, bool isVertical) const
{
    if (dimension.Unit() != DimensionUnit::PERCENT) {
        return NormalizeToPx(dimension);
    }
    auto limit = isVertical ? paintSize_.Width() : paintSize_.Height();
    return limit * dimension.Value();
}

double FlutterDecorationPainter::OutsetNormalizePercentToPx(const Dimension& dimension, bool isVertical) const
{
    if (dimension.Unit() != DimensionUnit::PERCENT) {
        return NormalizeToPx(dimension);
    }
    auto limit = isVertical ? paintSize_.Width() : paintSize_.Height();
    return limit * dimension.Value();
}

} // namespace OHOS::Ace
