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
 * 图片渐变示例
 */
@Entry
@Component
struct ImageExample068 {
  @State showGradient: boolean = false

  build() {
    Column() {
      Text('图片渐变示例')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Stack() {
        Image($r('app.media.png'))
          .width(200)
          .height(200)

        if (this.showGradient) {
          LinearGradient({
            angle: 90,
            colors: [['rgba(255, 255, 255, 0)', 0.0], ['rgba(255, 255, 255, 0.8)', 1.0]]
          })
            .width(200)
            .height(100)
            .position({ x: 0, y: 100 })
        }
      }
      .margin({ bottom: 20 })

      Row() {
        Button('显示渐变')
          .onClick(() => {
            this.showGradient = true
          })
          .margin({ right: 10 })

        Button('隐藏渐变')
          .onClick(() => {
            this.showGradient = false
          })
      }
    }
    .width('100%')
    .height('100%')
    .padding(20)
  }
}
