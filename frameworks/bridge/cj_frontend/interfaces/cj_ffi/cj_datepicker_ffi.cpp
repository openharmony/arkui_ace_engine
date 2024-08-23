/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_datepicker_ffi.h"


#include "cj_lambda.h"
#include "bridge/common/utils/utils.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_view_abstract_ffi.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/picker/datepicker_model_ng.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

namespace {
const int MAX_YEAR = 2100;
const int MIN_YEAR = 1900;

PickerDate ParseDate(FfiTime data)
{
    auto pickerDate = PickerDate();
    pickerDate.SetYear(data.year);
    pickerDate.SetMonth(data.month);
    pickerDate.SetDay(data.day);

    return pickerDate;
}

FFiDatePickerResult DatePickerChangeEventToFfi(const DatePickerChangeEvent& eventInfo)
{
    FFiDatePickerResult result;
    auto infoStr = eventInfo.GetSelectedStr();
    std::unique_ptr<JsonValue> argsPtr = JsonUtil::ParseJsonString(eventInfo.GetSelectedStr());
    if (!argsPtr) {
        LOGW("selectedStr is not exist.");
        return result;
    }
    const auto year = argsPtr->GetValue("year")->GetInt();
    const auto month = argsPtr->GetValue("month")->GetInt() + 1; // 0-11 means 1 to 12 months
    const auto day = argsPtr->GetValue("day")->GetInt();

    result.year = year;
    result.month = month;
    result.day = day;

    return result;
}
}

extern "C" {
void ConvertToNoramlDate(PickerDate& date)
{
    auto theme = GetTheme<PickerTheme>();
    if (date.GetYear() < MIN_YEAR) {
        date = theme->GetDefaultStartDate();
    }
    if (date.GetYear() > MAX_YEAR) {
        date = theme->GetDefaultEndDate();
    }
}

void FfiOHOSAceFrameworkDatePickerCreate(FfiTime startDate, FfiTime endDate, FfiTime selectedDate)
{
    auto theme = GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);
    auto parseStartDate = ParseDate(startDate);
    auto parseEndDate = ParseDate(endDate);
    auto parseSelectedDate = ParseDate(selectedDate);

    ConvertToNoramlDate(parseStartDate);
    ConvertToNoramlDate(parseEndDate);
    ConvertToNoramlDate(parseSelectedDate);
    
    auto startDays = parseStartDate.ToDays();
    auto endDays = parseEndDate.ToDays();
    auto selectedDays = parseSelectedDate.ToDays();
    if (startDays > endDays) {
        parseStartDate = theme->GetDefaultStartDate();
        parseEndDate = theme->GetDefaultEndDate();
        startDays = parseStartDate.ToDays();
        endDays = parseEndDate.ToDays();
    }
    if (selectedDays > endDays) {
        parseSelectedDate = parseEndDate;
    }
    if (selectedDays < startDays) {
        parseSelectedDate = parseStartDate;
    }

    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    DatePickerModel::GetInstance()->SetStartDate(parseStartDate);
    DatePickerModel::GetInstance()->SetEndDate(parseEndDate);
    DatePickerModel::GetInstance()->SetSelectedDate(parseSelectedDate);
    FfiOHOSAceFrameworkDatePickerSetDefaultAttributes();
}

void FfiOHOSAceFrameworkDatePickerSetLunar(bool isLunar)
{
    DatePickerModel::GetInstance()->SetShowLunar(isLunar);
}

void FfiOHOSAceFrameworkDatePickerUseMilitaryTime(bool isUseMilitaryTime)
{
    DatePickerModel::GetInstance()->SetHour24(isUseMilitaryTime);
}

void FfiOHOSAceFrameworkDatePickerSetOnChange(
    void (*callback)(int32_t year, int32_t month, int32_t day))
{
    auto onChange = [lambda = CJLambda::Create(callback)](const BaseEventInfo* index) -> void {
        auto* eventInfo = TypeInfoHelper::DynamicCast<DatePickerChangeEvent>(index);
        const auto infoResult = DatePickerChangeEventToFfi(*eventInfo);
        lambda(infoResult.year, infoResult.month, infoResult.day);
    };
    auto* getInstance = NG::ViewStackProcessor::GetInstance();

    CHECK_NULL_VOID(getInstance);
    auto getMainFrameNode = getInstance->GetMainFrameNode();
    CHECK_NULL_VOID(getMainFrameNode);

    DatePickerModel::GetInstance()->SetOnChange(std::move(onChange));
}

