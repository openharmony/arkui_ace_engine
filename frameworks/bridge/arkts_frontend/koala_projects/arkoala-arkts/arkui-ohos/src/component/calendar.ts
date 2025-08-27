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
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { Axis } from "./enums"
import { NodeAttach, remember } from "@koalaui/runtime"
import { ResourceColor } from "./units"
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
export class ArkCalendarPeer extends PeerNode {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkCalendarPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Calendar_construct(peerId, flags)
        const _peer  = new ArkCalendarPeer(_peerPtr, peerId, "Calendar", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setCalendarOptionsAttribute(value: Type_CalendarInterface_callable0_value): void {
        const thisSerializer : Serializer = Serializer.hold()
        const value_date  = value.date
        const value_date_year  = value_date.year
        thisSerializer.writeNumber(value_date_year)
        const value_date_month  = value_date.month
        thisSerializer.writeNumber(value_date_month)
        const value_date_day  = value_date.day
        thisSerializer.writeNumber(value_date_day)
        const value_currentData  = value.currentData
        thisSerializer.writeMonthData(value_currentData)
        const value_preData  = value.preData
        thisSerializer.writeMonthData(value_preData)
        const value_nextData  = value.nextData
        thisSerializer.writeMonthData(value_nextData)
        const value_controller  = value.controller
        let value_controller_type : int32 = RuntimeType.UNDEFINED
        value_controller_type = runtimeType(value_controller)
        thisSerializer.writeInt8(value_controller_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_controller_type)) {
            const value_controller_value  = value_controller!
            thisSerializer.writeCalendarController(value_controller_value)
        }
        ArkUIGeneratedNativeModule._CalendarInterface_setCalendarOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    showLunarAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._CalendarAttribute_showLunar(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    showHolidayAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._CalendarAttribute_showHoliday(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    needSlideAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._CalendarAttribute_needSlide(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    startOfWeekAttribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._CalendarAttribute_startOfWeek(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    offDaysAttribute(value: number | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._CalendarAttribute_offDays(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    directionAttribute(value: Axis | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as Axis)
            thisSerializer.writeInt32(TypeChecker.Axis_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._CalendarAttribute_direction(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    currentDayStyleAttribute(value: CurrentDayStyle | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeCurrentDayStyle(value_value)
        }
        ArkUIGeneratedNativeModule._CalendarAttribute_currentDayStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    nonCurrentDayStyleAttribute(value: NonCurrentDayStyle | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNonCurrentDayStyle(value_value)
        }
        ArkUIGeneratedNativeModule._CalendarAttribute_nonCurrentDayStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    todayStyleAttribute(value: TodayStyle | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeTodayStyle(value_value)
        }
        ArkUIGeneratedNativeModule._CalendarAttribute_todayStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    weekStyleAttribute(value: WeekStyle | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeWeekStyle(value_value)
        }
        ArkUIGeneratedNativeModule._CalendarAttribute_weekStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    workStateStyleAttribute(value: WorkStateStyle | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeWorkStateStyle(value_value)
        }
        ArkUIGeneratedNativeModule._CalendarAttribute_workStateStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onSelectChangeAttribute(value: ((event: CalendarSelectedDate) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._CalendarAttribute_onSelectChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onRequestDataAttribute(value: ((event: CalendarRequestedData) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._CalendarAttribute_onRequestData(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
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
export interface Type_CalendarInterface_callable0_value {
    date: Literal_Number_day_month_year;
    currentData: MonthData;
    preData: MonthData;
    nextData: MonthData;
    controller?: CalendarController;
}
export type CalendarInterface = (value: Type_CalendarInterface_callable0_value) => CalendarAttribute;
export type Callback_CalendarSelectedDate_Void = (event: CalendarSelectedDate) => void;
export type Callback_CalendarRequestedData_Void = (event: CalendarRequestedData) => void;
export interface CalendarAttribute {
    showLunar(value: boolean | undefined): this
    showHoliday(value: boolean | undefined): this
    needSlide(value: boolean | undefined): this
    startOfWeek(value: number | undefined): this
    offDays(value: number | undefined): this
    direction(value: Axis | undefined): this
    currentDayStyle(value: CurrentDayStyle | undefined): this
    nonCurrentDayStyle(value: NonCurrentDayStyle | undefined): this
    todayStyle(value: TodayStyle | undefined): this
    weekStyle(value: WeekStyle | undefined): this
    workStateStyle(value: WorkStateStyle | undefined): this
    onSelectChange(value: ((event: CalendarSelectedDate) => void) | undefined): this
    onRequestData(value: ((event: CalendarRequestedData) => void) | undefined): this
}
export class ArkCalendarStyle implements CalendarAttribute {
    showLunar_value?: boolean | undefined
    showHoliday_value?: boolean | undefined
    needSlide_value?: boolean | undefined
    startOfWeek_value?: number | undefined
    offDays_value?: number | undefined
    direction_value?: Axis | undefined
    currentDayStyle_value?: CurrentDayStyle | undefined
    nonCurrentDayStyle_value?: NonCurrentDayStyle | undefined
    todayStyle_value?: TodayStyle | undefined
    weekStyle_value?: WeekStyle | undefined
    workStateStyle_value?: WorkStateStyle | undefined
    onSelectChange_value?: ((event: CalendarSelectedDate) => void) | undefined
    onRequestData_value?: ((event: CalendarRequestedData) => void) | undefined
    public showLunar(value: boolean | undefined): this {
        return this
    }
    public showHoliday(value: boolean | undefined): this {
        return this
    }
    public needSlide(value: boolean | undefined): this {
        return this
    }
    public startOfWeek(value: number | undefined): this {
        return this
    }
    public offDays(value: number | undefined): this {
        return this
    }
    public direction(value: Axis | undefined): this {
        return this
    }
    public currentDayStyle(value: CurrentDayStyle | undefined): this {
        return this
    }
    public nonCurrentDayStyle(value: NonCurrentDayStyle | undefined): this {
        return this
    }
    public todayStyle(value: TodayStyle | undefined): this {
        return this
    }
    public weekStyle(value: WeekStyle | undefined): this {
        return this
    }
    public workStateStyle(value: WorkStateStyle | undefined): this {
        return this
    }
    public onSelectChange(value: ((event: CalendarSelectedDate) => void) | undefined): this {
        return this
    }
    public onRequestData(value: ((event: CalendarRequestedData) => void) | undefined): this {
        return this
    }
}
export class ArkCalendarComponent extends ComponentBase implements CalendarAttribute {
    getPeer(): ArkCalendarPeer {
        return (this.peer as ArkCalendarPeer)
    }
    public setCalendarOptions(value: Type_CalendarInterface_callable0_value): this {
        if (this.checkPriority("setCalendarOptions")) {
            const value_casted = value as (Type_CalendarInterface_callable0_value)
            this.getPeer()?.setCalendarOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    public showLunar(value: boolean | undefined): this {
        if (this.checkPriority("showLunar")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.showLunarAttribute(value_casted)
            return this
        }
        return this
    }
    public showHoliday(value: boolean | undefined): this {
        if (this.checkPriority("showHoliday")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.showHolidayAttribute(value_casted)
            return this
        }
        return this
    }
    public needSlide(value: boolean | undefined): this {
        if (this.checkPriority("needSlide")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.needSlideAttribute(value_casted)
            return this
        }
        return this
    }
    public startOfWeek(value: number | undefined): this {
        if (this.checkPriority("startOfWeek")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.startOfWeekAttribute(value_casted)
            return this
        }
        return this
    }
    public offDays(value: number | undefined): this {
        if (this.checkPriority("offDays")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.offDaysAttribute(value_casted)
            return this
        }
        return this
    }
    public direction(value: Axis | undefined): this {
        if (this.checkPriority("direction")) {
            const value_casted = value as (Axis | undefined)
            this.getPeer()?.directionAttribute(value_casted)
            return this
        }
        return this
    }
    public currentDayStyle(value: CurrentDayStyle | undefined): this {
        if (this.checkPriority("currentDayStyle")) {
            const value_casted = value as (CurrentDayStyle | undefined)
            this.getPeer()?.currentDayStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public nonCurrentDayStyle(value: NonCurrentDayStyle | undefined): this {
        if (this.checkPriority("nonCurrentDayStyle")) {
            const value_casted = value as (NonCurrentDayStyle | undefined)
            this.getPeer()?.nonCurrentDayStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public todayStyle(value: TodayStyle | undefined): this {
        if (this.checkPriority("todayStyle")) {
            const value_casted = value as (TodayStyle | undefined)
            this.getPeer()?.todayStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public weekStyle(value: WeekStyle | undefined): this {
        if (this.checkPriority("weekStyle")) {
            const value_casted = value as (WeekStyle | undefined)
            this.getPeer()?.weekStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public workStateStyle(value: WorkStateStyle | undefined): this {
        if (this.checkPriority("workStateStyle")) {
            const value_casted = value as (WorkStateStyle | undefined)
            this.getPeer()?.workStateStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public onSelectChange(value: ((event: CalendarSelectedDate) => void) | undefined): this {
        if (this.checkPriority("onSelectChange")) {
            const value_casted = value as (((event: CalendarSelectedDate) => void) | undefined)
            this.getPeer()?.onSelectChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public onRequestData(value: ((event: CalendarRequestedData) => void) | undefined): this {
        if (this.checkPriority("onRequestData")) {
            const value_casted = value as (((event: CalendarRequestedData) => void) | undefined)
            this.getPeer()?.onRequestDataAttribute(value_casted)
            return this
        }
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function Calendar(
    /** @memo */
    style: ((attributes: CalendarAttribute) => void) | undefined,
    value: Type_CalendarInterface_callable0_value,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
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
