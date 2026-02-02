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

@Entry
@Component
struct UpdatePopupAvoidTarget {
  private uiContext: UIContext = this.getUIContext();
  private promptAction: PromptAction = this.uiContext.getPromptAction();
  private contentNode: ComponentContent = new ComponentContent(this.uiContext, wrapBuilder(popupBuilder));

  build() {
    Column({ space: 5 } as ColumnOptions) {
      Text(`enableArrow设置为true:`)
        .fontSize(16)
        .width('100%')
      Row({ space: 5 } as RowOptions) {
        Text('从正常值更新成正常值 :')
          .fontSize(12)
          .fontColor('rgba(24,36,49,0.60)')
          .width('54%')
        Button('更新为COVER_TARGET')
          .id('1')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '1' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: true,
                avoidTarget: AvoidanceMode.AVOID_AROUND_TARGET,
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
            setTimeout(() => {
              try {
                this.promptAction.updatePopup(this.contentNode,
                  {
                    avoidTarget: AvoidanceMode.COVER_TARGET,
                  }, true)
                  .then(() => {
                    console.info('---1130---updatePopup success');
                  })
                  .catch((err: Error) => {
                    console.info('---1130---updatePopup error：' + err.code + '+' + err.message);
                  })
              } catch (error) {
                let message = (error as BusinessError).message;
                let code = (error as BusinessError).code;
                console.error(`---1130---updatePopup error code is ${code}, message is ${message}`);
              }
              ;
            }, 2000);

          })
      }

