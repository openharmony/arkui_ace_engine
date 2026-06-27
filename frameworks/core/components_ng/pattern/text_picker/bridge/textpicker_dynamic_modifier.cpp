/*
 * Copyright (c) 2023-2026 Huawei Device Co., Ltd.
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
#include "native_type.h"

#include "bridge/common/utils/utils.h"
#include "core/common/dynamic_module_helper.h"
#include "core/common/resource/resource_parse_utils.h"
#include "core/components/dialog/dialog_theme.h"
#include "core/components/text/text_theme.h"
#include "core/components_ng/pattern/date_picker/picker_theme.h"
#include "core/components_ng/pattern/date_picker/picker_types.h"
#include "core/components_ng/pattern/tabs/tabs_model.h"
#include "core/components_ng/pattern/text_picker/textpicker_model_ng.h"
#include "core/interfaces/native/node/node_textpicker_modifier.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/core/components_ng/pattern/text_picker/bridge/textpicker_parser.h"

namespace OHOS::Ace {

std::unique_ptr<TextPickerModel> TextPickerModel::textPickerInstance_ = nullptr;
std::once_flag TextPickerModel::onceFlag_;
std::unique_ptr<TextPickerDialogModel> TextPickerDialogModel::textPickerDialogInstance_ = nullptr;
std::once_flag TextPickerDialogModel::onceFlag_;

TextPickerModel* TextPickerModel::GetInstance()
{
    std::call_once(onceFlag_, []() { textPickerInstance_.reset(new NG::TextPickerModelNG()); });
    return textPickerInstance_.get();
}

TextPickerDialogModel* TextPickerDialogModel::GetInstance()
{
    std::call_once(onceFlag_, []() { textPickerDialogInstance_.reset(new NG::TextPickerDialogModelNG()); });
    return textPickerDialogInstance_.get();
}

} // namespace OHOS::Ace
namespace OHOS::Ace::NG {
#ifndef CROSS_PLATFORM
TextPickerModel* GetTextPickerModelImpl()
{
    // Load the textPicker loader from frameworks/compatible/components/picker directory
    static auto loader = DynamicModuleHelper::GetInstance().GetLoaderByName("textPicker");
    static TextPickerModel* instance = loader ? reinterpret_cast<TextPickerModel*>(loader->CreateModel()) : nullptr;
    return instance;
}
TextPickerDialogModel* GetTextPickerDialogModelImpl()
{
    // Load the textPicker loader from frameworks/compatible/components/picker directory
    static auto loader = DynamicModuleHelper::GetInstance().GetLoaderByName("textPickerDialog");
    static TextPickerDialogModel* instance =
        loader ? reinterpret_cast<TextPickerDialogModel*>(loader->CreateModel()) : nullptr;
    return instance;
}
#endif
namespace {
constexpr int32_t POS_0 = 0;
constexpr int32_t POS_1 = 1;
constexpr int32_t POS_2 = 2;
constexpr uint32_t MAX_SIZE = 12;
constexpr int FONT_INFO_SIZE = 3;
constexpr int32_t DEFAULT_GROUP_DIVIDER_VALUES_COUNT = 3;
const char DEFAULT_DELIMITER = '|';
const int32_t ERROR_INT_CODE = -1;
constexpr float MAX_PERCENT = 100.0f;
constexpr bool DEFAULT_ENABLE_HAPTIC_FEEDBACK = true;
thread_local std::string g_strValue;
const std::vector<OHOS::Ace::FontStyle> FONT_STYLES = { OHOS::Ace::FontStyle::NORMAL, OHOS::Ace::FontStyle::ITALIC };
const std::vector<TextOverflow> TEXT_OVERFLOWS = { TextOverflow::NONE, TextOverflow::CLIP, TextOverflow::ELLIPSIS,
    TextOverflow::MARQUEE };

enum GetValueArrayIndex {
    GETCOLOR,
    GETTOPLEFT,
    GETTOPRIGHT,
    GETBOTTOMLEFT,
    GETBOTTOMRIGHT,
};
enum ValueArrayIndex {
    TOPLEFT,
    TOPRIGHT,
    BOTTOMLEFT,
    BOTTOMRIGHT,
};

void SetSelectedIndexSingle(FrameNode* frameNode, uint32_t* selectedValues, const int32_t size)
{
    std::vector<NG::RangeContent> rangeResult;
    TextPickerModelNG::GetSingleRange(frameNode, rangeResult);
    if (selectedValues[0] >= rangeResult.size()) {
        TextPickerModelNG::SetSelected(frameNode, 0);
    } else {
        TextPickerModelNG::SetSelected(frameNode, selectedValues[0]);
    }
}

void SetSelectedInternal(
    uint32_t count, std::vector<NG::TextCascadePickerOptions>& options, std::vector<uint32_t>& selectedValues)
{
    for (uint32_t i = 0; i < count; i++) {
        uint32_t val = selectedValues.size() > 0 ? selectedValues.size() - 1 : 0;
        if (i > val) {
            selectedValues.emplace_back(0);
        } else {
            if (selectedValues[i] >= options[i].rangeResult.size()) {
                selectedValues[i] = 0;
            }
        }
    }
}

void ProcessCascadeSelected(
    const std::vector<NG::TextCascadePickerOptions>& options, uint32_t index, std::vector<uint32_t>& selectedValues)
{
    const size_t size = options.size();
    if (size == 0) {
        return;
    }
    std::vector<std::string> rangeResultValue;
    for (size_t i = 0; i < size; i++) {
        rangeResultValue.emplace_back(options[i].rangeResult[0]);
    }
    uint32_t val = selectedValues.size() > 0 ? selectedValues.size() - 1 : 0;
    if (index > val) {
        selectedValues.emplace_back(0);
    }
    if (selectedValues[index] >= rangeResultValue.size()) {
        selectedValues[index] = 0;
    }
    if ((selectedValues[index] <= size - 1) && (options[selectedValues[index]].children.size() > 0)) {
        ProcessCascadeSelected(options[selectedValues[index]].children, index + 1, selectedValues);
    }
}

void SetSelectedIndexMultiInternal(FrameNode* frameNode, uint32_t count,
    std::vector<NG::TextCascadePickerOptions>& options, std::vector<uint32_t>& selectedValues)
{
    if (!TextPickerModelNG::IsCascade(frameNode)) {
        SetSelectedInternal(count, options, selectedValues);
    } else {
        TextPickerModelNG::SetHasSelectAttr(frameNode, true);
        ProcessCascadeSelected(options, 0, selectedValues);
        uint32_t maxCount = TextPickerModelNG::GetMaxCount(frameNode);
        if (selectedValues.size() < maxCount) {
            auto differ = maxCount - selectedValues.size();
            for (uint32_t i = 0; i < differ; i++) {
                selectedValues.emplace_back(0);
            }
        }
    }
}

void SetSelectedIndexSingleInternal(const std::vector<NG::TextCascadePickerOptions>& options, uint32_t count,
    uint32_t& selectedValue, std::vector<uint32_t>& selectedValues)
{
    if (options.size() > 0) {
        if (selectedValue >= options[0].rangeResult.size()) {
            selectedValue = 0;
        }
        selectedValues.emplace_back(selectedValue);
        for (uint32_t i = 1; i < count; i++) {
            selectedValues.emplace_back(0);
        }
    } else {
        for (uint32_t i = 0; i < count; i++) {
            selectedValues.emplace_back(0);
        }
    }
}

void SetSelectedIndexMulti(FrameNode* frameNode, uint32_t* inputs, const int32_t size)
{
    std::vector<NG::TextCascadePickerOptions> options;
    TextPickerModelNG::GetMultiOptions(frameNode, options);

    auto count = TextPickerModelNG::IsCascade(frameNode) ? TextPickerModelNG::GetMaxCount(frameNode) : options.size();
    std::vector<uint32_t> selectedValues;

    if (size >= 0) {
        selectedValues.assign(inputs, inputs + size);
        SetSelectedIndexMultiInternal(frameNode, count, options, selectedValues);
    } else {
        TextPickerModelNG::SetHasSelectAttr(frameNode, true);
        SetSelectedIndexSingleInternal(options, count, inputs[0], selectedValues);
    }
    TextPickerModelNG::SetSelecteds(frameNode, selectedValues);
}

void SetTextPickerEnableHapticFeedback(ArkUINodeHandle node, ArkUI_Bool isEnableHapticFeedback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextPickerModelNG::SetEnableHapticFeedback(frameNode, isEnableHapticFeedback);
}

void ResetTextPickerEnableHapticFeedback(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextPickerModelNG::SetEnableHapticFeedback(frameNode, DEFAULT_ENABLE_HAPTIC_FEEDBACK);
}

ArkUI_Bool GetTextPickerEnableHapticFeedback(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<ArkUI_Bool>(TextPickerModelNG::GetEnableHapticFeedback(frameNode));
}

ArkUI_Bool GetPickerThemeByFrameNode(FrameNode* frameNode, RefPtr<PickerTheme>& theme)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, false);
    theme = themeManager->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(theme, false);
    return true;
}

void InitTextPickerTextStyle(const char* fontInfo, uint32_t color, int32_t fontStyle, NG::PickerTextStyle& textStyle)
{
    std::vector<std::string> res;
    std::string fontValues = std::string(fontInfo);
    StringUtils::StringSplitter(fontValues, DEFAULT_DELIMITER, res);
    if (res.size() != FONT_INFO_SIZE) {
        return;
    }
    textStyle.fontSize = StringUtils::StringToCalcDimension(res[POS_0], false, DimensionUnit::FP);
    if (fontStyle >= 0 && fontStyle < static_cast<int32_t>(FONT_STYLES.size())) {
        textStyle.fontStyle = FONT_STYLES[fontStyle];
    } else {
        textStyle.fontStyle = FONT_STYLES[0];
    }
    textStyle.fontFamily = Framework::ConvertStrToFontFamilies(res[POS_2]);
    textStyle.fontWeight = StringUtils::StringToFontWeight(res[POS_1]);
    textStyle.textColor = Color(color);
}

void GetColorResourceObject(FrameNode* frameNode, PickerTextStyle& textStyle)
{
    if (SystemProperties::ConfigChangePerform()) {
        RefPtr<ResourceObject> colorResObj;
        Color result = textStyle.textColor.value();
        ResourceParseUtils::CompleteResourceObjectFromColor(
            colorResObj, result, ResourceParseUtils::MakeNativeNodeInfo(frameNode));
        if (colorResObj) {
            textStyle.textColor = result;
            textStyle.textColorResObj = colorResObj;
        }
    }
}

void SetTextPickerTextStyleResObj(
    NG::PickerTextStyle& textStyle, const struct ArkUIPickerTextStyleStruct* textStyleStruct)
{
    auto* fontSizePtr = reinterpret_cast<ResourceObject*>(textStyleStruct->fontSizeRawPtr);
    if (fontSizePtr) {
        textStyle.fontSizeResObj = AceType::Claim(fontSizePtr);
    }

    auto* fontFamilyPtr = reinterpret_cast<ResourceObject*>(textStyleStruct->fontFamilyRawPtr);
    if (fontFamilyPtr) {
        textStyle.fontFamilyResObj = AceType::Claim(fontFamilyPtr);
    }

    auto* textColorPtr = reinterpret_cast<ResourceObject*>(textStyleStruct->textColorRawPtr);
    if (textColorPtr) {
        textStyle.textColorResObj = AceType::Claim(textColorPtr);
    }

    auto* minFontSizePtr = reinterpret_cast<ResourceObject*>(textStyleStruct->minFontSizeRawPtr);
    if (minFontSizePtr) {
        textStyle.minFontSizeResObj = AceType::Claim(minFontSizePtr);
    }

    auto* maxFontSizePtr = reinterpret_cast<ResourceObject*>(textStyleStruct->maxFontSizeRawPtr);
    if (maxFontSizePtr) {
        textStyle.maxFontSizeResObj = AceType::Claim(maxFontSizePtr);
    }
}

void SetTextPickerBackgroundColor(ArkUINodeHandle node, ArkUI_Uint32 color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextPickerModelNG::SetBackgroundColor(frameNode, Color(color));
}

void ResetTextPickerBackgroundColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<DialogTheme>();
    CHECK_NULL_VOID(theme);
    TextPickerModelNG::SetBackgroundColor(frameNode, theme->GetBackgroundColor());
}

ArkUI_Int32 GetTextPickerCanLoop(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, 1);
    return TextPickerModelNG::GetCanLoop(frameNode);
}

void SetTextPickerCanLoop(ArkUINodeHandle node, int canLoop)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextPickerModelNG::SetCanLoop(frameNode, canLoop);
}

void ResetTextPickerCanLoop(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto pickerTheme = themeManager->GetTheme<PickerTheme>();
    TextPickerModelNG::SetCanLoop(frameNode, true);
}

void SetTextPickerDigitalCrownSensitivity(ArkUINodeHandle node, int32_t CrownSensitivity)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextPickerModelNG::SetDigitalCrownSensitivity(frameNode, CrownSensitivity);
}

void ResetTextPickerDigitalCrownSensitivity(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextPickerModelNG::SetDigitalCrownSensitivity(frameNode, DEFAULT_CROWNSENSITIVITY);
}

void GetTextPickerSelectedIndex(ArkUINodeHandle node, ArkUI_Uint32* values, ArkUI_Int32 size)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (TextPickerModelNG::IsSingle(frameNode)) {
        auto selectedValue = static_cast<ArkUI_Uint32>(TextPickerModelNG::getTextPickerSelectedIndex(frameNode));
        values[0] = selectedValue;
    } else {
        auto selectedValue = TextPickerModelNG::getTextPickerSelecteds(frameNode);
        if (static_cast<ArkUI_Uint32>(size) != selectedValue.size()) {
            return;
        }
        for (int i = 0; i < size; i++) {
            values[i] = selectedValue[i];
        }
    }
}

void SetTextPickerSelectedIndex(ArkUINodeHandle node, ArkUI_Uint32* values, ArkUI_Int32 size)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    if (TextPickerModelNG::IsSingle(frameNode)) {
        SetSelectedIndexSingle(frameNode, values, size);
    } else {
        SetSelectedIndexMulti(frameNode, values, size);
    }
}

void ResetTextPickerSelectedIndex(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<uint32_t> selectedValues;
    selectedValues.emplace_back(0);
    if (TextPickerModelNG::IsSingle(frameNode)) {
        SetSelectedIndexSingle(frameNode, selectedValues.data(), selectedValues.size());
    } else {
        SetSelectedIndexMulti(frameNode, selectedValues.data(), selectedValues.size());
    }
}

void SetTextPickerTextStyleBase(ArkUINodeHandle node, ArkUI_Uint32 color, ArkUI_CharPtr fontInfo, ArkUI_Int32 style,
    ArkUI_CharPtr minFontSize, ArkUI_CharPtr maxFontSize, ArkUI_Int32 overflow, bool isNeedGetResObj)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefPtr<PickerTheme> theme;
    if (!GetPickerThemeByFrameNode(frameNode, theme)) {
        return;
    }
    NG::PickerTextStyle textStyle;
    InitTextPickerTextStyle(fontInfo, color, style, textStyle);
    if (isNeedGetResObj) {
        textStyle.textColorSetByUser = true;
        GetColorResourceObject(frameNode, textStyle);
    }
    if (minFontSize) {
        textStyle.minFontSize = StringUtils::StringToCalcDimension(minFontSize, false, DimensionUnit::FP);
    }
    if (maxFontSize) {
        textStyle.maxFontSize = StringUtils::StringToCalcDimension(maxFontSize, false, DimensionUnit::FP);
    }
    if (overflow >= 0 && overflow < static_cast<int32_t>(TEXT_OVERFLOWS.size())) {
        textStyle.textOverflow = TEXT_OVERFLOWS[overflow];
    } else {
        textStyle.textOverflow = TEXT_OVERFLOWS[0];
    }
    TextPickerModelNG::SetNormalTextStyle(frameNode, theme, textStyle);
}

void SetTextPickerTextStyle(ArkUINodeHandle node, ArkUI_Uint32 color, ArkUI_CharPtr fontInfo, ArkUI_Int32 style,
    ArkUI_CharPtr minFontSize, ArkUI_CharPtr maxFontSize, ArkUI_Int32 overflow)
{
    SetTextPickerTextStyleBase(node, color, fontInfo, style, minFontSize, maxFontSize, overflow, false);
}

void SetTextPickerTextStylePtr(ArkUINodeHandle node, ArkUI_Uint32 color, ArkUI_CharPtr fontInfo, ArkUI_Int32 style,
    ArkUI_CharPtr minFontSize, ArkUI_CharPtr maxFontSize, ArkUI_Int32 overflow, bool isDefaultColor)
{
    SetTextPickerTextStyleBase(node, color, fontInfo, style, minFontSize, maxFontSize, overflow, !isDefaultColor);
}

void SetTextPickerTextStyleWithResObj(ArkUINodeHandle node, const struct ArkUIPickerTextStyleStruct* textStyleStruct)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefPtr<PickerTheme> theme;
    if (!GetPickerThemeByFrameNode(frameNode, theme)) {
        return;
    }
    NG::PickerTextStyle textStyle;
    textStyle.textColorSetByUser = textStyleStruct->textColorSetByUser;
    InitTextPickerTextStyle(
        textStyleStruct->fontInfo, textStyleStruct->textColor, textStyleStruct->fontStyle, textStyle);
    if (textStyleStruct->minFontSize) {
        textStyle.minFontSize =
            StringUtils::StringToCalcDimension(textStyleStruct->minFontSize, false, DimensionUnit::FP);
    }
    if (textStyleStruct->maxFontSize) {
        textStyle.maxFontSize =
            StringUtils::StringToCalcDimension(textStyleStruct->maxFontSize, false, DimensionUnit::FP);
    }
    if (textStyleStruct->textOverflow >= 0 &&
        textStyleStruct->textOverflow < static_cast<int32_t>(TEXT_OVERFLOWS.size())) {
        textStyle.textOverflow = TEXT_OVERFLOWS[textStyleStruct->textOverflow];
    } else {
        textStyle.textOverflow = TEXT_OVERFLOWS[0];
    }
    SetTextPickerTextStyleResObj(textStyle, textStyleStruct);
    TextPickerModelNG::SetNormalTextStyle(frameNode, theme, textStyle);
}

void ResetTextPickerTextStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::PickerTextStyle pickerTextStyle;
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto pickerTheme = themeManager->GetTheme<PickerTheme>();
    TextPickerModelNG::SetNormalTextStyle(frameNode, pickerTheme, pickerTextStyle);
}

void SetTextPickerSelectedTextStyleBase(ArkUINodeHandle node, ArkUI_Uint32 color, ArkUI_CharPtr fontInfo,
    ArkUI_Int32 style, ArkUI_CharPtr minFontSize, ArkUI_CharPtr maxFontSize, ArkUI_Int32 overflow, bool isNeedGetResObj)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefPtr<PickerTheme> theme;
    if (!GetPickerThemeByFrameNode(frameNode, theme)) {
        return;
    }
    NG::PickerTextStyle textStyle;
    InitTextPickerTextStyle(fontInfo, color, style, textStyle);
    if (isNeedGetResObj) {
        textStyle.textColorSetByUser = true;
        GetColorResourceObject(frameNode, textStyle);
    }
    if (minFontSize) {
        textStyle.minFontSize = StringUtils::StringToCalcDimension(minFontSize, false, DimensionUnit::FP);
    }
    if (maxFontSize) {
        textStyle.maxFontSize = StringUtils::StringToCalcDimension(maxFontSize, false, DimensionUnit::FP);
    }
    if (overflow >= 0 && overflow < static_cast<int32_t>(TEXT_OVERFLOWS.size())) {
        textStyle.textOverflow = TEXT_OVERFLOWS[overflow];
    } else {
        textStyle.textOverflow = TEXT_OVERFLOWS[0];
    }
    TextPickerModelNG::SetSelectedTextStyle(frameNode, theme, textStyle);
}

void SetTextPickerSelectedTextStyle(ArkUINodeHandle node, ArkUI_Uint32 color, ArkUI_CharPtr fontInfo, ArkUI_Int32 style,
    ArkUI_CharPtr minFontSize, ArkUI_CharPtr maxFontSize, ArkUI_Int32 overflow)
{
    SetTextPickerSelectedTextStyleBase(node, color, fontInfo, style, minFontSize, maxFontSize, overflow, false);
}

void SetTextPickerSelectedTextStylePtr(ArkUINodeHandle node, ArkUI_Uint32 color, ArkUI_CharPtr fontInfo,
    ArkUI_Int32 style, ArkUI_CharPtr minFontSize, ArkUI_CharPtr maxFontSize, ArkUI_Int32 overflow, bool isDefaultColor)
{
    SetTextPickerSelectedTextStyleBase(
        node, color, fontInfo, style, minFontSize, maxFontSize, overflow, !isDefaultColor);
}

void SetTextPickerSelectedTextStyleWithResObj(
    ArkUINodeHandle node, const struct ArkUIPickerTextStyleStruct* textStyleStruct)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefPtr<PickerTheme> theme;
    if (!GetPickerThemeByFrameNode(frameNode, theme)) {
        return;
    }
    NG::PickerTextStyle textStyle;
    textStyle.textColorSetByUser = textStyleStruct->textColorSetByUser;
    InitTextPickerTextStyle(
        textStyleStruct->fontInfo, textStyleStruct->textColor, textStyleStruct->fontStyle, textStyle);
    if (textStyleStruct->minFontSize) {
        textStyle.minFontSize =
            StringUtils::StringToCalcDimension(textStyleStruct->minFontSize, false, DimensionUnit::FP);
    }
    if (textStyleStruct->maxFontSize) {
        textStyle.maxFontSize =
            StringUtils::StringToCalcDimension(textStyleStruct->maxFontSize, false, DimensionUnit::FP);
    }
    if (textStyleStruct->textOverflow >= 0 &&
        textStyleStruct->textOverflow < static_cast<int32_t>(TEXT_OVERFLOWS.size())) {
        textStyle.textOverflow = TEXT_OVERFLOWS[textStyleStruct->textOverflow];
    } else {
        textStyle.textOverflow = TEXT_OVERFLOWS[0];
    }
    SetTextPickerTextStyleResObj(textStyle, textStyleStruct);
    TextPickerModelNG::SetSelectedTextStyle(frameNode, theme, textStyle);
}

void ResetTextPickerSelectedTextStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::PickerTextStyle pickerTextStyle;
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto pickerTheme = themeManager->GetTheme<PickerTheme>();
    TextPickerModelNG::SetSelectedTextStyle(frameNode, pickerTheme, pickerTextStyle);
}

void SetTextPickerDisappearTextStyleBase(ArkUINodeHandle node, ArkUI_Uint32 color, ArkUI_CharPtr fontInfo,
    ArkUI_Int32 style, ArkUI_CharPtr minFontSize, ArkUI_CharPtr maxFontSize, ArkUI_Int32 overflow, bool isNeedGetResObj)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefPtr<PickerTheme> theme;
    if (!GetPickerThemeByFrameNode(frameNode, theme)) {
        return;
    }
    NG::PickerTextStyle textStyle;
    InitTextPickerTextStyle(fontInfo, color, style, textStyle);
    if (isNeedGetResObj) {
        textStyle.textColorSetByUser = true;
        GetColorResourceObject(frameNode, textStyle);
    }
    if (minFontSize) {
        textStyle.minFontSize = StringUtils::StringToCalcDimension(minFontSize, false, DimensionUnit::FP);
    }
    if (maxFontSize) {
        textStyle.maxFontSize = StringUtils::StringToCalcDimension(maxFontSize, false, DimensionUnit::FP);
    }
    if (overflow >= 0 && overflow < static_cast<int32_t>(TEXT_OVERFLOWS.size())) {
        textStyle.textOverflow = TEXT_OVERFLOWS[overflow];
    } else {
        textStyle.textOverflow = TEXT_OVERFLOWS[0];
    }
    TextPickerModelNG::SetDisappearTextStyle(frameNode, theme, textStyle);
}

void SetTextPickerDisappearTextStyle(ArkUINodeHandle node, ArkUI_Uint32 color, ArkUI_CharPtr fontInfo,
    ArkUI_Int32 style, ArkUI_CharPtr minFontSize, ArkUI_CharPtr maxFontSize, ArkUI_Int32 overflow)
{
    SetTextPickerDisappearTextStyleBase(node, color, fontInfo, style, minFontSize, maxFontSize, overflow, false);
}

void SetTextPickerDisappearTextStylePtr(ArkUINodeHandle node, ArkUI_Uint32 color, ArkUI_CharPtr fontInfo,
    ArkUI_Int32 style, ArkUI_CharPtr minFontSize, ArkUI_CharPtr maxFontSize, ArkUI_Int32 overflow, bool isDefaultColor)
{
    SetTextPickerDisappearTextStyleBase(
        node, color, fontInfo, style, minFontSize, maxFontSize, overflow, !isDefaultColor);
}

void SetTextPickerDisappearTextStyleWithResObj(
    ArkUINodeHandle node, const struct ArkUIPickerTextStyleStruct* textStyleStruct)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefPtr<PickerTheme> theme;
    if (!GetPickerThemeByFrameNode(frameNode, theme)) {
        return;
    }
    NG::PickerTextStyle textStyle;
    textStyle.textColorSetByUser = textStyleStruct->textColorSetByUser;
    InitTextPickerTextStyle(
        textStyleStruct->fontInfo, textStyleStruct->textColor, textStyleStruct->fontStyle, textStyle);
    if (textStyleStruct->minFontSize) {
        textStyle.minFontSize =
            StringUtils::StringToCalcDimension(textStyleStruct->minFontSize, false, DimensionUnit::FP);
    }
    if (textStyleStruct->maxFontSize) {
        textStyle.maxFontSize =
            StringUtils::StringToCalcDimension(textStyleStruct->maxFontSize, false, DimensionUnit::FP);
    }
    if (textStyleStruct->textOverflow >= 0 &&
        textStyleStruct->textOverflow < static_cast<int32_t>(TEXT_OVERFLOWS.size())) {
        textStyle.textOverflow = TEXT_OVERFLOWS[textStyleStruct->textOverflow];
    } else {
        textStyle.textOverflow = TEXT_OVERFLOWS[0];
    }
    SetTextPickerTextStyleResObj(textStyle, textStyleStruct);
    TextPickerModelNG::SetDisappearTextStyle(frameNode, theme, textStyle);
}

void ResetTextPickerDisappearTextStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::PickerTextStyle pickerTextStyle;
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto pickerTheme = themeManager->GetTheme<PickerTheme>();
    TextPickerModelNG::SetDisappearTextStyle(frameNode, pickerTheme, pickerTextStyle);
}

ArkUI_Float32 GetTextPickerDefaultPickerItemHeight(ArkUINodeHandle node, ArkUI_Int32 dUnit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, -1.0f);
    return TextPickerModelNG::GetDefaultPickerItemHeight(frameNode).GetNativeValue(static_cast<DimensionUnit>(dUnit));
}

void SetTextPickerDefaultPickerItemHeight(ArkUINodeHandle node, float dVal, ArkUI_Int32 dUnit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextPickerModelNG::SetDefaultPickerItemHeight(frameNode, Dimension(dVal, static_cast<DimensionUnit>(dUnit)));
}

void ResetTextPickerDefaultPickerItemHeight(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto height = Dimension(0.0);
    TextPickerModelNG::SetDefaultPickerItemHeight(frameNode, height);
}

ArkUI_CharPtr GetTextPickerRangeStr(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, "");
    g_strValue = TextPickerModelNG::getTextPickerRange(frameNode);
    return g_strValue.c_str();
}

ArkUI_Int32 GetTextPickerSingleRange(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return TextPickerModelNG::GetTextPickerRangeType(frameNode);
}

void SetTextCascadePickChildrenRangeContent(
    std::vector<NG::TextCascadePickerOptions>& multiResult, ArkUITextCascadePickerRangeContentArray arry)
{
    for (int index = 0; index < arry->rangeContentArraySize; index++) {
        NG::TextCascadePickerOptions option;
        if (arry[index].text == nullptr) {
            continue;
        }
        option.rangeResult.push_back(arry[index].text);

        if (arry[index].children != nullptr) {
            SetTextCascadePickChildrenRangeContent(option.children, arry[index].children);
        }
        multiResult.push_back(option);
    }
}

void SetTextCascadePickRangeContent(
    ArkUINodeHandle node, ArkUITextCascadePickerRangeContentArray arry, ArkUI_Int32 rangeType)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<NG::TextCascadePickerOptions> multiResult;

    SetTextCascadePickChildrenRangeContent(multiResult, arry);
    TextPickerModelNG::SetHasSelectAttr(frameNode, true);
    TextPickerModelNG::SetIsCascade(frameNode, true);
    TextPickerModelNG::SetColumns(frameNode, multiResult);

    std::vector<std::string> values;
    for (int index = 0; index < arry->rangeContentArraySize; index++) {
        if (arry[index].text == nullptr) {
            continue;
        }
        values.emplace_back(arry[index].text);
    }
    TextPickerModelNG::SetValues(frameNode, values);
    TextPickerModelNG::SetTextPickerRangeType(frameNode, rangeType);
}

void SetTextPickerIconRangeStr(
    ArkUINodeHandle node, ArkUITextPickerRangeContentArray arry, ArkUI_Bool isSingleRange, ArkUI_Int32 rangeType)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextPickerModelNG::SetTextPickerSingeRange(static_cast<bool>(isSingleRange));
    std::vector<NG::RangeContent> result;
    for (int i = 0; i < arry->rangeContentArraySize; i++) {
        NG::RangeContent content;
        if (arry->rangeContent[i].text != nullptr) {
            content.text_ = arry->rangeContent[i].text;
        }
        if (arry->rangeContent[i].icon != nullptr) {
            content.icon_ = arry->rangeContent[i].icon;
        }
        result.emplace_back(content);
    }
    TextPickerModelNG::SetColumnKind(frameNode, MIXTURE);
    TextPickerModelNG::SetRange(frameNode, result);
    TextPickerModelNG::SetTextPickerRangeType(frameNode, rangeType);
}

void SetTextPickerRangeStr(
    ArkUINodeHandle node, ArkUI_CharPtr rangeStr, ArkUI_Bool isSingleRange, ArkUI_Int32 rangeType)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextPickerModelNG::SetTextPickerSingeRange(static_cast<bool>(isSingleRange));
    std::vector<std::string> getRangeVector;
    StringUtils::StringSplitter(std::string(rangeStr), ';', getRangeVector);
    if (isSingleRange) {
        std::vector<NG::RangeContent> result;
        for (const auto& text : getRangeVector) {
            NG::RangeContent content;
            content.icon_ = "";
            content.text_ = text;
            result.emplace_back(content);
        }
        TextPickerModelNG::SetColumnKind(frameNode, TEXT);
        TextPickerModelNG::SetRange(frameNode, result);
    } else {
        std::vector<NG::TextCascadePickerOptions> multiResult;
        for (const auto& text : getRangeVector) {
            NG::TextCascadePickerOptions option;
            StringUtils::StringSplitter(std::string(text), ',', option.rangeResult);
            multiResult.emplace_back(option);
        }
        TextPickerModelNG::SetColumns(frameNode, multiResult);
    }
    TextPickerModelNG::SetTextPickerRangeType(frameNode, rangeType);
}

ArkUI_CharPtr GetTextPickerValue(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, "");
    if (TextPickerModelNG::IsSingle(frameNode)) {
        g_strValue = TextPickerModelNG::getTextPickerValue(frameNode);
    } else {
        g_strValue = TextPickerModelNG::getTextPickerValues(frameNode);
    }
    return g_strValue.c_str();
}

void SetTextPickerValue(ArkUINodeHandle node, ArkUI_CharPtr valueStr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<std::string> getValueVector;
    StringUtils::StringSplitter(std::string(valueStr), ';', getValueVector);
    if (TextPickerModelNG::GetTextPickerSingeRange()) {
        TextPickerModelNG::SetValue(frameNode, valueStr);
    } else {
        TextPickerModelNG::SetValues(frameNode, getValueVector);
    }
}

void SetTextPickerColumnWidths(ArkUINodeHandle node, ArkUI_Float32* values, ArkUI_Int32 size)
{
    std::vector<Dimension> widths;
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    for (ArkUI_Int32 i = 0; i < size; i++) {
        widths.emplace_back(Dimension(values[i] * MAX_PERCENT, DimensionUnit::PERCENT));
    }
    TextPickerModelNG::SetColumnWidths(frameNode, widths);
}

void ResetTextPickerColumnWidths(ArkUINodeHandle node)
{
    std::vector<Dimension> widths;
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto childCount = frameNode->GetChildren().size();
    for (size_t i = 0; i < childCount; i++) {
        widths.emplace_back(Dimension(MAX_PERCENT / static_cast<float>(childCount), DimensionUnit::PERCENT));
    }
    TextPickerModelNG::SetColumnWidths(frameNode, widths);
}

ArkUI_Int32 GetTextPickerColumnWidthsSize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, 0);
    return TextPickerModelNG::GetColumnWidthsSize(frameNode);
}

void GetTextPickerColumnWidths(ArkUINodeHandle node, ArkUI_Float32* values)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto size = GetTextPickerColumnWidthsSize(node);
    std::vector<Dimension> widths = TextPickerModelNG::GetColumnWidths(frameNode);
    for (int32_t i = 0; i < size; i++) {
        values[i] = widths[i].Value() / MAX_PERCENT;
    }
}

ArkUI_CharPtr GetTextPickerSelectedTextStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, "");
    PickerTextStyle pickerTextStyle = TextPickerModelNG::getSelectedTextStyle(frameNode);
    std::vector<std::string> fontFamilies = pickerTextStyle.fontFamily.value_or(std::vector<std::string>());
    std::string families;
    if (fontFamilies.size() == 0) {
        fontFamilies.emplace_back("HarmonyOS Sans");
    }
    // set index start
    int index = 0;
    for (auto& family : fontFamilies) {
        families += family;
        if (index != static_cast<int>(fontFamilies.size()) - 1) {
            families += ",";
        }
        index++;
    }
    g_strValue = pickerTextStyle.textColor->ColorToString() + ";";
    g_strValue = g_strValue + std::to_string(static_cast<int>(pickerTextStyle.fontSize->ConvertToFp())) + ";";
    g_strValue = g_strValue + StringUtils::ToString(pickerTextStyle.fontWeight.value_or(FontWeight::W100)) + ";";
    g_strValue = g_strValue + families + ";";
    g_strValue =
        g_strValue + StringUtils::ToStringNDK(pickerTextStyle.fontStyle.value_or(OHOS::Ace::FontStyle::NORMAL));
    return g_strValue.c_str();
}

ArkUI_CharPtr GetTextPickerTextStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, "");
    PickerTextStyle pickerTextStyle = TextPickerModelNG::getNormalTextStyle(frameNode);
    std::vector<std::string> fontFamilies = pickerTextStyle.fontFamily.value_or(std::vector<std::string>());
    std::string families;
    if (fontFamilies.size() == 0) {
        fontFamilies.emplace_back("HarmonyOS Sans");
    }
    // set index start
    int index = 0;
    for (auto& family : fontFamilies) {
        families += family;
        if (index != static_cast<int>(fontFamilies.size()) - 1) {
            families += ",";
        }
        index++;
    }
    g_strValue = pickerTextStyle.textColor->ColorToString() + ";";
    g_strValue = g_strValue + std::to_string(static_cast<int>(pickerTextStyle.fontSize->ConvertToFp())) + ";";
    g_strValue = g_strValue + StringUtils::ToString(pickerTextStyle.fontWeight.value_or(FontWeight::W100)) + ";";
    g_strValue = g_strValue + families + ";";
    g_strValue =
        g_strValue + StringUtils::ToStringNDK(pickerTextStyle.fontStyle.value_or(OHOS::Ace::FontStyle::NORMAL));
    return g_strValue.c_str();
}

ArkUI_CharPtr GetTextPickerDisappearTextStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, "");
    PickerTextStyle pickerTextStyle = TextPickerModelNG::getDisappearTextStyle(frameNode);
    std::vector<std::string> fontFamilies = pickerTextStyle.fontFamily.value_or(std::vector<std::string>());
    std::string families;
    if (fontFamilies.size() == 0) {
        fontFamilies.emplace_back("HarmonyOS Sans");
    }
    // set index start
    int index = 0;
    for (auto& family : fontFamilies) {
        families += family;
        if (index != static_cast<int>(fontFamilies.size()) - 1) {
            families += ",";
        }
        index++;
    }
    g_strValue = pickerTextStyle.textColor->ColorToString() + ";";
    g_strValue = g_strValue + std::to_string(static_cast<int>(pickerTextStyle.fontSize->ConvertToFp())) + ";";
    g_strValue = g_strValue + StringUtils::ToString(pickerTextStyle.fontWeight.value_or(FontWeight::W100)) + ";";
    g_strValue = g_strValue + families + ";";
    g_strValue =
        g_strValue + StringUtils::ToStringNDK(pickerTextStyle.fontStyle.value_or(OHOS::Ace::FontStyle::NORMAL));
    return g_strValue.c_str();
}

void SetTextPickerDivider(
    ArkUINodeHandle node, ArkUI_Uint32 color, const ArkUI_Float32* values, const ArkUI_Int32* units, ArkUI_Int32 length)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    if (length != DEFAULT_GROUP_DIVIDER_VALUES_COUNT) {
        return;
    }

    NG::ItemDivider divider;
    divider.color = Color(color);
    divider.strokeWidth = Dimension(values[POS_0], static_cast<OHOS::Ace::DimensionUnit>(units[POS_0]));
    divider.startMargin = Dimension(values[POS_1], static_cast<OHOS::Ace::DimensionUnit>(units[POS_1]));
    divider.endMargin = Dimension(values[POS_2], static_cast<OHOS::Ace::DimensionUnit>(units[POS_2]));

    TextPickerModelNG::SetDivider(frameNode, divider);
}

void SetTextPickerDividerWithResObj(ArkUINodeHandle node, ArkUI_Uint32 color, const ArkUI_Float32* values,
    const ArkUI_Int32* units, ArkUI_Int32 length, const struct ArkUIPickerDividerResObjStruct* dividerResObjStr,
    ArkUI_Bool isDefaultColor)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    if (length != DEFAULT_GROUP_DIVIDER_VALUES_COUNT) {
        return;
    }

    NG::ItemDivider divider;
    divider.color = Color(color);
    divider.isDefaultColor = isDefaultColor;
    divider.strokeWidth = Dimension(values[POS_0], static_cast<OHOS::Ace::DimensionUnit>(units[POS_0]));
    divider.startMargin = Dimension(values[POS_1], static_cast<OHOS::Ace::DimensionUnit>(units[POS_1]));
    divider.endMargin = Dimension(values[POS_2], static_cast<OHOS::Ace::DimensionUnit>(units[POS_2]));

    auto* strokeWidthPtr = reinterpret_cast<ResourceObject*>(dividerResObjStr->strokeWidthRawPtr);
    auto strokeWidthResObj = AceType::Claim(strokeWidthPtr);
    divider.strokeWidthResObj = strokeWidthResObj;

    auto* colorPtr = reinterpret_cast<ResourceObject*>(dividerResObjStr->colorRawPtr);
    auto colorResObj = AceType::Claim(colorPtr);
    divider.colorResObj = colorResObj;

    auto* startMarginPtr = reinterpret_cast<ResourceObject*>(dividerResObjStr->startMarginRawPtr);
    auto startMarginResObj = AceType::Claim(startMarginPtr);
    divider.startMarginResObj = startMarginResObj;

    auto* endMarginPtr = reinterpret_cast<ResourceObject*>(dividerResObjStr->endMarginRawPtr);
    auto endMarginResObj = AceType::Claim(endMarginPtr);
    divider.endMarginResObj = endMarginResObj;
    TextPickerModelNG::SetDivider(frameNode, divider);
}

void ResetTextPickerDivider(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto pickerTheme = themeManager->GetTheme<PickerTheme>();
    NG::ItemDivider divider;
    Dimension defaultStrokeWidth = 0.0_vp;
    Color defaultColor = Color::TRANSPARENT;
    if (pickerTheme) {
        defaultStrokeWidth = pickerTheme->GetDividerThickness();
        defaultColor = pickerTheme->GetDividerColor();
        divider.strokeWidth = defaultStrokeWidth;
        divider.color = defaultColor;
    }
    TextPickerModelNG::TextPickerRemoveResObj(frameNode, "textPicker.divider");
    TextPickerModelNG::SetDivider(frameNode, divider);
}

void ResetTextPickerDividerNull(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::ItemDivider divider;
    TextPickerModelNG::TextPickerRemoveResObj(frameNode, "textPicker.divider");
    TextPickerModelNG::SetDivider(frameNode, divider);
}

void SetTextPickerGradientHeight(ArkUINodeHandle node, ArkUI_Float32 dVal, ArkUI_Int32 dUnit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextPickerModelNG::SetGradientHeight(frameNode, Dimension(dVal, static_cast<DimensionUnit>(dUnit)));
}

void SetTextPickerGradientHeightWithResObj(
    ArkUINodeHandle node, ArkUI_Float32 dVal, ArkUI_Int32 dUnit, void* heightRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto* heightPtr = reinterpret_cast<ResourceObject*>(heightRawPtr);
    auto heightResObj = AceType::Claim(heightPtr);
    TextPickerModelNG::ParseGradientHeight(frameNode, heightResObj);
    TextPickerModelNG::SetGradientHeight(frameNode, Dimension(dVal, static_cast<DimensionUnit>(dUnit)));
}

void ResetTextPickerGradientHeight(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto pickerTheme = themeManager->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);

    CalcDimension height;
    if (pickerTheme) {
        height = pickerTheme->GetGradientHeight();
    } else {
        height = 0.0_vp;
    }

    TextPickerModelNG::TextPickerRemoveResObj(frameNode, "textPicker.gradientHeight");
    TextPickerModelNG::SetGradientHeight(frameNode, height);
}

void SetTextPickerDisableTextStyleAnimation(ArkUINodeHandle node, int disableTextStyleAnimation)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextPickerModelNG::SetDisableTextStyleAnimation(frameNode, disableTextStyleAnimation);
}

void ResetTextPickerDisableTextStyleAnimation(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextPickerModelNG::SetDisableTextStyleAnimation(frameNode, false);
}

void SetTextPickerDefaultTextStyleBase(ArkUINodeHandle node, ArkUI_Uint32 color, ArkUI_CharPtr fontInfo,
    ArkUI_Int32 style, ArkUI_CharPtr minFontSize, ArkUI_CharPtr maxFontSize, ArkUI_Int32 overflow, bool isNeedGetResObj)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto theme = themeManager->GetTheme<TextTheme>();
    CHECK_NULL_VOID(theme);

    NG::PickerTextStyle textStyle;
    InitTextPickerTextStyle(fontInfo, color, style, textStyle);
    if (isNeedGetResObj) {
        textStyle.textColorSetByUser = true;
        GetColorResourceObject(frameNode, textStyle);
    }
    textStyle.minFontSize = StringUtils::StringToCalcDimension(minFontSize, false, DimensionUnit::FP);
    textStyle.maxFontSize = StringUtils::StringToCalcDimension(maxFontSize, false, DimensionUnit::FP);
    if (overflow >= 0 && overflow < static_cast<int32_t>(TEXT_OVERFLOWS.size())) {
        textStyle.textOverflow = TEXT_OVERFLOWS[overflow];
    } else {
        textStyle.textOverflow = TEXT_OVERFLOWS[0];
    }

    TextPickerModelNG::SetDefaultTextStyle(frameNode, theme, textStyle);
}

void SetTextPickerDefaultTextStyle(ArkUINodeHandle node, ArkUI_Uint32 color, ArkUI_CharPtr fontInfo, ArkUI_Int32 style,
    ArkUI_CharPtr minFontSize, ArkUI_CharPtr maxFontSize, ArkUI_Int32 overflow)
{
    SetTextPickerDefaultTextStyleBase(node, color, fontInfo, style, minFontSize, maxFontSize, overflow, false);
}

void SetTextPickerDefaultTextStylePtr(ArkUINodeHandle node, ArkUI_Uint32 color, ArkUI_CharPtr fontInfo,
    ArkUI_Int32 style, ArkUI_CharPtr minFontSize, ArkUI_CharPtr maxFontSize, ArkUI_Int32 overflow, bool isDefaultColor)
{
    SetTextPickerDefaultTextStyleBase(
        node, color, fontInfo, style, minFontSize, maxFontSize, overflow, !isDefaultColor);
}

void SetTextPickerDefaultTextStyleWithResObj(
    ArkUINodeHandle node, const struct ArkUIPickerTextStyleStruct* textStyleStruct)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto theme = themeManager->GetTheme<TextTheme>();
    CHECK_NULL_VOID(theme);

    NG::PickerTextStyle textStyle;
    textStyle.textColorSetByUser = textStyleStruct->textColorSetByUser;
    InitTextPickerTextStyle(
        textStyleStruct->fontInfo, textStyleStruct->textColor, textStyleStruct->fontStyle, textStyle);
    textStyle.minFontSize = StringUtils::StringToCalcDimension(textStyleStruct->minFontSize, false, DimensionUnit::FP);
    textStyle.maxFontSize = StringUtils::StringToCalcDimension(textStyleStruct->maxFontSize, false, DimensionUnit::FP);
    if (textStyleStruct->textOverflow >= 0 &&
        textStyleStruct->textOverflow < static_cast<int32_t>(TEXT_OVERFLOWS.size())) {
        textStyle.textOverflow = TEXT_OVERFLOWS[textStyleStruct->textOverflow];
    } else {
        textStyle.textOverflow = TEXT_OVERFLOWS[0];
    }
    SetTextPickerTextStyleResObj(textStyle, textStyleStruct);
    TextPickerModelNG::SetDefaultTextStyle(frameNode, theme, textStyle);
}

void ResetTextPickerDefaultTextStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto theme = themeManager->GetTheme<TextTheme>();
    CHECK_NULL_VOID(theme);
    NG::PickerTextStyle pickerTextStyle;
    TextPickerModelNG::SetDefaultTextStyle(frameNode, theme, pickerTextStyle);
}

ArkUI_Int32 GetTextPickerSelectedSize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, 0);
    if (TextPickerModelNG::IsSingle(frameNode)) {
        return 1;
    }
    return TextPickerModelNG::GetSelectedSize(frameNode);
}
void SetTextPickerOnChangeExt(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onChange =
        reinterpret_cast<std::function<void(const std::vector<std::string>&, const std::vector<double>&)>*>(callback);
    TextPickerModelNG::SetOnCascadeChange(frameNode, std::move(*onChange));
}
void ResetTextPickerOnChange(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextPickerModelNG::SetOnCascadeChange(frameNode, nullptr);
}
void SetTextPickerOnScrollStopExt(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onChange =
        reinterpret_cast<std::function<void(const std::vector<std::string>&, const std::vector<double>&)>*>(callback);
    TextPickerModelNG::SetOnScrollStop(frameNode, std::move(*onChange));
}
void ResetTextPickerOnScrollStop(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextPickerModelNG::SetOnScrollStop(frameNode, nullptr);
}

void SetTextPickerOnScrollStopImpl(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onScrollStopEvent = [node, extraParam](
                                 const std::vector<std::string>& value, const std::vector<double>& indexVector) {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_TEXT_PICKER_SCROLL_STOP;
        for (size_t i = 0; i < indexVector.size() && i < MAX_SIZE; i++) {
            event.componentAsyncEvent.data[i].i32 = static_cast<int32_t>(indexVector[i]);
        }
        SendArkUISyncEvent(&event);
    };
    TextPickerModelNG::SetOnScrollStop(frameNode, std::move(onScrollStopEvent));
}

void SetTextPickerSelectedBackgroundStyle(ArkUINodeHandle node, ArkUI_Bool* getValue, ArkUI_Uint32 color,
    ArkUI_Float32* value, ArkUI_Int32* unit, ArkUI_Int32 size)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);
    PickerBackgroundStyle pickerBgStyle;
    pickerBgStyle.color = theme->GetSelectedBackgroundColor();
    pickerBgStyle.borderRadius = theme->GetSelectedBorderRadius();
    if (getValue[GETCOLOR]) {
        pickerBgStyle.color = Color(color);
        pickerBgStyle.textColorSetByUser = true;
        RefPtr<ResourceObject> colorResObj;
        Color result = Color(color);
        ResourceParseUtils::CompleteResourceObjectFromColor(
            colorResObj, result, ResourceParseUtils::MakeNativeNodeInfo(frameNode));
        if (colorResObj) {
            pickerBgStyle.color = result;
            pickerBgStyle.colorResObj = colorResObj;
        }
    }
    if (getValue[GETTOPLEFT]) {
        pickerBgStyle.borderRadius->radiusTopLeft =
            Dimension(value[TOPLEFT], static_cast<DimensionUnit>(unit[TOPLEFT]));
    }
    if (getValue[GETTOPRIGHT]) {
        pickerBgStyle.borderRadius->radiusTopRight =
            Dimension(value[TOPRIGHT], static_cast<DimensionUnit>(unit[TOPRIGHT]));
    }
    if (getValue[GETBOTTOMLEFT]) {
        pickerBgStyle.borderRadius->radiusBottomLeft =
            Dimension(value[BOTTOMLEFT], static_cast<DimensionUnit>(unit[BOTTOMLEFT]));
    }
    if (getValue[GETBOTTOMRIGHT]) {
        pickerBgStyle.borderRadius->radiusBottomRight =
            Dimension(value[BOTTOMRIGHT], static_cast<DimensionUnit>(unit[BOTTOMRIGHT]));
    }
    TextPickerModelNG::SetSelectedBackgroundStyle(frameNode, pickerBgStyle);
}

#define TEXT_PICKER_ADD_RADIUS_RESOURCE(radiusProp, propName, dimensionMember)                  \
    auto propName##Update = [](const RefPtr<ResourceObject>& obj, BorderRadiusProperty& prop) { \
        CalcDimension dim;                                                                      \
        ResourceParseUtils::ParseResDimensionVp(obj, dim);                                      \
        prop.dimensionMember = dim;                                                             \
    };                                                                                          \
    const std::string resourceKey = std::string("borderRadius.") + #dimensionMember;            \
    (radiusProp)->AddResource(resourceKey, propName##ResObj, std::move(propName##Update))

void AddRadiusResource(
    const struct ArkUIPickerBackgroundStyleStruct* backgroundStyleStruct, PickerBackgroundStyle& pickerBgStyle)
{
    auto* topLeftResPtr = reinterpret_cast<ResourceObject*>(backgroundStyleStruct->topLeftRawPtr);
    auto topLeftResObj = AceType::Claim(topLeftResPtr);
    auto* topRightResPtr = reinterpret_cast<ResourceObject*>(backgroundStyleStruct->topRightRawPtr);
    auto topRightResObj = AceType::Claim(topRightResPtr);
    auto* bottomLeftResPtr = reinterpret_cast<ResourceObject*>(backgroundStyleStruct->bottomLeftRawPtr);
    auto bottomLeftResObj = AceType::Claim(bottomLeftResPtr);
    auto* bottomRightResPtr = reinterpret_cast<ResourceObject*>(backgroundStyleStruct->bottomRightRawPtr);
    auto bottomRightResObj = AceType::Claim(bottomRightResPtr);
    if (topLeftResObj) {
        TEXT_PICKER_ADD_RADIUS_RESOURCE(pickerBgStyle.borderRadius, topLeft, radiusTopLeft);
    }
    if (topRightResObj) {
        TEXT_PICKER_ADD_RADIUS_RESOURCE(pickerBgStyle.borderRadius, topRight, radiusTopRight);
    }
    if (bottomLeftResObj) {
        TEXT_PICKER_ADD_RADIUS_RESOURCE(pickerBgStyle.borderRadius, bottomLeft, radiusBottomLeft);
    }
    if (bottomRightResObj) {
        TEXT_PICKER_ADD_RADIUS_RESOURCE(pickerBgStyle.borderRadius, bottomRight, radiusBottomRight);
    }
}

void SetTextPickerSelectedBackgroundStyleWithResObj(
    ArkUINodeHandle node, ArkUI_Bool* isHasValue, const struct ArkUIPickerBackgroundStyleStruct* backgroundStyleStruct)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);
    PickerBackgroundStyle pickerBgStyle;
    pickerBgStyle.color = theme->GetSelectedBackgroundColor();
    pickerBgStyle.borderRadius = theme->GetSelectedBorderRadius();
    if (isHasValue[GETCOLOR]) {
        pickerBgStyle.color = Color(backgroundStyleStruct->colorValue);
        pickerBgStyle.textColorSetByUser = backgroundStyleStruct->isColorSetByUser;
        auto* colorPtr = reinterpret_cast<ResourceObject*>(backgroundStyleStruct->colorRawPtr);
        pickerBgStyle.colorResObj = AceType::Claim(colorPtr);
    }
    if (isHasValue[GETTOPLEFT]) {
        pickerBgStyle.borderRadius->radiusTopLeft = Dimension(
            backgroundStyleStruct->values[TOPLEFT], static_cast<DimensionUnit>(backgroundStyleStruct->units[TOPLEFT]));
    }
    if (isHasValue[GETTOPRIGHT]) {
        pickerBgStyle.borderRadius->radiusTopRight = Dimension(backgroundStyleStruct->values[TOPRIGHT],
            static_cast<DimensionUnit>(backgroundStyleStruct->units[TOPRIGHT]));
    }
    if (isHasValue[GETBOTTOMLEFT]) {
        pickerBgStyle.borderRadius->radiusBottomLeft = Dimension(backgroundStyleStruct->values[BOTTOMLEFT],
            static_cast<DimensionUnit>(backgroundStyleStruct->units[BOTTOMLEFT]));
    }
    if (isHasValue[GETBOTTOMRIGHT]) {
        pickerBgStyle.borderRadius->radiusBottomRight = Dimension(backgroundStyleStruct->values[BOTTOMRIGHT],
            static_cast<DimensionUnit>(backgroundStyleStruct->units[BOTTOMRIGHT]));
    }

    AddRadiusResource(backgroundStyleStruct, pickerBgStyle);
    TextPickerModelNG::SetSelectedBackgroundStyle(frameNode, pickerBgStyle);
}

void GetTextPickerSelectedBackgroundStyle(ArkUINodeHandle node, ArkUINumberValue* result, ArkUI_Int32 size)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pickerBgStyle = TextPickerModelNG::GetSelectedBackgroundStyle(frameNode);
    result[GETCOLOR].u32 = pickerBgStyle.color->GetValue();
    result[GETTOPLEFT].f32 = pickerBgStyle.borderRadius->radiusTopLeft->Value();
    result[GETTOPRIGHT].f32 = pickerBgStyle.borderRadius->radiusTopRight->Value();
    result[GETBOTTOMLEFT].f32 = pickerBgStyle.borderRadius->radiusBottomLeft->Value();
    result[GETBOTTOMRIGHT].f32 = pickerBgStyle.borderRadius->radiusBottomRight->Value();
}

void SetTextPickerOnChangeImpl(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onChangeEvent = [node, extraParam](
                             const std::vector<std::string>& value, const std::vector<double>& indexVector) {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_TEXT_PICKER_CHANGE;
        for (size_t i = 0; i < indexVector.size() && i < MAX_SIZE; i++) {
            event.componentAsyncEvent.data[i].i32 = static_cast<int32_t>(indexVector[i]);
        }
        SendArkUISyncEvent(&event);
    };
    TextPickerModelNG::SetOnCascadeChange(frameNode, std::move(onChangeEvent));
}

void ResetTextPickerSelectedBackgroundStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);
    PickerBackgroundStyle pickerBgStyle;
    pickerBgStyle.color = theme->GetSelectedBackgroundColor();
    pickerBgStyle.borderRadius = theme->GetSelectedBorderRadius();
    TextPickerModelNG::SetSelectedBackgroundStyle(frameNode, pickerBgStyle);
}

ArkUINodeHandle CreateFrameNode(ArkUI_Int32 nodeId)
{
    auto frameNode = TextPickerModelNG::CreateFrameNode(nodeId);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode));
}

void CreateJsSingle(void* obj)
{
    auto theme = GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);
    CHECK_NULL_VOID(obj);
    ParseTextArrayParam param = *(reinterpret_cast<ParseTextArrayParam*>(obj));
    TextPickerModel::GetInstance()->Create(theme, param.kind);
    TextPickerModel::GetInstance()->SetRange(param.result);
    TextPickerModel::GetInstance()->SetSelected(param.selected);
    TextPickerModel::GetInstance()->SetValue(param.value);
    TextPickerModel::GetInstance()->SetColumnWidths(param.columnWidths);

    if (SystemProperties::ConfigChangePerform()) {
        if (param.kind == NG::TEXT) {
            TextPickerModel::GetInstance()->ParseSingleRangeResourceObj(param.resultResObj, param.valueResObj);
        } else if (param.kind == NG::ICON || param.kind == (NG::ICON | NG::TEXT)) {
            TextPickerModel::GetInstance()->ParseSingleIconTextResourceObj(param.result);
        }

        TextPickerModel::GetInstance()->ParseColumnWidthsResourceObj(param.columnWidthResObjs);
    }
}

void CreateJsMulti(void* optionsAttr, void* obj)
{
    auto theme = GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);
    CHECK_NULL_VOID(optionsAttr);
    CHECK_NULL_VOID(obj);
    ParseTextArrayParam param = *(reinterpret_cast<ParseTextArrayParam*>(obj));
    TextCascadePickerOptionsAttr attr = *(reinterpret_cast<TextCascadePickerOptionsAttr*>(optionsAttr));
    TextPickerModel::GetInstance()->MultiInit(theme);
    TextPickerModel::GetInstance()->SetValues(param.values);
    TextPickerModel::GetInstance()->SetSelecteds(param.selecteds);
    TextPickerModel::GetInstance()->SetIsCascade(attr.isCascade);
    TextPickerModel::GetInstance()->SetHasSelectAttr(attr.isHasSelectAttr);
    TextPickerModel::GetInstance()->SetColumns(param.options);
    TextPickerModel::GetInstance()->SetColumnWidths(param.columnWidths);

    if (SystemProperties::ConfigChangePerform()) {
        if (!param.valueArrResObj.empty()) {
            TextPickerModel::GetInstance()->ParseCascadeResourceObj(param.options, param.valueArrResObj);
        }
        TextPickerModel::GetInstance()->ParseColumnWidthsResourceObj(param.columnWidthResObjs);
    }
}

void SetJsSelected(ArkUINodeHandle node, ArkUI_Uint32 values)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextPickerModelNG::SetSelected(frameNode, values);
}

void SetJsSelecteds(ArkUINodeHandle node, const ArkUI_Uint32* values, ArkUI_Int32 size)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<uint32_t> selectedValues;
    if (values != nullptr && size > 0) {
        for (ArkUI_Int32 i = 0; i < size; i++) {
            auto index = values[i];
            selectedValues.emplace_back(index);
        }
    }
    TextPickerModelNG::SetSelecteds(frameNode, selectedValues);
}

void SetJsHasSelectAttr(ArkUINodeHandle node, ArkUI_Bool values)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextPickerModelNG::SetHasSelectAttr(frameNode, values);
}

void SetJsSingleRange(ArkUI_Bool isSingleRange)
{
    TextPickerModelNG::GetInstance()->SetSingleRange(isSingleRange);
}

void SetJsDefaultAttributes()
{
    auto theme = GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);
    TextPickerModelNG::GetInstance()->SetDefaultAttributes(theme);
    ViewAbstractModel::GetInstance()->SetFocusNode(true);
    ViewAbstractModel::GetInstance()->SetFocusable(true);
}

void SetJsMaxCount(ArkUI_Uint32 maxCount)
{
    TextPickerModelNG::GetInstance()->SetMaxCount(maxCount);
}

void SetJsOnValueChangeEvent(void* onChange)
{
    CHECK_NULL_VOID(onChange);
    auto* func = reinterpret_cast<std::function<void(const std::vector<std::string>&)>*>(onChange);
    TextPickerModelNG::GetInstance()->SetOnValueChangeEvent(std::move(*func));
}

void SetJsOnSelectedChangeEvent(void* onChange)
{
    CHECK_NULL_VOID(onChange);
    auto* func = reinterpret_cast<std::function<void(const std::vector<double>&)>*>(onChange);
    TextPickerModelNG::GetInstance()->SetOnSelectedChangeEvent(std::move(*func));
}

void SetJsSelectedBackgroundStyle(ArkUINodeHandle node, void* value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    PickerBackgroundStyle style;
    if (value) {
        style = *(reinterpret_cast<PickerBackgroundStyle*>(value));
    }
    TextPickerModelNG::SetSelectedBackgroundStyle(frameNode, style);
}

ArkUI_Bool IsJsCascade(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, false);
    return TextPickerModelNG::IsCascade(frameNode);
}

ArkUI_Bool GetCreateSingleRange()
{
    return TextPickerModel::GetInstance()->GetSingleRange();
}

void GetJsSingleRange(ArkUINodeHandle node, void* rangeValue)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(rangeValue);
    TextPickerModelNG::GetSingleRange(frameNode, *reinterpret_cast<std::vector<RangeContent>*>(rangeValue));
}

ArkUI_Uint32 GetJsMaxCount()
{
    return TextPickerModel::GetInstance()->GetMaxCount();
}

void GetJsMultiOptions(ArkUINodeHandle node, void* options)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
    TextPickerModelNG::GetMultiOptions(
        frameNode, *reinterpret_cast<std::vector<NG::TextCascadePickerOptions>*>(options));
}

ArkUI_Bool IsSingle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, false);
    return TextPickerModelNG::IsSingle(frameNode);
}

void SetJsDisappearTextStyle(ArkUINodeHandle node, void* textStyle)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    PickerTextStyle textStyles;
    if (textStyle) {
        textStyles = *(reinterpret_cast<PickerTextStyle*>(textStyle));
    }
    auto pickerTheme = frameNode->GetTheme<PickerTheme>(true);
    CHECK_NULL_VOID(pickerTheme);
    TextPickerModelNG::SetDisappearTextStyle(frameNode, pickerTheme, textStyles);
}

void SetJsDefaultTextStyle(ArkUINodeHandle node, void* textStyle)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    PickerTextStyle textStyles;
    if (textStyle) {
        textStyles = *(reinterpret_cast<PickerTextStyle*>(textStyle));
    }
    auto textTheme = frameNode->GetTheme<TextTheme>(true);
    CHECK_NULL_VOID(textTheme);
    TextPickerModelNG::SetDefaultTextStyle(frameNode, textTheme, textStyles);
}

void SetJsSelectedTextStyle(ArkUINodeHandle node, void* textStyle)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    PickerTextStyle textStyles;
    if (textStyle) {
        textStyles = *(reinterpret_cast<PickerTextStyle*>(textStyle));
    }
    auto pickerTheme = frameNode->GetTheme<PickerTheme>(true);
    CHECK_NULL_VOID(pickerTheme);
    TextPickerModelNG::SetSelectedTextStyle(frameNode, pickerTheme, textStyles);
    if (textStyles.textColor.has_value() && pickerTheme->IsCircleDial()) {
        TextPickerModel::GetInstance()->UpdateUserSetSelectColor();
    }
}

void SetJsNormalTextStyle(ArkUINodeHandle node, void* textStyle)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    PickerTextStyle textStyles;
    if (textStyle) {
        textStyles = *(reinterpret_cast<PickerTextStyle*>(textStyle));
    }
    auto theme = frameNode->GetTheme<PickerTheme>(true);
    CHECK_NULL_VOID(theme);
    TextPickerModelNG::SetNormalTextStyle(frameNode, theme, textStyles);
}

void HasUserDefinedDisappearFontFamily(ArkUI_Bool isHas)
{
    TextPickerModel::GetInstance()->HasUserDefinedDisappearFontFamily(isHas);
}

void HasUserDefinedNormalFontFamily(ArkUI_Bool isHas)
{
    TextPickerModel::GetInstance()->HasUserDefinedNormalFontFamily(isHas);
}

void HasUserDefinedSelectedFontFamily(ArkUI_Bool isHas)
{
    TextPickerModel::GetInstance()->HasUserDefinedSelectedFontFamily(isHas);
}

void HasUserDefinedOpacity(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TextPickerModelNG::HasUserDefinedOpacity(frameNode);
}

void SetOnEnterSelectedArea(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onChange =
        reinterpret_cast<std::function<void(const std::vector<std::string>&, const std::vector<double>&)>*>(callback);
    TextPickerModelNG::SetOnEnterSelectedArea(frameNode, std::move(*onChange));
}

void SetJsDivider(ArkUINodeHandle node, void* divider)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ItemDivider dividers;
    if (divider) {
        dividers = *(reinterpret_cast<ItemDivider*>(divider));
    }
    TextPickerModelNG::SetDivider(frameNode, dividers);
}

void* CreateObject()
{
    auto object = TextPickerDialogModel::GetInstance()->CreateObject();
    return AceType::RawPtr(object);
}

void Show(void* pickerDialog, void* settingData, void* cancelEvent, void* acceptEvent, void* changeEvent,
    void* scrollStopEvent, void* enterSelectedAreaEvent, void* textPickerDialog, void* textPickerDialogEvent,
    void* buttonInfos)
{
    RefPtr<AceType> pickerText = nullptr;
    TextPickerDialogModel::GetInstance()->SetTextPickerDialogShow(pickerText,
        *reinterpret_cast<NG::TextPickerSettingData*>(settingData),
        std::move(*reinterpret_cast<std::function<void()>*>(cancelEvent)),
        std::move(*reinterpret_cast<std::function<void(const std::string&)>*>(acceptEvent)),
        std::move(*reinterpret_cast<std::function<void(const std::string&)>*>(changeEvent)),
        std::move(*reinterpret_cast<std::function<void(const std::string&)>*>(scrollStopEvent)),
        std::move(*reinterpret_cast<std::function<void(const std::string&)>*>(enterSelectedAreaEvent)),
        *reinterpret_cast<TextPickerDialog*>(textPickerDialog),
        *reinterpret_cast<TextPickerDialogEvent*>(textPickerDialogEvent),
        *reinterpret_cast<std::vector<ButtonInfo>*>(buttonInfos));
}
#ifndef CROSS_PLATFORM
void SetTextPickerOnChangeExtImpl(ArkUINodeHandle node, void* callback)
{
    auto onChange =
        reinterpret_cast<std::function<void(const std::vector<std::string>&, const std::vector<double>&)>*>(callback);
    GetTextPickerModelImpl()->SetOnCascadeChange(std::move(*onChange));
}

void SetTextPickerSelectedIndexImpl(ArkUINodeHandle node, ArkUI_Uint32* values, ArkUI_Int32 size)
{
    GetTextPickerModelImpl()->SetSelected(values[0]);
}

void SetTextPickerIconRangeStrImpl(
    ArkUINodeHandle node, ArkUITextPickerRangeContentArray arry, ArkUI_Bool isSingleRange, ArkUI_Int32 rangeType)
{
    std::vector<NG::RangeContent> result;
    for (int i = 0; i < arry->rangeContentArraySize; i++) {
        NG::RangeContent content;
        if (arry->rangeContent[i].text != nullptr) {
            content.text_ = arry->rangeContent[i].text;
        }
        if (arry->rangeContent[i].icon != nullptr) {
            content.icon_ = arry->rangeContent[i].icon;
        }
        result.emplace_back(content);
    }
    GetTextPickerModelImpl()->SetRange(result);
}

void SetTextPickerDefaultPickerItemHeightImpl(ArkUINodeHandle node, float dVal, ArkUI_Int32 dUnit)
{
    GetTextPickerModelImpl()->SetDefaultPickerItemHeight(Dimension(dVal, static_cast<DimensionUnit>(dUnit)));
}

void SetTextPickerBackgroundColorImpl(ArkUINodeHandle node, ArkUI_Uint32 color)
{
    GetTextPickerModelImpl()->SetBackgroundColor(Color(color));
}

void SetTextPickerOnScrollStopExtImpl(ArkUINodeHandle node, void* callback)
{
    auto onChange =
        reinterpret_cast<std::function<void(const std::vector<std::string>&, const std::vector<double>&)>*>(callback);
    GetTextPickerModelImpl()->SetOnScrollStop(std::move(*onChange));
}

void* CreateObjectImpl()
{
    auto object = GetTextPickerDialogModelImpl()->CreateObject();
    return AceType::RawPtr(object);
}

void ShowImpl(void* pickerDialog, void* settingData, void* cancelEvent, void* acceptEvent, void* changeEvent,
    void* scrollStopEvent, void* enterSelectedAreaEvent, void* textPickerDialog, void* textPickerDialogEvent,
    void* buttonInfos)
{
    RefPtr<AceType> pickerText = nullptr;
    GetTextPickerDialogModelImpl()->SetTextPickerDialogShow(pickerText,
        *reinterpret_cast<NG::TextPickerSettingData*>(settingData),
        std::move(*reinterpret_cast<std::function<void()>*>(cancelEvent)),
        std::move(*reinterpret_cast<std::function<void(const std::string&)>*>(acceptEvent)),
        std::move(*reinterpret_cast<std::function<void(const std::string&)>*>(changeEvent)),
        std::move(*reinterpret_cast<std::function<void(const std::string&)>*>(scrollStopEvent)),
        std::move(*reinterpret_cast<std::function<void(const std::string&)>*>(enterSelectedAreaEvent)),
        *reinterpret_cast<TextPickerDialog*>(textPickerDialog),
        *reinterpret_cast<TextPickerDialogEvent*>(textPickerDialogEvent),
        *reinterpret_cast<std::vector<ButtonInfo>*>(buttonInfos));
}

void CreateJsSingleImpl(void* obj)
{
    auto theme = GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);
    CHECK_NULL_VOID(obj);
    ParseTextArrayParam param = *(reinterpret_cast<ParseTextArrayParam*>(obj));
    GetTextPickerModelImpl()->Create(theme, param.kind);
    GetTextPickerModelImpl()->SetRange(param.result);
    GetTextPickerModelImpl()->SetSelected(param.selected);
}
#endif
} // namespace

namespace NodeModifier {
const ArkUITextPickerModifier* GetTextPickerDynamicModifier()
{
    static bool isCurrentUseNewPipeline = Container::IsCurrentUseNewPipeline();
    if (!isCurrentUseNewPipeline) {
#ifndef CROSS_PLATFORM
        CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
        static const ArkUITextPickerModifier modifierImpl = {
            .setTextPickerBackgroundColor = SetTextPickerBackgroundColorImpl,
            .setTextPickerCanLoop = nullptr,
            .getTextPickerSelectedIndex = nullptr,
            .setTextPickerSelectedIndex = SetTextPickerSelectedIndexImpl,
            .getTextPickerTextStyle = nullptr,
            .setTextPickerTextStyle = nullptr,
            .setTextPickerTextStylePtr = nullptr,
            .setTextPickerTextStyleWithResObj = nullptr,
            .getTextPickerSelectedTextStyle = nullptr,
            .setTextPickerSelectedTextStyle = nullptr,
            .setTextPickerSelectedTextStylePtr = nullptr,
            .setTextPickerSelectedTextStyleWithResObj = nullptr,
            .getTextPickerDisappearTextStyle = nullptr,
            .setTextPickerDisappearTextStyle = nullptr,
            .setTextPickerDisappearTextStylePtr = nullptr,
            .setTextPickerDisappearTextStyleWithResObj = nullptr,
            .setTextPickerDefaultPickerItemHeight = SetTextPickerDefaultPickerItemHeightImpl,
            .resetTextPickerCanLoop = nullptr,
            .resetTextPickerSelectedIndex = nullptr,
            .resetTextPickerTextStyle = nullptr,
            .resetTextPickerSelectedTextStyle = nullptr,
            .resetTextPickerDisappearTextStyle = nullptr,
            .resetTextPickerDefaultPickerItemHeight = nullptr,
            .resetTextPickerBackgroundColor = nullptr,
            .getTextPickerRangeStr = nullptr,
            .getTextPickerSingleRange = nullptr,
            .setTextPickerRangeStr = nullptr,
            .getTextPickerValue = nullptr,
            .setTextPickerValue = nullptr,
            .setTextPickerColumnWidths = nullptr,
            .resetTextPickerColumnWidths = nullptr,
            .getTextPickerColumnWidths = nullptr,
            .getTextPickerColumnWidthsSize = nullptr,
            .setTextPickerDivider = nullptr,
            .setTextPickerDividerWithResObj = nullptr,
            .resetTextPickerDivider = nullptr,
            .setTextPickerGradientHeight = nullptr,
            .setTextPickerGradientHeightWithResObj = nullptr,
            .resetTextPickerGradientHeight = nullptr,
            .getTextPickerSelectedSize = nullptr,
            .getTextPickerCanLoop = nullptr,
            .getTextPickerDefaultPickerItemHeight = nullptr,
            .resetTextPickerDividerNull = nullptr,
            .setTextPickerDisableTextStyleAnimation = nullptr,
            .resetTextPickerDisableTextStyleAnimation = nullptr,
            .setTextPickerDefaultTextStyle = nullptr,
            .setTextPickerDefaultTextStylePtr = nullptr,
            .setTextPickerDefaultTextStyleWithResObj = nullptr,
            .resetTextPickerDefaultTextStyle = nullptr,
            .getTextPickerEnableHapticFeedback = nullptr,
            .setTextPickerEnableHapticFeedback = nullptr,
            .resetTextPickerEnableHapticFeedback = nullptr,
            .setTextPickerDigitalCrownSensitivity = nullptr,
            .resetTextPickerDigitalCrownSensitivity = nullptr,
            .setTextPickerOnChange = SetTextPickerOnChangeExtImpl,
            .resetTextPickerOnChange = nullptr,
            .setTextPickerOnScrollStop = SetTextPickerOnScrollStopExtImpl,
            .resetTextPickerOnScrollStop = nullptr,
            .setTextPickerIconRangeStr = SetTextPickerIconRangeStrImpl,
            .setTextCascadePickRangeContent = nullptr,
            .setTextPickerSelectedBackgroundStyle = nullptr,
            .setTextPickerSelectedBackgroundStyleWithResObj = nullptr,
            .getTextPickerSelectedBackgroundStyle = nullptr,
            .resetTextPickerSelectedBackgroundStyle = nullptr,
            .setTextPickerOnChangeHandler = nullptr,
            .setTextPickerOnScrollStopHandler = nullptr,
            .createFrameNode = nullptr,
            .createJsSingle = CreateJsSingleImpl,
            .createJsMulti = nullptr,
            .setJsDefaultAttributes = nullptr,
            .setJsOnValueChangeEvent = nullptr,
            .setJsOnSelectedChangeEvent = nullptr,
            .getCreateSingleRange = nullptr,
            .setJsMaxCount = nullptr,
            .setJsSingleRange = nullptr,
            .setJsSelectedTextStyle = nullptr,
            .setJsDisappearTextStyle = nullptr,
            .setJsNormalTextStyle = nullptr,
            .setJsDefaultTextStyle = nullptr,
            .hasUserDefinedDisappearFontFamily = nullptr,
            .hasUserDefinedNormalFontFamily = nullptr,
            .hasUserDefinedSelectedFontFamily = nullptr,
            .hasUserDefinedOpacity = nullptr,
            .setJsDivider = nullptr,
            .getJsSingleRange = nullptr,
            .setJsSelected = nullptr,
            .setOnEnterSelectedArea = nullptr,
            .isSingle = nullptr,
            .isJsCascade = nullptr,
            .getJsMaxCount = nullptr,
            .getJsMultiOptions = nullptr,
            .setJsSelecteds = nullptr,
            .setJsHasSelectAttr = nullptr,
            .setJsSelectedBackgroundStyle = nullptr,
            .createObject = CreateObjectImpl,
            .show = ShowImpl,
        };
        CHECK_INITIALIZED_FIELDS_END(modifierImpl, 0, 0, 0); // don't move this line
        return &modifierImpl;
#endif
    }
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUITextPickerModifier modifier = {
        .setTextPickerBackgroundColor = SetTextPickerBackgroundColor,
        .setTextPickerCanLoop = SetTextPickerCanLoop,
        .getTextPickerSelectedIndex = GetTextPickerSelectedIndex,
        .setTextPickerSelectedIndex = SetTextPickerSelectedIndex,
        .getTextPickerTextStyle = GetTextPickerTextStyle,
        .setTextPickerTextStyle = SetTextPickerTextStyle,
        .setTextPickerTextStylePtr = SetTextPickerTextStylePtr,
        .setTextPickerTextStyleWithResObj = SetTextPickerTextStyleWithResObj,
        .getTextPickerSelectedTextStyle = GetTextPickerSelectedTextStyle,
        .setTextPickerSelectedTextStyle = SetTextPickerSelectedTextStyle,
        .setTextPickerSelectedTextStylePtr = SetTextPickerSelectedTextStylePtr,
        .setTextPickerSelectedTextStyleWithResObj = SetTextPickerSelectedTextStyleWithResObj,
        .getTextPickerDisappearTextStyle = GetTextPickerDisappearTextStyle,
        .setTextPickerDisappearTextStyle = SetTextPickerDisappearTextStyle,
        .setTextPickerDisappearTextStylePtr = SetTextPickerDisappearTextStylePtr,
        .setTextPickerDisappearTextStyleWithResObj = SetTextPickerDisappearTextStyleWithResObj,
        .setTextPickerDefaultPickerItemHeight = SetTextPickerDefaultPickerItemHeight,
        .resetTextPickerCanLoop = ResetTextPickerCanLoop,
        .resetTextPickerSelectedIndex = ResetTextPickerSelectedIndex,
        .resetTextPickerTextStyle = ResetTextPickerTextStyle,
        .resetTextPickerSelectedTextStyle = ResetTextPickerSelectedTextStyle,
        .resetTextPickerDisappearTextStyle = ResetTextPickerDisappearTextStyle,
        .resetTextPickerDefaultPickerItemHeight = ResetTextPickerDefaultPickerItemHeight,
        .resetTextPickerBackgroundColor = ResetTextPickerBackgroundColor,
        .getTextPickerRangeStr = GetTextPickerRangeStr,
        .getTextPickerSingleRange = GetTextPickerSingleRange,
        .setTextPickerRangeStr = SetTextPickerRangeStr,
        .getTextPickerValue = GetTextPickerValue,
        .setTextPickerValue = SetTextPickerValue,
        .setTextPickerColumnWidths = SetTextPickerColumnWidths,
        .resetTextPickerColumnWidths = ResetTextPickerColumnWidths,
        .getTextPickerColumnWidths = GetTextPickerColumnWidths,
        .getTextPickerColumnWidthsSize = GetTextPickerColumnWidthsSize,
        .setTextPickerDivider = SetTextPickerDivider,
        .setTextPickerDividerWithResObj = SetTextPickerDividerWithResObj,
        .resetTextPickerDivider = ResetTextPickerDivider,
        .setTextPickerGradientHeight = SetTextPickerGradientHeight,
        .setTextPickerGradientHeightWithResObj = SetTextPickerGradientHeightWithResObj,
        .resetTextPickerGradientHeight = ResetTextPickerGradientHeight,
        .getTextPickerSelectedSize = GetTextPickerSelectedSize,
        .getTextPickerCanLoop = GetTextPickerCanLoop,
        .getTextPickerDefaultPickerItemHeight = GetTextPickerDefaultPickerItemHeight,
        .resetTextPickerDividerNull = ResetTextPickerDividerNull,
        .setTextPickerDisableTextStyleAnimation = SetTextPickerDisableTextStyleAnimation,
        .resetTextPickerDisableTextStyleAnimation = ResetTextPickerDisableTextStyleAnimation,
        .setTextPickerDefaultTextStyle = SetTextPickerDefaultTextStyle,
        .setTextPickerDefaultTextStylePtr = SetTextPickerDefaultTextStylePtr,
        .setTextPickerDefaultTextStyleWithResObj = SetTextPickerDefaultTextStyleWithResObj,
        .resetTextPickerDefaultTextStyle = ResetTextPickerDefaultTextStyle,
        .getTextPickerEnableHapticFeedback = GetTextPickerEnableHapticFeedback,
        .setTextPickerEnableHapticFeedback = SetTextPickerEnableHapticFeedback,
        .resetTextPickerEnableHapticFeedback = ResetTextPickerEnableHapticFeedback,
        .setTextPickerDigitalCrownSensitivity = SetTextPickerDigitalCrownSensitivity,
        .resetTextPickerDigitalCrownSensitivity = ResetTextPickerDigitalCrownSensitivity,
        .setTextPickerOnChange = SetTextPickerOnChangeExt,
        .resetTextPickerOnChange = ResetTextPickerOnChange,
        .setTextPickerOnScrollStop = SetTextPickerOnScrollStopExt,
        .resetTextPickerOnScrollStop = ResetTextPickerOnScrollStop,
        .setTextPickerIconRangeStr = SetTextPickerIconRangeStr,
        .setTextCascadePickRangeContent = SetTextCascadePickRangeContent,
        .setTextPickerSelectedBackgroundStyle = SetTextPickerSelectedBackgroundStyle,
        .setTextPickerSelectedBackgroundStyleWithResObj = SetTextPickerSelectedBackgroundStyleWithResObj,
        .getTextPickerSelectedBackgroundStyle = GetTextPickerSelectedBackgroundStyle,
        .resetTextPickerSelectedBackgroundStyle = ResetTextPickerSelectedBackgroundStyle,
        .setTextPickerOnChangeHandler = SetTextPickerOnChangeImpl,
        .setTextPickerOnScrollStopHandler = SetTextPickerOnScrollStopImpl,
        .createFrameNode = CreateFrameNode,
        .createJsSingle = CreateJsSingle,
        .createJsMulti = CreateJsMulti,
        .setJsDefaultAttributes = SetJsDefaultAttributes,
        .setJsOnValueChangeEvent = SetJsOnValueChangeEvent,
        .setJsOnSelectedChangeEvent = SetJsOnSelectedChangeEvent,
        .getCreateSingleRange = GetCreateSingleRange,
        .setJsMaxCount = SetJsMaxCount,
        .setJsSingleRange = SetJsSingleRange,
        .setJsSelectedTextStyle = SetJsSelectedTextStyle,
        .setJsDisappearTextStyle = SetJsDisappearTextStyle,
        .setJsNormalTextStyle = SetJsNormalTextStyle,
        .setJsDefaultTextStyle = SetJsDefaultTextStyle,
        .hasUserDefinedDisappearFontFamily = HasUserDefinedDisappearFontFamily,
        .hasUserDefinedNormalFontFamily = HasUserDefinedNormalFontFamily,
        .hasUserDefinedSelectedFontFamily = HasUserDefinedSelectedFontFamily,
        .hasUserDefinedOpacity = HasUserDefinedOpacity,
        .setJsDivider = SetJsDivider,
        .getJsSingleRange = GetJsSingleRange,
        .setJsSelected = SetJsSelected,
        .setOnEnterSelectedArea = SetOnEnterSelectedArea,
        .isSingle = IsSingle,
        .isJsCascade = IsJsCascade,
        .getJsMaxCount = GetJsMaxCount,
        .getJsMultiOptions = GetJsMultiOptions,
        .setJsSelecteds = SetJsSelecteds,
        .setJsHasSelectAttr = SetJsHasSelectAttr,
        .setJsSelectedBackgroundStyle = SetJsSelectedBackgroundStyle,
        .createObject = CreateObject,
        .show = Show,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}

const CJUITextPickerModifier* GetCJUITextPickerModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUITextPickerModifier modifier = {
        .setTextPickerBackgroundColor = SetTextPickerBackgroundColor,
        .setTextPickerCanLoop = SetTextPickerCanLoop,
        .getTextPickerSelectedIndex = GetTextPickerSelectedIndex,
        .setTextPickerSelectedIndex = SetTextPickerSelectedIndex,
        .getTextPickerTextStyle = GetTextPickerTextStyle,
        .setTextPickerTextStyle = SetTextPickerTextStyle,
        .getTextPickerSelectedTextStyle = GetTextPickerSelectedTextStyle,
        .setTextPickerSelectedTextStyle = SetTextPickerSelectedTextStyle,
        .getTextPickerDisappearTextStyle = GetTextPickerDisappearTextStyle,
        .setTextPickerDisappearTextStyle = SetTextPickerDisappearTextStyle,
        .setTextPickerDefaultPickerItemHeight = SetTextPickerDefaultPickerItemHeight,
        .resetTextPickerCanLoop = ResetTextPickerCanLoop,
        .resetTextPickerSelectedIndex = ResetTextPickerSelectedIndex,
        .resetTextPickerTextStyle = ResetTextPickerTextStyle,
        .resetTextPickerSelectedTextStyle = ResetTextPickerSelectedTextStyle,
        .resetTextPickerDisappearTextStyle = ResetTextPickerDisappearTextStyle,
        .resetTextPickerDefaultPickerItemHeight = ResetTextPickerDefaultPickerItemHeight,
        .resetTextPickerBackgroundColor = ResetTextPickerBackgroundColor,
        .getTextPickerRangeStr = GetTextPickerRangeStr,
        .getTextPickerSingleRange = GetTextPickerSingleRange,
        .setTextPickerRangeStr = SetTextPickerRangeStr,
        .getTextPickerValue = GetTextPickerValue,
        .setTextPickerValue = SetTextPickerValue,
        .setTextPickerDivider = SetTextPickerDivider,
        .resetTextPickerDivider = ResetTextPickerDivider,
        .setTextPickerGradientHeight = SetTextPickerGradientHeight,
        .resetTextPickerGradientHeight = ResetTextPickerGradientHeight,
        .getTextPickerSelectedSize = GetTextPickerSelectedSize,
        .getTextPickerCanLoop = GetTextPickerCanLoop,
        .getTextPickerDefaultPickerItemHeight = GetTextPickerDefaultPickerItemHeight,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
