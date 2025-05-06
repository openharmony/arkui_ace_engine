/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_UI_PROPERTIES_GRADIENT_PROPERTY_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_UI_PROPERTIES_GRADIENT_PROPERTY_H

#include <array>
#include <memory>
#include <optional>
#include <regex>
#include <vector>

#include "ui/base/geometry/dimension.h"
#include "ui/base/geometry/ng/offset_t.h"
#include "ui/base/ace_type.h"
#include "ui/base/macros.h"
#include "ui/base/utils/utils.h"
#include "ui/properties/color.h"
#include "ui/properties/linear_color.h"

namespace OHOS::Ace::NG {

constexpr float BOX_END_SIZE = 100.0f;

enum class GradientDirection {
    LEFT = 0,
    TOP,
    RIGHT,
    BOTTOM,
    LEFT_TOP,
    LEFT_BOTTOM,
    RIGHT_TOP,
    RIGHT_BOTTOM,
    NONE,
    START_TO_END,
    END_TO_START,
};

enum class GradientType {
    LINEAR,
    RADIAL,
    SWEEP,
    CONIC,
};

enum class RadialSizeType {
    CLOSEST_SIDE,
    CLOSEST_CORNER,
    FARTHEST_SIDE,
    FARTHEST_CORNER,
    NONE,
};

enum class RadialShapeType {
    CIRCLE,
    ELLIPSE,
    NONE,
};

enum class SpreadMethod {
    PAD,
    REFLECT,
    REPEAT,
};

struct LinearGradientInfo {
    float x1 = 0.0f;
    float x2 = 0.0f;
    float y1 = 0.0f;
    float y2 = 0.0f;
    bool operator==(const LinearGradientInfo& other) const
    {
        return (
            NearEqual(x1, other.x1) && NearEqual(x2, other.x2) && NearEqual(y1, other.y1) && NearEqual(y2, other.y2));
    }
};

struct RadialGradientInfo {
    float r = 0.0f;
    float cx = 0.0f;
    float cy = 0.0f;
    float fx = 0.0f;
    float fy = 0.0f;
    bool operator==(const RadialGradientInfo& other) const
    {
        return (NearEqual(r, other.r) && NearEqual(cx, other.cx) && NearEqual(cy, other.cy) &&
                NearEqual(fx, other.fx) && NearEqual(fy, other.fy));
    }
};

class GradientColor final {
public:
    GradientColor() = default;
    ~GradientColor() = default;

    explicit GradientColor(const Color& color)
    {
        color_ = color;
    }

    void SetDimension(double value, DimensionUnit unit = DimensionUnit::PERCENT)
    {
        if (value < 0.0) {
            return;
        }
        if (unit == DimensionUnit::PERCENT && value > BOX_END_SIZE) {
            return;
        }
        dimension_ = Dimension(value, unit);
    }

    void SetDimension(const Dimension& dimension)
    {
        if (dimension.Value() < 0.0) {
            return;
        }
        if (dimension.Unit() == DimensionUnit::PERCENT && dimension.Value() > BOX_END_SIZE) {
            return;
        }
        dimension_ = dimension;
    }

    void SetHasValue(bool hasValue)
    {
        hasValue_ = hasValue;
    }

    void SetColor(const Color& color)
    {
        color_ = color;
    }

    const Color& GetColor() const
    {
        return color_;
    }

    void SetLinearColor(const LinearColor& linearColor)
    {
        linearColor_ = linearColor;
    }

    const LinearColor& GetLinearColor() const
    {
        return linearColor_;
    }

    const Dimension& GetDimension() const
    {
        return dimension_;
    }

    bool GetHasValue() const
    {
        return hasValue_;
    }

    void SetOpacity(double opacity)
    {
        opacity_ = opacity;
    }

    double GetOpacity() const
    {
        return opacity_;
    }

