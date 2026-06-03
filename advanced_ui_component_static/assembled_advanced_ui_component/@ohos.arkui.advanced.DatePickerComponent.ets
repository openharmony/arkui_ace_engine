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

import {
  Component,
  Row,
  Text,
  UIPickerComponent,
  ForEach,
  PickerIndicatorType,
  PickerIndicatorStyle,
  BorderRadiuses,
  Callback,
  TextOverflow
} from '@ohos.arkui.component';
import { State, PropRef, Watch } from '@ohos.arkui.stateManagement';
import { LengthMetrics } from '@ohos.arkui.node';
import { intl } from '@kit.LocalizationKit';
import i18n from '@ohos.i18n';
import { commonEventManager } from '@kit.BasicServicesKit';

export enum DateMode {
  DATE = 0,
  YEAR_AND_MONTH = 1,
  MONTH_AND_DAY = 2
}

export enum DisplayMode {
  DATE = 0,
  TIME = 1,
  DATE_TIME = 2
}

export enum TimeFormat {
  HOUR_MINUTE = 0,
  HOUR_MINUTE_SECOND = 1
}

export class DatePickerComponentResult {
  public year?: int;
  public month?: int;
  public day?: int;
  public hour?: int;
  public minute?: int;
  public second?: int;
}

const noop = (result: DatePickerComponentResult) => {};

export class CommonOptions {
  public start?: Date;
  public end?: Date;
  public selected?: Date;
  public loop?: boolean;
  public onChange?: Callback<DatePickerComponentResult>;
  public onScrollStop?: Callback<DatePickerComponentResult>;
  public enableHapticFeedback?: boolean;
}

export class DateOptions extends CommonOptions {
  public mode?: DateMode;
  public lunar?: boolean;
}

export class TimeOptions extends CommonOptions {
  public format?: TimeFormat;
  public useMilitaryTime?: boolean;
}

export class DatePickerComponentOptions {
  public displayMode?: DisplayMode;
  public dateOptions?: DateOptions;
  public timeOptions?: TimeOptions;
}

class DatePickerConstant {
  public static readonly MIN_YEAR: int = 0;
  public static readonly MAX_YEAR: int = 10000;
  public static readonly DEFAULT_START_YEAR: int = 1970;
  public static readonly DEFAULT_END_YEAR: int = 2100;
  public static readonly MIN_MONTH: int = 0;
  public static readonly MAX_MONTH: int = 11;
  public static readonly MIN_DAY: int = 1;
  public static readonly MIN_HOUR: int = 0;
  public static readonly MAX_HOUR: int = 23;
  public static readonly MIN_MINUTE: int = 0;
  public static readonly MAX_MINUTE: int = 59;
  public static readonly MIN_SECOND: int = 0;
  public static readonly MAX_SECOND: int = 59;
  public static readonly MONTHS_IN_YEAR: int = 12;
  public static readonly DEFAULT_STEP: int = 1;
  public static readonly SYSTEM_MIN_DATE: Date = new Date(1970, 0, 1);
  public static readonly SYSTEM_MAX_DATE: Date = new Date(2100, 11, 31);
}

@Component
export struct DatePickerComponent {
  @PropRef @Watch('onOptionsChange') options: DatePickerComponentOptions = new DatePickerComponentOptions();
  @State displayMode: DisplayMode = DisplayMode.DATE;
  @State selectedYear: int = 0;
  @State selectedMonth: int = 0;
  @State selectedDay: int = 0;
  @State selectedHour: int = 0;
  @State selectedMinute: int = 0;
  @State selectedSecond: int = 0;
  @State startYear: int = DatePickerConstant.DEFAULT_START_YEAR;
  @State endYear: int = DatePickerConstant.DEFAULT_END_YEAR;
  @State startMonth: int = DatePickerConstant.MIN_MONTH;
  @State endMonth: int = DatePickerConstant.MAX_MONTH;
  @State startDay: int = DatePickerConstant.MIN_DAY;
  @State endDay: int = 31;
  @State startHour: int = DatePickerConstant.MIN_HOUR;
  @State endHour: int = DatePickerConstant.MAX_HOUR;
  @State startMinute: int = DatePickerConstant.MIN_MINUTE;
  @State endMinute: int = DatePickerConstant.MAX_MINUTE;
  @State startSecond: int = DatePickerConstant.MIN_SECOND;
  @State endSecond: int = DatePickerConstant.MAX_SECOND;
  @State dateMode: DateMode = DateMode.DATE;
  @State timeFormat: TimeFormat = TimeFormat.HOUR_MINUTE;
  @State useMilitaryTime: boolean = false;
  @State lunar: boolean = false;
  @State dateCanLoop: boolean = true;
  @State timeCanLoop: boolean = true;
  @State dateHapticFeedback: boolean = true;
  @State timeHapticFeedback: boolean = true;
  @State yearArray: Array<string> = new Array<string>();
  @State monthArray: Array<string> = new Array<string>();
  @State dayArray: Array<string> = new Array<string>();
  @State hourArray: Array<string> = new Array<string>();
  @State minuteArray: Array<string> = new Array<string>();
  @State secondArray: Array<string> = new Array<string>();
  @State periodArray: Array<string> = new Array<string>();
  @State selectedPeriod: int = 0;
  @State currentLocale: string = '';
  private dateOnChange: Callback<DatePickerComponentResult> = noop;
  private dateOnScrollStop: Callback<DatePickerComponentResult> = noop;
  private timeOnChange: Callback<DatePickerComponentResult> = noop;
  private timeOnScrollStop: Callback<DatePickerComponentResult> = noop;
  private localeID: string = '';
  private lunarCalendar: i18n.Calendar | null = null;
  private subscriber: commonEventManager.CommonEventSubscriber | null = null;
  private formatter: intl.NumberFormat = new intl.NumberFormat();
  private yearFormatter: intl.NumberFormat = new intl.NumberFormat('', { useGrouping: false });
  
  aboutToAppear(): void {
    const locale = i18n.System.getSystemLocaleInstance();
    this.localeID = locale.toString();
    this.currentLocale = i18n.System.getSystemLanguage();
    this.formatter = new intl.NumberFormat();
    this.yearFormatter = new intl.NumberFormat(this.localeID, { useGrouping: false });
  
    if (this.selectedYear === 0 || this.selectedMonth === 0 || this.selectedDay === 0) {
      const now = new Date();
      this.selectedYear = now.getFullYear().toInt();
      this.selectedMonth = now.getMonth().toInt();
      this.selectedDay = now.getDate().toInt();
      this.selectedHour = now.getHours().toInt();
      this.selectedMinute = now.getMinutes().toInt();
      this.selectedSecond = now.getSeconds().toInt();
      // Note: selectedPeriod will be set in initTimeArrays or updateTimeOptions
      // based on the correct useMilitaryTime value
    }
  
    if (this.lunar) {
      this.lunarCalendar = i18n.getCalendar(this.localeID, 'chinese');
    }
  
    if (this.options !== undefined && this.options !== null) {
      this.onOptionsChange('');
    } else {
      this.initArrays();
    }
    
    // Create subscriber to listen for system language changes
    this.createLocaleChangeSubscriber();
  }
  
  aboutToDisappear(): void {
    this.lunarCalendar = null;
    
    // Unsubscribe from locale change events
    if (this.subscriber !== null) {
      const subscriber: commonEventManager.CommonEventSubscriber = this.subscriber!;
      commonEventManager.unsubscribe(subscriber, (err) => {
        if (err) {
          console.error(`Failed to unsubscribe common event. error code: ${err.code}, message: ${err.message}.`);
        }
      });
      this.subscriber = null;
    }
  }
  
  private createLocaleChangeSubscriber(): void {
    const subscribeInfo: commonEventManager.CommonEventSubscribeInfo = {
      events: [commonEventManager.Support.COMMON_EVENT_LOCALE_CHANGED]
    };
    
    commonEventManager.createSubscriber(subscribeInfo)
      .then((commonEventSubscriber: commonEventManager.CommonEventSubscriber) => {
        this.subscriber = commonEventSubscriber;
        commonEventManager.subscribe(commonEventSubscriber, (err, data) => {
          if (err) {
            console.error(`Failed to subscribe common event. error code: ${err.code}, message: ${err.message}.`);
            return;
          }
          // Update locale when system language changes
          this.currentLocale = i18n.System.getSystemLanguage();
          this.onLocaleChange();
        });
      })
      .catch((err: Error) => {
        console.error(`CreateSubscriber failed, code is ${err.message}`);
      });
  }
  
  private onLocaleChange(): void {
    const locale = i18n.System.getSystemLocaleInstance();
    this.localeID = locale.toString();
    this.formatter = new intl.NumberFormat();
    this.yearFormatter = new intl.NumberFormat(this.localeID, { useGrouping: false });
    if (this.lunar) {
      this.lunarCalendar = i18n.getCalendar(this.localeID, 'chinese');
    }
    this.initArrays();
  }
  