void FfiOHOSAceFrameworkDatePickerSetOnDateChange(
    void (*callback)(int32_t year, int32_t month, int32_t day))
{
    auto onDateChange = [lambda = CJLambda::Create(callback)](const BaseEventInfo* index) -> void {
        auto* eventInfo = TypeInfoHelper::DynamicCast<DatePickerChangeEvent>(index);
        const auto infoResult = DatePickerChangeEventToFfi(*eventInfo);
        lambda(infoResult.year, infoResult.month, infoResult.day);
    };
    auto* getInstance = NG::ViewStackProcessor::GetInstance();

    CHECK_NULL_VOID(getInstance);
    auto getMainFrameNode = getInstance->GetMainFrameNode();
    CHECK_NULL_VOID(getMainFrameNode);

    DatePickerModel::GetInstance()->SetOnDateChange(std::move(onDateChange));
}

void FfiOHOSAceFrameworkDatePickerSetDefaultAttributes(void)
{
    auto theme = GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);
    NG::PickerTextStyle textStyle;
    auto selectedStyle = theme->GetOptionStyle(true, false);
    textStyle.textColor = selectedStyle.GetTextColor();
    textStyle.fontSize = selectedStyle.GetFontSize();
    textStyle.fontWeight = selectedStyle.GetFontWeight();
    DatePickerModel::GetInstance()->SetSelectedTextStyle(theme, textStyle);

    auto disappearStyle = theme->GetDisappearOptionStyle();
    textStyle.textColor = disappearStyle.GetTextColor();
    textStyle.fontSize = disappearStyle.GetFontSize();
    textStyle.fontWeight = disappearStyle.GetFontWeight();
    DatePickerModel::GetInstance()->SetDisappearTextStyle(theme, textStyle);

    auto normalStyle = theme->GetOptionStyle(false, false);
    textStyle.textColor = normalStyle.GetTextColor();
    textStyle.fontSize = normalStyle.GetFontSize();
    textStyle.fontWeight = normalStyle.GetFontWeight();
    DatePickerModel::GetInstance()->SetNormalTextStyle(theme, textStyle);
}

void FfiOHOSAceFrameworkDatePickerSetBackgroundColor(uint32_t color)
{
    DatePickerModel::GetInstance()->SetBackgroundColor(Color(color));
}

void FfiOHOSAceFrameworkDatePickerSetDisappearTextStyle(uint32_t color, double size, int32_t unit,
    const char* weight, const char* family, uint32_t style)
{
    auto theme = GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);
    NG::PickerTextStyle textStyle;

    textStyle.textColor = Color(color);
    CalcDimension fontSize = CalcDimension(size, DimensionUnit(unit));
    textStyle.fontSize = fontSize;

    std::string weightVal = weight;
    textStyle.fontWeight = ConvertStrToFontWeight(weightVal);

    std::string familyVal = family;
    textStyle.fontFamily = ConvertStrToFontFamilies(familyVal);
    textStyle.fontStyle = static_cast<FontStyle>(style);

    DatePickerModel::GetInstance()->SetDisappearTextStyle(theme, textStyle);
}

void FfiOHOSAceFrameworkDatePickerSetTextStyle(uint32_t color, double size, int32_t unit,
    const char* weight, const char* family, uint32_t style)
{
    auto theme = GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);
    NG::PickerTextStyle textStyle;

    textStyle.textColor = Color(color);
    CalcDimension fontSize = CalcDimension(size, DimensionUnit(unit));
    textStyle.fontSize = fontSize;

    std::string weightVal = weight;
    textStyle.fontWeight = ConvertStrToFontWeight(weightVal);

    std::string familyVal = family;
    textStyle.fontFamily = ConvertStrToFontFamilies(familyVal);
    textStyle.fontStyle = static_cast<FontStyle>(style);

    DatePickerModel::GetInstance()->SetNormalTextStyle(theme, textStyle);
}

void FfiOHOSAceFrameworkDatePickerSetSelectedTextStyle(uint32_t color, double size, int32_t unit,
    const char* weight, const char* family, uint32_t style)
{
    auto theme = GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);
    NG::PickerTextStyle textStyle;

    textStyle.textColor = Color(color);
    CalcDimension fontSize = CalcDimension(size, DimensionUnit(unit));
    textStyle.fontSize = fontSize;

    std::string weightVal = weight;
    textStyle.fontWeight = ConvertStrToFontWeight(weightVal);

    std::string familyVal = family;
    textStyle.fontFamily = ConvertStrToFontFamilies(familyVal);
    textStyle.fontStyle = static_cast<FontStyle>(style);

    DatePickerModel::GetInstance()->SetSelectedTextStyle(theme, textStyle);
}
}
