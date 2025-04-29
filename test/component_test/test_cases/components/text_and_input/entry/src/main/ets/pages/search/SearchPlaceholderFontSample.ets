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
import font from '@ohos.font';
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'
import searchPlaceholderFontTest from '../MyTest/SearchPlaceholderFontTest'

@Entry
@Component
struct SearchPlaceholderFontSample {
  @State placeholderFontType: Font = {
    size: '50px',
    weight: FontWeight.Lighter,
    family: 'Arial',
    style: FontStyle.Normal
  }
  @State placeholderFontWeightType: FontWeight | number[] =
    [100, FontWeight.Regular, FontWeight.Medium, FontWeight.Bold, FontWeight.Bolder]
  @State index: number = 0
  controller: SearchController = new SearchController()

  aboutToAppear() {
    font.registerFont({
      familyName: 'TESTFONTRawFile',
      familySrc: $rawfile('TESTFONT.TTF')
    })
    loadComponentTestEntry(searchPlaceholderFontTest)
  }

  build() {
    Column() {
      Search({ placeholder: 'Please input', controller: this.controller })
        .placeholderFont(this.placeholderFontType)
        .id('searchPlaceholderFont1')
      Button('SearchPlaceholderFont1')
        .onClick(() => {
          this.placeholderFontType = {
            size: 40,
            weight: FontWeight.Normal,
            family: 'TESTFONTRawFile',
            style: FontStyle.Italic
          }
        })
        .height(30)
      Search({ placeholder: 'Please input', controller: this.controller })
        .placeholderFont({ size: $r('app.string.length'), weight: "900" })
        .id('searchPlaceholderFont2')
      Search({ placeholder: 'Please input', controller: this.controller })
        .placeholderFont({ weight: this.placeholderFontWeightType[this.index] })
        .height(50)
        .id('searchPlaceholderFont3')
      Button('SearchPlaceholderFont2')
        .onClick(() => {
          this.index++
          this.index %= 5
        })
    }
  }
}