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
import textAreaFontColorTest from '../MyTest/TextAreaFontColorTest'

@Entry
@Component
struct TextAreaFontColorSample {
  @State fontColorType: ResourceColor = 0xffffff

  aboutToAppear(): void {
    loadComponentTestEntry(textAreaFontColorTest)
  }

  build() {
    Column() {
      TextArea()
        .fontColor(Color.Orange)
        .id('textAreaFontColor1')
      TextArea()
        .fontColor(this.fontColorType)
        .id('textAreaFontColor2')
      Button('TextAreaFontColor1')
        .onClick(() => {
          this.fontColorType = 'rgb(255, 100, 255)'
        })
      Button('TextAreaFontColor2')
        .onClick(() => {
          this.fontColorType = $r('sys.color.ohos_id_color_text_hyperlink')
        })
    }
  }
}