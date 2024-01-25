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
#include "core/interfaces/native/node/node_slider_modifier.h"

#include "core/components_ng/pattern/slider/slider_model_ng.h"
#include "core/components/common/layout/constants.h"
#include "core/components/slider/slider_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG {
const bool DEFAULT_SHOW_STEPS = false;
const bool DEFAULT_SHOW_TIPS = false;
void SetShowTips(ArkUINodeHandle node, ArkUI_Bool isShow, const char *value)
{
  auto *frameNode = reinterpret_cast<FrameNode *>(node);
  CHECK_NULL_VOID(frameNode);
  std::optional<std::string> content;

  if (value == nullptr) {
    content = std::nullopt;
  } else {
    content = std::string(value);
  }

  SliderModelNG::SetShowTips(frameNode, static_cast<bool>(isShow), content);
}

void ResetShowTips(ArkUINodeHandle node)
{
  auto *frameNode = reinterpret_cast<FrameNode *>(node);
  CHECK_NULL_VOID(frameNode);
  std::optional<std::string> content;
  SliderModelNG::SetShowTips(frameNode, DEFAULT_SHOW_TIPS, content);
}

void SetSliderStepSize(ArkUINodeHandle node, ArkUI_Float32 value, int unit)
{
  auto *frameNode = reinterpret_cast<FrameNode *>(node);
  CHECK_NULL_VOID(frameNode);
  Dimension size =
      Dimension(static_cast<double>(value), static_cast<OHOS::Ace::DimensionUnit>(unit));
  SliderModelNG::SetStepSize(frameNode, size);
}

void ResetSliderStepSize(ArkUINodeHandle node)
{
  auto *frameNode = reinterpret_cast<FrameNode *>(node);
  CHECK_NULL_VOID(frameNode);

  auto pipelineContext = PipelineBase::GetCurrentContext();
  CHECK_NULL_VOID(pipelineContext);
  auto theme = pipelineContext->GetTheme<SliderTheme>();

  Dimension stepSize = theme->GetMarkerSize();
  SliderModelNG::SetStepSize(frameNode, stepSize);
}

void SetBlockSize(ArkUINodeHandle node, ArkUI_Float32 widthVal, int widthUnit,
                  ArkUI_Float32 heightVal, int heightUnit)
{
  auto *frameNode = reinterpret_cast<FrameNode *>(node);
  CHECK_NULL_VOID(frameNode);
  Dimension blockWidth =
      Dimension(static_cast<double>(widthVal), static_cast<OHOS::Ace::DimensionUnit>(widthUnit));
  Dimension blockHeight =
      Dimension(static_cast<double>(heightVal), static_cast<OHOS::Ace::DimensionUnit>(heightUnit));

  if (LessNotEqual(blockWidth.Value(), 0.0)) {
    blockWidth.SetValue(0.0);
  }
  if (LessNotEqual(blockHeight.Value(), 0.0)) {
    blockHeight.SetValue(0.0);
  }

  SliderModelNG::SetBlockSize(frameNode, blockWidth, blockHeight);
}

void ResetBlockSize(ArkUINodeHandle node)
{
  auto *frameNode = reinterpret_cast<FrameNode *>(node);
  CHECK_NULL_VOID(frameNode);
  SliderModelNG::ResetBlockSize(frameNode);
}

void SetTrackBorderRadius(ArkUINodeHandle node, float value, int unit)
{
  auto *frameNode = reinterpret_cast<FrameNode *>(node);
  CHECK_NULL_VOID(frameNode);
  Dimension radius =
      Dimension(static_cast<double>(value), static_cast<OHOS::Ace::DimensionUnit>(unit));
  SliderModelNG::SetTrackBorderRadius(frameNode, radius);
}

void ResetTrackBorderRadius(ArkUINodeHandle node)
{
  auto *frameNode = reinterpret_cast<FrameNode *>(node);
  CHECK_NULL_VOID(frameNode);
  SliderModelNG::ResetTrackBorderRadius(frameNode);
}

void SetStepColor(ArkUINodeHandle node, uint32_t color)
{
  auto *frameNode = reinterpret_cast<FrameNode *>(node);
  CHECK_NULL_VOID(frameNode);
  SliderModelNG::SetStepColor(frameNode, Color(color));
}

void ResetStepColor(ArkUINodeHandle node)
{
  auto *frameNode = reinterpret_cast<FrameNode *>(node);
  CHECK_NULL_VOID(frameNode);
  SliderModelNG::ResetStepColor(frameNode);
}

void SetBlockBorderColor(ArkUINodeHandle node, uint32_t color)
{
  auto *frameNode = reinterpret_cast<FrameNode *>(node);
  CHECK_NULL_VOID(frameNode);
  SliderModelNG::SetBlockBorderColor(frameNode, Color(color));
}

void ResetBlockBorderColor(ArkUINodeHandle node)
{
  auto *frameNode = reinterpret_cast<FrameNode *>(node);
  CHECK_NULL_VOID(frameNode);
  SliderModelNG::ResetBlockBorderColor(frameNode);
}

