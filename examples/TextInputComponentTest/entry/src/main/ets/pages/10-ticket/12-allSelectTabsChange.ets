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
struct allSelectTabsChange {
  build() {
    Column({ space: 5 }) {
      Text('操作：1、TextInput、TextArea、Search输入框均输入文本;\n2、设备外接键盘，按Tabs键，依次走焦;\n3、观察输入框全选和手柄状态')
        .margin(5)
        .fontSize(14)
        .fontColor(Color.Blue)
        .borderWidth(1)
        .width('90%')

      Text('Pass条件：输入框均能出现全选高亮背景以及双手柄')
        .margin(5)
        .fontSize(14)
        .fontColor(Color.Red)
        .borderWidth(1)
        .width('90%')

      TextInput({ placeholder: 'please input word' })
        .width('90%')

      Blank()
      Search({ placeholder: 'please input word' })
        .width('90%')

      Blank()
      TextArea({ placeholder: 'please input word' })
        .width('90%')
        .height('80')


    }.width('100%')
  }
}