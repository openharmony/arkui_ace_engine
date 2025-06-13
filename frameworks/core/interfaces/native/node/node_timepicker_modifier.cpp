/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/node/node_timepicker_modifier.h"

#include "bridge/common/utils/utils.h"
#include "core/components_ng/pattern/tabs/tabs_model.h"
#include "core/interfaces/native/node/node_textpicker_modifier.h"
#include "core/pipeline_ng/pipeline_context.h"

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
std::string g_strValue;

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

void SetTimePickerTextStyleResObj(NG::PickerTextStyle& textStyle, void* fontSizeRawPtr, void* fontFamilyRawPtr,
    void* textColorRawPtr)
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

void SetTimepickerTextStyle(ArkUINodeHandle node, uint32_t color, const char* fontInfo, int32_t style)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefPtr<PickerTheme> theme;
    if (!GetPickerThemeByFrameNode(frameNode, theme)) {
        return;
    }
    NG::PickerTextStyle textStyle;
    InitTimePickerTextStyle(fontInfo, color, style, textStyle);
    TimePickerModelNG::SetNormalTextStyle(frameNode, theme, textStyle);
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
    InitTimePickerTextStyle(textStyleStruct->fontInfo, textStyleStruct->textColor, textStyleStruct->fontStyle,
        textStyle);
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

void SetTimepickerSelectedTextStyle(ArkUINodeHandle node, uint32_t color, const char* fontInfo, int32_t style)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefPtr<PickerTheme> theme;
    if (!GetPickerThemeByFrameNode(frameNode, theme)) {
        return;
    }
    NG::PickerTextStyle textStyle;
    InitTimePickerTextStyle(fontInfo, color, style, textStyle);
    TimePickerModelNG::SetSelectedTextStyle(frameNode, theme, textStyle);
}

void SetTimepickerSelectedTextStyleWithResObj(ArkUINodeHandle node,
    const struct ArkUIPickerTextStyleStruct* textStyleStruct)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefPtr<PickerTheme> theme;
    if (!GetPickerThemeByFrameNode(frameNode, theme)) {
        return;
    }
    NG::PickerTextStyle textStyle;
    InitTimePickerTextStyle(textStyleStruct->fontInfo, textStyleStruct->textColor, textStyleStruct->fontStyle,
        textStyle);
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

void SetTimepickerDisappearTextStyle(ArkUINodeHandle node, uint32_t color, const char* fontInfo, int32_t style)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefPtr<PickerTheme> theme;
    if (!GetPickerThemeByFrameNode(frameNode, theme)) {
        return;
    }
    NG::PickerTextStyle textStyle;
    InitTimePickerTextStyle(fontInfo, color, style, textStyle);
    TimePickerModelNG::SetDisappearTextStyle(frameNode, theme, textStyle);
}

void SetTimepickerDisappearTextStyleWithResObj(ArkUINodeHandle node,
    const struct ArkUIPickerTextStyleStruct* textStyleStruct)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefPtr<PickerTheme> theme;
    if (!GetPickerThemeByFrameNode(frameNode, theme)) {
        return;
    }
    NG::PickerTextStyle textStyle;
    InitTimePickerTextStyle(textStyleStruct->fontInfo, textStyleStruct->textColor, textStyleStruct->fontStyle,
        textStyle);
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
    //set index start
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
    //set index start
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
    //set index start
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
    return TimePickerModelNG::getTimepickerEnableCascade(frameNode);
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
} // namespace

namespace NodeModifier {
const ArkUITimepickerModifier* GetTimepickerModifier()
{
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
        .setTimepickerDisappearTextStyleWithResObj = SetTimepickerDisappearTextStyleWithResObj,
        .getTimepickerTextStyle = GetTimepickerTextStyle,
        .setTimepickerTextStyle = SetTimepickerTextStyle,
        .setTimepickerTextStyleWithResObj = SetTimepickerTextStyleWithResObj,
        .getTimepickerSelectedTextStyle = GetTimepickerSelectedTextStyle,
        .setTimepickerSelectedTextStyle = SetTimepickerSelectedTextStyle,
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
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}

const CJUITimepickerModifier* GetCJUITimepickerModifier()
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
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
