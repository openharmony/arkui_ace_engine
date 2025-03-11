/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/swiper_indicator/indicator_common/arc_swiper_indicator_pattern.h"

namespace OHOS::Ace::NG {
namespace {
constexpr double QUARTER_CIRCLE_ANGLE = 90.0;
constexpr double HALF_CIRCLE_ANGLE = 180.0;
constexpr double THREE_QUARTER_CIRCLE_ANGLE = 270.0;
constexpr double FULL_CIRCLE_ANGLE = 360.0;
constexpr float ITEM_PADDING = 5.0f;
constexpr int32_t OFFSET_ANGLE = 5;
constexpr float ACTIVE_ITEM_ANGLE = 4.0f;
constexpr float ADD_HOT_REG_ANGLE = 8.0f;
constexpr Dimension CIRCLE_DIAMETER_OFFSET = 16.0_vp;
constexpr float DIVIDE_NUM = 0.5f; // The number 0.5 represents equal division
} // namespace
bool ArcSwiperIndicatorPattern::SetArcIndicatorHotRegion(
    const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (isAccessibilityFocusd_) {
        return true;
    }
    if (config.skipMeasure && config.skipLayout) {
        return false;
    }

    const auto& indicatorGeometryNode = dirty->GetGeometryNode();
    CHECK_NULL_RETURN(indicatorGeometryNode, false);
    const auto& frameRect = indicatorGeometryNode->GetFrameRect();
    if (NonPositive(frameRect.Width()) || NonPositive(frameRect.Height())) {
        return false;
    }
    return CalculateArcIndicatorHotRegion(frameRect, indicatorGeometryNode->GetContentOffset());
}

void ArcSwiperIndicatorPattern::InitAccessibilityFocusEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto accessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetOnAccessibilityFocusCallback([weak = WeakClaim(this)](bool focus) {
        auto indicator = weak.Upgrade();
        CHECK_NULL_VOID(indicator);
        indicator->SetAccessibilityFocusd(focus);
    });
}

bool ArcSwiperIndicatorPattern::CalculateArcIndicatorHotRegion(const RectF& frameRect, const OffsetF& contentOffset)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto gestureHub = host->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(gestureHub, false);
    auto swiperNode = DynamicCast<FrameNode>(host->GetParent());
    CHECK_NULL_RETURN(swiperNode, false);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_RETURN(swiperPattern, false);
    int32_t itemCount = swiperPattern->RealTotalCount();
    if (itemCount <= 0) {
        return false;
    }
    auto allPointArcAngle = (itemCount - 1) * ITEM_PADDING + ACTIVE_ITEM_ANGLE + ADD_HOT_REG_ANGLE;
    auto centerX = frameRect.Width() * DIVIDE_NUM + contentOffset.GetX();
    auto centerY = frameRect.Height() * DIVIDE_NUM + contentOffset.GetY();
    auto minEdgeLength = LessNotEqual(frameRect.Width(), frameRect.Height()) ? frameRect.Width() : frameRect.Height();
    if (LessOrEqual(minEdgeLength, CIRCLE_DIAMETER_OFFSET.ConvertToPx())) {
        return false;
    }
    auto radius = (minEdgeLength - CIRCLE_DIAMETER_OFFSET.ConvertToPx()) * DIVIDE_NUM;
    const auto& parameter = swiperPattern->GetSwiperArcDotParameters();
    CHECK_NULL_RETURN(parameter, false);
    SwiperArcDirection arcDirection = parameter->arcDirection.value_or(SwiperArcDirection::SIX_CLOCK_DIRECTION);
    std::vector<DimensionRect> responseRegion;
    int32_t allAngleCount = static_cast<int32_t>(allPointArcAngle);
    for (int32_t i = 0; i <= allAngleCount; i++) {
        double angle = 0.0;
        if (arcDirection == SwiperArcDirection::THREE_CLOCK_DIRECTION) {
            angle = - allPointArcAngle * DIVIDE_NUM + i;
        } else if (arcDirection == SwiperArcDirection::NINE_CLOCK_DIRECTION) {
            angle = HALF_CIRCLE_ANGLE - allPointArcAngle * DIVIDE_NUM + i;
        } else {
            angle = QUARTER_CIRCLE_ANGLE - allPointArcAngle * DIVIDE_NUM + i;
        }
        if (LessNotEqual(angle, 0.0)) {
            angle = FULL_CIRCLE_ANGLE + angle;
        }

        OffsetF angleOffset = CalculateAngleOffset(centerX, centerY, radius, angle);
        Dimension width;
        Dimension height;
        OffsetF hotRegionOffset = CalculateRectLayout(angle, radius, angleOffset, width, height);

        DimensionRect responseRect(width, height, DimensionOffset(hotRegionOffset));
        responseRegion.emplace_back(responseRect);
    }

    gestureHub->SetResponseRegion(responseRegion);
    return true;
}

