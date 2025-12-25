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
import { Entry, Component, NavDestination, ClickEvent, Dimension, EdgeColors, Column, ColumnOptions, Row, RowOptions, Scroll, Scroller, Button, Text, Color, $r, Image, ResourceStr, ResourceColor,
  SubMenuExpandingMode, MenuOptions, ContextMenuOptions, MenuElement, Menu, MenuItem, MenuItemOptions, CustomDialog, PopupOptions, CustomPopupOptions, PopupCommonOptions, PopupStateChangeParam,
  EdgeOutlineWidths, wrapBuilder, AvoidanceMode, Placement, PopupMessageOptions, PopupBorderLinearGradient, GradientDirection, ContextMenuAnimationOptions, MenuPreviewMode, BlurStyle, ModalMode,
  PreviewScaleMode, AvailableLayoutArea, ResponseType, CustomDialogController, CustomBuilder, CustomBuilderT, FontWeight, Length, TextAlign, TransitionEffect, Curve,AnimationNumberRange, Margin,
  FlexAlign
} from '@ohos.arkui.component'
import { BusinessError } from '@kit.BasicServicesKit';
import { ComponentContent, FrameNode, Frame } from '@ohos.arkui.node';
import { UIContext, PromptAction, TargetInfo } from '@ohos.arkui.UIContext'
import { SymbolGlyphModifier } from 'arkui.SymbolGlyphModifier';
import promptAction from '@ohos.promptAction';
import hilog from '@ohos.hilog'

