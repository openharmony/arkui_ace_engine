/*
* Copyright (c) 2024 Huawei Device Co., Ltd.
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

import bindContextMenuTest_one from '../MyTest/BindContextMenuTest_one'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct BindContextMenuSample_one {
  @State thisMessage: string = 'message'
  @State offsetPosition: string | Resource = '10px'
  @State placement: Placement = Placement.Right
  @State arrowOffset: string | Resource = '10px'
  @State backgroundColorBindContextMenu: Color | string | Resource = Color.Black
  @State backgroundBlurStyleBindContextMenu: BlurStyle = BlurStyle.Regular

  @Builder
  MenuBuilder() {
    Flex({ direction: FlexDirection.Column, justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center }) {
      Text('TestMenuItem1')
        .fontSize(20)
        .width(100)
        .height(50)
        .textAlign(TextAlign.Center)
      Divider().height(10)
      Text('Test menu item 2')
        .fontSize(20)
        .width(100)
        .height(50)
        .textAlign(TextAlign.Center)
    }.width(100)
  }

  aboutToAppear(): void {
    loadComponentTestEntry(bindContextMenuTest_one)
  }

  build() {
    Column() {
      Text(this.thisMessage).id('bindContextMenuText1')
      Text('LongPress for menu')
        .width('100%')
        .margin({ top: 5 })
        .id('textBindContextMenu1')
        .bindContextMenu(this.MenuBuilder, ResponseType.RightClick, {
          offset: { x: 1, y: 2 },
          placement: Placement.Left,
          arrowOffset: 100,
          preview: MenuPreviewMode.NONE,
          previewAnimationOptions: { scale: [0.95, 1.1] },
          enableArrow: true,
          onAppear: () => {
            this.thisMessage = "onAppear";
          },
          onDisappear: () => {
            this.thisMessage = "onDisappear";
          },
          aboutToAppear: () => {
            this.thisMessage = "aboutToAppear";
          },
          aboutToDisappear: () => {
            this.thisMessage = "aboutToDisappear";
          },
          backgroundColor: 0xffffff,
          backgroundBlurStyle: BlurStyle.Thin
        })

      Row() {
        SymbolGlyph($r('sys.symbol.ohos_lungs'))
          .id('symbolGlyphBindContextMenu2')
          .fontSize(96)
          .bindContextMenu(this.MenuBuilder,
            ResponseType.LongPress,
            {
              offset: { x: this.offsetPosition, y: this.offsetPosition },
              placement: this.placement,
              arrowOffset: this.arrowOffset,
              preview: MenuPreviewMode.NONE
            }
          )
        Button('ButtonBindContextMenu1')
          .onClick(() => {
            this.offsetPosition = $r("app.string.any_length")
            this.placement = Placement.Top
            this.arrowOffset = $r("app.string.any_length")
          })
      }

      Row() {
        SymbolGlyph($r('sys.symbol.ohos_lungs'))
          .id('symbolGlyphBindContextMenu3')
          .fontSize(96)
          .bindContextMenu(this.MenuBuilder,
            ResponseType.LongPress,
            {
              offset: { x: this.offsetPosition, y: this.offsetPosition },
              placement: this.placement,
              arrowOffset: this.arrowOffset,
              preview: MenuPreviewMode.NONE,
              backgroundColor: this.backgroundColorBindContextMenu,
              backgroundBlurStyle: this.backgroundBlurStyleBindContextMenu
            }
          )
      }

      Button('ButtonBindContextMenu2')
        .onClick(() => {
          this.backgroundColorBindContextMenu = $r('app.color.start_window_background')
          this.backgroundBlurStyleBindContextMenu = BlurStyle.Thick
        })
      Button('ButtonBindContextMenu3')
        .onClick(() => {
          this.placement = Placement.Bottom
          this.backgroundBlurStyleBindContextMenu = BlurStyle.BACKGROUND_THIN
        })
    }
  }
}