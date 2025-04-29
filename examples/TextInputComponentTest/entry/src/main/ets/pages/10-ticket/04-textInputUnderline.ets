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
struct struct_10_04_textInputUnderline {
  @State text: string = ''

  build() {
    Column() {
      Text('操作： 在输入框一直输入内容，让Text组件内容增加时将该输入框顶下去，多顶几行。  然后一直按住删除键')
      Text('预期： 只显示输入框的那一条线，不会存在多条线')
      Text('内容' + this.text).fontSize(20)
      TextInput({ text: this.text }).showUnderline(true).fontSize(20).onChange((text: string) => {
        this.text = text
      })
    }
    .width('100%')
    .height('100%')
  }
}