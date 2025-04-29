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
import alphabetIndexerPopupItemFontTest from '../MyTest/AlphabetIndexerPopupItemFontTest';
import { loadComponentTestEntry } from '@ohos.arkui.componentTest';
import font from '@ohos.font';

@Entry
@Component
struct AlphabetIndexerPopupItemFontSample {
  private arrayA: string[] = ['甲', '乙']
  private arrayB: string[] = ['你', '我']
  @State popupItemFontType: Font = {
    size: 8,
    weight: 200,
    family: 'Arial',
    style: FontStyle.Normal
  }

  aboutToAppear() {
    loadComponentTestEntry(alphabetIndexerPopupItemFontTest);
    font.registerFont({
      familyName: 'TESTFONTRawFile',
      familySrc: $rawfile('TESTFONT.TTF')
    })
  }

  build() {
    Column() {
      AlphabetIndexer({ arrayValue: this.arrayA, selected: 0 })
        .popupItemFont(this.popupItemFontType)
        .onRequestPopupData((index: number) => {
          if (this.arrayA[index] == '甲') {
            return this.arrayB
          } else {
            return []
          }
        })
        .usingPopup(true)
        .margin({ left: 200 })
        .id('alphabetIndexerPopupItemFont1')
      AlphabetIndexer({ arrayValue: this.arrayA, selected: 0 })
        .popupItemFont({ size: $r('app.string.font_size'), weight: FontWeight.Lighter })
        .onRequestPopupData((index: number) => {
          if (this.arrayA[index] == '甲') {
            return this.arrayB
          } else {
            return []
          }
        })
        .usingPopup(true)
        .margin({ left: 200 })
        .id('alphabetIndexerPopupItemFont2')
      AlphabetIndexer({ arrayValue: this.arrayA, selected: 0 })
        .popupItemFont({ weight: FontWeight.Medium })
        .onRequestPopupData((index: number) => {
          if (this.arrayA[index] == '甲') {
            return this.arrayB
          } else {
            return []
          }
        })
        .margin({ left: 200 })
        .usingPopup(true)
        .id('alphabetIndexerPopupItemFont3')
      AlphabetIndexer({ arrayValue: this.arrayA, selected: 0 })
        .popupItemFont({ weight: FontWeight.Normal })
        .onRequestPopupData((index: number) => {
          if (this.arrayA[index] == '甲') {
            return this.arrayB
          } else {
            return []
          }
        })
        .margin({ left: 200 })
        .usingPopup(true)
        .id('alphabetIndexerPopupItemFont4')
      AlphabetIndexer({ arrayValue: this.arrayA, selected: 0 })
        .popupItemFont({ weight: FontWeight.Bolder })
        .onRequestPopupData((index: number) => {
          if (this.arrayA[index] == '甲') {
            return this.arrayB
          } else {
            return []
          }
        })
        .margin({ left: 200 })
        .usingPopup(true)
        .id('alphabetIndexerPopupItemFont5')
      AlphabetIndexer({ arrayValue: this.arrayA, selected: 0 })
        .popupItemFont({ weight: FontWeight.Regular })
        .onRequestPopupData((index: number) => {
          if (this.arrayA[index] == '甲') {
            return this.arrayB
          } else {
            return []
          }
        })
        .margin({ left: 200 })
        .usingPopup(true)
        .id('alphabetIndexerPopupItemFont6')
      Button('AlphabetIndexerPopupItemFont1')
        .onClick(() => {
          this.popupItemFontType = {
            size: '10px',
            weight: "200",
            family: 'TESTFONTRawFile',
            style: FontStyle.Italic
          }
        })
      Button('AlphabetIndexerPopupItemFont2')
        .onClick(() => {
          this.popupItemFontType = { weight: FontWeight.Bold }
        })
    }
  }
}