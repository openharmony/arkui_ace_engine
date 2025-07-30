/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { common } from '@kit.AbilityKit';

@Entry
@Component
struct Index_TextInput {
  build() {
    Scroll() {
      Column({ space: 10 }) {
        Column() {
          Text(' 测试点 TextInput create placeholder ')
          TextInput({ placeholder: $r('app.string.TextInputPlaceholder') }).borderColor(Color.Red)
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 TextInput create text ')
          TextInput({ text: $r('app.string.TextInputPlaceholder') })
        }.borderWidth(1).borderColor(Color.Red)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 TextInput PlaceholderColor ')
          Text(' 浅色 Red 深色 Blue ')
          TextInput({ placeholder: $r('app.string.TextInputPlaceholder') }).borderColor(Color.Red)
            .placeholderColor($r('app.color.ModeColor'))
        }.borderWidth(1).borderColor(Color.Red)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 TextInput PlaceholderFont ')
          Text(' placeholderFont fontSize 浅色 16 深色 32 ')
          Text(' placeholderFont fontFamily 浅色 Sans，深色 Sans Condensed ').borderColor(Color.Red)
          TextInput({ placeholder: $r('app.string.TextInputPlaceholder') }).borderColor(Color.Red)
            .placeholderFont({
              size: $r('app.float.TextFontSize'),
              family: $r('app.string.TextFontFamily'),
            })
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 TextInput backgroundColor ')
          Text(' 浅色 Red 深色 Blue ')
          TextInput({ text: $r('app.string.TextInputPlaceholder') }).borderColor(Color.Red)
            .backgroundColor($r('app.color.ModeColor'))
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 TextInput caretColor ')
          Text(' 浅色 Red 深色 Blue ')
          TextInput({ text: $r('app.string.TextInputPlaceholder') }).borderColor(Color.Red)
            .caretColor($r('app.color.ModeColor'))
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 TextInput backgroundColor ')
          Text(' 浅色 Red 深色 Blue ')
          TextInput({ text: $r('app.string.TextInputPlaceholder') }).borderColor(Color.Red)
            .selectedBackgroundColor($r('app.color.ModeColor'))
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 TextInput caretStyle ')
          Text(' 浅色 Red 深色 Blue ')
          Text(' 浅色 5 深色 20 ')
          TextInput({ text: $r('app.string.TextInputPlaceholder') })
            .caretStyle({
              color: $r('app.color.ModeColor'),
              width: $r('app.float.ModeNumber5_20')
            })
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 TextInput width ')
          Text(' 浅色 5 深色 20 ')
          TextInput({ text: $r('app.string.TextInputPlaceholder') })
            .width($r('app.float.ModeNumber5_20'))
        }.borderWidth(1).borderColor(Color.Red)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 TextInput height ')
          Text(' 浅色 20 深色 50 ')
          TextInput({ text: $r('app.string.TextInputPlaceholder') })
            .height($r('app.float.ModeNumber20_50'))
        }.borderWidth(1).borderColor(Color.Red)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 TextInput padding ')
          Text(' 浅色 {5 5 20 20} 深色 {20 20 50 50 } ')
          TextInput({ text: $r('app.string.TextInputPlaceholder') }).borderWidth(1).borderColor(Color.Red)
            .padding({
              top: (this.getUIContext()
                .getHostContext() as common.UIAbilityContext).resourceManager.getNumber($r('app.float.ModeNumber5_20')
                .id),
              right: (this.getUIContext()
                .getHostContext() as common.UIAbilityContext).resourceManager.getNumber($r('app.float.ModeNumber5_20')
                .id),
              bottom: (this.getUIContext()
                .getHostContext() as common.UIAbilityContext).resourceManager.getNumber($r('app.float.ModeNumber20_50')
                .id),
              left: (this.getUIContext()
                .getHostContext() as common.UIAbilityContext).resourceManager.getNumber($r('app.float.ModeNumber20_50')
                .id),
            })
        }.borderWidth(1).borderColor(Color.Red)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 TextInput margin ')
          Text(' 浅色 {5 5 20 20} 深色 {20 20 50 50 } ')
          TextInput({ text: $r('app.string.TextInputPlaceholder') }).borderWidth(1).borderColor(Color.Red)
            .margin({
              top: (this.getUIContext()
                .getHostContext() as common.UIAbilityContext).resourceManager.getNumber($r('app.float.ModeNumber5_20')
                .id),
              right: (this.getUIContext()
                .getHostContext() as common.UIAbilityContext).resourceManager.getNumber($r('app.float.ModeNumber5_20')
                .id),
              bottom: (this.getUIContext()
                .getHostContext() as common.UIAbilityContext).resourceManager.getNumber($r('app.float.ModeNumber20_50')
                .id),
              left: (this.getUIContext()
                .getHostContext() as common.UIAbilityContext).resourceManager.getNumber($r('app.float.ModeNumber20_50')
                .id),
            })
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)


        Column() {
          Text(' 测试点 TextInput border ，测试 border:{width color radius} ')
          Text(' 浅色 {width color radius}={5 Red 5} 深色 {width color radius}={20 Blue 20} ')
          TextInput({ text: $r('app.string.TextInputPlaceholder') })
            .border({
              width: {
                top: (this.getUIContext()
                  .getHostContext() as common.UIAbilityContext).resourceManager.getNumber($r('app.float.ModeNumber5_20')
                  .id),
                right: (this.getUIContext()
                  .getHostContext() as common.UIAbilityContext).resourceManager.getNumber($r('app.float.ModeNumber5_20')
                  .id),
                bottom: (this.getUIContext()
                  .getHostContext() as common.UIAbilityContext).resourceManager.getNumber($r('app.float.ModeNumber20_50')
                  .id),
                left: (this.getUIContext()
                  .getHostContext() as common.UIAbilityContext).resourceManager.getNumber($r('app.float.ModeNumber20_50')
                  .id),
              },
              color: {
                top: $r('app.color.ModeColor'),
                right: $r('app.color.ModeColorYellow_Pink'),
                bottom: $r('app.color.ModeColor'),
                left: $r('app.color.ModeColorYellow_Pink'),
              },
              radius: {
                topLeft: (this.getUIContext()
                  .getHostContext() as common.UIAbilityContext).resourceManager.getNumber($r('app.float.ModeNumber5_20')
                  .id),
                topRight: (this.getUIContext()
                  .getHostContext() as common.UIAbilityContext).resourceManager.getNumber($r('app.float.ModeNumber5_20')
                  .id),
                bottomLeft: (this.getUIContext()
                  .getHostContext() as common.UIAbilityContext).resourceManager.getNumber($r('app.float.ModeNumber20_50')
                  .id),
                bottomRight: (this.getUIContext()
                  .getHostContext() as common.UIAbilityContext).resourceManager.getNumber($r('app.float.ModeNumber20_50')
                  .id),
              }
            })
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 TextInput borderWidth ')
          Text(' 浅色 {5 5 20 20} 深色 {20 20 50 50 } ')
          TextInput({ text: $r('app.string.TextInputPlaceholder') })
            .borderWidth({
              top: (this.getUIContext()
                .getHostContext() as common.UIAbilityContext).resourceManager.getNumber($r('app.float.ModeNumber5_20')
                .id),
              right: (this.getUIContext()
                .getHostContext() as common.UIAbilityContext).resourceManager.getNumber($r('app.float.ModeNumber5_20')
                .id),
              bottom: (this.getUIContext()
                .getHostContext() as common.UIAbilityContext).resourceManager.getNumber($r('app.float.ModeNumber20_50')
                .id),
              left: (this.getUIContext()
                .getHostContext() as common.UIAbilityContext).resourceManager.getNumber($r('app.float.ModeNumber20_50')
                .id),
            })
            .borderColor($r('app.color.ModeColor'))
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 TextInput borderColor')
          Text(' 浅色 {Red Yellow} 深色 {Blue Pink} ')
          TextInput({ text: $r('app.string.TextInputPlaceholder') })
            .borderWidth(1)
            .borderColor({
              top: $r('app.color.ModeColor'),
              right: $r('app.color.ModeColorYellow_Pink'),
              bottom: $r('app.color.ModeColor'),
              left: $r('app.color.ModeColorYellow_Pink'),
            })
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 TextInput borderRadius')
          Text(' 浅色 {Red Yellow} 深色 {Blue Pink} ')
          TextInput({ text: $r('app.string.TextInputPlaceholder') })
            .borderWidth(1)
            .borderColor($r('app.color.ModeColor'))
            .borderRadius({
              topLeft: (this.getUIContext()
                .getHostContext() as common.UIAbilityContext).resourceManager.getNumber($r('app.float.ModeNumber5_20')
                .id),
              topRight: (this.getUIContext()
                .getHostContext() as common.UIAbilityContext).resourceManager.getNumber($r('app.float.ModeNumber5_20')
                .id),
              bottomLeft: (this.getUIContext()
                .getHostContext() as common.UIAbilityContext).resourceManager.getNumber($r('app.float.ModeNumber20_50')
                .id),
              bottomRight: (this.getUIContext()
                .getHostContext() as common.UIAbilityContext).resourceManager.getNumber($r('app.float.ModeNumber20_50')
                .id),
            })
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 TextInput fontSize')
          Text(' 浅色 {20} 深色 {50} ')
          TextInput({ text: $r('app.string.TextInputPlaceholder') })
            .fontSize($r('app.float.ModeNumber20_50'))
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 TextInput fontColor')
          Text(' 浅色 {20} 深色 {50} ')
          TextInput({ text: $r('app.string.TextInputPlaceholder') })
            .fontColor($r('app.color.ModeColor'))
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 TextInput fontWeight')
          Text(' 浅色 {400} 深色 {900} ')
          TextInput({ text: $r('app.string.TextInputPlaceholder') })
            .fontWeight((this.getUIContext()
              .getHostContext() as common.UIAbilityContext).resourceManager.getNumber($r('app.float.ModeWeight400_900')
              .id),)
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 TextInput fontFamily')
          Text(' 浅色 Sans，深色 Sans Condensed ')
          TextInput({ text: $r('app.string.TextInputPlaceholder') })
            .fontFamily($r('app.string.TextFontFamily'))
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 用来对比 Min ')
          TextInput({ text: '浅色 minFontScale 1.0，深色 minFontScale 1.0，原本字体大小是 16 ' })
            .borderWidth(2)
            .borderColor(Color.Blue)
            .fontSize(16)
            .minFontScale(1)
        }.borderWidth(1)

        Column() {
          Text(' 测试点 Text SetMinFontScale minFontScale ')
          TextInput({ text: ' 浅色 minFontScale 0，深色 minFontScale 1.0，原本字体大小是 16 ' })
            .borderWidth(2)
            .borderColor(Color.Red)
            .fontSize(16)
            .minFontScale($r('app.float.TextMinFontScale'))
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)


        Column() {
          Text(' 用来对比 Max ')
          TextInput({ text: '浅色 maxFontScale 1.0，深色 maxFontScale 1.0，原本字体大小是 16' })
            .borderWidth(2)
            .borderColor(Color.Blue)
            .fontSize(16)
            .maxFontScale(1)
        }.borderWidth(1)

        Column() {
          Text(' 测试点 Text SetMaxFontScale maxFontScale ')
          TextInput({ text: ' 浅色 maxFontScale 3.2，深色 maxFontScale 1.0，原本字体大小是 16 ' })
            .borderWidth(2)
            .borderColor(Color.Red)
            .fontSize(16)
            .maxFontScale($r('app.float.TextMaxFontScale'))
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 TextInput inputFilter')
          Text(' 浅色 [a-z]，深色 [0-9] ')
          TextInput({ text: $r('app.string.TextInputPlaceholder') })
            .inputFilter($r('app.string.inputFilter'))
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)


        Column() {
          Text(' 测试点 TextInput foregroundColor ')
          Text(' 浅色 foregroundColor Red，深色 foregroundColor Blue ')
          TextInput({ text: $r('app.string.TextInputPlaceholder') })
            .foregroundColor($r('app.color.TextColor'))
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)


        Column() {
          Text(' 测试点 TextInput showError ')
          Text(' 浅色 [a-z]，深色 [0-9] ')
          TextInput({ text: $r('app.string.TextInputPlaceholder') })
            .showError($r('app.string.TextInputPlaceholder'))
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)


        Column() {
          Text(' 测试点 TextInput passwordIcon ')
          Text(' 浅色 ，深色 ，on，off，共展示四个 ')
          TextInput({ text: $r('app.string.TextInputPlaceholder') })
            .type(InputType.Password)
            .showPasswordIcon(true)
            .passwordIcon({ onIconSrc: $r('app.media.onIcon'), offIconSrc: $r('app.media.offIcon') })
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)


        Column() {
          Text(' 测试点 TextInput underlineColor ')
          Text(' 浅色 ，深色 { normal typing error disable } ')
          TextInput({ text: $r('app.string.TextInputPlaceholder') })
            .underlineColor({
              normal: $r('app.color.ModeColor'),
              typing: $r('app.color.ModeColorYellow_Pink'),
              error: $r('app.color.ModeColor'),
              disable: $r('app.color.ModeColorYellow_Pink'),
            })
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 TextInput cancelButton ')
          Text(' 浅色 ，深色 { size color src } ')
          TextInput({ text: $r('app.string.TextInputPlaceholder') })
            .type(InputType.Password)
            .showPasswordIcon(true)
            .cancelButton({
              icon: {
                size: $r('app.float.ModeNumber5_20'),
                color: $r('app.color.ModeColor'),
                src: $r('app.media.onIcon'),
              },
            })
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 TextInput decoration ')
          Text(' 浅色 ，深色 decoration { LineThrough, color, SOLID } ')
          TextInput({ text: $r('app.string.TextInputPlaceholder') })
            .decoration({
              type: TextDecorationType.LineThrough,
              color: $r('app.color.ModeColor'),
              style: TextDecorationStyle.SOLID
            })
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 TextInput minFontSize maxFontSize ')
          Text(' 对比 fontSize 8，不缩放')
            .borderWidth(2)
            .borderColor(Color.Blue)
            .minFontScale(1)
            .maxFontScale(1)
            .fontSize(8)
          Text(' 对比 fontSize 16，不缩放')
            .borderWidth(2)
            .borderColor(Color.Blue)
            .minFontScale(1)
            .maxFontScale(1)
            .fontSize(16)
          Text(' 对比 fontSize 32，不缩放')
            .borderWidth(2)
            .borderColor(Color.Blue)
            .minFontScale(1)
            .maxFontScale(1)
            .fontSize(32)
          Text(' 对比 fontSize 64，不缩放')
            .borderWidth(2)
            .borderColor(Color.Blue)
            .minFontScale(1)
            .maxFontScale(1)
            .fontSize(64)
          Text(' 浅色 min/max = 16/16，深色 min/max = 4/64，设置 fontSize 16 ')
          TextInput({ text: $r('app.string.TextInputPlaceholder') })
            .borderWidth(2)
            .borderColor(Color.Red)
            .minFontSize($r('app.float.TextMinFontSize'))
            .maxFontSize($r('app.float.TextMaxFontSize'))
            .fontSize(16)
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 TextInput letterSpacing ')
          Text(' 浅色 letterSpacing 5，深色 letterSpacing 50 ')
          TextInput({ text: $r('app.string.TextInputPlaceholder') }).borderWidth(2).borderColor(Color.Red)
            .letterSpacing((this.getUIContext()
              .getHostContext() as common.UIAbilityContext).resourceManager.getNumber($r('app.float.TextLetterSpacing')
              .id))
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 TextInput lineHeight ')
          Text(' 浅色 lineHeight 20，深色 lineHeight 50 ')
          TextInput({ text: $r('app.string.TextInputPlaceholder') }).borderWidth(2).borderColor(Color.Red)
            .lineHeight($r('app.float.TextLineHeight'))
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 TextInput textIndent ')
          Text(' 浅色 textIndent 5，深色 textIndent 50 ')
          TextInput({ text: $r('app.string.TextInputPlaceholder') }).borderWidth(2).borderColor(Color.Red)
            .textIndent($r('app.float.TextIndent'))
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

      }
    }
  }
}