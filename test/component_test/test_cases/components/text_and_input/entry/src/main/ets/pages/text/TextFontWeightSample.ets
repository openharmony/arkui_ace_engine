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
import textFontWeightTest from '../MyTest/TextFontWeightTest'

@Entry
@Component
struct TextFontWeightSample {
  @State fontWeightType: FontWeight[] = [FontWeight.Regular, FontWeight.Bold, FontWeight.Medium, FontWeight.Bolder, 100]
  @State index: number = 0

  aboutToAppear(): void {
    loadComponentTestEntry(textFontWeightTest)
  }

  build() {
    Column() {
      Text('text')
        .fontWeight(FontWeight.Normal)
        .id('textFontWeight1')
      Text('text')
        .fontWeight(FontWeight.Lighter)
        .id('textFontWeight2')
      Text('text')
        .fontWeight("300")
        .id('textFontWeight3')
      Text('text')
        .fontWeight(this.fontWeightType[this.index])
        .id('textFontWeight4')
      Button('TextFontWeight')
        .onClick(() => {
          this.index++
          this.index %= 5
        })
    }
  }
}