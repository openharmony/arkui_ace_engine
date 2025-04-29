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
import fontWeightTest from '../MyTest/FontWeightTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct FontWeightSample {
  @State myFontWeight: FontWeight[] = [FontWeight.Lighter, FontWeight.Normal,
    FontWeight.Regular, FontWeight.Medium, FontWeight.Bold, FontWeight.Bolder]
  index = 0
  @State anyFontWeight: FontWeight = this.myFontWeight[this.index]

  aboutToAppear(): void {
    loadComponentTestEntry(fontWeightTest)
  }

  build() {
    Column() {
      TextArea()
        .fontWeight(700)
        .id('textAreaFontWeight1')

      TextArea()
        .fontWeight("500")
        .id('textAreaFontWeight2')

      Text('hello world')
        .fontWeight(this.anyFontWeight)
        .id('textFontWeight3')

      Button('ButtonFontWeight1')
        .onClick(() => {
          this.index++
          this.anyFontWeight = this.myFontWeight[this.index % 6]
        })
    }
  }
}

