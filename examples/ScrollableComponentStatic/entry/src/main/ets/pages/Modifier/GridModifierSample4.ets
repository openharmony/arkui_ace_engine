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
import { Entry, Text, Column, Component, Button, ClickEvent, Grid, ForEach, Color, GridItem ,Scroller,TextAlign,BorderStyle, ColumnOptions, GridAttribute,Row, RowOptions, Padding, Margin, EdgeEffect , BarState,CustomStyles,CommonMethod} from '@ohos.arkui.component'
import { State, Link } from '@ohos.arkui.stateManagement'
import { GridItemModifier } from "@ohos.arkui.modifier";
import hilog from '@ohos.hilog'
import router from '@ohos.router'


// 修改基类
class CustomModifier extends GridItemModifier {

}



@Component
struct ModifierComponent {
  @State numbers: string[] = ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15"]
  scroller: Scroller = new Scroller()

  stateStyle: CustomStyles = (instance: CommonMethod) =>{
    instance.backgroundColor("#ED6F21")
    .borderRadius(10)
    .borderStyle(BorderStyle.Dashed)
    .borderWidth(2)
    .borderColor("#33000000")
    .width(120)
    .height(30)
    .opacity(1)
  }
  customModifier: GridItemModifier = new CustomModifier()
    .rowStart(2)
    .rowEnd(2)
    .columnStart(1)
    .columnEnd(2)
    .selected(true)
    .selectable(true)

  build() {
    Column({ space: 10 } as ColumnOptions) {
      Grid(this.scroller) {
        GridItem() {
          Text('4')
            .fontSize(16)
            .backgroundColor(0xFAEEE0)
            .width('100%')
            .height('100%')
            .textAlign(TextAlign.Center)
        }
        .stateStyles({
          selected: this.stateStyle,
        })
        .attributeModifier(this.customModifier as CustomModifier)
        ForEach(this.numbers, (item: string) => {
          GridItem() {
            Text(item)
              .fontSize(16)
              .backgroundColor(0xF9CF93)
              .width('100%')
              .height('100%')
              .textAlign(TextAlign.Center)
          }
        }, (item: string) => item)
      }
      .multiSelectable(true)
      .columnsTemplate('1fr 1fr 1fr 1fr 1fr')
      .rowsTemplate('1fr 1fr 1fr 1fr 1fr')
      .height(300)
    }
  }
}
@Entry
@Component
struct Grid4 {

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
