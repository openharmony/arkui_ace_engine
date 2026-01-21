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
#include "core/components_ng/pattern/time_picker/timepicker_model.h"

#include "bridge/common/utils/utils.h"
#include "core/common/dynamic_module_helper.h"
#include "core/common/resource/resource_parse_utils.h"
#include "core/components_ng/pattern/overlay/sheet_style.h"
#include "core/components_ng/pattern/tabs/tabs_model.h"
#include "core/components_ng/pattern/time_picker/timepicker_model_ng.h"
#include "core/components_ng/pattern/time_picker/timepicker_row_pattern.h"
#include "core/interfaces/native/node/node_api.h"
#include "core/interfaces/native/node/node_textpicker_modifier.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace {
#ifndef CROSS_PLATFORM
TimePickerModel* GetTimePickerModelImpl()
{
    // Load the timePicker loader from frameworks/compatible/components/picker directory
    static auto loader = DynamicModuleHelper::GetInstance().GetLoaderByName("timePicker");
    static TimePickerModel* instance = loader ? reinterpret_cast<TimePickerModel*>(loader->CreateModel()) : nullptr;
    return instance;
}
TimePickerDialogModel* GetTimePickerDialogModelImpl()
{
    // Load the timePicker loader from frameworks/compatible/components/picker directory
    static auto loader = DynamicModuleHelper::GetInstance().GetLoaderByName("timePickerDialog");
    static TimePickerDialogModel* instance =
        loader ? reinterpret_cast<TimePickerDialogModel*>(loader->CreateModel()) : nullptr;
    return instance;
}
#endif
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
namespace {
constexpr uint32_t DEFAULT_BG_COLOR = 0xFF007DFF;
const int32_t ERROR_INT_CODE = -1;
constexpr int32_t POS_0 = 0;
constexpr int32_t POS_1 = 1;
constexpr int32_t POS_2 = 2;
constexpr int NUM_3 = 3;
const char DEFAULT_DELIMITER = '|';
const std::vector<OHOS::Ace::FontStyle> FONT_STYLES = { OHOS::Ace::FontStyle::NORMAL, OHOS::Ace::FontStyle::ITALIC };
thread_local std::string g_strValue;

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

void InitTimePickerTextStyle(const char* fontInfo, uint32_t color, int32_t style, NG::PickerTextStyle& textStyle)
{
    std::vector<std::string> res;
    std::string fontValues = std::string(fontInfo);
    StringUtils::StringSplitter(fontValues, DEFAULT_DELIMITER, res);
    if (res.size() != NUM_3) {
        return;
    }
    textStyle.fontSize = StringUtils::StringToCalcDimension(res[POS_0], false, DimensionUnit::FP);
    if (style >= 0 && style < static_cast<int32_t>(FONT_STYLES.size())) {
        textStyle.fontStyle = FONT_STYLES[style];
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
        ResourceParseUtils::CompleteResourceObjectFromColor(colorResObj, result, frameNode->GetTag());
        if (colorResObj) {
            textStyle.textColor = result;
            textStyle.textColorResObj = colorResObj;
        }
    }
}

void SetTimePickerTextStyleResObj(
    NG::PickerTextStyle& textStyle, void* fontSizeRawPtr, void* fontFamilyRawPtr, void* textColorRawPtr)
{
    auto* fontSizePtr = reinterpret_cast<ResourceObject*>(fontSizeRawPtr);
    if (fontSizePtr) {
        textStyle.fontSizeResObj = AceType::Claim(fontSizePtr);
    }

    auto* fontFamilyPtr = reinterpret_cast<ResourceObject*>(fontFamilyRawPtr);
    if (fontFamilyPtr) {
        textStyle.fontFamilyResObj = AceType::Claim(fontFamilyPtr);
    }

    auto* textColorPtr = reinterpret_cast<ResourceObject*>(textColorRawPtr);
    if (textColorPtr) {
        textStyle.textColorResObj = AceType::Claim(textColorPtr);
    }
}

void SetTimepickerSelected(ArkUINodeHandle node, ArkUI_Uint32 hour, ArkUI_Uint32 minute)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TimePickerModelNG::SetSelectedTime(frameNode, PickerTime(hour, minute, 0));
}

void ResetTimepickerSelected(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    time_t now = time(nullptr);
    auto currentTm = localtime(&now);
    CHECK_NULL_VOID(currentTm);
    PickerTime pickerTime(currentTm->tm_hour, currentTm->tm_min, 0);

    TimePickerModelNG::SetSelectedTime(frameNode, pickerTime);
}

void SetTimepickerStart(ArkUINodeHandle node, ArkUI_Uint32 hour, ArkUI_Uint32 minute)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TimePickerModelNG::SetStartTime(frameNode, PickerTime(hour, minute, 0));
}

void ResetTimepickerStart(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    PickerTime pickerTime(0, 0, 0);

    TimePickerModelNG::SetStartTime(frameNode, pickerTime);
}

