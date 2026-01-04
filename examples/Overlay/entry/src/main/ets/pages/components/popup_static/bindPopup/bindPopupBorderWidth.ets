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
struct BindPopupBorderWidth {
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
  @State handlePopup20: boolean = false;
  @State handlePopup21: boolean = false;
  @State handlePopup22: boolean = false;
  @State handlePopup23: boolean = false;
  @State handlePopup24: boolean = false;
  @State handlePopup25: boolean = false;
  @State borderWidthIndex: Int = 0;
  @State borderWidthList: (Dimension | undefined)[] = [
    '1vp' as Dimension, '10vp' as Dimension, undefined, 0 as Dimension, -1 as Dimension, '2px' as Dimension,
    '3.9fp' as Dimension, '5vp' as Dimension, '10lpx' as Dimension, 1000 as Dimension,
    $r('app.string.width') as Dimension, $r('app.string.error') as Dimension,
  ]
  @State borderWidthIndex1: Int = 0;
  @State borderWidthList1: (Dimension | undefined)[] = [
    '1vp' as Dimension, '10vp' as Dimension, undefined, 0 as Dimension, -1 as Dimension, '2px' as Dimension,
    '3.9fp' as Dimension, '5vp' as Dimension, '10lpx' as Dimension, 1000 as Dimension,
    $r('app.string.width') as Dimension, $r('app.string.error') as Dimension,
  ]
  @State borderWidthIndex2: Int = 0;
  @State borderWidthList2: (Dimension | undefined)[] = [
    '2vp' as Dimension, '5vp' as Dimension, '10vp' as Dimension, undefined, 0 as Dimension, -1 as Dimension,
    '2px' as Dimension, '3.9fp' as Dimension, '5vp' as Dimension, '10lpx' as Dimension, 1000 as Dimension,
    $r('app.string.width') as Dimension, $r('app.string.error') as Dimension,
  ]
  @State outlineWidthIndex: Int = 0;
  @State outlineWidthList: (Dimension | undefined)[] = [
    '2vp' as Dimension, '5vp' as Dimension, '10vp' as Dimension, undefined, 0 as Dimension,
    -1 as Dimension, '2px' as Dimension, '3.9fp' as Dimension, '5vp' as Dimension, '10lpx' as Dimension,
    1000 as Dimension, $r('app.string.width') as Dimension, $r('app.string.error') as Dimension,
  ]

