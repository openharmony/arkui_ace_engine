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
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { Axis, Color } from "./enums"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { ResourceColor } from "./units"
import { Resource, Resource_serializer } from "./../generated/resource"
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
    constructor() {
        this(CalendarController.construct())
    }
    static construct(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._CalendarController_construct()
        return retval
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
    setShowLunarAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._CalendarAttribute_setShowLunar(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setShowHolidayAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._CalendarAttribute_setShowHoliday(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setNeedSlideAttribute(value: boolean | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._CalendarAttribute_setNeedSlide(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setStartOfWeekAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._CalendarAttribute_setStartOfWeek(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOffDaysAttribute(value: number | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.writeNumber(value_value)
        }
        ArkUIGeneratedNativeModule._CalendarAttribute_setOffDays(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setDirectionAttribute(value: Axis | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = (value as Axis)
            thisSerializer.writeInt32(TypeChecker.Axis_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._CalendarAttribute_setDirection(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setCurrentDayStyleAttribute(value: CurrentDayStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            CurrentDayStyle_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._CalendarAttribute_setCurrentDayStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setNonCurrentDayStyleAttribute(value: NonCurrentDayStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            NonCurrentDayStyle_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._CalendarAttribute_setNonCurrentDayStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setTodayStyleAttribute(value: TodayStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            TodayStyle_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._CalendarAttribute_setTodayStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setWeekStyleAttribute(value: WeekStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            WeekStyle_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._CalendarAttribute_setWeekStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setWorkStateStyleAttribute(value: WorkStateStyle | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            WorkStateStyle_serializer.write(thisSerializer, value_value)
        }
        ArkUIGeneratedNativeModule._CalendarAttribute_setWorkStateStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnSelectChangeAttribute(value: ((event: CalendarSelectedDate) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._CalendarAttribute_setOnSelectChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    setOnRequestDataAttribute(value: ((event: CalendarRequestedData) => void) | undefined): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8((value_type).toChar())
        if ((value_type) != (RuntimeType.UNDEFINED)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._CalendarAttribute_setOnRequestData(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
    showLunar(value: boolean | undefined): this {
        throw new Error("Unimplemented method showLunar")
    }
    showHoliday(value: boolean | undefined): this {
        throw new Error("Unimplemented method showHoliday")
    }
    needSlide(value: boolean | undefined): this {
        throw new Error("Unimplemented method needSlide")
    }
    startOfWeek(value: number | undefined): this {
        throw new Error("Unimplemented method startOfWeek")
    }
    offDays(value: number | undefined): this {
        throw new Error("Unimplemented method offDays")
    }
    direction(value: Axis | undefined): this {
        throw new Error("Unimplemented method direction")
    }
    currentDayStyle(value: CurrentDayStyle | undefined): this {
        throw new Error("Unimplemented method currentDayStyle")
    }
    nonCurrentDayStyle(value: NonCurrentDayStyle | undefined): this {
        throw new Error("Unimplemented method nonCurrentDayStyle")
    }
    todayStyle(value: TodayStyle | undefined): this {
        throw new Error("Unimplemented method todayStyle")
    }
    weekStyle(value: WeekStyle | undefined): this {
        throw new Error("Unimplemented method weekStyle")
    }
    workStateStyle(value: WorkStateStyle | undefined): this {
        throw new Error("Unimplemented method workStateStyle")
    }
    onSelectChange(value: ((event: CalendarSelectedDate) => void) | undefined): this {
        throw new Error("Unimplemented method onSelectChange")
    }
    onRequestData(value: ((event: CalendarRequestedData) => void) | undefined): this {
        throw new Error("Unimplemented method onRequestData")
    }
    attributeModifier(value: AttributeModifier<CalendarAttribute> | undefined): this {
        throw new Error("Unimplemented method attributeModifier")
    }
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
            this.getPeer()?.setShowLunarAttribute(value_casted)
            return this
        }
        return this
    }
    public showHoliday(value: boolean | undefined): this {
        if (this.checkPriority("showHoliday")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setShowHolidayAttribute(value_casted)
            return this
        }
        return this
    }
    public needSlide(value: boolean | undefined): this {
        if (this.checkPriority("needSlide")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setNeedSlideAttribute(value_casted)
            return this
        }
        return this
    }
    public startOfWeek(value: number | undefined): this {
        if (this.checkPriority("startOfWeek")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.setStartOfWeekAttribute(value_casted)
            return this
        }
        return this
    }
    public offDays(value: number | undefined): this {
        if (this.checkPriority("offDays")) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.setOffDaysAttribute(value_casted)
            return this
        }
        return this
    }
    public direction(value: Axis | undefined): this {
        if (this.checkPriority("direction")) {
            const value_casted = value as (Axis | undefined)
            this.getPeer()?.setDirectionAttribute(value_casted)
            return this
        }
        return this
    }
    public currentDayStyle(value: CurrentDayStyle | undefined): this {
        if (this.checkPriority("currentDayStyle")) {
            const value_casted = value as (CurrentDayStyle | undefined)
            this.getPeer()?.setCurrentDayStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public nonCurrentDayStyle(value: NonCurrentDayStyle | undefined): this {
        if (this.checkPriority("nonCurrentDayStyle")) {
            const value_casted = value as (NonCurrentDayStyle | undefined)
            this.getPeer()?.setNonCurrentDayStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public todayStyle(value: TodayStyle | undefined): this {
        if (this.checkPriority("todayStyle")) {
            const value_casted = value as (TodayStyle | undefined)
            this.getPeer()?.setTodayStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public weekStyle(value: WeekStyle | undefined): this {
        if (this.checkPriority("weekStyle")) {
            const value_casted = value as (WeekStyle | undefined)
            this.getPeer()?.setWeekStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public workStateStyle(value: WorkStateStyle | undefined): this {
        if (this.checkPriority("workStateStyle")) {
            const value_casted = value as (WorkStateStyle | undefined)
            this.getPeer()?.setWorkStateStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public onSelectChange(value: ((event: CalendarSelectedDate) => void) | undefined): this {
        if (this.checkPriority("onSelectChange")) {
            const value_casted = value as (((event: CalendarSelectedDate) => void) | undefined)
            this.getPeer()?.setOnSelectChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public onRequestData(value: ((event: CalendarRequestedData) => void) | undefined): this {
        if (this.checkPriority("onRequestData")) {
            const value_casted = value as (((event: CalendarRequestedData) => void) | undefined)
            this.getPeer()?.setOnRequestDataAttribute(value_casted)
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
        if (modifier!.isUpdater())
            (modifier! as AttributeUpdater<CalendarAttribute>).initializeModifier(style)
        else
            (modifier! as AttributeModifier<CalendarAttribute>).applyNormalAttribute(style)
        style.apply(receiver)
    }
}
// @memo
// @BuilderLambda("Calendar")
// export function Calendar(
//     value: CalendarRequestedMonths,
//     @memo
//     content_?: () => void,
// ): CalendarAttribute {
//     throw new Error("Not implemented")
// }

@memo
export function Calendar(
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

export class ArkCalendarSet implements CalendarAttribute {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    _showLunar_flag?: boolean
    _showLunar0_value?: boolean | undefined
    _showHoliday_flag?: boolean
    _showHoliday0_value?: boolean | undefined
    _needSlide_flag?: boolean
    _needSlide0_value?: boolean | undefined
    _startOfWeek_flag?: boolean
    _startOfWeek0_value?: number | undefined
    _offDays_flag?: boolean
    _offDays0_value?: number | undefined
    _direction_flag?: boolean
    _direction0_value?: Axis | undefined
    _currentDayStyle_flag?: boolean
    _currentDayStyle0_value?: CurrentDayStyle | undefined
    _nonCurrentDayStyle_flag?: boolean
    _nonCurrentDayStyle0_value?: NonCurrentDayStyle | undefined
    _todayStyle_flag?: boolean
    _todayStyle0_value?: TodayStyle | undefined
    _weekStyle_flag?: boolean
    _weekStyle0_value?: WeekStyle | undefined
    _workStateStyle_flag?: boolean
    _workStateStyle0_value?: WorkStateStyle | undefined
    _onSelectChange_flag?: boolean
    _onSelectChange0_value?: ((event: CalendarSelectedDate) => void) | undefined
    _onRequestData_flag?: boolean
    _onRequestData0_value?: ((event: CalendarRequestedData) => void) | undefined
    applyModifierPatch(component: CalendarAttribute): void {
        if (this._showLunar_flag)
            component.showLunar((this._showLunar0_value as boolean | undefined))
        if (this._showHoliday_flag)
            component.showHoliday((this._showHoliday0_value as boolean | undefined))
        if (this._needSlide_flag)
            component.needSlide((this._needSlide0_value as boolean | undefined))
        if (this._startOfWeek_flag)
            component.startOfWeek((this._startOfWeek0_value as number | undefined))
        if (this._offDays_flag)
            component.offDays((this._offDays0_value as number | undefined))
        if (this._direction_flag)
            component.direction((this._direction0_value as Axis | undefined))
        if (this._currentDayStyle_flag)
            component.currentDayStyle((this._currentDayStyle0_value as CurrentDayStyle | undefined))
        if (this._nonCurrentDayStyle_flag)
            component.nonCurrentDayStyle((this._nonCurrentDayStyle0_value as NonCurrentDayStyle | undefined))
        if (this._todayStyle_flag)
            component.todayStyle((this._todayStyle0_value as TodayStyle | undefined))
        if (this._weekStyle_flag)
            component.weekStyle((this._weekStyle0_value as WeekStyle | undefined))
        if (this._workStateStyle_flag)
            component.workStateStyle((this._workStateStyle0_value as WorkStateStyle | undefined))
        if (this._onSelectChange_flag)
            component.onSelectChange((this._onSelectChange0_value as ((event: CalendarSelectedDate) => void) | undefined))
        if (this._onRequestData_flag)
            component.onRequestData((this._onRequestData0_value as ((event: CalendarRequestedData) => void) | undefined))
    }
    public showLunar(value: boolean | undefined): this {
        this._showLunar_flag = true
        this._showLunar0_value = value
        return this
    }
    public showHoliday(value: boolean | undefined): this {
        this._showHoliday_flag = true
        this._showHoliday0_value = value
        return this
    }
    public needSlide(value: boolean | undefined): this {
        this._needSlide_flag = true
        this._needSlide0_value = value
        return this
    }
    public startOfWeek(value: number | undefined): this {
        this._startOfWeek_flag = true
        this._startOfWeek0_value = value
        return this
    }
    public offDays(value: number | undefined): this {
        this._offDays_flag = true
        this._offDays0_value = value
        return this
    }
    public direction(value: Axis | undefined): this {
        this._direction_flag = true
        this._direction0_value = value
        return this
    }
    public currentDayStyle(value: CurrentDayStyle | undefined): this {
        this._currentDayStyle_flag = true
        this._currentDayStyle0_value = value
        return this
    }
    public nonCurrentDayStyle(value: NonCurrentDayStyle | undefined): this {
        this._nonCurrentDayStyle_flag = true
        this._nonCurrentDayStyle0_value = value
        return this
    }
    public todayStyle(value: TodayStyle | undefined): this {
        this._todayStyle_flag = true
        this._todayStyle0_value = value
        return this
    }
    public weekStyle(value: WeekStyle | undefined): this {
        this._weekStyle_flag = true
        this._weekStyle0_value = value
        return this
    }
    public workStateStyle(value: WorkStateStyle | undefined): this {
        this._workStateStyle_flag = true
        this._workStateStyle0_value = value
        return this
    }
    public onSelectChange(value: ((event: CalendarSelectedDate) => void) | undefined): this {
        this._onSelectChange_flag = true
        this._onSelectChange0_value = value
        return this
    }
    public onRequestData(value: ((event: CalendarRequestedData) => void) | undefined): this {
        this._onRequestData_flag = true
        this._onRequestData0_value = value
        return this
    }
    public attributeModifier(value: AttributeModifier<CalendarAttribute> | undefined): this {
        throw new Error("Not implemented")
    }
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
        valueSerializer.writeInt32((value_data.length).toInt())
        for (let value_data_counter_i = 0; value_data_counter_i < value_data.length; value_data_counter_i++) {
            const value_data_element : CalendarDay = value_data[value_data_counter_i]
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
        valueSerializer.writeInt8((value_controller_type).toChar())
        if ((value_controller_type) != (RuntimeType.UNDEFINED)) {
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
        const controller_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let controller_buf : CalendarController | undefined
        if ((controller_buf_runtimeType) != (RuntimeType.UNDEFINED))
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
        valueSerializer.writeInt8((value_dayColor_type).toChar())
        if ((value_dayColor_type) != (RuntimeType.UNDEFINED)) {
            const value_dayColor_value  = value_dayColor!
            let value_dayColor_value_type : int32 = RuntimeType.UNDEFINED
            value_dayColor_value_type = runtimeType(value_dayColor_value)
            if (TypeChecker.isColor(value_dayColor_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value_dayColor_value_0  = value_dayColor_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_dayColor_value_0))
            }
            else if (RuntimeType.NUMBER == value_dayColor_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_dayColor_value_1  = value_dayColor_value as number
                valueSerializer.writeNumber(value_dayColor_value_1)
            }
            else if (RuntimeType.STRING == value_dayColor_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_dayColor_value_2  = value_dayColor_value as string
                valueSerializer.writeString(value_dayColor_value_2)
            }
            else if (RuntimeType.OBJECT == value_dayColor_value_type) {
                valueSerializer.writeInt8((3).toChar())
                const value_dayColor_value_3  = value_dayColor_value as Resource
                Resource_serializer.write(valueSerializer, value_dayColor_value_3)
            }
        }
        const value_lunarColor  = value.lunarColor
        let value_lunarColor_type : int32 = RuntimeType.UNDEFINED
        value_lunarColor_type = runtimeType(value_lunarColor)
        valueSerializer.writeInt8((value_lunarColor_type).toChar())
        if ((value_lunarColor_type) != (RuntimeType.UNDEFINED)) {
            const value_lunarColor_value  = value_lunarColor!
            let value_lunarColor_value_type : int32 = RuntimeType.UNDEFINED
            value_lunarColor_value_type = runtimeType(value_lunarColor_value)
            if (TypeChecker.isColor(value_lunarColor_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value_lunarColor_value_0  = value_lunarColor_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_lunarColor_value_0))
            }
            else if (RuntimeType.NUMBER == value_lunarColor_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_lunarColor_value_1  = value_lunarColor_value as number
                valueSerializer.writeNumber(value_lunarColor_value_1)
            }
            else if (RuntimeType.STRING == value_lunarColor_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_lunarColor_value_2  = value_lunarColor_value as string
                valueSerializer.writeString(value_lunarColor_value_2)
            }
            else if (RuntimeType.OBJECT == value_lunarColor_value_type) {
                valueSerializer.writeInt8((3).toChar())
                const value_lunarColor_value_3  = value_lunarColor_value as Resource
                Resource_serializer.write(valueSerializer, value_lunarColor_value_3)
            }
        }
        const value_markLunarColor  = value.markLunarColor
        let value_markLunarColor_type : int32 = RuntimeType.UNDEFINED
        value_markLunarColor_type = runtimeType(value_markLunarColor)
        valueSerializer.writeInt8((value_markLunarColor_type).toChar())
        if ((value_markLunarColor_type) != (RuntimeType.UNDEFINED)) {
            const value_markLunarColor_value  = value_markLunarColor!
            let value_markLunarColor_value_type : int32 = RuntimeType.UNDEFINED
            value_markLunarColor_value_type = runtimeType(value_markLunarColor_value)
            if (TypeChecker.isColor(value_markLunarColor_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value_markLunarColor_value_0  = value_markLunarColor_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_markLunarColor_value_0))
            }
            else if (RuntimeType.NUMBER == value_markLunarColor_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_markLunarColor_value_1  = value_markLunarColor_value as number
                valueSerializer.writeNumber(value_markLunarColor_value_1)
            }
            else if (RuntimeType.STRING == value_markLunarColor_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_markLunarColor_value_2  = value_markLunarColor_value as string
                valueSerializer.writeString(value_markLunarColor_value_2)
            }
            else if (RuntimeType.OBJECT == value_markLunarColor_value_type) {
                valueSerializer.writeInt8((3).toChar())
                const value_markLunarColor_value_3  = value_markLunarColor_value as Resource
                Resource_serializer.write(valueSerializer, value_markLunarColor_value_3)
            }
        }
        const value_dayFontSize  = value.dayFontSize
        let value_dayFontSize_type : int32 = RuntimeType.UNDEFINED
        value_dayFontSize_type = runtimeType(value_dayFontSize)
        valueSerializer.writeInt8((value_dayFontSize_type).toChar())
        if ((value_dayFontSize_type) != (RuntimeType.UNDEFINED)) {
            const value_dayFontSize_value  = value_dayFontSize!
            valueSerializer.writeNumber(value_dayFontSize_value)
        }
        const value_lunarDayFontSize  = value.lunarDayFontSize
        let value_lunarDayFontSize_type : int32 = RuntimeType.UNDEFINED
        value_lunarDayFontSize_type = runtimeType(value_lunarDayFontSize)
        valueSerializer.writeInt8((value_lunarDayFontSize_type).toChar())
        if ((value_lunarDayFontSize_type) != (RuntimeType.UNDEFINED)) {
            const value_lunarDayFontSize_value  = value_lunarDayFontSize!
            valueSerializer.writeNumber(value_lunarDayFontSize_value)
        }
        const value_dayHeight  = value.dayHeight
        let value_dayHeight_type : int32 = RuntimeType.UNDEFINED
        value_dayHeight_type = runtimeType(value_dayHeight)
        valueSerializer.writeInt8((value_dayHeight_type).toChar())
        if ((value_dayHeight_type) != (RuntimeType.UNDEFINED)) {
            const value_dayHeight_value  = value_dayHeight!
            valueSerializer.writeNumber(value_dayHeight_value)
        }
        const value_dayWidth  = value.dayWidth
        let value_dayWidth_type : int32 = RuntimeType.UNDEFINED
        value_dayWidth_type = runtimeType(value_dayWidth)
        valueSerializer.writeInt8((value_dayWidth_type).toChar())
        if ((value_dayWidth_type) != (RuntimeType.UNDEFINED)) {
            const value_dayWidth_value  = value_dayWidth!
            valueSerializer.writeNumber(value_dayWidth_value)
        }
        const value_gregorianCalendarHeight  = value.gregorianCalendarHeight
        let value_gregorianCalendarHeight_type : int32 = RuntimeType.UNDEFINED
        value_gregorianCalendarHeight_type = runtimeType(value_gregorianCalendarHeight)
        valueSerializer.writeInt8((value_gregorianCalendarHeight_type).toChar())
        if ((value_gregorianCalendarHeight_type) != (RuntimeType.UNDEFINED)) {
            const value_gregorianCalendarHeight_value  = value_gregorianCalendarHeight!
            valueSerializer.writeNumber(value_gregorianCalendarHeight_value)
        }
        const value_dayYAxisOffset  = value.dayYAxisOffset
        let value_dayYAxisOffset_type : int32 = RuntimeType.UNDEFINED
        value_dayYAxisOffset_type = runtimeType(value_dayYAxisOffset)
        valueSerializer.writeInt8((value_dayYAxisOffset_type).toChar())
        if ((value_dayYAxisOffset_type) != (RuntimeType.UNDEFINED)) {
            const value_dayYAxisOffset_value  = value_dayYAxisOffset!
            valueSerializer.writeNumber(value_dayYAxisOffset_value)
        }
        const value_lunarDayYAxisOffset  = value.lunarDayYAxisOffset
        let value_lunarDayYAxisOffset_type : int32 = RuntimeType.UNDEFINED
        value_lunarDayYAxisOffset_type = runtimeType(value_lunarDayYAxisOffset)
        valueSerializer.writeInt8((value_lunarDayYAxisOffset_type).toChar())
        if ((value_lunarDayYAxisOffset_type) != (RuntimeType.UNDEFINED)) {
            const value_lunarDayYAxisOffset_value  = value_lunarDayYAxisOffset!
            valueSerializer.writeNumber(value_lunarDayYAxisOffset_value)
        }
        const value_underscoreXAxisOffset  = value.underscoreXAxisOffset
        let value_underscoreXAxisOffset_type : int32 = RuntimeType.UNDEFINED
        value_underscoreXAxisOffset_type = runtimeType(value_underscoreXAxisOffset)
        valueSerializer.writeInt8((value_underscoreXAxisOffset_type).toChar())
        if ((value_underscoreXAxisOffset_type) != (RuntimeType.UNDEFINED)) {
            const value_underscoreXAxisOffset_value  = value_underscoreXAxisOffset!
            valueSerializer.writeNumber(value_underscoreXAxisOffset_value)
        }
        const value_underscoreYAxisOffset  = value.underscoreYAxisOffset
        let value_underscoreYAxisOffset_type : int32 = RuntimeType.UNDEFINED
        value_underscoreYAxisOffset_type = runtimeType(value_underscoreYAxisOffset)
        valueSerializer.writeInt8((value_underscoreYAxisOffset_type).toChar())
        if ((value_underscoreYAxisOffset_type) != (RuntimeType.UNDEFINED)) {
            const value_underscoreYAxisOffset_value  = value_underscoreYAxisOffset!
            valueSerializer.writeNumber(value_underscoreYAxisOffset_value)
        }
        const value_scheduleMarkerXAxisOffset  = value.scheduleMarkerXAxisOffset
        let value_scheduleMarkerXAxisOffset_type : int32 = RuntimeType.UNDEFINED
        value_scheduleMarkerXAxisOffset_type = runtimeType(value_scheduleMarkerXAxisOffset)
        valueSerializer.writeInt8((value_scheduleMarkerXAxisOffset_type).toChar())
        if ((value_scheduleMarkerXAxisOffset_type) != (RuntimeType.UNDEFINED)) {
            const value_scheduleMarkerXAxisOffset_value  = value_scheduleMarkerXAxisOffset!
            valueSerializer.writeNumber(value_scheduleMarkerXAxisOffset_value)
        }
        const value_scheduleMarkerYAxisOffset  = value.scheduleMarkerYAxisOffset
        let value_scheduleMarkerYAxisOffset_type : int32 = RuntimeType.UNDEFINED
        value_scheduleMarkerYAxisOffset_type = runtimeType(value_scheduleMarkerYAxisOffset)
        valueSerializer.writeInt8((value_scheduleMarkerYAxisOffset_type).toChar())
        if ((value_scheduleMarkerYAxisOffset_type) != (RuntimeType.UNDEFINED)) {
            const value_scheduleMarkerYAxisOffset_value  = value_scheduleMarkerYAxisOffset!
            valueSerializer.writeNumber(value_scheduleMarkerYAxisOffset_value)
        }
        const value_colSpace  = value.colSpace
        let value_colSpace_type : int32 = RuntimeType.UNDEFINED
        value_colSpace_type = runtimeType(value_colSpace)
        valueSerializer.writeInt8((value_colSpace_type).toChar())
        if ((value_colSpace_type) != (RuntimeType.UNDEFINED)) {
            const value_colSpace_value  = value_colSpace!
            valueSerializer.writeNumber(value_colSpace_value)
        }
        const value_dailyFiveRowSpace  = value.dailyFiveRowSpace
        let value_dailyFiveRowSpace_type : int32 = RuntimeType.UNDEFINED
        value_dailyFiveRowSpace_type = runtimeType(value_dailyFiveRowSpace)
        valueSerializer.writeInt8((value_dailyFiveRowSpace_type).toChar())
        if ((value_dailyFiveRowSpace_type) != (RuntimeType.UNDEFINED)) {
            const value_dailyFiveRowSpace_value  = value_dailyFiveRowSpace!
            valueSerializer.writeNumber(value_dailyFiveRowSpace_value)
        }
        const value_dailySixRowSpace  = value.dailySixRowSpace
        let value_dailySixRowSpace_type : int32 = RuntimeType.UNDEFINED
        value_dailySixRowSpace_type = runtimeType(value_dailySixRowSpace)
        valueSerializer.writeInt8((value_dailySixRowSpace_type).toChar())
        if ((value_dailySixRowSpace_type) != (RuntimeType.UNDEFINED)) {
            const value_dailySixRowSpace_value  = value_dailySixRowSpace!
            valueSerializer.writeNumber(value_dailySixRowSpace_value)
        }
        const value_lunarHeight  = value.lunarHeight
        let value_lunarHeight_type : int32 = RuntimeType.UNDEFINED
        value_lunarHeight_type = runtimeType(value_lunarHeight)
        valueSerializer.writeInt8((value_lunarHeight_type).toChar())
        if ((value_lunarHeight_type) != (RuntimeType.UNDEFINED)) {
            const value_lunarHeight_value  = value_lunarHeight!
            valueSerializer.writeNumber(value_lunarHeight_value)
        }
        const value_underscoreWidth  = value.underscoreWidth
        let value_underscoreWidth_type : int32 = RuntimeType.UNDEFINED
        value_underscoreWidth_type = runtimeType(value_underscoreWidth)
        valueSerializer.writeInt8((value_underscoreWidth_type).toChar())
        if ((value_underscoreWidth_type) != (RuntimeType.UNDEFINED)) {
            const value_underscoreWidth_value  = value_underscoreWidth!
            valueSerializer.writeNumber(value_underscoreWidth_value)
        }
        const value_underscoreLength  = value.underscoreLength
        let value_underscoreLength_type : int32 = RuntimeType.UNDEFINED
        value_underscoreLength_type = runtimeType(value_underscoreLength)
        valueSerializer.writeInt8((value_underscoreLength_type).toChar())
        if ((value_underscoreLength_type) != (RuntimeType.UNDEFINED)) {
            const value_underscoreLength_value  = value_underscoreLength!
            valueSerializer.writeNumber(value_underscoreLength_value)
        }
        const value_scheduleMarkerRadius  = value.scheduleMarkerRadius
        let value_scheduleMarkerRadius_type : int32 = RuntimeType.UNDEFINED
        value_scheduleMarkerRadius_type = runtimeType(value_scheduleMarkerRadius)
        valueSerializer.writeInt8((value_scheduleMarkerRadius_type).toChar())
        if ((value_scheduleMarkerRadius_type) != (RuntimeType.UNDEFINED)) {
            const value_scheduleMarkerRadius_value  = value_scheduleMarkerRadius!
            valueSerializer.writeNumber(value_scheduleMarkerRadius_value)
        }
        const value_boundaryRowOffset  = value.boundaryRowOffset
        let value_boundaryRowOffset_type : int32 = RuntimeType.UNDEFINED
        value_boundaryRowOffset_type = runtimeType(value_boundaryRowOffset)
        valueSerializer.writeInt8((value_boundaryRowOffset_type).toChar())
        if ((value_boundaryRowOffset_type) != (RuntimeType.UNDEFINED)) {
            const value_boundaryRowOffset_value  = value_boundaryRowOffset!
            valueSerializer.writeNumber(value_boundaryRowOffset_value)
        }
        const value_boundaryColOffset  = value.boundaryColOffset
        let value_boundaryColOffset_type : int32 = RuntimeType.UNDEFINED
        value_boundaryColOffset_type = runtimeType(value_boundaryColOffset)
        valueSerializer.writeInt8((value_boundaryColOffset_type).toChar())
        if ((value_boundaryColOffset_type) != (RuntimeType.UNDEFINED)) {
            const value_boundaryColOffset_value  = value_boundaryColOffset!
            valueSerializer.writeNumber(value_boundaryColOffset_value)
        }
    }
    public static read(buffer: DeserializerBase): CurrentDayStyle {
        let valueDeserializer : DeserializerBase = buffer
        const dayColor_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let dayColor_buf : ResourceColor | undefined
        if ((dayColor_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const dayColor_buf__selector : int32 = valueDeserializer.readInt8()
            let dayColor_buf_ : Color | number | string | Resource | undefined
            if (dayColor_buf__selector == (0).toChar()) {
                dayColor_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (dayColor_buf__selector == (1).toChar()) {
                dayColor_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (dayColor_buf__selector == (2).toChar()) {
                dayColor_buf_ = (valueDeserializer.readString() as string)
            }
            else if (dayColor_buf__selector == (3).toChar()) {
                dayColor_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for dayColor_buf_ has to be chosen through deserialisation.")
            }
            dayColor_buf = (dayColor_buf_ as Color | number | string | Resource)
        }
        const dayColor_result : ResourceColor | undefined = dayColor_buf
        const lunarColor_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let lunarColor_buf : ResourceColor | undefined
        if ((lunarColor_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const lunarColor_buf__selector : int32 = valueDeserializer.readInt8()
            let lunarColor_buf_ : Color | number | string | Resource | undefined
            if (lunarColor_buf__selector == (0).toChar()) {
                lunarColor_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (lunarColor_buf__selector == (1).toChar()) {
                lunarColor_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (lunarColor_buf__selector == (2).toChar()) {
                lunarColor_buf_ = (valueDeserializer.readString() as string)
            }
            else if (lunarColor_buf__selector == (3).toChar()) {
                lunarColor_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for lunarColor_buf_ has to be chosen through deserialisation.")
            }
            lunarColor_buf = (lunarColor_buf_ as Color | number | string | Resource)
        }
        const lunarColor_result : ResourceColor | undefined = lunarColor_buf
        const markLunarColor_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let markLunarColor_buf : ResourceColor | undefined
        if ((markLunarColor_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const markLunarColor_buf__selector : int32 = valueDeserializer.readInt8()
            let markLunarColor_buf_ : Color | number | string | Resource | undefined
            if (markLunarColor_buf__selector == (0).toChar()) {
                markLunarColor_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (markLunarColor_buf__selector == (1).toChar()) {
                markLunarColor_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (markLunarColor_buf__selector == (2).toChar()) {
                markLunarColor_buf_ = (valueDeserializer.readString() as string)
            }
            else if (markLunarColor_buf__selector == (3).toChar()) {
                markLunarColor_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for markLunarColor_buf_ has to be chosen through deserialisation.")
            }
            markLunarColor_buf = (markLunarColor_buf_ as Color | number | string | Resource)
        }
        const markLunarColor_result : ResourceColor | undefined = markLunarColor_buf
        const dayFontSize_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let dayFontSize_buf : number | undefined
        if ((dayFontSize_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            dayFontSize_buf = (valueDeserializer.readNumber() as number)
        }
        const dayFontSize_result : number | undefined = dayFontSize_buf
        const lunarDayFontSize_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let lunarDayFontSize_buf : number | undefined
        if ((lunarDayFontSize_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            lunarDayFontSize_buf = (valueDeserializer.readNumber() as number)
        }
        const lunarDayFontSize_result : number | undefined = lunarDayFontSize_buf
        const dayHeight_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let dayHeight_buf : number | undefined
        if ((dayHeight_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            dayHeight_buf = (valueDeserializer.readNumber() as number)
        }
        const dayHeight_result : number | undefined = dayHeight_buf
        const dayWidth_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let dayWidth_buf : number | undefined
        if ((dayWidth_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            dayWidth_buf = (valueDeserializer.readNumber() as number)
        }
        const dayWidth_result : number | undefined = dayWidth_buf
        const gregorianCalendarHeight_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let gregorianCalendarHeight_buf : number | undefined
        if ((gregorianCalendarHeight_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            gregorianCalendarHeight_buf = (valueDeserializer.readNumber() as number)
        }
        const gregorianCalendarHeight_result : number | undefined = gregorianCalendarHeight_buf
        const dayYAxisOffset_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let dayYAxisOffset_buf : number | undefined
        if ((dayYAxisOffset_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            dayYAxisOffset_buf = (valueDeserializer.readNumber() as number)
        }
        const dayYAxisOffset_result : number | undefined = dayYAxisOffset_buf
        const lunarDayYAxisOffset_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let lunarDayYAxisOffset_buf : number | undefined
        if ((lunarDayYAxisOffset_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            lunarDayYAxisOffset_buf = (valueDeserializer.readNumber() as number)
        }
        const lunarDayYAxisOffset_result : number | undefined = lunarDayYAxisOffset_buf
        const underscoreXAxisOffset_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let underscoreXAxisOffset_buf : number | undefined
        if ((underscoreXAxisOffset_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            underscoreXAxisOffset_buf = (valueDeserializer.readNumber() as number)
        }
        const underscoreXAxisOffset_result : number | undefined = underscoreXAxisOffset_buf
        const underscoreYAxisOffset_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let underscoreYAxisOffset_buf : number | undefined
        if ((underscoreYAxisOffset_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            underscoreYAxisOffset_buf = (valueDeserializer.readNumber() as number)
        }
        const underscoreYAxisOffset_result : number | undefined = underscoreYAxisOffset_buf
        const scheduleMarkerXAxisOffset_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let scheduleMarkerXAxisOffset_buf : number | undefined
        if ((scheduleMarkerXAxisOffset_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            scheduleMarkerXAxisOffset_buf = (valueDeserializer.readNumber() as number)
        }
        const scheduleMarkerXAxisOffset_result : number | undefined = scheduleMarkerXAxisOffset_buf
        const scheduleMarkerYAxisOffset_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let scheduleMarkerYAxisOffset_buf : number | undefined
        if ((scheduleMarkerYAxisOffset_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            scheduleMarkerYAxisOffset_buf = (valueDeserializer.readNumber() as number)
        }
        const scheduleMarkerYAxisOffset_result : number | undefined = scheduleMarkerYAxisOffset_buf
        const colSpace_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let colSpace_buf : number | undefined
        if ((colSpace_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            colSpace_buf = (valueDeserializer.readNumber() as number)
        }
        const colSpace_result : number | undefined = colSpace_buf
        const dailyFiveRowSpace_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let dailyFiveRowSpace_buf : number | undefined
        if ((dailyFiveRowSpace_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            dailyFiveRowSpace_buf = (valueDeserializer.readNumber() as number)
        }
        const dailyFiveRowSpace_result : number | undefined = dailyFiveRowSpace_buf
        const dailySixRowSpace_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let dailySixRowSpace_buf : number | undefined
        if ((dailySixRowSpace_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            dailySixRowSpace_buf = (valueDeserializer.readNumber() as number)
        }
        const dailySixRowSpace_result : number | undefined = dailySixRowSpace_buf
        const lunarHeight_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let lunarHeight_buf : number | undefined
        if ((lunarHeight_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            lunarHeight_buf = (valueDeserializer.readNumber() as number)
        }
        const lunarHeight_result : number | undefined = lunarHeight_buf
        const underscoreWidth_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let underscoreWidth_buf : number | undefined
        if ((underscoreWidth_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            underscoreWidth_buf = (valueDeserializer.readNumber() as number)
        }
        const underscoreWidth_result : number | undefined = underscoreWidth_buf
        const underscoreLength_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let underscoreLength_buf : number | undefined
        if ((underscoreLength_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            underscoreLength_buf = (valueDeserializer.readNumber() as number)
        }
        const underscoreLength_result : number | undefined = underscoreLength_buf
        const scheduleMarkerRadius_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let scheduleMarkerRadius_buf : number | undefined
        if ((scheduleMarkerRadius_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            scheduleMarkerRadius_buf = (valueDeserializer.readNumber() as number)
        }
        const scheduleMarkerRadius_result : number | undefined = scheduleMarkerRadius_buf
        const boundaryRowOffset_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let boundaryRowOffset_buf : number | undefined
        if ((boundaryRowOffset_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            boundaryRowOffset_buf = (valueDeserializer.readNumber() as number)
        }
        const boundaryRowOffset_result : number | undefined = boundaryRowOffset_buf
        const boundaryColOffset_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let boundaryColOffset_buf : number | undefined
        if ((boundaryColOffset_buf_runtimeType) != (RuntimeType.UNDEFINED))
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
        valueSerializer.writeInt8((value_nonCurrentMonthDayColor_type).toChar())
        if ((value_nonCurrentMonthDayColor_type) != (RuntimeType.UNDEFINED)) {
            const value_nonCurrentMonthDayColor_value  = value_nonCurrentMonthDayColor!
            let value_nonCurrentMonthDayColor_value_type : int32 = RuntimeType.UNDEFINED
            value_nonCurrentMonthDayColor_value_type = runtimeType(value_nonCurrentMonthDayColor_value)
            if (TypeChecker.isColor(value_nonCurrentMonthDayColor_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value_nonCurrentMonthDayColor_value_0  = value_nonCurrentMonthDayColor_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_nonCurrentMonthDayColor_value_0))
            }
            else if (RuntimeType.NUMBER == value_nonCurrentMonthDayColor_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_nonCurrentMonthDayColor_value_1  = value_nonCurrentMonthDayColor_value as number
                valueSerializer.writeNumber(value_nonCurrentMonthDayColor_value_1)
            }
            else if (RuntimeType.STRING == value_nonCurrentMonthDayColor_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_nonCurrentMonthDayColor_value_2  = value_nonCurrentMonthDayColor_value as string
                valueSerializer.writeString(value_nonCurrentMonthDayColor_value_2)
            }
            else if (RuntimeType.OBJECT == value_nonCurrentMonthDayColor_value_type) {
                valueSerializer.writeInt8((3).toChar())
                const value_nonCurrentMonthDayColor_value_3  = value_nonCurrentMonthDayColor_value as Resource
                Resource_serializer.write(valueSerializer, value_nonCurrentMonthDayColor_value_3)
            }
        }
        const value_nonCurrentMonthLunarColor  = value.nonCurrentMonthLunarColor
        let value_nonCurrentMonthLunarColor_type : int32 = RuntimeType.UNDEFINED
        value_nonCurrentMonthLunarColor_type = runtimeType(value_nonCurrentMonthLunarColor)
        valueSerializer.writeInt8((value_nonCurrentMonthLunarColor_type).toChar())
        if ((value_nonCurrentMonthLunarColor_type) != (RuntimeType.UNDEFINED)) {
            const value_nonCurrentMonthLunarColor_value  = value_nonCurrentMonthLunarColor!
            let value_nonCurrentMonthLunarColor_value_type : int32 = RuntimeType.UNDEFINED
            value_nonCurrentMonthLunarColor_value_type = runtimeType(value_nonCurrentMonthLunarColor_value)
            if (TypeChecker.isColor(value_nonCurrentMonthLunarColor_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value_nonCurrentMonthLunarColor_value_0  = value_nonCurrentMonthLunarColor_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_nonCurrentMonthLunarColor_value_0))
            }
            else if (RuntimeType.NUMBER == value_nonCurrentMonthLunarColor_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_nonCurrentMonthLunarColor_value_1  = value_nonCurrentMonthLunarColor_value as number
                valueSerializer.writeNumber(value_nonCurrentMonthLunarColor_value_1)
            }
            else if (RuntimeType.STRING == value_nonCurrentMonthLunarColor_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_nonCurrentMonthLunarColor_value_2  = value_nonCurrentMonthLunarColor_value as string
                valueSerializer.writeString(value_nonCurrentMonthLunarColor_value_2)
            }
            else if (RuntimeType.OBJECT == value_nonCurrentMonthLunarColor_value_type) {
                valueSerializer.writeInt8((3).toChar())
                const value_nonCurrentMonthLunarColor_value_3  = value_nonCurrentMonthLunarColor_value as Resource
                Resource_serializer.write(valueSerializer, value_nonCurrentMonthLunarColor_value_3)
            }
        }
        const value_nonCurrentMonthWorkDayMarkColor  = value.nonCurrentMonthWorkDayMarkColor
        let value_nonCurrentMonthWorkDayMarkColor_type : int32 = RuntimeType.UNDEFINED
        value_nonCurrentMonthWorkDayMarkColor_type = runtimeType(value_nonCurrentMonthWorkDayMarkColor)
        valueSerializer.writeInt8((value_nonCurrentMonthWorkDayMarkColor_type).toChar())
        if ((value_nonCurrentMonthWorkDayMarkColor_type) != (RuntimeType.UNDEFINED)) {
            const value_nonCurrentMonthWorkDayMarkColor_value  = value_nonCurrentMonthWorkDayMarkColor!
            let value_nonCurrentMonthWorkDayMarkColor_value_type : int32 = RuntimeType.UNDEFINED
            value_nonCurrentMonthWorkDayMarkColor_value_type = runtimeType(value_nonCurrentMonthWorkDayMarkColor_value)
            if (TypeChecker.isColor(value_nonCurrentMonthWorkDayMarkColor_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value_nonCurrentMonthWorkDayMarkColor_value_0  = value_nonCurrentMonthWorkDayMarkColor_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_nonCurrentMonthWorkDayMarkColor_value_0))
            }
            else if (RuntimeType.NUMBER == value_nonCurrentMonthWorkDayMarkColor_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_nonCurrentMonthWorkDayMarkColor_value_1  = value_nonCurrentMonthWorkDayMarkColor_value as number
                valueSerializer.writeNumber(value_nonCurrentMonthWorkDayMarkColor_value_1)
            }
            else if (RuntimeType.STRING == value_nonCurrentMonthWorkDayMarkColor_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_nonCurrentMonthWorkDayMarkColor_value_2  = value_nonCurrentMonthWorkDayMarkColor_value as string
                valueSerializer.writeString(value_nonCurrentMonthWorkDayMarkColor_value_2)
            }
            else if (RuntimeType.OBJECT == value_nonCurrentMonthWorkDayMarkColor_value_type) {
                valueSerializer.writeInt8((3).toChar())
                const value_nonCurrentMonthWorkDayMarkColor_value_3  = value_nonCurrentMonthWorkDayMarkColor_value as Resource
                Resource_serializer.write(valueSerializer, value_nonCurrentMonthWorkDayMarkColor_value_3)
            }
        }
        const value_nonCurrentMonthOffDayMarkColor  = value.nonCurrentMonthOffDayMarkColor
        let value_nonCurrentMonthOffDayMarkColor_type : int32 = RuntimeType.UNDEFINED
        value_nonCurrentMonthOffDayMarkColor_type = runtimeType(value_nonCurrentMonthOffDayMarkColor)
        valueSerializer.writeInt8((value_nonCurrentMonthOffDayMarkColor_type).toChar())
        if ((value_nonCurrentMonthOffDayMarkColor_type) != (RuntimeType.UNDEFINED)) {
            const value_nonCurrentMonthOffDayMarkColor_value  = value_nonCurrentMonthOffDayMarkColor!
            let value_nonCurrentMonthOffDayMarkColor_value_type : int32 = RuntimeType.UNDEFINED
            value_nonCurrentMonthOffDayMarkColor_value_type = runtimeType(value_nonCurrentMonthOffDayMarkColor_value)
            if (TypeChecker.isColor(value_nonCurrentMonthOffDayMarkColor_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value_nonCurrentMonthOffDayMarkColor_value_0  = value_nonCurrentMonthOffDayMarkColor_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_nonCurrentMonthOffDayMarkColor_value_0))
            }
            else if (RuntimeType.NUMBER == value_nonCurrentMonthOffDayMarkColor_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_nonCurrentMonthOffDayMarkColor_value_1  = value_nonCurrentMonthOffDayMarkColor_value as number
                valueSerializer.writeNumber(value_nonCurrentMonthOffDayMarkColor_value_1)
            }
            else if (RuntimeType.STRING == value_nonCurrentMonthOffDayMarkColor_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_nonCurrentMonthOffDayMarkColor_value_2  = value_nonCurrentMonthOffDayMarkColor_value as string
                valueSerializer.writeString(value_nonCurrentMonthOffDayMarkColor_value_2)
            }
            else if (RuntimeType.OBJECT == value_nonCurrentMonthOffDayMarkColor_value_type) {
                valueSerializer.writeInt8((3).toChar())
                const value_nonCurrentMonthOffDayMarkColor_value_3  = value_nonCurrentMonthOffDayMarkColor_value as Resource
                Resource_serializer.write(valueSerializer, value_nonCurrentMonthOffDayMarkColor_value_3)
            }
        }
    }
    public static read(buffer: DeserializerBase): NonCurrentDayStyle {
        let valueDeserializer : DeserializerBase = buffer
        const nonCurrentMonthDayColor_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let nonCurrentMonthDayColor_buf : ResourceColor | undefined
        if ((nonCurrentMonthDayColor_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const nonCurrentMonthDayColor_buf__selector : int32 = valueDeserializer.readInt8()
            let nonCurrentMonthDayColor_buf_ : Color | number | string | Resource | undefined
            if (nonCurrentMonthDayColor_buf__selector == (0).toChar()) {
                nonCurrentMonthDayColor_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (nonCurrentMonthDayColor_buf__selector == (1).toChar()) {
                nonCurrentMonthDayColor_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (nonCurrentMonthDayColor_buf__selector == (2).toChar()) {
                nonCurrentMonthDayColor_buf_ = (valueDeserializer.readString() as string)
            }
            else if (nonCurrentMonthDayColor_buf__selector == (3).toChar()) {
                nonCurrentMonthDayColor_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for nonCurrentMonthDayColor_buf_ has to be chosen through deserialisation.")
            }
            nonCurrentMonthDayColor_buf = (nonCurrentMonthDayColor_buf_ as Color | number | string | Resource)
        }
        const nonCurrentMonthDayColor_result : ResourceColor | undefined = nonCurrentMonthDayColor_buf
        const nonCurrentMonthLunarColor_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let nonCurrentMonthLunarColor_buf : ResourceColor | undefined
        if ((nonCurrentMonthLunarColor_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const nonCurrentMonthLunarColor_buf__selector : int32 = valueDeserializer.readInt8()
            let nonCurrentMonthLunarColor_buf_ : Color | number | string | Resource | undefined
            if (nonCurrentMonthLunarColor_buf__selector == (0).toChar()) {
                nonCurrentMonthLunarColor_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (nonCurrentMonthLunarColor_buf__selector == (1).toChar()) {
                nonCurrentMonthLunarColor_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (nonCurrentMonthLunarColor_buf__selector == (2).toChar()) {
                nonCurrentMonthLunarColor_buf_ = (valueDeserializer.readString() as string)
            }
            else if (nonCurrentMonthLunarColor_buf__selector == (3).toChar()) {
                nonCurrentMonthLunarColor_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for nonCurrentMonthLunarColor_buf_ has to be chosen through deserialisation.")
            }
            nonCurrentMonthLunarColor_buf = (nonCurrentMonthLunarColor_buf_ as Color | number | string | Resource)
        }
        const nonCurrentMonthLunarColor_result : ResourceColor | undefined = nonCurrentMonthLunarColor_buf
        const nonCurrentMonthWorkDayMarkColor_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let nonCurrentMonthWorkDayMarkColor_buf : ResourceColor | undefined
        if ((nonCurrentMonthWorkDayMarkColor_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const nonCurrentMonthWorkDayMarkColor_buf__selector : int32 = valueDeserializer.readInt8()
            let nonCurrentMonthWorkDayMarkColor_buf_ : Color | number | string | Resource | undefined
            if (nonCurrentMonthWorkDayMarkColor_buf__selector == (0).toChar()) {
                nonCurrentMonthWorkDayMarkColor_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (nonCurrentMonthWorkDayMarkColor_buf__selector == (1).toChar()) {
                nonCurrentMonthWorkDayMarkColor_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (nonCurrentMonthWorkDayMarkColor_buf__selector == (2).toChar()) {
                nonCurrentMonthWorkDayMarkColor_buf_ = (valueDeserializer.readString() as string)
            }
            else if (nonCurrentMonthWorkDayMarkColor_buf__selector == (3).toChar()) {
                nonCurrentMonthWorkDayMarkColor_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for nonCurrentMonthWorkDayMarkColor_buf_ has to be chosen through deserialisation.")
            }
            nonCurrentMonthWorkDayMarkColor_buf = (nonCurrentMonthWorkDayMarkColor_buf_ as Color | number | string | Resource)
        }
        const nonCurrentMonthWorkDayMarkColor_result : ResourceColor | undefined = nonCurrentMonthWorkDayMarkColor_buf
        const nonCurrentMonthOffDayMarkColor_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let nonCurrentMonthOffDayMarkColor_buf : ResourceColor | undefined
        if ((nonCurrentMonthOffDayMarkColor_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const nonCurrentMonthOffDayMarkColor_buf__selector : int32 = valueDeserializer.readInt8()
            let nonCurrentMonthOffDayMarkColor_buf_ : Color | number | string | Resource | undefined
            if (nonCurrentMonthOffDayMarkColor_buf__selector == (0).toChar()) {
                nonCurrentMonthOffDayMarkColor_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (nonCurrentMonthOffDayMarkColor_buf__selector == (1).toChar()) {
                nonCurrentMonthOffDayMarkColor_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (nonCurrentMonthOffDayMarkColor_buf__selector == (2).toChar()) {
                nonCurrentMonthOffDayMarkColor_buf_ = (valueDeserializer.readString() as string)
            }
            else if (nonCurrentMonthOffDayMarkColor_buf__selector == (3).toChar()) {
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
        valueSerializer.writeInt8((value_focusedDayColor_type).toChar())
        if ((value_focusedDayColor_type) != (RuntimeType.UNDEFINED)) {
            const value_focusedDayColor_value  = value_focusedDayColor!
            let value_focusedDayColor_value_type : int32 = RuntimeType.UNDEFINED
            value_focusedDayColor_value_type = runtimeType(value_focusedDayColor_value)
            if (TypeChecker.isColor(value_focusedDayColor_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value_focusedDayColor_value_0  = value_focusedDayColor_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_focusedDayColor_value_0))
            }
            else if (RuntimeType.NUMBER == value_focusedDayColor_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_focusedDayColor_value_1  = value_focusedDayColor_value as number
                valueSerializer.writeNumber(value_focusedDayColor_value_1)
            }
            else if (RuntimeType.STRING == value_focusedDayColor_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_focusedDayColor_value_2  = value_focusedDayColor_value as string
                valueSerializer.writeString(value_focusedDayColor_value_2)
            }
            else if (RuntimeType.OBJECT == value_focusedDayColor_value_type) {
                valueSerializer.writeInt8((3).toChar())
                const value_focusedDayColor_value_3  = value_focusedDayColor_value as Resource
                Resource_serializer.write(valueSerializer, value_focusedDayColor_value_3)
            }
        }
        const value_focusedLunarColor  = value.focusedLunarColor
        let value_focusedLunarColor_type : int32 = RuntimeType.UNDEFINED
        value_focusedLunarColor_type = runtimeType(value_focusedLunarColor)
        valueSerializer.writeInt8((value_focusedLunarColor_type).toChar())
        if ((value_focusedLunarColor_type) != (RuntimeType.UNDEFINED)) {
            const value_focusedLunarColor_value  = value_focusedLunarColor!
            let value_focusedLunarColor_value_type : int32 = RuntimeType.UNDEFINED
            value_focusedLunarColor_value_type = runtimeType(value_focusedLunarColor_value)
            if (TypeChecker.isColor(value_focusedLunarColor_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value_focusedLunarColor_value_0  = value_focusedLunarColor_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_focusedLunarColor_value_0))
            }
            else if (RuntimeType.NUMBER == value_focusedLunarColor_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_focusedLunarColor_value_1  = value_focusedLunarColor_value as number
                valueSerializer.writeNumber(value_focusedLunarColor_value_1)
            }
            else if (RuntimeType.STRING == value_focusedLunarColor_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_focusedLunarColor_value_2  = value_focusedLunarColor_value as string
                valueSerializer.writeString(value_focusedLunarColor_value_2)
            }
            else if (RuntimeType.OBJECT == value_focusedLunarColor_value_type) {
                valueSerializer.writeInt8((3).toChar())
                const value_focusedLunarColor_value_3  = value_focusedLunarColor_value as Resource
                Resource_serializer.write(valueSerializer, value_focusedLunarColor_value_3)
            }
        }
        const value_focusedAreaBackgroundColor  = value.focusedAreaBackgroundColor
        let value_focusedAreaBackgroundColor_type : int32 = RuntimeType.UNDEFINED
        value_focusedAreaBackgroundColor_type = runtimeType(value_focusedAreaBackgroundColor)
        valueSerializer.writeInt8((value_focusedAreaBackgroundColor_type).toChar())
        if ((value_focusedAreaBackgroundColor_type) != (RuntimeType.UNDEFINED)) {
            const value_focusedAreaBackgroundColor_value  = value_focusedAreaBackgroundColor!
            let value_focusedAreaBackgroundColor_value_type : int32 = RuntimeType.UNDEFINED
            value_focusedAreaBackgroundColor_value_type = runtimeType(value_focusedAreaBackgroundColor_value)
            if (TypeChecker.isColor(value_focusedAreaBackgroundColor_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value_focusedAreaBackgroundColor_value_0  = value_focusedAreaBackgroundColor_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_focusedAreaBackgroundColor_value_0))
            }
            else if (RuntimeType.NUMBER == value_focusedAreaBackgroundColor_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_focusedAreaBackgroundColor_value_1  = value_focusedAreaBackgroundColor_value as number
                valueSerializer.writeNumber(value_focusedAreaBackgroundColor_value_1)
            }
            else if (RuntimeType.STRING == value_focusedAreaBackgroundColor_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_focusedAreaBackgroundColor_value_2  = value_focusedAreaBackgroundColor_value as string
                valueSerializer.writeString(value_focusedAreaBackgroundColor_value_2)
            }
            else if (RuntimeType.OBJECT == value_focusedAreaBackgroundColor_value_type) {
                valueSerializer.writeInt8((3).toChar())
                const value_focusedAreaBackgroundColor_value_3  = value_focusedAreaBackgroundColor_value as Resource
                Resource_serializer.write(valueSerializer, value_focusedAreaBackgroundColor_value_3)
            }
        }
        const value_focusedAreaRadius  = value.focusedAreaRadius
        let value_focusedAreaRadius_type : int32 = RuntimeType.UNDEFINED
        value_focusedAreaRadius_type = runtimeType(value_focusedAreaRadius)
        valueSerializer.writeInt8((value_focusedAreaRadius_type).toChar())
        if ((value_focusedAreaRadius_type) != (RuntimeType.UNDEFINED)) {
            const value_focusedAreaRadius_value  = value_focusedAreaRadius!
            valueSerializer.writeNumber(value_focusedAreaRadius_value)
        }
    }
    public static read(buffer: DeserializerBase): TodayStyle {
        let valueDeserializer : DeserializerBase = buffer
        const focusedDayColor_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let focusedDayColor_buf : ResourceColor | undefined
        if ((focusedDayColor_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const focusedDayColor_buf__selector : int32 = valueDeserializer.readInt8()
            let focusedDayColor_buf_ : Color | number | string | Resource | undefined
            if (focusedDayColor_buf__selector == (0).toChar()) {
                focusedDayColor_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (focusedDayColor_buf__selector == (1).toChar()) {
                focusedDayColor_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (focusedDayColor_buf__selector == (2).toChar()) {
                focusedDayColor_buf_ = (valueDeserializer.readString() as string)
            }
            else if (focusedDayColor_buf__selector == (3).toChar()) {
                focusedDayColor_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for focusedDayColor_buf_ has to be chosen through deserialisation.")
            }
            focusedDayColor_buf = (focusedDayColor_buf_ as Color | number | string | Resource)
        }
        const focusedDayColor_result : ResourceColor | undefined = focusedDayColor_buf
        const focusedLunarColor_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let focusedLunarColor_buf : ResourceColor | undefined
        if ((focusedLunarColor_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const focusedLunarColor_buf__selector : int32 = valueDeserializer.readInt8()
            let focusedLunarColor_buf_ : Color | number | string | Resource | undefined
            if (focusedLunarColor_buf__selector == (0).toChar()) {
                focusedLunarColor_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (focusedLunarColor_buf__selector == (1).toChar()) {
                focusedLunarColor_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (focusedLunarColor_buf__selector == (2).toChar()) {
                focusedLunarColor_buf_ = (valueDeserializer.readString() as string)
            }
            else if (focusedLunarColor_buf__selector == (3).toChar()) {
                focusedLunarColor_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for focusedLunarColor_buf_ has to be chosen through deserialisation.")
            }
            focusedLunarColor_buf = (focusedLunarColor_buf_ as Color | number | string | Resource)
        }
        const focusedLunarColor_result : ResourceColor | undefined = focusedLunarColor_buf
        const focusedAreaBackgroundColor_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let focusedAreaBackgroundColor_buf : ResourceColor | undefined
        if ((focusedAreaBackgroundColor_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const focusedAreaBackgroundColor_buf__selector : int32 = valueDeserializer.readInt8()
            let focusedAreaBackgroundColor_buf_ : Color | number | string | Resource | undefined
            if (focusedAreaBackgroundColor_buf__selector == (0).toChar()) {
                focusedAreaBackgroundColor_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (focusedAreaBackgroundColor_buf__selector == (1).toChar()) {
                focusedAreaBackgroundColor_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (focusedAreaBackgroundColor_buf__selector == (2).toChar()) {
                focusedAreaBackgroundColor_buf_ = (valueDeserializer.readString() as string)
            }
            else if (focusedAreaBackgroundColor_buf__selector == (3).toChar()) {
                focusedAreaBackgroundColor_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for focusedAreaBackgroundColor_buf_ has to be chosen through deserialisation.")
            }
            focusedAreaBackgroundColor_buf = (focusedAreaBackgroundColor_buf_ as Color | number | string | Resource)
        }
        const focusedAreaBackgroundColor_result : ResourceColor | undefined = focusedAreaBackgroundColor_buf
        const focusedAreaRadius_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let focusedAreaRadius_buf : number | undefined
        if ((focusedAreaRadius_buf_runtimeType) != (RuntimeType.UNDEFINED))
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
        valueSerializer.writeInt8((value_weekColor_type).toChar())
        if ((value_weekColor_type) != (RuntimeType.UNDEFINED)) {
            const value_weekColor_value  = value_weekColor!
            let value_weekColor_value_type : int32 = RuntimeType.UNDEFINED
            value_weekColor_value_type = runtimeType(value_weekColor_value)
            if (TypeChecker.isColor(value_weekColor_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value_weekColor_value_0  = value_weekColor_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_weekColor_value_0))
            }
            else if (RuntimeType.NUMBER == value_weekColor_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_weekColor_value_1  = value_weekColor_value as number
                valueSerializer.writeNumber(value_weekColor_value_1)
            }
            else if (RuntimeType.STRING == value_weekColor_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_weekColor_value_2  = value_weekColor_value as string
                valueSerializer.writeString(value_weekColor_value_2)
            }
            else if (RuntimeType.OBJECT == value_weekColor_value_type) {
                valueSerializer.writeInt8((3).toChar())
                const value_weekColor_value_3  = value_weekColor_value as Resource
                Resource_serializer.write(valueSerializer, value_weekColor_value_3)
            }
        }
        const value_weekendDayColor  = value.weekendDayColor
        let value_weekendDayColor_type : int32 = RuntimeType.UNDEFINED
        value_weekendDayColor_type = runtimeType(value_weekendDayColor)
        valueSerializer.writeInt8((value_weekendDayColor_type).toChar())
        if ((value_weekendDayColor_type) != (RuntimeType.UNDEFINED)) {
            const value_weekendDayColor_value  = value_weekendDayColor!
            let value_weekendDayColor_value_type : int32 = RuntimeType.UNDEFINED
            value_weekendDayColor_value_type = runtimeType(value_weekendDayColor_value)
            if (TypeChecker.isColor(value_weekendDayColor_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value_weekendDayColor_value_0  = value_weekendDayColor_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_weekendDayColor_value_0))
            }
            else if (RuntimeType.NUMBER == value_weekendDayColor_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_weekendDayColor_value_1  = value_weekendDayColor_value as number
                valueSerializer.writeNumber(value_weekendDayColor_value_1)
            }
            else if (RuntimeType.STRING == value_weekendDayColor_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_weekendDayColor_value_2  = value_weekendDayColor_value as string
                valueSerializer.writeString(value_weekendDayColor_value_2)
            }
            else if (RuntimeType.OBJECT == value_weekendDayColor_value_type) {
                valueSerializer.writeInt8((3).toChar())
                const value_weekendDayColor_value_3  = value_weekendDayColor_value as Resource
                Resource_serializer.write(valueSerializer, value_weekendDayColor_value_3)
            }
        }
        const value_weekendLunarColor  = value.weekendLunarColor
        let value_weekendLunarColor_type : int32 = RuntimeType.UNDEFINED
        value_weekendLunarColor_type = runtimeType(value_weekendLunarColor)
        valueSerializer.writeInt8((value_weekendLunarColor_type).toChar())
        if ((value_weekendLunarColor_type) != (RuntimeType.UNDEFINED)) {
            const value_weekendLunarColor_value  = value_weekendLunarColor!
            let value_weekendLunarColor_value_type : int32 = RuntimeType.UNDEFINED
            value_weekendLunarColor_value_type = runtimeType(value_weekendLunarColor_value)
            if (TypeChecker.isColor(value_weekendLunarColor_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value_weekendLunarColor_value_0  = value_weekendLunarColor_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_weekendLunarColor_value_0))
            }
            else if (RuntimeType.NUMBER == value_weekendLunarColor_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_weekendLunarColor_value_1  = value_weekendLunarColor_value as number
                valueSerializer.writeNumber(value_weekendLunarColor_value_1)
            }
            else if (RuntimeType.STRING == value_weekendLunarColor_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_weekendLunarColor_value_2  = value_weekendLunarColor_value as string
                valueSerializer.writeString(value_weekendLunarColor_value_2)
            }
            else if (RuntimeType.OBJECT == value_weekendLunarColor_value_type) {
                valueSerializer.writeInt8((3).toChar())
                const value_weekendLunarColor_value_3  = value_weekendLunarColor_value as Resource
                Resource_serializer.write(valueSerializer, value_weekendLunarColor_value_3)
            }
        }
        const value_weekFontSize  = value.weekFontSize
        let value_weekFontSize_type : int32 = RuntimeType.UNDEFINED
        value_weekFontSize_type = runtimeType(value_weekFontSize)
        valueSerializer.writeInt8((value_weekFontSize_type).toChar())
        if ((value_weekFontSize_type) != (RuntimeType.UNDEFINED)) {
            const value_weekFontSize_value  = value_weekFontSize!
            valueSerializer.writeNumber(value_weekFontSize_value)
        }
        const value_weekHeight  = value.weekHeight
        let value_weekHeight_type : int32 = RuntimeType.UNDEFINED
        value_weekHeight_type = runtimeType(value_weekHeight)
        valueSerializer.writeInt8((value_weekHeight_type).toChar())
        if ((value_weekHeight_type) != (RuntimeType.UNDEFINED)) {
            const value_weekHeight_value  = value_weekHeight!
            valueSerializer.writeNumber(value_weekHeight_value)
        }
        const value_weekWidth  = value.weekWidth
        let value_weekWidth_type : int32 = RuntimeType.UNDEFINED
        value_weekWidth_type = runtimeType(value_weekWidth)
        valueSerializer.writeInt8((value_weekWidth_type).toChar())
        if ((value_weekWidth_type) != (RuntimeType.UNDEFINED)) {
            const value_weekWidth_value  = value_weekWidth!
            valueSerializer.writeNumber(value_weekWidth_value)
        }
        const value_weekAndDayRowSpace  = value.weekAndDayRowSpace
        let value_weekAndDayRowSpace_type : int32 = RuntimeType.UNDEFINED
        value_weekAndDayRowSpace_type = runtimeType(value_weekAndDayRowSpace)
        valueSerializer.writeInt8((value_weekAndDayRowSpace_type).toChar())
        if ((value_weekAndDayRowSpace_type) != (RuntimeType.UNDEFINED)) {
            const value_weekAndDayRowSpace_value  = value_weekAndDayRowSpace!
            valueSerializer.writeNumber(value_weekAndDayRowSpace_value)
        }
    }
    public static read(buffer: DeserializerBase): WeekStyle {
        let valueDeserializer : DeserializerBase = buffer
        const weekColor_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let weekColor_buf : ResourceColor | undefined
        if ((weekColor_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const weekColor_buf__selector : int32 = valueDeserializer.readInt8()
            let weekColor_buf_ : Color | number | string | Resource | undefined
            if (weekColor_buf__selector == (0).toChar()) {
                weekColor_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (weekColor_buf__selector == (1).toChar()) {
                weekColor_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (weekColor_buf__selector == (2).toChar()) {
                weekColor_buf_ = (valueDeserializer.readString() as string)
            }
            else if (weekColor_buf__selector == (3).toChar()) {
                weekColor_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for weekColor_buf_ has to be chosen through deserialisation.")
            }
            weekColor_buf = (weekColor_buf_ as Color | number | string | Resource)
        }
        const weekColor_result : ResourceColor | undefined = weekColor_buf
        const weekendDayColor_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let weekendDayColor_buf : ResourceColor | undefined
        if ((weekendDayColor_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const weekendDayColor_buf__selector : int32 = valueDeserializer.readInt8()
            let weekendDayColor_buf_ : Color | number | string | Resource | undefined
            if (weekendDayColor_buf__selector == (0).toChar()) {
                weekendDayColor_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (weekendDayColor_buf__selector == (1).toChar()) {
                weekendDayColor_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (weekendDayColor_buf__selector == (2).toChar()) {
                weekendDayColor_buf_ = (valueDeserializer.readString() as string)
            }
            else if (weekendDayColor_buf__selector == (3).toChar()) {
                weekendDayColor_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for weekendDayColor_buf_ has to be chosen through deserialisation.")
            }
            weekendDayColor_buf = (weekendDayColor_buf_ as Color | number | string | Resource)
        }
        const weekendDayColor_result : ResourceColor | undefined = weekendDayColor_buf
        const weekendLunarColor_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let weekendLunarColor_buf : ResourceColor | undefined
        if ((weekendLunarColor_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const weekendLunarColor_buf__selector : int32 = valueDeserializer.readInt8()
            let weekendLunarColor_buf_ : Color | number | string | Resource | undefined
            if (weekendLunarColor_buf__selector == (0).toChar()) {
                weekendLunarColor_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (weekendLunarColor_buf__selector == (1).toChar()) {
                weekendLunarColor_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (weekendLunarColor_buf__selector == (2).toChar()) {
                weekendLunarColor_buf_ = (valueDeserializer.readString() as string)
            }
            else if (weekendLunarColor_buf__selector == (3).toChar()) {
                weekendLunarColor_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for weekendLunarColor_buf_ has to be chosen through deserialisation.")
            }
            weekendLunarColor_buf = (weekendLunarColor_buf_ as Color | number | string | Resource)
        }
        const weekendLunarColor_result : ResourceColor | undefined = weekendLunarColor_buf
        const weekFontSize_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let weekFontSize_buf : number | undefined
        if ((weekFontSize_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            weekFontSize_buf = (valueDeserializer.readNumber() as number)
        }
        const weekFontSize_result : number | undefined = weekFontSize_buf
        const weekHeight_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let weekHeight_buf : number | undefined
        if ((weekHeight_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            weekHeight_buf = (valueDeserializer.readNumber() as number)
        }
        const weekHeight_result : number | undefined = weekHeight_buf
        const weekWidth_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let weekWidth_buf : number | undefined
        if ((weekWidth_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            weekWidth_buf = (valueDeserializer.readNumber() as number)
        }
        const weekWidth_result : number | undefined = weekWidth_buf
        const weekAndDayRowSpace_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let weekAndDayRowSpace_buf : number | undefined
        if ((weekAndDayRowSpace_buf_runtimeType) != (RuntimeType.UNDEFINED))
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
        valueSerializer.writeInt8((value_workDayMarkColor_type).toChar())
        if ((value_workDayMarkColor_type) != (RuntimeType.UNDEFINED)) {
            const value_workDayMarkColor_value  = value_workDayMarkColor!
            let value_workDayMarkColor_value_type : int32 = RuntimeType.UNDEFINED
            value_workDayMarkColor_value_type = runtimeType(value_workDayMarkColor_value)
            if (TypeChecker.isColor(value_workDayMarkColor_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value_workDayMarkColor_value_0  = value_workDayMarkColor_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_workDayMarkColor_value_0))
            }
            else if (RuntimeType.NUMBER == value_workDayMarkColor_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_workDayMarkColor_value_1  = value_workDayMarkColor_value as number
                valueSerializer.writeNumber(value_workDayMarkColor_value_1)
            }
            else if (RuntimeType.STRING == value_workDayMarkColor_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_workDayMarkColor_value_2  = value_workDayMarkColor_value as string
                valueSerializer.writeString(value_workDayMarkColor_value_2)
            }
            else if (RuntimeType.OBJECT == value_workDayMarkColor_value_type) {
                valueSerializer.writeInt8((3).toChar())
                const value_workDayMarkColor_value_3  = value_workDayMarkColor_value as Resource
                Resource_serializer.write(valueSerializer, value_workDayMarkColor_value_3)
            }
        }
        const value_offDayMarkColor  = value.offDayMarkColor
        let value_offDayMarkColor_type : int32 = RuntimeType.UNDEFINED
        value_offDayMarkColor_type = runtimeType(value_offDayMarkColor)
        valueSerializer.writeInt8((value_offDayMarkColor_type).toChar())
        if ((value_offDayMarkColor_type) != (RuntimeType.UNDEFINED)) {
            const value_offDayMarkColor_value  = value_offDayMarkColor!
            let value_offDayMarkColor_value_type : int32 = RuntimeType.UNDEFINED
            value_offDayMarkColor_value_type = runtimeType(value_offDayMarkColor_value)
            if (TypeChecker.isColor(value_offDayMarkColor_value)) {
                valueSerializer.writeInt8((0).toChar())
                const value_offDayMarkColor_value_0  = value_offDayMarkColor_value as Color
                valueSerializer.writeInt32(TypeChecker.Color_ToNumeric(value_offDayMarkColor_value_0))
            }
            else if (RuntimeType.NUMBER == value_offDayMarkColor_value_type) {
                valueSerializer.writeInt8((1).toChar())
                const value_offDayMarkColor_value_1  = value_offDayMarkColor_value as number
                valueSerializer.writeNumber(value_offDayMarkColor_value_1)
            }
            else if (RuntimeType.STRING == value_offDayMarkColor_value_type) {
                valueSerializer.writeInt8((2).toChar())
                const value_offDayMarkColor_value_2  = value_offDayMarkColor_value as string
                valueSerializer.writeString(value_offDayMarkColor_value_2)
            }
            else if (RuntimeType.OBJECT == value_offDayMarkColor_value_type) {
                valueSerializer.writeInt8((3).toChar())
                const value_offDayMarkColor_value_3  = value_offDayMarkColor_value as Resource
                Resource_serializer.write(valueSerializer, value_offDayMarkColor_value_3)
            }
        }
        const value_workDayMarkSize  = value.workDayMarkSize
        let value_workDayMarkSize_type : int32 = RuntimeType.UNDEFINED
        value_workDayMarkSize_type = runtimeType(value_workDayMarkSize)
        valueSerializer.writeInt8((value_workDayMarkSize_type).toChar())
        if ((value_workDayMarkSize_type) != (RuntimeType.UNDEFINED)) {
            const value_workDayMarkSize_value  = value_workDayMarkSize!
            valueSerializer.writeNumber(value_workDayMarkSize_value)
        }
        const value_offDayMarkSize  = value.offDayMarkSize
        let value_offDayMarkSize_type : int32 = RuntimeType.UNDEFINED
        value_offDayMarkSize_type = runtimeType(value_offDayMarkSize)
        valueSerializer.writeInt8((value_offDayMarkSize_type).toChar())
        if ((value_offDayMarkSize_type) != (RuntimeType.UNDEFINED)) {
            const value_offDayMarkSize_value  = value_offDayMarkSize!
            valueSerializer.writeNumber(value_offDayMarkSize_value)
        }
        const value_workStateWidth  = value.workStateWidth
        let value_workStateWidth_type : int32 = RuntimeType.UNDEFINED
        value_workStateWidth_type = runtimeType(value_workStateWidth)
        valueSerializer.writeInt8((value_workStateWidth_type).toChar())
        if ((value_workStateWidth_type) != (RuntimeType.UNDEFINED)) {
            const value_workStateWidth_value  = value_workStateWidth!
            valueSerializer.writeNumber(value_workStateWidth_value)
        }
        const value_workStateHorizontalMovingDistance  = value.workStateHorizontalMovingDistance
        let value_workStateHorizontalMovingDistance_type : int32 = RuntimeType.UNDEFINED
        value_workStateHorizontalMovingDistance_type = runtimeType(value_workStateHorizontalMovingDistance)
        valueSerializer.writeInt8((value_workStateHorizontalMovingDistance_type).toChar())
        if ((value_workStateHorizontalMovingDistance_type) != (RuntimeType.UNDEFINED)) {
            const value_workStateHorizontalMovingDistance_value  = value_workStateHorizontalMovingDistance!
            valueSerializer.writeNumber(value_workStateHorizontalMovingDistance_value)
        }
        const value_workStateVerticalMovingDistance  = value.workStateVerticalMovingDistance
        let value_workStateVerticalMovingDistance_type : int32 = RuntimeType.UNDEFINED
        value_workStateVerticalMovingDistance_type = runtimeType(value_workStateVerticalMovingDistance)
        valueSerializer.writeInt8((value_workStateVerticalMovingDistance_type).toChar())
        if ((value_workStateVerticalMovingDistance_type) != (RuntimeType.UNDEFINED)) {
            const value_workStateVerticalMovingDistance_value  = value_workStateVerticalMovingDistance!
            valueSerializer.writeNumber(value_workStateVerticalMovingDistance_value)
        }
    }
    public static read(buffer: DeserializerBase): WorkStateStyle {
        let valueDeserializer : DeserializerBase = buffer
        const workDayMarkColor_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let workDayMarkColor_buf : ResourceColor | undefined
        if ((workDayMarkColor_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const workDayMarkColor_buf__selector : int32 = valueDeserializer.readInt8()
            let workDayMarkColor_buf_ : Color | number | string | Resource | undefined
            if (workDayMarkColor_buf__selector == (0).toChar()) {
                workDayMarkColor_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (workDayMarkColor_buf__selector == (1).toChar()) {
                workDayMarkColor_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (workDayMarkColor_buf__selector == (2).toChar()) {
                workDayMarkColor_buf_ = (valueDeserializer.readString() as string)
            }
            else if (workDayMarkColor_buf__selector == (3).toChar()) {
                workDayMarkColor_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for workDayMarkColor_buf_ has to be chosen through deserialisation.")
            }
            workDayMarkColor_buf = (workDayMarkColor_buf_ as Color | number | string | Resource)
        }
        const workDayMarkColor_result : ResourceColor | undefined = workDayMarkColor_buf
        const offDayMarkColor_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let offDayMarkColor_buf : ResourceColor | undefined
        if ((offDayMarkColor_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            const offDayMarkColor_buf__selector : int32 = valueDeserializer.readInt8()
            let offDayMarkColor_buf_ : Color | number | string | Resource | undefined
            if (offDayMarkColor_buf__selector == (0).toChar()) {
                offDayMarkColor_buf_ = TypeChecker.Color_FromNumeric(valueDeserializer.readInt32())
            }
            else if (offDayMarkColor_buf__selector == (1).toChar()) {
                offDayMarkColor_buf_ = (valueDeserializer.readNumber() as number)
            }
            else if (offDayMarkColor_buf__selector == (2).toChar()) {
                offDayMarkColor_buf_ = (valueDeserializer.readString() as string)
            }
            else if (offDayMarkColor_buf__selector == (3).toChar()) {
                offDayMarkColor_buf_ = Resource_serializer.read(valueDeserializer)
            }
            else {
                throw new Error("One of the branches for offDayMarkColor_buf_ has to be chosen through deserialisation.")
            }
            offDayMarkColor_buf = (offDayMarkColor_buf_ as Color | number | string | Resource)
        }
        const offDayMarkColor_result : ResourceColor | undefined = offDayMarkColor_buf
        const workDayMarkSize_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let workDayMarkSize_buf : number | undefined
        if ((workDayMarkSize_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            workDayMarkSize_buf = (valueDeserializer.readNumber() as number)
        }
        const workDayMarkSize_result : number | undefined = workDayMarkSize_buf
        const offDayMarkSize_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let offDayMarkSize_buf : number | undefined
        if ((offDayMarkSize_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            offDayMarkSize_buf = (valueDeserializer.readNumber() as number)
        }
        const offDayMarkSize_result : number | undefined = offDayMarkSize_buf
        const workStateWidth_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let workStateWidth_buf : number | undefined
        if ((workStateWidth_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            workStateWidth_buf = (valueDeserializer.readNumber() as number)
        }
        const workStateWidth_result : number | undefined = workStateWidth_buf
        const workStateHorizontalMovingDistance_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let workStateHorizontalMovingDistance_buf : number | undefined
        if ((workStateHorizontalMovingDistance_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            workStateHorizontalMovingDistance_buf = (valueDeserializer.readNumber() as number)
        }
        const workStateHorizontalMovingDistance_result : number | undefined = workStateHorizontalMovingDistance_buf
        const workStateVerticalMovingDistance_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let workStateVerticalMovingDistance_buf : number | undefined
        if ((workStateVerticalMovingDistance_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            workStateVerticalMovingDistance_buf = (valueDeserializer.readNumber() as number)
        }
        const workStateVerticalMovingDistance_result : number | undefined = workStateVerticalMovingDistance_buf
        let value : WorkStateStyle = ({workDayMarkColor: workDayMarkColor_result, offDayMarkColor: offDayMarkColor_result, workDayMarkSize: workDayMarkSize_result, offDayMarkSize: offDayMarkSize_result, workStateWidth: workStateWidth_result, workStateHorizontalMovingDistance: workStateHorizontalMovingDistance_result, workStateVerticalMovingDistance: workStateVerticalMovingDistance_result} as WorkStateStyle)
        return value
    }
}
