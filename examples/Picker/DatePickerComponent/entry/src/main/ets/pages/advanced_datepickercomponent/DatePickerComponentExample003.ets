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
struct DatePickerComponentExample003 {
  @State currentDateMode: DateMode = DateMode.DATE
  @State selectedYear: number = 2026
  @State selectedMonth: number = 0
  @State selectedDay: number = 1
  @State logText: string = ''

  build() {
    Scroll() {
      Column() {
        Text('DatePickerComponent DateMode Example')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 20 });

        Text('Different date picker modes: DATE, YEAR_MONTH, MONTH_DAY')
          .fontSize(14)
          .fontColor('#666666')
          .margin({ bottom: 20 });

        Column() {
          Text('Date Mode Selection')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ bottom: 10 });

          Row() {
            Button('DATE')
              .width(100)
              .type(this.currentDateMode === DateMode.DATE ? ButtonType.Capsule : ButtonType.Normal)
              .backgroundColor(this.currentDateMode === DateMode.DATE ? '#007DFF' : '#E0E0E0')
              .onClick(() => {
                this.currentDateMode = DateMode.DATE
                this.addLog('Mode: DATE (Year-Month-Day)')
              })
              .margin(4)

            Button('YEAR_MONTH')
              .width(100)
              .type(this.currentDateMode === DateMode.YEAR_AND_MONTH ? ButtonType.Capsule : ButtonType.Normal)
              .backgroundColor(this.currentDateMode === DateMode.YEAR_AND_MONTH ? '#007DFF' : '#E0E0E0')
              .onClick(() => {
                this.currentDateMode = DateMode.YEAR_AND_MONTH
                this.addLog('Mode: YEAR_MONTH')
              })
              .margin(4)

            Button('MONTH_DAY')
              .width(100)
              .type(this.currentDateMode === DateMode.MONTH_AND_DAY ? ButtonType.Capsule : ButtonType.Normal)
              .backgroundColor(this.currentDateMode === DateMode.MONTH_AND_DAY ? '#007DFF' : '#E0E0E0')
              .onClick(() => {
                this.currentDateMode = DateMode.MONTH_AND_DAY
                this.addLog('Mode: MONTH_DAY')
              })
              .margin(4)
          }
        }
        .width('90%')
        .padding(12)
        .backgroundColor('#F5F5F5')
        .borderRadius(8);

        Text('DatePickerComponent')
          .fontSize(18)
          .fontWeight(FontWeight.Medium)
          .margin({ top: 20, bottom: 10 });

        DatePickerComponent({
          options: {
            displayMode: DisplayMode.DATE,
            dateOptions: {
              mode: this.currentDateMode,
              lunar: false,
              start: new Date(1970, 0, 1),
              end: new Date(2100, 11, 31),
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
            .margin({ top: 20, bottom: 10 });

          if (this.currentDateMode === DateMode.DATE) {
            Text(`Year: ${this.selectedYear} | Month: ${this.selectedMonth + 1} | Day: ${this.selectedDay}`)
              .fontSize(20)
              .fontColor('#1890FF')
              .fontWeight(FontWeight.Bold);
          } else if (this.currentDateMode === DateMode.YEAR_AND_MONTH) {
            Text(`Year: ${this.selectedYear} | Month: ${this.selectedMonth + 1}`)
              .fontSize(20)
              .fontColor('#1890FF')
              .fontWeight(FontWeight.Bold);
          } else if (this.currentDateMode === DateMode.MONTH_AND_DAY) {
            Text(`Month: ${this.selectedMonth + 1} | Day: ${this.selectedDay}`)
              .fontSize(20)
              .fontColor('#1890FF')
              .fontWeight(FontWeight.Bold);
            Text('(Year fixed at 2026)')
              .fontSize(14)
              .fontColor('#FF9800')
              .margin({ top: 5 })
          }
        }
        .width('90%')
        .margin({ top: 20 })
        .padding(16)
        .backgroundColor('#F5F5F5')
        .borderRadius(12);

        Column() {
          Text('Event Log:')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ bottom: 10 });

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
        .borderRadius(12);

        Button('Back to Index')
          .margin({ top: 30, bottom: 20 })
          .onClick(() => {
            router.back();
          });
      }
      .width('100%')
      .padding(16);
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#FFFFFF');
  }

  addLog(message: string) {
    const timestamp = new Date().toLocaleTimeString();
    this.logText = `[${timestamp}] ${message}\n` + this.logText;
  }
}