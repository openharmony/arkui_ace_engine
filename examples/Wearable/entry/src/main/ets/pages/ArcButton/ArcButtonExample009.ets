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
 * ArcButton文本综合测试示例
 * 测试ArcButton内文本的各种特性：
 * - 正常长度文本
 * - 超长文本
 * - 超短文本
 * - 空文本
 * - 不同颜色的文本
 * - 不同语种的文本显示
 * - 不同文本大小
 * - 不同文本样式
 * - 不同文本边距
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
struct ArcButtonExample009 {
  // 文本长度测试配置
  @Local normalTextOptions: ArcButtonOptions = new ArcButtonOptions({});
  @Local longTextOptions: ArcButtonOptions = new ArcButtonOptions({});
  @Local shortTextOptions: ArcButtonOptions = new ArcButtonOptions({});
  @Local emptyTextOptions: ArcButtonOptions = new ArcButtonOptions({});

  // 颜色测试配置
  @Local whiteTextOptions: ArcButtonOptions = new ArcButtonOptions({});
  @Local blackTextOptions: ArcButtonOptions = new ArcButtonOptions({});
  @Local redTextOptions: ArcButtonOptions = new ArcButtonOptions({});
  @Local greenTextOptions: ArcButtonOptions = new ArcButtonOptions({});
  @Local blueTextOptions: ArcButtonOptions = new ArcButtonOptions({});

  // 语种测试配置
  @Local englishTextOptions: ArcButtonOptions = new ArcButtonOptions({});
  @Local chineseTextOptions: ArcButtonOptions = new ArcButtonOptions({});
  @Local japaneseTextOptions: ArcButtonOptions = new ArcButtonOptions({});
  @Local koreanTextOptions: ArcButtonOptions = new ArcButtonOptions({});
  @Local emojiTextOptions: ArcButtonOptions = new ArcButtonOptions({});

  // 大小测试配置
  @Local smallTextOptions: ArcButtonOptions = new ArcButtonOptions({});
  @Local mediumTextOptions: ArcButtonOptions = new ArcButtonOptions({});
  @Local largeTextOptions: ArcButtonOptions = new ArcButtonOptions({});

  // 样式测试配置
  @Local normalStyleOptions: ArcButtonOptions = new ArcButtonOptions({});
  @Local italicStyleOptions: ArcButtonOptions = new ArcButtonOptions({});

  // 边距测试配置
  @Local normalMarginOptions: ArcButtonOptions = new ArcButtonOptions({});
  @Local smallMarginOptions: ArcButtonOptions = new ArcButtonOptions({});
  @Local largeMarginOptions: ArcButtonOptions = new ArcButtonOptions({});

  aboutToAppear() {
    this.initTextLengthTests();
    this.initColorTests();
    this.initLanguageTests();
    this.initSizeTests();
    this.initStyleTests();
    this.initMarginTests();
  }

  // 初始化文本长度测试
  initTextLengthTests() {
    // 正常长度文本
    this.normalTextOptions = new ArcButtonOptions({
      label: '正常长度文本',
      styleMode: ArcButtonStyleMode.NORMAL_LIGHT,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(15, LengthUnit.FP),
      shadowEnabled: true,
    });

    // 超长文本
    this.longTextOptions = new ArcButtonOptions({
      label: '这是一个非常非常非常非常长的文本内容用于测试显示效果',
      styleMode: ArcButtonStyleMode.NORMAL_LIGHT,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(12, LengthUnit.FP),
      shadowEnabled: true,
    });

    // 超短文本
    this.shortTextOptions = new ArcButtonOptions({
      label: 'OK',
      styleMode: ArcButtonStyleMode.NORMAL_LIGHT,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(18, LengthUnit.FP),
      shadowEnabled: true,
    });

    // 空文本
    this.emptyTextOptions = new ArcButtonOptions({
      label: '',
      styleMode: ArcButtonStyleMode.NORMAL_LIGHT,
      position: ArcButtonPosition.BOTTOM_EDGE,
    });
  }

