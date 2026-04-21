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
 * ArcButton进度条前景色与背景混色示例
 * 演示进度条前景色是背景色25%透明时的混色效果
 * 对比展示不同背景色和进度值的效果
 */
import {
  LengthMetrics,
  LengthUnit,
  ArcButton,
  ArcButtonOptions,
  ArcButtonStatus,
  ArcButtonStyleMode,
  ArcButtonPosition,
  ColorMetrics,
} from '@kit.ArkUI';

@Entry
@ComponentV2
struct ArcButtonExample008 {
  // 测试用例配置
  @Local options1: ArcButtonOptions = new ArcButtonOptions({});
  @Local options2: ArcButtonOptions = new ArcButtonOptions({});
  @Local options3: ArcButtonOptions = new ArcButtonOptions({});
  @Local options4: ArcButtonOptions = new ArcButtonOptions({});
  @Local options5: ArcButtonOptions = new ArcButtonOptions({});
  @Local options6: ArcButtonOptions = new ArcButtonOptions({});

  aboutToAppear() {
    // 示例1: 白色背景，50%进度
    this.options1 = new ArcButtonOptions({
      label: '50%',
      styleMode: ArcButtonStyleMode.NORMAL_LIGHT,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(12, LengthUnit.FP),
      shadowEnabled: true,
      progressConfig: { value: 50, total: 100, color: '#FF1F71FF' }  // 蓝色进度
    });

    // 示例2: 浅色背景，75%进度
    this.options2 = new ArcButtonOptions({
      label: '75%',
      styleMode: ArcButtonStyleMode.CUSTOM,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(12, LengthUnit.FP),
      shadowEnabled: true,
      backgroundColor: ColorMetrics.resourceColor('#FF0066CC'),
      progressConfig: { value: 75, total: 100, color: '#FFD32F2F' }  // 深色进度
    });

    // 示例3: 深蓝色背景，30%进度
    this.options3 = new ArcButtonOptions({
      label: '30%',
      styleMode: ArcButtonStyleMode.CUSTOM,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(12, LengthUnit.FP),
      shadowEnabled: true,
      backgroundColor: ColorMetrics.resourceColor('#FF0047CC'),
      progressConfig: { value: 30, total: 100, color: '#FFFFFF00' }  // 白色进度
    });

    // 示例4: 浅绿色背景，25%进度
    this.options4 = new ArcButtonOptions({
      label: '25%',
      styleMode: ArcButtonStyleMode.CUSTOM,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(12, LengthUnit.FP),
      shadowEnabled: true,
      backgroundColor: ColorMetrics.resourceColor('#FF006400'),
      progressConfig: { value: 25, total: 100, color: '#FFFFFF00' }  // 白色进度
    });

    // 示例5: 浅紫色背景，90%进度（接近满）
    this.options5 = new ArcButtonOptions({
      label: '90%',
      styleMode: ArcButtonStyleMode.CUSTOM,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(12, LengthUnit.FP),
      shadowEnabled: true,
      backgroundColor: ColorMetrics.resourceColor('#FF6F5F5'),
      progressConfig: { value: 90, total: 100, color: '#FFFFFF00' }  // 浅紫色背景，白色进度
    });

    // 示例6: 深紫色背景，100%进度（满）
    this.options6 = new ArcButtonOptions({
      label: '100%',
      styleMode: ArcButtonStyleMode.CUSTOM,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(12, LengthUnit.FP),
      shadowEnabled: true,
      backgroundColor: ColorMetrics.resourceColor('#FF6F5F5'),
      progressConfig: { value: 100, total: 100, color: '#FFFFFF00' }  // 满状态
    });
  }

