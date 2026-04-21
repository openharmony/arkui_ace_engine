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

@Entry
@Component
struct DatePickerExample003 {
  @State selectedDate: Date = new Date('2025-06-15');
  @State currentMode: DatePickerMode = DatePickerMode.DATE;
  @State isLunar: boolean = false;
  @State logText: string = '';

  private modeOptions: DatePickerMode[] = [
    DatePickerMode.DATE,
    DatePickerMode.YEAR_AND_MONTH,
    DatePickerMode.MONTH_AND_DAY
  ];

  private modeNames: string[] = [
    'Full Date (Y-M-D)',
    'Year & Month',
    'Month & Day'
  ];

  @State currentModeIndex: number = 0;

  build() {
    Column() {
      Text('DatePicker Mode Example')
        .fontSize(24)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 20, bottom: 10 });

      Text('Different picker display modes')
        .fontSize(14)
        .fontColor('#666666')
        .margin({ bottom: 20 });

      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2100-12-31'),
        selected: this.selectedDate,
        mode: this.currentMode
      })
        .lunar(this.isLunar)
        .onDateChange((value: Date) => {
          this.selectedDate = value;
          this.addLog('Date changed: ' + value.toDateString());
        })
        .width('90%')
        .height(180);

      Column() {
        Text('Current Mode: ' + this.modeNames[this.currentModeIndex])
          .fontSize(18)
          .fontWeight(FontWeight.Medium)
          .margin({ bottom: 15 });

        Row() {
          Button('Previous Mode')
            .onClick(() => {
              this.currentModeIndex = (this.currentModeIndex - 1 + this.modeOptions.length) % this.modeOptions.length;
              this.currentMode = this.modeOptions[this.currentModeIndex];
              this.addLog('Mode changed to: ' + this.modeNames[this.currentModeIndex]);
            })
            .margin(8);

          Button('Next Mode')
            .onClick(() => {
              this.currentModeIndex = (this.currentModeIndex + 1) % this.modeOptions.length;
              this.currentMode = this.modeOptions[this.currentModeIndex];
              this.addLog('Mode changed to: ' + this.modeNames[this.currentModeIndex]);
            })
            .margin(8);
        }
      }
      .width('90%')
      .margin({ top: 25 })
      .padding(16)
      .backgroundColor('#F5F5F5')
      .borderRadius(12);

      Column() {
        Text('Calendar Type:')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .margin({ bottom: 10 });

        Row() {
          Button(this.isLunar ? 'Switch to Gregorian' : 'Switch to Lunar')
            .onClick(() => {
              this.isLunar = !this.isLunar;
              this.addLog('Calendar type: ' + (this.isLunar ? 'Lunar' : 'Gregorian'));
            })
            .margin(8);
        }
      }
      .width('90%')
      .margin({ top: 15 })
      .padding(16)
      .backgroundColor('#F5F5F5')
      .borderRadius(12);

      Column() {
        Text('Selected Date:')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .margin({ bottom: 8 });

        Text(this.formatDate(this.selectedDate))
          .fontSize(20)
          .fontColor('#1890FF')
          .fontWeight(FontWeight.Bold);
      }
      .width('90%')
      .margin({ top: 15 })
      .padding(16)
      .backgroundColor('#E6F7FF')
      .borderRadius(12);

      Column() {
        Text('Event Log:')
          .fontSize(14)
          .fontWeight(FontWeight.Medium)
          .margin({ bottom: 8 });

        Text(this.logText)
          .fontSize(12)
          .fontColor('#333333')
          .width('100%')
      }
      .width('90%')
      .margin({ top: 15 })
      .padding(12)
      .backgroundColor('#FAFAFA')
      .borderRadius(8);

      Button('Back to Index')
        .margin({ top: 30, bottom: 30 })
        .onClick(() => {
          router.back();
        });
    }
    .width('100%')
    .padding(16);
  }
  .height('100%')
  .backgroundColor('#FFFFFF');

  formatDate(date: Date): string {
    const year = date.getFullYear();
    const month = String(date.getMonth() + 1).padStart(2, '0');
    const day = String(date.getDate()).padStart(2, '0');
    return `${year}-${month}-${day}`;
  }

  addLog(message: string) {
    const timestamp = new Date().toLocaleTimeString();
    this.logText = `[${timestamp}] ${message}\n` + this.logText;
  }
}
