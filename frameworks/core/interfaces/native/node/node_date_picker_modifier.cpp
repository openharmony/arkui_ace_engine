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

#include "core/interfaces/native/node/node_date_picker_modifier.h"

#include "bridge/common/utils/utils.h"
#include "core/components_ng/pattern/picker/datepicker_model_ng.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t POS_0 = 0;
constexpr int32_t POS_1 = 1;
constexpr int32_t POS_2 = 2;
constexpr int YEAR_1900 = 1900;
constexpr int YEAR_1970 = 1970;
const char DEFAULT_DELIMITER = '|';
const int32_t ERROR_INT_CODE = -1;
std::string g_strValue;
const std::vector<OHOS::Ace::FontStyle> FONT_STYLES = { OHOS::Ace::FontStyle::NORMAL, OHOS::Ace::FontStyle::ITALIC };

ArkUI_CharPtr GetSelectedTextStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, "");
    PickerTextStyle pickerTextStyle = DatePickerModelNG::getSelectedTextStyle(frameNode);
    std::vector<std::string> fontFamilies = pickerTextStyle.fontFamily.value_or(std::vector<std::string>());
    if (fontFamilies.size() == 0) {
        fontFamilies.emplace_back("HarmonyOS Sans");
    }
    std::string families;
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
    g_strValue =
        g_strValue + StringUtils::ToString(pickerTextStyle.fontWeight.value_or(FontWeight::W100)) + ";";
    g_strValue = g_strValue + families + ";";
    g_strValue = g_strValue + StringUtils::ToStringNDK(pickerTextStyle.fontStyle.value_or(FontStyle::NORMAL));
    return g_strValue.c_str();
}

void SetSelectedTextStyle(ArkUINodeHandle node, const char* fontInfo, uint32_t color, int32_t style)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto theme = themeManager->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);

    NG::PickerTextStyle textStyle;
    std::vector<std::string> res;
    std::string fontValues = std::string(fontInfo);
    StringUtils::StringSplitter(fontValues, DEFAULT_DELIMITER, res);
    textStyle.fontSize = StringUtils::StringToCalcDimension(res[POS_0], false, DimensionUnit::FP);
    if (style >= 0 && style < static_cast<int32_t>(FONT_STYLES.size())) {
        textStyle.fontStyle = FONT_STYLES[style];
    } else {
        textStyle.fontStyle = FONT_STYLES[0];
    }
    textStyle.fontFamily = Framework::ConvertStrToFontFamilies(res[POS_2]);
    textStyle.fontWeight = StringUtils::StringToFontWeight(res[POS_1]);
    textStyle.textColor = Color(color);
    DatePickerModelNG::SetSelectedTextStyle(frameNode, theme, textStyle);
}

void ResetSelectedTextStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto theme = themeManager->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);

    NG::PickerTextStyle textStyle;
    auto selectedStyle = theme->GetOptionStyle(true, false);
    textStyle.textColor = selectedStyle.GetTextColor();
    textStyle.fontSize = selectedStyle.GetFontSize();
    textStyle.fontWeight = selectedStyle.GetFontWeight();
    DatePickerModelNG::SetSelectedTextStyle(frameNode, theme, textStyle);
}

ArkUI_CharPtr GetDatePickerTextStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, "");
    PickerTextStyle pickerTextStyle = DatePickerModelNG::getNormalTextStyle(frameNode);
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
    g_strValue =
        g_strValue + StringUtils::ToString(pickerTextStyle.fontWeight.value_or(FontWeight::W100)) + ";";
    g_strValue = g_strValue + families + ";";
    g_strValue = g_strValue + StringUtils::ToStringNDK(pickerTextStyle.fontStyle.value_or(FontStyle::NORMAL));
    return g_strValue.c_str();
}

