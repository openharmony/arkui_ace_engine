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
#include "core/interfaces/native/node/button_modifier.h"

#include "bridge/common/utils/utils.h"
#include "core/common/container.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/pattern/button/button_model_ng.h"
#include "frameworks/core/components/button/button_theme.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t DEFAULT_BUTTON_TYPE = (int32_t)ButtonType::CAPSULE;
constexpr int32_t DEFAULT_BUTTON_TYPE_VERSION_EIGHTEEN = (int32_t)ButtonType::ROUNDED_RECTANGLE;
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
constexpr uint32_t INDEX_DIMENSION_MIN_FONT_SIZE_0 = 0;
constexpr uint32_t INDEX_DIMENSION_MAX_FONT_SIZE_1 = 1;
constexpr uint32_t INDEX_DIMENSION_FONT_SIZE_2 = 2;
constexpr uint32_t INDEX_STRING_ARRAY_COUNT = 0;
constexpr uint32_t INDEX_VALUE_ARRAY_COUNT = 1;
constexpr uint32_t INDEX_DIMENSION_ARRAY_COUNT = 2;
constexpr uint32_t INDEX_INVALID_FONT_FAMILY_0 = 0;
const std::string DEFAULT_FONT_FAMILY = "HarmonyOS Sans";
constexpr int32_t OFFSET_1 = 1;
constexpr int32_t OFFSET_2 = 2;
constexpr int32_t OFFSET_3 = 3;
constexpr int32_t BORDER_RADIUS_SIZE = 12; // BorderRadius array size
const std::vector<TextOverflow> TEXT_OVERFLOWS = { TextOverflow::NONE, TextOverflow::CLIP, TextOverflow::ELLIPSIS,
    TextOverflow::MARQUEE };
const std::vector<Ace::FontStyle> FONT_STYLES = { Ace::FontStyle::NORMAL, Ace::FontStyle::ITALIC };
const std::vector<TextHeightAdaptivePolicy> HEIGHT_ADAPTIVE_POLICY = { TextHeightAdaptivePolicy::MAX_LINES_FIRST,
    TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST, TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST };
const std::string NONE_FONT_FAMILY = "NoneFontFamily";
const uint32_t ERROR_UINT_CODE = -1;
const float ERROR_FLOAT_CODE = -1.0f;
const int32_t ERROR_INT_CODE = -1;
thread_local std::string g_strValue;

const std::unordered_map<int, DimensionUnit> DIMENSION_UNIT_MAP = {
    { -2, DimensionUnit::INVALID },
    { -1, DimensionUnit::NONE },
    { 0, DimensionUnit::PX },
    { 1, DimensionUnit::VP },
    { 2, DimensionUnit::FP },
    { 3, DimensionUnit::PERCENT },
    { 4, DimensionUnit::LPX },
    { 5, DimensionUnit::AUTO },
    { 6, DimensionUnit::CALC },
};

const std::vector<FontWeight> BUTTON_FONT_WEIGHTS = {
    FontWeight::W100,
    FontWeight::W200,
    FontWeight::W300,
    FontWeight::W400,
    FontWeight::W500,
    FontWeight::W600,
    FontWeight::W700,
    FontWeight::W800,
    FontWeight::W900,
    FontWeight::BOLD,
    FontWeight::BOLDER,
    FontWeight::LIGHTER,
    FontWeight::MEDIUM,
    FontWeight::NORMAL,
    FontWeight::REGULAR,
};
} // namespace

void SetOptionalBorderRadius(
    std::optional<Dimension>& optionalDimension, const ArkUI_Float32* values, int32_t valuesSize, int32_t& offset)
{
    bool hasValue = static_cast<bool>(values[offset]);
    if (hasValue) {
        optionalDimension =
            Dimension(values[offset + OFFSET_1], static_cast<OHOS::Ace::DimensionUnit>(values[offset + OFFSET_2]));
    }
    offset = offset + OFFSET_3;
}

void SetButtonLabel(ArkUINodeHandle node, ArkUI_CharPtr label)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetLabel(frameNode, label);
}

void ResetButtonLabel(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetLabel(frameNode, "");
}

