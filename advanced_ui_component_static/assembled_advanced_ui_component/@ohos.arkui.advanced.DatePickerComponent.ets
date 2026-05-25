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
import { State } from '@ohos.arkui.stateManagement';
import { LengthMetrics } from '@ohos.arkui.node';
import { intl } from '@kit.LocalizationKit';
import i18n from '@ohos.i18n';

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
}

@Component
export struct DatePickerComponent {
  options: DatePickerComponentOptions = new DatePickerComponentOptions();
  @State displayMode: DisplayMode = DisplayMode.DATE;
  @State selectedYear: int = 0;
  @State selectedMonth: int = 0;
  @State selectedDay: int = 0;
  @State selectedHour: int = 0;
  @State selectedMinute: int = 0;
  @State selectedSecond: int = 0;
  @State startYear: int = DatePickerConstant.DEFAULT_START_YEAR;
  @State endYear: int = DatePickerConstant.DEFAULT_END_YEAR;
  @State dateMode: DateMode = DateMode.DATE;
  @State timeFormat: TimeFormat = TimeFormat.HOUR_MINUTE;
  @State useMilitaryTime: boolean = false;
  @State lunar: boolean = false;
  @State canLoop: boolean = true;
  @State hapticFeedback: boolean = true;
  @State yearArray: Array<string> = new Array<string>();
  @State monthArray: Array<string> = new Array<string>();
  @State dayArray: Array<string> = new Array<string>();
  @State hourArray: Array<string> = new Array<string>();
  @State minuteArray: Array<string> = new Array<string>();
  @State secondArray: Array<string> = new Array<string>();
  @State periodArray: Array<string> = new Array<string>();
  @State selectedPeriod: int = 0;
  @State currentLocale: string = '';
  private onChange: Callback<DatePickerComponentResult> = noop;
  private onScrollStop: Callback<DatePickerComponentResult> = noop;
  private localeID: string = '';
  private initFlag: boolean = true;
  private lunarCalendar: i18n.Calendar | null = null;
  
  aboutToAppear(): void {
    const locale = i18n.System.getSystemLocaleInstance();
    this.localeID = locale.toString();
    this.currentLocale = i18n.System.getSystemLanguage();
  
    if (this.selectedYear === 0 || this.selectedMonth === 0 || this.selectedDay === 0) {
      const now = new Date();
      this.selectedYear = now.getFullYear() as int;
      this.selectedMonth = now.getMonth() as int;
      this.selectedDay = now.getDate() as int;
      this.selectedHour = now.getHours() as int;
      this.selectedMinute = now.getMinutes() as int;
      this.selectedSecond = now.getSeconds() as int;
    }
  
    if (this.lunar) {
      this.lunarCalendar = i18n.getCalendar(this.localeID, 'chinese');
    }
  
    if (this.options !== undefined && this.options !== null) {
      this.onOptionsChange();
    } else {
      this.initArrays();
    }
  }
  
  aboutToDisappear(): void {
    this.lunarCalendar = null;
  }
  
