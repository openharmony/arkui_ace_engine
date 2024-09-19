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
import searchSearchButtonTest from '../MyTest/SearchSearchButtonTest'

@Entry
@Component
struct SearchSearchButtonSample {
  @State value: string = 'SEARCH'
  @State searchButtonOptionsType: SearchButtonOptions = { fontColor: Color.Red, fontSize: '10px' }
  controller: SearchController = new SearchController()

  aboutToAppear(): void {
    loadComponentTestEntry(searchSearchButtonTest)
  }

  build() {
    Column() {
      Search({ controller: this.controller })
        .searchButton(this.value, this.searchButtonOptionsType)
        .id('searchSearchButton1')
      Button('SearchSearchButton1')
        .onClick(() => {
          this.searchButtonOptionsType = { fontColor: 0xffffff, fontSize: 50 }
        })
      Button('SearchSearchButton2')
        .onClick(() => {
          this.searchButtonOptionsType = { fontColor: 'rgba(100, 50, 255, 0.5)', fontSize: $r('app.string.fp_length') }
        })
      Search({ controller: this.controller })
        .searchButton('搜索', { fontColor: $r('sys.color.ohos_id_color_text_hyperlink') })
        .id('searchSearchButton2')
      Search({ controller: this.controller })
        .searchButton('')
        .id('searchSearchButton3')
    }
  }
}