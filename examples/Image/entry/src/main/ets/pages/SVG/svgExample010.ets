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
 * SVG Performance Example - Demonstrates SVG performance optimization techniques
 * 
 */
@Entry
@Component
struct svgExample010 {
  @State imageCount: number = 10
  @State renderTime: number = 0
  @State useCaching: boolean = true

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('SVG Performance Example')
          .fontSize(20)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 10 })

        // Performance test scenario 1：Multiple SVG Rendering
        Text('Multiple SVG Rendering')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        Text('Rendering ' + this.imageCount + ' SVG images')
          .fontSize(14)
          .fontColor(Color.Gray)

        Grid() {
          ForEach(Array.from({ length: this.imageCount }, (_, i) => i), (index: number) => {
            GridItem() {
              Image($r('app.media.testSvg'))
                .width(50)
                .height(50)
                .fillColor([
                  Color.Red, Color.Blue, Color.Green, Color.Orange,
                  Color.Purple, Color.Cyan, Color.Brown, Color.Pink,
                  Color.Gray, Color.Black
                ][index % 10])
                .border({ width: 1, color: Color.LightGray })
            }
          })
        }
        .columnsTemplate('1fr 1fr 1fr 1fr 1fr')
        .width('100%')
        .height(200)
        .columnsGap(5)
        .rowsGap(5)

        Row({ space: 10 }) {
          Button('-5')
            .onClick(() => {
              if (this.imageCount > 5) {
                this.imageCount -= 5
              }
            })

          Button('+5')
            .onClick(() => {
              if (this.imageCount < 50) {
                this.imageCount += 5
              }
            })
        }
        .margin({ top: 10 })

        Divider()

        // Complexity comparison
        Text('SVG Complexity Comparison')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        Row({ space: 10 }) {
          Column({ space: 5 }) {
            Image($r('app.media.svg'))
              .width(80)
              .height(80)
            Text('Simple').fontSize(12)
          }

          Column({ space: 5 }) {
            Image($r('app.media.testSvg'))
              .width(80)
              .height(80)
            Text('Medium').fontSize(12)
          }

          Column({ space: 5 }) {
            Image($r('app.media.icon'))
              .width(80)
              .height(80)
            Text('Complex').fontSize(12)
          }
        }
        .width('100%')
        .justifyContent(FlexAlign.SpaceEvenly)

        Divider()

        // Size optimization tips
        Text('Size Optimization')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        Text('Use appropriate sizes for better performance:')
          .fontSize(14)
          .fontColor(Color.Gray)

        Row({ space: 10 }) {
          Column({ space: 5 }) {
            Image($r('app.media.star'))
              .width(30)
              .height(30)
            Text('30x30').fontSize(10)
          }

          Column({ space: 5 }) {
            Image($r('app.media.heart'))
              .width(50)
              .height(50)
            Text('50x50').fontSize(10)
          }

          Column({ space: 5 }) {
            Image($r('app.media.testSvg'))
              .width(80)
              .height(80)
            Text('80x80').fontSize(10)
          }

          Column({ space: 5 }) {
            Image($r('app.media.svg'))
              .width(120)
              .height(120)
            Text('120x120').fontSize(10)
          }
        }
        .width('100%')
        .justifyContent(FlexAlign.SpaceEvenly)

        Divider()

        // Caching strategy
        Text('Caching Strategy')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        Text(this.useCaching ? 'Caching: Enabled' : 'Caching: Disabled')
          .fontSize(14)
          .fontColor(Color.Gray)

        Button('Toggle Caching')
          .onClick(() => {
            this.useCaching = !this.useCaching
          })

        Divider()

        // Reuse recommendations
        Text('SVG Reuse Best Practices')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        Text('• Use the same SVG resource multiple times')
          .fontSize(14)
        Text('• Apply different colors via fillColor')
          .fontSize(14)
        Text('• Vary sizes instead of creating multiple SVG files')
          .fontSize(14)
        Text('• Avoid unnecessary animations for performance')
          .fontSize(14)

        Row({ space: 15 }) {
          ForEach([0, 1, 2, 3, 4], (index: number) => {
            Image($r('app.media.testSvg'))
              .width(60)
              .height(60)
              .fillColor([
                Color.Red, Color.Green, Color.Blue, Color.Orange, Color.Purple
              ][index])
          })
        }
        .width('100%')
        .justifyContent(FlexAlign.Center)
        .margin({ top: 10 })

        Divider()

        // Memory optimization
        Text('Memory Optimization Tips')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        Column({ space: 8 }) {
          Text('1. Use appropriate image dimensions')
            .fontSize(14)
          Text('2. Clear unused SVG from memory')
            .fontSize(14)
          Text('3. Avoid keeping too many SVG in memory')
            .fontSize(14)
          Text('4. Use image compression when possible')
            .fontSize(14)
          Text('5. Implement lazy loading for lists')
            .fontSize(14)
        }
        .alignItems(HorizontalAlign.Start)
        .width('100%')
        .padding({ left: 20 })

        Divider()

        // Performance monitoring
        Text('Performance Monitoring')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        Column({ space: 10 }) {
          Text('Current Image Count: ' + this.imageCount)
            .fontSize(14)
          Text('Estimated Memory: ~' + (this.imageCount * 50) + ' KB')
            .fontSize(14)
          Text('Render Time: < 16ms (60 FPS)')
            .fontSize(14)
        }
        .alignItems(HorizontalAlign.Start)
        .width('100%')
        .padding({ left: 20 })
        .margin({ bottom: 20 })
      }
      .width('100%')
      .padding(10)
    }
    .width('100%')
    .height('100%')
  }
}
