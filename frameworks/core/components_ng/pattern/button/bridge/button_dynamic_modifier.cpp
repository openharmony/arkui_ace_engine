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

#include <climits>
#include <list>
#include <optional>
#include <string>
#include <vector>

#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "base/utils/system_properties.h"
#include "bridge/common/utils/utils.h"
#include "core/common/container.h"
#include "core/common/resource/resource_parse_utils.h"
#include "core/components/common/layout/common_text_constants.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/input_event_hub.h"
#include "core/components_ng/pattern/button/bridge/button_custom_modifier.h"
#include "core/components_ng/pattern/button/button_event_hub.h"
#include "core/components_ng/pattern/button/button_model_impl.h"
#include "core/components_ng/pattern/button/button_model_ng.h"
#include "core/components_ng/pattern/button/button_model_static.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/button/toggle_button_event_hub.h"
#include "core/components_ng/pattern/button/toggle_button_model_ng.h"
#include "core/components_ng/pattern/button/toggle_button_pattern.h"
#include "core/components_ng/property/border_property.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "core/interfaces/cjui/cjui_api.h"
#include "core/pipeline/pipeline_base.h"
#include "frameworks/core/components/button/button_theme.h"

namespace OHOS::Ace {
#ifndef CROSS_PLATFORM
Framework::ButtonModelImpl* GetButtonImpl()
{
    static Framework::ButtonModelImpl instance;
    return &instance;
}
#endif

ButtonModel* ButtonModel::GetInstance()
{
#if defined(NG_BUILD) || defined(CROSS_PLATFORM)
    static NG::ButtonModelNG instance;
    return &instance;
#else
    if (Container::IsCurrentUseNewPipeline()) {
        static NG::ButtonModelNG instance;
        return &instance;
    } else {
        static Framework::ButtonModelImpl instance;
        return &instance;
    }
#endif
}
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t DEFAULT_BUTTON_TYPE = static_cast<int32_t>(ButtonType::CAPSULE);
constexpr int32_t DEFAULT_BUTTON_TYPE_VERSION_EIGHTEEN = static_cast<int32_t>(ButtonType::ROUNDED_RECTANGLE);
constexpr bool DEFAULT_STATE_EFFECT = true;
constexpr Ace::FontWeight DEFAULT_FONT_WEIGHT = Ace::FontWeight::NORMAL;
constexpr Ace::FontStyle DEFAULT_FONT_STYLE = Ace::FontStyle::NORMAL;
constexpr float DEFAULT_MIN_FONT_SCALE = 0.0f;
constexpr float DEFAULT_MAX_FONT_SCALE = static_cast<float>(INT32_MAX);
constexpr uint32_t INDEX_STRING_FONT_WEIGHT_0 = 0;
constexpr uint32_t INDEX_STRING_FONT_FAMILY_1 = 1;
constexpr uint32_t INDEX_VALUE_TEXT_OVERFLOW_0 = 0;
constexpr uint32_t INDEX_VALUE_MAX_LINES_1 = 1;
constexpr uint32_t INDEX_VALUE_ADAPT_HEIGHT_2 = 2;
constexpr uint32_t INDEX_VALUE_FONT_STYLE_3 = 3;
constexpr uint32_t INDEX_VALUE_TEXT_ALIGN_4 = 4;
constexpr uint32_t INDEX_DIMENSION_MIN_FONT_SIZE_0 = 0;
constexpr uint32_t INDEX_DIMENSION_MAX_FONT_SIZE_1 = 1;
constexpr uint32_t INDEX_DIMENSION_FONT_SIZE_2 = 2;
constexpr uint32_t INDEX_STRING_ARRAY_COUNT = 0;
constexpr uint32_t INDEX_VALUE_ARRAY_COUNT = 1;
constexpr uint32_t INDEX_DIMENSION_ARRAY_COUNT = 2;
constexpr uint32_t INDEX_INVALID_FONT_FAMILY_0 = 0;
constexpr int32_t OFFSET_1 = 1;
constexpr int32_t OFFSET_2 = 2;
constexpr int32_t OFFSET_3 = 3;
constexpr int32_t BORDER_RADIUS_SIZE = 12;
const std::string DEFAULT_FONT_FAMILY = "HarmonyOS Sans";
const std::string NONE_FONT_FAMILY = "NoneFontFamily";
const uint32_t ERROR_UINT_CODE = static_cast<uint32_t>(-1);
const float ERROR_FLOAT_CODE = -1.0f;
const int32_t ERROR_INT_CODE = -1;
thread_local std::string g_strValue;
const std::vector<TextOverflow> TEXT_OVERFLOWS = { TextOverflow::NONE, TextOverflow::CLIP, TextOverflow::ELLIPSIS,
    TextOverflow::MARQUEE };
const std::vector<TextAlign> TEXT_ALIGNS = { TextAlign::START, TextAlign::CENTER, TextAlign::END, TextAlign::JUSTIFY,
    TextAlign::LEFT, TextAlign::RIGHT };
const std::vector<Ace::FontStyle> FONT_STYLES = { Ace::FontStyle::NORMAL, Ace::FontStyle::ITALIC };
const std::vector<TextHeightAdaptivePolicy> HEIGHT_ADAPTIVE_POLICY = {
    TextHeightAdaptivePolicy::MAX_LINES_FIRST,
    TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST,
    TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST,
};
const char BUTTON_ETS_TAG[] = "Button";

FrameNode* GetFrameNode(ArkUINodeHandle node)
{
    return node ? reinterpret_cast<FrameNode*>(node) : ViewStackProcessor::GetInstance()->GetMainFrameNode();
}

std::optional<CalcLength> ToOptionalButtonPadding(const ArkUISizeType& value)
{
    if (!value.isSet) {
        return std::nullopt;
    }
    if (value.string != nullptr) {
        return CalcLength(value.string);
    }
    return CalcLength(value.value, static_cast<DimensionUnit>(value.unit));
}

RefPtr<ButtonPattern> GetButtonPattern(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    return AceType::DynamicCast<ButtonPattern>(frameNode->GetPattern());
}

RefPtr<ButtonLayoutProperty> GetButtonLayoutProperty(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    return frameNode->GetLayoutProperty<ButtonLayoutProperty>();
}

RefPtr<ToggleButtonPattern> GetToggleButtonPattern(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    return AceType::DynamicCast<ToggleButtonPattern>(frameNode->GetPattern());
}

void SetOptionalBorderRadius(
    std::optional<Dimension>& optionalDimension, const ArkUI_Float32* values, int32_t valuesSize, int32_t& offset)
{
    static_cast<void>(valuesSize);
    bool hasValue = static_cast<bool>(values[offset]);
    if (hasValue) {
        optionalDimension = Dimension(values[offset + OFFSET_1], static_cast<DimensionUnit>(values[offset + OFFSET_2]));
    }
    offset += OFFSET_3;
}

void SetButtonLabel(ArkUINodeHandle node, ArkUI_CharPtr label)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetLabel(frameNode, label);
}

void ResetButtonLabel(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetLabel(frameNode, "");
}

void SetButtonType(ArkUINodeHandle node, int type)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if ((ButtonType)type == ButtonType::CAPSULE || (ButtonType)type == ButtonType::CIRCLE ||
        (ButtonType)type == ButtonType::ARC || (ButtonType)type == ButtonType::NORMAL ||
        (ButtonType)type == ButtonType::ROUNDED_RECTANGLE) {
        ButtonModelNG::SetType(frameNode, type);
    }
}

void ResetButtonType(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (frameNode->GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        ButtonModelNG::SetType(frameNode, DEFAULT_BUTTON_TYPE_VERSION_EIGHTEEN);
    } else {
        ButtonModelNG::SetType(frameNode, DEFAULT_BUTTON_TYPE);
    }
}

void SetButtonStateEffect(ArkUINodeHandle node, ArkUI_Bool stateEffect)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetStateEffect(frameNode, stateEffect);
}

void ResetButtonStateEffect(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetStateEffect(frameNode, DEFAULT_STATE_EFFECT);
}

void SetButtonFontColor(ArkUINodeHandle node, uint32_t fontColor)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetFontColor(frameNode, Color(fontColor), true);
}

void SetButtonFontColorPtr(ArkUINodeHandle node, uint32_t fontColor, void* colorRawPtr)
{
    Color result = Color(fontColor);
    if (SystemProperties::ConfigChangePerform()) {
        auto* frameNode = GetFrameNode(node);
        CHECK_NULL_VOID(frameNode);
        RefPtr<ResourceObject> resObj;
        if (!colorRawPtr) {
            ResourceParseUtils::CompleteResourceObjectFromColor(
                resObj, result, ResourceParseUtils::MakeNativeNodeInfo(frameNode));
        } else {
            resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(colorRawPtr));
        }
        ButtonModelNG::CreateWithColorResourceObj(frameNode, resObj, ButtonColorType::FONT_COLOR);
    }
    SetButtonFontColor(node, result.GetValue());
}

void SetButtonFontColorUseColorPtr(ArkUINodeHandle node, const ArkUI_InnerColor* fontColor, void* colorRawPtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(fontColor);
    Color result = *(reinterpret_cast<const Color*>(fontColor));
    if (SystemProperties::ConfigChangePerform()) {
        RefPtr<ResourceObject> resObj;
        if (!colorRawPtr) {
            ResourceParseUtils::CompleteResourceObjectFromColor(
                resObj, result, ResourceParseUtils::MakeNativeNodeInfo(frameNode));
        } else {
            resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(colorRawPtr));
        }
        ButtonModelNG::CreateWithColorResourceObj(frameNode, resObj, ButtonColorType::FONT_COLOR);
    }
    ButtonModelNG::SetFontColor(frameNode, result, true);
}

void ResetButtonFontColor(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto buttonTheme = frameNode->GetTheme<ButtonTheme>(true);
    CHECK_NULL_VOID(buttonTheme);
    auto textColor = buttonTheme->GetTextStyle().GetTextColor();
    ButtonModelNG::SetFontColor(frameNode, textColor, true);
    if (SystemProperties::ConfigChangePerform()) {
        ButtonModelNG::CreateWithColorResourceObj(frameNode, nullptr, ButtonColorType::FONT_COLOR);
    }
}

void ResetButtonFontSizeInternal(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto buttonTheme = pipeline->GetTheme<ButtonTheme>();
    CHECK_NULL_VOID(buttonTheme);
    auto fontSize = buttonTheme->GetTextStyle().GetFontSize();
    ButtonModelNG::SetFontSize(frameNode, fontSize);
}

void SetButtonFontSize(ArkUINodeHandle node, ArkUI_Float32 fontSizeValue, int fontSizeUnit)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (LessNotEqual(fontSizeValue, 0.0)) {
        ResetButtonFontSizeInternal(node);
    } else {
        ButtonModelNG::SetFontSize(frameNode, CalcDimension(fontSizeValue, static_cast<DimensionUnit>(fontSizeUnit)));
    }
}

