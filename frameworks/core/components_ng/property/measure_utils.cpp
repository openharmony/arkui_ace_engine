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

#include "core/components_ng/property/measure_utils.h"

#include <optional>

#include "base/geometry/ng/size_t.h"
#include "base/log/log.h"
#include "base/utils/utils.h"

namespace OHOS::Ace::NG {
SizeF ConvertToSize(const CalcSize& size, const ScaleProperty& scaleProperty, const SizeF& parentSize)
{
    auto width = ConvertToPx(size.Width(), scaleProperty, parentSize.Width());
    auto height = ConvertToPx(size.Height(), scaleProperty, parentSize.Height());
    return { width.value_or(-1.0f), height.value_or(-1.0f) };
}

std::optional<float> ConvertToPx(const CalcLength& value, const ScaleProperty& scaleProperty, float parentLength)
{
    double result = -1.0;
    if (!value.NormalizeToPx(
            scaleProperty.vpScale, scaleProperty.fpScale, scaleProperty.lpxScale, parentLength, result)) {
        LOGE("fail to Convert CalcDimension To Px: %{public}f, %{public}f, %{public}f, %{public}f",
            scaleProperty.vpScale, scaleProperty.fpScale, scaleProperty.lpxScale, parentLength);
        return std::nullopt;
    }
    return static_cast<float>(result);
}

std::optional<float> ConvertToPx(
    const std::optional<CalcLength>& value, const ScaleProperty& scaleProperty, float parentLength)
{
    if (!value) {
        return std::nullopt;
    }
    double result = -1.0;
    if (!value.value().NormalizeToPx(
            scaleProperty.vpScale, scaleProperty.fpScale, scaleProperty.lpxScale, parentLength, result)) {
        LOGE("optional: fail to Convert CalcDimension To Px: %{public}f, %{public}f, %{public}f, %{public}f",
            scaleProperty.vpScale, scaleProperty.fpScale, scaleProperty.lpxScale, parentLength);
        return std::nullopt;
    }
    return static_cast<float>(result);
}

std::optional<float> ConvertToPx(const Dimension& dimension, const ScaleProperty& scaleProperty, float parentLength)
{
    double result = -1.0;
    if (!dimension.NormalizeToPx(
            scaleProperty.vpScale, scaleProperty.fpScale, scaleProperty.lpxScale, parentLength, result)) {
        LOGE("fail to Convert dimension To Px: %{public}f, %{public}f, %{public}f, %{public}f", scaleProperty.vpScale,
            scaleProperty.fpScale, scaleProperty.lpxScale, parentLength);
        return std::nullopt;
    }
    return static_cast<float>(result);
}

SizeF ConstrainSize(const SizeF& size, const SizeF& minSize, const SizeF& maxSize)
{
    float height = std::max(minSize.Height(), size.Height());
    if (maxSize.Height() > 0) {
        height = std::min(maxSize.Height(), height);
    }
    float width = std::max(minSize.Width(), size.Width());
    if (maxSize.Width() > 0) {
        width = std::min(maxSize.Width(), width);
    }
    return { width, height };
}

void MinusPaddingToConstraint(const std::unique_ptr<PaddingProperty>& padding, LayoutConstraintF& size)
{
    if (!padding) {
        return;
    }
    MinusPaddingToConstraint(*padding, size);
}

void MinusPaddingToConstraint(const PaddingProperty& padding, LayoutConstraintF& size)
{
    auto width = size.selfIdealSize.has_value() ? size.selfIdealSize->Width() : 0;
    auto height = size.selfIdealSize.has_value() ? size.selfIdealSize->Height() : 0;
    auto left = ConvertToPx(padding.left, size.scaleProperty, width);
    auto right = ConvertToPx(padding.right, size.scaleProperty, width);
    auto top = ConvertToPx(padding.top, size.scaleProperty, height);
    auto bottom = ConvertToPx(padding.bottom, size.scaleProperty, height);
    size.MinusPadding(left, right, top, bottom);
}

PaddingPropertyF ConvertToPaddingPropertyF(
    const std::unique_ptr<PaddingProperty>& padding, const ScaleProperty& scaleProperty, float parentWidth)
{
    if (!padding) {
        return {};
    }
    return ConvertToPaddingPropertyF(*padding, scaleProperty, parentWidth);
}

PaddingPropertyF ConvertToPaddingPropertyF(
    const PaddingProperty& padding, const ScaleProperty& scaleProperty, float parentWidth)
{
    auto left = ConvertToPx(padding.left, scaleProperty, parentWidth);
    auto right = ConvertToPx(padding.right, scaleProperty, parentWidth);
    auto top = ConvertToPx(padding.top, scaleProperty, parentWidth);
    auto bottom = ConvertToPx(padding.bottom, scaleProperty, parentWidth);
    return PaddingPropertyF { left, right, top, bottom };
}

void UpdatePaddingPropertyF(const PaddingProperty& padding, const ScaleProperty& scaleProperty, const SizeF& selfSize,
    PaddingPropertyF& paddingValue)
{
    auto left = ConvertToPx(padding.left, scaleProperty, selfSize.Width());
    auto right = ConvertToPx(padding.right, scaleProperty, selfSize.Width());
    auto top = ConvertToPx(padding.top, scaleProperty, selfSize.Height());
    auto bottom = ConvertToPx(padding.bottom, scaleProperty, selfSize.Height());
    if (left.has_value()) {
        paddingValue.left = left;
    }
    if (right.has_value()) {
        paddingValue.right = right;
    }
    if (top.has_value()) {
        paddingValue.top = top;
    }
    if (bottom.has_value()) {
        paddingValue.bottom = bottom;
    }
}

void AddPaddingToSize(const PaddingPropertyF& padding, SizeF& size)
{
    size.AddPadding(padding.left, padding.right, padding.top, padding.bottom);
}

void MinusPaddingToSize(const PaddingPropertyF& padding, SizeF& size)
{
    size.MinusPadding(padding.left, padding.right, padding.top, padding.bottom);
}
} // namespace OHOS::Ace::NG
