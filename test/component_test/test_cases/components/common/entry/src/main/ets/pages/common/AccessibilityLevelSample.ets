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

import accessibilityLevelTest from '../MyTest/AccessibilityLevelTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct accessibilityLevelSample {
  @State changeString: string = "auto"
  @State oneButtonColor: string = '#FFC0CB'

  aboutToAppear(): void {
    loadComponentTestEntry(accessibilityLevelTest)
  }

  build() {
    Column() {
      Gauge({ value: 5, min: 1, max: 100 })
        .accessibilityLevel(this.changeString).id('gaugeAccessibilityLevel1')

      Blank()
        .color("rgba(95, 255, 240, 1.00)")
        .height(100)
        .width(100)
        .accessibilityLevel("auto")
        .id('blankAccessibilityLevel1')

      Button("ButtonAccessibilityLevel1")
        .onClick(() => {
          this.changeString = "no-hide-descendants"
        })
      Button("ButtonAccessibilityLevel2")
        .onClick(() => {
          this.changeString = "no"
        })
      Button("ButtonAccessibilityLevel3")
        .onClick(() => {
          this.changeString = "yes"
        })
    }
  }
}