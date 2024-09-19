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

import colorBlendTest from '../MyTest/ColorBlendTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ColorBlendSample {
  aboutToAppear(): void {
    loadComponentTestEntry(colorBlendTest)
  }

  private arrayA: string[] = ['甲', '乙', '丙']
  @State colorBlendType: string | Color | Resource = '#a52a2a'

  build() {
    Column() {
      AlphabetIndexer({ arrayValue: this.arrayA, selected: 0 })
        .id('alphabetIndexerColorBlend1')
        .colorBlend(Color.Green)
        .margin({ bottom: 30 })
      Text('ColorBlend')
        .fontSize(12)
        .width('75%')
        .fontColor(0x000000)
        .id('textColorBlend2')
        .colorBlend(this.colorBlendType)
        .margin({ bottom: 20 })
      Button('ButtonColorBlend')
        .onClick(() => {
          this.colorBlendType = $r('sys.color.ohos_id_color_text_hyperlink')
        })
    }
  }
}