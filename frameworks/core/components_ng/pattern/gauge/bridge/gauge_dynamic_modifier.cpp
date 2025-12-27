/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/common/resource/resource_parse_utils.h"
#include "core/components/progress/progress_component.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/pattern/gauge/bridge/gauge_model_impl.h"
#include "core/components_ng/pattern/gauge/gauge_model_ng.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "core/interfaces/cjui/cjui_api.h"

namespace OHOS::Ace {
#ifndef CROSS_PLATFORM
Framework::GaugeModelImpl* GetGaugeModelImpl()
{
    static Framework::GaugeModelImpl instance;
    return &instance;
}
#endif
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
constexpr float MIN_VALUE = 0.0f;
constexpr float DEFAULT_START_ANGLE = 0.0f;
constexpr float DEFAULT_END_ANGLE = 360.0f;
constexpr int32_t DEFAULT_STROKE_WIDTH = 4;

FrameNode* GetFrameNode(ArkUINodeHandle node)
{
    return node ? reinterpret_cast<FrameNode*>(node) : ViewStackProcessor::GetInstance()->GetMainFrameNode();
}

void CreateModel(ArkUI_Float32 value, ArkUI_Float32 min, ArkUI_Float32 max)
{
    GaugeModelNG::CreateFrameNode(value, min, max);
}

void SetIsShowLimitValue(ArkUINodeHandle node, ArkUI_Bool isShowLimitValue)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GaugeModelNG::SetIsShowLimitValue(frameNode, isShowLimitValue);
}

void SetGaugeValue(ArkUINodeHandle node, ArkUI_Float32 value)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GaugeModelNG::SetValue(frameNode, value);
}

void ResetGaugeValue(ArkUINodeHandle node)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GaugeModelNG::SetValue(frameNode, MIN_VALUE);
}

void SetGaugeStartAngle(ArkUINodeHandle node, ArkUI_Float32 value)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GaugeModelNG::SetStartAngle(frameNode, value);
}

void ResetGaugeStartAngle(ArkUINodeHandle node)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GaugeModelNG::SetStartAngle(frameNode, DEFAULT_START_ANGLE);
}

void SetGaugeEndAngle(ArkUINodeHandle node, ArkUI_Float32 value)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GaugeModelNG::SetEndAngle(frameNode, value);
}

void ResetGaugeEndAngle(ArkUINodeHandle node)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GaugeModelNG::SetEndAngle(frameNode, DEFAULT_END_ANGLE);
}

void SetGaugeStrokeWidth(ArkUINodeHandle node, ArkUI_Float32 value, int32_t unit)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    GaugeModelNG::SetGaugeStrokeWidth(frameNode, Dimension(value, unitEnum));
}

void SetGaugeStrokeWidthPtr(ArkUINodeHandle node, ArkUI_Float32 value, int32_t unit, void* strokeWidthRawPtr)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    GaugeModelNG::SetGaugeStrokeWidth(frameNode, Dimension(value, unitEnum));
    if (SystemProperties::ConfigChangePerform()) {
        auto* strokeWidth = reinterpret_cast<ResourceObject*>(strokeWidthRawPtr);
        auto strokeWidthResObj = AceType::Claim(strokeWidth);
        GaugeModelNG::CreateWithResourceObj(frameNode, GaugeResourceType::STROKE_WIDTH, strokeWidthResObj);
    }
}

void ResetGaugeStrokeWidth(ArkUINodeHandle node)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GaugeModelNG::SetGaugeStrokeWidth(frameNode, Dimension(DEFAULT_STROKE_WIDTH, DimensionUnit::VP));
    if (SystemProperties::ConfigChangePerform()) {
        GaugeModelNG::CreateWithResourceObj(frameNode, GaugeResourceType::STROKE_WIDTH, nullptr);
    }
}

