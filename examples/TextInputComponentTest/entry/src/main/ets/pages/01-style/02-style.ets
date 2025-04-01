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
struct struct_01_style_02_style {
  build() {
    Scroll() {
      Column() {
        Column() {
          Text('规格：style 异常值取 TextInputStyle.Default').fontColor(Color.Blue)
          TextInput({ placeholder: '.style(TextInputStyle.Default)' }).style(TextInputStyle.Default)
          TextInput({ placeholder: '未设置style' })
          TextInput({ placeholder: '.style(undefined)' }).style(undefined)

          Column({ space: 5 }) {
            Text('规格：内联模式第一次获焦时不弹手柄，后续单击操作允许弹手柄').fontColor(Color.Blue)
            TextInput({ text: `文本框点击两次，第三次点击光标` }).style(TextContentStyle.INLINE)
            TextInput({ text: `文本框点击两次，第三次点击光标` }).style(TextInputStyle.Inline)
          }.borderWidth(2)

          Column({ space: 5 }) {
            Text('规格：TextInput 内联模式，全选多行文本，显示空行连接线（2vp）').fontColor(Color.Blue)
            TextInput({ text: `ABC CDE，点击全选` }).style(TextInputStyle.Inline)
          }.borderWidth(2)

        }.borderWidth(2)
      }
    }
    .height('100%')
    .width('100%')
  }
}