  // 初始化颜色测试
  initColorTests() {
    const customBgColor: ColorMetrics = ColorMetrics.resourceColor('#FF6200EE');

    // 白色文本
    this.whiteTextOptions = new ArcButtonOptions({
      label: '白色文本',
      styleMode: ArcButtonStyleMode.CUSTOM,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(15, LengthUnit.FP),
      shadowEnabled: true,
      backgroundColor: customBgColor,
      fontColor: ColorMetrics.resourceColor('#FFFFFFFF'),
    });

    // 黑色文本
    this.blackTextOptions = new ArcButtonOptions({
      label: '黑色文本',
      styleMode: ArcButtonStyleMode.CUSTOM,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(15, LengthUnit.FP),
      shadowEnabled: true,
      backgroundColor: ColorMetrics.resourceColor('#FFFFFFFF'),
      fontColor: ColorMetrics.resourceColor('#FF000000'),
    });

    // 红色文本
    this.redTextOptions = new ArcButtonOptions({
      label: '红色文本',
      styleMode: ArcButtonStyleMode.CUSTOM,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(15, LengthUnit.FP),
      shadowEnabled: true,
      backgroundColor: ColorMetrics.resourceColor('#FFFFFFFF'),
      fontColor: ColorMetrics.resourceColor('#FFFF0000'),
    });

    // 绿色文本
    this.greenTextOptions = new ArcButtonOptions({
      label: '绿色文本',
      styleMode: ArcButtonStyleMode.CUSTOM,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(15, LengthUnit.FP),
      shadowEnabled: true,
      backgroundColor: ColorMetrics.resourceColor('#FFFFFFFF'),
      fontColor: ColorMetrics.resourceColor('#FF00FF00'),
    });

    // 蓝色文本
    this.blueTextOptions = new ArcButtonOptions({
      label: '蓝色文本',
      styleMode: ArcButtonStyleMode.CUSTOM,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(15, LengthUnit.FP),
      shadowEnabled: true,
      backgroundColor: ColorMetrics.resourceColor('#FFFFFFFF'),
      fontColor: ColorMetrics.resourceColor('#FF0000FF'),
    });
  }

  // 初始化语种测试
  initLanguageTests() {
    // 英文
    this.englishTextOptions = new ArcButtonOptions({
      label: 'English',
      styleMode: ArcButtonStyleMode.NORMAL_LIGHT,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(16, LengthUnit.FP),
      shadowEnabled: true,
    });

    // 中文
    this.chineseTextOptions = new ArcButtonOptions({
      label: '中文按钮',
      styleMode: ArcButtonStyleMode.NORMAL_LIGHT,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(16, LengthUnit.FP),
      shadowEnabled: true,
    });

    // 日文
    this.japaneseTextOptions = new ArcButtonOptions({
      label: '日本語',
      styleMode: ArcButtonStyleMode.NORMAL_LIGHT,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(16, LengthUnit.FP),
      shadowEnabled: true,
    });

    // 韩文
    this.koreanTextOptions = new ArcButtonOptions({
      label: '한국어',
      styleMode: ArcButtonStyleMode.NORMAL_LIGHT,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(16, LengthUnit.FP),
      shadowEnabled: true,
    });

    // Emoji
    this.emojiTextOptions = new ArcButtonOptions({
      label: '⚡',
      styleMode: ArcButtonStyleMode.NORMAL_LIGHT,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(18, LengthUnit.FP),
      shadowEnabled: true,
    });
  }

