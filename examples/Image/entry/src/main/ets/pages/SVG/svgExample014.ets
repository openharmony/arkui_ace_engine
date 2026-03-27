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
 * SVG Image Loading Example - Demonstrates SVG loading methods and states
 * 
 */
@Entry
@Component
struct svgExample014 {
  @State loadState: string = 'Idle'
  @State imageWidth: number = 150
  @State imageHeight: number = 150
  @State currentSource: string = 'Resource'

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('SVG Image Loading Example')
          .fontSize(20)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 10 })

        // Load from resources
        Text('Load from Resources ($r)')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        Image($r('app.media.testSvg'))
          .width(this.imageWidth)
          .height(this.imageHeight)
          .border({ width: 1, color: Color.Gray })
          .onComplete(() => {
            this.loadState = 'Loaded from resources'
          })
          .onError(() => {
            this.loadState = 'Error loading from resources'
          })

        Text(this.loadState)
          .fontSize(14)
          .fontColor(Color.Gray)

        Divider()

        // Load at different sizes
        Text('Different Sizes')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        Row({ space: 15 }) {
          Column({ space: 5 }) {
            Image($r('app.media.svg'))
              .width(60)
              .height(60)
              .border({ width: 1, color: Color.Gray })
            Text('60x60').fontSize(12)
          }

          Column({ space: 5 }) {
            Image($r('app.media.icon'))
              .width(100)
              .height(100)
              .border({ width: 1, color: Color.Gray })
            Text('100x100').fontSize(12)
          }

          Column({ space: 5 }) {
            Image($r('app.media.star'))
              .width(140)
              .height(140)
              .border({ width: 1, color: Color.Gray })
            Text('140x140').fontSize(12)
          }
        }
        .width('100%')
        .justifyContent(FlexAlign.SpaceEvenly)

        Divider()

        // Load with aspect ratio
        Text('Aspect Ratio Loading')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        Row({ space: 15 }) {
          Column({ space: 5 }) {
            Image($r('app.media.heart'))
              .width(120)
              .aspectRatio(1)
              .objectFit(ImageFit.Contain)
              .border({ width: 1, color: Color.Gray })
            Text('1:1').fontSize(12)
          }

          Column({ space: 5 }) {
            Image($r('app.media.testSvg'))
              .width(150)
              .aspectRatio(4 / 3)
              .objectFit(ImageFit.Contain)
              .border({ width: 1, color: Color.Gray })
            Text('4:3').fontSize(12)
          }

          Column({ space: 5 }) {
            Image($r('app.media.svg'))
              .width(150)
              .aspectRatio(16 / 9)
              .objectFit(ImageFit.Contain)
              .border({ width: 1, color: Color.Gray })
            Text('16:9').fontSize(12)
          }
        }
        .width('100%')
        .justifyContent(FlexAlign.SpaceEvenly)

        Divider()

        // Synchronous and asynchronous loading
        Text('Loading States')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        @State loading1: boolean = false
        @State loading2: boolean = false
        @State loading3: boolean = false

        Row({ space: 15 }) {
          Column({ space: 5 }) {
            if (loading1) {
              LoadingProgress()
                .width(50)
                .height(50)
            } else {
              Image($r('app.media.icon'))
                .width(80)
                .height(80)
                .border({ width: 1, color: Color.Gray })
                .onComplete(() => {
                  this.loading1 = false
                })
            }
            Text('Sync Load').fontSize(12)
          }

          Column({ space: 5 }) {
            if (loading2) {
              LoadingProgress()
                .width(50)
                .height(50)
            } else {
              Image($r('app.media.star'))
                .width(80)
                .height(80)
                .border({ width: 1, color: Color.Gray })
                .onComplete(() => {
                  this.loading2 = false
                })
            }
            Text('Async Load').fontSize(12)
          }

          Column({ space: 5 }) {
            if (loading3) {
              LoadingProgress()
                .width(50)
                .height(50)
            } else {
              Image($r('app.media.heart'))
                .width(80)
                .height(80)
                .border({ width: 1, color: Color.Gray })
                .onComplete(() => {
                  this.loading3 = false
                })
            }
            Text('Cached').fontSize(12)
          }
        }
        .width('100%')
        .justifyContent(FlexAlign.SpaceEvenly)

        Row({ space: 10 }) {
          Button('Load 1')
            .onClick(() => {
              this.loading1 = true
            })
          Button('Load 2')
            .onClick(() => {
              this.loading2 = true
            })
          Button('Load 3')
            .onClick(() => {
              this.loading3 = true
            })
        }
        .width('100%')
        .justifyContent(FlexAlign.Center)

        Divider()

        // Preloading strategy
        Text('Preloading Strategy')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        Column({ space: 10 }) {
          ForEach([0, 1, 2], (index: number) => {
            Row({ space: 10 }) {
              Image($r('app.media.testSvg'))
                .width(50)
                .height(50)
                .fillColor([Color.Red, Color.Green, Color.Blue][index])
                .border({ width: 1, color: Color.Gray })

              Text('Preloaded SVG ' + (index + 1))
                .fontSize(14)
                .margin({ left: 10 })
            }
            .width('100%')
            .padding(10)
            .backgroundColor('#F5F5F5')
            .borderRadius(8)
          })
        }
        .width('100%')

        Divider()

        // Loading optimization
        Text('Loading Optimization Tips')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        Column({ space: 8 }) {
          Text('1. Use appropriate SVG file sizes')
            .fontSize(14)
          Text('2. Implement lazy loading for long lists')
            .fontSize(14)
          Text('3. Cache frequently used SVG files')
            .fontSize(14)
          Text('4. Use loading placeholders')
            .fontSize(14)
          Text('5. Handle loading errors gracefully')
            .fontSize(14)
          Text('6. Optimize SVG code complexity')
            .fontSize(14)
          Text('7. Use compression when possible')
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
