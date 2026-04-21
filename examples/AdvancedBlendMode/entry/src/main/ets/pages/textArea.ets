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

import { uiEffect } from "@kit.ArkGraphics2D";
import ConfigurationConstant from '@ohos.app.ability.ConfigurationConstant';
import common from '@ohos.app.ability.common';

// 创建亮度混合器
let blender: uiEffect.BrightnessBlender = uiEffect.createBrightnessBlender({
  cubicRate: 0.5,
  quadraticRate: 0.5,
  linearRate: 0.5,
  degree: 0.5,
  saturation: 0.5,
  positiveCoefficient: [2.3, 4.5, 2.0],
  negativeCoefficient: [0.5, 2.0, 0.5],
  fraction: 0
});

// 定义阴影样式常量（方便复用）
interface GeneratedObjectLiteralInterface_1 {
  radius: number;
  color: Color;
  offsetX: number;
  offsetY: number;
}

const textShadowStyle: GeneratedObjectLiteralInterface_1 = {
  radius: 10,
  color: Color.Yellow,
  offsetX: 2,
  offsetY: 2
};

@Entry
@Component
export struct MaskDemo {
  @State mUseOffscreen: boolean = false;
  @State blendApplyType: BlendApplyType | null | undefined = BlendApplyType.OFFSCREEN_WITH_BACKGROUND;
  @State isBrightnessEnabled: boolean = false;
  @State isTextColorEnabled: boolean = false;
  @State isTextShadowEnabled: boolean = false;
  @State isDark: boolean = false;
  @State isItalic: boolean = false;
  @State context: common.UIAbilityContext = getContext(this) as common.UIAbilityContext;
  // 输入框内容状态变量（适配多行文本）
  @State inputValue: string = String.fromCodePoint(0x1F600) + 'بۇلۇڭغۇم ئۇيغۇرچەدەك بۇرۇنغۇ چاغلىق، رەشىتلىك ۋە ئۇرۇمچىدىكى خېمتەر ئەگەرىدەك خۇشاللىقى، ئۇرۇمچىدىكى يېڭى يېزىدەك يېقىملىقى， ئۇرۇمچىدىكى قەشقەر دەرۋازىسىدەك تەكلىكلىقى بىلەن يېزىلگەن بۇرۇنغۇ مەزمۇن. ئۇرۇمچى، ئۇلۇغ خەلقۇمۇزىڭ ئۇرۇمچى ئۇلۇسلىك ئۇلۇغ شەھىرى، شىنجاڭ ئۇيغۇر ئاپتونوم رايونىڭ مۈلۈك، ئىسلام ئىشلەر، تېخنىك، تۇرۇش， ' + String.fromCodePoint(0x1F600);

