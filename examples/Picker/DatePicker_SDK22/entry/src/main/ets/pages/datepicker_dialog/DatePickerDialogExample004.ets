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
struct DatePickerDialogExample004 {
  @State selectedDate: Date = new Date('2025-06-15');
  @State enableHoverMode: boolean = false;
  @State hoverModeArea: HoverModeAreaType = HoverModeAreaType.BOTTOM_SCREEN;
  @State logText: string = '';

  private hoverModeOptions: HoverModeAreaType[] = [
    HoverModeAreaType.BOTTOM_SCREEN,
    HoverModeAreaType.TOP_SCREEN
  ];
  private hoverModeNames: string[] = ['Bottom Screen', 'Top Screen'];

  @State currentIndex: number = 0;

  build() {
    Column() {
      Text('DatePickerDialog HoverMode (SDK 14+)')
        .fontSize(24)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 20, bottom: 10 });

      Text('Configure dialog display in hover mode')
        .fontSize(14)
        .fontColor('#666666')
        .margin({ bottom: 20 });

      Column() {
        Text('Hover Mode Settings')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .margin({ bottom: 15 });

        Row() {
          Text('Enable Hover Mode: ')
            .fontSize(14);
          Toggle({ isOn: this.enableHoverMode, type: ToggleType.Switch })
            .onChange((isOn: boolean) => {
              this.enableHoverMode = isOn;
              this.addLog('Hover Mode: ' + (isOn ? 'Enabled' : 'Disabled'));
            });
        }
        .margin({ bottom: 15 });

        if (this.enableHoverMode) {
          Text('Hover Mode Area:')
            .fontSize(14)
            .fontColor('#666666')
            .margin({ bottom: 10 });

          Row() {
            Button('Previous')
              .onClick(() => {
                this.currentIndex = (this.currentIndex - 1 + this.hoverModeOptions.length) % this.hoverModeOptions.length;
                this.hoverModeArea = this.hoverModeOptions[this.currentIndex];
                this.addLog('Hover Mode Area: ' + this.hoverModeNames[this.currentIndex]);
              })
              .margin(8);

            Text(this.hoverModeNames[this.currentIndex])
              .fontSize(14)
              .fontWeight(FontWeight.Medium);

            Button('Next')
              .onClick(() => {
                this.currentIndex = (this.currentIndex + 1) % this.hoverModeOptions.length;
                this.hoverModeArea = this.hoverModeOptions[this.currentIndex];
                this.addLog('Hover Mode Area: ' + this.hoverModeNames[this.currentIndex]);
              })
              .margin(8);
          }
        }
      }
      .width('90%')
      .padding(16)
      .backgroundColor('#F5F5F5')
      .borderRadius(12)
      .margin({ bottom: 20 });

      Column() {
        Text('About Hover Mode:')
          .fontSize(14)
          .fontWeight(FontWeight.Medium)
          .margin({ bottom: 8 });

        Text('Hover mode is typically used for 2-in-1 devices like tablets. When enabled, the dialog displays in a specific area of the screen rather than as a full modal dialog.')
          .fontSize(12)
          .fontColor('#666666')
          .textAlign(TextAlign.Start);
      }
      .width('90%')
      .padding(16)
      .backgroundColor('#FFF7E6')
      .borderRadius(12)
      .margin({ bottom: 20 });

      Column() {
        Text('Current Settings:')
          .fontSize(14)
          .fontWeight(FontWeight.Medium)
          .margin({ bottom: 8 });

        Text(`Hover Mode: ${this.enableHoverMode ? 'Enabled' : 'Disabled'}`)
          .fontSize(14)
          .margin({ bottom: 4 });

        if (this.enableHoverMode) {
          Text(`Hover Area: ${this.hoverModeNames[this.currentIndex]}`)
            .fontSize(14);
        }
      }
      .width('90%')
      .padding(16)
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
      enableHoverMode: this.enableHoverMode,
      hoverModeArea: this.hoverModeArea,
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
