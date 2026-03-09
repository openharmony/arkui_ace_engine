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
 * ArcButton文本样式综合测试示例
 * 测试ArcButton内文本在不同按钮样式下的表现：
 * - 不同文本颜色
 * - 不同字体样式
 * - 按压时文本颜色
 * - 不同字体名
 * 以上内容在不同按钮样式下的显示效果对比
 */
import {
  LengthMetrics,
  LengthUnit,
  ArcButton,
  ArcButtonOptions,
  ArcButtonStatus,
  ArcButtonStyleMode,
  ArcButtonPosition,
  ColorMetrics
} from '@kit.ArkUI';

@Entry
@ComponentV2
struct ArcButtonExample010 {
  // 文本颜色测试配置 - 不同styleMode下
  @Local emphasizedLightRedText: ArcButtonOptions = new ArcButtonOptions({});
  @Local emphasizedDarkGreenText: ArcButtonOptions = new ArcButtonOptions({});
  @Local normalLightPurpleText: ArcButtonOptions = new ArcButtonOptions({});
  @Local customYellowText: ArcButtonOptions = new ArcButtonOptions({});

  // 字体样式测试配置 - 不同styleMode下
  @Local emphasizedItalicText: ArcButtonOptions = new ArcButtonOptions({});
  @Local normalItalicText: ArcButtonOptions = new ArcButtonOptions({});
  @Local customItalicText: ArcButtonOptions = new ArcButtonOptions({});

  // 按压文本颜色测试配置 - 不同styleMode下
  @Local emphasizedPressedText: ArcButtonOptions = new ArcButtonOptions({});
  @Local normalPressedText: ArcButtonOptions = new ArcButtonOptions({});
  @Local customPressedText: ArcButtonOptions = new ArcButtonOptions({});

  // 字体名测试配置 - 不同styleMode下
  @Local serifFontText: ArcButtonOptions = new ArcButtonOptions({});
  @Local monospaceFontText: ArcButtonOptions = new ArcButtonOptions({});
  @Local harmonyFontText: ArcButtonOptions = new ArcButtonOptions({});
  @Local defaultFontText: ArcButtonOptions = new ArcButtonOptions({});

  aboutToAppear() {
    this.initTextColorTests();
    this.initFontStyleTests();
    this.initPressedColorTests();
    this.initFontFamilyTests();
  }

  // 初始化文本颜色测试
  initTextColorTests() {
    // 强调亮色模式下设置红色文本（会被覆盖为白色，因为该模式强制白色文字）
    this.emphasizedLightRedText = new ArcButtonOptions({
      label: '强调亮色',
      styleMode: ArcButtonStyleMode.EMPHASIZED_LIGHT,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(14, LengthUnit.FP),
      shadowEnabled: true,
      fontColor: ColorMetrics.resourceColor('#FFFF0000')  // 红色文本
    });

    // 强调暗色模式下设置绿色文本（会被覆盖为白色，因为该模式强制白色文字）
    this.emphasizedDarkGreenText = new ArcButtonOptions({
      label: '强调暗色',
      styleMode: ArcButtonStyleMode.EMPHASIZED_DARK,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(14, LengthUnit.FP),
      shadowEnabled: true,
      fontColor: ColorMetrics.resourceColor('#FF00FF00')  // 绿色文本
    });

    // 常规亮色模式下设置紫色文本（会被覆盖为蓝色，因为该模式强制蓝色文字）
    this.normalLightPurpleText = new ArcButtonOptions({
      label: '常规亮色',
      styleMode: ArcButtonStyleMode.NORMAL_LIGHT,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(14, LengthUnit.FP),
      shadowEnabled: true,
      fontColor: ColorMetrics.resourceColor('#FF9900FF')  // 紫色文本
    });

    // 自定义模式下设置黄色文本（会生效）
    const customBgColor1: ColorMetrics = ColorMetrics.resourceColor('#FF0066CC');
    this.customYellowText = new ArcButtonOptions({
      label: '自定义',
      styleMode: ArcButtonStyleMode.CUSTOM,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(14, LengthUnit.FP),
      shadowEnabled: true,
      backgroundColor: customBgColor1,
      fontColor: ColorMetrics.resourceColor('#FFFFFF00')  // 黄色文本
    });
  }