  private initArrays(): void {
    if (this.lunar) {
      this.initLunarArrays();
    } else {
      this.initYearArray();
      this.initMonthArray();
      this.initDayArray();
    }
    this.initTimeArrays();
  }
  
  private initLunarArrays(): void {
    this.yearArray = [];
    for (let i: int = this.startYear; i <= this.endYear; i++) {
      this.yearArray.push(this.formatLunarYear(i));
    }
  
    this.monthArray = [];
    for (let i: int = DatePickerConstant.MIN_MONTH; i <= DatePickerConstant.MAX_MONTH; i++) {
      this.monthArray.push(this.formatLunarMonth(i, false));
    }
  
    this.initLunarDayArray();
  }
  
  private initLunarDayArray(): void {
    this.dayArray = [];
    const lunarDays: int = this.getLunarDaysInMonth(this.selectedYear, this.selectedMonth);
    for (let i: int = DatePickerConstant.MIN_DAY; i <= lunarDays; i++) {
      this.dayArray.push(this.formatLunarDay(i));
    }
  }
  
  private getLunarDaysInMonth(gregorianYear: int, lunarMonth: int): int {
    if (this.lunarCalendar === null) {
      return 30;
    }
  
    try {
      let month1Start: Date | null = null;
      let month2Start: Date | null = null;
    
      for (let m: int = 0; m < 12; m++) {
        for (let d: int = 1; d <= 31; d++) {
          const testDate = new Date(gregorianYear, m, d);
          if (this.lunarCalendar !== null) {
            this.lunarCalendar!.setTime(testDate);
            const currentLunarMonth: int = this.lunarCalendar!.get('month');
            const currentLunarDay: int = this.lunarCalendar!.get('date');
        
            if (currentLunarMonth === lunarMonth && currentLunarDay === 1 && month1Start === null) {
              month1Start = testDate;
            }
          
            if (month1Start !== null && month2Start === null) {
              const nextMonth: int = lunarMonth + 1;
              if (currentLunarMonth === nextMonth && currentLunarDay === 1) {
                month2Start = testDate;
                break;
              }
              if (currentLunarMonth === 0 && lunarMonth === 11 && currentLunarDay === 1) {
                month2Start = testDate;
                break;
              }
            }
          }
        }
        if (month1Start !== null && month2Start !== null) {
      break;
        }
      }
    
      if (month1Start !== null && month2Start !== null) {
        const diff: number = (month2Start.getTime() - month1Start.getTime()) / (24 * 60 * 60 * 1000);
        const daysDiff: int = Math.round(diff).toInt();
        return daysDiff;
      }
    
      return 30;
    } catch (e) {
      return 30;
    }
  }
  
  private formatLunarYear(gregorianYear: int): string {
    return this.yearFormatter.format(gregorianYear) + '年';
  }
  
  private formatLunarMonth(month: int, isLeap: boolean): string {
    const lunarMonthNames: string[] = ['正月', '二月', '三月', '四月', '五月', '六月',
                     '七月', '八月', '九月', '十月', '冬月', '腊月'];
  
    if (isLeap) {
      return '闰' + lunarMonthNames[month];
    }
    return lunarMonthNames[month];
  }
  
  private formatLunarDay(day: int): string {
    const lunarDayNames: string[] = ['初一', '初二', '初三', '初四', '初五', '初六', '初七', '初八', '初九', '初十',
                   '十一', '十二', '十三', '十四', '十五', '十六', '十七', '十八', '十九', '二十',
                   '廿一', '廿二', '廿三', '廿四', '廿五', '廿六', '廿七', '廿八', '廿九', '三十'];
  
    if (day >= 1 && day <= 30) {
      const idx: int = (day - 1).toInt();
      return lunarDayNames[idx];
    }
    return day + '日';
  }
  
  private initYearArray(): void {
    this.yearArray = [];
    for (let i: int = this.startYear; i <= this.endYear; i++) {
      this.yearArray.push(this.formatYear(i));
    }
  }
  
  private initMonthArray(): void {
    this.monthArray = [];
    let startMonthIndex: int = DatePickerConstant.MIN_MONTH;
    let endMonthIndex: int = DatePickerConstant.MAX_MONTH;
    
    if (this.selectedYear === this.startYear) {
      startMonthIndex = this.startMonth;
    }
    if (this.selectedYear === this.endYear) {
      endMonthIndex = this.endMonth;
    }
    
    for (let i: int = startMonthIndex; i <= endMonthIndex; i++) {
      this.monthArray.push(this.formatMonth(i));
    }
  }
  
  private initDayArray(): void {
    this.dayArray = [];
    const daysInMonth: int = this.getDaysInMonth(this.selectedYear, this.selectedMonth);
    let startDayIndex: int = DatePickerConstant.MIN_DAY;
    let endDayIndex: int = daysInMonth;
    
    if (this.selectedYear === this.startYear && this.selectedMonth === this.startMonth) {
      startDayIndex = this.startDay;
    }
    if (this.selectedYear === this.endYear && this.selectedMonth === this.endMonth) {
      endDayIndex = Math.min(this.endDay, daysInMonth).toInt();
    }
    
    for (let i: int = startDayIndex; i <= endDayIndex; i++) {
      this.dayArray.push(this.formatDay(i));
    }
  }
  
  private initTimeArrays(): void {
    this.periodArray = [];
    if (!this.useMilitaryTime) {
      this.selectedPeriod = this.selectedHour < 12 ? 0 : 1;
      this.updatePeriodArray();
      this.updateHourArrayFor12Hour();
    } else {
      this.hourArray = [];
      for (let i: int = this.startHour; i <= this.endHour; i++) {
        this.hourArray.push(this.formatNumber(i));
      }
    } else {
      this.updateHourArrayFor12Hour();
    }
  
    this.minuteArray = [];
    let startMinuteIndex: int = DatePickerConstant.MIN_MINUTE;
    let endMinuteIndex: int = DatePickerConstant.MAX_MINUTE;
    
    if (this.selectedHour === this.startHour) {
      startMinuteIndex = this.startMinute;
    }
    if (this.selectedHour === this.endHour) {
      endMinuteIndex = this.endMinute;
    }
    
    for (let i: int = startMinuteIndex; i <= endMinuteIndex; i++) {
      this.minuteArray.push(this.formatMinute(i));
    }
    
    if (this.selectedMinute < startMinuteIndex) {
      this.selectedMinute = startMinuteIndex;
    }
    if (this.selectedMinute > endMinuteIndex) {
      this.selectedMinute = endMinuteIndex;
    }
  
    this.secondArray = [];
    let startSecondIndex: int = DatePickerConstant.MIN_SECOND;
    let endSecondIndex: int = DatePickerConstant.MAX_SECOND;
    
    if (this.selectedHour === this.startHour && this.selectedMinute === this.startMinute) {
      startSecondIndex = this.startSecond;
    }
    if (this.selectedHour === this.endHour && this.selectedMinute === this.endMinute) {
      endSecondIndex = this.endSecond;
    }
    
    for (let i: int = startSecondIndex; i <= endSecondIndex; i++) {
      this.secondArray.push(this.formatSecond(i));
    }
    
    if (this.selectedSecond < startSecondIndex) {
      this.selectedSecond = startSecondIndex;
    }
    if (this.selectedSecond > endSecondIndex) {
      this.selectedSecond = endSecondIndex;
    }
  }
  
  private updateHourArrayFor12Hour(): void {
    this.hourArray = [];
    
    const isAM: boolean = this.selectedPeriod === 0;
    
    // For 12-hour format, build hour array based on current period and time range
    // AM period: 12 (midnight 0:00) and 1-11 (1:00-11:00)
    // PM period: 12 (noon 12:00) and 1-11 (13:00-23:00)
    
    if (isAM) {
      // Check if 12 AM (hour24=0) is within range
      const hour24ForAm12: int = 0;
      if (hour24ForAm12 >= this.startHour && hour24ForAm12 <= this.endHour) {
        this.hourArray.push('12');
      }
      
      // Check if 1-11 AM (hour24=1-11) are within range
      for (let displayHour: int = 1; displayHour <= 11; displayHour++) {
        const hour24: int = displayHour;
        if (hour24 >= this.startHour && hour24 <= this.endHour) {
          this.hourArray.push(this.formatNumber(displayHour));
        }
      }
    } else {
      // Check if 12 PM (hour24=12) is within range
      const hour24ForPm12: int = 12;
      if (hour24ForPm12 >= this.startHour && hour24ForPm12 <= this.endHour) {
        this.hourArray.push('12');
      }
      
      // Check if 1-11 PM (hour24=13-23) are within range
      for (let displayHour: int = 1; displayHour <= 11; displayHour++) {
        const hour24: int = displayHour + 12;
        if (hour24 >= this.startHour && hour24 <= this.endHour) {
          this.hourArray.push(this.formatNumber(displayHour));
        }
      }
    }
    
    // Fallback: if no hours available for current period, show all 12 hours
    if (this.hourArray.length === 0) {
      for (let i: int = 1; i <= 12; i++) {
        this.hourArray.push(this.formatNumber(i));
      }
    }
  }
  
