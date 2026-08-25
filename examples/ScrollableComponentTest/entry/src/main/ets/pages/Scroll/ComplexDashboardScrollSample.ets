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

class DashboardCardItem {
  public id: number;
  public title: string;
  public desc: string;
  public value: string;
  public color: string;

  constructor(id: number, title: string, desc: string, value: string, color: string) {
    this.id = id;
    this.title = title;
    this.desc = desc;
    this.value = value;
    this.color = color;
  }
}

class DashboardSectionItem {
  public id: number;
  public title: string;
  public count: number;
  public color: string;

  constructor(id: number, title: string, count: number, color: string) {
    this.id = id;
    this.title = title;
    this.count = count;
    this.color = color;
  }
}

@Entry
@Component
struct ComplexDashboardScrollSample {
  private mainScroller: Scroller = new Scroller();
  private cardScroller: Scroller = new Scroller();
  private quickScroller: Scroller = new Scroller();
  private cards: DashboardCardItem[] = [
    new DashboardCardItem(1, '性能走势', 'onDidScroll 偏移统计', '86%', '#E8F3FF'),
    new DashboardCardItem(2, '边界触发', '顶部/底部 edge 计数', '12', '#FFF1E6'),
    new DashboardCardItem(3, '内容区块', '多段内容混排', '6', '#EAF8F0'),
    new DashboardCardItem(4, '控制器', 'scrollTo / scrollBy / scrollPage', '4', '#F4ECFF'),
    new DashboardCardItem(5, '横向滚动', '嵌套横向 Scroll', 'ON', '#FFF8DB'),
    new DashboardCardItem(6, '返回顶部', 'scrollEdge Top', 'READY', '#EAF2FF')
  ];
  private sections: DashboardSectionItem[] = [
    new DashboardSectionItem(1, '关键指标', 7, '#E8F3FF'),
    new DashboardSectionItem(2, '业务事件', 8, '#F9FAFB'),
    new DashboardSectionItem(3, '横向卡片', 5, '#FFF7ED'),
    new DashboardSectionItem(4, '长文本内容', 6, '#F0FDF4'),
    new DashboardSectionItem(5, '控制器验证', 6, '#F5F3FF'),
    new DashboardSectionItem(6, '底部越界', 7, '#EFF6FF')
  ];
  private quickActions: string[] = [
    '回到顶部',
    '下滚 320',
    '上一页',
    '下一页',
    '到顶部边缘',
    '到底部边缘',
    '横向左移',
    '横向右移'
  ];
  private rows: number[] = [];
  @State yOffset: number = 0;
  @State xOffset: number = 0;
  @State activeSection: number = 0;
  @State startCount: number = 0;
  @State stopCount: number = 0;
  @State topEdgeCount: number = 0;
  @State bottomEdgeCount: number = 0;
  @State reachStartCount: number = 0;
  @State reachEndCount: number = 0;
  @State didScrollCount: number = 0;
  @State commandCount: number = 0;
  @State selectedCount: number = 0;
  @State selectedCard: string = '未选择';
  @State infoText: string = '拖动主 Scroll 或点击快捷按钮观察状态';
  @State showDenseMode: boolean = false;
  @State enableFade: boolean = false;
  @State showBackToTop: boolean = true;

  aboutToAppear(): void {
    for (let i = 0; i < 36; i++) {
      this.rows.push(i);
    }
  }

  private getSectionName(): string {
    if (this.activeSection < 0 || this.activeSection >= this.sections.length) {
      return '顶部';
    }
    return this.sections[this.activeSection].title;
  }

  private updateActiveSection(offset: number): void {
    if (offset < 260) {
      this.activeSection = 0;
    } else if (offset < 760) {
      this.activeSection = 1;
    } else if (offset < 1260) {
      this.activeSection = 2;
    } else if (offset < 1760) {
      this.activeSection = 3;
    } else if (offset < 2260) {
      this.activeSection = 4;
    } else {
      this.activeSection = 5;
    }
  }

  private handleQuickAction(index: number): void {
    this.commandCount += 1;
    if (index === 0) {
      this.mainScroller.scrollTo({ xOffset: 0, yOffset: 0, animation: { duration: 300 } });
      this.infoText = '已执行 scrollTo 顶部';
    } else if (index === 1) {
      this.mainScroller.scrollBy(0, 320);
      this.infoText = '已执行 scrollBy(0, 320)';
    } else if (index === 2) {
      this.mainScroller.scrollPage({ next: false, animation: true });
      this.infoText = '已执行 scrollPage 上一页';
    } else if (index === 3) {
      this.mainScroller.scrollPage({ next: true, animation: true });
      this.infoText = '已执行 scrollPage 下一页';
    } else if (index === 4) {
      this.mainScroller.scrollEdge(Edge.Top);
      this.infoText = '已执行 scrollEdge Top';
    } else if (index === 5) {
      this.mainScroller.scrollEdge(Edge.Bottom, { velocity: 800 });
      this.infoText = '已执行 scrollEdge Bottom';
    } else if (index === 6) {
      this.cardScroller.scrollBy(-260, 0);
      this.infoText = '横向卡片向左滚动';
    } else {
      this.cardScroller.scrollBy(260, 0);
      this.infoText = '横向卡片向右滚动';
    }
  }

