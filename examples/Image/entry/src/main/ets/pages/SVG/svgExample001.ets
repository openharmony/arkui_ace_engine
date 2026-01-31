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
 * SVG Basic Example - Demonstrates basic SVG image loading and display
 */
@Entry
@Component
struct svgExample001 {
  build() {
    Column({ space: 20 }) {
      Text('SVG Basic Example')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 20, bottom: 10 })

      // Load and display SVG image
      Image($r('app.media.svg'))
        .width(120)
        .height(120)
        .margin(10)
        .border({ width: 1, color: Color.Gray })

      // Load another SVG resource
      Image($r('app.media.testSvg'))
        .width(120)
        .height(120)
        .margin(10)
        .border({ width: 1, color: Color.Gray })

      Text('SVG images support vector scaling')
        .fontSize(14)
        .fontColor(Color.Gray)
        .margin({ bottom: 20 })
    }
    .width('100%')
    .height('100%')
    .padding(10)
  }
}