  private updatePeriodArray(): void {
    this.periodArray = [];
    
    // Check if AM period (hour24=0-11) has any available hours
    let canSelectAM: boolean = false;
    for (let hour: int = 0; hour <= 11; hour++) {
      if (hour >= this.startHour && hour <= this.endHour) {
        canSelectAM = true;
        break;
      }
    }
    
    // Check if PM period (hour24=12-23) has any available hours
    let canSelectPM: boolean = false;
    for (let hour: int = 12; hour <= 23; hour++) {
      if (hour >= this.startHour && hour <= this.endHour) {
        canSelectPM = true;
        break;
      }
    }
    
    if (canSelectAM && canSelectPM) {
      this.periodArray.push(this.formatPeriod(true));
      this.periodArray.push(this.formatPeriod(false));
    } else if (canSelectAM && !canSelectPM) {
      this.periodArray.push(this.formatPeriod(true));
      if (this.selectedPeriod === 1) {
        this.selectedPeriod = 0;
        // Adjust selectedHour to AM range when forced to switch to AM
        if (this.selectedHour >= 12) {
          const minAMHour: int = Math.max(0, this.startHour).toInt();
          const maxAMHour: int = Math.min(11, this.endHour).toInt();
          if (this.selectedHour === 12) {
            this.selectedHour = 0; // 12 PM -> 12 AM (0:00)
          } else {
            this.selectedHour = Math.max(minAMHour, Math.min(maxAMHour, this.selectedHour - 12)).toInt();
          }
        }
      }
    } else if (!canSelectAM && canSelectPM) {
      this.periodArray.push(this.formatPeriod(false));
      if (this.selectedPeriod === 0) {
        this.selectedPeriod = 1;
        // Adjust selectedHour to PM range when forced to switch to PM
        if (this.selectedHour < 12) {
          const minPMHour = Math.max(12, this.startHour).toInt();
          const maxPMHour = Math.min(23, this.endHour).toInt();
          // 计算目标小时（24小时制）：12 AM->12, 1-11 AM->13-23
          let targetHour24 = this.selectedHour === 0 ? 12 : this.selectedHour + 12;
          // 确保目标小时在有效范围内
          this.selectedHour = Math.max(minPMHour, Math.min(maxPMHour, targetHour24)).toInt();
        }
      }
    } else {
      // Fallback: show both periods if no hours available (shouldn't happen with valid ranges)
      this.periodArray.push(this.formatPeriod(true));
      this.periodArray.push(this.formatPeriod(false));
    }
  }
  
  private formatNumber(num: int): string {
    if (num < 10) {
      return '0' + String(num);
    }
    return String(num);
  }
  
  private isChineseLocale(): boolean {
    const localeStr: string = this.localeID;
    return localeStr.startsWith('zh') || localeStr.includes('zh-CN') || localeStr.includes('zh-TW') || localeStr.includes('zh-Hans') || localeStr.includes('zh-Hant');
  }
  
  private formatYear(year: int): string {
    if (this.isChineseLocale()) {
      return this.yearFormatter.format(year) + '年';
    }
    return this.yearFormatter.format(year);
  }
  
  private formatMonth(month: int): string {
    if (this.isChineseLocale()) {
      return (month + 1) + '月';
    }
  
    const monthNames: string[] = [
      'January', 'February', 'March', 'April', 'May', 'June',
      'July', 'August', 'September', 'October', 'November', 'December'
    ];
  
    const shortMonthNames: string[] = ['Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun',
                                       'Jul', 'Aug', 'Sep', 'Oct', 'Nov', 'Dec'];
  
    try {
      const localeStr: string = this.localeID;
      if (!localeStr || localeStr.length === 0) {
        return this.displayMode === DisplayMode.DATE_TIME ? shortMonthNames[month] : monthNames[month];
      }
    
      const monthFormat: string = this.displayMode === DisplayMode.DATE_TIME ? 'short' : 'long';
      const dateFormat = new intl.DateTimeFormat(localeStr, {
        month: monthFormat
      });
      const safeMonth: int = Math.max(0, Math.min(11, month)).toInt();
      const date = new Date(2026, safeMonth, 15);
      return dateFormat.format(date);
    } catch (error) {
      return this.displayMode === DisplayMode.DATE_TIME ? shortMonthNames[month] : monthNames[month];
    }
  }
  
  private formatDay(day: int): string {
    if (this.isChineseLocale()) {
      return this.formatter.format(day) + '日';
    }
  
    try {
      const localeStr: string = this.localeID;
      if (!localeStr || localeStr.length === 0) {
        return this.formatter.format(day);
      }
    
      const dateFormat = new intl.DateTimeFormat(localeStr, {
        day: 'numeric'
      });
      const safeDay: int = Math.max(1, Math.min(31, day)).toInt();
      const date = new Date(2026, 0, safeDay);
      return dateFormat.format(date);
    } catch (error) {
      return this.formatter.format(day);
    }
  }
  
  private formatMinute(minute: int): string {
    return this.formatNumber(minute);
  }
  
  private formatSecond(second: int): string {
    return this.formatNumber(second);
  }
  
  private formatPeriod(isAM: boolean): string {
    try {
      const localeStr: string = this.localeID;
      if (!localeStr || localeStr.length === 0) {
        return isAM ? 'AM' : 'PM';
      }
    
      if (this.isChineseLocale()) {
        return isAM ? '上午' : '下午';
      }
    
      const hour: int = isAM ? 10 : 22;
      const dateFormat = new intl.DateTimeFormat(localeStr, {
        hour: 'numeric',
        hour12: true
      });
      const date = new Date(2026, 0, 1, hour, 0, 0);
      const formatted: string = dateFormat.format(date);
    
      if (formatted.includes('上午')) {
        return isAM ? '上午' : '下午';
      } else if (formatted.includes('下午')) {
        return isAM ? '上午' : '下午';
      } else if (formatted.includes('AM') || formatted.includes('am')) {
        return isAM ? 'AM' : 'PM';
      } else if (formatted.includes('PM') || formatted.includes('pm')) {
        return isAM ? 'AM' : 'PM';
      }
    
      return isAM ? 'AM' : 'PM';
    } catch (error) {
      return isAM ? 'AM' : 'PM';
    }
  }
  
  private getDaysInMonth(year: int, month: int): int {
    const monthsWith31Days: int[] = [0, 2, 4, 6, 7, 9, 11];
    const monthsWith30Days: int[] = [3, 5, 8, 10];
  
    if (month === 1) {
      const isLeapYear: boolean = (year % 4 === 0 && year % 100 !== 0) || (year % 400 === 0);
      return isLeapYear ? 29 : 28;
    }
  
    for (let i: int = 0; i < monthsWith31Days.length; i++) {
      if (monthsWith31Days[i] === month) {
        return 31;
      }
    }
  
    for (let i: int = 0; i < monthsWith30Days.length; i++) {
      if (monthsWith30Days[i] === month) {
        return 30;
      }
    }
  
    return 30;
  }
  
  private validateDate(date: Date): Date | undefined {
    try {
      const year: int = date.getFullYear().toInt();
      const month: int = date.getMonth().toInt();
      const day: int = date.getDate().toInt();
    
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
    
      const daysInMonth: int = this.getDaysInMonth(year, month);
      if (day > daysInMonth) {
        return undefined;
      }
    
      // Detect JavaScript auto-correction by checking year jump
      // If year jumped significantly (> 1 year), it indicates异常input
      const originalTime: number = date.getTime();
      const correctedDate: Date = new Date(year, month, day);
      const correctedTime: number = correctedDate.getTime();
    
      // If time difference > 365 days, indicates year jump due to异常month/day
      const timeDiff: number = Math.abs(originalTime - correctedTime);
      const oneYearInMs: number = 365 * 24 * 60 * 60 * 1000;
      if (timeDiff > oneYearInMs) {
        return undefined;
      }
    
      return correctedDate;
    } catch (e) {
      return undefined;
    }
  }
  
