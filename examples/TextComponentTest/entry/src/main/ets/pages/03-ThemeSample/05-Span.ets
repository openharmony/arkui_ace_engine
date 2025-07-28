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

import { LengthMetrics } from '@kit.ArkUI';
import { common } from '@kit.AbilityKit';

@Entry
@Component
struct Index_Span {
  build() {
    Scroll() {
      Column() {

        Column() {
          Text(' 测试点 Span create ')
          Text() {
            Span($r('app.string.TextInputPlaceholder'))
          }
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 Span font ')
          Text(' 浅色 Sans，深色 Sans Condensed ')
          Text() {
            Span($r('app.string.TextInputPlaceholder'))
              .font({
                size: $r('app.float.TextFontSize'),
                family: $r('app.string.TextFontFamily'),
              })
          }
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 Span fontColor ')
          Text() {
            Span($r('app.string.TextInputPlaceholder'))
              .fontColor($r('app.color.ModeColor'))
          }
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 Span fontWeight')
          Text(' 浅色 {400} 深色 {900} ')
          Text() {
            Span($r('app.string.TextInputPlaceholder'))
              .fontWeight((this.getUIContext()
                .getHostContext() as common.UIAbilityContext).resourceManager.getNumber($r('app.float.ModeWeight400_900')
                .id),)
          }
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 Span letterSpacing ')
          Text(' 浅色 letterSpacing 5，深色 letterSpacing 50 ')
          Text() {
            Span($r('app.string.TextInputPlaceholder'))
              .letterSpacing((this.getUIContext()
                .getHostContext() as common.UIAbilityContext).resourceManager.getNumber($r('app.float.TextLetterSpacing')
                .id))
          }
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)


        Column() {
          Text(' 测试点 Span baselineOffset ')
          Text(' 浅色 5，深色 20 ')
          Text() {
            Span($r('app.string.TextInputPlaceholder'))
              .baselineOffset(LengthMetrics.vp((this.getUIContext()
                .getHostContext() as common.UIAbilityContext).resourceManager.getNumber($r('app.float.TextLineSpacing')
                .id)))
          }
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 Span textShadow {radius, color, offsetX, offsetY} ')
          Text(' 浅色 textShadow {10, Red, 50, 0}，深色 {1, Blue, 0, 50} ').borderWidth(2).borderColor(Color.Red)
          Text() {
            Span($r('app.string.TextInputPlaceholder'))
              .fontColor(Color.Black)
              .textShadow({
                radius: $r('app.float.TextShadowRadius'),
                color: $r('app.color.TextShadowColor'),
                offsetX: $r('app.float.TextShadowOffsetX'),
                offsetY: $r('app.float.TextShadowOffsetY'),
              })
          }
          .height(100)
          .backgroundColor(Color.White)
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 Span dataDetectorConfig ')
          Text(' 浅色  {字 Red 下划线 Yellow }，深色 {字 Blue 下划线 Pink }  ')
          Text() {
            Span(' 邮箱：***@example.com \n ').borderWidth(2).borderColor(Color.Red)
              .decoration({
                type: TextDecorationType.Underline,
                color: $r('app.color.TextdataDetectorConfigDecorationColor'),
                style: TextDecorationStyle.SOLID
              })
          }
        }.borderWidth(1)

        Column() {
          Text(' 测试点 Span lineHeight ')
          Text(' 浅色 lineHeight 20，深色 lineHeight 50 ')
          Text() {
            Span($r('app.string.TextInputPlaceholder'))
              .lineHeight($r('app.float.TextLineHeight'))
          }
        }.borderWidth(2).borderColor(Color.Red)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 ImageSpan textBackgroundStyle ')
          Text() {
            Span($r('app.string.TextInputPlaceholder'))
              .width(200)
              .height(200)
              .textBackgroundStyle({
                color: $r('app.color.ModeColor'),
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
          }
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

      }
    }
  }
}