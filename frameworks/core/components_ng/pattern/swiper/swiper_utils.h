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
        if (property->HasDisplayCount()) {
            return true;
        }

        return property->GetDisplayMode().value_or(SwiperDisplayMode::STRETCH) == SwiperDisplayMode::STRETCH;
    }

    static float GetItemSpace(const RefPtr<SwiperLayoutProperty>& property)
    {
        auto scale = property->GetLayoutConstraint()->scaleProperty;
        return ConvertToPx(property->GetItemSpace().value_or(0.0_px), scale).value_or(0);
    }

    static LayoutConstraintF CreateChildConstraint(const RefPtr<SwiperLayoutProperty>& property, const SizeF& idealSize)
    {
        auto layoutConstraint = property->CreateChildConstraint();
        layoutConstraint.parentIdealSize = OptionalSizeF(idealSize);
        if (IsStretch(property)) {
            auto displayCount = property->GetDisplayCount().value_or(1);
            auto axis = property->GetDirection().value_or(Axis::HORIZONTAL);
            auto itemSpace = GetItemSpace(property);
            SizeF selfIdealSize = idealSize;
            if (axis == Axis::HORIZONTAL) {
                selfIdealSize.SetWidth((idealSize.Width() - itemSpace * displayCount) / displayCount);
            } else if (axis == Axis::VERTICAL) {
                selfIdealSize.SetHeight((idealSize.Height() - itemSpace * displayCount) / displayCount);
            }
            layoutConstraint.selfIdealSize = OptionalSizeF(selfIdealSize);
            return layoutConstraint;
        }

        return layoutConstraint;
    }
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_SWIPER_UTILS_H
