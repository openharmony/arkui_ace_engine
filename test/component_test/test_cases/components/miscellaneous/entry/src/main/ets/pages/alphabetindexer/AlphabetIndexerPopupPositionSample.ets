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
import alphabetIndexerPopupPositionTest from '../MyTest/AlphabetIndexerPopupPositionTest';
import { loadComponentTestEntry } from '@ohos.arkui.componentTest';

@Entry
@Component
struct AlphabetIndexerPopupPositionSample {
  private arrayA: string[] = ['甲', '乙', '丙', '丁', '戊']
  @State popupPositionType: Position = { x: 30.0, y: 24.0 }

  aboutToAppear(): void {
    loadComponentTestEntry(alphabetIndexerPopupPositionTest);
  }

  build() {
    Column() {
      AlphabetIndexer({ arrayValue: this.arrayA, selected: 0 })
        .popupPosition(this.popupPositionType)
        .usingPopup(true)
        .margin({ left: 150 })
        .id('alphabetIndexerPopupPosition1')
      AlphabetIndexer({ arrayValue: this.arrayA, selected: 0 })
        .popupPosition({ x: $r('app.string.length'), y: $r('app.string.length') })
        .usingPopup(true)
        .margin({ left: 150 })
        .id('alphabetIndexerPopupPosition2')
      Button('AlphabetIndexerPopupPosition')
        .onClick(() => {
          this.popupPositionType = { x: '15px', y: '15px' }
        })
    }
  }
}