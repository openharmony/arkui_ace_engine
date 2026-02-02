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
 * 图片裁剪示例
 */
@Entry
@Component
struct ImageExample065 {
  @State clipRadius: number = 0

  build() {
    Column() {
      Text('图片裁剪示例')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Image($r('app.media.png'))
        .width(200)
        .height(200)
        .clip(new Path().addRoundRect({
          x: 0,
          y: 0,
          width: 200,
          height: 200,
          radiusTopLeft: this.clipRadius,
          radiusTopRight: this.clipRadius,
          radiusBottomLeft: this.clipRadius,
          radiusBottomRight: this.clipRadius
        }))
        .margin({ bottom: 20 })

      Row({ space: 10 }) {
        Button('无裁剪')
          .onClick(() => {
            this.clipRadius = 0
          })
        Button('圆角50')
          .onClick(() => {
            this.clipRadius = 50
          })
        Button('圆角100')
          .onClick(() => {
            this.clipRadius = 100
          })
      }

      Text('当前圆角: ' + this.clipRadius)
        .fontSize(14)
        .margin({ top: 10 })
    }
    .width('100%')
    .height('100%')
    .padding(20)
  }
}
