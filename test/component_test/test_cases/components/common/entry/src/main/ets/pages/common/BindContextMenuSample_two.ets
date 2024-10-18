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

import bindContextMenuTest_two from '../MyTest/BindContextMenuTest_two'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct BindContextMenuSample_two {
  @State backgroundBlurStyleBindContextMenu: BlurStyle = BlurStyle.BACKGROUND_REGULAR
  @State placement: Placement = Placement.TopLeft

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
    loadComponentTestEntry(bindContextMenuTest_two)
  }

  build() {
    Column() {

      Row() {
        SymbolGlyph($r('sys.symbol.ohos_lungs'))
          .fontSize(96)
          .id('symbolGlyphBindContextMenu4')
          .bindContextMenu(this.MenuBuilder,
            ResponseType.LongPress,
            {
              placement: this.placement,
              backgroundBlurStyle: this.backgroundBlurStyleBindContextMenu
            })
      }

      Button('ButtonBindContextMenu1')
        .onClick(() => {
          this.placement = Placement.TopRight
          this.backgroundBlurStyleBindContextMenu = BlurStyle.BACKGROUND_THICK
        })

      Button('ButtonBindContextMenu2')
        .onClick(() => {
          this.placement = Placement.BottomLeft
          this.backgroundBlurStyleBindContextMenu = BlurStyle.NONE
        })

      Button('ButtonBindContextMenu3')
        .onClick(() => {
          this.placement = Placement.BottomRight
          this.backgroundBlurStyleBindContextMenu = BlurStyle.COMPONENT_ULTRA_THIN
        })

      Button('ButtonBindContextMenu4')
        .onClick(() => {
          this.placement = Placement.LeftTop
          this.backgroundBlurStyleBindContextMenu = BlurStyle.COMPONENT_THIN
        })

      Button('ButtonBindContextMenu5')
        .onClick(() => {
          this.placement = Placement.LeftBottom
          this.backgroundBlurStyleBindContextMenu = BlurStyle.COMPONENT_REGULAR
        })
    }
  }
}