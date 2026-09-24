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

/*
 * 综合场景：独立 ScrollBar 与内置滚动条对比。
 * 覆盖能力：
 *   1. ScrollBar(scroller) 独立滚动条：direction / state / enableNestedScroll
 *   2. 与 Scroll 共用 Scroller 联动
 *   3. 内置滚动条：scrollBar / scrollBarColor / scrollBarWidth
 *   4. edgeEffect / friction / enableScrollInteraction
 *   5. 滚动事件反馈
 */

import { LengthMetrics } from '@kit.ArkUI';

@Entry
@Component
struct ScrollBarComprehensiveSample {
  private scroller: Scroller = new Scroller();
  private builtInScroller: Scroller = new Scroller();
  private items: number[] = [];

  @State barDirection: ScrollBarDirection = ScrollBarDirection.Vertical;
  @State barState: BarState = BarState.Auto;
  @State enableNestedScroll: boolean = true;
  @State builtInBarState: BarState = BarState.Auto;
  @State builtInColor: string = '#5B8DEF';
  @State builtInWidth: number = 10;
  @State edgeEffect: EdgeEffect = EdgeEffect.Spring;
  @State edgeEffectName: string = 'Spring';
  @State friction: number = 0.6;
  @State interactionEnabled: boolean = true;
  @State offsetX: number = 0;
  @State offsetY: number = 0;
  @State eventLogEnabled: boolean = false;
  @State logs: string[] = [];

  @Styles
  contentCard() {
    .borderRadius(12)
  }

  aboutToAppear(): void {
    for (let i = 0; i < 30; i++) {
      this.items.push(i + 1);
    }
    this.logs = [];
  }

  private addLog(message: string): void {
    this.logs.push(message);
    if (this.logs.length > 24) {
      this.logs.splice(0, 1);
    }
  }

  private clearLogs(): void {
    this.logs = [];
  }

  private stateName(state: BarState): string {
    if (state === BarState.Off) {
      return 'Off';
    }
    if (state === BarState.On) {
      return 'On';
    }
    return 'Auto';
  }

  private cycleDirection(): void {
    if (this.barDirection === ScrollBarDirection.Vertical) {
      this.barDirection = ScrollBarDirection.Horizontal;
    } else {
      this.barDirection = ScrollBarDirection.Vertical;
    }
  }

  private cycleBarState(): void {
    if (this.barState === BarState.Off) {
      this.barState = BarState.On;
    } else if (this.barState === BarState.On) {
      this.barState = BarState.Auto;
    } else {
      this.barState = BarState.Off;
    }
  }

  private cycleBuiltInState(): void {
    if (this.builtInBarState === BarState.Off) {
      this.builtInBarState = BarState.On;
    } else if (this.builtInBarState === BarState.On) {
      this.builtInBarState = BarState.Auto;
    } else {
      this.builtInBarState = BarState.Off;
    }
  }

  private toggleEdgeEffect(): void {
    if (this.edgeEffect === EdgeEffect.Spring) {
      this.edgeEffect = EdgeEffect.Fade;
      this.edgeEffectName = 'Fade';
    } else if (this.edgeEffect === EdgeEffect.Fade) {
      this.edgeEffect = EdgeEffect.None;
      this.edgeEffectName = 'None';
    } else {
      this.edgeEffect = EdgeEffect.Spring;
      this.edgeEffectName = 'Spring';
    }
  }

  private refreshOffset(): void {
    const offset = this.scroller.currentOffset();
    if (offset) {
      this.offsetX = offset.xOffset;
      this.offsetY = offset.yOffset;
    }
  }

  @Builder
  scrollContent() {
    if (this.barDirection === ScrollBarDirection.Vertical) {
      Column({ space: 10 }) {
        ForEach(this.items, (item: number) => {
          Text('纵向内容 ' + item)
            .contentCard()
            .width('100%')
            .height(86)
            .fontSize(16)
            .textAlign(TextAlign.Center)
            .backgroundColor(item % 2 === 0 ? '#D6E4FF' : '#E8F3FF')
        }, (item: number) => item.toString())
      }
      .width('100%')
    } else {
      Row({ space: 10 }) {
        ForEach(this.items, (item: number) => {
          Text('横向内容 ' + item)
            .contentCard()
            .width(140)
            .height(120)
            .fontSize(16)
            .textAlign(TextAlign.Center)
            .backgroundColor(item % 2 === 0 ? '#D6E4FF' : '#E8F3FF')
        }, (item: number) => item.toString())
      }
      .padding({ left: 10, right: 10 })
    }
  }

  @Builder
  standaloneScrollBar() {
    ScrollBar({
      scroller: this.scroller,
      direction: this.barDirection,
      state: this.barState
    }) {
      Text()
        .width(this.barDirection === ScrollBarDirection.Vertical ? 14 : 72)
        .height(this.barDirection === ScrollBarDirection.Vertical ? 72 : 14)
        .borderRadius(10)
        .backgroundColor('#5B8DEF')
    }
    .width(this.barDirection === ScrollBarDirection.Vertical ? 18 : '100%')
    .height(this.barDirection === ScrollBarDirection.Vertical ? '100%' : 18)
    .backgroundColor('#E9ECEF')
    .enableNestedScroll(this.enableNestedScroll)
  }

