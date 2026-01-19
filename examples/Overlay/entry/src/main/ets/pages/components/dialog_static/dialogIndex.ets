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
struct dialogIndex {
  @State stateVar: string = 'state var';
  uiContext: UIContext | undefined = undefined;

  aboutToAppear(): void {
    this.uiContext = this.getUIContext();
  }

  build() {
    Column({ space: 10 } as ColumnOptions) {
      Text('测试dialog页面')
        .fontColor(0xFFFFFF)
        .fontWeight(FontWeight.Bold)
        .textAlign(TextAlign.Center)
        .width('80%')
        .backgroundColor(0x0000FF)
      Button('showActionMenu')
        .margin(10)
        .width('80%')
        .onClick((e: ClickEvent) => {
          this.getUIContext()
            .getRouter()
            .pushUrl({ url: 'pages/components/dialog_static/showActionMenu/showActionMenuIndex' });
        })
      Button('openCustomDialogWithController')
        .margin(10)
        .width('80%')
        .onClick((e: ClickEvent) => {
          this.getUIContext()
            .getRouter()
            .pushUrl({
              url: 'pages/components/dialog_static/openCustomDialogWithController/openCustomDialogWithControllerIndex'
            });
        })
      Button('presentCustomDialog')
        .margin(10)
        .width('80%')
        .onClick((e: ClickEvent) => {
          this.getUIContext()
            .getRouter()
            .pushUrl({ url: 'pages/components/dialog_static/presentCustomDialog/presentCustomDialogIndex' });
        })
      Button('customDialog')
        .margin(10)
        .width('80%')
        .onClick((e: ClickEvent) => {
          this.getUIContext()
            .getRouter()
            .pushUrl({ url: 'pages/components/dialog_static/customDialog/customDialogIndex' });
        })
    }
    .width('100%')
  }
}