  // 初始化字体样式测试
  initFontStyleTests() {
    const customBgColor2: ColorMetrics = ColorMetrics.resourceColor('#FF6200EE');
    const customFontColor2: ColorMetrics = ColorMetrics.resourceColor('#FFFFFFFF');

    // 强调亮色模式下使用斜体
    this.emphasizedItalicText = new ArcButtonOptions({
      label: '斜体',
      styleMode: ArcButtonStyleMode.EMPHASIZED_LIGHT,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(15, LengthUnit.FP),
      fontStyle: FontStyle.Italic,
      shadowEnabled: true
    });

    // 常规亮色模式下使用斜体
    this.normalItalicText = new ArcButtonOptions({
      label: '斜体',
      styleMode: ArcButtonStyleMode.NORMAL_LIGHT,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(15, LengthUnit.FP),
      fontStyle: FontStyle.Italic,
      shadowEnabled: true
    });

    // 自定义模式下使用斜体
    this.customItalicText = new ArcButtonOptions({
      label: '斜体',
      styleMode: ArcButtonStyleMode.CUSTOM,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(15, LengthUnit.FP),
      fontStyle: FontStyle.Italic,
      shadowEnabled: true,
      backgroundColor: customBgColor2,
      fontColor: customFontColor2
    });
  }

  // 初始化按压文本颜色测试
  initPressedColorTests() {
    const customBgColor3: ColorMetrics = ColorMetrics.resourceColor('#FF4CAF50');
    const customFontColor3: ColorMetrics = ColorMetrics.resourceColor('#FFFFFFFF');

    // 强调亮色模式下设置按压文本颜色
    this.emphasizedPressedText = new ArcButtonOptions({
      label: '按住测试',
      styleMode: ArcButtonStyleMode.EMPHASIZED_LIGHT,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(14, LengthUnit.FP),
      shadowEnabled: true,
      pressedFontColor: ColorMetrics.resourceColor('#FFFFD700')  // 金色按压文本
    });

    // 常规亮色模式下设置按压文本颜色
    this.normalPressedText = new ArcButtonOptions({
      label: '按住测试',
      styleMode: ArcButtonStyleMode.NORMAL_LIGHT,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(14, LengthUnit.FP),
      shadowEnabled: true,
      pressedFontColor: ColorMetrics.resourceColor('#FFFFA500')  // 橙色按压文本
    });

    // 自定义模式下设置按压文本颜色
    this.customPressedText = new ArcButtonOptions({
      label: '按住测试',
      styleMode: ArcButtonStyleMode.CUSTOM,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(14, LengthUnit.FP),
      shadowEnabled: true,
      backgroundColor: customBgColor3,
      fontColor: customFontColor3,
      pressedFontColor: ColorMetrics.resourceColor('#FF00FFFF')  // 青色按压文本
    });
  }

