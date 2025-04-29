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
import gaugeIndicatorTest from '../MyTest/GaugeIndicatorTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct GaugeIndicatorSample {
  @State indicatorStatus: GaugeIndicatorOptions | null = { space: '10px' }

  aboutToAppear(): void {
    loadComponentTestEntry(gaugeIndicatorTest)
  }

  build() {
    Column() {
      Gauge({ value: 50, min: 1, max: 100 })
        .indicator(this.indicatorStatus)
        .width(100)
        .height(100)
        .id('gaugeIndicator1')
      Gauge({ value: 50, min: 1, max: 100 })
        .indicator({ icon: $rawfile('Gauge.svg'), space: '40vp' })
        .width(100)
        .height(100)
        .id('gaugeIndicator2')
      Gauge({ value: 50, min: 1, max: 100 })
        .indicator({ space: '40fp' })
        .width(100)
        .height(100)
        .id('gaugeIndicator3')
      Button('GaugeIndicator1')
        .onClick(() => {
          this.indicatorStatus = { space: '50lpx' }
        })
      Button('GaugeIndicator2')
        .onClick(() => {
          this.indicatorStatus = { space: $r('app.string.gauge_dimension') }
        })
      Button('GaugeIndicator3')
        .onClick(() => {
          this.indicatorStatus = null
        })
    }
  }
}