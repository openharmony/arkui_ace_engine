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
  @State changeIndex: Int = 0;
  @State changeList: (Dimension | EdgeOutlineWidths | undefined)[] = [
    '10px' as Dimension, undefined, '20vp' as Dimension, '30fp' as Dimension, '40lpx' as Dimension, '20%' as Dimension,
    $r('app.float.outlineWidth') as Dimension, undefined, {
    left: -100,
    right: '20px',
    top: '30px',
    bottom: '40px'
  } as EdgeOutlineWidths, -1 as Dimension
  ]
  @State changeTypeIndex: Int = 0;
  @State changeTypeList: (ResponseType | undefined)[] = [
    ResponseType.LongPress, ResponseType.RightClick, undefined
  ]
  contextMenuOptions: ContextMenuOptions = {
    outlineWidth: this.changeList[this.changeIndex],
    outlineColor: Color.Blue

  } as ContextMenuOptions

  build() {
    Column({ space: 10 } as ColumnOptions) {
      Row({ space: 10 } as RowOptions) {
        Text(`10px`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindContextMenu(MyMenu, this.changeTypeList[this.changeTypeIndex], {
            outlineWidth: '10px',
            outlineColor: Color.Blue
          } as ContextMenuOptions)
        Text(`20vp`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindContextMenu(MyMenu, this.changeTypeList[this.changeTypeIndex], {
            outlineWidth: '20vp',
            outlineColor: Color.Blue
          } as ContextMenuOptions)
        Text(`30fp`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindContextMenu(MyMenu, this.changeTypeList[this.changeTypeIndex], {
            outlineWidth: '30fp',
            outlineColor: Color.Blue
          } as ContextMenuOptions)
      }

      Row({ space: 10 } as RowOptions) {
        Text(`40lpx`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindContextMenu(MyMenu, this.changeTypeList[this.changeTypeIndex], {
            outlineWidth: '40lpx',
            outlineColor: Color.Blue
          } as ContextMenuOptions)
        Text(`20%`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindContextMenu(MyMenu, this.changeTypeList[this.changeTypeIndex], {
            outlineWidth: '20%',
            outlineColor: Color.Blue
          } as ContextMenuOptions)
        Text(`resource-10vp`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindContextMenu(MyMenu, this.changeTypeList[this.changeTypeIndex], {
            outlineWidth: $r('app.float.outlineWidth'),
            outlineColor: Color.Blue
          } as ContextMenuOptions)
      }

      Row({ space: 10 } as RowOptions) {
        Text(`undefined`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindContextMenu(MyMenu, this.changeTypeList[this.changeTypeIndex], {
            outlineWidth: undefined,
            outlineColor: Color.Blue
          } as ContextMenuOptions)
        Text(`-1异常值`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindContextMenu(MyMenu, this.changeTypeList[this.changeTypeIndex], {
            outlineWidth: -1,
            outlineColor: Color.Blue
          } as ContextMenuOptions)
        Text(`EdgeOutlineWidths`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindContextMenu(MyMenu, this.changeTypeList[this.changeTypeIndex], {
            outlineWidth: {
              left: -100,
              right: '20px',
              top: '30px',
              bottom: '40px'
            },
            outlineColor: Color.Blue
          } as ContextMenuOptions)
      }

      Button('切换数值')
        .onClick(() => {
          this.changeIndex++
          if (this.changeIndex > this.changeList.length - 1) {
            this.changeIndex = 0
          }
        })
      Button('切换ResponseType')
        .onClick(() => {
          this.changeTypeIndex++
          if (this.changeTypeIndex > this.changeTypeList.length - 1) {
            this.changeTypeIndex = 0
          }
        })
      Row({ space: 10 } as RowOptions) {
        Text(`动态切换调用Menu`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindContextMenu(MyMenu, this.changeTypeList[this.changeTypeIndex], {
            outlineWidth: this.changeList[this.changeIndex],
            outlineColor: Color.Blue

          } as ContextMenuOptions)
      }

      Text('Index: ' + this.changeIndex + '数值: ' + this.changeList[this.changeIndex]).fontColor(Color.Red)
      Text('ResponseType: ' + this.changeTypeList[this.changeTypeIndex]).fontColor(Color.Red)
    }
    .width('100%')
    .height('100%')
  }
}
