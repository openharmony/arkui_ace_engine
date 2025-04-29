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
struct Ets_8_3_onEditChange {
  @State time_onEditChange_1: number = 0
  @State boolean_1: boolean = false

  build() {
    Scroll() {
      Column() {
        Text() {
          Span('onSubmit事件\n')
          Span('规格1 获焦返回true，失焦返回false\n')
          Span('规格2 获焦状态进入任务中心，不产生回调\n')
          Span('规格3 获焦状态关应用会有一次false回调\n')
        }

        Column() {
          Text('规格1 获焦返回true，失焦返回false').fontColor(Color.Blue)
          Text('测试步骤：\n 1、点击 \n 2、收起键盘\n  3、点击 \n 4、拉起任务中心\n ')
          Text('pass条件：点击true，收起键盘false，点击true，拉起任务中心不变').fontColor(Color.Red)
          TextInput({ text: '这是一段示例内容用于测试 onEditChange' }).margin(1).type(InputType.Normal)
            .enterKeyType(EnterKeyType.NEW_LINE)
            .onEditChange((isEditing: boolean) => {
              this.boolean_1 = isEditing
              this.time_onEditChange_1++
            })

          Text('这是回调触发次数')
          Text('触发次数 ' + this.time_onEditChange_1).margin(1)
          Text('这是回调返回值')
          Text('返回值 ' + this.boolean_1).margin(1)
        }.borderWidth(2).margin(10).alignItems(HorizontalAlign.Start).borderColor(Color.Blue)

        TextArea()
          .borderWidth(2)
          .height(500)
          .opacity(0)
      }
    }
  }
}