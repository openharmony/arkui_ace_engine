/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { IMutableStateMeta, IObservedObject, ISubscribedWatches, RenderIdType, WatchIdType } from '../decorator';
import { SubscribedWatches } from '../decoratorImpl/decoratorWatch';
import { ObserveSingleton } from './observeSingleton';
import { FactoryInternal } from './iFactoryInternal';
import { ObserveWrappedBase } from './observeWrappedBase';

export class WrappedDate extends Date implements IObservedObject, ObserveWrappedBase, ISubscribedWatches {
    private store_: Date;
    private meta_: IMutableStateMeta;
    // support for @Watch
    // each IObservedObject manages a set of @Wtch subscribers
    // when a object property changes need to call execureOnSubscribingWatches
    // compare interface
    private subscribedWatches: SubscribedWatches = new SubscribedWatches();
    // IObservedObject interface
    private ____V1RenderId: RenderIdType = 0;

    /**
     * Constructs a Date from another Date
     * @param date another Date
     */
    constructor(date: Date) {
        // Create without parameters to avoid call back to WrappedMap before "this" is fully constructed!
        super();

        this.store_ = date;
        this.meta_ = FactoryInternal.mkMutableStateMeta('');
    }

    // implementation of ISubscribedWatches by forwarding to subscribedWatches
    public addWatchSubscriber(watchId: WatchIdType): void {
        this.subscribedWatches.addWatchSubscriber(watchId);
    }
    public removeWatchSubscriber(watchId: WatchIdType): boolean {
        return this.subscribedWatches.removeWatchSubscriber(watchId);
    }

    public executeOnSubscribingWatches(propertyName: string): void {
        this.subscribedWatches.executeOnSubscribingWatches(propertyName);
    }

    public getRaw(): Object {
        return this.store_;
    }

    public setV1RenderId(renderId: RenderIdType): void {
        this.____V1RenderId = renderId;
    }

    public shouldAddRef(): boolean {
        return ObserveSingleton.instance.shouldAddRef(this.____V1RenderId);
    }

    /**
     * The `isDateValid()` method checks if constructed date is maximum of ±100,000,000
     * (one hundred million) days relative to January 1, 1970 UTC
     * (that is, April 20, 271821 BCE ~ September 13, 275760 CE) can be represented
     * by the standard Date object (equivalent to ±8,640,000,000,000,000 milliseconds).
     */
    public override isDateValid(): boolean {
        this.conditionalAddRef();
        return this.store_.isDateValid();
    }

    /**
     * The `valueOf()` method returns the primitive value of a `Date` object.
     *
     * @see ECMA-262, 21.4.4.44
     * @returns The number of milliseconds between 1 January 1970 00:00:00 UTC and the given date.
     * @throws InvalidDate - Throws if Date object is invalid (@link{isDateValid} is `false`).
     */
    public override valueOf(): number {
        this.conditionalAddRef();
        return this.store_.valueOf();
    }

    /**
     * Gets a string with a language-sensitive representation of the time portion of the date.
     *
     * @returns a language-sensitive representation of the time portion of the date.
     */
    public override toLocaleTimeString(): string {
        this.conditionalAddRef();
        return this.store_.toLocaleTimeString();
    }

    /**
     * Gets a string with a language-sensitive representation
     * of the date portion of the specified date in the user agent's timezone.
     *
     * @returns a string with a language-sensitive representation
     * of the date portion of the specified date in the user agent's timezone.
     */
    public override toLocaleDateString(): string {
        this.conditionalAddRef();
        return this.store_.toLocaleDateString();
    }

    /**
     * The `getDate()` method returns the day of the month for the specified date according to local time.
     *
     * @see ECMA-262, 21.4.4.2
     * @returns An integer number, between 1 and 31, representing the day of the month for the given date according to local time.
     */
    public override getDate(): number {
        this.conditionalAddRef();
        return this.store_.getDate();
    }