  private onLocaleChange(): void {
    const locale = i18n.System.getSystemLocaleInstance();
    this.localeID = locale.toString();
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
      return 30 as int;
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
    
      return 30 as int;
    } catch (e) {
      return 30 as int;
    }
  }
  
  private formatLunarYear(gregorianYear: int): string {
    return gregorianYear + '年';
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
      const idx: int = (day - 1) as int;
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
    for (let i: int = DatePickerConstant.MIN_MONTH; i <= DatePickerConstant.MAX_MONTH; i++) {
      this.monthArray.push(this.formatMonth(i));
    }
  }
  
  private initDayArray(): void {
    this.dayArray = [];
    const daysInMonth: int = this.getDaysInMonth(this.selectedYear, this.selectedMonth);
    for (let i: int = DatePickerConstant.MIN_DAY; i <= daysInMonth; i++) {
      this.dayArray.push(this.formatDay(i));
    }
  }
  
  private initTimeArrays(): void {
    this.hourArray = [];
    if (this.useMilitaryTime) {
      for (let i: int = DatePickerConstant.MIN_HOUR; i <= DatePickerConstant.MAX_HOUR; i++) {
        this.hourArray.push(this.formatNumber(i));
      }
    } else {
      for (let i: int = 1; i <= 12; i++) {
        this.hourArray.push(this.formatNumber(i));
      }
    }
  
    this.minuteArray = [];
    for (let i: int = DatePickerConstant.MIN_MINUTE; i <= DatePickerConstant.MAX_MINUTE; i++) {
      this.minuteArray.push(this.formatMinute(i));
    }
  
    this.secondArray = [];
    for (let i: int = DatePickerConstant.MIN_SECOND; i <= DatePickerConstant.MAX_SECOND; i++) {
      this.secondArray.push(this.formatSecond(i));
    }
  
    this.periodArray = [];
    if (!this.useMilitaryTime) {
      this.periodArray.push(this.formatPeriod(true));
      this.periodArray.push(this.formatPeriod(false));
      this.selectedPeriod = this.selectedHour < 12 ? 0 as int : 1 as int;
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
      return year + '年';
    }
    return String(year);
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
      return day + '日';
    }
  
    try {
      const localeStr: string = this.localeID;
      if (!localeStr || localeStr.length === 0) {
        return String(day);
      }
    
      const dateFormat = new intl.DateTimeFormat(localeStr, {
        day: 'numeric'
      });
      const safeDay: int = Math.max(1, Math.min(31, day)).toInt();
      const date = new Date(2026, 0, safeDay);
      return dateFormat.format(date);
    } catch (error) {
      return String(day);
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
      return isLeapYear ? 29 as int : 28 as int;
    }
  
    for (let i: int = 0; i < monthsWith31Days.length; i++) {
      if (monthsWith31Days[i] === month) {
        return 31 as int;
      }
    }
  
    for (let i: int = 0; i < monthsWith30Days.length; i++) {
      if (monthsWith30Days[i] === month) {
        return 30 as int;
      }
    }
  
    return 30 as int;
  }
  
  private onOptionsChange(): void {
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
      this.canLoop = dateOptions.loop!;
    }
  
    if (dateOptions.enableHapticFeedback !== undefined) {
      this.hapticFeedback = dateOptions.enableHapticFeedback!;
    }
  
    if (dateOptions.start !== undefined && dateOptions.start !== null) {
      const year: int = dateOptions.start!.getFullYear() as int;
      this.startYear = Math.max(DatePickerConstant.MIN_YEAR, Math.min(DatePickerConstant.MAX_YEAR, year)).toInt();
    }
  
    if (dateOptions.end !== undefined && dateOptions.end !== null) {
      const year: int = dateOptions.end!.getFullYear() as int;
      this.endYear = Math.max(DatePickerConstant.MIN_YEAR, Math.min(DatePickerConstant.MAX_YEAR, year)).toInt();
    }
  
    if (this.startYear > this.endYear) {
      const temp: int = this.startYear;
      this.startYear = this.endYear;
      this.endYear = temp;
    }
  
    if (dateOptions.selected !== undefined && dateOptions.selected !== null) {
      if (this.initFlag) {
        this.initFlag = false;
        if (this.lunar && this.lunarCalendar !== null) {
          this.lunarCalendar!.setTime(dateOptions.selected!);
          const lunarMonth: int = this.lunarCalendar!.get('month');
          const lunarDay: int = this.lunarCalendar!.get('date');
        
          // 直接使用Date对象的公历年份，不需要通过干支纪年反推
          // lunarCalendar.get('year')返回的是干支纪年(1-60循环)，无法准确反推公历年份
          this.selectedYear = dateOptions.selected!.getFullYear() as int;
          this.selectedMonth = lunarMonth;
          this.selectedDay = lunarDay;
        } else {
          this.selectedYear = dateOptions.selected!.getFullYear() as int;
          this.selectedMonth = dateOptions.selected!.getMonth() as int;
          this.selectedDay = dateOptions.selected!.getDate() as int;
        }
      }
    } else {
      if (this.initFlag) {
        this.initFlag = false;
        const now = new Date();
        if (this.lunar && this.lunarCalendar !== null) {
          this.lunarCalendar!.setTime(now);
          const lunarMonth: int = this.lunarCalendar!.get('month');
          const lunarDay: int = this.lunarCalendar!.get('date');
        
          // 直接使用Date对象的公历年份
          this.selectedYear = now.getFullYear() as int;
          this.selectedMonth = lunarMonth;
          this.selectedDay = lunarDay;
        } else {
          this.selectedYear = now.getFullYear() as int;
          this.selectedMonth = now.getMonth() as int;
          this.selectedDay = now.getDate() as int;
        }
      }
    }
  
    if (dateOptions.onChange !== undefined) {
      this.onChange = dateOptions.onChange ?? noop;
    }
  
    if (dateOptions.onScrollStop !== undefined) {
      this.onScrollStop = dateOptions.onScrollStop ?? noop;
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
      this.canLoop = timeOptions.loop!;
    }
  
    if (timeOptions.enableHapticFeedback !== undefined) {
      this.hapticFeedback = timeOptions.enableHapticFeedback!;
    }
  
    if (timeOptions.selected !== undefined && timeOptions.selected !== null) {
      if (this.initFlag) {
        this.initFlag = false;
        this.selectedHour = timeOptions.selected!.getHours() as int;
        this.selectedMinute = timeOptions.selected!.getMinutes() as int;
        this.selectedSecond = timeOptions.selected!.getSeconds() as int;
      }
    } else {
      if (this.initFlag) {
        this.initFlag = false;
        const now = new Date();
        this.selectedHour = now.getHours() as int;
        this.selectedMinute = now.getMinutes() as int;
        this.selectedSecond = now.getSeconds() as int;
      }
    }
  
    if (timeOptions.onChange !== undefined) {
      this.onChange = timeOptions.onChange ?? noop;
    }
  
    if (timeOptions.onScrollStop !== undefined) {
      this.onScrollStop = timeOptions.onScrollStop ?? noop;
    }
  }
  
  private getResult(): DatePickerComponentResult {
    const result = new DatePickerComponentResult();
  
    result.year = this.selectedYear;
    result.month = this.selectedMonth;
    result.day = this.selectedDay;
  
    if (!this.useMilitaryTime) {
      if (this.selectedHour === 0) {
        result.hour = 12;
      } else if (this.selectedHour === 12) {
        result.hour = 12;
      } else if (this.selectedHour > 12) {
        result.hour = this.selectedHour - 12;
      } else {
        result.hour = this.selectedHour;
      }
    } else {
      result.hour = this.selectedHour;
    }
  
    result.minute = this.selectedMinute;
    result.second = this.selectedSecond;
    return result;
  }
  
  private onYearChange(selectedIndex: int): void {
    this.selectedYear = this.startYear + selectedIndex;
    this.updateDaysArray();
    this.onChange(this.getResult());
  }
  
  private onMonthChange(selectedIndex: int): void {
    this.selectedMonth = selectedIndex;
    this.updateDaysArray();
    this.onChange(this.getResult());
  }
  
  private onDayChange(selectedIndex: int): void {
    this.selectedDay = selectedIndex + 1;
    this.onChange(this.getResult());
  }
  
