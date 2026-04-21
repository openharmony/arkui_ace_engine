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
 * ImageExample083 - 图片图片源尺寸示例
 * 
 * 功能说明：
 * 1. fitOriginalSize 属性 - 设置图片的显示尺寸是否跟随图源尺寸
 * 2. 图片组件已设置 width、height 属性时，fitOriginalSize 属性不生效
 * 3. AnimatedDrawableDescriptor 类型时不生效
 */

@Entry
@Component
struct ImageExample083 {
  @State useOriginalSize: boolean = false;
  @State currentMode: string = '自定义尺寸';
  @State customWidth: number = 200;
  @State customHeight: number = 150;

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('图片图片源尺寸示例')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 10 })
          .fontColor(0x333333)

        this.buildDescription()
        this.buildCustomSizeDemo()
        this.buildOriginalSizeDemo()
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
      Text('fitOriginalSize 属性说明')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Text('设置图片的显示尺寸是否跟随图源尺寸。')
        .fontSize(14)
        .fontColor(0x666666)

      Text('重要特性：')
        .fontSize(14)
        .fontColor(0x666666)

      Text('• true：图片显示尺寸跟随图源尺寸')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• false：图片显示尺寸由组件的 width 和 height 属性决定')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• 图片组件已设置 width、height 属性时，fitOriginalSize 属性不生效')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• AnimatedDrawableDescriptor 类型时不生效')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• 默认值为 false')
        .fontSize(12)
        .fontColor(0x999999)
    }
    .width('100%')
    .padding(15)
    .backgroundColor(0xFFFFFF)
    .borderRadius(10)
  }

  @Builder
  buildCustomSizeDemo() {
    Column({ space: 15 }) {
      Text('自定义尺寸模式 (fitOriginalSize = false)')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Text('图片显示尺寸由组件的 width 和 height 属性决定')
        .fontSize(14)
        .fontColor(0x666666)

      Column({ space: 10 }) {
        Image($r('app.media.background'))
          .width(300)
          .height(200)
          .fitOriginalSize(false)
          .border({ width: 2, color: Color.Blue })
          .borderRadius(8)
          .backgroundColor(0xF0F0F0)

        Text('图片显示尺寸：300 x 200')
          .fontSize(12)
          .fontColor(0x666666)
      }
      .width('100%')
      .padding(15)
      .backgroundColor(0xFFFFFF)
      .borderRadius(10)
  }

  @Builder
  buildOriginalSizeDemo() {
    Column({ space: 15 }) {
      Text('原图尺寸模式 (fitOriginalSize = true)')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Text('图片显示尺寸跟随图源尺寸')
        .fontSize(14)
        .fontColor(0x666666)

      Column({ space: 10 }) {
        Image($r('app.media.background'))
          .fitOriginalSize(true)
          .border({ width: 2, color: Color.Green })
          .borderRadius(8)
          .backgroundColor(0xF0F0F0)

        Text('图片显示尺寸：跟随图源尺寸')
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
          Text('自定义尺寸')
            .fontSize(14)
            .fontColor(0x333333)

          Image($r('app.media.background'))
            .width(150)
            .height(100)
            .fitOriginalSize(false)
            .border({ width: 2, color: Color.Blue })
            .borderRadius(8)
            .backgroundColor(0xF0F0F0)

          Text('150 x 100')
            .fontSize(12)
            .fontColor(0x666666)
        }

        Column({ space: 10 }) {
          Text('原图尺寸')
            .fontSize(14)
            .fontColor(0x333333)

          Image($r('app.media.background'))
            .fitOriginalSize(true)
            .border({ width: 2, color: Color.Green })
            .borderRadius(8)
            .backgroundColor(0xF0F0F0)

          Text('跟随图源')
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
        Text('• 响应式布局')
          .fontSize(14)
          .fontColor(0x333333)
        Text('使用自定义尺寸模式，让图片适应不同屏幕尺寸')
          .fontSize(12)
          .fontColor(0x666666)
      }

      Column({ space: 10 }) {
        Text('• 原图显示')
          .fontSize(14)
          .fontColor(0x333333)
        Text('需要显示图片原始分辨率时，使用原图尺寸模式')
          .fontSize(12)
          .fontColor(0x666666)
      }

      Column({ space: 10 }) {
        Text('• 高清图片')
          .fontSize(14)
          .fontColor(0x333333)
        Text('对于高清图片，建议使用原图尺寸模式以保持清晰度')
          .fontSize(12)
          .fontColor(0x666666)
      }

      Column({ space: 10 }) {
        Text('• 缩略图')
          .fontSize(14)
          .fontColor(0x333333)
        Text('对于缩略图，使用自定义尺寸模式以节省空间')
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

        if (this.useOriginalSize) {
          Image($r('app.media.background'))
            .fitOriginalSize(true)
            .border({ width: 2, color: Color.Red })
            .borderRadius(8)
            .backgroundColor(0xF0F0F0)
        } else {
          Image($r('app.media.background'))
            .width(this.customWidth)
            .height(this.customHeight)
            .fitOriginalSize(false)
            .border({ width: 2, color: Color.Red })
            .borderRadius(8)
            .backgroundColor(0xF0F0F0)
        }
      }
      .width('100%')
      .padding(15)
      .backgroundColor(0xFFFFFF)
      .borderRadius(10)

      Row({ space: 10 }) {
        Button('自定义尺寸')
          .width(150)
          .onClick(() => {
            this.useOriginalSize = false;
            this.currentMode = '自定义尺寸';
          })

        Button('原图尺寸')
          .width(150)
          .onClick(() => {
            this.useOriginalSize = true;
            this.currentMode = '原图尺寸';
          })
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceEvenly)
      .padding(15)
      .backgroundColor(0xF0F0F0)
      .borderRadius(10)

      if (!this.useOriginalSize) {
        Column({ space: 10 }) {
          Text('宽度：' + this.customWidth)
            .fontSize(14)
            .fontColor(0x333333)

          Slider({
            min: 100,
            max: 400,
            value: this.customWidth,
            step: 10
          })
            .width('100%')
            .onChange((value: number) => {
              this.customWidth = value;
            })

          Text('高度：' + this.customHeight)
            .fontSize(14)
            .fontColor(0x333333)

          Slider({
            min: 100,
            max: 400,
            value: this.customHeight,
            step: 10
          })
            .width('100%')
            .onChange((value: number) => {
              this.customHeight = value;
            })
        }
        .width('100%')
        .padding(15)
        .backgroundColor(0xF0F0F0)
        .borderRadius(10)
      }
  }
}
