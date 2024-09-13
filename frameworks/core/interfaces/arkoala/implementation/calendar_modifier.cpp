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

#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace CalendarInterfaceModifier {
void SetCalendarOptionsImpl(Ark_NativePointer node,
                            const Type_CalendarInterface_setCalendarOptions_Arg0* value)
{
}
} // CalendarInterfaceModifier
namespace CalendarAttributeModifier {
void ShowLunarImpl(Ark_NativePointer node,
                   Ark_Boolean value)
{
}
void ShowHolidayImpl(Ark_NativePointer node,
                     Ark_Boolean value)
{
}
void NeedSlideImpl(Ark_NativePointer node,
                   Ark_Boolean value)
{
}
void StartOfWeekImpl(Ark_NativePointer node,
                     const Ark_Number* value)
{
}
void OffDaysImpl(Ark_NativePointer node,
                 const Ark_Number* value)
{
}
void DirectionImpl(Ark_NativePointer node,
                   enum Ark_Axis value)
{
}
void CurrentDayStyleImpl(Ark_NativePointer node,
                         const Ark_CurrentDayStyle* value)
{
}
void NonCurrentDayStyleImpl(Ark_NativePointer node,
                            const Ark_NonCurrentDayStyle* value)
{
}
void TodayStyleImpl(Ark_NativePointer node,
                    const Ark_TodayStyle* value)
{
}
void WeekStyleImpl(Ark_NativePointer node,
                   const Ark_WeekStyle* value)
{
}
void WorkStateStyleImpl(Ark_NativePointer node,
                        const Ark_WorkStateStyle* value)
{
}
void OnSelectChangeImpl(Ark_NativePointer node,
                        Ark_Function event)
{
}
void OnRequestDataImpl(Ark_NativePointer node,
                       Ark_Function event)
{
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
