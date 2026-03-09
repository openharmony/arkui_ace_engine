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
 * ImageExample092 - 图片内容过渡动效示例
 * 
 * 功能说明：
 * 1. contentTransition 属性 - 图片内容发生变化时，触发过渡动效
 * 2. 对动态图片资源不生效
 * 
 * ContentTransitionEffect 枚举值：
 * - ContentTransitionEffect.OPACITY - 淡入淡出效果
 * - ContentTransitionEffect.IDENTITY - 无动画效果
 */

@Entry
@Component
struct ImageExample092 {
  @State currentEffect: ContentTransitionEffect = ContentTransitionEffect.IDENTITY;
  @State selectedEffect: string = 'IDENTITY (无动画)';
  @State imageIndex: number = 0;
  @State images: Resource[] = [
    $r('app.media.startIcon'),
    $r('app.media.background'),
    $r('app.media.background'),
    $r('app.media.mix_png')
  ];

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('图片内容过渡动效示例')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 10 })
          .fontColor(0x333333)

        this.buildDescription()
        this.buildIdentityEffectDemo()
        this.buildOpacityEffectDemo()
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
      Text('contentTransition 属性说明')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Text('图片内容发生变化时，触发过渡动效。')
        .fontSize(14)
        .fontColor(0x666666)

      Text('重要特性：')
        .fontSize(14)
        .fontColor(0x666666)

      Text('• 对动态图片资源不生效')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• 支持淡入淡出过渡效果')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• 适用于图片切换场景')
        .fontSize(12)
        .fontColor(0x999999)

      Text('ContentTransitionEffect 枚举值：')
        .fontSize(14)
        .fontColor(0x666666)

      Text('• ContentTransitionEffect.OPACITY - 淡入淡出效果')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• ContentTransitionEffect.IDENTITY - 无动画效果')
        .fontSize(12)
        .fontColor(0x999999)
    }
    .width('100%')
    .padding(15)
    .backgroundColor(0xFFFFFF)
    .borderRadius(10)
  }

  @Builder
  buildIdentityEffectDemo() {
    Column({ space: 15 }) {
      Text('无动画效果 (ContentTransitionEffect.IDENTITY)')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Text('图片内容变化时无过渡动画')
        .fontSize(14)
        .fontColor(0x666666)

      Column({ space: 10 }) {
        Image(this.images[this.imageIndex])
          .width(300)
          .height(200)
          .contentTransition(ContentTransitionEffect.IDENTITY)
          .border({ width: 2, color: Color.Blue })
          .borderRadius(8)
          .backgroundColor(0xF0F0F0)

        Text('图片切换时无动画')
          .fontSize(12)
          .fontColor(0x666666)
      }
      .width('100%')
      .padding(15)
      .backgroundColor(0xFFFFFF)
      .borderRadius(10)
  }

  @Builder
  buildOpacityEffectDemo() {
    Column({ space: 15 }) {
      Text('淡入淡出效果 (ContentTransitionEffect.OPACITY)')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Text('图片内容变化时有淡入淡出过渡动画')
        .fontSize(14)
        .fontColor(0x666666)

      Column({ space: 10 }) {
        Image(this.images[this.imageIndex])
          .width(300)
          .height(200)
          .contentTransition(ContentTransitionEffect.OPACITY)
          .border({ width: 2, color: Color.Green })
          .borderRadius(8)
          .backgroundColor(0xF0F0F0)

        Text('图片切换时有淡入淡出动画')
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
      Text('过渡效果对比')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Row({ space: 20 }) {
        Column({ space: 10 }) {
          Text('IDENTITY')
            .fontSize(14)
            .fontColor(0x333333)

          Image(this.images[this.imageIndex])
            .width(150)
            .height(100)
            .contentTransition(ContentTransitionEffect.IDENTITY)
            .border({ width: 2, color: Color.Blue })
            .borderRadius(8)
            .backgroundColor(0xF0F0F0)

          Text('无动画')
            .fontSize(12)
            .fontColor(0x666666)
        }

        Column({ space: 10 }) {
          Text('OPACITY')
            .fontSize(14)
            .fontColor(0x333333)

          Image(this.images[this.imageIndex])
            .width(150)
            .height(100)
            .contentTransition(ContentTransitionEffect.OPACITY)
            .border({ width: 2, color: Color.Green })
            .borderRadius(8)
            .backgroundColor(0xF0F0F0)

          Text('淡入淡出')
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
        Text('• 图片轮播')
          .fontSize(14)
          .fontColor(0x333333)
        Text('使用 OPACITY 效果创建平滑的图片轮播')
          .fontSize(12)
          .fontColor(0x666666)
      }

      Column({ space: 10 }) {
        Text('• 快速切换')
          .fontSize(14)
          .fontColor(0x333333)
        Text('使用 IDENTITY 效果实现快速图片切换')
          .fontSize(12)
          .fontColor(0x666666)
      }

      Column({ space: 10 }) {
        Text('• 用户体验')
          .fontSize(14)
          .fontColor(0x333333)
        Text('淡入淡出效果提供更好的用户体验')
          .fontSize(12)
          .fontColor(0x666666)
      }

      Column({ space: 10 }) {
        Text('• 性能考虑')
          .fontSize(14)
          .fontColor(0x333333)
        Text('过渡动画会消耗一定的性能资源')
          .fontSize(12)
          .fontColor(0x666666)
      }

      Column({ space: 10 }) {
        Text('• 动态资源')
          .fontSize(14)
          .fontColor(0x333333)
        Text('此属性对动态图片资源不生效')
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
        Text('当前效果：' + this.selectedEffect)
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .fontColor(0x333333)

        Text('当前图片：' + (this.imageIndex + 1))
          .fontSize(14)
          .fontColor(0x666666)

        Image(this.images[this.imageIndex])
          .width(350)
          .height(250)
          .contentTransition(this.currentEffect)
          .border({ width: 2, color: Color.Red })
          .borderRadius(8)
          .backgroundColor(0xF0F0F0)
      }
      .width('100%')
      .padding(15)
      .backgroundColor(0xFFFFFF)
      .borderRadius(10)

      Row({ space: 10 }) {
        Button('IDENTITY')
          .width(120)
          .onClick(() => {
            this.currentEffect = ContentTransitionEffect.IDENTITY;
            this.selectedEffect = 'IDENTITY (无动画)';
          })

        Button('OPACITY')
          .width(120)
          .onClick(() => {
            this.currentEffect = ContentTransitionEffect.OPACITY;
            this.selectedEffect = 'OPACITY (淡入淡出)';
          })
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceEvenly)
      .padding(15)
      .backgroundColor(0xF0F0F0)
      .borderRadius(10)

      Row({ space: 10 }) {
        Button('上一张')
          .width(120)
          .onClick(() => {
            this.imageIndex = (this.imageIndex - 1 + this.images.length) % this.images.length;
          })

        Button('下一张')
          .width(120)
          .onClick(() => {
            this.imageIndex = (this.imageIndex + 1) % this.images.length;
          })
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceEvenly)
      .padding(15)
      .backgroundColor(0xF0F0F0)
      .borderRadius(10)

      Column({ space: 10 }) {
        Text('使用场景')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .fontColor(0x333333)

        Text('• OPACITY：适用于图片轮播、幻灯片等需要平滑过渡的场景')
          .fontSize(14)
          .fontColor(0x666666)

        Text('• IDENTITY：适用于需要快速切换图片、不需要动画的场景')
          .fontSize(14)
          .fontColor(0x666666)

        Text('• 注意：此属性对动态图片资源不生效')
          .fontSize(14)
          .fontColor(0x666666)
      }
      .width('100%')
      .padding(15)
      .backgroundColor(0xFFFFFF)
      .borderRadius(10)
  }
}
