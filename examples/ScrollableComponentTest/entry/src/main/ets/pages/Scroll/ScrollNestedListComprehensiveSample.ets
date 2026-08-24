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
 * 综合场景：外层 Scroll + 内层 List 的嵌套滚动。
 * 覆盖能力：
 *   1. NestedScrollMode：SELF_ONLY / SELF_FIRST / PARENT_FIRST / PARALLEL
 *   2. SELF_ONLY 模式下手动分发外层偏移（避免与 nestedScroll 重复消费）
 *   3. enableScrollInteraction / friction / edgeEffect
 *   4. 内层 List 与外层 Scroll 的控制器联动
 *   5. onReachStart / onReachEnd / onScrollStart / onScrollStop
 */

import { LengthMetrics } from '@kit.ArkUI';

@Entry
@Component
struct ScrollNestedListComprehensiveSample {
  private outerScroller: Scroller = new Scroller();
  private listScroller: Scroller = new Scroller();
  private listItems: number[] = [];

  @State forwardMode: NestedScrollMode = NestedScrollMode.PARENT_FIRST;
  @State backwardMode: NestedScrollMode = NestedScrollMode.SELF_FIRST;
  @State forwardName: string = 'PARENT_FIRST';
  @State backwardName: string = 'SELF_FIRST';
  @State outerInteractionEnabled: boolean = true;
  @State innerInteractionEnabled: boolean = true;
  @State outerFriction: number = 0.6;
  @State listPosition: number = 0;
  @State outerOffsetY: number = 0;
  @State outerIsAtEnd: boolean = false;
  @State eventLogEnabled: boolean = false;
  @State logs: string[] = [];

  @Styles
  listCard() {
    .width('100%')
    .height(72)
    .borderRadius(12)
  }

