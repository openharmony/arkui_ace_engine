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
import alphabetIndexerPopupSelectedColorTest from '../MyTest/AlphabetIndexerPopupSelectedColorTest';
import { loadComponentTestEntry } from '@ohos.arkui.componentTest';

@Entry
@Component
struct AlphabetIndexerPopupSelectedColorSample {
  private arrayA: string[] = ['甲', '乙', '丙']
  private arrayB: string[] = ['a', 'b', 'c', 'd']
  @State popupSelectedColorType: ResourceColor = 0xff0000

  aboutToAppear(): void {
    loadComponentTestEntry(alphabetIndexerPopupSelectedColorTest);
  }

  build() {
    Column() {
      AlphabetIndexer({ arrayValue: this.arrayA, selected: 0 })
        .onRequestPopupData((index: number) => {
          if (this.arrayA[index] == '甲') {
            return this.arrayB
          } else {
            return []
          }
        })
        .usingPopup(true)
        .margin({ left: 200 })
        .popupSelectedColor(Color.Red)
        .id('alphabetIndexerPopupSelectedColor1')
      AlphabetIndexer({ arrayValue: this.arrayA, selected: 0 })
        .onRequestPopupData((index: number) => {
          if (this.arrayA[index] == '甲') {
            return this.arrayB
          } else {
            return []
          }
        })
        .usingPopup(true)
        .margin({ left: 200 })
        .popupSelectedColor(this.popupSelectedColorType)
        .id('alphabetIndexerPopupSelectedColor2')
      Button('AlphabetIndexerPopupSelectedColor1')
        .onClick(() => {
          this.popupSelectedColorType = '#ffa500'
        })
      Button('AlphabetIndexerPopupSelectedColor2')
        .onClick(() => {
          this.popupSelectedColorType = $r('sys.color.ohos_id_color_text_hyperlink')
        })
    }
  }
}