    bool operator==(const GradientColor& other) const
    {
        return (hasValue_ == other.GetHasValue() && color_ == other.GetColor() && dimension_ == other.GetDimension() &&
                opacity_ == other.GetOpacity() && linearColor_ == other.GetLinearColor());
    }

private:
    bool hasValue_ = true;
    Color color_ { Color::TRANSPARENT };
    LinearColor linearColor_ { LinearColor::TRANSPARENT };
    Dimension dimension_ { BOX_END_SIZE, DimensionUnit::PERCENT };
    float opacity_ = 1.0f;
};

struct ACE_EXPORT RadialGradient {
    // size type
    std::optional<RadialSizeType> radialSizeType;
    // shape circle or ellipse
    std::optional<RadialShapeType> radialShape;
    // size in x-axis
    std::optional<Dimension> radialHorizontalSize;
    // size in y-axis
    std::optional<Dimension> radialVerticalSize;
    // center of shape
    std::optional<Dimension> radialCenterX;
    std::optional<Dimension> radialCenterY;

    std::optional<Dimension> fRadialCenterX;
    std::optional<Dimension> fRadialCenterY;

    bool operator==(const RadialGradient& other) const
    {
        return (radialSizeType == other.radialSizeType && radialShape == other.radialShape &&
                radialHorizontalSize == other.radialHorizontalSize && radialVerticalSize == other.radialVerticalSize &&
                radialCenterX == other.radialCenterX && radialCenterY == other.radialCenterY &&
                fRadialCenterX == other.fRadialCenterX && fRadialCenterY == other.fRadialCenterY);
    }
};

struct ACE_EXPORT LinearGradient {
    // direction in x-axis
    std::optional<GradientDirection> linearX;
    // direction in y-axis
    std::optional<GradientDirection> linearY;
    // angle of gradient line in bearing angle
    std::optional<Dimension> angle;

    std::optional<Dimension> x1;
    std::optional<Dimension> y1;
    std::optional<Dimension> x2;
    std::optional<Dimension> y2;

    // is direction in x-axis
    static bool IsXAxis(GradientDirection direction)
    {
        return (direction == GradientDirection::LEFT || direction == GradientDirection::RIGHT ||
                direction == GradientDirection::START_TO_END || direction == GradientDirection::END_TO_START);
    }

    bool operator==(const LinearGradient& other) const
    {
        return (x1 == other.x1 && y1 == other.y1 && x2 == other.x2 && y2 == other.y2 && linearX == other.linearX &&
                linearY == other.linearY && angle == other.angle);
    }
};

struct ACE_EXPORT SweepGradient {
    // center of x-axis
    std::optional<Dimension> centerX;
    // center of y-axis
    std::optional<Dimension> centerY;
    // startAngle in degree
    std::optional<Dimension> startAngle;
    // endAngle in degree
    std::optional<Dimension> endAngle;
    // rotation in degree
    std::optional<Dimension> rotation;

    bool operator==(const OHOS::Ace::NG::SweepGradient& other) const
    {
        return (centerX == other.centerX && centerY == other.centerY && startAngle == other.startAngle &&
                endAngle == other.endAngle && rotation == other.rotation);
    }
};

class ACE_FORCE_EXPORT Gradient final {
public:
    ACE_FORCE_EXPORT void AddColor(const GradientColor& color);

    void ClearColors();

    bool IsSweepGradientValid() const
    {
        if (sweepGradient_->startAngle.has_value() && sweepGradient_->endAngle.has_value()) {
            return LessOrEqual(sweepGradient_->startAngle.value().Value(), sweepGradient_->endAngle.value().Value());
        }
        if (sweepGradient_->startAngle.has_value() && !sweepGradient_->endAngle.has_value()) {
            return LessOrEqual(sweepGradient_->startAngle.value().Value(), 0.0);
        }
        if (!sweepGradient_->startAngle.has_value() && sweepGradient_->endAngle.has_value()) {
            return LessOrEqual(0.0, sweepGradient_->endAngle.value().Value());
        }
        return true;
    }

    bool IsValid() const
    {
        if (GetType() == GradientType::SWEEP) {
            return IsSweepGradientValid() && colors_.size() > 1;
        }
        return colors_.size() > 1;
    }

    void SetRepeat(bool repeat)
    {
        repeat_ = repeat;
    }

    bool GetRepeat() const
    {
        return repeat_;
    }

    const std::vector<GradientColor>& GetColors() const
    {
        return colors_;
    }

