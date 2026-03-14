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
  BarState,
  Builder,
  Button,
  ClickEvent,
  Color,
  Column,
  ColumnOptions,
  Component,
  EdgeEffect,
  Entry,
  ForEach,
  Grid,
  GridAttribute,
  GridItem,
  ItemDragInfo,
  Margin,
  Padding,
  Row,
  RowOptions,
  Scroller,
  Text,
  TextAlign
} from '@ohos.arkui.component'
import { State, Link } from '@ohos.arkui.stateManagement'
import hilog from '@ohos.hilog'

@Entry
@Component
struct ModifierComponent {
  @State numbers: string[] = [
    '0', '1', '2', '3', '4', '5', '6', '7',
    '8', '9', '10', '11', '12', '13', '14', '15'
  ]
  scroller: Scroller = new Scroller()


  @Builder pixelMapBuilder() { //拖拽过程样式
    Column() {
      Text('xxxxxxxad')
        .fontSize(16)
        .backgroundColor('#F9CF93')
        .width(80)
        .height(80)
        .textAlign(TextAlign.Center)
    }
  }

  build() {
    Column({ space: 10 } as ColumnOptions) {
      Grid(this.scroller) {
        ForEach(this.numbers, (item: string) => {
          GridItem() {
            Text(item)
          }
          .backgroundColor(Color.Pink)
          .width(80)
          .height(100)
          .borderWidth(2)
          .borderColor(Color.Red)
        }, (item: string) => item)
      }
      .friction(0.8)
      .enableScrollInteraction(true)
      .columnsTemplate('1fr 1fr 1fr')
      .columnsGap(10)
      .rowsGap(10)
      .height(300)
      .edgeEffect(EdgeEffect.Spring)
      .scrollBarWidth(2)
      .scrollBarColor('#FF1133')
      .scrollBar(BarState.On)
      .cachedCount(2)
      .borderColor(Color.Yellow)
      .editMode(true)
      .onScrollIndex((first: int,last: int):void => {
        console.info(first.toString())
      })
      .onScrollBarUpdate((index: int, offset: double) => {
        return { totalOffset: (index / 5) * (80 + 10) - offset, totalLength: 80 * 5 + 10 * 4 }
      })
      .onItemDragStart((event: ItemDragInfo, itemIndex: int) => {
        return this.pixelMapBuilder; //设置拖拽过程中显示的图片。
      })
      .onItemDrop(
        (event: ItemDragInfo, itemIndex: int, insertIndex: int, isSuccess: boolean) => {
          console.info('itemIndex:' + itemIndex + ', insertIndex:' + insertIndex);
        }
      )
      .onItemDragLeave((event: ItemDragInfo, itemIndex: int) => {

        console.info('onItemDragLeave:' + itemIndex );
      })
      .onItemDragMove((event: ItemDragInfo, itemIndex: int, insertIndex: int) => {
        console.info('onItemDragMove:' + itemIndex + 'insert' + insertIndex);

      })
      .onItemDrop((event: ItemDragInfo, itemIndex: int, insertIndex: int, isSuccess: boolean) => {
        console.info('onItemDrop:' + itemIndex + 'insert' + insertIndex);

      })
    }
  }
}
