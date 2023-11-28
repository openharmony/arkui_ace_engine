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
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_slider_modifier.h"
#include "core/components_ng/pattern/slider/slider_model_ng.h"

#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components/slider/slider_theme.h"
#include "core/pipeline/base/element_register.h"
#include "core/components_ng/pattern/slider/slider_model_ng.h"

namespace OHOS::Ace::NG {
void SetShowTips(NodeHandle node, bool isShow, const char* value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<std::string> content = std::optional(value);
    SliderModelNG::SetShowTips(frameNode, isShow, content);
}
void ResetShowTips(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::ResetShowTips(frameNode);
}
void SetSliderStepSize(NodeHandle node, const float value, const int unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension size = Dimension(value, static_cast<DimensionUnit>(unit));
    SliderModelNG::SetStepSize(frameNode, size);
}
void ResetSliderStepSize(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto theme = themeManager->GetTheme<SliderTheme>();
    Dimension stepSize = theme->GetMarkerSize();
    SliderModelNG::SetStepSize(frameNode, stepSize);
}
void SetBlockSize(NodeHandle node, float widthVal, int widthUnit, float heightVal, int heightUnit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension width = Dimension(widthVal, static_cast<DimensionUnit>(widthUnit));
    Dimension height = Dimension(heightVal, static_cast<DimensionUnit>(heightUnit));
    SliderModelNG::SetBlockSize(frameNode, width, height);
}
void ResetBlockSize(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::ResetBlockSize(frameNode);
}
void SetTrackBorderRadius(NodeHandle node, const float value, const int unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension radius = Dimension(value, static_cast<DimensionUnit>(unit));
    SliderModelNG::SetTrackBorderRadius(frameNode, radius);
}
void ResetTrackBorderRadius(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::ResetTrackBorderRadius(frameNode);
}
void SetStepColor(NodeHandle node, uint32_t color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetStepColor(frameNode, Color(color));
}
void ResetStepColor(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::ResetStepColor(frameNode);
}
void SetBlockBorderColor(NodeHandle node, uint32_t color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetBlockBorderColor(frameNode, Color(color));
}
void ResetBlockBorderColor(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::ResetBlockBorderColor(frameNode);
}
void SetBlockBorderWidth(NodeHandle node, const float value, const int unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension width = Dimension(value, static_cast<DimensionUnit>(unit));
    SliderModelNG::SetBlockBorderWidth(frameNode, width);
}
void ResetBlockBorderWidth(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::ResetBlockBorderWidth(frameNode);
}
void SetBlockColor(NodeHandle node, uint32_t color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetBlockColor(frameNode, Color(color));
}
void ResetBlockColor(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::ResetBlockColor(frameNode);
}
void SetTrackBackgroundColor(NodeHandle node, uint32_t color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetTrackBackgroundColor(frameNode, Color(color));
}
void ResetTrackBackgroundColor(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::ResetTrackBackgroundColor(frameNode);
}
void SetSelectColor(NodeHandle node, uint32_t color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetSelectColor(frameNode, Color(color));
}
void ResetSelectColor(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::ResetSelectColor(frameNode);
}
void SetShowSteps(NodeHandle node, bool showSteps)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::SetShowSteps(frameNode, showSteps);
}
void ResetShowSteps(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::ResetShowSteps(frameNode);
}
void SetThickness(NodeHandle node, const float value, const int unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension thickness = Dimension(value, static_cast<DimensionUnit>(unit));
    SliderModelNG::SetThickness(frameNode, thickness);
}
void ResetThickness(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SliderModelNG::ResetThickness(frameNode);
}
ArkUISliderModifierAPI GetSliderModifier()
{
    static const ArkUISliderModifierAPI modifier = { SetShowTips, ResetShowTips, SetSliderStepSize,
        ResetSliderStepSize, SetBlockSize, ResetBlockSize, SetTrackBorderRadius, ResetTrackBorderRadius,
        SetStepColor, ResetStepColor, SetBlockBorderColor, ResetBlockBorderColor,
        SetBlockBorderWidth, ResetBlockBorderWidth, SetBlockColor, ResetBlockColor, SetTrackBackgroundColor,
        ResetTrackBackgroundColor, SetSelectColor, ResetSelectColor, SetShowSteps, ResetShowSteps,
        SetThickness, ResetThickness };

    return modifier;
}
} // namespace OHOS::Ace::NG