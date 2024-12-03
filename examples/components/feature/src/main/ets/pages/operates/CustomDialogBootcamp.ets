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
export struct CustomDialogBootcamp {
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
  @State enableCustomDialogShadow: boolean = false;
  @State customDialogShadow: ShadowStyle = ShadowStyle.OUTER_DEFAULT_MD;
  @State enableCustomDialogBackgroundBlurStyle: boolean = false;
  @State customDialogBackgroundBlurStyle: BlurStyle = BlurStyle.COMPONENT_ULTRA_THICK;

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
        Button("确认").onClick(() => {
          promptAction.closeCustomDialog(this.customDialogComponentId)
        })
        Button("取消").onClick(() => {
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
              shadow: useEnabled(this.enableCustomDialogShadow, this.customDialogShadow),
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
          title: 'backgroundColor',
          isEnabled: $enableCustomDialogBackgroundColor,
          color: $customDialogBackgroundColor
        })

        SliderBlock({
          title: 'borderRadiusTopLeft',
          isEnabled: $enableBorderRadiusTopLeft,
          value: $borderRadiusTopLeft,
          min: 0,
          max: 50
        })

        SliderBlock({
          title: 'borderRadiusTopRight',
          isEnabled: $enableBorderRadiusTopRight,
          value: $borderRadiusTopRight,
          min: 0,
          max: 50
        })

        SliderBlock({
          title: 'borderRadiusBottomLeft',
          isEnabled: $enableBorderRadiusBottomLeft,
          value: $borderRadiusBottomLeft,
          min: 0,
          max: 50
        })

        SliderBlock({
          title: 'borderRadiusBottomRight',
          isEnabled: $enableBorderRadiusBottomRight,
          value: $borderRadiusBottomRight,
          min: 0,
          max: 50
        })

        SliderBlock({
          title: 'borderBorderWidthTop',
          isEnabled: $enableBorderWidthTop,
          value: $borderWidthTop,
          min: 0,
          max: 10
        })

        SliderBlock({
          title: 'borderBorderWidthLeft',
          isEnabled: $enableBorderWidthLeft,
          value: $borderWidthLeft,
          min: 0,
          max: 10
        })

        SliderBlock({
          title: 'borderBorderWidthBottom',
          isEnabled: $enableBorderWidthBottom,
          value: $borderWidthBottom,
          min: 0,
          max: 10
        })

        SliderBlock({
          title: 'borderBorderWidthRight',
          isEnabled: $enableBorderWidthRight,
          value: $borderWidthRight,
          min: 0,
          max: 10
        })

        ColorBlock({
          title: 'borderColorTop',
          isEnabled: $enableBorderColorTop,
          color: $borderColorTop
        })

        ColorBlock({
          title: 'borderColorLeft',
          isEnabled: $enableBorderColorLeft,
          color: $borderColorLeft
        })

        ColorBlock({
          title: 'borderColorBottom',
          isEnabled: $enableBorderColorBottom,
          color: $borderColorBottom
        })

        ColorBlock({
          title: 'borderColorRight',
          isEnabled: $enableBorderColorRight,
          color: $borderColorRight
        })


        RadioBlock({
          title: 'borderStyleTop',
          isEnabled: $enableBorderStyleTop,
          value: $borderStyleTop,
          dataSource: [
            { label: 'Solid', value: BorderStyle.Solid },
            { label: 'Dotted', value: BorderStyle.Dotted },
            { label: 'Dashed', value: BorderStyle.Dashed },
          ]
        })

        RadioBlock({
          title: 'borderStyleLeft',
          isEnabled: $enableBorderStyleLeft,
          value: $borderStyleLeft,
          dataSource: [
            { label: 'Solid', value: BorderStyle.Solid },
            { label: 'Dotted', value: BorderStyle.Dotted },
            { label: 'Dashed', value: BorderStyle.Dashed },
          ]
        })

        RadioBlock({
          title: 'borderStyleBottom',
          isEnabled: $enableBorderStyleBottom,
          value: $borderStyleBottom,
          dataSource: [
            { label: 'Solid', value: BorderStyle.Solid },
            { label: 'Dotted', value: BorderStyle.Dotted },
            { label: 'Dashed', value: BorderStyle.Dashed },
          ]
        })

        RadioBlock({
          title: 'borderStyleRight',
          isEnabled: $enableBorderStyleRight,
          value: $borderStyleRight,
          dataSource: [
            { label: 'Solid', value: BorderStyle.Solid },
            { label: 'Dotted', value: BorderStyle.Dotted },
            { label: 'Dashed', value: BorderStyle.Dashed },
          ]
        })

        SliderBlock({
          title: 'width',
          isEnabled: $enableCustomDialogWidth,
          value: $customDialogWidth,
          min: 100,
          max: 400
        })

        SliderBlock({
          title: 'height',
          isEnabled: $enableCustomDialogHeight,
          value: $customDialogHeight,
          min: 100,
          max: 400
        })

        RadioBlock({
          title: 'shadow',
          isEnabled: $enableCustomDialogShadow,
          value: $customDialogShadow,
          dataSource: [
            { label: 'OUTER_DEFAULT_XS', value: ShadowStyle.OUTER_DEFAULT_XS },
            { label: 'OUTER_DEFAULT_SM', value: ShadowStyle.OUTER_DEFAULT_SM },
            { label: 'OUTER_DEFAULT_MD', value: ShadowStyle.OUTER_DEFAULT_MD },
            { label: 'OUTER_DEFAULT_LG', value: ShadowStyle.OUTER_DEFAULT_LG },
            { label: 'OUTER_FLOATING_SM', value: ShadowStyle.OUTER_FLOATING_SM },
            { label: 'OUTER_FLOATING_MD', value: ShadowStyle.OUTER_FLOATING_MD },
          ]
        })

        RadioBlock({
          title: 'backgroundBlurStyle',
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

      }.width('100%')
    }
    .height('52%')
  }
}

@Preview
@Component
struct CustomDialogBootcampPreviewer {
  build() {
    CustomDialogBootcamp({
      title: '打开自定义弹窗/CustomDialog'
    })
  }
}
