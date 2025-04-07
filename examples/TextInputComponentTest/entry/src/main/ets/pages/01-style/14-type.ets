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
struct struct_01_style_14_type {
  @State text_1: string = '0123abcd`1@& *** ごじゅうおんず عرب 汉字'
  @State text_3: string = '012@abc@! # $ % & \' * + - / = ? ^ ` { | } ~'
  @State text_4: string = '0123abcd`1@& *** ごじゅうおんず عرب 汉字'
  @State text_5: string = '0123+#*()abcd`@&***ごじゅうおんずعرب汉字'
  @State text_8: string = '0123 abcd +#*()'
  @State text_9: string = '1234.5678.90 abcd +#*()'

  build() {
    Scroll() {
      Column() {
        Column() {
          Text('规格1 设置参数 Normal[无输入限制],').fontColor(Color.Blue)
          Text('pass条件：显示以下内容 \n  0123abcd`1@& *** ごじゅうおんず عرب 汉字').fontColor(Color.Red)
          TextInput({ placeholder: 'TextInput', text: this.text_1 }).margin(1).type(InputType.Normal)
        }.borderWidth(2)

        Column() {
          Text('规格2 设置参数 Password[密码输入模式，应该显示小眼睛图标]').fontColor(Color.Blue)
          Text('pass条件：:显示小眼睛图标').fontColor(Color.Red)
          TextInput({ placeholder: 'TextInput' }).margin(1).type(InputType.Password)
        }.borderWidth(2)

        Column() {
          Text('规格3 设置参数 Email[只能有一个@]').fontColor(Color.Blue)
          Text('实际输入是：012@abc@! # $ % & \' * + - / = ? ^ ` { | } ~')
          Text('pass条件: 只显示 \n 012@abc ! # $ % & \' * + - / = ? ^ ` { | } ~').fontColor(Color.Red)
          TextInput({ text: this.text_3 }).margin(1).type(InputType.Email)
        }.borderWidth(2)

        Column() {
          Text('规格4 设置参数 Number[只能输入数字]').fontColor(Color.Blue)
          Text('实际输入是：0123abcd`1@& *** ごじゅうおんず عرب 汉字')
          Text('pass条件: 只显示 \n 01231').fontColor(Color.Red)
          TextInput({ placeholder: 'TextInput', text: this.text_4 }).margin(1).type(InputType.Number)
        }.borderWidth(2)

        Column() {
          Text('规格5 设置参数 PhoneNumber[支持输入数字、空格、+、-、*、#、(、)]').fontColor(Color.Blue)
          Text('实际输入是：0123+#*()abcd`@&***ごじゅうおんずعرب汉字')
          Text('pass 条件: 显示以下内容 \n 0123+#*()***').fontColor(Color.Red)
          TextInput({ text: this.text_5 }).margin(1).type(InputType.PhoneNumber)
        }.borderWidth(2)


        Column() {
          Text('规格6 设置参数 USER_NAME[用户名输入模式，支持用户名、密码的自动保存与填充]').fontColor(Color.Blue)
          TextInput({}).margin(1).type(InputType.USER_NAME)
        }.borderWidth(2)

        Column() {
          Text('规格7 设置参数 NEW_PASSWORD[新密码输入模式，显示小眼睛图标]').fontColor(Color.Blue)
          Text('pass 条件:显示小眼睛图标').fontColor(Color.Red)
          TextInput({}).margin(1).type(InputType.NEW_PASSWORD)
        }.borderWidth(2)

        Column() {
          Text('规格8 设置参数 NUMBER_PASSWORD[纯数字密码模式]').fontColor(Color.Blue)
          Text('pass 条件: 显示小眼睛图标和四个星花，点击小眼睛，出现0123').fontColor(Color.Red)
          TextInput({ text: this.text_8 }).margin(1).type(InputType.NUMBER_PASSWORD)
        }.borderWidth(2)

        Column() {
          Text('规格9 设置参数 NUMBER_DECIMAL[支持数字，小数点.(仅一个)]').fontColor(Color.Blue)
          Text('实际输入是' + this.text_9)
          Text('pass 条件: 出现1234.567890').fontColor(Color.Red)
          TextInput({ text: this.text_9 }).margin(1).type(InputType.NUMBER_DECIMAL)
        }.borderWidth(2)
      }
    }
    .height('100%')
    .width('100%')
  }
}