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
import alphabetIndexerPopupFontTest from '../MyTest/AlphabetIndexerPopupFontTest';
import { loadComponentTestEntry } from '@ohos.arkui.componentTest';
import font from '@ohos.font';

@Entry
@Component
struct AlphabetIndexerPopupFontSample {
  private arrayA: string[] = ['甲', '乙']
  @State popupFontType: Font = {
    size: 8,
    weight: 200,
    family: 'Arial',
    style: FontStyle.Normal
  }

  aboutToAppear() {
    loadComponentTestEntry(alphabetIndexerPopupFontTest);
    font.registerFont({
      familyName: 'TESTFONTRawFile',
      familySrc: $rawfile('TESTFONT.TTF')
    })
  }

  build() {
    Column() {
      AlphabetIndexer({ arrayValue: this.arrayA, selected: 0 })
        .popupFont(this.popupFontType)
        .margin({ left: 150 })
        .usingPopup(true)
        .id('alphabetIndexerPopupFont1')
      AlphabetIndexer({ arrayValue: this.arrayA, selected: 0 })
        .popupFont({ size: $r('app.string.font_size'), weight: FontWeight.Lighter })
        .margin({ left: 150 })
        .usingPopup(true)
        .id('alphabetIndexerPopupFont2')
      AlphabetIndexer({ arrayValue: this.arrayA, selected: 0 })
        .popupFont({ weight: FontWeight.Bold })
        .margin({ left: 150 })
        .usingPopup(true)
        .id('alphabetIndexerPopupFont3')
      AlphabetIndexer({ arrayValue: this.arrayA, selected: 0 })
        .popupFont({ weight: FontWeight.Bolder })
        .margin({ left: 150 })
        .usingPopup(true)
        .id('alphabetIndexerPopupFont4')
      AlphabetIndexer({ arrayValue: this.arrayA, selected: 0 })
        .popupFont({ weight: FontWeight.Regular })
        .margin({ left: 150 })
        .usingPopup(true)
        .alignStyle(IndexerAlign.Left)
        .id('alphabetIndexerPopupFont5')
      AlphabetIndexer({ arrayValue: this.arrayA, selected: 0 })
        .popupFont({ weight: FontWeight.Medium })
        .margin({ left: 150 })
        .usingPopup(true)
        .alignStyle(IndexerAlign.Left)
        .id('alphabetIndexerPopupFont6')
      AlphabetIndexer({ arrayValue: this.arrayA, selected: 0 })
        .popupFont({ weight: FontWeight.Normal })
        .margin({ left: 150 })
        .usingPopup(true)
        .alignStyle(IndexerAlign.Left)
        .id('alphabetIndexerPopupFont7')
      Button('AlphabetIndexerPopupFont1')
        .onClick(() => {
          this.popupFontType = {
            size: '10px',
            weight: "200",
            family: 'TESTFONTRawFile',
            style: FontStyle.Italic
          }
        })
    }
  }
}