void ShadowOptionsUpdateFunc(
    NG::GaugeShadowOptions& shadowOptions, void* radiusRawPtr, void* offsetXRawPtr, void* offsetYRawPtr)
{
    if (SystemProperties::ConfigChangePerform() && radiusRawPtr) {
        auto* radius = reinterpret_cast<ResourceObject*>(radiusRawPtr);
        auto radiusResObj = AceType::Claim(radius);
        auto&& radiusUpdateFunc = [](const RefPtr<ResourceObject>& resObj, NG::GaugeShadowOptions& shadowOptions) {
            double radius = 0.0;
            if (ResourceParseUtils::ParseResDouble(resObj, radius) && !NonPositive(radius)) {
                shadowOptions.radius = radius;
            } else {
                shadowOptions.radius = NG::DEFAULT_GAUGE_SHADOW_RADIUS;
            }
        };
        shadowOptions.AddResource("gauge.shadow.radius", radiusResObj, std::move(radiusUpdateFunc));
    }
    if (SystemProperties::ConfigChangePerform() && offsetXRawPtr) {
        auto* offsetX = reinterpret_cast<ResourceObject*>(offsetXRawPtr);
        auto offsetXResObj = AceType::Claim(offsetX);
        auto&& offsetXUpdateFunc = [](const RefPtr<ResourceObject>& resObj, NG::GaugeShadowOptions& shadowOptions) {
            double offsetX = 0.0;
            if (ResourceParseUtils::ParseResDouble(resObj, offsetX)) {
                shadowOptions.offsetX = offsetX;
            } else {
                shadowOptions.offsetX = NG::DEFAULT_GAUGE_SHADOW_OFFSETX;
            }
        };
        shadowOptions.AddResource("gauge.shadow.offsetX", offsetXResObj, std::move(offsetXUpdateFunc));
    }
    if (SystemProperties::ConfigChangePerform() && offsetYRawPtr) {
        auto* offsetY = reinterpret_cast<ResourceObject*>(offsetYRawPtr);
        auto offsetYResObj = AceType::Claim(offsetY);
        auto&& offsetYUpdateFunc = [](const RefPtr<ResourceObject>& resObj, NG::GaugeShadowOptions& shadowOptions) {
            double offsetY = 0.0;
            if (ResourceParseUtils::ParseResDouble(resObj, offsetY)) {
                shadowOptions.offsetY = offsetY;
            } else {
                shadowOptions.offsetY = NG::DEFAULT_GAUGE_SHADOW_OFFSETY;
            }
        };
        shadowOptions.AddResource("gauge.shadow.offsetY", offsetYResObj, std::move(offsetYUpdateFunc));
    }
}

void SetShadowOptions(ArkUINodeHandle node, ArkUI_Float32 radius, ArkUI_Float32 offsetX, ArkUI_Float32 offsetY,
    ArkUI_Bool isShadowVisible)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    NG::GaugeShadowOptions shadowOptions;
    shadowOptions.radius = radius;
    shadowOptions.offsetX = offsetX;
    shadowOptions.offsetY = offsetY;
    shadowOptions.isShadowVisible = isShadowVisible;
    GaugeModelNG::SetShadowOptions(frameNode, shadowOptions);
}

void SetShadowOptionsPtr(
    ArkUINodeHandle node, ArkUIGaugeShadowOptions& shadow, ArkUIShadowOptionsResource& shadowOptionsResource)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    NG::GaugeShadowOptions shadowOptions;

    // Validate and set radius with default if invalid
    if (NonPositive(shadow.radius)) {
        shadowOptions.radius = NG::DEFAULT_GAUGE_SHADOW_RADIUS;
    } else {
        shadowOptions.radius = shadow.radius;
    }

    shadowOptions.offsetX = shadow.offsetX;
    shadowOptions.offsetY = shadow.offsetY;
    shadowOptions.isShadowVisible = shadow.isShadowVisible;
    ShadowOptionsUpdateFunc(shadowOptions, shadowOptionsResource.radiusRawPtr, shadowOptionsResource.offsetXRawPtr,
        shadowOptionsResource.offsetYRawPtr);
    GaugeModelNG::SetShadowOptions(frameNode, shadowOptions);
}

void ResetShadowOptions(ArkUINodeHandle node)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GaugeModelNG::ResetShadowOptions(frameNode);
}

void SetIsShowIndicator(ArkUINodeHandle node, ArkUI_Bool isShowIndicator)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GaugeModelNG::SetIsShowIndicator(frameNode, isShowIndicator);
}
void SetIndicatorIconPath(ArkUINodeHandle node, const char* iconPath, const char* bundleName, const char* moduleName)

