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
import alphabetIndexerAlignStyleTest from '../MyTest/AlphabetIndexerAlignStyleTest';
import { loadComponentTestEntry } from '@ohos.arkui.componentTest';

@Entry
@Component
struct AlphabetIndexerAlignStyleSample {
  private arrayA: string[] = ['甲', '乙', '丙', '丁', '戊']
  @State alignStyleType: IndexerAlign = IndexerAlign.Right
  @State lengthType: Length = 100

  aboutToAppear(): void {
    loadComponentTestEntry(alphabetIndexerAlignStyleTest);
  }

  build() {
    Column() {
      AlphabetIndexer({ arrayValue: this.arrayA, selected: 0 })
        .alignStyle(this.alignStyleType, this.lengthType)
        .usingPopup(true)
        .margin({ left: 200 })
        .id('alphabetIndexerAlignStyle1')
      AlphabetIndexer({ arrayValue: this.arrayA, selected: 0 })
        .alignStyle(IndexerAlign.Left, $r('app.string.length'))
        .usingPopup(true)
        .id('alphabetIndexerAlignStyle2')
      AlphabetIndexer({ arrayValue: this.arrayA, selected: 0 })
        .alignStyle(IndexerAlign.Left)
        .usingPopup(true)
        .id('alphabetIndexerAlignStyle3')
      AlphabetIndexer({ arrayValue: this.arrayA, selected: 0 })
        .alignStyle(IndexerAlign.Left, 10)
        .popupPosition({ x: 100, y: 48 })
        .usingPopup(true)
        .id('alphabetIndexerAlignStyle4')
      AlphabetIndexer({ arrayValue: this.arrayA, selected: 0 })
        .alignStyle(IndexerAlign.Left, -1)
        .popupPosition({ x: 100, y: 48 })
        .usingPopup(true)
        .id('alphabetIndexerAlignStyle5')
      Button('AlphabetIndexerAlignStyle')
        .onClick(() => {
          this.alignStyleType = IndexerAlign.Left
          this.lengthType = '100px'
        })
    }
  }
}