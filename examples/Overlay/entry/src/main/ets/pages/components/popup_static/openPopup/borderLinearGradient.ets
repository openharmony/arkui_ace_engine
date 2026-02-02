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

@Builder
function popupBuilder() {
  Scroll(new Scroller()) {
    Column({ space: 5 } as ColumnOptions) {
      Text('This is a popup with PopupOptionsThis is a popup with PopupOptionsThis is a popup with PopupOptions' +
        'This is a popup with PopupOptionsThis is a popup with PopupOptionsThis is a popup with PopupOptions,')
    }
  }
}

@Entry
@Component
struct OpenPopupBorderLinearGradient {
  private uiContext: UIContext = this.getUIContext();
  private promptAction: PromptAction = this.uiContext.getPromptAction();
  private contentNode: ComponentContent = new ComponentContent(this.uiContext, wrapBuilder(popupBuilder));
  @State outlineLinearGradientIndex: Int = 0;
  @State outlineLinearGradientList: (PopupBorderLinearGradient | undefined)[] = [
    {
      direction: GradientDirection.LeftBottom,
      colors: [[Color.Yellow, 0.0], [Color.Green, 0.5], [Color.Blue, 1.0]]
    } as PopupBorderLinearGradient,
    undefined,
    { direction: GradientDirection.Left, colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]] } as PopupBorderLinearGradient,
  ]
  @State outlineLinearGradientIndex1: Int = 0;
  @State outlineLinearGradientList1: (PopupBorderLinearGradient | undefined)[] = [
    {
      direction: GradientDirection.LeftBottom, colors: [[Color.Yellow, 0.0], [Color.Green, 0.5], [Color.Blue, 1.0]]
    } as PopupBorderLinearGradient,
    undefined,
    { direction: GradientDirection.Left, colors: [[Color.Pink, 0.0], [Color.Blue, 1.0]] } as PopupBorderLinearGradient,
  ]

  build() {
    Column({ space: 5 } as ColumnOptions) {
      Text(`enableArrow设置为true:`)
        .fontSize(16)
        .width('100%')
      Button('设置LeftBottom,Yellow,Green,Blue')
        .id('1')
        .onClick(() => {
          try {
            this.promptAction.openPopup(this.contentNode, { id: '1' } as TargetInfo, {
              placement: Placement.Bottom,
              enableArrow: true,
              borderWidth: '10vp',
              borderLinearGradient: {
                direction: GradientDirection.LeftBottom,
                colors: [[Color.Yellow, 0.0], [Color.Green, 0.5], [Color.Blue, 1.0]]
              },
            } as PopupCommonOptions).then(() => {
              console.info('---1130---openPopup success');
            })
              .catch((err: Error) => {
                console.info('---1130---openPopup error：' + err.code + '+' + err.message);
              })
          } catch (error) {
            let message = (error as BusinessError).message;
            let code = (error as BusinessError).code;
            console.error(`---1130---openPopup error code is ${code}, message is ${message}`);
          }
          ;
        })
      Button('不设置borderLinearGradient')
        .id('2')
        .onClick(() => {
          try {
            this.promptAction.openPopup(this.contentNode, { id: '2' } as TargetInfo, {
              placement: Placement.Bottom,
              enableArrow: true,
              borderWidth: '10vp',
            } as PopupCommonOptions).then(() => {
              console.info('---1130---openPopup success');
            })
              .catch((err: Error) => {
                console.info('---1130---openPopup error：' + err.code + '+' + err.message);
              })
          } catch (error) {
            let message = (error as BusinessError).message;
            let code = (error as BusinessError).code;
            console.error(`---1130---openPopup error code is ${code}, message is ${message}`);
          }
          ;
        })
      Button('undefined')
        .id('3')
        .onClick(() => {
          try {
            this.promptAction.openPopup(this.contentNode, { id: '3' } as TargetInfo, {
              placement: Placement.Bottom,
              enableArrow: true,
              borderWidth: '10vp',
              borderLinearGradient: undefined,
            } as PopupCommonOptions)
              .then(() => {
                console.info('---1130---openPopup success');
              })
              .catch((err: Error) => {
                console.info('---1130---openPopup error：' + err.code + '+' + err.message);
              })
          } catch (error) {
            let message = (error as BusinessError).message;
            let code = (error as BusinessError).code;
            console.error(`---1130---openPopup error code is ${code}, message is ${message}`);
          }
          ;
        })
      Text(`enableArrow设置为false:`)
        .fontSize(16)
        .width('100%')
      Button('设置LeftBottom,Yellow,Green,Blue')
        .id('5')
        .onClick(() => {
          try {
            this.promptAction.openPopup(this.contentNode, { id: '5' } as TargetInfo, {
              placement: Placement.Bottom,
              enableArrow: false,
              borderWidth: '10vp',
              borderLinearGradient: {
                direction: GradientDirection.LeftBottom,
                colors: [[Color.Yellow, 0.0], [Color.Green, 0.5], [Color.Blue, 1.0]]
              },
            } as PopupCommonOptions).then(() => {
              console.info('---1130---openPopup success');
            })
              .catch((err: Error) => {
                console.info('---1130---openPopup error：' + err.code + '+' + err.message);
              })
          } catch (error) {
            let message = (error as BusinessError).message;
            let code = (error as BusinessError).code;
            console.error(`---1130---openPopup error code is ${code}, message is ${message}`);
          }
          ;
        })
      Button('不设置borderLinearGradient')
        .id('6')
        .onClick(() => {
          try {
            this.promptAction.openPopup(this.contentNode, { id: '6' } as TargetInfo, {
              placement: Placement.Bottom,
              enableArrow: false,
              borderWidth: '10vp',
            } as PopupCommonOptions).then(() => {
              console.info('---1130---openPopup success');
            })
              .catch((err: Error) => {
                console.info('---1130---openPopup error：' + err.code + '+' + err.message);
              })
          } catch (error) {
            let message = (error as BusinessError).message;
            let code = (error as BusinessError).code;
            console.error(`---1130---openPopup error code is ${code}, message is ${message}`);
          }
          ;
        })
      Button('undefined')
        .id('7')
        .onClick(() => {
          try {
            this.promptAction.openPopup(this.contentNode, { id: '7' } as TargetInfo, {
              placement: Placement.Bottom,
              enableArrow: false,
              borderWidth: '10vp',
              borderLinearGradient: undefined,
            } as PopupCommonOptions).then(() => {
              console.info('---1130---openPopup success');
            })
              .catch((err: Error) => {
                console.info('---1130---openPopup error：' + err.code + '+' + err.message);
              })
          } catch (error) {
            let message = (error as BusinessError).message;
            let code = (error as BusinessError).code;
            console.error(`---1130---openPopup error code is ${code}, message is ${message}`);
          }
          ;
        })
    }.margin(20)
  }
}