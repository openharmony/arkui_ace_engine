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
struct Ets_8_6_onTextSelectionChange {
  @State time1: number = 0
  @State cut1: string = ''
  @State startIndex1: number = -1
  @State endIndex1: number = -1
  @State time2: number = 0
  @State startIndex2: number = -1
  @State endIndex2: number = -1
  @State onChangeIndex: number = 0
  @State onTextSelectionChangeIndex: number = 0

  build() {
    Scroll() {
      Column() {
        Text() {
          Span('onTextSelectionChange 事件')
          Span('规格1 初次显示时会有一次回调，值为文本长度')
          Span('规格2 未选中时，每次内容变化也会触发回调，start = end = 光标位置')
        }

        Column() {
          Text('规格1 初次显示时会有一次回调，值为文本长度(12,12)').fontColor(Color.Blue)
          Text('测试步骤：观察 ')
          Text('pass条件：首次进入该页面时 value—1 的值是 (12,12)').fontColor(Color.Red)
          TextInput({ text: '这是一段示例内容用于测试' }).margin(1).type(InputType.Normal)
            .onTextSelectionChange((selectionStart: number, selectionEnd: number) => {
              this.startIndex1 = selectionStart
              this.endIndex1 = selectionEnd
              this.time1++
            })

          Text('value-1的值 ').fontColor(Color.Red)
          Text('(start, end) == (' + this.startIndex1 + ',' + this.endIndex1 + ')')

          Text('这是回调触发次数')
          Text('触发次数 ' + this.time1).margin(1)

        }.borderWidth(2).margin(10).alignItems(HorizontalAlign.Start).borderColor(Color.Blue)

        Column() {
          Text('规格2 未选中时，每次内容变化也会触发回调，start = end = 光标位置').fontColor(Color.Blue)
          Text('测试步骤：点击文本框，输入字符 123 ')
          Text('pass条件：start=end, 数值一次是11 12 13').fontColor(Color.Red)
          TextInput({ text: '0123456789' }).margin(1).type(InputType.Normal)
            .onTextSelectionChange((selectionStart: number, selectionEnd: number) => {
              this.startIndex2 = selectionStart
              this.endIndex2 = selectionEnd
              this.time2++
            })

          Text('value-2的值 ').fontColor(Color.Red)
          Text('(start, end) == (' + this.startIndex2 + ',' + this.endIndex2 + ')')

          Text('这是回调触发次数')
          Text('触发次数 ' + this.time2).margin(1)

        }.borderWidth(2).margin(10).alignItems(HorizontalAlign.Start).borderColor(Color.Blue)


        TextArea()
          .borderWidth(2)
          .height(500)
          .opacity(0)
      }
    }
  }
}