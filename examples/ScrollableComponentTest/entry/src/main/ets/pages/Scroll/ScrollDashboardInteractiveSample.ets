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
 * 综合场景：Scroll 仪表盘交互。
 * 覆盖能力：
 *   1. Scroller 控制器：scrollEdge / scrollPage / currentOffset / isAtEnd
 *   2. scrollSnap 与 enablePaging
 *   3. edgeEffect / friction
 *   4. scrollBar / scrollBarColor / scrollBarWidth
 *   5. enableScrollInteraction / fadingEdge / backToTop
 *   6. 滚动事件生命周期与日志反馈
 */

import { LengthMetrics } from '@kit.ArkUI';

@Entry
@Component
struct ScrollDashboardInteractiveSample {
  private scroller: Scroller = new Scroller();
  private itemNames: string[] = [
    '概览卡片', '数据看板', '趋势图', '任务列表', '消息中心',
    '性能指标', '告警记录', '运营报表', '用户增长', '系统日志'
  ];
  private itemValues: number[] = [
    86, 72, 91, 58, 64, 77, 83, 69, 95, 48
  ];

  @State scrollOffsetY: number = 0;
  @State isAtEnd: boolean = false;
  @State snapAlign: ScrollSnapAlign = ScrollSnapAlign.START;
  @State snapName: string = 'START';
  @State edgeEffect: EdgeEffect = EdgeEffect.Spring;
  @State edgeEffectName: string = 'Spring';
  @State friction: number = 0.6;
  @State barState: BarState = BarState.Auto;
  @State barColor: string = '#5B8DEF';
  @State barWidth: number = 10;
  @State interactionEnabled: boolean = true;
  @State fadingEdge: boolean = false;
  @State backToTop: boolean = false;
  @State enablePaging: boolean = false;
  @State eventLogEnabled: boolean = false;
  @State logs: string[] = [];

  @Styles
  dashboardCard() {
    .width('100%')
    .height(96)
    .padding(14)
    .borderRadius(14)
  }

