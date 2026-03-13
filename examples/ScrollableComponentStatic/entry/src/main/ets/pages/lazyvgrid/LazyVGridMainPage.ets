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
struct LazyVGridMainPage {
  @State routers: Array<PageInfo> = new Array<PageInfo>()
  private listScroller: ListScroller = new ListScroller()

  aboutToAppear(): void {
    this.routers = new Array<PageInfo>()
    this.routers.push(new PageInfo('Back', 'pages/Index'))
    this.routers.push(new PageInfo('LavyVGrid1_2Test', 'pages/lazyvgrid/LavyVGrid1_2Test'))
  }

  build() {
    Column(undefined) {
      Text('LazyVGrid')
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