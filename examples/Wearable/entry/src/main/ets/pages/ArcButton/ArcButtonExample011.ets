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
 * ArcButton样式属性综合测试示例
 * 测试ArcButton的样式属性包括：
 * - 背景颜色(backgroundColor)
 * - 背景模糊能力(backgroundBlurStyle)
 * - 阴影开关(shadowEnabled)
 * - 阴影颜色(shadowColor)
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
  BlurStyle,
} from '@kit.ArkUI';

@Entry
@ComponentV2
struct ArcButtonExample011 {
 {
  // 背景颜色测试配置
  @Local redBgOptions: ArcButtonOptions = new ArcButtonOptions({});
  @Local greenBgOptions: ArcButtonOptions = new ArcButtonOptions({});
  @Local blueBgOptions: ArcButtonOptions = new ArcButtonOptions({});
  @Local purpleBgOptions: ArcButtonOptions = new ArcButtonOptions({});

  // 背景模糊测试配置
  @Local noBlurOptions: ArcButtonOptions = new ArcButtonOptions({});
  @Local thinBlurOptions: ArcButtonOptions = new ArcButtonOptions({});
  @Local regularBlurOptions: ArcButtonOptions = new ArcButtonOptions({});
  @Local thickBlurOptions: ArcButtonOptions = new ArcButtonOptions({});

  // 背景景深模糊测试配置
  @Local bgThinBlurOptions: ArcButtonOptions = new ArcButtonOptions({});
  @Local bgRegularBlurOptions: ArcButtonOptions = new ArcButtonOptions({});
  @Local bgThickBlurOptions: ArcButtonOptions = new ArcButtonOptions({});
  @Local bgUltraThickBlurOptions: ArcButtonOptions = new ArcButtonOptions({});

  // 组件模糊测试配置
  @Local compUltraThinBlurOptions: ArcButtonOptions = new ArcButtonOptions({});
  @Local compThinBlurOptions: ArcButtonOptions = new ArcButtonOptions({});
  @Local compRegularBlurOptions: ArcButtonOptions = new ArcButtonOptions({});
  @Local compThickBlurOptions: ArcButtonOptions = new ArcButtonOptions({});

  // 阴影测试配置
  @Local noShadowOptions: ArcButtonOptions = new ArcButtonOptions({});
  @Local withShadowOptions: ArcButtonOptions = new ArcButtonOptions({});
  @Local defaultShadowOptions: ArcButtonOptions = new ArcButtonOptions({});

  // 阴影颜色测试配置
  @Local blackShadowOptions: ArcButtonOptions = new ArcButtonOptions({});
  @Local redShadowOptions: ArcButtonOptions = new ArcButtonOptions({});
  @Local blueShadowOptions: ArcButtonOptions = new ArcButtonOptions({});
  @Local greenShadowOptions: ArcButtonOptions = new ArcButtonOptions({});

  // 综合效果测试配置
  @Local customStyleOptions: ArcButtonOptions = new ArcButtonOptions({});

  aboutToAppear() {
    this.initBackgroundColorTests();
    this.initBackgroundBlurTests();
    this.initBackgroundDepthBlurTests();
    this.initComponentBlurTests();
    this.initShadowTests();
    this.initShadowColorTests();
    this.initComprehensiveTest();
  }

  // 初始化背景颜色测试
  initBackgroundColorTests() {
    const whiteFontColor: ColorMetrics = ColorMetrics.resourceColor('#FFFFFFFF');

    // 红色背景
    this.redBgOptions = new ArcButtonOptions({
      label: '红色背景',
      styleMode: ArcButtonStyleMode.CUSTOM,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(14, LengthUnit.FP),
      shadowEnabled: true,
      backgroundColor: ColorMetrics.resourceColor('#FFFF0000'),
      fontColor: whiteFontColor
    });

    // 绿色背景
    this.greenBgOptions = new ArcButtonOptions({
      label: '绿色背景',
      styleMode: ArcButtonStyleMode.CUSTOM,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(14, LengthUnit.FP),
      shadowEnabled: true,
      backgroundColor: ColorMetrics.resourceColor('#FF00FF00'),
      fontColor: whiteFontColor
    });

    // 蓝色背景
    this.blueBgOptions = new ArcButtonOptions({
      label: '蓝色背景',
      styleMode: ArcButtonStyleMode.CUSTOM,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(14, LengthUnit.FP),
      shadowEnabled: true,
      backgroundColor: ColorMetrics.resourceColor('#FF0000FF'),
      fontColor: whiteFontColor
    });

    // 紫色背景
    this.purpleBgOptions = new ArcButtonOptions({
      label: '紫色背景',
      styleMode: ArcButtonStyleMode.CUSTOM,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(14, LengthUnit.FP),
      shadowEnabled: true,
      backgroundColor: ColorMetrics.resourceColor('#FF9900FF'),
      fontColor: whiteFontColor
    });
  }