void ResetButtonFontSize(ArkUINodeHandle node)
{
    ResetButtonFontSizeInternal(node);
}

void SetButtonFontWeight(ArkUINodeHandle node, ArkUI_CharPtr fontWeight)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    std::string fontWeightStr = fontWeight;
    ButtonModelNG::SetFontWeight(frameNode, Framework::ConvertStrToFontWeight(fontWeightStr));
}

void SetButtonFontWeightEnum(ArkUINodeHandle node, int fontWeight)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetFontWeight(frameNode, static_cast<FontWeight>(fontWeight));
}

void ResetButtonFontWeight(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetFontWeight(frameNode, DEFAULT_FONT_WEIGHT);
}

void SetButtonFontStyle(ArkUINodeHandle node, int32_t fontStyle)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (fontStyle < 0 || fontStyle >= static_cast<int32_t>(FONT_STYLES.size())) {
        ButtonModelNG::SetFontStyle(frameNode, DEFAULT_FONT_STYLE);
    } else {
        ButtonModelNG::SetFontStyle(frameNode, FONT_STYLES[fontStyle]);
    }
}

void ResetButtonFontStyle(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetFontStyle(frameNode, DEFAULT_FONT_STYLE);
}

void SetButtonFontFamily(ArkUINodeHandle node, ArkUI_CharPtr fontFamily)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    std::string familiesStr = fontFamily;
    auto fontFamilyResult = Framework::ConvertStrToFontFamilies(familiesStr);
    ButtonModelNG::SetFontFamily(frameNode, fontFamilyResult);
}

void SetButtonFontFamilyPtr(ArkUINodeHandle node, ArkUI_CharPtr fontFamily, void* familiesRawPtr)
{
    SetButtonFontFamily(node, fontFamily);
    if (SystemProperties::ConfigChangePerform()) {
        auto* frameNode = GetFrameNode(node);
        CHECK_NULL_VOID(frameNode);
        auto* families = reinterpret_cast<ResourceObject*>(familiesRawPtr);
        auto familiesResObj = AceType::Claim(families);
        ButtonModelNG::CreateWithFamiliesResourceObj(frameNode, familiesResObj, ButtonStringType::FONT_FAMILY);
    }
}

void ResetButtonFontFamily(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto fontFamilyResult = Framework::ConvertStrToFontFamilies(DEFAULT_FONT_FAMILY);
    ButtonModelNG::SetFontFamily(frameNode, fontFamilyResult);
    if (SystemProperties::ConfigChangePerform()) {
        ButtonModelNG::CreateWithFamiliesResourceObj(frameNode, nullptr, ButtonStringType::FONT_FAMILY);
    }
}

void ButtonCompleteParameters(ButtonParameters& buttonParameters)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto buttonTheme = pipeline->GetTheme<ButtonTheme>();
    if (!buttonTheme) {
        return;
    }
    auto textStyle = buttonTheme->GetTextStyle();
    if (!buttonParameters.textOverflow.has_value()) {
        buttonParameters.textOverflow = TextOverflow::CLIP;
    }
    if (!buttonParameters.maxLines.has_value()) {
        buttonParameters.maxLines = buttonTheme->GetTextMaxLines();
    }
    if (!buttonParameters.fontSize.has_value()) {
        buttonParameters.fontSize = textStyle.GetFontSize();
    }
    if (!buttonParameters.fontWeight.has_value()) {
        buttonParameters.fontWeight = textStyle.GetFontWeight();
    }
    if (!buttonParameters.fontStyle.has_value()) {
        buttonParameters.fontStyle = textStyle.GetFontStyle();
    }
    if (!buttonParameters.heightAdaptivePolicy.has_value()) {
        buttonParameters.heightAdaptivePolicy = TextHeightAdaptivePolicy::MAX_LINES_FIRST;
    }
}

bool SetButtonDimension(const ArkUI_Float32* dimensionArray, uint32_t offset, const size_t dataCount,
    std::optional<CalcDimension>& optDimension)
{
    CHECK_NULL_RETURN(dimensionArray, false);
    auto hasValue = dimensionArray[offset];
    if (!static_cast<bool>(hasValue)) {
        return false;
    }
    auto valueIndex = offset + 1;
    auto unitIndex = offset + 2;
    if (unitIndex >= dataCount) {
        return false;
    }
    auto value = dimensionArray[valueIndex];
    auto unit = dimensionArray[unitIndex];
    auto unitValue = static_cast<DimensionUnit>(unit);
    optDimension = CalcDimension(value, unitValue);
    return true;
}

void SetButtonDimensionParameters(
    const ArkUI_Float32* dimensionArray, const size_t dataCount, ButtonParameters& buttonParameters)
{
    CHECK_NULL_VOID(dimensionArray);
    constexpr uint32_t step = 3;
    std::optional<CalcDimension> minFontSizeOptional;
    if (SetButtonDimension(dimensionArray, INDEX_DIMENSION_MIN_FONT_SIZE_0, dataCount, minFontSizeOptional)) {
        buttonParameters.minFontSize = minFontSizeOptional;
    }
    std::optional<CalcDimension> maxFontSizeOptional;
    if (SetButtonDimension(dimensionArray, INDEX_DIMENSION_MAX_FONT_SIZE_1 * step, dataCount, maxFontSizeOptional)) {
        buttonParameters.maxFontSize = maxFontSizeOptional;
    }
    std::optional<CalcDimension> fontSizeOptional;
    if (SetButtonDimension(dimensionArray, INDEX_DIMENSION_FONT_SIZE_2 * step, dataCount, fontSizeOptional)) {
        buttonParameters.fontSize = fontSizeOptional;
    }
}

bool SetButtonValue(const int32_t* valueArray, uint32_t index, const size_t dataCount, int32_t& result)
{
    CHECK_NULL_RETURN(valueArray, false);
    constexpr uint32_t step = 2;
    auto hasValueIndex = index * step;
    auto valueIndex = hasValueIndex + 1;
    if (valueIndex >= dataCount) {
        return false;
    }
    if (static_cast<bool>(valueArray[hasValueIndex])) {
        result = valueArray[valueIndex];
        return true;
    }
    return false;
}

void SetButtonValueParameters(const int32_t* valueArray, const size_t dataCount, ButtonParameters& buttonParameters)
{
    CHECK_NULL_VOID(valueArray);
    int32_t result = 0;
    buttonParameters.textOverflow = TextOverflow::ELLIPSIS;
    if (SetButtonValue(valueArray, INDEX_VALUE_TEXT_OVERFLOW_0, dataCount, result) && result >= 0 &&
        result < static_cast<int32_t>(TEXT_OVERFLOWS.size())) {
        buttonParameters.textOverflow = TEXT_OVERFLOWS[result];
    }
    buttonParameters.maxLines = std::nullopt;
    if (SetButtonValue(valueArray, INDEX_VALUE_MAX_LINES_1, dataCount, result) && result >= 0) {
        buttonParameters.maxLines = Positive(result) ? result : 1;
    }
    buttonParameters.heightAdaptivePolicy = std::nullopt;
    if (SetButtonValue(valueArray, INDEX_VALUE_ADAPT_HEIGHT_2, dataCount, result) && result >= 0 &&
        result < static_cast<int32_t>(HEIGHT_ADAPTIVE_POLICY.size())) {
        buttonParameters.heightAdaptivePolicy = HEIGHT_ADAPTIVE_POLICY[result];
    }
    buttonParameters.fontStyle = std::nullopt;
    if (SetButtonValue(valueArray, INDEX_VALUE_FONT_STYLE_3, dataCount, result) && result >= 0 &&
        result < static_cast<int32_t>(FONT_STYLES.size())) {
        buttonParameters.fontStyle = FONT_STYLES[result];
    }
    if (SetButtonValue(valueArray, INDEX_VALUE_TEXT_ALIGN_4, dataCount, result) && result >= 0 &&
        result < static_cast<int32_t>(TEXT_ALIGNS.size())) {
        buttonParameters.textAlign = TEXT_ALIGNS[result];
    }
}

void SetButtonStringParameters(
    ArkUI_CharPtr* stringParameters, const size_t dataCount, ButtonParameters& buttonParameters)
{
    CHECK_NULL_VOID(stringParameters);
    buttonParameters.fontWeight = std::nullopt;
    if (INDEX_STRING_FONT_WEIGHT_0 < dataCount && stringParameters[INDEX_STRING_FONT_WEIGHT_0] != nullptr) {
        std::string fontWeightStr = stringParameters[INDEX_STRING_FONT_WEIGHT_0];
        buttonParameters.fontWeight = Framework::ConvertStrToFontWeight(fontWeightStr);
    }
    buttonParameters.fontFamily = std::nullopt;
    if (INDEX_STRING_FONT_FAMILY_1 < dataCount && stringParameters[INDEX_STRING_FONT_FAMILY_1] != nullptr) {
        std::string familiesStr = stringParameters[INDEX_STRING_FONT_FAMILY_1];
        auto fontFamilyResult = Framework::ConvertStrToFontFamilies(familiesStr);
        if (fontFamilyResult.size() == 1 &&
            fontFamilyResult[INDEX_INVALID_FONT_FAMILY_0].compare(NONE_FONT_FAMILY) == 0) {
            return;
        }
        buttonParameters.fontFamily = fontFamilyResult;
    }
}

void SetButtonLabelStyle(ArkUINodeHandle node, ArkUI_CharPtr* stringParameters, const ArkUI_Int32* valueArray,
    const ArkUI_Float32* dimensionArray, const ArkUI_Uint32* dataCountArray)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ButtonParameters buttonParameters;
    SetButtonStringParameters(stringParameters, dataCountArray[INDEX_STRING_ARRAY_COUNT], buttonParameters);
    SetButtonValueParameters(valueArray, dataCountArray[INDEX_VALUE_ARRAY_COUNT], buttonParameters);
    SetButtonDimensionParameters(dimensionArray, dataCountArray[INDEX_DIMENSION_ARRAY_COUNT], buttonParameters);
    ButtonCompleteParameters(buttonParameters);
    if (!buttonParameters.textAlign.has_value()) {
        ButtonModelNG::ResetTextAlign(frameNode);
    }
    ButtonModelNG::SetLabelStyle(frameNode, buttonParameters);
}

void SetButtonLabelStylePtr(ArkUINodeHandle node, ArkUI_CharPtr* stringParameters, const ArkUI_Int32* valueArray,
    const ArkUI_Float32* dimensionArray, const ArkUI_Uint32* dataCountArray, const ArkUIButtonSizeStruct& sizeResObj)
{
    SetButtonLabelStyle(node, stringParameters, valueArray, dimensionArray, dataCountArray);
    if (SystemProperties::ConfigChangePerform()) {
        auto* frameNode = GetFrameNode(node);
        CHECK_NULL_VOID(frameNode);
        auto* minFontSize = reinterpret_cast<ResourceObject*>(sizeResObj.minFontSize);
        auto minSizeResObj = AceType::Claim(minFontSize);
        ButtonModelNG::CreateWithDimensionFpResourceObj(frameNode, minSizeResObj, ButtonDimensionType::MIN_FONT_SIZE);
        auto* maxFontSize = reinterpret_cast<ResourceObject*>(sizeResObj.maxFontSize);
        auto maxSizeResObj = AceType::Claim(maxFontSize);
        ButtonModelNG::CreateWithDimensionFpResourceObj(frameNode, maxSizeResObj, ButtonDimensionType::MAX_FONT_SIZE);
    }
}

