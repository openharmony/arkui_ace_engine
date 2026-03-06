/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
 * ArcButtonProgressConfig 异常值测试示例
 * 测试进度条的各种边界情况和异常值处理
 */
import {
  LengthMetrics,
  LengthUnit,
  ArcButton,
  ArcButtonOptions,
  ArcButtonStatus,
  ArcButtonPosition,
  ArcButtonStyleMode
} from '@kit.ArkUI';

@Entry
@ComponentV2
struct ArcButtonExample006 {
  // 测试用例配置
  @Local options1: ArcButtonOptions = new ArcButtonOptions({});
  @Local options2: ArcButtonOptions = new ArcButtonOptions({});
  @Local options3: ArcButtonOptions = new ArcButtonOptions({});
  @Local options4: ArcButtonOptions = new ArcButtonOptions({});
  @Local options5: ArcButtonOptions = new ArcButtonOptions({});
  @Local options6: ArcButtonOptions = new ArcButtonOptions({});
  @Local options7: ArcButtonOptions = new ArcButtonOptions({});
  @Local options8: ArcButtonOptions = new ArcButtonOptions({});

  aboutToAppear() {
    // 测试1: value > total（value会被置为total）
    this.options1 = new ArcButtonOptions({
      label: '测试1: value>total\n期望: value置为total',
      styleMode: ArcButtonStyleMode.NORMAL_LIGHT,
      position: ArcButtonPosition.TOP_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(10, LengthUnit.FP),
      shadowEnabled: true,
      progressConfig: { value: 150, total: 100 }  // value > total
    });

    // 测试2: value < 0（value会被置为0）
    this.options2 = new ArcButtonOptions({
      label: '测试2: value<0\n期望: value置为0',
      styleMode: ArcButtonStyleMode.NORMAL_LIGHT,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(10, LengthUnit.FP),
      shadowEnabled: true,
      progressConfig: { value: -10, total: 100 }  // value < 0
    });

    // 测试3: total = 0（total会被置为默认值100）
    this.options3 = new ArcButtonOptions({
      label: '测试3: total=0\n期望: total置为100',
      styleMode: ArcButtonStyleMode.NORMAL_LIGHT,
      position: ArcButtonPosition.TOP_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(10, LengthUnit.FP),
      shadowEnabled: true,
      progressConfig: { value: 50, total: 0 }  // total = 0
    });

    // 测试4: total < 0（total会被置为默认值100）
    this.options4 = new ArcButtonOptions({
      label: '测试4: total<0\n期望: total置为100',
      styleMode: ArcButtonStyleMode.NORMAL_LIGHT,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(10, LengthUnit.FP),
      shadowEnabled: true,
      progressConfig: { value: 50, total: -50 }  // total < 0
    });

    // 测试5: value和total都为0
    this.options5 = new ArcButtonOptions({
      label: '测试5: 都为0\n期望: 正常显示',
      styleMode: ArcButtonStyleMode.NORMAL_LIGHT,
      position: ArcButtonPosition.TOP_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(10, LengthUnit.FP),
      shadowEnabled: true,
      progressConfig: { value: 0, total: 0 }  // 都为0
    });

    // 测试6: value和total都为负数
    this.options6 = new ArcButtonOptions({
      label: '测试6: 都为负\n期望: 置为0/100',
      styleMode: ArcButtonStyleMode.NORMAL_LIGHT,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(10, LengthUnit.FP),
      shadowEnabled: true,
      progressConfig: { value: -100, total: -200 }  // 都为负数
    });

    // 测试7: 超大数值（超出范围）
    this.options7 = new ArcButtonOptions({
      label: '测试7: 超大数值\n期望: 置为默认值',
      styleMode: ArcButtonStyleMode.NORMAL_LIGHT,
      position: ArcButtonPosition.TOP_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(10, LengthUnit.FP),
      shadowEnabled: true,
      progressConfig: { value: 9999999999, total: 9999999999 }  // 超出范围
    });

    // 测试8: 边界值测试（正常情况）
    this.options8 = new ArcButtonOptions({
      label: '测试8: 边界值\nvalue=total=2147483647',
      styleMode: ArcButtonStyleMode.NORMAL_LIGHT,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(10, LengthUnit.FP),
      shadowEnabled: true,
      progressConfig: { value: 2147483647, total: 2147483647 }  // 最大值
    });
  }

