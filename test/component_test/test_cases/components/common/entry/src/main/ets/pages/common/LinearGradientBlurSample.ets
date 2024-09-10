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

import linearGradientBlurTest from '../MyTest/LinearGradientBlurTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct LinearGradientBlurSample {
  gradientDirectionArr: GradientDirection[] = [GradientDirection.Left,
    GradientDirection.Top, GradientDirection.Right, GradientDirection.Bottom,
    GradientDirection.LeftTop, GradientDirection.LeftBottom, GradientDirection.RightTop,
    GradientDirection.RightBottom, GradientDirection.None]
  index: number = 0
  @State gradientDirection: GradientDirection = this.gradientDirectionArr[this.index]

  aboutToAppear(): void {
    loadComponentTestEntry(linearGradientBlurTest)
  }

  build() {
    Column({ space: 10 }) {
      Image($r('app.media.app_icon'))
        .linearGradientBlur(60, {
          fractionStops: [[0, 0], [0, 0.33], [1, 0.66], [1, 1]],
          direction: this.gradientDirection
        })
        .id('imageLinearGradientBlur')
        .width(200)
        .height(200)

      Button('ButtonLinearGradientBlur').onClick(() => {
        this.index++
        this.gradientDirection = this.gradientDirectionArr[this.index % 9]
      })
    }
  }
}