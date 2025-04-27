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
struct Ets_8_7_onContentScroll {
  @State timeOnCut1: number = 0
  @State cut1: string = ''
  @State text1: string = '这是一段单行文本这是一段单行文本  到这里刚好一行整'
  @State textReset: string = '这是一段单行文本这是一段单行文本  到这里刚好一行整'
  controller1: TextInputController = new TextInputController()
  @State shareIndex: number = 0
  @State onChangeIndex: number = 0
  @State onContentScrollIndex: number = 0
  @State onTextSelectionChangeIndex: number = 0

  build() {
    Scroll() {
      Column() {
        Text() {
          Span('onContentScroll 事件')
          Span('规格1 回调顺序 onChange-->onContentScroll-->onTextSelectionChange')
        }

        Column() {
          Text('规格1 回调顺序 onChange-->onContentScroll-->onTextSelectionChange').fontColor(Color.Blue)
          Text('测试步骤：\n 点击按钮1 。\n ')
          Text('pass条件：回调顺序 onChange-->onContentScroll-->onTextSelectionChange').fontColor(Color.Red)
          TextInput({ text: this.text1, controller: this.controller1 })
            .margin(1)
            .type(InputType.Normal)
            .id('TextInput_1')
            .style(TextInputStyle.Inline)
            .maxLines(1)
            .enterKeyType(EnterKeyType.NEW_LINE)
            .onContentScroll(() => {
              this.shareIndex++;
              this.onContentScrollIndex = this.shareIndex;
            })
            .onChange(() => {
              this.shareIndex++;
              this.onChangeIndex = this.shareIndex;
            })
            .onTextSelectionChange(() => {
              this.shareIndex++;
              this.onTextSelectionChangeIndex = this.shareIndex;
            })

          Text('这是触发顺序 ').fontColor(Color.Red)
          Text('onChange 触发次序 ' + this.onChangeIndex)
          Text('onContentScroll 触发次序 ' + this.onContentScrollIndex)
          Text('onTextSelectionChange 触发次序 ' + this.onTextSelectionChangeIndex)

          Button('规格1 插入一个字')
            .width('90%')
            .margin(2)
            .onClick(() => {
              this.getUIContext().getFocusController().requestFocus('TextInput_1')
              this.text1 = this.text1 + '换'
            })
          Button('规格1 重置')
            .width('90%')
            .margin(2)
            .onClick(() => {
              this.getUIContext().getFocusController().requestFocus('TextInput_1')
              this.text1 = this.textReset
            })

          Text('这是回调触发次数')
          Text('触发次数 ' + this.timeOnCut1).margin(1)
          Text('这是回调返回值')
          Text('返回值 ' + this.cut1).margin(1)
        }.borderWidth(2).margin(10).alignItems(HorizontalAlign.Start).borderColor(Color.Blue)

        TextArea()
          .borderWidth(2)
          .height(500)
          .opacity(0)

      }
    }
  }
}