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

import { FrameNode, NodeController, typeNode, UIContext } from '@kit.ArkUI';

class WaterFlowCommandController extends NodeController {
  private defaultScroller: Scroller = new Scroller();
  private dynamicScroller: Scroller = new Scroller();
  private waterFlowNode: FrameNode | null = null;
  private bindResultNode: typeNode.Text | null = null;
  private defaultOffsetNode: typeNode.Text | null = null;
  private dynamicOffsetNode: typeNode.Text | null = null;

  private getYOffset(scroller: Scroller): number {
    return scroller.currentOffset()?.yOffset ?? 0;
  }

  private refreshOffsetText(): void {
    const defaultOffset = this.getYOffset(this.defaultScroller);
    const dynamicOffset = this.getYOffset(this.dynamicScroller);
    this.defaultOffsetNode?.initialize(`Default yOffset: ${defaultOffset}`).fontSize(14);
    this.dynamicOffsetNode?.initialize(`Dynamic yOffset: ${dynamicOffset}`).fontSize(14);
  }

  private setBindResult(text: string): void {
    this.bindResultNode?.initialize(text).fontSize(14);
  }

  private bindDynamicScroller(): void {
    if (!this.waterFlowNode) {
      this.setBindResult('Bind failed: WaterFlow node is null');
      return;
    }
    try {
      typeNode.bindController(this.waterFlowNode, this.dynamicScroller, 'WaterFlow');
      this.setBindResult('Bind success');
      this.refreshOffsetText();
    } catch (e) {
      this.setBindResult(`Bind failed: code=${e.code}, msg=${e.message}`);
    }
  }

  private scrollBy(scroller: Scroller): void {
    scroller.scrollBy(0, 120);
    this.refreshOffsetText();
  }

  private scrollTop(scroller: Scroller): void {
    scroller.scrollEdge(Edge.Top);
    this.refreshOffsetText();
  }

  private scrollBottom(scroller: Scroller): void {
    scroller.scrollEdge(Edge.Bottom);
    this.refreshOffsetText();
  }

  makeNode(uiContext: UIContext): FrameNode | null {
    const root = typeNode.createNode(uiContext, 'Column');
    root.initialize().width('100%').height('100%').padding(16);

    const title = typeNode.createNode(uiContext, 'Text');
    title.initialize('Command WaterFlow Demo').fontSize(18).fontWeight(FontWeight.Bold)
      .margin({ bottom: 8 });

    this.bindResultNode = typeNode.createNode(uiContext, 'Text') as typeNode.Text;
    this.bindResultNode.initialize('Dynamic scroller not bound').fontSize(14).margin({ bottom: 4 });

    this.defaultOffsetNode = typeNode.createNode(uiContext, 'Text') as typeNode.Text;
    this.defaultOffsetNode.initialize('Default yOffset: 0').fontSize(14).margin({ bottom: 4 });

    this.dynamicOffsetNode = typeNode.createNode(uiContext, 'Text') as typeNode.Text;
    this.dynamicOffsetNode.initialize('Dynamic yOffset: 0').fontSize(14).margin({ bottom: 8 });

    const actionRow = typeNode.createNode(uiContext, 'Row');
    actionRow.initialize().margin({ bottom: 8 });

    const bindBtn = typeNode.createNode(uiContext, 'Button');
    bindBtn.initialize('Bind Dynamic').onClick(() => {
      this.bindDynamicScroller();
    }).margin({ right: 10 });

    const readBtn = typeNode.createNode(uiContext, 'Button');
    readBtn.initialize('Read Offsets').onClick(() => {
      this.refreshOffsetText();
    });

    actionRow.appendChild(bindBtn);
    actionRow.appendChild(readBtn);

    const defaultTitle = typeNode.createNode(uiContext, 'Text');
    defaultTitle.initialize('Default Scroller').fontSize(14).fontWeight(FontWeight.Medium).margin({ bottom: 4 });

    const defaultRow = typeNode.createNode(uiContext, 'Row');
    defaultRow.initialize().margin({ bottom: 8 });

    const defaultByBtn = typeNode.createNode(uiContext, 'Button');
    defaultByBtn.initialize('Default +120').onClick(() => {
      this.scrollBy(this.defaultScroller);
    }).margin({ right: 10 });

    const defaultTopBtn = typeNode.createNode(uiContext, 'Button');
    defaultTopBtn.initialize('Default Top').onClick(() => {
      this.scrollTop(this.defaultScroller);
    }).margin({ right: 10 });

    const defaultBottomBtn = typeNode.createNode(uiContext, 'Button');
    defaultBottomBtn.initialize('Default Bottom').onClick(() => {
      this.scrollBottom(this.defaultScroller);
    });

    defaultRow.appendChild(defaultByBtn);
    defaultRow.appendChild(defaultTopBtn);
    defaultRow.appendChild(defaultBottomBtn);

    const dynamicTitle = typeNode.createNode(uiContext, 'Text');
    dynamicTitle.initialize('Dynamic Scroller').fontSize(14).fontWeight(FontWeight.Medium).margin({ bottom: 4 });

    const dynamicRow = typeNode.createNode(uiContext, 'Row');
    dynamicRow.initialize().margin({ bottom: 8 });

    const dynamicByBtn = typeNode.createNode(uiContext, 'Button');
    dynamicByBtn.initialize('Dynamic +120').onClick(() => {
      this.scrollBy(this.dynamicScroller);
    }).margin({ right: 10 });

    const dynamicTopBtn = typeNode.createNode(uiContext, 'Button');
    dynamicTopBtn.initialize('Dynamic Top').onClick(() => {
      this.scrollTop(this.dynamicScroller);
    }).margin({ right: 10 });

    const dynamicBottomBtn = typeNode.createNode(uiContext, 'Button');
    dynamicBottomBtn.initialize('Dynamic Bottom').onClick(() => {
      this.scrollBottom(this.dynamicScroller);
    });

    dynamicRow.appendChild(dynamicByBtn);
    dynamicRow.appendChild(dynamicTopBtn);
    dynamicRow.appendChild(dynamicBottomBtn);

    const waterFlow = typeNode.createNode(uiContext, 'WaterFlow');
    waterFlow.initialize().height('70%').width('100%').borderWidth(1).borderColor('#d0d7de');
    this.waterFlowNode = waterFlow;
    typeNode.bindController(waterFlow, this.defaultScroller, 'WaterFlow');

    for (let i = 0; i < 40; i++) {
      const flowItem = typeNode.createNode(uiContext, 'FlowItem');
      flowItem.initialize().width('100%').margin({ bottom: 8 });

      const item = typeNode.createNode(uiContext, 'Text');
      item.initialize(`Item ${i}`)
        .width('100%')
        .height(48)
        .textAlign(TextAlign.Center)
        .backgroundColor(i % 2 === 0 ? '#f1f3f5' : '#e9ecef');

      flowItem.appendChild(item);
      waterFlow.appendChild(flowItem);
    }

    root.appendChild(title);
    root.appendChild(this.bindResultNode);
    root.appendChild(this.defaultOffsetNode);
    root.appendChild(this.dynamicOffsetNode);
    root.appendChild(actionRow);
    root.appendChild(defaultTitle);
    root.appendChild(defaultRow);
    root.appendChild(dynamicTitle);
    root.appendChild(dynamicRow);
    root.appendChild(waterFlow);

    return root;
  }
}

@Entry
@Component
struct WaterFlowCommand {
  private myNodeController: WaterFlowCommandController = new WaterFlowCommandController();

  build() {
    Column() {
      NodeContainer(this.myNodeController)
    }
    .width('100%')
    .height('100%')
  }
}
