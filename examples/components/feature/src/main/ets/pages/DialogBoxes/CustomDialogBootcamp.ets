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
import {
  ColorBlock,
  Drawer,
  IconBlock,
  RadioBlock,
  SliderBlock,
  useEnabled,
  useEnabledBase,
  useEnabledNumber
} from 'common'
import { KeyboardAvoidMode } from '@ohos.arkui.UIContext'

@CustomDialog
struct CustomDialogExample {
  controller?: CustomDialogController
  cancel: () => void = () => {
  }
  confirm: () => void = () => {
  }

  build() {
    Column() {
      Text('这是自定义弹窗')
        .fontSize(30)
        .height(100)
      Button('点我关闭弹窗')
        .onClick(() => {
          if (this.controller != undefined) {
            this.controller.close()
          }
        })
        .margin(20)
    }
  }
}


@Entry
@Component
export struct CustomDialogBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State customDialogControllerOptionsAutoCancel: boolean = true;
  @State enableCustomDialogControllerOptionsAutoCancel: boolean = false;
  @State customDialogControllerOptionsAlignment: DialogAlignment = DialogAlignment.Default;
  @State enableCustomDialogControllerOptionsAlignment: boolean = false;
  @State customDialogControllerOptionsOffsetDx: Length = 0;
  @State enableCustomDialogControllerOptionsOffsetDx: boolean = false;
  @State customDialogControllerOptionsOffsetDy: Length = 0;
  @State enableCustomDialogControllerOptionsOffsetDy: boolean = false;
  @State customDialogControllerOptionsIsModal: boolean = true;
  @State enableCustomDialogControllerOptionsIsModal: boolean = false;
  @State customDialogControllerOptionsBackgroundColor: Color = Color.Transparent;
  @State enableCustomDialogControllerOptionsBackgroundColor: boolean = false;
  @State customDialogControllerOptionsBackgroundBlurStyle: BlurStyle = BlurStyle.COMPONENT_ULTRA_THICK;
  @State enableCustomDialogControllerOptionsBackgroundBlurStyle: boolean = false;
  @State customDialogControllerOptionsWidth: number = 400;
  @State enableCustomDialogControllerOptionsWidth: boolean = false;
  @State customDialogControllerOptionsHeight: number = 400;
  @State enableCustomDialogControllerOptionsHeight: boolean = false;
  @State customDialogControllerOptionsMaskRectX: number = 0;
  @State enableCustomDialogControllerOptionsMaskRectX: boolean = false;
  @State customDialogControllerOptionsMaskRectY: number = 0;
  @State enableCustomDialogControllerOptionsMaskRectY: boolean = false;
  @State customDialogControllerOptionsMaskRectWidth: string = '100%';
  @State enableCustomDialogControllerOptionsMaskRectWidth: boolean = false;
  @State customDialogControllerOptionsMaskRectHeight: string = '100%';
  @State enableCustomDialogControllerOptionsMaskRectHeight: boolean = false;
  @State customDialogControllerOptionsCornerRadiusTopLeft: number = 32;
  @State enableCustomDialogControllerOptionsCornerRadiusTopLeft: boolean = false;
  @State customDialogControllerOptionsCornerRadiusTopRight: number = 32;
  @State enableCustomDialogControllerOptionsCornerRadiusTopRight: boolean = false;
  @State customDialogControllerOptionsCornerRadiusBottomLeft: number = 32;
  @State enableCustomDialogControllerOptionsCornerRadiusBottomLeft: boolean = false;
  @State customDialogControllerOptionsCornerRadiusBottomRight: number = 32;
  @State enableCustomDialogControllerOptionsCornerRadiusBottomRight: boolean = false;
  @State customDialogControllerOptionsShadow: ShadowStyle = ShadowStyle.OUTER_FLOATING_MD;
  @State enableCustomDialogControllerOptionsShadow: boolean = false;
  @State customDialogControllerOptionsBorderWidth: number = 0;
  @State enableCustomDialogControllerOptionsBorderWidth: boolean = false;
  @State customDialogControllerOptionsBorderColor: Color = Color.Black;
  @State enableCustomDialogControllerOptionsBorderColor: boolean = false;
  @State customDialogControllerOptionsBorderStyle: BorderStyle = BorderStyle.Solid;
  @State enableCustomDialogControllerOptionsBorderStyle: boolean = false;
  @State maskColor: Color = 0x33000000;
  @State enableMaskColor: boolean = false;
  @State customDialogControllerOptionsGridCount: number = 4;
  @State enableCustomDialogControllerOptionsGridCount: boolean = false;
  @State customDialogControllerOptionsCustomStyle: boolean = false;
  @State enableCustomDialogControllerOptionsCustomStyle: boolean = false;
  @State animateParamDuration: number = 1000;
  @State enableAnimateParamDuration: boolean = false;
  @State animateParamTempo: number = 1
  @State enableAnimateParamTempo: boolean = false;
  @State animateParamCurve: Curve = Curve.EaseInOut;
  @State enableAnimateParamCurve: boolean = false;
  @State animateParamDelay: number = 100;
  @State enableAnimateParamDelay: boolean = false;
  @State animateParamIterations: number = 1;
  @State enableAnimateParamIterations: boolean = false;
  @State animateParamPlayMode: PlayMode = PlayMode.Normal;
  @State enableAnimateParamPlayMode: boolean = false;
  @State animateParamFinishCallbackType: FinishCallbackType = FinishCallbackType.REMOVED;
  @State enableAnimateParamFinishCallbackType: boolean = false;
  @State animateParamExpectedFrameRateRangeMin: number = 10;
  @State enableAnimateParamExpectedFrameRateRangeMin: boolean = false;
  @State animateParamExpectedFrameRateRangeMax: number = 120;
  @State enableAnimateParamExpectedFrameRateRangeMax: boolean = false;
  @State animateParamExpectedFrameRateRangeExpected: number = 60;
  @State enableAnimateParamExpectedFrameRateRangeExpected: boolean = false;
  scroller: Scroller = new Scroller();

  aboutToAppear(): void {
    AppStorage.setOrCreate('scroller', this.scroller)
  }

  dialogController: CustomDialogController | null = new CustomDialogController({
    builder: CustomDialogExample({
      cancel: () => {
        this.onCancel()
      },
      confirm: () => {
        this.onAccept()
      }
    }),
    cancel: this.existApp,
    autoCancel: useEnabled(this.enableCustomDialogControllerOptionsAutoCancel,
      this.customDialogControllerOptionsAutoCancel),
    onWillDismiss: (dismissDialogAction: DismissDialogAction) => {
      if (dismissDialogAction.reason == DismissReason.PRESS_BACK) {
        dismissDialogAction.dismiss()
      }
      if (dismissDialogAction.reason == DismissReason.TOUCH_OUTSIDE) {
        dismissDialogAction.dismiss()
      }
    },
    alignment: useEnabled(this.enableCustomDialogControllerOptionsAlignment,
      this.customDialogControllerOptionsAlignment),
    offset: {
      dx: useEnabledBase(this.enableCustomDialogControllerOptionsOffsetDx, this.customDialogControllerOptionsOffsetDx,
        0),
      dy: useEnabledBase(this.enableCustomDialogControllerOptionsOffsetDy, this.customDialogControllerOptionsOffsetDy,
        0)
    },
    customStyle: useEnabled(this.enableCustomDialogControllerOptionsCustomStyle,
      this.customDialogControllerOptionsCustomStyle),
    cornerRadius: {
      topLeft: useEnabled(this.enableCustomDialogControllerOptionsCornerRadiusTopLeft,
        this.customDialogControllerOptionsCornerRadiusTopLeft),
      topRight: useEnabled(this.enableCustomDialogControllerOptionsCornerRadiusTopRight,
        this.customDialogControllerOptionsCornerRadiusTopRight),
      bottomLeft: useEnabled(this.enableCustomDialogControllerOptionsCornerRadiusBottomLeft,
        this.customDialogControllerOptionsCornerRadiusBottomLeft),
      bottomRight: useEnabled(this.enableCustomDialogControllerOptionsCornerRadiusBottomRight,
        this.customDialogControllerOptionsCornerRadiusBottomRight),
    },
    width: useEnabled(this.enableCustomDialogControllerOptionsWidth, this.customDialogControllerOptionsWidth),
    height: useEnabled(this.enableCustomDialogControllerOptionsHeight, this.customDialogControllerOptionsHeight),
    borderWidth: useEnabled(this.enableCustomDialogControllerOptionsBorderWidth,
      this.customDialogControllerOptionsBorderWidth),
    borderStyle: useEnabled(this.enableCustomDialogControllerOptionsBorderStyle,
      this.customDialogControllerOptionsBorderStyle),
    borderColor: useEnabled(this.enableCustomDialogControllerOptionsBorderColor,
      this.customDialogControllerOptionsBorderColor),
    backgroundColor: useEnabled(this.enableCustomDialogControllerOptionsBackgroundColor,
      this.customDialogControllerOptionsBackgroundColor),
    shadow: useEnabled(this.enableCustomDialogControllerOptionsShadow,
      this.customDialogControllerOptionsShadow),
    backgroundBlurStyle: useEnabled(this.enableCustomDialogControllerOptionsBackgroundBlurStyle,
      this.customDialogControllerOptionsBackgroundBlurStyle),
    maskColor: useEnabled(this.enableMaskColor, this.maskColor),
    maskRect: {
      x: useEnabled(this.enableCustomDialogControllerOptionsMaskRectX, this.customDialogControllerOptionsMaskRectX),
      y: useEnabled(this.enableCustomDialogControllerOptionsMaskRectY, this.customDialogControllerOptionsMaskRectY),
      width: useEnabled(this.enableCustomDialogControllerOptionsMaskRectWidth,
        this.customDialogControllerOptionsMaskRectWidth),
      height: useEnabled(this.enableCustomDialogControllerOptionsMaskRectHeight,
        this.customDialogControllerOptionsMaskRectHeight)
    },
    gridCount: useEnabled(this.enableCustomDialogControllerOptionsGridCount,
      this.customDialogControllerOptionsGridCount),
    openAnimation: {
      duration: useEnabled(this.enableAnimateParamDuration, this.animateParamDuration),
      tempo: useEnabled(this.enableAnimateParamTempo, this.animateParamTempo),
      curve: useEnabled(this.enableAnimateParamCurve, this.animateParamCurve),
      delay: useEnabled(this.enableAnimateParamDelay, this.animateParamDelay),
      iterations: useEnabled(this.enableAnimateParamIterations, this.animateParamIterations),
      playMode: useEnabled(this.enableAnimateParamPlayMode, this.animateParamPlayMode),
      finishCallbackType: useEnabled(this.enableAnimateParamFinishCallbackType, this.animateParamFinishCallbackType),
      expectedFrameRateRange: {
        min: useEnabledNumber(this.enableAnimateParamExpectedFrameRateRangeMin,
          this.animateParamExpectedFrameRateRangeMin, 30),
        max: useEnabledNumber(this.enableAnimateParamExpectedFrameRateRangeMax,
          this.animateParamExpectedFrameRateRangeMax, 120),
        expected: useEnabledNumber(this.enableAnimateParamExpectedFrameRateRangeExpected,
          this.animateParamExpectedFrameRateRangeExpected, 60),
      }
    },
    closeAnimation: {
      duration: useEnabled(this.enableAnimateParamDuration, this.animateParamDuration),
      tempo: useEnabled(this.enableAnimateParamTempo, this.animateParamTempo),
      curve: useEnabled(this.enableAnimateParamCurve, this.animateParamCurve),
      delay: useEnabled(this.enableAnimateParamDelay, this.animateParamDelay),
      iterations: useEnabled(this.enableAnimateParamIterations, this.animateParamIterations),
      playMode: useEnabled(this.enableAnimateParamPlayMode, this.animateParamPlayMode),
      finishCallbackType: useEnabled(this.enableAnimateParamFinishCallbackType, this.animateParamFinishCallbackType),
      expectedFrameRateRange: {
        min:
        useEnabledNumber(
          this.enableAnimateParamExpectedFrameRateRangeMin,
          this.animateParamExpectedFrameRateRangeMin, 30),
        max:
        useEnabledNumber(this.enableAnimateParamExpectedFrameRateRangeMax,
          this.animateParamExpectedFrameRateRangeMax, 120),
        expected:
        useEnabledNumber(this.enableAnimateParamExpectedFrameRateRangeExpected,
          this.animateParamExpectedFrameRateRangeExpected, 60),
      }
    },
    isModal: useEnabled(this.enableCustomDialogControllerOptionsIsModal, this.customDialogControllerOptionsIsModal),
  })

  aboutToDisappear() {
    this.dialogController = null
  }

  onCancel() {
    console.info('Callback when the first button is clicked')
  }

  onAccept() {
    console.info('Callback when the second button is clicked')
  }

  existApp() {
    console.info('Click the callback in the blank area')
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
      Button('click me')
        .onClick(() => {
          if (this.dialogController != null) {
            this.dialogController.open()
          }
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
          isEnabled: $enableCustomDialogControllerOptionsAutoCancel,
          value: $customDialogControllerOptionsAutoCancel,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        SliderBlock({
          title: 'duration',
          isEnabled: $enableAnimateParamDuration,
          value: $animateParamDuration,
          step: 500,
          min: 500,
          max: 2000
        })

        SliderBlock({
          title: 'tempo',
          isEnabled: $enableAnimateParamTempo,
          value: $animateParamTempo,
          min: 1,
          max: 5
        })

        SliderBlock({
          title: 'delay',
          isEnabled: $enableAnimateParamDelay,
          value: $animateParamDelay,
          min: 0,
          step: 500,
          max: 2000
        })

        SliderBlock({
          title: 'iterations',
          isEnabled: $enableAnimateParamIterations,
          value: $animateParamIterations,
          min: -1,
          max: 5
        })

        RadioBlock({
          title: 'playMode',
          isEnabled: $enableAnimateParamPlayMode,
          value: $animateParamPlayMode,
          dataSource: [
            { label: 'Normal', value: PlayMode.Normal },
            { label: 'Reverse', value: PlayMode.Reverse },
            { label: 'Alternate', value: PlayMode.Alternate },
            { label: 'AlternateReverse', value: PlayMode.AlternateReverse },
          ]
        })

        RadioBlock({
          title: 'finishCallbackType',
          isEnabled: $enableAnimateParamFinishCallbackType,
          value: $animateParamFinishCallbackType,
          dataSource: [
            { label: 'REMOVED', value: FinishCallbackType.REMOVED },
            { label: 'LOGICALLY', value: FinishCallbackType.LOGICALLY }
          ]
        })

        SliderBlock({
          title: 'expectedFrameRateRange.min',
          isEnabled: $enableAnimateParamExpectedFrameRateRangeMin,
          value: $animateParamExpectedFrameRateRangeMin,
          min: 10,
          max: 60
        })

        SliderBlock({
          title: 'expectedFrameRateRange.max',
          isEnabled: $enableAnimateParamExpectedFrameRateRangeMax,
          value: $animateParamExpectedFrameRateRangeMax,
          min: 60,
          max: 120
        })

        SliderBlock({
          title: 'expectedFrameRateRange.min',
          isEnabled: $enableAnimateParamExpectedFrameRateRangeExpected,
          value: $animateParamExpectedFrameRateRangeExpected,
          min: 30,
          max: 80
        })

        RadioBlock({
          title: 'alignment',
          isEnabled: $enableCustomDialogControllerOptionsAlignment,
          value: $customDialogControllerOptionsAlignment,
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
          isEnabled: $enableCustomDialogControllerOptionsOffsetDx,
          value: $customDialogControllerOptionsOffsetDx,
          min: 0,
          max: 16
        })

        SliderBlock({
          title: 'offset.dy',
          isEnabled: $enableCustomDialogControllerOptionsOffsetDy,
          value: $customDialogControllerOptionsOffsetDy,
          min: 0,
          max: 16
        })


        RadioBlock({
          title: 'customStyle',
          isEnabled: $enableCustomDialogControllerOptionsCustomStyle,
          value: $customDialogControllerOptionsCustomStyle,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        RadioBlock({
          title: 'isModal',
          isEnabled: $enableCustomDialogControllerOptionsIsModal,
          value: $customDialogControllerOptionsIsModal,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        ColorBlock({
          title: 'backgroundColor',
          isEnabled: $enableCustomDialogControllerOptionsBackgroundColor,
          color: $customDialogControllerOptionsBackgroundColor,
        })

        RadioBlock({
          title: 'backgroundBlurStyle',
          isEnabled: $enableCustomDialogControllerOptionsBackgroundBlurStyle,
          value: $customDialogControllerOptionsBackgroundBlurStyle,
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
          isEnabled: $enableCustomDialogControllerOptionsCornerRadiusTopLeft,
          value: $customDialogControllerOptionsCornerRadiusTopLeft,
          min: 28,
          max: 48
        })

        SliderBlock({
          title: 'cornerRadius.topRight',
          isEnabled: $enableCustomDialogControllerOptionsCornerRadiusTopRight,
          value: $customDialogControllerOptionsCornerRadiusTopRight,
          min: 28,
          max: 48
        })

        SliderBlock({
          title: 'cornerRadius.bottomLeft',
          isEnabled: $enableCustomDialogControllerOptionsCornerRadiusBottomLeft,
          value: $customDialogControllerOptionsCornerRadiusBottomLeft,
          min: 28,
          max: 48
        })

        SliderBlock({
          title: 'cornerRadius.bottomRight',
          isEnabled: $enableCustomDialogControllerOptionsCornerRadiusBottomRight,
          value: $customDialogControllerOptionsCornerRadiusBottomRight,
          min: 28,
          max: 48
        })

        RadioBlock({
          title: 'shadow',
          isEnabled: $enableCustomDialogControllerOptionsShadow,
          value: $customDialogControllerOptionsShadow,
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
          isEnabled: $enableCustomDialogControllerOptionsBorderWidth,
          value: $customDialogControllerOptionsBorderWidth,
          min: 0,
          max: 6
        })

        ColorBlock({
          title: 'borderColor',
          isEnabled: $enableCustomDialogControllerOptionsBorderColor,
          color: $customDialogControllerOptionsBorderColor,
        })

        ColorBlock({
          title: 'maskColor',
          isEnabled: $enableMaskColor,
          color: $maskColor,
        })

        RadioBlock({
          title: 'borderStyle',
          isEnabled: $enableCustomDialogControllerOptionsBorderStyle,
          value: $customDialogControllerOptionsBorderStyle,
          dataSource: [
            { label: 'Dotted', value: BorderStyle.Dotted },
            { label: 'Dashed', value: BorderStyle.Dashed },
            { label: 'Solid', value: BorderStyle.Solid },
          ]
        })

        SliderBlock({
          title: 'width',
          isEnabled: $enableCustomDialogControllerOptionsWidth,
          value: $customDialogControllerOptionsWidth,
          min: 300,
          max: 400
        })

        SliderBlock({
          title: 'height',
          isEnabled: $enableCustomDialogControllerOptionsHeight,
          value: $customDialogControllerOptionsHeight,
          min: 400,
          max: 500
        })

        SliderBlock({
          title: 'gridCount',
          isEnabled: $enableCustomDialogControllerOptionsGridCount,
          value: $customDialogControllerOptionsGridCount,
          min: 4,
          max: 12
        })

        SliderBlock({
          title: 'maskRect.x',
          isEnabled: $enableCustomDialogControllerOptionsMaskRectX,
          value: $customDialogControllerOptionsMaskRectX,
          min: 0,
          max: 100
        })

        SliderBlock({
          title: 'maskRect.y',
          isEnabled: $enableCustomDialogControllerOptionsMaskRectY,
          value: $customDialogControllerOptionsMaskRectY,
          min: 0,
          max: 100
        })

        RadioBlock({
          title: 'maskRect.width',
          isEnabled: $enableCustomDialogControllerOptionsMaskRectWidth,
          value: $customDialogControllerOptionsMaskRectWidth,
          dataSource: [
            { label: '50%', value: '50%' },
            { label: '80%', value: '80%' },
            { label: '100%', value: '100%' },
          ]
        })

        RadioBlock({
          title: 'maskRect.height',
          isEnabled: $enableCustomDialogControllerOptionsMaskRectHeight,
          value: $customDialogControllerOptionsMaskRectHeight,
          dataSource: [
            { label: '50%', value: '50%' },
            { label: '80%', value: '80%' },
            { label: '100%', value: '100%' },
          ]
        })

        RadioBlock({
          title: 'curve',
          isEnabled: $enableAnimateParamCurve,
          value: $animateParamCurve,
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
      }.width('100%')
    }
    .height('52%')
    .id('scroll')
  }

  @Builder
  Generic() {

  }
}