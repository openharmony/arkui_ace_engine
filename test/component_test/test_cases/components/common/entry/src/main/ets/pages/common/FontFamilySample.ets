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

import fontFamilyTest from '../MyTest/FontFamilyTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'
import font from '@ohos.font';

@Entry
@Component
struct FontFamilySample {
  fontFamilyArr: string[] = ['Arial', 'font',]
  index: number = 0
  @State fontFamily: string = this.fontFamilyArr[this.index]

  aboutToAppear() {
    font.registerFont({
      familyName: 'font',
      familySrc: $rawfile('TESTFONT.TTF'),
    })
    loadComponentTestEntry(fontFamilyTest)
  }

  build() {
    Column() {
      Text("haha").fontFamily(this.fontFamily)
        .id('textFontFamily')
      Button('ButtonFontFamily').onClick(() => {
        this.index++
        this.fontFamily = this.fontFamilyArr[this.index % 2]
      })
    }
  }
}