{
    FrameNode* frameNode = GetFrameNode(node);
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

void SetIndicatorIconPathPtr(
    ArkUINodeHandle node, const char* iconPath, const char* bundleName, const char* moduleName, void* iconPathRawPtr)
{
    FrameNode* frameNode = GetFrameNode(node);
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

    if (SystemProperties::ConfigChangePerform()) {
        auto* iconPathResObjRaw = reinterpret_cast<ResourceObject*>(iconPathRawPtr);
        auto iconPathResObj = AceType::Claim(iconPathResObjRaw);
        GaugeModelNG::CreateWithResourceObj(frameNode, GaugeResourceType::INDICATOR_ICON, iconPathResObj);
    }
}

void ResetIndicatorIconPath(ArkUINodeHandle node)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GaugeModelNG::ResetIndicatorIconPath(frameNode);
    if (SystemProperties::ConfigChangePerform()) {
        GaugeModelNG::CreateWithResourceObj(frameNode, GaugeResourceType::INDICATOR_ICON, nullptr);
    }
}

void SetIndicatorSpace(ArkUINodeHandle node, const char* spaceStrValue, ArkUI_Float32 spaceValue, int32_t spaceUnit)
{
    FrameNode* frameNode = GetFrameNode(node);
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

void SetIndicatorSpacePtr(
    ArkUINodeHandle node, const char* spaceStrValue, ArkUI_Float32 spaceValue, int32_t spaceUnit, void* spaceRawPtr)
{
    FrameNode* frameNode = GetFrameNode(node);
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

    // Validate space value - set to default if negative
    if (space.IsNegative()) {
        space = NG::INDICATOR_DISTANCE_TO_TOP;
    }

    GaugeModelNG::SetIndicatorSpace(frameNode, space);

    if (SystemProperties::ConfigChangePerform()) {
        auto* spaceResObj = reinterpret_cast<ResourceObject*>(spaceRawPtr);
        auto spaceResObjPtr = AceType::Claim(spaceResObj);
        GaugeModelNG::CreateWithResourceObj(frameNode, GaugeResourceType::INDICATOR_SPACE, spaceResObjPtr);
    }
}

void ResetIndicatorSpace(ArkUINodeHandle node)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GaugeModelNG::ResetIndicatorSpace(frameNode);
    if (SystemProperties::ConfigChangePerform()) {
        GaugeModelNG::CreateWithResourceObj(frameNode, GaugeResourceType::INDICATOR_SPACE, nullptr);
    }
}

void SetColors(ArkUINodeHandle node, const uint32_t* colors, const ArkUI_Float32* weight, uint32_t length)
{
    CHECK_NULL_VOID(colors);
    CHECK_NULL_VOID(weight);
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<Color> inputColor(length);
    std::vector<ArkUI_Float32> weights(length);
    for (uint32_t i = 0; i < length; i++) {
        inputColor.at(i) = Color(colors[i]);
        weights.at(i) = weight[i];
    }
    GaugeModelNG::SetColors(frameNode, inputColor, weights);
}

void ResetColors(ArkUINodeHandle node)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<Color> inputColor;
    std::vector<ArkUI_Float32> weights;
    GaugeModelNG::SetColors(frameNode, inputColor, weights);
}

void SortColorStopByOffset(std::vector<NG::ColorStopArray>& colors)
{
    for (auto& colorStopArray : colors) {
        std::sort(colorStopArray.begin(), colorStopArray.end(),
            [](const std::pair<Color, Dimension>& left, const std::pair<Color, Dimension>& right) {
                return left.second.Value() < right.second.Value();
            });

        auto iter = std::unique(colorStopArray.begin(), colorStopArray.end(),
            [](const std::pair<Color, Dimension>& left, const std::pair<Color, Dimension>& right) {
                return left.second.Value() == right.second.Value();
            });
        colorStopArray.erase(iter, colorStopArray.end());
    }
}

