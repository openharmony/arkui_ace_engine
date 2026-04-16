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
 * fillColor 多 SVG 静态图形 ColorMetrics 测试样例 (API 20+)
 * 使用不同 SVG 图形 (笑脸/方块/星圈/心星/五角星/重叠圆) 测试 fillColor + ColorMetrics
 * 基色: 红(0.631,0.0392,0.1294) 绿(0.09,0.662,0.552) 蓝(0,0.29,0.686)
 */
import { ColorMetrics } from '@kit.ArkUI'

@Entry
@Component
struct fillColorDemo07 {
  @State p3Red: ColorMetrics = ColorMetrics.colorWithSpace(ColorSpace.DISPLAY_P3, 0.631, 0.0392, 0.1294)
  @State p3Green: ColorMetrics = ColorMetrics.colorWithSpace(ColorSpace.DISPLAY_P3, 0.09, 0.662, 0.552)
  @State p3Blue: ColorMetrics = ColorMetrics.colorWithSpace(ColorSpace.DISPLAY_P3, 0, 0.29, 0.686)
  @State srgbRed: ColorMetrics = ColorMetrics.colorWithSpace(ColorSpace.SRGB, 0.631, 0.0392, 0.1294)
  @State srgbGreen: ColorMetrics = ColorMetrics.colorWithSpace(ColorSpace.SRGB, 0.09, 0.662, 0.552)
  @State srgbBlue: ColorMetrics = ColorMetrics.colorWithSpace(ColorSpace.SRGB, 0, 0.29, 0.686)

  @State colorArray: (Color | undefined | ColorMetrics | ColorContent)[] = [
    this.p3Red, this.p3Green, this.p3Blue,
    this.srgbRed, this.srgbGreen, this.srgbBlue,
    ColorContent.ORIGIN, Color.Gray, undefined
  ]
  @State colorArrayStr: string[] = [
    'P3 红', 'P3 绿', 'P3 蓝',
    'sRGB 红', 'sRGB 绿', 'sRGB 蓝',
    'ColorContent.ORIGIN', 'Gray', 'undefined'
  ]
  @State arrayIdx: number = 0
  @State svgIdx: number = 0
  @State svgArray: Resource[] = [
    $r('app.media.testSvg'), $r('app.media.heart'), $r('app.media.star'),
    $r('app.media.smiley'), $r('app.media.grid_blocks'), $r('app.media.star_circle'),
    $r('app.media.star_inner'), $r('app.media.pentagon_star'), $r('app.media.overlapping_circles'),
  ]
  @State svgStrArray: string[] = [
    'testSvg', 'heart', 'star', 'smiley', 'grid_blocks', 'star_circle',
    'star_inner', 'pentagon_star', 'overlapping_circles',
  ]

