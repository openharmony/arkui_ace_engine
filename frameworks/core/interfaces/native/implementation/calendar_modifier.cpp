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

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace CalendarModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // CalendarModifier
namespace CalendarInterfaceModifier {
void SetCalendarOptionsImpl(Ark_NativePointer node,
                            const Ark_CalendarRequestedMonths* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //CalendarModelNG::SetSetCalendarOptions(frameNode, convValue);
}
} // CalendarInterfaceModifier
namespace CalendarAttributeModifier {
void SetShowLunarImpl(Ark_NativePointer node,
                      const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CalendarModelNG::SetSetShowLunar(frameNode, convValue);
}
void SetShowHolidayImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CalendarModelNG::SetSetShowHoliday(frameNode, convValue);
}
void SetNeedSlideImpl(Ark_NativePointer node,
                      const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CalendarModelNG::SetSetNeedSlide(frameNode, convValue);
}
void SetStartOfWeekImpl(Ark_NativePointer node,
                        const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CalendarModelNG::SetSetStartOfWeek(frameNode, convValue);
}
void SetOffDaysImpl(Ark_NativePointer node,
                    const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CalendarModelNG::SetSetOffDays(frameNode, convValue);
}
void SetDirectionImpl(Ark_NativePointer node,
                      const Opt_Axis* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CalendarModelNG::SetSetDirection(frameNode, convValue);
}
void SetCurrentDayStyleImpl(Ark_NativePointer node,
                            const Opt_CurrentDayStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CalendarModelNG::SetSetCurrentDayStyle(frameNode, convValue);
}
void SetNonCurrentDayStyleImpl(Ark_NativePointer node,
                               const Opt_NonCurrentDayStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CalendarModelNG::SetSetNonCurrentDayStyle(frameNode, convValue);
}
void SetTodayStyleImpl(Ark_NativePointer node,
                       const Opt_TodayStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CalendarModelNG::SetSetTodayStyle(frameNode, convValue);
}
void SetWeekStyleImpl(Ark_NativePointer node,
                      const Opt_WeekStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CalendarModelNG::SetSetWeekStyle(frameNode, convValue);
}
void SetWorkStateStyleImpl(Ark_NativePointer node,
                           const Opt_WorkStateStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CalendarModelNG::SetSetWorkStateStyle(frameNode, convValue);
}
void SetOnSelectChangeImpl(Ark_NativePointer node,
                           const Opt_Callback_CalendarSelectedDate_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CalendarModelNG::SetSetOnSelectChange(frameNode, convValue);
}
void SetOnRequestDataImpl(Ark_NativePointer node,
                          const Opt_Callback_CalendarRequestedData_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //CalendarModelNG::SetSetOnRequestData(frameNode, convValue);
}
} // CalendarAttributeModifier
const GENERATED_ArkUICalendarModifier* GetCalendarModifier()
{
    static const GENERATED_ArkUICalendarModifier ArkUICalendarModifierImpl {
        CalendarModifier::ConstructImpl,
        CalendarInterfaceModifier::SetCalendarOptionsImpl,
        CalendarAttributeModifier::SetShowLunarImpl,
        CalendarAttributeModifier::SetShowHolidayImpl,
        CalendarAttributeModifier::SetNeedSlideImpl,
        CalendarAttributeModifier::SetStartOfWeekImpl,
        CalendarAttributeModifier::SetOffDaysImpl,
        CalendarAttributeModifier::SetDirectionImpl,
        CalendarAttributeModifier::SetCurrentDayStyleImpl,
        CalendarAttributeModifier::SetNonCurrentDayStyleImpl,
        CalendarAttributeModifier::SetTodayStyleImpl,
        CalendarAttributeModifier::SetWeekStyleImpl,
        CalendarAttributeModifier::SetWorkStateStyleImpl,
        CalendarAttributeModifier::SetOnSelectChangeImpl,
        CalendarAttributeModifier::SetOnRequestDataImpl,
    };
    return &ArkUICalendarModifierImpl;
}

}
