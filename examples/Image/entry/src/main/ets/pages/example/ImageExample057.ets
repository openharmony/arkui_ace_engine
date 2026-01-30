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
 * 图片边框样式示例
 */
@Entry
@Component
struct ImageExample057 {
  @State borderWidth: number = 1
  @State borderColor: Color = Color.Black

  build() {
    Column() {
      Text('图片边框样式示例')
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 20 })

      Image($r('app.media.png'))
        .width(200)
        .height(200)
        .border({ width: this.borderWidth, color: this.borderColor, radius: 0 })
        .margin({ bottom: 20 })

      Row({ space: 10 }) {
        Button('黑边1px')
          .onClick(() => {
            this.borderWidth = 1
            this.borderColor = Color.Black
          })
        Button('红边3px')
          .onClick(() => {
            this.borderWidth = 3
            this.borderColor = Color.Red
          })
        Button('蓝边5px')
          .onClick(() => {
            this.borderWidth = 5
            this.borderColor = Color.Blue
          })
      }
    }
    .width('100%')
    .height('100%')
    .padding(20)
  }
}
