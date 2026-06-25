/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/common/container.h"
#include "core/common/dynamic_module_helper.h"
#include "core/common/resource/resource_parse_utils.h"
#include "core/components/checkable/checkable_theme.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/toggle/toggle_model_ng.h"
#include "core/interfaces/native/node/node_toggle_modifier.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t ERROR_UINT_CODE = -1;
constexpr uint32_t RESPONSE_REGION_STEP = 4;
constexpr uint32_t OFFSET_0 = 0;
constexpr uint32_t OFFSET_1 = 1;
constexpr uint32_t OFFSET_2 = 2;
constexpr uint32_t OFFSET_3 = 3;
constexpr uint32_t INDEX_DIMENSION_TOP_0 = 0;
constexpr uint32_t INDEX_DIMENSION_RIGHT_1 = 1;
constexpr uint32_t INDEX_DIMENSION_BOTTOM_2 = 2;
constexpr uint32_t INDEX_DIMENSION_LEFT_3 = 3;
constexpr uint32_t DIMENSION_STEP = 3;

FrameNode* GetFrameNode(ArkUINodeHandle node)
{
    return node ? reinterpret_cast<FrameNode*>(node) : ViewStackProcessor::GetInstance()->GetMainFrameNode();
}

bool SetToggleDimension(const ArkUI_Float32* dimensionArray, ArkUI_Uint32 offset, const size_t dataCount,
    std::optional<CalcDimension>& optDimension)
{
    CHECK_NULL_RETURN(dimensionArray, false);
    auto hasValue = dimensionArray[offset];
    if (!static_cast<bool>(hasValue)) {
        return false;
    }
    uint32_t valueIndex = offset + 1;
    uint32_t unitIndex = offset + 2;
    if (unitIndex >= dataCount) {
        return false;
    }
    auto value = dimensionArray[valueIndex];
    auto unit = dimensionArray[unitIndex];
    DimensionUnit unitValue = static_cast<DimensionUnit>(unit);
    CalcDimension dimensionValue = CalcDimension(value, unitValue);
    optDimension = dimensionValue;
    return true;
}

void Create(ArkUI_Int32 toggleType, ArkUI_Bool isOn)
{
    ToggleModelNG toggleModelNG;
    toggleModelNG.Create(static_cast<NG::ToggleType>(toggleType), static_cast<bool>(isOn));
}

ArkUINodeHandle CreateFrameNode(ArkUI_Int32 nodeId, ArkUI_Int32 toggleType, ArkUI_Bool isOn)
{
    auto frameNode =
        ToggleModelNG::CreateFrameNode(nodeId, static_cast<NG::ToggleType>(toggleType), static_cast<bool>(isOn));
    frameNode->IncRefCount();
    return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode));
}

void SetOnChangeEvent(void* callback)
{
    auto* frameNode = GetFrameNode(nullptr);
    CHECK_NULL_VOID(frameNode);
    auto changeEvent = reinterpret_cast<std::function<void(bool)>*>(callback);
    ToggleModelNG::OnChangeEvent(frameNode, std::move(*changeEvent));
}

void SetToggleSelectedColor(ArkUINodeHandle node, ArkUI_Uint32 selectedColor)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ToggleModelNG::SetSelectedColor(frameNode, Color(selectedColor));
}

void SetToggleSelectedColorPtr(ArkUINodeHandle node, ArkUI_Uint32 selectedColor, void* colorRawPtr)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    Color result = Color(selectedColor);
    if (SystemProperties::ConfigChangePerform()) {
        RefPtr<ResourceObject> resObj;
        if (!colorRawPtr) {
            ResourceParseUtils::CompleteResourceObjectFromColor(
                resObj, result, ResourceParseUtils::MakeNativeNodeInfo(frameNode));
        } else {
            resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(colorRawPtr));
        }
        ToggleModelNG::CreateWithResourceObj(frameNode, ToggleColorType::SELECTED_COLOR, resObj);
    }
    ToggleModelNG::SetSelectedColor(frameNode, result);
}

void SetToggleSelectedColorPtrByJs(ArkUINodeHandle node, ArkUI_Uint32 selectedColor, void* colorRawPtr)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    Color result = Color(selectedColor);
    if (SystemProperties::ConfigChangePerform()) {
        RefPtr<ResourceObject> resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(colorRawPtr));
        ToggleModelNG::CreateWithResourceObj(frameNode, ToggleColorType::SELECTED_COLOR, resObj);
    }
    ToggleModelNG::SetSelectedColor(frameNode, result);
}

void ResetToggleSelectedColor(ArkUINodeHandle node)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<Color> selectedColor;
    ToggleModelNG::SetSelectedColor(frameNode, selectedColor);
    if (SystemProperties::ConfigChangePerform()) {
        ToggleModelNG::CreateWithResourceObj(frameNode, ToggleColorType::SELECTED_COLOR, nullptr);
    }
}

void SetToggleSwitchPointColor(ArkUINodeHandle node, ArkUI_Uint32 switchPointColor)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ToggleModelNG::SetSwitchPointColor(frameNode, Color(switchPointColor));
    ToggleModelNG::SetSwitchPointColorSetByUser(frameNode, true);
}

void SetToggleSwitchPointColorPtr(ArkUINodeHandle node, ArkUI_Uint32 switchPointColor, void* colorRawPtr)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    Color result = Color(switchPointColor);
    if (SystemProperties::ConfigChangePerform()) {
        RefPtr<ResourceObject> resObj;
        if (!colorRawPtr) {
            ResourceParseUtils::CompleteResourceObjectFromColor(
                resObj, result, ResourceParseUtils::MakeNativeNodeInfo(frameNode));
        } else {
            resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(colorRawPtr));
        }
        ToggleModelNG::CreateWithResourceObj(frameNode, ToggleColorType::SWITCH_POINT_COLOR, resObj);
    }
    ToggleModelNG::SetSwitchPointColor(frameNode, result);
    ToggleModelNG::SetSwitchPointColorSetByUser(frameNode, true);
}

