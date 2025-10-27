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
import { Entry, Text,Builder, Column,TextAlign, Component,ItemDragInfo, Button, ClickEvent, Grid, ForEach, Color, GridItem ,Scroller, ColumnOptions, GridAttribute,Row, RowOptions, Padding, Margin, EdgeEffect , BarState} from '@ohos.arkui.component'
import { State, Link } from '@ohos.arkui.stateManagement'
import { GridModifier } from "@ohos.arkui.modifier";
import hilog from '@ohos.hilog'
import router from '@ohos.router'


// 修改基类
class CustomModifier extends GridModifier {

}

@Component
struct ModifierComponent {
  @State numbers: string[] = ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15"]
  scroller: Scroller = new Scroller()
  customModifier: GridModifier = new CustomModifier()
    .friction(0.8)
    .enableScrollInteraction(true)
    .columnsTemplate('1fr 1fr 1fr')
    .columnsGap(10)
    .rowsGap(10)
    .height(300)
    .edgeEffect(EdgeEffect.Spring)
    .scrollBarWidth(2)
    .scrollBarColor(Color.Green)
    .scrollBar(BarState.On)
    .cachedCount(2)
    .borderColor(Color.Yellow)
    .editMode(true)
    .onItemDragStart((event: ItemDragInfo, itemIndex: int) => {
      return this.pixelMapBuilder; //设置拖拽过程中显示的图片。
    })



  @Builder pixelMapBuilder() { //拖拽过程样式
    Column() {
      Text("xxxxxxxad")
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
      .attributeModifier(this.customModifier as CustomModifier)

      .borderColor(Color.Black)
    }
  }
}
@Entry
@Component
struct Grid3 {

  build() {
    Column(undefined) {
      Button('Back').backgroundColor('#FFFF00FF')
        .onClick((e: ClickEvent) => {
          this.getUIContext().getRouter().back();
        })
      ModifierComponent()

    }
    .width('80%')
  }
}
