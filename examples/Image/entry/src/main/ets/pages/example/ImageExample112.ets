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
 * SVG2支持示例
 * 演示supportSvg2属性开启SVG2高级特性，包括渐变、滤镜、遮罩、混合模式等
 */
@Entry
@Component
struct ImageExample112 {
  @State svgEnabled: boolean = true
  @State currentSvgIndex: number = 0

  private svgItems: { name: string, resource: Resource, desc: string }[] = [
    { name: '基础SVG', resource: $r('app.media.svg'), desc: '基础SVG图形' },
    { name: '线性渐变', resource: $r('app.media.svg2_gradient_linear'), desc: 'SVG2 linearGradient渐变效果' },
    { name: '径向渐变', resource: $r('app.media.svg2_gradient_radial'), desc: 'SVG2 radialGradient渐变效果' },
    { name: '坐标变换', resource: $r('app.media.svg2_coordinates'), desc: 'SVG2坐标系统变换' },
    { name: '复杂滤镜', resource: $r('app.media.svg2_filter_complex'), desc: 'SVG2 feGaussianBlur等滤镜组合' },
    { name: '混合SVG', resource: $r('app.media.svg2_mixed'), desc: 'SVG2多种特性混合使用' },
    { name: '遮罩图案', resource: $r('app.media.svg2_mask_pattern'), desc: 'SVG2 mask和pattern特性' }
  ]

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('SVG2高级特性支持示例')
          .fontSize(22)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20 })

        Text('通过supportSvg2属性开启SVG2解析能力，支持渐变、滤镜、遮罩等高级特性')
          .fontSize(14)
          .fontColor(0x666666)

        Row({ space: 20 }) {
          Column({ space: 8 }) {
            Text('supportSvg2: false')
              .fontSize(14)
              .fontColor(0x666666)
            Image(this.svgItems[this.currentSvgIndex].resource)
              .width(160)
              .height(160)
              .objectFit(ImageFit.Contain)
              .supportSvg2(false)
              .border({ width: 2, color: Color.Red })
              .borderRadius(8)
              .backgroundColor(0xF0F0F0)
          }

          Column({ space: 8 }) {
            Text('supportSvg2: true')
              .fontSize(14)
              .fontColor(0x666666)
            Image(this.svgItems[this.currentSvgIndex].resource)
              .width(160)
              .height(160)
              .objectFit(ImageFit.Contain)
              .supportSvg2(true)
              .border({ width: 2, color: Color.Green })
              .borderRadius(8)
              .backgroundColor(0xF0F0F0)
          }
        }
        .width('100%')
        .justifyContent(FlexAlign.Center)

        Text(this.svgItems[this.currentSvgIndex].desc)
          .fontSize(14)
          .fontColor(0x666666)

        Column({ space: 8 }) {
          Text('SVG文件选择:')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)

          List({ space: 8 }) {
            ForEach(this.svgItems, (item: { name: string, resource: Resource, desc: string }, index: number) => {
              ListItem() {
                Row({ space: 10 }) {
                  Image(item.resource)
                    .width(40)
                    .height(40)
                    .objectFit(ImageFit.Contain)
                    .supportSvg2(true)
                    .border({ width: 1, color: 0xCCCCCC })
                    .borderRadius(4)
                    .backgroundColor(0xFFFFFF)

                  Column({ space: 2 }) {
                    Text(item.name)
                      .fontSize(14)
                      .fontWeight(FontWeight.Medium)
                    Text(item.desc)
                      .fontSize(11)
                      .fontColor(0x999999)
                  }
                  .alignItems(HorizontalAlign.Start)
                  .layoutWeight(1)
                }
                .width('100%')
                .padding(10)
                .backgroundColor(this.currentSvgIndex === index ? 0xE3F2FD : 0xFFFFFF)
                .borderRadius(8)
                .onClick(() => {
                  this.currentSvgIndex = index
                })
              }
            })
          }
          .width('100%')
          .height(300)
        }
        .width('100%')
        .padding(15)
        .backgroundColor(0xF5F5F5)
        .borderRadius(10)

        Column({ space: 10 }) {
          Text('SVG尺寸调节:')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)

          Row({ space: 20 }) {
            Column({ space: 5 }) {
              Text('小尺寸(80x80)')
                .fontSize(12)
                .fontColor(0x666666)
              Image(this.svgItems[this.currentSvgIndex].resource)
                .width(80)
                .height(80)
                .supportSvg2(this.svgEnabled)
                .border({ width: 1, color: 0xCCCCCC })
                .borderRadius(4)
            }

            Column({ space: 5 }) {
              Text('中尺寸(120x120)')
                .fontSize(12)
                .fontColor(0x666666)
              Image(this.svgItems[this.currentSvgIndex].resource)
                .width(120)
                .height(120)
                .supportSvg2(this.svgEnabled)
                .border({ width: 1, color: 0xCCCCCC })
                .borderRadius(4)
            }

            Column({ space: 5 }) {
              Text('大尺寸(180x180)')
                .fontSize(12)
                .fontColor(0x666666)
              Image(this.svgItems[this.currentSvgIndex].resource)
                .width(180)
                .height(180)
                .supportSvg2(this.svgEnabled)
                .border({ width: 1, color: 0xCCCCCC })
                .borderRadius(4)
            }
          }
        }
        .width('100%')
        .padding(15)
        .backgroundColor(0xFFFFFF)
        .borderRadius(10)

        Column({ space: 5 }) {
          Text('SVG2支持的特性:')
            .fontSize(14)
            .fontWeight(FontWeight.Medium)
          Text('• linearGradient/radialGradient: 线性和径向渐变')
            .fontSize(12)
            .fontColor(0x666666)
          Text('• filter: feGaussianBlur、feColorMatrix等滤镜')
            .fontSize(12)
            .fontColor(0x666666)
          Text('• mask: 遮罩效果')
            .fontSize(12)
            .fontColor(0x666666)
          Text('• pattern: 图案填充')
            .fontSize(12)
            .fontColor(0x666666)
          Text('• clipPath: 裁剪路径')
            .fontSize(12)
            .fontColor(0x666666)
          Text('• transform: 坐标变换(translate, rotate, scale)')
            .fontSize(12)
            .fontColor(0x666666)
        }
        .width('100%')
        .padding(15)
        .backgroundColor(0xFFFFFF)
        .borderRadius(10)
      }
      .width('100%')
      .padding({ left: 20, right: 20, bottom: 20 })
    }
    .width('100%')
    .height('100%')
    .backgroundColor(0xF5F5F5)
  }
}
