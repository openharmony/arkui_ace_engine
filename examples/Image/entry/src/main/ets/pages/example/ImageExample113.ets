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
 * 图片圆角裁剪综合示例
 * 演示borderRadius、clipShape等多种圆角裁剪方式的综合使用
 */
@Entry
@Component
struct ImageExample113 {
  @State borderRadius: number = 0
  @State clipShapeIndex: number = 0
  @State imageWidth: number = 200
  @State imageHeight: number = 200

  private clipShapes: { name: string, desc: string }[] = [
    { name: '无裁剪', desc: '不使用clipShape' },
    { name: '圆形', desc: 'Circle裁剪为圆形' },
    { name: '椭圆', desc: 'Ellipse裁剪为椭圆' },
    { name: '圆角矩形', desc: 'RoundRectangle自定义圆角' }
  ]

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('图片圆角裁剪综合示例')
          .fontSize(22)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20 })

        Text('演示borderRadius和clipShape两种圆角裁剪方式')
          .fontSize(14)
          .fontColor(0x666666)

        Column({ space: 8 }) {
          Text('borderRadius圆角效果:')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)

          Row({ space: 15 }) {
            Image($r('app.media.startIcon'))
              .width(120)
              .height(120)
              .objectFit(ImageFit.Cover)
              .borderRadius(this.borderRadius)
              .border({ width: 1, color: 0xCCCCCC })
            Image($r('app.media.startIcon'))
              .width(120)
              .height(120)
              .objectFit(ImageFit.Cover)
              .borderRadius(this.borderRadius)
              .border({ width: 1, color: 0xCCCCCC })
          }

          Row() {
            Text('圆角半径')
              .width(70)
              .fontSize(14)
            Slider({ value: this.borderRadius, min: 0, max: 100, step: 1 })
              .layoutWeight(1)
              .onChange((value: number) => {
                this.borderRadius = value
              })
            Text(`${this.borderRadius}`)
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

        Column({ space: 8 }) {
          Text('clipShape裁剪形状:')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)

          Row({ space: 8 }) {
            ForEach(this.clipShapes, (shape: { name: string, desc: string }, index: number) => {
              Button(shape.name)
                .fontSize(11)
                .height(32)
                .onClick(() => {
                  this.clipShapeIndex = index
                })
                .backgroundColor(this.clipShapeIndex === index ? 0x007DFF : 0xE0E0E0)
                .fontColor(this.clipShapeIndex === index ? Color.White : 0x333333)
            })
          }

          Row({ space: 15 }) {
            if (this.clipShapeIndex === 0) {
              Image($r('app.media.startIcon'))
                .width(150)
                .height(150)
                .objectFit(ImageFit.Cover)
                .border({ width: 1, color: 0xCCCCCC })
            }
            if (this.clipShapeIndex === 1) {
              Image($r('app.media.startIcon'))
                .width(150)
                .height(150)
                .objectFit(ImageFit.Cover)
                .clipShape(new Circle({ width: 150, height: 150 }))
            }
            if (this.clipShapeIndex === 2) {
              Image($r('app.media.startIcon'))
                .width(180)
                .height(120)
                .objectFit(ImageFit.Cover)
                .clipShape(new Ellipse({ width: 180, height: 120 }))
            }
            if (this.clipShapeIndex === 3) {
              Image($r('app.media.startIcon'))
                .width(150)
                .height(150)
                .objectFit(ImageFit.Cover)
                .clipShape(new RoundRectangle({
                  width: 150, height: 150,
                  radius: [20, 40, 20, 40]
                }))
            }
          }
          .width('100%')
          .justifyContent(FlexAlign.Center)

          Text(this.clipShapes[this.clipShapeIndex].desc)
            .fontSize(12)
            .fontColor(0x999999)
        }
        .width('100%')
        .padding(15)
        .backgroundColor(0xFFFFFF)
        .borderRadius(10)

        Column({ space: 8 }) {
          Text('形状组合示例:')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)

          Flex({ wrap: FlexWrap.Wrap, justifyContent: FlexAlign.SpaceAround }) {
            Column({ space: 5 }) {
              Image($r('app.media.startIcon'))
                .width(100)
                .height(100)
                .objectFit(ImageFit.Cover)
                .borderRadius(50)
              Text('borderRadius=50')
                .fontSize(11)
                .fontColor(0x999999)
            }
            .margin(8)

            Column({ space: 5 }) {
              Image($r('app.media.startIcon'))
                .width(100)
                .height(100)
                .objectFit(ImageFit.Cover)
                .clipShape(new Circle({ width: 100, height: 100 }))
              Text('Circle裁剪')
                .fontSize(11)
                .fontColor(0x999999)
            }
            .margin(8)

            Column({ space: 5 }) {
              Image($r('app.media.startIcon'))
                .width(100)
                .height(100)
                .objectFit(ImageFit.Cover)
                .borderRadius(15)
                .border({ width: 3, color: 0x007DFF })
              Text('边框+圆角')
                .fontSize(11)
                .fontColor(0x999999)
            }
            .margin(8)

            Column({ space: 5 }) {
              Image($r('app.media.startIcon'))
                .width(100)
                .height(100)
                .objectFit(ImageFit.Cover)
                .clipShape(new RoundRectangle({
                  width: 100, height: 100,
                  radius: [30, 5, 30, 5]
                }))
              Text('不对称圆角')
                .fontSize(11)
                .fontColor(0x999999)
            }
            .margin(8)
          }
        }
        .width('100%')
        .padding(15)
        .backgroundColor(0xFFFFFF)
        .borderRadius(10)

        Column({ space: 5 }) {
          Text('说明:')
            .fontSize(14)
            .fontWeight(FontWeight.Medium)
          Text('• borderRadius: 简单的圆角设置，适合矩形圆角场景')
            .fontSize(12)
            .fontColor(0x666666)
          Text('• clipShape: 支持Circle/Ellipse/RoundRectangle等形状裁剪')
            .fontSize(12)
            .fontColor(0x666666)
          Text('• borderRadius设为宽高一半时可实现圆形效果')
            .fontSize(12)
            .fontColor(0x666666)
          Text('• clipShape支持不对称圆角，更灵活')
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
