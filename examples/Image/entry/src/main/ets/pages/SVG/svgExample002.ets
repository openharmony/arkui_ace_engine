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

/**
 * SVG FillColor Example - Demonstrates how to change SVG colors using fillColor property
 * 
 */
@Entry
@Component
struct svgExample002 {
  @State currentColor: Color = Color.Red
  @State colorName: string = 'Red'

  build() {
    Column({ space: 15 }) {
      Text('SVG FillColor Example')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 20, bottom: 10 })

      Text('Current fill color: ' + this.colorName)
        .fontSize(16)

      // Display SVG with dynamic fill color
      Image($r('app.media.testSvg'))
        .width(150)
        .height(150)
        .margin(15)
        .fillColor(this.currentColor)

      // Color selection buttons
      Row({ space: 10 }) {
        Button('Red')
          .backgroundColor(Color.Red)
          .onClick(() => {
            this.currentColor = Color.Red
            this.colorName = 'Red'
          })

        Button('Green')
          .backgroundColor(Color.Green)
          .onClick(() => {
            this.currentColor = Color.Green
            this.colorName = 'Green'
          })

        Button('Blue')
          .backgroundColor(Color.Blue)
          .onClick(() => {
            this.currentColor = Color.Blue
            this.colorName = 'Blue'
          })
      }
      .margin({ bottom: 10 })

      // Fixed color examples
      Text('Fixed fill colors')
        .fontSize(16)
        .margin({ top: 10 })

      Row({ space: 15 }) {
        Image($r('app.media.testSvg'))
          .width(80)
          .height(80)
          .fillColor(Color.Orange)

        Image($r('app.media.testSvg'))
          .width(80)
          .height(80)
          .fillColor(Color.Purple)

        Image($r('app.media.testSvg'))
          .width(80)
          .height(80)
          .fillColor(Color.Brown)
      }
      .margin({ bottom: 20 })
    }
    .width('100%')
    .height('100%')
    .padding(10)
  }
}