void ResetButtonLabelStyle(ArkUINodeHandle node)
{
    if (SystemProperties::ConfigChangePerform()) {
        auto* frameNode = GetFrameNode(node);
        CHECK_NULL_VOID(frameNode);
        ButtonModelNG::CreateWithDimensionFpResourceObj(frameNode, nullptr, ButtonDimensionType::MIN_FONT_SIZE);
        ButtonModelNG::CreateWithDimensionFpResourceObj(frameNode, nullptr, ButtonDimensionType::MAX_FONT_SIZE);
    }
}

void SetButtonBackgroundColor(ArkUINodeHandle node, uint32_t color)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::BackgroundColor(frameNode, Color(color), true);
}

void SetButtonBackgroundColorPtr(ArkUINodeHandle node, uint32_t color, void* colorRawPtr)
{
    auto result = Color(color);
    if (SystemProperties::ConfigChangePerform()) {
        auto* frameNode = GetFrameNode(node);
        CHECK_NULL_VOID(frameNode);
        RefPtr<ResourceObject> resObj;
        if (!colorRawPtr) {
            ResourceParseUtils::CompleteResourceObjectFromColor(
                resObj, result, ResourceParseUtils::MakeNativeNodeInfo(frameNode));
        } else {
            resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(colorRawPtr));
        }
        ButtonModelNG::CreateWithColorResourceObj(frameNode, resObj, ButtonColorType::BACKGROUND_COLOR);
    }
    SetButtonBackgroundColor(node, result.GetValue());
}

void SetButtonBackgroundColorWithColorSpace(ArkUINodeHandle node, ArkUI_Uint32 color, ArkUI_Int32 colorSpace)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    Color backgroundColor { color };
    if (ColorSpace::DISPLAY_P3 == colorSpace) {
        backgroundColor.SetColorSpace(ColorSpace::DISPLAY_P3);
    } else {
        backgroundColor.SetColorSpace(ColorSpace::SRGB);
    }
    ButtonModelNG::BackgroundColor(frameNode, backgroundColor, true);
}

void SetButtonBackgroundColorWithColorSpacePtr(
    ArkUINodeHandle node, ArkUI_Uint32 color, ArkUI_Int32 colorSpace, void* colorRawPtr)
{
    SetButtonBackgroundColorWithColorSpace(node, color, colorSpace);
    if (SystemProperties::ConfigChangePerform()) {
        auto* frameNode = GetFrameNode(node);
        CHECK_NULL_VOID(frameNode);
        auto* colorObj = reinterpret_cast<ResourceObject*>(colorRawPtr);
        auto colorResObj = AceType::Claim(colorObj);
        ButtonModelNG::CreateWithColorResourceObj(frameNode, colorResObj, ButtonColorType::BACKGROUND_COLOR);
    }
}

void ResetButtonBackgroundColor(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto buttonTheme = frameNode->GetTheme<ButtonTheme>(true);
    CHECK_NULL_VOID(buttonTheme);
    auto backgroundColor = buttonTheme->GetBgColor();
    ButtonModelNG::BackgroundColor(frameNode, backgroundColor, true);
    if (SystemProperties::ConfigChangePerform()) {
        ButtonModelNG::CreateWithColorResourceObj(frameNode, nullptr, ButtonColorType::BACKGROUND_COLOR);
    }
}

void SetButtonBorderRadius(ArkUINodeHandle node, const ArkUI_Float32* values, int32_t valuesSize)
{
    if (values == nullptr || valuesSize != BORDER_RADIUS_SIZE) {
        return;
    }
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    int32_t offset = 0;
    std::optional<Dimension> radiusTopLeft;
    std::optional<Dimension> radiusTopRight;
    std::optional<Dimension> radiusBottomLeft;
    std::optional<Dimension> radiusBottomRight;
    SetOptionalBorderRadius(radiusTopLeft, values, valuesSize, offset);
    SetOptionalBorderRadius(radiusTopRight, values, valuesSize, offset);
    SetOptionalBorderRadius(radiusBottomLeft, values, valuesSize, offset);
    SetOptionalBorderRadius(radiusBottomRight, values, valuesSize, offset);
    ButtonModelNG::SetBorderRadius(frameNode, radiusTopLeft, radiusTopRight, radiusBottomLeft, radiusBottomRight);
}

void ResetButtonBorderRadius(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    Dimension reset;
    ButtonModelNG::SetBorderRadius(frameNode, reset);
}

void SetButtonSize(
    ArkUINodeHandle node, ArkUI_CharPtr widthValue, int32_t widthUnit, ArkUI_CharPtr heightValue, int32_t heightUnit)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    std::string widthValueStr = std::string(widthValue);
    std::string heightValueStr = std::string(heightValue);
    std::optional<CalcDimension> widthInfo;
    std::optional<CalcDimension> heightInfo;
    if (widthValueStr != "undefined") {
        widthInfo = CalcDimension(StringUtils::StringToDouble(widthValueStr), static_cast<DimensionUnit>(widthUnit));
    } else {
        ViewAbstract::ClearWidthOrHeight(frameNode, true);
    }
    if (heightValueStr != "undefined") {
        heightInfo = CalcDimension(StringUtils::StringToDouble(heightValueStr), static_cast<DimensionUnit>(heightUnit));
    } else {
        ViewAbstract::ClearWidthOrHeight(frameNode, false);
    }
    ButtonModelNG::SetSize(frameNode, widthInfo, heightInfo);
}

void ResetButtonSize(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::ClearWidthOrHeight(frameNode, true);
    ViewAbstract::ClearWidthOrHeight(frameNode, false);
}

ArkUI_CharPtr GetButtonLabel(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, const_cast<char*>(""));
    g_strValue = ButtonModelNG::GetLabel(frameNode);
    return g_strValue.data();
}

ArkUI_Float32 GetButtonFontSize(ArkUINodeHandle node, ArkUI_Int32 unit)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return ButtonModelNG::GetFontSize(frameNode).GetNativeValue(static_cast<DimensionUnit>(unit));
}

ArkUI_Int32 GetButtonFontWeight(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Int32>(ButtonModelNG::GetFontWeight(frameNode));
}

ArkUI_Uint32 GetButtonFontColor(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, ERROR_UINT_CODE);
    return ButtonModelNG::GetFontColor(frameNode).GetValue();
}

void SetButtonRole(ArkUINodeHandle node, ArkUI_Uint32 buttonRole)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto role = ButtonRole::NORMAL;
    if (buttonRole >= static_cast<uint32_t>(ButtonRole::NORMAL) &&
        buttonRole <= static_cast<uint32_t>(ButtonRole::ERROR)) {
        role = static_cast<ButtonRole>(buttonRole);
    }
    ButtonModelNG::SetRole(frameNode, role);
}

void SetButtonRoleOnly(ArkUINodeHandle node, ArkUI_Uint32 buttonRole)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto role = ButtonRole::NORMAL;
    if (buttonRole >= static_cast<uint32_t>(ButtonRole::NORMAL) &&
        buttonRole <= static_cast<uint32_t>(ButtonRole::ERROR)) {
        role = static_cast<ButtonRole>(buttonRole);
    }
    ButtonModelNG::SetRoleOnly(frameNode, role);
}

void ResetButtonRole(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetRole(frameNode, ButtonRole::NORMAL);
}

void SetButtonStyle(ArkUINodeHandle node, ArkUI_Uint32 buttonStyle)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto style = ButtonStyleMode::EMPHASIZE;
    if (buttonStyle >= static_cast<uint32_t>(ButtonStyleMode::NORMAL) &&
        buttonStyle <= static_cast<uint32_t>(ButtonStyleMode::TEXT)) {
        style = static_cast<ButtonStyleMode>(buttonStyle);
    }
    ButtonModelNG::SetButtonStyle(frameNode, style);
}

void SetButtonStyleOnly(ArkUINodeHandle node, ArkUI_Uint32 buttonStyle)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto style = ButtonStyleMode::EMPHASIZE;
    if (buttonStyle >= static_cast<uint32_t>(ButtonStyleMode::NORMAL) &&
        buttonStyle <= static_cast<uint32_t>(ButtonStyleMode::TEXT)) {
        style = static_cast<ButtonStyleMode>(buttonStyle);
    }
    ButtonModelNG::SetButtonStyleOnly(frameNode, style);
}

void ResetButtonStyle(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetButtonStyle(frameNode, ButtonStyleMode::EMPHASIZE);
}

void SetButtonControlSize(ArkUINodeHandle node, ArkUI_Uint32 controlSize)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto size = ControlSize::NORMAL;
    if (controlSize >= static_cast<uint32_t>(ControlSize::SMALL) &&
        controlSize <= static_cast<uint32_t>(ControlSize::NORMAL)) {
        size = static_cast<ControlSize>(controlSize);
    }
    ButtonModelNG::SetControlSize(frameNode, size);
}

void ResetButtonControlSize(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetControlSize(frameNode, ControlSize::NORMAL);
}

ArkUI_Int32 GetButtonType(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Int32>(ButtonModelNG::GetType(frameNode));
}

void SetButtonLabelWithCheck(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetLabelWithCheck(frameNode, value);
}

void ResetButtonLabelWithCheck(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetLabelWithCheck(frameNode, "");
}

void SetButtonOptions(ArkUINodeHandle node, ArkUI_Uint32 buttonStyle, ArkUI_Uint32 buttonRole)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto style = ButtonStyleMode::EMPHASIZE;
    if (buttonStyle >= static_cast<uint32_t>(ButtonStyleMode::NORMAL) &&
        buttonStyle <= static_cast<uint32_t>(ButtonStyleMode::TEXT)) {
        style = static_cast<ButtonStyleMode>(buttonStyle);
    }
    auto role = ButtonRole::NORMAL;
    if (buttonRole >= static_cast<uint32_t>(ButtonRole::NORMAL) &&
        buttonRole <= static_cast<uint32_t>(ButtonRole::ERROR)) {
        role = static_cast<ButtonRole>(buttonRole);
    }
    ButtonModelNG::ApplyTheme(frameNode, style, role);
}

void ResetButtonOptions(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (frameNode->GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        ButtonModelNG::SetType(frameNode, DEFAULT_BUTTON_TYPE_VERSION_EIGHTEEN);
    } else {
        ButtonModelNG::SetType(frameNode, DEFAULT_BUTTON_TYPE);
    }
    ButtonModelNG::SetStateEffect(frameNode, DEFAULT_STATE_EFFECT);
    ButtonModelNG::SetButtonStyle(frameNode, ButtonStyleMode::EMPHASIZE);
    ButtonModelNG::SetControlSize(frameNode, ControlSize::NORMAL);
    ButtonModelNG::SetRole(frameNode, ButtonRole::NORMAL);
}

