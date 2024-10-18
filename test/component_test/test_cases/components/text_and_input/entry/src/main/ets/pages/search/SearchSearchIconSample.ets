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
import searchSearchIconTest from '../MyTest/SearchSearchIconTest'

@Entry
@Component
struct SearchSearchIconSample {
  controller: SearchController = new SearchController()
  @State searchIconType: IconOptions =
    { size: '10px', color: Color.Orange, src: "../../../resources/base/media/icon.png" }

  aboutToAppear(): void {
    loadComponentTestEntry(searchSearchIconTest)
  }

  build() {
    Column() {
      Search({ controller: this.controller })
        .searchIcon(this.searchIconType)
        .id('searchSearchIcon1')
      Button('SearchSearchIcon1')
        .onClick(() => {
          this.searchIconType = { size: 10, color: 0xffffff }
        })
      Button('SearchSearchIcon2')
        .onClick(() => {
          this.searchIconType = { size: $r('app.string.vp_length'), color: 'rgb(200,78,90)' }
        })
      Search({ controller: this.controller })
        .searchIcon({ color: $r('sys.color.ohos_id_color_text_hyperlink') })
        .id('searchSearchIcon2')
      Search({ controller: this.controller })
        .searchIcon({ src: $r('app.media.startIcon') })
        .id('searchSearchIcon3')
    }
  }
}