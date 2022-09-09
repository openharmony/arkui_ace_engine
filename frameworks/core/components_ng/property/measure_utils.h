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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTIES_MEASURE_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTIES_MEASURE_UTILS_H

#include <optional>

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "core/components_ng/property/border_property.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/measure_property.h"

namespace OHOS::Ace::NG {
std::optional<float> ConvertToPx(
    const CalcLength& value, const ScaleProperty& scaleProperty, float percentReference = -1.0f);

std::optional<float> ConvertToPx(
    const std::optional<CalcLength>& value, const ScaleProperty& scaleProperty, float percentReference = -1.0f);

std::optional<float> ConvertToPx(
    const Dimension& dimension, const ScaleProperty& scaleProperty, float percentReference = -1.0f);

SizeF ConvertToSize(
    const CalcSize& size, const ScaleProperty& scaleProperty, const SizeF& percentReference = SizeF(-1.0f, -1.0f));

OptionalSizeF ConvertToOptionalSize(
    const CalcSize& size, const ScaleProperty& scaleProperty, const SizeF& percentReference = SizeF(-1.0f, -1.0f));

SizeF ConstrainSize(const SizeF& size, const SizeF& minSize, const SizeF& maxSize);

void MinusPaddingToConstraint(const std::unique_ptr<PaddingProperty>& padding, LayoutConstraintF& size);

void MinusPaddingToConstraint(const PaddingProperty& padding, LayoutConstraintF& size);

PaddingPropertyF ConvertToPaddingPropertyF(const std::unique_ptr<PaddingProperty>& padding,
    const ScaleProperty& scaleProperty, float percentReference = -1.0f);

PaddingPropertyF ConvertToPaddingPropertyF(
    const PaddingProperty& padding, const ScaleProperty& scaleProperty, float percentReference = -1.0f);

BorderWidthPropertyF ConvertToBorderWidthPropertyF(const std::unique_ptr<BorderWidthProperty>& borderWidth,
    const ScaleProperty& scaleProperty, float percentReference = -1.0f);

BorderWidthPropertyF ConvertToBorderWidthPropertyF(
    const BorderWidthProperty& borderWidth, const ScaleProperty& scaleProperty, float percentReference = -1.0f);

void UpdatePaddingPropertyF(const PaddingProperty& padding, const ScaleProperty& scaleProperty, const SizeF& selfSize,
    PaddingPropertyF& paddingValue);

void AddPaddingToSize(const PaddingPropertyF& padding, SizeF& size);

void MinusPaddingToSize(const PaddingPropertyF& padding, SizeF& size);

void AddPaddingToSize(const PaddingPropertyF& padding, OptionalSizeF& size);

void MinusPaddingToSize(const PaddingPropertyF& padding, OptionalSizeF& size);

float GetCrossAxisSize(const SizeF& size, Axis axis);

float GetMainAxisOffset(const OffsetF& offset, Axis axis);

float GetMainAxisSize(const SizeF& size, Axis axis);

void SetCrossAxisSize(float value, Axis axis, SizeF& size);

std::optional<float> GetCrossAxisSize(const OptionalSizeF& size, Axis axis);

std::optional<float> GetMainAxisSize(const OptionalSizeF& size, Axis axis);

void SetCrossAxisSize(float value, Axis axis, OptionalSizeF& size);

void SetMainAxisSize(float value, Axis axis, OptionalSizeF& size);

/**
 * @brief Create node IdealSize.
 *
 * @param layoutConstraint the constraint of current node.
 * @param axis the axis of this node.
 * @param measureType the measure info.
 * @param usingMaxSize When the component cannot confirm the size, it decides whether to use the maxi or min value.
 * @return SizeF the node size info.
 */
SizeF CreateIdealSize(const LayoutConstraintF& layoutConstraint, Axis axis, MeasureType measureType, bool usingMaxSize);

/**
 * @brief Create node IdealSize.
 *
 * @param layoutConstraint the constraint of current node.
 * @param axis the axis of this node.
 * @param measureType the measure info.
 * @return SizeF the node size info.
 */
OptionalSizeF CreateIdealSize(const LayoutConstraintF& layoutConstraint, Axis axis, MeasureType measureType);
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTIES_MEASURE_UTILS_H