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
#include "core/interfaces/native/node/data_panel_modifier.h"

#include "core/components_ng/pattern/data_panel/data_panel_model_ng.h"
#include "core/common/container.h"

namespace OHOS::Ace::NG {
namespace {
constexpr bool IS_CLOSE_EFFECT = true;
constexpr double DEFAULT_STROKE_WIDTH = 24.0;
constexpr double DEFAULT_RADIUS = 20.0;
constexpr double DEFAULT_OFFSET_X = 5.0;
constexpr double DEFAULT_OFFSET_Y = 5.0;
const std::string DEFAULT_TRACK_BACKGROUND = "#08182431";
}
void SetCloseEffect(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DataPanelModelNG::SetCloseEffect(frameNode, value);
}

void ResetCloseEffect(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DataPanelModelNG::SetCloseEffect(frameNode, IS_CLOSE_EFFECT);
}

void SetDataPanelTrackBackgroundColor(ArkUINodeHandle node, uint32_t value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DataPanelModelNG::SetTrackBackground(frameNode, Color(value));
}

void ResetDataPanelTrackBackgroundColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DataPanelModelNG::SetTrackBackground(frameNode, Color::FromString(DEFAULT_TRACK_BACKGROUND));
}

void SetDataPanelStrokeWidth(ArkUINodeHandle node, ArkUI_Float32 value, int32_t unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    DataPanelModelNG::SetStrokeWidth(frameNode, Dimension(value, unitEnum));
}

void ResetDataPanelStrokeWidth(ArkUINodeHandle node)
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

void SetValueColors(ArkUINodeHandle node, const struct ArkUIGradientType* gradient)
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

void ResetValueColors(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<OHOS::Ace::NG::Gradient> colors;
    ConvertThemeColor(colors);
    DataPanelModelNG::SetValueColors(frameNode, colors);
}

void SetTrackShadow(ArkUINodeHandle node, const struct ArkUIGradientType* gradient, ArkUI_Float32 radius,
    ArkUI_Float32 offsetX, ArkUI_Float32 offsetY)
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

void SetNullTrackShadow(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DataPanelShadow shadow;
    shadow.isShadowVisible = false;
    DataPanelModelNG::SetShadowOption(frameNode, shadow);
}

void ResetTrackShadow(ArkUINodeHandle node)
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

namespace NodeModifier {
const ArkUIDataPanelModifier* GetDataPanelModifier()
{
    constexpr auto lineBegin = __LINE__; // don't move this line
    static const ArkUIDataPanelModifier modifier = {
        .setCloseEffect = SetCloseEffect,
        .resetCloseEffect = ResetCloseEffect,
        .setDataPanelTrackBackgroundColor = SetDataPanelTrackBackgroundColor,
        .resetDataPanelTrackBackgroundColor = ResetDataPanelTrackBackgroundColor,
        .setDataPanelStrokeWidth = SetDataPanelStrokeWidth,
        .resetDataPanelStrokeWidth = ResetDataPanelStrokeWidth,
        .setValueColors = SetValueColors,
        .resetValueColors = ResetValueColors,
        .setTrackShadow = SetTrackShadow,
        .setNullTrackShadow = SetNullTrackShadow,
        .resetTrackShadow = ResetTrackShadow,
    };
    constexpr auto lineEnd = __LINE__; // don't move this line
    constexpr auto ifdefOverhead = 4; // don't modify this line
    constexpr auto overHeadLines = 3; // don't modify this line
    constexpr auto blankLines = 0; // modify this line accordingly
    constexpr auto ifdefs = 0; // modify this line accordingly
    constexpr auto initializedFieldLines = lineEnd - lineBegin - ifdefs * ifdefOverhead - overHeadLines - blankLines;
    static_assert(initializedFieldLines == sizeof(modifier) / sizeof(void*),
        "ensure all fields are explicitly initialized");

    return &modifier;
}

const CJUIDataPanelModifier* GetCJUIDataPanelModifier()
{
    constexpr auto lineBegin = __LINE__; // don't move this line
    static const CJUIDataPanelModifier modifier = {
        .setCloseEffect = SetCloseEffect,
        .resetCloseEffect = ResetCloseEffect,
        .setDataPanelTrackBackgroundColor = SetDataPanelTrackBackgroundColor,
        .resetDataPanelTrackBackgroundColor = ResetDataPanelTrackBackgroundColor,
        .setDataPanelStrokeWidth = SetDataPanelStrokeWidth,
        .resetDataPanelStrokeWidth = ResetDataPanelStrokeWidth,
        .setValueColors = SetValueColors,
        .resetValueColors = ResetValueColors,
        .setTrackShadow = SetTrackShadow,
        .setNullTrackShadow = SetNullTrackShadow,
        .resetTrackShadow = ResetTrackShadow,
    };
    constexpr auto lineEnd = __LINE__; // don't move this line
    constexpr auto ifdefOverhead = 4; // don't modify this line
    constexpr auto overHeadLines = 3; // don't modify this line
    constexpr auto blankLines = 0; // modify this line accordingly
    constexpr auto ifdefs = 0; // modify this line accordingly
    constexpr auto initializedFieldLines = lineEnd - lineBegin - ifdefs * ifdefOverhead - overHeadLines - blankLines;
    static_assert(initializedFieldLines == sizeof(modifier) / sizeof(void*),
        "ensure all fields are explicitly initialized");

    return &modifier;
}
}
} // namespace OHOS::Ace::NG
