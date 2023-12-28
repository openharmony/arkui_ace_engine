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

void SetSelect(NodeHandle node, bool isSelected)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxModelNG::SetSelect(frameNode, isSelected);
}

void SetSelectedColor(NodeHandle node, uint32_t color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxModelNG::SetSelectedColor(frameNode, Color(color));
}

void SetUnSelectedColor(NodeHandle node, uint32_t color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxModelNG::SetUnSelectedColor(frameNode, Color(color));
}

void SetCheckboxWidth(NodeHandle node, double value, int unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension width = Dimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit));
    CheckBoxModelNG::SetWidth(frameNode, width);
}

void SetCheckboxHeight(NodeHandle node, double value, int unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension height = Dimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit));
    CheckBoxModelNG::SetHeight(frameNode, height);
}

void SetMark(NodeHandle node, uint32_t color, double sizeValue, double widthValue)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxModelNG::SetCheckMarkColor(frameNode, Color(color));

    Dimension size = Dimension(sizeValue, DEFAULT_UNIT);
    CheckBoxModelNG::SetCheckMarkSize(frameNode, size);

    Dimension width = Dimension(widthValue, DEFAULT_UNIT);
    CheckBoxModelNG::SetCheckMarkWidth(frameNode, width);
}
void ResetSelect(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CheckBoxModelNG::SetSelect(frameNode, false);
}

void ResetSelectedColor(NodeHandle node)
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

void ResetUnSelectedColor(NodeHandle node)
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

void ResetCheckboxWidth(NodeHandle node)
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

void ResetCheckboxHeight(NodeHandle node)
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

void ResetMark(NodeHandle node)
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

ArkUICheckboxModifierAPI GetCheckboxModifier()
{
    static const ArkUICheckboxModifierAPI modifier = { SetSelect, SetSelectedColor, SetUnSelectedColor,
        SetCheckboxWidth, SetCheckboxHeight, SetMark, ResetSelect, ResetSelectedColor, ResetUnSelectedColor,
        ResetCheckboxWidth, ResetCheckboxHeight, ResetMark };

    return modifier;
}
}