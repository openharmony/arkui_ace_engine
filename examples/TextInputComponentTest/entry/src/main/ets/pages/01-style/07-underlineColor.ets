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
struct struct_01_style_07_underlineColor {
  @State errorMessage: string = '这是一个超长文本这是一个超长文本这是一个超长文本这是一个超长文本这是一个超长文本'

  build() {
    Scroll() {
      Column() {
        Column({ space: 5 }) {
          Text('规格：TextInput.underlineColor 默认值"#33182431"，异常值取默认值').fontColor(Color.Blue)
          TextInput({ text: '没有设置 underlineColor ' }).showUnderline(true)
          TextInput({ text: ' .underlineColor(undefined) ' }).showUnderline(true).underlineColor(undefined)
          TextInput({ text: ' .underlineColor("#33182431") ' }).showUnderline(true).underlineColor('#33182431')
          Blank().height(20)
        }.borderWidth(2)

        Column({ space: 5 }) {
          Text('规格：TextInput.underlineColor 与 decoration 同时生效 ').fontColor(Color.Blue)
          TextInput({ text: ' 设置 underlineColor' }).showUnderline(true).underlineColor(Color.Black)
          TextInput({ text: ' 设置 decoration ' }).decoration({
            type: TextDecorationType.Underline,
            color: Color.Red,
            style: TextDecorationStyle.SOLID
          })
          TextInput({ text: ' 设置 underlineColor 和 decoration ' })
            .showUnderline(true)
            .underlineColor(Color.Black)
            .decoration({
              type: TextDecorationType.Underline,
              color: Color.Red,
              style: TextDecorationStyle.SOLID
            })
          Blank().height(20)
        }.borderWidth(2)

      }
    }
    .height('100%')
    .width('100%')
  }
}