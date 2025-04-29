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
import alphabetIndexerPopupItemBackgroundColorTest from '../MyTest/AlphabetIndexerPopupItemBackgroundColorTest';
import { loadComponentTestEntry } from '@ohos.arkui.componentTest';

@Entry
@Component
struct AlphabetIndexerPopupItemBackgroundColorSample {
  private arrayA: string[] = ['甲', '乙', '丙']
  private arrayB: string[] = ['a', 'b', 'c', 'd']
  @State popupItemBackgroundColorType: ResourceColor = 0xffc0cb

  aboutToAppear(): void {
    loadComponentTestEntry(alphabetIndexerPopupItemBackgroundColorTest);
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
        .popupItemBackgroundColor(Color.Pink)
        .usingPopup(true)
        .margin({ left: 200 })
        .id('alphabetIndexerPopupItemBackgroundColor1')
      AlphabetIndexer({ arrayValue: this.arrayA, selected: 0 })
        .onRequestPopupData((index: number) => {
          if (this.arrayA[index] == '甲') {
            return this.arrayB
          } else {
            return []
          }
        })
        .popupItemBackgroundColor(this.popupItemBackgroundColorType)
        .usingPopup(true)
        .margin({ left: 200 })
        .id('alphabetIndexerPopupItemBackgroundColor2')
      Button('AlphabetIndexerPopupItemBackgroundColor1')
        .onClick(() => {
          this.popupItemBackgroundColorType = '#ffa500'
        })
      Button('AlphabetIndexerPopupItemBackgroundColor2')
        .onClick(() => {
          this.popupItemBackgroundColorType = $r('sys.color.ohos_id_color_text_hyperlink')
        })
    }
  }
}