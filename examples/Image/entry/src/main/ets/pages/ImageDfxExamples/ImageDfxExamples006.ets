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
 * Example: Demonstrates loading and displaying an SVG vector image.
 *
 * The SVG format supports **infinite scalability** without loss of quality.
 * This example loads an SVG file from app resources and allows switching fill color dynamically.
 */
@Entry
@Component
struct svgDemo01 {
  // Control the SVG fill color dynamically
  @State color: string = '#007DFF'

  build() {
    Column() {
      // Display SVG image from app resource (e.g., app/media/icon.svg)
      Image($r('app.media.icon_svg'))
        .width(150)
        .height(150)
        .fillColor(this.color)
        .margin({ top: 80 })

      // Button to toggle fill color between blue and red
      Button('Toggle SVG Fill Color')
        .margin({ top: 20 })
        .onClick(() => {
          animateTo({}, () => {
            this.color = this.color === '#007DFF' ? '#FF3B30' : '#007DFF'
          })
        })
    }
    .alignItems(HorizontalAlign.Center)
    .height('100%')
  }
}