  build() {
    Scroll() {
      Column() {
        Text('ArcButtonProgressConfig 异常值测试')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 20 })

        // 测试规则说明
        Column() {
          Text('测试规则说明')
            .fontSize(18)
            .fontWeight(FontWeight.Bold)
            .margin({ bottom: 10 })

          Text('• value < 0: 置为 0')
            .fontSize(14)
            .margin({ bottom: 5 })

          Text('• value > total: 置为 total')
            .fontSize(14)
            .margin({ bottom: 5 })

          Text('• total = 0 或 < 0: 置为默认值 100')
            .fontSize(14)
            .margin({ bottom: 5 })

          Text('• total > 2147483647: 置为默认值 100')
            .fontSize(14)
            .margin({ bottom: 5 })
        }
        .width('90%')
        .padding(15)
        .backgroundColor('#FFF3E0')
        .borderRadius(10)
        .margin({ bottom: 20 })

        // 测试1-2: value异常
        Row() {
          Column() {
            Stack() {
              Circle({ width: 160, height: 160 })
                .strokeWidth(0.1)
                .fill(Color.White)

              Column() {
                ArcButton({ options: this.options1 })
              }
              .width('100%')
              .height('100%')
            }
            .width(160)
            .height(160)

            Text('value=150, total=100')
              .fontSize(11)
              .fontColor('#666666')
              .margin({ top: 5 })
          }
          .margin({ right: 10 })

          Column() {
            Stack() {
              Circle({ width: 160, height: 160 })
                .strokeWidth(0.1)
                .fill(Color.White)

              Column() {
                ArcButton({ options: this.options2 })
              }
              .width('100%')
              .height('100%')
            }
            .width(160)
            .height(160)

            Text('value=-10, total=100')
              .fontSize(11)
              .fontColor('#666666')
              .margin({ top: 5 })
          }
        }
        .margin({ bottom: 20 })
        .justifyContent(FlexAlign.Center)

        // 测试3-4: total异常
        Row() {
          Column() {
            Stack() {
              Circle({ width: 160, height: 160 })
                .strokeWidth(0.1)
                .fill(Color.White)

              Column() {
                ArcButton({ options: this.options3 })
              }
              .width('100%')
              .height('100%')
            }
            .width(160)
            .height(160)

            Text('value=50, total=0')
              .fontSize(11)
              .fontColor('#666666')
              .margin({ top: 5 })
          }
          .margin({ right: 10 })

          Column() {
            Stack() {
              Circle({ width: 160, height: 160 })
                .strokeWidth(0.1)
                .fill(Color.White)

              Column() {
                ArcButton({ options: this.options4 })
              }
              .width('100%')
              .height('100%')
            }
            .width(160)
            .height(160)

            Text('value=50, total=-50')
              .fontSize(11)
              .fontColor('#666666')
              .margin({ top: 5 })
          }
        }
        .margin({ bottom: 20 })
        .justifyContent(FlexAlign.Center)

        // 测试5-6: 都为异常值
        Row() {
          Column() {
            Stack() {
              Circle({ width: 160, height: 160 })
                .strokeWidth(0.1)
                .fill(Color.White)

              Column() {
                ArcButton({ options: this.options5 })
              }
              .width('100%')
              .height('100%')
            }
            .width(160)
            .height(160)

            Text('value=0, total=0')
              .fontSize(11)
              .fontColor('#666666')
              .margin({ top: 5 })
          }
          .margin({ right: 10 })

          Column() {
            Stack() {
              Circle({ width: 160, height: 160 })
                .strokeWidth(0.1)
                .fill(Color.White)

              Column() {
                ArcButton({ options: this.options6 })
              }
              .width('100%')
              .height('100%')
            }
            .width(160)
            .height(160)

            Text('value=-100, total=-200')
              .fontSize(11)
              .fontColor('#666666')
              .margin({ top: 5 })
          }
        }
        .margin({ bottom: 20 })
        .justifyContent(FlexAlign.Center)

        // 测试7-8: 超大值和边界值
        Row() {
          Column() {
            Stack() {
              Circle({ width: 160, height: 160 })
                .strokeWidth(0.1)
                .fill(Color.White)

              Column() {
                ArcButton({ options: this.options7 })
              }
              .width('100%')
              .height('100%')
            }
            .width(160)
            .height(160)

            Text('超大数值\n(超出范围)')
              .fontSize(11)
              .fontColor('#666666')
              .margin({ top: 5 })
          }
          .margin({ right: 10 })

          Column() {
            Stack() {
              Circle({ width: 160, height: 160 })
                .strokeWidth(0.1)
                .fill(Color.White)

              Column() {
                ArcButton({ options: this.options8 })
              }
              .width('100%')
              .height('100%')
            }
            .width(160)
            .height(160)

            Text('最大边界值\nvalue=total')
              .fontSize(11)
              .fontColor('#666666')
              .margin({ top: 5 })
          }
        }
        .margin({ bottom: 20 })
        .justifyContent(FlexAlign.Center)

        // 测试结果总结
        Column() {
          Text('测试结果说明')
            .fontSize(18)
            .fontWeight(FontWeight.Bold)
            .margin({ bottom: 10 })

          Text('✓ 测试1: value>total → 显示满进度（100%）')
            .fontSize(13)
            .margin({ bottom: 5 })

          Text('✓ 测试2: value<0 → 显示空进度（0%）')
            .fontSize(13)
            .margin({ bottom: 5 })

          Text('✓ 测试3: total=0 → 使用默认total=100，显示50%')
            .fontSize(13)
            .margin({ bottom: 5 })

          Text('✓ 测试4: total<0 → 使用默认total=100，显示50%')
            .fontSize(13)
            .margin({ bottom: 5 })

          Text('✓ 测试5: 都为0 → 使用默认total=100，显示0%')
            .fontSize(13)
            .margin({ bottom: 5 })

          Text('✓ 测试6: 都为负 → 使用默认值，显示0%')
            .fontSize(13)
            .margin({ bottom: 5 })

          Text('✓ 测试7: 超大数值 → 使用默认值，显示100%')
            .fontSize(13)
            .margin({ bottom: 5 })

          Text('✓ 测试8: 最大边界值 → 正常显示满进度（100%）')
            .fontSize(13)
            .margin({ bottom: 5 })
        }
        .width('90%')
        .padding(15)
        .backgroundColor('#E8F5E9')
        .borderRadius(10)
        .margin({ bottom: 20 })

        // 使用建议
        Column() {
          Text('使用建议')
            .fontSize(18)
            .fontWeight(FontWeight.Bold)
            .margin({ bottom: 10 })

          Text('1. 始终保证 value 在 [0, total] 范围内')
            .fontSize(14)
            .margin({ bottom: 5 })

          Text('2. total 应设置合理的正数（推荐100或其倍数）')
            .fontSize(14)
            .margin({ bottom: 5 })

          Text('3. 避免使用负数或超大的数值')
            .fontSize(14)
            .margin({ bottom: 5 })

          Text('4. 动态更新进度时需要做边界检查')
            .fontSize(14)
            .margin({ bottom: 5 })
        }
        .width('90%')
        .padding(15)
        .backgroundColor('#E3F2FD')
        .borderRadius(10)
        .margin({ bottom: 20 })

        // 代码示例
        Column() {
          Text('安全的进度更新代码示例')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
            .margin({ bottom: 10 })

          Text('const newValue = currentValue + step;')
            .fontSize(12)
            .fontColor('#333333')
            .margin({ bottom: 3 })

          Text('let finalValue = newValue;')
            .fontSize(12)
            .fontColor('#333333')
            .margin({ bottom: 3 })

          Text('if (finalValue < 0) finalValue = 0;')
            .fontSize(12)
            .fontColor('#D32F2F')
            .margin({ bottom: 3 })

          Text('if (finalValue > total) finalValue = total;')
            .fontSize(12)
            .fontColor('#D32F2F')
            .margin({ bottom: 3 })

          Text('progressConfig.value = finalValue;')
            .fontSize(12)
            .fontColor('#333333')
            .margin({ bottom: 3 })
        }
        .width('90%')
        .padding(15)
        .backgroundColor('#F5F5F5')
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
