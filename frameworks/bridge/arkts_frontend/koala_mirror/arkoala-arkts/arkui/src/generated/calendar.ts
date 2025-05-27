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
import { CallbackTransformer } from "./../CallbackTransformer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { Axis } from "./enums"
import { ResourceColor } from "./units"
import { UICommonBase, AttributeModifier } from "./../handwritten"
import { NodeAttach, remember } from "@koalaui/runtime"
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
    public backToToday(): void {
        this.backToToday_serialize()
        return
    }
    public goTo(value: Literal_Number_day_month_year): void {
        const value_casted = value as (Literal_Number_day_month_year)
        this.goTo_serialize(value_casted)
        return
    }
    private backToToday_serialize(): void {
        ArkUIGeneratedNativeModule._CalendarController_backToToday(this.peer!.ptr)
    }
    private goTo_serialize(value: Literal_Number_day_month_year): void {
        const thisSerializer : Serializer = Serializer.hold()
        const value_year  = value.year
        thisSerializer.writeNumber(value_year)
        const value_month  = value.month
        thisSerializer.writeNumber(value_month)
        const value_day  = value.day
        thisSerializer.writeNumber(value_day)
        ArkUIGeneratedNativeModule._CalendarController_goTo(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export class ArkCalendarPeer extends PeerNode {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkCalendarPeer {
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
    showLunarAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._CalendarAttribute_showLunar(this.peer.ptr, value ? 1 : 0)
    }
    showHolidayAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._CalendarAttribute_showHoliday(this.peer.ptr, value ? 1 : 0)
    }
    needSlideAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._CalendarAttribute_needSlide(this.peer.ptr, value ? 1 : 0)
    }
    startOfWeekAttribute(value: number): void {
        ArkUIGeneratedNativeModule._CalendarAttribute_startOfWeek(this.peer.ptr, value)
    }
    offDaysAttribute(value: number): void {
        ArkUIGeneratedNativeModule._CalendarAttribute_offDays(this.peer.ptr, value)
    }
    directionAttribute(value: Axis): void {
        ArkUIGeneratedNativeModule._CalendarAttribute_direction(this.peer.ptr, TypeChecker.Axis_ToNumeric(value))
    }
    currentDayStyleAttribute(value: CurrentDayStyle): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeCurrentDayStyle(value)
        ArkUIGeneratedNativeModule._CalendarAttribute_currentDayStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    nonCurrentDayStyleAttribute(value: NonCurrentDayStyle): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeNonCurrentDayStyle(value)
        ArkUIGeneratedNativeModule._CalendarAttribute_nonCurrentDayStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    todayStyleAttribute(value: TodayStyle): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeTodayStyle(value)
        ArkUIGeneratedNativeModule._CalendarAttribute_todayStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    weekStyleAttribute(value: WeekStyle): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeWeekStyle(value)
        ArkUIGeneratedNativeModule._CalendarAttribute_weekStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    workStateStyleAttribute(value: WorkStateStyle): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeWorkStateStyle(value)
        ArkUIGeneratedNativeModule._CalendarAttribute_workStateStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onSelectChangeAttribute(value: ((event: CalendarSelectedDate) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._CalendarAttribute_onSelectChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onRequestDataAttribute(value: ((event: CalendarRequestedData) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
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

export type Callback_CalendarSelectedDate_Void = (event: CalendarSelectedDate) => void;
export type Callback_CalendarRequestedData_Void = (event: CalendarRequestedData) => void;
export interface CalendarAttribute {
    showLunar(value: boolean): this
    showHoliday(value: boolean): this
    needSlide(value: boolean): this
    startOfWeek(value: number): this
    offDays(value: number): this
    direction(value: Axis): this
    currentDayStyle(value: CurrentDayStyle): this
    nonCurrentDayStyle(value: NonCurrentDayStyle): this
    todayStyle(value: TodayStyle): this
    weekStyle(value: WeekStyle): this
    workStateStyle(value: WorkStateStyle): this
    onSelectChange(value: ((event: CalendarSelectedDate) => void)): this
    onRequestData(value: ((event: CalendarRequestedData) => void)): this
    attributeModifier(value: AttributeModifier<CalendarAttribute> | undefined): this
}
export interface UICalendarAttribute {
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
    /** @memo */
    attributeModifier(value: AttributeModifier<CalendarAttribute> | undefined): this
}
export class ArkCalendarStyle implements CalendarAttribute {
    showLunar_value?: boolean
    showHoliday_value?: boolean
    needSlide_value?: boolean
    startOfWeek_value?: number
    offDays_value?: number
    direction_value?: Axis
    currentDayStyle_value?: CurrentDayStyle
    nonCurrentDayStyle_value?: NonCurrentDayStyle
    todayStyle_value?: TodayStyle
    weekStyle_value?: WeekStyle
    workStateStyle_value?: WorkStateStyle
    onSelectChange_value?: ((event: CalendarSelectedDate) => void)
    onRequestData_value?: ((event: CalendarRequestedData) => void)
    public showLunar(value: boolean): this {
        return this
    }
    public showHoliday(value: boolean): this {
        return this
    }
    public needSlide(value: boolean): this {
        return this
    }
    public startOfWeek(value: number): this {
        return this
    }
    public offDays(value: number): this {
        return this
    }
    public direction(value: Axis): this {
        return this
    }
    public currentDayStyle(value: CurrentDayStyle): this {
        return this
    }
    public nonCurrentDayStyle(value: NonCurrentDayStyle): this {
        return this
    }
    public todayStyle(value: TodayStyle): this {
        return this
    }
    public weekStyle(value: WeekStyle): this {
        return this
    }
    public workStateStyle(value: WorkStateStyle): this {
        return this
    }
    public onSelectChange(value: ((event: CalendarSelectedDate) => void)): this {
        return this
    }
    public onRequestData(value: ((event: CalendarRequestedData) => void)): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<CalendarAttribute> | undefined): this {
        throw new Error("Not implemented")
    }
}
/** @memo:stable */
export class ArkCalendarComponent extends ComponentBase implements UICalendarAttribute {
    getPeer(): ArkCalendarPeer {
        return (this.peer as ArkCalendarPeer)
    }
    /** @memo */
    public setCalendarOptions(value: Type_CalendarInterface_callable0_value): this {
        if (this.checkPriority("setCalendarOptions")) {
            const value_casted = value as (Type_CalendarInterface_callable0_value)
            this.getPeer()?.setCalendarOptionsAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public showLunar(value: boolean): this {
        if (this.checkPriority("showLunar")) {
            const value_casted = value as (boolean)
            this.getPeer()?.showLunarAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public showHoliday(value: boolean): this {
        if (this.checkPriority("showHoliday")) {
            const value_casted = value as (boolean)
            this.getPeer()?.showHolidayAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public needSlide(value: boolean): this {
        if (this.checkPriority("needSlide")) {
            const value_casted = value as (boolean)
            this.getPeer()?.needSlideAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public startOfWeek(value: number): this {
        if (this.checkPriority("startOfWeek")) {
            const value_casted = value as (number)
            this.getPeer()?.startOfWeekAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public offDays(value: number): this {
        if (this.checkPriority("offDays")) {
            const value_casted = value as (number)
            this.getPeer()?.offDaysAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public direction(value: Axis): this {
        if (this.checkPriority("direction")) {
            const value_casted = value as (Axis)
            this.getPeer()?.directionAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public currentDayStyle(value: CurrentDayStyle): this {
        if (this.checkPriority("currentDayStyle")) {
            const value_casted = value as (CurrentDayStyle)
            this.getPeer()?.currentDayStyleAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public nonCurrentDayStyle(value: NonCurrentDayStyle): this {
        if (this.checkPriority("nonCurrentDayStyle")) {
            const value_casted = value as (NonCurrentDayStyle)
            this.getPeer()?.nonCurrentDayStyleAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public todayStyle(value: TodayStyle): this {
        if (this.checkPriority("todayStyle")) {
            const value_casted = value as (TodayStyle)
            this.getPeer()?.todayStyleAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public weekStyle(value: WeekStyle): this {
        if (this.checkPriority("weekStyle")) {
            const value_casted = value as (WeekStyle)
            this.getPeer()?.weekStyleAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public workStateStyle(value: WorkStateStyle): this {
        if (this.checkPriority("workStateStyle")) {
            const value_casted = value as (WorkStateStyle)
            this.getPeer()?.workStateStyleAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onSelectChange(value: ((event: CalendarSelectedDate) => void)): this {
        if (this.checkPriority("onSelectChange")) {
            const value_casted = value as (((event: CalendarSelectedDate) => void))
            this.getPeer()?.onSelectChangeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onRequestData(value: ((event: CalendarRequestedData) => void)): this {
        if (this.checkPriority("onRequestData")) {
            const value_casted = value as (((event: CalendarRequestedData) => void))
            this.getPeer()?.onRequestDataAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public attributeModifier(value: AttributeModifier<CalendarAttribute> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function ArkCalendar(
    /** @memo */
    style: ((attributes: UICalendarAttribute) => void) | undefined,
    /** @memo */
    content_: (() => void) | undefined,
    value: Type_CalendarInterface_callable0_value,
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
