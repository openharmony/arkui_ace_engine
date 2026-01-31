/*
 * Copyright (c) 2022-2026 Huawei Device Co., Ltd.
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

#include <optional>
#include <string>

#include "base/geometry/ng/size_t.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/layout_policy_property.h"
#include "ui/base/macros.h"

namespace OHOS::Ace::NG {

// Forward declarations to reduce header dependencies
class CalcSize;

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

    bool operator==(const ViewPosReference &other) const;
};

template<typename T>
struct ACE_FORCE_EXPORT LayoutConstraintT {
    ScaleProperty scaleProperty = ScaleProperty::CreateScaleProperty();
    SizeT<T> minSize { 0, 0 };
    SizeT<T> maxSize { Infinity<T>(), Infinity<T>() };
    SizeT<T> percentReference { 0, 0 };
    OptionalSize<T> parentIdealSize;
    OptionalSize<T> selfIdealSize;
    std::optional<ViewPosReference> viewPosRef;

    static bool CompareWithInfinityCheck(const OptionalSize<float>& first, const OptionalSize<float>& second);
    static bool CompareWithInfinityCheck(const SizeT<float>& first, const SizeT<float>& second);
    static bool CompareWithInfinityCheck(float first, float second);

    void ApplyAspectRatio(float ratio, const std::optional<CalcSize>& calcSize,
        const std::optional<NG::LayoutPolicyProperty>& layoutPolicy = std::nullopt, bool greaterThanApiTen = false);

    void ApplyAspectRatioToParentIdealSize(bool useWidth, float ratio);

    void ApplyAspectRatioByMaxSize(float ratio, std::optional<bool> useDefinedWidth, bool greaterThanApiTen = false);

    void ApplyAspectRatioWithCalcSize(float ratio, bool useDefinedWidth);

    void ApplyAspectRatioWithoutCalcSize(float ratio, bool greaterThanApiTen = false);

    void Reset();

    void MinusPadding(const std::optional<T>& left, const std::optional<T>& right, const std::optional<T>& top,
        const std::optional<T>& bottom);

    void MinusPaddingToNonNegativeSize(const std::optional<T>& left, const std::optional<T>& right,
        const std::optional<T>& top, const std::optional<T>& bottom);

    bool operator==(const LayoutConstraintT& layoutConstraint) const;
    bool operator!=(const LayoutConstraintT& layoutConstraint) const;
    bool EqualWithoutPercentWidth(const LayoutConstraintT& layoutConstraint) const;
    bool EqualWithoutPercentHeight(const LayoutConstraintT& layoutConstraint) const;

    ACE_FORCE_EXPORT bool UpdateSelfMarginSizeWithCheck(const OptionalSize<T>& size);
    bool UpdateIllegalSelfMarginSizeWithCheck(const OptionalSize<T>& size);
    bool UpdateIllegalSelfIdealSizeWithCheck(const OptionalSize<T>& size);
    bool UpdateParentIdealSizeWithCheck(const OptionalSize<T>&& size);
    bool UpdateIllegalParentIdealSizeWithCheck(const OptionalSize<T>&& size);
    bool UpdateParentIdealSizeByLayoutPolicy(const SizeT<T>& size, bool isMax, NG::LayoutPolicyProperty layoutPolicy);
    ACE_FORCE_EXPORT bool UpdateMaxSizeWithCheck(const SizeT<T>& size);
    bool UpdateMaxWidthWithCheck(const SizeT<T>& size);
    bool UpdateMaxHeightWithCheck(const SizeT<T>& size);
    bool UpdateMinSizeWithCheck(const SizeT<T>& size);
    bool UpdatePercentReference(const SizeT<T>& size);

    std::string ToString() const;

    ACE_FORCE_EXPORT SizeF Constrain(const SizeF& size) const;
};

using LayoutConstraintF = LayoutConstraintT<float>;
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTIES_LAYOUT_CONSTRAINT_H