void SetToggleSwitchPointColorPtrByJs(ArkUINodeHandle node, ArkUI_Uint32 switchPointColor, void* colorRawPtr)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    Color result = Color(switchPointColor);
    if (SystemProperties::ConfigChangePerform()) {
        RefPtr<ResourceObject> resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(colorRawPtr));
        ToggleModelNG::CreateWithResourceObj(frameNode, ToggleColorType::SWITCH_POINT_COLOR, resObj);
    }
    ToggleModelNG::SetSwitchPointColor(frameNode, result);
    ToggleModelNG::SetSwitchPointColorSetByUser(frameNode, true);
}

void ResetToggleSwitchPointColor(ArkUINodeHandle node)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto switchTheme = frameNode->GetTheme<SwitchTheme>(true);
    Color color;
    if (switchTheme) {
        color = switchTheme->GetPointColor();
    }
    ToggleModelNG::SetSwitchPointColor(frameNode, color);
    ToggleModelNG::SetSwitchPointColorSetByUser(frameNode, false);
    if (SystemProperties::ConfigChangePerform()) {
        ToggleModelNG::CreateWithResourceObj(frameNode, ToggleColorType::SWITCH_POINT_COLOR, nullptr);
    }
}

void ResetToggleSwitchPointColorByJs(ArkUINodeHandle node)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ToggleModelNG::ResetToggleSwitchPointColor(frameNode);
    ToggleModelNG::SetSwitchPointColorSetByUser(frameNode, false);
    if (SystemProperties::ConfigChangePerform()) {
        ToggleModelNG::CreateWithResourceObj(frameNode, ToggleColorType::SWITCH_POINT_COLOR, nullptr);
    }
}

ArkUI_Uint32 GetToggleSelectedColor(ArkUINodeHandle node)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, ERROR_UINT_CODE);
    return ToggleModelNG::GetSelectedColor(frameNode).GetValue();
}

ArkUI_Uint32 GetToggleSwitchPointColor(ArkUINodeHandle node)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, ERROR_UINT_CODE);
    return ToggleModelNG::GetSwitchPointColor(frameNode).GetValue();
}

void SetToggleHeight(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    DimensionUnit unitValue = static_cast<DimensionUnit>(unit);
    CalcDimension dimensionValue = CalcDimension(value, unitValue);
    ToggleModelNG::SetHeight(frameNode, dimensionValue);
}

void ResetToggleHeight(ArkUINodeHandle node)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto switchTheme = frameNode->GetTheme<SwitchTheme>(true);
    CHECK_NULL_VOID(switchTheme);
    auto defaultHeight = switchTheme->GetHeight();
    auto verticalPadding = switchTheme->GetHotZoneVerticalPadding();
    auto height = defaultHeight - verticalPadding * 2;
    CalcDimension value(height);
    ToggleModelNG::SetHeight(frameNode, value);
}

void SetToggleWidth(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    DimensionUnit unitValue = static_cast<DimensionUnit>(unit);
    CalcDimension dimensionValue = CalcDimension(value, unitValue);
    ToggleModelNG::SetWidth(frameNode, dimensionValue);
}

void SetToggleResponseRegion(
    ArkUINodeHandle node, const ArkUI_Float32* values, const ArkUI_Int32* units, ArkUI_Uint32 length)
{
    CHECK_NULL_VOID(values);
    CHECK_NULL_VOID(units);
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<DimensionRect> region;
    for (uint32_t i = 0; i + OFFSET_3 < length; i = i + RESPONSE_REGION_STEP) {
        CalcDimension xDimen = CalcDimension(values[i + OFFSET_0], static_cast<DimensionUnit>(units[i + OFFSET_0]));
        CalcDimension yDimen = CalcDimension(values[i + OFFSET_1], static_cast<DimensionUnit>(units[i + OFFSET_1]));
        CalcDimension widthDimen = CalcDimension(values[i + OFFSET_2], static_cast<DimensionUnit>(units[i + OFFSET_2]));
        CalcDimension heightDimen =
            CalcDimension(values[i + OFFSET_3], static_cast<DimensionUnit>(units[i + OFFSET_3]));
        DimensionOffset offsetDimen(xDimen, yDimen);
        DimensionRect dimenRect(widthDimen, heightDimen, offsetDimen);
        region.emplace_back(dimenRect);
    }
    ToggleModelNG::SetResponseRegion(frameNode, region);
}

void ResetToggleResponseRegion(ArkUINodeHandle node)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<DimensionRect> region;
    CalcDimension xDimen = CalcDimension(0.0, DimensionUnit::VP);
    CalcDimension yDimen = CalcDimension(0.0, DimensionUnit::VP);
    CalcDimension widthDimen = CalcDimension(1, DimensionUnit::PERCENT);
    CalcDimension heightDimen = CalcDimension(1, DimensionUnit::PERCENT);
    DimensionOffset offsetDimen(xDimen, yDimen);
    DimensionRect dimenRect(widthDimen, heightDimen, offsetDimen);
    region.emplace_back(dimenRect);
    ToggleModelNG::SetResponseRegion(frameNode, region);
}

