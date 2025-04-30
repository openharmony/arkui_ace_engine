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
                            const Ark_Type_CalendarInterface_callable0_value* value)
{
}
} // CalendarInterfaceModifier
namespace CalendarAttributeModifier {
void ShowLunarImpl(Ark_NativePointer node,
                   const Opt_Boolean* value)
{
}
void ShowHolidayImpl(Ark_NativePointer node,
                     const Opt_Boolean* value)
{
}
void NeedSlideImpl(Ark_NativePointer node,
                   const Opt_Boolean* value)
{
}
void StartOfWeekImpl(Ark_NativePointer node,
                     const Opt_Number* value)
{
}
void OffDaysImpl(Ark_NativePointer node,
                 const Opt_Number* value)
{
}
void DirectionImpl(Ark_NativePointer node,
                   const Opt_Axis* value)
{
}
void CurrentDayStyleImpl(Ark_NativePointer node,
                         const Opt_CurrentDayStyle* value)
{
}
void NonCurrentDayStyleImpl(Ark_NativePointer node,
                            const Opt_NonCurrentDayStyle* value)
{
}
void TodayStyleImpl(Ark_NativePointer node,
                    const Opt_TodayStyle* value)
{
}
void WeekStyleImpl(Ark_NativePointer node,
                   const Opt_WeekStyle* value)
{
}
void WorkStateStyleImpl(Ark_NativePointer node,
                        const Opt_WorkStateStyle* value)
{
}
void OnSelectChangeImpl(Ark_NativePointer node,
                        const Opt_Callback_CalendarSelectedDate_Void* value)
{
}
void OnRequestDataImpl(Ark_NativePointer node,
                       const Opt_Callback_CalendarRequestedData_Void* value)
{
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
