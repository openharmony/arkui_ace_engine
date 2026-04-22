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
 * fillColor HDR ColorMetrics 测试样例 (API 24+, @systemapi)
 * 覆盖 createHDRColor / createHDRColorWithLinearExposure / createHDRColorWithLogExposure
 * 色域: SRGB, DISPLAY_P3, BT2020
 * 基色: 红(0.631,0.0392,0.1294) 绿(0.09,0.662,0.552) 蓝(0,0.29,0.686)
 */
import { ColorMetrics } from '@kit.ArkUI'

@Entry
@Component
struct fillColorDemo05 {
  // createHDRColor - P3 色域 RGB>1.0
  @State hdrP3Red: ColorMetrics = ColorMetrics.createHDRColor(ColorSpace.DISPLAY_P3, 1.5, 0, 0)
  @State hdrP3Green: ColorMetrics = ColorMetrics.createHDRColor(ColorSpace.DISPLAY_P3, 0, 1.5, 0)
  @State hdrP3Blue: ColorMetrics = ColorMetrics.createHDRColor(ColorSpace.DISPLAY_P3, 0, 0, 1.5)
  // createHDRColor - BT2020 色域
  @State hdrBtRed: ColorMetrics = ColorMetrics.createHDRColor(2 as ColorSpace, 1.262, 0.0784, 0.2588)
  @State hdrBtGreen: ColorMetrics = ColorMetrics.createHDRColor(2 as ColorSpace, 0.18, 1.324, 1.104)
  @State hdrBtBlue: ColorMetrics = ColorMetrics.createHDRColor(2 as ColorSpace, 0, 0.58, 1.372)
  // createHDRColorWithLinearExposure - P3
  @State linearP3Red: ColorMetrics =
    ColorMetrics.createHDRColorWithLinearExposure(2.0, ColorSpace.DISPLAY_P3, 0.631, 0.0392, 0.1294)
  @State linearP3Green: ColorMetrics =
    ColorMetrics.createHDRColorWithLinearExposure(2.0, ColorSpace.DISPLAY_P3, 0.09, 0.662, 0.552)
  @State linearP3Blue: ColorMetrics =
    ColorMetrics.createHDRColorWithLinearExposure(2.0, ColorSpace.DISPLAY_P3, 0, 0.29, 0.686)
  // createHDRColorWithLinearExposure - BT2020
  @State linearBtRed: ColorMetrics =
    ColorMetrics.createHDRColorWithLinearExposure(3.0, 2 as ColorSpace, 0.631, 0.0392, 0.1294)
  @State linearBtGreen: ColorMetrics =
    ColorMetrics.createHDRColorWithLinearExposure(3.0, 2 as ColorSpace, 0.09, 0.662, 0.552)
  @State linearBtBlue: ColorMetrics =
    ColorMetrics.createHDRColorWithLinearExposure(3.0, 2 as ColorSpace, 0, 0.29, 0.686)
  // createHDRColorWithLogExposure - P3
  @State logP3Red: ColorMetrics =
    ColorMetrics.createHDRColorWithLogExposure(1.0, ColorSpace.DISPLAY_P3, 0.631, 0.0392, 0.1294)
  @State logP3Green: ColorMetrics =
    ColorMetrics.createHDRColorWithLogExposure(1.0, ColorSpace.DISPLAY_P3, 0.09, 0.662, 0.552)
  @State logP3Blue: ColorMetrics =
    ColorMetrics.createHDRColorWithLogExposure(1.0, ColorSpace.DISPLAY_P3, 0, 0.29, 0.686)
  // createHDRColorWithLogExposure - BT2020
  @State logBtRed: ColorMetrics =
    ColorMetrics.createHDRColorWithLogExposure(2.0, 2 as ColorSpace, 0.631, 0.0392, 0.1294)
  @State logBtGreen: ColorMetrics =
    ColorMetrics.createHDRColorWithLogExposure(2.0, 2 as ColorSpace, 0.09, 0.662, 0.552)
  @State logBtBlue: ColorMetrics =
    ColorMetrics.createHDRColorWithLogExposure(2.0, 2 as ColorSpace, 0, 0.29, 0.686)
  // SDR 对比色
  @State sdrP3Red: ColorMetrics = ColorMetrics.colorWithSpace(ColorSpace.DISPLAY_P3, 0.631, 0.0392, 0.1294)

