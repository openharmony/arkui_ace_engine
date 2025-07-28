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

import { TextModifier } from '@ohos.arkui.modifier';
import { LengthMetrics } from '@kit.ArkUI';
import { common } from '@kit.AbilityKit';

class TextCreateModifier extends TextModifier {
  applyNormalAttribute(instance: TextAttribute): void {
    super.applyNormalAttribute?.(instance);
  }

  public setGroup1(): void {
    this.layoutWeight(1.0)
    this.backgroundColor(Color.Pink)
    this.textAlign(TextAlign.Start)
    this.font({ weight: FontWeight.Bolder })
  }
}

class TextWidthModifier extends TextModifier {
  applyNormalAttribute(instance: TextAttribute): void {
    super.applyNormalAttribute?.(instance);
  }

  public setGroup1(): void {
    this.width($r('app.float.TextWith'))
  }
}

class TextHeightModifier extends TextModifier {
  applyNormalAttribute(instance: TextAttribute): void {
    super.applyNormalAttribute?.(instance);
  }

  public setGroup1(): void {
    this.height($r('app.float.TextHeight'))
  }
}

class TextFontFontSizeModifier extends TextModifier {
  applyNormalAttribute(instance: TextAttribute): void {
    super.applyNormalAttribute?.(instance);
  }

  public setGroup1(): void {
    this.font({ size: $r('app.float.TextFontSize') })
  }
}

class TextFontFontFamilyModifier extends TextModifier {
  applyNormalAttribute(instance: TextAttribute): void {
    super.applyNormalAttribute?.(instance);
  }

  public setGroup1(): void {
    this.font({ family: $r('app.string.TextFontFamily') })
  }
}

class TextFontSizeModifier extends TextModifier {
  applyNormalAttribute(instance: TextAttribute): void {
    super.applyNormalAttribute?.(instance);
  }

  public setGroup1(): void {
    this.fontSize($r('app.string.TextFontFamily'))
  }
}

class TextMinFontScaleModifier extends TextModifier {
  applyNormalAttribute(instance: TextAttribute): void {
    super.applyNormalAttribute?.(instance);
  }

  public setGroup1(): void {
    this.minFontScale($r('app.float.TextMinFontScale'))
  }
}

class TextMaxFontScaleModifier extends TextModifier {
  applyNormalAttribute(instance: TextAttribute): void {
    super.applyNormalAttribute?.(instance);
  }

  public setGroup1(): void {
    this.maxFontScale($r('app.float.TextMaxFontScale'))
  }
}

class TextFontColorModifier extends TextModifier {
  applyNormalAttribute(instance: TextAttribute): void {
    super.applyNormalAttribute?.(instance);
  }

  public setGroup1(): void {
    this.fontColor($r('app.color.TextColor'))
  }
}

class TextShadowModifier extends TextModifier {
  applyNormalAttribute(instance: TextAttribute): void {
    super.applyNormalAttribute?.(instance);
  }

  public setGroup1(): void {
    this.textShadow({
      radius: $r('app.float.TextShadowRadius'),
      color: $r('app.color.TextShadowColor'),
      offsetX: $r('app.float.TextShadowOffsetX'),
      offsetY: $r('app.float.TextShadowOffsetY'),
    })
  }
}

@Entry
@Component
struct Index_Text {
  @State textCreateModifier: TextModifier = new TextCreateModifier()
  textCreateController: TextController = new TextController()

  @State textWidthModifier: TextModifier = new TextWidthModifier()
  @State textHeightModifier: TextModifier = new TextHeightModifier()
  @State textFontFontSizeModifier: TextModifier = new TextFontFontSizeModifier()
  @State textFontFontFamilyModifier: TextModifier = new TextFontFontFamilyModifier()
  @State textFontSizeModifier: TextModifier = new TextFontSizeModifier()
  @State textMinFontScaleModifier: TextModifier = new TextMinFontScaleModifier()
  @State textMaxFontScaleModifier: TextModifier = new TextMaxFontScaleModifier()
  @State textFontColorModifier: TextModifier = new TextFontColorModifier()
  @State textShadowModifier: TextModifier = new TextShadowModifier()
  @State textResponseRegionController: TextController = new TextController()
  @State messageResponseRegion: string = '标记是否点到热区'

