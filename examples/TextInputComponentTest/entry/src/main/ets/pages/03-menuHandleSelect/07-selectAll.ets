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
struct SelectAllStruct {
  controller: TextAreaController = new TextAreaController()
  @State change: boolean = false

  build() {
    Column({ space: 10 }) {
      Text('获焦时选中所有文本').margin({ top: 20 })
      TextInput({ placeholder: 'TextInput', text: '能否选中全部文本', controller: this.controller })
        .selectAll(this.change)
        .margin(10)
        .width('95%')
        .height(60)
        .textAlign(TextAlign.Start)

      Row({ space: 10 }) {
        Button('是否支持全选：' + this.change)
          .onClick(() => {
            if (this.change == true) {
              this.change = false
            } else {
              this.change = true
            }
          })
      }
    }
  }
}