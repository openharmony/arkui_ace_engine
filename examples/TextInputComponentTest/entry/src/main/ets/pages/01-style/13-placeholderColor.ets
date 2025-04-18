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
struct struct_01_style_13_placeholderColor {
  build() {
    Scroll() {
      Column() {
        Column() {
          Text('规格：placeholderColor 异常值颜色与默认值相同').fontColor(Color.Blue)
          TextInput({ placeholder: 'placeholderColor 未设置' })
          TextInput({ placeholder: 'placeholderColor 设置 undefined' }).placeholderColor(undefined)
        }.borderWidth(2)
      }
    }
    .height('100%')
    .width('100%')
  }
}