  // 初始化背景模糊测试
  initBackgroundBlurTests() {
    const customBgColor: ColorMetrics = ColorMetrics.resourceColor('#FF6200EE');
    const customFontColor: ColorMetrics = ColorMetrics.resourceColor('#FFFFFFFF');

    // 无模糊
    this.noBlurOptions = new ArcButtonOptions({
      label: '无模糊',
      styleMode: ArcButtonStyleMode.CUSTOM,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(14, LengthUnit.FP),
      shadowEnabled: true,
      backgroundBlurStyle: BlurStyle.NONE,
      backgroundColor: customBgColor,
      fontColor: customFontColor
    });

    // 轻薄材质模糊
    this.thinBlurOptions = new ArcButtonOptions({
      label: '轻薄模糊',
      styleMode: ArcButtonStyleMode.CUSTOM,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(14, LengthUnit.FP),
      shadowEnabled: true,
      backgroundBlurStyle: BlurStyle.Thin,
      backgroundColor: customBgColor,
      fontColor: customFontColor
    });

    // 普通厚度材质模糊
    this.regularBlurOptions = new ArcButtonOptions({
      label: '普通过度',
      styleMode: ArcButtonStyleMode.CUSTOM,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(14, LengthUnit.FP),
      shadowEnabled: true,
      backgroundBlurStyle: BlurStyle.Regular,
      backgroundColor: customBgColor,
      fontColor: customFontColor
    });

    // 厚材质模糊
    this.thickBlurOptions = new ArcButtonOptions({
      label: '厚度模糊',
      styleMode: ArcButtonStyleMode.CUSTOM,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(14, LengthUnit.FP),
      shadowEnabled: true,
      backgroundBlurStyle: BlurStyle.Thick,
      backgroundColor: customBgColor,
      fontColor: customFontColor
    });
  }

  // 初始化背景景深模糊测试
  initBackgroundDepthBlurTests() {
    const customBgColor2: ColorMetrics = ColorMetrics.resourceColor('#FF00BCD4');
    const customFontColor2: ColorMetrics = ColorMetrics.resourceColor('#FFFFFFFF');

    // 近距景深模糊
    this.bgThinBlurOptions = new ArcButtonOptions({
      label: '近距景深',
      styleMode: ArcButtonStyleMode.CUSTOM,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(13, LengthUnit.FP),
      shadowEnabled: true,
      backgroundBlurStyle: BlurStyle.BACKGROUND_THIN,
      backgroundColor: customBgColor2,
      fontColor: customFontColor2
    });

    // 中距景深模糊
    this.bgRegularBlurOptions = new ArcButtonOptions({
      label: '中距景深',
      styleMode: ArcButtonStyleMode.CUSTOM,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(13, LengthUnit.FP),
      shadowEnabled: true,
      backgroundBlurStyle: BlurStyle.BACKGROUND_REGULAR,
      backgroundColor: customBgColor2,
      fontColor: customFontColor2
    });

    // 远距景深模糊
    this.bgThickBlurOptions = new ArcButtonOptions({
      label: '远距景深',
      styleMode: ArcButtonStyleMode.CUSTOM,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(13, LengthUnit.FP),
      shadowEnabled: true,
      backgroundBlurStyle: BlurStyle.BACKGROUND_THICK,
      backgroundColor: customBgColor2,
      fontColor: customFontColor2
    });

    // 超远距景深模糊
    this.bgUltraThickBlurOptions = new ArcButtonOptions({
      label: '超远距景深',
      styleMode: ArcButtonStyleMode.CUSTOM,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(13, LengthUnit.FP),
      shadowEnabled: true,
      backgroundBlurStyle: BlurStyle.BACKGROUND_ULTRA_THICK,
      backgroundColor: customBgColor2,
      fontColor: customFontColor2
    });
  }

