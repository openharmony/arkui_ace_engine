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
 * 图片模糊效果示例
 */
@Entry
@Component
struct ImageExample069 {
  @State blurRadius: number = 0

  build() {
    Column() {
      Text('图片模糊效果示例')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Image($r('app.media.png'))
        .width(200)
        .height(200)
        .blur(this.blurRadius)
        .margin({ bottom: 20 })

      Row({ space: 10 }) {
        Button('无模糊')
          .onClick(() => {
            this.blurRadius = 0
          })
        Button('模糊5')
          .onClick(() => {
            this.blurRadius = 5
          })
        Button('模糊10')
          .onClick(() => {
            this.blurRadius = 10
          })
        Button('模糊20')
          .onClick(() => {
            this.blurRadius = 20
          })
      }
      .margin({ bottom: 10 })

      Slider({ value: this.blurRadius, min: 0, max: 30, step: 1 })
        .width('100%')
        .onChange((value) => {
          this.blurRadius = value
        })

      Text('当前模糊度: ' + this.blurRadius)
        .fontSize(14)
        .margin({ top: 10 })
    }
    .width('100%')
    .height('100%')
    .padding(20)
  }
}
