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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_BORDER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_BORDER_H

#include "base/geometry/offset.h"
#include "base/geometry/size.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/border_edge.h"
#include "core/components/common/properties/radius.h"

namespace OHOS::Ace {

// Border of a box, contains four borderEdges: left, top, right, bottom.
// And four radius: topLeftRadius, topRightRadius, bottomLeftRadius, bottomRightRadius.
// Each borderEdge is a BorderEdge object and each radius is a Radius object.
class ACE_EXPORT Border final {
public:
    Border() = default;
    explicit Border(const BorderEdge& edge) : Border(edge, edge, edge, edge) {};
    Border(const BorderEdge& edge, const Radius& radius) : Border(edge, edge, edge, edge)
    {
        SetBorderRadius(radius);
    }
    Border(const BorderEdge& left, const BorderEdge& top, const BorderEdge& right, const BorderEdge& bottom);
    ~Border() = default;

    bool IsAllEqual() const;
    bool HasValue() const;
    bool HasRadius() const;
    Offset GetOffset(double dipScale) const;
    double HorizontalWidth(double dipScale) const;
    double VerticalWidth(double dipScale) const;
    Size GetLayoutSize(double dipScale) const;
    BorderEdge GetValidEdge() const;

    void SetBorderRadius(const Radius& radius)
    {
        topLeftRadius_ = radius;
        topRightRadius_ = radius;
        bottomLeftRadius_ = radius;
        bottomRightRadius_ = radius;
    }

    void SetBorderEdge(const BorderEdge& borderEdge)
    {
        top_ = borderEdge;
        left_ = borderEdge;
        right_ = borderEdge;
        bottom_ = borderEdge;
    }

    void SetTopLeftRadius(const Radius& topLeftRadius)
    {
        topLeftRadius_ = topLeftRadius;
    }

    void SetTopRightRadius(const Radius& topRightRadius)
    {
        topRightRadius_ = topRightRadius;
    }

    void SetBottomLeftRadius(const Radius& bottomLeftRadius)
    {
        bottomLeftRadius_ = bottomLeftRadius;
    }

    void SetBottomRightRadius(const Radius& bottomRightRadius)
    {
        bottomRightRadius_ = bottomRightRadius;
    }

    const Radius& TopLeftRadius() const
    {
        return topLeftRadius_;
    }

    const Radius& TopRightRadius() const
    {
        return topRightRadius_;
    }

    const Radius& BottomLeftRadius() const
    {
        return bottomLeftRadius_;
    }

    const Radius& BottomRightRadius() const
    {
        return bottomRightRadius_;
    }

    const BorderEdge& Left() const
    {
        return left_;
    }

    const BorderEdge& Top() const
    {
        return top_;
    }

    const BorderEdge& Right() const
    {
        return right_;
    }

    const BorderEdge& Bottom() const
    {
        return bottom_;
    }

    bool operator==(const Border& border) const
    {
        return (border.Left() == left_) && (border.Top() == top_) && (border.Right() == right_) &&
               (border.Bottom() == bottom_);
    }

    void SetLeftEdge(const BorderEdge& edge)
    {
        left_ = edge;
    }

    void SetTopEdge(const BorderEdge& edge)
    {
        top_ = edge;
    }

    void SetRightEdge(const BorderEdge& edge)
    {
        right_ = edge;
    }

    void SetBottomEdge(const BorderEdge& edge)
    {
        bottom_ = edge;
    }

private:
    BorderEdge left_;
    BorderEdge top_;
    BorderEdge right_;
    BorderEdge bottom_;
    Radius topLeftRadius_;
    Radius topRightRadius_;
    Radius bottomLeftRadius_;
    Radius bottomRightRadius_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_BORDER_H
