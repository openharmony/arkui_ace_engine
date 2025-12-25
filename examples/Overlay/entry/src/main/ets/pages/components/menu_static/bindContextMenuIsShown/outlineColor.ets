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
      startIcon: startIcon,
      content: "图标",
      builder: SubMenuBuilder,
    } as MenuItemOptions)
    MenuItem({
      startIcon: startIcon,
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
  @State isShow0: boolean = false;
  @State isShow1: boolean = false;
  @State isShow2: boolean = false;
  @State isShow3: boolean = false;
  @State isShow4: boolean = false;
  @State isShow5: boolean = false;
  @State isShow6: boolean = false;
  @State isShow7: boolean = false;
  @State isShow8: boolean = false;
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
  contextMenuOptions: ContextMenuOptions = {
    outlineWidth: '10px',
    outlineColor: this.changeList[this.changeIndex]

  } as ContextMenuOptions

  build() {
    Column({ space: 10 } as ColumnOptions) {
      Row({ space: 10 } as RowOptions) {
        Text(`Color.Red`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindContextMenu(this.isShow0, MyMenu, {
            outlineWidth: '10px',
            outlineColor: Color.Red
          } as ContextMenuOptions)
          .onClick(() => {
            this.isShow0 = !this.isShow0;
          })
        Text(`'#FFFFFF00'`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindContextMenu(this.isShow1, MyMenu, {
            outlineWidth: '10px',
            outlineColor: '#FFFFFF00'
          } as ContextMenuOptions)
          .onClick(() => {
            this.isShow1 = !this.isShow1;
          })
        Text(`12345`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindContextMenu(this.isShow2, MyMenu, {
            outlineWidth: '10px',
            outlineColor: 12345
          } as ContextMenuOptions)
          .onClick(() => {
            this.isShow2 = !this.isShow2;
          })
      }

      Row({ space: 10 } as RowOptions) {
        Text(`app.color.blue`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindContextMenu(this.isShow3, MyMenu, {
            outlineWidth: '10px',
            outlineColor: $r('app.color.blue')
          } as ContextMenuOptions)
          .onClick(() => {
            this.isShow3 = !this.isShow3;
          })
        Text(`undefined`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindContextMenu(this.isShow4, MyMenu, {
            outlineWidth: '10px',
            outlineColor: undefined
          } as ContextMenuOptions)
          .onClick(() => {
            this.isShow4 = !this.isShow4;
          })
        Text(`EdgeColors`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindContextMenu(this.isShow5, MyMenu, {
            outlineWidth: '10px',
            outlineColor: {
              left: Color.Red,
              right: '#FFFFFF00',
              top: 12345,
              bottom: $r('app.string.errorColor')
            }
          } as ContextMenuOptions)
          .onClick(() => {
            this.isShow5 = !this.isShow5;
          })
      }

      Row({ space: 10 } as RowOptions) {
        Text(`异常`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindContextMenu(this.isShow6, MyMenu, {
            outlineWidth: '10px',
            outlineColor: $r('app.string.errorColor')
          } as ContextMenuOptions)
          .onClick(() => {
            this.isShow6 = !this.isShow6;
          })
        Text(`rgba(23,169,141,0.5)`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindContextMenu(this.isShow7, MyMenu, {
            outlineWidth: '10px',
            outlineColor: 'rgba(23,169,141,0.5)'
          } as ContextMenuOptions)
          .onClick(() => {
            this.isShow7 = !this.isShow7;
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
          .bindContextMenu(this.isShow8, MyMenu, {
            outlineWidth: '10px',
            outlineColor: this.changeList[this.changeIndex]

          } as ContextMenuOptions)
          .onClick(() => {
            this.isShow8 = !this.isShow8;
          })
      }

      Text('Index: ' + this.changeIndex + '数值: ' + this.changeList[this.changeIndex]).fontColor(Color.Red)
    }
    .width('100%')
    .height('100%')
  }
}
