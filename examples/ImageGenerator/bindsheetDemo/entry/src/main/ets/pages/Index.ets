/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License"),
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

import { hilog } from '@kit.PerformanceAnalysisKit';
import { componentUtils } from '@kit.ArkUI';
import { SheetDragTester } from './SheetDragTester';

const DOMAIN: number = 0x0000;
const TAG: string = 'BindSheetDemo';

interface SheetLogEntry {
  time: string;
  msg: string;
}

interface SheetState {
  isShow: boolean;
  detents: Array<number | SheetSize>;
  height: number | string;
  dragBar: boolean;
  backgroundColor: string;
  blurStyle: BlurStyle;
  mode: SheetMode;
  showClose: boolean;
  shouldDismiss: boolean;
  onWillDismissAction: boolean;
  UIScale: number;
  UIWidth: string;
  UIHeight: string;
  UIStart: string;
  UIOffset: string;
  UIShowClose: boolean;
  UIBackgroundColor: string;
  UIBlurStyle: BlurStyle;
  enableOutsideDeselect: boolean;
  onHeightDidChange: number;
  onWidthDidChange: number;
  onDetentDidChange: number;
  onOffsetDidChange: number;
  size: string;
}

interface SheetSize {
  height: string;
}

function formatTime(ts: number): string {
  let d = new Date(ts);
  let hh = d.getHours().toString().padStart(2, '0');
  let mm = d.getMinutes().toString().padStart(2, '0');
  let ss = d.getSeconds().toString().padStart(2, '0');
  let ms = d.getMilliseconds().toString().padStart(3, '0');
  return `${hh}:${mm}:${ss}.${ms}`;
}

@Entry
@Component
struct Index {
  @State isShow: boolean = false;
  @State isShow2: boolean = false;
  @State isShow3: boolean = false;
  @State isShow4: boolean = false;
  @State isShow5: boolean = false;
  @State sheetHeight: number | string = 300;
  @State dragBar: boolean = true;
  @State sheetBgColor: string = '#FFFFFF';
  @State sheetBlurStyle: BlurStyle = BlurStyle.NONE;
  @State sheetMode: SheetMode = SheetMode.OVERLAY;
  @State showClose: boolean = true;
  @State shouldDismiss: boolean = true;
  @State onWillDismissAction: boolean = true;
  @State UIScale: number = 0.8;
  @State UIWidth: string = '80%';
  @State UIHeight: string = '50%';
  @State UIStart: string = 'center';
  @State UIOffset: string = '0';
  @State UIShowClose: boolean = false;
  @State UIBackgroundColor: string = '#FFFFFF';
  @State UIBlurStyle: BlurStyle = BlurStyle.NONE;
  @State enableOutsideDeselect: boolean = false;
  @State onHeightDidChange: number = 0;
  @State onWidthDidChange: number = 0;
  @State onDetentDidChange: number = 0;
  @State onOffsetDidChange: number = 0;
  @State sheetSize: string = '300 x 400';
  @State detentsVal: Array<number | SheetSize> = [200, 300, 400];
  @State logList: SheetLogEntry[] = [];
  @State currentDetentIndex: number = 1;
  @State dragOffsetY: number = 0;
  @State isDragging: boolean = false;
  @State startTouchY: number = 0;
  @State sheetContentHeight: number = 300;
  @State customDetentHeight: number = 300;
  @State enableScroll: boolean = true;
  @State sheetTitle: string = 'Sheet Title';
  @State contentText: string = 'This is the sheet content for testing drag and resize behavior.';

  private logCount: number = 0;
  private maxLogCount: number = 100;

  addLog(msg: string): void {
    let entry: SheetLogEntry = { time: formatTime(Date.now()), msg: msg };
    this.logList.push(entry);
    if (this.logList.length > this.maxLogCount) {
      this.logList.shift();
    }
    hilog.info(DOMAIN, TAG, msg);
  }

  clearLog(): void {
    this.logList = [];
    this.addLog('Logs cleared');
  }

