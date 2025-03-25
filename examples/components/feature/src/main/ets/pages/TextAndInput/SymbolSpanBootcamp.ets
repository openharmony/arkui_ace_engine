/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

import { Drawer } from 'common/src/main/ets/components/Drawer';
import { RadioBlock, SliderBlock, ColorBlock, useEnabled } from 'common';
import { curves } from '@kit.ArkUI';


class MyButtonModifierNormal implements AttributeModifier<SymbolSpanAttribute> {
  public isDark: boolean = false;

  applyNormalAttribute(instance: SymbolSpanAttribute): void {
    if (this.isDark) {
      instance.backgroundColor(Color.Black)
    } else {
      instance.backgroundColor(Color.Red)
    }
  }
}

class MyButtonModifierPressed implements AttributeModifier<SymbolSpanAttribute> {
  public isDark: boolean = false

  applyPressedAttribute(instance: SymbolSpanAttribute): void {
    if (this.isDark) {
      instance.backgroundColor(Color.Black)
    } else {
      instance.backgroundColor(Color.Red)
    }
  }
}

class MyButtonModifierFocused implements AttributeModifier<SymbolSpanAttribute> {
  public isDark: boolean = false

  applyFocusedAttribute(instance: SymbolSpanAttribute): void {
    if (this.isDark) {
      instance.backgroundColor(Color.Black)
    } else {
      instance.backgroundColor(Color.Red)
    }
  }
}

class MyButtonModifierDisabled implements AttributeModifier<SymbolSpanAttribute> {
  public isDark: boolean = false

  applyDisabledAttribute(instance: SymbolSpanAttribute): void {
    if (this.isDark) {
      instance.backgroundColor(Color.Black)
    } else {
      instance.backgroundColor(Color.Red)
    }
  }
}

class MyButtonModifierSelected implements AttributeModifier<SymbolSpanAttribute> {
  public isDark: boolean = false

  applySelectedAttribute(instance: SymbolSpanAttribute): void {
    if (this.isDark) {
      instance.backgroundColor(Color.Black)
    } else {
      instance.backgroundColor(Color.Red)
    }
  }
}