  // 初始化组件模糊测试
  initComponentBlurTests() {
    const customBgColor3: ColorMetrics = ColorMetrics.resourceColor('#FF4CAF50');
    const customFontColor3: ColorMetrics = ColorMetrics.resourceColor('#FFFFFFFF');

    // 组件超轻薄材质模糊
    this.compUltraThinBlurOptions = new ArcButtonOptions({
      label: '超轻薄',
      styleMode: ArcButtonStyleMode.CUSTOM,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(12, LengthUnit.FP),
      shadowEnabled: true,
      backgroundBlurStyle: BlurStyle.COMPONENT_ULTRA_THIN,
      backgroundColor: customBgColor3,
      fontColor: customFontColor3
    });

    // 组件轻薄材质模糊
    this.compThinBlurOptions = new ArcButtonOptions({
      label: '轻薄',
      styleMode: ArcButtonStyleMode.CUSTOM,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(12, LengthUnit.FP),
      shadowEnabled: true,
      backgroundBlurStyle: BlurStyle.COMPONENT_THIN,
      backgroundColor: customBgColor3,
      fontColor: customFontColor3
    });

    // 组件普通材质模糊
    this.compRegularBlurOptions = new ArcButtonOptions({
      label: '普通',
      styleMode: ArcButtonStyleMode.CUSTOM,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(12, LengthUnit.FP),
      shadowEnabled: true,
      backgroundBlurStyle: BlurStyle.COMPONENT_REGULAR,
      backgroundColor: customBgColor3,
      fontColor: customFontColor3
    });

    // 组件厚材质模糊
    this.compThickBlurOptions = new ArcButtonOptions({
      label: '厚度',
      styleMode: ArcButtonStyleMode.CUSTOM,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(12, LengthUnit.FP),
      shadowEnabled: true,
      backgroundBlurStyle: BlurStyle.COMPONENT_THICK,
      backgroundColor: customBgColor3,
      fontColor: customFontColor3
    });
  }

  // 初始化阴影测试
  initShadowTests() {
    const customBgColor4: ColorMetrics = ColorMetrics.resourceColor('#FF9C27B0');
    const customFontColor4: ColorMetrics = ColorMetrics.resourceColor('#FFFFFFFF');
    const shadowColor: ColorMetrics = ColorMetrics.resourceColor('#80000000');

    // 无阴影
    this.noShadowOptions = new ArcButtonOptions({
      label: '无阴影',
      styleMode: ArcButtonStyleMode.CUSTOM,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(14, LengthUnit.FP),
      shadowEnabled: false,
      backgroundColor: customBgColor4,
      fontColor: customFontColor4
    });

    // 有阴影
    this.withShadowOptions = new ArcButtonOptions({
      label: '有阴影',
      styleMode: ArcButtonStyleMode.CUSTOM,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(14, LengthUnit.FP),
      shadowEnabled: true,
      shadowColor: shadowColor,
      backgroundColor: customBgColor4,
      fontColor: customFontColor4
    });

    // 默认阴影
    this.defaultShadowOptions = new ArcButtonOptions({
      label: '默认阴影',
      styleMode: ArcButtonStyleMode.EMPHASIZED_LIGHT,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(14, LengthUnit.FP),
      shadowEnabled: true
    });
  }

