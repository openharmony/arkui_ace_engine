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
// 测试代码路径
import font from '@ohos.font';
import menuItemContentFontTest from '../MyTest/MenuItemContentFontTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct MenuItemContentFont {
  @State contentFont: Font = {
    size: 20,
    weight: 500,
    family: 'Arial',
    style: FontStyle.Normal
  }

  aboutToAppear() {
    font.registerFont({
      familyName: 'TESTFONTRawFile',
      familySrc: $rawfile('TESTFONT.TTF')
    })
    loadComponentTestEntry(menuItemContentFontTest)
  }

  build() {
    Column() {
      Menu() {
        MenuItem({ content: "菜单选项" })
          .contentFont(this.contentFont)
          .id('menuItemContentFont1')
        MenuItem({ content: "菜单选项" })
          .contentFont({
            size: '30px',
            weight: '200',
            family: 'TESTFONTRawFile',
            style: FontStyle.Italic
          })
          .id('menuItemContentFont2')
        MenuItem({ content: "菜单选项" })
          .contentFont({ weight: FontWeight.Lighter })
          .id('menuItemContentFont3')
        MenuItem({ content: "菜单选项" })
          .contentFont({ weight: FontWeight.Normal })
          .id('menuItemContentFont4')
        MenuItem({ content: "菜单选项" })
          .contentFont({ weight: FontWeight.Regular })
          .id('menuItemContentFont5')
        MenuItem({ content: "菜单选项" })
          .contentFont({ weight: FontWeight.Medium })
          .id('menuItemContentFont6')
      }

      Button('MenuItemContentFont1').onClick(() => {
        this.contentFont = {
          size: $r('app.string.font_size'),
          weight: FontWeight.Bolder,
          family: 'Arial',
          style: FontStyle.Normal
        }
      })
      Button('MenuItemContentFont2').onClick(() => {
        this.contentFont = { weight: FontWeight.Bold }
      })
    }
  }
}