/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_INDICATOR_SWIPER_INDICATOR_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_INDICATOR_SWIPER_INDICATOR_UTILS_H

#include <optional>

#include "core/components/declaration/swiper/swiper_declaration.h"
#include "core/components_ng/pattern/swiper/swiper_layout_property.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_indicator_layout_property.h"

namespace OHOS::Ace::NG {
static SwiperIndicatorType swiperIndicatorType = SwiperIndicatorType::DOT;

inline float GET_PADDING_PROPERTY_VALUE_PX(const std::optional<CalcLength>& value)
{
    return value.value_or(CalcLength(0.0_vp)).GetDimension().ConvertToPx();
}

inline float GET_BORDER_PROPERTY_VALUE_PX(const std::optional<Dimension>& value)
{
    return value.value_or(Dimension(0.0, DimensionUnit::PX)).ConvertToPx();
}

class SwiperIndicatorUtils {
public:
    SwiperIndicatorUtils() = delete;
    ~SwiperIndicatorUtils() = delete;

    static SwiperIndicatorType GetSwiperIndicatorType()
    {
        return swiperIndicatorType;
    }

    static void SetSwiperIndicatorType(SwiperIndicatorType indicatorType)
    {
        swiperIndicatorType = indicatorType;
    }

    static const OffsetF CalcIndicatrFrameOffSet(const RefPtr<SwiperLayoutProperty>& swiperLayoutProperty,
                                                const RefPtr<SwiperIndicatorLayoutProperty>& indicatorLayoutProperty,
                                                float indicatorWidth, float indicatorHeight)
    {
        auto direction = Axis::HORIZONTAL;
        float swiperPaddingLeft = 0.0f;
        float swiperPaddingRight = 0.0f;
        float swiperPaddingTop = 0.0f;
        float swiperPaddingBottom = 0.0f;
        float borderWidthLeft = 0.0f;
        float borderWidthRight = 0.0f;
        float borderWidthTop = 0.0f;
        float borderWidthBottom = 0.0f;
        if (swiperLayoutProperty) {
            direction = swiperLayoutProperty->GetDirectionValue(Axis::HORIZONTAL);
            const auto& swiperPaddingProperty = swiperLayoutProperty->GetPaddingProperty();
            const auto& borderWidthProperty = swiperLayoutProperty->GetBorderWidthProperty();
            if (swiperPaddingProperty != nullptr) {
                swiperPaddingLeft = GET_PADDING_PROPERTY_VALUE_PX(swiperPaddingProperty->left);
                swiperPaddingRight = GET_PADDING_PROPERTY_VALUE_PX(swiperPaddingProperty->right);
                swiperPaddingTop = GET_PADDING_PROPERTY_VALUE_PX(swiperPaddingProperty->top);
                swiperPaddingBottom = GET_PADDING_PROPERTY_VALUE_PX(swiperPaddingProperty->bottom);
            }
            if (borderWidthProperty != nullptr) {
                borderWidthLeft = GET_BORDER_PROPERTY_VALUE_PX(borderWidthProperty->leftDimen);
                borderWidthRight = GET_BORDER_PROPERTY_VALUE_PX(borderWidthProperty->rightDimen);
                borderWidthTop = GET_BORDER_PROPERTY_VALUE_PX(borderWidthProperty->topDimen);
                borderWidthBottom = GET_BORDER_PROPERTY_VALUE_PX(borderWidthProperty->bottomDimen);
            }
        }

        CHECK_NULL_RETURN(indicatorLayoutProperty, OffsetF(0.0f, 0.0f));
        auto left = indicatorLayoutProperty->GetLeft();
        auto right = indicatorLayoutProperty->GetRight();
        auto top = indicatorLayoutProperty->GetTop();
        auto bottom = indicatorLayoutProperty->GetBottom();
        const auto& layoutConstraint = indicatorLayoutProperty->GetLayoutConstraint();
        float swiperWidth = 0.0f;
        float swiperHeight = 0.0f;
        if (layoutConstraint.has_value()) {
            swiperWidth = layoutConstraint->parentIdealSize.Width().value_or(0.0f);
            swiperHeight = layoutConstraint->parentIdealSize.Height().value_or(0.0f);
        }

        return OffsetF {CalcIndicatrOffSetX(left, right, swiperPaddingLeft, swiperPaddingRight,
                                            borderWidthLeft, borderWidthRight,
                                            swiperWidth, indicatorWidth, direction),
                        CalcIndicatrOffsetY(top, bottom, swiperPaddingTop, swiperPaddingBottom,
                                            borderWidthTop, borderWidthBottom,
                                            swiperHeight, indicatorHeight, direction)};
    }

