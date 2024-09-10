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
import textClockFontWeightTestOne from '../MyTest/TextClockFontWeightTestOne'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct TextClockFontWeightSampleOne {
  @State fontWeight: number | FontWeight | string = 500

  aboutToAppear(): void {
    loadComponentTestEntry(textClockFontWeightTestOne)
  }

  build() {
    Column({ space: 8 }) {
      TextClock()
        .id('textClockFontWeight1')
        .fontWeight(this.fontWeight)
      TextClock()
        .id('textClockFontWeight2')
        .fontWeight(FontWeight.Normal)
      TextClock()
        .id('textClockFontWeight3')
        .fontWeight(FontWeight.Lighter)
      Button('TextClockFontWeight1')
        .onClick(() => {
          this.fontWeight = "lighter"
        })
      Button('TextClockFontWeight2')
        .onClick(() => {
          this.fontWeight = FontWeight.Bold
        })
    }
  }
}