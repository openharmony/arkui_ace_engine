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
import alphabetIndexerItemSizeTest from '../MyTest/AlphabetIndexerItemSizeTest';
import { loadComponentTestEntry } from '@ohos.arkui.componentTest';

@Entry
@Component
struct AlphabetIndexerItemSizeSample {
  private arrayA: string[] = ['甲', '乙', '丙', '丁', '戊']
  @State itemSizeType: number | string = 32

  aboutToAppear(): void {
    loadComponentTestEntry(alphabetIndexerItemSizeTest);
  }

  build() {
    Column() {
      AlphabetIndexer({ arrayValue: this.arrayA, selected: 0 })
        .itemSize(this.itemSizeType)
        .id('alphabetIndexerItemSize')
      Button('AlphabetIndexerItemSize')
        .onClick(() => {
          this.itemSizeType = '100px'
        })
    }
  }
}