void SetTogglePadding(ArkUINodeHandle node, const ArkUI_Float32* values, const ArkUI_Uint32 length)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(values);
    CalcLength topDimen;
    CalcLength rightDimen;
    CalcLength bottomDimen;
    CalcLength leftDimen;
    uint32_t step = DIMENSION_STEP;
    uint32_t topIndex = INDEX_DIMENSION_TOP_0;
    std::optional<CalcDimension> topOptional = std::nullopt;
    if (SetToggleDimension(values, topIndex, length, topOptional)) {
        topDimen = CalcLength(
            CalcDimension(topOptional.value().Value(), static_cast<DimensionUnit>(topOptional.value().Unit())));
    }
    uint32_t rightIndex = INDEX_DIMENSION_RIGHT_1 * step;
    std::optional<CalcDimension> rightOptional = std::nullopt;
    if (SetToggleDimension(values, rightIndex, length, rightOptional)) {
        rightDimen = CalcLength(
            CalcDimension(rightOptional.value().Value(), static_cast<DimensionUnit>(rightOptional.value().Unit())));
    }
    uint32_t bottomIndex = INDEX_DIMENSION_BOTTOM_2 * step;
    std::optional<CalcDimension> bottomOptional = std::nullopt;
    if (SetToggleDimension(values, bottomIndex, length, bottomOptional)) {
        bottomDimen = CalcLength(
            CalcDimension(bottomOptional.value().Value(), static_cast<DimensionUnit>(bottomOptional.value().Unit())));
    }
    uint32_t leftIndex = INDEX_DIMENSION_LEFT_3 * step;
    std::optional<CalcDimension> leftOptional = std::nullopt;
    if (SetToggleDimension(values, leftIndex, length, leftOptional)) {
        leftDimen = CalcLength(
            CalcDimension(leftOptional.value().Value(), static_cast<DimensionUnit>(leftOptional.value().Unit())));
    }
    NG::PaddingPropertyF oldPaddings;
    NG::PaddingProperty paddings;
    paddings.top = std::optional<CalcLength>(topDimen);
    paddings.bottom = std::optional<CalcLength>(bottomDimen);
    paddings.left = std::optional<CalcLength>(leftDimen);
    paddings.right = std::optional<CalcLength>(rightDimen);
    ToggleModelNG::SetPadding(frameNode, oldPaddings, paddings);
}

void SetTogglePaddingByJs(
    ArkUINodeHandle node, const struct ArkUIPaddingType* oldPaddings, const struct ArkUIPaddingType* newPaddings)
{
    auto frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    PaddingPropertyF oldPadding;
    PaddingProperty newPadding(
        { CalcLength(0.0_vp), CalcLength(0.0_vp), CalcLength(0.0_vp), CalcLength(0.0_vp), std::nullopt, std::nullopt });
    if (newPaddings) {
        newPadding.top = newPaddings->top.string
                             ? CalcLength(newPaddings->top.string)
                             : CalcLength(newPaddings->top.value, static_cast<DimensionUnit>(newPaddings->top.unit));
        newPadding.bottom = newPaddings->bottom.string ? CalcLength(newPaddings->bottom.string)
                                                       : CalcLength(newPaddings->bottom.value,
                                                             static_cast<DimensionUnit>(newPaddings->bottom.unit));
        newPadding.left = newPaddings->start.string ? CalcLength(newPaddings->start.string)
                                                    : CalcLength(newPaddings->start.value,
                                                          static_cast<DimensionUnit>(newPaddings->start.unit));
        newPadding.right = newPaddings->end.string
                               ? CalcLength(newPaddings->end.string)
                               : CalcLength(newPaddings->end.value, static_cast<DimensionUnit>(newPaddings->end.unit));
    }
    ToggleModelNG::SetPadding(frameNode, oldPadding, newPadding);
}

void ResetTogglePadding(ArkUINodeHandle node)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    NG::PaddingPropertyF oldPaddings;
    NG::PaddingProperty newPaddings;
    newPaddings.top = std::optional<CalcLength>(CalcLength(0.0, DimensionUnit::VP));
    newPaddings.bottom = std::optional<CalcLength>(CalcLength(0.0, DimensionUnit::VP));
    newPaddings.left = std::optional<CalcLength>(CalcLength(0.0, DimensionUnit::VP));
    newPaddings.right = std::optional<CalcLength>(CalcLength(0.0, DimensionUnit::VP));
    ToggleModelNG::SetPadding(frameNode, oldPaddings, newPaddings);
}

void SetToggleBackgroundColor(ArkUINodeHandle node, ArkUI_Uint32 color)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ToggleModelNG::SetBackgroundColor(frameNode, Color(color));
}

void SetToggleBackgroundColorWithColorSpace(ArkUINodeHandle node, ArkUI_Uint32 color, ArkUI_Int32 colorSpace)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    Color backgroundColor(color);
    if (ColorSpace::DISPLAY_P3 == colorSpace) {
        backgroundColor.SetColorSpace(ColorSpace::DISPLAY_P3);
    } else {
        backgroundColor.SetColorSpace(ColorSpace::SRGB);
    }
    ToggleModelNG::SetBackgroundColor(frameNode, backgroundColor);
}

void SetToggleBackgroundColorByJs(
    ArkUINodeHandle node, ArkUI_Uint32 color, ArkUI_Int32 colorSpace, void* colorRawPtr, ArkUI_Bool flag)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    Color backgroundColor(color);
    backgroundColor.SetColorSpace(static_cast<ColorSpace>(colorSpace));
    ToggleModelNG::SetBackgroundColorByJs(backgroundColor, static_cast<bool>(flag));
    if (SystemProperties::ConfigChangePerform()) {
        RefPtr<ResourceObject> resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(colorRawPtr));
        ToggleModelNG::CreateWithResourceObj(frameNode, ToggleColorType::BACKGROUND_COLOR, resObj);
    }
}

void ResetToggleBackgroundColor(ArkUINodeHandle node)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ToggleModelNG::SetBackgroundColor(frameNode, Color(Color::TRANSPARENT));
}

