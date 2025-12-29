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
  public text: string = '';
  public dialogController: promptAction.DialogController = new promptAction.DialogController();

  constructor(text: string, dialogController: promptAction.DialogController) {
    this.text = text;
    this.dialogController = dialogController;
  }
}

@Builder
function buildText(params: Params) {
  Column() {
    Text(params.text)
      .fontSize(50)
      .fontWeight(FontWeight.Bold)
      .margin({ bottom: 36 } as Margin)
    Button('点我关闭弹窗')
      .onClick(() => {
        if (params.dialogController != undefined) {
          params.dialogController!.close();
          console.info('openCustomDialogWithController state:' + params.dialogController.getState()); // 打印弹窗状态
        }
      })
    Button('点我获取状态')
      .onClick(() => {
        console.info('openCustomDialogWithController state:' + params.dialogController.getState()); // 打印弹窗状态
      })
  }.backgroundColor('#FFF0F0F0')
}

@Entry
@Component
struct openCustomDialogWithControllerIndex {
  @State message: string = 'hello';
  private dialogController: promptAction.DialogController = new promptAction.DialogController();

  build() {
    Row() {
      Column() {
        Button('click me')
          .onClick(() => {
            let uiContext = this.getUIContext();
            let promptAction = uiContext.getPromptAction();
            let contentNode = new ComponentContent<Params>(uiContext, wrapBuilder(buildText),
              new Params(this.message, this.dialogController)
            );
            promptAction.openCustomDialogWithController(contentNode, this.dialogController, {
              transition: TransitionEffect.OPACITY.animation({
                duration: 3000
              }) as TransitionEffect
            })
              .then(() => {
                console.info('succeeded');
              })

          })
        Button('点我查询弹窗状态')
          .onClick(() => {
            console.info('openCustomDialogWithController state:' + this.dialogController?.getState())
          }).margin(20)
      }
      .width('100%')
      .height('100%')
    }
    .height('100%')
  }
}