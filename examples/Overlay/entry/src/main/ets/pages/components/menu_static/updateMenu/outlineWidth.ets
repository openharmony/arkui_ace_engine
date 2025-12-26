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

let startIcon: ResourceStr = $r('app.media.startIcon')
let endIcon: ResourceStr = $r('app.media.startIcon')
let subMenuExpandingMode: SubMenuExpandingMode | undefined = SubMenuExpandingMode.SIDE_EXPAND;

@Builder
function subMenuBuilder() {
  Menu() {
    MenuItem({
      startIcon: $r('app.media.startIcon'),
      content: '图标',
      builder: subMenuBuilder,
    } as MenuItemOptions)
    MenuItem({
      startIcon: $r('app.media.startIcon'),
      content: '列表',
      builder: subMenuBuilder,
    } as MenuItemOptions)
  }.backgroundColor(Color.Grey)
}

@Builder
function menuBuilder() {
  Menu() {
    MenuItem({
      startIcon: startIcon,
      endIcon: endIcon,
      content: '新建文件夹',
      builder: subMenuBuilder,
    } as MenuItemOptions)
    MenuItem({
      startIcon: startIcon,
      content: '排序方式',
      builder: subMenuBuilder,
    } as MenuItemOptions)
    MenuItem({
      startIcon: startIcon,
      content: '查看方式',
      builder: subMenuBuilder,
    } as MenuItemOptions)
  }
  .backgroundColor(Color.Grey)
  .subMenuExpandingMode(subMenuExpandingMode)
}

@Entry
@Component
struct Index {
  @State changeIndex: Int = 0;
  @State changeList: (Dimension | EdgeOutlineWidths | undefined)[] = [
    '30px' as Dimension, undefined, '20vp' as Dimension, '30fp' as Dimension, '40lpx' as Dimension, '20%' as Dimension,
    $r('app.float.outlineWidth') as Dimension, undefined, {
    left: -100,
    right: '20px',
    top: '30px',
    bottom: '40px'
  } as EdgeOutlineWidths, -1 as Dimension
  ]
  menuOptions: MenuOptions = {
    title: '' + this.changeList[this.changeIndex],
    outlineWidth: this.changeList[this.changeIndex],
    outlineColor: Color.Blue

  } as MenuOptions
  private uiContext: UIContext = this.getUIContext();
  private promptAction: PromptAction = this.uiContext.getPromptAction();
  private targetInfo: TargetInfo = {
    id: 'open',
  } as TargetInfo
  private targetInfo1: TargetInfo = {
    id: 'open1',
  } as TargetInfo
  private targetInfo2: TargetInfo = {
    id: 'open2',
  } as TargetInfo
  private targetInfo3: TargetInfo = {
    id: 'open3',
  } as TargetInfo
  private targetInfo4: TargetInfo = {
    id: 'open4',
  } as TargetInfo
  private targetInfo5: TargetInfo = {
    id: 'open5',
  } as TargetInfo
  private targetInfo6: TargetInfo = {
    id: 'open6',
  } as TargetInfo
  private targetInfo7: TargetInfo = {
    id: 'open7',
  } as TargetInfo
  private targetInfo8: TargetInfo = {
    id: 'open8',
  } as TargetInfo
  private targetInfo9: TargetInfo = {
    id: 'open9',
  } as TargetInfo
  private targetInfo10: TargetInfo = {
    id: 'open10',
  } as TargetInfo
  @State changeIsPartialUpdateIndex: Int = 0;
  @State changeIsPartialUpdateList: (Boolean)[] = [
    false, true
  ]
  @State isPartialUpdate: string = '全量';