  // 初始化阴影颜色测试
  initShadowColorTests() {
    const whiteFontColor: ColorMetrics = ColorMetrics.resourceColor('#FFFFFFFF');

    // 黑色阴影
    this.blackShadowOptions = new ArcButtonOptions({
      label: '黑色阴影',
      styleMode: ArcButtonStyleMode.CUSTOM,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(13, LengthUnit.FP),
      shadowEnabled: true,
      shadowColor: ColorMetrics.resourceColor('#80000000'),
      backgroundColor: ColorMetrics.resourceColor('#FFFF9800'),
      fontColor: whiteFontColor
    });

    // 红色阴影
    this.redShadowOptions = new ArcButtonOptions({
      label: '红色阴影',
      styleMode: ArcButtonStyleMode.CUSTOM,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(13, LengthUnit.FP),
      shadowEnabled: true,
      shadowColor: ColorMetrics.resourceColor('#80FF0000'),
      backgroundColor: ColorMetrics.resourceColor('#FFFF9800'),
      fontColor: whiteFontColor
    });

    // 蓝色阴影
    this.blueShadowOptions = new ArcButtonOptions({
      label: '蓝色阴影',
      styleMode: ArcButtonStyleMode.CUSTOM,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(13, LengthUnit.FP),
      shadowEnabled: true,
      shadowColor: ColorMetrics.resourceColor('#800000FF'),
      backgroundColor: ColorMetrics.resourceColor('#FFFF9800'),
      fontColor: whiteFontColor
    });

    // 绿色阴影
    this.greenShadowOptions = new ArcButtonOptions({
      label: '绿色阴影',
      styleMode: ArcButtonStyleMode.CUSTOM,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(13, LengthUnit.FP),
      shadowEnabled: true,
      shadowColor: ColorMetrics.resourceColor('#8000FF00'),
      backgroundColor: ColorMetrics.resourceColor('#FFFF9800'),
      fontColor: whiteFontColor
    });
  }