    /**
     * Changes the day of the month of a given Date instance, based on local time.
     *
     * @param value new day.
     */
    public override setDate(value: byte): void {
        this.store_.setDate(value);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setDate');
    }

    /**
     * Changes the day of the month of a given Date instance, based on local time.
     *
     * @param value new day.
     */
    public override setDate(value: number): number {
        const result = this.store_.setDate(value);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setDate');
        return result;
    }

    /**
     * Alias to @link{setDate} and left for compatibility with ECMA-262.
     *
     * @param value new day.
     */
    public override setDay(value: byte): void {
        this.store_.setDay(value);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setDate');
    }

    /**
     * Returns the day of the month (from 1 to 31) in the specified date according to universal time.
     *
     * @returns An integer number, between 1 and 31, representing the day of the month for the given date according to local time.
     */
    public override getUTCDate(): number {
        this.conditionalAddRef();
        return this.store_.getUTCDate();
    }

    /**
     * Changes the day of the month of a given Date instance, based on UTC time.
     *
     * @param value new day.
     */
    public override setUTCDate(value: byte): void {
        this.store_.setUTCDate(value);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setUTCDate');
    }

    /**
     * Changes the day of the month of a given Date instance, based on UTC time.
     *
     * @param value new day.
     */
    public override setUTCDate(value: number): number {
        const result = this.store_.setUTCDate(value);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setUTCDate');
        return result;
    }

    /**
     * Changes the day of the month of a given Date instance, based on UTC time.
     *
     * @param value new day.
     */
    public override setUTCDay(value: byte): void {
        this.store_.setUTCDay(value);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setUTCDay');
    }

    /**
     * Changes the day of the month of a given Date instance, based on UTC time.
     *
     * @param value new day.
     */
    public override setUTCDay(value: number): number {
        const result = this.store_.setUTCDay(value);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setUTCDay');
        return result;
    }

    /**
     * Returns the day of the week for the specified date according to local time,
     * where 0 represents Sunday. For the day of the month, see @link{getDayOfMonth}.
     *
     * @see ECMA-262, 21.4.4.3
     * @returns An integer number, between 0 and 6, corresponding to the day of the week
     * for the given date, according to local time: 0 for Sunday, 1 for Monday, 2 for Tuesday, and so on.
     */
    public override getDay(): number {
        this.conditionalAddRef();
        return this.store_.getDay();
    }

    /**
     * Returns the day of the week in the specified date according to universal time, where 0 represents Sunday.
     *
     * @returns An integer number, between 0 and 6, corresponding to the day of the week
     * for the given date, according to local time: 0 for Sunday, 1 for Monday, 2 for Tuesday, and so on.
     */
    public override getUTCDay(): number {
        this.conditionalAddRef();
        return this.store_.getUTCDay();
    }

    /**
     * Returns the year of the specified date according to local time.
     *
     * @see ECMA-262, 21.4.4.4
     * @note This function is an alias to @link{getFullYear} and left for compatibility with ECMA-262.
     * @returns year
     */
    public override getYear(): int {
        this.conditionalAddRef();
        return this.store_.getYear();
    }

    /**
     * Returns the year of the specified date according to local time.
     *
     * @returns A year of the specified date according to local time.
     * @description The value returned by `getUTCFullYear()` is an absolute number.
     * For dates between the years 1000 and 9999, `getUTCFullYear()` returns a four-digit number,
     * for example, 1995. Use this function to make sure a year is compliant with years after 2000.
     * @returns year
     */
    public override getUTCFullYear(): number {
        this.conditionalAddRef();
        return this.store_.getUTCFullYear();
    }

    /**
     * Returns the year of the specified date according to local time.
     *
     * @see ECMA-262, 21.4.4.4
     * @returns A number corresponding to the year of the given date, according to local time.
     * @description The value returned by `getFullYear()` is an absolute number.
     * For dates between the years 1000 and 9999, `getFullYear()` returns a four-digit number,
     * for example, 1995. Use this function to make sure a year is compliant with years after 2000.
     * @example
     * ```ets
     * const today = new Date();
     * const year = today.getYearFull();
     * ```
     */
    public override getFullYear(): number {
        this.conditionalAddRef();
        return this.store_.getFullYear();
    }

