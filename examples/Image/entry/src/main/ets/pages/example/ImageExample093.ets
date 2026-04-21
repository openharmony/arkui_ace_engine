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
 * ImageExample093 - 图片抗锯齿示例
 * 
 * 功能说明：
 * 1. antialiased 属性 - 设置位图图片边缘是否开启抗锯齿
 * 2. SVG 类型图片不支持该属性
 * 3. 和 resizable 一起使用时，该属性不生效
 * 4. 如果图片设置了背景色属性，图片的抗锯齿属性设置为 true 不会影响背景色的锯齿效果
 */

@Entry
@Component
struct ImageExample093 {
  @State antialiasedEnabled: boolean = false;
  @State currentMode: string = '抗锯齿关闭';
  @State showComparison: boolean = true;

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('图片抗锯齿示例')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 10 })
          .fontColor(0x333333)

        this.buildDescription()
        this.buildAntialiasedDisabledDemo()
        this.buildAntialiasedEnabledDemo()
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
      Text('antialiased 属性说明')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Text('设置位图图片边缘是否开启抗锯齿。')
        .fontSize(14)
        .fontColor(0x666666)

      Text('重要特性：')
        .fontSize(14)
        .fontColor(0x666666)

      Text('• SVG 类型图片不支持该属性')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• 和 resizable 一起使用时，该属性不生效')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• 如果图片设置了背景色属性，图片的抗锯齿属性设置为 true 不会影响背景色的锯齿效果')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• 抗锯齿可以减少图片边缘的锯齿效果')
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
  buildAntialiasedDisabledDemo() {
    Column({ space: 15 }) {
      Text('抗锯齿关闭 (antialiased = false)')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Text('图片边缘不开启抗锯齿')
        .fontSize(14)
        .fontColor(0x666666)

      Column({ space: 10 }) {
        Image($r('app.media.background'))
          .width(300)
          .height(200)
          .antialiased(false)
          .border({ width: 2, color: Color.Blue })
          .borderRadius(8)
          .backgroundColor(0xF0F0F0)

        Text('图片边缘可能有锯齿')
          .fontSize(12)
          .fontColor(0x666666)
      }
      .width('100%')
      .padding(15)
      .backgroundColor(0xFFFFFF)
      .borderRadius(10)
  }

  @Builder
  buildAntialiasedEnabledDemo() {
    Column({ space: 15 }) {
      Text('抗锯齿开启 (antialiased = true)')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Text('图片边缘开启抗锯齿')
        .fontSize(14)
        .fontColor(0x666666)

      Column({ space: 10 }) {
        Image($r('app.media.background'))
          .width(300)
          .height(200)
          .antialiased(true)
          .border({ width: 2, color: Color.Green })
          .borderRadius(8)
          .backgroundColor(0xF0F0F0)

        Text('图片边缘更加平滑')
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
      Text('抗锯齿对比')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Row({ space: 20 }) {
        Column({ space: 10 }) {
          Text('抗锯齿关闭')
            .fontSize(14)
            .fontColor(0x333333)

          Image($r('app.media.background'))
            .width(150)
            .height(100)
            .antialiased(false)
            .border({ width: 2, color: Color.Blue })
            .borderRadius(8)
            .backgroundColor(0xF0F0F0)

          Text('可能有锯齿')
            .fontSize(12)
            .fontColor(0x666666)
        }

        Column({ space: 10 }) {
          Text('抗锯齿开启')
            .fontSize(14)
            .fontColor(0x333333)

          Image($r('app.media.background'))
            .width(150)
            .height(100)
            .antialiased(true)
            .border({ width: 2, color: Color.Green })
            .borderRadius(8)
            .backgroundColor(0xF0F0F0)

          Text('边缘平滑')
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
        Text('• 缩放图片')
          .fontSize(14)
          .fontColor(0x333333)
        Text('对于缩放的图片，建议开启抗锯齿')
          .fontSize(12)
          .fontColor(0x666666)
      }

      Column({ space: 10 }) {
        Text('• 旋转图片')
          .fontSize(14)
          .fontColor(0x333333)
        Text('对于旋转的图片，建议开启抗锯齿')
          .fontSize(12)
          .fontColor(0x666666)
      }

      Column({ space: 10 }) {
        Text('• 高清图片')
          .fontSize(14)
          .fontColor(0x333333)
        Text('对于高清图片，开启抗锯齿可以获得更好的显示效果')
          .fontSize(12)
          .fontColor(0x666666)
      }

      Column({ space: 10 }) {
        Text('• 性能考虑')
          .fontSize(14)
          .fontColor(0x333333)
        Text('抗锯齿会消耗一定的性能资源')
          .fontSize(12)
          .fontColor(0x666666)
      }

      Column({ space: 10 }) {
        Text('• 限制条件')
          .fontSize(14)
          .fontColor(0x333333)
        Text('SVG 图片不支持，和 resizable 一起使用时不生效')
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

        Image($r('app.media.background'))
          .width(350)
          .height(250)
          .antialiased(this.antialiasedEnabled)
          .border({ width: 2, color: Color.Red })
          .borderRadius(8)
          .backgroundColor(0xF0F0F0)
      }
      .width('100%')
      .padding(15)
      .backgroundColor(0xFFFFFF)
      .borderRadius(10)

      Row({ space: 10 }) {
        Button('抗锯齿关闭')
          .width(150)
          .onClick(() => {
            this.antialiasedEnabled = false;
            this.currentMode = '抗锯齿关闭';
          })

        Button('抗锯齿开启')
          .width(150)
          .onClick(() => {
            this.antialiasedEnabled = true;
            this.currentMode = '抗锯齿开启';
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

        Text('• 抗锯齿开启：适用于缩放、旋转的图片，提供更平滑的边缘')
          .fontSize(14)
          .fontColor(0x666666)

        Text('• 抗锯齿关闭：适用于原始尺寸显示的图片，节省性能')
          .fontSize(14)
          .fontColor(0x666666)

        Text('• 注意：SVG 图片不支持，和 resizable 一起使用时不生效')
          .fontSize(14)
          .fontColor(0x666666)
      }
      .width('100%')
      .padding(15)
      .backgroundColor(0xFFFFFF)
      .borderRadius(10)
  }
}
