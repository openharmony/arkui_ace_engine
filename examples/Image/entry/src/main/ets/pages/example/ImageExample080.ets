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
 * ImageExample080 - 图片重复样式示例
 * 
 * 功能说明：
 * 1. objectRepeat 属性 - 设置图片的重复样式，从中心点向两边重复
 * 2. 剩余空间不足放下一张图片时会截断
 * 3. SVG 类型图源不支持该属性
 * 4. AnimatedDrawableDescriptor 类型时不生效
 * 
 * ImageRepeat 枚举值：
 * - ImageRepeat.NoRepeat - 不重复
 * - ImageRepeat.X - 水平重复
 * - ImageRepeat.Y - 垂直重复
 * - ImageRepeat.XY - 水平和垂直重复
 */

@Entry
@Component
struct ImageExample080 {
  @State currentRepeat: ImageRepeat = ImageRepeat.NoRepeat;
  @State selectedMode: string = 'NoRepeat';
  @State showDescription: boolean = true;
  @State showComparison: boolean = true;
  @State showBestPractices: boolean = true;

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('图片重复样式示例')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 10 })
          .fontColor(0x333333)

        this.buildDescription()
        this.buildNoRepeatDemo()
        this.buildHorizontalRepeatDemo()
        this.buildVerticalRepeatDemo()
        this.buildXYRepeatDemo()
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
      Text('objectRepeat 属性说明')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Text('设置图片的重复样式，从中心点向两边重复。')
        .fontSize(14)
        .fontColor(0x666666)

      Text('重要特性：')
        .fontSize(14)
        .fontColor(0x666666)

      Text('• 从中心点向两边重复')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• 剩余空间不足放下一张图片时会截断')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• SVG 类型图源不支持该属性')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• AnimatedDrawableDescriptor 类型时不生效')
        .fontSize(12)
        .fontColor(0x999999)

      Text('ImageRepeat 枚举值：')
        .fontSize(14)
        .fontColor(0x666666)

      Text('• ImageRepeat.NoRepeat - 不重复')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• ImageRepeat.X - 水平重复')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• ImageRepeat.Y - 垂直重复')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• ImageRepeat.XY - 水平和垂直重复')
        .fontSize(12)
        .fontColor(0x999999)
    }
    .width('100%')
    .padding(15)
    .backgroundColor(0xFFFFFF)
    .borderRadius(10)
  }

  @Builder
  buildNoRepeatDemo() {
    Column({ space: 15 }) {
      Text('不重复模式 (ImageRepeat.NoRepeat)')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Text('图片只显示一次，不进行重复')
        .fontSize(14)
        .fontColor(0x666666)

      Column({ space: 10 }) {
        Image($r('app.media.background'))
          .width(300)
          .height(200)
          .objectRepeat(ImageRepeat.NoRepeat)
          .border({ width: 2, color: Color.Blue })
          .borderRadius(8)
          .backgroundColor(0xF0F0F0)

        Text('图片只显示一次')
          .fontSize(12)
          .fontColor(0x666666)
      }
      .width('100%')
      .padding(15)
      .backgroundColor(0xFFFFFF)
      .borderRadius(10)
  }

  @Builder
  buildHorizontalRepeatDemo() {
    Column({ space: 15 }) {
      Text('水平重复模式 (ImageRepeat.X)')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Text('图片在水平方向上重复显示')
        .fontSize(14)
        .fontColor(0x666666)

      Column({ space: 10 }) {
        Image($r('app.media.background'))
          .width(400)
          .height(100)
          .objectRepeat(ImageRepeat.X)
          .border({ width: 2, color: Color.Green })
          .borderRadius(8)
          .backgroundColor(0xF0F0F0)

        Text('图片在水平方向重复，从中心向两边扩展')
          .fontSize(12)
          .fontColor(0x666666)
      }
      .width('100%')
      .padding(15)
      .backgroundColor(0xFFFFFF)
      .borderRadius(10)
  }

  @Builder
  buildVerticalRepeatDemo() {
    Column({ space: 15 }) {
      Text('垂直重复模式 (ImageRepeat.Y)')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Text('图片在垂直方向上重复显示')
        .fontSize(14)
        .fontColor(0x666666)

      Column({ space: 10 }) {
        Image($r('app.media.background'))
          .width(100)
          .height(300)
          .objectRepeat(ImageRepeat.Y)
          .border({ width: 2, color: Color.Orange })
          .borderRadius(8)
          .backgroundColor(0xF0F0F0)

        Text('图片在垂直方向重复，从中心向两边扩展')
          .fontSize(12)
          .fontColor(0x666666)
      }
      .width('100%')
      .padding(15)
      .backgroundColor(0xFFFFFF)
      .borderRadius(10)
  }

  @Builder
  buildXYRepeatDemo() {
    Column({ space: 15 }) {
      Text('双向重复模式 (ImageRepeat.XY)')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Text('图片在水平和垂直方向上都重复显示')
        .fontSize(14)
        .fontColor(0x666666)

      Column({ space: 10 }) {
        Image($r('app.media.background'))
          .width(400)
          .height(300)
          .objectRepeat(ImageRepeat.XY)
          .border({ width: 2, color: Color.Purple })
          .borderRadius(8)
          .backgroundColor(0xF0F0F0)

        Text('图片在水平和垂直方向都重复，从中心向四周扩展')
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

      Row({ space: 15 }) {
        Column({ space: 10 }) {
          Text('NoRepeat')
            .fontSize(14)
            .fontColor(0x333333)

          Image($r('app.media.background'))
            .width(200)
            .height(150)
            .objectRepeat(ImageRepeat.NoRepeat)
            .border({ width: 2, color: Color.Blue })
            .borderRadius(8)
            .backgroundColor(0xF0F0F0)
        }

        Column({ space: 10 }) {
          Text('X')
            .fontSize(14)
            .fontColor(0x333333)

          Image($r('app.media.background'))
            .width(200)
            .height(150)
            .objectRepeat(ImageRepeat.X)
            .border({ width: 2, color: Color.Green })
            .borderRadius(8)
            .backgroundColor(0xF0F0F0)
        }

        Column({ space: 10 }) {
          Text('Y')
            .fontSize(14)
            .fontColor(0x333333)

          Image($r('app.media.background'))
            .width(200)
            .height(150)
            .objectRepeat(ImageRepeat.Y)
            .border({ width: 2, color: Color.Orange })
            .borderRadius(8)
            .backgroundColor(0xF0F0F0)
        }

        Column({ space: 10 }) {
          Text('XY')
            .fontSize(14)
            .fontColor(0x333333)

          Image($r('app.media.background'))
            .width(200)
            .height(150)
            .objectRepeat(ImageRepeat.XY)
            .border({ width: 2, color: Color.Purple })
            .borderRadius(8)
            .backgroundColor(0xF0F0F0)
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
        Text('• 背景图案')
          .fontSize(14)
          .fontColor(0x333333)
        Text('使用 ImageRepeat.XY 创建平铺背景效果')
          .fontSize(12)
          .fontColor(0x666666)
      }

      Column({ space: 10 }) {
        Text('• 边框装饰')
          .fontSize(14)
          .fontColor(0x333333)
        Text('使用 ImageRepeat.X 或 ImageRepeat.Y 创建边框效果')
          .fontSize(12)
          .fontColor(0x666666)
      }

      Column({ space: 10 }) {
        Text('• 性能优化')
          .fontSize(14)
          .fontColor(0x333333)
        Text('使用小尺寸图片进行重复，减少内存占用')
          .fontSize(12)
          .fontColor(0x666666)
      }

      Column({ space: 10 }) {
        Text('• 限制条件')
          .fontSize(14)
          .fontColor(0x333333)
        Text('SVG 图片不支持重复功能')
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
        Text('当前模式：' + this.selectedMode)
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .fontColor(0x333333)

        Image($r('app.media.background'))
          .width(350)
          .height(250)
          .objectRepeat(this.currentRepeat)
          .border({ width: 2, color: Color.Red })
          .borderRadius(8)
          .backgroundColor(0xF0F0F0)
      }
      .width('100%')
      .padding(15)
      .backgroundColor(0xFFFFFF)
      .borderRadius(10)

      Row({ space: 10 }) {
        Button('NoRepeat')
          .width(100)
          .onClick(() => {
            this.currentRepeat = ImageRepeat.NoRepeat;
            this.selectedMode = 'NoRepeat';
          })

        Button('X')
          .width(100)
          .onClick(() => {
            this.currentRepeat = ImageRepeat.X;
            this.selectedMode = 'X';
          })

        Button('Y')
          .width(100)
          .onClick(() => {
            this.currentRepeat = ImageRepeat.Y;
            this.selectedMode = 'Y';
          })

        Button('XY')
          .width(100)
          .onClick(() => {
            this.currentRepeat = ImageRepeat.XY;
            this.selectedMode = 'XY';
          })
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceEvenly)
      .padding(15)
      .backgroundColor(0xF0F0F0)
      .borderRadius(10)
  }
}
