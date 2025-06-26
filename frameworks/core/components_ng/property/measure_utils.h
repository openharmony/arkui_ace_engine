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

#include "base/geometry/calc_dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/utils/macros.h"
#include "core/components_ng/property/border_property.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/measure_property.h"

namespace OHOS::Ace::NG {
std::optional<float> ConvertToPx(const CalcLength& value, const ScaleProperty& scaleProperty,
    float percentReference = -1.0f, const std::vector<std::string>& rpnexp = std::vector<std::string>());

std::optional<float> ConvertToPx(const std::optional<CalcLength>& value, const ScaleProperty& scaleProperty,
    float percentReference = -1.0f, const std::vector<std::string>& rpnexp = std::vector<std::string>());

std::optional<float> ConvertToPx(
    const Dimension& dimension, const ScaleProperty& scaleProperty, float percentReference = -1.0f);

SizeF ConvertToSize(const CalcSize& size, const ScaleProperty& scaleProperty,
    const SizeF& percentReference = SizeF(-1.0f, -1.0f),
    const std::pair<std::vector<std::string>, std::vector<std::string>>& calcRpnexp =
        std::pair<std::vector<std::string>, std::vector<std::string>>());

OptionalSizeF ConvertToOptionalSize(const CalcSize& size, const ScaleProperty& scaleProperty,
    const SizeF& percentReference = SizeF(-1.0f, -1.0f),
    const std::pair<std::vector<std::string>, std::vector<std::string>>& calcRpnexp =
        std::pair<std::vector<std::string>, std::vector<std::string>>());

SizeF ConstrainSize(const SizeF& size, const SizeF& minSize, const SizeF& maxSize);

PaddingPropertyF ConvertToPaddingPropertyF(const std::unique_ptr<PaddingProperty>& padding,
    const ScaleProperty& scaleProperty, float percentReference = -1.0f, bool roundPixel = true,
    bool nonNegative = false);

PaddingPropertyF ConvertToPaddingPropertyF(const PaddingProperty& padding, const ScaleProperty& scaleProperty,
    float percentReference = -1.0f, bool roundPixel = true, bool nonNegative = false);

MarginPropertyF ConvertToMarginPropertyF(const std::unique_ptr<MarginProperty>& margin,
    const ScaleProperty& scaleProperty, float percentReference = -1.0f, bool roundPixel = true);

MarginPropertyF ConvertToMarginPropertyF(const MarginProperty& margin, const ScaleProperty& scaleProperty,
    float percentReference = -1.0f, bool roundPixel = true);

BorderWidthPropertyF ConvertToBorderWidthPropertyF(const std::unique_ptr<BorderWidthProperty>& borderWidth,
    const ScaleProperty& scaleProperty, float percentReference = -1.0f, bool roundPixel = true);

BorderWidthPropertyF ConvertToBorderWidthPropertyF(const BorderWidthProperty& borderWidth,
    const ScaleProperty& scaleProperty, float percentReference = -1.0f, bool roundPixel = true);

void UpdatePaddingPropertyF(const PaddingProperty& padding, const ScaleProperty& scaleProperty, const SizeF& selfSize,
    PaddingPropertyF& paddingValue);

ACE_FORCE_EXPORT void AddPaddingToSize(const PaddingPropertyF& padding, SizeF& size);

ACE_FORCE_EXPORT void MinusPaddingToSize(const PaddingPropertyF& padding, SizeF& size);

ACE_FORCE_EXPORT void MinusPaddingToNonNegativeSize(const PaddingPropertyF& padding, SizeF& size);

void AddPaddingToSize(const PaddingPropertyF& padding, OptionalSizeF& size);

void MinusPaddingToSize(const PaddingPropertyF& padding, OptionalSizeF& size);

PaddingPropertyF AdjacentExpandToRect(RectF& adjustingRect, PaddingPropertyF& frameExpand, RectF& frameRect);

float GetCrossAxisSize(const SizeF& size, Axis axis);

float GetMainAxisOffset(const OffsetF& offset, Axis axis);

float GetMainAxisSize(const SizeF& size, Axis axis);

void SetCrossAxisSize(float value, Axis axis, SizeF& size);

std::optional<float> GetCrossAxisSize(const OptionalSizeF& size, Axis axis);

std::optional<float> GetMainAxisSize(const OptionalSizeF& size, Axis axis);

void SetCrossAxisSize(float value, Axis axis, OptionalSizeF& size);

void SetMainAxisSize(float value, Axis axis, OptionalSizeF& size);

void UpdateOptionSizeByMaxOrMinCalcLayoutConstraint(OptionalSizeF& frameSize,
    const std::optional<CalcSize>& calcLayoutConstraintMaxMinSize, const SizeT<float> percentReference, bool IsMaxSize);

ACE_FORCE_EXPORT PaddingProperty ConvertToCalcPaddingProperty(const std::optional<CalcDimension>& top,
    const std::optional<CalcDimension>& bottom, const std::optional<CalcDimension>& left,
    const std::optional<CalcDimension>& right);

/**
 * @brief Create node IdealSize.
 *
 * @param layoutConstraint the constraint of current node.
 * @param axis the axis of this node.
 * @param measureType the measure info.
 * @param usingMaxSize When the component cannot confirm the size, it decides whether to use the max or min value.
 * @return SizeF the node size info.
 */
ACE_FORCE_EXPORT SizeF CreateIdealSize(
    const LayoutConstraintF& layoutConstraint, Axis axis, MeasureType measureType, bool usingMaxSize);

/**
 * @brief Create node IdealSize.
 *
 * @param layoutConstraint the constraint of current node.
 * @param axis the axis of this node.
 * @param measureType the measure info.
 * @return SizeF the node size info.
 */
ACE_FORCE_EXPORT OptionalSizeF CreateIdealSize(
    const LayoutConstraintF& layoutConstraint, Axis axis, MeasureType measureType);

/**
 * @brief Create node IdealSize by percent reference.
 *
 * @param layoutConstraint the constraint of current node.
 * @param axis the axis of this node.
 * @param measureType the measure info.
 * @param needToConstrain constraint the result idealSize or not by min and max size in layoutConstraint.
 * @return SizeF the node size info.
 */
OptionalSizeF CreateIdealSizeByPercentRef(const LayoutConstraintF& layoutConstraint, Axis axis, MeasureType measureType,
    bool needToConstrain = false, const std::unique_ptr<MeasureProperty>& rawConstraint = nullptr);

/**
 * @brief Constrain node IdealSize by LayoutPolicy.
 *
 * @param layoutConstraint the constraint of current node.
 * @param widthLayoutPolicy the LayoutPolicy of width.
 * @param heightLayoutPolicy the LayoutPolicy of height.
 * @param axis the axis of this node.
 * @return SizeF the node size info.
 */
OptionalSizeF ConstrainIdealSizeByLayoutPolicy(const LayoutConstraintF& layoutConstraint,
    LayoutCalPolicy widthLayoutPolicy, LayoutCalPolicy heightLayoutPolicy, Axis axis);

/**
 * @brief Create max size for children which is parent's max size minus margin and padding.
 *
 * @param size the max size of parent node.
 * @param margin the margin property of this node.
 * @param padding the padding property of this node.
 */
void CreateChildrenConstraint(SizeF& size, const PaddingPropertyF& padding);

/**
 * @brief Calculate IdeaSize by maxSize and minSize, while keeping margin unaffected by margin.
 *
 * @param frameSize the current size of node.
 * @param calcLayoutConstraint the calcLayoutConstraint of this node.
 * @param percentReference the percentReference of this node.
 */
OptionalSizeF UpdateOptionSizeByCalcLayoutConstraint(const OptionalSize<float>& frameSize,
    const std::unique_ptr<MeasureProperty>& calcLayoutConstraint, const SizeT<float> percentReference);
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PROPERTIES_MEASURE_UTILS_H
