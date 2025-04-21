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
struct struct_01_style_13_placeholderColor {
  build() {
    Scroll() {
      Column() {
        Column() {
          Text('规格：placeholderColor 异常值颜色与默认值相同').fontColor(Color.Blue)
          TextInput({ placeholder: 'placeholderColor 未设置' })
          TextInput({ placeholder: 'placeholderColor 设置 undefined' }).placeholderColor(undefined)
        }.borderWidth(2)

        Column({ space: 5 }) {
          Text('规格 1 设置参数 placeholderColor枚举值 ').fontColor(Color.Blue)
          Text('pass条件 ：placeholder颜色与描述一致 ').fontColor(Color.Red)
          TextInput({ placeholder: 'Color.Black' }).margin(1).placeholderColor(Color.Black)
          TextInput({ placeholder: 'Color.Blue' }).margin(1).placeholderColor(Color.Blue)
          TextInput({ placeholder: 'Color.Brown' }).margin(1).placeholderColor(Color.Brown)
          TextInput({ placeholder: 'Color.Gray' }).margin(1).placeholderColor(Color.Gray)
          TextInput({ placeholder: 'Color.Grey' }).margin(1).placeholderColor(Color.Grey)
          TextInput({ placeholder: 'Color.Green' }).margin(1).placeholderColor(Color.Green)
          TextInput({ placeholder: 'Color.Orange' }).margin(1).placeholderColor(Color.Orange)
          TextInput({ placeholder: 'Color.Pink' }).margin(1).placeholderColor(Color.Pink)
          TextInput({ placeholder: 'Color.Red' }).margin(1).placeholderColor(Color.Red)
          TextInput({ placeholder: 'Color.White' }).margin(1).placeholderColor(Color.White)
          TextInput({ placeholder: 'Color.Yellow' }).margin(1).placeholderColor(Color.Yellow)
          Text('下面是Color.Transparent')
          TextInput({ placeholder: 'Color.Transparent' }).margin(1).placeholderColor(Color.Transparent)
        }
        .borderWidth(2)
        .margin(10)
        .alignItems(HorizontalAlign.Start)
        .borderColor(Color.Blue)
        .padding(2)

        Column({ space: 5 }) {
          Text('规格 2 placeholderColor 异常值取默认值 ').fontColor(Color.Blue)
          Text('pass条件 ： 异常值颜色与默认值颜色相同 ').fontColor(Color.Red)
          TextInput({ placeholder: '这是默认值颜色，TextInput没有设置placeholderColor' }).margin(1)
          TextInput({ placeholder: '0x0000ff0000ff0000ff0000ff0000ff' })
            .margin(1)
            .placeholderColor(0x0000ff0000ff0000ff0000ff0000ff)
          TextInput({ placeholder: '\'\'' }).margin(1).placeholderColor('')
          TextInput({ placeholder: '0x0000ffabc' }).margin(1).placeholderColor(0x0000ffabc)
          TextInput({ placeholder: 'EmptyString' }).margin(1).placeholderColor('EmptyString')
          TextInput({ placeholder: 'Resource' }).margin(1).placeholderColor('Resource')
        }
        .borderWidth(2)
        .margin(10)
        .alignItems(HorizontalAlign.Start)
        .borderColor(Color.Blue)
        .padding(2)

        Column({ space: 5 }) {
          Text('规格 3 获焦、失焦、点击、长按 无变化 ').fontColor(Color.Blue)
          Text('步骤：')
          Text('1、点击文本框A')
          Text('2、点击文本框B')
          Text('3、长按文本框B')
          Text('4、收起键盘')
          Text('5、长按文本框A')
          Text('pass条件 ： 文本框A、B的颜色不发生变化').fontColor(Color.Red)
          TextInput({ placeholder: '文本框A Color.Green' }).margin(1).placeholderColor(Color.Green)
          TextInput({ placeholder: '文本框B Color.Red' }).margin(1).placeholderColor(Color.Red)
        }
        .borderWidth(2)
        .margin(10)
        .alignItems(HorizontalAlign.Start)
        .borderColor(Color.Blue)
        .padding(2)

      }
    }
    .height('100%')
    .width('100%')
  }
}