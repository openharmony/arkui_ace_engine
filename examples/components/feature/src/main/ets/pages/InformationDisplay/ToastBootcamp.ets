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
import promptAction from '@ohos.promptAction';

@Component
export struct ToastBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State enableMessage: boolean = false;
  @State compMessage: string = 'Harmony Sans';
  @State enableDuration: boolean = false;
  @State compDuration: number = 1500;
  @State enableBottom: boolean = false;
  @State compBottom: number = 80;
  @State compBackGroundColor:ResourceColor = Color.Transparent;
  @State compMargin: number = 15;
  @State enableAlignment: boolean = false;
  @State alignment: Alignment = Alignment.Bottom;
  @State enableOffsetX: boolean = false;
  @State offsetX: number = 0;
  @State enableOffsetY: boolean = false;
  @State offsetY: number = 0;
  @State enableToastBackgroundColor: boolean = false;
  @State toastBackgroundColor: ResourceColor = '#ff000000';
  @State enableToastTextColor: boolean = false;
  @State toastTextColor: ResourceColor = '#ff000000';
  @State enableToastBackgroundBlurStyle: boolean = false;
  @State toastBackgroundBlurStyle: BlurStyle = BlurStyle.COMPONENT_ULTRA_THICK;
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
    .backgroundColor(this.compBackGroundColor)
    .hideTitleBar(true)
  }

  @Builder
  Content() {
    Column() {
      Button('显示Toast')
        .onClick(() => {
          try {
            promptAction.showToast({
              message: useEnabled(this.enableMessage, this.compMessage, 'text'),
              duration: useEnabled(this.enableDuration, this.compDuration),
              bottom: useEnabled(this.enableBottom, this.compBottom),
              alignment: useEnabled(this.enableAlignment,this.alignment),
              offset: {dx:useEnabled(this.enableOffsetX,this.offsetX),dy:useEnabled(this.enableOffsetY,this.offsetY)},
              backgroundColor: useEnabled(this.enableToastBackgroundColor,this.toastBackgroundColor),
              textColor: useEnabled(this.enableToastTextColor,this.toastTextColor),
              backgroundBlurStyle: useEnabled(this.enableToastBackgroundBlurStyle, this.toastBackgroundBlurStyle),
              shadow: useEnabled(this.enableShadowType, this.shadowType) ?
              useEnabled(this.enableDialogShadowStyle, this.dialogShadowStyle) : {
                  radius: useEnabled(this.enableShadowOptionsRadius, this.shadowOptionsRadius),
                  type: useEnabled(this.enableShadowOptionsType, this.shadowOptionsType),
                  color: useEnabled(this.enableShadowOptionsColor, this.shadowOptionsColor),
                  offsetX: useEnabled(this.enableShadowOptionsOffsetX, this.shadowOptionsOffsetX),
                  offsetY: useEnabled(this.enableShadowOptionsOffsetY, this.shadowOptionsOffsetY),
                  fill: useEnabled(this.enableShadowOptionsFill, this.shadowOptionsFill),
                },
            });
          } catch (error) {

          }
        }).margin(this.compMargin)
    }
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
        RadioBlock({
          title: 'showToastOptions.message',
          isEnabled: $enableMessage,
          value: $compMessage,
          dataSource: [
            { label: '单行', value: 'text'},
            { label: '多行', value: 'The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.'},
            { label: '多', value: 'The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.'},
            { label: '超多', value: 'The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.The test text is normal display.'}
          ]
        })
        SliderBlock({
          title: 'showToastOptions.duration',
          isEnabled: $enableDuration,
          value: $compDuration,
          min: 1500,
          max: 10000
        })
        SliderBlock({
          title: 'showToastOptions.bottom',
          isEnabled: $enableBottom,
          value: $compBottom,
          min: 80,
          max: 400
        })

        RadioBlock({
          title: 'showToastOptions.alignment',
          isEnabled: $enableAlignment,
          value: $alignment,
          dataSource: [
            { label: 'TopStart', value: Alignment.TopStart },
            { label: 'Top', value: Alignment.Top },
            { label: 'TopEnd', value: Alignment.TopEnd },
            { label: 'Start', value: Alignment.Start },
            { label: 'Center', value: Alignment.Center },
            { label: 'End', value: Alignment.End },
            { label: 'BottomStart', value: Alignment.BottomStart },
            { label: 'Bottom', value: Alignment.Bottom },
            { label: 'BottomEnd', value: Alignment.BottomEnd },
          ]
        })

        SliderBlock({
          title: 'showToastOptions.offset.x',
          isEnabled: $enableOffsetX,
          value: $offsetX,
          min: 0,
          max: 100
        })

        SliderBlock({
          title: 'showToastOptions.offset.y',
          isEnabled: $enableOffsetY,
          value: $offsetY,
          min: 0,
          max: 100
        })

        ColorBlock({
          title: 'showToastOptions.BackgroundColor',
          isEnabled: $enableToastBackgroundColor,
          color: $toastBackgroundColor
        })

        ColorBlock({
          title: 'showToastOptions.TextColor',
          isEnabled: $enableToastTextColor,
          color: $toastTextColor
        })

        RadioBlock({
          title: 'showToastOptions.BackgroundBlurStyle',
          isEnabled: $enableToastBackgroundBlurStyle,
          value: $toastBackgroundBlurStyle,
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
          title: 'showToastOptions.shadow',
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
struct ToastBootcampPreviewer {
  build() {
    ToastBootcamp({
      title: '即时反馈/Toast'
    })
  }
}
