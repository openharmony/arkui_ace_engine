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
import textInputBarStateTest from '../MyTest/TextInputBarStateTest'

@Entry
@Component
struct TextInputBarStateSample {
  @State text: string = ''
  @State onValue: BarState = BarState.On

  aboutToAppear(): void {
    loadComponentTestEntry(textInputBarStateTest)
  }

  controller: TextInputController = new TextInputController()

  build() {
    Column() {
      TextInput({ text: this.text, controller: this.controller })
        .barState(BarState.Off)
        .id('textInputBarState1')
      TextInput({ text: this.text, controller: this.controller })
        .barState(this.onValue)
        .id('textInputBarState2')
      Button('TextInputBarState')
        .onClick(() => {
          this.onValue = BarState.Auto
        })
    }
  }
}