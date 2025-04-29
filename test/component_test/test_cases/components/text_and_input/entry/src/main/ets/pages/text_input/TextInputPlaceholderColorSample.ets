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
import textInputPlaceholderColorTest from '../MyTest/TextInputPlaceholderColorTest'

@Entry
@Component
struct TextInputPlaceholderColorSample {
  @State text: string = ''
  @State placeholderColorType: ResourceColor = 0xffffff
  controller: TextInputController = new TextInputController()

  aboutToAppear(): void {
    loadComponentTestEntry(textInputPlaceholderColorTest)
  }

  build() {
    Column() {
      TextInput({ placeholder: 'Please input', text: this.text, controller: this.controller })
        .placeholderColor(Color.Green)
        .id('textInputPlaceholderColor1')
      TextInput({ placeholder: 'Please input', text: this.text, controller: this.controller })
        .placeholderColor(this.placeholderColorType)
        .id('textInputPlaceholderColor2')
      Button('TextInputPlaceholderColor1')
        .onClick(() => {
          this.placeholderColorType = '#99182431'
        })
      Button('TextInputPlaceholderColor2')
        .onClick(() => {
          this.placeholderColorType = $r('sys.color.ohos_id_color_text_hyperlink')
        })
    }
  }
}