  build() {
    Column({ space: 12 }) {
      Text('ScrollBar Comprehensive')
        .fontSize(24)
        .fontWeight(FontWeight.Bold)

      Text('方向：' + (this.barDirection === ScrollBarDirection.Vertical ? 'Vertical' : 'Horizontal') +
        '，独立滚动条：' + this.stateName(this.barState) +
        '，内置滚动条：' + this.stateName(this.builtInBarState) +
        '，X：' + this.offsetX.toFixed(0) + '，Y：' + this.offsetY.toFixed(0))
        .fontSize(14)
        .fontColor(Color.Gray)

      Flex({ wrap: FlexWrap.Wrap, space: { main: new LengthMetrics(8), cross: new LengthMetrics(8) } }) {
        Button('切换方向')
          .onClick(() => {
            this.cycleDirection();
          })
        Button('独立状态：' + this.stateName(this.barState))
          .onClick(() => {
            this.cycleBarState();
          })
        Button('嵌套：' + (this.enableNestedScroll ? '开' : '关'))
          .onClick(() => {
            this.enableNestedScroll = !this.enableNestedScroll;
          })
        Button('内置状态：' + this.stateName(this.builtInBarState))
          .onClick(() => {
            this.cycleBuiltInState();
          })
      }

      Flex({ wrap: FlexWrap.Wrap, space: { main: new LengthMetrics(8), cross: new LengthMetrics(8) } }) {
        Button('边缘：' + this.edgeEffectName)
          .onClick(() => {
            this.toggleEdgeEffect();
          })
        Button('摩擦：' + this.friction.toFixed(1))
          .onClick(() => {
            this.friction = this.friction < 0.7 ? 1.2 : 0.2;
          })
        Button('手势：' + (this.interactionEnabled ? '开' : '关'))
          .onClick(() => {
            this.interactionEnabled = !this.interactionEnabled;
          })
        Button('颜色：' + this.builtInColor)
          .onClick(() => {
            this.builtInColor = this.builtInColor === '#5B8DEF' ? '#F97316' : '#5B8DEF';
          })
      }

      Flex({ wrap: FlexWrap.Wrap, space: { main: new LengthMetrics(8), cross: new LengthMetrics(8) } }) {
        Button('条宽：' + this.builtInWidth)
          .onClick(() => {
            this.builtInWidth = this.builtInWidth >= 24 ? 6 : this.builtInWidth + 4;
          })
        Button('清空日志')
          .onClick(() => {
            this.clearLogs();
          })
        Button('事件日志：' + (this.eventLogEnabled ? '开' : '关'))
          .onClick(() => {
            this.eventLogEnabled = !this.eventLogEnabled;
          })
      }

      if (this.barDirection === ScrollBarDirection.Vertical) {
        Row({ space: 4 }) {
          Scroll(this.scroller) {
            this.scrollContent()
          }
          .layoutWeight(1)
          .height('100%')
          .scrollable(ScrollDirection.Vertical)
          .scrollBar(BarState.Off)
          .edgeEffect(this.edgeEffect)
          .friction(this.friction)
          .enableScrollInteraction(this.interactionEnabled)
          .onDidScroll((xOffset: number, yOffset: number, scrollState: ScrollState) => {
            this.refreshOffset();
            if (this.eventLogEnabled) {
              this.addLog('onDidScroll x=' + xOffset.toFixed(0) + ' y=' + yOffset.toFixed(0));
            }
          })
          .onScrollStart(() => {
            this.addLog('onScrollStart');
          })
          .onScrollStop(() => {
            this.addLog('onScrollStop');
            this.refreshOffset();
          })
          this.standaloneScrollBar()
        }
        .layoutWeight(1)
        .width('100%')
      } else {
        Column({ space: 4 }) {
          Scroll(this.scroller) {
            this.scrollContent()
          }
          .layoutWeight(1)
          .width('100%')
          .scrollable(ScrollDirection.Horizontal)
          .scrollBar(BarState.Off)
          .edgeEffect(this.edgeEffect)
          .friction(this.friction)
          .enableScrollInteraction(this.interactionEnabled)
          .onDidScroll((xOffset: number, yOffset: number, scrollState: ScrollState) => {
            this.refreshOffset();
            if (this.eventLogEnabled) {
              this.addLog('onDidScroll x=' + xOffset.toFixed(0) + ' y=' + yOffset.toFixed(0));
            }
          })
          .onScrollStart(() => {
            this.addLog('onScrollStart');
          })
          .onScrollStop(() => {
            this.addLog('onScrollStop');
            this.refreshOffset();
          })
          this.standaloneScrollBar()
        }
        .layoutWeight(1)
        .width('100%')
      }

      Text('内置滚动条演示（独立 ScrollBar 隐藏后启用）')
        .fontSize(14)
        .fontWeight(FontWeight.Medium)

      Scroll(this.builtInScroller) {
        Column({ space: 10 }) {
          ForEach(this.items, (item: number) => {
            Text('内置滚动条内容 ' + item)
              .width('100%')
              .height(76)
              .fontSize(15)
              .textAlign(TextAlign.Center)
              .borderRadius(10)
              .backgroundColor(item % 2 === 0 ? '#FFF3E0' : '#FFE0B2')
          }, (item: number) => item.toString())
        }
        .width('100%')
      }
      .height(200)
      .width('100%')
      .scrollable(ScrollDirection.Vertical)
      .scrollBar(this.builtInBarState)
      .scrollBarColor(this.builtInColor)
      .scrollBarWidth(this.builtInWidth)
      .edgeEffect(EdgeEffect.Spring)

      Column({ space: 4 }) {
        ForEach(this.logs, (log: string) => {
          Text(log)
            .width('100%')
            .fontSize(12)
            .fontColor(Color.Black)
            .padding({ left: 8, right: 8 })
        }, (log: string, index: number) => index.toString() + '-' + log)
      }
      .width('100%')
      .height(120)
      .padding(8)
      .borderRadius(10)
      .backgroundColor('#F1F3F5')
    }
    .width('100%')
    .height('100%')
    .padding(16)
  }
}
