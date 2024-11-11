/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace CalendarInterfaceModifier {
void SetCalendarOptionsImpl(Ark_NativePointer node,
                            const Ark_Type_CalendarInterface_value* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CalendarModelNG::SetSetCalendarOptions(frameNode, convValue);
}
} // CalendarInterfaceModifier
namespace CalendarAttributeModifier {
void ShowLunarImpl(Ark_NativePointer node,
                   Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    //CalendarModelNG::SetShowLunar(frameNode, convValue);
}
void ShowHolidayImpl(Ark_NativePointer node,
                     Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    //CalendarModelNG::SetShowHoliday(frameNode, convValue);
}
void NeedSlideImpl(Ark_NativePointer node,
                   Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    //CalendarModelNG::SetNeedSlide(frameNode, convValue);
}
void StartOfWeekImpl(Ark_NativePointer node,
                     const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CalendarModelNG::SetStartOfWeek(frameNode, convValue);
}
void OffDaysImpl(Ark_NativePointer node,
                 const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CalendarModelNG::SetOffDays(frameNode, convValue);
}
void DirectionImpl(Ark_NativePointer node,
                   Ark_Axis value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //CalendarModelNG::SetDirection(frameNode, convValue);
}
void CurrentDayStyleImpl(Ark_NativePointer node,
                         const Ark_CurrentDayStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CalendarModelNG::SetCurrentDayStyle(frameNode, convValue);
}
void NonCurrentDayStyleImpl(Ark_NativePointer node,
                            const Ark_NonCurrentDayStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CalendarModelNG::SetNonCurrentDayStyle(frameNode, convValue);
}
void TodayStyleImpl(Ark_NativePointer node,
                    const Ark_TodayStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CalendarModelNG::SetTodayStyle(frameNode, convValue);
}
void WeekStyleImpl(Ark_NativePointer node,
                   const Ark_WeekStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CalendarModelNG::SetWeekStyle(frameNode, convValue);
}
void WorkStateStyleImpl(Ark_NativePointer node,
                        const Ark_WorkStateStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CalendarModelNG::SetWorkStateStyle(frameNode, convValue);
}
void OnSelectChangeImpl(Ark_NativePointer node,
                        const Callback_CalendarSelectedDate_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CalendarModelNG::SetOnSelectChange(frameNode, convValue);
}
void OnRequestDataImpl(Ark_NativePointer node,
                       const Callback_CalendarRequestedData_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CalendarModelNG::SetOnRequestData(frameNode, convValue);
}
} // CalendarAttributeModifier
const GENERATED_ArkUICalendarModifier* GetCalendarModifier()
{
    static const GENERATED_ArkUICalendarModifier ArkUICalendarModifierImpl {
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
