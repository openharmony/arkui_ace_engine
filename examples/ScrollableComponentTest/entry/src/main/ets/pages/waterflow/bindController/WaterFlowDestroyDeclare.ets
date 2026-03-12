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

import router from '@ohos.router';
import { typeNode } from '@kit.ArkUI';
import { WaterFlowControllerStore } from './WaterFlowControllerStore';

@Entry
@Component
struct WaterFlowDestroyDeclare {
  private static readonly COMPONENT_ID: string = 'COMPONENT_ID';
  private defaultScroller: Scroller = new Scroller();
  private dynamicScroller: Scroller = new Scroller();

  @State private bindResult: string = 'Dynamic scroller not bound';
  @State private defaultOffsetText: string = 'Default yOffset: 0';
  @State private dynamicOffsetText: string = 'Dynamic yOffset: 0';
  @State private items: number[] = [];
  @State private showWaterFlow: boolean = true;

  aboutToAppear(): void {
    this.initItems();
    this.resetPage();
  }

  onPageShow(): void {
    if (WaterFlowControllerStore.getNavigationMode() === 'push') {
      this.resetPage();
    }
  }

  private initItems(): void {
    this.items = [];
    for (let i = 0; i < 40; i++) {
      this.items.push(i);
    }
  }

  private resetPage(): void {
    this.showWaterFlow = true;
    this.bindResult = 'Dynamic scroller not bound';
    this.defaultOffsetText = 'Default yOffset: 0';
    this.dynamicOffsetText = 'Dynamic yOffset: 0';
    this.defaultScroller = new Scroller();
    this.dynamicScroller = new Scroller();
    WaterFlowControllerStore.setScroller(this.dynamicScroller);
    WaterFlowControllerStore.setResult('No controller call yet');
    WaterFlowControllerStore.setNavigationMode('push');
  }

  private bindScrollController(): boolean {
    const frameNode = this.getUIContext().getFrameNodeById(WaterFlowDestroyDeclare.COMPONENT_ID);
    if (!frameNode) {
      this.bindResult = 'Bind failed: FrameNode is null';
      return false;
    }
    try {
      typeNode.bindController(frameNode, this.dynamicScroller, 'WaterFlow');
      WaterFlowControllerStore.setScroller(this.dynamicScroller);
      this.bindResult = 'Bind success';
      this.refreshOffset();
      return true;
    } catch (e) {
      this.bindResult = `Bind failed: code=${e.code}, msg=${e.message}`;
      return false;
    }
  }

  private startDestroyTest(mode: string): void {
    if (!this.bindScrollController()) {
      return;
    }
    this.showWaterFlow = false;
    this.bindResult = `WaterFlow removed, entering child page by ${mode}`;
    WaterFlowControllerStore.setNavigationMode(mode);
    WaterFlowControllerStore.setResult(`WaterFlow host page left by ${mode}. Call methods on the bound controller below.`);
    setTimeout(() => {
      if (mode === 'replace') {
        router.replaceUrl({ url: 'pages/waterflow/bindController/WaterFlowDestroySubPage' });
      } else {
        router.pushUrl({ url: 'pages/waterflow/bindController/WaterFlowDestroySubPage' });
      }
    }, 100);
  }

  private refreshOffset(): void {
    const defaultOffset = this.defaultScroller.currentOffset()?.yOffset ?? 0;
    const dynamicOffset = this.dynamicScroller.currentOffset()?.yOffset ?? 0;
    this.defaultOffsetText = `Default yOffset: ${defaultOffset}`;
    this.dynamicOffsetText = `Dynamic yOffset: ${dynamicOffset}`;
  }

  build() {
    Column({ space: 12 }) {
      Text('Declarative WaterFlow Demo')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)

      Text(this.bindResult).fontSize(14)
      Text(this.defaultOffsetText).fontSize(14)
      Text(this.dynamicOffsetText).fontSize(14)

      Row({ space: 10 }) {
        Button('Bind Dynamic').onClick(() => {
          this.bindScrollController();
        })
        Button('Push Test').onClick(() => {
          this.startDestroyTest('push');
        })
        Button('Replace Test').onClick(() => {
          this.startDestroyTest('replace');
        })
      }

      Button('Read Offsets').onClick(() => {
        this.refreshOffset();
      })

      if (this.showWaterFlow) {
        WaterFlow({ scroller: this.defaultScroller }) {
          ForEach(this.items, (idx: number) => {
            FlowItem() {
              Text(`Item ${idx}`)
                .width('100%')
                .textAlign(TextAlign.Center)
            }
            .width('100%')
            .height(idx % 2 === 0 ? 48 : 72)
            .backgroundColor(idx % 2 === 0 ? '#f1f3f5' : '#e9ecef')
          })
        }
        .id(WaterFlowDestroyDeclare.COMPONENT_ID)
        .columnsTemplate('1fr 1fr')
        .columnsGap(8)
        .rowsGap(8)
        .layoutWeight(1)
        .width('100%')
        .borderWidth(1)
        .borderColor('#d0d7de')
      } else {
        Column({ space: 8 }) {
          Text('WaterFlow has been removed from the component tree.')
            .fontSize(14)
          Text('Waiting to enter child page...')
            .fontSize(14)
        }
        .layoutWeight(1)
        .width('100%')
        .justifyContent(FlexAlign.Center)
        .alignItems(HorizontalAlign.Center)
        .borderWidth(1)
        .borderColor('#d0d7de')
      }
    }
    .padding(16)
    .width('100%')
    .height('100%')
  }
}