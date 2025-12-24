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
struct CustomPopupOutlineWidth {
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
  @State outlineWidthIndex: Int = 0;
  @State outlineWidthList: Array<Dimension | undefined> = new Array<Dimension | undefined>(
    '1vp',
    '10vp',
    undefined,
    0,
    -1,
    '2px',
    '3.9fp',
    '5vp',
    '10lpx',
    1000,
    $r("app.string.width"),
    $r("app.string.error")
  )
  @State outlineWidthIndex1: Int = 0;
  @State outlineWidthList1: Array<Dimension | undefined> = new Array<Dimension | undefined>(
    '1vp',
    '10vp',
    undefined,
    0,
    -1,
    '2px',
    '3.9fp',
    '5vp',
    '10lpx',
    1000,
    $r("app.string.width"),
    $r("app.string.error")
  )
  @State outlineWidthIndex2: Int = 0;
  @State outlineWidthList2: Array<Dimension | undefined> = new Array<Dimension | undefined>(
    '2vp',
    '5vp',
    '10vp',
    undefined,
    0,
    -1,
    '2px',
    '3.9fp',
    '5vp',
    '10lpx',
    1000,
    $r("app.string.width"),
    $r("app.string.error")
  )
  @State borderWidthIndex: Int = 0;
  @State borderWidthList: Array<Dimension | undefined> = new Array<Dimension | undefined>(
    '2vp',
    '5vp',
    '10vp',
    undefined,
    0,
    -1,
    '2px',
    '3.9fp',
    '5vp',
    '10lpx',
    1000,
    $r("app.string.width"),
    $r("app.string.error")
  )

  @Builder
  PopupBuilder() {
    Scroll(new Scroller()) {
      Column({ space: 5 } as ColumnOptions) {
        Text('This is a popup with PopupOptionsThis is a popup with PopupOptionsThis is a popup with PopupOptions' +
          'This is a popup with PopupOptionsThis is a popup with PopupOptionsThis is a popup with PopupOptions')
      }
    }
  }

