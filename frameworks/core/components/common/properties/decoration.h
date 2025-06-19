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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_DECORATION_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_DECORATION_H

#include <memory>
#include <optional>
#include <regex>
#include <vector>

#include "base/geometry/dimension.h"
#include "base/geometry/rect.h"
#include "base/image/pixel_map.h"
#include "base/json/json_util.h"
#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "base/utils/utils.h"
#include "core/components/common/properties/alignment.h"
#include "core/components/common/properties/animatable_color.h"
#include "core/components/common/properties/background_image.h"
#include "core/components/common/properties/blend_mode.h"
#include "core/components/common/properties/blur_style_option.h"
#include "core/components/common/properties/border.h"
#include "core/components/common/properties/border_image.h"
#include "core/components/common/properties/brightness_option.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/blur_style_option.h"
#include "core/components/common/properties/edge.h"
#include "core/components/common/properties/effect_option.h"
#include "core/components/common/properties/invert.h"
#include "core/components/common/properties/outline_style.h"
#include "core/components/common/properties/shadow.h"
#include "core/components/theme/theme_utils.h"
#include "core/components_ng/base/inspector_filter.h"

namespace OHOS::Ace {

class PipelineContext;

constexpr double CENTER_OFFSET = 50.0;
constexpr double BOX_BEGIN_SIZE = 0.0;
constexpr double BOX_END_SIZE = 100.0;
constexpr double PERCENT_TRANSLATE = 100.0;

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

enum class HapticFeedbackMode {
    DISABLED,
    ENABLED,
    AUTO,
};

enum class ModalMode {
    AUTO = 0,
    NONE = 1,
    TARGET_WINDOW = 2,
};

struct SysOptions {
    bool disableSystemAdaptation = true;
    bool operator==(const SysOptions& other) const
    {
        return disableSystemAdaptation == other.disableSystemAdaptation;
    }
};

struct MenuPreviewAnimationOptions {
    float scaleFrom { -1.0f };
    float scaleTo { -1.0f };
};

struct LinearGradientInfo {
    double x1 = 0.0;
    double x2 = 0.0;
    double y1 = 0.0;
    double y2 = 0.0;
};

struct RadialGradientInfo {
    double r = 0.0;
    double cx = 0.0;
    double cy = 0.0;
    double fx = 0.0;
    double fy = 0.0;
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

private:
    bool hasValue_ = true;
    Color color_ { Color::TRANSPARENT };
    Dimension dimension_ { BOX_END_SIZE, DimensionUnit::PERCENT };
    double opacity_ = 1.0;
};

struct ACE_EXPORT RadialGradient {
    // size type
    std::optional<RadialSizeType> radialSizeType;
    // shape circle or ellipse
    std::optional<RadialShapeType> radialShape;
    // size in x-axis
    std::optional<AnimatableDimension> radialHorizontalSize;
    // size in y-axis
    std::optional<AnimatableDimension> radialVerticalSize;
    // center of shape
    std::optional<AnimatableDimension> radialCenterX;
    std::optional<AnimatableDimension> radialCenterY;

    std::optional<Dimension> fRadialCenterX;
    std::optional<Dimension> fRadialCenterY;
};

struct ACE_EXPORT LinearGradient {
    // direction in x-axis
    std::optional<GradientDirection> linearX;
    // direction in y-axis
    std::optional<GradientDirection> linearY;
    // angle of gradient line in bearing angle
    std::optional<AnimatableDimension> angle;

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
};

struct ACE_EXPORT SweepGradient {
    // center of x-axis
    std::optional<AnimatableDimension> centerX;
    // center of y-axis
    std::optional<AnimatableDimension> centerY;
    // startAngle in degree
    std::optional<AnimatableDimension> startAngle;
    // endAngle in degree
    std::optional<AnimatableDimension> endAngle;
    // rotation in degree
    std::optional<AnimatableDimension> rotation;
};

struct ACE_EXPORT ConicGradient {
    // center of x-axis
    std::optional<AnimatableDimension> centerX;
    // center of y-axis
    std::optional<AnimatableDimension> centerY;
    // startAngle in radian
    std::optional<AnimatableDimension> startAngle;
};

class ACE_FORCE_EXPORT Gradient final {
public:
    void AddColor(const GradientColor& color);

