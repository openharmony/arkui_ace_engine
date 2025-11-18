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
  TextAlign,
  Stack,
  ItemDragInfo,
  Alignment,
  ForEach,
  Axis,
  EdgeEffect,
  Padding,
  ListItem,
  CustomBuilder
} from '@ohos.arkui.component'
import { State } from '@ohos.arkui.stateManagement';

@Entry
@Component
struct ListExample11 {
  private arr1: number[] = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9] as number[]
  private arr2: string[] = ['a', 'b', 'c', 'd', 'e', 'f']
  @State editFlag: boolean = false
  @State bool1: boolean = false
  @State bool2: boolean = false
  @State text: number = 0

  @Builder
  pixelMapBuilder() {
    Column() {
      Text(`${this.text}`)
        .width('50%')
        .height(60)
        .fontSize(16)
        .borderRadius(10)
        .textAlign(TextAlign.Center)
        .backgroundColor(Color.Yellow)
    }
  }

  build() {
    Stack({ alignContent: Alignment.TopStart }) {
      Column() {
        List({ space: 20, initialIndex: 0 }) {
          ForEach(this.arr1, (item: number, index: int) => {
            ListItem() {
              Text('' + item)
                .width('100%')
                .height(100)
                .fontSize(16)
                .textAlign(TextAlign.Center)
                .borderRadius(10)
                .backgroundColor('#FFFFFF')
            }
          }, (item: number) => item.toString())
        }
        .key('list')
        .listDirection(Axis.Vertical)
        .divider({
          strokeWidth: 2,
          color: '#FFFFFF',
          startMargin: 20,
          endMargin: 20
        })
        .edgeEffect(EdgeEffect.None)
        .chainAnimation(false)
        .onScrollIndex((firstIndex: int, lastIndex: int, center: int): void => {
          console.info('first' + firstIndex)
          console.info('last' + lastIndex)
        })
        .onDidScroll((scrollOffset: double, scrollState: ScrollState): void => {
          console.info('scrollOffset:' + scrollOffset)
          console.info('ScrollState:' + scrollState)
        })
        .onReachStart(() => {
          console.info("On Reach Start")
        })
        .onReachEnd(() => {
          console.info("On Reach End")
        })
        .onScrollStop(() => {
          console.info("On Scroll Stop")
        })
        .onItemMove((from: int, to: int) => {
          console.info(from + 'from')
          console.info(to + 'to')
          return true
        })
        .onItemDragStart((event: ItemDragInfo, itemIndex: int): CustomBuilder => {
          this.bool1 = true
          this.text = this.arr1[itemIndex.toInt()]
          console.log('onItemDragStart, itemIndex:' + itemIndex);
          return this.pixelMapBuilder;
        })
        .onItemDragEnter((event: ItemDragInfo) => {
          console.log('onItemDragEnter');
        })
        .onItemDragMove((event: ItemDragInfo, itemIndex: int, insertIndex: int) => {
          console.log('onItemDragMove,itemIndex:' + itemIndex + 'insertIndex:' + insertIndex)
        })
        .onItemDragLeave((event: ItemDragInfo, itemIndex: int) => {
          console.log('onItemDragLeave, itemIndex:' + itemIndex);
        })
        .onItemDrop((event: ItemDragInfo, itemIndex: int, insertIndex: int, isSuccess: boolean) => {
          console.log('ItemDragInfo, itemIndex:' + itemIndex + 'insertIndex:' + insertIndex + 'isSuccess:' + isSuccess);
          if (isSuccess) {
            if (this.bool2) {
              this.arr2.splice(itemIndex, 1)
              this.arr1.splice(insertIndex, 0, this.text)
              this.bool1 = false
              this.bool2 = false
            } else if (this.bool1) {
              this.arr2.splice(itemIndex, 1)
              this.arr1.splice(insertIndex, 0, this.text)
              this.bool1 = false
              this.bool2 = false
            }
          }
        })
        .width('90%')
      }.width('100%')

    }.width('100%').height('50%').backgroundColor('#DCDCDC').padding({ top: 5 } as Padding)
  }
}