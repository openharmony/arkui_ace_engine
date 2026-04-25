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
 * fillColor BT2020 色域测试样例 (API 24+, @systemapi)
 * ColorSpace.BT2020 = 2，使用 ColorMetrics.colorWithSpace 在 BT2020 色域下设置 fillColor。
 * 基色: 红(0.631,0.0392,0.1294) 绿(0.09,0.662,0.552) 蓝(0,0.29,0.686)
 * 对比 BT2020、P3、sRGB 三种色域下同色值的视觉差异。
 */
import { ColorMetrics } from '@kit.ArkUI'

@Entry
@Component
struct fillColorDemo04 {
  // BT2020 色域基色 (ColorSpace.BT2020 = 2, API 24+, @systemapi)
  @State bt2020Red: ColorMetrics = ColorMetrics.colorWithSpace(2 as ColorSpace, 0.631, 0.0392, 0.1294)
  @State bt2020Green: ColorMetrics = ColorMetrics.colorWithSpace(2 as ColorSpace, 0.09, 0.662, 0.552)
  @State bt2020Blue: ColorMetrics = ColorMetrics.colorWithSpace(2 as ColorSpace, 0, 0.29, 0.686)
  @State bt2020RedAlpha: ColorMetrics = ColorMetrics.colorWithSpace(2 as ColorSpace, 0.631, 0.0392, 0.1294, 0.5)
  @State bt2020GreenAlpha: ColorMetrics = ColorMetrics.colorWithSpace(2 as ColorSpace, 0.09, 0.662, 0.552, 0.5)
  @State bt2020BlueAlpha: ColorMetrics = ColorMetrics.colorWithSpace(2 as ColorSpace, 0, 0.29, 0.686, 0.5)
  // P3 对比色
  @State p3Red: ColorMetrics = ColorMetrics.colorWithSpace(ColorSpace.DISPLAY_P3, 0.631, 0.0392, 0.1294)
  @State p3Green: ColorMetrics = ColorMetrics.colorWithSpace(ColorSpace.DISPLAY_P3, 0.09, 0.662, 0.552)
  @State p3Blue: ColorMetrics = ColorMetrics.colorWithSpace(ColorSpace.DISPLAY_P3, 0, 0.29, 0.686)
  // sRGB 对比色
  @State srgbRed: ColorMetrics = ColorMetrics.colorWithSpace(ColorSpace.SRGB, 0.631, 0.0392, 0.1294)
  @State srgbGreen: ColorMetrics = ColorMetrics.colorWithSpace(ColorSpace.SRGB, 0.09, 0.662, 0.552)
  @State srgbBlue: ColorMetrics = ColorMetrics.colorWithSpace(ColorSpace.SRGB, 0, 0.29, 0.686)

