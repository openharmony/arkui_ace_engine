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
import searchTextFontTest from '../MyTest/SearchTextFontTest'
import font from '@ohos.font';

@Entry
@Component
struct SearchTextFontSample {
  @State textFontType: Font = {
    size: 12.0,
    weight: 600,
    family: 'Arial',
    style: FontStyle.Normal
  }
  @State textFontWeightType: FontWeight[] = [FontWeight.Normal, FontWeight.Regular, FontWeight.Medium, FontWeight.Bold,
    FontWeight.Bolder]
  @State index: number = 0
  controller: SearchController = new SearchController()

  aboutToAppear() {
    font.registerFont({
      familyName: 'TESTFONTRawFile',
      familySrc: $rawfile('TESTFONT.TTF')
    })
    loadComponentTestEntry(searchTextFontTest)
  }

  build() {
    Column() {
      Search({ controller: this.controller })
        .textFont(this.textFontType)
        .height(30)
        .id('searchTextFont1')
      Button("SearchTextFont1")
        .onClick(() => {
          this.textFontType = {
            size: '10px',
            weight: '100',
            family: 'TESTFONTRawFile',
            style: FontStyle.Italic
          }
        })
      Search({ controller: this.controller })
        .textFont({ size: $r('app.string.length'), weight: FontWeight.Lighter, family: 'Arial' })
        .height(30)
        .id('searchTextFont2')
      Search({ controller: this.controller })
        .textFont({ weight: this.textFontWeightType[this.index], family: 'Arial' })
        .height(30)
        .id('searchTextFont3')
      Button("SearchTextFont2")
        .onClick(() => {
          this.index++
          this.index %= 5
        })
    }
  }
}