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

import { DatePickerComponent, DisplayMode, TimeFormat, DatePickerComponentOptions, TimeOptions } from '@ohos.arkui.advanced.DatePickerComponent'

@Entry
@Component
struct DatePickerComponentExample005 {
  @State currentTimeFormat: TimeFormat = TimeFormat.HOUR_MINUTE
  @State isMilitaryTime: boolean = false
  @State selectedHour: number = 14
  @State selectedMinute: number = 30
  @State selectedSecond: number = 0
  @State logText: string = ''

  build() {
    Scroll() {
      Column() {
        Text('DatePickerComponent TimeFormat Example')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 20 });

        Text('Time format options: HOUR_MINUTE, HOUR_MINUTE_SECOND')
          .fontSize(14)
          .fontColor('#666666')
          .margin({ bottom: 20 });

        Column() {
          Text('Time Format Selection')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ bottom: 10 });

          Row() {
            Button('H:M')
              .width(80)
              .type(this.currentTimeFormat === TimeFormat.HOUR_MINUTE ? ButtonType.Capsule : ButtonType.Normal)
              .backgroundColor(this.currentTimeFormat === TimeFormat.HOUR_MINUTE ? '#007DFF' : '#E0E0E0')
              .onClick(() => {
                this.currentTimeFormat = TimeFormat.HOUR_MINUTE
                this.addLog('Format: HOUR_MINUTE')
              })
              .margin(4)

            Button('H:M:S')
              .width(80)
              .type(this.currentTimeFormat === TimeFormat.HOUR_MINUTE_SECOND ? ButtonType.Capsule : ButtonType.Normal)
              .backgroundColor(this.currentTimeFormat === TimeFormat.HOUR_MINUTE_SECOND ? '#007DFF' : '#E0E0E0')
              .onClick(() => {
                this.currentTimeFormat = TimeFormat.HOUR_MINUTE_SECOND
                this.addLog('Format: HOUR_MINUTE_SECOND')
              })
              .margin(4)
          }
        }
        .width('90%')
        .padding(12)
        .backgroundColor('#F5F5F5')
        .borderRadius(8);

        Column() {
          Text('Time Display Format')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 12, bottom: 10 });

          Row() {
            Text('Military Time:').fontSize(14).width(120)
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
        }
        .width('90%')
        .padding(12)
        .backgroundColor('#F5F5F5')
        .borderRadius(8);

        Text('DatePickerComponent (TIME mode)')
          .fontSize(18)
          .fontWeight(FontWeight.Medium)
          .margin({ top: 20, bottom: 10 });

        DatePickerComponent({
          options: {
            displayMode: DisplayMode.TIME,
            timeOptions: {
              format: this.currentTimeFormat,
              selected: new Date(2026, 0, 1, this.selectedHour, this.selectedMinute, this.selectedSecond),
              useMilitaryTime: this.isMilitaryTime,
              loop: true,
              enableHapticFeedback: true,
              onChange: (result) => {
                this.addLog('onChange: ' + JSON.stringify(result))
                if (result.hour !== undefined) this.selectedHour = result.hour
                if (result.minute !== undefined) this.selectedMinute = result.minute
                if (result.second !== undefined) this.selectedSecond = result.second
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
          Text('Selected Time:')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ top: 20, bottom: 10 });

          if (this.currentTimeFormat === TimeFormat.HOUR_MINUTE) {
            Text(this.formatTimeHM(this.selectedHour, this.selectedMinute, this.isMilitaryTime))
              .fontSize(20)
              .fontColor('#1890FF')
              .fontWeight(FontWeight.Bold);
          } else {
            Text(this.formatTimeHMS(this.selectedHour, this.selectedMinute, this.selectedSecond, this.isMilitaryTime))
              .fontSize(20)
              .fontColor('#1890FF')
              .fontWeight(FontWeight.Bold);
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

  formatTimeHM(hour: number, minute: number, military: boolean): string {
    if (military) {
      return `${String(hour).padStart(2, '0')}:${String(minute).padStart(2, '0')}`;
    } else {
      const h = hour > 12 ? hour - 12 : hour;
      const ampm = hour >= 12 ? 'PM' : 'AM';
      return `${h}:${String(minute).padStart(2, '0')} ${ampm}`;
    }
  }

  formatTimeHMS(hour: number, minute: number, second: number, military: boolean): string {
    if (military) {
      return `${String(hour).padStart(2, '0')}:${String(minute).padStart(2, '0')}:${String(second).padStart(2, '0')}`;
    } else {
      const h = hour > 12 ? hour - 12 : hour;
      const ampm = hour >= 12 ? 'PM' : 'AM';
      return `${h}:${String(minute).padStart(2, '0')}:${String(second).padStart(2, '0')} ${ampm}`;
    }
  }

  addLog(message: string) {
    const timestamp = new Date().toLocaleTimeString();
    this.logText = `[${timestamp}] ${message}\n` + this.logText;
  }
}