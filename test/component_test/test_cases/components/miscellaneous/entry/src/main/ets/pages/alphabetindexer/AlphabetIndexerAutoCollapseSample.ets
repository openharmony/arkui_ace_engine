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
import alphabetIndexerAutoCollapseTest from '../MyTest/AlphabetIndexerAutoCollapseTest';
import { loadComponentTestEntry } from '@ohos.arkui.componentTest';

@Entry
@Component
struct AlphabetIndexerAutoCollapseSample {
  private arrayA: string[] = ['#', 'A', 'B', 'C', 'D', 'E', 'F', 'G',
    'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O']
  private arrayB: string[] = ['#', 'A', 'B', 'C', 'D', 'E', 'F', 'G',
    'H', 'I', 'J', 'K']
  private arrayC: string[] = ['#', 'A']
  private arrayD: string[] = ['A', 'B', 'C', 'D', 'E', 'F', 'G',
    'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O']
  private arrayE: string[] = ['A', 'B', 'C', 'D', 'E', 'F', 'G',
    'H', 'I', 'J']
  private arrayF: string[] = ['A', 'B']
  @State autoCollapseType: boolean = true

  aboutToAppear(): void {
    loadComponentTestEntry(alphabetIndexerAutoCollapseTest);
  }

  build() {
    Row() {
      AlphabetIndexer({ arrayValue: this.arrayA, selected: 0 })
        .autoCollapse(this.autoCollapseType)
        .id('alphabetIndexerAutoCollapse1')
      AlphabetIndexer({ arrayValue: this.arrayB, selected: 0 })
        .autoCollapse(true)
        .id('alphabetIndexerAutoCollapse2')
      AlphabetIndexer({ arrayValue: this.arrayC, selected: 0 })
        .autoCollapse(true)
        .id('alphabetIndexerAutoCollapse3')
      AlphabetIndexer({ arrayValue: this.arrayD, selected: 0 })
        .autoCollapse(true)
        .id('alphabetIndexerAutoCollapse4')
      AlphabetIndexer({ arrayValue: this.arrayE, selected: 0 })
        .autoCollapse(true)
        .id('alphabetIndexerAutoCollapse5')
      AlphabetIndexer({ arrayValue: this.arrayF, selected: 0 })
        .autoCollapse(true)
        .id('alphabetIndexerAutoCollapse6')
      Button('AlphabetIndexerAutoCollapse')
        .onClick(() => {
          this.autoCollapseType = !this.autoCollapseType
        })
    }
  }
}