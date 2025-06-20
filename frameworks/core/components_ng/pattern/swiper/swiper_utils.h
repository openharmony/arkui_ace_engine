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
namespace {
constexpr Dimension SWIPER_MARGIN = 16.0_vp;
constexpr Dimension SWIPER_GUTTER = 16.0_vp;
} // namespace

class SwiperUtils {
public:
    SwiperUtils() = delete;
    ~SwiperUtils() = delete;

    static bool IsStretch(const RefPtr<SwiperLayoutProperty>& property)
    {
        // If display count is setted, use stretch mode.
        CHECK_NULL_RETURN(property, true);
        return property->IsStretch();
    }

    static float GetItemSpace(const RefPtr<SwiperLayoutProperty>& property)
    {
        if (!property || property->IgnoreItemSpace()) {
            return 0.0f;
        }
        return property->GetItemSpace().value_or(0.0_px).ConvertToPx();
    }

    static LayoutConstraintF CheckLayoutPolicyConstraint(const RefPtr<SwiperLayoutProperty>& property,
        OptionalSizeF childSelfIdealSize, LayoutConstraintF layoutConstraint)
    {
        auto layoutPolicy = property->GetLayoutPolicyProperty();
        auto axis = property->GetDirection().value_or(Axis::HORIZONTAL);
        if (layoutPolicy.has_value()) {
            auto widthLayoutPolicy = layoutPolicy.value().widthLayoutPolicy_.value_or(LayoutCalPolicy::NO_MATCH);
            auto heightLayoutPolicy = layoutPolicy.value().heightLayoutPolicy_.value_or(LayoutCalPolicy::NO_MATCH);
            // crosss axis set maxSize and reset IdealSize'cross width/heigth, when layoutPolicy is matchParent
            if (axis == Axis::HORIZONTAL && heightLayoutPolicy == LayoutCalPolicy::MATCH_PARENT) {
                auto heightOpt = childSelfIdealSize.Height();
                if (heightOpt) {
                    layoutConstraint.maxSize.SetHeight(heightOpt.value());
                }
                auto width = childSelfIdealSize.Width();
                childSelfIdealSize.Reset();
                childSelfIdealSize.SetWidth(width);
            } else if (axis == Axis::VERTICAL && widthLayoutPolicy == LayoutCalPolicy::MATCH_PARENT) {
                auto widthOpt = childSelfIdealSize.Width();
                if (widthOpt) {
                    layoutConstraint.maxSize.SetWidth(widthOpt.value());
                }
                auto height = childSelfIdealSize.Height();
                childSelfIdealSize.Reset();
                childSelfIdealSize.SetHeight(height);
            }
        }
        layoutConstraint.selfIdealSize = childSelfIdealSize;
        return layoutConstraint;
    }

