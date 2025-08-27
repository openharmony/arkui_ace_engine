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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_GEOMETRY_SHAPE_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_GEOMETRY_SHAPE_H

#include "base/geometry/dimension.h"
#include "base/geometry/dimension_offset.h"
#include "base/memory/ace_type.h"
#include "core/common/resource/resource_object.h"
#include "core/components/common/properties/color.h"
#ifndef FUZZTEST
#include "core/components/common/properties/radius.h"
#else
#include "test/fuzztest/utilmost_fuzzer/radius.h"
#endif

namespace OHOS::Ace {

using ShapePoint = std::pair<Dimension, Dimension>;
using ShapePoints = std::vector<ShapePoint>;

enum class ShapeType {
    RECT = 0,
    CIRCLE,
    ELLIPSE,
    LINE,
    POLYGON,
    POLYLINE,
    PATH,
};

enum class BasicShapeType { NONE, INSET, CIRCLE, ELLIPSE, POLYGON, PATH, RECT };

class BasicShape : public AceType {
    DECLARE_ACE_TYPE(BasicShape, AceType);

public:
    BasicShape() = default;
    explicit BasicShape(BasicShapeType basicShapeType) : basicShapeType_(basicShapeType) {}
    ~BasicShape() override = default;

    void SetBasicShapeType(BasicShapeType basicShapeType)
    {
        basicShapeType_ = basicShapeType;
    }

    BasicShapeType GetBasicShapeType() const
    {
        return basicShapeType_;
    }

    const Dimension& GetWidth() const
    {
        return width_;
    }

    const Dimension& GetHeight() const
    {
        return height_;
    }

    const DimensionOffset& GetOffset() const
    {
        return offset_;
    }

    void SetWidth(const Dimension& width)
    {
        width_ = width;
    }

    void SetHeight(const Dimension& height)
    {
        height_ = height;
    }

    void SetOffset(const DimensionOffset& offset)
    {
        offset_ = offset;
    }

    void SetColor(const Color& color)
    {
        color_ = color;
    }

    void SetPosition(const DimensionOffset& position)
    {
        position_ = position;
    }

    const DimensionOffset& GetPosition() const
    {
        return position_;
    }

    Color GetColor() const
    {
        return color_;
    }

    void SetStrokeColor(uint32_t strokeColor)
    {
        strokeColor_ = strokeColor;
    }

    uint32_t GetStrokeColor() const
    {
        return strokeColor_;
    }

    void SetStrokeWidth(float strokeWidth)
    {
        strokeWidth_ = strokeWidth;
    }

    float GetStrokeWidth() const
    {
        return strokeWidth_;
    }

    bool operator==(const BasicShape& other) const
    {
        return (basicShapeType_ == other.GetBasicShapeType() && width_ == other.GetWidth() &&
                height_ == other.GetHeight() && offset_ == other.GetOffset() && color_ == other.GetColor());
    }

    BasicShape& operator=(const BasicShape& other)
    {
        if (this != &other) {
            basicShapeType_ = other.basicShapeType_;
            width_ = other.width_;
            height_ = other.height_;
            offset_ = other.offset_;
            color_ = other.color_;
        }
        return *this;
    }

    void AddResource(
        const std::string& key,
        const RefPtr<ResourceObject>& resObj,
        std::function<void(const RefPtr<ResourceObject>&, BasicShape&)>&& updateFunc)
    {
        if (resObj == nullptr || !updateFunc) {
            return;
        }
        resMap_[key] = {resObj, std::move(updateFunc)};
    }

    void ReloadResources()
    {
        for (const auto& [key, resourceUpdater] : resMap_) {
            resourceUpdater.updateFunc(resourceUpdater.resObj, *this);
        }
    }
protected:
    BasicShapeType basicShapeType_ = BasicShapeType::NONE;
    Dimension width_;
    Dimension height_;
    DimensionOffset offset_;
    DimensionOffset position_;
    Color color_;
    uint32_t strokeColor_ = 0;
    float strokeWidth_ = 0.0f;
    struct ResourceUpdater {
        RefPtr<ResourceObject> resObj;
        std::function<void(const RefPtr<ResourceObject>&, BasicShape&)> updateFunc;
    };
    std::unordered_map<std::string, ResourceUpdater> resMap_;
};

// inset(<top> <right> <bottom> <left> round <top-radius> <right-radius> <bottom-radius> <left-radius>)
class Inset : public BasicShape {
    DECLARE_ACE_TYPE(Inset, BasicShape);

public:
    Inset() : BasicShape(BasicShapeType::INSET) {}
    ~Inset() override = default;
    bool SetLength(const std::vector<Dimension>& lengths);
    void SetRadius(const std::vector<Dimension>& rounds, bool isX = true);

