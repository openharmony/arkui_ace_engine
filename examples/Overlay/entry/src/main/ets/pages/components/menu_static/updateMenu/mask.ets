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

let startIcon: ResourceStr = $r('app.media.startIcon')
let endIcon: ResourceStr = $r('app.media.startIcon')
let subMenuExpandingMode: SubMenuExpandingMode | undefined = SubMenuExpandingMode.SIDE_EXPAND;

@Builder
function SubMenuBuilder() {
  Menu() {
    MenuItem({
      startIcon: $r('app.media.startIcon'),
      content: "图标",
      builder: SubMenuBuilder,
    } as MenuItemOptions)
    MenuItem({
      startIcon: $r('app.media.startIcon'),
      content: "列表",
      builder: SubMenuBuilder,
    } as MenuItemOptions)
  }.backgroundColor(Color.Grey)
}

@Builder
function MyMenu() {
  Menu() {
    MenuItem({
      startIcon: startIcon,
      endIcon: endIcon,
      content: "新建文件夹",
      builder: SubMenuBuilder,
    } as MenuItemOptions)
    MenuItem({
      startIcon: startIcon,
      content: "排序方式",
      builder: SubMenuBuilder,
    } as MenuItemOptions)
    MenuItem({
      startIcon: startIcon,
      content: "查看方式",
      builder: SubMenuBuilder,
    } as MenuItemOptions)
  }
  .backgroundColor(Color.Grey)
  .subMenuExpandingMode(subMenuExpandingMode)
}

@Entry
@Component
struct Index {
  @Builder
  MyPreview() {
    Column({ space: 10 } as ColumnOptions) {
      Image($r('app.media.startIcon'))
        .width(200)
        .height(200)
    }
  }

  @State changeIndex: Int = 0;
  @State changeList: (ResourceColor | undefined)[] = [
    'rgba(23,169,141,0.5)' as ResourceColor, Color.Red as ResourceColor, '#FFFFFF00' as ResourceColor,
    12345 as ResourceColor, $r('app.color.blue') as ResourceColor, undefined,
    $r('app.string.errorColor') as ResourceColor
  ]
  @State changeBlurIndex: Int = 0;
  @State changeBlurList: (BlurStyle | undefined)[] = [
    BlurStyle.Thin, BlurStyle.Regular, BlurStyle.Thick, BlurStyle.BACKGROUND_THIN, BlurStyle.BACKGROUND_REGULAR,
    BlurStyle.BACKGROUND_THICK, BlurStyle.BACKGROUND_ULTRA_THICK, BlurStyle.NONE, BlurStyle.COMPONENT_ULTRA_THIN,
    BlurStyle.COMPONENT_THIN, BlurStyle.COMPONENT_REGULAR, BlurStyle.COMPONENT_THICK, BlurStyle.COMPONENT_ULTRA_THICK,
    undefined
  ]
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
  private targetInfo11: TargetInfo = {
    id: 'open11',
  } as TargetInfo
  private targetInfo12: TargetInfo = {
    id: 'open12',
  } as TargetInfo
  private targetInfo13: TargetInfo = {
    id: 'open13',
  } as TargetInfo
  private targetInfo14: TargetInfo = {
    id: 'open14',
  } as TargetInfo
  private targetInfo15: TargetInfo = {
    id: 'open15',
  } as TargetInfo
  private targetInfo16: TargetInfo = {
    id: 'open16',
  } as TargetInfo
  private targetInfo17: TargetInfo = {
    id: 'open17',
  } as TargetInfo
  private targetInfo18: TargetInfo = {
    id: 'open18',
  } as TargetInfo
  private targetInfo19: TargetInfo = {
    id: 'open19',
  } as TargetInfo
  private targetInfo20: TargetInfo = {
    id: 'open20',
  } as TargetInfo
  private targetInfo21: TargetInfo = {
    id: 'open21',
  } as TargetInfo
  private targetInfo22: TargetInfo = {
    id: 'open22',
  } as TargetInfo
  private targetInfo23: TargetInfo = {
    id: 'open23',
  } as TargetInfo
  private targetInfo24: TargetInfo = {
    id: 'open24',
  } as TargetInfo
  private targetInfo25: TargetInfo = {
    id: 'open25',
  } as TargetInfo
  menuOptions: MenuOptions = {
    title: '' + this.changeList[this.changeIndex] + '---' + this.changeBlurList[this.changeBlurIndex],
    mask: { color: this.changeList[this.changeIndex], backgroundBlurStyle: this.changeBlurList[this.changeBlurIndex] }

  } as MenuOptions
  @State changeIsPartialUpdateIndex: Int = 0;
  @State changeIsPartialUpdateList: (Boolean)[] = [
    false, true
  ]
  @State IsPartialUpdate: string = '全量';

