/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

declare namespace intl {
    export interface LocaleOptions {
        calendar?: string;
        collation?: string;
        hourCycle?: string;
        numberingSystem?: string;
        numeric?: boolean;
        caseFirst?: string;
    }

    export class Locale {
        constructor();
        constructor(locale: string, options?: LocaleOptions);
        get language(): string;
        get script(): string;
        get region(): string;
        get baseName(): string;
        get caseFirst(): string;
        get calendar(): string;
        get collation(): string;
        get hourCycle(): string;
        get numberingSystem(): string;
        get numeric(): boolean;
        toString(): string;
        maximize(): Locale;
        minimize(): Locale;
    }

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

    export class DateTimeFormat {
        constructor();
        constructor(locale: string | Array<string>, options?: DateTimeOptions);
        format(date: Date): string;
        formatRange(startDate: Date, endDate: Date): string;
        resolvedOptions(): DateTimeOptions;
    }

    export interface NumberOptions {
        locale?: string;
        currency?: string;
        currencySign?: string;
        currencyDisplay?: string;
        unit?: string;
        unitDisplay?: string;
        unitUsage?: string;
        signDisplay?: string;
        compactDisplay?: string;
        notation?: string;
        localeMatcher?: string;
        style?: string;
        numberingSystem?: string;
        useGrouping?: boolean;
        minimumIntegerDigits?: int;
        minimumFractionDigits?: int;
        maximumFractionDigits?: int;
        minimumSignificantDigits?: int;
        maximumSignificantDigits?: int;
        roundingPriority?: string;
        roundingIncrement?: int;
        roundingMode?: string;
    }

    export class NumberFormat {
        constructor();
        constructor(locale: string | Array<string>, options?: NumberOptions);
        format(number: double): string;
        formatRange(startRange: double, endRange: double): string;
        resolvedOptions(): NumberOptions;
    }

    export interface CollatorOptions {
        localeMatcher?: string;
        usage?: string;
        sensitivity?: string;
        ignorePunctuation?: boolean;
        collation?: string;
        numeric?: boolean;
        caseFirst?: string;
    }

    export class Collator {
        constructor();
        constructor(locale: string | Array<string>, options?: CollatorOptions);
        compare(first: string, second: string): int;
        resolvedOptions(): CollatorOptions;
    }

    export interface PluralRulesOptions {
        localeMatcher?: string;
        type?: string;
        minimumIntegerDigits?: int;
        minimumFractionDigits?: int;
        maximumFractionDigits?: int;
        minimumSignificantDigits?: int;
        maximumSignificantDigits?: int;
    }

    export class PluralRules {
        constructor();
        constructor(locale: string | Array<string>, options?: PluralRulesOptions);
        select(n: double): string;
    }

    export interface RelativeTimeFormatInputOptions {
        localeMatcher?: string;
        numeric?: string;
        style?: string;
    }

    export interface RelativeTimeFormatResolvedOptions {
        locale: string;
        style: string;
        numeric: string;
        numberingSystem: string;
    }

    export interface RelativeTimeFormatPart {
        type: string;
        value: string;
        unit?: string;
    }

    export class RelativeTimeFormat {
        constructor();
        constructor(locale: string | Array<string>, options?: RelativeTimeFormatInputOptions);
        format(value: double, unit: string): string;
        formatToParts(value: double, unit: string): Array<RelativeTimeFormatPart>;
        resolvedOptions(): RelativeTimeFormatResolvedOptions;
    }
}
export type DateTimeOptions = intl.DateTimeOptions;
