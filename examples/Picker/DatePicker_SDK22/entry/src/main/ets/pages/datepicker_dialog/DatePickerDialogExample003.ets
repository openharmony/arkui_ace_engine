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
struct DatePickerDialogExample003 {
  @State selectedDate: Date = new Date('2025-06-15');
  @State isLunar: boolean = false;
  @State logText: string = '';

  build() {
    Column() {
      Text('DatePickerDialog Lunar Example')
        .fontSize(24)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 20, bottom: 10 });

      Text('Toggle between lunar and gregorian calendar')
        .fontSize(14)
        .fontColor('#666666')
        .margin({ bottom: 20 });

      Row() {
        Text('Current: ')
          .fontSize(16);
        Text(this.isLunar ? 'Lunar Calendar' : 'Gregorian Calendar')
          .fontSize(16)
          .fontColor('#1890FF')
          .fontWeight(FontWeight.Bold);
      }
      .margin({ bottom: 20 });

      Column() {
        Text('Calendar Type:')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .margin({ bottom: 10 });

        Row() {
          Button(this.isLunar ? 'Switch to Gregorian' : 'Switch to Lunar')
            .onClick(() => {
              this.isLunar = !this.isLunar;
              this.addLog('Calendar: ' + (this.isLunar ? 'Lunar' : 'Gregorian'));
            })
            .margin(8);
        }
      }
      .width('90%')
      .padding(16)
      .backgroundColor('#F5F5F5')
      .borderRadius(12)
      .margin({ bottom: 20 });

      Column() {
        Text('Selected Date:')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .margin({ bottom: 8 });

        Text(this.formatDate(this.selectedDate))
          .fontSize(28)
          .fontColor('#1890FF')
          .fontWeight(FontWeight.Bold);
      }
      .width('90%')
      .padding(20)
      .backgroundColor('#E6F7FF')
      .borderRadius(12)
      .margin({ bottom: 20 });

      Button('Show DatePickerDialog')
        .width('90%')
        .height(50)
        .fontSize(18)
        .onClick(() => {
          this.showDatePickerDialog();
        });

      Column() {
        Text('About Lunar Calendar:')
          .fontSize(14)
          .fontWeight(FontWeight.Medium)
          .margin({ bottom: 8 });

        Text('The lunar calendar displays dates according to the traditional Chinese lunar calendar system. When enabled, users can select dates using lunar calendar notation.')
          .fontSize(12)
          .fontColor('#666666')
          .textAlign(TextAlign.Start);
      }
      .width('90%')
      .margin({ top: 20 })
      .padding(16)
      .backgroundColor('#FFF7E6')
      .borderRadius(12);

      Column() {
        Text('Event Log:')
          .fontSize(14)
          .fontWeight(FontWeight.Medium)
          .margin({ bottom: 8 });

        Scroll() {
          Text(this.logText)
            .fontSize(12)
            .fontColor('#333333')
            .width('100%');
        }
        .height(80);
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
    .height('100%')
    .padding(16)
    .backgroundColor('#FFFFFF');
  }

  showDatePickerDialog(): void {
    DatePickerDialog.show({
      start: new Date('2000-1-1'),
      end: new Date('2100-12-31'),
      selected: this.selectedDate,
      showTime: true,
      lunar: this.isLunar,
      onDateAccept: (value: Date) => {
        this.selectedDate = value;
        this.addLog('onDateAccept: ' + this.formatDate(value));
      },
      onCancel: () => {
        this.addLog('onCancel');
      },
      onDateChange: (value: Date) => {
        this.addLog('onDateChange: ' + this.formatDate(value));
      }
    });
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