  build() {
    Column({ space: 5 } as ColumnOptions) {
      Text(`enableArrow设置为true:`)
        .fontSize(16)
        .width("100%")
      Row({ space: 5 } as RowOptions) {
        Button('10vp')
          .onClick(() => {
            this.handlePopup1 = !this.handlePopup1;
          })
          .bindPopup(this.handlePopup1, {
            builder: this.PopupBuilder,
            placement: Placement.Bottom,
            enableArrow: true,
            outlineWidth: '10vp',
            outlineLinearGradient: {
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
            builder: this.PopupBuilder,
            placement: Placement.Bottom,
            enableArrow: true,
            outlineWidth: 0,
            outlineLinearGradient: {
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
            builder: this.PopupBuilder,
            placement: Placement.Bottom,
            enableArrow: true,
            outlineWidth: '2px',
            outlineLinearGradient: {
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
            builder: this.PopupBuilder,
            placement: Placement.Bottom,
            enableArrow: true,
            outlineWidth: '3.9fp',
            outlineLinearGradient: {
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
            builder: this.PopupBuilder,
            placement: Placement.Bottom,
            enableArrow: true,
            outlineWidth: '5vp',
            outlineLinearGradient: {
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
            builder: this.PopupBuilder,
            placement: Placement.Bottom,
            enableArrow: true,
            outlineWidth: '10lpx',
            outlineLinearGradient: {
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
            builder: this.PopupBuilder,
            placement: Placement.Bottom,
            enableArrow: true,
            outlineWidth: 1000,
            outlineLinearGradient: {
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
            builder: this.PopupBuilder,
            placement: Placement.Bottom,
            enableArrow: true,
            outlineWidth: -1,
            outlineLinearGradient: {
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
            builder: this.PopupBuilder,
            placement: Placement.Bottom,
            enableArrow: true,
            outlineWidth: $r("app.string.width"),
            outlineLinearGradient: {
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
            builder: this.PopupBuilder,
            placement: Placement.Bottom,
            enableArrow: true,
            outlineWidth: $r("app.string.error"),
            outlineLinearGradient: {
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
            builder: this.PopupBuilder,
            placement: Placement.Bottom,
            enableArrow: true,
            outlineWidth: undefined,
            outlineLinearGradient: {
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
            builder: this.PopupBuilder,
            placement: Placement.Bottom,
            enableArrow: true,
            outlineWidth: this.outlineWidthList[this.outlineWidthIndex],
            outlineLinearGradient: {
              direction: GradientDirection.None,
              colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
            },
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup = false;
              }
            }

          })
        Button("动态切换 : " + this.outlineWidthList[this.outlineWidthIndex])
          .onClick(() => {
            setTimeout(() => {
              this.outlineWidthIndex++
              if (this.outlineWidthIndex >= this.outlineWidthList.length) {
                this.outlineWidthIndex = 0
              }
            }, 2000)
          })
      }

      Text(`enableArrow设置为false:`)
        .fontSize(16)
        .width("100%")
      Row({ space: 5 } as RowOptions) {
        Button('10vp')
          .onClick(() => {
            this.handlePopup10 = !this.handlePopup10;
          })
          .bindPopup(this.handlePopup10, {
            builder: this.PopupBuilder,
            placement: Placement.Bottom,
            enableArrow: false,
            outlineWidth: '10vp',
            outlineLinearGradient: {
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
            builder: this.PopupBuilder,
            placement: Placement.Bottom,
            enableArrow: false,
            outlineWidth: 0,
            outlineLinearGradient: {
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
            builder: this.PopupBuilder,
            placement: Placement.Bottom,
            enableArrow: false,
            outlineWidth: '2px',
            outlineLinearGradient: {
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
            builder: this.PopupBuilder,
            placement: Placement.Bottom,
            enableArrow: false,
            outlineWidth: '3.9fp',
            outlineLinearGradient: {
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
            builder: this.PopupBuilder,
            placement: Placement.Bottom,
            enableArrow: false,
            outlineWidth: '5vp',
            outlineLinearGradient: {
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
            builder: this.PopupBuilder,
            placement: Placement.Bottom,
            enableArrow: false,
            outlineWidth: '10lpx',
            outlineLinearGradient: {
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
            builder: this.PopupBuilder,
            placement: Placement.Bottom,
            enableArrow: false,
            outlineWidth: 1000,
            outlineLinearGradient: {
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
            builder: this.PopupBuilder,
            placement: Placement.Bottom,
            enableArrow: false,
            outlineWidth: -1,
            outlineLinearGradient: {
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
            builder: this.PopupBuilder,
            placement: Placement.Bottom,
            enableArrow: false,
            outlineWidth: $r("app.string.width"),
            outlineLinearGradient: {
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
            builder: this.PopupBuilder,
            placement: Placement.Bottom,
            enableArrow: false,
            outlineWidth: $r("app.string.error"),
            outlineLinearGradient: {
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
            builder: this.PopupBuilder,
            placement: Placement.Bottom,
            enableArrow: false,
            outlineWidth: undefined,
            outlineLinearGradient: {
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
            builder: this.PopupBuilder,
            placement: Placement.Bottom,
            enableArrow: false,
            outlineWidth: this.outlineWidthList1[this.outlineWidthIndex1],
            outlineLinearGradient: {
              direction: GradientDirection.None,
              colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
            },
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup19 = false;
              }
            }

          })
        Button("动态切换 : " + this.outlineWidthList1[this.outlineWidthIndex1])
          .onClick(() => {
            setTimeout(() => {
              this.outlineWidthIndex1++
              if (this.outlineWidthIndex1 >= this.outlineWidthList1.length) {
                this.outlineWidthIndex1 = 0
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
          builder: this.PopupBuilder,
          placement: Placement.Bottom,
          enableArrow: false,
          outlineWidth: this.outlineWidthList2[this.outlineWidthIndex2],
          outlineLinearGradient: {
            direction: GradientDirection.None,
            colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
          },
          borderWidth: this.borderWidthList[this.borderWidthIndex],
          borderLinearGradient: {
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
          builder: this.PopupBuilder,
          placement: Placement.Bottom,
          enableArrow: true,
          outlineWidth: this.outlineWidthList2[this.outlineWidthIndex2],
          outlineLinearGradient: {
            direction: GradientDirection.None,
            colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
          },
          borderWidth: this.borderWidthList[this.borderWidthIndex],
          borderLinearGradient: {
            direction: GradientDirection.Left,
            colors: [[Color.Yellow, 0.0], [Color.Green, 1.0]]
          },
          onStateChange: (event: PopupStateChangeParam) => {
            if (!event.isVisible) {
              this.handlePopup25 = false;
            }
          }

        })
      Button("动态切换outlineWidth : " + this.outlineWidthList2[this.outlineWidthIndex2])
        .onClick(() => {
          this.outlineWidthIndex2++
          if (this.outlineWidthIndex2 >= this.outlineWidthList2.length) {
            this.outlineWidthIndex2 = 0
          }
        })
      Button("动态切换borderWidth : " + this.borderWidthList[this.borderWidthIndex])
        .onClick(() => {
          this.borderWidthIndex++
          if (this.borderWidthIndex >= this.borderWidthList.length) {
            this.borderWidthIndex = 0
          }
        })
    }.margin(20)
  }
}