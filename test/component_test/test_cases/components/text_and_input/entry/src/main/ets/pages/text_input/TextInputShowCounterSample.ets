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
import textInputShowCounterTest from '../MyTest/TextInputShowCounterTest'

@Entry
@Component
struct TextInputShowCounterSample {
  @State text: string = ''
  @State value: boolean = true
  @State highlightBorderType: boolean = false
  controller: TextInputController = new TextInputController()

  aboutToAppear(): void {
    loadComponentTestEntry(textInputShowCounterTest)
  }

  build() {
    Column() {
      TextInput({ text: this.text, controller: this.controller })
        .showCounter(this.value, { highlightBorder: this.highlightBorderType })
        .maxLength(10)
        .id('textInputShowCounter1')
      Button('TextInputShowCounter1')
        .onClick(() => {
          this.value = !this.value
        })
      Button('TextInputShowCounter2')
        .onClick(() => {
          this.highlightBorderType = !this.highlightBorderType
        })
      TextInput({ text: this.text, controller: this.controller })
        .showCounter(true, { thresholdPercentage: 70, highlightBorder: true })
        .maxLength(10)
        .id('textInputShowCounter2')
    }
  }
}