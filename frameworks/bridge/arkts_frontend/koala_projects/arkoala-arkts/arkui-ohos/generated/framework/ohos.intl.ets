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

import { default as intl } from '@ohos.intl'
import { SerializerBase, DeserializerBase, CallbackResource, InteropNativeModule, MaterializedBase, Tags, RuntimeType, toPeerPtr, nullptr, KPointer, NativeBuffer, KSerializerBuffer, KUint8ArrayPtr } from '@koalaui/interop'
import { int32, int64, float32, unsafeCast } from '@koalaui/common'
import { CallbackTransformer } from './../CallbackTransformer'
export class intl_DateTimeOptions_serializer {
    public static write(buffer: SerializerBase, value: intl.DateTimeOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForLocale  = value.locale
        if (valueHolderForLocale !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLocaleTmpValue  = valueHolderForLocale!
            valueSerializer.writeString(valueHolderForLocaleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForDateStyle  = value.dateStyle
        if (valueHolderForDateStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForDateStyleTmpValue  = valueHolderForDateStyle!
            valueSerializer.writeString(valueHolderForDateStyleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForTimeStyle  = value.timeStyle
        if (valueHolderForTimeStyle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTimeStyleTmpValue  = valueHolderForTimeStyle!
            valueSerializer.writeString(valueHolderForTimeStyleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForHourCycle  = value.hourCycle
        if (valueHolderForHourCycle !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForHourCycleTmpValue  = valueHolderForHourCycle!
            valueSerializer.writeString(valueHolderForHourCycleTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForTimeZone  = value.timeZone
        if (valueHolderForTimeZone !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTimeZoneTmpValue  = valueHolderForTimeZone!
            valueSerializer.writeString(valueHolderForTimeZoneTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForNumberingSystem  = value.numberingSystem
        if (valueHolderForNumberingSystem !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForNumberingSystemTmpValue  = valueHolderForNumberingSystem!
            valueSerializer.writeString(valueHolderForNumberingSystemTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForHour12  = value.hour12
        if (valueHolderForHour12 !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForHour12TmpValue  = valueHolderForHour12!
            valueSerializer.writeBoolean(valueHolderForHour12TmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForWeekday  = value.weekday
        if (valueHolderForWeekday !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForWeekdayTmpValue  = valueHolderForWeekday!
            valueSerializer.writeString(valueHolderForWeekdayTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForEra  = value.era
        if (valueHolderForEra !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForEraTmpValue  = valueHolderForEra!
            valueSerializer.writeString(valueHolderForEraTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForYear  = value.year
        if (valueHolderForYear !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForYearTmpValue  = valueHolderForYear!
            valueSerializer.writeString(valueHolderForYearTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMonth  = value.month
        if (valueHolderForMonth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMonthTmpValue  = valueHolderForMonth!
            valueSerializer.writeString(valueHolderForMonthTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForDay  = value.day
        if (valueHolderForDay !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForDayTmpValue  = valueHolderForDay!
            valueSerializer.writeString(valueHolderForDayTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForHour  = value.hour
        if (valueHolderForHour !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForHourTmpValue  = valueHolderForHour!
            valueSerializer.writeString(valueHolderForHourTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMinute  = value.minute
        if (valueHolderForMinute !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMinuteTmpValue  = valueHolderForMinute!
            valueSerializer.writeString(valueHolderForMinuteTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForSecond  = value.second
        if (valueHolderForSecond !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForSecondTmpValue  = valueHolderForSecond!
            valueSerializer.writeString(valueHolderForSecondTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForTimeZoneName  = value.timeZoneName
        if (valueHolderForTimeZoneName !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForTimeZoneNameTmpValue  = valueHolderForTimeZoneName!
            valueSerializer.writeString(valueHolderForTimeZoneNameTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForDayPeriod  = value.dayPeriod
        if (valueHolderForDayPeriod !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForDayPeriodTmpValue  = valueHolderForDayPeriod!
            valueSerializer.writeString(valueHolderForDayPeriodTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLocaleMatcher  = value.localeMatcher
        if (valueHolderForLocaleMatcher !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLocaleMatcherTmpValue  = valueHolderForLocaleMatcher!
            valueSerializer.writeString(valueHolderForLocaleMatcherTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFormatMatcher  = value.formatMatcher
        if (valueHolderForFormatMatcher !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFormatMatcherTmpValue  = valueHolderForFormatMatcher!
            valueSerializer.writeString(valueHolderForFormatMatcherTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): intl.DateTimeOptions {
        let valueDeserializer : DeserializerBase = buffer
        const localeTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let localeTmpBuf : string | undefined = undefined
        if ((localeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            localeTmpBuf = (valueDeserializer.readString() as string)
        }
        const localeTmpResult : string | undefined = localeTmpBuf
        const dateStyleTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let dateStyleTmpBuf : string | undefined = undefined
        if ((dateStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            dateStyleTmpBuf = (valueDeserializer.readString() as string)
        }
        const dateStyleTmpResult : string | undefined = dateStyleTmpBuf
        const timeStyleTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let timeStyleTmpBuf : string | undefined = undefined
        if ((timeStyleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            timeStyleTmpBuf = (valueDeserializer.readString() as string)
        }
        const timeStyleTmpResult : string | undefined = timeStyleTmpBuf
        const hourCycleTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let hourCycleTmpBuf : string | undefined = undefined
        if ((hourCycleTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            hourCycleTmpBuf = (valueDeserializer.readString() as string)
        }
        const hourCycleTmpResult : string | undefined = hourCycleTmpBuf
        const timeZoneTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let timeZoneTmpBuf : string | undefined = undefined
        if ((timeZoneTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            timeZoneTmpBuf = (valueDeserializer.readString() as string)
        }
        const timeZoneTmpResult : string | undefined = timeZoneTmpBuf
        const numberingSystemTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let numberingSystemTmpBuf : string | undefined = undefined
        if ((numberingSystemTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            numberingSystemTmpBuf = (valueDeserializer.readString() as string)
        }
        const numberingSystemTmpResult : string | undefined = numberingSystemTmpBuf
        const hour12TmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let hour12TmpBuf : boolean | undefined = undefined
        if ((hour12TmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            hour12TmpBuf = valueDeserializer.readBoolean()
        }
        const hour12TmpResult : boolean | undefined = hour12TmpBuf
        const weekdayTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let weekdayTmpBuf : string | undefined = undefined
        if ((weekdayTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            weekdayTmpBuf = (valueDeserializer.readString() as string)
        }
        const weekdayTmpResult : string | undefined = weekdayTmpBuf
        const eraTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let eraTmpBuf : string | undefined = undefined
        if ((eraTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            eraTmpBuf = (valueDeserializer.readString() as string)
        }
        const eraTmpResult : string | undefined = eraTmpBuf
        const yearTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let yearTmpBuf : string | undefined = undefined
        if ((yearTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            yearTmpBuf = (valueDeserializer.readString() as string)
        }
        const yearTmpResult : string | undefined = yearTmpBuf
        const monthTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let monthTmpBuf : string | undefined = undefined
        if ((monthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            monthTmpBuf = (valueDeserializer.readString() as string)
        }
        const monthTmpResult : string | undefined = monthTmpBuf
        const dayTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let dayTmpBuf : string | undefined = undefined
        if ((dayTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            dayTmpBuf = (valueDeserializer.readString() as string)
        }
        const dayTmpResult : string | undefined = dayTmpBuf
        const hourTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let hourTmpBuf : string | undefined = undefined
        if ((hourTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            hourTmpBuf = (valueDeserializer.readString() as string)
        }
        const hourTmpResult : string | undefined = hourTmpBuf
        const minuteTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let minuteTmpBuf : string | undefined = undefined
        if ((minuteTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            minuteTmpBuf = (valueDeserializer.readString() as string)
        }
        const minuteTmpResult : string | undefined = minuteTmpBuf
        const secondTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let secondTmpBuf : string | undefined = undefined
        if ((secondTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            secondTmpBuf = (valueDeserializer.readString() as string)
        }
        const secondTmpResult : string | undefined = secondTmpBuf
        const timeZoneNameTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let timeZoneNameTmpBuf : string | undefined = undefined
        if ((timeZoneNameTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            timeZoneNameTmpBuf = (valueDeserializer.readString() as string)
        }
        const timeZoneNameTmpResult : string | undefined = timeZoneNameTmpBuf
        const dayPeriodTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let dayPeriodTmpBuf : string | undefined = undefined
        if ((dayPeriodTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            dayPeriodTmpBuf = (valueDeserializer.readString() as string)
        }
        const dayPeriodTmpResult : string | undefined = dayPeriodTmpBuf
        const localeMatcherTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let localeMatcherTmpBuf : string | undefined = undefined
        if ((localeMatcherTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            localeMatcherTmpBuf = (valueDeserializer.readString() as string)
        }
        const localeMatcherTmpResult : string | undefined = localeMatcherTmpBuf
        const formatMatcherTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let formatMatcherTmpBuf : string | undefined = undefined
        if ((formatMatcherTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            formatMatcherTmpBuf = (valueDeserializer.readString() as string)
        }
        const formatMatcherTmpResult : string | undefined = formatMatcherTmpBuf
        let value : intl.DateTimeOptions = ({locale: localeTmpResult, dateStyle: dateStyleTmpResult, timeStyle: timeStyleTmpResult, hourCycle: hourCycleTmpResult, timeZone: timeZoneTmpResult, numberingSystem: numberingSystemTmpResult, hour12: hour12TmpResult, weekday: weekdayTmpResult, era: eraTmpResult, year: yearTmpResult, month: monthTmpResult, day: dayTmpResult, hour: hourTmpResult, minute: minuteTmpResult, second: secondTmpResult, timeZoneName: timeZoneNameTmpResult, dayPeriod: dayPeriodTmpResult, localeMatcher: localeMatcherTmpResult, formatMatcher: formatMatcherTmpResult} as intl.DateTimeOptions)
        return value
    }
}
