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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_EDGE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_EDGE_H

#include "base/geometry/dimension.h"
#include "base/geometry/offset.h"
#include "base/geometry/size.h"
#include "base/utils/macros.h"
#include "base/utils/utils.h"
#include "core/pipeline/base/constants.h"

namespace OHOS::Ace {

// Types of padding and margin. Contains four directions: left, top, right and bottom.
class ACE_EXPORT Edge {
public:
    Edge() = default;
    explicit Edge(double value) : Edge(value, value, value, value) {};
    explicit Edge(const Dimension& value) : Edge(value, value, value, value) {};
    Edge(double left, double top, double right, double bottom, DimensionUnit unit = DimensionUnit::PX)
        : left_(Dimension(left, unit)), top_(Dimension(top, unit)), right_(Dimension(right, unit)),
          bottom_(Dimension(bottom, unit)) {};
    Edge(const Dimension& left, const Dimension& top, const Dimension& right, const Dimension& bottom)
        : left_(left), top_(top), right_(right), bottom_(bottom) {};
    virtual ~Edge() = default;

    static const Edge NONE;

    // Parse string to edge, support four formats(value separated by one space):
    // 1. 1px, edge has same value.
    // 2. 1px 2px, top and bottom are 1px, left and right are 2px.
    // 3. 1px 2px 3px, top is 1px, left and right are 2px, bottom is 3px.
    // 4. 1px 2px 3px 4px, top is 1px, right is 2px, bottom is 3px and left is 4px.
    static bool FromString(const std::string& value, Edge& edge);

    bool IsValid() const;
    Size GetLayoutSizeInPx(double dipScale) const;
    Offset GetOffsetInPx(double dipScale) const;
    double HorizontalInPx(double dipScale) const;
    double VerticalInPx(double dipScale) const;

    const Dimension& Left() const
    {
        return left_;
    }

    virtual void SetLeft(const Dimension& left)
    {
        left_ = left;
    }

    const Dimension& Top() const
    {
        return top_;
    }

    virtual void SetTop(const Dimension& top)
    {
        top_ = top;
    }

    const Dimension& Right() const
    {
        return right_;
    }

    virtual void SetRight(const Dimension& right)
    {
        right_ = right;
    }

    const Dimension& Bottom() const
    {
        return bottom_;
    }

    virtual void SetBottom(const Dimension& bottom)
    {
        bottom_ = bottom;
    }

    Edge operator+(const Edge& edge) const
    {
        return Edge(left_ + edge.left_, top_ + edge.top_, right_ + edge.right_, bottom_ + edge.bottom_);
    }

    Edge operator-(const Edge& edge) const
    {
        return Edge(left_ - edge.left_, top_ - edge.top_, right_ - edge.right_, bottom_ - edge.bottom_);
    }

    Edge operator*(const double factor) const
    {
        return Edge(left_ * factor, top_ * factor, right_ * factor, bottom_ * factor);
    }

    Edge operator/(const double factor) const
    {
        if (NearZero(factor)) {
            return NONE;
        }
        return Edge(left_ / factor, top_ / factor, right_ / factor, bottom_ / factor);
    }

    bool operator==(const Edge& edge) const
    {
        return (edge.left_ == left_) && (edge.top_ == top_) && (edge.right_ == right_) && (edge.bottom_ == bottom_);
    }

protected:
    Dimension left_;
    Dimension top_;
    Dimension right_;
    Dimension bottom_;
};

class EdgePx : public Edge {
public:
    EdgePx() = default;
    explicit EdgePx(double value) : EdgePx(value, value, value, value) {};
    EdgePx(double left, double top, double right, double bottom) : Edge(left, top, right, bottom) {};
    ~EdgePx() override = default;

    double LeftPx() const
    {
        return left_.Value();
    }

    double TopPx() const
    {
        return top_.Value();
    }

    double RightPx() const
    {
        return right_.Value();
    }

    double BottomPx() const
    {
        return bottom_.Value();
    }

    void SetLeft(const Dimension& left) override
    {
        if (left.Unit() != DimensionUnit::PX) {
            return;
        }
        left_ = left;
    }

    void SetTop(const Dimension& top) override
    {
        if (top.Unit() != DimensionUnit::PX) {
            return;
        }
        top_ = top;
    }

    void SetRight(const Dimension& right) override
    {
        if (right.Unit() != DimensionUnit::PX) {
            return;
        }
        right_ = right;
    }

    void SetBottom(const Dimension& bottom) override
    {
        if (bottom.Unit() != DimensionUnit::PX) {
            return;
        }
        bottom_ = bottom;
    }

    Size GetLayoutSize() const
    {
        return Size(left_.Value() + right_.Value(), top_.Value() + bottom_.Value());
    }

    Offset GetOffset() const
    {
        return Offset(left_.Value(), top_.Value());
    }

    EdgePx operator+(const EdgePx& edge) const
    {
        return EdgePx(LeftPx() + edge.LeftPx(), TopPx() + edge.TopPx(), RightPx() + edge.RightPx(),
            BottomPx() + edge.BottomPx());
    }
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_EDGE_H
