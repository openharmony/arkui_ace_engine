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

#include "base/geometry/ng/size_t.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/measure_property.h"

namespace OHOS::Ace::NG {
std::optional<float> ConvertToPx(
    const CalcLength& value, const ScaleProperty& scaleProperty, float parentLength = -1.0f);

std::optional<float> ConvertToPx(
    const std::optional<CalcLength>& value, const ScaleProperty& scaleProperty, float parentLength = -1.0f);

std::optional<float> ConvertToPx(
    const Dimension& dimension, const ScaleProperty& scaleProperty, float parentLength = -1.0f);

SizeF ConvertToSize(
    const CalcSize& size, const ScaleProperty& scaleProperty, const SizeF& parentSize = SizeF(-1.0f, -1.0f));

SizeF ConstrainSize(const SizeF& size, const SizeF& minSize, const SizeF& maxSize);

void MinusPaddingToConstraint(const std::unique_ptr<PaddingProperty>& padding, LayoutConstraintF& size);

void MinusPaddingToConstraint(const PaddingProperty& padding, LayoutConstraintF& size);

PaddingPropertyF ConvertToPaddingPropertyF(
    const std::unique_ptr<PaddingProperty>& padding, const ScaleProperty& scaleProperty, float parentWidth = -1.0f);

PaddingPropertyF ConvertToPaddingPropertyF(
    const PaddingProperty& padding, const ScaleProperty& scaleProperty, float parentWidth = -1.0f);

void UpdatePaddingPropertyF(const PaddingProperty& padding, const ScaleProperty& scaleProperty, const SizeF& selfSize,
    PaddingPropertyF& paddingValue);

void AddPaddingToSize(const PaddingPropertyF& padding, SizeF& size);

void MinusPaddingToSize(const PaddingPropertyF& padding, SizeF& size);
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTIES_MEASURE_UTILS_H