void SetTimepickerEnd(ArkUINodeHandle node, ArkUI_Uint32 hour, ArkUI_Uint32 minute)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TimePickerModelNG::SetEndTime(frameNode, PickerTime(hour, minute, 0));
}

void ResetTimepickerEnd(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    PickerTime defaultEndTime = PickerTime(23, 59, 59);

    TimePickerModelNG::SetEndTime(frameNode, defaultEndTime);
}

void SetTimepickerBackgroundColor(ArkUINodeHandle node, uint32_t color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TimePickerModelNG::SetBackgroundColor(frameNode, Color(color));
}

void ResetTimepickerBackgroundColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TimePickerModelNG::SetBackgroundColor(frameNode, Color(DEFAULT_BG_COLOR));
}

void SetTimepickerTextStyleBase(
    ArkUINodeHandle node, uint32_t color, const char* fontInfo, int32_t style, bool isNeedGetResObj)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefPtr<PickerTheme> theme;
    if (!GetPickerThemeByFrameNode(frameNode, theme)) {
        return;
    }
    NG::PickerTextStyle textStyle;
    InitTimePickerTextStyle(fontInfo, color, style, textStyle);
    if (isNeedGetResObj) {
        textStyle.textColorSetByUser = true;
        GetColorResourceObject(frameNode, textStyle);
    }
    TimePickerModelNG::SetNormalTextStyle(frameNode, theme, textStyle);
}

void SetTimepickerTextStyle(ArkUINodeHandle node, uint32_t color, const char* fontInfo, int32_t style)
{
    SetTimepickerTextStyleBase(node, color, fontInfo, style, false);
}

void SetTimepickerTextStylePtr(
    ArkUINodeHandle node, uint32_t color, const char* fontInfo, int32_t style, bool isDefaultColor)
{
    SetTimepickerTextStyleBase(node, color, fontInfo, style, !isDefaultColor);
}

void SetTimepickerTextStyleWithResObj(ArkUINodeHandle node, const struct ArkUIPickerTextStyleStruct* textStyleStruct)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefPtr<PickerTheme> theme;
    if (!GetPickerThemeByFrameNode(frameNode, theme)) {
        return;
    }
    NG::PickerTextStyle textStyle;
    textStyle.textColorSetByUser = textStyleStruct->textColorSetByUser;
    InitTimePickerTextStyle(
        textStyleStruct->fontInfo, textStyleStruct->textColor, textStyleStruct->fontStyle, textStyle);
    SetTimePickerTextStyleResObj(textStyle, textStyleStruct->fontSizeRawPtr, textStyleStruct->fontFamilyRawPtr,
        textStyleStruct->textColorRawPtr);
    TimePickerModelNG::SetNormalTextStyle(frameNode, theme, textStyle);
}

void ResetTimepickerTextStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    NG::PickerTextStyle pickerTextStyle;
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto pickerTheme = themeManager->GetTheme<PickerTheme>();
    TimePickerModelNG::SetNormalTextStyle(frameNode, pickerTheme, pickerTextStyle);
}

void SetTimepickerSelectedTextStyleBase(
    ArkUINodeHandle node, uint32_t color, const char* fontInfo, int32_t style, bool isNeedGetResObj)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefPtr<PickerTheme> theme;
    if (!GetPickerThemeByFrameNode(frameNode, theme)) {
        return;
    }
    NG::PickerTextStyle textStyle;
    InitTimePickerTextStyle(fontInfo, color, style, textStyle);
    if (isNeedGetResObj) {
        textStyle.textColorSetByUser = true;
        GetColorResourceObject(frameNode, textStyle);
    }
    TimePickerModelNG::SetSelectedTextStyle(frameNode, theme, textStyle);
}

void SetTimepickerSelectedTextStyle(ArkUINodeHandle node, uint32_t color, const char* fontInfo, int32_t style)
{
    SetTimepickerSelectedTextStyleBase(node, color, fontInfo, style, false);
}

void SetTimepickerSelectedTextStylePtr(
    ArkUINodeHandle node, uint32_t color, const char* fontInfo, int32_t style, bool isDefaultColor)
{
    SetTimepickerSelectedTextStyleBase(node, color, fontInfo, style, !isDefaultColor);
}

void SetTimepickerSelectedTextStyleWithResObj(
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
    InitTimePickerTextStyle(
        textStyleStruct->fontInfo, textStyleStruct->textColor, textStyleStruct->fontStyle, textStyle);
    SetTimePickerTextStyleResObj(textStyle, textStyleStruct->fontSizeRawPtr, textStyleStruct->fontFamilyRawPtr,
        textStyleStruct->textColorRawPtr);
    TimePickerModelNG::SetSelectedTextStyle(frameNode, theme, textStyle);
}

void ResetTimepickerSelectedTextStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    NG::PickerTextStyle pickerTextStyle;
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto pickerTheme = themeManager->GetTheme<PickerTheme>();
    TimePickerModelNG::SetSelectedTextStyle(frameNode, pickerTheme, pickerTextStyle);
}

