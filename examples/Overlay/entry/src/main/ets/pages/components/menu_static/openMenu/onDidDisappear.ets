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
  @State onDidDisappear: boolean = false;
  private uiContext: UIContext = this.getUIContext();
  private promptAction: PromptAction = this.uiContext.getPromptAction();
  private targetInfo: TargetInfo = {
    id: 'open',
  } as TargetInfo

  build() {
    Column({ space: 10 } as ColumnOptions) {
      Text(`onDidDisappear`)
        .fontSize(10)
        .backgroundColor(0x0000ff)
        .fontColor(0xffffff)
        .id('open')
        .padding(5)
        .onClick(() => {
          let contentNode = new ComponentContent(this.uiContext, wrapBuilder(MyMenu));
          try {
            this.promptAction.openMenu(contentNode, this.targetInfo, {
              title: 'onDidDisappear',
              onDisappear: () => {
                console.info("bindMenu2001 Menu,is onDisappear!");
              },
              onDidDisappear: () => {
                console.info("bindMenu2001 cycle life onDidDisappear");
                this.onDidDisappear = true;
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
      Text('onDidDisappear: ' + this.onDidDisappear).fontColor(Color.Red)
    }
    .width('100%')
    .height('100%')
  }
}
