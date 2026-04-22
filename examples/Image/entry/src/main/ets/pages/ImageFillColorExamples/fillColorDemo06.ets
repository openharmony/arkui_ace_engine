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
 * fillColor ColorMetrics AttributeModifier 测试样例 (API 20+/24+)
 * 通过 AttributeModifier 方式动态设置 Image 的 fillColor，
 * 覆盖 P3、BT2020、HDR 等多种 ColorMetrics 类型。
 * 基色: 红(0.631,0.0392,0.1294) 绿(0.09,0.662,0.552) 蓝(0,0.29,0.686)
 */
import { ColorMetrics } from '@kit.ArkUI'

// P3 色域 Modifier
class P3ColorModifier implements AttributeModifier<ImageAttribute> {
  public colorIdx: number = 0
  public colors: (ColorMetrics | ColorContent | undefined)[] = [
    ColorMetrics.colorWithSpace(ColorSpace.DISPLAY_P3, 0.631, 0.0392, 0.1294),
    ColorMetrics.colorWithSpace(ColorSpace.DISPLAY_P3, 0.09, 0.662, 0.552),
    ColorMetrics.colorWithSpace(ColorSpace.DISPLAY_P3, 0, 0.29, 0.686),
    ColorMetrics.colorWithSpace(ColorSpace.DISPLAY_P3, 0.631, 0.0392, 0.1294, 0.5),
    ColorMetrics.colorWithSpace(ColorSpace.DISPLAY_P3, 0.09, 0.662, 0.552, 0.5),
    ColorMetrics.colorWithSpace(ColorSpace.DISPLAY_P3, 0, 0.29, 0.686, 0.5),
    ColorContent.ORIGIN,
    undefined,
  ]
  public colorStrs: string[] = [
    'P3 红 (0.631,0.0392,0.1294)', 'P3 绿 (0.09,0.662,0.552)', 'P3 蓝 (0,0.29,0.686)',
    'P3 红 alpha:0.5', 'P3 绿 alpha:0.5', 'P3 蓝 alpha:0.5',
    'ColorContent.ORIGIN', 'undefined',
  ]

  applyNormalAttribute(instance: ImageAttribute): void {
    instance.fillColor(this.colors[this.colorIdx])
  }
}

// BT2020 色域 Modifier (API 24+, @systemapi)
class BT2020ColorModifier implements AttributeModifier<ImageAttribute> {
  public colorIdx: number = 0
  public colors: (ColorMetrics | ColorContent | undefined)[] = [
    ColorMetrics.colorWithSpace(2 as ColorSpace, 0.631, 0.0392, 0.1294),
    ColorMetrics.colorWithSpace(2 as ColorSpace, 0.09, 0.662, 0.552),
    ColorMetrics.colorWithSpace(2 as ColorSpace, 0, 0.29, 0.686),
    ColorMetrics.colorWithSpace(2 as ColorSpace, 0.631, 0.0392, 0.1294, 0.5),
    ColorMetrics.colorWithSpace(2 as ColorSpace, 0.09, 0.662, 0.552, 0.5),
    ColorMetrics.colorWithSpace(2 as ColorSpace, 0, 0.29, 0.686, 0.5),
    ColorContent.ORIGIN,
    undefined,
  ]
  public colorStrs: string[] = [
    'BT2020 红', 'BT2020 绿', 'BT2020 蓝',
    'BT2020 红 alpha:0.5', 'BT2020 绿 alpha:0.5', 'BT2020 蓝 alpha:0.5',
    'ColorContent.ORIGIN', 'undefined',
  ]

  applyNormalAttribute(instance: ImageAttribute): void {
    instance.fillColor(this.colors[this.colorIdx])
  }
}