void SetGradientColors(ArkUINodeHandle node, const struct ArkUIGradientType* gradient, uint32_t weightLength)
{
    CHECK_NULL_VOID(gradient->gradientLength);
    CHECK_NULL_VOID(gradient->color);
    CHECK_NULL_VOID(gradient->offset);
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<ArkUI_Float32> weight;
    if (weightLength > 0 && gradient->weight != nullptr) {
        weight = std::vector<ArkUI_Float32>(gradient->weight, gradient->weight + weightLength);
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
            auto color = static_cast<Color>(gradient->color[pos]);
            if (gradient->colorResourceId != nullptr && pos >= 0 && pos < gradient->length) {
                color.SetResourceId(gradient->colorResourceId[pos]);
            }
            colorStop.at(j) = std::make_pair(
                color, Dimension(gradient->offset[pos].number, static_cast<DimensionUnit>(gradient->offset[pos].unit)));
        }
        colors.at(i) = colorStop;
    }
    GaugeType type = static_cast<GaugeType>(gradient->type);
    SortColorStopByOffset(colors);
    if (SystemProperties::ConfigChangePerform()) {
        GaugeModelNG::SetUseGradient(frameNode, gradient->isGradientColor);
    }
    GaugeModelNG::SetGradientColors(frameNode, colors, weight, type);
}

void ResetGradientColors(ArkUINodeHandle node)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GaugeModelNG::ResetGradientColors(frameNode);
}

void SetUseSpecialDefaultIndicator(ArkUINodeHandle node, ArkUI_Bool useSpecialDefaultIndicator)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GaugeModelNG::SetUseSpecialDefaultIndicator(frameNode, useSpecialDefaultIndicator);
}

void SetIsShowDescription(ArkUINodeHandle node, ArkUI_Bool isShowDescription)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GaugeModelNG::SetIsShowDescription(frameNode, isShowDescription);
}

void SetDescription()
{
    auto customNode = ViewStackModel::GetInstance()->Finish();
    CHECK_NULL_VOID(customNode);
    GaugeModelNG::SetDescriptionStatic(customNode);
}

#ifndef CROSS_PLATFORM
void CreateModelImpl(ArkUI_Float32 value, ArkUI_Float32 min, ArkUI_Float32 max)
{
    GetGaugeModelImpl()->Create(value, min, max);
}

void SetIsShowLimitValueImpl(ArkUINodeHandle node, ArkUI_Bool isShowLimitValue)
{
    GetGaugeModelImpl()->SetIsShowLimitValue(isShowLimitValue);
}

void SetValueImpl(ArkUINodeHandle node, ArkUI_Float32 value)
{
    GetGaugeModelImpl()->SetValue(value);
}

void ResetGaugeValueImpl(ArkUINodeHandle node)
{
    GetGaugeModelImpl()->SetValue(MIN_VALUE);
}

void SetGaugeStartAngleImpl(ArkUINodeHandle node, ArkUI_Float32 value)
{
    GetGaugeModelImpl()->SetStartAngle(value);
}

void ResetGaugeStartAngleImpl(ArkUINodeHandle node)
{
    GetGaugeModelImpl()->SetStartAngle(DEFAULT_START_ANGLE);
}

void SetGaugeEndAngleImpl(ArkUINodeHandle node, ArkUI_Float32 value)
{
    GetGaugeModelImpl()->SetEndAngle(value);
}

void ResetGaugeEndAngleImpl(ArkUINodeHandle node)
{
    GetGaugeModelImpl()->SetEndAngle(DEFAULT_END_ANGLE);
}

void SetGaugeStrokeWidthImpl(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit)
{
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    GetGaugeModelImpl()->SetStrokeWidth(Dimension(value, unitEnum));
}

void SetGaugeStrokeWidthPtrImpl(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, void* strokeWidthRawPtr)
{
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    GetGaugeModelImpl()->SetStrokeWidth(Dimension(value, unitEnum));
    if (SystemProperties::ConfigChangePerform()) {
        auto* strokeWidth = reinterpret_cast<ResourceObject*>(strokeWidthRawPtr);
        auto strokeWidthResObj = AceType::Claim(strokeWidth);
        GetGaugeModelImpl()->CreateWithResourceObj(GaugeResourceType::STROKE_WIDTH, strokeWidthResObj);
    }
}

void ResetGaugeStrokeWidthImpl(ArkUINodeHandle node)
{
    GetGaugeModelImpl()->SetStrokeWidth(Dimension(DEFAULT_STROKE_WIDTH, DimensionUnit::VP));
    if (SystemProperties::ConfigChangePerform()) {
        GetGaugeModelImpl()->CreateWithResourceObj(GaugeResourceType::STROKE_WIDTH, nullptr);
    }
}

