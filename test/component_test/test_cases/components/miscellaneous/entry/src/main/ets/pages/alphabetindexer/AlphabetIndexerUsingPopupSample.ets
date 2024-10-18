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
import alphabetIndexerUsingPopupTest from '../MyTest/AlphabetIndexerUsingPopupTest';
import { loadComponentTestEntry } from '@ohos.arkui.componentTest';

@Entry
@Component
struct AlphabetIndexerUsingPopupSample {
  @State usingPopupType: boolean = true
  private arrayA: string[] = ['甲', '乙', '丙', '丁', '戊']

  aboutToAppear(): void {
    loadComponentTestEntry(alphabetIndexerUsingPopupTest);
  }

  build() {
    Column() {
      AlphabetIndexer({ arrayValue: this.arrayA, selected: 0 })
        .usingPopup(this.usingPopupType)
        .margin({ left: 150 })
        .id('alphabetIndexerUsingPopup')
      Button('AlphabetIndexerUsingPopup')
        .onClick(() => {
          this.usingPopupType = !this.usingPopupType
        })
    }
  }
}