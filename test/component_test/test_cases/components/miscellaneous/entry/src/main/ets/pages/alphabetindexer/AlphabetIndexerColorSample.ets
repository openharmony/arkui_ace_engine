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
import alphabetIndexerColorTest from '../MyTest/AlphabetIndexerColorTest';
import { loadComponentTestEntry } from '@ohos.arkui.componentTest';

@Entry
@Component
struct AlphabetIndexerColorSample {
  @State colorType: ResourceColor = 0x808080
  private arrayA: string[] = ['甲', '乙', '丙']

  aboutToAppear(): void {
    loadComponentTestEntry(alphabetIndexerColorTest);
  }

  build() {
    Column() {
      AlphabetIndexer({ arrayValue: this.arrayA, selected: 0 })
        .color(Color.Gray)
        .id('alphabetIndexerColor1')
      AlphabetIndexer({ arrayValue: this.arrayA, selected: 0 })
        .color(this.colorType)
        .id('alphabetIndexerColor2')
      Button('AlphabetIndexerColor1')
        .onClick(() => {
          this.colorType = '#ffa500'
        })
      Button('AlphabetIndexerColor2')
        .onClick(() => {
          this.colorType = $r('sys.color.ohos_id_color_text_hyperlink')
        })
    }
  }
}