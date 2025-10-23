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
import { Entry, Text,Builder, Column,TextAlign, Component,ItemDragInfo, Button, ItemDragInfo,GridDirection,
  ClickEvent, Grid, ForEach, Color, GridItem ,Scroller,Scroll,Blank, Alignment,ColumnOptions, GridAttribute,Row, RowOptions, Padding, Margin, EdgeEffect , BarState} from '@ohos.arkui.component'
import { State, Link } from '@ohos.arkui.stateManagement'
import hilog from '@ohos.hilog'


@Entry
@Component
struct GridExample {
  numbers: Array<number> = new Array<number>(30).fill(0);



  build() {
    Scroll() {
      Column({ space: 5 } as ColumnOptions) {
        Blank()
        Text('rowsTemplate、columnsTemplate都不设置layoutDirection、maxCount、minCount、cellLength才生效')
          .fontSize(15).fontColor('#CCCCCC').width('90%')
        Grid() {
          ForEach(this.numbers, (day: number,index:int) => {
            GridItem() {
              Text(index+'').fontSize(16).backgroundColor('#F9CF93')

            }.width(40).height(80).borderWidth(2).borderColor(Color.Red)
          }, (day: number,index: int) => day+''+index)
        }
        .height(300)
        .columnsGap(10)
        .rowsGap(10)
        .backgroundColor('#FAEEE0')
        .maxCount(6)
        .minCount(2)
        .cellLength(0)
        .layoutDirection(GridDirection.Row)
      }
      .width('90%').margin({ top: 5, left: 5, right: 5 } as Margin)
      .align(Alignment.Center)
    }
  }
}