@Component
export struct SymbolSpanBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State enableFontColor: boolean = false;
  @State fontColor: ResourceColor | undefined = undefined;
  @State enableFontSize: boolean = false;
  @State fontSize: number | undefined = undefined;
  @State enableFontWeight: boolean = false;
  @State fontWeight: FontWeight | number | string = 400 | FontWeight.Normal;
  @State enableRenderingStrategy: boolean = false;
  @State renderingStrategy: SymbolRenderingStrategy = SymbolRenderingStrategy.SINGLE
  @State enableEffectStrategy: boolean = false;
  @State effectStrategy: SymbolEffectStrategy = SymbolEffectStrategy.NONE
  @State enableEnableModifierNormal: boolean = false;
  @State enableModifierNormal: boolean = false;
  @State modifierNormal: MyButtonModifierNormal = new MyButtonModifierNormal()
  @State enableEnableModifierPressed: boolean = false;
  @State enableModifierPressed: boolean = false;
  @State modifierPressed: MyButtonModifierPressed = new MyButtonModifierPressed()
  @State enableEnableModifierFocused: boolean = false;
  @State enableModifierFocused: boolean = false;
  @State modifierFocused: MyButtonModifierFocused = new MyButtonModifierFocused()
  @State enableEnableModifierDisabled: boolean = false;
  @State enableModifierDisabled: boolean = false;
  @State modifierDisabled: MyButtonModifierDisabled = new MyButtonModifierDisabled()
  @State enableEnableModifierSelected: boolean = false;
  @State enableModifierSelected: boolean = false;
  @State modifierSelected: MyButtonModifierSelected = new MyButtonModifierSelected()
  @State selection: string | null = null;
  scroller: Scroller = new Scroller()

  aboutToAppear(): void {
    AppStorage.setOrCreate('scroller', this.scroller)
  }

  build() {
    NavDestination() {
      Drawer({
        title: this.title,
        showParameters: $showParameters,
        content: () => {
          this.Content()
        },
        generic: () => {
          this.Generic()
        },
        parameters: () => {
          this.Parameters()
        }
      })
    }
    .backgroundColor('#f1f3f5')
    .hideTitleBar(true)
  }

  @Builder
  Content() {
    Row() {
      Column({ space: 10 }) {
        Text() {
          SymbolSpan($r('sys.symbol.ohos_folder_badge_plus'))
            .fontSize(useEnabled(this.enableFontSize, this.fontSize))
            .fontWeight(useEnabled(this.enableFontWeight, this.fontWeight))
            .fontColor([useEnabled(this.enableFontColor, this.fontColor)])
            .renderingStrategy(useEnabled(this.enableRenderingStrategy, this.renderingStrategy))
            .effectStrategy(useEnabled(this.enableEffectStrategy, this.effectStrategy))
            .key('SymbolSpan')
        }

        Row({ space: 10 }) {
          Column() {
            Text('Modifier.pressed')
            Text() {
              SymbolSpan($r('sys.symbol.ohos_folder_badge_plus'))
                .fontSize(useEnabled(this.enableFontSize, this.fontSize))
                .fontWeight(useEnabled(this.enableFontWeight, this.fontWeight))
                .fontColor([useEnabled(this.enableFontColor, this.fontColor)])
                .renderingStrategy(useEnabled(this.enableRenderingStrategy, this.renderingStrategy))
                .effectStrategy(useEnabled(this.enableEffectStrategy, this.effectStrategy))
                .attributeModifier(this.modifierPressed)
                .key('SymbolSpan')
                .onClick(() => {
                  this.modifierPressed.isDark = !this.modifierPressed.isDark
                })
            }
          }
          .visibility(this.enableModifierPressed ? Visibility.Visible : Visibility.None)

          Column() {
            Text('Modifier.normal')
            Text() {
              SymbolSpan($r('sys.symbol.ohos_folder_badge_plus'))
                .fontSize(useEnabled(this.enableFontSize, this.fontSize))
                .fontWeight(useEnabled(this.enableFontWeight, this.fontWeight))
                .fontColor([useEnabled(this.enableFontColor, this.fontColor)])
                .renderingStrategy(useEnabled(this.enableRenderingStrategy, this.renderingStrategy))
                .effectStrategy(useEnabled(this.enableEffectStrategy, this.effectStrategy))
                .attributeModifier(this.modifierNormal)
                .key('SymbolSpan')
                .onClick(() => {
                  this.modifierNormal.isDark = !this.modifierNormal.isDark
                })
            }
          }
          .visibility(this.enableModifierNormal ? Visibility.Visible : Visibility.Hidden)


          Column() {
            Text('Modifier.focused')
            Text() {
              SymbolSpan($r('sys.symbol.ohos_folder_badge_plus'))
                .fontSize(useEnabled(this.enableFontSize, this.fontSize))
                .fontWeight(useEnabled(this.enableFontWeight, this.fontWeight))
                .fontColor([useEnabled(this.enableFontColor, this.fontColor)])
                .renderingStrategy(useEnabled(this.enableRenderingStrategy, this.renderingStrategy))
                .effectStrategy(useEnabled(this.enableEffectStrategy, this.effectStrategy))
                .attributeModifier(this.modifierPressed)
                .key('SymbolSpan')
                .onClick(() => {
                  this.modifierFocused.isDark = !this.modifierFocused.isDark
                })
            }
          }
          .visibility(this.enableModifierFocused ? Visibility.Visible : Visibility.None)

          Column() {
            Text('Modifier.disabled')
            Text() {
              SymbolSpan($r('sys.symbol.ohos_folder_badge_plus'))
                .fontSize(useEnabled(this.enableFontSize, this.fontSize))
                .fontWeight(useEnabled(this.enableFontWeight, this.fontWeight))
                .fontColor([useEnabled(this.enableFontColor, this.fontColor)])
                .renderingStrategy(useEnabled(this.enableRenderingStrategy, this.renderingStrategy))
                .effectStrategy(useEnabled(this.enableEffectStrategy, this.effectStrategy))
                .attributeModifier(this.modifierDisabled)
                .key('SymbolSpan')
                .onClick(() => {
                  this.modifierDisabled.isDark = !this.modifierDisabled.isDark
                })
            }
          }
          .visibility(this.enableModifierDisabled ? Visibility.Visible : Visibility.None)

          Column() {
            Text('Modifier.selected')
            Text() {
              SymbolSpan($r('sys.symbol.ohos_folder_badge_plus'))
                .fontSize(useEnabled(this.enableFontSize, this.fontSize))
                .fontWeight(useEnabled(this.enableFontWeight, this.fontWeight))
                .fontColor([useEnabled(this.enableFontColor, this.fontColor)])
                .renderingStrategy(useEnabled(this.enableRenderingStrategy, this.renderingStrategy))
                .effectStrategy(useEnabled(this.enableEffectStrategy, this.effectStrategy))
                .attributeModifier(this.modifierSelected)
                .key('SymbolSpan')
                .onClick(() => {
                  this.modifierSelected.isDark = !this.modifierSelected.isDark
                })
            }
          }
          .visibility(this.enableModifierSelected ? Visibility.Visible : Visibility.None)
        }

      }
    }.justifyContent(FlexAlign.Start)
  }

  @Builder
  Parameters() {
    Scroll(this.scroller) {
      Column({ space: 8 }) {

        ColorBlock({
          title: 'fontColor',
          isEnabled: this.enableFontColor,
          color: this.fontColor
        })

        SliderBlock({
          title: 'fontSize',
          isEnabled: this.enableFontSize,
          value: this.fontSize,
          min: 0,
          max: 200
        })

        RadioBlock({
          title: 'fontWeight',
          isEnabled: this.enableFontWeight,
          value: this.fontWeight,
          dataSource: [
            { label: '100', value: 100 },
            { label: '200', value: 200 },
            { label: '300', value: 300 },
            { label: '400', value: 400 },
            { label: '500', value: 500 },
            { label: '600', value: 600 },
            { label: '700', value: 700 },
            { label: '800', value: 800 },
            { label: '900', value: 900 },
            { label: 'Lighter', value: FontWeight.Lighter },
            { label: 'Normal', value: FontWeight.Normal },
            { label: 'Regular', value: FontWeight.Regular },
            { label: 'Medium', value: FontWeight.Medium },
            { label: 'Bold', value: FontWeight.Bold },
            { label: 'Bolder', value: FontWeight.Bolder },
          ]
        })

        RadioBlock({
          title: 'renderingStrategy',
          isEnabled: this.enableRenderingStrategy,
          value: this.renderingStrategy,
          dataSource: [
            { label: 'SINGLE', value: SymbolRenderingStrategy.SINGLE },
            { label: 'MULTIPLE_COLOR', value: SymbolRenderingStrategy.MULTIPLE_COLOR },
            { label: 'MULTIPLE_OPACITY', value: SymbolRenderingStrategy.MULTIPLE_OPACITY },
          ]
        })

        RadioBlock({
          title: 'effectStrategy',
          isEnabled: this.enableEffectStrategy,
          value: this.effectStrategy,
          dataSource: [
            { label: 'NONE', value: SymbolEffectStrategy.NONE },
            { label: 'SCALE', value: SymbolEffectStrategy.SCALE },
            { label: 'HIERARCHICAL', value: SymbolEffectStrategy.HIERARCHICAL },
          ]
        })

        RadioBlock({
          title: 'attributeModifier.normal',
          isEnabled: this.enableEnableModifierNormal,
          value: this.enableModifierNormal,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false },
          ]
        })

        RadioBlock({
          title: 'attributeModifier.pressed',
          isEnabled: this.enableEnableModifierPressed,
          value: this.enableModifierPressed,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false },
          ]
        })

        RadioBlock({
          title: 'attributeModifier.focused',
          isEnabled: this.enableEnableModifierFocused,
          value: this.enableModifierFocused,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false },
          ]
        })

        RadioBlock({
          title: 'attributeModifier.disabled',
          isEnabled: this.enableEnableModifierDisabled,
          value: this.enableModifierDisabled,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false },
          ]
        })

        RadioBlock({
          title: 'attributeModifier.selected',
          isEnabled: this.enableEnableModifierSelected,
          value: this.enableModifierSelected,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false },
          ]
        })

      }
    }
    .align(Alignment.Top)
    .height('50%')
    .id('scroll')
  }

  @Builder
  ListItemGroupHeaders(str: string) {
    Row() {
      Text(str)
        .fontColor($r('sys.color.ohos_id_color_text_primary'))
        .fontWeight(FontWeight.Medium)
      Blank()
      Image($r('sys.media.ohos_ic_public_arrow_right'))
        .fillColor($r('sys.color.ohos_id_color_fourth'))
        .height(24)
        .width(24)
        .rotate({ angle: this.selection == str ? 90 : 0 })
        .animation({ curve: curves.interpolatingSpring(0, 1, 228, 30) })
    }
    .borderRadius(20)
    .width('100%')
    .padding({
      left: 8,
      right: 8,
      top: 18,
      bottom: 18
    })

    .onClick(() => {
      if (this.selection === str) {
        this.selection = null;
      } else {
        this.selection = str;
        AppStorage.setOrCreate('selection', this.selection)
      }
    })
  }

  @Builder
  Generic() {
    Scroll(this.scroller) {
      Column({ space: 8 }) {

      }.width('100%')
    }
    .height('52%')
    .id('scroll')
  }
}

@Preview
@Component
struct SymbolSpanBootcampPreviewer {
  build() {
    SymbolSpanBootcamp({
      title: 'SymbolSpan'
    })
  }
}