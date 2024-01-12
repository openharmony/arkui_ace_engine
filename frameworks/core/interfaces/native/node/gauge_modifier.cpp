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
#include "core/interfaces/native/node/gauge_modifier.h"
#include "core/pipeline/base/element_register.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/gauge/gauge_model_ng.h"
#include "core/components/common/layout/constants.h"

namespace OHOS::Ace::NG {
constexpr float MIN_VALUE = 0.0f;
constexpr float DEFAULT_START_ANGLE = 0.0f;
constexpr float DEFAULT_END_ANGLE = 360.0f;
constexpr int32_t DEFAULT_STROKE_WIDTH = 4;
void SetGaugeVaule(NodeHandle node, float value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GaugeModelNG::SetValue(frameNode, value);
}

void ResetGaugeVaule(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GaugeModelNG::SetValue(frameNode, MIN_VALUE);
}

void SetGaugeStartAngle(NodeHandle node, float value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GaugeModelNG::SetStartAngle(frameNode, value);
}

void ResetGaugeStartAngle(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GaugeModelNG::SetStartAngle(frameNode, DEFAULT_START_ANGLE);
}

void SetGaugeEndAngle(NodeHandle node, float value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GaugeModelNG::SetEndAngle(frameNode, value);
}

void ResetGaugeEndAngle(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GaugeModelNG::SetEndAngle(frameNode, DEFAULT_END_ANGLE);
}

void SetGaugeStrokeWidth(NodeHandle node, double value, int32_t unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    GaugeModelNG::SetGaugeStrokeWidth(frameNode, Dimension(value, unitEnum));
}

void ResetGaugeStrokeWidth(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GaugeModelNG::SetGaugeStrokeWidth(frameNode, Dimension(DEFAULT_STROKE_WIDTH, DimensionUnit::VP));
}

void SetShadowOptions(NodeHandle node, double radius, double offsetX, double offsetY, bool isShadowVisible)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::GaugeShadowOptions shadowOptions;
    shadowOptions.radius = radius;
    shadowOptions.offsetX = offsetX;
    shadowOptions.offsetY = offsetY;
    shadowOptions.isShadowVisible = isShadowVisible;
    GaugeModelNG::SetShadowOptions(frameNode, shadowOptions);
}

void ResetShadowOptions(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GaugeModelNG::ResetShadowOptions(frameNode);
}

void SetIsShowIndicator(NodeHandle node, bool isShowIndicator)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GaugeModelNG::SetIsShowIndicator(frameNode, isShowIndicator);
}

void SetIndicatorIconPath(NodeHandle node, const char* iconPath, const char* bundleName, const char* moduleName)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string iconPathStr;
    std::string bundleNameStr;
    std::string moduleNameStr;
    if (iconPath != nullptr) {
        iconPathStr = iconPath;
    }
    if (bundleName != nullptr) {
        bundleNameStr = bundleName;
    }
    if (moduleName != nullptr) {
        moduleNameStr = moduleName;
    }
    GaugeModelNG::SetIndicatorIconPath(frameNode, iconPathStr, bundleNameStr, moduleNameStr);
}

void ResetIndicatorIconPath(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GaugeModelNG::ResetIndicatorIconPath(frameNode);
}

void SetIndicatorSpace(NodeHandle node, const char* spaceStrValue, double spaceValue, int32_t spaceUnit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension space;
    auto spaceUnitValue = static_cast<DimensionUnit>(spaceUnit);
    if (spaceUnitValue == DimensionUnit::CALC) {
        std::string valueStr;
        if (spaceStrValue != nullptr) {
            valueStr = spaceStrValue;
        }
        space = CalcDimension(valueStr, spaceUnitValue);
    } else {
        space = CalcDimension(spaceValue, spaceUnitValue);
    }
    GaugeModelNG::SetIndicatorSpace(frameNode, space);
}

void ResetIndicatorSpace(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GaugeModelNG::ResetIndicatorSpace(frameNode);
}

void SetColors(NodeHandle node, const uint32_t* colors, const float* weight, uint32_t length)
{
    CHECK_NULL_VOID(colors);
    CHECK_NULL_VOID(weight);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<Color> inputColor(length);
    std::vector<float> weights(length);
    for (uint32_t i = 0; i < length; i++) {
        inputColor.at(i) = Color(colors[i]);
        weights.at(i) = weight[i];
    }
    GaugeModelNG::SetColors(frameNode, inputColor, weights);
}

void ResetColors(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<Color> inputColor;
    std::vector<float> weights;
    GaugeModelNG::SetColors(frameNode, inputColor, weights);
}

void SetGradientColors(NodeHandle node, const struct ArkUIGradientType* gradient, uint32_t weightLength)
{
    CHECK_NULL_VOID(gradient->gradientLength);
    CHECK_NULL_VOID(gradient->color);
    CHECK_NULL_VOID(gradient->offset);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<float> weight;
    if (weightLength > 0 && gradient->weight != nullptr) {
        weight = std::vector<float>(gradient->weight, gradient->weight + weightLength);
    }
    std::vector<ColorStopArray> colors(gradient->length);
    uint32_t pos = 0;
    for (uint32_t i = 0; i < gradient->length; i++) {
        if (static_cast<int32_t>(i) >= NG::COLORS_MAX_COUNT) {
            break;
        }
        if (gradient->gradientLength[i] == 0) {
            colors.at(i) = NG::ColorStopArray { std::make_pair(Color(gradient->color[pos]), Dimension(0.0)) };
            continue;
        }
        ColorStopArray colorStop(gradient->gradientLength[i]);
        for (uint32_t j = 0; j < gradient->gradientLength[i]; j++, pos++) {
            colorStop.at(j) = std::make_pair(Color(gradient->color[pos]),
                Dimension(gradient->offset[pos].number, static_cast<DimensionUnit>(gradient->offset[pos].unit)));
        }
        colors.at(i) = colorStop;
    }
    GaugeType type = static_cast<GaugeType>(gradient->type);
    GaugeModelNG::SetGradientColors(frameNode, colors, weight, type);
}

void ResetGradientColors(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    GaugeModelNG::ResetGradientColors(frameNode);
}

ArkUIGaugeModifierAPI GetGaugeModifier()
{
    static const ArkUIGaugeModifierAPI modifier = { SetGaugeVaule, ResetGaugeVaule, SetGaugeStartAngle,
        ResetGaugeStartAngle, SetGaugeEndAngle, ResetGaugeEndAngle, SetGaugeStrokeWidth, ResetGaugeStrokeWidth,
        SetShadowOptions, ResetShadowOptions, SetIsShowIndicator,
        SetIndicatorIconPath, ResetIndicatorIconPath, SetIndicatorSpace, ResetIndicatorSpace,
        SetColors, ResetColors, SetGradientColors, ResetGradientColors
    };

    return modifier;
}
} // namespace OHOS::Ace::NG