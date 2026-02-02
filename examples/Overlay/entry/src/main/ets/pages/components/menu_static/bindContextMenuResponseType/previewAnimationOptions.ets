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
  @Builder
  MyPreview() {
    Column() {
      Image($r('app.media.startIcon'))
        .width(200)
        .height(200)
    }
  }

  @State changeScaleIndex: Int = 0;
  @State changeScaleList: (AnimationNumberRange | undefined)[] = [
    undefined, [0.8, 1.0] as AnimationNumberRange, [-0.8, -1.0] as AnimationNumberRange,
    [0.0, 0.0] as AnimationNumberRange
  ]
  @State changeTransitionIndex: Int = 0;
  @State changeTransitionList: (TransitionEffect | undefined)[] = [
    undefined,
    TransitionEffect.OPACITY.animation({ duration: 4000, curve: Curve.Ease }).combine(
      TransitionEffect.rotate({ z: 1, angle: 180 })),
    TransitionEffect.OPACITY.animation({ duration: -4000, curve: Curve.Ease }).combine(
      TransitionEffect.rotate({ z: -1, angle: -180 })),
    TransitionEffect.OPACITY.animation({ duration: 0, curve: Curve.Ease }).combine(
      TransitionEffect.rotate({ z: 0, angle: 0 })),
    TransitionEffect.OPACITY.animation({ duration: undefined, curve: undefined }).combine(
      TransitionEffect.rotate({ z: 0, angle: 0 })),
    TransitionEffect.IDENTITY
  ]
  @State changeHoverScaleIndex: Int = 0;
  @State changeHoverScaleList: (AnimationNumberRange | undefined)[] = [
    undefined,
    [1.0, 0.95] as AnimationNumberRange,
    [-1.0, -0.95] as AnimationNumberRange,
    [0.0, 0.0] as AnimationNumberRange
  ]
  @State changeInterruptionIndex: Int = 0;
  @State changeInterruptionList: (boolean | undefined)[] = [
    undefined, true, false
  ]
  @State changeTypeIndex: Int = 0;
  @State changeTypeList: (ResponseType | undefined)[] = [
    ResponseType.LongPress, ResponseType.RightClick, undefined
  ]
  contextMenuOptions: ContextMenuOptions = {
    preview: this.MyPreview,
    previewBorderRadius: 50,
    previewAnimationOptions: {
      scale: this.changeScaleList[this.changeScaleIndex],
      transition: this.changeTransitionList[this.changeTransitionIndex],
      hoverScale: this.changeHoverScaleList[this.changeHoverScaleIndex],
      hoverScaleInterruption: this.changeInterruptionList[this.changeInterruptionIndex],
    },
    previewScaleMode: PreviewScaleMode.AUTO
  } as ContextMenuOptions

  build() {
    Column({ space: 10 } as ColumnOptions) {
      Row({ space: 10 } as RowOptions) {
        Text(`不设置hoverScale无效`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindContextMenu(menuBuilder, this.changeTypeList[this.changeTypeIndex], {
            preview: this.MyPreview,
            previewAnimationOptions: {
              hoverScaleInterruption: true,
            },
            previewScaleMode: PreviewScaleMode.AUTO
          } as ContextMenuOptions)
        Text(`设置transition无效`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindContextMenu(menuBuilder, this.changeTypeList[this.changeTypeIndex], {
            preview: this.MyPreview,
            previewAnimationOptions: {
              hoverScale: [0.5, 2.0],
              transition: TransitionEffect.OPACITY.animation({ duration: 4000, curve: Curve.Ease }).combine(
                TransitionEffect.rotate({ z: 1, angle: 180 })),
              hoverScaleInterruption: true,
            },
            previewScaleMode: PreviewScaleMode.AUTO
          } as ContextMenuOptions)
      }

      Row({ space: 10 } as RowOptions) {
        Text(`undefined`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindContextMenu(menuBuilder, this.changeTypeList[this.changeTypeIndex], {
            preview: this.MyPreview,
            previewAnimationOptions: {
              hoverScale: [0.5, 2.0],
              hoverScaleInterruption: undefined,
            },
            previewScaleMode: PreviewScaleMode.AUTO
          } as ContextMenuOptions)
        Text(`true`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindContextMenu(menuBuilder, this.changeTypeList[this.changeTypeIndex], {
            preview: this.MyPreview,
            previewAnimationOptions: {
              hoverScale: [0.5, 2.0],
              hoverScaleInterruption: true,
            },
            previewScaleMode: PreviewScaleMode.AUTO
          } as ContextMenuOptions)
        Text(`false`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindContextMenu(menuBuilder, this.changeTypeList[this.changeTypeIndex], {
            preview: this.MyPreview,
            previewAnimationOptions: {
              hoverScale: [0.5, 2.0],
              hoverScaleInterruption: false,
            },
            previewScaleMode: PreviewScaleMode.AUTO
          } as ContextMenuOptions)
      }

      Row({ space: 10 } as RowOptions) {
        Button('切换ResponseType')
          .onClick(() => {
            this.changeTypeIndex++
            if (this.changeTypeIndex > this.changeTypeList.length - 1) {
              this.changeTypeIndex = 0
            }
          })
      }

      Row({ space: 10 } as RowOptions) {
        Button('切换Interruption')
          .onClick(() => {
            this.changeInterruptionIndex++
            if (this.changeInterruptionIndex > this.changeInterruptionList.length - 1) {
              this.changeInterruptionIndex = 0
            }
          })
      }

      Row({ space: 10 } as RowOptions) {
        Text(`动态切换调用Menu`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindContextMenu(menuBuilder, this.changeTypeList[this.changeTypeIndex], {
            preview: this.MyPreview,
            previewAnimationOptions: {
              hoverScale: this.changeHoverScaleList[this.changeHoverScaleIndex],
              hoverScaleInterruption: this.changeInterruptionList[this.changeInterruptionIndex],
            },
            previewScaleMode: PreviewScaleMode.AUTO
          } as ContextMenuOptions)
      }

      Text('HoverScale: ' + this.changeHoverScaleIndex + '数值: ' +
      this.changeHoverScaleList[this.changeHoverScaleIndex]).fontColor(Color.Red)
      Text('Interruption: ' + this.changeInterruptionIndex + '数值: ' +
      this.changeInterruptionList[this.changeInterruptionIndex]).fontColor(Color.Red)
      Text('ResponseType: ' + this.changeTypeList[this.changeTypeIndex]).fontColor(Color.Red)
    }
    .width('100%')
    .height('100%')
  }
}