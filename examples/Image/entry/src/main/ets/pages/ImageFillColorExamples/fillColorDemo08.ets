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
 * fillColor 动态 SVG + ColorMetrics 测试样例 (API 20+/24+)
 * 使用带 SMIL 动画的 SVG 测试 fillColor + ColorMetrics 的交互效果。
 * 动画 SVG: animated_smiley / animated_yin_yang / animated_star / animated_orbit
 * 基色: 红(0.631,0.0392,0.1294) 绿(0.09,0.662,0.552) 蓝(0,0.29,0.686)
 */
import { ColorMetrics } from '@kit.ArkUI'

@Entry
@Component
struct fillColorDemo08 {
  @State p3Red: ColorMetrics = ColorMetrics.colorWithSpace(ColorSpace.DISPLAY_P3, 0.631, 0.0392, 0.1294)
  @State p3Green: ColorMetrics = ColorMetrics.colorWithSpace(ColorSpace.DISPLAY_P3, 0.09, 0.662, 0.552)
  @State p3Blue: ColorMetrics = ColorMetrics.colorWithSpace(ColorSpace.DISPLAY_P3, 0, 0.29, 0.686)
  @State p3RedAlpha: ColorMetrics = ColorMetrics.colorWithSpace(ColorSpace.DISPLAY_P3, 0.631, 0.0392, 0.1294, 0.5)
  @State p3GreenAlpha: ColorMetrics = ColorMetrics.colorWithSpace(ColorSpace.DISPLAY_P3, 0.09, 0.662, 0.552, 0.5)
  @State p3BlueAlpha: ColorMetrics = ColorMetrics.colorWithSpace(ColorSpace.DISPLAY_P3, 0, 0.29, 0.686, 0.5)
  @State bt2020Red: ColorMetrics = ColorMetrics.colorWithSpace(2 as ColorSpace, 0.631, 0.0392, 0.1294)
  @State bt2020Green: ColorMetrics = ColorMetrics.colorWithSpace(2 as ColorSpace, 0.09, 0.662, 0.552)
  @State bt2020Blue: ColorMetrics = ColorMetrics.colorWithSpace(2 as ColorSpace, 0, 0.29, 0.686)

  @State colorArray: (Color | undefined | ColorMetrics | ColorContent)[] = [
    this.p3Red, this.p3Green, this.p3Blue,
    this.p3RedAlpha, this.p3GreenAlpha, this.p3BlueAlpha,
    this.bt2020Red, this.bt2020Green, this.bt2020Blue,
    ColorContent.ORIGIN, Color.Gray, undefined
  ]
  @State colorArrayStr: string[] = [
    'P3 红', 'P3 绿', 'P3 蓝',
    'P3 红 alpha:0.5', 'P3 绿 alpha:0.5', 'P3 蓝 alpha:0.5',
    'BT2020 红', 'BT2020 绿', 'BT2020 蓝',
    'ColorContent.ORIGIN', 'Gray', 'undefined'
  ]
  @State arrayIdx: number = 0
  @State svgIdx: number = 0
  @State svgArray: Resource[] = [
    $r('app.media.testSvg'), $r('app.media.heart'), $r('app.media.star'),
    $r('app.media.smiley'), $r('app.media.grid_blocks'), $r('app.media.star_circle'),
    $r('app.media.star_inner'), $r('app.media.pentagon_star'), $r('app.media.overlapping_circles'),
    $r('app.media.animated_smiley'), $r('app.media.animated_yin_yang'),
    $r('app.media.animated_star'), $r('app.media.animated_orbit'),
  ]
  @State svgStrArray: string[] = [
    'testSvg', 'heart', 'star', 'smiley', 'grid_blocks', 'star_circle',
    'star_inner', 'pentagon_star', 'overlapping_circles',
    'animated_smiley', 'animated_yin_yang', 'animated_star', 'animated_orbit',
  ]

