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
#include "core/components_ng/property/measure_property.h"

namespace OHOS::Ace::NG {
template<typename T>
struct LayoutConstraintT {
    ScaleProperty scaleProperty = ScaleProperty::CreateScaleProperty();
    SizeT<T> minSize { 0, 0 };
    SizeT<T> maxSize { Infinity<T>(), Infinity<T>() };
    SizeT<T> percentReference { 0, 0 };
    OptionalSize<T> parentIdealSize;
    OptionalSize<T> selfIdealSize;

    void ApplyAspectRatio(float ratio, const std::optional<CalcSize>& calcSize);

    void ApplyAspectRatioToParentIdealSize(bool useWidth, float ratio);

    void ApplyAspectRatioByMaxSize(float ratio, std::optional<bool> useDefinedWidth);

    void ApplyAspectRatioWithCalcSize(float ratio, bool useDefinedWidth);

    void ApplyAspectRatioWithoutCalcSize(float ratio);

    void Reset();

    void MinusPadding(const std::optional<T>& left, const std::optional<T>& right,
        const std::optional<T>& top, const std::optional<T>& bottom);

    bool operator==(const LayoutConstraintT& layoutConstraint) const
    {
        return (scaleProperty == layoutConstraint.scaleProperty) && (minSize == layoutConstraint.minSize) &&
               (maxSize == layoutConstraint.maxSize) && (percentReference == layoutConstraint.percentReference) &&
               (parentIdealSize == layoutConstraint.parentIdealSize) &&
               (selfIdealSize == layoutConstraint.selfIdealSize);
    }

    bool operator!=(const LayoutConstraintT& layoutConstraint) const
    {
        return !(*this == layoutConstraint);
    }

    bool EqualWithoutPercentWidth(const LayoutConstraintT& layoutConstraint) const
    {
        return (scaleProperty == layoutConstraint.scaleProperty) && (minSize == layoutConstraint.minSize) &&
            (maxSize == layoutConstraint.maxSize) && (parentIdealSize == layoutConstraint.parentIdealSize) &&
            (percentReference.Height() == layoutConstraint.percentReference.Height()) &&
            (selfIdealSize == layoutConstraint.selfIdealSize);
    }

    bool EqualWithoutPercentHeight(const LayoutConstraintT& layoutConstraint) const
    {
        return (scaleProperty == layoutConstraint.scaleProperty) && (minSize == layoutConstraint.minSize) &&
            (maxSize == layoutConstraint.maxSize) && (parentIdealSize == layoutConstraint.parentIdealSize) &&
            (percentReference.Width() == layoutConstraint.percentReference.Width()) &&
            (selfIdealSize == layoutConstraint.selfIdealSize);
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

    bool UpdateMaxSizeWithCheck(const SizeT<T>& size)
    {
        if (maxSize == size) {
            return false;
        }
        return maxSize.UpdateSizeWhenSmaller(size);
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