  private validateTime(date: Date): Date | undefined {
    try {
      const hour: int = date.getHours().toInt();
      const minute: int = date.getMinutes().toInt();
      const second: int = date.getSeconds().toInt();
    
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
      const year: int = date.getFullYear().toInt();
      const month: int = date.getMonth().toInt();
      const day: int = date.getDate().toInt();
    
      const originalTime: number = date.getTime();
      const correctedTime: number = new Date(year, month, day, hour, minute, second).getTime();
    
      // If time difference > 1 hour, indicates异常minute/second overflow
      const timeDiff: number = Math.abs(originalTime - correctedTime);
      const oneHourInMs: number = 60 * 60 * 1000;
      if (timeDiff > oneHourInMs) {
        return undefined;
      }
    
      // Return Date with fixed base date (2026-01-01) + validated time
      // This ensures timeOptions only considers time part, ignoring date part
      return new Date(2026, 0, 1, hour, minute, second);
    } catch (e) {
      return undefined;
    }
  }
  
  private createDateFromParams(year: int, month: int, day: int): Date {
    return new Date(year, month, day);
  }
  
  private onOptionsChange(str: string): void {
    if (this.options.displayMode !== undefined) {
      this.displayMode = this.options.displayMode!;
    }
  
    if (this.options.dateOptions !== undefined && this.options.dateOptions !== null) {
      this.updateDateOptions(this.options.dateOptions!);
    }
  
    if (this.options.timeOptions !== undefined && this.options.timeOptions !== null) {
      this.updateTimeOptions(this.options.timeOptions!);
    }
  
    this.initArrays();
  }
  