void SetCreateWithLabel(ArkUINodeHandle node, bool createWithLabel)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetCreateWithLabel(frameNode, createWithLabel);
}

void CreateButtonWithLabel(ArkUI_VoidPtr createPara, ArkUI_VoidPtr buttonChildren)
{
    auto* para = reinterpret_cast<CreateWithPara*>(createPara);
    auto* children = reinterpret_cast<std::list<RefPtr<Component>>*>(buttonChildren);
    CHECK_NULL_VOID(para);
    CHECK_NULL_VOID(children);
    static ButtonModelNG model;
    model.CreateWithLabel(*para, *children);
}

void CreateButton(ArkUI_VoidPtr createPara, ArkUI_VoidPtr buttonChildren) {}

void CreateButtonWithChild(ArkUI_VoidPtr createPara)
{
    auto* para = reinterpret_cast<CreateWithPara*>(createPara);
    CHECK_NULL_VOID(para);
    static ButtonModelNG model;
    model.CreateWithChild(*para);
}

void CreateButtonStringResourceObj(ArkUINodeHandle node, ArkUI_VoidPtr resObj, ArkUI_Int32 buttonStringType)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto resourceObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resObj));
    ButtonModelNG::CreateWithStringResourceObj(frameNode, resourceObj, static_cast<ButtonStringType>(buttonStringType));
}

void SetButtonMinFontScale(ArkUINodeHandle node, ArkUI_Float32 minFontScale)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetMinFontScale(frameNode, minFontScale);
}

void SetButtonMinFontScalePtr(ArkUINodeHandle node, ArkUI_Float32 minFontScale, void* scaleRawPtr, ArkUI_Bool hasValue)
{
    if (hasValue) {
        SetButtonMinFontScale(node, minFontScale);
    }
    if (SystemProperties::ConfigChangePerform()) {
        auto* frameNode = GetFrameNode(node);
        CHECK_NULL_VOID(frameNode);
        auto* scaleValue = reinterpret_cast<ResourceObject*>(scaleRawPtr);
        auto scaleResObj = AceType::Claim(scaleValue);
        ButtonModelNG::CreateWithDoubleResourceObj(frameNode, scaleResObj, ButtonDoubleType::MIN_FONT_SCALE);
    }
}

void ResetButtonMinFontScale(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetMinFontScale(frameNode, DEFAULT_MIN_FONT_SCALE);
    if (SystemProperties::ConfigChangePerform()) {
        ButtonModelNG::CreateWithDoubleResourceObj(frameNode, nullptr, ButtonDoubleType::MIN_FONT_SCALE);
    }
}

void SetButtonMaxFontScale(ArkUINodeHandle node, ArkUI_Float32 maxFontScale)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetMaxFontScale(frameNode, maxFontScale);
}

void SetButtonMaxFontScalePtr(ArkUINodeHandle node, ArkUI_Float32 maxFontScale, void* scaleRawPtr, ArkUI_Bool hasValue)
{
    if (SystemProperties::ConfigChangePerform()) {
        auto* frameNode = GetFrameNode(node);
        CHECK_NULL_VOID(frameNode);
        auto* scaleValue = reinterpret_cast<ResourceObject*>(scaleRawPtr);
        auto scaleResObj = AceType::Claim(scaleValue);
        ButtonModelNG::CreateWithDoubleResourceObj(frameNode, scaleResObj, ButtonDoubleType::MAX_FONT_SCALE);
    }
    if (!hasValue) {
        return;
    }
    SetButtonMaxFontScale(node, maxFontScale);
}

void ResetButtonMaxFontScale(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetMaxFontScale(frameNode, DEFAULT_MAX_FONT_SCALE);
    if (SystemProperties::ConfigChangePerform()) {
        ButtonModelNG::CreateWithDoubleResourceObj(frameNode, nullptr, ButtonDoubleType::MAX_FONT_SCALE);
    }
}

ArkUI_Float32 GetButtonMinFontScale(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return static_cast<ArkUI_Float32>(ButtonModelNG::GetMinFontScale(frameNode));
}

ArkUI_Float32 GetButtonMaxFontScale(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return static_cast<ArkUI_Float32>(ButtonModelNG::GetMaxFontScale(frameNode));
}

void SetButtonFontColorWithPlaceholder(ArkUINodeHandle node, uint32_t fontColor, ArkUI_Uint32 colorPlaceholder)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    Color result = Color(fontColor);
    result.SetPlaceholder(static_cast<ColorPlaceholder>(colorPlaceholder));
    ButtonModelNG::SetFontColor(frameNode, result, true);
}

ArkUINodeHandle CreateButtonFrameNodeForCustom(ArkUI_Int32 nodeId)
{
    auto frameNode = ButtonModelNG::CreateFrameNode(nodeId);
    CHECK_NULL_RETURN(frameNode, nullptr);
    AceType::RawPtr(frameNode)->IncRefCount();
    return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode));
}

ArkUINodeHandle CreateFrameNodeForCustom(ArkUI_Int32 nodeId)
{
    auto frameNode = FrameNode::CreateFrameNode(BUTTON_ETS_TAG, nodeId, AceType::MakeRefPtr<ButtonPattern>());
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode));
}

void* CreateButtonPatternForCustom()
{
    auto pattern = AceType::MakeRefPtr<ButtonPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    AceType::RawPtr(pattern)->IncRefCount();
    return AceType::RawPtr(pattern);
}

void* CreateToggleButtonPatternForCustom()
{
    auto pattern = AceType::MakeRefPtr<ToggleButtonPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    AceType::RawPtr(pattern)->IncRefCount();
    return AceType::RawPtr(pattern);
}

void SetComponentButtonTypeForCustom(ArkUINodeHandle node, OHOS::Ace::ComponentButtonType buttonType)
{
    auto pattern = GetButtonPattern(node);
    CHECK_NULL_VOID(pattern);
    pattern->setComponentButtonType(buttonType);
}

void SetSkipColorConfigurationUpdateForCustom(ArkUINodeHandle node)
{
    auto pattern = GetButtonPattern(node);
    CHECK_NULL_VOID(pattern);
    pattern->SetSkipColorConfigurationUpdate();
}

void SetClickedColorForCustom(ArkUINodeHandle node, const Color& color)
{
    auto pattern = GetButtonPattern(node);
    CHECK_NULL_VOID(pattern);
    pattern->SetClickedColor(color);
}

void SetBlendColorForCustom(ArkUINodeHandle node, const Color& clickColor, const Color& hoverColor)
{
    auto pattern = GetButtonPattern(node);
    CHECK_NULL_VOID(pattern);
    pattern->SetBlendColor(clickColor, hoverColor);
}

void SetBlendColorWithOptionalForCustom(
    ArkUINodeHandle node, const std::optional<Color>& clickColor, const std::optional<Color>& hoverColor)
{
    auto pattern = GetButtonPattern(node);
    CHECK_NULL_VOID(pattern);
    pattern->SetBlendColor(clickColor, hoverColor);
}

void SetFocusBorderColorForCustom(ArkUINodeHandle node, const Color& color)
{
    auto pattern = GetButtonPattern(node);
    CHECK_NULL_VOID(pattern);
    pattern->SetFocusBorderColor(color);
}

void SetFocusBorderWidthForCustom(ArkUINodeHandle node, const Dimension& width)
{
    auto pattern = GetButtonPattern(node);
    CHECK_NULL_VOID(pattern);
    pattern->SetFocusBorderWidth(width);
}

void SetApplyShadowForCustom(ArkUINodeHandle node, bool shadow)
{
    auto pattern = GetButtonPattern(node);
    CHECK_NULL_VOID(pattern);
    pattern->SetApplyShadow(shadow);
}

void HandleButtonBackgroundColorForCustom(ArkUINodeHandle node)
{
    auto pattern = GetButtonPattern(node);
    CHECK_NULL_VOID(pattern);
    pattern->HandleBackgroundColor();
}

void SetNavigationFocusBlendBgColorForCustom(ArkUINodeHandle node, const Color& color)
{
    auto pattern = GetButtonPattern(node);
    CHECK_NULL_VOID(pattern);
    pattern->SetNavigationFocusBlendBgColor(color);
}

void SetNavMenuItemNeedFocusForCustom(ArkUINodeHandle node, bool needFocus)
{
    auto pattern = GetButtonPattern(node);
    CHECK_NULL_VOID(pattern);
    pattern->SetNavMenuItemNeedFocus(needFocus);
}

void SetHasCustomPaddingForCustom(ArkUINodeHandle node, bool hasCustomPadding)
{
    auto pattern = GetButtonPattern(node);
    CHECK_NULL_VOID(pattern);
    pattern->SetHasCustomPadding(hasCustomPadding);
}

bool IsToggleButtonPatternForCustom(ArkUINodeHandle node)
{
    auto frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, false);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_RETURN(pattern, false);
    return AceType::InstanceOf<ToggleButtonPattern>(pattern);
}

bool IsButtonPatternForCustom(ArkUINodeHandle node)
{
    auto frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, false);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_RETURN(pattern, false);
    return AceType::InstanceOf<ButtonPattern>(pattern);
}

bool IsButtonLayoutPropertyForCustom(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, false);
    auto layoutProperty = frameNode->GetLayoutProperty<LayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    return AceType::InstanceOf<ButtonLayoutProperty>(layoutProperty);
}

void SetToggleBackgroundColorForCustom(ArkUINodeHandle node, const Color& color)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ToggleButtonModelNG::SetBackgroundColor(frameNode, color);
}

void SetToggleBackgroundColorWithFlagForCustom(ArkUINodeHandle node, const Color& color, bool flag)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ToggleButtonModelNG::SetBackgroundColor(frameNode, color, flag);
}

void SetButtonBorderRadiusForCustom(ArkUINodeHandle node, const std::optional<Dimension>& topLeft,
    const std::optional<Dimension>& topRight, const std::optional<Dimension>& bottomLeft,
    const std::optional<Dimension>& bottomRight)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetBorderRadius(frameNode, topLeft, topRight, bottomLeft, bottomRight);
}

void SetToggleBuilderFuncForCustom(ArkUINodeHandle node, void* callback)
{
    auto pattern = GetToggleButtonPattern(node);
    CHECK_NULL_VOID(pattern);
    if (callback) {
        auto makeFunc = reinterpret_cast<SwitchMakeCallback*>(callback);
        pattern->SetToggleBuilderFunc(std::move(*makeFunc));
        return;
    }
    pattern->SetToggleBuilderFunc(nullptr);
}

void SetToggleButtonPressForCustom(ArkUINodeHandle node, bool value)
{
    auto pattern = GetToggleButtonPattern(node);
    CHECK_NULL_VOID(pattern);
    pattern->SetButtonPress(value);
}

