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
 * Example for testing the Image component's fillColor interface,
 * demonstrating support for different color spaces (Display-P3 and sRGB)
 * using ColorMetrics.
 */
import { ColorMetrics } from '@kit.ArkUI'

@Entry
@Component
struct fillColorDemo01 {
  // Define Display-P3 and sRGB colors for red, green, and blue
  @State p3Red: ColorMetrics = ColorMetrics.colorWithSpace(ColorSpace.DISPLAY_P3, 1, 0, 0)
  @State sRGBRed: ColorMetrics = ColorMetrics.colorWithSpace(ColorSpace.SRGB, 1, 0, 0)
  @State p3Green: ColorMetrics = ColorMetrics.colorWithSpace(ColorSpace.DISPLAY_P3, 0, 1, 0)
  @State sRGBGreen: ColorMetrics = ColorMetrics.colorWithSpace(ColorSpace.SRGB, 0, 1, 0)
  @State p3Blue: ColorMetrics = ColorMetrics.colorWithSpace(ColorSpace.DISPLAY_P3, 0, 0, 1)
  @State sRGBBlue: ColorMetrics = ColorMetrics.colorWithSpace(ColorSpace.SRGB, 0, 0, 1)

  // Define an array of colors to dynamically switch between
  @State colorArray: (Color | undefined | ColorMetrics | ColorContent)[] = [
    this.p3Red, this.sRGBRed, this.p3Green, this.sRGBGreen, this.p3Blue,
    this.sRGBBlue, ColorContent.ORIGIN, Color.Gray, undefined
  ]

  // Define a corresponding label array for display
  @State colorArrayStr: string[] = [
    'P3 Red', 'SRGB Red', 'P3 Green', 'SRGB Green',
    'P3 Blue', 'SRGB Blue', 'ColorContent.ORIGIN', 'Gray', 'undefined'
  ]

  // Index for tracking the currently selected color
  @State arrayIdx: number = 0

  build() {
    Column() {
      // Show currently applied fillColor label
      Text('FillColor is ' + this.colorArrayStr[this.arrayIdx])

      // Display an SVG image with dynamically applied fillColor
      Image($r('app.media.testSvg'))
        .width(110)
        .height(110)
        .margin(15)
        .fillColor(this.colorArray[this.arrayIdx])

      // Button to cycle through different fillColor values
      Button('ChangeFillColor')
        .onClick(() => {
          this.arrayIdx = (this.arrayIdx + 1) % this.colorArray.length
        })

      Divider()

      // Show three fixed examples using sRGB color space
      Text('FillColor is SRGB Red')
      Image($r('app.media.testSvg'))
        .width(110)
        .height(110)
        .margin(15)
        .fillColor(this.sRGBRed)

      Text('FillColor is SRGB Green')
      Image($r('app.media.testSvg'))
        .width(110)
        .height(110)
        .margin(15)
        .fillColor(this.sRGBGreen)

      Text('FillColor is SRGB Blue')
      Image($r('app.media.testSvg'))
        .width(110)
        .height(110)
        .margin(15)
        .fillColor(this.sRGBBlue)
    }
  }
}
