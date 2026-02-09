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
 * SVG Complex Layout Example - Demonstrates SVG in complex layout scenarios
 * 
 */
@Entry
@Component
struct svgExample007 {
  @State selectedIdx: number = 0
  @State toggleState: boolean = false

  build() {
    Scroll() {
      Column({ space: 15 }) {
        Text('SVG Complex Layout Example')
          .fontSize(20)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 10 })

        // List item layout
        Text('SVG in List Items')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        ForEach([0, 1, 2, 3, 4], (index: number) => {
          Row({ space: 15 }) {
            Image($r('app.media.testSvg'))
              .width(50)
              .height(50)
              .fillColor(this.selectedIdx === index ? Color.Blue : Color.Gray)

            Column({ space: 5 }) {
              Text('Item ' + (index + 1))
                .fontSize(16)
                .fontWeight(this.selectedIdx === index ? FontWeight.Bold : FontWeight.Normal)
              Text('This is a description for list item')
                .fontSize(14)
                .fontColor(Color.Gray)
            }
            .alignItems(HorizontalAlign.Start)

            Blank()

            Image($r('app.media.svg'))
              .width(30)
              .height(30)
              .fillColor(Color.Green)
          }
          .width('100%')
          .padding(10)
          .backgroundColor(this.selectedIdx === index ? '#F0F0F0' : Color.White)
          .border({ width: { bottom: 1 }, color: Color.LightGray })
          .onClick(() => {
            this.selectedIdx = index
          })
        })

        Divider()

        // Grid layout
        Text('SVG in Grid Layout')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        Grid() {
          ForEach([0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11], (index: number) => {
            GridItem() {
              Column({ space: 5 }) {
                Image($r('app.media.testSvg'))
                  .width(60)
                  .height(60)
                  .fillColor([
                    Color.Red, Color.Orange, Color.Yellow,
                    Color.Green, Color.Cyan, Color.Blue,
                    Color.Purple, Color.Pink, Color.Brown,
                    Color.Gray, Color.Black, Color.White
                  ][index])

                Text('Grid ' + (index + 1))
                  .fontSize(12)
              }
              .padding(10)
              .backgroundColor(Color.White)
              .border({ width: 1, color: Color.LightGray, radius: 8 })
            }
          })
        }
        .columnsTemplate('1fr 1fr 1fr')
        .rowsGap(10)
        .columnsGap(10)
        .width('100%')
        .height(350)

        Divider()

        // Card layout
        Text('SVG in Cards')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        Row({ space: 10 }) {
          Column({ space: 10 }) {
            Image($r('app.media.testSvg'))
              .width(80)
              .height(80)
              .fillColor(Color.Red)

            Text('Card 1')
              .fontSize(14)
              .fontWeight(FontWeight.Medium)

            Text('Description text here')
              .fontSize(12)
              .fontColor(Color.Gray)
          }
          .padding(15)
          .backgroundColor('#F5F5F5')
          .borderRadius(12)
          .width('48%')
          .alignItems(HorizontalAlign.Center)

          Column({ space: 10 }) {
            Image($r('app.media.svg'))
              .width(80)
              .height(80)
              .fillColor(Color.Blue)

            Text('Card 2')
              .fontSize(14)
              .fontWeight(FontWeight.Medium)

            Text('Description text here')
              .fontSize(12)
              .fontColor(Color.Gray)
          }
          .padding(15)
          .backgroundColor('#F5F5F5')
          .borderRadius(12)
          .width('48%')
          .alignItems(HorizontalAlign.Center)
        }
        .width('100%')
        .margin({ bottom: 20 })

        // Tab layout
        Text('SVG in Tabs')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)

        Tabs({ index: this.toggleState ? 1 : 0 }) {
          TabContent() {
            Column({ space: 10 }) {
              Image($r('app.media.testSvg'))
                .width(100)
                .height(100)
                .fillColor(Color.Red)
              Text('Tab 1 Content')
                .fontSize(16)
              Text('This is the first tab')
                .fontSize(14)
                .fontColor(Color.Gray)
            }
            .width('100%')
            .height('100%')
            .justifyContent(FlexAlign.Center)
          }
          .tabBar('Tab 1')

          TabContent() {
            Column({ space: 10 }) {
              Image($r('app.media.svg'))
                .width(100)
                .height(100)
                .fillColor(Color.Blue)
              Text('Tab 2 Content')
                .fontSize(16)
              Text('This is the second tab')
                .fontSize(14)
                .fontColor(Color.Gray)
            }
            .width('100%')
            .height('100%')
            .justifyContent(FlexAlign.Center)
          }
          .tabBar('Tab 2')
        }
        .width('100%')
        .height(200)
        .barMode(BarMode.Fixed)
        .margin({ bottom: 20 })
      }
      .width('100%')
      .padding(10)
    }
    .width('100%')
    .height('100%')
  }
}