  build() {
    Column({ space: 5 } as ColumnOptions) {
      Text(`enableArrow设置为true:`)
        .fontSize(16)
        .width('100%')
      Row({ space: 5 } as RowOptions) {
        Button('10vp')
          .onClick(() => {
            this.handlePopup1 = !this.handlePopup1;
          })
          .bindPopup(this.handlePopup1, {
            message: this.message,
            placement: Placement.Bottom,
            enableArrow: true,
            borderWidth: '10vp',
            borderLinearGradient: {
              direction: GradientDirection.None,
              colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
            },
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup1 = false;
              }
            }
          })
        Button('0')
          .onClick(() => {
            this.handlePopup2 = !this.handlePopup2;
          })
          .bindPopup(this.handlePopup2, {
            message: this.message,
            placement: Placement.Bottom,
            enableArrow: true,
            borderWidth: 0,
            borderLinearGradient: {
              direction: GradientDirection.None,
              colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
            },
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup2 = false;
              }
            }
          })
        Button('2px')
          .onClick(() => {
            this.handlePopup3 = !this.handlePopup3;
          })
          .bindPopup(this.handlePopup3, {
            message: this.message,
            placement: Placement.Bottom,
            enableArrow: true,
            borderWidth: '2px',
            borderLinearGradient: {
              direction: GradientDirection.None,
              colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
            },
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup3 = false;
              }
            }
          })
        Button('3.9fp')
          .onClick(() => {
            this.handlePopup4 = !this.handlePopup4;
          })
          .bindPopup(this.handlePopup4, {
            message: this.message,
            placement: Placement.Bottom,
            enableArrow: true,
            borderWidth: '3.9fp',
            borderLinearGradient: {
              direction: GradientDirection.None,
              colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
            },
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup4 = false;
              }
            }
          })
        Button('5vp')
          .onClick(() => {
            this.handlePopup5 = !this.handlePopup5;
          })
          .bindPopup(this.handlePopup5, {
            message: this.message,
            placement: Placement.Bottom,
            enableArrow: true,
            borderWidth: '5vp',
            borderLinearGradient: {
              direction: GradientDirection.None,
              colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
            },
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup5 = false;
              }
            }
          })
      }

      Row({ space: 5 } as RowOptions) {
        Button('10lpx')
          .onClick(() => {
            this.handlePopup6 = !this.handlePopup6;
          })
          .bindPopup(this.handlePopup6, {
            message: this.message,
            placement: Placement.Bottom,
            enableArrow: true,
            borderWidth: '10lpx',
            borderLinearGradient: {
              direction: GradientDirection.None,
              colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
            },
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup6 = false;
              }
            }
          })
        Button('1000')
          .onClick(() => {
            this.handlePopup7 = !this.handlePopup7;
          })
          .bindPopup(this.handlePopup7, {
            message: this.message,
            placement: Placement.Bottom,
            enableArrow: true,
            borderWidth: 1000,
            borderLinearGradient: {
              direction: GradientDirection.None,
              colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
            },
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup7 = false;
              }
            }
          })
        Button('-1')
          .onClick(() => {
            this.handlePopup8 = !this.handlePopup8;
          })
          .bindPopup(this.handlePopup8, {
            message: this.message,
            placement: Placement.Bottom,
            enableArrow: true,
            borderWidth: -1,
            borderLinearGradient: {
              direction: GradientDirection.None,
              colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
            },
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup8 = false;
              }
            }
          })
        Button('app.string.width')
          .onClick(() => {
            this.handlePopup9 = !this.handlePopup9;
          })
          .bindPopup(this.handlePopup9, {
            message: this.message,
            placement: Placement.Bottom,
            enableArrow: true,
            borderWidth: $r('app.string.width'),
            borderLinearGradient: {
              direction: GradientDirection.None,
              colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
            },
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup9 = false;
              }
            }
          })
      }

      Row({ space: 5 } as RowOptions) {
        Button('app.string.error')
          .onClick(() => {
            this.handlePopup20 = !this.handlePopup20;
          })
          .bindPopup(this.handlePopup20, {
            message: this.message,
            placement: Placement.Bottom,
            enableArrow: true,
            borderWidth: $r('app.string.error'),
            borderLinearGradient: {
              direction: GradientDirection.None,
              colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
            },
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup20 = false;
              }
            }
          })
        Button('undefined')
          .onClick(() => {
            this.handlePopup21 = !this.handlePopup21;
          })
          .bindPopup(this.handlePopup21, {
            message: this.message,
            placement: Placement.Bottom,
            enableArrow: true,
            borderWidth: undefined,
            borderLinearGradient: {
              direction: GradientDirection.None,
              colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
            },
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup21 = false;
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
            message: this.message,
            placement: Placement.Bottom,
            enableArrow: true,
            borderWidth: this.borderWidthList[this.borderWidthIndex],
            borderLinearGradient: {
              direction: GradientDirection.None,
              colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
            },
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup = false;
              }
            }
          })
        Button('动态切换 : ' + this.borderWidthList[this.borderWidthIndex])
          .onClick(() => {
            setTimeout(() => {
              this.borderWidthIndex++
              if (this.borderWidthIndex >= this.borderWidthList.length) {
                this.borderWidthIndex = 0
              }
            }, 2000)
          })
      }

      Text(`enableArrow设置为false:`)
        .fontSize(16)
        .width('100%')
      Row({ space: 5 } as RowOptions) {
        Button('10vp')
          .onClick(() => {
            this.handlePopup10 = !this.handlePopup10;
          })
          .bindPopup(this.handlePopup10, {
            message: this.message,
            placement: Placement.Bottom,
            enableArrow: false,
            borderWidth: '10vp',
            borderLinearGradient: {
              direction: GradientDirection.None,
              colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
            },
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup10 = false;
              }
            }
          })
        Button('0')
          .onClick(() => {
            this.handlePopup11 = !this.handlePopup11;
          })
          .bindPopup(this.handlePopup11, {
            message: this.message,
            placement: Placement.Bottom,
            enableArrow: false,
            borderWidth: 0,
            borderLinearGradient: {
              direction: GradientDirection.None,
              colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
            },
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup11 = false;
              }
            }
          })
        Button('2px')
          .onClick(() => {
            this.handlePopup12 = !this.handlePopup12;
          })
          .bindPopup(this.handlePopup12, {
            message: this.message,
            placement: Placement.Bottom,
            enableArrow: false,
            borderWidth: '2px',
            borderLinearGradient: {
              direction: GradientDirection.None,
              colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
            },
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup12 = false;
              }
            }
          })
        Button('3.9fp')
          .onClick(() => {
            this.handlePopup13 = !this.handlePopup13;
          })
          .bindPopup(this.handlePopup13, {
            message: this.message,
            placement: Placement.Bottom,
            enableArrow: false,
            borderWidth: '3.9fp',
            borderLinearGradient: {
              direction: GradientDirection.None,
              colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
            },
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup13 = false;
              }
            }
          })
        Button('5vp')
          .onClick(() => {
            this.handlePopup14 = !this.handlePopup14;
          })
          .bindPopup(this.handlePopup14, {
            message: this.message,
            placement: Placement.Bottom,
            enableArrow: false,
            borderWidth: '5vp',
            borderLinearGradient: {
              direction: GradientDirection.None,
              colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
            },
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup14 = false;
              }
            }
          })
      }

      Row({ space: 5 } as RowOptions) {
        Button('10lpx')
          .onClick(() => {
            this.handlePopup15 = !this.handlePopup15;
          })
          .bindPopup(this.handlePopup15, {
            message: this.message,
            placement: Placement.Bottom,
            enableArrow: false,
            borderWidth: '10lpx',
            borderLinearGradient: {
              direction: GradientDirection.None,
              colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
            },
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup15 = false;
              }
            }
          })
        Button('1000')
          .onClick(() => {
            this.handlePopup16 = !this.handlePopup16;
          })
          .bindPopup(this.handlePopup16, {
            message: this.message,
            placement: Placement.Bottom,
            enableArrow: false,
            borderWidth: 1000,
            borderLinearGradient: {
              direction: GradientDirection.None,
              colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
            },
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup16 = false;
              }
            }
          })
        Button('-1')
          .onClick(() => {
            this.handlePopup17 = !this.handlePopup17;
          })
          .bindPopup(this.handlePopup17, {
            message: this.message,
            placement: Placement.Bottom,
            enableArrow: false,
            borderWidth: -1,
            borderLinearGradient: {
              direction: GradientDirection.None,
              colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
            },
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup17 = false;
              }
            }
          })
        Button('app.string.width')
          .onClick(() => {
            this.handlePopup18 = !this.handlePopup18;
          })
          .bindPopup(this.handlePopup18, {
            message: this.message,
            placement: Placement.Bottom,
            enableArrow: false,
            borderWidth: $r('app.string.width'),
            borderLinearGradient: {
              direction: GradientDirection.None,
              colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
            },
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup18 = false;
              }
            }
          })
      }

      Row({ space: 5 } as RowOptions) {
        Button('app.string.error')
          .onClick(() => {
            this.handlePopup22 = !this.handlePopup22;
          })
          .bindPopup(this.handlePopup22, {
            message: this.message,
            placement: Placement.Bottom,
            enableArrow: false,
            borderWidth: $r('app.string.error'),
            borderLinearGradient: {
              direction: GradientDirection.None,
              colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
            },
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup22 = false;
              }
            }
          })
        Button('undefined')
          .onClick(() => {
            this.handlePopup23 = !this.handlePopup23;
          })
          .bindPopup(this.handlePopup23, {
            message: this.message,
            placement: Placement.Bottom,
            enableArrow: false,
            borderWidth: undefined,
            borderLinearGradient: {
              direction: GradientDirection.None,
              colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
            },
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup23 = false;
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
            message: this.message,
            placement: Placement.Bottom,
            enableArrow: false,
            borderWidth: this.borderWidthList1[this.borderWidthIndex1],
            borderLinearGradient: {
              direction: GradientDirection.None,
              colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
            },
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup19 = false;
              }
            }
          })
        Button('动态切换 : ' + this.borderWidthList1[this.borderWidthIndex1])
          .onClick(() => {
            setTimeout(() => {
              this.borderWidthIndex1++
              if (this.borderWidthIndex1 >= this.borderWidthList1.length) {
                this.borderWidthIndex1 = 0
              }
            }, 2000)
          })
      }

      Text(`内外描边结合:`)
        .fontSize(16)
        .width('100%')
      Button('popup_false')
        .onClick(() => {
          this.handlePopup24 = !this.handlePopup24;
        })
        .bindPopup(this.handlePopup24, {
          message: this.message,
          placement: Placement.Bottom,
          enableArrow: false,
          borderWidth: this.borderWidthList2[this.borderWidthIndex2],
          borderLinearGradient: {
            direction: GradientDirection.None,
            colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
          },
          outlineWidth: this.outlineWidthList[this.outlineWidthIndex],
          outlineLinearGradient: {
            direction: GradientDirection.Left,
            colors: [[Color.Yellow, 0.0], [Color.Green, 1.0]]
          },
          onStateChange: (event: PopupStateChangeParam) => {
            if (!event.isVisible) {
              this.handlePopup24 = false;
            }
          }
        })
      Button('popup_true')
        .onClick(() => {
          this.handlePopup25 = !this.handlePopup25;
        })
        .bindPopup(this.handlePopup25, {
          message: this.message,
          placement: Placement.Bottom,
          enableArrow: true,
          borderWidth: this.borderWidthList2[this.borderWidthIndex2],
          borderLinearGradient: {
            direction: GradientDirection.None,
            colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
          },
          outlineWidth: this.outlineWidthList[this.outlineWidthIndex],
          outlineLinearGradient: {
            direction: GradientDirection.Left,
            colors: [[Color.Yellow, 0.0], [Color.Green, 1.0]]
          },
          onStateChange: (event: PopupStateChangeParam) => {
            if (!event.isVisible) {
              this.handlePopup25 = false;
            }
          }
        })
      Button('动态切换borderWidth : ' + this.borderWidthList2[this.borderWidthIndex2])
        .onClick(() => {
          this.borderWidthIndex2++
          if (this.borderWidthIndex2 >= this.borderWidthList2.length) {
            this.borderWidthIndex2 = 0
          }
        })
      Button('动态切换outlineWidth : ' + this.outlineWidthList[this.outlineWidthIndex])
        .onClick(() => {
          this.outlineWidthIndex++
          if (this.outlineWidthIndex >= this.outlineWidthList.length) {
            this.outlineWidthIndex = 0
          }
        })
    }.margin(20)
  }
}