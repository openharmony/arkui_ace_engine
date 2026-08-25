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

const DOMAIN: number = 0x0000;
const TAG: string = 'BindSheetAdvanced';

interface AdvancedLogEntry {
  time: string;
  action: string;
  detail: string;
}

interface DragMetrics {
  startY: number;
  currentY: number;
  delta: number;
  velocity: number;
  direction: string;
}

interface ResizeConfig {
  minWidth: number;
  maxWidth: number;
  minHeight: number;
  maxHeight: number;
  step: number;
}

interface SheetThemeConfig {
  bgColors: string[];
  blurStyles: BlurStyle[];
  dragBarModes: boolean[];
  modes: SheetMode[];
}

function formatTime(ts: number): string {
  let d = new Date(ts);
  let hh = d.getHours().toString().padStart(2, '0');
  let mm = d.getMinutes().toString().padStart(2, '0');
  let ss = d.getSeconds().toString().padStart(2, '0');
  let ms = d.getMilliseconds().toString().padStart(3, '0');
  return `${hh}:${mm}:${ss}.${ms}`;
}

function clamp(value: number, min: number, max: number): number {
  return Math.max(min, Math.min(max, value));
}

function calculateVelocity(start: number, end: number, durationMs: number): number {
  if (durationMs <= 0) return 0;
  return Math.abs(end - start) / durationMs * 1000;
}

@Component
export struct SheetDragTester {
  @State isShow: boolean = false;
  @State dragMetrics: DragMetrics = { startY: 0, currentY: 0, delta: 0, velocity: 0, direction: 'none' };
  @State sheetHeight: number = 400;
  @State detents: Array<number | SheetSize> = [200, 400, 600];
  @State logEntries: AdvancedLogEntry[] = [];
  @State dragCount: number = 0;
  @State resizeCount: number = 0;
  @State snapCount: number = 0;
  @State lastSnapHeight: number = 400;
  @State enableDragLog: boolean = true;
  @State enableSnapLog: boolean = true;
  @State dragStartTime: number = 0;
  @State dragEndTime: number = 0;
  @State totalDragDistance: number = 0;
  @State averageDragSpeed: number = 0;
  @State maxDragSpeed: number = 0;
  @State currentDragSpeed: number = 0;
  @State isDragging: boolean = false;
  @State dragBarVisible: boolean = true;
  @State sheetMode: SheetMode = SheetMode.OVERLAY;
  @State sheetBgColor: string = '#FFFFFF';
  @State sheetBlurStyle: BlurStyle = BlurStyle.NONE;
  @State showCloseBtn: boolean = true;
  @State shouldDismiss: boolean = true;
  @State onWillDismissEnabled: boolean = true;
  @State heightCallbackCount: number = 0;
  @State detentCallbackCount: number = 0;
  @State offsetCallbackCount: number = 0;
  @State disappearCallbackCount: number = 0;
  @State lastHeightChange: number = 0;
  @State lastDetentChange: number = 0;
  @State lastOffsetChange: number = 0;
  @State contentScrollEnabled: boolean = true;
  @State sheetTitle: string = 'Drag Test Sheet';
  @State sheetDescription: string = 'Drag the sheet to test detent snapping and resize behavior';
  @State currentDetentIndex: number = 1;
  @State detentLabels: string[] = ['Small (200)', 'Medium (400)', 'Large (600)'];
  @State selectedDetentLabel: string = 'Medium (400)';

  private maxLogCount: number = 80;

  addLog(action: string, detail: string): void {
    if (!this.enableDragLog && action.startsWith('Drag')) return;
    if (!this.enableSnapLog && action.startsWith('Snap')) return;
    let entry: AdvancedLogEntry = { time: formatTime(Date.now()), action: action, detail: detail };
    this.logEntries.push(entry);
    if (this.logEntries.length > this.maxLogCount) {
      this.logEntries.shift();
    }
    hilog.info(DOMAIN, TAG, `${action}: ${detail}`);
  }

