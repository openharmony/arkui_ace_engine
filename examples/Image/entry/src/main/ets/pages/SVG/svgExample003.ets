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
 * SVG Size Scaling Example - Demonstrates SVG vector scaling at different sizes
 * 
 */
@Entry
@Component
struct svgExample003 {
  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('SVG Size Scaling Example')
          .fontSize(20)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 10 })

        Text('SVG maintains quality at any size')
          .fontSize(14)
          .fontColor(Color.Gray)

        // Small size
        Text('Small: 50x50')
          .fontSize(14)
        Image($r('app.media.testSvg'))
          .width(50)
          .height(50)
          .border({ width: 1, color: Color.LightGray })

        // Medium-small size
        Text('Medium-Small: 80x80')
          .fontSize(14)
        Image($r('app.media.testSvg'))
          .width(80)
          .height(80)
          .border({ width: 1, color: Color.LightGray })

        // Medium size
        Text('Medium: 120x120')
          .fontSize(14)
        Image($r('app.media.testSvg'))
          .width(120)
          .height(120)
          .border({ width: 1, color: Color.LightGray })

        // Large size
        Text('Large: 180x180')
          .fontSize(14)
        Image($r('app.media.testSvg'))
          .width(180)
          .height(180)
          .border({ width: 1, color: Color.LightGray })

        // Extra large size
        Text('Extra Large: 250x250')
          .fontSize(14)
        Image($r('app.media.testSvg'))
          .width(250)
          .height(250)
          .border({ width: 1, color: Color.LightGray })

        Text('All images remain sharp and clear')
          .fontSize(14)
          .fontColor(Color.Gray)
          .margin({ bottom: 20 })
      }
      .width('100%')
      .padding(10)
    }
    .width('100%')
    .height('100%')
  }
}
