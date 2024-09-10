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
import alphabetIndexerFontTest from '../MyTest/AlphabetIndexerFontTest';
import { loadComponentTestEntry } from '@ohos.arkui.componentTest';
import font from '@ohos.font';

@Entry
@Component
struct AlphabetIndexerFontSample {
  private arrayA: string[] = ['甲', '乙']
  @State fontType: Font = {
    size: 8,
    weight: 200,
    family: 'Arial',
    style: FontStyle.Normal
  }

  aboutToAppear() {
    loadComponentTestEntry(alphabetIndexerFontTest);
    font.registerFont({
      familyName: 'TESTFONTRawFile',
      familySrc: $rawfile('TESTFONT.TTF')
    })
  }

  build() {
    Column() {
      AlphabetIndexer({ arrayValue: this.arrayA, selected: 0 })
        .font(this.fontType)
        .id('alphabetIndexerFont1')
      AlphabetIndexer({ arrayValue: this.arrayA, selected: 0 })
        .font({ size: $r('app.string.font'), weight: FontWeight.Normal })
        .id('alphabetIndexerFont2')
      AlphabetIndexer({ arrayValue: this.arrayA, selected: 0 })
        .font({ weight: FontWeight.Lighter })
        .id('alphabetIndexerFont3')
      AlphabetIndexer({ arrayValue: this.arrayA, selected: 0 })
        .font({ weight: FontWeight.Medium })
        .id('alphabetIndexerFont4')
      AlphabetIndexer({ arrayValue: this.arrayA, selected: 0 })
        .font({ weight: FontWeight.Bold })
        .id('alphabetIndexerFont5')
      AlphabetIndexer({ arrayValue: this.arrayA, selected: 0 })
        .font({ weight: FontWeight.Regular })
        .id('alphabetIndexerFont6')
      AlphabetIndexer({ arrayValue: this.arrayA, selected: 0 })
        .font({ weight: FontWeight.Bolder })
        .id('alphabetIndexerFont7')
      Button('AlphabetIndexerFont1')
        .onClick(() => {
          this.fontType = {
            size: '10px',
            weight: "200",
            family: 'TESTFONTRawFile',
            style: FontStyle.Italic
          }
        })
    }
  }
}