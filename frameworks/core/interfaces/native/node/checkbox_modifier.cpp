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
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KINDDimenge governing permissions and
 * limitations under the License.
 */
#include "core/interfaces/native/node/checkbox_modifier.h"

#include "core/pipeline/base/element_register.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/pattern/checkbox/checkbox_model_ng.h"
#include "frameworks/core/components/checkable/checkable_theme.h"

namespace OHOS::Ace::NG {
const DimensionUnit DEFAULT_UNIT = DimensionUnit::VP;
constexpr float CHECK_BOX_MARK_SIZE_INVALID_VALUE = -1.0f;

void SetSelect(ArkUINodeHandle node, ArkUI_Bool isSelected)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxModelNG::SetSelect(frameNode, isSelected);
}

void SetSelectedColor(ArkUINodeHandle node, uint32_t color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxModelNG::SetSelectedColor(frameNode, Color(color));
}

void SetUnSelectedColor(ArkUINodeHandle node, uint32_t color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxModelNG::SetUnSelectedColor(frameNode, Color(color));
}

void SetCheckboxWidth(ArkUINodeHandle node, ArkUI_Float32 value, int unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension width = Dimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit));
    CheckBoxModelNG::SetWidth(frameNode, width);
}

void SetCheckboxHeight(ArkUINodeHandle node, ArkUI_Float32 value, int unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension height = Dimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit));
    CheckBoxModelNG::SetHeight(frameNode, height);
}

void SetMark(ArkUINodeHandle node, uint32_t color, ArkUI_Float32 sizeValue, ArkUI_Float32 widthValue)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxModelNG::SetCheckMarkColor(frameNode, Color(color));

    Dimension size = Dimension(sizeValue, DEFAULT_UNIT);
    CheckBoxModelNG::SetCheckMarkSize(frameNode, size);

    Dimension width = Dimension(widthValue, DEFAULT_UNIT);
    CheckBoxModelNG::SetCheckMarkWidth(frameNode, width);
}
void ResetSelect(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxModelNG::SetSelect(frameNode, false);
}

void ResetSelectedColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto checkBoxTheme = themeManager->GetTheme<CheckboxTheme>();
    CheckBoxModelNG::SetSelectedColor(frameNode, checkBoxTheme->GetActiveColor());
}

void ResetUnSelectedColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto checkBoxTheme = themeManager->GetTheme<CheckboxTheme>();
    CheckBoxModelNG::SetUnSelectedColor(frameNode, checkBoxTheme->GetInactiveColor());
}

void ResetCheckboxWidth(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto checkBoxTheme = themeManager->GetTheme<CheckboxTheme>();
    CHECK_NULL_VOID(checkBoxTheme);
    auto defaultWidth = checkBoxTheme->GetDefaultWidth();
    auto horizontalPadding = checkBoxTheme->GetHotZoneHorizontalPadding();
    auto width = defaultWidth - horizontalPadding * 2;
    CheckBoxModelNG::SetWidth(frameNode, width);
}

void ResetCheckboxHeight(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto checkBoxTheme = themeManager->GetTheme<CheckboxTheme>();
    CHECK_NULL_VOID(checkBoxTheme);
    auto defaultHeight = checkBoxTheme->GetDefaultHeight();
    auto verticalPadding = checkBoxTheme->GetHotZoneVerticalPadding();
    auto height = defaultHeight - verticalPadding * 2;

    CheckBoxModelNG::SetHeight(frameNode, height);
}

void ResetMark(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto checkBoxTheme = themeManager->GetTheme<CheckboxTheme>();

    CheckBoxModelNG::SetCheckMarkColor(frameNode, checkBoxTheme->GetPointColor());
    CheckBoxModelNG::SetCheckMarkSize(frameNode, Dimension(CHECK_BOX_MARK_SIZE_INVALID_VALUE));
    CheckBoxModelNG::SetCheckMarkWidth(frameNode, checkBoxTheme->GetCheckStroke());
}

void SetCheckboxPadding(ArkUINodeHandle node, const ArkUI_Float32* values, const int* units, uint32_t length)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (length != 4) { // 4 : data length
        return;
    }
    CalcLength topDim;
    CalcLength rightDim;
    CalcLength bottomDim;
    CalcLength leftDim;
    topDim = CalcLength(values[0], static_cast<DimensionUnit>(units[0])); // 0: top Dimension
    rightDim = CalcLength(values[1], static_cast<DimensionUnit>(units[1])); // 1: right Dimension
    bottomDim = CalcLength(values[2], static_cast<DimensionUnit>(units[2])); // 2: bottom Dimension
    leftDim = CalcLength(values[3], static_cast<DimensionUnit>(units[3])); // 3: left Dimension
    NG::PaddingProperty padding;
    padding.top = std::optional<CalcLength>(topDim);
    padding.bottom = std::optional<CalcLength>(bottomDim);
    padding.left = std::optional<CalcLength>(leftDim);
    padding.right = std::optional<CalcLength>(rightDim);

    CheckBoxModelNG::SetPadding(frameNode, padding);
}

void SetCheckboxResponseRegion(ArkUINodeHandle node, const ArkUI_Float32* values, const int32_t* units, uint32_t length)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<DimensionRect> region;
    uint32_t ARRAY_LENGTH = 4; // 4: dimension length
    for (uint32_t i = 0; i < length / 4; i++) {
        CalcDimension xDimen =
            CalcDimension(values[i * ARRAY_LENGTH], static_cast<DimensionUnit>(units[i * ARRAY_LENGTH]));
        CalcDimension yDimen =
            CalcDimension(values[i * ARRAY_LENGTH + 1], static_cast<DimensionUnit>(units[i * ARRAY_LENGTH + 1]));
        CalcDimension widthDimen = CalcDimension(
            values[i * ARRAY_LENGTH + 2], static_cast<DimensionUnit>(units[i * ARRAY_LENGTH + 2])); // 2: width value
        CalcDimension heightDimen = CalcDimension(
            values[i * ARRAY_LENGTH + 3], static_cast<DimensionUnit>(units[i * ARRAY_LENGTH + 3])); // 3: height value
        DimensionOffset offsetDimen(xDimen, yDimen);
        DimensionRect dimenRect(widthDimen, heightDimen, offsetDimen);
        region.emplace_back(dimenRect);
    }
    CheckBoxModelNG::SetResponseRegion(frameNode, region);
}

void ResetCheckboxPadding(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::PaddingProperty padding;
    padding.top = std::optional<CalcLength>(CalcLength(0.0, DimensionUnit::VP));
    padding.bottom = std::optional<CalcLength>(CalcLength(0.0, DimensionUnit::VP));
    padding.left = std::optional<CalcLength>(CalcLength(0.0, DimensionUnit::VP));
    padding.right = std::optional<CalcLength>(CalcLength(0.0, DimensionUnit::VP));

    CheckBoxModelNG::SetPadding(frameNode, padding);
}

void ResetCheckboxResponseRegion(ArkUINodeHandle node) {}

namespace NodeModifier {
const ArkUICheckboxModifier* GetCheckboxModifier()
{
    static const ArkUICheckboxModifier modifier = { SetSelect, SetSelectedColor, SetUnSelectedColor,
        SetCheckboxWidth, SetCheckboxHeight, SetMark, SetCheckboxPadding, SetCheckboxResponseRegion, ResetSelect,
        ResetSelectedColor, ResetUnSelectedColor, ResetCheckboxWidth, ResetCheckboxHeight, ResetMark,
        ResetCheckboxPadding, ResetCheckboxResponseRegion };

    return &modifier;
}
}
}