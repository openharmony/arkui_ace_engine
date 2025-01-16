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
#include "core/interfaces/native/node/node_checkbox_modifier.h"

#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/checkbox/checkbox_model_ng.h"
#include "frameworks/core/components/checkable/checkable_theme.h"

namespace OHOS::Ace::NG {
constexpr float CHECK_BOX_MARK_SIZE_INVALID_VALUE = -1.0f;
const uint32_t ERROR_UINT_CODE = -1;
const float ERROR_FLOAT_CODE = -1.0f;
const int32_t ERROR_INT_CODE = -1;
static std::string nameValue;

void SetSelect(ArkUINodeHandle node, ArkUI_Bool isSelected)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxModelNG::SetSelect(frameNode, static_cast<bool>(isSelected));
}

void SetSelectedColor(ArkUINodeHandle node, ArkUI_Uint32 color)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxModelNG::SetSelectedColor(frameNode, Color(color));
}

void SetUnSelectedColor(ArkUINodeHandle node, ArkUI_Uint32 color)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxModelNG::SetUnSelectedColor(frameNode, Color(color));
}

void SetCheckboxWidth(ArkUINodeHandle node, float value, int unit)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension width =
        Dimension(static_cast<double>(value), static_cast<OHOS::Ace::DimensionUnit>(unit));
    CheckBoxModelNG::SetWidth(frameNode, width);
}

void SetCheckboxHeight(ArkUINodeHandle node, float value, int unit)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension height =
        Dimension(static_cast<double>(value), static_cast<OHOS::Ace::DimensionUnit>(unit));
    CheckBoxModelNG::SetHeight(frameNode, height);
}

void SetMark(ArkUINodeHandle node, uint32_t color, float sizeValue, int sizeUnit, float widthValue, int widthUnit)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxModelNG::SetCheckMarkColor(frameNode, Color(color));

    Dimension size = Dimension(static_cast<double>(sizeValue), static_cast<OHOS::Ace::DimensionUnit>(sizeUnit));
    CheckBoxModelNG::SetCheckMarkSize(frameNode, size);

    Dimension width = Dimension(static_cast<double>(widthValue), static_cast<OHOS::Ace::DimensionUnit>(widthUnit));
    CheckBoxModelNG::SetCheckMarkWidth(frameNode, width);
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

void ResetSelect(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxModelNG::SetSelect(frameNode, false);
}

void ResetSelectedColor(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);

    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto checkBoxTheme = pipelineContext->GetTheme<CheckboxTheme>();
    CheckBoxModelNG::SetSelectedColor(frameNode, checkBoxTheme->GetActiveColor());
}

void ResetUnSelectedColor(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto checkBoxTheme = pipelineContext->GetTheme<CheckboxTheme>();
    CheckBoxModelNG::SetUnSelectedColor(frameNode, checkBoxTheme->GetInactiveColor());
}

void ResetCheckboxWidth(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto checkBoxTheme = pipelineContext->GetTheme<CheckboxTheme>();
    CHECK_NULL_VOID(checkBoxTheme);
    auto defaultWidth = checkBoxTheme->GetDefaultWidth();
    auto horizontalPadding = checkBoxTheme->GetHotZoneHorizontalPadding();
    auto width = defaultWidth - horizontalPadding * 2;
    CheckBoxModelNG::SetWidth(frameNode, width);
}

void ResetCheckboxHeight(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto checkBoxTheme = pipelineContext->GetTheme<CheckboxTheme>();
    CHECK_NULL_VOID(checkBoxTheme);
    auto defaultHeight = checkBoxTheme->GetDefaultHeight();
    auto verticalPadding = checkBoxTheme->GetHotZoneVerticalPadding();
    auto height = defaultHeight - verticalPadding * 2;

    CheckBoxModelNG::SetHeight(frameNode, height);
}

void ResetMark(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipelineContext = frameNode->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto checkBoxTheme = pipelineContext->GetTheme<CheckboxTheme>();

    CheckBoxModelNG::SetCheckMarkColor(frameNode, checkBoxTheme->GetPointColor());
    CheckBoxModelNG::SetCheckMarkSize(
        frameNode, Dimension(CHECK_BOX_MARK_SIZE_INVALID_VALUE));
    CheckBoxModelNG::SetCheckMarkWidth(frameNode, checkBoxTheme->GetCheckStroke());
}

void SetCheckboxShape(ArkUINodeHandle node, ArkUI_Int32 value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxModelNG::SetCheckboxStyle(frameNode, static_cast<CheckBoxStyle>(value));
}

void ResetCheckboxShape(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxModelNG::SetCheckboxStyle(frameNode, CheckBoxStyle::CIRCULAR_STYLE);
}

ArkUI_Bool GetSelect(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Bool>(CheckBoxModelNG::GetSelect(frameNode));
}

ArkUI_Uint32 GetSelectedColor(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_UINT_CODE);
    return CheckBoxModelNG::GetSelectedColor(frameNode).GetValue();
}

ArkUI_Uint32 GetUnSelectedColor(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_UINT_CODE);
    return CheckBoxModelNG::GetUnSelectedColor(frameNode).GetValue();
}

