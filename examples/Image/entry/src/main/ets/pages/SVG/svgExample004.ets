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
 * SVG ObjectFit Example - Demonstrates SVG display with different objectFit modes
 * 
 */
@Entry
@Component
struct svgExample004 {
  @State fitMode: ImageFit = ImageFit.Cover
  @State fitName: string = 'Cover'

  build() {
    Column({ space: 15 }) {
      Text('SVG ObjectFit Example')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 20, bottom: 10 })

      Text('Current mode: ' + this.fitName)
        .fontSize(16)

      // SVG with fixed container size
      Image($r('app.media.testSvg'))
        .width(200)
        .height(150)
        .objectFit(this.fitMode)
        .border({ width: 2, color: Color.Blue })
        .backgroundColor(Color.LightGray)
        .margin(15)

      // Switch between different fit modes
      Row({ space: 10 }) {
        Button('Cover')
          .onClick(() => {
            this.fitMode = ImageFit.Cover
            this.fitName = 'Cover'
          })

        Button('Contain')
          .onClick(() => {
            this.fitMode = ImageFit.Contain
            this.fitName = 'Contain'
          })

        Button('Fill')
          .onClick(() => {
            this.fitMode = ImageFit.Fill
            this.fitName = 'Fill'
          })
      }
      .margin({ bottom: 10 })

      Row({ space: 10 }) {
        Button('None')
          .onClick(() => {
            this.fitMode = ImageFit.None
            this.fitName = 'None'
          })

        Button('ScaleDown')
          .onClick(() => {
            this.fitMode = ImageFit.ScaleDown
            this.fitName = 'ScaleDown'
          })
      }
      .margin({ bottom: 20 })

      // All modes comparison
      Text('All modes comparison')
        .fontSize(16)
        .fontWeight(FontWeight.Medium)

      Grid() {
        GridItem() {
          Column({ space: 5 }) {
            Image($r('app.media.testSvg'))
              .width(100)
              .height(80)
              .objectFit(ImageFit.Cover)
              .border({ width: 1, color: Color.Gray })
            Text('Cover').fontSize(12)
          }
        }

        GridItem() {
          Column({ space: 5 }) {
            Image($r('app.media.testSvg'))
              .width(100)
              .height(80)
              .objectFit(ImageFit.Contain)
              .border({ width: 1, color: Color.Gray })
            Text('Contain').fontSize(12)
          }
        }

        GridItem() {
          Column({ space: 5 }) {
            Image($r('app.media.testSvg'))
              .width(100)
              .height(80)
              .objectFit(ImageFit.Fill)
              .border({ width: 1, color: Color.Gray })
            Text('Fill').fontSize(12)
          }
        }

        GridItem() {
          Column({ space: 5 }) {
            Image($r('app.media.testSvg'))
              .width(100)
              .height(80)
              .objectFit(ImageFit.None)
              .border({ width: 1, color: Color.Gray })
            Text('None').fontSize(12)
          }
        }

        GridItem() {
          Column({ space: 5 }) {
            Image($r('app.media.testSvg'))
              .width(100)
              .height(80)
              .objectFit(ImageFit.ScaleDown)
              .border({ width: 1, color: Color.Gray })
            Text('ScaleDown').fontSize(12)
          }
        }
      }
      .columnsTemplate('1fr 1fr')
      .rowsTemplate('1fr 1fr')
      .width('100%')
      .height(250)
      .margin({ bottom: 20 })
    }
    .width('100%')
    .height('100%')
    .padding(10)
  }
}