void SetButtonType(ArkUINodeHandle node, int type)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if ((ButtonType)type == ButtonType::CAPSULE || (ButtonType)type == ButtonType::CIRCLE ||
        (ButtonType)type == ButtonType::ARC || (ButtonType)type == ButtonType::NORMAL ||
        (ButtonType)type == ButtonType::ROUNDED_RECTANGLE) {
        ButtonModelNG::SetType(frameNode, type);
    }
}

void ResetButtonType(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (frameNode->GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        ButtonModelNG::SetType(frameNode, DEFAULT_BUTTON_TYPE_VERSION_EIGHTEEN);
    } else {
        ButtonModelNG::SetType(frameNode, DEFAULT_BUTTON_TYPE);
    }

    return;
}

void SetButtonStateEffect(ArkUINodeHandle node, ArkUI_Bool stateEffect)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetStateEffect(frameNode, stateEffect);
}

void ResetButtonStateEffect(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetStateEffect(frameNode, DEFAULT_STATE_EFFECT);
}

void SetButtonFontColor(ArkUINodeHandle node, uint32_t fontColor)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetFontColor(frameNode, Color(fontColor));
}

void SetButtonFontColorPtr(ArkUINodeHandle node, uint32_t fontColor, void* colorRawPtr)
{
    CHECK_NULL_VOID(node);
    SetButtonFontColor(node, fontColor);
    if (SystemProperties::ConfigChangePerform()) {
        auto* frameNode = reinterpret_cast<FrameNode*>(node);
        CHECK_NULL_VOID(frameNode);
        auto* color = reinterpret_cast<ResourceObject*>(colorRawPtr);
        auto colorResObj = AceType::Claim(color);
        ButtonModelNG::CreateWithColorResourceObj(frameNode, colorResObj, ButtonColorType::FONT_COLOR);
    }
}

void ResetButtonFontColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto buttonTheme = pipeline->GetTheme<ButtonTheme>();
    CHECK_NULL_VOID(buttonTheme);
    Color textColor = buttonTheme->GetTextStyle().GetTextColor();
    ButtonModelNG::SetFontColor(frameNode, textColor);
    if (SystemProperties::ConfigChangePerform()) {
        ButtonModelNG::CreateWithColorResourceObj(frameNode, nullptr, ButtonColorType::FONT_COLOR);
    }
}

void ResetButtonFontSizeInternal(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto buttonTheme = pipeline->GetTheme<ButtonTheme>();
    CHECK_NULL_VOID(buttonTheme);
    CalcDimension fontSize = buttonTheme->GetTextStyle().GetFontSize();
    ButtonModelNG::SetFontSize(frameNode, fontSize);
}

void SetButtonFontSize(ArkUINodeHandle node, ArkUI_Float32 fontSizeValue, int fontSizeUnit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (LessNotEqual(fontSizeValue, 0.0)) {
        ResetButtonFontSizeInternal(node);
    } else {
        ButtonModelNG::SetFontSize(frameNode, CalcDimension(fontSizeValue, (DimensionUnit)fontSizeUnit));
    }
}

void ResetButtonFontSize(ArkUINodeHandle node)
{
    ResetButtonFontSizeInternal(node);
}

void SetButtonFontWeight(ArkUINodeHandle node, ArkUI_CharPtr fontWeight)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string fontWeightStr = fontWeight;
    ButtonModelNG::SetFontWeight(frameNode, Framework::ConvertStrToFontWeight(fontWeightStr));
}

void SetButtonFontWeightEnum(ArkUINodeHandle node, int fontWeight)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetFontWeight(frameNode, static_cast<FontWeight>(fontWeight));
}

void ResetButtonFontWeight(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetFontWeight(frameNode, DEFAULT_FONT_WEIGHT);
}

void SetButtonFontStyle(ArkUINodeHandle node, int32_t fontStyle)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (fontStyle < 0 || fontStyle >= static_cast<int32_t>(FONT_STYLES.size())) {
        ButtonModelNG::SetFontStyle(frameNode, DEFAULT_FONT_STYLE);
    } else {
        ButtonModelNG::SetFontStyle(frameNode, FONT_STYLES[fontStyle]);
    }
}

void ResetButtonFontStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetFontStyle(frameNode, DEFAULT_FONT_STYLE);
}

