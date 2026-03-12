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

import { typeNode } from '@kit.ArkUI';

@Entry
@Component
struct GridDeclare {
  private static readonly GRID_ID: string = 'GRID_ID';
  private static readonly WATER_FLOW_ID: string = 'WATER_FLOW_ID';
  private defaultGridScroller: Scroller = new Scroller();
  private defaultWaterFlowScroller: Scroller = new Scroller();
  private dynamicScroller: Scroller = new Scroller();

  @State private bindResult: string = 'Dynamic scroller not bound';
  @State private gridOffsetText: string = 'Grid default yOffset: 0';
  @State private waterFlowOffsetText: string = 'WaterFlow default yOffset: 0';
  @State private dynamicOffsetText: string = 'Dynamic yOffset: 0';
  @State private items: number[] = [];

  aboutToAppear(): void {
    this.items = [];
    for (let i = 0; i < 40; i++) {
      this.items.push(i);
    }
  }

  private bindGridController(): void {
    const frameNode = this.getUIContext().getFrameNodeById(GridDeclare.GRID_ID);
    if (!frameNode) {
      this.bindResult = 'Bind failed: FrameNode is null';
      return;
    }
    try {
      typeNode.bindController(frameNode, this.dynamicScroller, 'Grid');
      this.bindResult = 'Bind Grid success';
      this.refreshOffset();
    } catch (e) {
      this.bindResult = `Bind failed: code=${e.code}, msg=${e.message}`;
    }
  }

  private bindWaterFlowController(): void {
    const frameNode = this.getUIContext().getFrameNodeById(GridDeclare.WATER_FLOW_ID);
    if (!frameNode) {
      this.bindResult = 'Bind failed: FrameNode is null';
      return;
    }
    try {
      typeNode.bindController(frameNode, this.dynamicScroller, 'WaterFlow');
      this.bindResult = 'Bind WaterFlow success';
      this.refreshOffset();
    } catch (e) {
      this.bindResult = `Bind failed: code=${e.code}, msg=${e.message}`;
    }
  }

  private bindEmptyComponentController(): void {
    const frameNode = this.getUIContext().getFrameNodeById('NO_ID');
    try {
      typeNode.bindController(frameNode, this.dynamicScroller, 'Grid');
      this.bindResult = 'Bind success';
      this.refreshOffset();
    } catch (e) {
      this.bindResult = `Bind failed: code=${e.code}, msg=${e.message}`;
    }
  }

  private refreshOffset(): void {
    const gridOffset = this.defaultGridScroller.currentOffset()?.yOffset ?? 0;
    const waterFlowOffset = this.defaultWaterFlowScroller.currentOffset()?.yOffset ?? 0;
    const dynamicOffset = this.dynamicScroller.currentOffset()?.yOffset ?? 0;
    this.gridOffsetText = `Grid default yOffset: ${gridOffset}`;
    this.waterFlowOffsetText = `WaterFlow default yOffset: ${waterFlowOffset}`;
    this.dynamicOffsetText = `Dynamic yOffset: ${dynamicOffset}`;
  }

  private scrollBy(scroller: Scroller): void {
    scroller.scrollBy(0, 120);
    this.refreshOffset();
  }

  private scrollTop(scroller: Scroller): void {
    scroller.scrollEdge(Edge.Top);
    this.refreshOffset();
  }

  private scrollBottom(scroller: Scroller): void {
    scroller.scrollEdge(Edge.Bottom);
    this.refreshOffset();
  }

