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
import textInputFontWeightTest from '../MyTest/TextInputFontWeightTest'

@Entry
@Component
struct TextInputFontWeightSample {
  @State text: string = ''
  @State weightType: FontWeight[] = [FontWeight.Bold, FontWeight.Regular, FontWeight.Medium, FontWeight.Bolder, 800]
  @State index: number = 0
  controller: TextInputController = new TextInputController()

  aboutToAppear(): void {
    loadComponentTestEntry(textInputFontWeightTest)
  }

  build() {
    Column() {
      TextInput({ text: this.text, controller: this.controller })
        .fontWeight(FontWeight.Lighter)
        .id('textInputFontWeight1')
      TextInput({ text: this.text, controller: this.controller })
        .fontWeight("400")
        .id('textInputFontWeight2')
      TextInput({ text: this.text, controller: this.controller })
        .fontWeight(FontWeight.Normal)
        .id('textInputFontWeight3')
      TextInput({ text: this.text, controller: this.controller })
        .fontWeight(this.weightType[this.index])
        .id('textInputFontWeight4')
      Button('TextInputFontWeight')
        .onClick(() => {
          this.index++
          this.index %= 5
        })
    }
  }
}