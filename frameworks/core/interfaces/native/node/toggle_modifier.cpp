/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/node/toggle_modifier.h"

#include "core/components/checkable/checkable_theme.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/toggle/toggle_model_ng.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG {
namespace {
constexpr uint32_t RESPONSE_REGION_STEP = 4;
constexpr uint32_t OFFSET_0 = 0;
constexpr uint32_t OFFSET_1 = 1;
constexpr uint32_t OFFSET_2 = 2;
constexpr uint32_t OFFSET_3 = 3;
constexpr uint32_t INDEX_DIMENSION_TOP_0 = 0;
constexpr uint32_t INDEX_DIMENSION_RIGHT_1 = 1;
constexpr uint32_t INDEX_DIMENSION_BOTTOM_2 = 2;
constexpr uint32_t INDEX_DIMENSION_LEFT_3 = 3;
constexpr uint32_t DIMENSION_STEP = 3;

bool SetToggleDimension(
    const double* dimensionArray, uint32_t offset, const size_t dataCount, std::optional<CalcDimension>& optDimension)
{
    CHECK_NULL_RETURN(dimensionArray, false);
    auto hasValue = dimensionArray[offset];
    if (!static_cast<bool>(hasValue)) {
        return false;
    }
    uint32_t valueIndex = offset + 1;
    uint32_t unitIndex = offset + 2;
    if (unitIndex >= dataCount) {
        return false;
    }
    auto value = dimensionArray[valueIndex];
    auto unit = dimensionArray[unitIndex];
    DimensionUnit unitValue = static_cast<DimensionUnit>(unit);
    CalcDimension dimensionValue = CalcDimension(value, unitValue);
    optDimension = dimensionValue;
    return true;
}
} // namespace
void SetToggleSelectedColor(NodeHandle node, uint32_t selectedColor)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ToggleModelNG::SetSelectedColor(frameNode, Color(selectedColor));
}

void ResetToggleSelectedColor(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<Color> selectedColor;
    ToggleModelNG::SetSelectedColor(frameNode, selectedColor);
}

void SetToggleSwitchPointColor(NodeHandle node, uint32_t switchPointColor)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ToggleModelNG::SetSwitchPointColor(frameNode, Color(switchPointColor));
}

void ResetToggleSwitchPointColor(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SwitchTheme>();
    Color color;
    if (theme) {
        color = theme->GetPointColor();
    }
    ToggleModelNG::SetSwitchPointColor(frameNode, Color(color));
}

void SetToggleHeight(NodeHandle node, double value, int32_t unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DimensionUnit unitValue = static_cast<DimensionUnit>(unit);
    CalcDimension dimensionValue = CalcDimension(value, unitValue);
    ToggleModelNG::SetHeight(frameNode, dimensionValue);
}

void ResetToggleHeight(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto switchTheme = GetTheme<SwitchTheme>();
    CHECK_NULL_VOID(switchTheme);
    auto defaultHeight = switchTheme->GetHeight();
    auto verticalPadding = switchTheme->GetHotZoneVerticalPadding();
    auto height = defaultHeight - verticalPadding * 2;
    CalcDimension value(height);
    ToggleModelNG::SetHeight(frameNode, value);
}

void SetToggleResponseRegion(NodeHandle node, const double* values, const int32_t* units, uint32_t length)
{
    CHECK_NULL_VOID(values);
    CHECK_NULL_VOID(units);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<DimensionRect> region;
    for (uint32_t i = 0; i + OFFSET_3 < length; i = i + RESPONSE_REGION_STEP) {
        CalcDimension xDimen = CalcDimension(values[i + OFFSET_0], static_cast<DimensionUnit>(units[i + OFFSET_0]));
        CalcDimension yDimen = CalcDimension(values[i + OFFSET_1], static_cast<DimensionUnit>(units[i + OFFSET_1]));
        CalcDimension widthDimen = CalcDimension(values[i + OFFSET_2], static_cast<DimensionUnit>(units[i + OFFSET_2]));
        CalcDimension heightDimen =
            CalcDimension(values[i + OFFSET_3], static_cast<DimensionUnit>(units[i + OFFSET_3]));
        DimensionOffset offsetDimen(xDimen, yDimen);
        DimensionRect dimenRect(widthDimen, heightDimen, offsetDimen);
        region.emplace_back(dimenRect);
    }
    ToggleModelNG::SetResponseRegion(frameNode, region);
}

void ResetToggleResponseRegion(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<DimensionRect> region;
    CalcDimension xDimen = CalcDimension(0.0, DimensionUnit::VP);
    CalcDimension yDimen = CalcDimension(0.0, DimensionUnit::VP);
    CalcDimension widthDimen = CalcDimension(1, DimensionUnit::PERCENT);
    CalcDimension heightDimen = CalcDimension(1, DimensionUnit::PERCENT);
    DimensionOffset offsetDimen(xDimen, yDimen);
    DimensionRect dimenRect(widthDimen, heightDimen, offsetDimen);
    region.emplace_back(dimenRect);
    ToggleModelNG::SetResponseRegion(frameNode, region);
}

