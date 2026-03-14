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
'use static'

import { typeNode } from '@ohos.arkui.node';
import {
  Button,
  Column,
  Component,
  Edge,
  Entry,
  FontWeight,
  ForEach,
  Row,
  Scroll,
  Scroller,
  Text,
  TextAlign
} from '@ohos.arkui.component';
import { State } from '@ohos.arkui.stateManagement';

@Entry
@Component
struct ScrollDeclare {
  private static readonly COMPONENT_ID: string = 'scroll_bind_demo_001';
  private defaultScroller: Scroller = new Scroller();
  private dynamicScroller: Scroller = new Scroller();
  @State private bindResult: string = 'Dynamic scroller not bound';
  @State private defaultOffsetText: string = 'Default yOffset: 0';
  @State private dynamicOffsetText: string = 'Dynamic yOffset: 0';
  @State private items: Array<number> = [];

  aboutToAppear(): void {
    this.items = [];
    for (let i: number = 0; i < 40; i++) {
      this.items.push(i);
    }
  }

  private bindController(): void {
    const frameNode = this.getUIContext().getFrameNodeById(ScrollDeclare.COMPONENT_ID);
    if (!frameNode) {
      this.bindResult = 'Bind failed: FrameNode is null';
      return;
    }
    try {
      typeNode.bindScrollController(frameNode, this.dynamicScroller);
      this.bindResult = 'Bind success';
      this.refreshOffset();
    } catch (e) {
      this.bindResult = `Bind failed: code=${e.code}, msg=${e.message}`;
      console.log(this.bindResult);
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
    Column() {
      Text('Declarative Scroll Static Demo')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 8 });

      Text(this.bindResult).fontSize(14).margin({ bottom: 4 });
      Text(this.defaultOffsetText).fontSize(14).margin({ bottom: 4 });
      Text(this.dynamicOffsetText).fontSize(14).margin({ bottom: 8 });

      Row() {
        Button('Bind Dynamic').onClick(() => {
          this.bindController();
        }).margin({ right: 10 });

        Button('Read Offsets').onClick(() => {
          this.refreshOffset();
        });
      }.margin({ bottom: 8 });

      Text('Default Scroller').fontSize(14).fontWeight(FontWeight.Medium).margin({ bottom: 4 });
      Row() {
        Button('Default +120').onClick(() => {
          this.scrollBy(this.defaultScroller);
        }).margin({ right: 10 });

        Button('Default Top').onClick(() => {
          this.scrollTop(this.defaultScroller);
        }).margin({ right: 10 });

        Button('Default Bottom').onClick(() => {
          this.scrollBottom(this.defaultScroller);
        });
      }.margin({ bottom: 8 });

      Text('Dynamic Scroller').fontSize(14).fontWeight(FontWeight.Medium).margin({ bottom: 4 });
      Row() {
        Button('Dynamic +120').onClick(() => {
          this.scrollBy(this.dynamicScroller);
        }).margin({ right: 10 });

        Button('Dynamic Top').onClick(() => {
          this.scrollTop(this.dynamicScroller);
        }).margin({ right: 10 });

        Button('Dynamic Bottom').onClick(() => {
          this.scrollBottom(this.dynamicScroller);
        });
      }.margin({ bottom: 8 });

      Scroll(this.defaultScroller) {
        Column() {
          ForEach(this.items, (idx: number) => {
            Text(`Item ${idx}`)
              .width('100%')
              .height(48)
              .margin({ bottom: 8 })
              .textAlign(TextAlign.Center)
              .backgroundColor(idx % 2 === 0 ? '#f1f3f5' : '#e9ecef');
          }, (idx: number) => idx.toString());
        }
        .width('100%');
      }
      .key(ScrollDeclare.COMPONENT_ID)
      .height('70%')
      .width('100%')
      .borderWidth(1)
      .borderColor('#d0d7de');
    }
    .padding(16)
    .width('100%')
    .height('100%');
  }
}
