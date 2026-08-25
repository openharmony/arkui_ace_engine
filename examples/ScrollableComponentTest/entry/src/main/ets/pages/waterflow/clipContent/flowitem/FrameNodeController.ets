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

import { FrameNode, NodeController, RectShape, typeNode, UIContext } from '@kit.ArkUI';

export class FlowItemFrameNodeController extends NodeController {
  private scroller: Scroller = new Scroller();
  private enableClip: boolean = false;
  private clipMode: number = 0;
  private lanes: string = '1fr 1fr';
  private itemBase: number = 0;
  private rangeCallback?: (range: string) => void;

  constructor(enableClip: boolean) {
    super();
    this.enableClip = enableClip;
  }

  setRangeCallback(callback: (range: string) => void): void {
    this.rangeCallback = callback;
  }

  makeNode(uiContext: UIContext): FrameNode | null {
    const waterFlow = typeNode.createNode(uiContext, 'WaterFlow');
    const waterAttr = waterFlow.initialize({ scroller: this.scroller })
      .width('100%')
      .height('100%')
      .columnsTemplate(this.lanes)
      .columnsGap(8)
      .rowsGap(8)
      .padding({ left: 12, right: 12 })
      .safeAreaPadding({ top: 50, bottom: 30 })
      .backgroundColor('#80FFD0B0');

    if (this.enableClip) {
      waterAttr.clipContent(this.getClipContent()).cachedCount(4, true);
    }

    const waterEvent = typeNode.getEvent(waterFlow, 'WaterFlow');
    waterEvent?.setOnScrollIndex((start: number, end: number) => {
      this.rangeCallback?.(`idx:${start}-${end}`);
      console.log(`FHF::onScrollIndex:(${start}, ${end})`);
    });

    for (let i = 0; i < 40; i++) {
      const itemIndex = this.itemBase + i;
      const flowItem = typeNode.createNode(uiContext, 'FlowItem');
      flowItem.initialize()
        .width('100%')
        .height(72)
        .borderRadius(12)
        .backgroundColor('#B0C0FF');

      const text = typeNode.createNode(uiContext, 'Text');
      text.initialize('Item' + itemIndex.toString())
        .width('100%')
        .height('100%')
        .textAlign(TextAlign.Center);

      try {
        flowItem.appendChild(text);
        waterFlow.appendChild(flowItem);
      } catch (e) {
        console.error(`FrameNode append failed: code=${e.code}, msg=${e.message}`);
      }
    }

    return waterFlow;
  }

  switchMode(): string {
    if (!this.enableClip) {
      return 'M:OFF';
    }
    this.clipMode = (this.clipMode + 1) % 4;
    this.rebuild();
    return this.getModeString();
  }

  switchLanes(): string {
    if (this.lanes === '1fr') {
      this.lanes = '1fr 1fr';
      this.rebuild();
      return 'L:2';
    }
    this.lanes = '1fr';
    this.rebuild();
    return 'L:1';
  }

  reload(): void {
    this.itemBase = this.itemBase === 0 ? 1000 : 0;
    this.rebuild();
  }

  scrollToIndex(index: number): void {
    this.scroller.scrollToIndex(index);
  }

  private getClipContent(): ContentClipMode | RectShape {
    if (this.clipMode === 0) {
      return ContentClipMode.SAFE_AREA;
    }
    if (this.clipMode === 1) {
      return ContentClipMode.BOUNDARY;
    }
    if (this.clipMode === 2) {
      return new RectShape().size({ width: '100%', height: '150%' }).offset({ x: 0, y: '-25%' });
    }
    return ContentClipMode.CONTENT_ONLY;
  }

  private getModeString(): string {
    if (this.clipMode === 0) {
      return 'M:SA';
    }
    if (this.clipMode === 1) {
      return 'M:BD';
    }
    if (this.clipMode === 2) {
      return 'M:CT';
    }
    return 'M:CO';
  }
}
