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
struct CustomPopupAvoidTarget {
  @State handlePopup: boolean = false;
  @State handlePopup1: boolean = false;
  @State handlePopup2: boolean = false;
  @State handlePopup3: boolean = false;
  @State handlePopup4: boolean = false;
  @State handlePopup5: boolean = false;
  @State handlePopup6: boolean = false;
  @State handlePopup7: boolean = false;
  @State handlePopup8: boolean = false;
  @State handlePopup9: boolean = false;
  @State handlePopup10: boolean = false;
  @State handlePopup11: boolean = false;
  @State handlePopup12: boolean = false;
  @State handlePopup13: boolean = false;
  @State handlePopup14: boolean = false;
  @State handlePopup15: boolean = false;
  @State handlePopup16: boolean = false;
  @State handlePopup17: boolean = false;
  @State handlePopup18: boolean = false;
  @State handlePopup19: boolean = false;
  @State avoidTargetIndex: Int = 0;
  @State avoidTargetList: (AvoidanceMode | undefined)[] = [
    AvoidanceMode.COVER_TARGET,
    AvoidanceMode.AVOID_AROUND_TARGET,
    undefined,
    AvoidanceMode.AVOID_AROUND_TARGET,
  ]
  @State avoidTargetIndex1: Int = 0;
  @State avoidTargetList1: (AvoidanceMode | undefined)[] = [
    AvoidanceMode.COVER_TARGET,
    AvoidanceMode.AVOID_AROUND_TARGET,
    undefined,
    AvoidanceMode.AVOID_AROUND_TARGET,
  ]

  @Builder
  PopupBuilder() {
    Scroll(new Scroller()) {
      Column({ space: 5 } as ColumnOptions) {
        Text('This is a popup with PopupOptionsThis is a popup with PopupOptionsThis is a popup with PopupOptions' +
          'This is a popup with PopupOptionsThis is a popup with PopupOptionsThis is a popup with PopupOptions' +
          'This is a popup with PopupOptionsThis is a popup with PopupOptionsThis is a popup with PopupOptions' +
          'This is a popup with PopupOptionsThis is a popup with PopupOptionsThis is a popup with PopupOptions' +
          'This is a popup with PopupOptionsThis is a popup with PopupOptionsThis is a popup with PopupOptions' +
          'This is a popup with PopupOptionsThis is a popup with PopupOptionsThis is a popup with PopupOptions' +
          'This is a popup with PopupOptionsThis is a popup with PopupOptionsThis is a popup with PopupOptions' +
          'This is a popup with PopupOptionsThis is a popup with PopupOptionsThis is a popup with PopupOptions' +
          'This is a popup with PopupOptionsThis is a popup with PopupOptionsThis is a popup with PopupOptions' +
          'This is a popup with PopupOptionsThis is a popup with PopupOptionsThis is a popup with PopupOptions' +
          'This is a popup with PopupOptionsThis is a popup with PopupOptionsThis is a popup with PopupOptions' +
          'This is a popup with PopupOptionsThis is a popup with PopupOptionsThis is a popup with PopupOptions' +
          'This is a popup with PopupOptionsThis is a popup with PopupOptionsThis is a popup with PopupOptions' +
          'This is a popup with PopupOptionsThis is a popup with PopupOptionsThis is a popup with PopupOptions' +
          'This is a popup with PopupOptionsThis is a popup with PopupOptionsThis is a popup with PopupOptions' +
          'This is a popup with PopupOptionsThis is a popup with PopupOptionsThis is a popup with PopupOptions' +
          'This is a popup with PopupOptionsThis is a popup with PopupOptionsThis is a popup with PopupOptions' +
          'This is a popup with PopupOptionsThis is a popup with PopupOptionsThis is a popup with PopupOptions' +
          'This is a popup with PopupOptionsThis is a popup with PopupOptionsThis is a popup with PopupOptions' +
          'This is a popup with PopupOptionsThis is a popup with PopupOptionsThis is a popup with PopupOptions' +
          'This is a popup with PopupOptionsThis is a popup with PopupOptionsThis is a popup with PopupOptions' +
          'This is a popup with PopupOptionsThis is a popup with PopupOptionsThis is a popup with PopupOptions' +
          'This is a popup with PopupOptionsThis is a popup with PopupOptionsThis is a popup with PopupOptions' +
          'This is a popup with PopupOptionsThis is a popup with PopupOptionsThis is a popup with PopupOptions' +
          'This is a popup with PopupOptionsThis is a popup with PopupOptionsThis is a popup with PopupOptions' +
          'This is a popup with PopupOptionsThis is a popup with PopupOptionsThis is a popup with PopupOptions' +
          'This is a popup with PopupOptionsThis is a popup with PopupOptionsThis is a popup with PopupOptions' +
          'This is a popup with PopupOptionsThis is a popup with PopupOptionsThis is a popup with PopupOptions' +
          'This is a popup with PopupOptionsThis is a popup with PopupOptionsThis is a popup with PopupOptions,')
      }
    }
  }

