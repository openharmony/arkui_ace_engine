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
  @State isShow10: boolean = false;
  @State isShow11: boolean = false;
  @State isShow12: boolean = false;
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
        .padding(5)
        .bindMenu(this.isShow0, [{
          value: 'Menu1', action: () => {
            console.info('handle Menu1 select');
          }
        } as MenuElement, {
          value: 'Menu2', action: () => {
            console.info('handle Menu2 select');
          }
        } as MenuElement], {
          title: 'X:10px;Y:10px',
          anchorPosition: { x: '10px', y: '10px' }
        })
        .onClick(() => {
          this.isShow0 = !this.isShow0
        })
      Text(`X:20vp;Y:20vp`)
        .fontSize(10)
        .backgroundColor(0x0000ff)
        .fontColor(0xffffff)
        .padding(5)
        .bindMenu(this.isShow1, [{
          value: 'Menu1', action: () => {
            console.info('handle Menu1 select');
          }
        } as MenuElement, {
          value: 'Menu2', action: () => {
            console.info('handle Menu2 select');
          }
        } as MenuElement], {
          title: 'X:20vp;Y:20vp',
          anchorPosition: { x: '20vp', y: '20vp' }
        })
        .onClick(() => {
          this.isShow1 = !this.isShow1
        })
      Text(`X:30fp;Y:30fp`)
        .fontSize(10)
        .backgroundColor(0x0000ff)
        .fontColor(0xffffff)
        .padding(5)
        .bindMenu(this.isShow2, [{
          value: 'Menu1', action: () => {
            console.info('handle Menu1 select');
          }
        } as MenuElement, {
          value: 'Menu2', action: () => {
            console.info('handle Menu2 select');
          }
        } as MenuElement], {
          title: 'X:30fp;Y:30fp',
          anchorPosition: { x: '30fp', y: '30fp' }
        })
        .onClick(() => {
          this.isShow2 = !this.isShow2
        })
      Text(`X:40lpx;Y:40lpx`)
        .fontSize(10)
        .backgroundColor(0x0000ff)
        .fontColor(0xffffff)
        .padding(5)
        .bindMenu(this.isShow3, [{
          value: 'Menu1', action: () => {
            console.info('handle Menu1 select');
          }
        } as MenuElement, {
          value: 'Menu2', action: () => {
            console.info('handle Menu2 select');
          }
        } as MenuElement], {
          title: 'X:40lpx;Y:40lpx',
          anchorPosition: { x: '40lpx', y: '40lpx' }
        })
        .onClick(() => {
          this.isShow3 = !this.isShow3
        })
      Text(`X:20%;Y:20%`)
        .fontSize(10)
        .backgroundColor(0x0000ff)
        .fontColor(0xffffff)
        .padding(5)
        .bindMenu(this.isShow4, [{
          value: 'Menu1', action: () => {
            console.info('handle Menu1 select');
          }
        } as MenuElement, {
          value: 'Menu2', action: () => {
            console.info('handle Menu2 select');
          }
        } as MenuElement], {
          title: 'X:20%;Y:20%%',
          anchorPosition: { x: '20%', y: '20%' }
        })
        .onClick(() => {
          this.isShow4 = !this.isShow4
        })
      Text(`X:30;Y:30`)
        .fontSize(10)
        .backgroundColor(0x0000ff)
        .fontColor(0xffffff)
        .padding(5)
        .bindMenu(this.isShow5, [{
          value: 'Menu1', action: () => {
            console.info('handle Menu1 select');
          }
        } as MenuElement, {
          value: 'Menu2', action: () => {
            console.info('handle Menu2 select');
          }
        } as MenuElement], {
          title: 'X:30;Y:30',
          anchorPosition: { x: 30, y: 30 }
        })
        .onClick(() => {
          this.isShow5 = !this.isShow5
        })
      Text(`Resource-10vp`)
        .fontSize(10)
        .backgroundColor(0x0000ff)
        .fontColor(0xffffff)
        .padding(5)
        .bindMenu(this.isShow6, [{
          value: 'Menu1', action: () => {
            console.info('handle Menu1 select');
          }
        } as MenuElement, {
          value: 'Menu2', action: () => {
            console.info('handle Menu2 select');
          }
        } as MenuElement], {
          title: 'EdgeOutlineWidths',
          anchorPosition: { x: $r('app.float.outlineWidth'), y: $r('app.float.outlineWidth') }
        })
        .onClick(() => {
          this.isShow6 = !this.isShow6
        })
      Text(`undefined`)
        .fontSize(10)
        .backgroundColor(0x0000ff)
        .fontColor(0xffffff)
        .padding(5)
        .bindMenu(this.isShow7, [{
          value: 'Menu1', action: () => {
            console.info('handle Menu1 select');
          }
        } as MenuElement, {
          value: 'Menu2', action: () => {
            console.info('handle Menu2 select');
          }
        } as MenuElement], {
          title: 'undefined',
          anchorPosition: { x: undefined, y: undefined }
        })
        .onClick(() => {
          this.isShow7 = !this.isShow7
        })
      Text(`异常`)
        .fontSize(10)
        .backgroundColor(0x0000ff)
        .fontColor(0xffffff)
        .padding(5)
        .bindMenu(this.isShow8, [{
          value: 'Menu1', action: () => {
            console.info('handle Menu1 select');
          }
        } as MenuElement, {
          value: 'Menu2', action: () => {
            console.info('handle Menu2 select');
          }
        } as MenuElement], {
          title: '-1',
          anchorPosition: { x: -1, y: -1 }
        })
        .onClick(() => {
          this.isShow8 = !this.isShow8
        })
      Text(`预览状态`)
        .fontSize(10)
        .backgroundColor(0x0000ff)
        .fontColor(0xffffff)
        .padding(5)
        .bindMenu(this.isShow9, [{
          value: 'Menu1', action: () => {
            console.info('handle Menu1 select');
          }
        } as MenuElement, {
          value: 'Menu2', action: () => {
            console.info('handle Menu2 select');
          }
        } as MenuElement], {
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
        })
        .onClick(() => {
          this.isShow9 = !this.isShow9
        })
      Text(`与offset叠加覆盖组件`)
        .fontSize(10)
        .backgroundColor(0x0000ff)
        .fontColor(0xffffff)
        .padding(5)
        .bindMenu(this.isShow10, [{
          value: 'Menu1', action: () => {
            console.info('handle Menu1 select');
          }
        } as MenuElement, {
          value: 'Menu2', action: () => {
            console.info('handle Menu2 select');
          }
        } as MenuElement], {
          title: '与offset叠加覆盖组件',
          offset: { x: 100, y: 0 },
          anchorPosition: { x: 100, y: 0 }
        })
        .onClick(() => {
          this.isShow10 = !this.isShow10
        })
      Text(`placement预设优先显示不生效`)
        .fontSize(10)
        .backgroundColor(0x0000ff)
        .fontColor(0xffffff)
        .padding(5)
        .bindMenu(this.isShow11, [{
          value: 'Menu1', action: () => {
            console.info('handle Menu1 select');
          }
        } as MenuElement, {
          value: 'Menu2', action: () => {
            console.info('handle Menu2 select');
          }
        } as MenuElement], {
          title: 'placement预设优先显示不生效',
          placement: Placement.Left,
          anchorPosition: { x: 100, y: 100 }
        })
        .onClick(() => {
          this.isShow11 = !this.isShow11
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
        .bindMenu(this.isShow12, [{
          value: 'Menu1', action: () => {
            console.info('handle Menu1 select');
          }
        } as MenuElement, {
          value: 'Menu2', action: () => {
            console.info('handle Menu2 select');
          }
        } as MenuElement], {
          title: 'X: ' + this.changeXList[this.changeXIndex] + 'Y: ' + this.changeYList[this.changeYIndex],
          anchorPosition: { x: this.changeXList[this.changeXIndex], y: this.changeYList[this.changeYIndex] }
        } as MenuOptions)
        .onClick(() => {
          this.isShow12 = !this.isShow12
        })
      Text('XIndex: ' + this.changeXIndex + '数值: ' + this.changeXList[this.changeXIndex]).fontColor(Color.Red)
      Text('YIndex: ' + this.changeYIndex + '数值: ' + this.changeYList[this.changeYIndex]).fontColor(Color.Red)
    }
    .width('100%')
    .height('100%')
  }
}