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

class Params {
  public dialogController: promptAction.DialogController = new promptAction.DialogController();

  constructor(dialogController: promptAction.DialogController) {
    this.dialogController = dialogController;
  }
}

@Builder
function dialogBuilder(params: Params) {
  Column() {
    Button('点我查询弹窗状态:通过外部传递的DialogController')
      .onClick(() => {
        console.info('openCustomDialogWithController state:', params.dialogController.getState())
      }).margin(20)
    Button('点我关闭弹窗2')
      .onClick(() => {
        console.info('openCustomDialogWithController state:', params.dialogController.getState())
        params.dialogController.close()
        console.info('openCustomDialogWithController state:', params.dialogController.getState())
      }).margin(20)
  }
}

@Entry
@Component
struct GetState {
  dialogController2: promptAction.DialogController = new promptAction.DialogController()
  baseDialogOptions: promptAction.BaseDialogOptions = {
    onWillAppear: () => {
      console.info('openCustomDialogWithController state onWillAppear:', this.dialogController2.getState())
    },
    onDidAppear: () => {
      console.info('openCustomDialogWithController state onDidAppear:', this.dialogController2.getState())
    },
    onWillDisappear: () => {
      console.info('openCustomDialogWithController state onWillDisappear:', this.dialogController2.getState())
    },
    onDidDisappear: () => {
      console.info('openCustomDialogWithController state onDidDisappear:', this.dialogController2.getState())
    },
  } as promptAction.BaseDialogOptions
  private uiContext: UIContext = this.getUIContext();
  private promptAction: PromptAction = this.uiContext.getPromptAction();
  private scroller: Scroller = new Scroller()

  build() {
    Column() {
      Button(`openCustomDialogWithController getState`)
        .onClick(() => {
          console.info('openCustomDialogWithController state:', this.dialogController2.getState())
        })
      Button(`openCustomDialogWithController`)
        .onClick(() => {
          try {
            let contentNode = new ComponentContent<Params>(this.uiContext, wrapBuilder(dialogBuilder),
              new Params(this.dialogController2));
            console.info('openCustomDialogWithController state:', this.dialogController2.getState())
            this.promptAction.openCustomDialogWithController(contentNode, this.dialogController2,
              this.baseDialogOptions)
              .then(() => {
                console.info('openCustomDialogWithController state:', this.dialogController2.getState())
              })
              .catch((err: Error) => {
                console.info('openCustomDialogWithController error：' + err.code + '+' + err.message);
              })
          } catch (error) {
            let message = (error as BusinessError).message;
            let code = (error as BusinessError).code;
            console.error(`openCustomDialogWithController error code is ${code}, message is ${message}`);
          }
          ;
        })
    }
  }
}