  build() {
    Column({ space: 10 } as ColumnOptions) {
      Button('切换全量/增量')
        .onClick(() => {
          this.changeIsPartialUpdateIndex++
          if (this.changeIsPartialUpdateIndex > this.changeIsPartialUpdateList.length - 1) {
            this.changeIsPartialUpdateIndex = 0
          }
          if (this.changeIsPartialUpdateIndex == 0) {
            this.isPartialUpdate = '全量'
          } else {
            this.isPartialUpdate = '增量'
          }
        })
      Text('' + this.isPartialUpdate).fontColor(Color.Red).fontSize(30)
      Row({ space: 10 } as RowOptions) {
        Text(`10px->30px`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .id('open1')
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(menuBuilder));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo1, {
                borderRadius: 0,
                title: '10px',
                outlineWidth: '10px',
                outlineColor: Color.Blue
              } as MenuOptions)
                .then(() => {
                  console.info('openMenu success');
                })
                .catch((err: Error) => {
                  console.info('openMenu error：' + err.message);
                })
            } catch (error) {
              let message = (error as BusinessError).message;
              let code = (error as BusinessError).code;
              console.error(`shjb+openMenu error code is ${code}, message is ${message}`);
            }
            ;
            setTimeout(() => {
              try {
                this.promptAction.updateMenu(contentNode, {
                  title: '10px',
                  outlineWidth: '30px',
                  outlineColor: Color.Blue
                } as MenuOptions, this.changeIsPartialUpdateList[this.changeIsPartialUpdateIndex])
                  .then(() => {
                    console.info('api20+updateMenu success');
                  })
                  .catch((err: Error) => {
                    console.info('api20+updateMenu error：' + '+' + err.message);
                  })
              } catch (error) {
                let message = (error as BusinessError).message;
                let code = (error as BusinessError).code;
                console.error(`api20+updateMenu error code is ${code}, message is ${message}`);
              }
              ;
            }, 2000);
          })
        Text(`10vp->30vp`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .id('open2')
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(menuBuilder));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo2, {
                borderRadius: 0,
                title: '10vp',
                outlineWidth: '10vp',
                outlineColor: Color.Blue
              } as MenuOptions)
                .then(() => {
                  console.info('openMenu success');
                })
                .catch((err: Error) => {
                  console.info('openMenu error：' + err.message);
                })
            } catch (error) {
              let message = (error as BusinessError).message;
              let code = (error as BusinessError).code;
              console.error(`shjb+openMenu error code is ${code}, message is ${message}`);
            }
            ;
            setTimeout(() => {
              try {
                this.promptAction.updateMenu(contentNode, {
                  title: '10vp',
                  outlineWidth: '30vp',
                  outlineColor: Color.Blue
                } as MenuOptions, this.changeIsPartialUpdateList[this.changeIsPartialUpdateIndex])
                  .then(() => {
                    console.info('api20+updateMenu success');
                  })
                  .catch((err: Error) => {
                    console.info('api20+updateMenu error：' + '+' + err.message);
                  })
              } catch (error) {
                let message = (error as BusinessError).message;
                let code = (error as BusinessError).code;
                console.error(`api20+updateMenu error code is ${code}, message is ${message}`);
              }
              ;
            }, 2000);
          })
        Text(`10fp->30fp`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .id('open3')
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(menuBuilder));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo3, {
                borderRadius: 0,
                title: '10fp',
                outlineWidth: '10fp',
                outlineColor: Color.Blue
              } as MenuOptions)
                .then(() => {
                  console.info('openMenu success');
                })
                .catch((err: Error) => {
                  console.info('openMenu error：' + err.message);
                })
            } catch (error) {
              let message = (error as BusinessError).message;
              let code = (error as BusinessError).code;
              console.error(`shjb+openMenu error code is ${code}, message is ${message}`);
            }
            ;
            setTimeout(() => {
              try {
                this.promptAction.updateMenu(contentNode, {
                  title: '10fp',
                  outlineWidth: '30fp',
                  outlineColor: Color.Blue
                } as MenuOptions, this.changeIsPartialUpdateList[this.changeIsPartialUpdateIndex])
                  .then(() => {
                    console.info('api20+updateMenu success');
                  })
                  .catch((err: Error) => {
                    console.info('api20+updateMenu error：' + '+' + err.message);
                  })
              } catch (error) {
                let message = (error as BusinessError).message;
                let code = (error as BusinessError).code;
                console.error(`api20+updateMenu error code is ${code}, message is ${message}`);
              }
              ;
            }, 2000);
          })
      }

      Row({ space: 10 } as RowOptions) {
        Text(`10lpx->30lpx`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .id('open4')
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(menuBuilder));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo4, {
                borderRadius: 0,
                title: '10lpx',
                outlineWidth: '10lpx',
                outlineColor: Color.Blue
              } as MenuOptions)
                .then(() => {
                  console.info('openMenu success');
                })
                .catch((err: Error) => {
                  console.info('openMenu error：' + err.message);
                })
            } catch (error) {
              let message = (error as BusinessError).message;
              let code = (error as BusinessError).code;
              console.error(`shjb+openMenu error code is ${code}, message is ${message}`);
            }
            ;
            setTimeout(() => {
              try {
                this.promptAction.updateMenu(contentNode, {
                  title: '10lpx',
                  outlineWidth: '30lpx',
                  outlineColor: Color.Blue
                } as MenuOptions, this.changeIsPartialUpdateList[this.changeIsPartialUpdateIndex])
                  .then(() => {
                    console.info('api20+updateMenu success');
                  })
                  .catch((err: Error) => {
                    console.info('api20+updateMenu error：' + '+' + err.message);
                  })
              } catch (error) {
                let message = (error as BusinessError).message;
                let code = (error as BusinessError).code;
                console.error(`api20+updateMenu error code is ${code}, message is ${message}`);
              }
              ;
            }, 2000);
          })
        Text(`20%->40%`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .id('open5')
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(menuBuilder));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo5, {
                borderRadius: 0,
                title: '20%',
                outlineWidth: '20%',
                outlineColor: Color.Blue
              } as MenuOptions)
                .then(() => {
                  console.info('openMenu success');
                })
                .catch((err: Error) => {
                  console.info('openMenu error：' + err.message);
                })
            } catch (error) {
              let message = (error as BusinessError).message;
              let code = (error as BusinessError).code;
              console.error(`shjb+openMenu error code is ${code}, message is ${message}`);
            }
            ;
            setTimeout(() => {
              try {
                this.promptAction.updateMenu(contentNode, {
                  title: '20%',
                  outlineWidth: '400%',
                  outlineColor: Color.Blue
                } as MenuOptions, this.changeIsPartialUpdateList[this.changeIsPartialUpdateIndex])
                  .then(() => {
                    console.info('api20+updateMenu success');
                  })
                  .catch((err: Error) => {
                    console.info('api20+updateMenu error：' + '+' + err.message);
                  })
              } catch (error) {
                let message = (error as BusinessError).message;
                let code = (error as BusinessError).code;
                console.error(`api20+updateMenu error code is ${code}, message is ${message}`);
              }
              ;
            }, 2000);
          })
        Text(`resource-10vp->30vp`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .id('open6')
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(menuBuilder));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo6, {
                borderRadius: 0,
                title: 'app.float.outlineWidth',
                outlineWidth: $r('app.float.outlineWidth'),
                outlineColor: Color.Blue
              } as MenuOptions)
                .then(() => {
                  console.info('openMenu success');
                })
                .catch((err: Error) => {
                  console.info('openMenu error：' + err.message);
                })
            } catch (error) {
              let message = (error as BusinessError).message;
              let code = (error as BusinessError).code;
              console.error(`shjb+openMenu error code is ${code}, message is ${message}`);
            }
            ;
            setTimeout(() => {
              try {
                this.promptAction.updateMenu(contentNode, {
                  title: 'app.float.outlineWidth',
                  outlineWidth: $r('app.float.outlineWidth1'),
                  outlineColor: Color.Blue
                } as MenuOptions, this.changeIsPartialUpdateList[this.changeIsPartialUpdateIndex])
                  .then(() => {
                    console.info('api20+updateMenu success');
                  })
                  .catch((err: Error) => {
                    console.info('api20+updateMenu error：' + '+' + err.message);
                  })
              } catch (error) {
                let message = (error as BusinessError).message;
                let code = (error as BusinessError).code;
                console.error(`api20+updateMenu error code is ${code}, message is ${message}`);
              }
              ;
            }, 2000);
          })
      }

      Row({ space: 10 } as RowOptions) {
        Text(`30px->undefined`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .id('open7')
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(menuBuilder));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo7, {
                borderRadius: 0,
                title: '10px',
                outlineWidth: '30px',
                outlineColor: Color.Blue
              } as MenuOptions)
                .then(() => {
                  console.info('openMenu success');
                })
                .catch((err: Error) => {
                  console.info('openMenu error：' + err.message);
                })
            } catch (error) {
              let message = (error as BusinessError).message;
              let code = (error as BusinessError).code;
              console.error(`shjb+openMenu error code is ${code}, message is ${message}`);
            }
            ;
            setTimeout(() => {
              try {
                this.promptAction.updateMenu(contentNode, {
                  title: 'undefined',
                  outlineWidth: undefined,
                  outlineColor: Color.Blue
                } as MenuOptions, this.changeIsPartialUpdateList[this.changeIsPartialUpdateIndex])
                  .then(() => {
                    console.info('api20+updateMenu success');
                  })
                  .catch((err: Error) => {
                    console.info('api20+updateMenu error：' + '+' + err.message);
                  })
              } catch (error) {
                let message = (error as BusinessError).message;
                let code = (error as BusinessError).code;
                console.error(`api20+updateMenu error code is ${code}, message is ${message}`);
              }
              ;
            }, 2000);
          })
        Text(`30px->-1异常`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .id('open8')
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(menuBuilder));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo8, {
                borderRadius: 0,
                title: '10px',
                outlineWidth: '30px',
                outlineColor: Color.Blue
              } as MenuOptions)
                .then(() => {
                  console.info('openMenu success');
                })
                .catch((err: Error) => {
                  console.info('openMenu error：' + err.message);
                })
            } catch (error) {
              let message = (error as BusinessError).message;
              let code = (error as BusinessError).code;
              console.error(`shjb+openMenu error code is ${code}, message is ${message}`);
            }
            ;
            setTimeout(() => {
              try {
                this.promptAction.updateMenu(contentNode, {
                  title: '-1',
                  outlineWidth: -1,
                  outlineColor: Color.Blue
                } as MenuOptions, this.changeIsPartialUpdateList[this.changeIsPartialUpdateIndex])
                  .then(() => {
                    console.info('api20+updateMenu success');
                  })
                  .catch((err: Error) => {
                    console.info('api20+updateMenu error：' + '+' + err.message);
                  })
              } catch (error) {
                let message = (error as BusinessError).message;
                let code = (error as BusinessError).code;
                console.error(`api20+updateMenu error code is ${code}, message is ${message}`);
              }
              ;
            }, 2000);
          })
        Text(`EdgeOutlineWidths-10px->30px`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .id('open9')
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(menuBuilder));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo9, {
                borderRadius: 0,
                title: 'EdgeOutlineWidths',
                outlineWidth: {
                  left: '10px',
                  right: '20px',
                  top: '30px',
                  bottom: '40px'
                },
                outlineColor: Color.Blue
              } as MenuOptions)
                .then(() => {
                  console.info('openMenu success');
                })
                .catch((err: Error) => {
                  console.info('openMenu error：' + err.message);
                })
            } catch (error) {
              let message = (error as BusinessError).message;
              let code = (error as BusinessError).code;
              console.error(`shjb+openMenu error code is ${code}, message is ${message}`);
            }
            ;
            setTimeout(() => {
              try {
                this.promptAction.updateMenu(contentNode, {
                  title: 'EdgeOutlineWidths',
                  outlineWidth: {
                    left: -100,
                    right: '20px',
                    top: '30px',
                    bottom: '40px'
                  },
                  outlineColor: Color.Blue
                } as MenuOptions, this.changeIsPartialUpdateList[this.changeIsPartialUpdateIndex])
                  .then(() => {
                    console.info('api20+updateMenu success');
                  })
                  .catch((err: Error) => {
                    console.info('api20+updateMenu error：' + '+' + err.message);
                  })
              } catch (error) {
                let message = (error as BusinessError).message;
                let code = (error as BusinessError).code;
                console.error(`api20+updateMenu error code is ${code}, message is ${message}`);
              }
              ;
            }, 2000);
          })
      }

      Row({ space: 10 } as RowOptions) {
        Text(`更新borderRadius将属性outlineWidth:unde/不变`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .id('open10')
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(menuBuilder));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo10, {
                borderRadius: 0,
                title: '100lpx',
                outlineWidth: '100lpx',
                outlineColor: Color.Blue
              } as MenuOptions)
                .then(() => {
                  console.info('openMenu success');
                })
                .catch((err: Error) => {
                  console.info('openMenu error：' + err.message);
                })
            } catch (error) {
              let message = (error as BusinessError).message;
              let code = (error as BusinessError).code;
              console.error(`shjb+openMenu error code is ${code}, message is ${message}`);
            }
            ;
            setTimeout(() => {
              try {
                this.promptAction.updateMenu(contentNode, {
                  borderRadius: 100,
                } as MenuOptions, this.changeIsPartialUpdateList[this.changeIsPartialUpdateIndex])
                  .then(() => {
                    console.info('api20+updateMenu success');
                  })
                  .catch((err: Error) => {
                    console.info('api20+updateMenu error：' + '+' + err.message);
                  })
              } catch (error) {
                let message = (error as BusinessError).message;
                let code = (error as BusinessError).code;
                console.error(`api20+updateMenu error code is ${code}, message is ${message}`);
              }
              ;
            }, 2000);
          })
      }

      Button('切换数值')
        .onClick(() => {
          this.changeIndex++
          if (this.changeIndex > this.changeList.length - 1) {
            this.changeIndex = 0
          }
        })
      Row({ space: 10 } as RowOptions) {
        Text(`动态切换调用Menu`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .id('open')
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(menuBuilder));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo, {
                borderRadius: 0,
                title: '100lpx',
                outlineWidth: '100lpx',
                outlineColor: Color.Blue
              } as MenuOptions)
                .then(() => {
                  console.info('openMenu success');
                })
                .catch((err: Error) => {
                  console.info('openMenu error：' + err.message);
                })
            } catch (error) {
              let message = (error as BusinessError).message;
              let code = (error as BusinessError).code;
              console.error(`shjb+openMenu error code is ${code}, message is ${message}`);
            }
            ;
            setTimeout(() => {
              try {
                this.promptAction.updateMenu(contentNode, {
                  title: '' + this.changeList[this.changeIndex],
                  outlineWidth: this.changeList[this.changeIndex],
                  outlineColor: Color.Blue

                } as MenuOptions, this.changeIsPartialUpdateList[this.changeIsPartialUpdateIndex])
                  .then(() => {
                    console.info('api20+updateMenu success');
                  })
                  .catch((err: Error) => {
                    console.info('api20+updateMenu error：' + '+' + err.message);
                  })
              } catch (error) {
                let message = (error as BusinessError).message;
                let code = (error as BusinessError).code;
                console.error(`api20+updateMenu error code is ${code}, message is ${message}`);
              }
              ;
            }, 2000);
          })
      }

      Text('Index: ' + this.changeIndex + '数值: ' + this.changeList[this.changeIndex]).fontColor(Color.Red)
    }
    .width('100%')
    .height('100%')
  }
}