void SetTimepickerDisappearTextStyleBase(
    ArkUINodeHandle node, uint32_t color, const char* fontInfo, int32_t style, bool isNeedGetResObj)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefPtr<PickerTheme> theme;
    if (!GetPickerThemeByFrameNode(frameNode, theme)) {
        return;
    }
    NG::PickerTextStyle textStyle;
    InitTimePickerTextStyle(fontInfo, color, style, textStyle);
    if (isNeedGetResObj) {
        textStyle.textColorSetByUser = true;
        GetColorResourceObject(frameNode, textStyle);
    }
    TimePickerModelNG::SetDisappearTextStyle(frameNode, theme, textStyle);
}

void SetTimepickerDisappearTextStyle(ArkUINodeHandle node, uint32_t color, const char* fontInfo, int32_t style)
{
    SetTimepickerDisappearTextStyleBase(node, color, fontInfo, style, false);
}

void SetTimepickerDisappearTextStylePtr(
    ArkUINodeHandle node, uint32_t color, const char* fontInfo, int32_t style, bool isDefaultColor)
{
    SetTimepickerDisappearTextStyleBase(node, color, fontInfo, style, !isDefaultColor);
}

void SetTimepickerDisappearTextStyleWithResObj(
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
    InitTimePickerTextStyle(
        textStyleStruct->fontInfo, textStyleStruct->textColor, textStyleStruct->fontStyle, textStyle);
    SetTimePickerTextStyleResObj(textStyle, textStyleStruct->fontSizeRawPtr, textStyleStruct->fontFamilyRawPtr,
        textStyleStruct->textColorRawPtr);
    TimePickerModelNG::SetDisappearTextStyle(frameNode, theme, textStyle);
}

void ResetTimepickerDisappearTextStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    NG::PickerTextStyle pickerTextStyle;
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto themeManager = context->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto pickerTheme = themeManager->GetTheme<PickerTheme>();

    TimePickerModelNG::SetDisappearTextStyle(frameNode, pickerTheme, pickerTextStyle);
}

void SetTimepickerUseMilitaryTime(ArkUINodeHandle node, int isUseMilitaryTime)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TimePickerModelNG::SetHour24(frameNode, isUseMilitaryTime);
}

void ResetTimepickerUseMilitaryTime(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TimePickerModelNG::SetHour24(frameNode, false);
}

void SetTimepickerLoop(ArkUINodeHandle node, int isLoop)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TimePickerModelNG::SetWheelModeEnabled(frameNode, isLoop);
}

void ResetTimepickerLoop(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TimePickerModelNG::SetWheelModeEnabled(frameNode, true);
}

void SetTimepickerDateTimeOptions(
    ArkUINodeHandle node, ArkUI_Int32 hourType, ArkUI_Int32 minuteType, ArkUI_Int32 secondType)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ZeroPrefixType hour = static_cast<ZeroPrefixType>(hourType);
    ZeroPrefixType minute = static_cast<ZeroPrefixType>(minuteType);
    ZeroPrefixType second = static_cast<ZeroPrefixType>(secondType);
    TimePickerModelNG::SetDateTimeOptions(frameNode, hour, minute, second);
}

void ResetTimepickerDateTimeOptions(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ZeroPrefixType hourType = ZeroPrefixType::AUTO;
    ZeroPrefixType minuteType = ZeroPrefixType::AUTO;
    ZeroPrefixType secondType = ZeroPrefixType::AUTO;
    TimePickerModelNG::SetDateTimeOptions(frameNode, hourType, minuteType, secondType);
}

void SetTimepickerEnableHapticFeedback(ArkUINodeHandle node, int enableHapticFeedback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TimePickerModelNG::SetIsEnableHapticFeedback(frameNode, enableHapticFeedback);
}

void ResetTimepickerEnableHapticFeedback(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TimePickerModelNG::SetIsEnableHapticFeedback(frameNode, true);
}

ArkUI_CharPtr GetTimepickerSelectedTextStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, "");
    PickerTextStyle pickerTextStyle = TimePickerModelNG::getSelectedTextStyle(frameNode);
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

ArkUI_CharPtr GetTimepickerTextStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, "");
    PickerTextStyle pickerTextStyle = TimePickerModelNG::getNormalTextStyle(frameNode);
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

ArkUI_CharPtr GetTimepickerDisappearTextStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, "");
    PickerTextStyle pickerTextStyle = TimePickerModelNG::getDisappearTextStyle(frameNode);
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

ArkUI_CharPtr GetTimepickerSelected(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, "");
    PickerTime pickerTime = TimePickerModelNG::getTimepickerSelected(frameNode);
    g_strValue = std::to_string(static_cast<uint32_t>(pickerTime.GetHour())) + ",";
    g_strValue = g_strValue + std::to_string(static_cast<uint32_t>(pickerTime.GetMinute())) + ",";
    g_strValue = g_strValue + std::to_string(static_cast<uint32_t>(pickerTime.GetSecond()));
    return g_strValue.c_str();
}

