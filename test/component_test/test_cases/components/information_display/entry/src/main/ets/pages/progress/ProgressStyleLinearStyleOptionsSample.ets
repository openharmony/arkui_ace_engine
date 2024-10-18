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
import progressStyleLinearStyleOptionsTest from '../MyTest/ProgressStyleLinearStyleOptionsTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ProgressStyleLinearStyleOptionsSample {
  @State style: LinearStyleOptions = {
    strokeWidth: 5,
    strokeRadius: '3px',
    enableScanEffect: true,
    enableSmoothEffect: true
  }

  aboutToAppear(): void {
    loadComponentTestEntry(progressStyleLinearStyleOptionsTest)
  }

  build() {
    Column({ space: 15 }) {
      Progress({ value: 100, total: 100, type: ProgressType.Linear })
        .height(10)
        .width(200)
        .color(Color.Blue)
        .value(60)
        .width(100)
        .style(this.style)
        .id('progressStyleLinearStyleOptions')
      Button('ProgressStyleLinearStyleOptions1')
        .onClick(() => {
          this.style = {
            strokeWidth: '4px',
            strokeRadius: '2vp',
            enableScanEffect: false,
            enableSmoothEffect: false
          }
        })
      Button('ProgressStyleLinearStyleOptions2')
        .onClick(() => {
          this.style = {
            strokeWidth: $r("app.string.stroke_width_length"),
            strokeRadius: '2lpx',
            enableScanEffect: true,
            enableSmoothEffect: true
          }
        })
      Button('ProgressStyleLinearStyleOptions3')
        .onClick(() => {
          this.style = {
            strokeWidth: 6,
            strokeRadius: $r("app.string.scale_radius"),
            enableScanEffect: true,
            enableSmoothEffect: true
          }
        })
    }
  }
}