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
 * 图片边框装饰与渐变效果示例
 * 演示border、outline、backgroundBlurStyle等装饰效果在图片上的应用
 */
@Entry
@Component
struct ImageExample115 {
  @State borderWidth: number = 2
  @State borderColor: number = 0x007DFF
  @State borderRadius: number = 12
  @State outlineWidth: number = 0
  @State blurRadius: number = 0
  @State grayscaleValue: number = 0
  @State sepiaValue: number = 0
  @State invertValue: number = 0

  private colorOptions: { name: string, color: number }[] = [
    { name: '蓝色', color: 0x007DFF },
    { name: '红色', color: 0xFF0000 },
    { name: '绿色', color: 0x00CC00 },
    { name: '橙色', color: 0xFF9900 },
    { name: '紫色', color: 0x9900FF },
    { name: '黑色', color: 0x000000 }
  ]

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('图片边框装饰与视觉效果示例')
          .fontSize(22)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20 })

        Column({ space: 8 }) {
          Image($r('app.media.startIcon'))
            .width(220)
            .height(220)
            .objectFit(ImageFit.Cover)
            .border({
              width: this.borderWidth,
              color: this.borderColor,
              style: BorderStyle.Solid
            })
            .borderRadius(this.borderRadius)
            .outline({
              width: this.outlineWidth,
              color: this.borderColor,
              style: BorderStyle.Dashed
            })
            .blur(this.blurRadius)
            .grayscale(this.grayscaleValue)
            .sepia(this.sepiaValue)
            .invert(this.invertValue)
            .shadow({ radius: 8, color: 0x33000000, offsetX: 2, offsetY: 4 })
        }
        .width('100%')
        .alignItems(HorizontalAlign.Center)

        Column({ space: 10 }) {
          Text('边框设置:')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)

          Row() {
            Text('边框宽度')
              .width(70)
              .fontSize(14)
            Slider({ value: this.borderWidth, min: 0, max: 15, step: 1 })
              .layoutWeight(1)
              .onChange((value: number) => {
                this.borderWidth = value
              })
            Text(`${this.borderWidth}`)
              .width(30)
              .fontSize(14)
              .textAlign(TextAlign.End)
          }

          Row() {
            Text('圆角半径')
              .width(70)
              .fontSize(14)
            Slider({ value: this.borderRadius, min: 0, max: 110, step: 1 })
              .layoutWeight(1)
              .onChange((value: number) => {
                this.borderRadius = value
              })
            Text(`${this.borderRadius}`)
              .width(30)
              .fontSize(14)
              .textAlign(TextAlign.End)
          }

          Row() {
            Text('外描边宽')
              .width(70)
              .fontSize(14)
            Slider({ value: this.outlineWidth, min: 0, max: 10, step: 1 })
              .layoutWeight(1)
              .onChange((value: number) => {
                this.outlineWidth = value
              })
            Text(`${this.outlineWidth}`)
              .width(30)
              .fontSize(14)
              .textAlign(TextAlign.End)
          }

          Text('边框颜色:')
            .fontSize(14)
          Row({ space: 8 }) {
            ForEach(this.colorOptions, (item: { name: string, color: number }) => {
              Column() {
                Row()
                  .width(24)
                  .height(24)
                  .borderRadius(12)
                  .backgroundColor(item.color)
                  .border({ width: 2, color: this.borderColor === item.color ? 0xFFD700 : 0xCCCCCC })
                Text(item.name)
                  .fontSize(10)
                  .fontColor(0x666666)
                  .margin({ top: 2 })
              }
              .onClick(() => {
                this.borderColor = item.color
              })
            })
          }
        }
        .width('100%')
        .padding(15)
        .backgroundColor(0xFFFFFF)
        .borderRadius(10)

        Column({ space: 10 }) {
          Text('视觉效果:')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)

          Row() {
            Text('模糊')
              .width(50)
              .fontSize(14)
            Slider({ value: this.blurRadius, min: 0, max: 20, step: 1 })
              .layoutWeight(1)
              .onChange((value: number) => {
                this.blurRadius = value
              })
            Text(`${this.blurRadius}`)
              .width(30)
              .fontSize(14)
              .textAlign(TextAlign.End)
          }

          Row() {
            Text('灰度')
              .width(50)
              .fontSize(14)
            Slider({ value: this.grayscaleValue * 100, min: 0, max: 100, step: 5 })
              .layoutWeight(1)
              .onChange((value: number) => {
                this.grayscaleValue = value / 100
              })
            Text(`${Math.floor(this.grayscaleValue * 100)}%`)
              .width(40)
              .fontSize(14)
              .textAlign(TextAlign.End)
          }

          Row() {
            Text('复古')
              .width(50)
              .fontSize(14)
            Slider({ value: this.sepiaValue * 100, min: 0, max: 100, step: 5 })
              .layoutWeight(1)
              .onChange((value: number) => {
                this.sepiaValue = value / 100
              })
            Text(`${Math.floor(this.sepiaValue * 100)}%`)
              .width(40)
              .fontSize(14)
              .textAlign(TextAlign.End)
          }

          Row() {
            Text('反转')
              .width(50)
              .fontSize(14)
            Slider({ value: this.invertValue * 100, min: 0, max: 100, step: 5 })
              .layoutWeight(1)
              .onChange((value: number) => {
                this.invertValue = value / 100
              })
            Text(`${Math.floor(this.invertValue * 100)}%`)
              .width(40)
              .fontSize(14)
              .textAlign(TextAlign.End)
          }

          Button('重置效果')
            .onClick(() => {
              this.borderWidth = 2
              this.borderColor = 0x007DFF
              this.borderRadius = 12
              this.outlineWidth = 0
              this.blurRadius = 0
              this.grayscaleValue = 0
              this.sepiaValue = 0
              this.invertValue = 0
            })
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
