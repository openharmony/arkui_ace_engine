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
      builder: SubMenuBuilder,
    } as MenuItemOptions)
  }
  .backgroundColor(Color.Grey)
  .subMenuExpandingMode(subMenuExpandingMode)
}

@Entry
@Component
struct Index {
  @State changeIndex: Int = 0;
  @State changeList: (ResourceColor | EdgeColors | undefined)[] = [
    'rgba(23,169,141,0.5)' as ResourceColor, Color.Red as ResourceColor, '#FFFFFF00' as ResourceColor,
    12345 as ResourceColor, $r('app.color.blue') as ResourceColor, $r('app.string.errorColor') as ResourceColor,
    undefined, {
    left: Color.Red,
    right: '#FFFFFF00',
    top: 12345,
    bottom: $r('app.string.errorColor')
  } as EdgeColors,
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
  menuOptions: MenuOptions = {
    title: '' + this.changeList[this.changeIndex],
    outlineWidth: '10px',
    outlineColor: this.changeList[this.changeIndex]

  } as MenuOptions

  build() {
    Column({ space: 10 } as ColumnOptions) {
      Row({ space: 10 } as RowOptions) {
        Text(`Color.Red`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .id('open1')
          .padding(5)
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(MyMenu));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo1, {
                title: 'Color.Red',
                outlineWidth: '10px',
                outlineColor: Color.Red
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
          })
        Text(`'#FFFFFF00'`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .id('open2')
          .padding(5)
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(MyMenu));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo2, {
                title: '#FFFFFF00',
                outlineWidth: '10px',
                outlineColor: '#FFFFFF00'
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
          })
        Text(`12345`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .id('open3')
          .padding(5)
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(MyMenu));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo3, {
                title: '12345',
                outlineWidth: '10px',
                outlineColor: 12345
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
          })
      }

      Row({ space: 10 } as RowOptions) {
        Text(`app.color.blue`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .id('open4')
          .padding(5)
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(MyMenu));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo4, {
                title: 'app.color.blue',
                outlineWidth: '10px',
                outlineColor: $r('app.color.blue')
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
          })
        Text(`undefined`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .id('open5')
          .padding(5)
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(MyMenu));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo5, {
                title: 'undefined',
                outlineWidth: '10px',
                outlineColor: undefined
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
          })
        Text(`EdgeColors`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .id('open6')
          .padding(5)
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(MyMenu));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo6, {
                title: 'EdgeColors',
                outlineWidth: '10px',
                outlineColor: {
                  left: Color.Red,
                  right: '#FFFFFF00',
                  top: 12345,
                  bottom: $r('app.string.errorColor')
                }
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
          })
      }

      Row({ space: 10 } as RowOptions) {
        Text(`异常`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .id('open7')
          .padding(5)
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(MyMenu));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo7, {
                title: '异常',
                outlineWidth: '10px',
                outlineColor: $r('app.string.errorColor')
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
          })
        Text(`rgba(23,169,141,0.5)`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .id('open8')
          .padding(5)
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(MyMenu));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo8, {
                title: 'rgba(23,169,141,0.5)',
                outlineWidth: '10px',
                outlineColor: 'rgba(23,169,141,0.5)'
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
          .id('open')
          .padding(5)
          .onClick(() => {
            let contentNode = new ComponentContent(this.uiContext, wrapBuilder(MyMenu));
            try {
              this.promptAction.openMenu(contentNode, this.targetInfo, {
                title: '' + this.changeList[this.changeIndex],
                outlineWidth: '10px',
                outlineColor: this.changeList[this.changeIndex]

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
          })
      }

      Text('Index: ' + this.changeIndex + '数值: ' + this.changeList[this.changeIndex]).fontColor(Color.Red)
    }
    .width('100%')
    .height('100%')
  }
}
