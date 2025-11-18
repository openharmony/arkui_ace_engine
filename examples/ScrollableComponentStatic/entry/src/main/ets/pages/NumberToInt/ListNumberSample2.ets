'use static'
/**
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
import {
  Entry,
  Component,
  Column,
  Flex,
  Row,
  Text,
  Color,
  ListScroller,
  Builder,
  Margin,
  List,
  VisibleListContentInfo,
  ScrollState,
  Button,
  ClickEvent,
  Scroller,
  ForEach,
  Axis,
  BarState,
  ListItemGroup,
  ListItem,
  TextAlign,
  ListItemGroupOptions
} from '@ohos.arkui.component'
import { State } from '@ohos.arkui.stateManagement';

@Entry
@Component
struct lanesItemGroupExample {
  scroller: ListScroller = new ListScroller()
  @State arr: number[] = [1, 2, 3] as number[]
  @State arr2: number[] = [1, 2, 3, 4, 5, 6, 7, 8] as number[]

  build() {
    Column() {
      List({ scroller: this.scroller }) {
        ForEach(this.arr, (item0: number, groupIndex: int) => {
          ListItemGroup({space:1} as ListItemGroupOptions) {
            ForEach(this.arr2, (item: number, itemIndex: int) => {
              ListItem() {
                Text('Group:' + (groupIndex + 1) + ', Item:' + item)
                  .id('group_ver_' + (groupIndex + 1) + '_' + item)
                  .width('100%')
                  .height('20%')
                  .fontSize(20)
                  .textAlign(TextAlign.Center)
                  .backgroundColor(Color.Pink)
              }
            }, (item: number) => item.toString())
          }

        })
      }
      .id('group_ver_list')
      .width('90%')
      .height('40%')
      .lanes(2)
      .listDirection(Axis.Vertical)
      .scrollBar(BarState.On)
      .onScrollIndex((firstIndex: int, lastIndex: int, centerIndex: int) => {
        console.info('first' + firstIndex)
        console.info('last' + lastIndex)
        console.info('center' + centerIndex)
      })
      .onScrollVisibleContentChange((start: VisibleListContentInfo, end: VisibleListContentInfo): void => {
        console.log(' start index: ' + start.index +
          ' start item group area: ' + start.itemGroupArea +
          ' start index in group: ' + start.itemIndexInGroup)
        console.log(' end index: ' + end.index +
          ' end item group area: ' + end.itemGroupArea +
          ' end index in group: ' + end.itemIndexInGroup)
      })
      .onDidScroll((scrollOffset: double, scrollState: ScrollState): void => {
        console.info(`onScroll scrollState = ScrollState` + scrollState + `, scrollOffset = ` + scrollOffset)
      })

      Button('scrollToItemInGroup(1, 2)')
        .id('itemInGroup_ver_item')
        .onClick((e: ClickEvent) => {
          this.scroller.scrollToItemInGroup(1, 2)
        })
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#DCDCDC')
    .margin({ top: 5 } as Margin)
  }
}