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
 *图片平移示例
 */
@Entry
@Component
struct ImageExample072 {
  @State translateX: number = 0
  @State translateY: number = 0

  build() {
    Column() {
      Text('图片平移示例')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Image($r('app.media.png'))
        .width(200)
        .height(200)
        .translate({ x: this.translateX, y: this.translateY })
        .margin({ bottom: 20 })

      Row() {
        Text('X轴: ')
          .fontSize(14)
        Slider({ value: this.translateX, min: -100, max: 100, step: 5 })
          .width('60%')
          .onChange((value) => {
            this.translateX = value
          })
      }
      .margin({ bottom: 10 })
      .width('100%')

      Row() {
        Text('Y轴: ')
          .fontSize(14)
        Slider({ value: this.translateY, min: -100, max: 100, step: 5 })
          .width('60%')
          .onChange((value) => {
            this.translateY = value
          })
      }
      .width('100%')

      Button('重置')
        .margin({ top: 10 })
        .onClick(() => {
          this.translateX = 0
          this.translateY = 0
        })
    }
    .width('100%')
    .height('100%')
    .padding(20)
  }
}