void SetDatePickerTextStyle(ArkUINodeHandle node, const char* fontInfo, uint32_t color, int32_t style)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto theme = themeManager->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);

    NG::PickerTextStyle textStyle;
    std::vector<std::string> res;
    std::string fontValues = std::string(fontInfo);
    StringUtils::StringSplitter(fontValues, DEFAULT_DELIMITER, res);

    textStyle.fontSize = StringUtils::StringToCalcDimension(res[POS_0], false, DimensionUnit::FP);
    if (style >= 0 && style < static_cast<int32_t>(FONT_STYLES.size())) {
        textStyle.fontStyle = FONT_STYLES[style];
    } else {
        textStyle.fontStyle = FONT_STYLES[0];
    }
    textStyle.fontFamily = Framework::ConvertStrToFontFamilies(res[POS_2]);
    textStyle.fontWeight = StringUtils::StringToFontWeight(res[POS_1]);
    textStyle.textColor = Color(color);
    DatePickerModelNG::SetNormalTextStyle(frameNode, theme, textStyle);
}

void ResetDatePickerTextStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto theme = themeManager->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);

    NG::PickerTextStyle textStyle;
    auto normalStyle = theme->GetOptionStyle(false, false);
    textStyle.textColor = normalStyle.GetTextColor();
    textStyle.fontSize = normalStyle.GetFontSize();
    textStyle.fontWeight = normalStyle.GetFontWeight();
    DatePickerModelNG::SetNormalTextStyle(frameNode, theme, textStyle);
}

ArkUI_CharPtr GetDisappearTextStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, "");
    PickerTextStyle pickerTextStyle = DatePickerModelNG::getDisappearTextStyle(frameNode);
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
    g_strValue =
        g_strValue + StringUtils::ToString(pickerTextStyle.fontWeight.value_or(FontWeight::W100)) + ";";
    g_strValue = g_strValue + families + ";";
    g_strValue = g_strValue + StringUtils::ToStringNDK(pickerTextStyle.fontStyle.value_or(FontStyle::NORMAL));
    return g_strValue.c_str();
}

void SetDisappearTextStyle(ArkUINodeHandle node, const char* fontInfo, uint32_t color, int32_t style)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto theme = themeManager->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);

    NG::PickerTextStyle textStyle;
    std::vector<std::string> res;
    std::string fontValues = std::string(fontInfo);
    StringUtils::StringSplitter(fontValues, DEFAULT_DELIMITER, res);

    textStyle.fontSize = StringUtils::StringToCalcDimension(res[POS_0], false, DimensionUnit::FP);
    if (style >= 0 && style < static_cast<int32_t>(FONT_STYLES.size())) {
        textStyle.fontStyle = FONT_STYLES[style];
    } else {
        textStyle.fontStyle = FONT_STYLES[0];
    }
    textStyle.fontFamily = Framework::ConvertStrToFontFamilies(res[POS_2]);
    textStyle.fontWeight = StringUtils::StringToFontWeight(res[POS_1]);
    textStyle.textColor = Color(color);
    DatePickerModelNG::SetDisappearTextStyle(frameNode, theme, textStyle);
}

void ResetDisappearTextStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto theme = themeManager->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);

    NG::PickerTextStyle textStyle;
    auto disappearStyle = theme->GetDisappearOptionStyle();
    textStyle.textColor = disappearStyle.GetTextColor();
    textStyle.fontSize = disappearStyle.GetFontSize();
    textStyle.fontWeight = disappearStyle.GetFontWeight();
    DatePickerModelNG::SetDisappearTextStyle(frameNode, theme, textStyle);
}

ArkUI_Int32 GetLunar(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return DatePickerModelNG::getLunar(frameNode);
}

void SetLunar(ArkUINodeHandle node, int lunar)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DatePickerModelNG::SetShowLunar(frameNode, lunar);
}

void ResetLunar(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DatePickerModelNG::SetShowLunar(frameNode, false);
}

ArkUI_Uint32 GetDatePickerBackgroundColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return DatePickerModelNG::getBackgroundColor(frameNode);
}

void SetDatePickerBackgroundColor(ArkUINodeHandle node, uint32_t color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DatePickerModelNG::SetBackgroundColor(frameNode, Color(color));
}

void ResetDatePickerBackgroundColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DatePickerModelNG::SetBackgroundColor(frameNode, Color(Color::TRANSPARENT));
}

ArkUI_CharPtr GetStartDate(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, "");
    LunarDate lunarDate = DatePickerModelNG::getStartDate(frameNode);
    g_strValue = std::to_string(static_cast<uint32_t>(lunarDate.year)) + "-";
    g_strValue = g_strValue + std::to_string(static_cast<uint32_t>(lunarDate.month)) + "-";
    g_strValue = g_strValue + std::to_string(static_cast<uint32_t>(lunarDate.day));
    return g_strValue.c_str();
}

void SetStartDate(ArkUINodeHandle node, uint32_t year, uint32_t month, uint32_t day)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pickerDate = PickerDate(year, month, day);
    if (pickerDate.GetYear() < YEAR_1900) {
        pickerDate.SetYear(YEAR_1970);
        pickerDate.SetMonth(1);
        pickerDate.SetDay(1);
    }
    DatePickerModelNG::SetStartDate(frameNode, pickerDate);
}

void ResetStartDate(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DatePickerModelNG::SetStartDate(frameNode, PickerDate(1970, 1, 1));
}

ArkUI_CharPtr GetEndDate(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, "");
    LunarDate lunarDate = DatePickerModelNG::getEndDate(frameNode);
    g_strValue = std::to_string(static_cast<uint32_t>(lunarDate.year)) + "-";
    g_strValue = g_strValue + std::to_string(static_cast<uint32_t>(lunarDate.month)) + "-";
    g_strValue = g_strValue + std::to_string(static_cast<uint32_t>(lunarDate.day));
    return g_strValue.c_str();
}

void SetEndDate(ArkUINodeHandle node, uint32_t year, uint32_t month, uint32_t day)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DatePickerModelNG::SetEndDate(frameNode, PickerDate(year, month, day));
}

void ResetEndDate(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DatePickerModelNG::SetEndDate(frameNode, PickerDate(2100, 12, 31));
}

ArkUI_CharPtr GetSelectedDate(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, "");
    LunarDate lunarDate = DatePickerModelNG::getSelectedDate(frameNode);
    g_strValue = std::to_string(static_cast<uint32_t>(lunarDate.year)) + "-";
    g_strValue = g_strValue + std::to_string(static_cast<uint32_t>(lunarDate.month)) + "-";
    g_strValue = g_strValue + std::to_string(static_cast<uint32_t>(lunarDate.day));
    return g_strValue.c_str();
}

void SetSelectedDate(ArkUINodeHandle node, uint32_t year, uint32_t month, uint32_t day)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DatePickerModelNG::SetSelectedDate(frameNode, PickerDate(year, month, day));
}

void ResetSelectedDate(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    time_t now = time(nullptr);
    auto currentTm = localtime(&now);
    CHECK_NULL_VOID(currentTm);
    PickerDate pickerDate(currentTm->tm_year + 1900, currentTm->tm_mon + 1, currentTm->tm_mday);

    DatePickerModelNG::SetSelectedDate(frameNode, pickerDate);
}

void SetDatePickerMode(ArkUINodeHandle node, int value)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    if (value < 0 || value > static_cast<int32_t>(DatePickerMode::MONTH_AND_DAY)) {
        return;
    }
    DatePickerModelNG::SetMode(frameNode, static_cast<DatePickerMode>(value));
}

void ResetDatePickerMode(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    DatePickerModelNG::SetMode(frameNode, DatePickerMode::DATE);
}

ArkUI_Int32 GetDatePickerMode(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return static_cast<int>(DatePickerModelNG::getMode(frameNode));
}

ArkUI_Bool GetEnableHapticFeedback(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, true);
    return DatePickerModelNG::GetEnableHapticFeedback(frameNode);
}

void SetEnableHapticFeedback(ArkUINodeHandle node, int enableHapticFeedback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DatePickerModelNG::SetEnableHapticFeedback(frameNode, enableHapticFeedback);
}

