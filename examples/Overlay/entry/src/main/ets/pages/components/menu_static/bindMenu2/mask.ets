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
  menuOptions: MenuOptions = {
    title: '' + this.changeList[this.changeIndex] + '---' + this.changeBlurList[this.changeBlurIndex],
    mask: { color: this.changeList[this.changeIndex], backgroundBlurStyle: this.changeBlurList[this.changeBlurIndex] }

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
            mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.Thin }

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
            mask: { color: 'rgba(23,169,141,0.5)', backgroundBlurStyle: BlurStyle.Thin }

          } as MenuOptions)
        Text(`#FFFFFF00`)
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
            mask: { color: '#FFFFFF00', backgroundBlurStyle: BlurStyle.Thin }

          } as MenuOptions)
      }

      Row({ space: 10 } as RowOptions) {
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
            mask: { color: 12345, backgroundBlurStyle: BlurStyle.Thin }

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
            mask: { color: undefined, backgroundBlurStyle: BlurStyle.Thin }

          } as MenuOptions)
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
            mask: { color: $r('app.color.blue'), backgroundBlurStyle: BlurStyle.Thin }

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
            mask: { color: $r('app.string.errorColor'), backgroundBlurStyle: BlurStyle.Thin }

          } as MenuOptions)
        Text(`预览默认显示蒙层`)
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
            title: '预览默认显示蒙层',
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

          } as MenuOptions)
      }

      Row({ space: 10 } as RowOptions) {
        Text(`BlurStyle.Thin`)
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
            title: 'BlurStyle.Thin',
            mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.Thin }
          } as MenuOptions)
        Text(`BlurStyle.Regular`)
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
            title: 'BlurStyle.Regular',
            mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.Regular }
          } as MenuOptions)
        Text(`BlurStyle.Thick`)
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
            title: 'BlurStyle.Thick',
            mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.Thick }
          } as MenuOptions)
      }

      Row({ space: 10 } as RowOptions) {
        Text(`BlurStyle.BACKGROUND_THIN`)
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
            title: 'BlurStyle.BACKGROUND_THIN',
            mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.BACKGROUND_THIN }
          } as MenuOptions)
        Text(`BlurStyle.BACKGROUND_REGULAR`)
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
            title: 'BlurStyle.BACKGROUND_REGULAR',
            mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.BACKGROUND_REGULAR }
          } as MenuOptions)
        Text(`BlurStyle.BACKGROUND_THICK`)
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
            title: 'BlurStyle.BACKGROUND_THICK',
            mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.BACKGROUND_THICK }
          } as MenuOptions)
      }

      Row({ space: 10 } as RowOptions) {
        Text(`BlurStyle.BACKGROUND_ULTRA_THICK`)
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
            title: 'BlurStyle.BACKGROUND_ULTRA_THICK',
            mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.BACKGROUND_ULTRA_THICK }
          } as MenuOptions)
        Text(`BlurStyle.NONE`)
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
            title: 'BlurStyle.NONE',
            mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.NONE }
          } as MenuOptions)
        Text(`BlurStyle.COMPONENT_ULTRA_THIN`)
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
            title: 'BlurStyle.COMPONENT_ULTRA_THIN',
            mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.COMPONENT_ULTRA_THIN }
          } as MenuOptions)
      }

      Row({ space: 10 } as RowOptions) {
        Text(`BlurStyle.COMPONENT_THIN`)
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
            title: 'BlurStyle.COMPONENT_THIN',
            mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.COMPONENT_THIN }
          } as MenuOptions)
        Text(`BlurStyle.COMPONENT_REGULAR`)
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
            title: 'BlurStyle.COMPONENT_REGULAR',
            mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.COMPONENT_REGULAR }
          } as MenuOptions)
        Text(`BlurStyle.COMPONENT_THICK`)
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
            title: 'BlurStyle.COMPONENT_THICK',
            mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.COMPONENT_THICK }
          } as MenuOptions)
      }

      Row({ space: 10 } as RowOptions) {
        Text(`BlurStyle.COMPONENT_ULTRA_THICK`)
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
            title: 'BlurStyle.COMPONENT_ULTRA_THICK',
            mask: { color: Color.Red, backgroundBlurStyle: BlurStyle.COMPONENT_ULTRA_THICK }
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
            mask: { color: Color.Red, backgroundBlurStyle: undefined }
          } as MenuOptions)
      }

      Row({ space: 10 } as RowOptions) {
        Text(`true`)
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
            title: 'true',
            mask: true
          } as MenuOptions)
        Text(`false`)
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
            title: 'false',
            mask: false
          } as MenuOptions)
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
          .bindMenu([{
            value: 'Menu1', action: () => {
              console.info('handle Menu1 select');
            }
          } as MenuElement, {
            value: 'Menu2', action: () => {
              console.info('handle Menu2 select');
            }
          } as MenuElement], {
            title: '' + this.changeList[this.changeIndex] + '---' + this.changeBlurList[this.changeBlurIndex],
            mask: {
              color: this.changeList[this.changeIndex],
              backgroundBlurStyle: this.changeBlurList[this.changeBlurIndex]
            }

          } as MenuOptions)
      }

      Text('Index: ' + this.changeIndex + '数值: ' + this.changeList[this.changeIndex]).fontColor(Color.Red)
      Text('Index: ' + this.changeBlurIndex + '数值: ' + this.changeBlurList[this.changeBlurIndex])
        .fontColor(Color.Green)
    }
    .width('100%')
    .height('100%')
  }
}