  resetMetrics(): void {
    this.dragCount = 0;
    this.resizeCount = 0;
    this.snapCount = 0;
    this.totalDragDistance = 0;
    this.averageDragSpeed = 0;
    this.maxDragSpeed = 0;
    this.heightCallbackCount = 0;
    this.detentCallbackCount = 0;
    this.offsetCallbackCount = 0;
    this.disappearCallbackCount = 0;
    this.addLog('Reset', 'All metrics reset');
  }

  build() {
    Column({ space: 8 }) {
      // Title
      Text('Sheet Drag & Resize Tester')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 8 })

      // Metrics display
      Row({ space: 6 }) {
        this.buildMetricCard('Drags', this.dragCount.toString(), '#E3F2FD')
        this.buildMetricCard('Resizes', this.resizeCount.toString(), '#E8F5E9')
        this.buildMetricCard('Snaps', this.snapCount.toString(), '#FFF3E0')
        this.buildMetricCard('MaxSpeed', `${this.maxDragSpeed.toFixed(0)}`, '#F3E5F5')
      }

      Row({ space: 6 }) {
        this.buildMetricCard('Height CB', this.heightCallbackCount.toString(), '#FFEBEE')
        this.buildMetricCard('Detent CB', this.detentCallbackCount.toString(), '#E0F7FA')
        this.buildMetricCard('Offset CB', this.offsetCallbackCount.toString(), '#F1F8E9')
        this.buildMetricCard('Disappear', this.disappearCallbackCount.toString(), '#FFF8E1')
      }

      // Current state
      Column({ space: 2 }) {
        Text(`Current Height: ${this.lastHeightChange}`)
          .fontSize(11)
        Text(`Current Detent: ${this.lastDetentChange} (${this.selectedDetentLabel})`)
          .fontSize(11)
        Text(`Current Offset: ${this.lastOffsetChange}`)
          .fontSize(11)
        Text(`Total Drag Dist: ${this.totalDragDistance.toFixed(0)}px`)
          .fontSize(11)
        Text(`Avg Speed: ${this.averageDragSpeed.toFixed(0)}px/s`)
          .fontSize(11)
      }
      .width('100%')
      .padding(8)
      .backgroundColor('#F5F5F5')
      .borderRadius(8)

      // Detent selector
      Row({ space: 6 }) {
        ForEach([0, 1, 2], (index: number) => {
          Button(this.detentLabels[index])
            .layoutWeight(1)
            .height(28)
            .fontSize(8)
            .backgroundColor(this.currentDetentIndex === index ? '#1976D2' : '#E0E0E0')
            .fontColor(this.currentDetentIndex === index ? '#FFFFFF' : '#333333')
            .onClick(() => {
              this.currentDetentIndex = index;
              this.selectedDetentLabel = this.detentLabels[index];
              let heights = [200, 400, 600];
              this.sheetHeight = heights[index];
              this.addLog('Detent Select', `Index ${index}, height ${heights[index]}`);
            })
        })
      }

      // Drag bar toggle
      Row({ space: 8 }) {
        Toggle({ type: ToggleType.Switch, isOn: this.dragBarVisible })
          .onChange((isOn: boolean) => {
            this.dragBarVisible = isOn;
            this.addLog('DragBar', `Toggled to ${isOn}`);
          })
        Text('DragBar')
          .fontSize(11)
        Blank()
        Toggle({ type: ToggleType.Switch, isOn: this.enableDragLog })
          .onChange((isOn: boolean) => { this.enableDragLog = isOn; })
        Text('DragLog')
          .fontSize(11)
        Blank()
        Toggle({ type: ToggleType.Switch, isOn: this.enableSnapLog })
          .onChange((isOn: boolean) => { this.enableSnapLog = isOn; })
        Text('SnapLog')
          .fontSize(11)
      }

