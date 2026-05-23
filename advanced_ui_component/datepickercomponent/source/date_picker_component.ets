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
  @State dateMode: DateMode = DateMode.DATE;
  @State timeFormat: TimeFormat = TimeFormat.HOUR_MINUTE;
  @State useMilitaryTime: boolean = false;
  @State lunar: boolean = false;
  @State canLoop: boolean = true;
  @State hapticFeedback: boolean = true;
  @State yearArray: string[] = [];
  @State monthArray: string[] = [];
  @State dayArray: string[] = [];
  @State hourArray: string[] = [];
  @State minuteArray: string[] = [];
  @State secondArray: string[] = [];
  @State periodArray: string[] = [];
  @State selectedPeriod: number = 0;
  private onChange?: Callback<DatePickerComponentResult>;
  private onScrollStop?: Callback<DatePickerComponentResult>;
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
    for (let i = DatePickerConstant.MIN_MONTH; i <= DatePickerConstant.MAX_MONTH; i++) {
      this.monthArray.push(this.formatMonth(i));
    }
  }
  
  private initDayArray(): void {
    this.dayArray = [];
    const daysInMonth = this.getDaysInMonth(this.selectedYear, this.selectedMonth);
    for (let i = DatePickerConstant.MIN_DAY; i <= daysInMonth; i++) {
      this.dayArray.push(this.formatDay(i));
    }
  }
  
  private initTimeArrays(): void {
    this.hourArray = [];
    if (this.useMilitaryTime) {
      for (let i = DatePickerConstant.MIN_HOUR; i <= DatePickerConstant.MAX_HOUR; i++) {
        this.hourArray.push(i.toString().padStart(2, '0'));
      }
    } else {
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
        } else {
          this.selectedYear = dateOptions.selected.getFullYear();
          this.selectedMonth = dateOptions.selected.getMonth();
          this.selectedDay = dateOptions.selected.getDate();
        }
      }
    } else {
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
        } else {
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
  
  private updateTimeOptions(timeOptions: TimeOptions): void {
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
    } else {
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
    this.onChange?.(this.getResult());
  }
  
  private onMonthChange(selectedIndex: number): void {
    this.selectedMonth = selectedIndex;
    this.updateDaysArray();
    this.onChange?.(this.getResult());
  }
  
  private onDayChange(selectedIndex: number): void {
    this.selectedDay = selectedIndex + 1;
    this.onChange?.(this.getResult());
  }
  
private onHourChange(selectedIndex: number): void {
    if (this.useMilitaryTime) {
      this.selectedHour = selectedIndex;
    } else {
      // Detect boundary crossing: 12(index 11) → 1(index 0) or 1(index 0) → 12(index 11)
      const oldDisplayIndex = this.getHourSelectedIndex();
      const crossingBoundary = (oldDisplayIndex === 11 && selectedIndex === 0) || 
                               (oldDisplayIndex === 0 && selectedIndex === 11);
      
      // Auto-switch period when crossing boundary
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
    this.onChange?.(this.getResult());
  }
  
  private onPeriodChange(selectedIndex: number): void {
    this.selectedPeriod = selectedIndex;
    if (!this.useMilitaryTime) {
      const displayHourIndex = this.getHourSelectedIndex();
      const displayHour = displayHourIndex + 1;
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
    this.onChange?.(this.getResult());
  }
  
  private onMinuteChange(selectedIndex: number): void {
    this.selectedMinute = selectedIndex;
    this.onChange?.(this.getResult());
  }
  
  private onSecondChange(selectedIndex: number): void {
    this.selectedSecond = selectedIndex;
    this.onChange?.(this.getResult());
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
    return this.selectedMonth;
  }
  
  private getDaySelectedIndex(): number {
    return this.selectedDay - 1;
  }
  
  private getHourSelectedIndex(): number {
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
  
  private getPeriodSelectedIndex(): number {
    return this.selectedPeriod;
  }
  
  private getMinuteSelectedIndex(): number {
    return this.selectedMinute;
  }
  
  private getSecondSelectedIndex(): number {
    return this.selectedSecond;
  }
  
  private getFirstPickerIndicator(radius: number = 20): PickerIndicatorStyle {
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
          .canLoop(this.canLoop)
          .enableHapticFeedback(this.hapticFeedback)
          .selectionIndicator(this.getFirstPickerIndicator())
          .onChange((selectedIndex: number) => {
            this.onYearChange(selectedIndex);
          })
          .onScrollStop((selectedIndex: number) => {
            this.selectedYear = this.startYear + selectedIndex;
            this.updateDaysArray();
            this.onScrollStop?.(this.getResult());
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
          .onChange((selectedIndex: number) => {
            this.onMonthChange(selectedIndex);
          })
          .onScrollStop((selectedIndex: number) => {
            this.selectedMonth = selectedIndex;
            this.onScrollStop?.(this.getResult());
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
          .onChange((selectedIndex: number) => {
            this.onDayChange(selectedIndex);
          })
          .onScrollStop((selectedIndex: number) => {
            this.selectedDay = selectedIndex + 1;
            this.onScrollStop?.(this.getResult());
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
          .onChange((selectedIndex: number) => {
            this.onYearChange(selectedIndex);
          })
          .onScrollStop((selectedIndex: number) => {
            this.selectedYear = this.startYear + selectedIndex;
            this.updateDaysArray();
            this.onScrollStop?.(this.getResult());
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
          .onChange((selectedIndex: number) => {
            this.onMonthChange(selectedIndex);
          })
          .onScrollStop((selectedIndex: number) => {
            this.selectedMonth = selectedIndex;
            this.onScrollStop?.(this.getResult());
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
          .onChange((selectedIndex: number) => {
            this.onMonthChange(selectedIndex);
          })
          .onScrollStop((selectedIndex: number) => {
            this.selectedMonth = selectedIndex;
            this.onScrollStop?.(this.getResult());
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
          .onChange((selectedIndex: number) => {
            this.onDayChange(selectedIndex);
          })
          .onScrollStop((selectedIndex: number) => {
            this.selectedDay = selectedIndex + 1;
            this.onScrollStop?.(this.getResult());
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
            .onChange((selectedIndex: number) => {
              this.onHourChange(selectedIndex);
            })
            .onScrollStop((selectedIndex: number) => {
              this.selectedHour = selectedIndex;
              this.onScrollStop?.(this.getResult());
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
            .onChange((selectedIndex: number) => {
              this.onMinuteChange(selectedIndex);
            })
            .onScrollStop((selectedIndex: number) => {
              this.selectedMinute = selectedIndex;
              this.onScrollStop?.(this.getResult());
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
            .onChange((selectedIndex: number) => {
              this.onPeriodChange(selectedIndex);
            })
            .onScrollStop((selectedIndex: number) => {
              this.selectedPeriod = selectedIndex;
              this.onScrollStop?.(this.getResult());
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
            .onChange((selectedIndex: number) => {
              this.onHourChange(selectedIndex);
            })
            .onScrollStop((selectedIndex: number) => {
              this.onHourChange(selectedIndex);
              this.onScrollStop?.(this.getResult());
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
            .onChange((selectedIndex: number) => {
              this.onMinuteChange(selectedIndex);
            })
            .onScrollStop((selectedIndex: number) => {
              this.selectedMinute = selectedIndex;
              this.onScrollStop?.(this.getResult());
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
            .onChange((selectedIndex: number) => {
              this.onHourChange(selectedIndex);
            })
            .onScrollStop((selectedIndex: number) => {
              this.selectedHour = selectedIndex;
              this.onScrollStop?.(this.getResult());
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
            .onChange((selectedIndex: number) => {
              this.onMinuteChange(selectedIndex);
            })
            .onScrollStop((selectedIndex: number) => {
              this.selectedMinute = selectedIndex;
              this.onScrollStop?.(this.getResult());
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
            .onChange((selectedIndex: number) => {
              this.onSecondChange(selectedIndex);
            })
            .onScrollStop((selectedIndex: number) => {
              this.selectedSecond = selectedIndex;
              this.onScrollStop?.(this.getResult());
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
            .onChange((selectedIndex: number) => {
              this.onPeriodChange(selectedIndex);
            })
            .onScrollStop((selectedIndex: number) => {
              this.selectedPeriod = selectedIndex;
              this.onScrollStop?.(this.getResult());
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
            .onChange((selectedIndex: number) => {
              this.onHourChange(selectedIndex);
            })
            .onScrollStop((selectedIndex: number) => {
              this.onHourChange(selectedIndex);
              this.onScrollStop?.(this.getResult());
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
            .onChange((selectedIndex: number) => {
              this.onMinuteChange(selectedIndex);
            })
            .onScrollStop((selectedIndex: number) => {
              this.selectedMinute = selectedIndex;
              this.onScrollStop?.(this.getResult());
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
            .onChange((selectedIndex: number) => {
              this.onSecondChange(selectedIndex);
            })
            .onScrollStop((selectedIndex: number) => {
              this.selectedSecond = selectedIndex;
              this.onScrollStop?.(this.getResult());
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
