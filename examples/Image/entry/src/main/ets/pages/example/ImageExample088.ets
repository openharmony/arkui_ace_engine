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
 * ImageExample088 - 图片隐私敏感示例
 * 
 * 功能说明：
 * 1. privacySensitive 属性 - 设置是否支持卡片敏感隐私信息
 * 2. 设置为 true 时，隐私模式下图片将显示为半透明底板样式
 * 3. 进入隐私模式需要卡片框架支持
 */

@Entry
@Component
struct ImageExample088 {
  @State privacySensitive: boolean = false;
  @State currentMode: string = '非隐私敏感';
  @State privacyMode: boolean = false;

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('图片隐私敏感示例')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 10 })
          .fontColor(0x333333)

        this.buildDescription()
        this.buildNonSensitiveDemo()
        this.buildSensitiveDemo()
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
      Text('privacySensitive 属性说明')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Text('设置是否支持卡片敏感隐私信息。设置为 true 时，隐私模式下图片将显示为半透明底板样式。')
        .fontSize(14)
        .fontColor(0x666666)

      Text('重要特性：')
        .fontSize(14)
        .fontColor(0x666666)

      Text('• true：隐私模式下图片显示为半透明底板样式')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• false：隐私模式下图片正常显示')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• 进入隐私模式需要卡片框架支持')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• 适用于卡片场景中的敏感图片内容')
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
  buildNonSensitiveDemo() {
    Column({ space: 15 }) {
      Text('非隐私敏感模式 (privacySensitive = false)')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Text('隐私模式下图片正常显示')
        .fontSize(14)
        .fontColor(0x666666)

      Column({ space: 10 }) {
        Image($r('app.media.background'))
          .width(300)
          .height(200)
          .privacySensitive(false)
          .border({ width: 2, color: Color.Blue })
          .borderRadius(8)
          .backgroundColor(0xF0F0F0)

        Text('隐私模式下正常显示')
          .fontSize(12)
          .fontColor(0x666666)
      }
      .width('100%')
      .padding(15)
      .backgroundColor(0xFFFFFF)
      .borderRadius(10)
  }

  @Builder
  buildSensitiveDemo() {
    Column({ space: 15 }) {
      Text('隐私敏感模式 (privacySensitive = true)')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Text('隐私模式下图片显示为半透明底板样式')
        .fontSize(14)
        .fontColor(0x666666)

      Column({ space: 10 }) {
        Image($r('app.media.background'))
          .width(300)
          .height(200)
          .privacySensitive(true)
          .border({ width: 2, color: Color.Green })
          .borderRadius(8)
          .backgroundColor(0xF0F0F0)

        Text('隐私模式下显示为半透明底板')
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
          Text('非隐私敏感')
            .fontSize(14)
            .fontColor(0x333333)

          Image($r('app.media.background'))
            .width(150)
            .height(100)
            .privacySensitive(false)
            .border({ width: 2, color: Color.Blue })
            .borderRadius(8)
            .backgroundColor(0xF0F0F0)

          Text('隐私模式下正常显示')
            .fontSize(12)
            .fontColor(0x666666)
        }

        Column({ space: 10 }) {
          Text('隐私敏感')
            .fontSize(14)
            .fontColor(0x333333)

          Image($r('app.media.background'))
            .width(150)
            .height(100)
            .privacySensitive(true)
            .border({ width: 2, color: Color.Green })
            .borderRadius(8)
            .backgroundColor(0xF0F0F0)

          Text('隐私模式下半透明显示')
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
        Text('• 个人信息')
          .fontSize(14)
          .fontColor(0x333333)
        Text('对于包含个人信息的图片，设置为隐私敏感')
          .fontSize(12)
          .fontColor(0x666666)
      }

      Column({ space: 10 }) {
        Text('• 敏感内容')
          .fontSize(14)
          .fontColor(0x333333)
        Text('对于敏感内容，设置为隐私敏感')
          .fontSize(12)
          .fontColor(0x666666)
      }

      Column({ space: 10 }) {
        Text('• 卡片场景')
          .fontSize(14)
          .fontColor(0x333333)
        Text('此属性主要适用于卡片场景')
          .fontSize(12)
          .fontColor(0x666666)
      }

      Column({ space: 10 }) {
        Text('• 公开内容')
          .fontSize(14)
          .fontColor(0x333333)
        Text('对于公开内容，不需要设置为隐私敏感')
          .fontSize(12)
          .fontColor(0x666666)
      }

      Column({ space: 10 }) {
        Text('• 框架支持')
          .fontSize(14)
          .fontColor(0x333333)
        Text('需要卡片框架支持隐私模式')
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
          .privacySensitive(this.privacySensitive)
          .border({ width: 2, color: Color.Red })
          .borderRadius(8)
          .backgroundColor(0xF0F0F0)
      }
      .width('100%')
      .padding(15)
      .backgroundColor(0xFFFFFF)
      .borderRadius(10)

      Row({ space: 10 }) {
        Button('非隐私敏感')
          .width(150)
          .onClick(() => {
            this.privacySensitive = false;
            this.currentMode = '非隐私敏感';
          })

        Button('隐私敏感')
          .width(150)
          .onClick(() => {
            this.privacySensitive = true;
            this.currentMode = '隐私敏感';
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

        Text('• 隐私敏感：包含个人信息的图片、敏感内容')
          .fontSize(14)
          .fontColor(0x666666)

        Text('• 非隐私敏感：公开内容、非敏感图片')
          .fontSize(14)
          .fontColor(0x666666)

        Text('• 注意：此属性需要卡片框架支持隐私模式')
          .fontSize(14)
          .fontColor(0x666666)
      }
      .width('100%')
      .padding(15)
      .backgroundColor(0xFFFFFF)
      .borderRadius(10)
  }
}
