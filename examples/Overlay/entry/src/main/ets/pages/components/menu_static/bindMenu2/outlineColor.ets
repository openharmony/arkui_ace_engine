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


@Entry
@Component
struct Index {
  @State changeIndex: Int = 0;
  @State changeList: (ResourceColor | EdgeColors | undefined)[] = [
    'rgba(23,169,141,0.5)' as ResourceColor, Color.Red as ResourceColor, '#FFFFFF00' as ResourceColor,
    12345 as ResourceColor, $r('app.color.blue') as ResourceColor, $r('app.string.errorColor') as ResourceColor,
    undefined, {
    left: Color.Red,
    right: '#FFFFFF00',
    top: 12345,
    bottom: $r('app.string.errorColor')
  } as EdgeColors,
  ]
  menuOptions: MenuOptions = {
    title: '' + this.changeList[this.changeIndex],
    outlineWidth: '10px',
    outlineColor: this.changeList[this.changeIndex]

  } as MenuOptions

  build() {
    Column({ space: 10 } as ColumnOptions) {
      Row({ space: 10 } as RowOptions) {
        Text(`Color.Red`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindMenu([{
            value: 'Menu1', action: () => {
              console.info('handle Menu1 select');
            }
          } as MenuElement, {
            value: 'Menu2', action: () => {
              console.info('handle Menu2 select');
            }
          } as MenuElement], {
            title: 'Color.Red',
            outlineWidth: '10px',
            outlineColor: Color.Red

          } as MenuOptions)
        Text(`'#FFFFFF00'`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindMenu([{
            value: 'Menu1', action: () => {
              console.info('handle Menu1 select');
            }
          } as MenuElement, {
            value: 'Menu2', action: () => {
              console.info('handle Menu2 select');
            }
          } as MenuElement], {
            title: '#FFFFFF00',
            outlineWidth: '10px',
            outlineColor: '#FFFFFF00'

          } as MenuOptions)
        Text(`12345`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindMenu([{
            value: 'Menu1', action: () => {
              console.info('handle Menu1 select');
            }
          } as MenuElement, {
            value: 'Menu2', action: () => {
              console.info('handle Menu2 select');
            }
          } as MenuElement], {
            title: '12345',
            outlineWidth: '10px',
            outlineColor: 12345

          } as MenuOptions)
      }

      Row({ space: 10 } as RowOptions) {
        Text(`app.color.blue`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindMenu([{
            value: 'Menu1', action: () => {
              console.info('handle Menu1 select');
            }
          } as MenuElement, {
            value: 'Menu2', action: () => {
              console.info('handle Menu2 select');
            }
          } as MenuElement], {
            title: 'app.color.blue',
            outlineWidth: '10px',
            outlineColor: $r('app.color.blue')

          } as MenuOptions)
        Text(`undefined`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindMenu([{
            value: 'Menu1', action: () => {
              console.info('handle Menu1 select');
            }
          } as MenuElement, {
            value: 'Menu2', action: () => {
              console.info('handle Menu2 select');
            }
          } as MenuElement], {
            title: 'undefined',
            outlineWidth: '10px',
            outlineColor: undefined

          } as MenuOptions)
        Text(`EdgeColors`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindMenu([{
            value: 'Menu1', action: () => {
              console.info('handle Menu1 select');
            }
          } as MenuElement, {
            value: 'Menu2', action: () => {
              console.info('handle Menu2 select');
            }
          } as MenuElement], {
            title: 'EdgeColors',
            outlineWidth: '10px',
            outlineColor: {
              left: Color.Red,
              right: '#FFFFFF00',
              top: 12345,
              bottom: $r('app.string.errorColor')
            }

          } as MenuOptions)
      }

      Row({ space: 10 } as RowOptions) {
        Text(`异常`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindMenu([{
            value: 'Menu1', action: () => {
              console.info('handle Menu1 select');
            }
          } as MenuElement, {
            value: 'Menu2', action: () => {
              console.info('handle Menu2 select');
            }
          } as MenuElement], {
            title: '异常',
            outlineWidth: '10px',
            outlineColor: $r('app.string.errorColor')

          } as MenuOptions)
        Text(`rgba(23,169,141,0.5)`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindMenu([{
            value: 'Menu1', action: () => {
              console.info('handle Menu1 select');
            }
          } as MenuElement, {
            value: 'Menu2', action: () => {
              console.info('handle Menu2 select');
            }
          } as MenuElement], {
            title: 'rgba(23,169,141,0.5)',
            outlineWidth: '10px',
            outlineColor: 'rgba(23,169,141,0.5)'

          } as MenuOptions)
      }

      Button('切换数值')
        .onClick(() => {
          this.changeIndex++
          if (this.changeIndex > this.changeList.length - 1) {
            this.changeIndex = 0
          }
        })
      Row({ space: 10 } as RowOptions) {
        Text(`动态切换调用Menu`)
          .fontSize(10)
          .backgroundColor(0x0000ff)
          .fontColor(0xffffff)
          .padding(5)
          .bindMenu([{
            value: 'Menu1', action: () => {
              console.info('handle Menu1 select');
            }
          } as MenuElement, {
            value: 'Menu2', action: () => {
              console.info('handle Menu2 select');
            }
          } as MenuElement], {
            title: '' + this.changeList[this.changeIndex],
            outlineWidth: '10px',
            outlineColor: this.changeList[this.changeIndex]

          } as MenuOptions)
      }

      Text('Index: ' + this.changeIndex + '数值: ' + this.changeList[this.changeIndex]).fontColor(Color.Red)
    }
    .width('100%')
    .height('100%')
  }
}
