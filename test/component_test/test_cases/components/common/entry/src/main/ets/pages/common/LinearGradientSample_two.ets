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

import linearGradientTest_two from '../MyTest/LinearGradientTest_two'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct LinearGradientSample_two {
  @State gradientDirectionArr: GradientDirection[] =
    [GradientDirection.Left, GradientDirection.Top, GradientDirection.Right, GradientDirection.Bottom,
      GradientDirection.LeftTop, GradientDirection.LeftBottom, GradientDirection.RightTop,
      GradientDirection.RightBottom, GradientDirection.None]
  index: number = 0
  @State type: GradientDirection = this.gradientDirectionArr[this.index]

  aboutToAppear(): void {
    loadComponentTestEntry(linearGradientTest_two)
  }

  build() {
    Column() {

      List()
        .width('80%')
        .height(50)
        .id('listLinearGradient3')
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