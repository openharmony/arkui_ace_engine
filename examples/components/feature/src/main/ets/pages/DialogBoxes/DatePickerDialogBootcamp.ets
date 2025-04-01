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
import { RadioBlock, ColorBlock, SliderBlock, useEnabled } from 'common';

@Component
export struct DatePickerDialogBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  selectedDate: Date = new Date('2010-1-1');
  @State enableFormat: boolean = false;
  @State enableMilitaryTime: boolean = false;
  @State enableHourFormat: boolean = false;
  @State enableMinuteFormat: boolean = false;
  @State enableSecondFormat: boolean = false;
  @State isMilitaryTime: boolean = false;
  @State hourFormat: string = 'numeric';
  @State minuteFormat: string = '2-digit';
  @State secondFormat: string = '2-digit';
  @State enabledAcceptButtonType: boolean = false;
  @State acceptButtonType: ButtonType = ButtonType.ROUNDED_RECTANGLE;
  @State enableAcceptButtonStyle: boolean = false;
  @State acceptButtonStyle: ButtonStyleMode = ButtonStyleMode.EMPHASIZED;
  @State enableAcceptButtonRole: boolean = false;
  @State acceptButtonRole: ButtonRole = ButtonRole.NORMAL;
  @State enableAcceptButtonFontSize: boolean = false;
  @State acceptButtonFontSize: Length = '16fp';
  @State enableAcceptButtonFontColor: boolean = false;
  @State acceptButtonFontColor: ResourceColor = '#ffffff';
  @State enableAcceptButtonFontWeight: boolean = false;
  @State acceptButtonFontWeight: FontWeight = 400;
  @State enableAcceptButtonFontStyle: boolean = false;
  @State acceptButtonFontStyle: FontStyle = FontStyle.Normal;
  @State enableAcceptButtonFontFamily: boolean = false;
  @State acceptButtonFontFamily: string = 'sans-serif';
  @State enableAcceptButtonBackGroundColor: boolean = false;
  @State acceptButtonBackGroundColor: ResourceColor = '#ff182431';
  @State enableAcceptButtonBorderRadius: boolean = false;
  @State acceptButtonBorderRadius: Length = 10;
  @State enabledCancelButtonType: boolean = false;
  @State cancelButtonType: ButtonType = ButtonType.ROUNDED_RECTANGLE;
  @State enableCancelButtonStyle: boolean = false;
  @State cancelButtonStyle: ButtonStyleMode = ButtonStyleMode.EMPHASIZED;
  @State enableCancelButtonRole: boolean = false;
  @State cancelButtonRole: ButtonRole = ButtonRole.NORMAL;
  @State enableCancelButtonFontSize: boolean = false;
  @State cancelButtonFontSize: Length = '16fp';
  @State enableCancelButtonFontColor: boolean = false;
  @State cancelButtonFontColor: ResourceColor = '#ffffff';
  @State enableCancelButtonFontWeight: boolean = false;
  @State cancelButtonFontWeight: FontWeight = 400;
  @State enableCancelButtonFontStyle: boolean = false;
  @State cancelButtonFontStyle: FontStyle = FontStyle.Normal;
  @State enableCancelButtonFontFamily: boolean = false;
  @State cancelButtonFontFamily: string = 'sans-serif';
  @State enableCancelButtonBackGroundColor: boolean = false;
  @State cancelButtonBackGroundColor: ResourceColor = '#ff182431';
  @State enableCancelButtonBorderRadius: boolean = false;
  @State cancelButtonBorderRadius: Length = 10;
  @State enableLunar: boolean = false;
  @State lunar: boolean = false;
  @State enableLunarSwitch: boolean = false;
  @State lunarSwitch: boolean = false;
  @State enableShowTime: boolean = false;
  @State showTime: boolean = false;
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
  @State enableAlignment: boolean = false;
  @State alignment: DialogAlignment = DialogAlignment.Default;
  @State enableOffsetDx: boolean = false;
  @State offsetDx: number = 0;
  @State enableOffsetDy: boolean = false;
  @State offsetDy: number = 0;
  @State enableMaskRectX: boolean = false;
  @State maskRectX: number = 0;
  @State enableMaskRectY: boolean = false;
  @State maskRectY: number = 0;
  @State enableMaskRectWidth: boolean = false;
  @State maskRectWidth: string = '100%';
  @State enableMaskRectHeight: boolean = false;
  @State maskRectHeight: string = '100%';
  @State enableDialogBackgroundColor: boolean = false;
  @State dialogBackgroundColor: ResourceColor = Color.Transparent;
  @State enableDialogBackgroundBlurStyle: boolean = false;
  @State dialogBackgroundBlurStyle: BlurStyle = BlurStyle.COMPONENT_ULTRA_THICK;
  @State enableDialogShadow: boolean = false;
  @State dialogShadow: ShadowStyle = ShadowStyle.OUTER_FLOATING_SM;
  @State enableHapticFeedback: boolean = false;
  @State isHapticFeedback: boolean = true;
  @State datePickerMode: DatePickerMode = DatePickerMode.DATE;
  @State enableMode: boolean = false;
  scroller: Scroller = new Scroller();
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
    .backgroundColor($r('sys.color.ohos_id_color_sub_background'))
    .hideTitleBar(true)
  }

  @Builder
  Content() {
    Column() {
      Button('弹出弹窗')
        .margin(20)
        .onClick(() => {
          DatePickerDialog.show({
            start: new Date('2000-1-1'),
            end: new Date('2100-12-31'),
            selected: this.selectedDate,
            // mode: useEnabled(this.enableMode, this.datePickerMode),
            lunar: useEnabled(this.enableLunar, this.lunar),
            lunarSwitch: useEnabled(this.enableLunarSwitch, this.lunarSwitch),
            showTime: useEnabled(this.enableShowTime, this.showTime),
            useMilitaryTime: useEnabled(this.enableMilitaryTime, this.isMilitaryTime),
            enableHapticFeedback: useEnabled(this.enableHapticFeedback, this.isHapticFeedback),
            disappearTextStyle: {
              color: useEnabled(this.enableDisappearTextStyleColor, this.disappearTextStyleColor),
              font: {
                size: useEnabled(this.enableDisappearTextStyleFontSize, this.disappearTextStyleFontSize),
                weight: useEnabled(this.enableDisappearTextStyleFontWeight, this.disappearTextStyleFontWeight),
              }
            },
            textStyle: {
              color: useEnabled(this.enableTextStyleColor, this.textStyleColor),
              font: {
                size: useEnabled(this.enableTextStyleFontSize, this.textStyleFontSize),
                weight: useEnabled(this.enableTextStyleFontWeight, this.textStyleFontWeight),
              }
            },
            selectedTextStyle: {
              color: useEnabled(this.enableSelectedTextStyleColor, this.selectedTextStyleColor),
              font: {
                size: useEnabled(this.enableSelectedTextStyleFontSize, this.selectedTextStyleFontSize),
                weight: useEnabled(this.enableSelectedTextStyleFontWeight, this.selectedTextStyleFontWeight),
              }
            },
            acceptButtonStyle: {
              type: useEnabled(this.enabledAcceptButtonType, this.acceptButtonType),
              style: useEnabled(this.enableAcceptButtonStyle, this.acceptButtonStyle),
              role: useEnabled(this.enableAcceptButtonRole, this.acceptButtonRole),
              fontColor: useEnabled(this.enableAcceptButtonFontColor, this.acceptButtonFontColor),
              fontSize: useEnabled(this.enableAcceptButtonFontSize, this.acceptButtonFontSize),
              fontWeight: useEnabled(this.enableAcceptButtonFontWeight, this.acceptButtonFontWeight),
              fontStyle: useEnabled(this.enableAcceptButtonFontStyle, this.acceptButtonFontStyle),
              fontFamily: useEnabled(this.enableAcceptButtonFontFamily, this.acceptButtonFontFamily),
              backgroundColor: useEnabled(this.enableAcceptButtonBackGroundColor, this.acceptButtonBackGroundColor),
              borderRadius: useEnabled(this.enableAcceptButtonBorderRadius, this.acceptButtonBorderRadius),
            },
            cancelButtonStyle: {
              type: useEnabled(this.enabledCancelButtonType, this.cancelButtonType),
              style: useEnabled(this.enableCancelButtonStyle, this.cancelButtonStyle),
              role: useEnabled(this.enableCancelButtonRole, this.cancelButtonRole),
              fontColor: useEnabled(this.enableCancelButtonFontColor, this.cancelButtonFontColor),
              fontSize: useEnabled(this.enableCancelButtonFontSize, this.cancelButtonFontSize),
              fontWeight: useEnabled(this.enableCancelButtonFontWeight, this.cancelButtonFontWeight),
              fontStyle: useEnabled(this.enableCancelButtonFontStyle, this.cancelButtonFontStyle),
              fontFamily: useEnabled(this.enableCancelButtonFontFamily, this.cancelButtonFontFamily),
              backgroundColor: useEnabled(this.enableCancelButtonBackGroundColor, this.cancelButtonBackGroundColor),
              borderRadius: useEnabled(this.enableCancelButtonBorderRadius, this.cancelButtonBorderRadius),
            },
            alignment: useEnabled(this.enableAlignment, this.alignment),
            offset: {
              dx: useEnabled(this.enableOffsetDx, this.offsetDx),
              dy: useEnabled(this.enableOffsetDy, this.offsetDy),
            },
            maskRect: {
              x: useEnabled(this.enableMaskRectX, this.maskRectX),
              y: useEnabled(this.enableMaskRectY, this.maskRectY),
              width: useEnabled(this.enableMaskRectWidth, this.maskRectWidth),
              height: useEnabled(this.enableMaskRectHeight, this.maskRectHeight),
            },
            backgroundColor: useEnabled(this.enableDialogBackgroundColor, this.dialogBackgroundColor),
            backgroundBlurStyle: useEnabled(this.enableDialogBackgroundBlurStyle, this.dialogBackgroundBlurStyle),
            shadow: useEnabled(this.enableDialogShadow, this.dialogShadow),
            dateTimeOptions: {
              hour: useEnabled(this.enableHourFormat, this.hourFormat),
              minute: useEnabled(this.enableMinuteFormat, this.minuteFormat),
            },
            onDateAccept: (value: Date) => {
              this.selectedDate = value
              console.info('DatePickerDialog:onDateAccept()' + value.toString())
            },
            onCancel: () => {
              console.info('DatePickerDialog:onCancel()')
            },
            onDateChange: (value: Date) => {
              console.info('DatePickerDialog:onDateChange()' + value.toString())
            },
            onDidAppear: () => {
              console.info('DatePickerDialog:onDidAppear()')
            },
            onDidDisappear: () => {
              console.info('DatePickerDialog:onDidDisappear()')
            },
            onWillAppear: () => {
              console.info('DatePickerDialog:onWillAppear()')
            },
            onWillDisappear: () => {
              console.info('DatePickerDialog:onWillDisappear()')
            }
          })
        })
    }.width('100%')
  }

  @Builder
  Parameters() {
    Scroll(this.scroller) {
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

        RadioBlock({
          title: 'lunarSwitch',
          isEnabled: $enableLunarSwitch,
          value: $lunarSwitch,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        RadioBlock({
          title: 'showTime',
          isEnabled: $enableShowTime,
          value: $showTime,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        RadioBlock({
          title: 'useMilitaryTime',
          isEnabled: $enableMilitaryTime,
          value: $isMilitaryTime,
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

        RadioBlock({
          title: 'disappearTextStyle.fontSize',
          isEnabled: $enableDisappearTextStyleFontSize,
          value: $disappearTextStyleFontSize,
          dataSource: [
            { label: '12fp', value: '12fp' },
            { label: '16fp', value: '16fp' },
            { label: '20fp', value: '20fp' },
          ]
        })

        RadioBlock({
          title: 'disappearTextStyle.fontWeight',
          isEnabled: $enableDisappearTextStyleFontWeight,
          value: $disappearTextStyleFontWeight,
          dataSource: [
            { label: 'FontWeight.Regular', value: FontWeight.Regular },
            { label: 'FontWeight.Medium', value: FontWeight.Medium },
          ]
        })

        ColorBlock({
          title: 'textStyle.color',
          isEnabled: $enableTextStyleColor,
          color: $textStyleColor
        })

        RadioBlock({
          title: 'textStyle.fontSize',
          isEnabled: $enableTextStyleFontSize,
          value: $textStyleFontSize,
          dataSource: [
            { label: '12fp', value: '12fp' },
            { label: '16fp', value: '16fp' },
            { label: '20fp', value: '20fp' },
          ]
        })

        RadioBlock({
          title: 'textStyle.fontWeight',
          isEnabled: $enableTextStyleFontWeight,
          value: $textStyleFontWeight,
          dataSource: [
            { label: 'FontWeight.Regular', value: FontWeight.Regular },
            { label: 'FontWeight.Medium', value: FontWeight.Medium },
          ]
        })

        ColorBlock({
          title: 'selectedTextStyle.color',
          isEnabled: $enableSelectedTextStyleColor,
          color: $selectedTextStyleColor
        })

        RadioBlock({
          title: 'selectedTextStyle.fontSize',
          isEnabled: $enableSelectedTextStyleFontSize,
          value: $selectedTextStyleFontSize,
          dataSource: [
            { label: '12vp', value: '12vp' },
            { label: '20vp', value: '20vp' },
            { label: '30vp', value: '30vp' },
          ]
        })

        RadioBlock({
          title: 'selectedTextStyle.fontWeight',
          isEnabled: $enableSelectedTextStyleFontWeight,
          value: $selectedTextStyleFontWeight,
          dataSource: [
            { label: 'FontWeight.Regular', value: FontWeight.Regular },
            { label: 'FontWeight.Medium', value: FontWeight.Medium },
          ]
        })

        RadioBlock({
          title: 'acceptButtonStyle',
          isEnabled: this.enabledAcceptButtonType,
          value: this.acceptButtonType,
          dataSource: [
            { label: 'Capsule', value: ButtonType.Capsule },
            { label: 'Normal', value: ButtonType.Normal },
            { label: 'Circle', value: ButtonType.Circle },
          ]
        })

        RadioBlock({
          title: 'cancelButtonStyle',
          isEnabled: this.enabledCancelButtonType,
          value: this.cancelButtonType,
          dataSource: [
            { label: 'Capsule', value: ButtonType.Capsule },
            { label: 'Normal', value: ButtonType.Normal },
            { label: 'Circle', value: ButtonType.Circle },
          ]
        })

        RadioBlock({
          title: 'acceptButtonType',
          isEnabled: this.enableAcceptButtonStyle,
          value: this.acceptButtonStyle,
          dataSource: [
            { label: 'EMPHASIZED', value: ButtonStyleMode.EMPHASIZED },
            { label: 'NORMAL', value: ButtonStyleMode.NORMAL },
            { label: 'TEXTUAL', value: ButtonStyleMode.TEXTUAL }
          ]
        })

        RadioBlock({
          title: 'cancelButtonType',
          isEnabled: this.enableCancelButtonStyle,
          value: this.cancelButtonStyle,
          dataSource: [
            { label: 'EMPHASIZED', value: ButtonStyleMode.EMPHASIZED },
            { label: 'NORMAL', value: ButtonStyleMode.NORMAL },
            { label: 'TEXTUAL', value: ButtonStyleMode.TEXTUAL }
          ]
        })

        ColorBlock({
          title: 'acceptButtonStyle.fontColor',
          isEnabled: this.enableAcceptButtonFontColor,
          color: this.acceptButtonFontColor
        })

        ColorBlock({
          title: 'cancelButtonStyle.fontColor',
          isEnabled: this.enableCancelButtonFontColor,
          color: this.cancelButtonFontColor
        })

        RadioBlock({
          title: 'acceptButton.role',
          isEnabled: this.enableAcceptButtonRole,
          value: this.acceptButtonRole,
          dataSource: [
            { label: 'NORMAL', value: ButtonRole.NORMAL },
            { label: 'ERROR', value: ButtonRole.ERROR }
          ]
        })

        RadioBlock({
          title: 'cancelButton.role',
          isEnabled: this.enableCancelButtonRole,
          value: this.cancelButtonRole,
          dataSource: [
            { label: 'NORMAL', value: ButtonRole.NORMAL },
            { label: 'ERROR', value: ButtonRole.ERROR }
          ]
        })

        RadioBlock({
          title: 'acceptButton.size',
          isEnabled: this.enableAcceptButtonFontSize,
          value: this.acceptButtonFontSize,
          dataSource: [
            { label: '16fp', value: '16fp' },
            { label: '12fp', value: '12fp' },
          ]
        })

        RadioBlock({
          title: 'cancelButton.size',
          isEnabled: this.enableCancelButtonFontSize,
          value: this.cancelButtonFontSize,
          dataSource: [
            { label: '16fp', value: '16fp' },
            { label: '12fp', value: '12fp' },
          ]
        })

        RadioBlock({
          title: 'acceptButton.fontWeight',
          isEnabled: this.enableAcceptButtonFontWeight,
          value: this.acceptButtonFontWeight,
          dataSource: [
            { label: '400px', value: 400 },
            { label: '800px', value: 800 },
          ]
        })

        RadioBlock({
          title: 'cancelButton.fontWeight',
          isEnabled: this.enableCancelButtonFontWeight,
          value: this.cancelButtonFontWeight,
          dataSource: [
            { label: '400px', value: 400 },
            { label: '800px', value: 800 },
          ]
        })

        RadioBlock({
          title: 'acceptButton.fontStyle',
          isEnabled: this.enableAcceptButtonFontStyle,
          value: this.acceptButtonFontStyle,
          dataSource: [
            { label: 'Normal', value: FontStyle.Normal },
            { label: 'Italic', value: FontStyle.Italic },
          ]
        })

        RadioBlock({
          title: 'cancelButton.fontStyle',
          isEnabled: this.enableCancelButtonFontStyle,
          value: this.cancelButtonFontStyle,
          dataSource: [
            { label: 'Normal', value: FontStyle.Normal },
            { label: 'Italic', value: FontStyle.Italic },
          ]
        })

        ColorBlock({
          title: 'acceptButton.backgroundColor',
          isEnabled: this.enableAcceptButtonBackGroundColor,
          color: this.acceptButtonBackGroundColor
        })

        ColorBlock({
          title: 'cancelButton.backgroundColor',
          isEnabled: this.enableCancelButtonBackGroundColor,
          color: this.cancelButtonBackGroundColor
        })

        RadioBlock({
          title: 'acceptButton.borderRadius',
          isEnabled: this.enableAcceptButtonBorderRadius,
          value: this.acceptButtonBorderRadius,
          dataSource: [
            { label: '10px', value: 10 },
            { label: '100px', value: 100 },
          ]
        })

        RadioBlock({
          title: 'cancelButton.borderRadius',
          isEnabled: this.enableCancelButtonBorderRadius,
          value: this.cancelButtonBorderRadius,
          dataSource: [
            { label: '10px', value: 10 },
            { label: '100px', value: 100 },
          ]
        })

        RadioBlock({
          title: 'alignment',
          isEnabled: $enableAlignment,
          value: $alignment,
          dataSource: [
            { label: 'Top', value: DialogAlignment.Top },
            { label: 'Center', value: DialogAlignment.Center },
            { label: 'Bottom', value: DialogAlignment.Bottom },
            { label: 'Default', value: DialogAlignment.Default }
          ]
        })

        SliderBlock({
          title: 'offset.dx',
          isEnabled: $enableOffsetDx,
          value: $offsetDx,
          min: -40,
          max: 40
        })

        SliderBlock({
          title: 'offset.dy',
          isEnabled: $enableOffsetDy,
          value: $offsetDy,
          min: -100,
          max: 100
        })

        SliderBlock({
          title: 'maskRect.x',
          isEnabled: $enableMaskRectX,
          value: $maskRectX,
          min: 0,
          max: 200
        })

        SliderBlock({
          title: 'maskRect.y',
          isEnabled: $enableMaskRectY,
          value: $maskRectY,
          min: 0,
          max: 400
        })

        RadioBlock({
          title: 'maskRect.width',
          isEnabled: $enableMaskRectWidth,
          value: $maskRectWidth,
          dataSource: [
            { label: '50%', value: '50%' },
            { label: '100%', value: '100%' }
          ]
        })

        RadioBlock({
          title: 'maskRect.height',
          isEnabled: $enableMaskRectHeight,
          value: $maskRectHeight,
          dataSource: [
            { label: '50%', value: '50%' },
            { label: '100%', value: '100%' }
          ]
        })

        ColorBlock({
          title: 'dialogBackgroundColor',
          isEnabled: $enableDialogBackgroundColor,
          color: $dialogBackgroundColor
        })

        RadioBlock({
          title: 'DialogBackgroundBlurStyle',
          isEnabled: $enableDialogBackgroundBlurStyle,
          value: $dialogBackgroundBlurStyle,
          dataSource: [
            { label: 'Thin', value: BlurStyle.Thin },
            { label: 'COMPONENT_ULTRA_THICK', value: BlurStyle.COMPONENT_ULTRA_THICK }
          ]
        })

        RadioBlock({
          title: 'shadow',
          isEnabled: $enableDialogShadow,
          value: $dialogShadow,
          dataSource: [
            { label: 'OUTER_FLOATING_MD', value: ShadowStyle.OUTER_FLOATING_MD },
            { label: 'OUTER_FLOATING_SM', value: ShadowStyle.OUTER_FLOATING_SM }
          ]
        })

        RadioBlock({
          title: 'hourFormat',
          isEnabled: this.enableHourFormat,
          value: this.hourFormat,
          dataSource: [
            { label: '2-digit', value: '2-digit' },
            { label: 'numeric', value: 'numeric' },
          ]
        })

        RadioBlock({
          title: 'minuteFormat',
          isEnabled: this.enableMinuteFormat,
          value: this.minuteFormat,
          dataSource: [
            { label: '2-digit', value: '2-digit' },
            { label: 'numeric', value: 'numeric' },
          ]
        })

        RadioBlock({
          title: 'hapticFeedback',
          isEnabled: this.enableHapticFeedback,
          value: this.isHapticFeedback,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false },
          ]
        })

        RadioBlock({
          title: '是否设置选项列',
          isEnabled: $enableMode,
          value: $datePickerMode,
          dataSource: [
            { label: '年月日', value: DatePickerMode.DATE },
            { label: '年和月', value: DatePickerMode.YEAR_AND_MONTH },
            { label: '月和日', value: DatePickerMode.MONTH_AND_DAY }
          ]
        })
      }.width('100%')
    }.height('50%').id('scroll')
  }

  @Builder
  Generic() {

  }
}

@Preview
@Component
struct DatePickerDialogBootcampPreviewer {
  build() {
    DatePickerDialogBootcamp({
      title: '日期选择器弹窗/DatepickerDialog'
    })
  }
}