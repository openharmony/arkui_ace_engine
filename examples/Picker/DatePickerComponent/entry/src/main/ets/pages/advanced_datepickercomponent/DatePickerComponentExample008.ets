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

import { DatePickerComponent, DateMode, DisplayMode, TimeFormat, DatePickerComponentOptions, DateOptions, TimeOptions } from '@ohos.arkui.advanced.DatePickerComponent'

@Entry
@Component
struct DatePickerComponentExample008 {
  @State isLunar: boolean = false
  @State currentDateMode: DateMode = DateMode.DATE
  @State currentDisplayMode: DisplayMode = DisplayMode.DATE
  @State currentTimeFormat: TimeFormat = TimeFormat.HOUR_MINUTE
  @State isMilitaryTime: boolean = false
  @State canLoop: boolean = true
  @State enableHaptic: boolean = true
  @State selectedYear: number = 2026
  @State selectedMonth: number = 0
  @State selectedDay: number = 1
  @State selectedHour: number = 14
  @State selectedMinute: number = 30
  @State selectedSecond: number = 0
  @State datePickerRef: DatePickerComponent | null = null
  @State currentLocaleTag: string = 'zh-CN'
  @State logText: string = ''

  build() {
    Scroll() {
      Column() {
        Text('DatePickerComponent Interactive Demo')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 20 })

        Text('Full-featured interactive control panel')
          .fontSize(14)
          .fontColor('#666666')
          .margin({ bottom: 20 })

        Column() {
          Text('Control Panel')
            .fontSize(18)
            .fontWeight(FontWeight.Medium)
            .margin({ bottom: 10 })

          Row() {
            Text('Lunar Mode:')
              .fontSize(14)
              .width(120)
            Toggle({ type: ToggleType.Switch, isOn: this.isLunar })
              .onChange((isOn: boolean) => {
                this.isLunar = isOn
                this.addLog('Lunar: ' + (isOn ? 'ON' : 'OFF'))
              })
              .selectedColor('#007DFF')
            Text(this.isLunar ? 'ON' : 'OFF')
              .fontSize(14)
              .margin({ left: 10 })
          }
          .width('100%')
          .justifyContent(FlexAlign.Start)
          .margin({ bottom: 10 })

          Row() {
            Text('Date Mode:')
              .fontSize(14)
              .width(120)
            Button('DATE')
              .fontSize(12)
              .width(80)
              .height(30)
              .type(this.currentDateMode === DateMode.DATE ? ButtonType.Capsule : ButtonType.Normal)
              .stateEffect(this.currentDateMode === DateMode.DATE)
              .backgroundColor(this.currentDateMode === DateMode.DATE ? '#007DFF' : '#E0E0E0')
              .onClick(() => {
                this.currentDateMode = DateMode.DATE
                this.currentDisplayMode = DisplayMode.DATE
                this.addLog('Date Mode: DATE')
              })
            Button('YEAR_MONTH')
              .fontSize(12)
              .width(80)
              .height(30)
              .margin({ left: 5 })
              .type(this.currentDateMode === DateMode.YEAR_AND_MONTH ? ButtonType.Capsule : ButtonType.Normal)
              .stateEffect(this.currentDateMode === DateMode.YEAR_AND_MONTH)
              .backgroundColor(this.currentDateMode === DateMode.YEAR_AND_MONTH ? '#007DFF' : '#E0E0E0')
              .onClick(() => {
                this.currentDateMode = DateMode.YEAR_AND_MONTH
                this.currentDisplayMode = DisplayMode.DATE
                this.addLog('Date Mode: YEAR_MONTH')
              })
            Button('MONTH_DAY')
              .fontSize(12)
              .width(80)
              .height(30)
              .margin({ left: 5 })
              .type(this.currentDateMode === DateMode.MONTH_AND_DAY ? ButtonType.Capsule : ButtonType.Normal)
              .stateEffect(this.currentDateMode === DateMode.MONTH_AND_DAY)
              .backgroundColor(this.currentDateMode === DateMode.MONTH_AND_DAY ? '#007DFF' : '#E0E0E0')
              .onClick(() => {
                this.currentDateMode = DateMode.MONTH_AND_DAY
                this.currentDisplayMode = DisplayMode.DATE
                this.addLog('Date Mode: MONTH_DAY')
              })
          }
          .width('100%')
          .justifyContent(FlexAlign.Start)
          .margin({ bottom: 10 })

          Row() {
            Text('Display Mode:')
              .fontSize(14)
              .width(120)
            Button('DATE')
              .fontSize(12)
              .width(80)
              .height(30)
              .type(this.currentDisplayMode === DisplayMode.DATE ? ButtonType.Capsule : ButtonType.Normal)
              .stateEffect(this.currentDisplayMode === DisplayMode.DATE)
              .backgroundColor(this.currentDisplayMode === DisplayMode.DATE ? '#007DFF' : '#E0E0E0')
              .onClick(() => {
                this.currentDisplayMode = DisplayMode.DATE
                this.addLog('Display Mode: DATE')
              })
            Button('TIME')
              .fontSize(12)
              .width(80)
              .height(30)
              .margin({ left: 5 })
              .type(this.currentDisplayMode === DisplayMode.TIME ? ButtonType.Capsule : ButtonType.Normal)
              .stateEffect(this.currentDisplayMode === DisplayMode.TIME)
              .backgroundColor(this.currentDisplayMode === DisplayMode.TIME ? '#007DFF' : '#E0E0E0')
              .onClick(() => {
                this.currentDisplayMode = DisplayMode.TIME
                this.addLog('Display Mode: TIME')
              })
            Button('DATE_TIME')
              .fontSize(12)
              .width(80)
              .height(30)
              .margin({ left: 5 })
              .type(this.currentDisplayMode === DisplayMode.DATE_TIME ? ButtonType.Capsule : ButtonType.Normal)
              .stateEffect(this.currentDisplayMode === DisplayMode.DATE_TIME)
              .backgroundColor(this.currentDisplayMode === DisplayMode.DATE_TIME ? '#007DFF' : '#E0E0E0')
              .onClick(() => {
                this.currentDisplayMode = DisplayMode.DATE_TIME
                this.addLog('Display Mode: DATE_TIME')
              })
          }
          .width('100%')
          .justifyContent(FlexAlign.Start)
          .margin({ bottom: 10 })

          Row() {
            Text('Time Format:')
              .fontSize(14)
              .width(120)
            Button('H:M')
              .fontSize(12)
              .width(80)
              .height(30)
              .type(this.currentTimeFormat === TimeFormat.HOUR_MINUTE ? ButtonType.Capsule : ButtonType.Normal)
              .stateEffect(this.currentTimeFormat === TimeFormat.HOUR_MINUTE)
              .backgroundColor(this.currentTimeFormat === TimeFormat.HOUR_MINUTE ? '#007DFF' : '#E0E0E0')
              .onClick(() => {
                this.currentTimeFormat = TimeFormat.HOUR_MINUTE
                this.addLog('Time Format: HOUR_MINUTE')
              })
            Button('H:M:S')
              .fontSize(12)
              .width(80)
              .height(30)
              .margin({ left: 5 })
              .type(this.currentTimeFormat === TimeFormat.HOUR_MINUTE_SECOND ? ButtonType.Capsule : ButtonType.Normal)
              .stateEffect(this.currentTimeFormat === TimeFormat.HOUR_MINUTE_SECOND)
              .backgroundColor(this.currentTimeFormat === TimeFormat.HOUR_MINUTE_SECOND ? '#007DFF' : '#E0E0E0')
              .onClick(() => {
                this.currentTimeFormat = TimeFormat.HOUR_MINUTE_SECOND
                this.addLog('Time Format: HOUR_MINUTE_SECOND')
              })
          }
          .width('100%')
          .justifyContent(FlexAlign.Start)
          .margin({ bottom: 10 })

          Row() {
            Text('Military Time:')
              .fontSize(14)
              .width(120)
            Toggle({ type: ToggleType.Switch, isOn: this.isMilitaryTime })
              .onChange((isOn: boolean) => {
                this.isMilitaryTime = isOn
                this.addLog('Military Time: ' + (isOn ? '24H' : '12H'))
              })
              .selectedColor('#007DFF')
            Text(this.isMilitaryTime ? '24H' : '12H')
              .fontSize(14)
              .margin({ left: 10 })
          }
          .width('100%')
          .justifyContent(FlexAlign.Start)
          .margin({ bottom: 10 })

          Row() {
            Text('Loop:')
              .fontSize(14)
              .width(120)
            Toggle({ type: ToggleType.Switch, isOn: this.canLoop })
              .onChange((isOn: boolean) => {
                this.canLoop = isOn
                this.addLog('Loop: ' + (isOn ? 'ON' : 'OFF'))
              })
              .selectedColor('#007DFF')
            Text(this.canLoop ? 'ON' : 'OFF')
              .fontSize(14)
              .margin({ left: 10 })
          }
          .width('100%')
          .justifyContent(FlexAlign.Start)
          .margin({ bottom: 10 })

          Row() {
            Text('Haptic:')
              .fontSize(14)
              .width(120)
            Toggle({ type: ToggleType.Switch, isOn: this.enableHaptic })
              .onChange((isOn: boolean) => {
                this.enableHaptic = isOn
                this.addLog('Haptic: ' + (isOn ? 'ON' : 'OFF'))
              })
              .selectedColor('#007DFF')
            Text(this.enableHaptic ? 'ON' : 'OFF')
              .fontSize(14)
              .margin({ left: 10 })
          }
          .width('100%')
          .justifyContent(FlexAlign.Start)
          .margin({ bottom: 10 })
        }
        .width('90%')
        .padding(15)
        .backgroundColor('#FFFFFF')
        .borderRadius(10)
        .margin({ bottom: 20 })

        Column() {
          Text('Current Settings')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ bottom: 10 })

