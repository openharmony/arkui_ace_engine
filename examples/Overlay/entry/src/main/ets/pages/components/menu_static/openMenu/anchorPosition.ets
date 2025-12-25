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

  @State changeXIndex: Int = 0;
  @State changeXList: (Length | undefined)[] = [
    '10px' as Length, '20vp' as Length, '30fp' as Length, '40lpx' as Length, '20%' as Length, 30 as Length,
    $r('app.float.outlineWidth') as Length, undefined, -1 as Length
  ]
  @State changeYIndex: Int = 0;
  @State changeYList: (Length | undefined)[] = [
    '10px' as Length, '20vp' as Length, '30fp' as Length, '40lpx' as Length, '20%' as Length, 30 as Length,
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
  menuOptions: MenuOptions = {
    title: 'X: ' + this.changeXList[this.changeXIndex] + 'Y: ' + this.changeYList[this.changeYIndex],
    anchorPosition: { x: this.changeXList[this.changeXIndex], y: this.changeYList[this.changeYIndex] }
  } as MenuOptions

  build() {
    Column({ space: 10 } as ColumnOptions) {
      Text(`X:10px;Y:10px`)
        .fontSize(10)
        .backgroundColor(0x0000ff)
        .fontColor(0xffffff)
        .id('open1')
        .padding(5)
        .onClick(() => {
          let contentNode = new ComponentContent(this.uiContext, wrapBuilder(MyMenu));
          try {
            this.promptAction.openMenu(contentNode, this.targetInfo1, {
              title: 'X:10px;Y:10px',
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
        })
      Text(`X:20vp;Y:20vp`)
        .fontSize(10)
        .backgroundColor(0x0000ff)
        .fontColor(0xffffff)
        .id('open2')
        .padding(5)
        .onClick(() => {
          let contentNode = new ComponentContent(this.uiContext, wrapBuilder(MyMenu));
          try {
            this.promptAction.openMenu(contentNode, this.targetInfo2, {
              title: 'X:20vp;Y:20vp',
              anchorPosition: { x: '20vp', y: '20vp' }
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
      Text(`X:30fp;Y:30fp`)
        .fontSize(10)
        .backgroundColor(0x0000ff)
        .id('open3')
        .padding(5)
        .onClick(() => {
          let contentNode = new ComponentContent(this.uiContext, wrapBuilder(MyMenu));
          try {
            this.promptAction.openMenu(contentNode, this.targetInfo3, {
              title: 'X:30fp;Y:30fp',
              anchorPosition: { x: '30fp', y: '30fp' }
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
      Text(`X:40lpx;Y:40lpx`)
        .fontSize(10)
        .backgroundColor(0x0000ff)
        .fontColor(0xffffff)
        .id('open4')
        .padding(5)
        .onClick(() => {
          let contentNode = new ComponentContent(this.uiContext, wrapBuilder(MyMenu));
          try {
            this.promptAction.openMenu(contentNode, this.targetInfo4, {
              title: 'X:40lpx;Y:40lpx',
              anchorPosition: { x: '40lpx', y: '40lpx' }
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
      Text(`X:20%;Y:20%`)
        .fontSize(10)
        .backgroundColor(0x0000ff)
        .fontColor(0xffffff)
        .id('open5')
        .padding(5)
        .onClick(() => {
          let contentNode = new ComponentContent(this.uiContext, wrapBuilder(MyMenu));
          try {
            this.promptAction.openMenu(contentNode, this.targetInfo5, {
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
        })
      Text(`X:30;Y:30`)
        .fontSize(10)
        .backgroundColor(0x0000ff)
        .fontColor(0xffffff)
        .id('open6')
        .padding(5)
        .onClick(() => {
          let contentNode = new ComponentContent(this.uiContext, wrapBuilder(MyMenu));
          try {
            this.promptAction.openMenu(contentNode, this.targetInfo6, {
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
        })
      Text(`Resource-10vp`)
        .fontSize(10)
        .backgroundColor(0x0000ff)
        .fontColor(0xffffff)
        .id('open7')
        .padding(5)
        .onClick(() => {
          let contentNode = new ComponentContent(this.uiContext, wrapBuilder(MyMenu));
          try {
            this.promptAction.openMenu(contentNode, this.targetInfo7, {
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
        })
      Text(`undefined`)
        .fontSize(10)
        .backgroundColor(0x0000ff)
        .fontColor(0xffffff)
        .id('open8')
        .padding(5)
        .onClick(() => {
          let contentNode = new ComponentContent(this.uiContext, wrapBuilder(MyMenu));
          try {
            this.promptAction.openMenu(contentNode, this.targetInfo8, {
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
        })
      Text(`异常`)
        .fontSize(10)
        .backgroundColor(0x0000ff)
        .fontColor(0xffffff)
        .id('open9')
        .padding(5)
        .onClick(() => {
          let contentNode = new ComponentContent(this.uiContext, wrapBuilder(MyMenu));
          try {
            this.promptAction.openMenu(contentNode, this.targetInfo9, {
              title: '-1',
              anchorPosition: { x: -1, y: -1 }
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
      Text(`预览状态`)
        .fontSize(10)
        .backgroundColor(0x0000ff)
        .fontColor(0xffffff)
        .id('open10')
        .padding(5)
        .onClick(() => {
          let contentNode = new ComponentContent(this.uiContext, wrapBuilder(MyMenu));
          try {
            this.promptAction.openMenu(contentNode, this.targetInfo10, {
              title: '预览状态',
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
      Text(`与offset叠加覆盖组件`)
        .fontSize(10)
        .backgroundColor(0x0000ff)
        .fontColor(0xffffff)
        .id('open11')
        .padding(5)
        .onClick(() => {
          let contentNode = new ComponentContent(this.uiContext, wrapBuilder(MyMenu));
          try {
            this.promptAction.openMenu(contentNode, this.targetInfo11, {
              title: '预览状态',
              offset: { x: 100, y: 0 },
              anchorPosition: { x: 100, y: 0 }
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
      Text(`placement预设优先显示不生效`)
        .fontSize(10)
        .backgroundColor(0x0000ff)
        .fontColor(0xffffff)
        .id('open12')
        .padding(5)
        .onClick(() => {
          let contentNode = new ComponentContent(this.uiContext, wrapBuilder(MyMenu));
          try {
            this.promptAction.openMenu(contentNode, this.targetInfo12, {
              title: '预览状态',
              placement: Placement.Left,
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
        .id('open')
        .padding(5)
        .onClick(() => {
          let contentNode = new ComponentContent(this.uiContext, wrapBuilder(MyMenu));
          try {
            this.promptAction.openMenu(contentNode, this.targetInfo, {
              title: 'X: ' + this.changeXList[this.changeXIndex] + 'Y: ' + this.changeYList[this.changeYIndex],
              anchorPosition: { x: this.changeXList[this.changeXIndex], y: this.changeYList[this.changeYIndex] }
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

      Text('XIndex: ' + this.changeXIndex + '数值: ' + this.changeXList[this.changeXIndex]).fontColor(Color.Red)
      Text('YIndex: ' + this.changeYIndex + '数值: ' + this.changeYList[this.changeYIndex]).fontColor(Color.Red)
    }
    .width('100%')
    .height('100%')
  }
}
