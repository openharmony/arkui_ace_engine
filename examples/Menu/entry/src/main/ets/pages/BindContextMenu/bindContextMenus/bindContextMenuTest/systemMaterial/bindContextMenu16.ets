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
struct bindContextMenu_multiple_components_without_material {
  @State activeMenu: string = 'None'

  @Builder
  TextMenuBuilder() {
    Column() {
      Text('Text Actions')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
        .width('100%')
        .height(40)
        .textAlign(TextAlign.Center)
        .backgroundColor('#E0E0E0')

      Divider().height(2)

      Text('Copy Text')
        .fontSize(16)
        .width('100%')
        .height(40)
        .padding({ left: 20 })
        .onClick(() => {
          this.activeMenu = 'Text: Copy'
          console.info('Text Copy clicked')
        })

      Text('Select All')
        .fontSize(16)
        .width('100%')
        .height(40)
        .padding({ left: 20 })
        .onClick(() => {
          this.activeMenu = 'Text: Select All'
          console.info('Text Select All clicked')
        })
    }
    .width(200)
  }

  @Builder
  ButtonMenuBuilder() {
    Column() {
      Text('Button Actions')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
        .width('100%')
        .height(40)
        .textAlign(TextAlign.Center)
        .backgroundColor('#E0E0E0')

      Divider().height(2)

      Text('Enable')
        .fontSize(16)
        .width('100%')
        .height(40)
        .padding({ left: 20 })
        .onClick(() => {
          this.activeMenu = 'Button: Enable'
          console.info('Button Enable clicked')
        })

      Text('Disable')
        .fontSize(16)
        .width('100%')
        .height(40)
        .padding({ left: 20 })
        .onClick(() => {
          this.activeMenu = 'Button: Disable'
          console.info('Button Disable clicked')
        })
    }
    .width(200)
  }

  @Builder
  ImageMenuBuilder() {
    Column() {
      Text('Image Actions')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
        .width('100%')
        .height(40)
        .textAlign(TextAlign.Center)
        .backgroundColor('#E0E0E0')

      Divider().height(2)

      Text('Download')
        .fontSize(16)
        .width('100%')
        .height(40)
        .padding({ left: 20 })
        .onClick(() => {
          this.activeMenu = 'Image: Download'
          console.info('Image Download clicked')
        })

      Text('Share')
        .fontSize(16)
        .width('100%')
        .height(40)
        .padding({ left: 20 })
        .onClick(() => {
          this.activeMenu = 'Image: Share'
          console.info('Image Share clicked')
        })
    }
    .width(200)
  }

  build() {
    Column() {
      Text('Multiple Components with Context Menus')
        .fontSize(22)
        .fontWeight(FontWeight.Bold)
        .margin(20)

      Text('Active Menu: ' + this.activeMenu)
        .fontSize(16)
        .fontColor(Color.Blue)
        .margin({ bottom: 20 })

      // Text with context menu
      Text('This is a text with context menu')
        .fontSize(18)
        .padding(15)
        .backgroundColor(Color.Blue)
        .borderRadius(8)
        .bindContextMenu(this.TextMenuBuilder, ResponseType.LongPress, {
        })
        .margin(20)

      // Button with context menu
      Button('Button with Context Menu')
        .fontSize(18)
        .margin(20)
        .bindContextMenu(this.ButtonMenuBuilder, ResponseType.LongPress, {
        })

      // Image placeholder with context menu
      Circle()
        .width(200)
        .height(120)
        .borderRadius(8)
        .bindContextMenu(this.ImageMenuBuilder, ResponseType.LongPress, {
        })
        .margin(20)

      Text('Long press on any component to show its context menu')
        .fontSize(14)
        .fontColor(Color.Gray)
        .margin(20)
    }
    .width('100%')
    .height('100%')
  }
}