ArkUI_CharPtr GetTimepickerStart(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, "");
    PickerTime pickerTime = TimePickerModelNG::getTimepickerStart(frameNode);
    g_strValue = std::to_string(static_cast<uint32_t>(pickerTime.GetHour())) + ":";
    g_strValue = g_strValue + std::to_string(static_cast<uint32_t>(pickerTime.GetMinute())) + ":";
    g_strValue = g_strValue + std::to_string(static_cast<uint32_t>(pickerTime.GetSecond()));
    return g_strValue.c_str();
}

ArkUI_CharPtr GetTimepickerEnd(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, "");
    PickerTime pickerTime = TimePickerModelNG::getTimepickerEnd(frameNode);
    g_strValue = std::to_string(static_cast<uint32_t>(pickerTime.GetHour())) + ":";
    g_strValue = g_strValue + std::to_string(static_cast<uint32_t>(pickerTime.GetMinute())) + ":";
    g_strValue = g_strValue + std::to_string(static_cast<uint32_t>(pickerTime.GetSecond()));
    return g_strValue.c_str();
}

ArkUI_Uint32 GetTimepickerBackgroundColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return TimePickerModelNG::getTimepickerBackgroundColor(frameNode);
}

ArkUI_Int32 GetTimepickerUseMilitaryTime(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return TimePickerModelNG::getTimepickerUseMilitaryTime(frameNode);
}

void SetTimepickerEnableCascade(ArkUINodeHandle node, int isEnableCascade)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TimePickerModelNG::SetEnableCascade(frameNode, isEnableCascade);
}

void ResetTimepickerEnableCascade(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TimePickerModelNG::SetEnableCascade(frameNode, false);
}

ArkUI_Int32 GetTimepickerEnableCascade(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return TimePickerModelNG::GetTimepickerEnableCascade(frameNode);
}

void SetTimePickerDigitalCrownSensitivity(ArkUINodeHandle node, int32_t CrownSensitivity)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TimePickerModelNG::SetDigitalCrownSensitivity(frameNode, CrownSensitivity);
}

void ResetTimePickerDigitalCrownSensitivity(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TimePickerModelNG::SetDigitalCrownSensitivity(frameNode, DEFAULT_CROWNSENSITIVITY);
}

void SetTimepickerOnChangeExt(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onChange = reinterpret_cast<std::function<void(const BaseEventInfo*)>*>(callback);
    TimePickerModelNG::SetOnChange(frameNode, std::move(*onChange));
}

void ResetTimepickerOnChange(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    TimePickerModelNG::SetOnChange(frameNode, nullptr);
}
void SetTimePickerOnChange(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onChange = [extraParam](const BaseEventInfo* info) {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.componentAsyncEvent.subKind = ON_TIME_PICKER_CHANGE;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        const auto* eventInfo = TypeInfoHelper::DynamicCast<DatePickerChangeEvent>(info);
        std::unique_ptr<JsonValue> argsPtr = JsonUtil::ParseJsonString(eventInfo->GetSelectedStr());
        if (!argsPtr) {
            event.componentAsyncEvent.data[0].i32 = 0;
            event.componentAsyncEvent.data[1].i32 = 0;
        } else {
            auto hour = argsPtr->GetValue("hour");
            auto minute = argsPtr->GetValue("minute");
            if (hour && hour->IsNumber()) {
                event.componentAsyncEvent.data[0].i32 = hour->GetInt();
            }
            if (minute && minute->IsNumber()) {
                event.componentAsyncEvent.data[1].i32 = minute->GetInt();
            }
        }
        SendArkUISyncEvent(&event);
    };
    TimePickerModelNG::SetOnChange(frameNode, std::move(onChange));
}

ArkUINodeHandle CreateFrameNode(ArkUI_Int32 nodeId)
{
    auto frameNode = TimePickerModelNG::CreateFrameNode(nodeId);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode));
}

void CreateTimePicker(void* theme, ArkUI_Bool value)
{
    CHECK_NULL_VOID(theme);
    TimePickerModelNG::GetInstance()->CreateTimePicker(AceType::Claim(reinterpret_cast<PickerTheme*>(theme)), value);
}

void SetJSTimepickerStart(void* value)
{
    CHECK_NULL_VOID(value);
    TimePickerModelNG::GetInstance()->SetStartTime((*reinterpret_cast<PickerTime*>(value)));
}

void SetJSTimepickerEnd(void* value)
{
    CHECK_NULL_VOID(value);
    TimePickerModelNG::GetInstance()->SetEndTime((*reinterpret_cast<PickerTime*>(value)));
}

void SetJSSelectedTime(void* value)
{
    CHECK_NULL_VOID(value);
    TimePickerModelNG::GetInstance()->SetSelectedTime((*reinterpret_cast<PickerTime*>(value)));
}

void SetJSChangeEvent(void* value)
{
    CHECK_NULL_VOID(value);
    TimePickerModel::GetInstance()->SetChangeEvent(std::move((*reinterpret_cast<ChangeEvent*>(value))));
}