  build() {
    Scroll() {
      Column() {
        Column() {
          Text('ArcButton 进度条前景色与背景混色')
            .fontSize(24)
            .fontWeight(FontWeight.Bold)
            .margin({ top: 20, bottom: 20 })

          // 说明区域
          Column() {
            Text('混色原理解')
              .fontSize(18)
              .fontWeight(FontWeight.Bold)
              .margin({ bottom: 10 })

            Text('进度条前景色是背景色的25%透明度，当进度未充满时，')
              .fontSize(14)
              .margin({ bottom: 5 })

            Text('前景色与背景色进行混合，呈现出半透明的视觉效果。')
              .fontSize(14)
              .margin({ bottom: 5 })

            Text('进度条背景色 = 背景色 * 25% 透明')
              .fontSize(14)
              .margin({ bottom: 5 })

            Text('例如：背景色为 #FFFFFF，进度色为 #FFFFFF00')
              .fontSize(14)
              .margin({ bottom: 5 })

            Text('进度条前景透明度 = 100% - 进度%')
              .fontSize(14)
              .margin({ bottom: 5 })

            Text('进度条前景透明度 = 100% - 25% = 75%（接近不透明）')
              .fontSize(14)
              .margin({ bottom: 15 })

            Text('接近未填充满时，透明效果更明显。')
              .fontSize(14)
              .fontColor('#666666')
              .margin({ bottom: 5 })
          }
          .width('90%')
          .padding(15)
          .backgroundColor('#FFF3E0')
          .borderRadius(10)
          .margin({ bottom: 20 })

          // 第一行：白色背景
          Row() {
            Column() {
              Stack() {
                Circle({ width: 160, height: 160 })
                  .strokeWidth(0.1)
                  .fill(Color.White)

                Column() {
                  Blank()
                  ArcButton({ options: this.options1 })
                }
                .width('100%')
                .height('100%')
              }
              .width(160)
              .height(160)

              Text('白色背景\n50%进度\n前景色白色')
                .fontSize(11)
                .fontColor('#666666')
                .margin({ top: 5 })
            }
            .margin({ right: 10 })
          }
          .margin({ bottom: 20 })
          .justifyContent(FlexAlign.Center)

          // 第二行：测试色背景
          Row() {
            Column() {
              Stack() {
                Circle({ width: 160, height: 160 })
                  .strokeWidth(0.1)
                  .fill(Color.Red)

                Column() {
                  Blank()
                  ArcButton({ options: this.options2 })
                }
                .width('100%')
                .height('100%')
              }
              .width(160)
              .height(160)

              Text('测试色背景\n75%进度\n前景色深粉')
                .fontSize(11)
                .fontColor('#666666')
                .margin({ top: 5 })
            }
            .margin({ right: 10 })
          }
          .margin({ bottom: 20 })
          .justifyContent(FlexAlign.Center)

          // 第三行：深蓝色背景
          Row() {
            Column() {
              Stack() {
                Circle({ width: 160, height: 160 })
                  .strokeWidth(0.1)
                  .fill(Color.Green)

                Column() {
                  Blank()
                  ArcButton({ options: this.options3 })
                }
                .width('100%')
                .height('100%')
              }
              .width(160)
              .height(160)

              Text('深蓝背景\n30%进度\n前景色白色')
                .fontSize(11)
                .fontColor('#666666')
                .margin({ top: 5 })
            }
            .margin({ right: 10 })
          }
          .margin({ bottom: 20 })
          .justifyContent(FlexAlign.Center)

          // 第四行：绿色背景
          Row() {
            Column() {
              Stack() {
                Circle({ width: 160, height: 160 })
                  .strokeWidth(0.1)
                  .fill(Color.Green)

                Column() {
                  Blank()
                  ArcButton({ options: this.options4 })
                }
                .width('100%')
                .height('100%')
              }
              .width(160)
              .height(160)

              Text('绿色背景\n25%进度\n前景色白色')
                .fontSize(11)
                .fontColor('#666666')
                .margin({ top: 5 })
            }
            .margin({ right: 10 })
          }
          .margin({ bottom: 20 })
          .justifyContent(FlexAlign.Center)

          // 第五行：紫色背景
          Row() {
            Column() {
              Stack() {
                Circle({ width: 160, height: 160 })
                  .strokeWidth(0.1)
                  .fill(Color.White)

                Column() {
                  Blank()
                  ArcButton({ options: this.options5 })
                }
                .width('100%')
                .height('100%')
              }
              .width(160)
              .height(160)

              Text('紫色背景\n90%进度\n前景色白色')
                .fontSize(11)
                .fontColor('#666666')
                .margin({ top: 5 })
            }
            .margin({ right: 10 })
          }
          .margin({ bottom: 20 })
          .justifyContent(FlexAlign.Center)

          // 第六行：满进度对比
          Row() {
            Column() {
              Stack() {
                Circle({ width: 160, height: 160 })
                  .strokeWidth(0.1)
                  .fill(Color.White)

                Column() {
                  Blank()
                  ArcButton({ options: this.options6 })
                }
                .width('100%')
                .height('100%')
              }
              .width(160)
              .height(160)

              Text('紫色背景\n100%进度（满）\n前景色白色')
                .fontSize(11)
                .fontColor('#666666')
                .margin({ top: 5 })
            }
          }
          .margin({ right: 10 })
        }
        .margin({ bottom: 20 })
        .justifyContent(FlexAlign.Center)

        // 颜色计算说明
        Column() {
          Text('颜色透明度计算示例（以紫色为例）')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
            .margin({ bottom: 10 })

          Text('背景色：#FF6F5F5（浅紫色）')
            .fontSize(14)
            .fontColor('#666666')
            .margin({ bottom: 5 })

          Text('进度色：#FFFFFF00（白色）')
            .fontSize(14)
            .margin({ bottom: 5 })

          Text('进度值：90%，进度条填充90%')
            .fontSize(14)
            .margin({ bottom: 5 })

          Text('进度条背景透明度 = 100% - 90% = 10%')
            .fontSize(14)
            .margin({ bottom: 5 })

          Text('进度条前景透明度 = 100% - 90% = 75%（接近不透明）')
            .fontSize(14)
            .fontColor('#666666')
            .margin({ bottom: 5 })
        }
        .width('90%')
        .padding(15)
        .backgroundColor('#FFF3E0')
        .borderRadius(10)
        .margin({ bottom: 20 })

        // 使用建议
        Column() {
          Text('使用建议')
            .fontSize(18)
            .fontWeight(FontWeight.Bold)
            .margin({ bottom: 10 })

          Text('1. 进度色与背景色形成对比')
            .fontSize(14)
            .margin({ bottom: 5 })

          Text('2. 避免使用与背景色相同或过于接近的颜色，以免混淆')
            .fontSize(14)
            .margin({ bottom: 5 })

          Text('3. 进度值较小时（<30%）或接近满时，透明效果更明显')
            .fontSize(14)
            .margin({ bottom: 5 })

          Text('4. 深度值较大时（>50%），使用醒目的颜色以突出进度')
            .fontSize(14)
            .margin({ bottom: 5 })

          Text('5. 动态更新进度时，直接修改 progressConfig.value 和 label')
            .fontSize(14)
            .margin({ bottom: 10 })

          Text('6. 背景色推荐使用冷色系（浅色），让进度条更突出')
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
      .height('300%')
      .backgroundColor('#E0E0E0')
    }
    .width('100%')
  }
}
