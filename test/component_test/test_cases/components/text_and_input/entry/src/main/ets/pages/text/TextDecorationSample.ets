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
import textDecorationTest from '../MyTest/TextDecorationTest'

@Entry
@Component
struct TextDecorationSample {
  @State typeValue: TextDecorationType = TextDecorationType.Overline
  @State colorValue: ResourceColor = '#ff2a65dd'

  aboutToAppear(): void {
    loadComponentTestEntry(textDecorationTest)
  }

  build() {
    Column() {
      Text('text')
        .decoration({
          type: TextDecorationType.None,
          color: Color.Red
        })
        .id('textDecoration1')
      Text('text')
        .decoration({
          type: this.typeValue,
          color: this.colorValue
        })
        .id('textDecoration2')
      Button('TextDecoration1')
        .onClick(() => {
          this.typeValue = TextDecorationType.Underline
          this.colorValue = $r('sys.color.ohos_id_color_text_hyperlink')
        })
      Button('TextDecoration2')
        .onClick(() => {
          this.typeValue = TextDecorationType.LineThrough
          this.colorValue = 0xffffff
        })
    }
  }
}