void SetJSSelectedTextStyle(void* theme, void* textStyle)
{
    CHECK_NULL_VOID(theme);
    CHECK_NULL_VOID(textStyle);
    TimePickerModelNG::GetInstance()->SetSelectedTextStyle(AceType::Claim((reinterpret_cast<Ace::PickerTheme*>(theme))),
        (*reinterpret_cast<NG::PickerTextStyle*>(textStyle)));
}

void SetJSNormalTextStyle(void* theme, void* textStyle)
{
    CHECK_NULL_VOID(theme);
    CHECK_NULL_VOID(textStyle);
    TimePickerModelNG::GetInstance()->SetNormalTextStyle(AceType::Claim((reinterpret_cast<Ace::PickerTheme*>(theme))),
        (*reinterpret_cast<NG::PickerTextStyle*>(textStyle)));
}

void SetJSDisappearTextStyle(void* theme, void* textStyle)
{
    CHECK_NULL_VOID(theme);
    CHECK_NULL_VOID(textStyle);
    TimePickerModelNG::GetInstance()->SetDisappearTextStyle(
        AceType::Claim((reinterpret_cast<Ace::PickerTheme*>(theme))),
        (*reinterpret_cast<NG::PickerTextStyle*>(textStyle)));
}

void UpdateUserSetSelectColor()
{
    TimePickerModel::GetInstance()->UpdateUserSetSelectColor();
}

void HasUserDefinedDisappearFontFamily(ArkUI_Bool isHas)
{
    TimePickerModel::GetInstance()->HasUserDefinedDisappearFontFamily(isHas);
}
void HasUserDefinedNormalFontFamily(ArkUI_Bool isHas)
{
    TimePickerModel::GetInstance()->HasUserDefinedNormalFontFamily(isHas);
}
void HasUserDefinedSelectedFontFamily(ArkUI_Bool isHas)
{
    TimePickerModel::GetInstance()->HasUserDefinedSelectedFontFamily(isHas);
}

void SetBackgroundColorWithResourceObj(ArkUI_Uint32 color, void* ojb)
{
    CHECK_NULL_VOID(ojb);
    ViewAbstractModel::GetInstance()->SetBackgroundColorWithResourceObj(
        Color(color), AceType::Claim((reinterpret_cast<ResourceObject*>(ojb))));
}
void SetBackgroundColor(ArkUI_Uint32 color)
{
    ViewAbstractModel::GetInstance()->SetBackgroundColor(Color(color));
}

void HasUserDefinedOpacity()
{
    TimePickerModel::GetInstance()->HasUserDefinedOpacity();
}

void SetOnEnterSelectedArea(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEnterSelectedArea = reinterpret_cast<std::function<void(const BaseEventInfo*)>*>(callback);
    TimePickerModelNG::SetOnEnterSelectedArea(frameNode, std::move(*onEnterSelectedArea));
}

