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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTIES_LAYOUT_CONSTRAINT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTIES_LAYOUT_CONSTRAINT_H

#include <algorithm>
#include <optional>
#include <string>

#include "base/geometry/ng/size_t.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/layout_policy_property.h"
#include "core/components_ng/property/measure_property.h"

namespace OHOS::Ace::NG {
enum class ReferenceEdge {
    START,
    END,
};
struct ViewPosReference {
    float viewPosStart;
    float viewPosEnd;
    float referencePos;
    ReferenceEdge referenceEdge;
    Axis axis;

    bool operator==(const ViewPosReference &other) const
    {
        return NearEqual(viewPosStart, other.viewPosStart) &&
               NearEqual(viewPosEnd, other.viewPosEnd) &&
               NearEqual(referencePos, other.referencePos) &&
               referenceEdge == other.referenceEdge &&
               axis == other.axis;
    }
};
template<typename T>
struct LayoutConstraintT {
    ScaleProperty scaleProperty = ScaleProperty::CreateScaleProperty();
    SizeT<T> minSize { 0, 0 };
    SizeT<T> maxSize { Infinity<T>(), Infinity<T>() };
    SizeT<T> percentReference { 0, 0 };
    OptionalSize<T> parentIdealSize;
    OptionalSize<T> selfIdealSize;
    std::optional<ViewPosReference> viewPosRef;

    static bool CompareWithInfinityCheck(const OptionalSize<float>& first, const OptionalSize<float>& second)
    {
        if (first.Width().has_value() ^ second.Width().has_value()) {
            return false;
        }
        auto widthBothInf = GreaterOrEqualToInfinity(first.Width().value_or(0.0f)) &&
                            GreaterOrEqualToInfinity(second.Width().value_or(0.0f));
        if (!widthBothInf && !NearEqual(first.Width().value_or(0), second.Width().value_or(0))) {
            return false;
        }
        if (first.Height().has_value() ^ second.Height().has_value()) {
            return false;
        }
        auto heightBothInf = GreaterOrEqualToInfinity(first.Height().value_or(0.0f)) &&
                            GreaterOrEqualToInfinity(second.Height().value_or(0.0f));
        if (!heightBothInf && !NearEqual(first.Height().value_or(0), second.Height().value_or(0))) {
            return false;
        }
        return true;
    }

    static bool CompareWithInfinityCheck(const SizeT<float>& first, const SizeT<float>& second)
    {
        auto widthBothInf = GreaterOrEqualToInfinity(first.Width()) && GreaterOrEqualToInfinity(second.Width());
        auto heightBothInf = GreaterOrEqualToInfinity(first.Height()) && GreaterOrEqualToInfinity(second.Height());
        if (widthBothInf && heightBothInf) {
            return true;
        }
        return NearEqual(first.Width(), second.Width()) && NearEqual(first.Height(), second.Height());
    }

    static bool CompareWithInfinityCheck(float first, float second)
    {
        auto bothInf = GreaterOrEqualToInfinity(first) && GreaterOrEqualToInfinity(second);
        if (bothInf) {
            return true;
        }
        return NearEqual(first, second);
    }

    void ApplyAspectRatio(float ratio, const std::optional<CalcSize>& calcSize, bool greaterThanApiTen = false);

    void ApplyAspectRatioToParentIdealSize(bool useWidth, float ratio);

    void ApplyAspectRatioByMaxSize(float ratio, std::optional<bool> useDefinedWidth, bool greaterThanApiTen = false);

    void ApplyAspectRatioWithCalcSize(float ratio, bool useDefinedWidth);

    void ApplyAspectRatioWithoutCalcSize(float ratio, bool greaterThanApiTen = false);

    void Reset();

    void MinusPadding(const std::optional<T>& left, const std::optional<T>& right, const std::optional<T>& top,
        const std::optional<T>& bottom);

    void MinusPaddingToNonNegativeSize(const std::optional<T>& left, const std::optional<T>& right,
        const std::optional<T>& top, const std::optional<T>& bottom);

    bool operator==(const LayoutConstraintT& layoutConstraint) const
    {
        return (scaleProperty == layoutConstraint.scaleProperty) && (minSize == layoutConstraint.minSize) &&
               (maxSize == layoutConstraint.maxSize) && (percentReference == layoutConstraint.percentReference) &&
               (parentIdealSize == layoutConstraint.parentIdealSize) &&
               (selfIdealSize == layoutConstraint.selfIdealSize) && (viewPosRef == layoutConstraint.viewPosRef);
    }

    bool operator!=(const LayoutConstraintT& layoutConstraint) const
    {
        return !(*this == layoutConstraint);
    }

