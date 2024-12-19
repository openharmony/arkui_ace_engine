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
import { promptAction } from '@kit.ArkUI';

@Component
export struct promptActionCustomDialogBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  private customDialogComponentId: number = 0
  @State enableCustomDialogBackgroundColor: boolean = false;
  @State customDialogBackgroundColor: ResourceColor = '#ff000000';
  @State enableBorderRadiusTopLeft: boolean = false;
  @State borderRadiusTopLeft: number = 32;
  @State enableBorderRadiusTopRight: boolean = false;
  @State borderRadiusTopRight: number = 32;
  @State enableBorderRadiusBottomLeft: boolean = false;
  @State borderRadiusBottomLeft: number = 32;
  @State enableBorderRadiusBottomRight: boolean = false;
  @State borderRadiusBottomRight: number = 32;
  @State enableBorderWidthTop: boolean = false;
  @State borderWidthTop: number = 0;
  @State enableBorderWidthLeft: boolean = false;
  @State borderWidthLeft: number = 0;
  @State enableBorderWidthBottom: boolean = false;
  @State borderWidthBottom: number = 0;
  @State enableBorderWidthRight: boolean = false;
  @State borderWidthRight: number = 0;
  @State enableBorderColorTop: boolean = false;
  @State borderColorTop: ResourceColor = '#ff000000';
  @State enableBorderColorLeft: boolean = false;
  @State borderColorLeft: ResourceColor = '#ff000000';
  @State enableBorderColorBottom: boolean = false;
  @State borderColorBottom: ResourceColor = '#ff000000';
  @State enableBorderColorRight: boolean = false;
  @State borderColorRight: ResourceColor = '#ff000000';
  @State enableBorderStyleTop: boolean = false;
  @State borderStyleTop: BorderStyle = BorderStyle.Solid;
  @State enableBorderStyleLeft: boolean = false;
  @State borderStyleLeft: BorderStyle = BorderStyle.Solid;
  @State enableBorderStyleBottom: boolean = false;
  @State borderStyleBottom: BorderStyle = BorderStyle.Solid;
  @State enableBorderStyleRight: boolean = false;
  @State borderStyleRight: BorderStyle = BorderStyle.Solid;
  @State enableCustomDialogWidth: boolean = false;
  @State customDialogWidth: number = 100;
  @State enableCustomDialogHeight: boolean = false;
  @State customDialogHeight: number = 100;
  @State enableCustomDialogBackgroundBlurStyle: boolean = false;
  @State customDialogBackgroundBlurStyle: BlurStyle = BlurStyle.COMPONENT_ULTRA_THICK;
  @State enableShadowType: boolean = false;
  @State shadowType: boolean = true;
  @State enableDialogShadowStyle: boolean = false;
  @State dialogShadowStyle: ShadowStyle = ShadowStyle.OUTER_DEFAULT_MD;
  @State enableShadowOptionsRadius: boolean = false;
  @State shadowOptionsRadius: number = 0;
  @State enableShadowOptionsType: boolean = false;
  @State shadowOptionsType: ShadowType = ShadowType.COLOR;
  @State enableShadowOptionsColor: boolean = false;
  @State shadowOptionsColor: ResourceColor = '#ff000000';
  @State enableShadowOptionsOffsetX: boolean = false;
  @State shadowOptionsOffsetX: number = 0;
  @State enableShadowOptionsOffsetY: boolean = false;
  @State shadowOptionsOffsetY: number = 0;
  @State enableShadowOptionsFill: boolean = false;
  @State shadowOptionsFill: boolean = false;

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
  customDialogComponent() {
    Column() {
      Text('弹窗').fontSize(30)
      Row({ space: 50 }) {
        Button('确认').onClick(() => {
          promptAction.closeCustomDialog(this.customDialogComponentId)
        })
        Button('确认').onClick(() => {
          promptAction.closeCustomDialog(this.customDialogComponentId)
        })
      }
    }.height(200).padding(5).justifyContent(FlexAlign.SpaceBetween)
  }

  @Builder
  Content() {
    Column() {
      Button('弹出自定义弹窗')
        .onClick(() => {
          try {
            promptAction.openCustomDialog({
              builder: () => {
                this.customDialogComponent()
              },
              backgroundColor: useEnabled(this.enableCustomDialogBackgroundColor, this.customDialogBackgroundColor),
              cornerRadius: {
                topLeft: useEnabled(this.enableBorderRadiusTopLeft, this.borderRadiusTopLeft),
                topRight: useEnabled(this.enableBorderRadiusTopRight, this.borderRadiusTopRight),
                bottomLeft: useEnabled(this.enableBorderRadiusBottomLeft, this.borderRadiusBottomLeft),
                bottomRight: useEnabled(this.enableBorderRadiusBottomRight, this.borderRadiusBottomRight),
              },
              borderWidth: {
                top: useEnabled(this.enableBorderWidthTop, this.borderWidthTop),
                left: useEnabled(this.enableBorderWidthLeft, this.borderWidthLeft),
                bottom: useEnabled(this.enableBorderWidthBottom, this.borderWidthBottom),
                right: useEnabled(this.enableBorderWidthRight, this.borderWidthRight),
              },
              borderColor: {
                top: useEnabled(this.enableBorderColorTop, this.borderColorTop),
                left: useEnabled(this.enableBorderColorLeft, this.borderColorLeft),
                bottom: useEnabled(this.enableBorderColorBottom, this.borderColorBottom),
                right: useEnabled(this.enableBorderColorRight, this.borderColorRight),
              },
              borderStyle: {
                top: useEnabled(this.enableBorderStyleTop, this.borderStyleTop),
                left: useEnabled(this.enableBorderStyleLeft, this.borderStyleLeft),
                bottom: useEnabled(this.enableBorderStyleBottom, this.borderStyleBottom),
                right: useEnabled(this.enableBorderStyleRight, this.borderStyleRight),
              },
              width: useEnabled(this.enableCustomDialogWidth, this.customDialogWidth),
              height: useEnabled(this.enableCustomDialogHeight, this.customDialogHeight),
              shadow: useEnabled(this.enableShadowType, this.shadowType) ?
              useEnabled(this.enableDialogShadowStyle, this.dialogShadowStyle) : {
                  radius: useEnabled(this.enableShadowOptionsRadius, this.shadowOptionsRadius),
                  type: useEnabled(this.enableShadowOptionsType, this.shadowOptionsType),
                  color: useEnabled(this.enableShadowOptionsColor, this.shadowOptionsColor),
                  offsetX: useEnabled(this.enableShadowOptionsOffsetX, this.shadowOptionsOffsetX),
                  offsetY: useEnabled(this.enableShadowOptionsOffsetY, this.shadowOptionsOffsetY),
                  fill: useEnabled(this.enableShadowOptionsFill, this.shadowOptionsFill),
                },
            }).then((dialogId: number) => {
              this.customDialogComponentId = dialogId
            })

          } catch (err) {

          }
        })
    }

  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {

        ColorBlock({
          title: 'CustomDialogOptions.backgroundColor',
          isEnabled: $enableCustomDialogBackgroundColor,
          color: $customDialogBackgroundColor
        })

        SliderBlock({
          title: 'CustomDialogOptions.borderRadiusTopLeft',
          isEnabled: $enableBorderRadiusTopLeft,
          value: $borderRadiusTopLeft,
          min: 0,
          max: 50
        })

        SliderBlock({
          title: 'CustomDialogOptions.borderRadiusTopRight',
          isEnabled: $enableBorderRadiusTopRight,
          value: $borderRadiusTopRight,
          min: 0,
          max: 50
        })

        SliderBlock({
          title: 'CustomDialogOptions.borderRadiusBottomLeft',
          isEnabled: $enableBorderRadiusBottomLeft,
          value: $borderRadiusBottomLeft,
          min: 0,
          max: 50
        })

        SliderBlock({
          title: 'CustomDialogOptions.borderRadiusBottomRight',
          isEnabled: $enableBorderRadiusBottomRight,
          value: $borderRadiusBottomRight,
          min: 0,
          max: 50
        })

        SliderBlock({
          title: 'CustomDialogOptions.borderBorderWidthTop',
          isEnabled: $enableBorderWidthTop,
          value: $borderWidthTop,
          min: 0,
          max: 10
        })

        SliderBlock({
          title: 'CustomDialogOptions.borderBorderWidthLeft',
          isEnabled: $enableBorderWidthLeft,
          value: $borderWidthLeft,
          min: 0,
          max: 10
        })

        SliderBlock({
          title: 'CustomDialogOptions.borderBorderWidthBottom',
          isEnabled: $enableBorderWidthBottom,
          value: $borderWidthBottom,
          min: 0,
          max: 10
        })

        SliderBlock({
          title: 'CustomDialogOptions.borderBorderWidthRight',
          isEnabled: $enableBorderWidthRight,
          value: $borderWidthRight,
          min: 0,
          max: 10
        })

        ColorBlock({
          title: 'CustomDialogOptions.borderColorTop',
          isEnabled: $enableBorderColorTop,
          color: $borderColorTop
        })

        ColorBlock({
          title: 'CustomDialogOptions.borderColorLeft',
          isEnabled: $enableBorderColorLeft,
          color: $borderColorLeft
        })

        ColorBlock({
          title: 'CustomDialogOptions.borderColorBottom',
          isEnabled: $enableBorderColorBottom,
          color: $borderColorBottom
        })

        ColorBlock({
          title: 'CustomDialogOptions.borderColorRight',
          isEnabled: $enableBorderColorRight,
          color: $borderColorRight
        })


        RadioBlock({
          title: 'CustomDialogOptions.borderStyleTop',
          isEnabled: $enableBorderStyleTop,
          value: $borderStyleTop,
          dataSource: [
            { label: 'Solid', value: BorderStyle.Solid },
            { label: 'Dotted', value: BorderStyle.Dotted },
            { label: 'Dashed', value: BorderStyle.Dashed },
          ]
        })

        RadioBlock({
          title: 'CustomDialogOptions.borderStyleLeft',
          isEnabled: $enableBorderStyleLeft,
          value: $borderStyleLeft,
          dataSource: [
            { label: 'Solid', value: BorderStyle.Solid },
            { label: 'Dotted', value: BorderStyle.Dotted },
            { label: 'Dashed', value: BorderStyle.Dashed },
          ]
        })

        RadioBlock({
          title: 'CustomDialogOptions.borderStyleBottom',
          isEnabled: $enableBorderStyleBottom,
          value: $borderStyleBottom,
          dataSource: [
            { label: 'Solid', value: BorderStyle.Solid },
            { label: 'Dotted', value: BorderStyle.Dotted },
            { label: 'Dashed', value: BorderStyle.Dashed },
          ]
        })

        RadioBlock({
          title: 'CustomDialogOptions.borderStyleRight',
          isEnabled: $enableBorderStyleRight,
          value: $borderStyleRight,
          dataSource: [
            { label: 'Solid', value: BorderStyle.Solid },
            { label: 'Dotted', value: BorderStyle.Dotted },
            { label: 'Dashed', value: BorderStyle.Dashed },
          ]
        })

        SliderBlock({
          title: 'CustomDialogOptions.width',
          isEnabled: $enableCustomDialogWidth,
          value: $customDialogWidth,
          min: 100,
          max: 400
        })

        SliderBlock({
          title: 'CustomDialogOptions.height',
          isEnabled: $enableCustomDialogHeight,
          value: $customDialogHeight,
          min: 100,
          max: 400
        })



        RadioBlock({
          title: 'CustomDialogOptions.backgroundBlurStyle',
          isEnabled: $enableCustomDialogBackgroundBlurStyle,
          value: $customDialogBackgroundBlurStyle,
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
            { label: 'COMPONENT_REGULAR', value: BlurStyle.COMPONENT_REGULAR },
            { label: 'COMPONENT_THICK', value: BlurStyle.COMPONENT_THICK },
            { label: 'COMPONENT_ULTRA_THICK', value: BlurStyle.COMPONENT_ULTRA_THICK },
          ]
        })

        RadioBlock({
          title: 'CustomDialogOptions.shadow',
          isEnabled: $enableShadowType,
          value: $shadowType,
          dataSource: [
            { label: 'shadowStyle', value: true },
            { label: 'shadowOptions', value: false }
          ]
        })

        if (this.shadowType) {
          RadioBlock({
            title: 'shadowStyle',
            isEnabled: $enableDialogShadowStyle,
            value: $dialogShadowStyle,
            dataSource: [
              { label: 'OUTER_DEFAULT_XS', value: ShadowStyle.OUTER_DEFAULT_XS },
              { label: 'OUTER_DEFAULT_SM', value: ShadowStyle.OUTER_DEFAULT_SM },
              { label: 'OUTER_DEFAULT_MD', value: ShadowStyle.OUTER_DEFAULT_MD },
              { label: 'OUTER_DEFAULT_LG', value: ShadowStyle.OUTER_DEFAULT_LG },
              { label: 'OUTER_FLOATING_SM', value: ShadowStyle.OUTER_FLOATING_SM },
              { label: 'OUTER_FLOATING_MD', value: ShadowStyle.OUTER_FLOATING_MD },
            ]
          })
        } else {

          SliderBlock({
            title: 'shadowOptions.radius',
            isEnabled: $enableShadowOptionsRadius,
            value: $shadowOptionsRadius,
            min: 0,
            max: 30,
          })

          RadioBlock({
            title: 'shadowOptions.type',
            isEnabled: $enableShadowOptionsType,
            value: $shadowOptionsType,
            dataSource: [
              { label: 'COLOR', value: ShadowType.COLOR },
              { label: 'BLUR', value: ShadowType.BLUR },
            ]
          })

          ColorBlock({
            title: 'shadowOptions.color',
            isEnabled: $enableShadowOptionsColor,
            color: $shadowOptionsColor,
          })

          SliderBlock({
            title: 'shadowOptions.offsetX',
            isEnabled: $enableShadowOptionsOffsetX,
            value: $shadowOptionsOffsetX,
            min: 0,
            max: 40,
          })

          SliderBlock({
            title: 'shadowOptions.offsetY',
            isEnabled: $enableShadowOptionsOffsetY,
            value: $shadowOptionsOffsetY,
            min: 0,
            max: 40,
          })

          RadioBlock({
            title: 'shadowOptions.fill',
            isEnabled: $enableShadowOptionsFill,
            value: $shadowOptionsFill,
            dataSource: [
              { label: 'true', value: true },
              { label: 'false', value: false },
            ]
          })

        }

      }.width('100%')
    }
    .height('52%')
  }
}

@Preview
@Component
struct CustomDialogBootcampPreviewer {
  build() {
    promptActionCustomDialogBootcamp({
      title: '打开自定义弹窗/CustomDialog'
    })
  }
}