void SetToggleHoverEffect(ArkUINodeHandle node, ArkUI_Int32 hoverEffectValue)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    HoverEffectType hoverEffect = static_cast<HoverEffectType>(hoverEffectValue);
    ToggleModelNG::SetHoverEffect(frameNode, hoverEffect);
}

void ResetToggleHoverEffect(ArkUINodeHandle node)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ToggleModelNG::SetHoverEffect(frameNode, HoverEffectType::AUTO);
}

void SetTogglePointRadius(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    DimensionUnit unitValue = static_cast<DimensionUnit>(unit);
    CalcDimension switchPointRadius = CalcDimension(value, unitValue);
    ToggleModelNG::SetPointRadius(frameNode, switchPointRadius);
}

void SetTogglePointRadiusPtr(ArkUINodeHandle node, ArkUI_Float64 value, ArkUI_Int32 unit, void* radiusRawPtr)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    Dimension switchPointRadius = Dimension(value, static_cast<DimensionUnit>(unit));
    ToggleModelNG::SetPointRadius(frameNode, switchPointRadius);
    if (SystemProperties::ConfigChangePerform()) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(radiusRawPtr));
        ToggleModelNG::CreateWithResourceObj(frameNode, ToggleDimensionType::POINT_RADIUS, resObj);
    }
}

void ResetTogglePointRadius(ArkUINodeHandle node)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ToggleModelNG::ResetPointRadius(frameNode);
    if (SystemProperties::ConfigChangePerform()) {
        ToggleModelNG::CreateWithResourceObj(frameNode, ToggleDimensionType::POINT_RADIUS, nullptr);
    }
}

void SetToggleUnselectedColor(ArkUINodeHandle node, ArkUI_Uint32 unselectedColor)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ToggleModelNG::SetUnselectedColor(frameNode, Color(unselectedColor));
    ToggleModelNG::SetUnselectedColorSetByUser(frameNode, true);
}

void SetToggleUnselectedColorPtr(ArkUINodeHandle node, ArkUI_Uint32 unselectedColor, void* colorRawPtr)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    Color result = Color(unselectedColor);
    if (SystemProperties::ConfigChangePerform()) {
        RefPtr<ResourceObject> resObj;
        if (!colorRawPtr) {
            ResourceParseUtils::CompleteResourceObjectFromColor(
                resObj, result, ResourceParseUtils::MakeNativeNodeInfo(frameNode));
        } else {
            resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(colorRawPtr));
        }
        ToggleModelNG::CreateWithResourceObj(frameNode, ToggleColorType::UN_SELECTED_COLOR, resObj);
    }
    ToggleModelNG::SetUnselectedColor(frameNode, result);
    ToggleModelNG::SetUnselectedColorSetByUser(frameNode, true);
}

void SetToggleUnselectedColorPtrByJs(ArkUINodeHandle node, ArkUI_Uint32 unselectedColor, void* colorRawPtr)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    Color result = Color(unselectedColor);
    if (SystemProperties::ConfigChangePerform()) {
        RefPtr<ResourceObject> resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(colorRawPtr));
        ToggleModelNG::CreateWithResourceObj(frameNode, ToggleColorType::UN_SELECTED_COLOR, resObj);
    }
    ToggleModelNG::SetUnselectedColor(frameNode, result);
    ToggleModelNG::SetUnselectedColorSetByUser(frameNode, true);
}

void ResetToggleUnselectedColor(ArkUINodeHandle node)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto switchTheme = frameNode->GetTheme<SwitchTheme>(true);
    CHECK_NULL_VOID(switchTheme);
    Color unselectedColor = switchTheme->GetInactiveColor();
    ToggleModelNG::SetUnselectedColor(frameNode, unselectedColor);
    ToggleModelNG::SetUnselectedColorSetByUser(frameNode, false);
    if (SystemProperties::ConfigChangePerform()) {
        ToggleModelNG::CreateWithResourceObj(frameNode, ToggleColorType::UN_SELECTED_COLOR, nullptr);
    }
}

void SetToggleTrackBorderRadius(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    DimensionUnit unitValue = static_cast<DimensionUnit>(unit);
    CalcDimension borderRadius = CalcDimension(value, unitValue);
    ToggleModelNG::SetTrackBorderRadius(frameNode, borderRadius);
}

void SetToggleTrackBorderRadiusPtr(ArkUINodeHandle node, ArkUI_Float64 value, ArkUI_Int32 unit, void* radiusRawPtr)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    Dimension borderRadius = Dimension(value, static_cast<DimensionUnit>(unit));
    ToggleModelNG::SetTrackBorderRadius(frameNode, borderRadius);
    if (SystemProperties::ConfigChangePerform()) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(radiusRawPtr));
        ToggleModelNG::CreateWithResourceObj(frameNode, ToggleDimensionType::TRACK_BORDER_RADIUS, resObj);
    }
}

void ResetToggleTrackBorderRadius(ArkUINodeHandle node)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ToggleModelNG::ResetTrackBorderRadius(frameNode);
    if (SystemProperties::ConfigChangePerform()) {
        ToggleModelNG::CreateWithResourceObj(frameNode, ToggleDimensionType::TRACK_BORDER_RADIUS, nullptr);
    }
}

void SetToggleIsOn(ArkUINodeHandle node, ArkUI_Bool switchPointColor)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ToggleModelNG::SetSwitchIsOn(frameNode, static_cast<bool>(switchPointColor));
}

void ResetToggleIsOn(ArkUINodeHandle node)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ToggleModelNG::SetSwitchIsOn(frameNode, false);
}

ArkUI_Bool GetToggleIsOn(ArkUINodeHandle node)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, ERROR_UINT_CODE);
    return static_cast<ArkUI_Bool>(ToggleModelNG::GetSwitchIsOn(frameNode));
}

