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
struct struct_01_style_01_placeholderFont {
  build() {
    Scroll() {
      Column() {
        Column() {
          Text('规格：placeholderFont size 输入异常值取默认值，默认值16').fontColor(Color.Blue)
          TextInput({ placeholder: 'placeholderFont({ size: 16 })' }).placeholderFont({ size: 16 })
          TextInput({ placeholder: 'placehoderFont 未设置' })
          TextInput({ placeholder: 'placehoderFont' }).placeholderFont({ size: undefined })
          TextInput({ placeholder: 'placeholderFont({ size: -100 })' }).placeholderFont({ size: -100 })
          TextInput({ placeholder: 'placeholderFont({size: "abc"})' }).placeholderFont({ size: 'abc' })
        }.borderWidth(2)

        Column() {
          Text('规格：placeholderFont weight 输入异常值取默认值FontWeight.Normal ').fontColor(Color.Blue)
          TextInput({ placeholder: 'placeholderFont({weight:FontWeight.Normal})' })
          TextInput({ placeholder: 'placehoderFont 未设置' })
            .placeholderFont({ weight: FontWeight.Normal })
          TextInput({ placeholder: 'placeholderFont({weight:undefined})' }).placeholderFont({ weight: undefined })
          TextInput({ placeholder: 'placeholderFont({weight:"abc"})' }).placeholderFont({ weight: 'abc' })
        }.borderWidth(2)

        Column() {
          Text('规格：placeholderFont style 默认值 FontStyle.Normal ').fontColor(Color.Blue)
          TextInput({ placeholder: 'placeholderFont({ style: FontStyle.Normal })' })
            .placeholderFont({ style: FontStyle.Normal })
          TextInput({ placeholder: 'placehoderFont 未设置' })
          TextInput({ placeholder: 'placeholderFont({style:undefined})' }).placeholderFont({ style: undefined })
        }.borderWidth(2)
      }
    }
    .height('100%')
    .width('100%')
  }
}