      Row({ space: 5 } as RowOptions) {
        Text('从正常值更新成异常值 :')
          .fontSize(12)
          .fontColor('rgba(24,36,49,0.60)')
          .width('65%')
        Button('更新为undefined')
          .id('3')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '3' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: true,
                avoidTarget: AvoidanceMode.AVOID_AROUND_TARGET,
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
            setTimeout(() => {
              try {
                this.promptAction.updatePopup(this.contentNode,
                  {
                    avoidTarget: undefined,
                  }, true)
                  .then(() => {
                    console.info('---1130---updatePopup success');
                  })
                  .catch((err: Error) => {
                    console.info('---1130---updatePopup error：' + err.code + '+' + err.message);
                  })
              } catch (error) {
                let message = (error as BusinessError).message;
                let code = (error as BusinessError).code;
                console.error(`---1130---updatePopup error code is ${code}, message is ${message}`);
              }
              ;
            }, 2000);

          })
      }

      Row({ space: 5 } as RowOptions) {
        Text('从异常值更新成正常值 :')
          .fontSize(12)
          .fontColor('rgba(24,36,49,0.60)')
          .width('40%')
        Button('更新为AVOID_AROUND_TARGET')
          .id('17')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '17' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: true,
                avoidTarget: undefined,
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
            setTimeout(() => {
              try {
                this.promptAction.updatePopup(this.contentNode,
                  {
                    avoidTarget: AvoidanceMode.AVOID_AROUND_TARGET,
                  }, true)
                  .then(() => {
                    console.info('---1130---updatePopup success');
                  })
                  .catch((err: Error) => {
                    console.info('---1130---updatePopup error：' + err.code + '+' + err.message);
                  })
              } catch (error) {
                let message = (error as BusinessError).message;
                let code = (error as BusinessError).code;
                console.error(`---1130---updatePopup error code is ${code}, message is ${message}`);
              }
              ;
            }, 2000);

          })
      }
      Row({ space: 5 } as RowOptions) {
        Text('从不设置更新成正常值 :')
          .fontSize(12)
          .fontColor('rgba(24,36,49,0.60)')
          .width('40%')
        Button('更新为AVOID_AROUND_TARGET')
          .id('6')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '6' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: true,
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
            setTimeout(() => {
              try {
                this.promptAction.updatePopup(this.contentNode,
                  {
                    avoidTarget: AvoidanceMode.AVOID_AROUND_TARGET,
                  }, true)
                  .then(() => {
                    console.info('---1130---updatePopup success');
                  })
                  .catch((err: Error) => {
                    console.info('---1130---updatePopup error：' + err.code + '+' + err.message);
                  })
              } catch (error) {
                let message = (error as BusinessError).message;
                let code = (error as BusinessError).code;
                console.error(`---1130---updatePopup error code is ${code}, message is ${message}`);
              }
              ;
            }, 2000);

          })
      }

      Row({ space: 5 } as RowOptions) {
        Text('从不设置更新成异常值 :')
          .fontSize(12)
          .fontColor('rgba(24,36,49,0.60)')
          .width('65%')
        Button('更新为undefined')
          .id('7')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '7' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: true,
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
            setTimeout(() => {
              try {
                this.promptAction.updatePopup(this.contentNode,
                  {
                    avoidTarget: undefined,
                  }, true)
                  .then(() => {
                    console.info('---1130---updatePopup success');
                  })
                  .catch((err: Error) => {
                    console.info('---1130---updatePopup error：' + err.code + '+' + err.message);
                  })
              } catch (error) {
                let message = (error as BusinessError).message;
                let code = (error as BusinessError).code;
                console.error(`---1130---updatePopup error code is ${code}, message is ${message}`);
              }
              ;
            }, 2000);

          })
      }

      Row({ space: 5 } as RowOptions) {
        Text('从设置全量更新到不设置 :')
          .fontSize(12)
          .fontColor('rgba(24,36,49,0.60)')
          .width('70%')
        Button('更新为不设置')
          .id('8')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '8' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: true,
                avoidTarget: AvoidanceMode.AVOID_AROUND_TARGET,
              } as PopupCommonOptions)
                .then(() => {
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
            setTimeout(() => {
              try {
                this.promptAction.updatePopup(this.contentNode,
                  {
                    popupColor: Color.Pink,
                  }, false)
                  .then(() => {
                    console.info('---1130---updatePopup success');
                  })
                  .catch((err: Error) => {
                    console.info('---1130---updatePopup error：' + err.code + '+' + err.message);
                  })
              } catch (error) {
                let message = (error as BusinessError).message;
                let code = (error as BusinessError).code;
                console.error(`---1130---updatePopup error code is ${code}, message is ${message}`);
              }
              ;
            }, 2000);

          })
      }

      Text(`enableArrow设置为false:`)
        .fontSize(16)
        .width('100%')
      Row({ space: 5 } as RowOptions) {
        Text('从正常值更新成正常值 :')
          .fontSize(12)
          .fontColor('rgba(24,36,49,0.60)')
          .width('54%')
        Button('更新为COVER_TARGET')
          .id('9')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '9' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: false,
                avoidTarget: AvoidanceMode.AVOID_AROUND_TARGET,
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
            setTimeout(() => {
              try {
                this.promptAction.updatePopup(this.contentNode,
                  {
                    avoidTarget: AvoidanceMode.COVER_TARGET,
                  }, true)
                  .then(() => {
                    console.info('---1130---updatePopup success');
                  })
                  .catch((err: Error) => {
                    console.info('---1130---updatePopup error：' + err.code + '+' + err.message);
                  })
              } catch (error) {
                let message = (error as BusinessError).message;
                let code = (error as BusinessError).code;
                console.error(`---1130---updatePopup error code is ${code}, message is ${message}`);
              }
              ;
            }, 2000);

          })
      }

      Row({ space: 5 } as RowOptions) {
        Text('从正常值更新成异常值 :')
          .fontSize(12)
          .fontColor('rgba(24,36,49,0.60)')
          .width('65%')
        Button('更新为undefined')
          .id('11')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '11' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: false,
                avoidTarget: AvoidanceMode.AVOID_AROUND_TARGET,
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
            setTimeout(() => {
              try {
                this.promptAction.updatePopup(this.contentNode,
                  {
                    avoidTarget: undefined,
                  }, true)
                  .then(() => {
                    console.info('---1130---updatePopup success');
                  })
                  .catch((err: Error) => {
                    console.info('---1130---updatePopup error：' + err.code + '+' + err.message);
                  })
              } catch (error) {
                let message = (error as BusinessError).message;
                let code = (error as BusinessError).code;
                console.error(`---1130---updatePopup error code is ${code}, message is ${message}`);
              }
              ;
            }, 2000);

          })
      }

      Row({ space: 5 } as RowOptions) {
        Text('从异常值更新成正常值 :')
          .fontSize(12)
          .fontColor('rgba(24,36,49,0.60)')
          .width('40%')
        Button('更新为AVOID_AROUND_TARGET')
          .id('18')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '18' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: false,
                avoidTarget: undefined,
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
            setTimeout(() => {
              try {
                this.promptAction.updatePopup(this.contentNode,
                  {
                    avoidTarget: AvoidanceMode.AVOID_AROUND_TARGET,
                  }, true)
                  .then(() => {
                    console.info('---1130---updatePopup success');
                  })
                  .catch((err: Error) => {
                    console.info('---1130---updatePopup error：' + err.code + '+' + err.message);
                  })
              } catch (error) {
                let message = (error as BusinessError).message;
                let code = (error as BusinessError).code;
                console.error(`---1130---updatePopup error code is ${code}, message is ${message}`);
              }
              ;
            }, 2000);
          })
      }
      Row({ space: 5 } as RowOptions) {
        Text('从不设置更新成正常值 :')
          .fontSize(12)
          .fontColor('rgba(24,36,49,0.60)')
          .width('40%')
        Button('更新为AVOID_AROUND_TARGET')
          .id('14')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '14' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: false,
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
            setTimeout(() => {
              try {
                this.promptAction.updatePopup(this.contentNode,
                  {
                    avoidTarget: AvoidanceMode.AVOID_AROUND_TARGET,
                  }, true)
                  .then(() => {
                    console.info('---1130---updatePopup success');
                  })
                  .catch((err: Error) => {
                    console.info('---1130---updatePopup error：' + err.code + '+' + err.message);
                  })
              } catch (error) {
                let message = (error as BusinessError).message;
                let code = (error as BusinessError).code;
                console.error(`---1130---updatePopup error code is ${code}, message is ${message}`);
              }
              ;
            }, 2000);

          })
      }

      Row({ space: 5 } as RowOptions) {
        Text('从不设置更新成异常值 :')
          .fontSize(12)
          .fontColor('rgba(24,36,49,0.60)')
          .width('65%')
        Button('更新为undefined')
          .id('15')
          .onClick(() => {
            try {
              this.promptAction.openPopup(this.contentNode, { id: '15' } as TargetInfo, {
                placement: Placement.Bottom,
                enableArrow: false,
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
            setTimeout(() => {
              try {
                this.promptAction.updatePopup(this.contentNode,
                  {
                    avoidTarget: undefined,
                  }, true)
                  .then(() => {
                    console.info('---1130---updatePopup success');
                  })
                  .catch((err: Error) => {
                    console.info('---1130---updatePopup error：' + err.code + '+' + err.message);
                  })
              } catch (error) {
                let message = (error as BusinessError).message;
                let code = (error as BusinessError).code;
                console.error(`---1130---updatePopup error code is ${code}, message is ${message}`);
              }
              ;
            }, 2000);

          })
      }

      Row({ space: 5 } as RowOptions) {
        Text('从设置全量更新到不设置 :')
          .fontSize(12)
          .fontColor('rgba(24,36,49,0.60)')
          .width('70%')
        Button('更新为不设置')
          .id('16')
      }

    }.margin(20)
  }
}