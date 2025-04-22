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
struct Ets_8_1_onChange {
  @State time_onchange_1: number = 0
  @State text_1: string = '这是一段示例内容用于测试onChange'
  controller_1: TextInputController = new TextInputController()
  @State time_onchange_2: number = 0
  @State text_2: string = '测试外接键盘onChange'
  controller_2: TextInputController = new TextInputController()
  @State time_onchange_3: number = 0
  @State text_3: string = '0123456789'
  controller_3: TextInputController = new TextInputController()

  build() {
    Scroll() {
      Column() {
        Text() {
          Span('onChange事件\n')
          Span('规格1 输入内容发生变化时，触发该回调。 触发条件：软键盘输入，粘贴、剪切，回调内容是输入框内完整内容。\n')
          Span('规格2 输入内容发生变化时，触发该回调。 触发条件：外接键盘输入，键盘快捷键Ctrl+v。 \n').fontColor(Color.Red)
          Span('规格3 因输入超出限制而未成功输入，不触发回调。 没写 \n').fontColor(Color.Red)
        }

        Column() {
          Text('规格1 规格1 输入内容发生变化时，触发该回调。 触发条件：键盘输入，粘贴、剪切，键盘快捷键Ctrl+v')
            .fontColor(Color.Blue)
          Text('测试步骤：')
          Text('1、点击按钮1 插入一段文本')
          Text('2、点击按钮2 删除一段文本')
          Text('3、点击按钮3 选中一段文本')
          Text('4、弹出窗口中点击 剪切')
          Text('5、点击文本框，点击手柄中的小圆球，弹窗中点击 粘贴')
          Text('pass条件：回调内容与textInput内容一致，每次操作后，触发次数+1').fontColor(Color.Red)
          Text('下面是 需要测试的区域')
          TextInput({ text: this.text_1, controller: this.controller_1 })
            .margin(1)
            .type(InputType.Normal)
            .id('TextInput_1')
            .onChange((value: string) => {
              this.time_onchange_1++;
              this.text_1 = value
            })
          Text('这是回调触发次数')
          Text('触发次数 ' + this.time_onchange_1).margin(1)
          Text('这是回调内容')
          Text(this.text_1).margin(1)

          Row() {
            Button('1插入一段文本')
              .onClick(() => {
                this.text_1 = this.text_1 + ' ,插入一段文本'
              })
            Button('2删除一段内容')
              .onClick(() => {
                this.text_1 = this.text_1.substring(0, this.text_1.length - 8)
              })
            Button('3选中一段内容')
              .onClick(() => {
                this.getUIContext().getFocusController().requestFocus('TextInput_1')
                setTimeout(() => {
                  this.controller_1.setTextSelection(4, 6, { menuPolicy: MenuPolicy.SHOW })
                }, 100)
              })
          }

        }.borderWidth(2).margin(10).alignItems(HorizontalAlign.Start).borderColor(Color.Blue)

        Column() {
          Text('规格2 textArea，输入法回车键类型为EnterKeyType.NEW_LINE时，不触发onSubmit').fontColor(Color.Blue)
          Text('说明：还不会写按钮模拟键盘输入的操作，请外接键盘')
          Text('步骤：1、点击按钮1 获得焦点')
          Text('步骤：2、键盘输入一个字符')
          Text('步骤：3、点击按钮2 选中一段文本，键盘ctrl+c')
          Text('步骤：4、移动选中区手柄，按下ctrl+v')
          Text('pass条件： 步骤2、4，回调次数+1').fontColor(Color.Red)
          TextInput({ text: this.text_2, controller: this.controller_2 })
            .margin(1)
            .type(InputType.Normal)
            .id('TextInput_2')
            .onChange((value: string) => {
              this.time_onchange_2++;
              this.text_2 = value
            })
          Text('这是回调触发次数')
          Text('触发次数 ' + this.time_onchange_2).margin(1)
          Text('这是回调内容')
          Text(this.text_2).margin(1)
          Row() {
            Button('1获得焦点')
              .onClick(() => {
                this.getUIContext().getFocusController().requestFocus('TextInput_2')
              })
            Button('2选中一段内容')
              .onClick(() => {
                this.getUIContext().getFocusController().requestFocus('TextInput_2')
                setTimeout(() => {
                  this.controller_2.setTextSelection(4, 6, { menuPolicy: MenuPolicy.SHOW })
                }, 100)
              })
          }
        }.borderWidth(2).margin(10).alignItems(HorizontalAlign.Start).borderColor(Color.Blue)

        Column() {
          Text('规格3 因输入超出限制而未成功输入，不触发回调。 ').fontColor(Color.Blue)
          Text('说明：已经设置了maxLength(10)')
          Text('步骤：1、点击按钮1插入一段文本 ')
          Text('步骤：2、点击按钮2选中一段内容 ')
          Text('步骤：3、点击复制')
          Text('步骤：4、点击文本末尾，点击手柄中的小圆球，弹窗中点击 粘贴')
          Text('步骤：5、点击文本框其他位置，点击手柄中的小圆球，弹窗中点击 粘贴')
          Text('pass条件：回调次数不变').fontColor(Color.Red)
          TextInput({ text: this.text_3, controller: this.controller_3 })
            .margin(1)
            .type(InputType.Normal)
            .id('TextInput_3')
            .maxLength(10)
            .onChange((value: string) => {
              this.time_onchange_3++;
              this.text_3 = value
            })
          Row() {
            Button('1插入一段文本')
              .onClick(() => {
                this.text_3 = this.text_3 + ' ,插入一段文本'
              })
            Button('2选中一段内容')
              .onClick(() => {
                this.getUIContext().getFocusController().requestFocus('TextInput_3')
                setTimeout(() => {
                  this.controller_3.setTextSelection(4, 6, { menuPolicy: MenuPolicy.SHOW })
                }, 100)
              })
          }

          Text('这是回调触发次数')
          Text('触发次数 ' + this.time_onchange_3).margin(1)

        }.borderWidth(2).margin(10).alignItems(HorizontalAlign.Start).borderColor(Color.Blue)

        TextArea()
          .borderWidth(2)
          .height(500)
          .opacity(0)

      }
    }
  }
}