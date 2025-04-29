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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_ACCESSIBILITY_UTILS_ACCESSIBILITY_RECT_INFO_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_ACCESSIBILITY_UTILS_ACCESSIBILITY_RECT_INFO_UTILS_H

#include <map>

#include "base/geometry/ng/point_t.h"
#include "base/memory/ace_type.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
constexpr int32_t ZERO_ANGLE = 0;
constexpr int32_t QUARTER_ANGLE = 90;
constexpr int32_t HALF_ANGLE = 180;
constexpr int32_t THREE_QUARTER_ANGLE = 270;
constexpr int32_t FULL_ANGLE = 360;

class AccessibilityRealRectInfo {
public:
    AccessibilityRealRectInfo(
        NG::PointT<int32_t> realLeftTop,
        float width,
        float height,
        int32_t rotation,
        NG::VectorF scale)
    {
        realLeftTop_ = realLeftTop;
        componentLeftTop_ = realLeftTop;
        width_ = width;
        height_ = height;
        rotation_ = rotation;
        scale_ = scale;
    }

    ~AccessibilityRealRectInfo()  = default;

    int32_t GetWidth()
    {
        return width_;
    }

    int32_t GetHeight()
    {
        return height_;
    }

    int32_t GetRotation()
    {
        return rotation_;
    }

    NG::PointT<int32_t>& GetComponentLeftTop()
    {
        return componentLeftTop_;
    }

    NG::PointT<int32_t>& GetRealLeftTop()
    {
        return componentLeftTop_;
    }

    NG::VectorF& GetScale()
    {
        return scale_;
    }

    // calculate child's true rect by self's rotate and scale
    AccessibilityRealRectInfo GenerateRectInfoByRelativeConner(
        NG::PointT<int32_t> leftTop,
        NG::PointT<int32_t> rightBottom,
        NG::VectorF& scale)
    {
        UpdatePointWithScale(leftTop);
        UpdatePointWithScale(rightBottom);
        UpdatePointToReal(leftTop);
        UpdatePointToReal(rightBottom);

        auto degree = GetRotationByConner(leftTop, rightBottom);
        auto width = LessNotEqual(leftTop.GetX(), rightBottom.GetX())
            ? rightBottom.GetX() - leftTop.GetX()
            : leftTop.GetX() - rightBottom.GetX();
        auto height = LessNotEqual(leftTop.GetY(), rightBottom.GetY())
            ? rightBottom.GetY() - leftTop.GetY()
            : leftTop.GetY() - rightBottom.GetY();

        AccessibilityRealRectInfo rectInfo(leftTop, width, height, degree, scale);
    
        rectInfo.UpdateRealLeftTopWithRealWidthHeight();
        rectInfo.UpdateScale(scale_);
        return rectInfo;
    }

private:
    // calculate rotate degree by leftTop Point and rightBottom Point
    int32_t GetRotationByConner(NG::PointT<int32_t> leftTop, NG::PointT<int32_t> rightBottom)
    {
        if ((leftTop.GetX() < rightBottom.GetX()) && (leftTop.GetY() < rightBottom.GetY())) {
            return ZERO_ANGLE;
        }
        if ((rightBottom.GetX() < leftTop.GetX()) && (leftTop.GetY() < rightBottom.GetY())) {
            return QUARTER_ANGLE;
        }
        if ((rightBottom.GetX() < leftTop.GetX()) && (rightBottom.GetY() < leftTop.GetY())) {
            return HALF_ANGLE;
        }
        if ((leftTop.GetX() < rightBottom.GetX()) && (rightBottom.GetY() < leftTop.GetY())) {
            return THREE_QUARTER_ANGLE;
        }
        return ZERO_ANGLE;
    }

    void UpdatePointWithScale(NG::PointT<int32_t>& point)
    {
        point.SetX(point.GetX() * scale_.x);
        point.SetY(point.GetY() * scale_.y);
    }

    // apply rotation
    void UpdatePointToReal(NG::PointT<int32_t>& point)
    {
        auto transformedX = point.GetX();
        auto transformedY = point.GetY();
        switch (rotation_) {
            case QUARTER_ANGLE:
                transformedX = -point.GetY();
                transformedY = point.GetX();
                break;
            case HALF_ANGLE:
                transformedX = -point.GetX();
                transformedY = -point.GetY();
                break;
            case THREE_QUARTER_ANGLE:
                transformedX = point.GetY();
                transformedY = -point.GetX();
                break;
        }
        point.SetX(componentLeftTop_.GetX() + transformedX);
        point.SetY(componentLeftTop_.GetY() + transformedY);
    }

    void UpdateRealLeftTopWithRealWidthHeight()
    {
        auto x = componentLeftTop_.GetX();
        auto y = componentLeftTop_.GetY();
        switch (rotation_) {
            case QUARTER_ANGLE:
                x -= width_;
                break;
            case HALF_ANGLE:
                x -= width_;
                y -= height_;
                break;
            case THREE_QUARTER_ANGLE:
                y -= height_;
                break;
        }
        realLeftTop_.SetX(x);
        realLeftTop_.SetY(y);
    }

    void UpdateScale(NG::VectorF& parentScale)
    {
        scale_.x *= parentScale.x;
        scale_.y *= parentScale.y;
    }

    int32_t width_;
    int32_t height_;
    int32_t rotation_;
    NG::PointT<int32_t> componentLeftTop_;
    NG::PointT<int32_t> realLeftTop_;
    NG::VectorF scale_{1.0, 1.0};
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_ACCESSIBILITY_UTILS_ACCESSIBILITY_RECT_INFO_UTILS_H
