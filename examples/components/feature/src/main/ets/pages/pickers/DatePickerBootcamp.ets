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
import { ColorBlock, RadioBlock, SliderBlock, useEnabled } from 'common';

@Component
export struct DatePickerBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State enableLunar: boolean = false;
  @State lunar: boolean = false;
  @State enableDisappearTextStyleColor: boolean = false;
  @State disappearTextStyleColor: ResourceColor = '#ff182431';
  @State enableDisappearTextStyleFontSize: boolean = false;
  @State disappearTextStyleFontSize: Length = '14fp';
  @State enableDisappearTextStyleFontWeight: boolean = false;
  @State disappearTextStyleFontWeight: FontWeight = FontWeight.Regular;
  @State enableTextStyleColor: boolean = false;
  @State textStyleColor: ResourceColor = '#ff182431';
  @State enableTextStyleFontSize: boolean = false;
  @State textStyleFontSize: Length = '16fp';
  @State enableTextStyleFontWeight: boolean = false;
  @State textStyleFontWeight: FontWeight = FontWeight.Regular;
  @State enableSelectedTextStyleColor: boolean = false;
  @State selectedTextStyleColor: ResourceColor = '#ff007dff';
  @State enableSelectedTextStyleFontSize: boolean = false;
  @State selectedTextStyleFontSize: Length = '20vp';
  @State enableSelectedTextStyleFontWeight: boolean = false;
  @State selectedTextStyleFontWeight: FontWeight = FontWeight.Medium;
  @State enableCompWidth: boolean = false;
  @State compWidth: Length = 'auto';
  @State enableCompHeight: boolean = false;
  @State compHeight: Length = 'auto';
  @State enableCompPadding: boolean = false;
  @State compPadding: number = 0;
  @State enableCompMargin: boolean = false;
  @State compMargin: number = 0;
  @State enableCompBackgroundColor: boolean = false;
  @State compBackgroundColor: ResourceColor = '#ff000000';
  @State enableCompBorderWidth: boolean = false;
  @State compBorderWidth: number = 0;
  @State enableCompBorderColor: boolean = false;
  @State compBorderColor: ResourceColor = Color.Black;
  @State enableCompBorderRadius: boolean = false;
  @State compBorderRadius: number = 0;
  @State enableCompBorderStyle: boolean = false;
  @State compBorderStyle: BorderStyle = BorderStyle.Solid;
  @State enableCompFlexBasis: boolean = false;
  @State compFlexBasis: number | string = 'auto';
  @State enableCompOpacity: boolean = false;
  @State compOpacity: number = 1;
  @State enableCompVisibility: boolean = false;
  @State compVisibility: Visibility = Visibility.Visible;
  @State enableCompDirection: boolean = false;
  @State compDirection: Direction = Direction.Auto;

  private selectedDate: Date = new Date();

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
    Column({ space: 8 }) {
      Column() {
        DatePicker({
          start: new Date('1970-1-1'),
          end: new Date('2100-1-1'),
          selected: this.selectedDate
        })
          .lunar(useEnabled(this.enableLunar, this.lunar))
          .disappearTextStyle({
            color: useEnabled(this.enableDisappearTextStyleColor, this.disappearTextStyleColor),
            font: {
              size: useEnabled(this.enableDisappearTextStyleFontSize, this.disappearTextStyleFontSize),
              weight: useEnabled(this.enableDisappearTextStyleFontWeight, this.disappearTextStyleFontWeight)
            }
          })
          .textStyle({
            color: useEnabled(this.enableTextStyleColor, this.textStyleColor),
            font: {
              size: useEnabled(this.enableTextStyleFontSize, this.textStyleFontSize),
              weight: useEnabled(this.enableTextStyleFontWeight, this.textStyleFontWeight)
            }
          })
          .selectedTextStyle({
            color: useEnabled(this.enableSelectedTextStyleColor, this.selectedTextStyleColor),
            font: {
              size: useEnabled(this.enableSelectedTextStyleFontSize, this.selectedTextStyleFontSize),
              weight: useEnabled(this.enableSelectedTextStyleFontWeight, this.selectedTextStyleFontWeight)
            }
          })
          .width(useEnabled(this.enableCompWidth, this.compWidth))
          .height(useEnabled(this.enableCompHeight, this.compHeight))
          .padding(useEnabled(this.enableCompPadding, this.compPadding))
          .margin(useEnabled(this.enableCompMargin, this.compMargin))
          .backgroundColor(useEnabled(this.enableCompBackgroundColor, this.compBackgroundColor))
          .borderWidth(useEnabled(this.enableCompBorderWidth, this.compBorderWidth))
          .borderColor(useEnabled(this.enableCompBorderColor, this.compBorderColor))
          .borderRadius(useEnabled(this.enableCompBorderRadius, this.compBorderRadius))
          .borderStyle(useEnabled(this.enableCompBorderStyle, this.compBorderStyle))
          .flexBasis(useEnabled(this.enableCompFlexBasis, this.compFlexBasis))
          .opacity(useEnabled(this.enableCompOpacity, this.compOpacity))
          .visibility(useEnabled(this.enableCompVisibility, this.compVisibility))
          .direction(useEnabled(this.enableCompDirection, this.compDirection))
      }
    }.width('100%').height('100%')
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
        RadioBlock({
          title: 'lunar',
          isEnabled: $enableLunar,
          value: $lunar,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        ColorBlock({
          title: 'disappearTextStyle.color',
          isEnabled: $enableDisappearTextStyleColor,
          color: $disappearTextStyleColor
        })

        SliderBlock({
          title: 'disappearTextStyle.font.size',
          isEnabled: $enableDisappearTextStyleFontSize,
          value: $disappearTextStyleFontSize,
          min: 10,
          max: 30
        })

        RadioBlock({
          title: 'disappearTextStyle.font.weight',
          isEnabled: $enableDisappearTextStyleFontWeight,
          value: $disappearTextStyleFontWeight,
          dataSource: [
            { label: 'Regular', value: FontWeight.Regular },
            { label: 'Medium', value: FontWeight.Medium },
          ]
        })

        ColorBlock({
          title: 'textStyle.color',
          isEnabled: $enableTextStyleColor,
          color: $textStyleColor
        })

        SliderBlock({
          title: 'textStyle.font.size',
          isEnabled: $enableTextStyleFontSize,
          value: $textStyleFontSize,
          min: 10,
          max: 30
        })

        RadioBlock({
          title: 'textStyle.font.weight',
          isEnabled: $enableTextStyleFontWeight,
          value: $textStyleFontWeight,
          dataSource: [
            { label: 'Regular', value: FontWeight.Regular },
            { label: 'Medium', value: FontWeight.Medium },
          ]
        })

        ColorBlock({
          title: 'selectedTextStyle.color',
          isEnabled: $enableSelectedTextStyleColor,
          color: $selectedTextStyleColor
        })

        SliderBlock({
          title: 'selectedTextStyle.font.size',
          isEnabled: $enableSelectedTextStyleFontSize,
          value: $selectedTextStyleFontSize,
          min: 10,
          max: 30
        })

        RadioBlock({
          title: 'selectedTextStyle.font.weight',
          isEnabled: $enableSelectedTextStyleFontWeight,
          value: $selectedTextStyleFontWeight,
          dataSource: [
            { label: 'Regular', value: FontWeight.Regular },
            { label: 'Medium', value: FontWeight.Medium },
          ]
        })

        SliderBlock({
          title: 'width',
          isEnabled: $enableCompWidth,
          value: $compWidth,
          min: 200,
          max: 600
        })

        SliderBlock({
          title: 'height',
          isEnabled: $enableCompHeight,
          value: $compHeight,
          min: 120,
          max: 400
        })

        SliderBlock({
          title: 'padding',
          isEnabled: $enableCompPadding,
          value: $compPadding,
          min: 0,
          max: 50
        })

        SliderBlock({
          title: 'margin',
          isEnabled: $enableCompMargin,
          value: $compMargin,
          min: 0,
          max: 100
        })

        ColorBlock({
          title: 'backgroundColor',
          isEnabled: $enableCompBackgroundColor,
          color: $compBackgroundColor
        })

        SliderBlock({
          title: 'borderWidth',
          isEnabled: $enableCompBorderWidth,
          value: $compBorderWidth,
          min: 0,
          max: 20
        })

        ColorBlock({
          title: 'borderColor',
          isEnabled: $enableCompBorderColor,
          color: $compBorderColor
        })

        SliderBlock({
          title: 'borderRadius',
          isEnabled: $enableCompBorderRadius,
          value: $compBorderRadius,
          min: 0,
          max: 100
        })

        RadioBlock({
          title: 'borderStyle',
          isEnabled: $enableCompBorderStyle,
          value: $compBorderStyle,
          dataSource: [
            { label: 'Solid', value: BorderStyle.Solid },
            { label: 'Dotted', value: BorderStyle.Dotted },
            { label: 'Dashed', value: BorderStyle.Dashed },
          ]
        })

        SliderBlock({
          title: 'flexBasis',
          isEnabled: $enableCompFlexBasis,
          value: $compFlexBasis,
          min: 120,
          max: 300
        })

        SliderBlock({
          title: 'opacity',
          isEnabled: $enableCompOpacity,
          value: $compOpacity,
          min: 0,
          max: 1,
          step: 0.1
        })

        RadioBlock({
          title: 'visibility',
          isEnabled: $enableCompVisibility,
          value: $compVisibility,
          dataSource: [
            { label: 'None', value: Visibility.None },
            { label: 'Hidden', value: Visibility.Hidden },
            { label: 'Visible', value: Visibility.Visible }
          ]
        })

        RadioBlock({
          title: 'direction',
          isEnabled: $enableCompDirection,
          value: $compDirection,
          dataSource: [
            { label: 'Auto', value: Direction.Auto },
            { label: 'Ltr', value: Direction.Ltr },
            { label: 'Rtl', value: Direction.Rtl }
          ]
        })
      }.width('100%')
    }.height('50%')
  }
}

@Preview
@Component
struct DatePickerBootcampPreviewer {
  build() {
    DatePickerBootcamp({
      title: '日期选择器/DatePicker'
    })
  }
}