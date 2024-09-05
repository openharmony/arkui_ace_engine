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
import spanFontWeightTest from '../MyTest/SpanFontWeightTest'

@Entry
@Component
struct SpanFontWeightSample {
  @State weightType: FontWeight[] = [FontWeight.Regular, FontWeight.Bold, FontWeight.Medium, FontWeight.Bolder, 100]
  @State index: number = 0

  aboutToAppear(): void {
    loadComponentTestEntry(spanFontWeightTest)
  }

  build() {
    Column() {
      Text() {
        Span('span')
          .fontWeight(this.weightType[this.index])
          .id('spanFontWeight1')
        Span('span')
          .fontWeight(FontWeight.Lighter)
          .id('spanFontWeight2')
        Span('span')
          .fontWeight(FontWeight.Normal)
          .id('spanFontWeight3')
        Span('span')
          .fontWeight("600")
          .id('spanFontWeight4')
      }

      Button('SpanFontWeight')
        .onClick(() => {
          this.index++
          this.index %= 5
        })
    }
  }
}