ArkUI_Uint32 GetToggleUnselectedColor(ArkUINodeHandle node)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, ERROR_UINT_CODE);
    return ToggleModelNG::GetUnselectedColor(frameNode).GetValue();
}

void SetToggleState(ArkUINodeHandle node, ArkUI_Bool isOn)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ToggleModelNG::SetToggleState(frameNode, static_cast<bool>(isOn));
}

ArkUI_Bool GetToggleState(ArkUINodeHandle node)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, false);
    return static_cast<ArkUI_Bool>(ToggleModelNG::GetToggleState(frameNode));
}

void SetToggleOnChange(ArkUINodeHandle node, void* callback)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onChange = reinterpret_cast<std::function<void(bool)>*>(callback);
        ToggleModelNG::OnChange(frameNode, std::move(*onChange));
    } else {
        ToggleModelNG::OnChange(frameNode, nullptr);
    }
}

void ResetToggleOnChange(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ToggleModelNG::OnChange(frameNode, nullptr);
}

void SetIsUserSetMargin(ArkUINodeHandle node)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ToggleModelNG::SetIsUserSetMargin(frameNode, true);
}

void Pop()
{
    ViewStackProcessor::GetInstance()->PopContainer();
}

#ifndef CROSS_PLATFORM
ToggleModel* GetToggleModelImpl()
{
    static auto loader = DynamicModuleHelper::GetInstance().GetLoaderByName("toggle");
    static ToggleModel* instance = loader ? reinterpret_cast<ToggleModel*>(loader->CreateModel()) : nullptr;
    return instance;
}

void CreateImpl(ArkUI_Int32 toggleType, ArkUI_Bool isOn)
{
    auto toggleModelImpl = GetToggleModelImpl();
    CHECK_NULL_VOID(toggleModelImpl);
    toggleModelImpl->Create(static_cast<NG::ToggleType>(toggleType), static_cast<bool>(isOn));
}

void SetOnChangeEventImpl(void* callback)
{
    auto toggleModelImpl = GetToggleModelImpl();
    CHECK_NULL_VOID(toggleModelImpl);
    auto changeEvent = reinterpret_cast<std::function<void(bool)>*>(callback);
    toggleModelImpl->OnChangeEvent(std::move(*changeEvent));
}

void SetToggleSelectedColorPtrByJsImpl(ArkUINodeHandle node, ArkUI_Uint32 selectedColor, void* colorRawPtr)
{
    auto toggleModelImpl = GetToggleModelImpl();
    CHECK_NULL_VOID(toggleModelImpl);
    Color result = Color(selectedColor);
    if (SystemProperties::ConfigChangePerform()) {
        RefPtr<ResourceObject> resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(colorRawPtr));
        toggleModelImpl->CreateWithColorResourceObj(resObj, ToggleColorType::SELECTED_COLOR);
    }
    toggleModelImpl->SetSelectedColor(result);
}

void ResetToggleSelectedColorImpl(ArkUINodeHandle node)
{
    auto toggleModelImpl = GetToggleModelImpl();
    CHECK_NULL_VOID(toggleModelImpl);
    std::optional<Color> selectedColor;
    toggleModelImpl->SetSelectedColor(selectedColor);
    if (SystemProperties::ConfigChangePerform()) {
        toggleModelImpl->CreateWithColorResourceObj(nullptr, ToggleColorType::SELECTED_COLOR);
    }
}

void SetToggleSwitchPointColorPtrByJsImpl(ArkUINodeHandle node, ArkUI_Uint32 switchPointColor, void* colorRawPtr)
{
    auto toggleModelImpl = GetToggleModelImpl();
    CHECK_NULL_VOID(toggleModelImpl);
    Color result = Color(switchPointColor);
    if (SystemProperties::ConfigChangePerform()) {
        RefPtr<ResourceObject> resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(colorRawPtr));
        toggleModelImpl->CreateWithColorResourceObj(resObj, ToggleColorType::SWITCH_POINT_COLOR);
    }
    toggleModelImpl->SetSwitchPointColor(result);
    toggleModelImpl->SetSwitchPointColorSetByUser(true);
}

void ResetToggleSwitchPointColorImpl(ArkUINodeHandle node)
{
    auto toggleModelImpl = GetToggleModelImpl();
    CHECK_NULL_VOID(toggleModelImpl);
    FrameNode* frameNode = GetFrameNode(node);
    auto switchTheme = frameNode->GetTheme<SwitchTheme>(true);
    Color color;
    if (switchTheme) {
        color = switchTheme->GetPointColor();
    }
    toggleModelImpl->SetSwitchPointColor(color);
    toggleModelImpl->SetSwitchPointColorSetByUser(false);
    if (SystemProperties::ConfigChangePerform()) {
        toggleModelImpl->CreateWithColorResourceObj(nullptr, ToggleColorType::SWITCH_POINT_COLOR);
    }
}

void ResetToggleSwitchPointColorByJsImpl(ArkUINodeHandle node)
{
    auto toggleModelImpl = GetToggleModelImpl();
    CHECK_NULL_VOID(toggleModelImpl);
    std::optional<Color> color;
    toggleModelImpl->SetSwitchPointColor(color);
    toggleModelImpl->SetSwitchPointColorSetByUser(false);
    if (SystemProperties::ConfigChangePerform()) {
        toggleModelImpl->CreateWithColorResourceObj(nullptr, ToggleColorType::SWITCH_POINT_COLOR);
    }
}

void SetToggleHeightImpl(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit)
{
    auto toggleModelImpl = GetToggleModelImpl();
    CHECK_NULL_VOID(toggleModelImpl);
    DimensionUnit unitValue = static_cast<DimensionUnit>(unit);
    CalcDimension dimensionValue = CalcDimension(value, unitValue);
    toggleModelImpl->SetHeight(dimensionValue);
}