  build() {
    Column({ space: 10 }) {
      Text('Declarative Grid + WaterFlow Demo')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)

      Text(this.bindResult).fontSize(14)
      Text(this.gridOffsetText).fontSize(14)
      Text(this.waterFlowOffsetText).fontSize(14)
      Text(this.dynamicOffsetText).fontSize(14)

      Row({ space: 10 }) {
        Button('Bind Grid').onClick(() => {
          this.bindGridController();
        })
        Button('Bind WaterFlow').onClick(() => {
          this.bindWaterFlowController();
        })
      }

      Row({ space: 10 }) {
        Button('Bind Empty Component').onClick(() => {
          this.bindEmptyComponentController();
        })
        Button('Read Offsets').onClick(() => {
          this.refreshOffset();
        })
      }

      Text('Grid Default Scroller').fontSize(14).fontWeight(FontWeight.Medium)
      Row({ space: 10 }) {
        Button('Grid +120').onClick(() => {
          this.scrollBy(this.defaultGridScroller);
        })
        Button('Grid Top').onClick(() => {
          this.scrollTop(this.defaultGridScroller);
        })
        Button('Grid Bottom').onClick(() => {
          this.scrollBottom(this.defaultGridScroller);
        })
      }

      Text('WaterFlow Default Scroller').fontSize(14).fontWeight(FontWeight.Medium)
      Row({ space: 10 }) {
        Button('WaterFlow +120').onClick(() => {
          this.scrollBy(this.defaultWaterFlowScroller);
        })
        Button('WaterFlow Top').onClick(() => {
          this.scrollTop(this.defaultWaterFlowScroller);
        })
        Button('WaterFlow Bottom').onClick(() => {
          this.scrollBottom(this.defaultWaterFlowScroller);
        })
      }

      Text('Dynamic Scroller').fontSize(14).fontWeight(FontWeight.Medium)
      Row({ space: 10 }) {
        Button('Dynamic +120').onClick(() => {
          this.scrollBy(this.dynamicScroller);
        })
        Button('Dynamic Top').onClick(() => {
          this.scrollTop(this.dynamicScroller);
        })
        Button('Dynamic Bottom').onClick(() => {
          this.scrollBottom(this.dynamicScroller);
        })
      }

      Row({ space: 12 }) {
        Column({ space: 8 }) {
          Text('Grid Component')
            .fontSize(14)
            .fontWeight(FontWeight.Medium)

          Grid(this.defaultGridScroller, { regularSize: [1, 1] }) {
            ForEach(this.items, (idx: number) => {
              GridItem() {
                Text(`Grid Item ${idx}`)
                  .width('100%')
                  .height(48)
                  .textAlign(TextAlign.Center)
                  .backgroundColor(idx % 2 === 0 ? '#f1f3f5' : '#e9ecef')
              }
            })
          }
          .id(GridDeclare.GRID_ID)
          .columnsTemplate('1fr 1fr')
          .columnsGap(8)
          .rowsGap(8)
          .layoutWeight(1)
          .width('100%')
          .borderWidth(1)
          .borderColor('#d0d7de')
        }
        .width(0)
        .layoutWeight(1)
        .height('100%')
        .padding(8)
        .borderWidth(1)
        .borderColor('#e5e7eb')

        Column({ space: 8 }) {
          Text('WaterFlow Component')
            .fontSize(14)
            .fontWeight(FontWeight.Medium)

          WaterFlow({ scroller: this.defaultWaterFlowScroller }) {
            ForEach(this.items, (idx: number) => {
              FlowItem() {
                Text(`Flow Item ${idx}`)
                  .width('100%')
                  .textAlign(TextAlign.Center)
              }
              .width('100%')
              .height(48)
              .backgroundColor(idx % 2 === 0 ? '#dee2e6' : '#ced4da')
            })
          }
          .id(GridDeclare.WATER_FLOW_ID)
          .columnsTemplate('1fr 1fr')
          .columnsGap(8)
          .rowsGap(8)
          .layoutWeight(1)
          .width('100%')
          .borderWidth(1)
          .borderColor('#adb5bd')
        }
        .width(0)
        .layoutWeight(1)
        .height('100%')
        .padding(8)
        .borderWidth(1)
        .borderColor('#e5e7eb')
      }
      .layoutWeight(1)
      .width('100%')
      .alignItems(VerticalAlign.Top)
    }
    .padding(16)
    .width('100%')
    .height('100%')
  }
}