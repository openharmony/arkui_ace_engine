/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

@Entry
@Component
struct MaxLengthStruct {
  @State textInput1: string = ''
  @State textInput2: string = ''
  @State textInput3: string = ''
  @State textInput4: string = ''
  @State textArea1: string = ''
  @State textArea2: string = ''
  @State textArea3: string = ''
  @State textArea4: string = ''

  build() {
    Column({ space: 20 }) {
      Text('设置异常值，同默认值，无最大输入限制')
      TextInput({ placeholder: 'TextInput', text: this.textInput1 })
        .maxLength(-1)
        .showCounter(true)
        .onChange((value: string) => {
          this.textInput1 = value
        })
      TextArea({ placeholder: 'TextArea', text: this.textArea1 })
        .maxLength(-1)
        .showCounter(true)
        .onChange((value: string) => {
          this.textArea1 = value
        })
      Text('输入单个emoji，预期不允许输入')
      TextInput({ placeholder: 'TextInput', text: this.textInput2 })
        .maxLength(1)
        .showCounter(true)
        .onChange((value: string) => {
          this.textInput2 = value
        })
      TextArea({ placeholder: 'TextArea', text: this.textArea2 })
        .maxLength(1)
        .showCounter(true)
        .onChange((value: string) => {
          this.textArea2 = value
        })
      Text('输入emoji string: \ud83c\udf0d\ud83c\udf0d\ud83c\udf0d，预期右截断').copyOption(CopyOptions.LocalDevice)
      TextInput({ placeholder: 'TextInput', text: this.textInput3 })
        .maxLength(4)
        .showCounter(true)
        .onChange((value: string) => {
          this.textInput3 = value
        })
      TextArea({ placeholder: 'TextArea', text: this.textArea3 })
        .maxLength(4)
        .showCounter(true)
        .onChange((value: string) => {
          this.textArea3 = value
        })
      Text('粘贴string：adllkalfhafhlk，预期右截断').copyOption(CopyOptions.LocalDevice).selection(29, 41)
      TextInput({ placeholder: 'TextInput', text: this.textInput4 })
        .maxLength(4)
        .showCounter(true)
        .onChange((value: string) => {
          this.textInput4 = value
        })
        .copyOption(CopyOptions.None)
      TextArea({ placeholder: 'TextArea', text: this.textArea4 })
        .maxLength(4)
        .showCounter(true)
        .onChange((value: string) => {
          this.textArea4 = value
        })
        .copyOption(CopyOptions.None)
    }.width('100%')
  }
}