void SetToggleWidthImpl(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit)
{
    auto toggleModelImpl = GetToggleModelImpl();
    CHECK_NULL_VOID(toggleModelImpl);
    DimensionUnit unitValue = static_cast<DimensionUnit>(unit);
    CalcDimension dimensionValue = CalcDimension(value, unitValue);
    toggleModelImpl->SetWidth(dimensionValue);
}

void SetToggleResponseRegionImpl(
    ArkUINodeHandle node, const ArkUI_Float32* values, const ArkUI_Int32* units, ArkUI_Uint32 length)
{
    auto toggleModelImpl = GetToggleModelImpl();
    CHECK_NULL_VOID(toggleModelImpl);
    CHECK_NULL_VOID(values);
    CHECK_NULL_VOID(units);
    std::vector<DimensionRect> region;
    for (uint32_t i = 0; i + OFFSET_3 < length; i = i + RESPONSE_REGION_STEP) {
        CalcDimension xDimen = CalcDimension(values[i + OFFSET_0], static_cast<DimensionUnit>(units[i + OFFSET_0]));
        CalcDimension yDimen = CalcDimension(values[i + OFFSET_1], static_cast<DimensionUnit>(units[i + OFFSET_1]));
        CalcDimension widthDimen = CalcDimension(values[i + OFFSET_2], static_cast<DimensionUnit>(units[i + OFFSET_2]));
        CalcDimension heightDimen =
            CalcDimension(values[i + OFFSET_3], static_cast<DimensionUnit>(units[i + OFFSET_3]));
        DimensionOffset offsetDimen(xDimen, yDimen);
        DimensionRect dimenRect(widthDimen, heightDimen, offsetDimen);
        region.emplace_back(dimenRect);
    }
    toggleModelImpl->SetResponseRegion(region);
}

void ResetToggleResponseRegionImpl(ArkUINodeHandle node)
{
    auto toggleModelImpl = GetToggleModelImpl();
    CHECK_NULL_VOID(toggleModelImpl);
    std::vector<DimensionRect> region;
    CalcDimension xDimen = CalcDimension(0.0, DimensionUnit::VP);
    CalcDimension yDimen = CalcDimension(0.0, DimensionUnit::VP);
    CalcDimension widthDimen = CalcDimension(1, DimensionUnit::PERCENT);
    CalcDimension heightDimen = CalcDimension(1, DimensionUnit::PERCENT);
    DimensionOffset offsetDimen(xDimen, yDimen);
    DimensionRect dimenRect(widthDimen, heightDimen, offsetDimen);
    region.emplace_back(dimenRect);
    toggleModelImpl->SetResponseRegion(region);
}

void SetTogglePaddingByJsImpl(
    ArkUINodeHandle node, const struct ArkUIPaddingType* oldPaddings, const struct ArkUIPaddingType* newPaddings)
{
    auto toggleModelImpl = GetToggleModelImpl();
    CHECK_NULL_VOID(toggleModelImpl);
    PaddingPropertyF oldPadding({ 0.0f, 0.0f, 0.0f, 0.0f });
    if (oldPaddings) {
        oldPadding.left = oldPaddings->start.value;
        oldPadding.right = oldPaddings->end.value;
        oldPadding.top = oldPaddings->top.value;
        oldPadding.bottom = oldPaddings->bottom.value;
    }
    PaddingProperty newPadding;
    toggleModelImpl->SetPadding(oldPadding, newPadding);
}

void SetToggleHoverEffectImpl(ArkUINodeHandle node, ArkUI_Int32 hoverEffectValue)
{
    auto toggleModelImpl = GetToggleModelImpl();
    CHECK_NULL_VOID(toggleModelImpl);
    HoverEffectType hoverEffect = static_cast<HoverEffectType>(hoverEffectValue);
    toggleModelImpl->SetHoverEffect(hoverEffect);
}

void SetTogglePointRadiusPtrImpl(ArkUINodeHandle node, ArkUI_Float64 value, ArkUI_Int32 unit, void* radiusRawPtr)
{
    auto toggleModelImpl = GetToggleModelImpl();
    CHECK_NULL_VOID(toggleModelImpl);
    Dimension switchPointRadius = Dimension(value, static_cast<DimensionUnit>(unit));
    toggleModelImpl->SetPointRadius(switchPointRadius);
    if (SystemProperties::ConfigChangePerform()) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(radiusRawPtr));
        toggleModelImpl->CreateWithDimensionVpResourceObj(resObj, ToggleDimensionType::POINT_RADIUS);
    }
}

void ResetTogglePointRadiusImpl(ArkUINodeHandle node)
{
    auto toggleModelImpl = GetToggleModelImpl();
    CHECK_NULL_VOID(toggleModelImpl);
    toggleModelImpl->ResetPointRadius();
    if (SystemProperties::ConfigChangePerform()) {
        toggleModelImpl->CreateWithDimensionVpResourceObj(nullptr, ToggleDimensionType::POINT_RADIUS);
    }
}

void SetToggleUnselectedColorPtrByJsImpl(ArkUINodeHandle node, ArkUI_Uint32 unselectedColor, void* colorRawPtr)
{
    auto toggleModelImpl = GetToggleModelImpl();
    CHECK_NULL_VOID(toggleModelImpl);
    Color result = Color(unselectedColor);
    if (SystemProperties::ConfigChangePerform()) {
        RefPtr<ResourceObject> resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(colorRawPtr));
        toggleModelImpl->CreateWithColorResourceObj(resObj, ToggleColorType::UN_SELECTED_COLOR);
    }
    toggleModelImpl->SetUnselectedColor(result);
    toggleModelImpl->SetUnselectedColorSetByUser(true);
}

