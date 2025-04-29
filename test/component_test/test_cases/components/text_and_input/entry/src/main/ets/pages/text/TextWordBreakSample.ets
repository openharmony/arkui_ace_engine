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
//测试代码路径
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'
import textWordBreakTest from '../MyTest/TextWordBreakTest'

@Entry
@Component
struct TextWordBreakSample {
  @State wordBreakValue: WordBreak = WordBreak.NORMAL

  aboutToAppear(): void {
    loadComponentTestEntry(textWordBreakTest)
  }

  build() {
    Column() {
      Text('This is set wordBreak to WordBreak text content This is set wordBreak to WordBreak text content')
        .wordBreak(WordBreak.BREAK_ALL)
        .border({ width: 1 })
        .id('textWordBreak1')
      Text('This is set wordBreak to WordBreak text.')
        .wordBreak(this.wordBreakValue)
        .border({ width: 1 })
        .id('textWordBreak2')
      Button('TextWordBreak')
        .onClick(() => {
          this.wordBreakValue = WordBreak.BREAK_WORD
        })
    }.height(300).width(335).padding({ left: 35, right: 35, top: 35 })
  }
}