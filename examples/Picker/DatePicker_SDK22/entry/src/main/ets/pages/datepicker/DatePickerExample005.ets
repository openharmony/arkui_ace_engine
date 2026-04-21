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

type DateOrderType = 'yMMMd' | 'MMd' | 'dMM';

@Entry
@Component
struct DatePickerExample005 {
  @State selectedDate: Date = new Date('2025-06-15');
  @State currentDateOrder: DateOrderType = 'yMMMd';
  @State logText: string = '';

  private dateOrderOptions: DateOrderType[] = ['yMMMd', 'MMd', 'dMM'];
  private dateOrderNames: string[] = [
    'Year-Month-Day (yMMMd)',
    'Month-Day (MMd)',
    'Day-Month (dMM)'
  ];
  @State currentIndex: number = 0;

  build() {
    Column() {
      Text('DatePicker DateOrder (SDK 22)')
        .fontSize(24)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 20, bottom: 10 });

      Text('Set the order of date display')
        .fontSize(14)
        .fontColor('#666666')
        .margin({ bottom: 20 });

      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2100-12-31'),
        selected: this.selectedDate
      })
        .dateOrder(this.currentDateOrder)
        .onDateChange((value: Date) => {
          this.selectedDate = value;
          this.addLog('Date changed: ' + value.toDateString());
        })
        .width('90%')
        .height(200);

      Column() {
        Text('Current Date Order:')
          .fontSize(18)
          .fontWeight(FontWeight.Medium)
          .margin({ bottom: 10 });

        Text(this.dateOrderNames[this.currentIndex])
          .fontSize(20)
          .fontColor('#1890FF')
          .fontWeight(FontWeight.Bold)
          .margin({ bottom: 15 });

        Text('The dateOrder property defines how dates are displayed in the picker.')
          .fontSize(12)
          .fontColor('#666666')
          .textAlign(TextAlign.Center)
          .margin({ bottom: 15 });

        Row() {
          Button('Previous')
            .onClick(() => {
              this.currentIndex = (this.currentIndex - 1 + this.dateOrderOptions.length) % this.dateOrderOptions.length;
              this.currentDateOrder = this.dateOrderOptions[this.currentIndex];
              this.addLog('DateOrder changed to: ' + this.dateOrderNames[this.currentIndex]);
            })
            .margin(8);

          Button('Next')
            .onClick(() => {
              this.currentIndex = (this.currentIndex + 1) % this.dateOrderOptions.length;
              this.currentDateOrder = this.dateOrderOptions[this.currentIndex];
              this.addLog('DateOrder changed to: ' + this.dateOrderNames[this.currentIndex]);
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
        Text('DateOrder Options:')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .margin({ bottom: 10 });

        ForEach(this.dateOrderNames, (name: string, index: number) => {
          Button(name)
            .onClick(() => {
              this.currentIndex = index;
              this.currentDateOrder = this.dateOrderOptions[index];
              this.addLog('DateOrder changed to: ' + name);
            })
            .margin(4)
            .width('90%');
        })
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