  @State colorArray: (Color | undefined | ColorMetrics | ColorContent)[] = [
    this.hdrP3Red, this.hdrP3Green, this.hdrP3Blue,
    this.hdrBtRed, this.hdrBtGreen, this.hdrBtBlue,
    this.linearP3Red, this.linearP3Green, this.linearP3Blue,
    this.linearBtRed, this.linearBtGreen, this.linearBtBlue,
    this.logP3Red, this.logP3Green, this.logP3Blue,
    this.logBtRed, this.logBtGreen, this.logBtBlue,
    ColorContent.ORIGIN, undefined
  ]
  @State colorArrayStr: string[] = [
    'HDR P3 红 (R=1.5)', 'HDR P3 绿 (G=1.5)', 'HDR P3 蓝 (B=1.5)',
    'HDR BT2020 红 (x2)', 'HDR BT2020 绿 (x2)', 'HDR BT2020 蓝 (x2)',
    'LinearExp P3 红 x2', 'LinearExp P3 绿 x2', 'LinearExp P3 蓝 x2',
    'LinearExp BT2020 红 x3', 'LinearExp BT2020 绿 x3', 'LinearExp BT2020 蓝 x3',
    'LogExp P3 红 +1stop', 'LogExp P3 绿 +1stop', 'LogExp P3 蓝 +1stop',
    'LogExp BT2020 红 +2stop', 'LogExp BT2020 绿 +2stop', 'LogExp BT2020 蓝 +2stop',
    'ColorContent.ORIGIN', 'undefined'
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
        Text('fillColor HDR ColorMetrics 测试')
          .fontSize(22).fontWeight(FontWeight.Bold).fontColor(Color.Black)

        Text('API 24+ @systemapi | 3种 HDR 创建方式')
          .fontSize(13).fontColor('#666666').margin({ top: 5 })

        Text('SVG: ' + this.svgStrArray[this.svgIdx] + ' | FillColor: ' + this.colorArrayStr[this.arrayIdx])
          .fontSize(14).margin({ top: 10 })

        Image(this.svgArray[this.svgIdx])
          .width(110).height(110).margin(15)
          .fillColor(this.colorArray[this.arrayIdx])

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

        Blank().height(30).width('100%')

        // 1. createHDRColor
        Text('1. createHDRColor (RGB>1.0)')
          .fontSize(16).fontWeight(FontWeight.Medium)
        Row({ space: 12 }) {
          Column() {
            Text('HDR P3 红').fontSize(11)
            Image(this.svgArray[this.svgIdx]).width(75).height(75)
              .fillColor(this.hdrP3Red).borderRadius(8)
          }
          Column() {
            Text('HDR P3 绿').fontSize(11)
            Image(this.svgArray[this.svgIdx]).width(75).height(75)
              .fillColor(this.hdrP3Green).borderRadius(8)
          }
          Column() {
            Text('HDR P3 蓝').fontSize(11)
            Image(this.svgArray[this.svgIdx]).width(75).height(75)
              .fillColor(this.hdrP3Blue).borderRadius(8)
          }
          Column() {
            Text('HDR BT 红').fontSize(11)
            Image(this.svgArray[this.svgIdx]).width(75).height(75)
              .fillColor(this.hdrBtRed).borderRadius(8)
          }
        }.width('100%').justifyContent(FlexAlign.Center)

        Blank().height(20).width('100%')

        // 2. createHDRColorWithLinearExposure
        Text('2. createHDRColorWithLinearExposure')
          .fontSize(16).fontWeight(FontWeight.Medium)
        Row({ space: 12 }) {
          Column() {
            Text('Linear P3 红 x2').fontSize(11)
            Image(this.svgArray[this.svgIdx]).width(75).height(75)
              .fillColor(this.linearP3Red).borderRadius(8)
          }
          Column() {
            Text('Linear P3 绿 x2').fontSize(11)
            Image(this.svgArray[this.svgIdx]).width(75).height(75)
              .fillColor(this.linearP3Green).borderRadius(8)
          }
          Column() {
            Text('Linear BT 红 x3').fontSize(11)
            Image(this.svgArray[this.svgIdx]).width(75).height(75)
              .fillColor(this.linearBtRed).borderRadius(8)
          }
          Column() {
            Text('Linear BT 蓝 x3').fontSize(11)
            Image(this.svgArray[this.svgIdx]).width(75).height(75)
              .fillColor(this.linearBtBlue).borderRadius(8)
          }
        }.width('100%').justifyContent(FlexAlign.Center)

        Blank().height(20).width('100%')

        // 3. createHDRColorWithLogExposure
        Text('3. createHDRColorWithLogExposure')
          .fontSize(16).fontWeight(FontWeight.Medium)
        Row({ space: 12 }) {
          Column() {
            Text('Log P3 红 +1s').fontSize(11)
            Image(this.svgArray[this.svgIdx]).width(75).height(75)
              .fillColor(this.logP3Red).borderRadius(8)
          }
          Column() {
            Text('Log P3 绿 +1s').fontSize(11)
            Image(this.svgArray[this.svgIdx]).width(75).height(75)
              .fillColor(this.logP3Green).borderRadius(8)
          }
          Column() {
            Text('Log BT 红 +2s').fontSize(11)
            Image(this.svgArray[this.svgIdx]).width(75).height(75)
              .fillColor(this.logBtRed).borderRadius(8)
          }
          Column() {
            Text('Log BT 蓝 +2s').fontSize(11)
            Image(this.svgArray[this.svgIdx]).width(75).height(75)
              .fillColor(this.logBtBlue).borderRadius(8)
          }
        }.width('100%').justifyContent(FlexAlign.Center)

        Blank().height(20).width('100%')

        // HDR vs SDR 对比
        Text('HDR vs SDR 对比')
          .fontSize(16).fontWeight(FontWeight.Medium)
        Row({ space: 20 }) {
          Column() {
            Text('SDR P3 红').fontSize(12)
            Image(this.svgArray[this.svgIdx]).width(90).height(90)
              .fillColor(this.sdrP3Red).borderRadius(10)
            Text('isHDR: ' + this.sdrP3Red.isHDR()).fontSize(11).fontColor('#666666')
          }
          Column() {
            Text('HDR P3 红').fontSize(12)
            Image(this.svgArray[this.svgIdx]).width(90).height(90)
              .fillColor(this.hdrP3Red).borderRadius(10)
            Text('isHDR: ' + this.hdrP3Red.isHDR()).fontSize(11).fontColor('#666666')
          }
        }.width('100%').justifyContent(FlexAlign.Center)

        Blank().height(20).width('100%')

        // API 查询验证
        Text('API 查询验证')
          .fontSize(16).fontWeight(FontWeight.Medium)
        Text('hdrP3Red colorSpace: ' + this.hdrP3Red.getColorSpace())
          .fontSize(13).margin({ top: 5 })
        Text('hdrP3Red isHDR: ' + this.hdrP3Red.isHDR())
          .fontSize(13)
        Text('hdrP3Red getRedValue: ' + this.hdrP3Red.getRedValue())
          .fontSize(13)
        Text('linearBtRed colorSpace: ' + this.linearBtRed.getColorSpace())
          .fontSize(13)
        Text('linearBtRed isHDR: ' + this.linearBtRed.isHDR())
          .fontSize(13)
        Text('logBtBlue colorSpace: ' + this.logBtBlue.getColorSpace())
          .fontSize(13)

        Text('注意: HDR ColorMetrics 为 @systemapi (API 24+)，需要支持 HDR 显示的设备')
          .fontSize(12).fontColor('#999999').margin({ top: 20, bottom: 20 })
      }
      .width('100%')
      .padding({ left: 15, right: 15, top: 10, bottom: 20 })
    }
    .width('100%').height('100%').backgroundColor(Color.White)
  }
}
