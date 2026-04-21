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
struct DatePickerExample001 {
  @State isLunar: boolean = false;
  @State selectedDate: Date = new Date('2025-01-15');
  @State logText: string = '';

  build() {
    Column() {
      Text('DatePicker Basic Example')
        .fontSize(24)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 20, bottom: 20 });

      Text('Toggle between lunar and gregorian calendar')
        .fontSize(14)
        .fontColor('#666666')
        .margin({ bottom: 20 });

      Button('Switch to ' + (this.isLunar ? 'Gregorian' : 'Lunar'))
        .margin({ bottom: 30 })
        .onClick(() => {
          this.isLunar = !this.isLunar;
          this.addLog('Calendar switched to: ' + (this.isLunar ? 'Lunar' : 'Gregorian'));
        });

      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2100-12-31'),
        selected: this.selectedDate
      })
        .lunar(this.isLunar)
        .onDateChange((value: Date) => {
          this.selectedDate = value;
          this.addLog('Date changed to: ' + value.toDateString());
        })
        .width('90%')
        .height(200);

      Column() {
        Text('Selected Date:')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .margin({ top: 30, bottom: 10 });

        Text(this.formatDate(this.selectedDate))
          .fontSize(20)
          .fontColor('#1890FF')
          .fontWeight(FontWeight.Bold);
      }
      .width('90%')
      .margin({ top: 30 })
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
    .height('100%')
    .backgroundColor('#FFFFFF');
  }

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
