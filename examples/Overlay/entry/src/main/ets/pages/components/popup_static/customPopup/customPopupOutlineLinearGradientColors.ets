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
struct CustomPopupOutlineLinearGradientColors {
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
  @State outlineLinearGradientIndex: Int = 0;
  @State outlineLinearGradientList: Array<PopupBorderLinearGradient | undefined> =
    new Array<PopupBorderLinearGradient | undefined>(
      { direction: GradientDirection.None, colors: [[Color.Yellow, 0.0], [Color.Green, 1.0]] },
      { direction: GradientDirection.None, colors: [[undefined, 0.0], [Color.Blue, 1.0]] } as PopupBorderLinearGradient,
      { direction: GradientDirection.None, colors: [[0xc6d40d, 0.5]] },
      {
        direction: GradientDirection.None,
        colors: [['rgb(255, 100, 255)', 0.0], [Color.Green, 0.5], [Color.Blue, 1.0]]
      },
      {
        direction: GradientDirection.None,
        colors: [['rgba(33, 23, 169, 0.50)', 0.0], [Color.Green, 0.1], [Color.Blue, 1.0]]
      },
      {
        direction: GradientDirection.None,
        colors: [[$r("app.string.error"), 0.0], [Color.Pink, 0.5], [Color.Blue, 1.0]]
      },
      { direction: GradientDirection.None, colors: [[Color.Pink, -1], [Color.Blue, 1.0]] },
      { direction: GradientDirection.None, colors: [[$r("app.color.color"), 0.0], [Color.Blue, 0.33]] },
      { direction: GradientDirection.None, colors: [['#3317A98D', 0.0], [Color.Blue, 0.88]] },
      { direction: GradientDirection.None, colors: [[Color.Pink, 0.0], [Color.Blue, 10]] },
    )
  @State outlineLinearGradientIndex1: Int = 0;
  @State outlineLinearGradientList1: Array<PopupBorderLinearGradient | undefined> =
    new Array<PopupBorderLinearGradient | undefined>(
      { direction: GradientDirection.None, colors: [[Color.Yellow, 0.0], [Color.Green, 1.0]] },
      { direction: GradientDirection.None, colors: [[undefined, 0.0], [Color.Blue, 1.0]] } as PopupBorderLinearGradient,
      { direction: GradientDirection.None, colors: [[0xc6d40d, 0.5]] },
      {
        direction: GradientDirection.None,
        colors: [['rgb(255, 100, 255)', 0.0], [Color.Green, 0.5], [Color.Blue, 1.0]]
      },
      {
        direction: GradientDirection.None,
        colors: [['rgba(33, 23, 169, 0.50)', 0.0], [Color.Green, 0.1], [Color.Blue, 1.0]]
      },
      {
        direction: GradientDirection.None,
        colors: [[$r("app.string.error"), 0.0], [Color.Pink, 0.5], [Color.Blue, 1.0]]
      },
      { direction: GradientDirection.None, colors: [[Color.Pink, -1], [Color.Blue, 1.0]] },
      { direction: GradientDirection.None, colors: [[$r("app.color.color"), 0.0], [Color.Blue, 0.33]] },
      { direction: GradientDirection.None, colors: [['#3317A98D', 0.0], [Color.Blue, 0.88]] },
      { direction: GradientDirection.None, colors: [[Color.Pink, 0.0], [Color.Blue, 10]] },
    )
  @State outlineLinearGradientIndex2: Int = 0;
  @State outlineLinearGradientList2: Array<PopupBorderLinearGradient | undefined> =
    new Array<PopupBorderLinearGradient | undefined>(
      { direction: GradientDirection.None, colors: [[Color.Yellow, 0.0], [Color.Green, 1.0]] },
      { direction: GradientDirection.None, colors: [[undefined, 0.0], [Color.Blue, 1.0]] } as PopupBorderLinearGradient,
      { direction: GradientDirection.None, colors: [[0xc6d40d, 0.5]] },
      {
        direction: GradientDirection.None,
        colors: [['rgb(255, 100, 255)', 0.0], [Color.Green, 0.5], [Color.Blue, 1.0]]
      },
      {
        direction: GradientDirection.None,
        colors: [['rgba(33, 23, 169, 0.50)', 0.0], [Color.Green, 0.1], [Color.Blue, 1.0]]
      },
      {
        direction: GradientDirection.None,
        colors: [[$r("app.string.error"), 0.0], [Color.Pink, 0.5], [Color.Blue, 1.0]]
      },
      { direction: GradientDirection.None, colors: [[Color.Pink, -1], [Color.Blue, 1.0]] },
      { direction: GradientDirection.None, colors: [[$r("app.color.color"), 0.0], [Color.Blue, 0.33]] },
      { direction: GradientDirection.None, colors: [['#3317A98D', 0.0], [Color.Blue, 0.88]] },
      { direction: GradientDirection.None, colors: [[Color.Pink, 0.0], [Color.Blue, 10]] },
    )
  @State borderLinearGradientIndex: Int = 0;
  @State borderLinearGradientList: Array<PopupBorderLinearGradient | undefined> =
    new Array<PopupBorderLinearGradient | undefined>(
      { direction: GradientDirection.None, colors: [[Color.Orange, 0.0], [Color.Red, 1.0]] },
      { direction: GradientDirection.None, colors: [[Color.Red, 0.0], [undefined, 1.0]] } as PopupBorderLinearGradient,
      { direction: GradientDirection.None, colors: [[0xc6d40d, 0.5]] },
      { direction: GradientDirection.None, colors: [['rgb(255, 100, 255)', 0.0], ['#800080', 0.5], [Color.Red, 1.0]] },
      {
        direction: GradientDirection.None,
        colors: [['rgba(33, 23, 169, 0.50)', 0.0], ['#800080', 0.1], [Color.Red, 1.0]]
      },
      {
        direction: GradientDirection.None,
        colors: [[$r("app.string.error"), 0.0], [Color.Pink, 0.5], [Color.Red, 1.0]]
      },
      { direction: GradientDirection.None, colors: [[Color.Pink, -1], [Color.Blue, 1.0]] },
      { direction: GradientDirection.None, colors: [[$r("app.color.color"), 0.0], [Color.Blue, 0.33]] },
      { direction: GradientDirection.None, colors: [['#3317A98D', 0.0], [Color.Blue, 0.88]] },
      { direction: GradientDirection.None, colors: [[Color.Pink, 0.0], [Color.Blue, 10]] },
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
        Button('Color_2_1.0')
          .onClick(() => {
            this.handlePopup1 = !this.handlePopup1;
          })
          .bindPopup(this.handlePopup1, {
            builder: this.PopupBuilder,
            placement: Placement.Bottom,
            enableArrow: true,
            outlineWidth: 10,
            outlineLinearGradient: {
              direction: GradientDirection.None,
              colors: [[Color.Yellow, 0.0], [Color.Green, 1.0]]
            },
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup1 = false;
              }
            }

          })
        Button('Num_1_0.5')
          .onClick(() => {
            this.handlePopup2 = !this.handlePopup2;
          })
          .bindPopup(this.handlePopup2, {
            builder: this.PopupBuilder,
            placement: Placement.Bottom,
            enableArrow: true,
            outlineWidth: 10,
            outlineLinearGradient: {
              direction: GradientDirection.None,
              colors: [[0xc6d40d, 0.5]]
            },
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup2 = false;
              }
            }

          })
        Button('Rgb_3_0.5')
          .onClick(() => {
            this.handlePopup3 = !this.handlePopup3;
          })
          .bindPopup(this.handlePopup3, {
            builder: this.PopupBuilder,
            placement: Placement.Bottom,
            enableArrow: true,
            outlineWidth: 10,
            outlineLinearGradient: {
              direction: GradientDirection.None,
              colors: [['rgb(255, 100, 255)', 0.0], [Color.Green, 0.5], [Color.Blue, 1.0]]
            },
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup3 = false;
              }
            }

          })
      }

      Row({ space: 5 } as RowOptions) {
        Button('Rgba_3_0.1')
          .onClick(() => {
            this.handlePopup4 = !this.handlePopup4;
          })
          .bindPopup(this.handlePopup4, {
            builder: this.PopupBuilder,
            placement: Placement.Bottom,
            enableArrow: true,
            outlineWidth: 10,
            outlineLinearGradient: {
              direction: GradientDirection.None,
              colors: [['rgba(33, 23, 169, 0.50)', 0.0], [Color.Green, 0.1], [Color.Blue, 1.0]]
            },
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup4 = false;
              }
            }

          })
        Button('$rError_3_0.5')
          .onClick(() => {
            this.handlePopup5 = !this.handlePopup5;
          })
          .bindPopup(this.handlePopup5, {
            builder: this.PopupBuilder,
            placement: Placement.Bottom,
            enableArrow: true,
            outlineWidth: 10,
            outlineLinearGradient: {
              direction: GradientDirection.None,
              colors: [[$r("app.string.error"), 0.0], [Color.Pink, 0.5], [Color.Blue, 1.0]]
            },
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup5 = false;
              }
            }

          })
        Button('Color_2_-1')
          .onClick(() => {
            this.handlePopup6 = !this.handlePopup6;
          })
          .bindPopup(this.handlePopup6, {
            builder: this.PopupBuilder,
            placement: Placement.Bottom,
            enableArrow: true,
            outlineWidth: 10,
            outlineLinearGradient: {
              direction: GradientDirection.None,
              colors: [[Color.Pink, -1], [Color.Blue, 1.0]]
            },
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup6 = false;
              }
            }

          })
      }

      Row({ space: 5 } as RowOptions) {
        Button('$r_2_0.33')
          .onClick(() => {
            this.handlePopup7 = !this.handlePopup7;
          })
          .bindPopup(this.handlePopup7, {
            builder: this.PopupBuilder,
            placement: Placement.Bottom,
            enableArrow: true,
            outlineWidth: 10,
            outlineLinearGradient: {
              direction: GradientDirection.None,
              colors: [[$r("app.color.color"), 0.0], [Color.Blue, 0.33]]
            },
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup7 = false;
              }
            }

          })
        Button('Str_2_0.88')
          .onClick(() => {
            this.handlePopup8 = !this.handlePopup8;
          })
          .bindPopup(this.handlePopup8, {
            builder: this.PopupBuilder,
            placement: Placement.Bottom,
            enableArrow: true,
            outlineWidth: 10,
            outlineLinearGradient: {
              direction: GradientDirection.None,
              colors: [['#3317A98D', 0.0], [Color.Blue, 0.88]]
            },
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup8 = false;
              }
            }

          })
        Button('Color_2_10')
          .onClick(() => {
            this.handlePopup9 = !this.handlePopup9;
          })
          .bindPopup(this.handlePopup9, {
            builder: this.PopupBuilder,
            placement: Placement.Bottom,
            enableArrow: true,
            outlineWidth: 10,
            outlineLinearGradient: {
              direction: GradientDirection.None,
              colors: [[Color.Pink, 0.0], [Color.Blue, 10]]
            },
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup9 = false;
              }
            }

          })
      }

      Row({ space: 5 } as RowOptions) {
        Button('undefined')
          .onClick(() => {
            this.handlePopup20 = !this.handlePopup20;
          })
          .bindPopup(this.handlePopup20, {
            builder: this.PopupBuilder,
            placement: Placement.Bottom,
            enableArrow: true,
            outlineWidth: 10,
            outlineLinearGradient: {
              direction: GradientDirection.None,
              colors: [[undefined, 0.0], [Color.Blue, 1.0]]
            } as PopupBorderLinearGradient,
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup20 = false;
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
            outlineWidth: 10,
            outlineLinearGradient: this.outlineLinearGradientList[this.outlineLinearGradientIndex],
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup = false;
              }
            }

          })
        Button("动态切换 : " + this.outlineLinearGradientIndex)
          .onClick(() => {
            setTimeout(() => {
              this.outlineLinearGradientIndex++
              if (this.outlineLinearGradientIndex >= this.outlineLinearGradientList.length) {
                this.outlineLinearGradientIndex = 0
              }
            }, 2000)
          })
      }

      Text(`enableArrow设置为false:`)
        .fontSize(16)
        .width("100%")
      Row({ space: 5 } as RowOptions) {
        Button('Color_2_1.0')
          .onClick(() => {
            this.handlePopup10 = !this.handlePopup10;
          })
          .bindPopup(this.handlePopup10, {
            builder: this.PopupBuilder,
            placement: Placement.Bottom,
            enableArrow: false,
            outlineWidth: 10,
            outlineLinearGradient: {
              direction: GradientDirection.None,
              colors: [[Color.Yellow, 0.0], [Color.Green, 1.0]]
            },
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup10 = false;
              }
            }

          })
        Button('Num_1_0.5')
          .onClick(() => {
            this.handlePopup11 = !this.handlePopup11;
          })
          .bindPopup(this.handlePopup11, {
            builder: this.PopupBuilder,
            placement: Placement.Bottom,
            enableArrow: false,
            outlineWidth: 10,
            outlineLinearGradient: {
              direction: GradientDirection.None,
              colors: [[0xc6d40d, 0.5]]
            },
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup11 = false;
              }
            }

          })
        Button('Rgb_3_0.5')
          .onClick(() => {
            this.handlePopup12 = !this.handlePopup12;
          })
          .bindPopup(this.handlePopup12, {
            builder: this.PopupBuilder,
            placement: Placement.Bottom,
            enableArrow: false,
            outlineWidth: 10,
            outlineLinearGradient: {
              direction: GradientDirection.None,
              colors: [['rgb(255, 100, 255)', 0.0], [Color.Green, 0.5], [Color.Blue, 1.0]]
            },
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup12 = false;
              }
            }

          })
      }

      Row({ space: 5 } as RowOptions) {
        Button('Rgba_3_0.1')
          .onClick(() => {
            this.handlePopup13 = !this.handlePopup13;
          })
          .bindPopup(this.handlePopup13, {
            builder: this.PopupBuilder,
            placement: Placement.Bottom,
            enableArrow: false,
            outlineWidth: 10,
            outlineLinearGradient: {
              direction: GradientDirection.None,
              colors: [['rgba(33, 23, 169, 0.50)', 0.0], [Color.Green, 0.1], [Color.Blue, 1.0]]
            },
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup13 = false;
              }
            }

          })
        Button('$rError_3_0.5')
          .onClick(() => {
            this.handlePopup14 = !this.handlePopup14;
          })
          .bindPopup(this.handlePopup14, {
            builder: this.PopupBuilder,
            placement: Placement.Bottom,
            enableArrow: false,
            outlineWidth: 10,
            outlineLinearGradient: {
              direction: GradientDirection.None,
              colors: [[$r("app.string.error"), 0.0], [Color.Pink, 0.5], [Color.Blue, 1.0]]
            },
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup14 = false;
              }
            }

          })
        Button('Color_2_-1')
          .onClick(() => {
            this.handlePopup15 = !this.handlePopup15;
          })
          .bindPopup(this.handlePopup15, {
            builder: this.PopupBuilder,
            placement: Placement.Bottom,
            enableArrow: false,
            outlineWidth: 10,
            outlineLinearGradient: {
              direction: GradientDirection.None,
              colors: [[Color.Pink, -1], [Color.Blue, 1.0]]
            },
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup15 = false;
              }
            }

          })
      }

      Row({ space: 5 } as RowOptions) {
        Button('$r_2_0.33')
          .onClick(() => {
            this.handlePopup16 = !this.handlePopup16;
          })
          .bindPopup(this.handlePopup16, {
            builder: this.PopupBuilder,
            placement: Placement.Bottom,
            enableArrow: false,
            outlineWidth: 10,
            outlineLinearGradient: {
              direction: GradientDirection.None,
              colors: [[$r("app.color.color"), 0.0], [Color.Blue, 0.33]]
            },
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup16 = false;
              }
            }

          })
        Button('Str_2_0.88')
          .onClick(() => {
            this.handlePopup17 = !this.handlePopup17;
          })
          .bindPopup(this.handlePopup17, {
            builder: this.PopupBuilder,
            placement: Placement.Bottom,
            enableArrow: false,
            outlineWidth: 10,
            outlineLinearGradient: {
              direction: GradientDirection.None,
              colors: [['#3317A98D', 0.0], [Color.Blue, 0.88]]
            },
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup17 = false;
              }
            }

          })
        Button('Color_2_10')
          .onClick(() => {
            this.handlePopup18 = !this.handlePopup18;
          })
          .bindPopup(this.handlePopup18, {
            builder: this.PopupBuilder,
            placement: Placement.Bottom,
            enableArrow: false,
            outlineWidth: 10,
            outlineLinearGradient: {
              direction: GradientDirection.None,
              colors: [[Color.Pink, 0.0], [Color.Blue, 10]]
            },
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup18 = false;
              }
            }

          })
      }

      Row({ space: 5 } as RowOptions) {
        Button('undefined')
          .onClick(() => {
            this.handlePopup22 = !this.handlePopup22;
          })
          .bindPopup(this.handlePopup22, {
            builder: this.PopupBuilder,
            placement: Placement.Bottom,
            enableArrow: false,
            outlineWidth: 10,
            outlineLinearGradient: {
              direction: GradientDirection.None,
              colors: [[undefined, 0.0], [Color.Blue, 1.0]]
            },
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup22 = false;
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
            outlineWidth: 10,
            outlineLinearGradient: this.outlineLinearGradientList1[this.outlineLinearGradientIndex1],
            onStateChange: (event: PopupStateChangeParam) => {
              if (!event.isVisible) {
                this.handlePopup19 = false;
              }
            }

          })
        Button("动态切换 : " + this.outlineLinearGradientIndex1)
          .onClick(() => {
            setTimeout(() => {
              this.outlineLinearGradientIndex1++
              if (this.outlineLinearGradientIndex1 >= this.outlineLinearGradientList1.length) {
                this.outlineLinearGradientIndex1 = 0
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
          outlineWidth: 10,
          outlineLinearGradient: this.outlineLinearGradientList2[this.outlineLinearGradientIndex2],
          borderWidth: 10,
          borderLinearGradient: this.borderLinearGradientList[this.borderLinearGradientIndex],
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
          outlineWidth: 10,
          outlineLinearGradient: this.outlineLinearGradientList2[this.outlineLinearGradientIndex2],
          borderWidth: 10,
          borderLinearGradient: this.borderLinearGradientList[this.borderLinearGradientIndex],
          onStateChange: (event: PopupStateChangeParam) => {
            if (!event.isVisible) {
              this.handlePopup25 = false;
            }
          }
        })
      Button("动态切换outlineLinearGradient_colors : " + this.outlineLinearGradientIndex2)
        .onClick(() => {
          this.outlineLinearGradientIndex2++
          if (this.outlineLinearGradientIndex2 >= this.outlineLinearGradientList2.length) {
            this.outlineLinearGradientIndex2 = 0
          }
        })
      Button("动态切换borderLinearGradient_colors : " + this.borderLinearGradientIndex)
        .onClick(() => {
          this.borderLinearGradientIndex++
          if (this.borderLinearGradientIndex >= this.borderLinearGradientList.length) {
            this.borderLinearGradientIndex = 0
          }
        })
    }.margin(20)
  }
}