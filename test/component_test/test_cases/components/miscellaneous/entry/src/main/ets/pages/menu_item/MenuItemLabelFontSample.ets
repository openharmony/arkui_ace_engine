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
import font from '@ohos.font'
import menuItemLabelFontTest from '../MyTest/MenuItemLabelFontTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct MenuItemLabelFontSample {
  @State labelFont: Font = {
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
  }

  onPageShow(): void {
    loadComponentTestEntry(menuItemLabelFontTest)
  }

  build() {
    Column() {
      Menu() {
        MenuItem({ content: "复制", labelInfo: "Ctrl+C" })
          .labelFont(this.labelFont)
          .id('menuItemLabelFont1')
        MenuItem({ content: "复制", labelInfo: "Ctrl+C" })
          .labelFont({
            size: '30px',
            weight: '200',
            family: 'TESTFONTRawFile',
            style: FontStyle.Italic
          })
          .id('menuItemLabelFont2')
        MenuItem({ content: "复制", labelInfo: "Ctrl+C" })
          .labelFont({ weight: FontWeight.Lighter })
          .id('menuItemLabelFont3')
        MenuItem({ content: "复制", labelInfo: "Ctrl+C" })
          .labelFont({ weight: FontWeight.Normal })
          .id('menuItemLabelFont4')
        MenuItem({ content: "复制", labelInfo: "Ctrl+C" })
          .labelFont({ weight: FontWeight.Regular })
          .id('menuItemLabelFont5')
        MenuItem({ content: "复制", labelInfo: "Ctrl+C" })
          .labelFont({ weight: FontWeight.Medium })
          .id('menuItemLabelFont6')
      }

      Button('MenuItemLabelFont1').onClick(() => {
        this.labelFont = {
          size: $r('app.string.font_size'),
          weight: FontWeight.Bolder,
          family: 'Arial',
          style: FontStyle.Normal
        }
      })
      Button('MenuItemLabelFont2').onClick(() => {
        this.labelFont = { weight: FontWeight.Bold }
      })
    }
  }
}