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
export struct TimePickerDialogBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  selectedDate: Date = new Date('2010-1-1');
  private selectTime: Date = new Date('2022-07-22T08:00:00');
  @State enableFormat: boolean = false;
  @State enableUseMilitaryTime: boolean = false;
  @State enableDateTimeOptionsHour: boolean = false;
  @State enableDateTimeOptionsMinute: boolean = false;
  @State enableDateTimeOptionsSecond: boolean = false;
  @State useMilitaryTime: boolean = false;
  @State dateTimeOptionsHour: string = 'numeric';
  @State dateTimeOptionsMinute: string = '2-digit';
  @State dateTimeOptionsSecond: string = '2-digit';
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
  @State isEnableCascade: boolean = false;
  @State enableCascade: boolean = false;
  @State enableHapticFeedback: boolean = false;
  @State hapticFeedback: boolean = true;
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
    Button('弹出弹窗')
      .margin(20)
      .onClick(() => {
        TimePickerDialog.show({
          selected: this.selectTime,
          useMilitaryTime: useEnabled(this.enableUseMilitaryTime, this.useMilitaryTime),
          enableCascade: useEnabled(this.isEnableCascade, this.enableCascade),
          enableHapticFeedback: useEnabled(this.enableHapticFeedback, this.hapticFeedback),
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
            hour: useEnabled(this.enableDateTimeOptionsHour, this.dateTimeOptionsHour),
            minute: useEnabled(this.enableDateTimeOptionsMinute, this.dateTimeOptionsMinute),
          },
          onAccept: (value: TimePickerResult) => {
            if (value.hour != undefined && value.minute != undefined) {
              this.selectTime.setHours(value.hour, value.minute)
              console.info('TimePickerDialog:onAccept()' + JSON.stringify(value))
            }
          },
          onCancel: () => {
            console.info('TimePickerDialog:onCancel()')
          },
          onChange: (value: TimePickerResult) => {
            console.info('TimePickerDialog:onChange()' + JSON.stringify(value))
          },
          onDidAppear: () => {
            console.info('TimePickerDialog:onDidAppear()')
          },
          onDidDisappear: () => {
            console.info('TimePickerDialog:onDidDisappear()')
          },
          onWillAppear: () => {
            console.info('TimePickerDialog:onWillAppear()')
          },
          onWillDisappear: () => {
            console.info('TimePickerDialog:onWillDisappear()')
          }
        })
      })
  }

  @Builder
  Parameters() {
    Scroll(this.scroller) {
      Column({ space: 8 }) {
        RadioBlock({
          title: 'useMilitaryTime',
          isEnabled: $enableUseMilitaryTime,
          value: $useMilitaryTime,
          dataSource: [
            { label: '24-hour', value: true },
            { label: '12-hour', value: false }
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

        RadioBlock({
          title: 'acceptButtonStyle.type',
          isEnabled: $enabledAcceptButtonType,
          value: $acceptButtonType,
          dataSource: [
            { label: 'Capsule', value: ButtonType.Capsule },
            { label: 'Normal', value: ButtonType.Normal },
            { label: 'Circle', value: ButtonType.Circle },
            { label: 'ROUNDED_RECTANGLE', value: ButtonType.ROUNDED_RECTANGLE }
          ]
        })

        RadioBlock({
          title: 'cancelButtonStyle.type',
          isEnabled: $enabledCancelButtonType,
          value: $cancelButtonType,
          dataSource: [
            { label: 'Capsule', value: ButtonType.Capsule },
            { label: 'Normal', value: ButtonType.Normal },
            { label: 'Circle', value: ButtonType.Circle },
            { label: 'ROUNDED_RECTANGLE', value: ButtonType.ROUNDED_RECTANGLE }
          ]
        })

        RadioBlock({
          title: 'acceptButtonStyle.style',
          isEnabled: $enableAcceptButtonStyle,
          value: $acceptButtonStyle,
          dataSource: [
            { label: 'EMPHASIZED', value: ButtonStyleMode.EMPHASIZED },
            { label: 'NORMAL', value: ButtonStyleMode.NORMAL },
            { label: 'TEXTUAL', value: ButtonStyleMode.TEXTUAL }
          ]
        })

        RadioBlock({
          title: 'cancelButtonStyle.style',
          isEnabled: $enableCancelButtonStyle,
          value: $cancelButtonStyle,
          dataSource: [
            { label: 'EMPHASIZED', value: ButtonStyleMode.EMPHASIZED },
            { label: 'NORMAL', value: ButtonStyleMode.NORMAL },
            { label: 'TEXTUAL', value: ButtonStyleMode.TEXTUAL }
          ]
        })

        ColorBlock({
          title: 'acceptButtonStyle.fontColor',
          isEnabled: $enableAcceptButtonFontColor,
          color: $acceptButtonFontColor
        })
        ColorBlock({
          title: 'cancelButtonStyle.fontColor',
          isEnabled: $enableCancelButtonFontColor,
          color: $cancelButtonFontColor
        })

        RadioBlock({
          title: 'acceptButtonStyle.role',
          isEnabled: $enableAcceptButtonRole,
          value: $acceptButtonRole,
          dataSource: [
            { label: 'NORMAL', value: ButtonRole.NORMAL },
            { label: 'ERROR', value: ButtonRole.ERROR }
          ]
        })

        RadioBlock({
          title: 'cancelButtonStyle.role',
          isEnabled: $enableCancelButtonRole,
          value: $cancelButtonRole,
          dataSource: [
            { label: 'NORMAL', value: ButtonRole.NORMAL },
            { label: 'ERROR', value: ButtonRole.ERROR }
          ]
        })

        SliderBlock({
          title: 'acceptButtonStyle.fontSize',
          isEnabled: $enableAcceptButtonFontSize,
          value: $acceptButtonFontSize,
          min: 10,
          max: 30
        })

        SliderBlock({
          title: 'cancelButtonStyle.fontSize',
          isEnabled: $enableCancelButtonFontSize,
          value: $cancelButtonFontSize,
          min: 10,
          max: 30
        })

        SliderBlock({
          title: 'acceptButtonStyle.fontWeight',
          isEnabled: $enableAcceptButtonFontWeight,
          value: $acceptButtonFontWeight,
          min: 400,
          max: 800
        })

        SliderBlock({
          title: 'cancelButtonStyle.fontWeight',
          isEnabled: $enableCancelButtonFontWeight,
          value: $cancelButtonFontWeight,
          min: 400,
          max: 800
        })

        RadioBlock({
          title: 'acceptButtonStyle.fontStyle',
          isEnabled: $enableAcceptButtonFontStyle,
          value: $acceptButtonFontStyle,
          dataSource: [
            { label: 'Normal', value: FontStyle.Normal },
            { label: 'Italic', value: FontStyle.Italic }
          ]
        })

        RadioBlock({
          title: 'cancelButtonStyle.fontStyle',
          isEnabled: $enableCancelButtonFontStyle,
          value: $cancelButtonFontStyle,
          dataSource: [
            { label: 'Normal', value: FontStyle.Normal },
            { label: 'Italic', value: FontStyle.Italic }
          ]
        })

        ColorBlock({
          title: 'acceptButtonStyle.backgroundColor',
          isEnabled: $enableAcceptButtonBackGroundColor,
          color: $acceptButtonBackGroundColor
        })

        ColorBlock({
          title: 'cancelButtonStyle.backgroundColor',
          isEnabled: $enableCancelButtonBackGroundColor,
          color: $cancelButtonBackGroundColor
        })

        SliderBlock({
          title: 'acceptButtonStyle.borderRadius',
          isEnabled: $enableAcceptButtonBorderRadius,
          value: $acceptButtonBorderRadius,
          min: 10,
          max: 100
        })

        SliderBlock({
          title: 'cancelButtonStyle.borderRadius',
          isEnabled: $enableCancelButtonBorderRadius,
          value: $cancelButtonBorderRadius,
          min: 10,
          max: 100
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
          title: 'backgroundColor',
          isEnabled: $enableDialogBackgroundColor,
          color: $dialogBackgroundColor
        })

        RadioBlock({
          title: 'backgroundBlurStyle',
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
          title: 'dateTimeOptions.hour',
          isEnabled: $enableDateTimeOptionsHour,
          value: $dateTimeOptionsHour,
          dataSource: [
            { label: '2-digit', value: '2-digit' },
            { label: 'numeric', value: 'numeric' }
          ]
        })

        RadioBlock({
          title: 'dateTimeOptions.minute',
          isEnabled: $enableDateTimeOptionsMinute,
          value: $dateTimeOptionsMinute,
          dataSource: [
            { label: '2-digit', value: '2-digit' },
            { label: 'numeric', value: 'numeric' }
          ]
        })

        RadioBlock({
          title: '切换12小时制上午下午跟随小时联动/不随小时联动',
          isEnabled: $isEnableCascade,
          value: $enableCascade,
          dataSource: [
            { label: '跟随小时联动', value: false },
            { label: '不随小时联动', value: true }
          ]
        })

        RadioBlock({
          title: 'hapticFeedback',
          isEnabled: this.enableHapticFeedback,
          value: this.hapticFeedback,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
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
struct TimePickerDialogBootcampPreviewer {
  build() {
    TimePickerDialogBootcamp({
      title: '时间选择器弹窗'
    })
  }
}