  // 初始化综合效果测试
  initComprehensiveTest() {
    this.customStyleOptions = new ArcButtonOptions({
      label: '综合样式',
      styleMode: ArcButtonStyleMode.CUSTOM,
      position: ArcButtonPosition.BOTTOM_EDGE,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(15, LengthUnit.FP),
      shadowEnabled: true,
      backgroundBlurStyle: BlurStyle.COMPONENT_REGULAR,
      shadowColor: ColorMetrics.resourceColor('#80000000'),
      backgroundColor: ColorMetrics.resourceColor('#FFE91E63'),
      fontColor: ColorMetrics.resourceColor('#FFFFFFFF')
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
          Text('ArcButton 样式属性综合测试')
            .fontSize(24)
            .fontWeight(FontWeight.Bold)
            .margin({ top: 20, bottom: 10 })

          Text('测试背景颜色、背景模糊、阴影开关、阴影颜色')
            .fontSize(14)
            .fontColor('#666666')
            .margin({ bottom: 20 })
        }
        .width('100%')
        .padding({ left: 15, right: 15 })

        // 背景颜色测试
        this.TitleSection('背景颜色测试', 'backgroundColor属性，需要CUSTOM模式')

        Row() {
          this.TestItem('红色', this.redBgOptions, '#FFFF0000')
          this.TestItem('绿色', this.greenBgOptions, '#FF00FF00')
          this.TestItem('蓝色', this.blueBgOptions, '#FF0000FF')
          this.TestItem('紫色', this.purpleBgOptions, '#FF9900FF')
        }
        .width('100%')
        .padding({ left: 15 })
        .margin({ bottom: 25 })
        .justifyContent(FlexAlign.Start)

        // 背景模糊测试
        this.TitleSection('背景模糊测试', 'backgroundBlurStyle属性 - 材质模糊')

        Row() {
          this.TestItem('无模糊', this.noBlurOptions, 'BlurStyle.NONE')
          this.TestItem('轻薄', this.thinBlurOptions, 'BlurStyle.Thin')
          this.TestItem('普通过度', this.regularBlurOptions, 'BlurStyle.Regular')
          this.TestItem('厚度', this.thickBlurOptions, 'BlurStyle.Thick')
        }
        .width('100%')
        .padding({ left: 15 })
        .margin({ bottom: 25 })
        .justifyContent(FlexAlign.Start)

        // 背景景深模糊测试
        this.TitleSection('背景景深模糊测试', 'backgroundBlurStyle属性 - 景深模糊')

        Row() {
          this.TestItem('近距景深', this.bgThinBlurOptions, 'BACKGROUND_THIN')
          this.TestItem('中距景深', this.bgRegularBlurOptions, 'BACKGROUND_REGULAR')
        }
        .width('100%')
        .padding({ left: 15 })
        .margin({ bottom: 10 })
        .justifyContent(FlexAlign.Start)

        Row() {
          this.TestItem('远距景深', this.bgThickBlurOptions, 'BACKGROUND_THICK')
          this.TestItem('超远距景深', this.bgUltraThickBlurOptions, 'BACKGROUND_ULTRA_THICK')
        }
        .width('100%')
        .padding({ left: 15 })
        .margin({ bottom: 25 })
        .justifyContent(FlexAlign.Start)

        // 组件模糊测试
        this.TitleSection('组件模糊测试', 'backgroundBlurStyle属性 - 组件模糊')

        Row() {
          this.TestItem('超轻薄', this.compUltraThinBlurOptions, 'COMPONENT_ULTRA_THIN')
          this.TestItem('轻薄', this.compThinBlurOptions, 'COMPONENT_THIN')
        }
        .width('100%')
        .padding({ left: 15 })
        .margin({ bottom: 10 })
        .justifyContent(FlexAlign.Start)

        Row() {
          this.TestItem('普通', this.compRegularBlurOptions, 'COMPONENT_REGULAR')
          this.TestItem('厚度', this.compThickBlurOptions, 'COMPONENT_THICK')
        }
        .width('100%')
        .padding({ left: 15 })
        .margin({ bottom: 25 })
        .justifyContent(FlexAlign.Start)

        // 阴影测试
        this.TitleSection('阴影开关测试', 'shadowEnabled属性')

        Row() {
          this.TestItem('无阴影', this.noShadowOptions, 'shadowEnabled=false')
          this.TestItem('有阴影', this.withShadowOptions, 'shadowEnabled=true')
          this.TestItem('默认阴影', this.defaultShadowOptions, 'EMPHASIZED_LIGHT')
        }
        .width('100%')
        .padding({ left: 15 })
        .margin({ bottom: 25 })
        .justifyContent(FlexAlign.Start)

        // 阴影颜色测试
        this.TitleSection('阴影颜色测试', 'shadowColor属性')

        Row() {
          this.TestItem('黑色阴影', this.blackShadowOptions, '#80000000')
          this.TestItem('红色阴影', this.redShadowOptions, '#80FF0000')
        }
        .width('100%')
        .padding({ left: 15 })
        .margin({ bottom: 10 })
        .justifyContent(FlexAlign.Start)

        Row() {
          this.TestItem('蓝色阴影', this.blueShadowOptions, '#800000FF')
          this.TestItem('绿色阴影', this.greenShadowOptions, '#8000FF00')
        }
        .width('100%')
        .padding({ left: 15 })
        .margin({ bottom: 25 })
        .justifyContent(FlexAlign.Start)

        // 综合效果测试
        this.TitleSection('综合效果测试', '同时应用多种样式属性')

        Row() {
          this.TestItem('综合样式', this.customStyleOptions, '所有属性')
        }
        .width('100%')
        .padding({ left: 15 })
        .margin({ bottom: 25 })
        .justifyContent(FlexAlign.Start)

        // 属性说明
        Column() {
          Text('属性说明')
            .fontSize(18)
            .fontWeight(FontWeight.Bold)
            .margin({ bottom: 10 })

          Text('1. backgroundColor: 背景颜色，仅在ArcButtonStyleMode.CUSTOM时生效')
            .fontSize(13)
            .margin({ bottom: 5 })

          Text('2. backgroundBlurStyle: 背景模糊样式，支持多种模糊效果')
            .fontSize(13)
            .margin({ bottom: 5 })

          Text('   - 材质模糊: Thin, Regular, Thick')
            .fontSize(13)
            .margin({ bottom: 5 })

          Text('   - 景深模糊: BACKGROUND_THIN, BACKGROUND_REGULAR, BACKGROUND_THICK, BACKGROUND_ULTRA_THICK')
            .fontSize(13)
            .margin({ bottom: 5 })

          Text('   - 组件模糊: COMPONENT_ULTRA_THIN, COMPONENT_THIN, COMPONENT_REGULAR, COMPONENT_THICK')
            .fontSize(13)
            .margin({ bottom: 5 })

          Text('3. shadowEnabled: 阴影开关，默认false')
            .fontSize(13)
            .margin({ bottom: 5 })

          Text('4. shadowColor: 阴影颜色，使用ColorMetrics指定')
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
