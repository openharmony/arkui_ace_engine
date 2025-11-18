'use static'
/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
import { State,Consume } from "@ohos.arkui.stateManagement" // should be insert by ui-plugins
import { memo, __memo_context_type, __memo_id_type } from "@ohos.arkui.stateManagement" // should be insert by ui-plugins
import { ForEach, List,NavigationMode,Alignment, Entry, Builder,
  Callback, Text, TextAttribute,BarStyle,Image,Color, Row, Column, 
  NavDestinationCommonTitle,Component, Button, ButtonAttribute, Scroll, ClickEvent, Curve, NavPathStack, Navigation,
  LayoutSafeAreaEdge, LaunchMode, NavigationMenuItem, NavPathInfo, NavDestination, LayoutSafeAreaType, NavigationMode } from "@ohos.arkui.component"  // TextAttribute should be insert by ui-plugins
import { PixelMap,ListItemAlign,ListItem,ColorMetrics,Row,,ForEach,BarPosition,TabContent,BarState,Tabs,NavDestination,NestedScrollMode,ListItem,
  TextAlign, Grid, LazyForEach, GridItem, Scroller, Component, Entry, Column, Row, Text, Navigation, NavDestination, 
  NavigationTitleMode, NavPathStack, Button, ClickEvent } from '@ohos.arkui.component'



@Entry
@Component
struct Index {
  @State listArr: string[] = ['1'] as string[];
  @State isChange:boolean = true

  @Builder
  pixelMapBuilder() {
    Column() {
      Text('123')
        .fontSize(16)
        .backgroundColor('#ffcc00')
        .width(80)
        .height(80)
        .textAlign(TextAlign.Center)
    }.backgroundColor('#330011')
  }

  aboutToAppear() {
    for (let i = 0; i < 16; i++) {
      this.listArr.push(i + '');
    }
  }

  build() {
    Column() {
      List() {
        ForEach(this.listArr, (item: string) => {
          ListItem() {
            Text(item)
          }
          .width(80)
          .height(80)
          .borderRadius(4)
          .backgroundColor('#ffcc00')
        }, (item: string) => item)
      }
      .width('100%')
      .height(500)
      .alignListItem(ListItemAlign.Center)
      .backgroundColor('#ff00')
      .onItemDragStart((event: ItemDragInfo) => {
        console.log("xxx onItemDragStart")
        return this.pixelMapBuilder
      })
      .onItemDrop((event: ItemDragInfo, itemIndex: Int, insertIndex: Int, isSuccess: boolean) => {
        console.log("xxx onItemDrop")
      })
      .onItemDragLeave(this.isChange ? (event: ItemDragInfo) => {
        console.log("xxx onItemDragLeave")
      } : undefined)

      Button('Change').onClick(() => {
        this.isChange = !this.isChange;
      })
    }
    .width('100%')
    .height('100%')
  }
}