@Entry
@Component
struct BindPopupBorderLinearGradientDirection {
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
  @State borderLinearGradientIndex: Int = 0;
  @State borderLinearGradientList: Array<PopupBorderLinearGradient | undefined> =
    new Array<PopupBorderLinearGradient | undefined>(
      { direction: GradientDirection.Left, colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]] },
      { direction: undefined, colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]] },
      { direction: GradientDirection.Top, colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]] },
      { direction: GradientDirection.Right, colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]] },
      { direction: GradientDirection.Bottom, colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]] },
      { direction: GradientDirection.LeftTop, colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]] },
      { direction: GradientDirection.LeftBottom, colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]] },
      { direction: GradientDirection.RightTop, colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]] },
      { direction: GradientDirection.RightBottom, colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]] },
      { direction: GradientDirection.None, colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]] },
    )
  @State borderLinearGradientIndex1: Int = 0;
  @State borderLinearGradientList1: Array<PopupBorderLinearGradient | undefined> =
    new Array<PopupBorderLinearGradient | undefined>(
      { direction: GradientDirection.Left, colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]] },
      { direction: undefined, colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]] },
      { direction: GradientDirection.Top, colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]] },
      { direction: GradientDirection.Right, colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]] },
      { direction: GradientDirection.Bottom, colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]] },
      { direction: GradientDirection.LeftTop, colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]] },
      { direction: GradientDirection.LeftBottom, colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]] },
      { direction: GradientDirection.RightTop, colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]] },
      { direction: GradientDirection.RightBottom, colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]] },
      { direction: GradientDirection.None, colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]] },
    )
  @State borderLinearGradientIndex2: Int = 0;
  @State borderLinearGradientList2: Array<PopupBorderLinearGradient | undefined> =
    new Array<PopupBorderLinearGradient | undefined>(
      { direction: GradientDirection.Left, colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]] },
      { direction: undefined, colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]] },
      { direction: GradientDirection.Top, colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]] },
      { direction: GradientDirection.Right, colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]] },
      { direction: GradientDirection.Bottom, colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]] },
      { direction: GradientDirection.LeftTop, colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]] },
      { direction: GradientDirection.LeftBottom, colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]] },
      { direction: GradientDirection.RightTop, colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]] },
      { direction: GradientDirection.RightBottom, colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]] },
      { direction: GradientDirection.None, colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]] },
    )
  @State outlineLinearGradientIndex: Int = 0;
  @State outlineLinearGradientList: Array<PopupBorderLinearGradient | undefined> =
    new Array<PopupBorderLinearGradient | undefined>(
      { direction: GradientDirection.Left, colors: [[Color.Yellow, 0.0], [Color.Green, 1.0]] },
      { direction: undefined, colors: [[Color.Yellow, 0.0], [Color.Green, 1.0]] },
      { direction: GradientDirection.Top, colors: [[Color.Yellow, 0.0], [Color.Green, 1.0]] },
      { direction: GradientDirection.Right, colors: [[Color.Yellow, 0.0], [Color.Green, 1.0]] },
      { direction: GradientDirection.Bottom, colors: [[Color.Yellow, 0.0], [Color.Green, 1.0]] },
      { direction: GradientDirection.LeftTop, colors: [[Color.Yellow, 0.0], [Color.Green, 1.0]] },
      { direction: GradientDirection.LeftBottom, colors: [[Color.Yellow, 0.0], [Color.Green, 1.0]] },
      { direction: GradientDirection.RightTop, colors: [[Color.Yellow, 0.0], [Color.Green, 1.0]] },
      { direction: GradientDirection.RightBottom, colors: [[Color.Yellow, 0.0], [Color.Green, 1.0]] },
      { direction: GradientDirection.None, colors: [[Color.Yellow, 0.0], [Color.Green, 1.0]] },
    )

  build() {
    Column({ space: 5 } as ColumnOptions) {
      Text(`enableArrow设置为true:`)
        .fontSize(16)
        .width("100%")
      Row({ space: 5 } as RowOptions) {
        Button('Top')
          .onClick(() => {
            this.handlePopup1 = !this.handlePopup1;
          })
          .bindPopup(this.handlePopup1, {
            message: this.message,
            placement: Placement.Bottom,
            enableArrow: true,
            borderWidth: 10,
            borderLinearGradient: {
              direction: GradientDirection.Top,
              colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
            },
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup1 = false;
              }
            }

          })
        Button('Right')
          .onClick(() => {
            this.handlePopup2 = !this.handlePopup2;
          })
          .bindPopup(this.handlePopup2, {
            message: this.message,
            placement: Placement.Bottom,
            enableArrow: true,
            borderWidth: 10,
            borderLinearGradient: {
              direction: GradientDirection.Right,
              colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
            },
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup2 = false;
              }
            }

          })
        Button('Bottom')
          .onClick(() => {
            this.handlePopup3 = !this.handlePopup3;
          })
          .bindPopup(this.handlePopup3, {
            message: this.message,
            placement: Placement.Bottom,
            enableArrow: true,
            borderWidth: 10,
            borderLinearGradient: {
              direction: GradientDirection.Bottom,
              colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
            },
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup3 = false;
              }
            }

          })
        Button('LeftTop')
          .onClick(() => {
            this.handlePopup4 = !this.handlePopup4;
          })
          .bindPopup(this.handlePopup4, {
            message: this.message,
            placement: Placement.Bottom,
            enableArrow: true,
            borderWidth: 10,
            borderLinearGradient: {
              direction: GradientDirection.LeftTop,
              colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
            },
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup4 = false;
              }
            }

          })
      }

      Row({ space: 5 } as RowOptions) {
        Button('LeftBottom')
          .onClick(() => {
            this.handlePopup5 = !this.handlePopup5;
          })
          .bindPopup(this.handlePopup5, {
            message: this.message,
            placement: Placement.Bottom,
            enableArrow: true,
            borderWidth: 10,
            borderLinearGradient: {
              direction: GradientDirection.LeftBottom,
              colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
            },
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup5 = false;
              }
            }

          })
        Button('RightTop')
          .onClick(() => {
            this.handlePopup6 = !this.handlePopup6;
          })
          .bindPopup(this.handlePopup6, {
            message: this.message,
            placement: Placement.Bottom,
            enableArrow: true,
            borderWidth: 10,
            borderLinearGradient: {
              direction: GradientDirection.RightTop,
              colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
            },
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup6 = false;
              }
            }

          })
        Button('RightBottom')
          .onClick(() => {
            this.handlePopup7 = !this.handlePopup7;
          })
          .bindPopup(this.handlePopup7, {
            message: this.message,
            placement: Placement.Bottom,
            enableArrow: true,
            borderWidth: 10,
            borderLinearGradient: {
              direction: GradientDirection.RightBottom,
              colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
            },
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup7 = false;
              }
            }

          })
      }

      Row({ space: 5 } as RowOptions) {
        Button('None')
          .onClick(() => {
            this.handlePopup8 = !this.handlePopup8;
          })
          .bindPopup(this.handlePopup8, {
            message: this.message,
            placement: Placement.Bottom,
            enableArrow: true,
            borderWidth: 10,
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

        Button('undefined')
          .onClick(() => {
            this.handlePopup21 = !this.handlePopup21;
          })
          .bindPopup(this.handlePopup21, {
            message: this.message,
            placement: Placement.Bottom,
            enableArrow: true,
            borderWidth: 10,
            borderLinearGradient: {
              direction: undefined,
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
            borderWidth: 10,
            borderLinearGradient: this.borderLinearGradientList[this.borderLinearGradientIndex],
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup = false;
              }
            }

          })
        Button("动态切换 : " + this.borderLinearGradientIndex)
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
        .width("100%")
      Row({ space: 5 } as RowOptions) {
        Button('Top')
          .onClick(() => {
            this.handlePopup10 = !this.handlePopup10;
          })
          .bindPopup(this.handlePopup10, {
            message: this.message,
            placement: Placement.Bottom,
            enableArrow: false,
            borderWidth: 10,
            borderLinearGradient: {
              direction: GradientDirection.Top,
              colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
            },
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup10 = false;
              }
            }

          })
        Button('Right')
          .onClick(() => {
            this.handlePopup11 = !this.handlePopup11;
          })
          .bindPopup(this.handlePopup11, {
            message: this.message,
            placement: Placement.Bottom,
            enableArrow: false,
            borderWidth: 10,
            borderLinearGradient: {
              direction: GradientDirection.Right,
              colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
            },
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup11 = false;
              }
            }

          })
        Button('Bottom')
          .onClick(() => {
            this.handlePopup12 = !this.handlePopup12;
          })
          .bindPopup(this.handlePopup12, {
            message: this.message,
            placement: Placement.Bottom,
            enableArrow: false,
            borderWidth: 10,
            borderLinearGradient: {
              direction: GradientDirection.Bottom,
              colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
            },
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup12 = false;
              }
            }

          })
        Button('LeftTop')
          .onClick(() => {
            this.handlePopup13 = !this.handlePopup13;
          })
          .bindPopup(this.handlePopup13, {
            message: this.message,
            placement: Placement.Bottom,
            enableArrow: false,
            borderWidth: 10,
            borderLinearGradient: {
              direction: GradientDirection.LeftTop,
              colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
            },
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup13 = false;
              }
            }

          })
      }

      Row({ space: 5 } as RowOptions) {
        Button('LeftBottom')
          .onClick(() => {
            this.handlePopup14 = !this.handlePopup14;
          })
          .bindPopup(this.handlePopup14, {
            message: this.message,
            placement: Placement.Bottom,
            enableArrow: false,
            borderWidth: 10,
            borderLinearGradient: {
              direction: GradientDirection.LeftBottom,
              colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
            },
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup14 = false;
              }
            }

          })
        Button('RightTop')
          .onClick(() => {
            this.handlePopup15 = !this.handlePopup15;
          })
          .bindPopup(this.handlePopup15, {
            message: this.message,
            placement: Placement.Bottom,
            enableArrow: false,
            borderWidth: 10,
            borderLinearGradient: {
              direction: GradientDirection.RightTop,
              colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
            },
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup15 = false;
              }
            }

          })
        Button('RightBottom')
          .onClick(() => {
            this.handlePopup16 = !this.handlePopup16;
          })
          .bindPopup(this.handlePopup16, {
            message: this.message,
            placement: Placement.Bottom,
            enableArrow: false,
            borderWidth: 10,
            borderLinearGradient: {
              direction: GradientDirection.RightBottom,
              colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
            },
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup16 = false;
              }
            }

          })
      }

      Row({ space: 5 } as RowOptions) {
        Button('None')
          .onClick(() => {
            this.handlePopup17 = !this.handlePopup17;
          })
          .bindPopup(this.handlePopup17, {
            message: this.message,
            placement: Placement.Bottom,
            enableArrow: false,
            borderWidth: 10,
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
        Button('undefined')
          .onClick(() => {
            this.handlePopup23 = !this.handlePopup23;
          })
          .bindPopup(this.handlePopup23, {
            message: this.message,
            placement: Placement.Bottom,
            enableArrow: false,
            borderWidth: 10,
            borderLinearGradient: {
              direction: undefined,
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
            borderWidth: 10,
            borderLinearGradient: this.borderLinearGradientList1[this.borderLinearGradientIndex1],
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup19 = false;
              }
            }

          })
        Button("动态切换 : " + this.borderLinearGradientIndex1)
          .onClick(() => {
            setTimeout(() => {
              this.borderLinearGradientIndex1++
              if (this.borderLinearGradientIndex1 >= this.borderLinearGradientList1.length) {
                this.borderLinearGradientIndex1 = 0
              }
            }, 2000)
          })
      }

      Text(`内外描边结合:`)
        .fontSize(16)
        .width("100%")
      Button('popup_false')
        .onClick(() => {
          this.handlePopup24 = !this.handlePopup24;
        })
        .bindPopup(this.handlePopup24, {
          message: this.message,
          placement: Placement.Bottom,
          enableArrow: false,
          borderWidth: 10,
          borderLinearGradient: this.borderLinearGradientList2[this.borderLinearGradientIndex2],
          outlineWidth: 10,
          outlineLinearGradient: this.outlineLinearGradientList[this.outlineLinearGradientIndex],
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
          borderWidth: 10,
          borderLinearGradient: this.borderLinearGradientList2[this.borderLinearGradientIndex2],
          outlineWidth: 10,
          outlineLinearGradient: this.outlineLinearGradientList[this.outlineLinearGradientIndex],
          onStateChange: (event: PopupStateChangeParam) => {
            if (!event.isVisible) {
              this.handlePopup25 = false;
            }
          }
        })
      Button("动态切换borderLinearGradient_direction : " + this.borderLinearGradientIndex2)
        .onClick(() => {
          this.borderLinearGradientIndex2++
          if (this.borderLinearGradientIndex2 >= this.borderLinearGradientList2.length) {
            this.borderLinearGradientIndex2 = 0
          }
        })
      Button("动态切换outlineLinearGradient_direction : " + this.outlineLinearGradientIndex)
        .onClick(() => {
          this.outlineLinearGradientIndex++
          if (this.outlineLinearGradientIndex >= this.outlineLinearGradientList.length) {
            this.outlineLinearGradientIndex = 0
          }
        })
    }.margin(20)
  }
}