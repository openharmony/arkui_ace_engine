/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
//测试代码路径
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'
import textInputCaretColorTest from '../MyTest/TextInputCaretColorTest'

@Entry
@Component
struct TextInputCaretColorSample {
  @State text: string = ''
  @State caretColorType: ResourceColor = 0xffffff
  controller: TextInputController = new TextInputController()

  aboutToAppear(): void {
    loadComponentTestEntry(textInputCaretColorTest)
  }

  build() {
    Column() {
      TextInput({ text: this.text, controller: this.controller })
        .caretColor(Color.Pink)
        .id('textInputCaretColor1')
      TextInput({ text: this.text, controller: this.controller })
        .caretColor(this.caretColorType)
        .id('textInputCaretColor2')
      Button('TextInputCaretColor1')
        .onClick(() => {
          this.caretColorType = 'rgb(255, 100, 255)'
        })
      Button('TextInputCaretColor2')
        .onClick(() => {
          this.caretColorType = $r('sys.color.ohos_id_color_text_hyperlink')
        })
    }
  }
}