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
import { ColorBlock, IconBlock, RadioBlock, SliderBlock, useEnabled } from 'common';
import { Chip, ChipSize, curves, LengthUnit } from '@kit.ArkUI';

@Component
export struct ChipBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State enableChipOptionSize: boolean = false
  @State chipOptionSize: ChipSize = ChipSize.NORMAL
  @State enableChipOptionEnabled: boolean = false
  @State chipOptionEnabled: boolean = true
  @State enableChipOptionActivated: boolean = false
  @State chipOptionActivated: boolean = false
  @State enableChipOptionPrefixIconSrc: boolean = false
  @State chipOptionPrefixIconSrc: ResourceStr = $r('app.media.app_icon')
  @State enableChipOptionPrefixIconSizeWidth: boolean = false
  @State chipOptionPrefixIconSizeWidth: number = 16
  @State enableChipOptionPrefixIconSizeHeight: boolean = false
  @State chipOptionPrefixIconSizeHeight: number = 16
  @State enableChipOptionPrefixIconFillColor: boolean = false
  @State chipOptionPrefixIconFillColor: ResourceColor | undefined = undefined
  @State enableChipOptionPrefixIconActivatedFillColor: boolean = false
  @State chipOptionPrefixIconActivatedFillColor: ResourceColor | undefined = undefined
  @State enableChipOptionLabelText: boolean = false
  @State chipOptionLabelText: string = '操作块'
  @State enableChipOptionLabelFontSize: boolean = false
  @State chipOptionLabelFontSize: Dimension = $r('sys.float.ohos_id_text_size_button2')
  @State enableChipOptionLabelFontColor: boolean = false
  @State chipOptionLabelFontColor: ResourceColor = $r('sys.color.ohos_id_color_text_primary')
  @State enableChipOptionLabelActivatedFontColor: boolean = false
  @State chipOptionLabelActivatedFontColor: ResourceColor = $r('sys.color.ohos_id_color_text_primary_contrary')
  @State enableChipOptionLabelLabelMarginLeft: boolean = false
  @State chipOptionLabelLabelMarginLeft: number = 0
  @State enableChipOptionLabelLabelMarginRight: boolean = false
  @State chipOptionLabelLabelMarginRight: number = 0
  @State enableChipOptionLabelLocalizedLabelMarginStartValue: boolean = false
  @State chipOptionLabelLocalizedLabelMarginStartValue: number = 6
  @State enableChipOptionLabelLocalizedLabelMarginStartUnit: boolean = false
  @State chipOptionLabelLocalizedLabelMarginStartUnit: LengthUnit = LengthUnit.VP
  @State enableChipOptionLabelLocalizedLabelMarginEndValue: boolean = false
  @State chipOptionLabelLocalizedLabelMarginEndValue: number = 6
  @State enableChipOptionLabelLocalizedLabelMarginEndUnit: boolean = false
  @State chipOptionLabelLocalizedLabelMarginEndUnit: LengthUnit = LengthUnit.VP
  @State enableChipOptionSuffixIconSrc: boolean = false
  @State chipOptionSuffixIconSrc: ResourceStr = $r('app.media.app_icon')
  @State enableChipOptionSuffixIconSizeWidth: boolean = false
  @State chipOptionSuffixIconSizeWidth: number = 16
  @State enableChipOptionSuffixIconSizeHeight: boolean = false
  @State chipOptionSuffixIconSizeHeight: number = 16
  @State enableChipOptionSuffixIconFillColor: boolean = false
  @State chipOptionSuffixIconFillColor: ResourceColor | undefined = undefined
  @State enableChipOptionSuffixIconActivatedFillColor: boolean = false
  @State chipOptionSuffixIconActivatedFillColor: ResourceColor | undefined = undefined
  @State enableChipOptionBackgroundColor: boolean = false
  @State chipOptionBackgroundColor: ResourceColor = $r('sys.color.ohos_id_color_button_normal')
  @State enableChipOptionActivatedBackgroundColor: boolean = false
  @State chipOptionActivatedBackgroundColor: ResourceColor = $r('sys.color.ohos_id_color_emphasize')
  @State enableChipOptionBorderRadius: boolean = false
  @State chipOptionBorderRadius: Dimension = 0
  @State enableChipOptionAllowClose: boolean = false
  @State chipOptionAllowClose: boolean = true
  @State enableChipOptionDirection: boolean = false
  @State chipOptionDirection: Direction = Direction.Auto
  @State selection: string | null = null;
  scroller: Scroller = new Scroller()

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
    .backgroundColor($r('sys.color.ohos_id_color_sub_background'))
    .hideTitleBar(true)
  }

  aboutToAppear(): void {
    AppStorage.setOrCreate('scroller', this.scroller)
  }

  @Builder
  Content() {
    Column() {
      Chip({
        size: useEnabled(this.enableChipOptionSize, this.chipOptionSize),
        enabled: useEnabled(this.enableChipOptionEnabled, this.chipOptionEnabled),
        activated: useEnabled(this.enableChipOptionActivated, this.chipOptionActivated),
        prefixIcon: {
          src: useEnabled(this.enableChipOptionPrefixIconSrc, this.chipOptionPrefixIconSrc) as ResourceStr,
          size: {
            width: useEnabled(this.enableChipOptionPrefixIconSizeWidth, this.chipOptionPrefixIconSizeWidth),
            height: useEnabled(this.enableChipOptionPrefixIconSizeHeight, this.chipOptionPrefixIconSizeHeight)
          },
          fillColor: useEnabled(this.enableChipOptionPrefixIconFillColor, this.chipOptionPrefixIconFillColor),
          activatedFillColor: useEnabled(this.enableChipOptionPrefixIconActivatedFillColor,
            this.chipOptionPrefixIconActivatedFillColor)
        },
        label: {
          text: this.chipOptionLabelText,
          fontSize: useEnabled(this.enableChipOptionLabelFontSize, this.chipOptionLabelFontSize),
          fontColor: useEnabled(this.enableChipOptionLabelFontColor, this.chipOptionLabelFontColor),
          activatedFontColor: useEnabled(this.enableChipOptionLabelActivatedFontColor,
            this.chipOptionLabelActivatedFontColor),
          labelMargin: {
            left: useEnabled(this.enableChipOptionLabelLabelMarginLeft, this.chipOptionLabelLabelMarginLeft),
            right: useEnabled(this.enableChipOptionLabelLabelMarginRight, this.chipOptionLabelLabelMarginRight)
          },
          localizedLabelMargin: {
            start: {
              value: useEnabled(this.enableChipOptionLabelLocalizedLabelMarginStartValue,
                this.chipOptionLabelLocalizedLabelMarginStartValue) as number,
              unit: useEnabled(this.enableChipOptionLabelLocalizedLabelMarginStartUnit,
                this.chipOptionLabelLocalizedLabelMarginStartUnit) as LengthUnit
            },
            end: {
              value: useEnabled(this.enableChipOptionLabelLocalizedLabelMarginEndValue,
                this.chipOptionLabelLocalizedLabelMarginEndValue) as number,
              unit: useEnabled(this.enableChipOptionLabelLocalizedLabelMarginEndUnit,
                this.chipOptionLabelLocalizedLabelMarginEndUnit) as LengthUnit
            }
          }
        },
        suffixIcon: {
          src: useEnabled(this.enableChipOptionSuffixIconSrc, this.chipOptionSuffixIconSrc) as ResourceStr,
          size: {
            width: useEnabled(this.enableChipOptionSuffixIconSizeWidth,
              this.chipOptionSuffixIconSizeWidth),
            height: useEnabled(this.enableChipOptionSuffixIconSizeHeight,
              this.chipOptionSuffixIconSizeHeight)
          },
          fillColor: useEnabled(this.enableChipOptionSuffixIconFillColor,
            this.chipOptionSuffixIconFillColor),
          activatedFillColor: useEnabled(this.enableChipOptionSuffixIconActivatedFillColor,
            this.chipOptionSuffixIconActivatedFillColor)
        },
        backgroundColor: useEnabled(this.enableChipOptionBackgroundColor, this.chipOptionBackgroundColor),
        activatedBackgroundColor: useEnabled(this.enableChipOptionActivatedBackgroundColor,
          this.chipOptionActivatedBackgroundColor),
        borderRadius: useEnabled(this.enableChipOptionBorderRadius, this.chipOptionBorderRadius),
        allowClose: useEnabled(this.enableChipOptionAllowClose, this.chipOptionAllowClose),
        onClose: () => {

        },
        onClicked: () => {

        },
        direction: useEnabled(this.enableChipOptionDirection, this.chipOptionDirection)
      })

    }
  }

  @Builder
  Parameters() {
    Scroll(this.scroller) {
      Column({ space: 8 }) {
        RadioBlock({
          title: 'options.size',
          isEnabled: $enableChipOptionSize,
          value: $chipOptionSize,
          dataSource: [
            { label: 'NORMAL', value: ChipSize.NORMAL },
            { label: 'SMALL', value: ChipSize.SMALL }
          ]
        })
        RadioBlock({
          title: 'options.enabled',
          isEnabled: $enableChipOptionEnabled,
          value: $chipOptionEnabled,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })
        RadioBlock({
          title: 'options.activated',
          isEnabled: $enableChipOptionActivated,
          value: $chipOptionActivated,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })
        IconBlock({
          title: 'options.prefixIcon.src',
          isEnabled: $enableChipOptionPrefixIconSrc,
          icon: $chipOptionPrefixIconSrc,
        })
        SliderBlock({
          title: 'options.prefixIcon.size.width',
          isEnabled: $enableChipOptionPrefixIconSizeWidth,
          value: $chipOptionPrefixIconSizeWidth,
          min: 0,
          max: 32
        })
        SliderBlock({
          title: 'options.prefixIcon.size.height',
          isEnabled: $enableChipOptionPrefixIconSizeHeight,
          value: $chipOptionPrefixIconSizeHeight,
          min: 0,
          max: 32
        })
        ColorBlock({
          title: 'options.prefixIcon.fillColor',
          isEnabled: $enableChipOptionPrefixIconFillColor,
          color: $chipOptionPrefixIconFillColor
        })
        ColorBlock({
          title: 'options.prefixIcon.activatedFillColor',
          isEnabled: $enableChipOptionPrefixIconActivatedFillColor,
          color: $chipOptionPrefixIconActivatedFillColor
        })
        RadioBlock({
          title: 'options.label.text',
          isEnabled: $enableChipOptionLabelText,
          value: $chipOptionLabelText,
          dataSource: [
            { label: '操作块', value: '操作块' },
            { label: '执行块', value: '执行块' }
          ]
        })
        RadioBlock({
          title: 'options.label.fontSize',
          isEnabled: $enableChipOptionLabelFontSize,
          value: $chipOptionLabelFontSize,
          dataSource: [
            { label: 'text_size_button1', value: $r('sys.float.ohos_id_text_size_button1') },
            { label: 'text_size_button2', value: $r('sys.float.ohos_id_text_size_button2') },
            { label: 'text_size_button3', value: $r('sys.float.ohos_id_text_size_button3') }
          ]
        })
        ColorBlock({
          title: 'options.label.fontColor',
          isEnabled: $enableChipOptionLabelFontColor,
          color: $chipOptionLabelFontColor
        })
        ColorBlock({
          title: 'options.label.activatedFontColor',
          isEnabled: $enableChipOptionLabelActivatedFontColor,
          color: $chipOptionLabelActivatedFontColor
        })
        SliderBlock({
          title: 'options.label.labelMargin.left',
          isEnabled: $enableChipOptionLabelLabelMarginLeft,
          value: $chipOptionLabelLabelMarginLeft,
          min: 0,
          max: 32
        })
        SliderBlock({
          title: 'options.label.labelMargin.right',
          isEnabled: $enableChipOptionLabelLabelMarginRight,
          value: $chipOptionLabelLabelMarginRight,
          min: 0,
          max: 32
        })
        SliderBlock({
          title: 'options.label.localizedLabelMargin.start.value',
          isEnabled: $enableChipOptionLabelLocalizedLabelMarginStartValue,
          value: $chipOptionLabelLocalizedLabelMarginStartValue,
          min: 0,
          max: 24
        })
        RadioBlock({
          title: 'options.label.localizedLabelMargin.start.unit',
          isEnabled: $enableChipOptionLabelLocalizedLabelMarginStartUnit,
          value: $chipOptionLabelLocalizedLabelMarginStartUnit,
          dataSource: [
            { label: 'PX', value: LengthUnit.PX },
            { label: 'VP', value: LengthUnit.VP },
            { label: 'FP', value: LengthUnit.FP },
            { label: 'PERCENT', value: LengthUnit.PERCENT },
            { label: 'LPX', value: LengthUnit.LPX },
          ]
        })
        SliderBlock({
          title: 'options.label.localizedLabelMargin.end.value',
          isEnabled: $enableChipOptionLabelLocalizedLabelMarginEndValue,
          value: $chipOptionLabelLocalizedLabelMarginEndValue,
          min: 0,
          max: 24
        })
        RadioBlock({
          title: 'options.label.localizedLabelMargin.end.unit',
          isEnabled: $enableChipOptionLabelLocalizedLabelMarginEndUnit,
          value: $chipOptionLabelLocalizedLabelMarginEndUnit,
          dataSource: [
            { label: 'PX', value: LengthUnit.PX },
            { label: 'VP', value: LengthUnit.VP },
            { label: 'FP', value: LengthUnit.FP },
            { label: 'PERCENT', value: LengthUnit.PERCENT },
            { label: 'LPX', value: LengthUnit.LPX },
          ]
        })
        IconBlock({
          title: 'options.suffixIcon.src',
          isEnabled: $enableChipOptionSuffixIconSrc,
          icon: $chipOptionSuffixIconSrc,
        })
        SliderBlock({
          title: 'options.suffixIcon.size.width',
          isEnabled: $enableChipOptionSuffixIconSizeWidth,
          value: $chipOptionSuffixIconSizeWidth,
          min: 0,
          max: 32
        })
        SliderBlock({
          title: 'options.suffixIcon.size.height',
          isEnabled: $enableChipOptionSuffixIconSizeHeight,
          value: $chipOptionSuffixIconSizeHeight,
          min: 0,
          max: 32
        })
        ColorBlock({
          title: 'options.suffixIcon.fillColor',
          isEnabled: $enableChipOptionSuffixIconFillColor,
          color: $chipOptionSuffixIconFillColor
        })
        ColorBlock({
          title: 'options.suffixIcon.activatedFillColor',
          isEnabled: $enableChipOptionSuffixIconActivatedFillColor,
          color: $chipOptionSuffixIconActivatedFillColor
        })
        ColorBlock({
          title: 'options.backgroundColor',
          isEnabled: $enableChipOptionBackgroundColor,
          color: $chipOptionBackgroundColor
        })
        ColorBlock({
          title: 'options.activatedBackgroundColor',
          isEnabled: $enableChipOptionActivatedBackgroundColor,
          color: $chipOptionActivatedBackgroundColor
        })
        SliderBlock({
          title: 'options.borderRadius',
          isEnabled: $enableChipOptionBorderRadius,
          value: $chipOptionBorderRadius,
          min: 0,
          max: 100
        })
        RadioBlock({
          title: 'options.allowClose',
          isEnabled: $enableChipOptionAllowClose,
          value: $chipOptionAllowClose,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })
        RadioBlock({
          title: 'options.direction',
          isEnabled: $enableChipOptionDirection,
          value: $chipOptionDirection,
          dataSource: [
            { label: 'Ltr', value: Direction.Ltr },
            { label: 'Rtl', value: Direction.Rtl },
            { label: 'Auto', value: Direction.Auto }
          ]
        })
      }
    }
    .height('52%')
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
struct ChipBootcampPreviewer {
  build() {
    ChipBootcamp({
      title: '操作块/Chip'
    })
  }
}