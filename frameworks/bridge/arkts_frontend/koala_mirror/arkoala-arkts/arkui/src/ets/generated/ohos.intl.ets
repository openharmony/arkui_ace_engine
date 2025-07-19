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

import { SerializerBase, DeserializerBase, CallbackResource, InteropNativeModule, MaterializedBase, Tags, RuntimeType, runtimeType, toPeerPtr, nullptr, KPointer, NativeBuffer, KSerializerBuffer, KUint8ArrayPtr, KInt, KBoolean, KStringPtr, wrapCallback } from "@koalaui/interop"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { CallbackKind } from "./peers/CallbackKind"
import { TypeChecker } from "#components"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
export class intl_DateTimeOptions_serializer {
    public static write(buffer: SerializerBase, value: intl.DateTimeOptions): void {
        let valueSerializer : SerializerBase = buffer
        const value_locale  = value.locale
        let value_locale_type : int32 = RuntimeType.UNDEFINED
        value_locale_type = runtimeType(value_locale)
        valueSerializer.writeInt8((value_locale_type).toChar())
        if ((value_locale_type) != (RuntimeType.UNDEFINED)) {
            const value_locale_value  = value_locale!
            valueSerializer.writeString(value_locale_value)
        }
        const value_dateStyle  = value.dateStyle
        let value_dateStyle_type : int32 = RuntimeType.UNDEFINED
        value_dateStyle_type = runtimeType(value_dateStyle)
        valueSerializer.writeInt8((value_dateStyle_type).toChar())
        if ((value_dateStyle_type) != (RuntimeType.UNDEFINED)) {
            const value_dateStyle_value  = value_dateStyle!
            valueSerializer.writeString(value_dateStyle_value)
        }
        const value_timeStyle  = value.timeStyle
        let value_timeStyle_type : int32 = RuntimeType.UNDEFINED
        value_timeStyle_type = runtimeType(value_timeStyle)
        valueSerializer.writeInt8((value_timeStyle_type).toChar())
        if ((value_timeStyle_type) != (RuntimeType.UNDEFINED)) {
            const value_timeStyle_value  = value_timeStyle!
            valueSerializer.writeString(value_timeStyle_value)
        }
        const value_hourCycle  = value.hourCycle
        let value_hourCycle_type : int32 = RuntimeType.UNDEFINED
        value_hourCycle_type = runtimeType(value_hourCycle)
        valueSerializer.writeInt8((value_hourCycle_type).toChar())
        if ((value_hourCycle_type) != (RuntimeType.UNDEFINED)) {
            const value_hourCycle_value  = value_hourCycle!
            valueSerializer.writeString(value_hourCycle_value)
        }
        const value_timeZone  = value.timeZone
        let value_timeZone_type : int32 = RuntimeType.UNDEFINED
        value_timeZone_type = runtimeType(value_timeZone)
        valueSerializer.writeInt8((value_timeZone_type).toChar())
        if ((value_timeZone_type) != (RuntimeType.UNDEFINED)) {
            const value_timeZone_value  = value_timeZone!
            valueSerializer.writeString(value_timeZone_value)
        }
        const value_numberingSystem  = value.numberingSystem
        let value_numberingSystem_type : int32 = RuntimeType.UNDEFINED
        value_numberingSystem_type = runtimeType(value_numberingSystem)
        valueSerializer.writeInt8((value_numberingSystem_type).toChar())
        if ((value_numberingSystem_type) != (RuntimeType.UNDEFINED)) {
            const value_numberingSystem_value  = value_numberingSystem!
            valueSerializer.writeString(value_numberingSystem_value)
        }
        const value_hour12  = value.hour12
        let value_hour12_type : int32 = RuntimeType.UNDEFINED
        value_hour12_type = runtimeType(value_hour12)
        valueSerializer.writeInt8((value_hour12_type).toChar())
        if ((value_hour12_type) != (RuntimeType.UNDEFINED)) {
            const value_hour12_value  = value_hour12!
            valueSerializer.writeBoolean(value_hour12_value)
        }
        const value_weekday  = value.weekday
        let value_weekday_type : int32 = RuntimeType.UNDEFINED
        value_weekday_type = runtimeType(value_weekday)
        valueSerializer.writeInt8((value_weekday_type).toChar())
        if ((value_weekday_type) != (RuntimeType.UNDEFINED)) {
            const value_weekday_value  = value_weekday!
            valueSerializer.writeString(value_weekday_value)
        }
        const value_era  = value.era
        let value_era_type : int32 = RuntimeType.UNDEFINED
        value_era_type = runtimeType(value_era)
        valueSerializer.writeInt8((value_era_type).toChar())
        if ((value_era_type) != (RuntimeType.UNDEFINED)) {
            const value_era_value  = value_era!
            valueSerializer.writeString(value_era_value)
        }
        const value_year  = value.year
        let value_year_type : int32 = RuntimeType.UNDEFINED
        value_year_type = runtimeType(value_year)
        valueSerializer.writeInt8((value_year_type).toChar())
        if ((value_year_type) != (RuntimeType.UNDEFINED)) {
            const value_year_value  = value_year!
            valueSerializer.writeString(value_year_value)
        }
        const value_month  = value.month
        let value_month_type : int32 = RuntimeType.UNDEFINED
        value_month_type = runtimeType(value_month)
        valueSerializer.writeInt8((value_month_type).toChar())
        if ((value_month_type) != (RuntimeType.UNDEFINED)) {
            const value_month_value  = value_month!
            valueSerializer.writeString(value_month_value)
        }
        const value_day  = value.day
        let value_day_type : int32 = RuntimeType.UNDEFINED
        value_day_type = runtimeType(value_day)
        valueSerializer.writeInt8((value_day_type).toChar())
        if ((value_day_type) != (RuntimeType.UNDEFINED)) {
            const value_day_value  = value_day!
            valueSerializer.writeString(value_day_value)
        }
        const value_hour  = value.hour
        let value_hour_type : int32 = RuntimeType.UNDEFINED
        value_hour_type = runtimeType(value_hour)
        valueSerializer.writeInt8((value_hour_type).toChar())
        if ((value_hour_type) != (RuntimeType.UNDEFINED)) {
            const value_hour_value  = value_hour!
            valueSerializer.writeString(value_hour_value)
        }
        const value_minute  = value.minute
        let value_minute_type : int32 = RuntimeType.UNDEFINED
        value_minute_type = runtimeType(value_minute)
        valueSerializer.writeInt8((value_minute_type).toChar())
        if ((value_minute_type) != (RuntimeType.UNDEFINED)) {
            const value_minute_value  = value_minute!
            valueSerializer.writeString(value_minute_value)
        }
        const value_second  = value.second
        let value_second_type : int32 = RuntimeType.UNDEFINED
        value_second_type = runtimeType(value_second)
        valueSerializer.writeInt8((value_second_type).toChar())
        if ((value_second_type) != (RuntimeType.UNDEFINED)) {
            const value_second_value  = value_second!
            valueSerializer.writeString(value_second_value)
        }
        const value_timeZoneName  = value.timeZoneName
        let value_timeZoneName_type : int32 = RuntimeType.UNDEFINED
        value_timeZoneName_type = runtimeType(value_timeZoneName)
        valueSerializer.writeInt8((value_timeZoneName_type).toChar())
        if ((value_timeZoneName_type) != (RuntimeType.UNDEFINED)) {
            const value_timeZoneName_value  = value_timeZoneName!
            valueSerializer.writeString(value_timeZoneName_value)
        }
        const value_dayPeriod  = value.dayPeriod
        let value_dayPeriod_type : int32 = RuntimeType.UNDEFINED
        value_dayPeriod_type = runtimeType(value_dayPeriod)
        valueSerializer.writeInt8((value_dayPeriod_type).toChar())
        if ((value_dayPeriod_type) != (RuntimeType.UNDEFINED)) {
            const value_dayPeriod_value  = value_dayPeriod!
            valueSerializer.writeString(value_dayPeriod_value)
        }
        const value_localeMatcher  = value.localeMatcher
        let value_localeMatcher_type : int32 = RuntimeType.UNDEFINED
        value_localeMatcher_type = runtimeType(value_localeMatcher)
        valueSerializer.writeInt8((value_localeMatcher_type).toChar())
        if ((value_localeMatcher_type) != (RuntimeType.UNDEFINED)) {
            const value_localeMatcher_value  = value_localeMatcher!
            valueSerializer.writeString(value_localeMatcher_value)
        }
        const value_formatMatcher  = value.formatMatcher
        let value_formatMatcher_type : int32 = RuntimeType.UNDEFINED
        value_formatMatcher_type = runtimeType(value_formatMatcher)
        valueSerializer.writeInt8((value_formatMatcher_type).toChar())
        if ((value_formatMatcher_type) != (RuntimeType.UNDEFINED)) {
            const value_formatMatcher_value  = value_formatMatcher!
            valueSerializer.writeString(value_formatMatcher_value)
        }
    }
    public static read(buffer: DeserializerBase): intl.DateTimeOptions {
        let valueDeserializer : DeserializerBase = buffer
        const locale_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let locale_buf : string | undefined
        if ((locale_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            locale_buf = (valueDeserializer.readString() as string)
        }
        const locale_result : string | undefined = locale_buf
        const dateStyle_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let dateStyle_buf : string | undefined
        if ((dateStyle_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            dateStyle_buf = (valueDeserializer.readString() as string)
        }
        const dateStyle_result : string | undefined = dateStyle_buf
        const timeStyle_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let timeStyle_buf : string | undefined
        if ((timeStyle_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            timeStyle_buf = (valueDeserializer.readString() as string)
        }
        const timeStyle_result : string | undefined = timeStyle_buf
        const hourCycle_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let hourCycle_buf : string | undefined
        if ((hourCycle_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            hourCycle_buf = (valueDeserializer.readString() as string)
        }
        const hourCycle_result : string | undefined = hourCycle_buf
        const timeZone_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let timeZone_buf : string | undefined
        if ((timeZone_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            timeZone_buf = (valueDeserializer.readString() as string)
        }
        const timeZone_result : string | undefined = timeZone_buf
        const numberingSystem_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let numberingSystem_buf : string | undefined
        if ((numberingSystem_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            numberingSystem_buf = (valueDeserializer.readString() as string)
        }
        const numberingSystem_result : string | undefined = numberingSystem_buf
        const hour12_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let hour12_buf : boolean | undefined
        if ((hour12_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            hour12_buf = valueDeserializer.readBoolean()
        }
        const hour12_result : boolean | undefined = hour12_buf
        const weekday_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let weekday_buf : string | undefined
        if ((weekday_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            weekday_buf = (valueDeserializer.readString() as string)
        }
        const weekday_result : string | undefined = weekday_buf
        const era_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let era_buf : string | undefined
        if ((era_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            era_buf = (valueDeserializer.readString() as string)
        }
        const era_result : string | undefined = era_buf
        const year_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let year_buf : string | undefined
        if ((year_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            year_buf = (valueDeserializer.readString() as string)
        }
        const year_result : string | undefined = year_buf
        const month_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let month_buf : string | undefined
        if ((month_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            month_buf = (valueDeserializer.readString() as string)
        }
        const month_result : string | undefined = month_buf
        const day_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let day_buf : string | undefined
        if ((day_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            day_buf = (valueDeserializer.readString() as string)
        }
        const day_result : string | undefined = day_buf
        const hour_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let hour_buf : string | undefined
        if ((hour_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            hour_buf = (valueDeserializer.readString() as string)
        }
        const hour_result : string | undefined = hour_buf
        const minute_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let minute_buf : string | undefined
        if ((minute_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            minute_buf = (valueDeserializer.readString() as string)
        }
        const minute_result : string | undefined = minute_buf
        const second_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let second_buf : string | undefined
        if ((second_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            second_buf = (valueDeserializer.readString() as string)
        }
        const second_result : string | undefined = second_buf
        const timeZoneName_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let timeZoneName_buf : string | undefined
        if ((timeZoneName_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            timeZoneName_buf = (valueDeserializer.readString() as string)
        }
        const timeZoneName_result : string | undefined = timeZoneName_buf
        const dayPeriod_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let dayPeriod_buf : string | undefined
        if ((dayPeriod_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            dayPeriod_buf = (valueDeserializer.readString() as string)
        }
        const dayPeriod_result : string | undefined = dayPeriod_buf
        const localeMatcher_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let localeMatcher_buf : string | undefined
        if ((localeMatcher_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            localeMatcher_buf = (valueDeserializer.readString() as string)
        }
        const localeMatcher_result : string | undefined = localeMatcher_buf
        const formatMatcher_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let formatMatcher_buf : string | undefined
        if ((formatMatcher_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            formatMatcher_buf = (valueDeserializer.readString() as string)
        }
        const formatMatcher_result : string | undefined = formatMatcher_buf
        let value : intl.DateTimeOptions = ({locale: locale_result, dateStyle: dateStyle_result, timeStyle: timeStyle_result, hourCycle: hourCycle_result, timeZone: timeZone_result, numberingSystem: numberingSystem_result, hour12: hour12_result, weekday: weekday_result, era: era_result, year: year_result, month: month_result, day: day_result, hour: hour_result, minute: minute_result, second: second_result, timeZoneName: timeZoneName_result, dayPeriod: dayPeriod_result, localeMatcher: localeMatcher_result, formatMatcher: formatMatcher_result} as intl.DateTimeOptions)
        return value
    }
}
export namespace intl {
    export interface DateTimeOptions {
        locale?: string;
        dateStyle?: string;
        timeStyle?: string;
        hourCycle?: string;
        timeZone?: string;
        numberingSystem?: string;
        hour12?: boolean;
        weekday?: string;
        era?: string;
        year?: string;
        month?: string;
        day?: string;
        hour?: string;
        minute?: string;
        second?: string;
        timeZoneName?: string;
        dayPeriod?: string;
        localeMatcher?: string;
        formatMatcher?: string;
    }
}
