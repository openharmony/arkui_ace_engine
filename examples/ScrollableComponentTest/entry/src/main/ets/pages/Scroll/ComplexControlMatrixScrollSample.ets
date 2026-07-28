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

class MatrixCellItem {
  public id: number;
  public title: string;
  public tag: string;
  public score: number;

  constructor(id: number, title: string, tag: string, score: number) {
    this.id = id;
    this.title = title;
    this.tag = tag;
    this.score = score;
  }
}

@Entry
@Component
struct ComplexControlMatrixScrollSample {
  private verticalScroller: Scroller = new Scroller();
  private horizontalScroller: Scroller = new Scroller();
  private matrixScroller: Scroller = new Scroller();
  private cells: MatrixCellItem[] = [];
  private modes: string[] = ['默认', '分页', '自由'];
  private edgeNames: string[] = ['Spring', 'Fade', 'None'];
  private zoomNames: string[] = ['1.0x', '0.8x', '1.2x'];
  @State modeIndex: number = 0;
  @State edgeIndex: number = 0;
  @State zoomIndex: number = 0;
  @State startOffset: number = 0;
  @State endOffset: number = 0;
  @State yOffset: number = 0;
  @State xOffset: number = 0;
  @State matrixXOffset: number = 0;
  @State matrixYOffset: number = 0;
  @State willScrollCount: number = 0;
  @State didScrollCount: number = 0;
  @State pageCount: number = 0;
  @State edgeCount: number = 0;
  @State commandCount: number = 0;
  @State modeChangeCount: number = 0;
  @State atEndText: string = '未知';
  @State lastSourceText: string = 'None';
  @State logText: string = '点击控制项或手势滚动，观察多个 Scroll 的联动状态。';
  @State compactCards: boolean = false;
  @State enableAlwaysEdge: boolean = false;
  @State enableFading: boolean = false;
  @State enableBackTop: boolean = false;

  aboutToAppear(): void {
    for (let i = 0; i < 48; i++) {
      this.cells.push(new MatrixCellItem(i, '任务 ' + (i + 1).toString(), this.getTagName(i), 60 + i % 35));
    }
  }

  private getTagName(index: number): string {
    if (index % 4 === 0) {
      return 'Layout';
    }
    if (index % 4 === 1) {
      return 'Event';
    }
    if (index % 4 === 2) {
      return 'Controller';
    }
    return 'Edge';
  }

  private getEdgeEffect(): EdgeEffect {
    if (this.edgeIndex === 1) {
      return EdgeEffect.Fade;
    }
    if (this.edgeIndex === 2) {
      return EdgeEffect.None;
    }
    return EdgeEffect.Spring;
  }

  private getDirection(): ScrollDirection {
    if (this.modeIndex === 2) {
      return ScrollDirection.FREE;
    }
    return ScrollDirection.Vertical;
  }

  private getZoomScale(): number {
    if (this.zoomIndex === 1) {
      return 0.8;
    }
    if (this.zoomIndex === 2) {
      return 1.2;
    }
    return 1.0;
  }

  private getCellColor(index: number): string {
    if (index % 4 === 0) {
      return '#E8F3FF';
    }
    if (index % 4 === 1) {
      return '#ECFDF3';
    }
    if (index % 4 === 2) {
      return '#FFF7ED';
    }
    return '#F5F3FF';
  }

  private getScoreColor(score: number): string {
    if (score >= 85) {
      return '#027A48';
    }
    if (score >= 72) {
      return '#B54708';
    }
    return '#B42318';
  }

  private cycleMode(): void {
    this.modeChangeCount += 1;
    this.modeIndex += 1;
    if (this.modeIndex >= this.modes.length) {
      this.modeIndex = 0;
    }
    this.logText = '主 Scroll 模式切换为：' + this.modes[this.modeIndex];
  }

  private cycleEdge(): void {
    this.modeChangeCount += 1;
    this.edgeIndex += 1;
    if (this.edgeIndex >= this.edgeNames.length) {
      this.edgeIndex = 0;
    }
    this.logText = '边缘效果切换为：' + this.edgeNames[this.edgeIndex];
  }

  private cycleZoom(): void {
    this.modeChangeCount += 1;
    this.zoomIndex += 1;
    if (this.zoomIndex >= this.zoomNames.length) {
      this.zoomIndex = 0;
    }
    this.logText = '缩放切换为：' + this.zoomNames[this.zoomIndex];
  }

