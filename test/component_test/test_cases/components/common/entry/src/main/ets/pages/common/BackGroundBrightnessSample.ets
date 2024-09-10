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

import backGroundBrightnessTest from '../MyTest/BackGroundBrightnessTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct BackGroundBrightnessSample {
  @State backgroundBrightness_value_1: BackgroundBrightnessOptions = { rate: 0, lightUpDegree: 0 }
  @State backgroundBrightness_value_2: BackgroundBrightnessOptions = { rate: 999, lightUpDegree: 1 }
  @State any: BackgroundBrightnessOptions = { rate: 400, lightUpDegree: -1 }

  aboutToAppear(): void {
    loadComponentTestEntry(backGroundBrightnessTest)
  }

  build() {
    Column({ space: 10 }) {
      Row() {
        Text('backgroundBrightness').fontSize(18)
        Blank().color(Color.Yellow)
        Toggle({ type: ToggleType.Button })
          .margin({
            top: 14,
            bottom: 14,
            left: 6,
            right: 6
          })
      }
      .width(200)
      .height(200)
      .position({ x: 100, y: 100 })
      .backgroundBlurStyle(BlurStyle.Thin, {
        colorMode: ThemeColorMode.LIGHT,
        adaptiveColor: AdaptiveColor.DEFAULT,
        scale: 1.0
      })
      .backgroundBrightness(this.any)
      .id('rowBackgroundBrightness1')

      Button('RowBackgroundBrightness1').onClick(() => {
        this.any = this.backgroundBrightness_value_1
      })
      Button('RowBackgroundBrightness2').onClick(() => {
        this.any = this.backgroundBrightness_value_2
      })
    }
  }
}
