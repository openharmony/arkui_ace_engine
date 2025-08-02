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
struct Index_Search {
  build() {
    Scroll() {
      Column() {
        Column() {
          Text(' 测试点 Search create placeholder ')
          Search({ placeholder: $r('app.string.TextInputPlaceholder') }).borderColor(Color.Red)
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 Search create text ')
          Search({
            value: (this.getUIContext()
              .getHostContext() as common.UIAbilityContext).resourceManager.getStringSync($r('app.string.TextInputPlaceholder')
              .id)
          })
        }.borderWidth(1).borderColor(Color.Red)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 TextInput searchButton ')
          Text(' 浅色 ，深色 ，{ value, {fontSize fontColor} } ')
          Search({
            value: (this.getUIContext()
              .getHostContext() as common.UIAbilityContext).resourceManager.getStringSync($r('app.string.TextInputPlaceholder')
              .id)
          })
            .searchButton(
              (this.getUIContext()
                .getHostContext() as common.UIAbilityContext).resourceManager.getStringSync($r('app.string.TextInputPlaceholder')
                .id),
              {
                fontSize: $r('app.float.ModeNumber5_20'),
                fontColor: $r('app.color.ModeColor'),
              },
            )
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 TextInput cancelButton ')
          Text(' 浅色 ，深色 { size color src } ')
          Search({
            value: (this.getUIContext()
              .getHostContext() as common.UIAbilityContext).resourceManager.getStringSync($r('app.string.TextInputPlaceholder')
              .id)
          })
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
          Text(' 测试点 Search fontColor')
          Text(' 浅色 {20} 深色 {50} ')
          Search({
            value: (this.getUIContext()
              .getHostContext() as common.UIAbilityContext).resourceManager.getStringSync($r('app.string.TextInputPlaceholder')
              .id)
          })
            .fontColor($r('app.color.ModeColor'))
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 Search caretStyle ')
          Text(' 浅色 Red 深色 Blue ')
          Search({
            value: (this.getUIContext()
              .getHostContext() as common.UIAbilityContext).resourceManager.getStringSync($r('app.string.TextInputPlaceholder')
              .id)
          })
            .caretStyle({
              color: $r('app.color.ModeColor'),
              width: $r('app.float.ModeNumber5_20')
            })
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 Search create placeholderFont ')
          Search({
            placeholder: (this.getUIContext()
              .getHostContext() as common.UIAbilityContext).resourceManager.getStringSync($r('app.string.TextInputPlaceholder')
              .id)
          })
            .placeholderFont({
              size: $r('app.float.TextFontSize'),
              family: $r('app.string.TextFontFamily'),
            })
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)


        Column() {
          Text(' 测试点 Search create placeholderFont ')
          Search({
            value: (this.getUIContext()
              .getHostContext() as common.UIAbilityContext).resourceManager.getStringSync($r('app.string.TextInputPlaceholder')
              .id)
          })
            .textFont({
              size: $r('app.float.TextFontSize'),
              family: $r('app.string.TextFontFamily'),
            })
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)


        Column() {
          Text(' 测试点 Search border ，测试 border:{width color radius} ')
          Text(' 浅色 {width color radius}={5 Red 5} 深色 {width color radius}={20 Blue 20} ')
          Search({
            value: (this.getUIContext()
              .getHostContext() as common.UIAbilityContext).resourceManager.getStringSync($r('app.string.TextInputPlaceholder')
              .id)
          })
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
          Text(' 测试点 Search height ')
          Text(' 浅色 20 深色 50 ')
          Search({
            value: (this.getUIContext()
              .getHostContext() as common.UIAbilityContext).resourceManager.getStringSync($r('app.string.TextInputPlaceholder')
              .id)
          })
            .height($r('app.float.ModeNumber20_50'))
        }.borderWidth(1).borderColor(Color.Red)

        Blank().borderWidth(5).height(1)


        Column() {
          Text(' 测试点 TextInput decoration ')
          Text(' 浅色 ，深色 decoration { LineThrough, color, SOLID } ')
          Search({
            value: (this.getUIContext()
              .getHostContext() as common.UIAbilityContext).resourceManager.getStringSync($r('app.string.TextInputPlaceholder')
              .id)
          })
            .decoration({
              type: TextDecorationType.LineThrough,
              color: $r('app.color.ModeColor'),
              style: TextDecorationStyle.SOLID
            })
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 用来对比 Min ')
          TextInput({ text: '浅色 minFontScale 1.0，深色 minFontScale 1.0，原本字体大小是 16 ' })
            .fontSize(16)
            .minFontScale(1)
        }.borderWidth(1)

        Column() {
          Text(' 测试点 Search SetMinFontScale minFontScale ')
          TextInput({ text: ' 浅色 minFontScale 0，深色 minFontScale 1.0，原本字体大小是 16 ' })
          Search({
            value: (this.getUIContext()
              .getHostContext() as common.UIAbilityContext).resourceManager.getStringSync($r('app.string.TextInputPlaceholder')
              .id)
          })
            .textFont({
              size: 16
            })
            .minFontScale($r('app.float.TextMinFontScale'))
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)


        Column() {
          Text(' 用来对比 Max ')
          TextInput({ text: '浅色 maxFontScale 1.0，深色 maxFontScale 1.0，原本字体大小是 16' })
            .fontSize(16)
            .maxFontScale(1)
        }.borderWidth(1)

        Column() {
          Text(' 测试点 Search SetMaxFontScale maxFontScale ')
          TextInput({ text: ' 浅色 maxFontScale 3.2，深色 maxFontScale 1.0，原本字体大小是 16 ' })
          Search({
            value: (this.getUIContext()
              .getHostContext() as common.UIAbilityContext).resourceManager.getStringSync($r('app.string.TextInputPlaceholder')
              .id)
          })
            .textFont({
              size: 16
            })
            .maxFontScale($r('app.float.TextMaxFontScale'))
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 Search letterSpacing ')
          Text(' 浅色 letterSpacing 5，深色 letterSpacing 50 ')
          Search({
            value: (this.getUIContext()
              .getHostContext() as common.UIAbilityContext).resourceManager.getStringSync($r('app.string.TextInputPlaceholder')
              .id)
          })
            .letterSpacing((this.getUIContext()
              .getHostContext() as common.UIAbilityContext).resourceManager.getNumber($r('app.float.TextLetterSpacing')
              .id))
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 TextInput lineHeight ')
          Text(' 浅色 lineHeight 20，深色 lineHeight 50 ')
          Search({
            value: (this.getUIContext()
              .getHostContext() as common.UIAbilityContext).resourceManager.getStringSync($r('app.string.TextInputPlaceholder')
              .id)
          })
            .lineHeight($r('app.float.TextLineHeight'))
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)


        Column() {
          Text(' 测试点 Search minFontSize maxFontSize ')
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
          Search({
            value: (this.getUIContext()
              .getHostContext() as common.UIAbilityContext).resourceManager.getStringSync($r('app.string.TextInputPlaceholder')
              .id)
          })
            .minFontSize($r('app.float.TextMinFontSize'))
            .maxFontSize($r('app.float.TextMaxFontSize'))
            .textFont({
              size: 16
            })
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 Search backgroundColor ')
          Text(' 浅色 Red 深色 Blue ')
          Search({
            value: (this.getUIContext()
              .getHostContext() as common.UIAbilityContext).resourceManager.getStringSync($r('app.string.TextInputPlaceholder')
              .id)
          })
            .backgroundColor($r('app.color.ModeColor'))
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 Search inputFilter')
          Text(' 浅色 [a-z]，深色 [0-9] ')
          Search({
            value: (this.getUIContext()
              .getHostContext() as common.UIAbilityContext).resourceManager.getStringSync($r('app.string.TextInputPlaceholder')
              .id)
          })
            .inputFilter($r('app.string.inputFilter'))
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 Search textIndent ')
          Text(' 浅色 textIndent 5，深色 textIndent 50 ')
          Search({
            value: (this.getUIContext()
              .getHostContext() as common.UIAbilityContext).resourceManager.getStringSync($r('app.string.TextInputPlaceholder')
              .id)
          })
            .textIndent($r('app.float.TextIndent'))
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

      }
    }
  }
}