void RemoveHoverListenerForCustom(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ButtonEventHub>();
    CHECK_NULL_VOID(eventHub);
    auto inputHub = eventHub->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(inputHub);
    auto pattern = GetButtonPattern(node);
    CHECK_NULL_VOID(pattern);
    inputHub->RemoveOnHoverEvent(pattern->GetHoverListener());
}

void SetButtonHoverForCustom(ArkUINodeHandle node, bool isHover)
{
    auto pattern = GetButtonPattern(node);
    CHECK_NULL_VOID(pattern);
    pattern->SetInHover(isHover);
}

bool GetButtonHoverForCustom(ArkUINodeHandle node)
{
    auto pattern = GetButtonPattern(node);
    CHECK_NULL_RETURN(pattern, false);
    return pattern->GetIsInHover();
}

void SetButtonLocalLocationForCustom(ArkUINodeHandle node, const Offset& localLocation)
{
    auto pattern = GetButtonPattern(node);
    CHECK_NULL_VOID(pattern);
    pattern->SetLocalLocation(localLocation);
}

const Offset& GetButtonLocalLocationForCustom(ArkUINodeHandle node)
{
    auto pattern = GetButtonPattern(node);
    static const Offset defaultOffset;
    CHECK_NULL_RETURN(pattern, defaultOffset);
    return pattern->GetLocalLocation();
}

void UpdateTypeToLayoutPropForCustom(ArkUINodeHandle node, OHOS::Ace::ButtonType type)
{
    auto layoutProperty = GetButtonLayoutProperty(node);
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateType(type);
}

void SetStateEffectToEventHubForCustom(ArkUINodeHandle node, bool stateEffect)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ButtonEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetStateEffect(stateEffect);
}

bool GetStateEffectFromEventHubForCustom(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, true);
    auto eventHub = frameNode->GetEventHub<ButtonEventHub>();
    CHECK_NULL_RETURN(eventHub, true);
    return eventHub->GetStateEffect();
}

void UpdateBackgroundColorFlagByUserToLayoutPropForCustom(ArkUINodeHandle node, bool value)
{
    auto layoutProperty = GetButtonLayoutProperty(node);
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateBackgroundColorFlagByUser(value);
}

void UpdateLabelToLayoutPropForCustom(ArkUINodeHandle node, const std::string& label)
{
    auto layoutProperty = GetButtonLayoutProperty(node);
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateLabel(label);
}

void UpdateFontSizeToLayoutPropForCustom(ArkUINodeHandle node, const Dimension& fontSize)
{
    auto layoutProperty = GetButtonLayoutProperty(node);
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateFontSize(fontSize);
}

void UpdateFontColorToLayoutPropForCustom(ArkUINodeHandle node, const Color& color)
{
    auto layoutProperty = GetButtonLayoutProperty(node);
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateFontColor(color);
}

void UpdateFontWeightToLayoutPropForCustom(ArkUINodeHandle node, FontWeight fontWeight)
{
    auto layoutProperty = GetButtonLayoutProperty(node);
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateFontWeight(fontWeight);
}

void UpdateFontColorFlagByUserToLayoutPropForCustom(ArkUINodeHandle node, bool value)
{
    auto layoutProperty = GetButtonLayoutProperty(node);
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateFontColorFlagByUser(value);
}

void UpdateFontStyleToLayoutPropForCustom(ArkUINodeHandle node, FontStyle fontStyle)
{
    auto layoutProperty = GetButtonLayoutProperty(node);
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateFontStyle(fontStyle);
}

void UpdateFontFamilyToLayoutPropForCustom(ArkUINodeHandle node, const std::vector<std::string>& fontFamily)
{
    auto layoutProperty = GetButtonLayoutProperty(node);
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateFontFamily(fontFamily);
}

void UpdateButtonStyleToLayoutPropForCustom(ArkUINodeHandle node, ButtonStyleMode buttonStyle)
{
    auto layoutProperty = GetButtonLayoutProperty(node);
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateButtonStyle(buttonStyle);
}

void UpdateButtonRoleToLayoutPropForCustom(ArkUINodeHandle node, ButtonRole buttonRole)
{
    auto layoutProperty = GetButtonLayoutProperty(node);
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateButtonRole(buttonRole);
}

void UpdateControlSizeToLayoutPropForCustom(ArkUINodeHandle node, ControlSize controlSize)
{
    auto layoutProperty = GetButtonLayoutProperty(node);
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateControlSize(controlSize);
}

const std::optional<ButtonStyleMode>& GetButtonStyleFromLayoutPropForCustom(ArkUINodeHandle node)
{
    static const std::optional<ButtonStyleMode> nullopt = std::nullopt;
    auto layoutProperty = GetButtonLayoutProperty(node);
    CHECK_NULL_RETURN(layoutProperty, nullopt);
    return layoutProperty->GetButtonStyle();
}

const std::optional<ButtonRole>& GetButtonRoleFromLayoutPropForCustom(ArkUINodeHandle node)
{
    static const std::optional<ButtonRole> nullopt = std::nullopt;
    auto layoutProperty = GetButtonLayoutProperty(node);
    CHECK_NULL_RETURN(layoutProperty, nullopt);
    return layoutProperty->GetButtonRole();
}

void UpdateAutoDisableToLayoutPropForCustom(ArkUINodeHandle node, bool autoDisable)
{
    auto layoutProperty = GetButtonLayoutProperty(node);
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateAutoDisable(autoDisable);
}

const std::optional<bool>& GetAutoDisableFromLayoutPropForCustom(ArkUINodeHandle node)
{
    static const std::optional<bool> emptyValue = std::nullopt;
    auto layoutProperty = GetButtonLayoutProperty(node);
    CHECK_NULL_RETURN(layoutProperty, emptyValue);
    return layoutProperty->GetAutoDisable();
}

bool HasFontColorFromLayoutPropForCustom(ArkUINodeHandle node)
{
    auto layoutProperty = GetButtonLayoutProperty(node);
    CHECK_NULL_RETURN(layoutProperty, false);
    return layoutProperty->HasFontColor();
}

void UpdateCreateWithLabelToLayoutPropForCustom(ArkUINodeHandle node, bool createWithLabel)
{
    auto layoutProperty = GetButtonLayoutProperty(node);
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateCreateWithLabel(createWithLabel);
}

void UpdateBorderRadiusToLayoutPropForCustom(ArkUINodeHandle node, const BorderRadiusProperty& borderRadius)
{
    auto layoutProperty = GetButtonLayoutProperty(node);
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateBorderRadius(borderRadius);
}

void UpdateTextOverflowToLayoutPropForCustom(ArkUINodeHandle node, TextOverflow textOverflow)
{
    auto layoutProperty = GetButtonLayoutProperty(node);
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateTextOverflow(textOverflow);
}

void UpdateMaxLinesToLayoutPropForCustom(ArkUINodeHandle node, uint32_t maxLines)
{
    auto layoutProperty = GetButtonLayoutProperty(node);
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateMaxLines(maxLines);
}

const std::optional<BorderRadiusProperty>& GetBorderRadiusFromLayoutPropForCustom(ArkUINodeHandle node)
{
    static const std::optional<BorderRadiusProperty> nullopt = std::nullopt;
    auto layoutProperty = GetButtonLayoutProperty(node);
    CHECK_NULL_RETURN(layoutProperty, nullopt);
    return layoutProperty->GetBorderRadius();
}

const std::optional<Dimension>& GetFontSizeFromLayoutPropForCustom(ArkUINodeHandle node)
{
    static const std::optional<Dimension> nullopt = std::nullopt;
    auto layoutProperty = GetButtonLayoutProperty(node);
    CHECK_NULL_RETURN(layoutProperty, nullopt);
    return layoutProperty->GetFontSize();
}

const std::optional<Color>& GetFontColorFromLayoutPropForCustom(ArkUINodeHandle node)
{
    static const std::optional<Color> nullopt = std::nullopt;
    auto layoutProperty = GetButtonLayoutProperty(node);
    CHECK_NULL_RETURN(layoutProperty, nullopt);
    return layoutProperty->GetFontColor();
}

const std::string& GetLabelFromLayoutPropForCustom(ArkUINodeHandle node)
{
    static const std::string emptyString = "";
    auto layoutProperty = GetButtonLayoutProperty(node);
    CHECK_NULL_RETURN(layoutProperty, emptyString);
    if (layoutProperty->HasLabel()) {
        return layoutProperty->GetLabelValue();
    }
    return emptyString;
}

void ResetFontSizeToLayoutPropForCustom(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ACE_RESET_NODE_LAYOUT_PROPERTY(ButtonLayoutProperty, FontSize, frameNode);
}

void SetFontColorDefaultForCustom(const Color& color)
{
    auto buttonModel = ButtonModel::GetInstance();
    CHECK_NULL_VOID(buttonModel);
    buttonModel->SetFontColorDefault(color);
}

void SetBackgroundColorDefaultForCustom(const Color& color)
{
    auto buttonModel = ButtonModel::GetInstance();
    CHECK_NULL_VOID(buttonModel);
    buttonModel->BackgroundColorDefault(color);
}

void SetBackgroundColorToModelStaticForCustom(FrameNode* frameNode, const std::optional<OHOS::Ace::Color>& color)
{
    CHECK_NULL_VOID(frameNode);
    ButtonModelStatic::BackgroundColor(frameNode, color);
}

void ResetButtonTextAlign(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::ResetTextAlign(frameNode);
}

void SetJsButtonLabelStylePtr(ArkUINodeHandle node, void* buttonParameters)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(buttonParameters);
    ButtonModelNG::SetLabelStyle(frameNode, *reinterpret_cast<ButtonParameters*>(buttonParameters));
}

void SetJsButtonOnClick(
    ArkUINodeHandle node, ArkUI_VoidPtr tapEventFunc, ArkUI_VoidPtr clickEventFunc, ArkUI_Float64 distanceThreshold)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(tapEventFunc);
    CHECK_NULL_VOID(clickEventFunc);
    auto onTapFunc = reinterpret_cast<std::function<void(GestureEvent&)>*>(tapEventFunc);
    auto onClickFunc = reinterpret_cast<std::function<void(const ClickInfo*)>*>(clickEventFunc);
    ButtonModelNG::OnClick(frameNode, std::move(*onTapFunc), std::move(*onClickFunc), distanceThreshold);
}

void SetJsButtonBackgroundColorPtr(
    ArkUINodeHandle node, const ArkUI_InnerColor* backgroundColor, ArkUI_VoidPtr colorRawPtr, ArkUI_Bool colorFlag)
{
    if (!node) {
        CHECK_NULL_VOID(backgroundColor);
        const auto* backgroundColorPtr = reinterpret_cast<const Color*>(backgroundColor);

        ButtonModelNG model;
        if (SystemProperties::ConfigChangePerform() && colorRawPtr) {
            auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(colorRawPtr));
            if (!NG::ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
                return;
            }
            model.CreateWithColorResourceObj(resObj, ButtonColorType::BACKGROUND_COLOR);
        }
        model.BackgroundColor(*backgroundColorPtr, colorFlag);
    }
}

