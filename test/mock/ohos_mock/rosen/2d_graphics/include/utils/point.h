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

#ifndef POINT_H
#define POINT_H

#include <cfloat>
#include <string>
#include "scalar.h"

namespace OHOS {
namespace Rosen {
namespace Drawing {
class PointF;

typedef PointF Point;

class PointF {
public:
    inline PointF() noexcept;
    inline PointF(const PointF& p) noexcept;
    inline PointF(scalar x, scalar y) noexcept;

    inline ~PointF() {}

    inline scalar GetX() const;
    inline scalar GetY() const;

    inline void SetX(scalar x);
    inline void SetY(scalar y);
    inline void Set(scalar x, scalar y);

    inline bool IsZero() const;

    inline void Offset(scalar x, scalar y);

    inline PointF& operator+=(const PointF& p);
    inline PointF& operator-=(const PointF& p);
    inline PointF& operator*=(scalar scale);
    inline PointF& operator/=(scalar divisor);

    friend inline const PointF operator+(const PointF& p1, const PointF& p2);
    friend inline const PointF operator-(const PointF& p1, const PointF& p2);
    friend inline const PointF operator*(scalar scale, const PointF& p);
    friend inline const PointF operator*(const PointF& p, scalar scale);
    friend inline const PointF operator/(const PointF& p, scalar divisor);
    friend inline const PointF operator+(const PointF& p);
    friend inline const PointF operator-(const PointF& p);
    friend inline bool operator==(const PointF& p1, const PointF& p2);
    friend inline bool operator!=(const PointF& p1, const PointF& p2);

    inline void Dump(std::string& out) const;

private:
    scalar x_;
    scalar y_;
};

inline PointF::PointF() noexcept : x_(0.0), y_(0.0) {}

inline PointF::PointF(const PointF& p) noexcept
{
    // Tell the compiler there is no alias and to select wider load/store instructions.
    scalar x = p.GetX();
    scalar y = p.GetY();
    x_ = x;
    y_ = y;
}

inline PointF::PointF(scalar x, scalar y) noexcept : x_(x), y_(y) {}

inline scalar PointF::GetX() const
{
    return x_;
}

inline scalar PointF::GetY() const
{
    return y_;
}

inline void PointF::SetX(scalar x)
{
    x_ = x;
}

inline void PointF::SetY(scalar y)
{
    y_ = y;
}

inline void PointF::Set(scalar x, scalar y)
{
    x_ = x;
    y_ = y;
}

inline bool PointF::IsZero() const
{
    return (0 == x_) && (0 == y_);
}

inline void PointF::Offset(scalar x, scalar y)
{
    x_ += x;
    y_ += y;
}

inline PointF& PointF::operator+=(const PointF& p)
{
    x_ += p.x_;
    y_ += p.y_;
    return *this;
}

inline PointF& PointF::operator-=(const PointF& p)
{
    x_ -= p.x_;
    y_ -= p.y_;
    return *this;
}

inline PointF& PointF::operator*=(scalar scale)
{
    x_ *= scale;
    y_ *= scale;
    return *this;
}

inline PointF& PointF::operator/=(scalar divisor)
{
    if (fabs(divisor) < FLT_EPSILON) {
        return *this;
    }
    x_ /= divisor;
    y_ /= divisor;
    return *this;
}

inline void PointF::Dump(std::string& out) const
{
    out += "[";
    out += "x:" + std::to_string(x_);
    out += " y:" + std::to_string(y_);
    out += "]";
}

inline const PointF operator+(const PointF& p1, const PointF& p2)
{
    return PointF(p1.x_ + p2.x_, p1.y_ + p2.y_);
}

inline const PointF operator-(const PointF& p1, const PointF& p2)
{
    return PointF(p1.x_ - p2.x_, p1.y_ - p2.y_);
}

inline const PointF operator*(scalar scale, const PointF& p)
{
    return PointF(scale * p.x_, scale * p.y_);
}

inline const PointF operator*(const PointF& p, scalar scale)
{
    return PointF(p.x_ * scale, p.y_ * scale);
}

inline const PointF operator/(const PointF& p, scalar divisor)
{
    if (fabs(divisor) < FLT_EPSILON) {
        return PointF(p.x_, p.y_);
    }
    return PointF(p.x_ / divisor, p.y_ / divisor);
}

inline const PointF operator+(const PointF& p)
{
    return PointF(p.x_, p.y_);
}

inline const PointF operator-(const PointF& p)
{
    return PointF(-p.x_, -p.y_);
}

inline bool operator==(const PointF& p1, const PointF& p2)
{
    return IsScalarAlmostEqual(p1.x_, p2.x_) && IsScalarAlmostEqual(p1.y_, p2.y_);
}

inline bool operator!=(const PointF& p1, const PointF& p2)
{
    return !IsScalarAlmostEqual(p1.x_, p2.x_) || !IsScalarAlmostEqual(p1.y_, p2.y_);
}

class PointI {
public:
    inline PointI() noexcept;
    inline PointI(const PointI& p) noexcept;
    inline PointI(int x, int y) noexcept;

