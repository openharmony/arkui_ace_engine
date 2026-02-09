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
 * ArcButton样式冲突示例 - progressConfig与styleMode互斥
 * 展示当同时设置progressConfig和styleMode时，progressConfig优先
 */
import {
  LengthMetrics,
  LengthUnit,
  ArcButton,
  ArcButtonOptions,
  ArcButtonStatus,
  ArcButtonStyleMode,
  ArcButtonPosition,
} from '@kit.ArkUI';

@Entry
@ComponentV2
struct ArcButtonExample005 {
  @Local options1: ArcButtonOptions = new ArcButtonOptions({});
  @Local options2: ArcButtonOptions = new ArcButtonOptions({});
  @Local options3: ArcButtonOptions = new ArcButtonOptions({});
  @Local options4: ArcButtonOptions = new ArcButtonOptions({});

  aboutToAppear() {
    // 示例1: 纯styleMode - 按钮样式
    this.options1 = new ArcButtonOptions({
      label: '纯按钮',
      styleMode: ArcButtonStyleMode.EMPHASIZED_LIGHT,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(14, LengthUnit.FP),
      shadowEnabled: true
    });

    // 示例2: 纯progressConfig - 进度条样式
    this.options2 = new ArcButtonOptions({
      label: '0%',
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(14, LengthUnit.FP),
      shadowEnabled: true,
      progressConfig: { value: 0, total: 100 }
    });

    // 示例3: 同时设置styleMode和progressConfig
    // 说明：progressConfig优先，忽略styleMode
    this.options3 = new ArcButtonOptions({
      label: '0%',
      styleMode: ArcButtonStyleMode.EMPHASIZED_DARK, // 会被忽略
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(14, LengthUnit.FP),
      shadowEnabled: true,
      progressConfig: { value: 0, total: 100, color: '#FF00BCD4' } // 优先
    });

    // 示例4: 可交互的进度条按钮
    this.options4 = new ArcButtonOptions({
      label: '50%',
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(14, LengthUnit.FP),
      shadowEnabled: true,
      progressConfig: { value: 50, total: 100, color: '#FF1F71FF' },
      onClick: () => {
        // 点击增加进度
        if (this.options4.progressConfig && this.options4.progressConfig.value < 100) {
          this.options4.progressConfig.value += 10;
          this.options4.label = this.options4.progressConfig.value + '%';
        }
      }
    });
  }

  build() {
    Scroll() {
      Column() {
        Text('progressConfig 与 styleMode 冲突')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 20 })

        // 说明区域
        Column() {
          Text('重要说明')
            .fontSize(18)
            .fontWeight(FontWeight.Bold)
            .margin({ bottom: 10 })

          Text('• progressConfig 与 styleMode 不能同时使用')
            .fontSize(14)
            .margin({ bottom: 5 })

          Text('• 设置 progressConfig 后，ArcButton 表现为进度条样式')
            .fontSize(14)
            .margin({ bottom: 5 })

          Text('• 进度条样式不受 styleMode 属性设置影响')
            .fontSize(14)
            .margin({ bottom: 5 })

          Text('• 设置 progressConfig 时 styleMode 会被忽略')
            .fontSize(14)
            .margin({ bottom: 5 })
        }
        .width('90%')
        .padding(15)
        .backgroundColor('#FFF3E0')
        .borderRadius(10)
        .margin({ bottom: 20 })

        // 对比示例1：纯按钮 vs 纯进度条
        Row() {
          Column() {
            Stack() {
              Circle({ width: 200, height: 200 })
                .strokeWidth(0.1)
                .fill(Color.White)

              Column() {
                Blank()
                ArcButton({ options: this.options1 })
              }
              .width('100%')
              .height('100%')
            }
            .width(200)
            .height(200)

            Text('仅设置 styleMode')
              .fontSize(12)
              .fontColor('#666666')
              .margin({ top: 10 })
          }
          .margin({ right: 15 })

          Column() {
            Stack() {
              Circle({ width: 200, height: 200 })
                .strokeWidth(0.1)
                .fill(Color.White)

              Column() {
                Blank()
                ArcButton({ options: this.options2 })
              }
              .width('100%')
              .height('100%')
            }
            .width(200)
            .height(200)

            Text('仅设置 progressConfig')
              .fontSize(12)
              .fontColor('#666666')
              .margin({ top: 10 })
          }
        }
        .margin({ bottom: 20 })
        .justifyContent(FlexAlign.Center)

        // 对比示例2：同时设置的情况
        Column() {
          Stack() {
            Circle({ width: 200, height: 200 })
              .strokeWidth(0.1)
              .fill(Color.White)

            Column() {
              Blank()
              ArcButton({ options: this.options3 })
            }
            .width('100%')
            .height('100%')
          }
          .width(200)
          .height(200)

          Text('同时设置两者（进度条样式，styleMode被忽略）')
            .fontSize(12)
            .fontColor('#666666')
            .margin({ top: 10 })
        }
        .margin({ bottom: 20 })

        // 代码示例说明
        Column() {
          Text('代码示例')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
            .margin({ bottom: 10 })

          Text('// 同时设置，progressConfig 优先')
            .fontSize(12)
            .fontColor('#666666')
            .margin({ bottom: 5 })

          Text('new ArcButtonOptions({')
            .fontSize(12)
            .fontColor('#666666')
            .margin({ bottom: 5 })

          Text('  styleMode: EMPHASIZED_DARK,  // 被忽略')
            .fontSize(12)
            .fontColor('#D32F2F')
            .margin({ bottom: 5 })

          Text('  progressConfig: { value: 0, total: 100 }  // 优先')
            .fontSize(12)
            .fontColor('#388E3C')
            .margin({ bottom: 5 })

          Text('})')
            .fontSize(12)
            .fontColor('#666666')
            .margin({ bottom: 5 })
        }
        .width('90%')
        .padding(15)
        .backgroundColor('#F5F5F5')
        .borderRadius(10)
        .margin({ bottom: 20 })

        // 可交互示例
        Column() {
          Text('可交互进度条（点击增加进度）')
            .fontSize(14)
            .margin({ bottom: 10 })

          Stack() {
            Circle({ width: 200, height: 200 })
              .strokeWidth(0.1)
              .fill(Color.White)

            Column() {
              Blank()
              ArcButton({ options: this.options4 })
            }
            .width('100%')
            .height('100%')
          }
          .width(200)
          .height(200)
        }
        .margin({ bottom: 20 })

        // 使用建议
        Column() {
          Text('使用建议')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
            .margin({ bottom: 10 })

          Text('1. 需要按钮样式时：仅设置 styleMode')
            .fontSize(14)
            .margin({ bottom: 5 })

          Text('2. 需要进度条样式时：仅设置 progressConfig')
            .fontSize(14)
            .margin({ bottom: 5 })

          Text('3. 不要同时设置两者，避免混淆')
            .fontSize(14)
            .margin({ bottom: 5 })
        }
        .width('90%')
        .padding(15)
        .backgroundColor('#E3F2FD')
        .borderRadius(10)
        .margin({ bottom: 20 })
      }
      .width('100%')
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#E0E0E0')
  }
}