    const Dimension& GetTop() const
    {
        return top_;
    }

    const Dimension& GetRight() const
    {
        return right_;
    }

    const Dimension& GetBottom() const
    {
        return bottom_;
    }

    const Dimension& GetLeft() const
    {
        return left_;
    }

    const Radius& GetTopLeftRadius() const
    {
        return topLeftRadius_;
    }

    const Radius& GetTopRightRadius() const
    {
        return topRightRadius_;
    }

    const Radius& GetBottomRightRadius() const
    {
        return bottomRightRadius_;
    }

    const Radius& GetBottomLeftRadius() const
    {
        return bottomLeftRadius_;
    }

    void SetTop(const Dimension& top)
    {
        top_ = top;
    }

    void SetRight(const Dimension& right)
    {
        right_ = right;
    }

    void SetBottom(const Dimension& bottom)
    {
        bottom_ = bottom;
    }

    void SetLeft(const Dimension& left)
    {
        left_ = left;
    }

    void SetTopLeftRadius(const Dimension& topLeftRadius, bool isX = true)
    {
        if (!topLeftRadius.IsValid()) {
            return;
        }
        if (isX) {
            topLeftRadius_.SetX(topLeftRadius);
        }
        topLeftRadius_.SetY(topLeftRadius);
    }

    void SetTopRightRadius(const Dimension& topRightRadius, bool isX = true)
    {
        if (!topRightRadius.IsValid()) {
            return;
        }
        if (isX) {
            topRightRadius_.SetX(topRightRadius);
        }
        topRightRadius_.SetY(topRightRadius);
    }

    void SetBottomRightRadius(const Dimension& bottomRightRadius, bool isX = true)
    {
        if (!bottomRightRadius.IsValid()) {
            return;
        }
        if (isX) {
            bottomRightRadius_.SetX(bottomRightRadius);
        }
        bottomRightRadius_.SetY(bottomRightRadius);
    }

    void SetBottomLeftRadius(const Dimension& bottomLeftRadius, bool isX = true)
    {
        if (!bottomLeftRadius.IsValid()) {
            return;
        }
        if (isX) {
            bottomLeftRadius_.SetX(bottomLeftRadius);
        }
        bottomLeftRadius_.SetY(bottomLeftRadius);
    }

private:
    void SetLength(const Dimension& top, const Dimension& right, const Dimension& bottom, const Dimension& left);
    void SetRadius(
        const Dimension& top, const Dimension& right, const Dimension& bottom, const Dimension& left, bool isX);

    Dimension top_;
    Dimension right_;
    Dimension bottom_;
    Dimension left_;
    Radius topLeftRadius_;
    Radius topRightRadius_;
    Radius bottomRightRadius_;
    Radius bottomLeftRadius_;
};

// circle(radius at x-axis y-axis)
class Circle : public BasicShape {
    DECLARE_ACE_TYPE(Circle, BasicShape);

public:
    Circle() : BasicShape(BasicShapeType::CIRCLE) {}
    ~Circle() override = default;

    const Dimension& GetRadius() const
    {
        return radius_;
    }

    const Dimension& GetAxisX() const
    {
        return axisX_;
    }

    const Dimension& GetAxisY() const
    {
        return axisY_;
    }

    void SetRadius(const Dimension& radius)
    {
        if (radius.IsValid()) {
            radius_ = radius;
        }
    }

    void SetAxisX(const Dimension& axisX)
    {
        axisX_ = axisX;
    }

    void SetAxisY(const Dimension& axisY)
    {
        axisY_ = axisY;
    }

    bool operator==(const Circle& other) const
    {
        return (radius_ == other.GetRadius() && axisX_ == other.GetAxisX() && axisY_ == other.GetAxisY());
    }

private:
    Dimension radius_;
    Dimension axisX_ = Dimension(0.5, DimensionUnit::PERCENT);
    Dimension axisY_ = Dimension(0.5, DimensionUnit::PERCENT);
};

// ellipse(x-rad y-rad at x-axis y-axis)
class Ellipse : public BasicShape {
    DECLARE_ACE_TYPE(Ellipse, BasicShape);

public:
    Ellipse() : BasicShape(BasicShapeType::ELLIPSE) {}
    ~Ellipse() override = default;

    const Dimension& GetRadiusX() const
    {
        return radiusX_;
    }