// HDR Modifier (API 24+, @systemapi)
class HDRColorModifier implements AttributeModifier<ImageAttribute> {
  public colorIdx: number = 0
  public colors: ColorMetrics[] = [
    ColorMetrics.createHDRColor(ColorSpace.DISPLAY_P3, 1.5, 0, 0),
    ColorMetrics.createHDRColor(ColorSpace.DISPLAY_P3, 0, 1.5, 0),
    ColorMetrics.createHDRColor(ColorSpace.DISPLAY_P3, 0, 0, 1.5),
    ColorMetrics.createHDRColor(2 as ColorSpace, 1.262, 0.0784, 0.2588),
    ColorMetrics.createHDRColor(2 as ColorSpace, 0.18, 1.324, 1.104),
    ColorMetrics.createHDRColor(2 as ColorSpace, 0, 0.58, 1.372),
    ColorMetrics.createHDRColorWithLinearExposure(2.0, ColorSpace.DISPLAY_P3, 0.631, 0.0392, 0.1294),
    ColorMetrics.createHDRColorWithLinearExposure(2.0, ColorSpace.DISPLAY_P3, 0.09, 0.662, 0.552),
    ColorMetrics.createHDRColorWithLinearExposure(3.0, 2 as ColorSpace, 0.631, 0.0392, 0.1294),
    ColorMetrics.createHDRColorWithLogExposure(1.0, ColorSpace.DISPLAY_P3, 0.631, 0.0392, 0.1294),
    ColorMetrics.createHDRColorWithLogExposure(1.0, ColorSpace.DISPLAY_P3, 0.09, 0.662, 0.552),
    ColorMetrics.createHDRColorWithLogExposure(2.0, 2 as ColorSpace, 0.631, 0.0392, 0.1294),
  ]
  public colorStrs: string[] = [
    'HDR P3 红 (R=1.5)', 'HDR P3 绿 (G=1.5)', 'HDR P3 蓝 (B=1.5)',
    'HDR BT2020 红', 'HDR BT2020 绿', 'HDR BT2020 蓝',
    'LinearExp P3 红 x2', 'LinearExp P3 绿 x2', 'LinearExp BT2020 红 x3',
    'LogExp P3 红 +1stop', 'LogExp P3 绿 +1stop', 'LogExp BT2020 红 +2stop',
  ]

  applyNormalAttribute(instance: ImageAttribute): void {
    instance.fillColor(this.colors[this.colorIdx])
  }
}

@Entry
@Component
struct fillColorDemo06 {
  @State p3Modifier: P3ColorModifier = new P3ColorModifier()
  @State bt2020Modifier: BT2020ColorModifier = new BT2020ColorModifier()
  @State hdrModifier: HDRColorModifier = new HDRColorModifier()
  @State p3Idx: number = 0
  @State bt2020Idx: number = 0
  @State hdrIdx: number = 0
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
        Text('fillColor AttributeModifier 测试')
          .fontSize(22).fontWeight(FontWeight.Bold).fontColor(Color.Black)

        Text('通过 attributeModifier 动态切换 ColorMetrics fillColor')
          .fontSize(13).fontColor('#666666').margin({ top: 5 })

        Text('当前 SVG: ' + this.svgStrArray[this.svgIdx])
          .fontSize(14).margin({ top: 5 })
        Button('ChangeSvg')
          .fontSize(13)
          .onClick(() => {
            this.svgIdx = (this.svgIdx + 1) % this.svgArray.length
          })

        Blank().height(20).width('100%')

        // P3 Modifier
        Text('P3 色域 Modifier')
          .fontSize(18).fontWeight(FontWeight.Medium)
        Text('当前: ' + this.p3Modifier.colorStrs[this.p3Modifier.colorIdx])
          .fontSize(14).margin({ top: 5 })
        Image(this.svgArray[this.svgIdx])
          .width(110).height(110).margin(15)
          .attributeModifier(this.p3Modifier)
        Row({ space: 10 }) {
          Button('上一个').onClick(() => {
            this.p3Modifier.colorIdx =
              (this.p3Modifier.colorIdx - 1 + this.p3Modifier.colors.length) % this.p3Modifier.colors.length
            this.p3Idx = this.p3Modifier.colorIdx
          })
          Button('下一个').onClick(() => {
            this.p3Modifier.colorIdx = (this.p3Modifier.colorIdx + 1) % this.p3Modifier.colors.length
            this.p3Idx = this.p3Modifier.colorIdx
          })
        }

