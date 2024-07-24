/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 // * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
// 测试代码路径
import menuItemContentFontColorTest from '../MyTest/MenuItemContentFontColorTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct MenuItemContentFontColorSample {
  @State contentFontColor: ResourceColor = Color.Red

  aboutToAppear(): void {
    loadComponentTestEntry(menuItemContentFontColorTest)
  }

  build() {
    Column() {
      Menu() {
        MenuItem({ content: "菜单选项", })
          .contentFontColor(this.contentFontColor)
          .id('menuItemContentFontColor1')
        MenuItem({ content: "菜单选项" })
          .contentFontColor('#ffff79f2')
          .id('menuItemContentFontColor2')
      }

      Button('MenuItemContentFontColor1').onClick(() => {
        this.contentFontColor = $r('sys.color.ohos_fa_connected')
      })
      Button('MenuItemContentFontColor2').onClick(() => {
        this.contentFontColor = 0xfff000
      })
    }
  }
}