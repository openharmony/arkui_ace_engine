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

#ifndef POINT3_H
#define POINT3_H

#include <string>
#include "utils/scalar.h"

namespace OHOS {
namespace Rosen {
namespace Drawing {
class Point3 {
public:
    inline Point3() noexcept;
    inline Point3(const Point3& p) noexcept;
    inline Point3(scalar x, scalar y, scalar z) noexcept;

    inline ~Point3() {}

    inline scalar GetX() const;
    inline scalar GetY() const;
    inline scalar GetZ() const;

    inline void SetX(scalar x);
    inline void SetY(scalar y);
    inline void SetZ(scalar z);

    inline Point3& operator+=(const Point3& p);
    inline Point3& operator-=(const Point3& p);
    inline Point3& operator*=(scalar scale);
    inline Point3& operator/=(scalar divisor);

    friend inline const Point3 operator+(const Point3& p1, const Point3& p2);
    friend inline const Point3 operator-(const Point3& p1, const Point3& p2);
    friend inline const Point3 operator*(scalar scale, const Point3& p);
    friend inline const Point3 operator*(const Point3& p, scalar scale);
    friend inline const Point3 operator/(const Point3& p, scalar divisor);
    friend inline const Point3 operator+(const Point3& p);
    friend inline const Point3 operator-(const Point3& p);
    friend inline bool operator==(const Point3& p1, const Point3& p2);
    friend inline bool operator!=(const Point3& p1, const Point3& p2);
private:
    scalar x_;
    scalar y_;
    scalar z_;
};

inline Point3::Point3() noexcept : x_(0.0), y_(0.0), z_(0.0) {}

inline Point3::Point3(const Point3& p) noexcept
{
    // Tell the compiler there is no alias and to select wider load/store instructions.
    scalar x = p.GetX();
    scalar y = p.GetY();
    scalar z = p.GetZ();
    x_ = x;
    y_ = y;
    z_ = z;
}

inline Point3::Point3(scalar x, scalar y, scalar z) noexcept : x_(x), y_(y), z_(z) {}

inline scalar Point3::GetX() const
{
    return x_;
}

inline scalar Point3::GetY() const
{
    return y_;
}

inline scalar Point3::GetZ() const
{
    return z_;
}

inline void Point3::SetX(scalar x)
{
    x_ = x;
}

inline void Point3::SetY(scalar y)
{
    y_ = y;
}

inline void Point3::SetZ(scalar z)
{
    z_ = z;
}

inline Point3& Point3::operator+=(const Point3& p)
{
    x_ += p.x_;
    y_ += p.y_;
    z_ += p.z_;
    return *this;
}

inline Point3& Point3::operator-=(const Point3& p)
{
    x_ -= p.x_;
    y_ -= p.y_;
    z_ -= p.z_;
    return *this;
}

inline Point3& Point3::operator*=(scalar scale)
{
    x_ = static_cast<int64_t>(x_ * scale);
    y_ = static_cast<int64_t>(y_ * scale);
    z_ = static_cast<int64_t>(z_ * scale);
    return *this;
}

inline Point3& Point3::operator/=(scalar divisor)
{
    if (divisor == 0) {
        return *this;
    }
    x_ = static_cast<int>(x_ / divisor);
    y_ = static_cast<int>(y_ / divisor);
    z_ = static_cast<int>(z_ / divisor);
    return *this;
}

inline const Point3 operator+(const Point3& p1, const Point3& p2)
{
    return Point3(p1.x_ + p2.x_, p1.y_ + p2.y_, p1.z_ + p2.z_);
}

inline const Point3 operator-(const Point3& p1, const Point3& p2)
{
    return Point3(p1.x_ - p2.x_, p1.y_ - p2.y_, p1.z_ - p2.z_);
}

inline const Point3 operator*(scalar scale, const Point3& p)
{
    return Point3(
        static_cast<int64_t>(scale * p.x_), static_cast<int64_t>(scale * p.y_), static_cast<int64_t>(scale * p.z_));
}

inline const Point3 operator*(const Point3& p, scalar scale)
{
    return Point3(
        static_cast<int64_t>(p.x_ * scale), static_cast<int64_t>(p.y_ * scale), static_cast<int64_t>(p.z_ * scale));
}

inline const Point3 operator/(const Point3& p, scalar divisor)
{
    if (divisor == 0) {
        return Point3(p.x_, p.y_, p.z_);
    }
    return Point3(p.x_ / divisor, p.y_ / divisor, p.z_ / divisor);
}

inline const Point3 operator+(const Point3& p)
{
    return Point3(p.x_, p.y_, p.z_);
}

inline const Point3 operator-(const Point3& p)
{
    return Point3(-p.x_, -p.y_, -p.z_);
}

inline bool operator==(const Point3& p1, const Point3& p2)
{
    return IsScalarAlmostEqual(p1.x_, p2.x_) && IsScalarAlmostEqual(p1.y_, p2.y_) && IsScalarAlmostEqual(p1.z_, p2.z_);
}

inline bool operator!=(const Point3& p1, const Point3& p2)
{
    return !IsScalarAlmostEqual(p1.x_, p2.x_) || !IsScalarAlmostEqual(p1.y_, p2.y_) ||
        !IsScalarAlmostEqual(p1.z_, p2.z_);
}
} // namespace Drawing
} // namespace Rosen
} // namespace OHOS
#endif
