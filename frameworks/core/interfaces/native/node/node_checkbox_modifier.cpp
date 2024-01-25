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

#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/checkbox/checkbox_model_ng.h"
#include "core/pipeline/base/element_register.h"
#include "frameworks/core/components/checkable/checkable_theme.h"

namespace OHOS::Ace::NG {
const DimensionUnit DEFAULT_UNIT = DimensionUnit::VP;
constexpr float CHECK_BOX_MARK_SIZE_INVALID_VALUE = -1.0f;

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

void SetMark(ArkUINodeHandle node, uint32_t color, float sizeValue,
             float widthValue)
{
  auto *frameNode = reinterpret_cast<FrameNode *>(node);
  CHECK_NULL_VOID(frameNode);
  CheckBoxModelNG::SetCheckMarkColor(frameNode, Color(color));

  Dimension size = Dimension(static_cast<double>(sizeValue), DEFAULT_UNIT);
  CheckBoxModelNG::SetCheckMarkSize(frameNode, size);

  Dimension width = Dimension(static_cast<double>(widthValue), DEFAULT_UNIT);
  CheckBoxModelNG::SetCheckMarkWidth(frameNode, width);
}
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

  auto pipelineContext = PipelineBase::GetCurrentContext();
  CHECK_NULL_VOID(pipelineContext);
  auto checkBoxTheme = pipelineContext->GetTheme<CheckboxTheme>();
  CheckBoxModelNG::SetSelectedColor(frameNode, checkBoxTheme->GetActiveColor());
}

void ResetUnSelectedColor(ArkUINodeHandle node)
{
  auto *frameNode = reinterpret_cast<FrameNode *>(node);
  CHECK_NULL_VOID(frameNode);
  auto pipelineContext = PipelineBase::GetCurrentContext();
  CHECK_NULL_VOID(pipelineContext);
  auto checkBoxTheme = pipelineContext->GetTheme<CheckboxTheme>();
  CheckBoxModelNG::SetUnSelectedColor(frameNode,
                                      checkBoxTheme->GetInactiveColor());
}

void ResetCheckboxWidth(ArkUINodeHandle node)
{
  auto *frameNode = reinterpret_cast<FrameNode *>(node);
  CHECK_NULL_VOID(frameNode);
  auto pipelineContext = PipelineBase::GetCurrentContext();
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
  auto pipelineContext = PipelineBase::GetCurrentContext();
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
  auto pipelineContext = PipelineBase::GetCurrentContext();
  CHECK_NULL_VOID(pipelineContext);
  auto checkBoxTheme = pipelineContext->GetTheme<CheckboxTheme>();

  CheckBoxModelNG::SetCheckMarkColor(frameNode, checkBoxTheme->GetPointColor());
  CheckBoxModelNG::SetCheckMarkSize(
      frameNode, Dimension(CHECK_BOX_MARK_SIZE_INVALID_VALUE));
  CheckBoxModelNG::SetCheckMarkWidth(frameNode,
                                     checkBoxTheme->GetCheckStroke());
}

namespace NodeModifier
{
const ArkUICheckboxModifier *GetCheckboxModifier() 
{
  static const ArkUICheckboxModifier modifier = {SetSelect,
                                                 SetSelectedColor,
                                                 SetUnSelectedColor,
                                                 SetCheckboxWidth,
                                                 SetCheckboxHeight,
                                                 SetMark,
                                                 ResetSelect,
                                                 ResetSelectedColor,
                                                 ResetUnSelectedColor,
                                                 ResetCheckboxWidth,
                                                 ResetCheckboxHeight,
                                                 ResetMark,};

  return &modifier;
}
} // namespace NodeModifier

} // namespace OHOS::Ace::NG
