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
import { ColorBlock, RadioBlock, SliderBlock, useEnabled} from 'common';

@Component
export struct AlphabetIndexerBootcamp {

  private value: string[] = ['#', 'A', 'B', 'C', 'D', 'E', 'F', 'G',
    'H', 'I', 'J', 'K', 'L', 'M', 'N',
    'O', 'P', 'Q', 'R', 'S', 'T', 'U',
    'V', 'W', 'X', 'Y', 'Z']
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State enableAlphabetIndexerColor: boolean = false
  @State alphabetIndexerColor: ResourceColor = '0x99182431';
  @State enableAlphabetIndexerSelectedColor: boolean = false;
  @State alphabetIndexerSelectedColor: ResourceColor = '0xFF007DFF';
  @State enableAlphabetIndexerPopupColor: boolean = false;
  @State alphabetIndexerPopupColor: ResourceColor = '0xFF007DFF';
  @State enableAlphabetIndexerSelectedBackgroundColor: boolean = false;
  @State alphabetIndexerSelectedBackgroundColor: ResourceColor = '0x1A007DFF';
  @State enableAlphabetIndexerPopupBackground: boolean = false;
  @State alphabetIndexerPopupBackground: ResourceColor = '#66808080';
  @State enableAlphabetIndexerUsingPopup: boolean = false;
  @State alphabetIndexerUsingPopup: boolean = false;
  @State enableAlphabetIndexerSelectedFontSize: boolean = false;
  @State alphabetIndexerSelectedFontSize: number = 10;
  @State enableAlphabetIndexerSelectedFontStyle: boolean = false;
  @State alphabetIndexerSelectedFontStyle: FontStyle = FontStyle.Normal;
  @State enableAlphabetIndexerSelectedFontWeight: boolean = false;
  @State alphabetIndexerSelectedFontWeight: FontWeight = FontWeight.Medium;
  @State enableAlphabetIndexerPopupFontSize: boolean = false;
  @State alphabetIndexerPopupFontSize: number = 24;
  @State enableAlphabetIndexerPopupFontStyle: boolean = false;
  @State alphabetIndexerPopupFontStyle: FontStyle = FontStyle.Normal;
  @State enableAlphabetIndexerPopupFontWeight: boolean = false;
  @State alphabetIndexerPopupFontWeight: FontWeight = FontWeight.Normal;
  @State enableAlphabetIndexerFontSize: boolean = false;
  @State alphabetIndexerFontSize: number = 10;
  @State enableAlphabetIndexerFontStyle: boolean = false;
  @State alphabetIndexerFontStyle: FontStyle = FontStyle.Normal;
  @State enableAlphabetIndexerFontWeight: boolean = false;
  @State alphabetIndexerFontWeight: FontWeight = FontWeight.Medium;
  @State enableAlphabetIndexerItemSize: boolean = false;
  @State alphabetIndexerItemSize: number = 16;
  @State enableAlphabetIndexerAlignStyleIndexerAlign: boolean = false;
  @State alphabetIndexerAlignStyleIndexerAlign: IndexerAlign = IndexerAlign.END;
  @State enableAlphabetIndexerAlignStyleLength: boolean = false;
  @State alphabetIndexerAlignStyleLength: number = 0;
  @State enableAlphabetIndexerSelected: boolean = false;
  @State alphabetIndexerSelected: number = 0;
  @State enableAlphabetIndexerPopupPositionX: boolean = false;
  @State alphabetIndexerPopupPositionX: number = 60;
  @State enableAlphabetIndexerPopupPositionY: boolean = false;
  @State alphabetIndexerPopupPositionY: number = 48;
  @State enableAlphabetIndexerPopupSelectedColor: boolean = false;
  @State alphabetIndexerPopupSelectedColor: ResourceColor = '#FF182431';
  @State enableAlphabetIndexerPopupUnselectedColor: boolean = false;
  @State alphabetIndexerPopupUnselectedColor: ResourceColor = '#FF182431';
  @State enableAlphabetIndexerPopupItemFontSize: boolean = false;
  @State alphabetIndexerPopupItemFontSize: number = 24;
  @State enableAlphabetIndexerPopupItemFontStyle: boolean = false;
  @State alphabetIndexerPopupItemFontStyle: FontStyle = FontStyle.Normal;
  @State enableAlphabetIndexerPopupItemFontWeight: boolean = false;
  @State alphabetIndexerPopupItemFontWeight: FontWeight = FontWeight.Medium;
  @State enableAlphabetIndexerPopupItemBackgroundColor: boolean = false;
  @State alphabetIndexerPopupItemBackgroundColor: ResourceColor = '#00000000';
  @State enableAlphabetIndexerAutoCollapse: boolean = false;
  @State alphabetIndexerAutoCollapse: boolean = true;
  @State enableAlphabetIndexerPopupItemBorderRadius: boolean = false;
  @State alphabetIndexerPopupItemBorderRadius: number = 24;
  @State enableAlphabetIndexerItemBorderRadius: boolean = false;
  @State alphabetIndexerItemBorderRadius: number = 8;
  @State enableAlphabetIndexerPopupBackgroundBlurStyle: boolean = false;
  @State alphabetIndexerPopupBackgroundBlurStyle: BlurStyle = BlurStyle.COMPONENT_REGULAR;
  @State enableAlphabetIndexerPopupTitleBackground: boolean = false;
  @State alphabetIndexerPopupTitleBackground: ResourceColor = '#0c182431';
  @State enableAlphabetIndexerEnableHapticFeedback: boolean = false;
  @State alphabetIndexerEnableHapticFeedback: boolean = true;