  // 初始化大小测试
  initSizeTests() {
    // 小号文本
    this.smallTextOptions = new ArcButtonOptions({
      label: '小号',
      styleMode: ArcButtonStyleMode.NORMAL_LIGHT,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(10, LengthUnit.FP),
      shadowEnabled: true,
    });

    // 中号文本
    this.mediumTextOptions = new ArcButtonOptions({
      label: '中号',
      styleMode: ArcButtonStyleMode.NORMAL_LIGHT,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(16, LengthUnit.FP),
      shadowEnabled: true,
    });

    // 大号文本
    this.largeTextOptions = new ArcButtonOptions({
      label: '大号',
      styleMode: ArcButtonStyleMode.NORMAL_LIGHT,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(24, LengthUnit.FP),
      shadowEnabled: true,
    });
  }

  // 初始化样式测试
  initStyleTests() {
    const customBgColor: ColorMetrics = ColorMetrics.resourceColor('#FF6200EE');
    const customFontColor: ColorMetrics = ColorMetrics.resourceColor('#FFFFFFFF');

    // 正常样式
    this.normalStyleOptions = new ArcButtonOptions({
      label: '正常样式',
      styleMode: ArcButtonStyleMode.CUSTOM,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(16, LengthUnit.FP),
      fontStyle: FontStyle.Normal,
      shadowEnabled: true,
      backgroundColor: customBgColor,
      fontColor: customFontColor,
    });

    // 斜体样式
    this.italicStyleOptions = new ArcButtonOptions({
      label: '斜体样式',
      styleMode: ArcButtonStyleMode.CUSTOM,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(16, LengthUnit.FP),
      fontStyle: FontStyle.Italic,
      shadowEnabled: true,
      backgroundColor: customBgColor,
      fontColor: customFontColor,
    });
  }

