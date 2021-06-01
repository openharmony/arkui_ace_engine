/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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
#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "core/components/common/properties/alignment.h"
#include "core/components/common/properties/border.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/edge.h"
#include "core/components/common/properties/shadow.h"

namespace OHOS::Ace {

constexpr double CENTER_OFFSET = 50.0;
constexpr double FULL_IMG_SIZE = 100.0;
constexpr double BOX_BEGIN_SIZE = 0.0;
constexpr double BOX_END_SIZE = 100.0;
constexpr double PERCENT_TRANSLATE = 100.0;

enum class GradientDirection {
    LEFT = 0,
    LEFT_TOP,
    TOP,
    RIGHT_TOP,
    RIGHT,
    RIGHT_BOTTOM,
    BOTTOM,
    LEFT_BOTTOM,
    START_TO_END,
    END_TO_START,
};

enum class GradientType {
    LINEAR,
    RADIAL,
    CONIC,
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

private:
    bool hasValue_ = true;
    Color color_ { Color::TRANSPARENT };
    Dimension dimension_ { BOX_END_SIZE, DimensionUnit::PERCENT };
};

class ACE_EXPORT Gradient final {
public:
    void AddColor(const GradientColor& color);

    void ClearColors();

    bool IsValid() const
    {
        return colors_.size() > 1;
    }

    void SetDirection(GradientDirection direction)
    {
        direction_ = direction;
    }

    void SetRepeat(bool repeat)
    {
        repeat_ = repeat;
    }

    void SetAngle(double angle)
    {
        angle_ = angle;
    }

    void SetUseAngle(bool useAngle)
    {
        useAngle_ = useAngle;
    }

    GradientDirection GetDirection() const
    {
        return direction_;
    }

    bool GetRepeat() const
    {
        return repeat_;
    }

    double GetAngle() const
    {
        return angle_;
    }

    bool GetUseAngle() const
    {
        return useAngle_;
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
            .append(",").append(std::to_string(innerRadius_))
            .append(" --- ")
            .append(endOffset_.ToString())
            .append(",").append(std::to_string(outerRadius_))
            .append(")");
    }

private:
    GradientDirection direction_ { GradientDirection::LEFT };
    double angle_ = 0.0;
    bool repeat_ = false;
    std::vector<GradientColor> colors_;
    bool useAngle_ = false;

    GradientType type_ = GradientType::LINEAR;
    // used for CanvasLinearGradient
    Offset beginOffset_;
    Offset endOffset_;
    // used for CanvasRadialGradient
    double innerRadius_ = 0.0;
    double outerRadius_ = 0.0;
};

enum class ACE_EXPORT BackgroundImageSizeType {
    CONTAIN = 0,
    COVER,
    AUTO,
    LENGTH,
    PERCENT,
};

class ACE_EXPORT BackgroundImageSize final {
public:
    BackgroundImageSize() = default;
    BackgroundImageSize(BackgroundImageSizeType type, double value) : typeX_(type), valueX_(value) {}
    BackgroundImageSize(BackgroundImageSizeType typeX, double valueX, BackgroundImageSizeType typeY, double valueY)
        : typeX_(typeX), valueX_(valueX), typeY_(typeY), valueY_(valueY) {}
    ~BackgroundImageSize() = default;

    void SetSizeTypeX(BackgroundImageSizeType type);
    void SetSizeTypeY(BackgroundImageSizeType type);
    void SetSizeValueX(double value);
    void SetSizeValueY(double value);
    bool IsValid() const;
    BackgroundImageSizeType GetSizeTypeX() const;
    BackgroundImageSizeType GetSizeTypeY() const;
    double GetSizeValueX() const;
    double GetSizeValueY() const;

    bool operator==(const BackgroundImageSize& size) const;
    bool operator!=(const BackgroundImageSize& size) const;

private:
    BackgroundImageSizeType typeX_ { BackgroundImageSizeType::AUTO };
    double valueX_ = 0.0;
    BackgroundImageSizeType typeY_ { BackgroundImageSizeType::AUTO };
    double valueY_ = 0.0;
};

enum class ACE_EXPORT BackgroundImagePositionType {
    PERCENT = 0,
    PX,
};

class ACE_EXPORT BackgroundImagePosition final {
public:
    BackgroundImagePosition() = default;
    ~BackgroundImagePosition() = default;
    BackgroundImagePosition(
        BackgroundImagePositionType typeX, double valueX, BackgroundImagePositionType typeY, double valueY)
        : typeX_(typeX), typeY_(typeY), valueX_(valueX), valueY_(valueY) {}

    void SetSizeTypeX(BackgroundImagePositionType type)
    {
        typeX_ = type;
    }

    void SetSizeX(const Dimension& sizeX)
    {
        if (sizeX.Unit() == DimensionUnit::PERCENT) {
            typeX_ = BackgroundImagePositionType::PERCENT;
        } else {
            typeX_ = BackgroundImagePositionType::PX;
        }
        valueX_ = sizeX.Value();
    }

    void SetSizeTypeY(BackgroundImagePositionType type)
    {
        typeY_ = type;
    }

    void SetSizeY(const Dimension& sizeY)
    {
        if (sizeY.Unit() == DimensionUnit::PERCENT) {
            typeY_ = BackgroundImagePositionType::PERCENT;
        } else {
            typeY_ = BackgroundImagePositionType::PX;
        }
        valueY_ = sizeY.Value();
    }

    void SetSizeValueX(double value)
    {
        valueX_ = value;
    }

    void SetSizeValueY(double value)
    {
        valueY_ = value;
    }

    BackgroundImagePositionType GetSizeTypeX() const
    {
        return typeX_;
    }

    BackgroundImagePositionType GetSizeTypeY() const
    {
        return typeY_;
    }

