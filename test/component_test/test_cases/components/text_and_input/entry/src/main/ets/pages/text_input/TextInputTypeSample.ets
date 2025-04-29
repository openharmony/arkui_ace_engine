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
import textInputTypeTest from '../MyTest/TextInputTypeTest'

@Entry
@Component
struct TextInputTypeSample {
  @State text: string = ''
  @State inputType: InputType[] = [InputType.Email, InputType.Number, InputType.PhoneNumber, InputType.USER_NAME
    , InputType.NEW_PASSWORD, InputType.NUMBER_PASSWORD, InputType.NUMBER_DECIMAL]
  @State index: number = 0
  controller: TextInputController = new TextInputController()

  aboutToAppear(): void {
    loadComponentTestEntry(textInputTypeTest)
  }

  build() {
    Column() {
      TextInput({ text: this.text, controller: this.controller })
        .type(InputType.Normal)
        .id('textInputType1')
      TextInput({ text: this.text, controller: this.controller })
        .type(InputType.Password)
        .id('textInputType2')
      TextInput({ text: this.text, controller: this.controller })
        .type(this.inputType[this.index])
        .id('textInputType3')
      Button('TextInputType1')
        .onClick(() => {
          this.index++
          this.index %= 7
        })
    }
  }
}