  // 初始化边距测试
  initMarginTests() {
    // 正常边距
    this.normalMarginOptions = new ArcButtonOptions({
      label: '正常边距',
      styleMode: ArcButtonStyleMode.NORMAL_LIGHT,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(15, LengthUnit.FP),
      shadowEnabled: true,
      fontMargin: {
        start: LengthMetrics.vp(24),
        top: LengthMetrics.vp(10),
        end: LengthMetrics.vp(24),
        bottom: LengthMetrics.vp(16)
      }
    });

    // 小边距
    this.smallMarginOptions = new ArcButtonOptions({
      label: '小边距',
      styleMode: ArcButtonStyleMode.NORMAL_LIGHT,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(15, LengthUnit.FP),
      shadowEnabled: true,
      fontMargin: {
        start: LengthMetrics.vp(8),
        top: LengthMetrics.vp(4),
        end: LengthMetrics.vp(8),
        bottom: LengthMetrics.vp(8)
      }
    });

    // 大边距
    this.largeMarginOptions = new ArcButtonOptions({
      label: '大边距',
      styleMode: ArcButtonStyleMode.NORMAL_LIGHT,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(15, LengthUnit.FP),
      shadowEnabled: true,
      fontMargin: {
        start: LengthMetrics.vp(20),
        top: LengthMetrics.vp(20),
        end: LengthMetrics.vp(40),
        bottom: LengthMetrics.vp(30)
      }
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
          Text('ArcButton 文本综合测试')
            .fontSize(24)
            .fontWeight(FontWeight.Bold)
            .margin({ top: 20, bottom: 10 })

          Text('测试文本长度、颜色、语种、大小、样式和边距')
            .fontSize(14)
            .fontColor('#666666')
            .margin({ bottom: 20 })
        }
        .width('100%')
        .padding({ left: 15, right: 15 })

        // 文本长度测试
        this.TitleSection('文本长度测试', '测试正常长度、超长、超短和空文本的显示效果')

        Row() {
          this.TestItem('正常长度', this.normalTextOptions, '常规文本')
          this.TestItem('超长文本', this.longTextOptions, '长文本截断')
          this.TestItem('超短文本', this.shortTextOptions, '单字符')
          this.TestItem('空文本', this.emptyTextOptions, '无文本')
        }
        .width('100%')
        .padding({ left: 15 })
        .margin({ bottom: 25 })
        .justifyContent(FlexAlign.Start)

        // 颜色测试
        this.TitleSection('文本颜色测试', '测试不同颜色的文本显示效果')

        Row() {
          this.TestItem('白色文本', this.whiteTextOptions, '#FFFFFF')
          this.TestItem('黑色文本', this.blackTextOptions, '#000000')
          this.TestItem('红色文本', this.redTextOptions, '#FF0000')
          this.TestItem('绿色文本', this.greenTextOptions, '#00FF00')
        }
        .width('100%')
        .padding({ left: 15 })
        .margin({ bottom: 25 })
        .justifyContent(FlexAlign.Start)

        Row() {
          this.TestItem('蓝色文本', this.blueTextOptions, '#0000FF')
        }
        .width('100%')
        .padding({ left: 15 })
        .margin({ bottom: 25 })
        .justifyContent(FlexAlign.Start)

        // 语种测试
        this.TitleSection('多语种测试', '测试不同语言和字符集的显示效果')

        Row() {
          this.TestItem('英文', this.englishTextOptions, 'English')
          this.TestItem('中文', this.chineseTextOptions, '中文')
          this.TestItem('日文', this.japaneseTextOptions, '日本語')
          this.TestItem('韩文', this.koreanTextOptions, '한국어')
        }
        .width('100%')
        .padding({ left: 15 })
        .margin({ bottom: 25 })
        .justifyContent(FlexAlign.Start)

        Row() {
          this.TestItem('Emoji', this.emojiTextOptions, '⚡')
        }
        .width('100%')
        .padding({ left: 15 })
        .margin({ bottom: 25 })
        .justifyContent(FlexAlign.Start)

        // 大小测试
        this.TitleSection('文本大小测试', '测试不同字体大小的显示效果')

        Row() {
          this.TestItem('小号', this.smallTextOptions, '10fp')
          this.TestItem('中号', this.mediumTextOptions, '16fp')
          this.TestItem('大号', this.largeTextOptions, '24fp')
        }
        .width('100%')
        .padding({ left: 15 })
        .margin({ bottom: 25 })
        .justifyContent(FlexAlign.Start)

        // 样式测试
        this.TitleSection('文本样式测试', '测试不同字体样式的显示效果')

        Row() {
          this.TestItem('正常样式', this.normalStyleOptions, 'FontStyle.Normal')
          this.TestItem('斜体样式', this.italicStyleOptions, 'FontStyle.Italic')
        }
        .width('100%')
        .padding({ left: 15 })
        .margin({ bottom: 25 })
        .justifyContent(FlexAlign.Start)

        // 边距测试
        this.TitleSection('文本边距测试', '测试不同文本边距的显示效果')

        Row() {
          this.TestItem('正常边距', this.normalMarginOptions, '默认边距')
          this.TestItem('小边距', this.smallMarginOptions, '8/4/8/8')
          this.TestItem('大边距', this.largeMarginOptions, '40/20/40/30')
        }
        .width('100%')
        .padding({ left: 15 })
        .margin({ bottom: 25 })
        .justifyContent(FlexAlign.Start)

        // 测试说明
        Column() {
          Text('测试说明')
            .fontSize(18)
            .fontWeight(FontWeight.Bold)
            .margin({ bottom: 10 })

          Text('1. 文本长度：测试正常、超长、超短和空文本的显示和截断行为')
            .fontSize(13)
            .margin({ bottom: 5 })

          Text('2. 文本颜色：测试多种颜色方案在按钮上的显示效果')
            .fontSize(13)
            .margin({ bottom: 5 })

          Text('3. 多语种：验证英文、中文、日文、韩文和Emoji的渲染效果')
            .fontSize(13)
            .margin({ bottom: 5 })

          Text('4. 文本大小：测试小号(10fp)、中号(16fp)、大号(24fp)字体')
            .fontSize(13)
            .margin({ bottom: 5 })

          Text('5. 文本样式：测试正常和斜体两种字体样式')
            .fontSize(13)
            .margin({ bottom: 5 })

          Text('6. 文本边距：测试不同边距配置对文本布局的影响')
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
