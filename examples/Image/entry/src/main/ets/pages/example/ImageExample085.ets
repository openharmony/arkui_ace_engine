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
 * ImageExample085 - 图片复制选项示例
 * 
 * 功能说明：
 * 1. copyOption 属性 - 设置图片是否可复制
 * 2. 支持：长按、鼠标右击、快捷组合键 'CTRL+C' 等方式进行复制
 * 3. SVG 图片不支持复制
 * 4. AnimatedDrawableDescriptor 类型时不生效
 * 
 * CopyOptions 枚举值：
 * - CopyOptions.None - 不可复制
 * - CopyOptions.InApp - 应用内复制
 * - CopyOptions.Distributed - 跨应用复制
 * - CopyOptions.Local - 本地设备复制
 */

@Entry
@Component
struct ImageExample085 {
  @State currentCopyOption: CopyOptions = CopyOptions.None;
  @State selectedOption: string = 'None (不可复制)';
  @State copyHint: string = '长按或右键点击图片尝试复制';

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('图片复制选项示例')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 10 })
          .fontColor(0x333333)

        this.buildDescription()
        this.buildNoneCopyDemo()
        this.buildInAppCopyDemo()
        this.buildDistributedCopyDemo()
        this.buildLocalCopyDemo()
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
      Text('copyOption 属性说明')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Text('设置图片是否可复制。当 copyOption 设置为非 CopyOptions.None 时，支持使用长按、鼠标右击、快捷组合键 \'CTRL+C\' 等方式进行复制。')
        .fontSize(14)
        .fontColor(0x666666)

      Text('重要特性：')
        .fontSize(14)
        .fontColor(0x666666)

      Text('• 支持长按、鼠标右击、快捷键复制')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• SVG 图片不支持复制')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• AnimatedDrawableDescriptor 类型时不生效')
        .fontSize(12)
        .fontColor(0x999999)

      Text('CopyOptions 枚举值：')
        .fontSize(14)
        .fontColor(0x666666)

      Text('• CopyOptions.None - 不可复制')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• CopyOptions.InApp - 应用内复制')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• CopyOptions.Distributed - 跨应用复制')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• CopyOptions.Local - 本地设备复制')
        .fontSize(12)
        .fontColor(0x999999)
    }
    .width('100%')
    .padding(15)
    .backgroundColor(0xFFFFFF)
    .borderRadius(10)
  }

  @Builder
  buildNoneCopyDemo() {
    Column({ space: 15 }) {
      Text('不可复制模式 (CopyOptions.None)')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Text('图片不可复制')
        .fontSize(14)
        .fontColor(0x666666)

      Column({ space: 10 }) {
        Image($r('app.media.background'))
          .width(300)
          .height(200)
          .copyOption(CopyOptions.None)
          .border({ width: 2, color: Color.Blue })
          .borderRadius(8)
          .backgroundColor(0xF0F0F0)

        Text('长按或右键点击无法复制')
          .fontSize(12)
          .fontColor(0x666666)
      }
      .width('100%')
      .padding(15)
      .backgroundColor(0xFFFFFF)
      .borderRadius(10)
  }

  @Builder
  buildInAppCopyDemo() {
    Column({ space: 15 }) {
      Text('应用内复制模式 (CopyOptions.InApp)')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Text('图片可以在应用内复制')
        .fontSize(14)
        .fontColor(0x666666)

      Column({ space: 10 }) {
        Image($r('app.media.background'))
          .width(300)
          .height(200)
          .copyOption(CopyOptions.InApp)
          .border({ width: 2, color: Color.Green })
          .borderRadius(8)
          .backgroundColor(0xF0F0F0)

        Text('长按或右键点击可在应用内复制')
          .fontSize(12)
          .fontColor(0x666666)
      }
      .width('100%')
      .padding(15)
      .backgroundColor(0xFFFFFF)
      .borderRadius(10)
  }

  @Builder
  buildDistributedCopyDemo() {
    Column({ space: 15 }) {
      Text('跨应用复制模式 (CopyOptions.Distributed)')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Text('图片可以跨应用复制')
        .fontSize(14)
        .fontColor(0x666666)

      Column({ space: 10 }) {
        Image($r('app.media.background'))
          .width(300)
          .height(200)
          .copyOption(CopyOptions.Distributed)
          .border({ width: 2, color: Color.Orange })
          .borderRadius(8)
          .backgroundColor(0xF0F0F0)

        Text('长按或右键点击可跨应用复制')
          .fontSize(12)
          .fontColor(0x666666)
      }
      .width('100%')
      .padding(15)
      .backgroundColor(0xFFFFFF)
      .borderRadius(10)
  }

  @Builder
  buildLocalCopyDemo() {
    Column({ space: 15 }) {
      Text('本地设备复制模式 (CopyOptions.Local)')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Text('图片可以在本地设备上复制')
        .fontSize(14)
        .fontColor(0x666666)

      Column({ space: 10 }) {
        Image($r('app.media.background'))
          .width(300)
          .height(200)
          .copyOption(CopyOptions.Local)
          .border({ width: 2, color: Color.Purple })
          .borderRadius(8)
          .backgroundColor(0xF0F0F0)

        Text('长按或右键点击可在本地设备复制')
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
      Text('复制选项对比')
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
            .copyOption(CopyOptions.None)
            .border({ width: 2, color: Color.Blue })
            .borderRadius(8)
            .backgroundColor(0xF0F0F0)

          Text('不可复制')
            .fontSize(12)
            .fontColor(0x666666)
        }

        Column({ space: 10 }) {
          Text('InApp')
            .fontSize(14)
            .fontColor(0x333333)

          Image($r('app.media.background'))
            .width(150)
            .height(100)
            .copyOption(CopyOptions.InApp)
            .border({ width: 2, color: Color.Green })
            .borderRadius(8)
            .backgroundColor(0xF0F0F0)

          Text('应用内复制')
            .fontSize(12)
            .fontColor(0x666666)
        }

        Column({ space: 10 }) {
          Text('Distributed')
            .fontSize(14)
            .fontColor(0x333333)

          Image($r('app.media.background'))
            .width(150)
            .height(100)
            .copyOption(CopyOptions.Distributed)
            .border({ width: 2, color: Color.Orange })
            .borderRadius(8)
            .backgroundColor(0xF0F0F0)

          Text('跨应用复制')
            .fontSize(12)
            .fontColor(0x666666)
        }

        Column({ space: 10 }) {
          Text('Local')
            .fontSize(14)
            .fontColor(0x333333)

          Image($r('app.media.background'))
            .width(150)
            .height(100)
            .copyOption(CopyOptions.Local)
            .border({ width: 2, color: Color.Purple })
            .borderRadius(8)
            .backgroundColor(0xF0F0F0)

          Text('本地设备复制')
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
        Text('• 用户生成内容')
          .fontSize(14)
          .fontColor(0x333333)
        Text('允许用户复制自己生成的图片')
          .fontSize(12)
          .fontColor(0x666666)
      }

      Column({ space: 10 }) {
        Text('• 公开内容')
          .fontSize(14)
          .fontColor(0x333333)
        Text('允许用户复制公开的图片内容')
          .fontSize(12)
          .fontColor(0x666666)
      }

      Column({ space: 10 }) {
        Text('• 敏感内容')
          .fontSize(14)
          .fontColor(0x333333)
        Text('对于敏感内容，禁止复制')
          .fontSize(12)
          .fontColor(0x666666)
      }

      Column({ space: 10 }) {
        Text('• 版权保护')
          .fontSize(14)
          .fontColor(0x333333)
        Text('对于受版权保护的图片，谨慎开启复制')
          .fontSize(12)
          .fontColor(0x666666)
      }

      Column({ space: 10 }) {
        Text('• 应用内共享')
          .fontSize(14)
          .fontColor(0x333333)
        Text('使用 InApp 选项限制在应用内复制')
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
        Text('当前选项：' + this.selectedOption)
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .fontColor(0x333333)

        Text(this.copyHint)
          .fontSize(14)
          .fontColor(0x666666)

        Image($r('app.media.background'))
          .width(350)
          .height(250)
          .copyOption(this.currentCopyOption)
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
            this.currentCopyOption = CopyOptions.None;
            this.selectedOption = 'None (不可复制)';
            this.copyHint = '长按或右键点击图片尝试复制';
          })

        Button('InApp')
          .width(80)
          .onClick(() => {
            this.currentCopyOption = CopyOptions.InApp;
            this.selectedOption = 'InApp (应用内复制)';
            this.copyHint = '长按或右键点击可在应用内复制';
          })

        Button('Distributed')
          .width(80)
          .onClick(() => {
            this.currentCopyOption = CopyOptions.Distributed;
            this.selectedOption = 'Distributed (跨应用复制)';
            this.copyHint = '长按或右键点击可跨应用复制';
          })

        Button('Local')
          .width(80)
          .onClick(() => {
            this.currentCopyOption = CopyOptions.Local;
            this.selectedOption = 'Local (本地设备复制)';
            this.copyHint = '长按或右键点击可在本地设备复制';
          })
      }
      .width('100%')
      .justifyContent(FlexAlign.SpaceEvenly)
      .padding(15)
      .backgroundColor(0xF0F0F0)
      .borderRadius(10)

      Column({ space: 10 }) {
        Text('操作方式')
          .fontSize(16)
          .fontWeight(FontWeight.Medium)
          .fontColor(0x333333)

        Text('• 长按图片进行复制')
          .fontSize(14)
          .fontColor(0x666666)

        Text('• 鼠标右键点击图片进行复制')
          .fontSize(14)
          .fontColor(0x666666)

        Text('• 使用快捷键 CTRL+C 进行复制')
          .fontSize(14)
          .fontColor(0x666666)
      }
      .width('100%')
      .padding(15)
      .backgroundColor(0xFFFFFF)
      .borderRadius(10)
  }
}