        Blank().height(30).width('100%')

        // BT2020 Modifier
        Text('BT2020 色域 Modifier (API 24+)')
          .fontSize(18).fontWeight(FontWeight.Medium)
        Text('当前: ' + this.bt2020Modifier.colorStrs[this.bt2020Modifier.colorIdx])
          .fontSize(14).margin({ top: 5 })
        Image(this.svgArray[this.svgIdx])
          .width(110).height(110).margin(15)
          .attributeModifier(this.bt2020Modifier)
        Row({ space: 10 }) {
          Button('上一个').onClick(() => {
            this.bt2020Modifier.colorIdx =
              (this.bt2020Modifier.colorIdx - 1 + this.bt2020Modifier.colors.length) % this.bt2020Modifier.colors.length
            this.bt2020Idx = this.bt2020Modifier.colorIdx
          })
          Button('下一个').onClick(() => {
            this.bt2020Modifier.colorIdx = (this.bt2020Modifier.colorIdx + 1) % this.bt2020Modifier.colors.length
            this.bt2020Idx = this.bt2020Modifier.colorIdx
          })
        }

        Blank().height(30).width('100%')

        // HDR Modifier
        Text('HDR ColorMetrics Modifier (API 24+)')
          .fontSize(18).fontWeight(FontWeight.Medium)
        Text('当前: ' + this.hdrModifier.colorStrs[this.hdrModifier.colorIdx])
          .fontSize(14).margin({ top: 5 })
        Image(this.svgArray[this.svgIdx])
          .width(110).height(110).margin(15)
          .attributeModifier(this.hdrModifier)
        Row({ space: 10 }) {
          Button('上一个').onClick(() => {
            this.hdrModifier.colorIdx =
              (this.hdrModifier.colorIdx - 1 + this.hdrModifier.colors.length) % this.hdrModifier.colors.length
            this.hdrIdx = this.hdrModifier.colorIdx
          })
          Button('下一个').onClick(() => {
            this.hdrModifier.colorIdx = (this.hdrModifier.colorIdx + 1) % this.hdrModifier.colors.length
            this.hdrIdx = this.hdrModifier.colorIdx
          })
        }

        Blank().height(30).width('100%')

        // 三 Modifier 并排对比
        Text('三种 Modifier 红色对比')
          .fontSize(16).fontWeight(FontWeight.Medium)
        Row({ space: 15 }) {
          Column() {
            Text('P3').fontSize(12)
            Image(this.svgArray[this.svgIdx]).width(85).height(85)
              .attributeModifier(this.p3Modifier).borderRadius(10)
          }
          Column() {
            Text('BT2020').fontSize(12)
            Image(this.svgArray[this.svgIdx]).width(85).height(85)
              .attributeModifier(this.bt2020Modifier).borderRadius(10)
          }
          Column() {
            Text('HDR').fontSize(12)
            Image(this.svgArray[this.svgIdx]).width(85).height(85)
              .attributeModifier(this.hdrModifier).borderRadius(10)
          }
        }.width('100%').justifyContent(FlexAlign.Center)

        Blank().height(20).width('100%')

        Button('全部重置').onClick(() => {
          this.p3Modifier.colorIdx = 0
          this.bt2020Modifier.colorIdx = 0
          this.hdrModifier.colorIdx = 0
          this.p3Idx = 0
          this.bt2020Idx = 0
          this.hdrIdx = 0
        })
      }
      .width('100%')
      .padding({ left: 15, right: 15, top: 10, bottom: 20 })
    }
    .width('100%').height('100%').backgroundColor(Color.White)
  }
}