private onHourChange(selectedIndex: int): void {
     if (this.useMilitaryTime) {
       this.selectedHour = selectedIndex;
     } else {
       // Detect boundary crossing: 12(index 11) → 1(index 0) or 1(index 0) → 12(index 11)
       const oldDisplayIndex: int = this.getHourSelectedIndex();
       const crossingBoundary: boolean = (oldDisplayIndex === 11 && selectedIndex === 0) || 
                                   (oldDisplayIndex === 0 && selectedIndex === 11);
       
       // Auto-switch period when crossing boundary
       if (crossingBoundary) {
         this.selectedPeriod = this.selectedPeriod === 0 ? 1 : 0;
       }
       
       const displayHour: int = selectedIndex + 1;
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
     this.onChange(this.getResult());
   }
  
  private onPeriodChange(selectedIndex: int): void {
    this.selectedPeriod = selectedIndex;
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
    this.onChange(this.getResult());
  }
  
  private onMinuteChange(selectedIndex: int): void {
    this.selectedMinute = selectedIndex;
    this.onChange(this.getResult());
  }
  
  private onSecondChange(selectedIndex: int): void {
    this.selectedSecond = selectedIndex;
    this.onChange(this.getResult());
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
      if (this.selectedDay > daysInMonth) {
        this.selectedDay = daysInMonth;
      }
      this.initDayArray();
    }
  }
  
  private getYearSelectedIndex(): int {
    return this.selectedYear - this.startYear;
  }
  
  private getMonthSelectedIndex(): int {
    return this.selectedMonth;
  }
  
  private getDaySelectedIndex(): int {
    return this.selectedDay - 1;
  }
  
  private getHourSelectedIndex(): int {
    if (this.useMilitaryTime) {
      return this.selectedHour;
    } else {
      if (this.selectedHour === 0) {
        return 11;
      } else if (this.selectedHour === 12) {
        return 11;
      } else if (this.selectedHour > 12) {
        return this.selectedHour - 13;
      } else {
        return this.selectedHour - 1;
      }
    }
  }
  
  private getPeriodSelectedIndex(): int {
    return this.selectedPeriod;
  }
  
  private getMinuteSelectedIndex(): int {
    return this.selectedMinute;
  }
  
  private getSecondSelectedIndex(): int {
    return this.selectedSecond;
  }
  
  private getFirstPickerIndicator(radius: int = 20): PickerIndicatorStyle {
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
  
  private callOnChange(): void {
    this.onChange(this.getResult());
  }
  
  private callOnScrollStop(): void {
    this.onScrollStop(this.getResult());
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
      .canLoop(this.canLoop)
      .enableHapticFeedback(this.hapticFeedback)
      .selectionIndicator(this.getFirstPickerIndicator())
      .onChange((selectedIndex: int) => {
        this.onYearChange(selectedIndex);
      })
      .onScrollStop((selectedIndex: int) => {
        this.selectedYear = this.startYear + selectedIndex;
        this.updateDaysArray();
        this.callOnScrollStop();
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
      .canLoop(this.canLoop)
      .enableHapticFeedback(this.hapticFeedback)
      .selectionIndicator(this.getMiddlePickerIndicator())
      .onChange((selectedIndex: int) => {
        this.onMonthChange(selectedIndex);
      })
      .onScrollStop((selectedIndex: int) => {
        this.selectedMonth = selectedIndex;
        this.callOnScrollStop();
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
      .canLoop(this.canLoop)
      .enableHapticFeedback(this.hapticFeedback)
      .selectionIndicator(this.displayMode === DisplayMode.DATE_TIME ? this.getMiddlePickerIndicator() : this.getLastPickerIndicator())
      .onChange((selectedIndex: int) => {
        this.onDayChange(selectedIndex);
      })
      .onScrollStop((selectedIndex: int) => {
        this.selectedDay = selectedIndex + 1;
        this.callOnScrollStop();
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
      .canLoop(this.canLoop)
      .enableHapticFeedback(this.hapticFeedback)
      .selectionIndicator(this.getFirstPickerIndicator())
      .onChange((selectedIndex: int) => {
        this.onYearChange(selectedIndex);
      })
      .onScrollStop((selectedIndex: int) => {
        this.selectedYear = this.startYear + selectedIndex;
        this.updateDaysArray();
        this.callOnScrollStop();
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
      .canLoop(this.canLoop)
      .enableHapticFeedback(this.hapticFeedback)
      .selectionIndicator(this.displayMode === DisplayMode.DATE_TIME ? this.getMiddlePickerIndicator() : this.getLastPickerIndicator())
      .onChange((selectedIndex: int) => {
        this.onMonthChange(selectedIndex);
      })
      .onScrollStop((selectedIndex: int) => {
        this.selectedMonth = selectedIndex;
        this.callOnScrollStop();
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
      .canLoop(this.canLoop)
      .enableHapticFeedback(this.hapticFeedback)
      .selectionIndicator(this.getFirstPickerIndicator())
      .onChange((selectedIndex: int) => {
        this.onMonthChange(selectedIndex);
      })
      .onScrollStop((selectedIndex: int) => {
        this.selectedMonth = selectedIndex;
        this.callOnScrollStop();
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
      .canLoop(this.canLoop)
      .enableHapticFeedback(this.hapticFeedback)
      .selectionIndicator(this.displayMode === DisplayMode.DATE_TIME ? this.getMiddlePickerIndicator() : this.getLastPickerIndicator())
      .onChange((selectedIndex: int) => {
        this.onDayChange(selectedIndex);
      })
      .onScrollStop((selectedIndex: int) => {
        this.selectedDay = selectedIndex + 1;
        this.callOnScrollStop();
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
        .canLoop(this.canLoop)
        .enableHapticFeedback(this.hapticFeedback)
        .selectionIndicator(this.displayMode === DisplayMode.DATE_TIME ? this.getMiddlePickerIndicator() : this.getFirstPickerIndicator())
        .onChange((selectedIndex: int) => {
          this.onHourChange(selectedIndex);
        })
        .onScrollStop((selectedIndex: int) => {
          this.selectedHour = selectedIndex;
          this.callOnScrollStop();
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
        .canLoop(this.canLoop)
        .enableHapticFeedback(this.hapticFeedback)
        .selectionIndicator(this.getLastPickerIndicator())
        .onChange((selectedIndex: int) => {
          this.onMinuteChange(selectedIndex);
        })
        .onScrollStop((selectedIndex: int) => {
          this.selectedMinute = selectedIndex;
          this.callOnScrollStop();
        })
      } else {
        UIPickerComponent({ selectedIndex: this.getPeriodSelectedIndex() }) {
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
        .enableHapticFeedback(this.hapticFeedback)
        .selectionIndicator(this.displayMode === DisplayMode.DATE_TIME ? this.getMiddlePickerIndicator() : this.getFirstPickerIndicator())
        .onChange((selectedIndex: int) => {
          this.onPeriodChange(selectedIndex);
        })
        .onScrollStop((selectedIndex: int) => {
          this.selectedPeriod = selectedIndex;
          this.callOnScrollStop();
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
        .canLoop(this.canLoop)
        .enableHapticFeedback(this.hapticFeedback)
        .selectionIndicator(this.getMiddlePickerIndicator())
        .onChange((selectedIndex: int) => {
          this.onHourChange(selectedIndex);
        })
        .onScrollStop((selectedIndex: int) => {
          this.onHourChange(selectedIndex);
          this.callOnScrollStop();
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
        .canLoop(this.canLoop)
        .enableHapticFeedback(this.hapticFeedback)
        .selectionIndicator(this.getLastPickerIndicator())
        .onChange((selectedIndex: int) => {
          this.onMinuteChange(selectedIndex);
        })
        .onScrollStop((selectedIndex: int) => {
          this.selectedMinute = selectedIndex;
          this.callOnScrollStop();
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
        .canLoop(this.canLoop)
        .enableHapticFeedback(this.hapticFeedback)
        .selectionIndicator(this.displayMode === DisplayMode.DATE_TIME ? this.getMiddlePickerIndicator() : this.getFirstPickerIndicator())
        .onChange((selectedIndex: int) => {
          this.onHourChange(selectedIndex);
        })
        .onScrollStop((selectedIndex: int) => {
          this.selectedHour = selectedIndex;
          this.callOnScrollStop();
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
        .canLoop(this.canLoop)
        .enableHapticFeedback(this.hapticFeedback)
        .selectionIndicator(this.getMiddlePickerIndicator())
        .onChange((selectedIndex: int) => {
          this.onMinuteChange(selectedIndex);
        })
        .onScrollStop((selectedIndex: int) => {
          this.selectedMinute = selectedIndex;
          this.callOnScrollStop();
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
        .canLoop(this.canLoop)
        .enableHapticFeedback(this.hapticFeedback)
        .selectionIndicator(this.getLastPickerIndicator())
        .onChange((selectedIndex: int) => {
          this.onSecondChange(selectedIndex);
        })
        .onScrollStop((selectedIndex: int) => {
          this.selectedSecond = selectedIndex;
          this.callOnScrollStop();
        })
      } else {
        UIPickerComponent({ selectedIndex: this.getPeriodSelectedIndex() }) {
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
        .enableHapticFeedback(this.hapticFeedback)
        .selectionIndicator(this.displayMode === DisplayMode.DATE_TIME ? this.getMiddlePickerIndicator() : this.getFirstPickerIndicator())
        .onChange((selectedIndex: int) => {
          this.onPeriodChange(selectedIndex);
        })
        .onScrollStop((selectedIndex: int) => {
          this.selectedPeriod = selectedIndex;
          this.callOnScrollStop();
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
        .canLoop(this.canLoop)
        .enableHapticFeedback(this.hapticFeedback)
        .selectionIndicator(this.getMiddlePickerIndicator())
        .onChange((selectedIndex: int) => {
          this.onHourChange(selectedIndex);
        })
        .onScrollStop((selectedIndex: int) => {
          this.onHourChange(selectedIndex);
          this.callOnScrollStop();
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
        .canLoop(this.canLoop)
        .enableHapticFeedback(this.hapticFeedback)
        .selectionIndicator(this.getMiddlePickerIndicator())
        .onChange((selectedIndex: int) => {
          this.onMinuteChange(selectedIndex);
        })
        .onScrollStop((selectedIndex: int) => {
          this.selectedMinute = selectedIndex;
          this.callOnScrollStop();
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
        .canLoop(this.canLoop)
        .enableHapticFeedback(this.hapticFeedback)
        .selectionIndicator(this.getLastPickerIndicator())
        .onChange((selectedIndex: int) => {
          this.onSecondChange(selectedIndex);
        })
        .onScrollStop((selectedIndex: int) => {
          this.selectedSecond = selectedIndex;
          this.callOnScrollStop();
        })
      }
        }
      }
    }
    .width('100%')
  }
}