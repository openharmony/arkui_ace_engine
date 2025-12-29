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
      startIcon: startIcon,
      content: '图标',
      builder: subMenuBuilder,
    } as MenuItemOptions)
    MenuItem({
      startIcon: startIcon,
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
  @State isShow0: boolean = false;
  @State isShow1: boolean = false;
  @State isShow2: boolean = false;
  @State isShow3: boolean = false;
  @State isShow4: boolean = false;
  @State isShow5: boolean = false;
  @State isShow6: boolean = false;
  @State isShow7: boolean = false;
  @State isShow8: boolean = false;
  @State isShow9: boolean = false;
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
          .bindContextMenu(this.isShow0, menuBuilder, {
            outlineWidth: '10px',
            outlineColor: Color.Blue
          } as ContextMenuOptions)
          .onClick(() => {
            this.isShow0 = !this.isShow0;
          })
        Text(`20vp`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindContextMenu(this.isShow1, menuBuilder, {
            outlineWidth: '20vp',
            outlineColor: Color.Blue
          } as ContextMenuOptions)
          .onClick(() => {
            this.isShow1 = !this.isShow1;
          })
        Text(`30fp`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindContextMenu(this.isShow2, menuBuilder, {
            outlineWidth: '30fp',
            outlineColor: Color.Blue
          } as ContextMenuOptions)
          .onClick(() => {
            this.isShow2 = !this.isShow2;
          })
      }

      Row({ space: 10 } as RowOptions) {
        Text(`40lpx`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindContextMenu(this.isShow3, menuBuilder, {
            outlineWidth: '40lpx',
            outlineColor: Color.Blue
          } as ContextMenuOptions)
          .onClick(() => {
            this.isShow3 = !this.isShow3;
          })
        Text(`20%`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindContextMenu(this.isShow4, menuBuilder, {
            outlineWidth: '20%',
            outlineColor: Color.Blue
          } as ContextMenuOptions)
          .onClick(() => {
            this.isShow4 = !this.isShow4;
          })
        Text(`resource-10vp`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindContextMenu(this.isShow5, menuBuilder, {
            outlineWidth: $r('app.float.outlineWidth'),
            outlineColor: Color.Blue
          } as ContextMenuOptions)
          .onClick(() => {
            this.isShow5 = !this.isShow5;
          })
      }

      Row({ space: 10 } as RowOptions) {
        Text(`undefined`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindContextMenu(this.isShow6, menuBuilder, {
            outlineWidth: undefined,
            outlineColor: Color.Blue
          } as ContextMenuOptions)
          .onClick(() => {
            this.isShow6 = !this.isShow6;
          })
        Text(`-1异常值`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindContextMenu(this.isShow7, menuBuilder, {
            outlineWidth: -1,
            outlineColor: Color.Blue
          } as ContextMenuOptions)
          .onClick(() => {
            this.isShow7 = !this.isShow7;
          })
        Text(`EdgeOutlineWidths`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindContextMenu(this.isShow8, menuBuilder, {
            outlineWidth: {
              left: -100,
              right: '20px',
              top: '30px',
              bottom: '40px'
            },
            outlineColor: Color.Blue
          } as ContextMenuOptions)
          .onClick(() => {
            this.isShow8 = !this.isShow8;
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
          .bindContextMenu(this.isShow9, menuBuilder, {
            outlineWidth: this.changeList[this.changeIndex],
            outlineColor: Color.Blue

          } as ContextMenuOptions)
          .onClick(() => {
            this.isShow9 = !this.isShow9;
          })
      }

      Text('Index: ' + this.changeIndex + '数值: ' + this.changeList[this.changeIndex]).fontColor(Color.Red)
    }
    .width('100%')
    .height('100%')
  }
}