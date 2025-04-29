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
import textFontColorTest from '../MyTest/TextFontColorTest'

@Entry
@Component
struct TextFontColorSample {
  @State colorValue: ResourceColor = 0x0000FF

  aboutToAppear(): void {
    loadComponentTestEntry(textFontColorTest)
  }

  build() {
    Column() {
      Text('text')
        .fontColor(Color.Orange)
        .id('textFontColor1')
      Text('text')
        .fontColor(this.colorValue)
        .id('textFontColor2')
      Button('TextFontColor1')
        .onClick(() => {
          this.colorValue = '#ffe72727'
        })
      Button('TextFontColor2')
        .onClick(() => {
          this.colorValue = $r('sys.color.ohos_id_color_text_hyperlink')
        })
    }
  }
}