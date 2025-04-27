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
struct struct_01_style_11_ShowCounter {
  build() {
    Scroll() {
      Column() {
        Column({ space: 5 }) {
          Text('规格：TextInput.showCounter 只设置第一个参数时，变红无抖动').fontColor(Color.Blue)
          TextInput({ text: `showCounter 只设置第一个参数` }).maxLength(10).showCounter(true)
          TextInput({ text: `showCounter 设置两个参数` }).maxLength(10).showCounter(true,
            { thresholdPercentage: 50, highlightBorder: true })
        }.borderWidth(2)

        Column({ space: 5 }) {
          Text('规格：输入/最大字符比值超过 thresholdPercentage 时，显示计数器 ').fontColor(Color.Blue)
          TextInput({ text: `12345` }).maxLength(10).showCounter(true,
            { thresholdPercentage: 50, highlightBorder: true })
          TextInput({ text: `123456` }).maxLength(10).showCounter(true,
            { thresholdPercentage: 50, highlightBorder: true })
        }.borderWidth(2)

        Column({ space: 5 }) {
          Text('规格：thresholdPercentage 超出[0,100]范围时，不显示计数器 ').fontColor(Color.Blue)
          TextInput({ text: `thresholdPercentage = -1` }).maxLength(30).showCounter(true,
            { thresholdPercentage: -1, highlightBorder: true })
          TextInput({ text: `thresholdPercentage = 0` }).maxLength(30).showCounter(true,
            { thresholdPercentage: 0, highlightBorder: true })
          TextInput({ text: `thresholdPercentage = 1` }).maxLength(30).showCounter(true,
            { thresholdPercentage: 1, highlightBorder: true })
          TextInput({ text: `thresholdPercentage = 100` }).maxLength(30).showCounter(true,
            { thresholdPercentage: 100, highlightBorder: true })
          TextInput({ text: `thresholdPercentage = 101` }).maxLength(30).showCounter(true,
            { thresholdPercentage: 101, highlightBorder: true })
        }.borderWidth(2)

        Column({ space: 5 }) {
          Text('规格：thresholdPercentage 必须配合maxLine才可以生效，inline和密码模式不生效 ').fontColor(Color.Blue)
          TextInput({ text: `有maxLength` }).maxLength(30).showCounter(true,
            { thresholdPercentage: 10, highlightBorder: true })
          TextInput({ text: `没有maxLength` }).maxLength(30).showCounter(true,
            { thresholdPercentage: 10, highlightBorder: true })
          TextInput({ text: `TextInputStyle.Inline` }).maxLength(30).showCounter(true,
            { thresholdPercentage: 10, highlightBorder: true }).style(TextInputStyle.Inline)
          TextInput({ text: `InputType.Password` }).maxLength(30).showCounter(true,
            { thresholdPercentage: 10, highlightBorder: true }).type(InputType.Password)
          TextInput({ text: `InputType.NEW_PASSWORD` }).maxLength(30).showCounter(true,
            { thresholdPercentage: 10, highlightBorder: true }).type(InputType.NEW_PASSWORD)
        }.borderWidth(2)

        Column({ space: 5 }) {
          Text('规格：highlightBorder 默认值true ').fontColor(Color.Blue)
          TextInput({ text: `设置 highlightBorder true` }).maxLength(30).showCounter(true,
            { thresholdPercentage: 10, highlightBorder: true })
          TextInput({ text: `没有设置 highlightBorder` }).maxLength(30).showCounter(true,
            { thresholdPercentage: 10 })
          TextInput({ text: `设置 highlightBorder undefined` }).maxLength(30).showCounter(true,
            { thresholdPercentage: 10, highlightBorder: undefined })
          TextInput({ text: `设置 highlightBorder false` }).maxLength(30).showCounter(true,
            { thresholdPercentage: 10, highlightBorder: false })
        }.borderWidth(2)

        Column({ space: 5 }) {
          Text('规格：变红抖动的规则是，达到maxLength，继续输入，才会变红抖动 ').fontColor(Color.Blue)
          TextInput({ text: `已达到 maxLength 继续输入` }).maxLength(30).showCounter(true,
            { thresholdPercentage: 10, highlightBorder: true })
          TextInput({ text: `已达到 maxLength 不继续输入` }).maxLength(30).showCounter(true,
            { thresholdPercentage: 10, highlightBorder: true })
        }.borderWidth(2)

        Column({ space: 5 }) {
          Text('规格：showCounter参数1设置true时， thresholdPercentage和highlightBorder分别设置 undefined 时，显示字符计数器；' +
            '且输入超过最大值时，字符计数器变红，输入框变红且不抖动')
            .fontColor(Color.Blue)
          TextInput({ text: `maxLength=10` }).maxLength(10).showCounter(true,
            { thresholdPercentage: undefined, highlightBorder: undefined })
        }.borderWidth(2)

        Column({ space: 5 }) {
          Text('规格：showCounter参数1设置 undefined 时， showCounter Option设置 undefined时，不显示字符计数器')
            .fontColor(Color.Blue)
          TextInput({ text: `.showCounter(true,undefined)` }).maxLength(10).showCounter(true, undefined)
        }.borderWidth(2)

        Column({ space: 5 }) {
          Text('规格：设置InputType.PhoneNumber，未达到输入最大值时，字符计数器保持黑色，不抖动 ')
            .fontColor(Color.Blue)
          TextInput({ text: `123456789` })
            .maxLength(10)
            .showCounter(true, { thresholdPercentage: 1, highlightBorder: true })
            .type(InputType.PhoneNumber)
        }.borderWidth(2)

        Column({ space: 5 }) {
          Text('规格：设置InputType.PhoneNumber，未达到输入最大值时，字符计数器保持黑色，不抖动 ')
            .fontColor(Color.Blue)
          TextInput({ text: `123456789` })
            .maxLength(10)
            .showCounter(true, { thresholdPercentage: 1, highlightBorder: true })
            .type(InputType.PhoneNumber)
        }.borderWidth(2)

        Column({ space: 5 }) {
          Text('规格：焦点从当前输入框切换到其他输入框时，红色警示消失，保持默认灰色计数器状态，记录最大输入字符。焦点从其他输入框切换会来时，保持灰色计数器状态。再次输入时出现红色示警 ')
            .fontColor(Color.Blue)
          TextInput({ text: `12345678910` })
            .maxLength(10)
            .showCounter(true, { thresholdPercentage: 1, highlightBorder: true })
          TextInput({ text: `123456789` })
            .maxLength(10)
            .showCounter(true, { thresholdPercentage: 1, highlightBorder: true })
        }.borderWidth(2)

        Column({ space: 5 }) {
          Text('规格：通过粘贴输入文本，未达到输入最大值，边框没有变红抖动 ')
            .fontColor(Color.Blue)
          TextInput({ text: `123456剩下的是好多好多汉字超过一十五个` })
          TextInput({ text: `123456` })
            .maxLength(15)
            .showCounter(true, { thresholdPercentage: 1, highlightBorder: true })
            .type(InputType.Number)
        }.borderWidth(2)

        Column({ space: 5 }) {
          Text('规格：样式是下划线时，达到最大输入字符数，只有下划线变红 ')
            .fontColor(Color.Blue)
          TextInput({ text: `123456剩下的是好多好多汉字超过一十五个` })
          TextInput({ text: `已设置showUnderline` })
            .maxLength(20)
            .showCounter(true, undefined)
            .showUnderline(true)
          TextInput({ text: `未设置showUnderline` })
            .maxLength(20)
            .showCounter(true, undefined)
        }.borderWidth(2)

      }
    }
    .height('100%')
    .width('100%')
  }
}