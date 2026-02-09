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
 * ArcButton样式对比示例 - 同时展示多种样式
 * 通过多个圆形屏幕并排展示不同的ArcButton样式配置
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
struct ArcButtonExample003 {
  @Local options1: ArcButtonOptions = new ArcButtonOptions({});
  @Local options2: ArcButtonOptions = new ArcButtonOptions({});
  @Local options3: ArcButtonOptions = new ArcButtonOptions({});
  @Local options4: ArcButtonOptions = new ArcButtonOptions({});

  aboutToAppear() {
    // 1. 强调亮色样式
    this.options1 = new ArcButtonOptions({
      label: '强调亮色',
      position: ArcButtonPosition.BOTTOM_EDGE,
      styleMode: ArcButtonStyleMode.EMPHASIZED_LIGHT,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(14, LengthUnit.FP),
      shadowEnabled: true
    });

    // 2. 强调暗色样式（警告样式）
    const shadowColor1: ColorMetrics = ColorMetrics.resourceColor('#80000000');
    this.options2 = new ArcButtonOptions({
      label: '强调暗色',
      position: ArcButtonPosition.BOTTOM_EDGE,
      styleMode: ArcButtonStyleMode.EMPHASIZED_DARK,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(14, LengthUnit.FP),
      shadowEnabled: true,
      shadowColor: shadowColor1
    });

    // 3. 常规亮色样式
    const shadowColor2: ColorMetrics = ColorMetrics.resourceColor('#80000000');
    this.options3 = new ArcButtonOptions({
      label: '常规亮色',
      position: ArcButtonPosition.BOTTOM_EDGE,
      styleMode: ArcButtonStyleMode.NORMAL_LIGHT,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(14, LengthUnit.FP),
      shadowEnabled: true,
      shadowColor: shadowColor2
    });

    // 4. 自定义样式
    const customBgColor: ColorMetrics = ColorMetrics.resourceColor('#FF00BCD4');
    const customFontColor: ColorMetrics = ColorMetrics.resourceColor('#FFFFFFFF');
    const shadowColor3: ColorMetrics = ColorMetrics.resourceColor('#80000000');
    this.options4 = new ArcButtonOptions({
      label: '自定义',
      position: ArcButtonPosition.BOTTOM_EDGE,
      styleMode: ArcButtonStyleMode.CUSTOM,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(14, LengthUnit.FP),
      shadowEnabled: true,
      shadowColor: shadowColor3,
      backgroundColor: customBgColor,
      fontColor: customFontColor
    });
  }

  build() {
    Scroll() {
      Column() {
        Text('ArcButton 样式对比')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .margin({ top: 20, bottom: 20 })

        // 第一行：两种强调样式
        Row() {
          // 强调亮色
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

            Text('强调亮色')
              .fontSize(14)
              .margin({ top: 10 })
          }
          .margin({ right: 15 })

          // 强调暗色
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

            Text('强调暗色（警告）')
              .fontSize(14)
              .margin({ top: 10 })
          }
        }
        .margin({ bottom: 20 })
        .justifyContent(FlexAlign.Center)

        // 第二行：常规样式和自定义样式
        Row() {
          // 常规亮色
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

            Text('常规亮色')
              .fontSize(14)
              .margin({ top: 10 })
          }
          .margin({ right: 15 })

          // 自定义样式
          Column() {
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

            Text('自定义颜色')
              .fontSize(14)
              .margin({ top: 10 })
          }
        }
        .margin({ bottom: 20 })
        .justifyContent(FlexAlign.Center)

        // 说明文字
        Column() {
          Text('样式说明')
            .fontSize(18)
            .fontWeight(FontWeight.Bold)
            .margin({ bottom: 10 })

          Text('• 强调亮色：蓝色背景，白色文字，适合主要操作')
            .fontSize(14)
            .margin({ bottom: 5 })

          Text('• 强调暗色：红色背景，白色文字，适合警告操作')
            .fontSize(14)
            .margin({ bottom: 5 })

          Text('• 常规亮色：深蓝色背景，蓝色文字，适合次要操作')
            .fontSize(14)
            .margin({ bottom: 5 })

          Text('• 自定义：可自由配置背景色和文字颜色')
            .fontSize(14)
            .margin({ bottom: 5 })
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