void SetShadowOptionsImpl(ArkUINodeHandle node, ArkUI_Float32 radius, ArkUI_Float32 offsetX, ArkUI_Float32 offsetY,
    ArkUI_Bool isShadowVisible)
{
    NG::GaugeShadowOptions shadowOptions;
    shadowOptions.radius = radius;
    shadowOptions.offsetX = offsetX;
    shadowOptions.offsetY = offsetY;
    shadowOptions.isShadowVisible = isShadowVisible;
    GetGaugeModelImpl()->SetShadowOptions(shadowOptions);
}

void SetShadowOptionsPtrImpl(
    ArkUINodeHandle node, ArkUIGaugeShadowOptions& shadow, ArkUIShadowOptionsResource& shadowOptionsResource)
{
    NG::GaugeShadowOptions shadowOptions;

    // Validate and set radius with default if invalid
    if (NonPositive(shadow.radius)) {
        shadowOptions.radius = NG::DEFAULT_GAUGE_SHADOW_RADIUS;
    } else {
        shadowOptions.radius = shadow.radius;
    }

    shadowOptions.offsetX = shadow.offsetX;
    shadowOptions.offsetY = shadow.offsetY;
    shadowOptions.isShadowVisible = shadow.isShadowVisible;
    ShadowOptionsUpdateFunc(shadowOptions, shadowOptionsResource.radiusRawPtr, shadowOptionsResource.offsetXRawPtr,
        shadowOptionsResource.offsetYRawPtr);
    GetGaugeModelImpl()->SetShadowOptions(shadowOptions);
}

void ResetShadowOptionsImpl(ArkUINodeHandle node)
{
    GetGaugeModelImpl()->ResetShadowOptions();
}

void SetIsShowIndicatorImpl(ArkUINodeHandle node, ArkUI_Bool isShowIndicator)
{
    GetGaugeModelImpl()->SetIsShowIndicator(isShowIndicator);
}

void SetIndicatorIconPathImpl(
    ArkUINodeHandle node, const char* iconPath, const char* bundleName, const char* moduleName)
{
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
    GetGaugeModelImpl()->SetIndicatorIconPath(iconPathStr, bundleNameStr, moduleNameStr);
}

void SetIndicatorIconPathPtrImpl(ArkUINodeHandle node, ArkUI_CharPtr iconPath, ArkUI_CharPtr bundleName,
    ArkUI_CharPtr moduleName, void* iconPathRawPtr)
{
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
    GetGaugeModelImpl()->SetIndicatorIconPath(iconPathStr, bundleNameStr, moduleNameStr);

    if (SystemProperties::ConfigChangePerform()) {
        auto* iconPathResObjRaw = reinterpret_cast<ResourceObject*>(iconPathRawPtr);
        auto iconPathResObj = AceType::Claim(iconPathResObjRaw);
        GetGaugeModelImpl()->CreateWithResourceObj(GaugeResourceType::INDICATOR_ICON, iconPathResObj);
    }
}

void ResetIndicatorIconPathImpl(ArkUINodeHandle node)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    GetGaugeModelImpl()->ResetIndicatorIconPath();
    if (SystemProperties::ConfigChangePerform()) {
        GetGaugeModelImpl()->CreateWithResourceObj(GaugeResourceType::INDICATOR_ICON, nullptr);
    }
}

void SetIndicatorSpaceImpl(ArkUINodeHandle node, const char* spaceStrValue, ArkUI_Float32 spaceValue, int32_t spaceUnit)
{
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
    GetGaugeModelImpl()->SetIndicatorSpace(space);
}

void SetIndicatorSpacePtrImpl(
    ArkUINodeHandle node, const char* spaceStrValue, ArkUI_Float32 spaceValue, int32_t spaceUnit, void* spaceRawPtr)
{
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

    // Validate space value - set to default if negative
    if (space.IsNegative()) {
        space = NG::INDICATOR_DISTANCE_TO_TOP;
    }

    GetGaugeModelImpl()->SetIndicatorSpace(space);

    if (SystemProperties::ConfigChangePerform()) {
        auto* spaceResObj = reinterpret_cast<ResourceObject*>(spaceRawPtr);
        auto spaceResObjPtr = AceType::Claim(spaceResObj);
        GetGaugeModelImpl()->CreateWithResourceObj(GaugeResourceType::INDICATOR_SPACE, spaceResObjPtr);
    }
}

