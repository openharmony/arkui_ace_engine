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
struct Ets_8_15_shortcut_key {
  @State text_1: string = '这是一段示例内容用于测试撤销/重做🤣🤣🤣🤣🤣'

  build() {
    Scroll() {
      Column() {
        Text() {
          Span('快捷键测试\n')
          Span('规格1 Ctrl+Z撤销 Ctlr+Y/Ctrl+Shift+Z重做，记录操作的队列上限为20，超出后队首记录移除，撤销不应该使文本被清空\n')
        }

        Column() {
          Text('规格1 在输入框内进行输入或删除操作后进行撤销/重做').fontColor(Color.Blue)
          Text('测试步骤：')
          Text('1、删除一个🤣')
          Text('2、撤销两次')
          Text('3、重做两次')
          Text('4、逐字删除全部文本')
          Text('5、撤销到不能撤销为止')
          Text('pass条件：步骤2未清空文本，步骤3恢复删除一个🤣的状态，步骤5无法恢复原始文本').fontColor(Color.Red)
          TextInput({ text: this.text_1 }).margin(1).type(InputType.Normal)
        }.borderWidth(2).margin(10).alignItems(HorizontalAlign.Start).borderColor(Color.Blue)
      }
    }
  }
}