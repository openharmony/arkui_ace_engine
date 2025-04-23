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
struct Ets_8_5_onPaste {
  @State timeOnCut1: number = 0
  @State cut1: string = ''
  @State shareIndex: number = 0
  @State onCutIndex: number = 0
  @State onChangeIndex: number = 0
  @State onTextSelectionChangeIndex: number = 0

  build() {
    Scroll() {
      Column() {
        Text() {
          Span('onSubmit事件')
          Span('规格1 回调顺序 onPaste-->onChange-->onTextSelectionChange')
          Span('规格2 从键盘剪切板直接粘贴不触发回调 不会写').fontColor(Color.Red)
          Span('规格3 使用preventDefault之后，不会有粘贴效果，但是不会影响回调的value').fontColor(Color.Red)
        }

        Column() {
          Text('规格1 回调顺序 onCut-->onChange-->onTextSelectionChange').fontColor(Color.Blue)
          Text('测试步骤：\n 选中文本，长按输入框，点击剪切板剪切按钮，点击粘贴，。\n ')
          Text('pass条件：回调顺序 onPaste-->onChange-->onTextSelectionChange').fontColor(Color.Red)
          TextInput({ text: '这是一段示例内容用于测试 onPaste' })
            .margin(1)
            .type(InputType.Normal)
            .enterKeyType(EnterKeyType.NEW_LINE)
            .onPaste((value: string) => {
              this.cut1 = value
              this.shareIndex++;
              this.onCutIndex = this.shareIndex;
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
          Text('onPaste 触发次序 ' + this.onCutIndex)
          Text('onChange 触发次序 ' + this.onChangeIndex)
          Text('onTextSelectionChange 触发次序 ' + this.onTextSelectionChangeIndex)

          Text('这是回调触发次数')
          Text('触发次数 ' + this.timeOnCut1).margin(1)
          Text('这是回调返回值')
          Text('返回值 ' + this.cut1).margin(1)
        }.borderWidth(2).margin(10).alignItems(HorizontalAlign.Start).borderColor(Color.Blue)


        Column() {
          Text('规格3 使用preventDefault之后，不会有粘贴效果，但是不会影响回调的value').fontColor(Color.Blue)
          Text('测试步骤：\n 选中文本，长按输入框，点击剪切板剪切按钮，点击粘贴，。\n ')
          Text('pass条件：点击粘贴后，文本内容不变；回调次数+1，返回值发生变化').fontColor(Color.Red)
          TextInput({ text: '这是一段示例内容用于测试 onPaste' }).margin(1).type(InputType.Normal)
            .enterKeyType(EnterKeyType.NEW_LINE)
            .onPaste((value: string, event: PasteEvent) => {
              this.cut1 = value
              this.timeOnCut1++;
              event.preventDefault!()
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