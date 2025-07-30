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

import { int32, float32, unsafeCast } from "@koalaui/common"
import { KStringPtr, KBoolean, RuntimeType, runtimeType, isInstanceOf } from "@koalaui/interop"
import { NodeAttach, remember } from "@koalaui/runtime"
import { ComponentBase } from "./../ComponentBase"
import { isResource, isPadding } from "./../utils"
import { ArkCalendarPeer } from "./peers/ArkCalendarPeer"
import { Axis } from "./ArkEnumsInterfaces"
import { CurrentDayStyle, NonCurrentDayStyle, TodayStyle, WeekStyle, WorkStateStyle, CalendarSelectedDate, CalendarRequestedData, MonthData, CalendarAttribute, CalendarDay } from "./ArkCalendarInterfaces"
import { ResourceColor } from "./ArkUnitsInterfaces"
import { CalendarController } from "./ArkCalendarControllerMaterialized"
/** @memo:stable */
export class ArkCalendarComponent extends ComponentBase {
    protected getPeer(): ArkCalendarPeer {
        return (this.peer as ArkCalendarPeer)
    }
    /** @memo */
    public setCalendarOptions(value: { date: { year: number, month: number, day: number }, currentData: MonthData, preData: MonthData, nextData: MonthData, controller?: CalendarController }): this {
        if (this.checkPriority("setCalendarOptions")) {
            const value_casted = value as ({ date: { year: number, month: number, day: number }, currentData: MonthData, preData: MonthData, nextData: MonthData, controller?: CalendarController })
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
    public applyAttributesFinish(): void {
        // we calls this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}

/** @memo */
export function ArkCalendar(
  /** @memo */
  style: ((attributes: ArkCalendarComponent) => void) | undefined,
  /** @memo */
  content_: (() => void) | undefined,
  value: { date: { year: number, month: number, day: number }, currentData: MonthData, preData: MonthData, nextData: MonthData, controller?: CalendarController }
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
