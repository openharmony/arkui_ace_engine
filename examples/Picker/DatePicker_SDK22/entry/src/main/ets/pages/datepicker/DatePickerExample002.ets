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
struct DatePickerExample002 {
  @State selectedDate: Date = new Date('2025-06-15');
  @State disappearTextColor: Color = Color.Gray;
  @State disappearTextSize: string = '16fp';
  @State disappearTextWeight: FontWeight = FontWeight.Bold;

  @State textColor: Color = Color.Black;
  @State textSize: string = '18fp';
  @State textWeight: FontWeight = FontWeight.Normal;

  @State selectedTextColor: Color = Color.Blue;
  @State selectedTextSize: string = '26fp';
  @State selectedTextWeight: FontWeight = FontWeight.Regular;
  @State selectedTextStyle: FontStyle = FontStyle.Normal;

  @State logText: string = '';

  build() {
    Scroll() {
      Column() {
        Text('DatePicker TextStyle Example')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 10 });

        Text('Customize appearance with text styles')
          .fontSize(14)
          .fontColor('#666666')
          .margin({ bottom: 20 });

        DatePicker({
          start: new Date('1970-1-1'),
          end: new Date('2100-12-31'),
          selected: this.selectedDate
        })
          .disappearTextStyle({
            color: this.disappearTextColor,
            font: { size: this.disappearTextSize, weight: this.disappearTextWeight }
          })
          .textStyle({
            color: this.textColor,
            font: { size: this.textSize, weight: this.textWeight }
          })
          .selectedTextStyle({
            color: this.selectedTextColor,
            font: { size: this.selectedTextSize, weight: this.selectedTextWeight, style: this.selectedTextStyle }
          })
          .onDateChange((value: Date) => {
            this.selectedDate = value;
            this.addLog('Date changed: ' + value.toDateString());
          })
          .width('90%')
          .height(220);

        Column() {
          Text('Disappear Text Style (Top/Bottom)')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ bottom: 10 });

          Row() {
            Button('Gray').onClick(() => {
              this.disappearTextColor = Color.Gray;
              this.addLog('Disappear text color: Gray');
            }).margin(4);
            Button('Red').onClick(() => {
              this.disappearTextColor = Color.Red;
              this.addLog('Disappear text color: Red');
            }).margin(4);
            Button('Green').onClick(() => {
              this.disappearTextColor = Color.Green;
              this.addLog('Disappear text color: Green');
            }).margin(4);
          }
        }
        .width('90%')
        .margin({ top: 20 })
        .padding(12)
        .backgroundColor('#F5F5F5')
        .borderRadius(8);

        Column() {
          Text('Normal Text Style')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ bottom: 10 });

          Row() {
            Button('Black').onClick(() => {
              this.textColor = Color.Black;
              this.addLog('Text color: Black');
            }).margin(4);
            Button('Blue').onClick(() => {
              this.textColor = Color.Blue;
              this.addLog('Text color: Blue');
            }).margin(4);
            Button('Purple').onClick(() => {
              this.textColor = Color.Purple;
              this.addLog('Text color: Purple');
            }).margin(4);
          }
        }
        .width('90%')
        .margin({ top: 12 })
        .padding(12)
        .backgroundColor('#F5F5F5')
        .borderRadius(8);

        Column() {
          Text('Selected Text Style')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .margin({ bottom: 10 });

          Row() {
            Button('Blue').onClick(() => {
              this.selectedTextColor = Color.Blue;
              this.addLog('Selected text color: Blue');
            }).margin(4);
            Button('Red').onClick(() => {
              this.selectedTextColor = Color.Red;
              this.addLog('Selected text color: Red');
            }).margin(4);
            Button('Orange').onClick(() => {
              this.selectedTextColor = '#FFA500';
              this.addLog('Selected text color: Orange');
            }).margin(4);
          }

          Row() {
            Button('Italic').onClick(() => {
              this.selectedTextStyle = FontStyle.Italic;
              this.addLog('Selected text style: Italic');
            }).margin(4);
            Button('Normal').onClick(() => {
              this.selectedTextStyle = FontStyle.Normal;
              this.addLog('Selected text style: Normal');
            }).margin(4);
          }
        }
        .width('90%')
        .margin({ top: 12 })
        .padding(12)
        .backgroundColor('#F5F5F5')
        .borderRadius(8);

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
        .margin({ top: 20 })
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
    .width('100%')
    .height('100%')
    .backgroundColor('#FFFFFF');
  }

  addLog(message: string) {
    const timestamp = new Date().toLocaleTimeString();
    this.logText = `[${timestamp}] ${message}\n` + this.logText;
  }
}