void SetButtonFontFamily(ArkUINodeHandle node, ArkUI_CharPtr fontFamily)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string familiesStr = fontFamily;
    std::vector<std::string> fontFamilyResult = Framework::ConvertStrToFontFamilies(familiesStr);
    ButtonModelNG::SetFontFamily(frameNode, fontFamilyResult);
}

void SetButtonFontFamilyPtr(ArkUINodeHandle node, ArkUI_CharPtr fontFamily, void* familiesRawPtr)
{
    CHECK_NULL_VOID(node);
    SetButtonFontFamily(node, fontFamily);
    if (SystemProperties::ConfigChangePerform()) {
        auto* frameNode = reinterpret_cast<FrameNode*>(node);
        CHECK_NULL_VOID(frameNode);
        auto* families = reinterpret_cast<ResourceObject*>(familiesRawPtr);
        auto familiesResObj = AceType::Claim(families);
        ButtonModelNG::CreateWithFamiliesResourceObj(frameNode, familiesResObj, ButtonStringType::FONT_FAMILY);
    }
}

void ResetButtonFontFamily(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string familiesStr = DEFAULT_FONT_FAMILY;
    std::vector<std::string> fontFamilyResult = Framework::ConvertStrToFontFamilies(familiesStr);
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

bool SetButtonDimension(
    const ArkUI_Float32* dimensionArray, uint32_t offset, const size_t dataCount,
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

void SetButtonDimensionParameters(
    const ArkUI_Float32* dimensionArray, const size_t dataCount, ButtonParameters& buttonParameters)
{
    CHECK_NULL_VOID(dimensionArray);
    uint32_t step = 3;
    uint32_t minFontSizeIndex = INDEX_DIMENSION_MIN_FONT_SIZE_0;
    std::optional<CalcDimension> minFontSizeOptional = std::nullopt;
    if (SetButtonDimension(dimensionArray, minFontSizeIndex, dataCount, minFontSizeOptional)) {
        buttonParameters.minFontSize = minFontSizeOptional;
    }
    uint32_t maxFontSizeIndex = INDEX_DIMENSION_MAX_FONT_SIZE_1 * step;
    std::optional<CalcDimension> maxFontSizeOptional = std::nullopt;
    if (SetButtonDimension(dimensionArray, maxFontSizeIndex, dataCount, maxFontSizeOptional)) {
        buttonParameters.maxFontSize = maxFontSizeOptional;
    }
    uint32_t fontSizeIndex = INDEX_DIMENSION_FONT_SIZE_2 * step;
    std::optional<CalcDimension> fontSizeOptional = std::nullopt;
    if (SetButtonDimension(dimensionArray, fontSizeIndex, dataCount, fontSizeOptional)) {
        buttonParameters.fontSize = fontSizeOptional;
    }
}

bool SetButtonValue(const int32_t* valueArray, uint32_t index, const size_t dataCount, int32_t& result)
{
    CHECK_NULL_RETURN(valueArray, false);
    uint32_t step = 2;
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
        std::vector<std::string> fontFamilyResult = Framework::ConvertStrToFontFamilies(familiesStr);
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
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ButtonParameters buttonParameters;
    SetButtonStringParameters(stringParameters, dataCountArray[INDEX_STRING_ARRAY_COUNT], buttonParameters);
    SetButtonValueParameters(valueArray, dataCountArray[INDEX_VALUE_ARRAY_COUNT], buttonParameters);
    SetButtonDimensionParameters(dimensionArray, dataCountArray[INDEX_DIMENSION_ARRAY_COUNT], buttonParameters);
    ButtonCompleteParameters(buttonParameters);
    ButtonModelNG::SetLabelStyle(frameNode, buttonParameters);
}

void SetButtonLabelStylePtr(ArkUINodeHandle node, ArkUI_CharPtr* stringParameters, const ArkUI_Int32* valueArray,
    const ArkUI_Float32* dimensionArray, const ArkUI_Uint32* dataCountArray, const ArkUIButtonSizeStruct& sizeResObj)
{
    CHECK_NULL_VOID(node);
    SetButtonLabelStyle(node, stringParameters, valueArray, dimensionArray, dataCountArray);
    if (SystemProperties::ConfigChangePerform()) {
        auto* frameNode = reinterpret_cast<FrameNode*>(node);
        CHECK_NULL_VOID(frameNode);
        auto* minFontSize = reinterpret_cast<ResourceObject*>(sizeResObj.minFontSize);
        auto minSizeResObj = AceType::Claim(minFontSize);
        ButtonModelNG::CreateWithDimensionFpResourceObj(frameNode, minSizeResObj,
            ButtonDimensionType::MIN_FONT_SIZE);
        auto* maxFontSize = reinterpret_cast<ResourceObject*>(sizeResObj.maxFontSize);
        auto maxSizeResObj = AceType::Claim(maxFontSize);
        ButtonModelNG::CreateWithDimensionFpResourceObj(frameNode, maxSizeResObj,
            ButtonDimensionType::MAX_FONT_SIZE);
    }
}

void ResetButtonLabelStyle(ArkUINodeHandle node)
{
    if (SystemProperties::ConfigChangePerform()) {
        auto* frameNode = reinterpret_cast<FrameNode*>(node);
        CHECK_NULL_VOID(frameNode);
        ButtonModelNG::CreateWithDimensionFpResourceObj(frameNode, nullptr, ButtonDimensionType::MIN_FONT_SIZE);
        ButtonModelNG::CreateWithDimensionFpResourceObj(frameNode, nullptr, ButtonDimensionType::MAX_FONT_SIZE);
    }
    return;
}

void SetButtonBackgroundColor(ArkUINodeHandle node, uint32_t color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::BackgroundColor(frameNode, Color(color), true);
}

void SetButtonBackgroundColorWithColorSpace(ArkUINodeHandle node, ArkUI_Uint32 color, ArkUI_Int32 colorSpace)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Color backgroundColor { color };
    if (ColorSpace::DISPLAY_P3 == colorSpace) {
        backgroundColor.SetColorSpace(ColorSpace::DISPLAY_P3);
    } else {
        backgroundColor.SetColorSpace(ColorSpace::SRGB);
    }
    ButtonModelNG::BackgroundColor(frameNode, backgroundColor, true);
}

void SetButtonBackgroundColorWithColorSpacePtr(ArkUINodeHandle node, ArkUI_Uint32 color,
    ArkUI_Int32 colorSpace, void* colorRawPtr)
{
    CHECK_NULL_VOID(node);
    SetButtonBackgroundColorWithColorSpace(node, color, colorSpace);
    if (SystemProperties::ConfigChangePerform()) {
        auto* frameNode = reinterpret_cast<FrameNode*>(node);
        CHECK_NULL_VOID(frameNode);
        auto* color = reinterpret_cast<ResourceObject*>(colorRawPtr);
        auto colorResObj = AceType::Claim(color);
        ButtonModelNG::CreateWithColorResourceObj(frameNode, colorResObj, ButtonColorType::BACKGROUND_COLOR);
    }
}

void ResetButtonBackgroundColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Color backgroundColor;
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto buttonTheme = pipeline->GetTheme<ButtonTheme>();
    CHECK_NULL_VOID(buttonTheme);
    backgroundColor = buttonTheme->GetBgColor();
    ButtonModelNG::BackgroundColor(frameNode, backgroundColor, false);
    if (SystemProperties::ConfigChangePerform()) {
        ButtonModelNG::CreateWithColorResourceObj(frameNode, nullptr, ButtonColorType::BACKGROUND_COLOR);
    }
}

