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

#include "base/geometry/dimension.h"
#include "base/utils/utils.h"
#include "bridge/common/utils/utils.h"
#include "frameworks/core/components/common/properties/text_style.h"
#include "core/components/picker/picker_theme.h"
#include "core/components_ng/pattern/picker/datepicker_model_ng.h"
#include "core/components_ng/pattern/picker/picker_type_define.h"
#include "core/interfaces/native/node/node_api.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int POS_0 = 0;
constexpr int POS_1 = 1;
constexpr int POS_2 = 2;
const char DEFAULT_DELIMITER = '|';
const std::vector<OHOS::Ace::FontStyle> FONT_STYLES = { OHOS::Ace::FontStyle::NORMAL, OHOS::Ace::FontStyle::ITALIC };
void SetSelectedTextStyle(
    ArkUINodeHandle node, const char* fontInfo, uint32_t color, int32_t style)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);

    NG::PickerTextStyle textStyle;
    std::vector<std::string> res;
    std::string fontValues = std::string(fontInfo);
    StringUtils::StringSplitter(fontValues, DEFAULT_DELIMITER, res);
    textStyle.fontSize =
        StringUtils::StringToCalcDimension(res[POS_0], false, DimensionUnit::FP);
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
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);

    NG::PickerTextStyle textStyle;
    auto selectedStyle = theme->GetOptionStyle(true, false);
    textStyle.textColor = selectedStyle.GetTextColor();
    textStyle.fontSize = selectedStyle.GetFontSize();
    textStyle.fontWeight = selectedStyle.GetFontWeight();
    DatePickerModelNG::SetSelectedTextStyle(frameNode, theme, textStyle);
}

void SetDatePickerTextStyle(
    ArkUINodeHandle node, const char* fontInfo, uint32_t color, int32_t style)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);

    NG::PickerTextStyle textStyle;
    std::vector<std::string> res;
    std::string fontValues = std::string(fontInfo);
    StringUtils::StringSplitter(fontValues, DEFAULT_DELIMITER, res);
    
    textStyle.fontSize =
        StringUtils::StringToCalcDimension(res[POS_0], false, DimensionUnit::FP);
    if (style >= 0 && style < static_cast<int32_t>(FONT_STYLES.size())) {
        textStyle.fontStyle = FONT_STYLES[style];
    } else {
        textStyle.fontStyle = FONT_STYLES[0];
    }
    textStyle.fontFamily = Framework::ConvertStrToFontFamilies(res[POS_2]);
    textStyle.fontWeight=StringUtils::StringToFontWeight(res[POS_1]);
    textStyle.textColor = Color(color);
    DatePickerModelNG::SetNormalTextStyle(frameNode, theme, textStyle);
}

void ResetDatePickerTextStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);

    NG::PickerTextStyle textStyle;
    auto normalStyle = theme->GetOptionStyle(false, false);
    textStyle.textColor = normalStyle.GetTextColor();
    textStyle.fontSize = normalStyle.GetFontSize();
    textStyle.fontWeight = normalStyle.GetFontWeight();
    DatePickerModelNG::SetNormalTextStyle(frameNode, theme, textStyle);
}

void SetDisappearTextStyle(
    ArkUINodeHandle node, const char* fontInfo, uint32_t color, int32_t style)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);

    NG::PickerTextStyle textStyle;
    std::vector<std::string> res;
    std::string fontValues = std::string(fontInfo);
    StringUtils::StringSplitter(fontValues, DEFAULT_DELIMITER, res);
    
    textStyle.fontSize =
        StringUtils::StringToCalcDimension(res[POS_0], false, DimensionUnit::FP);
    if (style >= 0 && style < static_cast<int32_t>(FONT_STYLES.size())) {
        textStyle.fontStyle = FONT_STYLES[style];
    } else {
        textStyle.fontStyle = FONT_STYLES[0];
    }
    textStyle.fontFamily = Framework::ConvertStrToFontFamilies(res[POS_2]);
    textStyle.fontWeight=StringUtils::StringToFontWeight(res[POS_1]);
    textStyle.textColor = Color(color);
    DatePickerModelNG::SetDisappearTextStyle(frameNode, theme, textStyle);
}

void ResetDisappearTextStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);

    NG::PickerTextStyle textStyle;
    auto disappearStyle = theme->GetDisappearOptionStyle();
    textStyle.textColor = disappearStyle.GetTextColor();
    textStyle.fontSize = disappearStyle.GetFontSize();
    textStyle.fontWeight = disappearStyle.GetFontWeight();
    DatePickerModelNG::SetDisappearTextStyle(frameNode, theme, textStyle);
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

void SetStartDate(ArkUINodeHandle node, uint32_t year, uint32_t month, uint32_t day)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DatePickerModelNG::SetStartDate(frameNode, PickerDate(year, month, day));
}

void ResetStartDate(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DatePickerModelNG::SetStartDate(frameNode, PickerDate(1970, 1, 1));
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
    PickerDate pickerDate(currentTm->tm_year + 1900, currentTm->tm_mon + 1, currentTm->tm_mday);

    DatePickerModelNG::SetSelectedDate(frameNode, pickerDate);
}
} // namespace

namespace NodeModifier {
const ArkUIDatePickerModifier* GetDatePickerModifier()
{
    static const ArkUIDatePickerModifier modifier = {
        SetSelectedTextStyle, ResetSelectedTextStyle, SetDatePickerTextStyle,
        ResetDatePickerTextStyle, SetDisappearTextStyle, ResetDisappearTextStyle,
        SetLunar, ResetLunar, SetStartDate, ResetStartDate, SetEndDate, ResetEndDate,
        SetSelectedDate, ResetSelectedDate, SetDatePickerBackgroundColor,
        ResetDatePickerBackgroundColor
    };

    return &modifier;
}

void SetDatePickerOnDateChange(ArkUINodeHandle node, ArkUI_Int32 eventId, void* extraParam)
{
    auto onDateChange = [eventId, extraParam](const BaseEventInfo* info) {
        ArkUINodeEvent event;
        event.kind = ON_DATE_PICKER_DATE_CHANGE;
        event.eventId = eventId;
        event.extraParam= extraParam;
        const auto* eventInfo = TypeInfoHelper::DynamicCast<DatePickerChangeEvent>(info);
        std::unique_ptr<JsonValue> argsPtr = JsonUtil::ParseJsonString(eventInfo->GetSelectedStr());
        if (!argsPtr) {
            event.componentAsyncEvent.data[0].i32 = 1970;
            event.componentAsyncEvent.data[1].i32 = 1;
            event.componentAsyncEvent.data[1].i32 = 1;
            event.componentAsyncEvent.data[1].i32 = 0;
            event.componentAsyncEvent.data[1].i32 = 0;
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
        SendArkUIAsyncEvent(&event);
    };
    DatePickerModel::GetInstance()->SetOnDateChange(std::move(onDateChange));
}
}
} // namespace OHOS::Ace::NG