  // 初始化字体名测试
  initFontFamilyTests() {
    const customBgColor4: ColorMetrics = ColorMetrics.resourceColor('#FF9C27B0');
    const customFontColor4: ColorMetrics = ColorMetrics.resourceColor('#FFFFFFFF');

    // 强调亮色模式 - 衬线字体
    this.serifFontText = new ArcButtonOptions({
      label: 'Serif字体',
      styleMode: ArcButtonStyleMode.EMPHASIZED_LIGHT,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(13, LengthUnit.FP),
      fontFamily: 'serif',
      shadowEnabled: true
    });

    // 常规亮色模式 - 等宽字体
    this.monospaceFontText = new ArcButtonOptions({
      label: 'Monospace',
      styleMode: ArcButtonStyleMode.NORMAL_LIGHT,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(13, LengthUnit.FP),
      fontFamily: 'monospace',
      shadowEnabled: true
    });

    // 自定义模式 - HarmonyOS Sans
    this.harmonyFontText = new ArcButtonOptions({
      label: 'HarmonyOS',
      styleMode: ArcButtonStyleMode.CUSTOM,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(13, LengthUnit.FP),
      fontFamily: 'HarmonyOS Sans',
      shadowEnabled: true,
      backgroundColor: customBgColor4,
      fontColor: customFontColor4
    });

    // 自定义模式 - 默认字体
    const customBgColor5: ColorMetrics = ColorMetrics.resourceColor('#FF009688');
    this.defaultFontText = new ArcButtonOptions({
      label: 'Default',
      styleMode: ArcButtonStyleMode.CUSTOM,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(13, LengthUnit.FP),
      fontFamily: 'sans-serif',
      shadowEnabled: true,
      backgroundColor: customBgColor5,
      fontColor: customFontColor4
    });
  }

  // 创建单个测试项的Builder
  @Builder
  TestItem(title: string, options: ArcButtonOptions, desc?: string) {
    Column() {
      Stack() {
        Circle({ width: 140, height: 140 })
          .strokeWidth(0.1)
          .fill(Color.White)

        Column() {
          Blank()
          ArcButton({ options: options })
        }
        .width('100%')
        .height('100%')
      }
      .width(140)
      .height(140)

      Text(title)
        .fontSize(12)
        .fontWeight(FontWeight.Bold)
        .margin({ top: 5 })

      if (desc) {
        Text(desc)
          .fontSize(10)
          .fontColor('#666666')
          .margin({ top: 2 })
      }
    }
    .margin({ right: 10, bottom: 10 })
    .alignItems(HorizontalAlign.Center)
  }

  // 创建标题区域
  @Builder
  TitleSection(title: string, description?: string) {
    Column() {
      Text(title)
        .fontSize(18)
        .fontWeight(FontWeight.Bold)
        .margin({ bottom: 8 })

      if (description) {
        Text(description)
          .fontSize(13)
          .fontColor('#666666')
          .margin({ bottom: 5 })
      }
    }
    .width('100%')
    .padding({ left: 15, right: 15 })
    .margin({ bottom: 15 })
  }

