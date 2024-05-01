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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_GEOMETRY_NG_OFFSET_T_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_GEOMETRY_NG_OFFSET_T_H

#include <cstdint>
#include <iomanip>
#include <sstream>
#include <string>

#include "base/geometry/axis.h"
#include "base/utils/utils.h"

namespace OHOS::Ace::NG {
template<typename T>
class OffsetT {
public:
    OffsetT() = default;
    ~OffsetT() = default;
    OffsetT(T x, T y) : x_(x), y_(y) {}

    OffsetT(T crossOffset, T mainOffset, Axis axis)
    {
        if (axis == Axis::HORIZONTAL) {
            x_ = mainOffset;
            y_ = crossOffset;
        } else { // Axis::VERTICAL and others
            x_ = crossOffset;
            y_ = mainOffset;
        }
    }

    void Reset()
    {
        x_ = 0;
        y_ = 0;
    }

    T GetX() const
    {
        return x_;
    }

    T GetY() const
    {
        return y_;
    }

    T GetMainOffset(Axis axis) const
    {
        return axis == Axis::HORIZONTAL ? x_ : y_;
    }

    T GetCrossOffset(Axis axis) const
    {
        return axis == Axis::HORIZONTAL ? y_ : x_;
    }

    T GetDistance(const OffsetT& offset) const
    {
        T dx = x_ - offset.x_;
        T dy = y_ - offset.y_;
        return std::sqrt(dx * dx + dy * dy);
    }

    void SetX(T x)
    {
        x_ = x;
    }

    void SetY(T y)
    {
        y_ = y;
    }

    void AddX(T x)
    {
        x_ += x;
    }

    void AddY(T y)
    {
        y_ += y;
    }

    OffsetT operator+(const OffsetT& offset) const
    {
        return OffsetT(x_ + offset.x_, y_ + offset.y_);
    }

    OffsetT operator-(const OffsetT& offset) const
    {
        return OffsetT(x_ - offset.x_, y_ - offset.y_);
    }

    OffsetT operator*(double value) const
    {
        return OffsetT(x_ * value, y_ * value);
    }

    OffsetT operator/(double value) const
    {
        if (NearZero(value)) {
            return {};
        }
        return OffsetT(x_ / value, y_ / value);
    }

    OffsetT& operator+=(const OffsetT& offset)
    {
        x_ += offset.x_;
        y_ += offset.y_;
        return *this;
    }

    OffsetT& operator-=(const OffsetT& offset)
    {
        x_ -= offset.x_;
        y_ -= offset.y_;
        return *this;
    }

    bool operator==(const OffsetT& offset) const
    {
        return NearEqual(x_, offset.x_) && NearEqual(y_, offset.y_);
    }

    bool operator!=(const OffsetT& offset) const
    {
        return !operator==(offset);
    }

    bool NonNegative() const
    {
        return GreatOrEqual(x_, 0) && GreatOrEqual(y_, 0);
    }

    bool IsNegative() const
    {
        return LessNotEqual(x_, 0) && LessNotEqual(y_, 0);
    }

    bool NonOffset() const
    {
        return NearZero(x_) && NearZero(y_);
    }

    std::string ToString() const
    {
        static const int32_t precision = 2;
        std::stringstream ss;
        ss << "Offset (" << std::fixed << std::setprecision(precision) << x_ << ", " << y_ << ")";
        std::string output = ss.str();
        return output;
    }

private:
    T x_ { 0 };
    T y_ { 0 };
};

using OffsetF = OffsetT<float>;
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_GEOMETRY_NG_OFFSET_T_H