    double GetSizeValueX() const
    {
        return valueX_;
    }

    double GetSizeValueY() const
    {
        return valueY_;
    }

    BackgroundImagePosition operator+(const BackgroundImagePosition& position) const;

    BackgroundImagePosition operator-(const BackgroundImagePosition& position) const;

    BackgroundImagePosition operator*(double value) const;

    bool operator==(const BackgroundImagePosition& backgroundImagePosition) const;

    bool operator!=(const BackgroundImagePosition& backgroundImagePosition) const;

private:
    BackgroundImagePositionType typeX_ { BackgroundImagePositionType::PX };
    BackgroundImagePositionType typeY_ { BackgroundImagePositionType::PX };
    double valueX_ = 0.0;
    double valueY_ = 0.0;
};

class BackgroundImage final : public AceType {
    DECLARE_ACE_TYPE(BackgroundImage, AceType);

public:
    BackgroundImage() = default;
    explicit BackgroundImage(const std::string& src)
    {
        src_ = src;
    }

    ~BackgroundImage() override = default;

    const BackgroundImageSize& GetImageSize() const
    {
        return imageSize_;
    }

    const BackgroundImagePosition& GetImagePosition() const
    {
        return imagePosition_;
    }

    ImageRepeat GetImageRepeat() const
    {
        return imageRepeat_;
    }

    const std::string& GetSrc() const
    {
        return src_;
    }

    void SetImageSize(BackgroundImageSizeType type, double value = FULL_IMG_SIZE)
    {
        imageSize_ = BackgroundImageSize(type, value);
    }

    void SetImageSize(BackgroundImageSizeType typeX, double valueX, BackgroundImageSizeType typeY, double valueY)
    {
        imageSize_ = BackgroundImageSize(typeX, valueX, typeY, valueY);
    }

    void SetImagePosition(const BackgroundImagePosition& imagePosition)
    {
        imagePosition_ = imagePosition;
    }

    void SetImagePosition(
        BackgroundImagePositionType typeX, double valueX, BackgroundImagePositionType typeY, double valueY)
    {
        imagePosition_ = BackgroundImagePosition(typeX, valueX, typeY, valueY);
    }

    void SetImageRepeat(const ImageRepeat& imageRepeat)
    {
        imageRepeat_ = imageRepeat;
    }

    void SetSrc(const std::string& src)
    {
        src_ = src;
    }

    bool operator==(const BackgroundImage& image) const
    {
        bool fileName = src_ == image.GetSrc();
        bool size = imageSize_ == image.GetImageSize();
        bool position = imagePosition_ == image.GetImagePosition();
        bool repeat = imageRepeat_ == image.GetImageRepeat();
        return fileName && size && position && repeat;
    }

    bool operator!=(const BackgroundImage& image) const
    {
        return !operator==(image);
    }

private:
    std::string src_;
    BackgroundImageSize imageSize_;
    BackgroundImagePosition imagePosition_;
    ImageRepeat imageRepeat_ { ImageRepeat::REPEAT };
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

    void AddShadow(const Shadow& shadow);

    void ClearAllShadow();

    void SetBackgroundColor(const Color& backgroundColor)
    {
        backgroundColor_ = backgroundColor;
    }

    void SetAnimationColor(const Color& animationColor)
    {
        animationColor_ = animationColor;
    }

    void SetGradient(const Gradient& gradient)
    {
        gradient_ = gradient;
    }

    void SetImage(const RefPtr<BackgroundImage>& image)
    {
        image_ = image;
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

    void SetWindowBlurProgress(float progress)
    {
        windowBlurProgress_ = progress;
    }

    void SetWindowBlurStyle(WindowBlurStyle style)
    {
        windowBlurStyle_ = style;
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

    const Gradient& GetGradient() const
    {
        return gradient_;
    }

    const Color& GetBackgroundColor() const
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

    const Dimension& GetBlurRadius() const
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

    // Indicate how much size the decoration taken, excluding the content size.
    Size GetOccupiedSize(double dipScale) const;
    double HorizontalSpaceOccupied(double dipScale) const;
    double VerticalSpaceOccupied(double dipScale) const;

    Offset GetOffset(double dipScale) const;

private:
    // padding is zero
    Edge padding_;
    // border contains black color and 1.0f thickness as default
    Border border_;
    // shadow vector is empty
    std::vector<Shadow> shadows_;
    // color is transparent
    Color backgroundColor_ = Color::TRANSPARENT;
    Color animationColor_ = Color::TRANSPARENT;
    // Gradient is not implemented
    Gradient gradient_ = Gradient();
    RefPtr<BackgroundImage> image_;
    RefPtr<ArcBackground> arcBG_;
    // Blur radius
    Dimension blurRadius_;
    // window blur progress
    float windowBlurProgress_ = 0.0f;
    // window blur style;
    WindowBlurStyle windowBlurStyle_ = WindowBlurStyle::STYLE_BACKGROUND_SMALL_LIGHT;
};

class Pattern final {
public:
    bool IsValid() const
    {
        return !imgSrc_.empty();
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

private:
    double imageWidth_ = 0.0;
    double imageHeight_ = 0.0;
    std::string imgSrc_;
    std::string repetition_;
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

class ACE_EXPORT CanvasPath2D : virtual public AceType {
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
    void Ellipse(double x, double y, double radiusX, double radiusY,
        double rotation, double startAngle, double endAngle, double ccw);
    void Rect(double x, double y, double width, double height);
    void ClosePath();
    const std::vector<std::pair<PathCmd, PathArgs>>& GetCaches() const;
    std::string ToString() const;

private:
    std::vector<std::pair<PathCmd, PathArgs>> caches_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_DECORATION_H