/**
 * @param src source borderRadius
 * @param options option value
 * values[offset + 0], option[offset + 1], option[offset + 2]: borderRadius topLeft(hasValue, value, unit)
 * values[offset + 3], option[offset + 4], option[offset + 5]: borderRadius topRight(hasValue, value, unit)
 * values[offset + 6], option[offset + 7], option[offset + 8]: borderRadius bottomLeft(hasValue, value, unit)
 * values[offset + 9], option[offset + 10], option[offset + 11]: borderRadius bottomRight(hasValue, value, unit)
 * @param optionsLength options valuesSize
 */
void SetButtonBorderRadius(ArkUINodeHandle node, const ArkUI_Float32* values, int32_t valuesSize)
{
    if ((values == nullptr) || (valuesSize != BORDER_RADIUS_SIZE)) {
        return;
    }
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
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
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    OHOS::Ace::Dimension reset;
    ButtonModelNG::SetBorderRadius(frameNode, reset);
}

void SetButtonSize(
    ArkUINodeHandle node, ArkUI_CharPtr widthValue, int32_t widthUnit, ArkUI_CharPtr heightValue, int32_t heightUnit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string widthValueStr = std::string(widthValue);
    std::string heightValueStr = std::string(heightValue);
    std::optional<CalcDimension> widthInfo;
    std::optional<CalcDimension> heightInfo;
    if (widthValueStr != "undefined") {
        widthInfo = CalcDimension(StringUtils::StringToDouble(widthValueStr), (DimensionUnit)widthUnit);
    } else {
        ViewAbstract::ClearWidthOrHeight(frameNode, true);
    }
    if (heightValueStr != "undefined") {
        heightInfo = CalcDimension(StringUtils::StringToDouble(heightValueStr), (DimensionUnit)heightUnit);
    } else {
        ViewAbstract::ClearWidthOrHeight(frameNode, false);
    }
    ButtonModelNG::SetSize(frameNode, widthInfo, heightInfo);
}

