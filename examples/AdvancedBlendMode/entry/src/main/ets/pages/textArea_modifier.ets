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


class MyButtonModifier implements AttributeModifier<ButtonAttribute> {
  blendApplyType: BlendApplyType | null | undefined = BlendApplyType.OFFSCREEN_WITH_BACKGROUND;
  index: number = 1

  applyNormalAttribute(instance: ButtonAttribute): void {
    if (this.index == 1) {
      this.blendApplyType = BlendApplyType.OFFSCREEN_WITH_BACKGROUND;
    } else if (this.index == 2){
      this.blendApplyType = null;
    } else if (this.index == 3){
      this.blendApplyType = undefined;
    }
  }
}

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
interface ShadowStyle {
  radius: number;
  color: Color;
  offsetX: number;
  offsetY: number;
}

const textShadowStyle: ShadowStyle = {
  radius: 10,
  color: Color.Yellow,
  offsetX: 2,
  offsetY: 2
};

@Entry
@Component
export struct MaskDemo {
  @State mUseOffscreen: boolean = false;
  @State modifier: MyButtonModifier = new MyButtonModifier();
  @State isBrightnessEnabled: boolean = false;
  @State isTextColorEnabled: boolean = false;
  @State isTextShadowEnabled: boolean = false;
  @State isDark: boolean = false;
  @State isItalic: boolean = false;
  @State context: common.UIAbilityContext = getContext(this) as common.UIAbilityContext;
  @State inputText: string = String.fromCodePoint(0x1F600) + 'بۇلۇڭغۇم ئۇيغۇرچەدەك بۇرۇنغۇ چاغلىق، رەشىتلىك ۋە ئۇرۇمچىدىكى خېمتەر ئەگەرىدەك خۇشاللىقى، ئۇرۇمچىدىكى يېڭى يېزىدەك يېقىملىقى، ئۇرۇمچىدىكى قەشقەر دەرۋازىسىدەك تەكلىكلىقى بىلەن يېزىلگەن بۇرۇنغۇ مەزمۇن. ئۇرۇمچى، ئۇلۇغ خەلقۇمۇزىڭ ئۇرۇمچى ئۇلۇسلىك ئۇلۇغ شەھىرى، شىنجاڭ ئۇيغۇر ئاپتونوم رايونىڭ مۈلۈك، ئىسلام ئىشلەر، تېخنىك، تۇرۇش، ' + String.fromCodePoint(0x1F600);

  build() {
    Column() {
      if (this.mUseOffscreen) {
        Stack() {
          Column() {
            // 将TextInput替换为TextArea
            TextArea({ text: this.inputText })
              .fontSize(25)
              .fontColor(this.isTextColorEnabled ? Color.Red : Color.White)
              .fontStyle(this.isItalic ? FontStyle.Italic : FontStyle.Normal)
              .onChange((value: string) => {
                this.inputText = value; // 同步输入内容
              })
              .width('100%')
              .height('100%')
              .padding(5)
          }
          .advancedBlendMode(this.isBrightnessEnabled ? blender : null, BlendApplyType.FAST)

          // 渐变遮罩层
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
        .margin({ top: 220 })
        .advancedBlendMode(BlendMode.SRC_OVER, this.modifier.blendApplyType)
        .width('100%')
        .height('15%')
      } else {
        // 未启用遮罩时的文本输入展示
        Stack() {
          Column() {
            // 将TextInput替换为TextArea
            TextArea({ text: this.inputText })
              .fontSize(25)
              .fontColor(this.isTextColorEnabled ? Color.Red : Color.White)
              .fontStyle(this.isItalic ? FontStyle.Italic : FontStyle.Normal)
              .onChange((value: string) => {
                this.inputText = value; // 同步输入内容
              })
              .width('100%')
              .height('100%')
              .padding(5)

          }
        }
        .margin({ top: 220 })
        .width('100%')
        .height('15%')
      }

      // 提亮控制按钮
      Button(this.isBrightnessEnabled ? '关闭提亮' : '开启提亮')
        .backgroundColor(this.isBrightnessEnabled ? Color.Green : Color.Blue)
        .fontColor(Color.White)
        .padding({ left: 20, right: 20, top: 5, bottom: 5 })
        .margin({ top: 20 })
        .onClick(() => {
          this.isBrightnessEnabled = !this.isBrightnessEnabled;
        })

      // 文本颜色控制按钮
      Button(this.isTextColorEnabled ? '关闭文本颜色' : '开启文本颜色')
        .backgroundColor(this.isTextColorEnabled ? Color.Red : Color.Gray)
        .fontColor(Color.White)
        .padding({ left: 20, right: 20, top: 5, bottom: 5 })
        .margin({ top: 10 })
        .onClick(() => {
          this.isTextColorEnabled = !this.isTextColorEnabled;
        })

      // 文本样式（斜体）控制按钮
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

      // 文本阴影控制按钮


      // 混合模式选择按钮组
      Column() {
        Row({ space: 10 }) {
          Button('WITH_BACKGROUND')
            .backgroundColor(this.modifier.blendApplyType === BlendApplyType.OFFSCREEN_WITH_BACKGROUND ? Color.Orange : Color.Gray)
            .attributeModifier(this.modifier)
            .fontColor(Color.White)
            .padding({ left: 15, right: 15 })
            .onClick(() => {
              this.modifier.index = 1
            })
        }
        .margin({ top: 10 })

        // null和undefined选项按钮
        Row({ space: 10 }) {
          Button('NULL')
            .backgroundColor(this.modifier.blendApplyType === null ? Color.Orange : Color.Gray)
            .fontColor(Color.White)
            .padding({ left: 15, right: 15 })
            .onClick(() => {
              this.modifier.index = 2
            })

          Button('UNDEFINED')
            .backgroundColor(this.modifier.blendApplyType === undefined ? Color.Orange : Color.Gray)
            .fontColor(Color.White)
            .padding({ left: 15, right: 15 })
            .onClick(() => {
              this.modifier.index = 3
            })
        }
        .margin({ top: 5 })
      }
      .justifyContent(FlexAlign.Center)

      // 功能开关按钮
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
    .width('100%')
    .height('100%')
  }
}