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
struct DatePickerDialogExample006 {
  @State selectedDate: Date = new Date('2025-06-15');
  @State enableHapticFeedback: boolean = true;
  @State logText: string = '';

  build() {
    Column() {
      Text('DatePickerDialog HapticFeedback (SDK 16+)')
        .fontSize(24)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 20, bottom: 10 });

      Text('Enable or disable haptic feedback for the dialog')
        .fontSize(14)
        .fontColor('#666666')
        .margin({ bottom: 20 });

      Column() {
        Text('Haptic Feedback Settings')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .margin({ bottom: 15 });

        Row() {
          Text('Enable Haptic Feedback: ')
            .fontSize(14);
          Toggle({ isOn: this.enableHapticFeedback, type: ToggleType.Switch })
            .onChange((isOn: boolean) => {
              this.enableHapticFeedback = isOn;
              this.addLog('Haptic Feedback: ' + (isOn ? 'Enabled' : 'Disabled'));
            });
        }
        .margin({ bottom: 15 });

        Text('Current Status: ' + (this.enableHapticFeedback ? 'Enabled' : 'Disabled'))
          .fontSize(14)
          .fontColor(this.enableHapticFeedback ? '#52C41A' : '#FF4D4F')
          .fontWeight(FontWeight.Medium);
      }
      .width('90%')
      .padding(16)
      .backgroundColor('#F5F5F5')
      .borderRadius(12)
      .margin({ bottom: 20 });

      Column() {
        Text('About Haptic Feedback:')
          .fontSize(14)
          .fontWeight(FontWeight.Medium)
          .margin({ bottom: 8 });

        Text('When enabled, the DatePickerDialog provides haptic feedback when the user interacts with the picker (scrolling, selecting dates, etc.). This enhances the user experience by providing tactile confirmation.')
          .fontSize(12)
          .fontColor('#666666')
          .textAlign(TextAlign.Start);

        Text('')
          .height(8);

        Text('Note: To enable haptic feedback, you must declare the ohos.permission.VIBRATE permission in your module.json5 file.')
          .fontSize(11)
          .fontColor('#FF4D4F')
          .textAlign(TextAlign.Start);
      }
      .width('90%')
      .padding(16)
      .backgroundColor('#FFF7E6')
      .borderRadius(12)
      .margin({ bottom: 20 });

      Column() {
        Text('Try It:')
          .fontSize(14)
          .fontWeight(FontWeight.Medium)
          .margin({ bottom: 8 });

        Text('1. Toggle haptic feedback on/off')
          .fontSize(12)
          .fontColor('#666666')
          .margin({ bottom: 4 });
        Text('2. Open the dialog')
          .fontSize(12)
          .fontColor('#666666')
          .margin({ bottom: 4 });
        Text('3. Scroll through dates')
          .fontSize(12)
          .fontColor('#666666')
          .margin({ bottom: 4 });
        Text('4. Select a date')
          .fontSize(12)
          .fontColor('#666666')
          .margin({ bottom: 4 });
        Text('5. Compare the tactile experience')
          .fontSize(12)
          .fontColor('#666666');
      }
      .width('90%')
      .padding(16)
      .backgroundColor('#E6F7FF')
      .borderRadius(12)
      .margin({ bottom: 20 });

      Column() {
        Text('Selected Date:')
          .fontSize(14)
          .fontWeight(FontWeight.Medium)
          .margin({ bottom: 8 });

        Text(this.formatDate(this.selectedDate))
          .fontSize(20)
          .fontColor('#1890FF')
          .fontWeight(FontWeight.Bold);
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
        .height(60);
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
      enableHapticFeedback: this.enableHapticFeedback,
      onDateAccept: (value: Date) => {
        this.selectedDate = value;
        this.addLog('onDateAccept: ' + this.formatDate(value));
        if (this.enableHapticFeedback) {
          this.addLog('Haptic feedback triggered on accept');
        }
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
