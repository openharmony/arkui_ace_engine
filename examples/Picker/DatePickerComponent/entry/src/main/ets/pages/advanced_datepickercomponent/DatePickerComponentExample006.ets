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

import { DatePickerComponent, DateMode, DisplayMode, DatePickerComponentOptions, DateOptions } from '@ohos.arkui.advanced.DatePickerComponent'

@Entry
@Component
struct DatePickerComponentExample006 {
  @State startYear: number = 2000
  @State endYear: number = 2030
  @State selectedYear: number = 2026
  @State selectedMonth: number = 0
  @State selectedDay: number = 1
  @State minDate: Date = new Date(2000, 0, 1)
  @State maxDate: Date = new Date(2030, 11, 31)
  @State logText: string = ''

  build() {
    Scroll() {
      Column() {
        Text('DatePickerComponent Date Range Example')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 20 })

        Text('Dynamic date range configuration with interactive controls')
          .fontSize(14)
          .fontColor('#666666')
          .margin({ bottom: 20 })

        Column() {
          Text('Date Range Configuration')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ bottom: 10 })

          Row() {
            Text('Start Year:')
              .fontSize(14)
              .width(100)
            Text(`${this.startYear}`)
              .fontSize(14)
              .fontColor('#007DFF')
              .width(60)
            Button('-5')
              .width(50)
              .height(30)
              .onClick(() => {
                if (this.startYear > 1970) {
                  this.startYear -= 5
                  this.updateDateRange()
                  this.addLog('Start year decreased to: ' + this.startYear)
                }
              })
              .margin({ left: 5 })
            Button('+5')
              .width(50)
              .height(30)
              .onClick(() => {
                if (this.startYear < this.endYear - 10) {
                  this.startYear += 5
                  this.updateDateRange()
                  this.addLog('Start year increased to: ' + this.startYear)
                }
              })
              .margin({ left: 5 })
          }
          .width('100%')
          .justifyContent(FlexAlign.Start)
          .margin({ bottom: 10 })

          Row() {
            Text('End Year:')
              .fontSize(14)
              .width(100)
            Text(`${this.endYear}`)
              .fontSize(14)
              .fontColor('#007DFF')
              .width(60)
            Button('-5')
              .width(50)
              .height(30)
              .onClick(() => {
                if (this.endYear > this.startYear + 10) {
                  this.endYear -= 5
                  this.updateDateRange()
                  this.addLog('End year decreased to: ' + this.endYear)
                }
              })
              .margin({ left: 5 })
            Button('+5')
              .width(50)
              .height(30)
              .onClick(() => {
                if (this.endYear < 2100) {
                  this.endYear += 5
                  this.updateDateRange()
                  this.addLog('End year increased to: ' + this.endYear)
                }
              })
              .margin({ left: 5 })
          }
          .width('100%')
          .justifyContent(FlexAlign.Start)
          .margin({ bottom: 10 })

          Row() {
            Button('Set Range: 1970-2025')
              .fontSize(12)
              .height(30)
              .onClick(() => {
                this.startYear = 1970
                this.endYear = 2025
                this.updateDateRange()
                this.addLog('Range set: 1970-2025')
              })
              .margin(4)
            Button('Set Range: 2000-2100')
              .fontSize(12)
              .height(30)
              .onClick(() => {
                this.startYear = 2000
                this.endYear = 2100
                this.updateDateRange()
                this.addLog('Range set: 2000-2100')
              })
              .margin(4)
          }
          .width('100%')
        }
        .width('90%')
        .padding(12)
        .backgroundColor('#F5F5F5')
        .borderRadius(8)

        Column() {
          Text('Current Range: ' + this.startYear + ' - ' + this.endYear)
            .fontSize(14)
            .fontColor('#1890FF')
            .fontWeight(FontWeight.Medium)
            .margin({ top: 10 })

          Text('Total years: ' + (this.endYear - this.startYear + 1))
            .fontSize(12)
            .fontColor('#666666')
            .margin({ top: 5 })
        }
        .width('90%')
        .padding(10)
        .backgroundColor('#E8F4FF')
        .borderRadius(8)
        .margin({ top: 12 })

        Text('DatePickerComponent')
          .fontSize(18)
          .fontWeight(FontWeight.Medium)
          .margin({ top: 20, bottom: 10 })

        DatePickerComponent({
          options: {
            displayMode: DisplayMode.DATE,
            dateOptions: {
              mode: DateMode.DATE,
              lunar: false,
              start: this.minDate,
              end: this.maxDate,
              selected: new Date(this.selectedYear, this.selectedMonth, this.selectedDay),
              loop: true,
              enableHapticFeedback: true,
              onChange: (result) => {
                this.addLog('onChange: ' + JSON.stringify(result))
                if (result.year !== undefined) this.selectedYear = result.year
                if (result.month !== undefined) this.selectedMonth = result.month
                if (result.day !== undefined) this.selectedDay = result.day
              },
              onScrollStop: (result) => {
                this.addLog('onScrollStop: ' + JSON.stringify(result))
              }
            }
          }
        })
        .width('90%')
        .height(200)

        Column() {
          Text('Selected Date:')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 20, bottom: 10 })

          Text(`${this.selectedYear}-${String(this.selectedMonth + 1).padStart(2, '0')}-${String(this.selectedDay).padStart(2, '0')}`)
            .fontSize(20)
            .fontColor('#1890FF')
            .fontWeight(FontWeight.Bold)

          if (this.selectedYear < this.startYear || this.selectedYear > this.endYear) {
            Text('Warning: Selected date outside current range!')
              .fontSize(12)
              .fontColor('#FF0000')
              .margin({ top: 5 })
          }
        }
        .width('90%')
        .margin({ top: 20 })
        .padding(16)
        .backgroundColor('#F5F5F5')
        .borderRadius(12)

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
      .padding(16)
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#FFFFFF')
  }

  updateDateRange() {
    this.minDate = new Date(this.startYear, 0, 1)
    this.maxDate = new Date(this.endYear, 11, 31)
    if (this.selectedYear < this.startYear) {
      this.selectedYear = this.startYear
    }
    if (this.selectedYear > this.endYear) {
      this.selectedYear = this.endYear
    }
  }

  addLog(message: string) {
    const timestamp = new Date().toLocaleTimeString()
    this.logText = `[${timestamp}] ${message}\n` + this.logText
  }
}