    /**
     * Sets the full year for a specified date according to universal time.
     *
     * @param value new year
     */
    public override setUTCFullYear(value: number, month?: number, date?: number): number {
        const result = this.store_.setUTCFullYear(value, month, date);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setUTCFullYear');
        return result;
    }

    /**
     * Sets the full year for a specified date according to universal time.
     *
     * @param value new year
     */
    public override setUTCFullYear(value: int): void {
        this.store_.setUTCFullYear(value);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setUTCFullYear');
    }

    /**
     * This function is an alias to @link{setFullYear} and left for compatibility with ECMA-262.
     *
     * @param value new year
     */
    public override setYear(value: number): void {
        this.store_.setYear(value);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setYear');
    }

    /**
     * This function is an alias to @link{setFullYear} and left for compatibility with ECMA-262.
     *
     * @param value new year
     */
    public override setYear(value: int): void {
        this.store_.setYear(value);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setYear');
    }

    /**
     * Sets the full year for a specified date according to local time.
     *
     * @param value new year
     */
    public override setFullYear(value: number, month?: Number, date?: Number): number {
        const result = this.store_.setFullYear(value, month, date);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setFullYear');
        return result;
    }

    /**
     * Sets the full year for a specified date according to local time.
     *
     * @param value new year
     */
    public override setFullYear(value: int): void {
        this.store_.setFullYear(value);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setFullYear');
    }

    /**
     * Returns the hour for the specified date, according to local time.
     *
     * @see ECMA-262, 21.4.4.5
     * @returns An integer number, between 0 and 23, representing the hour for the given date according to local time.
     * @example
     * ```ets
     * const today = new Date();
     * const hours = today.getHour();
     * ```
     */
    public override getHours(): number {
        this.conditionalAddRef();
        return this.store_.getHours();
    }

    /**
     * Returns the hours in the specified date according to universal time.
     *
     * @returns An integer number, between 0 and 23, representing the hour for the given date according to UTC time.
     */
    public override getUTCHours(): number {
        this.conditionalAddRef();
        return this.store_.getUTCHours();
    }

    /**
     * Sets the hours for a specified date according to local time.
     *
     * @param value new hours
     */
    public override setHours(value: byte): void {
        this.store_.setHours(value);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setHours');
    }

    /**
     * Sets the hours for a specified date according to local time.
     *
     * @param value new hours
     */
    public override setHours(value: number, min?: number, sec?: number, ms?: number): number {
        const result = this.store_.setHours(value, min, sec, ms);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setHours');
        return result;
    }

    /**
     * Sets the hour for a specified date according to universal time.
     *
     * @param value new hours
     */
    public override setUTCHours(value: byte): void {
        this.store_.setUTCHours(value);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setHours');
    }

    /**
     * Sets the hour for a specified date according to universal time.
     *
     * @param value new hours
     */
    public override setUTCHours(value: number, min?: number, sec?: number, ms?: number): number {
        const result = this.store_.setUTCHours(value, min, sec, ms);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setUTCHours');
        return result;
    }

    /**
     * Returns the milliseconds in the specified date according to local time.
     *
     * @see ECMA-262, 21.4.4.6
     * @returns A number between 0 and 999 representing the milliseconds for the given date according to local time.
     * @example
     * ```ets
     * const today = new Date();
     * const milliseconds = today.getMilliseconds();
     * ```
     */
    public override getMilliseconds(): number {
        this.conditionalAddRef();
        return this.store_.getMilliseconds();
    }

