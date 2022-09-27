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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_GEOMETRY_NG_RECT_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_GEOMETRY_NG_RECT_H

#include <algorithm>
#include <array>

#include "base/geometry/axis.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/point_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/utils/utils.h"

namespace OHOS::Ace::NG {
template<typename T>
class RectT {
public:
    RectT() = default;
    ~RectT() = default;

    RectT(T x, T y, T width, T height)
    {
        SetRect(x, y, width, height);
    }

    RectT(const OffsetF& offset, const SizeF& size)
    {
        SetOffset(offset);
        SetSize(size);
    }

    RectT(const OffsetF& topLeftPoint, const OffsetF& bottomRightPoint)
    {
        SetOffset(topLeftPoint);
        OffsetF sizeOffset = bottomRightPoint - topLeftPoint;
        SizeF size(sizeOffset.GetX(), sizeOffset.GetY());
        SetSize(size);
    }

    void Reset()
    {
        x_ = 0;
        y_ = 0;
        width_ = 0;
        height_ = 0;
    }

    void SetRect(T x, T y, T width, T height)
    {
        x_ = x;
        y_ = y;
        width_ = width;
        height_ = height;
    }

    void SetRect(const OffsetT<T>& offset, const SizeT<T>& size)
    {
        SetOffset(offset);
        SetSize(size);
    }

    void ApplyScale(T scale)
    {
        x_ *= scale;
        y_ *= scale;
        width_ *= scale;
        height_ *= scale;
    }

    void ApplyScaleAndRound(T scale)
    {
        x_ = round(x_ * scale);
        y_ = round(y_ * scale);
        width_ = round(width_ * scale);
        height_ = round(height_ * scale);
    }

    T Left() const
    {
        return GreatNotEqual(width_, 0) ? x_ : x_ + width_;
    }

    T Top() const
    {
        return GreatNotEqual(height_, 0) ? y_ : y_ + height_;
    }

    T Right() const
    {
        return GreatNotEqual(width_, 0) ? x_ + width_ : x_;
    }

    T Bottom() const
    {
        return GreatNotEqual(height_, 0) ? y_ + height_ : y_;
    }

    T GetX() const
    {
        return x_;
    }

    T GetY() const
    {
        return y_;
    }

    T Width() const
    {
        return width_;
    }

    T Height() const
    {
        return height_;
    }

    T MainSize(Axis axis) const
    {
        return axis == Axis::HORIZONTAL ? width_ : height_;
    }

    void SetSize(const SizeT<T>& size)
    {
        width_ = size.Width();
        height_ = size.Height();
    }

    SizeT<T> GetSize() const
    {
        return SizeT<T>(width_, height_);
    }

    void SetOffset(const OffsetT<T>& offset)
    {
        x_ = offset.GetX();
        y_ = offset.GetY();
    }

    OffsetT<T> GetOffset() const
    {
        return OffsetT<T>(x_, y_);
    }

    void SetLeft(T left)
    {
        x_ = left;
    }

    void SetTop(T top)
    {
        y_ = top;
    }

    void SetWidth(T width)
    {
        width_ = width;
    }

    void SetHeight(T height)
    {
        height_ = height;
    }

    bool IsInRegion(const PointT<T>& point) const
    {
        return GreatOrEqual(point.GetX(), x_) && LessOrEqual(point.GetX(), x_ + width_) &&
               GreatOrEqual(point.GetY(), y_) && LessOrEqual(point.GetY(), y_ + height_);
    }

    bool IsWrappedBy(const RectT& other) const
    {
        return GreatOrEqual(Left(), other.Left()) && LessOrEqual(Right(), other.Right()) &&
               GreatOrEqual(Top(), other.Top()) && LessOrEqual(Bottom(), other.Bottom());
    }

    bool IsValid() const
    {
        return NonNegative(width_) && NonNegative(height_);
    }

    bool IsEmpty() const
    {
        return NonPositive(width_) || NonPositive(height_);
    }

    RectT Constrain(const RectT& other)
    {
        T right = Right();
        T bottom = Bottom();
        T left = std::clamp(x_, other.Left(), other.Right());
        T top = std::clamp(y_, other.Top(), other.Bottom());
        right = std::clamp(right, other.Left(), other.Right()) - left;
        bottom = std::clamp(bottom, other.Top(), other.Bottom()) - top;
        return RectT(left, top, right, bottom);
    }