  private updateAtEnd(): void {
    this.atEndText = this.verticalScroller.isAtEnd() ? '是' : '否';
    this.logText = '已读取 isAtEnd：' + this.atEndText;
  }

  private syncOffsets(): void {
    let verticalOffset = this.verticalScroller.currentOffset();
    if (verticalOffset !== undefined) {
      this.yOffset = verticalOffset.yOffset;
    }

    let horizontalOffset = this.horizontalScroller.currentOffset();
    if (horizontalOffset !== undefined) {
      this.xOffset = horizontalOffset.xOffset;
    }

    let matrixOffset = this.matrixScroller.currentOffset();
    if (matrixOffset !== undefined) {
      this.matrixXOffset = matrixOffset.xOffset;
      this.matrixYOffset = matrixOffset.yOffset;
    }
  }

  private runCommand(command: number): void {
    this.commandCount += 1;
    if (command === 0) {
      this.verticalScroller.scrollTo({ xOffset: 0, yOffset: 0, animation: { duration: 300 } });
      this.logText = 'scrollTo 顶部';
    } else if (command === 1) {
      this.verticalScroller.scrollBy(0, 240);
      this.logText = 'scrollBy 向下 240';
    } else if (command === 2) {
      this.verticalScroller.scrollPage({ next: true, animation: true });
      this.pageCount += 1;
      this.logText = 'scrollPage 下一页';
    } else if (command === 3) {
      this.verticalScroller.scrollPage({ next: false, animation: true });
      this.pageCount += 1;
      this.logText = 'scrollPage 上一页';
    } else if (command === 4) {
      this.verticalScroller.scrollEdge(Edge.Bottom, { velocity: 900 });
      this.logText = 'scrollEdge 到底部';
    } else if (command === 5) {
      this.horizontalScroller.scrollBy(260, 0);
      this.logText = '顶部横向 Scroll 右移';
    } else if (command === 6) {
      this.matrixScroller.scrollBy(120, 120);
      this.logText = '矩阵 FREE Scroll 斜向滚动';
    } else {
      this.updateAtEnd();
    }
    this.syncOffsets();
    setTimeout(() => {
      this.syncOffsets();
    }, 350);
  }

  @Builder
  private buildTitle() {
    Column({ space: 8 }) {
      Text('Complex Control Matrix Scroll')
        .fontSize(24)
        .fontWeight(FontWeight.Bold)
        .fontColor('#101828')
        .width('100%')
      Text('复杂场景：多控制器、多 ScrollDirection、edgeEffect、content offset、paging、FREE 滚动矩阵。')
        .fontSize(13)
        .fontColor('#475467')
        .lineHeight(20)
        .width('100%')
    }
    .width('100%')
    .padding(14)
    .backgroundColor('#FFFFFF')
    .borderRadius(12)
  }