  private updateDateOptions(dateOptions: DateOptions): void {
    if (dateOptions.mode !== undefined) {
      this.dateMode = dateOptions.mode!;
    }
  
    if (dateOptions.lunar !== undefined) {
      this.lunar = dateOptions.lunar!;
      if (this.lunar) {
        this.lunarCalendar = i18n.getCalendar(this.localeID, 'chinese');
      } else {
        this.lunarCalendar = null;
      }
    }
  
    if (dateOptions.loop !== undefined) {
      this.dateCanLoop = dateOptions.loop!;
    }
  
    if (dateOptions.enableHapticFeedback !== undefined) {
      this.dateHapticFeedback = dateOptions.enableHapticFeedback!;
    }
  
    let startValid: boolean = false;
    let endValid: boolean = false;
    let startDate: Date | undefined = undefined;
    let endDate: Date | undefined = undefined;
  
    if (dateOptions.start !== undefined && dateOptions.start !== null) {
      startDate = this.validateDate(dateOptions.start!);
      if (startDate !== undefined) {
        startValid = true;
      }
    }
  
    if (dateOptions.end !== undefined && dateOptions.end !== null) {
      endDate = this.validateDate(dateOptions.end!);
      if (endDate !== undefined) {
        endValid = true;
      }
    }
  
    if (startValid && endValid) {
      if (startDate!.getTime() > endDate!.getTime()) {
        this.startYear = DatePickerConstant.DEFAULT_START_YEAR;
        this.endYear = DatePickerConstant.DEFAULT_END_YEAR;
        this.startMonth = DatePickerConstant.MIN_MONTH;
        this.endMonth = DatePickerConstant.MAX_MONTH;
        this.startDay = DatePickerConstant.MIN_DAY;
        this.endDay = 31;
      } else {
        this.startYear = startDate!.getFullYear().toInt();
        this.startMonth = startDate!.getMonth().toInt();
        this.startDay = startDate!.getDate().toInt();
        this.endYear = endDate!.getFullYear().toInt();
        this.endMonth = endDate!.getMonth().toInt();
        this.endDay = endDate!.getDate().toInt();
      }
    } else if (startValid && !endValid) {
      this.startYear = startDate!.getFullYear().toInt();
      this.startMonth = startDate!.getMonth().toInt();
      this.startDay = startDate!.getDate().toInt();
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
    } else if (!startValid && endValid) {
      this.startYear = DatePickerConstant.DEFAULT_START_YEAR;
      this.startMonth = DatePickerConstant.MIN_MONTH;
      this.startDay = DatePickerConstant.MIN_DAY;
      this.endYear = endDate!.getFullYear().toInt();
      this.endMonth = endDate!.getMonth().toInt();
      this.endDay = endDate!.getDate().toInt();
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
    } else {
      this.startYear = DatePickerConstant.DEFAULT_START_YEAR;
      this.endYear = DatePickerConstant.DEFAULT_END_YEAR;
      this.startMonth = DatePickerConstant.MIN_MONTH;
      this.endMonth = DatePickerConstant.MAX_MONTH;
      this.startDay = DatePickerConstant.MIN_DAY;
      this.endDay = 31;
    }
  
    if (this.startYear > this.endYear) {
      const tempYear: int = this.startYear;
      const tempMonth: int = this.startMonth;
      const tempDay: int = this.startDay;
      this.startYear = this.endYear;
      this.startMonth = this.endMonth;
      this.startDay = this.endDay;
      this.endYear = tempYear;
      this.endMonth = tempMonth;
      this.endDay = tempDay;
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
    let selectedDate: Date | undefined = undefined;
    let selectedValid: boolean = false;
  
    if (dateOptions.selected !== undefined && dateOptions.selected !== null) {
      selectedDate = this.validateDate(dateOptions.selected!);
      if (selectedDate !== undefined) {
        selectedValid = true;
      }
    }
  
    // Create Date objects for start and end
    const startDateObj: Date = this.createDateFromParams(this.startYear, this.startMonth, this.startDay);
    const endDateObj: Date = this.createDateFromParams(this.endYear, this.endMonth, this.endDay);
  
    // Determine the initial selected date
    let targetDate: Date;
    if (selectedValid) {
      targetDate = selectedDate!;
    } else {
      targetDate = now;
    }
  
    // Adjust selected date to be within range
    if (targetDate.getTime() < startDateObj.getTime()) {
      targetDate = startDateObj;
    } else if (targetDate.getTime() > endDateObj.getTime()) {
      targetDate = endDateObj;
    }
  
    // Extract year, month, day from adjusted date
    if (this.lunar && this.lunarCalendar !== null) {
      this.lunarCalendar!.setTime(targetDate);
      const lunarMonth: int = this.lunarCalendar!.get('month');
      const lunarDay: int = this.lunarCalendar!.get('date');
    
      this.selectedYear = targetDate.getFullYear().toInt();
      this.selectedMonth = lunarMonth;
      this.selectedDay = lunarDay;
    } else {
      this.selectedYear = targetDate.getFullYear().toInt();
      this.selectedMonth = targetDate.getMonth().toInt();
      this.selectedDay = targetDate.getDate().toInt();
    }
  
    // Ensure day doesn't exceed days in month
    const daysInMonth: int = this.getDaysInMonth(this.selectedYear, this.selectedMonth);
    if (this.selectedDay > daysInMonth) {
      this.selectedDay = daysInMonth;
    }
  
    if (dateOptions.onChange !== undefined) {
      this.dateOnChange = dateOptions.onChange ?? noop;
    }
  
    if (dateOptions.onScrollStop !== undefined) {
      this.dateOnScrollStop = dateOptions.onScrollStop ?? noop;
    }
  }
  
  private updateTimeOptions(timeOptions: TimeOptions): void {
    if (timeOptions.format !== undefined) {
      this.timeFormat = timeOptions.format!;
    }
  
    if (timeOptions.useMilitaryTime !== undefined) {
      this.useMilitaryTime = timeOptions.useMilitaryTime!;
    }
  
    if (timeOptions.loop !== undefined) {
      this.timeCanLoop = timeOptions.loop!;
    }
  
    if (timeOptions.enableHapticFeedback !== undefined) {
      this.timeHapticFeedback = timeOptions.enableHapticFeedback!;
    }
  
    let startValid: boolean = false;
    let endValid: boolean = false;
    let startTime: Date | undefined = undefined;
    let endTime: Date | undefined = undefined;
  
    if (timeOptions.start !== undefined && timeOptions.start !== null) {
      startTime = this.validateTime(timeOptions.start!);
      if (startTime !== undefined) {
        startValid = true;
      }
    }
  
    if (timeOptions.end !== undefined && timeOptions.end !== null) {
      endTime = this.validateTime(timeOptions.end!);
      if (endTime !== undefined) {
        endValid = true;
      }
    }
  
    if (startValid && endValid) {
      if (startTime!.getHours() > endTime!.getHours() ||
          (startTime!.getHours() === endTime!.getHours() && startTime!.getMinutes() > endTime!.getMinutes()) ||
          (startTime!.getHours() === endTime!.getHours() && startTime!.getMinutes() === endTime!.getMinutes() && startTime!.getSeconds() > endTime!.getSeconds())) {
        this.startHour = DatePickerConstant.MIN_HOUR;
        this.endHour = DatePickerConstant.MAX_HOUR;
        this.startMinute = DatePickerConstant.MIN_MINUTE;
        this.endMinute = DatePickerConstant.MAX_MINUTE;
        this.startSecond = DatePickerConstant.MIN_SECOND;
        this.endSecond = DatePickerConstant.MAX_SECOND;
      } else {
        this.startHour = startTime!.getHours().toInt();
        this.startMinute = startTime!.getMinutes().toInt();
        this.startSecond = startTime!.getSeconds().toInt();
        this.endHour = endTime!.getHours().toInt();
        this.endMinute = endTime!.getMinutes().toInt();
        this.endSecond = endTime!.getSeconds().toInt();
      }
    } else if (startValid && !endValid) {
      this.startHour = startTime!.getHours().toInt();
      this.startMinute = startTime!.getMinutes().toInt();
      this.startSecond = startTime!.getSeconds().toInt();
      this.endHour = DatePickerConstant.MAX_HOUR;
      this.endMinute = DatePickerConstant.MAX_MINUTE;
      this.endSecond = DatePickerConstant.MAX_SECOND;
    } else if (!startValid && endValid) {
      this.startHour = DatePickerConstant.MIN_HOUR;
      this.startMinute = DatePickerConstant.MIN_MINUTE;
      this.startSecond = DatePickerConstant.MIN_SECOND;
      this.endHour = endTime!.getHours().toInt();
      this.endMinute = endTime!.getMinutes().toInt();
      this.endSecond = endTime!.getSeconds().toInt();
    } else {
      this.startHour = DatePickerConstant.MIN_HOUR;
      this.endHour = DatePickerConstant.MAX_HOUR;
      this.startMinute = DatePickerConstant.MIN_MINUTE;
      this.endMinute = DatePickerConstant.MAX_MINUTE;
      this.startSecond = DatePickerConstant.MIN_SECOND;
      this.endSecond = DatePickerConstant.MAX_SECOND;
    }
  
    this.startHour = Math.max(DatePickerConstant.MIN_HOUR, Math.min(DatePickerConstant.MAX_HOUR, this.startHour)).toInt();
    this.endHour = Math.max(DatePickerConstant.MIN_HOUR, Math.min(DatePickerConstant.MAX_HOUR, this.endHour)).toInt();
    this.startMinute = Math.max(DatePickerConstant.MIN_MINUTE, Math.min(DatePickerConstant.MAX_MINUTE, this.startMinute)).toInt();
    this.endMinute = Math.max(DatePickerConstant.MIN_MINUTE, Math.min(DatePickerConstant.MAX_MINUTE, this.endMinute)).toInt();
    this.startSecond = Math.max(DatePickerConstant.MIN_SECOND, Math.min(DatePickerConstant.MAX_SECOND, this.startSecond)).toInt();
    this.endSecond = Math.max(DatePickerConstant.MIN_SECOND, Math.min(DatePickerConstant.MAX_SECOND, this.endSecond)).toInt();
  
    const now = new Date();
    let selectedTime: Date | undefined = undefined;
    let selectedValid: boolean = false;
  
    if (timeOptions.selected !== undefined && timeOptions.selected !== null) {
      selectedTime = this.validateTime(timeOptions.selected!);
      if (selectedTime !== undefined) {
        selectedValid = true;
      }
    }
  
    // Determine the initial selected time
    let targetTime: Date;
    if (selectedValid) {
      targetTime = selectedTime!;
    } else {
      targetTime = now;
    }
  
    // Create Date objects for start and end time on same day
    const startTimeObj: Date = new Date(2026, 0, 1, this.startHour, this.startMinute, this.startSecond);
    const endTimeObj: Date = new Date(2026, 0, 1, this.endHour, this.endMinute, this.endSecond);
    const targetTimeObj: Date = new Date(2026, 0, 1, targetTime.getHours(), targetTime.getMinutes(), targetTime.getSeconds());
  
    // Adjust selected time to be within range
    if (targetTimeObj.getTime() < startTimeObj.getTime()) {
      targetTimeObj.setTime(startTimeObj.getTime());
    } else if (targetTimeObj.getTime() > endTimeObj.getTime()) {
      targetTimeObj.setTime(endTimeObj.getTime());
    }
  
    // Extract hour, minute, second from adjusted time
    this.selectedHour = targetTimeObj.getHours().toInt();
    this.selectedMinute = targetTimeObj.getMinutes().toInt();
    this.selectedSecond = targetTimeObj.getSeconds().toInt();
  
    // Set selectedPeriod based on selectedHour for 12-hour format
    if (!this.useMilitaryTime) {
      this.selectedPeriod = this.selectedHour < 12 ? 0 : 1;
    }
  
    if (timeOptions.onChange !== undefined) {
      this.timeOnChange = timeOptions.onChange ?? noop;
    }
  
    if (timeOptions.onScrollStop !== undefined) {
      this.timeOnScrollStop = timeOptions.onScrollStop ?? noop;
    }
  }
  
  private getResult(): DatePickerComponentResult {
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
  
private onYearChange(selectedIndex: int): void {
    this.selectedYear = this.startYear + selectedIndex;
    
    // Update month array based on new year
    this.initMonthArray();
    
    // Adjust selectedMonth to be within new month range
    let startMonthIndex: int = DatePickerConstant.MIN_MONTH;
    let endMonthIndex: int = DatePickerConstant.MAX_MONTH;
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
    this.dateOnChange(this.getResult());
  }
  
  private onMonthChange(selectedIndex: int): void {
    let startMonthIndex: int = DatePickerConstant.MIN_MONTH;
    if (this.selectedYear === this.startYear) {
      startMonthIndex = this.startMonth;
    }
    this.selectedMonth = startMonthIndex + selectedIndex;
    this.updateDaysArray();
    this.dateOnChange(this.getResult());
  }
  
  private onDayChange(selectedIndex: int): void {
    let startDayIndex: int = DatePickerConstant.MIN_DAY;
    if (this.selectedYear === this.startYear && this.selectedMonth === this.startMonth) {
      startDayIndex = this.startDay;
    }
    this.selectedDay = startDayIndex + selectedIndex;
    this.dateOnChange(this.getResult());
  }
  
private onHourChange(selectedIndex: int): void {
      if (this.useMilitaryTime) {
        this.selectedHour = this.startHour + selectedIndex;
      } else {
        const oldDisplayHour: int = this.selectedHour === 0 || this.selectedHour === 12 ? 12 : 
                                  (this.selectedHour > 12 ? this.selectedHour - 12 : this.selectedHour);
        
        // Get the actual display hour from hourArray
        const newDisplayHour: int = parseInt(this.hourArray[selectedIndex]).toInt();
        
        // Crossing 11↔12 always triggers period toggle
        const crossingBoundary: boolean = (oldDisplayHour === 11 && newDisplayHour === 12) || 
                                         (oldDisplayHour === 12 && newDisplayHour === 11);
        
        if (crossingBoundary) {
          // Toggle period
          this.selectedPeriod = this.selectedPeriod === 0 ? 1 : 0;
        }
        
        // Convert display hour to 24-hour format based on CURRENT period (after toggle)
        if (newDisplayHour === 12) {
          if (this.selectedPeriod === 0) {
            this.selectedHour = 0; // 12 AM = 0:00 (24-hour)
          } else {
            this.selectedHour = 12; // 12 PM = 12:00 (24-hour)
          }
        } else {
          if (this.selectedPeriod === 0) {
            this.selectedHour = newDisplayHour; // 1-11 AM
          } else {
            this.selectedHour = newDisplayHour + 12; // 1-11 PM = 13-23
          }
        }
      }
      this.updateTimeArrays();
      this.timeOnChange(this.getResult());
    }
  
  private onPeriodChange(selectedIndex: int): void {
    // 根据periodArray内容确定selectedPeriod，而不是直接使用selectedIndex
    // 这样即使periodArray只有一个选项也能正确映射
    const selectedPeriodStr = this.periodArray[selectedIndex];
    this.selectedPeriod = selectedPeriodStr === this.formatPeriod(true) ? 0 : 1;
    if (!this.useMilitaryTime) {
      const displayHourIndex: int = this.getHourSelectedIndex();
      const displayHour: int = displayHourIndex + 1;
      if (displayHour === 12) {
        if (this.selectedPeriod === 0) {
      this.selectedHour = 0;
        } else {
      this.selectedHour = 12;
        }
      } else {
        if (this.selectedPeriod === 0) {
      this.selectedHour = displayHour;
        } else {
      this.selectedHour = displayHour + 12;
        }
      }
    }
    this.timeOnChange(this.getResult());
  }
  
  private onMinuteChange(selectedIndex: int): void {
    let startMinuteIndex: int = DatePickerConstant.MIN_MINUTE;
    if (this.selectedHour === this.startHour) {
      startMinuteIndex = this.startMinute;
    }
    this.selectedMinute = startMinuteIndex + selectedIndex;
    this.updateSecondArray();
    this.timeOnChange(this.getResult());
  }
  
  private onSecondChange(selectedIndex: int): void {
    let startSecondIndex: int = DatePickerConstant.MIN_SECOND;
    if (this.selectedHour === this.startHour && this.selectedMinute === this.startMinute) {
      startSecondIndex = this.startSecond;
    }
    this.selectedSecond = startSecondIndex + selectedIndex;
    this.timeOnChange(this.getResult());
  }
  
  private updateTimeArrays(): void {
    this.minuteArray = [];
    let startMinuteIndex: int = DatePickerConstant.MIN_MINUTE;
    let endMinuteIndex: int = DatePickerConstant.MAX_MINUTE;
    
    if (this.selectedHour === this.startHour) {
      startMinuteIndex = this.startMinute;
    }
    if (this.selectedHour === this.endHour) {
      endMinuteIndex = this.endMinute;
    }
    
    for (let i: int = startMinuteIndex; i <= endMinuteIndex; i++) {
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
  
  private updateSecondArray(): void {
    this.secondArray = [];
    let startSecondIndex: int = DatePickerConstant.MIN_SECOND;
    let endSecondIndex: int = DatePickerConstant.MAX_SECOND;
    
    if (this.selectedHour === this.startHour && this.selectedMinute === this.startMinute) {
      startSecondIndex = this.startSecond;
    }
    if (this.selectedHour === this.endHour && this.selectedMinute === this.endMinute) {
      endSecondIndex = this.endSecond;
    }
    
    for (let i: int = startSecondIndex; i <= endSecondIndex; i++) {
      this.secondArray.push(this.formatSecond(i));
    }
    
    if (this.selectedSecond < startSecondIndex) {
      this.selectedSecond = startSecondIndex;
    }
    if (this.selectedSecond > endSecondIndex) {
      this.selectedSecond = endSecondIndex;
    }
  }
  
  private updateDaysArray(): void {
    if (this.lunar) {
      const lunarDays: int = this.getLunarDaysInMonth(this.selectedYear, this.selectedMonth);
      if (this.selectedDay > lunarDays) {
        this.selectedDay = lunarDays;
      }
      this.initLunarDayArray();
    } else {
      const daysInMonth: int = this.getDaysInMonth(this.selectedYear, this.selectedMonth);
      
      // Determine the valid day range based on selected year and month
      let startDayIndex: int = DatePickerConstant.MIN_DAY;
      let endDayIndex: int = daysInMonth;
      
      if (this.selectedYear === this.startYear && this.selectedMonth === this.startMonth) {
        startDayIndex = this.startDay;
      }
      if (this.selectedYear === this.endYear && this.selectedMonth === this.endMonth) {
        endDayIndex = Math.min(this.endDay, daysInMonth).toInt();
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
  
  private getYearSelectedIndex(): int {
    return this.selectedYear - this.startYear;
  }
  
  private getMonthSelectedIndex(): int {
    let startMonthIndex: int = DatePickerConstant.MIN_MONTH;
    if (this.selectedYear === this.startYear) {
      startMonthIndex = this.startMonth;
    }
    return this.selectedMonth - startMonthIndex;
  }
  
  private getDaySelectedIndex(): int {
    let startDayIndex: int = DatePickerConstant.MIN_DAY;
    if (this.selectedYear === this.startYear && this.selectedMonth === this.startMonth) {
      startDayIndex = this.startDay;
    }
    return this.selectedDay - startDayIndex;
  }
  
  private getHourSelectedIndex(): int {
    if (this.useMilitaryTime) {
      return this.selectedHour - this.startHour;
    } else {
      // Convert selectedHour to display hour (1-12)
      const displayHour: int = this.selectedHour === 0 || this.selectedHour === 12 ? 12 : 
                              (this.selectedHour > 12 ? this.selectedHour - 12 : this.selectedHour);
      
      // Find the index of displayHour in hourArray
      const displayHourStr: string = displayHour.toString().padStart(2, '0');
      let index: int = 0;
      for (let i: int = 0; i < this.hourArray.length; i++) {
        if (this.hourArray[i] === displayHourStr) {
          index = i;
          break;
        }
      }
      
      return index;
    }
  }
  
  private getMinuteSelectedIndex(): int {
    let startMinuteIndex: int = DatePickerConstant.MIN_MINUTE;
    if (this.selectedHour === this.startHour) {
      startMinuteIndex = this.startMinute;
    }
    return this.selectedMinute - startMinuteIndex;
  }
  
  private getSecondSelectedIndex(): int {
    let startSecondIndex: int = DatePickerConstant.MIN_SECOND;
    if (this.selectedHour === this.startHour && this.selectedMinute === this.startMinute) {
      startSecondIndex = this.startSecond;
    }
    return this.selectedSecond - startSecondIndex;
  }
  
  private isRTL(): boolean {
    return i18n.isRTL(this.localeID) ?? false;
  }
  
  private getFirstPickerIndicator(radius: int = 20): PickerIndicatorStyle {
    if (this.isRTL()) {
      return {
        type: PickerIndicatorType.BACKGROUND,
        borderRadius: {
          topLeft: 0,
          topRight: radius,
          bottomLeft: 0,
          bottomRight: radius
        } as BorderRadiuses
      };
    }
    return {
      type: PickerIndicatorType.BACKGROUND,
      borderRadius: {
        topLeft: radius,
        topRight: 0,
        bottomLeft: radius,
        bottomRight: 0
      } as BorderRadiuses
    };
  }
  
  private getMiddlePickerIndicator(): PickerIndicatorStyle {
    return {
      type: PickerIndicatorType.BACKGROUND,
      borderRadius: {
        topLeft: 0,
        topRight: 0,
        bottomLeft: 0,
        bottomRight: 0
      } as BorderRadiuses
    };
  }
  
  private getLastPickerIndicator(radius: int = 20): PickerIndicatorStyle {
    if (this.isRTL()) {
      return {
        type: PickerIndicatorType.BACKGROUND,
        borderRadius: {
          topLeft: radius,
          topRight: 0,
          bottomLeft: radius,
          bottomRight: 0
        } as BorderRadiuses
      };
    }
    return {
      type: PickerIndicatorType.BACKGROUND,
      borderRadius: {
        topLeft: 0,
        topRight: radius,
        bottomLeft: 0,
        bottomRight: radius
      } as BorderRadiuses
    };
  }
  
  build(): void {
    Row() {
      if (this.displayMode === DisplayMode.DATE || this.displayMode === DisplayMode.DATE_TIME) {
        if (this.dateMode === DateMode.DATE) {
          UIPickerComponent({ selectedIndex: this.getYearSelectedIndex() }) {
            ForEach(this.yearArray, (item: string) => {
              Text(item)
                .maxLines(1)
                .maxFontSize('16vp')
                .minFontSize('14vp')
                .textOverflow({ overflow: TextOverflow.Clip })
            })
          }
          .width(this.displayMode === DisplayMode.DATE_TIME ? '17%' : '34%')
          .height(200)
          .canLoop(this.dateCanLoop)
          .enableHapticFeedback(this.dateHapticFeedback)
          .selectionIndicator(this.getFirstPickerIndicator())
          .onChange((selectedIndex: int) => {
            this.onYearChange(selectedIndex);
          })
          .onScrollStop((selectedIndex: int) => {
            this.selectedYear = this.startYear + selectedIndex;
            this.updateDaysArray();
            this.dateOnScrollStop(this.getResult());
          })
          
          UIPickerComponent({ selectedIndex: this.getMonthSelectedIndex() }) {
            ForEach(this.monthArray, (item: string) => {
              Text(item)
                .maxLines(1)
                .maxFontSize('16vp')
                .minFontSize('14vp')
                .textOverflow({ overflow: TextOverflow.Clip })
            })
          }
          .width(this.displayMode === DisplayMode.DATE_TIME ? '16%' : '33%')
          .height(200)
          .canLoop(this.dateCanLoop)
          .enableHapticFeedback(this.dateHapticFeedback)
          .selectionIndicator(this.getMiddlePickerIndicator())
          .onChange((selectedIndex: int) => {
            this.onMonthChange(selectedIndex);
          })
          .onScrollStop((selectedIndex: int) => {
            let startMonthIndex: int = DatePickerConstant.MIN_MONTH;
            if (this.selectedYear === this.startYear) {
              startMonthIndex = this.startMonth;
            }
            this.selectedMonth = startMonthIndex + selectedIndex;
            this.dateOnScrollStop(this.getResult());
          })
          
          UIPickerComponent({ selectedIndex: this.getDaySelectedIndex() }) {
            ForEach(this.dayArray, (item: string) => {
              Text(item)
                .maxLines(1)
                .maxFontSize('16vp')
                .minFontSize('14vp')
                .textOverflow({ overflow: TextOverflow.Clip })
            })
          }
          .width(this.displayMode === DisplayMode.DATE_TIME ? '17%' : '33%')
          .height(200)
          .canLoop(this.dateCanLoop)
          .enableHapticFeedback(this.dateHapticFeedback)
          .selectionIndicator(this.displayMode === DisplayMode.DATE_TIME ? this.getMiddlePickerIndicator() : this.getLastPickerIndicator())
          .onChange((selectedIndex: int) => {
            this.onDayChange(selectedIndex);
          })
          .onScrollStop((selectedIndex: int) => {
            let startDayIndex: int = DatePickerConstant.MIN_DAY;
            if (this.selectedYear === this.startYear && this.selectedMonth === this.startMonth) {
              startDayIndex = this.startDay;
            }
            this.selectedDay = startDayIndex + selectedIndex;
            this.dateOnScrollStop(this.getResult());
          })
        } else if (this.dateMode === DateMode.YEAR_AND_MONTH) {
          UIPickerComponent({ selectedIndex: this.getYearSelectedIndex() }) {
            ForEach(this.yearArray, (item: string) => {
              Text(item)
                .maxLines(1)
                .maxFontSize('16vp')
                .minFontSize('14vp')
                .textOverflow({ overflow: TextOverflow.Clip })
            })
          }
          .width(this.displayMode === DisplayMode.DATE_TIME ? '25%' : '50%')
          .height(200)
          .canLoop(this.dateCanLoop)
          .enableHapticFeedback(this.dateHapticFeedback)
          .selectionIndicator(this.getFirstPickerIndicator())
          .onChange((selectedIndex: int) => {
            this.onYearChange(selectedIndex);
          })
          .onScrollStop((selectedIndex: int) => {
            this.selectedYear = this.startYear + selectedIndex;
            this.updateDaysArray();
            this.dateOnScrollStop(this.getResult());
          })
          
          UIPickerComponent({ selectedIndex: this.getMonthSelectedIndex() }) {
            ForEach(this.monthArray, (item: string) => {
              Text(item)
                .maxLines(1)
                .maxFontSize('16vp')
                .minFontSize('14vp')
                .textOverflow({ overflow: TextOverflow.Clip })
            })
          }
          .width(this.displayMode === DisplayMode.DATE_TIME ? '25%' : '50%')
          .height(200)
          .canLoop(this.dateCanLoop)
          .enableHapticFeedback(this.dateHapticFeedback)
          .selectionIndicator(this.displayMode === DisplayMode.DATE_TIME ? this.getMiddlePickerIndicator() : this.getLastPickerIndicator())
          .onChange((selectedIndex: int) => {
            this.onMonthChange(selectedIndex);
          })
          .onScrollStop((selectedIndex: int) => {
            let startMonthIndex: int = DatePickerConstant.MIN_MONTH;
            if (this.selectedYear === this.startYear) {
              startMonthIndex = this.startMonth;
            }
            this.selectedMonth = startMonthIndex + selectedIndex;
            this.dateOnScrollStop(this.getResult());
          })
        } else if (this.dateMode === DateMode.MONTH_AND_DAY) {
          UIPickerComponent({ selectedIndex: this.getMonthSelectedIndex() }) {
            ForEach(this.monthArray, (item: string) => {
              Text(item)
                .maxLines(1)
                .maxFontSize('16vp')
                .minFontSize('14vp')
                .textOverflow({ overflow: TextOverflow.Clip })
            })
          }
          .width(this.displayMode === DisplayMode.DATE_TIME ? '25%' : '50%')
          .height(200)
          .canLoop(this.dateCanLoop)
          .enableHapticFeedback(this.dateHapticFeedback)
          .selectionIndicator(this.getFirstPickerIndicator())
          .onChange((selectedIndex: int) => {
            this.onMonthChange(selectedIndex);
          })
          .onScrollStop((selectedIndex: int) => {
            let startMonthIndex: int = DatePickerConstant.MIN_MONTH;
            if (this.selectedYear === this.startYear) {
              startMonthIndex = this.startMonth;
            }
            this.selectedMonth = startMonthIndex + selectedIndex;
            this.dateOnScrollStop(this.getResult());
          })
          
          UIPickerComponent({ selectedIndex: this.getDaySelectedIndex() }) {
            ForEach(this.dayArray, (item: string) => {
              Text(item)
                .maxLines(1)
                .maxFontSize('16vp')
                .minFontSize('14vp')
                .textOverflow({ overflow: TextOverflow.Clip })
            })
          }
          .width(this.displayMode === DisplayMode.DATE_TIME ? '25%' : '50%')
          .height(200)
          .canLoop(this.dateCanLoop)
          .enableHapticFeedback(this.dateHapticFeedback)
          .selectionIndicator(this.displayMode === DisplayMode.DATE_TIME ? this.getMiddlePickerIndicator() : this.getLastPickerIndicator())
          .onChange((selectedIndex: int) => {
            this.onDayChange(selectedIndex);
          })
          .onScrollStop((selectedIndex: int) => {
            let startDayIndex: int = DatePickerConstant.MIN_DAY;
            if (this.selectedYear === this.startYear && this.selectedMonth === this.startMonth) {
              startDayIndex = this.startDay;
            }
            this.selectedDay = startDayIndex + selectedIndex;
            this.dateOnScrollStop(this.getResult());
          })
        }
      }
      
      if (this.displayMode === DisplayMode.TIME || this.displayMode === DisplayMode.DATE_TIME) {
        if (this.timeFormat === TimeFormat.HOUR_MINUTE) {
          if (this.useMilitaryTime) {
            UIPickerComponent({ selectedIndex: this.getHourSelectedIndex() }) {
              ForEach(this.hourArray, (item: string) => {
                Text(item)
                  .maxLines(1)
                  .maxFontSize('16vp')
                  .minFontSize('14vp')
                  .textOverflow({ overflow: TextOverflow.Clip })
              })
            }
            .width(this.displayMode === DisplayMode.DATE_TIME ? '25%' : '50%')
            .height(200)
            .canLoop(this.timeCanLoop)
            .enableHapticFeedback(this.timeHapticFeedback)
            .selectionIndicator(this.displayMode === DisplayMode.DATE_TIME ? this.getMiddlePickerIndicator() : this.getFirstPickerIndicator())
            .onChange((selectedIndex: int) => {
              this.onHourChange(selectedIndex);
            })
            .onScrollStop((selectedIndex: int) => {
              this.selectedHour = this.startHour + selectedIndex;
              this.updateTimeArrays();
              this.timeOnScrollStop(this.getResult());
            })
            
            UIPickerComponent({ selectedIndex: this.getMinuteSelectedIndex() }) {
              ForEach(this.minuteArray, (item: string) => {
                Text(item)
                  .maxLines(1)
                  .maxFontSize('16vp')
                  .minFontSize('14vp')
                  .textOverflow({ overflow: TextOverflow.Clip })
              })
            }
            .width(this.displayMode === DisplayMode.DATE_TIME ? '25%' : '50%')
            .height(200)
            .canLoop(this.timeCanLoop)
            .enableHapticFeedback(this.timeHapticFeedback)
            .selectionIndicator(this.getLastPickerIndicator())
            .onChange((selectedIndex: int) => {
              this.onMinuteChange(selectedIndex);
            })
            .onScrollStop((selectedIndex: int) => {
              let startMinuteIndex: int = DatePickerConstant.MIN_MINUTE;
              if (this.selectedHour === this.startHour) {
                startMinuteIndex = this.startMinute;
              }
              this.selectedMinute = startMinuteIndex + selectedIndex;
              this.updateSecondArray();
              this.timeOnScrollStop(this.getResult());
            })
          } else {
            UIPickerComponent({ selectedIndex: this.selectedPeriod }) {
              ForEach(this.periodArray, (item: string) => {
                Text(item)
                  .maxLines(1)
                  .maxFontSize('16vp')
                  .minFontSize('14vp')
                  .textOverflow({ overflow: TextOverflow.Clip })
              })
            }
            .width(this.displayMode === DisplayMode.DATE_TIME ? '17%' : '33%')
            .height(200)
            .canLoop(false)
            .enableHapticFeedback(this.timeHapticFeedback)
            .selectionIndicator(this.displayMode === DisplayMode.DATE_TIME ? this.getMiddlePickerIndicator() : this.getFirstPickerIndicator())
            .onChange((selectedIndex: int) => {
              this.onPeriodChange(selectedIndex);
            })
            .onScrollStop((selectedIndex: int) => {
              this.selectedPeriod = selectedIndex;
              this.timeOnScrollStop(this.getResult());
            })
            
            UIPickerComponent({ selectedIndex: this.getHourSelectedIndex() }) {
              ForEach(this.hourArray, (item: string) => {
                Text(item)
                  .maxLines(1)
                  .maxFontSize('16vp')
                  .minFontSize('14vp')
                  .textOverflow({ overflow: TextOverflow.Clip })
              })
            }
            .width(this.displayMode === DisplayMode.DATE_TIME ? '16%' : '34%')
            .height(200)
            .canLoop(this.timeCanLoop)
            .enableHapticFeedback(this.timeHapticFeedback)
            .selectionIndicator(this.getMiddlePickerIndicator())
            .onChange((selectedIndex: int) => {
              this.onHourChange(selectedIndex);
            })
            .onScrollStop((selectedIndex: int) => {
              this.onHourChange(selectedIndex);
              this.timeOnScrollStop(this.getResult());
            })
            
            UIPickerComponent({ selectedIndex: this.getMinuteSelectedIndex() }) {
              ForEach(this.minuteArray, (item: string) => {
                Text(item)
                  .maxLines(1)
                  .maxFontSize('16vp')
                  .minFontSize('14vp')
                  .textOverflow({ overflow: TextOverflow.Clip })
              })
            }
            .width(this.displayMode === DisplayMode.DATE_TIME ? '17%' : '33%')
            .height(200)
            .canLoop(this.timeCanLoop)
            .enableHapticFeedback(this.timeHapticFeedback)
            .selectionIndicator(this.getLastPickerIndicator())
            .onChange((selectedIndex: int) => {
              this.onMinuteChange(selectedIndex);
            })
            .onScrollStop((selectedIndex: int) => {
              let startMinuteIndex: int = DatePickerConstant.MIN_MINUTE;
              if (this.selectedHour === this.startHour) {
                startMinuteIndex = this.startMinute;
              }
              this.selectedMinute = startMinuteIndex + selectedIndex;
              this.updateSecondArray();
              this.timeOnScrollStop(this.getResult());
            })
          }
        } else if (this.timeFormat === TimeFormat.HOUR_MINUTE_SECOND) {
          if (this.useMilitaryTime) {
            UIPickerComponent({ selectedIndex: this.getHourSelectedIndex() }) {
              ForEach(this.hourArray, (item: string) => {
                Text(item)
                  .maxLines(1)
                  .maxFontSize('16vp')
                  .minFontSize('14vp')
                  .textOverflow({ overflow: TextOverflow.Clip })
              })
            }
            .width(this.displayMode === DisplayMode.DATE_TIME ? '17%' : '34%')
            .height(200)
            .canLoop(this.timeCanLoop)
            .enableHapticFeedback(this.timeHapticFeedback)
            .selectionIndicator(this.displayMode === DisplayMode.DATE_TIME ? this.getMiddlePickerIndicator() : this.getFirstPickerIndicator())
            .onChange((selectedIndex: int) => {
              this.onHourChange(selectedIndex);
            })
            .onScrollStop((selectedIndex: int) => {
              this.selectedHour = this.startHour + selectedIndex;
              this.updateTimeArrays();
              this.timeOnScrollStop(this.getResult());
            })
            
            UIPickerComponent({ selectedIndex: this.getMinuteSelectedIndex() }) {
              ForEach(this.minuteArray, (item: string) => {
                Text(item)
                  .maxLines(1)
                  .maxFontSize('16vp')
                  .minFontSize('14vp')
                  .textOverflow({ overflow: TextOverflow.Clip })
              })
            }
            .width(this.displayMode === DisplayMode.DATE_TIME ? '16%' : '33%')
            .height(200)
            .canLoop(this.timeCanLoop)
            .enableHapticFeedback(this.timeHapticFeedback)
            .selectionIndicator(this.getMiddlePickerIndicator())
            .onChange((selectedIndex: int) => {
              this.onMinuteChange(selectedIndex);
            })
            .onScrollStop((selectedIndex: int) => {
              let startMinuteIndex: int = DatePickerConstant.MIN_MINUTE;
              if (this.selectedHour === this.startHour) {
                startMinuteIndex = this.startMinute;
              }
              this.selectedMinute = startMinuteIndex + selectedIndex;
              this.updateSecondArray();
              this.timeOnScrollStop(this.getResult());
            })
            
            UIPickerComponent({ selectedIndex: this.getSecondSelectedIndex() }) {
              ForEach(this.secondArray, (item: string) => {
                Text(item)
                  .maxLines(1)
                  .maxFontSize('16vp')
                  .minFontSize('14vp')
                  .textOverflow({ overflow: TextOverflow.Clip })
              })
            }
            .width(this.displayMode === DisplayMode.DATE_TIME ? '17%' : '33%')
            .height(200)
            .canLoop(this.timeCanLoop)
            .enableHapticFeedback(this.timeHapticFeedback)
            .selectionIndicator(this.getLastPickerIndicator())
            .onChange((selectedIndex: int) => {
              this.onSecondChange(selectedIndex);
            })
            .onScrollStop((selectedIndex: int) => {
              let startSecondIndex: int = DatePickerConstant.MIN_SECOND;
              if (this.selectedHour === this.startHour && this.selectedMinute === this.startMinute) {
                startSecondIndex = this.startSecond;
              }
              this.selectedSecond = startSecondIndex + selectedIndex;
              this.timeOnScrollStop(this.getResult());
            })
          } else {
            UIPickerComponent({ selectedIndex: this.selectedPeriod }) {
              ForEach(this.periodArray, (item: string) => {
                Text(item)
                  .maxLines(1)
                  .maxFontSize('16vp')
                  .minFontSize('14vp')
                  .textOverflow({ overflow: TextOverflow.Clip })
              })
            }
            .width(this.displayMode === DisplayMode.DATE_TIME ? '12%' : '25%')
            .height(200)
            .canLoop(false)
            .enableHapticFeedback(this.timeHapticFeedback)
            .selectionIndicator(this.displayMode === DisplayMode.DATE_TIME ? this.getMiddlePickerIndicator() : this.getFirstPickerIndicator())
            .onChange((selectedIndex: int) => {
              this.onPeriodChange(selectedIndex);
            })
            .onScrollStop((selectedIndex: int) => {
              this.selectedPeriod = selectedIndex;
              this.timeOnScrollStop(this.getResult());
            })
            
            UIPickerComponent({ selectedIndex: this.getHourSelectedIndex() }) {
              ForEach(this.hourArray, (item: string) => {
                Text(item)
                  .maxLines(1)
                  .maxFontSize('16vp')
                  .minFontSize('14vp')
                  .textOverflow({ overflow: TextOverflow.Clip })
              })
            }
            .width(this.displayMode === DisplayMode.DATE_TIME ? '13%' : '25%')
            .height(200)
            .canLoop(this.timeCanLoop)
            .enableHapticFeedback(this.timeHapticFeedback)
            .selectionIndicator(this.getMiddlePickerIndicator())
            .onChange((selectedIndex: int) => {
              this.onHourChange(selectedIndex);
            })
            .onScrollStop((selectedIndex: int) => {
              this.onHourChange(selectedIndex);
              this.timeOnScrollStop(this.getResult());
            })
            
            UIPickerComponent({ selectedIndex: this.getMinuteSelectedIndex() }) {
              ForEach(this.minuteArray, (item: string) => {
                Text(item)
                  .maxLines(1)
                  .maxFontSize('16vp')
                  .minFontSize('14vp')
                  .textOverflow({ overflow: TextOverflow.Clip })
              })
            }
            .width(this.displayMode === DisplayMode.DATE_TIME ? '13%' : '25%')
            .height(200)
            .canLoop(this.timeCanLoop)
            .enableHapticFeedback(this.timeHapticFeedback)
            .selectionIndicator(this.getMiddlePickerIndicator())
            .onChange((selectedIndex: int) => {
              this.onMinuteChange(selectedIndex);
            })
            .onScrollStop((selectedIndex: int) => {
              let startMinuteIndex: int = DatePickerConstant.MIN_MINUTE;
              if (this.selectedHour === this.startHour) {
                startMinuteIndex = this.startMinute;
              }
              this.selectedMinute = startMinuteIndex + selectedIndex;
              this.updateSecondArray();
              this.timeOnScrollStop(this.getResult());
            })
            
            UIPickerComponent({ selectedIndex: this.getSecondSelectedIndex() }) {
              ForEach(this.secondArray, (item: string) => {
                Text(item)
                  .maxLines(1)
                  .maxFontSize('16vp')
                  .minFontSize('14vp')
                  .textOverflow({ overflow: TextOverflow.Clip })
              })
            }
            .width(this.displayMode === DisplayMode.DATE_TIME ? '12%' : '25%')
            .height(200)
            .canLoop(this.timeCanLoop)
            .enableHapticFeedback(this.timeHapticFeedback)
            .selectionIndicator(this.getLastPickerIndicator())
            .onChange((selectedIndex: int) => {
              this.onSecondChange(selectedIndex);
            })
            .onScrollStop((selectedIndex: int) => {
              let startSecondIndex: int = DatePickerConstant.MIN_SECOND;
              if (this.selectedHour === this.startHour && this.selectedMinute === this.startMinute) {
                startSecondIndex = this.startSecond;
              }
              this.selectedSecond = startSecondIndex + selectedIndex;
              this.timeOnScrollStop(this.getResult());
            })
          }
        }
      }
    }
    .width('100%')
  }
}