    const std::shared_ptr<OffsetF>& GetBeginOffset() const
    {
        return beginOffset_;
    }

    void SetBeginOffset(const OffsetF& beginOffset)
    {
        beginOffset_ = std::make_shared<OffsetF>(beginOffset);
    }

    const std::shared_ptr<OffsetF>& GetEndOffset() const
    {
        return endOffset_;
    }

    void SetEndOffset(const OffsetF& endOffset)
    {
        endOffset_ = std::make_shared<OffsetF>(endOffset);
    }

    double GetInnerRadius() const
    {
        return innerRadius_;
    }

    void SetInnerRadius(double innerRadius)
    {
        innerRadius_ = innerRadius;
    }

    double GetOuterRadius() const
    {
        return outerRadius_;
    }

    void SetOuterRadius(double outerRadius)
    {
        outerRadius_ = outerRadius;
    }

    GradientType GetType() const
    {
        return type_;
    }

    void CreateGradientWithType(GradientType type);

    std::string ToString() const
    {
        return std::string("Gradient (")
            .append(beginOffset_->ToString())
            .append(",")
            .append(std::to_string(innerRadius_))
            .append(" --- ")
            .append(endOffset_->ToString())
            .append(",")
            .append(std::to_string(outerRadius_))
            .append(")");
    }

    std::shared_ptr<SweepGradient> GetSweepGradient()
    {
        return sweepGradient_;
    }

    const std::shared_ptr<SweepGradient> GetSweepGradient() const
    {
        return sweepGradient_;
    }

    void SetSweepGradient(const SweepGradient& sweepGradient)
    {
        sweepGradient_ = std::make_shared<SweepGradient>(sweepGradient);
    }

    std::shared_ptr<RadialGradient>& GetRadialGradient()
    {
        return radialGradient_;
    }

    const std::shared_ptr<RadialGradient>& GetRadialGradient() const
    {
        return radialGradient_;
    }

    void SetRadialGradient(const RadialGradient& radialGradient)
    {
        radialGradient_ = std::make_shared<RadialGradient>(radialGradient);
    }

    std::shared_ptr<LinearGradient>& GetLinearGradient()
    {
        return linearGradient_;
    }

    const std::shared_ptr<LinearGradient>& GetLinearGradient() const
    {
        return linearGradient_;
    }

    void SetLinearGradient(const LinearGradient& linearGradient)
    {
        linearGradient_ = std::make_shared<LinearGradient>(linearGradient);
    }

    void SetDirection(const GradientDirection& direction)
    {
        if (LinearGradient::IsXAxis(direction)) {
            linearGradient_->linearX = direction;
        } else {
            linearGradient_->linearY = direction;
        }
    }

    void SetSpreadMethod(SpreadMethod spreadMethod)
    {
        spreadMethod_ = spreadMethod;
    }

    void SetGradientTransform(const std::string& gradientTransform)
    {
        gradientTransform_ = gradientTransform;
    }

    SpreadMethod GetSpreadMethod() const
    {
        return spreadMethod_;
    }

    const std::string& GetGradientTransform() const
    {
        return gradientTransform_;
    }

    const std::shared_ptr<RadialGradientInfo>& GetRadialGradientInfo() const
    {
        return radialGradientInfo_;
    }

    void SetRadialGradientInfo(const RadialGradientInfo& radialGradientInfo)
    {
        radialGradientInfo_ = std::make_shared<RadialGradientInfo>(radialGradientInfo);
    }

    const std::shared_ptr<LinearGradientInfo> GetLinearGradientInfo() const
    {
        return linearGradientInfo_;
    }

    void SetLinearGradientInfo(const LinearGradientInfo& linearGradientInfo)
    {
        linearGradientInfo_ = std::make_shared<LinearGradientInfo>(linearGradientInfo);
    }