  @State colorArray: (Color | undefined | ColorMetrics | ColorContent)[] = [
    this.bt2020Red, this.bt2020Green, this.bt2020Blue,
    this.bt2020RedAlpha, this.bt2020GreenAlpha, this.bt2020BlueAlpha,
    ColorContent.ORIGIN, Color.Gray, undefined
  ]
  @State colorArrayStr: string[] = [
    'BT2020 红 (0.631,0.0392,0.1294)', 'BT2020 绿 (0.09,0.662,0.552)', 'BT2020 蓝 (0,0.29,0.686)',
    'BT2020 红 alpha:0.5', 'BT2020 绿 alpha:0.5', 'BT2020 蓝 alpha:0.5',
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
        Text('fillColor BT2020 色域测试')
          .fontSize(22).fontWeight(FontWeight.Bold).fontColor(Color.Black)

        Text('ColorSpace.BT2020 = 2 (API 24+, @systemapi)')
          .fontSize(13).fontColor('#666666').margin({ top: 5 })

        Text('SVG: ' + this.svgStrArray[this.svgIdx] + ' | FillColor: ' + this.colorArrayStr[this.arrayIdx])
          .fontSize(14).margin({ top: 10 })

        // 动态切换区 - 图源 + 颜色均可切换
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

        // 三色域红色对比
        Text('三色域红色对比 (同色值)')
          .fontSize(16).fontWeight(FontWeight.Medium)
        Row({ space: 12 }) {
          Column() {
            Text('BT2020').fontSize(12).fontColor(Color.Gray)
            Image(this.svgArray[this.svgIdx]).width(85).height(85)
              .fillColor(this.bt2020Red).borderRadius(10)
          }
          Column() {
            Text('P3').fontSize(12).fontColor(Color.Gray)
            Image(this.svgArray[this.svgIdx]).width(85).height(85)
              .fillColor(this.p3Red).borderRadius(10)
          }
          Column() {
            Text('sRGB').fontSize(12).fontColor(Color.Gray)
            Image(this.svgArray[this.svgIdx]).width(85).height(85)
              .fillColor(this.srgbRed).borderRadius(10)
          }
        }.width('100%').justifyContent(FlexAlign.Center)

        Blank().height(20).width('100%')

        // 三色域绿色对比
        Text('三色域绿色对比 (同色值)')
          .fontSize(16).fontWeight(FontWeight.Medium)
        Row({ space: 12 }) {
          Column() {
            Text('BT2020').fontSize(12).fontColor(Color.Gray)
            Image(this.svgArray[this.svgIdx]).width(85).height(85)
              .fillColor(this.bt2020Green).borderRadius(10)
          }
          Column() {
            Text('P3').fontSize(12).fontColor(Color.Gray)
            Image(this.svgArray[this.svgIdx]).width(85).height(85)
              .fillColor(this.p3Green).borderRadius(10)
          }
          Column() {
            Text('sRGB').fontSize(12).fontColor(Color.Gray)
            Image(this.svgArray[this.svgIdx]).width(85).height(85)
              .fillColor(this.srgbGreen).borderRadius(10)
          }
        }.width('100%').justifyContent(FlexAlign.Center)

        Blank().height(20).width('100%')

        // 三色域蓝色对比
        Text('三色域蓝色对比 (同色值)')
          .fontSize(16).fontWeight(FontWeight.Medium)
        Row({ space: 12 }) {
          Column() {
            Text('BT2020').fontSize(12).fontColor(Color.Gray)
            Image(this.svgArray[this.svgIdx]).width(85).height(85)
              .fillColor(this.bt2020Blue).borderRadius(10)
          }
          Column() {
            Text('P3').fontSize(12).fontColor(Color.Gray)
            Image(this.svgArray[this.svgIdx]).width(85).height(85)
              .fillColor(this.p3Blue).borderRadius(10)
          }
          Column() {
            Text('sRGB').fontSize(12).fontColor(Color.Gray)
            Image(this.svgArray[this.svgIdx]).width(85).height(85)
              .fillColor(this.srgbBlue).borderRadius(10)
          }
        }.width('100%').justifyContent(FlexAlign.Center)

        Blank().height(20).width('100%')

        // BT2020 半透明
        Text('BT2020 半透明 (alpha=0.5)')
          .fontSize(16).fontWeight(FontWeight.Medium)
        Row({ space: 15 }) {
          Column() {
            Text('红').fontSize(12)
            Image(this.svgArray[this.svgIdx]).width(80).height(80)
              .fillColor(this.bt2020RedAlpha).borderRadius(8)
          }
          Column() {
            Text('绿').fontSize(12)
            Image(this.svgArray[this.svgIdx]).width(80).height(80)
              .fillColor(this.bt2020GreenAlpha).borderRadius(8)
          }
          Column() {
            Text('蓝').fontSize(12)
            Image(this.svgArray[this.svgIdx]).width(80).height(80)
              .fillColor(this.bt2020BlueAlpha).borderRadius(8)
          }
        }.width('100%').justifyContent(FlexAlign.Center)

        Blank().height(20).width('100%')

        // getColorSpace 验证
        Text('getColorSpace() 验证')
          .fontSize(16).fontWeight(FontWeight.Medium)
        Text('BT2020 红 colorSpace: ' + this.bt2020Red.getColorSpace())
          .fontSize(13).margin({ top: 5 })
        Text('P3 红 colorSpace: ' + this.p3Red.getColorSpace())
          .fontSize(13)
        Text('sRGB 红 colorSpace: ' + this.srgbRed.getColorSpace())
          .fontSize(13)

        Text('注意: BT2020 为 @systemapi (API 24+)，需要系统权限')
          .fontSize(12).fontColor('#999999').margin({ top: 20, bottom: 20 })
      }
      .width('100%')
      .padding({ left: 15, right: 15, top: 10, bottom: 20 })
    }
    .width('100%').height('100%').backgroundColor(Color.White)
  }
}