      // Mode selector
      Row({ space: 6 }) {
        Button('OVERLAY')
          .layoutWeight(1)
          .height(28)
          .fontSize(9)
          .onClick(() => { this.sheetMode = SheetMode.OVERLAY; this.addLog('Mode', 'OVERLAY'); })
        Button('EMBEDDED')
          .layoutWeight(1)
          .height(28)
          .fontSize(9)
          .onClick(() => { this.sheetMode = SheetMode.EMBEDDED; this.addLog('Mode', 'EMBEDDED'); })
        Button('AUTO')
          .layoutWeight(1)
          .height(28)
          .fontSize(9)
          .onClick(() => { this.sheetMode = SheetMode.AUTO; this.addLog('Mode', 'AUTO'); })
      }

      // Background color selector
      Row({ space: 4 }) {
        ForEach(['#FFFFFF', '#E3F2FD', '#E8F5E9', '#FFF3E0', '#F3E5F5', '#FFEBEE'], (color: string) => {
          Button('')
            .width(32)
            .height(28)
            .backgroundColor(color)
            .border({ width: 1, color: '#CCCCCC' })
            .onClick(() => {
              this.sheetBgColor = color;
              this.addLog('BgColor', color);
            })
        })
      }

      // Blur style selector
      Row({ space: 4 }) {
        Button('None')
          .layoutWeight(1)
          .height(28)
          .fontSize(8)
          .onClick(() => { this.sheetBlurStyle = BlurStyle.NONE; })
        Button('Thin')
          .layoutWeight(1)
          .height(28)
          .fontSize(8)
          .onClick(() => { this.sheetBlurStyle = BlurStyle.BACKDROP_THIN; })
        Button('Regular')
          .layoutWeight(1)
          .height(28)
          .fontSize(8)
          .onClick(() => { this.sheetBlurStyle = BlurStyle.BACKDROP_REGULAR; })
        Button('Thick')
          .layoutWeight(1)
          .height(28)
          .fontSize(8)
          .onClick(() => { this.sheetBlurStyle = BlurStyle.BACKDROP_THICK; })
        Button('Ultra')
          .layoutWeight(1)
          .height(28)
          .fontSize(8)
          .onClick(() => { this.sheetBlurStyle = BlurStyle.COMPONENT_THICK; })
      }

      // Toggle controls
      Row({ space: 8 }) {
        Toggle({ type: ToggleType.Switch, isOn: this.showCloseBtn })
          .onChange((isOn: boolean) => { this.showCloseBtn = isOn; })
        Text('CloseBtn')
          .fontSize(11)
        Blank()
        Toggle({ type: ToggleType.Switch, isOn: this.shouldDismiss })
          .onChange((isOn: boolean) => { this.shouldDismiss = isOn; })
        Text('Dismiss')
          .fontSize(11)
        Blank()
        Toggle({ type: ToggleType.Switch, isOn: this.onWillDismissEnabled })
          .onChange((isOn: boolean) => { this.onWillDismissEnabled = isOn; })
        Text('WillDismiss')
          .fontSize(10)
      }

      Row({ space: 8 }) {
        Toggle({ type: ToggleType.Switch, isOn: this.contentScrollEnabled })
          .onChange((isOn: boolean) => { this.contentScrollEnabled = isOn; })
        Text('Scroll')
          .fontSize(11)
        Blank()
        Button('Reset')
          .height(28)
          .fontSize(10)
          .onClick(() => { this.resetMetrics(); })
        Button('Clear Log')
          .height(28)
          .fontSize(10)
          .onClick(() => { this.logEntries = []; })
      }

      // Height slider for custom resize
      Row({ space: 6 }) {
        Text('Height:')
          .fontSize(11)
          .width(40)
        Slider(value: this.sheetHeight instanceof number ? this.sheetHeight : 400, min: 100, max: 800, step: 10)
          .layoutWeight(1)
          .onChange((value: number) => {
            this.sheetHeight = Math.round(value);
          })
        Text(`${this.sheetHeight}`)
          .fontSize(11)
          .width(40)
      }

