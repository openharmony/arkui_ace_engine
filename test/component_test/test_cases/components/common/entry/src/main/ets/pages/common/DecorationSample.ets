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

import decorationTest from '../MyTest/DecorationTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct DecorationSample {
  @State any_Type: TextDecorationType = TextDecorationType.None
  @State any_Color: ResourceColor = $r("app.string.common_color")
  @State any_Style: TextDecorationStyle = TextDecorationStyle.SOLID

  aboutToAppear(): void {
    loadComponentTestEntry(decorationTest)
  }

  build() {
    Column({ space: 5 }) {
      Text('Hello, Text!')
        .decoration({ type: this.any_Type, color: this.any_Color, style: this.any_Style })
        .id('textDecoration1')
      Button('ButtonDecoration1')
        .onClick(() => {
          this.any_Type = TextDecorationType.LineThrough
          this.any_Color = Color.Orange
          this.any_Style = TextDecorationStyle.DOUBLE
        })
      Button('ButtonDecoration2')
        .onClick(() => {
          this.any_Type = TextDecorationType.Underline
          this.any_Color = 0xaaffaa
          this.any_Style = TextDecorationStyle.DOTTED
        })
      Button('ButtonDecoration3')
        .onClick(() => {
          this.any_Type = TextDecorationType.Overline
          this.any_Color = 'rgba(255, 0, 255, 1.00)'
          this.any_Style = TextDecorationStyle.DASHED
        })
      Button('ButtonDecoration4')
        .onClick(() => {
          this.any_Style = TextDecorationStyle.WAVY
        })
    }
  }
}