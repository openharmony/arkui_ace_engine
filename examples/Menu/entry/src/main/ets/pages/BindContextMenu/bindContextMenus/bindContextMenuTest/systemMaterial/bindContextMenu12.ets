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

import uiMaterial from "@ohos.arkui.uiMaterial"

@Entry
@Component
struct bindContextMenu_complex_menu_NONE {
  @State selectedColor: string = 'Black'

  @Builder
  ComplexMenuBuilder() {
    Column() {
      Text('Color Picker Menu')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
        .width('100%')
        .height(40)
        .textAlign(TextAlign.Center)
        .backgroundColor('#E0E0E0')
        .borderRadius({ topLeft: 10, topRight: 10 })

      Divider().height(2).color(Color.Gray)

      Row() {
        Circle()
          .width(30)
          .height(30)
          .fill(Color.Red)
          .margin(10)
        Text('Red')
          .fontSize(16)
          .margin({ left: 10 })
      }
      .width('100%')
      .height(50)
      .onClick(() => {
        this.selectedColor = 'Red'
        console.info('Selected: Red')
      })

      Row() {
        Circle()
          .width(30)
          .height(30)
          .fill(Color.Green)
          .margin(10)
        Text('Green')
          .fontSize(16)
          .margin({ left: 10 })
      }
      .width('100%')
      .height(50)
      .onClick(() => {
        this.selectedColor = 'Green'
        console.info('Selected: Green')
      })

      Row() {
        Circle()
          .width(30)
          .height(30)
          .fill(Color.Blue)
          .margin(10)
        Text('Blue')
          .fontSize(16)
          .margin({ left: 10 })
      }
      .width('100%')
      .height(50)
      .onClick(() => {
        this.selectedColor = 'Blue'
        console.info('Selected: Blue')
      })

      Divider().height(2).color(Color.Gray)

      Text('Close')
        .fontSize(16)
        .width('100%')
        .height(40)
        .textAlign(TextAlign.Center)
        .backgroundColor('#F0F0F0')
        .borderRadius({ bottomLeft: 10, bottomRight: 10 })
    }
    .width(250)
    .borderRadius(10)
  }

  build() {
    Column() {
      Text('Complex Context Menu Example')
        .fontSize(24)
        .fontWeight(FontWeight.Bold)
        .margin(20)

      Text('Selected Color: ' + this.selectedColor)
        .fontSize(18)
        .margin(20)
        .fontColor(this.selectedColor === 'Red' ? Color.Red :
          this.selectedColor === 'Green' ? Color.Green :
            this.selectedColor === 'Blue' ? Color.Blue : Color.Black)

      Circle()
        .width(200)
        .height(200)
        .fill(this.selectedColor === 'Red' ? Color.Red :
          this.selectedColor === 'Green' ? Color.Green :
            this.selectedColor === 'Blue' ? Color.Blue : Color.Black)
        .bindContextMenu(this.ComplexMenuBuilder, ResponseType.LongPress, {
          systemMaterial: new uiMaterial.Material({ type: uiMaterial.MaterialType.SEMI_TRANSPARENT })
        })
        .margin(20)

      Text('Long press the rectangle to show color picker menu')
        .fontSize(16)
        .fontColor(Color.Gray)
        .margin(20)
    }
    .width('100%')
    .height('100%')
  }
}
