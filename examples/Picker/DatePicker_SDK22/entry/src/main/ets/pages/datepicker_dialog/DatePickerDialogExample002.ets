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
struct DatePickerDialogExample002 {
  @State selectedDate: Date = new Date('2025-06-15');
  @State logText: string = '';
  @State disappearTextColor: Color = Color.Gray;
  @State textColor: Color = Color.Black;
  @State selectedTextColor: Color = Color.Blue;

  build() {

  Column() {
      Text('DatePickerDialog TextStyle Example')
        .fontSize(24)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 20, bottom: 10 });

      Text('Customize dialog text styles')
        .fontSize(14)
        .fontColor('#666666')
        .margin({ bottom: 20 });

      Column() {
        Text('Style Controls')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .margin({ bottom: 10 });

        Text('Disappear Text (Top/Bottom items)')
          .fontSize(12)
          .fontColor('#666666')
          .margin({ bottom: 8 });

        Row() {
          Button('Gray').onClick(() => {
            this.disappearTextColor = Color.Gray;
            this.addLog('Disappear text: Gray');
          }).margin(4);
          Button('Red').onClick(() => {
            this.disappearTextColor = Color.Red;
            this.addLog('Disappear text: Red');
          }).margin(4);
          Button('Green').onClick(() => {
            this.disappearTextColor = Color.Green;
            this.addLog('Disappear text: Green');
          }).margin(4);
        }

        Text('Normal Text')
          .fontSize(12)
          .fontColor('#666666')
          .margin({ top: 12, bottom: 8 });

        Row() {
          Button('Black').onClick(() => {
            this.textColor = Color.Black;
            this.addLog('Normal text: Black');
          }).margin(4);
          Button('Blue').onClick(() => {
            this.textColor = Color.Blue;
            this.addLog('Normal text: Blue');
          }).margin(4);
          Button('Purple').onClick(() => {
            this.textColor = Color.Purple;
            this.addLog('Normal text: Purple');
          }).margin(4);
        }

        Text('Selected Text')
          .fontSize(12)
          .fontColor('#666666')
          .margin({ top: 12, bottom: 8 });

        Row() {
          Button('Blue').onClick(() => {
            this.selectedTextColor = Color.Blue;
            this.addLog('Selected text: Blue');
          }).margin(4);
          Button('Red').onClick(() => {
            this.selectedTextColor = Color.Red;
            this.addLog('Selected text: Red');
          }).margin(4);
          Button('Orange').onClick(() => {
            this.selectedTextColor = '#FFA500';
            this.addLog('Selected text: Orange');
          }).margin(4);
        }
      }
      .width('90%')
      .padding(16)
      .backgroundColor('#F5F5F5')
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
      .margin({ top: 25 })
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
      disappearTextStyle: {
        color: this.disappearTextColor,
        font: { size: '14fp', weight: FontWeight.Bold }
      },
      textStyle: {
        color: this.textColor,
        font: { size: '16fp', weight: FontWeight.Normal }
      },
      selectedTextStyle: {
        color: this.selectedTextColor,
        font: { size: '24fp', weight: FontWeight.Regular }
      },
      onDateAccept: (value: Date) => {
        this.selectedDate = value;
        this.addLog('onDateAccept: ' + this.formatDate(value));
      },
      onCancel: () => {
        this.addLog('onCancel');
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
