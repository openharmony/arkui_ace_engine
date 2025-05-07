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
struct Ets_8_2_onSubmit {
  @State time_onSubmit_1: number = 0
  @State text_1: string = ''

  build() {
    Scroll() {
      Column() {
        Text() {
          Span('onSubmit事件  规格未明确，需要owner确认，已提单').fontColor(Color.Red)
          Span('规格1 输入法回车键类型为EnterKeyType.NEW_LINE时，不触发onSubmit\n')
        }

        Column() {
          Text('规格1 textInput，输入法回车键类型为EnterKeyType.NEW_LINE时，触发onSubmit').fontColor(Color.Blue)
          Text('测试步骤：\n 1、输入一段内容')
          Text('pass条件：文本框1点击回车，回调次数+1').fontColor(Color.Red)
          TextInput({ text: '这是一段示例内容用于测试 onSubmit' }).margin(1).type(InputType.Normal)
            .enterKeyType(EnterKeyType.NEW_LINE)
            .onSubmit(() => {
              this.time_onSubmit_1++;
            })

          Text('这是回调触发次数')
          Text('触发次数 ' + this.time_onSubmit_1).margin(1)
        }.borderWidth(2).margin(10).alignItems(HorizontalAlign.Start).borderColor(Color.Blue)


        Column() {
          Text('规格1 textArea，输入法回车键类型为EnterKeyType.NEW_LINE时，触发onSubmit').fontColor(Color.Blue)
          Text('测试步骤：\n 1、输入一段内容')
          Text('pass条件：文本框1点击回车，回调次数不变').fontColor(Color.Red)
          TextArea({ text: '这是一段示例内容用于测试 TextArea onSubmit' }).margin(1)
            .enterKeyType(EnterKeyType.NEW_LINE)
            .onSubmit(() => {
              this.time_onSubmit_1++;
            })

          Text('这是回调触发次数')
          Text('触发次数 ' + this.time_onSubmit_1).margin(1)
        }.borderWidth(2).margin(10).alignItems(HorizontalAlign.Start).borderColor(Color.Blue)

        TextArea()
          .borderWidth(2)
          .height(500)
          .opacity(0)
      }
    }
  }
}