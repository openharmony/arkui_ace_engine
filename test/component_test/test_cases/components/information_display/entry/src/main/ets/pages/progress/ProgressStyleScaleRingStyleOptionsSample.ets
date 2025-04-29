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
import progressStyleRingStyleOptionsTest from '../MyTest/ProgressStyleScaleRingStyleOptionsTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ProgressStyleScaleRingStyleOptionsSample {
  @State style: ScaleRingStyleOptions = {
    strokeWidth: 6,
    scaleWidth: 3,
    scaleCount: 150,
    enableSmoothEffect: true
  }

  aboutToAppear(): void {
    loadComponentTestEntry(progressStyleRingStyleOptionsTest)
  }

  build() {
    Column({ space: 15 }) {
      Progress({ value: 100, total: 100, type: ProgressType.ScaleRing })
        .height(30)
        .width(200)
        .color(Color.Blue)
        .value(60)
        .width(100)
        .style(this.style)
        .id('progressStyleScaleRingStyleOptions')
      Button('ProgressStyleScaleRingStyleOptions1')
        .onClick(() => {
          this.style = {
            strokeWidth: '1px',
            scaleWidth: '4px',
            scaleCount: 150,
            enableSmoothEffect: false
          }
        })
      Button('ProgressStyleScaleRingStyleOptions2')
        .onClick(() => {
          this.style = {
            strokeWidth: $r("app.string.stroke_width_length"),
            scaleWidth: $r("app.string.scale_width_length"),
            scaleCount: 150,
            enableSmoothEffect: true
          }
        })
    }
  }
}