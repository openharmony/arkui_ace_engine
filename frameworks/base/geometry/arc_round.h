/*
 * Copyright (c) 2021-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_ROUND_FRAMEWORKS_BASE_GEOMETRY_ARC_H
#define FOUNDATION_ACE_ROUND_FRAMEWORKS_BASE_GEOMETRY_ARC_H

#include "base/geometry/point.h"
#include "base/utils/utils.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/layout/constants.h"

constexpr float ARC_ROUND_RADIUS_TO_DIAMETER = 2.0;
constexpr float HALF = 0.5;
constexpr float SQUARE = 2.0;
constexpr float HALF_CIRCULARITY = 180;
constexpr float WHOLE_CIRCULARITY = 360;

namespace OHOS::Ace {

class ArcRound {
public:
    ArcRound() = default;
    ~ArcRound() = default;

    ArcRound(const ArcRound& other);
    ArcRound(Point centerPoint, float radius, float startAngle, float sweepAngle, float width);
    ArcRound& operator=(const ArcRound& arc);

    void Rotate(const Point& point, float angle);
    void Move(float xOffset, float yOffset);
    void GetPointByAngle(float angle, Point& out) const;
    float GetPositionAngle(const Offset& position) const;
    Point GetStartPoint() const;
    Point GetEndPoint() const;
    void SetOuterRadius(float outerRadius);
    void SetWidth(float width);
    bool IsInRegion(const Point& point) const;

    const Point& GetCenterPoint() const
    {
        return centerPoint_;
    }

    void SetCenterPoint(const Point& point)
    {
        centerPoint_ = point;
    }

    float GetRadius() const
    {
        return radius_;
    }

    void SetRadius(float radius)
    {
        radius_ = radius;
    }

    float GetStartAngle() const
    {
        return startAngle_;
    }

    void SetStartAngle(float angle)
    {
        startAngle_ = angle;
    }

    float GetStepAngle() const
    {
        return stepAngle_;
    }

    void SetStepAngle(float angle)
    {
        stepAngle_ = angle;
    }

    float GetEndAngle() const
    {
        return endAngle_;
    }

    void SetEndAngle(float angle)
    {
        endAngle_ = angle;
    }

    void GetStartPoint(Point& out) const
    {
        GetPointByAngle(startAngle_, out);
    }

    void GetEndPoint(Point& out) const
    {
        GetPointByAngle(endAngle_, out);
    }

    float GetLeft() const
    {
        return centerPoint_.GetX() - radius_;
    }

    float GetRight() const
    {
        return centerPoint_.GetX() + radius_;
    }

    float GetTop() const
    {
        return centerPoint_.GetY() - radius_;
    }

    float GetBottom() const
    {
        return centerPoint_.GetY() + radius_;
    }

    float GetOuterRadius() const
    {
        return outerRadius_;
    }

    float GetWidth() const
    {
        return width_;
    }

    float GetSweepAngle() const
    {
        return sweepAngle_;
    }

    Color GetColor() const
    {
        return color_;
    }

    void SetSweepAngle(float sweepAngle)
    {
        sweepAngle_ = sweepAngle;
    }

    void SetColor(const Color& color)
    {
        color_ = color;
    }

    bool IsAcrValid() const
    {
        return !NearZero(sweepAngle_);
    }

    bool IsArcShow() const
    {
        return color_.GetAlpha() != 0;
    }

    float GetShadowWidth() const
    {
        return shadowWidth_;
    }

    void SetPositionMode(PositionMode positionMode)
    {
        positionMode_ = positionMode;
    }

private:
    Point centerPoint_;
    float radius_ = 0.0;
    float startAngle_ = 0.0;
    float endAngle_ = 0.0;
    float stepAngle_ = 0.0;

    float sweepAngle_ = 0.0;
    float outerRadius_ = 0.0;
    float width_ = 0.0;
    Color color_ = Color::WHITE;
    float shadowWidth_ = 0.0;
    PositionMode positionMode_ = PositionMode::RIGHT;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_ROUND_FRAMEWORKS_BASE_GEOMETRY_ARC_H