void SetBlockBorderWidth(ArkUINodeHandle node, ArkUI_Float32 value, int unit)
{
  auto *frameNode = reinterpret_cast<FrameNode *>(node);
  CHECK_NULL_VOID(frameNode);
  Dimension width =
      Dimension(static_cast<double>(value), static_cast<OHOS::Ace::DimensionUnit>(unit));
  SliderModelNG::SetBlockBorderWidth(frameNode, width);
}

void ResetBlockBorderWidth(ArkUINodeHandle node)
{
  auto *frameNode = reinterpret_cast<FrameNode *>(node);
  CHECK_NULL_VOID(frameNode);
  SliderModelNG::ResetBlockBorderWidth(frameNode);
}

void SetBlockColor(ArkUINodeHandle node, uint32_t color)
{
  auto *frameNode = reinterpret_cast<FrameNode *>(node);
  CHECK_NULL_VOID(frameNode);
  SliderModelNG::SetBlockColor(frameNode, Color(color));
}

void ResetBlockColor(ArkUINodeHandle node)
{
  auto *frameNode = reinterpret_cast<FrameNode *>(node);
  CHECK_NULL_VOID(frameNode);
  SliderModelNG::ResetBlockColor(frameNode);
}

void SetTrackBackgroundColor(ArkUINodeHandle node, uint32_t color)
{
  auto *frameNode = reinterpret_cast<FrameNode *>(node);
  CHECK_NULL_VOID(frameNode);
  SliderModelNG::SetTrackBackgroundColor(frameNode, Color(color));
}

void ResetTrackBackgroundColor(ArkUINodeHandle node)
{
  auto *frameNode = reinterpret_cast<FrameNode *>(node);
  CHECK_NULL_VOID(frameNode);
  auto pipelineContext = PipelineBase::GetCurrentContext();
  CHECK_NULL_VOID(pipelineContext);
  auto theme = pipelineContext->GetTheme<SliderTheme>();
  CHECK_NULL_VOID(theme);

  SliderModelNG::SetTrackBackgroundColor(frameNode, theme->GetTrackBgColor());
}

void SetSelectColor(ArkUINodeHandle node, uint32_t color)
{
  auto *frameNode = reinterpret_cast<FrameNode *>(node);
  CHECK_NULL_VOID(frameNode);
  SliderModelNG::SetSelectColor(frameNode, Color(color));
}

void ResetSelectColor(ArkUINodeHandle node)
{
  auto *frameNode = reinterpret_cast<FrameNode *>(node);
  CHECK_NULL_VOID(frameNode);
  auto pipelineContext = PipelineBase::GetCurrentContext();
  CHECK_NULL_VOID(pipelineContext);
  auto theme = pipelineContext->GetTheme<SliderTheme>();
  CHECK_NULL_VOID(theme);
  SliderModelNG::SetSelectColor(frameNode, theme->GetTrackSelectedColor());
}

void SetShowSteps(ArkUINodeHandle node, int showSteps)
{
  auto *frameNode = reinterpret_cast<FrameNode *>(node);
  CHECK_NULL_VOID(frameNode);
  SliderModelNG::SetShowSteps(frameNode, static_cast<bool>(showSteps));
}

void ResetShowSteps(ArkUINodeHandle node)
{
  auto *frameNode = reinterpret_cast<FrameNode *>(node);
  CHECK_NULL_VOID(frameNode);
  SliderModelNG::SetShowSteps(frameNode, DEFAULT_SHOW_STEPS);
}

void SetThickness(ArkUINodeHandle node, ArkUI_Float32 value, int unit)
{
  auto *frameNode = reinterpret_cast<FrameNode *>(node);
  CHECK_NULL_VOID(frameNode);
  Dimension thickness =
      Dimension(static_cast<double>(value), static_cast<OHOS::Ace::DimensionUnit>(unit));
  SliderModelNG::SetThickness(frameNode, thickness);
}

void ResetThickness(ArkUINodeHandle node)
{
  auto *frameNode = reinterpret_cast<FrameNode *>(node);
  CHECK_NULL_VOID(frameNode);
  SliderModelNG::SetThickness(frameNode, CalcDimension(0.0));
}

namespace NodeModifier
{
const ArkUISliderModifier *GetSliderModifier()
{
  static const ArkUISliderModifier modifier = { SetShowTips,
                                               ResetShowTips,
                                               SetSliderStepSize,
                                               ResetSliderStepSize,
                                               SetBlockSize,
                                               ResetBlockSize,
                                               SetTrackBorderRadius,
                                               ResetTrackBorderRadius,
                                               SetStepColor,
                                               ResetStepColor,
                                               SetBlockBorderColor,
                                               ResetBlockBorderColor,
                                               SetBlockBorderWidth,
                                               ResetBlockBorderWidth,
                                               SetBlockColor,
                                               ResetBlockColor,
                                               SetTrackBackgroundColor,
                                               ResetTrackBackgroundColor,
                                               SetSelectColor,
                                               ResetSelectColor,
                                               SetShowSteps,
                                               ResetShowSteps,
                                               SetThickness,
                                               ResetThickness };

  return &modifier;
}

} // namespace NodeModifier
} // namespace OHOS::Ace::NG