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
 *图片旋转示例
 */
@Entry
@Component
struct ImageExample070 {
  @State angle: number = 0

  build() {
    Column() {
      Text('图片旋转示例')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Image($r('app.media.png'))
        .width(200)
        .height(200)
        .rotate({ angle: this.angle })
        .margin({ bottom: 20 })

      Row({ space: 10 }) {
        Button('0度')
          .onClick(() => {
            this.angle = 0
          })
        Button('90度')
          .onClick(() => {
            this.angle = 90
          })
        Button('180度')
          .onClick(() => {
            this.angle = 180
          })
        Button('270度')
          .onClick(() => {
            this.angle = 270
          })
      }
      .margin({ bottom: 10 })

      Slider({ value: this.angle, min: 0, max: 360, step: 15 })
        .width('100%')
        .onChange((value) => {
          this.angle = value
        })

      Text('当前角度: ' + this.angle + '°')
        .fontSize(14)
        .margin({ top: 10 })
    }
    .width('100%')
    .height('100%')
    .padding(20)
  }
}
