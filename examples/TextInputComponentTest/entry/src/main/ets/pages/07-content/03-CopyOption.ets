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
struct CopyOptionStruct {
  @State text1: string = ''
  @State text2: string = ''
  @State text3: string = ''

  build() {
    Column({ space: 20 }) {
      Text() {
        Span('规格:\n')
        Span('1、默认CopyOptions.LocalDevice,支持设备内复制 \n')
        Span('2、CopyOptions.None时无法复制，但可以粘贴 \n')
        Span('3、对于拖拽，只限制是否选中，不涉及拖拽范围 \n')
      }.draggable(true).copyOption(CopyOptions.InApp)

      Text('设置异常值，同默认值')
      TextInput({ placeholder: 'TextInput', text: this.text1 })
        .copyOption(-1)
        .onChange((value: string) => {
          this.text1 = value
        })
      TextArea({ placeholder: 'TextArea', text: this.text1 })
        .copyOption(-1)
        .onChange((value: string) => {
          this.text1 = value
        })
      Text('设置CopyOptions.None时无法复制，但可以粘贴')
      TextInput({ placeholder: 'TextInput', text: this.text2 })
        .copyOption(CopyOptions.None)
        .onChange((value: string) => {
          this.text2 = value
        })
      TextArea({ placeholder: 'TextArea', text: this.text2 })
        .copyOption(CopyOptions.None)
        .onChange((value: string) => {
          this.text2 = value
        })
      Text('拖拽，只限制是否选中，不涉及拖拽范围')
      TextInput({ placeholder: 'TextInput', text: this.text3 })
        .copyOption(CopyOptions.LocalDevice)
        .onChange((value: string) => {
          this.text3 = value
        })
      TextArea({ placeholder: 'TextArea', text: this.text3 })
        .copyOption(CopyOptions.LocalDevice)
        .onChange((value: string) => {
          this.text3 = value
        })
    }.width('100%')
  }
}