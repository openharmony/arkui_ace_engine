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
 * fillColor Display-P3 色域测试样例 (API 20+)
 * 使用 ColorMetrics.colorWithSpace 在 DISPLAY_P3 色域下设置 fillColor，
 * 并与 sRGB 同色值进行对比。使用 ITU-R BT.2100 推荐的 P3 基色坐标。
 * P3 基色: 红(0.631,0.0392,0.1294) 绿(0.09,0.662,0.552) 蓝(0,0.29,0.686)
 */
import { ColorMetrics } from '@kit.ArkUI'

@Entry
@Component
struct fillColorDemo03 {
  @State p3Red: ColorMetrics = ColorMetrics.colorWithSpace(ColorSpace.DISPLAY_P3, 0.631, 0.0392, 0.1294)
  @State p3Green: ColorMetrics = ColorMetrics.colorWithSpace(ColorSpace.DISPLAY_P3, 0.09, 0.662, 0.552)
  @State p3Blue: ColorMetrics = ColorMetrics.colorWithSpace(ColorSpace.DISPLAY_P3, 0, 0.29, 0.686)
  @State p3RedAlpha: ColorMetrics = ColorMetrics.colorWithSpace(ColorSpace.DISPLAY_P3, 0.631, 0.0392, 0.1294, 0.5)
  @State p3GreenAlpha: ColorMetrics = ColorMetrics.colorWithSpace(ColorSpace.DISPLAY_P3, 0.09, 0.662, 0.552, 0.5)
  @State p3BlueAlpha: ColorMetrics = ColorMetrics.colorWithSpace(ColorSpace.DISPLAY_P3, 0, 0.29, 0.686, 0.5)
  @State sRGBRed: ColorMetrics = ColorMetrics.colorWithSpace(ColorSpace.SRGB, 0.631, 0.0392, 0.1294)
  @State sRGBGreen: ColorMetrics = ColorMetrics.colorWithSpace(ColorSpace.SRGB, 0.09, 0.662, 0.552)
  @State sRGBBlue: ColorMetrics = ColorMetrics.colorWithSpace(ColorSpace.SRGB, 0, 0.29, 0.686)

  @State colorArray: (Color | undefined | ColorMetrics | ColorContent)[] = [
    this.p3Red, this.p3Green, this.p3Blue,
    this.p3RedAlpha, this.p3GreenAlpha, this.p3BlueAlpha,
    ColorContent.ORIGIN, Color.Gray, undefined
  ]
  @State colorArrayStr: string[] = [
    'P3 红 (0.631,0.0392,0.1294)', 'P3 绿 (0.09,0.662,0.552)', 'P3 蓝 (0,0.29,0.686)',
    'P3 红 alpha:0.5', 'P3 绿 alpha:0.5', 'P3 蓝 alpha:0.5',
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
        Text('fillColor P3 色域测试')
          .fontSize(22).fontWeight(FontWeight.Bold).fontColor(Color.Black)

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

        // P3 vs sRGB 红色对比
        Text('P3 红 vs sRGB 红 (同色值)')
          .fontSize(16).fontWeight(FontWeight.Medium)
        Row({ space: 20 }) {
          Column() {
            Text('P3').fontSize(14).fontColor(Color.Gray)
            Image(this.svgArray[this.svgIdx]).width(90).height(90)
              .fillColor(this.p3Red).borderRadius(10)
          }
          Column() {
            Text('sRGB').fontSize(14).fontColor(Color.Gray)
            Image(this.svgArray[this.svgIdx]).width(90).height(90)
              .fillColor(this.sRGBRed).borderRadius(10)
          }
        }.width('100%').justifyContent(FlexAlign.Center)

        Blank().height(20).width('100%')

        // P3 vs sRGB 绿色对比
        Text('P3 绿 vs sRGB 绿 (同色值)')
          .fontSize(16).fontWeight(FontWeight.Medium)
        Row({ space: 20 }) {
          Column() {
            Text('P3').fontSize(14).fontColor(Color.Gray)
            Image(this.svgArray[this.svgIdx]).width(90).height(90)
              .fillColor(this.p3Green).borderRadius(10)
          }
          Column() {
            Text('sRGB').fontSize(14).fontColor(Color.Gray)
            Image(this.svgArray[this.svgIdx]).width(90).height(90)
              .fillColor(this.sRGBGreen).borderRadius(10)
          }
        }.width('100%').justifyContent(FlexAlign.Center)

        Blank().height(20).width('100%')

        // P3 vs sRGB 蓝色对比
        Text('P3 蓝 vs sRGB 蓝 (同色值)')
          .fontSize(16).fontWeight(FontWeight.Medium)
        Row({ space: 20 }) {
          Column() {
            Text('P3').fontSize(14).fontColor(Color.Gray)
            Image(this.svgArray[this.svgIdx]).width(90).height(90)
              .fillColor(this.p3Blue).borderRadius(10)
          }
          Column() {
            Text('sRGB').fontSize(14).fontColor(Color.Gray)
            Image(this.svgArray[this.svgIdx]).width(90).height(90)
              .fillColor(this.sRGBBlue).borderRadius(10)
          }
        }.width('100%').justifyContent(FlexAlign.Center)

        Blank().height(20).width('100%')

        // P3 三基色
        Text('P3 三基色')
          .fontSize(16).fontWeight(FontWeight.Medium)
        Row({ space: 15 }) {
          Column() {
            Text('P3 红').fontSize(12)
            Image(this.svgArray[this.svgIdx]).width(80).height(80)
              .fillColor(this.p3Red).borderRadius(8)
          }
          Column() {
            Text('P3 绿').fontSize(12)
            Image(this.svgArray[this.svgIdx]).width(80).height(80)
              .fillColor(this.p3Green).borderRadius(8)
          }
          Column() {
            Text('P3 蓝').fontSize(12)
            Image(this.svgArray[this.svgIdx]).width(80).height(80)
              .fillColor(this.p3Blue).borderRadius(8)
          }
        }.width('100%').justifyContent(FlexAlign.Center)

        Blank().height(20).width('100%')

        // P3 半透明
        Text('P3 半透明 (alpha=0.5)')
          .fontSize(16).fontWeight(FontWeight.Medium)
        Row({ space: 15 }) {
          Column() {
            Text('红').fontSize(12)
            Image(this.svgArray[this.svgIdx]).width(80).height(80)
              .fillColor(this.p3RedAlpha).borderRadius(8)
          }
          Column() {
            Text('绿').fontSize(12)
            Image(this.svgArray[this.svgIdx]).width(80).height(80)
              .fillColor(this.p3GreenAlpha).borderRadius(8)
          }
          Column() {
            Text('蓝').fontSize(12)
            Image(this.svgArray[this.svgIdx]).width(80).height(80)
              .fillColor(this.p3BlueAlpha).borderRadius(8)
          }
        }.width('100%').justifyContent(FlexAlign.Center)
      }
      .width('100%')
      .padding({ left: 15, right: 15, top: 10, bottom: 20 })
    }
    .width('100%').height('100%').backgroundColor(Color.White)
  }
}
