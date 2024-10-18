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
import textInputPlaceholderFontTest from '../MyTest/TextInputPlaceholderFontTest'
import font from '@ohos.font';

@Entry
@Component
struct TextInputPlaceholderFontSample {
  @State text: string = ''
  @State placeholderFontType: Font = {
    size: '50px',
    weight: FontWeight.Lighter,
    family: 'Arial',
    style: FontStyle.Normal
  }
  @State placeholderFontWeightType: Font = { weight: 100 }
  controller: TextInputController = new TextInputController()

  aboutToAppear() {
    font.registerFont({
      familyName: 'TESTFONTRawFile',
      familySrc: $rawfile('TESTFONT.TTF')
    })
    loadComponentTestEntry(textInputPlaceholderFontTest)
  }

  build() {
    Column() {
      TextInput({ placeholder: 'Please input', text: this.text, controller: this.controller })
        .placeholderFont(this.placeholderFontType)
        .id("textInputPlaceholderFont1")
      Button('TextInputPlaceholderFont1')
        .onClick(() => {
          this.placeholderFontType = {
            size: 40,
            weight: FontWeight.Normal,
            family: 'TESTFONTRawFile',
            style: FontStyle.Italic
          }
        })
      TextInput({ placeholder: 'Please input', text: this.text, controller: this.controller })
        .placeholderFont({ size: $r('app.string.fp_length'), weight: FontWeight.Regular })
        .height(50)
        .id('textInputPlaceholderFont2')
      TextInput({ placeholder: 'Please input', text: this.text, controller: this.controller })
        .placeholderFont({ weight: FontWeight.Medium })
        .height(50)
        .id('textInputPlaceholderFont3')
      TextInput({ placeholder: 'Please input', text: this.text, controller: this.controller })
        .placeholderFont({ weight: FontWeight.Bold })
        .height(50)
        .id('textInputPlaceholderFont4')
      TextInput({ placeholder: 'Please input', text: this.text, controller: this.controller })
        .placeholderFont({ weight: FontWeight.Bolder })
        .height(50)
        .id('textInputPlaceholderFont5')
      TextInput({ placeholder: 'Please input', text: this.text, controller: this.controller })
        .placeholderFont(this.placeholderFontWeightType)
        .height(50)
        .id('textInputPlaceholderFont6')
      Button('TextInputPlaceholderFont2')
        .onClick(() => {
          this.placeholderFontWeightType = { weight: "900" }
        })
    }
  }
}