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
import { Entry, Text, Column, Component, Button, ClickEvent, Grid, ForEach, Color, GridItem ,Scroller, ColumnOptions, GridAttribute,Row, RowOptions, Padding, Margin, EdgeEffect , BarState,ScrollSource,ScrollState,OnWillScrollCallback,ScrollResult} from '@ohos.arkui.component'
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
    .rowsTemplate('1fr 1fr')
    .columnsTemplate('1fr 1fr 1fr')
    .columnsGap(10)
    .rowsGap(10)
    .edgeEffect(EdgeEffect.Spring)
    .scrollBarWidth(2)
    .scrollBarColor(Color.Green)
    .scrollBar(BarState.On)
    .cachedCount(2)
    .editMode(false)
    .multiSelectable(false)
    .supportAnimation(false)



  build() {
    Column({ space: 10 } as ColumnOptions) {
      Grid(this.scroller) {
          GridItem() {
            Text("item")
          }
          .backgroundColor(Color.Pink)
          .width(80)
          .height(100)
          .borderWidth(2)
          .borderColor(Color.Red)
        GridItem() {
          Text("item")
        }
        .backgroundColor(Color.Pink)
        .width(80)
        .height(100)
        .borderWidth(2)
        .borderColor(Color.Red)
        GridItem() {
          Text("item")
        }
        .backgroundColor(Color.Pink)
        .width(80)
        .height(100)
        .borderWidth(2)
        .borderColor(Color.Red)
        GridItem() {
          Text("item")
        }
        .backgroundColor(Color.Pink)
        .width(80)
        .height(100)
        .borderWidth(2)
        .borderColor(Color.Red)
      }
      .height(100)
      .columnsTemplate("1fr")
      .attributeModifier(this.customModifier as CustomModifier)
      .borderColor(Color.Black)
      .onWillScroll((scrollOffset: number, scrollState: ScrollState, scrollSource: ScrollSource)=>{


      })

    }
  }
}
@Entry
@Component
struct Grid2 {

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