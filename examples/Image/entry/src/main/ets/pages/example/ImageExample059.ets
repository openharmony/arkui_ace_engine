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
 * 图片透明度示例
 */
@Entry
@Component
struct ImageExample059 {
  @State opacity: number = 1.0

  build() {
    Column() {
      Text('图片透明度示例')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Image($r('app.media.png'))
        .width(200)
        .height(200)
        .opacity(this.opacity)
        .margin({ bottom: 20 })

      Row({ space: 10 }) {
        Button('不透明')
          .onClick(() => {
            this.opacity = 1.0
          })
        Button('50%')
          .onClick(() => {
            this.opacity = 0.5
          })
        Button('30%')
          .onClick(() => {
            this.opacity = 0.3
          })
      }
      .margin({ bottom: 10 })

      Text('当前透明度: ' + (this.opacity * 100).toFixed(0) + '%')
        .fontSize(14)

      Slider({ value: this.opacity, min: 0, max: 1, step: 0.1 })
        .width('100%')
        .margin({ top: 20 })
        .onChange((value) => {
          this.opacity = value
        })
    }
    .width('100%')
    .height('100%')
    .padding(20)
  }
}
