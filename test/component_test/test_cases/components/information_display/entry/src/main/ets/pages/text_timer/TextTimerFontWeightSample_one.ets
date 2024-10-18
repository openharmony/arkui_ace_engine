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
import textTimerFontWeightTest_one from '../MyTest/TextTimerFontWeightTest_one'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct TextTimerFontWeightSample_one {
  @State test1: number | FontWeight | string = FontWeight.Normal

  aboutToAppear(): void {
    loadComponentTestEntry(textTimerFontWeightTest_one)
  }

  build() {
    Column({ space: 8 }) {
      TextTimer().fontWeight(FontWeight.Lighter).id('textTimerFontWeight1')
      TextTimer().fontWeight(this.test1).id('textTimerFontWeight2')
      Button('TextTimerFontWeight')
        .onClick(() => {
          this.test1 = FontWeight.Bold
        })
      TextTimer().fontWeight(FontWeight.Regular).id('textTimerFontWeight3')
    }
  }
}