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
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_gauge_modifier.h"
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

ArkUIGaugeModifierAPI GetGaugeModifier()
{
    static const ArkUIGaugeModifierAPI modifier = { SetGaugeVaule, ResetGaugeVaule, SetGaugeStartAngle,
        ResetGaugeStartAngle, SetGaugeEndAngle, ResetGaugeEndAngle, SetGaugeStrokeWidth, ResetGaugeStrokeWidth,
        SetShadowOptions, ResetShadowOptions, SetIsShowIndicator,
        SetIndicatorIconPath, ResetIndicatorIconPath, SetIndicatorSpace, ResetIndicatorSpace,
    };

    return modifier;
}
} // namespace OHOS::Ace::NG