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
import { ColorBlock, Drawer, IconBlock, RadioBlock, SliderBlock, useEnabled } from 'common'

@Entry
@Component
export struct ActionSheetBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State actionSheetOptionsAutoCancel: boolean = true;
  @State enableActionSheetOptionsAutoCancel: boolean = false;
  @State actionSheetOptionsAlignment: DialogAlignment = DialogAlignment.Default;
  @State enableActionSheetOptionsAlignment: boolean = false;
  @State actionSheetOptionsOffsetDx: number = 0;
  @State enableActionSheetOptionsOffsetDx: boolean = false;
  @State actionSheetOptionsOffsetDy: number = 0;
  @State enableActionSheetOptionsOffsetDy: boolean = false;
  @State actionSheetOptionsShowInSubWindow: boolean = false;
  @State enableActionSheetOptionsShowInSubWindow: boolean = false;
  @State actionSheetOptionsIsModal: boolean = true;
  @State enableActionSheetOptionsIsModal: boolean = false;
  @State actionSheetOptionsBackgroundColor: Color = Color.Transparent;
  @State enableActionSheetOptionsBackgroundColor: boolean = false;
  @State actionSheetOptionsBackgroundBlurStyle: BlurStyle = BlurStyle.COMPONENT_ULTRA_THICK;
  @State enableActionSheetOptionsBackgroundBlurStyle: boolean = false;
  @State actionSheetOptionsConfirmEnabled: boolean = true;
  @State enableActionSheetOptionsConfirmEnabled: boolean = false;
  @State actionSheetOptionsConfirmDefaultFocus: boolean = false;
  @State enableActionSheetOptionsConfirmDefaultFocus: boolean = false;
  @State actionSheetOptionsConfirmStyle: DialogButtonStyle = DialogButtonStyle.DEFAULT;
  @State enableActionSheetOptionsConfirmStyle: boolean = false;
  @State actionSheetOptionsWidth: number = 400;
  @State enableActionSheetOptionsWidth: boolean = false;
  @State actionSheetOptionsHeight: number = 400;
  @State enableActionSheetOptionsHeight: boolean = false;
  @State actionSheetOptionsMaskRectX: number = 0;
  @State enableActionSheetOptionsMaskRectX: boolean = false;
  @State actionSheetOptionsMaskRectY: number = 0;
  @State enableActionSheetOptionsMaskRectY: boolean = false;
  @State actionSheetOptionsMaskRectWidth: string = '100%';
  @State enableActionSheetOptionsMaskRectWidth: boolean = false;
  @State actionSheetOptionsMaskRectHeight: string = '100%';
  @State enableActionSheetOptionsMaskRectHeight: boolean = false;
  @State actionSheetOptionsCornerRadiusTopLeft: number = 32;
  @State enableActionSheetOptionsCornerRadiusTopLeft: boolean = false;
  @State actionSheetOptionsCornerRadiusTopRight: number = 32;
  @State enableActionSheetOptionsCornerRadiusTopRight: boolean = false;
  @State actionSheetOptionsCornerRadiusBottomLeft: number = 32;
  @State enableActionSheetOptionsCornerRadiusBottomLeft: boolean = false;
  @State actionSheetOptionsCornerRadiusBottomRight: number = 32;
  @State enableActionSheetOptionsCornerRadiusBottomRight: boolean = false;
  @State actionSheetOptionsShadow: ShadowStyle = ShadowStyle.OUTER_FLOATING_MD;
  @State enableActionSheetOptionsShadow: boolean = false;
  @State actionSheetOptionsBorderWidth: number = 0;
  @State enableActionSheetOptionsBorderWidth: boolean = false;
  @State actionSheetOptionsBorderColor: Color = Color.Black;
  @State enableActionSheetOptionsBorderColor: boolean = false;
  @State actionSheetOptionsBorderStyle: BorderStyle = BorderStyle.Solid;
  @State enableActionSheetOptionsBorderStyle: boolean = false;
  @State duration: number = 500;
  @State enableDuration: boolean = false;
  @State scaleX: number = 1;
  @State enableScaleX: boolean = false;
  @State scaleY: number = 1;
  @State enableScaleY: boolean = false;
  @State curve: Curve = Curve.Sharp;
  @State enableCurve: boolean = false;
  @State sheetsIcon: Resource = $r('sys.media.ohos_ic_public_device_phone');
  @State enableSheetsIcon: boolean = false;
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
      Button('ActionSheet Set Duration')
        .onClick(() => {
          ActionSheet.show({
            title: 'ActionSheet 1',
            message: 'Set Animation Duration open 3 second, close 100 ms',
            autoCancel: useEnabled(this.enableActionSheetOptionsAutoCancel, this.actionSheetOptionsAutoCancel),
            subtitle: 'Subtitle',
            alignment: useEnabled(this.enableActionSheetOptionsAlignment, this.actionSheetOptionsAlignment),
            transition: TransitionEffect.asymmetric(TransitionEffect.prototype.animation({
              duration: useEnabled(this.enableDuration, this.duration),
              curve: useEnabled(this.enableCurve, this.curve),
            })
              .combine(TransitionEffect.scale({
                x: useEnabled(this.enableScaleX, this.scaleX),
                y: useEnabled(this.enableScaleY, this.scaleY)
              })
                .animation({
                  duration: useEnabled(this.enableDuration, this.duration),
                  curve: useEnabled(this.enableCurve, this.curve)
                })),
              TransitionEffect.OPACITY.animation({ duration: 100, curve: Curve.Smooth })
                .combine(TransitionEffect.scale({ x: 0.5, y: 0.5 }).animation({ duration: 100, curve: Curve.Smooth }))),
            offset: {
              dx: useEnabled(this.enableActionSheetOptionsOffsetDx, this.actionSheetOptionsOffsetDx),
              dy: useEnabled(this.enableActionSheetOptionsOffsetDy, this.actionSheetOptionsOffsetDy)
            },
            confirm: {
              value: 'button',
              enabled: useEnabled(this.enableActionSheetOptionsConfirmEnabled, this.actionSheetOptionsConfirmEnabled),
              defaultFocus: useEnabled(this.enableActionSheetOptionsConfirmDefaultFocus,
                this.actionSheetOptionsConfirmDefaultFocus),
              style: useEnabled(this.enableActionSheetOptionsConfirmStyle, this.actionSheetOptionsConfirmStyle),
              action: () => {
                console.info('Button-clicking callback')
              }
            },
            isModal: useEnabled(this.enableActionSheetOptionsIsModal, this.actionSheetOptionsIsModal),
            backgroundColor: useEnabled(this.enableActionSheetOptionsBackgroundColor,
              this.actionSheetOptionsBackgroundColor),
            backgroundBlurStyle: useEnabled(this.enableActionSheetOptionsBackgroundBlurStyle,
              this.actionSheetOptionsBackgroundBlurStyle),
            cancel: () => {
              console.info('Closed callbacks')
            },
            sheets: [
              {
                title: 'apples',
                icon: useEnabled(this.enableSheetsIcon, this.sheetsIcon),
                action: () => {
                  console.log('apples')
                }
              },
              {
                title: 'bananas',
                icon: useEnabled(this.enableSheetsIcon, this.sheetsIcon),
                action: () => {
                  console.log('bananas')
                }
              },
              {
                title: 'pears',
                icon: useEnabled(this.enableSheetsIcon, this.sheetsIcon),
                action: () => {
                  console.log('pears')
                }
              },
            ],
            cornerRadius: {
              topLeft: useEnabled(this.enableActionSheetOptionsCornerRadiusTopLeft,
                this.actionSheetOptionsCornerRadiusTopLeft),
              topRight: useEnabled(this.enableActionSheetOptionsCornerRadiusTopRight,
                this.actionSheetOptionsCornerRadiusTopRight),
              bottomLeft: useEnabled(this.enableActionSheetOptionsCornerRadiusBottomLeft,
                this.actionSheetOptionsCornerRadiusBottomLeft),
              bottomRight: useEnabled(this.enableActionSheetOptionsCornerRadiusBottomRight,
                this.actionSheetOptionsCornerRadiusBottomRight)
            },
            borderWidth: useEnabled(this.enableActionSheetOptionsBorderWidth, this.actionSheetOptionsBorderWidth),
            borderColor: useEnabled(this.enableActionSheetOptionsBorderColor, this.actionSheetOptionsBorderColor),
            borderStyle: useEnabled(this.enableActionSheetOptionsBorderStyle, this.actionSheetOptionsBorderStyle),
            width: useEnabled(this.enableActionSheetOptionsWidth, this.actionSheetOptionsWidth),
            height: useEnabled(this.enableActionSheetOptionsHeight, this.actionSheetOptionsHeight),
            shadow: useEnabled(this.enableActionSheetOptionsShadow, this.actionSheetOptionsShadow),
            maskRect: {
              x: useEnabled(this.enableActionSheetOptionsMaskRectX, this.actionSheetOptionsMaskRectX),
              y: useEnabled(this.enableActionSheetOptionsMaskRectY, this.actionSheetOptionsMaskRectY),
              width: useEnabled(this.enableActionSheetOptionsMaskRectWidth, this.actionSheetOptionsMaskRectWidth),
              height: useEnabled(this.enableActionSheetOptionsMaskRectHeight, this.actionSheetOptionsMaskRectHeight)
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
          })
        }).backgroundColor(0x317aff)
    }
    .width('100%')
  }

  @Builder
  Parameters() {
    Scroll(this.scroller) {
      Column({ space: 8 }) {
        RadioBlock({
          title: 'autoCancel',
          isEnabled: $enableActionSheetOptionsAutoCancel,
          value: $actionSheetOptionsAutoCancel,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        RadioBlock({
          title: 'alignment',
          isEnabled: $enableActionSheetOptionsAlignment,
          value: $actionSheetOptionsAlignment,
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
          isEnabled: $enableActionSheetOptionsOffsetDx,
          value: $actionSheetOptionsOffsetDx,
          min: 0,
          max: 16
        })

        SliderBlock({
          title: 'offset.dy',
          isEnabled: $enableActionSheetOptionsOffsetDy,
          value: $actionSheetOptionsOffsetDy,
          min: 0,
          max: 16
        })

        RadioBlock({
          title: 'isModal',
          isEnabled: $enableActionSheetOptionsIsModal,
          value: $actionSheetOptionsIsModal,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        ColorBlock({
          title: 'backgroundColor',
          isEnabled: $enableActionSheetOptionsBackgroundColor,
          color: $actionSheetOptionsBackgroundColor,
        })

        RadioBlock({
          title: 'backgroundBlurStyle',
          isEnabled: $enableActionSheetOptionsBackgroundBlurStyle,
          value: $actionSheetOptionsBackgroundBlurStyle,
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
          isEnabled: $enableActionSheetOptionsCornerRadiusTopLeft,
          value: $actionSheetOptionsCornerRadiusTopLeft,
          min: 28,
          max: 48
        })

        SliderBlock({
          title: 'cornerRadius.topRight',
          isEnabled: $enableActionSheetOptionsCornerRadiusTopRight,
          value: $actionSheetOptionsCornerRadiusTopRight,
          min: 28,
          max: 48
        })

        SliderBlock({
          title: 'cornerRadius.bottomLeft',
          isEnabled: $enableActionSheetOptionsCornerRadiusBottomLeft,
          value: $actionSheetOptionsCornerRadiusBottomLeft,
          min: 28,
          max: 48
        })

        SliderBlock({
          title: 'cornerRadius.bottomRight',
          isEnabled: $enableActionSheetOptionsCornerRadiusBottomRight,
          value: $actionSheetOptionsCornerRadiusBottomRight,
          min: 28,
          max: 48
        })

        RadioBlock({
          title: 'shadow',
          isEnabled: $enableActionSheetOptionsShadow,
          value: $actionSheetOptionsShadow,
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
          isEnabled: $enableActionSheetOptionsBorderWidth,
          value: $actionSheetOptionsBorderWidth,
          min: 0,
          max: 6
        })

        ColorBlock({
          title: 'borderColor',
          isEnabled: $enableActionSheetOptionsBorderColor,
          color: $actionSheetOptionsBorderColor,
        })

        RadioBlock({
          title: 'borderStyle',
          isEnabled: $enableActionSheetOptionsBorderStyle,
          value: $actionSheetOptionsBorderStyle,
          dataSource: [
            { label: 'Dotted', value: BorderStyle.Dotted },
            { label: 'Dashed', value: BorderStyle.Dashed },
            { label: 'Solid', value: BorderStyle.Solid },
          ]
        })

        SliderBlock({
          title: 'width',
          isEnabled: $enableActionSheetOptionsWidth,
          value: $actionSheetOptionsWidth,
          min: 300,
          max: 400
        })

        SliderBlock({
          title: 'height',
          isEnabled: $enableActionSheetOptionsHeight,
          value: $actionSheetOptionsHeight,
          min: 400,
          max: 500
        })

        RadioBlock({
          title: 'showInSubWindow',
          isEnabled: $enableActionSheetOptionsShowInSubWindow,
          value: $actionSheetOptionsShowInSubWindow,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false },
          ]
        })

        SliderBlock({
          title: 'maskRect.x',
          isEnabled: $enableActionSheetOptionsMaskRectX,
          value: $actionSheetOptionsMaskRectX,
          min: 0,
          max: 100
        })

        SliderBlock({
          title: 'maskRect.y',
          isEnabled: $enableActionSheetOptionsMaskRectY,
          value: $actionSheetOptionsMaskRectY,
          min: 0,
          max: 100
        })

        RadioBlock({
          title: 'maskRect.width',
          isEnabled: $enableActionSheetOptionsMaskRectWidth,
          value: $actionSheetOptionsMaskRectWidth,
          dataSource: [
            { label: '50%', value: '50%' },
            { label: '80%', value: '80%' },
            { label: '100%', value: '100%' },
          ]
        })

        RadioBlock({
          title: 'maskRect.height',
          isEnabled: $enableActionSheetOptionsMaskRectHeight,
          value: $actionSheetOptionsMaskRectHeight,
          dataSource: [
            { label: '50%', value: '50%' },
            { label: '80%', value: '80%' },
            { label: '100%', value: '100%' },
          ]
        })

        RadioBlock({
          title: 'confirm.enabled',
          isEnabled: $enableActionSheetOptionsConfirmEnabled,
          value: $actionSheetOptionsConfirmEnabled,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false },
          ]
        })

        RadioBlock({
          title: 'confirm.defaultFocus',
          isEnabled: $enableActionSheetOptionsConfirmDefaultFocus,
          value: $actionSheetOptionsConfirmDefaultFocus,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false },
          ]
        })

        RadioBlock({
          title: 'confirm.style',
          isEnabled: $enableActionSheetOptionsConfirmStyle,
          value: $actionSheetOptionsConfirmStyle,
          dataSource: [
            { label: 'DEFAULT', value: DialogButtonStyle.DEFAULT },
            { label: 'HIGHLIGHT', value: DialogButtonStyle.HIGHLIGHT },
          ]
        })

        SliderBlock({
          title: 'duration',
          isEnabled: $enableDuration,
          value: $duration,
          step: 1,
          min: 200,
          max: 800
        })

        RadioBlock({
          title: 'curve',
          isEnabled: $enableCurve,
          value: $curve,
          dataSource: [
            { label: 'Linear', value: Curve.Linear },
            { label: 'Ease', value: Curve.Ease },
            { label: 'EaseIn', value: Curve.EaseIn },
            { label: 'EaseOut', value: Curve.EaseOut },
            { label: 'EaseInOut', value: Curve.EaseInOut },
            { label: 'FastOutSlowIn', value: Curve.FastOutSlowIn },
            { label: 'LinearOutSlowIn', value: Curve.LinearOutSlowIn },
            { label: 'FastOutLinearIn', value: Curve.FastOutLinearIn },
            { label: 'ExtremeDeceleration', value: Curve.ExtremeDeceleration },
            { label: 'Sharp', value: Curve.Sharp },
            { label: 'Rhythm', value: Curve.Rhythm },
            { label: 'Smooth', value: Curve.Smooth },
            { label: 'Friction', value: Curve.Friction },
          ]
        })

        SliderBlock({
          title: 'scale.x',
          isEnabled: $enableScaleX,
          value: $scaleX,
          step: 0.1,
          min: 1,
          max: 1.5
        })

        SliderBlock({
          title: 'scale.y',
          isEnabled: $enableScaleY,
          value: $scaleY,
          step: 0.1,
          min: 1,
          max: 1.5
        })

        IconBlock({
          title: 'SuffixIcon',
          isEnabled: $enableSheetsIcon,
          icon: $sheetsIcon,
        })
      }.width('100%')
    }
    .height('52%')
    .id('scroll')
  }

  @Builder
  Generic() {

  }
}