  build() {
    Column({ space: 5 } as ColumnOptions) {
      Text(`enableArrow设置为true:`)
        .fontSize(16)
        .width('100%')
      Row({ space: 5 } as RowOptions) {
        Button('COVER_TARGET')
          .onClick(() => {
            this.handlePopup1 = !this.handlePopup1;
          })
          .bindPopup(this.handlePopup1, {
            builder: this.PopupBuilder,
            placement: Placement.Bottom,
            enableArrow: true,
            avoidTarget: AvoidanceMode.COVER_TARGET,
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup1 = false;
              }
            }
          })
      }

      Row({ space: 5 } as RowOptions) {
        Button('AVOID_AROUND_TARGET')
          .onClick(() => {
            this.handlePopup2 = !this.handlePopup2;
          })
          .bindPopup(this.handlePopup2, {
            builder: this.PopupBuilder,
            placement: Placement.Bottom,
            enableArrow: true,
            avoidTarget: AvoidanceMode.AVOID_AROUND_TARGET,
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup2 = false;
              }
            }
          })
        Button('un')
          .onClick(() => {
            this.handlePopup3 = !this.handlePopup3;
          })
          .bindPopup(this.handlePopup3, {
            builder: this.PopupBuilder,
            placement: Placement.Bottom,
            enableArrow: true,
            avoidTarget: undefined,
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup3 = false;
              }
            }
          })
      }

      Row({ space: 5 } as RowOptions) {
        Button('popup')
          .onClick(() => {
            this.handlePopup = !this.handlePopup;
          })
          .bindPopup(this.handlePopup, {
            builder: this.PopupBuilder,
            placement: Placement.Bottom,
            enableArrow: true,
            avoidTarget: this.avoidTargetList[this.avoidTargetIndex],
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup = false;
              }
            }
          })
        Button('动态切换 : ' + this.avoidTargetList[this.avoidTargetIndex])
          .onClick(() => {
            setTimeout(() => {
              this.avoidTargetIndex++
              if (this.avoidTargetIndex >= this.avoidTargetList.length) {
                this.avoidTargetIndex = 0
              }
            }, 2000)
          })
      }

      Text(`enableArrow设置为false:`)
        .fontSize(16)
        .width('100%')
      Row({ space: 5 } as RowOptions) {
        Button('COVER_TARGET')
          .onClick(() => {
            this.handlePopup10 = !this.handlePopup10;
          })
          .bindPopup(this.handlePopup10, {
            builder: this.PopupBuilder,
            placement: Placement.Bottom,
            enableArrow: false,
            avoidTarget: AvoidanceMode.COVER_TARGET,
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup10 = false;
              }
            }
          })
      }

      Row({ space: 5 } as RowOptions) {
        Button('AVOID_AROUND_TARGET')
          .onClick(() => {
            this.handlePopup11 = !this.handlePopup11;
          })
          .bindPopup(this.handlePopup11, {
            builder: this.PopupBuilder,
            placement: Placement.Bottom,
            enableArrow: false,
            avoidTarget: AvoidanceMode.AVOID_AROUND_TARGET,
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup11 = false;
              }
            }
          })
        Button('un')
          .onClick(() => {
            this.handlePopup12 = !this.handlePopup12;
          })
          .bindPopup(this.handlePopup12, {
            builder: this.PopupBuilder,
            placement: Placement.Bottom,
            enableArrow: false,
            avoidTarget: undefined,
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup12 = false;
              }
            }
          })
      }

      Row({ space: 5 } as RowOptions) {
        Button('popup')
          .onClick(() => {
            this.handlePopup19 = !this.handlePopup19;
          })
          .bindPopup(this.handlePopup19, {
            builder: this.PopupBuilder,
            placement: Placement.Bottom,
            enableArrow: false,
            avoidTarget: this.avoidTargetList1[this.avoidTargetIndex1],
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup19 = false;
              }
            }
          })
        Button('动态切换 : ' + this.avoidTargetList1[this.avoidTargetIndex1])
          .onClick(() => {
            setTimeout(() => {
              this.avoidTargetIndex1++
              if (this.avoidTargetIndex1 >= this.avoidTargetList1.length) {
                this.avoidTargetIndex1 = 0
              }
            }, 2000)
          })
      }
    }.margin(20)
  }
}