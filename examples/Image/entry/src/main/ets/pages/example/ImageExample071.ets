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
 * 图片缩放示例
 */
@Entry
@Component
struct ImageExample071 {
  @State scale: number = 1.0

  build() {
    Column() {
      Text('图片缩放示例')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Image($r('app.media.png'))
        .width(200)
        .height(200)
        .scale({ x: this.scale, y: this.scale })
        .margin({ bottom: 20 })

      Row({ space: 10 }) {
        Button('0.5x')
          .onClick(() => {
            this.scale = 0.5
          })
        Button('1.0x')
          .onClick(() => {
            this.scale = 1.0
          })
        Button('1.5x')
          .onClick(() => {
            this.scale = 1.5
          })
        Button('2.0x')
          .onClick(() => {
            this.scale = 2.0
          })
      }
      .margin({ bottom: 10 })

      Slider({ value: this.scale, min: 0.1, max: 3.0, step: 0.1 })
        .width('100%')
        .onChange((value) => {
          this.scale = value
        })

      Text('当前缩放: ' + this.scale.toFixed(1) + 'x')
        .fontSize(14)
        .margin({ top: 10 })
    }
    .width('100%')
    .height('100%')
    .padding(20)
  }
}