    void ClearColors();

    bool IsSweepGradientValid() const
    {
        if (sweepGradient_.startAngle.has_value() && sweepGradient_.endAngle.has_value()) {
            return LessOrEqual(sweepGradient_.startAngle.value().Value(), sweepGradient_.endAngle.value().Value());
        }
        if (sweepGradient_.startAngle.has_value() && !sweepGradient_.endAngle.has_value()) {
            return LessOrEqual(sweepGradient_.startAngle.value().Value(), 0.0);
        }
        if (!sweepGradient_.startAngle.has_value() && sweepGradient_.endAngle.has_value()) {
            return LessOrEqual(0.0, sweepGradient_.endAngle.value().Value());
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

    const Offset& GetBeginOffset() const
    {
        return beginOffset_;
    }

    void SetBeginOffset(const Offset& beginOffset)
    {
        beginOffset_ = beginOffset;
    }

    const Offset& GetEndOffset() const
    {
        return endOffset_;
    }

    void SetEndOffset(const Offset& endOffset)
    {
        endOffset_ = endOffset;
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

    void SetType(GradientType type)
    {
        type_ = type;
    }

    std::string ToString() const
    {
        return std::string("Gradient (")
            .append(beginOffset_.ToString())
            .append(",")
            .append(std::to_string(innerRadius_))
            .append(" --- ")
            .append(endOffset_.ToString())
            .append(",")
            .append(std::to_string(outerRadius_))
            .append(")");
    }

    SweepGradient& GetSweepGradient()
    {
        return sweepGradient_;
    }

    const SweepGradient& GetSweepGradient() const
    {
        return sweepGradient_;
    }

    void SetSweepGradient(const SweepGradient& sweepGradient)
    {
        sweepGradient_ = sweepGradient;
    }

    ConicGradient& GetConicGradient()
    {
        return conicGradient_;
    }

    const ConicGradient& GetConicGradient() const
    {
        return conicGradient_;
    }

    void SetConicGradient(const ConicGradient& conicGradient)
    {
        conicGradient_ = conicGradient;
    }

    RadialGradient& GetRadialGradient()
    {
        return radialGradient_;
    }

    const RadialGradient& GetRadialGradient() const
    {
        return radialGradient_;
    }

    void SetRadialGradient(const RadialGradient& radialGradient)
    {
        radialGradient_ = radialGradient;
    }

    LinearGradient& GetLinearGradient()
    {
        return linearGradient_;
    }

    const LinearGradient& GetLinearGradient() const
    {
        return linearGradient_;
    }

    void SetLinearGradient(const LinearGradient& linearGradient)
    {
        linearGradient_ = linearGradient;
    }

    void SetDirection(const GradientDirection& direction)
    {
        if (LinearGradient::IsXAxis(direction)) {
            linearGradient_.linearX = direction;
        } else {
            linearGradient_.linearY = direction;
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

    const RadialGradientInfo& GetRadialGradientInfo() const
    {
        return radialGradientInfo_;
    }

    void SetRadialGradientInfo(const RadialGradientInfo& radialGradientInfo)
    {
        radialGradientInfo_ = radialGradientInfo;
    }

    const LinearGradientInfo& GetLinearGradientInfo() const
    {
        return linearGradientInfo_;
    }

    void SetLinearGradientInfo(const LinearGradientInfo& linearGradientInfo)
    {
        linearGradientInfo_ = linearGradientInfo;
    }

    void SetHref(const std::string& href)
    {
        href_ = href;
    }

    std::string GetHref() const
    {
        return href_;
    }

private:
    GradientType type_ = GradientType::LINEAR;
    bool repeat_ = false;
    std::vector<GradientColor> colors_;
    // for RadialGradient
    RadialGradient radialGradient_;
    // for LinearGradient
    LinearGradient linearGradient_;
    // for SweepGradient
    SweepGradient sweepGradient_;
    // for ConicGradient
    ConicGradient conicGradient_;
    // used for CanvasLinearGradient
    Offset beginOffset_;
    Offset endOffset_;
    // used for CanvasRadialGradient
    double innerRadius_ = 0.0;
    double outerRadius_ = 0.0;
    SpreadMethod spreadMethod_ = SpreadMethod::PAD;
    std::string gradientTransform_;
    LinearGradientInfo linearGradientInfo_;
    RadialGradientInfo radialGradientInfo_;
    std::string href_;
};

class ArcBackground final : public AceType {
    DECLARE_ACE_TYPE(ArcBackground, AceType);

public:
    ~ArcBackground() override = default;
    ArcBackground(Point center, double radius)
    {
        SetCenter(center);
        SetRadius(radius);
    }

    const Point& GetCenter() const
    {
        return center_;
    }

    double GetRadius() const
    {
        return radius_;
    }

    void SetCenter(const Point& center)
    {
        center_ = center;
    }

    void SetRadius(double radius)
    {
        radius_ = radius;
    }

    void SetColor(const Color& color)
    {
        color_ = color;
    }

    const Color& GetColor() const
    {
        return color_;
    }

private:
    Point center_;
    double radius_ = 0.0;
    Color color_;
};

class Decoration final : public AceType {
    DECLARE_ACE_TYPE(Decoration, AceType);

public:
    Decoration() = default;
    ~Decoration() override = default;

    void SetContextAndCallback(const WeakPtr<PipelineContext>& context, const RenderNodeAnimationCallback& callback);

    void AddShadow(const Shadow& shadow);

    void ClearAllShadow();

    void SetBackgroundColor(const Color& backgroundColor, const AnimationOption& option = AnimationOption())
    {
        backgroundColor_ = AnimatableColor(backgroundColor, option);
    }

    void SetBackgroundColor(const AnimatableColor& backgroundColor)
    {
        backgroundColor_ = backgroundColor;
    }

    void SetAnimationColor(const Color& animationColor)
    {
        animationColor_ = animationColor;
    }

    void SetGradient(const Gradient& gradient, const WeakPtr<PipelineContext>& context = nullptr,
        const RenderNodeAnimationCallback& callback = nullptr);

    void SetBorderImageGradient(const Gradient& gradient)
    {
        gradientBorderImage_ = gradient;
    }
    void SetImage(const RefPtr<BackgroundImage>& image)
    {
        image_ = image;
    }

    void SetBorderImage(const RefPtr<BorderImage>& borderImage)
    {
        borderImage_ = borderImage;
    }

    void SetHasBorderImageSource(const bool tag)
    {
        hasBorderImageSource_ = tag;
    }

    void SetHasBorderImageSlice(const bool tag)
    {
        hasBorderImageSlice_ = tag;
    }

    void SetHasBorderImageWidth(const bool tag)
    {
        hasBorderImageWidth_ = tag;
    }

    void SetHasBorderImageOutset(const bool tag)
    {
        hasBorderImageOutset_ = tag;
    }

    void SetHasBorderImageRepeat(const bool tag)
    {
        hasBorderImageRepeat_ = tag;
    }

    void SetHasBorderImageGradient(const bool tag)
    {
        hasBorderImageGradient_ = tag;
    }

    void SetPadding(const Edge& padding)
    {
        padding_ = padding;
    }

    void SetBorderRadius(const Radius& radius)
    {
        border_.SetBorderRadius(radius);
    }

    void SetBorder(const Border& border)
    {
        border_ = border;
    }

    void SetArcBackground(const RefPtr<ArcBackground>& arcBG)
    {
        arcBG_ = arcBG;
    }

    void SetBlurRadius(const Dimension& radius)
    {
        blurRadius_ = radius;
    }

    void SetBlurRadius(const AnimatableDimension& radius)
    {
        blurRadius_ = radius;
    }

    const Color& GetColorBlend(void) const
    {
        return colorBlend;
    }

    void SetColorBlend(const Color& color)
    {
        colorBlend = color;
    }

    void SetWindowBlurProgress(float progress)
    {
        windowBlurProgress_ = progress;
    }

    void SetWindowBlurStyle(WindowBlurStyle style)
    {
        windowBlurStyle_ = style;
    }

    void SetBlurStyle(const BlurStyleOption& style)
    {
        blurStyle_ = style;
    }

    const Border& GetBorder() const
    {
        return border_;
    }

    const Edge& GetPadding() const
    {
        return padding_;
    }

    const RefPtr<BackgroundImage>& GetImage() const
    {
        return image_;
    }

    const RefPtr<BorderImage>& GetBorderImage() const
    {
        return borderImage_;
    }

    const Gradient& GetGradient() const
    {
        return gradient_;
    }

    const Gradient& GetBorderImageGradient() const
    {
        return gradientBorderImage_;
    }

    bool GetHasBorderImageSource()
    {
        return hasBorderImageSource_;
    }

    bool GetHasBorderImageSlice()
    {
        return hasBorderImageSlice_;
    }

    bool GetHasBorderImageWidth()
    {
        return hasBorderImageWidth_;
    }

    bool GetHasBorderImageOutset()
    {
        return hasBorderImageOutset_;
    }

    bool GetHasBorderImageRepeat()
    {
        return hasBorderImageRepeat_;
    }

    bool GetHasBorderImageGradient()
    {
        return hasBorderImageGradient_;
    }

    const AnimatableColor& GetBackgroundColor() const
    {
        return backgroundColor_;
    }

    const Color& GetAnimationColor() const
    {
        return animationColor_;
    }

    const std::vector<Shadow>& GetShadows() const
    {
        return shadows_;
    }

    void SetShadows(const std::vector<Shadow>& shadows)
    {
        shadows_.assign(shadows.begin(), shadows.end());
    }

    BlendMode GetBlendMode() const
    {
        return blendMode_;
    }

    void SetBlendMode(BlendMode blendMode)
    {
        blendMode_ = blendMode;
    }

    BlendApplyType GetBlendApplyType() const
    {
        return blendApplyType_;
    }

    void SetBlendApplyType(BlendApplyType blendApplyType)
    {
        blendApplyType_ = blendApplyType;
    }

    const Dimension& GetGrayScale(void) const
    {
        return grayScale_;
    }

    void SetGrayScale(const Dimension& grayScale)
    {
        grayScale_ = grayScale;
    }

    void SetBrightness(const Dimension& brightness)
    {
        brightness_ = brightness;
    }

    const Dimension& GetBrightness() const
    {
        return brightness_;
    }

    const Dimension& GetContrast(void) const
    {
        return contrast_;
    }

    void SetContrast(const Dimension& contrast)
    {
        contrast_ = contrast;
    }

    const Dimension& GetSaturate(void) const
    {
        return saturate_;
    }

    void SetSaturate(const Dimension& saturate)
    {
        saturate_ = saturate;
    }

    const Dimension& GetSepia(void) const
    {
        return sepia_;
    }

    void SetSepia(const Dimension& sepia)
    {
        sepia_ = sepia;
    }

    void SetInvert(const Dimension& invert)
    {
        invert_ = invert;
    }

    const Dimension& GetInvert(void) const
    {
        return invert_;
    }

    float GetHueRotate(void) const
    {
        return hueRotate_;
    }

    void SetHueRotate(const float& hueRotate)
    {
        hueRotate_ = hueRotate;
    }

    const RefPtr<ArcBackground>& GetArcBackground() const
    {
        return arcBG_;
    }

    bool NeedReloadImage(const RefPtr<Decoration>& lastDecoration) const
    {
        if (!image_) {
            return false;
        }

        if (!lastDecoration || !(lastDecoration->GetImage())) {
            return true;
        }

        return (*image_) != (*(lastDecoration->GetImage()));
    }

    const AnimatableDimension& GetBlurRadius() const
    {
        return blurRadius_;
    }

    float GetWindowBlurProgress() const
    {
        return windowBlurProgress_;
    }

    WindowBlurStyle GetWindowBlurStyle() const
    {
        return windowBlurStyle_;
    }

    const BlurStyleOption& GetBlurStyle() const
    {
        return blurStyle_;
    }

    // Indicate how much size the decoration taken, excluding the content size.
    Size GetOccupiedSize(double dipScale) const;
    double HorizontalSpaceOccupied(double dipScale) const;
    double VerticalSpaceOccupied(double dipScale) const;

    Offset GetOffset(double dipScale) const;

private:
    bool hasBorderImageSource_ = false;
    bool hasBorderImageSlice_ = false;
    bool hasBorderImageWidth_ = false;
    bool hasBorderImageOutset_ = false;
    bool hasBorderImageRepeat_ = false;
    bool hasBorderImageGradient_ = false;

    // padding is zero
    Edge padding_;
    // border contains black color and 1.0f thickness as default
    Border border_;
    // shadow vector is empty
    std::vector<Shadow> shadows_;
    // blendMode
    BlendMode blendMode_ = BlendMode::NONE;
    BlendApplyType blendApplyType_ = BlendApplyType::FAST;
    Dimension grayScale_;
    // Brightness (1.0 as default), range = (0, 2)
    Dimension brightness_ = 1.0_px;
    // hueRotate
    float hueRotate_ = 0.0f;
    // Contrast (1.0 as default), complete gray at 0
    Dimension contrast_ = 1.0_px;
    // Saturate
    Dimension saturate_ = 1.0_px;
    // Sepia
    Dimension sepia_;
    // invert
    Dimension invert_;
    // color is transparent
    AnimatableColor backgroundColor_ { Color::TRANSPARENT };
    Color animationColor_ = Color::TRANSPARENT;
    // Gradient is not implemented
    Gradient gradient_ = Gradient();
    Gradient gradientBorderImage_ = Gradient();
    RefPtr<BackgroundImage> image_;
    RefPtr<BorderImage> borderImage_;
    RefPtr<ArcBackground> arcBG_;
    // Blur radius
    AnimatableDimension blurRadius_;
    // window blur progress
    float windowBlurProgress_ = 0.0f;
    // window blur style;
    WindowBlurStyle windowBlurStyle_ = WindowBlurStyle::STYLE_BACKGROUND_SMALL_LIGHT;
    Color colorBlend;
    // blur from rosen
    BlurStyleOption blurStyle_;
};

class Pattern final : std::enable_shared_from_this<Pattern> {
public:
    bool IsValid() const
    {
        return (!imgSrc_.empty() || pixelMap_);
    }

    const std::string& GetImgSrc() const
    {
        return imgSrc_;
    }

    void SetImgSrc(const std::string& imgSrc)
    {
        imgSrc_ = imgSrc;
    }

    const std::string& GetRepetition() const
    {
        return repetition_;
    }

    void SetRepetition(const std::string& repetition)
    {
        repetition_ = repetition;
    }

    double GetImageWidth() const
    {
        return imageWidth_;
    }

    void SetImageWidth(double imageWidth)
    {
        imageWidth_ = imageWidth;
    }

    double GetImageHeight() const
    {
        return imageHeight_;
    }

    void SetImageHeight(double imageHeight)
    {
        imageHeight_ = imageHeight;
    }

    double GetScaleX() const
    {
        return scaleX_;
    }

    void SetScaleX(double scaleX)
    {
        transformable_ = true;
        scaleX_ = scaleX;
    }

    double GetScaleY() const
    {
        return scaleY_;
    }

    void SetScaleY(double scaleY)
    {
        transformable_ = true;
        scaleY_ = scaleY;
    }

    double GetSkewX() const
    {
        return skewX_;
    }

    void SetSkewX(double skewX)
    {
        transformable_ = true;
        skewX_ = skewX;
    }

    double GetSkewY() const
    {
        return skewY_;
    }

    void SetSkewY(double skewY)
    {
        transformable_ = true;
        skewY_ = skewY;
    }

    double GetTranslateX() const
    {
        return translateX_;
    }

    void SetTranslateX(double translateX)
    {
        transformable_ = true;
        translateX_ = translateX;
    }

    double GetTranslateY() const
    {
        return translateY_;
    }

    void SetTranslateY(double translateY)
    {
        transformable_ = true;
        translateY_ = translateY;
    }

    bool IsTransformable() const
    {
        return transformable_;
    }

    void SetPixelMap(const RefPtr<PixelMap>& pixelMap)
    {
        pixelMap_ = pixelMap;
    }

    RefPtr<PixelMap> GetPixelMap() const
    {
        return pixelMap_;
    }

private:
    double imageWidth_ = 0.0;
    double imageHeight_ = 0.0;
    double scaleX_ = 0.0;
    double skewX_ = 0.0;
    double skewY_ = 0.0;
    double scaleY_ = 0.0;
    double translateX_ = 0.0;
    double translateY_ = 0.0;
    bool transformable_ = false;
    std::string imgSrc_;
    std::string repetition_;
    RefPtr<PixelMap> pixelMap_;
};

enum class PathCmd {
    CMDS,
    TRANSFORM,
    MOVE_TO,
    LINE_TO,
    ARC,
    ARC_TO,
    QUADRATIC_CURVE_TO,
    BEZIER_CURVE_TO,
    ELLIPSE,
    RECT,
    ROUND_RECT,
    CLOSE_PATH,
};

struct PathArgs {
    std::string cmds;
    double para1 = 0.0;
    double para2 = 0.0;
    double para3 = 0.0;
    double para4 = 0.0;
    double para5 = 0.0;
    double para6 = 0.0;
    double para7 = 0.0;
    double para8 = 0.0;
};

class ACE_FORCE_EXPORT CanvasPath2D : virtual public AceType {
    DECLARE_ACE_TYPE(CanvasPath2D, AceType)
public:
    CanvasPath2D() = default;
    ~CanvasPath2D() = default;
    explicit CanvasPath2D(const std::string& cmds);
    explicit CanvasPath2D(const RefPtr<CanvasPath2D>& path);
    void AddPath(const RefPtr<CanvasPath2D>& path);
    void SetTransform(double a, double b, double c, double d, double e, double f);
    void MoveTo(double x, double y);
    void LineTo(double x, double y);
    void Arc(double x, double y, double radius, double startAngle, double endAngle, double ccw);
    void ArcTo(double x1, double y1, double x2, double y2, double radius);
    void QuadraticCurveTo(double cpx, double cpy, double x, double y);
    void BezierCurveTo(double cp1x, double cp1y, double cp2x, double cp2y, double x, double y);
    void Ellipse(double x, double y, double radiusX, double radiusY, double rotation, double startAngle,
        double endAngle, double ccw);
    void Rect(double x, double y, double width, double height);
    void RoundRect(const class Rect& rect, const std::vector<double>& radii);
    void ClosePath();
    const std::vector<std::pair<PathCmd, PathArgs>>& GetCaches() const;
    std::string ToString() const;

private:
    std::vector<std::pair<PathCmd, PathArgs>> caches_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_DECORATION_H