void ResetButtonSize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::ClearWidthOrHeight(frameNode, true);
    ViewAbstract::ClearWidthOrHeight(frameNode, false);
}

ArkUI_CharPtr GetButtonLabel(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, "");
    g_strValue = ButtonModelNG::GetLabel(frameNode);
    return g_strValue.c_str();
}

ArkUI_Float32 GetButtonFontSize(ArkUINodeHandle node, ArkUI_Int32 unit)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return ButtonModelNG::GetFontSize(frameNode).GetNativeValue(static_cast<DimensionUnit>(unit));
}

ArkUI_Int32 GetButtonFontWeight(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Int32>(ButtonModelNG::GetFontWeight(frameNode));
}

ArkUI_Uint32 GetButtonFontColor(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_UINT_CODE);
    return ButtonModelNG::GetFontColor(frameNode).GetValue();
}

void SetButtonRole(ArkUINodeHandle node, ArkUI_Uint32 buttonRole)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ButtonRole role = ButtonRole::NORMAL;
    if (buttonRole >= static_cast<uint32_t>(ButtonRole::NORMAL) && buttonRole <=
    static_cast<uint32_t>(ButtonRole::ERROR)) {
        role = static_cast<ButtonRole>(buttonRole);
    }
    ButtonModelNG::SetRole(frameNode, role);
}

void ResetButtonRole(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetRole(frameNode, ButtonRole::NORMAL);
}

void SetButtonStyle(ArkUINodeHandle node, ArkUI_Uint32 buttonStyle)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ButtonStyleMode style = ButtonStyleMode::EMPHASIZE;
    if (buttonStyle >= static_cast<uint32_t>(ButtonStyleMode::NORMAL) && buttonStyle <=
    static_cast<uint32_t>(ButtonStyleMode::TEXT)) {
        style = static_cast<ButtonStyleMode>(buttonStyle);
    }
    ButtonModelNG::SetButtonStyle(frameNode, style);
}

void ResetButtonStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetButtonStyle(frameNode, ButtonStyleMode::EMPHASIZE);
}

void SetButtonControlSize(ArkUINodeHandle node, ArkUI_Uint32 controlSize)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ControlSize size = ControlSize::NORMAL;
    if (controlSize >= static_cast<uint32_t>(ControlSize::SMALL) && controlSize <=
    static_cast<uint32_t>(ControlSize::NORMAL)) {
        size = static_cast<ControlSize>(controlSize);
    }
    ButtonModelNG::SetControlSize(frameNode, size);
}

void ResetButtonControlSize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetControlSize(frameNode, ControlSize::NORMAL);
}

ArkUI_Int32 GetButtonType(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Int32>(ButtonModelNG::GetType(frameNode));
}

void SetButtonLabelWithCheck(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetLabelWithCheck(frameNode, value);
}

void ResetButtonLabelWithCheck(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetLabelWithCheck(frameNode, "");
}

