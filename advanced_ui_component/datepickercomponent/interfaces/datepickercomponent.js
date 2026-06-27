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
const commonEventManager = requireNapi('commonEventManager');
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
DatePickerConstant.SYSTEM_MIN_DATE = new Date(1970, 0, 1);
DatePickerConstant.SYSTEM_MAX_DATE = new Date(2100, 11, 31);
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
        this.__startMonth = new ObservedPropertySimplePU(DatePickerConstant.MIN_MONTH, this, "startMonth");
        this.__endMonth = new ObservedPropertySimplePU(DatePickerConstant.MAX_MONTH, this, "endMonth");
        this.__startDay = new ObservedPropertySimplePU(DatePickerConstant.MIN_DAY, this, "startDay");
        this.__endDay = new ObservedPropertySimplePU(31, this, "endDay");
        this.__startHour = new ObservedPropertySimplePU(DatePickerConstant.MIN_HOUR, this, "startHour");
        this.__endHour = new ObservedPropertySimplePU(DatePickerConstant.MAX_HOUR, this, "endHour");
        this.__startMinute = new ObservedPropertySimplePU(DatePickerConstant.MIN_MINUTE, this, "startMinute");
        this.__endMinute = new ObservedPropertySimplePU(DatePickerConstant.MAX_MINUTE, this, "endMinute");
        this.__startSecond = new ObservedPropertySimplePU(DatePickerConstant.MIN_SECOND, this, "startSecond");
        this.__endSecond = new ObservedPropertySimplePU(DatePickerConstant.MAX_SECOND, this, "endSecond");
        this.__dateMode = new ObservedPropertySimplePU(DateMode.DATE, this, "dateMode");
        this.__timeFormat = new ObservedPropertySimplePU(TimeFormat.HOUR_MINUTE, this, "timeFormat");
        this.__useMilitaryTime = new ObservedPropertySimplePU(false, this, "useMilitaryTime");
        this.__lunar = new ObservedPropertySimplePU(false, this, "lunar");
        this.__dateCanLoop = new ObservedPropertySimplePU(true, this, "dateCanLoop");
        this.__timeCanLoop = new ObservedPropertySimplePU(true, this, "timeCanLoop");
        this.__dateHapticFeedback = new ObservedPropertySimplePU(true, this, "dateHapticFeedback");
        this.__timeHapticFeedback = new ObservedPropertySimplePU(true, this, "timeHapticFeedback");
        this.__yearArray = new ObservedPropertyObjectPU([], this, "yearArray");
        this.__monthArray = new ObservedPropertyObjectPU([], this, "monthArray");
        this.__dayArray = new ObservedPropertyObjectPU([], this, "dayArray");
        this.__hourArray = new ObservedPropertyObjectPU([], this, "hourArray");
        this.__minuteArray = new ObservedPropertyObjectPU([], this, "minuteArray");
        this.__secondArray = new ObservedPropertyObjectPU([], this, "secondArray");
        this.__periodArray = new ObservedPropertyObjectPU([], this, "periodArray");
        this.__selectedPeriod = new ObservedPropertySimplePU(0, this, "selectedPeriod");
        this.dateOnChange = undefined;
        this.dateOnScrollStop = undefined;
        this.timeOnChange = undefined;
        this.timeOnScrollStop = undefined;
        this.__currentLocale = new ObservedPropertySimplePU('', this, "currentLocale");
        this.locale = new intl.Locale();
        this.initFlag = true;
        this.lunarCalendar = null;
        this.subscriber = null;
        this.formatter = new intl.NumberFormat();
        this.yearFormatter = new intl.NumberFormat('', { useGrouping: false });
        this.userLunar = false;
        this.__firstColumnWidth = new ObservedPropertySimplePU(0, this, "firstColumnWidth");
        this.__lastColumnWidth = new ObservedPropertySimplePU(0, this, "lastColumnWidth");
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
        if (params.startMonth !== undefined) {
            this.startMonth = params.startMonth;
        }
        if (params.endMonth !== undefined) {
            this.endMonth = params.endMonth;
        }
        if (params.startDay !== undefined) {
            this.startDay = params.startDay;
        }
        if (params.endDay !== undefined) {
            this.endDay = params.endDay;
        }
        if (params.startHour !== undefined) {
            this.startHour = params.startHour;
        }
        if (params.endHour !== undefined) {
            this.endHour = params.endHour;
        }
        if (params.startMinute !== undefined) {
            this.startMinute = params.startMinute;
        }
        if (params.endMinute !== undefined) {
            this.endMinute = params.endMinute;
        }
        if (params.startSecond !== undefined) {
            this.startSecond = params.startSecond;
        }
        if (params.endSecond !== undefined) {
            this.endSecond = params.endSecond;
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
        if (params.dateCanLoop !== undefined) {
            this.dateCanLoop = params.dateCanLoop;
        }
        if (params.timeCanLoop !== undefined) {
            this.timeCanLoop = params.timeCanLoop;
        }
        if (params.dateHapticFeedback !== undefined) {
            this.dateHapticFeedback = params.dateHapticFeedback;
        }
        if (params.timeHapticFeedback !== undefined) {
            this.timeHapticFeedback = params.timeHapticFeedback;
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
        if (params.dateOnChange !== undefined) {
            this.dateOnChange = params.dateOnChange;
        }
        if (params.dateOnScrollStop !== undefined) {
            this.dateOnScrollStop = params.dateOnScrollStop;
        }
        if (params.timeOnChange !== undefined) {
            this.timeOnChange = params.timeOnChange;
        }
        if (params.timeOnScrollStop !== undefined) {
            this.timeOnScrollStop = params.timeOnScrollStop;
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
        if (params.subscriber !== undefined) {
            this.subscriber = params.subscriber;
        }
        if (params.formatter !== undefined) {
            this.formatter = params.formatter;
        }
        if (params.yearFormatter !== undefined) {
            this.yearFormatter = params.yearFormatter;
        }
        if (params.userLunar !== undefined) {
            this.userLunar = params.userLunar;
        }
        if (params.firstColumnWidth !== undefined) {
            this.firstColumnWidth = params.firstColumnWidth;
        }
        if (params.lastColumnWidth !== undefined) {
            this.lastColumnWidth = params.lastColumnWidth;
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
        this.__startMonth.purgeDependencyOnElmtId(rmElmtId);
        this.__endMonth.purgeDependencyOnElmtId(rmElmtId);
        this.__startDay.purgeDependencyOnElmtId(rmElmtId);
        this.__endDay.purgeDependencyOnElmtId(rmElmtId);
        this.__startHour.purgeDependencyOnElmtId(rmElmtId);
        this.__endHour.purgeDependencyOnElmtId(rmElmtId);
        this.__startMinute.purgeDependencyOnElmtId(rmElmtId);
        this.__endMinute.purgeDependencyOnElmtId(rmElmtId);
        this.__startSecond.purgeDependencyOnElmtId(rmElmtId);
        this.__endSecond.purgeDependencyOnElmtId(rmElmtId);
        this.__dateMode.purgeDependencyOnElmtId(rmElmtId);
        this.__timeFormat.purgeDependencyOnElmtId(rmElmtId);
        this.__useMilitaryTime.purgeDependencyOnElmtId(rmElmtId);
        this.__lunar.purgeDependencyOnElmtId(rmElmtId);
        this.__dateCanLoop.purgeDependencyOnElmtId(rmElmtId);
        this.__timeCanLoop.purgeDependencyOnElmtId(rmElmtId);
        this.__dateHapticFeedback.purgeDependencyOnElmtId(rmElmtId);
        this.__timeHapticFeedback.purgeDependencyOnElmtId(rmElmtId);
        this.__yearArray.purgeDependencyOnElmtId(rmElmtId);
        this.__monthArray.purgeDependencyOnElmtId(rmElmtId);
        this.__dayArray.purgeDependencyOnElmtId(rmElmtId);
        this.__hourArray.purgeDependencyOnElmtId(rmElmtId);
        this.__minuteArray.purgeDependencyOnElmtId(rmElmtId);
        this.__secondArray.purgeDependencyOnElmtId(rmElmtId);
        this.__periodArray.purgeDependencyOnElmtId(rmElmtId);
        this.__selectedPeriod.purgeDependencyOnElmtId(rmElmtId);
        this.__currentLocale.purgeDependencyOnElmtId(rmElmtId);
        this.__firstColumnWidth.purgeDependencyOnElmtId(rmElmtId);
        this.__lastColumnWidth.purgeDependencyOnElmtId(rmElmtId);
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
        this.__startMonth.aboutToBeDeleted();
        this.__endMonth.aboutToBeDeleted();
        this.__startDay.aboutToBeDeleted();
        this.__endDay.aboutToBeDeleted();
        this.__startHour.aboutToBeDeleted();
        this.__endHour.aboutToBeDeleted();
        this.__startMinute.aboutToBeDeleted();
        this.__endMinute.aboutToBeDeleted();
        this.__startSecond.aboutToBeDeleted();
        this.__endSecond.aboutToBeDeleted();
        this.__dateMode.aboutToBeDeleted();
        this.__timeFormat.aboutToBeDeleted();
        this.__useMilitaryTime.aboutToBeDeleted();
        this.__lunar.aboutToBeDeleted();
        this.__dateCanLoop.aboutToBeDeleted();
        this.__timeCanLoop.aboutToBeDeleted();
        this.__dateHapticFeedback.aboutToBeDeleted();
        this.__timeHapticFeedback.aboutToBeDeleted();
        this.__yearArray.aboutToBeDeleted();
        this.__monthArray.aboutToBeDeleted();
        this.__dayArray.aboutToBeDeleted();
        this.__hourArray.aboutToBeDeleted();
        this.__minuteArray.aboutToBeDeleted();
        this.__secondArray.aboutToBeDeleted();
        this.__periodArray.aboutToBeDeleted();
        this.__selectedPeriod.aboutToBeDeleted();
        this.__currentLocale.aboutToBeDeleted();
        this.__firstColumnWidth.aboutToBeDeleted();
        this.__lastColumnWidth.aboutToBeDeleted();
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
    get startMonth() {
        return this.__startMonth.get();
    }
    set startMonth(newValue) {
        this.__startMonth.set(newValue);
    }
    get endMonth() {
        return this.__endMonth.get();
    }
    set endMonth(newValue) {
        this.__endMonth.set(newValue);
    }
    get startDay() {
        return this.__startDay.get();
    }
    set startDay(newValue) {
        this.__startDay.set(newValue);
    }
    get endDay() {
        return this.__endDay.get();
    }
    set endDay(newValue) {
        this.__endDay.set(newValue);
    }
    get startHour() {
        return this.__startHour.get();
    }
    set startHour(newValue) {
        this.__startHour.set(newValue);
    }
    get endHour() {
        return this.__endHour.get();
    }
    set endHour(newValue) {
        this.__endHour.set(newValue);
    }
    get startMinute() {
        return this.__startMinute.get();
    }
    set startMinute(newValue) {
        this.__startMinute.set(newValue);
    }
    get endMinute() {
        return this.__endMinute.get();
    }
    set endMinute(newValue) {
        this.__endMinute.set(newValue);
    }
    get startSecond() {
        return this.__startSecond.get();
    }
    set startSecond(newValue) {
        this.__startSecond.set(newValue);
    }
    get endSecond() {
        return this.__endSecond.get();
    }
    set endSecond(newValue) {
        this.__endSecond.set(newValue);
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
    get dateCanLoop() {
        return this.__dateCanLoop.get();
    }
    set dateCanLoop(newValue) {
        this.__dateCanLoop.set(newValue);
    }
    get timeCanLoop() {
        return this.__timeCanLoop.get();
    }
    set timeCanLoop(newValue) {
        this.__timeCanLoop.set(newValue);
    }
    get dateHapticFeedback() {
        return this.__dateHapticFeedback.get();
    }
    set dateHapticFeedback(newValue) {
        this.__dateHapticFeedback.set(newValue);
    }
    get timeHapticFeedback() {
        return this.__timeHapticFeedback.get();
    }
    set timeHapticFeedback(newValue) {
        this.__timeHapticFeedback.set(newValue);
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
    get firstColumnWidth() {
        return this.__firstColumnWidth.get();
    }
    set firstColumnWidth(newValue) {
        this.__firstColumnWidth.set(newValue);
    }
    get lastColumnWidth() {
        return this.__lastColumnWidth.get();
    }
    set lastColumnWidth(newValue) {
        this.__lastColumnWidth.set(newValue);
    }
    aboutToAppear() {
        this.currentLocale = i18n.System.getSystemLanguage();
        this.locale = new intl.Locale(this.currentLocale);
        this.formatter = new intl.NumberFormat();
        this.yearFormatter = new intl.NumberFormat(this.locale.toString(), { useGrouping: false });
        // Issue 2: Save user-set lunar value, decide whether to apply based on current language
        this.userLunar = this.lunar;
        const isChinese = this.isChineseLocale();
        if (!isChinese) {
            // Static scenario: non-Chinese language, force lunar to false
            this.lunar = false;
            this.lunarCalendar = null;
        }
        else {
            // Chinese language: apply lunar based on user setting
            if (this.lunar) {
                this.lunarCalendar = i18n.getCalendar(this.locale.toString(), 'chinese');
            }
        }
        if (this.selectedYear === 0 || this.selectedMonth === 0 || this.selectedDay === 0) {
            const now = new Date();
            this.selectedYear = now.getFullYear();
            this.selectedMonth = now.getMonth();
            this.selectedDay = now.getDate();
            this.selectedHour = now.getHours();
            this.selectedMinute = now.getMinutes();
            this.selectedSecond = now.getSeconds();
        }
        if (this.options !== undefined && this.options !== null) {
            this.onOptionsChange();
        }
        else {
            this.initArrays();
        }
        this.createLocaleChangeSubscriber();
    }
    aboutToDisappear() {
        this.lunarCalendar = null;
        // Unsubscribe from locale change events
        if (this.subscriber !== null) {
            commonEventManager.unsubscribe(this.subscriber, (err) => {
                if (err) {
                    console.error(`Failed to unsubscribe common event. error code: ${err.code}, message: ${err.message}.`);
                }
            });
            this.subscriber = null;
        }
    }
    createLocaleChangeSubscriber() {
        const subscribeInfo = {
            events: [commonEventManager.Support.COMMON_EVENT_LOCALE_CHANGED]
        };
        commonEventManager.createSubscriber(subscribeInfo)
            .then((commonEventSubscriber) => {
            this.subscriber = commonEventSubscriber;
            commonEventManager.subscribe(this.subscriber, (err, data) => {
                if (err) {
                    console.error(`Failed to subscribe common event. error code: ${err.code}, message: ${err.message}.`);
                    return;
                }
                // Update locale when system language changes
                this.currentLocale = i18n.System.getSystemLanguage();
            });
        })
            .catch((err) => {
            console.error(`CreateSubscriber failed, code is ${err.message}`);
        });
    }
    onLocaleChange() {
        this.locale = new intl.Locale(this.currentLocale);
        this.formatter = new intl.NumberFormat();
        this.yearFormatter = new intl.NumberFormat(this.locale.toString(), { useGrouping: false });
        const isChinese = this.isChineseLocale();
        const prevLunar = this.lunar;
        const prevLunarCalendar = this.lunarCalendar;
        // Handle lunar calendar based on language
        if (isChinese) {
            // Chinese locale: use user-set lunar value
            this.lunar = this.userLunar;
            if (this.lunar) {
                this.lunarCalendar = i18n.getCalendar(this.locale.toString(), 'chinese');
            }
            else {
                this.lunarCalendar = null;
            }
        }
        else {
            // Non-Chinese locale: disable lunar calendar but keep user setting
            this.lunar = false;
            this.lunarCalendar = null;
        }
        // Convert date when switching between lunar and gregorian modes
        if (prevLunar !== this.lunar) {
            if (!prevLunar && this.lunar && this.lunarCalendar !== null) {
                // Switching from gregorian to lunar: convert gregorian date to lunar date
                this.lunarCalendar.setTime(new Date(this.selectedYear, this.selectedMonth, this.selectedDay));
                this.selectedMonth = this.lunarCalendar.get('month');
                this.selectedDay = this.lunarCalendar.get('date');
            }
            else if (prevLunar && !this.lunar && prevLunarCalendar !== null) {
                // Switching from lunar to gregorian: convert lunar date to gregorian date
                // Use prevLunarCalendar for conversion since current lunarCalendar is null
                const gregorianDate = this.convertLunarToGregorianWithCalendar(prevLunarCalendar, this.selectedYear, this.selectedMonth, this.selectedDay);
                if (gregorianDate !== null) {
                    this.selectedYear = gregorianDate.getFullYear();
                    this.selectedMonth = gregorianDate.getMonth();
                    this.selectedDay = gregorianDate.getDate();
                }
            }
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
    convertLunarToGregorian(gregorianYear, lunarMonth, lunarDay) {
        return this.convertLunarToGregorianWithCalendar(this.lunarCalendar, gregorianYear, lunarMonth, lunarDay);
    }
    convertLunarToGregorianWithCalendar(calendar, gregorianYear, lunarMonth, lunarDay) {
        if (calendar === null) {
            return null;
        }
        try {
            // Find the gregorian date for the given lunar date
            // Iterate through gregorian dates to find matching lunar month and day
            for (let month = 0; month < 12; month++) {
                for (let day = 1; day <= 31; day++) {
                    const testDate = new Date(gregorianYear, month, day);
                    calendar.setTime(testDate);
                    const currentLunarMonth = calendar.get('month');
                    const currentLunarDay = calendar.get('date');
                    if (currentLunarMonth === lunarMonth && currentLunarDay === lunarDay) {
                        return testDate;
                    }
                }
            }
            return null;
        }
        catch (e) {
            return null;
        }
    }
    formatLunarYear(gregorianYear) {
        return `${this.yearFormatter.format(gregorianYear)}年`;
    }
    formatLunarMonth(month, isLeap) {
        const lunarMonthNames = ['正月', '二月', '三月', '四月', '五月', '六月',
            '七月', '八月', '九月', '十月', '冬月', '腊月'];
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
        let startMonthIndex = DatePickerConstant.MIN_MONTH;
        let endMonthIndex = DatePickerConstant.MAX_MONTH;
        if (this.selectedYear === this.startYear) {
            startMonthIndex = this.startMonth;
        }
        if (this.selectedYear === this.endYear) {
            endMonthIndex = this.endMonth;
        }
        for (let i = startMonthIndex; i <= endMonthIndex; i++) {
            this.monthArray.push(this.formatMonth(i));
        }
    }
    initDayArray() {
        this.dayArray = [];
        const daysInMonth = this.getDaysInMonth(this.selectedYear, this.selectedMonth);
        let startDayIndex = DatePickerConstant.MIN_DAY;
        let endDayIndex = daysInMonth;
        if (this.selectedYear === this.startYear && this.selectedMonth === this.startMonth) {
            startDayIndex = this.startDay;
        }
        if (this.selectedYear === this.endYear && this.selectedMonth === this.endMonth) {
            endDayIndex = Math.min(this.endDay, daysInMonth);
        }
        for (let i = startDayIndex; i <= endDayIndex; i++) {
            this.dayArray.push(this.formatDay(i));
        }
    }
    initTimeArrays() {
        this.periodArray = [];
        if (!this.useMilitaryTime) {
            this.selectedPeriod = this.selectedHour < 12 ? 0 : 1;
            this.updatePeriodArray();
            this.updateHourArrayFor12Hour();
        }
        else {
            this.hourArray = [];
            for (let i = this.startHour; i <= this.endHour; i++) {
                this.hourArray.push(i.toString().padStart(2, '0'));
            }
        }
        this.minuteArray = [];
        let startMinuteIndex = DatePickerConstant.MIN_MINUTE;
        let endMinuteIndex = DatePickerConstant.MAX_MINUTE;
        if (this.selectedHour === this.startHour) {
            startMinuteIndex = this.startMinute;
        }
        if (this.selectedHour === this.endHour) {
            endMinuteIndex = this.endMinute;
        }
        for (let i = startMinuteIndex; i <= endMinuteIndex; i++) {
            this.minuteArray.push(this.formatMinute(i));
        }
        if (this.selectedMinute < startMinuteIndex) {
            this.selectedMinute = startMinuteIndex;
        }
        if (this.selectedMinute > endMinuteIndex) {
            this.selectedMinute = endMinuteIndex;
        }
        this.secondArray = [];
        let startSecondIndex = DatePickerConstant.MIN_SECOND;
        let endSecondIndex = DatePickerConstant.MAX_SECOND;
        if (this.selectedHour === this.startHour && this.selectedMinute === this.startMinute) {
            startSecondIndex = this.startSecond;
        }
        if (this.selectedHour === this.endHour && this.selectedMinute === this.endMinute) {
            endSecondIndex = this.endSecond;
        }
        for (let i = startSecondIndex; i <= endSecondIndex; i++) {
            this.secondArray.push(this.formatSecond(i));
        }
        if (this.selectedSecond < startSecondIndex) {
            this.selectedSecond = startSecondIndex;
        }
        if (this.selectedSecond > endSecondIndex) {
            this.selectedSecond = endSecondIndex;
        }
    }
    updateHourArrayFor12Hour() {
        this.hourArray = [];
        const isAM = this.selectedPeriod === 0;
        // For 12-hour format, build hour array based on current period and time range
        // AM period: 12 (midnight 0:00) and 1-11 (1:00-11:00)
        // PM period: 12 (noon 12:00) and 1-11 (13:00-23:00)
        if (isAM) {
            // Check if 12 AM (hour24=0) is within range
            const hour24ForAm12 = 0;
            if (hour24ForAm12 >= this.startHour && hour24ForAm12 <= this.endHour) {
                this.hourArray.push('12');
            }
            // Check if 1-11 AM (hour24=1-11) are within range
            for (let displayHour = 1; displayHour <= 11; displayHour++) {
                const hour24 = displayHour;
                if (hour24 >= this.startHour && hour24 <= this.endHour) {
                    this.hourArray.push(displayHour.toString().padStart(2, '0'));
                }
            }
        }
        else {
            // Check if 12 PM (hour24=12) is within range
            const hour24ForPm12 = 12;
            if (hour24ForPm12 >= this.startHour && hour24ForPm12 <= this.endHour) {
                this.hourArray.push('12');
            }
            // Check if 1-11 PM (hour24=13-23) are within range
            for (let displayHour = 1; displayHour <= 11; displayHour++) {
                const hour24 = displayHour + 12;
                if (hour24 >= this.startHour && hour24 <= this.endHour) {
                    this.hourArray.push(displayHour.toString().padStart(2, '0'));
                }
            }
        }
        // Fallback: if no hours available for current period, show all 12 hours
        if (this.hourArray.length === 0) {
            for (let i = 1; i <= 12; i++) {
                this.hourArray.push(i.toString().padStart(2, '0'));
            }
        }
    }
    updatePeriodArray() {
        this.periodArray = [];
        // Check if AM period (hour24=0-11) has any available hours
        let canSelectAM = false;
        for (let hour = 0; hour <= 11; hour++) {
            if (hour >= this.startHour && hour <= this.endHour) {
                canSelectAM = true;
                break;
            }
        }
        // Check if PM period (hour24=12-23) has any available hours
        let canSelectPM = false;
        for (let hour = 12; hour <= 23; hour++) {
            if (hour >= this.startHour && hour <= this.endHour) {
                canSelectPM = true;
                break;
            }
        }
        if (canSelectAM && canSelectPM) {
            this.periodArray.push(this.formatPeriod(true));
            this.periodArray.push(this.formatPeriod(false));
        }
        else if (canSelectAM && !canSelectPM) {
            this.periodArray.push(this.formatPeriod(true));
            if (this.selectedPeriod === 1) {
                this.selectedPeriod = 0;
                // Adjust selectedHour to AM range when forced to switch to AM
                if (this.selectedHour >= 12) {
                    const minAMHour = Math.max(0, this.startHour);
                    const maxAMHour = Math.min(11, this.endHour);
                    if (this.selectedHour === 12) {
                        this.selectedHour = 0; // 12 PM -> 12 AM (0:00)
                    }
                    else {
                        this.selectedHour = Math.max(minAMHour, Math.min(maxAMHour, this.selectedHour - 12));
                    }
                }
            }
        }
        else if (!canSelectAM && canSelectPM) {
            this.periodArray.push(this.formatPeriod(false));
            if (this.selectedPeriod === 0) {
                this.selectedPeriod = 1;
                // Adjust selectedHour to PM range when forced to switch to PM
                if (this.selectedHour < 12) {
                    const minPMHour = Math.max(12, this.startHour);
                    const maxPMHour = Math.min(23, this.endHour);
                    // Calculate target hour (24-hour format): 12 AM->12, 1-11 AM->13-23
                    let targetHour24 = this.selectedHour === 0 ? 12 : this.selectedHour + 12;
                    // Ensure target hour is within valid range
                    this.selectedHour = Math.max(minPMHour, Math.min(maxPMHour, targetHour24));
                }
            }
        }
        else {
            // Fallback: show both periods if no hours available (shouldn't happen with valid ranges)
            this.periodArray.push(this.formatPeriod(true));
            this.periodArray.push(this.formatPeriod(false));
        }
    }
    isChineseLocale() {
        const localeStr = this.locale.toString();
        return localeStr.startsWith('zh') || localeStr.includes('zh-CN') || localeStr.includes('zh-TW') || localeStr.includes('zh-Hans') || localeStr.includes('zh-Hant');
    }
    formatYear(year) {
        if (this.isChineseLocale()) {
            return `${this.yearFormatter.format(year)}年`;
        }
        return this.yearFormatter.format(year);
    }
    formatMonth(month) {
        if (this.isChineseLocale()) {
            return `${month + 1}月`;
        }
        const monthNames = [
            'January', 'February', 'March', 'April', 'May', 'June',
            'July', 'August', 'September', 'October', 'November', 'December'
        ];
        const shortMonthNames = ['Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun',
            'Jul', 'Aug', 'Sep', 'Oct', 'Nov', 'Dec'];
        try {
            const localeStr = this.locale.toString();
            if (!localeStr || localeStr.length === 0) {
                return this.displayMode === DisplayMode.DATE_TIME ? shortMonthNames[month] : monthNames[month];
            }
            const monthFormat = this.displayMode === DisplayMode.DATE_TIME ? 'short' : 'long';
            const dateFormat = new Intl.DateTimeFormat(localeStr, {
                month: monthFormat
            });
            const safeMonth = Math.max(0, Math.min(11, month));
            const date = new Date(2026, safeMonth, 15);
            return dateFormat.format(date);
        }
        catch (error) {
            return this.displayMode === DisplayMode.DATE_TIME ? shortMonthNames[month] : monthNames[month];
        }
    }
    formatDay(day) {
        if (this.isChineseLocale()) {
            return `${this.formatter.format(day)}日`;
        }
        try {
            const localeStr = this.locale.toString();
            if (!localeStr || localeStr.length === 0) {
                return this.formatter.format(day);
            }
            const dateFormat = new Intl.DateTimeFormat(localeStr, {
                day: 'numeric'
            });
            const safeDay = Math.max(1, Math.min(31, day));
            const date = new Date(2026, 0, safeDay);
            return dateFormat.format(date);
        }
        catch (error) {
            return this.formatter.format(day);
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
    validateDate(date) {
        try {
            const year = date.getFullYear();
            const month = date.getMonth();
            const day = date.getDate();
            // Check for Invalid Date (NaN values)
            if (isNaN(year) || isNaN(month) || isNaN(day)) {
                return undefined;
            }
            // Check if year, month, day are in valid ranges
            if (year < DatePickerConstant.MIN_YEAR || year > DatePickerConstant.MAX_YEAR) {
                return undefined;
            }
            if (month < DatePickerConstant.MIN_MONTH || month > DatePickerConstant.MAX_MONTH) {
                return undefined;
            }
            if (day < DatePickerConstant.MIN_DAY || day > 31) {
                return undefined;
            }
            const daysInMonth = this.getDaysInMonth(year, month);
            if (day > daysInMonth) {
                return undefined;
            }
            // Detect JavaScript auto-correction by checking year jump
            // If year jumped significantly (> 1 year), it indicates abnormal input
            // Create expected Date without correction
            const originalTime = date.getTime();
            const correctedDate = new Date(year, month, day);
            const correctedTime = correctedDate.getTime();
            // If time difference > 365 days, indicates year jump due to abnormal month/day
            const timeDiff = Math.abs(originalTime - correctedTime);
            const oneYearInMs = 365 * 24 * 60 * 60 * 1000;
            if (timeDiff > oneYearInMs) {
                return undefined;
            }
            return correctedDate;
        }
        catch (e) {
            return undefined;
        }
    }
    validateTime(date) {
        try {
            const hour = date.getHours();
            const minute = date.getMinutes();
            const second = date.getSeconds();
            // Check for Invalid Date (NaN values)
            if (isNaN(hour) || isNaN(minute) || isNaN(second)) {
                return undefined;
            }
            if (hour < DatePickerConstant.MIN_HOUR || hour > DatePickerConstant.MAX_HOUR) {
                return undefined;
            }
            if (minute < DatePickerConstant.MIN_MINUTE || minute > DatePickerConstant.MAX_MINUTE) {
                return undefined;
            }
            if (second < DatePickerConstant.MIN_SECOND || second > DatePickerConstant.MAX_SECOND) {
                return undefined;
            }
            // Detect JavaScript auto-correction by checking time jump
            // Use original year/month/day to construct comparison time
            const year = date.getFullYear();
            const month = date.getMonth();
            const day = date.getDate();
            const originalTime = date.getTime();
            const correctedTime = new Date(year, month, day, hour, minute, second).getTime();
            // If time difference > 1 hour, indicates abnormal minute/second overflow
            const timeDiff = Math.abs(originalTime - correctedTime);
            const oneHourInMs = 60 * 60 * 1000;
            if (timeDiff > oneHourInMs) {
                return undefined;
            }
            // Return Date with fixed base date (2026-01-01) + validated time
            // This ensures timeOptions only considers time part, ignoring date part
            return new Date(2026, 0, 1, hour, minute, second);
        }
        catch (e) {
            return undefined;
        }
    }
    createDateFromParams(year, month, day) {
        return new Date(year, month, day);
    }
    onOptionsChange() {
        // Issue 4: Restore defaults for undefined/null values
        if (this.options.displayMode !== undefined && this.options.displayMode !== null) {
            this.displayMode = this.options.displayMode;
        }
        else {
            this.displayMode = DisplayMode.DATE;
        }
        if (this.options.dateOptions !== undefined && this.options.dateOptions !== null) {
            this.updateDateOptions(this.options.dateOptions);
        }
        else {
            // Restore defaults when dateOptions is undefined
            this.dateMode = DateMode.DATE;
            this.lunar = false;
            this.userLunar = false;
            this.lunarCalendar = null;
            this.dateCanLoop = true;
            this.dateHapticFeedback = true;
            this.startYear = DatePickerConstant.DEFAULT_START_YEAR;
            this.endYear = DatePickerConstant.DEFAULT_END_YEAR;
            this.startMonth = DatePickerConstant.MIN_MONTH;
            this.endMonth = DatePickerConstant.MAX_MONTH;
            this.startDay = DatePickerConstant.MIN_DAY;
            this.endDay = 31;
        }
        if (this.options.timeOptions !== undefined && this.options.timeOptions !== null) {
            this.updateTimeOptions(this.options.timeOptions);
        }
        else {
            // Restore defaults when timeOptions is undefined
            this.timeFormat = TimeFormat.HOUR_MINUTE;
            this.useMilitaryTime = false;
            this.timeCanLoop = true;
            this.timeHapticFeedback = true;
            this.startHour = DatePickerConstant.MIN_HOUR;
            this.endHour = DatePickerConstant.MAX_HOUR;
            this.startMinute = DatePickerConstant.MIN_MINUTE;
            this.endMinute = DatePickerConstant.MAX_MINUTE;
            this.startSecond = DatePickerConstant.MIN_SECOND;
            this.endSecond = DatePickerConstant.MAX_SECOND;
            this.selectedPeriod = this.selectedHour < 12 ? 0 : 1;
        }
        this.initArrays();
    }
    updateDateOptions(dateOptions) {
        // Issue 4: Restore defaults for undefined/null values
        if (dateOptions.mode !== undefined && dateOptions.mode !== null) {
            this.dateMode = dateOptions.mode;
        }
        else {
            this.dateMode = DateMode.DATE;
        }
        if (dateOptions.lunar !== undefined && dateOptions.lunar !== null) {
            // Issue 2: Save user-set value first, then decide based on current language
            this.userLunar = dateOptions.lunar;
            const isChinese = this.isChineseLocale();
            if (isChinese) {
                this.lunar = dateOptions.lunar;
                if (this.lunar) {
                    this.lunarCalendar = i18n.getCalendar(this.locale.toString(), 'chinese');
                }
                else {
                    this.lunarCalendar = null;
                }
            }
            else {
                // Non-Chinese language: force lunar to false, do not apply
                this.lunar = false;
                this.lunarCalendar = null;
            }
        }
        else {
            this.lunar = false;
            this.userLunar = false;
            this.lunarCalendar = null;
        }
        if (dateOptions.loop !== undefined && dateOptions.loop !== null) {
            this.dateCanLoop = dateOptions.loop;
        }
        else {
            this.dateCanLoop = true;
        }
        if (dateOptions.enableHapticFeedback !== undefined && dateOptions.enableHapticFeedback !== null) {
            this.dateHapticFeedback = dateOptions.enableHapticFeedback;
        }
        else {
            this.dateHapticFeedback = true;
        }
        let startValid = false;
        let endValid = false;
        let startDate = undefined;
        let endDate = undefined;
        if (dateOptions.start !== undefined) {
            startDate = this.validateDate(dateOptions.start);
            if (startDate !== undefined) {
                startValid = true;
            }
        }
        if (dateOptions.end !== undefined) {
            endDate = this.validateDate(dateOptions.end);
            if (endDate !== undefined) {
                endValid = true;
            }
        }
        if (startValid && endValid) {
            if (startDate > endDate) {
                this.startYear = DatePickerConstant.DEFAULT_START_YEAR;
                this.endYear = DatePickerConstant.DEFAULT_END_YEAR;
                this.startMonth = DatePickerConstant.MIN_MONTH;
                this.endMonth = DatePickerConstant.MAX_MONTH;
                this.startDay = DatePickerConstant.MIN_DAY;
                this.endDay = 31;
            }
            else {
                this.startYear = startDate.getFullYear();
                this.startMonth = startDate.getMonth();
                this.startDay = startDate.getDate();
                this.endYear = endDate.getFullYear();
                this.endMonth = endDate.getMonth();
                this.endDay = endDate.getDate();
            }
        }
        else if (startValid && !endValid) {
            this.startYear = startDate.getFullYear();
            this.startMonth = startDate.getMonth();
            this.startDay = startDate.getDate();
            if (this.startYear < DatePickerConstant.MIN_YEAR) {
                this.startYear = DatePickerConstant.DEFAULT_START_YEAR;
                this.startMonth = DatePickerConstant.MIN_MONTH;
                this.startDay = DatePickerConstant.MIN_DAY;
            }
            if (this.startYear > DatePickerConstant.MAX_YEAR) {
                this.startYear = DatePickerConstant.DEFAULT_END_YEAR;
                this.startMonth = DatePickerConstant.MAX_MONTH;
                this.startDay = 31;
            }
            this.endYear = DatePickerConstant.DEFAULT_END_YEAR;
            this.endMonth = DatePickerConstant.MAX_MONTH;
            this.endDay = 31;
        }
        else if (!startValid && endValid) {
            this.startYear = DatePickerConstant.DEFAULT_START_YEAR;
            this.startMonth = DatePickerConstant.MIN_MONTH;
            this.startDay = DatePickerConstant.MIN_DAY;
            this.endYear = endDate.getFullYear();
            this.endMonth = endDate.getMonth();
            this.endDay = endDate.getDate();
            if (this.endYear < DatePickerConstant.MIN_YEAR) {
                this.endYear = DatePickerConstant.DEFAULT_START_YEAR;
                this.endMonth = DatePickerConstant.MIN_MONTH;
                this.endDay = DatePickerConstant.MIN_DAY;
            }
            if (this.endYear > DatePickerConstant.MAX_YEAR) {
                this.endYear = DatePickerConstant.DEFAULT_END_YEAR;
                this.endMonth = DatePickerConstant.MAX_MONTH;
                this.endDay = 31;
            }
        }
        else {
            this.startYear = DatePickerConstant.DEFAULT_START_YEAR;
            this.endYear = DatePickerConstant.DEFAULT_END_YEAR;
            this.startMonth = DatePickerConstant.MIN_MONTH;
            this.endMonth = DatePickerConstant.MAX_MONTH;
            this.startDay = DatePickerConstant.MIN_DAY;
            this.endDay = 31;
        }
        if (this.startYear > this.endYear) {
            const tempYear = this.startYear;
            const tempMonth = this.startMonth;
            const tempDay = this.startDay;
            this.startYear = this.endYear;
            this.startMonth = this.endMonth;
            this.startDay = this.endDay;
            this.endYear = tempYear;
            this.endMonth = tempMonth;
            this.endDay = tempDay;
        }
        // If user explicitly sets valid start or end, force loop to false
        if (startValid || endValid) {
            this.dateCanLoop = false;
        }
        if (this.startYear < DatePickerConstant.MIN_YEAR) {
            this.startYear = DatePickerConstant.MIN_YEAR;
            this.startMonth = DatePickerConstant.MIN_MONTH;
            this.startDay = DatePickerConstant.MIN_DAY;
        }
        if (this.endYear > DatePickerConstant.MAX_YEAR) {
            this.endYear = DatePickerConstant.MAX_YEAR;
            this.endMonth = DatePickerConstant.MAX_MONTH;
            this.endDay = 31;
        }
        if (this.startYear > DatePickerConstant.MAX_YEAR && this.endYear > DatePickerConstant.MAX_YEAR) {
            this.startYear = DatePickerConstant.MAX_YEAR;
            this.startMonth = DatePickerConstant.MIN_MONTH;
            this.startDay = DatePickerConstant.MIN_DAY;
            this.endYear = DatePickerConstant.MAX_YEAR;
            this.endMonth = DatePickerConstant.MAX_MONTH;
            this.endDay = 31;
        }
        if (this.startYear < DatePickerConstant.MIN_YEAR && this.endYear < DatePickerConstant.MIN_YEAR) {
            this.startYear = DatePickerConstant.MIN_YEAR;
            this.startMonth = DatePickerConstant.MIN_MONTH;
            this.startDay = DatePickerConstant.MIN_DAY;
            this.endYear = DatePickerConstant.MIN_YEAR;
            this.endMonth = DatePickerConstant.MAX_MONTH;
            this.endDay = 31;
        }
        const now = new Date();
        let selectedDate = undefined;
        let selectedValid = false;
        if (dateOptions.selected !== undefined) {
            selectedDate = this.validateDate(dateOptions.selected);
            if (selectedDate !== undefined) {
                selectedValid = true;
            }
        }
        // Create Date objects for start and end
        const startDateObj = this.createDateFromParams(this.startYear, this.startMonth, this.startDay);
        const endDateObj = this.createDateFromParams(this.endYear, this.endMonth, this.endDay);
        // Determine the initial selected date
        let targetDate;
        if (selectedValid) {
            targetDate = selectedDate;
        }
        else {
            targetDate = now;
        }
        // Adjust selected date to be within range
        if (targetDate < startDateObj) {
            targetDate = startDateObj;
        }
        else if (targetDate > endDateObj) {
            targetDate = endDateObj;
        }
        // Extract year, month, day from adjusted date
        if (this.lunar && this.lunarCalendar !== null) {
            this.lunarCalendar.setTime(targetDate);
            const lunarMonth = this.lunarCalendar.get('month');
            const lunarDay = this.lunarCalendar.get('date');
            this.selectedYear = targetDate.getFullYear();
            this.selectedMonth = lunarMonth;
            this.selectedDay = lunarDay;
        }
        else {
            this.selectedYear = targetDate.getFullYear();
            this.selectedMonth = targetDate.getMonth();
            this.selectedDay = targetDate.getDate();
        }
        // Ensure day doesn't exceed days in month
        const daysInMonth = this.getDaysInMonth(this.selectedYear, this.selectedMonth);
        if (this.selectedDay > daysInMonth) {
            this.selectedDay = daysInMonth;
        }
        if (dateOptions.onChange !== undefined) {
            this.dateOnChange = dateOptions.onChange;
        }
        if (dateOptions.onScrollStop !== undefined) {
            this.dateOnScrollStop = dateOptions.onScrollStop;
        }
    }
    updateTimeOptions(timeOptions) {
        // Issue 4: Restore defaults for undefined/null values
        if (timeOptions.format !== undefined && timeOptions.format !== null) {
            this.timeFormat = timeOptions.format;
        }
        else {
            this.timeFormat = TimeFormat.HOUR_MINUTE;
        }
        if (timeOptions.useMilitaryTime !== undefined && timeOptions.useMilitaryTime !== null) {
            this.useMilitaryTime = timeOptions.useMilitaryTime;
        }
        else {
            this.useMilitaryTime = false;
        }
        if (timeOptions.loop !== undefined && timeOptions.loop !== null) {
            this.timeCanLoop = timeOptions.loop;
        }
        else {
            this.timeCanLoop = true;
        }
        if (timeOptions.enableHapticFeedback !== undefined && timeOptions.enableHapticFeedback !== null) {
            this.timeHapticFeedback = timeOptions.enableHapticFeedback;
        }
        else {
            this.timeHapticFeedback = true;
        }
        let startValid = false;
        let endValid = false;
        let startTime = undefined;
        let endTime = undefined;
        if (timeOptions.start !== undefined) {
            startTime = this.validateTime(timeOptions.start);
            if (startTime !== undefined) {
                startValid = true;
            }
        }
        if (timeOptions.end !== undefined) {
            endTime = this.validateTime(timeOptions.end);
            if (endTime !== undefined) {
                endValid = true;
            }
        }
        if (startValid && endValid) {
            if (startTime.getHours() > endTime.getHours() ||
                (startTime.getHours() === endTime.getHours() && startTime.getMinutes() > endTime.getMinutes()) ||
                (startTime.getHours() === endTime.getHours() && startTime.getMinutes() === endTime.getMinutes() && startTime.getSeconds() > endTime.getSeconds())) {
                this.startHour = DatePickerConstant.MIN_HOUR;
                this.endHour = DatePickerConstant.MAX_HOUR;
                this.startMinute = DatePickerConstant.MIN_MINUTE;
                this.endMinute = DatePickerConstant.MAX_MINUTE;
                this.startSecond = DatePickerConstant.MIN_SECOND;
                this.endSecond = DatePickerConstant.MAX_SECOND;
            }
            else {
                this.startHour = startTime.getHours();
                this.startMinute = startTime.getMinutes();
                this.startSecond = startTime.getSeconds();
                this.endHour = endTime.getHours();
                this.endMinute = endTime.getMinutes();
                this.endSecond = endTime.getSeconds();
            }
        }
        else if (startValid && !endValid) {
            this.startHour = startTime.getHours();
            this.startMinute = startTime.getMinutes();
            this.startSecond = startTime.getSeconds();
            this.endHour = DatePickerConstant.MAX_HOUR;
            this.endMinute = DatePickerConstant.MAX_MINUTE;
            this.endSecond = DatePickerConstant.MAX_SECOND;
        }
        else if (!startValid && endValid) {
            this.startHour = DatePickerConstant.MIN_HOUR;
            this.startMinute = DatePickerConstant.MIN_MINUTE;
            this.startSecond = DatePickerConstant.MIN_SECOND;
            this.endHour = endTime.getHours();
            this.endMinute = endTime.getMinutes();
            this.endSecond = endTime.getSeconds();
        }
        else {
            this.startHour = DatePickerConstant.MIN_HOUR;
            this.endHour = DatePickerConstant.MAX_HOUR;
            this.startMinute = DatePickerConstant.MIN_MINUTE;
            this.endMinute = DatePickerConstant.MAX_MINUTE;
            this.startSecond = DatePickerConstant.MIN_SECOND;
            this.endSecond = DatePickerConstant.MAX_SECOND;
        }
        this.startHour = Math.max(DatePickerConstant.MIN_HOUR, Math.min(DatePickerConstant.MAX_HOUR, this.startHour));
        this.endHour = Math.max(DatePickerConstant.MIN_HOUR, Math.min(DatePickerConstant.MAX_HOUR, this.endHour));
        this.startMinute = Math.max(DatePickerConstant.MIN_MINUTE, Math.min(DatePickerConstant.MAX_MINUTE, this.startMinute));
        this.endMinute = Math.max(DatePickerConstant.MIN_MINUTE, Math.min(DatePickerConstant.MAX_MINUTE, this.endMinute));
        this.startSecond = Math.max(DatePickerConstant.MIN_SECOND, Math.min(DatePickerConstant.MAX_SECOND, this.startSecond));
        this.endSecond = Math.max(DatePickerConstant.MIN_SECOND, Math.min(DatePickerConstant.MAX_SECOND, this.endSecond));
        // If user explicitly sets valid start or end, force loop to false
        if (startValid || endValid) {
            this.timeCanLoop = false;
        }
        const now = new Date();
        let selectedTime = undefined;
        let selectedValid = false;
        if (timeOptions.selected !== undefined) {
            selectedTime = this.validateTime(timeOptions.selected);
            if (selectedTime !== undefined) {
                selectedValid = true;
            }
        }
        // Determine the initial selected time
        let targetTime;
        if (selectedValid) {
            targetTime = selectedTime;
        }
        else {
            targetTime = now;
        }
        // Create Date objects for start and end time on same day
        const startTimeObj = new Date(2026, 0, 1, this.startHour, this.startMinute, this.startSecond);
        const endTimeObj = new Date(2026, 0, 1, this.endHour, this.endMinute, this.endSecond);
        const targetTimeObj = new Date(2026, 0, 1, targetTime.getHours(), targetTime.getMinutes(), targetTime.getSeconds());
        // Adjust selected time to be within range
        if (targetTimeObj < startTimeObj) {
            targetTimeObj.setTime(startTimeObj.getTime());
        }
        else if (targetTimeObj > endTimeObj) {
            targetTimeObj.setTime(endTimeObj.getTime());
        }
        // Extract hour, minute, second from adjusted time
        this.selectedHour = targetTimeObj.getHours();
        this.selectedMinute = targetTimeObj.getMinutes();
        this.selectedSecond = targetTimeObj.getSeconds();
        // Set selectedPeriod based on selectedHour for 12-hour format
        if (!this.useMilitaryTime) {
            this.selectedPeriod = this.selectedHour < 12 ? 0 : 1;
        }
        if (timeOptions.onChange !== undefined) {
            this.timeOnChange = timeOptions.onChange;
        }
        if (timeOptions.onScrollStop !== undefined) {
            this.timeOnScrollStop = timeOptions.onScrollStop;
        }
    }
    getResult() {
        const result = new DatePickerComponentResult();
        result.year = this.selectedYear;
        result.month = this.selectedMonth;
        result.day = this.selectedDay;
        // Always return 24-hour format (selectedHour is always 0-23)
        result.hour = this.selectedHour;
        result.minute = this.selectedMinute;
        result.second = this.selectedSecond;
        return result;
    }
    onYearChange(selectedIndex) {
        this.selectedYear = this.startYear + selectedIndex;
        // Update month array based on new year
        this.initMonthArray();
        // Adjust selectedMonth to be within new month range
        let startMonthIndex = DatePickerConstant.MIN_MONTH;
        let endMonthIndex = DatePickerConstant.MAX_MONTH;
        if (this.selectedYear === this.startYear) {
            startMonthIndex = this.startMonth;
        }
        if (this.selectedYear === this.endYear) {
            endMonthIndex = this.endMonth;
        }
        if (this.selectedMonth < startMonthIndex) {
            this.selectedMonth = startMonthIndex;
        }
        if (this.selectedMonth > endMonthIndex) {
            this.selectedMonth = endMonthIndex;
        }
        // Update day array based on new year and adjusted month
        this.updateDaysArray();
        this.dateOnChange?.(this.getResult());
    }
    onMonthChange(selectedIndex) {
        let startMonthIndex = DatePickerConstant.MIN_MONTH;
        if (this.selectedYear === this.startYear) {
            startMonthIndex = this.startMonth;
        }
        this.selectedMonth = startMonthIndex + selectedIndex;
        this.updateDaysArray();
        this.dateOnChange?.(this.getResult());
    }
    onDayChange(selectedIndex) {
        let startDayIndex = DatePickerConstant.MIN_DAY;
        if (this.selectedYear === this.startYear && this.selectedMonth === this.startMonth) {
            startDayIndex = this.startDay;
        }
        this.selectedDay = startDayIndex + selectedIndex;
        this.dateOnChange?.(this.getResult());
    }
    onHourChange(selectedIndex) {
        if (this.useMilitaryTime) {
            this.selectedHour = this.startHour + selectedIndex;
        }
        else {
            const oldDisplayHour = this.selectedHour === 0 || this.selectedHour === 12 ? 12 :
                (this.selectedHour > 12 ? this.selectedHour - 12 : this.selectedHour);
            // Get the actual display hour from hourArray
            const newDisplayHour = parseInt(this.hourArray[selectedIndex]);
            // Crossing 11↔12 always triggers period toggle
            const crossingBoundary = (oldDisplayHour === 11 && newDisplayHour === 12) ||
                (oldDisplayHour === 12 && newDisplayHour === 11);
            if (crossingBoundary) {
                // Toggle period
                this.selectedPeriod = this.selectedPeriod === 0 ? 1 : 0;
            }
            // Convert display hour to 24-hour format based on CURRENT period (after toggle)
            if (newDisplayHour === 12) {
                if (this.selectedPeriod === 0) {
                    this.selectedHour = 0; // 12 AM = 0:00 (24-hour)
                }
                else {
                    this.selectedHour = 12; // 12 PM = 12:00 (24-hour)
                }
            }
            else {
                if (this.selectedPeriod === 0) {
                    this.selectedHour = newDisplayHour; // 1-11 AM
                }
                else {
                    this.selectedHour = newDisplayHour + 12; // 1-11 PM = 13-23
                }
            }
        }
        this.updateTimeArrays();
        this.timeOnChange?.(this.getResult());
    }
    onPeriodChange(selectedIndex) {
        // Determine selectedPeriod based on periodArray content, not directly using selectedIndex
        // This ensures correct mapping even if periodArray has only one option
        const selectedPeriodStr = this.periodArray[selectedIndex];
        this.selectedPeriod = selectedPeriodStr === this.formatPeriod(true) ? 0 : 1;
        if (!this.useMilitaryTime) {
            // Update hourArray
            this.updateHourArrayFor12Hour();
            // Adjust selectedHour based on new period
            const isAM = this.selectedPeriod === 0;
            if (isAM) {
                // Switch to AM period
                const minHour = Math.max(0, this.startHour);
                const maxHour = Math.min(11, this.endHour < 12 ? this.endHour : 11);
                // If current hour is not in AM range, adjust to within range
                if (this.selectedHour >= 12 || this.selectedHour < minHour) {
                    this.selectedHour = minHour;
                }
                if (this.selectedHour > maxHour) {
                    this.selectedHour = maxHour;
                }
            }
            else {
                // Switch to PM period
                const minHour = Math.max(12, this.startHour >= 12 ? this.startHour : 12);
                const maxHour = Math.min(23, this.endHour);
                // If current hour is not in PM range, adjust to within range
                if (this.selectedHour < 12 || this.selectedHour < minHour) {
                    this.selectedHour = minHour;
                }
                if (this.selectedHour > maxHour) {
                    this.selectedHour = maxHour;
                }
            }
            // Update minute and second arrays
            this.updateTimeArrays();
        }
        this.timeOnChange?.(this.getResult());
    }
    onMinuteChange(selectedIndex) {
        let startMinuteIndex = DatePickerConstant.MIN_MINUTE;
        if (this.selectedHour === this.startHour) {
            startMinuteIndex = this.startMinute;
        }
        this.selectedMinute = startMinuteIndex + selectedIndex;
        this.updateSecondArray();
        this.timeOnChange?.(this.getResult());
    }
    onSecondChange(selectedIndex) {
        let startSecondIndex = DatePickerConstant.MIN_SECOND;
        if (this.selectedHour === this.startHour && this.selectedMinute === this.startMinute) {
            startSecondIndex = this.startSecond;
        }
        this.selectedSecond = startSecondIndex + selectedIndex;
        this.timeOnChange?.(this.getResult());
    }
    updateTimeArrays() {
        this.minuteArray = [];
        let startMinuteIndex = DatePickerConstant.MIN_MINUTE;
        let endMinuteIndex = DatePickerConstant.MAX_MINUTE;
        if (this.selectedHour === this.startHour) {
            startMinuteIndex = this.startMinute;
        }
        if (this.selectedHour === this.endHour) {
            endMinuteIndex = this.endMinute;
        }
        for (let i = startMinuteIndex; i <= endMinuteIndex; i++) {
            this.minuteArray.push(this.formatMinute(i));
        }
        if (this.selectedMinute < startMinuteIndex) {
            this.selectedMinute = startMinuteIndex;
        }
        if (this.selectedMinute > endMinuteIndex) {
            this.selectedMinute = endMinuteIndex;
        }
        this.updateSecondArray();
    }
    updateSecondArray() {
        this.secondArray = [];
        let startSecondIndex = DatePickerConstant.MIN_SECOND;
        let endSecondIndex = DatePickerConstant.MAX_SECOND;
        if (this.selectedHour === this.startHour && this.selectedMinute === this.startMinute) {
            startSecondIndex = this.startSecond;
        }
        if (this.selectedHour === this.endHour && this.selectedMinute === this.endMinute) {
            endSecondIndex = this.endSecond;
        }
        for (let i = startSecondIndex; i <= endSecondIndex; i++) {
            this.secondArray.push(this.formatSecond(i));
        }
        if (this.selectedSecond < startSecondIndex) {
            this.selectedSecond = startSecondIndex;
        }
        if (this.selectedSecond > endSecondIndex) {
            this.selectedSecond = endSecondIndex;
        }
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
            // Determine the valid day range based on selected year and month
            let startDayIndex = DatePickerConstant.MIN_DAY;
            let endDayIndex = daysInMonth;
            if (this.selectedYear === this.startYear && this.selectedMonth === this.startMonth) {
                startDayIndex = this.startDay;
            }
            if (this.selectedYear === this.endYear && this.selectedMonth === this.endMonth) {
                endDayIndex = Math.min(this.endDay, daysInMonth);
            }
            // Adjust selectedDay to be within valid range
            if (this.selectedDay < startDayIndex) {
                this.selectedDay = startDayIndex;
            }
            if (this.selectedDay > endDayIndex) {
                this.selectedDay = endDayIndex;
            }
            this.initDayArray();
        }
    }
    getYearSelectedIndex() {
        return this.selectedYear - this.startYear;
    }
    getMonthSelectedIndex() {
        let startMonthIndex = DatePickerConstant.MIN_MONTH;
        if (this.selectedYear === this.startYear) {
            startMonthIndex = this.startMonth;
        }
        return this.selectedMonth - startMonthIndex;
    }
    getDaySelectedIndex() {
        let startDayIndex = DatePickerConstant.MIN_DAY;
        if (this.selectedYear === this.startYear && this.selectedMonth === this.startMonth) {
            startDayIndex = this.startDay;
        }
        return this.selectedDay - startDayIndex;
    }
    getHourSelectedIndex() {
        if (this.useMilitaryTime) {
            return this.selectedHour - this.startHour;
        }
        else {
            // Convert selectedHour to display hour (1-12)
            const displayHour = this.selectedHour === 0 || this.selectedHour === 12 ? 12 :
                (this.selectedHour > 12 ? this.selectedHour - 12 : this.selectedHour);
            // Find the index of displayHour in hourArray
            const displayHourStr = displayHour.toString().padStart(2, '0');
            const index = this.hourArray.indexOf(displayHourStr);
            // Fallback to first element if not found (shouldn't happen with correct logic)
            return index >= 0 ? index : 0;
        }
    }
    getMinuteSelectedIndex() {
        let startMinuteIndex = DatePickerConstant.MIN_MINUTE;
        if (this.selectedHour === this.startHour) {
            startMinuteIndex = this.startMinute;
        }
        return this.selectedMinute - startMinuteIndex;
    }
    getSecondSelectedIndex() {
        let startSecondIndex = DatePickerConstant.MIN_SECOND;
        if (this.selectedHour === this.startHour && this.selectedMinute === this.startMinute) {
            startSecondIndex = this.startSecond;
        }
        return this.selectedSecond - startSecondIndex;
    }
    isRTL() {
        return i18n.isRTL(this.locale.toString()) ?? false;
    }
    getDateColumnCount() {
        if (this.dateMode === DateMode.DATE) {
            return 3;
        }
        else {
            return 2;
        }
    }
    getTimeColumnCount() {
        if (this.timeFormat === TimeFormat.HOUR_MINUTE) {
            return this.useMilitaryTime ? 2 : 3;
        }
        else {
            return this.useMilitaryTime ? 3 : 4;
        }
    }
    getColumnCount() {
        let columnCount = 0;
        if (this.displayMode === DisplayMode.DATE) {
            columnCount = this.getDateColumnCount();
        }
        else if (this.displayMode === DisplayMode.TIME) {
            columnCount = this.getTimeColumnCount();
        }
        else {
            columnCount = this.getDateColumnCount() + this.getTimeColumnCount();
        }
        return columnCount;
    }
    getFontSize() {
        const columnCount = this.getColumnCount();
        return columnCount >= 6 ? '14vp' : '16vp';
    }
    getDatePartRatio() {
        const timeColumns = this.getTimeColumnCount();
        const dateColumns = this.getDateColumnCount();
        if (timeColumns === 4) {
            if (dateColumns === 3) {
                return 1;
            }
            else {
                return 2;
            }
        }
        else if (timeColumns === 2) {
            if (dateColumns === 3) {
                return 3;
            }
            else {
                return 1;
            }
        }
        else {
            return 1;
        }
    }
    getTimePartRatio() {
        const timeColumns = this.getTimeColumnCount();
        const dateColumns = this.getDateColumnCount();
        if (timeColumns === 4) {
            if (dateColumns === 3) {
                return 1;
            }
            else {
                return 3;
            }
        }
        else if (timeColumns === 2) {
            if (dateColumns === 3) {
                return 2;
            }
            else {
                return 1;
            }
        }
        else {
            return 1;
        }
    }
    getDateColumnWidth(columnIndex) {
        const inDateTimeMode = this.displayMode === DisplayMode.DATE_TIME;
        let parts = [];
        if (this.dateMode === DateMode.DATE) {
            parts = [3, 2, 2];
        }
        else if (this.dateMode === DateMode.YEAR_AND_MONTH) {
            parts = [3, 2];
        }
        else {
            parts = [1, 1];
        }
        const totalParts = parts.reduce((a, b) => a + b, 0);
        const columnPart = parts[columnIndex];
        if (inDateTimeMode) {
            const dateRatio = this.getDatePartRatio();
            const timeRatio = this.getTimePartRatio();
            const totalRatio = dateRatio + timeRatio;
            const percent = (dateRatio / totalRatio) * (columnPart / totalParts) * 100;
            return `${percent.toFixed(2)}%`;
        }
        else {
            const percent = (columnPart / totalParts) * 100;
            return `${percent.toFixed(2)}%`;
        }
    }
    getTimeColumnWidth(columnIndex) {
        const inDateTimeMode = this.displayMode === DisplayMode.DATE_TIME;
        const totalColumns = this.getTimeColumnCount();
        if (inDateTimeMode) {
            const dateRatio = this.getDatePartRatio();
            const timeRatio = this.getTimePartRatio();
            const totalRatio = dateRatio + timeRatio;
            const percent = (timeRatio / totalRatio) * (1 / totalColumns) * 100;
            return `${percent.toFixed(2)}%`;
        }
        else {
            const percent = (1 / totalColumns) * 100;
            return `${percent.toFixed(2)}%`;
        }
    }
    getFirstPickerIndicator(radius = 20) {
        if (this.isRTL()) {
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
        if (this.isRTL()) {
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
    getAdjustedRadius() {
        const minColumnWidth = Math.min(this.firstColumnWidth, this.lastColumnWidth);
        if (minColumnWidth <= 0) {
            return 20;
        }
        const calculatedRadius = Math.min(minColumnWidth / 2, 20);
        return Math.max(calculatedRadius, 0);
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
                                    UIPickerComponent.width(this.getDateColumnWidth(0));
                                    UIPickerComponent.height(200);
                                    UIPickerComponent.canLoop(this.dateCanLoop);
                                    UIPickerComponent.enableHapticFeedback(this.dateHapticFeedback);
                                    UIPickerComponent.selectionIndicator(this.getFirstPickerIndicator(this.getAdjustedRadius()));
                                    UIPickerComponent.onChange((selectedIndex) => {
                                        this.onYearChange(selectedIndex);
                                    });
                                    UIPickerComponent.onScrollStop((selectedIndex) => {
                                        this.selectedYear = this.startYear + selectedIndex;
                                        this.updateDaysArray();
                                        this.dateOnScrollStop?.(this.getResult());
                                    });
                                    UIPickerComponent.onAreaChange((oldValue, newValue) => {
                                        const newWidth = newValue.width;
                                        if (this.firstColumnWidth !== newWidth) {
                                            this.firstColumnWidth = newWidth;
                                        }
                                    });
                                }, UIPickerComponent);
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    ForEach.create();
                                    const forEachItemGenFunction = _item => {
                                        const item = _item;
                                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                                            Text.create(item);
                                            Text.maxLines(1);
                                            Text.fontSize(this.getFontSize());
                                            Text.textOverflow({ overflow: TextOverflow.Clip });
                                        }, Text);
                                        Text.pop();
                                    };
                                    this.forEachUpdateFunction(elmtId, this.yearArray, forEachItemGenFunction);
                                }, ForEach);
                                ForEach.pop();
                                UIPickerComponent.pop();
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    UIPickerComponent.create({ selectedIndex: this.getMonthSelectedIndex() });
                                    UIPickerComponent.width(this.getDateColumnWidth(1));
                                    UIPickerComponent.height(200);
                                    UIPickerComponent.canLoop(this.dateCanLoop);
                                    UIPickerComponent.enableHapticFeedback(this.dateHapticFeedback);
                                    UIPickerComponent.selectionIndicator(this.getMiddlePickerIndicator());
                                    UIPickerComponent.onChange((selectedIndex) => {
                                        this.onMonthChange(selectedIndex);
                                    });
                                    UIPickerComponent.onScrollStop((selectedIndex) => {
                                        let startMonthIndex = DatePickerConstant.MIN_MONTH;
                                        if (this.selectedYear === this.startYear) {
                                            startMonthIndex = this.startMonth;
                                        }
                                        this.selectedMonth = startMonthIndex + selectedIndex;
                                        this.dateOnScrollStop?.(this.getResult());
                                    });
                                }, UIPickerComponent);
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    ForEach.create();
                                    const forEachItemGenFunction = _item => {
                                        const item = _item;
                                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                                            Text.create(item);
                                            Text.maxLines(1);
                                            Text.fontSize(this.getFontSize());
                                            Text.textOverflow({ overflow: TextOverflow.Clip });
                                        }, Text);
                                        Text.pop();
                                    };
                                    this.forEachUpdateFunction(elmtId, this.monthArray, forEachItemGenFunction);
                                }, ForEach);
                                ForEach.pop();
                                UIPickerComponent.pop();
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    UIPickerComponent.create({ selectedIndex: this.getDaySelectedIndex() });
                                    UIPickerComponent.width(this.getDateColumnWidth(2));
                                    UIPickerComponent.height(200);
                                    UIPickerComponent.canLoop(this.dateCanLoop);
                                    UIPickerComponent.enableHapticFeedback(this.dateHapticFeedback);
                                    UIPickerComponent.selectionIndicator(this.displayMode === DisplayMode.DATE_TIME ? this.getMiddlePickerIndicator() : this.getLastPickerIndicator(this.getAdjustedRadius()));
                                    UIPickerComponent.onChange((selectedIndex) => {
                                        this.onDayChange(selectedIndex);
                                    });
                                    UIPickerComponent.onScrollStop((selectedIndex) => {
                                        let startDayIndex = DatePickerConstant.MIN_DAY;
                                        if (this.selectedYear === this.startYear && this.selectedMonth === this.startMonth) {
                                            startDayIndex = this.startDay;
                                        }
                                        this.selectedDay = startDayIndex + selectedIndex;
                                        this.dateOnScrollStop?.(this.getResult());
                                    });
                                    UIPickerComponent.onAreaChange((oldValue, newValue) => {
                                        if (this.displayMode !== DisplayMode.DATE_TIME) {
                                            const newWidth = newValue.width;
                                            if (this.lastColumnWidth !== newWidth) {
                                                this.lastColumnWidth = newWidth;
                                            }
                                        }
                                    });
                                }, UIPickerComponent);
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    ForEach.create();
                                    const forEachItemGenFunction = _item => {
                                        const item = _item;
                                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                                            Text.create(item);
                                            Text.maxLines(1);
                                            Text.fontSize(this.getFontSize());
                                            Text.textOverflow({ overflow: TextOverflow.Clip });
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
                                    UIPickerComponent.width(this.getDateColumnWidth(0));
                                    UIPickerComponent.height(200);
                                    UIPickerComponent.canLoop(this.dateCanLoop);
                                    UIPickerComponent.enableHapticFeedback(this.dateHapticFeedback);
                                    UIPickerComponent.selectionIndicator(this.getFirstPickerIndicator(this.getAdjustedRadius()));
                                    UIPickerComponent.onChange((selectedIndex) => {
                                        this.onYearChange(selectedIndex);
                                    });
                                    UIPickerComponent.onScrollStop((selectedIndex) => {
                                        this.selectedYear = this.startYear + selectedIndex;
                                        this.updateDaysArray();
                                        this.dateOnScrollStop?.(this.getResult());
                                    });
                                    UIPickerComponent.onAreaChange((oldValue, newValue) => {
                                        const newWidth = newValue.width;
                                        if (this.firstColumnWidth !== newWidth) {
                                            this.firstColumnWidth = newWidth;
                                        }
                                    });
                                }, UIPickerComponent);
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    ForEach.create();
                                    const forEachItemGenFunction = _item => {
                                        const item = _item;
                                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                                            Text.create(item);
                                            Text.maxLines(1);
                                            Text.fontSize(this.getFontSize());
                                            Text.textOverflow({ overflow: TextOverflow.Clip });
                                        }, Text);
                                        Text.pop();
                                    };
                                    this.forEachUpdateFunction(elmtId, this.yearArray, forEachItemGenFunction);
                                }, ForEach);
                                ForEach.pop();
                                UIPickerComponent.pop();
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    UIPickerComponent.create({ selectedIndex: this.getMonthSelectedIndex() });
                                    UIPickerComponent.width(this.getDateColumnWidth(1));
                                    UIPickerComponent.height(200);
                                    UIPickerComponent.canLoop(this.dateCanLoop);
                                    UIPickerComponent.enableHapticFeedback(this.dateHapticFeedback);
                                    UIPickerComponent.selectionIndicator(this.displayMode === DisplayMode.DATE_TIME ? this.getMiddlePickerIndicator() : this.getLastPickerIndicator(this.getAdjustedRadius()));
                                    UIPickerComponent.onChange((selectedIndex) => {
                                        this.onMonthChange(selectedIndex);
                                    });
                                    UIPickerComponent.onScrollStop((selectedIndex) => {
                                        let startMonthIndex = DatePickerConstant.MIN_MONTH;
                                        if (this.selectedYear === this.startYear) {
                                            startMonthIndex = this.startMonth;
                                        }
                                        this.selectedMonth = startMonthIndex + selectedIndex;
                                        this.dateOnScrollStop?.(this.getResult());
                                    });
                                    UIPickerComponent.onAreaChange((oldValue, newValue) => {
                                        if (this.displayMode !== DisplayMode.DATE_TIME) {
                                            const newWidth = newValue.width;
                                            if (this.lastColumnWidth !== newWidth) {
                                                this.lastColumnWidth = newWidth;
                                            }
                                        }
                                    });
                                }, UIPickerComponent);
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    ForEach.create();
                                    const forEachItemGenFunction = _item => {
                                        const item = _item;
                                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                                            Text.create(item);
                                            Text.maxLines(1);
                                            Text.fontSize(this.getFontSize());
                                            Text.textOverflow({ overflow: TextOverflow.Clip });
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
                                    UIPickerComponent.width(this.getDateColumnWidth(0));
                                    UIPickerComponent.height(200);
                                    UIPickerComponent.canLoop(this.dateCanLoop);
                                    UIPickerComponent.enableHapticFeedback(this.dateHapticFeedback);
                                    UIPickerComponent.selectionIndicator(this.getFirstPickerIndicator(this.getAdjustedRadius()));
                                    UIPickerComponent.onChange((selectedIndex) => {
                                        this.onMonthChange(selectedIndex);
                                    });
                                    UIPickerComponent.onScrollStop((selectedIndex) => {
                                        let startMonthIndex = DatePickerConstant.MIN_MONTH;
                                        if (this.selectedYear === this.startYear) {
                                            startMonthIndex = this.startMonth;
                                        }
                                        this.selectedMonth = startMonthIndex + selectedIndex;
                                        this.dateOnScrollStop?.(this.getResult());
                                    });
                                    UIPickerComponent.onAreaChange((oldValue, newValue) => {
                                        const newWidth = newValue.width;
                                        if (this.firstColumnWidth !== newWidth) {
                                            this.firstColumnWidth = newWidth;
                                        }
                                    });
                                }, UIPickerComponent);
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    ForEach.create();
                                    const forEachItemGenFunction = _item => {
                                        const item = _item;
                                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                                            Text.create(item);
                                            Text.maxLines(1);
                                            Text.fontSize(this.getFontSize());
                                            Text.textOverflow({ overflow: TextOverflow.Clip });
                                        }, Text);
                                        Text.pop();
                                    };
                                    this.forEachUpdateFunction(elmtId, this.monthArray, forEachItemGenFunction);
                                }, ForEach);
                                ForEach.pop();
                                UIPickerComponent.pop();
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    UIPickerComponent.create({ selectedIndex: this.getDaySelectedIndex() });
                                    UIPickerComponent.width(this.getDateColumnWidth(1));
                                    UIPickerComponent.height(200);
                                    UIPickerComponent.canLoop(this.dateCanLoop);
                                    UIPickerComponent.enableHapticFeedback(this.dateHapticFeedback);
                                    UIPickerComponent.selectionIndicator(this.displayMode === DisplayMode.DATE_TIME ? this.getMiddlePickerIndicator() : this.getLastPickerIndicator(this.getAdjustedRadius()));
                                    UIPickerComponent.onChange((selectedIndex) => {
                                        this.onDayChange(selectedIndex);
                                    });
                                    UIPickerComponent.onScrollStop((selectedIndex) => {
                                        let startDayIndex = DatePickerConstant.MIN_DAY;
                                        if (this.selectedYear === this.startYear && this.selectedMonth === this.startMonth) {
                                            startDayIndex = this.startDay;
                                        }
                                        this.selectedDay = startDayIndex + selectedIndex;
                                        this.dateOnScrollStop?.(this.getResult());
                                    });
                                    UIPickerComponent.onAreaChange((oldValue, newValue) => {
                                        if (this.displayMode !== DisplayMode.DATE_TIME) {
                                            const newWidth = newValue.width;
                                            if (this.lastColumnWidth !== newWidth) {
                                                this.lastColumnWidth = newWidth;
                                            }
                                        }
                                    });
                                }, UIPickerComponent);
                                this.observeComponentCreation2((elmtId, isInitialRender) => {
                                    ForEach.create();
                                    const forEachItemGenFunction = _item => {
                                        const item = _item;
                                        this.observeComponentCreation2((elmtId, isInitialRender) => {
                                            Text.create(item);
                                            Text.maxLines(1);
                                            Text.fontSize(this.getFontSize());
                                            Text.textOverflow({ overflow: TextOverflow.Clip });
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
                                                UIPickerComponent.width(this.getTimeColumnWidth(0));
                                                UIPickerComponent.height(200);
                                                UIPickerComponent.canLoop(this.timeCanLoop);
                                                UIPickerComponent.enableHapticFeedback(this.timeHapticFeedback);
                                                UIPickerComponent.selectionIndicator(this.displayMode === DisplayMode.DATE_TIME ? this.getMiddlePickerIndicator() : this.getFirstPickerIndicator(this.getAdjustedRadius()));
                                                UIPickerComponent.onChange((selectedIndex) => {
                                                    this.onHourChange(selectedIndex);
                                                });
                                                UIPickerComponent.onScrollStop((selectedIndex) => {
                                                    this.selectedHour = this.startHour + selectedIndex;
                                                    this.updateTimeArrays();
                                                    this.timeOnScrollStop?.(this.getResult());
                                                });
                                                UIPickerComponent.onAreaChange((oldValue, newValue) => {
                                                    if (this.displayMode === DisplayMode.TIME) {
                                                        const newWidth = newValue.width;
                                                        if (this.firstColumnWidth !== newWidth) {
                                                            this.firstColumnWidth = newWidth;
                                                        }
                                                    }
                                                });
                                            }, UIPickerComponent);
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                ForEach.create();
                                                const forEachItemGenFunction = _item => {
                                                    const item = _item;
                                                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                        Text.create(item);
                                                        Text.maxLines(1);
                                                        Text.fontSize(this.getFontSize());
                                                        Text.textOverflow({ overflow: TextOverflow.Clip });
                                                    }, Text);
                                                    Text.pop();
                                                };
                                                this.forEachUpdateFunction(elmtId, this.hourArray, forEachItemGenFunction);
                                            }, ForEach);
                                            ForEach.pop();
                                            UIPickerComponent.pop();
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                UIPickerComponent.create({ selectedIndex: this.getMinuteSelectedIndex() });
                                                UIPickerComponent.width(this.getTimeColumnWidth(1));
                                                UIPickerComponent.height(200);
                                                UIPickerComponent.canLoop(this.timeCanLoop);
                                                UIPickerComponent.enableHapticFeedback(this.timeHapticFeedback);
                                                UIPickerComponent.selectionIndicator(this.getLastPickerIndicator(this.getAdjustedRadius()));
                                                UIPickerComponent.onChange((selectedIndex) => {
                                                    this.onMinuteChange(selectedIndex);
                                                });
                                                UIPickerComponent.onScrollStop((selectedIndex) => {
                                                    let startMinuteIndex = DatePickerConstant.MIN_MINUTE;
                                                    if (this.selectedHour === this.startHour) {
                                                        startMinuteIndex = this.startMinute;
                                                    }
                                                    this.selectedMinute = startMinuteIndex + selectedIndex;
                                                    this.updateSecondArray();
                                                    this.timeOnScrollStop?.(this.getResult());
                                                });
                                                UIPickerComponent.onAreaChange((oldValue, newValue) => {
                                                    const newWidth = newValue.width;
                                                    if (this.lastColumnWidth !== newWidth) {
                                                        this.lastColumnWidth = newWidth;
                                                    }
                                                });
                                            }, UIPickerComponent);
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                ForEach.create();
                                                const forEachItemGenFunction = _item => {
                                                    const item = _item;
                                                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                        Text.create(item);
                                                        Text.maxLines(1);
                                                        Text.fontSize(this.getFontSize());
                                                        Text.textOverflow({ overflow: TextOverflow.Clip });
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
                                                UIPickerComponent.create({ selectedIndex: this.selectedPeriod });
                                                UIPickerComponent.width(this.getTimeColumnWidth(0));
                                                UIPickerComponent.height(200);
                                                UIPickerComponent.canLoop(false);
                                                UIPickerComponent.enableHapticFeedback(this.timeHapticFeedback);
                                                UIPickerComponent.selectionIndicator(this.displayMode === DisplayMode.DATE_TIME ? this.getMiddlePickerIndicator() : this.getFirstPickerIndicator(this.getAdjustedRadius()));
                                                UIPickerComponent.onChange((selectedIndex) => {
                                                    this.onPeriodChange(selectedIndex);
                                                });
                                                UIPickerComponent.onScrollStop((selectedIndex) => {
                                                    this.selectedPeriod = selectedIndex;
                                                    this.timeOnScrollStop?.(this.getResult());
                                                });
                                                UIPickerComponent.onAreaChange((oldValue, newValue) => {
                                                    if (this.displayMode === DisplayMode.TIME) {
                                                        const newWidth = newValue.width;
                                                        if (this.firstColumnWidth !== newWidth) {
                                                            this.firstColumnWidth = newWidth;
                                                        }
                                                    }
                                                });
                                            }, UIPickerComponent);
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                ForEach.create();
                                                const forEachItemGenFunction = _item => {
                                                    const item = _item;
                                                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                        Text.create(item);
                                                        Text.maxLines(1);
                                                        Text.fontSize(this.getFontSize());
                                                        Text.textOverflow({ overflow: TextOverflow.Clip });
                                                    }, Text);
                                                    Text.pop();
                                                };
                                                this.forEachUpdateFunction(elmtId, this.periodArray, forEachItemGenFunction);
                                            }, ForEach);
                                            ForEach.pop();
                                            UIPickerComponent.pop();
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                UIPickerComponent.create({ selectedIndex: this.getHourSelectedIndex() });
                                                UIPickerComponent.width(this.getTimeColumnWidth(1));
                                                UIPickerComponent.height(200);
                                                UIPickerComponent.canLoop(this.timeCanLoop);
                                                UIPickerComponent.enableHapticFeedback(this.timeHapticFeedback);
                                                UIPickerComponent.selectionIndicator(this.getMiddlePickerIndicator());
                                                UIPickerComponent.onChange((selectedIndex) => {
                                                    this.onHourChange(selectedIndex);
                                                });
                                                UIPickerComponent.onScrollStop((selectedIndex) => {
                                                    this.onHourChange(selectedIndex);
                                                    this.timeOnScrollStop?.(this.getResult());
                                                });
                                            }, UIPickerComponent);
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                ForEach.create();
                                                const forEachItemGenFunction = _item => {
                                                    const item = _item;
                                                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                        Text.create(item);
                                                        Text.maxLines(1);
                                                        Text.fontSize(this.getFontSize());
                                                        Text.textOverflow({ overflow: TextOverflow.Clip });
                                                    }, Text);
                                                    Text.pop();
                                                };
                                                this.forEachUpdateFunction(elmtId, this.hourArray, forEachItemGenFunction);
                                            }, ForEach);
                                            ForEach.pop();
                                            UIPickerComponent.pop();
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                UIPickerComponent.create({ selectedIndex: this.getMinuteSelectedIndex() });
                                                UIPickerComponent.width(this.getTimeColumnWidth(2));
                                                UIPickerComponent.height(200);
                                                UIPickerComponent.canLoop(this.timeCanLoop);
                                                UIPickerComponent.enableHapticFeedback(this.timeHapticFeedback);
                                                UIPickerComponent.selectionIndicator(this.getLastPickerIndicator(this.getAdjustedRadius()));
                                                UIPickerComponent.onChange((selectedIndex) => {
                                                    this.onMinuteChange(selectedIndex);
                                                });
                                                UIPickerComponent.onScrollStop((selectedIndex) => {
                                                    let startMinuteIndex = DatePickerConstant.MIN_MINUTE;
                                                    if (this.selectedHour === this.startHour) {
                                                        startMinuteIndex = this.startMinute;
                                                    }
                                                    this.selectedMinute = startMinuteIndex + selectedIndex;
                                                    this.updateSecondArray();
                                                    this.timeOnScrollStop?.(this.getResult());
                                                });
                                                UIPickerComponent.onAreaChange((oldValue, newValue) => {
                                                    const newWidth = newValue.width;
                                                    if (this.lastColumnWidth !== newWidth) {
                                                        this.lastColumnWidth = newWidth;
                                                    }
                                                });
                                            }, UIPickerComponent);
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                ForEach.create();
                                                const forEachItemGenFunction = _item => {
                                                    const item = _item;
                                                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                        Text.create(item);
                                                        Text.maxLines(1);
                                                        Text.fontSize(this.getFontSize());
                                                        Text.textOverflow({ overflow: TextOverflow.Clip });
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
                                                UIPickerComponent.width(this.getTimeColumnWidth(0));
                                                UIPickerComponent.height(200);
                                                UIPickerComponent.canLoop(this.timeCanLoop);
                                                UIPickerComponent.enableHapticFeedback(this.timeHapticFeedback);
                                                UIPickerComponent.selectionIndicator(this.displayMode === DisplayMode.DATE_TIME ? this.getMiddlePickerIndicator() : this.getFirstPickerIndicator(this.getAdjustedRadius()));
                                                UIPickerComponent.onChange((selectedIndex) => {
                                                    this.onHourChange(selectedIndex);
                                                });
                                                UIPickerComponent.onScrollStop((selectedIndex) => {
                                                    this.selectedHour = this.startHour + selectedIndex;
                                                    this.updateTimeArrays();
                                                    this.timeOnScrollStop?.(this.getResult());
                                                });
                                                UIPickerComponent.onAreaChange((oldValue, newValue) => {
                                                    if (this.displayMode === DisplayMode.TIME) {
                                                        const newWidth = newValue.width;
                                                        if (this.firstColumnWidth !== newWidth) {
                                                            this.firstColumnWidth = newWidth;
                                                        }
                                                    }
                                                });
                                            }, UIPickerComponent);
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                ForEach.create();
                                                const forEachItemGenFunction = _item => {
                                                    const item = _item;
                                                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                        Text.create(item);
                                                        Text.maxLines(1);
                                                        Text.fontSize(this.getFontSize());
                                                        Text.textOverflow({ overflow: TextOverflow.Clip });
                                                    }, Text);
                                                    Text.pop();
                                                };
                                                this.forEachUpdateFunction(elmtId, this.hourArray, forEachItemGenFunction);
                                            }, ForEach);
                                            ForEach.pop();
                                            UIPickerComponent.pop();
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                UIPickerComponent.create({ selectedIndex: this.getMinuteSelectedIndex() });
                                                UIPickerComponent.width(this.getTimeColumnWidth(1));
                                                UIPickerComponent.height(200);
                                                UIPickerComponent.canLoop(this.timeCanLoop);
                                                UIPickerComponent.enableHapticFeedback(this.timeHapticFeedback);
                                                UIPickerComponent.selectionIndicator(this.getMiddlePickerIndicator());
                                                UIPickerComponent.onChange((selectedIndex) => {
                                                    this.onMinuteChange(selectedIndex);
                                                });
                                                UIPickerComponent.onScrollStop((selectedIndex) => {
                                                    let startMinuteIndex = DatePickerConstant.MIN_MINUTE;
                                                    if (this.selectedHour === this.startHour) {
                                                        startMinuteIndex = this.startMinute;
                                                    }
                                                    this.selectedMinute = startMinuteIndex + selectedIndex;
                                                    this.updateSecondArray();
                                                    this.timeOnScrollStop?.(this.getResult());
                                                });
                                            }, UIPickerComponent);
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                ForEach.create();
                                                const forEachItemGenFunction = _item => {
                                                    const item = _item;
                                                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                        Text.create(item);
                                                        Text.maxLines(1);
                                                        Text.fontSize(this.getFontSize());
                                                        Text.textOverflow({ overflow: TextOverflow.Clip });
                                                    }, Text);
                                                    Text.pop();
                                                };
                                                this.forEachUpdateFunction(elmtId, this.minuteArray, forEachItemGenFunction);
                                            }, ForEach);
                                            ForEach.pop();
                                            UIPickerComponent.pop();
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                UIPickerComponent.create({ selectedIndex: this.getSecondSelectedIndex() });
                                                UIPickerComponent.width(this.getTimeColumnWidth(2));
                                                UIPickerComponent.height(200);
                                                UIPickerComponent.canLoop(this.timeCanLoop);
                                                UIPickerComponent.enableHapticFeedback(this.timeHapticFeedback);
                                                UIPickerComponent.selectionIndicator(this.getLastPickerIndicator(this.getAdjustedRadius()));
                                                UIPickerComponent.onChange((selectedIndex) => {
                                                    this.onSecondChange(selectedIndex);
                                                });
                                                UIPickerComponent.onScrollStop((selectedIndex) => {
                                                    let startSecondIndex = DatePickerConstant.MIN_SECOND;
                                                    if (this.selectedHour === this.startHour && this.selectedMinute === this.startMinute) {
                                                        startSecondIndex = this.startSecond;
                                                    }
                                                    this.selectedSecond = startSecondIndex + selectedIndex;
                                                    this.timeOnScrollStop?.(this.getResult());
                                                });
                                                UIPickerComponent.onAreaChange((oldValue, newValue) => {
                                                    const newWidth = newValue.width;
                                                    if (this.lastColumnWidth !== newWidth) {
                                                        this.lastColumnWidth = newWidth;
                                                    }
                                                });
                                            }, UIPickerComponent);
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                ForEach.create();
                                                const forEachItemGenFunction = _item => {
                                                    const item = _item;
                                                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                        Text.create(item);
                                                        Text.maxLines(1);
                                                        Text.fontSize(this.getFontSize());
                                                        Text.textOverflow({ overflow: TextOverflow.Clip });
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
                                                UIPickerComponent.create({ selectedIndex: this.selectedPeriod });
                                                UIPickerComponent.width(this.getTimeColumnWidth(0));
                                                UIPickerComponent.height(200);
                                                UIPickerComponent.canLoop(false);
                                                UIPickerComponent.enableHapticFeedback(this.timeHapticFeedback);
                                                UIPickerComponent.selectionIndicator(this.displayMode === DisplayMode.DATE_TIME ? this.getMiddlePickerIndicator() : this.getFirstPickerIndicator(this.getAdjustedRadius()));
                                                UIPickerComponent.onChange((selectedIndex) => {
                                                    this.onPeriodChange(selectedIndex);
                                                });
                                                UIPickerComponent.onScrollStop((selectedIndex) => {
                                                    this.selectedPeriod = selectedIndex;
                                                    this.timeOnScrollStop?.(this.getResult());
                                                });
                                                UIPickerComponent.onAreaChange((oldValue, newValue) => {
                                                    if (this.displayMode === DisplayMode.TIME) {
                                                        const newWidth = newValue.width;
                                                        if (this.firstColumnWidth !== newWidth) {
                                                            this.firstColumnWidth = newWidth;
                                                        }
                                                    }
                                                });
                                            }, UIPickerComponent);
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                ForEach.create();
                                                const forEachItemGenFunction = _item => {
                                                    const item = _item;
                                                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                        Text.create(item);
                                                        Text.maxLines(1);
                                                        Text.fontSize(this.getFontSize());
                                                        Text.textOverflow({ overflow: TextOverflow.Clip });
                                                    }, Text);
                                                    Text.pop();
                                                };
                                                this.forEachUpdateFunction(elmtId, this.periodArray, forEachItemGenFunction);
                                            }, ForEach);
                                            ForEach.pop();
                                            UIPickerComponent.pop();
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                UIPickerComponent.create({ selectedIndex: this.getHourSelectedIndex() });
                                                UIPickerComponent.width(this.getTimeColumnWidth(1));
                                                UIPickerComponent.height(200);
                                                UIPickerComponent.canLoop(this.timeCanLoop);
                                                UIPickerComponent.enableHapticFeedback(this.timeHapticFeedback);
                                                UIPickerComponent.selectionIndicator(this.getMiddlePickerIndicator());
                                                UIPickerComponent.onChange((selectedIndex) => {
                                                    this.onHourChange(selectedIndex);
                                                });
                                                UIPickerComponent.onScrollStop((selectedIndex) => {
                                                    this.onHourChange(selectedIndex);
                                                    this.timeOnScrollStop?.(this.getResult());
                                                });
                                            }, UIPickerComponent);
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                ForEach.create();
                                                const forEachItemGenFunction = _item => {
                                                    const item = _item;
                                                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                        Text.create(item);
                                                        Text.maxLines(1);
                                                        Text.fontSize(this.getFontSize());
                                                        Text.textOverflow({ overflow: TextOverflow.Clip });
                                                    }, Text);
                                                    Text.pop();
                                                };
                                                this.forEachUpdateFunction(elmtId, this.hourArray, forEachItemGenFunction);
                                            }, ForEach);
                                            ForEach.pop();
                                            UIPickerComponent.pop();
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                UIPickerComponent.create({ selectedIndex: this.getMinuteSelectedIndex() });
                                                UIPickerComponent.width(this.getTimeColumnWidth(2));
                                                UIPickerComponent.height(200);
                                                UIPickerComponent.canLoop(this.timeCanLoop);
                                                UIPickerComponent.enableHapticFeedback(this.timeHapticFeedback);
                                                UIPickerComponent.selectionIndicator(this.getMiddlePickerIndicator());
                                                UIPickerComponent.onChange((selectedIndex) => {
                                                    this.onMinuteChange(selectedIndex);
                                                });
                                                UIPickerComponent.onScrollStop((selectedIndex) => {
                                                    let startMinuteIndex = DatePickerConstant.MIN_MINUTE;
                                                    if (this.selectedHour === this.startHour) {
                                                        startMinuteIndex = this.startMinute;
                                                    }
                                                    this.selectedMinute = startMinuteIndex + selectedIndex;
                                                    this.updateSecondArray();
                                                    this.timeOnScrollStop?.(this.getResult());
                                                });
                                            }, UIPickerComponent);
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                ForEach.create();
                                                const forEachItemGenFunction = _item => {
                                                    const item = _item;
                                                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                        Text.create(item);
                                                        Text.maxLines(1);
                                                        Text.fontSize(this.getFontSize());
                                                        Text.textOverflow({ overflow: TextOverflow.Clip });
                                                    }, Text);
                                                    Text.pop();
                                                };
                                                this.forEachUpdateFunction(elmtId, this.minuteArray, forEachItemGenFunction);
                                            }, ForEach);
                                            ForEach.pop();
                                            UIPickerComponent.pop();
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                UIPickerComponent.create({ selectedIndex: this.getSecondSelectedIndex() });
                                                UIPickerComponent.width(this.getTimeColumnWidth(3));
                                                UIPickerComponent.height(200);
                                                UIPickerComponent.canLoop(this.timeCanLoop);
                                                UIPickerComponent.enableHapticFeedback(this.timeHapticFeedback);
                                                UIPickerComponent.selectionIndicator(this.getLastPickerIndicator(this.getAdjustedRadius()));
                                                UIPickerComponent.onChange((selectedIndex) => {
                                                    this.onSecondChange(selectedIndex);
                                                });
                                                UIPickerComponent.onScrollStop((selectedIndex) => {
                                                    let startSecondIndex = DatePickerConstant.MIN_SECOND;
                                                    if (this.selectedHour === this.startHour && this.selectedMinute === this.startMinute) {
                                                        startSecondIndex = this.startSecond;
                                                    }
                                                    this.selectedSecond = startSecondIndex + selectedIndex;
                                                    this.timeOnScrollStop?.(this.getResult());
                                                });
                                                UIPickerComponent.onAreaChange((oldValue, newValue) => {
                                                    const newWidth = newValue.width;
                                                    if (this.lastColumnWidth !== newWidth) {
                                                        this.lastColumnWidth = newWidth;
                                                    }
                                                });
                                            }, UIPickerComponent);
                                            this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                ForEach.create();
                                                const forEachItemGenFunction = _item => {
                                                    const item = _item;
                                                    this.observeComponentCreation2((elmtId, isInitialRender) => {
                                                        Text.create(item);
                                                        Text.maxLines(1);
                                                        Text.fontSize(this.getFontSize());
                                                        Text.textOverflow({ overflow: TextOverflow.Clip });
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
