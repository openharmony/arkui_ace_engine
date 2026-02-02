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

/**
 *图片叠加层示例
 */
@Entry
@Component
struct ImageExample067 {
  @State overlayText: string = '图片'

  build() {
    Column() {
      Text('图片叠加层示例')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Image($r('app.media.png'))
        .width(200)
        .height(200)
        .overlay(this.overlayText, {
          align: Alignment.Bottom,
          offset: { x: 0, y: -20 }
        })
        .margin({ bottom: 20 })

      Row({ space: 10 }) {
        Button('图片')
          .onClick(() => {
            this.overlayText = '图片'
          })
        Button('风景')
          .onClick(() => {
            this.overlayText = '风景'
          })
        Button('示例')
          .onClick(() => {
            this.overlayText = '示例'
          })
      }
    }
    .width('100%')
    .height('100%')
    .padding(20)
  }
}