          Text(`Lunar: ${this.isLunar ? 'ON' : 'OFF'} | Mode: ${this.getDateModeText()} | Display: ${this.getDisplayModeText()}`)
            .fontSize(12)
            .margin({ bottom: 5 })

          Text(`Time Format: ${this.currentTimeFormat === TimeFormat.HOUR_MINUTE ? 'H:M' : 'H:M:S'} | Military: ${this.isMilitaryTime ? '24H' : '12H'}`)
            .fontSize(12)
            .margin({ bottom: 5 })

          Text(`Loop: ${this.canLoop ? 'ON' : 'OFF'} | Haptic: ${this.enableHaptic ? 'ON' : 'OFF'} | Locale: ${this.currentLocaleTag}`)
            .fontSize(12)
            .margin({ bottom: 5 })
        }
        .width('90%')
        .padding(10)
        .backgroundColor('#E8F4FF')
        .borderRadius(8)
        .margin({ bottom: 20 })

        Text('DatePickerComponent')
          .fontSize(18)
          .fontWeight(FontWeight.Medium)
          .margin({ bottom: 10 })

        DatePickerComponent({
          options: {
            displayMode: this.currentDisplayMode,
            dateOptions: {
              mode: this.currentDateMode,
              lunar: this.isLunar,
              start: new Date(1970, 0, 1),
              end: new Date(2100, 11, 31),
              selected: new Date(this.selectedYear, this.selectedMonth, this.selectedDay),
              loop: this.canLoop,
              enableHapticFeedback: this.enableHaptic,
              onChange: (result) => {
                this.addLog('onChange: ' + JSON.stringify(result))
                if (result.year !== undefined) this.selectedYear = result.year
                if (result.month !== undefined) this.selectedMonth = result.month
                if (result.day !== undefined) this.selectedDay = result.day
                if (result.hour !== undefined) this.selectedHour = result.hour
                if (result.minute !== undefined) this.selectedMinute = result.minute
                if (result.second !== undefined) this.selectedSecond = result.second
              },
              onScrollStop: (result) => {
                this.addLog('onScrollStop: ' + JSON.stringify(result))
              }
            },
            timeOptions: {
              format: this.currentTimeFormat,
              selected: new Date(this.selectedYear, this.selectedMonth, this.selectedDay, this.selectedHour, this.selectedMinute, this.selectedSecond),
              useMilitaryTime: this.isMilitaryTime,
              loop: this.canLoop,
              enableHapticFeedback: this.enableHaptic,
              onChange: (result) => {
                this.addLog('Time onChange: ' + JSON.stringify(result))
                if (result.hour !== undefined) this.selectedHour = result.hour
                if (result.minute !== undefined) this.selectedMinute = result.minute
                if (result.second !== undefined) this.selectedSecond = result.second
              },
              onScrollStop: (result) => {
                this.addLog('Time onScrollStop: ' + JSON.stringify(result))
              }
            }
          }
        })
        .width('90%')
        .height(200)

        Column() {
          Text('Selected Value')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 20, bottom: 10 })

          if (this.currentDisplayMode === DisplayMode.DATE || this.currentDisplayMode === DisplayMode.DATE_TIME) {
            Text(`Year: ${this.selectedYear} | Month: ${this.selectedMonth + 1} | Day: ${this.selectedDay}`)
              .fontSize(14)
              .margin({ bottom: 5 })
          }

          if (this.currentDisplayMode === DisplayMode.TIME || this.currentDisplayMode === DisplayMode.DATE_TIME) {
            if (this.currentTimeFormat === TimeFormat.HOUR_MINUTE) {
              Text(`Hour: ${this.selectedHour} | Minute: ${this.selectedMinute}`)
                .fontSize(14)
                .margin({ bottom: 5 })
            } else {
              Text(`Hour: ${this.selectedHour} | Minute: ${this.selectedMinute} | Second: ${this.selectedSecond}`)
                .fontSize(14)
                .margin({ bottom: 5 })
            }
          }
        }
        .width('90%')
        .padding(10)
        .backgroundColor('#FFF9E6')
        .borderRadius(8)
        .margin({ top: 20 })

        Column() {
          Text('Event Log:')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ bottom: 10 })

          Scroll() {
            Text(this.logText)
              .fontSize(12)
              .fontColor('#333333')
              .width('100%')
          }
          .height(100)
          .width('100%')
        }
        .width('90%')
        .margin({ top: 20 })
        .padding(16)
        .backgroundColor('#FAFAFA')
        .borderRadius(12)

        Button('Back to Index')
          .margin({ top: 30, bottom: 20 })
          .onClick(() => {
            router.back()
          })
      }
      .width('100%')
      .padding(20)
      .backgroundColor('#F5F5F5')
    }
    .width('100%')
    .height('100%')
    .scrollBar(BarState.Auto)
    .edgeEffect(EdgeEffect.Spring)
  }

  private getDateModeText(): string {
    if (this.currentDateMode === DateMode.DATE) return 'DATE'
    if (this.currentDateMode === DateMode.YEAR_AND_MONTH) return 'YEAR_MONTH'
    if (this.currentDateMode === DateMode.MONTH_AND_DAY) return 'MONTH_DAY'
    return 'UNKNOWN'
  }

  private getDisplayModeText(): string {
    if (this.currentDisplayMode === DisplayMode.DATE) return 'DATE'
    if (this.currentDisplayMode === DisplayMode.TIME) return 'TIME'
    if (this.currentDisplayMode === DisplayMode.DATE_TIME) return 'DATE_TIME'
    return 'UNKNOWN'
  }

  addLog(message: string) {
    const timestamp = new Date().toLocaleTimeString()
    this.logText = `[${timestamp}] ${message}\n` + this.logText
  }
}