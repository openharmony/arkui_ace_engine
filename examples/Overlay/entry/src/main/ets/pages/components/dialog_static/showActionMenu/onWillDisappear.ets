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
struct showActionMenuOnWillAppear {
  promptAction: PromptAction = this.getUIContext().getPromptAction();

  build() {
    Column() {
      Button('showActionMenu1')
        .margin(10)
        .onClick(() => {
          this.promptAction.showActionMenu({
            title: 'showActionMenu1 Title Info',
            buttons: [
              {
                text: 'button1',
                color: '#000000',
                primary: true,
              } as promptAction.Button,
            ] as [promptAction.Button],
            onWillDisappear: () => {
              console.info("showActionMenu1,is onWillDisappear!");
            },
          } as promptAction.ActionMenuOptions)
            .then((data: promptAction.ActionMenuSuccessResponse | null): void => {
              if (data) {
                console.info('showActionMenu1 success, click button: ' + data.index);
              }
            })
            .catch((err: Error) => {
              console.error('showActionMenu1 error: ' + err);
            })
        })
      Button('showActionMenu2')
        .margin(10)
        .onClick(() => {
          try {
            this.promptAction.showActionMenu({
              title: 'Title Info',
              buttons: [
                {
                  text: 'button1',
                  color: '#000000',
                  primary: true,
                } as promptAction.Button,
              ] as [promptAction.Button],
              onWillDisappear: () => {
                console.info("showActionMenu2,is onWillDisappear!");
              },
            } as promptAction.ActionMenuOptions,
              (err: BusinessError<void> | null, data: promptAction.ActionMenuSuccessResponse | undefined): void => {
                if (err) {
                  console.error('showActionMenu2 err: ' + err);
                  return;
                }
                if (data) {
                  console.info('showActionMenu2 success callback, click button: ' + data.index);
                }
              });
          } catch (error) {
            let message = (error as BusinessError).message;
            let code = (error as BusinessError).code;
            console.error(`showActionMenu2 args error code is ${code}, message is ${message}`);
          }
          ;
        })
    }.height('100%').width('100%').justifyContent(FlexAlign.Center)
  }
}