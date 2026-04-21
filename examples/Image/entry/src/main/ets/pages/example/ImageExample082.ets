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
 * ImageExample082 - 图片跟随系统语言方向示例
 * 
 * 功能说明：
 * 1. matchTextDirection 属性 - 设置图片是否跟随系统语言方向
 * 2. 在 RTL 语言环境下显示镜像翻转显示效果
 * 3. AnimatedDrawableDescriptor 类型时不生效
 */

@Entry
@Component
struct ImageExample082 {
  @State matchDirection: boolean = false;
  @State currentDirection: string = 'LTR (从左到右)';
  @State showLTR: boolean = true;
  @State showRTL: boolean = true;

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('图片跟随系统语言方向示例')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 10 })
          .fontColor(0x333333)

        this.buildDescription()
        this.buildLTRDemo()
        this.buildRTLDemo()
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
      Text('matchTextDirection 属性说明')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Text('设置图片是否跟随系统语言方向，在 RTL 语言环境下显示镜像翻转显示效果。')
        .fontSize(14)
        .fontColor(0x666666)

      Text('重要特性：')
        .fontSize(14)
        .fontColor(0x666666)

      Text('• 在 RTL 语言环境下显示镜像翻转效果')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• 适用于多语言应用，特别是支持阿拉伯语、希伯来语等 RTL 语言')
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
  buildLTRDemo() {
    Column({ space: 15 }) {
      Text('LTR (从左到右) 模式')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Text('在从左到右的语言环境下显示图片')
        .fontSize(14)
        .fontColor(0x666666)

      Column({ space: 10 }) {
        Text('不跟随系统语言方向')
          .fontSize(14)
          .fontColor(0x333333)

        Image($r('app.media.background'))
          .width(300)
          .height(200)
          .matchTextDirection(false)
          .border({ width: 2, color: Color.Blue })
          .borderRadius(8)
          .backgroundColor(0xF0F0F0)

        Text('图片保持原始方向')
          .fontSize(12)
          .fontColor(0x666666)
      }
      .width('100%')
      .padding(15)
      .backgroundColor(0xFFFFFF)
      .borderRadius(10)
  }

  @Builder
  buildRTLDemo() {
    Column({ space: 15 }) {
      Text('RTL (从右到左) 模式')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Text('在从右到左的语言环境下显示镜像翻转效果')
        .fontSize(14)
        .fontColor(0x666666)

      Column({ space: 10 }) {
        Text('跟随系统语言方向')
          .fontSize(14)
          .fontColor(0x333333)

        Image($r('app.media.background'))
          .width(300)
          .height(200)
          .matchTextDirection(true)
          .border({ width: 2, color: Color.Green })
          .borderRadius(8)
          .backgroundColor(0xF0F0F0)

        Text('在 RTL 环境下图片会镜像翻转')
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
          Text('不跟随 (false)')
            .fontSize(14)
            .fontColor(0x333333)

          Image($r('app.media.background'))
            .width(200)
            .height(150)
            .matchTextDirection(false)
            .border({ width: 2, color: Color.Blue })
            .borderRadius(8)
            .backgroundColor(0xF0F0F0)

          Text('图片保持原始方向')
            .fontSize(12)
            .fontColor(0x666666)
        }

        Column({ space: 10 }) {
          Text('跟随 (true)')
            .fontSize(14)
            .fontColor(0x333333)

          Image($r('app.media.background'))
            .width(200)
            .height(150)
            .matchTextDirection(true)
            .border({ width: 2, color: Color.Green })
            .borderRadius(8)
            .backgroundColor(0xF0F0F0)

          Text('RTL 环境下镜像翻转')
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
        Text('• 多语言应用')
          .fontSize(14)
          .fontColor(0x333333)
        Text('对于支持 RTL 语言的应用，应开启此功能')
          .fontSize(12)
          .fontColor(0x666666)
      }

      Column({ space: 10 }) {
        Text('• 方向性图片')
          .fontSize(14)
          .fontColor(0x333333)
        Text('对于箭头、手势等方向性图片，建议开启')
          .fontSize(12)
          .fontColor(0x666666)
      }

      Column({ space: 10 }) {
        Text('• 对称图片')
          .fontSize(14)
          .fontColor(0x333333)
        Text('对于对称图片（如圆形、正方形），可以关闭')
          .fontSize(12)
          .fontColor(0x666666)
      }

      Column({ space: 10 }) {
        Text('• 图标')
          .fontSize(14)
          .fontColor(0x333333)
        Text('图标通常需要跟随语言方向翻转')
          .fontSize(12)
          .fontColor(0x666666)
      }

      Column({ space: 10 }) {
        Text('• 照片和图片')
          .fontSize(14)
          .fontColor(0x333333)
        Text('照片和风景图片通常不需要翻转')
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
        Text('当前模式：' + this.currentDirection)
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .fontColor(0x333333)

        Image($r('app.media.background'))
          .width(350)
          .height(250)
          .matchTextDirection(this.matchDirection)
          .border({ width: 2, color: Color.Red })
          .borderRadius(8)
          .backgroundColor(0xF0F0F0)
      }
      .width('100%')
      .padding(15)
      .backgroundColor(0xFFFFFF)
      .borderRadius(10)

      Row({ space: 10 }) {
        Button('不跟随系统语言方向')
          .width(200)
          .onClick(() => {
            this.matchDirection = false;
            this.currentDirection = '不跟随系统语言方向';
          })

        Button('跟随系统语言方向')
          .width(200)
          .onClick(() => {
            this.matchDirection = true;
            this.currentDirection = '跟随系统语言方向';
          })
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceEvenly)
      .padding(15)
      .backgroundColor(0xF0F0F0)
      .borderRadius(10)

      Column({ space: 10 }) {
        Text('说明')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .fontColor(0x333333)

        Text('在实际 RTL 语言环境中，设置 matchTextDirection(true) 的图片会自动镜像翻转')
          .fontSize(14)
          .fontColor(0x666666)

        Text('支持 RTL 的语言包括：阿拉伯语、希伯来语、波斯语、乌尔都语等')
          .fontSize(14)
          .fontColor(0x666666)
      }
      .width('100%')
      .padding(15)
      .backgroundColor(0xFFFFFF)
      .borderRadius(10)
  }
}