  build() {
    Scroll() {
      Column() {
        Text('多 SVG fillColor 测试')
          .fontSize(22).fontWeight(FontWeight.Bold).fontColor(Color.Black)

        Text('SVG: ' + this.svgStrArray[this.svgIdx] + ' | FillColor: ' + this.colorArrayStr[this.arrayIdx])
          .fontSize(14).margin({ top: 10 })

        Row({ space: 10 }) {
          Button('ChangeSvg')
            .onClick(() => {
              this.svgIdx = (this.svgIdx + 1) % this.svgArray.length
            })
          Button('ChangeFillColor')
            .onClick(() => {
              this.arrayIdx = (this.arrayIdx + 1) % this.colorArray.length
            })
        }

        // 单 SVG 动态切换预览
        Image(this.svgArray[this.svgIdx])
          .width(110).height(110).margin(15)
          .fillColor(this.colorArray[this.arrayIdx])

        Blank().height(20).width('100%')

        // P3 红 - 所有 SVG
        Text('P3 红 (0.631,0.0392,0.1294)')
          .fontSize(16).fontWeight(FontWeight.Medium)
        Row({ space: 10 }) {
          Column() {
            Text('笑脸').fontSize(11)
            Image($r('app.media.smiley')).width(60).height(60)
              .fillColor(this.p3Red).borderRadius(8)
          }
          Column() {
            Text('方块').fontSize(11)
            Image($r('app.media.grid_blocks')).width(60).height(60)
              .fillColor(this.p3Red).borderRadius(8)
          }
          Column() {
            Text('星圈').fontSize(11)
            Image($r('app.media.star_circle')).width(60).height(60)
              .fillColor(this.p3Red).borderRadius(8)
          }
          Column() {
            Text('心星').fontSize(11)
            Image($r('app.media.star_inner')).width(60).height(60)
              .fillColor(this.p3Red).borderRadius(8)
          }
          Column() {
            Text('五角').fontSize(11)
            Image($r('app.media.pentagon_star')).width(60).height(60)
              .fillColor(this.p3Red).borderRadius(8)
          }
        }.width('100%').justifyContent(FlexAlign.Center)

        Blank().height(20).width('100%')

        // P3 绿 - 所有 SVG
        Text('P3 绿 (0.09,0.662,0.552)')
          .fontSize(16).fontWeight(FontWeight.Medium)
        Row({ space: 10 }) {
          Column() {
            Text('笑脸').fontSize(11)
            Image($r('app.media.smiley')).width(60).height(60)
              .fillColor(this.p3Green).borderRadius(8)
          }
          Column() {
            Text('方块').fontSize(11)
            Image($r('app.media.grid_blocks')).width(60).height(60)
              .fillColor(this.p3Green).borderRadius(8)
          }
          Column() {
            Text('星圈').fontSize(11)
            Image($r('app.media.star_circle')).width(60).height(60)
              .fillColor(this.p3Green).borderRadius(8)
          }
          Column() {
            Text('心星').fontSize(11)
            Image($r('app.media.star_inner')).width(60).height(60)
              .fillColor(this.p3Green).borderRadius(8)
          }
          Column() {
            Text('五角').fontSize(11)
            Image($r('app.media.pentagon_star')).width(60).height(60)
              .fillColor(this.p3Green).borderRadius(8)
          }
        }.width('100%').justifyContent(FlexAlign.Center)

        Blank().height(20).width('100%')

        // P3 蓝 - 所有 SVG
        Text('P3 蓝 (0,0.29,0.686)')
          .fontSize(16).fontWeight(FontWeight.Medium)
        Row({ space: 10 }) {
          Column() {
            Text('笑脸').fontSize(11)
            Image($r('app.media.smiley')).width(60).height(60)
              .fillColor(this.p3Blue).borderRadius(8)
          }
          Column() {
            Text('方块').fontSize(11)
            Image($r('app.media.grid_blocks')).width(60).height(60)
              .fillColor(this.p3Blue).borderRadius(8)
          }
          Column() {
            Text('星圈').fontSize(11)
            Image($r('app.media.star_circle')).width(60).height(60)
              .fillColor(this.p3Blue).borderRadius(8)
          }
          Column() {
            Text('心星').fontSize(11)
            Image($r('app.media.star_inner')).width(60).height(60)
              .fillColor(this.p3Blue).borderRadius(8)
          }
          Column() {
            Text('五角').fontSize(11)
            Image($r('app.media.pentagon_star')).width(60).height(60)
              .fillColor(this.p3Blue).borderRadius(8)
          }
        }.width('100%').justifyContent(FlexAlign.Center)

        Blank().height(20).width('100%')

        // 重叠圆 - 特殊多色测试
        Text('重叠圆 SVG (多填充色)')
          .fontSize(16).fontWeight(FontWeight.Medium)
        Row({ space: 15 }) {
          Column() {
            Text('P3 红').fontSize(11)
            Image($r('app.media.overlapping_circles')).width(80).height(80)
              .fillColor(this.p3Red).borderRadius(8)
          }
          Column() {
            Text('P3 绿').fontSize(11)
            Image($r('app.media.overlapping_circles')).width(80).height(80)
              .fillColor(this.p3Green).borderRadius(8)
          }
          Column() {
            Text('P3 蓝').fontSize(11)
            Image($r('app.media.overlapping_circles')).width(80).height(80)
              .fillColor(this.p3Blue).borderRadius(8)
          }
          Column() {
            Text('ORIGIN').fontSize(11)
            Image($r('app.media.overlapping_circles')).width(80).height(80)
              .fillColor(ColorContent.ORIGIN).borderRadius(8)
          }
        }.width('100%').justifyContent(FlexAlign.Center)

        Blank().height(20).width('100%')

        // 动态切换区 - 所有 SVG 一起变色
        Text('动态切换 - 所有 SVG 同步变色')
          .fontSize(16).fontWeight(FontWeight.Medium)
        Grid() {
          GridItem() {
            Column() {
              Image($r('app.media.smiley')).width(70).height(70)
                .fillColor(this.colorArray[this.arrayIdx]).borderRadius(8)
              Text('笑脸').fontSize(10)
            }
          }
          GridItem() {
            Column() {
              Image($r('app.media.grid_blocks')).width(70).height(70)
                .fillColor(this.colorArray[this.arrayIdx]).borderRadius(8)
              Text('方块').fontSize(10)
            }
          }
          GridItem() {
            Column() {
              Image($r('app.media.star_circle')).width(70).height(70)
                .fillColor(this.colorArray[this.arrayIdx]).borderRadius(8)
              Text('星圈').fontSize(10)
            }
          }
          GridItem() {
            Column() {
              Image($r('app.media.star_inner')).width(70).height(70)
                .fillColor(this.colorArray[this.arrayIdx]).borderRadius(8)
              Text('心星').fontSize(10)
            }
          }
          GridItem() {
            Column() {
              Image($r('app.media.pentagon_star')).width(70).height(70)
                .fillColor(this.colorArray[this.arrayIdx]).borderRadius(8)
              Text('五角').fontSize(10)
            }
          }
          GridItem() {
            Column() {
              Image($r('app.media.overlapping_circles')).width(70).height(70)
                .fillColor(this.colorArray[this.arrayIdx]).borderRadius(8)
              Text('重叠圆').fontSize(10)
            }
          }
          GridItem() {
            Column() {
              Image($r('app.media.heart')).width(70).height(70)
                .fillColor(this.colorArray[this.arrayIdx]).borderRadius(8)
              Text('爱心').fontSize(10)
            }
          }
          GridItem() {
            Column() {
              Image($r('app.media.star')).width(70).height(70)
                .fillColor(this.colorArray[this.arrayIdx]).borderRadius(8)
              Text('星星').fontSize(10)
            }
          }
          GridItem() {
            Column() {
              Image($r('app.media.testSvg')).width(70).height(70)
                .fillColor(this.colorArray[this.arrayIdx]).borderRadius(8)
              Text('方块脸').fontSize(10)
            }
          }
        }
        .columnsTemplate('1fr 1fr 1fr')
        .rowsGap(10)
        .columnsGap(10)
        .width('100%')
      }
      .width('100%')
      .padding({ left: 15, right: 15, top: 10, bottom: 20 })
    }
    .width('100%').height('100%').backgroundColor(Color.White)
  }
}
