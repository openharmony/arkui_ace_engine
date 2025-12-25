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
  @Builder
  MyPreview() {
    Column({ space: 10 } as ColumnOptions) {
      Image($r('app.media.startIcon'))
        .width(200)
        .height(200)
    }
  }

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
  @State isShow13: boolean = false;
  @State isShow14: boolean = false;
  @State isShow15: boolean = false;
  @State isShow16: boolean = false;
  @State isShow17: boolean = false;
  @State isShow18: boolean = false;
  @State isShow19: boolean = false;
  @State isShow20: boolean = false;
  @State isShow21: boolean = false;
  @State isShow22: boolean = false;
  @State isShow23: boolean = false;
  @State isShow24: boolean = false;
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
  contextMenuOptions: ContextMenuOptions = {
    mask: { color: this.changeList[this.changeIndex], backgroundBlurStyle: this.changeBlurList[this.changeBlurIndex] }

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
            mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.Thin }
          } as ContextMenuOptions)
          .onClick(() => {
            this.isShow0 = !this.isShow0;
          })
        Text(`rgba(23,169,141,0.5)`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindContextMenu(this.isShow1, MyMenu, {
            mask: { color: 'rgba(23,169,141,0.5)', backgroundBlurStyle: BlurStyle.Thin }
          } as ContextMenuOptions)
          .onClick(() => {
            this.isShow1 = !this.isShow1;
          })
        Text(`#FFFFFF00`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindContextMenu(this.isShow2, MyMenu, {
            mask: { color: '#FFFFFF00', backgroundBlurStyle: BlurStyle.Thin }
          } as ContextMenuOptions)
          .onClick(() => {
            this.isShow2 = !this.isShow2;
          })
      }

      Row({ space: 10 } as RowOptions) {
        Text(`12345`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindContextMenu(this.isShow3, MyMenu, {
            mask: { color: 12345, backgroundBlurStyle: BlurStyle.Thin }
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
            mask: { color: undefined, backgroundBlurStyle: BlurStyle.Thin }
          } as ContextMenuOptions)
          .onClick(() => {
            this.isShow4 = !this.isShow4;
          })
        Text(`app.color.blue`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindContextMenu(this.isShow5, MyMenu, {
            mask: { color: $r('app.color.blue'), backgroundBlurStyle: BlurStyle.Thin }
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
          .bindContextMenu(this.isShow21, MyMenu, {
            mask: { color: $r('app.string.errorColor'), backgroundBlurStyle: BlurStyle.Thin }
          } as ContextMenuOptions)
          .onClick(() => {
            this.isShow21 = !this.isShow21;
          })
        Text(`预览默认显示蒙层`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindContextMenu(this.isShow22, MyMenu, {
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
          } as ContextMenuOptions)
          .onClick(() => {
            this.isShow22 = !this.isShow22;
          })
      }

      Row({ space: 10 } as RowOptions) {
        Text(`BlurStyle.Thin`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindContextMenu(this.isShow6, MyMenu, {
            mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.Thin }
          } as ContextMenuOptions)
          .onClick(() => {
            this.isShow6 = !this.isShow6;
          })
        Text(`BlurStyle.Regular`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindContextMenu(this.isShow7, MyMenu, {
            mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.Regular }
          } as ContextMenuOptions)
          .onClick(() => {
            this.isShow7 = !this.isShow7;
          })
        Text(`BlurStyle.Thick`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindContextMenu(this.isShow8, MyMenu, {
            mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.Thick }
          } as ContextMenuOptions)
          .onClick(() => {
            this.isShow8 = !this.isShow8;
          })
      }

      Row({ space: 10 } as RowOptions) {
        Text(`BlurStyle.BACKGROUND_THIN`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindContextMenu(this.isShow9, MyMenu, {
            mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.BACKGROUND_THIN }
          } as ContextMenuOptions)
          .onClick(() => {
            this.isShow9 = !this.isShow9;
          })
        Text(`BlurStyle.BACKGROUND_REGULAR`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindContextMenu(this.isShow10, MyMenu, {
            mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.BACKGROUND_REGULAR }
          } as ContextMenuOptions)
          .onClick(() => {
            this.isShow10 = !this.isShow10;
          })
        Text(`BlurStyle.BACKGROUND_THICK`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindContextMenu(this.isShow11, MyMenu, {
            mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.BACKGROUND_THICK }
          } as ContextMenuOptions)
          .onClick(() => {
            this.isShow11 = !this.isShow11;
          })
      }

      Row({ space: 10 } as RowOptions) {
        Text(`BlurStyle.BACKGROUND_ULTRA_THICK`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindContextMenu(this.isShow12, MyMenu, {
            mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.BACKGROUND_ULTRA_THICK }
          } as ContextMenuOptions)
          .onClick(() => {
            this.isShow12 = !this.isShow12;
          })
        Text(`BlurStyle.NONE`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindContextMenu(this.isShow13, MyMenu, {
            mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.NONE }
          } as ContextMenuOptions)
          .onClick(() => {
            this.isShow13 = !this.isShow13;
          })
        Text(`BlurStyle.COMPONENT_ULTRA_THIN`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindContextMenu(this.isShow14, MyMenu, {
            mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.COMPONENT_ULTRA_THIN }
          } as ContextMenuOptions)
          .onClick(() => {
            this.isShow14 = !this.isShow14;
          })
      }

      Row({ space: 10 } as RowOptions) {
        Text(`BlurStyle.COMPONENT_THIN`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindContextMenu(this.isShow15, MyMenu, {
            mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.COMPONENT_THIN }
          } as ContextMenuOptions)
          .onClick(() => {
            this.isShow15 = !this.isShow15;
          })
        Text(`BlurStyle.COMPONENT_REGULAR`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindContextMenu(this.isShow16, MyMenu, {
            mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.COMPONENT_REGULAR }
          } as ContextMenuOptions)
          .onClick(() => {
            this.isShow16 = !this.isShow16;
          })
        Text(`BlurStyle.COMPONENT_THICK`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindContextMenu(this.isShow17, MyMenu, {
            mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.COMPONENT_THICK }
          } as ContextMenuOptions)
          .onClick(() => {
            this.isShow17 = !this.isShow17;
          })
      }

      Row({ space: 10 } as RowOptions) {
        Text(`BlurStyle.COMPONENT_ULTRA_THICK`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindContextMenu(this.isShow18, MyMenu, {
            mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.COMPONENT_ULTRA_THICK }
          } as ContextMenuOptions)
          .onClick(() => {
            this.isShow18 = !this.isShow18;
          })
        Text(`undefined`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindContextMenu(this.isShow19, MyMenu, {
            mask: { color: Color.Red, backgroundBlurStyle: undefined }
          } as ContextMenuOptions)
          .onClick(() => {
            this.isShow19 = !this.isShow19;
          })
      }

      Row({ space: 10 } as RowOptions) {
        Text(`true`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindContextMenu(this.isShow23, MyMenu, {
            mask: true
          } as ContextMenuOptions)
          .onClick(() => {
            this.isShow23 = !this.isShow23;
          })
        Text(`false`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindContextMenu(this.isShow24, MyMenu, {
            mask: false
          } as ContextMenuOptions)
          .onClick(() => {
            this.isShow24 = !this.isShow24;
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
          .bindContextMenu(this.isShow20, MyMenu, {
            mask: {
              color: this.changeList[this.changeIndex],
              backgroundBlurStyle: this.changeBlurList[this.changeBlurIndex]
            }

          } as ContextMenuOptions)
          .onClick(() => {
            this.isShow20 = !this.isShow20;
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
