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
import gaugeColorsTest_two from '../MyTest/GaugeColorsTest_two'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct GaugeColorsSample_two {
  @State colorsStatus: ResourceColor | LinearGradient | Array<[ResourceColor | LinearGradient, number]> =
    new LinearGradient([{ color: 0xFFA500, offset: $r('app.float.data_panel_offset_min') },
      { color: 0xFFFF00, offset: $r('app.float.data_panel_offset_max') }])

  aboutToAppear(): void {
    loadComponentTestEntry(gaugeColorsTest_two)
  }

  build() {
    Column() {
      Gauge({ value: 50, min: 1, max: 100 })
        .colors(this.colorsStatus)
        .width(50)
        .height(50)
        .id('gaugeColors1')
      Gauge({ value: 50, min: 1, max: 100 })
        .colors(new LinearGradient([{ color: $r('app.color.data_panel_resource_color5'), offset: 0 },
          { color: $r('app.color.data_panel_resource_color3'), offset: 1 }]))
        .width(50)
        .height(50)
        .id('gaugeColors2')
      Button('GaugeColors1')
        .onClick(() => {
          this.colorsStatus =
            [[new LinearGradient([{ color: "#deb6fb", offset: 0 }, { color: "#ac49f5", offset: 1 }]), 9],
              [new LinearGradient([{ color: "#b5e0f4", offset: 0 }, { color: "#46b1e3", offset: 1 }]), 1]]
        })
      Button('GaugeColors2')
        .onClick(() => {
          this.colorsStatus = [[new LinearGradient([{ color: $r('app.color.data_panel_resource_color1'), offset: 0 },
            { color: $r('app.color.data_panel_resource_color3'), offset: 1 }]), 9],
            [new LinearGradient([{ color: $r('app.color.data_panel_resource_color2'), offset: 0 },
              { color: $r('app.color.data_panel_resource_color6'), offset: 1 }]), 1]]
        })
    }
  }
}