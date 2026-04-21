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
struct DatePickerExample006 {
  @State selectedDate: Date = new Date('2025-06-15');
  @State enableHaptic: boolean = true;
  @State logText: string = '';

  build() {
    Column() {
      Text('DatePicker HapticFeedback (SDK 22)')
        .fontSize(24)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 20, bottom: 10 });

      Text('Enable or disable haptic feedback')
        .fontSize(14)
        .fontColor('#666666')
        .margin({ bottom: 20 });

      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2100-12-31'),
        selected: this.selectedDate
      })
        .enableHapticFeedback(this.enableHaptic)
        .onDateChange((value: Date) => {
          this.selectedDate = value;
          this.addLog('Date changed: ' + value.toDateString());
          if (this.enableHaptic) {
            this.addLog('Haptic feedback triggered');
          }
        })
        .width('90%')
        .height(200);

      Column() {
        Text('Haptic Feedback Control')
          .fontSize(18)
          .fontWeight(FontWeight.Medium)
          .margin({ bottom: 15 });

        Row() {
          Button(this.enableHaptic ? 'Disable Haptic' : 'Enable Haptic')
            .onClick(() => {
              this.enableHaptic = !this.enableHaptic;
              this.addLog('Haptic feedback: ' + (this.enableHaptic ? 'Enabled' : 'Disabled'));
            })
            .margin(8);
        }

        Text('Current Status: ' + (this.enableHaptic ? 'Enabled' : 'Disabled'))
          .fontSize(14)
          .fontColor(this.enableHaptic ? '#52C41A' : '#FF4D4F')
          .fontWeight(FontWeight.Medium)
          .margin({ top: 10 });
      }
      .width('90%')
      .margin({ top: 25 })
      .padding(16)
      .backgroundColor('#F5F5F5')
      .borderRadius(12);

      Column() {
        Text('About Haptic Feedback')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .margin({ bottom: 10 });

        Text('When enabled, the DatePicker provides haptic feedback when the user scrolls or selects a date. This enhances the user experience by providing tactile confirmation of interactions.')
          .fontSize(12)
          .fontColor('#666666')
          .textAlign(TextAlign.Start);
      }
      .width('90%')
      .margin({ top: 15 })
      .padding(16)
      .backgroundColor('#FFF7E6')
      .borderRadius(12);

      Column() {
        Text('Try It:')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .margin({ bottom: 10 });

        Text('1. Scroll through the date options')
          .fontSize(12)
          .fontColor('#666666')
          .margin({ bottom: 4 });
        Text('2. Select a different date')
          .fontSize(12)
          .fontColor('#666666')
          .margin({ bottom: 4 });
        Text('3. Toggle haptic feedback on/off')
          .fontSize(12)
          .fontColor('#666666')
          .margin({ bottom: 4 });
        Text('4. Compare the tactile experience')
          .fontSize(12)
          .fontColor('#666666');
      }
      .width('90%')
      .margin({ top: 15 })
      .padding(16)
      .backgroundColor('#E6F7FF')
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
      .backgroundColor('#F5F5F5')
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
