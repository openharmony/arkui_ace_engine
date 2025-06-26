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

import { SerializerBase, DeserializerBase, Finalizable, runtimeType, RuntimeType, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr, CallbackResource, InteropNativeModule, Tags, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { Axis, Color } from "./enums"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
import { ResourceColor } from "./units"
import { Resource, Resource_serializer } from "./resource"
import { UICommonBase, AttributeModifier, AttributeUpdater } from "./../handwritten"
import { NodeAttach, remember } from "@koalaui/runtime"
export class CalendarControllerInternal {
    public static fromPtr(ptr: KPointer): CalendarController {
        return new CalendarController(ptr)
    }
}
export class CalendarController implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    constructor(peerPtr: KPointer) {
        this.peer = new Finalizable(peerPtr, CalendarController.getFinalizer())
    }
    static ctor(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._CalendarController_ctor()
        return retval
    }
    constructor() {
        this(CalendarController.ctor())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._CalendarController_getFinalizer()
    }
    public backToToday(): void {
        this.backToToday_serialize()
        return
    }
    public goTo(date: CalendarSelectedDate): void {
        const date_casted = date as (CalendarSelectedDate)
        this.goTo_serialize(date_casted)
        return
    }
    private backToToday_serialize(): void {
        ArkUIGeneratedNativeModule._CalendarController_backToToday(this.peer!.ptr)
    }
    private goTo_serialize(date: CalendarSelectedDate): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        CalendarSelectedDate_serializer.write(thisSerializer, date)
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
    setCalendarOptionsAttribute(value: CalendarRequestedMonths): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        CalendarRequestedMonths_serializer.write(thisSerializer, value)
        ArkUIGeneratedNativeModule._CalendarInterface_setCalendarOptions(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    showLunarAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._CalendarAttribute_showLunar(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    showHolidayAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._CalendarAttribute_showHoliday(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    needSlideAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._CalendarAttribute_needSlide(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    startOfWeekAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._CalendarAttribute_startOfWeek(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    offDaysAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._CalendarAttribute_offDays(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    directionAttribute(value: Axis | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as Axis)
            thisSerializer.writeInt32(TypeChecker.Axis_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._CalendarAttribute_direction(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    currentDayStyleAttribute(value: CurrentDayStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            CurrentDayStyle_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._CalendarAttribute_currentDayStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    nonCurrentDayStyleAttribute(value: NonCurrentDayStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            NonCurrentDayStyle_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._CalendarAttribute_nonCurrentDayStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    todayStyleAttribute(value: TodayStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            TodayStyle_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._CalendarAttribute_todayStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    weekStyleAttribute(value: WeekStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            WeekStyle_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._CalendarAttribute_weekStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    workStateStyleAttribute(value: WorkStateStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            WorkStateStyle_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._CalendarAttribute_workStateStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onSelectChangeAttribute(value: ((event: CalendarSelectedDate) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._CalendarAttribute_onSelectChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onRequestDataAttribute(value: ((event: CalendarRequestedData) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type)
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
export interface DateOptions {
    year: number;
    month: number;
    day: number;
}
export interface CalendarRequestedMonths {
    date: CalendarSelectedDate;
    currentData: MonthData;
    preData: MonthData;
    nextData: MonthData;
    controller?: CalendarController;
}
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
    attributeModifier(value: AttributeModifier<CalendarAttribute> | undefined): this
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
    public attributeModifier(value: AttributeModifier<CalendarAttribute> | undefined): this {
        throw new Error("Not implemented")
    }
    public apply(target: CalendarAttribute): void {
        if (this.showLunar_value !== undefined)
            target.showLunar(this.showLunar_value!)
        if (this.showHoliday_value !== undefined)
            target.showHoliday(this.showHoliday_value!)
        if (this.needSlide_value !== undefined)
            target.needSlide(this.needSlide_value!)
        if (this.startOfWeek_value !== undefined)
            target.startOfWeek(this.startOfWeek_value!)
        if (this.offDays_value !== undefined)
            target.offDays(this.offDays_value!)
        if (this.direction_value !== undefined)
            target.direction(this.direction_value!)
        if (this.currentDayStyle_value !== undefined)
            target.currentDayStyle(this.currentDayStyle_value!)
        if (this.nonCurrentDayStyle_value !== undefined)
            target.nonCurrentDayStyle(this.nonCurrentDayStyle_value!)
        if (this.todayStyle_value !== undefined)
            target.todayStyle(this.todayStyle_value!)
        if (this.weekStyle_value !== undefined)
            target.weekStyle(this.weekStyle_value!)
        if (this.workStateStyle_value !== undefined)
            target.workStateStyle(this.workStateStyle_value!)
        if (this.onSelectChange_value !== undefined)
            target.onSelectChange(this.onSelectChange_value!)
        if (this.onRequestData_value !== undefined)
            target.onRequestData(this.onRequestData_value!)
    }
}

export class ArkCalendarComponent extends ComponentBase implements CalendarAttribute {
    getPeer(): ArkCalendarPeer {
        return (this.peer as ArkCalendarPeer)
    }
    public setCalendarOptions(value: CalendarRequestedMonths): this {
        if (this.checkPriority("setCalendarOptions")) {
            const value_casted = value as (CalendarRequestedMonths)
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
    _modifier?: AttributeModifier<CalendarAttribute> | undefined
    public attributeModifier(value: AttributeModifier<CalendarAttribute> | undefined): this {
        this._modifier = value
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
export function withCalendarStyle(receiver: CalendarAttribute, modifier: AttributeModifier<CalendarAttribute> | undefined): void {
    if (modifier !== undefined)
    {
        let style  = new ArkCalendarStyle()
        if (modifier!.isUpdater)
            (modifier! as AttributeUpdater<CalendarAttribute>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CalendarAttribute>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
@memo
@BuilderLambda("CalendarImpl")
export function Calendar(
    value: CalendarRequestedMonths,
    @memo
    content_?: () => void,
): CalendarAttribute {
    throw new Error("Not implemented")
}

@memo
export function CalendarImpl(
    @memo
    style: ((attributes: CalendarAttribute) => void) | undefined,
    value: CalendarRequestedMonths,
    @memo
    content_?: () => void,
): void {
    const receiver = remember<ArkCalendarComponent>((): ArkCalendarComponent => {
        return new ArkCalendarComponent()
    })
    NodeAttach<ArkCalendarPeer>((): ArkCalendarPeer => ArkCalendarPeer.create(receiver), (_: ArkCalendarPeer): void => {
        receiver.setCalendarOptions(value)
        style?.(receiver)
        withCalendarStyle(receiver, receiver._modifier)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

export class CalendarController_serializer {
    public static write(buffer: SerializerBase, value: CalendarController): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): CalendarController {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return CalendarControllerInternal.fromPtr(ptr)
    }
}
export class CalendarDay_serializer {
    public static write(buffer: SerializerBase, value: CalendarDay): void {
        let valueSerializer : SerializerBase = buffer
        const value_index  = value.index
        valueSerializer.writeNumber(value_index)
        const value_lunarMonth  = value.lunarMonth
        valueSerializer.writeString(value_lunarMonth)
        const value_lunarDay  = value.lunarDay
        valueSerializer.writeString(value_lunarDay)
        const value_dayMark  = value.dayMark
        valueSerializer.writeString(value_dayMark)
        const value_dayMarkValue  = value.dayMarkValue
        valueSerializer.writeString(value_dayMarkValue)
        const value_year  = value.year
        valueSerializer.writeNumber(value_year)
        const value_month  = value.month
        valueSerializer.writeNumber(value_month)
        const value_day  = value.day
        valueSerializer.writeNumber(value_day)
        const value_isFirstOfLunar  = value.isFirstOfLunar
        valueSerializer.writeBoolean(value_isFirstOfLunar)
        const value_hasSchedule  = value.hasSchedule
        valueSerializer.writeBoolean(value_hasSchedule)
        const value_markLunarDay  = value.markLunarDay
        valueSerializer.writeBoolean(value_markLunarDay)
    }
    public static read(buffer: DeserializerBase): CalendarDay {
        let valueDeserializer : DeserializerBase = buffer
        const index_result : number = (valueDeserializer.readNumber() as number)
        const lunarMonth_result : string = (valueDeserializer.readString() as string)
        const lunarDay_result : string = (valueDeserializer.readString() as string)
        const dayMark_result : string = (valueDeserializer.readString() as string)
        const dayMarkValue_result : string = (valueDeserializer.readString() as string)
        const year_result : number = (valueDeserializer.readNumber() as number)
        const month_result : number = (valueDeserializer.readNumber() as number)
        const day_result : number = (valueDeserializer.readNumber() as number)
        const isFirstOfLunar_result : boolean = valueDeserializer.readBoolean()
        const hasSchedule_result : boolean = valueDeserializer.readBoolean()
        const markLunarDay_result : boolean = valueDeserializer.readBoolean()
        let value : CalendarDay = ({index: index_result, lunarMonth: lunarMonth_result, lunarDay: lunarDay_result, dayMark: dayMark_result, dayMarkValue: dayMarkValue_result, year: year_result, month: month_result, day: day_result, isFirstOfLunar: isFirstOfLunar_result, hasSchedule: hasSchedule_result, markLunarDay: markLunarDay_result} as CalendarDay)
        return value
    }
}
export class CalendarRequestedData_serializer {
    public static write(buffer: SerializerBase, value: CalendarRequestedData): void {
        let valueSerializer : SerializerBase = buffer
        const value_year  = value.year
        valueSerializer.writeNumber(value_year)
        const value_month  = value.month
        valueSerializer.writeNumber(value_month)
        const value_currentYear  = value.currentYear
        valueSerializer.writeNumber(value_currentYear)
        const value_currentMonth  = value.currentMonth
        valueSerializer.writeNumber(value_currentMonth)
        const value_monthState  = value.monthState
        valueSerializer.writeNumber(value_monthState)
    }
    public static read(buffer: DeserializerBase): CalendarRequestedData {
        let valueDeserializer : DeserializerBase = buffer
        const year_result : number = (valueDeserializer.readNumber() as number)
        const month_result : number = (valueDeserializer.readNumber() as number)
        const currentYear_result : number = (valueDeserializer.readNumber() as number)
        const currentMonth_result : number = (valueDeserializer.readNumber() as number)
        const monthState_result : number = (valueDeserializer.readNumber() as number)
        let value : CalendarRequestedData = ({year: year_result, month: month_result, currentYear: currentYear_result, currentMonth: currentMonth_result, monthState: monthState_result} as CalendarRequestedData)
        return value
    }
}
export class CalendarSelectedDate_serializer {
    public static write(buffer: SerializerBase, value: CalendarSelectedDate): void {
        let valueSerializer : SerializerBase = buffer
        const value_year  = value.year
        valueSerializer.writeNumber(value_year)
        const value_month  = value.month
        valueSerializer.writeNumber(value_month)
        const value_day  = value.day
        valueSerializer.writeNumber(value_day)
    }
    public static read(buffer: DeserializerBase): CalendarSelectedDate {
        let valueDeserializer : DeserializerBase = buffer
        const year_result : number = (valueDeserializer.readNumber() as number)
        const month_result : number = (valueDeserializer.readNumber() as number)
        const day_result : number = (valueDeserializer.readNumber() as number)
        let value : CalendarSelectedDate = ({year: year_result, month: month_result, day: day_result} as CalendarSelectedDate)
        return value
    }
}
export class MonthData_serializer {
    public static write(buffer: SerializerBase, value: MonthData): void {
        let valueSerializer : SerializerBase = buffer
        const value_year  = value.year
        valueSerializer.writeNumber(value_year)
        const value_month  = value.month
        valueSerializer.writeNumber(value_month)
        const value_data  = value.data
        valueSerializer.writeInt32(value_data.length as int32)
        for (let i = 0; i < value_data.length; i++) {
            const value_data_element : CalendarDay = value_data[i]
            CalendarDay_serializer.write(valueSerializer, value_data_element)
        }
    }
    public static read(buffer: DeserializerBase): MonthData {
        let valueDeserializer : DeserializerBase = buffer
        const year_result : number = (valueDeserializer.readNumber() as number)
        const month_result : number = (valueDeserializer.readNumber() as number)
        const data_buf_length : int32 = valueDeserializer.readInt32()
        let data_buf : Array<CalendarDay> = new Array<CalendarDay>(data_buf_length)
        for (let data_buf_i = 0; data_buf_i < data_buf_length; data_buf_i++) {
            data_buf[data_buf_i] = CalendarDay_serializer.read(valueDeserializer)
        }
        const data_result : Array<CalendarDay> = data_buf
        let value : MonthData = ({year: year_result, month: month_result, data: data_result} as MonthData)
        return value
    }
}
export class CalendarRequestedMonths_serializer {
    public static write(buffer: SerializerBase, value: CalendarRequestedMonths): void {
        let valueSerializer : SerializerBase = buffer
        const value_date  = value.date
        CalendarSelectedDate_serializer.write(valueSerializer, value_date)
        const value_currentData  = value.currentData
        MonthData_serializer.write(valueSerializer, value_currentData)
        const value_preData  = value.preData
        MonthData_serializer.write(valueSerializer, value_preData)
        const value_nextData  = value.nextData
        MonthData_serializer.write(valueSerializer, value_nextData)
        const value_controller  = value.controller
        let value_controller_type : int32 = RuntimeType.UNDEFINED
        value_controller_type = runtimeType(value_controller)
        valueSerializer.writeInt8(value_controller_type)
        if ((RuntimeType.UNDEFINED) != (value_controller_type)) {
            const value_controller_value  = value_controller!
            CalendarController_serializer.write(valueSerializer, value_controller_value)
        }
    }
    public static read(buffer: DeserializerBase): CalendarRequestedMonths {
        let valueDeserializer : DeserializerBase = buffer
        const date_result : CalendarSelectedDate = CalendarSelectedDate_serializer.read(valueDeserializer)
        const currentData_result : MonthData = MonthData_serializer.read(valueDeserializer)
        const preData_result : MonthData = MonthData_serializer.read(valueDeserializer)
        const nextData_result : MonthData = MonthData_serializer.read(valueDeserializer)
        const controller_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let controller_buf : CalendarController | undefined
        if ((RuntimeType.UNDEFINED) != (controller_buf_runtimeType))
        {
            controller_buf = (CalendarController_serializer.read(valueDeserializer) as CalendarController)
        }
        const controller_result : CalendarController | undefined = controller_buf
        let value : CalendarRequestedMonths = ({date: date_result, currentData: currentData_result, preData: preData_result, nextData: nextData_result, controller: controller_result} as CalendarRequestedMonths)
        return value
    }
}
export class CurrentDayStyle_serializer {
    public static write(buffer: SerializerBase, value: CurrentDayStyle): void {
        let valueSerializer : SerializerBase = buffer
        const value_dayColor  = value.dayColor
        let value_dayColor_type : int32 = RuntimeType.UNDEFINED
        value_dayColor_type = runtimeType(value_dayColor)
        valueSerializer.writeInt8(value_dayColor_type)
        if ((RuntimeType.UNDEFINED) != (value_dayColor_type)) {
            const value_dayColor_value  = value_dayColor!
            let value_dayColor_value_type : int32 = RuntimeType.UNDEFINED
            value_dayColor_value_type = runtimeType(value_dayColor_value)
            if (TypeChecker.isColor(value_dayColor_value)) {
                valueSerializer.writeInt8(0)
                const value_dayColor_value_0  = value_dayColor_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_dayColor_value_0))
            }
            else if (RuntimeType.NUMBER == value_dayColor_value_type) {
                valueSerializer.writeInt8(1)
                const value_dayColor_value_1  = value_dayColor_value as number
                valueSerializer.writeNumber(value_dayColor_value_1)
            }
            else if (RuntimeType.STRING == value_dayColor_value_type) {
                valueSerializer.writeInt8(2)
                const value_dayColor_value_2  = value_dayColor_value as string
                valueSerializer.writeString(value_dayColor_value_2)
            }
            else if (RuntimeType.OBJECT == value_dayColor_value_type) {
                valueSerializer.writeInt8(3)
                const value_dayColor_value_3  = value_dayColor_value as Resource
                Resource_serializer.write(valueSerializer, value_dayColor_value_3)
            }
        }
        const value_lunarColor  = value.lunarColor
        let value_lunarColor_type : int32 = RuntimeType.UNDEFINED
        value_lunarColor_type = runtimeType(value_lunarColor)
        valueSerializer.writeInt8(value_lunarColor_type)
        if ((RuntimeType.UNDEFINED) != (value_lunarColor_type)) {
            const value_lunarColor_value  = value_lunarColor!
            let value_lunarColor_value_type : int32 = RuntimeType.UNDEFINED
            value_lunarColor_value_type = runtimeType(value_lunarColor_value)
            if (TypeChecker.isColor(value_lunarColor_value)) {
                valueSerializer.writeInt8(0)
                const value_lunarColor_value_0  = value_lunarColor_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_lunarColor_value_0))
            }
            else if (RuntimeType.NUMBER == value_lunarColor_value_type) {
                valueSerializer.writeInt8(1)
                const value_lunarColor_value_1  = value_lunarColor_value as number
                valueSerializer.writeNumber(value_lunarColor_value_1)
            }
            else if (RuntimeType.STRING == value_lunarColor_value_type) {
                valueSerializer.writeInt8(2)
                const value_lunarColor_value_2  = value_lunarColor_value as string
                valueSerializer.writeString(value_lunarColor_value_2)
            }
            else if (RuntimeType.OBJECT == value_lunarColor_value_type) {
                valueSerializer.writeInt8(3)
                const value_lunarColor_value_3  = value_lunarColor_value as Resource
                Resource_serializer.write(valueSerializer, value_lunarColor_value_3)
            }
        }
        const value_markLunarColor  = value.markLunarColor
        let value_markLunarColor_type : int32 = RuntimeType.UNDEFINED
        value_markLunarColor_type = runtimeType(value_markLunarColor)
        valueSerializer.writeInt8(value_markLunarColor_type)
        if ((RuntimeType.UNDEFINED) != (value_markLunarColor_type)) {
            const value_markLunarColor_value  = value_markLunarColor!
            let value_markLunarColor_value_type : int32 = RuntimeType.UNDEFINED
            value_markLunarColor_value_type = runtimeType(value_markLunarColor_value)
            if (TypeChecker.isColor(value_markLunarColor_value)) {
                valueSerializer.writeInt8(0)
                const value_markLunarColor_value_0  = value_markLunarColor_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_markLunarColor_value_0))
            }
            else if (RuntimeType.NUMBER == value_markLunarColor_value_type) {
                valueSerializer.writeInt8(1)
                const value_markLunarColor_value_1  = value_markLunarColor_value as number
                valueSerializer.writeNumber(value_markLunarColor_value_1)
            }
            else if (RuntimeType.STRING == value_markLunarColor_value_type) {
                valueSerializer.writeInt8(2)
                const value_markLunarColor_value_2  = value_markLunarColor_value as string
                valueSerializer.writeString(value_markLunarColor_value_2)
            }
            else if (RuntimeType.OBJECT == value_markLunarColor_value_type) {
                valueSerializer.writeInt8(3)
                const value_markLunarColor_value_3  = value_markLunarColor_value as Resource
                Resource_serializer.write(valueSerializer, value_markLunarColor_value_3)
            }
        }
        const value_dayFontSize  = value.dayFontSize
        let value_dayFontSize_type : int32 = RuntimeType.UNDEFINED
        value_dayFontSize_type = runtimeType(value_dayFontSize)
        valueSerializer.writeInt8(value_dayFontSize_type)
        if ((RuntimeType.UNDEFINED) != (value_dayFontSize_type)) {
            const value_dayFontSize_value  = value_dayFontSize!
            valueSerializer.writeNumber(value_dayFontSize_value)
        }
        const value_lunarDayFontSize  = value.lunarDayFontSize
        let value_lunarDayFontSize_type : int32 = RuntimeType.UNDEFINED
        value_lunarDayFontSize_type = runtimeType(value_lunarDayFontSize)
        valueSerializer.writeInt8(value_lunarDayFontSize_type)
        if ((RuntimeType.UNDEFINED) != (value_lunarDayFontSize_type)) {
            const value_lunarDayFontSize_value  = value_lunarDayFontSize!
            valueSerializer.writeNumber(value_lunarDayFontSize_value)
        }
        const value_dayHeight  = value.dayHeight
        let value_dayHeight_type : int32 = RuntimeType.UNDEFINED
        value_dayHeight_type = runtimeType(value_dayHeight)
        valueSerializer.writeInt8(value_dayHeight_type)
        if ((RuntimeType.UNDEFINED) != (value_dayHeight_type)) {
            const value_dayHeight_value  = value_dayHeight!
            valueSerializer.writeNumber(value_dayHeight_value)
        }
        const value_dayWidth  = value.dayWidth
        let value_dayWidth_type : int32 = RuntimeType.UNDEFINED
        value_dayWidth_type = runtimeType(value_dayWidth)
        valueSerializer.writeInt8(value_dayWidth_type)
        if ((RuntimeType.UNDEFINED) != (value_dayWidth_type)) {
            const value_dayWidth_value  = value_dayWidth!
            valueSerializer.writeNumber(value_dayWidth_value)
        }
        const value_gregorianCalendarHeight  = value.gregorianCalendarHeight
        let value_gregorianCalendarHeight_type : int32 = RuntimeType.UNDEFINED
        value_gregorianCalendarHeight_type = runtimeType(value_gregorianCalendarHeight)
        valueSerializer.writeInt8(value_gregorianCalendarHeight_type)
        if ((RuntimeType.UNDEFINED) != (value_gregorianCalendarHeight_type)) {
            const value_gregorianCalendarHeight_value  = value_gregorianCalendarHeight!
            valueSerializer.writeNumber(value_gregorianCalendarHeight_value)
        }
        const value_dayYAxisOffset  = value.dayYAxisOffset
        let value_dayYAxisOffset_type : int32 = RuntimeType.UNDEFINED
        value_dayYAxisOffset_type = runtimeType(value_dayYAxisOffset)
        valueSerializer.writeInt8(value_dayYAxisOffset_type)
        if ((RuntimeType.UNDEFINED) != (value_dayYAxisOffset_type)) {
            const value_dayYAxisOffset_value  = value_dayYAxisOffset!
            valueSerializer.writeNumber(value_dayYAxisOffset_value)
        }
        const value_lunarDayYAxisOffset  = value.lunarDayYAxisOffset
        let value_lunarDayYAxisOffset_type : int32 = RuntimeType.UNDEFINED
        value_lunarDayYAxisOffset_type = runtimeType(value_lunarDayYAxisOffset)
        valueSerializer.writeInt8(value_lunarDayYAxisOffset_type)
        if ((RuntimeType.UNDEFINED) != (value_lunarDayYAxisOffset_type)) {
            const value_lunarDayYAxisOffset_value  = value_lunarDayYAxisOffset!
            valueSerializer.writeNumber(value_lunarDayYAxisOffset_value)
        }
        const value_underscoreXAxisOffset  = value.underscoreXAxisOffset
        let value_underscoreXAxisOffset_type : int32 = RuntimeType.UNDEFINED
        value_underscoreXAxisOffset_type = runtimeType(value_underscoreXAxisOffset)
        valueSerializer.writeInt8(value_underscoreXAxisOffset_type)
        if ((RuntimeType.UNDEFINED) != (value_underscoreXAxisOffset_type)) {
            const value_underscoreXAxisOffset_value  = value_underscoreXAxisOffset!
            valueSerializer.writeNumber(value_underscoreXAxisOffset_value)
        }
        const value_underscoreYAxisOffset  = value.underscoreYAxisOffset
        let value_underscoreYAxisOffset_type : int32 = RuntimeType.UNDEFINED
        value_underscoreYAxisOffset_type = runtimeType(value_underscoreYAxisOffset)
        valueSerializer.writeInt8(value_underscoreYAxisOffset_type)
        if ((RuntimeType.UNDEFINED) != (value_underscoreYAxisOffset_type)) {
            const value_underscoreYAxisOffset_value  = value_underscoreYAxisOffset!
            valueSerializer.writeNumber(value_underscoreYAxisOffset_value)
        }
        const value_scheduleMarkerXAxisOffset  = value.scheduleMarkerXAxisOffset
        let value_scheduleMarkerXAxisOffset_type : int32 = RuntimeType.UNDEFINED
        value_scheduleMarkerXAxisOffset_type = runtimeType(value_scheduleMarkerXAxisOffset)
        valueSerializer.writeInt8(value_scheduleMarkerXAxisOffset_type)
        if ((RuntimeType.UNDEFINED) != (value_scheduleMarkerXAxisOffset_type)) {
            const value_scheduleMarkerXAxisOffset_value  = value_scheduleMarkerXAxisOffset!
            valueSerializer.writeNumber(value_scheduleMarkerXAxisOffset_value)
        }
        const value_scheduleMarkerYAxisOffset  = value.scheduleMarkerYAxisOffset
        let value_scheduleMarkerYAxisOffset_type : int32 = RuntimeType.UNDEFINED
        value_scheduleMarkerYAxisOffset_type = runtimeType(value_scheduleMarkerYAxisOffset)
        valueSerializer.writeInt8(value_scheduleMarkerYAxisOffset_type)
        if ((RuntimeType.UNDEFINED) != (value_scheduleMarkerYAxisOffset_type)) {
            const value_scheduleMarkerYAxisOffset_value  = value_scheduleMarkerYAxisOffset!
            valueSerializer.writeNumber(value_scheduleMarkerYAxisOffset_value)
        }
        const value_colSpace  = value.colSpace
        let value_colSpace_type : int32 = RuntimeType.UNDEFINED
        value_colSpace_type = runtimeType(value_colSpace)
        valueSerializer.writeInt8(value_colSpace_type)
        if ((RuntimeType.UNDEFINED) != (value_colSpace_type)) {
            const value_colSpace_value  = value_colSpace!
            valueSerializer.writeNumber(value_colSpace_value)
        }
        const value_dailyFiveRowSpace  = value.dailyFiveRowSpace
        let value_dailyFiveRowSpace_type : int32 = RuntimeType.UNDEFINED
        value_dailyFiveRowSpace_type = runtimeType(value_dailyFiveRowSpace)
        valueSerializer.writeInt8(value_dailyFiveRowSpace_type)
        if ((RuntimeType.UNDEFINED) != (value_dailyFiveRowSpace_type)) {
            const value_dailyFiveRowSpace_value  = value_dailyFiveRowSpace!
            valueSerializer.writeNumber(value_dailyFiveRowSpace_value)
        }
        const value_dailySixRowSpace  = value.dailySixRowSpace
        let value_dailySixRowSpace_type : int32 = RuntimeType.UNDEFINED
        value_dailySixRowSpace_type = runtimeType(value_dailySixRowSpace)
        valueSerializer.writeInt8(value_dailySixRowSpace_type)
        if ((RuntimeType.UNDEFINED) != (value_dailySixRowSpace_type)) {
            const value_dailySixRowSpace_value  = value_dailySixRowSpace!
            valueSerializer.writeNumber(value_dailySixRowSpace_value)
        }
        const value_lunarHeight  = value.lunarHeight
        let value_lunarHeight_type : int32 = RuntimeType.UNDEFINED
        value_lunarHeight_type = runtimeType(value_lunarHeight)
        valueSerializer.writeInt8(value_lunarHeight_type)
        if ((RuntimeType.UNDEFINED) != (value_lunarHeight_type)) {
            const value_lunarHeight_value  = value_lunarHeight!
            valueSerializer.writeNumber(value_lunarHeight_value)
        }
        const value_underscoreWidth  = value.underscoreWidth
        let value_underscoreWidth_type : int32 = RuntimeType.UNDEFINED
        value_underscoreWidth_type = runtimeType(value_underscoreWidth)
        valueSerializer.writeInt8(value_underscoreWidth_type)
        if ((RuntimeType.UNDEFINED) != (value_underscoreWidth_type)) {
            const value_underscoreWidth_value  = value_underscoreWidth!
            valueSerializer.writeNumber(value_underscoreWidth_value)
        }
        const value_underscoreLength  = value.underscoreLength
        let value_underscoreLength_type : int32 = RuntimeType.UNDEFINED
        value_underscoreLength_type = runtimeType(value_underscoreLength)
        valueSerializer.writeInt8(value_underscoreLength_type)
        if ((RuntimeType.UNDEFINED) != (value_underscoreLength_type)) {
            const value_underscoreLength_value  = value_underscoreLength!
            valueSerializer.writeNumber(value_underscoreLength_value)
        }
        const value_scheduleMarkerRadius  = value.scheduleMarkerRadius
        let value_scheduleMarkerRadius_type : int32 = RuntimeType.UNDEFINED
        value_scheduleMarkerRadius_type = runtimeType(value_scheduleMarkerRadius)
        valueSerializer.writeInt8(value_scheduleMarkerRadius_type)
        if ((RuntimeType.UNDEFINED) != (value_scheduleMarkerRadius_type)) {
            const value_scheduleMarkerRadius_value  = value_scheduleMarkerRadius!
            valueSerializer.writeNumber(value_scheduleMarkerRadius_value)
        }
        const value_boundaryRowOffset  = value.boundaryRowOffset
        let value_boundaryRowOffset_type : int32 = RuntimeType.UNDEFINED
        value_boundaryRowOffset_type = runtimeType(value_boundaryRowOffset)
        valueSerializer.writeInt8(value_boundaryRowOffset_type)
        if ((RuntimeType.UNDEFINED) != (value_boundaryRowOffset_type)) {
            const value_boundaryRowOffset_value  = value_boundaryRowOffset!
            valueSerializer.writeNumber(value_boundaryRowOffset_value)
        }
        const value_boundaryColOffset  = value.boundaryColOffset
        let value_boundaryColOffset_type : int32 = RuntimeType.UNDEFINED
        value_boundaryColOffset_type = runtimeType(value_boundaryColOffset)
        valueSerializer.writeInt8(value_boundaryColOffset_type)
        if ((RuntimeType.UNDEFINED) != (value_boundaryColOffset_type)) {
            const value_boundaryColOffset_value  = value_boundaryColOffset!
            valueSerializer.writeNumber(value_boundaryColOffset_value)
        }
    }
    public static read(buffer: DeserializerBase): CurrentDayStyle {
        let valueDeserializer : DeserializerBase = buffer
        const dayColor_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let dayColor_buf : ResourceColor | undefined
        if ((RuntimeType.UNDEFINED) != (dayColor_buf_runtimeType))
        {
            const dayColor_buf__selector : int32 = valueDeserializer.readInt8()
            let dayColor_buf_ : Color | number | string | Resource | undefined
            if (dayColor_buf__selector == 0) {
                dayColor_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (dayColor_buf__selector == 1) {
                dayColor_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (dayColor_buf__selector == 2) {
                dayColor_buf_ = (valueDeserializer.readString() as string)
            }
            else if (dayColor_buf__selector == 3) {
                dayColor_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for dayColor_buf_ has to be chosen through deserialisation.")
            }
            dayColor_buf = (dayColor_buf_ as Color | number | string | Resource)
        }
        const dayColor_result : ResourceColor | undefined = dayColor_buf
        const lunarColor_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let lunarColor_buf : ResourceColor | undefined
        if ((RuntimeType.UNDEFINED) != (lunarColor_buf_runtimeType))
        {
            const lunarColor_buf__selector : int32 = valueDeserializer.readInt8()
            let lunarColor_buf_ : Color | number | string | Resource | undefined
            if (lunarColor_buf__selector == 0) {
                lunarColor_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (lunarColor_buf__selector == 1) {
                lunarColor_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (lunarColor_buf__selector == 2) {
                lunarColor_buf_ = (valueDeserializer.readString() as string)
            }
            else if (lunarColor_buf__selector == 3) {
                lunarColor_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for lunarColor_buf_ has to be chosen through deserialisation.")
            }
            lunarColor_buf = (lunarColor_buf_ as Color | number | string | Resource)
        }
        const lunarColor_result : ResourceColor | undefined = lunarColor_buf
        const markLunarColor_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let markLunarColor_buf : ResourceColor | undefined
        if ((RuntimeType.UNDEFINED) != (markLunarColor_buf_runtimeType))
        {
            const markLunarColor_buf__selector : int32 = valueDeserializer.readInt8()
            let markLunarColor_buf_ : Color | number | string | Resource | undefined
            if (markLunarColor_buf__selector == 0) {
                markLunarColor_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (markLunarColor_buf__selector == 1) {
                markLunarColor_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (markLunarColor_buf__selector == 2) {
                markLunarColor_buf_ = (valueDeserializer.readString() as string)
            }
            else if (markLunarColor_buf__selector == 3) {
                markLunarColor_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for markLunarColor_buf_ has to be chosen through deserialisation.")
            }
            markLunarColor_buf = (markLunarColor_buf_ as Color | number | string | Resource)
        }
        const markLunarColor_result : ResourceColor | undefined = markLunarColor_buf
        const dayFontSize_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let dayFontSize_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (dayFontSize_buf_runtimeType))
        {
            dayFontSize_buf = (valueDeserializer.readNumber() as number)
        }
        const dayFontSize_result : number | undefined = dayFontSize_buf
        const lunarDayFontSize_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let lunarDayFontSize_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (lunarDayFontSize_buf_runtimeType))
        {
            lunarDayFontSize_buf = (valueDeserializer.readNumber() as number)
        }
        const lunarDayFontSize_result : number | undefined = lunarDayFontSize_buf
        const dayHeight_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let dayHeight_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (dayHeight_buf_runtimeType))
        {
            dayHeight_buf = (valueDeserializer.readNumber() as number)
        }
        const dayHeight_result : number | undefined = dayHeight_buf
        const dayWidth_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let dayWidth_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (dayWidth_buf_runtimeType))
        {
            dayWidth_buf = (valueDeserializer.readNumber() as number)
        }
        const dayWidth_result : number | undefined = dayWidth_buf
        const gregorianCalendarHeight_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let gregorianCalendarHeight_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (gregorianCalendarHeight_buf_runtimeType))
        {
            gregorianCalendarHeight_buf = (valueDeserializer.readNumber() as number)
        }
        const gregorianCalendarHeight_result : number | undefined = gregorianCalendarHeight_buf
        const dayYAxisOffset_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let dayYAxisOffset_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (dayYAxisOffset_buf_runtimeType))
        {
            dayYAxisOffset_buf = (valueDeserializer.readNumber() as number)
        }
        const dayYAxisOffset_result : number | undefined = dayYAxisOffset_buf
        const lunarDayYAxisOffset_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let lunarDayYAxisOffset_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (lunarDayYAxisOffset_buf_runtimeType))
        {
            lunarDayYAxisOffset_buf = (valueDeserializer.readNumber() as number)
        }
        const lunarDayYAxisOffset_result : number | undefined = lunarDayYAxisOffset_buf
        const underscoreXAxisOffset_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let underscoreXAxisOffset_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (underscoreXAxisOffset_buf_runtimeType))
        {
            underscoreXAxisOffset_buf = (valueDeserializer.readNumber() as number)
        }
        const underscoreXAxisOffset_result : number | undefined = underscoreXAxisOffset_buf
        const underscoreYAxisOffset_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let underscoreYAxisOffset_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (underscoreYAxisOffset_buf_runtimeType))
        {
            underscoreYAxisOffset_buf = (valueDeserializer.readNumber() as number)
        }
        const underscoreYAxisOffset_result : number | undefined = underscoreYAxisOffset_buf
        const scheduleMarkerXAxisOffset_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let scheduleMarkerXAxisOffset_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (scheduleMarkerXAxisOffset_buf_runtimeType))
        {
            scheduleMarkerXAxisOffset_buf = (valueDeserializer.readNumber() as number)
        }
        const scheduleMarkerXAxisOffset_result : number | undefined = scheduleMarkerXAxisOffset_buf
        const scheduleMarkerYAxisOffset_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let scheduleMarkerYAxisOffset_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (scheduleMarkerYAxisOffset_buf_runtimeType))
        {
            scheduleMarkerYAxisOffset_buf = (valueDeserializer.readNumber() as number)
        }
        const scheduleMarkerYAxisOffset_result : number | undefined = scheduleMarkerYAxisOffset_buf
        const colSpace_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let colSpace_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (colSpace_buf_runtimeType))
        {
            colSpace_buf = (valueDeserializer.readNumber() as number)
        }
        const colSpace_result : number | undefined = colSpace_buf
        const dailyFiveRowSpace_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let dailyFiveRowSpace_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (dailyFiveRowSpace_buf_runtimeType))
        {
            dailyFiveRowSpace_buf = (valueDeserializer.readNumber() as number)
        }
        const dailyFiveRowSpace_result : number | undefined = dailyFiveRowSpace_buf
        const dailySixRowSpace_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let dailySixRowSpace_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (dailySixRowSpace_buf_runtimeType))
        {
            dailySixRowSpace_buf = (valueDeserializer.readNumber() as number)
        }
        const dailySixRowSpace_result : number | undefined = dailySixRowSpace_buf
        const lunarHeight_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let lunarHeight_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (lunarHeight_buf_runtimeType))
        {
            lunarHeight_buf = (valueDeserializer.readNumber() as number)
        }
        const lunarHeight_result : number | undefined = lunarHeight_buf
        const underscoreWidth_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let underscoreWidth_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (underscoreWidth_buf_runtimeType))
        {
            underscoreWidth_buf = (valueDeserializer.readNumber() as number)
        }
        const underscoreWidth_result : number | undefined = underscoreWidth_buf
        const underscoreLength_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let underscoreLength_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (underscoreLength_buf_runtimeType))
        {
            underscoreLength_buf = (valueDeserializer.readNumber() as number)
        }
        const underscoreLength_result : number | undefined = underscoreLength_buf
        const scheduleMarkerRadius_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let scheduleMarkerRadius_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (scheduleMarkerRadius_buf_runtimeType))
        {
            scheduleMarkerRadius_buf = (valueDeserializer.readNumber() as number)
        }
        const scheduleMarkerRadius_result : number | undefined = scheduleMarkerRadius_buf
        const boundaryRowOffset_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let boundaryRowOffset_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (boundaryRowOffset_buf_runtimeType))
        {
            boundaryRowOffset_buf = (valueDeserializer.readNumber() as number)
        }
        const boundaryRowOffset_result : number | undefined = boundaryRowOffset_buf
        const boundaryColOffset_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let boundaryColOffset_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (boundaryColOffset_buf_runtimeType))
        {
            boundaryColOffset_buf = (valueDeserializer.readNumber() as number)
        }
        const boundaryColOffset_result : number | undefined = boundaryColOffset_buf
        let value : CurrentDayStyle = ({dayColor: dayColor_result, lunarColor: lunarColor_result, markLunarColor: markLunarColor_result, dayFontSize: dayFontSize_result, lunarDayFontSize: lunarDayFontSize_result, dayHeight: dayHeight_result, dayWidth: dayWidth_result, gregorianCalendarHeight: gregorianCalendarHeight_result, dayYAxisOffset: dayYAxisOffset_result, lunarDayYAxisOffset: lunarDayYAxisOffset_result, underscoreXAxisOffset: underscoreXAxisOffset_result, underscoreYAxisOffset: underscoreYAxisOffset_result, scheduleMarkerXAxisOffset: scheduleMarkerXAxisOffset_result, scheduleMarkerYAxisOffset: scheduleMarkerYAxisOffset_result, colSpace: colSpace_result, dailyFiveRowSpace: dailyFiveRowSpace_result, dailySixRowSpace: dailySixRowSpace_result, lunarHeight: lunarHeight_result, underscoreWidth: underscoreWidth_result, underscoreLength: underscoreLength_result, scheduleMarkerRadius: scheduleMarkerRadius_result, boundaryRowOffset: boundaryRowOffset_result, boundaryColOffset: boundaryColOffset_result} as CurrentDayStyle)
        return value
    }
}
export class NonCurrentDayStyle_serializer {
    public static write(buffer: SerializerBase, value: NonCurrentDayStyle): void {
        let valueSerializer : SerializerBase = buffer
        const value_nonCurrentMonthDayColor  = value.nonCurrentMonthDayColor
        let value_nonCurrentMonthDayColor_type : int32 = RuntimeType.UNDEFINED
        value_nonCurrentMonthDayColor_type = runtimeType(value_nonCurrentMonthDayColor)
        valueSerializer.writeInt8(value_nonCurrentMonthDayColor_type)
        if ((RuntimeType.UNDEFINED) != (value_nonCurrentMonthDayColor_type)) {
            const value_nonCurrentMonthDayColor_value  = value_nonCurrentMonthDayColor!
            let value_nonCurrentMonthDayColor_value_type : int32 = RuntimeType.UNDEFINED
            value_nonCurrentMonthDayColor_value_type = runtimeType(value_nonCurrentMonthDayColor_value)
            if (TypeChecker.isColor(value_nonCurrentMonthDayColor_value)) {
                valueSerializer.writeInt8(0)
                const value_nonCurrentMonthDayColor_value_0  = value_nonCurrentMonthDayColor_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_nonCurrentMonthDayColor_value_0))
            }
            else if (RuntimeType.NUMBER == value_nonCurrentMonthDayColor_value_type) {
                valueSerializer.writeInt8(1)
                const value_nonCurrentMonthDayColor_value_1  = value_nonCurrentMonthDayColor_value as number
                valueSerializer.writeNumber(value_nonCurrentMonthDayColor_value_1)
            }
            else if (RuntimeType.STRING == value_nonCurrentMonthDayColor_value_type) {
                valueSerializer.writeInt8(2)
                const value_nonCurrentMonthDayColor_value_2  = value_nonCurrentMonthDayColor_value as string
                valueSerializer.writeString(value_nonCurrentMonthDayColor_value_2)
            }
            else if (RuntimeType.OBJECT == value_nonCurrentMonthDayColor_value_type) {
                valueSerializer.writeInt8(3)
                const value_nonCurrentMonthDayColor_value_3  = value_nonCurrentMonthDayColor_value as Resource
                Resource_serializer.write(valueSerializer, value_nonCurrentMonthDayColor_value_3)
            }
        }
        const value_nonCurrentMonthLunarColor  = value.nonCurrentMonthLunarColor
        let value_nonCurrentMonthLunarColor_type : int32 = RuntimeType.UNDEFINED
        value_nonCurrentMonthLunarColor_type = runtimeType(value_nonCurrentMonthLunarColor)
        valueSerializer.writeInt8(value_nonCurrentMonthLunarColor_type)
        if ((RuntimeType.UNDEFINED) != (value_nonCurrentMonthLunarColor_type)) {
            const value_nonCurrentMonthLunarColor_value  = value_nonCurrentMonthLunarColor!
            let value_nonCurrentMonthLunarColor_value_type : int32 = RuntimeType.UNDEFINED
            value_nonCurrentMonthLunarColor_value_type = runtimeType(value_nonCurrentMonthLunarColor_value)
            if (TypeChecker.isColor(value_nonCurrentMonthLunarColor_value)) {
                valueSerializer.writeInt8(0)
                const value_nonCurrentMonthLunarColor_value_0  = value_nonCurrentMonthLunarColor_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_nonCurrentMonthLunarColor_value_0))
            }
            else if (RuntimeType.NUMBER == value_nonCurrentMonthLunarColor_value_type) {
                valueSerializer.writeInt8(1)
                const value_nonCurrentMonthLunarColor_value_1  = value_nonCurrentMonthLunarColor_value as number
                valueSerializer.writeNumber(value_nonCurrentMonthLunarColor_value_1)
            }
            else if (RuntimeType.STRING == value_nonCurrentMonthLunarColor_value_type) {
                valueSerializer.writeInt8(2)
                const value_nonCurrentMonthLunarColor_value_2  = value_nonCurrentMonthLunarColor_value as string
                valueSerializer.writeString(value_nonCurrentMonthLunarColor_value_2)
            }
            else if (RuntimeType.OBJECT == value_nonCurrentMonthLunarColor_value_type) {
                valueSerializer.writeInt8(3)
                const value_nonCurrentMonthLunarColor_value_3  = value_nonCurrentMonthLunarColor_value as Resource
                Resource_serializer.write(valueSerializer, value_nonCurrentMonthLunarColor_value_3)
            }
        }
        const value_nonCurrentMonthWorkDayMarkColor  = value.nonCurrentMonthWorkDayMarkColor
        let value_nonCurrentMonthWorkDayMarkColor_type : int32 = RuntimeType.UNDEFINED
        value_nonCurrentMonthWorkDayMarkColor_type = runtimeType(value_nonCurrentMonthWorkDayMarkColor)
        valueSerializer.writeInt8(value_nonCurrentMonthWorkDayMarkColor_type)
        if ((RuntimeType.UNDEFINED) != (value_nonCurrentMonthWorkDayMarkColor_type)) {
            const value_nonCurrentMonthWorkDayMarkColor_value  = value_nonCurrentMonthWorkDayMarkColor!
            let value_nonCurrentMonthWorkDayMarkColor_value_type : int32 = RuntimeType.UNDEFINED
            value_nonCurrentMonthWorkDayMarkColor_value_type = runtimeType(value_nonCurrentMonthWorkDayMarkColor_value)
            if (TypeChecker.isColor(value_nonCurrentMonthWorkDayMarkColor_value)) {
                valueSerializer.writeInt8(0)
                const value_nonCurrentMonthWorkDayMarkColor_value_0  = value_nonCurrentMonthWorkDayMarkColor_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_nonCurrentMonthWorkDayMarkColor_value_0))
            }
            else if (RuntimeType.NUMBER == value_nonCurrentMonthWorkDayMarkColor_value_type) {
                valueSerializer.writeInt8(1)
                const value_nonCurrentMonthWorkDayMarkColor_value_1  = value_nonCurrentMonthWorkDayMarkColor_value as number
                valueSerializer.writeNumber(value_nonCurrentMonthWorkDayMarkColor_value_1)
            }
            else if (RuntimeType.STRING == value_nonCurrentMonthWorkDayMarkColor_value_type) {
                valueSerializer.writeInt8(2)
                const value_nonCurrentMonthWorkDayMarkColor_value_2  = value_nonCurrentMonthWorkDayMarkColor_value as string
                valueSerializer.writeString(value_nonCurrentMonthWorkDayMarkColor_value_2)
            }
            else if (RuntimeType.OBJECT == value_nonCurrentMonthWorkDayMarkColor_value_type) {
                valueSerializer.writeInt8(3)
                const value_nonCurrentMonthWorkDayMarkColor_value_3  = value_nonCurrentMonthWorkDayMarkColor_value as Resource
                Resource_serializer.write(valueSerializer, value_nonCurrentMonthWorkDayMarkColor_value_3)
            }
        }
        const value_nonCurrentMonthOffDayMarkColor  = value.nonCurrentMonthOffDayMarkColor
        let value_nonCurrentMonthOffDayMarkColor_type : int32 = RuntimeType.UNDEFINED
        value_nonCurrentMonthOffDayMarkColor_type = runtimeType(value_nonCurrentMonthOffDayMarkColor)
        valueSerializer.writeInt8(value_nonCurrentMonthOffDayMarkColor_type)
        if ((RuntimeType.UNDEFINED) != (value_nonCurrentMonthOffDayMarkColor_type)) {
            const value_nonCurrentMonthOffDayMarkColor_value  = value_nonCurrentMonthOffDayMarkColor!
            let value_nonCurrentMonthOffDayMarkColor_value_type : int32 = RuntimeType.UNDEFINED
            value_nonCurrentMonthOffDayMarkColor_value_type = runtimeType(value_nonCurrentMonthOffDayMarkColor_value)
            if (TypeChecker.isColor(value_nonCurrentMonthOffDayMarkColor_value)) {
                valueSerializer.writeInt8(0)
                const value_nonCurrentMonthOffDayMarkColor_value_0  = value_nonCurrentMonthOffDayMarkColor_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_nonCurrentMonthOffDayMarkColor_value_0))
            }
            else if (RuntimeType.NUMBER == value_nonCurrentMonthOffDayMarkColor_value_type) {
                valueSerializer.writeInt8(1)
                const value_nonCurrentMonthOffDayMarkColor_value_1  = value_nonCurrentMonthOffDayMarkColor_value as number
                valueSerializer.writeNumber(value_nonCurrentMonthOffDayMarkColor_value_1)
            }
            else if (RuntimeType.STRING == value_nonCurrentMonthOffDayMarkColor_value_type) {
                valueSerializer.writeInt8(2)
                const value_nonCurrentMonthOffDayMarkColor_value_2  = value_nonCurrentMonthOffDayMarkColor_value as string
                valueSerializer.writeString(value_nonCurrentMonthOffDayMarkColor_value_2)
            }
            else if (RuntimeType.OBJECT == value_nonCurrentMonthOffDayMarkColor_value_type) {
                valueSerializer.writeInt8(3)
                const value_nonCurrentMonthOffDayMarkColor_value_3  = value_nonCurrentMonthOffDayMarkColor_value as Resource
                Resource_serializer.write(valueSerializer, value_nonCurrentMonthOffDayMarkColor_value_3)
            }
        }
    }
    public static read(buffer: DeserializerBase): NonCurrentDayStyle {
        let valueDeserializer : DeserializerBase = buffer
        const nonCurrentMonthDayColor_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let nonCurrentMonthDayColor_buf : ResourceColor | undefined
        if ((RuntimeType.UNDEFINED) != (nonCurrentMonthDayColor_buf_runtimeType))
        {
            const nonCurrentMonthDayColor_buf__selector : int32 = valueDeserializer.readInt8()
            let nonCurrentMonthDayColor_buf_ : Color | number | string | Resource | undefined
            if (nonCurrentMonthDayColor_buf__selector == 0) {
                nonCurrentMonthDayColor_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (nonCurrentMonthDayColor_buf__selector == 1) {
                nonCurrentMonthDayColor_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (nonCurrentMonthDayColor_buf__selector == 2) {
                nonCurrentMonthDayColor_buf_ = (valueDeserializer.readString() as string)
            }
            else if (nonCurrentMonthDayColor_buf__selector == 3) {
                nonCurrentMonthDayColor_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for nonCurrentMonthDayColor_buf_ has to be chosen through deserialisation.")
            }
            nonCurrentMonthDayColor_buf = (nonCurrentMonthDayColor_buf_ as Color | number | string | Resource)
        }
        const nonCurrentMonthDayColor_result : ResourceColor | undefined = nonCurrentMonthDayColor_buf
        const nonCurrentMonthLunarColor_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let nonCurrentMonthLunarColor_buf : ResourceColor | undefined
        if ((RuntimeType.UNDEFINED) != (nonCurrentMonthLunarColor_buf_runtimeType))
        {
            const nonCurrentMonthLunarColor_buf__selector : int32 = valueDeserializer.readInt8()
            let nonCurrentMonthLunarColor_buf_ : Color | number | string | Resource | undefined
            if (nonCurrentMonthLunarColor_buf__selector == 0) {
                nonCurrentMonthLunarColor_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (nonCurrentMonthLunarColor_buf__selector == 1) {
                nonCurrentMonthLunarColor_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (nonCurrentMonthLunarColor_buf__selector == 2) {
                nonCurrentMonthLunarColor_buf_ = (valueDeserializer.readString() as string)
            }
            else if (nonCurrentMonthLunarColor_buf__selector == 3) {
                nonCurrentMonthLunarColor_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for nonCurrentMonthLunarColor_buf_ has to be chosen through deserialisation.")
            }
            nonCurrentMonthLunarColor_buf = (nonCurrentMonthLunarColor_buf_ as Color | number | string | Resource)
        }
        const nonCurrentMonthLunarColor_result : ResourceColor | undefined = nonCurrentMonthLunarColor_buf
        const nonCurrentMonthWorkDayMarkColor_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let nonCurrentMonthWorkDayMarkColor_buf : ResourceColor | undefined
        if ((RuntimeType.UNDEFINED) != (nonCurrentMonthWorkDayMarkColor_buf_runtimeType))
        {
            const nonCurrentMonthWorkDayMarkColor_buf__selector : int32 = valueDeserializer.readInt8()
            let nonCurrentMonthWorkDayMarkColor_buf_ : Color | number | string | Resource | undefined
            if (nonCurrentMonthWorkDayMarkColor_buf__selector == 0) {
                nonCurrentMonthWorkDayMarkColor_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (nonCurrentMonthWorkDayMarkColor_buf__selector == 1) {
                nonCurrentMonthWorkDayMarkColor_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (nonCurrentMonthWorkDayMarkColor_buf__selector == 2) {
                nonCurrentMonthWorkDayMarkColor_buf_ = (valueDeserializer.readString() as string)
            }
            else if (nonCurrentMonthWorkDayMarkColor_buf__selector == 3) {
                nonCurrentMonthWorkDayMarkColor_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for nonCurrentMonthWorkDayMarkColor_buf_ has to be chosen through deserialisation.")
            }
            nonCurrentMonthWorkDayMarkColor_buf = (nonCurrentMonthWorkDayMarkColor_buf_ as Color | number | string | Resource)
        }
        const nonCurrentMonthWorkDayMarkColor_result : ResourceColor | undefined = nonCurrentMonthWorkDayMarkColor_buf
        const nonCurrentMonthOffDayMarkColor_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let nonCurrentMonthOffDayMarkColor_buf : ResourceColor | undefined
        if ((RuntimeType.UNDEFINED) != (nonCurrentMonthOffDayMarkColor_buf_runtimeType))
        {
            const nonCurrentMonthOffDayMarkColor_buf__selector : int32 = valueDeserializer.readInt8()
            let nonCurrentMonthOffDayMarkColor_buf_ : Color | number | string | Resource | undefined
            if (nonCurrentMonthOffDayMarkColor_buf__selector == 0) {
                nonCurrentMonthOffDayMarkColor_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (nonCurrentMonthOffDayMarkColor_buf__selector == 1) {
                nonCurrentMonthOffDayMarkColor_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (nonCurrentMonthOffDayMarkColor_buf__selector == 2) {
                nonCurrentMonthOffDayMarkColor_buf_ = (valueDeserializer.readString() as string)
            }
            else if (nonCurrentMonthOffDayMarkColor_buf__selector == 3) {
                nonCurrentMonthOffDayMarkColor_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for nonCurrentMonthOffDayMarkColor_buf_ has to be chosen through deserialisation.")
            }
            nonCurrentMonthOffDayMarkColor_buf = (nonCurrentMonthOffDayMarkColor_buf_ as Color | number | string | Resource)
        }
        const nonCurrentMonthOffDayMarkColor_result : ResourceColor | undefined = nonCurrentMonthOffDayMarkColor_buf
        let value : NonCurrentDayStyle = ({nonCurrentMonthDayColor: nonCurrentMonthDayColor_result, nonCurrentMonthLunarColor: nonCurrentMonthLunarColor_result, nonCurrentMonthWorkDayMarkColor: nonCurrentMonthWorkDayMarkColor_result, nonCurrentMonthOffDayMarkColor: nonCurrentMonthOffDayMarkColor_result} as NonCurrentDayStyle)
        return value
    }
}
export class TodayStyle_serializer {
    public static write(buffer: SerializerBase, value: TodayStyle): void {
        let valueSerializer : SerializerBase = buffer
        const value_focusedDayColor  = value.focusedDayColor
        let value_focusedDayColor_type : int32 = RuntimeType.UNDEFINED
        value_focusedDayColor_type = runtimeType(value_focusedDayColor)
        valueSerializer.writeInt8(value_focusedDayColor_type)
        if ((RuntimeType.UNDEFINED) != (value_focusedDayColor_type)) {
            const value_focusedDayColor_value  = value_focusedDayColor!
            let value_focusedDayColor_value_type : int32 = RuntimeType.UNDEFINED
            value_focusedDayColor_value_type = runtimeType(value_focusedDayColor_value)
            if (TypeChecker.isColor(value_focusedDayColor_value)) {
                valueSerializer.writeInt8(0)
                const value_focusedDayColor_value_0  = value_focusedDayColor_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_focusedDayColor_value_0))
            }
            else if (RuntimeType.NUMBER == value_focusedDayColor_value_type) {
                valueSerializer.writeInt8(1)
                const value_focusedDayColor_value_1  = value_focusedDayColor_value as number
                valueSerializer.writeNumber(value_focusedDayColor_value_1)
            }
            else if (RuntimeType.STRING == value_focusedDayColor_value_type) {
                valueSerializer.writeInt8(2)
                const value_focusedDayColor_value_2  = value_focusedDayColor_value as string
                valueSerializer.writeString(value_focusedDayColor_value_2)
            }
            else if (RuntimeType.OBJECT == value_focusedDayColor_value_type) {
                valueSerializer.writeInt8(3)
                const value_focusedDayColor_value_3  = value_focusedDayColor_value as Resource
                Resource_serializer.write(valueSerializer, value_focusedDayColor_value_3)
            }
        }
        const value_focusedLunarColor  = value.focusedLunarColor
        let value_focusedLunarColor_type : int32 = RuntimeType.UNDEFINED
        value_focusedLunarColor_type = runtimeType(value_focusedLunarColor)
        valueSerializer.writeInt8(value_focusedLunarColor_type)
        if ((RuntimeType.UNDEFINED) != (value_focusedLunarColor_type)) {
            const value_focusedLunarColor_value  = value_focusedLunarColor!
            let value_focusedLunarColor_value_type : int32 = RuntimeType.UNDEFINED
            value_focusedLunarColor_value_type = runtimeType(value_focusedLunarColor_value)
            if (TypeChecker.isColor(value_focusedLunarColor_value)) {
                valueSerializer.writeInt8(0)
                const value_focusedLunarColor_value_0  = value_focusedLunarColor_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_focusedLunarColor_value_0))
            }
            else if (RuntimeType.NUMBER == value_focusedLunarColor_value_type) {
                valueSerializer.writeInt8(1)
                const value_focusedLunarColor_value_1  = value_focusedLunarColor_value as number
                valueSerializer.writeNumber(value_focusedLunarColor_value_1)
            }
            else if (RuntimeType.STRING == value_focusedLunarColor_value_type) {
                valueSerializer.writeInt8(2)
                const value_focusedLunarColor_value_2  = value_focusedLunarColor_value as string
                valueSerializer.writeString(value_focusedLunarColor_value_2)
            }
            else if (RuntimeType.OBJECT == value_focusedLunarColor_value_type) {
                valueSerializer.writeInt8(3)
                const value_focusedLunarColor_value_3  = value_focusedLunarColor_value as Resource
                Resource_serializer.write(valueSerializer, value_focusedLunarColor_value_3)
            }
        }
        const value_focusedAreaBackgroundColor  = value.focusedAreaBackgroundColor
        let value_focusedAreaBackgroundColor_type : int32 = RuntimeType.UNDEFINED
        value_focusedAreaBackgroundColor_type = runtimeType(value_focusedAreaBackgroundColor)
        valueSerializer.writeInt8(value_focusedAreaBackgroundColor_type)
        if ((RuntimeType.UNDEFINED) != (value_focusedAreaBackgroundColor_type)) {
            const value_focusedAreaBackgroundColor_value  = value_focusedAreaBackgroundColor!
            let value_focusedAreaBackgroundColor_value_type : int32 = RuntimeType.UNDEFINED
            value_focusedAreaBackgroundColor_value_type = runtimeType(value_focusedAreaBackgroundColor_value)
            if (TypeChecker.isColor(value_focusedAreaBackgroundColor_value)) {
                valueSerializer.writeInt8(0)
                const value_focusedAreaBackgroundColor_value_0  = value_focusedAreaBackgroundColor_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_focusedAreaBackgroundColor_value_0))
            }
            else if (RuntimeType.NUMBER == value_focusedAreaBackgroundColor_value_type) {
                valueSerializer.writeInt8(1)
                const value_focusedAreaBackgroundColor_value_1  = value_focusedAreaBackgroundColor_value as number
                valueSerializer.writeNumber(value_focusedAreaBackgroundColor_value_1)
            }
            else if (RuntimeType.STRING == value_focusedAreaBackgroundColor_value_type) {
                valueSerializer.writeInt8(2)
                const value_focusedAreaBackgroundColor_value_2  = value_focusedAreaBackgroundColor_value as string
                valueSerializer.writeString(value_focusedAreaBackgroundColor_value_2)
            }
            else if (RuntimeType.OBJECT == value_focusedAreaBackgroundColor_value_type) {
                valueSerializer.writeInt8(3)
                const value_focusedAreaBackgroundColor_value_3  = value_focusedAreaBackgroundColor_value as Resource
                Resource_serializer.write(valueSerializer, value_focusedAreaBackgroundColor_value_3)
            }
        }
        const value_focusedAreaRadius  = value.focusedAreaRadius
        let value_focusedAreaRadius_type : int32 = RuntimeType.UNDEFINED
        value_focusedAreaRadius_type = runtimeType(value_focusedAreaRadius)
        valueSerializer.writeInt8(value_focusedAreaRadius_type)
        if ((RuntimeType.UNDEFINED) != (value_focusedAreaRadius_type)) {
            const value_focusedAreaRadius_value  = value_focusedAreaRadius!
            valueSerializer.writeNumber(value_focusedAreaRadius_value)
        }
    }
    public static read(buffer: DeserializerBase): TodayStyle {
        let valueDeserializer : DeserializerBase = buffer
        const focusedDayColor_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let focusedDayColor_buf : ResourceColor | undefined
        if ((RuntimeType.UNDEFINED) != (focusedDayColor_buf_runtimeType))
        {
            const focusedDayColor_buf__selector : int32 = valueDeserializer.readInt8()
            let focusedDayColor_buf_ : Color | number | string | Resource | undefined
            if (focusedDayColor_buf__selector == 0) {
                focusedDayColor_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (focusedDayColor_buf__selector == 1) {
                focusedDayColor_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (focusedDayColor_buf__selector == 2) {
                focusedDayColor_buf_ = (valueDeserializer.readString() as string)
            }
            else if (focusedDayColor_buf__selector == 3) {
                focusedDayColor_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for focusedDayColor_buf_ has to be chosen through deserialisation.")
            }
            focusedDayColor_buf = (focusedDayColor_buf_ as Color | number | string | Resource)
        }
        const focusedDayColor_result : ResourceColor | undefined = focusedDayColor_buf
        const focusedLunarColor_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let focusedLunarColor_buf : ResourceColor | undefined
        if ((RuntimeType.UNDEFINED) != (focusedLunarColor_buf_runtimeType))
        {
            const focusedLunarColor_buf__selector : int32 = valueDeserializer.readInt8()
            let focusedLunarColor_buf_ : Color | number | string | Resource | undefined
            if (focusedLunarColor_buf__selector == 0) {
                focusedLunarColor_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (focusedLunarColor_buf__selector == 1) {
                focusedLunarColor_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (focusedLunarColor_buf__selector == 2) {
                focusedLunarColor_buf_ = (valueDeserializer.readString() as string)
            }
            else if (focusedLunarColor_buf__selector == 3) {
                focusedLunarColor_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for focusedLunarColor_buf_ has to be chosen through deserialisation.")
            }
            focusedLunarColor_buf = (focusedLunarColor_buf_ as Color | number | string | Resource)
        }
        const focusedLunarColor_result : ResourceColor | undefined = focusedLunarColor_buf
        const focusedAreaBackgroundColor_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let focusedAreaBackgroundColor_buf : ResourceColor | undefined
        if ((RuntimeType.UNDEFINED) != (focusedAreaBackgroundColor_buf_runtimeType))
        {
            const focusedAreaBackgroundColor_buf__selector : int32 = valueDeserializer.readInt8()
            let focusedAreaBackgroundColor_buf_ : Color | number | string | Resource | undefined
            if (focusedAreaBackgroundColor_buf__selector == 0) {
                focusedAreaBackgroundColor_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (focusedAreaBackgroundColor_buf__selector == 1) {
                focusedAreaBackgroundColor_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (focusedAreaBackgroundColor_buf__selector == 2) {
                focusedAreaBackgroundColor_buf_ = (valueDeserializer.readString() as string)
            }
            else if (focusedAreaBackgroundColor_buf__selector == 3) {
                focusedAreaBackgroundColor_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for focusedAreaBackgroundColor_buf_ has to be chosen through deserialisation.")
            }
            focusedAreaBackgroundColor_buf = (focusedAreaBackgroundColor_buf_ as Color | number | string | Resource)
        }
        const focusedAreaBackgroundColor_result : ResourceColor | undefined = focusedAreaBackgroundColor_buf
        const focusedAreaRadius_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let focusedAreaRadius_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (focusedAreaRadius_buf_runtimeType))
        {
            focusedAreaRadius_buf = (valueDeserializer.readNumber() as number)
        }
        const focusedAreaRadius_result : number | undefined = focusedAreaRadius_buf
        let value : TodayStyle = ({focusedDayColor: focusedDayColor_result, focusedLunarColor: focusedLunarColor_result, focusedAreaBackgroundColor: focusedAreaBackgroundColor_result, focusedAreaRadius: focusedAreaRadius_result} as TodayStyle)
        return value
    }
}
export class WeekStyle_serializer {
    public static write(buffer: SerializerBase, value: WeekStyle): void {
        let valueSerializer : SerializerBase = buffer
        const value_weekColor  = value.weekColor
        let value_weekColor_type : int32 = RuntimeType.UNDEFINED
        value_weekColor_type = runtimeType(value_weekColor)
        valueSerializer.writeInt8(value_weekColor_type)
        if ((RuntimeType.UNDEFINED) != (value_weekColor_type)) {
            const value_weekColor_value  = value_weekColor!
            let value_weekColor_value_type : int32 = RuntimeType.UNDEFINED
            value_weekColor_value_type = runtimeType(value_weekColor_value)
            if (TypeChecker.isColor(value_weekColor_value)) {
                valueSerializer.writeInt8(0)
                const value_weekColor_value_0  = value_weekColor_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_weekColor_value_0))
            }
            else if (RuntimeType.NUMBER == value_weekColor_value_type) {
                valueSerializer.writeInt8(1)
                const value_weekColor_value_1  = value_weekColor_value as number
                valueSerializer.writeNumber(value_weekColor_value_1)
            }
            else if (RuntimeType.STRING == value_weekColor_value_type) {
                valueSerializer.writeInt8(2)
                const value_weekColor_value_2  = value_weekColor_value as string
                valueSerializer.writeString(value_weekColor_value_2)
            }
            else if (RuntimeType.OBJECT == value_weekColor_value_type) {
                valueSerializer.writeInt8(3)
                const value_weekColor_value_3  = value_weekColor_value as Resource
                Resource_serializer.write(valueSerializer, value_weekColor_value_3)
            }
        }
        const value_weekendDayColor  = value.weekendDayColor
        let value_weekendDayColor_type : int32 = RuntimeType.UNDEFINED
        value_weekendDayColor_type = runtimeType(value_weekendDayColor)
        valueSerializer.writeInt8(value_weekendDayColor_type)
        if ((RuntimeType.UNDEFINED) != (value_weekendDayColor_type)) {
            const value_weekendDayColor_value  = value_weekendDayColor!
            let value_weekendDayColor_value_type : int32 = RuntimeType.UNDEFINED
            value_weekendDayColor_value_type = runtimeType(value_weekendDayColor_value)
            if (TypeChecker.isColor(value_weekendDayColor_value)) {
                valueSerializer.writeInt8(0)
                const value_weekendDayColor_value_0  = value_weekendDayColor_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_weekendDayColor_value_0))
            }
            else if (RuntimeType.NUMBER == value_weekendDayColor_value_type) {
                valueSerializer.writeInt8(1)
                const value_weekendDayColor_value_1  = value_weekendDayColor_value as number
                valueSerializer.writeNumber(value_weekendDayColor_value_1)
            }
            else if (RuntimeType.STRING == value_weekendDayColor_value_type) {
                valueSerializer.writeInt8(2)
                const value_weekendDayColor_value_2  = value_weekendDayColor_value as string
                valueSerializer.writeString(value_weekendDayColor_value_2)
            }
            else if (RuntimeType.OBJECT == value_weekendDayColor_value_type) {
                valueSerializer.writeInt8(3)
                const value_weekendDayColor_value_3  = value_weekendDayColor_value as Resource
                Resource_serializer.write(valueSerializer, value_weekendDayColor_value_3)
            }
        }
        const value_weekendLunarColor  = value.weekendLunarColor
        let value_weekendLunarColor_type : int32 = RuntimeType.UNDEFINED
        value_weekendLunarColor_type = runtimeType(value_weekendLunarColor)
        valueSerializer.writeInt8(value_weekendLunarColor_type)
        if ((RuntimeType.UNDEFINED) != (value_weekendLunarColor_type)) {
            const value_weekendLunarColor_value  = value_weekendLunarColor!
            let value_weekendLunarColor_value_type : int32 = RuntimeType.UNDEFINED
            value_weekendLunarColor_value_type = runtimeType(value_weekendLunarColor_value)
            if (TypeChecker.isColor(value_weekendLunarColor_value)) {
                valueSerializer.writeInt8(0)
                const value_weekendLunarColor_value_0  = value_weekendLunarColor_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_weekendLunarColor_value_0))
            }
            else if (RuntimeType.NUMBER == value_weekendLunarColor_value_type) {
                valueSerializer.writeInt8(1)
                const value_weekendLunarColor_value_1  = value_weekendLunarColor_value as number
                valueSerializer.writeNumber(value_weekendLunarColor_value_1)
            }
            else if (RuntimeType.STRING == value_weekendLunarColor_value_type) {
                valueSerializer.writeInt8(2)
                const value_weekendLunarColor_value_2  = value_weekendLunarColor_value as string
                valueSerializer.writeString(value_weekendLunarColor_value_2)
            }
            else if (RuntimeType.OBJECT == value_weekendLunarColor_value_type) {
                valueSerializer.writeInt8(3)
                const value_weekendLunarColor_value_3  = value_weekendLunarColor_value as Resource
                Resource_serializer.write(valueSerializer, value_weekendLunarColor_value_3)
            }
        }
        const value_weekFontSize  = value.weekFontSize
        let value_weekFontSize_type : int32 = RuntimeType.UNDEFINED
        value_weekFontSize_type = runtimeType(value_weekFontSize)
        valueSerializer.writeInt8(value_weekFontSize_type)
        if ((RuntimeType.UNDEFINED) != (value_weekFontSize_type)) {
            const value_weekFontSize_value  = value_weekFontSize!
            valueSerializer.writeNumber(value_weekFontSize_value)
        }
        const value_weekHeight  = value.weekHeight
        let value_weekHeight_type : int32 = RuntimeType.UNDEFINED
        value_weekHeight_type = runtimeType(value_weekHeight)
        valueSerializer.writeInt8(value_weekHeight_type)
        if ((RuntimeType.UNDEFINED) != (value_weekHeight_type)) {
            const value_weekHeight_value  = value_weekHeight!
            valueSerializer.writeNumber(value_weekHeight_value)
        }
        const value_weekWidth  = value.weekWidth
        let value_weekWidth_type : int32 = RuntimeType.UNDEFINED
        value_weekWidth_type = runtimeType(value_weekWidth)
        valueSerializer.writeInt8(value_weekWidth_type)
        if ((RuntimeType.UNDEFINED) != (value_weekWidth_type)) {
            const value_weekWidth_value  = value_weekWidth!
            valueSerializer.writeNumber(value_weekWidth_value)
        }
        const value_weekAndDayRowSpace  = value.weekAndDayRowSpace
        let value_weekAndDayRowSpace_type : int32 = RuntimeType.UNDEFINED
        value_weekAndDayRowSpace_type = runtimeType(value_weekAndDayRowSpace)
        valueSerializer.writeInt8(value_weekAndDayRowSpace_type)
        if ((RuntimeType.UNDEFINED) != (value_weekAndDayRowSpace_type)) {
            const value_weekAndDayRowSpace_value  = value_weekAndDayRowSpace!
            valueSerializer.writeNumber(value_weekAndDayRowSpace_value)
        }
    }
    public static read(buffer: DeserializerBase): WeekStyle {
        let valueDeserializer : DeserializerBase = buffer
        const weekColor_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let weekColor_buf : ResourceColor | undefined
        if ((RuntimeType.UNDEFINED) != (weekColor_buf_runtimeType))
        {
            const weekColor_buf__selector : int32 = valueDeserializer.readInt8()
            let weekColor_buf_ : Color | number | string | Resource | undefined
            if (weekColor_buf__selector == 0) {
                weekColor_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (weekColor_buf__selector == 1) {
                weekColor_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (weekColor_buf__selector == 2) {
                weekColor_buf_ = (valueDeserializer.readString() as string)
            }
            else if (weekColor_buf__selector == 3) {
                weekColor_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for weekColor_buf_ has to be chosen through deserialisation.")
            }
            weekColor_buf = (weekColor_buf_ as Color | number | string | Resource)
        }
        const weekColor_result : ResourceColor | undefined = weekColor_buf
        const weekendDayColor_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let weekendDayColor_buf : ResourceColor | undefined
        if ((RuntimeType.UNDEFINED) != (weekendDayColor_buf_runtimeType))
        {
            const weekendDayColor_buf__selector : int32 = valueDeserializer.readInt8()
            let weekendDayColor_buf_ : Color | number | string | Resource | undefined
            if (weekendDayColor_buf__selector == 0) {
                weekendDayColor_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (weekendDayColor_buf__selector == 1) {
                weekendDayColor_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (weekendDayColor_buf__selector == 2) {
                weekendDayColor_buf_ = (valueDeserializer.readString() as string)
            }
            else if (weekendDayColor_buf__selector == 3) {
                weekendDayColor_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for weekendDayColor_buf_ has to be chosen through deserialisation.")
            }
            weekendDayColor_buf = (weekendDayColor_buf_ as Color | number | string | Resource)
        }
        const weekendDayColor_result : ResourceColor | undefined = weekendDayColor_buf
        const weekendLunarColor_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let weekendLunarColor_buf : ResourceColor | undefined
        if ((RuntimeType.UNDEFINED) != (weekendLunarColor_buf_runtimeType))
        {
            const weekendLunarColor_buf__selector : int32 = valueDeserializer.readInt8()
            let weekendLunarColor_buf_ : Color | number | string | Resource | undefined
            if (weekendLunarColor_buf__selector == 0) {
                weekendLunarColor_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (weekendLunarColor_buf__selector == 1) {
                weekendLunarColor_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (weekendLunarColor_buf__selector == 2) {
                weekendLunarColor_buf_ = (valueDeserializer.readString() as string)
            }
            else if (weekendLunarColor_buf__selector == 3) {
                weekendLunarColor_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for weekendLunarColor_buf_ has to be chosen through deserialisation.")
            }
            weekendLunarColor_buf = (weekendLunarColor_buf_ as Color | number | string | Resource)
        }
        const weekendLunarColor_result : ResourceColor | undefined = weekendLunarColor_buf
        const weekFontSize_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let weekFontSize_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (weekFontSize_buf_runtimeType))
        {
            weekFontSize_buf = (valueDeserializer.readNumber() as number)
        }
        const weekFontSize_result : number | undefined = weekFontSize_buf
        const weekHeight_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let weekHeight_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (weekHeight_buf_runtimeType))
        {
            weekHeight_buf = (valueDeserializer.readNumber() as number)
        }
        const weekHeight_result : number | undefined = weekHeight_buf
        const weekWidth_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let weekWidth_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (weekWidth_buf_runtimeType))
        {
            weekWidth_buf = (valueDeserializer.readNumber() as number)
        }
        const weekWidth_result : number | undefined = weekWidth_buf
        const weekAndDayRowSpace_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let weekAndDayRowSpace_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (weekAndDayRowSpace_buf_runtimeType))
        {
            weekAndDayRowSpace_buf = (valueDeserializer.readNumber() as number)
        }
        const weekAndDayRowSpace_result : number | undefined = weekAndDayRowSpace_buf
        let value : WeekStyle = ({weekColor: weekColor_result, weekendDayColor: weekendDayColor_result, weekendLunarColor: weekendLunarColor_result, weekFontSize: weekFontSize_result, weekHeight: weekHeight_result, weekWidth: weekWidth_result, weekAndDayRowSpace: weekAndDayRowSpace_result} as WeekStyle)
        return value
    }
}
export class WorkStateStyle_serializer {
    public static write(buffer: SerializerBase, value: WorkStateStyle): void {
        let valueSerializer : SerializerBase = buffer
        const value_workDayMarkColor  = value.workDayMarkColor
        let value_workDayMarkColor_type : int32 = RuntimeType.UNDEFINED
        value_workDayMarkColor_type = runtimeType(value_workDayMarkColor)
        valueSerializer.writeInt8(value_workDayMarkColor_type)
        if ((RuntimeType.UNDEFINED) != (value_workDayMarkColor_type)) {
            const value_workDayMarkColor_value  = value_workDayMarkColor!
            let value_workDayMarkColor_value_type : int32 = RuntimeType.UNDEFINED
            value_workDayMarkColor_value_type = runtimeType(value_workDayMarkColor_value)
            if (TypeChecker.isColor(value_workDayMarkColor_value)) {
                valueSerializer.writeInt8(0)
                const value_workDayMarkColor_value_0  = value_workDayMarkColor_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_workDayMarkColor_value_0))
            }
            else if (RuntimeType.NUMBER == value_workDayMarkColor_value_type) {
                valueSerializer.writeInt8(1)
                const value_workDayMarkColor_value_1  = value_workDayMarkColor_value as number
                valueSerializer.writeNumber(value_workDayMarkColor_value_1)
            }
            else if (RuntimeType.STRING == value_workDayMarkColor_value_type) {
                valueSerializer.writeInt8(2)
                const value_workDayMarkColor_value_2  = value_workDayMarkColor_value as string
                valueSerializer.writeString(value_workDayMarkColor_value_2)
            }
            else if (RuntimeType.OBJECT == value_workDayMarkColor_value_type) {
                valueSerializer.writeInt8(3)
                const value_workDayMarkColor_value_3  = value_workDayMarkColor_value as Resource
                Resource_serializer.write(valueSerializer, value_workDayMarkColor_value_3)
            }
        }
        const value_offDayMarkColor  = value.offDayMarkColor
        let value_offDayMarkColor_type : int32 = RuntimeType.UNDEFINED
        value_offDayMarkColor_type = runtimeType(value_offDayMarkColor)
        valueSerializer.writeInt8(value_offDayMarkColor_type)
        if ((RuntimeType.UNDEFINED) != (value_offDayMarkColor_type)) {
            const value_offDayMarkColor_value  = value_offDayMarkColor!
            let value_offDayMarkColor_value_type : int32 = RuntimeType.UNDEFINED
            value_offDayMarkColor_value_type = runtimeType(value_offDayMarkColor_value)
            if (TypeChecker.isColor(value_offDayMarkColor_value)) {
                valueSerializer.writeInt8(0)
                const value_offDayMarkColor_value_0  = value_offDayMarkColor_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_offDayMarkColor_value_0))
            }
            else if (RuntimeType.NUMBER == value_offDayMarkColor_value_type) {
                valueSerializer.writeInt8(1)
                const value_offDayMarkColor_value_1  = value_offDayMarkColor_value as number
                valueSerializer.writeNumber(value_offDayMarkColor_value_1)
            }
            else if (RuntimeType.STRING == value_offDayMarkColor_value_type) {
                valueSerializer.writeInt8(2)
                const value_offDayMarkColor_value_2  = value_offDayMarkColor_value as string
                valueSerializer.writeString(value_offDayMarkColor_value_2)
            }
            else if (RuntimeType.OBJECT == value_offDayMarkColor_value_type) {
                valueSerializer.writeInt8(3)
                const value_offDayMarkColor_value_3  = value_offDayMarkColor_value as Resource
                Resource_serializer.write(valueSerializer, value_offDayMarkColor_value_3)
            }
        }
        const value_workDayMarkSize  = value.workDayMarkSize
        let value_workDayMarkSize_type : int32 = RuntimeType.UNDEFINED
        value_workDayMarkSize_type = runtimeType(value_workDayMarkSize)
        valueSerializer.writeInt8(value_workDayMarkSize_type)
        if ((RuntimeType.UNDEFINED) != (value_workDayMarkSize_type)) {
            const value_workDayMarkSize_value  = value_workDayMarkSize!
            valueSerializer.writeNumber(value_workDayMarkSize_value)
        }
        const value_offDayMarkSize  = value.offDayMarkSize
        let value_offDayMarkSize_type : int32 = RuntimeType.UNDEFINED
        value_offDayMarkSize_type = runtimeType(value_offDayMarkSize)
        valueSerializer.writeInt8(value_offDayMarkSize_type)
        if ((RuntimeType.UNDEFINED) != (value_offDayMarkSize_type)) {
            const value_offDayMarkSize_value  = value_offDayMarkSize!
            valueSerializer.writeNumber(value_offDayMarkSize_value)
        }
        const value_workStateWidth  = value.workStateWidth
        let value_workStateWidth_type : int32 = RuntimeType.UNDEFINED
        value_workStateWidth_type = runtimeType(value_workStateWidth)
        valueSerializer.writeInt8(value_workStateWidth_type)
        if ((RuntimeType.UNDEFINED) != (value_workStateWidth_type)) {
            const value_workStateWidth_value  = value_workStateWidth!
            valueSerializer.writeNumber(value_workStateWidth_value)
        }
        const value_workStateHorizontalMovingDistance  = value.workStateHorizontalMovingDistance
        let value_workStateHorizontalMovingDistance_type : int32 = RuntimeType.UNDEFINED
        value_workStateHorizontalMovingDistance_type = runtimeType(value_workStateHorizontalMovingDistance)
        valueSerializer.writeInt8(value_workStateHorizontalMovingDistance_type)
        if ((RuntimeType.UNDEFINED) != (value_workStateHorizontalMovingDistance_type)) {
            const value_workStateHorizontalMovingDistance_value  = value_workStateHorizontalMovingDistance!
            valueSerializer.writeNumber(value_workStateHorizontalMovingDistance_value)
        }
        const value_workStateVerticalMovingDistance  = value.workStateVerticalMovingDistance
        let value_workStateVerticalMovingDistance_type : int32 = RuntimeType.UNDEFINED
        value_workStateVerticalMovingDistance_type = runtimeType(value_workStateVerticalMovingDistance)
        valueSerializer.writeInt8(value_workStateVerticalMovingDistance_type)
        if ((RuntimeType.UNDEFINED) != (value_workStateVerticalMovingDistance_type)) {
            const value_workStateVerticalMovingDistance_value  = value_workStateVerticalMovingDistance!
            valueSerializer.writeNumber(value_workStateVerticalMovingDistance_value)
        }
    }
    public static read(buffer: DeserializerBase): WorkStateStyle {
        let valueDeserializer : DeserializerBase = buffer
        const workDayMarkColor_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let workDayMarkColor_buf : ResourceColor | undefined
        if ((RuntimeType.UNDEFINED) != (workDayMarkColor_buf_runtimeType))
        {
            const workDayMarkColor_buf__selector : int32 = valueDeserializer.readInt8()
            let workDayMarkColor_buf_ : Color | number | string | Resource | undefined
            if (workDayMarkColor_buf__selector == 0) {
                workDayMarkColor_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (workDayMarkColor_buf__selector == 1) {
                workDayMarkColor_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (workDayMarkColor_buf__selector == 2) {
                workDayMarkColor_buf_ = (valueDeserializer.readString() as string)
            }
            else if (workDayMarkColor_buf__selector == 3) {
                workDayMarkColor_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for workDayMarkColor_buf_ has to be chosen through deserialisation.")
            }
            workDayMarkColor_buf = (workDayMarkColor_buf_ as Color | number | string | Resource)
        }
        const workDayMarkColor_result : ResourceColor | undefined = workDayMarkColor_buf
        const offDayMarkColor_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let offDayMarkColor_buf : ResourceColor | undefined
        if ((RuntimeType.UNDEFINED) != (offDayMarkColor_buf_runtimeType))
        {
            const offDayMarkColor_buf__selector : int32 = valueDeserializer.readInt8()
            let offDayMarkColor_buf_ : Color | number | string | Resource | undefined
            if (offDayMarkColor_buf__selector == 0) {
                offDayMarkColor_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (offDayMarkColor_buf__selector == 1) {
                offDayMarkColor_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (offDayMarkColor_buf__selector == 2) {
                offDayMarkColor_buf_ = (valueDeserializer.readString() as string)
            }
            else if (offDayMarkColor_buf__selector == 3) {
                offDayMarkColor_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for offDayMarkColor_buf_ has to be chosen through deserialisation.")
            }
            offDayMarkColor_buf = (offDayMarkColor_buf_ as Color | number | string | Resource)
        }
        const offDayMarkColor_result : ResourceColor | undefined = offDayMarkColor_buf
        const workDayMarkSize_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let workDayMarkSize_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (workDayMarkSize_buf_runtimeType))
        {
            workDayMarkSize_buf = (valueDeserializer.readNumber() as number)
        }
        const workDayMarkSize_result : number | undefined = workDayMarkSize_buf
        const offDayMarkSize_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let offDayMarkSize_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (offDayMarkSize_buf_runtimeType))
        {
            offDayMarkSize_buf = (valueDeserializer.readNumber() as number)
        }
        const offDayMarkSize_result : number | undefined = offDayMarkSize_buf
        const workStateWidth_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let workStateWidth_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (workStateWidth_buf_runtimeType))
        {
            workStateWidth_buf = (valueDeserializer.readNumber() as number)
        }
        const workStateWidth_result : number | undefined = workStateWidth_buf
        const workStateHorizontalMovingDistance_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let workStateHorizontalMovingDistance_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (workStateHorizontalMovingDistance_buf_runtimeType))
        {
            workStateHorizontalMovingDistance_buf = (valueDeserializer.readNumber() as number)
        }
        const workStateHorizontalMovingDistance_result : number | undefined = workStateHorizontalMovingDistance_buf
        const workStateVerticalMovingDistance_buf_runtimeType  = (valueDeserializer.readInt8() as int32)
        let workStateVerticalMovingDistance_buf : number | undefined
        if ((RuntimeType.UNDEFINED) != (workStateVerticalMovingDistance_buf_runtimeType))
        {
            workStateVerticalMovingDistance_buf = (valueDeserializer.readNumber() as number)
        }
        const workStateVerticalMovingDistance_result : number | undefined = workStateVerticalMovingDistance_buf
        let value : WorkStateStyle = ({workDayMarkColor: workDayMarkColor_result, offDayMarkColor: offDayMarkColor_result, workDayMarkSize: workDayMarkSize_result, offDayMarkSize: offDayMarkSize_result, workStateWidth: workStateWidth_result, workStateHorizontalMovingDistance: workStateHorizontalMovingDistance_result, workStateVerticalMovingDistance: workStateVerticalMovingDistance_result} as WorkStateStyle)
        return value
    }
}
