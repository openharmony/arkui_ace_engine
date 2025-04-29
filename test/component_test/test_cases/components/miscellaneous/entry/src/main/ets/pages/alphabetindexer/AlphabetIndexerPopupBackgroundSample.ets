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
import alphabetIndexerPopupBackgroundTest from '../MyTest/AlphabetIndexerPopupBackgroundTest';
import { loadComponentTestEntry } from '@ohos.arkui.componentTest';

@Entry
@Component
struct AlphabetIndexerPopupBackgroundSample {
  @State popupBackgroundColorType: ResourceColor = 0x808080
  private arrayA: string[] = ['甲', '乙', '丙']

  aboutToAppear(): void {
    loadComponentTestEntry(alphabetIndexerPopupBackgroundTest);
  }

  build() {
    Column() {
      AlphabetIndexer({ arrayValue: this.arrayA, selected: 0 })
        .popupBackground(Color.Red)
        .usingPopup(true)
        .margin({ left: 150 })
        .id('alphabetIndexerPopupBackground1')
      AlphabetIndexer({ arrayValue: this.arrayA, selected: 0 })
        .popupBackground(this.popupBackgroundColorType)
        .usingPopup(true)
        .margin({ left: 150 })
        .alignStyle(IndexerAlign.Left)
        .id('alphabetIndexerPopupBackground2')
      Button('AlphabetIndexerPopupBackground1')
        .onClick(() => {
          this.popupBackgroundColorType = '#ffa500'
        })
      Button('AlphabetIndexerPopupBackground2')
        .onClick(() => {
          this.popupBackgroundColorType = $r('sys.color.ohos_id_color_text_hyperlink')
        })
    }
  }
}