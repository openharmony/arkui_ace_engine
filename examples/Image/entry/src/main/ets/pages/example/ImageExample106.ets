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
 * 图片colorFilter颜色滤镜示例
 * 演示通过5x4颜色矩阵对图片进行颜色变换，包括亮度、对比度、饱和度、色相旋转等效果
 */
@Entry
@Component
struct ImageExample106 {
  @State brightness: number = 1.0
  @State contrast: number = 1.0
  @State saturation: number = 1.0
  @State hueRotation: number = 0
  @State selectedPreset: number = 0

  private presets: string[] = ['原图', '灰度', '复古', '冷色', '暖色', '反转', '高亮', '暗化']

  private presetFilters: number[][] = [
    [1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0],
    [0.299, 0.587, 0.114, 0, 0, 0.299, 0.587, 0.114, 0, 0, 0.299, 0.587, 0.114, 0, 0, 0, 0, 0, 1, 0],
    [0.393, 0.769, 0.189, 0, 0, 0.349, 0.686, 0.168, 0, 0, 0.272, 0.534, 0.131, 0, 0, 0, 0, 0, 1, 0],
    [0.2, 0.3, 0.5, 0, 0, 0.1, 0.4, 0.5, 0, 0, 0.1, 0.2, 0.7, 0, 0, 0, 0, 0, 1, 0],
    [0.5, 0.3, 0.1, 0, 0, 0.3, 0.5, 0.1, 0, 0, 0.1, 0.2, 0.4, 0, 0, 0, 0, 0, 1, 0],
    [-1, 0, 0, 0, 1, 0, -1, 0, 0, 1, 0, 0, -1, 0, 1, 0, 0, 0, 1, 0],
    [1.5, 0, 0, 0, 0.2, 0, 1.5, 0, 0, 0.2, 0, 0, 1.5, 0, 0.2, 0, 0, 0, 1, 0],
    [0.5, 0, 0, 0, 0, 0, 0.5, 0, 0, 0, 0, 0, 0.5, 0, 0, 0, 0, 0, 1, 0]
  ]

  getCurrentFilter(): ColorFilter {
    if (this.selectedPreset > 0) {
      return ColorFilter.create(this.presetFilters[this.selectedPreset])
    }
    let matrix: number[] = [
      this.contrast, 0, 0, 0, this.brightness - 1,
      0, this.contrast, 0, 0, this.brightness - 1,
      0, 0, this.contrast, 0, this.brightness - 1,
      0, 0, 0, this.saturation, 0
    ]
    return ColorFilter.create(matrix)
  }

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('图片colorFilter颜色滤镜示例')
          .fontSize(22)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20 })

        Row({ space: 20 }) {
          Column({ space: 8 }) {
            Text('原图')
              .fontSize(14)
            Image($r('app.media.startIcon'))
              .width(150)
              .height(150)
              .objectFit(ImageFit.Cover)
              .borderRadius(8)
          }

          Column({ space: 8 }) {
            Text('滤镜效果')
              .fontSize(14)
            Image($r('app.media.startIcon'))
              .width(150)
              .height(150)
              .objectFit(ImageFit.Cover)
              .colorFilter(this.getCurrentFilter())
              .borderRadius(8)
          }
        }
        .width('100%')
        .justifyContent(FlexAlign.Center)

        Text('预设滤镜:')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .width('100%')

        Flex({ wrap: FlexWrap.Wrap, justifyContent: FlexAlign.Start }) {
          ForEach(this.presets, (preset: string, index: number) => {
            Button(preset)
              .fontSize(12)
              .margin(4)
              .height(36)
              .onClick(() => {
                this.selectedPreset = index
                if (index === 0) {
                  this.brightness = 1.0
                  this.contrast = 1.0
                  this.saturation = 1.0
                  this.hueRotation = 0
                }
              })
              .backgroundColor(this.selectedPreset === index ? 0x007DFF : 0xE0E0E0)
              .fontColor(this.selectedPreset === index ? Color.White : 0x333333)
          })
        }
        .width('100%')

        if (this.selectedPreset === 0) {
          Column({ space: 10 }) {
            Text('自定义调节:')
              .fontSize(16)
              .fontWeight(FontWeight.Medium)

            Row() {
              Text('亮度')
                .width(60)
                .fontSize(14)
              Slider({ value: this.brightness, min: 0, max: 2, step: 0.1 })
                .width('70%')
                .onChange((value: number) => {
                  this.brightness = value
                })
              Text(`${this.brightness.toFixed(1)}`)
                .width(40)
                .fontSize(14)
                .textAlign(TextAlign.End)
            }
            .width('100%')

            Row() {
              Text('对比度')
                .width(60)
                .fontSize(14)
              Slider({ value: this.contrast, min: 0, max: 3, step: 0.1 })
                .width('70%')
                .onChange((value: number) => {
                  this.contrast = value
                })
              Text(`${this.contrast.toFixed(1)}`)
                .width(40)
                .fontSize(14)
                .textAlign(TextAlign.End)
            }
            .width('100%')

            Row() {
              Text('饱和度')
                .width(60)
                .fontSize(14)
              Slider({ value: this.saturation, min: 0, max: 3, step: 0.1 })
                .width('70%')
                .onChange((value: number) => {
                  this.saturation = value
                })
              Text(`${this.saturation.toFixed(1)}`)
                .width(40)
                .fontSize(14)
                .textAlign(TextAlign.End)
            }
            .width('100%')
          }
          .width('100%')
          .padding(15)
          .backgroundColor(0xFFFFFF)
          .borderRadius(10)
        }

        Column({ space: 5 }) {
          Text('颜色矩阵说明:')
            .fontSize(14)
            .fontWeight(FontWeight.Medium)
          Text('colorFilter接受5x4颜色矩阵(20个浮点数)')
            .fontSize(12)
            .fontColor(0x666666)
          Text('矩阵格式: [R行5个, G行5个, B行5个, A行5个]')
            .fontSize(12)
            .fontColor(0x666666)
          Text('每行前4个为颜色通道权重，第5个为偏移量')
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
