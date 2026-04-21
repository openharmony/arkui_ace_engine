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
 * ImageExample089 - 图片动态范围示例
 * 
 * 功能说明：
 * 1. dynamicRangeMode 属性 - 设置期望展示的图像动态范围
 * 2. SVG 类型图源不支持该属性
 * 3. 该接口在手机、PC/2in1 和 Tablet 设备中可正常生效，在其他设备
 * 
 * DynamicRangeMode 枚举值：
 * - DynamicRangeMode.HIGH - 不受限动态范围，最大限度进行图片提亮
 * - DynamicRangeMode.CONSTRAINT - 受限动态范围，受限进行图片提亮
 * - DynamicRangeMode.STANDARD - 标准动态范围，不进行图片提亮
 */

@Entry
@Component
struct ImageExample089 {
  @State currentRangeMode: DynamicRangeMode = DynamicRangeMode.STANDARD;
  @State selectedMode: string = 'STANDARD (标准动态范围)';

  build() {
    Scroll() {
      Column({ space: 20 }) {
        Text('图片动态范围示例')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 10 })
          .fontColor(0x333333)

        this.buildDescription()
        this.buildStandardRangeDemo()
        this.buildConstraintRangeDemo()
        this.buildHighRangeDemo()
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
      Text('dynamicRangeMode 属性说明')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Text('设置期望展示的图像动态范围。')
        .fontSize(14)
        .fontColor(0x666666)

      Text('重要特性：')
        .fontSize(14)
        .fontColor(0x666666)

      Text('• SVG 类型图源不支持该属性')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• 该接口在手机、PC/2in1 和 Tablet 设备中可正常生效')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• 在其他设备类型中无效果')
        .fontSize(12)
        .fontColor(0x999999)

      Text('DynamicRangeMode 枚举值：')
        .fontSize(14)
        .fontColor(0x666666)

      Text('• DynamicRangeMode.HIGH - 不受限动态范围，最大限度进行图片提亮')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• DynamicRangeMode.CONSTRAINT - 受限动态范围，受限进行图片提亮')
        .fontSize(12)
        .fontColor(0x999999)

