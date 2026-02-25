/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include <algorithm>

#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/layout_policy_property.h"
#include "core/components_ng/property/measure_property.h"

namespace OHOS::Ace::NG {

// ViewPosReference::operator==
bool ViewPosReference::operator==(const ViewPosReference& other) const
{
    return NearEqual(viewPosStart, other.viewPosStart) &&
           NearEqual(viewPosEnd, other.viewPosEnd) &&
           NearEqual(referencePos, other.referencePos) &&
           referenceEdge == other.referenceEdge &&
           axis == other.axis;
}

// Static methods for LayoutConstraintT
template<typename T>
bool LayoutConstraintT<T>::CompareWithInfinityCheck(const OptionalSize<float>& first, const OptionalSize<float>& second)
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

template<typename T>
bool LayoutConstraintT<T>::CompareWithInfinityCheck(const SizeT<float>& first, const SizeT<float>& second)
{
    auto widthBothInf = GreaterOrEqualToInfinity(first.Width()) && GreaterOrEqualToInfinity(second.Width());
    auto heightBothInf = GreaterOrEqualToInfinity(first.Height()) && GreaterOrEqualToInfinity(second.Height());
    if (widthBothInf && heightBothInf) {
        return true;
    }
    return NearEqual(first.Width(), second.Width()) && NearEqual(first.Height(), second.Height());
}

template<typename T>
bool LayoutConstraintT<T>::CompareWithInfinityCheck(float first, float second)
{
    auto bothInf = GreaterOrEqualToInfinity(first) && GreaterOrEqualToInfinity(second);
    if (bothInf) {
        return true;
    }
    return NearEqual(first, second);
}

// Comparison operators
template<typename T>
bool LayoutConstraintT<T>::operator==(const LayoutConstraintT& layoutConstraint) const
{
    return (scaleProperty == layoutConstraint.scaleProperty) && (minSize == layoutConstraint.minSize) &&
           (maxSize == layoutConstraint.maxSize) && (percentReference == layoutConstraint.percentReference) &&
           (parentIdealSize == layoutConstraint.parentIdealSize) &&
           (selfIdealSize == layoutConstraint.selfIdealSize) && (viewPosRef == layoutConstraint.viewPosRef);
}

template<typename T>
bool LayoutConstraintT<T>::operator!=(const LayoutConstraintT& layoutConstraint) const
{
    return !(*this == layoutConstraint);
}

template<typename T>
bool LayoutConstraintT<T>::EqualWithoutPercentWidth(const LayoutConstraintT& layoutConstraint) const
{
    return (scaleProperty == layoutConstraint.scaleProperty) &&
           CompareWithInfinityCheck(minSize, layoutConstraint.minSize) &&
           CompareWithInfinityCheck(maxSize, layoutConstraint.maxSize) &&
           CompareWithInfinityCheck(parentIdealSize, layoutConstraint.parentIdealSize) &&
           CompareWithInfinityCheck(percentReference.Height(), layoutConstraint.percentReference.Height()) &&
           CompareWithInfinityCheck(selfIdealSize, layoutConstraint.selfIdealSize) &&
           (viewPosRef == layoutConstraint.viewPosRef);
}

template<typename T>
bool LayoutConstraintT<T>::EqualWithoutPercentHeight(const LayoutConstraintT& layoutConstraint) const
{
    return (scaleProperty == layoutConstraint.scaleProperty) &&
           CompareWithInfinityCheck(minSize, layoutConstraint.minSize) &&
           CompareWithInfinityCheck(maxSize, layoutConstraint.maxSize) &&
           CompareWithInfinityCheck(parentIdealSize, layoutConstraint.parentIdealSize) &&
           CompareWithInfinityCheck(percentReference.Width(), layoutConstraint.percentReference.Width()) &&
           CompareWithInfinityCheck(selfIdealSize, layoutConstraint.selfIdealSize) &&
           (viewPosRef == layoutConstraint.viewPosRef);
}

// Update methods
template<typename T>
ACE_FORCE_EXPORT
bool LayoutConstraintT<T>::UpdateSelfMarginSizeWithCheck(const OptionalSize<T>& size)
{
    if (selfIdealSize == size) {
        return false;
    }
    return selfIdealSize.UpdateSizeWithCheck(size);
}

template<typename T>
bool LayoutConstraintT<T>::UpdateIllegalSelfMarginSizeWithCheck(const OptionalSize<T>& size)
{
    if (selfIdealSize == size) {
        return false;
    }
    return selfIdealSize.UpdateIllegalSizeWithCheck(size);
}

template<typename T>
bool LayoutConstraintT<T>::UpdateIllegalSelfIdealSizeWithCheck(const OptionalSize<T>& size)
{
    if (selfIdealSize == size) {
        return false;
    }
    return selfIdealSize.UpdateIllegalSizeWithCheck(size);
}

template<typename T>
bool LayoutConstraintT<T>::UpdateParentIdealSizeWithCheck(const OptionalSize<T>&& size)
{
    if (parentIdealSize == size) {
        return false;
    }
    return parentIdealSize.UpdateSizeWithCheck(size);
}

template<typename T>
bool LayoutConstraintT<T>::UpdateIllegalParentIdealSizeWithCheck(const OptionalSize<T>&& size)
{
    if (parentIdealSize == size) {
        return false;
    }
    return parentIdealSize.UpdateIllegalSizeWithCheck(size);
}

template<typename T>
bool LayoutConstraintT<T>::UpdateParentIdealSizeByLayoutPolicy(const SizeT<T>& size, bool isMax, NG::LayoutPolicyProperty layoutPolicy)
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

template<typename T>
ACE_FORCE_EXPORT
bool LayoutConstraintT<T>::UpdateMaxSizeWithCheck(const SizeT<T>& size)
{
    if (maxSize == size) {
        return false;
    }
    return maxSize.UpdateSizeWhenSmaller(size);
}

template<typename T>
bool LayoutConstraintT<T>::UpdateMaxWidthWithCheck(const SizeT<T>& size)
{
    if (maxSize == size) {
        return false;
    }
    return maxSize.UpdateWidthWhenSmaller(size);
}

template<typename T>
bool LayoutConstraintT<T>::UpdateMaxHeightWithCheck(const SizeT<T>& size)
{
    if (maxSize == size) {
        return false;
    }
    return maxSize.UpdateHeightWhenSmaller(size);
}

template<typename T>
bool LayoutConstraintT<T>::UpdateMinSizeWithCheck(const SizeT<T>& size)
{
    if (minSize == size) {
        return false;
    }
    return minSize.UpdateSizeWhenLarger(size);
}

template<typename T>
bool LayoutConstraintT<T>::UpdatePercentReference(const SizeT<T>& size)
{
    if (percentReference == size) {
        return false;
    }
    percentReference.SetSizeT(size);
    return true;
}

// Implementations moved from .inl file to reduce header dependencies
template<typename T>
void LayoutConstraintT<T>::ApplyAspectRatio(float ratio, const std::optional<CalcSize>& calcSize,
    const std::optional<NG::LayoutPolicyProperty>& layoutPolicy, bool greaterThanApiTen)
{
    if (!Positive(ratio)) {
        // just in case ratio is illegal value
        return;
    }
    std::optional<bool> useDefinedWidth;
    if (calcSize) {
        if (calcSize.value().Width() || (layoutPolicy.has_value() && layoutPolicy->IsWidthMatch())) {
            useDefinedWidth = true;
        } else if (calcSize.value().Height() || (layoutPolicy.has_value() && layoutPolicy->IsHeightMatch())) {
            useDefinedWidth = false;
        }
    }
    if (useDefinedWidth) {
        if (useDefinedWidth.value_or(false)) {
            if (selfIdealSize.Width()) {
                selfIdealSize.SetHeight(selfIdealSize.Width().value() / ratio);
            }
            minSize.SetHeight(minSize.Width() / ratio);
            maxSize.SetHeight(maxSize.Width() / ratio);
            ApplyAspectRatioToParentIdealSize(true, ratio);
            return;
        }
        if (selfIdealSize.Height()) {
            selfIdealSize.SetWidth(selfIdealSize.Height().value() * ratio);
        }
        minSize.SetWidth(minSize.Height() * ratio);
        maxSize.SetWidth(maxSize.Height() * ratio);
        ApplyAspectRatioToParentIdealSize(false, ratio);
        return;
    } else {
        if (selfIdealSize.Width()) {
            selfIdealSize.SetHeight(selfIdealSize.Width().value() / ratio);
            minSize.SetHeight(minSize.Width() / ratio);
            maxSize.SetHeight(maxSize.Width() / ratio);
            ApplyAspectRatioToParentIdealSize(true, ratio);
            return;
        }
        if (selfIdealSize.Height()) {
            selfIdealSize.SetWidth(selfIdealSize.Height().value() * ratio);
            minSize.SetWidth(minSize.Height() * ratio);
            maxSize.SetWidth(maxSize.Height() * ratio);
            ApplyAspectRatioToParentIdealSize(false, ratio);
            return;
        }
    }
    // after previous conditions, ideal size does not exist, we use max size to rule aspect ratio
    // but nothing can be done if both width and height are inf
    if (NearEqual(maxSize.Width(), Infinity<T>()) && NearEqual(maxSize.Height(), Infinity<T>())) {
        return;
    }
    ApplyAspectRatioByMaxSize(ratio, useDefinedWidth, greaterThanApiTen);
}

template<typename T>
void LayoutConstraintT<T>::ApplyAspectRatioToParentIdealSize(bool useWidth, float ratio)
{
    if (!Positive(ratio)) {
        return;
    }
    if (useWidth && parentIdealSize.Width()) {
        parentIdealSize.SetHeight(parentIdealSize.Width().value() / ratio);
        return;
    }
    if (!parentIdealSize.Height()) {
        return;
    }
    parentIdealSize.SetWidth(parentIdealSize.Height().value() * ratio);
}

template<typename T>
void LayoutConstraintT<T>::ApplyAspectRatioByMaxSize(
    float ratio, std::optional<bool> useDefinedWidth, bool greaterThanApiTen)
{
    if (!Positive(ratio)) {
        return;
    }
    if (useDefinedWidth) {
        ApplyAspectRatioWithCalcSize(ratio, useDefinedWidth.value());
        return;
    }
    ApplyAspectRatioWithoutCalcSize(ratio, greaterThanApiTen);
}

template<typename T>
void LayoutConstraintT<T>::ApplyAspectRatioWithCalcSize(float ratio, bool useDefinedWidth)
{
    if (!Positive(ratio)) {
        return;
    }
    if (useDefinedWidth) {
        minSize.SetHeight(minSize.Width() / ratio);
        maxSize.SetHeight(maxSize.Width() / ratio);
        percentReference.SetHeight(percentReference.Width() / ratio);
        ApplyAspectRatioToParentIdealSize(true, ratio);
        return;
    }
    minSize.SetWidth(minSize.Height() * ratio);
    maxSize.SetWidth(maxSize.Height() * ratio);
    percentReference.SetWidth(percentReference.Height() / ratio);
    ApplyAspectRatioToParentIdealSize(false, ratio);
}

template<typename T>
void LayoutConstraintT<T>::ApplyAspectRatioWithoutCalcSize(float ratio, bool greaterThanApiTen)
{
    if (!Positive(ratio)) {
        return;
    }
    if (greaterThanApiTen) {
        if (percentReference.Height() * ratio > maxSize.Width()) {
            minSize.SetHeight(minSize.Width() / ratio);
            maxSize.SetHeight(maxSize.Width() / ratio);
            percentReference.SetHeight(percentReference.Width() / ratio);
            ApplyAspectRatioToParentIdealSize(true, ratio);
            return;
        }
        if (percentReference.Width() / ratio > maxSize.Height()) {
            minSize.SetWidth(minSize.Height() * ratio);
            maxSize.SetWidth(maxSize.Height() * ratio);
            percentReference.SetWidth(percentReference.Height() * ratio);
            ApplyAspectRatioToParentIdealSize(false, ratio);
        }
        return;
    } else {
        if (maxSize.Width() < maxSize.Height()) {
            minSize.SetHeight(minSize.Width() / ratio);
            maxSize.SetHeight(maxSize.Width() / ratio);
            percentReference.SetHeight(percentReference.Width() / ratio);
            ApplyAspectRatioToParentIdealSize(true, ratio);
            return;
        }
    }
    minSize.SetWidth(minSize.Height() * ratio);
    maxSize.SetWidth(maxSize.Height() * ratio);
    percentReference.SetWidth(percentReference.Height() / ratio);
    ApplyAspectRatioToParentIdealSize(false, ratio);
}

template<typename T>
void LayoutConstraintT<T>::Reset()
{
    scaleProperty.Reset();
    minSize = { 0, 0 };
    maxSize = { Infinity<T>(), Infinity<T>() };
    percentReference = { 0, 0 };
    parentIdealSize.Reset();
    selfIdealSize.Reset();
}

template<typename T>
void LayoutConstraintT<T>::MinusPadding(const std::optional<T>& left, const std::optional<T>& right,
    const std::optional<T>& top, const std::optional<T>& bottom)
{
    minSize.MinusPadding(left, right, top, bottom);
    maxSize.MinusPadding(left, right, top, bottom);
    parentIdealSize.MinusPadding(left, right, top, bottom);
    selfIdealSize.MinusPadding(left, right, top, bottom);
    percentReference.MinusPadding(left, right, top, bottom);
}

template<typename T>
void LayoutConstraintT<T>::MinusPaddingToNonNegativeSize(const std::optional<T>& left, const std::optional<T>& right,
    const std::optional<T>& top, const std::optional<T>& bottom)
{
    minSize.MinusPaddingToNonNegative(left, right, top, bottom);
    maxSize.MinusPaddingToNonNegative(left, right, top, bottom);
    parentIdealSize.MinusPadding(left, right, top, bottom);
    selfIdealSize.MinusPadding(left, right, top, bottom);
    percentReference.MinusPaddingToNonNegative(left, right, top, bottom);
}

template<typename T>
std::string LayoutConstraintT<T>::ToString() const
{
    std::string str;
    str.append("minSize: [").append(minSize.ToString()).append("]");
    str.append("maxSize: [").append(maxSize.ToString()).append("]");
    str.append("percentReference: [").append(percentReference.ToString()).append("]");
    str.append("parentIdealSize: [").append(parentIdealSize.ToString()).append("]");
    str.append("selfIdealSize: [").append(selfIdealSize.ToString()).append("]");
    return str;
}

template<typename T>
ACE_FORCE_EXPORT
SizeF LayoutConstraintT<T>::Constrain(const SizeF& size) const
{
    SizeF constrainSize;
    constrainSize.SetWidth(std::clamp(size.Width(), minSize.Width(), maxSize.Width()));
    constrainSize.SetHeight(std::clamp(size.Height(), minSize.Height(), maxSize.Height()));
    return constrainSize;
}

template struct LayoutConstraintT<float>;

} // namespace OHOS::Ace::NG
