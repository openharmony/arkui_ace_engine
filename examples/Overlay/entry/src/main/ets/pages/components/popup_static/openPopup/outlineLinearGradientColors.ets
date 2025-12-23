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

@Builder
function PopupBuilder() {
  Scroll(new Scroller()) {
    Column({ space: 5 } as ColumnOptions) {
      Text('This is a popup with PopupOptionsThis is a popup with PopupOptionsThis is a popup with PopupOptions' +
        'This is a popup with PopupOptionsThis is a popup with PopupOptionsThis is a popup with PopupOptions,')
    }
  }
}

@Entry
@Component
struct OpenPopupOutlineLinearGradientColors {
  private uiContext: UIContext = this.getUIContext();
  private promptAction: PromptAction = this.uiContext.getPromptAction();
  private contentNode: ComponentContent = new ComponentContent(this.uiContext, wrapBuilder(PopupBuilder));
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

  build() {
    Column({ space: 5 } as ColumnOptions) {
      Text(`enableArrow设置为true:`)
        .fontSize(16)
        .width("100%")
      Row({ space: 5 } as RowOptions) {
        Button('Color_2_1.0')
          .id('1')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '1' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: true,
                outlineWidth: 10,
                outlineLinearGradient: {
                  direction: GradientDirection.None,
                  colors: [[Color.Yellow, 0.0], [Color.Green, 1.0]]
                },
              } as PopupCommonOptions).then(() => {
                console.info('---1130---openPopup success');
              })
                .catch((err: Error) => {
                  console.info('---1130---openPopup error：' + err.code + '+' + err.message);
                })
            } catch (error) {
              let message = (error as BusinessError).message;
              let code = (error as BusinessError).code;
              console.error(`---1130---openPopup error code is ${code}, message is ${message}`);
            }
            ;
          })
        Button('Num_1_0.5')
          .id('2')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '2' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: true,
                outlineWidth: 10,
                outlineLinearGradient: {
                  direction: GradientDirection.None,
                  colors: [[0xc6d40d, 0.5]]
                },
              } as PopupCommonOptions).then(() => {
                console.info('---1130---openPopup success');
              })
                .catch((err: Error) => {
                  console.info('---1130---openPopup error：' + err.code + '+' + err.message);
                })
            } catch (error) {
              let message = (error as BusinessError).message;
              let code = (error as BusinessError).code;
              console.error(`---1130---openPopup error code is ${code}, message is ${message}`);
            }
            ;
          })
        Button('Rgb_3_0.5')
          .id('3')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '3' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: true,
                outlineWidth: 10,
                outlineLinearGradient: {
                  direction: GradientDirection.None,
                  colors: [['rgb(255, 100, 255)', 0.0], [Color.Green, 0.5], [Color.Blue, 1.0]]
                },
              } as PopupCommonOptions).then(() => {
                console.info('---1130---openPopup success');
              })
                .catch((err: Error) => {
                  console.info('---1130---openPopup error：' + err.code + '+' + err.message);
                })
            } catch (error) {
              let message = (error as BusinessError).message;
              let code = (error as BusinessError).code;
              console.error(`---1130---openPopup error code is ${code}, message is ${message}`);
            }
            ;
          })
      }

      Row({ space: 5 } as RowOptions) {
        Button('Rgba_3_0.1')
          .id('4')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '4' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: true,
                outlineWidth: 10,
                outlineLinearGradient: {
                  direction: GradientDirection.None,
                  colors: [['rgba(33, 23, 169, 0.50)', 0.0], [Color.Green, 0.1], [Color.Blue, 1.0]]
                },
              } as PopupCommonOptions).then(() => {
                console.info('---1130---openPopup success');
              })
                .catch((err: Error) => {
                  console.info('---1130---openPopup error：' + err.code + '+' + err.message);
                })
            } catch (error) {
              let message = (error as BusinessError).message;
              let code = (error as BusinessError).code;
              console.error(`---1130---openPopup error code is ${code}, message is ${message}`);
            }
            ;
          })

        Button('$rError_3_0.5')
          .id('5')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '5' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: true,
                outlineWidth: 10,
                outlineLinearGradient: {
                  direction: GradientDirection.None,
                  colors: [[$r("app.string.error"), 0.0], [Color.Pink, 0.5], [Color.Blue, 1.0]]
                },
              } as PopupCommonOptions).then(() => {
                console.info('---1130---openPopup success');
              })
                .catch((err: Error) => {
                  console.info('---1130---openPopup error：' + err.code + '+' + err.message);
                })
            } catch (error) {
              let message = (error as BusinessError).message;
              let code = (error as BusinessError).code;
              console.error(`---1130---openPopup error code is ${code}, message is ${message}`);
            }
            ;
          })
        Button('Color_2_-1')
          .id('6')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '6' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: true,
                outlineWidth: 10,
                outlineLinearGradient: {
                  direction: GradientDirection.None,
                  colors: [[Color.Pink, -1], [Color.Blue, 1.0]]
                },
              } as PopupCommonOptions).then(() => {
                console.info('---1130---openPopup success');
              })
                .catch((err: Error) => {
                  console.info('---1130---openPopup error：' + err.code + '+' + err.message);
                })
            } catch (error) {
              let message = (error as BusinessError).message;
              let code = (error as BusinessError).code;
              console.error(`---1130---openPopup error code is ${code}, message is ${message}`);
            }
            ;
          })
      }

      Row({ space: 5 } as RowOptions) {
        Button('$r_2_0.33')
          .id('7')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '7' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: true,
                outlineWidth: 10,
                outlineLinearGradient: {
                  direction: GradientDirection.None,
                  colors: [[$r("app.color.color"), 0.0], [Color.Blue, 0.33]]
                },
              } as PopupCommonOptions).then(() => {
                console.info('---1130---openPopup success');
              })
                .catch((err: Error) => {
                  console.info('---1130---openPopup error：' + err.code + '+' + err.message);
                })
            } catch (error) {
              let message = (error as BusinessError).message;
              let code = (error as BusinessError).code;
              console.error(`---1130---openPopup error code is ${code}, message is ${message}`);
            }
            ;
          })
        Button('Str_2_0.88')
          .id('8')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '8' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: true,
                outlineWidth: 10,
                outlineLinearGradient: {
                  direction: GradientDirection.None,
                  colors: [['#3317A98D', 0.0], [Color.Blue, 0.88]]
                },
              } as PopupCommonOptions).then(() => {
                console.info('---1130---openPopup success');
              })
                .catch((err: Error) => {
                  console.info('---1130---openPopup error：' + err.code + '+' + err.message);
                })
            } catch (error) {
              let message = (error as BusinessError).message;
              let code = (error as BusinessError).code;
              console.error(`---1130---openPopup error code is ${code}, message is ${message}`);
            }
            ;
          })
        Button('Color_2_10')
          .id('9')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '9' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: true,
                outlineWidth: 10,
                outlineLinearGradient: {
                  direction: GradientDirection.None,
                  colors: [[Color.Pink, 0.0], [Color.Blue, 10]]
                },
              } as PopupCommonOptions).then(() => {
                console.info('---1130---openPopup success');
              })
                .catch((err: Error) => {
                  console.info('---1130---openPopup error：' + err.code + '+' + err.message);
                })
            } catch (error) {
              let message = (error as BusinessError).message;
              let code = (error as BusinessError).code;
              console.error(`---1130---openPopup error code is ${code}, message is ${message}`);
            }
            ;
          })
      }

      Row({ space: 5 } as RowOptions) {
        Button('undefined')
          .id('10')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '10' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: true,
                outlineWidth: 10,
                outlineLinearGradient: {
                  direction: GradientDirection.None,
                  colors: [[undefined, 0.0], [Color.Blue, 1.0]]
                } as PopupBorderLinearGradient,
              } as PopupCommonOptions).then(() => {
                console.info('---1130---openPopup success');
              })
                .catch((err: Error) => {
                  console.info('---1130---openPopup error：' + err.code + '+' + err.message);
                })
            } catch (error) {
              let message = (error as BusinessError).message;
              let code = (error as BusinessError).code;
              console.error(`---1130---openPopup error code is ${code}, message is ${message}`);
            }
            ;
          })
      }

      Text(`enableArrow设置为false:`)
        .fontSize(16)
        .width("100%")
      Row({ space: 5 } as RowOptions) {
        Button('Color_2_1.0')
          .id('12')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '12' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: false,
                outlineWidth: 10,
                outlineLinearGradient: {
                  direction: GradientDirection.None,
                  colors: [[Color.Yellow, 0.0], [Color.Green, 1.0]]
                },
              } as PopupCommonOptions).then(() => {
                console.info('---1130---openPopup success');
              })
                .catch((err: Error) => {
                  console.info('---1130---openPopup error：' + err.code + '+' + err.message);
                })
            } catch (error) {
              let message = (error as BusinessError).message;
              let code = (error as BusinessError).code;
              console.error(`---1130---openPopup error code is ${code}, message is ${message}`);
            }
            ;
          })
        Button('Num_1_0.5')
          .id('13')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '13' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: false,
                outlineWidth: 10,
                outlineLinearGradient: {
                  direction: GradientDirection.None,
                  colors: [[0xc6d40d, 0.5]]
                },
              } as PopupCommonOptions).then(() => {
                console.info('---1130---openPopup success');
              })
                .catch((err: Error) => {
                  console.info('---1130---openPopup error：' + err.code + '+' + err.message);
                })
            } catch (error) {
              let message = (error as BusinessError).message;
              let code = (error as BusinessError).code;
              console.error(`---1130---openPopup error code is ${code}, message is ${message}`);
            }
            ;
          })
        Button('Rgb_3_0.5')
          .id('14')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '14' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: false,
                outlineWidth: 10,
                outlineLinearGradient: {
                  direction: GradientDirection.None,
                  colors: [['rgb(255, 100, 255)', 0.0], [Color.Green, 0.5], [Color.Blue, 1.0]]
                },
              } as PopupCommonOptions).then(() => {
                console.info('---1130---openPopup success');
              })
                .catch((err: Error) => {
                  console.info('---1130---openPopup error：' + err.code + '+' + err.message);
                })
            } catch (error) {
              let message = (error as BusinessError).message;
              let code = (error as BusinessError).code;
              console.error(`---1130---openPopup error code is ${code}, message is ${message}`);
            }
            ;
          })
      }

      Row({ space: 5 } as RowOptions) {
        Button('Rgba_3_0.1')
          .id('15')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '15' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: false,
                outlineWidth: 10,
                outlineLinearGradient: {
                  direction: GradientDirection.None,
                  colors: [['rgba(33, 23, 169, 0.50)', 0.0], [Color.Green, 0.1], [Color.Blue, 1.0]]
                },
              } as PopupCommonOptions).then(() => {
                console.info('---1130---openPopup success');
              })
                .catch((err: Error) => {
                  console.info('---1130---openPopup error：' + err.code + '+' + err.message);
                })
            } catch (error) {
              let message = (error as BusinessError).message;
              let code = (error as BusinessError).code;
              console.error(`---1130---openPopup error code is ${code}, message is ${message}`);
            }
            ;
          })

        Button('$rError_3_0.5')
          .id('16')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '16' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: false,
                outlineWidth: 10,
                outlineLinearGradient: {
                  direction: GradientDirection.None,
                  colors: [[$r("app.string.error"), 0.0], [Color.Pink, 0.5], [Color.Blue, 1.0]]
                },
              } as PopupCommonOptions).then(() => {
                console.info('---1130---openPopup success');
              })
                .catch((err: Error) => {
                  console.info('---1130---openPopup error：' + err.code + '+' + err.message);
                })
            } catch (error) {
              let message = (error as BusinessError).message;
              let code = (error as BusinessError).code;
              console.error(`---1130---openPopup error code is ${code}, message is ${message}`);
            }
            ;
          })
        Button('Color_2_-1')
          .id('17')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '17' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: false,
                outlineWidth: 10,
                outlineLinearGradient: {
                  direction: GradientDirection.None,
                  colors: [[Color.Pink, -1], [Color.Blue, 1.0]]
                },
              } as PopupCommonOptions).then(() => {
                console.info('---1130---openPopup success');
              })
                .catch((err: Error) => {
                  console.info('---1130---openPopup error：' + err.code + '+' + err.message);
                })
            } catch (error) {
              let message = (error as BusinessError).message;
              let code = (error as BusinessError).code;
              console.error(`---1130---openPopup error code is ${code}, message is ${message}`);
            }
            ;
          })
      }

      Row({ space: 5 } as RowOptions) {
        Button('$r_2_0.33')
          .id('18')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '18' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: false,
                outlineWidth: 10,
                outlineLinearGradient: {
                  direction: GradientDirection.None,
                  colors: [[$r("app.color.color"), 0.0], [Color.Blue, 0.33]]
                },
              } as PopupCommonOptions).then(() => {
                console.info('---1130---openPopup success');
              })
                .catch((err: Error) => {
                  console.info('---1130---openPopup error：' + err.code + '+' + err.message);
                })
            } catch (error) {
              let message = (error as BusinessError).message;
              let code = (error as BusinessError).code;
              console.error(`---1130---openPopup error code is ${code}, message is ${message}`);
            }
            ;
          })
        Button('Str_2_0.88')
          .id('19')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '19' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: false,
                outlineWidth: 10,
                outlineLinearGradient: {
                  direction: GradientDirection.None,
                  colors: [['#3317A98D', 0.0], [Color.Blue, 0.88]]
                },
              } as PopupCommonOptions).then(() => {
                console.info('---1130---openPopup success');
              })
                .catch((err: Error) => {
                  console.info('---1130---openPopup error：' + err.code + '+' + err.message);
                })
            } catch (error) {
              let message = (error as BusinessError).message;
              let code = (error as BusinessError).code;
              console.error(`---1130---openPopup error code is ${code}, message is ${message}`);
            }
            ;
          })
        Button('Color_2_10')
          .id('20')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '20' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: false,
                outlineWidth: 10,
                outlineLinearGradient: {
                  direction: GradientDirection.None,
                  colors: [[Color.Pink, 0.0], [Color.Blue, 10]]
                },
              } as PopupCommonOptions).then(() => {
                console.info('---1130---openPopup success');
              })
                .catch((err: Error) => {
                  console.info('---1130---openPopup error：' + err.code + '+' + err.message);
                })
            } catch (error) {
              let message = (error as BusinessError).message;
              let code = (error as BusinessError).code;
              console.error(`---1130---openPopup error code is ${code}, message is ${message}`);
            }
            ;
          })
      }

      Row({ space: 5 } as RowOptions) {
        Button('undefined')
          .id('21')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '21' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: false,
                outlineWidth: 10,
                outlineLinearGradient: {
                  direction: GradientDirection.None,
                  colors: [[undefined, 0.0], [Color.Blue, 1.0]]
                },
              } as PopupCommonOptions).then(() => {
                console.info('---1130---openPopup success');
              })
                .catch((err: Error) => {
                  console.info('---1130---openPopup error：' + err.code + '+' + err.message);
                })
            } catch (error) {
              let message = (error as BusinessError).message;
              let code = (error as BusinessError).code;
              console.error(`---1130---openPopup error code is ${code}, message is ${message}`);
            }
            ;
          })
      }

      Text(`内外描边结合:`)
        .fontSize(16)
        .width("100%")
      Button('popup_false')
        .id('23')
        .onClick(() => {
          try {
            this.promptAction.openPopup(this.contentNode, { id: '23' } as TargetInfo, {
              placement: Placement.Bottom,
              enableArrow: false,
              borderWidth: 10,
              borderLinearGradient: this.borderLinearGradientList[this.borderLinearGradientIndex],
              outlineWidth: 10,
              outlineLinearGradient: this.outlineLinearGradientList[this.outlineLinearGradientIndex],
            } as PopupCommonOptions).then(() => {
              console.info('---1130---openPopup success');
            })
              .catch((err: Error) => {
                console.info('---1130---openPopup error：' + err.code + '+' + err.message);
              })
          } catch (error) {
            let message = (error as BusinessError).message;
            let code = (error as BusinessError).code;
            console.error(`---1130---openPopup error code is ${code}, message is ${message}`);
          }
          ;
        })
      Button('popup_true')
        .id('24')
        .onClick(() => {
          try {
            this.promptAction.openPopup(this.contentNode, { id: '24' } as TargetInfo, {
              placement: Placement.Bottom,
              enableArrow: true,
              borderWidth: 10,
              borderLinearGradient: this.borderLinearGradientList[this.borderLinearGradientIndex],
              outlineWidth: 10,
              outlineLinearGradient: this.outlineLinearGradientList[this.outlineLinearGradientIndex],
            } as PopupCommonOptions).then(() => {
              console.info('---1130---openPopup success');
            })
              .catch((err: Error) => {
                console.info('---1130---openPopup error：' + err.code + '+' + err.message);
              })
          } catch (error) {
            let message = (error as BusinessError).message;
            let code = (error as BusinessError).code;
            console.error(`---1130---openPopup error code is ${code}, message is ${message}`);
          }
          ;
        })
      Button("切换borderLinearGradient_colors : " + this.borderLinearGradientIndex)
        .onClick(() => {
          this.borderLinearGradientIndex++
          if (this.borderLinearGradientIndex >= this.borderLinearGradientList.length) {
            this.borderLinearGradientIndex = 0
          }
        })
      Button("切换outlineLinearGradient_colors : " + this.outlineLinearGradientIndex)
        .onClick(() => {
          this.outlineLinearGradientIndex++
          if (this.outlineLinearGradientIndex >= this.outlineLinearGradientList.length) {
            this.outlineLinearGradientIndex = 0
          }
        })
    }.margin(20)
  }
}