  aboutToAppear(): void {
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

  private refreshState(): void {
    const offset = this.scroller.currentOffset();
    if (offset) {
      this.scrollOffsetY = offset.yOffset;
    }
    this.isAtEnd = this.scroller.isAtEnd();
  }

  private setSnapAlign(align: ScrollSnapAlign, name: string): void {
    this.snapAlign = align;
    this.snapName = name;
  }

  private cycleSnapAlign(): void {
    if (this.snapAlign === ScrollSnapAlign.START) {
      this.setSnapAlign(ScrollSnapAlign.CENTER, 'CENTER');
    } else if (this.snapAlign === ScrollSnapAlign.CENTER) {
      this.setSnapAlign(ScrollSnapAlign.END, 'END');
    } else if (this.snapAlign === ScrollSnapAlign.END) {
      this.setSnapAlign(ScrollSnapAlign.NONE, 'NONE');
    } else {
      this.setSnapAlign(ScrollSnapAlign.START, 'START');
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

  private barStateName(): string {
    if (this.barState === BarState.Off) {
      return 'Off';
    }
    if (this.barState === BarState.On) {
      return 'On';
    }
    return 'Auto';
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

  private edgeName(edge: Edge): string {
    if (edge === Edge.Top) {
      return 'Top';
    }
    if (edge === Edge.Bottom) {
      return 'Bottom';
    }
    if (edge === Edge.Start) {
      return 'Start';
    }
    return 'End';
  }

  private scrollToTop(): void {
    this.scroller.scrollEdge(Edge.Top);
    this.refreshState();
  }

  private scrollToBottom(): void {
    this.scroller.scrollEdge(Edge.Bottom, { velocity: 800 });
    this.refreshState();
  }

  private scrollNextPage(): void {
    this.scroller.scrollPage({ next: true, animation: true });
    this.refreshState();
  }

  private scrollPreviousPage(): void {
    this.scroller.scrollPage({ next: false, animation: true });
    this.refreshState();
  }

  build() {
    Column({ space: 12 }) {
      Text('Scroll Dashboard Interactive')
        .fontSize(24)
        .fontWeight(FontWeight.Bold)

      Text('Y 偏移：' + this.scrollOffsetY.toFixed(0) +
        '，底部：' + (this.isAtEnd ? '是' : '否') +
        '，Snap：' + this.snapName +
        '，边缘：' + this.edgeEffectName +
        '，滚动条：' + this.barStateName())
        .fontSize(14)
        .fontColor(Color.Gray)

      Flex({ wrap: FlexWrap.Wrap, space: { main: new LengthMetrics(8), cross: new LengthMetrics(8) } }) {
        Button('回顶')
          .onClick(() => {
            this.scrollToTop();
          })
        Button('到底')
          .onClick(() => {
            this.scrollToBottom();
          })
        Button('上一页')
          .onClick(() => {
            this.scrollPreviousPage();
          })
        Button('下一页')
          .onClick(() => {
            this.scrollNextPage();
          })
      }

      Flex({ wrap: FlexWrap.Wrap, space: { main: new LengthMetrics(8), cross: new LengthMetrics(8) } }) {
        Button('Snap：' + this.snapName)
          .onClick(() => {
            this.cycleSnapAlign();
          })
        Button('分页：' + (this.enablePaging ? '开' : '关'))
          .onClick(() => {
            this.enablePaging = !this.enablePaging;
          })
        Button('边缘：' + this.edgeEffectName)
          .onClick(() => {
            this.toggleEdgeEffect();
          })
        Button('手势：' + (this.interactionEnabled ? '开' : '关'))
          .onClick(() => {
            this.interactionEnabled = !this.interactionEnabled;
          })
      }

      Flex({ wrap: FlexWrap.Wrap, space: { main: new LengthMetrics(8), cross: new LengthMetrics(8) } }) {
        Button('摩擦：' + this.friction.toFixed(1))
          .onClick(() => {
            this.friction = this.friction < 0.7 ? 1.2 : 0.2;
          })
        Button('滚动条：' + this.barStateName())
          .onClick(() => {
            this.cycleBarState();
          })
        Button('条宽：' + this.barWidth)
          .onClick(() => {
            this.barWidth = this.barWidth >= 24 ? 6 : this.barWidth + 4;
          })
        Button('渐隐：' + (this.fadingEdge ? '开' : '关'))
          .onClick(() => {
            this.fadingEdge = !this.fadingEdge;
          })
      }

      Scroll(this.scroller) {
        Column({ space: 10 }) {
          ForEach(this.itemNames, (name: string, index: number) => {
            Row({ space: 10 }) {
              Column({ space: 4 }) {
                Text(name)
                  .fontSize(18)
                  .fontWeight(FontWeight.Medium)
                Text('当前数值：' + this.itemValues[index])
                  .fontSize(14)
                  .fontColor(Color.Gray)
              }
              .alignItems(HorizontalAlign.Start)
              .layoutWeight(1)

              Text(this.itemValues[index] >= 80 ? '优秀' : '待优化')
                .fontSize(14)
                .fontColor(Color.White)
                .padding({ left: 10, right: 10, top: 4, bottom: 4 })
                .borderRadius(8)
                .backgroundColor(this.itemValues[index] >= 80 ? '#34C759' : '#FF9F0A')
            }
            .dashboardCard()
            .backgroundColor(index % 2 === 0 ? '#D6E4FF' : '#E8F3FF')
          }, (name: string) => name)
        }
        .width('100%')
      }
      .layoutWeight(1)
      .width('100%')
      .scrollable(ScrollDirection.Vertical)
      .scrollBar(this.barState)
      .scrollBarColor(this.barColor)
      .scrollBarWidth(this.barWidth)
      .edgeEffect(this.edgeEffect)
      .friction(this.friction)
      .enableScrollInteraction(this.interactionEnabled)
      .fadingEdge(this.fadingEdge, { fadingEdgeLength: LengthMetrics.vp(80) })
      .backToTop(this.backToTop)
      .scrollSnap({
        snapAlign: this.snapAlign,
        enableSnapToStart: true,
        enableSnapToEnd: true
      })
      .enablePaging(this.enablePaging)
      .onWillScroll((xOffset: number, yOffset: number, scrollState: ScrollState, scrollSource: ScrollSource) => {
        if (this.eventLogEnabled) {
          this.addLog('onWillScroll y=' + yOffset.toFixed(0) +
            ' state=' + scrollState + ' source=' + scrollSource);
        }
      })
      .onDidScroll((xOffset: number, yOffset: number, scrollState: ScrollState) => {
        this.refreshState();
        if (this.eventLogEnabled) {
          this.addLog('onDidScroll y=' + yOffset.toFixed(0) + ' state=' + scrollState);
        }
      })
      .onScrollFrameBegin((offset: number, state: ScrollState) => {
        if (this.eventLogEnabled) {
          this.addLog('onScrollFrameBegin offset=' + offset.toFixed(0) + ' state=' + state);
        }
        return { offsetRemain: offset };
      })
      .onScrollStart(() => {
        this.addLog('onScrollStart');
      })
      .onScrollStop(() => {
        this.addLog('onScrollStop');
        this.refreshState();
      })
      .onScrollEdge((edge: Edge) => {
        this.addLog('onScrollEdge ' + this.edgeName(edge));
      })
      .onReachStart(() => {
        this.addLog('onReachStart');
      })
      .onReachEnd(() => {
        this.addLog('onReachEnd');
      })

      Flex({ wrap: FlexWrap.Wrap, space: { main: new LengthMetrics(8), cross: new LengthMetrics(8) } }) {
        Button('清空日志')
          .onClick(() => {
            this.clearLogs();
          })
        Button('事件日志：' + (this.eventLogEnabled ? '开' : '关'))
          .onClick(() => {
            this.eventLogEnabled = !this.eventLogEnabled;
          })
        Button('回顶开关：' + (this.backToTop ? '开' : '关'))
          .onClick(() => {
            this.backToTop = !this.backToTop;
          })
      }

      Text('事件日志')
        .fontSize(16)
        .fontWeight(FontWeight.Medium)

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
      .height(160)
      .padding(8)
      .borderRadius(10)
      .backgroundColor('#F1F3F5')
    }
    .width('100%')
    .height('100%')
    .padding(16)
  }
}
