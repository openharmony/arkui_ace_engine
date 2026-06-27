/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "base/geometry/point.h"

#include <cmath>

#include "ui/base/geometry/offset.h"
#include "ui/base/utils/utils.h"

namespace OHOS::Ace {

void Point::Rotate(const Point& center, double angle)
{
    double x = (x_ - center.GetX()) * std::cos(angle) - (y_ - center.GetY()) * std::sin(angle) + center.GetX();
    double y = (x_ - center.GetX()) * std::sin(angle) + (y_ - center.GetY()) * std::cos(angle) + center.GetY();
    x_ = x;
    y_ = y;
}

Point Point::operator-(const Offset& offset) const
{
    return Point(x_ - offset.GetX(), y_ - offset.GetY());
}

Point Point::operator+(const Offset& offset) const
{
    return Point(x_ + offset.GetX(), y_ + offset.GetY());
}

Offset Point::operator-(const Point& point) const
{
    return Offset(x_ - point.x_, y_ - point.y_);
}

bool Point::operator==(const Point& point) const
{
    return NearEqual(x_, point.x_) && NearEqual(y_, point.y_);
}

bool Point::operator!=(const Point& point) const
{
    return !operator==(point);
}

} // namespace OHOS::Ace