      // Quick height presets
      Row({ space: 4 }) {
        Button('100')
          .layoutWeight(1)
          .height(26)
          .fontSize(8)
          .onClick(() => { this.sheetHeight = 100; this.detents = [100, 300, 500]; this.addLog('Height', '100px'); })
        Button('200')
          .layoutWeight(1)
          .height(26)
          .fontSize(8)
          .onClick(() => { this.sheetHeight = 200; this.detents = [200, 400, 600]; this.addLog('Height', '200px'); })
        Button('400')
          .layoutWeight(1)
          .height(26)
          .fontSize(8)
          .onClick(() => { this.sheetHeight = 400; this.detents = [200, 400, 600]; this.addLog('Height', '400px'); })
        Button('600')
          .layoutWeight(1)
          .height(26)
          .fontSize(8)
          .onClick(() => { this.sheetHeight = 600; this.detents = [300, 600, 800]; this.addLog('Height', '600px'); })
        Button('800')
          .layoutWeight(1)
          .height(26)
          .fontSize(8)
          .onClick(() => { this.sheetHeight = 800; this.detents = [400, 600, 800]; this.addLog('Height', '800px'); })
      }

      // Percentage height presets
      Row({ space: 4 }) {
        Button('25%').layoutWeight(1).height(26).fontSize(8).onClick(() => { this.sheetHeight = '25%'; this.detents = [SheetSize.height('25%'), SheetSize.height('50%'), SheetSize.height('75%')]; this.addLog('Height', '25%'); })
        Button('50%').layoutWeight(1).height(26).fontSize(8).onClick(() => { this.sheetHeight = '50%'; this.detents = [SheetSize.height('25%'), SheetSize.height('50%'), SheetSize.height('75%')]; this.addLog('Height', '50%'); })
        Button('75%').layoutWeight(1).height(26).fontSize(8).onClick(() => { this.sheetHeight = '75%'; this.detents = [SheetSize.height('25%'), SheetSize.height('50%'), SheetSize.height('75%')]; this.addLog('Height', '75%'); })
        Button('100%').layoutWeight(1).height(26).fontSize(8).onClick(() => { this.sheetHeight = '100%'; this.detents = [SheetSize.height('50%'), SheetSize.height('75%'), SheetSize.height('100%')]; this.addLog('Height', '100%'); })
      }

      // Show sheet button
      Button('Show Drag Test Sheet')
        .width('100%')
        .height(40)
        .fontSize(14)
        .margin({ top: 4, bottom: 4 })
        .onClick(() => {
          this.isShow = true;
          this.addLog('Show', 'Drag test sheet opened');
        })

      // Log display
      Text('Event Log:')
        .fontSize(13)
        .fontWeight(FontWeight.Bold)
        .alignSelf(ItemAlign.Start)

