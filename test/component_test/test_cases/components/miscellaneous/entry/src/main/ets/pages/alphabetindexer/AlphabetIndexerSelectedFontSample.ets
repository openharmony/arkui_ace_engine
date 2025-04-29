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
// 测试代码路径
import alphabetIndexerSelectedFontTest from '../MyTest/AlphabetIndexerSelectedFontTest';
import { loadComponentTestEntry } from '@ohos.arkui.componentTest';
import font from '@ohos.font';

@Entry
@Component
struct AlphabetIndexerSelectedFontSample {
  @State selectedFontType: Font = {
    size: 10,
    weight: 600,
    family: 'Arial',
    style: FontStyle.Normal
  }
  private arrayA: string[] = ['甲', '乙']

  aboutToAppear() {
    loadComponentTestEntry(alphabetIndexerSelectedFontTest);
    font.registerFont({
      familyName: 'TESTFONTRawFile',
      familySrc: $rawfile('TESTFONT.TTF')
    })
  }

  build() {
    Column() {
      AlphabetIndexer({ arrayValue: this.arrayA, selected: 0 })
        .selectedFont(this.selectedFontType)
        .id('alphabetIndexerSelectedFont1')
      AlphabetIndexer({ arrayValue: this.arrayA, selected: 0 })
        .selectedFont({ size: $r('app.string.font_size'), weight: FontWeight.Normal })
        .id('alphabetIndexerSelectedFont2')
      AlphabetIndexer({ arrayValue: this.arrayA, selected: 0 })
        .selectedFont({ weight: FontWeight.Lighter })
        .id('alphabetIndexerSelectedFont3')
      AlphabetIndexer({ arrayValue: this.arrayA, selected: 0 })
        .selectedFont({ weight: FontWeight.Medium })
        .id('alphabetIndexerSelectedFont4')
      AlphabetIndexer({ arrayValue: this.arrayA, selected: 0 })
        .selectedFont({ weight: FontWeight.Regular })
        .id('alphabetIndexerSelectedFont5')
      AlphabetIndexer({ arrayValue: this.arrayA, selected: 0 })
        .selectedFont({ weight: FontWeight.Bolder })
        .id('alphabetIndexerSelectedFont6')
      Button('AlphabetIndexerSelectedFont1')
        .onClick(() => {
          this.selectedFontType = {
            size: '10px',
            weight: "200",
            family: 'TESTFONTRawFile',
            style: FontStyle.Italic
          }
        })
      Button('AlphabetIndexerSelectedFont2')
        .onClick(() => {
          this.selectedFontType = { weight: FontWeight.Bold }
        })
    }
  }
}