  private getRowColor(index: number): string {
    if (index % 3 === 0) {
      return '#FFFFFF';
    }
    if (index % 3 === 1) {
      return '#F8FAFC';
    }
    return '#F1F5F9';
  }

  @Builder
  private buildHeader() {
    Column({ space: 8 }) {
      Text('Complex Dashboard Scroll')
        .fontSize(24)
        .fontWeight(FontWeight.Bold)
        .fontColor('#101828')
        .width('100%')
      Text('复杂场景：主纵向 Scroll、横向 Scroll、控制器跳转、边缘事件、滚动状态统计组合。')
        .fontSize(13)
        .fontColor('#475467')
        .lineHeight(20)
        .width('100%')
    }
    .width('100%')
    .padding({ left: 14, right: 14, top: 14, bottom: 10 })
    .backgroundColor('#FFFFFF')
    .borderRadius(12)
  }

  @Builder
  private buildStatusPanel() {
    Column({ space: 8 }) {
      Row() {
        Text('当前分区：' + this.getSectionName())
          .fontSize(16)
          .fontWeight(FontWeight.Bold)
          .fontColor('#182230')
          .layoutWeight(1)
        Text('Y=' + this.yOffset.toFixed(0))
          .fontSize(14)
          .fontColor('#344054')
      }
      .width('100%')

      Row({ space: 8 }) {
        this.buildOffsetMetric()
        this.buildMoveMetric()
        this.buildCommandMetric()
        this.buildSelectMetric()
      }
      .width('100%')

      Row({ space: 8 }) {
        this.buildStartMetric()
        this.buildStopMetric()
        this.buildReachTopMetric()
        this.buildReachBottomMetric()
      }
      .width('100%')

      Text('状态：' + this.infoText)
        .fontSize(13)
        .fontColor('#667085')
        .lineHeight(19)
        .width('100%')
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#FFFFFF')
    .borderRadius(12)
  }

  @Builder
  private buildOffsetMetric() {
    Column({ space: 3 }) {
      Text('Offset')
        .fontSize(11)
        .fontColor('#667085')
      Text(this.yOffset.toFixed(0))
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
        .fontColor('#182230')
    }
    .height(56)
    .layoutWeight(1)
    .justifyContent(FlexAlign.Center)
    .alignItems(HorizontalAlign.Center)
    .backgroundColor('#E8F3FF')
    .borderRadius(10)
  }

  @Builder
  private buildMoveMetric() {
    Column({ space: 3 }) {
      Text('Move')
        .fontSize(11)
        .fontColor('#667085')
      Text(this.didScrollCount.toString())
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
        .fontColor('#182230')
    }
    .height(56)
    .layoutWeight(1)
    .justifyContent(FlexAlign.Center)
    .alignItems(HorizontalAlign.Center)
    .backgroundColor('#EAF8F0')
    .borderRadius(10)
  }

  @Builder
  private buildCommandMetric() {
    Column({ space: 3 }) {
      Text('Cmd')
        .fontSize(11)
        .fontColor('#667085')
      Text(this.commandCount.toString())
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
        .fontColor('#182230')
    }
    .height(56)
    .layoutWeight(1)
    .justifyContent(FlexAlign.Center)
    .alignItems(HorizontalAlign.Center)
    .backgroundColor('#FFF7ED')
    .borderRadius(10)
  }

  @Builder
  private buildSelectMetric() {
    Column({ space: 3 }) {
      Text('Select')
        .fontSize(11)
        .fontColor('#667085')
      Text(this.selectedCount.toString())
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
        .fontColor('#182230')
    }
    .height(56)
    .layoutWeight(1)
    .justifyContent(FlexAlign.Center)
    .alignItems(HorizontalAlign.Center)
    .backgroundColor('#F4ECFF')
    .borderRadius(10)
  }

  @Builder
  private buildStartMetric() {
    Column({ space: 3 }) {
      Text('Start')
        .fontSize(11)
        .fontColor('#667085')
      Text(this.startCount.toString())
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
        .fontColor('#182230')
    }
    .height(56)
    .layoutWeight(1)
    .justifyContent(FlexAlign.Center)
    .alignItems(HorizontalAlign.Center)
    .backgroundColor('#F9FAFB')
    .borderRadius(10)
  }

  @Builder
  private buildStopMetric() {
    Column({ space: 3 }) {
      Text('Stop')
        .fontSize(11)
        .fontColor('#667085')
      Text(this.stopCount.toString())
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
        .fontColor('#182230')
    }
    .height(56)
    .layoutWeight(1)
    .justifyContent(FlexAlign.Center)
    .alignItems(HorizontalAlign.Center)
    .backgroundColor('#F9FAFB')
    .borderRadius(10)
  }

  @Builder
  private buildReachTopMetric() {
    Column({ space: 3 }) {
      Text('ReachT')
        .fontSize(11)
        .fontColor('#667085')
      Text(this.reachStartCount.toString())
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
        .fontColor('#182230')
    }
    .height(56)
    .layoutWeight(1)
    .justifyContent(FlexAlign.Center)
    .alignItems(HorizontalAlign.Center)
    .backgroundColor('#F9FAFB')
    .borderRadius(10)
  }

  @Builder
  private buildReachBottomMetric() {
    Column({ space: 3 }) {
      Text('ReachB')
        .fontSize(11)
        .fontColor('#667085')
      Text(this.reachEndCount.toString())
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
        .fontColor('#182230')
    }
    .height(56)
    .layoutWeight(1)
    .justifyContent(FlexAlign.Center)
    .alignItems(HorizontalAlign.Center)
    .backgroundColor('#F9FAFB')
    .borderRadius(10)
  }

  @Builder
  private buildControlBar() {
    Column({ space: 8 }) {
      Flex({ wrap: FlexWrap.Wrap }) {
        Button(this.showDenseMode ? '紧凑：开' : '紧凑：关')
          .width('31%')
          .height(38)
          .fontSize(12)
          .margin({ right: 6, bottom: 6 })
          .onClick(() => {
            this.commandCount += 1;
            this.showDenseMode = !this.showDenseMode;
            this.infoText = this.showDenseMode ? '已切换紧凑列表高度' : '已恢复普通列表高度';
          })
        Button(this.enableFade ? 'Fade：开' : 'Fade：关')
          .width('31%')
          .height(38)
          .fontSize(12)
          .margin({ right: 6, bottom: 6 })
          .onClick(() => {
            this.commandCount += 1;
            this.enableFade = !this.enableFade;
            this.infoText = this.enableFade ? '已开启 fadingEdge' : '已关闭 fadingEdge';
          })
        Button(this.showBackToTop ? 'BackTop：开' : 'BackTop：关')
          .width('31%')
          .height(38)
          .fontSize(12)
          .margin({ right: 6, bottom: 6 })
          .onClick(() => {
            this.commandCount += 1;
            this.showBackToTop = !this.showBackToTop;
            this.infoText = this.showBackToTop ? '已开启 backToTop' : '已关闭 backToTop';
          })
      }
      .width('100%')

      Scroll(this.quickScroller) {
        Row({ space: 8 }) {
          ForEach(this.quickActions, (action: string, index: number) => {
            Button(action)
              .height(38)
              .onClick(() => {
                this.handleQuickAction(index);
              })
          }, (action: string) => action)
        }
        .padding({ left: 2, right: 2 })
      }
      .width('100%')
      .height(46)
      .scrollable(ScrollDirection.Horizontal)
      .scrollBar(BarState.Off)
      .edgeEffect(EdgeEffect.Spring)
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#FFFFFF')
    .borderRadius(12)
  }

  @Builder
  private buildHorizontalCards() {
    Column({ space: 8 }) {
      Row() {
        Text('横向卡片区')
          .fontSize(16)
          .fontWeight(FontWeight.Bold)
          .fontColor('#182230')
          .layoutWeight(1)
        Text('X=' + this.xOffset.toFixed(0))
          .fontSize(13)
          .fontColor('#667085')
      }
      .width('100%')

      Scroll(this.cardScroller) {
        Row({ space: 12 }) {
          ForEach(this.cards, (card: DashboardCardItem) => {
            Column({ space: 10 }) {
              Text(card.title)
                .fontSize(18)
                .fontWeight(FontWeight.Bold)
                .fontColor('#182230')
                .width('100%')
              Text(card.desc)
                .fontSize(12)
                .fontColor('#667085')
                .width('100%')
              Blank()
              Text(card.value)
                .fontSize(26)
                .fontWeight(FontWeight.Bold)
                .fontColor('#101828')
                .width('100%')
            }
            .width(210)
            .height(150)
            .padding(14)
            .backgroundColor(card.color)
            .borderRadius(14)
            .onClick(() => {
              this.selectedCount += 1;
              this.selectedCard = card.title;
              this.infoText = '已选择横向卡片：' + card.title;
            })
          }, (card: DashboardCardItem) => card.id.toString())
        }
        .padding({ left: 2, right: 2 })
      }
      .width('100%')
      .height(162)
      .scrollable(ScrollDirection.Horizontal)
      .scrollBar(BarState.Auto)
      .edgeEffect(EdgeEffect.Spring)
      .onDidScroll((xOffset: number) => {
        this.xOffset = xOffset;
      })

      Text('选中卡片：' + this.selectedCard)
        .fontSize(13)
        .fontColor('#475467')
        .width('100%')
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#FFFFFF')
    .borderRadius(12)
  }

  @Builder
  private buildSectionCard(section: DashboardSectionItem) {
    Column({ space: 10 }) {
      Row() {
        Text(section.title)
          .fontSize(18)
          .fontWeight(FontWeight.Bold)
          .fontColor('#182230')
          .layoutWeight(1)
        Text(section.count.toString() + ' items')
          .fontSize(12)
          .fontColor('#667085')
      }
      .width('100%')

      ForEach(this.rows, (row: number) => {
        if (row < section.count) {
          this.buildInfoRow(section, row)
        }
      }, (row: number) => section.id.toString() + '-' + row.toString())
    }
    .width('100%')
    .padding(12)
    .backgroundColor(section.color)
    .borderRadius(12)
  }

  @Builder
  private buildInfoRow(section: DashboardSectionItem, row: number) {
    Row({ space: 10 }) {
      Text((row + 1).toString())
        .width(34)
        .height(34)
        .textAlign(TextAlign.Center)
        .fontSize(14)
        .fontWeight(FontWeight.Bold)
        .fontColor('#344054')
        .backgroundColor('#FFFFFF')
        .borderRadius(17)
      Column({ space: 3 }) {
        Text(section.title + ' - 场景 ' + (row + 1).toString())
          .fontSize(14)
          .fontWeight(FontWeight.Medium)
          .fontColor('#182230')
          .width('100%')
        Text('用于观察复杂内容下的滚动偏移、事件回调和布局稳定性。')
          .fontSize(12)
          .fontColor('#667085')
          .lineHeight(18)
          .width('100%')
      }
      .layoutWeight(1)
    }
    .width('100%')
    .height(this.showDenseMode ? 54 : 68)
    .padding({ left: 10, right: 10 })
    .backgroundColor(this.getRowColor(row))
    .borderRadius(10)
  }

  build() {
    Scroll(this.mainScroller) {
      Column({ space: 10 }) {
        this.buildHeader()
        this.buildStatusPanel()
        this.buildControlBar()
        this.buildHorizontalCards()

        ForEach(this.sections, (section: DashboardSectionItem) => {
          this.buildSectionCard(section)
        }, (section: DashboardSectionItem) => section.id.toString())
      }
      .width('100%')
      .padding({ left: 14, right: 14, top: 14, bottom: 16 })
    }
    .width('100%')
    .height('100%')
    .scrollable(ScrollDirection.Vertical)
    .scrollBar(BarState.Auto)
    .scrollBarWidth(6)
    .scrollBarColor('#98A2B3')
    .edgeEffect(EdgeEffect.Spring)
    .fadingEdge(this.enableFade)
    .backToTop(this.showBackToTop)
    .backgroundColor('#F5F6FA')
    .onScrollStart(() => {
      this.startCount += 1;
      this.infoText = '主 Scroll 开始滚动';
    })
    .onScrollStop(() => {
      this.stopCount += 1;
      this.infoText = '主 Scroll 停止滚动';
    })
    .onReachStart(() => {
      this.reachStartCount += 1;
      this.infoText = '到达顶部：' + this.reachStartCount.toString();
    })
    .onReachEnd(() => {
      this.reachEndCount += 1;
      this.infoText = '到达底部：' + this.reachEndCount.toString();
    })
    .onScrollEdge((edge: Edge) => {
      if (edge === Edge.Top) {
        this.topEdgeCount += 1;
        this.infoText = '触发顶部越界：' + this.topEdgeCount.toString();
      } else if (edge === Edge.Bottom) {
        this.bottomEdgeCount += 1;
        this.infoText = '触发底部越界：' + this.bottomEdgeCount.toString();
      }
    })
    .onDidScroll((xOffset: number, yOffset: number, scrollState: ScrollState) => {
      this.didScrollCount += 1;
      this.yOffset += yOffset;
      if (this.yOffset < 0) {
        this.yOffset = 0;
      }
      this.updateActiveSection(this.yOffset);
    })
  }
}