  aboutToAppear(): void {
    for (let i = 0; i < 30; i++) {
      this.listItems.push(i);
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

  private modeName(mode: NestedScrollMode): string {
    if (mode === NestedScrollMode.SELF_ONLY) {
      return 'SELF_ONLY';
    }
    if (mode === NestedScrollMode.SELF_FIRST) {
      return 'SELF_FIRST';
    }
    if (mode === NestedScrollMode.PARENT_FIRST) {
      return 'PARENT_FIRST';
    }
    return 'PARALLEL';
  }

  private cycleMode(current: NestedScrollMode): NestedScrollMode {
    if (current === NestedScrollMode.SELF_ONLY) {
      return NestedScrollMode.SELF_FIRST;
    }
    if (current === NestedScrollMode.SELF_FIRST) {
      return NestedScrollMode.PARENT_FIRST;
    }
    if (current === NestedScrollMode.PARENT_FIRST) {
      return NestedScrollMode.PARALLEL;
    }
    return NestedScrollMode.SELF_ONLY;
  }

  private cycleForwardMode(): void {
    this.forwardMode = this.cycleMode(this.forwardMode);
    this.forwardName = this.modeName(this.forwardMode);
  }

  private cycleBackwardMode(): void {
    this.backwardMode = this.cycleMode(this.backwardMode);
    this.backwardName = this.modeName(this.backwardMode);
  }

  private refreshOuterOffset(): void {
    const offset = this.outerScroller.currentOffset();
    if (offset) {
      this.outerOffsetY = offset.yOffset;
    }
    this.outerIsAtEnd = this.outerScroller.isAtEnd();
  }

  private scrollOuterToTop(): void {
    this.outerScroller.scrollEdge(Edge.Top);
    this.refreshOuterOffset();
  }

  private scrollOuterToBottom(): void {
    this.outerScroller.scrollEdge(Edge.Bottom, { velocity: 800 });
    this.refreshOuterOffset();
  }

  private scrollListToTop(): void {
    this.listScroller.scrollToIndex(0, false, ScrollAlign.START);
  }

  private scrollListToBottom(): void {
    this.listScroller.scrollToIndex(this.listItems.length - 1, false, ScrollAlign.END);
  }

  private positionName(): string {
    if (this.listPosition === 0) {
      return '顶部';
    }
    if (this.listPosition === 2) {
      return '底部';
    }
    return '中间';
  }

  build() {
    Column({ space: 12 }) {
      Text('Nested List + Scroll')
        .fontSize(24)
        .fontWeight(FontWeight.Bold)

      Text('前进：' + this.forwardName + '，后退：' + this.backwardName +
        '，List 位置：' + this.positionName() +
        '，外层 Y：' + this.outerOffsetY.toFixed(0) +
        '，外层底部：' + (this.outerIsAtEnd ? '是' : '否'))
        .fontSize(14)
        .fontColor(Color.Gray)

      Flex({ wrap: FlexWrap.Wrap, space: { main: new LengthMetrics(8), cross: new LengthMetrics(8) } }) {
        Button('切换前进')
          .onClick(() => {
            this.cycleForwardMode();
          })
        Button('切换后退')
          .onClick(() => {
            this.cycleBackwardMode();
          })
        Button('外层手势：' + (this.outerInteractionEnabled ? '开' : '关'))
          .onClick(() => {
            this.outerInteractionEnabled = !this.outerInteractionEnabled;
          })
        Button('内层手势：' + (this.innerInteractionEnabled ? '开' : '关'))
          .onClick(() => {
            this.innerInteractionEnabled = !this.innerInteractionEnabled;
          })
      }

      Flex({ wrap: FlexWrap.Wrap, space: { main: new LengthMetrics(8), cross: new LengthMetrics(8) } }) {
        Button('外层摩擦：' + this.outerFriction.toFixed(1))
          .onClick(() => {
            this.outerFriction = this.outerFriction < 0.7 ? 1.2 : 0.2;
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

      Flex({ wrap: FlexWrap.Wrap, space: { main: new LengthMetrics(8), cross: new LengthMetrics(8) } }) {
        Button('外层回顶')
          .onClick(() => {
            this.scrollOuterToTop();
          })
        Button('外层到底')
          .onClick(() => {
            this.scrollOuterToBottom();
          })
        Button('List 顶部')
          .onClick(() => {
            this.scrollListToTop();
          })
        Button('List 底部')
          .onClick(() => {
            this.scrollListToBottom();
          })
      }

      Scroll(this.outerScroller) {
        Column() {
          Text('外层 Scroll 头部区域')
            .width('100%')
            .height(180)
            .fontSize(20)
            .textAlign(TextAlign.Center)
            .fontColor(Color.White)
            .backgroundColor('#0080DC')

          List({ space: 10, scroller: this.listScroller }) {
            ForEach(this.listItems, (item: number) => {
              ListItem() {
                Text('List item ' + item)
                  .fontSize(16)
                  .textAlign(TextAlign.Center)
                  .backgroundColor(Color.White)
                  .fontColor(Color.Black)
              }
              .listCard()
            }, (item: number) => item.toString())
          }
          .width('100%')
          .height(480)
          .edgeEffect(EdgeEffect.Spring)
          .friction(0.6)
          .enableScrollInteraction(this.innerInteractionEnabled)
          .scrollBar(BarState.Off)
          .nestedScroll({
            scrollForward: this.forwardMode,
            scrollBackward: this.backwardMode
          })
          .onReachStart(() => {
            this.listPosition = 0;
            this.addLog('list onReachStart');
          })
          .onReachEnd(() => {
            this.listPosition = 2;
            this.addLog('list onReachEnd');
          })
          .onScrollStart(() => {
            this.addLog('list onScrollStart');
          })
          .onScrollStop(() => {
            this.addLog('list onScrollStop');
          })
          .onScrollFrameBegin((offset: number, state: ScrollState) => {
            if (this.eventLogEnabled) {
              this.addLog('list onScrollFrameBegin offset=' + offset.toFixed(0) + ' state=' + state);
            }
            // 仅在 SELF_ONLY 模式下手动转发，避免与 nestedScroll 的系统分发重复消费同一帧偏移。
            const shouldManualForward = (offset <= 0 && this.backwardMode === NestedScrollMode.SELF_ONLY) ||
              (offset >= 0 && this.forwardMode === NestedScrollMode.SELF_ONLY);
            if (shouldManualForward &&
              ((this.listPosition === 0 && offset <= 0) || (this.listPosition === 2 && offset >= 0))) {
              this.outerScroller.scrollBy(0, offset);
              return { offsetRemain: 0 };
            }
            this.listPosition = 1;
            return { offsetRemain: offset };
          })

          Text('外层 Scroll 底部区域')
            .width('100%')
            .height(160)
            .fontSize(20)
            .textAlign(TextAlign.Center)
            .fontColor(Color.White)
            .backgroundColor('#0080DC')
        }
        .width('100%')
      }
      .layoutWeight(1)
      .width('100%')
      .edgeEffect(EdgeEffect.Spring)
      .friction(this.outerFriction)
      .enableScrollInteraction(this.outerInteractionEnabled)
      .scrollBar(BarState.Auto)
      .onWillScroll((xOffset: number, yOffset: number, scrollState: ScrollState, scrollSource: ScrollSource) => {
        if (this.eventLogEnabled) {
          this.addLog('outer onWillScroll y=' + yOffset.toFixed(0) + ' state=' + scrollState);
        }
      })
      .onDidScroll((xOffset: number, yOffset: number, scrollState: ScrollState) => {
        this.refreshOuterOffset();
        if (this.eventLogEnabled) {
          this.addLog('outer onDidScroll y=' + yOffset.toFixed(0) + ' state=' + scrollState);
        }
      })
      .onScrollStart(() => {
        this.addLog('outer onScrollStart');
      })
      .onScrollStop(() => {
        this.addLog('outer onScrollStop');
        this.refreshOuterOffset();
      })
      .onScrollEdge((edge: Edge) => {
        this.addLog('outer onScrollEdge ' + edge);
      })

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
      .height(150)
      .padding(8)
      .borderRadius(10)
      .backgroundColor('#F1F3F5')
    }
    .width('100%')
    .height('100%')
    .padding(16)
  }
}