  build() {
    Column() {
      if (this.mUseOffscreen) {
        Stack() {
          // 文本区域列（替换原输入框列）
          Column() {
            TextArea({ text: this.inputValue })
              .fontSize(25)
              .fontColor(this.isTextColorEnabled ? Color.Red : Color.White)
              .fontStyle(this.isItalic ? FontStyle.Italic : FontStyle.Normal)
              .width('100%')
              .height('100%')
              .maxLength(1000) // 限制最大长度
              .textAlign(TextAlign.Start) // 文本左对齐
              .onChange((value: string) => {
                this.inputValue = value;
              })
          }
          .advancedBlendMode(this.isBrightnessEnabled ? blender : null, BlendApplyType.FAST)

          // 渐变遮罩层（保持不变）
          Column()
            .width('100%')
            .height('100%')
            .linearGradient({
              direction: GradientDirection.Right,
              colors: [
                [Color.Transparent, 0.0],
                [Color.Black, 0.35],
                [Color.Black, 0.65],
                [Color.Transparent, 1.0]
              ]
            })
            .blendMode(BlendMode.DST_IN, BlendApplyType.FAST)
        }
        .margin({ top: 100 }) // 调整顶部边距，适配多行显示
        .advancedBlendMode(BlendMode.SRC_OVER, this.blendApplyType)
        .width('100%')
        .height('40%') // 增加高度，适应多行文本
      } else {
        // 未启用遮罩时的文本区域展示
        Stack() {
          Column() {
            TextArea({ text: this.inputValue })
              .fontSize(25)
              .fontColor(this.isTextColorEnabled ? Color.Red : Color.White)
              .fontStyle(this.isItalic ? FontStyle.Italic : FontStyle.Normal)
              .width('100%')
              .height('100%')
              .maxLength(1000)
              .textAlign(TextAlign.Start)
              .onChange((value: string) => {
                this.inputValue = value;
              })
          }
        }
        .margin({ top: 100 })
        .width('100%')
        .height('40%')
      }

      // 控制按钮区域保持不变
      Button(this.isBrightnessEnabled ? '关闭提亮' : '开启提亮')
        .backgroundColor(this.isBrightnessEnabled ? Color.Green : Color.Blue)
        .fontColor(Color.White)
        .padding({ left: 20, right: 20, top: 5, bottom: 5 })
        .margin({ top: 20 })
        .onClick(() => {
          this.isBrightnessEnabled = !this.isBrightnessEnabled;
        })

      Button(this.isTextColorEnabled ? '关闭文本颜色' : '开启文本颜色')
        .backgroundColor(this.isTextColorEnabled ? Color.Red : Color.Gray)
        .fontColor(Color.White)
        .padding({ left: 20, right: 20, top: 5, bottom: 5 })
        .margin({ top: 10 })
        .onClick(() => {
          this.isTextColorEnabled = !this.isTextColorEnabled;
        })

      Button(this.isItalic ? '切换为正常样式' : '切换为斜体样式')
        .backgroundColor(this.isItalic ? Color.Black : Color.Gray)
        .fontColor(Color.White)
        .padding({ left: 20, right: 20, top: 5, bottom: 5 })
        .margin({ top: 10 })
        .onClick(() => {
          this.isItalic = !this.isItalic;
        })

      Button("切换深浅色模式")
        .onClick(() => {
          this.isDark = !this.isDark;
          this.context.getApplicationContext().setColorMode(
            this.isDark ? ConfigurationConstant.ColorMode.COLOR_MODE_DARK : ConfigurationConstant.ColorMode.COLOR_MODE_LIGHT
          );
        })

      Column() {
        Row({ space: 10 }) {
          Button('FAST')
            .backgroundColor(this.blendApplyType === BlendApplyType.FAST ? Color.Orange : Color.Gray)
            .fontColor(Color.White)
            .padding({ left: 15, right: 15 })
            .onClick(() => {
              this.blendApplyType = BlendApplyType.FAST;
            })

          Button('OFFSCREEN')
            .backgroundColor(this.blendApplyType === BlendApplyType.OFFSCREEN ? Color.Orange : Color.Gray)
            .fontColor(Color.White)
            .padding({ left: 15, right: 15 })
            .onClick(() => {
              this.blendApplyType = BlendApplyType.OFFSCREEN;
            })

          Button('WITH_BACKGROUND')
            .backgroundColor(this.blendApplyType === BlendApplyType.OFFSCREEN_WITH_BACKGROUND ? Color.Orange : Color.Gray)
            .fontColor(Color.White)
            .padding({ left: 15, right: 15 })
            .onClick(() => {
              this.blendApplyType = BlendApplyType.OFFSCREEN_WITH_BACKGROUND;
            })
        }
        .margin({ top: 10 })

        Row({ space: 10 }) {
          Button('NULL')
            .backgroundColor(this.blendApplyType === null ? Color.Orange : Color.Gray)
            .fontColor(Color.White)
            .padding({ left: 15, right: 15 })
            .onClick(() => {
              this.blendApplyType = null;
            })

          Button('UNDEFINED')
            .backgroundColor(this.blendApplyType === undefined ? Color.Orange : Color.Gray)
            .fontColor(Color.White)
            .padding({ left: 15, right: 15 })
            .onClick(() => {
              this.blendApplyType = undefined;
            })
        }
        .margin({ top: 5 })
      }
      .justifyContent(FlexAlign.Center)

      Row() {
        Text('useBrightnessAndGradientColor:')
          .fontColor(Color.Red)
          .margin({ right: 10 })

        Button(this.mUseOffscreen ? '已启用' : '未启用')
          .backgroundColor(this.mUseOffscreen ? Color.Orange : Color.Gray)
          .fontColor(Color.White)
          .padding({ left: 20, right: 20 })
          .onClick(() => {
            this.mUseOffscreen = !this.mUseOffscreen;
          })
      }
      .margin({ top: 10 })
    }
    .justifyContent(FlexAlign.Center)
    .backgroundImage($r('app.media.lan'))
    .backgroundColor(Color.Black)
    .width('100%')
    .height('100%')
  }
}
