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
struct EnableKeyboardOnFocusStruct {
  @State text: string = ''
  @State inputValue: string = ''

  // 自定义键盘组件
  @Builder
  CustomKeyboardBuilder() {
    Column() {
      Grid() {
        ForEach([1, 2, 3, 4, 5, 6, 7, 8, 9, '*', 0, '#'], (item: number | string) => {
          GridItem() {
            Button(item + '')
              .width(110).onClick(() => {
              this.inputValue += item
            })
          }
        })
      }.maxCount(3).columnsGap(10).rowsGap(10).padding(5)
    }.backgroundColor(Color.Gray)
  }

  build() {
    Column({ space: 20 }) {
      Text() {
        Span('规格:\n')
        Span('1、默认值为true, 同一窗口切换两个输入框时，系统键盘会保持 \n')
        Span('2、自定义键盘不支持键盘接续 \n')
      }.draggable(true)

      Text('默认设置true，同一窗口切换两个输入框时，观察键盘切换行为')
      Row() {
        TextInput({ placeholder: 'TextInput: not set value', text: this.text }).width('50%')
          .onChange((value: string) => {
            this.text = value
          })
        TextArea({ placeholder: 'TextArea: not set value', text: this.text }).width('50%')
          .onChange((value: string) => {
            this.text = value
          })
      }

      Row() {
        TextInput({ placeholder: 'TextInput: set enable to true', text: this.text }).width('50%')
          .enableKeyboardOnFocus(true)
          .onChange((value: string) => {
            this.text = value
          })
        TextArea({ placeholder: 'TextArea: set enable to true', text: this.text }).width('50%')
          .enableKeyboardOnFocus(true)
          .onChange((value: string) => {
            this.text = value
          })
      }

      Row() {
        TextInput({ placeholder: 'TextInput: set enable to false', text: this.text }).width('50%')
          .enableKeyboardOnFocus(false)
          .onChange((value: string) => {
            this.text = value
          })
        TextArea({ placeholder: 'TextArea: set enable to false', text: this.text }).width('50%')
          .enableKeyboardOnFocus(false)
          .onChange((value: string) => {
            this.text = value
          })
      }

      Text('自定义键盘不支持键盘接续')
      Row() {
        TextArea({ placeholder: 'TextArea', text: this.inputValue })
          .width('50%')
          .enableKeyboardOnFocus(true)
          .customKeyboard(this.CustomKeyboardBuilder(), { supportAvoidance: true })
          .margin(2)
          .onChange((value: string) => {
            this.text = value
          })
        TextInput({ placeholder: 'TextInput', text: this.inputValue })
          .width('50%')
          .enableKeyboardOnFocus(true)
          .customKeyboard(this.CustomKeyboardBuilder(), { supportAvoidance: true })
          .margin(2)
          .onChange((value: string) => {
            this.text = value
          })
      }
    }.width('100%')
  }
}