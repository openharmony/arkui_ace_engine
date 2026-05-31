/*
 * Copyright (C) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License"),
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
import { LengthMetrics } from '@ohos.arkui.node';
import { Callback } from '@ohos.base';
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
  public year?: number;
  public month?: number;
  public day?: number;
  public hour?: number;
  public minute?: number;
  public second?: number;
}

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
  public static readonly MIN_YEAR = 0;
  public static readonly MAX_YEAR = 10000;
  public static readonly DEFAULT_START_YEAR = 1970;
  public static readonly DEFAULT_END_YEAR = 2100;
  public static readonly MIN_MONTH = 0;
  public static readonly MAX_MONTH = 11;
  public static readonly MIN_DAY = 1;
  public static readonly MIN_HOUR = 0;
  public static readonly MAX_HOUR = 23;
  public static readonly MIN_MINUTE = 0;
  public static readonly MAX_MINUTE = 59;
  public static readonly MIN_SECOND = 0;
  public static readonly MAX_SECOND = 59;
  public static readonly MONTHS_IN_YEAR = 12;
  public static readonly DEFAULT_STEP = 1;
  public static readonly SYSTEM_MIN_DATE = new Date(1970, 0, 1);
  public static readonly SYSTEM_MAX_DATE = new Date(2100, 11, 31);
}

@Component
export struct DatePickerComponent {
  @Prop @Watch('onOptionsChange') options: DatePickerComponentOptions;
  @State displayMode: DisplayMode = DisplayMode.DATE;
  @State selectedYear: number = 0;
  @State selectedMonth: number = 0;
  @State selectedDay: number = 0;
  @State selectedHour: number = 0;
  @State selectedMinute: number = 0;
  @State selectedSecond: number = 0;
  @State startYear: number = DatePickerConstant.DEFAULT_START_YEAR;
  @State endYear: number = DatePickerConstant.DEFAULT_END_YEAR;
  @State startMonth: number = DatePickerConstant.MIN_MONTH;
  @State endMonth: number = DatePickerConstant.MAX_MONTH;
  @State startDay: number = DatePickerConstant.MIN_DAY;
  @State endDay: number = 31;
  @State startHour: number = DatePickerConstant.MIN_HOUR;
  @State endHour: number = DatePickerConstant.MAX_HOUR;
  @State startMinute: number = DatePickerConstant.MIN_MINUTE;
  @State endMinute: number = DatePickerConstant.MAX_MINUTE;
  @State startSecond: number = DatePickerConstant.MIN_SECOND;
  @State endSecond: number = DatePickerConstant.MAX_SECOND;
  @State dateMode: DateMode = DateMode.DATE;
  @State timeFormat: TimeFormat = TimeFormat.HOUR_MINUTE;
  @State useMilitaryTime: boolean = false;
  @State lunar: boolean = false;
  @State dateCanLoop: boolean = true;
  @State timeCanLoop: boolean = true;
  @State dateHapticFeedback: boolean = true;
  @State timeHapticFeedback: boolean = true;
  @State yearArray: string[] = [];
  @State monthArray: string[] = [];
  @State dayArray: string[] = [];
  @State hourArray: string[] = [];
  @State minuteArray: string[] = [];
  @State secondArray: string[] = [];
  @State periodArray: string[] = [];
  @State selectedPeriod: number = 0;
  private dateOnChange?: Callback<DatePickerComponentResult>;
  private dateOnScrollStop?: Callback<DatePickerComponentResult>;
  private timeOnChange?: Callback<DatePickerComponentResult>;
  private timeOnScrollStop?: Callback<DatePickerComponentResult>;
  @State @Watch('onLocaleChange') currentLocale: string = '';
  private locale: intl.Locale = new intl.Locale();
  private initFlag: boolean = true;
  private lunarCalendar: i18n.Calendar | null = null;
  
  aboutToAppear(): void {
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
    } else {
      this.initArrays();
    }
  }
  
  aboutToDisappear(): void {
    this.lunarCalendar = null;
  }
  
  private onLocaleChange(): void {
    this.locale = new intl.Locale(this.currentLocale);
    if (this.lunar) {
      this.lunarCalendar = i18n.getCalendar(this.locale.toString(), 'chinese');
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
    for (let i = this.startYear; i <= this.endYear; i++) {
      this.yearArray.push(this.formatLunarYear(i));
    }
    
    this.monthArray = [];
    for (let i = DatePickerConstant.MIN_MONTH; i <= DatePickerConstant.MAX_MONTH; i++) {
      this.monthArray.push(this.formatLunarMonth(i, false));
    }
    
    this.initLunarDayArray();
  }
  
  private initLunarDayArray(): void {
    this.dayArray = [];
    const lunarDays = this.getLunarDaysInMonth(this.selectedYear, this.selectedMonth);
    for (let i = DatePickerConstant.MIN_DAY; i <= lunarDays; i++) {
      this.dayArray.push(this.formatLunarDay(i));
    }
  }
  
  private getLunarDaysInMonth(gregorianYear: number, lunarMonth: number): number {
    if (this.lunarCalendar === null) {
      return 30;
    }
    
    try {
      let month1Start: Date | null = null;
      let month2Start: Date | null = null;
      
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
    } catch (e) {
      return 30;
    }
  }
  
  private formatLunarYear(gregorianYear: number): string {
    return `${gregorianYear}年`;
  }
  
  private formatLunarMonth(month: number, isLeap: boolean): string {
    const lunarMonthNames = ['正月', '二月', '三月', '四月', '五月', '六月',
                             '七月', '八月', '九月', '十月', '冬月', '腊月'];
    
    if (isLeap) {
      return `闰${lunarMonthNames[month]}`;
    }
    return lunarMonthNames[month];
  }
  
  private formatLunarDay(day: number): string {
    const lunarDayNames = ['初一', '初二', '初三', '初四', '初五', '初六', '初七', '初八', '初九', '初十',
                           '十一', '十二', '十三', '十四', '十五', '十六', '十七', '十八', '十九', '二十',
                           '廿一', '廿二', '廿三', '廿四', '廿五', '廿六', '廿七', '廿八', '廿九', '三十'];
    
    if (day >= 1 && day <= 30) {
      return lunarDayNames[day - 1];
    }
    return `${day}日`;
  }
  
  private initYearArray(): void {
    this.yearArray = [];
    for (let i = this.startYear; i <= this.endYear; i++) {
      this.yearArray.push(this.formatYear(i));
    }
  }
  
  private initMonthArray(): void {
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
  
  private initDayArray(): void {
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
  
  private initTimeArrays(): void {
    if (this.useMilitaryTime) {
      this.hourArray = [];
      for (let i = this.startHour; i <= this.endHour; i++) {
        this.hourArray.push(i.toString().padStart(2, '0'));
      }
    } else {
      this.updateHourArrayFor12Hour();
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
    
    this.periodArray = [];
    if (!this.useMilitaryTime) {
      this.updatePeriodArray();
      this.selectedPeriod = this.selectedHour < 12 ? 0 : 1;
    }
  }
  
  private updateHourArrayFor12Hour(): void {
    this.hourArray = [];
    
    const isAM = this.selectedPeriod === 0;
    const startHourForPeriod = isAM ? (this.startHour < 12 ? this.startHour : 12) : (this.startHour >= 12 ? this.startHour : 12);
    const endHourForPeriod = isAM ? (this.endHour < 12 ? this.endHour : 11) : (this.endHour >= 12 ? this.endHour : 11);
    
    if (isAM) {
      if (this.startHour < 12 && this.endHour >= 0) {
        const minHour = Math.max(0, this.startHour);
        const maxHour = Math.min(11, this.endHour < 12 ? this.endHour : 11);
        for (let i = minHour; i <= maxHour; i++) {
          const hour12 = i === 0 ? 12 : i;
          this.hourArray.push(hour12.toString().padStart(2, '0'));
        }
      } else if (this.startHour >= 12) {
        // AM时段不可选
      }
    } else {
      if (this.endHour >= 12) {
        const minHour = Math.max(12, this.startHour >= 12 ? this.startHour : 12);
        const maxHour = Math.min(23, this.endHour);
        for (let i = minHour; i <= maxHour; i++) {
          const hour12 = i === 12 ? 12 : i - 12;
          this.hourArray.push(hour12.toString().padStart(2, '0'));
        }
      } else if (this.endHour < 12) {
        // PM时段不可选
      }
    }
    
    if (this.hourArray.length === 0) {
      // 如果范围限制导致没有可选小时，显示默认范围
      for (let i = 1; i <= 12; i++) {
        this.hourArray.push(i.toString().padStart(2, '0'));
      }
    }
  }
  
  private updatePeriodArray(): void {
    this.periodArray = [];
    
    const canSelectAM = this.startHour < 12 || this.endHour >= 0;
    const canSelectPM = this.endHour >= 12;
    
    if (canSelectAM && canSelectPM) {
      this.periodArray.push(this.formatPeriod(true));
      this.periodArray.push(this.formatPeriod(false));
    } else if (canSelectAM && !canSelectPM) {
      this.periodArray.push(this.formatPeriod(true));
      if (this.selectedPeriod === 1) {
        this.selectedPeriod = 0;
      }
    } else if (!canSelectAM && canSelectPM) {
      this.periodArray.push(this.formatPeriod(false));
      if (this.selectedPeriod === 0) {
        this.selectedPeriod = 1;
      }
    } else {
      // 默认显示两个时段
      this.periodArray.push(this.formatPeriod(true));
      this.periodArray.push(this.formatPeriod(false));
    }
  }
  
  private isChineseLocale(): boolean {
    const localeStr = this.locale.toString();
    return localeStr.startsWith('zh') || localeStr.includes('zh-CN') || localeStr.includes('zh-TW') || localeStr.includes('zh-Hans') || localeStr.includes('zh-Hant');
  }
  
  private formatYear(year: number): string {
    if (this.isChineseLocale()) {
      return `${year}年`;
    }
    return year.toString();
  }
  
  private formatMonth(month: number): string {
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
    } catch (error) {
      return this.displayMode === DisplayMode.DATE_TIME ? shortMonthNames[month] : monthNames[month];
    }
  }
  
  private formatDay(day: number): string {
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
    } catch (error) {
      return `${day}`;
    }
  }
  
  private formatMinute(minute: number): string {
    return minute.toString().padStart(2, '0');
  }
  
private formatSecond(second: number): string {
  return second.toString().padStart(2, '0');
  }
  
  private formatPeriod(isAM: boolean): string {
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
  
  private getDaysInMonth(year: number, month: number): number {
    const monthsWith31Days = [0, 2, 4, 6, 7, 9, 11];
    const monthsWith30Days = [3, 5, 8, 10];
    
    if (month === 1) {
      const isLeapYear = (year % 4 === 0 && year % 100 !== 0) || (year % 400 === 0);
      return isLeapYear ? 29 : 28;
    } else if (monthsWith31Days.includes(month)) {
      return 31;
    } else if (monthsWith30Days.includes(month)) {
      return 30;
    }
    return 30;
  }
  
  private validateDate(date: Date): Date | undefined {
    try {
      const year = date.getFullYear();
      const month = date.getMonth();
      const day = date.getDate();
      
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
      
      return new Date(year, month, day);
    } catch (e) {
      return undefined;
    }
  }
  
  private validateTime(date: Date): Date | undefined {
    try {
      const hour = date.getHours();
      const minute = date.getMinutes();
      const second = date.getSeconds();
      
      if (hour < DatePickerConstant.MIN_HOUR || hour > DatePickerConstant.MAX_HOUR) {
        return undefined;
      }
      if (minute < DatePickerConstant.MIN_MINUTE || minute > DatePickerConstant.MAX_MINUTE) {
        return undefined;
      }
      if (second < DatePickerConstant.MIN_SECOND || second > DatePickerConstant.MAX_SECOND) {
        return undefined;
      }
      
      return new Date(2026, 0, 1, hour, minute, second);
    } catch (e) {
      return undefined;
    }
  }
  
  private createDateFromParams(year: number, month: number, day: number): Date {
    return new Date(year, month, day);
  }
  
  private onOptionsChange(): void {
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
  
  private updateDateOptions(dateOptions: DateOptions): void {
    if (dateOptions.mode !== undefined) {
      this.dateMode = dateOptions.mode;
    }
    
    if (dateOptions.lunar !== undefined) {
      this.lunar = dateOptions.lunar;
      if (this.lunar) {
        this.lunarCalendar = i18n.getCalendar(this.locale.toString(), 'chinese');
      } else {
        this.lunarCalendar = null;
      }
    }
    
    if (dateOptions.loop !== undefined) {
      this.dateCanLoop = dateOptions.loop;
    }
    
    if (dateOptions.enableHapticFeedback !== undefined) {
      this.dateHapticFeedback = dateOptions.enableHapticFeedback;
    }
    
    let startValid = false;
    let endValid = false;
    let startDate: Date | undefined = undefined;
    let endDate: Date | undefined = undefined;
    
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
      if (startDate! > endDate!) {
        this.startYear = DatePickerConstant.DEFAULT_START_YEAR;
        this.endYear = DatePickerConstant.DEFAULT_END_YEAR;
        this.startMonth = DatePickerConstant.MIN_MONTH;
        this.endMonth = DatePickerConstant.MAX_MONTH;
        this.startDay = DatePickerConstant.MIN_DAY;
        this.endDay = 31;
      } else {
        this.startYear = startDate!.getFullYear();
        this.startMonth = startDate!.getMonth();
        this.startDay = startDate!.getDate();
        this.endYear = endDate!.getFullYear();
        this.endMonth = endDate!.getMonth();
        this.endDay = endDate!.getDate();
      }
    } else if (startValid && !endValid) {
      this.startYear = startDate!.getFullYear();
      this.startMonth = startDate!.getMonth();
      this.startDay = startDate!.getDate();
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
      this.endYear = endDate!.getFullYear();
      this.endMonth = endDate!.getMonth();
      this.endDay = endDate!.getDate();
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
    let targetDate: Date;
    if (selectedValid) {
      targetDate = selectedDate!;
    } else {
      targetDate = now;
    }
    
    // Adjust selected date to be within range
    if (targetDate < startDateObj) {
      targetDate = startDateObj;
    } else if (targetDate > endDateObj) {
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
    } else {
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
  
  private updateTimeOptions(timeOptions: TimeOptions): void {
    if (timeOptions.format !== undefined) {
      this.timeFormat = timeOptions.format;
    }
    
    if (timeOptions.useMilitaryTime !== undefined) {
      this.useMilitaryTime = timeOptions.useMilitaryTime;
    }
    
    if (timeOptions.loop !== undefined) {
      this.timeCanLoop = timeOptions.loop;
    }
    
    if (timeOptions.enableHapticFeedback !== undefined) {
      this.timeHapticFeedback = timeOptions.enableHapticFeedback;
    }
    
    let startValid = false;
    let endValid = false;
    let startTime: Date | undefined = undefined;
    let endTime: Date | undefined = undefined;
    
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
        this.startHour = startTime!.getHours();
        this.startMinute = startTime!.getMinutes();
        this.startSecond = startTime!.getSeconds();
        this.endHour = endTime!.getHours();
        this.endMinute = endTime!.getMinutes();
        this.endSecond = endTime!.getSeconds();
      }
    } else if (startValid && !endValid) {
      this.startHour = startTime!.getHours();
      this.startMinute = startTime!.getMinutes();
      this.startSecond = startTime!.getSeconds();
      this.endHour = DatePickerConstant.MAX_HOUR;
      this.endMinute = DatePickerConstant.MAX_MINUTE;
      this.endSecond = DatePickerConstant.MAX_SECOND;
    } else if (!startValid && endValid) {
      this.startHour = DatePickerConstant.MIN_HOUR;
      this.startMinute = DatePickerConstant.MIN_MINUTE;
      this.startSecond = DatePickerConstant.MIN_SECOND;
      this.endHour = endTime!.getHours();
      this.endMinute = endTime!.getMinutes();
      this.endSecond = endTime!.getSeconds();
    } else {
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
    
    const now = new Date();
    let selectedTime: Date | undefined = undefined;
    let selectedValid = false;
    
    if (timeOptions.selected !== undefined) {
      selectedTime = this.validateTime(timeOptions.selected);
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
    const startTimeObj = new Date(2026, 0, 1, this.startHour, this.startMinute, this.startSecond);
    const endTimeObj = new Date(2026, 0, 1, this.endHour, this.endMinute, this.endSecond);
    const targetTimeObj = new Date(2026, 0, 1, targetTime.getHours(), targetTime.getMinutes(), targetTime.getSeconds());
    
    // Adjust selected time to be within range
    if (targetTimeObj < startTimeObj) {
      targetTimeObj.setTime(startTimeObj.getTime());
    } else if (targetTimeObj > endTimeObj) {
      targetTimeObj.setTime(endTimeObj.getTime());
    }
    
    // Extract hour, minute, second from adjusted time
    this.selectedHour = targetTimeObj.getHours();
    this.selectedMinute = targetTimeObj.getMinutes();
    this.selectedSecond = targetTimeObj.getSeconds();
    
    if (timeOptions.onChange !== undefined) {
      this.timeOnChange = timeOptions.onChange;
    }
    
    if (timeOptions.onScrollStop !== undefined) {
      this.timeOnScrollStop = timeOptions.onScrollStop;
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
  
  private onYearChange(selectedIndex: number): void {
    this.selectedYear = this.startYear + selectedIndex;
    this.updateDaysArray();
    this.dateOnChange?.(this.getResult());
  }
  
  private onMonthChange(selectedIndex: number): void {
    let startMonthIndex = DatePickerConstant.MIN_MONTH;
    if (this.selectedYear === this.startYear) {
      startMonthIndex = this.startMonth;
    }
    this.selectedMonth = startMonthIndex + selectedIndex;
    this.updateDaysArray();
    this.dateOnChange?.(this.getResult());
  }
  
  private onDayChange(selectedIndex: number): void {
    let startDayIndex = DatePickerConstant.MIN_DAY;
    if (this.selectedYear === this.startYear && this.selectedMonth === this.startMonth) {
      startDayIndex = this.startDay;
    }
    this.selectedDay = startDayIndex + selectedIndex;
    this.dateOnChange?.(this.getResult());
  }
  
private onHourChange(selectedIndex: number): void {
    if (this.useMilitaryTime) {
      this.selectedHour = this.startHour + selectedIndex;
    } else {
      const oldDisplayIndex = this.getHourSelectedIndex();
      const crossingBoundary = (oldDisplayIndex === 11 && selectedIndex === 0) || 
                               (oldDisplayIndex === 0 && selectedIndex === 11);
      
      if (crossingBoundary) {
        this.selectedPeriod = this.selectedPeriod === 0 ? 1 : 0;
      }
      
      const displayHour = selectedIndex + 1;
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
    this.updateTimeArrays();
    this.timeOnChange?.(this.getResult());
  }
  
  private onPeriodChange(selectedIndex: number): void {
    this.selectedPeriod = selectedIndex;
    
    if (!this.useMilitaryTime) {
      // 更新hourArray
      this.updateHourArrayFor12Hour();
      
      // 根据新的period调整selectedHour
      const isAM = this.selectedPeriod === 0;
      if (isAM) {
        // 切换到AM时段
        const minHour = Math.max(0, this.startHour);
        const maxHour = Math.min(11, this.endHour < 12 ? this.endHour : 11);
        
        // 如果当前hour不在AM范围内，调整到范围内
        if (this.selectedHour >= 12 || this.selectedHour < minHour) {
          this.selectedHour = minHour;
        }
        if (this.selectedHour > maxHour) {
          this.selectedHour = maxHour;
        }
      } else {
        // 切换到PM时段
        const minHour = Math.max(12, this.startHour >= 12 ? this.startHour : 12);
        const maxHour = Math.min(23, this.endHour);
        
        // 如果当前hour不在PM范围内，调整到范围内
        if (this.selectedHour < 12 || this.selectedHour < minHour) {
          this.selectedHour = minHour;
        }
        if (this.selectedHour > maxHour) {
          this.selectedHour = maxHour;
        }
      }
      
      // 更新minute和second数组
      this.updateTimeArrays();
    }
    
    this.timeOnChange?.(this.getResult());
  }
  
  private onMinuteChange(selectedIndex: number): void {
    let startMinuteIndex = DatePickerConstant.MIN_MINUTE;
    if (this.selectedHour === this.startHour) {
      startMinuteIndex = this.startMinute;
    }
    this.selectedMinute = startMinuteIndex + selectedIndex;
    this.updateSecondArray();
    this.timeOnChange?.(this.getResult());
  }
  
  private onSecondChange(selectedIndex: number): void {
    let startSecondIndex = DatePickerConstant.MIN_SECOND;
    if (this.selectedHour === this.startHour && this.selectedMinute === this.startMinute) {
      startSecondIndex = this.startSecond;
    }
    this.selectedSecond = startSecondIndex + selectedIndex;
    this.timeOnChange?.(this.getResult());
  }
  
  private updateTimeArrays(): void {
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
  
  private updateSecondArray(): void {
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
  
  private updateDaysArray(): void {
    if (this.lunar) {
      const lunarDays = this.getLunarDaysInMonth(this.selectedYear, this.selectedMonth);
      if (this.selectedDay > lunarDays) {
        this.selectedDay = lunarDays;
      }
      this.initLunarDayArray();
    } else {
      const daysInMonth = this.getDaysInMonth(this.selectedYear, this.selectedMonth);
      if (this.selectedDay > daysInMonth) {
        this.selectedDay = daysInMonth;
      }
      this.initDayArray();
    }
  }
  
  private getYearSelectedIndex(): number {
    return this.selectedYear - this.startYear;
  }
  
  private getMonthSelectedIndex(): number {
    let startMonthIndex = DatePickerConstant.MIN_MONTH;
    if (this.selectedYear === this.startYear) {
      startMonthIndex = this.startMonth;
    }
    return this.selectedMonth - startMonthIndex;
  }
  
  private getDaySelectedIndex(): number {
    let startDayIndex = DatePickerConstant.MIN_DAY;
    if (this.selectedYear === this.startYear && this.selectedMonth === this.startMonth) {
      startDayIndex = this.startDay;
    }
    return this.selectedDay - startDayIndex;
  }
  
  private getHourSelectedIndex(): number {
    if (this.useMilitaryTime) {
      return this.selectedHour - this.startHour;
    } else {
      const isAM = this.selectedPeriod === 0;
      
      if (isAM) {
        const minHour = Math.max(0, this.startHour);
        if (this.selectedHour === 0) {
          return 0 - minHour;
        } else if (this.selectedHour >= 1 && this.selectedHour <= 11) {
          return this.selectedHour - minHour;
        }
        return 0;
      } else {
        const minHour = Math.max(12, this.startHour >= 12 ? this.startHour : 12);
        if (this.selectedHour === 12) {
          return 0;
        } else if (this.selectedHour >= 13 && this.selectedHour <= 23) {
          return this.selectedHour - minHour;
        }
        return 0;
      }
    }
  }
  
  private getMinuteSelectedIndex(): number {
    let startMinuteIndex = DatePickerConstant.MIN_MINUTE;
    if (this.selectedHour === this.startHour) {
      startMinuteIndex = this.startMinute;
    }
    return this.selectedMinute - startMinuteIndex;
  }
  
  private getSecondSelectedIndex(): number {
    let startSecondIndex = DatePickerConstant.MIN_SECOND;
    if (this.selectedHour === this.startHour && this.selectedMinute === this.startMinute) {
      startSecondIndex = this.startSecond;
    }
    return this.selectedSecond - startSecondIndex;
  }
  
  private isRTL(): boolean {
    return i18n.isRTL(this.locale.toString()) ?? false;
  }
  
  private getFirstPickerIndicator(radius: number = 20): PickerIndicatorStyle {
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
  
  private getLastPickerIndicator(radius: number = 20): PickerIndicatorStyle {
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
  
  build() {
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
          .onChange((selectedIndex: number) => {
            this.onYearChange(selectedIndex);
          })
          .onScrollStop((selectedIndex: number) => {
            this.selectedYear = this.startYear + selectedIndex;
            this.updateDaysArray();
            this.dateOnScrollStop?.(this.getResult());
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
          .onChange((selectedIndex: number) => {
            this.onMonthChange(selectedIndex);
          })
          .onScrollStop((selectedIndex: number) => {
            let startMonthIndex = DatePickerConstant.MIN_MONTH;
            if (this.selectedYear === this.startYear) {
              startMonthIndex = this.startMonth;
            }
            this.selectedMonth = startMonthIndex + selectedIndex;
            this.dateOnScrollStop?.(this.getResult());
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
          .onChange((selectedIndex: number) => {
            this.onDayChange(selectedIndex);
          })
          .onScrollStop((selectedIndex: number) => {
            let startDayIndex = DatePickerConstant.MIN_DAY;
            if (this.selectedYear === this.startYear && this.selectedMonth === this.startMonth) {
              startDayIndex = this.startDay;
            }
            this.selectedDay = startDayIndex + selectedIndex;
            this.dateOnScrollStop?.(this.getResult());
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
          .onChange((selectedIndex: number) => {
            this.onYearChange(selectedIndex);
          })
          .onScrollStop((selectedIndex: number) => {
            this.selectedYear = this.startYear + selectedIndex;
            this.updateDaysArray();
            this.dateOnScrollStop?.(this.getResult());
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
          .onChange((selectedIndex: number) => {
            this.onMonthChange(selectedIndex);
          })
          .onScrollStop((selectedIndex: number) => {
            let startMonthIndex = DatePickerConstant.MIN_MONTH;
            if (this.selectedYear === this.startYear) {
              startMonthIndex = this.startMonth;
            }
            this.selectedMonth = startMonthIndex + selectedIndex;
            this.dateOnScrollStop?.(this.getResult());
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
          .onChange((selectedIndex: number) => {
            this.onMonthChange(selectedIndex);
          })
          .onScrollStop((selectedIndex: number) => {
            let startMonthIndex = DatePickerConstant.MIN_MONTH;
            if (this.selectedYear === this.startYear) {
              startMonthIndex = this.startMonth;
            }
            this.selectedMonth = startMonthIndex + selectedIndex;
            this.dateOnScrollStop?.(this.getResult());
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
          .onChange((selectedIndex: number) => {
            this.onDayChange(selectedIndex);
          })
          .onScrollStop((selectedIndex: number) => {
            let startDayIndex = DatePickerConstant.MIN_DAY;
            if (this.selectedYear === this.startYear && this.selectedMonth === this.startMonth) {
              startDayIndex = this.startDay;
            }
            this.selectedDay = startDayIndex + selectedIndex;
            this.dateOnScrollStop?.(this.getResult());
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
            .onChange((selectedIndex: number) => {
              this.onHourChange(selectedIndex);
            })
            .onScrollStop((selectedIndex: number) => {
              this.selectedHour = this.startHour + selectedIndex;
              this.updateTimeArrays();
              this.timeOnScrollStop?.(this.getResult());
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
            .onChange((selectedIndex: number) => {
              this.onMinuteChange(selectedIndex);
            })
            .onScrollStop((selectedIndex: number) => {
              let startMinuteIndex = DatePickerConstant.MIN_MINUTE;
              if (this.selectedHour === this.startHour) {
                startMinuteIndex = this.startMinute;
              }
              this.selectedMinute = startMinuteIndex + selectedIndex;
              this.updateSecondArray();
              this.timeOnScrollStop?.(this.getResult());
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
            .onChange((selectedIndex: number) => {
              this.onPeriodChange(selectedIndex);
            })
            .onScrollStop((selectedIndex: number) => {
              this.selectedPeriod = selectedIndex;
              this.timeOnScrollStop?.(this.getResult());
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
            .onChange((selectedIndex: number) => {
              this.onHourChange(selectedIndex);
            })
            .onScrollStop((selectedIndex: number) => {
              this.onHourChange(selectedIndex);
              this.timeOnScrollStop?.(this.getResult());
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
            .onChange((selectedIndex: number) => {
              this.onMinuteChange(selectedIndex);
            })
            .onScrollStop((selectedIndex: number) => {
              let startMinuteIndex = DatePickerConstant.MIN_MINUTE;
              if (this.selectedHour === this.startHour) {
                startMinuteIndex = this.startMinute;
              }
              this.selectedMinute = startMinuteIndex + selectedIndex;
              this.updateSecondArray();
              this.timeOnScrollStop?.(this.getResult());
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
            .onChange((selectedIndex: number) => {
              this.onHourChange(selectedIndex);
            })
            .onScrollStop((selectedIndex: number) => {
              this.selectedHour = this.startHour + selectedIndex;
              this.updateTimeArrays();
              this.timeOnScrollStop?.(this.getResult());
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
            .onChange((selectedIndex: number) => {
              this.onMinuteChange(selectedIndex);
            })
            .onScrollStop((selectedIndex: number) => {
              let startMinuteIndex = DatePickerConstant.MIN_MINUTE;
              if (this.selectedHour === this.startHour) {
                startMinuteIndex = this.startMinute;
              }
              this.selectedMinute = startMinuteIndex + selectedIndex;
              this.updateSecondArray();
              this.timeOnScrollStop?.(this.getResult());
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
            .onChange((selectedIndex: number) => {
              this.onSecondChange(selectedIndex);
            })
            .onScrollStop((selectedIndex: number) => {
              let startSecondIndex = DatePickerConstant.MIN_SECOND;
              if (this.selectedHour === this.startHour && this.selectedMinute === this.startMinute) {
                startSecondIndex = this.startSecond;
              }
              this.selectedSecond = startSecondIndex + selectedIndex;
              this.timeOnScrollStop?.(this.getResult());
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
            .onChange((selectedIndex: number) => {
              this.onPeriodChange(selectedIndex);
            })
            .onScrollStop((selectedIndex: number) => {
              this.selectedPeriod = selectedIndex;
              this.timeOnScrollStop?.(this.getResult());
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
            .onChange((selectedIndex: number) => {
              this.onHourChange(selectedIndex);
            })
            .onScrollStop((selectedIndex: number) => {
              this.onHourChange(selectedIndex);
              this.timeOnScrollStop?.(this.getResult());
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
            .onChange((selectedIndex: number) => {
              this.onMinuteChange(selectedIndex);
            })
            .onScrollStop((selectedIndex: number) => {
              let startMinuteIndex = DatePickerConstant.MIN_MINUTE;
              if (this.selectedHour === this.startHour) {
                startMinuteIndex = this.startMinute;
              }
              this.selectedMinute = startMinuteIndex + selectedIndex;
              this.updateSecondArray();
              this.timeOnScrollStop?.(this.getResult());
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
            .onChange((selectedIndex: number) => {
              this.onSecondChange(selectedIndex);
            })
            .onScrollStop((selectedIndex: number) => {
              let startSecondIndex = DatePickerConstant.MIN_SECOND;
              if (this.selectedHour === this.startHour && this.selectedMinute === this.startMinute) {
                startSecondIndex = this.startSecond;
              }
              this.selectedSecond = startSecondIndex + selectedIndex;
              this.timeOnScrollStop?.(this.getResult());
            })
          }
        }
      }
    }
    .width('100%')
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
}