  @Builder
  private buildSwitchPanel() {
    Column({ space: 8 }) {
      Flex({ wrap: FlexWrap.Wrap }) {
        Button('模式：' + this.modes[this.modeIndex])
          .width('31%')
          .height(38)
          .fontSize(12)
          .margin({ right: 6, bottom: 6 })
          .onClick(() => {
            this.cycleMode();
          })
        Button('边缘：' + this.edgeNames[this.edgeIndex])
          .width('31%')
          .height(38)
          .fontSize(12)
          .margin({ right: 6, bottom: 6 })
          .onClick(() => {
            this.cycleEdge();
          })
        Button('缩放：' + this.zoomNames[this.zoomIndex])
          .width('31%')
          .height(38)
          .fontSize(12)
          .margin({ right: 6, bottom: 6 })
          .onClick(() => {
            this.cycleZoom();
          })
      }
      .width('100%')

      Flex({ wrap: FlexWrap.Wrap }) {
        Button(this.compactCards ? '卡片紧凑：开' : '卡片紧凑：关')
          .width('48%')
          .height(38)
          .fontSize(12)
          .margin({ right: 6, bottom: 6 })
          .onClick(() => {
            this.commandCount += 1;
            this.compactCards = !this.compactCards;
            this.logText = this.compactCards ? '列表卡片高度压缩' : '列表卡片恢复高度';
          })
        Button(this.enableAlwaysEdge ? '越界常开：开' : '越界常开：关')
          .width('48%')
          .height(38)
          .fontSize(12)
          .margin({ right: 6, bottom: 6 })
          .onClick(() => {
            this.commandCount += 1;
            this.enableAlwaysEdge = !this.enableAlwaysEdge;
            this.logText = this.enableAlwaysEdge ? 'edgeEffect alwaysEnabled 开启' : 'edgeEffect alwaysEnabled 关闭';
          })
      }
      .width('100%')

      Flex({ wrap: FlexWrap.Wrap }) {
        Button(this.enableFading ? 'Fading：开' : 'Fading：关')
          .width('48%')
          .height(38)
          .fontSize(12)
          .margin({ right: 6, bottom: 6 })
          .onClick(() => {
            this.commandCount += 1;
            this.enableFading = !this.enableFading;
            this.logText = this.enableFading ? 'fadingEdge 开启' : 'fadingEdge 关闭';
          })
        Button(this.enableBackTop ? 'BackTop：开' : 'BackTop：关')
          .width('48%')
          .height(38)
          .fontSize(12)
          .margin({ right: 6, bottom: 6 })
          .onClick(() => {
            this.commandCount += 1;
            this.enableBackTop = !this.enableBackTop;
            this.logText = this.enableBackTop ? 'backToTop 开启' : 'backToTop 关闭';
          })
      }
      .width('100%')
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#FFFFFF')
    .borderRadius(12)
  }

  @Builder
  private buildOffsetPanel() {
    Column({ space: 8 }) {
      Row() {
        Text('Content Offset 调节')
          .fontSize(16)
          .fontWeight(FontWeight.Bold)
          .fontColor('#182230')
          .layoutWeight(1)
        Text('start=' + this.startOffset.toString() + ', end=' + this.endOffset.toString())
          .fontSize(12)
          .fontColor('#667085')
      }
      .width('100%')

      Flex({ wrap: FlexWrap.Wrap }) {
        Button('start +20')
          .width('48%')
          .height(38)
          .fontSize(12)
          .margin({ right: 6, bottom: 6 })
          .onClick(() => {
            this.commandCount += 1;
            this.startOffset += 20;
            this.logText = 'contentStartOffset 增加到 ' + this.startOffset.toString();
          })
        Button('start -20')
          .width('48%')
          .height(38)
          .fontSize(12)
          .margin({ right: 6, bottom: 6 })
          .onClick(() => {
            this.commandCount += 1;
            if (this.startOffset >= 20) {
              this.startOffset -= 20;
            }
            this.logText = 'contentStartOffset 减少到 ' + this.startOffset.toString();
          })
        Button('end +20')
          .width('48%')
          .height(38)
          .fontSize(12)
          .margin({ right: 6, bottom: 6 })
          .onClick(() => {
            this.commandCount += 1;
            this.endOffset += 20;
            this.logText = 'contentEndOffset 增加到 ' + this.endOffset.toString();
          })
        Button('end -20')
          .width('48%')
          .height(38)
          .fontSize(12)
          .margin({ right: 6, bottom: 6 })
          .onClick(() => {
            this.commandCount += 1;
            if (this.endOffset >= 20) {
              this.endOffset -= 20;
            }
            this.logText = 'contentEndOffset 减少到 ' + this.endOffset.toString();
          })
      }
      .width('100%')
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#FFFFFF')
    .borderRadius(12)
  }

  @Builder
  private buildCommandPanel() {
    Column({ space: 8 }) {
      Flex({ wrap: FlexWrap.Wrap }) {
        Button('顶部')
          .width('48%')
          .height(38)
          .fontSize(12)
          .margin({ right: 6, bottom: 6 })
          .onClick(() => {
            this.runCommand(0);
          })
        Button('下滚')
          .width('48%')
          .height(38)
          .fontSize(12)
          .margin({ right: 6, bottom: 6 })
          .onClick(() => {
            this.runCommand(1);
          })
        Button('下一页')
          .width('48%')
          .height(38)
          .fontSize(12)
          .margin({ right: 6, bottom: 6 })
          .onClick(() => {
            this.runCommand(2);
          })
        Button('上一页')
          .width('48%')
          .height(38)
          .fontSize(12)
          .margin({ right: 6, bottom: 6 })
          .onClick(() => {
            this.runCommand(3);
          })
      }
      .width('100%')

      Flex({ wrap: FlexWrap.Wrap }) {
        Button('到底')
          .width('48%')
          .height(38)
          .fontSize(12)
          .margin({ right: 6, bottom: 6 })
          .onClick(() => {
            this.runCommand(4);
          })
        Button('横向右移')
          .width('48%')
          .height(38)
          .fontSize(12)
          .margin({ right: 6, bottom: 6 })
          .onClick(() => {
            this.runCommand(5);
          })
        Button('矩阵斜滚')
          .width('48%')
          .height(38)
          .fontSize(12)
          .margin({ right: 6, bottom: 6 })
          .onClick(() => {
            this.runCommand(6);
          })
        Button('isAtEnd')
          .width('48%')
          .height(38)
          .fontSize(12)
          .margin({ right: 6, bottom: 6 })
          .onClick(() => {
            this.runCommand(7);
          })
      }
      .width('100%')
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#FFFFFF')
    .borderRadius(12)
  }

  @Builder
  private buildTelemetryPanel() {
    Column({ space: 8 }) {
      Row({ space: 8 }) {
        this.buildYMetric()
        this.buildDidMetric()
        this.buildCommandMetric()
        this.buildModeMetric()
      }
      .width('100%')

      Row({ space: 8 }) {
        this.buildXMetric()
        this.buildMatrixXMetric()
        this.buildMatrixYMetric()
        this.buildEdgeMetric()
      }
      .width('100%')

      Text('Source=' + this.lastSourceText + '，isAtEnd=' + this.atEndText)
        .fontSize(13)
        .fontColor('#344054')
        .width('100%')
      Text('Log：' + this.logText)
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
  private buildYMetric() {
    Column({ space: 2 }) {
      Text('Y')
        .fontSize(11)
        .fontColor('#667085')
      Text(this.yOffset.toFixed(0))
        .fontSize(15)
        .fontWeight(FontWeight.Bold)
        .fontColor('#182230')
    }
    .height(52)
    .layoutWeight(1)
    .justifyContent(FlexAlign.Center)
    .alignItems(HorizontalAlign.Center)
    .backgroundColor('#E8F3FF')
    .borderRadius(10)
  }

  @Builder
  private buildDidMetric() {
    Column({ space: 2 }) {
      Text('Did')
        .fontSize(11)
        .fontColor('#667085')
      Text(this.didScrollCount.toString())
        .fontSize(15)
        .fontWeight(FontWeight.Bold)
        .fontColor('#182230')
    }
    .height(52)
    .layoutWeight(1)
    .justifyContent(FlexAlign.Center)
    .alignItems(HorizontalAlign.Center)
    .backgroundColor('#ECFDF3')
    .borderRadius(10)
  }

  @Builder
  private buildCommandMetric() {
    Column({ space: 2 }) {
      Text('Cmd')
        .fontSize(11)
        .fontColor('#667085')
      Text(this.commandCount.toString())
        .fontSize(15)
        .fontWeight(FontWeight.Bold)
        .fontColor('#182230')
    }
    .height(52)
    .layoutWeight(1)
    .justifyContent(FlexAlign.Center)
    .alignItems(HorizontalAlign.Center)
    .backgroundColor('#FFF7ED')
    .borderRadius(10)
  }

  @Builder
  private buildModeMetric() {
    Column({ space: 2 }) {
      Text('Mode')
        .fontSize(11)
        .fontColor('#667085')
      Text(this.modeChangeCount.toString())
        .fontSize(15)
        .fontWeight(FontWeight.Bold)
        .fontColor('#182230')
    }
    .height(52)
    .layoutWeight(1)
    .justifyContent(FlexAlign.Center)
    .alignItems(HorizontalAlign.Center)
    .backgroundColor('#F5F3FF')
    .borderRadius(10)
  }

  @Builder
  private buildXMetric() {
    Column({ space: 2 }) {
      Text('X')
        .fontSize(11)
        .fontColor('#667085')
      Text(this.xOffset.toFixed(0))
        .fontSize(15)
        .fontWeight(FontWeight.Bold)
        .fontColor('#182230')
    }
    .height(52)
    .layoutWeight(1)
    .justifyContent(FlexAlign.Center)
    .alignItems(HorizontalAlign.Center)
    .backgroundColor('#F9FAFB')
    .borderRadius(10)
  }

  @Builder
  private buildMatrixXMetric() {
    Column({ space: 2 }) {
      Text('MX')
        .fontSize(11)
        .fontColor('#667085')
      Text(this.matrixXOffset.toFixed(0))
        .fontSize(15)
        .fontWeight(FontWeight.Bold)
        .fontColor('#182230')
    }
    .height(52)
    .layoutWeight(1)
    .justifyContent(FlexAlign.Center)
    .alignItems(HorizontalAlign.Center)
    .backgroundColor('#F9FAFB')
    .borderRadius(10)
  }

  @Builder
  private buildMatrixYMetric() {
    Column({ space: 2 }) {
      Text('MY')
        .fontSize(11)
        .fontColor('#667085')
      Text(this.matrixYOffset.toFixed(0))
        .fontSize(15)
        .fontWeight(FontWeight.Bold)
        .fontColor('#182230')
    }
    .height(52)
    .layoutWeight(1)
    .justifyContent(FlexAlign.Center)
    .alignItems(HorizontalAlign.Center)
    .backgroundColor('#F9FAFB')
    .borderRadius(10)
  }

  @Builder
  private buildEdgeMetric() {
    Column({ space: 2 }) {
      Text('Edge')
        .fontSize(11)
        .fontColor('#667085')
      Text(this.edgeCount.toString())
        .fontSize(15)
        .fontWeight(FontWeight.Bold)
        .fontColor('#182230')
    }
    .height(52)
    .layoutWeight(1)
    .justifyContent(FlexAlign.Center)
    .alignItems(HorizontalAlign.Center)
    .backgroundColor('#F9FAFB')
    .borderRadius(10)
  }

  @Builder
  private buildHorizontalStrip() {
    Column({ space: 8 }) {
      Text('顶部横向 Scroll')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
        .fontColor('#182230')
        .width('100%')

      Scroll(this.horizontalScroller) {
        Row({ space: 10 }) {
          ForEach(this.cells, (cell: MatrixCellItem) => {
            if (cell.id < 12) {
              Column({ space: 8 }) {
                Text(cell.title)
                  .fontSize(16)
                  .fontWeight(FontWeight.Bold)
                  .fontColor('#182230')
                  .width('100%')
                Text(cell.tag)
                  .fontSize(12)
                  .fontColor('#667085')
                  .width('100%')
                Text(cell.score.toString())
                  .fontSize(24)
                  .fontWeight(FontWeight.Bold)
                  .fontColor(this.getScoreColor(cell.score))
                  .width('100%')
              }
              .width(160)
              .height(128)
              .padding(12)
              .backgroundColor(this.getCellColor(cell.id))
              .borderRadius(12)
            }
          }, (cell: MatrixCellItem) => 'strip-' + cell.id.toString())
        }
      }
      .width('100%')
      .height(140)
      .scrollable(ScrollDirection.Horizontal)
      .scrollBar(BarState.Auto)
      .edgeEffect(EdgeEffect.Spring)
      .onDidScroll((xOffset: number, yOffset: number, scrollState: ScrollState) => {
        this.xOffset += xOffset;
        if (this.xOffset < 0) {
          this.xOffset = 0;
        }
      })
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#FFFFFF')
    .borderRadius(12)
  }

  @Builder
  private buildFreeMatrix() {
    Column({ space: 8 }) {
      Text('FREE 矩阵 Scroll')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
        .fontColor('#182230')
        .width('100%')

      Scroll(this.matrixScroller) {
        Column({ space: 10 }) {
          ForEach([0, 1, 2, 3, 4, 5], (row: number) => {
            Row({ space: 10 }) {
              ForEach([0, 1, 2, 3, 4, 5], (col: number) => {
                this.buildMatrixBlock(row, col)
              }, (col: number) => row.toString() + '-' + col.toString())
            }
          }, (row: number) => row.toString())
        }
        .padding(8)
      }
      .width('100%')
      .height(250)
      .scrollable(ScrollDirection.FREE)
      .scrollBar(BarState.Auto)
      .edgeEffect(EdgeEffect.Spring)
      .onDidScroll((xOffset: number, yOffset: number, scrollState: ScrollState) => {
        this.matrixXOffset += xOffset;
        this.matrixYOffset += yOffset;
        if (this.matrixXOffset < 0) {
          this.matrixXOffset = 0;
        }
        if (this.matrixYOffset < 0) {
          this.matrixYOffset = 0;
        }
      })
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#FFFFFF')
    .borderRadius(12)
  }

  @Builder
  private buildMatrixBlock(row: number, col: number) {
    Column({ space: 4 }) {
      Text('R' + row.toString() + ' C' + col.toString())
        .fontSize(14)
        .fontWeight(FontWeight.Bold)
        .fontColor('#182230')
      Text('free')
        .fontSize(11)
        .fontColor('#667085')
    }
    .width(120)
    .height(92)
    .justifyContent(FlexAlign.Center)
    .alignItems(HorizontalAlign.Center)
    .backgroundColor(this.getCellColor(row + col))
    .borderRadius(10)
  }

  @Builder
  private buildVerticalList() {
    Column({ space: 10 }) {
      Text('主纵向列表')
        .fontSize(16)
        .fontWeight(FontWeight.Bold)
        .fontColor('#182230')
        .width('100%')

      ForEach(this.cells, (cell: MatrixCellItem) => {
        this.buildVerticalCell(cell)
      }, (cell: MatrixCellItem) => cell.id.toString())
    }
    .width('100%')
    .padding(12)
    .backgroundColor('#FFFFFF')
    .borderRadius(12)
  }

  @Builder
  private buildVerticalCell(cell: MatrixCellItem) {
    Row({ space: 10 }) {
      Text(cell.id.toString())
        .width(38)
        .height(38)
        .fontSize(14)
        .fontWeight(FontWeight.Bold)
        .fontColor('#344054')
        .textAlign(TextAlign.Center)
        .backgroundColor(this.getCellColor(cell.id))
        .borderRadius(19)
      Column({ space: 4 }) {
        Row() {
          Text(cell.title)
            .fontSize(15)
            .fontWeight(FontWeight.Bold)
            .fontColor('#182230')
            .layoutWeight(1)
          Text(cell.tag)
            .fontSize(12)
            .fontColor('#667085')
        }
        .width('100%')
        Text('score=' + cell.score.toString() + '，用于验证动态高度列表与控制器滚动。')
          .fontSize(12)
          .fontColor('#667085')
          .lineHeight(18)
          .width('100%')
      }
      .layoutWeight(1)
    }
    .width('100%')
    .height(this.compactCards ? 58 : 78)
    .padding({ left: 10, right: 10 })
    .backgroundColor(cell.id % 2 === 0 ? '#FFFFFF' : '#F8FAFC')
    .borderRadius(10)
  }

  build() {
    Scroll(this.verticalScroller) {
      Column({ space: 10 }) {
        this.buildTitle()
        this.buildSwitchPanel()
        this.buildOffsetPanel()
        this.buildCommandPanel()
        this.buildTelemetryPanel()
        this.buildHorizontalStrip()
        this.buildFreeMatrix()
        this.buildVerticalList()
      }
      .width('100%')
      .padding({ left: 14, right: 14, top: 14, bottom: 16 })
    }
    .width('100%')
    .height('100%')
    .scrollable(this.getDirection())
    .scrollBar(BarState.Auto)
    .scrollBarWidth(8)
    .scrollBarColor('#667085')
    .edgeEffect(this.getEdgeEffect(), { alwaysEnabled: this.enableAlwaysEdge })
    .contentStartOffset(this.startOffset)
    .contentEndOffset(this.endOffset)
    .enablePaging(this.modeIndex === 1)
    .zoomScale(this.getZoomScale())
    .fadingEdge(this.enableFading)
    .backToTop(this.enableBackTop)
    .backgroundColor('#F5F6FA')
    .onWillScroll((xOffset: number, yOffset: number, state: ScrollState, source: ScrollSource) => {
      this.willScrollCount += 1;
      this.lastSourceText = source.toString();
    })
    .onDidScroll((xOffset: number, yOffset: number, scrollState: ScrollState) => {
      this.didScrollCount += 1;
      this.yOffset += yOffset;
      if (this.yOffset < 0) {
        this.yOffset = 0;
      }
    })
    .onScrollEdge((edge: Edge) => {
      this.edgeCount += 1;
      this.logText = edge === Edge.Top ? '主 Scroll 顶部越界' : '主 Scroll 底部越界';
    })
    .onReachEnd(() => {
      this.atEndText = '是';
    })
    .onReachStart(() => {
      this.atEndText = '否';
    })
  }
}
