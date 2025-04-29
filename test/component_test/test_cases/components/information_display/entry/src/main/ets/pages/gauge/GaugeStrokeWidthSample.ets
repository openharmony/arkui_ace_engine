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
import gaugeStrokeWidthTest from '../MyTest/GaugeStrokeWidthTest'
import { loadComponentTestEntry } from '@ohos.arkui.componentTest'

@Entry
@Component
struct GaugeStrokeWidthSample {
  @State strokeWidthStatus: Length = 50

  aboutToAppear(): void {
    loadComponentTestEntry(gaugeStrokeWidthTest)
  }

  build() {
    Column() {
      Gauge({ value: 50, min: 1, max: 100 })
        .strokeWidth(this.strokeWidthStatus)
        .width(150)
        .height(150)
        .id('gaugeStrokeWidth1')
      Gauge({ value: 50, min: 1, max: 100 })
        .strokeWidth("40px")
        .width(150)
        .height(150)
        .id('gaugeStrokeWidth2')
      Button('GaugeStrokeWidth1')
        .onClick(() => {
          this.strokeWidthStatus = $r('app.string.data_panel_strokeWidth')
        })
      Button('GaugeStrokeWidth2')
        .onClick(() => {
          this.strokeWidthStatus = -10
        })
    }
  }
}