/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "core/components_ng/pattern/calendar/calendar_model_ng.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "core/interfaces/native/implementation/calendar_controller_peer.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "base/json/json_util.h"

namespace OHOS::Ace::NG {
namespace {
void SetFirstDay(ObtainedMonth& obtainedMonth)
{
    for (const auto& item : obtainedMonth.days) {
        if (item.day == 1) {
            obtainedMonth.firstDayIndex = item.index;
            break;
        }
    }
}

std::string GetDaysIndexes(uint32_t bits)
{
    constexpr uint32_t DAY_OF_WEEK = 7;
    std::string result;
    for (uint32_t i = 0; i < DAY_OF_WEEK; ++i) {
        if (bits & (1 << i)) {
            if (!result.empty()) {
                result += ",";
            }
            result += std::to_string(i);
        }
    }
    return result;
}
} // namespace

namespace Converter {
template<>
CalendarDay Convert(const Ark_CalendarDay& src)
{
    return {
        .index = Convert<int32_t>(src.index),
        .day = Convert<int32_t>(src.day),
        .isFirstOfLunar = Convert<bool>(src.isFirstOfLunar),
        .hasSchedule = Convert<bool>(src.hasSchedule),
        .markLunarDay = Convert<bool>(src.markLunarDay),
        .lunarMonth = Convert<std::string>(src.lunarMonth),
        .lunarDay = Convert<std::string>(src.lunarDay),
        .dayMark = Convert<std::string>(src.dayMark),
        .dayMarkValue = Convert<std::string>(src.dayMarkValue),
        .month { .year = Convert<int32_t>(src.year), .month = Convert<int32_t>(src.month) },
    };
}

template<>
ObtainedMonth Convert(const Ark_MonthData& src)
{
    ObtainedMonth obtainedMonth = {
        .year = Convert<int32_t>(src.year),
        .month = Convert<int32_t>(src.month),
        .days = Convert<std::vector<CalendarDay>>(src.data),
    };
    SetFirstDay(obtainedMonth);
    return obtainedMonth;
}

template<>
CalendarData Convert(const Ark_Type_CalendarInterface_value& src)
{
    const auto peer = OptConvert<Ark_CalendarController>(src.controller);
    return {
        .date = {
            .day = Convert<int32_t>(src.date.day),
            .month { .year = Convert<int32_t>(src.date.year), .month = Convert<int32_t>(src.date.month) }
        },
        .currentData = Convert<ObtainedMonth>(src.currentData),
        .preData = Convert<ObtainedMonth>(src.preData),
        .nextData = Convert<ObtainedMonth>(src.nextData),
        .controller = peer ? peer.value()->controller : nullptr,
    };
}

template<>
CurrentDayStyleData Convert(const Ark_CurrentDayStyle& src)
{
    return {
        .dayColor = OptConvert<Color>(src.dayColor),
        .lunarColor = OptConvert<Color>(src.lunarColor),
        .markLunarColor = OptConvert<Color>(src.markLunarColor),
        .dayFontSize = OptConvert<Dimension>(src.dayFontSize),
        .lunarDayFontSize = OptConvert<Dimension>(src.lunarDayFontSize),
        .dayHeight = OptConvert<Dimension>(src.dayHeight),
        .dayWidth = OptConvert<Dimension>(src.dayWidth),
        .gregorianCalendarHeight = OptConvert<Dimension>(src.gregorianCalendarHeight),
        .lunarHeight = OptConvert<Dimension>(src.lunarHeight),
        .dayYAxisOffset = OptConvert<Dimension>(src.dayYAxisOffset),
        .lunarDayYAxisOffset = OptConvert<Dimension>(src.lunarDayYAxisOffset),
        .underscoreXAxisOffset = OptConvert<Dimension>(src.underscoreXAxisOffset),
        .underscoreYAxisOffset = OptConvert<Dimension>(src.underscoreYAxisOffset),
        .scheduleMarkerXAxisOffset = OptConvert<Dimension>(src.scheduleMarkerXAxisOffset),
        .scheduleMarkerYAxisOffset = OptConvert<Dimension>(src.scheduleMarkerYAxisOffset),
        .colSpace = OptConvert<Dimension>(src.colSpace),
        .dailyFiveRowSpace = OptConvert<Dimension>(src.dailyFiveRowSpace),
        .dailySixRowSpace = OptConvert<Dimension>(src.dailySixRowSpace),
        .underscoreWidth = OptConvert<Dimension>(src.underscoreWidth),
        .underscoreLength = OptConvert<Dimension>(src.underscoreLength),
        .scheduleMarkerRadius = OptConvert<Dimension>(src.scheduleMarkerRadius),
        .boundaryRowOffset = OptConvert<Dimension>(src.boundaryRowOffset),
        .boundaryColOffset = OptConvert<Dimension>(src.boundaryColOffset),
    };
}

template<>
NonCurrentDayStyleData Convert(const Ark_NonCurrentDayStyle& src)
{
    return {
        .nonCurrentMonthDayColor = OptConvert<Color>(src.nonCurrentMonthDayColor),
        .nonCurrentMonthLunarColor = OptConvert<Color>(src.nonCurrentMonthLunarColor),
        .nonCurrentMonthWorkDayMarkColor = OptConvert<Color>(src.nonCurrentMonthWorkDayMarkColor),
        .nonCurrentMonthOffDayMarkColor = OptConvert<Color>(src.nonCurrentMonthOffDayMarkColor),
    };
}

template<>
TodayStyleData Convert(const Ark_TodayStyle& src)
{
    return {
        .focusedDayColor = OptConvert<Color>(src.focusedDayColor),
        .focusedLunarColor = OptConvert<Color>(src.focusedLunarColor),
        .focusedAreaBackgroundColor = OptConvert<Color>(src.focusedAreaBackgroundColor),
        .focusedAreaRadius = OptConvert<Dimension>(src.focusedAreaRadius),
    };
}

template<>
WeekStyleData Convert(const Ark_WeekStyle& src)
{
    return {
        .weekColor = OptConvert<Color>(src.weekColor),
        .weekendDayColor = OptConvert<Color>(src.weekendDayColor),
        .weekendLunarColor = OptConvert<Color>(src.weekendLunarColor),
        .weekFontSize = OptConvert<Dimension>(src.weekFontSize),
        .weekHeight = OptConvert<Dimension>(src.weekHeight),
        .weekWidth = OptConvert<Dimension>(src.weekWidth),
        .weekAndDayRowSpace = OptConvert<Dimension>(src.weekAndDayRowSpace),
    };
}

template<>
WorkStateStyleData Convert(const Ark_WorkStateStyle& src)
{
    return {
        .workDayMarkColor = OptConvert<Color>(src.workDayMarkColor),
        .offDayMarkColor = OptConvert<Color>(src.offDayMarkColor),
        .workDayMarkSize = OptConvert<Dimension>(src.workDayMarkSize),
        .offDayMarkSize = OptConvert<Dimension>(src.offDayMarkSize),
        .workStateWidth = OptConvert<Dimension>(src.workStateWidth),
        .workStateHorizontalMovingDistance = OptConvert<Dimension>(src.workStateHorizontalMovingDistance),
        .workStateVerticalMovingDistance = OptConvert<Dimension>(src.workStateVerticalMovingDistance),
    };
}
} // namespace Converter
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG::GeneratedModifier {
namespace CalendarModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return nullptr;
}
} // CalendarModifier
namespace CalendarInterfaceModifier {
void SetCalendarOptionsImpl(Ark_NativePointer node,
                            const Ark_Type_CalendarInterface_value* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<CalendarData>(*value);
}
} // CalendarInterfaceModifier
namespace CalendarAttributeModifier {
void ShowLunarImpl(Ark_NativePointer node,
                   Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
}
void ShowHolidayImpl(Ark_NativePointer node,
                     Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
}
void NeedSlideImpl(Ark_NativePointer node,
                   Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
}
void StartOfWeekImpl(Ark_NativePointer node,
                     const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<int32_t>(*value);
}
void OffDaysImpl(Ark_NativePointer node,
                 const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = value ? Converter::OptConvert<int32_t>(*value) : std::nullopt;
    Validator::ValidateNonNegative(convValue);
    auto offDays = convValue
        ? std::optional<std::string>(GetDaysIndexes(static_cast<uint32_t>(*convValue)))
        : std::nullopt;
}
void DirectionImpl(Ark_NativePointer node,
                   Ark_Axis value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<Axis>(value);
}
void CurrentDayStyleImpl(Ark_NativePointer node,
                         const Ark_CurrentDayStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<CurrentDayStyleData>(*value);
}
void NonCurrentDayStyleImpl(Ark_NativePointer node,
                            const Ark_NonCurrentDayStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<NonCurrentDayStyleData>(*value);
}
void TodayStyleImpl(Ark_NativePointer node,
                    const Ark_TodayStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<TodayStyleData>(*value);
}
void WeekStyleImpl(Ark_NativePointer node,
                   const Ark_WeekStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<WeekStyleData>(*value);
}
void WorkStateStyleImpl(Ark_NativePointer node,
                        const Ark_WorkStateStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<WorkStateStyleData>(*value);
}
void OnSelectChangeImpl(Ark_NativePointer node,
                        const Callback_CalendarSelectedDate_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onSelectChange = [arkCallback = CallbackHelper(*value)](const std::string& dataStr) {
        const auto json = JsonUtil::ParseJsonString(dataStr);
        arkCallback.Invoke(Ark_CalendarSelectedDate {
            .year = Converter::ArkValue<Ark_Number>(json->GetInt("year")),
            .month = Converter::ArkValue<Ark_Number>(json->GetInt("month")),
            .day = Converter::ArkValue<Ark_Number>(json->GetInt("day")),
        });
    };
}
void OnRequestDataImpl(Ark_NativePointer node,
                       const Callback_CalendarRequestedData_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onRequestData = [arkCallback = CallbackHelper(*value)](const std::string& dataStr) {
        const auto json = JsonUtil::ParseJsonString(dataStr);
        arkCallback.Invoke(Ark_CalendarRequestedData {
            .year = Converter::ArkValue<Ark_Number>(json->GetInt("year")),
            .month = Converter::ArkValue<Ark_Number>(json->GetInt("month")),
            .currentYear = Converter::ArkValue<Ark_Number>(json->GetInt("currentYear")),
            .currentMonth = Converter::ArkValue<Ark_Number>(json->GetInt("currentMonth")),
            .monthState = Converter::ArkValue<Ark_Number>(json->GetInt("MonthState")),
        });
    };
}
} // CalendarAttributeModifier
const GENERATED_ArkUICalendarModifier* GetCalendarModifier()
{
    static const GENERATED_ArkUICalendarModifier ArkUICalendarModifierImpl {
        CalendarModifier::ConstructImpl,
        CalendarInterfaceModifier::SetCalendarOptionsImpl,
        CalendarAttributeModifier::ShowLunarImpl,
        CalendarAttributeModifier::ShowHolidayImpl,
        CalendarAttributeModifier::NeedSlideImpl,
        CalendarAttributeModifier::StartOfWeekImpl,
        CalendarAttributeModifier::OffDaysImpl,
        CalendarAttributeModifier::DirectionImpl,
        CalendarAttributeModifier::CurrentDayStyleImpl,
        CalendarAttributeModifier::NonCurrentDayStyleImpl,
        CalendarAttributeModifier::TodayStyleImpl,
        CalendarAttributeModifier::WeekStyleImpl,
        CalendarAttributeModifier::WorkStateStyleImpl,
        CalendarAttributeModifier::OnSelectChangeImpl,
        CalendarAttributeModifier::OnRequestDataImpl,
    };
    return &ArkUICalendarModifierImpl;
}

}