void ResetIndicatorSpaceImpl(ArkUINodeHandle node)
{
    GetGaugeModelImpl()->ResetIndicatorSpace();
    if (SystemProperties::ConfigChangePerform()) {
        GetGaugeModelImpl()->CreateWithResourceObj(GaugeResourceType::INDICATOR_SPACE, nullptr);
    }
}

void SetColorsImpl(ArkUINodeHandle node, const ArkUI_Uint32* colors, const ArkUI_Float32* weight, ArkUI_Uint32 length)
{
    std::vector<Color> inputColor(length);
    std::vector<ArkUI_Float32> weights(length);
    for (uint32_t i = 0; i < length; i++) {
        inputColor.at(i) = Color(colors[i]);
        weights.at(i) = weight[i];
    }
    GetGaugeModelImpl()->SetColors(inputColor, weights);
}

void ResetColorsImpl(ArkUINodeHandle node)
{
    std::vector<Color> inputColor;
    std::vector<ArkUI_Float32> weights;
    GetGaugeModelImpl()->SetColors(inputColor, weights);
}

void SetGradientColorsImpl(ArkUINodeHandle node, const struct ArkUIGradientType* gradient, ArkUI_Uint32 weightLength)
{
    std::vector<ArkUI_Float32> weight;
    if (weightLength > 0 && gradient->weight != nullptr) {
        weight = std::vector<ArkUI_Float32>(gradient->weight, gradient->weight + weightLength);
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
            auto color = static_cast<Color>(gradient->color[pos]);
            if (gradient->colorResourceId != nullptr && pos >= 0 && pos < gradient->length) {
                color.SetResourceId(gradient->colorResourceId[pos]);
            }
            colorStop.at(j) = std::make_pair(
                color, Dimension(gradient->offset[pos].number, static_cast<DimensionUnit>(gradient->offset[pos].unit)));
        }
        colors.at(i) = colorStop;
    }
    GaugeType type = static_cast<GaugeType>(gradient->type);
    SortColorStopByOffset(colors);
    if (SystemProperties::ConfigChangePerform()) {
        GetGaugeModelImpl()->SetUseGradient(gradient->isGradientColor);
    }
    GetGaugeModelImpl()->SetGradientColors(colors, weight, type);
}

void ResetGradientColorsImpl(ArkUINodeHandle node)
{
    GetGaugeModelImpl()->ResetGradientColors();
}

void SetUseSpecialDefaultIndicatorImpl(ArkUINodeHandle node, ArkUI_Bool useSpecialDefaultIndicator)
{
    GetGaugeModelImpl()->SetUseSpecialDefaultIndicator(useSpecialDefaultIndicator);
}

void SetIsShowDescriptionImpl(ArkUINodeHandle node, ArkUI_Bool isShowDescription)
{
    GetGaugeModelImpl()->SetIsShowDescription(isShowDescription);
}

void SetDescriptionImpl() {}
#endif

ArkUINodeHandle CreateFrameNode(int32_t nodeId)
{
    return nullptr;
}