  build() {
    Scroll() {
      Column() {
        // 页面标题
        Column() {
          Text('ArcButton 文本样式综合测试')
            .fontSize(24)
            .fontWeight(FontWeight.Bold)
            .margin({ top: 20, bottom: 10 })

          Text('测试文本颜色、字体样式、按压颜色、字体名在不同按钮样式下的效果')
            .fontSize(14)
            .fontColor('#666666')
            .margin({ bottom: 20 })
        }
        .width('100%')
        .padding({ left: 15, right: 15 })

        // 文本颜色测试
        this.TitleSection('文本颜色测试', '在不同按钮样式下设置fontColor，观察显示效果')

        Row() {
          this.TestItem('强调亮色', this.emphasizedLightRedText, '红色被覆盖为白色')
          this.TestItem('强调暗色', this.emphasizedDarkGreenText, '绿色被覆盖为白色')
          this.TestItem('常规亮色', this.normalLightPurpleText, '紫色被覆盖为蓝色')
          this.TestItem('自定义', this.customYellowText, '黄色文本生效')
        }
        .width('100%')
        .padding({ left: 15 })
        .margin({ bottom: 25 })
        .justifyContent(FlexAlign.Start)

        // 颜色说明
        Column() {
          Text('重要说明')
            .fontSize(16)
            .fontWeight(FontWeight.Bold)
            .margin({ bottom: 10 })

          Text('• 强调亮色(EMPHASIZED_LIGHT)：蓝色背景，强制白色文字，fontColor设置无效')
            .fontSize(13)
            .margin({ bottom: 5 })

          Text('• 强调暗色(EMPHASIZED_DARK)：红色背景，强制白色文字，fontColor设置无效')
            .fontSize(13)
            .margin({ bottom: 5 })

          Text('• 常规亮色(NORMAL_LIGHT)：深蓝色背景，强制蓝色文字，fontColor设置无效')
            .fontSize(13)
            .margin({ bottom: 5 })

          Text('• 自定义(CUSTOM)：backgroundColor和fontColor设置完全生效')
            .fontSize(13)
            .margin({ bottom: 5 })
        }
        .width('90%')
        .padding(15)
        .backgroundColor('#FFF3E0')
        .borderRadius(10)
        .margin({ left: 15, right: 15, bottom: 25 })

        // 字体样式测试
        this.TitleSection('字体样式测试', '在不同按钮样式下设置fontStyle，观察斜体效果')

        Row() {
          this.TestItem('强调亮色', this.emphasizedItalicText, 'FontStyle.Italic')
          this.TestItem('常规亮色', this.normalItalicText, 'FontStyle.Italic')
          this.TestItem('自定义', this.customItalicText, 'FontStyle.Italic')
        }
        .width('100%')
        .padding({ left: 15 })
        .margin({ bottom: 25 })
        .justifyContent(FlexAlign.Start)

        // 按压文本颜色测试
        this.TitleSection('按压文本颜色测试', '按住按钮观察pressedFontColor效果')

        Row() {
          this.TestItem('强调亮色', this.emphasizedPressedText, '按住变金色')
          this.TestItem('常规亮色', this.normalPressedText, '按住变橙色')
          this.TestItem('自定义', this.customPressedText, '按住变青色')
        }
        .width('100%')
        .padding({ left: 15 })
        .margin({ bottom: 25 })
        .justifyContent(FlexAlign.Start)

        // 字体名测试
        this.TitleSection('字体名测试', '在不同按钮样式下设置fontFamily，观察字体变化')

        Row() {
          this.TestItem('强调亮色', this.serifFontText, 'serif')
          this.TestItem('常规亮色', this.monospaceFontText, 'monospace')
        }
        .width('100%')
        .padding({ left: 15 })
        .margin({ bottom: 10 })
        .justifyContent(FlexAlign.Start)

        Row() {
          this.TestItem('自定义', this.harmonyFontText, 'HarmonyOS Sans')
          this.TestItem('自定义', this.defaultFontText, 'sans-serif')
        }
        .width('100%')
        .padding({ left: 15 })
        .margin({ bottom: 25 })
        .justifyContent(FlexAlign.Start)

        // 总结说明
        Column() {
          Text('测试总结')
            .fontSize(18)
            .fontWeight(FontWeight.Bold)
            .margin({ bottom: 10 })

          Text('1. 文本颜色：预设样式模式下fontColor被覆盖，只有自定义模式生效')
            .fontSize(13)
            .margin({ bottom: 5 })

          Text('2. 字体样式：fontStyle在所有模式下都生效，斜体效果一致')
            .fontSize(13)
            .margin({ bottom: 5 })

          Text('3. 按压颜色：pressedFontColor在所有模式下都生效，按住即变色')
            .fontSize(13)
            .margin({ bottom: 5 })

          Text('4. 字体名：fontFamily在所有模式下都生效，字体渲染不同')
            .fontSize(13)
            .margin({ bottom: 5 })
        }
        .width('90%')
        .padding(15)
        .backgroundColor('#E3F2FD')
        .borderRadius(10)
        .margin({ left: 15, right: 15, bottom: 30 })
      }
      .width('100%')
      .backgroundColor('#F5F5F5')
    }
    .width('100%')
    .height('100%')
    .scrollBar(BarState.Off)
    .edgeEffect(EdgeEffect.Spring)
  }
}