void ResetEnableHapticFeedback(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DatePickerModelNG::SetEnableHapticFeedback(frameNode, true);
}

void SetDatePickerDigitalCrownSensitivity(ArkUINodeHandle node, int32_t CrownSensitivity)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DatePickerModelNG::SetDigitalCrownSensitivity(frameNode, CrownSensitivity);
}

void ResetDatePickerDigitalCrownSensitivity(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DatePickerModelNG::SetDigitalCrownSensitivity(frameNode, DEFAULT_CROWNSENSITIVITY);
}

ArkUI_Bool GetCanLoop(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ERROR_INT_CODE);
    return DatePickerModelNG::GetCanLoop(frameNode);
}

void SetCanLoop(ArkUINodeHandle node, int isLoop)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DatePickerModelNG::SetCanLoop(frameNode, isLoop);
}

void ResetCanLoop(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DatePickerModelNG::SetCanLoop(frameNode, true);
}

void SetDatePickerOnDateChangeExt(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onDateChange = reinterpret_cast<std::function<void(const BaseEventInfo*)>*>(callback);
    DatePickerModelNG::SetOnDateChange(frameNode, std::move(*onDateChange));
}

void ResetDatePickerOnDateChange(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DatePickerModelNG::SetOnDateChange(frameNode, nullptr);
}

void SetDatePickerOnChangeExt(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onChange = reinterpret_cast<std::function<void(const BaseEventInfo*)>*>(callback);
    DatePickerModelNG::SetOnChange(frameNode, std::move(*onChange));
}

void ResetDatePickerOnChange(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DatePickerModelNG::SetOnChange(frameNode, nullptr);
}

} // namespace

