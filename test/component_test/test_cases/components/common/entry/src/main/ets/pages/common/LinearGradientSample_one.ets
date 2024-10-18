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

import linearGradientTest_one from '../MyTest/LinearGradientTest_one'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct LinearGradientSample_one {
  @State gradientDirectionArr: GradientDirection[] =
    [GradientDirection.Left, GradientDirection.Top, GradientDirection.Right, GradientDirection.Bottom,
      GradientDirection.LeftTop, GradientDirection.LeftBottom, GradientDirection.RightTop,
      GradientDirection.RightBottom, GradientDirection.None]
  index: number = 0
  @State type: GradientDirection = this.gradientDirectionArr[this.index]

  aboutToAppear(): void {
    loadComponentTestEntry(linearGradientTest_one)
  }

  build() {
    Column() {
      List()
        .width('80%')
        .height(50)
        .id('listLinearGradient1')
        .linearGradient({
          angle: 90,
          repeating: false,
          colors: [['#ff0000', 0.2], [0x0000ff, 0.3], [$r('sys.color.ohos_id_color_text_secondary_dark'), 0.5]]
        })
      List()
        .width('80%')
        .height(50)
        .id('listLinearGradient2')
        .linearGradient({
          angle: '20%',
          repeating: true,
          direction: this.type,
          colors: [[Color.Red, 1.0]]
        })
      Button('ButtonLinearGradient1')
        .onClick(() => {
          this.index++
          this.type = this.gradientDirectionArr[this.index % 9]
        })
    }
  }
}