  build() {
    NavDestination() {
      Drawer({
        title: this.title,
        showParameters: $showParameters,
        content: () => {
          this.Content()
        },
        parameters: () => {
          this.Parameters()
        }
      })
    }
    .backgroundColor($r('sys.color.ohos_id_color_sub_background'))
    .hideTitleBar(true)
  }

  @Builder
  Content() {
    Column() {
      AlphabetIndexer({ arrayValue: this.value, selected: 0 })
        .color(
          useEnabled(this.enableAlphabetIndexerColor, this.alphabetIndexerColor))
        .selectedColor(
          useEnabled(this.enableAlphabetIndexerSelectedColor, this.alphabetIndexerSelectedColor))
        .popupColor(
          useEnabled(this.enableAlphabetIndexerPopupColor, this.alphabetIndexerPopupColor))
        .selectedBackgroundColor(
          useEnabled(this.enableAlphabetIndexerSelectedBackgroundColor, this.alphabetIndexerSelectedBackgroundColor))
        .popupBackground(
          useEnabled(this.enableAlphabetIndexerPopupBackground, this.alphabetIndexerPopupBackground))
        .usingPopup(
          useEnabled(this.enableAlphabetIndexerUsingPopup, this.alphabetIndexerUsingPopup))
        .selectedFont({
          size: useEnabled(this.enableAlphabetIndexerSelectedFontSize, this.alphabetIndexerSelectedFontSize),
          style: useEnabled(this.enableAlphabetIndexerSelectedFontStyle, this.alphabetIndexerSelectedFontStyle),
          weight: useEnabled(this.enableAlphabetIndexerSelectedFontWeight, this.alphabetIndexerSelectedFontWeight)})
        .popupFont({
          size: useEnabled(this.enableAlphabetIndexerPopupFontSize, this.alphabetIndexerPopupFontSize),
          style: useEnabled(this.enableAlphabetIndexerPopupFontStyle, this.alphabetIndexerPopupFontStyle),
          weight: useEnabled(this.enableAlphabetIndexerPopupFontWeight, this.alphabetIndexerPopupFontWeight)})
        .font({
          size: useEnabled(this.enableAlphabetIndexerFontSize, this.alphabetIndexerFontSize),
          style: useEnabled(this.enableAlphabetIndexerFontStyle, this.alphabetIndexerFontStyle),
          weight: useEnabled(this.enableAlphabetIndexerFontWeight, this.alphabetIndexerFontWeight)})
        .itemSize(useEnabled(this.enableAlphabetIndexerItemSize, this.alphabetIndexerItemSize))
        .alignStyle(
          useEnabled(this.enableAlphabetIndexerAlignStyleIndexerAlign, this.alphabetIndexerAlignStyleIndexerAlign),
          useEnabled(this.enableAlphabetIndexerAlignStyleLength, this.alphabetIndexerAlignStyleLength))
        .selected(useEnabled(this.enableAlphabetIndexerSelected, this.alphabetIndexerSelected))
        .popupPosition({
          x: useEnabled(this.enableAlphabetIndexerPopupPositionX, this.alphabetIndexerPopupPositionX),
          y: useEnabled(this.enableAlphabetIndexerPopupPositionY, this.alphabetIndexerPopupPositionY)})
        .popupSelectedColor(
          useEnabled(this.enableAlphabetIndexerPopupSelectedColor, this.alphabetIndexerPopupSelectedColor))
        .popupUnselectedColor(
          useEnabled(this.enableAlphabetIndexerPopupUnselectedColor, this.alphabetIndexerPopupUnselectedColor))
        .popupItemFont({
          size: useEnabled(this.enableAlphabetIndexerPopupItemFontSize, this.alphabetIndexerPopupItemFontSize),
          style: useEnabled(this.enableAlphabetIndexerPopupItemFontStyle, this.alphabetIndexerPopupItemFontStyle),
          weight: useEnabled(this.enableAlphabetIndexerPopupItemFontWeight, this.alphabetIndexerPopupItemFontWeight)})
        .popupItemBackgroundColor(
          useEnabled(this.enableAlphabetIndexerPopupItemBackgroundColor, this.alphabetIndexerPopupItemBackgroundColor))
        .autoCollapse(
          useEnabled(this.enableAlphabetIndexerAutoCollapse, this.alphabetIndexerAutoCollapse))
        .popupItemBorderRadius(
          useEnabled(this.enableAlphabetIndexerPopupItemBorderRadius, this.alphabetIndexerPopupItemBorderRadius))
        .itemBorderRadius(
          useEnabled(this.enableAlphabetIndexerItemBorderRadius, this.alphabetIndexerItemBorderRadius))
        .popupBackgroundBlurStyle(
          useEnabled(this.enableAlphabetIndexerPopupBackgroundBlurStyle, this.alphabetIndexerPopupBackgroundBlurStyle))
        .popupTitleBackground(
          useEnabled(this.enableAlphabetIndexerPopupTitleBackground, this.alphabetIndexerPopupTitleBackground))
        .enableHapticFeedback(
          useEnabled(this.enableAlphabetIndexerEnableHapticFeedback, this.alphabetIndexerEnableHapticFeedback))
    }
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
        ColorBlock({
          title: 'color',
          isEnabled: $enableAlphabetIndexerColor,
          color: $alphabetIndexerColor
        })
        ColorBlock({
          title: 'selectedColor',
          isEnabled: $enableAlphabetIndexerSelectedColor,
          color: $alphabetIndexerSelectedColor
        })
        ColorBlock({
          title: 'popupColor',
          isEnabled: $enableAlphabetIndexerPopupColor,
          color: $alphabetIndexerPopupColor
        })
        ColorBlock({
          title: 'selectedBackgroundColor',
          isEnabled: $enableAlphabetIndexerSelectedBackgroundColor,
          color: $alphabetIndexerSelectedBackgroundColor
        })
        ColorBlock({
          title: 'popupBackground',
          isEnabled: $enableAlphabetIndexerPopupBackground,
          color: $alphabetIndexerPopupBackground
        })
        RadioBlock({
          title: 'usingPopup',
          isEnabled: $enableAlphabetIndexerUsingPopup,
          value: $alphabetIndexerUsingPopup,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })
        SliderBlock({
          title: 'selectedFontSize',
          isEnabled: $enableAlphabetIndexerSelectedFontSize,
          value: $alphabetIndexerSelectedFontSize,
          min: 4,
          max: 16
        })
        RadioBlock({
          title: 'selectedFontStyle',
          isEnabled: $enableAlphabetIndexerSelectedFontStyle,
          value: $alphabetIndexerSelectedFontStyle,
          dataSource: [
            { label: 'Normal', value: FontStyle.Normal },
            { label: 'Italic', value: FontStyle.Italic }
          ]
        })
        RadioBlock({
          title: 'selectedFontWeight',
          isEnabled: $enableAlphabetIndexerSelectedFontWeight,
          value: $alphabetIndexerSelectedFontWeight,
          dataSource: [
            { label: 'Lighter', value: FontWeight.Lighter },
            { label: 'Normal', value: FontWeight.Normal },
            { label: 'Regular', value: FontWeight.Regular },
            { label: 'Medium', value: FontWeight.Medium },
            { label: 'Bold', value: FontWeight.Bold },
            { label: 'Bolder', value: FontWeight.Bolder }
          ]
        })
        SliderBlock({
          title: 'popupFontSize',
          isEnabled: $enableAlphabetIndexerPopupFontSize,
          value: $alphabetIndexerPopupFontSize,
          min: 12,
          max: 32
        })
        RadioBlock({
          title: 'popupFontStyle',
          isEnabled: $enableAlphabetIndexerPopupFontStyle,
          value: $alphabetIndexerPopupFontStyle,
          dataSource: [
            { label: 'Normal', value: FontStyle.Normal },
            { label: 'Italic', value: FontStyle.Italic }
          ]
        })
        RadioBlock({
          title: 'popupFontWeight',
          isEnabled: $enableAlphabetIndexerPopupFontWeight,
          value: $alphabetIndexerPopupFontWeight,
          dataSource: [
            { label: 'Lighter', value: FontWeight.Lighter },
            { label: 'Normal', value: FontWeight.Normal },
            { label: 'Regular', value: FontWeight.Regular },
            { label: 'Medium', value: FontWeight.Medium },
            { label: 'Bold', value: FontWeight.Bold },
            { label: 'Bolder', value: FontWeight.Bolder }
          ]
        })
        SliderBlock({
          title: 'fontSize',
          isEnabled: $enableAlphabetIndexerFontSize,
          value: $alphabetIndexerFontSize,
          min: 4,
          max: 16
        })
        RadioBlock({
          title: 'fontStyle',
          isEnabled: $enableAlphabetIndexerFontStyle,
          value: $alphabetIndexerFontStyle,
          dataSource: [
            { label: 'Normal', value: FontStyle.Normal },
            { label: 'Italic', value: FontStyle.Italic }
          ]
        })
        RadioBlock({
          title: 'fontWeight',
          isEnabled: $enableAlphabetIndexerFontWeight,
          value: $alphabetIndexerFontWeight,
          dataSource: [
            { label: 'Lighter', value: FontWeight.Lighter },
            { label: 'Normal', value: FontWeight.Normal },
            { label: 'Regular', value: FontWeight.Regular },
            { label: 'Medium', value: FontWeight.Medium },
            { label: 'Bold', value: FontWeight.Bold },
            { label: 'Bolder', value: FontWeight.Bolder }
          ]
        })
        SliderBlock({
          title: 'itemSize',
          isEnabled: $enableAlphabetIndexerItemSize,
          value: $alphabetIndexerItemSize,
          min: 12,
          max: 32
        })
        RadioBlock({
          title: 'alignStyle.value',
          isEnabled: $enableAlphabetIndexerAlignStyleIndexerAlign,
          value: $alphabetIndexerAlignStyleIndexerAlign,
          dataSource: [
            { label: 'Left', value: IndexerAlign.Left },
            { label: 'Right', value: IndexerAlign.Right },
            { label: 'START', value: IndexerAlign.START },
            { label: 'END', value: IndexerAlign.END },
          ]
        })
        SliderBlock({
          title: 'alignStyle.offset',
          isEnabled: $enableAlphabetIndexerAlignStyleLength,
          value: $alphabetIndexerAlignStyleLength,
          min: 0,
          max: 50
        })
        SliderBlock({
          title: 'selected',
          isEnabled: $enableAlphabetIndexerSelected,
          value: $alphabetIndexerSelected,
          min: 0,
          max: this.value.length
        })
        SliderBlock({
          title: 'popupPosition.value.x',
          isEnabled: $enableAlphabetIndexerPopupPositionX,
          value: $alphabetIndexerPopupPositionX,
          min: 30,
          max: 90
        })
        SliderBlock({
          title: 'popupPosition.value.y',
          isEnabled: $enableAlphabetIndexerPopupPositionY,
          value: $alphabetIndexerPopupPositionY,
          min: 24,
          max: 72
        })
        ColorBlock({
          title: 'popupSelectedColor',
          isEnabled: $enableAlphabetIndexerPopupSelectedColor,
          color: $alphabetIndexerPopupSelectedColor
        })
        ColorBlock({
          title: 'popupUnselectedColor',
          isEnabled: $enableAlphabetIndexerPopupUnselectedColor,
          color: $alphabetIndexerPopupUnselectedColor
        })
        SliderBlock({
          title: 'popupItemFont.size',
          isEnabled: $enableAlphabetIndexerPopupItemFontSize,
          value: $alphabetIndexerPopupItemFontSize,
          min: 12,
          max: 36
        })
        RadioBlock({
          title: 'popupItemFont.style',
          isEnabled: $enableAlphabetIndexerPopupItemFontStyle,
          value: $alphabetIndexerPopupItemFontStyle,
          dataSource: [
            { label: 'Normal', value: FontStyle.Normal },
            { label: 'Italic', value: FontStyle.Italic }
          ]
        })
        RadioBlock({
          title: 'popupItemFont.weight',
          isEnabled: $enableAlphabetIndexerPopupItemFontStyle,
          value: $alphabetIndexerPopupItemFontStyle,
          dataSource: [
            { label: 'Lighter', value: FontWeight.Lighter },
            { label: 'Normal', value: FontWeight.Normal },
            { label: 'Regular', value: FontWeight.Regular },
            { label: 'Medium', value: FontWeight.Medium },
            { label: 'Bold', value: FontWeight.Bold },
            { label: 'Bolder', value: FontWeight.Bolder }
          ]
        })
        ColorBlock({
          title: 'popupItemBackgroundColor',
          isEnabled: $enableAlphabetIndexerPopupItemBackgroundColor,
          color: $alphabetIndexerPopupItemBackgroundColor
        })
        RadioBlock({
          title: 'autoCollapse',
          isEnabled: $enableAlphabetIndexerAutoCollapse,
          value: $alphabetIndexerAutoCollapse,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })
        SliderBlock({
          title: 'popupItemBorderRadius',
          isEnabled: $enableAlphabetIndexerPopupItemBorderRadius,
          value: $alphabetIndexerPopupItemBorderRadius,
          min: 0,
          max: 48
        })
        SliderBlock({
          title: 'itemBorderRadius',
          isEnabled: $enableAlphabetIndexerItemBorderRadius,
          value: $alphabetIndexerItemBorderRadius,
          min: 0,
          max: 16
        })
        RadioBlock({
          title: 'popupBackgroundBlurStyle',
          isEnabled: $enableAlphabetIndexerPopupBackgroundBlurStyle,
          value: $alphabetIndexerPopupBackgroundBlurStyle,
          dataSource: [
            { label: 'Thin', value: BlurStyle.Thin },
            { label: 'Regular', value: BlurStyle.Regular },
            { label: 'Thick', value: BlurStyle.Thick },
            { label: 'BACKGROUND_THIN', value: BlurStyle.BACKGROUND_THIN },
            { label: 'BACKGROUND_REGULAR', value: BlurStyle.BACKGROUND_REGULAR },
            { label: 'BACKGROUND_THICK', value: BlurStyle.BACKGROUND_THICK },
            { label: 'BACKGROUND_ULTRA_THICK', value: BlurStyle.BACKGROUND_ULTRA_THICK },
            { label: 'NONE', value: BlurStyle.NONE },
            { label: 'COMPONENT_ULTRA_THIN', value: BlurStyle.COMPONENT_ULTRA_THIN },
            { label: 'COMPONENT_THIN', value: BlurStyle.COMPONENT_THIN },
            { label: 'COMPONENT_REGULAR', value: BlurStyle.COMPONENT_REGULAR },
            { label: 'COMPONENT_THICK', value: BlurStyle.COMPONENT_THICK },
            { label: 'COMPONENT_ULTRA_THICK', value: BlurStyle.COMPONENT_ULTRA_THICK },
          ]
        })
        ColorBlock({
          title: 'popupTitleBackground',
          isEnabled: $enableAlphabetIndexerPopupTitleBackground,
          color: $alphabetIndexerPopupTitleBackground
        })
        RadioBlock({
          title: 'enableHapticFeedback',
          isEnabled: $enableAlphabetIndexerEnableHapticFeedback,
          value: $alphabetIndexerEnableHapticFeedback,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })
      }
    }
    .height('52%')
  }
}

@Preview
@Component
struct ButtonBootcampPreviewer {
  build() {
    AlphabetIndexerBootcamp({
      title: '索引条/AlphabetIndexerBootcamp'
    })
  }
}