    RectT& operator+=(const OffsetT<T>& offset)
    {
        x_ += offset.GetX();
        y_ += offset.GetY();
        return *this;
    }

    RectT& operator-=(const OffsetT<T>& offset)
    {
        x_ -= offset.GetX();
        y_ -= offset.GetY();
        return *this;
    }

    RectT& operator+=(const SizeT<T>& size)
    {
        width_ += size.Width();
        height_ += size.Height();
        return *this;
    }

    RectT& operator-=(const SizeT<T>& size)
    {
        width_ -= size.Width();
        height_ -= size.Height();
        return *this;
    }

    RectT operator+(const OffsetT<T>& offset) const
    {
        return RectT(x_ + offset.GetX(), y_ + offset.GetY(), width_, height_);
    }

    RectT operator-(const OffsetT<T>& offset) const
    {
        return RectT(x_ - offset.GetX(), y_ - offset.GetY(), width_, height_);
    }

    RectT operator+(const SizeT<T>& size) const
    {
        return RectT(x_, y_, width_ + size.Width(), height_ + size.Height());
    }

    RectT operator-(const SizeT<T>& size) const
    {
        return RectT(x_, y_, width_ - size.Width(), height_ - size.Height());
    }

    RectT operator*(T scale) const
    {
        return RectT(x_ * scale, y_ * scale, width_ * scale, height_ * scale);
    }

    bool operator==(const RectT& RectT) const
    {
        return (GetOffset() == RectT.GetOffset()) && (GetSize() == RectT.GetSize());
    }

    bool operator!=(const RectT& RectT) const
    {
        return !operator==(RectT);
    }

    bool IsIntersectWith(const RectT& other) const
    {
        return !(LessNotEqual(other.Right(), Left()) || GreatNotEqual(other.Left(), Right()) ||
                 LessNotEqual(other.Bottom(), Top()) || GreatNotEqual(other.Top(), Bottom()));
    }

    RectT IntersectRectT(const RectT& other) const
    {
        T left = std::max(Left(), other.Left());
        T right = std::min(Right(), other.Right());
        T top = std::max(Top(), other.Top());
        T bottom = std::min(Bottom(), other.Bottom());
        return RectT(left, top, right - left, bottom - top);
    }

    RectT CombineRectT(const RectT& other) const
    {
        T left = std::min(Left(), other.Left());
        T right = std::max(Right(), other.Right());
        T top = std::min(Top(), other.Top());
        T bottom = std::max(Bottom(), other.Bottom());
        return RectT(left, top, right - left, bottom - top);
    }

    OffsetT<T> MagneticAttractedBy(const RectT& magnet)
    {
        OffsetT<T> offset { 0.0, 0.0 };
        if (IsWrappedBy(magnet)) {
            return offset;
        }

        if (LessNotEqual(Left(), magnet.Left())) {
            offset.SetX(std::max(0.0, std::min(magnet.Left() - Left(), magnet.Right() - Right())));
        } else if (GreatNotEqual(Right(), magnet.Right())) {
            offset.SetX(std::min(0.0, std::max(magnet.Left() - Left(), magnet.Right() - Right())));
        } else {
            // No need to offset.
        }

        if (LessNotEqual(Top(), magnet.Top())) {
            offset.SetY(std::max(0.0, std::min(magnet.Top() - Top(), magnet.Bottom() - Bottom())));
        } else if (GreatNotEqual(Bottom(), magnet.Bottom())) {
            offset.SetY(std::min(0.0, std::max(magnet.Top() - Top(), magnet.Bottom() - Bottom())));
        } else {
            // No need to offset.
        }

        *this += offset;

        return offset;
    }

    std::string ToString() const
    {
        static const int32_t precision = 2;
        std::stringstream ss;
        ss << "RectT (" << std::fixed << std::setprecision(precision) << x_ << ", " << y_ << ") - [";
        ss << width_;
        ss << " x ";
        ss << height_;
        ss << "]";
        std::string output = ss.str();
        return output;
    }

    OffsetT<T> Center() const
    {
        return OffsetT<T>(width_ / 2.0 + x_, height_ / 2.0 + y_);
    }

private:
    T x_ = 0;
    T y_ = 0;
    T width_ = 0;
    T height_ = 0;

    friend class GeometryProperty;
};

using RectF = RectT<float>;
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_GEOMETRY_NG_RECT_H
