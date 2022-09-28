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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_GEOMETRY_NG_PointT_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_GEOMETRY_NG_PointT_H

#include <cmath>

#include "base/geometry/ng/offset_t.h"

namespace OHOS::Ace::NG {
template<typename T>
class PointT {
public:
    PointT() = default;
    ~PointT() = default;
    PointT(T x, T y) : x_(x), y_(y) {}

    T GetX() const
    {
        return x_;
    }

    T GetY() const
    {
        return y_;
    }

    void SetX(T x)
    {
        x_ = x;
    }

    void SetY(T y)
    {
        y_ = y;
    }

    void Rotate(const PointT& center, T angle)
    {
        T x = (x_ - center.GetX()) * std::cos(angle) - (y_ - center.GetY()) * std::sin(angle) + center.GetX();
        T y = (x_ - center.GetX()) * std::sin(angle) + (y_ - center.GetY()) * std::cos(angle) + center.GetY();
        x_ = x;
        y_ = y;
    }

    PointT operator-(const OffsetF& offset) const
    {
        return PointT(x_ - offset.GetX(), y_ - offset.GetY());
    }

    PointT operator+(const OffsetF& offset) const
    {
        return PointT(x_ + offset.GetX(), y_ + offset.GetY());
    }

    OffsetF operator-(const PointT& PointT) const
    {
        return OffsetF(x_ - PointT.x_, y_ - PointT.y_);
    }

    bool operator==(const PointT& PointT) const
    {
        return NearEqual(x_, PointT.x_) && NearEqual(y_, PointT.y_);
    }

    bool operator!=(const PointT& PointT) const
    {
        return !operator==(PointT);
    }

    std::string ToString() const
    {
        static const int32_t precision = 2;
        std::stringstream ss;
        ss << "Point (" << std::fixed << std::setprecision(precision) << x_ << ", " << y_ << ")";
        std::string output = ss.str();
        return output;
    }

private:
    T x_ { 0 };
    T y_ { 0 };
};

using PointF = PointT<float>;
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_GEOMETRY_NG_PointT_H
