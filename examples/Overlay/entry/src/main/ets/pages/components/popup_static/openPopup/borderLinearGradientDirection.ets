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
struct OpenPopupBorderLinearGradientDirection {
  private uiContext: UIContext = this.getUIContext();
  private promptAction: PromptAction = this.uiContext.getPromptAction();
  private contentNode: ComponentContent = new ComponentContent(this.uiContext, wrapBuilder(PopupBuilder));
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
          .id('1')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '1' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: true,
                borderWidth: 10,
                borderLinearGradient: {
                  direction: GradientDirection.Top,
                  colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
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
        Button('Right')
          .id('2')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '2' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: true,
                borderWidth: 10,
                borderLinearGradient: {
                  direction: GradientDirection.Right,
                  colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
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
        Button('Bottom')
          .id('3')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '3' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: true,
                borderWidth: 10,
                borderLinearGradient: {
                  direction: GradientDirection.Bottom,
                  colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
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
        Button('LeftTop')
          .id('4')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '4' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: true,
                borderWidth: 10,
                borderLinearGradient: {
                  direction: GradientDirection.LeftTop,
                  colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
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
        Button('LeftBottom')
          .id('5')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '5' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: true,
                borderWidth: 10,
                borderLinearGradient: {
                  direction: GradientDirection.LeftBottom,
                  colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
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
        Button('RightTop')
          .id('6')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '6' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: true,
                borderWidth: 10,
                borderLinearGradient: {
                  direction: GradientDirection.RightTop,
                  colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
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
        Button('RightBottom')
          .id('7')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '7' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: true,
                borderWidth: 10,
                borderLinearGradient: {
                  direction: GradientDirection.RightBottom,
                  colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
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
        Button('None')
          .id('8')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '8' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: true,
                borderWidth: 10,
                borderLinearGradient: {
                  direction: GradientDirection.None,
                  colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
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
        Button('undefined')
          .id('11')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '11' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: true,
                borderWidth: 10,
                borderLinearGradient: {
                  direction: undefined,
                  colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
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

      Text(`enableArrow设置为false:`)
        .fontSize(16)
        .width("100%")
      Row({ space: 5 } as RowOptions) {
        Button('Top')
          .id('12')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '12' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: false,
                borderWidth: 10,
                borderLinearGradient: {
                  direction: GradientDirection.Top,
                  colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
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
        Button('Right')
          .id('13')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '13' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: false,
                borderWidth: 10,
                borderLinearGradient: {
                  direction: GradientDirection.Right,
                  colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
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
        Button('Bottom')
          .id('14')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '14' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: false,
                borderWidth: 10,
                borderLinearGradient: {
                  direction: GradientDirection.Bottom,
                  colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
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
        Button('LeftTop')
          .id('15')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '15' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: false,
                borderWidth: 10,
                borderLinearGradient: {
                  direction: GradientDirection.LeftTop,
                  colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
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
        Button('LeftBottom')
          .id('16')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '16' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: false,
                borderWidth: 10,
                borderLinearGradient: {
                  direction: GradientDirection.LeftBottom,
                  colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
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
        Button('RightTop')
          .id('17')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '17' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: false,
                borderWidth: 10,
                borderLinearGradient: {
                  direction: GradientDirection.RightTop,
                  colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
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
        Button('RightBottom')
          .id('18')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '18' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: false,
                borderWidth: 10,
                borderLinearGradient: {
                  direction: GradientDirection.RightBottom,
                  colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
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
        Button('None')
          .id('19')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '19' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: false,
                borderWidth: 10,
                borderLinearGradient: {
                  direction: GradientDirection.None,
                  colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
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
        Button('undefined')
          .id('22')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '22' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: false,
                borderWidth: 10,
                borderLinearGradient: {
                  direction: undefined,
                  colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
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
      Button("切换borderLinearGradient_direction : " + this.borderLinearGradientIndex)
        .onClick(() => {
          this.borderLinearGradientIndex++
          if (this.borderLinearGradientIndex >= this.borderLinearGradientList.length) {
            this.borderLinearGradientIndex = 0
          }
        })
      Button("切换outlineLinearGradient_direction : " + this.outlineLinearGradientIndex)
        .onClick(() => {
          this.outlineLinearGradientIndex++
          if (this.outlineLinearGradientIndex >= this.outlineLinearGradientList.length) {
            this.outlineLinearGradientIndex = 0
          }
        })
    }.margin(20)
  }
}