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
import textAreaPlaceholderFontTest from '../MyTest/TextAreaPlaceholderFontTest'
import font from '@ohos.font';

@Entry
@Component
struct TextAreaPlaceholderFontSample {
  @State placeholderFontType: Font = {
    size: '50px',
    weight: FontWeight.Lighter,
    family: 'Arial',
    style: FontStyle.Normal
  }
  @State placeholderFontWeightType: Font = { weight: 100 }

  aboutToAppear() {
    font.registerFont({
      familyName: 'TESTFONTRawFile',
      familySrc: $rawfile('TESTFONT.TTF')
    })
    loadComponentTestEntry(textAreaPlaceholderFontTest)
  }

  build() {
    Column() {
      TextArea({ placeholder: 'text area' })
        .placeholderFont(this.placeholderFontType)
        .id('textAreaPlaceholderFont1')
      Button('TextAreaPlaceholderFont1')
        .onClick(() => {
          this.placeholderFontType = {
            size: 40,
            weight: FontWeight.Normal,
            family: 'TESTFONTRawFile',
            style: FontStyle.Italic
          }
        })
      TextArea({ placeholder: 'text area' })
        .placeholderFont({ size: $r('app.string.length'), weight: FontWeight.Regular })
        .id('textAreaPlaceholderFont2')
      TextArea({ placeholder: 'text area' })
        .placeholderFont({ weight: FontWeight.Medium })
        .id('textAreaPlaceholderFont3')
      TextArea({ placeholder: 'text area' })
        .placeholderFont({ weight: FontWeight.Bold })
        .id('textAreaPlaceholderFont4')
      TextArea({ placeholder: 'text area' })
        .placeholderFont({ weight: FontWeight.Bolder })
        .id('textAreaPlaceholderFont5')
      TextArea({ placeholder: 'text area' })
        .placeholderFont(this.placeholderFontWeightType)
        .height(50)
        .id('textAreaPlaceholderFont6')
      Button('TextAreaPlaceholderFont2')
        .onClick(() => {
          this.placeholderFontWeightType = { weight: 900 }
        })
    }
  }
}