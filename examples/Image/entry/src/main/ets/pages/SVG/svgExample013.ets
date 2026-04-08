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
 * SVG Color Blend Mode Example - SVGDemonstrates SVG color blending with backgrounds
 * 
 */
@Entry
@Component
struct svgExample013 {
  @State blendColor: Color = Color.Red
  @State backgroundColor: Color = Color.White
  @State blendMode: number = 0

  private blendModes: string[] = ['Normal', 'Multiply', 'Screen', 'Overlay']
  private colors: Color[] = [
    Color.Red, Color.Green, Color.Blue, Color.Yellow,
    Color.Orange, Color.Purple, Color.Cyan, Color.Pink
  ]

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('SVG Color Blend Mode Example')
          .fontSize(20)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 10 })

        // Color blending
        Text('Color Blending with fillColor')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        Grid() {
          ForEach(this.colors, (color: Color, index: number) => {
            GridItem() {
              Column({ space: 5 }) {
                Image($r('app.media.testSvg'))
                  .width(80)
                  .height(80)
                  .fillColor(color)
                  .border({ width: 1, color: Color.LightGray })

                Text('Color ' + (index + 1))
                  .fontSize(12)
              }
              .padding(5)
            }
          })
        }
        .columnsTemplate('1fr 1fr 1fr 1fr')
        .width('100%')

        Divider()

        // Background color blending
        Text('Background Color Blending')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        Row({ space: 15 }) {
          Column({ space: 5 }) {
            Image($r('app.media.svg'))
              .width(100)
              .height(100)
              .backgroundColor(Color.Red)
              .border({ width: 1, color: Color.Gray })
            Text('Red BG').fontSize(12)
          }

          Column({ space: 5 }) {
            Image($r('app.media.svg'))
              .width(100)
              .height(100)
              .backgroundColor(Color.Green)
              .border({ width: 1, color: Color.Gray })
            Text('Green BG').fontSize(12)
          }

          Column({ space: 5 }) {
            Image($r('app.media.svg'))
              .width(100)
              .height(100)
              .backgroundColor(Color.Blue)
              .border({ width: 1, color: Color.Gray })
            Text('Blue BG').fontSize(12)
          }
        }
        .width('100%')
        .justifyContent(FlexAlign.SpaceEvenly)

        Divider()

        // Gradient background effects
        Text('Gradient Background Effects')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        Row({ space: 15 }) {
          Column({ space: 5 }) {
            Image($r('app.media.icon'))
              .width(100)
              .height(100)
              .linearGradient({
                angle: 90,
                colors: [[0xFF0000, 0.0], [0x0000FF, 1.0]]
              })
              .border({ width: 1, color: Color.Gray })
            Text('Linear').fontSize(12)
          }

          Column({ space: 5 }) {
            Image($r('app.media.star'))
              .width(100)
              .height(100)
              .linearGradient({
                direction: GradientDirection.Right,
                colors: [[0xFFFF00, 0.0], [0x00FF00, 0.5], [0x0000FF, 1.0]]
              })
              .border({ width: 1, color: Color.Gray })
            Text('Multi-stop').fontSize(12)
          }

          Column({ space: 5 }) {
            Image($r('app.media.heart'))
              .width(100)
              .height(100)
              .linearGradient({
                angle: 45,
                colors: [[0xFF00FF, 0.0], [0x00FFFF, 1.0]]
              })
              .border({ width: 1, color: Color.Gray })
            Text('Diagonal').fontSize(12)
          }
        }
        .width('100%')
        .justifyContent(FlexAlign.SpaceEvenly)

        Divider()

        // Opacity blending
        Text('Opacity Blending')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        Row({ space: 15 }) {
          ForEach([1.0, 0.8, 0.6, 0.4, 0.2], (opacity: number) => {
            Column({ space: 5 }) {
              Image($r('app.media.testSvg'))
                .width(70)
                .height(70)
                .opacity(opacity)
                .backgroundColor(Color.LightBlue)
                .border({ width: 1, color: Color.Gray })

              Text(opacity.toFixed(1))
                .fontSize(12)
            }
          })
        }
        .width('100%')
        .justifyContent(FlexAlign.SpaceEvenly)

        Divider()

        // Layered blending
        Text('Layered Blending')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        Stack({ alignContent: Alignment.Center }) {
          Image($r('app.media.svg'))
            .width(150)
            .height(150)
            .fillColor(Color.Red)
            .opacity(0.5)

          Image($r('app.media.icon'))
            .width(100)
            .height(100)
            .fillColor(Color.Blue)
            .opacity(0.7)
        }
        .width(150)
        .height(150)
        .border({ width: 1, color: Color.Gray })

        Divider()

        // Dynamic color blending
        Text('Dynamic Color Blending')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        @State blendIndex: number = 0

        Image($r('app.media.testSvg'))
          .width(150)
          .height(150)
          .fillColor(this.colors[this.blendIndex])
          .border({ width: 2, color: Color.Gray })

        Row({ space: 10 }) {
          ForEach([0, 1, 2, 3], (index: number) => {
            Button('Color ' + (index + 1))
              .backgroundColor(this.colors[index])
              .onClick(() => {
                this.blendIndex = index
              })
          })
        }
        .width('100%')
        .justifyContent(FlexAlign.Center)

        Divider()

        // Duotone effect
        Text('Duotone Effect')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        Row({ space: 15 }) {
          Column({ space: 5 }) {
            Image($r('app.media.star'))
              .width(100)
              .height(100)
              .fillColor(Color.Red)
              .backgroundColor('#E0E0E0')
            Text('Red+Gray').fontSize(12)
          }

          Column({ space: 5 }) {
            Image($r('app.media.heart'))
              .width(100)
              .height(100)
              .fillColor(Color.Blue)
              .backgroundColor('#FFE0E0')
            Text('Blue+Pink').fontSize(12)
          }

          Column({ space: 5 }) {
            Image($r('app.media.testSvg'))
              .width(100)
              .height(100)
              .fillColor(Color.Green)
              .backgroundColor('#E0FFE0')
            Text('Green+Mint').fontSize(12)
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
