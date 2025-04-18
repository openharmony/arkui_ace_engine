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
import { ColorBlock, Drawer, RadioBlock, SliderBlock, useEnabled } from 'common'
import {
  DimensionNoPercentage,
  ItemRestriction,
  SegmentButton,
  SegmentButtonItemTuple,
  SegmentButtonOptions,
  SegmentButtonTextItem
} from '@ohos.arkui.advanced.SegmentButton';
import { LengthUnit } from '@kit.ArkUI';

@Component
export struct SegmentButtonBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State @Watch('onChange') enableBtnType: boolean = false;
  @State @Watch('onChange') btnType: string = 'capsule';
  @State @Watch('onChange') enableMultiply: boolean = false;
  @State @Watch('onChange') multiply: boolean = false;
  @State @Watch('onChange') enableButtons: boolean = false;
  @State @Watch('onChange') buttons: SegmentButtonItemTuple =
    [{ text: '按钮1' }, { text: '按钮2' }, { text: '按钮3' }] as SegmentButtonItemTuple;
  @State @Watch('onChange') enableFontColor: boolean = false;
  @State @Watch('onChange') fontColor: ResourceColor | undefined = undefined;
  @State @Watch('onChange') enableSelectedFontColor: boolean = false;
  @State @Watch('onChange') selectedFontColor: ResourceColor | undefined = undefined;
  @State @Watch('onChange') enableFontSize: boolean = false;
  @State @Watch('onChange') fontSize: DimensionNoPercentage = 16;
  @State @Watch('onChange') enableSelectedFontSize: boolean = false;
  @State @Watch('onChange') selectedFontSize: number = 16;
  @State @Watch('onChange') enableFontWeight: boolean = false;
  @State @Watch('onChange') fontWeight: FontWeight = FontWeight.Normal;
  @State @Watch('onChange') enableSelectedFontWeight: boolean = false;
  @State @Watch('onChange') selectedFontWeight: FontWeight = FontWeight.Normal;
  @State @Watch('onChange') enableBackgroundColors: boolean = false;
  @State @Watch('onChange') backgroundColors: ResourceColor = '#007DFF'
  @State @Watch('onChange') enableSelectedBackgroundColor: boolean = false;
  @State @Watch('onChange') selectedBackgroundColor: ResourceColor = '#007DFF'
  @State @Watch('onChange') enableImageSizeWidth: boolean = false;
  @State @Watch('onChange') imageSizeWidth: Length = 24;
  @State @Watch('onChange') enableImageSizeHeight: boolean = false;
  @State @Watch('onChange') imageSizeHeight: Length = 24;
  @State @Watch('onChange') enableButtonPaddingTop: boolean = false
  @State @Watch('onChange') buttonPaddingTop: Length = 4
  @State @Watch('onChange') enableButtonPaddingRight: boolean = false
  @State @Watch('onChange') buttonPaddingRight: Length = 8
  @State @Watch('onChange') enableButtonPaddingBottom: boolean = false
  @State @Watch('onChange') buttonPaddingBottom: Length = 4
  @State @Watch('onChange') enableButtonPaddingLeft: boolean = false
  @State @Watch('onChange') buttonPaddingLeft: Length = 8
  @State @Watch('onChange') enableTextPaddingTop: boolean = false
  @State @Watch('onChange') textPaddingTop: Length = 0
  @State @Watch('onChange') enableTextPaddingRight: boolean = false
  @State @Watch('onChange') textPaddingRight: Length = 0
  @State @Watch('onChange') enableTextPaddingBottom: boolean = false
  @State @Watch('onChange') textPaddingBottom: Length = 0
  @State @Watch('onChange') enableTextPaddingLeft: boolean = false
  @State @Watch('onChange') textPaddingLeft: Length = 0
  @State @Watch('onChange') enableLocalizedButtonPaddingTopValue: boolean = false
  @State @Watch('onChange') localizedButtonPaddingTopValue: number = 4
  @State @Watch('onChange') enableLocalizedButtonPaddingTopUnit: boolean = false
  @State @Watch('onChange') localizedButtonPaddingTopUnit: LengthUnit = LengthUnit.PX
  @State @Watch('onChange') enableLocalizedButtonPaddingEndValue: boolean = false
  @State @Watch('onChange') localizedButtonPaddingEndValue: number = 8
  @State @Watch('onChange') enableLocalizedButtonPaddingEndUnit: boolean = false
  @State @Watch('onChange') localizedButtonPaddingEndUnit: LengthUnit = LengthUnit.PX
  @State @Watch('onChange') enableLocalizedButtonPaddingBottomValue: boolean = false
  @State @Watch('onChange') localizedButtonPaddingBottomValue: number = 4
  @State @Watch('onChange') enableLocalizedButtonPaddingBottomUnit: boolean = false
  @State @Watch('onChange') localizedButtonPaddingBottomUnit: LengthUnit = LengthUnit.PX
  @State @Watch('onChange') enableLocalizedButtonPaddingStartValue: boolean = false
  @State @Watch('onChange') localizedButtonPaddingStartValue: number = 8
  @State @Watch('onChange') enableLocalizedButtonPaddingStartUnit: boolean = false
  @State @Watch('onChange') localizedButtonPaddingStartUnit: LengthUnit = LengthUnit.PX
  @State @Watch('onChange') enableLocalizedTextPaddingTopValue: boolean = false
  @State @Watch('onChange') localizedTextPaddingTopValue: number = 4
  @State @Watch('onChange') enableLocalizedTextPaddingTopUnit: boolean = false
  @State @Watch('onChange') localizedTextPaddingTopUnit: LengthUnit = LengthUnit.PX
  @State @Watch('onChange') enableLocalizedTextPaddingEndValue: boolean = false
  @State @Watch('onChange') localizedTextPaddingEndValue: number = 8
  @State @Watch('onChange') enableLocalizedTextPaddingEndUnit: boolean = false
  @State @Watch('onChange') localizedTextPaddingEndUnit: LengthUnit = LengthUnit.PX
  @State @Watch('onChange') enableLocalizedTextPaddingBottomValue: boolean = false
  @State @Watch('onChange') localizedTextPaddingBottomValue: number = 4
  @State @Watch('onChange') enableLocalizedTextPaddingBottomUnit: boolean = false
  @State @Watch('onChange') localizedTextPaddingBottomUnit: LengthUnit = LengthUnit.PX
  @State @Watch('onChange') enableLocalizedTextPaddingStartValue: boolean = false
  @State @Watch('onChange') localizedTextPaddingStartValue: number = 8
  @State @Watch('onChange') enableLocalizedTextPaddingStartUnit: boolean = false
  @State @Watch('onChange') localizedTextPaddingStartUnit: LengthUnit = LengthUnit.PX
  @State @Watch('onChange') enableDirections: boolean = false;
  @State @Watch('onChange') directions: Direction = Direction.Auto;
  @State @Watch('onChange') enableBackgroundBlurStyles: boolean = false;
  @State @Watch('onChange') backgroundBlurStyles: BlurStyle = BlurStyle.NONE;
  @State tabSelectedIndex: number[] = [1]
  @State singleSelectCapsuleOptions: SegmentButtonOptions = SegmentButtonOptions.capsule({
    multiply: useEnabled(this.enableMultiply, this.multiply),
    buttons: [{ text: '按钮1' }, { text: '按钮2' }, { text: '按钮3' }],
    fontColor: useEnabled(this.enableFontColor, this.fontColor),
    selectedFontColor: useEnabled(this.enableSelectedFontColor, this.selectedFontColor),
    fontSize: useEnabled(this.enableFontSize, this.fontSize),
    selectedFontSize: useEnabled(this.enableSelectedFontSize, this.selectedFontSize),
    fontWeight: useEnabled(this.enableFontWeight, this.fontWeight),
    selectedFontWeight: useEnabled(this.enableSelectedFontWeight, this.selectedFontWeight),
    backgroundColor: useEnabled(this.enableBackgroundColors, this.backgroundColors),
    selectedBackgroundColor: useEnabled(this.enableSelectedBackgroundColor, this.selectedBackgroundColor),
    imageSize: {
      width: useEnabled(this.enableImageSizeWidth, this.imageSizeWidth),
      height: useEnabled(this.enableImageSizeHeight, this.imageSizeHeight),
    },
    buttonPadding: {
      top: useEnabled(this.enableButtonPaddingTop, this.buttonPaddingTop),
      right: useEnabled(this.enableButtonPaddingRight, this.buttonPaddingRight),
      bottom: useEnabled(this.enableButtonPaddingBottom, this.buttonPaddingBottom),
      left: useEnabled(this.enableButtonPaddingLeft, this.buttonPaddingLeft)
    },
    textPadding: {
      top: useEnabled(this.enableTextPaddingTop, this.textPaddingTop),
      right: useEnabled(this.enableTextPaddingRight, this.textPaddingRight),
      bottom: useEnabled(this.enableTextPaddingBottom, this.textPaddingBottom),
      left: useEnabled(this.enableTextPaddingLeft, this.textPaddingLeft)
    },
    localizedButtonPadding: {
      top: {
        value: useEnabled(this.enableLocalizedButtonPaddingTopValue, this.localizedButtonPaddingTopValue) as number,
        unit: useEnabled(this.enableLocalizedButtonPaddingTopUnit,
          this.localizedButtonPaddingTopUnit) as LengthUnit
      },
      end: {
        value: useEnabled(this.enableLocalizedButtonPaddingEndValue, this.localizedButtonPaddingEndValue) as number,
        unit: useEnabled(this.enableLocalizedButtonPaddingEndUnit,
          this.localizedButtonPaddingEndUnit) as LengthUnit
      },
      bottom: {
        value: useEnabled(this.enableLocalizedButtonPaddingBottomValue,
          this.localizedButtonPaddingBottomValue) as number,
        unit: useEnabled(this.enableLocalizedButtonPaddingBottomUnit,
          this.localizedButtonPaddingBottomUnit) as LengthUnit
      },
      start: {
        value: useEnabled(this.enableLocalizedButtonPaddingStartValue, this.localizedButtonPaddingStartValue) as number,
        unit: useEnabled(this.enableLocalizedButtonPaddingStartUnit,
          this.localizedButtonPaddingStartUnit) as LengthUnit
      }
    },
    localizedTextPadding: {
      top: {
        value: useEnabled(this.enableLocalizedTextPaddingTopValue, this.localizedTextPaddingTopValue) as number,
        unit: useEnabled(this.enableLocalizedTextPaddingTopUnit, this.localizedTextPaddingTopUnit) as LengthUnit
      },
      end: {
        value: useEnabled(this.enableLocalizedTextPaddingEndValue, this.localizedTextPaddingEndValue) as number,
        unit: useEnabled(this.enableLocalizedTextPaddingEndUnit, this.localizedTextPaddingEndUnit) as LengthUnit
      },
      bottom: {
        value: useEnabled(this.enableLocalizedTextPaddingBottomValue, this.localizedTextPaddingBottomValue) as number,
        unit: useEnabled(this.enableLocalizedTextPaddingBottomUnit,
          this.localizedTextPaddingBottomUnit) as LengthUnit
      },
      start: {
        value: useEnabled(this.enableLocalizedTextPaddingStartValue, this.localizedTextPaddingStartValue) as number,
        unit: useEnabled(this.enableLocalizedTextPaddingStartUnit,
          this.localizedTextPaddingStartUnit) as LengthUnit
      }
    },
    direction: (useEnabled(this.enableDirections, this.directions)),
    backgroundBlurStyle: useEnabled(this.enableBackgroundBlurStyles,
      this.backgroundBlurStyles)
  })
  scroller: Scroller = new Scroller()

  aboutToAppear(): void {
    AppStorage.setOrCreate('scroller', this.scroller)
  }

  onChange() {
    if (this.btnType === 'tab') {
      this.singleSelectCapsuleOptions = SegmentButtonOptions.tab({
        buttons: useEnabled(this.enableButtons, this.buttons) ?
          useEnabled(this.enableButtons, this.buttons) as ItemRestriction<SegmentButtonTextItem> :
          [{ text: '按钮1' }, { text: '按钮2' }, { text: '按钮3' }],
        fontColor: useEnabled(this.enableFontColor, this.fontColor),
        selectedFontColor: useEnabled(this.enableSelectedFontColor, this.selectedFontColor),
        fontSize: useEnabled(this.enableFontSize, this.fontSize),
        selectedFontSize: useEnabled(this.enableSelectedFontSize, this.selectedFontSize),
        fontWeight: useEnabled(this.enableFontWeight, this.fontWeight),
        selectedFontWeight: useEnabled(this.enableSelectedFontWeight, this.selectedFontWeight),
        backgroundColor: useEnabled(this.enableBackgroundColors, this.backgroundColors),
        selectedBackgroundColor: useEnabled(this.enableSelectedBackgroundColor, this.selectedBackgroundColor),
        imageSize: {
          width: useEnabled(this.enableImageSizeWidth, this.imageSizeWidth) ?
          useEnabled(this.enableImageSizeWidth, this.imageSizeWidth) : 24,
          height: useEnabled(this.enableImageSizeHeight, this.imageSizeHeight) ?
          useEnabled(this.enableImageSizeHeight, this.imageSizeHeight) : 24,
        },
        buttonPadding: {
          top: useEnabled(this.enableButtonPaddingTop, this.buttonPaddingTop),
          right: useEnabled(this.enableButtonPaddingRight, this.buttonPaddingRight),
          bottom: useEnabled(this.enableButtonPaddingBottom, this.buttonPaddingBottom),
          left: useEnabled(this.enableButtonPaddingLeft, this.buttonPaddingLeft)
        },
        textPadding: {
          top: useEnabled(this.enableTextPaddingTop, this.textPaddingTop),
          right: useEnabled(this.enableTextPaddingRight, this.textPaddingRight),
          bottom: useEnabled(this.enableTextPaddingBottom, this.textPaddingBottom),
          left: useEnabled(this.enableTextPaddingLeft, this.textPaddingLeft)
        },
        localizedButtonPadding: {
          top: {
            value: useEnabled(this.enableLocalizedButtonPaddingTopValue, this.localizedButtonPaddingTopValue) as number,
            unit: useEnabled(this.enableLocalizedButtonPaddingTopUnit,
              this.localizedButtonPaddingTopUnit) as LengthUnit
          },
          end: {
            value: useEnabled(this.enableLocalizedButtonPaddingEndValue, this.localizedButtonPaddingEndValue) as number,
            unit: useEnabled(this.enableLocalizedButtonPaddingEndUnit,
              this.localizedButtonPaddingEndUnit) as LengthUnit
          },
          bottom: {
            value: useEnabled(this.enableLocalizedButtonPaddingBottomValue,
              this.localizedButtonPaddingBottomValue) as number,
            unit: useEnabled(this.enableLocalizedButtonPaddingBottomUnit,
              this.localizedButtonPaddingBottomUnit) as LengthUnit
          },
          start: {
            value: useEnabled(this.enableLocalizedButtonPaddingStartValue,
              this.localizedButtonPaddingStartValue) as number,
            unit: useEnabled(this.enableLocalizedButtonPaddingStartUnit,
              this.localizedButtonPaddingStartUnit) as LengthUnit
          }
        },
        localizedTextPadding: {
          top: {
            value: useEnabled(this.enableLocalizedTextPaddingTopValue, this.localizedTextPaddingTopValue) as number,
            unit: useEnabled(this.enableLocalizedTextPaddingTopUnit, this.localizedTextPaddingTopUnit) as LengthUnit
          },
          end: {
            value: useEnabled(this.enableLocalizedTextPaddingEndValue, this.localizedTextPaddingEndValue) as number,
            unit: useEnabled(this.enableLocalizedTextPaddingEndUnit, this.localizedTextPaddingEndUnit) as LengthUnit
          },
          bottom: {
            value: useEnabled(this.enableLocalizedTextPaddingBottomValue,
              this.localizedTextPaddingBottomValue) as number,
            unit: useEnabled(this.enableLocalizedTextPaddingBottomUnit,
              this.localizedTextPaddingBottomUnit) as LengthUnit
          },
          start: {
            value: useEnabled(this.enableLocalizedTextPaddingStartValue, this.localizedTextPaddingStartValue) as number,
            unit: useEnabled(this.enableLocalizedTextPaddingStartUnit,
              this.localizedTextPaddingStartUnit) as LengthUnit
          }
        },
        direction: (useEnabled(this.enableDirections, this.directions)),
        backgroundBlurStyle: useEnabled(this.enableBackgroundBlurStyles,
          this.backgroundBlurStyles)
      })
    } else {
      this.singleSelectCapsuleOptions = SegmentButtonOptions.capsule({
        multiply: useEnabled(this.enableMultiply, this.multiply),
        buttons: useEnabled(this.enableButtons, this.buttons) ?
          useEnabled(this.enableButtons, this.buttons) as SegmentButtonItemTuple :
          [{ text: '按钮1' }, { text: '按钮2' }, { text: '按钮3' }],
        fontColor: useEnabled(this.enableFontColor, this.fontColor),
        selectedFontColor: useEnabled(this.enableSelectedFontColor, this.selectedFontColor),
        fontSize: useEnabled(this.enableFontSize, this.fontSize),
        selectedFontSize: useEnabled(this.enableSelectedFontSize, this.selectedFontSize),
        fontWeight: useEnabled(this.enableFontWeight, this.fontWeight),
        selectedFontWeight: useEnabled(this.enableSelectedFontWeight, this.selectedFontWeight),
        backgroundColor: useEnabled(this.enableBackgroundColors, this.backgroundColors),
        selectedBackgroundColor: useEnabled(this.enableSelectedBackgroundColor, this.selectedBackgroundColor),
        imageSize: {
          width: useEnabled(this.enableImageSizeWidth, this.imageSizeWidth) ?
          useEnabled(this.enableImageSizeWidth, this.imageSizeWidth) : 24,
          height: useEnabled(this.enableImageSizeHeight, this.imageSizeHeight) ?
          useEnabled(this.enableImageSizeHeight, this.imageSizeHeight) : 24,
        },
        buttonPadding: {
          top: useEnabled(this.enableButtonPaddingTop, this.buttonPaddingTop),
          right: useEnabled(this.enableButtonPaddingRight, this.buttonPaddingRight),
          bottom: useEnabled(this.enableButtonPaddingBottom, this.buttonPaddingBottom),
          left: useEnabled(this.enableButtonPaddingLeft, this.buttonPaddingLeft)
        },
        textPadding: {
          top: useEnabled(this.enableTextPaddingTop, this.textPaddingTop),
          right: useEnabled(this.enableTextPaddingRight, this.textPaddingRight),
          bottom: useEnabled(this.enableTextPaddingBottom, this.textPaddingBottom),
          left: useEnabled(this.enableTextPaddingLeft, this.textPaddingLeft)
        },
        localizedButtonPadding: {
          top: {
            value: useEnabled(this.enableLocalizedButtonPaddingTopValue, this.localizedButtonPaddingTopValue) as number,
            unit: useEnabled(this.enableLocalizedButtonPaddingTopUnit,
              this.localizedButtonPaddingTopUnit) as LengthUnit
          },
          end: {
            value: useEnabled(this.enableLocalizedButtonPaddingEndValue, this.localizedButtonPaddingEndValue) as number,
            unit: useEnabled(this.enableLocalizedButtonPaddingEndUnit,
              this.localizedButtonPaddingEndUnit) as LengthUnit
          },
          bottom: {
            value: useEnabled(this.enableLocalizedButtonPaddingBottomValue,
              this.localizedButtonPaddingBottomValue) as number,
            unit: useEnabled(this.enableLocalizedButtonPaddingBottomUnit,
              this.localizedButtonPaddingBottomUnit) as LengthUnit
          },
          start: {
            value: useEnabled(this.enableLocalizedButtonPaddingStartValue,
              this.localizedButtonPaddingStartValue) as number,
            unit: useEnabled(this.enableLocalizedButtonPaddingStartUnit,
              this.localizedButtonPaddingStartUnit) as LengthUnit
          }
        },
        localizedTextPadding: {
          top: {
            value: useEnabled(this.enableLocalizedTextPaddingTopValue, this.localizedTextPaddingTopValue) as number,
            unit: useEnabled(this.enableLocalizedTextPaddingTopUnit, this.localizedTextPaddingTopUnit) as LengthUnit
          },
          end: {
            value: useEnabled(this.enableLocalizedTextPaddingEndValue, this.localizedTextPaddingEndValue) as number,
            unit: useEnabled(this.enableLocalizedTextPaddingEndUnit, this.localizedTextPaddingEndUnit) as LengthUnit
          },
          bottom: {
            value: useEnabled(this.enableLocalizedTextPaddingBottomValue,
              this.localizedTextPaddingBottomValue) as number,
            unit: useEnabled(this.enableLocalizedTextPaddingBottomUnit,
              this.localizedTextPaddingBottomUnit) as LengthUnit
          },
          start: {
            value: useEnabled(this.enableLocalizedTextPaddingStartValue, this.localizedTextPaddingStartValue) as number,
            unit: useEnabled(this.enableLocalizedTextPaddingStartUnit,
              this.localizedTextPaddingStartUnit) as LengthUnit
          }
        },
        direction: (useEnabled(this.enableDirections, this.directions)),
        backgroundBlurStyle: useEnabled(this.enableBackgroundBlurStyles,
          this.backgroundBlurStyles)
      })
    }
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
    .backgroundColor
    ($r
    ('sys.color.ohos_id_color_sub_background'
    ))
    .hideTitleBar(true)
  }

  @Builder
  Content() {
    Column() {
      SegmentButton({ options: this.singleSelectCapsuleOptions, selectedIndexes: $tabSelectedIndex })
    }.width('90%')
  }

  @Builder
  Parameters() {
    Scroll(this.scroller) {
      Column({ space: 8 }) {
        RadioBlock({
          title: 'SegmentButtonOptions.type',
          isEnabled: $enableBtnType,
          value: $btnType,
          dataSource: [
            { label: 'tab', value: 'tab' },
            { label: 'capsule', value: 'capsule' },
          ]
        })
        if (this.btnType === 'capsule') {
          RadioBlock({
            title: 'Multiply',
            isEnabled: $enableMultiply,
            value: $multiply,
            dataSource: [
              { label: 'true', value: true },
              { label: 'false', value: false }
            ]
          })
          RadioBlock({
            title: 'buttons',
            isEnabled: $enableButtons,
            value: $buttons,
            dataSource: [
              {
                label: 'SegmentButtonTextItem',
                value: [{ text: '按钮1' }, { text: '按钮2' }, { text: '按钮3' }] as SegmentButtonItemTuple
              },
              {
                label: 'SegmentButtonIconItem', value: [
                { icon: $r('sys.media.ohos_ic_public_email'), selectedIcon: $r('sys.media.ohos_ic_public_clock') },
                { icon: $r('sys.media.ohos_ic_public_email'), selectedIcon: $r('sys.media.ohos_ic_public_clock') },
                { icon: $r('sys.media.ohos_ic_public_email'), selectedIcon: $r('sys.media.ohos_ic_public_clock') },
                { icon: $r('sys.media.ohos_ic_public_email'), selectedIcon: $r('sys.media.ohos_ic_public_clock') }
              ] as SegmentButtonItemTuple
              },
              {
                label: 'SegmentButtonIconTextItem', value: [
                {
                  text: '图标1',
                  icon: $r('sys.media.ohos_ic_public_email'),
                  selectedIcon: $r('sys.media.ohos_ic_public_clock')
                },
                {
                  text: '图标2',
                  icon: $r('sys.media.ohos_ic_public_email'),
                  selectedIcon: $r('sys.media.ohos_ic_public_clock')
                },
                {
                  text: '图标3',
                  icon: $r('sys.media.ohos_ic_public_email'),
                  selectedIcon: $r('sys.media.ohos_ic_public_clock')
                },
                {
                  text: '图标4',
                  icon: $r('sys.media.ohos_ic_public_email'),
                  selectedIcon: $r('sys.media.ohos_ic_public_clock')
                },
                {
                  text: '图标5',
                  icon: $r('sys.media.ohos_ic_public_email'),
                  selectedIcon: $r('sys.media.ohos_ic_public_clock')
                }
              ] as SegmentButtonItemTuple
              }
            ]
          })
        }
        ColorBlock({
          title: 'fontColor',
          isEnabled: $enableFontColor,
          color: $fontColor
        })
        ColorBlock({
          title: 'selectedFontColor',
          isEnabled: $enableSelectedFontColor,
          color: $selectedFontColor
        })
        RadioBlock({
          title: 'fontWeight',
          isEnabled: $enableFontWeight,
          value: $fontWeight,
          dataSource: [
            { label: 'Lighter', value: FontWeight.Lighter },
            { label: 'Normal', value: FontWeight.Normal },
            { label: 'Regular', value: FontWeight.Regular },
            { label: 'Medium', value: FontWeight.Medium },
            { label: 'Bold', value: FontWeight.Bold },
            { label: 'Bolder', value: FontWeight.Bolder },
          ]
        })
        RadioBlock({
          title: 'selectedFontWeight',
          isEnabled: $enableSelectedFontWeight,
          value: $selectedFontWeight,
          dataSource: [
            { label: 'Lighter', value: FontWeight.Lighter },
            { label: 'Normal', value: FontWeight.Normal },
            { label: 'Regular', value: FontWeight.Regular },
            { label: 'Medium', value: FontWeight.Medium },
            { label: 'Bold', value: FontWeight.Bold },
            { label: 'Bolder', value: FontWeight.Bolder },
          ]
        })
        ColorBlock({
          title: 'backgroundColor',
          isEnabled: $enableBackgroundColors,
          color: $backgroundColors
        })
        ColorBlock({
          title: 'selectedBackgroundColor',
          isEnabled: $enableSelectedBackgroundColor,
          color: $selectedBackgroundColor
        })
        SliderBlock({
          title: 'imageSize.width',
          isEnabled: $enableImageSizeWidth,
          value: $imageSizeWidth,
          min: 0,
          max: 200
        })
        SliderBlock({
          title: 'imageSize.height',
          isEnabled: $enableImageSizeHeight,
          value: $imageSizeHeight,
          min: 0,
          max: 200
        })
        SliderBlock({
          title: 'buttonPadding.top',
          isEnabled: $enableButtonPaddingTop,
          value: $buttonPaddingTop,
          min: 0,
          max: 20
        })
        SliderBlock({
          title: 'buttonPadding.right',
          isEnabled: $enableButtonPaddingRight,
          value: $buttonPaddingRight,
          min: 0,
          max: 20
        })
        SliderBlock({
          title: 'buttonPadding.bottom',
          isEnabled: $enableButtonPaddingBottom,
          value: $buttonPaddingBottom,
          min: 0,
          max: 20
        })
        SliderBlock({
          title: 'buttonPadding.left',
          isEnabled: $enableButtonPaddingLeft,
          value: $buttonPaddingLeft,
          min: 0,
          max: 20
        })
        SliderBlock({
          title: 'textPadding.top',
          isEnabled: $enableTextPaddingTop,
          value: $textPaddingTop,
          min: 0,
          max: 20
        })
        SliderBlock({
          title: 'textPadding.right',
          isEnabled: $enableTextPaddingRight,
          value: $textPaddingRight,
          min: 0,
          max: 20
        })
        SliderBlock({
          title: 'textPadding.bottom',
          isEnabled: $enableTextPaddingBottom,
          value: $textPaddingBottom,
          min: 0,
          max: 20
        })
        SliderBlock({
          title: 'textPadding.left',
          isEnabled: $enableTextPaddingLeft,
          value: $textPaddingLeft,
          min: 0,
          max: 20
        })
        RadioBlock({
          title: 'localizedButtonPadding.top.unit',
          isEnabled: $enableLocalizedButtonPaddingTopUnit,
          value: $localizedButtonPaddingTopUnit,
          dataSource: [
            { label: 'PX', value: LengthUnit.PX },
            { label: 'VP', value: LengthUnit.VP },
            { label: 'FP', value: LengthUnit.FP },
            { label: 'PERCENT', value: LengthUnit.PERCENT },
            { label: 'LPX', value: LengthUnit.LPX },
          ]
        })
        SliderBlock({
          title: 'localizedButtonPadding.top.value',
          isEnabled: $enableLocalizedButtonPaddingTopValue,
          value: $localizedButtonPaddingTopValue,
          min: 0,
          max: 20
        })
        RadioBlock({
          title: 'localizedButtonPadding.end.unit',
          isEnabled: $enableLocalizedButtonPaddingEndUnit,
          value: $localizedButtonPaddingEndUnit,
          dataSource: [
            { label: 'PX', value: LengthUnit.PX },
            { label: 'VP', value: LengthUnit.VP },
            { label: 'FP', value: LengthUnit.FP },
            { label: 'PERCENT', value: LengthUnit.PERCENT },
            { label: 'LPX', value: LengthUnit.LPX },
          ]
        })
        SliderBlock({
          title: 'localizedButtonPadding.end.value',
          isEnabled: $enableLocalizedButtonPaddingEndValue,
          value: $localizedButtonPaddingEndValue,
          min: 0,
          max: 20
        })
        RadioBlock({
          title: 'localizedButtonPadding.bottom.unit',
          isEnabled: $enableLocalizedButtonPaddingBottomUnit,
          value: $localizedButtonPaddingBottomUnit,
          dataSource: [
            { label: 'PX', value: LengthUnit.PX },
            { label: 'VP', value: LengthUnit.VP },
            { label: 'FP', value: LengthUnit.FP },
            { label: 'PERCENT', value: LengthUnit.PERCENT },
            { label: 'LPX', value: LengthUnit.LPX },
          ]
        })
        SliderBlock({
          title: 'localizedButtonPadding.bottom.value',
          isEnabled: $enableLocalizedButtonPaddingBottomValue,
          value: $localizedButtonPaddingBottomValue,
          min: 0,
          max: 20
        })
        RadioBlock({
          title: 'localizedButtonPadding.start.unit',
          isEnabled: $enableLocalizedButtonPaddingStartUnit,
          value: $localizedButtonPaddingStartUnit,
          dataSource: [
            { label: 'PX', value: LengthUnit.PX },
            { label: 'VP', value: LengthUnit.VP },
            { label: 'FP', value: LengthUnit.FP },
            { label: 'PERCENT', value: LengthUnit.PERCENT },
            { label: 'LPX', value: LengthUnit.LPX },
          ]
        })
        SliderBlock({
          title: 'localizedButtonPadding.start.value',
          isEnabled: $enableLocalizedButtonPaddingStartValue,
          value: $localizedButtonPaddingStartValue,
          min: 0,
          max: 20
        })
        RadioBlock({
          title: 'localizedTextPadding.top.unit',
          isEnabled: $enableLocalizedTextPaddingTopUnit,
          value: $localizedTextPaddingTopUnit,
          dataSource: [
            { label: 'PX', value: LengthUnit.PX },
            { label: 'VP', value: LengthUnit.VP },
            { label: 'FP', value: LengthUnit.FP },
            { label: 'PERCENT', value: LengthUnit.PERCENT },
            { label: 'LPX', value: LengthUnit.LPX },
          ]
        })
        SliderBlock({
          title: 'localizedTextPadding.top.value',
          isEnabled: $enableLocalizedTextPaddingTopValue,
          value: $localizedTextPaddingTopValue,
          min: 0,
          max: 20
        })
        RadioBlock({
          title: 'localizedTextPadding.end.unit',
          isEnabled: $enableLocalizedTextPaddingEndUnit,
          value: $localizedTextPaddingEndUnit,
          dataSource: [
            { label: 'PX', value: LengthUnit.PX },
            { label: 'VP', value: LengthUnit.VP },
            { label: 'FP', value: LengthUnit.FP },
            { label: 'PERCENT', value: LengthUnit.PERCENT },
            { label: 'LPX', value: LengthUnit.LPX },
          ]
        })
        SliderBlock({
          title: 'localizedTextPadding.end.value',
          isEnabled: $enableLocalizedTextPaddingEndValue,
          value: $localizedTextPaddingEndValue,
          min: 0,
          max: 20
        })
        RadioBlock({
          title: 'localizedTextPadding.bottom.unit',
          isEnabled: $enableLocalizedTextPaddingBottomUnit,
          value: $localizedTextPaddingBottomUnit,
          dataSource: [
            { label: 'PX', value: LengthUnit.PX },
            { label: 'VP', value: LengthUnit.VP },
            { label: 'FP', value: LengthUnit.FP },
            { label: 'PERCENT', value: LengthUnit.PERCENT },
            { label: 'LPX', value: LengthUnit.LPX },
          ]
        })
        SliderBlock({
          title: 'localizedTextPadding.bottom.value',
          isEnabled: $enableLocalizedTextPaddingBottomValue,
          value: $localizedTextPaddingBottomValue,
          min: 0,
          max: 20
        })
        RadioBlock({
          title: 'localizedTextPadding.start.unit',
          isEnabled: $enableLocalizedTextPaddingStartUnit,
          value: $localizedTextPaddingStartUnit,
          dataSource: [
            { label: 'PX', value: LengthUnit.PX },
            { label: 'VP', value: LengthUnit.VP },
            { label: 'FP', value: LengthUnit.FP },
            { label: 'PERCENT', value: LengthUnit.PERCENT },
            { label: 'LPX', value: LengthUnit.LPX },
          ]
        })
        SliderBlock({
          title: 'localizedTextPadding.start.value',
          isEnabled: $enableLocalizedTextPaddingStartValue,
          value: $localizedTextPaddingStartValue,
          min: 0,
          max: 20
        })
        RadioBlock({
          title: 'Direction',
          isEnabled: $enableDirections,
          value: $directions,
          dataSource: [
            { label: 'Auto', value: Direction.Auto },
            { label: 'Rtl', value: Direction.Rtl },
            { label: 'Ltr', value: Direction.Ltr }
          ]
        })
        RadioBlock({
          title: 'backgroundBlurStyle',
          isEnabled: $enableBackgroundBlurStyles,
          value: $backgroundBlurStyles,
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
            { label: 'COMPONENT_ULTRA_THICK', value: BlurStyle.COMPONENT_ULTRA_THICK }
          ]
        })
      }
    }
    .height('52%')
    .id('scroll')
  }

  @Builder
  Generic() {
    Scroll(this.scroller) {
    }.height('52%')
    .id('scroll')
  }
}

@Preview
@Component
struct SegmentButtonBootcampPreviewer {
  build() {
    SegmentButtonBootcamp({
      title: '多段按钮/SegmentButton'
    })
  }
}