void SetJsButtonPadding(ArkUINodeHandle node, const ArkUIPaddingType* oldValue, const ArkUIPaddingType* newValue)
{
    if (!node) {
        PaddingProperty padding;
        if (newValue != nullptr) {
            padding.top = ToOptionalButtonPadding(newValue->top);
            padding.bottom = ToOptionalButtonPadding(newValue->bottom);
            padding.left = ToOptionalButtonPadding(newValue->start);
            padding.right = ToOptionalButtonPadding(newValue->end);
        }
        ButtonModelNG model;
        Edge oldPadding;
        model.Padding(padding, oldPadding);
    }
}

void SetJsButtonBorderRadius(ArkUINodeHandle node, ArkUI_Float64 value, ArkUI_Int32 unit)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetBorderRadius(frameNode, Dimension(value, static_cast<DimensionUnit>(unit)));
}

void SetJsButtonLocalizedBorderRadius(ArkUINodeHandle node, const ArkUI_Float32* values, ArkUI_Int32 valuesSize)
{
    if (values == nullptr || valuesSize != BORDER_RADIUS_SIZE) {
        return;
    }
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    int32_t offset = 0;
    std::optional<Dimension> radiusTopLeft;
    std::optional<Dimension> radiusTopRight;
    std::optional<Dimension> radiusBottomLeft;
    std::optional<Dimension> radiusBottomRight;
    SetOptionalBorderRadius(radiusTopLeft, values, valuesSize, offset);
    SetOptionalBorderRadius(radiusTopRight, values, valuesSize, offset);
    SetOptionalBorderRadius(radiusBottomLeft, values, valuesSize, offset);
    SetOptionalBorderRadius(radiusBottomRight, values, valuesSize, offset);
    ButtonModelNG::SetLocalizedBorderRadius(
        frameNode, radiusTopLeft, radiusTopRight, radiusBottomLeft, radiusBottomRight);
}

void ResetJsButtonBorderRadius(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::ResetBorderRadius(frameNode);
}

void SetJsButtonFontSize(ArkUINodeHandle node, ArkUI_Float64 fontSizeValue, ArkUI_Int32 fontSizeUnit)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (LessNotEqual(fontSizeValue, 0.0)) {
        ResetButtonFontSizeInternal(node);
    } else {
        ButtonModelNG::SetFontSize(frameNode, CalcDimension(fontSizeValue, static_cast<DimensionUnit>(fontSizeUnit)));
    }
}

void UpdateToggleIsOnToPaintPropForCustom(ArkUINodeHandle node, bool isOn)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_PAINT_PROPERTY(ToggleButtonPaintProperty, IsOn, isOn, frameNode);
}

bool GetToggleIsOnFromPaintPropForCustom(ArkUINodeHandle node, bool defaultValue)
{
    bool value = defaultValue;
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_RETURN(frameNode, value);
    ACE_GET_NODE_PAINT_PROPERTY_WITH_DEFAULT_VALUE(ToggleButtonPaintProperty, IsOn, value, frameNode, value);
    return value;
}

void SetToggleOnChangeToEventHubForCustom(ArkUINodeHandle node, std::function<void(const bool)>&& onChange)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ToggleButtonEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChange(std::move(onChange));
}

void SetToggleOnChangeEventToEventHubForCustom(ArkUINodeHandle node, std::function<void(const bool)>&& onChangeEvent)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<ToggleButtonEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChangeEvent(std::move(onChangeEvent));
}

bool IsToggleButtonUseContentModifierForCustom(ArkUINodeHandle node)
{
    auto pattern = GetToggleButtonPattern(node);
    CHECK_NULL_RETURN(pattern, false);
    return pattern->UseContentModifier();
}

int32_t GetToggleButtonBuilderIdForCustom(ArkUINodeHandle node)
{
    auto pattern = GetToggleButtonPattern(node);
    CHECK_NULL_RETURN(pattern, ERROR_INT_CODE);
    return pattern->GetBuilderId();
}

void ResetToggleSelectedColorForCustom(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ToggleButtonModelNG::ResetSelectedColor(frameNode);
}

void SetToggleSelectedColorForCustom(ArkUINodeHandle node, const OHOS::Ace::Color& color)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ToggleButtonModelNG::SetSelectedColor(frameNode, color);
}

void SetToggleSelectedColorSetByUserForCustom(ArkUINodeHandle node, bool isByUser)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    ToggleButtonModelNG::SetSelectedColorSetByUser(frameNode, isByUser);
}

#ifndef CROSS_PLATFORM
void SetButtonFontSizeImpl(ArkUINodeHandle node, ArkUI_Float32 fontSizeValue, int fontSizeUnit)
{
    GetButtonImpl()->SetFontSize(Dimension(fontSizeValue, static_cast<DimensionUnit>(fontSizeUnit)));
}

void SetButtonFontWeightImpl(ArkUINodeHandle node, ArkUI_CharPtr fontWeight)
{
    std::string fontWeightStr = fontWeight;
    GetButtonImpl()->SetFontWeight(Framework::ConvertStrToFontWeight(fontWeightStr));
}

void SetButtonFontStyleImpl(ArkUINodeHandle node, int32_t fontStyle)
{
    if (fontStyle < 0 || fontStyle >= static_cast<int32_t>(FONT_STYLES.size())) {
        GetButtonImpl()->SetFontStyle(DEFAULT_FONT_STYLE);
    } else {
        GetButtonImpl()->SetFontStyle(FONT_STYLES[fontStyle]);
    }
}

void SetButtonFontFamilyPtrImpl(ArkUINodeHandle node, ArkUI_CharPtr fontFamily, void* familiesRawPtr)
{
    std::string familiesStr = fontFamily;
    auto fontFamilyResult = Framework::ConvertStrToFontFamilies(familiesStr);
    GetButtonImpl()->SetFontFamily(fontFamilyResult);
    if (SystemProperties::ConfigChangePerform()) {
        auto* families = reinterpret_cast<ResourceObject*>(familiesRawPtr);
        auto familiesResObj = AceType::Claim(families);
        GetButtonImpl()->CreateWithFamiliesResourceObj(familiesResObj, ButtonStringType::FONT_FAMILY);
    }
}

void SetJsButtonOnClickImpl(
    ArkUINodeHandle node, ArkUI_VoidPtr tapEventFunc, ArkUI_VoidPtr clickEventFunc, ArkUI_Float64 distanceThreshold)
{
    CHECK_NULL_VOID(tapEventFunc);
    CHECK_NULL_VOID(clickEventFunc);
    auto onTapFunc = reinterpret_cast<std::function<void(GestureEvent&)>*>(tapEventFunc);
    auto onClickFunc = reinterpret_cast<std::function<void(const ClickInfo*)>*>(clickEventFunc);
    GetButtonImpl()->OnClick(std::move(*onTapFunc), std::move(*onClickFunc), distanceThreshold);
}

void SetJsButtonRemoteMessageImpl(ArkUINodeHandle node, ArkUI_VoidPtr remoteMessageFunc)
{
    CHECK_NULL_VOID(remoteMessageFunc);
    auto callback = reinterpret_cast<RemoteCallback*>(remoteMessageFunc);
    GetButtonImpl()->SetRemoteMessage(std::move(*callback));
}

void SetJsButtonBackgroundColorPtrImpl(
    ArkUINodeHandle node, const ArkUI_InnerColor* backgroundColor, ArkUI_VoidPtr colorRawPtr, ArkUI_Bool colorFlag)
{
    CHECK_NULL_VOID(backgroundColor);
    const auto* backgroundColorPtr = reinterpret_cast<const Color*>(backgroundColor);

    if (SystemProperties::ConfigChangePerform() && colorRawPtr) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(colorRawPtr));
        if (!NG::ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
            return;
        }
        GetButtonImpl()->CreateWithColorResourceObj(resObj, ButtonColorType::BACKGROUND_COLOR);
    }
    GetButtonImpl()->BackgroundColor(*backgroundColorPtr, colorFlag);
}

void SetJsButtonWidthImpl(ArkUINodeHandle node, ArkUI_Float64 width, ArkUI_Int32 unit)
{
    GetButtonImpl()->SetWidth(Dimension(width, static_cast<DimensionUnit>(unit)));
}

void SetJsButtonHeightImpl(ArkUINodeHandle node, ArkUI_Float64 height, ArkUI_Int32 unit)
{
    GetButtonImpl()->SetHeight(Dimension(height, static_cast<DimensionUnit>(unit)));
}

void SetJsButtonAspectRatioImpl(ArkUINodeHandle node, ArkUI_Float64 aspectRatio)
{
    GetButtonImpl()->SetAspectRatio(aspectRatio);
}

void CreateButtonWithLabelImpl(ArkUI_VoidPtr createPara, ArkUI_VoidPtr buttonChildren)
{
    auto* para = reinterpret_cast<CreateWithPara*>(createPara);
    auto* children = reinterpret_cast<std::list<RefPtr<Component>>*>(buttonChildren);
    CHECK_NULL_VOID(para);
    CHECK_NULL_VOID(children);
    GetButtonImpl()->CreateWithLabel(*para, *children);
}

void CreateButtonImpl(ArkUI_VoidPtr createPara, ArkUI_VoidPtr buttonChildren)
{
    auto* para = reinterpret_cast<CreateWithPara*>(createPara);
    auto* children = reinterpret_cast<std::list<RefPtr<Component>>*>(buttonChildren);
    CHECK_NULL_VOID(para);
    CHECK_NULL_VOID(children);
    GetButtonImpl()->Create(*para, *children);
}

void CreateButtonWithChildImpl(ArkUI_VoidPtr createPara)
{
    auto* para = reinterpret_cast<CreateWithPara*>(createPara);
    CHECK_NULL_VOID(para);
    GetButtonImpl()->CreateWithChild(*para);
}

void SetJsButtonPaddingImpl(ArkUINodeHandle node, const ArkUIPaddingType* oldValue, const ArkUIPaddingType* newValue)
{
    Edge oldPadding;
    if (oldValue != nullptr) {
        auto left = oldValue->start.string
                        ? CalcDimension(oldValue->start.string)
                        : CalcDimension(oldValue->start.value, static_cast<DimensionUnit>(oldValue->start.unit));
        auto top = oldValue->top.string
                       ? CalcDimension(oldValue->top.string)
                       : CalcDimension(oldValue->top.value, static_cast<DimensionUnit>(oldValue->top.unit));
        auto right = oldValue->end.string
                         ? CalcDimension(oldValue->end.string)
                         : CalcDimension(oldValue->end.value, static_cast<DimensionUnit>(oldValue->end.unit));
        auto bottom = oldValue->bottom.string
                          ? CalcDimension(oldValue->bottom.string)
                          : CalcDimension(oldValue->bottom.value, static_cast<DimensionUnit>(oldValue->bottom.unit));
        oldPadding = Edge(left, top, right, bottom);
    }
    PaddingProperty padding;
    GetButtonImpl()->Padding(padding, oldPadding);
}