    static float GetValidEdgeLength(float swiperLength, float indicatorLength, const Dimension& edge)
    {
        float edgeLength = edge.Unit() == DimensionUnit::PERCENT ? swiperLength * edge.Value() : edge.ConvertToPx();
        if (!NearZero(edgeLength) && edgeLength > (swiperLength - indicatorLength)) {
            edgeLength = swiperLength - indicatorLength;
        }
        if (edgeLength < 0.0) {
            edgeLength = 0.0;
        }
        return edgeLength;
    }

    static int32_t GetLoopIndex(int32_t index, int32_t totalCount)
    {
        if (totalCount <= 0) {
            return index;
        }

        auto loopIndex = index;
        while (loopIndex < 0) {
            loopIndex = loopIndex + totalCount;
        }
        loopIndex %= totalCount;
        return loopIndex;
    }

    static int32_t CalcLoopCount(int32_t index, int32_t totalCount)
    {
        if (totalCount <= 0) {
            return 0;
        }

        if (index < 0) {
            index++;
        }

        return std::abs(index / totalCount);
    }

private:
    static float CalcIndicatrOffSetX(const std::optional<Dimension>& left, const std::optional<Dimension>& right,
                                    float swiperPaddingLeft, float swiperPaddingRight,
                                    float borderWidthLeft, float borderWidthRight,
                                    float swiperWidth, float indicatorWidth, const Axis& direction)
    {
        float offsetX = 0.0f;
        if (left.has_value() && GreatOrEqual(left.value().Value(), 0)) {
            auto leftValue = GetValidEdgeLength(swiperWidth, indicatorWidth, left.value());
            offsetX = leftValue + swiperPaddingLeft + borderWidthLeft;
        } else if (right.has_value() && GreatOrEqual(right.value().Value(), 0)) {
            auto rightValue = GetValidEdgeLength(swiperWidth, indicatorWidth, right.value());
            offsetX = swiperWidth - indicatorWidth - rightValue - swiperPaddingRight - borderWidthRight;
        } else {
            if (direction == Axis::HORIZONTAL) {
                offsetX = (swiperWidth - swiperPaddingRight - borderWidthRight +
                    swiperPaddingLeft + borderWidthLeft - indicatorWidth) * 0.5f;
            } else {
                offsetX = swiperWidth - indicatorWidth - swiperPaddingRight - borderWidthRight;
            }
        }
        return offsetX;
    }

    static float CalcIndicatrOffsetY(const std::optional<Dimension>& top, const std::optional<Dimension>& bottom,
                                    float swiperPaddingTop, float swiperPaddingBottom,
                                    float borderWidthTop, float borderWidthBottom,
                                    float swiperHeight, float indicatorHeight, const Axis& direction)
    {
        float offsetY = 0.0f;
        if (top.has_value() && GreatOrEqual(top.value().Value(), 0)) {
            auto topValue = GetValidEdgeLength(swiperHeight, indicatorHeight, top.value());
            offsetY = topValue + swiperPaddingTop + borderWidthTop;
        } else if (bottom.has_value() && GreatOrEqual(bottom.value().Value(), 0)) {
            auto bottomValue = GetValidEdgeLength(swiperHeight, indicatorHeight, bottom.value());
            offsetY = swiperHeight - indicatorHeight - bottomValue - swiperPaddingBottom - borderWidthBottom;
        } else {
            if (direction == Axis::HORIZONTAL) {
                offsetY = swiperHeight - indicatorHeight - swiperPaddingBottom - borderWidthBottom;
            } else {
                offsetY = (swiperHeight - swiperPaddingBottom - borderWidthBottom +
                    swiperPaddingTop + borderWidthTop - indicatorHeight) * 0.5f;
            }
        }
        return offsetY;
    }
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_INDICATOR_SWIPER_INDICATOR_UTILS_H
