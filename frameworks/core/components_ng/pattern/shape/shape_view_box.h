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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_VIEWBOX_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_VIEWBOX_H

#include "base/geometry/dimension.h"

namespace OHOS::Ace::NG {

class ShapeViewBox final {
public:
    ShapeViewBox() = default;
    ShapeViewBox(const Dimension& x, const Dimension& y, const Dimension& width, const Dimension& height);
    ~ShapeViewBox() = default;

    const Dimension& Left() const
    {
        return x_;
    }

    const Dimension& Top() const
    {
        return y_;
    }

    const Dimension& Width() const
    {
        return width_;
    }

    const Dimension& Height() const
    {
        return height_;
    }

    void SetLeft(const Dimension& left)
    {
        x_ = left;
    }

    void SetTop(const Dimension& top)
    {
        y_ = top;
    }

    void SetWidth(const Dimension& width)
    {
        width_ = width;
    }

    void SetHeight(const Dimension& height)
    {
        height_ = height;
    }
    bool IsValid() const
    {
        return width_.Value() > 0.0 && height_.Value() > 0.0;
    }

    ShapeViewBox& operator=(const ShapeViewBox& shapeViewBox)
    {
        x_ = shapeViewBox.x_;
        y_ = shapeViewBox.y_;
        width_ = shapeViewBox.width_;
        height_ = shapeViewBox.height_;
        return *this;
    }

    bool operator==(const ShapeViewBox& shapeViewBox) const
    {
        return (x_ == shapeViewBox.x_) && (y_ == shapeViewBox.y_) && (width_ == shapeViewBox.width_) &&
               (height_ == shapeViewBox.height_);
    }

    bool operator!=(const ShapeViewBox& shapeViewBox) const
    {
        return (x_ != shapeViewBox.x_) || (y_ != shapeViewBox.y_) || (width_ != shapeViewBox.width_) ||
               (height_ != shapeViewBox.height_);
    }

private:
    Dimension x_ = Dimension(-1.0);
    Dimension y_ = Dimension(-1.0);
    Dimension width_ = Dimension(-1.0);
    Dimension height_ = Dimension(-1.0);
};

} // namespace OHOS::Ace::NG

#endif
