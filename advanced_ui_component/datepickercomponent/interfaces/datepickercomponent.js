/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
if (!("finalizeConstruction" in ViewPU.prototype)) {
    Reflect.set(ViewPU.prototype, "finalizeConstruction", () => { });
}
const LengthMetrics = requireNapi('arkui.node').LengthMetrics;
const intl = requireNapi('intl');
const i18n = requireNapi('i18n');
export var DateMode;
(function (DateMode) {
    DateMode[DateMode["DATE"] = 0] = "DATE";
    DateMode[DateMode["YEAR_AND_MONTH"] = 1] = "YEAR_AND_MONTH";
    DateMode[DateMode["MONTH_AND_DAY"] = 2] = "MONTH_AND_DAY";
})(DateMode || (DateMode = {}));
export var DisplayMode;
(function (DisplayMode) {
    DisplayMode[DisplayMode["DATE"] = 0] = "DATE";
    DisplayMode[DisplayMode["TIME"] = 1] = "TIME";
    DisplayMode[DisplayMode["DATE_TIME"] = 2] = "DATE_TIME";
})(DisplayMode || (DisplayMode = {}));
export var TimeFormat;
(function (TimeFormat) {
    TimeFormat[TimeFormat["HOUR_MINUTE"] = 0] = "HOUR_MINUTE";
    TimeFormat[TimeFormat["HOUR_MINUTE_SECOND"] = 1] = "HOUR_MINUTE_SECOND";
})(TimeFormat || (TimeFormat = {}));
export class DatePickerComponentResult {
}
export class CommonOptions {
}
export class DateOptions extends CommonOptions {
}
export class TimeOptions extends CommonOptions {
}
export class DatePickerComponentOptions {
}
class DatePickerConstant {
}
DatePickerConstant.MIN_YEAR = 0;
DatePickerConstant.MAX_YEAR = 10000;
DatePickerConstant.DEFAULT_START_YEAR = 1970;
DatePickerConstant.DEFAULT_END_YEAR = 2100;
DatePickerConstant.MIN_MONTH = 0;
DatePickerConstant.MAX_MONTH = 11;
DatePickerConstant.MIN_DAY = 1;
DatePickerConstant.MIN_HOUR = 0;
DatePickerConstant.MAX_HOUR = 23;
DatePickerConstant.MIN_MINUTE = 0;
DatePickerConstant.MAX_MINUTE = 59;
DatePickerConstant.MIN_SECOND = 0;
DatePickerConstant.MAX_SECOND = 59;
DatePickerConstant.MONTHS_IN_YEAR = 12;
DatePickerConstant.DEFAULT_STEP = 1;
export class DatePickerComponent extends ViewPU {
    constructor(parent, params, __localStorage, elmtId = -1, paramsLambda = undefined, extraInfo) {
        super(parent, __localStorage, elmtId, extraInfo);
        if (typeof paramsLambda === "function") {
            this.paramsGenerator_ = paramsLambda;
        }
        this.__options = new SynchedPropertyObjectOneWayPU(params.options, this, "options");
        this.__displayMode = new ObservedPropertySimplePU(DisplayMode.DATE, this, "displayMode");
        this.__selectedYear = new ObservedPropertySimplePU(0, this, "selectedYear");
        this.__selectedMonth = new ObservedPropertySimplePU(0, this, "selectedMonth");
        this.__selectedDay = new ObservedPropertySimplePU(0, this, "selectedDay");
        this.__selectedHour = new ObservedPropertySimplePU(0, this, "selectedHour");
        this.__selectedMinute = new ObservedPropertySimplePU(0, this, "selectedMinute");
        this.__selectedSecond = new ObservedPropertySimplePU(0, this, "selectedSecond");
        this.__startYear = new ObservedPropertySimplePU(DatePickerConstant.DEFAULT_START_YEAR, this, "startYear");
        this.__endYear = new ObservedPropertySimplePU(DatePickerConstant.DEFAULT_END_YEAR, this, "endYear");
        this.__dateMode = new ObservedPropertySimplePU(DateMode.DATE, this, "dateMode");
        this.__timeFormat = new ObservedPropertySimplePU(TimeFormat.HOUR_MINUTE, this, "timeFormat");
        this.__useMilitaryTime = new ObservedPropertySimplePU(false, this, "useMilitaryTime");
        this.__lunar = new ObservedPropertySimplePU(false, this, "lunar");
        this.__canLoop = new ObservedPropertySimplePU(true, this, "canLoop");
        this.__hapticFeedback = new ObservedPropertySimplePU(true, this, "hapticFeedback");
        this.__yearArray = new ObservedPropertyObjectPU([], this, "yearArray");
        this.__monthArray = new ObservedPropertyObjectPU([], this, "monthArray");
        this.__dayArray = new ObservedPropertyObjectPU([], this, "dayArray");
        this.__hourArray = new ObservedPropertyObjectPU([], this, "hourArray");
        this.__minuteArray = new ObservedPropertyObjectPU([], this, "minuteArray");
        this.__secondArray = new ObservedPropertyObjectPU([], this, "secondArray");
        this.__periodArray = new ObservedPropertyObjectPU([], this, "periodArray");
        this.__selectedPeriod = new ObservedPropertySimplePU(0, this, "selectedPeriod");
        this.onChange = undefined;
        this.onScrollStop = undefined;
        this.__currentLocale = new ObservedPropertySimplePU('', this, "currentLocale");
        this.locale = new intl.Locale();
        this.initFlag = true;
        this.lunarCalendar = null;
        this.setInitiallyProvidedValue(params);
        this.declareWatch("options", this.onOptionsChange);
        this.declareWatch("currentLocale", this.onLocaleChange);
        this.finalizeConstruction();
    }
    setInitiallyProvidedValue(params) {
        if (params.displayMode !== undefined) {
            this.displayMode = params.displayMode;
        }
        if (params.selectedYear !== undefined) {
            this.selectedYear = params.selectedYear;
        }
        if (params.selectedMonth !== undefined) {
            this.selectedMonth = params.selectedMonth;
        }
        if (params.selectedDay !== undefined) {
            this.selectedDay = params.selectedDay;
        }
        if (params.selectedHour !== undefined) {
            this.selectedHour = params.selectedHour;
        }
        if (params.selectedMinute !== undefined) {
            this.selectedMinute = params.selectedMinute;
        }
        if (params.selectedSecond !== undefined) {
            this.selectedSecond = params.selectedSecond;
        }
        if (params.startYear !== undefined) {
            this.startYear = params.startYear;
        }
        if (params.endYear !== undefined) {
            this.endYear = params.endYear;
        }
        if (params.dateMode !== undefined) {
            this.dateMode = params.dateMode;
        }
        if (params.timeFormat !== undefined) {
            this.timeFormat = params.timeFormat;
        }
        if (params.useMilitaryTime !== undefined) {
            this.useMilitaryTime = params.useMilitaryTime;
        }
        if (params.lunar !== undefined) {
            this.lunar = params.lunar;
        }
        if (params.canLoop !== undefined) {
            this.canLoop = params.canLoop;
        }
        if (params.hapticFeedback !== undefined) {
            this.hapticFeedback = params.hapticFeedback;
        }
        if (params.yearArray !== undefined) {
            this.yearArray = params.yearArray;
        }
        if (params.monthArray !== undefined) {
            this.monthArray = params.monthArray;
        }
        if (params.dayArray !== undefined) {
            this.dayArray = params.dayArray;
        }
        if (params.hourArray !== undefined) {
            this.hourArray = params.hourArray;
        }
        if (params.minuteArray !== undefined) {
            this.minuteArray = params.minuteArray;
        }
        if (params.secondArray !== undefined) {
            this.secondArray = params.secondArray;
        }
        if (params.periodArray !== undefined) {
            this.periodArray = params.periodArray;
        }
        if (params.selectedPeriod !== undefined) {
            this.selectedPeriod = params.selectedPeriod;
        }
        if (params.onChange !== undefined) {
            this.onChange = params.onChange;
        }
        if (params.onScrollStop !== undefined) {
            this.onScrollStop = params.onScrollStop;
        }
        if (params.currentLocale !== undefined) {
            this.currentLocale = params.currentLocale;
        }
        if (params.locale !== undefined) {
            this.locale = params.locale;
        }
        if (params.initFlag !== undefined) {
            this.initFlag = params.initFlag;
        }
        if (params.lunarCalendar !== undefined) {
            this.lunarCalendar = params.lunarCalendar;
        }
    }
    updateStateVars(params) {
        this.__options.reset(params.options);
    }
    purgeVariableDependenciesOnElmtId(rmElmtId) {
        this.__options.purgeDependencyOnElmtId(rmElmtId);
        this.__displayMode.purgeDependencyOnElmtId(rmElmtId);
        this.__selectedYear.purgeDependencyOnElmtId(rmElmtId);
        this.__selectedMonth.purgeDependencyOnElmtId(rmElmtId);
        this.__selectedDay.purgeDependencyOnElmtId(rmElmtId);
        this.__selectedHour.purgeDependencyOnElmtId(rmElmtId);
        this.__selectedMinute.purgeDependencyOnElmtId(rmElmtId);
        this.__selectedSecond.purgeDependencyOnElmtId(rmElmtId);
        this.__startYear.purgeDependencyOnElmtId(rmElmtId);
        this.__endYear.purgeDependencyOnElmtId(rmElmtId);
        this.__dateMode.purgeDependencyOnElmtId(rmElmtId);
        this.__timeFormat.purgeDependencyOnElmtId(rmElmtId);
        this.__useMilitaryTime.purgeDependencyOnElmtId(rmElmtId);
        this.__lunar.purgeDependencyOnElmtId(rmElmtId);
        this.__canLoop.purgeDependencyOnElmtId(rmElmtId);
        this.__hapticFeedback.purgeDependencyOnElmtId(rmElmtId);
        this.__yearArray.purgeDependencyOnElmtId(rmElmtId);
        this.__monthArray.purgeDependencyOnElmtId(rmElmtId);
        this.__dayArray.purgeDependencyOnElmtId(rmElmtId);
        this.__hourArray.purgeDependencyOnElmtId(rmElmtId);
        this.__minuteArray.purgeDependencyOnElmtId(rmElmtId);
        this.__secondArray.purgeDependencyOnElmtId(rmElmtId);
        this.__periodArray.purgeDependencyOnElmtId(rmElmtId);
        this.__selectedPeriod.purgeDependencyOnElmtId(rmElmtId);
        this.__currentLocale.purgeDependencyOnElmtId(rmElmtId);
    }
    aboutToBeDeleted() {
        this.__options.aboutToBeDeleted();
        this.__displayMode.aboutToBeDeleted();
        this.__selectedYear.aboutToBeDeleted();
        this.__selectedMonth.aboutToBeDeleted();
        this.__selectedDay.aboutToBeDeleted();
        this.__selectedHour.aboutToBeDeleted();
        this.__selectedMinute.aboutToBeDeleted();
        this.__selectedSecond.aboutToBeDeleted();
        this.__startYear.aboutToBeDeleted();
        this.__endYear.aboutToBeDeleted();
        this.__dateMode.aboutToBeDeleted();
        this.__timeFormat.aboutToBeDeleted();
        this.__useMilitaryTime.aboutToBeDeleted();
        this.__lunar.aboutToBeDeleted();
        this.__canLoop.aboutToBeDeleted();
        this.__hapticFeedback.aboutToBeDeleted();
        this.__yearArray.aboutToBeDeleted();
        this.__monthArray.aboutToBeDeleted();
        this.__dayArray.aboutToBeDeleted();
        this.__hourArray.aboutToBeDeleted();
        this.__minuteArray.aboutToBeDeleted();
        this.__secondArray.aboutToBeDeleted();
        this.__periodArray.aboutToBeDeleted();
        this.__selectedPeriod.aboutToBeDeleted();
        this.__currentLocale.aboutToBeDeleted();
        SubscriberManager.Get().delete(this.id__());
        this.aboutToBeDeletedInternal();
    }
    get options() {
        return this.__options.get();
    }
    set options(newValue) {
        this.__options.set(newValue);
    }
    get displayMode() {
        return this.__displayMode.get();
    }
    set displayMode(newValue) {
        this.__displayMode.set(newValue);
    }
    get selectedYear() {
        return this.__selectedYear.get();
    }
    set selectedYear(newValue) {
        this.__selectedYear.set(newValue);
    }
    get selectedMonth() {
        return this.__selectedMonth.get();
    }
    set selectedMonth(newValue) {
        this.__selectedMonth.set(newValue);
    }
    get selectedDay() {
        return this.__selectedDay.get();
    }
    set selectedDay(newValue) {
        this.__selectedDay.set(newValue);
    }
    get selectedHour() {
        return this.__selectedHour.get();
    }
    set selectedHour(newValue) {
        this.__selectedHour.set(newValue);
    }
    get selectedMinute() {
        return this.__selectedMinute.get();
    }
    set selectedMinute(newValue) {
        this.__selectedMinute.set(newValue);
    }
    get selectedSecond() {
        return this.__selectedSecond.get();
    }
    set selectedSecond(newValue) {
        this.__selectedSecond.set(newValue);
    }
    get startYear() {
        return this.__startYear.get();
    }
    set startYear(newValue) {
        this.__startYear.set(newValue);
    }
    get endYear() {
        return this.__endYear.get();
    }
    set endYear(newValue) {
        this.__endYear.set(newValue);
    }
    get dateMode() {
        return this.__dateMode.get();
    }
    set dateMode(newValue) {
        this.__dateMode.set(newValue);
    }
    get timeFormat() {
        return this.__timeFormat.get();
    }
    set timeFormat(newValue) {
        this.__timeFormat.set(newValue);
    }
    get useMilitaryTime() {
        return this.__useMilitaryTime.get();
    }
    set useMilitaryTime(newValue) {
        this.__useMilitaryTime.set(newValue);
    }
    get lunar() {
        return this.__lunar.get();
    }
    set lunar(newValue) {
        this.__lunar.set(newValue);
    }
    get canLoop() {
        return this.__canLoop.get();
    }
    set canLoop(newValue) {
        this.__canLoop.set(newValue);
    }
    get hapticFeedback() {
        return this.__hapticFeedback.get();
    }
    set hapticFeedback(newValue) {
        this.__hapticFeedback.set(newValue);
    }
    get yearArray() {
        return this.__yearArray.get();
    }
    set yearArray(newValue) {
        this.__yearArray.set(newValue);
    }
    get monthArray() {
        return this.__monthArray.get();
    }
    set monthArray(newValue) {
        this.__monthArray.set(newValue);
    }
    get dayArray() {
        return this.__dayArray.get();
    }
    set dayArray(newValue) {
        this.__dayArray.set(newValue);
    }
    get hourArray() {
        return this.__hourArray.get();
    }
    set hourArray(newValue) {
        this.__hourArray.set(newValue);
    }
    get minuteArray() {
        return this.__minuteArray.get();
    }
    set minuteArray(newValue) {
        this.__minuteArray.set(newValue);
    }
    get secondArray() {
        return this.__secondArray.get();
    }
    set secondArray(newValue) {
        this.__secondArray.set(newValue);
    }
    get periodArray() {
        return this.__periodArray.get();
    }
    set periodArray(newValue) {
        this.__periodArray.set(newValue);
    }
    get selectedPeriod() {
        return this.__selectedPeriod.get();
    }
    set selectedPeriod(newValue) {
        this.__selectedPeriod.set(newValue);
    }
    get currentLocale() {
        return this.__currentLocale.get();
    }
    set currentLocale(newValue) {
        this.__currentLocale.set(newValue);
    }
    aboutToAppear() {
        this.currentLocale = i18n.System.getSystemLanguage();
        this.locale = new intl.Locale(this.currentLocale);
        if (this.selectedYear === 0 || this.selectedMonth === 0 || this.selectedDay === 0) {
            const now = new Date();
            this.selectedYear = now.getFullYear();
            this.selectedMonth = now.getMonth();
            this.selectedDay = now.getDate();
            this.selectedHour = now.getHours();
            this.selectedMinute = now.getMinutes();
            this.selectedSecond = now.getSeconds();
        }
        if (this.lunar) {
            this.lunarCalendar = i18n.getCalendar(this.locale.toString(), 'chinese');
        }
        if (this.options !== undefined && this.options !== null) {
            this.onOptionsChange();
        }
        else {
            this.initArrays();
        }
    }
    onLocaleChange() {
        this.locale = new intl.Locale(this.currentLocale);
        if (this.lunar) {
            this.lunarCalendar = i18n.getCalendar(this.locale.toString(), 'chinese');
        }
        this.initArrays();
    }
    initArrays() {
        if (this.lunar) {
            this.initLunarArrays();
        }
        else {
            this.initYearArray();
            this.initMonthArray();
            this.initDayArray();
        }
        this.initTimeArrays();
    }
    initLunarArrays() {
        this.yearArray = [];
        for (let i = this.startYear; i <= this.endYear; i++) {
            this.yearArray.push(this.formatLunarYear(i));
        }
        this.monthArray = [];
        for (let i = DatePickerConstant.MIN_MONTH; i <= DatePickerConstant.MAX_MONTH; i++) {
            this.monthArray.push(this.formatLunarMonth(i, false));
        }
        this.initLunarDayArray();
    }
    initLunarDayArray() {
        this.dayArray = [];
        const lunarDays = this.getLunarDaysInMonth(this.selectedYear, this.selectedMonth);
        for (let i = DatePickerConstant.MIN_DAY; i <= lunarDays; i++) {
            this.dayArray.push(this.formatLunarDay(i));
        }
    }
    getLunarDaysInMonth(gregorianYear, lunarMonth) {
        if (this.lunarCalendar === null) {
            return 30;
        }
        try {
            let month1Start = null;
            let month2Start = null;
            for (let month = 0; month < 12; month++) {
                for (let day = 1; day <= 31; day++) {
                    const testDate = new Date(gregorianYear, month, day);
                    this.lunarCalendar.setTime(testDate);
                    const currentLunarMonth = this.lunarCalendar.get('month');
                    const currentLunarDay = this.lunarCalendar.get('date');
                    if (currentLunarMonth === lunarMonth && currentLunarDay === 1 && month1Start === null) {
                        month1Start = testDate;
                    }
                    if (month1Start !== null && month2Start === null) {
                        if (currentLunarMonth === lunarMonth + 1 && currentLunarDay === 1) {
                            month2Start = testDate;
                            break;
                        }
                        if (currentLunarMonth === 0 && lunarMonth === 11 && currentLunarDay === 1) {
                            month2Start = testDate;
                            break;
                        }
                    }
                }
                if (month1Start !== null && month2Start !== null) {
                    break;
                }
            }
            if (month1Start !== null && month2Start !== null) {
                const daysDiff = Math.round((month2Start.getTime() - month1Start.getTime()) / (24 * 60 * 60 * 1000));
                return daysDiff;
            }
            return 30;
        }
        catch (e) {
            return 30;
        }
    }
    formatLunarYear(gregorianYear) {
        return `${gregorianYear}年`;
    }
    formatLunarMonth(month, isLeap) {
        const lunarMonthNames = ['正月', '二月', '三月', '四月', '五月', '六月',
            '七月', '八月', '九月', '十月', '十一月', '十二月'];
        if (isLeap) {
            return `闰${lunarMonthNames[month]}`;
        }
        return lunarMonthNames[month];
    }
    formatLunarDay(day) {
        const lunarDayNames = ['初一', '初二', '初三', '初四', '初五', '初六', '初七', '初八', '初九', '初十',
            '十一', '十二', '十三', '十四', '十五', '十六', '十七', '十八', '十九', '二十',
            '廿一', '廿二', '廿三', '廿四', '廿五', '廿六', '廿七', '廿八', '廿九', '三十'];
        if (day >= 1 && day <= 30) {
            return lunarDayNames[day - 1];
        }
        return `${day}日`;
    }
    initYearArray() {
        this.yearArray = [];
        for (let i = this.startYear; i <= this.endYear; i++) {
            this.yearArray.push(this.formatYear(i));
        }
    }
    initMonthArray() {
        this.monthArray = [];
        for (let i = DatePickerConstant.MIN_MONTH; i <= DatePickerConstant.MAX_MONTH; i++) {
            this.monthArray.push(this.formatMonth(i));
        }
    }
    initDayArray() {
        this.dayArray = [];
        const daysInMonth = this.getDaysInMonth(this.selectedYear, this.selectedMonth);
        for (let i = DatePickerConstant.MIN_DAY; i <= daysInMonth; i++) {
            this.dayArray.push(this.formatDay(i));
        }
    }
    initTimeArrays() {
        this.hourArray = [];
        if (this.useMilitaryTime) {
            for (let i = DatePickerConstant.MIN_HOUR; i <= DatePickerConstant.MAX_HOUR; i++) {
                this.hourArray.push(i.toString().padStart(2, '0'));
            }
        }
        else {
            for (let i = 1; i <= 12; i++) {
                this.hourArray.push(i.toString().padStart(2, '0'));
            }
        }
        this.minuteArray = [];
        for (let i = DatePickerConstant.MIN_MINUTE; i <= DatePickerConstant.MAX_MINUTE; i++) {
            this.minuteArray.push(this.formatMinute(i));
        }
        this.secondArray = [];
        for (let i = DatePickerConstant.MIN_SECOND; i <= DatePickerConstant.MAX_SECOND; i++) {
            this.secondArray.push(this.formatSecond(i));
        }
        this.periodArray = [];
        if (!this.useMilitaryTime) {
            this.periodArray.push(this.formatPeriod(true));
            this.periodArray.push(this.formatPeriod(false));
            this.selectedPeriod = this.selectedHour < 12 ? 0 : 1;
        }
    }
    isChineseLocale() {
        const localeStr = this.locale.toString();
        return localeStr.startsWith('zh') || localeStr.includes('zh-CN') || localeStr.includes('zh-TW') || localeStr.includes('zh-Hans') || localeStr.includes('zh-Hant');
    }
    formatYear(year) {
        if (this.isChineseLocale()) {
            return `${year}年`;
        }
        return year.toString();
    }
    formatMonth(month) {
        if (this.isChineseLocale()) {
            return `${month + 1}月`;
        }
        const monthNames = [
            'January', 'February', 'March', 'April', 'May', 'June',
            'July', 'August', 'September', 'October', 'November', 'December'
        ];
        try {
            const localeStr = this.locale.toString();
            if (!localeStr || localeStr.length === 0) {
                return monthNames[month];
            }
            const dateFormat = new Intl.DateTimeFormat(localeStr, {
                month: 'long'
            });
            const safeMonth = Math.max(0, Math.min(11, month));
            const date = new Date(2026, safeMonth, 15);
            return dateFormat.format(date);
        }
        catch (error) {
            return monthNames[month];
        }
    }
    formatDay(day) {
        if (this.isChineseLocale()) {
            return `${day}日`;
        }
        try {
            const localeStr = this.locale.toString();
            if (!localeStr || localeStr.length === 0) {
                return `${day}`;
            }
            const dateFormat = new Intl.DateTimeFormat(localeStr, {
                day: 'numeric'
            });
            const safeDay = Math.max(1, Math.min(31, day));
            const date = new Date(2026, 0, safeDay);
            return dateFormat.format(date);
        }
        catch (error) {
            return `${day}`;
        }
    }
    formatMinute(minute) {
        return minute.toString().padStart(2, '0');
    }
    formatSecond(second) {
        return second.toString().padStart(2, '0');
    }
    formatPeriod(isAM) {
        try {
            const localeStr = this.locale.toString();
            if (!localeStr || localeStr.length === 0) {
                return isAM ? 'AM' : 'PM';
            }
            if (this.isChineseLocale()) {
                return isAM ? '上午' : '下午';
            }
            const hour = isAM ? 10 : 22;
            const dateFormat = new Intl.DateTimeFormat(localeStr, {
                hour: 'numeric',
                hour12: true
            });
            const date = new Date(2026, 0, 1, hour, 0, 0);
            const formatted = dateFormat.format(date);
            if (formatted.includes('上午')) {
                return isAM ? '上午' : '下午';
            }
            else if (formatted.includes('下午')) {
                return isAM ? '上午' : '下午';
            }
            else if (formatted.includes('AM') || formatted.includes('am')) {
                return isAM ? 'AM' : 'PM';
            }
            else if (formatted.includes('PM') || formatted.includes('pm')) {
                return isAM ? 'AM' : 'PM';
            }
            return isAM ? 'AM' : 'PM';
        }
        catch (error) {
            return isAM ? 'AM' : 'PM';
        }
    }
    getDaysInMonth(year, month) {
        const monthsWith31Days = [0, 2, 4, 6, 7, 9, 11];
        const monthsWith30Days = [3, 5, 8, 10];
        if (month === 1) {
            const isLeapYear = (year % 4 === 0 && year % 100 !== 0) || (year % 400 === 0);
            return isLeapYear ? 29 : 28;
        }
        else if (monthsWith31Days.includes(month)) {
            return 31;
        }
        else if (monthsWith30Days.includes(month)) {
            return 30;
        }
        return 30;
    }
    onOptionsChange() {
        if (this.options.displayMode !== undefined) {
            this.displayMode = this.options.displayMode;
        }
        if (this.options.dateOptions !== undefined) {
            this.updateDateOptions(this.options.dateOptions);
        }
        if (this.options.timeOptions !== undefined) {
            this.updateTimeOptions(this.options.timeOptions);
        }
        this.initArrays();
    }
    updateDateOptions(dateOptions) {
        if (dateOptions.mode !== undefined) {
            this.dateMode = dateOptions.mode;
        }
        if (dateOptions.lunar !== undefined) {
            this.lunar = dateOptions.lunar;
            if (this.lunar) {
                this.lunarCalendar = i18n.getCalendar(this.locale.toString(), 'chinese');
            }
            else {
                this.lunarCalendar = null;
            }
        }
        if (dateOptions.loop !== undefined) {
            this.canLoop = dateOptions.loop;
        }
        if (dateOptions.enableHapticFeedback !== undefined) {
            this.hapticFeedback = dateOptions.enableHapticFeedback;
        }
        if (dateOptions.start !== undefined) {
            const year = dateOptions.start.getFullYear();
            this.startYear = Math.max(DatePickerConstant.MIN_YEAR, Math.min(DatePickerConstant.MAX_YEAR, year));
        }
        if (dateOptions.end !== undefined) {
            const year = dateOptions.end.getFullYear();
            this.endYear = Math.max(DatePickerConstant.MIN_YEAR, Math.min(DatePickerConstant.MAX_YEAR, year));
        }
        if (this.startYear > this.endYear) {
            const temp = this.startYear;
            this.startYear = this.endYear;
            this.endYear = temp;
        }
        if (dateOptions.selected !== undefined) {
            if (this.initFlag) {
                this.initFlag = false;
                if (this.lunar && this.lunarCalendar !== null) {
                    this.lunarCalendar.setTime(dateOptions.selected);
                    const lunarMonth = this.lunarCalendar.get('month');
                    const lunarDay = this.lunarCalendar.get('date');
                    // Use Gregorian year from Date object directly, do not reverse derive from sexagenary cycle
                    // lunarCalendar.get('year') returns sexagenary cycle (1-60 cycle), cannot accurately derive Gregorian year
                    this.selectedYear = dateOptions.selected.getFullYear();
                    this.selectedMonth = lunarMonth;
                    this.selectedDay = lunarDay;
                }
                else {
                    this.selectedYear = dateOptions.selected.getFullYear();
                    this.selectedMonth = dateOptions.selected.getMonth();
                    this.selectedDay = dateOptions.selected.getDate();
                }
            }
        }
        else {
            if (this.initFlag) {
                this.initFlag = false;
                const now = new Date();
                if (this.lunar && this.lunarCalendar !== null) {
                    this.lunarCalendar.setTime(now);
                    const lunarMonth = this.lunarCalendar.get('month');
                    const lunarDay = this.lunarCalendar.get('date');
                    // Use Gregorian year from Date object directly
                    this.selectedYear = now.getFullYear();
                    this.selectedMonth = lunarMonth;
                    this.selectedDay = lunarDay;
                }
                else {
                    this.selectedYear = now.getFullYear();
                    this.selectedMonth = now.getMonth();
                    this.selectedDay = now.getDate();
                }
            }
        }
        if (dateOptions.onChange !== undefined) {
            this.onChange = dateOptions.onChange;
        }
        if (dateOptions.onScrollStop !== undefined) {
            this.onScrollStop = dateOptions.onScrollStop;
        }
    }
    updateTimeOptions(timeOptions) {
        if (timeOptions.format !== undefined) {
            this.timeFormat = timeOptions.format;
        }
        if (timeOptions.useMilitaryTime !== undefined) {
            this.useMilitaryTime = timeOptions.useMilitaryTime;
        }
        if (timeOptions.loop !== undefined) {
            this.canLoop = timeOptions.loop;
        }
        if (timeOptions.enableHapticFeedback !== undefined) {
            this.hapticFeedback = timeOptions.enableHapticFeedback;
        }
        if (timeOptions.selected !== undefined) {
            if (this.initFlag) {
                this.initFlag = false;
                this.selectedHour = timeOptions.selected.getHours();
                this.selectedMinute = timeOptions.selected.getMinutes();
                this.selectedSecond = timeOptions.selected.getSeconds();
            }
        }
        else {
            if (this.initFlag) {
                this.initFlag = false;
                const now = new Date();
                this.selectedHour = now.getHours();
                this.selectedMinute = now.getMinutes();
                this.selectedSecond = now.getSeconds();
            }
        }
        if (timeOptions.onChange !== undefined) {
            this.onChange = timeOptions.onChange;
        }
        if (timeOptions.onScrollStop !== undefined) {
            this.onScrollStop = timeOptions.onScrollStop;
        }
    }
    getResult() {
        const result = new DatePickerComponentResult();
        result.year = this.selectedYear;
        result.month = this.selectedMonth;
        result.day = this.selectedDay;
        result.hour = this.selectedHour;
        result.minute = this.selectedMinute;
        result.second = this.selectedSecond;
        return result;
    }
    onYearChange(selectedIndex) {
        this.selectedYear = this.startYear + selectedIndex;
        this.updateDaysArray();
        this.onChange?.(this.getResult());
    }
    onMonthChange(selectedIndex) {
        this.selectedMonth = selectedIndex;
        this.updateDaysArray();
        this.onChange?.(this.getResult());
    }
    onDayChange(selectedIndex) {
        this.selectedDay = selectedIndex + 1;
        this.onChange?.(this.getResult());
    }
    onHourChange(selectedIndex) {
        if (this.useMilitaryTime) {
            this.selectedHour = selectedIndex;
        }
        else {
            const displayHour = selectedIndex + 1;
            if (displayHour === 12) {
                if (this.selectedPeriod === 0) {
                    this.selectedHour = 0;
                }
                else {
                    this.selectedHour = 12;
                }
            }
            else {
                if (this.selectedPeriod === 0) {
                    this.selectedHour = displayHour;
                }
                else {
                    this.selectedHour = displayHour + 12;
                }
            }
        }
        this.onChange?.(this.getResult());
    }
    onPeriodChange(selectedIndex) {
        this.selectedPeriod = selectedIndex;
        if (!this.useMilitaryTime) {
            const displayHourIndex = this.getHourSelectedIndex();
            const displayHour = displayHourIndex + 1;
            if (displayHour === 12) {
                if (this.selectedPeriod === 0) {
                    this.selectedHour = 0;
                }
                else {
                    this.selectedHour = 12;
                }
            }
            else {
                if (this.selectedPeriod === 0) {
                    this.selectedHour = displayHour;
                }
                else {
                    this.selectedHour = displayHour + 12;
                }
            }
        }
        this.onChange?.(this.getResult());
    }
    onMinuteChange(selectedIndex) {
        this.selectedMinute = selectedIndex;
        this.onChange?.(this.getResult());
    }
    onSecondChange(selectedIndex) {
        this.selectedSecond = selectedIndex;
        this.onChange?.(this.getResult());
    }
    updateDaysArray() {
        if (this.lunar) {
            const lunarDays = this.getLunarDaysInMonth(this.selectedYear, this.selectedMonth);
            if (this.selectedDay > lunarDays) {
                this.selectedDay = lunarDays;
            }
            this.initLunarDayArray();
        }
        else {
            const daysInMonth = this.getDaysInMonth(this.selectedYear, this.selectedMonth);
            if (this.selectedDay > daysInMonth) {
                this.selectedDay = daysInMonth;
            }
            this.initDayArray();
        }
    }
    getYearSelectedIndex() {
        return this.selectedYear - this.startYear;
    }
    getMonthSelectedIndex() {
        return this.selectedMonth;
    }
    getDaySelectedIndex() {
        return this.selectedDay - 1;
    }
    getHourSelectedIndex() {
        if (this.useMilitaryTime) {
            return this.selectedHour;
        }
        else {
            if (this.selectedHour === 0) {
                return 11;
            }
            else if (this.selectedHour === 12) {
                return 11;
            }
            else if (this.selectedHour > 12) {
                return this.selectedHour - 13;
            }
            else {
                return this.selectedHour - 1;
            }
        }
    }
    getPeriodSelectedIndex() {
        return this.selectedPeriod;
    }
    getMinuteSelectedIndex() {
        return this.selectedMinute;
    }
    getSecondSelectedIndex() {
        return this.selectedSecond;
    }
    getFirstPickerIndicator(radius = 20) {
        return {
            type: PickerIndicatorType.BACKGROUND,
            borderRadius: {
                topLeft: radius,
                topRight: 0,
                bottomLeft: radius,
                bottomRight: 0
            }
        };
    }
    getMiddlePickerIndicator() {
        return {
            type: PickerIndicatorType.BACKGROUND,
            borderRadius: {
                topLeft: 0,
                topRight: 0,
                bottomLeft: 0,
                bottomRight: 0
            }
        };
    }
    getLastPickerIndicator(radius = 20) {
        return {
            type: PickerIndicatorType.BACKGROUND,
            borderRadius: {
                topLeft: 0,
                topRight: radius,
                bottomLeft: 0,
                bottomRight: radius
            }
        };
    }
    initialRender() {
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            Row.create();
            Row.width('100%');
        }, Row);
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.displayMode === DisplayMode.DATE || this.displayMode === DisplayMode.DATE_TIME) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (this.dateMode === DateMode.DATE) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    UIPickerComponent.create({ selectedIndex: this.getYearSelectedIndex() });
                                    UIPickerComponent.width(this.displayMode === DisplayMode.DATE_TIME ? '17%' : '34%');
                                    UIPickerComponent.height(200);
                                    UIPickerComponent.canLoop(this.canLoop);
                                    UIPickerComponent.enableHapticFeedback(this.hapticFeedback);
                                    UIPickerComponent.selectionIndicator(this.getFirstPickerIndicator());
                                    UIPickerComponent.onChange((selectedIndex) => {
                                        this.onYearChange(selectedIndex);
                                    });
                                    UIPickerComponent.onScrollStop((selectedIndex) => {
                                        this.selectedYear = this.startYear + selectedIndex;
                                        this.updateDaysArray();
                                        this.onScrollStop?.(this.getResult());
                                    });
                                }, UIPickerComponent);
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    ForEach.create();
                                    const forEachItemGenFunction = _item => {
                                        const item = _item;
                                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                                            Text.create(item);
                                        }, Text);
                                        Text.pop();
                                    };
                                    this.forEachUpdateFunction(elmtId, this.yearArray, forEachItemGenFunction);
                                }, ForEach);
                                ForEach.pop();
                                UIPickerComponent.pop();
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    UIPickerComponent.create({ selectedIndex: this.getMonthSelectedIndex() });
                                    UIPickerComponent.width(this.displayMode === DisplayMode.DATE_TIME ? '16%' : '33%');
                                    UIPickerComponent.height(200);
                                    UIPickerComponent.canLoop(this.canLoop);
                                    UIPickerComponent.enableHapticFeedback(this.hapticFeedback);
                                    UIPickerComponent.selectionIndicator(this.getMiddlePickerIndicator());
                                    UIPickerComponent.onChange((selectedIndex) => {
                                        this.onMonthChange(selectedIndex);
                                    });
                                    UIPickerComponent.onScrollStop((selectedIndex) => {
                                        this.selectedMonth = selectedIndex;
                                        this.onScrollStop?.(this.getResult());
                                    });
                                }, UIPickerComponent);
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    ForEach.create();
                                    const forEachItemGenFunction = _item => {
                                        const item = _item;
                                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                                            Text.create(item);
                                        }, Text);
                                        Text.pop();
                                    };
                                    this.forEachUpdateFunction(elmtId, this.monthArray, forEachItemGenFunction);
                                }, ForEach);
                                ForEach.pop();
                                UIPickerComponent.pop();
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    UIPickerComponent.create({ selectedIndex: this.getDaySelectedIndex() });
                                    UIPickerComponent.width(this.displayMode === DisplayMode.DATE_TIME ? '17%' : '33%');
                                    UIPickerComponent.height(200);
                                    UIPickerComponent.canLoop(this.canLoop);
                                    UIPickerComponent.enableHapticFeedback(this.hapticFeedback);
                                    UIPickerComponent.selectionIndicator(this.displayMode === DisplayMode.DATE_TIME ? this.getMiddlePickerIndicator() : this.getLastPickerIndicator());
                                    UIPickerComponent.onChange((selectedIndex) => {
                                        this.onDayChange(selectedIndex);
                                    });
                                    UIPickerComponent.onScrollStop((selectedIndex) => {
                                        this.selectedDay = selectedIndex + 1;
                                        this.onScrollStop?.(this.getResult());
                                    });
                                }, UIPickerComponent);
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    ForEach.create();
                                    const forEachItemGenFunction = _item => {
                                        const item = _item;
                                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                                            Text.create(item);
                                        }, Text);
                                        Text.pop();
                                    };
                                    this.forEachUpdateFunction(elmtId, this.dayArray, forEachItemGenFunction);
                                }, ForEach);
                                ForEach.pop();
                                UIPickerComponent.pop();
                            });
                        }
                        else if (this.dateMode === DateMode.YEAR_AND_MONTH) {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    UIPickerComponent.create({ selectedIndex: this.getYearSelectedIndex() });
                                    UIPickerComponent.width(this.displayMode === DisplayMode.DATE_TIME ? '25%' : '50%');
                                    UIPickerComponent.height(200);
                                    UIPickerComponent.canLoop(this.canLoop);
                                    UIPickerComponent.enableHapticFeedback(this.hapticFeedback);
                                    UIPickerComponent.selectionIndicator(this.getFirstPickerIndicator());
                                    UIPickerComponent.onChange((selectedIndex) => {
                                        this.onYearChange(selectedIndex);
                                    });
                                    UIPickerComponent.onScrollStop((selectedIndex) => {
                                        this.selectedYear = this.startYear + selectedIndex;
                                        this.updateDaysArray();
                                        this.onScrollStop?.(this.getResult());
                                    });
                                }, UIPickerComponent);
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    ForEach.create();
                                    const forEachItemGenFunction = _item => {
                                        const item = _item;
                                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                                            Text.create(item);
                                        }, Text);
                                        Text.pop();
                                    };
                                    this.forEachUpdateFunction(elmtId, this.yearArray, forEachItemGenFunction);
                                }, ForEach);
                                ForEach.pop();
                                UIPickerComponent.pop();
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    UIPickerComponent.create({ selectedIndex: this.getMonthSelectedIndex() });
                                    UIPickerComponent.width(this.displayMode === DisplayMode.DATE_TIME ? '25%' : '50%');
                                    UIPickerComponent.height(200);
                                    UIPickerComponent.canLoop(this.canLoop);
                                    UIPickerComponent.enableHapticFeedback(this.hapticFeedback);
                                    UIPickerComponent.selectionIndicator(this.displayMode === DisplayMode.DATE_TIME ? this.getMiddlePickerIndicator() : this.getLastPickerIndicator());
                                    UIPickerComponent.onChange((selectedIndex) => {
                                        this.onMonthChange(selectedIndex);
                                    });
                                    UIPickerComponent.onScrollStop((selectedIndex) => {
                                        this.selectedMonth = selectedIndex;
                                        this.onScrollStop?.(this.getResult());
                                    });
                                }, UIPickerComponent);
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    ForEach.create();
                                    const forEachItemGenFunction = _item => {
                                        const item = _item;
                                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                                            Text.create(item);
                                        }, Text);
                                        Text.pop();
                                    };
                                    this.forEachUpdateFunction(elmtId, this.monthArray, forEachItemGenFunction);
                                }, ForEach);
                                ForEach.pop();
                                UIPickerComponent.pop();
                            });
                        }
                        else if (this.dateMode === DateMode.MONTH_AND_DAY) {
                            this.ifElseBranchUpdateFunction(2, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    UIPickerComponent.create({ selectedIndex: this.getMonthSelectedIndex() });
                                    UIPickerComponent.width(this.displayMode === DisplayMode.DATE_TIME ? '25%' : '50%');
                                    UIPickerComponent.height(200);
                                    UIPickerComponent.canLoop(this.canLoop);
                                    UIPickerComponent.enableHapticFeedback(this.hapticFeedback);
                                    UIPickerComponent.selectionIndicator(this.getFirstPickerIndicator());
                                    UIPickerComponent.onChange((selectedIndex) => {
                                        this.onMonthChange(selectedIndex);
                                    });
                                    UIPickerComponent.onScrollStop((selectedIndex) => {
                                        this.selectedMonth = selectedIndex;
                                        this.onScrollStop?.(this.getResult());
                                    });
                                }, UIPickerComponent);
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    ForEach.create();
                                    const forEachItemGenFunction = _item => {
                                        const item = _item;
                                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                                            Text.create(item);
                                        }, Text);
                                        Text.pop();
                                    };
                                    this.forEachUpdateFunction(elmtId, this.monthArray, forEachItemGenFunction);
                                }, ForEach);
                                ForEach.pop();
                                UIPickerComponent.pop();
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    UIPickerComponent.create({ selectedIndex: this.getDaySelectedIndex() });
                                    UIPickerComponent.width(this.displayMode === DisplayMode.DATE_TIME ? '25%' : '50%');
                                    UIPickerComponent.height(200);
                                    UIPickerComponent.canLoop(this.canLoop);
                                    UIPickerComponent.enableHapticFeedback(this.hapticFeedback);
                                    UIPickerComponent.selectionIndicator(this.displayMode === DisplayMode.DATE_TIME ? this.getMiddlePickerIndicator() : this.getLastPickerIndicator());
                                    UIPickerComponent.onChange((selectedIndex) => {
                                        this.onDayChange(selectedIndex);
                                    });
                                    UIPickerComponent.onScrollStop((selectedIndex) => {
                                        this.selectedDay = selectedIndex + 1;
                                        this.onScrollStop?.(this.getResult());
                                    });
                                }, UIPickerComponent);
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    ForEach.create();
                                    const forEachItemGenFunction = _item => {
                                        const item = _item;
                                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                                            Text.create(item);
                                        }, Text);
                                        Text.pop();
                                    };
                                    this.forEachUpdateFunction(elmtId, this.dayArray, forEachItemGenFunction);
                                }, ForEach);
                                ForEach.pop();
                                UIPickerComponent.pop();
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(3, () => {
                            });
                        }
                    }, If);
                    If.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        this.observeComponentCreation2((elmtId, isInitialRender) => {
            If.create();
            if (this.displayMode === DisplayMode.TIME || this.displayMode === DisplayMode.DATE_TIME) {
                this.ifElseBranchUpdateFunction(0, () => {
                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                        If.create();
                        if (this.timeFormat === TimeFormat.HOUR_MINUTE) {
                            this.ifElseBranchUpdateFunction(0, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    If.create();
                                    if (this.useMilitaryTime) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                UIPickerComponent.create({ selectedIndex: this.getHourSelectedIndex() });
                                                UIPickerComponent.width(this.displayMode === DisplayMode.DATE_TIME ? '25%' : '50%');
                                                UIPickerComponent.height(200);
                                                UIPickerComponent.canLoop(this.canLoop);
                                                UIPickerComponent.enableHapticFeedback(this.hapticFeedback);
                                                UIPickerComponent.selectionIndicator(this.displayMode === DisplayMode.DATE_TIME ? this.getMiddlePickerIndicator() : this.getFirstPickerIndicator());
                                                UIPickerComponent.onChange((selectedIndex) => {
                                                    this.onHourChange(selectedIndex);
                                                });
                                                UIPickerComponent.onScrollStop((selectedIndex) => {
                                                    this.selectedHour = selectedIndex;
                                                    this.onScrollStop?.(this.getResult());
                                                });
                                            }, UIPickerComponent);
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                ForEach.create();
                                                const forEachItemGenFunction = _item => {
                                                    const item = _item;
                                                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                        Text.create(item);
                                                    }, Text);
                                                    Text.pop();
                                                };
                                                this.forEachUpdateFunction(elmtId, this.hourArray, forEachItemGenFunction);
                                            }, ForEach);
                                            ForEach.pop();
                                            UIPickerComponent.pop();
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                UIPickerComponent.create({ selectedIndex: this.getMinuteSelectedIndex() });
                                                UIPickerComponent.width(this.displayMode === DisplayMode.DATE_TIME ? '25%' : '50%');
                                                UIPickerComponent.height(200);
                                                UIPickerComponent.canLoop(this.canLoop);
                                                UIPickerComponent.enableHapticFeedback(this.hapticFeedback);
                                                UIPickerComponent.selectionIndicator(this.getLastPickerIndicator());
                                                UIPickerComponent.onChange((selectedIndex) => {
                                                    this.onMinuteChange(selectedIndex);
                                                });
                                                UIPickerComponent.onScrollStop((selectedIndex) => {
                                                    this.selectedMinute = selectedIndex;
                                                    this.onScrollStop?.(this.getResult());
                                                });
                                            }, UIPickerComponent);
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                ForEach.create();
                                                const forEachItemGenFunction = _item => {
                                                    const item = _item;
                                                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                        Text.create(item);
                                                    }, Text);
                                                    Text.pop();
                                                };
                                                this.forEachUpdateFunction(elmtId, this.minuteArray, forEachItemGenFunction);
                                            }, ForEach);
                                            ForEach.pop();
                                            UIPickerComponent.pop();
                                        });
                                    }
                                    else {
                                        this.ifElseBranchUpdateFunction(1, () => {
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                UIPickerComponent.create({ selectedIndex: this.getPeriodSelectedIndex() });
                                                UIPickerComponent.width(this.displayMode === DisplayMode.DATE_TIME ? '17%' : '33%');
                                                UIPickerComponent.height(200);
                                                UIPickerComponent.canLoop(false);
                                                UIPickerComponent.enableHapticFeedback(this.hapticFeedback);
                                                UIPickerComponent.selectionIndicator(this.displayMode === DisplayMode.DATE_TIME ? this.getMiddlePickerIndicator() : this.getFirstPickerIndicator());
                                                UIPickerComponent.onChange((selectedIndex) => {
                                                    this.onPeriodChange(selectedIndex);
                                                });
                                                UIPickerComponent.onScrollStop((selectedIndex) => {
                                                    this.selectedPeriod = selectedIndex;
                                                    this.onScrollStop?.(this.getResult());
                                                });
                                            }, UIPickerComponent);
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                ForEach.create();
                                                const forEachItemGenFunction = _item => {
                                                    const item = _item;
                                                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                        Text.create(item);
                                                    }, Text);
                                                    Text.pop();
                                                };
                                                this.forEachUpdateFunction(elmtId, this.periodArray, forEachItemGenFunction);
                                            }, ForEach);
                                            ForEach.pop();
                                            UIPickerComponent.pop();
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                UIPickerComponent.create({ selectedIndex: this.getHourSelectedIndex() });
                                                UIPickerComponent.width(this.displayMode === DisplayMode.DATE_TIME ? '16%' : '34%');
                                                UIPickerComponent.height(200);
                                                UIPickerComponent.canLoop(this.canLoop);
                                                UIPickerComponent.enableHapticFeedback(this.hapticFeedback);
                                                UIPickerComponent.selectionIndicator(this.getMiddlePickerIndicator());
                                                UIPickerComponent.onChange((selectedIndex) => {
                                                    this.onHourChange(selectedIndex);
                                                });
                                                UIPickerComponent.onScrollStop((selectedIndex) => {
                                                    this.onHourChange(selectedIndex);
                                                    this.onScrollStop?.(this.getResult());
                                                });
                                            }, UIPickerComponent);
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                ForEach.create();
                                                const forEachItemGenFunction = _item => {
                                                    const item = _item;
                                                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                        Text.create(item);
                                                    }, Text);
                                                    Text.pop();
                                                };
                                                this.forEachUpdateFunction(elmtId, this.hourArray, forEachItemGenFunction);
                                            }, ForEach);
                                            ForEach.pop();
                                            UIPickerComponent.pop();
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                UIPickerComponent.create({ selectedIndex: this.getMinuteSelectedIndex() });
                                                UIPickerComponent.width(this.displayMode === DisplayMode.DATE_TIME ? '17%' : '33%');
                                                UIPickerComponent.height(200);
                                                UIPickerComponent.canLoop(this.canLoop);
                                                UIPickerComponent.enableHapticFeedback(this.hapticFeedback);
                                                UIPickerComponent.selectionIndicator(this.getLastPickerIndicator());
                                                UIPickerComponent.onChange((selectedIndex) => {
                                                    this.onMinuteChange(selectedIndex);
                                                });
                                                UIPickerComponent.onScrollStop((selectedIndex) => {
                                                    this.selectedMinute = selectedIndex;
                                                    this.onScrollStop?.(this.getResult());
                                                });
                                            }, UIPickerComponent);
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                ForEach.create();
                                                const forEachItemGenFunction = _item => {
                                                    const item = _item;
                                                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                        Text.create(item);
                                                    }, Text);
                                                    Text.pop();
                                                };
                                                this.forEachUpdateFunction(elmtId, this.minuteArray, forEachItemGenFunction);
                                            }, ForEach);
                                            ForEach.pop();
                                            UIPickerComponent.pop();
                                        });
                                    }
                                }, If);
                                If.pop();
                            });
                        }
                        else if (this.timeFormat === TimeFormat.HOUR_MINUTE_SECOND) {
                            this.ifElseBranchUpdateFunction(1, () => {
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    If.create();
                                    if (this.useMilitaryTime) {
                                        this.ifElseBranchUpdateFunction(0, () => {
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                UIPickerComponent.create({ selectedIndex: this.getHourSelectedIndex() });
                                                UIPickerComponent.width(this.displayMode === DisplayMode.DATE_TIME ? '17%' : '34%');
                                                UIPickerComponent.height(200);
                                                UIPickerComponent.canLoop(this.canLoop);
                                                UIPickerComponent.enableHapticFeedback(this.hapticFeedback);
                                                UIPickerComponent.selectionIndicator(this.displayMode === DisplayMode.DATE_TIME ? this.getMiddlePickerIndicator() : this.getFirstPickerIndicator());
                                                UIPickerComponent.onChange((selectedIndex) => {
                                                    this.onHourChange(selectedIndex);
                                                });
                                                UIPickerComponent.onScrollStop((selectedIndex) => {
                                                    this.selectedHour = selectedIndex;
                                                    this.onScrollStop?.(this.getResult());
                                                });
                                            }, UIPickerComponent);
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                ForEach.create();
                                                const forEachItemGenFunction = _item => {
                                                    const item = _item;
                                                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                        Text.create(item);
                                                    }, Text);
                                                    Text.pop();
                                                };
                                                this.forEachUpdateFunction(elmtId, this.hourArray, forEachItemGenFunction);
                                            }, ForEach);
                                            ForEach.pop();
                                            UIPickerComponent.pop();
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                UIPickerComponent.create({ selectedIndex: this.getMinuteSelectedIndex() });
                                                UIPickerComponent.width(this.displayMode === DisplayMode.DATE_TIME ? '16%' : '33%');
                                                UIPickerComponent.height(200);
                                                UIPickerComponent.canLoop(this.canLoop);
                                                UIPickerComponent.enableHapticFeedback(this.hapticFeedback);
                                                UIPickerComponent.selectionIndicator(this.getMiddlePickerIndicator());
                                                UIPickerComponent.onChange((selectedIndex) => {
                                                    this.onMinuteChange(selectedIndex);
                                                });
                                                UIPickerComponent.onScrollStop((selectedIndex) => {
                                                    this.selectedMinute = selectedIndex;
                                                    this.onScrollStop?.(this.getResult());
                                                });
                                            }, UIPickerComponent);
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                ForEach.create();
                                                const forEachItemGenFunction = _item => {
                                                    const item = _item;
                                                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                        Text.create(item);
                                                    }, Text);
                                                    Text.pop();
                                                };
                                                this.forEachUpdateFunction(elmtId, this.minuteArray, forEachItemGenFunction);
                                            }, ForEach);
                                            ForEach.pop();
                                            UIPickerComponent.pop();
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                UIPickerComponent.create({ selectedIndex: this.getSecondSelectedIndex() });
                                                UIPickerComponent.width(this.displayMode === DisplayMode.DATE_TIME ? '17%' : '33%');
                                                UIPickerComponent.height(200);
                                                UIPickerComponent.canLoop(this.canLoop);
                                                UIPickerComponent.enableHapticFeedback(this.hapticFeedback);
                                                UIPickerComponent.selectionIndicator(this.getLastPickerIndicator());
                                                UIPickerComponent.onChange((selectedIndex) => {
                                                    this.onSecondChange(selectedIndex);
                                                });
                                                UIPickerComponent.onScrollStop((selectedIndex) => {
                                                    this.selectedSecond = selectedIndex;
                                                    this.onScrollStop?.(this.getResult());
                                                });
                                            }, UIPickerComponent);
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                ForEach.create();
                                                const forEachItemGenFunction = _item => {
                                                    const item = _item;
                                                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                        Text.create(item);
                                                    }, Text);
                                                    Text.pop();
                                                };
                                                this.forEachUpdateFunction(elmtId, this.secondArray, forEachItemGenFunction);
                                            }, ForEach);
                                            ForEach.pop();
                                            UIPickerComponent.pop();
                                        });
                                    }
                                    else {
                                        this.ifElseBranchUpdateFunction(1, () => {
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                UIPickerComponent.create({ selectedIndex: this.getPeriodSelectedIndex() });
                                                UIPickerComponent.width(this.displayMode === DisplayMode.DATE_TIME ? '12%' : '25%');
                                                UIPickerComponent.height(200);
                                                UIPickerComponent.canLoop(false);
                                                UIPickerComponent.enableHapticFeedback(this.hapticFeedback);
                                                UIPickerComponent.selectionIndicator(this.displayMode === DisplayMode.DATE_TIME ? this.getMiddlePickerIndicator() : this.getFirstPickerIndicator());
                                                UIPickerComponent.onChange((selectedIndex) => {
                                                    this.onPeriodChange(selectedIndex);
                                                });
                                                UIPickerComponent.onScrollStop((selectedIndex) => {
                                                    this.selectedPeriod = selectedIndex;
                                                    this.onScrollStop?.(this.getResult());
                                                });
                                            }, UIPickerComponent);
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                ForEach.create();
                                                const forEachItemGenFunction = _item => {
                                                    const item = _item;
                                                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                        Text.create(item);
                                                    }, Text);
                                                    Text.pop();
                                                };
                                                this.forEachUpdateFunction(elmtId, this.periodArray, forEachItemGenFunction);
                                            }, ForEach);
                                            ForEach.pop();
                                            UIPickerComponent.pop();
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                UIPickerComponent.create({ selectedIndex: this.getHourSelectedIndex() });
                                                UIPickerComponent.width(this.displayMode === DisplayMode.DATE_TIME ? '13%' : '25%');
                                                UIPickerComponent.height(200);
                                                UIPickerComponent.canLoop(this.canLoop);
                                                UIPickerComponent.enableHapticFeedback(this.hapticFeedback);
                                                UIPickerComponent.selectionIndicator(this.getMiddlePickerIndicator());
                                                UIPickerComponent.onChange((selectedIndex) => {
                                                    this.onHourChange(selectedIndex);
                                                });
                                                UIPickerComponent.onScrollStop((selectedIndex) => {
                                                    this.onHourChange(selectedIndex);
                                                    this.onScrollStop?.(this.getResult());
                                                });
                                            }, UIPickerComponent);
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                ForEach.create();
                                                const forEachItemGenFunction = _item => {
                                                    const item = _item;
                                                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                        Text.create(item);
                                                    }, Text);
                                                    Text.pop();
                                                };
                                                this.forEachUpdateFunction(elmtId, this.hourArray, forEachItemGenFunction);
                                            }, ForEach);
                                            ForEach.pop();
                                            UIPickerComponent.pop();
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                UIPickerComponent.create({ selectedIndex: this.getMinuteSelectedIndex() });
                                                UIPickerComponent.width(this.displayMode === DisplayMode.DATE_TIME ? '13%' : '25%');
                                                UIPickerComponent.height(200);
                                                UIPickerComponent.canLoop(this.canLoop);
                                                UIPickerComponent.enableHapticFeedback(this.hapticFeedback);
                                                UIPickerComponent.selectionIndicator(this.getMiddlePickerIndicator());
                                                UIPickerComponent.onChange((selectedIndex) => {
                                                    this.onMinuteChange(selectedIndex);
                                                });
                                                UIPickerComponent.onScrollStop((selectedIndex) => {
                                                    this.selectedMinute = selectedIndex;
                                                    this.onScrollStop?.(this.getResult());
                                                });
                                            }, UIPickerComponent);
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                ForEach.create();
                                                const forEachItemGenFunction = _item => {
                                                    const item = _item;
                                                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                        Text.create(item);
                                                    }, Text);
                                                    Text.pop();
                                                };
                                                this.forEachUpdateFunction(elmtId, this.minuteArray, forEachItemGenFunction);
                                            }, ForEach);
                                            ForEach.pop();
                                            UIPickerComponent.pop();
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                UIPickerComponent.create({ selectedIndex: this.getSecondSelectedIndex() });
                                                UIPickerComponent.width(this.displayMode === DisplayMode.DATE_TIME ? '12%' : '25%');
                                                UIPickerComponent.height(200);
                                                UIPickerComponent.canLoop(this.canLoop);
                                                UIPickerComponent.enableHapticFeedback(this.hapticFeedback);
                                                UIPickerComponent.selectionIndicator(this.getLastPickerIndicator());
                                                UIPickerComponent.onChange((selectedIndex) => {
                                                    this.onSecondChange(selectedIndex);
                                                });
                                                UIPickerComponent.onScrollStop((selectedIndex) => {
                                                    this.selectedSecond = selectedIndex;
                                                    this.onScrollStop?.(this.getResult());
                                                });
                                            }, UIPickerComponent);
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                ForEach.create();
                                                const forEachItemGenFunction = _item => {
                                                    const item = _item;
                                                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                        Text.create(item);
                                                    }, Text);
                                                    Text.pop();
                                                };
                                                this.forEachUpdateFunction(elmtId, this.secondArray, forEachItemGenFunction);
                                            }, ForEach);
                                            ForEach.pop();
                                            UIPickerComponent.pop();
                                        });
                                    }
                                }, If);
                                If.pop();
                            });
                        }
                        else {
                            this.ifElseBranchUpdateFunction(2, () => {
                            });
                        }
                    }, If);
                    If.pop();
                });
            }
            else {
                this.ifElseBranchUpdateFunction(1, () => {
                });
            }
        }, If);
        If.pop();
        Row.pop();
    }
    rerender() {
        this.updateDirtyElements();
    }
}

export default {
  DatePickerComponent,
  DateMode,
  DisplayMode,
  TimeFormat,
  DatePickerComponentResult,
  CommonOptions,
  DateOptions,
  TimeOptions,
  DatePickerComponentOptions,
};