    bool EqualWithoutPercentWidth(const LayoutConstraintT& layoutConstraint) const
    {
        return (scaleProperty == layoutConstraint.scaleProperty) &&
               CompareWithInfinityCheck(minSize, layoutConstraint.minSize) &&
               CompareWithInfinityCheck(maxSize, layoutConstraint.maxSize) &&
               CompareWithInfinityCheck(parentIdealSize, layoutConstraint.parentIdealSize) &&
               CompareWithInfinityCheck(percentReference.Height(), layoutConstraint.percentReference.Height()) &&
               CompareWithInfinityCheck(selfIdealSize, layoutConstraint.selfIdealSize) &&
               (viewPosRef == layoutConstraint.viewPosRef);
    }

    bool EqualWithoutPercentHeight(const LayoutConstraintT& layoutConstraint) const
    {
        return (scaleProperty == layoutConstraint.scaleProperty) &&
               CompareWithInfinityCheck(minSize, layoutConstraint.minSize) &&
               CompareWithInfinityCheck(maxSize, layoutConstraint.maxSize) &&
               CompareWithInfinityCheck(parentIdealSize, layoutConstraint.parentIdealSize) &&
               CompareWithInfinityCheck(percentReference.Width(), layoutConstraint.percentReference.Width()) &&
               CompareWithInfinityCheck(selfIdealSize, layoutConstraint.selfIdealSize) &&
               (viewPosRef == layoutConstraint.viewPosRef);
    }

    bool UpdateSelfMarginSizeWithCheck(const OptionalSize<T>& size)
    {
        if (selfIdealSize == size) {
            return false;
        }
        return selfIdealSize.UpdateSizeWithCheck(size);
    }

    bool UpdateIllegalSelfMarginSizeWithCheck(const OptionalSize<T>& size)
    {
        if (selfIdealSize == size) {
            return false;
        }
        return selfIdealSize.UpdateIllegalSizeWithCheck(size);
    }

    bool UpdateIllegalSelfIdealSizeWithCheck(const OptionalSize<T>& size)
    {
        if (selfIdealSize == size) {
            return false;
        }
        return selfIdealSize.UpdateIllegalSizeWithCheck(size);
    }

    bool UpdateParentIdealSizeWithCheck(const OptionalSize<T>&& size)
    {
        if (parentIdealSize == size) {
            return false;
        }
        return parentIdealSize.UpdateSizeWithCheck(size);
    }

    bool UpdateIllegalParentIdealSizeWithCheck(const OptionalSize<T>&& size)
    {
        if (parentIdealSize == size) {
            return false;
        }
        return parentIdealSize.UpdateIllegalSizeWithCheck(size);
    }

    bool UpdateParentIdealSizeByLayoutPolicy(const SizeT<T>& size, bool isMax, NG::LayoutPolicyProperty layoutPolicy)
    {
        bool widthUpdated = false;
        bool heightUpdated = false;
        if (layoutPolicy.IsWidthMatch()) {
            if (isMax) {
                widthUpdated = parentIdealSize.UpdateWidthWhenSmaller(size);
            } else {
                widthUpdated = parentIdealSize.UpdateWidthWhenLarger(size);
            }
        }
        if (layoutPolicy.IsHeightMatch()) {
            if (isMax) {
                heightUpdated = parentIdealSize.UpdateHeightWhenSmaller(size);
            } else {
                heightUpdated = parentIdealSize.UpdateHeightWhenLarger(size);
            }
        }
        return widthUpdated || heightUpdated;
    }

    bool UpdateMaxSizeWithCheck(const SizeT<T>& size)
    {
        if (maxSize == size) {
            return false;
        }
        return maxSize.UpdateSizeWhenSmaller(size);
    }

    bool UpdateMaxWidthWithCheck(const SizeT<T>& size)
    {
        if (maxSize == size) {
            return false;
        }
        return maxSize.UpdateWidthWhenSmaller(size);
    }

    bool UpdateMaxHeightWithCheck(const SizeT<T>& size)
    {
        if (maxSize == size) {
            return false;
        }
        return maxSize.UpdateHeightWhenSmaller(size);
    }

    bool UpdateMinSizeWithCheck(const SizeT<T>& size)
    {
        if (minSize == size) {
            return false;
        }
        return minSize.UpdateSizeWhenLarger(size);
    }

    bool UpdatePercentReference(const SizeT<T>& size)
    {
        if (percentReference == size) {
            return false;
        }
        percentReference.SetSizeT(size);
        return true;
    }

    std::string ToString() const;

    SizeF Constrain(const SizeF& size) const;
};

using LayoutConstraintF = LayoutConstraintT<float>;
} // namespace OHOS::Ace::NG

#include "layout_constraint.inl"

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTIES_LAYOUT_CONSTRAINT_H