  build() {
    Column() {
      // Header
      Row() {
        Text('BindSheet Demo')
          .fontSize(22)
          .fontWeight(FontWeight.Bold)
          .margin({ left: 16 })
        Blank()
        Button('Clear Log')
          .height(32)
          .fontSize(12)
          .margin({ right: 16 })
          .onClick(() => { this.clearLog(); })
      }
      .width('100%')
      .height(50)
      .backgroundColor('#F1F3F5')

      // Scrollable content area
      Scroll() {
        Column({ space: 8 }) {
          // Section 1: Basic BindSheet
          this.buildBasicSection()

          // Section 2: Detents (drag snap points)
          this.buildDetentsSection()

          // Section 3: Drag Bar control
          this.buildDragBarSection()

          // Section 4: Background and blur
          this.buildBackgroundSection()

          // Section 5: Mode and dismiss
          this.buildModeSection()

          // Section 6: UI properties
          this.buildUISection()

          // Section 7: Callbacks
          this.buildCallbackSection()

          // Section 8: Custom drag resize
          this.buildCustomDragSection()

          // Section 9: Multiple sheets
          this.buildMultipleSheetsSection()

          // Section 10: Advanced drag tester
          this.buildAdvancedTesterSection()

          // Section 11: Log display
          this.buildLogSection()
        }
        .width('100%')
        .padding(8)
      }
      .layoutWeight(1)
      .width('100%')
    }
    .width('100%')
    .height('100%')
    .bindSheet($$this.isShow, this.builderSheetContent(), {
      height: this.sheetHeight,
      dragBar: this.dragBar,
      backgroundColor: this.sheetBgColor,
      blurStyle: this.sheetBlurStyle,
      detents: this.detentsVal,
      mode: this.sheetMode,
      showClose: this.showClose,
      shouldDismiss: this.shouldDismiss,
      onWillDismiss: this.onWillDismissAction ? (sheetDismiss: SheetDismiss) => {
        this.addLog('onWillDismiss triggered');
        sheetDismiss.dismiss();
      } : undefined,
      onHeightDidChange: (height: number) => {
        this.onHeightDidChange = height;
        this.addLog(`onHeightDidChange: ${height}`);
      },
      onWidthDidChange: (width: number) => {
        this.onWidthDidChange = width;
        this.addLog(`onWidthDidChange: ${width}`);
      },
      onDetentDidChange: (detent: number) => {
        this.onDetentDidChange = detent;
        this.addLog(`onDetentDidChange: ${detent}`);
      },
      onOffsetDidChange: (offset: number) => {
        this.onOffsetDidChange = offset;
        this.addLog(`onOffsetDidChange: ${offset}`);
      },
      onDisappear: () => {
        this.addLog('onDisappear triggered');
      },
    })
    .bindSheet($$this.isShow2, this.builderSheetContent2(), {
      height: '50%',
      dragBar: true,
      backgroundColor: '#F0F0FF',
      detents: [SheetSize.height('30%'), SheetSize.height('50%'), SheetSize.height('80%')],
      mode: SheetMode.EMBEDDED,
      showClose: true,
    })
    .bindSheet($$this.isShow3, this.builderSheetContent3(), {
      height: 400,
      dragBar: false,
      backgroundColor: '#FFF0F0',
      detents: [300, 400, 500],
      mode: SheetMode.OVERLAY,
      showClose: false,
    })
    .bindSheet($$this.isShow4, this.builderSheetContent4(), {
      height: '60%',
      dragBar: true,
      backgroundColor: '#F0FFF0',
      detents: [200, 400, 600],
      mode: SheetMode.AUTO,
      showClose: true,
      uiOption: {
        scale: this.UIScale,
        width: this.UIWidth,
        height: this.UIHeight,
        start: this.UIStart,
        offset: this.UIOffset,
        showClose: this.UIShowClose,
        backgroundColor: this.UIBackgroundColor,
        blurStyle: this.UIBlurStyle,
        enableOutsideDeselect: this.enableOutsideDeselect,
      },
    })
    .bindSheet($$this.isShow5, this.builderSheetContent5(), {
      height: '40%',
      dragBar: true,
      backgroundColor: '#FFFAF0',
      detents: [SheetSize.height('20%'), SheetSize.height('40%'), SheetSize.height('70%')],
      mode: SheetMode.OVERLAY,
      showClose: true,
    })
  }

  @Builder
  builderSheetContent() {
    Column() {
      Text(this.sheetTitle)
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 16, bottom: 8 })

      Text(this.contentText)
        .fontSize(14)
        .margin({ bottom: 16 })
        .textAlign(TextAlign.Center)

