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

'use static'

import { State } from '@ohos.arkui.stateManagement'
import { Entry, Component, NavDestination, ClickEvent, Dimension, EdgeColors, Column, ColumnOptions, Row, RowOptions,
  Scroll, Scroller, Button, Text, Color, $r, Image, ResourceStr, ResourceColor, SubMenuExpandingMode, MenuOptions,
  ContextMenuOptions, MenuElement, Menu, MenuItem, MenuItemOptions, CustomDialog, PopupOptions, CustomPopupOptions,
  PopupCommonOptions, PopupStateChangeParam, EdgeOutlineWidths, wrapBuilder, AvoidanceMode, Placement,
  PopupMessageOptions, PopupBorderLinearGradient, GradientDirection, ContextMenuAnimationOptions, MenuPreviewMode,
  BlurStyle, ModalMode, PreviewScaleMode, AvailableLayoutArea, ResponseType, CustomDialogController, CustomBuilder,
  CustomBuilderT, FontWeight, Length, TextAlign, TransitionEffect, Curve,AnimationNumberRange, Margin, FlexAlign
} from '@ohos.arkui.component'
import { BusinessError } from '@kit.BasicServicesKit';
import { ComponentContent, FrameNode, Frame } from '@ohos.arkui.node';
import { UIContext, PromptAction, TargetInfo } from '@ohos.arkui.UIContext'
import { SymbolGlyphModifier } from 'arkui.SymbolGlyphModifier';
import promptAction from '@ohos.promptAction';
import hilog from '@ohos.hilog'

