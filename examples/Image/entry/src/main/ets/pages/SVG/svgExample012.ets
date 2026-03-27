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
 * SVG Image Fit Example - Demonstrates SVG fitting in different containers
 * 
 */
@Entry
@Component
struct svgExample012 {
  @State containerWidth: number = 200
  @State containerHeight: number = 200
  @State currentFit: ImageFit = ImageFit.Contain

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('SVG Image Fit Example')
          .fontSize(20)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 10 })

        // Dynamic container size
        Text('Dynamic Container Size')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        Text('Size: ' + this.containerWidth + ' x ' + this.containerHeight)
          .fontSize(14)
          .fontColor(Color.Gray)

        Image($r('app.media.testSvg'))
          .width(this.containerWidth)
          .height(this.containerHeight)
          .objectFit(this.currentFit)
          .border({ width: 2, color: Color.Blue, style: BorderStyle.Dashed })
          .backgroundColor(Color.LightGray)

        Row({ space: 10 }) {
          Column({ space: 5 }) {
            Text('Width').fontSize(12)
            Slider({
              value: this.containerWidth,
              min: 100,
              max: 300,
              step: 10
            })
              .width('100%')
              .onChange((value: number) => {
                this.containerWidth = value
              })
          }
          .width('48%')

          Column({ space: 5 }) {
            Text('Height').fontSize(12)
            Slider({
              value: this.containerHeight,
              min: 100,
              max: 300,
              step: 10
            })
              .width('100%')
              .onChange((value: number) => {
                this.containerHeight = value
              })
          }
          .width('48%')
        }
        .width('100%')

        Divider()

        // Aspect ratio fitting
        Text('Aspect Ratio Fit')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        Row({ space: 15 }) {
          Column({ space: 5 }) {
            Image($r('app.media.svg'))
              .width(150)
              .height(100)
              .objectFit(ImageFit.Contain)
              .border({ width: 1, color: Color.Gray })
            Text('Contain').fontSize(12)
          }

          Column({ space: 5 }) {
            Image($r('app.media.svg'))
              .width(150)
              .height(100)
              .objectFit(ImageFit.Cover)
              .border({ width: 1, color: Color.Gray })
            Text('Cover').fontSize(12)
          }

          Column({ space: 5 }) {
            Image($r('app.media.svg'))
              .width(150)
              .height(100)
              .objectFit(ImageFit.Fill)
              .border({ width: 1, color: Color.Gray })
            Text('Fill').fontSize(12)
          }
        }
        .width('100%')
        .justifyContent(FlexAlign.SpaceEvenly)

        Divider()

        // Responsive layout
        Text('Responsive Layout')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        Column({ space: 10 }) {
          Row({ space: 10 }) {
            Image($r('app.media.icon'))
              .width('30%')
              .aspectRatio(1)
              .objectFit(ImageFit.Contain)
              .border({ width: 1, color: Color.Gray })

            Image($r('app.media.star'))
              .width('30%')
              .aspectRatio(1)
              .objectFit(ImageFit.Contain)
              .border({ width: 1, color: Color.Gray })

            Image($r('app.media.heart'))
              .width('30%')
              .aspectRatio(1)
              .objectFit(ImageFit.Contain)
              .border({ width: 1, color: Color.Gray })
          }
          .width('100%')

          Row({ space: 10 }) {
            Image($r('app.media.testSvg'))
              .width('48%')
              .aspectRatio(1)
              .objectFit(ImageFit.Contain)
              .border({ width: 1, color: Color.Gray })

            Image($r('app.media.svg'))
              .width('48%')
              .aspectRatio(1)
              .objectFit(ImageFit.Contain)
              .border({ width: 1, color: Color.Gray })
          }
          .width('100%')
        }
        .width('100%')

        Divider()

        // Adaptive container
        Text('Adaptive Container')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        Column({ space: 10 }) {
          Row() {
            Image($r('app.media.testSvg'))
              .width('100%')
              .height(100)
              .objectFit(ImageFit.FitWidth)
              .border({ width: 1, color: Color.Gray })
          }
          .width('100%')

          Row() {
            Image($r('app.media.svg'))
              .width(100)
              .height('100%')
              .objectFit(ImageFit.FitHeight)
              .border({ width: 1, color: Color.Gray })
          }
          .height(150)
        }
        .width('100%')

        Divider()

        // Different shape containers
        Text('Different Shape Containers')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        Row({ space: 15 }) {
          Column({ space: 5 }) {
            Image($r('app.media.icon'))
              .width(100)
              .height(100)
              .borderRadius(10)
              .objectFit(ImageFit.Contain)
              .clip(true)
              .border({ width: 1, color: Color.Gray })
            Text('Square').fontSize(12)
          }

          Column({ space: 5 }) {
            Image($r('app.media.star'))
              .width(120)
              .height(80)
              .borderRadius(15)
              .objectFit(ImageFit.Cover)
              .clip(true)
              .border({ width: 1, color: Color.Gray })
            Text('Rectangle').fontSize(12)
          }

          Column({ space: 5 }) {
            Image($r('app.media.heart'))
              .width(90)
              .height(90)
              .borderRadius(45)
              .objectFit(ImageFit.Contain)
              .clip(true)
              .border({ width: 1, color: Color.Gray })
            Text('Circle').fontSize(12)
          }
        }
        .width('100%')
        .justifyContent(FlexAlign.SpaceEvenly)

        Divider()

        // Scale constraints
        Text('Scale Constraints')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        Row({ space: 15 }) {
          Column({ space: 5 }) {
            Image($r('app.media.testSvg'))
              .width(120)
              .height(120)
              .objectFit(ImageFit.None)
              .border({ width: 1, color: Color.Gray })
            Text('None').fontSize(12)
          }

          Column({ space: 5 }) {
            Image($r('app.media.svg'))
              .width(120)
              .height(120)
              .objectFit(ImageFit.ScaleDown)
              .border({ width: 1, color: Color.Gray })
            Text('ScaleDown').fontSize(12)
          }
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
