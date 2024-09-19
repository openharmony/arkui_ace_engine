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
import textInputFontFamilyTest from '../MyTest/TextInputFontFamilyTest'
import font from '@ohos.font';

@Entry
@Component
struct TextInputFontFamilySample {
  @State text: string = ''
  @State fontFamilyType: string = 'Arial'
  controller: TextInputController = new TextInputController()

  aboutToAppear() {
    font.registerFont({
      familyName: 'TESTFONTRawFile',
      familySrc: $rawfile('TESTFONT.TTF')
    })
    loadComponentTestEntry(textInputFontFamilyTest)
  }

  build() {
    Column() {
      TextInput({ text: this.text, controller: this.controller })
        .fontFamily(this.fontFamilyType)
        .margin({ bottom: 10 })
        .id('textInputFontFamily')
      Button('TextInputFontFamily')
        .onClick(() => {
          this.fontFamilyType = 'TESTFONTRawFile'
        })

    }
  }
}