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
struct ScrollDeclare {
  private static readonly COMPONENT_ID: string = 'COMPONENT_ID';
  private defaultScroller: Scroller = new Scroller();
  private dynamicScroller: Scroller = new Scroller();
  @State private bindResult: string = 'Dynamic scroller not bound';
  @State private defaultOffsetText: string = 'Default yOffset: 0';
  @State private dynamicOffsetText: string = 'Dynamic yOffset: 0';
  @State private items: number[] = [];

  aboutToAppear(): void {
    this.items = [];
    for (let i = 0; i < 40; i++) {
      this.items.push(i);
    }
  }

  private bindScrollController(): void {
    const frameNode = this.getUIContext().getFrameNodeById(ScrollDeclare.COMPONENT_ID);
    if (!frameNode) {
      this.bindResult = 'Bind failed: FrameNode is null';
      return;
    }
    try {
      typeNode.bindController(frameNode, this.dynamicScroller, 'Scroll');
      this.bindResult = 'Bind success';
      this.refreshOffset();
    } catch (e) {
      this.bindResult = `Bind failed: code=${e.code}, msg=${e.message}`;
    }
  }

  private refreshOffset(): void {
    const defaultOffset = this.defaultScroller.currentOffset()?.yOffset ?? 0;
    const dynamicOffset = this.dynamicScroller.currentOffset()?.yOffset ?? 0;
    this.defaultOffsetText = `Default yOffset: ${defaultOffset}`;
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
    Column({ space: 12 }) {
      Text('Declarative Scroll Demo')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)

      Text(this.bindResult).fontSize(14)
      Text(this.defaultOffsetText).fontSize(14)
      Text(this.dynamicOffsetText).fontSize(14)

      Row({ space: 10 }) {
        Button('Bind Dynamic').onClick(() => {
          this.bindScrollController();
        })
        Button('Read Offsets').onClick(() => {
          this.refreshOffset();
        })
      }

      Text('Default Scroller').fontSize(14).fontWeight(FontWeight.Medium)
      Row({ space: 10 }) {
        Button('Default +120').onClick(() => {
          this.scrollBy(this.defaultScroller);
        })
        Button('Default Top').onClick(() => {
          this.scrollTop(this.defaultScroller);
        })
        Button('Default Bottom').onClick(() => {
          this.scrollBottom(this.defaultScroller);
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

      Scroll(this.defaultScroller) {
        Column({ space: 8 }) {
          ForEach(this.items, (idx: number) => {
            Text(`Item ${idx}`)
              .width('100%')
              .height(48)
              .textAlign(TextAlign.Center)
              .backgroundColor(idx % 2 === 0 ? '#f1f3f5' : '#e9ecef')
          })
        }
        .width('100%')
      }
      .id(ScrollDeclare.COMPONENT_ID)
      .height('70%')
      .width('100%')
      .borderWidth(1)
      .borderColor('#d0d7de')
    }
    .padding(16)
    .width('100%')
    .height('100%')
  }
}

