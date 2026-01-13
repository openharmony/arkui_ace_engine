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

#ifndef RECT_H
#define RECT_H

#include <cmath>
#include <string>

#include "scalar.h"

namespace OHOS {
namespace Rosen {
namespace Drawing {
class RectF;

typedef RectF Rect;

#define DRAWING_MAX_S32_FITS_IN_FLOAT    2147483520
#define DRAWING_MIN_S32_FITS_IN_FLOAT    (-DRAWING_MAX_S32_FITS_IN_FLOAT)

static inline int32_t DrawingFloatSaturate2Int(float x)
{
    x = x < DRAWING_MAX_S32_FITS_IN_FLOAT ? x : DRAWING_MAX_S32_FITS_IN_FLOAT;
    x = x > DRAWING_MIN_S32_FITS_IN_FLOAT ? x : DRAWING_MIN_S32_FITS_IN_FLOAT;
    return (int32_t)x;
}

class RectI {
public:
    inline RectI() noexcept;
    inline RectI(const RectI& r) noexcept;
    inline RectI(const int32_t l, const int32_t t, const int32_t r, const int32_t b) noexcept;

    ~RectI() {}

    inline bool IsValid() const;
    inline bool IsEmpty() const;

    inline int32_t GetLeft() const;
    inline int32_t GetTop() const;
    inline int32_t GetRight() const;
    inline int32_t GetBottom() const;

    inline int32_t GetWidth() const;
    inline int32_t GetHeight() const;

    inline void SetLeft(int32_t pos);
    inline void SetTop(int32_t pos);
    inline void SetRight(int32_t pos);
    inline void SetBottom(int32_t pos);
    inline void Offset(int32_t dx, int32_t dy);
    inline void MakeOutset(int32_t dx, int32_t dy);
    inline bool Contains(const RectI& other) const;
    inline bool Intersect(const RectI& other);
    inline bool Join(const RectI& other);

    inline std::string ToString() const;

    friend inline bool operator==(const RectI& r1, const RectI& r2);
    friend inline bool operator!=(const RectI& r1, const RectI& r2);

    inline void Dump(std::string& out) const;

    int32_t left_;
    int32_t top_;
    int32_t right_;
    int32_t bottom_;
};

inline RectI::RectI() noexcept : left_(0), top_(0), right_(0), bottom_(0) {}

inline RectI::RectI(const RectI& r) noexcept
{
    // Tell the compiler there is no alias and to select wider load/store instructions.
    int32_t left = r.GetLeft();
    int32_t top = r.GetTop();
    int32_t right = r.GetRight();
    int32_t bottom = r.GetBottom();
    left_ = left;
    top_ = top;
    right_ = right;
    bottom_ = bottom;
}

inline RectI::RectI(const int l, const int t, const int r, const int b) noexcept
    : left_(l), top_(t), right_(r), bottom_(b)
{}

inline bool RectI::IsValid() const
{
    return !IsEmpty();
}

inline bool RectI::IsEmpty() const
{
    int64_t w = (int64_t)right_ - (int64_t)left_;
    int64_t h = (int64_t)bottom_ - (int64_t)top_;
    if (w <= 0 || h <= 0) {
        return true;
    }
    // Return true if either exceeds int32_t
    int32_t int32test = (w | h) & 0xFFFFFFFF;
    return int32test < 0;
}

inline int32_t RectI::GetLeft() const
{
    return left_;
}

inline int32_t RectI::GetTop() const
{
    return top_;
}

inline int32_t RectI::GetRight() const
{
    return right_;
}

inline int32_t RectI::GetBottom() const
{
    return bottom_;
}

inline int32_t RectI::GetWidth() const
{
    return right_ - left_;
}

inline int32_t RectI::GetHeight() const
{
    return bottom_ - top_;
}

inline void RectI::SetLeft(int32_t pos)
{
    left_ = pos;
}

inline void RectI::SetTop(int32_t pos)
{
    top_ = pos;
}

inline void RectI::SetRight(int32_t pos)
{
    right_ = pos;
}

inline void RectI::SetBottom(int32_t pos)
{
    bottom_ = pos;
}

inline void RectI::Offset(int32_t dx, int32_t dy)
{
    left_ += dx;
    right_ += dx;
    top_ += dy;
    bottom_ += dy;
}

inline void RectI::MakeOutset(int32_t dx, int32_t dy)
{
    left_ -= dx;
    right_ += dx;
    top_ -= dy;
    bottom_ += dy;
}

inline bool RectI::Intersect(const RectI& other)
{
    RectI rectI(left_ > other.left_ ? left_ : other.left_, top_ > other.top_ ? top_ : other.top_,
        right_ < other.right_ ? right_ : other.right_, bottom_ < other.bottom_ ? bottom_ : other.bottom_);
    if (!rectI.IsValid()) {
        return false;
    }
    *this = rectI;
    return true;
}

inline bool RectI::Join(const RectI& other)
{
    if (!other.IsValid()) {
        return false;
    }
    if (!IsValid()) {
        *this = other;
    } else {
        *this = RectI(left_ < other.left_ ? left_ : other.left_, top_ < other.top_ ? top_ : other.top_,
            right_ > other.right_ ? right_ : other.right_, bottom_ > other.bottom_ ? bottom_ : other.bottom_);
    }
    return true;
}

inline bool RectI::Contains(const RectI& other) const
{
    return !other.IsEmpty() && !this->IsEmpty() &&
        left_ <= other.left_ && top_ <= other.top_ &&
        right_ >= other.right_ && bottom_ >= other.bottom_;
}

inline std::string RectI::ToString() const
{
    return std::string("(") + std::to_string(left_) + ", " + std::to_string(top_) + ", " +
        std::to_string(right_ - left_) + ", " + std::to_string(bottom_ - top_) + ")";
}

inline void RectI::Dump(std::string& out) const
{
    out += "[left:" + std::to_string(left_);
    out += " top:" + std::to_string(top_);
    out += " right:" + std::to_string(right_);
    out += " bottom:" + std::to_string(bottom_);
    out += "]";
}

inline bool operator==(const RectI& r1, const RectI& r2)
{
    return r1.left_ == r2.left_ && r1.right_ == r2.right_ && r1.top_ == r2.top_ && r1.bottom_ == r2.bottom_;
}

inline bool operator!=(const RectI& r1, const RectI& r2)
{
    return r1.left_ != r2.left_ || r1.right_ != r2.right_ || r1.top_ != r2.top_ || r1.bottom_ != r2.bottom_;
}

class RectF {
public:
    inline RectF() noexcept;
    inline RectF(const RectF& r) noexcept;
    inline RectF(const RectI& r) noexcept;
    inline RectF(const scalar l, const scalar t, const scalar r, const scalar b) noexcept;

