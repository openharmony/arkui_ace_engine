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
struct struct_01_style_09_maxLines {
  @State message: string =
    '这是一个超长文本这是一个超长文本这是一个超长文本这是一个超长文本这是一个超长文本这是一个超长文本这是一个超长文本这是一个超长文本这是一个超长文本这是一个超长文本这是一个超长文本这是一个超长文本这是一个超长文本这是一个超长文本这是一个超长文本'

  build() {
    Scroll() {
      Column() {
        Column({ space: 5 }) {
          Text('规格：TextInput.maxLines 默认值 3，取值范围：(0, +∞)').fontColor(Color.Blue)
          TextInput({ text: `没有设置 barState ${this.message}` }).style(TextInputStyle.Inline)
          TextInput({ text: ` .maxLines(3) ${this.message}` }).style(TextInputStyle.Inline).maxLines(3)
          TextInput({ text: ` .maxLines(undefined) ${this.message}` }).style(TextInputStyle.Inline).maxLines(undefined)
          TextInput({ text: ` .maxLines(0) ${this.message}` }).style(TextInputStyle.Inline).maxLines(0)
          TextInput({ text: ` .maxLines(0.5) ${this.message}` }).style(TextInputStyle.Inline).maxLines(0.5)
          TextInput({ text: ` .maxLines(-5) ${this.message}` }).style(TextInputStyle.Inline).maxLines(-5)
        }.borderWidth(2)

      }
    }
    .height('100%')
    .width('100%')
  }
}