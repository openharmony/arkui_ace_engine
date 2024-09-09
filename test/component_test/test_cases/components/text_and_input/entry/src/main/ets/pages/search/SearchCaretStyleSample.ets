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
import searchCaretStyleTest from '../MyTest/SearchCaretStyleTest'

@Entry
@Component
struct SearchCaretStyleSample {
  controller: SearchController = new SearchController()
  @State caretStyleType: CaretStyle = { width: '10px', color: Color.Pink }

  aboutToAppear(): void {
    loadComponentTestEntry(searchCaretStyleTest)
  }

  build() {
    Column() {
      Search({ controller: this.controller })
        .caretStyle(this.caretStyleType)
        .id('searchCaretStyle1')
      Button('SearchCaretStyle1')
        .onClick(() => {
          this.caretStyleType = { width: 50, color: $r('sys.color.ohos_id_color_text_hyperlink') }
        })
      Button('SearchCaretStyle2')
        .onClick(() => {
          this.caretStyleType = { width: $r('app.string.vp_length'), color: 0xffffff }
        })
      Search({ controller: this.controller })
        .caretStyle({ color: 'rgb(255, 100, 255)' })
        .id('searchCaretStyle2')
    }
  }
}