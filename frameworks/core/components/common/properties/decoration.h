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
#include <vector>

#include "base/geometry/dimension.h"
#include "base/geometry/rect.h"
#include "base/image/pixel_map.h"
#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "base/utils/utils.h"
#include "core/components/common/properties/animatable_color.h"
#include "core/components/common/properties/blend_mode.h"
#include "core/components/common/properties/blur_style_option.h"
#include "core/components/common/properties/border.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/edge.h"
#include "core/components/common/properties/gradient.h"
#include "core/components/common/properties/haptic_feedback_mode.h"
#include "core/components/common/properties/modal_mode.h"
#include "core/components/common/properties/menu_preview_animation_options.h"
#include "core/components/common/properties/shadow.h"
#include "core/components/common/properties/sys_options.h"

namespace OHOS::Ace {

class BackgroundImage;
class BorderImage;
class PixelMap;
class PipelineContext;

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
    ACE_FORCE_EXPORT Decoration();
    ACE_FORCE_EXPORT ~Decoration() override;

    ACE_FORCE_EXPORT void SetContextAndCallback(
        const WeakPtr<PipelineContext>& context, const RenderNodeAnimationCallback& callback);

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

    ACE_FORCE_EXPORT void SetGradient(const Gradient& gradient, const WeakPtr<PipelineContext>& context = nullptr,
        const RenderNodeAnimationCallback& callback = nullptr);

    void SetBorderImageGradient(const Gradient& gradient)
    {
        gradientBorderImage_ = gradient;
    }
    ACE_FORCE_EXPORT void SetImage(const RefPtr<BackgroundImage>& image);

    void SetBorderImage(const RefPtr<BorderImage>& borderImage);

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

    ACE_FORCE_EXPORT const RefPtr<BackgroundImage>& GetImage() const;

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

    bool NeedReloadImage(const RefPtr<Decoration>& lastDecoration) const;

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
    ACE_FORCE_EXPORT double HorizontalSpaceOccupied(double dipScale) const;
    ACE_FORCE_EXPORT double VerticalSpaceOccupied(double dipScale) const;

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
    DECLARE_ACE_TYPE(CanvasPath2D, AceType);
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
