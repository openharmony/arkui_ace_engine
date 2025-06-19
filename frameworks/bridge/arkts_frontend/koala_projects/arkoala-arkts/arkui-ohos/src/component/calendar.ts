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


// WARNING! THIS FILE IS AUTO-GENERATED, DO NOT MAKE CHANGES, THEY WILL BE LOST ON NEXT GENERATION!

import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, float32, int64 } from "@koalaui/common"
import { Serializer } from "./../generated/peers/Serializer"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { Deserializer } from "./../generated/peers/Deserializer"
import { CallbackTransformer } from "./../generated/peers/CallbackTransformer"
import { NodeAttach, remember } from "@koalaui/runtime"
import { ResourceColor } from "./units"
import { Axis } from "./enums"
import { ArkCalendarComponent } from "./../generated/ArkCalendar"
import { ArkCalendarPeer } from "./../generated/peers/ArkCalendarPeer"
export class CalendarControllerInternal {
    public static fromPtr(ptr: KPointer): CalendarController {
        const obj : CalendarController = new CalendarController()
        obj.peer = new Finalizable(ptr, CalendarController.getFinalizer())
        return obj
    }
}
export class CalendarController implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_calendarcontroller(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._CalendarController_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = CalendarController.ctor_calendarcontroller()
        this.peer = new Finalizable(ctorPtr, CalendarController.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._CalendarController_getFinalizer()
    }
    public backToToday(): undefined {
        return this.backToToday_serialize()
    }
    public goTo(value: Literal_Number_day_month_year): undefined {
        const value_casted = value as (Literal_Number_day_month_year)
        return this.goTo_serialize(value_casted)
    }
    private backToToday_serialize(): undefined {
        const retval  = ArkUIGeneratedNativeModule._CalendarController_backToToday(this.peer!.ptr)
        return retval
    }
    private goTo_serialize(value: Literal_Number_day_month_year): undefined {
        const thisSerializer : Serializer = Serializer.hold()
        const value_year  = value.year
        thisSerializer.writeNumber(value_year)
        const value_month  = value.month
        thisSerializer.writeNumber(value_month)
        const value_day  = value.day
        thisSerializer.writeNumber(value_day)
        const retval  = ArkUIGeneratedNativeModule._CalendarController_goTo(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
}
export interface CalendarDay {
    index: number;
    lunarMonth: string;
    lunarDay: string;
    dayMark: string;
    dayMarkValue: string;
    year: number;
    month: number;
    day: number;
    isFirstOfLunar: boolean;
    hasSchedule: boolean;
    markLunarDay: boolean;
}
export interface MonthData {
    year: number;
    month: number;
    data: Array<CalendarDay>;
}
export interface CurrentDayStyle {
    dayColor?: ResourceColor;
    lunarColor?: ResourceColor;
    markLunarColor?: ResourceColor;
    dayFontSize?: number;
    lunarDayFontSize?: number;
    dayHeight?: number;
    dayWidth?: number;
    gregorianCalendarHeight?: number;
    dayYAxisOffset?: number;
    lunarDayYAxisOffset?: number;
    underscoreXAxisOffset?: number;
    underscoreYAxisOffset?: number;
    scheduleMarkerXAxisOffset?: number;
    scheduleMarkerYAxisOffset?: number;
    colSpace?: number;
    dailyFiveRowSpace?: number;
    dailySixRowSpace?: number;
    lunarHeight?: number;
    underscoreWidth?: number;
    underscoreLength?: number;
    scheduleMarkerRadius?: number;
    boundaryRowOffset?: number;
    boundaryColOffset?: number;
}
export interface NonCurrentDayStyle {
    nonCurrentMonthDayColor?: ResourceColor;
    nonCurrentMonthLunarColor?: ResourceColor;
    nonCurrentMonthWorkDayMarkColor?: ResourceColor;
    nonCurrentMonthOffDayMarkColor?: ResourceColor;
}
export interface TodayStyle {
    focusedDayColor?: ResourceColor;
    focusedLunarColor?: ResourceColor;
    focusedAreaBackgroundColor?: ResourceColor;
    focusedAreaRadius?: number;
}
export interface WeekStyle {
    weekColor?: ResourceColor;
    weekendDayColor?: ResourceColor;
    weekendLunarColor?: ResourceColor;
    weekFontSize?: number;
    weekHeight?: number;
    weekWidth?: number;
    weekAndDayRowSpace?: number;
}
export interface WorkStateStyle {
    workDayMarkColor?: ResourceColor;
    offDayMarkColor?: ResourceColor;
    workDayMarkSize?: number;
    offDayMarkSize?: number;
    workStateWidth?: number;
    workStateHorizontalMovingDistance?: number;
    workStateVerticalMovingDistance?: number;
}
export interface CalendarSelectedDate {
    year: number;
    month: number;
    day: number;
}
export interface CalendarRequestedData {
    year: number;
    month: number;
    currentYear: number;
    currentMonth: number;
    monthState: number;
}
export interface Literal_Number_day_month_year {
    year: number;
    month: number;
    day: number;
}
export interface Type_CalendarInterface_value {
    date: Literal_Number_day_month_year;
    currentData: MonthData;
    preData: MonthData;
    nextData: MonthData;
    controller?: CalendarController;
}
export type Callback_CalendarSelectedDate_Void = (event: CalendarSelectedDate) => void;
export type Callback_CalendarRequestedData_Void = (event: CalendarRequestedData) => void;
/** @memo:stable */
export interface CalendarAttribute {
    /** @memo */
    setCalendarOptions(value: Type_CalendarInterface_value): this
    /** @memo */
    showLunar(value: boolean): this
    /** @memo */
    showHoliday(value: boolean): this
    /** @memo */
    needSlide(value: boolean): this
    /** @memo */
    startOfWeek(value: number): this
    /** @memo */
    offDays(value: number): this
    /** @memo */
    direction(value: Axis): this
    /** @memo */
    currentDayStyle(value: CurrentDayStyle): this
    /** @memo */
    nonCurrentDayStyle(value: NonCurrentDayStyle): this
    /** @memo */
    todayStyle(value: TodayStyle): this
    /** @memo */
    weekStyle(value: WeekStyle): this
    /** @memo */
    workStateStyle(value: WorkStateStyle): this
    /** @memo */
    onSelectChange(value: ((event: CalendarSelectedDate) => void)): this
    /** @memo */
    onRequestData(value: ((event: CalendarRequestedData) => void)): this
}
/** @memo */
export function Calendar(
  /** @memo */
  style: ((attributes: CalendarAttribute) => void) | undefined,
  value: Type_CalendarInterface_value, 
  /** @memo */
  content_?: () => void,
) {
    const receiver = remember(() => {
        return new ArkCalendarComponent()
    })
    NodeAttach<ArkCalendarPeer>((): ArkCalendarPeer => ArkCalendarPeer.create(receiver), (_: ArkCalendarPeer) => {
        receiver.setCalendarOptions(value)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}