    inline ~PointI() {}

    inline int GetX() const;
    inline int GetY() const;

    inline void SetX(int x);
    inline void SetY(int y);
    inline void Set(int x, int y);

    inline PointI& operator+=(const PointI& p);
    inline PointI& operator-=(const PointI& p);
    inline PointI& operator*=(scalar scale);
    inline PointI& operator/=(scalar divisor);

    friend inline const PointI operator+(const PointI& p1, const PointI& p2);
    friend inline const PointI operator-(const PointI& p1, const PointI& p2);
    friend inline const PointI operator*(scalar scale, const PointI& p);
    friend inline const PointI operator*(const PointI& p, scalar scale);
    friend inline const PointI operator/(const PointI& p, scalar divisor);
    friend inline const PointI operator+(const PointI& p);
    friend inline const PointI operator-(const PointI& p);
    friend inline bool operator==(const PointI& p1, const PointI& p2);
    friend inline bool operator!=(const PointI& p1, const PointI& p2);

private:
    int x_;
    int y_;
};

inline PointI::PointI() noexcept : x_(0), y_(0) {}

inline PointI::PointI(const PointI& p) noexcept : x_(p.GetX()), y_(p.GetY()) {}

inline PointI::PointI(int x, int y) noexcept : x_(x), y_(y) {}

inline int PointI::GetX() const
{
    return x_;
}

inline int PointI::GetY() const
{
    return y_;
}

inline void PointI::SetX(int x)
{
    x_ = x;
}

inline void PointI::SetY(int y)
{
    y_ = y;
}

inline void PointI::Set(int x, int y)
{
    x_ = x;
    y_ = y;
}

inline PointI& PointI::operator+=(const PointI& p)
{
    x_ += p.x_;
    y_ += p.y_;
    return *this;
}

inline PointI& PointI::operator-=(const PointI& p)
{
    x_ -= p.x_;
    y_ -= p.y_;
    return *this;
}

inline PointI& PointI::operator*=(scalar scale)
{
    x_ = static_cast<int64_t>(x_ * scale);
    y_ = static_cast<int64_t>(y_ * scale);
    return *this;
}

inline PointI& PointI::operator/=(scalar divisor)
{
    if (divisor == 0) {
        return *this;
    }
    x_ = static_cast<int>(x_ / divisor);
    y_ = static_cast<int>(y_ / divisor);
    return *this;
}

inline const PointI operator+(const PointI& p1, const PointI& p2)
{
    return PointI(p1.x_ + p2.x_, p1.y_ + p2.y_);
}

inline const PointI operator-(const PointI& p1, const PointI& p2)
{
    return PointI(p1.x_ - p2.x_, p1.y_ - p2.y_);
}

inline const PointI operator*(scalar scale, const PointI& p)
{
    return PointI(static_cast<int64_t>(scale * p.x_), static_cast<int64_t>(scale * p.y_));
}

inline const PointI operator*(const PointI& p, scalar scale)
{
    return PointI(static_cast<int64_t>(p.x_ * scale), static_cast<int64_t>(p.y_ * scale));
}

inline const PointI operator/(const PointI& p, scalar divisor)
{
    if (divisor == 0) {
        return PointI(p.x_, p.y_);
    }
    return PointI(static_cast<int>(p.x_ / divisor), static_cast<int>(p.y_ / divisor));
}

inline const PointI operator+(const PointI& p)
{
    return PointI(p.x_, p.y_);
}

inline const PointI operator-(const PointI& p)
{
    return PointI(-p.x_, -p.y_);
}

inline bool operator==(const PointI& p1, const PointI& p2)
{
    return p1.x_ == p2.x_ && p1.y_ == p2.y_;
}

inline bool operator!=(const PointI& p1, const PointI& p2)
{
    return p1.x_ != p2.x_ || p1.y_ != p2.y_;
}
} // namespace Drawing
} // namespace Rosen
} // namespace OHOS
#endif
