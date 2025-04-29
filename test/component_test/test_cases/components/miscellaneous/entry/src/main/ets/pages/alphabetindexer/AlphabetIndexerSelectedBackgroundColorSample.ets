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
import alphabetIndexerSelectedBackgroundColorTest from '../MyTest/AlphabetIndexerSelectedBackgroundColorTest';
import { loadComponentTestEntry } from '@ohos.arkui.componentTest';

@Entry
@Component
struct AlphabetIndexerSelectedBackgroundColorSample {
  @State selectedBackgroundColorType: ResourceColor = 0x808080
  private arrayA: string[] = ['甲', '乙', '丙']

  aboutToAppear(): void {
    loadComponentTestEntry(alphabetIndexerSelectedBackgroundColorTest);
  }

  build() {
    Column() {
      AlphabetIndexer({ arrayValue: this.arrayA, selected: 0 })
        .selectedBackgroundColor(Color.Red)
        .id('alphabetIndexerSelectedBackgroundColor1')
      AlphabetIndexer({ arrayValue: this.arrayA, selected: 0 })
        .selectedBackgroundColor(this.selectedBackgroundColorType)
        .id('alphabetIndexerSelectedBackgroundColor2')
      Button('AlphabetIndexerSelectedBackgroundColor1')
        .onClick(() => {
          this.selectedBackgroundColorType = '#ffa500'
        })
      Button('AlphabetIndexerSelectedBackgroundColor2')
        .onClick(() => {
          this.selectedBackgroundColorType = $r('sys.color.ohos_id_color_text_hyperlink')
        })
    }
  }
}