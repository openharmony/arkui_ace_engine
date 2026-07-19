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
struct DatePickerComponentExample001 {
  @State selectedYear: number = 2026
  @State selectedMonth: number = 0
  @State selectedDay: number = 1
  @State selectedHour: number = 14
  @State selectedMinute: number = 30
  @State selectedSecond: number = 0
  @State canLoop: boolean = true
  @State enableHaptic: boolean = true
  @State logText: string = ''

  build() {
    Scroll() {
      Column() {
        Text('DatePickerComponent Basic Example')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 20 });

        Text('Basic DatePickerComponent with default settings')
          .fontSize(14)
          .fontColor('#666666')
          .margin({ bottom: 20 });

        Column() {
          Text('Configuration')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ bottom: 10 });

          Row() {
            Text('Loop:').fontSize(14).width(100)
            Toggle({ type: ToggleType.Switch, isOn: this.canLoop })
              .onChange((isOn: boolean) => {
                this.canLoop = isOn
                this.addLog('Loop: ' + (isOn ? 'ON' : 'OFF'))
              })
              .selectedColor('#007DFF')
            Text(this.canLoop ? 'ON' : 'OFF').fontSize(14).margin({ left: 10 })
          }
          .width('100%')
          .margin({ bottom: 10 })

          Row() {
            Text('Haptic:').fontSize(14).width(100)
            Toggle({ type: ToggleType.Switch, isOn: this.enableHaptic })
              .onChange((isOn: boolean) => {
                this.enableHaptic = isOn
                this.addLog('Haptic: ' + (isOn ? 'ON' : 'OFF'))
              })
              .selectedColor('#007DFF')
            Text(this.enableHaptic ? 'ON' : 'OFF').fontSize(14).margin({ left: 10 })
          }
          .width('100%')
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
              mode: DateMode.DATE,
              lunar: false,
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

          Text(`Year: ${this.selectedYear} | Month: ${this.selectedMonth + 1} | Day: ${this.selectedDay}`)
            .fontSize(20)
            .fontColor('#1890FF')
            .fontWeight(FontWeight.Bold);
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