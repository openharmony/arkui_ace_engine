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

import bindMenuTest from '../MyTest/BindMenuTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct BindMenuSample {
  @State enabledBoolean: boolean = true
  @State listData: number[] = [0, 0, 0]
  @State thisMessage: string = 'message'
  @State isShowBindMenu: boolean = false

  @Builder
  MenuBuilder() {
    Text('MenuBuilder')
  }

  aboutToAppear(): void {
    loadComponentTestEntry(bindMenuTest)
  }

  build() {
    Column() {
      Text('click for menu')
        .fontSize(20)
        .margin({ top: 20 })
        .bindMenu(this.MenuBuilder)

      Text(this.thisMessage)
        .id('bindMenuText1')

      SymbolGlyph($r('sys.symbol.ohos_lungs'))
        .id('symbolGlyphBindMenu1')
        .bindMenu(this.isShowBindMenu, [
          {
            value: 'Menu1',
            icon: $r('sys.symbol.ohos_lungs'),
            enabled: true,
            action: () => {
              this.thisMessage = "Menu1";
            }
          }
        ],
          {
            title: 'hello',
            showInSubWindow: false
          })
      SymbolGlyph($r('sys.symbol.ohos_lungs'))
        .id('symbolGlyphBindMenu2')
        .bindMenu(this.isShowBindMenu, [{
          value: 'Menu2',
          icon: $r('sys.symbol.ohos_lungs'),
          enabled: this.enabledBoolean,
          action: () => {
            this.thisMessage = "Menu2";
          }
        }])

      Button('ButtonBindMenu')
        .onClick(() => {
          this.isShowBindMenu = true
          this.enabledBoolean = false
        })
    }
    .height('100%')
    .width('100%')
    .backgroundColor('#f0f0f0')
  }
}