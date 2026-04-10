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
 * SVG Overlay Example - Demonstrates SVG overlay effects
 * 
 */
@Entry
@Component
struct svgExample011 {
  @State overlayText: string = 'Overlay'
  @State overlayOpacity: number = 0.8
  @State showOverlay: boolean = true

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('SVG Overlay Example')
          .fontSize(20)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 10 })

        // Basic overlay
        Text('Basic Overlay')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        Image($r('app.media.testSvg'))
          .width(150)
          .height(150)
          .overlay(this.overlayText, {
            align: Alignment.Center
          })

        Divider()

        // Positioned overlay
        Text('Positioned Overlay')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        Row({ space: 15 }) {
          Image($r('app.media.svg'))
            .width(100)
            .height(100)
            .overlay('Top', {
              align: Alignment.Top,
              offset: { x: 0, y: 10 }
            })

          Image($r('app.media.icon'))
            .width(100)
            .height(100)
            .overlay('Bottom', {
              align: Alignment.Bottom,
              offset: { x: 0, y: -10 }
            })

          Image($r('app.media.star'))
            .width(100)
            .height(100)
            .overlay('Center', {
              align: Alignment.Center
            })
        }
        .width('100%')
        .justifyContent(FlexAlign.SpaceEvenly)

        Divider()

        // Styled overlay
        Text('Styled Overlay')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        Image($r('app.media.heart'))
          .width(150)
          .height(150)
          .overlay('SVG Heart', {
            align: Alignment.BottomEnd
          })
          .overlay('Custom', {
            align: Alignment.TopStart
          })

        Divider()

        // Dynamic overlay text
        Text('Dynamic Overlay Text')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        @State dynamicText: string = 'Dynamic'

        Image($r('app.media.testSvg'))
          .width(150)
          .height(150)
          .overlay(this.dynamicText, {
            align: Alignment.Center
          })

        Row({ space: 10 }) {
          Button('Text 1')
            .onClick(() => {
              this.dynamicText = 'Text 1'
            })

          Button('Text 2')
            .onClick(() => {
              this.dynamicText = 'Text 2'
            })

          Button('Text 3')
            .onClick(() => {
              this.dynamicText = 'Text 3'
            })
        }
        .width('100%')
        .justifyContent(FlexAlign.Center)

        Divider()

        // Multiple overlays
        Text('Multiple Overlays')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        Image($r('app.media.svg'))
          .width(150)
          .height(150)
          .overlay('Layer 1', {
            align: Alignment.TopStart,
            offset: { x: 5, y: 5 }
          })
          .overlay('Layer 2', {
            align: Alignment.TopEnd,
            offset: { x: -5, y: 5 }
          })
          .overlay('Layer 3', {
            align: Alignment.BottomStart,
            offset: { x: 5, y: -5 }
          })
          .overlay('Layer 4', {
            align: Alignment.BottomEnd,
            offset: { x: -5, y: -5 }
          })

        Divider()

        // Icon overlay
        Text('Icon Overlay')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        Row({ space: 15 }) {
          Image($r('app.media.testSvg'))
            .width(100)
            .height(100)
            .overlay('Badge', {
              align: Alignment.TopEnd
            })

          Image($r('app.media.svg'))
            .width(100)
            .height(100)
            .overlay('New', {
              align: Alignment.TopStart
            })

          Image($r('app.media.icon'))
            .width(100)
            .height(100)
            .overlay('Hot', {
              align: Alignment.BottomEnd
            })
        }
        .width('100%')
        .justifyContent(FlexAlign.SpaceEvenly)

        Divider()

        // Conditional overlay
        Text('Conditional Overlay')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        Image($r('app.media.star'))
          .width(150)
          .height(150)
          .overlay(this.showOverlay ? 'Visible' : '', {
            align: Alignment.Center
          })

        Button('Toggle Overlay: ' + (this.showOverlay ? 'On' : 'Off'))
          .onClick(() => {
            this.showOverlay = !this.showOverlay
          })

        Divider()

        // Opacity overlay
        Text('Opacity Overlay')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        Image($r('app.media.heart'))
          .width(150)
          .height(150)
          .overlay('Opacity: ' + this.overlayOpacity.toFixed(1), {
            align: Alignment.Center
          })

        Slider({
          value: this.overlayOpacity,
          min: 0,
          max: 1,
          step: 0.1
        })
          .width('80%')
          .onChange((value: number) => {
            this.overlayOpacity = value
          })

        Divider()

        // Colored overlay
        Text('Colored SVG Overlay')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        Row({ space: 15 }) {
          Image($r('app.media.testSvg'))
            .width(100)
            .height(100)
            .fillColor(Color.Red)
            .overlay('Red', {
              align: Alignment.Bottom
            })

          Image($r('app.media.svg'))
            .width(100)
            .height(100)
            .fillColor(Color.Green)
            .overlay('Green', {
              align: Alignment.Bottom
            })

          Image($r('app.media.icon'))
            .width(100)
            .height(100)
            .fillColor(Color.Blue)
            .overlay('Blue', {
              align: Alignment.Bottom
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
