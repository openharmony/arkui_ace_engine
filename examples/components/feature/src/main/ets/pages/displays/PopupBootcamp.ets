/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
import { Popup, PopupButtonOptions, PopupIconOptions, PopupTextOptions } from '@kit.ArkUI';


@Component
export struct PopupBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State isShow: boolean = false;
  @State enableIconImage: boolean = true;
  @State iconImage: ResourceStr = $r('app.media.startIcon');
  @State enableIconWidth: boolean = false;
  @State iconWidth: number = 32;
  @State enableIconHeight: boolean = false;
  @State iconHeight: number = 32;
  @State enableIconFillColor: boolean = false;
  @State iconFillColor: Color = Color.White;
  @State enableIconBorderRadius: boolean = false;
  @State iconBorderRadius: number = 16;
  @State enableTitle: boolean = true;
  @State showTitle:string='This is a popup with PopupOptions';
  @State enableTitleFontWeight: boolean = false;
  @State titleFontWeight: FontWeight = FontWeight.Normal;
  @State enableTitleFontSize: boolean = false;
  @State titleFontSize: number = 20;
  @State enableTitleFontColor: boolean = false;
  @State titleFontColor: Color = Color.Black;
  @State enableMessageFontSize: boolean = false;
  @State messageFontSize: number = 15;
  @State enableMessageFontColor: boolean = false;
  @State messageFontColor: Color = Color.Black;
  @State enableShowClose: boolean = false;
  @State showClose: boolean = false;
  @State enableButtonsConfirm: boolean = true;
  @State showButtonsConfirmText:string='confirm';
  @State enableButtonsCancel: boolean = true;
  @State showButtonsCancelText:string='cancel';
  @State enableButtonsConfirmFontSize: boolean = false;
  @State buttonsConfirmFontSize: number = 15;
  @State enableButtonsConfirmFontColor: boolean = false;
  @State buttonsConfirmFontColor: ResourceColor = Color.Black;
  @State enableButtonsCancelFontSize: boolean = false;
  @State buttonsCancelFontSize: number = 15;
  @State enableButtonsCancelFontColor: boolean = false;
  @State buttonsCancelFontColor: ResourceColor = Color.Black;
  @State currentDirection: Direction = Direction.Rtl

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
    .backgroundColor('#f1f3f5')
    .hideTitleBar(true)
  }

  @Builder
  Content() {
    Row() {
      Popup({
        //PopupIconOptions 类型设置图标内容
        direction: this.currentDirection,
        icon: {
          image: useEnabled(this.enableIconImage, this.iconImage),
          width: useEnabled(this.enableIconWidth, this.iconWidth),
          height: useEnabled(this.enableIconHeight, this.iconHeight),
          fillColor: useEnabled(this.enableIconFillColor, this.iconFillColor),
          borderRadius: useEnabled(this.enableIconBorderRadius, this.iconBorderRadius),
        } as PopupIconOptions,
        // PopupTextOptions 类型设置文字内容
        title: {
          text: useEnabled(this.enableTitle, this.showTitle),
          fontSize: useEnabled(this.enableTitleFontSize, this.titleFontSize),
          fontColor: useEnabled(this.enableTitleFontColor, this.titleFontColor),
          fontWeight: useEnabled(this.enableTitleFontWeight, this.titleFontWeight),
        } as PopupTextOptions,
        //PopupTextOptions 类型设置文字内容
        message: {
          text: 'This is the message',
          fontSize: useEnabled(this.enableMessageFontSize, this.messageFontSize),
          fontColor: useEnabled(this.enableMessageFontColor, this.messageFontColor),
        } as PopupTextOptions,
        showClose: useEnabled(this.enableShowClose, this.showClose),
        onClose: () => {
          console.info('close Button click')
        },
        // PopupButtonOptions 类型设置按钮内容
        buttons: [{
          text: useEnabled(this.enableButtonsConfirm, this.showButtonsConfirmText),
          action: () => {
            console.info('confirm button click')
          },
          fontSize: useEnabled(this.enableButtonsConfirmFontSize, this.buttonsConfirmFontSize),
          fontColor: useEnabled(this.enableButtonsConfirmFontColor, this.buttonsConfirmFontColor),
        },
          {
            text: useEnabled(this.enableButtonsCancel, this.showButtonsCancelText),
            action: () => {
              console.info('cancel button click')
            },
            fontSize: useEnabled(this.enableButtonsCancelFontSize, this.buttonsCancelFontSize),
            fontColor: useEnabled(this.enableButtonsCancelFontColor, this.buttonsCancelFontColor),
          },] as [PopupButtonOptions?, PopupButtonOptions?],
      })
    }.justifyContent(FlexAlign.Center)
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
        IconBlock({
          title: 'icon.image',
          isEnabled: $enableIconImage,
          icon: $iconImage,
        })

        SliderBlock({
          title: 'icon.width',
          isEnabled: $enableIconWidth,
          value: $iconWidth,
          min: 0,
          max: 100,
        })

        SliderBlock({
          title: 'icon.height',
          isEnabled: $enableIconHeight,
          value: $iconHeight,
          min: 0,
          max: 100,
        })

        ColorBlock({
          title: 'icon.fillColor',
          isEnabled: $enableIconFillColor,
          color: $iconFillColor,
        })

        SliderBlock({
          title: 'icon.borderRadius',
          isEnabled: $enableIconBorderRadius,
          value: $iconBorderRadius,
          min: 0,
          max: 24,
        })

        RadioBlock({
          title: 'title',
          isEnabled: $enableTitle,
          value: $showTitle
        })

        ColorBlock({
          title: 'title.fontColor',
          isEnabled: $enableTitleFontColor,
          color: $titleFontColor,
        })

        SliderBlock({
          title: 'title.fontSize',
          isEnabled: $enableTitleFontSize,
          value: $titleFontSize,
          min: 0,
          max: 24,
        })

        RadioBlock({
          title: 'title.fontWeight',
          isEnabled: $enableTitleFontWeight,
          value: $titleFontWeight,
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
          title: 'message.fontColor',
          isEnabled: $enableMessageFontColor,
          color: $messageFontColor,
        })

        SliderBlock({
          title: 'message.fontSize',
          isEnabled: $enableMessageFontSize,
          value: $messageFontSize,
          min: 0,
          max: 24,
        })

        RadioBlock({
          title: 'buttons.confirm',
          isEnabled: $enableButtonsConfirm,
          value: $showButtonsConfirmText
        })

        RadioBlock({
          title: 'buttons.cancel',
          isEnabled: $enableButtonsCancel,
          value: $showButtonsCancelText
        })

        ColorBlock({
          title: 'buttons.confirm.fontColor',
          isEnabled: $enableButtonsConfirmFontColor,
          color: $buttonsConfirmFontColor,
        })

        SliderBlock({
          title: 'buttons.confirm.fontSize',
          isEnabled: $enableButtonsConfirmFontSize,
          value: $buttonsConfirmFontSize,
          min: 0,
          max: 24,
        })

        ColorBlock({
          title: 'buttons.cancel.fontColor',
          isEnabled: $enableButtonsCancelFontColor,
          color: $buttonsCancelFontColor,
        })

        SliderBlock({
          title: 'buttons.cancel.fontSize',
          isEnabled: $enableButtonsCancelFontSize,
          value: $buttonsCancelFontSize,
          min: 0,
          max: 24,
        })

        RadioBlock({
          title: 'showClose',
          isEnabled: $enableShowClose,
          value: $showClose
        })
      }.width('100%')
    }
    .height('52%')
  }
}

@Preview
@Component
struct PopupBootcampPreviewer {
  build() {
    PopupBootcamp({
      title: '气泡/Popup'
    })
  }
}