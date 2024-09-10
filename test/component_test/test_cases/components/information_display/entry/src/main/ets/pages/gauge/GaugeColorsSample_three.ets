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
import gaugeColorsTest_three from '../MyTest/GaugeColorsTest_three'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct GaugeColorsSample_three {
  @State colorsStatus: ResourceColor | LinearGradient | Array<[ResourceColor | LinearGradient, number]> =
    $r('app.color.data_panel_resource_color5')

  aboutToAppear(): void {
    loadComponentTestEntry(gaugeColorsTest_three)
  }

  build() {
    Column() {
      Gauge({ value: 50, min: 1, max: 100 })
        .colors(this.colorsStatus)
        .width(50)
        .height(50)
        .id('gaugeColors1')
      Gauge({ value: 50, min: 1, max: 100 })
        .colors(new LinearGradient([{ color: Color.Green, offset: 0 }, { color: Color.Brown, offset: 1 }]))
        .width(50)
        .height(50)
        .id('gaugeColors2')
      Gauge({ value: 50, min: 1, max: 100 })
        .colors(new LinearGradient([{ color: "#e84026", offset: '0%' }, { color: "#64bb5c", offset: '100%' }]))
        .width(50)
        .height(50)
        .id('gaugeColors3')
      Button('GaugeColors1')
        .onClick(() => {
          this.colorsStatus = [[$r('app.color.data_panel_resource_color6'), 8],
            [$r('app.color.data_panel_resource_color5'), 5],
            [$r('app.color.data_panel_resource_color1'), 1]]
        })
      Button('GaugeColors2')
        .onClick(() => {
          this.colorsStatus =
            [[new LinearGradient([{ color: Color.Brown, offset: 0 }, { color: Color.Blue, offset: 1 }]), 9],
              [new LinearGradient([{ color: Color.Pink, offset: 0 }, { color: Color.Yellow, offset: 1 }]), 1]]
        })
      Button('GaugeColors3')
        .onClick(() => {
          this.colorsStatus =
            [[new LinearGradient([{ color: 0x317AF7, offset: 0 }, { color: 0x5BA854, offset: 1 }]), 9],
              [new LinearGradient([{ color: 0xFFFF00, offset: 0 }, { color: 0x008000, offset: 1 }]), 1]]
        })
    }
  }
}