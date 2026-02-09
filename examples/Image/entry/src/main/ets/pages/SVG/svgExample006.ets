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
 * SVG Animation Example - Demonstrates SVG animation effects
 * 
 */
@Entry
@Component
struct svgExample006 {
  @State rotateAngle: number = 0
  @State scaleValue: number = 1.0
  @State translateX: number = 0
  @State opacityValue: number = 1.0

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('SVG Animation Example')
          .fontSize(20)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 10 })

        // Rotation animation
        Text('Rotation Animation')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        Image($r('app.media.testSvg'))
          .width(100)
          .height(100)
          .rotate({ angle: this.rotateAngle })
          .border({ width: 1, color: Color.Gray })
          .animation({
            duration: 2000,
            curve: Curve.EaseInOut,
            iterations: -1
          })

        Button('Start Rotation')
          .margin({ top: 10 })
          .onClick(() => {
            this.rotateAngle = this.rotateAngle + 360
          })

        Divider()

        // Scale animation
        Text('Scale Animation')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        Image($r('app.media.svg'))
          .width(100)
          .height(100)
          .scale({ x: this.scaleValue, y: this.scaleValue })
          .border({ width: 1, color: Color.Gray })
          .animation({
            duration: 1000,
            curve: Curve.EaseInOut,
            iterations: -1,
            playMode: PlayMode.Alternate
          })

        Button('Start Scale')
          .margin({ top: 10 })
          .onClick(() => {
            this.scaleValue = this.scaleValue === 1.0 ? 1.5 : 1.0
          })

        Divider()

        // Translation animation
        Text('Translation Animation')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        Image($r('app.media.icon'))
          .width(100)
          .height(100)
          .translate({ x: this.translateX, y: 0 })
          .border({ width: 1, color: Color.Gray })
          .animation({
            duration: 1500,
            curve: Curve.EaseInOut,
            iterations: -1,
            playMode: PlayMode.Alternate
          })

        Button('Start Translation')
          .margin({ top: 10 })
          .onClick(() => {
            this.translateX = this.translateX === 0 ? 100 : 0
          })

        Divider()

        // Opacity animation
        Text('Opacity Animation')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        Image($r('app.media.star'))
          .width(100)
          .height(100)
          .opacity(this.opacityValue)
          .border({ width: 1, color: Color.Gray })
          .animation({
            duration: 1200,
            curve: Curve.EaseInOut,
            iterations: -1,
            playMode: PlayMode.Alternate
          })

        Button('Start Fade')
          .margin({ top: 10 })
          .onClick(() => {
            this.opacityValue = this.opacityValue === 1.0 ? 0.2 : 1.0
          })

        Divider()

        // Combined animation example
        Text('Combined Animation')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        Image($r('app.media.heart'))
          .width(100)
          .height(100)
          .rotate({ angle: this.rotateAngle })
          .scale({ x: this.scaleValue, y: this.scaleValue })
          .opacity(this.opacityValue)
          .border({ width: 1, color: Color.Gray })
          .margin({ bottom: 20 })

        Button('Start Combined')
          .onClick(() => {
            this.rotateAngle = this.rotateAngle + 360
            this.scaleValue = this.scaleValue === 1.0 ? 1.5 : 1.0
            this.opacityValue = this.opacityValue === 1.0 ? 0.5 : 1.0
          })
      }
      .width('100%')
      .padding(10)
    }
    .width('100%')
    .height('100%')
  }
}
