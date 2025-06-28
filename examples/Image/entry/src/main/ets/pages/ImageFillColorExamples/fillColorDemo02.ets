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
 * Example demonstrating how to dynamically change the fillColor of an SVG image
 * using attributeModifier and ColorMetrics (supports Display-P3 and sRGB).
 */
import { ColorMetrics } from '@kit.ArkUI'

// Custom attribute modifier for the Image component
class SvgImageModifier implements AttributeModifier<ImageAttribute> {
  // Define Display-P3 and sRGB colors for red, green, and blue
  public p3Red: ColorMetrics = ColorMetrics.colorWithSpace(ColorSpace.DISPLAY_P3, 1, 0, 0)
  public sRGBRed: ColorMetrics = ColorMetrics.colorWithSpace(ColorSpace.SRGB, 1, 0, 0)
  public p3Green: ColorMetrics = ColorMetrics.colorWithSpace(ColorSpace.DISPLAY_P3, 0, 1, 0)
  public sRGBGreen: ColorMetrics = ColorMetrics.colorWithSpace(ColorSpace.SRGB, 0, 1, 0)
  public p3Blue: ColorMetrics = ColorMetrics.colorWithSpace(ColorSpace.DISPLAY_P3, 0, 0, 1)
  public sRGBBlue: ColorMetrics = ColorMetrics.colorWithSpace(ColorSpace.SRGB, 0, 0, 1)

  // Array of color values used for dynamic switching
  public colorArray: (Color | undefined | ColorMetrics | ColorContent)[] = [
    this.p3Red, this.sRGBRed, this.p3Green, this.sRGBGreen, this.p3Blue,
    this.sRGBBlue, ColorContent.ORIGIN, Color.Gray, undefined
  ]

  // Corresponding text labels for each color
  public colorArrayStr: string[] = [
    'P3 Red', 'SRGB Red', 'P3 Green', 'SRGB Green',
    'P3 Blue', 'SRGB Blue', 'ColorContent.ORIGIN', 'Gray', 'undefined'
  ]

  // Current index to determine which color is applied
  public colorIdx: number = 0

  // Called when Image component updates its attributes; sets fillColor
  applyNormalAttribute(instance: ImageAttribute): void {
    instance.fillColor(this.colorArray[this.colorIdx])
  }
}

@Entry
@Component
struct fillColorDemo02 {
  // Define sRGB fallback colors for fixed examples
  @State sRGBRed: ColorMetrics = ColorMetrics.colorWithSpace(ColorSpace.SRGB, 1, 0, 0)
  @State sRGBGreen: ColorMetrics = ColorMetrics.colorWithSpace(ColorSpace.SRGB, 0, 1, 0)
  @State sRGBBlue: ColorMetrics = ColorMetrics.colorWithSpace(ColorSpace.SRGB, 0, 0, 1)

  // Text labels shown in UI, consistent with modifier's color order
  @State colorArrayStr: string[] = [
    'P3 Red', 'SRGB Red', 'P3 Green', 'SRGB Green',
    'P3 Blue', 'SRGB Blue', 'ColorContent.ORIGIN', 'Gray', 'undefined'
  ]

  // Used to display current selected color text in the UI
  @State arrayIdx: number = 0

  // Create a modifier instance to apply dynamic fillColor
  @State modifier: SvgImageModifier = new SvgImageModifier()

  build() {
    Column() {
      // Display current fillColor label
      Text('FillColor is ' + this.colorArrayStr[this.arrayIdx])

      // SVG image using the attributeModifier for dynamic fillColor
      Image($r('app.media.testSvg'))
        .width(110)
        .height(110)
        .margin(15)
        .attributeModifier(this.modifier)

      // Button to switch to the next color in the array
      Button('ChangeFillColor')
        .onClick(() => {
          this.modifier.colorIdx = (this.modifier.colorIdx + 1) % this.modifier.colorArray.length
          this.arrayIdx = this.modifier.colorIdx
        })

      Divider()

      // Fixed examples with sRGB Red, Green, and Blue
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
