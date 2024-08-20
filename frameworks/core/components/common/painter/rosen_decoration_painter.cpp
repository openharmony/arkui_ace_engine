/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#include "core/components/common/painter/rosen_decoration_painter.h"

#ifndef USE_ROSEN_DRAWING
#include "include/core/SkBitmap.h"
#include "include/core/SkCanvas.h"
#include "include/core/SkColor.h"
#include "include/core/SkColorFilter.h"
#include "include/core/SkImage.h"
#include "include/core/SkMaskFilter.h"
#include "include/effects/Sk1DPathEffect.h"
#include "include/effects/SkDashPathEffect.h"
#include "include/effects/SkGradientShader.h"
#include "include/effects/SkImageFilters.h"
#include "include/utils/SkShadowUtils.h"
#endif

#include "core/components/common/painter/border_image_painter.h"
#include "core/pipeline/base/rosen_render_context.h"

namespace OHOS::Ace {
namespace {

constexpr int32_t DOUBLE_WIDTH = 2;
constexpr int32_t DASHED_LINE_LENGTH = 3;
constexpr int32_t DEL_NUM = 2;

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
#ifdef USE_ROSEN_DRAWING
constexpr float FLOAT_HALF = 0.5f;
#endif

class GradientShader {
public:
    struct ColorStop {
#ifndef USE_ROSEN_DRAWING
        SkColor color { SK_ColorTRANSPARENT };
#else
        RSColorQuad color { RSColor::COLOR_TRANSPARENT };
#endif
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
#ifndef USE_ROSEN_DRAWING
    virtual sk_sp<SkShader> CreateGradientShader()
#else
    virtual std::shared_ptr<RSShaderEffect> CreateGradientShader()
#endif
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

#ifndef USE_ROSEN_DRAWING
    void ToSkColors(std::vector<SkScalar>& pos, std::vector<SkColor>& colors) const
#else
    void ToDrawingColors(std::vector<RSScalar>& pos, std::vector<RSColorQuad>& colors) const
#endif
    {
#ifndef USE_ROSEN_DRAWING
        if (colorStops_.empty()) {
            pos.push_back(0.0f);
            colors.push_back(SK_ColorTRANSPARENT);
        } else if (colorStops_.front().offset > 0.0f) {
            pos.push_back(0.0f);
            colors.push_back(SkColor(colorStops_.front().color));
        }
#else
        if (colorStops_.empty()) {
            pos.push_back(0.0f);
            colors.push_back(RSColor::COLOR_TRANSPARENT);
        } else if (colorStops_.front().offset > 0.0f) {
            pos.push_back(0.0f);
            colors.push_back(colorStops_.front().color);
        }
#endif

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
#ifndef USE_ROSEN_DRAWING
    LinearGradientShader(const Gradient& gradient, const SkPoint& firstPoint, const SkPoint& secondPoint)
        : GradientShader(gradient), firstPoint_(firstPoint), secondPoint_(secondPoint)
    {}
#else
    LinearGradientShader(const Gradient& gradient, const RSPoint& firstPoint, const RSPoint& secondPoint)
        : GradientShader(gradient), firstPoint_(firstPoint), secondPoint_(secondPoint)
    {}
#endif
    ~LinearGradientShader() = default;

#ifndef USE_ROSEN_DRAWING
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
#else
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
        ToDrawingColors(pos, colors);
        RSTileMode tileMode = RSTileMode::CLAMP;
        if (isRepeat_) {
            tileMode = RSTileMode::REPEAT;
        }
        return RSRecordingShaderEffect::CreateLinearGradient(firstPoint_, secondPoint_, colors, pos, tileMode);
    }
#endif

#ifndef USE_ROSEN_DRAWING
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
#else
    static std::unique_ptr<GradientShader> CreateLinearGradient(const Gradient& gradient, const RSSize& size)
    {
        auto linearGradient = gradient.GetLinearGradient();
        RSPoint firstPoint { 0.0f, 0.0f };
        RSPoint secondPoint { 0.0f, 0.0f };
        if (linearGradient.angle) {
            EndPointsFromAngle(linearGradient.angle.value().Value(), size, firstPoint, secondPoint);
        } else {
            if (linearGradient.linearX && linearGradient.linearY) {
                float width = size.Width();
                float height = size.Height();
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
                    firstPoint.SetX(size.Width() - secondPoint.GetX());
                }
                if (linearGradient.linearY) {
                    firstPoint.SetY(size.Height() - secondPoint.GetY());
                }
            } else {
                secondPoint = { 0.0f, size.Height() };
            }
        }
        return std::make_unique<LinearGradientShader>(gradient, firstPoint, secondPoint);
    }
#endif

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

#ifndef USE_ROSEN_DRAWING
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
#else
    static void EndPointsFromAngle(float angle, const RSSize& size, RSPoint& firstPoint, RSPoint& secondPoint)
    {
        angle = fmod(angle, 360.0f);
        if (LessNotEqual(angle, 0.0)) {
            angle += 360.0f;
        }

        if (NearEqual(angle, 0.0)) {
            firstPoint = { 0.0f, size.Height() };
            secondPoint = { 0.0f, 0.0f };
            return;
        } else if (NearEqual(angle, 90.0)) {
            firstPoint = { 0.0f, 0.0f };
            secondPoint = { size.Width(), 0.0f };
            return;
        } else if (NearEqual(angle, 180.0)) {
            firstPoint = { 0.0f, 0.0f };
            secondPoint = { 0, size.Height() };
            return;
        } else if (NearEqual(angle, 270.0)) {
            firstPoint = { size.Width(), 0.0f };
            secondPoint = { 0.0f, 0.0f };
            return;
        }
        float slope = tan(Deg2rad(90.0f - angle));
        float perpendicularSlope = -1 / slope;

        float halfHeight = size.Height() / 2;
        float halfWidth = size.Width() / 2;
        RSPoint cornerPoint { 0.0f, 0.0f };
        if (angle < 90.0) {
            cornerPoint = { halfWidth, halfHeight };
        } else if (angle < 180) {
            cornerPoint = { halfWidth, -halfHeight };
        } else if (angle < 270) {
            cornerPoint = { -halfWidth, -halfHeight };
        } else {
            cornerPoint = { -halfWidth, halfHeight };
        }

        // Compute b (of y = kx + b) using the corner point.
        float b = cornerPoint.GetY() - perpendicularSlope * cornerPoint.GetX();
        float endX = b / (slope - perpendicularSlope);
        float endY = perpendicularSlope * endX + b;

        secondPoint = { halfWidth + endX, halfHeight - endY };
        firstPoint = { halfWidth - endX, halfHeight + endY };
    }
#endif

#ifndef USE_ROSEN_DRAWING
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
#else
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
#endif

private:
#ifndef USE_ROSEN_DRAWING
    SkPoint firstPoint_ { 0.0f, 0.0f };
    SkPoint secondPoint_ { 0.0f, 0.0f };
#else
    RSPoint firstPoint_ { 0.0f, 0.0f };
    RSPoint secondPoint_ { 0.0f, 0.0f };
#endif
};

class RadialGradientShader final : public GradientShader {
public:
#ifndef USE_ROSEN_DRAWING
    RadialGradientShader(const Gradient& gradient, const SkPoint& center, float radius0, float radius1, float ratio)
        : GradientShader(gradient), center_(center), radius0_(radius0), radius1_(radius1), ratio_(ratio)
    {}
#else
    RadialGradientShader(const Gradient& gradient, const RSPoint& center, float radius0, float radius1, float ratio)
        : GradientShader(gradient), center_(center), radius0_(radius0), radius1_(radius1), ratio_(ratio)
    {}
#endif