    ~RectF() {}

    inline bool IsValid() const;
    inline bool IsEmpty() const;

    inline scalar GetLeft() const;
    inline scalar GetTop() const;
    inline scalar GetRight() const;
    inline scalar GetBottom() const;

    inline scalar GetWidth() const;
    inline scalar GetHeight() const;

    inline void SetLeft(scalar pos);
    inline void SetTop(scalar pos);
    inline void SetRight(scalar pos);
    inline void SetBottom(scalar pos);

    inline void Offset(scalar dx, scalar dy);
    inline void MakeOutset(scalar dx, scalar dy);
    inline void Round();
    inline RectI RoundOut();
    inline std::string ToString() const;

    /*
     * @brief        If RectF intersects other, sets RectF to intersection.
     * @param other  other rectangle.
     * @return       true if other and RectF have area in common.
     */
    inline bool Intersect(const RectF& other);

    /*
     * @brief        Determine whether this and other intersect.
     * @param other  other rectangle.
     * @return       true if other and RectF have area in common.
     */
    inline bool IsIntersect(const RectF& other) const;

    /*
     * @brief        If other is valid, sets RectF to the union of itself and other.
     * @param other  expansion RectF.
     * @return       true if other is valid.
     */
    inline bool Join(const RectF& other);

    /*
     * @brief Determine if (x, y) is within this rectangle.
     * @param x x-coordinate.
     * @param y y-coordinate.
     * @return true if rectangle contains (x, y), false otherwise.
     */
    inline bool Contains(scalar x, scalar y) const;

    /*
     * @brief Determine if other rectangle is inside this rectangle.
     * @param other other rectangle.
     * @return true if rectangle contains other rectangle, false otherwise.
     */
    inline bool Contains(const RectF& other) const;

    /*
     * @brief Swaps left and right if left is greater than right;
     *        and swaps top and bottom if top is greater than bottom.
     */
    inline void Sort();

    friend inline bool operator==(const RectF& r1, const RectF& r2);
    friend inline bool operator!=(const RectF& r1, const RectF& r2);

    inline void Dump(std::string& out) const;

