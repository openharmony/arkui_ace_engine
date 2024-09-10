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
import alphabetIndexerAlphabetIndexerAttributeTest from '../MyTest/AlphabetIndexerAlphabetIndexerAttributeTest';
import { loadComponentTestEntry } from '@ohos.arkui.componentTest';

class MyAlphabetIndexer implements AttributeModifier<AlphabetIndexerAttribute> {
  isDark: boolean = false

  applyNormalAttribute(instance: AlphabetIndexerAttribute): void {
    if (this.isDark) {
      instance.color(Color.Black)
    } else {
      instance.color(Color.Red)
    }
  }
}

@Entry
@Component
struct AlphabetIndexerAlphabetIndexerAttributeSample {
  @State modifier: MyAlphabetIndexer = new MyAlphabetIndexer()
  private arrayA: string[] = ['甲', '乙', '丙']

  aboutToAppear(): void {
    loadComponentTestEntry(alphabetIndexerAlphabetIndexerAttributeTest);
  }

  build() {
    Row() {
      Column() {
        AlphabetIndexer({ arrayValue: this.arrayA, selected: 0 })
          .attributeModifier(this.modifier)
          .id('alphabetIndexerAlphabetIndexerAttribute')
        Button('AlphabetIndexerAlphabetIndexerAttribute')
          .onClick(() => {
            this.modifier.isDark = !this.modifier.isDark
          })
      }
    }
  }
}