  build() {
    Column({ space: 10 } as ColumnOptions) {
      Button('切换全量/增量')
        .onClick(() => {
          this.changeIsPartialUpdateIndex++
          if (this.changeIsPartialUpdateIndex > this.changeIsPartialUpdateList.length - 1) {
            this.changeIsPartialUpdateIndex = 0
          }
          if (this.changeIsPartialUpdateIndex == 0) {
            this.IsPartialUpdate = '全量'
          } else {
            this.IsPartialUpdate = '增量'
          }
        })
      Text('' + this.IsPartialUpdate).fontColor(Color.Red).fontSize(30)
      Text('Color').fontColor(Color.Red).fontSize(30)
      Row({ space: 10 } as RowOptions) {
        Text(`Color.Blue->Red`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .id('open1')
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(MyMenu));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo1, {
                borderRadius: 0,
                title: 'Color.Red',
                mask: { color: Color.Blue, backgroundBlurStyle: BlurStyle.Thin }

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
                  title: 'Color.Red',
                  mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.Thin }
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
        Text(`rgba(23,169,141,0.5)->(169,23,141,0.5)`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .id('open2')
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(MyMenu));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo2, {
                borderRadius: 0,
                title: 'rgba(23,169,141,0.5)',
                mask: { color: 'rgba(23,169,141,0.5)', backgroundBlurStyle: BlurStyle.Thin }

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
                  title: 'rgba(169,23,141,0.5)',
                  mask: { color: 'rgba(169,23,141,0.5)', backgroundBlurStyle: BlurStyle.Thin }
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
        Text(`#87F787->#FFFFFF00`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .id('open3')
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(MyMenu));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo3, {
                borderRadius: 0,
                title: '#87F787',
                mask: { color: '#87F787', backgroundBlurStyle: BlurStyle.Thin }
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
                  title: '#FFFFFF00',
                  mask: { color: '#FFFFFF00', backgroundBlurStyle: BlurStyle.Thin }
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
        Text(`54321->12345`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .id('open4')
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(MyMenu));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo4, {
                borderRadius: 0,
                title: '54321',
                mask: { color: 54321, backgroundBlurStyle: BlurStyle.Thin }

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
                  title: '12345',
                  mask: { color: 12345, backgroundBlurStyle: BlurStyle.Thin }
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
        Text(`Color.Red->undefined`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .id('open5')
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(MyMenu));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo5, {
                borderRadius: 0,
                title: 'Color.Red',
                mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.Thin }
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
                  mask: { color: undefined, backgroundBlurStyle: BlurStyle.Thin }
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
        Text(`app.color.green->blue`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .id('open6')
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(MyMenu));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo6, {
                borderRadius: 0,
                title: 'app.color.green',
                mask: { color: $r('app.color.green'), backgroundBlurStyle: BlurStyle.Thin }

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
                  title: 'app.color.blue',
                  mask: { color: $r('app.color.blue'), backgroundBlurStyle: BlurStyle.Thin }
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
        Text(`Color.Red->异常`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .id('open22')
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(MyMenu));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo22, {
                borderRadius: 0,
                title: 'Color.Red',
                mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.Thin }
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
                  title: '异常',
                  mask: { color: $r('app.string.errorColor'), backgroundBlurStyle: BlurStyle.Thin }
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
        Text(`Color.Red->预览默认显示蒙层`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .id('open23')
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(MyMenu));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo23, {
                borderRadius: 0,
                title: 'Color.Red',
                preview: this.MyPreview,
                previewBorderRadius: 50,
                previewAnimationOptions: {
                  scale: [0, 0],
                  transition: TransitionEffect.OPACITY.animation({ duration: 4000, curve: Curve.Ease }).combine(
                    TransitionEffect.rotate({ z: 1, angle: 180 })),
                  hoverScale: [1.0, 0.95],
                  hoverScaleInterruption: true,
                },
                previewScaleMode: PreviewScaleMode.AUTO,
                mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.Thin }
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
                  title: '异常',
                  preview: this.MyPreview,
                  previewBorderRadius: 50,
                  previewAnimationOptions: {
                    scale: [0, 0],
                    transition: TransitionEffect.OPACITY.animation({ duration: 4000, curve: Curve.Ease }).combine(
                      TransitionEffect.rotate({ z: 1, angle: 180 })),
                    hoverScale: [1.0, 0.95],
                    hoverScaleInterruption: true,
                  },
                  previewScaleMode: PreviewScaleMode.AUTO,
                  mask: { color: Color.Blue, backgroundBlurStyle: BlurStyle.Thin }
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

      Text('backgroundBlurStyle').fontColor(Color.Red).fontSize(30)
      Row({ space: 10 } as RowOptions) {
        Text(`BlurStyle.Regular->Thin`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .id('open7')
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(MyMenu));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo7, {
                borderRadius: 0,
                title: 'BlurStyle.Regular',
                mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.Regular }
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
                  title: 'BlurStyle.Thin',
                  mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.Thin }
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
        Text(`BlurStyle.Thin->Regular`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .id('open8')
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(MyMenu));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo8, {
                borderRadius: 0,
                title: 'BlurStyle.Thin',
                mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.Thin }
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
                  title: 'BlurStyle.Regular',
                  mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.Regular }
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
        Text(`BlurStyle.Thin->Thick`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .id('open9')
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(MyMenu));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo9, {
                borderRadius: 0,
                title: 'BlurStyle.Thin',
                mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.Thin }
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
                  title: 'BlurStyle.Thick',
                  mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.Thick }
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
        Text(`BlurStyle.Thin->BACKGROUND_THIN`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .id('open10')
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(MyMenu));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo10, {
                borderRadius: 0,
                title: 'BlurStyle.Thin',
                mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.Thin }
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
                  title: 'BlurStyle.BACKGROUND_THIN',
                  mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.BACKGROUND_THIN }
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
        Text(`BlurStyle.Thin->BACKGROUND_REGULAR`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .id('open11')
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(MyMenu));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo11, {
                borderRadius: 0,
                title: 'BlurStyle.Thin',
                mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.Thin }
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
                  title: 'BlurStyle.BACKGROUND_REGULAR',
                  mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.BACKGROUND_REGULAR }
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
        Text(`BlurStyle.Thin->BACKGROUND_THICK`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .id('open12')
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(MyMenu));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo12, {
                borderRadius: 0,
                title: 'BlurStyle.Thin',
                mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.Thin }
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
                  title: 'BlurStyle.BACKGROUND_THICK',
                  mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.BACKGROUND_THICK }
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
        Text(`BlurStyle.Thin->BACKGROUND_ULTRA_THICK`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .id('open13')
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(MyMenu));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo13, {
                borderRadius: 0,
                title: 'BlurStyle.Thin',
                mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.Thin }
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
                  title: 'BlurStyle.BACKGROUND_ULTRA_THICK',
                  mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.BACKGROUND_ULTRA_THICK }
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
        Text(`BlurStyle.Thin->NONE`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .id('open14')
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(MyMenu));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo14, {
                borderRadius: 0,
                title: 'BlurStyle.Thin',
                mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.Thin }
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
                  title: 'BlurStyle.NONE',
                  mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.NONE }
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
        Text(`BlurStyle.Thin->COMPONENT_ULTRA_THIN`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .id('open15')
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(MyMenu));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo15, {
                borderRadius: 0,
                title: 'BlurStyle.Thin',
                mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.Thin }
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
                  title: 'BlurStyle.COMPONENT_ULTRA_THIN',
                  mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.COMPONENT_ULTRA_THIN }
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
        Text(`BlurStyle.Thin->COMPONENT_THIN`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .id('open16')
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(MyMenu));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo16, {
                borderRadius: 0,
                title: 'BlurStyle.Thin',
                mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.Thin }
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
                  title: 'BlurStyle.COMPONENT_THIN',
                  mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.COMPONENT_THIN }
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
        Text(`BlurStyle.Thin->COMPONENT_REGULAR`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .id('open17')
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(MyMenu));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo17, {
                borderRadius: 0,
                title: 'BlurStyle.Thin',
                mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.Thin }
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
                  title: 'BlurStyle.COMPONENT_REGULAR',
                  mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.COMPONENT_REGULAR }
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
        Text(`BlurStyle.Thin->COMPONENT_THICK`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .id('open18')
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(MyMenu));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo18, {
                borderRadius: 0,
                title: 'BlurStyle.Thin',
                mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.Thin }
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
                  title: 'BlurStyle.COMPONENT_THICK',
                  mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.COMPONENT_THICK }
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
        Text(`BlurStyle.Thin->COMPONENT_ULTRA_THICK`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .id('open19')
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(MyMenu));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo19, {
                borderRadius: 0,
                title: 'BlurStyle.Thin',
                mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.Thin }
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
                  title: 'BlurStyle.COMPONENT_ULTRA_THICK',
                  mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.COMPONENT_ULTRA_THICK }
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
        Text(`Thin->undefined`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .id('open20')
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(MyMenu));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo20, {
                borderRadius: 0,
                title: 'BlurStyle.Thin',
                mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.Thin }
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
                  mask: { color: Color.Red, backgroundBlurStyle: undefined }
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
        Text(`false->true`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .id('open24')
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(MyMenu));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo24, {
                borderRadius: 0,
                title: 'false',
                mask: false
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
                  title: 'true',
                  mask: true
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
        Text(`true->false`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .id('open25')
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(MyMenu));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo25, {
                borderRadius: 0,
                title: 'true',
                mask: true
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
                  title: 'false',
                  mask: false
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
        Text(`更新borderRadius将属性mask:unde/不变`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .id('open21')
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(MyMenu));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo21, {
                borderRadius: 0,
                mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.Thin }
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

      Row({ space: 10 } as RowOptions) {
        Button('切换color')
          .onClick(() => {
            this.changeIndex++
            if (this.changeIndex > this.changeList.length - 1) {
              this.changeIndex = 0
            }
          })
        Button('切换blur')
          .onClick(() => {
            this.changeBlurIndex++
            if (this.changeBlurIndex > this.changeBlurList.length - 1) {
              this.changeBlurIndex = 0
            }
          })
      }

      Row({ space: 10 } as RowOptions) {
        Text(`动态切换调用Menu`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .id('open')
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(MyMenu));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo, {
                borderRadius: 0,
                mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.Thin }
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
                  title: '' + this.changeList[this.changeIndex] + '---' + this.changeBlurList[this.changeBlurIndex],
                  mask: {
                    color: this.changeList[this.changeIndex],
                    backgroundBlurStyle: this.changeBlurList[this.changeBlurIndex]
                  }

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
      Text('Index: ' + this.changeBlurIndex + '数值: ' + this.changeBlurList[this.changeBlurIndex])
        .fontColor(Color.Green)
    }
    .width('100%')
    .height('100%')
  }
}