const ArkUIGaugeModifier* GetGaugeDynamicModifier()
{
    static bool isCurrentUseNewPipeline = Container::IsCurrentUseNewPipeline();
    if (!isCurrentUseNewPipeline) {
#ifndef CROSS_PLATFORM
        CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
        static const ArkUIGaugeModifier modifier = {
            .createModel = CreateModelImpl,
            .setIsShowLimitValue = SetIsShowLimitValueImpl,
            .setGaugeValue = SetValueImpl,
            .resetGaugeValue = ResetGaugeValueImpl,
            .setGaugeStartAngle = SetGaugeStartAngleImpl,
            .resetGaugeStartAngle = ResetGaugeStartAngleImpl,
            .setGaugeEndAngle = SetGaugeEndAngleImpl,
            .resetGaugeEndAngle = ResetGaugeEndAngleImpl,
            .setGaugeStrokeWidth = SetGaugeStrokeWidthImpl,
            .setGaugeStrokeWidthPtr = SetGaugeStrokeWidthPtrImpl,
            .resetGaugeStrokeWidth = ResetGaugeStrokeWidthImpl,
            .setShadowOptions = SetShadowOptionsImpl,
            .setShadowOptionsPtr = SetShadowOptionsPtrImpl,
            .resetShadowOptions = ResetShadowOptionsImpl,
            .setIsShowIndicator = SetIsShowIndicatorImpl,
            .setIndicatorIconPath = SetIndicatorIconPathImpl,
            .setIndicatorIconPathPtr = SetIndicatorIconPathPtrImpl,
            .resetIndicatorIconPath = ResetIndicatorIconPathImpl,
            .setIndicatorSpace = SetIndicatorSpaceImpl,
            .setIndicatorSpacePtr = SetIndicatorSpacePtrImpl,
            .resetIndicatorSpace = ResetIndicatorSpaceImpl,
            .setColors = SetColorsImpl,
            .resetColors = ResetColorsImpl,
            .setGradientColors = SetGradientColorsImpl,
            .resetGradientColors = ResetGradientColorsImpl,
            .setUseSpecialDefaultIndicator = SetUseSpecialDefaultIndicatorImpl,
            .setIsShowDescription = SetIsShowDescriptionImpl,
            .setDescription = SetDescriptionImpl,
            .createFrameNode = CreateFrameNode,
        };
        CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

        return &modifier;
#endif
    }
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIGaugeModifier modifier = {
        .createModel = CreateModel,
        .setIsShowLimitValue = SetIsShowLimitValue,
        .setGaugeValue = SetGaugeValue,
        .resetGaugeValue = ResetGaugeValue,
        .setGaugeStartAngle = SetGaugeStartAngle,
        .resetGaugeStartAngle = ResetGaugeStartAngle,
        .setGaugeEndAngle = SetGaugeEndAngle,
        .resetGaugeEndAngle = ResetGaugeEndAngle,
        .setGaugeStrokeWidth = SetGaugeStrokeWidth,
        .setGaugeStrokeWidthPtr = SetGaugeStrokeWidthPtr,
        .resetGaugeStrokeWidth = ResetGaugeStrokeWidth,
        .setShadowOptions = SetShadowOptions,
        .setShadowOptionsPtr = SetShadowOptionsPtr,
        .resetShadowOptions = ResetShadowOptions,
        .setIsShowIndicator = SetIsShowIndicator,
        .setIndicatorIconPath = SetIndicatorIconPath,
        .setIndicatorIconPathPtr = SetIndicatorIconPathPtr,
        .resetIndicatorIconPath = ResetIndicatorIconPath,
        .setIndicatorSpace = SetIndicatorSpace,
        .setIndicatorSpacePtr = SetIndicatorSpacePtr,
        .resetIndicatorSpace = ResetIndicatorSpace,
        .setColors = SetColors,
        .resetColors = ResetColors,
        .setGradientColors = SetGradientColors,
        .resetGradientColors = ResetGradientColors,
        .setUseSpecialDefaultIndicator = SetUseSpecialDefaultIndicator,
        .setIsShowDescription = SetIsShowDescription,
        .setDescription = SetDescription,
        .createFrameNode = CreateFrameNode,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}

const CJUIGaugeModifier* GetCJUIGaugeModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIGaugeModifier modifier = {
        .setGaugeValue = SetGaugeValue,
        .resetGaugeValue = ResetGaugeValue,
        .setGaugeStartAngle = SetGaugeStartAngle,
        .resetGaugeStartAngle = ResetGaugeStartAngle,
        .setGaugeEndAngle = SetGaugeEndAngle,
        .resetGaugeEndAngle = ResetGaugeEndAngle,
        .setGaugeStrokeWidth = SetGaugeStrokeWidth,
        .setGaugeStrokeWidthPtr = SetGaugeStrokeWidthPtr,
        .resetGaugeStrokeWidth = ResetGaugeStrokeWidth,
        .setShadowOptions = SetShadowOptions,
        .setShadowOptionsPtr = SetShadowOptionsPtr,
        .resetShadowOptions = ResetShadowOptions,
        .setIsShowIndicator = SetIsShowIndicator,
        .setIndicatorIconPath = SetIndicatorIconPath,
        .setIndicatorIconPathPtr = SetIndicatorIconPathPtr,
        .resetIndicatorIconPath = ResetIndicatorIconPath,
        .setIndicatorSpace = SetIndicatorSpace,
        .setIndicatorSpacePtr = SetIndicatorSpacePtr,
        .resetIndicatorSpace = ResetIndicatorSpace,
        .setColors = SetColors,
        .resetColors = ResetColors,
        .setGradientColors = SetGradientColors,
        .resetGradientColors = ResetGradientColors,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}

} // namespace OHOS::Ace::NG
