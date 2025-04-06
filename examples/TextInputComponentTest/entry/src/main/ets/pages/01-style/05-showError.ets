/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

@Entry
@Component
struct struct_01_style_05_showError {
  @State errorMessage: string = '这是一个超长文本这是一个超长文本这是一个超长文本这是一个超长文本这是一个超长文本'

  build() {
    Scroll() {
      Column() {
        Column() {
          Text('规格：TextInput.showError 默认undefined，不显示错误提示信息').fontColor(Color.Blue)
          TextInput({ text: '没有设置 showError ' })
          TextInput({ text: ' .showError(undefined) ' }).showError(undefined)
          TextInput({ text: ' .showError() ' }).showError()
        }.borderWidth(2)

        Column() {
          Text('规格：错误提示信息，超长文本超出部分显示省略号...').fontColor(Color.Blue)
          TextInput({ text: ' showError超长文本 ' }).showError(this.errorMessage)
        }.borderWidth(2)

        Column() {
          Text('规格：错误提示信息与字符计数器不应该重叠').fontColor(Color.Blue)
          TextInput({ text: ' 错误提示信息与字符计数器不应该重叠 ' })
            .showError(this.errorMessage)
            .showCounter(true)
            .maxLength(10)
        }.borderWidth(2)

        Column() {
          Text('规格：错误提示信息超长，padding值很大时，错误提示信息与字符计数器重叠').fontColor(Color.Blue)
          TextInput({ text: ' 错误提示信息与字符计数器重叠 ' })
            .showError(this.errorMessage)
            .showCounter(true)
            .maxLength(10)
            .padding({left:200, right:200})
        }.borderWidth(2)



      }
    }
    .height('100%')
    .width('100%')
  }
}