    static LayoutConstraintF CreateChildConstraint(
        const RefPtr<SwiperLayoutProperty>& property, const OptionalSizeF& idealSize, bool getAutoFill)
    {
        CHECK_NULL_RETURN(property, {});
        auto layoutConstraint = property->CreateChildConstraint();
        layoutConstraint.parentIdealSize = idealSize;
        auto displayCount = property->GetDisplayCount().value_or(1);
        if ((!getAutoFill && !IsStretch(property)) || NonPositive(static_cast<double>(displayCount))) {
            return layoutConstraint;
        }
        auto axis = property->GetDirection().value_or(Axis::HORIZONTAL);
        // re-determine ignoreItemSpace_ based on child calc length
        property->ResetIgnorePrevMarginAndNextMargin();
        property->ResetIgnoreItemSpace();
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
        // Invalid size need not to calculate margin
        if (!idealSize.IsNonPositive() && ((axis == Axis::HORIZONTAL && idealSize.Width().has_value()) ||
                                              (axis == Axis::VERTICAL && idealSize.Height().has_value()))) {
            auto length = axis == Axis::HORIZONTAL ? idealSize.Width().value() : idealSize.Height().value();
            childCalcIdealLength =
                (length - itemSpace * itemSpaceCount - static_cast<float>(prevMargin + nextMargin)) / displayCount;
            if (LessNotEqual(childCalcIdealLength, 0.0)) {
                // prioritize margin and displayCount, ignore itemSpace to create a positive idealLength.
                property->MarkIgnoreItemSpace();
                childCalcIdealLength = (length - static_cast<float>(prevMargin + nextMargin)) / displayCount;
            }
            if (CheckMarginPropertyExceed(property, childCalcIdealLength)) {
                prevMargin = 0.0;
                nextMargin = 0.0;
                itemSpaceCount = CaculateDisplayItemSpaceCount(property, prevMargin, nextMargin);
                childCalcIdealLength = (length - itemSpace * itemSpaceCount) / displayCount;
                if (LessNotEqual(childCalcIdealLength, 0.0)) {
                    childCalcIdealLength = length / displayCount;
                } else {
                    property->ResetIgnoreItemSpace();
                }
            }
            axis == Axis::HORIZONTAL ? childSelfIdealSize.SetWidth(childCalcIdealLength)
                                     : childSelfIdealSize.SetHeight(childCalcIdealLength);
        }
        
        return CheckLayoutPolicyConstraint(property, childSelfIdealSize, layoutConstraint);
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

    static int32_t ComputePageIndex(int32_t index, int32_t displayCount)
    {
        if (displayCount <= 0) {
            return index;
        }

        return static_cast<int32_t>(std::floor(static_cast<float>(index) / static_cast<float>(displayCount))) *
               displayCount;
    }

    static int32_t ComputePageEndIndex(int32_t index, int32_t displayCount)
    {
        if (displayCount <= 0) {
            return index;
        }

        return static_cast<int32_t>(std::floor(static_cast<float>(index) / static_cast<float>(displayCount))) *
                   displayCount +
               displayCount - 1;
    }

    static void CheckAutoFillDisplayCount(
        RefPtr<SwiperLayoutProperty>& swiperLayoutProperty, float contentWidth, int32_t totalCount)
    {
        CHECK_NULL_VOID(swiperLayoutProperty);
        bool isAutoFill = swiperLayoutProperty->GetMinSize().has_value();
        if (!isAutoFill) {
            return;
        }
        auto minSize = swiperLayoutProperty->GetMinSize()->ConvertToPx();
        auto displayCount =
            static_cast<int32_t>(floor((contentWidth - 2 * SWIPER_MARGIN.ConvertToPx() + SWIPER_GUTTER.ConvertToPx()) /
                                       (minSize + SWIPER_GUTTER.ConvertToPx())));
        if (LessOrEqual(minSize, 0)) {
            displayCount = 1;
        }
        displayCount = displayCount > 0 ? displayCount : 1;
        displayCount = displayCount > totalCount ? totalCount : displayCount;

        auto displayCountProperty = swiperLayoutProperty->GetDisplayCount().value_or(1);
        if (displayCountProperty != displayCount) {
            swiperLayoutProperty->UpdateDisplayCount(displayCount);
        }
    }

    static bool CheckIsSingleCase(const RefPtr<SwiperLayoutProperty>& property)
    {
        bool hasMinSize = property->GetMinSize().has_value() && !LessOrEqual(property->GetMinSizeValue().Value(), 0);
        bool hasPrevMargin = Positive(property->GetCalculatedPrevMargin());
        bool hasNextMargin = Positive(property->GetCalculatedNextMargin());

        return !hasMinSize && (!hasPrevMargin && !hasNextMargin) &&
               ((property->GetDisplayCount().has_value() && property->GetDisplayCountValue() == 1) ||
                   (!property->GetDisplayCount().has_value() && SwiperUtils::IsStretch(property)));
    }

private:
    static bool CheckMarginPropertyExceed(const RefPtr<SwiperLayoutProperty>& property, float childCalcIdealLength)
    {
        CHECK_NULL_RETURN(property, false);
        auto prevMargin = property->GetPrevMarginValue(0.0_px).ConvertToPx();
        auto nextMargin = property->GetNextMarginValue(0.0_px).ConvertToPx();
        if (GreatNotEqual(prevMargin, childCalcIdealLength) || GreatNotEqual(nextMargin, childCalcIdealLength)) {
            property->MarkIgnorePrevMarginAndNextMargin();
            return true;
        }
        return false;
    }
};

/**
 * @brief Helper RAII object. set @c var to @c value when this object goes out of scope.
 * REQUIRES: the life span of @c var surpasses this object.
 */
template<typename T>
class DestructSetter {
public:
    DestructSetter() = delete;
    DestructSetter(T& var, T value) : ref_(var), value_(value) {}
    ~DestructSetter()
    {
        ref_ = value_;
    }

private:
    T& ref_;
    T value_ {};

    ACE_DISALLOW_COPY_AND_MOVE(DestructSetter);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SWIPER_SWIPER_UTILS_H
