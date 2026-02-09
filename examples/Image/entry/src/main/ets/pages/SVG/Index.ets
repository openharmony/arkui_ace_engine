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
 * SVG Examples Index Page
 * SVG Examples Index Page with navigation to all test examples
 */
import { router } from '@kit.ArkUI'

@Entry
@Component
struct Index {
  build() {
    Scroll() {
      Column({ space: 10 }) {
        Text('SVG Examples')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 20 })

        // Basic examples
        Text('Basic Examples')
          .fontSize(18)
          .fontWeight(FontWeight.Medium)
          .width('100%')
          .margin({ top: 10, bottom: 5 })

        this.NavigationButton('SVG Basic Example', 'Demonstrates basic SVG image loading and display',
          'pages/SVG/svgExample001')

        this.NavigationButton('SVG FillColor Example', 'Demonstrates how to change SVG colors using fillColor property',
          'pages/SVG/svgExample002')

        this.NavigationButton('SVG Size Scaling', 'Demonstrates SVG vector scaling at different sizes',
          'pages/SVG/svgExample003')

        this.NavigationButton('SVG ObjectFit', 'Demonstrates SVG display with different objectFit modes',
          'pages/SVG/svgExample004')

        this.NavigationButton('SVG ColorMetrics', 'Demonstrates using ColorMetrics to apply different color spaces to SVG',
          'pages/SVG/svgExample005')

        // Animation examples
        Text('Animation Examples')
          .fontSize(18)
          .fontWeight(FontWeight.Medium)
          .width('100%')
          .margin({ top: 15, bottom: 5 })

        this.NavigationButton('SVG Animation', 'Demonstrates SVG animation effects',
          'pages/SVG/svgExample006')

        this.NavigationButton('SVG Advanced Animation', 'Demonstrates advanced SVG animation effects',
          'pages/SVG/svgExample015')

        // Layout examples
        Text('Layout Examples')
          .fontSize(18)
          .fontWeight(FontWeight.Medium)
          .width('100%')
          .margin({ top: 15, bottom: 5 })

        this.NavigationButton('SVG Complex Layout', 'Demonstrates SVG in complex layout scenarios',
          'pages/SVG/svgExample007')

        this.NavigationButton('SVG Image Fit', 'Demonstrates SVG fitting in different containers',
          'pages/SVG/svgExample012')

        // Attribute examples
        Text('Attribute Examples')
          .fontSize(18)
          .fontWeight(FontWeight.Medium)
          .width('100%')
          .margin({ top: 15, bottom: 5 })

        this.NavigationButton('SVG Image Attributes', 'Demonstrates various SVG image attributes',
          'pages/SVG/svgExample008')

        // Event handling examples
        Text('Event Examples')
          .fontSize(18)
          .fontWeight(FontWeight.Medium)
          .width('100%')
          .margin({ top: 15, bottom: 5 })

        this.NavigationButton('SVG Event Handling', 'Demonstrates SVG event handling and interaction',
          'pages/SVG/svgExample009')

        this.NavigationButton('SVG Gesture', 'Demonstrates SVG gesture interactions',
          'pages/SVG/svgExample016')

        // Advanced feature examples
        Text('Advanced Examples')
          .fontSize(18)
          .fontWeight(FontWeight.Medium)
          .width('100%')
          .margin({ top: 15, bottom: 5 })

        this.NavigationButton('SVG Performance', 'Demonstrates SVG performance optimization techniques',
          'pages/SVG/svgExample010')

        this.NavigationButton('SVG Overlay', 'Demonstrates SVG overlay effects',
          'pages/SVG/svgExample011')

        this.NavigationButton('SVG Color Blend', 'Demonstrates SVG color blending with backgrounds',
          'pages/SVG/svgExample013')

        this.NavigationButton('SVG Image Loading', 'Demonstrates SVG loading methods and states',
          'pages/SVG/svgExample014')

        Button('Back')
          .margin({ top: 20, bottom: 20 })
          .onClick(() => {
            router.back()
          })
      }
      .width('100%')
      .padding(15)
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#F5F5F5')
  }

  @Builder
  NavigationButton(title: string, description: string, url: string) {
    Button() {
      Column({ space: 5 }) {
        Text(title)
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .fontColor(Color.White)

        Text(description)
          .fontSize(12)
          .fontColor('#E0E0E0')
      }
      .alignItems(HorizontalAlign.Start)
      .width('100%')
      .padding({ left: 10, right: 10, top: 12, bottom: 12 })
    }
    .width('100%')
    .backgroundColor('#007AFF')
    .borderRadius(8)
    .onClick(() => {
      router.pushUrl({ url: url })
    })
  }
}