void SetJsButtonBorderRadiusImpl(ArkUINodeHandle node, ArkUI_Float64 value, ArkUI_Int32 unit)
{
    GetButtonImpl()->SetBorderRadius(Dimension(value, static_cast<DimensionUnit>(unit)));
}

void SetButtonFontColorUseColorPtrImpl(ArkUINodeHandle node, const ArkUI_InnerColor* fontColor, void* colorRawPtr)
{
    CHECK_NULL_VOID(fontColor);
    Color result = *(reinterpret_cast<const Color*>(fontColor));
    if (SystemProperties::ConfigChangePerform()) {
        CHECK_NULL_VOID(colorRawPtr);
        RefPtr<ResourceObject> resObj;
        resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(colorRawPtr));
        GetButtonImpl()->CreateWithColorResourceObj(resObj, ButtonColorType::FONT_COLOR);
    }
    GetButtonImpl()->SetFontColor(result);
}

void SetButtonTypeImpl(ArkUINodeHandle node, int type)
{
    if ((ButtonType)type == ButtonType::CAPSULE || (ButtonType)type == ButtonType::CIRCLE ||
        (ButtonType)type == ButtonType::ARC || (ButtonType)type == ButtonType::NORMAL ||
        (ButtonType)type == ButtonType::ROUNDED_RECTANGLE) {
        GetButtonImpl()->SetType(type);
    }
}

void SetButtonStateEffectImpl(ArkUINodeHandle node, ArkUI_Bool stateEffect)
{
    GetButtonImpl()->SetStateEffect(stateEffect);
}

void ResetButtonStateEffectImpl(ArkUINodeHandle node)
{
    GetButtonImpl()->SetStateEffect(DEFAULT_STATE_EFFECT);
}

void CreateButtonStringResourceObjImpl(ArkUINodeHandle node, ArkUI_VoidPtr resObj, ArkUI_Int32 buttonStringType)
{
    CHECK_NULL_VOID(resObj);
    auto resourceObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resObj));
    GetButtonImpl()->CreateWithStringResourceObj(resourceObj, static_cast<ButtonStringType>(buttonStringType));
}

void SetCreateWithLabelImpl(ArkUINodeHandle node, bool createWithLabel)
{
    GetButtonImpl()->SetCreateWithLabel(createWithLabel);
}

void ResetButtonTextAlignImpl(ArkUINodeHandle node)
{
    GetButtonImpl()->ResetTextAlign();
}

void SetJsButtonLabelStylePtrImpl(ArkUINodeHandle node, void* buttonParameters)
{
    CHECK_NULL_VOID(buttonParameters);
    GetButtonImpl()->SetLabelStyle(*reinterpret_cast<ButtonParameters*>(buttonParameters));
}

void SetJsButtonFontSizeImpl(ArkUINodeHandle node, ArkUI_Float64 fontSizeValue, ArkUI_Int32 fontSizeUnit)
{
    GetButtonImpl()->SetFontSize(Dimension(fontSizeValue, static_cast<DimensionUnit>(fontSizeUnit)));
}
#endif
} // namespace

