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
struct Ets_8_8_onSecurityStateChange {
  @State timeOnSecurityStateChange1: number = 0
  @State state: Boolean = false
  @State text1: string = '这是一段单行文本'
  @State textReset: string = '这是一段单行文本'
  controller1: TextInputController = new TextInputController()
  @State state2: Boolean = false
  @State type2: InputType = InputType.Password

  build() {
    Scroll() {
      Column() {
        Text() {
          Span('onSecurityStateChange 事件')
          Span('规格1 仅仅在password生效')
          Span('规格2 从password切换到其他模式不会产生回调，切换到password也不会')
        }

        Column() {
          Text('规格1 仅仅在password生效').fontColor(Color.Blue)
          Text('测试步骤：\n 点击小眼睛 \n ')
          Text('pass条件：回调次数+1').fontColor(Color.Red)
          TextInput({ text: this.text1, controller: this.controller1 })
            .margin(1)
            .type(InputType.Normal)
            .id('TextInput_1')
            .type(InputType.Password)
            .onSecurityStateChange((callback: Boolean) => {
              this.timeOnSecurityStateChange1++
              this.state = callback
            })
          Text('这是回调触发次数')
          Text('触发次数 ' + this.timeOnSecurityStateChange1).margin(1)
          Text('这是回调返回值')
          Text('返回值 ' + this.state).margin(1)
        }.borderWidth(2).margin(10).alignItems(HorizontalAlign.Start).borderColor(Color.Blue)

        Column() {
          Text('规格2 从password切换到其他模式不会产生回调，切换到password也不会').fontColor(Color.Blue)
          Text('测试步骤：\n 点击按钮，查看回调次数 \n ')
          TextInput({ text: this.text1, controller: this.controller1 })
            .margin(1)
            .type(InputType.Normal)
            .id('TextInput_2')
            .type(this.type2)
            .onSecurityStateChange((callback: Boolean) => {
              this.timeOnSecurityStateChange1++
              this.state = callback
            })
          Text('这是回调触发次数')
          Text('触发次数 ' + this.timeOnSecurityStateChange1).margin(1)
          Text('这是回调返回值')
          Text('返回值 ' + this.state2).margin(1)
          Button('更改InputType类型到Normal')
            .onClick(() => {
              this.type2 = InputType.Normal
            })
          Button('更改InputType类型到 Password')
            .onClick(() => {
              this.type2 = InputType.Password
            })
        }.borderWidth(2).margin(10).alignItems(HorizontalAlign.Start).borderColor(Color.Blue)

        TextArea()
          .borderWidth(2)
          .height(500)
          .opacity(0)
      }
    }
  }
}