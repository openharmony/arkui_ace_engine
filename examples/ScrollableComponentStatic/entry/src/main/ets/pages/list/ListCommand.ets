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

import { FrameNode, NodeController, typeNode } from '@ohos.arkui.node'
import { UIContext } from '@ohos.arkui.UIContext'
import {
  Button,
  ButtonType,
  Color,
  Column,
  Component,
  Edge,
  Entry,
  FontWeight,
  NodeContainer,
  Row,
  Scroller,
  Text
} from '@ohos.arkui.component'
import { State } from '@ohos.arkui.stateManagement'

class ListCommandController extends NodeController {
  private defaultScroller: Scroller = new Scroller()
  private dynamicScroller: Scroller = new Scroller()
  private listNode: FrameNode | null = null

  makeNode(uiContext: UIContext): FrameNode | null {
    const list: FrameNode = typeNode.createListNode(uiContext)
    const listAttr = typeNode.getListAttribute(list)
    if (!listAttr) {
      return null
    }

    listAttr
      .size({ width: '100%', height: '100%' })
      .borderWidth(1)
      .borderColor('#d0d7de')

    for (let i = 0; i < 40; i++) {
      const listItem: FrameNode = typeNode.createListItemNode(uiContext)

      const itemNode: FrameNode = typeNode.createButtonNode(uiContext)
      itemNode.initialize(`List Item ${i}`)
        .type(ButtonType.Normal)
        .stateEffect(false)
        .backgroundColor(i % 2 === 0 ? '#f8f9fa' : '#edf2f7')
        .borderWidth(0)
        .fontColor(0x000000)
        .fontSize(14)
        .width('100%')
        .height(56)

      listItem.appendChild(itemNode)
      list.appendChild(listItem)
    }

    this.listNode = list
    typeNode.bindListController(list, this.defaultScroller)
    return list
  }

  bindDynamicScroller(): string {
    const node: FrameNode | null = this.listNode
    if (node === null) {
      return 'Bind failed: List node is null'
    }
    try {
      typeNode.bindListController(node, this.dynamicScroller)
      return 'Bind success'
    } catch (e) {
      return `Bind failed: code=${e.code}, msg=${e.message}`
    }
  }

  getDefaultYOffset(): number {
    return this.defaultScroller.currentOffset()?.yOffset ?? 0
  }

  getDynamicYOffset(): number {
    return this.dynamicScroller.currentOffset()?.yOffset ?? 0
  }

  scrollByDefault(): void {
    this.defaultScroller.scrollBy(0, 120)
  }

  scrollTopDefault(): void {
    this.defaultScroller.scrollEdge(Edge.Top)
  }

  scrollBottomDefault(): void {
    this.defaultScroller.scrollEdge(Edge.Bottom)
  }

  scrollByDynamic(): void {
    this.dynamicScroller.scrollBy(0, 120)
  }

  scrollTopDynamic(): void {
    this.dynamicScroller.scrollEdge(Edge.Top)
  }

  scrollBottomDynamic(): void {
    this.dynamicScroller.scrollEdge(Edge.Bottom)
  }
}

@Entry
@Component
struct ListCommand {
  private myNodeController: ListCommandController = new ListCommandController()
  @State private bindResult: string = 'Dynamic scroller not bound'
  @State private defaultOffsetText: string = 'Default yOffset: 0'
  @State private dynamicOffsetText: string = 'Dynamic yOffset: 0'

  private refreshOffsetText(): void {
    this.defaultOffsetText = `Default yOffset: ${this.myNodeController.getDefaultYOffset()}`
    this.dynamicOffsetText = `Dynamic yOffset: ${this.myNodeController.getDynamicYOffset()}`
  }

  build() {
    Column(undefined) {
      Text('Command List Static Demo').fontSize(18).fontWeight(FontWeight.Bold).margin({ bottom: 8 })
      Text(this.bindResult).fontSize(14).margin({ bottom: 4 })
      Text(this.defaultOffsetText).fontSize(14).margin({ bottom: 4 })
      Text(this.dynamicOffsetText).fontSize(14).margin({ bottom: 8 })

      Row(undefined) {
        Button('Bind Dynamic').onClick(() => {
          this.bindResult = this.myNodeController.bindDynamicScroller();
          this.refreshOffsetText()
        }).margin({ right: 10 })
        Button('Read Offsets').onClick(() => this.refreshOffsetText())
      }.margin({ bottom: 8 })

      Row(undefined) {
        Button('Default +120').onClick(() => {
          this.myNodeController.scrollByDefault();
          this.refreshOffsetText()
        }).margin({ right: 10 })
        Button('Default Top').onClick(() => {
          this.myNodeController.scrollTopDefault();
          this.refreshOffsetText()
        }).margin({ right: 10 })
        Button('Default Bottom').onClick(() => {
          this.myNodeController.scrollBottomDefault();
          this.refreshOffsetText()
        })
      }.margin({ bottom: 8 })

      Row(undefined) {
        Button('Dynamic +120').onClick(() => {
          this.myNodeController.scrollByDynamic();
          this.refreshOffsetText()
        }).margin({ right: 10 })
        Button('Dynamic Top').onClick(() => {
          this.myNodeController.scrollTopDynamic();
          this.refreshOffsetText()
        }).margin({ right: 10 })
        Button('Dynamic Bottom').onClick(() => {
          this.myNodeController.scrollBottomDynamic();
          this.refreshOffsetText()
        })
      }.margin({ bottom: 8 })

      NodeContainer(this.myNodeController).width('100%').height('70%')
    }
    .padding(16).width('100%').height('100%')
  }
}
