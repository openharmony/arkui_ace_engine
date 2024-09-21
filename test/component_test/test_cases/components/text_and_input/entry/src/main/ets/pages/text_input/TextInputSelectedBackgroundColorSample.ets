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
import textInputSelectedBackgroundColorTest from '../MyTest/TextInputSelectedBackgroundColorTest'

@Entry
@Component
struct TextInputSelectedBackgroundColorSample {
  @State text: string = ''
  @State selectedBackgroundColorType: ResourceColor = 0xffffff
  controller: TextInputController = new TextInputController()

  aboutToAppear(): void {
    loadComponentTestEntry(textInputSelectedBackgroundColorTest)
  }

  build() {
    Column() {
      TextInput({ text: this.text, controller: this.controller })
        .selectedBackgroundColor(Color.Pink)
        .id('textInputSelectedBackgroundColor1')
      TextInput({ text: this.text, controller: this.controller })
        .selectedBackgroundColor(this.selectedBackgroundColorType)
        .id('textInputSelectedBackgroundColor2')
      Button('TextInputSelectedBackgroundColor1')
        .onClick(() => {
          this.selectedBackgroundColorType = 'rgb(255, 100, 255)'
        })
      Button('TextInputSelectedBackgroundColor2')
        .onClick(() => {
          this.selectedBackgroundColorType = $r('sys.color.ohos_id_color_text_hyperlink')
        })
    }
  }
}