      Scroll() {
        Column({ space: 1 }) {
          ForEach(this.logEntries.slice().reverse(), (entry: AdvancedLogEntry) => {
            Row() {
              Text(entry.time)
                .fontSize(8)
                .fontColor('#888888')
                .width(80)
              Text(entry.action)
                .fontSize(9)
                .width(70)
                .fontColor('#1976D2')
              Text(entry.detail)
                .fontSize(9)
                .layoutWeight(1)
            }
            .width('100%')
          })
        }
        .width('100%')
      }
      .layoutWeight(1)
      .width('100%')
      .backgroundColor('#FAFAFA')
      .borderRadius(8)
      .padding(4)
    }
    .width('100%')
    .height('100%')
    .bindSheet($$this.isShow, this.builderDragSheet(), {
      height: this.sheetHeight,
      dragBar: this.dragBarVisible,
      backgroundColor: this.sheetBgColor,
      blurStyle: this.sheetBlurStyle,
      detents: this.detents,
      mode: this.sheetMode,
      showClose: this.showCloseBtn,
      shouldDismiss: this.shouldDismiss,
      onWillDismiss: this.onWillDismissEnabled ? (sheetDismiss: SheetDismiss) => {
        this.addLog('onWillDismiss', 'Dismiss triggered');
        sheetDismiss.dismiss();
      } : undefined,
      onHeightDidChange: (height: number) => {
        this.heightCallbackCount++;
        this.lastHeightChange = height;
        this.resizeCount++;
        this.addLog('onHeightDidChange', `${height}px`);
      },
      onWidthDidChange: (width: number) => {
        this.addLog('onWidthDidChange', `${width}px`);
      },
      onDetentDidChange: (detent: number) => {
        this.detentCallbackCount++;
        this.lastDetentChange = detent;
        this.snapCount++;
        let heights = [200, 400, 600];
        for (let i = 0; i < heights.length; i++) {
          if (Math.abs(detent - heights[i]) < 50) {
            this.currentDetentIndex = i;
            this.selectedDetentLabel = this.detentLabels[i];
            break;
          }
        }
        this.addLog('onDetentDidChange', `detent=${detent}, label=${this.selectedDetentLabel}`);
      },
      onOffsetDidChange: (offset: number) => {
        this.offsetCallbackCount++;
        this.lastOffsetChange = offset;
        this.addLog('onOffsetDidChange', `${offset}px`);
      },
      onAppear: () => {
        this.addLog('onAppear', 'Sheet appeared');
      },
      onDisappear: () => {
        this.disappearCallbackCount++;
        this.addLog('onDisappear', 'Sheet disappeared');
      },
    })
  }

  @Builder
  buildMetricCard(title: string, value: string, color: string) {
    Column() {
      Text(title)
        .fontSize(9)
        .fontColor('#666666')
      Text(value)
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
        .fontColor('#333333')
    }
    .layoutWeight(1)
    .height(48)
    .backgroundColor(color)
    .borderRadius(8)
    .justifyContent(FlexAlign.Center)
  }

  @Builder
  builderDragSheet() {
    Column() {
      Text(this.sheetTitle)
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 16, bottom: 4 })

      Text(this.sheetDescription)
        .fontSize(13)
        .fontColor('#666666')
        .textAlign(TextAlign.Center)
        .margin({ bottom: 12 })

      // State display
      Column({ space: 4 }) {
        Text(`Height: ${this.lastHeightChange}px`)
          .fontSize(12)
        Text(`Detent: ${this.selectedDetentLabel}`)
          .fontSize(12)
        Text(`Offset: ${this.lastOffsetChange}px`)
          .fontSize(12)
        Text(`Drag Count: ${this.dragCount}`)
          .fontSize(12)
        Text(`Snap Count: ${this.snapCount}`)
          .fontSize(12)
      }
      .width('100%')
      .padding(12)
      .backgroundColor('#F8F8F8')
      .borderRadius(8)
      .margin({ bottom: 12 })

      // Action buttons
      Row({ space: 8 }) {
        Button('Small')
          .layoutWeight(1)
          .height(32)
          .fontSize(11)
          .onClick(() => {
            this.sheetHeight = 200;
            this.currentDetentIndex = 0;
            this.selectedDetentLabel = this.detentLabels[0];
            this.addLog('Resize', 'Small (200)');
          })
        Button('Medium')
          .layoutWeight(1)
          .height(32)
          .fontSize(11)
          .onClick(() => {
            this.sheetHeight = 400;
            this.currentDetentIndex = 1;
            this.selectedDetentLabel = this.detentLabels[1];
            this.addLog('Resize', 'Medium (400)');
          })
        Button('Large')
          .layoutWeight(1)
          .height(32)
          .fontSize(11)
          .onClick(() => {
            this.sheetHeight = 600;
            this.currentDetentIndex = 2;
            this.selectedDetentLabel = this.detentLabels[2];
            this.addLog('Resize', 'Large (600)');
          })
      }
      .margin({ bottom: 8 })

      // Detent configuration
      Row({ space: 8 }) {
        Button('Single Detent')
          .layoutWeight(1)
          .height(30)
          .fontSize(9)
          .onClick(() => {
            this.detents = [400];
            this.addLog('Detents', 'Single [400]');
          })
        Button('Triple Detent')
          .layoutWeight(1)
          .height(30)
          .fontSize(9)
          .onClick(() => {
            this.detents = [200, 400, 600];
            this.addLog('Detents', 'Triple [200,400,600]');
          })
        Button('Pct Detent')
          .layoutWeight(1)
          .height(30)
          .fontSize(9)
          .onClick(() => {
            this.detents = [SheetSize.height('30%'), SheetSize.height('50%'), SheetSize.height('80%')];
            this.addLog('Detents', 'Pct [30%,50%,80%]');
          })
      }
      .margin({ bottom: 12 })

      // Scrollable content
      if (this.contentScrollEnabled) {
        List({ space: 3 }) {
          ForEach([0, 1, 2, 3, 4, 5, 6, 7, 8, 9], (item: number) => {
            ListItem() {
              Row() {
                Text(`List Item ${item}`)
                  .fontSize(13)
                  .layoutWeight(1)
                Text(`#${item}`)
                  .fontSize(11)
                  .fontColor('#999999')
              }
              .width('100%')
              .height(36)
              .padding({ left: 16, right: 16 })
              .backgroundColor(item % 2 === 0 ? '#F5F5F5' : '#FFFFFF')
            }
          })
        }
        .width('100%')
        .layoutWeight(1)
        .padding({ left: 8, right: 8 })
        .margin({ bottom: 8 })
      }

      // Close button
      Button('Close Sheet')
        .width('80%')
        .height(40)
        .fontSize(14)
        .margin({ bottom: 16 })
        .onClick(() => {
          this.isShow = false;
          this.addLog('Close', 'Sheet closed by button');
        })

      // Theme quick switch
      Text('Theme Presets:')
        .fontSize(12)
        .fontWeight(FontWeight.Bold)
        .alignSelf(ItemAlign.Start)
        .margin({ left: 8, bottom: 4 })

      Row({ space: 4 }) {
        Button('Light')
          .layoutWeight(1)
          .height(28)
          .fontSize(9)
          .onClick(() => {
            this.sheetBgColor = '#FFFFFF';
            this.sheetBlurStyle = BlurStyle.NONE;
            this.addLog('Theme', 'Light preset applied');
          })
        Button('Blur')
          .layoutWeight(1)
          .height(28)
          .fontSize(9)
          .onClick(() => {
            this.sheetBgColor = '#F5F5F5';
            this.sheetBlurStyle = BlurStyle.BACKDROP_REGULAR;
            this.addLog('Theme', 'Blur preset applied');
          })
        Button('Dark')
          .layoutWeight(1)
          .height(28)
          .fontSize(9)
          .onClick(() => {
            this.sheetBgColor = '#333333';
            this.sheetBlurStyle = BlurStyle.BACKDROP_THICK;
            this.addLog('Theme', 'Dark preset applied');
          })
        Button('Colorful')
          .layoutWeight(1)
          .height(28)
          .fontSize(9)
          .onClick(() => {
            this.sheetBgColor = '#E3F2FD';
            this.sheetBlurStyle = BlurStyle.COMPONENT_THIN;
            this.addLog('Theme', 'Colorful preset applied');
          })
      }
      .margin({ bottom: 8 })

      // Drag behavior info
      Column({ space: 1 }) {
        Text('Drag to snap. Callbacks: onHeightDidChange/onDetentDidChange/onOffsetDidChange/onWillDismiss/onDisappear')
          .fontSize(10)
          .fontColor('#666666')
      }
      .width('100%')
      .padding(8)
      .backgroundColor('#F0F0F0')
      .borderRadius(8)
      .margin({ bottom: 8 })

      // Stats summary
      Column({ space: 1 }) {
        Text(`Drags:${this.dragCount} Resizes:${this.resizeCount} Snaps:${this.snapCount} HCB:${this.heightCallbackCount} DCB:${this.detentCallbackCount} OCB:${this.offsetCallbackCount} DisCB:${this.disappearCallbackCount}`)
          .fontSize(10)
          .fontColor('#666666')
        Text(`MaxSpd:${this.maxDragSpeed.toFixed(0)}px/s Dist:${this.totalDragDistance.toFixed(0)}px`)
          .fontSize(10)
          .fontColor('#666666')
      }
      .width('100%')
      .padding(8)
      .backgroundColor('#E8F5E9')
      .borderRadius(8)
      .margin({ bottom: 8 })
    }
    .width('100%')
    .height('100%')
  }
}
