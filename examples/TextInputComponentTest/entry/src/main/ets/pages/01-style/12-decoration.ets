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
struct struct_01_style_12_decoration {
  build() {
    Scroll() {
      Column() {
        Column({ space: 5 }) {
          Text('规格：文本装饰线类型默认是None，不显示装饰性，异常值取默认值').fontColor(Color.Blue)
          TextInput({ text: `.decoration({type:TextDecorationType.None}) ` })
            .decoration({ type: TextDecorationType.None })
          TextInput({ text: `没有设置 .decoration ` })
          TextInput({ text: `.decoration(undefined) ` }).decoration(undefined)
        }.borderWidth(2)

        Column({ space: 5 }) {
          Text('规格：装饰线样式默认SOLID实线').fontColor(Color.Blue)
          TextInput({ text: `没有设置TextDecorationStyle ` }).decoration({ type: TextDecorationType.Overline })
          TextInput({ text: `设置style:TextDecorationStyle.SOLID ` })
            .decoration({ type: TextDecorationType.Overline, style: TextDecorationStyle.SOLID })
        }.borderWidth(2)

        Column({ space: 5 }) {
          Text('规格：密码模式不显示装饰线').fontColor(Color.Blue)
          TextInput({ text: `Password 设置了下划线 ` })
            .decoration({ type: TextDecorationType.Underline })
            .type(InputType.Password)
          TextInput({ text: `NEW_PASSWORD 设置了下划线 ` })
            .decoration({ type: TextDecorationType.Underline })
            .type(InputType.NEW_PASSWORD)
        }.borderWidth(2)

        Column({ space: 5 }) {
          Text('规格：获得焦点、失去焦点、点击、长按，下划线不变').fontColor(Color.Blue)
          TextInput({ text: `Password 设置了下划线 ` })
            .decoration({ type: TextDecorationType.Underline })
          TextInput({ text: `NEW_PASSWORD 设置了下划线 ` })
            .decoration({ type: TextDecorationType.Underline })
        }.borderWidth(2)
      }
    }
    .height('100%')
    .width('100%')
  }
}