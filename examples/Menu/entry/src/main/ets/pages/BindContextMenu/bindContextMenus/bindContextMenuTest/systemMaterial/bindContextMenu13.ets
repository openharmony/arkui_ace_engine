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
import { image } from '@kit.ImageKit'

@Entry
@Component
struct bindContextMenu_Image_component_WITHOUT_MATERIAL {
  @State imageScale: number = 1.0

  @Builder
  ImageMenuBuilder() {
    Column() {
      Text('Image Options')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
        .width('100%')
        .height(40)
        .textAlign(TextAlign.Center)

      Divider().height(2)

      Text('🔍+ Zoom In')
        .fontSize(18)
        .width('100%')
        .height(45)
        .padding({ left: 20 })
        .textAlign(TextAlign.Start)
        .onClick(() => {
          this.imageScale = Math.min(this.imageScale + 0.1, 3.0)
          console.info('Zoom In: ' + this.imageScale)
        })

      Text('🔍- Zoom Out')
        .fontSize(18)
        .width('100%')
        .height(45)
        .padding({ left: 20 })
        .textAlign(TextAlign.Start)
        .onClick(() => {
          this.imageScale = Math.max(this.imageScale - 0.1, 0.5)
          console.info('Zoom Out: ' + this.imageScale)
        })

      Text('🔄 Reset')
        .fontSize(18)
        .width('100%')
        .height(45)
        .padding({ left: 20 })
        .textAlign(TextAlign.Start)
        .onClick(() => {
          this.imageScale = 1.0
          console.info('Reset: ' + this.imageScale)
        })

      Divider().height(2)

      Text('💾 Save Image')
        .fontSize(18)
        .width('100%')
        .height(45)
        .padding({ left: 20 })
        .textAlign(TextAlign.Start)
        .onClick(() => {
          console.info('Save Image clicked')
        })
    }
    .width(250)
  }

  build() {
    Column() {
      Text('Image Context Menu Example')
        .fontSize(24)
        .fontWeight(FontWeight.Bold)
        .margin(20)

      Text('Scale: ' + this.imageScale.toFixed(1))
        .fontSize(16)
        .margin(10)

      // Placeholder image using colored rectangle
      Circle()
        .width(200)
        .height(200)
        .borderRadius(10)
        .scale({ x: this.imageScale, y: this.imageScale })
        .bindContextMenu(this.ImageMenuBuilder, ResponseType.LongPress, {
        })
        .margin(20)

      Text('Long press the image to show options')
        .fontSize(16)
        .fontColor(Color.Gray)
        .margin(20)
    }
    .width('100%')
    .height('100%')
  }
}
