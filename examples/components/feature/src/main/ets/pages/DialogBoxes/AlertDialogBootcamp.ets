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

@Entry
@Component
export struct AlertDialogBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State oneButton: boolean = true;
  @State twoButton: boolean = false;
  @State threeButton: boolean = false;
  @State alertDialogParamAutoCancel: boolean = true;
  @State enableAlertDialogParamAutoCancel: boolean = false;
  @State alertDialogParamAlignment: DialogAlignment = DialogAlignment.Default;
  @State enableAlertDialogParamAlignment: boolean = false;
  @State alertDialogParamOffsetDx: number = 0;
  @State enableAlertDialogParamOffsetDx: boolean = false;
  @State alertDialogParamOffsetDy: number = 0;
  @State enableAlertDialogParamOffsetDy: boolean = false;
  @State alertDialogParamGridCount: number = 4;
  @State enableAlertDialogParamGridCount: boolean = false;
  @State alertDialogParamShowInSubWindow: boolean = false;
  @State enableAlertDialogParamShowInSubWindow: boolean = false;
  @State alertDialogParamIsModal: boolean = true;
  @State enableAlertDialogParamIsModal: boolean = false;
  @State alertDialogParamBackgroundColor: Color = Color.Transparent;
  @State enableAlertDialogParamBackgroundColor: boolean = false;
  @State alertDialogParamBackgroundBlurStyle: BlurStyle = BlurStyle.COMPONENT_ULTRA_THICK;
  @State enableAlertDialogParamBackgroundBlurStyle: boolean = false;
  @State alertDialogParamBackgroundBlurRadius: number = 0;
  @State enableAlertDialogParamBackgroundBlurRadius: boolean = false;
  @State alertDialogParamBackgroundBlurDistance: number = 0;
  @State enableAlertDialogParamBackgroundBlurDistance: boolean = false;
  @State alertDialogParamCornerRadiusTopLeft: number = 32;
  @State enableAlertDialogParamCornerRadiusTopLeft: boolean = false;
  @State alertDialogParamCornerRadiusTopRight: number = 32;
  @State enableAlertDialogParamCornerRadiusTopRight: boolean = false;
  @State alertDialogParamCornerRadiusBottomLeft: number = 32;
  @State enableAlertDialogParamCornerRadiusBottomLeft: boolean = false;
  @State alertDialogParamCornerRadiusBottomRight: number = 32;
  @State enableAlertDialogParamCornerRadiusBottomRight: boolean = false;
  @State alertDialogParamTextStyleWordBreak: WordBreak = WordBreak.BREAK_ALL;
  @State enableAlertDialogParamTextStyleWordBreak: boolean = false;
  @State alertDialogParamShadow: ShadowStyle = ShadowStyle.OUTER_FLOATING_MD;
  @State enableAlertDialogParamShadow: boolean = false;
  @State alertDialogParamBorderWidth: number = 0;
  @State enableAlertDialogParamBorderWidth: boolean = false;
  @State alertDialogParamBorderColor: Color = Color.Black;
  @State enableAlertDialogParamBorderColor: boolean = false;
  @State alertDialogParamBorderRadius: number = 0;
  @State enableAlertDialogParamBorderRadius: boolean = false;
  @State alertDialogParamBorderStyle: BorderStyle = BorderStyle.Solid;
  @State enableAlertDialogParamBorderStyle: boolean = false;
  @State alertDialogParamWidth: number = 400;
  @State enableAlertDialogParamWidth: boolean = false;
  @State alertDialogParamHeight: number = 400;
  @State enableAlertDialogParamHeight: boolean = false;
  @State alertDialogParamMaskRectX: number = 0;
  @State enableAlertDialogParamMaskRectX: boolean = false;
  @State alertDialogParamMaskRectY: number = 0;
  @State enableAlertDialogParamMaskRectY: boolean = false;
  @State alertDialogParamMaskRectWidth: string = '100%';
  @State enableAlertDialogParamMaskRectWidth: boolean = false;
  @State alertDialogParamMaskRectHeight: string = '100%';
  @State enableAlertDialogParamMaskRectHeight: boolean = false;
  @State alertDialogParamConfirmEnabled: boolean = true;
  @State enableAlertDialogParamConfirmEnabled: boolean = false;
  @State alertDialogParamConfirmDefaultFocus: boolean = false;
  @State enableAlertDialogParamConfirmDefaultFocus: boolean = false;
  @State alertDialogParamConfirmStyle: DialogButtonStyle = DialogButtonStyle.DEFAULT;
  @State enableAlertDialogParamConfirmStyle: boolean = false;
  @State alertDialogParamConfirmFontColor: Color = Color.Black;
  @State enableAlertDialogParamConfirmFontColor: boolean = false;
  @State alertDialogParamConfirmBackgroundColor: Color = Color.Transparent;
  @State enableAlertDialogParamConfirmBackgroundColor: boolean = false;
  @State alertDialogParamPrimaryButtonEnabled: boolean = true;
  @State enableAlertDialogParamPrimaryButtonEnabled: boolean = false;
  @State alertDialogParamPrimaryButtonDefaultFocus: boolean = false;
  @State enableAlertDialogParamPrimaryButtonDefaultFocus: boolean = false;
  @State alertDialogParamPrimaryButtonStyle: DialogButtonStyle = DialogButtonStyle.DEFAULT;
  @State enableAlertDialogParamPrimaryButtonStyle: boolean = false;
  @State alertDialogParamPrimaryButtonFontColor: Color = Color.Black;
  @State enableAlertDialogParamPrimaryButtonFontColor: boolean = false;
  @State alertDialogParamPrimaryButtonBackgroundColor: Color = Color.Transparent;
  @State enableAlertDialogParamPrimaryButtonBackgroundColor: boolean = false;
  @State alertDialogParamSecondaryButtonEnabled: boolean = true;
  @State enableAlertDialogParamSecondaryButtonEnabled: boolean = false;
  @State alertDialogParamSecondaryButtonDefaultFocus: boolean = false;
  @State enableAlertDialogParamSecondaryButtonDefaultFocus: boolean = false;
  @State alertDialogParamSecondaryButtonStyle: DialogButtonStyle = DialogButtonStyle.DEFAULT;
  @State enableAlertDialogParamSecondaryButtonStyle: boolean = false;
  @State alertDialogParamSecondaryButtonFontColor: Color = Color.Black;
  @State enableAlertDialogParamSecondaryButtonFontColor: boolean = false;
  @State alertDialogParamSecondaryButtonBackgroundColor: Color = Color.Transparent;
  @State enableAlertDialogParamSecondaryButtonBackgroundColor: boolean = false;
  @State alertDialogParamButtonsEnabled: boolean = true;
  @State enableAlertDialogParamButtonsEnabled: boolean = false;
  @State alertDialogParamButtonsDefaultFocus: boolean = false;
  @State enableAlertDialogParamButtonsDefaultFocus: boolean = false;
  @State alertDialogParamButtonsStyle: DialogButtonStyle = DialogButtonStyle.DEFAULT;
  @State enableAlertDialogParamButtonsStyle: boolean = false;
  @State alertDialogParamButtonsFontColor: Color = Color.Black;
  @State enableAlertDialogParamButtonsFontColor: boolean = false;
  @State alertDialogParamButtonsBackgroundColor: Color = Color.Transparent;
  @State enableAlertDialogParamButtonsBackgroundColor: boolean = false;
  @State alertDialogParamButtonDirection: DialogButtonDirection = DialogButtonDirection.AUTO;
  @State enableAlertDialogParamButtonDirection: boolean = false;

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
    Column({ space: 24 }) {
      if (this.oneButton) {
        Button('oneButton')
          .onClick(() => {
            AlertDialog.show(
              {
                title: 'title',
                message: 'text',
                autoCancel: useEnabled(this.enableAlertDialogParamAutoCancel, this.alertDialogParamAutoCancel),
                alignment: useEnabled(this.enableAlertDialogParamAlignment, this.alertDialogParamAlignment),
                offset: {
                  dx: useEnabled(this.enableAlertDialogParamOffsetDx, this.alertDialogParamOffsetDx),
                  dy: useEnabled(this.enableAlertDialogParamOffsetDy, this.alertDialogParamOffsetDy)
                },
                gridCount: useEnabled(this.enableAlertDialogParamGridCount, this.alertDialogParamGridCount),
                isModal: useEnabled(this.enableAlertDialogParamIsModal, this.alertDialogParamIsModal),
                backgroundColor: useEnabled(this.enableAlertDialogParamBackgroundColor,
                  this.alertDialogParamBackgroundColor),
                backgroundBlurStyle: useEnabled(this.enableAlertDialogParamBackgroundBlurStyle,
                  this.alertDialogParamBackgroundBlurStyle),
                cornerRadius: {
                  topLeft: useEnabled(this.enableAlertDialogParamCornerRadiusTopLeft,
                    this.alertDialogParamCornerRadiusTopLeft),
                  topRight: useEnabled(this.enableAlertDialogParamCornerRadiusTopRight,
                    this.alertDialogParamCornerRadiusTopRight),
                  bottomLeft: useEnabled(this.enableAlertDialogParamCornerRadiusBottomLeft,
                    this.alertDialogParamCornerRadiusBottomLeft),
                  bottomRight: useEnabled(this.enableAlertDialogParamCornerRadiusBottomRight,
                    this.alertDialogParamCornerRadiusBottomRight)
                },
                textStyle: {
                  wordBreak: useEnabled(this.enableAlertDialogParamTextStyleWordBreak,
                    this.alertDialogParamTextStyleWordBreak)
                },
                shadow: useEnabled(this.enableAlertDialogParamShadow, this.alertDialogParamShadow),
                borderWidth: useEnabled(this.enableAlertDialogParamBorderWidth, this.alertDialogParamBorderWidth),
                borderStyle: useEnabled(this.enableAlertDialogParamBorderStyle, this.alertDialogParamBorderStyle),
                borderColor: useEnabled(this.enableAlertDialogParamBorderColor, this.alertDialogParamBorderColor),
                width: useEnabled(this.enableAlertDialogParamWidth, this.alertDialogParamWidth),
                height: useEnabled(this.enableAlertDialogParamHeight, this.alertDialogParamHeight),
                showInSubWindow: useEnabled(this.enableAlertDialogParamShowInSubWindow,
                  this.alertDialogParamShowInSubWindow),
                maskRect: {
                  x: useEnabled(this.enableAlertDialogParamMaskRectX, this.alertDialogParamMaskRectX),
                  y: useEnabled(this.enableAlertDialogParamMaskRectY, this.alertDialogParamMaskRectY),
                  width: useEnabled(this.enableAlertDialogParamMaskRectWidth, this.alertDialogParamMaskRectWidth),
                  height: useEnabled(this.enableAlertDialogParamMaskRectHeight, this.alertDialogParamMaskRectHeight)
                },
                confirm: {
                  value: 'button',
                  enabled: useEnabled(this.enableAlertDialogParamConfirmEnabled, this.alertDialogParamConfirmEnabled),
                  defaultFocus: useEnabled(this.enableAlertDialogParamConfirmDefaultFocus,
                    this.alertDialogParamConfirmDefaultFocus),
                  style: useEnabled(this.enableAlertDialogParamConfirmStyle, this.alertDialogParamConfirmStyle),
                  fontColor: useEnabled(this.enableAlertDialogParamConfirmFontColor,
                    this.alertDialogParamConfirmFontColor),
                  backgroundColor: useEnabled(this.enableAlertDialogParamConfirmBackgroundColor,
                    this.alertDialogParamConfirmBackgroundColor),
                  action: () => {
                    console.info('Button-clicking callback')
                  }
                },
                cancel: () => {
                  console.info('Closed callbacks')
                },
                onWillDismiss: (dismissDialogAction: DismissDialogAction) => {
                  console.info('reason=' + JSON.stringify(dismissDialogAction.reason))
                  console.log('dialog onWillDismiss')
                  if (dismissDialogAction.reason === DismissReason.PRESS_BACK) {
                    dismissDialogAction.dismiss()
                  }
                  if (dismissDialogAction.reason === DismissReason.TOUCH_OUTSIDE) {
                    dismissDialogAction.dismiss()
                  }
                }
              }
            )
            this.oneButton = true;
            this.twoButton = false;
            this.threeButton = false;
          })
          .backgroundColor(0x317aff)
      }

      if (this.twoButton) {
        Button('twoButton')
          .onClick(() => {
            this.oneButton = false;
            this.twoButton = true;
            this.threeButton = false;
            AlertDialog.show(
              {
                title: 'title',
                message: 'text',
                autoCancel: useEnabled(this.enableAlertDialogParamAutoCancel, this.alertDialogParamAutoCancel),
                alignment: useEnabled(this.enableAlertDialogParamAlignment, this.alertDialogParamAlignment),
                offset: {
                  dx: useEnabled(this.enableAlertDialogParamOffsetDx, this.alertDialogParamOffsetDx),
                  dy: useEnabled(this.enableAlertDialogParamOffsetDy, this.alertDialogParamOffsetDy)
                },
                gridCount: useEnabled(this.enableAlertDialogParamGridCount, this.alertDialogParamGridCount),
                isModal: useEnabled(this.enableAlertDialogParamIsModal, this.alertDialogParamIsModal),
                backgroundColor: useEnabled(this.enableAlertDialogParamBackgroundColor,
                  this.alertDialogParamBackgroundColor),
                backgroundBlurStyle: useEnabled(this.enableAlertDialogParamBackgroundBlurStyle,
                  this.alertDialogParamBackgroundBlurStyle),
                cornerRadius: {
                  topLeft: useEnabled(this.enableAlertDialogParamCornerRadiusTopLeft,
                    this.alertDialogParamCornerRadiusTopLeft),
                  topRight: useEnabled(this.enableAlertDialogParamCornerRadiusTopRight,
                    this.alertDialogParamCornerRadiusTopRight),
                  bottomLeft: useEnabled(this.enableAlertDialogParamCornerRadiusBottomLeft,
                    this.alertDialogParamCornerRadiusBottomLeft),
                  bottomRight: useEnabled(this.enableAlertDialogParamCornerRadiusBottomRight,
                    this.alertDialogParamCornerRadiusBottomRight)
                },
                textStyle: {
                  wordBreak: useEnabled(this.enableAlertDialogParamTextStyleWordBreak,
                    this.alertDialogParamTextStyleWordBreak)
                },
                shadow: useEnabled(this.enableAlertDialogParamShadow, this.alertDialogParamShadow),
                borderWidth: useEnabled(this.enableAlertDialogParamBorderWidth, this.alertDialogParamBorderWidth),
                borderStyle: useEnabled(this.enableAlertDialogParamBorderStyle, this.alertDialogParamBorderStyle),
                borderColor: useEnabled(this.enableAlertDialogParamBorderColor, this.alertDialogParamBorderColor),
                width: useEnabled(this.enableAlertDialogParamWidth, this.alertDialogParamWidth),
                height: useEnabled(this.enableAlertDialogParamHeight, this.alertDialogParamHeight),
                showInSubWindow: useEnabled(this.enableAlertDialogParamShowInSubWindow,
                  this.alertDialogParamShowInSubWindow),
                maskRect: {
                  x: useEnabled(this.enableAlertDialogParamMaskRectX, this.alertDialogParamMaskRectX),
                  y: useEnabled(this.enableAlertDialogParamMaskRectY, this.alertDialogParamMaskRectY),
                  width: useEnabled(this.enableAlertDialogParamMaskRectWidth, this.alertDialogParamMaskRectWidth),
                  height: useEnabled(this.enableAlertDialogParamMaskRectHeight, this.alertDialogParamMaskRectHeight)
                },

                primaryButton: {
                  value: 'cancel',
                  enabled: useEnabled(this.enableAlertDialogParamPrimaryButtonEnabled,
                    this.alertDialogParamPrimaryButtonEnabled),
                  defaultFocus: useEnabled(this.enableAlertDialogParamPrimaryButtonDefaultFocus,
                    this.alertDialogParamPrimaryButtonDefaultFocus),
                  style: useEnabled(this.enableAlertDialogParamPrimaryButtonStyle,
                    this.alertDialogParamPrimaryButtonStyle),
                  fontColor: useEnabled(this.enableAlertDialogParamPrimaryButtonFontColor,
                    this.alertDialogParamPrimaryButtonFontColor),
                  backgroundColor: useEnabled(this.enableAlertDialogParamPrimaryButtonBackgroundColor,
                    this.alertDialogParamPrimaryButtonBackgroundColor),
                  action: () => {
                    console.info('Callback when the first button is clicked')
                  }
                },
                secondaryButton: {
                  enabled: useEnabled(this.enableAlertDialogParamSecondaryButtonEnabled,
                    this.alertDialogParamSecondaryButtonEnabled),
                  defaultFocus: useEnabled(this.enableAlertDialogParamSecondaryButtonDefaultFocus,
                    this.alertDialogParamSecondaryButtonDefaultFocus),
                  style: useEnabled(this.enableAlertDialogParamSecondaryButtonStyle,
                    this.alertDialogParamSecondaryButtonStyle),
                  value: 'ok',
                  fontColor: useEnabled(this.enableAlertDialogParamSecondaryButtonFontColor,
                    this.alertDialogParamSecondaryButtonFontColor),
                  backgroundColor: useEnabled(this.enableAlertDialogParamSecondaryButtonBackgroundColor,
                    this.alertDialogParamSecondaryButtonBackgroundColor),
                  action: () => {
                    console.info('Callback when the second button is clicked')
                  }
                },
                cancel: () => {
                  console.info('Closed callbacks')
                },
                onWillDismiss: (dismissDialogAction: DismissDialogAction) => {
                  console.info('reason=' + JSON.stringify(dismissDialogAction.reason))
                  console.log('dialog onWillDismiss')
                  if (dismissDialogAction.reason === DismissReason.PRESS_BACK) {
                    dismissDialogAction.dismiss()
                  }
                  if (dismissDialogAction.reason === DismissReason.TOUCH_OUTSIDE) {
                    dismissDialogAction.dismiss()
                  }
                }
              }
            )
          })
          .backgroundColor(0x317aff)
      }

      if (this.threeButton) {
        Button('threeButton')
          .onClick(() => {
            AlertDialog.show(
              {
                title: 'title',
                message: 'text',
                autoCancel: useEnabled(this.enableAlertDialogParamAutoCancel, this.alertDialogParamAutoCancel),
                alignment: useEnabled(this.enableAlertDialogParamAlignment, this.alertDialogParamAlignment),
                offset: {
                  dx: useEnabled(this.enableAlertDialogParamOffsetDx, this.alertDialogParamOffsetDx),
                  dy: useEnabled(this.enableAlertDialogParamOffsetDy, this.alertDialogParamOffsetDy)
                },
                gridCount: useEnabled(this.enableAlertDialogParamGridCount, this.alertDialogParamGridCount),
                isModal: useEnabled(this.enableAlertDialogParamIsModal, this.alertDialogParamIsModal),
                backgroundColor: useEnabled(this.enableAlertDialogParamBackgroundColor,
                  this.alertDialogParamBackgroundColor),
                backgroundBlurStyle: useEnabled(this.enableAlertDialogParamBackgroundBlurStyle,
                  this.alertDialogParamBackgroundBlurStyle),
                cornerRadius: {
                  topLeft: useEnabled(this.enableAlertDialogParamCornerRadiusTopLeft,
                    this.alertDialogParamCornerRadiusTopLeft),
                  topRight: useEnabled(this.enableAlertDialogParamCornerRadiusTopRight,
                    this.alertDialogParamCornerRadiusTopRight),
                  bottomLeft: useEnabled(this.enableAlertDialogParamCornerRadiusBottomLeft,
                    this.alertDialogParamCornerRadiusBottomLeft),
                  bottomRight: useEnabled(this.enableAlertDialogParamCornerRadiusBottomRight,
                    this.alertDialogParamCornerRadiusBottomRight)
                },
                textStyle: {
                  wordBreak: useEnabled(this.enableAlertDialogParamTextStyleWordBreak,
                    this.alertDialogParamTextStyleWordBreak)
                },
                shadow: useEnabled(this.enableAlertDialogParamShadow, this.alertDialogParamShadow),
                borderWidth: useEnabled(this.enableAlertDialogParamBorderWidth, this.alertDialogParamBorderWidth),
                borderStyle: useEnabled(this.enableAlertDialogParamBorderStyle, this.alertDialogParamBorderStyle),
                borderColor: useEnabled(this.enableAlertDialogParamBorderColor, this.alertDialogParamBorderColor),
                width: useEnabled(this.enableAlertDialogParamWidth, this.alertDialogParamWidth),
                height: useEnabled(this.enableAlertDialogParamHeight, this.alertDialogParamHeight),
                showInSubWindow: useEnabled(this.enableAlertDialogParamShowInSubWindow,
                  this.alertDialogParamShowInSubWindow),
                maskRect: {
                  x: useEnabled(this.enableAlertDialogParamMaskRectX, this.alertDialogParamMaskRectX),
                  y: useEnabled(this.enableAlertDialogParamMaskRectY, this.alertDialogParamMaskRectY),
                  width: useEnabled(this.enableAlertDialogParamMaskRectWidth, this.alertDialogParamMaskRectWidth),
                  height: useEnabled(this.enableAlertDialogParamMaskRectHeight, this.alertDialogParamMaskRectHeight)
                },
                buttons: [{
                  value: '按钮',
                  action: () => {
                    console.info('Callback when button1 is clicked')
                  }
                },
                  {
                    value: '按钮',
                    action: () => {
                      console.info('Callback when button2 is clicked')
                    }
                  },
                  {
                    value: '按钮',
                    enabled: useEnabled(this.enableAlertDialogParamButtonsEnabled, this.alertDialogParamButtonsEnabled),
                    defaultFocus: useEnabled(this.enableAlertDialogParamButtonsDefaultFocus,
                      this.alertDialogParamButtonsDefaultFocus),
                    style: useEnabled(this.enableAlertDialogParamButtonsStyle, this.alertDialogParamButtonsStyle),
                    fontColor: useEnabled(this.enableAlertDialogParamButtonsFontColor,
                      this.alertDialogParamButtonsFontColor),
                    backgroundColor: useEnabled(this.enableAlertDialogParamButtonsBackgroundColor,
                      this.alertDialogParamButtonsBackgroundColor),
                    action: () => {
                      console.info('Callback when button3 is clicked')
                    }
                  }],
                buttonDirection: useEnabled(this.enableAlertDialogParamButtonDirection,
                  this.alertDialogParamButtonDirection),
                cancel: () => {
                  console.info('Closed callbacks')
                },
                onWillDismiss: (dismissDialogAction: DismissDialogAction) => {
                  console.info('reason=' + JSON.stringify(dismissDialogAction.reason))
                  console.log('dialog onWillDismiss')
                  if (dismissDialogAction.reason === DismissReason.PRESS_BACK) {
                    dismissDialogAction.dismiss()
                  }
                  if (dismissDialogAction.reason === DismissReason.TOUCH_OUTSIDE) {
                    dismissDialogAction.dismiss()
                  }
                }
              }
            )
            this.oneButton = false;
            this.twoButton = false;
            this.threeButton = true;
          })
          .backgroundColor(0x317aff)
      }

    }
    .width('100%')
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
        RadioBlock({
          title: 'autoCancel',
          isEnabled: $enableAlertDialogParamAutoCancel,
          value: $alertDialogParamAutoCancel,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        RadioBlock({
          title: 'alignment',
          isEnabled: $enableAlertDialogParamAlignment,
          value: $alertDialogParamAlignment,
          dataSource: [
            { label: 'Default', value: DialogAlignment.Default },
            { label: 'Top', value: DialogAlignment.Top },
            { label: 'Center', value: DialogAlignment.Center },
            { label: 'Bottom', value: DialogAlignment.Bottom },
            { label: 'TopStart', value: DialogAlignment.TopStart },
            { label: 'TopEnd', value: DialogAlignment.TopEnd },
            { label: 'CenterStart', value: DialogAlignment.CenterStart },
            { label: 'BottomStart', value: DialogAlignment.BottomStart },
            { label: 'BottomEnd', value: DialogAlignment.BottomEnd },
            { label: 'CenterEnd', value: DialogAlignment.CenterEnd }
          ]
        })

        SliderBlock({
          title: 'offset.dx',
          isEnabled: $enableAlertDialogParamOffsetDx,
          value: $alertDialogParamOffsetDx,
          min: 0,
          max: 16
        })

        SliderBlock({
          title: 'offset.dy',
          isEnabled: $enableAlertDialogParamOffsetDy,
          value: $alertDialogParamOffsetDy,
          min: 0,
          max: 16
        })

        SliderBlock({
          title: 'gridCount',
          isEnabled: $enableAlertDialogParamGridCount,
          value: $alertDialogParamGridCount,
          min: 3,
          max: 12
        })

        RadioBlock({
          title: 'isModal',
          isEnabled: $enableAlertDialogParamIsModal,
          value: $alertDialogParamIsModal,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        ColorBlock({
          title: 'backgroundColor',
          isEnabled: $enableAlertDialogParamBackgroundColor,
          color: $alertDialogParamBackgroundColor,
        })

        RadioBlock({
          title: 'backgroundBlurStyle',
          isEnabled: $enableAlertDialogParamBackgroundBlurStyle,
          value: $alertDialogParamBackgroundBlurStyle,
          dataSource: [
            { label: 'NONE', value: BlurStyle.NONE },
            { label: 'Thin', value: BlurStyle.Thin },
            { label: 'Thick', value: BlurStyle.Thick },
            { label: 'Dark', value: BlurStyle.Regular },
            { label: 'Light', value: BlurStyle.BACKGROUND_THIN },
            { label: 'ExtraLight', value: BlurStyle.BACKGROUND_THICK },
            { label: 'ExtraDark', value: BlurStyle.BACKGROUND_REGULAR },
            { label: 'ExtraExtraLight', value: BlurStyle.BACKGROUND_ULTRA_THICK },
            { label: 'ExtraExtraDark', value: BlurStyle.COMPONENT_ULTRA_THIN },
            { label: 'ExtraThick', value: BlurStyle.COMPONENT_THIN },
            { label: 'ExtraThin', value: BlurStyle.COMPONENT_THICK },
            { label: 'ExtraRegular', value: BlurStyle.COMPONENT_REGULAR },
            { label: 'ExtraSemiThin', value: BlurStyle.COMPONENT_ULTRA_THICK },
          ]
        })

        SliderBlock({
          title: 'cornerRadius.topLeft',
          isEnabled: $enableAlertDialogParamCornerRadiusTopLeft,
          value: $alertDialogParamCornerRadiusTopLeft,
          min: 28,
          max: 48
        })

        SliderBlock({
          title: 'cornerRadius.topRight',
          isEnabled: $enableAlertDialogParamCornerRadiusTopRight,
          value: $alertDialogParamCornerRadiusTopRight,
          min: 28,
          max: 48
        })

        SliderBlock({
          title: 'cornerRadius.bottomLeft',
          isEnabled: $enableAlertDialogParamCornerRadiusBottomLeft,
          value: $alertDialogParamCornerRadiusBottomLeft,
          min: 28,
          max: 48
        })

        SliderBlock({
          title: 'cornerRadius.bottomRight',
          isEnabled: $enableAlertDialogParamCornerRadiusBottomRight,
          value: $alertDialogParamCornerRadiusBottomRight,
          min: 28,
          max: 48
        })

        RadioBlock({
          title: 'textStyle.wordBreak',
          isEnabled: $enableAlertDialogParamTextStyleWordBreak,
          value: $alertDialogParamTextStyleWordBreak,
          dataSource: [
            { label: 'NORMAL', value: WordBreak.NORMAL },
            { label: 'BREAK_ALL', value: WordBreak.BREAK_ALL },
            { label: 'BREAK_WORD', value: WordBreak.BREAK_WORD },
          ]
        })

        RadioBlock({
          title: 'shadow',
          isEnabled: $enableAlertDialogParamShadow,
          value: $alertDialogParamShadow,
          dataSource: [
            { label: 'OUTER_FLOATING_MD', value: ShadowStyle.OUTER_FLOATING_MD },
            { label: 'OUTER_DEFAULT_XS', value: ShadowStyle.OUTER_DEFAULT_XS },
            { label: 'OUTER_DEFAULT_SM', value: ShadowStyle.OUTER_DEFAULT_SM },
            { label: 'OUTER_DEFAULT_MD', value: ShadowStyle.OUTER_DEFAULT_MD },
            { label: 'OUTER_DEFAULT_LG', value: ShadowStyle.OUTER_DEFAULT_LG },
            { label: 'OUTER_FLOATING_SM', value: ShadowStyle.OUTER_FLOATING_SM },
          ]
        })

        SliderBlock({
          title: 'borderWidth',
          isEnabled: $enableAlertDialogParamBorderWidth,
          value: $alertDialogParamBorderWidth,
          min: 0,
          max: 6
        })

        ColorBlock({
          title: 'borderColor',
          isEnabled: $enableAlertDialogParamBorderColor,
          color: $alertDialogParamBorderColor,
        })

        RadioBlock({
          title: 'borderStyle',
          isEnabled: $enableAlertDialogParamBorderStyle,
          value: $alertDialogParamBorderStyle,
          dataSource: [
            { label: 'Dotted', value: BorderStyle.Dotted },
            { label: 'Dashed', value: BorderStyle.Dashed },
            { label: 'Solid', value: BorderStyle.Solid },
          ]
        })

        SliderBlock({
          title: 'width',
          isEnabled: $enableAlertDialogParamWidth,
          value: $alertDialogParamWidth,
          min: 300,
          max: 400
        })

        SliderBlock({
          title: 'height',
          isEnabled: $enableAlertDialogParamHeight,
          value: $alertDialogParamHeight,
          min: 400,
          max: 500
        })

        RadioBlock({
          title: 'showInSubWindow',
          isEnabled: $enableAlertDialogParamShowInSubWindow,
          value: $alertDialogParamShowInSubWindow,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false },
          ]
        })

        SliderBlock({
          title: 'maskRect.x',
          isEnabled: $enableAlertDialogParamMaskRectX,
          value: $alertDialogParamMaskRectX,
          min: 0,
          max: 100
        })

        SliderBlock({
          title: 'maskRect.y',
          isEnabled: $enableAlertDialogParamMaskRectY,
          value: $alertDialogParamMaskRectY,
          min: 0,
          max: 100
        })

        RadioBlock({
          title: 'maskRect.width',
          isEnabled: $enableAlertDialogParamMaskRectWidth,
          value: $alertDialogParamMaskRectWidth,
          dataSource: [
            { label: '50%', value: '50%' },
            { label: '80%', value: '80%' },
            { label: '100%', value: '100%' },
          ]
        })

        RadioBlock({
          title: 'maskRect.height',
          isEnabled: $enableAlertDialogParamMaskRectHeight,
          value: $alertDialogParamMaskRectHeight,
          dataSource: [
            { label: '50%', value: '50%' },
            { label: '80%', value: '80%' },
            { label: '100%', value: '100%' },
          ]
        })

        RadioBlock({
          title: 'oneButton',
          isEnabled: $oneButton,
          value: $oneButton,
        })

        if (this.oneButton) {
          RadioBlock({
            title: 'confirm.enabled',
            isEnabled: $enableAlertDialogParamConfirmEnabled,
            value: $alertDialogParamConfirmEnabled,
            dataSource: [
              { label: 'true', value: true },
              { label: 'false', value: false },
            ]
          })

          RadioBlock({
            title: 'confirm.defaultFocus',
            isEnabled: $enableAlertDialogParamConfirmDefaultFocus,
            value: $alertDialogParamConfirmDefaultFocus,
            dataSource: [
              { label: 'true', value: true },
              { label: 'false', value: false },
            ]
          })

          RadioBlock({
            title: 'confirm.style',
            isEnabled: $enableAlertDialogParamConfirmStyle,
            value: $alertDialogParamConfirmStyle,
            dataSource: [
              { label: 'DEFAULT', value: DialogButtonStyle.DEFAULT },
              { label: 'HIGHLIGHT', value: DialogButtonStyle.HIGHLIGHT },
            ]
          })

          ColorBlock({
            title: 'confirm.fontColor',
            isEnabled: $enableAlertDialogParamConfirmFontColor,
            color: $alertDialogParamConfirmFontColor,
          })

          ColorBlock({
            title: 'confirm.backgroundColor',
            isEnabled: $enableAlertDialogParamConfirmBackgroundColor,
            color: $alertDialogParamConfirmBackgroundColor,
          })
        }

        RadioBlock({
          title: 'twoButton',
          isEnabled: $twoButton,
          value: $twoButton,
        })

        if (this.twoButton) {
          RadioBlock({
            title: 'primaryButton.enabled',
            isEnabled: $enableAlertDialogParamPrimaryButtonEnabled,
            value: $alertDialogParamPrimaryButtonEnabled,
            dataSource: [
              { label: 'true', value: true },
              { label: 'false', value: false },
            ]
          })

          RadioBlock({
            title: 'primaryButton.defaultFocus',
            isEnabled: $enableAlertDialogParamPrimaryButtonDefaultFocus,
            value: $alertDialogParamPrimaryButtonDefaultFocus,
            dataSource: [
              { label: 'true', value: true },
              { label: 'false', value: false },
            ]
          })

          RadioBlock({
            title: 'primaryButton.style',
            isEnabled: $enableAlertDialogParamPrimaryButtonStyle,
            value: $alertDialogParamPrimaryButtonStyle,
            dataSource: [
              { label: 'DEFAULT', value: DialogButtonStyle.DEFAULT },
              { label: 'HIGHLIGHT', value: DialogButtonStyle.HIGHLIGHT },
            ]
          })

          ColorBlock({
            title: 'primaryButton.fontColor',
            isEnabled: $enableAlertDialogParamPrimaryButtonFontColor,
            color: $alertDialogParamPrimaryButtonFontColor,
          })

          ColorBlock({
            title: 'primaryButton.backgroundColor',
            isEnabled: $enableAlertDialogParamPrimaryButtonBackgroundColor,
            color: $alertDialogParamPrimaryButtonBackgroundColor,
          })

          RadioBlock({
            title: 'secondaryButton.enabled',
            isEnabled: $enableAlertDialogParamSecondaryButtonEnabled,
            value: $alertDialogParamSecondaryButtonEnabled,
            dataSource: [
              { label: 'true', value: true },
              { label: 'false', value: false },
            ]
          })

          RadioBlock({
            title: 'secondaryButton.defaultFocus',
            isEnabled: $enableAlertDialogParamSecondaryButtonDefaultFocus,
            value: $alertDialogParamSecondaryButtonDefaultFocus,
            dataSource: [
              { label: 'true', value: true },
              { label: 'false', value: false },
            ]
          })

          RadioBlock({
            title: 'secondaryButton.style',
            isEnabled: $enableAlertDialogParamSecondaryButtonStyle,
            value: $alertDialogParamSecondaryButtonStyle,
            dataSource: [
              { label: 'DEFAULT', value: DialogButtonStyle.DEFAULT },
              { label: 'HIGHLIGHT', value: DialogButtonStyle.HIGHLIGHT },
            ]
          })

          ColorBlock({
            title: 'secondaryButton.fontColor',
            isEnabled: $enableAlertDialogParamSecondaryButtonFontColor,
            color: $alertDialogParamSecondaryButtonFontColor,
          })

          ColorBlock({
            title: 'secondaryButton.backgroundColor',
            isEnabled: $enableAlertDialogParamSecondaryButtonBackgroundColor,
            color: $alertDialogParamSecondaryButtonBackgroundColor,
          })
        }

        RadioBlock({
          title: 'threeButton',
          isEnabled: $threeButton,
          value: $threeButton,
        })

        if (this.threeButton) {
          RadioBlock({
            title: 'buttons.enabled',
            isEnabled: $enableAlertDialogParamButtonsEnabled,
            value: $alertDialogParamButtonsEnabled,
            dataSource: [
              { label: 'true', value: true },
              { label: 'false', value: false },
            ]
          })

          RadioBlock({
            title: 'buttons.defaultFocus',
            isEnabled: $enableAlertDialogParamButtonsDefaultFocus,
            value: $alertDialogParamButtonsDefaultFocus,
            dataSource: [
              { label: 'true', value: true },
              { label: 'false', value: false },
            ]
          })

          RadioBlock({
            title: 'buttons.style',
            isEnabled: $enableAlertDialogParamButtonsStyle,
            value: $alertDialogParamButtonsStyle,
            dataSource: [
              { label: 'DEFAULT', value: DialogButtonStyle.DEFAULT },
              { label: 'HIGHLIGHT', value: DialogButtonStyle.HIGHLIGHT },
            ]
          })

          ColorBlock({
            title: 'buttons.fontColor',
            isEnabled: $enableAlertDialogParamButtonsFontColor,
            color: $alertDialogParamButtonsFontColor,
          })

          ColorBlock({
            title: 'buttons.backgroundColor',
            isEnabled: $enableAlertDialogParamButtonsBackgroundColor,
            color: $alertDialogParamButtonsBackgroundColor,
          })
        }

        RadioBlock({
          title: 'buttonDirection',
          isEnabled: $enableAlertDialogParamButtonDirection,
          value: $alertDialogParamButtonDirection,
          dataSource: [
            { label: 'AUTO', value: DialogButtonDirection.AUTO },
            { label: 'HIGHLIGHT', value: DialogButtonDirection.HORIZONTAL },
            { label: 'VERTICAL', value: DialogButtonDirection.VERTICAL },
          ]
        })
      }.width('100%')
    }
    .height('52%')
  }
}