    /**
     * Returns the milliseconds portion of the time object's value according to universal time.
     *
     * @returns the milliseconds portion of the time object's value according to universal time.
     */
    public override getUTCMilliseconds(): number {
        this.conditionalAddRef();
        return this.store_.getUTCMilliseconds();
    }

    /**
     * Sets the milliseconds for a specified date according to local time.
     *
     * @param value new ms
     */
    public override setMilliseconds(value: short): void {
        this.store_.setMilliseconds(value);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setMilliseconds');
    }

    /**
     * Sets the milliseconds for a specified date according to local time.
     *
     * @param value new ms
     */
    public override setMilliseconds(value: number): number {
        const result = this.store_.setMilliseconds(value);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setMilliseconds');
        return result;
    }

    /**
     * Sets the milliseconds for a specified date according to universal time.
     *
     * @param value new ms
     */
    public override setUTCMilliseconds(value: short): void {
        this.store_.setUTCMilliseconds(value);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setUTCMilliseconds');
    }

    /**
     * Sets the milliseconds for a specified date according to universal time.
     *
     * @param value new ms
     */
    public override setUTCMilliseconds(value: number): number {
        const result = this.store_.setUTCMilliseconds(value);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setUTCMilliseconds');
        return result;
    }

    /**
     * Returns the seconds in the specified date according to local time.
     *
     * @see ECMA-262, 21.4.4.9
     * @returns An integer number, between 0 and 59, representing the seconds in the given date according to local time.
     * @example
     * ```ets
     * const today = new Date();
     * const seconds = today.getSeconds();
     * ```
     */
    public override getSeconds(): number {
        this.conditionalAddRef();
        return this.store_.getSeconds();
    }

    /**
     * Returns the seconds in the specified date according to universal time.
     *
     * @returns the seconds in the specified date according to universal time.
     */
    public override getUTCSeconds(): number {
        this.conditionalAddRef();
        return this.store_.getUTCSeconds();
    }

    /**
     * Sets the seconds for a specified date according to local time.
     *
     * @param value new seconds
     */
    public override setSeconds(value: number, ms?: number): number {
        const result = this.store_.setSeconds(value, ms);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setSeconds');
        return result;
    }

    /**
     * Sets the seconds for a specified date according to local time.
     *
     * @param value new seconds
     */
    public override setSeconds(value: byte): void {
        this.store_.setSeconds(value);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setSeconds');
    }

    /**
     * Sets the seconds for a specified date according to universal time.
     *
     * @param value new seconds
     */
    public override setUTCSeconds(value: byte): void {
        this.store_.setUTCSeconds(value);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setUTCSeconds');
    }

    /**
     * Sets the seconds for a specified date according to universal time.
     *
     * @param value new seconds
     */
    public override setUTCSeconds(value: number, ms?: number): number {
        const result = this.store_.setUTCSeconds(value, ms);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setUTCSeconds');
        return result;
    }

    /**
     * Returns the minutes in the specified date according to local time.
     *
     * @see ECMA-262, 21.4.4.7
     * @returns An integer number, between 0 and 59, representing the minutes in the given date according to local time.
     * @example
     * ```ets
     * const today = new Date();
     * const minutes = today.getMinutes();
     * ```
     */
    public override getMinutes(): number {
        this.conditionalAddRef();
        return this.store_.getMinutes();
    }

    /**
     * Sets the minutes for a specified date according to universal time.
     *
     * @param value new minutes
     */
    public override setUTCMinutes(value: byte): void {
        this.store_.setUTCMinutes(value);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setUTCMinutes');
    }

    /**
     * Sets the minutes for a specified date according to universal time.
     *
     * @param value new minutes
     */
    public override setUTCMinutes(value: number, sec?: Number, ms?: Number): number {
        const result = this.store_.setUTCMinutes(value, sec, ms);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setUTCMinutes');
        return result;
    }

    /**
     * Returns the minutes in the specified date according to universal time.
     *
     * @returns the minutes in the specified date according to universal time.
     */
    public override getUTCMinutes(): number {
        this.conditionalAddRef();
        return this.store_.getUTCMinutes();
    }