    ~RadialGradientShader() = default;

#ifndef USE_ROSEN_DRAWING
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
#else
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
        ToDrawingColors(pos, colors);
        radius0_ = std::max(radius0_, 0.0f);
        radius1_ = std::max(radius1_, 0.0f);
        return RSRecordingShaderEffect::CreateTwoPointConical(
            center_, radius0_, center_, radius1_, colors, pos, tileMode, &matrix);
    }
#endif

#ifndef USE_ROSEN_DRAWING
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
#else
    static std::unique_ptr<GradientShader> CreateRadialGradient(
        const Gradient& gradient, const RSSize& size, float dipScale)
    {
        auto radialGradient = gradient.GetRadialGradient();
        RSPoint center = GetCenter(radialGradient, size, dipScale);
        RSSize circleSize = GetCircleSize(radialGradient, size, center, dipScale);
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
#endif

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

#ifndef USE_ROSEN_DRAWING
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
#else
    static RSPoint GetCenter(const RadialGradient& radialGradient, const RSSize& size, float dipScale)
    {
        RSPoint center = RSPoint(size.Width() / 2.0f, size.Height() / 2.0f);
        if (radialGradient.radialCenterX) {
            const auto& value = radialGradient.radialCenterX.value();
            center.SetX(static_cast<float>(value.Unit() == DimensionUnit::PERCENT ? value.Value() / 100.0 * size.Width()
                                                                                  : value.ConvertToPx(dipScale)));
        }
        if (radialGradient.radialCenterY) {
            const auto& value = radialGradient.radialCenterY.value();
            center.SetY(
                static_cast<float>(value.Unit() == DimensionUnit::PERCENT ? value.Value() / 100.0 * size.Height()
                                                                          : value.ConvertToPx(dipScale)));
        }
        return center;
    }
#endif

#ifndef USE_ROSEN_DRAWING
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
#else
    static RSSize GetCircleSize(
        const RadialGradient& radialGradient, const RSSize& size, const RSPoint& center, float dipScale)
    {
        RSSize circleSize { 0.0f, 0.0f };
        if (radialGradient.radialHorizontalSize) {
            const auto& hValue = radialGradient.radialHorizontalSize.value();
            RSScalar value = static_cast<float>(
                hValue.Unit() == DimensionUnit::PERCENT ? hValue.Value() * size.Width() : hValue.ConvertToPx(dipScale));
            circleSize.SetWidth(value);
            circleSize.SetHeight(value);
            if (radialGradient.radialVerticalSize) {
                const auto& wValue = radialGradient.radialVerticalSize.value();
                value = static_cast<float>(wValue.Unit() == DimensionUnit::PERCENT ? wValue.Value() * size.Height()
                                                                                   : wValue.ConvertToPx(dipScale));
                circleSize.SetHeight(value);
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
#endif

    using CompareType = std::function<bool(float, float)>;

#ifndef USE_ROSEN_DRAWING
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
#else
    static RSSize RadiusToSide(
        const RSPoint& center, const RSSize& size, RadialShapeType type, const CompareType& compare)
    {
        auto dx1 = static_cast<float>(std::fabs(center.GetX()));
        auto dy1 = static_cast<float>(std::fabs(center.GetY()));
        auto dx2 = static_cast<float>(std::fabs(center.GetX() - size.Width()));
        auto dy2 = static_cast<float>(std::fabs(center.GetY() - size.Height()));

        auto dx = compare(dx1, dx2) ? dx1 : dx2;
        auto dy = compare(dy1, dy2) ? dy1 : dy2;

        if (type == RadialShapeType::CIRCLE) {
            return compare(dx, dy) ? RSSize(dx, dx) : RSSize(dy, dy);
        }
        return RSSize(dx, dy);
    }
#endif

#ifndef USE_ROSEN_DRAWING
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
#else
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
#endif

#ifndef USE_ROSEN_DRAWING
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
#else
    static RSSize RadiusToCorner(
        const RSPoint& center, const RSSize& size, RadialShapeType type, const CompareType& compare)
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
        for (int32_t i = 1; i < 4; i++) {
            auto point = center - corners[i];
            float newDistance = std::sqrt(std::pow(point.GetX(), 2) + std::pow(point.GetY(), 2));
            if (compare(newDistance, distance)) {
                cornerIndex = i;
                distance = newDistance;
            }
        }

        if (type == RadialShapeType::CIRCLE) {
            return RSSize(distance, distance);
        }

        RSSize sideRadius = RadiusToSide(center, size, RadialShapeType::ELLIPSE, compare);
        return EllipseRadius(corners[cornerIndex] - center,
            NearZero(sideRadius.Height()) ? 1.0f : sideRadius.Width() / sideRadius.Height());
    }
#endif

private:
#ifndef USE_ROSEN_DRAWING
    SkPoint center_ { 0.0f, 0.0f };
#else
    RSPoint center_ { 0.0f, 0.0f };
#endif
    float radius0_ { 0.0f };
    float radius1_ { 0.0f };
    float ratio_ { 1.0f };
};

class SweepGradientShader final : public GradientShader {
public:
#ifndef USE_ROSEN_DRAWING
    SweepGradientShader(
        const Gradient& gradient, const SkPoint& center, float startAngle, float endAngle, float rotation)
        : GradientShader(gradient), center_(center), startAngle_(startAngle), endAngle_(endAngle), rotation_(rotation)
    {}
#else
    SweepGradientShader(
        const Gradient& gradient, const RSPoint& center, float startAngle, float endAngle, float rotation)
        : GradientShader(gradient), center_(center), startAngle_(startAngle), endAngle_(endAngle), rotation_(rotation)
    {}
#endif
    ~SweepGradientShader() = default;

#ifndef USE_ROSEN_DRAWING
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
#else
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
            matrix.PreRotate(rotation_, center_.GetX(), center_.GetY());
        }

        std::vector<RSScalar> pos;
        std::vector<RSColorQuad> colors;
        ToDrawingColors(pos, colors);
        RSTileMode tileMode = RSTileMode::CLAMP;
        if (isRepeat_) {
            tileMode = RSTileMode::REPEAT;
        }
        return RSRecordingShaderEffect::CreateSweepGradient(
            center_, colors, pos, tileMode, startAngle_, endAngle_, &matrix);
    }
#endif

#ifndef USE_ROSEN_DRAWING
    static std::unique_ptr<GradientShader> CreateSweepGradient(
        const Gradient& gradient, const SkSize& size, float dipScale)
#else
    static std::unique_ptr<GradientShader> CreateSweepGradient(
        const Gradient& gradient, const RSSize& size, float dipScale)
#endif
    {
        auto sweepGradient = gradient.GetSweepGradient();
#ifndef USE_ROSEN_DRAWING
        SkPoint center = GetCenter(sweepGradient, size, dipScale);
#else
        RSPoint center = GetCenter(sweepGradient, size, dipScale);
#endif
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
#ifndef USE_ROSEN_DRAWING
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
#else
    static RSPoint GetCenter(const SweepGradient& sweepGradient, const RSSize& size, float dipScale)
    {
        RSPoint center = RSPoint(size.Width() / 2.0f, size.Height() / 2.0f);

        if (sweepGradient.centerX) {
            const auto& value = sweepGradient.centerX.value();
            center.SetX(
                static_cast<float>(value.Unit() == DimensionUnit::PERCENT ? value.Value() / 100.0f * size.Width()
                                                                          : value.ConvertToPx(dipScale)));
        }
        if (sweepGradient.centerY) {
            const auto& value = sweepGradient.centerY.value();
            center.SetY(
                static_cast<float>(value.Unit() == DimensionUnit::PERCENT ? value.Value() / 100.0f * size.Height()
                                                                          : value.ConvertToPx(dipScale)));
        }
        return center;
    }
#endif

    void AdjustAngle(float firstOffset, float lastOffset)
    {
        const auto delta = endAngle_ - startAngle_;
        endAngle_ = startAngle_ + delta * lastOffset;
        startAngle_ = startAngle_ + delta * firstOffset;
    }

private:
#ifndef USE_ROSEN_DRAWING
    SkPoint center_ { 0.0f, 0.0f };
#else
    RSPoint center_ { 0.0f, 0.0f };
#endif
    float startAngle_ { 0.0f };
    float endAngle_ { 0.0f };
    float rotation_ { 0.0f };
};

} // namespace

RosenDecorationPainter::RosenDecorationPainter(
    const RefPtr<Decoration>& decoration, const Rect& paintRect, const Size& paintSize, double dipScale)
    : dipScale_(dipScale), paintRect_(paintRect), decoration_(decoration), paintSize_(paintSize)
{}

#ifndef USE_ROSEN_DRAWING
void RosenDecorationPainter::PaintDecoration(const Offset& offset, SkCanvas* canvas, RenderContext& context)
#else
void RosenDecorationPainter::PaintDecoration(const Offset& offset, RSCanvas* canvas, RenderContext& context)
#endif
{
    auto rsNode = static_cast<RosenRenderContext*>(&context)->GetRSNode();
    if (!canvas || !paintSize_.IsValid() || !rsNode) {
        LOGE("PaintDecoration failed.");
        return;
    }

    Border borderFour;
    Rosen::Vector4f cornerRadius;
    if (decoration_) {
#ifndef USE_ROSEN_DRAWING
        SkPaint paint;

        if (opacity_ != UINT8_MAX) {
            paint.setAlpha(opacity_);
        }

        Border border = decoration_->GetBorder();
        PaintColorAndImage(offset, canvas, paint, context);
#else
        RSBrush brush;

        if (opacity_ != UINT8_MAX) {
            brush.SetAlpha(opacity_);
        }

        Border border = decoration_->GetBorder();
        PaintColorAndImage(offset, canvas, brush, context);
#endif
        if (border.HasRadius()) {
            cornerRadius.SetValues(NormalizeToPx(border.TopLeftRadius().GetX()),
                NormalizeToPx(border.TopRightRadius().GetX()), NormalizeToPx(border.BottomRightRadius().GetX()),
                NormalizeToPx(border.BottomLeftRadius().GetX()));
        }
        if (border.HasValue()) {
            borderFour = border;
        }
    }
    PaintBorder(rsNode, borderFour, dipScale_);
    rsNode->SetCornerRadius(cornerRadius);
}

#ifndef USE_ROSEN_DRAWING
void RosenDecorationPainter::PaintBorderImage(RefPtr<OHOS::Ace::Decoration>& decoration, Size& paintSize,
    const Offset& position, SkCanvas* canvas, const sk_sp<SkImage>& image, double dipScale)
{
    if (!decoration->GetHasBorderImageSource() && !decoration->GetHasBorderImageGradient()) {
        return;
    }
    // set AntiAlias
    SkPaint paint;
    paint.setAntiAlias(true);
    if (decoration->GetHasBorderImageSource()) {
        if (!image) {
            return;
        }
        canvas->save();

        BorderImagePainter borderImagePainter(paintSize, decoration, image, dipScale);
        borderImagePainter.InitPainter();
        borderImagePainter.PaintBorderImage(position, canvas, paint);
        canvas->restore();
    }
    if (decoration->GetHasBorderImageGradient()) {
        Gradient gradient = decoration->GetBorderImageGradient();
        if (!gradient.IsValid()) {
            LOGE("Gradient not valid");
            return;
        }
        if (NearZero(paintSize.Width()) || NearZero(paintSize.Height())) {
            return;
        }
        canvas->save();

        SkSize skPaintSize = SkSize::Make(paintSize.Width(), paintSize.Height());
        auto shader = CreateGradientShader(gradient, skPaintSize, dipScale);
        paint.setShader(std::move(shader));

        auto imageInfo = SkImageInfo::Make(paintSize.Width(), paintSize.Height(), SkColorType::kRGBA_8888_SkColorType,
            SkAlphaType::kOpaque_SkAlphaType);
        SkBitmap skBitmap;
        skBitmap.allocPixels(imageInfo);
        std::unique_ptr<SkCanvas> skCanvas = std::make_unique<SkCanvas>(skBitmap);
        skCanvas->drawPaint(paint);
        sk_sp<SkImage> skImage = SkImage::MakeFromBitmap(skBitmap);

        BorderImagePainter borderImagePainter(paintSize, decoration, skImage, dipScale);
        borderImagePainter.InitPainter();
        borderImagePainter.PaintBorderImage(position, canvas, paint);
        paint.setShader(nullptr);
        canvas->restore();
    }
}
#else
void RosenDecorationPainter::PaintBorderImage(RefPtr<OHOS::Ace::Decoration>& decoration, Size& paintSize,
    const Offset& position, RSCanvas* canvas, const std::shared_ptr<RSImage>& image, double dipScale)
{
    if (!decoration->GetHasBorderImageSource() && !decoration->GetHasBorderImageGradient()) {
        return;
    }
    // set AntiAlias
    RSBrush brush;
    brush.SetAntiAlias(true);
    if (decoration->GetHasBorderImageSource()) {
        if (!image) {
            return;
        }
        canvas->Save();

        BorderImagePainter borderImagePainter(paintSize, decoration, image, dipScale);
        borderImagePainter.InitPainter();
        borderImagePainter.PaintBorderImage(position, canvas, brush);
        canvas->Restore();
    }
    if (decoration->GetHasBorderImageGradient()) {
        Gradient gradient = decoration->GetBorderImageGradient();
        if (!gradient.IsValid()) {
            LOGE("Gradient not valid");
            return;
        }
        if (NearZero(paintSize.Width()) || NearZero(paintSize.Height())) {
            return;
        }
        canvas->Save();
        RSSize drPaintSize(static_cast<float>(paintSize.Width()), static_cast<float>(paintSize.Height()));
        auto shader = CreateGradientShader(gradient, drPaintSize, dipScale);
        brush.SetShaderEffect(shader);

        RSBitmapFormat bitmapFormat;
        bitmapFormat.colorType = RSColorType::COLORTYPE_RGBA_8888;
        bitmapFormat.alphaType = RSAlphaType::ALPHATYPE_OPAQUE;

        RSBitmap bitmap;
        bitmap.Build(paintSize.Width(), paintSize.Height(), bitmapFormat);

        std::unique_ptr<RSCanvas> drCanvas = std::make_unique<RSCanvas>();
        drCanvas->Bind(bitmap);
        drCanvas->DrawBackground(brush);

        auto image = std::make_shared<RSImage>();
        image->BuildFromBitmap(bitmap);

        BorderImagePainter borderImagePainter(paintSize, decoration, image, dipScale);
        borderImagePainter.InitPainter();
        borderImagePainter.PaintBorderImage(position, canvas, brush);
        brush.SetShaderEffect(nullptr);
        canvas->Restore();
    }
}
#endif

#ifndef USE_ROSEN_DRAWING
void RosenDecorationPainter::PaintDecoration(
    const Offset& offset, SkCanvas* canvas, RenderContext& context, const sk_sp<SkImage>& image)
{
    auto rsNode = static_cast<RosenRenderContext*>(&context)->GetRSNode();
    if (!canvas || !rsNode) {
        LOGE("PaintDecoration failed, canvas is null.");
        return;
    }
    if (decoration_ && rsNode) {
        canvas->save();
        SkPaint paint;

        if (opacity_ != UINT8_MAX) {
            paint.setAlpha(opacity_);
        }
        Border border = decoration_->GetBorder();
        PaintColorAndImage(offset, canvas, paint, context);
        if (border.HasValue()) {
            PaintBorder(rsNode, border, dipScale_);
            Gradient gradient = decoration_->GetBorderImageGradient();
            if (gradient.IsValid()) {
                if (NearZero(paintSize_.Width()) || NearZero(paintSize_.Height())) {
                    return;
                }
                auto size = SkSize::Make(GetLayoutSize().Width(), GetLayoutSize().Width());
                auto shader = CreateGradientShader(gradient, size);
#ifdef OHOS_PLATFORM
                rsNode->SetBackgroundShader(Rosen::RSShader::CreateRSShader(shader));
#endif
            }
        }
        canvas->restore();
    }
}
#else
void RosenDecorationPainter::PaintDecoration(
    const Offset& offset, RSCanvas* canvas, RenderContext& context, const std::shared_ptr<RSImage>& image)
{
    auto rsNode = static_cast<RosenRenderContext*>(&context)->GetRSNode();
    if (!canvas || !rsNode) {
        LOGE("PaintDecoration failed, canvas is null.");
        return;
    }
    if (decoration_ && rsNode) {
        canvas->Save();
        RSBrush brush;

        if (opacity_ != UINT8_MAX) {
            brush.SetAlpha(opacity_);
        }
        Border border = decoration_->GetBorder();
        PaintColorAndImage(offset, canvas, brush, context);
        if (border.HasValue()) {
            PaintBorder(rsNode, border, dipScale_);
            Gradient gradient = decoration_->GetBorderImageGradient();
            if (gradient.IsValid()) {
                if (NearZero(paintSize_.Width()) || NearZero(paintSize_.Height())) {
                    return;
                }
                auto size = RSSize(GetLayoutSize().Width(), GetLayoutSize().Width());
                auto shader = CreateGradientShader(gradient, size);
#ifdef OHOS_PLATFORM
                rsNode->SetBackgroundShader(Rosen::RSShader::CreateRSShader(shader));
#endif
            }
        }
        canvas->Restore();
    }
}
#endif

void RosenDecorationPainter::CheckWidth(const Border& border)
{
    if (NearZero(leftWidth_)) {
        leftWidth_ = NormalizeToPx(border.Left().GetWidth());
    }
    if (NearZero(topWidth_)) {
        topWidth_ = NormalizeToPx(border.Top().GetWidth());
    }
    if (NearZero(rightWidth_)) {
        rightWidth_ = NormalizeToPx(border.Right().GetWidth());
    }
    if (NearZero(bottomWidth_)) {
        bottomWidth_ = NormalizeToPx(border.Bottom().GetWidth());
    }
}

#ifndef USE_ROSEN_DRAWING
void RosenDecorationPainter::PaintGrayScale(
    const SkRRect& outerRRect, SkCanvas* canvas, const Dimension& grayscale, const Color& color)
{
    double scale = grayscale.Value();
    if (GreatNotEqual(scale, 0.0)) {
        if (canvas) {
            SkAutoCanvasRestore acr(canvas, true);
            canvas->clipRRect(outerRRect, true);
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
#else
void RosenDecorationPainter::PaintGrayScale(
    const RSRoundRect& outerRRect, RSCanvas* canvas, const Dimension& grayscale, const Color& color)
{
    double scale = grayscale.Value();
    if (GreatNotEqual(scale, 0.0)) {
        if (canvas) {
            RSAutoCanvasRestore acr(*canvas, true);
            canvas->ClipRoundRect(outerRRect, RSClipOp::INTERSECT, true);
            RSScalar matrix[20] = { 0 };
            matrix[0] = matrix[5] = matrix[10] = 0.2126f * scale;
            matrix[1] = matrix[6] = matrix[11] = 0.7152f * scale;
            matrix[2] = matrix[7] = matrix[12] = 0.0722f * scale;
            matrix[18] = 1.0f * scale;
            RSColorMatrix colorMatrix;
            colorMatrix.SetArray(matrix);
            std::shared_ptr<RSColorFilter> colorFilter = RSColorFilter::CreateMatrixColorFilter(colorMatrix);
            RSFilter filter;
            filter.SetColorFilter(colorFilter);

            RSBrush brush;
            brush.SetAntiAlias(true);
            brush.SetFilter(filter);
            RSSaveLayerOps slr(nullptr, &brush, RSSaveLayerOps::INIT_WITH_PREVIOUS);
            canvas->SaveLayer(slr);
        }
    }
}
#endif

#ifndef USE_ROSEN_DRAWING
void RosenDecorationPainter::PaintBrightness(
    const SkRRect& outerRRect, SkCanvas* canvas, const Dimension& brightness, const Color& color)
{
    double bright = brightness.Value();
    // brightness range = (0, 2)
    // skip painting when brightness is normal
    if (NearEqual(bright, 1.0)) {
        return;
    }
    if (canvas) {
        SkAutoCanvasRestore acr(canvas, true);
        canvas->clipRRect(outerRRect, true);
        SkPaint paint;
        paint.setAntiAlias(true);
        float matrix[20] = { 0 };
        // shift brightness to (-1, 1)
        bright = bright - 1;
        matrix[0] = matrix[6] = matrix[12] = matrix[18] = 1.0f;
        matrix[4] = matrix[9] = matrix[14] = bright;

        paint.setColorFilter(SkColorFilters::Matrix(matrix));
        SkCanvas::SaveLayerRec slr(nullptr, &paint, SkCanvas::kInitWithPrevious_SaveLayerFlag);
        canvas->saveLayer(slr);
    }
}
#else
void RosenDecorationPainter::PaintBrightness(
    const RSRoundRect& outerRRect, RSCanvas* canvas, const Dimension& brightness, const Color& color)
{
    double bright = brightness.Value();
    // brightness range = (0, 2)
    // skip painting when brightness is normal
    if (NearEqual(bright, 1.0)) {
        return;
    }
    if (canvas) {
        RSAutoCanvasRestore acr(*canvas, true);
        canvas->ClipRoundRect(outerRRect, RSClipOp::INTERSECT, true);
        RSBrush brush;
        brush.SetAntiAlias(true);
        RSScalar matrix[20] = { 0 };
        // shift brightness to (-1, 1)
        bright = bright - 1;
        matrix[0] = matrix[6] = matrix[12] = matrix[18] = 1.0f;
        matrix[4] = matrix[9] = matrix[14] = bright;
        RSColorMatrix colorMatrix;
        colorMatrix.SetArray(matrix);
        std::shared_ptr<RSColorFilter> colorFilter = RSColorFilter::CreateMatrixColorFilter(colorMatrix);
        RSFilter filter;
        filter.SetColorFilter(colorFilter);
        RSSaveLayerOps slr(nullptr, &brush, RSSaveLayerOps::INIT_WITH_PREVIOUS);
        canvas->SaveLayer(slr);
    }
}
#endif

#ifndef USE_ROSEN_DRAWING
void RosenDecorationPainter::PaintContrast(
    const SkRRect& outerRRect, SkCanvas* canvas, const Dimension& contrast, const Color& color)
{
    double contrasts = contrast.Value();
    // skip painting if contrast is normal
    if (NearEqual(contrasts, 1.0)) {
        return;
    }
    if (canvas) {
        SkAutoCanvasRestore acr(canvas, true);
        canvas->clipRRect(outerRRect, true);
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
#else
void RosenDecorationPainter::PaintContrast(
    const RSRoundRect& outerRRect, RSCanvas* canvas, const Dimension& contrast, const Color& color)
{
    double contrasts = contrast.Value();
    // skip painting if contrast is normal
    if (NearEqual(contrasts, 1.0)) {
        return;
    }
    if (canvas) {
        RSAutoCanvasRestore acr(*canvas, true);
        canvas->ClipRoundRect(outerRRect, RSClipOp::INTERSECT, true);
        RSBrush brush;
        brush.SetAntiAlias(true);
        RSScalar matrix[20] = { 0 };
        matrix[0] = matrix[6] = matrix[12] = contrasts;
        matrix[4] = matrix[9] = matrix[14] = 128 * (1 - contrasts) / 255;
        matrix[18] = 1.0f;
        RSColorMatrix colorMatrix;
        colorMatrix.SetArray(matrix);
        std::shared_ptr<RSColorFilter> colorFilter = RSColorFilter::CreateMatrixColorFilter(colorMatrix);
        RSFilter filter;
        filter.SetColorFilter(colorFilter);
        brush.SetFilter(filter);
        RSSaveLayerOps slr(nullptr, &brush, RSSaveLayerOps::INIT_WITH_PREVIOUS);
        canvas->SaveLayer(slr);
    }
}
#endif

#ifndef USE_ROSEN_DRAWING
void RosenDecorationPainter::PaintColorBlend(
    const SkRRect& outerRRect, SkCanvas* canvas, const Color& colorBlend, const Color& color)
{
    if (colorBlend.GetValue() != COLOR_MASK) {
        if (canvas) {
            SkAutoCanvasRestore acr(canvas, true);
            canvas->clipRRect(outerRRect, true);
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
#else
void RosenDecorationPainter::PaintColorBlend(
    const RSRoundRect& outerRRect, RSCanvas* canvas, const Color& colorBlend, const Color& color)
{
    if (colorBlend.GetValue() != COLOR_MASK) {
        if (canvas) {
            RSAutoCanvasRestore acr(*canvas, true);
            canvas->ClipRoundRect(outerRRect, RSClipOp::INTERSECT, true);
            std::shared_ptr<RSColorFilter> colorFilter =
                RSColorFilter::CreateBlendModeColorFilter(colorBlend.GetValue(), RSBlendMode::PLUS);
            RSFilter filter;
            filter.SetColorFilter(colorFilter);

            RSBrush brush;
            brush.SetAntiAlias(true);
            brush.SetFilter(filter);
            RSSaveLayerOps slr(nullptr, &brush, RSSaveLayerOps::INIT_WITH_PREVIOUS);
            canvas->SaveLayer(slr);
        }
    }
}
#endif

#ifndef USE_ROSEN_DRAWING
void RosenDecorationPainter::PaintSaturate(
    const SkRRect& outerRRect, SkCanvas* canvas, const Dimension& saturate, const Color& color)
{
    double saturates = saturate.Value();
    if (!NearEqual(saturates, 1.0) && GreatOrEqual(saturates, 0.0)) {
        if (canvas) {
            SkAutoCanvasRestore acr(canvas, true);
            canvas->clipRRect(outerRRect, true);
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
#else
void RosenDecorationPainter::PaintSaturate(
    const RSRoundRect& outerRRect, RSCanvas* canvas, const Dimension& saturate, const Color& color)
{
    double saturates = saturate.Value();
    if (!NearEqual(saturates, 1.0) && GreatOrEqual(saturates, 0.0)) {
        if (canvas) {
            RSAutoCanvasRestore acr(*canvas, true);
            canvas->ClipRoundRect(outerRRect, RSClipOp::INTERSECT, true);
            RSBrush brush;
            brush.SetAntiAlias(true);
            RSScalar matrix[20] = { 0 };
            matrix[0] = 0.3086f * (1 - saturates) + saturates;
            matrix[1] = matrix[11] = 0.6094f * (1 - saturates);
            matrix[2] = matrix[7] = 0.0820f * (1 - saturates);
            matrix[5] = matrix[10] = 0.3086f * (1 - saturates);
            matrix[6] = 0.6094f * (1 - saturates) + saturates;
            matrix[12] = 0.0820f * (1 - saturates) + saturates;
            matrix[18] = 1.0f;
            RSColorMatrix colorMatrix;
            colorMatrix.SetArray(matrix);
            std::shared_ptr<RSColorFilter> colorFilter = RSColorFilter::CreateMatrixColorFilter(colorMatrix);
            RSFilter filter;
            filter.SetColorFilter(colorFilter);
            brush.SetFilter(filter);
            RSSaveLayerOps slr(nullptr, &brush, RSSaveLayerOps::INIT_WITH_PREVIOUS);
            canvas->SaveLayer(slr);
        }
    }
}
#endif

#ifndef USE_ROSEN_DRAWING
void RosenDecorationPainter::PaintSepia(
    const SkRRect& outerRRect, SkCanvas* canvas, const Dimension& sepia, const Color& color)
{
    double sepias = sepia.Value();
    if (sepias > 1.0) {
        sepias = 1.0;
    }
    if (GreatNotEqual(sepias, 0.0)) {
        if (canvas) {
            SkAutoCanvasRestore acr(canvas, true);
            canvas->clipRRect(outerRRect, true);
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
#else
void RosenDecorationPainter::PaintSepia(
    const RSRoundRect& outerRRect, RSCanvas* canvas, const Dimension& sepia, const Color& color)
{
    double sepias = sepia.Value();
    if (sepias > 1.0) {
        sepias = 1.0;
    }
    if (GreatNotEqual(sepias, 0.0)) {
        if (canvas) {
            RSAutoCanvasRestore acr(*canvas, true);
            canvas->ClipRoundRect(outerRRect, RSClipOp::INTERSECT, true);
            RSBrush brush;
            brush.SetAntiAlias(true);
            RSScalar matrix[20] = { 0 };
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
            std::shared_ptr<RSColorFilter> colorFilter = RSColorFilter::CreateMatrixColorFilter(colorMatrix);
            RSFilter filter;
            filter.SetColorFilter(colorFilter);

            brush.SetFilter(filter);
            RSSaveLayerOps slr(nullptr, &brush, RSSaveLayerOps::INIT_WITH_PREVIOUS);
            canvas->SaveLayer(slr);
        }
    }
}
#endif

#ifndef USE_ROSEN_DRAWING
void RosenDecorationPainter::PaintInvert(
    const SkRRect& outerRRect, SkCanvas* canvas, const Dimension& invert, const Color& color)
{
    double inverts = invert.Value();
    if (GreatNotEqual(inverts, 0.0)) {
        if (canvas) {
            SkAutoCanvasRestore acr(canvas, true);
            canvas->clipRRect(outerRRect, true);
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
#else
void RosenDecorationPainter::PaintInvert(
    const RSRoundRect& outerRRect, RSCanvas* canvas, const Dimension& invert, const Color& color)
{
    double inverts = invert.Value();
    if (GreatNotEqual(inverts, 0.0)) {
        if (canvas) {
            RSAutoCanvasRestore acr(*canvas, true);
            canvas->ClipRoundRect(outerRRect, RSClipOp::INTERSECT, true);
            RSBrush brush;
            brush.SetAntiAlias(true);
            RSScalar matrix[20] = { 0 };
            if (inverts > 1.0) {
                inverts = 1.0;
            }
            // complete color invert when dstRGB = 1 - srcRGB
            // map (0, 1) to (1, -1)
            matrix[0] = matrix[6] = matrix[12] = -1.0f * inverts;
            matrix[18] = 1.0f;
            // inverts = 0.5 -> RGB = (0.5, 0.5, 0.5) -> image completely gray
            matrix[4] = matrix[9] = matrix[14] = 1.0f;
            RSColorMatrix colorMatrix;
            colorMatrix.SetArray(matrix);
            std::shared_ptr<RSColorFilter> colorFilter = RSColorFilter::CreateMatrixColorFilter(colorMatrix);
            RSFilter filter;
            filter.SetColorFilter(colorFilter);

            brush.SetFilter(filter);
            RSSaveLayerOps slr(nullptr, &brush, RSSaveLayerOps::INIT_WITH_PREVIOUS);
            canvas->SaveLayer(slr);
        }
    }
}
#endif

#ifndef USE_ROSEN_DRAWING
void RosenDecorationPainter::PaintHueRotate(
    const SkRRect& outerRRect, SkCanvas* canvas, const float& hueRotate, const Color& color)
{
    float hueRotates = hueRotate;
    if (GreatNotEqual(hueRotates, 0.0)) {
        if (canvas) {
            SkAutoCanvasRestore acr(canvas, true);
            canvas->clipRRect(outerRRect, true);
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
#else
void RosenDecorationPainter::PaintHueRotate(
    const RSRoundRect& outerRRect, RSCanvas* canvas, const float& hueRotate, const Color& color)
{
    float hueRotates = hueRotate;
    if (GreatNotEqual(hueRotates, 0.0)) {
        if (canvas) {
            RSAutoCanvasRestore acr(*canvas, true);
            canvas->ClipRoundRect(outerRRect, RSClipOp::INTERSECT, true);
            RSBrush brush;
            brush.SetAntiAlias(true);
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
            RSColorMatrix colorMatrix;
            colorMatrix.SetArray(matrix);
            std::shared_ptr<RSColorFilter> colorFilter = RSColorFilter::CreateMatrixColorFilter(colorMatrix);
            RSFilter filter;
            filter.SetColorFilter(colorFilter);

            brush.SetFilter(filter);
            RSSaveLayerOps slr(nullptr, &brush, RSSaveLayerOps::INIT_WITH_PREVIOUS);
            canvas->SaveLayer(slr);
        }
    }
}
#endif

void RosenDecorationPainter::PaintBlur(RenderContext& context, const Dimension& blurRadius)
{
    auto rsNode = static_cast<RosenRenderContext*>(&context)->GetRSNode();
    auto radius = ConvertRadiusToSigma(NormalizeToPx(blurRadius));
    if (GreatNotEqual(radius, 0.0)) {
        if (rsNode) {
            float backblurRadius = ConvertRadiusToSigma(radius);
            auto backFilter = Rosen::RSFilter::CreateBlurFilter(backblurRadius, backblurRadius);
            rsNode->SetBackgroundFilter(backFilter);
        }
    }
}

void RosenDecorationPainter::PaintBorder(std::shared_ptr<RSNode>& rsNode, Border& border, double dipScale)
{
    if (!rsNode) {
        return;
    }
    AdjustBorderStyle(border);
    rsNode->SetBorderColor(border.Left().GetColor().GetValue(), border.Top().GetColor().GetValue(),
        border.Right().GetColor().GetValue(), border.Bottom().GetColor().GetValue());
    rsNode->SetBorderWidth(border.Left().GetWidth().ConvertToPx(dipScale),
        border.Top().GetWidth().ConvertToPx(dipScale), border.Right().GetWidth().ConvertToPx(dipScale),
        border.Bottom().GetWidth().ConvertToPx(dipScale));
    rsNode->SetBorderStyle(static_cast<uint32_t>(border.Left().GetBorderStyle()),
        static_cast<uint32_t>(border.Top().GetBorderStyle()), static_cast<uint32_t>(border.Right().GetBorderStyle()),
        static_cast<uint32_t>(border.Bottom().GetBorderStyle()));
}

#ifndef USE_ROSEN_DRAWING
SkRRect RosenDecorationPainter::GetBoxOuterRRect(const Offset& offset)
{
    SkRRect outerRRect;
    if (decoration_) {
        Border border = decoration_->GetBorder();
        outerRRect = GetBoxRRect(offset + margin_.GetOffsetInPx(scale_), border, 0.0, true);
    } else {
        Rect paintSize = paintRect_ + offset;
        outerRRect = SkRRect::MakeRect(
            SkRect::MakeLTRB(paintSize.Left(), paintSize.Top(), paintSize.Right(), paintSize.Bottom()));
    }
    return outerRRect;
}
#else
RSRoundRect RosenDecorationPainter::GetBoxOuterRRect(const Offset& offset)
{
    RSRoundRect outerRRect;
    if (decoration_) {
        Border border = decoration_->GetBorder();
        outerRRect = GetBoxRRect(offset + margin_.GetOffsetInPx(scale_), border, 0.0, true);
    } else {
        Rect paintSize = paintRect_ + offset;
        outerRRect.SetRect(RSRect(paintSize.Left(), paintSize.Top(), paintSize.Right(), paintSize.Bottom()));
    }
    return outerRRect;
}
#endif

#ifndef USE_ROSEN_DRAWING
void RosenDecorationPainter::PaintColorAndImage(
    const Offset& offset, SkCanvas* canvas, SkPaint& paint, RenderContext& renderContext)
#else
void RosenDecorationPainter::PaintColorAndImage(
    const Offset& offset, RSCanvas* canvas, RSBrush& brush, RenderContext& renderContext)
#endif
{
    auto rsNode = static_cast<RosenRenderContext*>(&renderContext)->GetRSNode();
    if (!decoration_ || !rsNode) {
        return;
    }

    // paint backColor
    bool paintBgColor = false;
#ifndef USE_ROSEN_DRAWING
    paint.setStyle(SkPaint::Style::kFill_Style);
#endif
    Color backColor = decoration_->GetBackgroundColor();
    Color animationColor = decoration_->GetAnimationColor();
    if (backColor != Color::TRANSPARENT) {
        rsNode->SetBackgroundColor(backColor.GetValue());
        paintBgColor = true;
    } else {
        rsNode->SetBackgroundColor(Color::TRANSPARENT.GetValue());
    }

    if (animationColor != Color::TRANSPARENT) {
        rsNode->SetBackgroundColor(animationColor.GetValue());
    }

    // paint background image.
    RefPtr<ArcBackground> arcBG = decoration_->GetArcBackground();
    if (arcBG) {
        Color arcColor = arcBG->GetColor();
        if (arcColor != Color::TRANSPARENT) {
#ifndef USE_ROSEN_DRAWING
            paint.setColor(arcColor.GetValue());
            canvas->drawCircle(arcBG->GetCenter().GetX(), arcBG->GetCenter().GetY(), arcBG->GetRadius(), paint);
#else
            brush.SetColor(arcColor.GetValue());
            canvas->AttachBrush(brush);
            RSPoint point(arcBG->GetCenter().GetX(), arcBG->GetCenter().GetY());
            canvas->DrawCircle(point, arcBG->GetRadius());
            canvas->DetachBrush();
#endif
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
        PaintGradient(renderContext);
    }
}

#ifndef USE_ROSEN_DRAWING
SkRRect RosenDecorationPainter::GetOuterRRect(const Offset& offset, const Border& border)
{
    SkRRect rrect;
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
    rrect.setRectRadii(outerRect, outerRadii);
    return rrect;
}
#else
RSRoundRect RosenDecorationPainter::GetOuterRRect(const Offset& offset, const Border& border)
{
    float topLeftRadiusX = NormalizeToPx(border.TopLeftRadius().GetX());
    float topLeftRadiusY = NormalizeToPx(border.TopLeftRadius().GetY());
    float topRightRadiusX = NormalizeToPx(border.TopRightRadius().GetX());
    float topRightRadiusY = NormalizeToPx(border.TopRightRadius().GetY());
    float bottomRightRadiusX = NormalizeToPx(border.BottomRightRadius().GetX());
    float bottomRightRadiusY = NormalizeToPx(border.BottomRightRadius().GetY());
    float bottomLeftRadiusX = NormalizeToPx(border.BottomLeftRadius().GetX());
    float bottomLeftRadiusY = NormalizeToPx(border.BottomLeftRadius().GetY());
    RSRect outerRect =
        RSRect(offset.GetX(), offset.GetY(), paintSize_.Width() + offset.GetX(), paintSize_.Height() + offset.GetY());
    std::vector<RSPoint> outerRadii;
    outerRadii.push_back(RSPoint(topLeftRadiusX, topLeftRadiusY));
    outerRadii.push_back(RSPoint(topRightRadiusX, topRightRadiusY));
    outerRadii.push_back(RSPoint(bottomRightRadiusX, bottomRightRadiusY));
    outerRadii.push_back(RSPoint(bottomLeftRadiusX, bottomLeftRadiusY));
    return RSRoundRect(outerRect, outerRadii);
}
#endif

#ifndef USE_ROSEN_DRAWING
SkRRect RosenDecorationPainter::GetInnerRRect(const Offset& offset, const Border& border)
{
    SkRRect rrect;
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
    rrect.setRectRadii(innerRect, innerRadii);
    return rrect;
}
#else
RSRoundRect RosenDecorationPainter::GetInnerRRect(const Offset& offset, const Border& border)
{
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
    RSRect innerRect = RSRect(x + leftW, y + topW, w - rightW + x, h - bottomW + y);
    std::vector<RSPoint> innerRadii;
    innerRadii.push_back(RSPoint(std::max(0.0f, tlX - leftW), std::max(0.0f, tlY - topW)));
    innerRadii.push_back(RSPoint(std::max(0.0f, trX - rightW), std::max(0.0f, trY - topW)));
    innerRadii.push_back(RSPoint(std::max(0.0f, brX - rightW), std::max(0.0f, brY - bottomW)));
    innerRadii.push_back(RSPoint(std::max(0.0f, blX - leftW), std::max(0.0f, blY - bottomW)));
    return RSRoundRect(innerRect, innerRadii);
}
#endif

#ifndef USE_ROSEN_DRAWING
SkRRect RosenDecorationPainter::GetClipRRect(const Offset& offset, const Border& border)
{
    SkRRect rrect;
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
    rrect.setRectRadii(SkRect::MakeXYWH(x, y, w, h), outerRadii);
    return rrect;
}
#else
RSRoundRect RosenDecorationPainter::GetClipRRect(const Offset& offset, const Border& border)
{
    float bottomRightRadiusX = NormalizeToPx(border.BottomRightRadius().GetX());
    float bottomRightRadiusY = NormalizeToPx(border.BottomRightRadius().GetY());
    float bottomLeftRadiusX = NormalizeToPx(border.BottomLeftRadius().GetX());
    float bottomLeftRadiusY = NormalizeToPx(border.BottomLeftRadius().GetY());
    float topLeftRadiusX = NormalizeToPx(border.TopLeftRadius().GetX());
    float topLeftRadiusY = NormalizeToPx(border.TopLeftRadius().GetY());
    float topRightRadiusX = NormalizeToPx(border.TopRightRadius().GetX());
    float topRightRadiusY = NormalizeToPx(border.TopRightRadius().GetY());
    std::vector<RSPoint> outerRadii;
    outerRadii.push_back(RSPoint(topLeftRadiusX, topLeftRadiusY));
    outerRadii.push_back(RSPoint(topRightRadiusX, topRightRadiusY));
    outerRadii.push_back(RSPoint(bottomRightRadiusX, bottomRightRadiusY));
    outerRadii.push_back(RSPoint(bottomLeftRadiusX, bottomLeftRadiusY));
    float leftW = NormalizeToPx(border.Left().GetWidth());
    float topW = NormalizeToPx(border.Top().GetWidth());
    float rightW = NormalizeToPx(border.Right().GetWidth());
    float bottomW = NormalizeToPx(border.Bottom().GetWidth());
    float x = offset.GetX() + leftW / 2.0f;
    float y = offset.GetY() + topW / 2.0f;
    float w = paintSize_.Width() - (leftW + rightW) / 2.0f;
    float h = paintSize_.Height() - (topW + bottomW) / 2.0f;
    RSRect outerRect = RSRect(x, y, w + x, h + y);
    return RSRoundRect(outerRect, outerRadii);
}
#endif

#ifndef USE_ROSEN_DRAWING
bool RosenDecorationPainter::CanUseFillStyle(const Border& border, SkPaint& paint)
#else
bool RosenDecorationPainter::CanUseFillStyle(const Border& border, RSBrush& brush)
#endif
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
#ifndef USE_ROSEN_DRAWING
    paint.setStyle(SkPaint::Style::kFill_Style);
    paint.setColor(border.Left().GetColor().GetValue());
#else
    brush.SetColor(border.Left().GetColor().GetValue());
#endif
    return true;
}

#ifndef USE_ROSEN_DRAWING
bool RosenDecorationPainter::CanUsePathRRect(const Border& border, SkPaint& paint)
#else
bool RosenDecorationPainter::CanUsePathRRect(const Border& border, RSPen& pen)
#endif
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
#ifndef USE_ROSEN_DRAWING
    SetBorderStyle(border.Left(), paint, false);
#else
    SetBorderStyle(border.Left(), pen, false);
#endif
    return true;
}

bool RosenDecorationPainter::CanUseFourLine(const Border& border)
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

bool RosenDecorationPainter::CanUseInnerRRect(const Border& border)
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

#ifndef USE_ROSEN_DRAWING
SkRRect RosenDecorationPainter::GetBoxRRect(
    const Offset& offset, const Border& border, double shrinkFactor, bool isRound)
{
    SkRRect rrect;
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
    rrect.setRectRadii(skRect, fRadii);
    return rrect;
}
#else
RSRoundRect RosenDecorationPainter::GetBoxRRect(
    const Offset& offset, const Border& border, double shrinkFactor, bool isRound)
{
    RSRoundRect rrect;
    RSRect rect;
    if (CheckBorderEdgeForRRect(border)) {
        std::vector<RSPoint> fRadii;
        BorderEdge borderEdge = border.Left();
        double borderWidth = NormalizeToPx(borderEdge.GetWidth());
        rect = RSRect(static_cast<RSScalar>(offset.GetX() + shrinkFactor * borderWidth),
            static_cast<RSScalar>(offset.GetY() + shrinkFactor * borderWidth),
            static_cast<RSScalar>(paintSize_.Width() - shrinkFactor * borderWidth + offset.GetX()),
            static_cast<RSScalar>(paintSize_.Height() - shrinkFactor * borderWidth + offset.GetY()));
        if (isRound) {
            fRadii.push_back(
                RSPoint(static_cast<RSScalar>(
                            std::max(NormalizeToPx(border.TopLeftRadius().GetX()) - shrinkFactor * borderWidth, 0.0)),
                    static_cast<RSScalar>(
                        std::max(NormalizeToPx(border.TopLeftRadius().GetY()) - shrinkFactor * borderWidth, 0.0))));
            fRadii.push_back(
                RSPoint(static_cast<RSScalar>(
                            std::max(NormalizeToPx(border.TopRightRadius().GetX()) - shrinkFactor * borderWidth, 0.0)),
                    static_cast<RSScalar>(
                        std::max(NormalizeToPx(border.TopRightRadius().GetY()) - shrinkFactor * borderWidth, 0.0))));
            fRadii.push_back(
                RSPoint(static_cast<RSScalar>(std::max(
                            NormalizeToPx(border.BottomRightRadius().GetX()) - shrinkFactor * borderWidth, 0.0)),
                    static_cast<RSScalar>(
                        std::max(NormalizeToPx(border.BottomRightRadius().GetY()) - shrinkFactor * borderWidth, 0.0))));
            fRadii.push_back(
                RSPoint(static_cast<RSScalar>(std::max(
                            NormalizeToPx(border.BottomLeftRadius().GetX()) - shrinkFactor * borderWidth, 0.0)),
                    static_cast<RSScalar>(
                        std::max(NormalizeToPx(border.BottomLeftRadius().GetY()) - shrinkFactor * borderWidth, 0.0))));
        }
        rrect = RSRoundRect(rect, fRadii);
    } else {
        rect = RSRect(static_cast<RSScalar>(offset.GetX() + shrinkFactor * NormalizeToPx(border.Left().GetWidth())),
            static_cast<RSScalar>(offset.GetY() + shrinkFactor * NormalizeToPx(border.Top().GetWidth())),
            static_cast<RSScalar>(paintSize_.Width() -
                                  shrinkFactor * DOUBLE_WIDTH * NormalizeToPx(border.Right().GetWidth()) +
                                  offset.GetX() + shrinkFactor * NormalizeToPx(border.Left().GetWidth())),
            static_cast<RSScalar>(
                paintSize_.Height() -
                shrinkFactor * (NormalizeToPx(border.Bottom().GetWidth()) + NormalizeToPx(border.Top().GetWidth())) +
                offset.GetY() + shrinkFactor * NormalizeToPx(border.Top().GetWidth())));
        rrect.SetRect(rect);
    }
    return rrect;
}
#endif

#ifndef USE_ROSEN_DRAWING
void RosenDecorationPainter::SetBorderStyle(
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
                spaceBetweenDot = width * 2.0; // 2.0: Double factor.
            }
            dotPath.addCircle(0.0f, 0.0f, SkDoubleToScalar(width / 2.0)); // 2.0: Average factor.
            paint.setPathEffect(
                SkPath1DPathEffect::Make(dotPath, spaceBetweenDot, 0.0, SkPath1DPathEffect::kRotate_Style));
        } else if (borderEdge.GetBorderStyle() == BorderStyle::DASHED) {
            double addLen = 0.0; // When left < 2 * gap, splits left to gaps.
            double delLen = 0.0; // When left > 2 * gap, add one dash and shortening them.
            if (!NearZero(borderLength)) {
                double count = borderLength / width;
                double leftLen = fmod((count - DASHED_LINE_LENGTH), (DASHED_LINE_LENGTH + 1));
                if (NearZero(count - DASHED_LINE_LENGTH)) {
                    return;
                }
                if (leftLen > DASHED_LINE_LENGTH - 1) {
                    delLen = (DASHED_LINE_LENGTH + 1 - leftLen) * width /
                             static_cast<int32_t>((count - DASHED_LINE_LENGTH) / (DASHED_LINE_LENGTH + 1) + DEL_NUM);
                } else {
                    addLen =
                        leftLen * width / static_cast<int32_t>((count - DASHED_LINE_LENGTH) / (DASHED_LINE_LENGTH + 1));
                }
            }
            const float intervals[] = { width * DASHED_LINE_LENGTH - delLen, width + addLen };
            paint.setPathEffect(SkDashPathEffect::Make(intervals, SK_ARRAY_COUNT(intervals), 0.0));
        } else {
            paint.setPathEffect(nullptr);
        }
    }
}
#else
void RosenDecorationPainter::SetBorderStyle(
    const BorderEdge& borderEdge, RSPen& pen, bool useDefaultColor, double spaceBetweenDot, double borderLength)
{
    if (borderEdge.HasValue()) {
        double width = NormalizeToPx(borderEdge.GetWidth());
        uint32_t color = useDefaultColor ? Color::BLACK.GetValue() : borderEdge.GetColor().GetValue();
        pen.SetWidth(width);
        pen.SetColor(color);
        if (borderEdge.GetBorderStyle() == BorderStyle::DOTTED) {
            RSPath dotPath;
            if (NearZero(spaceBetweenDot)) {
                spaceBetweenDot = width * 2.0; // 2.0: Double factor.
            }
            dotPath.AddCircle(0.0f, 0.0f, static_cast<RSScalar>(width / 2.0)); // 2.0: Average factor.
            pen.SetPathEffect(
                RSPathEffect::CreatePathDashEffect(dotPath, spaceBetweenDot, 0.0, RSPathDashStyle::ROTATE));
        } else if (borderEdge.GetBorderStyle() == BorderStyle::DASHED) {
            double addLen = 0.0; // When left < 2 * gap, splits left to gaps.
            double delLen = 0.0; // When left > 2 * gap, add one dash and shortening them.
            if (!NearZero(borderLength)) {
                double count = borderLength / width;
                double leftLen = fmod((count - DASHED_LINE_LENGTH), (DASHED_LINE_LENGTH + 1));
                if (NearZero(count - DASHED_LINE_LENGTH)) {
                    return;
                }
                if (leftLen > DASHED_LINE_LENGTH - 1) {
                    delLen = (DASHED_LINE_LENGTH + 1 - leftLen) * width /
                             static_cast<int32_t>((count - DASHED_LINE_LENGTH) / (DASHED_LINE_LENGTH + 1) + DEL_NUM);
                } else {
                    addLen =
                        leftLen * width / static_cast<int32_t>((count - DASHED_LINE_LENGTH) / (DASHED_LINE_LENGTH + 1));
                }
            }
            const RSScalar intervals[] = { width * DASHED_LINE_LENGTH - delLen, width + addLen };
            pen.SetPathEffect(RSPathEffect::CreateDashPathEffect(intervals, sizeof(intervals) / sizeof(RSScalar), 0.0));
        } else {
            pen.SetPathEffect(nullptr);
        }
    }
}
#endif

#ifndef USE_ROSEN_DRAWING
void RosenDecorationPainter::PaintBorder(const Offset& offset, const Border& border, SkCanvas* canvas, SkPaint& paint)
#else
void RosenDecorationPainter::PaintBorder(const Offset& offset, const Border& border, RSCanvas* canvas, RSPen& pen)
#endif
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
#ifndef USE_ROSEN_DRAWING
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
#else
    if (border.Top().HasValue() && !NearZero(topW)) {
        // Draw Top Border
        SetBorderStyle(border.Top(), pen, false);
        auto rectStart = RSRect(x, y, tlX * 2.0f + x, tlY * 2.0f + y);
        auto rectEnd = RSRect(x + w - trX * 2.0f, y, x + w, trY * 2.0f + y);
        RSRecordingPath topBorder;
        pen.SetWidth(maxW);
        if (border.Top().GetBorderStyle() != BorderStyle::DOTTED) {
            pen.SetWidth(maxW);
        }
        if (NearZero(tlX) || NearZero(tlY) || NearZero(trX) || NearZero(trY)) {
            canvas->Save();
        }
        if (NearZero(tlX) && !NearZero(leftW)) {
            topBorder.MoveTo(offsetX, y);
            topBorder.LineTo(x, y);
            RSRecordingPath topClipPath;
            topClipPath.MoveTo(offsetX - leftW, offsetY - topW);
            topClipPath.LineTo(offsetX + leftW * EXTEND, offsetY + topW * EXTEND);
            topClipPath.LineTo(offsetX, offsetY + topW * EXTEND);
            topClipPath.Close();
            canvas->ClipPath(topClipPath, RSClipOp::DIFFERENCE, true);
        }
        topBorder.ArcTo(rectStart.GetLeft(), rectStart.GetTop(), rectStart.GetRight(), rectStart.GetBottom(),
            TOP_START, SWEEP_ANGLE);
        topBorder.ArcTo(rectEnd.GetLeft(), rectEnd.GetTop(), rectEnd.GetRight(), rectEnd.GetBottom(),
            TOP_END, SWEEP_ANGLE + 0.5f);
        if (NearZero(trX) && !NearZero(rightW)) {
            topBorder.LineTo(offsetX + width, y);
            RSRecordingPath topClipPath;
            topClipPath.MoveTo(offsetX + width + rightW, offsetY - topW);
            topClipPath.LineTo(offsetX + width - rightW * EXTEND, offsetY + topW * EXTEND);
            topClipPath.LineTo(offsetX + width, offsetY + topW * EXTEND);
            topClipPath.Close();
            canvas->ClipPath(topClipPath, RSClipOp::DIFFERENCE, true);
        }
        canvas->AttachPen(pen);
        canvas->DrawPath(topBorder);
        if (NearZero(tlX) || NearZero(tlY) || NearZero(trX) || NearZero(trY)) {
            canvas->Restore();
        }
        canvas->DetachPen();
    }
    if (border.Right().HasValue() && !NearZero(rightW)) {
        // Draw Right Border
        SetBorderStyle(border.Right(), pen, false);
        auto rectStart = RSRect(x + w - trX * 2.0f, y, x + w, trY * 2.0f + y);
        auto rectEnd = RSRect(x + w - brX * 2.0f, y + h - brY * 2.0f, x + w, y + h);
        RSRecordingPath rightBorder;
        pen.SetWidth(maxW);
        if (border.Right().GetBorderStyle() != BorderStyle::DOTTED) {
            pen.SetWidth(maxW);
        }
        if (NearZero(trX) || NearZero(trY) || NearZero(brX) || NearZero(brY)) {
            canvas->Save();
        }
        if (NearZero(trX) && !NearZero(topW)) {
            rightBorder.MoveTo(offsetX + width - rightW / 2.0f, offsetY);
            rightBorder.LineTo(x + w - trX * 2.0f, y);
            RSRecordingPath rightClipPath;
            rightClipPath.MoveTo(offsetX + width + rightW, offsetY - topW);
            rightClipPath.LineTo(offsetX + width - rightW * EXTEND, offsetY + topW * EXTEND);
            rightClipPath.LineTo(offsetX + width - rightW * EXTEND, offsetY);
            rightClipPath.Close();
            canvas->ClipPath(rightClipPath, RSClipOp::DIFFERENCE, true);
        }
        rightBorder.ArcTo(rectStart.GetLeft(), rectStart.GetTop(), rectStart.GetRight(), rectStart.GetBottom(),
            RIGHT_START, SWEEP_ANGLE);
        rightBorder.ArcTo(rectEnd.GetLeft(), rectEnd.GetTop(), rectEnd.GetRight(), rectEnd.GetBottom(),
            RIGHT_END, SWEEP_ANGLE + 0.5f);
        if (NearZero(brX) && !NearZero(bottomW)) {
            rightBorder.LineTo(offsetX + width - rightW / 2.0f, offsetY + height);
            RSRecordingPath rightClipPath;
            rightClipPath.MoveTo(offsetX + width + rightW, offsetY + height + bottomW);
            rightClipPath.LineTo(offsetX + width - rightW * EXTEND, offsetY + height - bottomW * EXTEND);
            rightClipPath.LineTo(offsetX + width - rightW * EXTEND, offsetY + height);
            rightClipPath.Close();
            canvas->ClipPath(rightClipPath, RSClipOp::DIFFERENCE, true);
        }
        canvas->AttachPen(pen);
        canvas->DrawPath(rightBorder);
        if (NearZero(trX) || NearZero(trY) || NearZero(brX) || NearZero(brY)) {
            canvas->Restore();
        }
        canvas->DetachPen();
    }
    if (border.Bottom().HasValue() && !NearZero(bottomW)) {
        // Draw Bottom Border
        SetBorderStyle(border.Bottom(), pen, false);
        auto rectStart = RSRect(x + w - brX * 2.0f, y + h - brY * 2.0f, x + w, y + h);
        auto rectEnd = RSRect(x, y + h - blY * 2.0f, blX * 2.0f + x, y + h);
        RSRecordingPath bottomBorder;
        if (border.Bottom().GetBorderStyle() != BorderStyle::DOTTED) {
            pen.SetWidth(maxW);
        }
        if (NearZero(brX) || NearZero(brY) || NearZero(blX) || NearZero(blY)) {
            canvas->Save();
        }
        if (NearZero(brX) && !NearZero(rightW)) {
            bottomBorder.MoveTo(offsetX + width, offsetY + height - bottomW / 2.0f);
            bottomBorder.LineTo(x + w - brX * 2.0f, y + h - brY * 2.0f);
            RSRecordingPath bottomClipPath;
            bottomClipPath.MoveTo(offsetX + width + rightW, offsetY + height + bottomW);
            bottomClipPath.LineTo(offsetX + width - rightW * EXTEND, offsetY + height - bottomW * EXTEND);
            bottomClipPath.LineTo(offsetX + width, offsetY + height - bottomW * EXTEND);
            bottomClipPath.Close();
            canvas->ClipPath(bottomClipPath, RSClipOp::DIFFERENCE, true);
        }
        bottomBorder.ArcTo(rectStart.GetLeft(), rectStart.GetTop(), rectStart.GetRight(), rectStart.GetBottom(),
            BOTTOM_START, SWEEP_ANGLE);
        bottomBorder.ArcTo(rectEnd.GetLeft(), rectEnd.GetTop(), rectEnd.GetRight(), rectEnd.GetBottom(),
            BOTTOM_END, SWEEP_ANGLE + 0.5f);
        if (NearZero(blX) && !NearZero(leftW)) {
            bottomBorder.LineTo(offsetX, offsetY + height - bottomW / 2.0f);
            RSRecordingPath bottomClipPath;
            bottomClipPath.MoveTo(offsetX - leftW, offsetY + height + bottomW);
            bottomClipPath.LineTo(offsetX + leftW * EXTEND, offsetY + height - bottomW * EXTEND);
            bottomClipPath.LineTo(offsetX, offsetY + height - bottomW * EXTEND);
            bottomClipPath.Close();
            canvas->ClipPath(bottomClipPath, RSClipOp::DIFFERENCE, true);
        }
        canvas->AttachPen(pen);
        canvas->DrawPath(bottomBorder);
        if (NearZero(brX) || NearZero(brY) || NearZero(blX) || NearZero(blY)) {
            canvas->Restore();
        }
        canvas->DetachPen();
    }
    if (border.Left().HasValue() && !NearZero(leftW)) {
        // Draw Left Border
        SetBorderStyle(border.Left(), pen, false);
        auto rectStart = RSRect(x, y + h - blY * 2.0f, blX * 2.0f, blY * 2.0f);
        auto rectEnd = RSRect(x, y, tlX * 2.0f, tlY * 2.0f);
        RSRecordingPath leftBorder;
        if (border.Left().GetBorderStyle() != BorderStyle::DOTTED) {
            pen.SetWidth(maxW);
        }
        if (NearZero(blX) || NearZero(blY) || NearZero(tlX) || NearZero(tlY)) {
            canvas->Save();
        }
        if (NearZero(blX) && !NearZero(bottomW)) {
            leftBorder.MoveTo(offsetX + leftW / 2.0f, offsetY + height);
            leftBorder.LineTo(x, y + h - blY * 2.0f);
            RSRecordingPath leftClipPath;
            leftClipPath.MoveTo(offsetX - leftW, offsetY + height + bottomW);
            leftClipPath.LineTo(offsetX + leftW * EXTEND, offsetY + height - bottomW * EXTEND);
            leftClipPath.LineTo(offsetX + leftW * EXTEND, offsetY + height);
            leftClipPath.Close();
            canvas->ClipPath(leftClipPath, RSClipOp::DIFFERENCE, true);
        }
        leftBorder.ArcTo(rectStart.GetLeft(), rectStart.GetTop(), rectStart.GetRight(), rectStart.GetBottom(),
            LEFT_START, SWEEP_ANGLE);
        leftBorder.ArcTo(rectEnd.GetLeft(), rectEnd.GetTop(), rectEnd.GetRight(), rectEnd.GetBottom(),
            LEFT_END, SWEEP_ANGLE + 0.5f);
        if (NearZero(tlX) && !NearZero(topW)) {
            leftBorder.LineTo(offsetX + leftW / 2.0f, offsetY);
            RSRecordingPath topClipPath;
            topClipPath.MoveTo(offsetX - leftW, offsetY - topW);
            topClipPath.LineTo(offsetX + leftW * EXTEND, offsetY + topW * EXTEND);
            topClipPath.LineTo(offsetX + leftW * EXTEND, offsetY);
            topClipPath.Close();
            canvas->ClipPath(topClipPath, RSClipOp::DIFFERENCE, true);
        }
        canvas->AttachPen(pen);
        canvas->DrawPath(leftBorder);
        if (NearZero(blX) || NearZero(blY) || NearZero(tlX) || NearZero(tlY)) {
            canvas->Restore();
        }
        canvas->DetachPen();
    }
#endif
}

#ifndef USE_ROSEN_DRAWING
void RosenDecorationPainter::PaintBorderWithLine(
    const Offset& offset, const Border& border, SkCanvas* canvas, SkPaint& paint)
#else
void RosenDecorationPainter::PaintBorderWithLine(
    const Offset& offset, const Border& border, RSCanvas* canvas, RSPen& pen)
#endif
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
#ifndef USE_ROSEN_DRAWING
        SetBorderStyle(left, paint, false, borderLength / rawNumber, borderLength);
        canvas->drawLine(offset.GetX() + SK_ScalarHalf * NormalizeToPx(left.GetWidth()),
            offset.GetY() + addLen * NormalizeToPx(left.GetWidth()),
            offset.GetX() + SK_ScalarHalf * NormalizeToPx(left.GetWidth()), offset.GetY() + paintSize_.Height(), paint);
#else
        SetBorderStyle(left, pen, false, borderLength / rawNumber, borderLength);
        canvas->AttachPen(pen);
        canvas->DrawLine(RSPoint(offset.GetX() + FLOAT_HALF * NormalizeToPx(left.GetWidth()),
                             offset.GetY() + addLen * NormalizeToPx(left.GetWidth())),
            RSPoint(offset.GetX() + FLOAT_HALF * NormalizeToPx(left.GetWidth()), offset.GetY() + paintSize_.Height()));
        canvas->DetachPen();
#endif
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
#ifndef USE_ROSEN_DRAWING
        SetBorderStyle(bottom, paint, false, borderLength / rawNumber, borderLength);
        canvas->drawLine(offset.GetX() + addLen * NormalizeToPx(bottom.GetWidth()),
            offset.GetY() + paintSize_.Height() - SK_ScalarHalf * NormalizeToPx(bottom.GetWidth()),
            offset.GetX() + paintSize_.Width(),
            offset.GetY() + paintSize_.Height() - SK_ScalarHalf * NormalizeToPx(bottom.GetWidth()), paint);
#else
        SetBorderStyle(bottom, pen, false, borderLength / rawNumber, borderLength);
        canvas->AttachPen(pen);
        canvas->DrawLine(RSPoint(offset.GetX() + addLen * NormalizeToPx(bottom.GetWidth()),
                             offset.GetY() + paintSize_.Height() - FLOAT_HALF * NormalizeToPx(bottom.GetWidth())),
            RSPoint(offset.GetX() + paintSize_.Width(),
                offset.GetY() + paintSize_.Height() - FLOAT_HALF * NormalizeToPx(bottom.GetWidth())));
        canvas->DetachPen();
#endif
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
#ifndef USE_ROSEN_DRAWING
        SetBorderStyle(right, paint, false, borderLength / rawNumber, borderLength);
        canvas->drawLine(offset.GetX() + paintSize_.Width() - SK_ScalarHalf * NormalizeToPx(right.GetWidth()),
            offset.GetY() + paintSize_.Height() - addLen * NormalizeToPx(right.GetWidth()),
            offset.GetX() + paintSize_.Width() - SK_ScalarHalf * NormalizeToPx(right.GetWidth()), offset.GetY(), paint);
#else
        SetBorderStyle(right, pen, false, borderLength / rawNumber, borderLength);
        canvas->AttachPen(pen);
        canvas->DrawLine(RSPoint(offset.GetX() + paintSize_.Width() - FLOAT_HALF * NormalizeToPx(right.GetWidth()),
                             offset.GetY() + paintSize_.Height() - addLen * NormalizeToPx(right.GetWidth())),
            RSPoint(offset.GetX() + paintSize_.Width() - FLOAT_HALF * NormalizeToPx(right.GetWidth()), offset.GetY()));
        canvas->DetachPen();
#endif
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
#ifndef USE_ROSEN_DRAWING
        SetBorderStyle(top, paint, false, borderLength / rawNumber, borderLength);
        canvas->drawLine(offset.GetX() + addLen * NormalizeToPx(top.GetWidth()),
            offset.GetY() + SK_ScalarHalf * NormalizeToPx(top.GetWidth()), offset.GetX() + paintSize_.Width(),
            offset.GetY() + SK_ScalarHalf * NormalizeToPx(top.GetWidth()), paint);
#else
        SetBorderStyle(top, pen, false, borderLength / rawNumber, borderLength);
        canvas->AttachPen(pen);
        canvas->DrawLine(RSPoint(offset.GetX() + addLen * NormalizeToPx(top.GetWidth()),
                             offset.GetY() + FLOAT_HALF * NormalizeToPx(top.GetWidth())),
            RSPoint(offset.GetX() + paintSize_.Width(), offset.GetY() + FLOAT_HALF * NormalizeToPx(top.GetWidth())));
        canvas->DetachPen();
#endif
    }
}

// Add for box-shadow, otherwise using PaintShadow().
void RosenDecorationPainter::PaintBoxShadows(const std::vector<Shadow>& shadows, const std::shared_ptr<RSNode>& rsNode)
{
    if (!rsNode) {
        LOGE("PaintBoxShadows failed, rsNode is null.");
        return;
    }

    if (!shadows.empty()) {
        for (const auto& shadow : shadows) {
            if (!shadow.IsValid()) {
                LOGW("The current shadow is not drawn if the shadow is invalid.");
                continue;
            }
#ifndef USE_ROSEN_DRAWING
            PaintShadow(SkPath(), shadow, rsNode);
#else
            PaintShadow(RSRecordingPath(), shadow, rsNode);
#endif
        }
    } else {
        rsNode->SetShadowRadius(0.f);
    }
}

#ifndef USE_ROSEN_DRAWING
void RosenDecorationPainter::PaintShadow(
    const SkPath& path, const Shadow& shadow, const std::shared_ptr<RSNode>& rsNode)
#else
void RosenDecorationPainter::PaintShadow(
    const RSPath& path, const Shadow& shadow, const std::shared_ptr<RSNode>& rsNode)
#endif
{
    if (!rsNode || !shadow.IsValid()) {
        return;
    }
#ifndef USE_ROSEN_DRAWING
    if (!path.isEmpty()) {
#else
    if (path.IsValid()) {
#endif
        rsNode->SetShadowPath(Rosen::RSPath::CreateRSPath(path));
    }
    rsNode->SetShadowColor(shadow.GetColor().GetValue());
    rsNode->SetShadowOffsetX(shadow.GetOffset().GetX());
    rsNode->SetShadowOffsetY(shadow.GetOffset().GetY());
    rsNode->SetShadowMask(shadow.GetShadowType() == ShadowType::BLUR);
    if (shadow.GetHardwareAcceleration()) {
        rsNode->SetShadowElevation(shadow.GetElevation());
    } else {
        rsNode->SetShadowRadius(ConvertRadiusToSigma(shadow.GetBlurRadius()));
    }
}

#ifndef USE_ROSEN_DRAWING
void RosenDecorationPainter::PaintShadow(
    const SkPath& path, const Shadow& shadow, SkCanvas* canvas, const SkPaint* paint)
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
        SkPaint ShadowPaint;
        ShadowPaint.setColor(spotColor);
        ShadowPaint.setAntiAlias(true);
        if (paint) {
            ShadowPaint.setStyle(paint->getStyle());
            ShadowPaint.setStrokeWidth(paint->getStrokeWidth());
            ShadowPaint.setStrokeMiter(paint->getStrokeMiter());
            ShadowPaint.setStrokeCap(paint->getStrokeCap());
            ShadowPaint.setStrokeJoin(paint->getStrokeJoin());
            ShadowPaint.setAlphaf(paint->getAlphaf() * ShadowPaint.getAlphaf());
        }
        ShadowPaint.setMaskFilter(
            SkMaskFilter::MakeBlur(kNormal_SkBlurStyle, ConvertRadiusToSigma(shadow.GetBlurRadius())));
        canvas->drawPath(skPath, ShadowPaint);
    }
    canvas->restore();
}
#else
void RosenDecorationPainter::PaintShadow(const RSPath& path, const Shadow& shadow,
    RSCanvas* canvas, const RSBrush* brush, const RSPen* pen)
{
    if (!canvas) {
        LOGE("PaintShadow failed, canvas is null.");
        return;
    }
    if (!shadow.IsValid()) {
        LOGW("The current shadow is not drawn if the shadow is invalid.");
        return;
    }
    canvas->Save();
    RSRecordingPath drPath = static_cast<const RSRecordingPath&>(path);
    drPath.Offset(shadow.GetOffset().GetX(), shadow.GetOffset().GetY());
    RSColorQuad spotColor = shadow.GetColor().GetValue();
    if (shadow.GetHardwareAcceleration()) {
        // PlaneParams represents the coordinates of the component, and here we only need to focus on the elevation
        // of the component.
        RSPoint3 planeParams = RSPoint3(0.0f, 0.0f, shadow.GetElevation());

        // LightPos is the location of a spot light source, which is by default located directly above the center
        // of the component.
        auto drRect = drPath.GetBounds();
        RSPoint3 lightPos = RSPoint3(drRect.GetLeft() * FLOAT_HALF + drRect.GetRight() * FLOAT_HALF,
            drRect.GetTop() * FLOAT_HALF + drRect.GetBottom() * FLOAT_HALF, shadow.GetLightHeight());

        // Current ambient color is not available.
        RSColorQuad ambientColor = RSColor::ColorQuadSetARGB(0, 0, 0, 0);
        canvas->DrawShadow(drPath, planeParams, lightPos, shadow.GetLightRadius(), ambientColor, spotColor,
            RSShadowFlags::TRANSPARENT_OCCLUDER);
    } else {
        RSFilter filter;
        filter.SetMaskFilter(RSRecordingMaskFilter::CreateBlurMaskFilter(
            RSBlurType::NORMAL, ConvertRadiusToSigma(shadow.GetBlurRadius())));
        if (pen) {
            RSPen shadowPen;
            shadowPen.SetColor(spotColor);
            shadowPen.SetAntiAlias(true);
            shadowPen.SetWidth(pen->GetWidth());
            shadowPen.SetMiterLimit(pen->GetMiterLimit());
            shadowPen.SetCapStyle(pen->GetCapStyle());
            shadowPen.SetJoinStyle(pen->GetJoinStyle());
            shadowPen.SetAlphaF(pen->GetAlphaF() * shadowPen.GetAlphaF());
            shadowPen.SetFilter(filter);
            canvas->AttachPen(shadowPen);
        }
        if (brush) {
            RSBrush shadowBrush;
            shadowBrush.SetColor(spotColor);
            shadowBrush.SetAntiAlias(true);
            shadowBrush.SetAlphaF(brush->GetAlphaF() * shadowBrush.GetAlphaF());
            shadowBrush.SetFilter(filter);
            canvas->AttachBrush(shadowBrush);
        }
        canvas->DrawPath(drPath);
        if (pen) {
            canvas->DetachBrush();
        }
        if (brush) {
            canvas->DetachPen();
        }
    }
    canvas->Restore();
}
#endif

void RosenDecorationPainter::PaintImage(const Offset& offset, RenderContext& context)
{
    if (decoration_) {
        RefPtr<BackgroundImage> backgroundImage = decoration_->GetImage();
        if (backgroundImage && renderImage_) {
            renderImage_->RenderWithContext(context, offset);
        }
    }
}

#ifndef USE_ROSEN_DRAWING
bool RosenDecorationPainter::GetGradientPaint(SkPaint& paint)
#else
bool RosenDecorationPainter::GetGradientPaint(RSBrush& brush)
#endif
{
    Gradient gradient = decoration_->GetGradient();
    if (NearZero(paintSize_.Width()) || NearZero(paintSize_.Height()) || !gradient.IsValid()) {
        return false;
    }

#ifndef USE_ROSEN_DRAWING

    SkSize skPaintSize = SkSize::Make(paintSize_.Width(), paintSize_.Height());
    auto shader = CreateGradientShader(gradient, skPaintSize);
    paint.setShader(std::move(shader));
#else
    RSSize paintSize = RSSize(static_cast<RSScalar>(paintSize_.Width()), static_cast<RSScalar>(paintSize_.Height()));
    auto shader = CreateGradientShader(gradient, paintSize);
    brush.SetShaderEffect(shader);
#endif
    return true;
}

void RosenDecorationPainter::PaintGradient(RenderContext& context)
{
    Gradient gradient = decoration_->GetGradient();
    if (NearZero(paintSize_.Width()) || NearZero(paintSize_.Height())) {
        return;
    }
    if (!gradient.IsValid()) {
        return;
    }

#ifndef USE_ROSEN_DRAWING
    auto size = SkSize::Make(paintSize_.Width(), paintSize_.Width());
#else
    auto size = RSSize(paintSize_.Width(), paintSize_.Width());
#endif
    auto shader = CreateGradientShader(gradient, size, dipScale_);
#ifdef OHOS_PLATFORM
    auto rsNode = static_cast<RosenRenderContext*>(&context)->GetRSNode();
    if (rsNode) {
        rsNode->SetBackgroundShader(Rosen::RSShader::CreateRSShader(shader));
    }
#endif
}

#ifndef USE_ROSEN_DRAWING
sk_sp<SkShader> RosenDecorationPainter::CreateGradientShader(const Gradient& gradient, const SkSize& size)
#else
std::shared_ptr<RSShaderEffect> RosenDecorationPainter::CreateGradientShader(
    const Gradient& gradient, const RSSize& size)
#endif
{
    return CreateGradientShader(gradient, size, dipScale_);
}

#ifndef USE_ROSEN_DRAWING
sk_sp<SkShader> RosenDecorationPainter::CreateGradientShader(
    const Gradient& gradient, const SkSize& size, double dipScale)
#else
std::shared_ptr<RSShaderEffect> RosenDecorationPainter::CreateGradientShader(
    const Gradient& gradient, const RSSize& size, double dipScale)
#endif
{
    auto ptr = std::make_unique<GradientShader>(gradient);
    switch (gradient.GetType()) {
        case GradientType::LINEAR:
            ptr = LinearGradientShader::CreateLinearGradient(gradient, size);
            break;
        case GradientType::RADIAL:
            ptr = RadialGradientShader::CreateRadialGradient(gradient, size, dipScale);
            break;
        case GradientType::SWEEP:
            ptr = SweepGradientShader::CreateSweepGradient(gradient, size, dipScale);
            break;
        default:
            LOGE("unsupported gradient type.");
            break;
    }
    return ptr->CreateGradientShader();
}

bool RosenDecorationPainter::CheckBorderEdgeForRRect(const Border& border)
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

void RosenDecorationPainter::AdjustBorderStyle(Border& border)
{
    // if not set border style use default border style solid
    if (border.Left().GetBorderStyle() == BorderStyle::NONE) {
        border.SetLeftStyle(BorderStyle::SOLID);
    }

    if (border.Top().GetBorderStyle() == BorderStyle::NONE) {
        border.SetTopStyle(BorderStyle::SOLID);
    }

    if (border.Right().GetBorderStyle() == BorderStyle::NONE) {
        border.SetRightStyle(BorderStyle::SOLID);
    }

    if (border.Bottom().GetBorderStyle() == BorderStyle::NONE) {
        border.SetBottomStyle(BorderStyle::SOLID);
    }
}

double RosenDecorationPainter::NormalizeToPx(const Dimension& dimension) const
{
    if ((dimension.Unit() == DimensionUnit::VP) || (dimension.Unit() == DimensionUnit::FP)) {
        return (dimension.Value() * dipScale_);
    }
    return dimension.Value();
}

double RosenDecorationPainter::SliceNormalizePercentToPx(const Dimension& dimension, bool isVertical) const
{
    if (dimension.Unit() != DimensionUnit::PERCENT) {
        return NormalizeToPx(dimension);
    }
#ifndef USE_ROSEN_DRAWING
    auto limit = isVertical ? image_->width() : image_->height();
#else
    auto limit = isVertical ? image_->GetWidth() : image_->GetHeight();
#endif
    return limit * dimension.Value();
}

double RosenDecorationPainter::WidthNormalizePercentToPx(const Dimension& dimension, bool isVertical) const
{
    if (dimension.Unit() != DimensionUnit::PERCENT) {
        return NormalizeToPx(dimension);
    }
    auto limit = isVertical ? paintSize_.Width() : paintSize_.Height();
    return limit * dimension.Value();
}

double RosenDecorationPainter::OutsetNormalizePercentToPx(const Dimension& dimension, bool isVertical) const
{
    if (dimension.Unit() != DimensionUnit::PERCENT) {
        return NormalizeToPx(dimension);
    }
    auto limit = isVertical ? paintSize_.Width() : paintSize_.Height();
    return limit * dimension.Value();
}

} // namespace OHOS::Ace
