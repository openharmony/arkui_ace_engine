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
struct struct_01_style_06_showUnderline {
  build() {
    Scroll() {
      Column() {
        Column() {
          Text('规格：TextInput.showUnderline 默认false，异常值取默认值').fontColor(Color.Blue)
          TextInput({ text: '没有设置 showUnderline ' })
          TextInput({ text: ' .showUnderline(false) ' }).showUnderline(false)
          TextInput({ text: ' .showUnderline(undefined) ' }).showUnderline(undefined)
        }.borderWidth(2)

        Column() {
          Text('规格：TextInput.showUnderline 文本框获得焦点、失去焦点、点击、长按没变化').fontColor(Color.Blue)
          TextInput({ text: ' .showUnderline(true) ' }).showUnderline(true)
          TextInput({ text: ' .showUnderline(false) ' }).showUnderline(false)
        }.borderWidth(2)

        Column() {
          Text('规格：TextInput设置下划线，不影响计数器&删除按钮&文本的位置').fontColor(Color.Blue)
          TextInput({ text: ' .showUnderline(true) ' })
            .showUnderline(false)
            .showCounter(true, undefined)
            .maxLength(10)
            .cancelButton({ style: CancelButtonStyle.CONSTANT })
            .padding(10)
          TextInput({ text: ' .showUnderline(false) ' })
            .showUnderline(true)
            .showCounter(true, undefined)
            .maxLength(10)
            .cancelButton({ style: CancelButtonStyle.CONSTANT })
            .padding(10)
          Blank().height(20)
        }.borderWidth(2)

      }
    }
    .height('100%')
    .width('100%')
  }
}