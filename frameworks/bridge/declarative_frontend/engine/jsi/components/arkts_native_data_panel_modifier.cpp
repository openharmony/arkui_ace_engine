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
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_data_panel_modifier.h"

#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/data_panel/data_panel_model_ng.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG {
namespace {
constexpr bool IS_CLOSE_EFFECT = false;
constexpr double DEFAULT_STROKE_WIDTH = 24.0;
constexpr double DEFAULT_RADIUS = 5.0;
constexpr double DEFAULT_OFFSET_X = 5.0;
constexpr double DEFAULT_OFFSET_Y = 5.0;
const std::string DEFAULT_TRACK_BACKGROUND = "#08182431";
}
void SetCloseEffect(NodeHandle node, bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DataPanelModelNG::SetCloseEffect(frameNode, value);
}

void ResetCloseEffect(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DataPanelModelNG::SetCloseEffect(frameNode, IS_CLOSE_EFFECT);
}

void SetDataPanelTrackBackgroundColor(NodeHandle node, uint32_t value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DataPanelModelNG::SetTrackBackground(frameNode, Color(value));
}

void ResetDataPanelTrackBackgroundColor(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DataPanelModelNG::SetTrackBackground(frameNode, Color::FromString(DEFAULT_TRACK_BACKGROUND));
}

void SetDataPanelStrokeWidth(NodeHandle node, double value, int32_t unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    DataPanelModelNG::SetStrokeWidth(frameNode, Dimension(value, unitEnum));
}

void ResetDataPanelStrokeWidth(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DataPanelModelNG::SetStrokeWidth(frameNode, Dimension(DEFAULT_STROKE_WIDTH, DimensionUnit::VP));
}

void ConvertThemeColor(std::vector<OHOS::Ace::NG::Gradient>& colors)
{
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    auto themeManager = pipelineContext->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    RefPtr<DataPanelTheme> theme = themeManager->GetTheme<DataPanelTheme>();
    auto themeColors = theme->GetColorsArray();
    for (const auto& item : themeColors) {
        OHOS::Ace::NG::Gradient gradient;
        OHOS::Ace::NG::GradientColor gradientColorStart;
        gradientColorStart.SetLinearColor(LinearColor(item.first));
        gradientColorStart.SetDimension(Dimension(0.0));
        gradient.AddColor(gradientColorStart);
        OHOS::Ace::NG::GradientColor gradientColorEnd;
        gradientColorEnd.SetLinearColor(LinearColor(item.second));
        gradientColorEnd.SetDimension(Dimension(1.0));
        gradient.AddColor(gradientColorEnd);
        colors.emplace_back(gradient);
    }
}

void SetValueColors(NodeHandle node, const struct ArkUIGradientType* gradient)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<OHOS::Ace::NG::Gradient> shadowColors(gradient->length);
    uint32_t pos = 0;
    for (uint32_t i = 0; i < gradient->length; i++) {
        if (gradient->gradientLength[i] == 0) {
            shadowColors.clear();
            ConvertThemeColor(shadowColors);
            break;
        }
        OHOS::Ace::NG::Gradient tempGradient;
        for (uint32_t j = 0; j < gradient->gradientLength[i]; j++, pos++) {
            OHOS::Ace::NG::GradientColor gradientColor;
            gradientColor.SetLinearColor(LinearColor(Color(gradient->color[pos])));
            gradientColor.SetDimension(
                Dimension(gradient->offset[pos].number, static_cast<DimensionUnit>(gradient->offset[pos].unit)));
            tempGradient.AddColor(gradientColor);
        }
        shadowColors.at(i) = tempGradient;
    }
    DataPanelModelNG::SetValueColors(frameNode, shadowColors);
}

void ResetValueColors(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<OHOS::Ace::NG::Gradient> colors;
    ConvertThemeColor(colors);
    DataPanelModelNG::SetValueColors(frameNode, colors);
}

void SetTrackShadow(
    NodeHandle node, const struct ArkUIGradientType* gradient, double radius, double offsetX, double offsetY)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    OHOS::Ace::NG::DataPanelShadow shadow;

    std::vector<OHOS::Ace::NG::Gradient> shadowColors(gradient->length);
    uint32_t pos = 0;
    for (uint32_t i = 0; i < gradient->length; i++) {
        if (gradient->gradientLength[i] == 0) {
            shadowColors.clear();
            ConvertThemeColor(shadowColors);
            break;
        }
        OHOS::Ace::NG::Gradient tempGradient;
        for (uint32_t j = 0; j < gradient->gradientLength[i]; j++, pos++) {
            OHOS::Ace::NG::GradientColor gradientColor;
            gradientColor.SetLinearColor(LinearColor(Color(gradient->color[pos])));
            gradientColor.SetDimension(
                Dimension(gradient->offset[pos].number, static_cast<DimensionUnit>(gradient->offset[pos].unit)));
            tempGradient.AddColor(gradientColor);
        }
        shadowColors.at(i) = tempGradient;
    }

    shadow.radius = radius;
    shadow.offsetX = offsetX;
    shadow.offsetY = offsetY;
    shadow.colors = shadowColors;
    DataPanelModelNG::SetShadowOption(frameNode, shadow);
}

void SetNullTrackShadow(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DataPanelShadow shadow;
    shadow.isShadowVisible = false;
    DataPanelModelNG::SetShadowOption(frameNode, shadow);
}

void ResetTrackShadow(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DataPanelShadow shadow;
    shadow.isShadowVisible = true;
    shadow.radius = DEFAULT_RADIUS;
    shadow.offsetX = DEFAULT_OFFSET_X;
    shadow.offsetY = DEFAULT_OFFSET_Y;
    std::vector<OHOS::Ace::NG::Gradient> colors;
    ConvertThemeColor(colors);
    shadow.colors = colors;
    DataPanelModelNG::SetShadowOption(frameNode, shadow);
}

ArkUIDataPanelModifierAPI GetDataPanelModifier()
{
    static const ArkUIDataPanelModifierAPI modifier = { SetCloseEffect, ResetCloseEffect,
        SetDataPanelTrackBackgroundColor, ResetDataPanelTrackBackgroundColor, SetDataPanelStrokeWidth,
        ResetDataPanelStrokeWidth, SetValueColors, ResetValueColors, SetTrackShadow, SetNullTrackShadow,
        ResetTrackShadow };

    return modifier;
}
} // namespace OHOS::Ace::NG