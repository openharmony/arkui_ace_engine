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

@Builder
function popupBuilder() {
  Scroll(new Scroller()) {
    Column({ space: 5 } as ColumnOptions) {
      Text('This is a popup with PopupOptionsThis is a popup with PopupOptionsThis is a popup with PopupOptions' +
        'This is a popup with PopupOptionsThis is a popup with PopupOptionsThis is a popup with PopupOptions,')
    }
  }
}

@Entry
@Component
struct OpenPopupBorderWidth {
  private uiContext: UIContext = this.getUIContext();
  private promptAction: PromptAction = this.uiContext.getPromptAction();
  private contentNode: ComponentContent = new ComponentContent(this.uiContext, wrapBuilder(popupBuilder));
  @State outlineWidthIndex: Int = 0;
  @State outlineWidthList: (Dimension | undefined)[] = [
    '1vp' as Dimension, '2vp' as Dimension, '5vp' as Dimension, '10vp' as Dimension, undefined, 0 as Dimension,
    -1 as Dimension, '2px' as Dimension, '3.9fp' as Dimension, '5vp' as Dimension, '10lpx' as Dimension,
    1000 as Dimension, $r('app.string.width') as Dimension, $r('app.string.error') as Dimension,
  ]
  @State borderWidthIndex: Int = 0;
  @State borderWidthList: (Dimension | undefined)[] = [
    '1vp' as Dimension, '2vp' as Dimension, '5vp' as Dimension, '10vp' as Dimension, undefined, 0 as Dimension,
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
          .id('1')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '1' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: true,
                borderWidth: '10vp',
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
        Button('0')
          .id('2')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '2' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: true,
                borderWidth: 0,
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
        Button('2px')
          .id('3')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '3' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: true,
                borderWidth: '2px',
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
        Button('3.9fp')
          .id('4')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '4' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: true,
                borderWidth: '3.9fp',
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
        Button('5vp')
          .id('5')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '5' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: true,
                borderWidth: '5vp',
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
      }

      Row({ space: 5 } as RowOptions) {
        Button('10lpx')
          .id('6')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '6' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: true,
                borderWidth: '10lpx',
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
        Button('1000')
          .id('7')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '7' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: true,
                borderWidth: 1000,
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
        Button('-1')
          .id('8')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '8' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: true,
                borderWidth: -1,
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
        Button('app.string.width')
          .id('9')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '9' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: true,
                borderWidth: $r('app.string.width'),
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
      }

      Row({ space: 5 } as RowOptions) {
        Button('app.string.error')
          .id('10')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '10' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: true,
                borderWidth: $r('app.string.error'),
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
                borderWidth: undefined,
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
      }

      Text(`enableArrow设置为false:`)
        .fontSize(16)
        .width('100%')
      Row({ space: 5 } as RowOptions) {
        Button('10vp')
          .id('12')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '12' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: false,
                borderWidth: '10vp',
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
        Button('0')
          .id('13')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '13' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: false,
                borderWidth: 0,
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
        Button('2px')
          .id('14')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '14' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: false,
                borderWidth: '2px',
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
        Button('3.9fp')
          .id('15')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '15' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: false,
                borderWidth: '3.9fp',
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
        Button('5vp')
          .id('16')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '16' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: false,
                borderWidth: '5vp',
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
      }

      Row({ space: 5 } as RowOptions) {
        Button('10lpx')
          .id('17')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '17' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: false,
                borderWidth: '10lpx',
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
        Button('1000')
          .id('18')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '18' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: false,
                borderWidth: 1000,
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
        Button('-1')
          .id('19')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '19' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: false,
                borderWidth: -1,
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
        Button('app.string.width')
          .id('20')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '20' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: false,
                borderWidth: $r('app.string.width'),
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
      }

      Row({ space: 5 } as RowOptions) {
        Button('app.string.error')
          .id('21')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '21' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: false,
                borderWidth: $r('app.string.error'),
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
                borderWidth: undefined,
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
      }

      Text(`内外描边结合:`)
        .fontSize(16)
        .width('100%')
      Button('popup_false')
        .id('23')
        .onClick(() => {
          try {
            this.promptAction.openPopup(this.contentNode, { id: '23' } as TargetInfo, {
              placement: Placement.Bottom,
              enableArrow: false,
              outlineWidth: this.outlineWidthList[this.outlineWidthIndex],
              outlineLinearGradient: {
                direction: GradientDirection.None,
                colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
              },
              borderWidth: this.borderWidthList[this.borderWidthIndex],
              borderLinearGradient: {
                direction: GradientDirection.Left,
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
      Button('popup_true')
        .id('24')
        .onClick(() => {
          try {
            this.promptAction.openPopup(this.contentNode, { id: '24' } as TargetInfo, {
              placement: Placement.Bottom,
              enableArrow: true,
              outlineWidth: this.outlineWidthList[this.outlineWidthIndex],
              outlineLinearGradient: {
                direction: GradientDirection.None,
                colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]]
              },
              borderWidth: this.borderWidthList[this.borderWidthIndex],
              borderLinearGradient: {
                direction: GradientDirection.Left,
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
      Button('动态切换outlineWidth : ' + this.outlineWidthList[this.outlineWidthIndex])
        .onClick(() => {
          this.outlineWidthIndex++
          if (this.outlineWidthIndex >= this.outlineWidthList.length) {
            this.outlineWidthIndex = 0
          }
        })
      Button('动态切换borderWidth : ' + this.borderWidthList[this.borderWidthIndex])
        .onClick(() => {
          this.borderWidthIndex++
          if (this.borderWidthIndex >= this.borderWidthList.length) {
            this.borderWidthIndex = 0
          }
        })
    }.margin(20)
  }
}