    const Dimension& GetRadiusY() const
    {
        return radiusY_;
    }

    const Dimension& GetAxisX() const
    {
        return axisX_;
    }

    const Dimension& GetAxisY() const
    {
        return axisY_;
    }

    void SetRadiusX(const Dimension& radiusX)
    {
        if (radiusX.IsValid()) {
            radiusX_ = radiusX;
        }
    }

    void SetRadiusY(const Dimension& radiusY)
    {
        if (radiusY.IsValid()) {
            radiusY_ = radiusY;
        }
    }

    void SetAxisX(const Dimension& axisX)
    {
        axisX_ = axisX;
    }

    void SetAxisY(const Dimension& axisY)
    {
        axisY_ = axisY;
    }

    bool operator==(const Ellipse& other) const
    {
        return (radiusX_ == other.GetRadiusX() && radiusY_ == other.GetRadiusY() && axisX_ == other.GetAxisX() &&
                axisY_ == other.GetAxisY());
    }

private:
    Dimension radiusX_;
    Dimension radiusY_;
    Dimension axisX_ = Dimension(0.5, DimensionUnit::PERCENT);
    Dimension axisY_ = Dimension(0.5, DimensionUnit::PERCENT);
};

// polygon(x-axis y-axis, x-axis y-axis, … )
class Polygon : public BasicShape {
    DECLARE_ACE_TYPE(Polygon, BasicShape);

public:
    Polygon() : BasicShape(BasicShapeType::POLYGON) {}
    ~Polygon() override = default;

    const std::vector<std::pair<Dimension, Dimension>>& GetPoints() const
    {
        return points_;
    }

    void PushPoint(const Dimension& x, const Dimension& y)
    {
        points_.emplace_back(std::make_pair(x, y));
    }

    bool IsValid() const
    {
        return !points_.empty();
    }

    bool operator==(const Polygon& other) const
    {
        return points_ == other.GetPoints();
    }

private:
    std::vector<std::pair<Dimension, Dimension>> points_;
};

// path('value')
class Path : public BasicShape {
    DECLARE_ACE_TYPE(Path, BasicShape);

public:
    Path() : BasicShape(BasicShapeType::PATH) {}
    ~Path() override = default;

    const std::string& GetValue() const
    {
        return value_;
    }

    void SetValue(const std::string& value)
    {
        value_ = value;
    }

    bool operator==(const Path& other) const
    {
        return value_ == other.GetValue();
    }

private:
    std::string value_;
};

class ShapeRect : public BasicShape {
    DECLARE_ACE_TYPE(ShapeRect, BasicShape);

public:
    ShapeRect() : BasicShape(BasicShapeType::RECT) {}
    ~ShapeRect() override = default;

    void SetTopLeftRadius(const Radius& topLeftRadius)
    {
        topLeftRadius_ = topLeftRadius;
    }

    void SetTopRightRadius(const Radius& topRightRadius)
    {
        topRightRadius_ = topRightRadius;
    }

    void SetBottomRightRadius(const Radius& bottomRightRadius)
    {
        bottomRightRadius_ = bottomRightRadius;
    }

    void SetBottomLeftRadius(const Radius& bottomLeftRadius)
    {
        bottomLeftRadius_ = bottomLeftRadius;
    }

    Radius GetTopLeftRadius() const
    {
        return topLeftRadius_;
    }

    Radius GetTopRightRadius() const
    {
        return topRightRadius_;
    }

    Radius GetBottomRightRadius() const
    {
        return bottomRightRadius_;
    }

    Radius GetBottomLeftRadius() const
    {
        return bottomLeftRadius_;
    }

    void SetRadiusWidth(const Dimension& value, const AnimationOption& option = AnimationOption())
    {
        topLeftRadius_.SetX(value, option);
        topRightRadius_.SetX(value, option);
        bottomRightRadius_.SetX(value, option);
        bottomLeftRadius_.SetX(value, option);
    }

    void SetRadiusHeight(const Dimension& value, const AnimationOption& option = AnimationOption())
    {
        topLeftRadius_.SetY(value, option);
        topRightRadius_.SetY(value, option);
        bottomRightRadius_.SetY(value, option);
        bottomLeftRadius_.SetY(value, option);
    }

private:
    Radius topLeftRadius_ = Radius(-1.0);
    Radius topRightRadius_ = Radius(-1.0);
    Radius bottomRightRadius_ = Radius(-1.0);
    Radius bottomLeftRadius_ = Radius(-1.0);
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_GEOMETRY_SHAPE_H