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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_GEOMETRY_POINT_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_GEOMETRY_POINT_H

#include "base/geometry/offset.h"
#include "base/utils/macros.h"
#include "base/utils/utils.h"

namespace OHOS::Ace {

class ACE_EXPORT Point {
public:
    Point() = default;
    ~Point() = default;
    Point(double x, double y) : x_(x), y_(y) {}

    double GetX() const
    {
        return x_;
    }

    double GetY() const
    {
        return y_;
    }

    void SetX(double x)
    {
        x_ = x;
    }

    void SetY(double y)
    {
        y_ = y;
    }

    void Rotate(const Point& center, double angle)
    {
        double x = (x_ - center.GetX()) * std::cos(angle) - (y_ - center.GetY()) * std::sin(angle) + center.GetX();
        double y = (x_ - center.GetX()) * std::sin(angle) + (y_ - center.GetY()) * std::cos(angle) + center.GetY();
        x_ = x;
        y_ = y;
    }

    Point operator-(const Offset& offset) const
    {
        return Point(x_ - offset.GetX(), y_ - offset.GetY());
    }

    Point operator+(const Offset& offset) const
    {
        return Point(x_ + offset.GetX(), y_ + offset.GetY());
    }

    Offset operator-(const Point& point) const
    {
        return Offset(x_ - point.x_, y_ - point.y_);
    }

    bool operator==(const Point& point) const
    {
        return NearEqual(x_, point.x_) && NearEqual(y_, point.y_);
    }

    bool operator!=(const Point& point) const
    {
        return !operator==(point);
    }

private:
    double x_ = 0.0;
    double y_ = 0.0;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_GEOMETRY_POINT_H
