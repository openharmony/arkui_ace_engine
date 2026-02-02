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
      builder: subMenuBuilder,
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

  @State changeXIndex: Int = 0;
  @State changeXList: (Length | undefined)[] = [
    '30px' as Length, '30vp' as Length, '30fp' as Length, '30lpx' as Length, '20%' as Length, 30 as Length,
    $r('app.float.outlineWidth') as Length, undefined, -1 as Length
  ]
  @State changeYIndex: Int = 0;
  @State changeYList: (Length | undefined)[] = [
    '30px' as Length, '30vp' as Length, '30fp' as Length, '30lpx' as Length, '20%' as Length, 30 as Length,
    $r('app.float.outlineWidth') as Length, undefined, -1 as Length
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
  menuOptions: MenuOptions = {
    title: 'X: ' + this.changeXList[this.changeXIndex] + 'Y: ' + this.changeYList[this.changeYIndex],
    anchorPosition: { x: this.changeXList[this.changeXIndex], y: this.changeYList[this.changeYIndex] }
  } as MenuOptions
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
      Text(`X:10px;Y:10px->X:30px;Y:30px`)
        .fontSize(10)
        .backgroundColor(0x0000ff)
        .fontColor(0xffffff)
        .padding(5)
        .id('open1')
        .onClick(() => {
          let contentNode = new ComponentContent(this.uiContext, wrapBuilder(menuBuilder));
          try {
            this.promptAction.openMenu(contentNode, this.targetInfo1, {
              title: 'X:10px;Y:10px',
              borderRadius: 0,
              anchorPosition: { x: '10px', y: '10px' }
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
                anchorPosition: { x: '30px', y: '30px' }
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
      Text(`X:10vp;Y:10vp->X:30vp;Y:30vp`)
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
              title: 'X:10vp;Y:10vp',
              anchorPosition: { x: '10vp', y: '10vp' }
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
                anchorPosition: { x: '30vp', y: '30vp' }
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
      Text(`X:10fp;Y:10fp->X:30fp;Y:30fp`)
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
              title: 'X:10fp;Y:10fp',
              anchorPosition: { x: '10fp', y: '10fp' }
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
                anchorPosition: { x: '30fp', y: '30fp' }
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
      Text(`X:10lpx;Y:10lpx->X:30lpx;Y:30lpx`)
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
              title: 'X:10lpx;Y:10lpx',
              anchorPosition: { x: '10lpx', y: '10lpx' }
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
                anchorPosition: { x: '30lpx', y: '30lpx' }
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
      Text(`X:20%;Y:20%->X:40%;Y:40%`)
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
              title: 'X:20%;Y:20%%',
              anchorPosition: { x: '20%', y: '20%' }
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
                anchorPosition: { x: '40%', y: '40%' }
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
      Text(`X:30;Y:30->X:100;Y:100`)
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
              title: 'X:30;Y:30',
              anchorPosition: { x: 30, y: 30 }
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
                anchorPosition: { x: 100, y: 100 }
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
      Text(`Resource-10vp->30vp`)
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
              title: 'EdgeOutlineWidths',
              anchorPosition: { x: $r('app.float.outlineWidth'), y: $r('app.float.outlineWidth') }
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
                anchorPosition: { x: $r('app.float.outlineWidth1'), y: $r('app.float.outlineWidth1') }
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
      Text(`undefined->X:100;Y:100`)
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
              title: 'undefined',
              anchorPosition: { x: undefined, y: undefined }
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
                anchorPosition: { x: 100, y: 100 }
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
      Text(`undefined->X:-100;Y:-100`)
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
              title: 'undefined',
              anchorPosition: undefined
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
                anchorPosition: { x: -100, y: -100 }
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
      Text(`更新borderRadius将属性anchorPosition:unde/不变`)
        .fontSize(10)
        .backgroundColor(0x0000ff)
        .fontColor(0xffffff)
        .padding(5)
        .id('open20')
        .onClick(() => {
          let contentNode = new ComponentContent(this.uiContext, wrapBuilder(menuBuilder));
          try {
            this.promptAction.openMenu(contentNode, this.targetInfo20, {
              borderRadius: 0,
              title: 'undefined',
              anchorPosition: { x: 100, y: 100 }
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
                borderRadius: 100
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
      Text(`预览状态`)
        .fontSize(10)
        .backgroundColor(0x0000ff)
        .fontColor(0xffffff)
        .padding(5)
        .id('open21')
        .onClick(() => {
          let contentNode = new ComponentContent(this.uiContext, wrapBuilder(menuBuilder));
          try {
            this.promptAction.openMenu(contentNode, this.targetInfo21, {
              borderRadius: 0,
              title: 'undefined',
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
              anchorPosition: undefined
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
                anchorPosition: { x: 100, y: 100 }
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
      Text(`与offset叠加覆盖组件`)
        .fontSize(10)
        .backgroundColor(0x0000ff)
        .fontColor(0xffffff)
        .padding(5)
        .id('open22')
        .onClick(() => {
          let contentNode = new ComponentContent(this.uiContext, wrapBuilder(menuBuilder));
          try {
            this.promptAction.openMenu(contentNode, this.targetInfo22, {
              borderRadius: 0,
              title: 'undefined',
              anchorPosition: undefined
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
                offset: { x: 100, y: 0 },
                anchorPosition: { x: 100, y: 0 }
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
      Text(`placement预设优先显示不生效`)
        .fontSize(10)
        .backgroundColor(0x0000ff)
        .fontColor(0xffffff)
        .padding(5)
        .id('open23')
        .onClick(() => {
          let contentNode = new ComponentContent(this.uiContext, wrapBuilder(menuBuilder));
          try {
            this.promptAction.openMenu(contentNode, this.targetInfo23, {
              borderRadius: 0,
              title: 'undefined',
              anchorPosition: undefined
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
                placement: Placement.Left,
                anchorPosition: { x: 100, y: 100 }
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
      Button('切换X')
        .onClick(() => {
          this.changeXIndex++
          if (this.changeXIndex > this.changeXList.length - 1) {
            this.changeXIndex = 0
          }
        })
      Button('切换Y')
        .onClick(() => {
          this.changeYIndex++
          if (this.changeYIndex > this.changeYList.length - 1) {
            this.changeYIndex = 0
          }
        })
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
              anchorPosition: { x: '30vp', y: '30vp' }
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
                title: 'X: ' + this.changeXList[this.changeXIndex] + 'Y: ' + this.changeYList[this.changeYIndex],
                anchorPosition: { x: this.changeXList[this.changeXIndex], y: this.changeYList[this.changeYIndex] }
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

      Text('XIndex: ' + this.changeXIndex + '数值: ' + this.changeXList[this.changeXIndex]).fontColor(Color.Red)
      Text('YIndex: ' + this.changeYIndex + '数值: ' + this.changeYList[this.changeYIndex]).fontColor(Color.Red)
    }
    .width('100%')
    .height('100%')
  }
}