    bool operator==(const Gradient& other) const
    {
        return (type_ == other.GetType() && repeat_ == other.GetRepeat() && colors_ == other.GetColors() &&
                radialGradient_ == other.GetRadialGradient() && linearGradient_ == other.GetLinearGradient() &&
                sweepGradient_ == other.GetSweepGradient() && beginOffset_ == other.GetBeginOffset() &&
                endOffset_ == other.GetEndOffset() && spreadMethod_ == other.GetSpreadMethod() &&
                gradientTransform_ == other.GetGradientTransform() &&
                linearGradientInfo_ == other.GetLinearGradientInfo() &&
                radialGradientInfo_ == other.GetRadialGradientInfo());
    }

    bool operator!=(const Gradient& other) const
    {
        return !(*this == other);
    }

private:
    GradientType type_ = GradientType::LINEAR;
    bool repeat_ = false;
    std::vector<GradientColor> colors_;
    // for RadialGradient
    std::shared_ptr<RadialGradient> radialGradient_;
    // for LinearGradient
    std::shared_ptr<LinearGradient> linearGradient_;
    // for SweepGradient
    std::shared_ptr<SweepGradient> sweepGradient_;
    // used for CanvasLinearGradient
    std::shared_ptr<OffsetF> beginOffset_;
    std::shared_ptr<OffsetF> endOffset_;
    // used for CanvasRadialGradient
    float innerRadius_ = 0.0f;
    float outerRadius_ = 0.0;
    SpreadMethod spreadMethod_ = SpreadMethod::PAD;
    std::string gradientTransform_;
    std::shared_ptr<LinearGradientInfo> linearGradientInfo_;
    std::shared_ptr<RadialGradientInfo> radialGradientInfo_;
};


class LinearGradientBlurPara final {
public:
    Dimension blurRadius_;
    std::vector<std::pair<float, float>> fractionStops_;
    GradientDirection direction_;

    LinearGradientBlurPara(const Dimension blurRadius,
        const std::vector<std::pair<float, float>>fractionStops, const GradientDirection direction)
        : blurRadius_(blurRadius), fractionStops_(fractionStops), direction_(direction) {}
    bool operator==(const LinearGradientBlurPara& other) const
    {
        return NearEqual(blurRadius_, other.blurRadius_) && NearEqual(fractionStops_, other.fractionStops_) &&
                                                            NearEqual(direction_, other.direction_);
    }

    ~LinearGradientBlurPara() = default;
};

class MagnifierParams final {
public:
    float factor_ = 0.f;
    float width_ = 0.f;
    float height_ = 0.f;
    float borderWidth_ = 0.f;
    float cornerRadius_ = 0.f;
    float offsetX_ = 0.f;
    float offsetY_ = 0.f;

    float shadowOffsetX_ = 0.f;
    float shadowOffsetY_ = 0.f;
    float shadowSize_ = 0.f;
    float shadowStrength_ = 0.f;

    bool changed_ = false;

    // rgba
    uint32_t gradientMaskColor1_ = 0x00000000;
    uint32_t gradientMaskColor2_ = 0x00000000;
    uint32_t outerContourColor1_ = 0x00000000;
    uint32_t outerContourColor2_ = 0x00000000;

    bool operator==(const MagnifierParams& other) const
    {
        return NearEqual(factor_, other.factor_) && NearEqual(width_, other.width_) &&
               NearEqual(height_, other.height_) && NearEqual(borderWidth_, other.borderWidth_) &&
               NearEqual(cornerRadius_, other.cornerRadius_) && NearEqual(offsetX_, other.offsetX_) &&
               NearEqual(offsetY_, other.offsetY_) && NearEqual(shadowOffsetX_, other.shadowOffsetX_) &&
               NearEqual(shadowOffsetY_, other.shadowOffsetY_) && NearEqual(shadowSize_, other.shadowSize_) &&
               NearEqual(shadowStrength_, other.shadowStrength_) &&
               NearEqual(gradientMaskColor1_, other.gradientMaskColor1_) &&
               NearEqual(gradientMaskColor2_, other.gradientMaskColor2_) &&
               NearEqual(outerContourColor1_, other.outerContourColor1_) &&
               NearEqual(outerContourColor2_, other.outerContourColor2_) &&
               changed_ == other.changed_;
    }
    MagnifierParams() = default;
    ~MagnifierParams() = default;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_UI_PROPERTIES_GRADIENT_PROPERTY_H
