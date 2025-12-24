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

@Entry
@Component
struct PresentGetState {
  @Builder
  customDialogComponentWithId(dialogId: int) {
    Column() {
      Button('点我查询弹窗状态:通过DialogController')
        .onClick(() => {
          console.info('presentCustomDialog state:', this.dialogController3.getState())
        }).margin(20)
      Button('点我关闭弹窗1')
        .onClick(() => {
          console.info('presentCustomDialog state:', this.dialogController3.getState())
          this.promptAction.closeCustomDialog(dialogId);
          console.info('presentCustomDialog state:', this.dialogController3.getState())
        }).margin(20)
      Button('点我关闭弹窗2')
        .onClick(() => {
          console.info('presentCustomDialog state:', this.dialogController3.getState())
          this.dialogController3.close()
          console.info('presentCustomDialog state:', this.dialogController3.getState())
        }).margin(20)
    }
  }

  dialogController3: promptAction.DialogController = new promptAction.DialogController()
  dialogOptions: promptAction.DialogOptions = {
    onWillAppear: () => {
      console.info('presentCustomDialog state onWillAppear:', this.dialogController3.getState())
    },
    onDidAppear: () => {
      console.info('presentCustomDialog state onDidAppear:', this.dialogController3.getState())
    },
    onWillDisappear: () => {
      console.info('presentCustomDialog state onWillDisappear:', this.dialogController3.getState())
    },
    onDidDisappear: () => {
      console.info('presentCustomDialog state onDidDisappear:', this.dialogController3.getState())
    },
  } as promptAction.DialogOptions
  private uiContext: UIContext = this.getUIContext();
  private promptAction: PromptAction = this.uiContext.getPromptAction();
  private scroller: Scroller = new Scroller()

  build() {
    Column() {
      Button(`presentCustomDialog getState`)
        .onClick(() => {
          console.info('presentCustomDialog state:', this.dialogController3.getState())
        })
      Button(`presentCustomDialog`)
        .onClick(() => {
          try {
            console.info('presentCustomDialog state:', this.dialogController3.getState())
            this.promptAction.presentCustomDialog(this.customDialogComponentWithId as CustomBuilderT<int>,
              this.dialogController3, this.dialogOptions)
              .then(() => {
                console.info('presentCustomDialog state:', this.dialogController3.getState())
                console.info('presentCustomDialog  success');
              })
              .catch((err: Error) => {
                console.info('presentCustomDialog  error：' + err.code + '+' + err.message);
              })
          } catch (error) {
            let message = (error as BusinessError).message;
            let code = (error as BusinessError).code;
            console.error(`presentCustomDialog error code is ${code}, message is ${message}`);
          }
          ;
        })
    }
  }
}