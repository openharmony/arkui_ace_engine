/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
 * ImageExample087 - 图片可调整大小示例
 * 
 * 功能说明：
 * 1. resizable 属性 - 设置图像拉伸时可调整大小的图像选项
 * 2. 拉伸对拖拽缩略图以及占位图有效
 * 3. AnimatedDrawableDescriptor 和 SVG 时不生效
 * 
 * ResizableOptions 属性：
 * - slice: 切片区域，包含 top、bottom、left、right
 * - 当设置 top + bottom 大于原图的高或者 left + right 大于原图的宽时，ResizableOptions 属性设置不生效
 */

@Entry
@Component
struct ImageExample087 {
  @State useResizable: boolean = false;
  @State currentMode: string = '不可调整大小';
  @State sliceTop: number = 20;
  @State sliceBottom: number = 20;
  @State sliceLeft: number = 20;
  @State sliceRight: number = 20;

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('图片可调整大小示例')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 10 })
          .fontColor(0x333333)

        this.buildDescription()
        this.buildNonResizableDemo()
        this.buildResizableDemo()
        this.buildComparisonDemo()
        this.buildBestPractices()
        this.buildInteractiveDemo()
      }
      .width('100%')
      .padding({ left: 20, right: 20, bottom: 20 })
    }
    .width('100%')
    .height('100%')
    .backgroundColor(0xF5F5F5)
  }

  @Builder
  buildDescription() {
    Column({ space: 10 }) {
      Text('resizable 属性说明')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Text('设置图像拉伸时可调整大小的图像选项。拉伸对拖拽缩略图以及占位图有效。')
        .fontSize(14)
        .fontColor(0x666666)

      Text('重要特性：')
        .fontSize(14)
        .fontColor(0x666666)

      Text('• 支持九宫格拉伸效果')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• AnimatedDrawableDescriptor 和 SVG 时不生效')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• 当设置 top + bottom 大于原图的高或者 left + right 大于原图的宽时，ResizableOptions 属性设置不生效')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• 设置合法的 ResizableOptions 时，objectRepeat 属性、antialiased 属性和 orientation 属性设置不生效')
        .fontSize(12)
        .fontColor(0x999999)

      Text('ResizableOptions 属性：')
        .fontSize(14)
        .fontColor(0x666666)

      Text('• slice: 切片区域，包含 top、bottom、left、right')
        .fontSize(12)
        .fontColor(0x999999)
    }
    .width('100%')
    .padding(15)
    .backgroundColor(0xFFFFFF)
    .borderRadius(10)
  }

  @Builder
  buildNonResizableDemo() {
    Column({ space: 15 }) {
      Text('不可调整大小模式')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Text('图片正常显示，不使用可调整大小功能')
        .fontSize(14)
        .fontColor(0x666666)

      Column({ space: 10 }) {
        Image($r('app.media.background'))
          .width(300)
          .height(200)
          .border({ width: 2, color: Color.Blue })
          .borderRadius(8)
          .backgroundColor(0xF0F0F0)

        Text('图片正常显示')
          .fontSize(12)
          .fontColor(0x666666)
      }
      .width('100%')
      .padding(15)
      .backgroundColor(0xFFFFFF)
      .borderRadius(10)
  }

  @Builder
  buildResizableDemo() {
    Column({ space: 15 }) {
      Text('可调整大小模式')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Text('图片使用九宫格拉伸效果')
        .fontSize(14)
        .fontColor(0x666666)

      Column({ space: 10 }) {
        Image($r('app.media.background'))
          .width(300)
          .height(200)
          .resizable({
            slice: { top: 20, bottom: 20, left: 20, right: 20 }
          })
          .border({ width: 2, color: Color.Green })
          .borderRadius(8)
          .backgroundColor(0xF0F0F0)

        Text('九宫格拉伸：top:20, bottom:20, left:20, right:20')
          .fontSize(12)
          .fontColor(0x666666)
      }
      .width('100%')
      .padding(15)
      .backgroundColor(0xFFFFFF)
      .borderRadius(10)
  }

  @Builder
  buildComparisonDemo() {
    Column({ space: 15 }) {
      Text('模式对比')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Row({ space: 20 }) {
        Column({ space: 10 }) {
          Text('不可调整大小')
            .fontSize(14)
            .fontColor(0x333333)

          Image($r('app.media.background'))
            .width(150)
            .height(100)
            .border({ width: 2, color: Color.Blue })
            .borderRadius(8)
            .backgroundColor(0xF0F0F0)

          Text('正常显示')
            .fontSize(12)
            .fontColor(0x666666)
        }

        Column({ space: 10 }) {
          Text('可调整大小')
            .fontSize(14)
            .fontColor(0x333333)

          Image($r('app.media.background'))
            .width(150)
            .height(100)
            .resizable({
              slice: { top: 15, bottom: 15, left: 15, right: 15 }
            })
            .border({ width: 2, color: Color.Green })
            .borderRadius(8)
            .backgroundColor(0xF0F0F0)

          Text('九宫格拉伸')
            .fontSize(12)
            .fontColor(0x666666)
        }
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceEvenly)
    }
    .width('100%')
    .padding(15)
    .backgroundColor(0xFFFFFF)
    .borderRadius(10)
  }

  @Builder
  buildBestPractices() {
    Column({ space: 15 }) {
      Text('最佳实践建议')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Column({ space: 10 }) {
        Text('• 按钮背景')
          .fontSize(14)
          .fontColor(0x333333)
        Text('使用九宫格拉伸创建自适应按钮背景')
          .fontSize(12)
          .fontColor(0x666666)
      }

      Column({ space: 10 }) {
        Text('• 对话框背景')
          .fontSize(14)
          .fontColor(0x333333)
        Text('使用九宫格拉伸创建自适应对话框背景')
          .fontSize(12)
          .fontColor(0x666666)
      }

      Column({ space: 10 }) {
        Text('• 边框装饰')
          .fontSize(14)
          .fontColor(0x333333)
        Text('使用九宫格拉伸创建自适应边框')
          .fontSize(12)
          .fontColor(0x666666)
      }

      Column({ space: 10 }) {
        Text('• 切片区域')
          .fontSize(14)
          .fontColor(0x333333)
        Text('合理设置切片区域，确保拉伸效果自然')
          .fontSize(12)
          .fontColor(0x666666)
      }

      Column({ space: 10 }) {
        Text('• 限制条件')
          .fontSize(14)
          .fontColor(0x333333)
        Text('确保 top + bottom 不大于图片高度，left + right 不大于图片宽度')
          .fontSize(12)
          .fontColor(0x666666)
      }
    }
    .width('100%')
    .padding(15)
    .backgroundColor(0xFFFFFF)
    .borderRadius(10)
  }

  @Builder
  buildInteractiveDemo() {
    Column({ space: 15 }) {
      Text('交互式演示')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Column({ space: 10 }) {
        Text('当前模式：' + this.currentMode)
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .fontColor(0x333333)

        if (this.useResizable) {
          Image($r('app.media.background'))
            .width(350)
            .height(250)
            .resizable({
              slice: { top: this.sliceTop, bottom: this.sliceBottom, left: this.sliceLeft, right: this.sliceRight }
            })
            .border({ width: 2, color: Color.Red })
            .borderRadius(8)
            .backgroundColor(0xF0F0F0)

          Text('切片区域：top:' + this.sliceTop + ' bottom:' + this.sliceBottom + ' left:' + this.sliceLeft + ' right:' + this.sliceRight)
            .fontSize(12)
            .fontColor(0x666666)
        } else {
          Image($r('app.media.background'))
            .width(350)
            .height(250)
            .border({ width: 2, color: Color.Red })
            .borderRadius(8)
            .backgroundColor(0xF0F0F0)

          Text('图片正常显示')
            .fontSize(12)
            .fontColor(0x666666)
        }
      }
      .width('100%')
      .padding(15)
      .backgroundColor(0xFFFFFF)
      .borderRadius(10)

      Row({ space: 10 }) {
        Button('不可调整大小')
          .width(150)
          .onClick(() => {
            this.useResizable = false;
            this.currentMode = '不可调整大小';
          })

        Button('可调整大小')
          .width(150)
          .onClick(() => {
            this.useResizable = true;
            this.currentMode = '可调整大小';
          })
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceEvenly)
      .padding(15)
      .backgroundColor(0xF0F0F0)
      .borderRadius(10)

      if (this.useResizable) {
        Column({ space: 10 }) {
          Text('切片区域设置')
            .fontSize(16)
            .fontWeight(FontWeight.Medium)
            .fontColor(0x333333)

          Text('Top: ' + this.sliceTop)
            .fontSize(14)
            .fontColor(0x333333)

          Slider({
            min: 0,
            max: 50,
            value: this.sliceTop,
            step: 5
          })
            .width('100%')
            .onChange((value: number) => {
              this.sliceTop = value;
            })

          Text('Bottom: ' + this.sliceBottom)
            .fontSize(14)
            .fontColor(0x333333)

          Slider({
            min: 0,
            max: 50,
            value: this.sliceBottom,
            step: 5
          })
            .width('100%')
            .onChange((value: number) => {
              this.sliceBottom = value;
            })

          Text('Left: ' + this.sliceLeft)
            .fontSize(14)
            .fontColor(0x333333)

          Slider({
            min: 0,
            max: 50,
            value: this.sliceLeft,
            step: 5
          })
            .width('100%')
            .onChange((value: number) => {
              this.sliceLeft = value;
            })

          Text('Right: ' + this.sliceRight)
            .fontSize(14)
            .fontColor(0x333333)

          Slider({
            min: 0,
            max: 50,
            value: this.sliceRight,
            step: 5
          })
            .width('100%')
            .onChange((value: number) => {
              this.sliceRight = value;
            })
        }
        .width('100%')
        .padding(15)
        .backgroundColor(0xF0F0F0)
        .borderRadius(10)
      }
  }
}