      Text('• DynamicRangeMode.STANDARD - 标准动态范围，不进行图片提亮')
        .fontSize(12)
        .fontColor(0x999999)
    }
    .width('100%')
    .padding(15)
    .backgroundColor(0xFFFFFF)
    .borderRadius(10)
  }

  @Builder
  buildStandardRangeDemo() {
    Column({ space: 15 }) {
      Text('标准动态范围 (DynamicRangeMode.STANDARD)')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Text('标准动态范围，不进行图片提亮')
        .fontSize(14)
        .fontColor(0x666666)

      Column({ space: 10 }) {
        Image($r('app.media.background'))
          .width(300)
          .height(200)
          .dynamicRangeMode(DynamicRangeMode.STANDARD)
          .border({ width: 2, color: Color.Blue })
          .borderRadius(8)
          .backgroundColor(0xF0F0F0)

        Text('不进行图片提亮')
          .fontSize(12)
          .fontColor(0x666666)
      }
      .width('100%')
      .padding(15)
      .backgroundColor(0xFFFFFF)
      .borderRadius(10)
  }

  @Builder
  buildConstraintRangeDemo() {
    Column({ space: 15 }) {
      Text('受限动态范围 (DynamicRangeMode.CONSTRAINT)')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Text('受限动态范围，受限进行图片提亮')
        .fontSize(14)
        .fontColor(0x666666)

      Column({ space: 10 }) {
        Image($r('app.media.background'))
          .width(300)
          .height(200)
          .dynamicRangeMode(DynamicRangeMode.CONSTRAINT)
          .border({ width: 2, color: Color.Green })
          .borderRadius(8)
          .backgroundColor(0xF0F0F0)

        Text('受限进行图片提亮')
          .fontSize(12)
          .fontColor(0x666666)
      }
      .width('100%')
      .padding(15)
      .backgroundColor(0xFFFFFF)
      .borderRadius(10)
  }

  @Builder
  buildHighRangeDemo() {
    Column({ space: 15 }) {
      Text('不受限动态范围 (DynamicRangeMode.HIGH)')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Text('不受限动态范围，最大限度进行图片提亮')
        .fontSize(14)
        .fontColor(0x666666)

      Column({ space: 10 }) {
        Image($r('app.media.background'))
          .width(300)
          .height(200)
          .dynamicRangeMode(DynamicRangeMode.HIGH)
          .border({ width: 2, color: Color.Orange })
          .borderRadius(8)
          .backgroundColor(0xF0F0F0)

        Text('最大限度进行图片提亮')
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
      Text('动态范围模式对比')
        .fontSize(18)
        .fontWeight(FontWeight.Medium)
        .fontColor(0x666666)

      Row({ space: 15 }) {
        Column({ space: 10 }) {
          Text('STANDARD')
            .fontSize(14)
            .fontColor(0x333333)

          Image($r('app.media.background'))
            .width(150)
            .height(100)
            .dynamicRangeMode(DynamicRangeMode.STANDARD)
            .border({ width: 2, color: Color.Blue })
            .borderRadius(8)
            .backgroundColor(0xF0F0F0)

          Text('不提亮')
            .fontSize(12)
            .fontColor(0x666666)
        }

        Column({ space: 10 }) {
          Text('CONSTRAINT')
            .fontSize(14)
            .fontColor(0x333333)

          Image($r('app.media.background'))
            .width(150)
            .height(100)
            .dynamicRangeMode(DynamicRangeMode.CONSTRAINT)
            .border({ width: 2, color: Color.Green })
            .borderRadius(8)
            .backgroundColor(0xF0F0F0)

          Text('受限提亮')
            .fontSize(12)
            .fontColor(0x666666)
        }

        Column({ space: 10 }) {
          Text('HIGH')
            .fontSize(14)
            .fontColor(0x333333)

          Image($r('app.media.background'))
            .width(150)
            .height(100)
            .dynamicRangeMode(DynamicRangeMode.HIGH)
            .border({ width: 2, color: Color.Orange })
            .borderRadius(8)
            .backgroundColor(0xF0F0F0)

          Text('最大限度提亮')
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
        Text('• HDR 图片')
          .fontSize(14)
          .fontColor(0x333333)
        Text('使用 HIGH 模式获得最佳 HDR 显示效果')
          .fontSize(12)
          .fontColor(0x666666)
      }

      Column({ space: 10 }) {
        Text('• SDR 图片')
          .fontSize(14)
          .fontColor(0x333333)
        Text('使用 STANDARD 模式保持原始显示效果')
          .fontSize(12)
          .fontColor(0x666666)
      }

      Column({ space: 10 }) {
        Text('• 混合内容')
          .fontSize(14)
          .fontColor(0x333333)
        Text('使用 CONSTRAINT 模式平衡显示效果')
          .fontSize(12)
          .fontColor(0x666666)
      }

      Column({ space: 10 }) {
        Text('• 设备兼容')
          .fontSize(14)
          .fontColor(0x333333)
        Text('注意此属性在部分设备上可能不生效')
          .fontSize(12)
          .fontColor(0x666666)
      }

      Column({ space: 10 }) {
        Text('• SVG 图片')
          .fontSize(14)
          .fontColor(0x333333)
        Text('SVG 图片不支持此属性')
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
          .dynamicRangeMode(this.currentRangeMode)
          .border({ width: 2, color: Color.Red })
          .borderRadius(8)
          .backgroundColor(0xF0F0F0)
      }
      .width('100%')
      .padding(15)
      .backgroundColor(0xFFFFFF)
      .borderRadius(10)

      Row({ space: 10 }) {
        Button('STANDARD')
          .width(100)
          .onClick(() => {
            this.currentRangeMode = DynamicRangeMode.STANDARD;
            this.selectedMode = 'STANDARD (标准动态范围)';
          })

        Button('CONSTRAINT')
          .width(100)
          .onClick(() => {
            this.currentRangeMode = DynamicRangeMode.CONSTRAINT;
            this.selectedMode = 'CONSTRAINT (受限动态范围)';
          })

        Button('HIGH')
          .width(100)
          .onClick(() => {
            this.currentRangeMode = DynamicRangeMode.HIGH;
            this.selectedMode = 'HIGH (不受限动态范围)';
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

        Text('• STANDARD：标准动态范围，不进行图片提亮，适用于 SDR 图片')
          .fontSize(14)
          .fontColor(0x666666)

        Text('• CONSTRAINT：受限动态范围，受限进行图片提亮，适用于混合内容')
          .fontSize(14)
          .fontColor(0x666666)

        Text('• HIGH：不受限动态范围，最大限度进行图片提亮，适用于 HDR 图片')
          .fontSize(14)
          .fontColor(0x666666)

        Text('• 注意：此属性在手机、PC/2in1 和 Tablet 设备中可正常生效')
          .fontSize(14)
          .fontColor(0x666666)
      }
      .width('100%')
      .padding(15)
      .backgroundColor(0xFFFFFF)
      .borderRadius(10)
  }
}