const ArkUIButtonModifier* GetButtonDynamicModifier()
{
    static bool isCurrentUseNewPipeline = Container::IsCurrentUseNewPipeline();
    if (!isCurrentUseNewPipeline) {
#ifndef CROSS_PLATFORM
        CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
        static const ArkUIButtonModifier modifier = {
            .setButtonLabel = nullptr,
            .resetButtonLabel = nullptr,
            .setButtonType = SetButtonTypeImpl,
            .resetButtonType = nullptr,
            .setButtonStateEffect = SetButtonStateEffectImpl,
            .resetButtonStateEffect = ResetButtonStateEffectImpl,
            .setButtonFontColor = nullptr,
            .resetButtonFontColor = nullptr,
            .setButtonFontSize = SetButtonFontSizeImpl,
            .resetButtonFontSize = nullptr,
            .setButtonFontWeight = SetButtonFontWeightImpl,
            .resetButtonFontWeight = nullptr,
            .setButtonFontStyle = SetButtonFontStyleImpl,
            .resetButtonFontStyle = nullptr,
            .setButtonFontFamily = nullptr,
            .resetButtonFontFamily = nullptr,
            .setButtonLabelStyle = nullptr,
            .resetButtonLabelStyle = nullptr,
            .setButtonBackgroundColor = nullptr,
            .setButtonBackgroundColorWithColorSpace = nullptr,
            .resetButtonBackgroundColor = nullptr,
            .setButtonBorderRadius = nullptr,
            .resetButtonBorderRadius = nullptr,
            .setButtonFontWeightEnum = nullptr,
            .setButtonSize = nullptr,
            .resetButtonSize = nullptr,
            .getButtonLabel = nullptr,
            .getButtonFontSize = nullptr,
            .getButtonFontWeight = nullptr,
            .getButtonFontColor = nullptr,
            .setButtonRole = nullptr,
            .setButtonRoleOnly = nullptr,
            .resetButtonRole = nullptr,
            .setButtonStyle = nullptr,
            .setButtonStyleOnly = nullptr,
            .resetButtonStyle = nullptr,
            .setButtonControlSize = nullptr,
            .resetButtonControlSize = nullptr,
            .getButtonType = nullptr,
            .setButtonLabelWithCheck = nullptr,
            .resetButtonLabelWithCheck = nullptr,
            .setButtonOptions = nullptr,
            .resetButtonOptions = nullptr,
            .setCreateWithLabel = SetCreateWithLabelImpl,
            .createButtonWithLabel = CreateButtonWithLabelImpl,
            .createButton = CreateButtonImpl,
            .createButtonWithChild = CreateButtonWithChildImpl,
            .createButtonStringResourceObj = CreateButtonStringResourceObjImpl,
            .setButtonMinFontScale = nullptr,
            .resetButtonMinFontScale = nullptr,
            .setButtonMaxFontScale = nullptr,
            .resetButtonMaxFontScale = nullptr,
            .getButtonMinFontScale = nullptr,
            .getButtonMaxFontScale = nullptr,
            .setButtonFontColorPtr = nullptr,
            .setButtonFontColorUseColorPtr = SetButtonFontColorUseColorPtrImpl,
            .setButtonFontFamilyPtr = SetButtonFontFamilyPtrImpl,
            .setButtonLabelStylePtr = nullptr,
            .setButtonBackgroundColorWithColorSpacePtr = nullptr,
            .setButtonMinFontScalePtr = nullptr,
            .setButtonMaxFontScalePtr = nullptr,
            .setButtonBackgroundColorPtr = nullptr,
            .setButtonFontColorWithPlaceholder = nullptr,
            .resetButtonTextAlign = ResetButtonTextAlignImpl,
            .setJsButtonLabelStylePtr = SetJsButtonLabelStylePtrImpl,
            .setJsButtonOnClick = SetJsButtonOnClickImpl,
            .setJsButtonRemoteMessage = SetJsButtonRemoteMessageImpl,
            .setJsButtonBackgroundColorPtr = SetJsButtonBackgroundColorPtrImpl,
            .setJsButtonWidth = SetJsButtonWidthImpl,
            .setJsButtonHeight = SetJsButtonHeightImpl,
            .setJsButtonAspectRatio = SetJsButtonAspectRatioImpl,
            .setJsButtonPadding = SetJsButtonPaddingImpl,
            .setJsButtonBorderRadius = SetJsButtonBorderRadiusImpl,
            .setJsButtonLocalizedBorderRadius = nullptr,
            .resetJsButtonBorderRadius = nullptr,
            .setJsButtonFontSize = SetJsButtonFontSizeImpl,
        };
        CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
        return &modifier;
#endif
    }
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIButtonModifier modifier = {
        .setButtonLabel = SetButtonLabel,
        .resetButtonLabel = ResetButtonLabel,
        .setButtonType = SetButtonType,
        .resetButtonType = ResetButtonType,
        .setButtonStateEffect = SetButtonStateEffect,
        .resetButtonStateEffect = ResetButtonStateEffect,
        .setButtonFontColor = SetButtonFontColor,
        .resetButtonFontColor = ResetButtonFontColor,
        .setButtonFontSize = SetButtonFontSize,
        .resetButtonFontSize = ResetButtonFontSize,
        .setButtonFontWeight = SetButtonFontWeight,
        .resetButtonFontWeight = ResetButtonFontWeight,
        .setButtonFontStyle = SetButtonFontStyle,
        .resetButtonFontStyle = ResetButtonFontStyle,
        .setButtonFontFamily = SetButtonFontFamily,
        .resetButtonFontFamily = ResetButtonFontFamily,
        .setButtonLabelStyle = SetButtonLabelStyle,
        .resetButtonLabelStyle = ResetButtonLabelStyle,
        .setButtonBackgroundColor = SetButtonBackgroundColor,
        .setButtonBackgroundColorWithColorSpace = SetButtonBackgroundColorWithColorSpace,
        .resetButtonBackgroundColor = ResetButtonBackgroundColor,
        .setButtonBorderRadius = SetButtonBorderRadius,
        .resetButtonBorderRadius = ResetButtonBorderRadius,
        .setButtonFontWeightEnum = SetButtonFontWeightEnum,
        .setButtonSize = SetButtonSize,
        .resetButtonSize = ResetButtonSize,
        .getButtonLabel = GetButtonLabel,
        .getButtonFontSize = GetButtonFontSize,
        .getButtonFontWeight = GetButtonFontWeight,
        .getButtonFontColor = GetButtonFontColor,
        .setButtonRole = SetButtonRole,
        .setButtonRoleOnly = SetButtonRoleOnly,
        .resetButtonRole = ResetButtonRole,
        .setButtonStyle = SetButtonStyle,
        .setButtonStyleOnly = SetButtonStyleOnly,
        .resetButtonStyle = ResetButtonStyle,
        .setButtonControlSize = SetButtonControlSize,
        .resetButtonControlSize = ResetButtonControlSize,
        .getButtonType = GetButtonType,
        .setButtonLabelWithCheck = SetButtonLabelWithCheck,
        .resetButtonLabelWithCheck = ResetButtonLabelWithCheck,
        .setButtonOptions = SetButtonOptions,
        .resetButtonOptions = ResetButtonOptions,
        .setCreateWithLabel = SetCreateWithLabel,
        .createButtonWithLabel = CreateButtonWithLabel,
        .createButton = CreateButton,
        .createButtonWithChild = CreateButtonWithChild,
        .createButtonStringResourceObj = CreateButtonStringResourceObj,
        .setButtonMinFontScale = SetButtonMinFontScale,
        .resetButtonMinFontScale = ResetButtonMinFontScale,
        .setButtonMaxFontScale = SetButtonMaxFontScale,
        .resetButtonMaxFontScale = ResetButtonMaxFontScale,
        .getButtonMinFontScale = GetButtonMinFontScale,
        .getButtonMaxFontScale = GetButtonMaxFontScale,
        .setButtonFontColorPtr = SetButtonFontColorPtr,
        .setButtonFontColorUseColorPtr = SetButtonFontColorUseColorPtr,
        .setButtonFontFamilyPtr = SetButtonFontFamilyPtr,
        .setButtonLabelStylePtr = SetButtonLabelStylePtr,
        .setButtonBackgroundColorWithColorSpacePtr = SetButtonBackgroundColorWithColorSpacePtr,
        .setButtonMinFontScalePtr = SetButtonMinFontScalePtr,
        .setButtonMaxFontScalePtr = SetButtonMaxFontScalePtr,
        .setButtonBackgroundColorPtr = SetButtonBackgroundColorPtr,
        .setButtonFontColorWithPlaceholder = SetButtonFontColorWithPlaceholder,
        .resetButtonTextAlign = ResetButtonTextAlign,
        .setJsButtonLabelStylePtr = SetJsButtonLabelStylePtr,
        .setJsButtonOnClick = SetJsButtonOnClick,
        .setJsButtonRemoteMessage = nullptr,
        .setJsButtonBackgroundColorPtr = SetJsButtonBackgroundColorPtr,
        .setJsButtonWidth = nullptr,
        .setJsButtonHeight = nullptr,
        .setJsButtonAspectRatio = nullptr,
        .setJsButtonPadding = SetJsButtonPadding,
        .setJsButtonBorderRadius = SetJsButtonBorderRadius,
        .setJsButtonLocalizedBorderRadius = SetJsButtonLocalizedBorderRadius,
        .resetJsButtonBorderRadius = ResetJsButtonBorderRadius,
        .setJsButtonFontSize = SetJsButtonFontSize,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

const CJUIButtonModifier* GetCJUIButtonModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIButtonModifier modifier = {
        .setButtonLabel = SetButtonLabel,
        .resetButtonLabel = ResetButtonLabel,
        .setButtonType = SetButtonType,
        .resetButtonType = ResetButtonType,
        .setButtonStateEffect = SetButtonStateEffect,
        .resetButtonStateEffect = ResetButtonStateEffect,
        .setButtonFontColor = SetButtonFontColor,
        .resetButtonFontColor = ResetButtonFontColor,
        .setButtonFontSize = SetButtonFontSize,
        .resetButtonFontSize = ResetButtonFontSize,
        .setButtonFontWeight = SetButtonFontWeight,
        .resetButtonFontWeight = ResetButtonFontWeight,
        .setButtonFontStyle = SetButtonFontStyle,
        .resetButtonFontStyle = ResetButtonFontStyle,
        .setButtonFontFamily = SetButtonFontFamily,
        .resetButtonFontFamily = ResetButtonFontFamily,
        .setButtonLabelStyle = SetButtonLabelStyle,
        .resetButtonLabelStyle = ResetButtonLabelStyle,
        .setButtonBackgroundColor = SetButtonBackgroundColor,
        .setButtonBackgroundColorWithColorSpace = SetButtonBackgroundColorWithColorSpace,
        .resetButtonBackgroundColor = ResetButtonBackgroundColor,
        .setButtonBorderRadius = SetButtonBorderRadius,
        .resetButtonBorderRadius = ResetButtonBorderRadius,
        .setButtonFontWeightEnum = SetButtonFontWeightEnum,
        .setButtonSize = SetButtonSize,
        .resetButtonSize = ResetButtonSize,
        .getButtonLabel = GetButtonLabel,
        .getButtonFontSize = GetButtonFontSize,
        .getButtonFontWeight = GetButtonFontWeight,
        .getButtonFontColor = GetButtonFontColor,
        .setButtonRole = SetButtonRole,
        .resetButtonRole = ResetButtonRole,
        .setButtonStyle = SetButtonStyle,
        .resetButtonStyle = ResetButtonStyle,
        .setButtonControlSize = SetButtonControlSize,
        .resetButtonControlSize = ResetButtonControlSize,
        .getButtonType = GetButtonType,
        .setButtonLabelWithCheck = SetButtonLabelWithCheck,
        .resetButtonLabelWithCheck = ResetButtonLabelWithCheck,
        .setButtonOptions = SetButtonOptions,
        .resetButtonOptions = ResetButtonOptions,
        .setCreateWithLabel = SetCreateWithLabel,
        .setButtonMinFontScale = SetButtonMinFontScale,
        .resetButtonMinFontScale = ResetButtonMinFontScale,
        .setButtonMaxFontScale = SetButtonMaxFontScale,
        .resetButtonMaxFontScale = ResetButtonMaxFontScale,
        .getButtonMinFontScale = GetButtonMinFontScale,
        .getButtonMaxFontScale = GetButtonMaxFontScale,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

const ArkUIButtonCustomModifier* GetButtonCustomModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIButtonCustomModifier modifier = {
        .createFrameNode = CreateFrameNodeForCustom,
        .createButtonFrameNode = CreateButtonFrameNodeForCustom,
        .createButtonPattern = CreateButtonPatternForCustom,
        .createToggleButtonPattern = CreateToggleButtonPatternForCustom,
        .setComponentButtonType = SetComponentButtonTypeForCustom,
        .setSkipColorConfigurationUpdate = SetSkipColorConfigurationUpdateForCustom,
        .setClickedColor = SetClickedColorForCustom,
        .setBlendColor = SetBlendColorForCustom,
        .setBlendColorWithOptional = SetBlendColorWithOptionalForCustom,
        .setFocusBorderColor = SetFocusBorderColorForCustom,
        .setFocusBorderWidth = SetFocusBorderWidthForCustom,
        .setApplyShadow = SetApplyShadowForCustom,
        .handleButtonBackgroundColor = HandleButtonBackgroundColorForCustom,
        .setNavigationFocusBlendBgColor = SetNavigationFocusBlendBgColorForCustom,
        .setNavMenuItemNeedFocus = SetNavMenuItemNeedFocusForCustom,
        .setHasCustomPadding = SetHasCustomPaddingForCustom,
        .isToggleButtonPattern = IsToggleButtonPatternForCustom,
        .setToggleBackgroundColor = SetToggleBackgroundColorForCustom,
        .setToggleBackgroundColorWithFlag = SetToggleBackgroundColorWithFlagForCustom,
        .setButtonBorderRadius = SetButtonBorderRadiusForCustom,
        .setToggleBuilderFunc = SetToggleBuilderFuncForCustom,
        .setToggleButtonPress = SetToggleButtonPressForCustom,
        .setToggleOnChangeToEventHub = SetToggleOnChangeToEventHubForCustom,
        .setToggleOnChangeEventToEventHub = SetToggleOnChangeEventToEventHubForCustom,
        .isToggleButtonUseContentModifier = IsToggleButtonUseContentModifierForCustom,
        .getToggleButtonBuilderId = GetToggleButtonBuilderIdForCustom,
        .resetToggleSelectedColor = ResetToggleSelectedColorForCustom,
        .setToggleSelectedColor = SetToggleSelectedColorForCustom,
        .setToggleSelectedColorSetByUser = SetToggleSelectedColorSetByUserForCustom,
        .removeHoverListener = RemoveHoverListenerForCustom,
        .setButtonHover = SetButtonHoverForCustom,
        .getButtonHover = GetButtonHoverForCustom,
        .isButtonLayoutProperty = IsButtonLayoutPropertyForCustom,
        .setButtonLocalLocation = SetButtonLocalLocationForCustom,
        .getButtonLocalLocation = GetButtonLocalLocationForCustom,
        .isButtonPattern = IsButtonPatternForCustom,
        .updateToggleIsOnToPaintProp = UpdateToggleIsOnToPaintPropForCustom,
        .getToggleIsOnFromPaintProp = GetToggleIsOnFromPaintPropForCustom,
        .updateTypeToLayoutProp = UpdateTypeToLayoutPropForCustom,
        .setStateEffectToEventHub = SetStateEffectToEventHubForCustom,
        .getStateEffectFromEventHub = GetStateEffectFromEventHubForCustom,
        .updateBackgroundColorFlagByUserToLayoutProp = UpdateBackgroundColorFlagByUserToLayoutPropForCustom,
        .updateLabelToLayoutProp = UpdateLabelToLayoutPropForCustom,
        .updateFontSizeToLayoutProp = UpdateFontSizeToLayoutPropForCustom,
        .updateFontColorToLayoutProp = UpdateFontColorToLayoutPropForCustom,
        .updateFontWeightToLayoutProp = UpdateFontWeightToLayoutPropForCustom,
        .updateFontColorFlagByUserToLayoutProp = UpdateFontColorFlagByUserToLayoutPropForCustom,
        .updateFontStyleToLayoutProp = UpdateFontStyleToLayoutPropForCustom,
        .updateFontFamilyToLayoutProp = UpdateFontFamilyToLayoutPropForCustom,
        .updateButtonStyleToLayoutProp = UpdateButtonStyleToLayoutPropForCustom,
        .updateButtonRoleToLayoutProp = UpdateButtonRoleToLayoutPropForCustom,
        .updateControlSizeToLayoutProp = UpdateControlSizeToLayoutPropForCustom,
        .getButtonStyleFromLayoutProp = GetButtonStyleFromLayoutPropForCustom,
        .getButtonRoleFromLayoutProp = GetButtonRoleFromLayoutPropForCustom,
        .updateAutoDisableToLayoutProp = UpdateAutoDisableToLayoutPropForCustom,
        .getAutoDisableFromLayoutProp = GetAutoDisableFromLayoutPropForCustom,
        .hasFontColorFromLayoutProp = HasFontColorFromLayoutPropForCustom,
        .updateCreateWithLabelToLayoutProp = UpdateCreateWithLabelToLayoutPropForCustom,
        .updateBorderRadiusToLayoutProp = UpdateBorderRadiusToLayoutPropForCustom,
        .updateTextOverflowToLayoutProp = UpdateTextOverflowToLayoutPropForCustom,
        .updateMaxLinesToLayoutProp = UpdateMaxLinesToLayoutPropForCustom,
        .getBorderRadiusFromLayoutProp = GetBorderRadiusFromLayoutPropForCustom,
        .getFontSizeFromLayoutProp = GetFontSizeFromLayoutPropForCustom,
        .getFontColorFromLayoutProp = GetFontColorFromLayoutPropForCustom,
        .getLabelFromLayoutProp = GetLabelFromLayoutPropForCustom,
        .resetFontSizeToLayoutProp = ResetFontSizeToLayoutPropForCustom,
        .setFontColorDefault = SetFontColorDefaultForCustom,
        .setBackgroundColorDefault = SetBackgroundColorDefaultForCustom,
        .setBackgroundColorToModelStatic = SetBackgroundColorToModelStaticForCustom,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

} // namespace OHOS::Ace::NG