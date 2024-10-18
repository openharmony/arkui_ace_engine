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
import gaugeColorsTest_one from '../MyTest/GaugeColorsTest_one'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct GaugeColorsSample_one {
  @State colorsStatus: ResourceColor | LinearGradient | Array<[ResourceColor | LinearGradient, number]> = Color.Green

  aboutToAppear(): void {
    loadComponentTestEntry(gaugeColorsTest_one)
  }

  build() {
    Column() {
      Gauge({ value: 50, min: 1, max: 100 })
        .colors(this.colorsStatus)
        .width(50)
        .height(50)
        .id('gaugeColors1')
      Gauge({ value: 50, min: 1, max: 100 })
        .colors(0x0000FF)
        .width(50)
        .height(50)
        .id('gaugeColors2')
      Gauge({ value: 50, min: 1, max: 100 })
        .colors('#201bf5df')
        .width(50)
        .height(50)
        .id('gaugeColors3')
      Button('GaugeColors1')
        .onClick(() => {
          this.colorsStatus = [[Color.Green, 8], [Color.Brown, 5], [Color.Pink, 1]]
        })
      Button('GaugeColors2')
        .onClick(() => {
          this.colorsStatus = [['#20e38c8c', 8], ['#201660e0', 5], ['#00FF00', 1]]
        })
      Button('GaugeColors3')
        .onClick(() => {
          this.colorsStatus = [[0xFFA500, 8], [0xFFFF00, 5], [0x00FF00, 1]]
        })
    }
  }
}