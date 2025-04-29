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
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'
import searchFontColorTest from '../MyTest/SearchFontColorTest'

@Entry
@Component
struct SearchFontColorSample {
  controller: SearchController = new SearchController()
  @State fontColorType: ResourceColor = 0xffffff

  aboutToAppear(): void {
    loadComponentTestEntry(searchFontColorTest)
  }

  build() {
    Column() {
      Search({ controller: this.controller })
        .fontColor(Color.Yellow)
        .id('searchFontColor1')
      Search({ controller: this.controller })
        .fontColor(this.fontColorType)
        .id('searchFontColor2')
      Button('SearchFontColor1')
        .onClick(() => {
          this.fontColorType = 'rgb(255, 100, 255)'
        })
      Button('SearchFontColor2')
        .onClick(() => {
          this.fontColorType = $r('sys.color.ohos_id_color_text_hyperlink')
        })
    }
  }
}