PointF ArcSwiperIndicatorPattern::GetCenterPointF()
{
    auto center = PointF(0.0, 0.0);
    auto swiperNode = GetSwiperNode();
    CHECK_NULL_RETURN(swiperNode, center);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_RETURN(swiperPattern, center);

    const auto& geometryNode = swiperNode->GetGeometryNode();
    const auto& contentSize = geometryNode->GetFrameSize();
    float centerY_ = (swiperPattern->GetDirection() == Axis::HORIZONTAL ?
        contentSize.Height() : contentSize.Width()) * DIVIDE_NUM;
    float centerX_ = (swiperPattern->GetDirection() == Axis::HORIZONTAL ?
        contentSize.Width() : contentSize.Height()) * DIVIDE_NUM;
    center = PointF(centerX_, centerY_);
    return center;
}

float ArcSwiperIndicatorPattern::GetAngleWithPoint(const PointF& conter, const PointF& point)
{
    float angle = 0.0;
    auto swiperNode = GetSwiperNode();
    CHECK_NULL_RETURN(swiperNode, angle);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_RETURN(swiperPattern, angle);

    float centerX = swiperPattern->GetDirection() == Axis::HORIZONTAL ? conter.GetX() : conter.GetY();
    float centerY = swiperPattern->GetDirection() == Axis::HORIZONTAL ? conter.GetY() : conter.GetX();
    float pointX = swiperPattern->GetDirection() == Axis::HORIZONTAL ? point.GetX() : point.GetY();
    float pointY = swiperPattern->GetDirection() == Axis::HORIZONTAL ? point.GetY() : point.GetX();
    const auto& arcDotParameters = swiperPattern->GetSwiperArcDotParameters();
    CHECK_NULL_RETURN(arcDotParameters, angle);
    std::optional<SwiperArcDirection> swiperArcDirection = arcDotParameters->arcDirection;
    CHECK_NULL_RETURN(swiperArcDirection.has_value(), angle);
    auto arcDirection = swiperArcDirection.value();
    if (NearEqual(centerY, pointY) && LessOrEqual(centerX, pointX)) {
        angle = -QUARTER_CIRCLE_ANGLE;
    } else if (NearEqual(centerX, pointX) && pointY > centerY) {
        angle = 0.0;
    } else if (NearEqual(centerY, pointY) && pointX < centerX) {
        angle = QUARTER_CIRCLE_ANGLE;
    } else if (NearEqual(centerX, pointX) && pointY < centerY) {
        angle = HALF_CIRCLE_ANGLE;
    } else if (pointX > centerX && pointY > centerY) {
        angle = atan((pointY - centerY) / (pointX - centerX)) * HALF_CIRCLE_ANGLE / M_PI - QUARTER_CIRCLE_ANGLE;
    } else if (pointX < centerX && pointY > centerY) {
        angle = QUARTER_CIRCLE_ANGLE - atan((pointY - centerY) / (centerX - pointX)) * HALF_CIRCLE_ANGLE / M_PI;
    } else if (pointX < centerX && pointY < centerY) {
        angle = QUARTER_CIRCLE_ANGLE + atan((centerY - pointY) / (centerX - pointX)) * HALF_CIRCLE_ANGLE / M_PI;
    } else {
        angle = -QUARTER_CIRCLE_ANGLE - atan((centerY - pointY) / (pointX - centerX)) * HALF_CIRCLE_ANGLE / M_PI;
    }

    return ConvertAngleWithArcDirection(arcDirection, angle);
}

float ArcSwiperIndicatorPattern::ConvertAngleWithArcDirection(SwiperArcDirection arcDirection, const float& angle)
{
    float result = 0.0;
    if (arcDirection == SwiperArcDirection::SIX_CLOCK_DIRECTION) {
        result = angle;
    } else if (arcDirection == SwiperArcDirection::THREE_CLOCK_DIRECTION) {
        if (angle > QUARTER_CIRCLE_ANGLE) {
            result = -THREE_QUARTER_CIRCLE_ANGLE + angle;
        } else {
            result  = angle + QUARTER_CIRCLE_ANGLE;
        }
        result = -result;
    } else {
        if (angle < -QUARTER_CIRCLE_ANGLE) {
            result = THREE_QUARTER_CIRCLE_ANGLE + angle;
        } else {
            result = angle - QUARTER_CIRCLE_ANGLE;
        }
    }

    return result;
}

