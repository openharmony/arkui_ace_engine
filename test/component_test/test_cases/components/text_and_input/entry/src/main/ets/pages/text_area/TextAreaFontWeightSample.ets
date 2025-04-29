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
import textAreaFontWeightTest from '../MyTest/TextAreaFontWeightTest'

@Entry
@Component
struct TextAreaFontWeightSample {
  @State weightType: FontWeight[] = [FontWeight.Regular, FontWeight.Bold, FontWeight.Medium, FontWeight.Bolder, 800]
  @State index: number = 0

  aboutToAppear(): void {
    loadComponentTestEntry(textAreaFontWeightTest)
  }

  build() {
    Column() {
      TextArea()
        .fontWeight(FontWeight.Lighter)
        .id('textAreaFontWeight1')
      TextArea()
        .fontWeight(FontWeight.Normal)
        .id('textAreaFontWeight2')
      TextArea()
        .fontWeight(this.weightType[this.index])
        .id('textAreaFontWeight3')
      Button('TextAreaFontWeight')
        .onClick(() => {
          this.index++
          this.index %= 5
        })
      TextArea()
        .fontWeight('400')
        .id('textAreaFontWeight4')
    }
  }
}