void SetButtonOptions(ArkUINodeHandle node, ArkUI_Uint32 buttonStyle, ArkUI_Uint32 buttonRole)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ButtonStyleMode style = ButtonStyleMode::EMPHASIZE;
    if (buttonStyle >= static_cast<uint32_t>(ButtonStyleMode::NORMAL) && buttonStyle <=
    static_cast<uint32_t>(ButtonStyleMode::TEXT)) {
        style = static_cast<ButtonStyleMode>(buttonStyle);
    }
    ButtonRole role = ButtonRole::NORMAL;
    if (buttonRole >= static_cast<uint32_t>(ButtonRole::NORMAL) && buttonRole <=
    static_cast<uint32_t>(ButtonRole::ERROR)) {
        role = static_cast<ButtonRole>(buttonRole);
    }
    ButtonModelNG::ApplyTheme(frameNode, style, role);
}

void ResetButtonOptions(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
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
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetCreateWithLabel(frameNode, createWithLabel);
}

void SetButtonMinFontScale(ArkUINodeHandle node, ArkUI_Float32 minFontScale)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetMinFontScale(frameNode, minFontScale);
}

void SetButtonMinFontScalePtr(ArkUINodeHandle node, ArkUI_Float32 minFontScale, void* scaleRawPtr)
{
    CHECK_NULL_VOID(node);
    SetButtonMinFontScale(node, minFontScale);
    if (SystemProperties::ConfigChangePerform()) {
        auto* frameNode = reinterpret_cast<FrameNode*>(node);
        CHECK_NULL_VOID(frameNode);
        auto* scaleValue = reinterpret_cast<ResourceObject*>(scaleRawPtr);
        auto scaleResObj = AceType::Claim(scaleValue);
        ButtonModelNG::CreateWithDoubleResourceObj(frameNode, scaleResObj, ButtonDoubleType::MIN_FONT_SCALE);
    }
}

void ResetButtonMinFontScale(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetMinFontScale(frameNode, DEFAULT_MIN_FONT_SCALE);
    if (SystemProperties::ConfigChangePerform()) {
        ButtonModelNG::CreateWithDoubleResourceObj(frameNode, nullptr, ButtonDoubleType::MIN_FONT_SCALE);
    }
}

void SetButtonMaxFontScale(ArkUINodeHandle node, ArkUI_Float32 maxFontScale)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetMaxFontScale(frameNode, maxFontScale);
}

void SetButtonMaxFontScalePtr(ArkUINodeHandle node, ArkUI_Float32 maxFontScale, void* scaleRawPtr)
{
    CHECK_NULL_VOID(node);
    SetButtonMaxFontScale(node, maxFontScale);
    if (SystemProperties::ConfigChangePerform()) {
        auto* frameNode = reinterpret_cast<FrameNode*>(node);
        CHECK_NULL_VOID(frameNode);
        auto* scaleValue = reinterpret_cast<ResourceObject*>(scaleRawPtr);
        auto scaleResObj = AceType::Claim(scaleValue);
        ButtonModelNG::CreateWithDoubleResourceObj(frameNode, scaleResObj, ButtonDoubleType::MAX_FONT_SCALE);
    }
}

void ResetButtonMaxFontScale(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetMaxFontScale(frameNode, DEFAULT_MAX_FONT_SCALE);
    if (SystemProperties::ConfigChangePerform()) {
        ButtonModelNG::CreateWithDoubleResourceObj(frameNode, nullptr, ButtonDoubleType::MAX_FONT_SCALE);
    }
}

ArkUI_Float32 GetButtonMinFontScale(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return static_cast<ArkUI_Float32>(ButtonModelNG::GetMinFontScale(frameNode));
}

ArkUI_Float32 GetButtonMaxFontScale(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_FLOAT_CODE);
    return static_cast<ArkUI_Float32>(ButtonModelNG::GetMaxFontScale(frameNode));
}

namespace NodeModifier {
const ArkUIButtonModifier* GetButtonModifier()
{
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
        .setButtonFontColorPtr = SetButtonFontColorPtr,
        .setButtonFontFamilyPtr = SetButtonFontFamilyPtr,
        .setButtonLabelStylePtr = SetButtonLabelStylePtr,
        .setButtonBackgroundColorWithColorSpacePtr = SetButtonBackgroundColorWithColorSpacePtr,
        .setButtonMinFontScalePtr = SetButtonMinFontScalePtr,
        .setButtonMaxFontScalePtr = SetButtonMaxFontScalePtr,
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
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