void ArcSwiperIndicatorPattern::CalculateCycle(float angle, float startAngle, const PointF& conter, const PointF& point)
{
    if (direction_ == SwiperDirection::LEFT) {
        if (angle < startAngle && !isUpdateCycle_ && CheckPointLocation(conter, point)) {
            dragCycle_ += static_cast<int32_t>(FULL_CIRCLE_ANGLE);
            isUpdateCycle_ = true;
        } else if (angle > startAngle) {
            isUpdateCycle_ = false;
        }
    }
    if (direction_ == SwiperDirection::RIGHT) {
        if (angle > startAngle && !isUpdateCycle_ && CheckPointLocation(conter, point)) {
            dragCycle_ -= static_cast<int32_t>(FULL_CIRCLE_ANGLE);
            isUpdateCycle_ = true;
        } else if (angle < startAngle) {
            isUpdateCycle_ = false;
        }
    }
}

float ArcSwiperIndicatorPattern::GetEndAngle(const PointF& conter, const PointF& point, float startAngle)
{
    float angle = GetAngleWithPoint(conter, point);
    if (isUpageStartAngle_) {
        if (angle > startAngle + OFFSET_ANGLE) {
            direction_ = SwiperDirection::LEFT;
        } else if (angle < startAngle - OFFSET_ANGLE) {
            direction_ = SwiperDirection::RIGHT;
        }
    }
    CalculateCycle(angle, startAngle, conter, point);
    angle += dragCycle_;
    if (isUpageStartAngle_ && direction_!= SwiperDirection::UNKNOWN) {
        oldEndAngle_ = angle;
        isUpageStartAngle_ = false;
    }
    if (((direction_ == SwiperDirection::LEFT) && angle < oldEndAngle_ - OFFSET_ANGLE) ||
        ((direction_ == SwiperDirection::RIGHT) && angle > oldEndAngle_ + OFFSET_ANGLE)) {
        float angle = GetAngleWithPoint(conter, point);
        if ((direction_ == SwiperDirection::LEFT) && angle < startAngle) {
            UpadateStartAngle();
        }
        if ((direction_ == SwiperDirection::RIGHT) && angle > startAngle) {
            UpadateStartAngle();
        }
    }
    if ((direction_ == SwiperDirection::LEFT) && (angle > oldEndAngle_)) {
        oldEndAngle_ = angle;
    }
    if ((direction_ == SwiperDirection::RIGHT) && (angle < oldEndAngle_)) {
        oldEndAngle_ = angle;
    }
    if (direction_ == SwiperDirection::UNKNOWN) {
        angle = startAngle;
    }
    return angle;
}

void ArcSwiperIndicatorPattern::UpadateStartAngle()
{
    dragCycle_ = 0;
    direction_ = SwiperDirection::UNKNOWN;
    isUpageStartAngle_ = true;
    isUpdateCycle_ = false;
    oldEndAngle_ = 0;
}

bool ArcSwiperIndicatorPattern::CheckPointLocation(const PointF& conter, const PointF& point)
{
    auto swiperNode = GetSwiperNode();
    CHECK_NULL_RETURN(swiperNode, false);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    CHECK_NULL_RETURN(swiperPattern, false);

    float centerX = swiperPattern->GetDirection() == Axis::HORIZONTAL ? conter.GetX() : conter.GetY();
    float centerY = swiperPattern->GetDirection() == Axis::HORIZONTAL ? conter.GetY() : conter.GetX();
    float pointX = swiperPattern->GetDirection() == Axis::HORIZONTAL ? point.GetX() : point.GetY();
    float pointY = swiperPattern->GetDirection() == Axis::HORIZONTAL ? point.GetY() : point.GetX();
    if ((direction_ == SwiperDirection::LEFT) && pointX > centerX && pointY < centerY) {
        return true;
    }
    if ((direction_ == SwiperDirection::RIGHT) && pointX < centerX && pointY < centerY) {
        return true;
    }

    return false;
}
} // namespace OHOS::Ace::NG