    /**
     * Sets the minutes for a specified date according to local time.
     *
     * @param value new minutes
     */
    public override setMinutes(value: byte): void {
        this.store_.setMinutes(value);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setUTCMinutes');
    }

    /**
     * Sets the minutes for a specified date according to local time.
     *
     * @param value new minutes
     */
    public override setMinutes(value: number, sec?: number, ms?: number): number {
        const result = this.store_.setMinutes(value, sec, ms);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setUTCMinutes');
        return result;
    }

    /**
     * Returns the month in the specified date according to local time,
     * as a zero-based value (where zero indicates the first month of the year).
     *
     * @see ECMA-262, 21.4.4.8
     * @returns  An integer number, between 0 and 11, representing the month in the given date according to local time.
     * 0 corresponds to January, 1 to February, and so on.
     * @example
     * ```ets
     * const today = new Date();
     * const month = today.getMonth();
     * ```
     */
    public override getMonth(): number {
        this.conditionalAddRef();
        return this.store_.getMonth();
    }

    /**
     * Returns the month of the specified date according to universal time, as a zero-based value (where zero indicates the first month of the year).
     *
     * @returns  An integer number, between 0 and 11, representing the month in the given date according to UTC time.
     * 0 corresponds to January, 1 to February, and so on.
     */
    public override getUTCMonth(): number {
        this.conditionalAddRef();
        return this.store_.getUTCMonth();
    }

    /**
     * Sets the month for a specified date according to the currently set year.
     *
     * @param month new month
     */
    public override setMonth(month: number, date?: number): number {
        const result = this.store_.setMonth(month, date);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setMonth');
        return result;
    }

    /**
     * Sets the month for a specified date according to the currently set year.
     *
     * @param month new month
     */
    public override setMonth(month: int): void {
        this.store_.setMonth(month);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setMonth');
    }

    /**
     * Sets the month for a specified date according to universal time.
     *
     * @param month new month
     */
    public override setUTCMonth(month: number, date?: number): number {
        const result = this.store_.setUTCMonth(month, date);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setUTCMonth');
        return result;
    }

    /**
     * Sets the month for a specified date according to universal time.
     *
     * @param month new month
     */
    public override setUTCMonth(month: int): void {
        this.store_.setUTCMonth(month);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setUTCMonth');
    }

    /**
     * Returns the number of milliseconds since the epoch,
     * which is defined as the midnight at the beginning of January 1, 1970, UTC.
     *
     * @see ECMA-262, 21.4.4.10
     * @returns A number representing the milliseconds elapsed between 1 January 1970 00:00:00 UTC and the given date.
     */
    public override getTime(): number {
        this.conditionalAddRef();
        return this.store_.getTime();
    }

    /**
     * Sets the number of milliseconds since the epoch,
     * which is defined as the midnight at the beginning of January 1, 1970, UTC.
     *
     * @param value new ms
     * @see ECMA-262, 21.4.4.10
     * @returns A number representing the milliseconds elapsed between 1 January 1970 00:00:00 UTC and the given date.
     */
    public override setTime(value: long): void {
        this.store_.setTime(value);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setTime');
    }

    /**
     * Sets the number of milliseconds since the epoch,
     * which is defined as the midnight at the beginning of January 1, 1970, UTC.
     *
     * @param value new ms
     * @see ECMA-262, 21.4.4.10
     * @returns A number representing the milliseconds elapsed between 1 January 1970 00:00:00 UTC and the given date.
     */
    public override setTime(value: number): number {
        const result = this.store_.setTime(value);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setTime');
        return result;
    }

    /**
     * Returns the difference, in minutes, between a date as
     * evaluated in the UTC time zone, and the same date as evaluated in the local time zone.
     *
     * @returns the difference, in minutes, between a date as
     * evaluated in the UTC time zone, and the same date as evaluated in the local time zone.
     */
    public override getTimezoneOffset(): number {
        this.conditionalAddRef();
        return this.store_.getTimezoneOffset();
    }