  onPageShow(): void {
    (this.textWidthModifier as TextWidthModifier).setGroup1();
    (this.textHeightModifier as TextHeightModifier).setGroup1();
    (this.textFontFontSizeModifier as TextFontFontSizeModifier).setGroup1();
    (this.textFontFontFamilyModifier as TextFontFontFamilyModifier).setGroup1();
    (this.textFontSizeModifier as TextFontSizeModifier).setGroup1();
    (this.textMinFontScaleModifier as TextMinFontScaleModifier).setGroup1();
    (this.textMaxFontScaleModifier as TextMaxFontScaleModifier).setGroup1();
    (this.textFontColorModifier as TextFontColorModifier).setGroup1();
    (this.textShadowModifier as TextShadowModifier).setGroup1();

  }

  build() {
    Scroll() {
      Column({ space: 10 }) {
        Column() {
          Text(' 测试点 Text create content ')
          Text($r('app.string.textCreateContent'))
        }.borderWidth(1)

        Column() {
          Text(' 测试点 Text create content Modifier ')
          Text(' 不会写create ')
            .attributeModifier(this.textCreateModifier as TextCreateModifier)
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 Text create TextController setStyledString 有问题')
          Text(undefined, { controller: this.textCreateController })

        }.borderWidth(1)

        Column() {
          Text(' 测试点 Text create TextController setStyledString Modifier 没写')
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 Text SetWidth width ')
          Text(' 浅色width 50，深色width 500').borderWidth(2).borderColor(Color.Red)
            .width($r('app.float.TextWith'))
        }.borderWidth(1)

        Column() {
          Text(' 测试点 Text SetWidth width Modifier ')
          Text(' 浅色width 50，深色width 500').borderWidth(2).borderColor(Color.Red)
            .attributeModifier(this.textWidthModifier as TextWidthModifier)
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 Text SetHeight height ')
          Text(' 浅色 height 50，深色 height 200 ').borderWidth(2).borderColor(Color.Red)
            .height($r('app.float.TextHeight'))
        }.borderWidth(1)

        Column() {
          Text(' 测试点 Text SetHeight height Modifier ')
          Text(' 浅色 height 50，深色 height 200 ').borderWidth(2).borderColor(Color.Red)
            .attributeModifier(this.textHeightModifier as TextHeightModifier)
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 Text SetFont size ')
          Text(' 浅色 fontsize 16，深色 fontsize 32 ').borderWidth(2).borderColor(Color.Red)
            .font({ size: $r('app.float.TextFontSize') })
        }.borderWidth(1)

        Column() {
          Text(' 测试点 Text SetFont size Modifier ')
          Text(' 浅色 fontsize 16，深色 fontsize 32 ').borderWidth(2).borderColor(Color.Red)
            .attributeModifier(this.textFontFontSizeModifier as TextFontFontSizeModifier)
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 Text SetFont family ')
          Text(' 浅色 Sans，深色 Sans Condensed ').borderWidth(2).borderColor(Color.Red)
            .font({ family: $r('app.string.TextFontFamily') })
        }.borderWidth(1)

        Column() {
          Text(' 测试点 Text SetFont family Modifier')
          Text(' 浅色 Sans，深色 Sans Condensed ').borderWidth(2).borderColor(Color.Red)
            .attributeModifier(this.textFontFontFamilyModifier as TextFontFontFamilyModifier)
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 Text SetFontSize fontsize ')
          Text(' 浅色 fontsize 16，深色 fontsize 32 ').borderWidth(2).borderColor(Color.Red)
            .fontSize($r('app.float.TextFontSize'))
        }.borderWidth(1)

        Column() {
          Text(' 测试点 Text SetFontSize fontsize Modifier ')
          Text(' 浅色 fontsize 16，深色 fontsize 32 ').borderWidth(2).borderColor(Color.Red)
            .attributeModifier(this.textFontSizeModifier as TextFontSizeModifier)
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 用来对比 Min ')
          Text('浅色 minFontScale 1.0，深色 minFontScale 1.0，原本字体大小是 16 ').borderWidth(2).borderColor(Color.Blue)
            .fontSize(16)
            .minFontScale(1)
        }.borderWidth(1)

        Column() {
          Text(' 测试点 Text SetMinFontScale minFontScale ')
          Text(' 浅色 minFontScale 0，深色 minFontScale 1.0，原本字体大小是 16 ').borderWidth(2).borderColor(Color.Red)
            .fontSize(16)
            .minFontScale($r('app.float.TextMinFontScale'))
        }.borderWidth(1)

        Column() {
          Text(' 测试点 Text SetMinFontScale minFontScale Modifier ')
          Text(' 浅色 minFontScale 0，深色 minFontScale 1.0，原本字体大小是 16 ').borderWidth(2).borderColor(Color.Red)
            .fontSize(16)
            .attributeModifier(this.textMinFontScaleModifier as TextMinFontScaleModifier)
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)


        Column() {
          Text(' 用来对比 Max ')
          Text('浅色 maxFontScale 1.0，深色 maxFontScale 1.0，原本字体大小是 16').borderWidth(2).borderColor(Color.Blue)
            .fontSize(16)
            .maxFontScale(1)
        }.borderWidth(1)

        Column() {
          Text(' 测试点 Text SetMaxFontScale maxFontScale ')
          Text(' 浅色 maxFontScale 3.2，深色 maxFontScale 1.0，原本字体大小是 16 ').borderWidth(2).borderColor(Color.Red)
            .fontSize(16)
            .maxFontScale($r('app.float.TextMaxFontScale'))
        }.borderWidth(1)

        Column() {
          Text(' 测试点 Text SetMaxFontScale maxFontScale Modifier')
          Text(' 浅色 maxFontScale 3.2，深色 maxFontScale 1.0，原本字体大小是 16 ').borderWidth(2).borderColor(Color.Red)
            .fontSize(16)
            .attributeModifier(this.textMaxFontScaleModifier as TextMaxFontScaleModifier)
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 Text SetTextColor textColor ')
          Text(' 浅色 textColor Red，深色 textColor Blue ').borderWidth(2).borderColor(Color.Red)
            .fontColor($r('app.color.TextColor'))
        }.borderWidth(1)

        Column() {
          Text(' 测试点 Text SetTextColor textColor Modifier')
          Text(' 浅色 textColor Red，深色 textColor Blue  ').borderWidth(2).borderColor(Color.Red)
            .attributeModifier(this.textFontColorModifier as TextFontColorModifier)
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 Text textShadow {radius, color, offsetX, offsetY} ')
          Text(' 浅色 textShadow {10, Red, 50, 0}，深色 {1, Blue, 0, 50} ')
            .borderWidth(2)
            .borderColor(Color.Red)
            .height(100)
            .backgroundColor(Color.White)
            .fontColor(Color.Black)
            .textShadow({
              radius: $r('app.float.TextShadowRadius'),
              color: $r('app.color.TextShadowColor'),
              offsetX: $r('app.float.TextShadowOffsetX'),
              offsetY: $r('app.float.TextShadowOffsetY'),
            })
        }.borderWidth(1)

        Column() {
          Text(' 测试点 Text textShadow {radius, color, offsetX, offsetY} Modifier ')
          Text(' 浅色 textShadow {10, Red, 50, 0}，深色 {1, Blue, 0, 50} ')
            .borderWidth(2)
            .borderColor(Color.Red)
            .height(100)
            .backgroundColor(Color.White)
            .fontColor(Color.Black)
            .attributeModifier(this.textShadowModifier as TextShadowModifier)
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 Text textIndent ')
          Text(' 浅色 textIndent 5，深色 textIndent 50 ').borderWidth(2).borderColor(Color.Red)
            .textIndent($r('app.float.TextIndent'))
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 Text lineHeight ')
          Text(' 浅色 lineHeight 20，深色 lineHeight 50 ').borderWidth(2).borderColor(Color.Red)
            .lineHeight($r('app.float.TextLineHeight'))
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 Text lineSpacing ')
          Text(' 浅色 lineHeight 20，深色 lineHeight 50 \n 下一行').borderWidth(2).borderColor(Color.Red)
            .lineSpacing(LengthMetrics.vp((this.getUIContext()
              .getHostContext() as common.UIAbilityContext).resourceManager.getNumber($r('app.float.TextLineSpacing')
              .id)))
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 Text fontFamily ')
          Text(' 浅色 Sans，深色 Sans Condensed ').borderWidth(2).borderColor(Color.Red)
            .fontFamily($r('app.string.TextFontFamily'))
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 Text minFontSize maxFontSize ')
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
            .borderWidth(2)
            .borderColor(Color.Red)
            .minFontSize($r('app.float.TextMinFontSize'))
            .maxFontSize($r('app.float.TextMaxFontSize'))
            .fontSize(16)
            .maxLines(3)
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 Text letterSpacing ')
          Text(' 浅色 letterSpacing 5，深色 letterSpacing 50 ').borderWidth(2).borderColor(Color.Red)
            .letterSpacing((this.getUIContext()
              .getHostContext() as common.UIAbilityContext).resourceManager.getNumber($r('app.float.TextLetterSpacing')
              .id))
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 Text baselineOffset ')
          Text(' 浅色 baselineOffset 5，深色 baselineOffset 50 ').borderWidth(2).borderColor(Color.Red)
            .baselineOffset((this.getUIContext()
              .getHostContext() as common.UIAbilityContext).resourceManager.getNumber($r('app.float.TextLetterSpacing')
              .id))
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)

        Column() {
          Text(' 测试点 Text baselineOffset ')
          Text(' 浅色 baselineOffset 5，深色 baselineOffset 50 ').borderWidth(2).borderColor(Color.Red)
            .baselineOffset((this.getUIContext()
              .getHostContext() as common.UIAbilityContext).resourceManager.getNumber($r('app.float.TextBaselineOffset')
              .id))
        }.borderWidth(1)

        Blank().borderWidth(5).height(1)


        Column() {
          Text(' 测试点 Text caretColor ')
          Text(' 浅色 caretColor Red，深色 caretColor Blue ').borderWidth(2).borderColor(Color.Red)
            .caretColor($r('app.color.TextColor'))
            .copyOption(CopyOptions.LocalDevice)
        }.borderWidth(1)

        Column() {
          Text(' 测试点 Text selectedBackgroundColor ')
          Text(' 浅色 selectedBackgroundColor Red，深色 selectedBackgroundColor Blue ')
            .borderWidth(2)
            .borderColor(Color.Red)
            .selectedBackgroundColor($r('app.color.TextColor'))
            .copyOption(CopyOptions.LocalDevice)
        }.borderWidth(1)

        Column() {
          Text(' 测试点 Text dataDetectorConfig ')
          Text(' 邮箱：***@example.com \n 浅色  {字 Red 下划线 Yellow }，深色 {字 Blue 下划线 Pink }  ')
            .borderWidth(2)
            .borderColor(Color.Red)
            .enableDataDetector(true)
            .dataDetectorConfig({
              types: [] as TextDataDetectorType[],
              color: $r('app.color.TextdataDetectorConfigColor'),
              decoration: {
                type: TextDecorationType.Underline,
                color: $r('app.color.TextdataDetectorConfigDecorationColor'),
                style: TextDecorationStyle.SOLID
              }
            })
            .copyOption(CopyOptions.LocalDevice)
        }.borderWidth(1)

        Column() {
          Text(' 测试点 Text foregroundColor ')
          Text(' 浅色 foregroundColor Red，深色 foregroundColor Blue ').borderWidth(2).borderColor(Color.Red)
            .foregroundColor($r('app.color.TextColor'))
        }.borderWidth(1)

        Column() {
          Text(' 测试点 Text responseRegion ')
          Text(' 浅色 左半边，深色 全部 ')
            .borderWidth(2)
            .borderColor(Color.Red)
            .height(100)
            .width(300)
            .onClick(() => {
              this.messageResponseRegion = '已经点到热区，点一下 点击复位 '
            })
            .responseRegion({
              x: 0,
              y: 0,
              width: $r('app.string.TextResponseRegionWidth'),
              height: '100%'
            })
          Text(this.messageResponseRegion)
          Button('点击复位')
            .onClick(() => {
              this.messageResponseRegion = '标记是否点到热区'
            })
        }.borderWidth(1)

      }
    }
  }
}