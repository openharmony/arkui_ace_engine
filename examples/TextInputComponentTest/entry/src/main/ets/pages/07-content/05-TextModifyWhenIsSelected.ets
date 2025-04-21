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
struct TextModifyWhenIsSelected {
  @State text: string = '选中文本1时，切换到文本2，需要显示光标。\n1、点击“设置文本1”。\n2、点击“设置选中位置”。\n3、点击“设置文本2”。\n4、观察光标。预期有展示光标。'
  controller: TextAreaController = new TextAreaController();

  build() {
    Column({ space: '20px' }) {
      TextArea({
        text: this.text,
        controller: this.controller
      })
        .caretStyle({ width: 20 })
        .caretColor(Color.Red)
      Button('设置文本1')
        .onClick(() => {
          this.text = '=========文本1========='
        })
      Button('设置选中位置')
        .onClick(() => {
          this.controller.setTextSelection(0, 5, { menuPolicy: MenuPolicy.SHOW })
        })
      Button('设置文本2')
        .onClick(() => {
          this.text = '=========文本2========='
        })
    }
  }
}