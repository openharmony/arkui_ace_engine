/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this is file except in compliance with the License.
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
 * ImageExample091 - SVG2 增强功能示例
 * 
 * 功能说明：
 * 1. supportSvg2 属性 - 开启或关闭 SVG 标签解析能力增强功能
 * 2. 开启后相关 SVG2 图片显示效果会有变化
 * 3. Image 组件创建后，不支持动态修改该属性的值
 */

@Entry
@Component
struct ImageExample091 {
  @State svg2Enabled: boolean = false;
  @State currentMode: string = 'SVG2 关闭';
  @State showComparison: boolean = true;

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('SVG2 增强功能示例')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 10 })
          .fontColor(0x333333)

        this.buildDescription()
        this.buildSvg2DisabledDemo()
        this.buildSvg2EnabledDemo()
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
      Text('supportSvg2 属性说明')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Text('开启或关闭 SVG 标签解析能力增强功能，开启后相关 SVG2 图片显示效果会有变化。')
        .fontSize(14)
        .fontColor(0x666666)

      Text('重要特性：')
        .fontSize(14)
        .fontColor(0x666666)

      Text('• 开启后 SVG2 图片显示效果会有变化')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• Image 组件创建后，不支持动态修改该属性的值')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• 适用于 SVG 类型图片')
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
  buildSvg2DisabledDemo() {
    Column({ space: 15 }) {
      Text('SVG2 关闭 (supportSvg2 = false)')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Text('使用标准 SVG 解析能力')
        .fontSize(14)
        .fontColor(0x666666)

      Column({ space: 10 }) {
        Image($r('app.media.ic_public_app_icon'))
          .width(300)
          .height(200)
          .supportSvg2(false)
          .border({ width: 2, color: Color.Blue })
          .borderRadius(8)
          .backgroundColor(0xF0F0F0)

        Text('标准 SVG 解析')
          .fontSize(12)
          .fontColor(0x666666)
      }
      .width('100%')
      .padding(15)
      .backgroundColor(0xFFFFFF)
      .borderRadius(10)
  }

  @Builder
  buildSvg2EnabledDemo() {
    Column({ space: 15 }) {
      Text('SVG2 开启 (supportSvg2 = true)')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Text('使用 SVG2 增强解析能力')
        .fontSize(14)
        .fontColor(0x666666)

      Column({ space: 10 }) {
        Image($r('app.media.ic_public_app_icon'))
          .width(300)
          .height(200)
          .supportSvg2(true)
          .border({ width: 2, color: Color.Green })
          .borderRadius(8)
          .backgroundColor(0xF0F0F0)

        Text('SVG2 增强解析')
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
          Text('SVG2 关闭')
            .fontSize(14)
            .fontColor(0x333333)

          Image($r('app.media.ic_public_app_icon'))
            .width(150)
            .height(100)
            .supportSvg2(false)
            .border({ width: 2, color: Color.Blue })
            .borderRadius(8)
            .backgroundColor(0xF0F0F0)

          Text('标准解析')
            .fontSize(12)
            .fontColor(0x666666)
        }

        Column({ space: 10 }) {
          Text('SVG2 开启')
            .fontSize(14)
            .fontColor(0x333333)

          Image($r('app.media.ic_public_app_icon'))
            .width(150)
            .height(100)
            .supportSvg2(true)
            .border({ width: 2, color: Color.Green })
            .borderRadius(8)
            .backgroundColor(0xF0F0F0)

          Text('增强解析')
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
        Text('• 复杂 SVG')
          .fontSize(14)
          .fontColor(0x333333)
        Text('对于复杂的 SVG 图片，建议开启 SVG2 增强功能')
          .fontSize(12)
          .fontColor(0x666666)
      }

      Column({ space: 10 }) {
        Text('• 标准 SVG')
          .fontSize(14)
          .fontColor(0x333333)
        Text('对于简单的 SVG 图片，可以使用标准解析')
          .fontSize(12)
          .fontColor(0x666666)
      }

      Column({ space: 10 }) {
        Text('• 兼容性')
          .fontSize(14)
          .fontColor(0x333333)
        Text('注意不同 SVG 版本的兼容性差异')
          .fontSize(12)
          .fontColor(0x666666)
      }

      Column({ space: 10 }) {
        Text('• 性能考虑')
          .fontSize(14)
          .fontColor(0x333333)
        Text('SVG2 增强功能可能消耗更多资源')
          .fontSize(12)
          .fontColor(0x666666)
      }

      Column({ space: 10 }) {
        Text('• 动态修改')
          .fontSize(14)
          .fontColor(0x333333)
        Text('Image 组件创建后，不支持动态修改该属性的值')
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

        Image($r('app.media.ic_public_app_icon'))
          .width(350)
          .height(250)
          .supportSvg2(this.svg2Enabled)
          .border({ width: 2, color: Color.Red })
          .borderRadius(8)
          .backgroundColor(0xF0F0F0)
      }
      .width('100%')
      .padding(15)
      .backgroundColor(0xFFFFFF)
      .borderRadius(10)

      Row({ space: 10 }) {
        Button('SVG2 关闭')
          .width(150)
          .onClick(() => {
            this.svg2Enabled = false;
            this.currentMode = 'SVG2 关闭';
          })

        Button('SVG2 开启')
          .width(150)
          .onClick(() => {
            this.svg2Enabled = true;
            this.currentMode = 'SVG2 开启';
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

        Text('• SVG2 开启：适用于复杂的 SVG 图片，提供更好的解析和显示效果')
          .fontSize(14)
          .fontColor(0x666666)

        Text('• SVG2 关闭：适用于简单的 SVG 图片，使用标准解析')
          .fontSize(14)
          .fontColor(0x666666)

        Text('• 注意：Image 组件创建后，不支持动态修改该属性的值')
          .fontSize(14)
          .fontColor(0x666666)
      }
      .width('100%')
      .padding(15)
      .backgroundColor(0xFFFFFF)
      .borderRadius(10)
  }
}
