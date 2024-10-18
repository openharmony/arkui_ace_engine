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
import progressStyleRingStyleOptionsTest from '../MyTest/ProgressStyleRingStyleOptionsTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct ProgressStyleRingStyleOptionsSample {
  aboutToAppear(): void {
    loadComponentTestEntry(progressStyleRingStyleOptionsTest)
  }

  @State style: RingStyleOptions = {
    strokeWidth: 5,
    shadow: true,
    status: ProgressStatus.LOADING,
    enableScanEffect: true,
    enableSmoothEffect: true
  }

  build() {
    Column({ space: 15 }) {
      Progress({ value: 100, type: ProgressType.Ring })
        .height(50)
        .width(100)
        .color(Color.Blue)
        .value(60)
        .width(100)
        .style(this.style)
        .id('progressStyleRingStyleOptions')
      Button('ProgressStyleRingStyleOptions1')
        .onClick(() => {
          this.style = {
            strokeWidth: '20px',
            shadow: false,
            status: ProgressStatus.PROGRESSING,
            enableScanEffect: false,
            enableSmoothEffect: false
          }
        })
      Button('ProgressStyleRingStyleOptions2')
        .onClick(() => {
          this.style = {
            strokeWidth: $r("app.string.stroke_width_length"),
            shadow: true,
            status: ProgressStatus.PROGRESSING,
            enableScanEffect: true,
            enableSmoothEffect: true
          }
        })
    }
  }
}