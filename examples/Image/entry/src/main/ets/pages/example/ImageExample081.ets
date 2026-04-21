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
 * ImageExample081 - 图片插值效果示例
 * 
 * 功能说明：
 * 1. interpolation 属性 - 设置图片的插值效果，缓解图片在缩放时的锯齿问题
 * 2. SVG 类型图源不支持该属性
 * 3. AnimatedDrawableDescriptor 类型时不生效
 * 
 * ImageInterpolation 枚举值：
 * - ImageInterpolation.None - 最近邻插值
 * - ImageInterpolation.Low - 双线性插值
 * - ImageInterpolation.Medium - MipMap 插值
 * - ImageInterpolation.High - 三次插值，插值质量最高，可能会影响图片渲染的速度
 */

@Entry
@Component
struct ImageExample081 {
  @State currentInterpolation: ImageInterpolation = ImageInterpolation.None;
  @State selectedMode: string = 'None';
  @State imageScale: number = 1.0;

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('图片插值效果示例')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 10 })
          .fontColor(0x333333)

        this.buildDescription()
        this.buildNoneInterpolationDemo()
        this.buildLowInterpolationDemo()
        this.buildMediumInterpolationDemo()
        this.buildHighInterpolationDemo()
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
      Text('interpolation 属性说明')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Text('设置图片的插值效果，缓解图片在缩放时的锯齿问题。')
        .fontSize(14)
        .fontColor(0x666666)

      Text('重要特性：')
        .fontSize(14)
        .fontColor(0x666666)

      Text('• 缓解图片在缩放时的锯齿问题')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• SVG 类型图源不支持该属性')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• AnimatedDrawableDescriptor 类型时不生效')
        .fontSize(12)
        .fontColor(0x999999)

      Text('ImageInterpolation 枚举值：')
        .fontSize(14)
        .fontColor(0x666666)

      Text('• ImageInterpolation.None - 最近邻插值')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• ImageInterpolation.Low - 双线性插值')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• ImageInterpolation.Medium - MipMap 插值')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• ImageInterpolation.High - 三次插值，插值质量最高')
        .fontSize(12)
        .fontColor(0x999999)
    }
    .width('100%')
    .padding(15)
    .backgroundColor(0xFFFFFF)
    .borderRadius(10)
  }

  @Builder
  buildNoneInterpolationDemo() {
    Column({ space: 15 }) {
      Text('最近邻插值 (ImageInterpolation.None)')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Text('使用最近邻插值，速度最快但可能有锯齿')
        .fontSize(14)
        .fontColor(0x666666)

      Column({ space: 10 }) {
        Image($r('app.media.background'))
          .width(300)
          .height(200)
          .interpolation(ImageInterpolation.None)
          .border({ width: 2, color: Color.Blue })
          .borderRadius(8)
          .backgroundColor(0xF0F0F0)

        Text('最近邻插值 - 速度最快')
          .fontSize(12)
          .fontColor(0x666666)
      }
      .width('100%')
      .padding(15)
      .backgroundColor(0xFFFFFF)
      .borderRadius(10)
  }

  @Builder
  buildLowInterpolationDemo() {
    Column({ space: 15 }) {
      Text('双线性插值 (ImageInterpolation.Low)')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Text('使用双线性插值，平衡性能和质量')
        .fontSize(14)
        .fontColor(0x666666)

      Column({ space: 10 }) {
        Image($r('app.media.background'))
          .width(300)
          .height(200)
          .interpolation(ImageInterpolation.Low)
          .border({ width: 2, color: Color.Green })
          .borderRadius(8)
          .backgroundColor(0xF0F0F0)

        Text('双线性插值 - 平衡性能和质量')
          .fontSize(12)
          .fontColor(0x666666)
      }
      .width('100%')
      .padding(15)
      .backgroundColor(0xFFFFFF)
      .borderRadius(10)
  }

  @Builder
  buildMediumInterpolationDemo() {
    Column({ space: 15 }) {
      Text('MipMap 插值 (ImageInterpolation.Medium)')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Text('使用 MipMap 插值，适合缩小显示')
        .fontSize(14)
        .fontColor(0x666666)

      Column({ space: 10 }) {
        Image($r('app.media.background'))
          .width(300)
          .height(200)
          .interpolation(ImageInterpolation.Medium)
          .border({ width: 2, color: Color.Orange })
          .borderRadius(8)
          .backgroundColor(0xF0F0F0)

        Text('MipMap 插值 - 适合缩小显示')
          .fontSize(12)
          .fontColor(0x666666)
      }
      .width('100%')
      .padding(15)
      .backgroundColor(0xFFFFFF)
      .borderRadius(10)
  }

  @Builder
  buildHighInterpolationDemo() {
    Column({ space: 15 }) {
      Text('三次插值 (ImageInterpolation.High)')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Text('使用三次插值，质量最高但可能影响渲染速度')
        .fontSize(14)
        .fontColor(0x666666)

      Column({ space: 10 }) {
        Image($r('app.media.background'))
          .width(300)
          .height(200)
          .interpolation(ImageInterpolation.High)
          .border({ width: 2, color: Color.Purple })
          .borderRadius(8)
          .backgroundColor(0xF0F0F0)

        Text('三次插值 - 质量最高')
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
      Text('插值模式对比')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Row({ space: 15 }) {
        Column({ space: 10 }) {
          Text('None')
            .fontSize(14)
            .fontColor(0x333333)

          Image($r('app.media.background'))
            .width(150)
            .height(100)
            .interpolation(ImageInterpolation.None)
            .border({ width: 2, color: Color.Blue })
            .borderRadius(8)
        }

        Column({ space: 10 }) {
          Text('Low')
            .fontSize(14)
            .fontColor(0x333333)

          Image($r('app.media.background'))
            .width(150)
            .height(100)
            .interpolation(ImageInterpolation.Low)
            .border({ width: 2, color: Color.Green })
            .borderRadius(8)
        }

        Column({ space: 10 }) {
          Text('Medium')
            .fontSize(14)
            .fontColor(0x333333)

          Image($r('app.media.background'))
            .width(150)
            .height(100)
            .interpolation(ImageInterpolation.Medium)
            .border({ width: 2, color: Color.Orange })
            .borderRadius(8)
        }

        Column({ space: 10 }) {
          Text('High')
            .fontSize(14)
            .fontColor(0x333333)

          Image($r('app.media.background'))
            .width(150)
            .height(100)
            .interpolation(ImageInterpolation.High)
            .border({ width: 2, color: Color.Purple })
            .borderRadius(8)
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
        Text('• 性能优先')
          .fontSize(14)
          .fontColor(0x333333)
        Text('使用 ImageInterpolation.None 或 Low 获得最佳性能')
          .fontSize(12)
          .fontColor(0x666666)
      }

      Column({ space: 10 }) {
        Text('• 质量优先')
          .fontSize(14)
          .fontColor(0x333333)
        Text('使用 ImageInterpolation.High 获得最佳显示质量')
          .fontSize(12)
          .fontColor(0x666666)
      }

      Column({ space: 10 }) {
        Text('• 缩小显示')
          .fontSize(14)
          .fontColor(0x333333)
        Text('使用 ImageInterpolation.Medium 适合缩小显示的图片')
          .fontSize(12)
          .fontColor(0x666666)
      }

      Column({ space: 10 }) {
        Text('• 放大显示')
          .fontSize(14)
          .fontColor(0x333333)
        Text('使用 ImageInterpolation.High 减少放大时的锯齿')
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
          .width(300 * this.imageScale)
          .height(200 * this.imageScale)
          .interpolation(this.currentInterpolation)
          .border({ width: 2, color: Color.Red })
          .borderRadius(8)
          .backgroundColor(0xF0F0F0)
      }
      .width('100%')
      .padding(15)
      .backgroundColor(0xFFFFFF)
      .borderRadius(10)

      Row({ space: 10 }) {
        Button('None')
          .width(80)
          .onClick(() => {
            this.currentInterpolation = ImageInterpolation.None;
            this.selectedMode = 'None';
          })

        Button('Low')
          .width(80)
          .onClick(() => {
            this.currentInterpolation = ImageInterpolation.Low;
            this.selectedMode = 'Low';
          })

        Button('Medium')
          .width(80)
          .onClick(() => {
            this.currentInterpolation = ImageInterpolation.Medium;
            this.selectedMode = 'Medium';
          })

        Button('High')
          .width(80)
          .onClick(() => {
            this.currentInterpolation = ImageInterpolation.High;
            this.selectedMode = 'High';
          })
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceEvenly)
      .padding(15)
      .backgroundColor(0xF0F0F0)
      .borderRadius(10)

      Column({ space: 10 }) {
        Text('缩放比例：' + this.imageScale.toFixed(2))
          .fontSize(14)
          .fontColor(0x333333)

        Slider({
          min: 0.5,
          max: 2.0,
          value: this.imageScale,
          step: 0.1
        })
          .width('100%')
          .onChange((value: number) => {
            this.imageScale = value;
          })
      }
      .width('100%')
      .padding(15)
      .backgroundColor(0xF0F0F0)
      .borderRadius(10)
  }
}