void Show(void* pickerDialog, void* settingData, void* cancelEvent, void* acceptEvent, void* changeEvent,
    void* enterEvent, void* timePickerDialogEvent, void* buttonInfos)
{
    TimePickerDialogModel::GetInstance()->SetTimePickerDialogShow(*reinterpret_cast<PickerDialogInfo*>(pickerDialog),
        *reinterpret_cast<NG::TimePickerSettingData*>(settingData),
        std::move(*reinterpret_cast<std::function<void()>*>(cancelEvent)),
        std::move(*reinterpret_cast<std::function<void(const std::string&)>*>(acceptEvent)),
        std::move(*reinterpret_cast<std::function<void(const std::string&)>*>(changeEvent)),
        std::move(*reinterpret_cast<std::function<void(const std::string&)>*>(enterEvent)),
        *reinterpret_cast<TimePickerDialogEvent*>(timePickerDialogEvent),
        *reinterpret_cast<std::vector<ButtonInfo>*>(buttonInfos));
}
#ifndef CROSS_PLATFORM
void CreateTimePickerImpl(void* theme, ArkUI_Bool value)
{
    CHECK_NULL_VOID(theme);
    GetTimePickerModelImpl()->CreateTimePicker(AceType::Claim(reinterpret_cast<PickerTheme*>(theme)), value);
}
void SetJSSelectedTimeImpl(void* value)
{
    CHECK_NULL_VOID(value);
    GetTimePickerModelImpl()->SetSelectedTime((*reinterpret_cast<PickerTime*>(value)));
}
void SetTimepickerOnChangeExtImpl(ArkUINodeHandle node, void* callback)
{
    auto onChange = reinterpret_cast<std::function<void(const BaseEventInfo*)>*>(callback);
    GetTimePickerModelImpl()->SetOnChange(std::move(*onChange));
}
void SetOnEnterSelectedAreaImpl(ArkUINodeHandle node, void* callback)
{
    auto onEnterSelectedArea = reinterpret_cast<std::function<void(const BaseEventInfo*)>*>(callback);
    GetTimePickerModelImpl()->SetOnEnterSelectedArea(std::move(*onEnterSelectedArea));
}
void SetTimepickerUseMilitaryTimeImpl(ArkUINodeHandle node, int isUseMilitaryTime)
{
    GetTimePickerModelImpl()->SetHour24(isUseMilitaryTime);
}
void ResetTimepickerUseMilitaryTimeImpl(ArkUINodeHandle node)
{
    GetTimePickerModelImpl()->SetHour24(false);
}
void SetBackgroundColorImpl(ArkUI_Uint32 color)
{
    GetTimePickerModelImpl()->SetBackgroundColor(Color(color));
}
void SetTimepickerEnableCascadeImpl(ArkUINodeHandle node, int isEnableCascade)
{
    GetTimePickerModelImpl()->SetEnableCascade(isEnableCascade);
}
void ResetTimepickerEnableCascadeImpl(ArkUINodeHandle node)
{
    GetTimePickerModelImpl()->SetEnableCascade(false);
}
void SetJSTimepickerStartImpl(void* value) {}
void SetJSTimepickerEndImpl(void* value) {}
void SetJSSelectedTextStyleImpl(void* theme, void* textStyle) {}
void SetJSNormalTextStyleImpl(void* theme, void* textStyle) {}
void SetJSDisappearTextStyleImpl(void* theme, void* textStyle) {}
void SetTimepickerLoopImpl(ArkUINodeHandle node, int isLoop) {}
void ResetTimepickerLoopImpl(ArkUINodeHandle node) {}
void HasUserDefinedDisappearFontFamilyImpl(ArkUI_Bool isHas) {}
void HasUserDefinedNormalFontFamilyImpl(ArkUI_Bool isHas) {}
void HasUserDefinedSelectedFontFamilyImpl(ArkUI_Bool isHas) {}
void SetBackgroundColorWithResourceObjImpl(ArkUI_Uint32 color, void* ojb) {}
void SetJSChangeEventImpl(void* value) {}
void HasUserDefinedOpacityImpl() {}
void SetTimePickerDigitalCrownSensitivityImpl(ArkUINodeHandle node, int32_t CrownSensitivity) {}
void ResetTimePickerDigitalCrownSensitivityImpl(ArkUINodeHandle node) {}
void UpdateUserSetSelectColorImpl() {}
void SetTimepickerBackgroundColorImpl(ArkUINodeHandle node, uint32_t color) {}
void ShowImpl(void* pickerDialog, void* settingData, void* cancelEvent, void* acceptEvent, void* changeEvent,
    void* enterEvent, void* timePickerDialogEvent, void* buttonInfos)
{
    GetTimePickerDialogModelImpl()->SetTimePickerDialogShow(*reinterpret_cast<PickerDialogInfo*>(pickerDialog),
        *reinterpret_cast<NG::TimePickerSettingData*>(settingData),
        std::move(*reinterpret_cast<std::function<void()>*>(cancelEvent)),
        std::move(*reinterpret_cast<std::function<void(const std::string&)>*>(acceptEvent)),
        std::move(*reinterpret_cast<std::function<void(const std::string&)>*>(changeEvent)),
        std::move(*reinterpret_cast<std::function<void(const std::string&)>*>(enterEvent)),
        *reinterpret_cast<TimePickerDialogEvent*>(timePickerDialogEvent),
        *reinterpret_cast<std::vector<ButtonInfo>*>(buttonInfos));
}
#endif
} // namespace