void SetTogglePadding(NodeHandle node, const double* values, const uint32_t length)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(values);
    CalcLength topDimen;
    CalcLength rightDimen;
    CalcLength bottomDimen;
    CalcLength leftDimen;
    uint32_t step = DIMENSION_STEP;
    uint32_t topIndex = INDEX_DIMENSION_TOP_0;
    std::optional<CalcDimension> topOptional = std::nullopt;
    if (SetToggleDimension(values, topIndex, length, topOptional)) {
        topDimen = CalcLength(
            CalcDimension(topOptional.value().Value(), static_cast<DimensionUnit>(topOptional.value().Unit())));
    }
    uint32_t rightIndex = INDEX_DIMENSION_RIGHT_1 * step;
    std::optional<CalcDimension> rightOptional = std::nullopt;
    if (SetToggleDimension(values, rightIndex, length, rightOptional)) {
        rightDimen = CalcLength(
            CalcDimension(rightOptional.value().Value(), static_cast<DimensionUnit>(rightOptional.value().Unit())));
    }
    uint32_t bottomIndex = INDEX_DIMENSION_BOTTOM_2 * step;
    std::optional<CalcDimension> bottomOptional = std::nullopt;
    if (SetToggleDimension(values, bottomIndex, length, bottomOptional)) {
        bottomDimen = CalcLength(
            CalcDimension(bottomOptional.value().Value(), static_cast<DimensionUnit>(bottomOptional.value().Unit())));
    }
    uint32_t leftIndex = INDEX_DIMENSION_LEFT_3 * step;
    std::optional<CalcDimension> leftOptional = std::nullopt;
    if (SetToggleDimension(values, leftIndex, length, leftOptional)) {
        leftDimen = CalcLength(
            CalcDimension(leftOptional.value().Value(), static_cast<DimensionUnit>(leftOptional.value().Unit())));
    }
    NG::PaddingPropertyF oldPaddings;
    NG::PaddingProperty paddings;
    paddings.top = std::optional<CalcLength>(topDimen);
    paddings.bottom = std::optional<CalcLength>(bottomDimen);
    paddings.left = std::optional<CalcLength>(leftDimen);
    paddings.right = std::optional<CalcLength>(rightDimen);
    ToggleModelNG::SetPadding(frameNode, oldPaddings, paddings);
}

void ResetTogglePadding(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::PaddingPropertyF oldPaddings;
    NG::PaddingProperty paddings;
    paddings.top = std::optional<CalcLength>(CalcLength(0.0, DimensionUnit::VP));
    paddings.bottom = std::optional<CalcLength>(CalcLength(0.0, DimensionUnit::VP));
    paddings.left = std::optional<CalcLength>(CalcLength(0.0, DimensionUnit::VP));
    paddings.right = std::optional<CalcLength>(CalcLength(0.0, DimensionUnit::VP));
    ToggleModelNG::SetPadding(frameNode, oldPaddings, paddings);
}

void SetToggleBackgroundColor(NodeHandle node, uint32_t color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ToggleModelNG::SetBackgroundColor(frameNode, Color(color));
}

void ResetToggleBackgroundColor(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ToggleModelNG::SetBackgroundColor(frameNode, Color(Color::TRANSPARENT));
}

void SetToggleHoverEffect(NodeHandle node, int32_t hoverEffectValue)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    OHOS::Ace::HoverEffectType hoverEffect = OHOS::Ace::HoverEffectType::AUTO;
    hoverEffect = static_cast<OHOS::Ace::HoverEffectType>(hoverEffectValue);
    ToggleModelNG::SetHoverEffect(frameNode, hoverEffect);
}

void ResetToggleHoverEffect(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ToggleModelNG::SetHoverEffect(frameNode, OHOS::Ace::HoverEffectType::AUTO);
}

ArkUIToggleModifierAPI GetToggleModifier()
{
    static const ArkUIToggleModifierAPI modifier = { SetToggleSelectedColor, ResetToggleSelectedColor,
        SetToggleSwitchPointColor, ResetToggleSwitchPointColor, SetToggleHeight, ResetToggleHeight,
        SetToggleResponseRegion, ResetToggleResponseRegion, SetTogglePadding, ResetTogglePadding,
        SetToggleBackgroundColor, ResetToggleBackgroundColor, SetToggleHoverEffect, ResetToggleHoverEffect };

    return modifier;
}
} // namespace OHOS::Ace::NG