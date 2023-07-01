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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_SWIPER_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_SWIPER_UTILS_H

#include <optional>

#include "base/geometry/axis.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/swiper/swiper_layout_property.h"
#include "core/components_ng/pattern/swiper/swiper_paint_property.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {

class SwiperUtils {
public:
    SwiperUtils() = delete;
    ~SwiperUtils() = delete;

    static bool IsStretch(const RefPtr<SwiperLayoutProperty>& property)
    {
        // If display count is setted, use stretch mode.
        CHECK_NULL_RETURN(property, true);
        if (property->HasDisplayCount() && !property->HasMinSize()) {
            return true;
        }

        return property->GetDisplayMode().value_or(SwiperDisplayMode::STRETCH) == SwiperDisplayMode::STRETCH;
    }

    static float GetItemSpace(const RefPtr<SwiperLayoutProperty>& property)
    {
        auto scale = property->GetLayoutConstraint()->scaleProperty;
        return ConvertToPx(property->GetItemSpace().value_or(0.0_px), scale).value_or(0);
    }

    static LayoutConstraintF CreateChildConstraint(
        const RefPtr<SwiperLayoutProperty>& property, const OptionalSizeF& idealSize)
    {
        auto layoutConstraint = property->CreateChildConstraint();
        layoutConstraint.parentIdealSize = idealSize;
        auto displayCount = property->GetDisplayCount().value_or(1);
        if (!IsStretch(property) || NonPositive(static_cast<double>(displayCount))) {
            return layoutConstraint;
        }
        auto axis = property->GetDirection().value_or(Axis::HORIZONTAL);
        auto itemSpace = GetItemSpace(property);
        auto parentMainSize = idealSize.MainSize(axis);
        if (parentMainSize.has_value() && itemSpace > parentMainSize.value()) {
            itemSpace = 0.0f;
        }
        auto prevMargin = property->GetPrevMarginValue(0.0_px).ConvertToPx();
        auto nextMargin = property->GetNextMarginValue(0.0_px).ConvertToPx();
        auto itemSpaceCount = CaculateDisplayItemSpaceCount(property, prevMargin, nextMargin);
        auto childSelfIdealSize = idealSize;
        float childCalcIdealLength = 0.0f;

        if (axis == Axis::HORIZONTAL) {
            if (idealSize.Width().has_value()) {
                childCalcIdealLength = (idealSize.Width().value() - itemSpace * itemSpaceCount -
                                        static_cast<float>(prevMargin + nextMargin)) / displayCount;
                if (CheckMarginPropertyExceed(property, childCalcIdealLength)) {
                    prevMargin = 0.0;
                    nextMargin = 0.0;
                    itemSpaceCount = CaculateDisplayItemSpaceCount(property, prevMargin, nextMargin);
                    childCalcIdealLength = (idealSize.Width().value() - itemSpace * itemSpaceCount) / displayCount;
                }
                childSelfIdealSize.SetWidth(childCalcIdealLength);
            }
        } else if (axis == Axis::VERTICAL) {
            if (idealSize.Height().has_value()) {
                childCalcIdealLength = (idealSize.Height().value() - itemSpace * itemSpaceCount -
                                        static_cast<float>(prevMargin + nextMargin)) / displayCount;
                if (CheckMarginPropertyExceed(property, childCalcIdealLength)) {
                    prevMargin = 0.0;
                    nextMargin = 0.0;
                    itemSpaceCount = CaculateDisplayItemSpaceCount(property, prevMargin, nextMargin);
                    childCalcIdealLength = (idealSize.Height().value() -
                                            itemSpace * itemSpaceCount) / displayCount;
                }
                childSelfIdealSize.SetHeight(childCalcIdealLength);
            }
        }

        layoutConstraint.selfIdealSize = childSelfIdealSize;
        return layoutConstraint;
    }

    static int32_t CaculateDisplayItemSpaceCount(
        const RefPtr<SwiperLayoutProperty>& property, double prevMargin, double nextMargin)
    {
        CHECK_NULL_RETURN(property, 0);
        auto count = property->GetDisplayCountValue(1);
        count = (Positive(static_cast<double>(count)) ? count : 1);
        if (Positive(prevMargin) && Positive(nextMargin)) {
            return count + 1;
        } else if (NonPositive(prevMargin) && NonPositive(nextMargin)) {
            return count - 1;
        } else {
            return count;
        }
    }

private:
    static bool CheckMarginPropertyExceed(
        const RefPtr<SwiperLayoutProperty>& property, float childCalcIdealLength)
    {
        CHECK_NULL_RETURN(property, false);
        auto prevMargin = property->GetPrevMarginValue(0.0_px).ConvertToPx();
        auto nextMargin = property->GetNextMarginValue(0.0_px).ConvertToPx();
        if (GreatNotEqual(prevMargin, childCalcIdealLength) ||
            GreatNotEqual(nextMargin, childCalcIdealLength)) {
            property->UpdatePrevMargin(0.0_px);
            property->UpdateNextMargin(0.0_px);
            return true;
        }
        return false;
    }
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_SWIPER_UTILS_H
