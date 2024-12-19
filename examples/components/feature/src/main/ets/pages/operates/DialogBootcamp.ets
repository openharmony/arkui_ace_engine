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
export struct DialogBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State enableDialogType: boolean = false;
  @State dialogType: number = 0;
  @State enableAlignment: boolean = false;
  @State alignment: DialogAlignment = DialogAlignment.Center;
  @State enableIsModal: boolean = false;
  @State isModal: boolean = true;
  @State enableDialogBackgroundColor: boolean = false;
  @State dialogBackgroundColor: ResourceColor = '#ff000000';
  @State enableDialogBackgroundBlurStyle: boolean = false;
  @State dialogBackgroundBlurStyle: BlurStyle = BlurStyle.COMPONENT_ULTRA_THICK;
  @State enableAlignmentOffsetX: boolean = false;
  @State alignmentOffsetX: number = 0;
  @State enableAlignmentOffsetY: boolean = false;
  @State alignmentOffsetY: number = 0;
  @State enableMaskRectX: boolean = false;
  @State maskRectX: number = 0;
  @State enableMaskRectY: boolean = false;
  @State maskRectY: number = 0;
  @State enableMaskRectWidth: boolean = false;
  @State maskRectWidth: number = 100;
  @State enableMaskRectHeight: boolean = false;
  @State maskRectHeight: number = 100;
  @State enableShowInSubWindow: boolean = false;
  @State showInSubWindow: boolean = false;
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
  Content() {
    Column() {
      Button('弹出对话框')
        .onClick(() => {
          try {
            promptAction.showDialog(
              {
                title: 'text',
                message: 'Message',
                alignment: useEnabled(this.enableAlignment, this.alignment),
                backgroundColor: useEnabled(this.enableDialogBackgroundColor, this.dialogBackgroundColor),
                backgroundBlurStyle: useEnabled(this.enableDialogBackgroundBlurStyle, this.dialogBackgroundBlurStyle),
                offset: {
                  dx: useEnabled(this.enableAlignmentOffsetX, this.alignmentOffsetX),
                  dy: useEnabled(this.enableAlignmentOffsetY, this.alignmentOffsetY)
                },
                isModal: useEnabled(this.enableIsModal, this.isModal),
                showInSubWindow: useEnabled(this.enableShowInSubWindow, this.showInSubWindow),
                shadow: useEnabled(this.enableShadowType, this.shadowType) ?
                useEnabled(this.enableDialogShadowStyle, this.dialogShadowStyle) : {
                    radius: useEnabled(this.enableShadowOptionsRadius, this.shadowOptionsRadius),
                    type: useEnabled(this.enableShadowOptionsType, this.shadowOptionsType),
                    color: useEnabled(this.enableShadowOptionsColor, this.shadowOptionsColor),
                    offsetX: useEnabled(this.enableShadowOptionsOffsetX, this.shadowOptionsOffsetX),
                    offsetY: useEnabled(this.enableShadowOptionsOffsetY, this.shadowOptionsOffsetY),
                    fill: useEnabled(this.enableShadowOptionsFill, this.shadowOptionsFill),
                  },
                maskRect: {
                  x: this.enableMaskRectX ? useEnabled(this.enableMaskRectX, this.maskRectX) : 0,
                  y: this.enableMaskRectY ? useEnabled(this.enableMaskRectY, this.maskRectY) : 0,
                  width: this.enableMaskRectWidth ? useEnabled(this.enableMaskRectWidth, this.maskRectHeight) : '100%',
                  height: this.enableMaskRectHeight ? useEnabled(this.enableMaskRectHeight, this.maskRectHeight) :
                    '100%',
                },
                buttons: this.dialogType === 0 ? [
                  {
                    text: 'button1',
                    color: '#000000'
                  },
                  {
                    text: 'button2',
                    color: '#000000'
                  }
                ] : null,
              }
            );
          } catch (err) {

          }
        })
    }

  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {

        RadioBlock({
          title: 'ShowDialogOptions.buttons',
          isEnabled: $enableDialogType,
          value: $dialogType,
          dataSource: [
            { label: '显示按钮', value: 0 },
            { label: '不显示按妞', value: 1 }
          ]
        })

        RadioBlock({
          title: 'ShowDialogOptions.alignment',
          isEnabled: $enableAlignment,
          value: $alignment,
          dataSource: [
            { label: 'Top', value: DialogAlignment.Top },
            { label: 'Center', value: DialogAlignment.Center },
            { label: 'Bottom', value: DialogAlignment.Bottom },
            { label: 'Default', value: DialogAlignment.Default },
            { label: 'TopStart', value: DialogAlignment.TopStart },
            { label: 'TopEnd', value: DialogAlignment.TopEnd },
            { label: 'CenterStart', value: DialogAlignment.CenterStart },
            { label: 'CenterEnd', value: DialogAlignment.CenterEnd },
            { label: 'BottomStart', value: DialogAlignment.BottomStart },
            { label: 'BottomEnd', value: DialogAlignment.BottomEnd },
          ]
        })

        SliderBlock({
          title: 'ShowDialogOptions.offsetX',
          isEnabled: $enableAlignmentOffsetX,
          value: $alignmentOffsetX,
          min: 0,
          max: 100
        })

        SliderBlock({
          title: 'ShowDialogOptions.offsetY',
          isEnabled: $enableAlignmentOffsetY,
          value: $alignmentOffsetY,
          min: 0,
          max: 100
        })

        SliderBlock({
          title: 'ShowDialogOptions.MaskRectX',
          isEnabled: $enableMaskRectX,
          value: $maskRectX,
          min: 0,
          max: 100
        })

        SliderBlock({
          title: 'ShowDialogOptions.MaskRectY',
          isEnabled: $enableMaskRectY,
          value: $maskRectY,
          min: 0,
          max: 100
        })

        SliderBlock({
          title: 'ShowDialogOptions.MaskRectWidth',
          isEnabled: $enableMaskRectWidth,
          value: $maskRectWidth,
          min: 100,
          max: 600
        })

        SliderBlock({
          title: 'ShowDialogOptions.MaskRectHeight',
          isEnabled: $enableMaskRectHeight,
          value: $maskRectHeight,
          min: 100,
          max: 600
        })

        RadioBlock({
          title: 'ShowDialogOptions.isModal',
          isEnabled: $enableIsModal,
          value: $isModal,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        RadioBlock({
          title: 'ShowDialogOptions.showInSubWindow',
          isEnabled: $enableShowInSubWindow,
          value: $showInSubWindow,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        ColorBlock({
          title: 'ShowDialogOptions.BackgroundColor',
          isEnabled: $enableDialogBackgroundColor,
          color: $dialogBackgroundColor
        })

        RadioBlock({
          title: 'ShowDialogOptions.BackgroundBlurStyle',
          isEnabled: $enableDialogBackgroundBlurStyle,
          value: $dialogBackgroundBlurStyle,
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
          title: 'ShowDialogOptions.shadow',
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
struct DialogBootcampPreviewer {
  build() {
    DialogBootcamp({
      title: '对话框/Dialog'
    })
  }
}
