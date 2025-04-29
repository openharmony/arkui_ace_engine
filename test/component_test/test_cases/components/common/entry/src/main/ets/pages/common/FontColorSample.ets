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

import fontColorTest from '../MyTest/FontColorTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct FontColorSample {
  @State any_Color: ResourceColor = $r("app.string.common_color")

  aboutToAppear(): void {
    loadComponentTestEntry(fontColorTest)
  }

  build() {
    Column({ space: 5 }) {

      Text('Color')
        .fontColor(this.any_Color)
        .id('textFontColor1')

      Row() {
        Button("ButtonFontColor1")
          .onClick(() => {
            this.any_Color = Color.Red
          })
        Button("ButtonFontColor2")
          .onClick(() => {
            this.any_Color = 0xaaffaa
          })
        Button("ButtonFontColor3")
          .onClick(() => {
            this.any_Color = 'rgba(255, 224, 0, 1.00)'
          })
      }
    }
  }
}