  build() {
    Scroll() {
      Column() {
        Text('动态 SVG fillColor 测试')
          .fontSize(22).fontWeight(FontWeight.Bold).fontColor(Color.Black)

        Text('SVG 带 SMIL 动画 + ColorMetrics fillColor')
          .fontSize(13).fontColor('#666666').margin({ top: 5 })

        Text('SVG: ' + this.svgStrArray[this.svgIdx] + ' | FillColor: ' + this.colorArrayStr[this.arrayIdx])
          .fontSize(14).margin({ top: 10 })

        // 单 SVG 动态切换预览
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

        Blank().height(20).width('100%')

        // animated_smiley - 缩放动画
        Text('animated_smiley (scale 动画)')
          .fontSize(16).fontWeight(FontWeight.Medium)
        Row({ space: 15 }) {
          Column() {
            Text('P3 红').fontSize(11)
            Image($r('app.media.animated_smiley')).width(100).height(100)
              .fillColor(this.p3Red).borderRadius(10)
          }
          Column() {
            Text('P3 绿').fontSize(11)
            Image($r('app.media.animated_smiley')).width(100).height(100)
              .fillColor(this.p3Green).borderRadius(10)
          }
          Column() {
            Text('BT2020 蓝').fontSize(11)
            Image($r('app.media.animated_smiley')).width(100).height(100)
              .fillColor(this.bt2020Blue).borderRadius(10)
          }
        }.width('100%').justifyContent(FlexAlign.Center)

        Blank().height(20).width('100%')

        // animated_yin_yang - 旋转+脉冲动画
        Text('animated_yin_yang (rotate + pulse)')
          .fontSize(16).fontWeight(FontWeight.Medium)
        Row({ space: 15 }) {
          Column() {
            Text('P3 红').fontSize(11)
            Image($r('app.media.animated_yin_yang')).width(100).height(100)
              .fillColor(this.p3Red).borderRadius(10)
          }
          Column() {
            Text('P3 绿').fontSize(11)
            Image($r('app.media.animated_yin_yang')).width(100).height(100)
              .fillColor(this.p3Green).borderRadius(10)
          }
          Column() {
            Text('P3 蓝').fontSize(11)
            Image($r('app.media.animated_yin_yang')).width(100).height(100)
              .fillColor(this.p3Blue).borderRadius(10)
          }
        }.width('100%').justifyContent(FlexAlign.Center)

        Blank().height(20).width('100%')

        // animated_star - 旋转+透明度动画
        Text('animated_star (rotate + opacity)')
          .fontSize(16).fontWeight(FontWeight.Medium)
        Row({ space: 15 }) {
          Column() {
            Text('BT2020 红').fontSize(11)
            Image($r('app.media.animated_star')).width(100).height(100)
              .fillColor(this.bt2020Red).borderRadius(10)
          }
          Column() {
            Text('BT2020 绿').fontSize(11)
            Image($r('app.media.animated_star')).width(100).height(100)
              .fillColor(this.bt2020Green).borderRadius(10)
          }
          Column() {
            Text('BT2020 蓝').fontSize(11)
            Image($r('app.media.animated_star')).width(100).height(100)
              .fillColor(this.bt2020Blue).borderRadius(10)
          }
        }.width('100%').justifyContent(FlexAlign.Center)

        Blank().height(20).width('100%')

        // animated_orbit - 轨道移动+脉冲
        Text('animated_orbit (move + pulse)')
          .fontSize(16).fontWeight(FontWeight.Medium)
        Row({ space: 15 }) {
          Column() {
            Text('P3 红').fontSize(11)
            Image($r('app.media.animated_orbit')).width(100).height(100)
              .fillColor(this.p3Red).borderRadius(10)
          }
          Column() {
            Text('P3 绿').fontSize(11)
            Image($r('app.media.animated_orbit')).width(100).height(100)
              .fillColor(this.p3Green).borderRadius(10)
          }
          Column() {
            Text('P3 蓝').fontSize(11)
            Image($r('app.media.animated_orbit')).width(100).height(100)
              .fillColor(this.p3Blue).borderRadius(10)
          }
        }.width('100%').justifyContent(FlexAlign.Center)

        Blank().height(20).width('100%')

        // 半透明 + 动画 SVG
        Text('动态 SVG + 半透明 (alpha=0.5)')
          .fontSize(16).fontWeight(FontWeight.Medium)
        Row({ space: 12 }) {
          Column() {
            Text('smiley 红 0.5').fontSize(10)
            Image($r('app.media.animated_smiley')).width(80).height(80)
              .fillColor(this.p3RedAlpha).borderRadius(8)
          }
          Column() {
            Text('yin_yang 绿 0.5').fontSize(10)
            Image($r('app.media.animated_yin_yang')).width(80).height(80)
              .fillColor(this.p3GreenAlpha).borderRadius(8)
          }
          Column() {
            Text('star 蓝 0.5').fontSize(10)
            Image($r('app.media.animated_star')).width(80).height(80)
              .fillColor(this.p3BlueAlpha).borderRadius(8)
          }
          Column() {
            Text('orbit 红 0.5').fontSize(10)
            Image($r('app.media.animated_orbit')).width(80).height(80)
              .fillColor(this.p3RedAlpha).borderRadius(8)
          }
        }.width('100%').justifyContent(FlexAlign.Center)

        Blank().height(20).width('100%')

        // 动态切换 - 4个动画 SVG 同步
        Text('动态切换 - 动画 SVG 同步变色')
          .fontSize(16).fontWeight(FontWeight.Medium)
        Row({ space: 10 }) {
          Column() {
            Image($r('app.media.animated_smiley')).width(75).height(75)
              .fillColor(this.colorArray[this.arrayIdx]).borderRadius(8)
            Text('smiley').fontSize(10)
          }
          Column() {
            Image($r('app.media.animated_yin_yang')).width(75).height(75)
              .fillColor(this.colorArray[this.arrayIdx]).borderRadius(8)
            Text('yin_yang').fontSize(10)
          }
          Column() {
            Image($r('app.media.animated_star')).width(75).height(75)
              .fillColor(this.colorArray[this.arrayIdx]).borderRadius(8)
            Text('star').fontSize(10)
          }
          Column() {
            Image($r('app.media.animated_orbit')).width(75).height(75)
              .fillColor(this.colorArray[this.arrayIdx]).borderRadius(8)
            Text('orbit').fontSize(10)
          }
        }.width('100%').justifyContent(FlexAlign.Center)

        Blank().height(20).width('100%')

        // ColorContent.ORIGIN vs fillColor
        Text('ColorContent.ORIGIN vs fillColor')
          .fontSize(16).fontWeight(FontWeight.Medium)
        Row({ space: 15 }) {
          Column() {
            Text('ORIGIN (原始色)').fontSize(11)
            Image($r('app.media.animated_smiley')).width(90).height(90)
              .fillColor(ColorContent.ORIGIN).borderRadius(10)
          }
          Column() {
            Text('P3 红 fillColor').fontSize(11)
            Image($r('app.media.animated_smiley')).width(90).height(90)
              .fillColor(this.p3Red).borderRadius(10)
          }
        }.width('100%').justifyContent(FlexAlign.Center)
      }
      .width('100%')
      .padding({ left: 15, right: 15, top: 10, bottom: 20 })
    }
    .width('100%').height('100%').backgroundColor(Color.White)
  }
}
