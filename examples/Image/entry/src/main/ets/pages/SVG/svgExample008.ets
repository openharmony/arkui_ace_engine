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
 * SVG Image Attributes Example - Demonstrates various SVG image attributes
 * 
 */
@Entry
@Component
struct svgExample008 {
  @State opacityValue: number = 1.0
  @State borderRadius: number = 0
  @State borderWidth: number = 0
  @State shadowRadius: number = 0
  @State rotationAngle: number = 0

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('SVG Image Attributes Example')
          .fontSize(20)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 10 })

        // Opacity control
        Text('Opacity: ' + this.opacityValue.toFixed(1))
          .fontSize(16)

        Image($r('app.media.testSvg'))
          .width(120)
          .height(120)
          .opacity(this.opacityValue)
          .border({ width: 1, color: Color.Gray })

        Slider({
          value: this.opacityValue,
          min: 0,
          max: 1,
          step: 0.1
        })
          .width('80%')
          .onChange((value: number) => {
            this.opacityValue = value
          })

        Divider()

        // Border radius control
        Text('Border Radius: ' + this.borderRadius)
          .fontSize(16)

        Image($r('app.media.svg'))
          .width(120)
          .height(120)
          .borderRadius(this.borderRadius)
          .border({ width: 1, color: Color.Gray })
          .backgroundColor(Color.LightBlue)

        Slider({
          value: this.borderRadius,
          min: 0,
          max: 60,
          step: 5
        })
          .width('80%')
          .onChange((value: number) => {
            this.borderRadius = value
          })

        Divider()

        // Border width control
        Text('Border Width: ' + this.borderWidth)
          .fontSize(16)

        Image($r('app.media.icon'))
          .width(120)
          .height(120)
          .border({
            width: this.borderWidth,
            color: Color.Blue,
            style: BorderStyle.Solid
          })

        Slider({
          value: this.borderWidth,
          min: 0,
          max: 20,
          step: 1
        })
          .width('80%')
          .onChange((value: number) => {
            this.borderWidth = value
          })

        Divider()

        // Shadow radius control
        Text('Shadow Radius: ' + this.shadowRadius)
          .fontSize(16)

        Image($r('app.media.star'))
          .width(120)
          .height(120)
          .shadow({
            radius: this.shadowRadius,
            color: Color.Gray,
            offsetX: 5,
            offsetY: 5
          })
          .border({ width: 1, color: Color.Gray })

        Slider({
          value: this.shadowRadius,
          min: 0,
          max: 30,
          step: 2
        })
          .width('80%')
          .onChange((value: number) => {
            this.shadowRadius = value
          })

        Divider()

        // Rotation angle control
        Text('Rotation Angle: ' + this.rotationAngle)
          .fontSize(16)

        Image($r('app.media.heart'))
          .width(120)
          .height(120)
          .rotate({ angle: this.rotationAngle })
          .border({ width: 1, color: Color.Gray })

        Slider({
          value: this.rotationAngle,
          min: 0,
          max: 360,
          step: 15
        })
          .width('80%')
          .onChange((value: number) => {
            this.rotationAngle = value
          })

        Divider()

        // Shadow effects presets
        Text('Shadow Effects Presets')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        Row({ space: 15 }) {
          Column({ space: 5 }) {
            Image($r('app.media.testSvg'))
              .width(80)
              .height(80)
              .shadow({
                radius: 5,
                color: Color.Gray,
                offsetX: 2,
                offsetY: 2
              })
            Text('Small').fontSize(12)
          }

          Column({ space: 5 }) {
            Image($r('app.media.svg'))
              .width(80)
              .height(80)
              .shadow({
                radius: 10,
                color: Color.Blue,
                offsetX: 5,
                offsetY: 5
              })
            Text('Medium').fontSize(12)
          }

          Column({ space: 5 }) {
            Image($r('app.media.icon'))
              .width(80)
              .height(80)
              .shadow({
                radius: 15,
                color: Color.Red,
                offsetX: 8,
                offsetY: 8
              })
            Text('Large').fontSize(12)
          }
        }
        .width('100%')
        .justifyContent(FlexAlign.SpaceEvenly)

        Divider()

        // Background color combinations
        Text('With Background Colors')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        Row({ space: 15 }) {
          Image($r('app.media.testSvg'))
            .width(80)
            .height(80)
            .backgroundColor(Color.LightBlue)
            .border({ width: 1, color: Color.Gray })

          Image($r('app.media.svg'))
            .width(80)
            .height(80)
            .backgroundColor(Color.LightGreen)
            .border({ width: 1, color: Color.Gray })

          Image($r('app.media.icon'))
            .width(80)
            .height(80)
            .backgroundColor(Color.LightYellow)
            .border({ width: 1, color: Color.Gray })
        }
        .width('100%')
        .justifyContent(FlexAlign.SpaceEvenly)
        .margin({ bottom: 20 })

        // Border styles
        Text('Border Styles')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        Row({ space: 15 }) {
          Image($r('app.media.star'))
            .width(80)
            .height(80)
            .border({
              width: 3,
              color: Color.Black,
              style: BorderStyle.Solid
            })

          Image($r('app.media.heart'))
            .width(80)
            .height(80)
            .border({
              width: 3,
              color: Color.Blue,
              style: BorderStyle.Dashed
            })

          Image($r('app.media.testSvg'))
            .width(80)
            .height(80)
            .border({
              width: 3,
              color: Color.Red,
              style: BorderStyle.Dotted
            })
        }
        .width('100%')
        .justifyContent(FlexAlign.SpaceEvenly)
        .margin({ bottom: 20 })
      }
      .width('100%')
      .padding(10)
    }
    .width('100%')
    .height('100%')
  }
}
