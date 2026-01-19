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

@Entry
@Component
struct CustomDialogUser {
  @State dialogController: CustomDialogController | null = new CustomDialogController({
    builder: CustomDialogExample({}),
    autoCancel: false,
  })

  build() {
    Column() {
      Button('click me')
        .onClick(() => {
          if (this.dialogController != null) {
            this.dialogController!.open()
          }
        }).backgroundColor(0x317aff)
      Button('点我查询弹窗状态')
        .onClick(() => {
          console.info('customDialog state:' + this.dialogController?.getState())
        }).margin(20)
    }.width('100%').margin(5)
  }
}

@CustomDialog
struct CustomDialogExample {
  controller?: CustomDialogController

  build() {
    Column() {
      Button('点我查询弹窗状态:通过自定义组件自带controller')
        .onClick(() => {
          if (this.getDialogController() != undefined) {
            console.info('customDialog state:' + this.getDialogController()?.getState())
          } else {
            console.info('customDialog state: no exist')
          }
        }).margin(20)
      Button('点我查询弹窗状态:通过CustomDialogController ')
        .onClick((e: ClickEvent) => {
          console.info('customDialog state:' + this.controller?.getState())
        }
        ).margin(20)
      Button('点我关闭弹窗')
        .onClick(() => {
          if (this.getDialogController() != undefined) {
            this.getDialogController()!.close()
            console.info('customDialog state:' + this.getDialogController()?.getState())
          }
        }).margin(20)

    }
  }
}