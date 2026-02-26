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

class DatePickerModifier implements AttributeModifier<DatePickerAttribute> {
  canLoop: boolean = false;
  backgroundColor: Color = Color.White;
  textColor: Color = Color.Black;

  constructor(loop: boolean, bgColor: Color, txtColor: Color) {
    this.canLoop = loop;
    this.backgroundColor = bgColor;
    this.textColor = txtColor;
  }

  applyNormalAttribute(instance: DatePickerAttribute): void {
    instance.canLoop(this.canLoop);
    instance.backgroundColor(this.backgroundColor);
    instance.textStyle({ color: this.textColor });
  }
}

@Entry
@Component
struct DatePickerExample004 {
  @State modifier: DatePickerModifier = new DatePickerModifier(false, Color.White, Color.Black);
  @State selectedDate: Date = new Date('2025-06-15');
  @State logText: string = '';

  build() {
    Column() {
      Text('DatePicker AttributeModifier Example')
        .fontSize(24)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 20, bottom: 10 });

      Text('Dynamically modify picker appearance')
        .fontSize(14)
        .fontColor('#666666')
        .margin({ bottom: 20 });

      DatePicker({
        start: new Date('1970-1-1'),
        end: new Date('2100-12-31'),
        selected: this.selectedDate
      })
        .attributeModifier(this.modifier)
        .onDateChange((value: Date) => {
          this.selectedDate = value;
          this.addLog('Date changed: ' + value.toDateString());
        })
        .width('90%')
        .height(200);

      Column() {
        Text('Loop Control')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .margin({ bottom: 10 });

        Row() {
          Button('Toggle Loop')
            .onClick(() => {
              this.modifier = new DatePickerModifier(
                !this.modifier.canLoop,
                this.modifier.backgroundColor,
                this.modifier.textColor
              );
              this.addLog('Loop: ' + (!this.modifier.canLoop ? 'Enabled' : 'Disabled'));
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
        Text('Background Color')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .margin({ bottom: 10 });

        Row() {
          Button('White').onClick(() => {
            this.modifier = new DatePickerModifier(
              this.modifier.canLoop,
              Color.White,
              this.modifier.textColor
            );
            this.addLog('Background: White');
          }).margin(4);

          Button('LightBlue').onClick(() => {
            this.modifier = new DatePickerModifier(
              this.modifier.canLoop,
              '#E6F7FF',
              this.modifier.textColor
            );
            this.addLog('Background: LightBlue');
          }).margin(4);

          Button('LightGreen').onClick(() => {
            this.modifier = new DatePickerModifier(
              this.modifier.canLoop,
              '#E8F5E9',
              this.modifier.textColor
            );
            this.addLog('Background: LightGreen');
          }).margin(4);
        }
      }
      .width('90%')
      .margin({ top: 15 })
      .padding(16)
      .backgroundColor('#F5F5F5')
      .borderRadius(12);

      Column() {
        Text('Text Color')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .margin({ bottom: 10 });

        Row() {
          Button('Black').onClick(() => {
            this.modifier = new DatePickerModifier(
              this.modifier.canLoop,
              this.modifier.backgroundColor,
              Color.Black
            );
            this.addLog('Text: Black');
          }).margin(4);

          Button('Blue').onClick(() => {
            this.modifier = new DatePickerModifier(
              this.modifier.canLoop,
              this.modifier.backgroundColor,
              Color.Blue
            );
            this.addLog('Text: Blue');
          }).margin(4);

          Button('Red').onClick(() => {
            this.modifier = new DatePickerModifier(
              this.modifier.canLoop,
              this.modifier.backgroundColor,
              Color.Red
            );
            this.addLog('Text: Red');
          }).margin(4);
        }
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

  addLog(message: string) {
    const timestamp = new Date().toLocaleTimeString();
    this.logText = `[${timestamp}] ${message}\n` + this.logText;
  }
}