@Entry
@Component
struct BindPopupBorderLinearGradient {
  @State message: string =
    'This is a popup with PopupOptions,This is a popup with PopupOptions,This is a popup with PopupOptions' +
      'This is a popup with PopupOptions,This is a popup with PopupOptions,This is a popup with PopupOptions,This is a popup with PopupOptions'
  @State handlePopup: boolean = false;
  @State handlePopup1: boolean = false;
  @State handlePopup2: boolean = false;
  @State handlePopup3: boolean = false;
  @State handlePopup4: boolean = false;
  @State handlePopup5: boolean = false;
  @State handlePopup6: boolean = false;
  @State handlePopup7: boolean = false;
  @State borderLinearGradientIndex: Int = 0;
  @State borderLinearGradientList: (PopupBorderLinearGradient | undefined)[] = [
    {
      direction: GradientDirection.LeftBottom,
      colors: [[Color.Yellow, 0.0], [Color.Green, 0.5], [Color.Blue, 1.0]]
    } as PopupBorderLinearGradient,
    undefined,
    { direction: GradientDirection.Left, colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]] } as PopupBorderLinearGradient,
  ]
  @State borderLinearGradientIndex1: Int = 0;
  @State borderLinearGradientList1: (PopupBorderLinearGradient | undefined)[] = [
    {
      direction: GradientDirection.LeftBottom, colors: [[Color.Yellow, 0.0], [Color.Green, 0.5], [Color.Blue, 1.0]]
    } as PopupBorderLinearGradient,
    undefined,
    { direction: GradientDirection.Left, colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]] } as PopupBorderLinearGradient,
  ]

  build() {
    Column({ space: 5 } as ColumnOptions) {
      Text(`enableArrow设置为true:`)
        .fontSize(16)
        .width('100%')
      Button('设置LeftBottom,Yellow,Green,Blue')
        .onClick(() => {
          this.handlePopup1 = !this.handlePopup1;
        })
        .bindPopup(this.handlePopup1, {
          message: this.message,
          placement: Placement.Bottom,
          enableArrow: true,
          borderWidth: '10vp',
          borderLinearGradient: {
            direction: GradientDirection.LeftBottom,
            colors: [[Color.Yellow, 0.0], [Color.Green, 0.5], [Color.Blue, 1.0]]
          },
          onStateChange: (event: PopupStateChangeParam) => {
            if (!event.isVisible) {
              this.handlePopup1 = false;
            }
          }
        })
      Button('不设置borderLinearGradient')
        .onClick(() => {
          this.handlePopup2 = !this.handlePopup2;
        })
        .bindPopup(this.handlePopup2, {
          message: this.message,
          placement: Placement.Bottom,
          enableArrow: true,
          borderWidth: '10vp',
          onStateChange: (event: PopupStateChangeParam) => {
            if (!event.isVisible) {
              this.handlePopup2 = false;
            }
          }
        })
      Button('undefined')
        .onClick(() => {
          this.handlePopup3 = !this.handlePopup3;
        })
        .bindPopup(this.handlePopup3, {
          message: this.message,
          placement: Placement.Bottom,
          enableArrow: true,
          borderWidth: '10vp',
          borderLinearGradient: undefined,
          onStateChange: (event: PopupStateChangeParam) => {
            if (!event.isVisible) {
              this.handlePopup3 = false;
            }
          }
        })
      Row({ space: 5 } as RowOptions) {
        Button('popup')
          .onClick(() => {
            this.handlePopup = !this.handlePopup;
          })
          .bindPopup(this.handlePopup, {
            message: this.message,
            placement: Placement.Bottom,
            enableArrow: true,
            borderWidth: '10vp',
            borderLinearGradient: this.borderLinearGradientList[this.borderLinearGradientIndex],
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup = false;
              }
            }
          })
        Button('动态切换 : ' + this.borderLinearGradientList[this.borderLinearGradientIndex])
          .onClick(() => {
            setTimeout(() => {
              this.borderLinearGradientIndex++
              if (this.borderLinearGradientIndex >= this.borderLinearGradientList.length) {
                this.borderLinearGradientIndex = 0
              }
            }, 2000)
          })
      }

      Text(`enableArrow设置为false:`)
        .fontSize(16)
        .width('100%')
      Button('设置LeftBottom,Yellow,Green,Blue')
        .onClick(() => {
          this.handlePopup4 = !this.handlePopup4;
        })
        .bindPopup(this.handlePopup4, {
          message: this.message,
          placement: Placement.Bottom,
          enableArrow: false,
          borderWidth: '10vp',
          borderLinearGradient: {
            direction: GradientDirection.LeftBottom,
            colors: [[Color.Yellow, 0.0], [Color.Green, 0.5], [Color.Blue, 1.0]]
          },
          onStateChange: (event: PopupStateChangeParam) => {
            if (!event.isVisible) {
              this.handlePopup4 = false;
            }
          }
        })
      Button('不设置borderLinearGradient')
        .onClick(() => {
          this.handlePopup5 = !this.handlePopup5;
        })
        .bindPopup(this.handlePopup5, {
          message: this.message,
          placement: Placement.Bottom,
          enableArrow: false,
          borderWidth: '10vp',
          onStateChange: (event: PopupStateChangeParam) => {
            if (!event.isVisible) {
              this.handlePopup5 = false;
            }
          }
        })
      Button('undefined')
        .onClick(() => {
          this.handlePopup6 = !this.handlePopup6;
        })
        .bindPopup(this.handlePopup6, {
          message: this.message,
          placement: Placement.Bottom,
          enableArrow: false,
          borderWidth: '10vp',
          borderLinearGradient: undefined,
          onStateChange: (event: PopupStateChangeParam) => {
            if (!event.isVisible) {
              this.handlePopup6 = false;
            }
          }
        })
      Row({ space: 5 } as RowOptions) {
        Button('popup')
          .onClick(() => {
            this.handlePopup7 = !this.handlePopup7;
          })
          .bindPopup(this.handlePopup7, {
            message: this.message,
            placement: Placement.Bottom,
            enableArrow: false,
            borderWidth: '10vp',
            borderLinearGradient: this.borderLinearGradientList1[this.borderLinearGradientIndex1],
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup7 = false;
              }
            }
          })
        Button('动态切换 : ' + this.borderLinearGradientList1[this.borderLinearGradientIndex1])
          .onClick(() => {
            setTimeout(() => {
              this.borderLinearGradientIndex1++
              if (this.borderLinearGradientIndex1 >= this.borderLinearGradientList1.length) {
                this.borderLinearGradientIndex1 = 0
              }
            }, 2000)
          })
      }
    }.margin(20)
  }
}