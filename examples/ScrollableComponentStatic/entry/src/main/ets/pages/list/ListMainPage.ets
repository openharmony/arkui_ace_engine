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

import {
  Entry,
  Component,
  Column,
  List,
  ListItem,
  ForEach,
  Text,
  ListScroller,
  ListDividerOptions,
  TextAlign,
  ListItemAlign,
  EdgeEffect,
  BarState
} from '@ohos.arkui.component'
import { State } from '@ohos.arkui.stateManagement'

class PageInfo {
  title: string
  url: string

  constructor(title: string, url: string) {
    this.title = title
    this.url = url
  }
}

@Entry
@Component
struct ListMainPage {
  @State routers: Array<PageInfo> = new Array<PageInfo>()
  private listScroller: ListScroller = new ListScroller()

  aboutToAppear(): void {
    this.routers = new Array<PageInfo>()
    this.routers.push(new PageInfo('Back', 'pages/Index'))
    this.routers.push(new PageInfo('List 声明式', 'pages/list/ListDeclare'))
    this.routers.push(new PageInfo('List 命令式', 'pages/list/ListCommand'))
    this.routers.push(new PageInfo('ListItemGroupMixedCase', 'pages/list/childrenMainSize/ListItemGroupMixedCase'))
    this.routers.push(new PageInfo('OnlyListItemCase', 'pages/list/childrenMainSize/OnlyListItemCase'))
    this.routers.push(new PageInfo('ListOnItemDrag', 'pages/list/drag/ListOnItemDrag'))
    this.routers.push(new PageInfo('ListBindListScroller', 'pages/list/ListScroller/ListBindListScroller'))
    this.routers.push(new PageInfo('ListItemNumberSample', 'pages/list/number/ListItemNumberSample'))
    this.routers.push(new PageInfo('ListNumberSample1', 'pages/list/number/ListNumberSample1'))
    this.routers.push(new PageInfo('ListNumberSample2', 'pages/list/number/ListNumberSample2'))
    this.routers.push(new PageInfo('ForEachCase', 'pages/list/onMove/ForEachCase'))
    this.routers.push(new PageInfo('LazyForEachCase', 'pages/list/onMove/LazyForEachCase'))
    this.routers.push(new PageInfo('RepeatNonVirtualCase', 'pages/list/onMove/RepeatNonVirtualCase'))
    this.routers.push(new PageInfo('RepeatVirtualScrollCase', 'pages/list/onMove/RepeatVirtualScrollCase'))
    this.routers.push(new PageInfo('scrollEvent', 'pages/list/scrollEvent/scrollEvent'))
    this.routers.push(new PageInfo('listSelectedAttr', 'pages/list/selected/listSelectedAttr'))
    this.routers.push(new PageInfo('swipeActionWithBuilder', 'pages/list/swipeAction/swipeActionWithBuilder'))
  }

  build() {
    Column(undefined) {
      Text('List')
        .fontSize(20)
        .margin({ top: 12, bottom: 8 })
      List({ scroller: this.listScroller }) {
        ForEach(this.routers, (item: PageInfo) => {
          ListItem() {
            Text(item.title)
              .width('100%')
              .height(88)
              .fontSize(16)
              .textAlign(TextAlign.Center)
              .borderRadius(10)
              .backgroundColor(0xFFFFFF)
              .onClick(() => {
                this.getUIContext().getRouter().pushUrl({ url: item.url })
              })
          }
          .width('80%')
        }, (item: PageInfo) => item.url)
      }
      .divider({
        strokeWidth: 2,
        color: 0xFFFFFF,
        startMargin: 20,
        endMargin: 20
      } as ListDividerOptions)
      .width('100%')
      .layoutWeight(1)
      .edgeEffect(EdgeEffect.Spring)
      .alignListItem(ListItemAlign.Center)
      .scrollBar(BarState.On)
      .scrollBarWidth(20)
    }
    .width('100%')
    .height('100%')
    .backgroundColor(0xDCDCDC)
    .padding({ top: 5 })
  }
}