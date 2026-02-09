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
 * SVG ColorMetrics Example - Demonstrates using ColorMetrics to apply different color spaces to SVG
 * 
 */
import { ColorMetrics } from '@kit.ArkUI'

@Entry
@Component
struct svgExample005 {
  // Define Display-P3 and sRGB color space colors
  @State p3Red: ColorMetrics = ColorMetrics.colorWithSpace(ColorSpace.DISPLAY_P3, 1, 0, 0)
  @State sRGBRed: ColorMetrics = ColorMetrics.colorWithSpace(ColorSpace.SRGB, 1, 0, 0)
  @State p3Green: ColorMetrics = ColorMetrics.colorWithSpace(ColorSpace.DISPLAY_P3, 0, 1, 0)
  @State sRGBGreen: ColorMetrics = ColorMetrics.colorWithSpace(ColorSpace.SRGB, 0, 1, 0)
  @State p3Blue: ColorMetrics = ColorMetrics.colorWithSpace(ColorSpace.DISPLAY_P3, 0, 0, 1)
  @State sRGBBlue: ColorMetrics = ColorMetrics.colorWithSpace(ColorSpace.SRGB, 0, 0, 1)

  // Color array for switching
  @State colorArray: (Color | ColorMetrics)[] = [
    this.p3Red, this.sRGBRed, this.p3Green, this.sRGBGreen,
    this.p3Blue, this.sRGBBlue, Color.Orange, Color.Purple
  ]

  @State colorArrayStr: string[] = [
    'P3 Red', 'SRGB Red', 'P3 Green', 'SRGB Green',
    'P3 Blue', 'SRGB Blue', 'Orange', 'Purple'
  ]

  @State arrayIdx: number = 0

  build() {
    Column({ space: 15 }) {
      Text('SVG ColorMetrics Example')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 20, bottom: 10 })

      Text('Supporting Display-P3 and sRGB color spaces')
        .fontSize(14)
        .fontColor(Color.Gray)

      Text('Current color: ' + this.colorArrayStr[this.arrayIdx])
        .fontSize(16)
        .margin({ top: 10 })

      // SVG with dynamic color switching
      Image($r('app.media.testSvg'))
        .width(150)
        .height(150)
        .margin(15)
        .fillColor(this.colorArray[this.arrayIdx])
        .border({ width: 2, color: Color.Gray })

      Button('Change Color')
        .onClick(() => {
          this.arrayIdx = (this.arrayIdx + 1) % this.colorArray.length
        })

      Divider()

      // Color space comparison
      Text('Color Space Comparison')
        .fontSize(16)
        .fontWeight(FontWeight.Medium)

      Row({ space: 10 }) {
        Column({ space: 5 }) {
          Image($r('app.media.testSvg'))
            .width(80)
            .height(80)
            .fillColor(this.p3Red)
          Text('P3 Red').fontSize(12)
        }

        Column({ space: 5 }) {
          Image($r('app.media.testSvg'))
            .width(80)
            .height(80)
            .fillColor(this.sRGBRed)
          Text('SRGB Red').fontSize(12)
        }

        Column({ space: 5 }) {
          Image($r('app.media.testSvg'))
            .width(80)
            .height(80)
            .fillColor(this.p3Green)
          Text('P3 Green').fontSize(12)
        }

        Column({ space: 5 }) {
          Image($r('app.media.testSvg'))
            .width(80)
            .height(80)
            .fillColor(this.sRGBGreen)
          Text('SRGB Green').fontSize(12)
        }
      }
      .margin({ bottom: 20 })

      Row({ space: 10 }) {
        Column({ space: 5 }) {
          Image($r('app.media.testSvg'))
            .width(80)
            .height(80)
            .fillColor(this.p3Blue)
          Text('P3 Blue').fontSize(12)
        }

        Column({ space: 5 }) {
          Image($r('app.media.testSvg'))
            .width(80)
            .height(80)
            .fillColor(this.sRGBBlue)
          Text('SRGB Blue').fontSize(12)
        }
      }
    }
    .width('100%')
    .height('100%')
    .padding(10)
  }
}
