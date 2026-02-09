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
 * ArcButton事件与字体示例 - 展示事件处理和字体样式配置
 * 包含点击事件、触摸事件、字体样式、字体族等配置
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
  FontStyle,
} from '@kit.ArkUI';

@Entry
@ComponentV2
struct ArcButtonExample004 {
  @Local clickCount: number = 0;
  @Local touchInfo: string = '等待触摸...';
  @Local topOptions: ArcButtonOptions = new ArcButtonOptions({});
  @Local bottomOptions: ArcButtonOptions = new ArcButtonOptions({});

  // 字体样式数组
  private fontStyles: FontStyle[] = [
    FontStyle.Normal,
    FontStyle.Italic,
  ];
  private fontStyleNames: string[] = ['正常', '斜体'];
  @Local currentFontStyleIndex: number = 0;

  // 字体族数组
  private fontFamilies: string[] = [
    'HarmonyOS Sans',
    'serif',
    'monospace'
  ];
  @Local currentFontFamilyIndex: number = 0;

  aboutToAppear() {
    this.updateArcButtons();
  }

  updateArcButtons() {
    const customBgColor: ColorMetrics = ColorMetrics.resourceColor('#FF6200EE');
    const customFontColor: ColorMetrics = ColorMetrics.resourceColor('#FFFFFFFF');

    this.topOptions = new ArcButtonOptions({
      label: '点击测试',
      position: ArcButtonPosition.TOP_EDGE,
      styleMode: ArcButtonStyleMode.CUSTOM,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(16, LengthUnit.FP),
      shadowEnabled: true,
      backgroundColor: customBgColor,
      fontColor: customFontColor,
      fontStyle: this.fontStyles[this.currentFontStyleIndex],
      fontFamily: this.fontFamilies[this.currentFontFamilyIndex],
      onClick: (event) => {
        this.clickCount++;
        console.info('ArcButton clicked, count: ' + this.clickCount);
      },
      onTouch: (event) => {
        let touchType = '';
        switch (event.type) {
          case TouchType.Down:
            touchType = '按下';
            break;
          case TouchType.Up:
            touchType = '抬起';
            break;
          case TouchType.Move:
            touchType = '移动';
            break;
          case TouchType.Cancel:
            touchType = '取消';
            break;
          default:
            touchType = '未知';
        }
        this.touchInfo = `触摸: ${touchType}\n位置: (${event.touches[0].x.toFixed(0)}, ${event.touches[0].y.toFixed(0)})`;
        console.info('ArcButton touch: ' + touchType);
      }
    });

    this.bottomOptions = new ArcButtonOptions({
      label: '样式: ' + this.fontStyleNames[this.currentFontStyleIndex],
      styleMode: ArcButtonStyleMode.CUSTOM,
      status: ArcButtonStatus.NORMAL,
      fontSize: new LengthMetrics(14, LengthUnit.FP),
      shadowEnabled: true,
      backgroundColor: customBgColor,
      fontColor: customFontColor,
      fontStyle: this.fontStyles[this.currentFontStyleIndex],
      fontFamily: this.fontFamilies[this.currentFontFamilyIndex]
    });
  }

  build() {
    Column() {
      // 标题和统计
      Column() {
        Text('ArcButton 事件与字体')
          .fontSize(20)
          .fontWeight(FontWeight.Bold)
          .margin({ bottom: 15 })

        Row() {
          Text('点击次数: ')
            .fontSize(14)
          Text(this.clickCount.toString())
            .fontSize(14)
            .fontColor('#FF6200EE')
            .fontWeight(FontWeight.Bold)
        }
        .margin({ bottom: 10 })

        Text(this.touchInfo)
          .fontSize(12)
          .fontColor('#666666')
          .height(50)
      }
      .width(300)
      .padding(15)
      .backgroundColor('#F0F0F0')
      .borderRadius(10)
      .margin({ top: 20, bottom: 10 })

      // 字体样式控制
      Column() {
        Text('字体样式')
          .fontSize(16)
          .fontWeight(FontWeight.Bold)
          .margin({ bottom: 10 })

        // 字体样式切换
        Row() {
          Text('样式: ')
            .fontSize(14)
          Text(this.fontStyleNames[this.currentFontStyleIndex])
            .fontSize(14)
            .fontColor('#FF6200EE')
            .fontWeight(FontWeight.Bold)
        }
        .width('100%')
        .margin({ bottom: 5 })

        Row() {
          Button('正常')
            .fontSize(12)
            .width(60)
            .height(30)
            .margin({ right: 10 })
            .onClick(() => {
              this.currentFontStyleIndex = 0;
              this.topOptions.fontStyle = this.fontStyles[0];
              this.bottomOptions.fontStyle = this.fontStyles[0];
              this.bottomOptions.label = '样式: ' + this.fontStyleNames[0];
            })

          Button('斜体')
            .fontSize(12)
            .width(60)
            .height(30)
            .onClick(() => {
              this.currentFontStyleIndex = 1;
              this.topOptions.fontStyle = this.fontStyles[1];
              this.bottomOptions.fontStyle = this.fontStyles[1];
              this.bottomOptions.label = '样式: ' + this.fontStyleNames[1];
            })
        }
        .width('100%')
        .margin({ bottom: 15 })

        // 字体族切换
        Row() {
          Text('字体: ')
            .fontSize(14)
          Text(this.fontFamilies[this.currentFontFamilyIndex])
            .fontSize(14)
            .fontColor('#FF6200EE')
            .fontWeight(FontWeight.Bold)
        }
        .width('100%')
        .margin({ bottom: 5 })

        Row() {
          Button('无衬线')
            .fontSize(10)
            .width(60)
            .height(30)
            .margin({ right: 5 })
            .onClick(() => {
              this.currentFontFamilyIndex = 0;
              this.topOptions.fontFamily = this.fontFamilies[0];
              this.bottomOptions.fontFamily = this.fontFamilies[0];
            })

          Button('衬线')
            .fontSize(10)
            .width(60)
            .height(30)
            .margin({ right: 5 })
            .onClick(() => {
              this.currentFontFamilyIndex = 1;
              this.topOptions.fontFamily = this.fontFamilies[1];
              this.bottomOptions.fontFamily = this.fontFamilies[1];
            })

          Button('等宽')
            .fontSize(10)
            .width(60)
            .height(30)
            .onClick(() => {
              this.currentFontFamilyIndex = 2;
              this.topOptions.fontFamily = this.fontFamilies[2];
              this.bottomOptions.fontFamily = this.fontFamilies[2];
            })
        }
        .width('100%')
      }
      .width(300)
      .padding(15)
      .backgroundColor('#F0F0F0')
      .borderRadius(10)
      .margin({ bottom: 10 })

      // ArcButton展示区域
      Stack() {
        Circle({ width: 233, height: 233 })
          .strokeWidth(0.1)
          .fill(Color.White)

        Column() {
          ArcButton({ options: this.topOptions })
          Blank()
          ArcButton({ options: this.bottomOptions })
        }
        .width('100%')
        .height('100%')
      }
      .width(233)
      .height(233)
      .margin({ top: 10 })

      // 说明文字
      Text('点击上方按钮测试事件，下方按钮查看字体样式')
        .fontSize(12)
        .fontColor('#666666')
        .width(280)
        .textAlign(TextAlign.Center)
        .margin({ top: 10 })
    }
    .width('100%')
    .height('100%')
    .backgroundColor(Color.Gray)
  }
}