namespace NodeModifier {
const ArkUITimepickerModifier* GetTimePickerDynamicModifier()
{
    static bool isCurrentUseNewPipeline = Container::IsCurrentUseNewPipeline();
    if (!isCurrentUseNewPipeline) {
#ifndef CROSS_PLATFORM
        CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
        static const ArkUITimepickerModifier modifierImpl = {
            .getTimepickerSelected = nullptr,
            .setTimepickerSelected = nullptr,
            .resetTimepickerSelected = nullptr,
            .getTimepickerStart = nullptr,
            .setTimepickerStart = nullptr,
            .resetTimepickerStart = nullptr,
            .getTimepickerEnd = nullptr,
            .setTimepickerEnd = nullptr,
            .resetTimepickerEnd = nullptr,
            .getTimepickerBackgroundColor = nullptr,
            .setTimepickerBackgroundColor = SetTimepickerBackgroundColorImpl,
            .getTimepickerDisappearTextStyle = nullptr,
            .setTimepickerDisappearTextStyle = nullptr,
            .setTimepickerDisappearTextStylePtr = nullptr,
            .setTimepickerDisappearTextStyleWithResObj = nullptr,
            .getTimepickerTextStyle = nullptr,
            .setTimepickerTextStyle = nullptr,
            .setTimepickerTextStylePtr = nullptr,
            .setTimepickerTextStyleWithResObj = nullptr,
            .getTimepickerSelectedTextStyle = nullptr,
            .setTimepickerSelectedTextStyle = nullptr,
            .setTimepickerSelectedTextStylePtr = nullptr,
            .setTimepickerSelectedTextStyleWithResObj = nullptr,
            .resetTimepickerDisappearTextStyle = nullptr,
            .resetTimepickerTextStyle = nullptr,
            .resetTimepickerSelectedTextStyle = nullptr,
            .resetTimepickerBackgroundColor = nullptr,
            .getTimepickerUseMilitaryTime = nullptr,
            .setTimepickerUseMilitaryTime = SetTimepickerUseMilitaryTimeImpl,
            .resetTimepickerUseMilitaryTime = ResetTimepickerUseMilitaryTimeImpl,
            .setTimepickerLoop = SetTimepickerLoopImpl,
            .resetTimepickerLoop = ResetTimepickerLoopImpl,
            .setTimepickerDateTimeOptions = nullptr,
            .resetTimepickerDateTimeOptions = nullptr,
            .setTimepickerEnableHapticFeedback = nullptr,
            .resetTimepickerEnableHapticFeedback = nullptr,
            .getTimepickerEnableCascade = nullptr,
            .setTimepickerEnableCascade = SetTimepickerEnableCascadeImpl,
            .resetTimepickerEnableCascade = ResetTimepickerEnableCascadeImpl,
            .setTimePickerDigitalCrownSensitivity = SetTimePickerDigitalCrownSensitivityImpl,
            .resetTimePickerDigitalCrownSensitivity = ResetTimePickerDigitalCrownSensitivityImpl,
            .setTimepickerOnChange = SetTimepickerOnChangeExtImpl,
            .resetTimepickerOnChange = nullptr,
            .setTimePickerOnChangeHandler = nullptr,
            .createFrameNode = nullptr,
            .create = CreateTimePickerImpl,
            .setJSTimepickerStart = SetJSTimepickerStartImpl,
            .setJSTimepickerEnd = SetJSTimepickerEndImpl,
            .setJSSelectedTime = SetJSSelectedTimeImpl,
            .setJSChangeEvent = SetJSChangeEventImpl,
            .setJSSelectedTextStyle = SetJSSelectedTextStyleImpl,
            .setJSDisappearTextStyle = SetJSDisappearTextStyleImpl,
            .setJSNormalTextStyle = SetJSNormalTextStyleImpl,
            .updateUserSetSelectColor = UpdateUserSetSelectColorImpl,
            .hasUserDefinedDisappearFontFamily = HasUserDefinedDisappearFontFamilyImpl,
            .hasUserDefinedNormalFontFamily = HasUserDefinedNormalFontFamilyImpl,
            .hasUserDefinedSelectedFontFamily = HasUserDefinedSelectedFontFamilyImpl,
            .setBackgroundColorWithResourceObj = SetBackgroundColorWithResourceObjImpl,
            .setBackgroundColor = SetBackgroundColorImpl,
            .hasUserDefinedOpacity = HasUserDefinedOpacityImpl,
            .setOnEnterSelectedArea = SetOnEnterSelectedAreaImpl,
            .show = ShowImpl,
        };
        CHECK_INITIALIZED_FIELDS_END(modifierImpl, 0, 0, 0); // don't move this line
        return &modifierImpl;
#endif
    }
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUITimepickerModifier modifier = {
        .getTimepickerSelected = GetTimepickerSelected,
        .setTimepickerSelected = SetTimepickerSelected,
        .resetTimepickerSelected = ResetTimepickerSelected,
        .getTimepickerStart = GetTimepickerStart,
        .setTimepickerStart = SetTimepickerStart,
        .resetTimepickerStart = ResetTimepickerStart,
        .getTimepickerEnd = GetTimepickerEnd,
        .setTimepickerEnd = SetTimepickerEnd,
        .resetTimepickerEnd = ResetTimepickerEnd,
        .getTimepickerBackgroundColor = GetTimepickerBackgroundColor,
        .setTimepickerBackgroundColor = SetTimepickerBackgroundColor,
        .getTimepickerDisappearTextStyle = GetTimepickerDisappearTextStyle,
        .setTimepickerDisappearTextStyle = SetTimepickerDisappearTextStyle,
        .setTimepickerDisappearTextStylePtr = SetTimepickerDisappearTextStylePtr,
        .setTimepickerDisappearTextStyleWithResObj = SetTimepickerDisappearTextStyleWithResObj,
        .getTimepickerTextStyle = GetTimepickerTextStyle,
        .setTimepickerTextStyle = SetTimepickerTextStyle,
        .setTimepickerTextStylePtr = SetTimepickerTextStylePtr,
        .setTimepickerTextStyleWithResObj = SetTimepickerTextStyleWithResObj,
        .getTimepickerSelectedTextStyle = GetTimepickerSelectedTextStyle,
        .setTimepickerSelectedTextStyle = SetTimepickerSelectedTextStyle,
        .setTimepickerSelectedTextStylePtr = SetTimepickerSelectedTextStylePtr,
        .setTimepickerSelectedTextStyleWithResObj = SetTimepickerSelectedTextStyleWithResObj,
        .resetTimepickerDisappearTextStyle = ResetTimepickerDisappearTextStyle,
        .resetTimepickerTextStyle = ResetTimepickerTextStyle,
        .resetTimepickerSelectedTextStyle = ResetTimepickerSelectedTextStyle,
        .resetTimepickerBackgroundColor = ResetTimepickerBackgroundColor,
        .getTimepickerUseMilitaryTime = GetTimepickerUseMilitaryTime,
        .setTimepickerUseMilitaryTime = SetTimepickerUseMilitaryTime,
        .resetTimepickerUseMilitaryTime = ResetTimepickerUseMilitaryTime,
        .setTimepickerLoop = SetTimepickerLoop,
        .resetTimepickerLoop = ResetTimepickerLoop,
        .setTimepickerDateTimeOptions = SetTimepickerDateTimeOptions,
        .resetTimepickerDateTimeOptions = ResetTimepickerDateTimeOptions,
        .setTimepickerEnableHapticFeedback = SetTimepickerEnableHapticFeedback,
        .resetTimepickerEnableHapticFeedback = ResetTimepickerEnableHapticFeedback,
        .getTimepickerEnableCascade = GetTimepickerEnableCascade,
        .setTimepickerEnableCascade = SetTimepickerEnableCascade,
        .resetTimepickerEnableCascade = ResetTimepickerEnableCascade,
        .setTimePickerDigitalCrownSensitivity = SetTimePickerDigitalCrownSensitivity,
        .resetTimePickerDigitalCrownSensitivity = ResetTimePickerDigitalCrownSensitivity,
        .setTimepickerOnChange = SetTimepickerOnChangeExt,
        .resetTimepickerOnChange = ResetTimepickerOnChange,
        .setTimePickerOnChangeHandler = SetTimePickerOnChange,
        .createFrameNode = CreateFrameNode,
        .create = CreateTimePicker,
        .setJSTimepickerStart = SetJSTimepickerStart,
        .setJSTimepickerEnd = SetJSTimepickerEnd,
        .setJSSelectedTime = SetJSSelectedTime,
        .setJSChangeEvent = SetJSChangeEvent,
        .setJSSelectedTextStyle = SetJSSelectedTextStyle,
        .setJSDisappearTextStyle = SetJSDisappearTextStyle,
        .setJSNormalTextStyle = SetJSNormalTextStyle,
        .updateUserSetSelectColor = UpdateUserSetSelectColor,
        .hasUserDefinedDisappearFontFamily = HasUserDefinedDisappearFontFamily,
        .hasUserDefinedNormalFontFamily = HasUserDefinedNormalFontFamily,
        .hasUserDefinedSelectedFontFamily = HasUserDefinedSelectedFontFamily,
        .setBackgroundColorWithResourceObj = SetBackgroundColorWithResourceObj,
        .setBackgroundColor = SetBackgroundColor,
        .hasUserDefinedOpacity = HasUserDefinedOpacity,
        .setOnEnterSelectedArea = SetOnEnterSelectedArea,
        .show = Show,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}

const CJUITimepickerModifier* GetCJUITimePickerModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUITimepickerModifier modifier = {
        .getTimepickerSelected = GetTimepickerSelected,
        .setTimepickerSelected = SetTimepickerSelected,
        .resetTimepickerSelected = ResetTimepickerSelected,
        .getTimepickerStart = GetTimepickerStart,
        .setTimepickerStart = SetTimepickerStart,
        .resetTimepickerStart = ResetTimepickerStart,
        .getTimepickerEnd = GetTimepickerEnd,
        .setTimepickerEnd = SetTimepickerEnd,
        .resetTimepickerEnd = ResetTimepickerEnd,
        .getTimepickerBackgroundColor = GetTimepickerBackgroundColor,
        .setTimepickerBackgroundColor = SetTimepickerBackgroundColor,
        .getTimepickerDisappearTextStyle = GetTimepickerDisappearTextStyle,
        .setTimepickerDisappearTextStyle = SetTimepickerDisappearTextStyle,
        .getTimepickerTextStyle = GetTimepickerTextStyle,
        .setTimepickerTextStyle = SetTimepickerTextStyle,
        .getTimepickerSelectedTextStyle = GetTimepickerSelectedTextStyle,
        .setTimepickerSelectedTextStyle = SetTimepickerSelectedTextStyle,
        .resetTimepickerDisappearTextStyle = ResetTimepickerDisappearTextStyle,
        .resetTimepickerTextStyle = ResetTimepickerTextStyle,
        .resetTimepickerSelectedTextStyle = ResetTimepickerSelectedTextStyle,
        .resetTimepickerBackgroundColor = ResetTimepickerBackgroundColor,
        .getTimepickerUseMilitaryTime = GetTimepickerUseMilitaryTime,
        .setTimepickerUseMilitaryTime = SetTimepickerUseMilitaryTime,
        .resetTimepickerUseMilitaryTime = ResetTimepickerUseMilitaryTime,
        .setTimepickerLoop = SetTimepickerLoop,
        .resetTimepickerLoop = ResetTimepickerLoop,
        .setTimepickerDateTimeOptions = SetTimepickerDateTimeOptions,
        .resetTimepickerDateTimeOptions = ResetTimepickerDateTimeOptions,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