void ResetToggleUnselectedColorImpl(ArkUINodeHandle node)
{
    auto toggleModelImpl = GetToggleModelImpl();
    CHECK_NULL_VOID(toggleModelImpl);
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto switchTheme = frameNode->GetTheme<SwitchTheme>(true);
    Color unselectedColor;
    if (switchTheme) {
        unselectedColor = switchTheme->GetInactiveColor();
    }
    toggleModelImpl->SetUnselectedColor(unselectedColor);
    toggleModelImpl->SetUnselectedColorSetByUser(false);
    if (SystemProperties::ConfigChangePerform()) {
        toggleModelImpl->CreateWithColorResourceObj(nullptr, ToggleColorType::UN_SELECTED_COLOR);
    }
}

void SetToggleTrackBorderRadiusPtrImpl(ArkUINodeHandle node, ArkUI_Float64 value, ArkUI_Int32 unit, void* radiusRawPtr)
{
    auto toggleModelImpl = GetToggleModelImpl();
    CHECK_NULL_VOID(toggleModelImpl);
    Dimension borderRadius = Dimension(value, static_cast<DimensionUnit>(unit));
    toggleModelImpl->SetTrackBorderRadius(borderRadius);
    if (SystemProperties::ConfigChangePerform()) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(radiusRawPtr));
        toggleModelImpl->CreateWithDimensionVpResourceObj(resObj, ToggleDimensionType::TRACK_BORDER_RADIUS);
    }
}

void ResetToggleTrackBorderRadiusImpl(ArkUINodeHandle node)
{
    auto toggleModelImpl = GetToggleModelImpl();
    CHECK_NULL_VOID(toggleModelImpl);
    toggleModelImpl->ResetTrackBorderRadius();
    if (SystemProperties::ConfigChangePerform()) {
        toggleModelImpl->CreateWithDimensionVpResourceObj(nullptr, ToggleDimensionType::TRACK_BORDER_RADIUS);
    }
}

void SetToggleOnChangeImpl(ArkUINodeHandle node, void* callback)
{
    auto toggleModelImpl = GetToggleModelImpl();
    CHECK_NULL_VOID(toggleModelImpl);
    if (callback) {
        auto onChange = reinterpret_cast<std::function<void(bool)>*>(callback);
        toggleModelImpl->OnChange(std::move(*onChange));
    } else {
        toggleModelImpl->OnChange(nullptr);
    }
}

void SetIsUserSetMarginImpl(ArkUINodeHandle node)
{
    auto toggleModelImpl = GetToggleModelImpl();
    CHECK_NULL_VOID(toggleModelImpl);
    toggleModelImpl->SetIsUserSetMargin(true);
}

void PopImpl()
{
    auto toggleModelImpl = GetToggleModelImpl();
    CHECK_NULL_VOID(toggleModelImpl);
    toggleModelImpl->Pop();
}
#endif
} // namespace

