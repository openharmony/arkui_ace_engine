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
  @State changeList: (PreviewScaleMode | undefined)[] = [
    PreviewScaleMode.AUTO, undefined, PreviewScaleMode.CONSTANT, PreviewScaleMode.MAINTAIN
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
  menuOptions: MenuOptions = {
    title: '' + this.changeList[this.changeIndex],
    preview: MenuPreviewMode.IMAGE,
    previewBorderRadius: 50,
    previewScaleMode: this.changeList[this.changeIndex]

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
      Row({ space: 10 } as RowOptions) {
        Text(`CONSTANT->AUTO`)
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
                title: 'CONSTANT',

                preview: MenuPreviewMode.IMAGE,
                previewBorderRadius: 50,
                previewAnimationOptions: { scale: [0.5, 20.0] } as ContextMenuAnimationOptions,
                previewScaleMode: PreviewScaleMode.CONSTANT

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
                  title: 'AUTO',
                  preview: MenuPreviewMode.IMAGE,
                  previewBorderRadius: 50,
                  previewAnimationOptions: { scale: [0.5, 20.0] } as ContextMenuAnimationOptions,
                  previewScaleMode: PreviewScaleMode.AUTO
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
        Text(`AUTO->CONSTANT`)
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
                title: 'AUTO',
                preview: MenuPreviewMode.IMAGE,
                previewBorderRadius: 50,
                previewAnimationOptions: { scale: [0.5, 20.0] } as ContextMenuAnimationOptions,
                previewScaleMode: PreviewScaleMode.AUTO

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
                  title: 'CONSTANT',
                  preview: MenuPreviewMode.IMAGE,
                  previewBorderRadius: 50,
                  previewAnimationOptions: { scale: [0.5, 20.0] } as ContextMenuAnimationOptions,
                  previewScaleMode: PreviewScaleMode.CONSTANT
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
        Text(`CONSTANT->MAINTAIN`)
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
                title: 'CONSTANT',
                preview: MenuPreviewMode.IMAGE,
                previewBorderRadius: 50,
                previewAnimationOptions: { scale: [0.5, 20.0] } as ContextMenuAnimationOptions,
                previewScaleMode: PreviewScaleMode.CONSTANT

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
                  title: 'MAINTAIN',
                  preview: MenuPreviewMode.IMAGE,
                  previewBorderRadius: 50,
                  previewAnimationOptions: { scale: [0.5, 20.0] } as ContextMenuAnimationOptions,
                  previewScaleMode: PreviewScaleMode.MAINTAIN
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
        Text(`CONSTANT->undefined`)
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
                title: 'CONSTANT',
                preview: MenuPreviewMode.IMAGE,
                previewBorderRadius: 50,
                previewAnimationOptions: { scale: [0.5, 20.0] } as ContextMenuAnimationOptions,
                previewScaleMode: PreviewScaleMode.CONSTANT

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
                  preview: MenuPreviewMode.IMAGE,
                  previewBorderRadius: 50,
                  previewAnimationOptions: { scale: [0.5, 20.0] } as ContextMenuAnimationOptions,
                  previewScaleMode: undefined
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
        Text(`更新borderRadius将属性previewScaleMode: unde/不变`)
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
                title: 'CONSTANT',
                preview: MenuPreviewMode.IMAGE,
                previewBorderRadius: 50,
                previewAnimationOptions: { scale: [0.5, 20.0] } as ContextMenuAnimationOptions,
                previewScaleMode: PreviewScaleMode.CONSTANT
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
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(MyMenu));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo, {
                title: '' + this.changeList[this.changeIndex],
                preview: MenuPreviewMode.IMAGE,
                previewBorderRadius: 50,
                previewAnimationOptions: { scale: [0.5, 20.0] } as ContextMenuAnimationOptions,
                previewScaleMode: PreviewScaleMode.CONSTANT

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
                  borderRadius: 0,
                  title: 'this.changeList[this.changeIndex]',
                  preview: MenuPreviewMode.IMAGE,
                  previewBorderRadius: 50,
                  previewAnimationOptions: { scale: [0.5, 20.0] } as ContextMenuAnimationOptions,
                  previewScaleMode: this.changeList[this.changeIndex]
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
