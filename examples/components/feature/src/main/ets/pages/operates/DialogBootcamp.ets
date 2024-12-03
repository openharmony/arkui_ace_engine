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
import { ColorBlock, IconBlock, RadioBlock, SliderBlock, useEnabled } from 'common';
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
  @State enableDialogShadow: boolean = false;
  @State dialogShadow: ShadowStyle = ShadowStyle.OUTER_DEFAULT_MD;

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
                shadow: useEnabled(this.enableDialogShadow, this.dialogShadow),
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
          title: '对话框按钮',
          isEnabled: $enableDialogType,
          value: $dialogType,
          dataSource: [
            { label: '显示按钮', value: 0 },
            { label: '不显示按妞', value: 1 }
          ]
        })

        RadioBlock({
          title: '弹窗在竖直方向上的对齐方式',
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
          title: 'offsetX',
          isEnabled: $enableAlignmentOffsetX,
          value: $alignmentOffsetX,
          min: 0,
          max: 100
        })

        SliderBlock({
          title: 'offsetY',
          isEnabled: $enableAlignmentOffsetY,
          value: $alignmentOffsetY,
          min: 0,
          max: 100
        })
        SliderBlock({
          title: 'MaskRectX',
          isEnabled: $enableMaskRectX,
          value: $maskRectX,
          min: 0,
          max: 100
        })
        SliderBlock({
          title: 'MaskRectY',
          isEnabled: $enableMaskRectY,
          value: $maskRectY,
          min: 0,
          max: 100
        })

        SliderBlock({
          title: 'MaskRectWidth',
          isEnabled: $enableMaskRectWidth,
          value: $maskRectWidth,
          min: 100,
          max: 600
        })

        SliderBlock({
          title: 'MaskRectHeight',
          isEnabled: $enableMaskRectHeight,
          value: $maskRectHeight,
          min: 100,
          max: 600
        })

        RadioBlock({
          title: 'isModal',
          isEnabled: $enableIsModal,
          value: $isModal,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        RadioBlock({
          title: 'showInSubWindow',
          isEnabled: $enableShowInSubWindow,
          value: $showInSubWindow,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false }
          ]
        })

        ColorBlock({
          title: 'BackgroundColor',
          isEnabled: $enableDialogBackgroundColor,
          color: $dialogBackgroundColor
        })

        RadioBlock({
          title: 'BackgroundBlurStyle',
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
          title: 'shadow',
          isEnabled: $enableDialogShadow,
          value: $dialogShadow,
          dataSource: [
            { label: 'OUTER_DEFAULT_XS', value: ShadowStyle.OUTER_DEFAULT_XS },
            { label: 'OUTER_DEFAULT_SM', value: ShadowStyle.OUTER_DEFAULT_SM },
            { label: 'OUTER_DEFAULT_MD', value: ShadowStyle.OUTER_DEFAULT_MD },
            { label: 'OUTER_DEFAULT_LG', value: ShadowStyle.OUTER_DEFAULT_LG },
            { label: 'OUTER_FLOATING_SM', value: ShadowStyle.OUTER_FLOATING_SM },
            { label: 'OUTER_FLOATING_MD', value: ShadowStyle.OUTER_FLOATING_MD },
          ]
        })


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