    scalar left_;
    scalar top_;
    scalar right_;
    scalar bottom_;
};

inline RectF::RectF() noexcept : left_(0.0), top_(0.0), right_(0.0), bottom_(0.0) {}

inline RectF::RectF(const RectF& r) noexcept
{
    // Tell the compiler there is no alias and to select wider load/store instructions.
    scalar left = r.GetLeft();
    scalar top = r.GetTop();
    scalar right = r.GetRight();
    scalar bottom = r.GetBottom();
    left_ = left;
    top_ = top;
    right_ = right;
    bottom_ = bottom;
}

inline RectF::RectF(const RectI& r) noexcept
{
    // Tell the compiler there is no alias and to select wider load/store instructions.
    scalar left = r.GetLeft();
    scalar top = r.GetTop();
    scalar right = r.GetRight();
    scalar bottom = r.GetBottom();
    left_ = left;
    top_ = top;
    right_ = right;
    bottom_ = bottom;
}

inline RectF::RectF(const scalar l, const scalar t, const scalar r, const scalar b) noexcept
    : left_(l), top_(t), right_(r), bottom_(b)
{}

inline bool RectF::IsValid() const
{
    return left_ < right_ && top_ < bottom_;
}

inline bool RectF::IsEmpty() const
{
    return !(left_ < right_ && top_ < bottom_);
}

inline scalar RectF::GetLeft() const
{
    return left_;
}

inline scalar RectF::GetTop() const
{
    return top_;
}

inline scalar RectF::GetRight() const
{
    return right_;
}

inline scalar RectF::GetBottom() const
{
    return bottom_;
}

inline scalar RectF::GetWidth() const
{
    return right_ - left_;
}

inline scalar RectF::GetHeight() const
{
    return bottom_ - top_;
}

inline void RectF::SetLeft(scalar pos)
{
    left_ = pos;
}

inline void RectF::SetTop(scalar pos)
{
    top_ = pos;
}

inline void RectF::SetRight(scalar pos)
{
    right_ = pos;
}

inline void RectF::SetBottom(scalar pos)
{
    bottom_ = pos;
}

inline void RectF::Offset(scalar dx, scalar dy)
{
    left_ += dx;
    right_ += dx;
    top_ += dy;
    bottom_ += dy;
}

inline void RectF::MakeOutset(scalar dx, scalar dy)
{
    left_ -= dx;
    right_ += dx;
    top_ -= dy;
    bottom_ += dy;
}

inline void RectF::Round()
{
    left_ = DrawingFloatSaturate2Int(left_ + 0.5f);
    right_ = DrawingFloatSaturate2Int(right_ + 0.5f);
    top_ = DrawingFloatSaturate2Int(top_ + 0.5f);
    bottom_ = DrawingFloatSaturate2Int(bottom_ + 0.5f);
}

inline RectI RectF::RoundOut()
{
    int32_t left = DrawingFloatSaturate2Int(floorf(left_));
    int32_t right = DrawingFloatSaturate2Int(ceilf(right_));
    int32_t top = DrawingFloatSaturate2Int(floorf(top_));
    int32_t bottom = DrawingFloatSaturate2Int(ceilf(bottom_));
    return RectI(left, top, right, bottom);
}

inline bool RectF::Intersect(const RectF& other)
{
    RectF rectF(left_ > other.left_ ? left_ : other.left_, top_ > other.top_ ? top_ : other.top_,
                right_ < other.right_ ? right_ : other.right_, bottom_ < other.bottom_ ? bottom_ : other.bottom_);
    if (!rectF.IsValid()) {
        return false;
    }
    *this = rectF;
    return true;
}

inline bool RectF::IsIntersect(const RectF& other) const
{
    RectF rectF(left_ > other.left_ ? left_ : other.left_, top_ > other.top_ ? top_ : other.top_,
                right_ < other.right_ ? right_ : other.right_, bottom_ < other.bottom_ ? bottom_ : other.bottom_);
    return rectF.IsValid();
}

inline bool RectF::Join(const RectF& other)
{
    if (!other.IsValid()) {
        return false;
    }
    if (!IsValid()) {
        *this = other;
    } else {
        *this = RectF(left_ < other.left_ ? left_ : other.left_, top_ < other.top_ ? top_ : other.top_,
            right_ > other.right_ ? right_ : other.right_, bottom_ > other.bottom_ ? bottom_ : other.bottom_);
    }
    return true;
}

inline bool RectF::Contains(scalar x, scalar y) const
{
    return x >= left_ && x < right_ && y >= top_ && y < bottom_;
}

inline bool RectF::Contains(const RectF& other) const
{
    return !other.IsEmpty() && !this->IsEmpty() &&
        left_ <= other.left_ && top_ <= other.top_ &&
        right_ >= other.right_ && bottom_ >= other.bottom_;
}

inline void RectF::Sort()
{
    if (left_ > right_) {
        std::swap(left_, right_);
    }

    if (top_ > bottom_) {
        std::swap(top_, bottom_);
    }
}

inline std::string RectF::ToString() const
{
    return std::string("(") + std::to_string(left_) + ", " + std::to_string(top_) + ", " +
        std::to_string(right_ - left_) + ", " + std::to_string(bottom_ - top_) + ")";
}

inline void RectF::Dump(std::string& out) const
{
    out += "[left:" + std::to_string(left_);
    out += " top:" + std::to_string(top_);
    out += " right:" + std::to_string(right_);
    out += " bottom:" + std::to_string(bottom_);
    out += ']';
}

inline bool operator==(const RectF& r1, const RectF& r2)
{
    return IsScalarAlmostEqual(r1.left_, r2.left_) && IsScalarAlmostEqual(r1.right_, r2.right_) &&
        IsScalarAlmostEqual(r1.top_, r2.top_) && IsScalarAlmostEqual(r1.bottom_, r2.bottom_);
}

inline bool operator!=(const RectF& r1, const RectF& r2)
{
    return !IsScalarAlmostEqual(r1.left_, r2.left_) || !IsScalarAlmostEqual(r1.right_, r2.right_) ||
        !IsScalarAlmostEqual(r1.top_, r2.top_) || !IsScalarAlmostEqual(r1.bottom_, r2.bottom_);
}
} // namespace Drawing
} // namespace Rosen
} // namespace OHOS
#endif