namespace NodeModifier {
const ArkUIDatePickerModifier* GetDatePickerModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIDatePickerModifier modifier = {
        .getSelectedTextStyle = GetSelectedTextStyle,
        .setSelectedTextStyle = SetSelectedTextStyle,
        .resetSelectedTextStyle = ResetSelectedTextStyle,
        .getDatePickerTextStyle = GetDatePickerTextStyle,
        .setDatePickerTextStyle = SetDatePickerTextStyle,
        .resetDatePickerTextStyle = ResetDatePickerTextStyle,
        .getDisappearTextStyle = GetDisappearTextStyle,
        .setDisappearTextStyle = SetDisappearTextStyle,
        .resetDisappearTextStyle = ResetDisappearTextStyle,
        .getLunar = GetLunar,
        .setLunar = SetLunar,
        .resetLunar = ResetLunar,
        .getStartDate = GetStartDate,
        .setStartDate = SetStartDate,
        .resetStartDate = ResetStartDate,
        .getEndDate = GetEndDate,
        .setEndDate = SetEndDate,
        .resetEndDate = ResetEndDate,
        .getSelectedDate = GetSelectedDate,
        .setSelectedDate = SetSelectedDate,
        .resetSelectedDate = ResetSelectedDate,
        .getDatePickerBackgroundColor = GetDatePickerBackgroundColor,
        .setDatePickerBackgroundColor = SetDatePickerBackgroundColor,
        .resetDatePickerBackgroundColor = ResetDatePickerBackgroundColor,
        .getDatePickerMode = GetDatePickerMode,
        .setDatePickerMode = SetDatePickerMode,
        .resetDatePickerMode = ResetDatePickerMode,
        .getEnableHapticFeedback = GetEnableHapticFeedback,
        .setEnableHapticFeedback = SetEnableHapticFeedback,
        .resetEnableHapticFeedback = ResetEnableHapticFeedback,
        .setDatePickerDigitalCrownSensitivity = SetDatePickerDigitalCrownSensitivity,
        .resetDatePickerDigitalCrownSensitivity = ResetDatePickerDigitalCrownSensitivity,
        .getCanLoop = GetCanLoop,
        .setCanLoop = SetCanLoop,
        .resetCanLoop = ResetCanLoop,
        .setDatePickerOnDateChange = SetDatePickerOnDateChangeExt,
        .resetDatePickerOnDateChange = ResetDatePickerOnDateChange,
        .setDatePickerOnChange = SetDatePickerOnChangeExt,
        .resetDatePickerOnChange = ResetDatePickerOnChange,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}

const CJUIDatePickerModifier* GetCJUIDatePickerModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIDatePickerModifier modifier = {
        .getSelectedTextStyle = GetSelectedTextStyle,
        .setSelectedTextStyle = SetSelectedTextStyle,
        .resetSelectedTextStyle = ResetSelectedTextStyle,
        .getDatePickerTextStyle = GetDatePickerTextStyle,
        .setDatePickerTextStyle = SetDatePickerTextStyle,
        .resetDatePickerTextStyle = ResetDatePickerTextStyle,
        .getDisappearTextStyle = GetDisappearTextStyle,
        .setDisappearTextStyle = SetDisappearTextStyle,
        .resetDisappearTextStyle = ResetDisappearTextStyle,
        .getLunar = GetLunar,
        .setLunar = SetLunar,
        .resetLunar = ResetLunar,
        .getStartDate = GetStartDate,
        .setStartDate = SetStartDate,
        .resetStartDate = ResetStartDate,
        .getEndDate = GetEndDate,
        .setEndDate = SetEndDate,
        .resetEndDate = ResetEndDate,
        .getSelectedDate = GetSelectedDate,
        .setSelectedDate = SetSelectedDate,
        .resetSelectedDate = ResetSelectedDate,
        .getDatePickerBackgroundColor = GetDatePickerBackgroundColor,
        .setDatePickerBackgroundColor = SetDatePickerBackgroundColor,
        .resetDatePickerBackgroundColor = ResetDatePickerBackgroundColor,
        .getDatePickerMode = GetDatePickerMode,
        .setDatePickerMode = SetDatePickerMode,
        .resetDatePickerMode = ResetDatePickerMode,
        .getEnableHapticFeedback = GetEnableHapticFeedback,
        .setEnableHapticFeedback = SetEnableHapticFeedback,
        .resetEnableHapticFeedback = ResetEnableHapticFeedback,
        .getCanLoop = GetCanLoop,
        .setCanLoop = SetCanLoop,
        .resetCanLoop = ResetCanLoop,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}
void SetDatePickerOnDateChange(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onDateChange = [extraParam](const BaseEventInfo* info) {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_DATE_PICKER_DATE_CHANGE;
        const auto* eventInfo = TypeInfoHelper::DynamicCast<DatePickerChangeEvent>(info);
        std::unique_ptr<JsonValue> argsPtr = JsonUtil::ParseJsonString(eventInfo->GetSelectedStr());
        if (!argsPtr) {
            event.componentAsyncEvent.data[0].i32 = 1970;
            event.componentAsyncEvent.data[1].i32 = 1;
            event.componentAsyncEvent.data[2].i32 = 1;
            event.componentAsyncEvent.data[3].i32 = 0;
            event.componentAsyncEvent.data[4].i32 = 0;
        }
        auto year = argsPtr->GetValue("year");
        auto month = argsPtr->GetValue("month");
        auto day = argsPtr->GetValue("day");
        auto hour = argsPtr->GetValue("hour");
        auto minute = argsPtr->GetValue("minute");
        if (year && year->IsNumber()) {
            event.componentAsyncEvent.data[0].i32 = year->GetInt();
        }
        if (month && month->IsNumber()) {
            event.componentAsyncEvent.data[1].i32 = month->GetInt();
        }
        if (day && day->IsNumber()) {
            event.componentAsyncEvent.data[2].i32 = day->GetInt();
        }
        if (hour && hour->IsNumber()) {
            event.componentAsyncEvent.data[3].i32 = hour->GetInt();
        }
        if (minute && minute->IsNumber()) {
            event.componentAsyncEvent.data[4].i32 = minute->GetInt();
        }
        SendArkUISyncEvent(&event);
    };
    DatePickerModelNG::SetOnDateChange(frameNode, std::move(onDateChange));
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
