/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_GEOMETRY_NG_RADIUST_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_GEOMETRY_NG_RADIUST_H

#include <string>

#include "base/geometry/dimension.h"
namespace OHOS::Ace::NG {
class Radius final {
public:
    Radius() = default;
    explicit Radius(double value) : Radius(value, value) {}
    explicit Radius(const Dimension& value) : Radius(value, value) {}
    Radius(double x, double y) : x_(Dimension(x)), y_(Dimension(y)) {}
    Radius(const Dimension& x, const Dimension& y) : x_(x), y_(y) {}
    ~Radius() = default;

    bool IsValid() const
    {
        return x_.IsValid() && y_.IsValid();
    }

    bool HasValue() const
    {
        return x_.IsValid() || y_.IsValid();
    }

    Dimension GetX() const
    {
        return x_;
    }

    Dimension GetY() const
    {
        return y_;
    }

    void SetX(const Dimension& x)
    {
        // bug to fix: unit of x will be convert to PX
        x_ = Dimension(x);
    }

    void SetY(const Dimension& y)
    {
        // bug to fix: unit of x will be convert to PX
        y_ = Dimension(y);
    }

    Radius operator+(const Radius& radius) const
    {
        return Radius(x_ + radius.x_, y_ + radius.y_);
    }

    Radius operator-(const Radius& radius) const
    {
        return Radius(x_ - radius.x_, y_ - radius.y_);
    }

    bool operator==(const Radius& radius) const
    {
        return (radius.x_ == x_) && (radius.y_ == y_);
    }

    bool operator!=(const Radius& radius) const
    {
        return (radius.x_ != x_) || (radius.y_ != y_);
    }

    Radius operator=(const Radius& radius)
    {
        x_ = radius.x_;
        y_ = radius.y_;
        return *this;
    }

    std::string ToString() const
    {
        return std::string("x:").append(x_.ToString()).append(", y:").append(y_.ToString());
    }

private:
    Dimension x_;
    Dimension y_;
};
} // namespace OHOS::Ace::NG
#endif