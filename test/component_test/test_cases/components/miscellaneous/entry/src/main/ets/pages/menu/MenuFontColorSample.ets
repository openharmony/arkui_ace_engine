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
//测试代码路径
import menuFontColorTest from '../MyTest/MenuFontColorTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct MenuFontColorSample {
  @State fontColorType: ResourceColor = 0xf00fff

  aboutToAppear(): void {
    loadComponentTestEntry(menuFontColorTest)
  }

  build() {
    Column() {
      Menu() {
        MenuItem({ content: "fontColor", labelInfo: "Color" })
      }.fontColor(Color.Blue).id('menuFontColor1')

      Menu() {
        MenuItem({ content: "fontColor", labelInfo: "number" })
      }.fontColor(this.fontColorType).id('menuFontColor2')

      Button('MenuFontColor1')
        .onClick(() => {
          this.fontColorType = "#ffc0cb"
        })
      Button('MenuFontColor2')
        .onClick(() => {
          this.fontColorType = $r('sys.color.ohos_id_color_badge_red')
        })
    }
  }
}