      Row({ space: 12 }) {
        Button('Close Sheet')
          .onClick(() => {
            this.isShow = false;
            this.addLog('Sheet closed by button');
          })
        Button('Change Height')
          .onClick(() => {
            this.sheetHeight = this.sheetHeight === 300 ? 500 : 300;
            this.addLog(`Height changed to ${this.sheetHeight}`);
          })
      }
      .margin({ bottom: 16 })

      // Content area
      Column() {
        Text(`Height: ${this.onHeightDidChange}`)
          .fontSize(13)
        Text(`Width: ${this.onWidthDidChange}`)
          .fontSize(13)
        Text(`Detent: ${this.onDetentDidChange}`)
          .fontSize(13)
        Text(`Offset: ${this.onOffsetDidChange}`)
          .fontSize(13)
      }
      .width('100%')
      .padding(12)
      .backgroundColor('#F8F8F8')
      .borderRadius(8)

      // Scrollable list
      if (this.enableScroll) {
        List({ space: 4 }) {
          ForEach([0, 1, 2, 3, 4, 5, 6, 7, 8, 9], (item: number) => {
            ListItem() {
              Text(`Item ${item}`)
                .fontSize(14)
                .width('100%')
                .height(40)
                .padding({ left: 16 })
            }
            .backgroundColor(item % 2 === 0 ? '#F0F0F0' : '#FFFFFF')
            .borderRadius(4)
          })
        }
        .width('100%')
        .layoutWeight(1)
        .padding({ left: 12, right: 12 })
        .margin({ bottom: 12 })
      }
    }
    .width('100%')
    .height('100%')
  }

  @Builder
  builderSheetContent2() {
    Column() {
      Text('Embedded Mode Sheet')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 16, bottom: 12 })
      Text('This sheet uses EMBEDDED mode with percentage detents')
        .fontSize(13)
        .margin({ bottom: 16 })
      Button('Close')
        .onClick(() => { this.isShow2 = false; })
    }
    .width('100%')
    .height('100%')
  }

  @Builder
  builderSheetContent3() {
    Column() {
      Text('No Drag Bar Sheet')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 16, bottom: 12 })
      Text('Drag bar is hidden, close button is hidden')
        .fontSize(13)
        .margin({ bottom: 16 })
      Button('Close')
        .onClick(() => { this.isShow3 = false; })
    }
    .width('100%')
    .height('100%')
  }

  @Builder
  builderSheetContent4() {
    Column() {
      Text('UI Option Sheet')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 16, bottom: 12 })
      Text(`Scale: ${this.UIScale}, Width: ${this.UIWidth}`)
        .fontSize(13)
        .margin({ bottom: 8 })
      Text(`Start: ${this.UIStart}, Offset: ${this.UIOffset}`)
        .fontSize(13)
        .margin({ bottom: 16 })
      Button('Close')
        .onClick(() => { this.isShow4 = false; })
    }
    .width('100%')
    .height('100%')
  }

  @Builder
  builderSheetContent5() {
    Column() {
      Text('Percentage Detents Sheet')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 16, bottom: 12 })
      Text('Detents: 20%, 40%, 70%')
        .fontSize(13)
        .margin({ bottom: 16 })
      Button('Close')
        .onClick(() => { this.isShow5 = false; })
    }
    .width('100%')
    .height('100%')
  }

  @Builder
  buildBasicSection() {
    Column({ space: 6 }) {
      Text('1. Basic BindSheet')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
      Row({ space: 8 }) {
        Button('Show Basic Sheet')
          .layoutWeight(1)
          .height(36)
          .fontSize(12)
          .onClick(() => {
            this.isShow = true;
            this.sheetHeight = 300;
            this.dragBar = true;
            this.detentsVal = [200, 300, 400];
            this.sheetMode = SheetMode.OVERLAY;
            this.showClose = true;
            this.shouldDismiss = true;
            this.addLog('Basic sheet shown, height=300, detents=[200,300,400]');
          })
        Button('Show Half Sheet')
          .layoutWeight(1)
          .height(36)
          .fontSize(12)
          .onClick(() => {
            this.isShow = true;
            this.sheetHeight = '50%';
            this.addLog('Half sheet shown, height=50%');
          })
      }
    }
    .width('100%')
    .padding(8)
    .backgroundColor('#FAFAFA')
    .borderRadius(8)
  }

  @Builder
  buildDetentsSection() {
    Column({ space: 6 }) {
      Text('2. Detents (Drag Snap Points)')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
      Row({ space: 6 }) {
        Button('Detents [100,200,300]')
          .layoutWeight(1)
          .height(32)
          .fontSize(10)
          .onClick(() => {
            this.detentsVal = [100, 200, 300];
            this.isShow = true;
            this.addLog('Detents set to [100,200,300]');
          })
        Button('Detents [200,400,600]')
          .layoutWeight(1)
          .height(32)
          .fontSize(10)
          .onClick(() => {
            this.detentsVal = [200, 400, 600];
            this.isShow = true;
            this.addLog('Detents set to [200,400,600]');
          })
      }
      Row({ space: 6 }) {
        Button('Detents [30%,50%,80%]')
          .layoutWeight(1)
          .height(32)
          .fontSize(10)
          .onClick(() => {
            this.detentsVal = [SheetSize.height('30%'), SheetSize.height('50%'), SheetSize.height('80%')];
            this.isShow = true;
            this.addLog('Detents set to [30%,50%,80%]');
          })
        Button('Detents [200]')
          .layoutWeight(1)
          .height(32)
          .fontSize(10)
          .onClick(() => {
            this.detentsVal = [200];
            this.isShow = true;
            this.addLog('Detents set to [200] single');
          })
      }
    }
    .width('100%')
    .padding(8)
    .backgroundColor('#FAFAFA')
    .borderRadius(8)
  }

  @Builder
  buildDragBarSection() {
    Column({ space: 6 }) {
      Text('3. Drag Bar Control')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
      Row({ space: 8 }) {
        Toggle({ type: ToggleType.Switch, isOn: this.dragBar })
          .onChange((isOn: boolean) => {
            this.dragBar = isOn;
            this.addLog(`DragBar toggled: ${isOn}`);
          })
        Text(this.dragBar ? 'DragBar: ON' : 'DragBar: OFF')
          .fontSize(13)
        Blank()
        Button('Show No DragBar')
          .height(32)
          .fontSize(11)
          .onClick(() => {
            this.isShow3 = true;
            this.addLog('Sheet with no drag bar shown');
          })
      }
    }
    .width('100%')
    .padding(8)
    .backgroundColor('#FAFAFA')
    .borderRadius(8)
  }

  @Builder
  buildBackgroundSection() {
    Column({ space: 6 }) {
      Text('4. Background and Blur')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
      Row({ space: 6 }) {
        Button('White BG')
          .layoutWeight(1)
          .height(32)
          .fontSize(10)
          .onClick(() => {
            this.sheetBgColor = '#FFFFFF';
            this.isShow = true;
            this.addLog('Background: White');
          })
        Button('Light Blue BG')
          .layoutWeight(1)
          .height(32)
          .fontSize(10)
          .onClick(() => {
            this.sheetBgColor = '#E3F2FD';
            this.isShow = true;
            this.addLog('Background: Light Blue');
          })
        Button('Light Green BG')
          .layoutWeight(1)
          .height(32)
          .fontSize(10)
          .onClick(() => {
            this.sheetBgColor = '#E8F5E9';
            this.isShow = true;
            this.addLog('Background: Light Green');
          })
      }
      Row({ space: 6 }) {
        Button('No Blur')
          .layoutWeight(1)
          .height(32)
          .fontSize(10)
          .onClick(() => {
            this.sheetBlurStyle = BlurStyle.NONE;
            this.isShow = true;
            this.addLog('BlurStyle: NONE');
          })
        Button('Thin Blur')
          .layoutWeight(1)
          .height(32)
          .fontSize(10)
          .onClick(() => {
            this.sheetBlurStyle = BlurStyle.BACKDROP_THIN;
            this.isShow = true;
            this.addLog('BlurStyle: BACKDROP_THIN');
          })
        Button('Regular Blur')
          .layoutWeight(1)
          .height(32)
          .fontSize(10)
          .onClick(() => {
            this.sheetBlurStyle = BlurStyle.BACKDROP_REGULAR;
            this.isShow = true;
            this.addLog('BlurStyle: BACKDROP_REGULAR');
          })
        Button('Thick Blur')
          .layoutWeight(1)
          .height(32)
          .fontSize(10)
          .onClick(() => {
            this.sheetBlurStyle = BlurStyle.BACKDROP_THICK;
            this.isShow = true;
            this.addLog('BlurStyle: BACKDROP_THICK');
          })
      }
    }
    .width('100%')
    .padding(8)
    .backgroundColor('#FAFAFA')
    .borderRadius(8)
  }

  @Builder
  buildModeSection() {
    Column({ space: 6 }) {
      Text('5. Mode and Dismiss')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
      Row({ space: 6 }) {
        Button('OVERLAY Mode')
          .layoutWeight(1)
          .height(32)
          .fontSize(10)
          .onClick(() => {
            this.sheetMode = SheetMode.OVERLAY;
            this.isShow = true;
            this.addLog('Mode: OVERLAY');
          })
        Button('EMBEDDED Mode')
          .layoutWeight(1)
          .height(32)
          .fontSize(10)
          .onClick(() => {
            this.isShow2 = true;
            this.addLog('Mode: EMBEDDED (sheet2)');
          })
        Button('AUTO Mode')
          .layoutWeight(1)
          .height(32)
          .fontSize(10)
          .onClick(() => {
            this.isShow4 = true;
            this.addLog('Mode: AUTO (sheet4)');
          })
      }
      Row({ space: 8 }) {
        Toggle({ type: ToggleType.Switch, isOn: this.shouldDismiss })
          .onChange((isOn: boolean) => {
            this.shouldDismiss = isOn;
            this.addLog(`shouldDismiss: ${isOn}`);
          })
        Text('shouldDismiss')
          .fontSize(12)
        Blank()
        Toggle({ type: ToggleType.Switch, isOn: this.onWillDismissAction })
          .onChange((isOn: boolean) => {
            this.onWillDismissAction = isOn;
            this.addLog(`onWillDismiss action: ${isOn}`);
          })
        Text('onWillDismiss')
          .fontSize(12)
      }
    }
    .width('100%')
    .padding(8)
    .backgroundColor('#FAFAFA')
    .borderRadius(8)
  }

  @Builder
  buildUISection() {
    Column({ space: 6 }) {
      Text('6. UI Option Properties')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
      Row({ space: 6 }) {
        Text('Scale:')
          .fontSize(12)
        Slider(value: this.UIScale, min: 0.3, max: 1.0, step: 0.05)
          .layoutWeight(1)
          .onChange((value: number) => {
            this.UIScale = Math.round(value * 100) / 100;
          })
        Text(this.UIScale.toFixed(2))
          .fontSize(12)
          .width(36)
      }
      Row({ space: 6 }) {
        Button('Width 50%')
          .layoutWeight(1)
          .height(30)
          .fontSize(9)
          .onClick(() => { this.UIWidth = '50%'; })
        Button('Width 80%')
          .layoutWeight(1)
          .height(30)
          .fontSize(9)
          .onClick(() => { this.UIWidth = '80%'; })
        Button('Width 100%')
          .layoutWeight(1)
          .height(30)
          .fontSize(9)
          .onClick(() => { this.UIWidth = '100%'; })
      }
      Row({ space: 6 }) {
        Button('Height 30%')
          .layoutWeight(1)
          .height(30)
          .fontSize(9)
          .onClick(() => { this.UIHeight = '30%'; })
        Button('Height 60%')
          .layoutWeight(1)
          .height(30)
          .fontSize(9)
          .onClick(() => { this.UIHeight = '60%'; })
        Button('Height 90%')
          .layoutWeight(1)
          .height(30)
          .fontSize(9)
          .onClick(() => { this.UIHeight = '90%'; })
      }
      Row({ space: 6 }) {
        Button('Start: Left')
          .layoutWeight(1)
          .height(30)
          .fontSize(9)
          .onClick(() => { this.UIStart = 'left'; })
        Button('Start: Center')
          .layoutWeight(1)
          .height(30)
          .fontSize(9)
          .onClick(() => { this.UIStart = 'center'; })
        Button('Start: Right')
          .layoutWeight(1)
          .height(30)
          .fontSize(9)
          .onClick(() => { this.UIStart = 'right'; })
      }
      Row({ space: 6 }) {
        Button('Offset: 0')
          .layoutWeight(1)
          .height(30)
          .fontSize(9)
          .onClick(() => { this.UIOffset = '0'; })
        Button('Offset: 50')
          .layoutWeight(1)
          .height(30)
          .fontSize(9)
          .onClick(() => { this.UIOffset = '50'; })
        Button('Offset: -50')
          .layoutWeight(1)
          .height(30)
          .fontSize(9)
          .onClick(() => { this.UIOffset = '-50'; })
      }
      Row({ space: 6 }) {
        Toggle({ type: ToggleType.Switch, isOn: this.UIShowClose })
          .onChange((isOn: boolean) => { this.UIShowClose = isOn; })
        Text('UIShowClose')
          .fontSize(11)
        Blank()
        Toggle({ type: ToggleType.Switch, isOn: this.enableOutsideDeselect })
          .onChange((isOn: boolean) => { this.enableOutsideDeselect = isOn; })
        Text('OutsideDeselect')
          .fontSize(11)
      }
      Button('Show UI Option Sheet')
        .width('100%')
        .height(36)
        .fontSize(12)
        .onClick(() => {
          this.isShow4 = true;
          this.addLog('UI Option sheet shown');
        })
    }
    .width('100%')
    .padding(8)
    .backgroundColor('#FAFAFA')
    .borderRadius(8)
  }

  @Builder
  buildCallbackSection() {
    Column({ space: 6 }) {
      Text('7. Callback Events')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
      Row({ space: 6 }) {
        Text(`Height: ${this.onHeightDidChange}`)
          .fontSize(11)
          .layoutWeight(1)
          .backgroundColor('#E0E0E0')
          .padding(4)
          .borderRadius(4)
        Text(`Width: ${this.onWidthDidChange}`)
          .fontSize(11)
          .layoutWeight(1)
          .backgroundColor('#E0E0E0')
          .padding(4)
          .borderRadius(4)
      }
      Row({ space: 6 }) {
        Text(`Detent: ${this.onDetentDidChange}`)
          .fontSize(11)
          .layoutWeight(1)
          .backgroundColor('#E0E0E0')
          .padding(4)
          .borderRadius(4)
        Text(`Offset: ${this.onOffsetDidChange}`)
          .fontSize(11)
          .layoutWeight(1)
          .backgroundColor('#E0E0E0')
          .padding(4)
          .borderRadius(4)
      }
      Button('Show Sheet to Test Callbacks')
        .width('100%')
        .height(36)
        .fontSize(12)
        .onClick(() => {
          this.isShow = true;
          this.addLog('Sheet shown for callback testing');
        })
    }
    .width('100%')
    .padding(8)
    .backgroundColor('#FAFAFA')
    .borderRadius(8)
  }

  @Builder
  buildCustomDragSection() {
    Column({ space: 6 }) {
      Text('8. Custom Drag and Resize')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
      Row({ space: 6 }) {
        Text('Sheet Height:')
          .fontSize(12)
        Slider(value: this.customDetentHeight, min: 100, max: 800, step: 10)
          .layoutWeight(1)
          .onChange((value: number) => {
            this.customDetentHeight = Math.round(value);
          })
        Text(`${this.customDetentHeight}`)
          .fontSize(12)
          .width(40)
      }
      Row({ space: 6 }) {
        Button('Apply Custom Height')
          .layoutWeight(1)
          .height(32)
          .fontSize(10)
          .onClick(() => {
            this.sheetHeight = this.customDetentHeight;
            this.detentsVal = [this.customDetentHeight];
            this.isShow = true;
            this.addLog(`Custom height applied: ${this.customDetentHeight}`);
          })
        Button('Multi Detent')
          .layoutWeight(1)
          .height(32)
          .fontSize(10)
          .onClick(() => {
            this.detentsVal = [this.customDetentHeight - 100, this.customDetentHeight, this.customDetentHeight + 100];
            this.isShow = true;
            this.addLog(`Multi detent: [${this.customDetentHeight - 100},${this.customDetentHeight},${this.customDetentHeight + 100}]`);
          })
      }
      Row({ space: 6 }) {
        Toggle({ type: ToggleType.Switch, isOn: this.enableScroll })
          .onChange((isOn: boolean) => { this.enableScroll = isOn; })
        Text('Enable Scroll Content')
          .fontSize(11)
        Blank()
        Toggle({ type: ToggleType.Switch, isOn: this.showClose })
          .onChange((isOn: boolean) => { this.showClose = isOn; })
        Text('Show Close Button')
          .fontSize(11)
      }
      Text('Drag the sheet up/down to test detent snapping. Use slider to adjust height.')
        .fontSize(10)
        .fontColor('#888888')
    }
    .width('100%')
    .padding(8)
    .backgroundColor('#FAFAFA')
    .borderRadius(8)
  }

  @Builder
  buildMultipleSheetsSection() {
    Column({ space: 6 }) {
      Text('9. Multiple Sheets')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
      Row({ space: 6 }) {
        Button('Sheet 1 (OVERLAY)')
          .layoutWeight(1)
          .height(32)
          .fontSize(9)
          .onClick(() => {
            this.isShow = true;
            this.addLog('Sheet 1 (OVERLAY) shown');
          })
        Button('Sheet 2 (EMBEDDED)')
          .layoutWeight(1)
          .height(32)
          .fontSize(9)
          .onClick(() => {
            this.isShow2 = true;
            this.addLog('Sheet 2 (EMBEDDED) shown');
          })
        Button('Sheet 3 (No DragBar)')
          .layoutWeight(1)
          .height(32)
          .fontSize(9)
          .onClick(() => {
            this.isShow3 = true;
            this.addLog('Sheet 3 (No DragBar) shown');
          })
      }
      Row({ space: 6 }) {
        Button('Sheet 4 (UI Option)')
          .layoutWeight(1)
          .height(32)
          .fontSize(9)
          .onClick(() => {
            this.isShow4 = true;
            this.addLog('Sheet 4 (UI Option) shown');
          })
        Button('Sheet 5 (% Detents)')
          .layoutWeight(1)
          .height(32)
          .fontSize(9)
          .onClick(() => {
            this.isShow5 = true;
            this.addLog('Sheet 5 (% Detents) shown');
          })
      }
      Row({ space: 6 }) {
        Button('Close All')
          .layoutWeight(1)
          .height(32)
          .fontSize(10)
          .onClick(() => {
            this.isShow = false;
            this.isShow2 = false;
            this.isShow3 = false;
            this.isShow4 = false;
            this.isShow5 = false;
            this.addLog('All sheets closed');
          })
      }
    }
    .width('100%')
    .padding(8)
    .backgroundColor('#FAFAFA')
    .borderRadius(8)
  }

  @Builder
  buildAdvancedTesterSection() {
    Column({ space: 6 }) {
      Text('10. Advanced Drag & Resize Tester')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
      Text('Comprehensive sheet testing with drag metrics, detent snapping, callbacks tracking, and theme configuration')
        .fontSize(10)
        .fontColor('#888888')

      // Feature list
      Column({ space: 2 }) {
        Text('Test Coverage:')
          .fontSize(11)
          .fontWeight(FontWeight.Bold)
        Text('DragBar toggle, Detent config (px/%), Height resize, BG/Blur, Mode switch, onWillDismiss, Height/Width/Detent/Offset callbacks, onAppear/onDisappear, Drag metrics, Theme presets')
          .fontSize(10)
          .fontColor('#666666')
      }
      .width('100%')
      .padding(8)
      .backgroundColor('#F0F0F0')
      .borderRadius(8)

      SheetDragTester()
        .width('100%')
        .height(500)
    }
    .width('100%')
    .padding(8)
    .backgroundColor('#FAFAFA')
    .borderRadius(8)
  }

  @Builder
  buildLogSection() {
    Column({ space: 4 }) {
      Row() {
        Text('Event Log')
          .fontSize(16)
          .fontWeight(FontWeight.Bold)
        Blank()
        Text(`${this.logList.length} entries`)
          .fontSize(11)
          .fontColor('#888888')
      }
      .width('100%')
      Scroll() {
        Column({ space: 2 }) {
          ForEach(this.logList.slice().reverse(), (entry: SheetLogEntry) => {
            Row() {
              Text(entry.time).fontSize(9).fontColor('#888888').width(90)
              Text(entry.msg).fontSize(10).layoutWeight(1)
            }
            .width('100%')
            .padding({ left: 4, right: 4 })
          })
        }
        .width('100%')
      }
      .width('100%')
      .height(200)
      .backgroundColor('#F5F5F5')
      .borderRadius(8)
      .padding(4)
    }
    .width('100%')
    .padding(8)
    .backgroundColor('#FAFAFA')
    .borderRadius(8)
  }
}