    /**
     * Sets the difference, in minutes, between a date as
     * evaluated in the UTC time zone, and the same date as evaluated in the local time zone.
     *
     * @param value new timezone offset
     */
    public override setTimezoneOffset(value: number): number {
        const result = this.store_.setTimezoneOffset(value);
        this.meta_.fireChange();
        this.executeOnSubscribingWatches('setTime');
        return result;
    }

    /**
     * Returns a string in simplified extended ISO format (ISO 8601),
     * which is always 24 or 27 characters long (YYYY-MM-DDTHH:mm:ss.sssZ or
     * ±YYYYYY-MM-DDTHH:mm:ss.sssZ, respectively). The timezone is always zero UTC offset,
     * as denoted by the suffix Z.
     *
     * @see ECMA-262, 21.4.4.36
     * @returns A string representing the given date in the ISO 8601 format according to universal time.
     * It's the same format as the one required to be recognized by @link{parse()}.
     * @example
     * ```ets
     * const today = new Date();
     * console.println(today.toISOString()); // Returns 2023-02-05T14:48:00.000Z
     * ```
     */
    public override toISOString(): string {
        this.conditionalAddRef();
        return this.store_.toISOString();
    }

    /**
     * Returns a string representation of the Date object.
     *
     * @returns JSON representation of the current instance
     */
    public override toJSON(): string {
        this.conditionalAddRef();
        return this.store_.toJSON() ?? '';
    }

    /**
     * Returns the time portion of a `Date` object interpreted in the local timezone in English.
     *
     * @see ECMA-262, 21.4.4.42
     * @returns A string representing the time portion of the given date in human-readable form in English.
     * @example
     * ```
     * let d = new Date(1979.0, 9.0, 27.0, 13.0, 12.8, 57.0, 444.1);
     * console.println(d.toTimeString()); // 13:12:57 GMT
     * ```
     */
    public override toTimeString(): string {
        this.conditionalAddRef();
        return this.store_.toTimeString();
    }

    /**
     * Returns the date portion of a `Date` object interpreted in the local timezone in English.
     *
     * @see ECMA-262, 21.4.4.35
     * @returns A string representing the date portion of the given Date object in human-readable form in English.
     * @example
     * ```
     * let d = new Date(1979.0, 9.0, 27.0, 13.0, 12.8, 57.0, 444.1);
     * console.println(d.toDateString()); // Sat Oct 27 1979
     * ```
     */
    public override toDateString(): string {
        this.conditionalAddRef();
        return this.store_.toDateString();
    }

    /**
     * Returns a string representing the specified `Date` object interpreted in the local timezone.
     *
     * @see ECMA-262, 21.4.4.41
     * @returns A string representing the given date.
     * @example
     * ```
     * let d = new Date(1979.0, 9.0, 27.0, 13.0, 12.8, 57.0, 444.1);
     * console.println(d.toString()); // Sat Oct 27 1979 13:12:57 GMT
     * ```
     */
    public override toString(): string {
        this.conditionalAddRef();
        return this.store_.toString();
    }

    /**
     * Returns a string representing the specified `Date` object interpreted in UTC.
     *
     * @see ECMA-262, 21.4.4.41
     * @returns A string representing the given date.
     * @example
     * ```
     * let d = new Date(1979.0, 9.0, 27.0, 13.0, 12.8, 57.0, 444.1);
     * console.println(d.toUTCString()); // Sat Oct 27 1979 13:12:57 GMT
     * ```
     */
    public override toUTCString(): string {
        this.conditionalAddRef();
        return this.store_.toUTCString();
    }

    // shorthand function because
    // Date can suffice with one meta
    // (IMutableStateMeta)
    private conditionalAddRef(): void {
        if (this.shouldAddRef()) {
            this.meta_.addRef();
        }
    }
}
