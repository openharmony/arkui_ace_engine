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
struct struct_01_style_08_barState {
  build() {
    Scroll() {
      Column() {
        Column({ space: 5 }) {
          Text('规格：TextInput.barState 默认值 BarState.Auto，异常值取默认值').fontColor(Color.Blue)
          TextInput({ text: '没有设置 barState ' }).style(TextInputStyle.Inline)
          TextInput({ text: ' .barState(BarState.Auto) ' }).style(TextInputStyle.Inline).barState(BarState.Auto)
          TextInput({ text: ' .barState(undefined) ' }).style(TextInputStyle.Inline).barState(undefined)
        }.borderWidth(2)

      }
    }
    .height('100%')
    .width('100%')
  }
}