const ArkUIToggleModifier* GetToggleDynamicModifier()
{
    static bool isCurrentUseNewPipeline = Container::IsCurrentUseNewPipeline();
    if (isCurrentUseNewPipeline) {
        CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
        static const ArkUIToggleModifier modifier = {
            .create = Create,
            .createFrameNode = CreateFrameNode,
            .setOnChangeEvent = SetOnChangeEvent,
            .setToggleSelectedColor = SetToggleSelectedColor,
            .setToggleSelectedColorPtr = SetToggleSelectedColorPtr,
            .setToggleSelectedColorPtrByJs = SetToggleSelectedColorPtrByJs,
            .resetToggleSelectedColor = ResetToggleSelectedColor,
            .setToggleSwitchPointColor = SetToggleSwitchPointColor,
            .setToggleSwitchPointColorPtr = SetToggleSwitchPointColorPtr,
            .setToggleSwitchPointColorPtrByJs = SetToggleSwitchPointColorPtrByJs,
            .resetToggleSwitchPointColor = ResetToggleSwitchPointColor,
            .resetToggleSwitchPointColorByJs = ResetToggleSwitchPointColorByJs,
            .setToggleHeight = SetToggleHeight,
            .resetToggleHeight = ResetToggleHeight,
            .setToggleWidth = SetToggleWidth,
            .setToggleResponseRegion = SetToggleResponseRegion,
            .resetToggleResponseRegion = ResetToggleResponseRegion,
            .setTogglePadding = SetTogglePadding,
            .setTogglePaddingByJs = SetTogglePaddingByJs,
            .resetTogglePadding = ResetTogglePadding,
            .setToggleBackgroundColor = SetToggleBackgroundColor,
            .setToggleBackgroundColorWithColorSpace = SetToggleBackgroundColorWithColorSpace,
            .setToggleBackgroundColorByJs = SetToggleBackgroundColorByJs,
            .resetToggleBackgroundColor = ResetToggleBackgroundColor,
            .setToggleHoverEffect = SetToggleHoverEffect,
            .resetToggleHoverEffect = ResetToggleHoverEffect,
            .getToggleSelectedColor = GetToggleSelectedColor,
            .getToggleSwitchPointColor = GetToggleSwitchPointColor,
            .setToggleIsOn = SetToggleIsOn,
            .resetToggleIsOn = ResetToggleIsOn,
            .getToggleIsOn = GetToggleIsOn,
            .setTogglePointRadius = SetTogglePointRadius,
            .setTogglePointRadiusPtr = SetTogglePointRadiusPtr,
            .resetTogglePointRadius = ResetTogglePointRadius,
            .setToggleUnselectedColor = SetToggleUnselectedColor,
            .setToggleUnselectedColorPtr = SetToggleUnselectedColorPtr,
            .setToggleUnselectedColorPtrByJs = SetToggleUnselectedColorPtrByJs,
            .resetToggleUnselectedColor = ResetToggleUnselectedColor,
            .setToggleTrackBorderRadius = SetToggleTrackBorderRadius,
            .setToggleTrackBorderRadiusPtr = SetToggleTrackBorderRadiusPtr,
            .resetToggleTrackBorderRadius = ResetToggleTrackBorderRadius,
            .getToggleUnselectedColor = GetToggleUnselectedColor,
            .setToggleState = SetToggleState,
            .setToggleOnChange = SetToggleOnChange,
            .resetToggleOnChange = ResetToggleOnChange,
            .setIsUserSetMargin = SetIsUserSetMargin,
            .getToggleState = GetToggleState,
            .pop = Pop,
        };
        CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
        return &modifier;
    } else {
#ifndef CROSS_PLATFORM
        CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
        static const ArkUIToggleModifier modifier = {
            .create = CreateImpl,
            .createFrameNode = nullptr,
            .setOnChangeEvent = SetOnChangeEventImpl,
            .setToggleSelectedColor = nullptr,
            .setToggleSelectedColorPtr = nullptr,
            .setToggleSelectedColorPtrByJs = SetToggleSelectedColorPtrByJsImpl,
            .resetToggleSelectedColor = ResetToggleSelectedColorImpl,
            .setToggleSwitchPointColor = nullptr,
            .setToggleSwitchPointColorPtr = nullptr,
            .setToggleSwitchPointColorPtrByJs = SetToggleSwitchPointColorPtrByJsImpl,
            .resetToggleSwitchPointColor = ResetToggleSwitchPointColorImpl,
            .resetToggleSwitchPointColorByJs = ResetToggleSwitchPointColorByJsImpl,
            .setToggleHeight = SetToggleHeightImpl,
            .resetToggleHeight = nullptr,
            .setToggleWidth = SetToggleWidthImpl,
            .setToggleResponseRegion = SetToggleResponseRegionImpl,
            .resetToggleResponseRegion = ResetToggleResponseRegionImpl,
            .setTogglePadding = nullptr,
            .setTogglePaddingByJs = SetTogglePaddingByJsImpl,
            .resetTogglePadding = nullptr,
            .setToggleBackgroundColor = nullptr,
            .setToggleBackgroundColorWithColorSpace = nullptr,
            .setToggleBackgroundColorByJs = nullptr,
            .resetToggleBackgroundColor = nullptr,
            .setToggleHoverEffect = SetToggleHoverEffectImpl,
            .resetToggleHoverEffect = nullptr,
            .getToggleSelectedColor = nullptr,
            .getToggleSwitchPointColor = nullptr,
            .setToggleIsOn = nullptr,
            .resetToggleIsOn = nullptr,
            .getToggleIsOn = nullptr,
            .setTogglePointRadius = nullptr,
            .setTogglePointRadiusPtr = SetTogglePointRadiusPtrImpl,
            .resetTogglePointRadius = ResetTogglePointRadiusImpl,
            .setToggleUnselectedColor = nullptr,
            .setToggleUnselectedColorPtr = nullptr,
            .setToggleUnselectedColorPtrByJs = SetToggleUnselectedColorPtrByJsImpl,
            .resetToggleUnselectedColor = ResetToggleUnselectedColorImpl,
            .setToggleTrackBorderRadius = nullptr,
            .setToggleTrackBorderRadiusPtr = SetToggleTrackBorderRadiusPtrImpl,
            .resetToggleTrackBorderRadius = ResetToggleTrackBorderRadiusImpl,
            .getToggleUnselectedColor = nullptr,
            .setToggleState = nullptr,
            .setToggleOnChange = SetToggleOnChangeImpl,
            .resetToggleOnChange = nullptr,
            .setIsUserSetMargin = SetIsUserSetMarginImpl,
            .getToggleState = nullptr,
            .pop = PopImpl,
        };
        CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
        return &modifier;
#else
        return nullptr;
#endif
    }
}

const CJUIToggleModifier* GetCJUIToggleDynamicModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIToggleModifier modifier = {
        .setToggleSelectedColor = SetToggleSelectedColor,
        .resetToggleSelectedColor = ResetToggleSelectedColor,
        .setToggleSwitchPointColor = SetToggleSwitchPointColor,
        .resetToggleSwitchPointColor = ResetToggleSwitchPointColor,
        .setToggleHeight = SetToggleHeight,
        .resetToggleHeight = ResetToggleHeight,
        .setToggleResponseRegion = SetToggleResponseRegion,
        .resetToggleResponseRegion = ResetToggleResponseRegion,
        .setTogglePadding = SetTogglePadding,
        .resetTogglePadding = ResetTogglePadding,
        .setToggleBackgroundColor = SetToggleBackgroundColor,
        .setToggleBackgroundColorWithColorSpace = SetToggleBackgroundColorWithColorSpace,
        .resetToggleBackgroundColor = ResetToggleBackgroundColor,
        .setToggleHoverEffect = SetToggleHoverEffect,
        .resetToggleHoverEffect = ResetToggleHoverEffect,
        .getToggleSelectedColor = GetToggleSelectedColor,
        .getToggleSwitchPointColor = GetToggleSwitchPointColor,
        .setToggleIsOn = SetToggleIsOn,
        .resetToggleIsOn = ResetToggleIsOn,
        .getToggleIsOn = GetToggleIsOn,
        .setTogglePointRadius = SetTogglePointRadius,
        .resetTogglePointRadius = ResetTogglePointRadius,
        .setToggleUnselectedColor = SetToggleUnselectedColor,
        .resetToggleUnselectedColor = ResetToggleUnselectedColor,
        .setToggleTrackBorderRadius = SetToggleTrackBorderRadius,
        .resetToggleTrackBorderRadius = ResetToggleTrackBorderRadius,
        .getToggleUnselectedColor = GetToggleUnselectedColor,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}
} // namespace OHOS::Ace::NG
