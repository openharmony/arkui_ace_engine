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

#ifndef ROUND_RECT_H
#define ROUND_RECT_H

#include <vector>

#include "point.h"
#include "rect.h"

namespace OHOS {
namespace Rosen {
namespace Drawing {
class RoundRect {
public:
    enum CornerPos : int {
        TOP_LEFT_POS = 0,
        TOP_RIGHT_POS,
        BOTTOM_RIGHT_POS,
        BOTTOM_LEFT_POS,
        CORNER_NUMBER
    };

    inline RoundRect() noexcept;
    inline ~RoundRect() {}

    inline RoundRect(const RoundRect& roundRect) noexcept;
    inline RoundRect(const Rect& r, scalar xRad, scalar yRad) noexcept;
    inline RoundRect(const Rect& r, const std::vector<Point>& radiusXY) noexcept;


    inline void SetRect(const Rect& rect);
    inline const Rect& GetRect() const;

    /**
     * @brief Translates RoundRect by (dx, dy).
     * @param dx  offset added to rect left and rect right
     * @param dy  offset added to rect top and rect bottom
     */
    inline void Offset(scalar dx, scalar dy);
    inline bool IsSimpleRoundRect() const;
    inline scalar GetSimpleX() const;
    inline scalar GetSimpleY() const;
    bool ClampToZero();

    /**
     * @brief Returns true if the radii had to be scaled to fit rect.
     */
    bool ScaleRadii();

    void Dump(std::string& out) const;

private:
    Rect rect_;
    // Four radii are stored: top-left/top-right/bottom-left/bottom-right corner radii.
    Point radiusXY_[CORNER_NUMBER] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}};
    bool isSimple_ = false;
};

inline RoundRect::RoundRect() noexcept : rect_(), isSimple_(true) {}

inline RoundRect::RoundRect(const RoundRect& roundRect) noexcept : RoundRect()
{
    rect_ = roundRect.rect_;
    for (int i = 0; i < CORNER_NUMBER; ++i) {
        radiusXY_[i] = roundRect.radiusXY_[i];
    }
    isSimple_ = roundRect.isSimple_;
}

inline RoundRect::RoundRect(const Rect& r, scalar xRad, scalar yRad) noexcept : RoundRect()
{
    rect_ = r;
    for (int i = 0; i < CORNER_NUMBER; ++i) {
        radiusXY_[i].SetX(xRad);
        radiusXY_[i].SetY(yRad);
    }
    isSimple_ = true;
}

inline RoundRect::RoundRect(const Rect& r, const std::vector<Point>& radiusXY) noexcept : RoundRect()
{
    rect_ = r;
    for (int i = 0; i < CORNER_NUMBER && i < static_cast<int>(radiusXY.size()); ++i) {
        radiusXY_[i] = radiusXY[i];
    }
    isSimple_ = false;
    ScaleRadii();
}

inline void RoundRect::SetRect(const Rect& rect)
{
    rect_ = rect;
}

inline const Rect& RoundRect::GetRect() const
{
    return rect_;
}

inline void RoundRect::Offset(scalar dx, scalar dy)
{
    rect_.Offset(dx, dy);
}

inline bool RoundRect::IsSimpleRoundRect() const
{
    return isSimple_;
}

inline scalar RoundRect::GetSimpleX() const
{
    return radiusXY_[RoundRect::TOP_LEFT_POS].GetX();
}

inline scalar RoundRect::GetSimpleY() const
{
    return radiusXY_[RoundRect::TOP_LEFT_POS].GetY();
}
} // namespace Drawing
} // namespace Rosen
} // namespace OHOS
#endif