ArkUI_Uint32 GetCheckMarkColor(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_UINT_CODE);
    return CheckBoxModelNG::GetCheckMarkColor(frameNode).GetValue();
}

ArkUI_Float64 GetCheckMarkSize(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return CheckBoxModelNG::GetCheckMarkSize(frameNode).Value();
}

ArkUI_Float64 GetCheckMarkWidth(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return CheckBoxModelNG::GetCheckMarkWidth(frameNode).Value();
}

ArkUI_Int32 GetCheckboxShape(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Int32>(CheckBoxModelNG::GetCheckboxStyle(frameNode));
}

void SetCheckboxName(ArkUINodeHandle node, ArkUI_CharPtr name)
{
    CHECK_NULL_VOID(name);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxModelNG::SetCheckboxName(frameNode, std::string(name));
}

void SetCheckboxGroup(ArkUINodeHandle node, ArkUI_CharPtr group)
{
    CHECK_NULL_VOID(group);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxModelNG::SetCheckboxGroup(frameNode, std::string(group));
}

ArkUI_CharPtr GetCheckboxName(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, "");
    nameValue = CheckBoxModelNG::GetCheckboxName(frameNode);
    return nameValue.c_str();
}

ArkUI_CharPtr GetCheckboxGroup(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, "");
    nameValue = CheckBoxModelNG::GetCheckboxGroup(frameNode);
    return nameValue.c_str();
}

namespace NodeModifier {
const ArkUICheckboxModifier *GetCheckboxModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUICheckboxModifier modifier = {
        .setSelect = SetSelect,
        .setSelectedColor = SetSelectedColor,
        .setUnSelectedColor = SetUnSelectedColor,
        .setCheckboxWidth = SetCheckboxWidth,
        .setCheckboxHeight = SetCheckboxHeight,
        .setMark = SetMark,
        .setCheckboxPadding = SetCheckboxPadding,
        .setCheckboxResponseRegion = SetCheckboxResponseRegion,
        .resetSelect = ResetSelect,
        .resetSelectedColor = ResetSelectedColor,
        .resetUnSelectedColor = ResetUnSelectedColor,
        .resetCheckboxWidth = ResetCheckboxWidth,
        .resetCheckboxHeight = ResetCheckboxHeight,
        .resetMark = ResetMark,
        .setCheckboxShape = SetCheckboxShape,
        .resetCheckboxShape = ResetCheckboxShape,
        .resetCheckboxPadding = ResetCheckboxPadding,
        .resetCheckboxResponseRegion = ResetCheckboxResponseRegion,
        .getSelect = GetSelect,
        .getSelectedColor = GetSelectedColor,
        .getUnSelectedColor = GetUnSelectedColor,
        .getCheckMarkColor = GetCheckMarkColor,
        .getCheckMarkSize = GetCheckMarkSize,
        .getCheckMarkWidth = GetCheckMarkWidth,
        .getCheckboxShape = GetCheckboxShape,
        .setCheckboxName = SetCheckboxName,
        .setCheckboxGroup = SetCheckboxGroup,
        .getCheckboxName = GetCheckboxName,
        .getCheckboxGroup = GetCheckboxGroup,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

const CJUICheckboxModifier* GetCJUICheckboxModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUICheckboxModifier modifier = {
        .setSelect = SetSelect,
        .setSelectedColor = SetSelectedColor,
        .setUnSelectedColor = SetUnSelectedColor,
        .setCheckboxWidth = SetCheckboxWidth,
        .setCheckboxHeight = SetCheckboxHeight,
        .setMark = SetMark,
        .setCheckboxPadding = SetCheckboxPadding,
        .setCheckboxResponseRegion = SetCheckboxResponseRegion,
        .resetSelect = ResetSelect,
        .resetSelectedColor = ResetSelectedColor,
        .resetUnSelectedColor = ResetUnSelectedColor,
        .resetCheckboxWidth = ResetCheckboxWidth,
        .resetCheckboxHeight = ResetCheckboxHeight,
        .resetMark = ResetMark,
        .setCheckboxShape = SetCheckboxShape,
        .resetCheckboxShape = ResetCheckboxShape,
        .resetCheckboxPadding = ResetCheckboxPadding,
        .resetCheckboxResponseRegion = ResetCheckboxResponseRegion,
        .getSelect = GetSelect,
        .getSelectedColor = GetSelectedColor,
        .getUnSelectedColor = GetUnSelectedColor,
        .getCheckMarkColor = GetCheckMarkColor,
        .getCheckMarkSize = GetCheckMarkSize,
        .getCheckMarkWidth = GetCheckMarkWidth,
        .getCheckboxShape = GetCheckboxShape,
        .setCheckboxName = SetCheckboxName,
        .setCheckboxGroup = SetCheckboxGroup,
        .getCheckboxName = GetCheckboxName,
        .getCheckboxGroup = GetCheckboxGroup,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

void SetCheckboxChange(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [node, extraParam](const bool value) {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_CHECKBOX_CHANGE;
        event.componentAsyncEvent.data[0].i32 = static_cast<int>(value);
        SendArkUISyncEvent(&event);
    };
    CheckBoxModelNG::SetOnChange(frameNode, std::move(onEvent));
}

} // namespace NodeModifier
} // namespace OHOS::Ace::NG
